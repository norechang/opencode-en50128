# Component Test Report

**Document ID**: DOC-COMPTESTREP-YYYY-NNN  
**Version**: 1.0  
**Date**: YYYY-MM-DD  
**Project**: [Project Name]  
**SIL Level**: [0, 1, 2, 3, or 4]  
**Author**: Tester (TST)  
**Status**: Final

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-COMPTESTREP-YYYY-NNN |
| **Version** | 1.0 |
| **Date** | YYYY-MM-DD |
| **Project** | [Project Name] |
| **SIL Level** | [0, 1, 2, 3, or 4] |
| **Author** | Tester (TST) |
| **Reviewer** | [Name, Role] |
| **Approver** | [Name], QA Manager |
| **Status** | Final |

---

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | YYYY-MM-DD | TST | Initial test results | - |
| 1.0 | YYYY-MM-DD | TST | Final test report | QA Manager |

---

## APPROVALS

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author (Tester)** | [Name] | | YYYY-MM-DD |
| **Reviewer** | [Name] | | YYYY-MM-DD |
| **QA Manager** | [Name] | | YYYY-MM-DD |
| **Verifier** (SIL 3-4) | [Name] | | YYYY-MM-DD |

---

## 1. EXECUTIVE SUMMARY

### 1.1 Test Summary

**Test Specification**: Component Test Specification (DOC-COMPTEST-YYYY-NNN)

**Test Execution Period**: [Start Date] to [End Date] ([N] days)

**Test Result**: **[PASS / FAIL]**

**Overall Status**:
- **Test Cases Executed**: [N] of [Total] ([X]%)
- **Test Cases Passed**: [N] ([X]%)
- **Test Cases Failed**: [N] ([X]%)
- **Test Cases Blocked**: [N] ([X]%)
- **Coverage Achieved**: Statement [X]%, Branch [Y]%, Condition [Z]%
- **Coverage Target Met**: [YES / NO]
- **Defects Found**: [N] (Critical: [N], High: [N], Medium: [N], Low: [N])
- **Open Defects**: [N] (0 required for PASS)

**Recommendation**: [APPROVE FOR INTEGRATION / REWORK REQUIRED]

---

## 2. INTRODUCTION

### 2.1 Purpose

This Component Test Report documents the execution and results of component (unit) testing for **[Project Name]** in accordance with EN 50128:2011 Section 7.4 and 7.5.

**Objectives**:
- Report test execution results for all component test cases
- Document code coverage achieved
- Report defects found and their status
- Provide pass/fail assessment for each module
- Support verification and validation activities

### 2.2 Scope

**Components Tested**:
- Module 1: [Module name] - [N] functions
- Module 2: [Module name] - [N] functions
- Module 3: [Module name] - [N] functions

**Test Types Executed**:
- Unit tests (white-box testing)
- Boundary value testing
- Equivalence class testing
- Error handling testing
- Fault injection testing (SIL 3-4)

### 2.3 Test Environment

**Test Configuration**:
- **Host System**: [OS, version]
- **Compiler**: [gcc version X.Y.Z]
- **Test Framework**: [Unity / CUnit / Google Test]
- **Coverage Tool**: [gcov / lcov / Bullseye]
- **Build Date**: [YYYY-MM-DD]
- **Software Version**: [X.Y.Z]

**Test Tools**:
- Test framework: [Name and version]
- Coverage tool: [Name and version]
- Memory checker: [valgrind / AddressSanitizer]
- Static analyzer: [cppcheck / PC-lint]

### 2.4 References

| Reference | Document |
|-----------|----------|
| **[COMPTEST]** | Component Test Specification, DOC-COMPTEST-YYYY-NNN |
| **[SRS]** | Software Requirements Specification, DOC-SRS-YYYY-NNN |
| **[SDS]** | Software Design Specification, DOC-SDS-YYYY-NNN |
| **[SVP]** | Software Verification Plan, DOC-SVP-YYYY-NNN |

---

## 3. TEST EXECUTION SUMMARY

### 3.1 Test Execution Overview

