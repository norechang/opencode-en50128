# Software Architecture Specification (SAS)

**REFERENCE**: EN 50128:2011 Section 7.3, Table A.3, Annex C Item 9

---

## DOCUMENT CONTROL

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SAS-2026-001 |
| **CI ID** | CI-SAS-TDC-001 |
| **Version** | 0.2 DRAFT |
| **Date** | 2026-04-02 |
| **Project** | TDC (Train Door Control System) |
| **SIL Level** | SIL 3 |
| **Author** | Software Designer (DES) |
| **Status** | Draft |

### Revision History

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-04-02 | DES | Initial draft — Phase 3 software architecture from SRS and Hazard Log | — |
| 0.2 | 2026-04-02 | DES | Resolve OI-FTA-003: unify CRC-16 polynomial to CRC-16-CCITT (0x1021) across all SPI and safety-critical CAN messages. Resolve OI-FMEA-001: specify SPI transient filter (3-consecutive-cycle confirmation for infrastructure faults; immediate for safety-data disagreements). Add SW-HAZ-011 traceability (new hazard from DOC-FMEA-2026-001). Close OI-SAS-005. | — |

---

## APPROVALS

**EN 50128 Annex C Table C.1 Signature Chain — Item 9 (SAS) — Track A (Development)**

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Author (DES) | Software Designer | _____________ | 2026-04-02 |
| Reviewer (QUA) | Quality Assurance | _____________ | __________ |
| Approver (PM) | Project Manager | _____________ | __________ |

**Notes:**
- Track A sign-off only. VER and VAL are Track B independent reviewers; their sign-off is
  recorded in their own reports (item 14: Architecture and Design Verification Report,
  item 25: Software Validation Report) — NOT in this document's Approvals table.
- DES has no authorship role in items 12, 13, 14 (owned by INT or VER).
- All submissions route through PM — DES does not contact QUA or VER directly.

---

## 1. INTRODUCTION

### 1.1 Purpose

This Software Architecture Specification (SAS) defines the high-level software architecture
for the **Train Door Control System (TDC)** software running on the Door Control Unit (DCU).
It is produced in accordance with EN 50128:2011 Section 7.3 and constitutes Annex C Item 9.

This document:
- Decomposes the TDC software into major architectural components and layers
- Defines the safety architecture including 2oo2 dual-channel design, fault detection,
  and safe state management
- Specifies component interfaces and data flows at architecture level
- Allocates SRS requirements and Hazard Log entries to software components
- Documents the mandatory structured methodology and modular approach (Table A.3)
- Establishes the Requirements → Architecture traceability matrix (mandatory at SIL 3)

### 1.2 Scope

This SAS applies to the TDC software executing on the Door Control Unit (DCU) — a
dual-channel (2oo2) bare-metal embedded system based on two STM32H743 MCUs (Channel A
and Channel B), each running the same software binary with independent sensor inputs and
independent safety decision logic.

**In Scope**:
- All software executing on Channel A (MCU-A) and Channel B (MCU-B)
- Safety Kernel, Door State Machine, Speed Monitor, Obstacle Detector, TCMS Interface,
  Fault Manager, Diagnostics, and Hardware Abstraction Layer components
- Cross-channel SPI communication and 2oo2 comparison logic
- Static cyclic executive scheduler (20 ms cycle)

**Out of Scope**:
- Hardware design (DOC-HW-DES-2026-001)
- System-level requirements (DOC-SYS-REQ-2026-001)
- Bootloader software (separate deliverable)
- Software Integration Test Specification (item 12, owned by INT)
- Software Architecture and Design Verification Report (item 14, owned by VER)

### 1.3 SIL Classification

**Target SIL Level**: SIL 3

SIL 3 is derived from hazard analysis per EN 50126-2. The highest-severity hazards
(SW-HAZ-001, SW-HAZ-002, SW-HAZ-003, SW-HAZ-004, SW-HAZ-006, SW-HAZ-007, SW-HAZ-008)
require SIL 3 mitigation. The overall project SIL cap is SIL 3.

### 1.4 Definitions and Acronyms

| Term | Definition |
|------|------------|
| **2oo2** | Two-out-of-two voting — both channels/sensors must agree |
| **CCF** | Common Cause Failure |
| **CRC** | Cyclic Redundancy Check — **CRC-16-CCITT, polynomial 0x1021** (unified; 0x8005 is NOT used in TDC) |
| **DCU** | Door Control Unit — dual-channel (2oo2) embedded processing module |
| **DDU** | Door Drive Unit — per-door electromechanical actuator |
| **DGN** | Diagnostics component |
| **DSM** | Door State Machine component |
| **FMG** | Fault Manager component |
| **HAL** | Hardware Abstraction Layer component |
| **MCU** | Microcontroller Unit (STM32H743, ARM Cortex-M7, 400 MHz) |
| **OBD** | Obstacle Detector component |
| **SKN** | Safety Kernel component |
| **SPM** | Speed Monitor component |
| **TCI** | TCMS Interface component |
| **TCMS** | Train Control Management System |
| **WCET** | Worst-Case Execution Time |

### 1.5 Input Documents

| Document ID | Title | Version | Role |
|-------------|-------|---------|------|
| DOC-SRS-2026-001 | Software Requirements Specification | 0.1 DRAFT | Primary input |
| DOC-HAZLOG-2026-001 | Hazard Log | 0.2 | Safety requirements and hazard allocation input |
| DOC-SQAP-2026-001 | Software Quality Assurance Plan | — | Process constraints |
| DOC-SCMP-2026-001 | Software Configuration Management Plan | — | CM constraints |
| DOC-SVP-2026-001 | Software Verification Plan | — | Verification obligations |
| DOC-SYS-ARCH-2026-001 | System Architecture Description | — | System context |

### 1.6 Output Documents

| Document ID | Title | Owner |
|-------------|-------|-------|
| DOC-SDS-2026-001 | Software Design Specification (item 10) | DES |
| DOC-SIS-2026-001 | Software Interface Specifications (item 11) | DES |
| DOC-SITSPEC-2026-001 | Software Integration Test Specification (item 12) | INT |
| DOC-DESVER-2026-001 | Architecture and Design Verification Report (item 14) | VER |

---

## 2. STRUCTURED METHODOLOGY

**EN 50128 Table A.3 Entry 1 — Structured Methodology: Mandatory at SIL 3–4**

The TDC software architecture has been produced using the **Yourdon Structured Analysis /
Structured Design (SASD)** methodology, which is explicitly listed in EN 50128 §7.3 as a
compliant structured methodology (Annex D.52).

The methodology was applied as follows:

| SASD Activity | Applied To | Section |
|---------------|-----------|---------|
| Context diagram — system boundary identification | Section 3.1 (System Context) | §3.1 |
| Functional decomposition — top-down hierarchical decomposition | Components identified (§4) | §4 |
| Data flow diagrams — inter-component data flows | Section 5 (Data Flow Architecture) | §5 |
| Data dictionary — data types and structures | Section 5 and SDS (item 10) | §5, SDS |
| Module cohesion and coupling analysis | Section 4 per-component specs | §4 |
| Safety allocation — safety requirements to components | Section 6 (Safety Architecture) | §6 |

**Rationale for SASD selection**: SASD is well-suited to real-time embedded control
systems. It provides explicit data flow visibility required for SIL 3 cross-channel
comparison design, and its structured decomposition supports the mandatory Modular
Approach (Table A.3 entry 19).

---

## 3. SYSTEM CONTEXT

### 3.1 Architectural Overview

The TDC software executes on a dual-channel Door Control Unit (DCU). Both channels
(Channel A and Channel B) execute the same software binary with independent sensor
inputs. Safety decisions are validated by 2oo2 cross-channel comparison.

```
+============================================================================+
|              EXTERNAL SYSTEMS                                              |
|                                                                            |
|  +-----------+    +------------------+    +---------------------+          |
|  | Driver    |    | TCMS             |    | DDU x N (per door)  |          |
|  | Control   |<-->| CAN 2.0B         |    | RS-485, 115.2 kbit/s|          |
|  | Panel     |    | 250 kbit/s       |    +----------+----------+          |
|  +-----+-----+    +--------+---------+               |                    |
|        | 24V I/O            | CAN (0x100-0x104)       | RS-485             |
|        v                    v                         v                    |
|  +----------------------------------------------------------------------+  |
|  |       Door Control Unit (DCU) — SIL 3 Software Boundary             |  |
|  |                                                                      |  |
|  |   +---------------------------+   +---------------------------+      |  |
|  |   |  CHANNEL A (MCU-A)        |   |  CHANNEL B (MCU-B)        |      |  |
|  |   |  STM32H743, 400 MHz       |<->|  STM32H743, 400 MHz       |      |  |
|  |   |                           |   |                           |      |  |
|  |   |  [SKN] Safety Kernel      |   |  [SKN] Safety Kernel      |      |  |
|  |   |  [SPM] Speed Monitor      |   |  [SPM] Speed Monitor      |      |  |
|  |   |  [OBD] Obstacle Detector  |   |  [OBD] Obstacle Detector  |      |  |
|  |   |  [DSM] Door State Machine |   |  [DSM] Door State Machine |      |  |
|  |   |  [FMG] Fault Manager      |   |  [FMG] Fault Manager      |      |  |
|  |   |  [TCI] TCMS Interface     |   |  [TCI] TCMS Interface     |      |  |
|  |   |  [DGN] Diagnostics        |   |                           |      |  |
|  |   |  [HAL] HW Abstraction     |   |  [HAL] HW Abstraction     |      |  |
|  |   +---------------------------+   +---------------------------+      |  |
|  |          SPI 10 Mbit/s (cross_channel_state_t, CRC-16)               |  |
|  +----------------------------------------------------------------------+  |
|            |  Sensors / Actuators (via HAL)                               |
|    Position sensors (2x/door, 2oo2)   Obstacle sensors (2x/door)          |
|    Lock sensors (2x/lock, 2oo2)       Motor PWM (20 kHz)                  |
|    Lock actuators (24V solenoid)      Emergency release switch             |
+============================================================================+
```

