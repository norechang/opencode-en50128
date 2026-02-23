# Safety Case

**Document ID**: DOC-SAF-YYYY-NNN  
**Version**: 0.1  
**Date**: YYYY-MM-DD  
**Project**: [Project Name]  
**SIL Level**: [0, 1, 2, 3, or 4]  
**Author**: Safety Engineer (SAF)  
**Status**: Draft

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SAF-YYYY-NNN |
| **Version** | 0.1 |
| **Date** | YYYY-MM-DD |
| **Project** | [Project Name] |
| **SIL Level** | [0, 1, 2, 3, or 4] |
| **Author** | Safety Engineer (SAF) |
| **Reviewer** | [Name, Role] |
| **Approver** | Safety Manager, Customer |
| **Status** | Draft |

---

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | YYYY-MM-DD | SAF Engineer | Initial Safety Case | - |
| 1.0 | TBD | SAF Engineer | First approved version | TBD |

---

## APPROVALS

**SIL 3-4 Requirements**: Author, Independent Reviewer, Safety Manager, Independent Assessor, Customer

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author (Safety Engineer)** | [Name] | | YYYY-MM-DD |
| **Independent Reviewer** | TBD | | |
| **Safety Manager** | TBD | | |
| **Independent Assessor** | TBD | | |
| **QA Manager** | TBD | | |
| **Customer Representative** | TBD | | |
| **Railway Safety Authority** | TBD | | |

---

## 1. EXECUTIVE SUMMARY

### 1.1 Safety Claim

**Primary Claim**: **[System Name]** achieves Safety Integrity Level **[SIL X]** and is safe for deployment in railway operations in accordance with EN 50128:2011 and EN 50126:2017.

### 1.2 System Description

**System**: [System Name]  
**Function**: [Primary safety function]  
**Application**: [Railway application context]  
**SIL Level**: [0, 1, 2, 3, or 4]  
**Deployment**: [Deployment environment]

### 1.3 Safety Case Summary

This Safety Case demonstrates that **[System Name]** is acceptably safe for railway operation by presenting:

1. **Hazard Identification**: All foreseeable hazards identified and analyzed
2. **Risk Assessment**: Risks assessed and SIL levels assigned
3. **Safety Requirements**: Comprehensive safety requirements derived from hazards
4. **Safety Architecture**: System designed with fail-safe principles and redundancy
5. **Implementation**: Software developed to SIL [X] standards (MISRA C, defensive programming)
6. **Verification**: Independent verification confirms requirements met
7. **Validation**: System validated in operational scenarios
8. **Residual Risk**: All residual risks are tolerable (ALARP demonstrated)

**Recommendation**: **[APPROVE / CONDITIONAL APPROVAL / REJECT]** for deployment

---

## 2. INTRODUCTION

### 2.1 Purpose

This Safety Case provides a structured argument, supported by evidence, that **[System Name]** is acceptably safe for its intended railway application at Safety Integrity Level **[SIL X]**.

**Safety Case Objectives**:
- Present clear safety claims
- Provide systematic safety arguments
- Reference supporting evidence
- Demonstrate compliance with EN 50128:2011 and EN 50126:2017
- Support regulatory approval and customer acceptance

### 2.2 Scope

**In Scope**:
- Software safety (primary focus)
- Hardware-software interface safety
- System-level safety relevant to software
- Software lifecycle process compliance (EN 50128)
- RAMS requirements (EN 50126)

**Out of Scope**:
- Pure hardware safety (covered by hardware safety case)
- Mechanical safety (covered by mechanical design documentation)
- Electromagnetic compatibility (covered by EMC testing - EN 50121)
- System-level safety case (this document supports system-level case)

### 2.3 Intended Audience

- Railway safety authorities (regulatory approval)
- Customer safety managers (acceptance decision)
- Independent safety assessors (EN 50128 Section 6.4)
- Project management and engineering teams
- Maintenance and operations personnel

### 2.4 Safety Case Structure

