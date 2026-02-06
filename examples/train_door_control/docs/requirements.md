# Software Requirements Specification (SRS)
# Train Door Control System

## Document Information

| Property | Value |
|----------|-------|
| **Project** | Train Door Control System |
| **Document** | Software Requirements Specification (SRS) |
| **Version** | 1.0 |
| **Date** | 2026-02-06 |
| **SIL Level** | 3 |
| **Standard** | EN 50128:2011 Section 7.2 |

## 1. Introduction

### 1.1 Purpose

This document specifies the software requirements for the Train Door Control System, a safety-critical component responsible for controlling train door operations.

### 1.2 Scope

The Train Door Control System SHALL:
- Control door opening and closing operations
- Ensure doors are locked when train is moving
- Detect door sensor failures
- Implement safety interlocks

### 1.3 Safety Integrity Level

**SIL 3**: High safety integrity level due to potential hazards of doors opening during train movement.

## 2. System Overview

The Train Door Control System interfaces with:
- Door sensors (closed/locked status)
- Speed sensors (train speed)
- Door actuators (open/close/lock commands)
- Safety alarm system

## 3. Functional Requirements

### REQ-FUNC-001: Door Lock When Moving

**Type**: Functional (Safety)  
**SIL**: 3  
**Priority**: Mandatory  

**Description**:  
The system SHALL prevent doors from opening when train speed is greater than 0 km/h.

**Rationale**:  
Prevents passengers from falling out of moving train.

**Acceptance Criteria**:
1. Door open command SHALL be ignored when speed > 0 km/h
2. Door locks SHALL remain engaged when speed > 0 km/h
3. Safety alarm SHALL activate if door open attempted while moving

**Verification Method**: Test  
**Dependencies**: REQ-FUNC-002, REQ-FUNC-005  
**Traceability**: HAZ-001 (Unintended door opening)

---

### REQ-FUNC-002: Speed Monitoring

**Type**: Functional  
**SIL**: 3  
**Priority**: Mandatory  

**Description**:  
The system SHALL continuously monitor train speed with update rate of at least 10 Hz.

**Rationale**:  
Timely speed information is critical for door interlock safety.

**Acceptance Criteria**:
1. Speed SHALL be read at least every 100 ms
2. Speed value SHALL be validated for plausibility (0-350 km/h)
3. Speed sensor failure SHALL be detected within 200 ms

**Verification Method**: Test  
**Dependencies**: None  
**Traceability**: REQ-FUNC-001

---

### REQ-FUNC-003: Door Status Monitoring

**Type**: Functional  
**SIL**: 3  
**Priority**: Mandatory  

**Description**:  
The system SHALL monitor door closed and locked sensors continuously.

**Rationale**:  
Door status must be known to ensure safety interlocks.

**Acceptance Criteria**:
1. Door sensors SHALL be read at least every 50 ms
2. Sensor failure SHALL be detected within 100 ms
3. Inconsistent sensor states SHALL trigger fault condition

**Verification Method**: Test  
**Dependencies**: None  
**Traceability**: REQ-FUNC-001

---

### REQ-FUNC-004: Door Open Command

**Type**: Functional  
**SIL**: 3  
**Priority**: Mandatory  

**Description**:  
The system SHALL allow doors to open only when:
- Train speed is 0 km/h, AND
- Door unlock command is received, AND
- No safety faults are active

**Rationale**:  
Controlled door opening ensures passenger safety.

**Acceptance Criteria**:
1. All preconditions SHALL be verified before opening
2. Door open sequence SHALL complete within 5 seconds
3. Failed open attempt SHALL be logged

**Verification Method**: Test  
**Dependencies**: REQ-FUNC-001, REQ-FUNC-002  
**Traceability**: None

---

### REQ-FUNC-005: Door Close and Lock Command

**Type**: Functional  
**SIL**: 3  
**Priority**: Mandatory  

**Description**:  
The system SHALL close and lock doors when close command is received.

**Rationale**:  
Doors must be secured before train movement.

**Acceptance Criteria**:
1. Door close sequence SHALL complete within 3 seconds
2. Door locked status SHALL be confirmed via sensors
3. Lock failure SHALL prevent train movement authorization

**Verification Method**: Test  
**Dependencies**: REQ-FUNC-003  
**Traceability**: None

---

### REQ-FUNC-006: Emergency Door Release

**Type**: Functional  
**SIL**: 3  
**Priority**: Mandatory  

**Description**:  
The system SHALL provide emergency door release capability that overrides normal interlocks.

**Rationale**:  
Emergency egress may be required in hazardous situations.

**Acceptance Criteria**:
1. Emergency release SHALL unlock doors regardless of speed
2. Emergency release activation SHALL trigger safety alarm
3. Emergency release SHALL be logged

**Verification Method**: Test  
**Dependencies**: None  
**Traceability**: REQ-SAFE-002

