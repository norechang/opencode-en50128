# Phase Gate Check Report

**Document ID**: DOC-GATE-YYYY-NNN  
**Version**: 1.0  
**Date**: YYYY-MM-DD  
**Project**: [Project Name]  
**SIL Level**: [0, 1, 2, 3, or 4]  
**Author**: Lifecycle Coordinator (COD)  
**Status**: Final

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-GATE-YYYY-NNN |
| **Version** | 1.0 |
| **Date** | YYYY-MM-DD |
| **Project** | [Project Name] |
| **SIL Level** | [0, 1, 2, 3, or 4] |
| **Phase** | Phase [X]: [Phase Name] |
| **Gate Check ID** | GATE-[PHASE]-YYYY-NNN |
| **Author** | Lifecycle Coordinator (COD) |
| **Status** | Final |

---

## GATE CHECK SUMMARY

| Property | Value |
|----------|-------|
| **Phase** | Phase [X]: [Phase Name] |
| **Gate Check Date** | YYYY-MM-DD |
| **Gate Check Result** | **[PASS / CONDITIONAL PASS / FAIL]** |
| **Next Phase** | Phase [X+1]: [Next Phase Name] |
| **Transition Authorized** | [YES / NO / CONDITIONAL] |
| **Conditions** | [List conditions if conditional pass] |

---

## 1. GATE CHECK OVERVIEW

### 1.1 Purpose

This Gate Check Report documents the Lifecycle Coordinator (COD) assessment of Phase [X] completion for **[Project Name]** in accordance with EN 50128:2011 lifecycle requirements.

**Gate Check Objective**: Verify that all Phase [X] deliverables, quality criteria, and EN 50128 requirements have been met before authorizing transition to Phase [X+1].

### 1.2 Scope

**Phase Assessed**: Phase [X]: [Phase Name] (EN 50128 Section [X.X])

**Assessment Period**: [Start Date] to [End Date] ([N] days)

**Assessment Method**: [Checklist-based / Review-based / Audit-based]

**Assessor**: Lifecycle Coordinator (COD)

**COD Mode**: [Advisory / Semi-strict / Strict Gatekeeper]

### 1.3 EN 50128 Lifecycle Context

**EN 50128 Section**: [Section X.X] - [Phase Name]

**Mandatory Deliverables** (per Annex C Table C.1):
- [Deliverable 1]
- [Deliverable 2]
- [Deliverable 3]

**Mandatory Techniques** (per Table A.X for SIL [Y]):
- [Technique 1]
- [Technique 2]

**Quality Gates** (per SIL [Y]):
- [Quality gate 1]
- [Quality gate 2]

---

## 2. DELIVERABLE ASSESSMENT

### 2.1 Deliverable Checklist

| Deliverable ID | Document Name | Document ID | Version | Status | QUA | VER | VAL | COD | Assessment |
|---------------|---------------|-------------|---------|--------|-----|-----|-----|-----|------------|
| D-[X]-01 | [Document name] | DOC-XXX-YYYY-NNN | [Ver] | [Status] | [Date] | [Date] | [Date] | [Date] | [PASS/FAIL] |
| D-[X]-02 | [Document name] | DOC-XXX-YYYY-NNN | [Ver] | [Status] | [Date] | [Date] | [Date] | [Date] | [PASS/FAIL] |

**Deliverable Status Summary**:
- **Total deliverables**: [N]
- **Complete**: [N] ([X]%)
- **Incomplete**: [N]
- **Approved**: [N] ([X]%)
- **Not approved**: [N]

**Assessment**: [All deliverables complete and approved / Deliverables missing or not approved]

---

### 2.2 Deliverable Quality Assessment

#### D-[X]-01: [Document Name]

**Document**: [Document Name] (DOC-XXX-YYYY-NNN v[X.Y])  
**EN 50128 Reference**: [Section X.X]  
**SIL Requirement**: [Mandatory / Highly Recommended / Recommended]

**Template Compliance**:
- [ ] Document ID format correct (DOC-TYPE-YYYY-NNN)
- [ ] Version number format correct (MAJOR.MINOR)
- [ ] Document Control table present
- [ ] Approvals table present with SIL-appropriate signatures
- [ ] All mandatory header fields completed

**Content Quality**:
- [ ] All required sections present (per EN 50128 Section [X.X])
- [ ] Content complete and unambiguous
- [ ] Traceability to requirements (if applicable)
- [ ] Technical accuracy verified
- [ ] SIL-appropriate level of detail

**Review Status**:
- **QA Review**: [Date] - [ACCEPTED / REJECTED / NOT REQUIRED]
- **VER Review**: [Date] - [VERIFIED / REJECTED / NOT REQUIRED]
- **VAL Review**: [Date] - [VALIDATED / REJECTED / NOT REQUIRED]
- **COD Approval**: [Date] - [APPROVED / REJECTED / PENDING]

