# System Safety Requirements Specification

**DOCUMENT TYPE**: System-Level Input Document  
**EN 50128 REFERENCE**: Section 7.2.2 (Input to Software Requirements Specification)  
**STANDARD**: EN 50126-2:2017, EN 50129:2018

<!--
TEMPLATE USAGE INSTRUCTIONS:

This is a REFERENCE EXAMPLE document, not a generic template with placeholders.

The content below is a REAL, COMPLETE System Safety Requirements Specification for the Train Door Control System.
It demonstrates proper EN 50126/50129 compliant safety requirements structure, including:
- Hazard identification and risk assessment (9 real hazards)
- FMEA and FTA analysis with quantitative results
- System safety functions (7 functions at SIL 2-3)
- Safety integrity requirements for hardware and software
- Safety function allocation to subsystems
- Traceability from hazards to safety requirements

TO USE THIS TEMPLATE FOR YOUR PROJECT:

1. COPY this file and rename it (e.g., System-Safety-Requirements-Specification.md)
2. REPLACE metadata fields with YOUR project information:
   - Document IDs: DOC-SYS-SAFE-YYYY-NNN → DOC-SYS-SAFE-2026-001
   - Dates: YYYY-MM-DD → 2026-03-15
   - Names: [Name] → Jane Smith
   - Organizations: [Railway Authority] → UK Rail Safety Authority
   - Configuration IDs: CI-SYS-SAFE-NNN → CI-SYS-SAFE-001
3. ADAPT the concrete Train Door Control System content to YOUR system:
   - Replace the 9 hazards with YOUR system hazards
   - Adapt FMEA table with YOUR components and failure modes
   - Define YOUR safety functions (keep structure, change content)
   - Customize safety requirements to YOUR design
   - Maintain the same level of rigor and EN 50126/50129 compliance

This approach gives you a working example to learn from and adapt, rather than
forcing you to fill in generic placeholders without context.

Key sections to customize:
- Section 2: Your hazard analysis, FMEA, FTA
- Section 3: Your safety functions and safety requirements
- Section 4: Your hardware/software allocation
- Section 8: Your traceability matrices
-->

---

## DOCUMENT CONTROL

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SYS-SAFE-YYYY-NNN |
| **Version** | 1.0 |
| **Date** | YYYY-MM-DD |
| **Project** | Train Door Control System (train_door_control2) |
| **System SIL Level** | SIL 3 |
| **Author** | System Safety Team |
| **Status** | Approved - Baseline for Software Safety Requirements |

---

## VERSION HISTORY

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | YYYY-MM-DD | [Safety Engineer Name] | Initial hazard analysis | - |
| 0.5 | YYYY-MM-DD | [Safety Engineer Name] | FMEA and FTA completed | [Safety Manager Name] |
| 1.0 | YYYY-MM-DD | [Safety Engineer Name] | Approved safety baseline | [Safety Authority], [Project Manager Name] |

---

## APPROVALS

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Safety Engineer** | [Name] | [Signed] | YYYY-MM-DD |
| **Independent Safety Assessor** | [Name] ([Assessment Body]) | [Signed] | YYYY-MM-DD |
| **System Engineer** | [Name] | [Signed] | YYYY-MM-DD |
| **Safety Manager** | [Name] | [Signed] | YYYY-MM-DD |
| **Railway Safety Authority** | [Railway Authority] | [Signed] | YYYY-MM-DD |

---

## 1. INTRODUCTION

### 1.1 Purpose

This System Safety Requirements Specification (SSRS) defines the safety requirements, hazards, risk analysis, and safety integrity requirements for the **Train Door Control System**. It establishes the safety baseline for allocating safety requirements to hardware and software subsystems.

This document serves as the **primary safety input** to:
- Software Requirements Specification (EN 50128 Section 7.2) - for software safety requirements
- Hardware Requirements Specification - for hardware safety requirements
- System Safety Plan - for safety assurance activities

### 1.2 Scope

This SSRS applies to the Train Door Control System for passenger railway vehicles, covering:
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

This classification is derived from hazard analysis per EN 50126-2 risk assessment methodology.

---

## 2. HAZARD ANALYSIS

