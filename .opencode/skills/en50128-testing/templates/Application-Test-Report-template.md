# Application Test Report

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 §8.4.5.4  
**ANNEX C ITEM**: #34

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-APP-TEST-RPT-[YYYY]-[NNN] |
| **Version** | [X.Y] |
| **Date** | [YYYY-MM-DD] |
| **Project / Application** | [Application Name] |
| **SIL Level** | [0 \| 1 \| 2 \| 3 \| 4] |
| **Author** | [Name], TST |
| **Reviewer** | [Name], VER |
| **Approver** | [Name], PM |
| **Status** | [Draft \| Final] |

## DOCUMENT CONTROL

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft |
| 1.0 | YYYY-MM-DD | [Name] | Final report |

---

## 1. Executive Summary

**Overall Test Result:** [PASS / FAIL]

| Item | Value |
|------|-------|
| **Application** | [Application Name] |
| **Application Data Version** | [Version] |
| **Generic Software Version** | [Version] |
| **Test Specification** | DOC-APP-TEST-SPEC-YYYY-NNN |
| **Test Period** | [Start Date] to [End Date] |
| **Test Environment** | [Description] |
| **Total Test Cases** | [Count] |
| **Passed** | [Count] |
| **Failed** | [Count] |
| **Skipped / Blocked** | [Count] |

---

## 2. Introduction

### 2.1 Purpose

This Application Test Report records the results of testing performed per the Application Test Specification (DOC-APP-TEST-SPEC-YYYY-NNN) on the complete installation of [Application Name], in accordance with EN 50128:2011 §8.4.5.4.

### 2.2 Test Environment

| Component | Specification | Version/Configuration | Verified |
|-----------|--------------|----------------------|----------|
| Target hardware | [Specification] | [Version] | [Yes/No] |
| Generic software | [Name] | [Version] | [Yes/No] |
| Application data | [Name] | [Version] | [Yes/No] |

---

## 3. Test Results

### 3.1 Test Case Results

| Test ID | Description | Result | Defect ID | Notes |
|---------|-------------|--------|-----------|-------|
| APP-TC-001 | [Description] | [PASS/FAIL/SKIP] | [DEF-NNN or "-"] | [Notes] |
| APP-TC-002 | [Description] | [PASS/FAIL/SKIP] | [DEF-NNN or "-"] | [Notes] |
| APP-TC-S001 | [Safety test] | [PASS/FAIL/SKIP] | [DEF-NNN or "-"] | [Notes] |

### 3.2 Safety Test Results

| Test ID | Safety Requirement | Result | Evidence |
|---------|-------------------|--------|----------|
| APP-TC-S001 | APP-REQ-S001 | [PASS/FAIL] | [Reference] |

### 3.3 Coverage Summary

| Requirement | Covered by Test(s) | Result |
|-------------|-------------------|--------|
| APP-REQ-001 | APP-TC-001 | [PASS/FAIL] |
| APP-REQ-S001 | APP-TC-S001 | [PASS/FAIL] |

**Requirements Coverage:** [X]% ([Count] of [Total] requirements covered)

---

## 4. Defects

### 4.1 Open Defects

| Defect ID | Severity | Description | Affected Requirement | Status |
|-----------|----------|-------------|---------------------|--------|
| DEF-001 | [Critical/High/Medium/Low] | [Description] | [APP-REQ-NNN] | [Open] |

### 4.2 Closed Defects

| Defect ID | Severity | Description | Resolution | Closure Date |
|-----------|----------|-------------|-----------|-------------|
| DEF-XXX | [Severity] | [Description] | [Fix description] | [Date] |

---

## 5. Test Execution Log

| Date | Test ID(s) | Tester | Environment | Result | Notes |
|------|-----------|--------|------------|--------|-------|
| [Date] | APP-TC-001 | [Name] | [Environment] | [PASS/FAIL] | [Notes] |

---

## 6. Test Tester Statement

I, [Tester Name], certify that the tests recorded in this report were performed in accordance with the Application Test Specification and that the results accurately reflect the observed system behaviour.

| Field | Value |
|-------|-------|
| **Tester** | [Name] |
| **Signature** | [Signature] |
| **Date** | [Date] |

---

## 7. Conclusion and Recommendation

**Test Conclusion:**

[ ] **PASS** — All mandatory test cases passed. Application data/algorithms meet all requirements. Recommend proceeding to Application Data/Algorithms Verification.

[ ] **FAIL** — [Count] test cases failed. Defects must be resolved before proceeding.

[ ] **CONDITIONAL PASS** — Minor failures with documented workarounds. Conditions: [list conditions]

---

## 8. Appendices

### Appendix A: Detailed Test Evidence

[Per-test screenshots, log extracts, measurement data]

### Appendix B: Defect Details

[Full defect descriptions and resolution evidence]

---

**End of Application Test Report**