This Safety Case follows the **Goal Structuring Notation (GSN)** approach:
- **Goals**: Safety claims to be demonstrated
- **Strategies**: Approach to demonstrating goals
- **Evidence**: Supporting documentation and test results
- **Context**: Assumptions, scope, and operating environment

### 2.5 References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems |
| **[EN50126-1]** | EN 50126-1:2017 Railway applications - RAMS - Part 1: Generic RAMS process |
| **[EN50126-2]** | EN 50126-2:2017 Railway applications - RAMS - Part 2: Systems approach to safety |
| **[EN50129]** | EN 50129:2018 Railway applications - Safety related electronic systems for signalling |
| **[HAZ]** | Hazard Log, DOC-HAZLOG-YYYY-NNN |
| **[FMEA]** | FMEA Report, DOC-FMEA-YYYY-NNN |
| **[FTA]** | FTA Report, DOC-FTA-YYYY-NNN |
| **[SRS]** | Software Requirements Specification, DOC-SRS-YYYY-NNN |
| **[SAS]** | Software Architecture Specification, DOC-SAS-YYYY-NNN |
| **[SDS]** | Software Design Specification, DOC-SDS-YYYY-NNN |
| **[SVP]** | Software Verification Plan, DOC-SVP-YYYY-NNN |
| **[SVR]** | Software Verification Report, DOC-SVR-YYYY-NNN |
| **[SVaP]** | Software Validation Plan, DOC-SVAP-YYYY-NNN |
| **[SVaR]** | Software Validation Report, DOC-SVAR-YYYY-NNN |
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-YYYY-NNN |
| **[SCMP]** | Software Configuration Management Plan, DOC-SCMP-YYYY-NNN |

---

## 3. SYSTEM DESCRIPTION

### 3.1 System Overview

**System Name**: [System Name]  
**System ID**: [System Identifier]  
**Version**: [Version Number]

**Primary Function**: [Detailed description of primary safety function]

**Operational Context**: [Railway operational environment]

**Interfaces**:
- **Inputs**: [Sensors, signals, commands]
- **Outputs**: [Actuators, displays, alarms]
- **Communications**: [CAN bus, Ethernet, etc.]

### 3.2 System Boundary

**Software Boundary**: [What software components are in scope]

**Hardware Boundary**: [Hardware components that interact with software]

**Environmental Boundary**: [Operating conditions - temperature, vibration, EMI]

### 3.3 Safety Functions

| Safety Function ID | Description | SIL | Related Hazards |
|-------------------|-------------|-----|-----------------|
| SF-01 | [Safety function] | [SIL] | [HAZ-IDs] |
| SF-02 | [Safety function] | [SIL] | [HAZ-IDs] |

### 3.4 Operational Scenarios

**Normal Operation**: [Description]

**Degraded Operation**: [Description]

**Emergency Operation**: [Description]

**Maintenance Mode**: [Description]

---

## 4. SAFETY ARGUMENT

### 4.1 Top-Level Safety Claim

**Goal G1**: **[System Name] is acceptably safe for railway operation at SIL [X]**

**Context**:
- System operates in [railway environment]
- Compliance required with EN 50128:2011 (SIL [X])
- Compliance required with EN 50126:2017 (RAMS)
- Target failure rate: < 10^-X per hour for safety-critical functions

### 4.2 Safety Argument Structure (GSN)

```
┌──────────────────────────────────────────────────┐
│ G1: [System] is acceptably safe for SIL [X]     │
│     railway operation                            │
└────────────────────┬─────────────────────────────┘
                     │
         ┌───────────┴───────────┐
         │    S1: Argument by    │
         │    EN 50128 Lifecycle │
         └───────────┬───────────┘
                     │
    ┌────────────────┼────────────────┐
    │                │                │
    ▼                ▼                ▼
┌───────┐        ┌───────┐        ┌───────┐
│  G2:  │        │  G3:  │        │  G4:  │
│Hazards│        │Safety │        │ V&V   │
│Identif│        │Design │        │Complete│
└───┬───┘        └───┬───┘        └───┬───┘
    │                │                │
    ▼                ▼                ▼
[Evidence]      [Evidence]      [Evidence]
```

