# FMEA Report — Software Architecture Failure Mode and Effects Analysis

**Document Type**: Cross-cutting safety artifact (outside Annex C Table C.1)  
**Standard**: EN 50128:2011 §7.1, §6.3; EN 50126-1:2017 §6.3, Annex D.27  
**Template version**: 1.0

---

## Document Control

| Field | Value |
|-------|-------|
| **Document ID** | DOC-FMEA-2026-001 |
| **Version** | 0.1 |
| **Date** | 2026-04-02 |
| **Project** | TDC (Train Door Control System) |
| **SIL Level** | SIL 3 |
| **Author** | SAF (Safety Engineer) |
| **Status** | Draft |
| **Input: SAS** | DOC-SAS-2026-001 v0.1 DRAFT |
| **Input: SRS** | DOC-SRS-2026-001 v0.1 DRAFT |
| **Input: Hazard Log** | DOC-HAZLOG-2026-001 v0.2 |

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 0.1 | 2026-04-02 | SAF | Initial FMEA — Phase 3 software architecture analysis; 8 components; 48 failure modes |

## Approvals

> **Note**: FMEA Report is a cross-cutting safety artifact. Per SIL 3 Track B process:
> VER reviews as part of Architecture Verification (item 14); VAL reviews for validation evidence (item 25).

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author** (SAF) | Safety Engineer | DRAFT | 2026-04-02 |
| **QUA Review** | Quality Assurance | ___ | ___ |
| **VER Review** | Verifier | ___ | ___ |
| **VMGR Approval** | V&V Manager | ___ | ___ |

---

## 1. Introduction

### 1.1 Purpose

This FMEA Report documents the bottom-up Failure Mode and Effects Analysis (FMEA) performed on the **TDC software architecture** as defined in the Software Architecture Specification (DOC-SAS-2026-001). This analysis is a Phase 3 SAF activity per EN 50128 §7.1 and EN 50126-1:2017 Annex D.27.

The FMEA:
- Identifies failure modes for each of the 8 architectural software components
- Assesses each failure mode's effect on safety functions (SF-001 through SF-005)
- Calculates Risk Priority Numbers (RPN = Severity × Occurrence × Detection) to prioritise mitigation
- Validates that architectural mitigations in the SAS address all failure modes
- Updates the Hazard Log (DOC-HAZLOG-2026-001) with Phase 3 findings
- Confirms that all 15 SEEA findings from Hazard Log §5 have architectural mitigations

### 1.2 Scope

**Components analysed**: All 8 software architectural components per SAS §4:

| Comp | Name | SIL | Phase 3 FMEA Scope |
|------|------|-----|-------------------|
| SKN | Safety Kernel | SIL 3 | Central gating authority; departure interlock; safe state |
| SPM | Speed Monitor | SIL 3 | Speed data validity; interlock flag management |
| OBD | Obstacle Detector | SIL 3 | Sensor polling; reversal authority |
| DSM | Door State Machine | SIL 3 | Per-door FSM; 2oo2 sensor voting |
| FMG | Fault Manager | SIL 3 | Fault aggregation; escalation |
| TCI | TCMS Interface | SIL 3 | CAN integrity; timeout; sequence counter |
| DGN | Diagnostics | SIL 1 | Event log; diagnostic port |
| HAL | HW Abstraction Layer | SIL 3 | All hardware I/O; watchdog |

**Failure mode categories analysed** (per SEEA technique, Table A.8 entry 5, and architectural review):
- Output stuck-at (value frozen)
- Output incorrect (wrong value computed)
- Component crash / no output
- Component hang / deadlock
- Data corruption (CRC failure)
- Timing violation (overrun or underrun)
- Interface failure (CAN timeout, SPI error, GPIO fault)
- Incorrect state transition
- NULL pointer / uninitialized value (from Hazard Log §5 SEEA)
- Integer overflow / underflow (from Hazard Log §5 SEEA)

### 1.3 FMEA Severity, Occurrence, and Detection Scales

**Severity (S)**:

| Score | Level | Description |
|-------|-------|-------------|
| 9–10 | Catastrophic | Death or multiple serious injuries |
| 7–8 | Critical | Serious injury possible |
| 4–6 | Moderate | Minor injury or service disruption |
| 1–3 | Minor | No injury; minimal inconvenience |

**Occurrence (O)**:

| Score | Level | Probability |
|-------|-------|-------------|
| 9–10 | Frequent | Multiple failures per year |
| 7–8 | Probable | Once per year or more |
| 4–6 | Occasional | Several times in system lifetime |
| 1–3 | Remote | Unlikely in system lifetime |

**Detection (D)** (lower = better — more easily detected):

| Score | Level | Description |
|-------|-------|-------------|
| 1–2 | Always detected | Multiple independent detection mechanisms |
| 3–4 | Likely detected | Primary detection mechanism reliable |
| 5–6 | Possibly detected | Detection may be delayed |
| 7–8 | Difficult to detect | Limited detection capability |
| 9–10 | Undetectable | No detection mechanism |

**RPN Threshold**: RPN ≥ 100 requires mandatory mitigation action. RPN ≥ 200 is a critical finding.

### 1.4 SEEA Integration