**Execution model**: Static cyclic executive scheduler, 20 ms cycle, bare-metal
(no RTOS). Task execution order per REQ-OPR-008:

```
Cycle start (20 ms tick)
  1. Safety Kernel (SKN) — cross-channel gate check, safe state evaluation
  2. Speed Monitor (SPM) — read CAN speed, validate, update interlock flag
  3. Obstacle Detector (OBD) — poll obstacle sensors, evaluate reversal
  4. Door State Machine (DSM) — process door commands and sensor 2oo2 voting
  5. Fault Manager (FMG) — evaluate all fault flags, update fault state
  6. Cross-Channel SPI — transmit/receive cross_channel_state_t, compare
  7. Actuator outputs — apply HAL motor, lock, and indicator commands
  8. CAN transmit — send door status and departure interlock to TCMS
  9. RS-485 DDU — exchange motor commands and position feedback
 10. Watchdog refresh — kick hardware watchdog (HAL_Watchdog_Refresh)
 11. Diagnostics (DGN) — log events (if non-safety buffer available)
Cycle end
```

---

## 4. ARCHITECTURAL COMPONENTS

**EN 50128 Table A.3 Entry 19 — Modular Approach: Mandatory at SIL 2+**

The TDC software is decomposed into 8 cohesive, loosely coupled software components.
Each component has a single clearly-defined responsibility (high cohesion) and
communicates with other components only through well-defined interfaces (low coupling),
per the Modular Approach requirement.

### 4.1 Component Inventory

| Comp ID | Name | Acronym | SIL | Responsibility |
|---------|------|---------|-----|----------------|
| COMP-001 | Safety Kernel | SKN | SIL 3 | Cross-channel 2oo2 gate, safe state authority, departure interlock |
| COMP-002 | Speed Monitor | SPM | SIL 3 | TCMS speed validation, speed interlock flag management |
| COMP-003 | Obstacle Detector | OBD | SIL 3 | Obstacle sensor polling and ISR, reversal command authority |
| COMP-004 | Door State Machine | DSM | SIL 3 | Per-door FSM (OPEN/CLOSING/CLOSED_AND_LOCKED etc.), 2oo2 sensor voting |
| COMP-005 | Fault Manager | FMG | SIL 3 | Fault flag aggregation, fault classification, safe-state escalation |
| COMP-006 | TCMS Interface | TCI | SIL 3 | CAN message receive/transmit, CRC-16 check, sequence counter |
| COMP-007 | Diagnostics | DGN | SIL 1 | Event log (circular buffer, SPI Flash), diagnostic port access |
| COMP-008 | Hardware Abstraction Layer | HAL | SIL 3 | GPIO, PWM, CAN, SPI, RS-485, ADC, Watchdog drivers |

**Note**: DGN (COMP-007) is SIL 1 (non-safety), providing event logging only. It MUST NOT
influence safety decisions. It executes last in each cycle (lowest priority).

### 4.2 COMP-001: Safety Kernel (SKN)

| Attribute | Value |
|-----------|-------|
| **Responsibility** | Central authority for 2oo2 cross-channel gating, safe state management, and departure interlock output. SKN is the only component permitted to assert or de-assert the `safe_state_active` flag and the `departure_interlock_ok` output. |
| **SIL** | SIL 3 |
| **Cyclomatic complexity limit** | ≤ 10 per function (SIL 3 mandatory) |
| **Executes at** | Cycle step 1 (first in every 20 ms cycle) |
| **Inputs** | `cross_channel_state_t` from Channel B (via SPI), speed interlock flag (SPM), door states (DSM), lock states (DSM), fault flags (FMG), watchdog status |
| **Outputs** | `safe_state_active` flag (`uint8_t`), `departure_interlock_ok` flag (`uint8_t`), safe-state command to FMG |
| **Safety functions** | SF-002 (Departure Interlock), SF-004 (Safe State on Fault), SF-005 (Door Position Verification) |
| **Key constraints** | (1) Safe state entry is irreversible within a cycle — once set, only a power cycle or maintenance reset clears it. (2) Departure interlock only asserted when ALL DSM instances report CLOSED_AND_LOCKED AND cross-channel comparison passes. (3) Division by zero guard before all arithmetic (SEEA: SKN/division-by-zero). (4) Departure interlock flag initialized to LOCKED_UNKNOWN at startup (SEEA: SKN/uninitialized-flag). |

**Interfaces**:

| Direction | Interface | Data Type | Destination |
|-----------|-----------|-----------|-------------|
| IN | Cross-channel SPI receive | `cross_channel_state_t` | Channel B → Channel A SKN |
| IN | Speed interlock flag | `uint8_t` | SPM → SKN |
| IN | Door states array | `uint8_t[MAX_DOORS]` | DSM → SKN |
| IN | Lock states array | `uint8_t[MAX_DOORS]` | DSM → SKN |
| IN | Fault flag register | `uint8_t` | FMG → SKN |
| OUT | Safe state flag | `uint8_t` | SKN → all components |
| OUT | Departure interlock signal | `uint8_t` | SKN → TCI (CAN 0x200) |
| OUT | Safe state command | void | SKN → FMG |

**Hazard allocation**: SW-HAZ-001 (speed interlock), SW-HAZ-003 (false lock indication),
SW-HAZ-006 (watchdog failure). Safety requirements: REQ-SAFE-007, REQ-SAFE-008,
REQ-SAFE-009, REQ-SAFE-014, REQ-SAFE-015.

---

### 4.3 COMP-002: Speed Monitor (SPM)

| Attribute | Value |
|-----------|-------|
| **Responsibility** | Receive TCMS speed data via CAN, validate CRC-16 and sequence counter, apply timeout logic, derive `speed_interlock_active` flag. SPM is the sole authority for speed data validity — no other component reads raw CAN speed directly. |
| **SIL** | SIL 3 |
| **Cyclomatic complexity limit** | ≤ 10 per function |
| **Executes at** | Cycle step 2 |
| **Inputs** | CAN message buffer (TCI provides validated frame), system tick (for timeout) |
| **Outputs** | `speed_interlock_active` flag (`uint8_t`, 1=inhibit-open), `current_speed_kmh_x10` (`uint16_t`), speed data validity timestamp |
| **Safety functions** | SF-001 (Speed Interlock) |
| **Key constraints** | (1) Default is "moving" (speed = UNKNOWN → inhibit open): if CAN timeout > 200 ms or CRC error, `speed_interlock_active` = 1. (2) NULL guard before CAN buffer access (SEEA: SPM/null-deref). (3) Range check: valid speed 0–3000 (km/h × 10); out-of-range → reject, log, treat as UNKNOWN (SEEA: SPM/integer-overflow). (4) Timestamp validation: if speed data age > 200 ms, treat as stale → `speed_interlock_active` = 1 (SEEA: SPM/stale-data). |

**Interfaces**:

| Direction | Interface | Data Type | Source / Destination |
|-----------|-----------|-----------|----------------------|
| IN | Validated CAN speed frame | `tcms_speed_msg_t` | TCI → SPM |
| IN | System tick | `uint32_t` (ms) | Scheduler → SPM |
| OUT | Speed interlock active | `uint8_t` | SPM → SKN, DSM |
| OUT | Current speed value | `uint16_t` (km/h × 10) | SPM → SKN, cross-channel |
| OUT | Speed data timestamp | `uint32_t` | SPM → SKN |

**Hazard allocation**: SW-HAZ-001, SW-HAZ-007. Safety requirements: REQ-SAFE-001,
REQ-SAFE-002, REQ-SAFE-003, REQ-SAFE-016.

---

### 4.4 COMP-003: Obstacle Detector (OBD)

