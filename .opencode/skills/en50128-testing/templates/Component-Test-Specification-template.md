# Component Test Specification

**Document ID**: DOC-COMPTEST-YYYY-NNN  
**Version**: 1.0  
**Date**: YYYY-MM-DD  
**Project**: [Project Name]  
**SIL Level**: [0, 1, 2, 3, or 4]  
**Author**: Tester (TST)  
**Status**: Approved

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-COMPTEST-YYYY-NNN |
| **Version** | 1.0 |
| **Date** | YYYY-MM-DD |
| **Project** | [Project Name] |
| **SIL Level** | [0, 1, 2, 3, or 4] |
| **Author** | Tester (TST) |
| **Reviewer** | [Name, Role] |
| **Approver** | [Name], QA Manager |
| **Status** | Approved |

---

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | YYYY-MM-DD | TST | Initial draft | - |
| 1.0 | YYYY-MM-DD | TST | First approved version | QA Manager |

---

## APPROVALS

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author (Tester)** | [Name] | | YYYY-MM-DD |
| **Reviewer** | [Name] | | YYYY-MM-DD |
| **QA Manager** | [Name] | | YYYY-MM-DD |
| **Verifier** (SIL 3-4) | [Name] | | YYYY-MM-DD |

---

## 1. INTRODUCTION

### 1.1 Purpose

This Component Test Specification defines the unit tests for **[Project Name]** software components in accordance with EN 50128:2011 Section 7.4 and 7.5.

**Objectives**:
- Define component-level test cases for all software modules
- Specify test procedures and expected results
- Define code coverage targets per SIL level
- Ensure all requirements are testable at component level

**EN 50128 Reference**: Section 7.4.4.8 (Component Testing), Section 7.5 (Integration)

### 1.2 Scope

**Components Under Test**:
- Module 1: [Module name] - [N] functions
- Module 2: [Module name] - [N] functions
- Module 3: [Module name] - [N] functions

**Test Types**:
- Unit tests (white-box testing)
- Boundary value testing
- Equivalence class testing
- Error handling testing
- Fault injection testing (SIL 3-4)

**Out of Scope**:
- Integration testing (covered in Integration Test Specification)
- System testing (covered in Overall Software Test Specification)
- Hardware testing (covered by hardware test plans)

### 1.3 Test Strategy

**Test Framework**: [Unity / CUnit / Google Test / etc.]

**Test Approach**: [Black-box / White-box / Both]

**Coverage Targets** (per SIL level):
- **SIL 0-1**: Statement (HR), Branch (HR)
- **SIL 2**: Statement (HR), Branch (**M**)
- **SIL 3-4**: Statement (**M**), Branch (**M**), Condition (**M**)

**Coverage Target**: [X]% statement, [Y]% branch, [Z]% condition (per SIL [N] requirements)

**Test Environment**:
- **Host**: [Host development machine with test framework]
- **Target**: [Target embedded system / simulator]
- **Tools**: [gcc, gcov, lcov, test harness]

### 1.4 References

| Reference | Document |
|-----------|----------|
| **[SRS]** | Software Requirements Specification, DOC-SRS-YYYY-NNN |
| **[SDS]** | Software Design Specification, DOC-SDS-YYYY-NNN |
| **[SAS]** | Software Architecture Specification, DOC-SAS-YYYY-NNN |
| **[SVP]** | Software Verification Plan, DOC-SVP-YYYY-NNN |
| **[EN50128]** | EN 50128:2011 Section 7.4, 7.5 |

---

## 2. TEST ORGANIZATION

### 2.1 Test Naming Convention

**Test Case ID Format**: `TC-[MODULE]-[FUNCTION]-[NUM]`

**Example**: `TC-MOD001-init-001` = Test case 1 for init() function in MOD-001

**Test Suite Organization**:
- One test suite per module
- Test suites named: `test_[module_name].c`
- Test cases grouped by function

### 2.2 Test Data

**Test Data Location**: `tests/data/`

**Test Data Types**:
- Valid input data (normal cases)
- Boundary values (min, max, zero, overflow)
- Invalid input data (error cases)
- Extreme values (stress testing)

### 2.3 Test Execution Order

**Order**: [Sequential / Independent / Randomized]

**Dependencies**: [List any test dependencies or required execution order]

**Setup/Teardown**: [Describe common setup and teardown procedures]

---

## 3. COMPONENT TEST CASES

### 3.1 Module: [MOD-001] - [Module Name]

**Module Description**: [Brief description of module functionality]

**Requirements Covered**: [REQ-FUNC-001, REQ-FUNC-002, REQ-SAFE-001]

**Functions Under Test**: [List of functions]

---

#### 3.1.1 Function: `[function_name]()`

**Function Signature**: `[return_type] [function_name]([parameters])`

**Requirements**: [REQ-IDs that this function implements]

**Test Cases**:

---

##### TC-MOD001-[FUNC]-001: [Test Case Title]

**Objective**: [What this test verifies]

**Requirement**: [REQ-ID]

**Test Type**: [Normal / Boundary / Error / Fault Injection]

