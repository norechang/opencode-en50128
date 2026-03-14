# Test and Verification Documentation Workflow

**EN 50128 Reference**: Sections 6.1.4.4 (Test Specification), 6.1.4.5 (Test Report), 6.2.4 (Verification Report), Table A.21 (Test Coverage)  
**Lifecycle Phase**: Phase 4 (Component Testing), Phase 5 (Integration), Phase 6 (Validation), Verification (All Phases)  
**SIL Applicability**: All (0, 1, 2, 3, 4) - Requirements vary by SIL  
**Version**: 1.0

---

## Table of Contents

1. [EN 50128 Test and Verification Documentation Requirements](#1-en-50128-test-and-verification-documentation-requirements)
2. [Test Documentation Structure](#2-test-documentation-structure)
3. [Test Specification Structure](#3-test-specification-structure)
4. [Test Report Structure](#4-test-report-structure)
5. [Verification Report Structure](#5-verification-report-structure)
6. [SIL-Specific Test Requirements](#6-sil-specific-test-requirements)
7. [Test Traceability](#7-test-traceability)
8. [Test Review and Approval Workflow](#8-test-review-and-approval-workflow)
9. [Template Validation](#9-template-validation)
10. [Tool Integration - Document Workflow](#10-tool-integration---document-workflow)
11. [Tool Integration - Traceability Management](#11-tool-integration---traceability-management)
12. [Automation Scripts](#12-automation-scripts)
13. [Complete Example Scenarios](#13-complete-example-scenarios)

---

## 1. EN 50128 Test and Verification Documentation Requirements

### 1.1 Overview

EN 50128:2011 requires comprehensive documentation of all testing and verification activities:

- **Section 6.1.4.4**: Test Specification requirements
- **Section 6.1.4.5**: Test Report requirements
- **Section 6.2.4**: Software Verification Plan and Reports
- **Table A.21**: Test coverage requirements by SIL level

### 1.2 Mandatory Test Documents (EN 50128 Section 6.1.4)

EN 50128 Section 6.1.4.3 states:
> "Software testing shall be documented by a Test Specification and a Test Report"

**Required Test Documents:**

1. **Component Test Specification** (Section 7.4.4.8) - Unit test specification
2. **Component Test Report** (Section 7.4.4.8) - Unit test results
3. **Software Integration Test Specification** (Section 7.6) - Integration test specification
4. **Software Integration Test Report** (Section 7.6) - Integration test results
5. **Overall Software Test Specification** (Section 7.7) - System/validation test specification
6. **Overall Software Test Report** (Section 7.7) - System/validation test results

**SIL-Specific Requirements:**
- **SIL 0-2**: Standard test documentation with technical review
- **SIL 3-4**: Test documentation with **independent review** and **assessor approval**

### 1.3 Test Specification Requirements (EN 50128 Section 6.1.4.4)

EN 50128 Section 6.1.4.4 mandates that each Test Specification SHALL document:

a) **Test objectives** - What is being tested and why
b) **Test cases, test data, and expected results** - Complete test specifications
c) **Types of tests to be performed** - Unit, integration, system, performance, etc.
d) **Test environment, tools, configuration, and programs** - Complete test setup
e) **Test criteria on which completion will be judged** - Pass/fail criteria
f) **Criteria and degree of test coverage to be achieved** - Coverage targets per Table A.21
g) **Roles and responsibilities** - Who performs testing (independent for SIL 3-4)
h) **Requirements covered by test specification** - Traceability to SRS
i) **Selection and utilization of test equipment** - Tools, frameworks, measurement devices

### 1.4 Test Report Requirements (EN 50128 Section 6.1.4.5)

EN 50128 Section 6.1.4.5 mandates that Test Reports SHALL:

a) **Mention Tester names** and **state test results** - Who tested and what happened
b) **Document whether test objectives and criteria met** - Pass/fail assessment
c) **Document and summarize failures** - All defects found
d) **Record test cases and results in machine-readable form** - XML/JSON for automation
e) **Tests SHALL be repeatable** - Same inputs → same outputs
f) **Tests SHALL be automated if practicable** - Automated test execution
g) **Test scripts SHALL be verified** - Verify test code correctness
h) **Document identity and configuration of all items** - Hardware, software, tools, versions
i) **Provide evaluation of test coverage** - Coverage achieved vs. target
j) **Note any deviations** - Deviations from Test Specification

### 1.5 Verification Report Requirements (EN 50128 Section 6.2.4)

EN 50128 Section 6.2.4.13 mandates that Verification Reports SHALL document:

a) **Identity and configuration of items verified** - What was verified and by whom
b) **Items not conforming to specifications** - Non-conformances found
c) **Components poorly adapted** - Design issues found
d) **Detected errors or deficiencies** - All defects found
e) **Fulfillment or deviation from Verification Plan** - Verification completeness
f) **Non-fulfilled or non-verifiable requirements** - Requirements issues
g) **Conclusions and recommendations** - Approve/reject decision

**Verification Activities Include:**
- **Static analysis** (Cppcheck, Clang, PC-lint Plus)
- **Code review** (manual review for MISRA C, design patterns, complexity)
- **Complexity analysis** (Lizard for cyclomatic complexity ≤10 for SIL 3-4)
- **Coverage analysis** (gcov/lcov for statement/branch/condition coverage)
- **Traceability verification** (requirements → design → code → tests)
- **Document review** (all project documents for completeness, correctness)

### 1.6 Coverage Requirements (EN 50128 Table A.21)

**Table A.21 - Test Coverage for Code:**

| Coverage Type | SIL 0 | SIL 1-2 | SIL 3-4 | Target |
|---------------|-------|---------|---------|--------|
| **Statement Coverage** | HR | HR | **M** | 100% for SIL 3-4 |
| **Branch Coverage** | HR | **M** | **M** | 100% for SIL 2+ |
| **Condition Coverage** | - | R | **M** | 100% for SIL 3-4 |
| **Data Flow Coverage** | - | R | HR | Not typically measured |
| **Path Coverage** | - | - | R | Infeasible for most code |

**Key**: M = Mandatory, HR = Highly Recommended, R = Recommended, - = No recommendation

**Coverage Targets by SIL:**
- **SIL 0**: Statement (HR), Branch (HR) - Typical target: 80%
- **SIL 1-2**: Statement (HR), Branch (**M** - 100%), Condition (R)
- **SIL 3-4**: Statement (**M** - 100%), Branch (**M** - 100%), Condition (**M** - 100%)

**Coverage Measurement:**
- Use **gcov/lcov** (GNU coverage tools) or **Bullseye** (commercial)
- Coverage measured at **component level** (unit tests) AND **integration level**
- Coverage SHALL be documented in Test Reports
- Any uncovered code SHALL be justified (dead code, defensive code, etc.)

---

## 2. Test Documentation Structure

### 2.1 Test Document Hierarchy

```
Test Documentation
│
├── Component Level (Unit Tests)
│   ├── Component Test Specification (DOC-COMPTEST-YYYY-NNN)
│   └── Component Test Report (DOC-COMPRPT-YYYY-NNN)
│
├── Integration Level
│   ├── Software Integration Test Specification (DOC-INTTEST-YYYY-NNN)
│   └── Software Integration Test Report (DOC-INTRPT-YYYY-NNN)
│
├── System Level (Validation)
│   ├── Overall Software Test Specification (DOC-SYSTEST-YYYY-NNN)
│   └── Overall Software Test Report (DOC-SYSRPT-YYYY-NNN)
│
└── Verification
    ├── Software Verification Plan (DOC-SVP-YYYY-NNN)
    └── Software Verification Report (DOC-VERRPT-YYYY-NNN)
```

### 2.2 Test Specification vs Test Report

**Test Specification** (written BEFORE testing):
- Test objectives and scope
- Test cases with inputs, expected outputs
- Test environment and tools
- Coverage targets
- Pass/fail criteria

**Test Report** (written AFTER testing):
- Test execution results (pass/fail for each test case)
- Coverage achieved (statement/branch/condition %)
- Defects found (with severity and status)
- Test environment configuration (actual versions used)
- Pass/fail assessment (overall)

### 2.3 Document Templates

All test and verification documents SHALL use EN 50128-compliant templates:

- `.opencode/skills/en50128-testing/templates/Component-Test-Specification-template.md` (577 lines)
- `.opencode/skills/en50128-testing/templates/Component-Test-Report-template.md` (554 lines)
- `.opencode/skills/en50128-testing/templates/Overall-Software-Test-Specification-template.md` (546 lines)
- `.opencode/skills/en50128-testing/templates/Overall-Software-Test-Report-template.md` (similar structure)

**Template Requirements:**
- **Document ID**: `DOC-{TYPE}-{PROJECT}-{NNN}` format
- **Version Control**: Version table with history
- **Approvals**: SIL-specific approval table (see Section 8)
- **Traceability**: Links to SRS, SAS, SDS, test specifications

---

## 3. Test Specification Structure

### 3.1 Component Test Specification (Unit Tests)

**Purpose**: Define unit tests for all software modules per EN 50128 Section 7.4.4.8

**Document Structure:**

```markdown
# Component Test Specification

## 1. INTRODUCTION
### 1.1 Purpose
### 1.2 Scope (modules under test)
### 1.3 Test Strategy (framework, approach, coverage targets)
### 1.4 References (SRS, SDS, SVP)

## 2. TEST ORGANIZATION
### 2.1 Test Naming Convention (TC-{MODULE}-{FUNCTION}-{NUM})
### 2.2 Test Data (valid, boundary, invalid, extreme)
### 2.3 Test Execution Order (sequential/independent)

## 3. COMPONENT TEST CASES
### 3.1 Module: [MOD-001] - [Module Name]
#### Test Case TC-MOD001-init-001: Initialize with valid parameters
- **Requirement**: REQ-FUNC-001
- **Objective**: Verify initialization succeeds with valid inputs
- **Preconditions**: System reset
- **Test Data**: 
  - Input: param1=10, param2=20
- **Procedure**:
  1. Call init(10, 20)
  2. Check return value == SUCCESS
  3. Verify internal state is initialized
- **Expected Result**: 
  - Return: SUCCESS
  - State: Initialized
- **Pass Criteria**: Return == SUCCESS AND state == INITIALIZED

#### Test Case TC-MOD001-init-002: Initialize with NULL pointer
- **Requirement**: REQ-SAFE-002 (defensive programming)
- **Objective**: Verify NULL pointer is rejected
- **Test Data**: 
  - Input: NULL pointer
- **Procedure**:
  1. Call init(NULL)
  2. Check return value == ERROR_NULL_POINTER
- **Expected Result**: ERROR_NULL_POINTER
- **Pass Criteria**: Return == ERROR_NULL_POINTER

[... repeat for all functions in all modules ...]

## 4. COVERAGE TARGETS
- Statement: 100% (SIL 3 requirement)
- Branch: 100% (SIL 3 requirement)
- Condition: 100% (SIL 3 requirement)

## 5. TEST ENVIRONMENT
- Host: Ubuntu 22.04 x86_64
- Compiler: gcc 11.4.0
- Test Framework: Unity 2.5.2
- Coverage Tool: gcov/lcov 1.16

## 6. TRACEABILITY MATRIX
| Test Case | Requirements Covered | Functions Tested |
|-----------|---------------------|------------------|
| TC-MOD001-init-001 | REQ-FUNC-001 | init() |
| TC-MOD001-init-002 | REQ-SAFE-002 | init() |
[...]
```