| Attribute | Value |
|-----------|-------|
| **Responsibility** | Monitor obstacle sensors (interrupt-driven + polled every 20 ms), detect obstacles during door closing, issue motor reversal command. OBD is the sole authority for obstacle reversal decisions — no other component overrides an active reversal command. |
| **SIL** | SIL 3 |
| **Cyclomatic complexity limit** | ≤ 10 per function |
| **Executes at** | Cycle step 3; ISR: immediate (sub-1 ms) |
| **Inputs** | Obstacle sensor A and B (HAL GPIO, per door), door state (from DSM), closing flag |
| **Outputs** | `obstacle_detected` flag per door (`uint8_t`), motor reversal command (to DSM/actuator) |
| **Safety functions** | SF-003 (Obstacle Detection and Reversal) |
| **Key constraints** | (1) Either sensor triggering is sufficient to issue reversal (conservative 1oo2 for detection). (2) Fail-safe: NULL sensor pointer → treat as OBSTACLE_DETECTED (SEEA: OBD/null-deref). (3) Saturating arithmetic for force current value; capped at MAX_FORCE before comparison (SEEA: OBD/integer-overflow). (4) Execution time monitoring: if OBD task overruns > 25 ms, FMG triggers safe state (SEEA: OBD/timing-fault). (5) Reversal command issued within 100 ms of detection (leaving 50 ms hardware margin within 150 ms REQ-PERF-003 budget). |

**Interfaces**:

| Direction | Interface | Data Type | Source / Destination |
|-----------|-----------|-----------|----------------------|
| IN | Obstacle sensor A/B | `uint8_t` per door | HAL GPIO → OBD |
| IN | Door closing flag | `uint8_t` per door | DSM → OBD |
| OUT | Obstacle detected flag | `uint8_t[MAX_DOORS]` | OBD → DSM, SKN, cross-channel |
| OUT | Reversal command | `uint8_t` per door | OBD → HAL PWM direction |

**Hazard allocation**: SW-HAZ-002. Safety requirements: REQ-SAFE-004, REQ-SAFE-005,
REQ-SAFE-006.

---

### 4.5 COMP-004: Door State Machine (DSM)

| Attribute | Value |
|-----------|-------|
| **Responsibility** | Per-door finite state machine (FSM) managing door position states. Applies 2oo2 sensor voting for position and lock status. Generates door state variables consumed by SKN, SPM, TCI, and FMG. DSM is the sole authority for door position and lock state. |
| **SIL** | SIL 3 |
| **Cyclomatic complexity limit** | ≤ 10 per function |
| **Executes at** | Cycle step 4 |
| **Inputs** | Position sensor A+B per door (HAL GPIO), lock sensor A+B per door (HAL GPIO), open/close commands (from TCI), obstacle reversal (from OBD), speed interlock (from SPM), safe state (from SKN) |
| **Outputs** | Door state per door (`uint8_t[MAX_DOORS]`: FULLY_OPEN=1, INTERMEDIATE=2, FULLY_CLOSED=3, CLOSED_AND_LOCKED=4, UNKNOWN=5), lock state per door (`uint8_t[MAX_DOORS]`), lock actuator command (to HAL) |
| **Safety functions** | SF-002 (Departure Interlock), SF-005 (Door Position Verification) |
| **Door FSM States**: IDLE → OPENING → FULLY_OPEN → CLOSING → OBSTACLE_REVERSAL → FULLY_CLOSED → LOCKING → CLOSED_AND_LOCKED ↔ FAULT | |
| **Key constraints** | (1) State machine stuck-at detection: each state has maximum dwell time; dwell exceeded → watchdog-triggers safe state (SEEA: DSM/stuck-at). (2) Door index bounds check: 0 ≤ door_id < MAX_DOORS before any array access (SEEA: DSM/array-oob). (3) Lock status initialized to LOCKED_UNKNOWN at startup (SEEA: DSM/uninitialized). (4) CLOSED_AND_LOCKED only set when BOTH position sensors AND BOTH lock sensors agree (2oo2 × 2oo2). (5) No open command processed when `speed_interlock_active` = 1. |

**Door FSM Transition Table** (abbreviated):

| From State | Event | Guard | To State | Action |
|------------|-------|-------|----------|--------|
| IDLE | CMD_OPEN | speed=0, no fault | OPENING | Motor PWM open direction |
| OPENING | pos_A=OPEN AND pos_B=OPEN | — | FULLY_OPEN | Motor stop |
| OPENING | timer > 4000 ms | — | FAULT | Log OPEN_TIMEOUT, stop motor |
| FULLY_OPEN | CMD_CLOSE | no obstacle, no fault | CLOSING | Motor PWM close direction |
| CLOSING | obstacle detected | — | OBSTACLE_REVERSAL | Motor reverse (OBD authority) |
| CLOSING | pos_A=CLOSED AND pos_B=CLOSED | — | FULLY_CLOSED | Motor stop |
| CLOSING | timer > 10000 ms | — | FAULT | Log CLOSE_TIMEOUT, stop motor |
| FULLY_CLOSED | — | — | LOCKING | Lock actuator energize |
| LOCKING | lock_A=LOCKED AND lock_B=LOCKED | — | CLOSED_AND_LOCKED | Notify SKN |
| ANY | safe_state_active=1 | — | FAULT | Stop motor, lock doors |

**Interfaces**: (defined in SIS, DOC-SIS-2026-001)

**Hazard allocation**: SW-HAZ-003, SW-HAZ-004. Safety requirements: REQ-SAFE-007,
REQ-SAFE-008, REQ-SAFE-009, REQ-SAFE-010, REQ-SAFE-011.

---

### 4.6 COMP-005: Fault Manager (FMG)

| Attribute | Value |
|-----------|-------|
| **Responsibility** | Aggregate all fault flags from all components every 20 ms cycle. Classify faults by severity. Issue safe state command for critical faults. Provide fault status to TCI for TCMS reporting. FMG is the fault aggregation authority — it does not originate faults, it classifies and escalates them. |
| **SIL** | SIL 3 |
| **Cyclomatic complexity limit** | ≤ 10 per function |
| **Executes at** | Cycle step 5 |
| **Inputs** | Fault flags from SPM, OBD, DSM, TCI, HAL; execution time overrun flags (per component) |
| **Outputs** | `fault_state` (`uint8_t`), safe state command to SKN, fault report to TCI (CAN 0x202), fault log entry to DGN |
| **Safety functions** | SF-004 (Safe State on Fault) |
| **Key constraints** | (1) Fault counter initialized to 0 at startup and after safe state recovery (SEEA: FMG/uninitialized-counter). (2) Stuck-in-safe-state detection: FMG maintains max safe-state dwell time; on expiry with fault cleared → enter degraded mode (SEEA: FMG/stuck-at). (3) Selective door disablement (REQ-FUN-013) handled in FMG — disablement does NOT remove speed interlock. |

**Fault Classification Table**:

| Fault Category | Severity | Action |
|----------------|----------|--------|
| Speed interlock defeat | CRITICAL | Immediate safe state (both channels) |
| Cross-channel SPI mismatch | CRITICAL | Immediate safe state |
| CRC mismatch (any safety structure) | CRITICAL | Immediate safe state |
| Watchdog timeout | CRITICAL | Hardware reset (not software) |
| Sensor 2oo2 disagreement (position/lock) | HIGH | Door state → UNKNOWN; alert TCMS |
| CAN timeout (> 200 ms) | HIGH | Speed interlock → assume moving |
| Motor control failure | HIGH | Motor stop; alert TCMS |
| Obstacle sensor fault | HIGH | Close door disabled; alert TCMS |
| DDU communication timeout | MEDIUM | Log; alert TCMS; retry |
| Event log CRC error | LOW | Log; DGN fault; no safety impact |

**Interfaces**: (defined in SIS, DOC-SIS-2026-001)

**Hazard allocation**: SW-HAZ-005, SW-HAZ-006. Safety requirements: REQ-SAFE-012,
REQ-SAFE-013, REQ-SAFE-014, REQ-SAFE-015.

---

### 4.7 COMP-006: TCMS Interface (TCI)

| Attribute | Value |
|-----------|-------|
| **Responsibility** | Receive and validate CAN messages from TCMS (IDs 0x100–0x104). Transmit door status and departure interlock CAN messages (IDs 0x200–0x203). Apply CRC-16 on all safety-critical messages. Detect sequence counter discontinuities. |
| **SIL** | SIL 3 |
| **Cyclomatic complexity limit** | ≤ 10 per function |
| **Executes at** | Cycle step 8 (transmit); ISR (receive, interrupt-driven) |
| **Inputs** | CAN receive FIFO (HAL), departure interlock flag (SKN), door status (DSM), fault report (FMG) |
| **Outputs** | Validated CAN frames to SPM (speed), DSM (commands), FMG (faults); CAN transmit to TCMS |
| **Safety functions** | SF-001 (CAN speed data integrity) |
| **Key constraints** | (1) CRC mismatch → discard message, log, treat as timeout (SEEA: CAN-DRV/null-ptr). (2) NULL receive buffer guard (SEEA: CAN-DRV/null-ptr). (3) Sequence counter overflow handled: delta checked modulo 256 (SEEA: CAN-DRV/seq-counter-overflow). (4) CAN timeout 200 ms → SPM notified "no speed" → assume moving. |