### 4.3 Sub-Goal G2: All Hazards Identified and Mitigated

**Goal G2**: All foreseeable hazards have been identified, analyzed, and mitigated to tolerable risk levels.

**Strategy S2**: Systematic hazard analysis per EN 50126

**Sub-Goals**:
- **G2.1**: Hazard identification complete
- **G2.2**: Risk assessment performed for all hazards
- **G2.3**: SIL levels assigned based on risk
- **G2.4**: Safety requirements derived from hazards
- **G2.5**: Mitigations implemented and verified
- **G2.6**: Residual risk is tolerable (ALARP)

**Evidence**:
- **E2.1**: Hazard Log [HAZ] - [Count] hazards identified
- **E2.2**: FMEA Report [FMEA] - Failure modes analyzed
- **E2.3**: FTA Report [FTA] - Top event probabilities calculated
- **E2.4**: SRS [SRS] - [Count] safety requirements defined
- **E2.5**: Verification Report [SVR] - All requirements verified
- **E2.6**: Residual Risk Assessment [HAZ, Section 9]

**Assessment**: **[SATISFIED / NOT SATISFIED]**

---

### 4.4 Sub-Goal G3: System Designed for Safety

**Goal G3**: System architecture and design incorporate fail-safe principles, redundancy, and defensive programming appropriate for SIL [X].

**Strategy S3**: Design per EN 50128 SIL [X] techniques (Table A.3, A.4)

**Sub-Goals**:
- **G3.1**: Modular architecture (mandatory SIL 2+)
- **G3.2**: Redundancy for critical functions
- **G3.3**: Fail-safe design (default to safe state)
- **G3.4**: Defensive programming (MISRA C, bounds checks)
- **G3.5**: Complexity within limits (≤ 10 for SIL 3-4)
- **G3.6**: Static memory allocation (no malloc for SIL 2+)

**Evidence**:
- **E3.1**: Software Architecture Specification [SAS]
- **E3.2**: Software Design Specification [SDS]
- **E3.3**: Design Review Reports [QA reviews]
- **E3.4**: Complexity Analysis Report [VER] - All modules ≤ 10
- **E3.5**: MISRA C Compliance Report [VER] - Zero mandatory violations
- **E3.6**: Static Analysis Report [VER] - No malloc/free calls

**Assessment**: **[SATISFIED / NOT SATISFIED]**

---

### 4.5 Sub-Goal G4: Verification and Validation Complete

**Goal G4**: All safety requirements have been verified and the system has been validated in operational scenarios.

**Strategy S4**: Independent V&V per EN 50128 SIL [X] requirements

**Sub-Goals**:
- **G4.1**: All requirements traced and verified
- **G4.2**: Test coverage meets SIL [X] target
- **G4.3**: Static analysis performed (SIL 3-4 mandatory)
- **G4.4**: Independent verification performed (SIL 3-4 mandatory)
- **G4.5**: System validation performed (SIL 3-4 mandatory)
- **G4.6**: No open safety-critical defects

**Evidence**:
- **E4.1**: Requirements Traceability Matrix [RTM] - 100% traced
- **E4.2**: Test Reports [STR] - Coverage: Statement [X]%, Branch [Y]%, Condition [Z]%
- **E4.3**: Static Analysis Report [SVR] - PC-lint, Cppcheck
- **E4.4**: Verification Report [SVR] - Independent verifier approval
- **E4.5**: Validation Report [SVaR] - Independent validator approval
- **E4.6**: Defect Log - [Count] open defects, [Count] safety-critical (0 target)

**Assessment**: **[SATISFIED / NOT SATISFIED]**

---

### 4.6 Sub-Goal G5: Process Compliance

**Goal G5**: Software developed in accordance with EN 50128:2011 lifecycle and process requirements for SIL [X].

**Strategy S5**: Compliance with EN 50128 mandatory processes

