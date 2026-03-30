# System Safety Requirements Specification

## Document Control

| Property | Value |
|----------|-------|
| **Document ID** | DOC-TDC-SSRS-SYS-001 |
| **Project** | TDC — Train Door Control |
| **System** | Train Door Control System (TDCS) |
| **Version** | 1.0 |
| **Status** | APPROVED — System Input |
| **Date** | 2026-03-27 |
| **Prepared by** | COD (generate-system) |
| **Standard** | EN 50126:2017, EN 50128:2011, EN 50129:2018 |
| **SIL Level** | SIL 3 |

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Safety Manager | TBD | ___________ | 2026-03-27 |
| System Engineer | TBD | ___________ | — |
| Safety Authority | TBD | ___________ | — |

---

## 1. Introduction

### 1.1 Purpose

This System Safety Requirements Specification (SSRS) defines the safety requirements allocated to the Train Door Control System (TDCS) software. These requirements SHALL be decomposed into software-level requirements in the Software Requirements Specification (SRS) produced in EN 50128 Phase 2. Each safety requirement is traceable to a system hazard and safety function.

### 1.2 Scope

This SSRS covers all safety requirements for the TDCS software component at SIL 3. It includes:
- Functional safety requirements (derived from SF-001 to SF-007)
- Integrity requirements (SIL allocation per module)
- Architectural safety requirements
- Safety-related interface requirements
- Non-functional safety requirements (performance, integrity, fault tolerance)

### 1.3 Relationship to Other Documents

| Document | Relationship |
|----------|-------------|
| DOC-TDC-SRS-SYS-001 (System SRS) | Parent — system-level functional requirements |
| DOC-TDC-SSP-SYS-001 (System Safety Plan) | Parent — safety process and methods |
| DOC-TDC-SAD-SYS-001 (System Architecture Description) | Parent — architectural constraints |
| Software Requirements Specification (Phase 2) | Child — software decomposes these requirements |
| Hazard Log (Phase 2) | Peer — safety requirements derived from hazards |

---

## 2. Safety Requirements

### 2.1 Speed Interlock Safety Requirements (SF-001, HAZ-003)

| ID | Safety Requirement | SIL | Verification Method |
|----|-------------------|-----|---------------------|
| SSR-001 | The software SHALL inhibit any door open command when the received train speed value exceeds 5 km/h | SIL 3 | Test (boundary value) |
| SSR-002 | The software SHALL validate the train speed input received from TCMS; if no valid speed data is received within 200 ms, the software SHALL treat the speed as exceeding 5 km/h (safe default) | SIL 3 | Test (fault injection) |
| SSR-003 | The software SHALL apply the speed interlock in both DCU channels independently; the interlock SHALL be enforced even if only one channel has valid speed data indicating > 5 km/h | SIL 3 | Test (single-channel fault) |
| SSR-004 | The speed threshold value (5 km/h) SHALL be stored as a named constant; its value SHALL NOT be modifiable at runtime | SIL 3 | Code review + test |

### 2.2 Departure Interlock Safety Requirements (SF-002, HAZ-001, HAZ-005)

| ID | Safety Requirement | SIL | Verification Method |
|----|-------------------|-----|---------------------|
| SSR-005 | The software SHALL NOT assert the door-locked signal to TCMS unless ALL monitored doors on the train have independently confirmed the locked position via their dedicated lock sensors | SIL 3 | Test (all door positions) |
| SSR-006 | The software SHALL use at least two independent sensor readings per door leaf to confirm the locked position before contributing to the door-locked signal | SIL 3 | Code review + test |
| SSR-007 | The software SHALL require both DCU channels to independently agree that all doors are locked before the door-locked output is asserted | SIL 3 | Test (channel comparison) |
| SSR-008 | If any door lock sensor fails to confirm locked status within 10 seconds of a close command, the software SHALL assert a door fault for that door and SHALL NOT assert the overall door-locked signal | SIL 3 | Test (timeout + fault) |
| SSR-009 | The door-locked signal SHALL be de-asserted immediately (within one control cycle, 10 ms) if any door lock sensor reports a non-locked state during normal monitoring | SIL 3 | Test (sensor transition) |

### 2.3 Obstacle Detection Safety Requirements (SF-003, HAZ-002, HAZ-004)

