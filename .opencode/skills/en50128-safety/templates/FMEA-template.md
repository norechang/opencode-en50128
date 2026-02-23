# Failure Modes and Effects Analysis (FMEA)

**Document ID**: DOC-FMEA-YYYY-NNN  
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
| **Document ID** | DOC-FMEA-YYYY-NNN |
| **Version** | 0.1 |
| **Date** | YYYY-MM-DD |
| **Project** | [Project Name] |
| **SIL Level** | [0, 1, 2, 3, or 4] |
| **Author** | Safety Engineer (SAF) |
| **Reviewer** | [Name, Role] |
| **Approver** | [Name], Safety Manager |
| **Status** | Draft |

---

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | YYYY-MM-DD | SAF Engineer | Initial FMEA | - |
| 1.0 | TBD | SAF Engineer | First approved version | TBD |

---

## APPROVALS

**SIL 3-4 Requirements**: Author, Independent Reviewer, Safety Manager, QA Manager

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author (Safety Engineer)** | [Name] | | YYYY-MM-DD |
| **Independent Reviewer** | TBD | | |
| **Safety Manager** | TBD | | |
| **QA Manager** | TBD | | |

---

## 1. INTRODUCTION

### 1.1 Purpose

This document presents the Failure Modes and Effects Analysis (FMEA) for **[Project Name]** in accordance with EN 50128:2011 Table A.8.

**FMEA Objective**:
- Identify all potential failure modes of system components
- Analyze the effects of each failure mode on system safety
- Assess the severity of each failure mode
- Identify detection methods for each failure mode
- Define mitigations to reduce risk
- Calculate residual risk after mitigation

**EN 50128 Requirement**: FMEA is **Highly Recommended** for SIL 3-4 (Table A.8).

### 1.2 Scope

This FMEA covers:
- Software modules and functions
- Hardware-software interfaces
- Sensors and actuators
- Communication interfaces
- Critical data structures and variables

**FMEA Type**: [Hardware FMEA / Software FMEA / System FMEA]

### 1.3 FMEA Methodology

**Standard Reference**: 
- IEC 60812:2018 - Failure modes and effects analysis (FMEA and FMECA)
- EN 50128:2011 Annex D.25 - FMEA technique

**FMEA Process**:
1. Identify system components and functions
2. Identify potential failure modes for each component
3. Analyze effects of each failure mode
4. Assess severity (1-10 scale)
5. Identify causes of failure
6. Identify detection methods
7. Define mitigations
8. Calculate Risk Priority Number (RPN) = Severity × Occurrence × Detection
9. Track mitigation implementation

### 1.4 References

| Reference | Document |
|-----------|----------|
| **[HAZ]** | Hazard Log, DOC-HAZLOG-YYYY-NNN |
| **[SRS]** | Software Requirements Specification, DOC-SRS-YYYY-NNN |
| **[SAS]** | Software Architecture Specification, DOC-SAS-YYYY-NNN |
| **[SDS]** | Software Design Specification, DOC-SDS-YYYY-NNN |
| **[EN50128]** | EN 50128:2011 Railway applications - Software standard |

---

## 2. FMEA SEVERITY SCALE

| Severity | Rating | Description | Examples |
|----------|--------|-------------|----------|
| **Catastrophic** | 10 | Death or multiple serious injuries | Passenger falls from moving train |
| **Critical** | 9 | Single serious injury | Passenger crushed by door |
| **Serious** | 8 | Multiple minor injuries or single hospitalization | Broken bones, head injury |
| **Major** | 7 | Single minor injury | Bruising, cuts requiring first aid |
| **Moderate** | 6 | System degradation, loss of primary function | System enters safe state, service disruption |
| **Minor** | 5 | Partial loss of function | Degraded mode operation |
| **Very Minor** | 4 | Nuisance, inconvenience | False alarm, minor delay |
| **Negligible** | 3 | Unnoticeable effect | No operational impact |
| **No Effect** | 2 | No safety or operational effect | Detected and ignored |
| **None** | 1 | No effect | - |

---

## 3. FMEA OCCURRENCE SCALE

