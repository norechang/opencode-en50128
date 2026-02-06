# Test Directory

Unit tests and integration tests for EN 50128 railway software.

## Purpose

Contains all test code, test harnesses, and test utilities.

## Testing Requirements by SIL

### SIL 0-1
- Statement coverage: 80-90%
- Branch coverage: 70-80%

### SIL 2
- Statement coverage: 100%
- Branch coverage: 100%

### SIL 3-4
- Statement coverage: 100%
- Branch coverage: 100%
- Condition coverage (MC/DC): 100%

## Test Framework

Use **Unity** test framework for C:

```c
#include "unity.h"
#include "component_under_test.h"

void setUp(void) {
    // Setup before each test
}

void tearDown(void) {
    // Cleanup after each test
}

void test_normal_operation(void) {
    // Arrange
    input_t input = {.value = 100};
    output_t output;
    
    // Act
    error_t result = component_process(&input, &output);
    
    // Assert
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(100, output.value);
}

void test_null_pointer(void) {
    error_t result = component_process(NULL, NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_normal_operation);
    RUN_TEST(test_null_pointer);
    return UNITY_END();
}
```

## Test Organization

```
tests/
├── unit/           # Unit tests (one test file per component)
├── integration/    # Integration tests
├── system/         # System-level tests
└── unity/          # Unity test framework (external)
```

## Coverage Analysis

Use gcov/lcov for coverage:

```bash
# Compile with coverage
gcc -fprofile-arcs -ftest-coverage source.c test.c -o test

# Run tests
./test

# Generate coverage report
gcov source.c
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_html
```

## Test Categories

### 1. Normal Operation Tests
- Valid inputs and expected outputs
- Typical use cases

### 2. Boundary Value Tests
- Minimum values
- Maximum values
- Just below minimum
- Just above maximum

### 3. Error Condition Tests
- NULL pointers
- Invalid parameters
- Out-of-range values
- Resource exhaustion

### 4. Fault Injection Tests (SIL 3-4)
- Simulated hardware faults
- Communication failures
- Timing violations

## Creating Tests

Use `/tst` agent to generate tests:

```bash
/tst
Create unit tests for door_control component with 100% coverage
```

## References

- See `.opencode/skills/en50128-testing/` for test patterns
- Unity framework: http://www.throwtheswitch.org/unity
- gcov documentation: https://gcc.gnu.org/onlinedocs/gcc/Gcov.html