The FMEA incorporates all 15 SEEA fault modes from Hazard Log §5. These are marked `[SEEA]` in the FMEA table. The FMEA verifies that each SEEA fault mode has a corresponding architectural mitigation in SAS Appendix B.

---

## 2. FMEA — Component Analysis

### 2.1 COMP-001: Safety Kernel (SKN) — SIL 3

**Safety functions**: SF-002 (Departure Interlock), SF-004 (Safe State on Fault), SF-005 (Door Position Verification)  
**Hazard allocation**: SW-HAZ-001, SW-HAZ-003, SW-HAZ-006

| FM-ID | Module | Failure Mode | Local Effect | System Effect | S | O | D | RPN | HAZ Link | Architectural Mitigation | Status |
|-------|--------|--------------|--------------|---------------|---|---|---|-----|----------|--------------------------|--------|
| FM-SKN-001 | SKN | Output stuck-at: `safe_state_active` frozen at 0 (no safe state asserted when required) | Safe state not entered on critical fault | Door may open while moving; false lock indication persists | 10 | 2 | 2 | 40 | SW-HAZ-001, SW-HAZ-003 | Cross-channel comparison: Channel B SKN independently asserts safe state if Channel A fails; hardware watchdog resets MCU-A | ✅ Mitigated |
| FM-SKN-002 | SKN | Output stuck-at: `safe_state_active` frozen at 1 (spurious permanent safe state) | Doors permanently locked; cannot open at station | Service disruption; secondary passenger egress risk | 5 | 2 | 3 | 30 | SW-HAZ-005 | FMG stuck-state detection: max safe-state dwell time before degraded mode; driver override with TCMS authorization (SAS §4.6) | ✅ Mitigated |
| FM-SKN-003 | SKN | Cross-channel SPI mismatch not detected (comparison logic fault) | Divergent channel states not detected | Both channels operate independently with no reconciliation — safety guarantee lost | 10 | 1 | 3 | 30 | SW-HAZ-001, SW-HAZ-003 | CRC-16 on `cross_channel_state_t` provides independent integrity check; hardware watchdog enforces cycle completion | ✅ Mitigated |
| FM-SKN-004 | SKN | `departure_interlock_ok` asserted before all doors CLOSED_AND_LOCKED | Premature departure signal to TCMS | Train departs with door not confirmed locked | 10 | 1 | 2 | 20 | SW-HAZ-003 | SKN only asserts interlock when ALL DSM instances report CLOSED_AND_LOCKED AND cross-channel comparison passes (2oo2 gate) | ✅ Mitigated |
| FM-SKN-005 [SEEA] | SKN | Division by zero in duty cycle calculation | SKN produces NaN or processor trap | Safety kernel may halt; motor command undefined | 9 | 1 | 2 | 18 | SW-HAZ-001, SW-HAZ-003 | Non-zero denominator guard before all divisions (SAS §4.2 constraint 3; MISRA C Rule 15.5) | ✅ Mitigated |
| FM-SKN-006 [SEEA] | SKN | Uninitialized `departure_interlock_ok` flag (defaults to "clear") | Interlock defaults to "all locked" at startup | Departure permitted before door confirmation | 10 | 1 | 2 | 20 | SW-HAZ-003 | Flag initialized to LOCKED_UNKNOWN at startup; departure signal only output when flag = ALL_LOCKED (SAS §4.2 constraint 4) | ✅ Mitigated |
| FM-SKN-007 | SKN | Memory integrity CRC check not executed on schedule | Safety-critical data corruption undetected for > 100 ms | Corrupted door state or speed value used in safety decision | 9 | 1 | 3 | 27 | SW-HAZ-008 | Hardware watchdog enforces cycle completion — missed CRC check implies missed watchdog refresh → hardware reset; memory integrity check is in main cycle (SAS §6.4) | ✅ Mitigated |
| FM-SKN-008 | SKN | Stack canary overwritten not detected | Stack corruption proceeds undetected | Arbitrary code execution or data corruption in safety-critical path | 9 | 1 | 2 | 18 | SW-HAZ-008 | Stack canary checked by SKN every cycle; mismatch → immediate safe state; static stack sizing prevents overflow under normal operation (SAS §6.4, §10) | ✅ Mitigated |

**SKN Critical Findings**: None (all RPN < 100). All failure modes mitigated by dual-channel architecture.

---

### 2.2 COMP-002: Speed Monitor (SPM) — SIL 3

**Safety functions**: SF-001 (Speed Interlock)  
**Hazard allocation**: SW-HAZ-001, SW-HAZ-007

