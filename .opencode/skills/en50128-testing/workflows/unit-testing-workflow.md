# Unit Testing Workflow

**EN 50128 Reference**: Section 7.4.4.8 (Component Testing), Table A.5, Table A.21  
**Role**: Tester (TST)  
**Phase**: Implementation & Testing (Phase 4)  
**SIL Applicability**: All (0, 1, 2, 3, 4)

---

## Overview

This workflow defines the complete unit testing process for C software components in EN 50128 railway applications. Unit testing verifies individual functions and modules against design specifications and requirements.

**Key Objectives**:
- Execute white-box testing at function/module level
- Achieve SIL-appropriate code coverage targets
- Validate defensive programming implementation
- Detect defects early in the development lifecycle
- Generate traceability from requirements to test results

**EN 50128 Requirements**:
- **Component Testing MANDATORY** for all SIL levels (Section 7.4.4.8)
- **Coverage Requirements** per SIL (Table A.21 - see below)
- **Test independence** for SIL 3-4 (separate tester from implementer)
- **Boundary value analysis** MANDATORY for SIL 3-4
- **Fault injection** HIGHLY RECOMMENDED for SIL 3-4

---

## EN 50128 Coverage Requirements (Table A.21)

| Coverage Type | SIL 0 | SIL 1-2 | SIL 3-4 | Target |
|---------------|-------|---------|---------|--------|
| **Statement Coverage** | HR | HR | **M** | 100% |
| **Branch Coverage** | HR | **M** | **M** | 100% |
| **Condition Coverage** | - | R | **M** | 100% |
| **MC/DC Coverage** | - | - | HR | 100% |

**Key Points**:
- **SIL 0-1**: Statement (HR), Branch (HR) - Target 80%+
- **SIL 2**: Branch (**MANDATORY** 100%), Statement (HR 95%+)
- **SIL 3-4**: Statement + Branch + Condition (**ALL MANDATORY** 100%)
- **Uncovered code** requires documented justification for SIL 2+

**Standard Reference**: `std/EN50128-2011.md` Annex A, Table A.21

---

## Workflow Steps

### Step 1: Test Planning and Preparation

#### 1.1 Review Component Design

**Input Documents**:
- Software Design Specification (SDS) - `docs/SDS.md`
- Software Requirements Specification (SRS) - `docs/SRS.md`
- Source code modules - `src/`

**Activities**:
```bash
# Review design documentation
cat docs/SDS.md | grep "MODULE: ${MODULE_NAME}"

# Review source code
cat src/${MODULE_NAME}.c

# Extract requirements traceability
workspace.py trace query --source ${MODULE_NAME} --direction backward
```

**Expected Output**:
- List of functions to test
- Requirements mapped to each function
- Identified test types (normal, boundary, error, fault injection)

---

#### 1.2 Identify Test Cases

**Test Types** (per EN 50128 Table A.14 - Functional Testing):

1. **Normal Operation Tests**
   - Valid inputs within expected range
   - Typical operational scenarios
   - Expected return values and state changes

2. **Boundary Value Tests** (MANDATORY SIL 3-4)
   - Minimum value (e.g., 0, INT_MIN)
   - Maximum value (e.g., UINT32_MAX)
   - Just below minimum (underflow check)
   - Just above maximum (overflow check)

3. **Equivalence Class Tests**
   - Group inputs into classes with similar behavior
   - Test representative from each class

4. **Error Handling Tests** (MANDATORY all SILs)
   - NULL pointer parameters
   - Invalid parameter values
   - Out-of-range inputs
   - Division by zero
   - Buffer overflow attempts

5. **Fault Injection Tests** (HIGHLY RECOMMENDED SIL 3-4)
   - Simulated sensor failures
   - Communication timeouts
   - Resource exhaustion
   - Hardware fault conditions

