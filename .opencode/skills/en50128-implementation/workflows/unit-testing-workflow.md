# Unit Testing Workflow

**Skill**: en50128-implementation  
**Role**: Implementer (IMP) and Tester (TST)  
**Phase**: Implementation & Testing (Phase 4)  
**EN 50128 Reference**: Section 7.5, Table A.5 (Dynamic Analysis and Testing), Table A.21 (Test Coverage)

---

## Purpose

This workflow guides the creation and execution of unit tests for C code following EN 50128 requirements. Unit testing (component testing) is a **Mandatory** part of the verification process per EN 50128 Section 7.5.

**Key Objectives**:
- Achieve **100% statement, branch, and condition coverage** (SIL 3-4)
- Test all functions in isolation
- Verify all error paths
- Document test results with traceability
- Use automated test framework (Unity recommended)

**Coverage Requirements** (EN 50128 Table A.21):
- **SIL 0-1**: Statement coverage (HR), Branch coverage (HR)
- **SIL 2**: Statement coverage (HR), **Branch coverage (M)**
- **SIL 3-4**: **Statement coverage (M)**, **Branch coverage (M)**, **Condition coverage (M)**

---

## Prerequisites

### Required Inputs
- [ ] Source code implementation (.c files) - COMPLETE
- [ ] Module interfaces (.h files) - COMPLETE
- [ ] Software Design Specification (DOC-10) - defines test requirements
- [ ] Traceability matrix (Code → Test)

### Required Tools
```bash
# Verify test framework
ls test/unity/unity.c          # Unity test framework
ls test/unity/unity.h

# Verify coverage tools
which gcov && gcov --version   # Coverage analysis
which lcov && lcov --version   # HTML coverage reports

# Verify build system
ls Makefile.test || ls CMakeLists.txt
```

### Test Framework

**Unity Test Framework** (recommended for EN 50128):
- Lightweight C unit testing framework
- MISRA C compliant
- Simple assertion macros
- Integrated with gcov for coverage

**Installation**:
```bash
# Clone Unity into project
cd test
git clone https://github.com/ThrowTheSwitch/Unity.git unity

# Or copy unity.c and unity.h into test/unity/
```

---

## Step 1: Setup Test Environment

### 1.1 Directory Structure

```
project/
├── src/                        # Source code
│   ├── brake_controller.c
│   └── brake_controller.h
├── test/                       # Test code
│   ├── unity/                  # Unity framework
│   │   ├── unity.c
│   │   └── unity.h
│   ├── test_brake_controller.c # Test file
│   └── test_runner.c           # Test runner (optional)
├── build/                      # Build artifacts
└── coverage/                   # Coverage reports
```

### 1.2 Makefile Configuration

**Makefile.test**:
```makefile
# Compiler and flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -g
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage

# Directories
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build
COVERAGE_DIR = coverage
UNITY_DIR = $(TEST_DIR)/unity

# Include paths
INCLUDES = -I$(SRC_DIR) -I$(UNITY_DIR)

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Test files
TEST_SRCS = $(wildcard $(TEST_DIR)/test_*.c)
TEST_EXES = $(patsubst $(TEST_DIR)/test_%.c,$(BUILD_DIR)/test_%,$(TEST_SRCS))

# Unity framework
UNITY_SRC = $(UNITY_DIR)/unity.c
UNITY_OBJ = $(BUILD_DIR)/unity.o

# Default target
all: $(TEST_EXES)

# Compile source with coverage
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $(INCLUDES) -c $< -o $@

# Compile Unity
$(UNITY_OBJ): $(UNITY_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link test executable
$(BUILD_DIR)/test_%: $(TEST_DIR)/test_%.c $(OBJS) $(UNITY_OBJ)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $(INCLUDES) $^ -o $@

# Run all tests
test: $(TEST_EXES)
	@echo "Running unit tests..."
	@for test in $(TEST_EXES); do \
		echo "Running $$test..."; \
		./$$test || exit 1; \
	done

# Generate coverage report
coverage: test
	@mkdir -p $(COVERAGE_DIR)
	lcov --capture --directory $(BUILD_DIR) --output-file $(COVERAGE_DIR)/coverage.info
	lcov --remove $(COVERAGE_DIR)/coverage.info '/usr/*' '*/unity/*' --output-file $(COVERAGE_DIR)/coverage_filtered.info
	genhtml $(COVERAGE_DIR)/coverage_filtered.info --output-directory $(COVERAGE_DIR)/html
	@echo "Coverage report: $(COVERAGE_DIR)/html/index.html"

# Clean
clean:
	rm -rf $(BUILD_DIR) $(COVERAGE_DIR)

.PHONY: all test coverage clean
```