| Module | Test Suite | Test Cases | Executed | Passed | Failed | Blocked | Pass Rate |
|--------|------------|-----------|----------|--------|--------|---------|-----------|
| MOD-001 | test_mod001.c | [N] | [N] | [N] | [N] | [N] | [X]% |
| MOD-002 | test_mod002.c | [N] | [N] | [N] | [N] | [N] | [X]% |
| MOD-003 | test_mod003.c | [N] | [N] | [N] | [N] | [N] | [X]% |
| **TOTAL** | - | **[N]** | **[N]** | **[N]** | **[N]** | **[N]** | **[X]%** |

**Execution Status**:
- ✅ **PASS**: All test cases passed
- ❌ **FAIL**: One or more test cases failed
- ⚠️ **BLOCKED**: Test could not be executed (environment issue, dependency)

### 3.2 Test Execution Timeline

| Date | Activity | Modules Tested | Tests Executed | Defects Found |
|------|----------|---------------|----------------|---------------|
| YYYY-MM-DD | Initial test run | MOD-001, MOD-002 | [N] | [N] |
| YYYY-MM-DD | Re-test after fixes | MOD-001 | [N] | [N] |
| YYYY-MM-DD | Final test run | All modules | [N] | [N] |

---

## 4. TEST RESULTS BY MODULE

### 4.1 Module: [MOD-001] - [Module Name]

**Module Description**: [Brief description]

**Test Suite**: test_mod001.c

**Test Summary**:
- Total test cases: [N]
- Executed: [N]
- Passed: [N] ([X]%)
- Failed: [N]
- Blocked: [N]

**Module Result**: [PASS / FAIL]

---

#### 4.1.1 Test Case Results

##### TC-MOD001-init-001: [Test Case Title]

**Requirement**: [REQ-ID]

**Execution Date**: YYYY-MM-DD

**Test Input**:
```c
param1 = [value];
param2 = [value];
```

**Expected Result**:
```c
return_value == SUCCESS
state == INITIALIZED
```

**Actual Result**:
```c
return_value == SUCCESS
state == INITIALIZED
```

**Result**: ✅ **PASS**

**Notes**: [Any observations or notes]

---

##### TC-MOD001-init-002: Boundary Test - NULL Pointer

**Requirement**: [REQ-IMPL-006]

**Execution Date**: YYYY-MM-DD

**Test Input**:
```c
pointer_param = NULL;
```

**Expected Result**:
```c
return_value == ERROR_NULL_POINTER
// No crash, defensive check working
```

**Actual Result**:
```c
return_value == ERROR_NULL_POINTER
// Defensive check working correctly
```

**Result**: ✅ **PASS**

**Notes**: Defensive programming verified

---

##### TC-MOD001-func-005: Error Handling Test - FAILED

**Requirement**: [REQ-FUNC-002]

**Execution Date**: YYYY-MM-DD

**Test Input**:
```c
param1 = INVALID_VALUE;
```

**Expected Result**:
```c
return_value == ERROR_INVALID_PARAMETER
```

**Actual Result**:
```c
return_value == SUCCESS  // INCORRECT!
// Parameter validation missing
```

**Result**: ❌ **FAIL**

**Defect**: DEF-001 - Missing parameter validation

**Resolution**: Fix implemented, re-test scheduled

---

[Repeat for all test cases]

---

### 4.2 Module: [MOD-002] - [Module Name]

[Repeat structure for next module]

---

## 5. CODE COVERAGE ANALYSIS

### 5.1 Coverage Summary

**Coverage Requirements** (SIL [X]):
- Statement coverage: ≥ [Y]%
- Branch coverage: ≥ [Z]%
- Condition coverage: ≥ [W]% (SIL 3-4 only)

**Coverage Achieved**:

| Module | Statement | Branch | Condition | Status |
|--------|-----------|--------|-----------|--------|
| MOD-001 | [X]% | [Y]% | [Z]% | [PASS/FAIL] |
| MOD-002 | [X]% | [Y]% | [Z]% | [PASS/FAIL] |
| MOD-003 | [X]% | [Y]% | [Z]% | [PASS/FAIL] |
| **Overall** | **[X]%** | **[Y]%** | **[Z]%** | **[PASS/FAIL]** |

**Coverage Target Met**: [YES / NO]

**Coverage Report**: `tests/coverage/index.html`

---

### 5.2 Uncovered Code Analysis

**Uncovered Lines**: [N] lines uncovered

