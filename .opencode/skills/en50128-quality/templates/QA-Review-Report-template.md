# Quality Assurance Review Report

**Document ID:** DOC-QAR-YYYY-NNN  
**Project:** [Project Name]  
**System/Subsystem:** [System Name]  
**SIL Level:** [0 | 1 | 2 | 3 | 4]

---

## Document Control

| Version | Date | Author | Change Description | Status |
|---------|------|--------|-------------------|--------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft | Draft |

---

## Approvals (SIL-Dependent)

| Role | Name | Signature | Date | SIL Requirement |
|------|------|-----------|------|----------------|
| **Quality Assurance** | [Name] | [Signature] | YYYY-MM-DD | All SILs |
| **Project Manager** | [Name] | [Signature] | YYYY-MM-DD | All SILs |
| **Independent Verifier** | [Name] | [Signature] | YYYY-MM-DD | SIL 3-4 |

**Independence Note (SIL 3-4):**
- Verifier SHALL NOT be Requirements Manager, Designer, Implementer, Integrator, or Tester
- QA review MUST be independent of development activities

---

## Executive Summary

**Review Type:** [Code Review | Document Review | Design Review | Process Audit | Template Compliance | Phase Gate Review]

**Review Date:** YYYY-MM-DD  
**Phase/Deliverable:** [Requirements | Design | Implementation | Integration | Validation | etc.]

**Overall Result:** [Pass | Pass with Minor Issues | Fail - Rework Required]

**Key Findings:**
- [Summary finding 1]
- [Summary finding 2]
- [Summary finding 3]

**Critical Defects:** [Number]  
**Major Defects:** [Number]  
**Minor Defects:** [Number]  
**Observations:** [Number]

**Recommendation:** [Approve | Approve with Conditions | Reject - Require Rework]

---

## 1. Review Information

### 1.1 Review Identification

| Field | Value |
|-------|-------|
| **Review ID** | QAR-YYYY-NNN |
| **Review Type** | [Code Review \| Document Review \| Design Review \| Process Audit \| Template Compliance \| Phase Gate] |
| **Artifacts Reviewed** | [List key artifacts/deliverables] |
| **Review Method** | [Formal Inspection \| Walkthrough \| Desk Check \| Tool-Based Analysis] |
| **Review Date** | YYYY-MM-DD |
| **Review Duration** | [X hours] |
| **SIL Level** | [0 \| 1 \| 2 \| 3 \| 4] |

### 1.2 Review Team

| Name | Role | Expertise | Independence Status |
|------|------|-----------|-------------------|
| [Name] | QA Lead | [Domain] | Independent |
| [Name] | Technical Reviewer | [Domain] | [Independent / Not Applicable] |
| [Name] | Author/Presenter | [Domain] | N/A (Author) |

**Independence Verification (SIL 3-4):**
- [ ] QA reviewer is independent of development team
- [ ] No conflicts of interest identified
- [ ] Independence documented and approved

### 1.3 Review Scope

**Artifacts Under Review:**
- [ ] Documents (specify IDs)
- [ ] Source code modules (list files)
- [ ] Test specifications/reports
- [ ] Design specifications
- [ ] Processes/procedures
- [ ] Other: [Specify]

**Specific Artifacts:**
| Artifact ID | Artifact Name | Version | Author |
|-------------|---------------|---------|--------|
| [DOC-XXX-YYYY-NNN or filename] | [Name] | [X.Y] | [Name] |

**Review Focus Areas:**
- [ ] EN 50128 compliance
- [ ] Template compliance (document structure)
- [ ] Coding standards (MISRA C for SIL 2+)
- [ ] Complexity limits (≤10 for SIL 3-4, ≤15 for SIL 2)
- [ ] Defensive programming
- [ ] Traceability
- [ ] Test coverage (SIL-dependent)
- [ ] Safety requirements
- [ ] Other: [Specify]

---

## 2. Review Criteria

### 2.1 EN 50128 Quality Requirements (Section 6.5)

**Software Quality Assurance Activities (Table A.9):**

| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Compliance Status |
|-----------|-------|---------|---------|------------------|
| Software Quality Assurance Plan | HR | M | M | [Compliant / Non-Compliant] |
| Design reviews | R | HR | HR | [Compliant / Non-Compliant] |
| Code reviews | R | HR | M | [Compliant / Non-Compliant] |
| Software Configuration Management | M | M | M | [Compliant / Non-Compliant] |
| Traceability | R | HR | M | [Compliant / Non-Compliant] |
| Test Management | - | HR | HR | [Compliant / Non-Compliant] |
| Data Recording and Analysis | HR | HR | M | [Compliant / Non-Compliant] |

**Key:**
- M = Mandatory
- HR = Highly Recommended
- R = Recommended
- "-" = No recommendation

### 2.2 Review Checklist

The following checklist items were evaluated during the review:

#### Document Template Compliance (All Document Reviews)

- [ ] Document ID follows format: DOC-TYPE-YYYY-NNN
- [ ] Document Control table present and complete
- [ ] Version history tracked correctly
- [ ] Approvals table present with SIL-appropriate roles
- [ ] EN 50128 references included
- [ ] Document structure follows approved template
- [ ] All mandatory sections present
- [ ] Cross-references correct and up-to-date

#### Code Review Checklist (MANDATORY for all code, all SILs)

**MISRA C Compliance (SIL 2+):**
- [ ] MISRA C:2012 mandatory rules: 0 violations (REQUIRED for SIL 2+)
- [ ] MISRA C:2012 required rules: [N violations] (deviations documented)
- [ ] MISRA C:2012 advisory rules: [N violations] (deviations documented)
- [ ] Static analysis performed (PC-lint, Cppcheck, or equivalent)

**Complexity Limits:**
- [ ] Cyclomatic complexity ≤ 10 (SIL 3-4) OR ≤ 15 (SIL 2) OR ≤ 20 (SIL 0-1)
- [ ] Function length reasonable (< 200 LOC recommended)
- [ ] Nesting depth reasonable (< 5 levels recommended)

**Defensive Programming (HR for SIL 2+, M for SIL 3-4):**
- [ ] All pointer parameters validated (NULL checks)
- [ ] All array accesses bounds-checked
- [ ] All function return values checked
- [ ] All division operations check for zero divisor
- [ ] Integer overflow protection where needed
- [ ] Input parameter validation at function entry
- [ ] Assertions used appropriately

**Memory Management (SIL 2+):**
- [ ] No dynamic memory allocation (no malloc/calloc/realloc/free)
- [ ] Static allocation only
- [ ] Fixed-width integer types used (uint8_t, uint16_t, etc.)
- [ ] No variable-length arrays

**Control Flow:**
- [ ] No recursion (HR for SIL 3-4)
- [ ] No unbounded loops
- [ ] Loop termination guaranteed
- [ ] No unreachable code
- [ ] No dead code

**Error Handling:**
- [ ] All error conditions identified and handled
- [ ] Error codes defined and used consistently
- [ ] Error propagation appropriate
- [ ] Fail-safe behavior implemented where needed

**Coding Style:**
- [ ] Naming conventions followed
- [ ] Indentation consistent
- [ ] Comments adequate and accurate
- [ ] Magic numbers avoided (use named constants)
- [ ] Header file guards present
- [ ] Module structure clear and logical

**Safety and Reliability:**
- [ ] Safety requirements implemented correctly
- [ ] Fault detection mechanisms present (if required)
- [ ] Redundancy implemented correctly (if required)
- [ ] Watchdog patterns correct (if required)

#### Design Review Checklist

**Architecture and Design (EN 50128 Section 7.3):**
- [ ] Modular approach applied (M for SIL 2+)
- [ ] Structured methodology used (M for SIL 3-4)
- [ ] Interfaces fully defined (HR for all SILs)
- [ ] Information encapsulation (HR for SIL 2+)
- [ ] Design complexity manageable
- [ ] Design traceability to requirements

**Defensive Design (HR for SIL 2+):**
- [ ] Input validation designed
- [ ] Error handling strategy defined
- [ ] Fault detection and diagnosis designed (R for SIL 2, HR for SIL 3-4)
- [ ] Fail-safe mechanisms designed

