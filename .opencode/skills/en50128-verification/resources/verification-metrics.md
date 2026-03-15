# Verification Metrics for EN 50128 Railway Safety Software

**Purpose**: Comprehensive catalog of verification metrics, measurement methods, calculation formulas, interpretation guidelines, and target values for EN 50128 compliant railway software verification.

**Scope**: Verification phase (Phase 5+) - metrics collection, analysis, interpretation, reporting

**Audience**: Verifiers (VER), V&V Managers (VMGR), Quality Assurance (QUA), Project Managers (PM)

**EN 50128 Reference**:
- Section 6.2 "Software Verification"
- Table A.5, Technique 6 "Metrics" (HR SIL 3-4, R SIL 2)
- Table A.19 "Static Analysis Techniques"
- Table A.21 "Test Coverage for Code"

**Related Documents**:
- `workflows/verification-reporting.md` - Verification report creation
- `resources/static-analysis-guidelines.md` - Tool configuration and thresholds
- `resources/verification-tools-reference.md` - Tool catalog with metric capabilities

---

## Table of Contents

1. [Metrics Overview](#1-metrics-overview)
2. [Complexity Metrics](#2-complexity-metrics)
3. [Coverage Metrics](#3-coverage-metrics)
4. [Defect Metrics](#4-defect-metrics)
5. [MISRA C Compliance Metrics](#5-misra-c-compliance-metrics)
6. [Traceability Metrics](#6-traceability-metrics)
7. [Code Quality Metrics](#7-code-quality-metrics)
8. [Verification Progress Metrics](#8-verification-progress-metrics)
9. [Tool Qualification Metrics](#9-tool-qualification-metrics)
10. [Safety Metrics](#10-safety-metrics)
11. [Industry Benchmarks](#11-industry-benchmarks)
12. [Metrics Dashboard Examples](#12-metrics-dashboard-examples)
13. [Metrics Collection Automation](#13-metrics-collection-automation)
14. [Metrics Reporting Templates](#14-metrics-reporting-templates)
15. [References](#15-references)

---

## 1. Metrics Overview

### 1.1 Purpose of Verification Metrics

Verification metrics provide **quantitative evidence** for:
- **Compliance**: Objective demonstration of EN 50128 requirements met
- **Progress**: Track verification activities completion
- **Quality**: Measure code quality against standards
- **Risk**: Identify high-risk areas requiring additional verification
- **Decision Support**: Provide data for gate check decisions (COD, VMGR)
- **Continuous Improvement**: Identify process improvement opportunities

**EN 50128 Requirement**: Table A.5, Technique 6 "Metrics"
- SIL 0-1: Recommended (R)
- SIL 2: Recommended (R)
- SIL 3-4: **Highly Recommended (HR)**

### 1.2 Metrics Categories

**Primary Metrics** (collected for all SIL levels):
1. **Complexity Metrics**: Cyclomatic Complexity (CCN), function length, nesting depth
2. **Coverage Metrics**: Statement, branch, condition, MC/DC coverage
3. **Defect Metrics**: Defect density, distribution by severity, resolution time
4. **MISRA C Metrics**: Rule compliance rate, violations by category
5. **Traceability Metrics**: Forward/backward trace completeness, coverage percentage

**Secondary Metrics** (SIL 3-4 recommended):
6. **Code Quality Metrics**: Maintainability Index, Technical Debt, Halstead metrics
7. **Verification Progress**: Activities complete, evidence collected, approvals obtained
8. **Safety Metrics**: Safety requirements coverage, hazard mitigation verification
9. **Tool Qualification**: Tool confidence level, qualification status

### 1.3 Metrics Collection Tools

| Metric Category | Primary Tool | Alternative Tool | Output Format |
|-----------------|--------------|------------------|---------------|
| **Complexity** | Lizard | PC-lint Plus, Clang | CSV, JSON, XML |
| **Coverage** | gcov/lcov | Bullseye | HTML, XML, JSON |
| **Defects** | Cppcheck, PC-lint Plus | Clang | XML, JSON, CSV |
| **MISRA C** | PC-lint Plus | Cppcheck MISRA addon | XML, JSON |
| **Code Quality** | SonarQube | CodeClimate, Lizard | JSON, XML |
| **Traceability** | Custom Python scripts | DOORS, ReqIF tools | CSV, JSON |

### 1.4 Metrics Collection Workflow

```
Phase Start
    │
    ├─ Baseline Metrics Collection
    │   └─ Establish starting point (t=0)
    │
    ├─ Periodic Metrics Collection (daily/weekly)
    │   ├─ Automated CI/CD collection
    │   ├─ Trend analysis
    │   └─ Early warning alerts
    │
    ├─ Gate Check Metrics Collection
    │   ├─ Comprehensive analysis
    │   ├─ Target vs. actual comparison
    │   └─ Compliance verification
    │
    └─ Phase Completion Metrics Report
        ├─ Final metrics snapshot
        ├─ Trends over phase
        └─ Lessons learned
```

---

## 2. Complexity Metrics

### 2.1 Cyclomatic Complexity Number (CCN)

**Definition**: Number of linearly independent paths through a function. Measures decision point complexity.

**Calculation**: 
```
CCN = E - N + 2P
Where:
  E = Number of edges in control flow graph
  N = Number of nodes in control flow graph
  P = Number of connected components (usually 1 for single function)

Simplified (for single function):
CCN = Number of decision points + 1
Decision points: if, for, while, case, &&, ||, ?:
```

**Alternate Formula** (practical):
```
CCN = 1 + count(if) + count(for) + count(while) + 
      count(case) + count(&&) + count(||) + count(?)
```

**EN 50128 Targets**:

| SIL Level | CCN Target | Requirement | Rationale |
|-----------|------------|-------------|-----------|
| **SIL 0-1** | ≤ 20 | Advisory | Maintainability, testability |
| **SIL 2** | ≤ 15 | Recommended | Improved testability, reduced defect probability |
| **SIL 3-4** | **≤ 10** | **Highly Recommended** | 100% coverage achievable, analyzable |

**Tool Command**:
```bash
# Lizard: CCN analysis
lizard -CCN 10 -w src/

# Output example:
# Function: calculate_braking_distance
# CCN: 8
# Lines: 45
# Tokens: 234
# Parameters: 3
```

**Interpretation**:

| CCN Range | Risk Level | Testability | Action |
|-----------|------------|-------------|--------|
| **1-5** | Low | Excellent | No action needed |
| **6-10** | Moderate | Good | Acceptable for SIL 3-4 |
| **11-15** | High | Fair | Refactor for SIL 3-4, acceptable for SIL 2 |
| **16-20** | Very High | Poor | Refactor for SIL 2+, acceptable for SIL 0-1 |
| **21+** | Extreme | Very Poor | MUST refactor for all SILs |

**Example**:

```c
/* Function with CCN = 8 */
error_t validate_input(const sensor_data_t* data)
{
    /* Decision 1 */ if (data == NULL) return ERROR_NULL;
    /* Decision 2 */ if (data->value < MIN) return ERROR_TOO_LOW;
    /* Decision 3 */ if (data->value > MAX) return ERROR_TOO_HIGH;
    /* Decision 4 */ if (data->timestamp < last_timestamp) return ERROR_OLD_DATA;
    /* Decision 5 */ if (data->checksum != calculate_checksum(data)) return ERROR_CHECKSUM;
    /* Decision 6 */ if (!data->valid) return ERROR_INVALID;
    /* Decision 7 */ if (data->sensor_id >= MAX_SENSORS) return ERROR_INVALID_ID;
    /* Decision 8 */ if (sensor_states[data->sensor_id] != ACTIVE) return ERROR_SENSOR_INACTIVE;
    
    return SUCCESS;
}
/* CCN = 8 (1 + 8 decisions) */
```

### 2.2 Function Length Metric

**Definition**: Number of lines of code in a function (excluding blank lines and comments).

**Calculation**:
```
Function Length = Count of non-blank, non-comment lines within function body
```

**EN 50128 Targets**:

| SIL Level | Max Lines | Requirement | Rationale |
|-----------|-----------|-------------|-----------|
| **SIL 0-1** | 200 | Advisory | General maintainability |
| **SIL 2** | 100 | Recommended | Improved comprehension |
| **SIL 3-4** | **50** | **Highly Recommended** | Reviewability, testability |

**Tool Command**:
```bash
# Lizard: Function length analysis
lizard -L 50 -w src/

# Output shows functions exceeding 50 lines
```

**Interpretation**:

| Length (LOC) | Comprehension | Defect Probability | Action |
|--------------|---------------|-------------------|--------|
| **1-25** | Excellent | Very Low | Ideal |
| **26-50** | Good | Low | Acceptable for SIL 3-4 |
| **51-100** | Fair | Moderate | Refactor for SIL 3-4, acceptable for SIL 2 |
| **101-200** | Poor | High | Refactor for SIL 2+, acceptable for SIL 0-1 |
| **201+** | Very Poor | Very High | MUST refactor for all SILs |

**Correlation**: Function length correlates with CCN (r ≈ 0.7-0.8). Long functions typically have high CCN.

### 2.3 Nesting Depth Metric

**Definition**: Maximum level of nested control structures (if, for, while) within a function.

**Calculation**:
```
Nesting Depth = Maximum depth of nested control structures

Example:
void function() {              // Depth 0
    if (condition1) {          // Depth 1
        while (condition2) {   // Depth 2
            if (condition3) {  // Depth 3
                for (...) {    // Depth 4
                    ...
                }
            }
        }
    }
}
// Max nesting depth = 4
```

**EN 50128 Targets**:

| SIL Level | Max Nesting Depth | Requirement | Rationale |
|-----------|-------------------|-------------|-----------|
| **SIL 0-1** | 5 | Advisory | Readability |
| **SIL 2** | 4 | Recommended | Improved comprehension |
| **SIL 3-4** | **3** | **Highly Recommended** | Reviewability, reduced defect probability |

**Tool Command**:
```bash
# Lizard: Nesting depth analysis
lizard -ND 3 -w src/

# PC-lint Plus: Nesting depth check
pclp64 +e{depth>3} src/*.c
```

**Interpretation**:

| Depth | Code Complexity | Cognitive Load | Action |
|-------|-----------------|----------------|--------|
| **0-1** | Simple | Very Low | Ideal |
| **2-3** | Moderate | Low | Acceptable for SIL 3-4 |
| **4** | Complex | Moderate | Refactor for SIL 3-4, acceptable for SIL 2 |
| **5** | Very Complex | High | Refactor for SIL 2+, limit for SIL 0-1 |
| **6+** | Extremely Complex | Very High | MUST refactor for all SILs |

**Refactoring Technique**: Extract inner loops/conditions into helper functions.

### 2.4 Parameter Count Metric

**Definition**: Number of parameters a function accepts.

**EN 50128 Targets**:

| SIL Level | Max Parameters | Requirement | Rationale |
|-----------|----------------|-------------|-----------|
| **SIL 0-1** | 7 | Advisory | Function signature complexity |
| **SIL 2** | 5 | Recommended | Reduced coupling |
| **SIL 3-4** | **4** | **Highly Recommended** | Testability, interface clarity |

**Tool Command**:
```bash
# Lizard: Parameter count analysis
lizard -arguments 4 -w src/
```

**Interpretation**:
- **1-3 parameters**: Ideal
- **4 parameters**: Acceptable for SIL 3-4
- **5 parameters**: Limit for SIL 2
- **6+ parameters**: Consider using structure to group related parameters

**Refactoring Example**:

```c
/* BEFORE: 6 parameters (exceeds limit) */
error_t create_train_route(uint32_t train_id, 
                           uint32_t route_id,
                           uint32_t start_station,
                           uint32_t end_station,
                           uint32_t departure_time,
                           uint32_t arrival_time);

/* AFTER: 2 parameters (within limit) */
typedef struct {
    uint32_t train_id;
    uint32_t route_id;
    uint32_t start_station;
    uint32_t end_station;
    uint32_t departure_time;
    uint32_t arrival_time;
} train_route_params_t;

error_t create_train_route(const train_route_params_t* params, 
                           route_handle_t* handle);
```

### 2.5 Complexity Metrics Summary

**Comprehensive Function Complexity Report Example**:

```
Module: brake_controller.c

Function Name                   CCN   Lines   Depth   Params   Status
----------------------------------------------------------------------
emergency_brake()                5     28      2       1       ✓ PASS
calculate_braking_distance()     8     45      3       3       ✓ PASS
apply_gradual_brake()           12     67      4       4       ✗ FAIL (CCN > 10)
check_brake_status()             3     15      1       2       ✓ PASS
validate_brake_inputs()          9     52      3       4       ✓ PASS

Module Summary:
  Total Functions: 5
  Functions Passing CCN ≤ 10: 4 (80%)
  Functions Failing: 1 (20%)
  Average CCN: 7.4
  Max CCN: 12 (apply_gradual_brake)
  
ACTION REQUIRED: Refactor apply_gradual_brake() to reduce CCN from 12 to ≤ 10
```

---

## 3. Coverage Metrics

### 3.1 Statement Coverage (C0)

**Definition**: Percentage of executable statements that have been executed at least once during testing.

**Calculation**:
```
Statement Coverage (%) = (Executed Statements / Total Executable Statements) × 100

Example:
Total statements: 1000
Executed statements: 950
Statement Coverage = (950 / 1000) × 100 = 95.0%
```

**EN 50128 Requirements** (Table A.21):

| SIL Level | Statement Coverage Target | Requirement | Notes |
|-----------|---------------------------|-------------|-------|
| **SIL 0** | ≥ 70% | Recommended | Basic testing |
| **SIL 1** | ≥ 85% | Highly Recommended | Good testing |
| **SIL 2** | ≥ 95% | Highly Recommended | Comprehensive testing |
| **SIL 3-4** | **100%** | **MANDATORY** | Every statement must execute |

**Tool Command**:
```bash
# gcov: Statement coverage measurement
gcc -fprofile-arcs -ftest-coverage src/module.c -o module_test
./module_test
gcov src/module.c

# lcov: HTML report generation
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_html

# Output example:
# Lines executed: 95.5% of 1234
```

**Interpretation**:

| Coverage | Quality Level | SIL 0-1 | SIL 2 | SIL 3-4 | Action |
|----------|---------------|---------|-------|---------|--------|
| **100%** | Excellent | ✓ Excellent | ✓ Excellent | ✓ REQUIRED | None |
| **95-99%** | Very Good | ✓ Good | ✓ Acceptable | ✗ FAIL | Add tests for uncovered statements |
| **85-94%** | Good | ✓ Acceptable | ✗ Insufficient | ✗ FAIL | Significant test additions needed |
| **70-84%** | Fair | ✓ Minimum | ✗ FAIL | ✗ FAIL | Major test additions needed |
| **< 70%** | Poor | ✗ Insufficient | ✗ FAIL | ✗ FAIL | Comprehensive test suite needed |

**Uncovered Statement Analysis**:
- **Defensive Code**: Error handlers that should never execute (still must be tested)
- **Dead Code**: Code that cannot execute (should be removed)
- **Incomplete Tests**: Missing test cases

**Example Report**:
```
File: train_controller.c
Statement Coverage: 98.5% (1347 / 1368 lines)

Uncovered Statements (21 lines):
  Line 234: return ERROR_HARDWARE_FAULT;  [Error handler - add fault injection test]
  Line 567: handle_impossible_state();    [Dead code? - investigate and remove]
  Line 892: log_critical("Sensor timeout"); [Timeout handler - add timeout test]
  ...
```

### 3.2 Branch Coverage (C1)

**Definition**: Percentage of decision branches (true/false outcomes) that have been executed at least once during testing.

**Calculation**:
```
Branch Coverage (%) = (Executed Branches / Total Branches) × 100

Example:
if (x > 0) {     // Branch 1: true
    ...          // Branch 2: false
}

Total branches: 2
Executed branches: 2 (both true and false tested)
Branch Coverage = (2 / 2) × 100 = 100%
```

**EN 50128 Requirements** (Table A.21):

| SIL Level | Branch Coverage Target | Requirement | Notes |
|-----------|------------------------|-------------|-------|
| **SIL 0** | ≥ 60% | Recommended | Basic decision testing |
| **SIL 1** | ≥ 75% | Highly Recommended | Good decision testing |
| **SIL 2** | ≥ 90%, **100%** | **MANDATORY** | All branches tested |
| **SIL 3-4** | **100%** | **MANDATORY** | Every branch must execute |

**Tool Command**:
```bash
# gcov: Branch coverage (--branch-counts flag)
gcov --branch-counts src/module.c

# lcov: Branch coverage in HTML report
genhtml coverage.info --branch-coverage --output-directory coverage_html

# Output example:
# Branches executed: 92.3% of 456
```

**Interpretation**:

| Coverage | Quality Level | SIL 0-1 | SIL 2 | SIL 3-4 | Action |
|----------|---------------|---------|-------|---------|--------|
| **100%** | Excellent | ✓ Excellent | ✓ REQUIRED | ✓ REQUIRED | None |
| **90-99%** | Very Good | ✓ Good | ✗ FAIL | ✗ FAIL | Add tests for uncovered branches |
| **75-89%** | Good | ✓ Acceptable | ✗ FAIL | ✗ FAIL | Significant test additions needed |
| **60-74%** | Fair | ✓ Minimum | ✗ FAIL | ✗ FAIL | Major test additions needed |
| **< 60%** | Poor | ✗ Insufficient | ✗ FAIL | ✗ FAIL | Comprehensive test suite needed |

**Branch Coverage Example**:

```c
/* Example function */
error_t process_sensor(sensor_data_t* data)
{
    if (data == NULL) {          // Branch A: true/false
        return ERROR_NULL;       // Branch A-true
    }
    
    if (data->value > MAX) {     // Branch B: true/false
        return ERROR_TOO_HIGH;   // Branch B-true
    } else if (data->value < MIN) {  // Branch C: true/false
        return ERROR_TOO_LOW;    // Branch C-true
    }
    
    return SUCCESS;              // Branch B-false AND C-false
}

/* Total branches: 6 (A-true, A-false, B-true, B-false, C-true, C-false) */
/* For 100% coverage, need tests that trigger all 6 branch outcomes */
```

### 3.3 Condition Coverage (C2)

**Definition**: Percentage of individual Boolean sub-expressions (conditions) that have been evaluated to both true and false during testing.

**Calculation**:
```
Condition Coverage (%) = (Evaluated Conditions / Total Conditions) × 100

Example:
if ((x > 0) && (y < 10)) {  // 2 conditions: (x > 0), (y < 10)
    ...
}

Total conditions: 2
Each condition must evaluate to true and false at least once.
Total condition outcomes: 4 (x>0: T/F, y<10: T/F)
```

**EN 50128 Requirements** (Table A.21):

| SIL Level | Condition Coverage Target | Requirement | Notes |
|-----------|---------------------------|-------------|-------|
| **SIL 0-1** | Not Required | - | Branch coverage sufficient |
| **SIL 2** | ≥ 90% | Recommended | Enhanced decision testing |
| **SIL 3-4** | **100%** | **MANDATORY** | Every condition outcome tested |

**Tool Command**:
```bash
# gcov: Condition coverage analysis
gcov --branch-counts --conditions src/module.c

# Bullseye (commercial): Condition coverage
covselect --file src/module.c
```

**Example**:

```c
/* Example with compound condition */
if ((speed > MAX_SPEED) || (brake_pressure < MIN_PRESSURE)) {
    emergency_stop();
}

/* Conditions:
 * C1: (speed > MAX_SPEED)
 * C2: (brake_pressure < MIN_PRESSURE)
 *
 * Test cases needed for 100% condition coverage:
 * Test 1: C1=true,  C2=true   (both conditions true)
 * Test 2: C1=true,  C2=false  (C1 true, C2 false)
 * Test 3: C1=false, C2=true   (C1 false, C2 true)
 * Test 4: C1=false, C2=false  (both conditions false)
 */
```

**Important Note**: Condition coverage is **stronger** than branch coverage. 100% condition coverage implies 100% branch coverage, but not vice versa.

### 3.4 Modified Condition/Decision Coverage (MC/DC)

**Definition**: A test coverage criterion requiring that each condition within a decision has been shown to independently affect the outcome of the decision.

**EN 50128 Requirement** (Table A.21):
- **SIL 3-4**: MC/DC **MANDATORY** (Table A.21 explicitly lists MC/DC)
- **SIL 2**: Highly Recommended
- **SIL 0-1**: Not Required

**MC/DC Requirements**:
1. Every condition in a decision takes on all possible outcomes at least once
2. Every decision takes on all possible outcomes at least once
3. Each condition is shown to independently affect the decision's outcome

**Calculation**:
```
MC/DC Coverage (%) = (MC/DC Pairs Executed / Total Required MC/DC Pairs) × 100

For a decision with N conditions, minimum N+1 test cases required
(vs. 2^N test cases for full truth table)
```

**Example**:

```c
/* Decision with 2 conditions */
if ((sensor_active) && (value_valid)) {
    process_data();
}

/* MC/DC Test Cases (minimum 3 for 2 conditions):
 * 
 * Test# | sensor_active | value_valid | Decision | Affects
 * ------|---------------|-------------|----------|--------
 * T1    | true          | true        | TRUE     | -
 * T2    | false         | true        | FALSE    | sensor_active (compare T1/T2)
 * T3    | true          | false       | FALSE    | value_valid (compare T1/T3)
 *
 * T2 shows sensor_active independently affects decision
 * T3 shows value_valid independently affects decision
 * MC/DC coverage: 100% (both conditions shown independent)
 */
```

**Tool Command**:
```bash
# Custom MC/DC analyzer (Python tool)
python3 tools/mcdc/mcdc_analyzer.py --source src/ --tests tests/

# Bullseye (commercial): MC/DC coverage
covselect --mc-dc --file src/module.c
```

**MC/DC Coverage Target**:
- **SIL 3-4**: **100% MC/DC coverage MANDATORY**
- **SIL 2**: ≥ 95% (highly recommended)
- **SIL 0-1**: Not required

**Tool Reference**: See `resources/verification-tools-reference.md` Section 9 for MC/DC analyzer usage.

### 3.5 Function Coverage

**Definition**: Percentage of functions that have been called at least once during testing.

**Calculation**:
```
Function Coverage (%) = (Called Functions / Total Functions) × 100
```

**EN 50128 Target**:
- **All SIL levels**: **100% function coverage** (implicit requirement)
- If a function exists, it must be tested

**Tool Command**:
```bash
# gcov: Function coverage
gcov --function-summaries src/module.c

# Output example:
# Functions executed: 98.5% of 67
```

**Interpretation**:
- **100%**: All functions tested (required)
- **< 100%**: Dead functions (should be removed) OR missing test cases

### 3.6 Coverage Metrics Summary

**Comprehensive Coverage Report Example**:

```
Project: Railway Signal Controller (SIL 3)
Coverage Report Date: 2026-03-13

Coverage Metric              Target   Actual   Status   Notes
----------------------------------------------------------------
Statement Coverage (C0)      100%     100.0%   ✓ PASS   All statements executed
Branch Coverage (C1)         100%     100.0%   ✓ PASS   All branches executed
Condition Coverage (C2)      100%      99.2%   ✗ FAIL   3 conditions not fully tested
MC/DC Coverage               100%      98.8%   ✗ FAIL   4 independence pairs missing
Function Coverage            100%     100.0%   ✓ PASS   All functions called

Overall Coverage Status: FAIL (MC/DC < 100%)

Uncovered Items:
  1. brake_controller.c:234 - Condition "(pressure > MAX) && (temp < LIMIT)"
     Missing: pressure=MAX+1, temp=LIMIT-1 test case
  2. signal_logic.c:567 - MC/DC pair for "(red || yellow) && green"
     Missing: Independent effect test for 'yellow' condition
  3. route_validator.c:890 - Condition "route->valid && route->active"
     Missing: route->valid=false, route->active=true test case
  4. ...

ACTION REQUIRED: Add 12 test cases to achieve 100% MC/DC coverage before VER approval.
```

---

## 4. Defect Metrics

### 4.1 Defect Density

**Definition**: Number of defects found per thousand lines of code (KLOC).

**Calculation**:
```
Defect Density = (Total Defects Found / Total Lines of Code) × 1000

Example:
Total defects: 45
Total LOC: 15,000
Defect Density = (45 / 15000) × 1000 = 3.0 defects/KLOC
```

**EN 50128 Targets** (based on industry benchmarks):

| SIL Level | Target Defect Density | Phase | Notes |
|-----------|-----------------------|-------|-------|
| **SIL 0-1** | < 5.0 defects/KLOC | Post-verification | Acceptable quality |
| **SIL 2** | < 2.0 defects/KLOC | Post-verification | Good quality |
| **SIL 3-4** | **< 0.5 defects/KLOC** | **Post-verification** | High quality required |
| **All SILs** | < 0.1 defects/KLOC | Post-validation (field) | Deployed software |

**Defect Density by Detection Phase**:

| Detection Phase | Typical Defect Density | SIL 3-4 Target |
|-----------------|------------------------|----------------|
| **Code Review** | 10-20 defects/KLOC | Find early, fix cheap |
| **Static Analysis** | 5-15 defects/KLOC | Automated detection |
| **Unit Testing** | 3-10 defects/KLOC | Developer testing |
| **Integration Testing** | 1-5 defects/KLOC | Component interaction |
| **System Testing** | 0.5-2 defects/KLOC | End-to-end testing |
| **Acceptance Testing** | **< 0.5 defects/KLOC** | **Pre-release target** |

**Interpretation**:

| Defect Density | Quality Assessment | SIL 3-4 Status | Action |
|----------------|--------------------|----------------|--------|
| **< 0.5 /KLOC** | Excellent | ✓ PASS | Ready for release |
| **0.5-2.0 /KLOC** | Good | ⚠ MARGINAL | Additional testing/analysis |
| **2.0-5.0 /KLOC** | Fair | ✗ FAIL | Significant quality improvement needed |
| **> 5.0 /KLOC** | Poor | ✗ FAIL | Major quality issues, re-development? |

### 4.2 Defect Distribution by Severity

**Definition**: Breakdown of defects by severity level (Critical, High, Medium, Low).

**Severity Definitions** (from `resources/common-verification-defects.md`):
- **Critical**: Undefined behavior, crash, safety hazard (MUST FIX for SIL 3-4)
- **High**: Incorrect behavior, data corruption (MUST FIX for SIL 3-4)
- **Medium**: Reliability, maintainability issues (SHOULD FIX)
- **Low**: Code quality, style issues (MAY FIX or document)

**EN 50128 Targets (SIL 3-4)**:

| Severity | Target (Post-Verification) | Requirement |
|----------|----------------------------|-------------|
| **Critical** | **0 defects** | **MANDATORY** |
| **High** | **0 defects** | **MANDATORY** |
| **Medium** | < 5 defects / KLOC | Highly Recommended |
| **Low** | < 10 defects / KLOC | Recommended |

**Defect Distribution Example**:

```
Module: brake_controller.c (2,345 LOC)

Severity Distribution:
  Critical:  0 defects (  0.0%)  ✓ Target: 0
  High:      2 defects (  1.2%)  ✗ Target: 0  [ACTION REQUIRED]
  Medium:    8 defects (  4.7%)  ✓ Target: < 5/KLOC (3.4/KLOC actual)
  Low:      15 defects (  8.8%)  ✓ Target: < 10/KLOC (6.4/KLOC actual)
  -------------------------
  Total:    25 defects (100.0%)  Defect Density: 10.7/KLOC

Outstanding High Severity Defects:
  1. Line 456: NULL pointer dereference in emergency_brake() [Cppcheck]
  2. Line 892: Buffer overflow in log_brake_event() [PC-lint Plus]

ACTION: Fix 2 High severity defects before VER approval.
```

### 4.3 Defect Detection Efficiency

**Definition**: Percentage of defects found in each phase of development.

**Calculation**:
```
Detection Efficiency (Phase X) = (Defects Found in Phase X / Total Defects) × 100
```

**Industry Benchmarks** (safety-critical software):

| Detection Phase | % of Total Defects | Cost to Fix | SIL 3-4 Goal |
|-----------------|-------------------|-------------|--------------|
| **Code Review** | 40-50% | Low | 50%+ |
| **Static Analysis** | 20-30% | Low | 30%+ |
| **Unit Testing** | 15-20% | Medium | 15% |
| **Integration Testing** | 10-15% | High | 5% |
| **System Testing** | 5-10% | Very High | < 5% |
| **Field** | < 1% | Extremely High | **0%** (none allowed) |

**Goal**: Shift defect detection LEFT (earlier phases = lower cost).

**Example Report**:

```
Project: Signal Controller (SIL 3)
Total Defects Found: 234

Phase                   Defects   % of Total   Cost/Defect   Total Cost
-------------------------------------------------------------------------
Code Review                115       49.1%        1x          115x
Static Analysis             68       29.1%        1x           68x
Unit Testing                32       13.7%        5x          160x
Integration Testing         15        6.4%       20x          300x
System Testing               4        1.7%       50x          200x
Field                        0        0.0%      500x            0x
-------------------------------------------------------------------------
Total                      234      100.0%                    843x

Analysis:
  - 78.2% defects found in low-cost phases (review + static analysis) ✓ EXCELLENT
  - 1.7% defects escaped to system testing (target < 5%) ✓ GOOD
  - 0% field defects ✓ EXCELLENT
  
Overall: Highly effective defect detection strategy.
```

### 4.4 Defect Resolution Time

**Definition**: Time from defect discovery to defect closure (fix verified).

**Calculation**:
```
Average Resolution Time = Sum(Closure Date - Discovery Date) / Number of Defects
```

**EN 50128 Targets** (SIL 3-4):

| Severity | Target Resolution Time | Notes |
|----------|------------------------|-------|
| **Critical** | < 24 hours | Immediate fix, block all other work |
| **High** | < 3 days | High priority, dedicated resources |
| **Medium** | < 1 week | Normal priority, scheduled fix |
| **Low** | < 2 weeks | Low priority, batch with other work |

**Metric Example**:

```
Defect Resolution Time Report (30-day period)

Severity    Count   Avg. Resolution   Min    Max    Target   Status
----------------------------------------------------------------------
Critical        3        8 hours       2h    18h    < 24h    ✓ PASS
High           12       2.3 days       1d     4d    < 3d     ✗ FAIL (1 defect took 4 days)
Medium         28       4.5 days       2d    10d    < 7d     ✓ PASS
Low            67      11.2 days       3d    25d    < 14d    ✓ PASS

Outliers:
  - High severity defect #H-0089 took 4 days (investigation complexity)
  - Low severity defect #L-0234 took 25 days (waiting for design clarification)

ACTION: Review High severity defect workflow to ensure < 3 day target met consistently.
```

### 4.5 Defect Closure Rate

**Definition**: Percentage of discovered defects that have been fixed and verified closed.

**Calculation**:
```
Defect Closure Rate (%) = (Closed Defects / Total Defects) × 100
```

**EN 50128 Gate Check Requirements**:

| Phase Gate | Defect Closure Target | SIL 3-4 Requirement |
|------------|----------------------|---------------------|
| **Implementation → Integration** | ≥ 95% | Critical/High: 100% |
| **Integration → Verification** | ≥ 98% | Critical/High: 100% |
| **Verification → Validation** | **100%** | **ALL defects closed** |
| **Validation → Deployment** | **100%** | **ALL defects closed** |

**Example Report**:

```
Defect Closure Status (Pre-Verification Gate Check)

Severity    Discovered   Closed   Open   Closure Rate   Target    Status
---------------------------------------------------------------------------
Critical            5        5       0      100.0%       100%     ✓ PASS
High               23       23       0      100.0%       100%     ✓ PASS
Medium             67       65       2       97.0%       ≥ 98%    ✗ FAIL
Low               134      128       6       95.5%       ≥ 95%    ✓ PASS
---------------------------------------------------------------------------
Total             229      221       8       96.5%       100%     ✗ FAIL

Open Defects (8 total):
  Medium (2):
    - M-0112: Code formatting inconsistency (fix in progress)
    - M-0145: Missing Doxygen comment (fix ready for review)
  Low (6):
    - L-0089: Variable naming style (scheduled for next sprint)
    - ... (5 more)

ACTION REQUIRED: Close 2 Medium severity defects before proceeding to Verification phase.
```

---

## 5. MISRA C Compliance Metrics

### 5.1 MISRA C Rule Compliance Rate

**Definition**: Percentage of MISRA C:2012 rules that have zero violations in the codebase.

**Calculation**:
```
Rule Compliance Rate (%) = (Rules with 0 Violations / Total Applicable Rules) × 100

Example:
Total applicable MISRA C rules: 178 (143 Mandatory + 35 Required/Advisory)
Rules with 0 violations: 165
Rule Compliance Rate = (165 / 178) × 100 = 92.7%
```

**EN 50128 Targets** (Table A.4, Technique 6 "Design and Coding Standards"):

| SIL Level | Mandatory Rules | Required Rules | Advisory Rules |
|-----------|-----------------|----------------|----------------|
| **SIL 0-1** | ≥ 95% compliance | ≥ 90% compliance | Best effort |
| **SIL 2** | **100% compliance** | ≥ 95% compliance | ≥ 90% compliance |
| **SIL 3-4** | **100% compliance** | **100% compliance** | ≥ 95% compliance |

**Important**: **Zero mandatory violations** required for SIL 2+ (no exceptions).

**Tool Command**:
```bash
# PC-lint Plus: MISRA C:2012 compliance check
pclp64 -vm \
       -os(misra_report.xml) \
       +ffn \
       -w3 \
       au-misra3.lnt \
       src/*.c

# Cppcheck MISRA addon:
cppcheck --addon=misra.json --xml --xml-version=2 src/ 2> misra_check.xml
```

**Example Report**:

```
MISRA C:2012 Compliance Report
Project: Signal Controller (SIL 3)

Rule Category              Total   0 Viol.   Compliance   Target   Status
---------------------------------------------------------------------------
Mandatory Rules (143)        143      143      100.0%      100%    ✓ PASS
Required Rules (10)           10       10      100.0%      100%    ✓ PASS
Advisory Rules (125)         125      118       94.4%      ≥ 95%   ✗ FAIL
---------------------------------------------------------------------------
Overall (178 rules)          178      171       96.1%      ≥ 98%   ✗ FAIL

Advisory Rules with Violations (7 rules):
  Rule 2.2: 12 violations - "Dead code detected"
  Rule 2.7: 8 violations - "Unused parameter in function"
  Rule 8.13: 15 violations - "Pointer parameter could be const"
  ...

ACTION REQUIRED: 
  - Fix 12 dead code instances (Rule 2.2)
  - Fix or justify 8 unused parameters (Rule 2.7)
  - Add const qualifier to 15 pointer parameters (Rule 8.13)
  - Achieve ≥ 95% Advisory rule compliance before VER approval
```

### 5.2 MISRA C Violation Density

**Definition**: Number of MISRA C violations per thousand lines of code.

**Calculation**:
```
MISRA Violation Density = (Total MISRA Violations / Total Lines of Code) × 1000

Example:
Total violations: 85
Total LOC: 15,000
Violation Density = (85 / 15000) × 1000 = 5.7 violations/KLOC
```

**EN 50128 Targets**:

| SIL Level | Violation Density Target | Notes |
|-----------|--------------------------|-------|
| **SIL 0-1** | < 10 violations/KLOC | Acceptable quality |
| **SIL 2** | < 2 violations/KLOC | Good quality (mandatory: 0) |
| **SIL 3-4** | **0 violations/KLOC (mandatory)** | **Zero mandatory violations** |

**Note**: For SIL 2+, **zero mandatory** violations required. Advisory violations should be minimized (< 2/KLOC).

### 5.3 MISRA C Deviation Rate

**Definition**: Percentage of MISRA C violations that have been formally approved as deviations.

**Calculation**:
```
Deviation Rate (%) = (Approved Deviations / Total Violations) × 100
```

**EN 50128 Requirements**:
- **SIL 3-4**: ALL mandatory rule violations require formal deviation with safety justification approved by CCB
- **SIL 2**: Mandatory rule violations require formal deviation
- **SIL 0-1**: Deviations recommended for significant violations

**Deviation Categories**:
1. **Project-wide deviation**: Rule not applicable to entire project (e.g., recursion rule if no recursion used)
2. **File-specific deviation**: Rule violation in specific file with justification
3. **Line-specific deviation**: Individual violation with detailed rationale

**Example Deviation Record**:

```
MISRA C Deviation Record

Deviation ID: DEV-MISRA-001
Rule: 11.3 (Required) - "A cast shall not be performed between pointer to object type and a different pointer to object type"
Severity: Required
Location: hardware_interface.c:234
Code: uint32_t* reg_ptr = (uint32_t*)HW_REGISTER_BASE;
Rationale: Hardware register access requires cast from fixed address to pointer. 
           No alternative available. Hardware interface layer isolated from safety logic.
Safety Impact: Low - Hardware interface tested extensively, no safety logic in this module.
Mitigation: Defensive checks on register values before use. Module isolated from safety-critical functions.
Approved By: Chief Designer (J. Smith), Safety Engineer (A. Johnson)
CCB Approval Date: 2026-02-15
Status: APPROVED

Total Deviations: 3 (all Required rules, 0 Mandatory rules)
```

---

## 6. Traceability Metrics

### 6.1 Forward Traceability Coverage

**Definition**: Percentage of requirements that have forward traces to design, code, and tests.

**Calculation**:
```
Forward Trace Coverage (%) = (Requirements with Forward Traces / Total Requirements) × 100

Example:
Total requirements: 150
Requirements with traces to design: 148
Requirements with traces to code: 147
Requirements with traces to tests: 150

Forward Trace Coverage (Design): (148/150) × 100 = 98.7%
Forward Trace Coverage (Code): (147/150) × 100 = 98.0%
Forward Trace Coverage (Tests): (150/150) × 100 = 100.0%
```

**EN 50128 Requirements** (Table A.5, Technique 7 "Traceability" - **MANDATORY SIL 3-4**):

| SIL Level | Forward Trace Target | Requirement |
|-----------|----------------------|-------------|
| **SIL 0-1** | ≥ 95% | Recommended |
| **SIL 2** | ≥ 98% | Highly Recommended |
| **SIL 3-4** | **100%** | **MANDATORY** |

**Special Requirement (SIL 3-4)**: **100% forward traceability for safety requirements** (no exceptions).

**Tool Command**:
```bash
# Validate forward traceability using workspace trace
workspace.py trace validate \
    --phase design,implementation,tests \
    --sil 3

# Check specific requirements coverage
workspace.py trace query \
    --source REQ-FUNC-001 \
    --direction forward \
    --matrix requirements_to_design,design_to_implementation,implementation_to_tests

# Generate comprehensive traceability report
workspace.py trace report \
    --from requirements \
    --to design,implementation,tests \
    --format markdown \
    --output reports/traceability/forward_trace_report.md

# Output format: Forward trace coverage percentages per phase
```

**Example Report**:

```
Forward Traceability Report
Project: Signal Controller (SIL 3)

Traceability Path                 Total   Traced   Coverage   Target   Status
------------------------------------------------------------------------------
Requirements → Design (SAS/SDS)     150      150     100.0%    100%    ✓ PASS
Requirements → Code (*.c)           150      150     100.0%    100%    ✓ PASS
Requirements → Unit Tests           150      150     100.0%    100%    ✓ PASS
Requirements → Integration Tests    150      148      98.7%    100%    ✗ FAIL
Requirements → System Tests         150      150     100.0%    100%    ✓ PASS

Safety Requirements (subset):
  Safety Req. → Design              45       45     100.0%    100%    ✓ PASS
  Safety Req. → Code                45       45     100.0%    100%    ✓ PASS
  Safety Req. → Tests               45       45     100.0%    100%    ✓ PASS

Missing Forward Traces (2):
  1. REQ-SIG-078 "Yellow signal warning duration" → No integration test found
  2. REQ-SIG-092 "Signal state transition logging" → No integration test found

ACTION REQUIRED: Add 2 integration test cases to achieve 100% forward traceability.
```

### 6.2 Backward Traceability Coverage

**Definition**: Percentage of design/code/test items that have backward traces to requirements.

**Calculation**:
```
Backward Trace Coverage (%) = (Items with Backward Traces / Total Items) × 100
```

**EN 50128 Target**:
- **SIL 3-4**: **100% backward traceability** (MANDATORY)
- **SIL 2**: ≥ 98%
- **SIL 0-1**: ≥ 95%

**Purpose**: Ensures no "gold plating" (features not required by specifications).

**Example Report**:

```
Backward Traceability Report

Item Type                 Total   Traced   Coverage   Target   Status
----------------------------------------------------------------------
Design Elements (SAS)        85       85     100.0%    100%    ✓ PASS
Design Elements (SDS)       234      234     100.0%    100%    ✓ PASS
Code Functions              156      154      98.7%    100%    ✗ FAIL
Test Cases                  423      423     100.0%    100%    ✓ PASS

Functions Missing Backward Traces (2):
  1. signal_state_to_string() in signal_controller.c:456
     Purpose: Debug logging helper function
     Action: Add trace to REQ-DBG-001 "Debug Logging" or remove if not needed
     
  2. calculate_display_brightness() in display_driver.c:892
     Purpose: Automatic brightness adjustment (not in requirements!)
     Action: Add requirement or remove function (gold plating)

ACTION REQUIRED: 
  - Add requirements for 2 functions OR remove functions before VER approval
  - 100% backward traceability mandatory for SIL 3-4
```

### 6.3 Traceability Gap Analysis

**Definition**: Identification of requirements without complete trace chains or orphaned design/code/test items.

**Traceability Gaps Types**:
1. **Missing Forward Trace**: Requirement exists but no design/code/test
2. **Missing Backward Trace**: Design/code/test exists but no requirement
3. **Broken Trace**: Trace link exists but target item deleted/moved
4. **Circular Trace**: Trace loop (requirement A → design B → requirement A)

**Example Report**:

```
Traceability Gap Analysis

Gap Type                Count   Severity   Action Required
----------------------------------------------------------
Missing Forward Trace       2    High      Add tests for REQ-SIG-078, REQ-SIG-092
Missing Backward Trace      2    High      Add requirements or remove functions
Broken Traces               5   Medium     Update trace links (design refactored)
Circular Traces             0    -         None

Details:

[1] Missing Forward Trace: REQ-SIG-078
    Requirement: "Yellow signal warning duration shall be 3-5 seconds"
    Design: ✓ SDS Section 4.2.3 "Signal Timing"
    Code: ✓ signal_timing.c:calculate_yellow_duration()
    Unit Test: ✓ test_signal_timing.c:test_yellow_duration()
    Integration Test: ✗ MISSING
    System Test: ✓ test_signal_sequences.c:test_yellow_to_red_transition()
    Action: Add integration test

[2] Missing Backward Trace: calculate_display_brightness()
    Function: display_driver.c:892
    Purpose: Automatic brightness adjustment based on ambient light
    Requirement: ✗ NOT FOUND
    Action: This appears to be "gold plating" (feature not in requirements).
            Either add requirement to SRS or remove function.

ACTION: Close 2 high-severity gaps before VER approval.
```

---

## 7. Code Quality Metrics

### 7.1 Maintainability Index

**Definition**: Composite metric measuring code maintainability based on complexity, size, and comments.

**Calculation** (Microsoft Visual Studio formula):
```
MI = 171 - 5.2 × ln(V) - 0.23 × G - 16.2 × ln(LOC)

Where:
  V = Halstead Volume
  G = Cyclomatic Complexity (CCN)
  LOC = Lines of Code
  
Normalized to 0-100 scale:
  MI = max(0, (MI × 100) / 171)
```

**Interpretation**:

| MI Score | Maintainability | Action |
|----------|-----------------|--------|
| **85-100** | Excellent | No action needed |
| **65-84** | Good | Acceptable |
| **50-64** | Moderate | Consider refactoring |
| **25-49** | Difficult | Refactor recommended |
| **0-24** | Very Difficult | Refactor required |

**EN 50128 Target**:
- **SIL 3-4**: MI ≥ 65 (good maintainability)
- **SIL 2**: MI ≥ 50
- **SIL 0-1**: MI ≥ 40

**Tool**: SonarQube, CodeClimate, or custom Halstead analyzer

### 7.2 Comment Density

**Definition**: Ratio of comment lines to code lines.

**Calculation**:
```
Comment Density (%) = (Comment Lines / (Code Lines + Comment Lines)) × 100

Example:
Code lines: 800
Comment lines: 200
Comment Density = (200 / 1000) × 100 = 20%
```

**EN 50128 Target**:
- **All SILs**: 15-30% comment density (optimal range)
- **< 10%**: Under-commented (insufficient documentation)
- **> 40%**: Over-commented (potentially redundant comments)

**Tool Command**:
```bash
# cloc: Count Lines of Code
cloc --by-file src/

# Output includes:
# Language  files  blank  comment  code
# C            45   1234     2345  9876
```

### 7.3 Documentation Coverage

**Definition**: Percentage of functions with complete Doxygen documentation.

**Required Documentation** (EN 50128 SIL 3-4):
- Function brief description
- Detailed description
- Parameter descriptions (`@param`)
- Return value description (`@return`)
- Pre-conditions (`@pre`)
- Post-conditions (`@post`)
- Safety considerations (`@safety`)

**Tool Command**:
```bash
# Doxygen: Generate documentation and warnings
doxygen Doxyfile 2>&1 | grep -i warning

# Custom checker:
python3 tools/check_documentation.py --source src/
```

**EN 50128 Target**:
- **SIL 3-4**: 100% functions documented (MANDATORY)
- **SIL 2**: ≥ 95%
- **SIL 0-1**: ≥ 85%

---

## 8. Verification Progress Metrics

### 8.1 Verification Activities Completion

**Definition**: Percentage of planned verification activities that have been completed.

**Verification Activities** (from Software Verification Plan):
1. Static analysis execution
2. Complexity analysis
3. MISRA C compliance check
4. Code review completion
5. Traceability verification
6. Coverage analysis
7. Verification report generation
8. QUA template compliance review
9. VMGR technical review
10. Defect closure verification

**Calculation**:
```
Activity Completion (%) = (Completed Activities / Total Planned Activities) × 100
```

**Example Report**:

```
Verification Progress Report
Phase: Implementation Verification (Phase 5)

Activity                          Status      Complete   Notes
----------------------------------------------------------------
1. Static Analysis (Cppcheck)     COMPLETE    100%       234 issues found, 234 fixed
2. Static Analysis (PC-lint)      COMPLETE    100%       156 issues found, 156 fixed
3. Static Analysis (Clang)        COMPLETE    100%       89 issues found, 89 fixed
4. Complexity Analysis (Lizard)   COMPLETE    100%       All functions CCN ≤ 10
5. MISRA C Compliance Check       COMPLETE    100%       0 mandatory violations
6. Code Review (QUA)              COMPLETE    100%       All files reviewed, approved
7. Traceability Verification      IN PROGRESS  95%       2 forward traces missing
8. Coverage Analysis              COMPLETE    100%       100% statement, branch, MC/DC
9. Verification Report Draft      IN PROGRESS  80%       Completing evidence section
10. QUA Template Review           PENDING       0%       Waiting for report completion
11. VMGR Technical Review         PENDING       0%       Waiting for QUA approval
12. Defect Closure Verification   COMPLETE    100%       All defects closed

Overall Progress: 80% (10 of 12 activities complete)

NEXT STEPS:
  1. Complete 2 missing forward traces (1 day)
  2. Complete verification report (2 days)
  3. Submit to QUA for template review (1 day)
  4. Address QUA feedback if any (1 day)
  5. Submit to VMGR for technical review (3 days)
  
Estimated completion: 8 days
```

### 8.2 Evidence Collection Completeness

**Definition**: Percentage of required evidence items that have been collected and documented.

**Required Evidence** (SIL 3-4):
- Static analysis reports (Cppcheck, PC-lint Plus, Clang, Lizard)
- Coverage reports (statement, branch, condition, MC/DC)
- MISRA C compliance report
- Code review records
- Traceability matrices
- Defect reports and closure records
- Tool qualification evidence (for T2/T3 tools)
- Review meeting minutes
- Approval signatures

**Calculation**:
```
Evidence Completeness (%) = (Evidence Items Collected / Total Required Evidence) × 100
```

---

## 9. Tool Qualification Metrics

### 9.1 Tool Confidence Level Distribution

**Definition**: Breakdown of verification tools by Tool Confidence Level (TCL).

**EN 50128 Tool Confidence Levels**:
- **TCL 1 (T1)**: Tool output manually verified - no qualification needed
- **TCL 2 (T2)**: Tool output used with increased confidence - validation required
- **TCL 3 (T3)**: Tool output used without independent verification - full qualification required

**Example Report**:

```
Tool Qualification Status

Tool Name            TCL   Qualification Status   Notes
---------------------------------------------------------
Cppcheck             T1    Not Required           Manual review of all findings
PC-lint Plus         T2    QUALIFIED              Vendor certification + validation testing
Clang Analyzer       T1    Not Required           Findings reviewed manually
Lizard               T1    Not Required           Metrics manually inspected
gcov/lcov            T2    IN PROGRESS            Validation suite 80% complete
GCC Compiler         T3    QUALIFIED              Certified toolchain v11.2
Unity Test Framework T2    QUALIFIED              Vendor docs + validation tests

Summary:
  T1 Tools: 3 (no qualification needed)
  T2 Tools: 3 (2 qualified, 1 in progress)
  T3 Tools: 1 (qualified)
  
ACTION REQUIRED: Complete gcov/lcov validation suite (20% remaining) before VER approval.
```

---

## 10. Safety Metrics

### 10.1 Safety Requirements Coverage

**Definition**: Percentage of safety requirements that have been implemented, tested, and verified.

**Calculation**:
```
Safety Req. Coverage (%) = (Verified Safety Requirements / Total Safety Requirements) × 100
```

**EN 50128 Target**:
- **SIL 3-4**: **100% safety requirements coverage** (MANDATORY, no exceptions)
- **SIL 2**: 100% (highly recommended)
- **SIL 0-1**: ≥ 98%

**Example Report**:

```
Safety Requirements Verification Status

Hazard Category          Total   Verified   Coverage   Target   Status
-----------------------------------------------------------------------
Emergency Braking           12       12      100.0%     100%    ✓ PASS
Signal State Transitions    23       23      100.0%     100%    ✓ PASS
Fault Detection             18       18      100.0%     100%    ✓ PASS
Fail-Safe Behavior          15       15      100.0%     100%    ✓ PASS
Redundancy & Voting          8        8      100.0%     100%    ✓ PASS
-----------------------------------------------------------------------
TOTAL Safety Requirements   76       76      100.0%     100%    ✓ PASS

All 76 safety requirements fully implemented, tested, and verified.
```

### 10.2 Hazard Mitigation Verification

**Definition**: Percentage of identified hazards that have verified mitigation measures.

**EN 50128 Target**:
- **All SILs**: **100% hazards mitigated** (MANDATORY)

**Example Report**:

```
Hazard Mitigation Verification

Hazard ID   Description                  Mitigation               Verified
-------------------------------------------------------------------------
H-001       Train overspeed              Speed limit enforcement  ✓ YES
H-002       Signal misread               Redundant signal logic   ✓ YES
H-003       Brake failure                Dual brake circuits      ✓ YES
H-004       Power loss                   Battery backup           ✓ YES
...
H-045       Communication timeout        Watchdog timer           ✓ YES

Total Hazards: 45
Mitigated: 45 (100%)
Verified: 45 (100%)

STATUS: ✓ PASS - All hazards mitigated and verified
```

---

## 11. Industry Benchmarks

### 11.1 Safety-Critical Software Benchmarks

**Source**: IEEE/IEC standards, EN 50128 projects, CENELEC railway industry data

| Metric | SIL 0-1 | SIL 2 | SIL 3-4 | World-Class |
|--------|---------|-------|---------|-------------|
| **Defect Density (post-verification)** | < 5.0 /KLOC | < 2.0 /KLOC | **< 0.5 /KLOC** | < 0.1 /KLOC |
| **Statement Coverage** | ≥ 85% | ≥ 95% | **100%** | 100% |
| **Branch Coverage** | ≥ 75% | **100%** | **100%** | 100% |
| **MC/DC Coverage** | N/A | ≥ 95% | **100%** | 100% |
| **CCN (max per function)** | ≤ 20 | ≤ 15 | **≤ 10** | ≤ 8 |
| **MISRA C Mandatory Violations** | < 1 /KLOC | **0** | **0** | 0 |
| **Traceability Coverage** | ≥ 95% | ≥ 98% | **100%** | 100% |
| **Code Review Coverage** | ≥ 80% | ≥ 95% | **100%** | 100% |

### 11.2 Development Productivity Benchmarks

| Metric | Average Team | High-Performance Team | Notes |
|--------|--------------|----------------------|-------|
| **Lines of Code per Day (SIL 3-4)** | 10-20 LOC | 20-40 LOC | Includes testing, review, doc |
| **Defects Introduced per KLOC** | 20-40 | 10-20 | Before verification |
| **Code Review Speed** | 150-200 LOC/hour | 200-300 LOC/hour | Thorough review |
| **Test Development Ratio** | 1:1 (test:prod) | 1.5:1 | More tests = higher quality |

---

## 12. Metrics Dashboard Examples

### 12.1 Project Overview Dashboard

```
═══════════════════════════════════════════════════════════════════
  EN 50128 VERIFICATION METRICS DASHBOARD
  Project: Railway Signal Controller (SIL 3)
  Date: 2026-03-13
  Phase: Implementation Verification (Phase 5)
═══════════════════════════════════════════════════════════════════

┌─ CODE METRICS ──────────────────────────────────────────────────┐
│  Total Lines of Code:        15,234 LOC                         │
│  Number of Functions:          156 functions                    │
│  Average Function Length:      24.3 LOC                  ✓ GOOD │
│  Average CCN:                   6.2                      ✓ GOOD │
│  Max CCN:                      10  (validate_route)     ✓ PASS │
└──────────────────────────────────────────────────────────────────┘

┌─ COVERAGE METRICS ──────────────────────────────────────────────┐
│  Statement Coverage:          100.0%  (1523/1523)       ✓ PASS │
│  Branch Coverage:             100.0%  (456/456)         ✓ PASS │
│  Condition Coverage:          100.0%  (892/892)         ✓ PASS │
│  MC/DC Coverage:              100.0%  (434/434)         ✓ PASS │
│  Function Coverage:           100.0%  (156/156)         ✓ PASS │
└──────────────────────────────────────────────────────────────────┘

┌─ DEFECT METRICS ────────────────────────────────────────────────┐
│  Total Defects Found:            234 defects                    │
│  Defect Density:              15.4 /KLOC  (initial)             │
│  Defect Density:               0.0 /KLOC  (current)     ✓ PASS │
│  Critical Defects:                 0                    ✓ PASS │
│  High Defects:                     0                    ✓ PASS │
│  Medium Defects:                   0                    ✓ PASS │
│  Low Defects:                      0                    ✓ PASS │
│  Defect Closure Rate:          100.0%                   ✓ PASS │
└──────────────────────────────────────────────────────────────────┘

┌─ MISRA C COMPLIANCE ────────────────────────────────────────────┐
│  Mandatory Rules (143):        100.0%  (0 violations)   ✓ PASS │
│  Required Rules (10):          100.0%  (0 violations)   ✓ PASS │
│  Advisory Rules (125):          96.8%  (4 violations)   ✓ PASS │
│  Overall Compliance:            99.8%  (4 total viol.)  ✓ PASS │
└──────────────────────────────────────────────────────────────────┘

┌─ TRACEABILITY ──────────────────────────────────────────────────┐
│  Req → Design:                100.0%  (150/150)         ✓ PASS │
│  Req → Code:                  100.0%  (150/150)         ✓ PASS │
│  Req → Tests:                 100.0%  (150/150)         ✓ PASS │
│  Safety Req Coverage:         100.0%  (45/45)          ✓ PASS │
└──────────────────────────────────────────────────────────────────┘

┌─ OVERALL STATUS ────────────────────────────────────────────────┐
│  Verification Progress:         100% COMPLETE                   │
│  Gate Check Status:             ✓ READY FOR VMGR APPROVAL      │
│  Estimated Completion:          2026-03-15 (2 days)            │
└──────────────────────────────────────────────────────────────────┘

═══════════════════════════════════════════════════════════════════
  ALL METRICS MEET SIL 3 REQUIREMENTS
  Ready for VMGR Technical Review
═══════════════════════════════════════════════════════════════════
```

---

## 13. Metrics Collection Automation

### 13.1 Automated Metrics Collection Script

**Script**: `tools/metrics/collect_all_metrics.sh`

```bash
#!/bin/bash
# Automated verification metrics collection
# Usage: ./collect_all_metrics.sh <sil_level> <output_dir>

SIL_LEVEL=$1
OUTPUT_DIR=$2
DATE=$(date +%Y-%m-%d)

echo "Collecting EN 50128 Verification Metrics (SIL ${SIL_LEVEL})..."

# 1. Complexity Metrics
echo "  [1/8] Complexity analysis..."
lizard -CCN 10 -L 50 -ND 3 --csv src/ > ${OUTPUT_DIR}/complexity_${DATE}.csv

# 2. Coverage Metrics
echo "  [2/8] Coverage analysis..."
lcov --capture --directory . --output-file ${OUTPUT_DIR}/coverage_${DATE}.info
genhtml ${OUTPUT_DIR}/coverage_${DATE}.info --output-directory ${OUTPUT_DIR}/coverage_html

# 3. Static Analysis (Cppcheck)
echo "  [3/8] Cppcheck analysis..."
cppcheck --enable=all --xml --xml-version=2 src/ 2> ${OUTPUT_DIR}/cppcheck_${DATE}.xml

# 4. MISRA C Compliance
echo "  [4/8] MISRA C compliance check..."
pclp64 -vm -os(${OUTPUT_DIR}/misra_${DATE}.xml) +ffn -w3 au-misra3.lnt src/*.c

# 5. Defect Metrics
echo "  [5/8] Defect metrics collection..."
python3 tools/metrics/extract_defect_metrics.py \
    --cppcheck ${OUTPUT_DIR}/cppcheck_${DATE}.xml \
    --pclint ${OUTPUT_DIR}/misra_${DATE}.xml \
    --output ${OUTPUT_DIR}/defects_${DATE}.csv

# 6. Traceability Metrics
echo "  [6/8] Traceability verification..."
workspace.py trace validate \
    --phase design,implementation,tests \
    --sil 3
workspace.py trace report \
    --from requirements \
    --to design,implementation,tests \
    --format json \
    --output ${OUTPUT_DIR}/traceability_${DATE}.json

# 7. Code Quality Metrics
echo "  [7/8] Code quality analysis..."
cloc --by-file --csv --out=${OUTPUT_DIR}/code_stats_${DATE}.csv src/

# 8. Generate Summary Report
echo "  [8/8] Generating metrics report..."
python3 tools/metrics/generate_metrics_report.py \
    --sil ${SIL_LEVEL} \
    --metrics-dir ${OUTPUT_DIR} \
    --output ${OUTPUT_DIR}/verification_metrics_report_${DATE}.html

echo "Metrics collection complete. Report: ${OUTPUT_DIR}/verification_metrics_report_${DATE}.html"
```

### 13.2 CI/CD Integration

**GitLab CI Example** (`.gitlab-ci.yml`):

```yaml
verification_metrics:
  stage: verify
  script:
    - ./tools/metrics/collect_all_metrics.sh 3 metrics_output/
    - python3 tools/metrics/check_gate_criteria.py --sil 3 --metrics metrics_output/
  artifacts:
    reports:
      metrics: metrics_output/verification_metrics_report_*.html
    when: always
  rules:
    - if: '$CI_COMMIT_BRANCH == "main"'
      when: always
```

---

## 14. Metrics Reporting Templates

### 14.1 Monthly Metrics Report Template

```markdown
# EN 50128 Verification Metrics Report

**Project**: [Project Name]
**SIL Level**: [0/1/2/3/4]
**Reporting Period**: [Month Year]
**Report Date**: [YYYY-MM-DD]
**Prepared By**: [VER/VMGR Name]

---

## 1. Executive Summary

[Brief overview of metrics status - 2-3 sentences]

**Overall Status**: ✓ ON TRACK / ⚠ AT RISK / ✗ OFF TRACK

**Key Highlights**:
- [Metric 1 achievement]
- [Metric 2 achievement]
- [Issue 1 if any]

---

## 2. Complexity Metrics

| Metric | Target | Actual | Status | Trend |
|--------|--------|--------|--------|-------|
| Average CCN | ≤ 10 | 6.8 | ✓ PASS | ↓ Improving |
| Max CCN | ≤ 10 | 10 | ✓ PASS | → Stable |
| Avg Function Length | ≤ 50 | 28.3 | ✓ PASS | ↓ Improving |

**Analysis**: [1-2 sentences]

---

## 3. Coverage Metrics

[Similar table for coverage]

---

[Continue for all metric categories]

---

## 10. Action Items

| Priority | Action | Owner | Due Date | Status |
|----------|--------|-------|----------|--------|
| P1 | Fix 2 High defects | IMP-Smith | 2026-03-15 | In Progress |
| P2 | Add 3 missing traces | REQ-Jones | 2026-03-18 | Not Started |

---

**Approval**:

Verifier: __________________ Date: __________
V&V Manager: __________________ Date: __________
```

---

## 15. References

### 15.1 EN 50128 Standard References

- **EN 50128:2011** - Railway applications - Communication, signalling and processing systems - Software for railway control and protection systems
  - Section 6.2: Software Verification
  - Table A.5: Software Verification techniques/measures
  - Table A.19: Static Analysis techniques
  - Table A.21: Test Coverage for Code

### 15.2 Related Skill Resources

- `workflows/verification-planning.md` - Verification planning workflow
- `workflows/static-analysis-workflow.md` - Static analysis execution
- `workflows/verification-reporting.md` - Verification report creation
- `resources/static-analysis-guidelines.md` - Tool configuration and thresholds
- `resources/verification-tools-reference.md` - Comprehensive tool catalog
- `resources/common-verification-defects.md` - Defect patterns and fixes

### 15.3 Tool Documentation

- **Lizard**: https://github.com/terryyin/lizard
- **gcov/lcov**: https://gcc.gnu.org/onlinedocs/gcc/Gcov.html
- **Cppcheck**: http://cppcheck.sourceforge.net/
- **PC-lint Plus**: https://www.gimpel.com/
- **SonarQube**: https://www.sonarqube.org/

---

**Document Control**:
- **Version**: 1.0
- **Date**: 2026-03-13
- **Author**: EN50128 Verification Skill Development Team
- **Status**: Active
- **Classification**: Internal - Project Reference

**Revision History**:
| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2026-03-13 | Verification Team | Initial release - comprehensive metrics catalog |

---

**End of Verification Metrics Resource**