---

## 4. Safety Requirements

### REQ-SAFE-001: Fail-Safe Behavior

**Type**: Safety  
**SIL**: 3  
**Priority**: Mandatory  

**Description**:  
The system SHALL enter fail-safe state upon detection of critical failure.

**Rationale**:  
System must default to safe state to prevent hazards.

**Acceptance Criteria**:
1. Fail-safe state SHALL lock all doors
2. Fail-safe state SHALL activate safety alarm
3. Fail-safe state SHALL prevent door opening until reset

**Verification Method**: Test, Analysis  
**Dependencies**: All functional requirements  
**Traceability**: HAZ-002 (Sensor failure)

---

### REQ-SAFE-002: Redundant Safety Checks

**Type**: Safety  
**SIL**: 3  
**Priority**: Mandatory  

**Description**:  
The system SHALL implement redundant checking of safety-critical conditions.

**Rationale**:  
Redundancy reduces probability of undetected failures.

**Acceptance Criteria**:
1. Speed check SHALL be performed by two independent paths
2. Door lock status SHALL be verified by multiple sensors
3. Disagreement SHALL trigger fail-safe state

**Verification Method**: Analysis, Test  
**Dependencies**: REQ-FUNC-002, REQ-FUNC-003  
**Traceability**: HAZ-001, HAZ-002

---

### REQ-SAFE-003: Watchdog Monitoring

**Type**: Safety  
**SIL**: 3  
**Priority**: Mandatory  

**Description**:  
The system SHALL implement watchdog monitoring with timeout of 100 ms.

**Rationale**:  
Detects software execution failures.

**Acceptance Criteria**:
1. Watchdog SHALL be refreshed every 50 ms during normal operation
2. Watchdog timeout SHALL trigger system reset
3. Watchdog SHALL be independent of main processor

**Verification Method**: Test  
**Dependencies**: None  
**Traceability**: HAZ-003 (Software failure)

---

## 5. Performance Requirements

### REQ-PERF-001: Response Time

**Type**: Performance  
**SIL**: 3  
**Priority**: Mandatory  

**Description**:  
The system SHALL respond to safety-critical inputs within 100 ms.

**Rationale**:  
Timely response prevents hazardous situations.

**Acceptance Criteria**:
1. Door lock command SHALL execute within 100 ms
2. Speed threshold detection SHALL occur within 100 ms
3. Sensor failure detection SHALL occur within 200 ms

**Verification Method**: Test  
**Dependencies**: All functional requirements  
**Traceability**: None

---

### REQ-PERF-002: Reliability

**Type**: Performance  
**SIL**: 3  
**Priority**: Mandatory  

**Description**:  
The system SHALL achieve failure rate of less than 10^-7 failures per hour.

**Rationale**:  
Meets SIL 3 reliability requirements per EN 50128.

**Acceptance Criteria**:
1. Demonstrated through reliability analysis
2. Verified through extensive testing
3. Field data monitoring

**Verification Method**: Analysis, Test  
**Dependencies**: All requirements  
**Traceability**: SIL 3 allocation

---

## 6. Interface Requirements

### REQ-INTF-001: Speed Sensor Interface

**Type**: Interface  
**SIL**: 3  
**Priority**: Mandatory  

**Description**:  
The system SHALL interface with speed sensor providing digital output (0-350 km/h range).

**Rationale**:  
Speed information is critical for door interlock.

**Acceptance Criteria**:
1. Input range: 0-350 km/h
2. Resolution: 1 km/h
3. Update rate: ≥ 10 Hz
4. Interface: Digital (CAN bus or similar)

**Verification Method**: Test, Inspection  
**Dependencies**: REQ-FUNC-002  
**Traceability**: None

---

### REQ-INTF-002: Door Sensor Interface

**Type**: Interface  
**SIL**: 3  
**Priority**: Mandatory  

**Description**:  
The system SHALL interface with door sensors (closed and locked status).

**Rationale**:  
Door status is required for safety interlocks.

**Acceptance Criteria**:
1. Inputs: Door closed (binary), Door locked (binary)
2. Number of sensors: 2 per door (redundant)
3. Update rate: ≥ 20 Hz
4. Interface: Digital I/O

**Verification Method**: Test, Inspection  
**Dependencies**: REQ-FUNC-003  
**Traceability**: None

---

### REQ-INTF-003: Door Actuator Interface

**Type**: Interface  
**SIL**: 3  
**Priority**: Mandatory  

**Description**:  
The system SHALL interface with door actuators for open/close/lock commands.

**Rationale**:  
Actuators control physical door operation.

**Acceptance Criteria**:
1. Outputs: Open command, Close command, Lock command
2. Interface: Digital outputs with current monitoring
3. Command acknowledgment required

**Verification Method**: Test, Inspection  
**Dependencies**: REQ-FUNC-004, REQ-FUNC-005  
**Traceability**: None