### 1.3 Initialize Traceability

```bash
# Create/initialize traceability matrix for code-to-test
workspace.py trace create \
    --from implementation \
    --to tests

# Extract traceability from test file
workspace.py trace extract \
    --document test/test_brake_controller.c \
    --type implementation_to_tests \
    --merge
```

---

## Step 2: Write Unit Test File

### 2.1 Test File Structure

**test/test_brake_controller.c**:
```c
/**
 * @file    test_brake_controller.c
 * @brief   Unit tests for brake controller module
 * @author  [Name]
 * @date    2026-03-13
 * @version 1.0.0
 * 
 * EN 50128 Traceability:
 * - Tests: src/brake_controller.c
 * - Requirement: DOC-6 REQ-FUNC-012 (Brake control)
 * - Test Spec: DOC-16 TEST-BRAKE-001
 * - SIL Level: 3
 * 
 * Coverage Target: 100% statement, branch, condition (SIL 3)
 */

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/
#include "unity.h"
#include "brake_controller.h"
#include <string.h>

/*******************************************************************************
 * TEST SETUP AND TEARDOWN
 ******************************************************************************/
static brake_state_t test_state;

/**
 * @brief Setup function called before each test
 */
void setUp(void)
{
    /* Initialize test state */
    memset(&test_state, 0, sizeof(test_state));
}

/**
 * @brief Teardown function called after each test
 */
void tearDown(void)
{
    /* Cleanup after test */
}

/*******************************************************************************
 * TEST CASES: brake_init()
 ******************************************************************************/
/**
 * @brief Test brake_init with valid state
 * @test_id TEST-BRAKE-INIT-001
 * @requirement REQ-FUNC-012.1
 */
void test_brake_init_valid_state(void)
{
    error_t status;
    
    /* Execute */
    status = brake_init(&test_state);
    
    /* Verify */
    TEST_ASSERT_EQUAL(SUCCESS, status);
}

/**
 * @brief Test brake_init with NULL pointer
 * @test_id TEST-BRAKE-INIT-002
 * @requirement REQ-FUNC-012.1
 * @coverage Branch coverage (error path)
 */
void test_brake_init_null_pointer(void)
{
    error_t status;
    
    /* Execute */
    status = brake_init(NULL);
    
    /* Verify error handling */
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, status);
}

/*******************************************************************************
 * TEST CASES: brake_apply()
 ******************************************************************************/
/**
 * @brief Test brake_apply with valid parameters
 * @test_id TEST-BRAKE-APPLY-001
 * @requirement REQ-FUNC-012.2
 */
void test_brake_apply_valid_parameters(void)
{
    error_t status;
    uint8_t level;
    uint16_t speed = 100U;
    
    /* Setup */
    status = brake_init(&test_state);
    TEST_ASSERT_EQUAL(SUCCESS, status);
    
    /* Execute */
    status = brake_apply(&test_state, speed, &level);
    
    /* Verify */
    TEST_ASSERT_EQUAL(SUCCESS, status);
    TEST_ASSERT_GREATER_THAN(0, level);
    TEST_ASSERT_LESS_OR_EQUAL(BRAKE_MAX_LEVEL, level);
}

/**
 * @brief Test brake_apply with NULL state
 * @test_id TEST-BRAKE-APPLY-002
 * @requirement REQ-FUNC-012.2
 * @coverage Branch coverage (error path)
 */
void test_brake_apply_null_state(void)
{
    error_t status;
    uint8_t level;
    
    /* Execute */
    status = brake_apply(NULL, 100U, &level);
    
    /* Verify */
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, status);
}

/**
 * @brief Test brake_apply with NULL level pointer
 * @test_id TEST-BRAKE-APPLY-003
 * @requirement REQ-FUNC-012.2
 * @coverage Branch coverage (error path)
 */
void test_brake_apply_null_level(void)
{
    error_t status;
    
    /* Setup */
    (void)brake_init(&test_state);
    
    /* Execute */
    status = brake_apply(&test_state, 100U, NULL);
    
    /* Verify */
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, status);
}

/**
 * @brief Test brake_apply with invalid speed
 * @test_id TEST-BRAKE-APPLY-004
 * @requirement REQ-FUNC-012.2
 * @coverage Branch coverage (validation failure)
 */
void test_brake_apply_invalid_speed(void)
{
    error_t status;
    uint8_t level;
    uint16_t invalid_speed = 500U;  /* Exceeds MAX_TRAIN_SPEED */
    
    /* Setup */
    (void)brake_init(&test_state);
    
    /* Execute */
    status = brake_apply(&test_state, invalid_speed, &level);
    
    /* Verify */
    TEST_ASSERT_EQUAL(ERROR_INVALID_PARAMETER, status);
}

/**
 * @brief Test brake_apply at boundary: speed = 0
 * @test_id TEST-BRAKE-APPLY-005
 * @requirement REQ-FUNC-012.2
 * @coverage Boundary value
 */
void test_brake_apply_speed_zero(void)
{
    error_t status;
    uint8_t level;
    
    /* Setup */
    (void)brake_init(&test_state);
    
    /* Execute */
    status = brake_apply(&test_state, 0U, &level);
    
    /* Verify */
    TEST_ASSERT_EQUAL(SUCCESS, status);
    TEST_ASSERT_EQUAL(0, level);
}

/**
 * @brief Test brake_apply at boundary: speed = MAX_TRAIN_SPEED
 * @test_id TEST-BRAKE-APPLY-006
 * @requirement REQ-FUNC-012.2
 * @coverage Boundary value
 */
void test_brake_apply_speed_max(void)
{
    error_t status;
    uint8_t level;
    uint16_t max_speed = 300U;  /* MAX_TRAIN_SPEED */
    
    /* Setup */
    (void)brake_init(&test_state);
    
    /* Execute */
    status = brake_apply(&test_state, max_speed, &level);
    
    /* Verify */
    TEST_ASSERT_EQUAL(SUCCESS, status);
    TEST_ASSERT_EQUAL(BRAKE_MAX_LEVEL, level);
}

/*******************************************************************************
 * TEST CASES: brake_emergency()
 ******************************************************************************/
/**
 * @brief Test brake_emergency with valid state
 * @test_id TEST-BRAKE-EMERG-001
 * @requirement REQ-FUNC-012.3
 */
void test_brake_emergency_valid_state(void)
{
    error_t status;
    
    /* Setup */
    (void)brake_init(&test_state);
    
    /* Execute */
    status = brake_emergency(&test_state);
    
    /* Verify */
    TEST_ASSERT_EQUAL(SUCCESS, status);
}

/**
 * @brief Test brake_emergency with NULL state
 * @test_id TEST-BRAKE-EMERG-002
 * @requirement REQ-FUNC-012.3
 * @coverage Branch coverage (error path)
 */
void test_brake_emergency_null_state(void)
{
    error_t status;
    
    /* Execute */
    status = brake_emergency(NULL);
    
    /* Verify */
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, status);
}

/*******************************************************************************
 * TEST RUNNER
 ******************************************************************************/
/**
 * @brief Main test runner
 */
int main(void)
{
    UNITY_BEGIN();
    
    /* brake_init() tests */
    RUN_TEST(test_brake_init_valid_state);
    RUN_TEST(test_brake_init_null_pointer);
    
    /* brake_apply() tests */
    RUN_TEST(test_brake_apply_valid_parameters);
    RUN_TEST(test_brake_apply_null_state);
    RUN_TEST(test_brake_apply_null_level);
    RUN_TEST(test_brake_apply_invalid_speed);
    RUN_TEST(test_brake_apply_speed_zero);
    RUN_TEST(test_brake_apply_speed_max);
    
    /* brake_emergency() tests */
    RUN_TEST(test_brake_emergency_valid_state);
    RUN_TEST(test_brake_emergency_null_state);
    
    return UNITY_END();
}
```

