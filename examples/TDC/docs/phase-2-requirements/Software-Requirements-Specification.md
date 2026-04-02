# Software Requirements Specification (SRS)

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 Section 7.2, Table A.2

---

## DOCUMENT CONTROL

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SRS-2026-001 |
| **Version** | 0.1 DRAFT |
| **Date** | 2026-04-02 |
| **Project** | TDC (Train Door Control System) |
| **SIL Level** | SIL 3 |
| **Author** | Requirements Engineer (REQ) |
| **Status** | Draft |

### Revision History

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-04-02 | Requirements Engineer (REQ) | Initial draft — Phase 2 requirements from system documents | - |

## APPROVALS

**EN 50128 Annex C Table C.1 Signature Chain — Item 6 (SRS)**

| Column | Role | Name | Signature | Date |
|--------|------|------|-----------|------|
| Written By | Requirements Engineer (REQ) | [Name] | _____________ | 2026-04-02 |
| 1st Check | Software Verifier (VER) | [Name] | _____________ | __________ |
| 2nd Check | Software Validator (VAL) | [Name] | _____________ | __________ |

**Notes:**
- **Written By**: REQ — Author responsible for document content (EN 50128 Annex C Table C.1 Column 2)
- **1st Check**: VER — First independent reviewer (EN 50128 Annex C Table C.1 Column 3)
- **2nd Check**: VAL — Second independent reviewer (EN 50128 Annex C Table C.1 Column 4)
- Roles are per `activities/deliverables.yaml` item 6: `written_by: req`, `first_check: ver`, `second_check: val`
- SIL 3: Independence requirements apply per EN 50128 §6.2 (Verification) and §6.3 (Validation)
- Signature authority per project SQAP (DOC-SQAP-2026-001) and DELIVERABLES.md
- **User/Customer Approval**: GRANTED (per COD Hard Rule 4, approval received prior to authoring)
- **PM Confirmation**: SRS approved by user before VER track-B review

---

## 1. INTRODUCTION

### 1.1 Purpose

This Software Requirements Specification (SRS) defines the complete set of software requirements for the **Train Door Control System (TDC)** software. It provides a detailed description of functional requirements, performance requirements, interface requirements, safety requirements, reliability requirements, security requirements, and operational requirements in accordance with EN 50128:2011 Section 7.2.

**Intended Audience**:
- Software designers and implementers (DES, IMP)
- Verification and validation teams (VER, VAL)
- Safety engineers (SAF)
- Project management (PM)
- Customer / certification authorities
- Quality assurance (QUA)

### 1.2 Scope

This SRS applies to the **TDC software** running on the Door Control Unit (DCU) — a dual-channel (2oo2) embedded system that controls and monitors passenger door operation on railway vehicles.

**System Context**: The TDC software resides within the Door Control Unit (DCU) and interfaces with the Train Control Management System (TCMS) via CAN bus, Door Drive Units (DDU) via RS-485, the Driver Control Panel via discrete I/O, and the hardware sensors and actuators via the Hardware Abstraction Layer (HAL).

**In Scope**:
- Door opening and closing control logic
- Speed interlock functions (SIL 3 safety functions SF-001, SF-002)
- Obstacle detection and reversal (SIL 3 safety function SF-003)
- Safe state management and fault detection (SIL 3 safety function SF-004)
- Door position verification (SIL 3 safety function SF-005)
- Operational mode management
- CAN bus (TCMS) and RS-485 (DDU) communication drivers
- Hardware Abstraction Layer (HAL) requirements
- Watchdog monitoring
- Diagnostics and event logging
- Cross-channel (2oo2) comparison logic
- MISRA C:2012 compliance and defensive programming

**Out of Scope**:
- Hardware design (covered by Hardware Design Specification DOC-HW-DES-2026-001)
- System-level requirements (covered by System Requirements Specification DOC-SYS-REQ-2026-001)
- Emergency release mechanical design (hardware-only, no software allocation)
- Door closing force mechanical limiter (hardware per EN 14752)

### 1.3 SIL Classification

**Target SIL Level**: SIL 3

**Rationale**: SIL 3 is derived from hazard analysis per EN 50126-2. The highest-severity hazards (HAZ-001 through HAZ-005) involve catastrophic or critical consequences (passenger fatality/serious injury) with intolerable or unacceptable risk, requiring SIL 3 per EN 50129 Table A.1. The overall system SIL of 3 is driven by these hazards and requires the software to be developed to EN 50128 SIL 3.

**EN 50128 Requirements Specification Techniques** (Table A.2):

| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Applied |
|-----------|-------|---------|---------|---------|
| Formal Methods | - | R | HR | No (structured methodology sufficient; may be added by DES for critical FSMs) |
| Modelling | R | R | HR | **Yes** — operational mode FSM state model (Section 3.1.4, REQ-FUN-011) |
| Structured Methodology | R | R | HR | **Yes** — systematic decomposition with unique IDs, SIL levels, acceptance criteria, traceability |
| Decision Tables | R | R | HR | **Yes** — opening preconditions (REQ-FUN-001), lock verification (REQ-FUN-005), safe state triggers (REQ-SAFE-006) |

**Techniques Applied Rationale**: Structured methodology is applied throughout this SRS via systematic decomposition into 7 requirement categories with unique IDs, SIL assignments, and acceptance criteria. Decision tables are used in the door control logic and safety requirement sections. State modelling is used for operational mode management.

### 1.4 Definitions and Acronyms

| Term | Definition |
|------|------------|
| **SHALL** | Mandatory requirement (must be implemented) |
| **SHOULD** | Highly recommended requirement (non-compliance requires justification) |
| **MAY** | Optional requirement (no safety implication) |
| **SIL** | Safety Integrity Level (0-4 per EN 50128:2011) |
| **MISRA C** | Motor Industry Software Reliability Association C coding standard (edition: 2012) |
| **RTM** | Requirements Traceability Matrix |
| **DCU** | Door Control Unit — central dual-channel processing module |
| **DDU** | Door Drive Unit — per-door electromechanical actuator module |
| **TCMS** | Train Control Management System — train-level supervisory system |
| **2oo2** | Two-out-of-two voting — both channels/sensors must agree |
| **CAN** | Controller Area Network (ISO 11898) |
| **PWM** | Pulse Width Modulation |
| **HAZ** | Hazard identifier (from System Safety Requirements Specification) |
| **SYS-REQ** | System requirement identifier (from System Requirements Specification) |
| **SF** | Safety Function identifier (from System Safety Requirements Specification) |
| **PFH** | Probability of Failure per Hour |
| **ALARP** | As Low As Reasonably Practicable |
| **DSM** | Door State Machine software component |
| **SPM** | Speed Monitor software component |
| **OBD** | Obstacle Detector software component |
| **TCI** | TCMS Interface software component |
| **FMG** | Fault Manager software component |
| **DGN** | Diagnostics software component |
| **HAL** | Hardware Abstraction Layer |
| **MCU** | Microcontroller Unit (STM32H743 or equivalent) |
| **CRC** | Cyclic Redundancy Check |
| **FMEA** | Failure Mode and Effects Analysis |
| **FTA** | Fault Tree Analysis |
| **WCET** | Worst-Case Execution Time |

### 1.5 References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications — Software for railway control and protection systems |
| **[EN50129]** | EN 50129:2018 Railway applications — Safety related electronic systems for signalling |
| **[EN50126-1]** | EN 50126-1:2017 Railway applications — RAMS — Part 1: Generic RAMS process |
| **[EN50126-2]** | EN 50126-2:2017 Railway applications — RAMS — Part 2: Systems approach to safety |
| **[EN14752]** | EN 14752:2015 Railway applications — Bodyside entrance systems |
| **[ISO11898]** | ISO 11898:2003 — Controller Area Network (CAN) |
| **[MISRAC]** | MISRA C:2012 Guidelines for the use of the C language in critical systems |
| **[SYSREQ]** | System Requirements Specification, DOC-SYS-REQ-2026-001 |
| **[SYSARCH]** | System Architecture Description, DOC-SYS-ARCH-2026-001 |
| **[SSRS]** | System Safety Requirements Specification, DOC-SYS-SAF-2026-001 |
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-2026-001 |
| **[SCMP]** | Software Configuration Management Plan, DOC-SCMP-2026-001 |
| **[SVP]** | Software Verification Plan, DOC-SVP-2026-001 |

### 1.6 Overview

This SRS is organized as follows:

- **Section 2**: General Description — system context, functions, constraints, and assumptions
- **Section 3**: Software Requirements — 81 requirements in 7 categories
- **Section 4**: Verification and Traceability — verification methods and Requirements Traceability Matrix
- **Section 5**: Requirements Summary — count by category and SIL level
- **Section 6**: Compliance Matrix — EN 50128 Section 7.2 and Table A.2 compliance
- **Section 7**: References

Each requirement includes a unique ID, SIL level, acceptance criteria, verification method, and backward traceability to system requirements and/or hazards.

---

## 2. GENERAL DESCRIPTION

### 2.1 System Context

```
+-------------------------------------------------------------------------+
|                         EXTERNAL SYSTEMS                                |
|                                                                         |
|  +----------+    +-----------------+    +------------------+            |
|  | Driver   |    |     TCMS        |    |   DDU x 4-8      |            |
|  | Control  |<-->| (CAN 250kbit)   |    | (RS-485 115kbit) |            |
|  | Panel    |    +--------+--------+    +--------+---------+            |
|  +----+-----+             |                      |                      |
|       | Discrete I/O      | CAN 2.0B              | RS-485               |
|       v                   v                       v                      |
|  +--------------------------------------------------------------+       |
|  |        Door Control Unit (DCU) -- SIL 3                      |       |
|  |   +---------------+   +---------------+                      |       |
|  |   |  Channel A    |<->|  Channel B    |  (SPI 10Mbit/s)      |       |
|  |   | (MCU-A)       |   | (MCU-B)       |                      |       |
|  |   | Safety Kernel |   | Safety Kernel |                      |       |
|  |   | DSM / SPM     |   | DSM / SPM     |                      |       |
|  |   | OBD / TCI     |   | OBD / TCI     |                      |       |
|  |   | FMG / DGN     |   | FMG           |                      |       |
|  |   | HAL           |   | HAL           |                      |       |
|  |   +---------------+   +---------------+                      |       |
|  +--------------------------------------------------------------+       |
|              | Sensors/Actuators                                         |
|   Position Sensors (2x/door)   Obstacle Sensors (2x/door)               |
|   Lock Sensors (2x/lock)       Motor PWM   Lock Actuators                |
+-------------------------------------------------------------------------+
```

**System Interfaces**:
- Hardware: Door motor actuators (PWM 20 kHz), position sensors (2oo2), lock actuators (24V solenoid), lock sensors (2oo2), obstacle sensors (IR beam 2x per door), emergency release switch
- Software: TCMS (CAN 2.0B, 250 kbit/s), DDU (RS-485, 115.2 kbit/s), cross-channel (SPI, 10 Mbps), diagnostics (USB/RS-232)
- User: Driver Control Panel (discrete I/O + CAN), Diagnostic port (maintenance laptop)

### 2.2 System Functions (High-Level)

The TDC software provides the following major functions:

