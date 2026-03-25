# Software Assessment Report

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 §6.4.4.16-6.4.4.19  
**ANNEX C ITEM**: #46  
**NOTE**: Assessment is MANDATORY for SIL 1-4 (§6.4.1.1). SIL 0 exempt (§6.4.1.2) for ISO 9001-certified organisations.

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SAR-[YYYY]-[NNN] |
| **Version** | [MAJOR.MINOR] |
| **Date** | [YYYY-MM-DD] |
| **Project** | [ProjectName] |
| **SIL Level** | [1 \| 2 \| 3 \| 4] |
| **Author** | [AuthorName], Assessor (ASR) |
| **Reviewer** | [ReviewerName], VER |
| **Status** | [Draft \| Final] |

## DOCUMENT CONTROL

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft |
| 1.0 | YYYY-MM-DD | [Name] | Final release |

---

## 1. Introduction

### 1.1 Purpose

This Software Assessment Report (SAR) records the findings and conclusions of the independent assessment of [Project Name] software, conducted in accordance with EN 50128:2011 Section 6.4.

### 1.2 Assessment Reference

Assessment was performed per the Software Assessment Plan: DOC-SAP-YYYY-NNN v[X.Y].

### 1.3 Independence Declaration

Assessor [Name] declares independence from all development, verification, and validation activities throughout this project. The assessor has no reporting relationship to the project team, per EN 50128 §6.4.1.1.

---

## 2. Assessment Summary

**Overall Assessment Result:** [APPROVED / NOT APPROVED / CONDITIONALLY APPROVED]

| Aspect | Result | Reference |
|--------|--------|-----------|
| Lifecycle processes suitable | [Yes/No] | §6.4.4.5(a) |
| Techniques and measures suitable | [Yes/No] | §6.4.4.5(b) |
| SIL requirements met | [Yes/No] | §6.4.4.5(c) |
| Independence requirements satisfied | [Yes/No] | §6.4.4.5(d) |
| Development documentation suitable | [Yes/No] | §6.4.4.5(e) |

**Conditions (if CONDITIONALLY APPROVED):**  
[List any conditions that must be met for final approval]

---

## 3. Assessment Scope

### 3.1 Documents Reviewed

| Deliverable ID | Document | Version | Review Result |
|---------------|----------|---------|---------------|
| DOC-001-SQAP | Software Quality Assurance Plan | X.Y | [PASS/FAIL/OBSERVATION] |
| DOC-006-SRS | Software Requirements Specification | X.Y | [PASS/FAIL/OBSERVATION] |
| DOC-009-SAS | Software Architecture Specification | X.Y | [PASS/FAIL/OBSERVATION] |
| DOC-025-VALIDATION-REPORT | Software Validation Report | X.Y | [PASS/FAIL/OBSERVATION] |
| [All other Annex C deliverables reviewed] | ... | ... | ... |

### 3.2 Processes Assessed

| Process | Assessment Method | Result |
|---------|-------------------|--------|
| Requirements process (§7.2) | Process audit | [COMPLIANT/NON-COMPLIANT] |
| Design process (§7.3) | Process audit | [COMPLIANT/NON-COMPLIANT] |
| Implementation process (§7.4-7.5) | Audit + sampling | [COMPLIANT/NON-COMPLIANT] |
| Testing process (§7.4-7.7) | Process audit | [COMPLIANT/NON-COMPLIANT] |
| Verification process (§6.2) | Independence check | [COMPLIANT/NON-COMPLIANT] |
| Validation process (§6.3) | Independence check | [COMPLIANT/NON-COMPLIANT] |
| Configuration management (§6.6) | Process audit | [COMPLIANT/NON-COMPLIANT] |

---

## 4. Assessment Findings

### 4.1 Non-Conformances (Must be resolved before approval)

| Finding ID | Phase | Standard Ref | Description | Resolution |
|-----------|-------|-------------|-------------|-----------|
| NC-001 | [Phase] | §[X.Y] | [Description] | [Required action] |

### 4.2 Observations (Recommended improvements)

| Observation ID | Phase | Description | Recommendation |
|---------------|-------|-------------|----------------|
| OBS-001 | [Phase] | [Description] | [Recommendation] |

### 4.3 Positive Observations

[Aspects of the project that are particularly well-executed]

---

## 5. Assessment by Lifecycle Phase

### 5.1 Planning Phase Assessment

**Result:** [COMPLIANT / NON-COMPLIANT / OBSERVATION]

| Requirement | Reference | Status | Finding |
|-------------|-----------|--------|---------|
| SQAP complete and adequate | §6.5.4 | [PASS/FAIL] | [Finding ID or "-"] |
| SCMP complete and adequate | §6.6.4 | [PASS/FAIL] | [Finding ID or "-"] |
| SVP complete and adequate | §6.2.4 | [PASS/FAIL] | [Finding ID or "-"] |
| SVaP complete and adequate | §6.3.4 | [PASS/FAIL] | [Finding ID or "-"] |