**Test Case Identification Process**:
```bash
# Create test specification file
cat > tests/specs/test_${MODULE_NAME}_spec.md << 'EOF'
# Test Specification: ${MODULE_NAME}

## Function: ${FUNCTION_NAME}
**Requirements**: REQ-FUNC-001, REQ-SAFE-005
**Test Cases**:
- TC-${MODULE}-${FUNC}-001: Normal operation
- TC-${MODULE}-${FUNC}-002: Boundary - minimum value
- TC-${MODULE}-${FUNC}-003: Boundary - maximum value
- TC-${MODULE}-${FUNC}-004: Error - NULL pointer
- TC-${MODULE}-${FUNC}-005: Error - invalid parameter
- TC-${MODULE}-${FUNC}-006: Fault injection - sensor fault
EOF
```

---

#### 1.3 Set Up Test Environment

**Test Framework**: Unity (lightweight C test framework)

**Directory Structure**:
```
tests/
├── unit/
│   ├── test_brake_controller.c
│   ├── test_speed_sensor.c
│   └── test_signal_processor.c
├── data/
│   ├── valid_inputs.csv
│   ├── boundary_values.csv
│   └── fault_scenarios.csv
├── mocks/
│   ├── mock_hardware.c
│   └── mock_sensors.c
├── coverage/
│   └── (generated coverage reports)
└── reports/
    └── (generated test reports)
```

**Build Configuration**:
```bash
# Create Makefile for unit tests
cat > tests/unit/Makefile << 'EOF'
# Unit Test Makefile

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic \
         -fprofile-arcs -ftest-coverage \
         -g -O0 -DUNIT_TEST

INCLUDES = -I../../src -I../../include -I../mocks -I./unity/src

# Test executables
TESTS = test_brake_controller test_speed_sensor test_signal_processor

all: $(TESTS)

test_brake_controller: test_brake_controller.c ../../src/brake_controller.c unity/src/unity.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

coverage: all
	@for test in $(TESTS); do \
		./$$test || exit 1; \
	done
	gcov ../../src/*.c
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory ../coverage

clean:
	rm -f $(TESTS) *.gcda *.gcno *.gcov coverage.info
	rm -rf ../coverage

.PHONY: all coverage clean
EOF
```

**Tool Installation Check**:
```bash
# Verify required tools installed
which gcc && gcc --version
which gcov && gcov --version
which lcov && lcov --version

# Install Unity test framework if needed
cd tests/unit
git clone https://github.com/ThrowTheSwitch/Unity.git unity
```

---

### Step 2: Write Unit Tests

#### 2.1 Unit Test Structure (Unity Framework)