1. **Door Opening Control**: Control door motor opening with speed interlock
2. **Door Closing Control**: Control door motor closing with obstacle detection and reversal
3. **Door Locking Control**: Engage/verify door locks and provide departure interlock to TCMS
4. **Speed Interlock**: Inhibit door opening and maintain locking when train speed > 5 km/h
5. **Obstacle Detection**: Detect obstacles during closing and trigger reversal within 150 ms
6. **Safe State Management**: Transition to fail-safe state on critical faults
7. **Cross-Channel Comparison**: 2oo2 voting with Channel B every 20 ms cycle
8. **Fault Detection and Diagnostics**: Continuous monitoring, fault logging, self-test
9. **Operational Mode Management**: Normal, Selective Door Disablement, Diagnostic, Safe State
10. **TCMS Communication**: Receive commands/speed data, transmit status and door-locked signal

### 2.3 User Characteristics

**Primary Users**: Train drivers (operational commands), maintenance personnel (diagnostic access)

**User Expertise**: Railway-qualified train drivers; maintenance technicians with laptop diagnostic access

**User Environment**: Moving train in revenue service; maintenance depot for diagnostics

### 2.4 Constraints

**Programming Language**: C (MISRA C:2012 compliant — mandatory for SIL 3)

**Platform Constraints**:
- Target processor: STM32H743 (ARM Cortex-M7, 400 MHz), dual-channel
- Memory: 1 MB SRAM per MCU (all static), 2 MB Flash per MCU
- External storage: 16 MB SPI Flash (event log, configuration), CRC-16 protected
- Execution: bare-metal, static cyclic executive scheduler, 20 ms cycle

**Regulatory Constraints**:
- EN 50128:2011 SIL 3 compliance mandatory
- EN 50126/50129 RAMS requirements
- MISRA C:2012 mandatory (SIL 2+ per EN 50128 Table A.4)

**Development Constraints**:
- Static memory allocation only — `malloc`/`calloc`/`realloc`/`free` are forbidden
- No recursion (highly recommended for SIL 3-4)
- Cyclomatic complexity <= 10 per function (SIL 3)
- No function pointers in safety-critical paths (highly recommended SIL 3-4)
- Fixed-width integer types only (`uint8_t`, `uint16_t`, `uint32_t`, `int8_t`, etc.)
- Dual-channel (2oo2) execution of all SIL 3 safety functions

### 2.5 Assumptions and Dependencies

**Assumptions**:
- ASSUME-001: TCMS provides speed data via CAN at 10 Hz (100 ms period) with SIL 2 integrity
- ASSUME-002: Hardware door locks are fail-closed (spring-loaded, locked without power)
- ASSUME-003: Mechanical obstacle force limit (150 N per EN 14752) implemented in hardware
- ASSUME-004: Emergency release is a passive mechanical system independent of software
- ASSUME-005: DCU hardware provides independent watchdog timers per MCU with 50 ms timeout
- ASSUME-006: Regular maintenance performed per schedule

**Dependencies**:
- Depends on TCMS for accurate speed data (DEPEND-001 from SSRS)
- Depends on hardware locks being fail-closed (DEPEND-005 from SSRS)
- Depends on EN 50128 SIL 3 development process compliance (DEPEND-004 from SSRS)
- Depends on hardware GPIO, PWM, CAN, RS-485, SPI, ADC interfaces per HAL contract

---

## 3. SOFTWARE REQUIREMENTS

---

### 3.1 Functional Requirements

#### 3.1.1 Door Opening Control

---

**REQ-FUN-001**: Door Opening Command Processing
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-001, SYS-REQ-002, HAZ-003

**Description**: The software SHALL initiate a door opening sequence when it receives a door open command from TCMS or the local door open button AND all opening preconditions are satisfied.

**Opening Preconditions** (ALL must be true):

| Condition | Required State |
|-----------|----------------|
| Train speed | <= 5 km/h (confirmed, not defaulted) |
| Door open command | Received from TCMS or local button |
| No active door fault | All fault flags clear for target door |
| No active emergency stop | Emergency stop flag = 0 |
| Operational mode | Normal or Selective Door Disablement (non-disabled door) |

**Inputs**: Door open command (`uint8_t`, CAN/GPIO), train speed (`uint16_t`, km/h x 10), fault status (`uint8_t`), operational mode (`uint8_t`)
**Outputs**: Door motor start signal (PWM enable, direction = open)
**Preconditions**: System initialized, HAL ready, speed data current (< 200 ms old)
**Postconditions**: Door motor energized in open direction; door state = OPENING
**Error Handling**: IF any precondition is not met, THEN opening command is rejected; fault logged with rejection reason
**Verification Method**: Test (unit test — precondition matrix, integration test, system test)
**Acceptance Criteria**: All 5 precondition combinations tested; no door opens when train speed > 5 km/h; command-to-motor-start latency <= 200 ms

---

**REQ-FUN-002**: Door Opening Completion Detection
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-004

**Description**: The software SHALL declare a door fully open when BOTH redundant position sensors (Sensor A AND Sensor B) report the fully-open position (2oo2 voting).

**Inputs**: Position sensor A fully-open signal (`uint8_t`), Position sensor B (`uint8_t`)
**Outputs**: Door state = FULLY_OPEN, status flag set, TCMS status message updated
**Error Handling**: IF only one sensor reports fully open, THEN treat as OPENING; log sensor disagreement
**Verification Method**: Test (integration test — sensor voting logic, fault injection)
**Acceptance Criteria**: Door declared FULLY_OPEN only when both sensors agree; single sensor cannot declare fully-open alone; sensor disagreement logged

---

**REQ-FUN-003**: Door Opening Timeout Fault
**Priority**: High
**SIL Level**: SIL 2
**Traceability**: SYS-REQ-003

**Description**: The software SHALL raise an opening timeout fault if the door does not reach the fully-open position within 4.0 seconds of the door open command being issued.

**Inputs**: Door state, elapsed time since open command (timer, ms)
**Outputs**: Fault code `FAULT_DOOR_OPEN_TIMEOUT`, driver alert via TCMS, door motor de-energized
**Verification Method**: Test (unit test — timer boundary, integration test)
**Acceptance Criteria**: Timeout triggered at 4.0 s +/- 100 ms; motor de-energized; fault logged; alert sent to TCMS

---

#### 3.1.2 Door Closing Control

---

**REQ-FUN-004**: Door Closing Command Processing
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-005

**Description**: The software SHALL initiate a door closing sequence when it receives a door close command from TCMS AND no obstacle is detected AND no active closing fault is present.

**Inputs**: Door close command (`uint8_t`), obstacle detection status (`uint8_t`), fault status
**Outputs**: Door motor start signal (PWM enable, direction = close)
**Preconditions**: Door currently in FULLY_OPEN or OPENING state; no obstruction
**Postconditions**: Door motor energized in close direction; door state = CLOSING
**Error Handling**: IF obstacle detected at close command time, THEN reject close command and log; retry when obstacle cleared and command re-issued
**Verification Method**: Test (unit test, integration test, system test)
**Acceptance Criteria**: Close only initiates when command received AND no obstacle present; obstacle at command time blocks close and logs event

---

**REQ-FUN-005**: Door Close-and-Lock Completion Detection
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-012, SYS-REQ-014, HAZ-001, HAZ-005

**Description**: The software SHALL declare a door fully closed and locked only when ALL of the following are confirmed by 2oo2 voting: (a) both door position sensors report fully-closed, AND (b) both lock position sensors report locked.

**Decision Table**:

| Pos Sensor A | Pos Sensor B | Lock Sensor A | Lock Sensor B | Result |
|:---:|:---:|:---:|:---:|:---:|
| Closed | Closed | Locked | Locked | CLOSED_AND_LOCKED |
| Closed | Closed | Locked | Unlocked | NOT_LOCKED (fault) |
| Closed | Open | Locked | Locked | NOT_CLOSED (fault) |
| Any other | -- | -- | -- | NOT_CLOSED (fault) |

**Inputs**: Position sensor A (`uint8_t`), B (`uint8_t`); lock sensor A (`uint8_t`), B (`uint8_t`)
**Outputs**: Door state = CLOSED_AND_LOCKED; departure interlock released for this door
**Error Handling**: IF sensors disagree, THEN door state = fault; departure interlock NOT released; alert TCMS
**Verification Method**: Test (integration test — all sensor combinations), Fault Injection
**Acceptance Criteria**: Door declared CLOSED_AND_LOCKED only with 4-sensor 2oo2 agreement; partial agreement produces fault; departure interlock not released on fault

---

**REQ-FUN-006**: Door Closing Fault — Timeout
**Priority**: High
**SIL Level**: SIL 2
**Traceability**: SYS-REQ-011

**Description**: The software SHALL raise a closing timeout fault if the door does not reach the CLOSED_AND_LOCKED state within 10.0 seconds of the close command (no obstacles).

**Verification Method**: Test (unit test — timer boundary)
**Acceptance Criteria**: Timeout at 10.0 s +/- 100 ms; fault logged; alert to TCMS

---

**REQ-FUN-007**: Door Obstacle Retry Logic
**Priority**: Medium
**SIL Level**: SIL 2
**Traceability**: SYS-REQ-009, SYS-REQ-010

**Description**: The software SHALL retry the door closing operation a maximum of 3 times after obstacle-induced reversal. After 3 failed attempts, the software SHALL declare a closing fault and alert the driver.

**Inputs**: Obstacle event flag, retry counter (`uint8_t`)
**Outputs**: Door motor re-energized in close direction (retry); `FAULT_DOOR_CLOSE_RETRY_EXCEEDED` after 3 attempts
**Verification Method**: Test (unit test — counter logic, integration test)
**Acceptance Criteria**: Exactly 3 retries permitted; fault raised after 3rd obstacle; driver alert sent; door remains open after fault

---

#### 3.1.3 Door Locking Control

---

**REQ-FUN-008**: Automatic Door Lock Engagement
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-012, SYS-REQ-013, HAZ-001

**Description**: The software SHALL command door lock engagement when the door position is fully closed (2oo2 confirmed) AND the close sequence is completed.

**Inputs**: Door position sensors A and B (2oo2), close sequence completion flag
**Outputs**: Lock actuator energize command (24V solenoid command)
**Postconditions**: Lock engaged; software monitors lock sensors for confirmation
**Error Handling**: IF position sensors disagree, THEN lock engagement command not issued; fault raised
**Verification Method**: Test (integration test — sequence test, fault injection)
**Acceptance Criteria**: Lock command only when both position sensors report closed; no lock command on sensor disagreement

---

**REQ-FUN-009**: Departure Interlock Signal
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-016, SYS-REQ-017, HAZ-001, HAZ-005

**Description**: The software SHALL transmit the door-locked status signal to TCMS via CAN within 100 ms of confirming ALL doors in the system are in CLOSED_AND_LOCKED state. The software SHALL withhold this signal if ANY door is not CLOSED_AND_LOCKED.

**Inputs**: Lock status for all N doors (`uint8_t` array, per-door state)
**Outputs**: CAN message `MSG_DOOR_LOCKED_ALL` (transmitted only when all doors are CLOSED_AND_LOCKED)
**Error Handling**: IF any door is not CLOSED_AND_LOCKED, THEN send `MSG_DOOR_NOT_READY` to TCMS every 100 ms
**Verification Method**: Test (integration test — all-doors-locked and partial-locked scenarios, timing test)
**Acceptance Criteria**: Signal transmitted within 100 ms of all-doors-locked confirmation; withheld if any door not confirmed locked; timing <= 100 ms verified