**Key Points:**
- **Every requirement** SHALL be covered by at least one test case
- **Every function** SHALL have tests for normal, boundary, and error cases
- **Coverage targets** SHALL meet Table A.21 requirements for SIL level
- **Traceability** to requirements is MANDATORY

### 3.2 Integration Test Specification

**Purpose**: Define integration tests for software component integration per EN 50128 Section 7.6

**Focus:**
- **Interface testing** between modules
- **Data flow** across module boundaries
- **Integration scenarios** (bottom-up, top-down, sandwich)
- **Performance testing** (timing, resource usage) - HR for SIL 3-4

**Test Case Structure:**
```markdown
#### Test Case TC-INT-001: Module A → Module B interface
- **Requirements**: REQ-FUNC-010, REQ-INT-001
- **Modules**: MOD-001 (Module A), MOD-002 (Module B)
- **Interface**: function_a() calls function_b()
- **Test Data**: 
  - Input to A: data_a = {x: 100, y: 200}
  - Expected output from A to B: data_ab = {z: 300}
- **Procedure**:
  1. Call function_a(data_a)
  2. Verify function_b receives data_ab
  3. Verify function_b returns expected result
  4. Verify function_a processes result correctly
- **Expected Result**: End-to-end data flow correct
- **Pass Criteria**: Data passed correctly, no data corruption
```

### 3.3 Overall Software Test Specification (System/Validation)

**Purpose**: Define system-level validation tests per EN 50128 Section 7.7

**Focus:**
- **Black-box testing** based on SRS (no knowledge of internal structure)
- **Operational scenarios** (real-world usage patterns)
- **Acceptance criteria** (customer requirements)
- **Performance testing** (MANDATORY for SIL 3-4 per Table A.7)

**Test Case Structure:**
```markdown
#### Test Case TC-SYS-001: Operational Scenario - Train Door Control
- **Requirements**: REQ-FUNC-050, REQ-SAFE-010, REQ-PERF-005
- **Scenario**: Door opens when train stopped, closes before departure
- **Preconditions**: Train at station, stopped
- **Test Steps**:
  1. Simulate "train stopped" signal
  2. Driver presses "door open" button
  3. Verify doors open (within 2 seconds)
  4. Passengers board (simulate 30 seconds)
  5. Driver presses "door close" button
  6. Verify doors close (within 3 seconds)
  7. Verify "doors locked" signal sent
  8. Driver releases brakes
  9. Verify train can depart
- **Expected Results**:
  - Doors open in ≤ 2 seconds
  - Doors close in ≤ 3 seconds
  - "Doors locked" signal sent before brake release
- **Pass Criteria**: All timing requirements met, safety interlock works
```

---

## 4. Test Report Structure

### 4.1 Component Test Report (Unit Test Results)

**Purpose**: Document unit test execution results per EN 50128 Section 6.1.4.5

**Document Structure:**

```markdown
# Component Test Report

## 1. EXECUTIVE SUMMARY
- **Test Result**: PASS / FAIL
- **Test Cases Executed**: 150 of 150 (100%)
- **Test Cases Passed**: 148 (98.7%)
- **Test Cases Failed**: 2 (1.3%)
- **Coverage Achieved**: Statement 99.2%, Branch 98.8%, Condition 97.5%
- **Coverage Target Met**: NO (SIL 3 requires 100%)
- **Defects Found**: 3 (Critical: 0, High: 1, Medium: 2, Low: 0)
- **Open Defects**: 1 High (DEFECT-045: Buffer overflow in parse_input)
- **Recommendation**: REWORK REQUIRED (1 open High defect, coverage below 100%)

## 2. INTRODUCTION
- Test Specification reference
- Test environment (actual configuration used)
- Test period (dates)

## 3. TEST EXECUTION SUMMARY
| Module | Test Suite | Total | Executed | Passed | Failed | Pass Rate |
|--------|------------|-------|----------|--------|--------|-----------|
| MOD-001 | test_module1.c | 50 | 50 | 50 | 0 | 100% |
| MOD-002 | test_module2.c | 50 | 50 | 48 | 2 | 96% |
| MOD-003 | test_module3.c | 50 | 50 | 50 | 0 | 100% |
| **TOTAL** | - | **150** | **150** | **148** | **2** | **98.7%** |

## 4. TEST RESULTS BY MODULE
### 4.1 Module MOD-001 - PASS
- All 50 test cases passed
- Coverage: Statement 100%, Branch 100%, Condition 100%

### 4.2 Module MOD-002 - FAIL
- **Failed Tests**:
  - **TC-MOD002-parse-005**: Buffer overflow on input > 256 bytes
    - Expected: ERROR_BUFFER_OVERFLOW
    - Actual: Segmentation fault
    - **Defect**: DEFECT-045 (High severity, OPEN)
  - **TC-MOD002-validate-012**: Incorrect validation result
    - Expected: VALIDATION_FAILED
    - Actual: VALIDATION_PASSED
    - **Defect**: DEFECT-046 (Medium severity, FIXED in v1.2)
- Coverage: Statement 98%, Branch 97%, Condition 95% (BELOW TARGET)

## 5. COVERAGE ANALYSIS
### 5.1 Overall Coverage
- Statement: 99.2% (Target: 100% for SIL 3) - **BELOW TARGET**
- Branch: 98.8% (Target: 100% for SIL 3) - **BELOW TARGET**
- Condition: 97.5% (Target: 100% for SIL 3) - **BELOW TARGET**

### 5.2 Uncovered Code
| File | Line | Reason |
|------|------|--------|
| module2.c | 345-350 | Defensive check for hardware fault (cannot test) |
| module2.c | 412 | Error path for malloc failure (no dynamic memory used) |

**Justification**: Lines 345-350 handle hardware faults that cannot be simulated in unit test environment. This will be tested in integration testing with hardware simulator.

## 6. DEFECTS FOUND
| Defect ID | Severity | Module | Description | Status |
|-----------|----------|--------|-------------|--------|
| DEFECT-045 | High | MOD-002 | Buffer overflow in parse_input() | OPEN |
| DEFECT-046 | Medium | MOD-002 | Incorrect validation logic | FIXED |
| DEFECT-047 | Low | MOD-003 | Warning message unclear | CLOSED |

## 7. CONCLUSIONS AND RECOMMENDATIONS
**Overall Result**: **FAIL** (1 open High defect, coverage below 100%)

**Issues**:
1. DEFECT-045 (High) must be fixed before integration
2. Coverage for MOD-002 below 100% target
3. Uncovered code needs justification or additional tests

**Recommendations**:
1. Fix DEFECT-045 (buffer overflow)
2. Add tests to increase MOD-002 coverage to 100%
3. Document justification for uncovered defensive code
4. Re-run Component Test Specification after fixes
5. DO NOT PROCEED to integration until all issues resolved

**Next Steps**:
- IMP: Fix DEFECT-045 and DEFECT-046
- TST: Add test cases for uncovered code paths
- TST: Re-execute test suite
- VER: Review fixes and re-test results
```

**Key Points:**
- **Machine-readable results** (XML/JSON) SHALL be generated for automation
- **All defects** SHALL be documented with severity and status
- **Coverage gaps** SHALL be justified or additional tests added
- **Pass/fail recommendation** SHALL be clear (APPROVE or REWORK REQUIRED)

### 4.2 Integration Test Report

**Purpose**: Document integration test execution results

**Focus:**
- Interface test results (data passed correctly between modules?)
- Integration coverage (all interfaces tested?)
- Performance results (timing requirements met?)
- Defects found during integration

**Similar structure to Component Test Report** with focus on integration-specific metrics.

### 4.3 Overall Software Test Report (System/Validation)

**Purpose**: Document system-level validation test results

**Focus:**
- Operational scenario results (all scenarios passed?)
- Acceptance criteria met (customer requirements satisfied?)
- Performance results (timing, resource usage within limits?)
- Validation coverage (all requirements validated?)

**Final Gate**: This report supports the **validation approval** decision (proceed to deployment or rework required).

---

## 5. Verification Report Structure

### 5.1 Software Verification Report

**Purpose**: Document verification activities and results per EN 50128 Section 6.2.4.13

**Document Structure:**

```markdown
# Software Verification Report

## 1. EXECUTIVE SUMMARY
- **Verification Result**: PASS / FAIL
- **Phase Verified**: Phase 4 (Implementation)
- **Verification Activities Performed**:
  - Static analysis (Cppcheck, Clang)
  - Code review (manual MISRA C review)
  - Complexity analysis (Lizard)
  - Coverage verification (gcov/lcov)
  - Traceability verification (requirements → code)
- **Non-Conformances Found**: 5
- **Critical Non-Conformances**: 0
- **Recommendation**: APPROVE (all critical issues resolved)

## 2. INTRODUCTION
- Software Verification Plan reference
- Phase/documents verified
- Verification period

## 3. VERIFICATION ACTIVITIES

### 3.1 Static Analysis (Cppcheck)
**Tool**: Cppcheck 2.13.0
**Command**: `cppcheck --enable=all --xml --xml-version=2 src/ 2> cppcheck_report.xml`
**Results**:
- **Errors**: 0
- **Warnings**: 12 (all justified as false positives or defensive code)
- **Style issues**: 45 (fixed)

**Sample Issues**:
- `src/module2.c:234`: Possible null pointer dereference
  - **Analysis**: False positive - pointer checked on line 232
  - **Action**: Justified, no change needed
- `src/module3.c:156`: Variable 'result' is assigned a value that is never used
  - **Analysis**: Result used for debugging (conditional compilation)
  - **Action**: Justified, no change needed

### 3.2 MISRA C Compliance (Manual Review)
**Standard**: MISRA C:2012
**SIL 3 Requirement**: Zero mandatory rule violations
**Results**:
- **Mandatory rule violations**: 0 ✓
- **Required rule violations**: 3 (all justified with formal deviations)
- **Advisory rule violations**: 15 (documented)

**Deviations**:
| Rule | Category | File | Justification |
|------|----------|------|---------------|
| 11.3 | Required | module2.c:345 | Cast required for hardware register access (documented) |
| 11.5 | Required | module3.c:128 | Cast from void* for generic callback (standard pattern) |

### 3.3 Complexity Analysis (Lizard)
**Tool**: Lizard 1.17.10
**SIL 3 Requirement**: CCN ≤ 10 for all functions
**Results**:
- **Functions analyzed**: 87
- **Functions with CCN > 10**: 0 ✓
- **Average CCN**: 4.2
- **Maximum CCN**: 9 (function: `process_state_machine`)

**Top 5 Most Complex Functions**:
| Function | CCN | LOC | File | Status |
|----------|-----|-----|------|--------|
| process_state_machine | 9 | 145 | module2.c | OK (≤10) |
| validate_input | 8 | 98 | module3.c | OK (≤10) |
| handle_error | 7 | 76 | error.c | OK (≤10) |

### 3.4 Coverage Verification
**Tool**: gcov/lcov 1.16
**SIL 3 Requirement**: Statement, Branch, Condition = 100%
**Results** (from Component Test Report):
- **Statement**: 99.2% (BELOW TARGET - justification provided)
- **Branch**: 98.8% (BELOW TARGET - justification provided)
- **Condition**: 97.5% (BELOW TARGET - justification provided)

**Action**: Reviewed uncovered code justification - ACCEPTED (defensive hardware fault checks cannot be unit tested, will be tested in integration).

### 3.5 Traceability Verification
**Tool**: workspace.py trace validate
**Requirements**:
- All SRS requirements traced to design (SAS/SDS)
- All SRS requirements traced to code
- All SRS requirements traced to tests
- No orphan design elements (design not traced to requirement)
- No orphan test cases (test not traced to requirement)

**Results**:
```bash
$ workspace.py trace validate
Traceability Validation Report:

Requirements → Design: 143/143 (100%) ✓
Requirements → Code: 143/143 (100%) ✓
Requirements → Tests: 143/143 (100%) ✓
Orphan design elements: 0 ✓
Orphan test cases: 0 ✓

PASS: Traceability complete
```

## 4. NON-CONFORMANCES FOUND
| NC ID | Severity | Description | Status |
|-------|----------|-------------|--------|
| NC-001 | Medium | Missing function header comment (module3.c:45) | FIXED |
| NC-002 | Low | Inconsistent naming convention (variable: temp_val) | FIXED |
| NC-003 | Low | Magic number used (module2.c:234) | FIXED (defined constant) |
| NC-004 | Info | TODO comment in code (module1.c:89) | CLOSED (TODO addressed) |
| NC-005 | Info | Unused variable 'debug_flag' | CLOSED (removed) |

**Critical Non-Conformances**: 0

## 5. VERIFICATION EVIDENCE
- Static analysis reports: `docs/verification/cppcheck_report.xml`
- Complexity analysis: `docs/verification/complexity_report.html`
- Coverage reports: `docs/verification/coverage/index.html`
- MISRA C checklist: `docs/verification/misra_checklist.xlsx`
- Code review records: `docs/verification/code_review_records.md`
- Traceability matrix: `docs/verification/traceability_matrix.xlsx`

## 6. CONCLUSIONS AND RECOMMENDATIONS
**Verification Result**: **PASS**

**Summary**:
- All static analysis issues resolved or justified
- MISRA C compliance achieved (0 mandatory violations)
- Complexity within limits (all functions CCN ≤ 10)
- Coverage below 100% but justified (hardware-specific defensive code)
- Traceability complete (100% requirements traced)
- All non-conformances resolved

**Recommendation**: **APPROVE Phase 4 (Implementation) for gate check**

**Verifier**: [Name], Independent Verifier (SIL 3)
**Date**: 2026-03-15
**Signature**: [Digital signature]
```

**Key Points:**
- **Independent verification** MANDATORY for SIL 3-4
- **All verification activities** from Verification Plan SHALL be performed
- **Evidence** SHALL be collected and referenced
- **Non-conformances** SHALL be documented and resolved
- **Approve/reject recommendation** SHALL be clear

---

## 6. SIL-Specific Test Requirements

### 6.1 SIL 0-1 Requirements

**Coverage** (Table A.21):
- Statement: HR (target ~80%)
- Branch: HR (target ~80%)

**Testing Techniques** (Table A.5):
- Dynamic Analysis and Testing: No recommendation
- Functional/Black-Box Testing: HR

**Independence**:
- **No independence required** - Developer can test own code

**Approval**:
- Author
- Technical Reviewer
- QA Manager
- Project Manager

### 6.2 SIL 2 Requirements

**Coverage** (Table A.21):
- Statement: HR (target ≥90%)
- Branch: **MANDATORY (100%)**
- Condition: R

**Testing Techniques** (Table A.5):
- Dynamic Analysis and Testing: HR
- Test Coverage for Code: HR
- Functional/Black-Box Testing: HR
- Performance Testing: HR

**Independence**:
- **No independence required** (but recommended for verification)

**Approval**:
- Author
- Technical Reviewer
- QA Manager
- Safety Manager
- Project Manager

### 6.3 SIL 3-4 Requirements

**Coverage** (Table A.21):
- Statement: **MANDATORY (100%)**
- Branch: **MANDATORY (100%)**
- Condition: **MANDATORY (100%)**

**Testing Techniques** (Table A.5):
- Dynamic Analysis and Testing: **MANDATORY**
- Test Coverage for Code: **MANDATORY**
- Functional/Black-Box Testing: **MANDATORY**
- Performance Testing: **MANDATORY**

**Independence** (EN 50128 Section 5.1.2.10):
- **MANDATORY**: Testing performed by independent Tester (not Implementer)
- **MANDATORY**: Verification performed by independent Verifier (not Designer/Implementer/Tester)
- **MANDATORY**: Validation performed by independent Validator (not Developer/Verifier)

**Approval**:
- Author
- Technical Reviewer (independent)
- QA Manager
- Safety Manager
- Independent Verifier
- Independent Validator
- Assessor (SIL 3-4)
- Project Manager

**Additional Requirements**:
- **Fault injection testing**: HR (test error handling)
- **Robustness testing**: M for SIL 4
- **All test scripts SHALL be verified** (test the tests)
- **Machine-readable test results** (XML/JSON for automation)

### 6.4 SIL-Specific Coverage Targets Summary

| SIL | Statement | Branch | Condition | MC/DC |
|-----|-----------|--------|-----------|-------|
| **0** | HR (~80%) | HR (~80%) | - | - |
| **1** | HR (~90%) | HR (~90%) | R | - |
| **2** | HR (~95%) | **M (100%)** | R (~90%) | R |
| **3** | **M (100%)** | **M (100%)** | **M (100%)** | HR |
| **4** | **M (100%)** | **M (100%)** | **M (100%)** | HR |

---

## 7. Test Traceability

### 7.1 Traceability Requirements

EN 50128 requires complete traceability for SIL 3-4 (Table A.9):
- **Requirements → Tests**: Every requirement SHALL have at least one test
- **Tests → Requirements**: Every test SHALL trace to at least one requirement
- **Tests → Test Results**: Every test case SHALL have a documented result

### 7.2 Requirements-to-Tests Traceability Matrix

**Example RTM (Requirements Traceability Matrix):**

```markdown
| Requirement ID | Requirement Title | Test Cases | Test Status |
|----------------|-------------------|------------|-------------|
| REQ-FUNC-001 | Initialize system | TC-UNIT-001, TC-INT-005, TC-SYS-001 | PASS |
| REQ-FUNC-002 | Process input data | TC-UNIT-010, TC-UNIT-011, TC-INT-010 | PASS |
| REQ-SAFE-001 | Detect buffer overflow | TC-UNIT-015, TC-INT-020 | FAIL (DEFECT-045) |
| REQ-PERF-001 | Response time < 100ms | TC-PERF-001, TC-SYS-010 | PASS |
```

### 7.3 Automated Traceability with workspace.py

**Link test cases to requirements:**

```bash
# Link unit test to requirement
workspace.py trace link \
  --from "REQ-FUNC-001" \
  --to "TC-UNIT-001" \
  --type "verified-by" \
  --rationale "Unit test verifies system initialization"

# Link integration test to requirement
workspace.py trace link \
  --from "REQ-INT-001" \
  --to "TC-INT-005" \
  --type "verified-by" \
  --rationale "Integration test verifies module A-B interface"

# Link system test to requirement
workspace.py trace link \
  --from "REQ-FUNC-050" \
  --to "TC-SYS-001" \
  --type "verified-by" \
  --rationale "System test verifies door control operational scenario"
```

**Generate requirements coverage report:**

```bash
# Check which requirements have test coverage
workspace.py trace report --type requirements-coverage
```

**Output:**
```
Requirements Coverage Report:

Total Requirements: 143
Requirements with Tests: 143 (100%)
Requirements without Tests: 0

Untested Requirements: None

Coverage by Category:
- Functional Requirements: 87/87 (100%)
- Safety Requirements: 34/34 (100%)
- Performance Requirements: 12/12 (100%)
- Interface Requirements: 10/10 (100%)

PASS: All requirements have test coverage
```

### 7.4 Test-to-Results Traceability

**Link test cases to test results in Test Report:**

```bash
# Record test result
workspace.py trace link \
  --from "TC-UNIT-001" \
  --to "TEST-RESULT-001" \
  --type "result" \
  --rationale "Test executed 2026-03-15, PASS"

# Record failed test result with defect
workspace.py trace link \
  --from "TC-UNIT-015" \
  --to "DEFECT-045" \
  --type "found-defect" \
  --rationale "Test revealed buffer overflow"
```

---

## 8. Test Review and Approval Workflow

### 8.1 Test Specification Approval Workflow (SIL 3-4)

```
Step 1: Author (TST) creates Test Specification
   │
   │ workspace.py wf submit docs/Component-Test-Specification.md \
   │   --doc-type test-specification --phase component-testing
   ▼
Step 2: QUA reviews for template compliance (1 pass only)
   │
   │ [QUA checks: document structure, traceability, coverage targets]
   ├─► APPROVE: Submit to VER
   └─► REJECT: Return to TST (TST fixes, resubmit to QUA - 1 pass)
   ▼
Step 3: VER reviews for technical correctness
   │
   │ [VER checks: test cases complete, coverage adequate, traceability]
   ├─► APPROVE: Submit to SAF
   └─► REJECT: Return to TST (TST fixes, restart workflow)
   ▼
Step 4: SAF reviews for safety completeness
   │
   │ [SAF checks: safety requirements tested, fault injection, robustness]
   ├─► APPROVE: Submit to PM
   └─► REJECT: Return to TST (TST fixes, restart workflow)
   ▼
Step 5: PM approves and baselines
   │
   │ workspace.py wf approve docs/Component-Test-Specification.md --approver PM
   ▼
Test Specification APPROVED (baseline, ready for test execution)
```

