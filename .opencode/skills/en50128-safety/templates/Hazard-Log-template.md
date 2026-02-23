# Hazard Log

**Document ID**: DOC-HAZLOG-YYYY-NNN  
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
| **Document ID** | DOC-HAZLOG-YYYY-NNN |
| **Version** | 0.1 |
| **Date** | YYYY-MM-DD |
| **Project** | [Project Name] |
| **SIL Level** | [0, 1, 2, 3, or 4] |
| **Author** | Safety Engineer (SAF) |
| **Reviewer** | [Name, Role] |
| **Approver** | [Name], Project Manager |
| **Status** | Draft |

---

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | YYYY-MM-DD | SAF Engineer | Initial hazard log | - |
| 1.0 | TBD | SAF Engineer | First approved version | TBD |

---

## APPROVALS

**SIL Requirements**:
- **SIL 0-1**: Author, Reviewer
- **SIL 2**: Author, Independent Reviewer, Safety Manager
- **SIL 3-4**: Author, Independent Reviewer, Safety Manager, Project Manager, Customer

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author (Safety Engineer)** | [Name] | | YYYY-MM-DD |
| **Independent Reviewer** | TBD | | |
| **Safety Manager** | TBD | | |
| **QA Manager** | TBD | | |
| **Project Manager** | TBD | | |
| **Customer Representative** | TBD | | |

---

## 1. INTRODUCTION

### 1.1 Purpose

This Hazard Log documents all identified hazards, risks, and safety measures for **[Project Name]** in accordance with EN 50128:2011 Section 7.1 and EN 50126:2017.

The Hazard Log provides:
- Complete hazard identification and analysis
- Risk assessment and SIL determination
- Safety requirements traceability
- FMEA (Failure Modes and Effects Analysis) for critical functions
- FTA (Fault Tree Analysis) for catastrophic hazards
- Verification methods and residual risk assessment

**Intended Audience**:
- Safety engineers
- System and software designers
- Verification and validation teams
- Project management
- Customer and certification authorities

### 1.2 Scope

This Hazard Log covers:
- Software-related hazards in the [system name]
- Hardware-software interface failures
- Common cause failures
- Systematic failures in software
- Random hardware failures affecting software behavior

**Out of Scope** (covered by System Hazard Analysis):
- Pure mechanical failures
- Electrical power supply failures (unless affecting software)
- Human factors - addressed at system level

### 1.3 Safety Analysis Methods Applied

Per EN 50128 Table A.1 and A.8, the following safety analysis techniques have been applied:

| Technique | SIL 0-1 | SIL 2 | SIL 3-4 | Applied | Evidence |
|-----------|---------|-------|---------|---------|----------|
| **Hazard Identification** | R | HR | HR | ✓ | Section 3 |
| **Risk Assessment** | R | HR | HR | ✓ | Section 3 |
| **FMEA** | - | R | HR | ✓ | Section 5 |
| **FTA** | - | R | HR | ✓ | Section 6 |
| **Common Cause Failure Analysis** | - | R | **M** | ✓ | Section 4 |
| **Software Error Effect Analysis** | - | R | HR | ✓ | Section 5 |

**Key**: M = Mandatory, HR = Highly Recommended, R = Recommended

### 1.4 References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems |
| **[EN50126-1]** | EN 50126-1:2017 Railway applications - RAMS - Part 1: Generic RAMS process |
| **[EN50126-2]** | EN 50126-2:2017 Railway applications - RAMS - Part 2: Systems approach to safety |
| **[EN50129]** | EN 50129:2018 Railway applications - Safety related electronic systems for signalling |
| **[SRS]** | Software Requirements Specification, DOC-SRS-YYYY-NNN |
| **[SAS]** | Software Architecture Specification, DOC-SAS-YYYY-NNN |
| **[RTM]** | Requirements Traceability Matrix, DOC-RTM-YYYY-NNN |

---

## 2. HAZARD ANALYSIS SUMMARY

### 2.1 Hazard Count by Severity