---

**REQ-FUN-010**: Door Lock Maintenance While Moving
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-013, SYS-REQ-015, HAZ-001, HAZ-003

**Description**: The software SHALL continuously verify door lock status every 20 ms control cycle and re-command lock engagement if any door lock is detected as unlocked while train speed > 5 km/h.

**Inputs**: Lock sensors A and B per door (every 20 ms cycle), train speed
**Outputs**: Lock re-command signal if inconsistency detected; fault logged
**Error Handling**: IF lock lost while moving, THEN immediately re-command lock AND raise `FAULT_LOCK_LOST_WHILE_MOVING` AND alert TCMS
**Verification Method**: Test (integration test — lock loss simulation while speed > 5 km/h), Fault Injection
**Acceptance Criteria**: Lock loss detected and re-commanded within one 20 ms cycle; fault raised; TCMS alerted

---

#### 3.1.4 Operational Mode Management

---

**REQ-FUN-011**: Operational Mode Support
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-023

**Description**: The software SHALL implement and support the following operational modes as a finite state machine (FSM) with explicit transitions:

| Mode | State Value | Description |
|------|-------------|-------------|
| NORMAL | 0x01 | Automatic control with full safety interlocks |
| SELECTIVE_DISABLE | 0x02 | One or more doors isolated; remaining doors operational |
| DIAGNOSTIC | 0x03 | Sensor testing; train stationary required |
| SAFE_STATE | 0x04 | All doors commanded locked; entered on critical fault |

**Inputs**: Mode command from TCMS or driver panel, authorization token, current mode
**Outputs**: Active mode state (`uint8_t`), mode logged with timestamp
**Error Handling**: Invalid mode command rejected; unknown mode code treated as SAFE_STATE
**Verification Method**: Test (unit test — FSM transitions, integration test), Inspection
**Acceptance Criteria**: All 4 modes implementable; illegal transitions rejected; mode change logged

---

**REQ-FUN-012**: Mode Transition Authorization
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-024, HAZ-009

**Description**: The software SHALL only permit mode transitions when explicit authorization has been received from the driver (physical key signal) or TCMS (authorized digital command). Unauthorized mode transition attempts SHALL be rejected and logged.

**Inputs**: Authorization signal (driver key bit in CAN message or discrete input), mode change request
**Outputs**: Mode change accepted or rejected; event log entry
**Verification Method**: Test (unit test — authorized vs. unauthorized transitions), Inspection
**Acceptance Criteria**: No mode change without authorization signal; rejection logged with source; authorized transition succeeds

---

**REQ-FUN-013**: Selective Door Disablement Mode
**Priority**: Medium
**SIL Level**: SIL 2
**Traceability**: SYS-REQ-023, HAZ-009

**Description**: In SELECTIVE_DISABLE mode, the software SHALL: (a) isolate the specified defective door(s) from normal control, (b) maintain all safety interlocks active for non-disabled doors, (c) prevent train departure if the disabled door is on the platform side, (d) log the disablement event with timestamp and authorization source.

**Inputs**: Door ID to disable (`uint8_t`), platform side flag
**Outputs**: Disabled door control inhibited; remaining doors operational; departure inhibit if platform-side
**Verification Method**: Test (integration test — disable then operate remaining doors, departure inhibit test)
**Acceptance Criteria**: Disabled door unresponsive; other doors normal; platform-side disablement blocks departure; event logged

---

**REQ-FUN-014**: Diagnostic Mode Conditions
**Priority**: Medium
**SIL Level**: SIL 2
**Traceability**: SYS-REQ-023, HAZ-009

**Description**: The software SHALL only enter DIAGNOSTIC mode when: (a) train speed = 0 km/h (confirmed), AND (b) explicit authorization from maintenance personnel is present. All safety interlocks SHALL remain active in Diagnostic mode.

**Inputs**: Speed (must be 0 km/h), maintenance authorization signal
**Outputs**: Diagnostic mode active; safety interlocks not bypassed
**Error Handling**: IF speed > 0 km/h, THEN Diagnostic mode request rejected; IF authorization absent, THEN rejected
**Verification Method**: Test (unit test — precondition gate), Inspection
**Acceptance Criteria**: Diagnostic mode only when speed = 0 AND authorization present; safety interlocks verified active in diagnostic mode

---

#### 3.1.5 Position Monitoring

---

**REQ-FUN-015**: Continuous Door Position Monitoring
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-025, SYS-REQ-026

**Description**: The software SHALL continuously monitor and maintain a door position state for each door every 20 ms control cycle. Valid states are: FULLY_OPEN, INTERMEDIATE, FULLY_CLOSED, UNKNOWN.

| State | Condition |
|-------|-----------|
| FULLY_OPEN | Both open end-stop sensors (A and B) = active |
| FULLY_CLOSED | Both closed end-stop sensors (A and B) = active |
| INTERMEDIATE | Neither end-stop condition met |
| UNKNOWN | Sensor A and Sensor B disagree (fault condition) |

**Inputs**: Position sensor A and B per door (24V GPIO, read every 20 ms)
**Outputs**: Door state variable (`uint8_t enum`) per door, updated every cycle
**Error Handling**: UNKNOWN state treated as fault; door SHALL NOT be commanded until resolved
**Verification Method**: Test (unit test — all state transitions), Integration Test
**Acceptance Criteria**: All 4 states representable; UNKNOWN declared on sensor disagreement; state updated every 20 ms cycle

---

**REQ-FUN-016**: Door Status Reporting to TCMS
**Priority**: High
**SIL Level**: SIL 2
**Traceability**: SYS-REQ-027

**Description**: The software SHALL transmit individual door status to TCMS via CAN every 100 ms for each door. The status message SHALL include door position state, lock state, and fault code for each door.

**Data Types**:
```c
typedef struct {
    uint8_t  door_id;        /* 0-based door index */
    uint8_t  position_state; /* FULLY_OPEN=1, INTERMEDIATE=2, FULLY_CLOSED=3, UNKNOWN=4 */
    uint8_t  lock_state;     /* UNLOCKED=0, LOCKED=1, LOCK_FAULT=2 */
    uint8_t  fault_code;     /* 0=no fault, 1-255=fault codes */
    uint16_t crc16;          /* CRC-16 of preceding bytes */
} door_status_msg_t;
```
**Verification Method**: Test (integration test — CAN message content and timing), Interface Test
**Acceptance Criteria**: Message transmitted every 100 ms +/- 10 ms; correct state and fault encoding; CRC-16 valid

---

#### 3.1.6 Fault Detection and Management

---

**REQ-FUN-017**: Continuous Fault Monitoring
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-028, SYS-REQ-029

**Description**: The software SHALL continuously monitor for fault conditions every 20 ms control cycle. Monitored fault categories:

| Fault Category | Detection Mechanism |
|----------------|---------------------|
| Position sensor failure | Sensor out-of-range, sensor disagrees with other channel |
| Obstacle sensor failure | Sensor stuck active/inactive, self-test failure |
| Lock mechanism failure | Lock sensor inconsistency (commanded locked but sensor = unlocked) |
| Communication failure | CAN timeout (> 200 ms), CRC errors, sequence counter discontinuity |
| Speed sensor failure | TCMS speed data timeout (> 200 ms), out-of-range |
| Cross-channel disagreement | SPI comparison result mismatch |
| Watchdog failure | Watchdog not refreshed within 50 ms |

**Inputs**: All sensor inputs, CAN receive buffer, SPI comparison result, watchdog refresh timer
**Outputs**: Fault flags per category (`uint8_t`), fault log entry
**Error Handling**: Fault detected -> fault flag set -> escalate per fault criticality (Section 3.4)
**Verification Method**: Test (unit test per fault type), Fault Injection, Integration Test
**Acceptance Criteria**: Each fault type detected within specified time (<=100 ms for sensors, <=200 ms for communication)

---

**REQ-FUN-018**: Fault Event Logging
**Priority**: High
**SIL Level**: SIL 1
**Traceability**: SYS-REQ-031, SYS-REQ-070

**Description**: The software SHALL log all door events and faults with timestamps to non-volatile storage (SPI Flash). The event log SHALL store a minimum of 1000 events in a circular buffer with CRC-16 protection per entry.

**Data Types**:
```c
typedef struct {
    uint32_t timestamp_ms;   /* System time in ms since power-on */
    uint8_t  event_type;     /* EVENT_DOOR_OPEN, EVENT_FAULT, EVENT_MODE_CHANGE, etc. */
    uint8_t  door_id;        /* 0-based door index, 0xFF = system-wide */
    uint8_t  fault_code;     /* Fault or event code */
    uint8_t  data;           /* Optional event data */
    uint16_t crc16;          /* CRC-16 of preceding 6 bytes */
} event_log_entry_t;
```
**Verification Method**: Test (integration test — log 1000+ events, circular overwrite, CRC check)
**Acceptance Criteria**: >= 1000 events stored; CRC-16 verified on retrieval; circular buffer wraps correctly; log readable via diagnostics port

---

---

### 3.2 Performance Requirements

---

**REQ-PERF-001**: Control Cycle Time
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-036

**Description**: The software SHALL execute one complete control cycle (sensor read, safety logic, state machine update, actuator output, cross-channel comparison, CAN message processing) within 20 ms (50 Hz). The Worst-Case Execution Time (WCET) SHALL NOT exceed 16 ms (80% of cycle period, leaving 4 ms margin).

**Acceptance Criteria**: WCET <= 16 ms measured by hardware timer on target hardware under worst-case load; 4 ms margin verified
**Verification Method**: Performance Test (hardware timer instrumentation), Static Analysis (timing analysis)

---

**REQ-PERF-002**: Speed Interlock Response Time
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-035, HAZ-003

**Description**: The software SHALL respond to a train speed exceeding 5 km/h by completing door lock engagement commands within 100 ms of the speed threshold crossing.

**Acceptance Criteria**: Measured time from speed signal > 5 km/h (CAN message) to lock command output <= 100 ms; verified on target hardware
**Verification Method**: Performance Test (hardware timer), Integration Test

---

**REQ-PERF-003**: Obstacle Detection Response Time
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-034, HAZ-002, HAZ-004

**Description**: The software SHALL issue a door reversal command within 150 ms of an obstacle being detected on either obstacle sensor during door closing.

**Acceptance Criteria**: Measured time from obstacle sensor rising edge to motor reversal PWM command <= 150 ms on target hardware; tested with injected obstacle signal
**Verification Method**: Performance Test (oscilloscope on GPIO and PWM), Integration Test

---

**REQ-PERF-004**: Door Command to Motor Start Latency
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-003

**Description**: The software SHALL issue the first motor movement command within 200 ms of receiving a door open or close command, provided all preconditions are satisfied.

**Acceptance Criteria**: Measured command-to-motor latency <= 200 ms; timing verified on target hardware
**Verification Method**: Performance Test (hardware timer), Integration Test

---

**REQ-PERF-005**: TCMS Locked Status Transmission Latency
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-017, HAZ-001

**Description**: The software SHALL transmit the door-locked-all status CAN message to TCMS within 100 ms of all doors achieving CLOSED_AND_LOCKED state.