**Performance and Resource Constraints:**
- [ ] Timing constraints identified
- [ ] Memory constraints identified
- [ ] Resource allocation strategy defined
- [ ] Worst-case execution time analysis planned

#### Test Review Checklist

**Test Coverage (SIL-Dependent):**
- [ ] Statement coverage achieved: [X%] (M: 100% for SIL 3-4)
- [ ] Branch coverage achieved: [X%] (M: 100% for SIL 2+)
- [ ] Condition coverage achieved: [X%] (M: 100% for SIL 3-4)
- [ ] Coverage justified if < 100%

**Test Quality:**
- [ ] Test cases trace to requirements
- [ ] Boundary value analysis performed (M for SIL 3-4)
- [ ] Equivalence partitioning applied
- [ ] Negative test cases included
- [ ] Test data selection justified
- [ ] Expected results clearly defined

**Test Documentation:**
- [ ] Test specifications complete
- [ ] Test procedures clear and repeatable
- [ ] Test results documented
- [ ] Test environment documented
- [ ] Defects tracked and resolved

#### Process Compliance Review

**Software Quality Assurance Plan (SQAP) Compliance:**
- [ ] SQAP requirements followed
- [ ] Reviews performed as planned
- [ ] Audits conducted as scheduled
- [ ] Metrics collected and analyzed
- [ ] Non-conformances tracked and resolved

**Configuration Management (EN 50128 Section 6.6):**
- [ ] All items under version control
- [ ] Change control process followed
- [ ] Baselines properly managed
- [ ] Traceability maintained (M for SIL 3-4)

---

## 3. Review Findings

### 3.1 Compliance Summary

| Review Area | Criteria Checked | Criteria Passed | Pass Rate | Status |
|-------------|-----------------|-----------------|-----------|--------|
| Template Compliance | [N] | [N] | [X%] | [Pass/Fail] |
| EN 50128 Compliance | [N] | [N] | [X%] | [Pass/Fail] |
| MISRA C Compliance (SIL 2+) | [N] | [N] | [X%] | [Pass/Fail] |
| Complexity Limits | [N] | [N] | [X%] | [Pass/Fail] |
| Defensive Programming | [N] | [N] | [X%] | [Pass/Fail] |
| Traceability | [N] | [N] | [X%] | [Pass/Fail] |
| Test Coverage (if applicable) | [N] | [N] | [X%] | [Pass/Fail] |
| **Overall** | **[N]** | **[N]** | **[X%]** | **[Pass/Fail]** |

### 3.2 Code Metrics (if applicable)

**Source Code Metrics:**
- Total files reviewed: [N]
- Total lines of code: [N]
- Total functions: [N]
- Average cyclomatic complexity: [X.X]
- Maximum cyclomatic complexity: [N]
- Functions exceeding complexity limit: [N]

**MISRA C Compliance (SIL 2+):**
- Mandatory violations: [N] (MUST be 0 for SIL 2+)
- Required violations: [N]
- Advisory violations: [N]
- Total violations: [N]

**Static Analysis Results:**
- Tool used: [PC-lint Plus / Cppcheck / Clang Analyzer]
- Critical issues: [N]
- Major issues: [N]
- Minor issues: [N]
- Warnings: [N]

### 3.3 Defects and Issues

#### 3.3.1 Critical Defects

**Definition:** Defects that violate EN 50128 mandatory requirements or present safety risks. MUST be fixed before approval.

| Defect ID | Location | Description | EN 50128 Reference | Impact | Resolution Required |
|-----------|----------|-------------|-------------------|--------|-------------------|
| QAR-CRIT-NNN | [File:Line or Document Section] | [Description] | [Section X.Y] | [Safety/Quality] | [Action required] |

#### 3.3.2 Major Defects

**Definition:** Defects that violate highly recommended practices or significantly impact quality. SHOULD be fixed before approval.

| Defect ID | Location | Description | EN 50128 Reference | Impact | Resolution Required |
|-----------|----------|-------------|-------------------|--------|-------------------|
| QAR-MAJ-NNN | [File:Line or Document Section] | [Description] | [Section X.Y] | [Quality] | [Action required] |

#### 3.3.3 Minor Defects