**Test File Template**:
```c
// test_brake_controller.c
// Unit tests for brake controller module
// EN 50128 SIL 3 Component Testing

#include "brake_controller.h"
#include "unity.h"
#include "mock_hardware.h"
#include <stdint.h>
#include <stdbool.h>

// ============================================
// TEST SETUP AND TEARDOWN
// ============================================

void setUp(void) {
    // Initialize before each test
    brake_controller_init();
    mock_hardware_reset();
}

void tearDown(void) {
    // Cleanup after each test
    brake_controller_shutdown();
}

// ============================================
// NORMAL OPERATION TESTS
// ============================================

// TC-BRAKE-APPLY-001: Normal brake application
// Requirement: REQ-FUNC-010
// Test Type: Normal
void test_brake_normal_application(void) {
    // Arrange
    uint16_t speed = 100U;  // km/h
    uint8_t brake_level = 0U;
    error_t result;
    
    // Act
    result = brake_controller_apply(speed, &brake_level);
    
    // Assert
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_TRUE(brake_level > 0U);
    TEST_ASSERT_TRUE(brake_level <= MAX_BRAKE_LEVEL);
}

// TC-BRAKE-RELEASE-001: Normal brake release
// Requirement: REQ-FUNC-011
// Test Type: Normal
void test_brake_normal_release(void) {
    // Arrange
    uint8_t brake_level = 5U;
    error_t result;
    
    // Set initial brake level
    brake_controller_set_level(brake_level);
    
    // Act
    result = brake_controller_release();
    
    // Assert
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(0U, brake_controller_get_level());
}

// ============================================
// BOUNDARY VALUE TESTS (MANDATORY SIL 3-4)
// ============================================

// TC-BRAKE-APPLY-002: Boundary - Minimum speed
// Requirement: REQ-FUNC-010
// Test Type: Boundary
void test_brake_minimum_speed(void) {
    uint16_t speed = 0U;  // Minimum
    uint8_t brake_level;
    error_t result;
    
    result = brake_controller_apply(speed, &brake_level);
    
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(0U, brake_level);  // No brake at zero speed
}

// TC-BRAKE-APPLY-003: Boundary - Maximum speed
// Requirement: REQ-FUNC-010
// Test Type: Boundary
void test_brake_maximum_speed(void) {
    uint16_t speed = MAX_SPEED;  // Maximum (e.g., 300 km/h)
    uint8_t brake_level;
    error_t result;
    
    result = brake_controller_apply(speed, &brake_level);
    
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(MAX_BRAKE_LEVEL, brake_level);  // Full brake
}

// TC-BRAKE-APPLY-004: Boundary - Just above maximum
// Requirement: REQ-IMPL-006 (Defensive programming)
// Test Type: Boundary
void test_brake_speed_overflow(void) {
    uint16_t speed = MAX_SPEED + 1U;  // Just above max
    uint8_t brake_level;
    error_t result;
    
    result = brake_controller_apply(speed, &brake_level);
    
    TEST_ASSERT_EQUAL(ERROR_INVALID_SPEED, result);
    // Verify defensive: brake level unchanged
    TEST_ASSERT_EQUAL(0U, brake_level);
}

// ============================================
// ERROR HANDLING TESTS (MANDATORY ALL SILS)
// ============================================

// TC-BRAKE-APPLY-005: Error - NULL pointer
// Requirement: REQ-IMPL-006 (Defensive programming)
// Test Type: Error
void test_brake_null_pointer(void) {
    uint16_t speed = 100U;
    error_t result;
    
    // Act with NULL output parameter
    result = brake_controller_apply(speed, NULL);
    
    // Assert
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    // Function MUST NOT crash (test passes if we reach this line)
}

// TC-BRAKE-SET-001: Error - Invalid brake level
// Requirement: REQ-IMPL-006
// Test Type: Error
void test_brake_invalid_level(void) {
    uint8_t invalid_level = MAX_BRAKE_LEVEL + 1U;
    error_t result;
    
    result = brake_controller_set_level(invalid_level);
    
    TEST_ASSERT_EQUAL(ERROR_INVALID_PARAMETER, result);
    // Verify system state unchanged
    TEST_ASSERT_EQUAL(0U, brake_controller_get_level());
}

// ============================================
// FAULT INJECTION TESTS (HR SIL 3-4)
// ============================================

// TC-BRAKE-FAULT-001: Fault injection - Sensor stuck
// Requirement: REQ-SAFE-015
// Test Type: Fault Injection
void test_brake_sensor_stuck_fault(void) {
    // Arrange: Inject sensor fault
    mock_hardware_inject_fault(SENSOR_SPEED, FAULT_STUCK);
    
    // Act
    uint8_t brake_level;
    error_t result = brake_controller_apply(100U, &brake_level);
    
    // Assert: System detects fault and enters safe state
    TEST_ASSERT_EQUAL(ERROR_SENSOR_FAULT, result);
    TEST_ASSERT_TRUE(brake_controller_in_safe_state());
    // Emergency brake should be applied
    TEST_ASSERT_EQUAL(MAX_BRAKE_LEVEL, brake_controller_get_emergency_level());
}

// TC-BRAKE-FAULT-002: Fault injection - Communication timeout
// Requirement: REQ-SAFE-016
// Test Type: Fault Injection
void test_brake_communication_timeout(void) {
    // Arrange: Inject communication timeout
    mock_hardware_inject_fault(BUS_CAN, FAULT_TIMEOUT);
    
    // Act
    system_tick();  // Trigger timeout detection
    
    // Assert: Safe state entered
    TEST_ASSERT_TRUE(brake_controller_in_safe_state());
    TEST_ASSERT_TRUE(system_get_fault_flag(FAULT_COMM_TIMEOUT));
}

// ============================================
// ROBUSTNESS TESTS (MANDATORY SIL 4)
// ============================================

// TC-BRAKE-ROBUST-001: Multiple rapid commands
// Requirement: REQ-PERF-005
// Test Type: Robustness
void test_brake_rapid_commands(void) {
    error_t result;
    
    // Apply and release brake rapidly 1000 times
    for (uint16_t i = 0U; i < 1000U; i++) {
        result = brake_controller_apply(100U, NULL);
        TEST_ASSERT_EQUAL(SUCCESS, result);
        
        result = brake_controller_release();
        TEST_ASSERT_EQUAL(SUCCESS, result);
    }
    
    // Verify system still responsive
    uint8_t brake_level;
    result = brake_controller_apply(100U, &brake_level);
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_TRUE(brake_level > 0U);
}

// ============================================
// TEST RUNNER
// ============================================

int main(void) {
    UNITY_BEGIN();
    
    // Normal operation tests
    RUN_TEST(test_brake_normal_application);
    RUN_TEST(test_brake_normal_release);
    
    // Boundary value tests (MANDATORY SIL 3-4)
    RUN_TEST(test_brake_minimum_speed);
    RUN_TEST(test_brake_maximum_speed);
    RUN_TEST(test_brake_speed_overflow);
    
    // Error handling tests (MANDATORY)
    RUN_TEST(test_brake_null_pointer);
    RUN_TEST(test_brake_invalid_level);
    
    // Fault injection tests (HR SIL 3-4)
    RUN_TEST(test_brake_sensor_stuck_fault);
    RUN_TEST(test_brake_communication_timeout);
    
    // Robustness tests (MANDATORY SIL 4)
    RUN_TEST(test_brake_rapid_commands);
    
    return UNITY_END();
}
```