**Sub-Goals**:
- **G5.1**: Software Quality Assurance Plan followed
- **G5.2**: Software Configuration Management Plan followed
- **G5.3**: Software Verification Plan followed
- **G5.4**: Software Validation Plan followed
- **G5.5**: Independent assessment performed (SIL 3-4 mandatory)
- **G5.6**: All mandatory EN 50128 techniques applied

**Evidence**:
- **E5.1**: SQAP [SQAP] and QA Audit Reports
- **E5.2**: SCMP [SCMP] and Configuration Audit Reports
- **E5.3**: SVP [SVP] and Verification Report [SVR]
- **E5.4**: SVaP [SVaP] and Validation Report [SVaR]
- **E5.5**: Independent Assessment Report [ASS] (SIL 3-4)
- **E5.6**: EN 50128 Compliance Matrix

**Assessment**: **[SATISFIED / NOT SATISFIED]**

---

## 5. HAZARD ANALYSIS SUMMARY

### 5.1 Identified Hazards

| Hazard ID | Description | Severity | Frequency | Initial Risk | SIL | Mitigated? |
|-----------|-------------|----------|-----------|--------------|-----|------------|
| HAZ-001 | [Description] | [Level] | [Freq] | [Risk] | [SIL] | [Yes/No] |
| HAZ-002 | [Description] | [Level] | [Freq] | [Risk] | [SIL] | [Yes/No] |

**Total Hazards**: [Count]  
**Catastrophic/Critical Hazards**: [Count]  
**SIL 3-4 Hazards**: [Count]  
**All Hazards Mitigated**: [Yes/No]

### 5.2 Safety Requirements Summary

**Total Safety Requirements**: [Count]  
**From Hazard Analysis**: [Count]  
**All Requirements Verified**: [Yes/No]  
**All Requirements Traced**: [Yes/No]

### 5.3 Residual Risk Summary

| Hazard ID | Initial Risk | Target Risk | Residual Risk | Acceptable? |
|-----------|-------------|-------------|---------------|-------------|
| HAZ-001 | [Risk] | [Risk] | < 10^-X /hr | [Yes/No] |

**ALARP Demonstration**: [Summary of As Low As Reasonably Practicable analysis]

**Conclusion**: All residual risks are **[TOLERABLE / UNACCEPTABLE]**

---

## 6. DESIGN AND IMPLEMENTATION SUMMARY

### 6.1 Architecture Overview

**Architecture Style**: [Modular / Layered / etc.]  
**Safety Principles**:
- [Principle 1]
- [Principle 2]
- [Principle 3]

### 6.2 Safety Mechanisms

| Mechanism | Description | Requirement | Status |
|-----------|-------------|-------------|--------|
| Watchdog | [Description] | [REQ-ID] | [Implemented] |
| Redundancy | [Description] | [REQ-ID] | [Implemented] |
| Fail-Safe | [Description] | [REQ-ID] | [Implemented] |

### 6.3 Coding Standards Compliance

**Standard**: MISRA C:2012 (mandatory SIL 2+)

**Compliance Results**:
- **Mandatory rules**: [X] checked, [Y] violations, [Z] deviations approved
- **Required rules**: [X] checked, [Y] violations
- **Advisory rules**: [X] checked, [Y] violations

**Static Analysis Tools**:
- [Tool 1]: [Results summary]
- [Tool 2]: [Results summary]

**Conclusion**: [COMPLIANT / NON-COMPLIANT]

### 6.4 Complexity Analysis

**Cyclomatic Complexity**:
- **Target**: ≤ 10 (SIL 3-4)
- **Actual**: Max [X], Average [Y]
- **Modules exceeding limit**: [Count] (0 target)

**Conclusion**: [ACCEPTABLE / UNACCEPTABLE]

---

## 7. VERIFICATION AND VALIDATION SUMMARY

### 7.1 Verification Results

**Requirements Verification**:
- **Total requirements**: [Count]
- **Requirements verified**: [Count] ([X]%)
- **Requirements not verified**: [Count]