**Priority**: [High / Medium / Low]

**Preconditions**:
- [Precondition 1]
- [Precondition 2]

**Test Steps**:
1. [Step 1]
2. [Step 2]
3. [Step 3]

**Test Inputs**:
```c
// Input parameter values
param1 = [value];
param2 = [value];
```

**Expected Result**:
```c
// Expected return value
return_value == [expected_value]

// Expected state changes
state_variable == [expected_state]
```

**Pass Criteria**:
- Return value matches expected value
- [Additional pass criteria]

**Coverage**: [Statement: X%, Branch: Y%, Condition: Z%]

---

##### TC-MOD001-[FUNC]-002: Boundary Test - Minimum Value

**Objective**: Verify function behavior at minimum boundary

**Requirement**: [REQ-ID]

**Test Type**: Boundary

**Priority**: High

**Test Inputs**:
```c
param1 = MIN_VALUE;  // e.g., 0, INT_MIN
```

**Expected Result**:
- Function returns success or appropriate error code
- No buffer overflow or underflow
- State remains consistent

---

##### TC-MOD001-[FUNC]-003: Boundary Test - Maximum Value

**Objective**: Verify function behavior at maximum boundary

**Requirement**: [REQ-ID]

**Test Type**: Boundary

**Priority**: High

**Test Inputs**:
```c
param1 = MAX_VALUE;  // e.g., UINT32_MAX
```

**Expected Result**:
- Function handles maximum value correctly
- No integer overflow
- Proper saturation or error handling

---

##### TC-MOD001-[FUNC]-004: Error Handling - NULL Pointer

**Objective**: Verify defensive programming - NULL pointer check

**Requirement**: [REQ-IMPL-006] (Defensive programming)

**Test Type**: Error

**Priority**: High (SIL 3-4 mandatory)

**Test Inputs**:
```c
pointer_param = NULL;
```

**Expected Result**:
```c
return_value == ERROR_NULL_POINTER;
// Function does NOT crash
// No side effects
```

---

##### TC-MOD001-[FUNC]-005: Error Handling - Invalid Parameter

**Objective**: Verify parameter validation

**Requirement**: [REQ-ID]

**Test Type**: Error

**Priority**: High

**Test Inputs**:
```c
param1 = INVALID_VALUE;  // e.g., -1, out of range
```

**Expected Result**:
```c
return_value == ERROR_INVALID_PARAMETER;
// State unchanged
```

---

##### TC-MOD001-[FUNC]-006: Fault Injection - Simulated Sensor Failure

**Objective**: Verify fault handling (SIL 3-4)

**Requirement**: [REQ-SAFE-XXX]

**Test Type**: Fault Injection

**Priority**: High (SIL 3-4)

**Fault Injected**: Sensor returns out-of-range value

**Test Inputs**:
```c
sensor_value = OUT_OF_RANGE;  // Simulated fault
```

**Expected Result**:
- Function detects fault
- Enters safe state or degraded mode
- Returns appropriate error code
- No unsafe behavior

---

[Repeat test case structure for all functions in module]

---

### 3.2 Module: [MOD-002] - [Module Name]

[Repeat structure for next module]

---

## 4. TEST COVERAGE ANALYSIS

### 4.1 Coverage Requirements

**EN 50128 Table A.21 - Test Coverage for Code**:

| SIL Level | Statement Coverage | Branch Coverage | Condition Coverage |
|-----------|-------------------|-----------------|-------------------|
| SIL 0-1 | HR | HR | - |
| SIL 2 | HR | **M** (Mandatory) | - |
| SIL 3-4 | **M** | **M** | **M** |

**Project Target** (SIL [X]):
- Statement coverage: [X]% (target: [Y]%)
- Branch coverage: [X]% (target: [Y]%)
- Condition coverage: [X]% (target: [Y]%) (SIL 3-4 only)

### 4.2 Coverage Measurement

**Tool**: gcov + lcov (or alternative)

**Measurement Procedure**:
1. Compile with coverage instrumentation (`-fprofile-arcs -ftest-coverage`)
2. Execute all test cases
3. Generate coverage report (`gcov`, `lcov`)
4. Analyze uncovered code
5. Add tests or justify uncoverable code

**Coverage Report Location**: `tests/coverage/`

### 4.3 Uncoverable Code Justification

**Uncoverable Code** (if any):
- Defensive error checks that cannot be triggered
- Hardware fault conditions not simulatable
- Dead code removed by optimizer

**Justification**: [For each uncovered line, provide justification]

---

## 5. TEST EXECUTION PLAN

### 5.1 Test Execution Schedule

| Module | Test Suite | Test Cases | Priority | Planned Execution | Responsible |
|--------|------------|-----------|----------|------------------|-------------|
| MOD-001 | test_mod001.c | [N] | High | [Date] | [Name] |
| MOD-002 | test_mod002.c | [N] | High | [Date] | [Name] |

### 5.2 Test Environment Setup

**Build Configuration**:
```bash
# Build with test framework
make test

# Build with coverage instrumentation
make coverage
```

