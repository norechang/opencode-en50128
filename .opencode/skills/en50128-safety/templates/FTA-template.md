# Fault Tree Analysis (FTA)

**Document ID**: DOC-FTA-YYYY-NNN  
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
| **Document ID** | DOC-FTA-YYYY-NNN |
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
| 0.1 | YYYY-MM-DD | SAF Engineer | Initial FTA | - |
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

This document presents the Fault Tree Analysis (FTA) for **[Project Name]** in accordance with EN 50128:2011 Table A.8.

**FTA Objective**:
- Identify all combinations of failures leading to hazardous events (top events)
- Calculate probability of top events
- Identify critical failure combinations (minimal cut sets)
- Verify that safety requirements reduce top event probability to acceptable levels
- Support SIL achievement demonstration

**EN 50128 Requirement**: FTA is **Highly Recommended** for SIL 3-4 (Table A.8).

### 1.2 Scope

This FTA analyzes the following top events:
1. [Top Event 1] - Related to [HAZ-ID]
2. [Top Event 2] - Related to [HAZ-ID]
3. [Top Event 3] - Related to [HAZ-ID]

**Analysis Type**: [Qualitative / Quantitative / Both]

### 1.3 FTA Methodology

**Standard Reference**:
- IEC 61025:2006 - Fault tree analysis (FTA)
- EN 50128:2011 Annex D.31 - Fault Tree Analysis technique
- NASA Fault Tree Handbook (NUREG-0492)

**FTA Process**:
1. Define top event (undesired system state)
2. Identify immediate causes of top event
3. Break down causes using logic gates (AND, OR)
4. Continue decomposition to basic events (primary failures)
5. Assign probabilities to basic events
6. Calculate top event probability
7. Identify minimal cut sets
8. Analyze critical paths to top event
9. Verify mitigations reduce top event probability

### 1.4 FTA Symbols and Gates

**Logic Gates**:
- **AND Gate**: Output occurs if ALL inputs occur
- **OR Gate**: Output occurs if ANY input occurs
- **VOTING Gate (k/n)**: Output occurs if k out of n inputs occur
- **INHIBIT Gate**: Output occurs if input occurs AND condition is true

**Events**:
- **Basic Event**: Primary failure (cannot be decomposed further)
- **Undeveloped Event**: Event not developed (lack of information or outside scope)
- **Intermediate Event**: Event resulting from combination of other events
- **Conditional Event**: Condition required for INHIBIT gate

### 1.5 References

| Reference | Document |
|-----------|----------|
| **[HAZ]** | Hazard Log, DOC-HAZLOG-YYYY-NNN |
| **[FMEA]** | FMEA Report, DOC-FMEA-YYYY-NNN |
| **[SRS]** | Software Requirements Specification, DOC-SRS-YYYY-NNN |
| **[SAS]** | Software Architecture Specification, DOC-SAS-YYYY-NNN |
| **[EN50128]** | EN 50128:2011 Railway applications - Software standard |

---

## 2. FAULT TREE ANALYSIS

### 2.1 Fault Tree: [Top Event 1 Description]

**Top Event ID**: FTA-001  
**Top Event Description**: [Detailed description of undesired event]  
**Related Hazard**: [HAZ-ID] from Hazard Log  
**Severity**: [Catastrophic / Critical / Marginal]  
**Target Failure Rate**: [< 10^-X per hour for SIL Y]

#### 2.1.1 Fault Tree Diagram