| Occurrence | Rating | Description | Probability (per hour) |
|------------|--------|-------------|----------------------|
| **Very High** | 10 | Failure almost certain | > 10^-3 |
| **High** | 9 | Frequent failure | 10^-3 to 10^-4 |
| **Moderate** | 8 | Occasional failure | 10^-4 to 10^-5 |
| **Low** | 7 | Unlikely failure | 10^-5 to 10^-6 |
| **Remote** | 6 | Remote failure | 10^-6 to 10^-7 |
| **Very Low** | 5 | Very unlikely | 10^-7 to 10^-8 |
| **Extremely Low** | 4 | Extremely unlikely | 10^-8 to 10^-9 |
| **Nearly Impossible** | 3 | Nearly impossible | 10^-9 to 10^-10 |
| **Impossible** | 2 | Prevented by design | < 10^-10 |
| **No Failure** | 1 | No failure possible | 0 |

---

## 4. FMEA DETECTION SCALE

| Detection | Rating | Description | Detection Method |
|-----------|--------|-------------|------------------|
| **None** | 10 | No detection method | Failure not detectable |
| **Very Low** | 9 | Very unlikely to detect | Visual inspection (infrequent) |
| **Low** | 8 | Unlikely to detect | Manual inspection (periodic) |
| **Moderate** | 7 | Moderate chance of detection | Diagnostic routine (periodic) |
| **Moderately High** | 6 | Good chance of detection | Automatic diagnostic (periodic) |
| **High** | 5 | High chance of detection | Online monitoring (continuous) |
| **Very High** | 4 | Very high chance of detection | Redundant sensors, cross-check |
| **Automatic** | 3 | Automatic detection | Watchdog, built-in self-test |
| **Fail-Safe** | 2 | Fail-safe design | Failure prevented by design |
| **Impossible** | 1 | Failure prevented | Design prevents failure mode |

---

## 5. FMEA ANALYSIS

### 5.1 FMEA: [Subsystem/Module Name]

**Module**: [Module Name]  
**Function**: [Primary function]  
**SIL**: [0, 1, 2, 3, or 4]  
**Reference Requirements**: [REQ-IDs]

| Component | Function | Failure Mode | Effect (Local) | Effect (System) | Severity (S) | Cause | Occurrence (O) | Current Controls | Detection (D) | RPN (S×O×D) | Mitigation | Residual Risk |
|-----------|----------|--------------|---------------|-----------------|--------------|-------|----------------|------------------|---------------|-------------|------------|---------------|
| [Component] | [Function] | [Failure mode] | [Local effect] | [System effect] | [1-10] | [Cause] | [1-10] | [Controls] | [1-10] | [S×O×D] | [Mitigation] | [Risk] |

**FMEA Summary** - [Subsystem Name]:
- **Total failure modes analyzed**: [Count]
- **Critical failure modes (RPN > 100)**: [Count]
- **High severity (S ≥ 8)**: [Count]
- **Mitigations defined**: [Count]
- **Residual risk assessment**: [TOLERABLE / UNACCEPTABLE]

---

### 5.2 FMEA: [Next Subsystem/Module]

[Repeat FMEA table structure]

---

[Repeat for all subsystems]

---

## 6. HIGH-RISK FAILURE MODES (RPN > 100)

### 6.1 Failure Mode: [Description]

**Component**: [Component name]  
**RPN**: [Value]  
**Severity**: [Value] - [Description]  
**Occurrence**: [Value] - [Probability]  
**Detection**: [Value] - [Detection method]

**Effect**: [Detailed effect description]

**Cause**: [Detailed cause analysis]

**Current Controls**: [Existing controls]

**Recommended Actions**:
1. [Action 1] - [Responsible party] - [Target date]
2. [Action 2] - [Responsible party] - [Target date]
3. [Action 3] - [Responsible party] - [Target date]

**Target RPN** (after mitigation): [Value]

---

[Repeat for each high-risk failure mode]

---

## 7. MITIGATION ACTION PLAN

| Failure Mode | Current RPN | Mitigation Action | Responsible | Target Date | Status | Expected RPN |
|--------------|-------------|-------------------|-------------|-------------|--------|--------------|
| [Failure mode] | [RPN] | [Action] | [Person] | [Date] | [Status] | [RPN] |