**CAN Message Summary**:

| ID | Direction | Content | Period | SIL |
|----|-----------|---------|--------|-----|
| 0x100 | RX | Speed (`uint16_t` km/h×10), seq, CRC-16 | 100 ms | SIL 3 |
| 0x101 | RX | Door open command + authorization | On-event | SIL 3 |
| 0x102 | RX | Door close command | On-event | SIL 3 |
| 0x103 | RX | Mode change + authorization | On-event | SIL 3 |
| 0x104 | RX | Emergency stop | On-event | SIL 3 |
| 0x200 | TX | Departure interlock + per-door lock mask, CRC-16 | 100 ms | SIL 3 |
| 0x201 | TX | Per-door status (position, lock, fault), CRC-16 | 100 ms | SIL 2 |
| 0x202 | TX | System fault report | On-event + 500 ms | SIL 2 |
| 0x203 | TX | Mode status + door disable mask | On-change + 1 s | SIL 2 |

**Hazard allocation**: SW-HAZ-007. Safety requirements: REQ-SAFE-003, REQ-SAFE-016.

---

### 4.8 COMP-007: Diagnostics (DGN)

| Attribute | Value |
|-----------|-------|
| **Responsibility** | Write event log entries to circular buffer in SPI Flash (16 MB). Serve diagnostic data via USB/RS-232 at 115.2 kbit/s. DGN is SIL 1 — it MUST NOT affect safety decisions. Safety data is read-only within DGN. |
| **SIL** | SIL 1 |
| **Cyclomatic complexity limit** | ≤ 10 per function (applied uniformly) |
| **Executes at** | Cycle step 11 (last in cycle; non-safety) |
| **Inputs** | Event log entries from FMG, DSM, SKN; diagnostic port (USB/RS-232 RX) |
| **Outputs** | SPI Flash event log writes; diagnostic port (USB/RS-232 TX) |
| **Key constraints** | (1) Circular buffer: ≥ 1000 entries; CRC-16 per entry. (2) DGN MUST NOT hold or delay any safety-critical component. (3) If DGN overruns its cycle budget, it defers to next cycle — safety components are never blocked. (4) Diagnostic port: read-only during Normal mode. |

**Hazard allocation**: None (SIL 1 — no direct safety function). Supports fault
observability for SW-HAZ-001 through SW-HAZ-010 via event log.

---

### 4.9 COMP-008: Hardware Abstraction Layer (HAL)

| Attribute | Value |
|-----------|-------|
| **Responsibility** | Provide hardware-independent API for all I/O: GPIO, PWM, CAN controller, SPI (cross-channel), RS-485 (DDU), ADC (current sensing), Watchdog. HAL is the only component that accesses hardware registers directly. All other components call HAL APIs exclusively. |
| **SIL** | SIL 3 |
| **Cyclomatic complexity limit** | ≤ 10 per function |
| **Executes at** | Called by all components; ISR handlers registered in HAL |
| **Inputs** | Hardware peripheral registers (GPIO, TIM, CAN, SPI, USART, ADC, IWDG) |
| **Outputs** | Abstracted I/O results to calling components |
| **Key constraints** | (1) HAL functions return `error_t` on all I/O operations (never void for safety-critical). (2) Callers MUST check return value and escalate to FMG on error. (3) HAL MUST NOT contain safety logic — it is purely a hardware driver. (4) Static allocation only — all DMA buffers, CAN mailboxes, and SPI buffers are statically declared. |

**HAL API (architecture-level)**:

```c
/* Return type used throughout HAL — all safety-critical operations */
typedef enum {
    SUCCESS           = 0,
    ERR_NULL_PTR      = 1,
    ERR_RANGE         = 2,
    ERR_TIMEOUT       = 3,
    ERR_CRC           = 4,
    ERR_HW_FAULT      = 5,
    ERR_INVALID_STATE = 6,
    ERR_NOT_PERMITTED = 7,
    ERR_SENSOR_DISAGREE = 8,
    ERR_COMM_TIMEOUT  = 9,
    ERR_WATCHDOG      = 10
} error_t;

/* Motor control */
error_t HAL_PWM_SetDutyCycle(uint8_t door_id, uint8_t duty_percent);
error_t HAL_GPIO_SetMotorDirection(uint8_t door_id, uint8_t direction);

/* Sensor reads */
error_t HAL_GPIO_ReadPositionSensor(uint8_t door_id, uint8_t sensor_id, uint8_t *state);
error_t HAL_GPIO_ReadObstacleSensor(uint8_t door_id, uint8_t sensor_id, uint8_t *detected);
error_t HAL_GPIO_ReadLockSensor(uint8_t door_id, uint8_t sensor_id, uint8_t *locked);

/* Actuators */
error_t HAL_GPIO_SetLockActuator(uint8_t door_id, uint8_t locked);

/* Communications */
error_t HAL_CAN_Receive(uint32_t *msg_id, uint8_t *data, uint8_t *dlc);
error_t HAL_CAN_Transmit(uint32_t msg_id, const uint8_t *data, uint8_t dlc);
error_t HAL_SPI_CrossChannel_Exchange(const cross_channel_state_t *tx,
                                       cross_channel_state_t *rx);
error_t HAL_RS485_DDU_Exchange(uint8_t ddu_id, const uint8_t *cmd,
                                uint8_t cmd_len, uint8_t *resp, uint8_t *resp_len);

/* Watchdog */
void HAL_Watchdog_Refresh(void);  /* Must be called ≤ 40 ms; HW timeout = 50 ms */
```

**Hazard allocation**: SW-HAZ-006 (watchdog), SW-HAZ-008 (memory integrity via stack
canary). Safety requirements: REQ-SAFE-014, REQ-SAFE-017, REQ-SAFE-018.

---

## 5. INTER-COMPONENT INTERFACES

**EN 50128 §7.3.4.12–7.3.4.13 — Inter-component data flows, control flows, and shared
resources shall be defined in the Software Architecture Specification.**

Detailed interface specifications — including pre/postconditions, boundary values, and
timing constraints for every interface — are produced in the Software Interface
Specifications (SIS, Annex C Item 11, DOC-SIS-2026-001). This section provides the
architecture-level interface summary.

### 5.1 Interface Summary

| Interface ID | From | To | Data / Control | Type | Period |
|--------------|------|----|---------------|------|--------|
| IF-001 | TCI | SPM | `tcms_speed_msg_t` (CAN 0x100) | Data | 100 ms |
| IF-002 | SPM | SKN | `speed_interlock_active`, `current_speed_kmh_x10` | Data | Every cycle |
| IF-003 | SPM | DSM | `speed_interlock_active` (gate) | Control | Every cycle |
| IF-004 | HAL GPIO | DSM | Position sensor A+B, Lock sensor A+B (per door) | Data | Every cycle |
| IF-005 | HAL GPIO | OBD | Obstacle sensor A+B (per door) | Data | ISR + every cycle |
| IF-006 | OBD | DSM | `obstacle_flags[MAX_DOORS]` | Control | Every cycle |
| IF-007 | OBD | SKN | `obstacle_flags[MAX_DOORS]` | Data | Every cycle |
| IF-008 | DSM | SKN | `door_states[MAX_DOORS]`, `lock_states[MAX_DOORS]` | Data | Every cycle |
| IF-009 | DSM | TCI | Per-door status (position, lock, fault) | Data | 100 ms |
| IF-010 | DSM | HAL | Lock actuator command (`uint8_t` per door) | Control | On transition |
| IF-011 | DSM | HAL | Motor PWM duty + direction (per door) | Control | On command |
| IF-012 | FMG | SKN | `fault_state` bitmask | Data | Every cycle |
| IF-013 | FMG | TCI | Fault report (CAN 0x202) | Data | On-event + 500 ms |
| IF-014 | FMG | DGN | Fault log entry (`event_log_entry_t`) | Data | On-fault |
| IF-015 | SKN | all | `safe_state_active` flag (broadcast) | Control | Every cycle |
| IF-016 | SKN | TCI | `departure_interlock_ok` → CAN 0x200 | Control | 100 ms |
| IF-017 | SKN (Ch A) | SKN (Ch B) | `cross_channel_state_t` via SPI | Data | Every cycle |
| IF-018 | TCI | DSM | Door open/close/mode/emergency commands | Control | On-event |
| IF-019 | HAL | SKN | Watchdog status (implicit: no HAL error = refresh OK) | Control | Every cycle |
| IF-020 | DGN | SPI Flash | `event_log_entry_t[1024]` circular buffer | Data | Every cycle (deferred) |

### 5.2 Shared Resources