### 5.2 Requirements Phase Assessment

**Result:** [COMPLIANT / NON-COMPLIANT / OBSERVATION]

| Requirement | Reference | Status | Finding |
|-------------|-----------|--------|---------|
| SRS complete per §7.2.4 | §7.2.4 | [PASS/FAIL] | [Finding ID or "-"] |
| SRS requirements unambiguous and testable | §7.2.4.10 | [PASS/FAIL] | [Finding ID or "-"] |
| SIL levels assigned per §7.2.4.12 | §7.2.4.12 | [PASS/FAIL] | [Finding ID or "-"] |
| Requirements Verification Report adequate | §7.2.4.20 | [PASS/FAIL] | [Finding ID or "-"] |

### 5.3 Design Phase Assessment

**Result:** [COMPLIANT / NON-COMPLIANT / OBSERVATION]

| Requirement | Reference | Status | Finding |
|-------------|-----------|--------|---------|
| SAS complete per §7.3.4 | §7.3.4 | [PASS/FAIL] | [Finding ID or "-"] |
| Modular approach applied (SIL 2+) | Table A.3 | [PASS/FAIL] | [Finding ID or "-"] |
| Architecture/Design Verification Report adequate | §7.3.4.20 | [PASS/FAIL] | [Finding ID or "-"] |

### 5.4 Implementation Phase Assessment

**Result:** [COMPLIANT / NON-COMPLIANT / OBSERVATION]

| Requirement | Reference | Status | Finding |
|-------------|-----------|--------|---------|
| MISRA C applied (SIL 2+) | Table A.4 | [PASS/FAIL] | [Finding ID or "-"] |
| Static analysis performed (SIL 3+) | Table A.19 | [PASS/FAIL] | [Finding ID or "-"] |
| Complexity limits met | §7.5.4.2 | [PASS/FAIL] | [Finding ID or "-"] |
| No dynamic memory allocation (SIL 2+) | Table A.4 | [PASS/FAIL] | [Finding ID or "-"] |
| Coverage requirements met | Table A.21 | [PASS/FAIL] | [Finding ID or "-"] |

### 5.5 Verification Assessment

**Result:** [COMPLIANT / NON-COMPLIANT / OBSERVATION]

| Requirement | Reference | Status | Finding |
|-------------|-----------|--------|---------|
| Verifier independent from development (SIL 3-4) | §5.3.5.10 | [PASS/FAIL] | [Finding ID or "-"] |
| All verification reports complete | §6.2.4.13 | [PASS/FAIL] | [Finding ID or "-"] |
| VMGR independent from COD and PM (SIL 3-4) | §5.1.2.10e | [PASS/FAIL] | [Finding ID or "-"] |

### 5.6 Validation Assessment

**Result:** [COMPLIANT / NON-COMPLIANT / OBSERVATION]

| Requirement | Reference | Status | Finding |
|-------------|-----------|--------|---------|
| Validator independent from development (SIL 3-4) | §5.3.7.10 | [PASS/FAIL] | [Finding ID or "-"] |
| Validation Report complete per §6.3.4.7-11 | §6.3.4 | [PASS/FAIL] | [Finding ID or "-"] |
| Overall Software Test Report adequate | §7.7.4 | [PASS/FAIL] | [Finding ID or "-"] |

---

## 6. Conclusion and Recommendation

**Assessment Conclusion:**

Based on the assessment activities performed in accordance with the Software Assessment Plan (DOC-SAP-YYYY-NNN), the software development of [Project Name] at SIL [X]:

[Select one:]
- [ ] **IS APPROVED** — All EN 50128 requirements are met. The software is suitable for its intended use at SIL [X].
- [ ] **IS CONDITIONALLY APPROVED** — The software may proceed with the following conditions: [list conditions]
- [ ] **IS NOT APPROVED** — The following non-conformances must be resolved: [list NC IDs]

**Assessor Statement:**

I, [Assessor Name], certify that:
1. I am independent of all development, verification, and validation activities
2. This assessment was performed in accordance with EN 50128:2011 §6.4
3. The findings and conclusions in this report are accurate and complete

**Lead Assessor:** [Name]  
**Signature:** [Signature]  
**Date:** [Date]  
**Organisation:** [Organisation]

---

## 7. Appendices

### Appendix A: Document Review Records

[Detailed review notes for each document reviewed]

### Appendix B: Process Audit Records

[Notes from process interviews and audits]

### Appendix C: Non-Conformance and Observation Details

[Full description and resolution evidence for each finding]

---

**End of Software Assessment Report**