| ID | Safety Requirement | SIL | Verification Method |
|----|-------------------|-----|---------------------|
| SSR-010 | The software SHALL monitor obstacle sensor inputs continuously during any door closing operation | SIL 3 | Test + code review |
| SSR-011 | Upon detection of an obstacle (sensor beam break), the software SHALL reverse the door motor direction within **150 ms** of the beam break event | SIL 3 | Test (timing measurement) |
| SSR-012 | The software SHALL treat a sensor fault (no signal, out-of-range, or both beams simultaneously broken) as an obstacle present (fail-safe) | SIL 3 | Test (fault injection) |
| SSR-013 | After an obstacle-triggered reversal, the software SHALL NOT resume closing until the obstacle is cleared AND an explicit re-close command is received from TCMS | SIL 3 | Test (state machine) |
| SSR-014 | The 150 ms obstacle response budget SHALL be allocated as: ≤ 5 ms interrupt latency + ≤ 20 ms software processing + ≤ 125 ms DDU mechanical response | SIL 3 | Timing analysis + test |

### 2.4 Safe State Safety Requirements (SF-004, HAZ-005, HAZ-009)

| ID | Safety Requirement | SIL | Verification Method |
|----|-------------------|-----|---------------------|
| SSR-015 | The software SHALL enter the safe state unconditionally upon detection of any of the following: (a) cross-channel disagreement for > 2 consecutive cycles, (b) watchdog timeout, (c) CRC error in safety-critical data, (d) sensor input out of valid range, (e) stack overflow detection | SIL 3 | Test (fault injection each condition) |
| SSR-016 | The safe state action SHALL: (a) de-energise all door drive motors, (b) energise all door lock solenoids (locked position), (c) de-assert door-locked signal to TCMS, (d) assert door-fault signal to TCMS, (e) write fault code to non-volatile log | SIL 3 | Test (safe state verification) |
| SSR-017 | The software SHALL NOT exit the safe state autonomously; a deliberate operator reset action (via TCMS command with confirmation sequence) is required | SIL 3 | Test (reset sequence) |
| SSR-018 | The safe state SHALL be achievable from any software state within one control cycle (10 ms) | SIL 3 | Test + timing analysis |

### 2.5 Door Position Verification Safety Requirements (SF-005, HAZ-001, HAZ-005)

| ID | Safety Requirement | SIL | Verification Method |
|----|-------------------|-----|---------------------|
| SSR-019 | The software SHALL use a dedicated lock sensor channel (separate from the drive feedback channel) to confirm door lock status | SIL 3 | Design review + test |
| SSR-020 | The lock sensor input SHALL be validated by both DCU channels independently; a disagreement between channels on the lock status of any door SHALL trigger a fault and prevent door-locked signal assertion | SIL 3 | Test (dual-channel lock) |
| SSR-021 | The software SHALL cyclically re-read all door lock sensor inputs during monitoring state at a period not exceeding 50 ms | SIL 3 | Code review + test |

### 2.6 Emergency Release Monitoring Safety Requirements (SF-006, HAZ-008)

| ID | Safety Requirement | SIL | Verification Method |
|----|-------------------|-----|---------------------|
| SSR-022 | The software SHALL monitor the emergency door release sensor on each door continuously | SIL 2 | Test |
| SSR-023 | Upon detection of an emergency release activation, the software SHALL: (a) record the event with timestamp, (b) transmit an emergency release alert to TCMS within 500 ms, (c) inhibit any subsequent close command for that door until acknowledged | SIL 2 | Test |

### 2.7 Fault Isolation Safety Requirements (SF-007, HAZ-009)