**Findings**:
1. [Finding 1] - Severity: [H/M/L] - Status: [Open/Closed]
2. [Finding 2] - Severity: [H/M/L] - Status: [Open/Closed]

**Assessment**: [PASS / FAIL] - [Rationale]

---

[Repeat for each deliverable]

---

## 3. QUALITY CRITERIA ASSESSMENT

### 3.1 SIL-Specific Quality Criteria

**SIL Level**: [0, 1, 2, 3, or 4]

| Criterion | SIL [X] Requirement | Actual | Target | Status | Assessment |
|-----------|-------------------|--------|--------|--------|------------|
| Code Coverage - Statement | [X]% (M/HR/R) | [Y]% | [X]% | [PASS/FAIL] | [Comment] |
| Code Coverage - Branch | [X]% (M/HR/R) | [Y]% | [X]% | [PASS/FAIL] | [Comment] |
| Code Coverage - Condition | [X]% (M/HR/R) | [Y]% | [X]% | [PASS/FAIL] | [Comment] |
| Cyclomatic Complexity | ≤ [N] (M/HR/R) | ≤ [M] | ≤ [N] | [PASS/FAIL] | [Comment] |
| MISRA C Compliance | Zero mandatory violations | [N] violations | 0 | [PASS/FAIL] | [Comment] |
| Static Analysis | No critical findings | [N] findings | 0 | [PASS/FAIL] | [Comment] |
| Requirements Traceability | 100% (M for SIL 3-4) | [X]% | 100% | [PASS/FAIL] | [Comment] |
| Independent Verification | Required (SIL 3-4) | [YES/NO] | YES | [PASS/FAIL] | [Comment] |
| Independent Validation | Required (SIL 3-4) | [YES/NO] | YES | [PASS/FAIL] | [Comment] |

**Quality Criteria Summary**:
- **Total criteria**: [N]
- **Passed**: [N] ([X]%)
- **Failed**: [N]
- **Not applicable**: [N]

**Assessment**: [All quality criteria met / Quality criteria violations]

---

### 3.2 EN 50128 Technique Compliance

**Mandatory Techniques** (Table A.[X] for SIL [Y]):

| Technique | EN 50128 Requirement | Applied | Evidence | Status |
|-----------|---------------------|---------|----------|--------|
| [Technique 1] | M (Mandatory) | [YES/NO] | [Document/Section] | [PASS/FAIL] |
| [Technique 2] | HR (Highly Recommended) | [YES/NO] | [Document/Section] | [PASS/FAIL] |
| [Technique 3] | R (Recommended) | [YES/NO] | [Document/Section] | [PASS/FAIL] |

**Technique Compliance Summary**:
- **Mandatory (M)**: [N] of [N] applied ([X]%)
- **Highly Recommended (HR)**: [N] of [N] applied ([X]%)
- **Recommended (R)**: [N] of [N] applied ([X]%)

**Non-Compliance**:
- [Technique name]: [Justification for non-application]

**Assessment**: [All mandatory techniques applied / Missing mandatory techniques]

---

### 3.3 Independence Requirements (SIL 3-4 Only)

**Verifier Independence**:
- **Required**: [YES / NO] (SIL 3-4 mandatory)
- **Verifier**: [Name, Organization]
- **Independence verified**: [YES / NO]
- **Verification report**: [Document ID]
- **Assessment**: [PASS / FAIL]

**Validator Independence**:
- **Required**: [YES / NO] (SIL 3-4 mandatory)
- **Validator**: [Name, Organization]
- **Independence verified**: [YES / NO]
- **Validation report**: [Document ID]
- **Assessment**: [PASS / FAIL]

**Assessment**: [Independence requirements met / Independence violations]

---

## 4. TRACEABILITY ASSESSMENT

### 4.1 Requirements Traceability

**Traceability Matrix**: [Document ID]

| Requirement Type | Total | Traced | Verified | Validated | Percentage |
|------------------|-------|--------|----------|-----------|------------|
| Functional | [N] | [N] | [N] | [N] | [X]% |
| Performance | [N] | [N] | [N] | [N] | [X]% |
| Safety | [N] | [N] | [N] | [N] | [X]% |
| Interface | [N] | [N] | [N] | [N] | [X]% |
| Implementation | [N] | [N] | [N] | [N] | [X]% |
| **TOTAL** | [N] | [N] | [N] | [N] | [X]% |

**Traceability Target**: 100% (Mandatory for SIL 3-4)

**Assessment**: [Traceability complete / Traceability gaps]

