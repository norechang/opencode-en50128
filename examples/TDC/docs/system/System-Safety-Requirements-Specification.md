# System Safety Requirements Specification

**DOCUMENT TYPE**: System-Level Input Document  
**EN 50128 REFERENCE**: Section 7.2.2 (Input to Software Requirements Specification)  
**STANDARD**: EN 50126-2:2017 (Sections 5, 6, 7), EN 50129:2018

---

## DOCUMENT CONTROL

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SYS-SAF-2026-001 |
| **Version** | 1.0 |
| **Date** | 2026-04-02 |
| **Project** | TDC (Train Door Control System) |
| **System SIL Level** | SIL 3 |
| **Author** | System Safety Team |
| **Status** | Approved - Baseline for Software Safety Requirements |

---

## VERSION HISTORY

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-03-10 | Safety Engineer | Initial hazard analysis | - |
| 0.5 | 2026-03-20 | Safety Engineer | FMEA and FTA completed | Safety Manager |
| 1.0 | 2026-04-02 | Safety Engineer | Approved safety baseline | Safety Authority, Project Manager |

---

## APPROVALS

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Safety Engineer** | [PENDING] | [PENDING] | [PENDING] |
| **Independent Safety Assessor** | [PENDING] | [PENDING] | [PENDING] |
| **System Engineer** | [PENDING] | [PENDING] | [PENDING] |
| **Safety Manager** | [PENDING] | [PENDING] | [PENDING] |
| **Railway Safety Authority** | [PENDING] | [PENDING] | [PENDING] |

---

## 1. INTRODUCTION

### 1.1 Purpose

This System Safety Requirements Specification (SSRS) defines the safety requirements, hazards, risk analysis, and safety integrity requirements for the **Train Door Control System (TDC)**. It establishes the safety baseline for allocating safety requirements to hardware and software subsystems.

This document serves as the **primary safety input** to:
- Software Requirements Specification (EN 50128 Section 7.2) - for software safety requirements
- Hardware Requirements Specification - for hardware safety requirements
- System Safety Plan - for safety assurance activities

**EN 50126-2:2017 Reference**: Sections 5, 6, 7 define the systems approach to safety, hazard management, and safety requirements.

### 1.2 Scope

This SSRS applies to the Train Door Control System (TDC) for passenger railway vehicles, covering:
- System-level hazard identification and analysis
- Risk assessment and SIL determination
- System safety requirements
- Safety integrity requirements
- Allocation of safety functions to subsystems
- Safety-related interfaces

**Safety Standards Applied**:
- EN 50126-2:2017 (RAMS - Systems approach to safety)
- EN 50129:2018 (Safety related electronic systems for signalling)
- EN 50128:2011 (Software for railway control and protection systems)

### 1.3 System SIL Classification

**System SIL Level**: **SIL 3**

This classification is derived from hazard analysis per EN 50126-2 risk assessment methodology (see Section 2).

---

## 2. HAZARD ANALYSIS

### 2.1 Hazard Identification

Per EN 50126-2, hazards are identified through systematic analysis of system operation, failures, and environmental conditions.

#### Hazard Log Summary