| Module | Function | Lines | Reason | Justification |
|--------|----------|-------|--------|---------------|
| MOD-001 | func_name() | 123-125 | Unreachable error path | Defensive check for hardware fault that cannot be simulated |
| MOD-002 | func_name() | 456 | Dead code | Removed in future iteration |

**Coverage Waivers**: [List any approved waivers for uncovered code]

**Assessment**: [All uncovered code justified / Additional tests required]

---

### 5.3 Coverage Metrics by Function

**Functions with <100% Coverage**:

| Module | Function | Statement | Branch | Condition | Missing Coverage |
|--------|----------|-----------|--------|-----------|------------------|
| MOD-001 | func_a() | 95% | 90% | 88% | Error path line 123 |
| MOD-002 | func_b() | 98% | 100% | 100% | Unreachable defensive check |

---

## 6. DEFECT SUMMARY

### 6.1 Defects Found

**Total Defects**: [N]

| Defect ID | Severity | Description | Module | Test Case | Status | Resolution |
|-----------|----------|-------------|--------|-----------|--------|------------|
| DEF-001 | Critical | Missing NULL check | MOD-001 | TC-MOD001-init-002 | Fixed | Added NULL check, re-test passed |
| DEF-002 | High | Off-by-one error | MOD-002 | TC-MOD002-func-003 | Fixed | Corrected loop condition |
| DEF-003 | Medium | Incorrect error code | MOD-003 | TC-MOD003-func-005 | Fixed | Updated return value |
| DEF-004 | Low | Typo in comment | MOD-001 | - | Fixed | Comment corrected |

**Defect Status Summary**:
- **Open**: [N]
- **Fixed (Re-test Passed)**: [N]
- **Fixed (Re-test Pending)**: [N]
- **Closed**: [N]
- **Deferred**: [N] (with justification)

**Safety-Critical Defects**: [N] (0 required for deployment)

---

### 6.2 Defect Analysis

**Defect by Severity**:
- **Critical**: [N] (safety-critical failure, crash, data corruption)
- **High**: [N] (functional failure, incorrect result)
- **Medium**: [N] (minor functional issue, edge case)
- **Low**: [N] (cosmetic, non-functional)

**Defect by Root Cause**:
- **Coding error**: [N]
- **Logic error**: [N]
- **Missing requirement**: [N]
- **Test specification error**: [N]
- **Environment issue**: [N]

**Defect Trends**: [Analysis of defect trends, lessons learned]

---

### 6.3 Re-Test Results

**Defects Re-Tested**:

| Defect ID | Original Test | Re-Test Date | Re-Test Result | Status |
|-----------|--------------|--------------|----------------|--------|
| DEF-001 | TC-MOD001-init-002 | YYYY-MM-DD | PASS | Closed |
| DEF-002 | TC-MOD002-func-003 | YYYY-MM-DD | PASS | Closed |
| DEF-003 | TC-MOD003-func-005 | YYYY-MM-DD | PASS | Closed |

**Regression Testing**: [N] regression tests performed, [N] passed

---

## 7. TRACEABILITY ANALYSIS

### 7.1 Requirements Coverage

**Requirements Traceability**:

| Requirement ID | Test Cases | Execution Status | Result | Coverage |
|---------------|-----------|------------------|--------|----------|
| REQ-FUNC-001 | TC-MOD001-init-001, TC-MOD001-init-002 | Executed | PASS | 100% |
| REQ-FUNC-002 | TC-MOD002-func-001 | Executed | PASS | 100% |
| REQ-SAFE-001 | TC-MOD001-func-006, TC-MOD003-func-005 | Executed | PASS | 100% |

**Requirements Coverage Summary**:
- Total requirements: [N]
- Requirements tested: [N] ([X]%)
- Requirements passed: [N] ([X]%)
- Requirements failed: [N]
- Requirements not tested: [N] (justify)

**Traceability Status**: [100% requirements covered / Gaps exist]

---

### 7.2 Test Case to Requirements Traceability

**Orphaned Test Cases** (no requirement):
- [List test cases not linked to requirements, with justification]

**Missing Test Cases** (requirement not tested):
- [List requirements without test cases, with justification]

---

## 8. QUALITY METRICS

### 8.1 Test Efficiency Metrics

