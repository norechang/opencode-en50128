# Software Requirements Verification Report

**Document ID**: DOC-VER-YYYY-NNN  
**Project**: [Project Name]  
**Software Component**: [Component Name]  
**SIL Level**: [0/1/2/3/4]  
**Version**: [X.Y]  
**Date**: [YYYY-MM-DD]

---

## Document Control

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | YYYY-MM-DD | [Author] | Initial draft | - |
| 1.0 | YYYY-MM-DD | [Author] | First release | [Approver] |

---

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Verifier** (Author) | [Name] | | YYYY-MM-DD |
| **Quality Assurance** (Review) | [Name] | | YYYY-MM-DD |
| **V&V Manager** (Approval - SIL 3-4) | [Name] | | YYYY-MM-DD |
| **Project Manager** (Approval) | [Name] | | YYYY-MM-DD |

**SIL 3-4 Requirements**:
- Verifier SHALL be independent from Requirements Engineer

---

## EN 50128 References

| Section | Title | Relevance |
|---------|-------|-----------|
| **6.2** | Software Verification | PRIMARY - Verification process |
| **7.2** | Software Requirements Specification | Requirements verification |
| **Table A.2** | Software Requirements techniques | Requirements techniques by SIL |

---

## Executive Summary

**Verification Result**: [PASS / FAIL / CONDITIONAL PASS]

**Verification Period**: [Start Date] to [End Date]

**Requirements Verified**: [N] requirements

**Key Findings**:
- Requirements completeness: [Complete / Incomplete]
- Requirements quality: [Acceptable / Issues found]
- Traceability: [Complete / Incomplete]
- EN 50128 compliance: [Compliant / Issues found]

**Verification Decision**: [APPROVE / DO NOT APPROVE / CONDITIONAL]

---

## 1. Introduction

### 1.1 Purpose

This document reports verification of software requirements for [Software Component] per EN 50128:2011 Section 6.2 and 7.2.

**Objectives**:
- Verify requirements completeness
- Verify requirements quality (unambiguous, testable, traceable)
- Verify traceability (system requirements → software requirements)
- Verify EN 50128 requirements techniques applied
- Provide independent verification evidence (SIL 3-4)

### 1.2 Scope

**Verification Activities**:
- Software Requirements Specification review
- Requirements quality assessment
- Traceability verification
- EN 50128 technique compliance check

### 1.3 Reference Documents

- **Software Requirements Specification (SRS)** - DOC-REQ-YYYY-NNN
- **System Requirements Specification** - [System document]
- **Software Verification Plan (SVP)** - DOC-VER-YYYY-NNN
- **Hazard Log** - DOC-SAF-YYYY-NNN

---

## 2. Requirements Verification

### 2.1 Requirements Completeness

| Item | Status | Notes |
|------|--------|-------|
| All functional requirements specified | ✓ / ✗ | [Notes] |
| All performance requirements specified | ✓ / ✗ | [Notes] |
| All safety requirements specified | ✓ / ✗ | [Notes] |
| All interface requirements specified | ✓ / ✗ | [Notes] |
| Normal operation covered | ✓ / ✗ | [Notes] |
| Error conditions covered | ✓ / ✗ | [Notes] |
| Boundary conditions covered | ✓ / ✗ | [Notes] |

**Completeness Result**: [COMPLETE / INCOMPLETE]

### 2.2 Requirements Quality

**Quality Criteria (EN 50128 Section 7.2)**:

| Criterion | Pass | Fail | Notes |
|-----------|------|------|-------|
| **Unambiguous** (clear, single interpretation) | [N] | [M] | [Notes] |
| **Testable** (verifiable by test/analysis) | [N] | [M] | [Notes] |
| **Traceable** (unique ID, traced to source) | [N] | [M] | [Notes] |
| **Complete** (no missing information) | [N] | [M] | [Notes] |
| **Consistent** (no contradictions) | [N] | [M] | [Notes] |
| **Modifiable** (structured, not duplicated) | [N] | [M] | [Notes] |

**Quality Issues**: [List requirements with quality issues]

**Quality Result**: [ACCEPTABLE / ISSUES FOUND]

### 2.3 Requirements Classification

| Category | Count | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 |
|----------|-------|-------|-------|-------|-------|-------|
| Functional | [N] | [n0] | [n1] | [n2] | [n3] | [n4] |
| Performance | [N] | [n0] | [n1] | [n2] | [n3] | [n4] |
| Safety | [N] | - | - | [n2] | [n3] | [n4] |
| Interface | [N] | [n0] | [n1] | [n2] | [n3] | [n4] |
| **TOTAL** | [N] | [n0] | [n1] | [n2] | [n3] | [n4] |

**SIL Classification Result**: [ACCEPTABLE / ISSUES FOUND]

### 2.4 Traceability Verification

**System to Software Requirements**:

| Metric | Value | Target | Status |
|--------|-------|--------|--------|
| Total system requirements | [N] | - | - |
| System requirements traced | [M] | [N] | [✓ / ✗] |
| Coverage | [M/N%] | 100% | [✓ / ✗] |

**Orphan Requirements**: [List software requirements not traced to system]

**Traceability Result**: [COMPLETE / INCOMPLETE]

---

## 3. EN 50128 Compliance

### 3.1 Table A.2 Compliance (Requirements)

**SIL [X] Requirements**:

| Technique | Requirement | Applied | Evidence |
|-----------|-------------|---------|----------|
| Structured Methodology | [M/HR/R] | ✓ / ✗ | [SRS structure] |
| Decision Tables | [HR] | ✓ / ✗ | [Decision tables] |
| Modelling | [HR] | ✓ / ✗ | [Models] |

**Table A.2 Compliance**: [COMPLIANT / NON-COMPLIANT]

---

## 4. Verification Decision

### 4.1 Summary

**Overall Assessment**:
- Requirements completeness: [Complete / Incomplete]
- Requirements quality: [Acceptable / Issues]
- Traceability: [Complete / Incomplete]
- EN 50128 compliance: [Compliant / Non-compliant]

### 4.2 Verifier Decision

**Decision**: [APPROVE / DO NOT APPROVE / CONDITIONAL]

**Rationale**: [Justification]

**Verifier Signature**: _________________ Date: _________

### 4.3 V&V Manager Approval (SIL 3-4)

**Decision**: [APPROVE / DO NOT APPROVE / CONDITIONAL]

**V&V Manager Signature**: _________________ Date: _________

---

## References

- **EN 50128:2011** - Railway applications - Software for railway control and protection systems
- **Software Requirements Specification (SRS)** - DOC-REQ-YYYY-NNN
- **Software Verification Plan (SVP)** - DOC-VER-YYYY-NNN

---

## Document History

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 0.1 | YYYY-MM-DD | [Author] | Initial draft |
| 1.0 | YYYY-MM-DD | [Author] | First release |

---

**END OF DOCUMENT**
