# Application Preparation Verification Report

**Document ID:** DOC-APPPREPVER-YYYY-NNN  
**Document Type:** Application-Preparation-Verification-Report  
**Phase:** Phase — Application (Section 8, EN 50128)  
**EN 50128 Reference:** Annex C #32, Section 8.4.4.4, 8.4.5.1

---

## Document Control

| Version | Date | Author | Reviewer | Approver | Changes |
|---------|------|--------|----------|----------|---------|
| 0.1 | YYYY-MM-DD | [VER Name] | — | — | Initial draft |

**Configuration Item:** [CI ID]  
**Application:** [Application Name / ID]  
**Generic Software Baseline:** [Baseline ID / Version]  
**SIL Level:** [0/1/2/3/4]

*Note: Per EN 50128 Table C.1, item 32 has no first_check or second_check. The report is complete upon VER sign-off.*

---

## Approvals

| Role | Name | Signature | Date | SIL Level |
|------|------|-----------|------|-----------|
| Verifier (VER) | [Name] | [Signature] | YYYY-MM-DD | [0/1/2/3/4] |
| V&V Manager (VMGR) | [Name] | [Signature] | YYYY-MM-DD | [3/4 only] |

---

## 1. Executive Summary

**Project/Application:** [Application Name]  
**SIL Level:** [0/1/2/3/4]  
**Verification Date:** [Date Range]  
**Verifier:** [Name]  
**Application Preparation Plan Version:** [Version ID]

**Overall Verification Result:** [PASS / FAIL / PASS WITH CONDITIONS]

**Summary:**  
[Brief narrative of what was verified and the overall outcome]

---

## 2. Introduction

### 2.1 Purpose

This document reports the independent verification of the Application Preparation activities for [Application Name], in compliance with EN 50128:2011 Section 8.4.4.4 and 8.4.5.1.

Application preparation verification confirms that:
- Every activity ensuring correctness of data and algorithms has been documented
- Every activity ensuring completeness of data and algorithms has been documented
- Coherency of data/algorithms with application principles has been verified
- Coherency of data/algorithms with application architecture has been verified
- Compatibility with the generic application has been evaluated
- Completeness and correctness of tests on the complete installation have been checked

### 2.2 Reference Documents

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-APP-PREP-PLAN-YYYY-NNN | Application Preparation Plan | X.Y |
| DOC-APP-REQ-YYYY-NNN | Application Requirements Specification | X.Y |
| DOC-SVP-YYYY-NNN | Software Verification Plan | X.Y |
| STD-EN50128 | EN 50128:2011 Railway Applications | - |

### 2.3 Verification Team

| Role | Name | Organization | Independence |
|------|------|--------------|--------------|
| Verifier | [Name] | [Organization] | [Yes/No — SIL 3-4] |

---

## 3. Verification Criteria (§8.4.4.4)

| Criterion | Normative Basis | SIL Requirement |
|-----------|----------------|-----------------|
| (a) Correctness activities documented | §8.4.4.4(a) | **M** (all SILs) |
| (b) Completeness activities documented | §8.4.4.4(b) | **M** (all SILs) |
| (c) Coherency with application principles | §8.4.4.4(c) | **M** (all SILs) |
| (d) Coherency with application architecture | §8.4.4.4(d) | **M** (all SILs) |
| (e) Compatibility with generic application | §8.4.4.4(e) | **M** (all SILs) |
| (f) Installation test completeness/correctness | §8.4.4.4(f) | **M** (all SILs) |

---

## 4. Verification Results

### 4.1 Application Preparation Plan — Document Quality (§8.4.5.1)

**Reference:** DOC-APP-PREP-PLAN-YYYY-NNN  
**Result:** [PASS / FAIL]

| Criterion | Status | Evidence / Notes |
|-----------|--------|-----------------|
| Readability (§5.3.2.7-10) | [PASS/FAIL] | [Reference] |
| Traceability (§6.5.4.14-17) | [PASS/FAIL] | [Reference] |
| §8.4.3.3 content requirements met | [PASS/FAIL] | [Reference] |
| Internal consistency | [PASS/FAIL] | [Reference] |

### 4.2 Correctness Activities Verified (§8.4.4.4(a))

| Activity Description | Documented | Correct | Evidence |
|----------------------|------------|---------|----------|
| [Data validation activity 1] | [Yes/No] | [Yes/No] | [Reference] |
| [Algorithm correctness check 1] | [Yes/No] | [Yes/No] | [Reference] |
| [Range/boundary check] | [Yes/No] | [Yes/No] | [Reference] |

**Result:** [PASS / FAIL]  
**Finding:** [Any issues identified]

### 4.3 Completeness Activities Verified (§8.4.4.4(b))

