---
name: en50128-testing
description: Software testing methodologies with coverage analysis for EN 50128 C programs using Unity test framework
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  language: C
  test-framework: Unity
---

## What I do

I provide comprehensive testing methodologies and coverage analysis for EN 50128 Sections 7.4, 7.5, 7.6:
- Define coverage requirements by SIL (statement, branch, condition, MC/DC) per Table A.21
- Provide unit test patterns for C using Unity framework
- Guide integration testing strategies (bottom-up, top-down, sandwich)
- Apply black-box and white-box testing techniques (boundary value, equivalence class)
- Implement fault injection testing (HR SIL 3-4)
- Generate coverage reports with gcov/lcov and validate against SIL targets
- Ensure test traceability to requirements using `workspace.py trace`
- Automate coverage validation with `tools/check_coverage.py`

## When to use me

Use this skill when:
- **Writing unit tests** for C code modules (Section 7.4.4.8)
- **Performing integration testing** of software components (Section 7.6)
- **Analyzing code coverage** and validating against SIL requirements (Table A.21)
- **Implementing fault injection tests** (HR SIL 3-4)
- **Verifying test completeness** and traceability
- **Generating test reports** (Component Test Report, Integration Test Report)
- **Validating coverage targets** (100% statement/branch/condition for SIL 3-4)

## Testing Techniques (EN 50128 Table A.5)

**EN 50128 Sections 7.4, 7.5, 7.7, Table A.5** defines verification and testing techniques.

**Testing Techniques (subset of Table A.5):**

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 3 | **Dynamic Analysis and Testing** | Table A.13 | - | HR | **M** |
| 4 | **Test Coverage for Code** | Table A.21 | R | HR | **M** |
| 5 | **Functional and Black-Box Testing** | Table A.14 | HR | HR | **M** |
| 6 | **Performance Testing** | Table A.18 | - | HR | **M** |
| 8 | Interface Testing | D.34 | HR | HR | HR |

**Mandatory for SIL 3-4:**
- Dynamic Analysis and Testing (3) - **MANDATORY**
- Test Coverage for Code (4) - **MANDATORY** (see Table A.21 below)
- Functional and Black-Box Testing (5) - **MANDATORY**
- Performance Testing (6) - **MANDATORY**

**Key Points:**
- One or more techniques SHALL be selected per SIL level
- Testing must be performed by independent team for SIL 3-4
- Coverage requirements defined in Table A.21 below

**Standard Reference:** `std/EN50128-2011.md` Sections 7.4, 7.5, 7.7, Table A.5

## Test Coverage Requirements (EN 50128 Table A.21)

**EN 50128 Annex A, Table A.21** defines mandatory coverage levels:

| Coverage Type | SIL 0 | SIL 1-2 | SIL 3-4 |
|---------------|-------|---------|---------|
| **Statement Coverage** | HR | HR | **M** (100%) |
| **Branch Coverage** | HR | **M** (100%) | **M** (100%) |
| **Condition Coverage** | - | R | **M** (100%) |
| **Data Flow Coverage** | - | R | HR |
| **Path Coverage** | - | - | R |

**Coverage Requirements by SIL:**
- **SIL 0:** Statement (HR), Branch (HR)
- **SIL 1-2:** Statement (HR), Branch (**M** - 100%), Condition (R)
- **SIL 3-4:** Statement (**M** - 100%), Branch (**M** - 100%), Condition (**M** - 100%)

**Key Points:**
- **100% coverage required** for all mandatory coverage types
- Coverage measured at component level AND integration level
- Use gcov, lcov, Bullseye, or equivalent tools
- Document any uncovered code with justification
- Coverage reports SHALL be included in test reports

**Standard Reference:** `std/EN50128-2011.md` Annex A, Table A.21

## Coverage Requirements by SIL

## Testing Techniques by SIL

| Technique | SIL 0-1 | SIL 2 | SIL 3-4 |
|-----------|---------|-------|---------|
| Boundary Value Analysis | HR | HR | **M** |
| Equivalence Partitioning | HR | HR | HR |
| Control Flow Testing | HR | HR | **M** |
| Data Flow Testing | R | HR | HR |
| Fault Injection | R | HR | HR |
| Robustness Testing | R | HR | **M** (SIL 4) |

