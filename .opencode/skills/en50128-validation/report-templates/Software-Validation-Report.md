# Software Validation Report

**Document ID:** DOC-VALRPT-YYYY-NNN  
**Document Type:** Software-Validation-Report  
**Phase:** Phase 7 — Validation (Annex C item 25)  
**EN 50128 Reference:** §6.3.4.7–6.3.4.11, §7.7.4.6–7.7.4.11  
**Author Role:** VAL  
**1st Check:** VER (item †) | **2nd Check:** none

---

## Document Control

| Version | Date | Author | Reviewer | Approver | Changes |
|---------|------|--------|----------|----------|---------|
| 0.1 | YYYY-MM-DD | [VAL Name] | [QUA Name] | [VMGR Name] | Initial draft |

**Configuration Item:** [CI ID]  
**Baseline:** [Baseline ID]

---

## Approvals

**EN 50128 Annex C Table C.1 Signature Chain**

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Written By: Software Validator | [Name] | _____________ | YYYY-MM-DD |
| 1st Check: Software Verifier | [Name] | _____________ | YYYY-MM-DD |
| 2nd Check: Quality Assurance Engineer | [Name] | _____________ | YYYY-MM-DD |

**Notes:**
- Signature authority per EN 50128 Annex C Table C.1 and project SQAP
- For SIL 3-4: Independence requirements apply per EN 50128 §6.2 (Verification) and §6.3 (Validation)

---

## 1. Executive Summary

**Project:** [Project Name]  
**SIL Level:** [0/1/2/3/4]  
**Software Baseline Validated:** [Version / CI ID — full identification per §6.3.4.10]  
**Validation Period:** [Start date] to [End date]  
**Validator:** [Name]  
**Independent Validator:** [Yes / No — N/A for SIL 0-2]

**Overall Validation Result:** [PASS / FAIL]

**Release Decision (§5.1.2.8):** [AGREE / DISAGREE for software release]

**Summary:**  
[2–4 sentence summary: validation scope, key results, any critical non-conformities,
readiness for release. Reference SVaP DOC-SVaP-YYYY-NNN.]

---

## 2. Introduction

### 2.1 Purpose

This Software Validation Report documents the results of all validation activities performed
on [Software Component / System Name] per EN 50128:2011 §6.3.4.7–6.3.4.11 and §7.7.4.6–
7.7.4.11. It provides the Validator's AGREE/DISAGREE decision for software release per §5.1.2.8.

### 2.2 Validation Scope

| Item | Value |
|------|-------|
| Software component | [Name] |
| Software version | [Version] |
| Configuration Item ID | [CI ID] |
| SIL level | [0/1/2/3/4] |
| Target hardware | [Hardware identification] |
| Validation environment | [Lab / HIL / target / field] |
| Governing SVaP | DOC-SVaP-YYYY-NNN rev X.Y |

### 2.3 Reference Documents

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-SVaP-YYYY-NNN | Software Validation Plan | X.Y |
| DOC-SRS-YYYY-NNN | Software Requirements Specification | X.Y |
| DOC-OTSS-YYYY-NNN | Overall Software Test Specification | X.Y |
| DOC-OTSR-YYYY-NNN | Overall Software Test Report (item 24) | X.Y |
| DOC-SVP-YYYY-NNN | Software Verification Plan | X.Y |
| STD-EN50128 | EN 50128:2011 | — |

### 2.4 Deviations from SVaP

| Deviation ID | Description | Justification | Impact |
|-------------|-------------|---------------|--------|
| DEV-001 | [If any] | [Reason] | [None / Minor / Major] |

---

## 3. Validation Activities Summary

| Activity | Tests Planned | Tests Executed | Passed | Failed | Result |
|----------|--------------|----------------|--------|--------|--------|
| Functional / Black-box Testing | — | — | — | — | [PASS/FAIL] |
| Performance Testing | — | — | — | — | [PASS/FAIL] |
| Operational Scenarios | — | — | — | — | [PASS/FAIL] |
| Safety Scenario Validation | — | — | — | — | [PASS/FAIL] |
| Acceptance Testing (UAT) | — | — | — | — | [PASS/FAIL] |
| **Total** | **—** | **—** | **—** | **—** | **[PASS/FAIL]** |

---

## 4. Functional and Black-box Testing Results (§7.7.4.7 / Table A.14)

**Applicable:** [Yes / No]  
**SIL Requirement:** SIL 3-4: **MANDATORY**; SIL 1-2: HR; SIL 0: HR  
**Result:** [PASS / FAIL]