### 2.2 Unity Assertion Macros

**Basic Assertions**:
```c
TEST_ASSERT(condition)                      // Assert condition is true
TEST_ASSERT_TRUE(condition)                 // Assert true
TEST_ASSERT_FALSE(condition)                // Assert false
TEST_ASSERT_NULL(pointer)                   // Assert pointer is NULL
TEST_ASSERT_NOT_NULL(pointer)               // Assert pointer not NULL
```

**Integer Assertions**:
```c
TEST_ASSERT_EQUAL(expected, actual)         // Assert equality
TEST_ASSERT_NOT_EQUAL(expected, actual)     // Assert inequality
TEST_ASSERT_EQUAL_INT(expected, actual)     // Integer equality
TEST_ASSERT_EQUAL_INT8(expected, actual)    // 8-bit integer
TEST_ASSERT_EQUAL_INT16(expected, actual)   // 16-bit integer
TEST_ASSERT_EQUAL_INT32(expected, actual)   // 32-bit integer
TEST_ASSERT_EQUAL_UINT8(expected, actual)   // Unsigned 8-bit
TEST_ASSERT_EQUAL_UINT16(expected, actual)  // Unsigned 16-bit
TEST_ASSERT_EQUAL_UINT32(expected, actual)  // Unsigned 32-bit
```