| Metric | Value | Target | Status |
|--------|-------|--------|--------|
| Test Execution Time | [N] hours | [Target] | [On time / Delayed] |
| Defect Detection Rate | [N] defects / [M] KLOC | Industry average: 10-50 | [Good / Poor] |
| Test Case Pass Rate | [X]% | >95% | [Good / Poor] |
| Re-test Pass Rate | [X]% | 100% | [Good / Poor] |
| Coverage Achievement | [X]% | [Target]% | [Met / Not met] |

### 8.2 Code Quality Metrics

| Metric | Value | Target | Status |
|--------|-------|--------|--------|
| Cyclomatic Complexity (max) | [N] | ≤10 (SIL 3-4) | [Pass / Fail] |
| MISRA C Violations | [N] | 0 mandatory | [Pass / Fail] |
| Static Analysis Warnings | [N] | 0 critical | [Pass / Fail] |
| Memory Leaks | [N] | 0 | [Pass / Fail] |

---

## 9. PASS/FAIL ASSESSMENT

### 9.1 Module Assessment

| Module | Test Cases | Pass Rate | Coverage | Defects | Status |
|--------|-----------|-----------|----------|---------|--------|
| MOD-001 | [N] | [X]% | Statement: [Y]%, Branch: [Z]% | [N] open | [PASS/FAIL] |
| MOD-002 | [N] | [X]% | Statement: [Y]%, Branch: [Z]% | [N] open | [PASS/FAIL] |
| **Overall** | **[N]** | **[X]%** | **Statement: [Y]%, Branch: [Z]%** | **[N] open** | **[PASS/FAIL]** |

### 9.2 Overall Assessment

**Component Testing Result**: **[PASS / FAIL]**

**Pass Criteria**:
- ✅ All test cases executed
- ✅ Pass rate ≥ 95%
- ✅ Coverage targets met (statement, branch, condition per SIL)
- ✅ All requirements traced and tested
- ✅ No open safety-critical defects
- ✅ All critical/high defects fixed and re-tested
- ✅ Independent verification performed (SIL 3-4)

**Criteria Met**: [YES / NO]

**Outstanding Issues**:
1. [Issue 1] - [Resolution plan]
2. [Issue 2] - [Resolution plan]

---

## 10. RECOMMENDATIONS

### 10.1 Recommendation for Integration

**Recommendation**: **[APPROVE FOR INTEGRATION / REWORK REQUIRED]**

**Justification**:
- [Rationale for recommendation]
- [Summary of test results]
- [Risk assessment]

**Conditions** (if conditional approval):
1. [Condition 1] - Target resolution: [Date]
2. [Condition 2] - Target resolution: [Date]

### 10.2 Recommendations for Improvement

**Process Improvements**:
1. [Recommendation 1]
2. [Recommendation 2]

**Testing Improvements**:
1. [Recommendation 1]
2. [Recommendation 2]

**Code Quality Improvements**:
1. [Recommendation 1]
2. [Recommendation 2]

---

## 11. LESSONS LEARNED

**What Went Well**:
- [Item 1]
- [Item 2]

**What Could Be Improved**:
- [Item 1]
- [Item 2]

**Actions for Future Testing**:
- [Action 1]
- [Action 2]

---

## APPENDIX A: DETAILED TEST RESULTS

**Complete Test Execution Log**: `tests/logs/test_execution_[date].log`

**Coverage Report**: `tests/coverage/index.html`

**Defect Log**: `tests/defects.md`

---

## APPENDIX B: TEST METRICS CHARTS

[Include charts if available:]
- Test execution trend (pass/fail over time)
- Coverage trend (coverage percentage over time)
- Defect discovery rate
- Defect resolution rate

---

## APPENDIX C: TEST ARTIFACTS

**Test Artifacts Location**: `tests/artifacts/`

**Artifacts**:
- Test execution logs
- Coverage reports (HTML, XML)
- Memory check reports (valgrind output)
- Static analysis reports
- Test data files
- Screenshots (if applicable)

---

## APPENDIX D: REVISION HISTORY

| Date | Version | Author | Changes | Approval |
|------|---------|--------|---------|----------|
| YYYY-MM-DD | 0.1 | TST | Initial test results | - |
| YYYY-MM-DD | 1.0 | TST | Final report | QA Manager |

---

**END OF COMPONENT TEST REPORT**