| FM-ID | Module | Failure Mode | Local Effect | System Effect | S | O | D | RPN | HAZ Link | Architectural Mitigation | Status |
|-------|--------|--------------|--------------|---------------|---|---|---|-----|----------|--------------------------|--------|
| FM-SPM-001 | SPM | Output incorrect: `speed_interlock_active` = 0 when speed > 5 km/h (missed interlock) | Speed gate not set | Door opening permitted while train in motion | 10 | 1 | 2 | 20 | SW-HAZ-001 | Cross-channel: Channel B SPM independently computes interlock; disagreement → safe state (SAS §6.2, §7.2) | ✅ Mitigated |
| FM-SPM-002 | SPM | Stale CAN speed data used without timeout detection | SPM uses outdated speed reading | Interlock may act on incorrect speed; door opens when train moving | 10 | 2 | 2 | 40 | SW-HAZ-007 | Timestamp validation on every CAN message; timeout = 200 ms → UNKNOWN → assume moving (SAS §4.3 constraint 4) | ✅ Mitigated |
| FM-SPM-003 [SEEA] | SPM | NULL pointer dereference on CAN speed buffer | No speed output | Speed interlock disabled; door may open while moving | 10 | 1 | 2 | 20 | SW-HAZ-001, SW-HAZ-007 | NULL guard before buffer access; NULL → assume speed HIGH (fail-safe) (SAS §4.3 constraint 2) | ✅ Mitigated |
| FM-SPM-004 [SEEA] | SPM | Integer overflow on speed value from CAN (wraps to 0 or negative) | Speed = 0; system interprets as stationary | Door open permitted while train in motion | 10 | 1 | 2 | 20 | SW-HAZ-001, SW-HAZ-007 | Range check: valid speed 0–3000 (km/h × 10); out-of-range → reject, log, treat as UNKNOWN (SAS §4.3 constraint 3) | ✅ Mitigated |
| FM-SPM-005 | SPM | CAN speed CRC failure not rejected (incorrect validation) | Corrupt speed value accepted as valid | Speed interlock may act on corrupt speed data | 10 | 1 | 2 | 20 | SW-HAZ-007 | TCI performs CRC-16 validation before passing frame to SPM; CRC failure → discard + timeout path (SAS §4.7) | ✅ Mitigated |
| FM-SPM-006 | SPM | Incorrect speed threshold comparison (e.g., > vs. ≥ 5 km/h) | Edge case: speed = 5.0 km/h not inhibited | Door opens at exactly 5 km/h — marginal safety violation | 8 | 1 | 4 | 32 | SW-HAZ-001 | Code review (VER) verifies boundary condition; unit test TC-SPM-007 specifically tests speed = 50 (5.0 km/h × 10) — must inhibit (CCF-001 mitigation: independent VER review) | ✅ Mitigated |

**SPM Critical Findings**: None (all RPN < 100). Dual-channel architecture is primary safety net.

---

### 2.3 COMP-003: Obstacle Detector (OBD) — SIL 3

**Safety functions**: SF-003 (Obstacle Detection and Reversal)  
**Hazard allocation**: SW-HAZ-002

| FM-ID | Module | Failure Mode | Local Effect | System Effect | S | O | D | RPN | HAZ Link | Architectural Mitigation | Status |
|-------|--------|--------------|--------------|---------------|---|---|---|-----|----------|--------------------------|--------|
| FM-OBD-001 | OBD | Obstacle not detected: sensor polling missed in cycle | Obstacle detection delayed > 20 ms | Obstacle response time may exceed 150 ms budget; passenger crushing risk | 8 | 2 | 3 | 48 | SW-HAZ-002 | ISR (sub-1 ms) provides independent detection path; 20 ms poll is backup; execution time monitoring by FMG (SAS §4.4 constraint 4) | ✅ Mitigated |
| FM-OBD-002 | OBD | Reversal command not issued within 100 ms of detection | Detection occurs but reversal delayed | Obstacle response time exceeds 150 ms REQ-PERF-003 budget | 8 | 2 | 3 | 48 | SW-HAZ-002 | ISR path triggers immediate reversal (sub-1 ms); polled path has ≤ 20 ms + processing latency = ≤ 25 ms; WCET budget: OBD = 0.5 ms (SAS §11) | ✅ Mitigated |
| FM-OBD-003 [SEEA] | OBD | NULL pointer dereference on obstacle sensor data | No obstacle detection output | Obstacle not detected; door closes on passenger | 8 | 1 | 2 | 16 | SW-HAZ-002 | NULL check before sensor read; NULL → treat as OBSTACLE_DETECTED (fail-safe) (SAS §4.4 constraint 2) | ✅ Mitigated |
| FM-OBD-004 [SEEA] | OBD | Integer overflow on force sensor current reading | Force value overflows; comparison bypassed | Excessive closing force not detected | 8 | 1 | 2 | 16 | SW-HAZ-002 | Saturating arithmetic: force value capped at MAX_FORCE before comparison (SAS §4.4 constraint 3) | ✅ Mitigated |
| FM-OBD-005 [SEEA] | OBD | Timing fault: OBD task overruns 25 ms execution budget | Obstacle detection delayed beyond 100 ms software budget | Obstacle response time violation | 8 | 2 | 2 | 32 | SW-HAZ-002 | Execution time monitoring by FMG; if OBD overruns > 25 ms → safe state (SAS §4.4 constraint 4) | ✅ Mitigated |
| FM-OBD-006 | OBD | Obstacle sensor self-test failure at startup not detected | Faulty obstacle sensor enters service undetected | Door closing disabled correctly, BUT sensor fault not reported to TCMS | 6 | 2 | 3 | 36 | SW-HAZ-002 | Sensor self-test at each cycle; sensor fault → immediate safe state (door re-opens) (SAS §4.4 implicit in SEEA) | ✅ Mitigated |
| FM-OBD-007 | OBD | False positive obstacle detection (spurious reversal during closing) | Door reversal when no obstacle present | Service disruption; retry counter increments; after 3 retries → fault | 4 | 3 | 3 | 36 | SW-HAZ-005 | OBD uses 1oo2 (either sensor triggers reversal) — conservative but may produce false positives; FMG retry counter limits disruption (SAS §4.4 constraint 1); aligned with SW-HAZ-005 (spurious safe state) | ✅ Mitigated |