**Comparison Assertions**:
```c
TEST_ASSERT_GREATER_THAN(threshold, actual)
TEST_ASSERT_LESS_THAN(threshold, actual)
TEST_ASSERT_GREATER_OR_EQUAL(threshold, actual)
TEST_ASSERT_LESS_OR_EQUAL(threshold, actual)
TEST_ASSERT_INT_WITHIN(delta, expected, actual)
```

**Memory Assertions**:
```c
TEST_ASSERT_EQUAL_MEMORY(expected, actual, len)
TEST_ASSERT_EQUAL_STRING(expected, actual)
TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, actual, len, count)
```

---

## Step 3: Test Design Strategies

### 3.1 Equivalence Partitioning

**Principle**: Divide input domain into equivalence classes and test one value from each class.

**Example: Speed input validation**:
```c
/* Equivalence classes for speed [0..300]:
 * 1. Valid range: [0..300]
 * 2. Below range: < 0 (not possible with uint16_t)
 * 3. Above range: > 300
 */

void test_brake_apply_valid_range(void)
{
    /* Test representative from valid class */
    uint16_t speed = 150U;  /* Middle of [0..300] */
    /* ... test code ... */
}

void test_brake_apply_above_range(void)
{
    /* Test representative from invalid class */
    uint16_t speed = 400U;  /* > 300 */
    /* ... test code ... */
}
```

### 3.2 Boundary Value Analysis

**Principle**: Test values at boundaries of equivalence classes.

**Example: Boundary values for speed [0..300]**:
```c
/* Boundary values:
 * - Minimum: 0
 * - Just above minimum: 1
 * - Nominal: 150
 * - Just below maximum: 299
 * - Maximum: 300
 * - Just above maximum: 301
 */

void test_brake_apply_boundary_min(void)
{
    uint16_t speed = 0U;
    /* ... test ... */
}

void test_brake_apply_boundary_max(void)
{
    uint16_t speed = 300U;
    /* ... test ... */
}

void test_brake_apply_boundary_above_max(void)
{
    uint16_t speed = 301U;
    /* ... expect error ... */
}
```

### 3.3 Error Path Testing

**Principle**: Test ALL error conditions.

**Example: All error paths in brake_apply()**:
```c
/* Error path 1: NULL state pointer */
void test_brake_apply_null_state(void) { /* ... */ }

/* Error path 2: NULL level pointer */
void test_brake_apply_null_level(void) { /* ... */ }

/* Error path 3: Invalid speed */
void test_brake_apply_invalid_speed(void) { /* ... */ }

/* Error path 4: Invalid state (if applicable) */
void test_brake_apply_invalid_state(void) { /* ... */ }
```

### 3.4 State-Based Testing

**Principle**: Test state transitions and state-dependent behavior.

**Example: State machine testing**:
```c
typedef enum {
    STATE_IDLE,
    STATE_ACTIVE,
    STATE_ERROR
} state_t;

/* Test initial state */
void test_fsm_initial_state(void)
{
    fsm_t fsm;
    fsm_init(&fsm);
    TEST_ASSERT_EQUAL(STATE_IDLE, fsm_get_state(&fsm));
}

/* Test valid transition: IDLE -> ACTIVE */
void test_fsm_idle_to_active(void)
{
    fsm_t fsm;
    fsm_init(&fsm);
    error_t status = fsm_transition(&fsm, STATE_ACTIVE);
    TEST_ASSERT_EQUAL(SUCCESS, status);
    TEST_ASSERT_EQUAL(STATE_ACTIVE, fsm_get_state(&fsm));
}

/* Test invalid transition: ACTIVE -> IDLE (not allowed) */
void test_fsm_active_to_idle_invalid(void)
{
    fsm_t fsm;
    fsm_init(&fsm);
    fsm_transition(&fsm, STATE_ACTIVE);
    error_t status = fsm_transition(&fsm, STATE_IDLE);
    TEST_ASSERT_EQUAL(ERROR_INVALID_TRANSITION, status);
}
```