---

#### 2.2 Mock Object Creation

**Mock Hardware Interface** (`tests/mocks/mock_hardware.c`):
```c
// mock_hardware.c
// Mock hardware for unit testing

#include "mock_hardware.h"
#include <string.h>

// Mock state
typedef struct {
    bool fault_injected;
    fault_type_t fault_type;
    component_t fault_component;
    uint16_t sensor_values[NUM_SENSORS];
} mock_state_t;

static mock_state_t mock_state;

void mock_hardware_reset(void) {
    memset(&mock_state, 0, sizeof(mock_state_t));
}

void mock_hardware_inject_fault(component_t component, fault_type_t fault) {
    mock_state.fault_injected = true;
    mock_state.fault_component = component;
    mock_state.fault_type = fault;
}

bool mock_hardware_has_fault(component_t component) {
    return (mock_state.fault_injected && 
            mock_state.fault_component == component);
}

void mock_hardware_set_sensor(sensor_id_t sensor, uint16_t value) {
    if (sensor < NUM_SENSORS) {
        mock_state.sensor_values[sensor] = value;
    }
}

uint16_t mock_hardware_read_sensor(sensor_id_t sensor) {
    if (mock_hardware_has_fault(sensor)) {
        // Return fault-specific value
        if (mock_state.fault_type == FAULT_STUCK) {
            return 0xFFFFU;  // Stuck at max
        }
        return 0U;  // Disconnected
    }
    return mock_state.sensor_values[sensor];
}
```

---

### Step 3: Execute Unit Tests

#### 3.1 Build and Run Tests

```bash
# Navigate to test directory
cd tests/unit

# Build all unit tests with coverage instrumentation
make clean
make coverage

# Output:
# gcc -std=c11 -Wall -Wextra -Werror -pedantic -fprofile-arcs -ftest-coverage -g -O0 -DUNIT_TEST ...
# Compiled: test_brake_controller
# Compiled: test_speed_sensor
# Compiled: test_signal_processor
```