**OBD Critical Findings**: None (all RPN < 100).

---

### 2.4 COMP-004: Door State Machine (DSM) — SIL 3

**Safety functions**: SF-002 (Departure Interlock), SF-005 (Door Position Verification)  
**Hazard allocation**: SW-HAZ-003, SW-HAZ-004

| FM-ID | Module | Failure Mode | Local Effect | System Effect | S | O | D | RPN | HAZ Link | Architectural Mitigation | Status |
|-------|--------|--------------|--------------|---------------|---|---|---|-----|----------|--------------------------|--------|
| FM-DSM-001 [SEEA] | DSM | State machine stuck-at (e.g., stuck in OPENING state) | Door does not complete transition; lock cannot be confirmed | Departure interlock never asserted; or CLOSING never reached → obstacle undetected | 9 | 2 | 2 | 36 | SW-HAZ-003, SW-HAZ-004 | Max dwell timeout per state: OPENING = 4000 ms, CLOSING = 10000 ms; timeout → FAULT state → FMG escalation → safe state (SAS §4.5 constraint 1; DSM FSM table) | ✅ Mitigated |
| FM-DSM-002 [SEEA] | DSM | Uninitialized lock status variable at startup | Lock status undefined on first check | Departure interlock may read uninitialized = "locked" | 10 | 1 | 2 | 20 | SW-HAZ-003 | Explicit initialization to LOCKED_UNKNOWN at startup (SAS §4.5 constraint 3; MISRA Rule 9.3) | ✅ Mitigated |
| FM-DSM-003 [SEEA] | DSM | Array out-of-bounds access on `door_states[door_id]` | Wrong door's state read or overwritten | Incorrect lock status reported for platform-side door | 10 | 1 | 2 | 20 | SW-HAZ-003, SW-HAZ-004 | Bounds check: 0 ≤ door_id < MAX_DOORS before any array access (SAS §4.5 constraint 2) | ✅ Mitigated |
| FM-DSM-004 | DSM | CLOSED_AND_LOCKED state set with only 1oo2 sensor agreement | Door declared locked when only one sensor confirms | False lock indication; departure interlock asserted prematurely | 10 | 1 | 2 | 20 | SW-HAZ-003 | 2oo2 × 2oo2 gate: CLOSED_AND_LOCKED only when BOTH position AND BOTH lock sensors agree (SAS §4.5 constraint 4) | ✅ Mitigated |
| FM-DSM-005 | DSM | Position sensor timeout not triggering UNKNOWN state | Stale position data used without fault | Incorrect door state reported; departure interlock may be asserted with stale data | 9 | 2 | 2 | 36 | SW-HAZ-004 | Position sensor timeout (100 ms) → assume "door open" (REQ-SAFE-011; SAS §4.5, SAS §9.2) | ✅ Mitigated |
| FM-DSM-006 | DSM | Door open command processed when `speed_interlock_active` = 1 | Door opens while train in motion | Passenger fall hazard | 10 | 1 | 2 | 20 | SW-HAZ-001 | DSM gate: no open command processed when `speed_interlock_active` = 1 (SAS §4.5 constraint 5) | ✅ Mitigated |
| FM-DSM-007 | DSM | Emergency release state not latched after activation | Emergency release resets spontaneously | Departure may proceed with emergency release still active | 7 | 1 | 3 | 21 | SW-HAZ-009 | DSM state machine: emergency release state latched until explicit maintenance reset (REQ-SAFE-020; SAS §9.2 allocation) | ✅ Mitigated |

**DSM Critical Findings**: None (all RPN < 100). 2oo2 × 2oo2 voting is robust against single sensor failure.

---

### 2.5 COMP-005: Fault Manager (FMG) — SIL 3

**Safety functions**: SF-004 (Safe State on Fault)  
**Hazard allocation**: SW-HAZ-005, SW-HAZ-006