| Severity Level | Count | Catastrophic | Critical | Marginal | Negligible |
|----------------|-------|--------------|----------|----------|------------|
| **Total Hazards** | [N] | [N] | [N] | [N] | [N] |

### 2.2 Hazard Status Summary

| Status | Count | Description |
|--------|-------|-------------|
| **Open** | [N] | Hazard identified, no mitigation yet |
| **Mitigated** | [N] | Safety requirements defined, implementation pending |
| **Closed** | [N] | Mitigation implemented and verified |

### 2.3 SIL Distribution

| SIL Level | Hazard Count | Percentage |
|-----------|--------------|------------|
| **SIL 4** | [N] | [X]% |
| **SIL 3** | [N] | [X]% |
| **SIL 2** | [N] | [X]% |
| **SIL 1** | [N] | [X]% |
| **SIL 0** | [N] | [X]% |

---

## 3. HAZARD REGISTER

### HAZ-001: [Hazard Title]

**Hazard Category**: [Category]  
**System**: [System Name]  
**Status**: [Open / Mitigated / Closed]  
**SIL Level**: [0, 1, 2, 3, or 4]

#### 3.1.1 Hazard Description

[Detailed description of the hazard condition]

#### 3.1.2 Consequences

- **Severity**: [Catastrophic / Critical / Marginal / Negligible]
- **Impact**:
  - [Impact 1]
  - [Impact 2]
  - [Impact 3]

#### 3.1.3 Causes (Root Cause Analysis)

1. **[Cause Category 1]**:
   - [Specific cause 1]
   - [Specific cause 2]

2. **[Cause Category 2]**:
   - [Specific cause 1]
   - [Specific cause 2]

#### 3.1.4 Risk Assessment

**Frequency Assessment**:
- [Failure mode]: [Frequency] ([probability per hour])

**Severity**: [Catastrophic / Critical / Marginal / Negligible]

**Risk Matrix**:

| Frequency ↓ / Severity → | Negligible | Marginal | Critical | Catastrophic |
|--------------------------|------------|----------|----------|--------------|
| Frequent                 | Tolerable  | Undesirable | Unacceptable | Unacceptable |
| Probable                 | Tolerable  | Undesirable | Unacceptable | Unacceptable |
| Occasional               | Tolerable  | Undesirable | Unacceptable | Unacceptable |
| Remote                   | Acceptable | Tolerable | Undesirable | Undesirable |
| Improbable               | Acceptable | Tolerable | Tolerable | Tolerable |

**Initial Risk Level**: [Unacceptable / Undesirable / Tolerable / Acceptable]

**Target Risk Level**: [Tolerable / Acceptable]

**Assigned SIL**: [0, 1, 2, 3, or 4]

#### 3.1.5 Safety Requirements (Mitigations)

| SW Req ID | Description | Mitigation Effectiveness |
|-----------|-------------|-------------------------|
| **[REQ-ID]** | [Requirement description] | [Mitigation type] |

**Combined Mitigation Strategy**:
1. [Strategy 1]
2. [Strategy 2]
3. [Strategy 3]

**Expected Risk Reduction**: [Factor]

#### 3.1.6 Verification Methods

- **Test**: [Test description]
- **FMEA**: Section [X]
- **FTA**: Section [X]
- **Fault Injection**: [Description]
- **Coverage Analysis**: [Coverage target]

#### 3.1.7 Residual Risk

After mitigation, residual risk:
- **Failure Rate**: [Target rate]
- **Severity**: [Level]
- **Risk Level**: [Tolerable / Acceptable]

**Assumptions**:
- [Assumption 1]
- [Assumption 2]

**Acceptance**: Residual risk is **[TOLERABLE / ACCEPTABLE]** per EN 50126 risk acceptance criteria (ALARP principle).

---

[Repeat HAZ-002, HAZ-003, etc. for each hazard]

---

## 4. COMMON CAUSE FAILURE ANALYSIS

**EN 50128 Requirement**: Common Cause Failure (CCF) analysis is **MANDATORY** for SIL 3-4 (Table A.1, A.8).