**Definition:** Defects that violate recommended practices but do not significantly impact safety or quality. MAY be deferred.

| Defect ID | Location | Description | EN 50128 Reference | Impact | Resolution Recommended |
|-----------|----------|-------------|-------------------|--------|----------------------|
| QAR-MIN-NNN | [File:Line or Document Section] | [Description] | [Section X.Y] | [Style/Maintainability] | [Action recommended] |

#### 3.3.4 Observations

**Definition:** Areas for improvement that do not constitute defects.

| Observation ID | Location | Description | Recommendation |
|---------------|----------|-------------|----------------|
| QAR-OBS-NNN | [Location] | [Description] | [Recommendation] |

### 3.4 Best Practices Identified

**Positive Findings:**
- [Best practice or exemplary implementation 1]
- [Best practice or exemplary implementation 2]
- [Best practice or exemplary implementation 3]

---

## 4. Detailed Analysis

### 4.1 Template Compliance Analysis (Document Reviews)

**Document Structure:**
- Document ID format: [Correct / Incorrect - specify issue]
- Document Control table: [Complete / Incomplete - specify missing fields]
- Version history: [Adequate / Inadequate - specify issue]
- Approvals table: [Complete with SIL-appropriate roles / Incomplete]
- EN 50128 references: [Present / Missing]

**Content Completeness:**
- All mandatory sections present: [Yes / No - list missing sections]
- Content adequate for SIL level: [Yes / No - specify gaps]
- Technical accuracy: [Verified / Issues found - specify]

### 4.2 MISRA C Analysis (Code Reviews, SIL 2+)

**Static Analysis Tool:** [PC-lint Plus / Cppcheck / Clang Analyzer / Other]  
**Analysis Date:** YYYY-MM-DD

**Violation Summary by Category:**
| MISRA Category | Mandatory | Required | Advisory |
|---------------|-----------|----------|----------|
| Directives | [N] | [N] | [N] |
| Rules | [N] | [N] | [N] |
| **Total** | **[N]** | **[N]** | **[N]** |

**Critical MISRA Violations (if any):**
| Rule | Severity | Location | Description | Action Required |
|------|----------|----------|-------------|----------------|
| [Rule X.Y] | Mandatory | [File:Line] | [Description] | [Fix / Deviation (with justification)] |

**SIL 2+ Compliance:** [PASS - 0 mandatory violations | FAIL - N mandatory violations]

### 4.3 Complexity Analysis

**Cyclomatic Complexity Report:**
| Module/Function | Complexity | Limit | Status | Action Required |
|-----------------|-----------|-------|--------|----------------|
| [function_name()] | [N] | [10/15/20 based on SIL] | [Pass/Fail] | [Refactor if failed] |

**Functions Exceeding Complexity Limit:** [N]

**Recommendation:** [All functions within limits / Refactoring required for N functions]

### 4.4 Defensive Programming Analysis

**Input Validation:**
- Functions with pointer parameters: [N]
- Functions with NULL checks: [N] ([X%])
- Missing NULL checks: [N] (MUST be 0 for SIL 2+)

**Return Value Checking:**
- Function calls that return error codes: [N]
- Calls with return value checked: [N] ([X%])
- Unchecked return values: [N] (MUST be 0 for SIL 2+)

**Bounds Checking:**
- Array accesses: [N]
- Bounds-checked accesses: [N] ([X%])
- Potentially unsafe accesses: [N]

**Overflow Protection:**
- Arithmetic operations with overflow risk: [N]
- Operations with overflow protection: [N] ([X%])
- Unprotected operations: [N]

### 4.5 Traceability Analysis (SIL 3-4 Mandatory)

**Requirements Traceability:**
- Total requirements: [N]
- Requirements traced to design: [N] ([X%])
- Requirements traced to code: [N] ([X%])
- Requirements traced to tests: [N] ([X%])
- Orphaned requirements: [N] (MUST be 0 for SIL 3-4)

**Backward Traceability:**
- Design elements without requirement traceability: [N]
- Code modules without requirement traceability: [N]
- Test cases without requirement traceability: [N]

**Traceability Compliance:** [PASS | FAIL - specify gaps]