| Test ID | SRS Req | Description | Technique | Result | Evidence |
|---------|---------|-------------|-----------|--------|----------|
| FT-001 | REQ-xxx | [Test name] | Black-box | [PASS/FAIL] | [log ref] |
| ... | ... | ... | ... | ... | ... |

**Requirements Coverage:**

| Metric | Value | Requirement |
|--------|-------|-------------|
| SRS requirements validated | [N] / [Total] | 100% (SIL 3-4) |
| Safety requirements validated | [N] / [Total] | 100% |
| Failed test cases | [N] | 0 critical/high |

---

## 5. Performance Testing Results (§7.7.4.7 / Table A.18)

**Applicable:** [Yes / No]  
**SIL Requirement:** SIL 3-4: **MANDATORY**; SIL 2: HR  
**Result:** [PASS / FAIL]

### 5.1 Timing Requirements

| Test ID | Parameter | Requirement | Measured (worst case) | Result |
|---------|-----------|-------------|----------------------|--------|
| PT-001 | Response time — [function] | ≤ [X] ms | [Y] ms | [PASS/FAIL] |
| PT-002 | WCET — [task] | ≤ [X] µs | [Y] µs | [PASS/FAIL] |
| ... | ... | ... | ... | ... |

### 5.2 Resource Usage

| Parameter | Requirement | Measured | Result |
|-----------|-------------|----------|--------|
| CPU utilisation (average) | ≤ [X] % | [Y] % | [PASS/FAIL] |
| CPU utilisation (peak) | ≤ [X] % | [Y] % | [PASS/FAIL] |
| RAM usage | ≤ [X] KB | [Y] KB | [PASS/FAIL] |
| Stack usage (max) | ≤ [X] KB | [Y] KB | [PASS/FAIL] |
| Flash / ROM usage | ≤ [X] KB | [Y] KB | [PASS/FAIL] |

---

## 6. Operational Scenario Validation Results (§7.7.4.5)

**Result:** [PASS / FAIL]

| Scenario ID | Name | Type | Result | Notes |
|-------------|------|------|--------|-------|
| SC-001 | [Name] | Normal | [PASS/FAIL] | [Notes] |
| SC-002 | [Name] | Degraded | [PASS/FAIL] | [Notes] |
| SC-003 | [Name] | Emergency | [PASS/FAIL] | [Notes] |
| SC-004 | [Name] | Recovery | [PASS/FAIL] | [Notes] |
| ... | ... | ... | ... | ... |

---

## 7. Safety Validation Results

**Result:** [PASS / FAIL]

| Hazard ID | Hazard Description | Mitigation Requirement | Validation Test | Result |
|-----------|-------------------|----------------------|-----------------|--------|
| HAZ-001 | [Hazard] | [SRS requirement] | [Test ID] | [PASS/FAIL] |
| ... | ... | ... | ... | ... |

**Hazard log reference:** [DOC-HAZLOG-YYYY-NNN]  
**All hazard mitigations validated:** [Yes / No]

---

## 8. Acceptance Testing Results (§7.7.4.8)

**Result:** [PASS / FAIL]

| Test ID | Customer Requirement | Tester | Date | Result | Customer Signature |
|---------|---------------------|--------|------|--------|-------------------|
| UAT-001 | [Requirement] | [Name / Role] | YYYY-MM-DD | [PASS/FAIL] | [Signature] |
| ... | ... | ... | ... | ... | ... |

---

## 9. Requirements Validation Traceability (§6.3.4.8 / §7.7.4.9)

End-to-end traceability: SRS → Overall Test Specification → Validation Test → Result

| SRS Req ID | Requirement Description | Validation Test ID | Result | Coverage |
|-----------|------------------------|-------------------|--------|----------|
| REQ-001 | [Description] | FT-001, SC-001 | PASS | Full |
| REQ-002 | [Description] | FT-002 | PASS | Full |
| ... | ... | ... | ... | ... |

**Traceability completeness:** [N] / [Total] requirements validated ([%])  
**Gaps:** [None / List any unvalidated requirements with justification]

---

## 10. Verification Process Completeness Check (§6.3.4.9)

The Validator confirms that the verification process is complete before issuing the release
decision per §6.3.4.9.

