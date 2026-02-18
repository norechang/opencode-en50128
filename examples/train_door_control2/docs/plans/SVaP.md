# Software Validation Plan

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SVAP-2026-001 |
| **Version** | 2.0 |
| **Date** | 2026-02-18 |
| **Project** | train_door_control2 |
| **SIL Level** | 3 |
| **Author** | Independent Validator |
| **Reviewer** | Safety Manager |
| **Approver** | Project Manager |
| **Status** | Draft |

---

## Document Control

| Version | Date | Author | Changes | Approval Status |
|---------|------|--------|---------|-----------------|
| 0.1 | 2026-02-18 | Independent Validator | Initial draft | Draft |
| 1.0 | 2026-02-18 | Independent Validator | First approved version | Approved |
| 2.0 | 2026-02-18 | Independent Validator | Major revision: Added standard header, Document Control table, Approvals table, and enhanced template compliance per EN 50128 Section 7.7 | Draft |

---

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author** | Independent Validator | | 2026-02-18 |
| **Independent Validator** (SIL 3) | Independent Validator | | |
| **Safety Manager** | Safety Manager | | |
| **Project Manager** | Project Manager | | |

---

## Table of Contents

1. [Introduction](#1-introduction)
2. [Validation Approach](#2-validation-approach)
3. [Validation Environment](#3-validation-environment)
4. [Validation Test Cases](#4-validation-test-cases)
5. [Validation Methods](#5-validation-methods)
6. [Acceptance Criteria](#6-acceptance-criteria)
7. [Independence Requirements](#7-independence-requirements)
8. [Schedule](#8-schedule)
9. [Resources](#9-resources)
10. [Deliverables](#10-deliverables)
11. [Risk Assessment](#11-risk-assessment)
12. [Traceability](#12-traceability)
13. [References](#13-references)

---

## 1. Introduction

### 1.1 Purpose

This Software Validation Plan (SVaP) defines the validation strategy, activities, and acceptance criteria for the train_door_control2 software. Validation confirms that the software fulfills its intended use in the operational railway environment in accordance with EN 50128:2011 Section 7.7.

**Validation Definition** (EN 50128): Confirmation by examination and provision of objective evidence that the particular requirements for the specific intended use are fulfilled.

### 1.2 Scope

**Software Component:** train_door_control2

**SIL Level:** 3

**Target Platform:** Embedded microcontroller with door sensors/actuators

**Operational Environment:** Railway train door control system

**Validation Coverage:**
- System-level testing in target environment
- Operational scenario validation for railway door operations
- User acceptance testing with train operators
- Performance validation for real-time constraints
- Safety validation for SIL 3 compliance

### 1.3 SIL Classification

**Target SIL Level**: 3

**EN 50128 Validation Requirements** (Table A.7):

**SIL 3 Mandatory Techniques:**
- Performance Testing (**M**)
- Functional and Black-box Testing (**M**)

**Independence Requirements:**
- **SIL 3**: **Independent Validator MANDATORY** (different person/team from developers and verifiers)

### 1.4 Application Context

**Railway Door Control Application:**
- Safety-critical door control for passenger trains
- Interlocks with train speed and station position
- Emergency door release capability
- Fault detection and fail-safe behavior

### 1.5 Definitions and Acronyms

| Term | Definition |
|------|------------|
| **Validation** | Confirmation that software fulfills its intended use |
| **Verification** | Confirmation that software outputs correctly implement specifications |
| **HIL** | Hardware-in-the-Loop testing |
| **SIL** | Safety Integrity Level (0-4) |
| **RTM** | Requirements Traceability Matrix |

### 1.6 References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems |
| **[EN50126]** | EN 50126-1:2017 Railway Applications - RAMS |
| **[MISRA]** | MISRA C:2012 Guidelines for the use of the C language in critical systems |
| **[SRS]** | Software Requirements Specification - train_door_control2 |
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-2026-001 |
| **[SCMP]** | Software Configuration Management Plan, DOC-SCMP-2026-001 |
| **[SVP]** | Software Verification Plan, DOC-SVP-2026-001 |
| **[System Spec]** | System Requirements Specification |
| **[LIFECYCLE]** | LIFECYCLE.md - EN 50128 V-Model lifecycle definition |

---

## 2. Validation Approach

### 2.1 Validation Strategy

The validation strategy for train_door_control2 SIL 3 includes:

1. **System-level testing** in target environment (embedded railway controller)
2. **Operational scenario validation** for railway door operations (normal and fault conditions)
3. **User acceptance testing** with train operators and railway domain experts
4. **Performance validation** for real-time constraints (response times < 100ms)
5. **Safety validation** for SIL 3 compliance (fault injection, fail-safe behavior)

**Validation Focus:**
- Validate that software meets user needs and operational requirements
- Confirm safe operation in railway environment
- Verify performance under real-world conditions
- Ensure usability and operator acceptance

### 2.2 Validation Phases

**Phase 1: Laboratory Validation**
- Hardware-in-the-Loop (HIL) testing
- Functional and performance testing
- Safety testing with fault injection

**Phase 2: Operational Validation**
- Testing in simulated operational environment
- Full operational scenario coverage
- Stress testing and edge cases

**Phase 3: User Acceptance Testing**
- Train operator validation
- Customer acceptance
- Final sign-off

### 2.3 Validation Techniques (EN 50128 Table A.7)

**Mandatory for SIL 3:**
- **Performance Testing** (Table A.18) - **MANDATORY**
- **Functional and Black-box Testing** (Table A.14) - **MANDATORY**

**Highly Recommended:**
- Modelling (Table A.17) - Recommended for complex scenarios

---

## 3. Validation Environment

### 3.1 Target Platform

**Hardware:**
- Railway-grade microcontroller (ARM Cortex-M based)
- Door position sensors (CAN bus interface)
- Door actuators (digital I/O)
- Speed sensor interface
- Emergency button interface

**Operating System:** Bare-metal RTOS

**Communication Interfaces:**
- CAN bus for sensors
- Digital I/O for actuators
- Serial interface for diagnostics

### 3.2 Test Environment

**Laboratory Setup:**
- Hardware test bench with simulated train conditions
- Hardware-in-the-Loop (HIL) system for actuator and sensor simulation
- CAN bus simulator for train speed and position signals
- Fault injection equipment

**Simulation Environment:**
- PC-based simulation for initial validation
- Real-time simulation of door mechanics
- Sensor fault injection capability

**Real Operational Environment:**
- Planned for final acceptance testing
- On-site testing with train operators
- Customer acceptance in operational conditions

### 3.3 Test Equipment

**Required Equipment:**
- HIL test bench with door actuator simulation
- Oscilloscopes for timing measurements
- CAN bus analyzers for protocol validation
- Fault injection hardware
- Data logging equipment

---

## 4. Validation Test Cases

### 4.1 Functional Validation

**Test Cases:**
- **TC-VAL-FUNC-001**: Door lock interlock when speed > 0 km/h
- **TC-VAL-FUNC-002**: Door open command with safety preconditions (speed = 0, station position)
- **TC-VAL-FUNC-003**: Door close command with obstruction detection
- **TC-VAL-FUNC-004**: Sensor monitoring and failure detection
- **TC-VAL-FUNC-005**: Emergency door release functionality
- **TC-VAL-FUNC-006**: Multiple door coordination
- **TC-VAL-FUNC-007**: Operator interface commands

**Pass Criteria:** All functional requirements met, all tests passed

### 4.2 Performance Validation

**Test Cases:**
- **TC-VAL-PERF-001**: Response time validation (< 100ms for safety-critical functions)
- **TC-VAL-PERF-002**: Execution time measurement for all critical paths
- **TC-VAL-PERF-003**: Resource usage validation (CPU utilization < 70%, memory < 80%)
- **TC-VAL-PERF-004**: Stack usage validation (no overflow)
- **TC-VAL-PERF-005**: Interrupt latency validation

**Pass Criteria:** All performance requirements met, response times within limits

### 4.3 Safety Validation

**Test Cases:**
- **TC-VAL-SAFE-001**: Fail-safe behavior on door sensor failures
- **TC-VAL-SAFE-002**: Fail-safe behavior on speed sensor failures
- **TC-VAL-SAFE-003**: Redundant safety checks validation
- **TC-VAL-SAFE-004**: Watchdog functionality testing
- **TC-VAL-SAFE-005**: Fault injection testing (single and multiple faults)
- **TC-VAL-SAFE-006**: Common cause failure mitigation
- **TC-VAL-SAFE-007**: Emergency stop response

**Pass Criteria:** Safe state maintained under all fault conditions

### 4.4 Operational Scenarios

**Test Cases:**
- **TC-VAL-OPS-001**: Normal train station stop and departure sequence
- **TC-VAL-OPS-002**: Passenger boarding and alighting (door open/close cycles)
- **TC-VAL-OPS-003**: Emergency braking with door safety interlocks
- **TC-VAL-OPS-004**: Fault conditions and recovery procedures
- **TC-VAL-OPS-005**: Multiple door operations (simultaneous open/close)
- **TC-VAL-OPS-006**: Operator interface validation (commands, status display)
- **TC-VAL-OPS-007**: Maintenance mode operations
- **TC-VAL-OPS-008**: Edge cases (rapid command sequences, operator errors)

**Pass Criteria:** All operational scenarios execute correctly, operator acceptance obtained

---

## 5. Validation Methods

### 5.1 Functional Testing (EN 50128 Table A.14)

**Method:** Black-box testing of all system requirements

**Techniques:**
- Boundary value analysis (door position limits, speed thresholds)
- State transition testing (door states: closed, opening, open, closing)
- Equivalence partitioning

**Coverage:** 100% of system requirements

### 5.2 Performance Testing (EN 50128 Table A.18)

**Method:** Response time measurement and execution profiling

**Techniques:**
- Response time measurement for safety-critical functions
- Execution profiling with oscilloscope
- Resource monitoring (CPU, memory, stack usage)
- Worst-case execution time (WCET) analysis

**Acceptance:**
- Response times < 100ms for safety-critical functions
- CPU utilization < 70%
- Memory usage < 80%

### 5.3 Safety Testing

**Method:** Fault injection and failure mode analysis

**Techniques:**
- Single fault injection (sensor failures, actuator failures)
- Multiple fault injection (combined failures)
- Redundancy validation (redundant sensors, safety checks)
- Watchdog testing (software hang, infinite loop)

**Acceptance:**
- Safe state maintained under all fault conditions
- No single point of failure

### 5.4 User Acceptance Testing

**Method:** Operational validation with train operators

**Techniques:**
- Operational scenario execution by operators
- Usability assessment
- Customer feedback collection

**Acceptance:**
- Operator approval
- Customer sign-off

### 5.5 Coverage Requirements (SIL 3)

**EN 50128 Table A.21 (Test Coverage for Code):**
- **Statement coverage:** 100% (MANDATORY)
- **Branch coverage:** 100% (MANDATORY)
- **MC/DC coverage:** 100% (MANDATORY)

**Tools:** gcov/lcov for coverage analysis

---

## 6. Acceptance Criteria

### 6.1 Functional Acceptance

- [ ] All system-level functional tests passed
- [ ] All requirements validated (100% coverage)
- [ ] No critical or major defects open
- [ ] All operational scenarios validated

### 6.2 Performance Acceptance

- [ ] Response times within limits (< 100ms for safety-critical functions)
- [ ] Resource usage within limits (CPU < 70%, Memory < 80%)
- [ ] Performance requirements met in operational environment

### 6.3 Safety Acceptance

- [ ] Safety requirements validated with fault injection
- [ ] Fail-safe behavior verified under all fault conditions
- [ ] No single point of failure
- [ ] Watchdog functionality verified

### 6.4 User Acceptance

- [ ] Customer acceptance obtained from railway operators
- [ ] Operator training completed
- [ ] Usability approved

### 6.5 Documentation Acceptance

- [ ] Independent validation report approved
- [ ] Validation test results complete
- [ ] Traceability report complete (100% bidirectional)
- [ ] Acceptance certificate signed

---

## 7. Independence Requirements

### 7.1 EN 50128 Requirements

Per EN 50128 Section 5.3.7 and Table A.7:

**SIL 3 (MANDATORY):**
- **Independent Validation MANDATORY**
- Validator SHALL NOT be the same person as designer, implementer, or verifier
- Validator SHALL be organizationally independent from development and verification teams
- Validator SHALL have authority to reject software that does not meet validation criteria
- Validator SHALL report directly to Safety Manager (NOT Project Manager)

### 7.2 Implementation

**Validation Team:**
- Independent Validator (Lead)
- Validation Engineers

**Independence Verification:**
- [x] Validator organizationally separate from development and verification
- [x] Validator reports to Safety Manager (not Project Manager)
- [x] Validator has authority to reject non-compliant software

**Reporting Line:** Safety Manager (not Project Manager)

---

## 8. Schedule

### 8.1 Validation Timeline

**Validation Start:** [Date TBD - After Phase 5 Integration completion]

**Phase 1: Laboratory Validation**
- Duration: 2 weeks
- Deliverable: Laboratory Test Results

**Phase 2: Operational Validation**
- Duration: 2 weeks
- Deliverable: Operational Test Results

**Phase 3: User Acceptance Testing**
- Duration: 1 week
- Deliverable: Acceptance Certificate

**Validation End:** [Date TBD + 5 weeks]

**Acceptance Review:** [Date TBD + 6 weeks]

### 8.2 Milestones

- **Validation Kickoff**: After integration testing complete
- **HIL Setup Complete**: Week 1
- **Laboratory Validation Complete**: Week 2
- **Operational Validation Complete**: Week 4
- **User Acceptance Complete**: Week 5
- **Validation Report Approved**: Week 6

---

## 9. Resources

### 9.1 Personnel

**Validation Team:**
- 1 Independent Validator (Lead)
- 1 Validation Engineer (test execution)
- 1 Test Automation Engineer (optional)

**Other Roles:**
- Train operators (user acceptance testing)
- Railway domain experts (operational scenario validation)

### 9.2 Test Equipment

**Required Equipment:**
- HIL test bench with door actuator simulation
- Oscilloscopes for timing measurements
- CAN bus analyzers for protocol validation
- Fault injection hardware
- Data logging equipment
- Target hardware (railway controller)

### 9.3 Software Tools

**Tools:**
- Test automation scripts (Python)
- Coverage tools (gcov/lcov)
- CAN bus analysis tools
- Data analysis tools

### 9.4 Budget

**Estimated Budget:** [TBD]
- Personnel costs
- Equipment costs
- Travel costs (for on-site testing)

---

## 10. Deliverables

### 10.1 Validation Documents

**Required Deliverables:**
- Validation Test Specification (detailed test cases)
- Validation Test Procedures (step-by-step instructions)
- Validation Test Results (test execution records)
- Validation Report (summary, findings, acceptance decision)
- Acceptance Certificate (customer sign-off)
- Traceability Report (requirements-to-tests traceability)

**Deliverable Storage:** `docs/validation/`

**Deliverable Review:** All deliverables reviewed by Safety Manager and Independent Validator

### 10.2 Evidence Collection

**Validation Evidence:**
- Test execution logs
- Performance measurement data
- Coverage reports (100% statement/branch/MC/DC)
- Fault injection records
- Operator feedback
- Customer acceptance sign-off

**Evidence Storage:** `docs/validation/evidence/`

**Evidence Retention:** Project lifecycle + 10 years

---

## 11. Risk Assessment

### 11.1 Validation Risks

| Risk | Impact | Likelihood | Mitigation |
|------|--------|------------|------------|
| Inadequate test environment setup | High | Medium | Early HIL setup, equipment testing |
| Incomplete operational scenario coverage | High | Medium | Domain expert review, operator involvement |
| Performance measurement inaccuracies | Medium | Low | Calibrated equipment, multiple measurements |
| Target hardware unavailable | High | Low | Early hardware procurement, backup plan |
| Customer unavailable for acceptance | Medium | Medium | Schedule coordination, alternative acceptance process |

### 11.2 Mitigation Strategies

**Test Environment:**
- Early HIL setup and commissioning (Phase 1)
- Equipment calibration and validation
- Backup equipment available

**Operational Scenarios:**
- Domain expert review of test cases
- Operator involvement in scenario definition
- Comprehensive scenario coverage analysis

**Performance Measurement:**
- Calibrated measurement equipment
- Multiple measurements for statistical confidence
- Independent measurement verification

**Hardware Availability:**
- Early hardware procurement
- Backup hardware units
- Simulation as fallback

**Customer Availability:**
- Early schedule coordination
- Flexible acceptance process
- Remote acceptance option

---

## 12. Traceability

### 12.1 Traceability Requirements

**SIL 3 (MANDATORY):**
- 100% bidirectional traceability from system requirements to validation tests
- All system requirements shall have corresponding validation test cases
- All validation test cases shall trace to system requirements

### 12.2 Traceability Matrix

**Traceability Links:**
```
System Requirements → Software Requirements → Validation Test Cases → Test Results
```

**Traceability Verification:**
- Independent review of traceability matrix
- No orphan requirements (all requirements tested)
- No orphan test cases (all tests trace to requirements)

**Traceability Report:** Deliverable at validation completion

---

## 13. References

### 13.1 Normative References

1. EN 50128:2011 Railway applications - Communication, signalling and processing systems - Software for railway control and protection systems
2. EN 50126-1:2017 Railway Applications - The Specification and Demonstration of Reliability, Availability, Maintainability and Safety (RAMS)
3. MISRA C:2012 Guidelines for the use of the C language in critical systems
4. IEC 61508:2010 Functional safety of electrical/electronic/programmable electronic safety-related systems

### 13.2 Project References

| Reference | Document ID |
|-----------|-------------|
| **Software Requirements Specification** | train_door_control2 SRS |
| **System Requirements Specification** | System Spec |
| **Software Quality Assurance Plan** | DOC-SQAP-2026-001 |
| **Software Configuration Management Plan** | DOC-SCMP-2026-001 |
| **Software Verification Plan** | DOC-SVP-2026-001 |
| **Lifecycle Definition** | LIFECYCLE.md |

---

**END OF DOCUMENT**