## Unity Test Framework Pattern

```c
// test_brake_controller.c
#include "brake_controller.h"
#include "unity.h"

void setUp(void) {
    brake_controller_init();
}

void tearDown(void) {
    brake_controller_shutdown();
}

// TC-UNIT-001: Normal brake application
void test_brake_normal_application(void) {
    // Arrange
    uint16_t speed = 100U;
    uint8_t brake_level;
    
    // Act
    error_t result = brake_controller_apply(speed, &brake_level);
    
    // Assert
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_TRUE(brake_level > 0U);
    TEST_ASSERT_TRUE(brake_level <= MAX_BRAKE_LEVEL);
}

// TC-UNIT-002: NULL pointer handling
void test_brake_null_pointer(void) {
    error_t result = brake_controller_apply(100U, NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
}

// TC-UNIT-003: Boundary value - minimum
void test_brake_minimum_speed(void) {
    uint8_t brake_level;
    error_t result = brake_controller_apply(0U, &brake_level);
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(0U, brake_level);
}

// TC-UNIT-004: Boundary value - maximum
void test_brake_maximum_speed(void) {
    uint8_t brake_level;
    error_t result = brake_controller_apply(MAX_SPEED, &brake_level);
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(MAX_BRAKE_LEVEL, brake_level);
}

// TC-UNIT-005: Invalid input
void test_brake_speed_too_high(void) {
    uint8_t brake_level;
    error_t result = brake_controller_apply(MAX_SPEED + 1U, &brake_level);
    TEST_ASSERT_EQUAL(ERROR_INVALID_SPEED, result);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_brake_normal_application);
    RUN_TEST(test_brake_null_pointer);
    RUN_TEST(test_brake_minimum_speed);
    RUN_TEST(test_brake_maximum_speed);
    RUN_TEST(test_brake_speed_too_high);
    
    return UNITY_END();
}
```

## Test Specification Template

```markdown
### Test Case: TC-[LEVEL]-[ID]

**Requirement**: REQ-[ID]
**SIL Level**: [0-4]
**Test Type**: [Functional|Performance|Boundary|Fault|Robustness]
**Priority**: [High|Medium|Low]

**Objective**: Verify [what is being tested]

**Preconditions**:
- System initialized
- [Other preconditions]

**Test Data**:
| Input | Expected Output | Expected Error |
|-------|----------------|----------------|
| value | result | status |

**Test Steps**:
1. Setup: [Initialization]
2. Execute: [Function call]
3. Verify: [Assertions]
4. Cleanup: [Resource release]

**Expected Result**: [Description]

**Pass Criteria**:
- All assertions pass
- No memory leaks
- Execution time < [limit]

**Status**: [Pass|Fail|Blocked]
```

## Coverage Analysis with gcov/lcov

### Build and Run with Coverage

```bash
# Compile with coverage flags
gcc -fprofile-arcs -ftest-coverage -g -O0 \
    -o test_brake \
    brake_controller.c test_brake_controller.c unity.c

# Run tests
./test_brake

# Generate coverage report
gcov brake_controller.c

# Generate HTML report
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_html
```

### Python Coverage Analysis Script

```python
#!/usr/bin/env python3
"""
Coverage analysis for EN 50128 compliance
"""

import subprocess
import sys

def analyze_coverage(source_file, sil_level):
    """Check coverage against SIL requirements"""
    
    # Run gcov
    result = subprocess.run(['gcov', source_file], 
                          capture_output=True, text=True)
    
    # Parse coverage (simplified)
    # In production, parse actual gcov output
    
    requirements = {
        0: {'statement': 0, 'branch': 0},
        1: {'statement': 80, 'branch': 70},
        2: {'statement': 100, 'branch': 100},
        3: {'statement': 100, 'branch': 100, 'condition': 100},
        4: {'statement': 100, 'branch': 100, 'condition': 100}
    }
    
    print(f"Coverage Analysis for SIL {sil_level}")
    print(f"Required: {requirements[sil_level]}")
    
    return True

if __name__ == "__main__":
    analyze_coverage(sys.argv[1], int(sys.argv[2]))
```

## Boundary Value Testing