---

## Step 4: Mocking Dependencies

### 4.1 When to Use Mocks

Use mocks when the unit under test has external dependencies:
- Hardware I/O functions
- Time functions
- Other modules
- Operating system calls

**Goal**: Test the module in **isolation**.

### 4.2 Manual Mocking Pattern

**Original hardware function** (in hardware_hal.c):
```c
uint32_t hardware_read_register(uint32_t address)
{
    return *((volatile uint32_t*)address);
}
```

**Mock implementation** (in test/mock_hardware_hal.c):
```c
/* Mock state */
static uint32_t mock_register_value = 0U;
static error_t mock_register_error = SUCCESS;

/* Mock function */
uint32_t hardware_read_register(uint32_t address)
{
    (void)address;  /* Unused in mock */
    
    if (mock_register_error != SUCCESS) {
        return 0xFFFFFFFFU;  /* Error value */
    }
    
    return mock_register_value;
}

/* Mock control functions */
void mock_hardware_set_register_value(uint32_t value)
{
    mock_register_value = value;
}

void mock_hardware_set_error(error_t error)
{
    mock_register_error = error;
}

void mock_hardware_reset(void)
{
    mock_register_value = 0U;
    mock_register_error = SUCCESS;
}
```

**Using mock in test**:
```c
void setUp(void)
{
    mock_hardware_reset();
}

void test_sensor_read_success(void)
{
    uint16_t value;
    error_t status;
    
    /* Setup mock to return specific value */
    mock_hardware_set_register_value(0x1234U);
    
    /* Execute */
    status = sensor_read(&value);
    
    /* Verify */
    TEST_ASSERT_EQUAL(SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT16(0x1234U, value);
}

void test_sensor_read_hardware_fault(void)
{
    uint16_t value;
    error_t status;
    
    /* Setup mock to simulate hardware error */
    mock_hardware_set_error(ERROR_HARDWARE_FAULT);
    
    /* Execute */
    status = sensor_read(&value);
    
    /* Verify error handling */
    TEST_ASSERT_EQUAL(ERROR_HARDWARE_FAULT, status);
}
```

### 4.3 Time Mocking

**Mock system time**:
```c
/* Mock state */
static uint32_t mock_system_time_ms = 0U;

/* Mock function */
uint32_t system_get_time_ms(void)
{
    return mock_system_time_ms;
}

/* Mock control */
void mock_time_set(uint32_t time_ms)
{
    mock_system_time_ms = time_ms;
}

void mock_time_advance(uint32_t delta_ms)
{
    mock_system_time_ms += delta_ms;
}
```

**Test timeout behavior**:
```c
void test_timeout_detection(void)
{
    error_t status;
    
    /* Setup: Start at time 0 */
    mock_time_set(0U);
    start_operation();
    
    /* Advance time to just before timeout */
    mock_time_advance(TIMEOUT_MS - 1U);
    status = check_operation();
    TEST_ASSERT_EQUAL(SUCCESS, status);  /* Not timed out */
    
    /* Advance time past timeout */
    mock_time_advance(2U);
    status = check_operation();
    TEST_ASSERT_EQUAL(ERROR_TIMEOUT, status);  /* Timed out */
}
```

---

## Step 5: Build and Run Tests

### 5.1 Build Tests

```bash
# Build all tests
make -f Makefile.test clean all

# Expected output:
# gcc -std=c99 -Wall -Wextra -Werror -g -fprofile-arcs -ftest-coverage ...
# gcc -std=c99 -Wall -Wextra -Werror -g -fprofile-arcs -ftest-coverage ...
# ...
```

### 5.2 Run Tests