**Test Coverage** (SIL [X] targets):
- **Statement coverage**: [X]% (target: [Y]%)
- **Branch coverage**: [X]% (target: [Y]%)
- **Condition coverage**: [X]% (target: [Y]%) (SIL 3-4 only)

**Static Analysis**:
- **Tools used**: [List]
- **Critical findings**: [Count]
- **All findings resolved**: [Yes/No]

**Independent Verification**: [Performed / Not Required]

**Conclusion**: Verification **[COMPLETE / INCOMPLETE]**

### 7.2 Validation Results

**System Testing**:
- **Test cases executed**: [Count]
- **Test cases passed**: [Count] ([X]%)
- **Test cases failed**: [Count]

**Operational Scenarios**:
- **Scenarios tested**: [Count]
- **Scenarios passed**: [Count]

**Independent Validation**: [Performed / Not Required]

**Customer Acceptance**: [Accepted / Pending / Rejected]

**Conclusion**: Validation **[COMPLETE / INCOMPLETE]**

---

## 8. PROCESS COMPLIANCE SUMMARY

### 8.1 EN 50128 Lifecycle Compliance

| Lifecycle Phase | EN 50128 Section | Status | Evidence |
|----------------|------------------|--------|----------|
| Software Planning | 6.1 | [Complete] | [SQAP, SCMP, SVP, SVaP] |
| Software Requirements | 7.2 | [Complete] | [SRS] |
| Software Architecture | 7.3 | [Complete] | [SAS] |
| Software Design & Implementation | 7.4 | [Complete] | [SDS, Source Code] |
| Integration | 7.6 | [Complete] | [Integration Test Report] |
| Validation | 7.7 | [Complete] | [SVaR] |

**Compliance Status**: [FULLY COMPLIANT / PARTIALLY COMPLIANT / NON-COMPLIANT]

### 8.2 EN 50128 Technique Compliance

**Mandatory Techniques Applied** (SIL [X]):

| Technique | EN 50128 Table | Requirement | Applied | Evidence |
|-----------|----------------|-------------|---------|----------|
| [Technique] | [Table] | [M/HR/R] | [Yes/No] | [Document] |

**Non-Compliance**: [List any mandatory techniques not applied with justification]

### 8.3 Independence Requirements (SIL 3-4)

**Verifier Independence**: [Yes/No] - [Name, Organization]  
**Validator Independence**: [Yes/No] - [Name, Organization]  
**Assessor Independence**: [Yes/No] - [Name, Organization]

**Conclusion**: Independence requirements **[MET / NOT MET]**

---

## 9. SAFETY CASE EVIDENCE REGISTER

| Evidence ID | Evidence Type | Document | Version | Date | Status |
|-------------|--------------|----------|---------|------|--------|
| E-HAZ | Hazard Log | DOC-HAZLOG-YYYY-NNN | [Ver] | [Date] | [Approved] |
| E-FMEA | FMEA Report | DOC-FMEA-YYYY-NNN | [Ver] | [Date] | [Approved] |
| E-FTA | FTA Report | DOC-FTA-YYYY-NNN | [Ver] | [Date] | [Approved] |
| E-SRS | Requirements | DOC-SRS-YYYY-NNN | [Ver] | [Date] | [Approved] |
| E-SAS | Architecture | DOC-SAS-YYYY-NNN | [Ver] | [Date] | [Approved] |
| E-SDS | Design | DOC-SDS-YYYY-NNN | [Ver] | [Date] | [Approved] |
| E-CODE | Source Code | [Location] | [Ver] | [Date] | [Baseline] |
| E-SVP | Verification Plan | DOC-SVP-YYYY-NNN | [Ver] | [Date] | [Approved] |
| E-SVR | Verification Report | DOC-SVR-YYYY-NNN | [Ver] | [Date] | [Approved] |
| E-SVaP | Validation Plan | DOC-SVAP-YYYY-NNN | [Ver] | [Date] | [Approved] |
| E-SVaR | Validation Report | DOC-SVAR-YYYY-NNN | [Ver] | [Date] | [Approved] |
| E-SQAP | QA Plan | DOC-SQAP-YYYY-NNN | [Ver] | [Date] | [Approved] |
| E-SCMP | CM Plan | DOC-SCMP-YYYY-NNN | [Ver] | [Date] | [Approved] |
| E-ASS | Assessment Report | DOC-ASS-YYYY-NNN | [Ver] | [Date] | [Approved] |