### 4.1 Common Cause Failure Scenarios

#### CCF-001: [Common Cause Failure Description]

**Scenario**: [Detailed scenario description]

**Hazard**: [Related hazard ID]

**Likelihood**: [Frequency]

**Mitigation**:
- **Hardware Design**: [Hardware mitigation]
- **Software**: [Software mitigation]

**Status**: [Mitigated / Partially Mitigated]

---

[Repeat for CCF-002, CCF-003, etc.]

---

### 4.2 Common Cause Failure Summary

| CCF ID | Scenario | Affected Hazard | Likelihood | Mitigation | Status |
|--------|----------|----------------|------------|------------|--------|
| CCF-001 | [Scenario] | [HAZ-ID] | [Frequency] | [Mitigation] | [Status] |

**Conclusion**: [Overall CCF analysis conclusion]

---

## 5. FAILURE MODES AND EFFECTS ANALYSIS (FMEA)

### 5.1 FMEA: [Subsystem Name]

**Module**: [Module Name]  
**SIL**: [0, 1, 2, 3, or 4]  
**Reference**: [Related requirements]

| Failure Mode | Effect | Severity | Cause | Detection | Mitigation | Residual Risk |
|--------------|--------|----------|-------|-----------|------------|---------------|
| [Failure mode] | [Effect] | [1-10] | [Cause] | [Detection method] | [Mitigation] | [Risk level] |

**FMEA Summary**:
- **Critical failure modes**: [Count]
- **Mitigations**: [Summary]
- **Residual Risk**: [Overall assessment]

---

[Repeat for additional FMEA sections]

---

## 6. FAULT TREE ANALYSIS (FTA)

### 6.1 Fault Tree: "[Top Event Description]"

**Top Event**: [Description of top event]

```
                     ┌───────────────────────────────────────┐
                     │         [Top Event]                   │
                     │         (SEVERITY)                    │
                     └─────────────────┬─────────────────────┘
                                       │
                             ┌─────────┴─────────┐
                             │     [GATE]        │
                             └─────────┬─────────┘
                     ┌─────────────────┼─────────────────┐
                     ▼                 ▼                 ▼
           [Event 1]          [Event 2]          [Event 3]
```

**Fault Tree Analysis**:

**Top Event Probability** (without mitigation): [Calculation]

**Mitigation Effect**: [Description of mitigations]

**Top Event Probability** (with mitigation): [Calculation]

**Critical Cut Sets**: [Minimal combinations leading to top event]

**Conclusion**: [FTA conclusion and SIL achievement]

---

[Repeat for additional FTA sections]

---

## 7. SAFETY REQUIREMENTS SUMMARY

### 7.1 Hazard to Safety Requirement Mapping

| Hazard ID | Description | SIL | Safety Requirements | Status |
|-----------|-------------|-----|---------------------|--------|
| **HAZ-001** | [Description] | [SIL] | [Requirements] | [Status] |

**Total Safety Requirements**: [Count]

---

## 8. VERIFICATION AND VALIDATION PLAN

### 8.1 Hazard Verification Methods

Each hazard SHALL be verified using the following methods:

| Hazard ID | Verification Method | Test Cases | FMEA | FTA | Fault Injection | Status |
|-----------|---------------------|------------|------|-----|----------------|--------|
| HAZ-001 | [Methods] | [Test IDs] | [Section] | [Section] | [Description] | [Status] |

**Verification Responsibility**:
- **Test**: Tester (TST) and Verifier (VER)
- **FMEA/FTA**: Safety Engineer (SAF) and Verifier (VER)
- **Fault Injection**: Tester (TST) with safety test rig
- **Static Analysis**: Verifier (VER)

---

## 9. RESIDUAL RISK ASSESSMENT

### 9.1 Residual Risk Summary

After application of all safety requirements and mitigations:

| Hazard ID | Initial Risk | Target Risk | Residual Risk | Acceptable? |
|-----------|-------------|-------------|---------------|-------------|
| HAZ-001 | [Risk] | [Risk] | [Risk] | [Yes/No] |