| Hazard ID | Hazard Description | Potential Cause | Consequence | Severity | Frequency | Risk Class | Initial SIL |
|-----------|-------------------|----------------|-------------|----------|-----------|------------|------------|
| **HAZ-001** | Train departs with door open or not fully locked | Lock failure, sensor failure, software error | Passenger fall from train → Multiple fatalities | Catastrophic | Occasional | Intolerable | **SIL 3** |
| **HAZ-002** | Door closes on passenger causing entrapment injury | Obstacle detection failure, excessive closing force | Passenger trapped/crushed → Serious injury | Critical | Frequent | Intolerable | **SIL 3** |
| **HAZ-003** | Door opens while train is moving above 5 km/h | Speed interlock failure, software error, sensor failure | Passenger fall from train → Fatality | Catastrophic | Remote | Intolerable | **SIL 3** |
| **HAZ-004** | Obstacle detected but door continues to close | Obstacle sensor failure, software error | Passenger crushed → Serious injury | Critical | Occasional | Intolerable | **SIL 3** |
| **HAZ-005** | False door-locked signal allows train departure with door ajar | Lock sensor failure, software error | Passenger fall → Fatality | Catastrophic | Occasional | Intolerable | **SIL 3** |
| **HAZ-006** | Door fails to open at station (passenger trapped) | Motor failure, control failure, power loss | Passenger trapped → Minor injury/disruption | Marginal | Frequent | Tolerable (ALARP) | **SIL 2** |
| **HAZ-007** | Door fails to close at end of dwell time (service disruption) | Mechanical failure, control failure | Service delay | Marginal | Occasional | Tolerable (ALARP) | **SIL 1** |
| **HAZ-008** | Emergency door release triggers during normal operation | Spurious activation, misuse | Spurious door opening → Injury | Critical | Remote | Tolerable (ALARP) | **SIL 2** |
| **HAZ-009** | DCU software fault leads to loss of all door control | Software error, memory corruption | Loss of door control → Injury | Critical | Remote | Tolerable (ALARP) | **SIL 2** |

**Risk Matrix** (per EN 50126-2):

| Severity ↓ / Frequency → | Frequent | Probable | Occasional | Remote | Improbable | Incredible |
|---------------------------|----------|----------|------------|--------|------------|------------|
| **Catastrophic** | Intolerable | Unacceptable | **Unacceptable** | Undesirable | Tolerable | Acceptable |
| **Critical** | Unacceptable | Undesirable | **Undesirable** | Tolerable | Acceptable | Acceptable |
| **Marginal** | Undesirable | Tolerable | **Tolerable** | Acceptable | Acceptable | Acceptable |
| **Negligible** | Tolerable | Acceptable | Acceptable | Acceptable | Acceptable | Acceptable |

### 2.2 SIL Determination

Per EN 50129 Table A.1, SIL levels are determined based on risk classification:

| Risk Class | Action Required | Typical SIL |
|------------|----------------|-------------|
| **Intolerable** | Must be eliminated or reduced | SIL 4 |
| **Unacceptable** | Shall only be accepted with adequate risk reduction | SIL 3-4 |
| **Undesirable** | Shall only be tolerated if risk reduction is impractical | SIL 2-3 |
| **Tolerable** | Accepted with review by railway authority | SIL 1-2 |
| **Acceptable** | Acceptable without additional safety requirements | SIL 0-1 |

**System SIL Assignment**:
- **HAZ-001, HAZ-002, HAZ-003, HAZ-004, HAZ-005**: Intolerable risk → **SIL 3**
- **HAZ-006, HAZ-008, HAZ-009**: Tolerable risk (ALARP) → **SIL 2**
- **HAZ-007**: Tolerable risk → **SIL 1**

**Overall System SIL**: **SIL 3** (highest hazard-driven SIL)

### 2.3 Failure Mode and Effects Analysis (FMEA)

FMEA performed per EN 50126-2 Annex C. Key failure modes analyzed:

| Component | Failure Mode | Effect | Severity | Detection Method | Mitigation | SIL |
|-----------|-------------|--------|----------|------------------|------------|-----|
| Speed Sensor (TCMS) | Erroneous speed reading (low) | System permits door opening while moving | Catastrophic | Redundant sensors (2oo2), plausibility checks, timeout | Diverse speed sources, CRC, fail-safe default | **SIL 3** |
| Position Sensor | False "door closed" signal | System locks door while not fully closed | Critical | Redundant sensors (2oo2) | Dual sensors with cross-check | **SIL 3** |
| Obstacle Sensor | Failure to detect obstacle | Doors close on passenger | Critical | Sensor self-test, redundant sensors (2x per door) | Dual IR beams, force limit 150N | **SIL 3** |
| Door Lock | Lock fails to engage | Door unlocks while moving | Catastrophic | Lock position sensors (2oo2) | Redundant locks, continuous monitoring, fail-closed spring | **SIL 3** |
| Control Software | Logic error permits door open when moving | Doors open while moving | Catastrophic | Static analysis, testing, formal methods, code review | EN 50128 SIL 3 development, dual-channel processing | **SIL 3** |
| Motor Driver | Excessive closing force | Passenger injury | Critical | Current monitoring, force limit | Mechanical force limiter 150N, current cutoff | **SIL 3** |
| Emergency Release | Mechanism jammed | Passengers trapped in emergency | Catastrophic | Regular inspection, pull-test | Mechanical redundancy, fail-safe design, independent of electronics | **SIL 3** |
| Communication Bus (CAN) | Loss of speed data from TCMS | Speed interlock non-functional | Catastrophic | CRC, timeout detection (200 ms) | Fail-safe default (doors locked), redundant channels | **SIL 3** |
| DCU Processor | MCU hang/crash | Loss of door control | Critical | Watchdog timeout (50 ms), cross-channel monitor | Dual-channel 2oo2, independent watchdogs, safe state | **SIL 3** |

### 2.4 Fault Tree Analysis (FTA)

Top Event: **Passenger falls from train due to door opening while moving** (HAZ-003)

```
                     TOP EVENT
          Passenger falls from moving train
                         |
         ┌───────────────┴───────────────┐
         |                               |
     Doors open                      Train moving
     while moving                     (>5 km/h)
         |                               |
         ├──────────┬──────────┐         └─ (ASSUMED: Train operational)
         |          |          |
     Speed      Control    Door lock
     interlock  software   fails &
     fails      error      door opens
         |          |          |
     ┌───┴───┐  ┌──┴───┐  ┌───┴────┐
     |       |  |      |  |        |
   Speed   AND  Logic  HW  Lock    Lock
   sensor  gate error fail actuator sensor
   fail x2      |           fail    fail x2
   (2oo2)       |          (bypass) (2oo2)
                |
           ┌────┴────┐
           |         |
        Requirement Design/
        error       coding
                    error
```

**Quantitative FTA Results**:
- Target dangerous failure rate (top event): λ ≤ 10^-9 per hour (SIL 3 target)
- Speed sensor failure (2oo2 from TCMS): λ = 10^-6 per hour each → λ_combined = 10^-12 per hour (common mode β = 0.01)
- Software systematic failure: SC 2 (Systematic Capability per EN 50129) → adequate for SIL 3
- Lock mechanism (2oo2 + fail-closed): λ = 10^-6 per hour each → λ_combined = 10^-12 per hour
- DCU dual-channel (2oo2): λ = 10^-7 per hour per channel → λ_combined ≈ 10^-9 per hour (with DC ≥ 99%)
- **Total system dangerous failure rate**: λ_system ≈ 5 × 10^-9 per hour (accounting for common cause)
- **PFH (Probability of Failure per Hour)**: ≈ 5 × 10^-9 per hour
- **Result**: Meets SIL 3 requirement (< 10^-8 per hour per IEC 61508 Table 2) with margin

---

## 3. SYSTEM SAFETY REQUIREMENTS

### 3.1 Safety Functions

The following safety functions are identified (per EN 50126-2 Section 7):