```c
void test_all_boundaries(void) {
    // Test min-1, min, min+1, max-1, max, max+1
    
    test_cases_t cases[] = {
        {MIN_VALUE - 1, ERROR_OUT_OF_RANGE},
        {MIN_VALUE, SUCCESS},
        {MIN_VALUE + 1, SUCCESS},
        {MAX_VALUE - 1, SUCCESS},
        {MAX_VALUE, SUCCESS},
        {MAX_VALUE + 1, ERROR_OUT_OF_RANGE}
    };
    
    for (size_t i = 0; i < ARRAY_SIZE(cases); i++) {
        error_t result = function_under_test(cases[i].input);
        TEST_ASSERT_EQUAL(cases[i].expected, result);
    }
}
```

## Fault Injection Testing

```c
typedef enum {
    FAULT_NONE,
    FAULT_NULL_POINTER,
    FAULT_TIMEOUT,
    FAULT_SENSOR_STUCK
} fault_type_t;

void inject_fault(const char* component, fault_type_t fault);

void test_handle_sensor_fault(void) {
    // Inject fault
    inject_fault("speed_sensor", FAULT_SENSOR_STUCK);
    
    // System should detect and handle
    system_tick();
    
    // Verify safe state
    TEST_ASSERT_EQUAL(STATE_SAFE, system_get_state());
}
```

## Integration Testing

```c
// test_integration_brake_sensor.c

void test_brake_responds_to_speed(void) {
    // Setup
    speed_sensor_init();
    brake_controller_init();
    
    // Simulate high speed
    speed_sensor_set_value(250U);
    
    // Process
    system_tick();
    
    // Verify brake applied
    uint8_t brake_level = brake_controller_get_level();
    TEST_ASSERT_TRUE(brake_level > 0U);
}

void test_emergency_on_sensor_failure(void) {
    // Setup
    speed_sensor_init();
    brake_controller_init();
    
    // Inject sensor failure
    speed_sensor_inject_fault(FAULT_DISCONNECTED);
    
    // Process
    system_tick();
    
    // Verify safe state
    TEST_ASSERT_EQUAL(STATE_SAFE, system_get_state());
    TEST_ASSERT_TRUE(is_emergency_brake_active());
}
```

## Python Test Harness

```python
#!/usr/bin/env python3
"""
Test harness for automated test execution
"""

import subprocess
import json

class TestHarness:
    def __init__(self, sil_level):
        self.sil_level = sil_level
        self.results = []
    
    def run_unit_tests(self):
        """Execute all unit tests"""
        tests = self.discover_tests('tests/unit')
        
        for test in tests:
            result = subprocess.run([test], capture_output=True)
            self.results.append({
                'test': test,
                'status': 'PASS' if result.returncode == 0 else 'FAIL'
            })
    
    def check_coverage(self):
        """Verify coverage requirements"""
        subprocess.run(['./analyze_coverage.py', 'src/', str(self.sil_level)])
    
    def generate_report(self):
        """Generate test report"""
        summary = {
            'total': len(self.results),
            'passed': sum(1 for r in self.results if r['status'] == 'PASS')
        }
        
        with open('test_report.json', 'w') as f:
            json.dump({'summary': summary, 'results': self.results}, f)
```

## Test Traceability Matrix

| Requirement | Design | Code | Test Cases | Status |
|-------------|--------|------|------------|--------|
| REQ-FUNC-001 | DES-MOD-005 | brake.c | TC-UNIT-001, TC-UNIT-002 | PASS |
| REQ-SAFE-010 | DES-SAFE-002 | emergency.c | TC-UNIT-006, TC-INT-002 | PASS |

## Test Review Checklist

- [ ] All requirements have test cases
- [ ] Coverage targets achieved (per SIL)
- [ ] All boundary values tested
- [ ] Error conditions tested
- [ ] Fault injection performed (SIL 3-4)
- [ ] Performance requirements verified
- [ ] Test results documented
- [ ] Traceability maintained

## Comprehensive Workflows

This skill provides **3 comprehensive workflows** covering the complete testing lifecycle:

### 1. Unit Testing Workflow (`workflows/unit-testing-workflow.md`)