---

## 8. FMEA RESULTS SUMMARY

### 8.1 RPN Distribution

| RPN Range | Count | Percentage | Action Required |
|-----------|-------|------------|-----------------|
| **Critical (200-1000)** | [N] | [X]% | Immediate action required |
| **High (100-199)** | [N] | [X]% | Mitigation plan required |
| **Moderate (50-99)** | [N] | [X]% | Monitor and review |
| **Low (< 50)** | [N] | [X]% | Acceptable risk |

### 8.2 Severity Distribution

| Severity Level | Count | Percentage |
|----------------|-------|------------|
| **Catastrophic (10)** | [N] | [X]% |
| **Critical (9)** | [N] | [X]% |
| **Serious (8)** | [N] | [X]% |
| **Major (7)** | [N] | [X]% |
| **Moderate (6)** | [N] | [X]% |
| **Low (1-5)** | [N] | [X]% |

### 8.3 Key Findings

**Critical Findings**:
1. [Finding 1]
2. [Finding 2]
3. [Finding 3]

**Recommendations**:
1. [Recommendation 1]
2. [Recommendation 2]
3. [Recommendation 3]

### 8.4 FMEA Completeness

- [ ] All system components analyzed
- [ ] All failure modes identified
- [ ] All effects documented (local and system level)
- [ ] All severity ratings assigned
- [ ] All causes identified
- [ ] All detection methods documented
- [ ] All mitigations defined
- [ ] High-risk items (RPN > 100) have action plans
- [ ] FMEA reviewed by independent reviewer (SIL 3-4)
- [ ] FMEA approved by Safety Manager

---

## 9. TRACEABILITY

### 9.1 FMEA to Hazard Log Traceability

| FMEA Failure Mode | Related Hazard ID | Safety Requirements |
|-------------------|------------------|---------------------|
| [Failure mode] | [HAZ-ID] | [REQ-IDs] |

### 9.2 FMEA to Safety Requirements Traceability

| Safety Requirement | FMEA Failure Modes Mitigated | Effectiveness |
|--------------------|------------------------------|---------------|
| [REQ-ID] | [Failure modes] | [Assessment] |

---

## 10. FMEA MAINTENANCE

### 10.1 Update Triggers

This FMEA SHALL be updated when:
1. System design changes (new components, modified functions)
2. New failure modes identified during testing or operation
3. Severity, occurrence, or detection ratings change
4. Mitigations implemented (residual risk assessment)
5. Field failures or incidents occur

### 10.2 Review Schedule

**FMEA Review Frequency**:
- **During Development**: After each design phase (Phase 3, 4, 5)
- **After Deployment**: Annually or after significant system changes
- **After Incidents**: Within 30 days of safety incident

---

## APPENDIX A: FMEA CALCULATION EXAMPLES

### A.1 RPN Calculation Example

**Example**: Speed sensor failure

- **Severity (S)**: 10 (Catastrophic - doors open while moving)
- **Occurrence (O)**: 8 (Occasional - 10^-4 per hour)
- **Detection (D)**: 4 (Very High - redundant sensor cross-check)
- **RPN**: S × O × D = 10 × 8 × 4 = 320 (Critical - requires immediate action)

**After Mitigation** (fail-safe logic added):
- **Severity (S)**: 10 (unchanged - catastrophic if occurs)
- **Occurrence (O)**: 5 (Very Low - 10^-7 per hour)
- **Detection (D)**: 2 (Fail-Safe - design prevents unsafe state)
- **RPN**: 10 × 5 × 2 = 100 (High - acceptable with monitoring)

---

## APPENDIX B: FMEA WORKSHEETS

### B.1 Blank FMEA Worksheet

[Provide blank table for additional analysis]

---

## APPENDIX C: REVISION HISTORY

| Date | Version | Author | Changes | Approval |
|------|---------|--------|---------|----------|
| YYYY-MM-DD | 0.1 | [Author] | Initial FMEA | Draft |

---

**END OF FMEA REPORT**