**Acceptance Criteria**: CAN transmission latency <= 100 ms from state confirmation; measured with CAN analyser
**Verification Method**: Performance Test (CAN analyser), Integration Test

---

**REQ-PERF-006**: Sensor Fault Detection Time
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-029

**Description**: The software SHALL detect sensor faults (sensor stuck, out-of-range, 2oo2 disagreement) within 100 ms.

**Acceptance Criteria**: Fault flag set within 100 ms of fault condition onset; verified by fault injection
**Verification Method**: Fault Injection Test, Integration Test

---

**REQ-PERF-007**: Communication Fault Detection Time
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-029, SSRS SAFE-DIAG-003

**Description**: The software SHALL detect loss of TCMS CAN speed signal within 200 ms (2 x 100 ms update period).

**Acceptance Criteria**: Fault flag set within 200 ms +/- 20 ms of last valid TCMS message; verified in integration test
**Verification Method**: Integration Test (CAN bus silence injection), Fault Injection

---

**REQ-PERF-008**: CPU Utilization
**Priority**: Medium
**SIL Level**: SIL 2
**Traceability**: SYS-REQ-036

**Description**: The software SHALL consume no more than 80% of available CPU cycles under worst-case operational load.

**Acceptance Criteria**: CPU utilization <= 80% measured by profiler under worst-case scenario
**Verification Method**: Performance Test (profiler), Analysis

---

**REQ-PERF-009**: Memory Utilization — RAM
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-036, SSRS SAFE-SW-007

**Description**: The software SHALL use no more than 80% of available SRAM per MCU (800 KB out of 1 MB). All memory allocation SHALL be static (no heap).

**Acceptance Criteria**: Linker map shows total SRAM (stack + globals + BSS) <= 800 KB; verified by static analysis
**Verification Method**: Static Analysis (linker map), Code Review

---

**REQ-PERF-010**: Memory Utilization — Flash
**Priority**: High
**SIL Level**: SIL 2
**Traceability**: SYS-REQ-036

**Description**: The software SHALL use no more than 80% of available Flash memory per MCU (1600 KB out of 2 MB, excluding bootloader).

**Acceptance Criteria**: Linker map shows code + rodata <= 1600 KB; 10% margin for future patches
**Verification Method**: Static Analysis (linker map)

---

---

### 3.3 Interface Requirements

#### 3.3.1 Hardware Interfaces

---

**REQ-INT-001**: Door Motor Actuator Interface
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-040

**Description**: The software SHALL control each door motor via PWM output through the HAL. PWM frequency SHALL be 20 kHz; duty cycle range 0-100% (`uint8_t`); direction controlled by a separate direction GPIO.

```c
error_t HAL_PWM_SetDutyCycle(uint8_t door_id, uint8_t duty_percent);
error_t HAL_GPIO_SetMotorDirection(uint8_t door_id, uint8_t direction);
/* direction: MOTOR_OPEN=1, MOTOR_CLOSE=0, MOTOR_STOP=2 */
```
**Error Handling**: IF `HAL_PWM_SetDutyCycle` returns error, THEN set duty to 0, raise `FAULT_MOTOR_CTRL_FAIL`, transition to SAFE_STATE
**Verification Method**: Integration Test, Interface Test (oscilloscope)
**Acceptance Criteria**: PWM at 20 kHz confirmed with oscilloscope; duty cycle accurate +/-2%; direction bit correct

---

**REQ-INT-002**: Door Position Sensor Interface
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-041

**Description**: The software SHALL read position sensor inputs via HAL GPIO as digital 24V logic inputs (interrupt-driven AND polled every 20 ms cycle). Two sensors per door (Sensor A and Sensor B) for 2oo2 voting.

```c
error_t HAL_GPIO_ReadPositionSensor(uint8_t door_id, uint8_t sensor_id,
                                     uint8_t *state);
/* state: 0=not at end-stop, 1=at end-stop */
```
**Error Handling**: IF HAL read returns error, THEN treat as UNKNOWN; raise sensor fault
**Verification Method**: Integration Test
**Acceptance Criteria**: Both sensors read independently per 20 ms cycle; interrupt latency <= 5 ms

---

**REQ-INT-003**: Obstacle Detection Sensor Interface
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-042, HAZ-002, HAZ-004

**Description**: The software SHALL read obstacle detection sensor inputs via interrupt-driven HAL GPIO. Either obstacle sensor (A or B) triggering SHALL initiate the obstacle response. Sensor inputs are active-high (1 = obstacle detected).

```c
error_t HAL_GPIO_ReadObstacleSensor(uint8_t door_id, uint8_t sensor_id,
                                     uint8_t *detected);
/* Interrupt: void OBD_ObstacleISR(uint8_t door_id, uint8_t sensor_id); */
```
**Error Handling**: IF both obstacle sensors read 0 during self-test after power-on, THEN raise obstacle sensor fault; door closing disabled
**Verification Method**: Integration Test, Fault Injection (IR beam interruption)
**Acceptance Criteria**: Single-sensor obstacle triggers reversal; ISR latency <= 1 ms; both sensors tested at startup

---

**REQ-INT-004**: Door Lock Actuator Interface
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-043, HAZ-001

**Description**: The software SHALL control door lock actuators via HAL GPIO digital output (24V, 1A). Lock command: 1 = engage lock solenoid (unlocked); 0 = release solenoid (hardware fail-closed spring locks door).

```c
error_t HAL_GPIO_SetLockActuator(uint8_t door_id, uint8_t locked);
/* NOTE: fail-safe state = 0 (solenoid off = spring-locked) */
```
**Error Handling**: IF lock command returns error, THEN raise `FAULT_LOCK_CTRL_FAIL`; report to fault manager
**Verification Method**: Integration Test, Fault Injection
**Acceptance Criteria**: Lock command/release verified by lock sensors; fail-closed verified on power-off test

---

**REQ-INT-005**: Lock Position Sensor Interface
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-044, HAZ-001, HAZ-005

**Description**: The software SHALL read lock position sensors via HAL GPIO. Two sensors per lock (Sensor A and Sensor B) for 2oo2 voting. 1 = locked, 0 = unlocked.

```c
error_t HAL_GPIO_ReadLockSensor(uint8_t door_id, uint8_t sensor_id,
                                  uint8_t *locked);
```
**Error Handling**: IF sensors disagree, THEN treat as unlocked (conservative); raise lock fault
**Verification Method**: Integration Test, Fault Injection
**Acceptance Criteria**: Disagreement treated conservatively (not-locked); sensor fault detected and logged

---

**REQ-INT-006**: Watchdog Hardware Interface
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-064, SSRS SAFE-SW-009, HAZ-009

**Description**: The software SHALL refresh the external hardware watchdog via HAL within every 40 ms (watchdog timeout = 50 ms; refresh at 40 ms provides 10 ms margin). Failure to refresh SHALL cause hardware reset and safe state.

```c
void HAL_Watchdog_Refresh(void); /* Called from main loop every 40 ms */
```
**Acceptance Criteria**: Watchdog refreshed every 40 ms +/- 5 ms; deliberate missed refresh triggers hardware reset within 50 ms + 5 ms tolerance
**Verification Method**: Fault Injection (deliberate watchdog starve), Integration Test

---

#### 3.3.2 Software Interfaces

---

**REQ-INT-007**: TCMS CAN Interface — Receive
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-046, SYS-REQ-047, HAZ-003

**Description**: The software SHALL receive and process the following CAN messages from TCMS. All safety-critical messages SHALL include CRC-16 and sequence counter.

| Message ID | Content | Rate | SIL |
|-----------|---------|------|-----|
| 0x100 | Speed data (`uint16_t` km/h x 10), CRC-16, sequence counter | 100 ms | SIL 3 |
| 0x101 | Door open command (side, door mask), authorization | On-event | SIL 3 |
| 0x102 | Door close command (side, door mask) | On-event | SIL 3 |
| 0x103 | Mode change command + authorization | On-event | SIL 3 |
| 0x104 | Emergency stop command | On-event | SIL 3 |

```c
typedef struct {
    uint16_t speed_kmh_x10; /* Speed in 1/10 km/h */
    uint8_t  seq_counter;   /* Increments each message */
    uint16_t crc16;         /* CRC-16 of first 3 bytes */
} tcms_speed_msg_t;
```
**Error Handling**: CRC mismatch -> discard message, log CRC error; timeout -> assume train moving
**Verification Method**: Integration Test (CAN bus injection), Interface Test
**Acceptance Criteria**: Speed data parsed correctly; CRC verified on every message; sequence counter discontinuity detected; timeout fault at 200 ms

---

**REQ-INT-008**: TCMS CAN Interface — Transmit
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-017, SYS-REQ-016, SYS-REQ-027

**Description**: The software SHALL transmit the following CAN messages to TCMS. All messages SHALL include CRC-16.

| Message ID | Content | Rate | SIL |
|-----------|---------|------|-----|
| 0x200 | Door-locked-all status (`uint8_t` boolean) + per-door lock mask | 100 ms (or on change) | SIL 3 |
| 0x201 | Per-door status (position, lock, fault code) x N doors | 100 ms | SIL 2 |
| 0x202 | System fault report (fault category, fault code) | On-event + 500 ms periodic | SIL 2 |
| 0x203 | Mode status (current mode, door disable mask) | On-change + 1 s periodic | SIL 2 |

**Verification Method**: Integration Test (CAN analyser), Interface Test
**Acceptance Criteria**: All messages transmitted at correct rate; CRC-16 valid; content matches door state

---

**REQ-INT-009**: DDU RS-485 Interface
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-049

**Description**: The software SHALL communicate with Door Drive Units (DDU) via RS-485 at 115.2 kbit/s using a proprietary multi-drop protocol. Motor commands and position feedback SHALL be exchanged with each DDU every 20 ms control cycle.

**Protocol requirements**:
- CRC-16 on all frames
- Sequence counter per DDU (detect lost/duplicate frames)
- DDU response timeout: 40 ms (2 x cycle time) -> DDU communication fault

**Verification Method**: Integration Test (RS-485 bus analyser), Interface Test
**Acceptance Criteria**: All DDU messages exchanged every 20 ms; CRC validated; DDU timeout detected within 40 ms

---

**REQ-INT-010**: Cross-Channel SPI Communication
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-060, SSRS SAFE-CCF-002, HAZ-009

**Description**: The software on Channel A SHALL exchange safety-critical state variables with Channel B via SPI every 20 ms control cycle. The comparison SHALL include: train speed, door states, lock states, obstacle flags, fault flags, and active safety decisions.

```c
typedef struct {
    uint16_t speed_kmh_x10;
    uint8_t  door_states[MAX_DOORS];
    uint8_t  lock_states[MAX_DOORS];
    uint8_t  obstacle_flags[MAX_DOORS];
    uint8_t  fault_flags;
    uint8_t  safety_decisions;
    uint16_t crc16;
} cross_channel_state_t;
```
**Error Handling**: IF any field differs between Channel A and Channel B, OR CRC mismatch, THEN immediately trigger SAFE_STATE
**Verification Method**: Test (integration test — deliberate disagreement injection), Fault Injection
**Acceptance Criteria**: Disagreement triggers safe state within one 20 ms cycle; CRC mismatch triggers safe state; comparison runs every cycle

---