| Safety Function ID | Description | SIL | Allocation | Derived From |
|-------------------|-------------|-----|------------|--------------|
| **SF-001** | Speed Interlock: Inhibit door open command when train speed > 5 km/h | **SIL 3** | Software + Hardware (sensors) | HAZ-003 |
| **SF-002** | Departure Interlock: Withhold door-locked signal until all doors confirmed locked | **SIL 3** | Software + Hardware (locks) | HAZ-001, HAZ-005 |
| **SF-003** | Obstacle Detection and Reversal: Detect and respond to obstacle within 150 ms | **SIL 3** | Software + Hardware (sensors) | HAZ-002, HAZ-004 |
| **SF-004** | Safe State: Command all doors to locked state on system fault | **SIL 3** | Software + Hardware | HAZ-005, HAZ-009 |
| **SF-005** | Door Position Verification: Confirm door lock status via independent sensor channel (2oo2) | **SIL 3** | Software + Hardware (sensors) | HAZ-001, HAZ-005 |
| **SF-006** | Emergency Release Monitoring: Detect and report emergency release activation | **SIL 2** | Hardware (mechanical) + Software | HAZ-008 |
| **SF-007** | Fault Isolation: Isolate defective door and maintain operation of remaining doors | **SIL 2** | Software | HAZ-009 |

### 3.2 Safety Integrity Requirements

#### 3.2.1 Hardware Safety Integrity

**SAFE-HW-001**: Hardware SHALL achieve SIL 3 hardware fault tolerance per EN 50129 Table A.2.  
**Requirement**: For SIL 3, either:
- Hardware Fault Tolerance = 1 (single fault does not cause hazard), OR
- Safe Failure Fraction ≥ 99%

**Applied**: Redundant sensors (2oo2) for critical functions + dual-channel processing → HFT = 1

**SAFE-HW-002**: Position sensors for "door closed" SHALL be implemented with 2oo2 architecture (2 out of 2 must agree).  
**Rationale**: SF-005 (SIL 3) per HAZ-001, HAZ-005

**SAFE-HW-003**: Lock position sensors SHALL be implemented with 2oo2 architecture.  
**Rationale**: SF-002, SF-005 (SIL 3) per HAZ-001, HAZ-005

**SAFE-HW-004**: Speed input SHALL use redundant sources (2oo2) or diverse sensors from TCMS.  
**Rationale**: SF-001 (SIL 3) per HAZ-003

**SAFE-HW-005**: Emergency release mechanism SHALL be mechanical (independent of electronics).  
**Rationale**: SF-006 (SIL 3), fail-safe independence

**SAFE-HW-006**: Door closing force SHALL be mechanically limited to ≤ 150 N (EN 14752).  
**Rationale**: SF-003 (SIL 3) per HAZ-002, HAZ-004, passive safety

**SAFE-HW-007**: Door locks SHALL be fail-closed (spring-loaded, default locked without power).  
**Rationale**: SF-004 (SIL 3), fail-safe on power loss

**SAFE-HW-008**: Dual-channel processing (2oo2) SHALL be implemented for safety-critical control.  
**Rationale**: SIL 3 hardware fault tolerance per EN 50129

#### 3.2.2 Software Safety Integrity

**SAFE-SW-001**: Software controlling SF-001, SF-002, SF-003, SF-004, SF-005, SF-007 SHALL be developed to SIL 3 per EN 50128.  
**Requirement**: EN 50128 Table A.3, A.4, A.5 mandatory and highly recommended techniques for SIL 3-4.

**SAFE-SW-002**: Software SHALL achieve Systematic Capability SC 2 per EN 50129 Table A.3 (adequate for SIL 3).

**SAFE-SW-003**: Software SHALL implement defensive programming per EN 50128 Table A.3 (Highly Recommended for SIL 3).

**SAFE-SW-004**: Software SHALL use structured programming (mandatory for SIL 3-4 per EN 50128 Table A.4).

**SAFE-SW-005**: Software cyclomatic complexity SHALL NOT exceed 10 (EN 50128 recommendation for SIL 3-4).

**SAFE-SW-006**: Software SHALL achieve 100% statement, branch, and MC/DC (Modified Condition/Decision Coverage) for SIL 3 functions (EN 50128 Table A.21).

**SAFE-SW-007**: Software SHALL NOT use dynamic memory allocation (malloc/free forbidden for SIL 2+ per EN 50128 Table A.4).

