# Software Validation Verification Report

**Document ID:** DOC-VALVER-YYYY-NNN  
**Document Type:** Software-Validation-Verification-Report  
**Phase:** Phase 7 - Validation (Step B2, Annex C item †)  
**EN 50128 Reference:** Section 6.3.4.12–6.3.4.14  
**Note:** Item † is a platform-designated item (not in Annex C printed table). Required per §6.3.4.12. Numbering subject to Safety Authority confirmation per §6.4.4.1. Primarily applicable at SIL 3-4 (VMGR flow).

---

## Document Control

| Version | Date | Author | Reviewer | Approver | Changes |
|---------|------|--------|----------|----------|---------|
| 0.1 | YYYY-MM-DD | [VER Name] | — | [VMGR Name] | Initial draft |

**Configuration Item:** [CI ID]  
**Baseline:** [Baseline ID]

*Note: Per Table C.1 item †, there is no first_check or second_check. This report is reviewed directly by VMGR for the final V&V decision.*

---

## Approvals

| Role | Name | Signature | Date | SIL Level |
|------|------|-----------|------|-----------|
| Verifier (VER) | [Name] | [Signature] | YYYY-MM-DD | [3/4] |
| V&V Manager (VMGR) | [Name] | [Signature] | YYYY-MM-DD | [3/4] |

**Independence Declaration (SIL 3-4):**  
Verifier [Name] declares independence from the Validator and all development roles per EN 50128 Section 5.1.2.10i. This is a mandatory independence requirement for verification of the Validation Report.

---

## 1. Executive Summary

**Project:** [Project Name]  
**SIL Level:** [3/4]  
**Verification Date:** [Date Range]  
**Verifier:** [Name]  
**Verification Scope:**
- Software Validation Plan (SVaP) — DOC-SVAP-YYYY-NNN (per §6.3.4.13)
- Software Validation Report — DOC-VALRPT-YYYY-NNN (per §6.3.4.14)
- Tools Validation Report — DOC-TOOLSVAL-YYYY-NNN (if applicable, per §6.3.4.14)

**Overall Verification Result:** [PASS / FAIL / PASS WITH OBSERVATIONS]

**Summary:**  
[Brief summary: whether the SVaP and Validation Report meet their respective requirements; any critical findings; readiness for VMGR final V&V decision]

---

## 2. Introduction

### 2.1 Purpose

This document records the results of VER's independent verification of the Software Validation Plan and Software Validation Report, in compliance with EN 50128:2011 §6.3.4.12–6.3.4.14.

This is Phase 7 Track B Step B2. It is produced after:
- QUA has confirmed the Validation Reports are quality-checked
- VER has already produced the Integration Verification Report (item 23, Step B1)

VMGR uses this report, together with item 23, to make the final V&V decision.

### 2.2 What Is Verified

| Document | Normative Basis | Verification Focus |
|----------|-----------------|--------------------|
| Software Validation Plan (SVaP) | §6.3.4.13 | Readability, traceability (§5.3.2.7-10, §6.5.4.14-17), specific requirements (§6.3.4.4-6), internal consistency |
| Software Validation Report | §6.3.4.14 | Readability, traceability, specific requirements (§6.3.4.8-11, §7.7.4.7-11), internal consistency |
| Tools Validation Report (if applicable) | §6.3.4.14 | Same criteria as Validation Report |

### 2.3 Reference Documents

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-SVAP-YYYY-NNN | Software Validation Plan | X.Y |
| DOC-VALRPT-YYYY-NNN | Software Validation Report | X.Y |
| DOC-TOOLSVAL-YYYY-NNN | Tools Validation Report | X.Y |
| DOC-SVP-YYYY-NNN | Software Verification Plan | X.Y |
| DOC-SRS-YYYY-NNN | Software Requirements Specification | X.Y |
| STD-EN50128 | EN 50128:2011 Railway Applications | - |

### 2.4 Verification Team

| Role | Name | Organization | Independence |
|------|------|--------------|--------------|
| Lead Verifier | [Name] | [Organization] | Yes — independent from Validator |
| Verifier | [Name] | [Organization] | Yes — independent from Validator |

---

## 3. Verification Criteria

### 3.1 Software Validation Plan Verification Criteria (§6.3.4.13)

| Criterion | Normative Basis |
|-----------|----------------|
| Readability per §5.3.2.7-10 | §6.3.4.13(a) |
| Traceability per §6.5.4.14-17 | §6.3.4.13(a) |
| Specific requirements §6.3.4.4-6 met | §6.3.4.13(a) |
| Internal consistency | §6.3.4.13(b) |

**§6.3.4.4-6 requirements for the SVaP include:**
- Validation scope and objectives defined
- Independence requirements addressed
- Validation methods and techniques specified
- Acceptance criteria defined

### 3.2 Software Validation Report Verification Criteria (§6.3.4.14)