---

### 4.2 Hazard to Mitigation Traceability

**Hazard Log**: [Document ID]

| Hazard ID | Severity | SIL | Safety Requirements | Mitigations | Verified | Status |
|-----------|----------|-----|---------------------|-------------|----------|--------|
| HAZ-001 | [Level] | [SIL] | [REQ-IDs] | [Mitigations] | [YES/NO] | [Open/Closed] |

**Hazard Assessment**:
- **Total hazards**: [N]
- **Hazards mitigated**: [N] ([X]%)
- **Open hazards**: [N] (0 target for deployment)
- **Residual risk**: [TOLERABLE / UNACCEPTABLE]

**Assessment**: [All hazards mitigated / Open hazards remain]

---

## 5. DEFECT AND ISSUE ASSESSMENT

### 5.1 Open Defects

**Defect Log**: [Document ID or location]

| Defect ID | Severity | Description | Module/Document | Status | Target Resolution |
|-----------|----------|-------------|----------------|--------|------------------|
| DEF-001 | [H/M/L] | [Description] | [Location] | [Open/Closed] | [Date] |

**Defect Summary**:
- **Total defects**: [N]
- **Open defects**: [N]
- **Safety-critical defects**: [N] (0 target for deployment)
- **High severity defects**: [N]
- **Medium severity defects**: [N]
- **Low severity defects**: [N]

**Assessment**: [No blocking defects / Blocking defects present]

---

### 5.2 Open Issues and Risks

**Issue/Risk Log**: [Document ID or location]

| Issue ID | Type | Description | Severity | Mitigation | Status |
|----------|------|-------------|----------|------------|--------|
| ISS-001 | [Issue/Risk] | [Description] | [H/M/L] | [Mitigation] | [Open/Closed] |

**Issue Summary**:
- **Total open issues**: [N]
- **Safety-critical issues**: [N] (0 target for deployment)
- **High severity issues**: [N]

**Assessment**: [No blocking issues / Blocking issues present]

---

## 6. CONFIGURATION MANAGEMENT ASSESSMENT

### 6.1 Baseline Status

**Configuration Baseline**: [Baseline ID] (e.g., Baseline 1 - Requirements Phase)

**Baseline Contents**:
- [Document 1] (DOC-XXX-YYYY-NNN v[X.Y])
- [Document 2] (DOC-XXX-YYYY-NNN v[X.Y])
- [Source code] (if applicable) - Version [X.Y.Z]

**Baseline Status**:
- [ ] All deliverables included in baseline
- [ ] All deliverables under version control
- [ ] Baseline tagged in repository
- [ ] Configuration audit performed
- [ ] No unapproved changes

**Assessment**: [Baseline established / Baseline incomplete]

---

### 6.2 Change Control

**Change Requests**: [Document ID or location]

| CR ID | Description | Impact | Status | Approval |
|-------|-------------|--------|--------|----------|
| CR-001 | [Description] | [Impact] | [Open/Closed] | [Approved/Rejected] |

**Change Control Summary**:
- **Total change requests**: [N]
- **Open change requests**: [N]
- **Approved changes**: [N]
- **Changes requiring re-verification**: [N]

**Assessment**: [Change control satisfactory / Change control issues]

---

## 7. PROCESS COMPLIANCE ASSESSMENT

### 7.1 Lifecycle Process Compliance

**EN 50128 Lifecycle Requirements** (Section 5.3):

| Requirement | Description | Compliant | Evidence |
|-------------|-------------|-----------|----------|
| 5.3.2.5 | Phase activities defined and planned | [YES/NO] | [Document] |
| 5.3.2.10 | Independent verification (SIL 3-4) | [YES/NO] | [Document] |
| 5.3.2.11 | Independent validation (SIL 3-4) | [YES/NO] | [Document] |
| 5.3.2.13 | Phase modification authority | [YES/NO] | [Document] |

**Process Compliance Summary**:
- **Total requirements**: [N]
- **Compliant**: [N] ([X]%)
- **Non-compliant**: [N]

**Assessment**: [Process compliant / Process violations]

---

### 7.2 Quality Assurance Assessment

**SQAP Compliance**: [Document ID]

**QA Activities Performed**:
- [ ] Document template compliance checks
- [ ] Code reviews (all code, mandatory)
- [ ] Design reviews (SIL 3-4 mandatory)
- [ ] MISRA C compliance verification
- [ ] Complexity analysis
- [ ] QA audits

**QA Audit Results**: [Summary of QA audit findings]

**Assessment**: [QA requirements met / QA deficiencies]

---

## 8. GATE CHECK DECISION

### 8.1 Gate Criteria Summary