**Key Points:**
- **QUA review MANDATORY** before VER review (1 pass only for template compliance)
- **Independent VER** MANDATORY for SIL 3-4
- **SAF review** ensures safety requirements covered
- **Baseline** after PM approval (version controlled)

### 8.2 Test Report Approval Workflow (SIL 3-4)

```
Step 1: Author (TST) creates Test Report (after test execution)
   │
   │ workspace.py wf submit docs/Component-Test-Report.md \
   │   --doc-type test-report --phase component-testing
   ▼
Step 2: QUA reviews for template compliance (1 pass only)
   │
   │ [QUA checks: document structure, results documented, defects recorded]
   ├─► APPROVE: Submit to VER
   └─► REJECT: Return to TST (TST fixes, resubmit to QUA - 1 pass)
   ▼
Step 3: VER reviews test results
   │
   │ [VER checks: coverage achieved, defects resolved, pass/fail justified]
   ├─► PASS: Submit to VAL
   └─► FAIL: Reject (TST/IMP fix defects, re-test, restart workflow)
   ▼
Step 4: VAL reviews for validation completeness
   │
   │ [VAL checks: requirements validated, acceptance criteria met]
   ├─► APPROVE: Submit to PM
   └─► REJECT: Return to TST (re-test required, restart workflow)
   ▼
Step 5: PM approves and gates
   │
   │ workspace.py wf approve docs/Component-Test-Report.md --approver PM
   ▼
Test Report APPROVED (gate check: proceed to next phase or rework)
```

**Key Points:**
- **Test execution BEFORE Test Report creation**
- **VER review focuses on technical correctness of results**
- **VAL review focuses on validation completeness**
- **Gate decision**: PASS (proceed) or FAIL (rework and re-test)

### 8.3 Verification Report Approval Workflow (SIL 3-4)

```
Step 1: Author (VER) creates Verification Report
   │
   │ [VER performs: static analysis, code review, complexity, coverage, traceability]
   │ workspace.py wf submit docs/Software-Verification-Report.md \
   │   --doc-type verification-report --phase verification
   ▼
Step 2: QUA reviews for template compliance (1 pass only)
   │
   │ [QUA checks: document structure, evidence included, NC documented]
   ├─► APPROVE: Submit to VAL
   └─► REJECT: Return to VER (VER fixes, resubmit to QUA - 1 pass)
   ▼
Step 3: VAL reviews verification completeness
   │
   │ [VAL checks: all verification activities performed, evidence adequate]
   ├─► APPROVE: Submit to PM
   └─► REJECT: Return to VER (additional verification needed, restart workflow)
   ▼
Step 4: PM approves and gates
   │
   │ workspace.py wf approve docs/Software-Verification-Report.md --approver PM
   ▼
Verification Report APPROVED (phase gate: proceed to next phase)
```

**Key Points:**
- **VER is independent** (not Designer/Implementer/Tester)
- **Evidence collection MANDATORY** (static analysis reports, coverage, traceability)
- **VAL review ensures verification completeness**
- **Phase gate decision** based on Verification Report

### 8.4 Approval Role Summary by SIL

| Document | SIL 0-1 Approvers | SIL 2 Approvers | SIL 3-4 Approvers |
|----------|-------------------|-----------------|-------------------|
| **Test Specification** | Author, Reviewer, QUA, PM | Author, Reviewer, QUA, SAF, PM | Author, Reviewer, QUA, VER (ind.), SAF, PM |
| **Test Report** | Author, Reviewer, QUA, PM | Author, Reviewer, QUA, SAF, PM | Author, Reviewer, QUA, VER (ind.), VAL (ind.), PM |
| **Verification Report** | Author, Reviewer, QUA, PM | Author, Reviewer, QUA, SAF, PM | Author (VER ind.), QUA, VAL (ind.), PM |

**(ind.) = independent role required**

---

## 9. Template Validation

### 9.1 Automated Template Validation Script

Test and verification documents SHALL be validated for completeness and EN 50128 compliance using automated scripts.

**Script: `validate_test_doc_template.py`** (~200 lines)

```python
#!/usr/bin/env python3
"""
EN 50128 Test and Verification Document Template Validator

Validates test specifications, test reports, and verification reports
for EN 50128 compliance.

Usage:
    python3 validate_test_doc_template.py <document.md> <doc-type> <sil-level>
    
    doc-type: test-specification | test-report | verification-report
    sil-level: 0, 1, 2, 3, or 4

Example:
    python3 validate_test_doc_template.py Component-Test-Specification.md test-specification 3
"""

import sys
import re
from pathlib import Path
from typing import List, Tuple, Dict

def validate_document_header(content: str, sil: int) -> List[str]:
    """Validate standard document header."""
    errors = []
    
    # Check Document ID format
    if not re.search(r'\*\*Document ID\*\*.*DOC-[A-Z]+-[A-Z0-9]+-\d{3}', content):
        errors.append("HEADER: Document ID missing or incorrect format (expected: DOC-XXX-YYYY-NNN)")
    
    # Check version
    if not re.search(r'\*\*Version\*\*.*\d+\.\d+', content):
        errors.append("HEADER: Version missing or incorrect format (expected: X.Y)")
    
    # Check SIL level
    if not re.search(rf'\*\*SIL Level\*\*.*{sil}', content):
        errors.append(f"HEADER: SIL Level {sil} not documented")
    
    # Check status
    if not re.search(r'\*\*Status\*\*.*\[(Draft|Review|Approved|Baseline)\]', content):
        errors.append("HEADER: Status missing or invalid")
    
    return errors

def validate_document_control(content: str) -> List[str]:
    """Validate document control table."""
    errors = []
    
    if '## DOCUMENT CONTROL' not in content:
        errors.append("DOCUMENT CONTROL: Section missing")
    else:
        # Check version history table
        if not re.search(r'\| Version \| Date \| Author \| Changes \| Approved By \|', content):
            errors.append("DOCUMENT CONTROL: Version history table missing or incorrect format")
    
    return errors

def validate_approvals(content: str, sil: int) -> List[str]:
    """Validate approvals table based on SIL level."""
    errors = []
    
    if '## APPROVALS' not in content:
        errors.append("APPROVALS: Section missing")
        return errors
    
    # Extract approvals section
    approvals_match = re.search(r'## APPROVALS(.+?)(?:##|\Z)', content, re.DOTALL)
    if not approvals_match:
        errors.append("APPROVALS: Section empty")
        return errors
    
    approvals_section = approvals_match.group(1)
    
    # SIL-specific approval requirements
    required_roles = ['Author', 'Technical Reviewer', 'QA Manager', 'Project Manager']
    
    if sil >= 2:
        required_roles.append('Safety Manager')
    
    if sil >= 3:
        required_roles.extend(['Independent Verifier', 'Independent Validator', 'Assessor'])
    
    # Check each required role
    for role in required_roles:
        if role not in approvals_section:
            errors.append(f"APPROVALS: Missing required role '{role}' for SIL {sil}")
    
    # Check approval table format
    if not re.search(r'\| Role \| Name \| Signature \| Date \|', approvals_section):
        errors.append("APPROVALS: Approval table missing or incorrect format")
    
    return errors

def validate_test_specification(content: str, sil: int) -> List[str]:
    """Validate Test Specification specific requirements."""
    errors = []
    
    # Section 6.1.4.4 requirements
    required_sections = [
        ('## 1. INTRODUCTION', 'Introduction'),
        ('### 1.1 Purpose', 'Purpose (test objectives)'),
        ('### 1.3 Test Strategy', 'Test Strategy'),
        ('## 3. COMPONENT TEST CASES', 'Test Cases or TEST CASES'),
        ('## 4. COVERAGE TARGETS', 'Coverage Targets'),
        ('## 5. TEST ENVIRONMENT', 'Test Environment'),
        ('## 6. TRACEABILITY MATRIX', 'Traceability Matrix'),
    ]
    
    for pattern, name in required_sections:
        if pattern not in content and name not in content:
            errors.append(f"TEST SPEC: Missing required section '{name}' (EN 50128 6.1.4.4)")
    
    # Check coverage targets match SIL requirements
    if sil >= 3:
        if 'Statement: 100%' not in content and 'Statement.*100%' not in content:
            errors.append(f"TEST SPEC: SIL {sil} requires Statement coverage 100%")
        if 'Branch: 100%' not in content and 'Branch.*100%' not in content:
            errors.append(f"TEST SPEC: SIL {sil} requires Branch coverage 100%")
        if 'Condition: 100%' not in content and 'Condition.*100%' not in content:
            errors.append(f"TEST SPEC: SIL {sil} requires Condition coverage 100%")
    elif sil == 2:
        if 'Branch: 100%' not in content and 'Branch.*100%' not in content:
            errors.append(f"TEST SPEC: SIL {sil} requires Branch coverage 100%")
    
    # Check test case format
    if not re.search(r'Test Case TC-[A-Z0-9]+-[a-z_]+-\d{3}', content):
        errors.append("TEST SPEC: Test cases missing or incorrect format (expected: TC-MOD-func-001)")
    
    # Check traceability
    if not re.search(r'REQ-[A-Z]+-\d{3}', content):
        errors.append("TEST SPEC: Requirements traceability missing (no REQ-XXX-NNN references)")
    
    return errors

def validate_test_report(content: str, sil: int) -> List[str]:
    """Validate Test Report specific requirements."""
    errors = []
    
    # Section 6.1.4.5 requirements
    required_sections = [
        ('## 1. EXECUTIVE SUMMARY', 'Executive Summary'),
        ('## 3. TEST EXECUTION SUMMARY', 'Test Execution Summary'),
        ('## 5. COVERAGE ANALYSIS', 'Coverage Analysis'),
        ('## 6. DEFECTS FOUND', 'Defects Found or DEFECTS'),
        ('## 7. CONCLUSIONS AND RECOMMENDATIONS', 'Conclusions and Recommendations'),
    ]
    
    for pattern, name in required_sections:
        if pattern not in content and name not in content:
            errors.append(f"TEST REPORT: Missing required section '{name}' (EN 50128 6.1.4.5)")
    
    # Check test result present
    if not re.search(r'\*\*Test Result\*\*.*\*\*(PASS|FAIL)\*\*', content):
        errors.append("TEST REPORT: Overall test result (PASS/FAIL) missing")
    
    # Check coverage results
    if not re.search(r'Statement.*:\s*\d+\.\d+%', content):
        errors.append("TEST REPORT: Statement coverage result missing")
    
    if sil >= 2:
        if not re.search(r'Branch.*:\s*\d+\.\d+%', content):
            errors.append("TEST REPORT: Branch coverage result missing (mandatory for SIL 2+)")
    
    if sil >= 3:
        if not re.search(r'Condition.*:\s*\d+\.\d+%', content):
            errors.append("TEST REPORT: Condition coverage result missing (mandatory for SIL 3-4)")
    
    # Check defects documented
    if 'Defects Found' in content or 'DEFECTS' in content:
        if not re.search(r'DEFECT-\d{3}', content) and 'No defects found' not in content:
            errors.append("TEST REPORT: Defects section present but no defects documented or 'No defects found' statement")
    
    # Check recommendation
    if not re.search(r'\*\*Recommendation\*\*.*\*\*(APPROVE|REWORK REQUIRED|PASS|FAIL)\*\*', content):
        errors.append("TEST REPORT: Recommendation missing (expected: APPROVE or REWORK REQUIRED)")
    
    return errors

def validate_verification_report(content: str, sil: int) -> List[str]:
    """Validate Verification Report specific requirements."""
    errors = []
    
    # Section 6.2.4.13 requirements
    required_sections = [
        ('## 1. EXECUTIVE SUMMARY', 'Executive Summary'),
        ('## 3. VERIFICATION ACTIVITIES', 'Verification Activities'),
        ('## 4. NON-CONFORMANCES FOUND', 'Non-Conformances or NON-CONFORMANCES'),
        ('## 5. VERIFICATION EVIDENCE', 'Verification Evidence'),
        ('## 6. CONCLUSIONS AND RECOMMENDATIONS', 'Conclusions and Recommendations'),
    ]
    
    for pattern, name in required_sections:
        if pattern not in content and name not in content:
            errors.append(f"VERIFICATION REPORT: Missing required section '{name}' (EN 50128 6.2.4.13)")
    
    # Check verification result
    if not re.search(r'\*\*Verification Result\*\*.*\*\*(PASS|FAIL)\*\*', content):
        errors.append("VERIFICATION REPORT: Verification result (PASS/FAIL) missing")
    
    # Check verification activities for SIL 3-4
    if sil >= 3:
        mandatory_activities = ['Static analysis', 'Code review', 'Complexity analysis', 'Coverage', 'Traceability']
        for activity in mandatory_activities:
            if activity.lower() not in content.lower():
                errors.append(f"VERIFICATION REPORT: Missing mandatory verification activity '{activity}' for SIL {sil}")
    
    # Check evidence documented
    if 'Verification Evidence' in content or 'VERIFICATION EVIDENCE' in content:
        if not re.search(r'docs/verification/', content):
            errors.append("VERIFICATION REPORT: Evidence section present but no evidence file paths documented")
    
    # Check recommendation
    if not re.search(r'\*\*Recommendation\*\*.*\*\*(APPROVE|REJECT)\*\*', content):
        errors.append("VERIFICATION REPORT: Recommendation missing (expected: APPROVE or REJECT)")
    
    # Check verifier name and signature (independence for SIL 3-4)
    if sil >= 3:
        if not re.search(r'\*\*Verifier\*\*.*Independent Verifier', content):
            errors.append("VERIFICATION REPORT: Independent Verifier name/title missing (mandatory for SIL 3-4)")
    
    return errors

def main():
    if len(sys.argv) != 4:
        print("Usage: python3 validate_test_doc_template.py <document.md> <doc-type> <sil-level>")
        print("  doc-type: test-specification | test-report | verification-report")
        print("  sil-level: 0, 1, 2, 3, or 4")
        sys.exit(1)
    
    doc_path = Path(sys.argv[1])
    doc_type = sys.argv[2]
    sil = int(sys.argv[3])
    
    if not doc_path.exists():
        print(f"ERROR: Document '{doc_path}' not found")
        sys.exit(1)
    
    if doc_type not in ['test-specification', 'test-report', 'verification-report']:
        print(f"ERROR: Invalid doc-type '{doc_type}'")
        sys.exit(1)
    
    if sil not in [0, 1, 2, 3, 4]:
        print(f"ERROR: Invalid SIL level '{sil}'")
        sys.exit(1)
    
    # Read document
    content = doc_path.read_text(encoding='utf-8')
    
    # Validate
    errors = []
    errors.extend(validate_document_header(content, sil))
    errors.extend(validate_document_control(content))
    errors.extend(validate_approvals(content, sil))
    
    if doc_type == 'test-specification':
        errors.extend(validate_test_specification(content, sil))
    elif doc_type == 'test-report':
        errors.extend(validate_test_report(content, sil))
    elif doc_type == 'verification-report':
        errors.extend(validate_verification_report(content, sil))
    
    # Report results
    print(f"\n{'='*80}")
    print(f"EN 50128 Document Validation Report")
    print(f"{'='*80}")
    print(f"Document: {doc_path}")
    print(f"Type: {doc_type}")
    print(f"SIL: {sil}")
    print(f"{'='*80}\n")
    
    if errors:
        print(f"❌ VALIDATION FAILED: {len(errors)} error(s) found\n")
        for i, error in enumerate(errors, 1):
            print(f"{i}. {error}")
        print(f"\n{'='*80}")
        sys.exit(1)
    else:
        print("✅ VALIDATION PASSED: Document complies with EN 50128 requirements\n")
        print(f"{'='*80}")
        sys.exit(0)

if __name__ == '__main__':
    main()
```