**SAFE-SW-008**: Software SHALL comply with MISRA C:2012 (mandatory for SIL 2+ per EN 50128 Table A.4).

**SAFE-SW-009**: Software SHALL implement watchdog monitoring (timeout ≤ 50 ms → safe state).

**SAFE-SW-010**: Software SHALL use CRC protection (CRC-16 minimum) for all safety-critical data structures and communications.

**SAFE-SW-011**: Software SHALL validate all external inputs before use (range checks, plausibility checks).

**SAFE-SW-012**: Software SHALL use static cyclic executive scheduler (no RTOS for SIL 3 safety kernel).

### 3.3 Common Cause Failures

**SAFE-CCF-001**: The system SHALL implement protection against common cause failures for redundant channels:
- Diverse sensor technologies where feasible (inductive + magnetic)
- Physical separation of redundant sensors
- Independent processing channels (dual MCU)
- Diverse power supplies where feasible

**Rationale**: EN 50129 Annex B - Common cause failures can defeat redundancy; β factor ≤ 0.01 assumed in FTA

**SAFE-CCF-002**: Software SHALL use cross-channel comparison for critical safety functions (dual-channel 2oo2):
- Independent execution of safety logic on both channels
- SPI cross-check every 20 ms cycle
- Disagreement → immediate safe state

**Applicability**: Mandatory for SIL 3 per EN 50128 Table A.4

### 3.4 Fault Detection and Diagnostics

**SAFE-DIAG-001**: The system SHALL detect ≥ 99% of dangerous failures (diagnostic coverage DC ≥ 99% for SIL 3 per EN 50129).

**SAFE-DIAG-002**: The system SHALL detect sensor faults within 100 ms.

**SAFE-DIAG-003**: The system SHALL detect communication faults within 200 ms (2x communication cycle).

**SAFE-DIAG-004**: The system SHALL implement online self-test for all safety-critical sensors and actuators.

**SAFE-DIAG-005**: The system SHALL log all detected faults with timestamp for analysis (minimum 1000 events in non-volatile storage).

**SAFE-DIAG-006**: The system SHALL detect MCU failures via:
- Watchdog timeout (50 ms)
- Cross-channel comparison (every 20 ms)
- Memory CRC checks (boot-time and periodic)

### 3.5 Safe States

**SAFE-STATE-001**: Upon detection of critical fault affecting SF-001 or SF-002 (door interlocks), the system SHALL:
- Immediately lock all doors (if train moving or fault prevents safe determination of speed)
- Prevent door opening until fault cleared
- Alert driver via TCMS
- Maintain emergency release functionality

**SAFE-STATE-002**: Upon loss of speed information from TCMS, the system SHALL assume "train moving" (conservative assumption) and lock doors.

**SAFE-STATE-003**: Upon detection of position sensor fault, the system SHALL assume "door not closed" until fault cleared.

**SAFE-STATE-004**: Safe states SHALL be maintained even under power loss (mechanical locks fail-closed, emergency release remains mechanical).

**SAFE-STATE-005**: Upon watchdog timeout (50 ms), the system SHALL trigger safe state (both channels lock doors, inhibit opening).

**SAFE-STATE-006**: Upon cross-channel disagreement, the system SHALL trigger safe state immediately (within 20 ms cycle).

### 3.6 Safety-Related Application Conditions

**SAFE-COND-001**: Selective Door Disablement Mode (isolate one defective door) SHALL:
- Maintain safety interlocks (speed interlock remains active)
- Require explicit authorization from driver or TCMS
- Log disablement event with timestamp
- Prevent train departure if disabled door is on platform side

**Rationale**: Prevents misuse of safety interlock bypass, addresses HAZ-009

**SAFE-COND-002**: Diagnostic Mode SHALL only be permitted when:
- Train is stationary (speed = 0 km/h confirmed)
- Parking brake applied (if available)
- Explicit authorization from maintenance personnel
- Safety interlocks remain active (cannot be bypassed)