```
                     ┌───────────────────────────────────────┐
                     │       [Top Event Description]         │
                     │           (SEVERITY LEVEL)            │
                     │         Target: < 10^-X /hr           │
                     └─────────────────┬─────────────────────┘
                                       │
                             ┌─────────┴─────────┐
                             │      [GATE]       │
                             │    (AND / OR)     │
                             └─────────┬─────────┘
                     ┌─────────────────┼─────────────────┐
                     ▼                 ▼                 ▼
           ┌──────────────────┐  ┌──────────────┐  ┌──────────────┐
           │  [Intermediate   │  │ [Intermediate│  │ [Intermediate│
           │    Event 1]      │  │   Event 2]   │  │   Event 3]   │
           └─────────┬────────┘  └──────┬───────┘  └──────┬───────┘
                     │                  │                  │
           ┌─────────┴─────────┐        │        ┌─────────┴─────────┐
           │      [GATE]       │        │        │      [GATE]       │
           └─────────┬─────────┘        │        └─────────┬─────────┘
       ┌─────────────┼─────────────┐    │    ┌─────────────┼─────────────┐
       ▼             ▼             ▼    ▼    ▼             ▼             ▼
┌─────────────┐ ┌─────────────┐ ┌─────────────┐ ┌─────────────┐ ┌─────────────┐
│[Basic Event]│ │[Basic Event]│ │[Basic Event]│ │[Basic Event]│ │[Basic Event]│
│   BE-01     │ │   BE-02     │ │   BE-03     │ │   BE-04     │ │   BE-05     │
│  λ=10^-X    │ │  λ=10^-Y    │ │  λ=10^-Z    │ │  λ=10^-A    │ │  λ=10^-B    │
└─────────────┘ └─────────────┘ └─────────────┘ └─────────────┘ └─────────────┘
```

**Diagram Legend**:
- λ = Failure rate (per hour)
- BE = Basic Event
- IE = Intermediate Event

#### 2.1.2 Event Descriptions

**Intermediate Events**:

| Event ID | Description | Logic Gate | Input Events |
|----------|-------------|------------|--------------|
| IE-01 | [Description] | [AND/OR] | [BE-01, BE-02, ...] |
| IE-02 | [Description] | [AND/OR] | [BE-03, BE-04, ...] |

**Basic Events**:

| Event ID | Description | Failure Rate (λ) | Source | Notes |
|----------|-------------|------------------|--------|-------|
| BE-01 | [Primary failure description] | [10^-X /hr] | [Reference] | [Notes] |
| BE-02 | [Primary failure description] | [10^-Y /hr] | [Reference] | [Notes] |
| BE-03 | [Primary failure description] | [10^-Z /hr] | [Reference] | [Notes] |

**Failure Rate Sources**:
- Hardware reliability database (e.g., MIL-HDBK-217F, IEC 61709)
- Manufacturer datasheets
- Historical field data
- Expert judgment (justified)

#### 2.1.3 Quantitative Analysis

**Top Event Probability Calculation** (Boolean algebra):

**Without Mitigations**:
```
P(Top Event) = [Boolean expression]
             = [Calculation steps]
             = [Result] per hour
```

**Example** (AND gate with 2 inputs):
```
P(Top) = P(A AND B) = P(A) × P(B)
       = 10^-4 × 10^-4
       = 10^-8 per hour
```

**Example** (OR gate with 2 inputs):
```
P(Top) = P(A OR B) = P(A) + P(B) - P(A) × P(B)
       ≈ P(A) + P(B)  (if P(A) and P(B) are small)
       = 10^-4 + 10^-5
       = 1.1 × 10^-4 per hour
```

**With Mitigations**:
```
[List mitigations applied]
- [Mitigation 1]: Reduces [event] by factor of [X]
- [Mitigation 2]: Adds redundancy, changes [gate] to [gate]

P(Top Event) = [New Boolean expression]
             = [Calculation]
             = [Result] per hour
```

**SIL Achievement**:
- **Target**: < 10^-X per hour for SIL [Y]
- **Calculated**: [Result] per hour
- **Margin**: [Factor]
- **Conclusion**: [MEETS / DOES NOT MEET] SIL [Y] target

#### 2.1.4 Minimal Cut Sets

**Definition**: Minimal Cut Sets are the smallest combinations of basic events that, if they all occur, cause the top event.

| Cut Set ID | Basic Events | Probability | Rank | Contribution |
|------------|--------------|-------------|------|--------------|
| CS-01 | BE-01, BE-02 | [Probability] | 1 | [%] |
| CS-02 | BE-03 | [Probability] | 2 | [%] |
| CS-03 | BE-04, BE-05, BE-06 | [Probability] | 3 | [%] |