| Resource | Shared By | Access Control |
|----------|-----------|---------------|
| `safe_state_active` flag | Written by SKN only; read by all | Write: SKN exclusive; Read: all (polling) |
| `departure_interlock_ok` flag | Written by SKN only; read by TCI | Write: SKN exclusive |
| `door_states[MAX_DOORS]` | Written by DSM only; read by SKN, TCI | Write: DSM exclusive |
| `lock_states[MAX_DOORS]` | Written by DSM only; read by SKN, TCI | Write: DSM exclusive |
| `speed_interlock_active` | Written by SPM only; read by SKN, DSM | Write: SPM exclusive |
| SPI peripheral | SKN (cross-channel exchange) only | Exclusive use at cycle step 6 |
| CAN controller | TCI only | Exclusive; ISR for receive, polling for transmit |
| SPI Flash (event log) | DGN only (write); DGN/diagnostics port (read) | Exclusive write by DGN |

**Access rule**: No two components may write the same variable. Write authority is assigned
exclusively per the table above. This eliminates data races in the static cyclic executive
(no concurrent task execution on bare-metal single-core MCU).

### 5.3 Control Flow

The overall control flow is defined by the static cyclic executive (§3.1 execution order).
Within each 20 ms cycle, components execute in strict sequential order (no concurrency,
no preemption). Control flow between components occurs via:

1. **Safety gate signals** (synchronous): `safe_state_active`, `speed_interlock_active`
   — evaluated at start of each component that uses them.
2. **ISR → mailbox → polling** (asynchronous events): CAN receive ISR and obstacle ISR
   write to static mailboxes; component polling reads mailboxes at their cycle step.
3. **SPI cross-channel exchange** (synchronous, blocking): Channel A transmits then
   receives; comparison result available before actuator output step.

---

## 6. DATA FLOW ARCHITECTURE

### 5.1 Primary Safety Data Flows

```
[TCMS CAN] --> [TCI] --> [SPM] --> speed_interlock_active --> [SKN]
                                                            --> [DSM] (gate)

[HAL GPIO sensors] --> [DSM] --> door_states[MAX_DOORS] --> [SKN]
                              --> lock_states[MAX_DOORS] --> [SKN]
                              --> [TCI] (for CAN 0x201)

[HAL GPIO obstacle] --> [OBD] --> obstacle_flags[MAX_DOORS] --> [DSM]
                               --> [SKN] (cross-channel)

[all faults] --> [FMG] --> fault_state --> [SKN]
                        --> [TCI] (CAN 0x202)

[SKN] --> safe_state_active --> [all components] (broadcast)
       --> departure_interlock_ok --> [TCI] (CAN 0x200)

[Channel A SKN/SPM/OBD/DSM] --(SPI cross_channel_state_t)--> [Channel B SKN]
                              <-- comparison result --------
```

### 5.2 Cross-Channel State Exchange

The `cross_channel_state_t` structure is exchanged every 20 ms (cycle step 6):

```c
typedef struct {
    uint16_t speed_kmh_x10;              /* SPM output — validated speed */
    uint8_t  door_states[MAX_DOORS];     /* DSM output — per-door state enum */
    uint8_t  lock_states[MAX_DOORS];     /* DSM output — per-lock state */
    uint8_t  obstacle_flags[MAX_DOORS];  /* OBD output — per-door obstacle */
    uint8_t  fault_flags;                /* FMG output — bitmask */
    uint8_t  safety_decisions;           /* SKN output — interlock, safe state */
    uint16_t crc16;                      /* CRC-16 over all preceding bytes */
} cross_channel_state_t;
```

**Comparison rule**: If ANY field differs between Channel A and Channel B, OR if CRC-16
fails, SKN on both channels IMMEDIATELY asserts `safe_state_active` = 1.
This triggers SAFE_STATE on both channels within the same 20 ms cycle.

### 5.3 CRC-16 Protection Scope

**CRC-16 Polynomial (OI-FTA-003 resolution)**: All CRC-16 computations throughout the TDC
software SHALL use **CRC-16-CCITT, polynomial 0x1021** (also known as CRC-CCITT or
X.25 CRC), with **initial value 0xFFFF** and **no final XOR**.  
Polynomial 0x8005 (CRC-16/IBM) is **explicitly prohibited** in TDC software.

**Rationale**: Cross-channel SPI comparison (Channel A vs Channel B) requires both channels
to compute CRC-16 over `cross_channel_state_t` using the identical polynomial. If channels
use different polynomials, the CRC fields will always differ, causing a false cross-channel
mismatch and permanent safe state (OI-FTA-003, DOC-FTA-2026-001 §7.3).

All safety-critical data structures carry CRC-16 protection (REQ-SAFE-010):

| Structure | CRC-16 Applied | Polynomial | Checked by |
|-----------|---------------|------------|------------|
| `cross_channel_state_t` | Yes | **0x1021** | SKN at cycle step 6 |
| `tcms_speed_msg_t` | Yes | **0x1021** | TCI at receive |
| `door_status_msg_t` (CAN 0x201) | Yes | **0x1021** | TCI at transmit |
| Event log entry (`event_log_entry_t`) | Yes | **0x1021** | DGN at write and read |
| Safety-critical global variables | Periodic (every 100 ms) | **0x1021** | SKN memory integrity check |

---

## 7. SAFETY ARCHITECTURE

### 7.1 Safety Functions and Component Allocation

| Safety Function | ID | SIL | Primary Component | Supporting Component |
|-----------------|----|-----|-------------------|----------------------|
| Speed Interlock — inhibit open when moving | SF-001 | SIL 3 | SPM | SKN, TCI |
| Departure Interlock — all doors locked before departure | SF-002 | SIL 3 | SKN | DSM, TCI |
| Obstacle Detection and Reversal | SF-003 | SIL 3 | OBD | DSM, HAL |
| Safe State on Critical Fault | SF-004 | SIL 3 | SKN | FMG, all |
| Door Position Verification (2oo2) | SF-005 | SIL 3 | DSM | SKN, HAL |

### 7.2 Dual-Channel (2oo2) Architecture

The TDC safety architecture uses a dual-channel 2oo2 design. Both Channel A (MCU-A) and
Channel B (MCU-B) execute all SIL 3 safety functions independently:

- Each channel reads its own sensor inputs via independent HAL instances.
- Each channel independently evaluates speed interlock, obstacle detection, door states,
  and fault conditions.
- SKN on Channel A transmits its complete safety state to Channel B via SPI at cycle
  step 6. Channel B (SKN) independently computes its own safety state and compares.
- Any disagreement between the two channels immediately triggers SAFE_STATE on both.

**2oo2 Coverage**: This architecture provides:
1. Single-channel software fault detection (cross-channel mismatch → safe state)
2. Independent hardware sensor fault detection (2oo2 sensor voting within each channel)
3. CCF mitigation via formal code review and static analysis (CCF-001 in Hazard Log)

### 7.3 Safe State Definition and Entry

**Safe State** (REQ-SAFE-012, SF-004): All doors commanded to CLOSED_AND_LOCKED; door
opening inhibited; departure interlock de-asserted; motor PWM set to 0; TCMS alerted.

**Safe State entry triggers**:

| Trigger | Response Time | Authority | Filter |
|---------|---------------|-----------|--------|
| Cross-channel SPI mismatch — **safety-data disagreement** (speed, door state, lock state, obstacle, safety decisions differ) | Immediate (< 1 ms, within cycle) | SKN | **None — immediate** |
| Cross-channel SPI mismatch — **infrastructure fault** (CRC failure on SPI frame, SPI timeout, SPI hardware error) | ≤ 60 ms (3-cycle confirmation) | SKN | **3 consecutive cycles** (OI-FMEA-001 — see note below) |
| CRC-16 failure on any safety-critical structure (non-SPI) | Immediate | SKN | None — immediate |
| Speed interlock defeat (SPM detects) | Immediate | SKN via SPM | None |
| Watchdog timeout | Hardware reset (< 50 ms) | Hardware IWDG | None |
| Sensor 2oo2 disagreement (3 consecutive cycles) | ≤ 60 ms (3 × 20 ms) | SKN via DSM/FMG | 3 cycles |
| CAN speed timeout (> 200 ms) | ≤ 220 ms | SPM → SKN | None |
| Cross-channel software watchdog fault | ≤ 40 ms | Channel B SKN | None |
| Memory CRC mismatch (every 100 ms check) | ≤ 120 ms | SKN | None |

**OI-FMEA-001 SPI Transient Filter Note** (resolution of DOC-FMEA-2026-001 §4, SW-HAZ-011):
A transient SPI infrastructure fault (bit error, glitch, or short timeout) MUST NOT
trigger an immediate safe state. This prevents spurious passenger-trapping scenarios.
The filter applies **only** to SPI frame-level faults (CRC of the SPI physical frame,
SPI bus timeout, SPI controller error). It does **NOT** apply when the SPI frame
transfers successfully but the contained safety-data fields disagree — that is a
safety-data disagreement and triggers immediate safe state.