### 2.1 Hazard Identification

Per EN 50126-2, hazards are identified through systematic analysis of system operation, failures, and environmental conditions.

#### Hazard Log Summary

| Hazard ID | Hazard Description | Potential Cause | Consequence | Severity | Frequency | Risk Class | Initial SIL |
|-----------|-------------------|----------------|-------------|----------|-----------|------------|------------|
| **SYS-HAZ-001** | Doors open while train is moving (>5 km/h) | Speed interlock failure, software error, sensor failure | Passenger fall from train → Multiple fatalities | Catastrophic | Credible | Unacceptable | **SIL 3** |
| **SYS-HAZ-002** | Doors close on passenger causing injury | Obstacle detection failure, excessive closing force | Passenger trapped/crushed → Serious injury | Critical | Probable | Undesirable | **SIL 2** |
| **SYS-HAZ-003** | Doors fail to open during emergency evacuation | Door control failure, lock failure, power loss | Passenger entrapment in emergency → Fatalities | Catastrophic | Occasional | Unacceptable | **SIL 3** |
| **SYS-HAZ-004** | Door unlocks while train is moving | Lock control failure, software error | Passenger could manually open door → Fatality | Catastrophic | Remote | Undesirable | **SIL 3** |
| **SYS-HAZ-005** | Incorrect platform side door opening | Platform detection failure, software error | Passenger exits on non-platform side → Fatality | Catastrophic | Remote | Undesirable | **SIL 2** |
| **SYS-HAZ-006** | Door fails to close and lock before departure | Control failure, mechanical failure | Train departs with open door → Passenger fall | Catastrophic | Occasional | Unacceptable | **SIL 3** |
| **SYS-HAZ-007** | Unintended door opening at station | Spurious command, software error | Passenger egress on wrong side → Injury | Marginal | Probable | Tolerable | **SIL 1** |
| **SYS-HAZ-008** | Loss of door status indication to driver | Display failure, communication failure | Driver unaware of door state → Incorrect actions | Critical | Probable | Undesirable | **SIL 1** |
| **SYS-HAZ-009** | Emergency release inoperative | Mechanical failure, design error | Passenger cannot escape in emergency → Fatalities | Catastrophic | Remote | Undesirable | **SIL 3** |

**Risk Matrix** (per EN 50126-2):

| Severity ↓ / Frequency → | Frequent | Probable | Occasional | Remote | Improbable | Incredible |
|---------------------------|----------|----------|------------|--------|------------|------------|
| **Catastrophic** | Intolerable | Unacceptable | Unacceptable | Undesirable | Tolerable | Acceptable |
| **Critical** | Unacceptable | Undesirable | Undesirable | Tolerable | Acceptable | Acceptable |
| **Marginal** | Undesirable | Tolerable | Tolerable | Acceptable | Acceptable | Acceptable |
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
- **HAZ-001, HAZ-003, HAZ-004, HAZ-006, HAZ-009**: Unacceptable risk → **SIL 3**
- **HAZ-002, HAZ-005**: Undesirable risk → **SIL 2**
- **HAZ-007, HAZ-008**: Tolerable risk → **SIL 1**

**Overall System SIL**: **SIL 3** (highest hazard-driven SIL)

### 2.3 Failure Mode and Effects Analysis (FMEA)

FMEA performed per EN 50126-2 Annex C. Key failure modes analyzed:

| Component | Failure Mode | Effect | Severity | Detection Method | Mitigation | SIL |
|-----------|-------------|--------|----------|------------------|------------|-----|
| Speed Sensor | Erroneous speed reading (low) | System permits door opening while moving | Catastrophic | Redundant sensors (2oo2), plausibility checks | Diverse speed sources, watchdog | **SIL 3** |
| Position Sensor | False "door closed" signal | System locks door while not fully closed | Critical | Redundant sensors (2oo2) | Dual sensors with cross-check | **SIL 3** |
| Obstacle Sensor | Failure to detect obstacle | Doors close on passenger | Critical | Sensor self-test, redundant sensors | Dual IR beams, force limit | **SIL 2** |
| Door Lock | Lock fails to engage | Door unlocks while moving | Catastrophic | Lock position sensors (2oo2) | Redundant locks, continuous monitoring | **SIL 3** |
| Control Software | Logic error permits door open when moving | Doors open while moving | Catastrophic | Static analysis, testing, formal methods | EN 50128 SIL 3 development, diverse programming | **SIL 3** |
| Motor Driver | Excessive closing force | Passenger injury | Critical | Current monitoring, force limit | Mechanical force limiter, current cutoff | **SIL 2** |
| Emergency Release | Mechanism jammed | Passengers trapped in emergency | Catastrophic | Regular inspection, pull-test | Mechanical redundancy, fail-safe design | **SIL 3** |
| Communication Bus | Loss of speed data | Speed interlock non-functional | Catastrophic | CRC, timeout detection | Fail-safe default (doors locked), redundant channels | **SIL 3** |