| Criterion Category | Result | Weight | Assessment |
|--------------------|--------|--------|------------|
| **Deliverables Complete** | [PASS/FAIL] | Critical | [Comment] |
| **Quality Criteria Met** | [PASS/FAIL] | Critical | [Comment] |
| **EN 50128 Techniques Applied** | [PASS/FAIL] | Critical | [Comment] |
| **Traceability Complete** | [PASS/FAIL] | Critical (SIL 3-4) | [Comment] |
| **Defects Resolved** | [PASS/FAIL] | Critical | [Comment] |
| **Configuration Management** | [PASS/FAIL] | Important | [Comment] |
| **Process Compliance** | [PASS/FAIL] | Critical | [Comment] |
| **Independence Verified** | [PASS/FAIL] | Critical (SIL 3-4) | [Comment] |

**Critical Criteria Failed**: [N] (0 required for PASS)

---

### 8.2 COD Gate Decision

**Gate Check Result**: **[PASS / CONDITIONAL PASS / FAIL]**

**Decision Rationale**:

[Detailed rationale for gate decision, including:
- Summary of assessment results
- Critical criteria status
- SIL-specific requirements met/not met
- Risk assessment
- Justification for decision]

**Conditions** (if Conditional Pass):
1. [Condition 1] - Target resolution: [Date]
2. [Condition 2] - Target resolution: [Date]

**Next Phase Authorization**: [AUTHORIZED / NOT AUTHORIZED / CONDITIONAL]

**Next Phase**: Phase [X+1]: [Phase Name]

**Target Start Date**: [YYYY-MM-DD]

---

### 8.3 Recommendations

**For Next Phase**:
1. [Recommendation 1]
2. [Recommendation 2]
3. [Recommendation 3]

**For Project Management**:
1. [Recommendation 1]
2. [Recommendation 2]

**For Continuous Improvement**:
1. [Lesson learned 1]
2. [Lesson learned 2]

---

## 9. APPROVAL

| Role | Name | Signature | Date | Comment |
|------|------|-----------|------|---------|
| **Lifecycle Coordinator (COD)** | [Name] | | YYYY-MM-DD | Gate check decision |
| **Project Manager (PM)** | [Name] | | YYYY-MM-DD | Acknowledge decision |
| **V&V Manager (VMGR)** (SIL 3-4) | [Name] | | YYYY-MM-DD | Concurrence (independent) |

**Note**: For SIL 3-4, VMGR must concur with gate decision (but COD has final authority for lifecycle progression).

---

## APPENDIX A: GATE CRITERIA CHECKLIST (DETAILED)

### A.1 Phase [X] Mandatory Criteria

[Detailed checklist of all gate criteria specific to this phase]

| Criterion ID | Criterion Description | Status | Evidence | Assessment |
|--------------|----------------------|--------|----------|------------|
| GC-[X]-001 | [Criterion] | [PASS/FAIL] | [Document] | [Comment] |

---

## APPENDIX B: SUPPORTING EVIDENCE

### B.1 Evidence Register

| Evidence ID | Evidence Type | Document | Version | Date | Location |
|-------------|--------------|----------|---------|------|----------|
| E-[X]-001 | [Type] | [Document name] | [Ver] | [Date] | [Location] |

---

## APPENDIX C: NON-COMPLIANCE JUSTIFICATIONS

[For any EN 50128 mandatory techniques or requirements not applied, provide detailed justification]

---

## APPENDIX D: LESSONS LEARNED

**What Went Well**:
- [Item 1]
- [Item 2]

**What Could Be Improved**:
- [Item 1]
- [Item 2]

**Actions for Future Phases**:
- [Action 1]
- [Action 2]

---

## APPENDIX E: GATE CHECK METRICS

### E.1 Phase Metrics

| Metric | Value | Target | Status |
|--------|-------|--------|--------|
| Phase Duration | [N] days | [Target] days | [On time / Delayed] |
| Deliverable Count | [N] | [N] | [Complete / Incomplete] |
| Defect Count | [N] | [Target] | [Acceptable / High] |
| Rework Count | [N] iterations | [1-2] | [Acceptable / High] |
| Document Quality (QA accepted first pass) | [X]% | >80% | [Good / Poor] |

### E.2 Quality Metrics

| Metric | Value | Target | Status |
|--------|-------|--------|--------|
| Code Coverage - Statement | [X]% | [Target]% | [Met / Not met] |
| Code Coverage - Branch | [X]% | [Target]% | [Met / Not met] |
| Cyclomatic Complexity (max) | [N] | ≤ [Target] | [Met / Not met] |
| MISRA C Violations | [N] | 0 | [Met / Not met] |

---

**END OF GATE CHECK REPORT**