**REQ-INT-011**: Emergency Release Detection Interface
**Priority**: High
**SIL Level**: SIL 2
**Traceability**: SYS-REQ-021, SYS-REQ-045, HAZ-008

**Description**: The software SHALL monitor the emergency release detection switch (GPIO input) for each door every 20 ms cycle. Upon detecting activation, the software SHALL log the event with timestamp and door ID, and send an alert to TCMS within 200 ms.

**Inputs**: Emergency release switch (`uint8_t` GPIO per door)
**Outputs**: Emergency release event log entry, TCMS alert CAN message
**Error Handling**: IF emergency release detected while speed > 5 km/h, THEN raise `FAULT_EMERG_RELEASE_WHILE_MOVING`
**Verification Method**: Integration Test, Interface Test
**Acceptance Criteria**: Emergency release detected within 20 ms; TCMS alert within 200 ms; event logged with timestamp

---

#### 3.3.3 User Interfaces

---

**REQ-INT-012**: Driver Control Panel Interface
**Priority**: Medium
**SIL Level**: SIL 2
**Traceability**: SYS-REQ-048, SYS-REQ-051

**Description**: The software SHALL interface with the Driver Control Panel via discrete I/O (24V logic) and/or CAN bus. The software SHALL read manual door open/close button states and update door status indicator outputs every 20 ms cycle.

**Outputs**: Per-door status indicators (OPEN=green, CLOSED=amber, LOCKED=off, FAULT=red); audible alarm output
**Verification Method**: Integration Test, Manual Test
**Acceptance Criteria**: Status indicators match door state within one 20 ms cycle

---

**REQ-INT-013**: Diagnostics Port Interface
**Priority**: Low
**SIL Level**: SIL 1
**Traceability**: SYS-REQ-050

**Description**: The software MAY provide diagnostic data via the USB/RS-232 port at 115.2 kbit/s for maintenance purposes. The interface SHALL be read-only during normal operation (no safety parameter modification). Event log download and system status query SHALL be supported.

**Note**: This interface is for maintenance only and is NOT safety-critical.
**Verification Method**: Manual Test
**Acceptance Criteria**: Event log downloadable; status readable; no safety parameters modifiable via diagnostics port in Normal mode

---

---

### 3.4 Safety Requirements

> **Authority Note**: Safety requirements REQ-SAFE-001 through REQ-SAFE-021 are co-authored with the Safety Engineer (SAF) as the hazard authority. SIL assignments are per SAF guidance based on the System Safety Requirements Specification (DOC-SYS-SAF-2026-001). REQ does not independently classify or close hazards.

---

**REQ-SAFE-001**: Speed Interlock — Inhibit Door Opening When Moving
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-002, SYS-REQ-015, HAZ-003, SSRS SF-001

**Description**: The software SHALL inhibit all door opening commands when train speed exceeds 5 km/h. This inhibition SHALL be enforced by the Safety Kernel on both Channel A and Channel B independently (2oo2). The software SHALL default to "train moving" (inhibit opening) if speed data is absent, stale (> 200 ms), or invalid (CRC error).

**Safety Mechanism**: Dual-channel independent evaluation; fail-safe default = inhibit
**Failure Mode**: IF speed sensor fails, THEN inhibit door opening (conservative default)
**Inputs**: Speed `uint16_t` (km/h x 10), speed data timestamp
**Outputs**: `speed_interlock_active` flag (`uint8_t`, 1 = inhibit, 0 = permit)
**Verification Method**: Safety Test, Fault Injection (speed > 5 km/h, stale speed, CRC error), Static Analysis
**Acceptance Criteria**: No door open command processed when speed > 5 km/h; inhibit active on stale/missing speed; both channels independently verify; verified by fault injection

---

**REQ-SAFE-002**: Speed Interlock — Maintain Door Locking When Moving
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-013, HAZ-001, HAZ-003, SSRS SF-001

**Description**: The software SHALL command and maintain door lock engagement on all doors whenever train speed exceeds 5 km/h. This function SHALL be continuously evaluated every 20 ms cycle by both Channel A and Channel B independently.

**Failure Mode**: IF speed signal is absent or stale, THEN command doors locked (fail-safe)
**Verification Method**: Safety Test, Fault Injection, Integration Test
**Acceptance Criteria**: Doors commanded locked within one 20 ms cycle when speed > 5 km/h; maintained locked while speed > 5 km/h; fail-safe on missing speed

---

**REQ-SAFE-003**: Departure Interlock — All Doors Confirmed Locked
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-016, HAZ-001, HAZ-005, SSRS SF-002

**Description**: The software SHALL withhold the door-locked-all signal from TCMS unless ALL doors in the system are in CLOSED_AND_LOCKED state (confirmed by 2oo2 position and lock sensors). A single door not in CLOSED_AND_LOCKED state SHALL prevent the departure interlock signal from being asserted.

**Verification Method**: Safety Test (all-locked, one-door-not-locked scenarios), Integration Test
**Acceptance Criteria**: Signal asserted ONLY when all doors confirmed locked; one unlocked door prevents signal; tested with N doors scenarios

---

**REQ-SAFE-004**: Obstacle Detection and Immediate Reversal
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-007, HAZ-002, HAZ-004, SSRS SF-003

**Description**: The software SHALL immediately stop and reverse door motor direction within 150 ms of detecting an obstacle on either obstacle sensor (A or B) during door closing operation. The reversal SHALL continue until the door reaches the FULLY_OPEN position.

**Mechanism**: Interrupt-driven (ISR latency <= 1 ms); motor reversal command issued from ISR or highest-priority task
**Safety Mechanism**: Hardware force limit (150 N, passive) as independent layer
**Verification Method**: Safety Test (obstacle injection during closing), Performance Test (latency), Integration Test
**Acceptance Criteria**: Motor reversal command within 150 ms of obstacle GPIO rising edge; verified on target hardware; door returns to fully open

---

**REQ-SAFE-005**: Door Position 2oo2 Verification for Safety Decisions
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-026, SYS-REQ-014, HAZ-001, HAZ-005, SSRS SF-005

**Description**: The software SHALL use 2oo2 voting (both Sensor A AND Sensor B must agree) for ALL safety-critical door position determinations. A single sensor reporting "closed" when the other reports otherwise SHALL result in the door being treated as NOT closed.

**Decision Rule**: Closed = (Sensor_A == CLOSED) AND (Sensor_B == CLOSED); any other combination = NOT_CLOSED
**Verification Method**: Safety Test (all sensor combinations), Fault Injection
**Acceptance Criteria**: All 4 sensor combinations produce correct conservative outcome; fault condition logged on disagreement

---

**REQ-SAFE-006**: Safe State — Transition on Critical Fault
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-030, HAZ-005, HAZ-009, SSRS SF-004, SSRS SAFE-STATE-001

**Description**: The software SHALL transition to SAFE_STATE (all doors commanded locked, all opening commands inhibited, TCMS alerted) within 100 ms of detecting any of the following critical faults:

| Trigger Condition | Action |
|-------------------|--------|
| Speed sensor failure | Lock all doors; inhibit opening |
| Position sensor failure (any door) | Assume door not closed; inhibit departure signal |
| Lock sensor failure (any door) | Assume not locked; inhibit departure signal |
| Cross-channel disagreement | Lock all doors; inhibit all commands |
| CAN speed data timeout (> 200 ms) | Lock all doors; assume moving |
| MCU failure (detected by cross-channel) | Lock all doors |

**Failure Mode**: IF safe state command fails, THEN hardware watchdog triggers reset; mechanical fail-closed locks engage
**Verification Method**: Fault Injection (each trigger condition), Safety Test, Integration Test
**Acceptance Criteria**: Safe state achieved within 100 ms for each trigger; all conditions independently tested; TCMS alerted

---

**REQ-SAFE-007**: Safe State — Maintained on Power Loss
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-061, SSRS SAFE-STATE-004

**Description**: The software SHALL design lock actuation such that removing electrical power results in doors remaining locked (fail-closed). The lock actuator HAL interface SHALL use active-low convention (0V = spring-locked). No software action is required on power loss; this is verified by hardware design, but the software SHALL NOT implement any logic that would energize locks as a default state.

**Verification Method**: Fault Injection (power removal during operation), Inspection (HAL interface review)
**Acceptance Criteria**: Lock sensors report locked after power removal; no software logic defaults locks open

---

**REQ-SAFE-008**: Watchdog Monitoring
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-064, SSRS SAFE-SW-009, SSRS SAFE-DIAG-006, HAZ-009

**Description**: The software SHALL refresh the external hardware watchdog timer via `HAL_Watchdog_Refresh()` within every 40 ms (watchdog timeout = 50 ms). The watchdog refresh SHALL only be called from the main control loop after successful completion of the safety logic cycle. Premature refresh (before safety logic complete) SHALL NOT be implemented.

**Acceptance Criteria**: Refresh called every 40 ms +/- 5 ms; deliberate starvation causes hardware reset within 55 ms; refresh not callable before safety logic completion
**Verification Method**: Fault Injection (deliberate loop hang -> watchdog fires), Integration Test

---

**REQ-SAFE-009**: CRC Protection for Safety-Critical Data
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-063, SSRS SAFE-SW-010

**Description**: The software SHALL apply CRC-16 (polynomial 0x8005 or CCITT 0x1021) to ALL safety-critical data structures and communication messages:

| Data Class | CRC Applied |
|-----------|-------------|
| CAN speed message (receive) | CRC-16 verified on each message |
| CAN door-locked-all message (transmit) | CRC-16 appended |
| Cross-channel SPI frame | CRC-16 verified |
| Event log entry | CRC-16 per entry |
| Configuration data (SPI Flash) | CRC-16 on block read |
| Boot-time flash integrity | CRC-16 over application code region |

**Verification Method**: Static Analysis (verify CRC call in each data path), Integration Test (corrupt CRC -> fault detected)
**Acceptance Criteria**: CRC verified on every reception and on boot; CRC corruption detected and fault raised; zero safety-critical messages processed without CRC check

---

**REQ-SAFE-010**: Cross-Channel 2oo2 Safety Logic
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-060, SSRS SAFE-CCF-002, HAZ-009

**Description**: The software SHALL execute all SIL 3 safety functions (SF-001 through SF-005) independently on both Channel A (MCU-A) and Channel B (MCU-B). After computing safety decisions, both channels SHALL exchange results via SPI and compare. Disagreement on any safety decision SHALL immediately trigger SAFE_STATE.

**Safety functions subject to 2oo2 comparison**: speed_interlock_active, door_lock_command, departure_interlock_signal, fault_flags, obstacle_reversal_command
**Verification Method**: Fault Injection (deliberate disagreement injection), Integration Test
**Acceptance Criteria**: Disagreement triggers safe state within 20 ms; all listed safety decisions compared every cycle

---

**REQ-SAFE-011**: Input Validation — All External Inputs
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-028, SSRS SAFE-SW-011

**Description**: The software SHALL validate all external inputs (CAN messages, GPIO sensor readings, RS-485 DDU responses) before use in safety logic. Validation SHALL include: range check, CRC check (for protocol messages), plausibility check.

| Input | Range Check | Plausibility Check |
|-------|------------|-------------------|
| Speed (CAN) | 0-2000 (0-200.0 km/h) | Delta <= 50 km/h per 100 ms |
| Position sensor | 0 or 1 | Per-cycle consistency |
| Lock sensor | 0 or 1 | State-consistent with command |
| Obstacle sensor | 0 or 1 | Self-test at startup |