### 9.2 Using the Validation Script

**Validate Test Specification:**
```bash
python3 validate_test_doc_template.py \
  docs/Component-Test-Specification.md \
  test-specification \
  3
```

**Output (PASS):**
```
================================================================================
EN 50128 Document Validation Report
================================================================================
Document: docs/Component-Test-Specification.md
Type: test-specification
SIL: 3
================================================================================

✅ VALIDATION PASSED: Document complies with EN 50128 requirements

================================================================================
```

**Output (FAIL):**
```
================================================================================
EN 50128 Document Validation Report
================================================================================
Document: docs/Component-Test-Specification.md
Type: test-specification
SIL: 3
================================================================================

❌ VALIDATION FAILED: 5 error(s) found

1. HEADER: Document ID missing or incorrect format (expected: DOC-XXX-YYYY-NNN)
2. APPROVALS: Missing required role 'Independent Verifier' for SIL 3
3. TEST SPEC: Missing required section 'Traceability Matrix' (EN 50128 6.1.4.4)
4. TEST SPEC: SIL 3 requires Statement coverage 100%
5. TEST SPEC: Requirements traceability missing (no REQ-XXX-NNN references)

================================================================================
```

---

## 10. Tool Integration - Document Workflow

### 10.1 Submit Test Specification for Approval

**Command**: `workspace.py wf submit <document> --doc-type <type> --phase <phase>`

**Example: Submit Component Test Specification (SIL 3)**

```bash
# Submit Component Test Specification to QUA for review
workspace.py wf submit docs/Component-Test-Specification.md \
  --doc-type test-specification \
  --phase component-testing \
  --sil 3 \
  --author "Jane Doe (TST)" \
  --description "Unit test specification for all software modules"
```

**Output:**
```
Document submitted for approval: docs/Component-Test-Specification.md

Workflow ID: WF-TEST-001
Document Type: test-specification
Phase: component-testing
SIL: 3
Status: Pending QUA Review

Approval Workflow (SIL 3):
  1. QUA (template compliance) - PENDING
  2. VER (technical review) - Not started
  3. SAF (safety review) - Not started
  4. PM (approval) - Not started

Next Step: QUA reviews document for template compliance
```

### 10.2 QUA Approves Test Specification

**Command**: `workspace.py wf approve <document> --role QUA`

```bash
# QUA approves after template validation
workspace.py wf approve docs/Component-Test-Specification.md \
  --role QUA \
  --approver "John Smith (QUA)" \
  --comments "Template compliance verified, all required sections present"
```

**Output:**
```
Approval recorded: docs/Component-Test-Specification.md

Workflow ID: WF-TEST-001
Approver: John Smith (QUA)
Status: QUA Approved, pending VER review

Next Step: VER reviews document for technical correctness
```

### 10.3 Submit Test Report After Test Execution

**Command**: `workspace.py wf submit <document> --doc-type test-report`

```bash
# Submit Component Test Report after test execution
workspace.py wf submit docs/Component-Test-Report.md \
  --doc-type test-report \
  --phase component-testing \
  --sil 3 \
  --author "Jane Doe (TST)" \
  --description "Unit test execution results, 148/150 tests passed, 1 open defect"
```

**Output:**
```
Document submitted for approval: docs/Component-Test-Report.md

Workflow ID: WF-TESTRPT-001
Document Type: test-report
Phase: component-testing
SIL: 3
Status: Pending QUA Review
Test Result: FAIL (1 open High defect)

Approval Workflow (SIL 3):
  1. QUA (template compliance) - PENDING
  2. VER (technical review) - Not started
  3. VAL (validation review) - Not started
  4. PM (gate decision) - Not started

WARNING: Test result is FAIL - expect rework required
Next Step: QUA reviews document for template compliance
```

### 10.4 Track Document Approval Status

**Command**: `workspace.py wf status <document>`

```bash
# Check approval status
workspace.py wf status docs/Component-Test-Specification.md
```

**Output:**
```
Document: docs/Component-Test-Specification.md
Workflow ID: WF-TEST-001
Status: Approved

Approval History:
  1. QUA - John Smith - Approved - 2026-03-10 14:30
  2. VER - Alice Johnson (Independent) - Approved - 2026-03-11 10:15
  3. SAF - Bob Wilson - Approved - 2026-03-12 09:00
  4. PM - Charlie Brown - Approved - 2026-03-12 15:45

Document Status: BASELINE (v1.0)
Next Phase: Component testing execution
```

---

## 11. Tool Integration - Traceability Management

### 11.1 Link Test Cases to Requirements

**Command**: `workspace.py trace link --from <req> --to <test> --type verified-by`

**Example: Link unit tests to requirements**

```bash
# Link test case to functional requirement
workspace.py trace link \
  --from "REQ-FUNC-001" \
  --to "TC-UNIT-001" \
  --type "verified-by" \
  --rationale "Unit test verifies system initialization with valid parameters"

# Link test case to safety requirement
workspace.py trace link \
  --from "REQ-SAFE-002" \
  --to "TC-UNIT-002" \
  --type "verified-by" \
  --rationale "Unit test verifies NULL pointer detection (defensive programming)"

# Link integration test to interface requirement
workspace.py trace link \
  --from "REQ-INT-001" \
  --to "TC-INT-005" \
  --type "verified-by" \
  --rationale "Integration test verifies Module A→B interface data flow"
```

### 11.2 Generate Requirements Coverage Report

**Command**: `workspace.py trace report --type requirements-coverage`

```bash
# Generate coverage report for all requirements
workspace.py trace report --type requirements-coverage
```