| FM-ID | Module | Failure Mode | Local Effect | System Effect | S | O | D | RPN | HAZ Link | Architectural Mitigation | Status |
|-------|--------|--------------|--------------|---------------|---|---|---|-----|----------|--------------------------|--------|
| FM-FMG-001 [SEEA] | FMG | State machine stuck-at in FAULT_ACTIVE (permanent safe state) | FMG holds safe state permanently after fault cleared | Passengers trapped; cannot open doors at station | 5 | 2 | 3 | 30 | SW-HAZ-005 | Max safe-state dwell time before degraded mode; driver override with TCMS authorization (SAS §4.6 constraint 2) | ✅ Mitigated |
| FM-FMG-002 [SEEA] | FMG | Uninitialized fault counter at startup | Fault counter = random; spurious or missed fault escalation | Incorrect fault management decisions; spurious safe state or missed escalation | 7 | 1 | 2 | 14 | SW-HAZ-005 | Explicit initialization to 0 at startup and after safe state recovery (SAS §4.6 constraint 1) | ✅ Mitigated |
| FM-FMG-003 | FMG | Critical fault not escalated to safe state (misclassification) | Fault flag set but safe state not triggered | Safety function continues operating with detected fault — undetected single-point failure | 10 | 1 | 3 | 30 | SW-HAZ-001, SW-HAZ-002, SW-HAZ-003 | FMG fault classification table is explicit (SAS §4.6): "Speed interlock defeat → CRITICAL → immediate safe state"; VER code review verifies classification | ✅ Mitigated |
| FM-FMG-004 | FMG | Selective door disablement removes speed interlock for disabled door | Disabled door speed interlock bypassed | Door opens while moving if disabled door open command issued | 10 | 1 | 2 | 20 | SW-HAZ-010 | FMG constraint: selective disablement does NOT remove speed interlock (REQ-SAFE-013; SAS §4.6 constraint 3) | ✅ Mitigated |
| FM-FMG-005 | FMG | Execution time overrun not detected for other components | Component overrun not flagged to FMG | Timing violation may propagate; watchdog may be missed | 8 | 2 | 3 | 48 | SW-HAZ-006 | FMG receives execution time overrun flags from each component; hardware watchdog provides ultimate timing backstop (SAS §7.4 step 7) | ✅ Mitigated |

**FMG Critical Findings**: None (all RPN < 100).

---

### 2.6 COMP-006: TCMS Interface (TCI) — SIL 3

**Safety functions**: SF-001 (CAN speed data integrity)  
**Hazard allocation**: SW-HAZ-007

| FM-ID | Module | Failure Mode | Local Effect | System Effect | S | O | D | RPN | HAZ Link | Architectural Mitigation | Status |
|-------|--------|--------------|--------------|---------------|---|---|---|-----|----------|--------------------------|--------|
| FM-TCI-001 [SEEA] | TCI | NULL pointer on CAN receive buffer | CAN message dropped silently | Speed data or TCMS command lost; system acts on stale data | 10 | 1 | 2 | 20 | SW-HAZ-007 | NULL check on receive buffer; NULL → safety messages never dropped; non-safety: oldest discarded (SAS §4.7 constraint 1–2) | ✅ Mitigated |
| FM-TCI-002 [SEEA] | TCI | Sequence counter overflow: counter wraps to 0; replayed message accepted | Old or duplicate TCMS command executed | Stale speed data or replayed command processed | 8 | 1 | 2 | 16 | SW-HAZ-007 | Sequence counter overflow: delta checked modulo 256 (SAS §4.7 constraint 3) | ✅ Mitigated |
| FM-TCI-003 | TCI | CAN timeout not detected (200 ms threshold missed) | Stale speed data used beyond 200 ms | Speed interlock may operate on stale speed; door opens while moving | 10 | 1 | 2 | 20 | SW-HAZ-007 | CAN timeout 200 ms → SPM notified "no speed" → `speed_interlock_active` = 1 → inhibit open (SAS §4.7 constraint 4) | ✅ Mitigated |
| FM-TCI-004 | TCI | CRC-16 failure not rejected (corrupt CAN message accepted) | Corrupt speed or command data processed | Speed interlock or door command based on corrupt data | 10 | 1 | 2 | 20 | SW-HAZ-007 | CRC mismatch → discard message, log, treat as timeout (REQ-SAFE-016; SAS §4.7 constraint 1) | ✅ Mitigated |
| FM-TCI-005 | TCI | Departure interlock signal transmitted incorrectly (CAN 0x200) | TCMS receives incorrect door-locked status | Train departs with door not confirmed locked | 10 | 1 | 2 | 20 | SW-HAZ-003 | TCI transmits CAN 0x200 only when SKN asserts `departure_interlock_ok`; CRC-16 on transmission (SAS §5.1 IF-016) | ✅ Mitigated |
| FM-TCI-006 | TCI | CAN bus-off condition (tx error counter = 255) | TCI cannot transmit departure interlock or fault reports | TCMS receives no status — may assume all-clear | 8 | 2 | 2 | 32 | SW-HAZ-007 | CAN bus-off → TCI reports to FMG as CAN fault → FMG escalates to safe state; TCMS has independent bus-off supervision at system level | ✅ Mitigated |

**TCI Critical Findings**: None (all RPN < 100).

---

### 2.7 COMP-007: Diagnostics (DGN) — SIL 1

**Safety functions**: None (SIL 1 — event logging only)  
**Hazard allocation**: None (observability support for SW-HAZ-001 through SW-HAZ-010)