```bash
# Run all tests
make -f Makefile.test test

# Expected output:
# Running build/test_brake_controller...
# test/test_brake_controller.c:45:test_brake_init_valid_state:PASS
# test/test_brake_controller.c:56:test_brake_init_null_pointer:PASS
# test/test_brake_controller.c:72:test_brake_apply_valid_parameters:PASS
# test/test_brake_controller.c:89:test_brake_apply_null_state:PASS
# test/test_brake_controller.c:103:test_brake_apply_null_level:PASS
# test/test_brake_controller.c:118:test_brake_apply_invalid_speed:PASS
# test/test_brake_controller.c:134:test_brake_apply_speed_zero:PASS
# test/test_brake_controller.c:150:test_brake_apply_speed_max:PASS
# test/test_brake_controller.c:167:test_brake_emergency_valid_state:PASS
# test/test_brake_controller.c:179:test_brake_emergency_null_state:PASS
# 
# -----------------------
# 10 Tests 0 Failures 0 Ignored
# OK
```

### 5.3 Handle Test Failures

**When a test fails**:
```
test/test_brake_controller.c:72:test_brake_apply_valid_parameters:FAIL: Expected 0 Was 1
```

**Debugging steps**:
1. Review test assertion that failed
2. Check expected vs. actual values
3. Add debug output to test
4. Run single test:
   ```bash
   ./build/test_brake_controller
   ```
5. Use debugger:
   ```bash
   gdb ./build/test_brake_controller
   ```

---

## Step 6: Measure Test Coverage

### 6.1 Generate Coverage Report

```bash
# Run tests and generate coverage
make -f Makefile.test coverage

# Output:
# Running unit tests...
# ...
# Capturing coverage data...
# Processing coverage info...
# Generating HTML report...
# Coverage report: coverage/html/index.html
```

### 6.2 Review Coverage Report

**Open in browser**:
```bash
firefox coverage/html/index.html
# or
xdg-open coverage/html/index.html
```

**Coverage metrics**:
- **Line coverage**: Percentage of lines executed
- **Function coverage**: Percentage of functions called
- **Branch coverage**: Percentage of branches taken

**Example coverage report**:
```
File: src/brake_controller.c
Lines: 95/100 (95.0%)
Functions: 6/6 (100%)
Branches: 18/20 (90.0%)

Uncovered lines:
  Line 145: (error handling path not tested)
  Line 178: (boundary condition not tested)
  
Uncovered branches:
  Line 167: condition (a && b) - false branch not tested
  Line 189: condition (x > MAX) - true branch not tested
```

### 6.3 Coverage Analysis for SIL Levels

**SIL 3-4 Requirements**:
- **Statement coverage: 100%** (MANDATORY)
- **Branch coverage: 100%** (MANDATORY)
- **Condition coverage: 100%** (MANDATORY)

**If coverage < 100%**:
1. Identify uncovered code from report
2. Add test cases to cover missing paths
3. Re-run tests and verify coverage increased
4. Repeat until 100% achieved

**Justification for uncovered code** (rare):
- Defensive code that cannot be triggered in normal operation
- Hardware-specific code that cannot be tested in simulation
- **Must be documented** with rationale approved by VER

### 6.4 Condition Coverage (MC/DC)

**Modified Condition/Decision Coverage** is **Highly Recommended** for SIL 3-4.

**Example: Complex condition**:
```c
if ((speed > MIN_SPEED) && (brake_level < MAX_LEVEL)) {
    /* ... */
}
```

**MC/DC test cases**:
```c
/* Test 1: Both conditions true */
void test_condition_both_true(void)
{
    speed = MIN_SPEED + 1U;
    brake_level = MAX_LEVEL - 1U;
    /* Condition evaluates to TRUE */
}

/* Test 2: First condition false */
void test_condition_first_false(void)
{
    speed = MIN_SPEED - 1U;  /* FALSE */
    brake_level = MAX_LEVEL - 1U;  /* TRUE */
    /* Condition evaluates to FALSE */
}

/* Test 3: Second condition false */
void test_condition_second_false(void)
{
    speed = MIN_SPEED + 1U;  /* TRUE */
    brake_level = MAX_LEVEL + 1U;  /* FALSE */
    /* Condition evaluates to FALSE */
}

/* Test 4: Both conditions false */
void test_condition_both_false(void)
{
    speed = MIN_SPEED - 1U;  /* FALSE */
    brake_level = MAX_LEVEL + 1U;  /* FALSE */
    /* Condition evaluates to FALSE */
}
```

**MC/DC Tools**:
```bash
# Use custom MC/DC analyzer
python3 tools/mcdc/mcdc_analyzer.py \
    --source src/brake_controller.c \
    --coverage coverage/coverage.info \
    --output analysis/mcdc_report.txt
```

---

## Step 7: Document Test Results

### 7.1 Test Execution Log