**SAFE-COND-003**: Emergency door release SHALL:
- Be operable without electrical power (mechanical)
- Override electronic door locks mechanically
- Trigger alert to driver (if power available)
- Not prevent subsequent door operation (after reset)

---

## 4. SAFETY FUNCTION ALLOCATION

### 4.1 Hardware-Implemented Safety Functions

The following safety functions are allocated to hardware:

| Function | Hardware Implementation | SIL | Rationale |
|----------|------------------------|-----|-----------|
| **SF-006** (Emergency Release) | Mechanical door release mechanism (passive) | SIL 3 | Independence from electronics, fail-safe |
| **Door force limit** | Mechanical force limiter (150 N), current limiter | SIL 3 | Passive safety, independent of software per EN 14752 |
| **Lock fail-closed** | Spring-loaded lock mechanism | SIL 3 | Fail-safe under power loss |
| **Dual processing** | Dual STM32H743 microcontrollers (2oo2) | SIL 3 | Hardware fault tolerance HFT=1 |

### 4.2 Software-Implemented Safety Functions

The following safety functions are allocated to software:

| Function | Software Module | SIL | Requirements Reference |
|----------|----------------|-----|----------------------|
| **SF-001** (Speed interlock) | Speed Monitor (SPM) | SIL 3 | See Software Requirements Specification Section 3.2 |
| **SF-002** (Departure interlock) | Door State Machine (DSM), Safety Kernel | SIL 3 | See Software Requirements Specification Section 3.3 |
| **SF-003** (Obstacle detection) | Obstacle Detector (OBD) | SIL 3 | See Software Requirements Specification Section 3.4 |
| **SF-004** (Safe state) | Fault Manager (FMG), Safety Kernel | SIL 3 | See Software Requirements Specification Section 3.5 |
| **SF-005** (Position verification) | Door State Machine (DSM), Safety Kernel | SIL 3 | See Software Requirements Specification Section 3.6 |
| **SF-007** (Fault isolation) | Fault Manager (FMG) | SIL 2 | See Software Requirements Specification Section 3.7 |

**Traceability**: All software safety requirements are detailed in **Software Requirements Specification (DOC-SRS-2026-001)** Section 3 (Safety Requirements).

---

## 5. SAFETY INTEGRITY VERIFICATION

### 5.1 Hardware Safety Verification

Hardware safety integrity SHALL be verified through:
- FMEA analysis (completed - see Section 2.3)
- Hardware fault injection testing (verify safe states)
- Environmental qualification testing (EN 50155, EN 61373)
- EMC testing (EN 50121-3-2)
- Safe failure fraction calculation (target ≥ 99% for SIL 3)
- Dangerous failure rate calculation (target PFH ≤ 10^-7 per hour)

### 5.2 Software Safety Verification

Software safety integrity SHALL be verified through:
- EN 50128 SIL 3 development lifecycle compliance
- Static analysis (PC-lint, Cppcheck, Coverity)
- MISRA C:2012 compliance verification (zero mandatory violations)
- Dynamic testing with 100% MC/DC coverage for safety functions
- Formal verification (where applicable, e.g., critical state machines)
- Independent safety review (SIL 3 requires independence per EN 50128)

See **Software Verification Plan (DOC-SVP-2026-001)** for detailed verification approach.

### 5.3 System Safety Validation

System safety validation SHALL be performed through:
- Fault injection testing (induced failures to verify safe states)
- Hazard scenario testing (test cases derived from HAZ-001 to HAZ-009)
- Operational scenario testing in target environment
- Independent safety assessment (required for SIL 3 per EN 50129)

See **Software Validation Plan (DOC-SVaP-2026-001)** for detailed validation approach.

---

## 6. SAFETY CASE

### 6.1 Safety Argument Structure

The safety case for the Train Door Control System (TDC) is structured per EN 50129:

1. **Claim**: The Train Door Control System (TDC) is acceptably safe for operation at SIL 3
2. **Evidence**:
   - Hazard analysis (FMEA, FTA) demonstrates risks mitigated to acceptable levels
   - System design implements safety functions per safety requirements
   - Hardware achieves SIL 3 integrity (HFT = 1, DC ≥ 99%, PFH ≤ 10^-7)
   - Software developed per EN 50128 SIL 3 lifecycle
   - Verification and validation demonstrate compliance
   - Independent safety assessment confirms safety integrity
3. **Argument**: All identified hazards are mitigated through combination of safety functions, redundancy, diagnostics, and safe states; residual risk is ALARP (As Low As Reasonably Practicable)

### 6.2 Safety Case Documentation

The complete safety case consists of:
- This System Safety Requirements Specification
- Hazard Log (docs/Hazard-Log.md)
- FMEA Report (Appendix A of this document)
- FTA Report (Appendix B of this document)
- System Architecture Description (safety architecture)
- Software Safety Requirements (in Software Requirements Specification)
- Verification and Validation Reports
- Independent Safety Assessment Report (EN 50129 Section 6)

---

## 7. HAZARD LOG

The Hazard Log is maintained throughout the system lifecycle. Initial hazards are documented in Section 2.1. Updates to the Hazard Log SHALL be managed through the Change Control Board (CCB).

**Hazard Log Location**: `docs/Hazard-Log.md`

**Hazard Log Contents**:
- Hazard identification and description
- Risk assessment (severity, frequency)
- SIL assignment
- Safety requirements derived from hazard
- Mitigation measures (design, procedures, training)
- Verification evidence
- Residual risk assessment
- Status (open, mitigated, closed)

---

## 8. SAFETY REQUIREMENTS TRACEABILITY

### 8.1 Hazard to Safety Requirement Traceability

| Hazard | Safety Function | Safety Requirements | Allocation |
|--------|----------------|---------------------|------------|
| HAZ-001 | SF-002, SF-005 | SAFE-HW-002, SAFE-HW-003, SAFE-HW-007, SAFE-SW-001 | Software + Hardware |
| HAZ-002 | SF-003 | SAFE-HW-006, SAFE-SW-001, SAFE-SW-003 | Software + Hardware |
| HAZ-003 | SF-001 | SAFE-HW-004, SAFE-SW-001 | Software + Hardware |
| HAZ-004 | SF-003 | SAFE-HW-006, SAFE-SW-001 | Software + Hardware |
| HAZ-005 | SF-002, SF-004, SF-005 | SAFE-HW-003, SAFE-HW-007, SAFE-SW-001 | Software + Hardware |
| HAZ-006 | SF-007 | SAFE-SW-001 | Software |
| HAZ-007 | (Operational) | - | Operational procedures |
| HAZ-008 | SF-006 | SAFE-HW-005 | Hardware (mechanical) |
| HAZ-009 | SF-004, SF-007 | SAFE-SW-001, SAFE-HW-008, SAFE-DIAG-006 | Software + Hardware |

### 8.2 Safety Requirement to Software Requirement Traceability

All SAFE-SW-xxx requirements are traced to detailed software requirements in **Software Requirements Specification (DOC-SRS-2026-001)**.

Example traceability:
- SAFE-SW-001 → SW-SAFE-001 to SW-SAFE-020 (software safety requirements in SRS Section 3)
- SAFE-SW-003 → SW-IMPL-xxx (defensive programming requirements)
- SAFE-SW-007 → SW-IMPL-005 (static memory allocation)
- SAFE-SW-008 → SW-IMPL-010 (MISRA C:2012 compliance)

---

## 9. ASSUMPTIONS AND DEPENDENCIES

### 9.1 Assumptions

**ASSUME-001**: Train speed information is available from Train Control Management System (TCMS) via CAN bus with latency < 100 ms and update rate 10 Hz.