**Execute Tests**:
```bash
# Run all tests
./test_brake_controller
./test_speed_sensor
./test_signal_processor

# Unity output example:
# test_brake_controller.c:45:test_brake_normal_application:PASS
# test_brake_controller.c:65:test_brake_normal_release:PASS
# test_brake_controller.c:85:test_brake_minimum_speed:PASS
# test_brake_controller.c:95:test_brake_maximum_speed:PASS
# test_brake_controller.c:105:test_brake_speed_overflow:PASS
# test_brake_controller.c:120:test_brake_null_pointer:PASS
# test_brake_controller.c:135:test_brake_invalid_level:PASS
# test_brake_controller.c:150:test_brake_sensor_stuck_fault:PASS
# test_brake_controller.c:165:test_brake_communication_timeout:PASS
# test_brake_controller.c:180:test_brake_rapid_commands:PASS
#
# -----------------------
# 10 Tests 0 Failures 0 Ignored 
# OK
```

---

#### 3.2 Generate Coverage Report

```bash
# Generate coverage data
gcov ../../src/brake_controller.c

# Output:
# File '../../src/brake_controller.c'
# Lines executed:100.00% of 150
# Branches executed:100.00% of 45
# Taken at least once:100.00% of 45
# Calls executed:100.00% of 20

# Generate HTML coverage report
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory ../coverage

# View coverage report
firefox ../coverage/index.html &
```

**Coverage Analysis**:
```bash
# Check coverage against SIL requirements
python3 ../../tools/check_coverage.py \
    --source ../../src/brake_controller.c \
    --sil 3 \
    --statement 100.0 \
    --branch 100.0 \
    --condition 100.0

# Output:
# Coverage Analysis Report
# ========================
# SIL Level: 3
# Module: brake_controller.c
# 
# Statement Coverage: 100.0% [PASS] (Required: 100%)
# Branch Coverage:    100.0% [PASS] (Required: 100%)
# Condition Coverage: 100.0% [PASS] (Required: 100%)
# 
# Result: PASS - All coverage targets met
```

---

### Step 4: Analyze and Document Results

#### 4.1 Review Test Results

**Test Execution Summary**:
```bash
# Generate test summary report
cat > ../reports/unit_test_summary.md << 'EOF'
# Unit Test Execution Summary

**Date**: 2026-03-14
**SIL Level**: 3
**Modules Tested**: brake_controller, speed_sensor, signal_processor

## Test Results

| Module | Test Cases | Passed | Failed | Coverage (S/B/C) |
|--------|-----------|--------|--------|------------------|
| brake_controller | 10 | 10 | 0 | 100% / 100% / 100% |
| speed_sensor | 8 | 8 | 0 | 100% / 100% / 100% |
| signal_processor | 12 | 12 | 0 | 100% / 100% / 100% |

**Total**: 30 test cases, 30 passed (100%), 0 failed

## Coverage Analysis

**Overall Coverage**:
- Statement: 100% (SIL 3 target: 100%) ✅
- Branch: 100% (SIL 3 target: 100%) ✅
- Condition: 100% (SIL 3 target: 100%) ✅

**Uncovered Code**: None

## Defects Found

**Total Defects**: 2 (both fixed and re-tested)

| Defect ID | Severity | Description | Status |
|-----------|----------|-------------|--------|
| DEF-001 | Medium | Brake level not clamped at maximum | Fixed |
| DEF-002 | High | NULL pointer not checked in set_level() | Fixed |

## Conclusion

All unit tests PASSED. Coverage targets met for SIL 3. Ready for integration testing.
EOF
```

---

#### 4.2 Update Traceability Matrix

```bash
# Update traceability: tests to requirements
workspace.py trace create \
    --from tests \
    --to requirements \
    --source-id TC-BRAKE-APPLY-001 \
    --target-id REQ-FUNC-010 \
    --rationale "Unit test verifies normal brake application"

workspace.py trace create \
    --from tests \
    --to requirements \
    --source-id TC-BRAKE-APPLY-005 \
    --target-id REQ-IMPL-006 \
    --rationale "Unit test verifies NULL pointer defensive programming"

# Generate traceability report
workspace.py trace report \
    --from requirements \
    --to tests \
    --format markdown \
    --output evidence/traceability/requirements_to_tests.md

# Validate traceability completeness
workspace.py trace validate --phase testing --sil 3

# Output:
# Traceability Validation Report
# ===============================
# Phase: testing
# SIL Level: 3
# 
# Requirements Coverage:
# - Total requirements: 45
# - Requirements with tests: 45 (100%)
# - Requirements without tests: 0
# 
# Result: PASS - All requirements traced to tests
```