**Output:**
```
================================================================================
Requirements Coverage Report (Test Traceability)
================================================================================
Generated: 2026-03-15 10:30:00
SIL: 3 (100% coverage MANDATORY)

Total Requirements: 143
Requirements with Tests: 143 (100%)
Requirements without Tests: 0

Coverage by Category:
  Functional Requirements (REQ-FUNC-*): 87/87 (100%)
  Safety Requirements (REQ-SAFE-*): 34/34 (100%)
  Performance Requirements (REQ-PERF-*): 12/12 (100%)
  Interface Requirements (REQ-INT-*): 10/10 (100%)

Coverage by Test Level:
  Unit Tests (TC-UNIT-*): 87 requirements covered
  Integration Tests (TC-INT-*): 56 requirements covered
  System Tests (TC-SYS-*): 143 requirements covered (all)

Untested Requirements: None

✅ PASS: All requirements have test coverage (SIL 3 requirement met)
================================================================================
```

### 11.3 Validate Traceability Completeness

**Command**: `workspace.py trace validate`

```bash
# Validate complete traceability chain
workspace.py trace validate
```

**Output:**
```
================================================================================
Traceability Validation Report
================================================================================
SIL: 3 (Traceability MANDATORY)

Forward Traceability:
  SRS → SAS: 143/143 (100%) ✓
  SRS → SDS: 143/143 (100%) ✓
  SRS → Code: 143/143 (100%) ✓
  SRS → Tests: 143/143 (100%) ✓

Backward Traceability:
  SAS → SRS: 87/87 design elements traced (100%) ✓
  SDS → SRS: 134/134 design elements traced (100%) ✓
  Code → SRS: 156/156 functions traced (100%) ✓
  Tests → SRS: 247/247 test cases traced (100%) ✓

Orphan Detection:
  Orphan design elements (SAS/SDS not traced to SRS): 0 ✓
  Orphan code (functions not traced to design): 0 ✓
  Orphan tests (tests not traced to requirements): 0 ✓

✅ PASS: Traceability complete (SIL 3 requirement met)
================================================================================
```

### 11.4 Link Test Results to Defects

**Command**: `workspace.py trace link --from <test> --to <defect> --type found-defect`

```bash
# Link failed test to defect
workspace.py trace link \
  --from "TC-UNIT-015" \
  --to "DEFECT-045" \
  --type "found-defect" \
  --rationale "Test TC-UNIT-015 revealed buffer overflow in parse_input() function"

# Query defects found by test
workspace.py trace query --from "TC-UNIT-015" --type found-defect
```

**Output:**
```
Defects found by test TC-UNIT-015:

DEFECT-045 (High severity):
  Module: MOD-002
  Function: parse_input()
  Description: Buffer overflow when input > 256 bytes
  Status: OPEN
  Found by: TC-UNIT-015 (2026-03-15)
  Assigned to: John Doe (IMP)
```

---

## 12. Automation Scripts

### 12.1 Test Report Generator

**Script: `generate_test_report.py`** (~200 lines)

**Purpose**: Automatically generate Test Report from test execution results (XML/JSON)

```python
#!/usr/bin/env python3
"""
EN 50128 Test Report Generator

Generates Test Report from machine-readable test results (JUnit XML format).

Usage:
    python3 generate_test_report.py <test-results.xml> <template.md> <output-report.md>

Example:
    python3 generate_test_report.py \
      build/test-results.xml \
      templates/Component-Test-Report-template.md \
      docs/Component-Test-Report.md
"""

import sys
import xml.etree.ElementTree as ET
from pathlib import Path
from datetime import datetime

def parse_junit_xml(xml_path: Path) -> dict:
    """Parse JUnit XML test results."""
    tree = ET.parse(xml_path)
    root = tree.getroot()
    
    # Extract test suite information
    testsuite = root.find('testsuite')
    if testsuite is None:
        testsuite = root  # Root might be testsuite itself
    
    results = {
        'name': testsuite.get('name', 'Unknown'),
        'tests': int(testsuite.get('tests', 0)),
        'failures': int(testsuite.get('failures', 0)),
        'errors': int(testsuite.get('errors', 0)),
        'skipped': int(testsuite.get('skipped', 0)),
        'time': float(testsuite.get('time', 0.0)),
        'timestamp': testsuite.get('timestamp', datetime.now().isoformat()),
        'testcases': []
    }
    
    # Extract test cases
    for testcase in testsuite.findall('testcase'):
        tc = {
            'classname': testcase.get('classname', ''),
            'name': testcase.get('name', ''),
            'time': float(testcase.get('time', 0.0)),
            'status': 'PASS'
        }
        
        # Check for failure
        failure = testcase.find('failure')
        if failure is not None:
            tc['status'] = 'FAIL'
            tc['failure_message'] = failure.get('message', '')
            tc['failure_type'] = failure.get('type', '')
            tc['failure_text'] = failure.text or ''
        
        # Check for error
        error = testcase.find('error')
        if error is not None:
            tc['status'] = 'ERROR'
            tc['error_message'] = error.get('message', '')
            tc['error_type'] = error.get('type', '')
            tc['error_text'] = error.text or ''
        
        # Check for skipped
        skipped = testcase.find('skipped')
        if skipped is not None:
            tc['status'] = 'SKIPPED'
        
        results['testcases'].append(tc)
    
    # Calculate pass rate
    results['passed'] = results['tests'] - results['failures'] - results['errors'] - results['skipped']
    results['pass_rate'] = (results['passed'] / results['tests'] * 100) if results['tests'] > 0 else 0
    
    return results

def parse_coverage_report(coverage_path: Path) -> dict:
    """Parse lcov coverage report (info file)."""
    if not coverage_path.exists():
        return {'line': 0, 'function': 0, 'branch': 0}
    
    coverage_text = coverage_path.read_text()
    
    # Extract coverage percentages from lcov.info summary
    line_coverage = 0.0
    branch_coverage = 0.0
    
    # Look for coverage percentages (simple parsing)
    import re
    line_match = re.search(r'lines\.+:\s*([\d.]+)%', coverage_text)
    if line_match:
        line_coverage = float(line_match.group(1))
    
    branch_match = re.search(r'branches\.+:\s*([\d.]+)%', coverage_text)
    if branch_match:
        branch_coverage = float(branch_match.group(1))
    
    return {
        'statement': line_coverage,
        'branch': branch_coverage,
        'condition': 0.0  # Condition coverage not typically in lcov
    }

def generate_executive_summary(results: dict, coverage: dict, sil: int) -> str:
    """Generate Executive Summary section."""
    overall_status = 'PASS' if results['failures'] == 0 and results['errors'] == 0 else 'FAIL'
    
    # Check coverage targets
    coverage_met = True
    if sil >= 3:
        if coverage['statement'] < 100 or coverage['branch'] < 100:
            coverage_met = False
    elif sil >= 2:
        if coverage['branch'] < 100:
            coverage_met = False
    
    recommendation = 'APPROVE FOR INTEGRATION' if overall_status == 'PASS' and coverage_met else 'REWORK REQUIRED'
    
    summary = f"""## 1. EXECUTIVE SUMMARY

### 1.1 Test Summary

**Test Execution Period**: {results['timestamp'][:10]} ([N] days)

**Test Result**: **{overall_status}**

**Overall Status**:
- **Test Cases Executed**: {results['tests']} of {results['tests']} (100%)
- **Test Cases Passed**: {results['passed']} ({results['pass_rate']:.1f}%)
- **Test Cases Failed**: {results['failures']} ({results['failures']/results['tests']*100 if results['tests'] > 0 else 0:.1f}%)
- **Test Cases Blocked**: {results['skipped']} ({results['skipped']/results['tests']*100 if results['tests'] > 0 else 0:.1f}%)
- **Coverage Achieved**: Statement {coverage['statement']:.1f}%, Branch {coverage['branch']:.1f}%, Condition {coverage['condition']:.1f}%
- **Coverage Target Met**: {'YES' if coverage_met else 'NO'}
- **Defects Found**: {results['failures'] + results['errors']} (Critical: [N], High: [N], Medium: [N], Low: [N])
- **Open Defects**: [N] (0 required for PASS)

**Recommendation**: {recommendation}
"""
    return summary

def generate_test_results_table(results: dict) -> str:
    """Generate test execution summary table."""
    table = """## 3. TEST EXECUTION SUMMARY

### 3.1 Test Execution Overview

| Module | Test Suite | Test Cases | Executed | Passed | Failed | Blocked | Pass Rate |
|--------|------------|-----------|----------|--------|--------|---------|-----------|
"""
    
    # Group test cases by module
    modules = {}
    for tc in results['testcases']:
        module = tc['classname'].split('.')[0] if tc['classname'] else 'unknown'
        if module not in modules:
            modules[module] = {'total': 0, 'passed': 0, 'failed': 0, 'skipped': 0}
        modules[module]['total'] += 1
        if tc['status'] == 'PASS':
            modules[module]['passed'] += 1
        elif tc['status'] in ['FAIL', 'ERROR']:
            modules[module]['failed'] += 1
        elif tc['status'] == 'SKIPPED':
            modules[module]['skipped'] += 1
    
    # Generate rows
    for module, stats in modules.items():
        pass_rate = (stats['passed'] / stats['total'] * 100) if stats['total'] > 0 else 0
        table += f"| {module} | test_{module}.c | {stats['total']} | {stats['total']} | {stats['passed']} | {stats['failed']} | {stats['skipped']} | {pass_rate:.0f}% |\n"
    
    # Total row
    table += f"| **TOTAL** | - | **{results['tests']}** | **{results['tests']}** | **{results['passed']}** | **{results['failures'] + results['errors']}** | **{results['skipped']}** | **{results['pass_rate']:.1f}%** |\n"
    
    return table

def generate_coverage_analysis(coverage: dict, sil: int) -> str:
    """Generate coverage analysis section."""
    target_statement = '100%' if sil >= 3 else 'HR'
    target_branch = '100%' if sil >= 2 else 'HR'
    target_condition = '100%' if sil >= 3 else 'R'
    
    statement_status = '✅ MET' if (sil >= 3 and coverage['statement'] >= 100) or sil < 3 else '❌ BELOW TARGET'
    branch_status = '✅ MET' if (sil >= 2 and coverage['branch'] >= 100) or sil < 2 else '❌ BELOW TARGET'
    condition_status = '✅ MET' if (sil >= 3 and coverage['condition'] >= 100) or sil < 3 else '⚠️ NOT MEASURED'
    
    section = f"""## 5. COVERAGE ANALYSIS

### 5.1 Overall Coverage

- **Statement**: {coverage['statement']:.1f}% (Target: {target_statement} for SIL {sil}) - {statement_status}
- **Branch**: {coverage['branch']:.1f}% (Target: {target_branch} for SIL {sil}) - {branch_status}
- **Condition**: {coverage['condition']:.1f}% (Target: {target_condition} for SIL {sil}) - {condition_status}

### 5.2 Uncovered Code

| File | Line | Reason |
|------|------|--------|
| [File] | [Lines] | [Justification for uncovered code] |

**Note**: Add justification for any uncovered code (defensive checks, error paths that cannot be tested, etc.)
"""
    return section

def main():
    if len(sys.argv) != 4:
        print("Usage: python3 generate_test_report.py <test-results.xml> <template.md> <output-report.md>")
        sys.exit(1)
    
    xml_path = Path(sys.argv[1])
    template_path = Path(sys.argv[2])
    output_path = Path(sys.argv[3])
    
    if not xml_path.exists():
        print(f"ERROR: Test results file '{xml_path}' not found")
        sys.exit(1)
    
    # Parse test results
    print(f"Parsing test results from {xml_path}...")
    results = parse_junit_xml(xml_path)
    
    # Parse coverage (optional)
    coverage_path = xml_path.parent / 'coverage.info'
    coverage = parse_coverage_report(coverage_path)
    
    # Generate report sections
    sil = 3  # Default SIL 3 (should be parameter)
    executive_summary = generate_executive_summary(results, coverage, sil)
    test_results_table = generate_test_results_table(results)
    coverage_analysis = generate_coverage_analysis(coverage, sil)
    
    # Load template
    if template_path.exists():
        template_content = template_path.read_text()
    else:
        # Generate from scratch
        template_content = "# Component Test Report\n\n"
    
    # Replace placeholders or append sections
    report_content = template_content
    report_content += "\n\n" + executive_summary
    report_content += "\n\n" + test_results_table
    report_content += "\n\n" + coverage_analysis
    
    # Write output
    output_path.write_text(report_content, encoding='utf-8')
    print(f"✅ Test report generated: {output_path}")
    print(f"   Tests: {results['passed']}/{results['tests']} passed ({results['pass_rate']:.1f}%)")
    print(f"   Coverage: Statement {coverage['statement']:.1f}%, Branch {coverage['branch']:.1f}%")

if __name__ == '__main__':
    main()
```