| Criterion | Normative Basis |
|-----------|----------------|
| Readability per §5.3.2.7-10 | §6.3.4.14(a) |
| Traceability per §6.5.4.14-17 | §6.3.4.14(a) |
| Specific requirements §6.3.4.8-11 met | §6.3.4.14(a) |
| Specific requirements §7.7.4.7-11 met | §6.3.4.14(a) |
| Internal consistency | §6.3.4.14(b) |

**§6.3.4.8-11 and §7.7.4.7-11 requirements include:**
- All validation activities documented
- All test results recorded
- Overall validation conclusion (PASS/FAIL) present with rationale
- Non-conformities documented
- All requirements verified against acceptance criteria

---

## 4. Verification Results

### 4.1 Software Validation Plan Verification (§6.3.4.13)

**Result:** [PASS / FAIL]

#### 4.1.1 Readability (§6.3.4.13(a), §5.3.2.7-10)

| Criterion | Status | Evidence |
|-----------|--------|----------|
| Document structure clear and logical (§5.3.2.7) | [PASS/FAIL] | [Reference] |
| Terminology defined and used consistently (§5.3.2.8) | [PASS/FAIL] | [Reference] |
| Traceability to EN 50128 requirements (§5.3.2.9) | [PASS/FAIL] | [Reference] |
| Document management information present (§5.3.2.10) | [PASS/FAIL] | [Reference] |

#### 4.1.2 Traceability (§6.3.4.13(a), §6.5.4.14-17)

| Criterion | Status | Evidence |
|-----------|--------|----------|
| Traceability to Software Requirements (§5.3.2.9) | [PASS/FAIL] | [Reference] |
| Traceability to system test requirements | [PASS/FAIL] | [Reference] |
| Independence requirements traceable | [PASS/FAIL] | [Reference] |

#### 4.1.3 Specific Requirements §6.3.4.4-6 (§6.3.4.13(a))

| §6.3.4.x Requirement | Status | Evidence |
|----------------------|--------|----------|
| §6.3.4.4 — Validation scope and objectives | [PASS/FAIL] | [Reference] |
| §6.3.4.5 — Independence requirements | [PASS/FAIL] | [Reference] |
| §6.3.4.6 — Validation methods and acceptance criteria | [PASS/FAIL] | [Reference] |

#### 4.1.4 Internal Consistency (§6.3.4.13(b))

| Criterion | Status | Evidence |
|-----------|--------|----------|
| No contradictions between SVaP sections | [PASS/FAIL] | [Reference] |
| All cross-references valid | [PASS/FAIL] | [Reference] |
| Consistent terminology throughout | [PASS/FAIL] | [Reference] |
| Acceptance criteria consistently defined | [PASS/FAIL] | [Reference] |

**SVaP Verification Sub-Result:** [PASS / FAIL]

---

### 4.2 Software Validation Report Verification (§6.3.4.14)

**Result:** [PASS / FAIL]

#### 4.2.1 Readability (§6.3.4.14(a), §5.3.2.7-10)

| Criterion | Status | Evidence |
|-----------|--------|----------|
| Document structure clear and logical | [PASS/FAIL] | [Reference] |
| Terminology consistent | [PASS/FAIL] | [Reference] |
| Traceability to EN 50128 requirements | [PASS/FAIL] | [Reference] |
| Document management information present | [PASS/FAIL] | [Reference] |

#### 4.2.2 Traceability (§6.3.4.14(a), §6.5.4.14-17)

| Criterion | Status | Evidence |
|-----------|--------|----------|
| All test results traceable to requirements | [PASS/FAIL] | [Reference] |
| Validation results traceable to SVaP | [PASS/FAIL] | [Reference] |
| Non-conformities traceable to requirements | [PASS/FAIL] | [Reference] |

#### 4.2.3 Specific Requirements §6.3.4.8-11 (§6.3.4.14(a))

| §6.3.4.x Requirement | Status | Evidence |
|----------------------|--------|----------|
| §6.3.4.8 — All validation activities documented | [PASS/FAIL] | [Reference] |
| §6.3.4.9 — All test results recorded | [PASS/FAIL] | [Reference] |
| §6.3.4.10 — Non-conformities documented | [PASS/FAIL] | [Reference] |
| §6.3.4.11 — Overall validation conclusion present | [PASS/FAIL] | [Reference] |

#### 4.2.4 Specific Requirements §7.7.4.7-11 (§6.3.4.14(a))

| §7.7.4.x Requirement | Status | Evidence |
|----------------------|--------|----------|
| §7.7.4.7 — System test results complete | [PASS/FAIL] | [Reference] |
| §7.7.4.8 — Acceptance criteria evaluated | [PASS/FAIL] | [Reference] |
| §7.7.4.9 — Software suitability for intended use | [PASS/FAIL] | [Reference] |
| §7.7.4.10 — Restrictions and conditions of use | [PASS/FAIL] | [Reference] |
| §7.7.4.11 — Limitations of validation | [PASS/FAIL] | [Reference] |