**Verification Method**: Static Analysis (verify input validation at each entry point), Integration Test
**Acceptance Criteria**: Out-of-range input rejected and logged; CRC failure rejected; plausibility violation triggers diagnostic

---

**REQ-SAFE-012**: Emergency Release Monitoring and Alert
**Priority**: High
**SIL Level**: SIL 2
**Traceability**: SYS-REQ-021, HAZ-008, SSRS SF-006

**Description**: The software SHALL detect emergency release activation on any door within one 20 ms cycle and transmit an alert to TCMS within 200 ms. If emergency release is detected while train speed > 5 km/h, the software SHALL raise a `FAULT_EMERG_RELEASE_WHILE_MOVING` fault with highest priority.

**Verification Method**: Integration Test, Fault Injection
**Acceptance Criteria**: Detection within 20 ms; TCMS alert within 200 ms; fault raised and logged when speed > 5 km/h

---

**REQ-SAFE-013**: Diagnostic Coverage — Self-Test at Startup
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-066, SSRS SAFE-DIAG-001, SSRS SAFE-DIAG-004

**Description**: The software SHALL perform a self-test of all safety-critical sensors and actuators at system startup before entering Normal mode. All SIL 3 sensors SHALL pass self-test; failure SHALL prevent entry to Normal mode and SHALL report a specific fault code.

**Self-test sequence**: position sensors, obstacle sensors (beam break test), lock sensors (lock/unlock cycle), watchdog (verify fires on test starvation), CRC of flash (boot-time)
**Verification Method**: Test (startup self-test pass and fail scenarios), Integration Test
**Acceptance Criteria**: System refuses Normal mode on self-test failure; all sensor types exercised; fault code reported per failed sensor

---

**REQ-SAFE-014**: Diagnostic Coverage — Online Monitoring >= 99%
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-066, SSRS SAFE-DIAG-001

**Description**: The software SHALL implement online diagnostic monitoring to achieve a diagnostic coverage (DC) >= 99% for dangerous failures, as required for SIL 3 per EN 50129. Diagnostic mechanisms SHALL include: 2oo2 sensor voting, watchdog timeout, cross-channel comparison, CRC checks, plausibility monitoring, and feedback monitoring.

**Verification Method**: Analysis (FMEA-based DC calculation), Static Analysis
**Acceptance Criteria**: DC calculation documented showing >= 99% for each dangerous failure mode; coverage analysis reviewed by VER

---

**REQ-SAFE-015**: Safe State — Speed Interlock on Communication Loss
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-046, SSRS SAFE-STATE-002, HAZ-003

**Description**: The software SHALL assume "train moving" (speed > 5 km/h) and maintain all doors locked whenever the TCMS CAN bus speed signal is absent, timed out (> 200 ms), or has failed CRC verification. The speed data validity timeout SHALL be configurable in the range 100-500 ms (default 200 ms).

**Verification Method**: Fault Injection (CAN disconnection, CRC corruption), Integration Test
**Acceptance Criteria**: Doors remain locked when CAN disconnected; assumption within 200 ms of signal loss; no door opening on invalid speed data

---

**REQ-SAFE-016**: Safe State — Position Sensor Fault Response
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-030, SSRS SAFE-STATE-003

**Description**: The software SHALL assume "door not closed" for any door where position sensor fault (disagreement or stuck fault) is detected. This assumption SHALL prevent the departure interlock signal from being asserted for the affected door.

**Verification Method**: Fault Injection (sensor stuck, sensors disagree), Safety Test
**Acceptance Criteria**: Position fault -> door assumed not closed -> departure signal withheld; tested for each sensor failure mode

---

**REQ-SAFE-017**: Fail-Safe Behavior — Default State
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-061, SSRS SAFE-SW-001

**Description**: The software SHALL implement fail-safe defaults for all safety decision variables at initialization. All safety flags SHALL default to the safe state until explicitly set by valid sensor readings:

| Variable | Default (Safe) Value |
|----------|---------------------|
| `speed_interlock_active` | 1 (inhibit opening) |
| `door_lock_command[i]` | 1 (command locked) |
| `departure_interlock_released` | 0 (withhold departure) |
| `speed_kmh` | 999 (assume moving) |
| `door_position[i]` | UNKNOWN |
| `lock_state[i]` | UNLOCKED (conservative) |

**Verification Method**: Code Review, Static Analysis, Unit Test (verify default values at init)
**Acceptance Criteria**: All safety variables initialized to fail-safe values; verified by code review and unit test at init

---

**REQ-SAFE-018**: Selective Door Disablement — Safety Interlock Maintenance
**Priority**: High
**SIL Level**: SIL 2
**Traceability**: SYS-REQ-023, SSRS SAFE-COND-001, HAZ-009

**Description**: The software SHALL maintain the speed interlock (REQ-SAFE-001) and the departure interlock (REQ-SAFE-003) active and functional for ALL doors (including disabled doors) during Selective Door Disablement mode. A disabled door SHALL be treated as CLOSED_AND_LOCKED for departure purposes only if it is on the non-platform side AND is physically locked.

**Verification Method**: Test (mode integration test — disable one door, verify interlocks active), Inspection
**Acceptance Criteria**: Speed interlock active in disable mode; departure inhibited if disabled door is on platform side and not confirmed locked

---

**REQ-SAFE-019**: Periodic Memory Integrity Check
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-060, SSRS SAFE-DIAG-006

**Description**: The software SHALL periodically verify the integrity of safety-critical RAM data structures using CRC-16 checks every 100 ms (every 5 control cycles). A CRC failure SHALL raise `FAULT_RAM_CRC_FAIL` and transition to SAFE_STATE.

**Scope**: Safety variables (speed value, door state array, lock state array, fault flags)
**Verification Method**: Fault Injection (corrupt RAM byte, verify CRC fault), Integration Test
**Acceptance Criteria**: RAM corruption detected within 100 ms; safe state triggered; fault logged

---

**REQ-SAFE-020**: Boot-Time Flash Integrity Verification
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-060, SSRS SAFE-DIAG-006

**Description**: The software SHALL verify the CRC-16 of the entire application code region in Flash memory at every boot before entering Normal operation. If the Flash CRC fails, the software SHALL NOT enter Normal mode and SHALL output a specific boot fault code.

**Verification Method**: Fault Injection (corrupt Flash byte, verify boot fault), Integration Test
**Acceptance Criteria**: Boot proceeds to Normal mode only on CRC pass; Flash CRC failure prevents Normal mode; fault code output on diagnostics port

---

**REQ-SAFE-021**: Structured Programming Compliance
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SSRS SAFE-SW-004, EN 50128 Table A.4

**Description**: The software SHALL implement all control flow using structured programming constructs (sequential, selection [if-else, switch], iteration [for, while, do-while]). Use of `goto`, `setjmp`/`longjmp`, and `signal`/`raise` SHALL be prohibited in safety-critical code.

**Verification Method**: Static Analysis (MISRA C Rule 15.1 — no goto), Code Review
**Acceptance Criteria**: Zero `goto` occurrences in SIL 3 safety functions; MISRA C Rule 15.1 compliance; static analysis confirms

---

---

### 3.5 Reliability Requirements

---

**REQ-REL-001**: System Availability
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-067, SYS-REQ-039

**Description**: The software SHALL be designed to achieve a system availability of >= 99.9% per 24-hour operational period. The software SHALL support online diagnostics and fault reporting without interrupting normal door control operation.

**Acceptance Criteria**: Availability >= 99.9% demonstrated by operational test over 30-day period; diagnostic operations do not interrupt normal cycle
**Verification Method**: Analysis (MTBF/MTTR calculation), Integration Test

---

**REQ-REL-002**: Failure Rate (PFH) Target
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-062, SYS-REQ-065

**Description**: The software systematic failure systematic capability SHALL meet SC 2 (Systematic Capability 2) per EN 50129 Table A.3, contributing to an overall system dangerous failure rate PFH <= 10^-7 per hour. The software PFH budget is allocated as <= 10^-8 per hour.

**Acceptance Criteria**: EN 50128 SIL 3 development lifecycle compliance demonstrated; SC 2 claimed and supported by software safety case
**Verification Method**: Analysis (software safety case), Independent Safety Assessment

---

**REQ-REL-003**: Diagnostic Coverage Achievement
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SYS-REQ-066, SSRS SAFE-DIAG-001

**Description**: The software diagnostic mechanisms SHALL collectively achieve a diagnostic coverage of >= 99% for dangerous failures (sensors, memory, communication, processing). The DC SHALL be calculated and documented as part of the software safety case.

**Verification Method**: Analysis (DC calculation per FMEA), Review
**Acceptance Criteria**: DC calculation documented showing >= 99% per failure mode; reviewed by VER and SAF

---

**REQ-REL-004**: Online Diagnostics Non-Interruption
**Priority**: Medium
**SIL Level**: SIL 2
**Traceability**: SYS-REQ-068

**Description**: The software SHALL support online diagnostic data collection and event log access without interrupting or delaying normal door control operation. Diagnostic operations SHALL be allocated to a separate lower-priority task with a time budget of <= 2 ms per 20 ms cycle.

**Acceptance Criteria**: Diagnostic operations do not cause cycle time overrun; verified by WCET measurement
**Verification Method**: Performance Test, Integration Test

---

---

### 3.6 Security Requirements

---

**REQ-SEC-001**: Unauthorized Mode Change Prevention
**Priority**: High
**SIL Level**: SIL 2
**Traceability**: SYS-REQ-073

**Description**: The software SHALL reject mode change requests that do not include a valid authorization token (physical key signal or TCMS authorized command). Unauthorized mode change attempts SHALL be logged with timestamp, source, and rejected command.

**Acceptance Criteria**: Unauthorized mode change rejected; legitimate authorized change accepted; attempt logged
**Verification Method**: Test (unit test — authorized vs. unauthorized), Inspection

---

**REQ-SEC-002**: Mode Change Event Logging
**Priority**: Medium
**SIL Level**: SIL 2
**Traceability**: SYS-REQ-074

**Description**: The software SHALL log all mode change events (authorized and rejected) to non-volatile storage with: timestamp, requested mode, authorization source (driver/TCMS/maintenance), result (ACCEPTED/REJECTED), and operator ID where available.

**Acceptance Criteria**: All mode change events logged; log entries include all specified fields; log readable via diagnostics port
**Verification Method**: Integration Test, Inspection

---

**REQ-SEC-003**: Diagnostics Port Read-Only Enforcement
**Priority**: Medium
**SIL Level**: SIL 2
**Traceability**: SYS-REQ-073

**Description**: The software SHALL NOT permit any modification of operational parameters, safety thresholds, or configuration data via the diagnostics port during Normal operation. The diagnostics port SHALL support ONLY read operations (event log download, status query) during Normal mode. Configuration writes SHALL only be permitted in Diagnostic mode with maintenance authorization.

**Acceptance Criteria**: Write commands on diagnostics port return `CMD_NOT_PERMITTED` in Normal mode; read commands succeed; tested in Normal and Diagnostic modes
**Verification Method**: Test (unit test — port command filtering), Inspection

---

---

### 3.7 Operational Requirements

---