### 12.2 Coverage Report Parser

**Script: `parse_coverage_report.py`** (~150 lines)

**Purpose**: Parse lcov coverage output and validate against SIL requirements

```python
#!/usr/bin/env python3
"""
EN 50128 Coverage Report Parser and Validator

Parses lcov coverage.info and validates against SIL requirements.

Usage:
    python3 parse_coverage_report.py <coverage.info> <sil-level>

Example:
    python3 parse_coverage_report.py build/coverage.info 3
"""

import sys
import re
from pathlib import Path
from typing import Dict, List, Tuple

def parse_lcov_info(info_path: Path) -> Dict:
    """Parse lcov coverage.info file."""
    content = info_path.read_text()
    
    coverage = {
        'files': [],
        'summary': {
            'lines_found': 0,
            'lines_hit': 0,
            'functions_found': 0,
            'functions_hit': 0,
            'branches_found': 0,
            'branches_hit': 0
        }
    }
    
    current_file = None
    
    for line in content.splitlines():
        line = line.strip()
        
        if line.startswith('SF:'):
            # Source file
            current_file = {
                'name': line[3:],
                'lines_found': 0,
                'lines_hit': 0,
                'functions_found': 0,
                'functions_hit': 0,
                'branches_found': 0,
                'branches_hit': 0,
                'uncovered_lines': []
            }
            coverage['files'].append(current_file)
        
        elif line.startswith('FNF:'):
            # Functions found
            current_file['functions_found'] = int(line[4:])
            coverage['summary']['functions_found'] += int(line[4:])
        
        elif line.startswith('FNH:'):
            # Functions hit
            current_file['functions_hit'] = int(line[4:])
            coverage['summary']['functions_hit'] += int(line[4:])
        
        elif line.startswith('LF:'):
            # Lines found
            current_file['lines_found'] = int(line[3:])
            coverage['summary']['lines_found'] += int(line[3:])
        
        elif line.startswith('LH:'):
            # Lines hit
            current_file['lines_hit'] = int(line[3:])
            coverage['summary']['lines_hit'] += int(line[3:])
        
        elif line.startswith('BRF:'):
            # Branches found
            current_file['branches_found'] = int(line[4:])
            coverage['summary']['branches_found'] += int(line[4:])
        
        elif line.startswith('BRH:'):
            # Branches hit
            current_file['branches_hit'] = int(line[4:])
            coverage['summary']['branches_hit'] += int(line[4:])
        
        elif line.startswith('DA:'):
            # Line execution count
            parts = line[3:].split(',')
            line_num = int(parts[0])
            exec_count = int(parts[1])
            if exec_count == 0 and current_file:
                current_file['uncovered_lines'].append(line_num)
    
    # Calculate percentages
    s = coverage['summary']
    s['line_coverage'] = (s['lines_hit'] / s['lines_found'] * 100) if s['lines_found'] > 0 else 0
    s['function_coverage'] = (s['functions_hit'] / s['functions_found'] * 100) if s['functions_found'] > 0 else 0
    s['branch_coverage'] = (s['branches_hit'] / s['branches_found'] * 100) if s['branches_found'] > 0 else 0
    
    return coverage

def validate_coverage(coverage: Dict, sil: int) -> List[str]:
    """Validate coverage against SIL requirements."""
    errors = []
    s = coverage['summary']
    
    # SIL-specific requirements (Table A.21)
    if sil >= 3:
        # SIL 3-4: Statement, Branch, Condition = 100% (Mandatory)
        if s['line_coverage'] < 100.0:
            errors.append(f"Statement coverage {s['line_coverage']:.1f}% < 100% (SIL {sil} requirement)")
        if s['branch_coverage'] < 100.0:
            errors.append(f"Branch coverage {s['branch_coverage']:.1f}% < 100% (SIL {sil} requirement)")
        # Note: Condition coverage not typically in lcov, needs specialized tool
    
    elif sil == 2:
        # SIL 2: Branch = 100% (Mandatory), Statement = HR
        if s['branch_coverage'] < 100.0:
            errors.append(f"Branch coverage {s['branch_coverage']:.1f}% < 100% (SIL {sil} requirement)")
        if s['line_coverage'] < 90.0:
            errors.append(f"Statement coverage {s['line_coverage']:.1f}% < 90% (HR for SIL {sil})")
    
    else:
        # SIL 0-1: Statement, Branch = HR
        if s['line_coverage'] < 80.0:
            errors.append(f"Statement coverage {s['line_coverage']:.1f}% < 80% (HR for SIL {sil})")
        if s['branch_coverage'] < 80.0:
            errors.append(f"Branch coverage {s['branch_coverage']:.1f}% < 80% (HR for SIL {sil})")
    
    return errors

def print_coverage_report(coverage: Dict, sil: int):
    """Print coverage report."""
    s = coverage['summary']
    
    print(f"\n{'='*80}")
    print(f"EN 50128 Coverage Report")
    print(f"{'='*80}")
    print(f"SIL: {sil}")
    print(f"{'='*80}\n")
    
    print("Overall Coverage:")
    print(f"  Statement Coverage: {s['line_coverage']:.1f}% ({s['lines_hit']}/{s['lines_found']} lines)")
    print(f"  Function Coverage:  {s['function_coverage']:.1f}% ({s['functions_hit']}/{s['functions_found']} functions)")
    print(f"  Branch Coverage:    {s['branch_coverage']:.1f}% ({s['branches_hit']}/{s['branches_found']} branches)")
    print()
    
    # SIL requirements
    print(f"SIL {sil} Requirements (Table A.21):")
    if sil >= 3:
        print("  Statement: 100% (Mandatory)")
        print("  Branch: 100% (Mandatory)")
        print("  Condition: 100% (Mandatory)")
    elif sil == 2:
        print("  Statement: Highly Recommended (~90%)")
        print("  Branch: 100% (Mandatory)")
        print("  Condition: Recommended")
    else:
        print("  Statement: Highly Recommended (~80%)")
        print("  Branch: Highly Recommended (~80%)")
    print()
    
    # Validate
    errors = validate_coverage(coverage, sil)
    if errors:
        print(f"❌ VALIDATION FAILED: {len(errors)} issue(s)\n")
        for i, error in enumerate(errors, 1):
            print(f"  {i}. {error}")
    else:
        print("✅ VALIDATION PASSED: Coverage meets SIL requirements")
    
    # Files with low coverage
    print(f"\n{'='*80}")
    print("Files with Coverage < 100%:")
    print(f"{'='*80}\n")
    for file_cov in coverage['files']:
        if file_cov['lines_found'] > 0:
            file_line_cov = (file_cov['lines_hit'] / file_cov['lines_found'] * 100)
            if file_line_cov < 100.0:
                print(f"{file_cov['name']}:")
                print(f"  Statement: {file_line_cov:.1f}% ({file_cov['lines_hit']}/{file_cov['lines_found']} lines)")
                if file_cov['branches_found'] > 0:
                    file_branch_cov = (file_cov['branches_hit'] / file_cov['branches_found'] * 100)
                    print(f"  Branch: {file_branch_cov:.1f}% ({file_cov['branches_hit']}/{file_cov['branches_found']} branches)")
                if file_cov['uncovered_lines']:
                    print(f"  Uncovered lines: {', '.join(map(str, file_cov['uncovered_lines'][:10]))}")
                    if len(file_cov['uncovered_lines']) > 10:
                        print(f"    (and {len(file_cov['uncovered_lines']) - 10} more...)")
                print()
    
    print(f"{'='*80}\n")

def main():
    if len(sys.argv) != 3:
        print("Usage: python3 parse_coverage_report.py <coverage.info> <sil-level>")
        sys.exit(1)
    
    info_path = Path(sys.argv[1])
    sil = int(sys.argv[2])
    
    if not info_path.exists():
        print(f"ERROR: Coverage file '{info_path}' not found")
        sys.exit(1)
    
    if sil not in [0, 1, 2, 3, 4]:
        print(f"ERROR: Invalid SIL level '{sil}'")
        sys.exit(1)
    
    # Parse coverage
    coverage = parse_lcov_info(info_path)
    
    # Print report
    print_coverage_report(coverage, sil)
    
    # Exit with error if validation failed
    errors = validate_coverage(coverage, sil)
    sys.exit(1 if errors else 0)

if __name__ == '__main__':
    main()
```

**Usage:**
```bash
# Parse coverage and validate for SIL 3
python3 parse_coverage_report.py build/coverage.info 3
```

---

## 13. Complete Example Scenarios

### 13.1 Scenario 1: SIL 3 Component Testing (End-to-End)

**Context**: SIL 3 railway project, Phase 4 (Implementation complete), now performing component (unit) testing

**Step 1: Create Component Test Specification**