**Critical Cut Sets** (highest probability):
1. [Cut Set ID]: [Description] - Probability: [Value]
2. [Cut Set ID]: [Description] - Probability: [Value]

**Cut Set Analysis**:
- **Single-point failures**: [Count] (cut sets with 1 event)
- **Two-point failures**: [Count] (cut sets with 2 events)
- **Three-point failures**: [Count] (cut sets with 3+ events)

**Safety Implications**:
- [Analysis of critical cut sets]
- [Recommendations for additional mitigations]

#### 2.1.5 Sensitivity Analysis

**Objective**: Identify which basic events have the greatest impact on top event probability.

| Basic Event | Baseline λ | λ × 2 (worse) | Top Event Impact | λ ÷ 2 (better) | Top Event Impact |
|-------------|-----------|---------------|------------------|----------------|------------------|
| BE-01 | [Value] | [Value] | [+X%] | [Value] | [-Y%] |
| BE-02 | [Value] | [Value] | [+X%] | [Value] | [-Y%] |

**Key Findings**:
- [Event ID] has highest impact (±[X]%)
- [Event ID] has minimal impact (±[Y]%)

**Recommendations**:
- Focus mitigation efforts on [high-impact events]
- [Specific recommendations]

#### 2.1.6 Common Cause Failures

**Common Cause Failures (CCF)** affecting multiple basic events:

| CCF ID | Description | Affected Events | Impact | Mitigation |
|--------|-------------|----------------|--------|------------|
| CCF-01 | [CCF description] | [BE-01, BE-02] | [Impact on fault tree] | [Mitigation] |

**Beta Factor Model** (if applicable):
- β = [Value] (fraction of failures that are common cause)
- Adjusted failure rates: λ_independent = (1-β) × λ, λ_CCF = β × λ

#### 2.1.7 Assumptions and Limitations

**Assumptions**:
1. [Assumption 1]
2. [Assumption 2]
3. [Assumption 3]

**Limitations**:
1. [Limitation 1]
2. [Limitation 2]

**Validation**:
- [How assumptions will be validated]
- [Testing or analysis required]

---

### 2.2 Fault Tree: [Top Event 2 Description]

[Repeat FTA structure for next top event]

---

[Repeat for all top events]

---

## 3. FTA RESULTS SUMMARY

### 3.1 Top Event Summary

| FTA ID | Top Event | Related Hazard | Target λ | Calculated λ (no mitigation) | Calculated λ (with mitigation) | SIL Target Met? |
|--------|-----------|----------------|----------|------------------------------|--------------------------------|-----------------|
| FTA-001 | [Event] | [HAZ-ID] | < 10^-X | [Value] | [Value] | [Yes/No] |
| FTA-002 | [Event] | [HAZ-ID] | < 10^-Y | [Value] | [Value] | [Yes/No] |

### 3.2 Critical Findings

**High-Risk Paths**:
1. [Finding 1]
2. [Finding 2]
3. [Finding 3]

**Single-Point Failures**:
1. [Event] - [Description] - Mitigated by [Requirement]

**Common Cause Failures**:
1. [CCF] - [Description] - Mitigated by [Strategy]

### 3.3 Mitigation Effectiveness

**Mitigations Applied**:

| Mitigation | Affected FTA | Risk Reduction Factor | Safety Requirement |
|------------|--------------|----------------------|-------------------|
| [Mitigation] | [FTA-ID] | [Factor] | [REQ-ID] |

**Overall Risk Reduction**: [Factor] (from [initial] to [final])

### 3.4 Recommendations

1. [Recommendation 1]
2. [Recommendation 2]
3. [Recommendation 3]

---

## 4. TRACEABILITY

### 4.1 FTA to Hazard Log Traceability

| FTA ID | Top Event | Related Hazard | Safety Requirements |
|--------|-----------|----------------|---------------------|
| FTA-001 | [Event] | [HAZ-ID] | [REQ-IDs] |