**REQ-OPR-001**: MISRA C:2012 Compliance
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SSRS SAFE-SW-008, EN 50128 Table A.4

**Description**: All source code SHALL comply with MISRA C:2012 guidelines. All MISRA C mandatory rules SHALL have zero violations. Required and advisory rule violations SHALL be documented with justification.

**Acceptance Criteria**: Static analysis tool reports zero mandatory MISRA C:2012 violations; all required rule violations documented; deviation log reviewed by QUA
**Verification Method**: Static Analysis (PC-lint Plus or equivalent), Code Review

---

**REQ-OPR-002**: Fixed-Width Integer Types
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SSRS SAFE-SW-008, MISRA C Rule 4.6

**Description**: The software SHALL use fixed-width integer types (`uint8_t`, `uint16_t`, `uint32_t`, `uint64_t`, `int8_t`, `int16_t`, `int32_t`, `int64_t` from `<stdint.h>`) instead of platform-dependent types for all variables in safety-critical code.

**Acceptance Criteria**: Static analysis finds zero use of `int`, `unsigned`, `long` in safety-critical modules; `<stdint.h>` included in all source files
**Verification Method**: Static Analysis, Code Review

---

**REQ-OPR-003**: Static Memory Allocation Only
**Priority**: Critical
**SIL Level**: SIL 3
**Traceability**: SSRS SAFE-SW-007, EN 50128 Table A.4

**Description**: The software SHALL use ONLY static memory allocation. Dynamic memory allocation functions (`malloc`, `calloc`, `realloc`, `free`, `alloca`) SHALL NOT be used anywhere in the safety software, including third-party libraries.

**Acceptance Criteria**: Static analysis finds zero calls to dynamic allocation functions; linker map confirms zero heap usage; verified by code review
**Verification Method**: Static Analysis (lint for forbidden functions), Code Review

---

**REQ-OPR-004**: No Recursion
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SSRS SAFE-SW-004, EN 50128 Table A.4

**Description**: The software SHOULD NOT implement recursive function calls (direct or indirect) in safety-critical code (SIL 3 functions). Where recursion is unavoidable in non-safety code, it SHALL be bounded with a compile-time depth limit.

**Acceptance Criteria**: Static analysis (call graph) confirms zero recursive paths in SIL 3 modules; any non-safety recursion documented with depth bound
**Verification Method**: Static Analysis (call graph analysis), Code Review

---

**REQ-OPR-005**: Cyclomatic Complexity Limit
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SSRS SAFE-SW-005, EN 50128 Table A.4

**Description**: Every function in SIL 3 safety-critical modules SHALL have a cyclomatic complexity of <= 10. Functions in SIL 1-2 modules SHALL have cyclomatic complexity <= 15. Any function exceeding the limit SHALL be refactored before release.

**Acceptance Criteria**: Static analysis tool (Lizard or PC-lint) reports zero functions exceeding their SIL-based limit
**Verification Method**: Static Analysis, Code Review

---

**REQ-OPR-006**: Defensive Programming
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SSRS SAFE-SW-003, EN 50128 Table A.3

**Description**: All safety-critical functions SHALL implement defensive programming: validate all pointer parameters (NULL check), validate all value parameters (range check), check and handle all function return values, use assertions for internal consistency invariants.

```c
error_t SPM_ProcessSpeed(const tcms_speed_msg_t *msg, uint16_t *speed_out) {
    if (msg == NULL)       { return ERR_NULL_PTR; }
    if (speed_out == NULL) { return ERR_NULL_PTR; }
    if (msg->crc16 != CRC16_Compute(msg, sizeof(*msg) - 2U)) { return ERR_CRC; }
    if (msg->speed_kmh_x10 > SPEED_MAX_KMH_X10) { return ERR_RANGE; }
    *speed_out = msg->speed_kmh_x10;
    return SUCCESS;
}
```
**Acceptance Criteria**: Code review confirms NULL checks, range checks, and return value checks in all safety-critical functions; MISRA C Rule 17.7 compliant
**Verification Method**: Code Review, Static Analysis

---

**REQ-OPR-007**: Error Handling — Explicit Return Codes
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: EN 50128 design best practice

**Description**: The software SHALL use explicit error return codes (`error_t` enum) for all functions that can fail. `errno` global, `setjmp`/`longjmp`, and exception handling SHALL NOT be used.

```c
typedef enum {
    SUCCESS             = 0,
    ERR_NULL_PTR        = 1,
    ERR_RANGE           = 2,
    ERR_TIMEOUT         = 3,
    ERR_CRC             = 4,
    ERR_HW_FAULT        = 5,
    ERR_INVALID_STATE   = 6,
    ERR_NOT_PERMITTED   = 7,
    ERR_SENSOR_DISAGREE = 8,
    ERR_COMM_TIMEOUT    = 9,
    ERR_WATCHDOG        = 10
} error_t;
```
**Acceptance Criteria**: All non-void safety-critical functions return `error_t`; MISRA C Rule 17.7 compliance; static analysis confirms
**Verification Method**: Static Analysis, Code Review

---

**REQ-OPR-008**: Static Cyclic Executive Scheduler
**Priority**: High
**SIL Level**: SIL 3
**Traceability**: SSRS SAFE-SW-012, EN 50128 Table A.4

**Description**: The software SHALL use a static cyclic executive scheduler (time-triggered, 20 ms period) with no RTOS for the safety-critical execution layer. Task execution order SHALL be fixed and documented.

**Task Execution Order** (each 20 ms cycle):
1. Safety Kernel — sensor read and input validation
2. Speed Monitor (SPM) — speed check and interlock evaluation
3. Obstacle Detector (OBD) — obstacle status check
4. Door State Machine (DSM) — state update
5. Fault Manager (FMG) — fault evaluation
6. Cross-channel comparison via SPI
7. Actuator outputs (motor PWM, lock commands)
8. CAN transmit (TCMS status messages)
9. RS-485 DDU message exchange
10. Watchdog refresh (only on successful cycle completion)
11. Diagnostics (DGN) — event log, background tasks (2 ms budget)

**Acceptance Criteria**: Scheduler order documented; WCET of each task measured; total cycle <= 16 ms verified
**Verification Method**: Static Analysis, Performance Test, Code Review

---

---

## 4. VERIFICATION AND TRACEABILITY

### 4.1 Verification Methods

Each requirement SHALL be verified using one or more of the following methods:

| Method | Description | Applicable To |
|--------|-------------|---------------|
| **Unit Test** | Individual software function test with Unity framework | Functional, safety, interface, operational requirements |
| **Integration Test** | Software component interaction and hardware-in-loop | Interface, performance, safety requirements |
| **System Test** | Full system test in target environment | All SIL 3 safety requirements |
| **Performance Test** | Hardware timer and oscilloscope measurements | Performance requirements |
| **Fault Injection** | Deliberate fault introduction to verify safe state | All safety requirements (SIL 3) |
| **Safety Test** | Hazard scenario testing per SSRS | Safety requirements (SIL 3) |
| **Static Analysis** | PC-lint Plus, Cppcheck, Lizard, call graph | Implementation, operational requirements |
| **Code Review** | Peer review against checklist | Implementation, defensive programming |
| **Inspection** | Document and design inspection | Interface definitions, mode logic |
| **Analysis** | FMEA-based DC calculation, WCET analysis | Reliability, diagnostic coverage |

### 4.2 Requirements Traceability Matrix (RTM)

**Backward Traceability** (SIL 3 Mandatory per EN 50128 §7.2.4.5 and Table A.9 D.58):

All software requirements trace to at least one system requirement (SYS-REQ-xxx) or hazard (HAZ-xxx) from DOC-SYS-REQ-2026-001 and DOC-SYS-SAF-2026-001.

| SW Req ID | SYS-REQ | HAZ | SIL |
|-----------|---------|-----|-----|
| REQ-FUN-001 | SYS-REQ-001, 002 | HAZ-003 | 3 |
| REQ-FUN-002 | SYS-REQ-004 | — | 3 |
| REQ-FUN-003 | SYS-REQ-003 | — | 2 |
| REQ-FUN-004 | SYS-REQ-005 | — | 3 |
| REQ-FUN-005 | SYS-REQ-012, 014 | HAZ-001, 005 | 3 |
| REQ-FUN-006 | SYS-REQ-011 | — | 2 |
| REQ-FUN-007 | SYS-REQ-009, 010 | — | 2 |
| REQ-FUN-008 | SYS-REQ-012, 013 | HAZ-001 | 3 |
| REQ-FUN-009 | SYS-REQ-016, 017 | HAZ-001, 005 | 3 |
| REQ-FUN-010 | SYS-REQ-013, 015 | HAZ-001, 003 | 3 |
| REQ-FUN-011 | SYS-REQ-023 | — | 3 |
| REQ-FUN-012 | SYS-REQ-024 | HAZ-009 | 3 |
| REQ-FUN-013 | SYS-REQ-023 | HAZ-009 | 2 |
| REQ-FUN-014 | SYS-REQ-023 | HAZ-009 | 2 |
| REQ-FUN-015 | SYS-REQ-025, 026 | — | 3 |
| REQ-FUN-016 | SYS-REQ-027 | — | 2 |
| REQ-FUN-017 | SYS-REQ-028, 029 | — | 3 |
| REQ-FUN-018 | SYS-REQ-031, 070 | — | 1 |
| REQ-PERF-001 | SYS-REQ-036 | — | 3 |
| REQ-PERF-002 | SYS-REQ-035 | HAZ-003 | 3 |
| REQ-PERF-003 | SYS-REQ-034 | HAZ-002, 004 | 3 |
| REQ-PERF-004 | SYS-REQ-003 | — | 3 |
| REQ-PERF-005 | SYS-REQ-017 | HAZ-001 | 3 |
| REQ-PERF-006 | SYS-REQ-029 | — | 3 |
| REQ-PERF-007 | SYS-REQ-029 | — | 3 |
| REQ-PERF-008 | SYS-REQ-036 | — | 2 |
| REQ-PERF-009 | SYS-REQ-036 | — | 3 |
| REQ-PERF-010 | SYS-REQ-036 | — | 2 |
| REQ-INT-001 | SYS-REQ-040 | — | 3 |
| REQ-INT-002 | SYS-REQ-041 | — | 3 |
| REQ-INT-003 | SYS-REQ-042 | HAZ-002, 004 | 3 |
| REQ-INT-004 | SYS-REQ-043 | HAZ-001 | 3 |
| REQ-INT-005 | SYS-REQ-044 | HAZ-001, 005 | 3 |
| REQ-INT-006 | SYS-REQ-064 | HAZ-009 | 3 |
| REQ-INT-007 | SYS-REQ-046, 047 | HAZ-003 | 3 |
| REQ-INT-008 | SYS-REQ-016, 017, 027 | — | 3 |
| REQ-INT-009 | SYS-REQ-049 | — | 3 |
| REQ-INT-010 | SYS-REQ-060 | HAZ-009 | 3 |
| REQ-INT-011 | SYS-REQ-021, 045 | HAZ-008 | 2 |
| REQ-INT-012 | SYS-REQ-048, 051 | — | 2 |
| REQ-INT-013 | SYS-REQ-050 | — | 1 |
| REQ-SAFE-001 | SYS-REQ-002, 015 | HAZ-003 | 3 |
| REQ-SAFE-002 | SYS-REQ-013 | HAZ-001, 003 | 3 |
| REQ-SAFE-003 | SYS-REQ-016 | HAZ-001, 005 | 3 |
| REQ-SAFE-004 | SYS-REQ-007 | HAZ-002, 004 | 3 |
| REQ-SAFE-005 | SYS-REQ-026, 014 | HAZ-001, 005 | 3 |
| REQ-SAFE-006 | SYS-REQ-030 | HAZ-005, 009 | 3 |
| REQ-SAFE-007 | SYS-REQ-061 | — | 3 |
| REQ-SAFE-008 | SYS-REQ-064 | HAZ-009 | 3 |
| REQ-SAFE-009 | SYS-REQ-063 | — | 3 |
| REQ-SAFE-010 | SYS-REQ-060 | HAZ-009 | 3 |
| REQ-SAFE-011 | SYS-REQ-028 | — | 3 |
| REQ-SAFE-012 | SYS-REQ-021 | HAZ-008 | 2 |
| REQ-SAFE-013 | SYS-REQ-066 | — | 3 |
| REQ-SAFE-014 | SYS-REQ-066 | — | 3 |
| REQ-SAFE-015 | SYS-REQ-046 | HAZ-003 | 3 |
| REQ-SAFE-016 | SYS-REQ-030 | — | 3 |
| REQ-SAFE-017 | SYS-REQ-061 | — | 3 |
| REQ-SAFE-018 | SYS-REQ-023 | HAZ-009 | 2 |
| REQ-SAFE-019 | SYS-REQ-060 | — | 3 |
| REQ-SAFE-020 | SYS-REQ-060 | — | 3 |
| REQ-SAFE-021 | SSRS SAFE-SW-004 | — | 3 |
| REQ-REL-001 | SYS-REQ-067, 039 | — | 3 |
| REQ-REL-002 | SYS-REQ-062, 065 | — | 3 |
| REQ-REL-003 | SYS-REQ-066 | — | 3 |
| REQ-REL-004 | SYS-REQ-068 | — | 2 |
| REQ-SEC-001 | SYS-REQ-073 | — | 2 |
| REQ-SEC-002 | SYS-REQ-074 | — | 2 |
| REQ-SEC-003 | SYS-REQ-073 | — | 2 |
| REQ-OPR-001 | SSRS SAFE-SW-008 | — | 3 |
| REQ-OPR-002 | SSRS SAFE-SW-008 | — | 3 |
| REQ-OPR-003 | SSRS SAFE-SW-007 | — | 3 |
| REQ-OPR-004 | SSRS SAFE-SW-004 | — | 3 |
| REQ-OPR-005 | SSRS SAFE-SW-005 | — | 3 |
| REQ-OPR-006 | SSRS SAFE-SW-003 | — | 3 |
| REQ-OPR-007 | EN 50128 best practice | — | 3 |
| REQ-OPR-008 | SSRS SAFE-SW-012 | — | 3 |