```bash
# Author (TST): Create test specification document
cp templates/Component-Test-Specification-template.md docs/Component-Test-Specification.md

# Edit document: fill in test cases for all modules
# - Module MOD-001: 50 test cases
# - Module MOD-002: 50 test cases
# - Module MOD-003: 50 test cases
# - Coverage targets: Statement 100%, Branch 100%, Condition 100%
# - Traceability: Link all test cases to requirements

# Validate document
python3 validate_test_doc_template.py \
  docs/Component-Test-Specification.md \
  test-specification \
  3

# Output: ✅ VALIDATION PASSED

# Submit for approval
workspace.py wf submit docs/Component-Test-Specification.md \
  --doc-type test-specification \
  --phase component-testing \
  --sil 3 \
  --author "Jane Doe (TST)"

# Output: Workflow WF-TEST-001 created, pending QUA review
```

**Step 2: QUA Review (Template Compliance)**

```bash
# QUA: Validate template compliance
python3 validate_test_doc_template.py \
  docs/Component-Test-Specification.md \
  test-specification \
  3

# QUA: Check traceability
workspace.py trace validate

# QUA: Approve
workspace.py wf approve docs/Component-Test-Specification.md \
  --role QUA \
  --approver "John Smith (QUA)" \
  --comments "Template compliance verified"

# Output: Approved, pending VER review
```

**Step 3: VER Review (Technical Correctness)**

```bash
# VER: Review test cases for completeness
# - All requirements covered?
# - Coverage targets correct for SIL 3?
# - Test cases have expected results?

# VER: Approve
workspace.py wf approve docs/Component-Test-Specification.md \
  --role VER \
  --approver "Alice Johnson (Independent VER)" \
  --comments "All requirements covered, coverage targets correct"

# Output: Approved, pending SAF review
```

**Step 4: SAF Review (Safety Requirements)**

```bash
# SAF: Review safety test cases
# - All safety requirements tested?
# - Fault injection tests included?
# - Defensive programming tested?

# SAF: Approve
workspace.py wf approve docs/Component-Test-Specification.md \
  --role SAF \
  --approver "Bob Wilson (SAF)" \
  --comments "Safety requirements covered, fault injection included"

# Output: Approved, pending PM approval
```

**Step 5: PM Approval and Baseline**

```bash
# PM: Final approval
workspace.py wf approve docs/Component-Test-Specification.md \
  --role PM \
  --approver "Charlie Brown (PM)"

# Output: APPROVED and BASELINED (v1.0)

# Git commit baseline
git add docs/Component-Test-Specification.md
git commit -m "Baseline Component Test Specification v1.0 (SIL 3)"
git push origin main
```

**Step 6: Execute Tests**

```bash
# TST: Execute all test suites
cd build
make test

# Output: 150 test cases, 148 PASS, 2 FAIL
# Generate JUnit XML results: build/test-results.xml

# TST: Measure coverage
make coverage

# Output: lcov generates build/coverage.info
#   Statement: 99.2%
#   Branch: 98.8%
```

**Step 7: Parse Coverage**

```bash
# TST: Parse coverage and validate
python3 parse_coverage_report.py build/coverage.info 3

# Output:
# ❌ VALIDATION FAILED: 2 issues
# 1. Statement coverage 99.2% < 100% (SIL 3 requirement)
# 2. Branch coverage 98.8% < 100% (SIL 3 requirement)
#
# Files with Coverage < 100%:
# src/module2.c:
#   Statement: 98.0% (196/200 lines)
#   Branch: 97.5% (39/40 branches)
#   Uncovered lines: 345, 346, 347, 348, 349, 350, 412
```

**Step 8: Generate Test Report**

```bash
# TST: Generate Test Report from results
python3 generate_test_report.py \
  build/test-results.xml \
  templates/Component-Test-Report-template.md \
  docs/Component-Test-Report.md

# TST: Edit report - add justification for uncovered code
# Lines 345-350: Defensive check for hardware fault (cannot test in unit test)
# Line 412: Error path for malloc failure (no dynamic memory used)

# TST: Submit Test Report
workspace.py wf submit docs/Component-Test-Report.md \
  --doc-type test-report \
  --phase component-testing \
  --sil 3 \
  --author "Jane Doe (TST)" \
  --description "Component testing complete, 148/150 passed, 1 open defect"

# Output: Workflow WF-TESTRPT-001 created, pending QUA review
# WARNING: Test result is FAIL (1 open High defect - DEFECT-045)
```

**Step 9: VER Reviews Test Report**

```bash
# VER: Review test results
# - Coverage: 99.2% statement, 98.8% branch (BELOW 100%)
# - Uncovered code justification: ACCEPTED (hardware-specific defensive code)
# - Failed tests: 2 (DEFECT-045, DEFECT-046)
# - DEFECT-046: FIXED in v1.2
# - DEFECT-045: OPEN (High severity - buffer overflow)

# VER: REJECT (1 open High defect)
workspace.py wf reject docs/Component-Test-Report.md \
  --role VER \
  --approver "Alice Johnson (Independent VER)" \
  --comments "REJECT: DEFECT-045 (High) must be fixed before integration. Coverage justification accepted."

# Output: REJECTED - rework required
```

**Step 10: Fix Defects and Re-Test**

```bash
# IMP: Fix DEFECT-045 (buffer overflow)
# Edit src/module2.c: Add buffer size check

# TST: Re-run tests
cd build
make test

# Output: 150 test cases, 150 PASS, 0 FAIL ✅

# TST: Re-measure coverage
make coverage

# Output: Statement: 99.5%, Branch: 99.2% (still below 100%, but justified)

# TST: Update Test Report
# - All tests now PASS
# - DEFECT-045: FIXED
# - Coverage: 99.5% statement, 99.2% branch (justification unchanged)

# TST: Re-submit Test Report
workspace.py wf submit docs/Component-Test-Report-v2.md \
  --doc-type test-report \
  --phase component-testing \
  --sil 3 \
  --author "Jane Doe (TST)"

# QUA + VER + VAL + PM approve
# Output: APPROVED ✅

# PM: Gate check PASS - proceed to integration
```

**Duration**: 2 weeks (1 week test spec, 1 week test execution and report)

---

### 13.2 Scenario 2: SIL 3 Verification Report Creation

**Context**: SIL 3 project, Phase 4 (Implementation) complete, VER performs verification activities

**Step 1: Static Analysis**

```bash
# VER: Run Cppcheck
cppcheck --enable=all --xml --xml-version=2 src/ 2> docs/verification/cppcheck_report.xml

# Output: 0 errors, 12 warnings (all justified)

# VER: Run Clang Static Analyzer
scan-build -o docs/verification/clang-analysis make

# Output: 0 issues found
```

**Step 2: MISRA C Compliance**

```bash
# VER: Run PC-lint Plus (MISRA C checker)
pclp64 -misra3 src/*.c > docs/verification/misra_report.txt

# Output:
# - Mandatory violations: 0 ✅
# - Required violations: 3 (with deviations)
# - Advisory violations: 15 (documented)
```

**Step 3: Complexity Analysis**

```bash
# VER: Run Lizard (complexity)
lizard src/ -o docs/verification/complexity_report.html

# Output:
# - All functions CCN ≤ 10 ✅
# - Average CCN: 4.2
# - Maximum CCN: 9 (function: process_state_machine)
```

**Step 4: Coverage Verification**

```bash
# VER: Parse coverage from Test Report
python3 parse_coverage_report.py build/coverage.info 3

# Output:
# - Statement: 99.5% (justified)
# - Branch: 99.2% (justified)
# - PASS (justification accepted)
```

**Step 5: Traceability Verification**

```bash
# VER: Validate complete traceability
workspace.py trace validate

# Output:
# ✅ PASS: All requirements traced to design, code, tests
# ✅ PASS: No orphan elements
```

**Step 6: Create Verification Report**

```bash
# VER: Create Verification Report
cp templates/Software-Verification-Report-template.md docs/Software-Verification-Report.md

# VER: Fill in all verification results
# - Static analysis: 0 errors, 12 warnings (justified)
# - MISRA C: 0 mandatory violations ✅
# - Complexity: All ≤ 10 ✅
# - Coverage: 99.5%/99.2% (justified) ✅
# - Traceability: 100% ✅
# - Non-conformances: 5 (all resolved)
# - Recommendation: APPROVE

# VER: Submit Verification Report
workspace.py wf submit docs/Software-Verification-Report.md \
  --doc-type verification-report \
  --phase verification \
  --sil 3 \
  --author "Alice Johnson (Independent VER)"

# Output: Workflow WF-VERRPT-001 created, pending QUA review
```

**Step 7: Approval Workflow**

```bash
# QUA: Template compliance check
python3 validate_test_doc_template.py \
  docs/Software-Verification-Report.md \
  verification-report \
  3
# Output: ✅ VALIDATION PASSED

workspace.py wf approve docs/Software-Verification-Report.md \
  --role QUA \
  --approver "John Smith (QUA)"

# VAL: Verification completeness review
workspace.py wf approve docs/Software-Verification-Report.md \
  --role VAL \
  --approver "David Lee (Independent VAL)" \
  --comments "All verification activities performed, evidence adequate"

# PM: Final approval
workspace.py wf approve docs/Software-Verification-Report.md \
  --role PM \
  --approver "Charlie Brown (PM)"

# Output: APPROVED ✅

# PM: Gate check - Phase 4 COMPLETE, proceed to Phase 5 (Integration)
```

**Duration**: 1 week verification activities, 3 days report creation and approval

---

## Summary

This workflow provides complete guidance for:

1. **Test Documentation** (Specifications and Reports for component, integration, system/validation levels)
2. **Verification Documentation** (Verification Plans and Reports)
3. **SIL-Specific Requirements** (Coverage, independence, approval by SIL 0-4)
4. **Traceability** (Requirements → Tests → Results using workspace.py)
5. **Tool Integration** (Document workflow with workspace.py wf)
6. **Automation** (Template validation, test report generation, coverage parsing)
7. **Complete Examples** (End-to-end scenarios for SIL 3 testing and verification)

All test and verification documents SHALL:
- Follow EN 50128-compliant templates
- Meet SIL-specific coverage requirements (Table A.21)
- Include complete traceability to requirements
- Undergo SIL-appropriate review and approval
- Be validated for template compliance before technical review
- Document all defects found with severity and status
- Provide clear pass/fail recommendations

**Key Tools:**
- `workspace.py wf` - Document submission and approval tracking
- `workspace.py trace` - Requirements-to-tests traceability
- `validate_test_doc_template.py` - Automated template validation
- `generate_test_report.py` - Automated test report generation from JUnit XML
- `parse_coverage_report.py` - Coverage parsing and SIL validation

**Next Steps After This Workflow:**
1. TST creates test specifications using templates
2. QUA validates template compliance
3. VER/VAL/PM approve test specifications
4. TST executes tests and generates test reports
5. VER reviews test results and performs verification activities
6. VER creates verification reports
7. VAL/PM approve and gate check (proceed or rework)