SPI transient filter algorithm (specified for SDS/SKN module, COMP-001):
```
spi_infra_fault_count = 0   /* persistent across cycles, cleared on successful exchange */

On SPI infrastructure fault (CRC error / timeout / HW error):
    spi_infra_fault_count++
    IF spi_infra_fault_count >= 3:
        ASSERT safe_state_active = 1   /* 3-consecutive-cycle confirmation */
    ELSE:
        retain previous cross_channel_state (use last known good)
        log WARN event to DGN

On successful SPI exchange with safety-data disagreement:
    spi_infra_fault_count = 0    /* reset infrastructure counter */
    ASSERT safe_state_active = 1 /* immediate — no filter */

On successful SPI exchange with data agreement:
    spi_infra_fault_count = 0    /* reset */
```

**Safe State is fail-closed**: Hardware locks are spring-loaded and fail-closed (locked)
without power (ASSUME-002). Safe state software command energizes solenoids to LOCKED
position. Loss of power inherently produces the safe state at hardware level.

### 7.4 Fault Detection Architecture

**Defence-in-depth** — multiple layers:

1. **Input validation** (every cycle): All sensor inputs validated for NULL, range, and
   plausibility before use. Out-of-range or NULL → fail-safe value substituted.

2. **2oo2 sensor voting** (every cycle): Position and lock sensors voted per door.
   Disagreement → UNKNOWN/conservative state.

3. **Data structure CRC-16** (every cycle / every 100 ms): All safety-critical structures
   carry CRC-16. Mismatch → immediate safe state.

4. **Stack canary** (every cycle): Fixed canary values at stack boundaries checked by
   SKN. Corruption → safe state.

5. **Memory integrity check** (every 100 ms): ROM CRC-16 and RAM CRC-16 of safety-
   critical globals checked by SKN.

6. **Cross-channel comparison** (every cycle): All safety decisions compared between
   Channel A and Channel B via SPI.

7. **Hardware watchdog** (50 ms timeout, refreshed at 40 ms): Independent of software.
   If any task overruns and prevents watchdog refresh, hardware resets DCU.

8. **Communication timeout** (CAN 200 ms, DDU 40 ms): Loss of CAN speed data →
   assume moving → inhibit door open.

### 7.5 No Dynamic Memory Allocation

**EN 50128 Table A.4 / REQ-SAFE-017 / MISRA C:2012 Rule 21.3 — No dynamic allocation
(mandatory SIL 2+)**

The TDC software MUST NOT use `malloc`, `calloc`, `realloc`, or `free` at any point.
All data structures, buffers, arrays, and stacks are statically declared at compile time.

This applies to:
- All component state variables: `static` global or module-level arrays
- CAN receive/transmit mailboxes: static array of fixed size
- Event log circular buffer: `static event_log_entry_t log[1024]`
- Cross-channel SPI buffers: `static cross_channel_state_t ch_tx, ch_rx`
- Door state arrays: `static uint8_t door_states[MAX_DOORS]`

Rationale: Dynamic memory allocation introduces non-deterministic execution time,
fragmentation, and potential heap corruption — all incompatible with SIL 3 determinism
requirements.

### 7.6 Cyclomatic Complexity Limits

**EN 50128 SIL 3 constraint (mandatory): Cyclomatic complexity ≤ 10 per function.**

This is an architectural constraint that DES enforces in the component design (item 15)
and IMP must adhere to during implementation (item 18). The design is structured so that
no function requires more than 10 independent paths:

- All FSM transition functions use look-up tables or switch statements with ≤ 10 cases.
- Complex logic (e.g., 2oo2 voting for 4 sensors) is decomposed into separate
  sub-functions, each with complexity ≤ 10.
- No recursive functions are used (highly recommended at SIL 3–4).
- No function pointers in safety-critical paths (highly recommended at SIL 3–4).

IMP shall run static analysis (PC-lint or Polyspace) to verify complexity ≤ 10 per
function before submitting code for VER review.

---

## 8. TABLE A.3 COMPLIANCE

**EN 50128 Table A.3 — Architecture Techniques — SIL 3 Application:**

| # | Technique/Measure | SIL 3–4 | Applied | Evidence |
|---|-------------------|---------|---------|---------|
| 1 | Structured Methodology | **M** | **Yes** — Yourdon SASD | Section 2 |
| 2 | Defensive Programming | HR | Yes | SEEA guards in §4, stack canaries in §6.4 |
| 3 | Fault Detection and Diagnosis | HR | Yes | §6.4 multi-layer fault detection |
| 4 | Information Encapsulation | HR | Yes | Each component exposes defined API only (SIS item 11) |
| 5 | Modelling | HR | Yes | DSM FSM state model (§4.5), data flow diagrams (§5) |
| 7 | Fully Defined Interface | HR | Yes | All interfaces typed; pre/postconditions in SIS (item 11) |
| 8 | Structured Design | HR | Yes | SASD applied throughout (Section 2) |
| 9 | Functional Cohesion | HR | Yes | Each component has single responsibility (§4.1) |
| 11 | Software Modules with Low Coupling | HR | Yes | Components communicate via defined APIs only |
| 16 | Design and Coding Standards | HR | Yes | MISRA C:2012 mandatory (SIL 3) |
| 17 | Software Design Notations | HR | Yes | Block diagram (§3.1), FSM (§4.5), data flow (§5) |
| 19 | **Modular Approach** | **M** | **Yes** | 8 cohesive components, §4 |
| 20 | Schedulability Analysis | HR | Yes | WCET ≤ 16 ms; 4 ms margin (REQ-PERF-001) |
| 21 | Time-triggered Architecture | HR | Yes | Static cyclic executive, 20 ms fixed cycle |
| 22 | Memorisation of Data/Program Flow | HR | Yes | CRC-16 on all safety data; stack canary |
| 23 | Failure Assertion Programming | HR | Yes | `error_t` return codes; fail-safe substitution |

**Items not applied and rationale**:
- Entry 6 (Formal Methods): Not applied at architecture level. Structured walkthroughs
  of critical FSM transitions applied instead per CCF-001 mitigation. May be added by
  DES at component design (item 15) for SKN departure interlock logic.
- Entry 12 (Event-driven): Not primary architecture. ISR used only for obstacle sensor
  and CAN receive (bounded, deterministic). Time-triggered architecture is primary.

---

## 9. REQUIREMENTS → ARCHITECTURE TRACEABILITY

**EN 50128 §7.3 — Traceability mandatory at SIL 3–4 (TRACEABILITY.md Rule T5).**

Every SRS requirement is allocated to at least one architectural component. No orphan
modules. The full RTM is maintained in `activities/traceability.yaml`.

### 9.1 SRS Functional Requirements → Components

| Requirement | Description (brief) | Primary Component | Supporting |
|-------------|---------------------|-------------------|-----------|
| REQ-FUN-001 | Door opening command processing | DSM | SPM, SKN, TCI |
| REQ-FUN-002 | Door opening completion detection (2oo2) | DSM | HAL |
| REQ-FUN-003 | Door opening timeout fault | DSM | FMG |
| REQ-FUN-004 | Door closing command processing | DSM | OBD, TCI |
| REQ-FUN-005 | Door close-and-lock completion (2oo2 × 2oo2) | DSM | HAL, SKN |
| REQ-FUN-006 | Door closing timeout fault | DSM | FMG |
| REQ-FUN-007 | Door obstacle retry logic | OBD | DSM, FMG |
| REQ-FUN-008 | Automatic door lock engagement | DSM | HAL |
| REQ-FUN-009 | Departure interlock signal | SKN | TCI (CAN 0x200) |
| REQ-FUN-010 | Door lock maintenance while moving | DSM | SPM, SKN |
| REQ-FUN-011 | Operational mode FSM | DSM | FMG, TCI |
| REQ-FUN-012 | Mode transition authorization | DSM | TCI |
| REQ-FUN-013 | Selective door disablement mode | FMG | DSM, TCI |
| REQ-FUN-014 | Diagnostic mode conditions | DSM | SPM |
| REQ-FUN-015 | Continuous door position monitoring | DSM | HAL |
| REQ-FUN-016 | Door status reporting to TCMS | TCI | DSM |
| REQ-FUN-017 | Continuous fault monitoring | FMG | all |
| REQ-FUN-018 | Fault event logging | DGN | FMG |

### 9.2 SRS Safety Requirements → Components