| Verification Activity | Status | Evidence Reference |
|----------------------|--------|-------------------|
| Software Requirements Verification Report (item 8) | [Complete/Pending] | DOC-REQVER-YYYY-NNN |
| Architecture/Design Verification Report (item 14) | [Complete/Pending] | DOC-ARCHDESIGNVER-YYYY-NNN |
| Component Design Verification Report (item 17) | [Complete/Pending] | DOC-COMPDESIGNVER-YYYY-NNN |
| Source Code Verification Report (item 19) | [Complete/Pending] | DOC-SOURCECODEVER-YYYY-NNN |
| Integration Verification Report (item 23) | [Complete/Pending] | DOC-INTVER-YYYY-NNN |
| All VER-identified non-conformities resolved | [Yes/No] | [NCR register ref] |
| VMGR approval on VER reports | [Yes/No] | [VMGR approval ref] |

**Verification process completeness:** [COMPLETE / INCOMPLETE]

---

## 11. Software Baseline Statement (§6.3.4.10)

Per §6.3.4.10, the validation report shall fully state the baseline of software validated.

| Component | Identification | Version | Hash / Build ID |
|-----------|---------------|---------|----------------|
| Source code | [CI ID] | [version] | [git hash / build] |
| Compiled executable | [CI ID] | [version] | [hash] |
| Test harness | [CI ID] | [version] | [hash] |
| Configuration data | [CI ID] | [version] | [hash] |
| Third-party libraries | [CI ID] | [version] | [hash] |

**Baseline record:** [CM baseline ID, e.g. BASELINE-VAL-v1.0]

---

## 12. Known Deficiencies (§6.3.4.11)

Per §6.3.4.11, the validation report shall identify known deficiencies and their impact.

| Deficiency ID | Description | Impact on Use | Restriction / Condition | Status |
|--------------|-------------|--------------|------------------------|--------|
| DEF-001 | [Description] | [Impact] | [Restriction] | [Open/Accepted] |
| ... | ... | ... | ... | ... |

*If no known deficiencies: state explicitly "No known deficiencies identified."*

---

## 13. Non-Conformities

### 13.1 Critical Non-Conformities

| NCR ID | Description | Status | Resolution |
|--------|-------------|--------|------------|
| NCR-001 | [Description] | [Open/Closed] | [Action taken] |

### 13.2 Major Non-Conformities

| NCR ID | Description | Status | Resolution |
|--------|-------------|--------|------------|
| NCR-002 | [Description] | [Open/Closed] | [Action taken] |

### 13.3 Minor Non-Conformities / Observations

| NCR ID | Description | Status |
|--------|-------------|--------|
| NCR-003 | [Description] | [Open/Closed] |

---

## 14. Validation Conclusion (§7.7.4.10–7.7.4.11)

### 14.1 Overall Validation Result

**Result:** [PASS / FAIL]

**Rationale:**  
[Summary of validation findings, evidence of fitness for purpose, and basis for the result.
Reference §6.3.4.8 (activities documented), §6.3.4.9 (verification complete), §6.3.4.10
(baseline stated), §6.3.4.11 (deficiencies identified), §7.7.4.9 (suitability demonstrated).]

### 14.2 Suitability for Intended Use (§7.7.4.9)

The software [has been / has NOT been] demonstrated to be suitable for its intended use in
[operational context]. Basis: [test evidence summary].

### 14.3 Restrictions and Conditions of Use (§7.7.4.10)

[State any restrictions on the use of the validated software, e.g., hardware versions,
environmental conditions, operational constraints.]

### 14.4 Limitations of Validation (§7.7.4.11)

[State any limitations of the validation performed, e.g., partial environment coverage,
test environment differences from production, deferred test cases.]

---

## 15. Release Decision (§5.1.2.8 / §6.3.4.16)

**VAL Release Decision:** [AGREE / DISAGREE]

**Basis:**  
- All functional tests passed: [Yes / No]
- All performance requirements met: [Yes / No]
- All operational scenarios passed: [Yes / No]
- Verification process complete (§6.3.4.9): [Yes / No]
- Zero unresolved critical/high defects: [Yes / No]
- Known deficiencies documented and accepted: [Yes / No]
- Customer acceptance obtained: [Yes / No]

**Conditions (if AGREE with conditions):**  
[List any conditions attached to the release decision, e.g., must resolve DEF-001 before v2.0]

**If DISAGREE:**  
[State reason(s) for blocking release; list defects requiring resolution before re-validation]

**Validator Statement:**  
I, [Validator Name], having independently validated [Software Component] at SIL [level], hereby
give my [AGREE / DISAGREE] for software release per EN 50128:2011 §5.1.2.8. This decision is
final and independent of Project Manager or Lifecycle Coordinator direction.

**Validator:** [Name]  
**Signature:** [Signature]  
**Date:** [Date]

---

**End of Software Validation Report**