---

### Step 5: Defect Management

#### 5.1 Log Test Failures

**Defect Tracking**:
```bash
# Create defect log if test fails
cat > ../reports/defects.md << 'EOF'
# Unit Test Defects

## DEF-001: Brake level exceeds maximum

**Date**: 2026-03-14
**Severity**: Medium
**Test Case**: TC-BRAKE-APPLY-003
**Module**: brake_controller.c
**Function**: brake_controller_apply()

**Description**: 
When maximum speed is provided, brake level is calculated as 101, which exceeds MAX_BRAKE_LEVEL (100).

**Expected Result**: brake_level == 100
**Actual Result**: brake_level == 101

**Root Cause**: 
Missing saturation logic in brake calculation:
```c
brake_level = (speed * BRAKE_FACTOR) / 100U;  // No clamping
```

**Fix**:
```c
brake_level = (speed * BRAKE_FACTOR) / 100U;
if (brake_level > MAX_BRAKE_LEVEL) {
    brake_level = MAX_BRAKE_LEVEL;  // Clamp to maximum
}
```

**Re-test Result**: PASS (brake_level == 100)

**Status**: CLOSED
EOF
```

---

#### 5.2 Regression Testing

```bash
# After fixing defects, re-run ALL tests (regression)
make clean
make coverage

./test_brake_controller
./test_speed_sensor
./test_signal_processor

# Verify no new failures introduced
# Update test report with re-test results
```

---

## Coverage Analysis Deep Dive

### Statement Coverage

**Definition**: Percentage of executable statements executed by tests.

**SIL Requirements**:
- SIL 0-1: Highly Recommended (HR) - Target 80%+
- SIL 2: Highly Recommended (HR) - Target 95%+
- SIL 3-4: **MANDATORY (M)** - Target 100%

**Measurement**:
```bash
# gcov provides statement coverage
gcov src/brake_controller.c

# Output shows line-by-line execution counts:
#         -:   10:#include "brake_controller.h"
#         1:   20:error_t brake_controller_apply(uint16_t speed, uint8_t* brake_level) {
#         1:   21:    if (brake_level == NULL) {
#     #####:   22:        return ERROR_NULL_POINTER;  // <-- UNCOVERED (need test)
#         -:   23:    }
#         1:   24:    *brake_level = calculate_brake(speed);
#         1:   25:    return SUCCESS;
#         -:   26:}
```

---

### Branch Coverage

**Definition**: Percentage of conditional branches (if/while/for/switch) where both TRUE and FALSE paths are executed.

**SIL Requirements**:
- SIL 0-1: Highly Recommended (HR) - Target 80%+
- SIL 2: **MANDATORY (M)** - Target 100%
- SIL 3-4: **MANDATORY (M)** - Target 100%

**Example**:
```c
if (speed > MAX_SPEED) {           // Branch point
    return ERROR_INVALID_SPEED;    // TRUE path
} else {
    return calculate_brake(speed); // FALSE path
}
```

**Both paths MUST be tested** for SIL 2+ compliance.

**Measurement**:
```bash
# gcov with --branch-probabilities shows branch coverage
gcov --branch-probabilities src/brake_controller.c

# Output:
# branch  0 taken 5 (TRUE path)
# branch  1 taken 3 (FALSE path)
# Branch coverage: 100%
```

---

### Condition Coverage (SIL 3-4)

**Definition**: Percentage of Boolean sub-expressions evaluated to both TRUE and FALSE.

**SIL Requirements**:
- SIL 0-2: Not recommended (-)
- SIL 3-4: **MANDATORY (M)** - Target 100%

**Example**:
```c
if (speed > 0 && speed <= MAX_SPEED && !fault_detected) {
    // Three conditions: each must be tested TRUE and FALSE
    // Condition 1: speed > 0
    // Condition 2: speed <= MAX_SPEED
    // Condition 3: !fault_detected
}
```