| FM-ID | Module | Failure Mode | Local Effect | System Effect | S | O | D | RPN | HAZ Link | Architectural Mitigation | Status |
|-------|--------|--------------|--------------|---------------|---|---|---|-----|----------|--------------------------|--------|
| FM-DGN-001 | DGN | Event log buffer overrun or CRC failure | Event log entries lost or corrupted | Loss of diagnostic evidence; no safety impact (SIL 1) | 3 | 3 | 4 | 36 | None | Circular buffer: oldest entries overwritten (not dropped); CRC-16 per entry (SAS §4.8 constraint 1) | ✅ Accepted (SIL 1) |
| FM-DGN-002 | DGN | DGN overruns its cycle budget and blocks safety components | Safety component execution delayed | CRITICAL: If DGN blocks SKN, watchdog may be missed | 9 | 1 | 2 | 18 | SW-HAZ-006 | DGN executes last in cycle (step 11, lowest priority); if DGN overruns → defers to next cycle; safety components NEVER blocked (SAS §4.8 constraint 2–3) | ✅ Mitigated |
| FM-DGN-003 | DGN | Diagnostic port write access during Normal mode | Safety parameter modified via diagnostic port | Safety configuration corruption | 9 | 1 | 2 | 18 | SW-HAZ-008 | Diagnostic port: read-only in Normal mode (SAS §4.8 constraint 4; REQ-INT-013) | ✅ Mitigated |

**DGN Critical Findings**: None (all RPN < 100). DGN isolation from safety path is the primary mitigation.

---

### 2.8 COMP-008: Hardware Abstraction Layer (HAL) — SIL 3

**Safety functions**: Supports SF-001 through SF-005 via hardware I/O  
**Hazard allocation**: SW-HAZ-006 (watchdog), SW-HAZ-008 (memory integrity)

| FM-ID | Module | Failure Mode | Local Effect | System Effect | S | O | D | RPN | HAZ Link | Architectural Mitigation | Status |
|-------|--------|--------------|--------------|---------------|---|---|---|-----|----------|--------------------------|--------|
| FM-HAL-001 | HAL | `HAL_GPIO_ReadPositionSensor` returns incorrect value without error | DSM receives wrong position data | Incorrect door state declared; departure interlock based on wrong state | 10 | 1 | 3 | 30 | SW-HAZ-003, SW-HAZ-004 | 2oo2 sensor voting at DSM level: single sensor fault → UNKNOWN state; cross-channel comparison detects persistent disagreement | ✅ Mitigated |
| FM-HAL-002 | HAL | `HAL_GPIO_ReadObstacleSensor` returns ERR without fail-safe action | Obstacle sensor error not propagated | Obstacle detection may be disabled silently | 8 | 1 | 2 | 16 | SW-HAZ-002 | HAL returns `error_t`; callers MUST check return; OBD maps HAL error → OBSTACLE_DETECTED (fail-safe) (SAS §4.9 constraint 2) | ✅ Mitigated |
| FM-HAL-003 | HAL | `HAL_Watchdog_Refresh` not called within 40 ms cycle | Hardware watchdog times out (50 ms) | Hardware reset of MCU — enters safe state via power-on reset (fail-safe) | 5 | 1 | 1 | 5 | SW-HAZ-006 | Hardware watchdog is independent of software; timeout = hardware reset = safe state (ASSUME-002 + ASSUME-005). This is the intended behavior. | ✅ By design |
| FM-HAL-004 | HAL | `HAL_GPIO_SetLockActuator` HAL error not propagated to FMG | Lock command sent but error not escalated | Lock fault not logged; departure interlock may not reflect true lock state | 10 | 1 | 2 | 20 | SW-HAZ-003 | HAL returns `error_t`; DSM checks return; non-SUCCESS → FMG fault raised (SAS §4.9 constraint 1–2) | ✅ Mitigated |
| FM-HAL-005 | HAL | `HAL_SPI_CrossChannel_Exchange` failure (SPI error, timeout) | Cross-channel state exchange fails | No comparison performed → safety independence lost for that cycle | 10 | 2 | 2 | 40 | SW-HAZ-006 | SPI failure → SKN treats as comparison failure → immediate safe state (SAS §7.3 trigger table: "Cross-channel SPI mismatch → Immediate") | ✅ Mitigated |
| FM-HAL-006 | HAL | HAL contains safety logic (violation of pure driver constraint) | Coupling between HAL and safety decisions | HAL changes may inadvertently modify safety behavior | 8 | 1 | 4 | 32 | All | HAL constraint: "MUST NOT contain safety logic — purely a hardware driver" (SAS §4.9 constraint 3); VER code review enforces boundary | ✅ Mitigated |
| FM-HAL-007 | HAL | Dynamic memory allocation used within HAL (malloc/calloc) | Non-deterministic execution time; potential heap corruption | SIL 3 determinism violated; memory fragmentation over time | 9 | 1 | 2 | 18 | SW-HAZ-008 | Architectural constraint: all HAL buffers statically declared (SAS §4.9 constraint 4; REQ-SAFE-017; MISRA C Rule 21.3) | ✅ Mitigated |

**HAL Critical Findings**: None (all RPN < 100). HAL error propagation and fail-safe defaults are the primary mechanisms.

---

## 3. FMEA Summary

### 3.1 RPN Summary by Component

