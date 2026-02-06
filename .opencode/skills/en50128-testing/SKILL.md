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

I provide testing methodologies and coverage requirements for EN 50128 Sections 7.4 and 7.5:
- Define coverage requirements by SIL (statement, branch, condition, MC/DC)
- Provide unit test patterns for C using Unity framework
- Apply black-box and white-box testing techniques
- Implement fault injection testing
- Generate coverage reports with gcov/lcov
- Ensure test traceability to requirements

## When to use me

Use this skill when:
- Writing unit tests for C code
- Performing integration testing
- Analyzing code coverage
- Implementing fault injection tests
- Verifying test completeness
- Generating test reports

## Coverage Requirements by SIL (EN 50128 Table A.5)

| Coverage Type | SIL 0-1 | SIL 2 | SIL 3-4 |
|---------------|---------|-------|---------|
| Statement Coverage | HR | HR | **M** (100%) |
| Branch Coverage | HR | **M** (100%) | **M** (100%) |
| Condition Coverage | R | HR | **M** (100%) |
| MC/DC Coverage | - | R | HR (100%) |

**M**=Mandatory, **HR**=Highly Recommended, **R**=Recommended

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

## References
- EN 50128:2011 Section 7.4 (Component Testing)
- EN 50128:2011 Section 7.5 (Integration Testing)
- EN 50128:2011 Table A.5 (Testing Techniques)
- Unity Test Framework Documentation