| Requirement | Description (brief) | SIL | Primary Component |
|-------------|---------------------|-----|-------------------|
| REQ-SAFE-001 | Inhibit door open when speed > 5 km/h | SIL 3 | SPM → DSM gate |
| REQ-SAFE-002 | Dual-channel speed confirmation (2oo2) | SIL 3 | SKN (cross-channel) |
| REQ-SAFE-003 | CAN timeout → assume moving → inhibit | SIL 3 | SPM, TCI |
| REQ-SAFE-004 | Obstacle detection ≤ 20 ms poll; reversal ≤ 100 ms | SIL 3 | OBD |
| REQ-SAFE-005 | Obstacle sensor fault → door re-opens | SIL 3 | OBD → DSM |
| REQ-SAFE-006 | Motor current > 150 N equivalent → reversal | SIL 3 | OBD → HAL ADC |
| REQ-SAFE-007 | 2oo2 sensor agreement for LOCKED state | SIL 3 | DSM |
| REQ-SAFE-008 | All-doors-locked signal withheld until all DSMs confirm | SIL 3 | SKN → TCI |
| REQ-SAFE-009 | Cross-channel lock state verification every 20 ms | SIL 3 | SKN (SPI) |
| REQ-SAFE-010 | CRC-16 on all safety-critical data structures | SIL 3 | All (SKN oversight) |
| REQ-SAFE-011 | Position sensor timeout (100 ms) → assume door open | SIL 3 | DSM, HAL |
| REQ-SAFE-012 | Safe state trigger requires 2oo2 channel confirmation | SIL 2 | SKN, FMG |
| REQ-SAFE-013 | Selective disablement: speed interlock remains active | SIL 2 | FMG → SPM |
| REQ-SAFE-014 | Hardware watchdog 50 ms → safe state both channels | SIL 3 | HAL (IWDG) |
| REQ-SAFE-015 | Cross-channel software watchdog every 20 ms | SIL 3 | SKN, Channel B |
| REQ-SAFE-016 | CRC-16 on CAN messages; CRC fail = reject + timeout | SIL 3 | TCI |
| REQ-SAFE-017 | No dynamic memory allocation (MISRA 21.3) | SIL 3 | All (architectural) |
| REQ-SAFE-018 | Memory integrity check at boot + every 100 ms | SIL 3 | SKN |
| REQ-SAFE-019 | Emergency release debounce ≥ 60 ms; alert TCMS ≤ 100 ms | SIL 2 | DSM → TCI |
| REQ-SAFE-020 | Emergency release latched until maintenance reset | SIL 2 | DSM |
| REQ-SAFE-021 | Selective disablement: TCMS authorization required; logged | SIL 2 | FMG, DGN |

### 9.3 SRS Performance Requirements → Components

| Requirement | Description (brief) | Primary Component |
|-------------|---------------------|-------------------|
| REQ-PERF-001 | WCET ≤ 16 ms per 20 ms cycle | Scheduler + all |
| REQ-PERF-002 | Speed interlock response ≤ 100 ms | SPM → DSM |
| REQ-PERF-003 | Obstacle reversal ≤ 150 ms | OBD → HAL PWM |
| REQ-PERF-004 | Command-to-motor latency ≤ 200 ms | DSM → HAL PWM |
| REQ-PERF-005 | TCMS locked status TX ≤ 100 ms | SKN → TCI |
| REQ-PERF-006 | Sensor fault detection ≤ 100 ms | DSM, FMG |
| REQ-PERF-007 | CAN communication fault ≤ 200 ms | TCI, SPM |
| REQ-PERF-008 | CPU utilization ≤ 80% | Scheduler (all) |
| REQ-PERF-009 | SRAM ≤ 800 KB (static only) | All (architectural) |
| REQ-PERF-010 | Flash ≤ 1600 KB | All (architectural) |

### 9.4 SRS Interface Requirements → Components

| Requirement | Description (brief) | Primary Component |
|-------------|---------------------|-------------------|
| REQ-INT-001 | Door motor PWM interface | HAL |
| REQ-INT-002 | Door position sensor interface | HAL → DSM |
| REQ-INT-003 | Obstacle sensor interface (interrupt) | HAL → OBD |
| REQ-INT-004 | Door lock actuator interface | HAL → DSM |
| REQ-INT-005 | Lock position sensor interface | HAL → DSM |
| REQ-INT-006 | Watchdog hardware interface | HAL |
| REQ-INT-007 | TCMS CAN receive | TCI → SPM, DSM |
| REQ-INT-008 | TCMS CAN transmit | TCI |
| REQ-INT-009 | DDU RS-485 interface | HAL → DSM |
| REQ-INT-010 | Cross-channel SPI interface | HAL → SKN |
| REQ-INT-011 | Emergency release detection | DSM → TCI |
| REQ-INT-012 | Driver control panel interface | HAL → DSM |
| REQ-INT-013 | Diagnostics port interface | DGN |

### 9.5 Hazard Log → Component Traceability

| Hazard ID | Hazard (brief) | SIL | Primary Component | Safety Requirements |
|-----------|---------------|-----|-------------------|---------------------|
| SW-HAZ-001 | Door opens while moving | SIL 3 | SPM, SKN | REQ-SAFE-001, 002, 003 |
| SW-HAZ-002 | Door closes on passenger | SIL 3 | OBD | REQ-SAFE-004, 005, 006 |
| SW-HAZ-003 | False door lock indication | SIL 3 | DSM, SKN | REQ-SAFE-007, 008, 009 |
| SW-HAZ-004 | Loss of door position indication | SIL 3 | DSM | REQ-SAFE-009, 010, 011 |
| SW-HAZ-005 | Spurious safe state | SIL 2 | FMG, SKN | REQ-SAFE-012, 013 |
| SW-HAZ-006 | Watchdog failure | SIL 3 | HAL, SKN | REQ-SAFE-014, 015 |
| SW-HAZ-007 | CAN speed data loss | SIL 3 | TCI, SPM | REQ-SAFE-003, 016 |
| SW-HAZ-008 | Memory corruption | SIL 3 | SKN (all) | REQ-SAFE-010, 017, 018 |
| SW-HAZ-009 | Emergency release mishandled | SIL 2 | DSM, TCI | REQ-SAFE-019, 020 |
| SW-HAZ-010 | Selective disablement misuse | SIL 2 | FMG | REQ-SAFE-013, 021 |
| SW-HAZ-011 | SPI transient fault → denial-of-safe-operation (passenger trapping) | SIL 2 | SKN | OI-FMEA-001 mitigation: 3-cycle SPI infra filter (§7.3) |

---

## 10. MEMORY ALLOCATION STRATEGY

**Platform**: STM32H743, 1 MB SRAM per MCU, 2 MB Flash per MCU (bare-metal)

**Allocation principle**: 100% static. All allocations determined at compile-link time.

| Memory Region | Contents | Estimated Size |
|---------------|---------|---------------|
| `.text` (Flash) | Program code (all components) | ≤ 512 KB |
| `.rodata` (Flash) | Constants, lookup tables, CAN message definitions | ≤ 64 KB |
| `.data` (SRAM) | Initialized global variables | ≤ 32 KB |
| `.bss` (SRAM) | Uninitialized globals (zero-initialized at boot) | ≤ 64 KB |
| Stack (SRAM) | Fixed-size stack per task (main + ISR stacks) | ≤ 64 KB |
| Event log buffer (SRAM) | `event_log_entry_t log[1024]` | ≤ 8 KB |
| CAN mailboxes (SRAM) | Static RX/TX mailbox arrays | ≤ 4 KB |
| SPI cross-channel buffers (SRAM) | `cross_channel_state_t ch_tx, ch_rx` | ≤ 64 bytes |
| **Total estimated SRAM** | | **≤ 180 KB** (well within 800 KB limit) |

**Stack guard**: Fixed-size canary values at stack top and bottom, checked by SKN
every cycle. Stack overflow causes safe state entry and event log entry.

**No heap**: `malloc`, `calloc`, `realloc`, `free` MUST NOT appear anywhere in the
TDC software binary. This is verified by static analysis (VER) per REQ-SAFE-017.

---

## 11. SCHEDULABILITY ANALYSIS

**EN 50128 Table A.3 Entry 20 — Schedulability Analysis: HR at SIL 3**

Execution model: Static cyclic executive with 20 ms period (50 Hz).

WCET budget allocation per cycle step (REQ-PERF-001: WCET ≤ 16 ms):

| Step | Component | Task | WCET Budget |
|------|-----------|------|-------------|
| 1 | SKN | Cross-channel gate check + safe state | 1.0 ms |
| 2 | SPM | Speed data validation + interlock update | 0.5 ms |
| 3 | OBD | Obstacle sensor poll + reversal logic | 0.5 ms |
| 4 | DSM | Door FSM × N doors + 2oo2 voting | 2.0 ms |
| 5 | FMG | Fault flag aggregation + escalation | 0.5 ms |
| 6 | SPI | Cross-channel exchange + comparison | 1.0 ms |
| 7 | HAL | Actuator output writes | 1.0 ms |
| 8 | TCI | CAN transmit (all messages) | 2.0 ms |
| 9 | HAL | RS-485 DDU exchange × N DDUs | 4.0 ms |
| 10 | HAL | Watchdog refresh | 0.1 ms |
| 11 | DGN | Event log write (non-safety, deferrable) | 2.0 ms |
| — | Margin | Unallocated | **1.4 ms** |
| **Total** | | | **≤ 16.1 ms** |