| Component | SIL | Failure Modes Analysed | Max RPN | Critical (≥200) | High (≥100) | Mitigated | Status |
|-----------|-----|----------------------|---------|-----------------|-------------|-----------|--------|
| SKN | SIL 3 | 8 | 40 | 0 | 0 | 8/8 | ✅ All mitigated |
| SPM | SIL 3 | 6 | 40 | 0 | 0 | 6/6 | ✅ All mitigated |
| OBD | SIL 3 | 7 | 48 | 0 | 0 | 7/7 | ✅ All mitigated |
| DSM | SIL 3 | 7 | 36 | 0 | 0 | 7/7 | ✅ All mitigated |
| FMG | SIL 3 | 5 | 48 | 0 | 0 | 5/5 | ✅ All mitigated |
| TCI | SIL 3 | 6 | 32 | 0 | 0 | 6/6 | ✅ All mitigated |
| DGN | SIL 1 | 3 | 36 | 0 | 0 | 3/3 | ✅ Accepted (SIL 1) |
| HAL | SIL 3 | 7 | 40 | 0 | 0 | 7/7 | ✅ All mitigated |
| **TOTAL** | | **49** | **48** | **0** | **0** | **49/49** | ✅ |

### 3.2 SEEA Validation

All 15 SEEA fault modes from Hazard Log §5 are verified against SAS Appendix B:

| SEEA Module | Fault Mode | FMEA ID | Architectural Mitigation | Validated |
|-------------|-----------|---------|--------------------------|-----------|
| SPM | NULL pointer | FM-SPM-003 | NULL guard; fail-safe HIGH | ✅ |
| SPM | Integer overflow | FM-SPM-004 | Range check 0–3000 | ✅ |
| SPM | Stale data | FM-SPM-002 | Timestamp + 200 ms timeout | ✅ |
| DSM | Stuck-at state | FM-DSM-001 | Max dwell timeout | ✅ |
| DSM | Uninitialized lock status | FM-DSM-002 | Init to LOCKED_UNKNOWN | ✅ |
| DSM | Array out-of-bounds | FM-DSM-003 | Bounds check 0 ≤ id < MAX | ✅ |
| OBD | NULL pointer | FM-OBD-003 | NULL → OBSTACLE_DETECTED | ✅ |
| OBD | Integer overflow (force) | FM-OBD-004 | Saturating arithmetic | ✅ |
| OBD | Timing fault | FM-OBD-005 | FMG overrun detection | ✅ |
| FMG | Stuck-at FAULT_ACTIVE | FM-FMG-001 | Max dwell + driver override | ✅ |
| FMG | Uninitialized fault counter | FM-FMG-002 | Init to 0 at startup | ✅ |
| SKN | Division by zero | FM-SKN-005 | Non-zero denominator guard | ✅ |
| SKN | Uninitialized interlock flag | FM-SKN-006 | Init to LOCKED_UNKNOWN | ✅ |
| CAN-DRV (TCI) | NULL pointer (receive buf) | FM-TCI-001 | NULL guard; safety msg not dropped | ✅ |
| CAN-DRV (TCI) | Sequence counter overflow | FM-TCI-002 | Modulo-256 delta check | ✅ |

**All 15/15 SEEA findings verified at architecture level** ✅

### 3.3 Hazard Mitigation Validation

All 10 hazards in the Hazard Log (SW-HAZ-001 through SW-HAZ-010) are mitigated by the architecture:

| Hazard | Description | Primary Component | Key FMEA IDs | Architecture Adequacy |
|--------|-------------|-------------------|-------------|----------------------|
| SW-HAZ-001 | Door opens while moving | SPM, SKN | FM-SPM-001 to 006, FM-SKN-001 | ✅ Adequate: 2oo2 + fail-safe default |
| SW-HAZ-002 | Door closes on passenger | OBD | FM-OBD-001 to 007 | ✅ Adequate: ISR + poll + force monitoring |
| SW-HAZ-003 | False door lock indication | DSM, SKN | FM-DSM-001 to 006, FM-SKN-003, FM-SKN-004 | ✅ Adequate: 2oo2×2oo2 voting + cross-channel |
| SW-HAZ-004 | Loss of door position | DSM | FM-DSM-001, FM-DSM-005 | ✅ Adequate: timeout → UNKNOWN + cross-channel |
| SW-HAZ-005 | Spurious safe state | FMG, SKN | FM-FMG-001, FM-FMG-002, FM-OBD-007 | ✅ Adequate: max dwell + driver override |
| SW-HAZ-006 | Watchdog failure | HAL, SKN | FM-HAL-003, FM-HAL-005, FM-DGN-002 | ✅ Adequate: HW watchdog independent; SPI fail → safe |
| SW-HAZ-007 | CAN speed data loss | TCI, SPM | FM-TCI-001 to 006, FM-SPM-002 to 005 | ✅ Adequate: CRC + timeout + assume moving |
| SW-HAZ-008 | Memory corruption | SKN (all) | FM-SKN-007, FM-SKN-008, FM-HAL-007, FM-DGN-003 | ✅ Adequate: CRC + canary + no dynamic alloc |
| SW-HAZ-009 | Emergency release mishandled | DSM, TCI | FM-DSM-007 | ✅ Adequate: latch + TCMS alert |
| SW-HAZ-010 | Selective disablement misuse | FMG | FM-FMG-004 | ✅ Adequate: speed interlock NOT removed |

### 3.4 New Hazards Identified by FMEA