### 2.4 Fault Tree Analysis (FTA)

Top Event: **Passenger falls from train due to door opening while moving** (HAZ-001)

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
    interlock  software   fails
    fails      error
        |          |          |
    ┌───┴───┐  ┌──┴───┐  ┌───┴────┐
    |       |  |      |  |        |
  Speed   AND  Logic  HW  Lock    Lock
  sensor  gate error fail actuator sensor
  fail x2      |           fail    fail x2
               |
          ┌────┴────┐
          |         |
       Requirement Design
       error       error
```

**Quantitative FTA Results**:
- Target dangerous failure rate (top event): λ ≤ 10^-9 per hour (SIL 3)
- Speed sensor failure (2oo2): λ = 10^-6 per hour each → λ_combined = 10^-12 per hour
- Software systematic failure: SC 2 (Systematic Capability per EN 50129) → adequate for SIL 3
- Lock mechanism (2oo2): λ = 10^-6 per hour each → λ_combined = 10^-12 per hour
- **Total system dangerous failure rate**: λ_system ≈ 5 × 10^-9 per hour → **Meets SIL 3** (< 10^-8)

---

## 3. SYSTEM SAFETY REQUIREMENTS

### 3.1 Safety Functions

The following safety functions are identified:

| Safety Function ID | Description | SIL | Allocation |
|-------------------|-------------|-----|------------|
| **SF-001** | Door Opening Interlock - Prevent door opening when train speed > 5 km/h | **SIL 3** | Software + Hardware (sensors) |
| **SF-002** | Door Locking Function - Maintain doors locked when train speed > 5 km/h | **SIL 3** | Software + Hardware (locks) |
| **SF-003** | Obstacle Detection - Detect obstacles during door closing and prevent injury | **SIL 2** | Software + Hardware (sensors) |
| **SF-004** | Emergency Release - Enable manual door opening in emergency regardless of system state | **SIL 3** | Hardware (mechanical) |
| **SF-005** | Platform Side Detection - Ensure doors open only on correct platform side | **SIL 2** | Software + Hardware (sensors) |
| **SF-006** | Door Closed Verification - Confirm doors fully closed before permitting train movement | **SIL 3** | Software + Hardware (sensors) |
| **SF-007** | Fault Detection and Safe State - Detect failures and transition to safe state | **SIL 3** | Software + Hardware |

### 3.2 Safety Integrity Requirements

#### 3.2.1 Hardware Safety Integrity

**SAFE-HW-001**: Hardware SHALL achieve SIL 3 hardware fault tolerance per EN 50129 Table A.2.  
**Requirement**: For SIL 3, either:
- Hardware Fault Tolerance = 1 (single fault does not cause hazard), OR
- Safe Failure Fraction ≥ 99%

**Applied**: Redundant sensors (2oo2) for critical functions → HFT = 1

**SAFE-HW-002**: Position sensors for "door closed" SHALL be implemented with 2oo2 architecture (2 out of 2 must agree).  
**Rationale**: SF-006 (SIL 3)

**SAFE-HW-003**: Lock position sensors SHALL be implemented with 2oo2 architecture.  
**Rationale**: SF-002 (SIL 3)

**SAFE-HW-004**: Speed input SHALL use redundant sources (2oo2) or diverse sensors.  
**Rationale**: SF-001 (SIL 3)

**SAFE-HW-005**: Emergency release mechanism SHALL be mechanical (independent of electronics).  
**Rationale**: SF-004 (SIL 3), fail-safe independence

**SAFE-HW-006**: Door closing force SHALL be mechanically limited to ≤ 150 N (EN 14752).  
**Rationale**: SF-003 (SIL 2), passive safety

#### 3.2.2 Software Safety Integrity

**SAFE-SW-001**: Software controlling SF-001, SF-002, SF-006, SF-007 SHALL be developed to SIL 3 per EN 50128.  
**Requirement**: EN 50128 Table A.3, A.4, A.5 mandatory and highly recommended techniques for SIL 3-4.

**SAFE-SW-002**: Software SHALL achieve Systematic Capability SC 2 per EN 50129 Table A.3 (adequate for SIL 3).

**SAFE-SW-003**: Software SHALL implement defensive programming per EN 50128 Table A.3 (Highly Recommended for SIL 3).

**SAFE-SW-004**: Software SHALL use structured programming (mandatory for SIL 3-4).

**SAFE-SW-005**: Software cyclomatic complexity SHALL NOT exceed 10 (EN 50128 recommendation for SIL 3-4).

**SAFE-SW-006**: Software SHALL achieve 100% statement, branch, and MC/DC coverage for SIL 3 functions (EN 50128 Table A.21).

**SAFE-SW-007**: Software SHALL NOT use dynamic memory allocation (malloc/free forbidden for SIL 2+).

**SAFE-SW-008**: Software SHALL comply with MISRA C:2012 (mandatory for SIL 2+).

**SAFE-SW-009**: Software SHALL implement watchdog monitoring (timeout ≤ 100 ms).

**SAFE-SW-010**: Software SHALL use CRC protection for all safety-critical data structures and communications.

### 3.3 Common Cause Failures

**SAFE-CCF-001**: The system SHALL implement protection against common cause failures for redundant channels:
- Diverse sensor technologies where feasible
- Physical separation of redundant sensors
- Independent processing channels (if applicable)
- Diverse software (if dual processing used)

**Rationale**: EN 50129 Annex B - Common cause failures can defeat redundancy

**SAFE-CCF-002**: Software SHALL use diverse programming for critical safety functions (if resources permit):
- Two independent implementations of speed interlock logic
- Cross-comparison and voting

**Applicability**: Recommended for SIL 3-4 per EN 50128 Table A.4

### 3.4 Fault Detection and Diagnostics

**SAFE-DIAG-001**: The system SHALL detect ≥ 99% of dangerous failures (diagnostic coverage DC ≥ 99% for SIL 3).

**SAFE-DIAG-002**: The system SHALL detect sensor faults within 100 ms.

**SAFE-DIAG-003**: The system SHALL detect communication faults within 200 ms (2x communication cycle).

**SAFE-DIAG-004**: The system SHALL implement online self-test for all safety-critical sensors and actuators.

**SAFE-DIAG-005**: The system SHALL log all detected faults with timestamp for analysis.

### 3.5 Safe States

**SAFE-STATE-001**: Upon detection of critical fault affecting SF-001 or SF-002 (door interlocks), the system SHALL:
- Immediately lock all doors (if train moving or fault prevents safe determination of speed)
- Prevent door opening until fault cleared
- Alert driver

**SAFE-STATE-002**: Upon loss of speed information, the system SHALL assume "train moving" (conservative assumption) and lock doors.

**SAFE-STATE-003**: Upon detection of position sensor fault, the system SHALL assume "door not closed" until fault cleared.

**SAFE-STATE-004**: Safe states SHALL be maintained even under power loss (mechanical locks fail-closed, emergency release remains mechanical).

### 3.6 Safety-Related Application Conditions

**SAFE-COND-001**: Emergency Evacuation Mode (which bypasses speed interlock) SHALL only be activated when:
- Explicit authorization from driver OR emergency controller
- Train speed < 5 km/h (verified by independent speed sensor)
- Emergency situation confirmed

**Rationale**: Prevents misuse of safety interlock bypass

**SAFE-COND-002**: Maintenance Mode (manual door operation) SHALL NOT bypass safety interlocks (speed interlock remains active).

**SAFE-COND-003**: Diagnostic Mode SHALL only be permitted when train is stationary and secured (parking brake applied).

---

## 4. SAFETY FUNCTION ALLOCATION

### 4.1 Hardware-Implemented Safety Functions

The following safety functions are allocated to hardware:

| Function | Hardware Implementation | SIL | Rationale |
|----------|------------------------|-----|-----------|
| **SF-004** (Emergency Release) | Mechanical door release mechanism | SIL 3 | Independence from electronics, fail-safe |
| **Door force limit** | Mechanical force limiter, current limiter | SIL 2 | Passive safety, independent of software |
| **Lock fail-closed** | Spring-loaded lock mechanism | SIL 3 | Fail-safe under power loss |

### 4.2 Software-Implemented Safety Functions

The following safety functions are allocated to software:

| Function | Software Module | SIL | Requirements Reference |
|----------|----------------|-----|----------------------|
| **SF-001** (Door opening interlock) | Speed interlock module | SIL 3 | See Software Requirements Specification Section 3.2 |
| **SF-002** (Door locking function) | Lock control module | SIL 3 | See Software Requirements Specification Section 3.3 |
| **SF-003** (Obstacle detection) | Obstacle detection module | SIL 2 | See Software Requirements Specification Section 3.4 |
| **SF-005** (Platform side detection) | Platform logic module | SIL 2 | See Software Requirements Specification Section 3.5 |
| **SF-006** (Door closed verification) | Position monitoring module | SIL 3 | See Software Requirements Specification Section 3.6 |
| **SF-007** (Fault detection) | Diagnostics and fault management module | SIL 3 | See Software Requirements Specification Section 3.7 |

**Traceability**: All software safety requirements are detailed in **Software Requirements Specification (DOC-SRS-YYYY-NNN)** Section 3 (Safety Requirements).

---

## 5. SAFETY INTEGRITY VERIFICATION

### 5.1 Hardware Safety Verification

Hardware safety integrity SHALL be verified through:
- FMEA analysis (completed - see Section 2.3)
- Hardware fault injection testing
- Environmental qualification testing (EN 50155, EN 61373)
- EMC testing (EN 50121-3-2)
- Safe failure fraction calculation (target ≥ 99% for SIL 3)

### 5.2 Software Safety Verification

Software safety integrity SHALL be verified through:
- EN 50128 SIL 3 development lifecycle compliance
- Static analysis (PC-lint, Cppcheck)
- Dynamic testing with 100% MC/DC coverage for safety functions
- Formal verification (if applicable)
- Independent safety review (SIL 3 requires independence)

See **Software Verification Plan (DOC-SVP-YYYY-NNN)** for detailed verification approach.

### 5.3 System Safety Validation

System safety validation SHALL be performed through:
- Fault injection testing (induced failures to verify safe states)
- Hazard scenario testing (test cases derived from HAZ-001 to HAZ-009)
- Operational scenario testing in target environment
- Independent safety assessment (required for SIL 3)

See **Software Validation Plan (DOC-SVaP-YYYY-NNN)** for detailed validation approach.

---

## 6. SAFETY CASE

### 6.1 Safety Argument Structure

The safety case for the Train Door Control System is structured per EN 50129:

1. **Claim**: The Train Door Control System is acceptably safe for operation at SIL 3
2. **Evidence**:
   - Hazard analysis (FMEA, FTA) demonstrates risks mitigated to acceptable levels
   - System design implements safety functions per safety requirements
   - Hardware achieves SIL 3 integrity (HFT = 1, DC ≥ 99%)
   - Software developed per EN 50128 SIL 3 lifecycle
   - Verification and validation demonstrate compliance
   - Independent safety assessment confirms safety integrity
3. **Argument**: All identified hazards are mitigated through combination of safety functions, redundancy, diagnostics, and safe states; residual risk is ALARP (As Low As Reasonably Practicable)

### 6.2 Safety Case Documentation

The complete safety case consists of:
- This System Safety Requirements Specification
- Hazard Log (DOC-HAZ-YYYY-NNN)
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

---

## 8. SAFETY REQUIREMENTS TRACEABILITY

### 8.1 Hazard to Safety Requirement Traceability

| Hazard | Safety Function | Safety Requirements | Allocation |
|--------|----------------|---------------------|------------|
| HAZ-001 | SF-001, SF-002 | SAFE-SW-001, SAFE-HW-002, SAFE-HW-003, SAFE-HW-004 | Software + Hardware |
| HAZ-002 | SF-003 | SAFE-HW-006, SAFE-SW-003 | Software + Hardware |
| HAZ-003 | SF-004 | SAFE-HW-005 | Hardware (mechanical) |
| HAZ-004 | SF-002 | SAFE-SW-001, SAFE-HW-003 | Software + Hardware |
| HAZ-005 | SF-005 | SAFE-SW-001 | Software |
| HAZ-006 | SF-006 | SAFE-HW-002, SAFE-SW-001 | Software + Hardware |
| HAZ-009 | SF-004 | SAFE-HW-005 | Hardware (mechanical) |

### 8.2 Safety Requirement to Software Requirement Traceability

All SAFE-SW-xxx requirements are traced to detailed software requirements in **Software Requirements Specification (DOC-SRS-YYYY-NNN)**.

Example traceability:
- SAFE-SW-001 → SW-SAFE-001 to SW-SAFE-020 (software safety requirements in Software Requirements Specification Section 3)
- SAFE-SW-003 → SW-IMPL-xxx (defensive programming requirements)
- SAFE-SW-007 → SW-IMPL-005 (static memory allocation)

---

## 9. ASSUMPTIONS AND DEPENDENCIES

### 9.1 Assumptions

**ASSUME-001**: Train speed information is available from Train Control Management System (TCMS) via CAN bus with latency < 50 ms.

**ASSUME-002**: Platform detection system provides reliable platform side indication (left/right) with SIL 2 integrity.

**ASSUME-003**: Driver is trained and follows operational procedures for emergency evacuation mode activation.

**ASSUME-004**: Mechanical door hardware (actuators, locks) meets reliability and safety requirements specified in hardware specification.

**ASSUME-005**: Regular maintenance is performed per maintenance schedule (sensor calibration, lock inspection, emergency release testing).

### 9.2 Dependencies

**DEPEND-001**: System safety depends on correct operation of Train Control Management System (TCMS) for operational commands.

**DEPEND-002**: Safety interlocks depend on accurate speed information from Speed Monitoring System.

**DEPEND-003**: Hardware safety integrity depends on component quality and manufacturing per hardware specification.

**DEPEND-004**: Software safety integrity depends on EN 50128 SIL 3 development process compliance.

---

## 10. REFERENCES

### 10.1 Normative References

- **EN 50126-2:2017** - Railway applications - The specification and demonstration of RAMS - Part 2: Systems approach to safety
- **EN 50129:2018** - Railway applications - Communication, signalling and processing systems - Safety related electronic systems for signalling
- **EN 50128:2011** - Railway applications - Software for railway control and protection systems
- **EN 14752:2015** - Railway applications - Bodyside entrance systems
- **EN 50155:2017** - Railway applications - Electronic equipment used on rolling stock

### 10.2 Project References

- **System Requirements Specification** (DOC-SYS-REQ-YYYY-NNN)
- **System Architecture Description** (DOC-SYS-ARCH-YYYY-NNN)
- **Software Requirements Specification** (DOC-SRS-YYYY-NNN)
- **System Safety Plan** (DOC-SYS-SAFE-PLAN-YYYY-NNN)
- **Hazard Log** (docs/Hazard-Log.md)

---

## APPENDIX A: FMEA REPORT

[Detailed FMEA tables would be included here - abbreviated above in Section 2.3]

---

## APPENDIX B: FTA REPORT

[Detailed FTA analysis and quantitative calculations would be included here - abbreviated above in Section 2.4]

---

## DOCUMENT APPROVAL

This System Safety Requirements Specification is **APPROVED** as the safety baseline for software and hardware development.

**Baseline Version**: 1.0  
**Baseline Date**: YYYY-MM-DD  
**Configuration Item ID**: CI-SYS-SAFE-NNN  

Any changes to safety requirements SHALL be processed through the Change Control Board (CCB) with Safety Manager approval.

---

**END OF DOCUMENT**