**Test Execution**:
```bash
# Run all component tests
./run_component_tests.sh

# Generate coverage report
./generate_coverage.sh
```

**Required Tools**:
- gcc (with coverage support)
- Unity test framework (or alternative)
- gcov / lcov
- make

### 5.3 Test Data Preparation

**Test Data Sources**:
- [Source 1: Manual test data]
- [Source 2: Generated test data]
- [Source 3: Real operational data]

**Test Data Validation**: [How test data is validated]

---

## 6. TEST TRACEABILITY

### 6.1 Requirements to Test Case Traceability

| Requirement ID | Description | Test Cases | Coverage |
|---------------|-------------|-----------|----------|
| REQ-FUNC-001 | [Description] | TC-MOD001-func-001, TC-MOD001-func-002 | 100% |
| REQ-FUNC-002 | [Description] | TC-MOD002-func-001 | 100% |
| REQ-SAFE-001 | [Description] | TC-MOD001-func-006, TC-MOD003-func-005 | 100% |

**Traceability Summary**:
- Total requirements: [N]
- Requirements with test cases: [N] ([X]%)
- Requirements without test cases: [N] (justify)

### 6.2 Test Cases to Requirements Traceability

| Test Case ID | Requirements Covered | Module | Priority |
|--------------|---------------------|--------|----------|
| TC-MOD001-init-001 | REQ-FUNC-001 | MOD-001 | High |
| TC-MOD001-init-002 | REQ-FUNC-001, REQ-IMPL-006 | MOD-001 | High |

---

## 7. TEST PASS/FAIL CRITERIA

### 7.1 Individual Test Case Criteria

**Pass**:
- All expected results match actual results
- No unexpected errors or warnings
- No memory leaks (checked with valgrind or similar)
- No undefined behavior (checked with sanitizers)

**Fail**:
- Any expected result does not match actual result
- Unexpected errors or crashes
- Memory corruption detected
- Timing violations (if applicable)

### 7.2 Module Test Suite Criteria

**Pass**:
- All test cases in suite pass
- Coverage targets met for module
- No open defects related to module

**Fail**:
- One or more test cases fail
- Coverage targets not met
- Open critical defects

### 7.3 Overall Component Testing Criteria

**Pass** (ready for integration):
- All module test suites pass
- Overall coverage targets met (statement, branch, condition per SIL)
- All requirements traced to passing test cases
- No open safety-critical defects
- Independent verification performed (SIL 3-4)

**Fail**:
- Any module test suite fails
- Coverage targets not met
- Requirements without test coverage
- Open safety-critical defects

---

## 8. DEFECT MANAGEMENT

### 8.1 Defect Reporting

**Defect Log**: `tests/defects.md` or issue tracking system

**Defect Severity Levels**:
- **Critical**: Safety-critical failure, system crash, data corruption
- **High**: Functional failure, incorrect result
- **Medium**: Minor functional issue, edge case failure
- **Low**: Cosmetic issue, typo, non-functional

### 8.2 Defect Triage

**Triage Process**:
1. Defect reported by tester
2. Severity assigned
3. Developer investigates root cause
4. Fix implemented
5. Re-test performed
6. Defect closed if re-test passes

**Defect Closure Criteria**:
- Fix verified by re-running failing test case
- Regression testing performed
- No new defects introduced

---

## 9. TEST AUTOMATION

### 9.1 Automated Test Execution

**Test Harness**: [Description of test automation framework]

**Continuous Integration**:
- Tests run automatically on each commit (if CI/CD pipeline exists)
- Coverage reports generated automatically
- Test results emailed to team

**Automation Scripts**:
- `run_component_tests.sh` - Run all component tests
- `generate_coverage.sh` - Generate coverage report
- `check_coverage_targets.sh` - Verify coverage meets SIL targets

### 9.2 Test Reporting

**Report Format**: [JUnit XML / HTML / PDF]

**Report Location**: `tests/reports/`

**Report Contents**:
- Test execution summary (pass/fail counts)
- Coverage metrics
- Failed test details
- Defect summary

---

## APPENDIX A: TEST CASE SUMMARY TABLE

| Test Case ID | Module | Function | Requirement | Type | Priority | Status |
|--------------|--------|----------|-------------|------|----------|--------|
| TC-MOD001-init-001 | MOD-001 | init() | REQ-FUNC-001 | Normal | High | Not Run |
| TC-MOD001-init-002 | MOD-001 | init() | REQ-FUNC-001 | Boundary | High | Not Run |

**Total Test Cases**: [N]

---

## APPENDIX B: TEST DATA REPOSITORY

**Test Data Files**:
- `tests/data/valid_inputs.csv` - Valid input test data
- `tests/data/boundary_values.csv` - Boundary test data
- `tests/data/invalid_inputs.csv` - Error case test data

---

## APPENDIX C: REVISION HISTORY

| Date | Version | Author | Changes | Approval |
|------|---------|--------|---------|----------|
| YYYY-MM-DD | 0.1 | TST | Initial draft | - |
| YYYY-MM-DD | 1.0 | TST | Approved version | QA Manager |

---

**END OF COMPONENT TEST SPECIFICATION**