**HAZ-011 (NEW)**: SPI Cross-Channel Communication Failure — Denial of Safe Operation

| Field | Value |
|-------|-------|
| **HAZ-ID** | SW-HAZ-011 (NEW — Phase 3 FMEA finding) |
| **Description** | SPI cross-channel link failure causes SKN on both channels to immediately assert `safe_state_active` = 1. While fail-safe, this creates a denial-of-service scenario: a recurring SPI transient (EMI, connector fault) repeatedly forces safe state, trapping passengers and potentially leading to secondary hazards (forced egress). This is distinct from SW-HAZ-005 (spurious safe state via false fault) — SW-HAZ-011 is safe-state caused by communication infrastructure fault, not by logic error. |
| **Source** | FMEA Phase 3: FM-HAL-005 (SPI exchange failure) analysis |
| **Severity** | 5 (Moderate — same consequence class as SW-HAZ-005) |
| **Frequency** | 3 (Remote — SPI is PCB-internal; EMI filtering per EN 50121-3-2 applied) |
| **Risk Level** | 15 |
| **SIL Assignment** | SIL 2 — same risk class as SW-HAZ-005; tolerable ALARP |
| **Mitigation** | (1) SPI failure requires 3 consecutive cycle mismatches before triggering final safe state (not immediate for transients); (2) EMC filtering per CCF-002; (3) FMG logs SPI fault with timestamp to distinguish transient from persistent; (4) driver override with TCMS authorization after N consecutive SPI faults confirmed as transient |
| **Residual Risk** | 4 |
| **REQ-SAFE-xxx** | REQ-SAFE-012 (existing — safe state requires confirmation); requires new architectural decision OI-FMEA-001 (see §4) |
| **Status** | OPEN — new finding; PM notification required |

### 3.5 Critical Findings Summary

| Finding | Category | Severity | Action Required |
|---------|----------|----------|----------------|
| FM-SPM-006: Speed = 5.0 km/h boundary condition | Code review | HIGH | VER unit test TC-SPM-007 must verify boundary at exactly 50 (5.0 km/h × 10) |
| FM-HAL-005: SPI failure → immediate safe state (no debounce) | Architectural gap | MODERATE | Open Issue OI-FMEA-001: Add 3-cycle SPI fault confirmation before safe state to prevent spurious safe state from SPI transients (new SW-HAZ-011) |
| FM-FMG-003: Critical fault misclassification | Code review | HIGH | VER must verify FMG classification table exhaustiveness per SAS §4.6 |
| 15/15 SEEA findings mitigated | Validation | PASS | All SEEA architectural mitigations confirmed in SAS Appendix B |

---

## 4. Open Issues (FMEA Phase 3)

| Issue ID | Source | Description | Resolution Owner | Priority |
|----------|--------|-------------|------------------|----------|
| OI-FMEA-001 | FM-HAL-005 / SW-HAZ-011 | SPI cross-channel communication failure triggers immediate safe state with no transient filter. Recommendation: add 3-cycle (60 ms) confirmation before final safe state assertion — except for safety-critical disagreements (speed mismatch with train moving). Update SAS §7.3 safe state trigger table to differentiate SPI infrastructure fault from safety-data disagreement. | DES (SAS update) → PM | MEDIUM |
| OI-FMEA-002 | FM-SPM-006 | Speed threshold boundary condition (exactly 5.0 km/h) must have dedicated unit test. | TST (TC-SPM-007) | HIGH |
| OI-FMEA-003 | OI-SAS-005 (from SAS) | CRC-16 polynomial unification (0x8005 vs. 0x1021) must be resolved in SDS. Cross-channel comparison relies on identical CRC calculation on both channels — polynomial mismatch would cause persistent SPI mismatch. | DES (SDS) | HIGH |

---

## 5. FMEA Conclusion

The FMEA of the TDC software architecture (DOC-SAS-2026-001 v0.1) has been completed:

- **49 failure modes** analysed across 8 components
- **0 unmitigated failure modes** — all failure modes have architectural mitigations
- **0 critical findings (RPN ≥ 200)** — maximum RPN = 48 (FM-OBD-001, FM-FMG-005)
- **15/15 SEEA findings validated** against SAS Appendix B
- **10/10 existing hazards mitigated** by the architecture
- **1 new hazard identified** (SW-HAZ-011 — SPI transient safe-state denial; SIL 2)
- **3 open issues raised** (OI-FMEA-001 through OI-FMEA-003) — none blocking Phase 3 completion

**Architecture Verdict**: The dual-channel 2oo2 design provides effective defence-in-depth. No single-point failures exist in any SIL 3 safety function. The architecture is **ADEQUATE** for SIL 3 with resolution of open issues OI-FMEA-001 to OI-FMEA-003 before Phase 4.

---

**END OF FMEA REPORT**

*Document ID*: DOC-FMEA-2026-001 v0.1  
*Phase 3 analysis*: 2026-04-02  
*Maintained by*: SAF (Safety Engineer), CM-controlled per §6.6  
*Review chain*: VER (item 14), VAL (item 25) in Track B per WORKFLOW.md  
*Next update*: Phase 7 — after system test evidence available (hazard closure confirmation)
