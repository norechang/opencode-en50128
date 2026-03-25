# Application Data/Algorithms Verification Report

**Document ID:** DOC-APPDATAVER-YYYY-NNN  
**Document Type:** Application-Data-Algorithms-Verification-Report  
**Phase:** Phase — Application (Section 8, EN 50128)  
**EN 50128 Reference:** Annex C #35, Section 8.4

---

## Document Control

| Version | Date | Author | Reviewer | Approver | Changes |
|---------|------|--------|----------|----------|---------|
| 0.1 | YYYY-MM-DD | [VER Name] | — | [VAL Name] | Initial draft |

**Configuration Item:** [CI ID]  
**Application:** [Application Name / ID]  
**Generic Software Baseline:** [Baseline ID / Version]  
**SIL Level:** [0/1/2/3/4]

*Note: Per EN 50128 Table C.1, item 35 second_check=VAL. This report must be approved by the Validator.*

---

## Approvals

| Role | Name | Signature | Date | SIL Level |
|------|------|-----------|------|-----------|
| Verifier (VER) | [Name] | [Signature] | YYYY-MM-DD | [0/1/2/3/4] |
| Validator (VAL) | [Name] | [Signature] | YYYY-MM-DD | [0/1/2/3/4] |
| V&V Manager (VMGR) | [Name] | [Signature] | YYYY-MM-DD | [3/4 only] |

**Independence Declaration (SIL 3-4):**  
Verifier [Name] declares independence from the Application Designer and Application Developer per EN 50128 Section 5 and §8.4.

---

## 1. Executive Summary

**Project/Application:** [Application Name]  
**SIL Level:** [0/1/2/3/4]  
**Verification Date:** [Date Range]  
**Verifier:** [Name]  
**Application Data/Algorithm Version:** [Version ID]

**Verification Scope:**
- Application Preparation Plan — DOC-APP-PREP-PLAN-YYYY-NNN
- Application Requirements Specification — DOC-APP-REQ-YYYY-NNN
- Application Test Specification — DOC-APP-TEST-SPEC-YYYY-NNN
- Source Code of Application Data/Algorithms — [CI ID]

**Overall Verification Result:** [PASS / FAIL / PASS WITH CONDITIONS]

**Summary:**  
[Brief narrative of verification findings and overall assessment]

---

## 2. Introduction

### 2.1 Purpose

This document reports the independent verification of application data and algorithms for [Application Name], in compliance with EN 50128:2011 Section 8.4.

Application data/algorithms verification confirms that:
- Application data and algorithms are correct and complete
- Application data is coherent with the application principles and architecture
- Application data is compatible with the generic application software
- Tests on the complete installation are adequate

### 2.2 Reference Documents

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-APP-PREP-PLAN-YYYY-NNN | Application Preparation Plan | X.Y |
| DOC-APP-REQ-YYYY-NNN | Application Requirements Specification | X.Y |
| DOC-APP-TEST-SPEC-YYYY-NNN | Application Test Specification | X.Y |
| DOC-APP-TEST-RPT-YYYY-NNN | Application Test Report | X.Y |
| DOC-SVP-YYYY-NNN | Software Verification Plan | X.Y |
| STD-EN50128 | EN 50128:2011 Railway Applications | - |

### 2.3 Verification Team

| Role | Name | Organization | Independence |
|------|------|--------------|--------------|
| Lead Verifier | [Name] | [Organization] | [Yes/No — SIL 3-4] |

---

## 3. Verification Criteria

### 3.1 Document Verification Criteria (§8.4.4.4 per §8.4.5.1)

Each application document is verified for:

| Criterion | Normative Basis | SIL Requirement |
|-----------|----------------|-----------------|
| Readability per §5.3.2.7-10 | §8.4.5.1(a) | R / HR / **M** |
| Traceability per §6.5.4.14-17 | §8.4.5.1(a) | R / HR / **M** |
| Requirements of applicable section met | §8.4.5.1(a) | **M** (all SILs) |
| Internal consistency | §8.4.5.1(b) | R / HR / **M** |

### 3.2 Application Data/Algorithm Verification Criteria (§8.4.4.4)

| Criterion | Normative Basis | SIL Requirement |
|-----------|----------------|-----------------|
| Correctness of data/algorithms | §8.4.4.4(a) | **M** (all SILs) |
| Completeness of data/algorithms | §8.4.4.4(b) | **M** (all SILs) |
| Coherency with application principles | §8.4.4.4(c) | **M** (all SILs) |
| Coherency with application architecture | §8.4.4.4(d) | **M** (all SILs) |
| Compatibility with generic application | §8.4.4.4(e) | **M** (all SILs) |
| Completeness/correctness of installation tests | §8.4.4.4(f) | **M** (all SILs) |

---

## 4. Verification Results

### 4.1 Application Preparation Plan Verification

**Reference:** DOC-APP-PREP-PLAN-YYYY-NNN  
**Result:** [PASS / FAIL]