Create `test/test_execution_log.md`:

```markdown
# Unit Test Execution Log

## Module: brake_controller
- **Test File**: test/test_brake_controller.c
- **Source File**: src/brake_controller.c
- **Date**: 2026-03-13
- **Tester**: [Name]
- **SIL Level**: 3

## Test Results Summary
| Metric | Target (SIL 3) | Actual | Status |
|--------|----------------|--------|--------|
| Tests Executed | - | 10 | ✅ |
| Tests Passed | 100% | 10 (100%) | ✅ |
| Statement Coverage | 100% | 100% | ✅ |
| Branch Coverage | 100% | 100% | ✅ |
| Condition Coverage | 100% | 100% | ✅ |

## Test Cases Executed
| Test ID | Description | Status | Requirement |
|---------|-------------|--------|-------------|
| TEST-BRAKE-INIT-001 | Init with valid state | PASS | REQ-FUNC-012.1 |
| TEST-BRAKE-INIT-002 | Init with NULL pointer | PASS | REQ-FUNC-012.1 |
| TEST-BRAKE-APPLY-001 | Apply with valid params | PASS | REQ-FUNC-012.2 |
| TEST-BRAKE-APPLY-002 | Apply with NULL state | PASS | REQ-FUNC-012.2 |
| TEST-BRAKE-APPLY-003 | Apply with NULL level | PASS | REQ-FUNC-012.2 |
| TEST-BRAKE-APPLY-004 | Apply with invalid speed | PASS | REQ-FUNC-012.2 |
| TEST-BRAKE-APPLY-005 | Apply with speed = 0 | PASS | REQ-FUNC-012.2 |
| TEST-BRAKE-APPLY-006 | Apply with speed = MAX | PASS | REQ-FUNC-012.2 |
| TEST-BRAKE-EMERG-001 | Emergency with valid state | PASS | REQ-FUNC-012.3 |
| TEST-BRAKE-EMERG-002 | Emergency with NULL state | PASS | REQ-FUNC-012.3 |

## Coverage Analysis
- **Statement Coverage**: 100% (50/50 lines)
- **Branch Coverage**: 100% (20/20 branches)
- **Function Coverage**: 100% (6/6 functions)

### Uncovered Code: None

## Issues Found: None

## Sign-off
- **Tester**: [Name], Date: 2026-03-13
- **Reviewer**: [Name], Date: 2026-03-13
```

### 7.2 Update Traceability

```bash
# Extract traceability from test files
workspace.py trace extract \
    --document test/test_brake_controller.c \
    --type implementation_to_tests \
    --merge

# Validate test traceability completeness
workspace.py trace validate \
    --phase tests \
    --sil 3

# Generate test traceability report
workspace.py trace report \
    --from implementation \
    --to tests \
    --format markdown \
    --output docs/traceability/code_to_test_report.md
```

---

## Step 8: Integration with CI/CD

### 8.1 Automated Test Execution

**CI script (.github/workflows/test.yml)**:
```yaml
name: Unit Tests

on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v2
    
    - name: Install dependencies
      run: |
        sudo apt-get update
        sudo apt-get install -y gcc lcov
    
    - name: Build tests
      run: make -f Makefile.test all
    
    - name: Run tests
      run: make -f Makefile.test test
    
    - name: Generate coverage
      run: make -f Makefile.test coverage
    
    - name: Check coverage threshold
      run: |
        COVERAGE=$(lcov --summary coverage/coverage_filtered.info | grep lines | awk '{print $2}' | sed 's/%//')
        if (( $(echo "$COVERAGE < 100" | bc -l) )); then
          echo "Coverage $COVERAGE% below 100% requirement (SIL 3)"
          exit 1
        fi
    
    - name: Upload coverage report
      uses: actions/upload-artifact@v2
      with:
        name: coverage-report
        path: coverage/html
```

### 8.2 Nightly Test Runs

**Cron job** (tests run every night):
```bash
#!/bin/bash
# nightly_tests.sh

# Run all unit tests
make -f Makefile.test clean test coverage

# Check for failures
if [ $? -ne 0 ]; then
    echo "UNIT TESTS FAILED"
    # Send notification
    mail -s "Unit Test Failure" team@example.com < test_failure.log
    exit 1
fi

# Check coverage
COVERAGE=$(lcov --summary coverage/coverage_filtered.info | grep lines | awk '{print $2}' | sed 's/%//')
echo "Coverage: $COVERAGE%"

if (( $(echo "$COVERAGE < 100" | bc -l) )); then
    echo "COVERAGE BELOW 100%"
    mail -s "Coverage Failure" team@example.com < coverage.log
    exit 1
fi

echo "All tests passed, coverage: $COVERAGE%"
```