#### 4.2.5 Internal Consistency (§6.3.4.14(b))

| Criterion | Status | Evidence |
|-----------|--------|----------|
| No contradictions between report sections | [PASS/FAIL] | [Reference] |
| All cross-references valid | [PASS/FAIL] | [Reference] |
| Conclusion consistent with detailed results | [PASS/FAIL] | [Reference] |

**Validation Report Verification Sub-Result:** [PASS / FAIL]

---

### 4.3 Tools Validation Report Verification (if applicable)

**Applicable:** [Yes / No]  
**Result:** [PASS / FAIL / N/A]

If applicable, apply the same criteria as Section 4.2 to the Tools Validation Report.

| Criterion | Status | Evidence |
|-----------|--------|----------|
| Readability (§5.3.2.7-10) | [PASS/FAIL/N/A] | [Reference] |
| Traceability (§6.5.4.14-17) | [PASS/FAIL/N/A] | [Reference] |
| Specific requirements met | [PASS/FAIL/N/A] | [Reference] |
| Internal consistency | [PASS/FAIL/N/A] | [Reference] |

---

## 5. Findings and Non-Conformities

### 5.1 Critical Findings

| ID | Document | §Clause | Description | Status |
|----|----------|---------|-------------|--------|
| F-001 | [SVaP/VR/TVR] | [§X.Y] | [Description] | [Open/Closed] |

### 5.2 Major Findings

| ID | Document | §Clause | Description | Status |
|----|----------|---------|-------------|--------|
| F-002 | [SVaP/VR/TVR] | [§X.Y] | [Description] | [Open/Closed] |

### 5.3 Minor Findings

| ID | Document | §Clause | Description | Recommendation |
|----|----------|---------|-------------|----------------|
| F-003 | [SVaP/VR/TVR] | [§X.Y] | [Description] | [Recommendation] |

### 5.4 Observations

| ID | Description | Recommendation |
|----|-------------|----------------|
| OBS-001 | [Description] | [Recommendation] |

---

## 6. Independence Evidence

**Independence Status:** [COMPLIANT / NOT COMPLIANT]

| Independence Requirement | Status | Evidence |
|--------------------------|--------|----------|
| Independent from Validator | [Yes/No] | [Reference] |
| Independent from all development roles | [Yes/No] | [Reference] |
| Organizational independence documented | [Yes/No] | [Reference] |
| Verifier does not report to Validator | [Yes/No] | [Reference] |

---

## 7. Conclusion and VMGR Input

### 7.1 Summary of Results

| Document Verified | Result |
|-------------------|--------|
| Software Validation Plan (§6.3.4.13) | [PASS / FAIL] |
| Software Validation Report (§6.3.4.14) | [PASS / FAIL] |
| Tools Validation Report (§6.3.4.14, if applicable) | [PASS / FAIL / N/A] |

### 7.2 Overall Verification Result

**Result:** [PASS / FAIL]

**Rationale:**  
[Summary of key findings and basis for the overall result]

### 7.3 Input to VMGR Final V&V Decision

This report, together with the Software Integration Verification Report (item 23), provides the complete VER input for VMGR's final V&V decision per §5.1.2.10(e-f).

**VER Assessment for VMGR:**
- SVaP verification status: [PASS / FAIL / CONDITIONS]
- Validation Report verification status: [PASS / FAIL / CONDITIONS]
- All VER-identified non-conformities: [Resolved / Pending — see Section 5]
- VER recommendation: [APPROVE / CONDITIONAL APPROVE / REJECT] for VMGR consideration

### 7.4 Conditions for VMGR Approval

- [ ] All critical findings resolved
- [ ] All major findings resolved or justified
- [ ] SVaP meets §6.3.4.13 criteria
- [ ] Validation Report meets §6.3.4.14 criteria
- [ ] Independence between VER and VAL documented
- [ ] VMGR concurs with VER assessment

### 7.5 Verifier Statement

I, [Verifier Name], hereby certify that:
1. I have independently verified the Software Validation Plan per §6.3.4.13
2. I have independently verified the Software Validation Report per §6.3.4.14
3. I am independent from the Validator and all development roles
4. The verification results documented in this report are accurate and complete
5. This report is provided as VER input to VMGR's final V&V decision

**Verifier:** [Name]  
**Signature:** [Signature]  
**Date:** [Date]

---

## 8. Appendices

### Appendix A: SVaP Verification Checklist

[Detailed §6.3.4.4-6 requirements checklist with SVaP section cross-references]

### Appendix B: Validation Report Verification Checklist

[Detailed §6.3.4.8-11 and §7.7.4.7-11 requirements checklist with section cross-references]

### Appendix C: Defect Details

[Detailed finding records with evidence, normative basis, and resolution tracking]

---

**End of Software Validation Verification Report**