**All 3 conditions** must be tested with both TRUE and FALSE values.

**Test Cases Required**:
```c
// Test case 1: All TRUE
test_all_conditions_true() {
    speed = 50;  // > 0: TRUE, <= MAX: TRUE
    fault = false;  // !fault: TRUE
}

// Test case 2: First condition FALSE
test_speed_zero() {
    speed = 0;  // > 0: FALSE
}

// Test case 3: Second condition FALSE
test_speed_overflow() {
    speed = MAX_SPEED + 1;  // <= MAX: FALSE
}

// Test case 4: Third condition FALSE
test_fault_detected() {
    fault = true;  // !fault: FALSE
}
```

---

### MC/DC Coverage (Modified Condition/Decision Coverage)

**Definition**: Each condition independently affects the decision outcome.

**SIL Requirements**:
- SIL 0-2: Not recommended (-)
- SIL 3-4: Highly Recommended (HR) - Target 100%

**Standard Reference**: DO-178C (avionics standard), applicable to railway software

**Tool Support**:
```bash
# Use custom MC/DC analyzer (see resources/mcdc-analysis-guide.md)
python3 tools/mcdc/mcdc_analyzer.py \
    --source src/brake_controller.c \
    --coverage coverage.info \
    --output evidence/mcdc/brake_controller_mcdc.json
```

---

## Test Automation

### Continuous Integration Integration

**Automated Test Execution**:
```bash
# CI/CD pipeline script: .github/workflows/unit-tests.yml
name: Unit Tests

on: [push, pull_request]

jobs:
  unit-tests:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Install dependencies
        run: |
          sudo apt-get update
          sudo apt-get install -y gcc gcov lcov
      
      - name: Build tests
        run: |
          cd tests/unit
          make clean
          make coverage
      
      - name: Run tests
        run: |
          cd tests/unit
          ./test_brake_controller || exit 1
          ./test_speed_sensor || exit 1
          ./test_signal_processor || exit 1
      
      - name: Generate coverage
        run: |
          cd tests/unit
          gcov ../../src/*.c
          lcov --capture --directory . --output-file coverage.info
      
      - name: Check coverage targets
        run: |
          python3 tools/check_coverage.py --sil 3 --threshold 100
      
      - name: Upload coverage report
        uses: codecov/codecov-action@v3
        with:
          files: tests/unit/coverage.info
```

---

### Test Harness Script

**Automated Test Execution Script** (`tests/run_unit_tests.sh`):
```bash
#!/bin/bash
# run_unit_tests.sh - Automated unit test execution
# Usage: ./run_unit_tests.sh [SIL_LEVEL]

set -e  # Exit on error

SIL_LEVEL=${1:-3}
TEST_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPORT_DIR="$TEST_DIR/reports"
COVERAGE_DIR="$TEST_DIR/coverage"

echo "========================================"
echo "EN 50128 Unit Test Execution"
echo "SIL Level: $SIL_LEVEL"
echo "Date: $(date +%Y-%m-%d)"
echo "========================================"

# Build tests
echo "[1/5] Building unit tests..."
cd "$TEST_DIR/unit"
make clean
make coverage

# Run tests
echo "[2/5] Executing unit tests..."
TEST_FAILED=0
for test_exec in test_*; do
    if [ -x "$test_exec" ]; then
        echo "Running $test_exec..."
        ./$test_exec || TEST_FAILED=1
    fi
done

if [ $TEST_FAILED -eq 1 ]; then
    echo "ERROR: One or more tests failed!"
    exit 1
fi

# Generate coverage
echo "[3/5] Generating coverage report..."
gcov ../../src/*.c
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory "$COVERAGE_DIR"

# Check coverage targets
echo "[4/5] Validating coverage targets..."
python3 ../../tools/check_coverage.py \
    --sil "$SIL_LEVEL" \
    --coverage coverage.info \
    --report "$REPORT_DIR/coverage_validation.json"

# Generate test report
echo "[5/5] Generating test report..."
python3 ../../tools/generate_test_report.py \
    --test-results . \
    --coverage coverage.info \
    --sil "$SIL_LEVEL" \
    --output "$REPORT_DIR/unit_test_report.md"

echo "========================================"
echo "Unit tests completed successfully!"
echo "Coverage report: $COVERAGE_DIR/index.html"
echo "Test report: $REPORT_DIR/unit_test_report.md"
echo "========================================"
```