| ID | Safety Requirement | SIL | Verification Method |
|----|-------------------|-----|---------------------|
| SSR-024 | The software SHALL isolate a defective door (cease commands to that door's DDU) upon detection of a persistent fault on that door, while maintaining normal operation of all remaining doors | SIL 2 | Test (door isolation) |
| SSR-025 | An isolated door SHALL be reported individually to TCMS via the door fault status message | SIL 2 | Test |
| SSR-026 | The software SHALL allow re-integration of an isolated door only after a deliberate operator action confirming door health | SIL 2 | Test |

---

## 3. Architectural Safety Requirements

| ID | Requirement | SIL | Phase |
|----|------------|-----|-------|
| ASR-001 | The safety-critical software (DSM, SPM, OBD, TCI, FMG, HAL) SHALL execute on both DCU channels independently with no shared mutable state | SIL 3 | Phase 3 |
| ASR-002 | All inter-module interfaces SHALL be defined with typed parameters; no void pointer passing for safety-critical data | SIL 3 | Phase 3 |
| ASR-003 | All safety-critical global variables SHALL be declared in dedicated header files; their modification SHALL be restricted to the owning module | SIL 3 | Phase 3 |
| ASR-004 | All safety-critical configuration constants SHALL be stored in read-only (const) memory | SIL 3 | Phase 3 |
| ASR-005 | The HAL SHALL validate all sensor input ranges before passing data to the application layer | SIL 3 | Phase 3, 5 |
| ASR-006 | The software SHALL implement a startup self-test that verifies: (a) RAM integrity, (b) flash CRC, (c) cross-channel link, (d) sensor responsiveness — and shall refuse to commence operation if any test fails | SIL 3 | Phase 3 |

---

## 4. Interface Safety Requirements

| ID | Requirement | SIL | Interface |
|----|------------|-----|-----------|
| ISR-001 | All TCMS CAN messages shall include a sequence counter and CRC; the software SHALL reject messages with invalid CRC or out-of-sequence counters | SIL 3 | TCMS ↔ DCU |
| ISR-002 | The software SHALL reject any TCMS command message with a message age > 500 ms | SIL 3 | TCMS ↔ DCU |
| ISR-003 | The cross-channel SPI link shall include a message ID, sequence counter, and CRC; a failed integrity check SHALL trigger the safe state | SIL 3 | Channel A ↔ B |
| ISR-004 | All DDU RS-485 command messages shall include a checksum; the DDU SHALL NOT execute a command with an invalid checksum | SIL 3 | DCU ↔ DDU |
| ISR-005 | The TCMS door-locked status output shall remain asserted only while the lock condition is confirmed; any interruption of lock sensor confirmation SHALL cause immediate de-assertion | SIL 3 | DCU → TCMS |

---

## 5. Non-Functional Safety Requirements

| ID | Requirement | SIL | Metric |
|----|------------|-----|--------|
| NFSR-001 | The software shall achieve a PFH ≤ 1×10⁻⁷ per hour for the combined TDCS software (SIL 3) | SIL 3 | PFH analysis (Phase 8) |
| NFSR-002 | All SIL 3 safety functions shall be executed within the 10 ms control cycle with a worst-case execution time (WCET) ≤ 7 ms (70% CPU budget) | SIL 3 | Timing analysis (Phase 5) |
| NFSR-003 | The software shall be free of MISRA C:2012 mandatory violations; all required violations shall be documented with justification | SIL 3 | Static analysis report |
| NFSR-004 | All SIL 3 software modules shall achieve 100% statement, branch, and MC/DC condition coverage | SIL 3 | Coverage report (Phase 5) |
| NFSR-005 | No function shall exceed cyclomatic complexity of 10 | SIL 3 | Complexity report (Phase 5) |
| NFSR-006 | Stack usage SHALL be statically analysed; dynamic stack growth SHALL NOT exceed 80% of available stack space | SIL 3 | Static stack analysis (Phase 5) |

---

## 6. Traceability Matrix — Safety Requirements

| System Hazard | System Safety Function | System Safety Requirement(s) | SW SRS (Phase 2) |
|--------------|----------------------|------------------------------|------------------|
| HAZ-001 | SF-002, SF-005 | SSR-005, SSR-006, SSR-007, SSR-008, SSR-009, SSR-019, SSR-020, SSR-021 | TBD Phase 2 |
| HAZ-002 | SF-003 | SSR-010, SSR-011, SSR-012, SSR-013, SSR-014 | TBD Phase 2 |
| HAZ-003 | SF-001 | SSR-001, SSR-002, SSR-003, SSR-004 | TBD Phase 2 |
| HAZ-004 | SF-003 | SSR-010, SSR-011, SSR-012, SSR-013 | TBD Phase 2 |
| HAZ-005 | SF-002, SF-004 | SSR-005, SSR-007, SSR-015, SSR-016, SSR-017, SSR-018 | TBD Phase 2 |
| HAZ-006 | SF-007 | SSR-024, SSR-025, SSR-026 | TBD Phase 2 |
| HAZ-007 | — | (Operational/performance — no dedicated SW SSR) | — |
| HAZ-008 | SF-006 | SSR-022, SSR-023 | TBD Phase 2 |
| HAZ-009 | SF-004, SF-007 | SSR-015, SSR-016, SSR-024 | TBD Phase 2 |

---

## 7. Safety Requirements Summary

| SIL | Count | Requirement IDs |
|-----|-------|----------------|
| SIL 3 | 23 | SSR-001 to SSR-021, ASR-001 to ASR-006, ISR-001 to ISR-005, NFSR-001 to NFSR-006 |
| SIL 2 | 5 | SSR-022, SSR-023, SSR-024, SSR-025, SSR-026 |
| **Total** | **28** | |

All safety requirements in this SSRS SHALL be decomposed into software requirements in the Phase 2 SRS. No SSR shall be left without a corresponding SW-REQ in the SRS.

---

*End of Document — DOC-TDC-SSRS-SYS-001 v1.0*