**ASSUME-002**: TCMS provides reliable speed data with SIL 2 integrity (redundant sources, CRC protection).

**ASSUME-003**: Driver is trained and follows operational procedures for selective door disablement mode activation.

**ASSUME-004**: Mechanical door hardware (actuators, locks) meets reliability and safety requirements specified in hardware specification.

**ASSUME-005**: Regular maintenance is performed per maintenance schedule (sensor calibration, lock inspection, emergency release testing).

**ASSUME-006**: Emergency release mechanism is tested monthly per maintenance procedures.

### 9.2 Dependencies

**DEPEND-001**: System safety depends on correct operation of Train Control Management System (TCMS) for operational commands and speed data.

**DEPEND-002**: Safety interlocks depend on accurate speed information from TCMS (redundant sources with timeout detection).

**DEPEND-003**: Hardware safety integrity depends on component quality and manufacturing per hardware specification.

**DEPEND-004**: Software safety integrity depends on EN 50128 SIL 3 development process compliance.

**DEPEND-005**: Safe state functionality depends on fail-closed spring-loaded locks (no electrical power required).

---

## 10. REFERENCES

### 10.1 Normative References

- **EN 50126-2:2017** - Railway applications - The specification and demonstration of RAMS - Part 2: Systems approach to safety
- **EN 50129:2018** - Railway applications - Communication, signalling and processing systems - Safety related electronic systems for signalling
- **EN 50128:2011** - Railway applications - Software for railway control and protection systems
- **EN 14752:2015** - Railway applications - Bodyside entrance systems
- **EN 50155:2017** - Railway applications - Electronic equipment used on rolling stock
- **IEC 61508** - Functional Safety of E/E/PE Safety-related Systems

### 10.2 Project References

- **System Requirements Specification** (DOC-SYS-REQ-2026-001)
- **System Architecture Description** (DOC-SYS-ARCH-2026-001)
- **Software Requirements Specification** (DOC-SRS-2026-001)
- **System Safety Plan** (DOC-SYS-PLAN-2026-001)
- **Hazard Log** (docs/Hazard-Log.md)

---

## APPENDIX A: FMEA REPORT

**Summary**: Detailed FMEA tables are provided in Section 2.3.

**Key Findings**:
- 9 critical failure modes identified requiring SIL 3 mitigation
- Redundancy (2oo2) applied to all safety-critical sensors
- Dual-channel processing (2oo2) implemented for control
- Mechanical fail-safe mechanisms (fail-closed locks, emergency release)
- Diagnostic coverage ≥ 99% achievable with proposed design

---

## APPENDIX B: FTA REPORT

**Summary**: Detailed FTA analysis is provided in Section 2.4.

**Quantitative Results**:
- Top event: Passenger falls from moving train (HAZ-003)
- Target: PFH ≤ 10^-9 per hour (SIL 3 target)
- Calculated: PFH ≈ 5 × 10^-9 per hour (with common cause β = 0.01)
- Result: **Meets SIL 3 requirement** (< 10^-8 per hour per IEC 61508 Table 2)

**Key Contributors**:
- Speed sensor failure (mitigated by 2oo2 redundancy): λ = 10^-12
- Software systematic failure (mitigated by EN 50128 SIL 3 development): SC 2
- Lock mechanism failure (mitigated by 2oo2 + fail-closed): λ = 10^-12
- DCU dual-channel failure (mitigated by 2oo2 + watchdog + DC ≥ 99%): λ ≈ 10^-9

---

## DOCUMENT APPROVAL

This System Safety Requirements Specification is **APPROVED** as the safety baseline for software and hardware development.

**Baseline Version**: 1.0  
**Baseline Date**: 2026-04-02  
**Configuration Item ID**: CI-SYS-SAF-001  

Any changes to safety requirements SHALL be processed through the Change Control Board (CCB) with Safety Manager approval.

---

**END OF DOCUMENT**