| Criterion | Status | Evidence / Notes |
|-----------|--------|-----------------|
| Readability (§5.3.2.7-10) | [PASS/FAIL] | [Reference] |
| Traceability (§6.5.4.14-17) | [PASS/FAIL] | [Reference] |
| §8.4.3.3 requirements met | [PASS/FAIL] | [Reference] |
| Internal consistency | [PASS/FAIL] | [Reference] |

### 4.2 Application Requirements Specification Verification

**Reference:** DOC-APP-REQ-YYYY-NNN  
**Result:** [PASS / FAIL]

| Criterion | Status | Evidence / Notes |
|-----------|--------|-----------------|
| Readability (§5.3.2.7-10) | [PASS/FAIL] | [Reference] |
| Traceability (§6.5.4.14-17) | [PASS/FAIL] | [Reference] |
| §8.4.4.2 requirements met | [PASS/FAIL] | [Reference] |
| Internal consistency | [PASS/FAIL] | [Reference] |

### 4.3 Application Test Specification Verification

**Reference:** DOC-APP-TEST-SPEC-YYYY-NNN  
**Result:** [PASS / FAIL]

| Criterion | Status | Evidence / Notes |
|-----------|--------|-----------------|
| Readability (§5.3.2.7-10) | [PASS/FAIL] | [Reference] |
| Traceability (§6.5.4.14-17) | [PASS/FAIL] | [Reference] |
| §8.4.5.3 requirements met | [PASS/FAIL] | [Reference] |
| Internal consistency | [PASS/FAIL] | [Reference] |

### 4.4 Application Data/Algorithm Verification (§8.4.4.4)

**Result:** [PASS / FAIL]

| §8.4.4.4 Criterion | Status | Evidence / Notes |
|--------------------|--------|-----------------|
| (a) Correctness of all data and algorithms | [PASS/FAIL] | [Reference] |
| (b) Completeness of all data and algorithms | [PASS/FAIL] | [Reference] |
| (c) Coherency with application principles | [PASS/FAIL] | [Reference] |
| (d) Coherency with application architecture | [PASS/FAIL] | [Reference] |
| (e) Compatibility with generic application software | [PASS/FAIL] | [Reference] |
| (f) Completeness and correctness of installation tests | [PASS/FAIL] | [Reference] |

### 4.5 Traceability Verification (SIL 2+ — HR)

| Traceability Chain | Coverage | Status |
|--------------------|----------|--------|
| Application Requirements → Application Data | [%] | [PASS/FAIL] |
| Application Requirements → Application Test Cases | [%] | [PASS/FAIL] |
| Application Data → Application Requirements | [%] | [PASS/FAIL] |

---

## 5. Findings and Non-Conformities

### 5.1 Critical Findings

| ID | Document/Artifact | Description | Status |
|----|------------------|-------------|--------|
| F-001 | [Doc/Artifact] | [Description] | [Open/Closed] |

### 5.2 Major Findings

| ID | Document/Artifact | Description | Status |
|----|------------------|-------------|--------|
| F-002 | [Doc/Artifact] | [Description] | [Open/Closed] |

### 5.3 Observations

| ID | Document/Artifact | Description | Recommendation |
|----|------------------|-------------|----------------|
| OBS-001 | [Doc/Artifact] | [Description] | [Recommendation] |

---

## 6. Independence Evidence (SIL 3-4)

**Independence Status:** [COMPLIANT / NOT COMPLIANT / N/A]

| Independence Requirement | Status | Evidence |
|--------------------------|--------|----------|
| Independent from Application Designer | [Yes/No] | [Reference] |
| Independent from Application Developer | [Yes/No] | [Reference] |
| Organizational independence documented | [Yes/No] | [Reference] |

---

## 7. Summary and Conclusion

### 7.1 Verification Activities Summary

| Activity | Result | Key Findings |
|----------|--------|--------------|
| Application Preparation Plan verification | [PASS/FAIL] | [Summary] |
| Application Requirements Specification verification | [PASS/FAIL] | [Summary] |
| Application Test Specification verification | [PASS/FAIL] | [Summary] |
| Application data/algorithm verification (§8.4.4.4) | [PASS/FAIL] | [Summary] |

### 7.2 Overall Conclusion

**Overall Verification Result:** [PASS / FAIL / PASS WITH CONDITIONS]

**Rationale:**  
[Justification for the overall conclusion]

### 7.3 Conditions for Acceptance

- [ ] All §8.4.4.4 criteria met (a through f)
- [ ] All application documents verified (readability, traceability, requirements, consistency)
- [ ] All critical findings resolved
- [ ] Traceability complete (SIL 2+)
- [ ] Independence documented (SIL 3-4)
- [ ] VAL and VMGR approval obtained (SIL 3-4)

---

## 8. Appendices

### Appendix A: Detailed Data/Algorithm Review Records

[Per-data-item or per-algorithm review records]

### Appendix B: Traceability Matrix

[Application requirements ↔ application data ↔ application test cases]

---

**End of Application Data/Algorithms Verification Report**