### 4.2 FTA to Safety Requirements Traceability

| Safety Requirement | FTA Top Events Mitigated | Risk Reduction |
|--------------------|--------------------------|----------------|
| [REQ-ID] | [FTA-IDs] | [Factor] |

### 4.3 FTA to FMEA Traceability

| FTA Basic Event | FMEA Failure Mode | Failure Rate Source |
|-----------------|------------------|---------------------|
| [BE-ID] | [Failure mode] | [Source] |

---

## 5. FTA VALIDATION

### 5.1 FTA Completeness Checklist

- [ ] All hazardous top events analyzed
- [ ] All immediate causes identified
- [ ] Fault tree decomposed to basic events (no further decomposition)
- [ ] All logic gates correctly applied
- [ ] All basic event failure rates assigned with justification
- [ ] Quantitative analysis performed (top event probability)
- [ ] Minimal cut sets identified
- [ ] Common cause failures considered
- [ ] Sensitivity analysis performed
- [ ] Mitigations incorporated into fault tree
- [ ] SIL achievement verified
- [ ] FTA reviewed by independent reviewer (SIL 3-4)
- [ ] FTA approved by Safety Manager

### 5.2 Independent Review

**Reviewer**: [Name, Role]  
**Review Date**: [Date]  
**Review Findings**: [Summary]  
**Review Status**: [Approved / Approved with comments / Rejected]

---

## 6. FTA MAINTENANCE

### 6.1 Update Triggers

This FTA SHALL be updated when:
1. New hazards identified
2. System design changes affecting fault paths
3. Basic event failure rates updated
4. Mitigations added or modified
5. Field failures provide new data

### 6.2 Review Schedule

**FTA Review Frequency**:
- **During Development**: After design phase (Phase 3), after implementation (Phase 4)
- **After Deployment**: Annually or after significant changes
- **After Incidents**: Within 30 days of safety incident

---

## APPENDIX A: FTA CALCULATION REFERENCE

### A.1 Boolean Algebra Rules

**AND Gate**:
```
P(A AND B) = P(A) × P(B)
```

**OR Gate**:
```
P(A OR B) = P(A) + P(B) - P(A) × P(B)
         ≈ P(A) + P(B)  (if P(A), P(B) << 1)
```

**VOTING Gate (k out of n)**:
```
P(k/n) = Σ C(n,i) × P^i × (1-P)^(n-i)  for i = k to n
where C(n,i) = n! / (i! × (n-i)!)
```

### A.2 Common Cause Failure Beta Factor

**Beta Factor Model**:
```
P(Both A and B fail due to CCF) = β × λ_A × λ_B × t
P(A fails independently) = (1-β) × λ_A × t
```

Typical β values: 0.01 to 0.10 (1% to 10%)

---

## APPENDIX B: FAILURE RATE DATA SOURCES

### B.1 Hardware Component Failure Rates

| Component | Failure Rate (λ) | Source | Notes |
|-----------|------------------|--------|-------|
| [Component] | [λ] | [Source] | [Notes] |

**Standard References**:
- MIL-HDBK-217F - Military Handbook: Reliability Prediction of Electronic Equipment
- IEC 61709 - Electric components - Reliability - Reference conditions for failure rates
- IEEE Std 500 - IEEE Guide to the Collection and Presentation of Electrical, Electronic, and Sensing Component Reliability Data

### B.2 Software Failure Rates

**Software Systematic Failures**:
- Estimated based on complexity, testing coverage, SIL level
- Typical values: 10^-7 to 10^-9 per hour (SIL 3-4 with extensive V&V)

**Justification**: [Rationale for software failure rate estimates]

---

## APPENDIX C: FAULT TREE DIAGRAMS (FULL SIZE)

[Include full-size, high-resolution fault tree diagrams]

---

## APPENDIX D: REVISION HISTORY

| Date | Version | Author | Changes | Approval |
|------|---------|--------|---------|----------|
| YYYY-MM-DD | 0.1 | [Author] | Initial FTA | Draft |

---

**END OF FTA REPORT**