**Evidence Completeness**: [X] of [Y] documents approved ([Z]%)

---

## 10. ASSUMPTIONS AND LIMITATIONS

### 10.1 Assumptions

| Assumption ID | Description | Impact if Violated | Verification Method |
|--------------|-------------|-------------------|---------------------|
| A-01 | [Assumption] | [Impact] | [Verification] |
| A-02 | [Assumption] | [Impact] | [Verification] |

### 10.2 Limitations

| Limitation ID | Description | Mitigation |
|--------------|-------------|------------|
| L-01 | [Limitation] | [Mitigation] |
| L-02 | [Limitation] | [Mitigation] |

### 10.3 Operating Constraints

**Environmental Constraints**:
- [Constraint 1]
- [Constraint 2]

**Operational Constraints**:
- [Constraint 1]
- [Constraint 2]

**Maintenance Requirements**:
- [Requirement 1]
- [Requirement 2]

---

## 11. CONCLUSIONS AND RECOMMENDATIONS

### 11.1 Safety Claim Status

**Primary Claim**: **[System Name] is acceptably safe for railway operation at SIL [X]**

**Status**: **[DEMONSTRATED / NOT DEMONSTRATED]**

### 11.2 Supporting Argument Summary

| Goal | Status | Evidence Complete | Assessment |
|------|--------|-------------------|------------|
| G2: Hazards Mitigated | [Status] | [Yes/No] | [Pass/Fail] |
| G3: Safe Design | [Status] | [Yes/No] | [Pass/Fail] |
| G4: V&V Complete | [Status] | [Yes/No] | [Pass/Fail] |
| G5: Process Compliance | [Status] | [Yes/No] | [Pass/Fail] |

**Overall Assessment**: **[PASS / CONDITIONAL PASS / FAIL]**

### 11.3 Open Issues

| Issue ID | Description | Severity | Resolution Plan | Target Date |
|----------|-------------|----------|-----------------|-------------|
| [ID] | [Description] | [H/M/L] | [Plan] | [Date] |

### 11.4 Recommendations

**For Deployment**:
1. [Recommendation 1]
2. [Recommendation 2]

**For Future Versions**:
1. [Recommendation 1]
2. [Recommendation 2]

### 11.5 Final Recommendation

**Recommendation**: **[APPROVE FOR DEPLOYMENT / CONDITIONAL APPROVAL / REJECT]**

**Conditions** (if conditional approval):
1. [Condition 1]
2. [Condition 2]

**Justification**: [Rationale for recommendation]

---

## APPENDIX A: GSN SAFETY ARGUMENT DIAGRAM

[Include full Goal Structuring Notation diagram]

---

## APPENDIX B: EN 50128 COMPLIANCE MATRIX

| EN 50128 Section | Requirement | Evidence | Compliant |
|------------------|-------------|----------|-----------|
| [Section] | [Requirement] | [Document] | [Yes/No] |

---

## APPENDIX C: GLOSSARY

| Term | Definition |
|------|------------|
| ALARP | As Low As Reasonably Practicable |
| EN 50128 | Railway software standard |
| FMEA | Failure Modes and Effects Analysis |
| FTA | Fault Tree Analysis |
| GSN | Goal Structuring Notation |
| RAMS | Reliability, Availability, Maintainability, Safety |
| SIL | Safety Integrity Level |

---

## APPENDIX D: REVISION HISTORY

| Date | Version | Author | Changes | Approval |
|------|---------|--------|---------|----------|
| YYYY-MM-DD | 0.1 | [Author] | Initial Safety Case | Draft |

---

**END OF SAFETY CASE**