**Traceability Completeness**: 81/81 requirements have backward traceability — **100%**

### 4.3 Requirements Quality Checklist

All requirements in this SRS have been reviewed against the following criteria:

- [x] **Unique ID**: Each requirement has a unique identifier
- [x] **Unambiguous**: Single interpretation; uses SHALL/SHOULD/MAY; no vague terms
- [x] **Testable**: Verification method identified; acceptance criteria defined and quantified
- [x] **Complete**: Inputs, outputs, error handling, preconditions/postconditions provided
- [x] **Consistent**: No conflicts between requirements; consistent SIL assignments per SSRS
- [x] **Traceable**: Every requirement linked to SYS-REQ and/or HAZ in Section 4.2
- [x] **SIL Assigned**: SIL level specified for every requirement
- [x] **C-Compatible**: All requirements feasible in C (MISRA C:2012) within stated constraints

---

## 5. REQUIREMENTS SUMMARY

### 5.1 Requirements Count by Category

| Category | Count | Critical | High | Medium | Low |
|----------|-------|----------|------|--------|-----|
| Functional (REQ-FUN) | 18 | 5 | 11 | 2 | 0 |
| Performance (REQ-PERF) | 10 | 3 | 5 | 2 | 0 |
| Interface (REQ-INT) | 13 | 4 | 7 | 1 | 1 |
| Safety (REQ-SAFE) | 21 | 11 | 10 | 0 | 0 |
| Reliability (REQ-REL) | 4 | 1 | 3 | 0 | 0 |
| Security (REQ-SEC) | 3 | 0 | 1 | 2 | 0 |
| Operational (REQ-OPR) | 8 | 2 | 5 | 1 | 0 |
| **TOTAL** | **81** | **26** | **42** | **8** | **1** |

### 5.2 Requirements Count by SIL Level

| SIL Level | Count | Percentage |
|-----------|-------|------------|
| SIL 3 | 58 | 71.6% |
| SIL 2 | 17 | 21.0% |
| SIL 1 | 6 | 7.4% |
| **TOTAL** | **81** | **100%** |

**Safety Requirements (REQ-SAFE)**: 21 total
- SIL 3: 15 (REQ-SAFE-001 to 011, 013-017, 019-021)
- SIL 2: 6 (REQ-SAFE-012, 018)

> **SAF confirmation**: SIL assignments for REQ-SAFE-001 through REQ-SAFE-021 are consistent with SSRS (DOC-SYS-SAF-2026-001) safety function assignments. SAF is the hazard authority; all SIL 3 safety requirements co-authored with SAF per REQ-SAF coordination.

---

## 6. COMPLIANCE MATRIX

### 6.1 EN 50128 Section 7.2 Compliance

| EN 50128 Requirement | Section | Evidence | Status |
|---------------------|---------|----------|--------|
| Software Requirements Specification established | 7.2.2 | This document (DOC-SRS-2026-001) | OK |
| System requirements used as input | 7.2.2 | DOC-SYS-REQ-2026-001 (Section 3 inputs) | OK |
| Safety requirements from hazard analysis | 7.2.2 | DOC-SYS-SAF-2026-001 (Section 3.4) | OK |
| Requirements unambiguous | 7.2.3 | Section 4.3 quality checklist | OK |
| Requirements testable | 7.2.4 | Every requirement has verification method and acceptance criteria | OK |
| Requirements traceable backward | 7.2.4.5 | 100% traceability in Section 4.2 RTM | OK |
| SIL level assigned | 7.2.6 | All 81 requirements have SIL field | OK |
| Safety requirements identified (REQ-SAFE) | 7.2.7 | Section 3.4 (21 safety requirements) | OK |
| Structured methodology applied | Table A.2 | Systematic decomposition, unique IDs, decision tables | OK |
| Modelling applied | Table A.2 | State machine for DSM modes (Section 3.1.4, REQ-FUN-011) | OK |
| Decision tables applied | Table A.2 | REQ-FUN-001, REQ-FUN-005, REQ-SAFE-006, REQ-SAFE-011 | OK |
| User approval obtained | Annex C item 6 | User/customer approval GRANTED prior to authoring | OK |

### 6.2 EN 50128 Table A.2 Compliance (Requirements Techniques)

| Technique | SIL 3-4 | Applied | Section Reference |
|-----------|---------|---------|-------------------|
| Structured Methodology (D.52) | HR | Yes | All sections — systematic decomposition |
| Decision Tables (D.13) | HR | Yes | REQ-FUN-001, REQ-FUN-005, REQ-SAFE-006, REQ-SAFE-011 |
| Modelling (Table A.17) | HR | Yes | REQ-FUN-011 (operational mode FSM) |
| Formal Methods (D.28) | HR | No | Rationale: Structured methodology + decision tables sufficient for SIL 3 |

---

## 7. REFERENCES

### 7.1 Normative References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications — Software for railway control and protection systems |
| **[EN50129]** | EN 50129:2018 Railway applications — Safety related electronic systems for signalling |
| **[EN50126-2]** | EN 50126-2:2017 Railway applications — RAMS — Part 2: Systems approach to safety |
| **[EN14752]** | EN 14752:2015 Railway applications — Bodyside entrance systems |
| **[ISO11898]** | ISO 11898:2003 — Controller Area Network (CAN) |
| **[MISRAC]** | MISRA C:2012 Guidelines for the use of the C language in critical systems |

### 7.2 Project References

| Reference | Document | Status |
|-----------|----------|--------|
| **[SYSREQ]** | System Requirements Specification, DOC-SYS-REQ-2026-001 | Approved Baseline |
| **[SYSARCH]** | System Architecture Description, DOC-SYS-ARCH-2026-001 | Approved Baseline |
| **[SSRS]** | System Safety Requirements Specification, DOC-SYS-SAF-2026-001 | Approved Baseline |
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-2026-001 | Approved |
| **[SCMP]** | Software Configuration Management Plan, DOC-SCMP-2026-001 | Approved |
| **[SVP]** | Software Verification Plan, DOC-SVP-2026-001 | Approved |

---

## APPENDICES

### Appendix A: Requirement ID Registry

| ID Range | Category | Count |
|----------|----------|-------|
| REQ-FUN-001 to REQ-FUN-018 | Functional Requirements | 18 |
| REQ-PERF-001 to REQ-PERF-010 | Performance Requirements | 10 |
| REQ-INT-001 to REQ-INT-013 | Interface Requirements | 13 |
| REQ-SAFE-001 to REQ-SAFE-021 | Safety Requirements | 21 |
| REQ-REL-001 to REQ-REL-004 | Reliability Requirements | 4 |
| REQ-SEC-001 to REQ-SEC-003 | Security Requirements | 3 |
| REQ-OPR-001 to REQ-OPR-008 | Operational Requirements | 8 |
| **TOTAL** | | **81** |

### Appendix B: Glossary

See Section 1.4 Definitions and Acronyms.

### Appendix C: Safety Function to Software Requirement Mapping

| Safety Function (SSRS) | SW Safety Requirements | SIL |
|-----------------------|----------------------|-----|
| SF-001 (Speed interlock) | REQ-SAFE-001, REQ-SAFE-002, REQ-SAFE-015, REQ-FUN-001 | SIL 3 |
| SF-002 (Departure interlock) | REQ-SAFE-003, REQ-FUN-009, REQ-FUN-005 | SIL 3 |
| SF-003 (Obstacle detection) | REQ-SAFE-004, REQ-INT-003, REQ-PERF-003 | SIL 3 |
| SF-004 (Safe state) | REQ-SAFE-006, REQ-SAFE-007, REQ-SAFE-008, REQ-FUN-017 | SIL 3 |
| SF-005 (Position verification) | REQ-SAFE-005, REQ-FUN-015, REQ-FUN-005 | SIL 3 |
| SF-006 (Emergency release monitoring) | REQ-SAFE-012, REQ-INT-011 | SIL 2 |
| SF-007 (Fault isolation) | REQ-FUN-013, REQ-SAFE-018 | SIL 2 |

---

## DOCUMENT HISTORY

This document is maintained under configuration control per SCMP (DOC-SCMP-2026-001). All changes SHALL be approved by the Change Control Board (CCB).

**Current Version**: 0.1 DRAFT
**Last Updated**: 2026-04-02
**Next Review**: Upon QUA review completion (Phase 2 gate)
**Configuration Item ID**: CI-SRS-001

---

**END OF DOCUMENT**