**Conclusion**: [Overall residual risk assessment]

### 9.2 Risk Acceptance

**Risk Acceptance Authority**: Customer / Railway Safety Authority

**Acceptance Criteria**: 
1. [Criterion 1]
2. [Criterion 2]
3. [Criterion 3]

**Status**: [Pending / Accepted / Rejected]

---

## 10. SAFETY CASE SUMMARY

### 10.1 Safety Argument

[System name] is safe for SIL [X] operation based on the following argument:

1. **Hazards Identified**: [Summary]

2. **Risks Assessed**: [Summary]

3. **SIL Determined**: [Summary]

4. **Safety Requirements Defined**: [Summary]

5. **Multiple Mitigations Applied**: [Summary]

6. **Verification Performed**: [Summary]

7. **Independent Assessment**: [Summary]

8. **Residual Risk Acceptable**: [Summary]

### 10.2 Safety Case Evidence

| Evidence Type | Document | Status |
|---------------|----------|--------|
| **Hazard Log** | This document | [Status] |
| **FMEA Reports** | Section 5 | [Status] |
| **FTA Reports** | Section 6 | [Status] |
| **Safety Requirements** | SRS DOC-SRS-YYYY-NNN | [Status] |
| **Verification Reports** | DOC-SVR-YYYY-NNN | [Status] |
| **Test Reports** | DOC-STR-YYYY-NNN | [Status] |

### 10.3 Safety Case Conclusion

**Claim**: [System name] achieves SIL [X] and is safe for deployment in railway operations.

**Evidence**: [Summary of evidence]

**Recommendation**: [Recommendation for acceptance]

---

## APPENDIX A: RISK MATRIX DEFINITIONS

### A.1 Severity Definitions

| Severity | Description | Examples |
|----------|-------------|----------|
| **Catastrophic** | Death or multiple serious injuries | Passenger falls from moving train, train collision |
| **Critical** | Single serious injury or multiple minor injuries | Passenger crushed by door, broken bones |
| **Marginal** | Minor injury, first aid required | Bruising, cuts, passenger alarm |
| **Negligible** | No injury, minor inconvenience | Service delay, passenger confusion |

### A.2 Frequency Definitions

| Frequency | Description | Probability Range (per hour) |
|-----------|-------------|------------------------------|
| **Frequent** | Expected to occur often | > 10^-3 |
| **Probable** | Will occur several times | 10^-4 to 10^-3 |
| **Occasional** | Likely to occur sometime | 10^-5 to 10^-4 |
| **Remote** | Unlikely but possible | 10^-6 to 10^-5 |
| **Improbable** | Very unlikely to occur | < 10^-6 |

### A.3 Risk Levels

| Risk Level | Description | Action Required |
|------------|-------------|-----------------|
| **Unacceptable** | Risk must be eliminated | Redesign required, operation prohibited |
| **Undesirable** | Risk must be reduced | Additional mitigations required |
| **Tolerable** | Risk accepted with mitigations | ALARP demonstration required |
| **Acceptable** | Risk broadly acceptable | No additional mitigations required |

---

## APPENDIX B: SAFETY ANALYSIS TECHNIQUES REFERENCE

### B.1 EN 50128 Table A.8 - Software Analysis Techniques

| Technique | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 | Reference |
|-----------|-------|-------|-------|-------|-------|-----------|
| **Common Cause Failure Analysis** | - | - | R | **M** | **M** | EN 50128 D.11 |
| **FMEA** | - | - | R | HR | HR | EN 50128 D.25 |
| **FTA** | - | - | R | HR | HR | EN 50128 D.31 |
| **Hazard and Risk Analysis** | R | R | HR | HR | HR | EN 50126 |

**Key**: M = Mandatory, HR = Highly Recommended, R = Recommended, - = No recommendation

---

## APPENDIX C: REVISION HISTORY

| Date | Version | Author | Changes | Approval |
|------|---------|--------|---------|----------|
| YYYY-MM-DD | 0.1 | [Author] | Initial template | Draft |

---

**END OF HAZARD LOG**