---

## 7. Data Requirements

### REQ-DATA-001: Data Types

**Type**: Data  
**SIL**: 3  
**Priority**: Mandatory  

**Description**:  
The system SHALL use fixed-width data types for all variables.

**Rationale**:  
Ensures consistent behavior across platforms (MISRA C compliance).

**Acceptance Criteria**:
1. Use uint8_t, uint16_t, uint32_t (not int, long)
2. Use bool for boolean values (not int)
3. Document valid ranges for all variables

**Verification Method**: Code Review  
**Dependencies**: All implementation  
**Traceability**: MISRA C:2012

---

### REQ-DATA-002: Memory Allocation

**Type**: Data  
**SIL**: 3  
**Priority**: Mandatory  

**Description**:  
The system SHALL use static memory allocation only (no dynamic allocation).

**Rationale**:  
Prevents memory leaks and fragmentation (SIL 3 requirement).

**Acceptance Criteria**:
1. No use of malloc, calloc, realloc, free
2. All arrays statically sized
3. Maximum stack usage documented

**Verification Method**: Code Review, Static Analysis  
**Dependencies**: All implementation  
**Traceability**: EN 50128 Table A.18

---

## 8. Constraints

### REQ-CONS-001: MISRA C Compliance

**Type**: Constraint  
**SIL**: 3  
**Priority**: Mandatory  

**Description**:  
The system SHALL comply with MISRA C:2012 coding standard.

**Rationale**:  
Mandatory for SIL 3 per EN 50128 Table A.18.

**Acceptance Criteria**:
1. Zero mandatory rule violations
2. Required rule violations documented and justified
3. Static analysis verification

**Verification Method**: Static Analysis  
**Dependencies**: All implementation  
**Traceability**: EN 50128 Table A.18

---

### REQ-CONS-002: Cyclomatic Complexity

**Type**: Constraint  
**SIL**: 3  
**Priority**: Mandatory  

**Description**:  
The system SHALL limit cyclomatic complexity to 10 or less per function.

**Rationale**:  
Reduces testing burden and improves understandability (SIL 3 requirement).

**Acceptance Criteria**:
1. Maximum complexity per function: 10
2. Measured using standard tools (Lizard, PC-lint)
3. Violations require justification

**Verification Method**: Static Analysis  
**Dependencies**: All implementation  
**Traceability**: EN 50128 Table A.4

---

## 9. Requirements Traceability Matrix

| Requirement ID | Type | SIL | Hazard | Design Element | Test Case |
|----------------|------|-----|--------|----------------|-----------|
| REQ-FUNC-001 | Functional | 3 | HAZ-001 | door_control.c | TC-001 |
| REQ-FUNC-002 | Functional | 3 | - | speed_monitor.c | TC-002 |
| REQ-FUNC-003 | Functional | 3 | - | sensor_monitor.c | TC-003 |
| REQ-FUNC-004 | Functional | 3 | - | door_control.c | TC-004 |
| REQ-FUNC-005 | Functional | 3 | - | door_control.c | TC-005 |
| REQ-FUNC-006 | Functional | 3 | REQ-SAFE-002 | door_control.c | TC-006 |
| REQ-SAFE-001 | Safety | 3 | HAZ-002 | All modules | TC-010 |
| REQ-SAFE-002 | Safety | 3 | HAZ-001, HAZ-002 | All monitors | TC-011 |
| REQ-SAFE-003 | Safety | 3 | HAZ-003 | watchdog.c | TC-012 |
| REQ-PERF-001 | Performance | 3 | - | All modules | TC-020 |
| REQ-PERF-002 | Performance | 3 | - | System | TC-021 |

## 10. Hazard Analysis Summary

| Hazard ID | Description | Severity | Mitigation |
|-----------|-------------|----------|------------|
| HAZ-001 | Unintended door opening during movement | Catastrophic | REQ-FUNC-001, REQ-SAFE-002 |
| HAZ-002 | Sensor failure undetected | Critical | REQ-SAFE-001, REQ-SAFE-002 |
| HAZ-003 | Software execution failure | Critical | REQ-SAFE-003 |

## 11. Verification Summary

All requirements SHALL be verified using one or more of the following methods:

- **Test**: Functional testing on target or simulator
- **Analysis**: Design analysis, FMEA, FTA
- **Code Review**: Manual inspection by independent reviewer
- **Static Analysis**: Automated tools (PC-lint, Cppcheck)

**Coverage Requirements (SIL 3)**:
- Statement coverage: 100%
- Branch coverage: 100%
- MC/DC coverage: 100%

## 12. Document Approval

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Requirements Engineer | [Name] | | |
| Safety Manager | [Name] | | |
| Project Manager | [Name] | | |

---

**Document Version**: 1.0  
**Last Updated**: 2026-02-06  
**Next Review**: [Date]