---

## SIL-Dependent Requirements

### SIL 0-1: Recommended
- Unit testing **recommended**
- Statement coverage **highly recommended** (target: 80%+)
- Branch coverage **highly recommended** (target: 70%+)

### SIL 2: Highly Recommended
- Unit testing **highly recommended**
- Statement coverage **highly recommended** (target: 95%+)
- **Branch coverage MANDATORY** (100%)

### SIL 3-4: Mandatory
- Unit testing **MANDATORY**
- **Statement coverage MANDATORY** (100%)
- **Branch coverage MANDATORY** (100%)
- **Condition coverage MANDATORY** (100% or MC/DC)
- Independent test review required
- Automated test execution in CI/CD

---

## Checklist

### Test Design
- [ ] Test file created for each source file
- [ ] All public functions have test cases
- [ ] All error paths tested
- [ ] Boundary values tested
- [ ] Invalid inputs tested
- [ ] State transitions tested (if applicable)
- [ ] Mocks created for dependencies

### Test Execution
- [ ] All tests pass
- [ ] No test failures
- [ ] Test execution automated

### Coverage
- [ ] Statement coverage measured
- [ ] Branch coverage measured
- [ ] Condition coverage measured (SIL 3-4)
- [ ] Coverage meets SIL requirements
- [ ] Uncovered code justified (if any)

### Documentation
- [ ] Test execution log created
- [ ] Coverage report generated
- [ ] Traceability updated (Code → Test)
- [ ] Test results reviewed

### Quality
- [ ] Tests follow naming convention
- [ ] Tests are repeatable
- [ ] Tests are isolated (no dependencies)
- [ ] Tests have clear pass/fail criteria

---

## Tools and Commands

### Build and Test
```bash
# Build tests
make -f Makefile.test all

# Run tests
make -f Makefile.test test

# Run single test
./build/test_brake_controller

# Debug test
gdb ./build/test_brake_controller
```

### Coverage Analysis
```bash
# Generate coverage
make -f Makefile.test coverage

# View coverage summary
lcov --summary coverage/coverage_filtered.info

# Check specific file
gcov build/brake_controller.gcda
```

### Traceability
```bash
# Link code to test
# Extract test traceability
workspace.py trace extract --document test/test_module.c --type implementation_to_tests --merge

# Check test coverage completeness
workspace.py trace check-gaps --phase tests --sil 3
```

---

## Common Issues and Solutions

### Issue 1: Test Fails to Link
**Problem:**
```
undefined reference to 'hardware_read_register'
```

**Solution:**
Create mock for hardware function or link with mock library.

### Issue 2: Coverage < 100%
**Problem:**
```
Branch coverage: 95% (19/20 branches)
Uncovered: Line 145 (false branch)
```

**Solution:**
Add test case for missing branch:
```c
void test_function_branch_false(void)
{
    /* Setup conditions for false branch */
    result = function(input_for_false_branch);
    TEST_ASSERT_EQUAL(expected_for_false, result);
}
```

### Issue 3: Flaky Tests
**Problem:**
Test passes sometimes, fails other times.

**Solution:**
- Check for uninitialized variables
- Verify test isolation (setUp/tearDown)
- Check for timing dependencies
- Review static variables

---

## Related Resources

- **[Unit Testing Patterns](../resources/unit-testing-patterns.md)** - Common testing patterns and mocking strategies
- **[Code Review Checklist](../resources/code-review-checklist.md)** - Review test quality
- **[MISRA C Coding Patterns](../resources/misra-c-coding-patterns.md)** - Testable code patterns

---

## References

1. **EN 50128:2011** Section 7.5 (Component Testing)
2. **EN 50128:2011** Table A.5 (Dynamic Analysis and Testing - MANDATORY SIL 3-4)
3. **EN 50128:2011** Table A.21 (Test Coverage for Code - MANDATORY SIL 3-4)
4. **Unity Test Framework** - http://www.throwtheswitch.org/unity
5. **gcov/lcov Documentation** - Coverage tools
6. **`std/EN50128-2011.md`** - Full EN 50128 standard (project repository)