**Note**: RS-485 DDU step (step 9) is the largest WCET consumer due to multi-drop
polling of N DDUs. IMP shall implement with DMA-assisted UART to minimize CPU time.
Actual WCET must be measured on target hardware per REQ-PERF-001.

**ISR latency budget**:
- Obstacle sensor ISR: ≤ 1 ms (triggers `OBD_ObstacleISR` only — no logic)
- CAN receive ISR: ≤ 0.5 ms (copies to static mailbox only — no processing in ISR)
- Timer ISR (20 ms tick): ≤ 0.1 ms (sets cycle flag only)

---

## 12. DESIGN CONSTRAINTS SUMMARY

The following constraints are mandatory for all phases downstream of this SAS:

| Constraint | Rule | Applies To |
|-----------|------|-----------|
| No dynamic memory allocation | MISRA C:2012 Rule 21.3; REQ-SAFE-017 | All components (IMP) |
| Cyclomatic complexity ≤ 10 | EN 50128 SIL 3 | All functions (IMP, verified by VER) |
| No recursion | HR SIL 3–4 | All components (IMP) |
| No function pointers in safety-critical paths | HR SIL 3–4 | SKN, SPM, OBD, DSM, FMG (IMP) |
| Fixed-width integer types only | MISRA C:2012 | All components (IMP) |
| All HAL functions return `error_t` | Architecture rule | HAL (IMP) |
| All HAL return values must be checked | Architecture rule | All callers of HAL (IMP) |
| CRC-16 on all safety-critical structures | REQ-SAFE-010 | All components (IMP) |
| `safe_state_active` is write-once per cycle | Architecture rule | SKN only (DES/IMP) |
| Departure interlock set only by SKN | Architecture rule | SKN only (DES/IMP) |
| Door state set only by DSM | Architecture rule | DSM only (DES/IMP) |
| Speed interlock flag set only by SPM | Architecture rule | SPM only (DES/IMP) |

---

## 13. OPEN ISSUES AND DEFERRED DECISIONS

| Issue ID | Description | Resolution Owner | Target Phase |
|----------|-------------|------------------|-------------|
| OI-SAS-001 | MAX_DOORS value: SRS uses N doors; exact count TBD from System Architecture | PM → DES | Phase 3 (SDS) |
| OI-SAS-002 | RS-485 DDU protocol specification (frame format, addressing) — referenced but not fully defined in SRS | PM → REQ | Phase 3 (SIS item 11) |
| OI-SAS-003 | Operational mode FSM complete transition table — SRS §REQ-FUN-011 provides 4 modes; full transition guard conditions to be specified in SDS (item 10) | DES | Phase 3 (SDS) |
| OI-SAS-004 | FMEA on software architecture — Phase 3 SAF activity per Hazard Log §1.1 — pending SAF Phase 3 update to DOC-FMEA-2026-001 | SAF | Phase 3 |
| ~~OI-SAS-005~~ | ~~CRC-16 polynomial selection~~ | **CLOSED in v0.2** — CRC-16-CCITT (0x1021) unified for all TDC software. See §5.3. | — |
| OI-SAS-006 | SW-HAZ-011 (SPI transient → denial-of-safe-operation, SIL 2) — new hazard from DOC-FMEA-2026-001. SPI transient filter algorithm specified in §7.3. Hazard Log update (DOC-HAZLOG-2026-001) is a SAF action. | SAF | Phase 3 |

---

## APPENDIX A: SAFETY REQUIREMENTS ALLOCATION SUMMARY

**All 21 REQ-SAFE-xxx requirements from DOC-HAZLOG-2026-001 are allocated:**

| REQ-SAFE | SIL | Component | Status |
|----------|-----|-----------|--------|
| REQ-SAFE-001 | SIL 3 | SPM | ✅ Allocated (§4.3, §8.2) |
| REQ-SAFE-002 | SIL 3 | SKN | ✅ Allocated (§4.2, §6.2) |
| REQ-SAFE-003 | SIL 3 | SPM, TCI | ✅ Allocated (§4.3, §4.7) |
| REQ-SAFE-004 | SIL 3 | OBD | ✅ Allocated (§4.4, §8.2) |
| REQ-SAFE-005 | SIL 3 | OBD → DSM | ✅ Allocated (§4.4) |
| REQ-SAFE-006 | SIL 3 | OBD → HAL ADC | ✅ Allocated (§4.4) |
| REQ-SAFE-007 | SIL 3 | DSM | ✅ Allocated (§4.5) |
| REQ-SAFE-008 | SIL 3 | SKN → TCI | ✅ Allocated (§4.2) |
| REQ-SAFE-009 | SIL 3 | SKN (SPI) | ✅ Allocated (§4.2, §6.2) |
| REQ-SAFE-010 | SIL 3 | All (SKN oversight) | ✅ Allocated (§5.3, §6.4) |
| REQ-SAFE-011 | SIL 3 | DSM, HAL | ✅ Allocated (§4.5) |
| REQ-SAFE-012 | SIL 2 | SKN, FMG | ✅ Allocated (§4.2, §4.6) |
| REQ-SAFE-013 | SIL 2 | FMG → SPM | ✅ Allocated (§4.6) |
| REQ-SAFE-014 | SIL 3 | HAL (IWDG) | ✅ Allocated (§4.9) |
| REQ-SAFE-015 | SIL 3 | SKN, Channel B | ✅ Allocated (§4.2, §6.2) |
| REQ-SAFE-016 | SIL 3 | TCI | ✅ Allocated (§4.7) |
| REQ-SAFE-017 | SIL 3 | All (architectural) | ✅ Allocated (§6.5) |
| REQ-SAFE-018 | SIL 3 | SKN | ✅ Allocated (§4.2, §6.4) |
| REQ-SAFE-019 | SIL 2 | DSM → TCI | ✅ Allocated (§4.5) |
| REQ-SAFE-020 | SIL 2 | DSM | ✅ Allocated (§4.5) |
| REQ-SAFE-021 | SIL 2 | FMG, DGN | ✅ Allocated (§4.6, §4.8) |

**Traceability completeness**: 21/21 REQ-SAFE-xxx allocated (100%).
**No orphan modules**: All 8 components trace to ≥1 SRS requirement or hazard.

---

## APPENDIX B: SEEA MITIGATION SUMMARY

All SEEA findings from DOC-HAZLOG-2026-001 §5 are addressed at architecture level:

| Module | Fault Mode (SEEA) | Architecture Mitigation | Component |
|--------|-------------------|-----------------------|-----------|
| SPM | NULL pointer dereference | NULL guard before buffer access; fail-safe = HIGH speed | SPM §4.3 |
| SPM | Integer overflow (speed) | Range check 0–3000; out-of-range → UNKNOWN | SPM §4.3 |
| SPM | Stale data (> 200 ms) | Timestamp check; stale → assume moving | SPM §4.3 |
| DSM | State machine stuck-at | Per-state max dwell timeout → safe state | DSM §4.5 |
| DSM | Uninitialized lock status | Initialize to LOCKED_UNKNOWN at startup | DSM §4.5 |
| DSM | Array out-of-bounds | Bounds check 0 ≤ door_id < MAX_DOORS | DSM §4.5 |
| OBD | NULL pointer | NULL → OBSTACLE_DETECTED (fail-safe) | OBD §4.4 |
| OBD | Integer overflow (force) | Saturating arithmetic; capped at MAX_FORCE | OBD §4.4 |
| OBD | Timing fault | Execution time monitoring; overrun → safe state | OBD §4.4 |
| FMG | State machine stuck-at | Max safe-state dwell; driver override with TCMS auth | FMG §4.6 |
| FMG | Uninitialized fault counter | Initialize to 0 at startup and after recovery | FMG §4.6 |
| SKN | Division by zero | Non-zero denominator guard before all divisions | SKN §4.2 |
| SKN | Uninitialized departure flag | Initialize to LOCKED_UNKNOWN at startup | SKN §4.2 |
| CAN-DRV | NULL pointer (receive buffer) | NULL guard on receive; safety messages never dropped | TCI §4.7 |
| CAN-DRV | Sequence counter overflow | Modulo-256 delta check | TCI §4.7 |

---

**END OF SOFTWARE ARCHITECTURE SPECIFICATION**

*Document ID*: DOC-SAS-2026-001 v0.2 DRAFT  
*Date*: 2026-04-02  
*Author*: Software Designer (DES)  
*Project*: TDC (Train Door Control System), SIL 3  
*Changes in v0.2*: CRC-16-CCITT (0x1021) unification (OI-FTA-003); SPI transient filter 3-cycle confirmation (OI-FMEA-001); SW-HAZ-011 traceability; OI-SAS-005 closed.  
*Next action*: Submit to PM for QUA review routing (DES does not contact QUA directly)