---

## Deliverables

### Required Outputs

1. **Component Test Specification** (before testing)
   - Location: `docs/Component-Test-Specification.md`
   - Template: `templates/Component-Test-Specification-template.md`
   - Content: Test cases, procedures, expected results

2. **Component Test Report** (after testing)
   - Location: `docs/Component-Test-Report.md`
   - Template: `templates/Component-Test-Report-template.md`
   - Content: Test execution results, coverage, defects

3. **Test Code**
   - Location: `tests/unit/test_*.c`
   - Framework: Unity
   - Traceability: Comments link tests to requirements

4. **Coverage Reports**
   - Location: `tests/coverage/`
   - Format: HTML (lcov), JSON (for automation)
   - Content: Statement, branch, condition coverage

5. **Traceability Evidence**
   - Location: `evidence/traceability/requirements_to_tests.csv`
   - Tool: `workspace.py trace report`
   - Content: Requirements → Tests mapping

6. **Defect Log**
   - Location: `tests/reports/defects.md`
   - Content: All defects found during testing, status, resolution

---

## Quality Gates

### Unit Testing Exit Criteria (per SIL)

**SIL 0-1**:
- [ ] All test cases executed
- [ ] 80%+ statement coverage achieved
- [ ] 80%+ branch coverage achieved
- [ ] Critical defects resolved
- [ ] Test report generated

**SIL 2**:
- [ ] All test cases executed
- [ ] 95%+ statement coverage achieved
- [ ] **100% branch coverage achieved (MANDATORY)**
- [ ] All defects triaged and resolved
- [ ] Boundary value testing performed
- [ ] Test report generated and reviewed

**SIL 3-4**:
- [ ] All test cases executed **by independent tester**
- [ ] **100% statement coverage (MANDATORY)**
- [ ] **100% branch coverage (MANDATORY)**
- [ ] **100% condition coverage (MANDATORY)**
- [ ] **Boundary value analysis performed (MANDATORY)**
- [ ] **Fault injection testing performed (HR)**
- [ ] MC/DC coverage analyzed (HR)
- [ ] All defects resolved and re-tested
- [ ] Traceability validated (requirements → tests)
- [ ] Test report reviewed by independent verifier
- [ ] Coverage evidence archived

---

## Tool References

### Test Framework
- **Unity**: `tests/unit/unity/` (ThrowTheSwitch/Unity)
- **CUnit**: Alternative C test framework
- **Google Test**: C++ alternative (if using C++)

### Coverage Tools
- **gcov**: Statement and branch coverage (bundled with GCC)
- **lcov**: HTML coverage reports
- **Bullseye**: Commercial coverage tool (MC/DC support)
- **gcovr**: Python-based coverage reporting

### Custom Tools
- `tools/check_coverage.py` - Validate coverage against SIL targets
- `tools/generate_test_report.py` - Generate EN 50128 test reports
- `tools/mcdc/mcdc_analyzer.py` - MC/DC coverage analysis
- `workspace.py trace` - Traceability management

---

## References

- **EN 50128:2011**
  - Section 7.4.4.8 - Component Testing
  - Section 7.5 - Integration (Component and Hardware/Software Integration)
  - Table A.5 - Verification and Testing Techniques
  - Table A.13 - Dynamic Analysis and Testing
  - Table A.14 - Functional and Black-Box Testing
  - Table A.21 - Test Coverage for Code
- **Standard Location**: `std/EN50128-2011.md`
- **TOOLS.md**: Tool catalog and qualification requirements
- **Skill Resources**: `resources/testing-techniques-catalog.md`, `resources/coverage-analysis-guide.md`