| Activity Description | Documented | Complete | Evidence |
|----------------------|------------|----------|----------|
| [All required data present check] | [Yes/No] | [Yes/No] | [Reference] |
| [All required parameters defined] | [Yes/No] | [Yes/No] | [Reference] |
| [All required algorithms present] | [Yes/No] | [Yes/No] | [Reference] |

**Result:** [PASS / FAIL]  
**Finding:** [Any issues identified]

### 4.4 Coherency with Application Principles (§8.4.4.4(c))

| Principle | Coherent | Evidence / Notes |
|-----------|----------|-----------------|
| [Application safety principle 1] | [Yes/No] | [Reference] |
| [Application operational principle 1] | [Yes/No] | [Reference] |
| [Fail-safe behaviour principles] | [Yes/No] | [Reference] |

**Result:** [PASS / FAIL]  
**Finding:** [Any issues identified]

### 4.5 Coherency with Application Architecture (§8.4.4.4(d))

| Architecture Element | Coherent | Evidence / Notes |
|----------------------|----------|-----------------|
| [Software component 1] | [Yes/No] | [Reference] |
| [Interface specification 1] | [Yes/No] | [Reference] |
| [Data flow design] | [Yes/No] | [Reference] |

**Result:** [PASS / FAIL]  
**Finding:** [Any issues identified]

### 4.6 Compatibility with Generic Application (§8.4.4.4(e))

| Compatibility Check | Status | Evidence / Notes |
|---------------------|--------|-----------------|
| Data format compatibility | [PASS/FAIL] | [Reference] |
| Parameter range compatibility | [PASS/FAIL] | [Reference] |
| Interface compatibility | [PASS/FAIL] | [Reference] |
| Version compatibility declared | [PASS/FAIL] | [Reference] |

**Result:** [PASS / FAIL]  
**Finding:** [Any issues identified]

### 4.7 Installation Test Completeness/Correctness (§8.4.4.4(f))

| Test Coverage Check | Status | Evidence / Notes |
|--------------------|--------|-----------------|
| All application data tested on complete installation | [PASS/FAIL] | [Reference] |
| Test results documented | [PASS/FAIL] | [Reference] |
| Test pass criteria defined and met | [PASS/FAIL] | [Reference] |
| Test coverage adequate for SIL level | [PASS/FAIL] | [Reference] |

**Result:** [PASS / FAIL]  
**Finding:** [Any issues identified]

---

## 5. Findings and Non-Conformities

### 5.1 Critical Findings

| ID | Criterion | Description | Status |
|----|-----------|-------------|--------|
| F-001 | §8.4.4.4([x]) | [Description] | [Open/Closed] |

### 5.2 Major Findings

| ID | Criterion | Description | Status |
|----|-----------|-------------|--------|
| F-002 | §8.4.4.4([x]) | [Description] | [Open/Closed] |

### 5.3 Observations

| ID | Criterion | Description | Recommendation |
|----|-----------|-------------|----------------|
| OBS-001 | [Criterion] | [Description] | [Recommendation] |

---

## 6. Independence Evidence (SIL 3-4)

**Independence Status:** [COMPLIANT / NOT COMPLIANT / N/A]

| Independence Requirement | Status | Evidence |
|--------------------------|--------|----------|
| Independent from Application Designer | [Yes/No] | [Reference] |
| Independent from Application Developer | [Yes/No] | [Reference] |

---

## 7. Summary and Conclusion

### 7.1 Verification Activities Summary

| Activity | Result | Key Findings |
|----------|--------|--------------|
| Application Preparation Plan document quality | [PASS/FAIL] | [Summary] |
| (a) Correctness activities | [PASS/FAIL] | [Summary] |
| (b) Completeness activities | [PASS/FAIL] | [Summary] |
| (c) Coherency with application principles | [PASS/FAIL] | [Summary] |
| (d) Coherency with application architecture | [PASS/FAIL] | [Summary] |
| (e) Compatibility with generic application | [PASS/FAIL] | [Summary] |
| (f) Installation test completeness/correctness | [PASS/FAIL] | [Summary] |

### 7.2 Overall Conclusion

**Overall Verification Result:** [PASS / FAIL / PASS WITH CONDITIONS]

**Rationale:**  
[Justification for the overall conclusion]

### 7.3 Conditions for Acceptance

- [ ] All §8.4.4.4 criteria (a–f) met
- [ ] Application Preparation Plan document quality verified
- [ ] All critical findings resolved
- [ ] Independence documented (SIL 3-4)

---

## 8. Appendices

### Appendix A: Detailed Review Records

[Detailed per-item review records]

---

**End of Application Preparation Verification Report**