**EN 50128 Reference**: Section 7.4.4.8, Table A.5, Table A.21  
**Coverage**: Unit test development, execution, and validation

**Key Topics**:
- Unit test structure (Unity framework)
- Test types: Normal, boundary value, error handling, fault injection, robustness
- Coverage measurement (statement, branch, condition)
- Mock object creation for hardware abstraction
- Defect management and regression testing
- Automated test execution with CI/CD integration

**Example Usage**:
```bash
# Build unit tests with coverage
cd tests/unit
make coverage

# Run tests
./test_brake_controller

# Generate coverage report
gcov ../../src/brake_controller.c
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory ../coverage

# Validate coverage against SIL requirements
python3 ../../tools/check_coverage.py --sil 3 --coverage coverage.json

# Update traceability
workspace.py trace create --from tests --to requirements \
    --source-id TC-BRAKE-APPLY-001 --target-id REQ-FUNC-010

workspace.py trace validate --phase testing --sil 3
```

---

### 2. Integration Testing Workflow (`workflows/integration-testing-workflow.md`)

**EN 50128 Reference**: Section 7.6, Table A.6  
**Coverage**: Component integration, HW/SW integration, interface testing

**Key Topics**:
- Integration strategies: Bottom-up, top-down, sandwich
- Interface testing (function calls, data structures, IPC)
- Data flow and control flow testing
- Resource sharing and concurrent access testing
- Timing and performance testing (HR SIL 3-4)
- Fault propagation testing
- Hardware-in-the-loop (HIL) testing

**Example Usage**:
```bash
# Build integration tests
cd tests/integration
make run

# Execute integration tests
./test_brake_speed_integration

# Generate integration coverage
make coverage

# Combine unit + integration coverage
lcov --add-tracefile ../unit/coverage.info \
     --add-tracefile ./coverage.info \
     --output-file ../combined_coverage.info

# Analyze performance
python3 ../../tools/analyze_performance.py \
    --results test_results.log \
    --output ../reports/performance_analysis.md
```

---

### 3. Coverage Analysis Workflow (`workflows/coverage-analysis-workflow.md`)

**EN 50128 Reference**: Table A.21 (Test Coverage for Code)  
**Coverage**: Statement, branch, condition, MC/DC coverage analysis

**Key Topics**:
- Coverage types: Statement, branch, condition, MC/DC, data flow, path
- Coverage measurement with gcov, lcov, gcovr
- SIL-specific validation (100% coverage for SIL 3-4)
- Uncovered code identification and justification
- MC/DC analysis (HR SIL 3-4)
- Automated coverage validation

**Example Usage**:
```bash
# Compile with coverage instrumentation
gcc -fprofile-arcs -ftest-coverage -g -O0 -o test_executable src/module.c test/test_module.c

# Run tests
./test_executable

# Generate HTML coverage report
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_html

# Validate coverage against SIL 3 requirements
python3 tools/check_coverage.py \
    --sil 3 \
    --coverage coverage.json \
    --threshold statement:100,branch:100,condition:100

# Perform MC/DC analysis (SIL 3-4)
python3 tools/mcdc/mcdc_analyzer.py \
    --source src/module.c \
    --coverage coverage.info \
    --output evidence/mcdc/module_mcdc.json
```

---

## Coverage Requirements by SIL (Table A.21)

**EN 50128 Table A.21** defines mandatory coverage levels:

| Coverage Type | SIL 0 | SIL 1-2 | SIL 3-4 | Tool Support |
|---------------|-------|---------|---------|--------------|
| **Statement Coverage** | HR | HR | **M** (100%) | gcov, lcov, gcovr |
| **Branch Coverage** | HR | **M** (100%) | **M** (100%) | gcov --branch-probabilities |
| **Condition Coverage** | - | R | **M** (100%) | gcov + custom analysis |
| **Data Flow Coverage** | - | R | HR | Manual analysis |
| **MC/DC Coverage** | - | - | HR (100%) | tools/mcdc/mcdc_analyzer.py, Bullseye |
| **Path Coverage** | - | - | R | Manual analysis |