### 4.6 Test Coverage Analysis (if applicable)

**Coverage Metrics:**
- Statement coverage: [X%] (Target: 100% for SIL 3-4)
- Branch coverage: [X%] (Target: 100% for SIL 2+)
- Condition coverage: [X%] (Target: 100% for SIL 3-4)

**Uncovered Code Analysis:**
- Uncovered statements: [N lines]
- Uncovered branches: [N branches]
- Justification provided: [Yes / No]
- Justification adequate: [Yes / No]

**Coverage Compliance:** [PASS | FAIL - specify gaps]

---

## 5. Review Conclusions

### 5.1 Overall Assessment

**Review Result:** [Pass | Pass with Minor Issues | Fail - Rework Required]

**Summary:**
[Provide overall assessment of artifact quality, EN 50128 compliance, and SIL-appropriate practices]

**Compliance Assessment:**
- EN 50128 compliance: [Compliant | Non-Compliant - specify violations]
- SIL-specific requirements: [Met | Not Met - specify gaps]
- MISRA C compliance (SIL 2+): [Compliant - 0 mandatory violations | Non-Compliant - N violations]
- Complexity limits: [Met | Exceeded - N functions over limit]
- Defensive programming: [Adequate | Inadequate - specify gaps]
- Traceability (SIL 3-4): [Complete | Incomplete - specify gaps]

### 5.2 Approval Decision

**Decision:** [Approve | Approve with Conditions | Reject - Require Rework]

**Rationale:**
[Explain decision based on findings]

**Conditions for Approval (if applicable):**
1. [Condition 1 - must be resolved before final approval]
2. [Condition 2 - must be resolved before final approval]

**Rejection Rationale (if applicable):**
[Explain why rework is required - typically due to critical or major defects]

### 5.3 Recommendations

**Immediate Actions (Required for Approval):**
1. [Action 1 - fix critical defects]
2. [Action 2 - fix critical defects]

**Short-term Actions (Recommended):**
1. [Action 1 - address major defects]
2. [Action 2 - address major defects]

**Long-term Improvements (Process/Quality):**
1. [Improvement 1]
2. [Improvement 2]

---

## 6. Follow-Up Actions

### 6.1 Corrective Action Plan

| Defect ID | Corrective Action | Responsible | Target Date | Status |
|-----------|------------------|-------------|-------------|--------|
| [QAR-XXX-NNN] | [Action description] | [Name] | YYYY-MM-DD | [Open/In Progress/Closed] |

### 6.2 Re-Review Requirements

**Re-Review Required:** [Yes / No]

**Re-Review Scope:**
- [ ] Full re-review
- [ ] Partial re-review (corrected items only)
- [ ] Desktop review (no meeting required)

**Re-Review Date:** YYYY-MM-DD (if applicable)

### 6.3 Lessons Learned

**What went well:**
- [Observation 1]
- [Observation 2]

**What could be improved:**
- [Observation 1]
- [Observation 2]

**Recommendations for future reviews:**
- [Recommendation 1]
- [Recommendation 2]

---

## EN 50128 References

- **Section 6.5:** Software Quality Assurance
- **Table A.9:** Software Quality Assurance techniques
- **Section 7.4.2:** Code reviews and inspections
- **Table A.4:** Software Design and Implementation techniques
- **Table A.12:** Design and Coding Standards

## EN 50126 RAMS References

- **Section 9:** Quality management in RAMS lifecycle

---

## Appendices

### Appendix A: Review Checklist (Complete)

[Attach complete review checklist with all items marked]

### Appendix B: Static Analysis Report

[Attach full static analysis report from PC-lint/Cppcheck/Clang]

### Appendix C: Complexity Report

[Attach full complexity analysis report from Lizard or equivalent tool]

### Appendix D: Coverage Report (if applicable)

[Attach coverage report from gcov/lcov or equivalent]

### Appendix E: Evidence

[Attach supporting evidence: code snippets, document screenshots, etc.]

---

**Template Version:** 1.0  
**EN 50128:2011 Compliance:** Section 6.5, Table A.9  
**Skill Owner:** Quality Assurance (`/qua`)