**Key Points**:
- **SIL 0-1**: Statement (HR), Branch (HR) - Target 80%+
- **SIL 2**: Branch (**MANDATORY** 100%), Statement (HR 95%+)
- **SIL 3-4**: Statement + Branch + Condition (**ALL MANDATORY** 100%)
- **MC/DC**: HIGHLY RECOMMENDED for SIL 3-4 (100% target)
- **Uncovered code**: Requires documented justification for SIL 2+

**Standard Reference**: `std/EN50128-2011.md` Annex A, Table A.21

---

## Tool Integration

### Coverage Tools (Working Implementations)

**gcov** (Statement + Branch):
```bash
# Compile with coverage flags
gcc -fprofile-arcs -ftest-coverage -g -O0 -o test src/module.c test/test_module.c

# Run tests
./test

# Generate text coverage report
gcov src/module.c

# Output: module.c.gcov (line-by-line execution counts)
```

**lcov** (HTML Reports):
```bash
# Capture coverage data
lcov --capture --directory . --output-file coverage.info

# Filter system headers
lcov --remove coverage.info '/usr/*' 'tests/*' --output-file coverage_filtered.info

# Generate HTML report
genhtml coverage_filtered.info --output-directory coverage_html

# View in browser
firefox coverage_html/index.html &
```

**gcovr** (JSON/XML Reports):
```bash
# Generate machine-readable JSON report
gcovr --json --output coverage.json

# Generate Cobertura XML (for CI/CD)
gcovr --xml --output coverage.xml
```

**Custom Validation** (SIL Requirements):
```bash
# Validate coverage against SIL 3 requirements
python3 tools/check_coverage.py \
    --sil 3 \
    --coverage coverage.json \
    --report evidence/coverage/validation_report.json

# Output:
# Statement Coverage: 100.0% [PASS]
# Branch Coverage:    100.0% [PASS]
# Condition Coverage: 100.0% [PASS]
# Result: PASS - All coverage targets met
```

---

### Traceability Integration (Working Implementation)

**Link Tests to Requirements**:
```bash
# Create traceability link
workspace.py trace create \
    --from tests \
    --to requirements \
    --source-id TC-BRAKE-APPLY-001 \
    --target-id REQ-FUNC-010 \
    --rationale "Unit test verifies normal brake application"

# Validate traceability completeness
workspace.py trace validate --phase testing --sil 3

# Generate traceability report
workspace.py trace report \
    --from requirements \
    --to tests \
    --format markdown \
    --output evidence/traceability/requirements_to_tests.md
```

---

## Test Templates

The skill includes **4 comprehensive test templates** (already present):

1. **Component Test Specification** (`templates/Component-Test-Specification-template.md`)
   - Purpose: Define unit test cases before testing
   - Content: Test cases, procedures, expected results, coverage targets
   - Sections: Test organization, test cases, coverage analysis, traceability

2. **Component Test Report** (`templates/Component-Test-Report-template.md`)
   - Purpose: Document unit test execution results
   - Content: Test results, coverage metrics, defects, evidence
   - Approval: TST, QA, Verifier (SIL 3-4)

3. **Overall Software Test Specification** (`templates/Overall-Software-Test-Specification-template.md`)
   - Purpose: Define system-level test cases
   - Content: System test procedures, validation test cases

4. **Overall Software Test Report** (`templates/Overall-Software-Test-Report-template.md`)
   - Purpose: Document system test execution
   - Content: System test results, validation evidence

---

## References
- **EN 50128:2011**
  - Section 7.4.4.8 - Component Testing
  - Section 7.5 - Integration (Component and Hardware/Software Integration)
  - Section 7.6 - Software Integration
  - Table A.5 - Verification and Testing Techniques
  - Table A.6 - Integration Techniques
  - Table A.13 - Dynamic Analysis and Testing
  - Table A.14 - Functional and Black-Box Testing
  - Table A.18 - Performance Testing
  - Table A.21 - Test Coverage for Code
- **Standard Location**: `std/EN50128-2011.md`
- **TOOLS.md**: Tool catalog (gcov, lcov, gcovr, Bullseye, Unity)
- **Unity Test Framework**: https://github.com/ThrowTheSwitch/Unity
- **Related Skills**: 
  - `en50128-implementation` (code under test)
  - `en50128-verification` (independent verification of test results)
  - `en50128-integration` (integration activities)
