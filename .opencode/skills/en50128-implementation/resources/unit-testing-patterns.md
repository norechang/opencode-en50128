# Unit Testing Patterns for EN 50128 Railway Safety Software

**Purpose**: Comprehensive reference catalog of unit testing patterns for EN 50128-compliant C safety software using the Unity test framework.

**Scope**: Component testing (Phase 4) - unit test design, implementation, execution, and coverage achievement

**Audience**: Testers (TST), Implementers (IMP), Verifiers (VER)

**EN 50128 Reference**:
- Section 7.5 "Component Testing"
- Table A.5 "Dynamic Analysis and Testing" (MANDATORY SIL 3-4)
- Table A.21 "Test Coverage for Code" (Statement, Branch, Condition, MC/DC)

**Test Framework**: Unity (ThrowTheSwitch/Unity) - lightweight unit testing framework for C

**Related Documents**:
- `workflows/unit-testing-workflow.md` - Step-by-step unit testing workflow
- `workflows/defensive-coding-implementation.md` - Defensive patterns to test
- `resources/misra-c-coding-patterns.md` - Code patterns being tested

---

## Table of Contents

1. [Overview: Unity Test Framework for Safety-Critical C](#1-overview-unity-test-framework-for-safety-critical-c)
2. [Test File Structure Patterns](#2-test-file-structure-patterns)
3. [Test Case Design Patterns](#3-test-case-design-patterns)
4. [Test Fixture Patterns](#4-test-fixture-patterns)
5. [Mocking and Stub Patterns](#5-mocking-and-stub-patterns)
6. [Assertion Patterns](#6-assertion-patterns)
7. [Coverage Achievement Patterns](#7-coverage-achievement-patterns)
8. [Error Path Testing Patterns](#8-error-path-testing-patterns)
9. [Parameterized and Table-Driven Test Patterns](#9-parameterized-and-table-driven-test-patterns)
10. [Test Documentation Patterns](#10-test-documentation-patterns)

---

## 1. Overview: Unity Test Framework for Safety-Critical C

### 1.1 Why Unity for EN 50128?

**Unity Framework Advantages**:
- **Lightweight**: Small footprint, suitable for embedded targets
- **C-native**: Written in C, MISRA C compliant (with minor deviations)
- **Portable**: Runs on host (x86/x64) and target (ARM, etc.)
- **Simple**: Minimal dependencies, easy to integrate
- **Assertions**: Rich set of assertion macros for C types

**EN 50128 Suitability**:
- Used in safety-critical projects (automotive, medical, railway)
- Supports 100% coverage requirements (SIL 3-4)
- Generates machine-readable output (XML, JSON)
- Open source (MIT license) - auditable, no black box

### 1.2 EN 50128 Coverage Requirements

**Table A.21: Test Coverage for Code**

| Coverage Type | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 |
|---------------|-------|-------|-------|-------|-------|
| **Statement Coverage** | R | HR | HR | **M** | **M** |
| **Branch Coverage** | R | HR | **M** | **M** | **M** |
| **Condition Coverage** | - | - | R | **M** | **M** |
| **MC/DC Coverage** | - | - | - | R | R |

**SIL 3-4 Requirements**:
- **100% statement coverage** (MANDATORY)
- **100% branch coverage** (MANDATORY)
- **100% condition coverage** (MANDATORY)
- **MC/DC** (Recommended) - each condition independently affects outcome

**Measurement Tools**:
- `gcov` (GCC coverage tool) - statement and branch
- `lcov` (HTML report generator) - visualization
- Custom MC/DC analyzer (`tools/mcdc/mcdc_analyzer.py`) - condition coverage

### 1.3 Test Independence Requirements

**EN 50128 Section 5.3.4 (Tester Role)**:
- **SIL 0-1**: Tester may be same person as Implementer
- **SIL 2**: Tester should be different person (same team acceptable)
- **SIL 3-4**: **Independent Tester** (separate team, reports to VER/VAL)

**Test Traceability** (MANDATORY SIL 3-4):
- Each test case traces to Software Requirements Specification (DOC-5)
- Traceability managed by Traceability Manager CLI tool
- Format: `TEST-<module>-<function>-<scenario>` → `REQ-<id>`

### 1.4 Unity Framework API Summary

**Core Assertions**:
```c
TEST_ASSERT(condition)                          /* Boolean condition */
TEST_ASSERT_TRUE(condition)                     /* Explicit true */
TEST_ASSERT_FALSE(condition)                    /* Explicit false */
TEST_ASSERT_NULL(pointer)                       /* Pointer is NULL */
TEST_ASSERT_NOT_NULL(pointer)                   /* Pointer is not NULL */
TEST_ASSERT_EQUAL(expected, actual)             /* Generic equality */
TEST_ASSERT_EQUAL_INT(expected, actual)         /* Integer equality */
TEST_ASSERT_EQUAL_UINT(expected, actual)        /* Unsigned equality */
TEST_ASSERT_EQUAL_HEX(expected, actual)         /* Hex equality */
TEST_ASSERT_EQUAL_MEMORY(expected, actual, len) /* Memory comparison */
TEST_FAIL_MESSAGE(message)                      /* Explicit failure */
```

**Test Structure**:
```c
void setUp(void)    { /* Runs before each test */ }
void tearDown(void) { /* Runs after each test */ }

void test_example(void) {
    /* Test body with assertions */
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_example);
    return UNITY_END();
}
```

### 1.5 Relationship Between Workflow and This Resource

**`workflows/unit-testing-workflow.md`** provides:
- **Process**: 8-step workflow from setup to CI/CD integration
- **How-to**: Step-by-step instructions for test development
- **Tools**: Commands for gcov, lcov, Unity runner generation

**This resource** provides:
- **Patterns**: Reusable test design templates
- **Examples**: Complete test code for common scenarios
- **Reference**: Quick lookup for assertion syntax, mocking techniques
- **Catalog**: Organized library of test patterns

**Use Together**: Follow workflow for process, reference this document for patterns.

---

## 2. Test File Structure Patterns

### 2.1 Standard Test File Template

**Pattern: Complete Unity Test File**

```c
/* test_sensor_manager.c */

/* Include Unity framework */
#include "unity.h"

/* Include module under test */
#include "sensor_manager.h"

/* Include mocks/stubs */
#include "mock_hardware.h"

/* Test fixture setup - runs before EACH test */
void setUp(void) {
    /* Initialize module under test */
    sensor_manager_init();
    
    /* Initialize mocks */
    mock_hardware_reset();
}

/* Test fixture teardown - runs after EACH test */
void tearDown(void) {
    /* Clean up module state */
    sensor_manager_shutdown();
}

/* ===== Test Cases ===== */

/* Test: sensor_read returns success for valid channel
 * Req ID: REQ-SENSOR-001
 * Coverage: Statement, Branch (channel validation true path)
 */
void test_sensor_read_valid_channel_returns_success(void) {
    /* Arrange */
    uint8_t channel = 0;
    sensor_reading_t reading;
    error_t result;
    
    /* Act */
    result = sensor_read(channel, &reading);
    
    /* Assert */
    TEST_ASSERT_EQUAL(ERROR_NONE, result);
    TEST_ASSERT_NOT_NULL(&reading);
}

/* Test: sensor_read returns error for NULL pointer
 * Req ID: REQ-SENSOR-002
 * Coverage: Branch (NULL pointer check)
 */
void test_sensor_read_null_pointer_returns_error(void) {
    /* Arrange */
    uint8_t channel = 0;
    error_t result;
    
    /* Act */
    result = sensor_read(channel, NULL);
    
    /* Assert */
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
}

/* Test: sensor_read returns error for out-of-range channel
 * Req ID: REQ-SENSOR-003
 * Coverage: Branch (channel range check false path)
 */
void test_sensor_read_invalid_channel_returns_error(void) {
    /* Arrange */
    uint8_t channel = 255;  /* Out of range */
    sensor_reading_t reading;
    error_t result;
    
    /* Act */
    result = sensor_read(channel, &reading);
    
    /* Assert */
    TEST_ASSERT_EQUAL(ERROR_OUT_OF_RANGE, result);
}

/* ===== Test Runner (main) ===== */
int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_sensor_read_valid_channel_returns_success);
    RUN_TEST(test_sensor_read_null_pointer_returns_error);
    RUN_TEST(test_sensor_read_invalid_channel_returns_error);
    
    return UNITY_END();
}
```

**File Naming Convention**:
- Format: `test_<module_name>.c`
- Example: `test_sensor_manager.c`, `test_door_control.c`

**Test Function Naming Convention**:
- Format: `test_<function>_<scenario>_<expected_result>`
- Example: `test_sensor_read_null_pointer_returns_error`

### 2.2 Test Suite Organization Pattern

**Pattern: Group Tests by Functional Area**

```
test/
├── test_sensor_manager.c      # Sensor reading tests
├── test_door_control.c         # Door FSM tests
├── test_safety_monitor.c       # Safety validation tests
├── test_error_handling.c       # Error path tests
├── test_integration_helpers.c  # Integration test utilities
└── test_all.c                  # Master test runner (optional)
```

**Master Test Runner** (`test_all.c`):
```c
#include "unity.h"

/* External test declarations */
extern void run_sensor_manager_tests(void);
extern void run_door_control_tests(void);
extern void run_safety_monitor_tests(void);

int main(void) {
    UNITY_BEGIN();
    
    run_sensor_manager_tests();
    run_door_control_tests();
    run_safety_monitor_tests();
    
    return UNITY_END();
}
```

### 2.3 Makefile Integration Pattern

**Pattern: Test Build Target in Makefile**

```makefile
# Makefile

# Test directory
TEST_DIR = test
TEST_BUILD_DIR = build/test

# Unity framework
UNITY_DIR = vendor/Unity/src
UNITY_SRC = $(UNITY_DIR)/unity.c

# Test sources
TEST_SOURCES = $(wildcard $(TEST_DIR)/test_*.c)
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.c, $(TEST_BUILD_DIR)/%.o, $(TEST_SOURCES))
TEST_EXECUTABLES = $(patsubst $(TEST_DIR)/test_%.c, $(TEST_BUILD_DIR)/test_%, $(TEST_SOURCES))

# Compiler flags for testing
TEST_CFLAGS = -std=c99 -g -O0 \
              -I$(UNITY_DIR) \
              -Isrc \
              -Itest/mocks \
              -DUNIT_TEST \
              --coverage  # Enable gcov coverage

# Build test executables
$(TEST_BUILD_DIR)/test_%: $(TEST_DIR)/test_%.c $(UNITY_SRC) $(SOURCES)
	@mkdir -p $(TEST_BUILD_DIR)
	$(CC) $(TEST_CFLAGS) $^ -o $@

# Run all tests
test: $(TEST_EXECUTABLES)
	@echo "Running unit tests..."
	@for test in $(TEST_EXECUTABLES); do \
		echo "Running $$test..."; \
		$$test || exit 1; \
	done
	@echo "All tests passed!"

# Coverage report
coverage: test
	@echo "Generating coverage report..."
	gcov -o $(TEST_BUILD_DIR) $(SOURCES)
	lcov --capture --directory $(TEST_BUILD_DIR) --output-file coverage.info
	genhtml coverage.info --output-directory coverage_html
	@echo "Coverage report: coverage_html/index.html"

.PHONY: test coverage
```

### 2.4 Unity Test Runner Generation Pattern

**Pattern: Automatic Test Runner with Unity Script**

Unity provides `generate_test_runner.rb` script to auto-generate test runners:

```bash
# Generate test runner for test file
ruby vendor/Unity/auto/generate_test_runner.rb test/test_sensor_manager.c test/test_sensor_manager_runner.c

# Generated runner includes all test functions automatically
```

**Generated Output** (`test_sensor_manager_runner.c`):
```c
/* Auto-generated by Unity */
#include "unity.h"

extern void test_sensor_read_valid_channel_returns_success(void);
extern void test_sensor_read_null_pointer_returns_error(void);
extern void test_sensor_read_invalid_channel_returns_error(void);

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_sensor_read_valid_channel_returns_success);
    RUN_TEST(test_sensor_read_null_pointer_returns_error);
    RUN_TEST(test_sensor_read_invalid_channel_returns_error);
    return UNITY_END();
}
```

---

## 3. Test Case Design Patterns

### 3.1 Equivalence Partitioning Pattern

**Purpose**: Divide input domain into equivalence classes, test one value per class

**Theory**: If function behaves same for all values in class, testing one representative value is sufficient

**Pattern Example: Speed Controller**

```c
/* Function under test:
 * error_t set_speed(uint8_t speed);
 * Valid range: 0-100
 * Returns: ERROR_NONE (0-100), ERROR_OUT_OF_RANGE (>100)
 */

/* Equivalence Classes:
 * Class 1: Valid low (0-50) → Representative: 25
 * Class 2: Valid high (51-100) → Representative: 75
 * Class 3: Invalid (101-255) → Representative: 150
 */

void test_set_speed_valid_low_returns_success(void) {
    /* Equivalence class: Valid low (0-50) */
    error_t result = set_speed(25);
    TEST_ASSERT_EQUAL(ERROR_NONE, result);
}

void test_set_speed_valid_high_returns_success(void) {
    /* Equivalence class: Valid high (51-100) */
    error_t result = set_speed(75);
    TEST_ASSERT_EQUAL(ERROR_NONE, result);
}

void test_set_speed_invalid_returns_error(void) {
    /* Equivalence class: Invalid (101-255) */
    error_t result = set_speed(150);
    TEST_ASSERT_EQUAL(ERROR_OUT_OF_RANGE, result);
}
```

### 3.2 Boundary Value Pattern

**Purpose**: Test at exact boundaries and one value away (±1)

**Theory**: Errors most likely at boundaries (off-by-one errors)

**Pattern Example: Buffer Write**

```c
/* Function under test:
 * error_t buffer_write(uint8_t* buf, uint32_t size, uint32_t index, uint8_t val);
 * Valid index: 0 to (size-1)
 */

#define BUFFER_SIZE 100

/* Boundary values: -1 (invalid), 0 (min), 99 (max), 100 (invalid) */

void test_buffer_write_index_minus_one_invalid(void) {
    /* Boundary: Below minimum (test with wrap-around to large uint) */
    uint8_t buffer[BUFFER_SIZE];
    /* uint32_t index = -1 wraps to 4294967295 */
    error_t result = buffer_write(buffer, BUFFER_SIZE, UINT32_MAX, 0xAB);
    TEST_ASSERT_EQUAL(ERROR_OUT_OF_RANGE, result);
}

void test_buffer_write_index_zero_valid(void) {
    /* Boundary: Minimum valid (0) */
    uint8_t buffer[BUFFER_SIZE] = {0};
    error_t result = buffer_write(buffer, BUFFER_SIZE, 0, 0xAB);
    TEST_ASSERT_EQUAL(ERROR_NONE, result);
    TEST_ASSERT_EQUAL_HEX8(0xAB, buffer[0]);
}

void test_buffer_write_index_max_valid(void) {
    /* Boundary: Maximum valid (99) */
    uint8_t buffer[BUFFER_SIZE] = {0};
    error_t result = buffer_write(buffer, BUFFER_SIZE, 99, 0xCD);
    TEST_ASSERT_EQUAL(ERROR_NONE, result);
    TEST_ASSERT_EQUAL_HEX8(0xCD, buffer[99]);
}

void test_buffer_write_index_out_of_bounds_invalid(void) {
    /* Boundary: Above maximum (100) */
    uint8_t buffer[BUFFER_SIZE];
    error_t result = buffer_write(buffer, BUFFER_SIZE, 100, 0xEF);
    TEST_ASSERT_EQUAL(ERROR_OUT_OF_RANGE, result);
}
```

### 3.3 State Transition Pattern

**Purpose**: Test all state machine transitions and boundary conditions

**Pattern Example: Door Control FSM**

```c
/* Door FSM States: CLOSED, OPENING, OPEN, CLOSING, ERROR */

/* Test: Initial state is CLOSED */
void test_door_fsm_initial_state_is_closed(void) {
    door_fsm_init();
    door_state_t state = door_fsm_get_state();
    TEST_ASSERT_EQUAL(DOOR_STATE_CLOSED, state);
}

/* Test: CLOSED → OPENING on open command */
void test_door_fsm_closed_to_opening_on_open_cmd(void) {
    door_fsm_init();  /* Start in CLOSED */
    error_t result = door_fsm_process_command(DOOR_CMD_OPEN);
    TEST_ASSERT_EQUAL(ERROR_NONE, result);
    TEST_ASSERT_EQUAL(DOOR_STATE_OPENING, door_fsm_get_state());
}

/* Test: OPENING → OPEN when fully open */
void test_door_fsm_opening_to_open_when_fully_open(void) {
    door_fsm_set_state(DOOR_STATE_OPENING);  /* Force to OPENING */
    mock_door_position_set(100);  /* Mock: door fully open */
    
    door_fsm_update();  /* Process state machine */
    
    TEST_ASSERT_EQUAL(DOOR_STATE_OPEN, door_fsm_get_state());
}

/* Test: OPEN → CLOSING on close command */
void test_door_fsm_open_to_closing_on_close_cmd(void) {
    door_fsm_set_state(DOOR_STATE_OPEN);
    error_t result = door_fsm_process_command(DOOR_CMD_CLOSE);
    TEST_ASSERT_EQUAL(ERROR_NONE, result);
    TEST_ASSERT_EQUAL(DOOR_STATE_CLOSING, door_fsm_get_state());
}

/* Test: ANY STATE → ERROR on hardware fault */
void test_door_fsm_any_state_to_error_on_fault(void) {
    door_fsm_set_state(DOOR_STATE_OPENING);
    mock_hardware_inject_fault(FAULT_MOTOR_OVERLOAD);
    
    door_fsm_update();
    
    TEST_ASSERT_EQUAL(DOOR_STATE_ERROR, door_fsm_get_state());
}
```

### 3.4 Decision Table Pattern

**Purpose**: Test all combinations of boolean conditions

**Theory**: For N conditions, need 2^N tests for exhaustive coverage

**Pattern Example: Safety Interlock (2 conditions)**

```c
/* Function: bool safety_interlock_check(bool door_closed, bool brake_engaged);
 * Returns true if both door_closed AND brake_engaged, else false
 * 
 * Decision Table:
 * | door_closed | brake_engaged | Result |
 * |-------------|---------------|--------|
 * | false       | false         | false  |
 * | false       | true          | false  |
 * | true        | false         | false  |
 * | true        | true          | true   |
 */

void test_safety_interlock_both_false_returns_false(void) {
    bool result = safety_interlock_check(false, false);
    TEST_ASSERT_FALSE(result);
}

void test_safety_interlock_door_false_brake_true_returns_false(void) {
    bool result = safety_interlock_check(false, true);
    TEST_ASSERT_FALSE(result);
}

void test_safety_interlock_door_true_brake_false_returns_false(void) {
    bool result = safety_interlock_check(true, false);
    TEST_ASSERT_FALSE(result);
}

void test_safety_interlock_both_true_returns_true(void) {
    bool result = safety_interlock_check(true, true);
    TEST_ASSERT_TRUE(result);
}
```

### 3.5 Error Guessing Pattern

**Purpose**: Test known common failure modes based on experience

**Pattern Example: Common Error Scenarios**

```c
/* Error Guessing: Known common failures */

/* Error 1: NULL pointer */
void test_process_data_null_input_returns_error(void) {
    output_t output;
    error_t result = process_data(NULL, &output);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
}

/* Error 2: Zero divisor */
void test_calculate_ratio_zero_denominator_returns_error(void) {
    int32_t result;
    error_t err = calculate_ratio(100, 0, &result);
    TEST_ASSERT_EQUAL(ERROR_DIVIDE_BY_ZERO, err);
}

/* Error 3: Empty buffer */
void test_queue_dequeue_empty_returns_error(void) {
    queue_t queue;
    queue_init(&queue);  /* Empty queue */
    uint8_t value;
    error_t result = queue_dequeue(&queue, &value);
    TEST_ASSERT_EQUAL(ERROR_QUEUE_EMPTY, result);
}

/* Error 4: Overflow value */
void test_add_overflow_returns_error(void) {
    int32_t result;
    error_t err = add_safe(INT32_MAX, 1, &result);
    TEST_ASSERT_EQUAL(ERROR_OVERFLOW, err);
}

/* Error 5: Uninitialized module */
void test_sensor_read_before_init_returns_error(void) {
    /* Deliberately skip sensor_init() */
    sensor_reading_t reading;
    error_t result = sensor_read(0, &reading);
    TEST_ASSERT_EQUAL(ERROR_NOT_INITIALIZED, result);
}
```

---

## 4. Test Fixture Patterns

### 4.1 Basic Fixture Pattern

**Purpose**: Reset module state before each test

**Pattern**:
```c
/* Global state for module under test */
static module_state_t module_state;

void setUp(void) {
    /* Reset module state to known initial state */
    memset(&module_state, 0, sizeof(module_state));
    
    /* Initialize module */
    error_t result = module_init(&module_state);
    TEST_ASSERT_EQUAL(ERROR_NONE, result);
}

void tearDown(void) {
    /* Clean up module resources */
    module_shutdown(&module_state);
}

void test_module_function_nominal(void) {
    /* Test starts with clean state from setUp() */
    error_t result = module_function(&module_state, 10);
    TEST_ASSERT_EQUAL(ERROR_NONE, result);
}
/* tearDown() automatically called after test */
```

### 4.2 Hardware Mock Fixture Pattern

**Purpose**: Initialize mock hardware registers before each test

**Pattern**:
```c
/* Mock hardware registers */
static volatile uint32_t mock_control_register;
static volatile uint32_t mock_status_register;

void setUp(void) {
    /* Reset mock hardware to power-on state */
    mock_control_register = 0x00000000;
    mock_status_register = 0x00000001;  /* Ready bit set */
    
    /* Initialize hardware abstraction layer with mocks */
    hardware_init_with_mocks(&mock_control_register, &mock_status_register);
}

void tearDown(void) {
    /* No cleanup needed for mocks */
}

void test_hardware_write_sets_control_register(void) {
    hardware_write_control(0xABCD1234);
    TEST_ASSERT_EQUAL_HEX32(0xABCD1234, mock_control_register);
}
```

### 4.3 Multi-Module Fixture Pattern

**Purpose**: Set up multiple interdependent modules

**Pattern**:
```c
void setUp(void) {
    /* Initialize modules in dependency order */
    error_t result;
    
    /* 1. Hardware abstraction layer (no dependencies) */
    result = hal_init();
    TEST_ASSERT_EQUAL(ERROR_NONE, result);
    
    /* 2. Sensor manager (depends on HAL) */
    result = sensor_manager_init();
    TEST_ASSERT_EQUAL(ERROR_NONE, result);
    
    /* 3. Control logic (depends on sensor manager) */
    result = control_logic_init();
    TEST_ASSERT_EQUAL(ERROR_NONE, result);
}

void tearDown(void) {
    /* Shutdown in reverse order */
    control_logic_shutdown();
    sensor_manager_shutdown();
    hal_shutdown();
}
```

### 4.4 Error Injection Fixture Pattern

**Purpose**: Configure fault injection for specific test

**Pattern**:
```c
/* Fault injection control */
typedef struct {
    bool inject_null_pointer;
    bool inject_timeout;
    bool inject_hardware_fault;
    uint32_t fault_after_calls;  /* Inject fault after N calls */
} fault_injection_config_t;

static fault_injection_config_t fault_config;

void setUp(void) {
    /* Default: no faults */
    memset(&fault_config, 0, sizeof(fault_config));
    module_init();
}

void tearDown(void) {
    module_shutdown();
}

/* Test with fault injection */
void test_module_handles_hardware_fault(void) {
    /* Configure fault injection */
    fault_config.inject_hardware_fault = true;
    fault_config.fault_after_calls = 2;  /* Fault on 3rd call */
    
    /* Call function multiple times */
    error_t result;
    result = module_function();  /* Call 1: OK */
    TEST_ASSERT_EQUAL(ERROR_NONE, result);
    
    result = module_function();  /* Call 2: OK */
    TEST_ASSERT_EQUAL(ERROR_NONE, result);
    
    result = module_function();  /* Call 3: FAULT */
    TEST_ASSERT_EQUAL(ERROR_HARDWARE_FAULT, result);
}
```

### 4.5 Timeout Fixture Pattern

**Purpose**: Mock time for deterministic timeout testing

**Pattern**:
```c
/* Mock time (milliseconds since start) */
static uint32_t mock_time_ms = 0;

/* Override system time function */
uint32_t get_time_ms(void) {
    return mock_time_ms;
}

void setUp(void) {
    mock_time_ms = 0;  /* Reset time to zero */
    module_init();
}

void tearDown(void) {
    module_shutdown();
}

/* Test timeout detection */
void test_wait_for_ready_timeout_after_1000ms(void) {
    /* Start waiting (timeout = 1000ms) */
    error_t result = wait_for_ready(1000);
    
    /* Advance time to 999ms (before timeout) */
    mock_time_ms = 999;
    /* Status: still waiting */
    
    /* Advance time to 1000ms (timeout) */
    mock_time_ms = 1000;
    result = wait_for_ready(1000);
    TEST_ASSERT_EQUAL(ERROR_TIMEOUT, result);
}
```

---

## 5. Mocking and Stub Patterns

### 5.1 Simple Stub Pattern

**Purpose**: Replace external function with minimal implementation

**Pattern**:
```c
/* Original function (in production code): */
/* extern int32_t sensor_read_hardware(uint8_t channel); */

/* Stub replacement (in test code): */
int32_t sensor_read_hardware(uint8_t channel) {
    (void)channel;  /* Unused parameter */
    return 100;  /* Fixed value */
}

/* Test using stub */
void test_control_logic_uses_sensor_value(void) {
    /* sensor_read_hardware() will return 100 (stubbed) */
    int32_t result = control_logic_calculate();
    TEST_ASSERT_EQUAL(200, result);  /* Expects 100 * 2 = 200 */
}
```

### 5.2 Return Value Mock Pattern

**Purpose**: Configurable return value for each test

**Pattern**:
```c
/* Mock configuration */
static int32_t mock_sensor_return_value = 0;
static error_t mock_sensor_return_error = ERROR_NONE;

/* Mock function */
error_t sensor_read(uint8_t channel, int32_t* value) {
    (void)channel;
    
    if (mock_sensor_return_error != ERROR_NONE) {
        return mock_sensor_return_error;
    }
    
    if (value != NULL) {
        *value = mock_sensor_return_value;
    }
    return ERROR_NONE;
}

/* Test: Configure mock for success case */
void test_process_sensor_data_nominal(void) {
    mock_sensor_return_value = 50;
    mock_sensor_return_error = ERROR_NONE;
    
    int32_t result = process_sensor_data();
    TEST_ASSERT_EQUAL(100, result);  /* Expects 50 * 2 = 100 */
}

/* Test: Configure mock for error case */
void test_process_sensor_data_sensor_error(void) {
    mock_sensor_return_error = ERROR_TIMEOUT;
    
    int32_t result = process_sensor_data();
    TEST_ASSERT_EQUAL(-1, result);  /* Error handling */
}
```

### 5.3 Call Count Verification Pattern

**Purpose**: Verify function called N times

**Pattern**:
```c
/* Mock state */
static uint32_t mock_motor_start_call_count = 0;

/* Mock function */
void motor_start(void) {
    mock_motor_start_call_count++;
}

/* Reset in setUp */
void setUp(void) {
    mock_motor_start_call_count = 0;
}

/* Test: Verify function called exactly once */
void test_start_sequence_calls_motor_start_once(void) {
    start_sequence();
    TEST_ASSERT_EQUAL_UINT32(1, mock_motor_start_call_count);
}

/* Test: Verify function NOT called */
void test_idle_state_does_not_start_motor(void) {
    set_state(STATE_IDLE);
    update_state_machine();
    TEST_ASSERT_EQUAL_UINT32(0, mock_motor_start_call_count);
}
```

### 5.4 Parameter Capture Pattern

**Purpose**: Capture function arguments for assertion

**Pattern**:
```c
/* Mock state */
static uint8_t captured_channel = 0;
static uint32_t captured_value = 0;
static bool mock_write_called = false;

/* Mock function */
error_t hardware_write(uint8_t channel, uint32_t value) {
    mock_write_called = true;
    captured_channel = channel;
    captured_value = value;
    return ERROR_NONE;
}

void setUp(void) {
    mock_write_called = false;
    captured_channel = 0;
    captured_value = 0;
}

/* Test: Verify function called with correct parameters */
void test_control_writes_channel_5_with_value_1000(void) {
    control_update(5, 1000);
    
    TEST_ASSERT_TRUE(mock_write_called);
    TEST_ASSERT_EQUAL_UINT8(5, captured_channel);
    TEST_ASSERT_EQUAL_UINT32(1000, captured_value);
}
```

### 5.5 Sequence Mock Pattern

**Purpose**: Different return values per call

**Pattern**:
```c
/* Mock sequence state */
#define MAX_SEQUENCE_LENGTH 10
static int32_t mock_values[MAX_SEQUENCE_LENGTH];
static uint32_t mock_sequence_index = 0;
static uint32_t mock_sequence_length = 0;

/* Configure sequence */
void mock_set_sequence(const int32_t* values, uint32_t length) {
    TEST_ASSERT_TRUE(length <= MAX_SEQUENCE_LENGTH);
    memcpy(mock_values, values, length * sizeof(int32_t));
    mock_sequence_length = length;
    mock_sequence_index = 0;
}

/* Mock function - returns next value in sequence */
int32_t sensor_read(void) {
    if (mock_sequence_index < mock_sequence_length) {
        return mock_values[mock_sequence_index++];
    }
    return 0;  /* Default if sequence exhausted */
}

/* Test: Function adapts to changing sensor values */
void test_filter_adapts_to_changing_input(void) {
    /* Sequence: [10, 20, 30, 40, 50] */
    int32_t sequence[] = {10, 20, 30, 40, 50};
    mock_set_sequence(sequence, 5);
    
    filter_update();  /* Read 10 */
    filter_update();  /* Read 20 */
    filter_update();  /* Read 30 */
    
    int32_t result = filter_get_output();
    TEST_ASSERT_EQUAL(20, result);  /* Average of 10, 20, 30 */
}
```

### 5.6 Hardware Register Mock Pattern

**Purpose**: Mock memory-mapped I/O

**Pattern**:
```c
/* Mock hardware registers (file scope) */
static volatile uint32_t mock_control_reg = 0;
static volatile uint32_t mock_status_reg = 0;

/* Mock register addresses (match hardware spec) */
#define CONTROL_REG_ADDR ((volatile uint32_t*)&mock_control_reg)
#define STATUS_REG_ADDR  ((volatile uint32_t*)&mock_status_reg)

/* Hardware abstraction layer uses mock addresses */
void hardware_init_test_mode(void) {
    /* Point HAL to mock registers instead of real hardware */
    hal_set_control_register(CONTROL_REG_ADDR);
    hal_set_status_register(STATUS_REG_ADDR);
}

void setUp(void) {
    mock_control_reg = 0;
    mock_status_reg = 0x0001;  /* Ready bit set */
    hardware_init_test_mode();
}

/* Test: Verify register write */
void test_start_motor_sets_control_bit(void) {
    motor_start();
    TEST_ASSERT_EQUAL_HEX32(0x0001, mock_control_reg);  /* Bit 0 set */
}

/* Test: Function reads status register */
void test_is_ready_returns_true_when_ready_bit_set(void) {
    mock_status_reg = 0x0001;  /* Ready bit set */
    bool ready = hardware_is_ready();
    TEST_ASSERT_TRUE(ready);
}
```

### 5.7 Time Mock Pattern

**Purpose**: Deterministic time for testing

**Pattern**:
```c
/* Mock time (milliseconds) */
static uint32_t mock_current_time_ms = 0;

/* Override system time function */
uint32_t system_get_time_ms(void) {
    return mock_current_time_ms;
}

/* Helper: Advance time */
void mock_time_advance(uint32_t delta_ms) {
    mock_current_time_ms += delta_ms;
}

void setUp(void) {
    mock_current_time_ms = 0;
}

/* Test: Timeout detection */
void test_wait_times_out_after_1000ms(void) {
    /* Start operation with 1000ms timeout */
    operation_start(1000);
    
    /* Advance time to 999ms (still within timeout) */
    mock_time_advance(999);
    bool timedout = operation_check_timeout();
    TEST_ASSERT_FALSE(timedout);
    
    /* Advance time to 1000ms (timeout) */
    mock_time_advance(1);
    timedout = operation_check_timeout();
    TEST_ASSERT_TRUE(timedout);
}
```

---

## 6. Assertion Patterns

### 6.1 Unity Assertion Macro Reference

**Boolean Assertions**:
```c
TEST_ASSERT(condition)                /* Generic boolean */
TEST_ASSERT_TRUE(condition)          /* Explicit true */
TEST_ASSERT_FALSE(condition)         /* Explicit false */
TEST_ASSERT_UNLESS(condition)        /* Same as TEST_ASSERT_FALSE */
```

**Equality Assertions**:
```c
TEST_ASSERT_EQUAL(expected, actual)           /* Generic equality */
TEST_ASSERT_EQUAL_INT(expected, actual)       /* Signed int */
TEST_ASSERT_EQUAL_UINT(expected, actual)      /* Unsigned int */
TEST_ASSERT_EQUAL_INT8(expected, actual)      /* int8_t */
TEST_ASSERT_EQUAL_UINT8(expected, actual)     /* uint8_t */
TEST_ASSERT_EQUAL_INT16(expected, actual)     /* int16_t */
TEST_ASSERT_EQUAL_UINT16(expected, actual)    /* uint16_t */
TEST_ASSERT_EQUAL_INT32(expected, actual)     /* int32_t */
TEST_ASSERT_EQUAL_UINT32(expected, actual)    /* uint32_t */
TEST_ASSERT_EQUAL_HEX8(expected, actual)      /* Hex comparison */
TEST_ASSERT_EQUAL_HEX16(expected, actual)     /* Hex comparison */
TEST_ASSERT_EQUAL_HEX32(expected, actual)     /* Hex comparison */
```

**Pointer Assertions**:
```c
TEST_ASSERT_NULL(pointer)             /* Pointer is NULL */
TEST_ASSERT_NOT_NULL(pointer)         /* Pointer not NULL */
TEST_ASSERT_EQUAL_PTR(expected, actual) /* Pointer equality */
```

**Memory Assertions**:
```c
TEST_ASSERT_EQUAL_MEMORY(expected, actual, len)  /* Memory comparison */
TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, actual, len, count) /* Array of memory blocks */
```

**Floating-Point Assertions** (if needed):
```c
TEST_ASSERT_EQUAL_FLOAT(expected, actual)        /* Float equality */
TEST_ASSERT_EQUAL_DOUBLE(expected, actual)       /* Double equality */
TEST_ASSERT_FLOAT_WITHIN(delta, expected, actual) /* Float within tolerance */
```

**String Assertions**:
```c
TEST_ASSERT_EQUAL_STRING(expected, actual)       /* String equality */
TEST_ASSERT_EQUAL_STRING_LEN(expected, actual, len) /* First len chars */
```

**Explicit Failure**:
```c
TEST_FAIL()                           /* Explicit failure */
TEST_FAIL_MESSAGE(message)            /* Failure with message */
TEST_IGNORE()                         /* Skip test */
TEST_IGNORE_MESSAGE(message)          /* Skip with reason */
```

### 6.2 Range Assertion Pattern

**Purpose**: Verify value within expected range

**Pattern**:
```c
/* Range check: value between min and max (inclusive) */
void test_sensor_value_in_valid_range(void) {
    int32_t value = sensor_read();
    TEST_ASSERT_TRUE((value >= 0) && (value <= 4095));  /* 12-bit ADC range */
}

/* Alternative: Separate assertions for clarity */
void test_sensor_value_in_valid_range_verbose(void) {
    int32_t value = sensor_read();
    TEST_ASSERT_GREATER_OR_EQUAL(0, value);     /* value >= 0 */
    TEST_ASSERT_LESS_OR_EQUAL(4095, value);     /* value <= 4095 */
}
```

### 6.3 Struct Assertion Pattern

**Purpose**: Compare struct fields individually

**Pattern**:
```c
typedef struct {
    uint8_t id;
    uint16_t value;
    bool valid;
} sensor_reading_t;

/* Compare struct field-by-field */
void test_sensor_read_returns_correct_data(void) {
    sensor_reading_t expected = {
        .id = 5,
        .value = 1234,
        .valid = true
    };
    
    sensor_reading_t actual;
    error_t result = sensor_read(5, &actual);
    
    TEST_ASSERT_EQUAL(ERROR_NONE, result);
    TEST_ASSERT_EQUAL_UINT8(expected.id, actual.id);
    TEST_ASSERT_EQUAL_UINT16(expected.value, actual.value);
    TEST_ASSERT_EQUAL(expected.valid, actual.valid);
}

/* Alternative: Memory comparison (if struct has no padding issues) */
void test_sensor_read_memory_compare(void) {
    sensor_reading_t expected = {.id = 5, .value = 1234, .valid = true};
    sensor_reading_t actual;
    
    sensor_read(5, &actual);
    
    TEST_ASSERT_EQUAL_MEMORY(&expected, &actual, sizeof(sensor_reading_t));
}
```

### 6.4 Array Assertion Pattern

**Purpose**: Compare arrays element-by-element

**Pattern**:
```c
/* Compare arrays */
void test_filter_output_array_correct(void) {
    uint8_t expected[5] = {10, 20, 30, 40, 50};
    uint8_t actual[5];
    
    filter_get_output_array(actual, 5);
    
    /* Option 1: Memory comparison */
    TEST_ASSERT_EQUAL_MEMORY(expected, actual, 5);
    
    /* Option 2: Element-by-element (for debugging) */
    for (uint32_t i = 0; i < 5; i++) {
        TEST_ASSERT_EQUAL_UINT8(expected[i], actual[i]);
    }
}
```

### 6.5 Enum Assertion Pattern

**Purpose**: Compare enum states with descriptive names

**Pattern**:
```c
typedef enum {
    STATE_IDLE = 0,
    STATE_RUNNING = 1,
    STATE_ERROR = 2
} system_state_t;

/* Enum comparison */
void test_state_machine_transitions_to_running(void) {
    system_state_t state = get_current_state();
    TEST_ASSERT_EQUAL(STATE_RUNNING, state);
    
    /* Alternative: Use int cast for better error messages */
    TEST_ASSERT_EQUAL_INT32(STATE_RUNNING, (int32_t)state);
}
```

### 6.6 Error Code Assertion Pattern

**Purpose**: Verify specific error code returned

**Pattern**:
```c
typedef enum {
    ERROR_NONE = 0,
    ERROR_NULL_POINTER = 1,
    ERROR_OUT_OF_RANGE = 2,
    ERROR_TIMEOUT = 3
} error_t;

/* Error code assertions */
void test_function_returns_null_pointer_error(void) {
    error_t result = function_under_test(NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
}

/* Check for success (common pattern) */
void test_function_succeeds(void) {
    error_t result = function_under_test(&valid_data);
    TEST_ASSERT_EQUAL(ERROR_NONE, result);  /* Success */
}
```

### 6.7 Side Effect Assertion Pattern

**Purpose**: Verify state changes after function call

**Pattern**:
```c
/* Verify state changed */
void test_motor_start_sets_motor_running_flag(void) {
    /* Precondition: motor not running */
    TEST_ASSERT_FALSE(is_motor_running());
    
    /* Action */
    motor_start();
    
    /* Postcondition: motor running */
    TEST_ASSERT_TRUE(is_motor_running());
}

/* Verify multiple state changes */
void test_reset_clears_all_flags(void) {
    /* Setup: set flags */
    set_flag_a(true);
    set_flag_b(true);
    
    /* Action */
    system_reset();
    
    /* Verify all flags cleared */
    TEST_ASSERT_FALSE(get_flag_a());
    TEST_ASSERT_FALSE(get_flag_b());
}
```

---

## 7. Coverage Achievement Patterns

### 7.1 Statement Coverage Pattern

**Goal**: Execute every statement at least once

**Pattern**:
```c
/* Function under test:
 * error_t process(uint32_t value) {
 *     if (value > 100) {
 *         return ERROR_OUT_OF_RANGE;  // Statement 1
 *     }
 *     uint32_t result = value * 2;    // Statement 2
 *     return ERROR_NONE;               // Statement 3
 * }
 */

/* Test 1: Execute statement 1 (error path) */
void test_process_out_of_range(void) {
    error_t result = process(101);
    TEST_ASSERT_EQUAL(ERROR_OUT_OF_RANGE, result);
    /* Executes: Statement 1 */
}

/* Test 2: Execute statements 2 and 3 (success path) */
void test_process_valid_value(void) {
    error_t result = process(50);
    TEST_ASSERT_EQUAL(ERROR_NONE, result);
    /* Executes: Statement 2, Statement 3 */
}

/* Coverage: 100% statement coverage (all 3 statements executed) */
```

**Verification with gcov**:
```bash
# Run tests with coverage
gcc -fprofile-arcs -ftest-coverage test_module.c module.c -o test_module
./test_module

# Generate coverage report
gcov module.c
# Output: 100% statement coverage
```

### 7.2 Branch Coverage Pattern

**Goal**: Execute every branch (true and false) of every condition

**Pattern**:
```c
/* Function under test:
 * error_t validate(uint32_t value) {
 *     if (value < 10) {           // Branch A
 *         return ERROR_TOO_LOW;
 *     }
 *     if (value > 100) {          // Branch B
 *         return ERROR_TOO_HIGH;
 *     }
 *     return ERROR_NONE;
 * }
 */

/* Test 1: Branch A true */
void test_validate_too_low(void) {
    error_t result = validate(5);
    TEST_ASSERT_EQUAL(ERROR_TOO_LOW, result);
    /* Branch A: TRUE, Branch B: NOT EXECUTED */
}

/* Test 2: Branch A false, Branch B true */
void test_validate_too_high(void) {
    error_t result = validate(150);
    TEST_ASSERT_EQUAL(ERROR_TOO_HIGH, result);
    /* Branch A: FALSE, Branch B: TRUE */
}

/* Test 3: Branch A false, Branch B false */
void test_validate_valid(void) {
    error_t result = validate(50);
    TEST_ASSERT_EQUAL(ERROR_NONE, result);
    /* Branch A: FALSE, Branch B: FALSE */
}

/* Coverage: 100% branch coverage (all true/false paths executed) */
```

### 7.3 Condition Coverage Pattern

**Goal**: Each boolean sub-expression evaluated to true and false

**Pattern**:
```c
/* Function under test:
 * bool safety_check(bool door_closed, bool brake_engaged) {
 *     if (door_closed && brake_engaged) {  // Condition: A && B
 *         return true;
 *     }
 *     return false;
 * }
 */

/* Condition coverage requires:
 * - door_closed evaluated to TRUE and FALSE
 * - brake_engaged evaluated to TRUE and FALSE
 */

/* Test 1: door_closed = TRUE, brake_engaged = TRUE */
void test_safety_check_both_true(void) {
    bool result = safety_check(true, true);
    TEST_ASSERT_TRUE(result);
    /* Condition A: TRUE, Condition B: TRUE */
}

/* Test 2: door_closed = FALSE, brake_engaged = TRUE */
void test_safety_check_door_false(void) {
    bool result = safety_check(false, true);
    TEST_ASSERT_FALSE(result);
    /* Condition A: FALSE, Condition B: TRUE (short-circuit: B not evaluated) */
}

/* Test 3: door_closed = TRUE, brake_engaged = FALSE */
void test_safety_check_brake_false(void) {
    bool result = safety_check(true, false);
    TEST_ASSERT_FALSE(result);
    /* Condition A: TRUE, Condition B: FALSE */
}

/* Coverage: 100% condition coverage (each condition TRUE and FALSE) */
```

### 7.4 MC/DC Pattern (Modified Condition/Decision Coverage)

**Goal**: Each condition independently affects the outcome

**Theory**: For N conditions, need minimum N+1 tests

**Pattern Example: 2-Condition MC/DC**

```c
/* Function: bool check(bool A, bool B) { return A && B; } */

/* MC/DC Test Cases (3 tests for 2 conditions):
 * | Test | A | B | Result | Shows |
 * |------|---|---|--------|-------|
 * | 1    | T | T | TRUE   | Baseline |
 * | 2    | F | T | FALSE  | A independently affects result |
 * | 3    | T | F | FALSE  | B independently affects result |
 */

void test_check_both_true(void) {
    TEST_ASSERT_TRUE(check(true, true));   /* Test 1 */
}

void test_check_a_false(void) {
    TEST_ASSERT_FALSE(check(false, true)); /* Test 2: A flip */
}

void test_check_b_false(void) {
    TEST_ASSERT_FALSE(check(true, false)); /* Test 3: B flip */
}

/* MC/DC Coverage: 100% (minimum 3 tests, each condition independently shown) */
```

**Pattern Example: 3-Condition MC/DC**

```c
/* Function: bool interlock(bool A, bool B, bool C) { return A && (B || C); } */

/* MC/DC Test Cases (minimum 4 tests for 3 conditions):
 * | Test | A | B | C | Result | Independent Condition |
 * |------|---|---|---|--------|----------------------|
 * | 1    | T | T | F | TRUE   | Baseline             |
 * | 2    | F | T | F | FALSE  | A                    |
 * | 3    | T | F | F | FALSE  | B (C false)          |
 * | 4    | T | T | T | TRUE   | C (B true, C changes)|
 */

void test_interlock_a_true_b_true_c_false(void) {
    TEST_ASSERT_TRUE(interlock(true, true, false));
}

void test_interlock_a_false(void) {
    TEST_ASSERT_FALSE(interlock(false, true, false));  /* A flip */
}

void test_interlock_b_false_c_false(void) {
    TEST_ASSERT_FALSE(interlock(true, false, false));  /* B flip */
}

void test_interlock_c_true(void) {
    TEST_ASSERT_TRUE(interlock(true, true, true));     /* C flip */
}
```

### 7.5 Coverage Gap Analysis Pattern

**Purpose**: Find uncovered code with gcov

**Pattern**:
```bash
# Step 1: Run tests with coverage
gcc --coverage test_module.c module.c -o test_module
./test_module

# Step 2: Generate coverage data
gcov module.c

# Step 3: View uncovered lines
cat module.c.gcov | grep "#####"
# "#####" indicates line NOT executed

# Example output:
#     10:   11:  if (value < 10) {
#     10:   12:      return ERROR_TOO_LOW;
# #####:   13:  }
# #####:   14:  if (value > 100) {
# #####:   15:      return ERROR_TOO_HIGH;
# #####:   16:  }
#     10:   17:  return ERROR_NONE;

# Lines 13-16 not covered → need test with value > 100
```

### 7.6 100% Coverage Strategy (SIL 3-4)

**Systematic Approach**:

```c
/* Step 1: List all functions in module */
/* module.c exports: init(), process(), shutdown() */

/* Step 2: List all branches in each function */
/* process() has 3 branches:
 * - Branch 1: value < 10 (TRUE/FALSE)
 * - Branch 2: value > 100 (TRUE/FALSE)
 * - Branch 3: default (10 <= value <= 100)
 */

/* Step 3: Design test for each branch */
void test_process_too_low(void)  { /* Branch 1 TRUE */ }
void test_process_too_high(void) { /* Branch 2 TRUE */ }
void test_process_valid(void)    { /* Both FALSE, Branch 3 */ }

/* Step 4: Design tests for error paths */
void test_process_null_pointer(void) { /* NULL check branch */ }

/* Step 5: Run coverage and verify 100% */
/* lcov --summary coverage.info
 * lines......: 100.0% (50 of 50 lines)
 * functions..: 100.0% (5 of 5 functions)
 * branches...: 100.0% (20 of 20 branches)
 */
```

---

## 8. Error Path Testing Patterns

### 8.1 NULL Input Pattern

**Purpose**: Test every NULL pointer path

**Pattern**:
```c
/* Function: error_t process(const input_t* in, output_t* out); */

/* Test NULL input pointer */
void test_process_null_input_returns_error(void) {
    output_t output;
    error_t result = process(NULL, &output);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
}

/* Test NULL output pointer */
void test_process_null_output_returns_error(void) {
    input_t input = {.value = 10};
    error_t result = process(&input, NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
}

/* Test both NULL */
void test_process_both_null_returns_error(void) {
    error_t result = process(NULL, NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
}
```

### 8.2 Out-of-Range Pattern

**Purpose**: Test values outside valid range

**Pattern**:
```c
/* Function: error_t set_speed(uint8_t speed);  // Valid: 0-100 */

/* Test below minimum */
void test_set_speed_below_min(void) {
    /* uint8_t cannot be < 0, but test 0 boundary */
    error_t result = set_speed(0);
    TEST_ASSERT_EQUAL(ERROR_NONE, result);  /* 0 is valid */
}

/* Test above maximum */
void test_set_speed_above_max(void) {
    error_t result = set_speed(101);
    TEST_ASSERT_EQUAL(ERROR_OUT_OF_RANGE, result);
}

/* Test far above maximum */
void test_set_speed_far_above_max(void) {
    error_t result = set_speed(255);
    TEST_ASSERT_EQUAL(ERROR_OUT_OF_RANGE, result);
}
```

### 8.3 Overflow Pattern

**Purpose**: Test arithmetic overflow detection

**Pattern**:
```c
/* Function: error_t add_safe(int32_t a, int32_t b, int32_t* result); */

/* Test positive overflow */
void test_add_safe_positive_overflow(void) {
    int32_t result;
    error_t err = add_safe(INT32_MAX, 1, &result);
    TEST_ASSERT_EQUAL(ERROR_OVERFLOW, err);
}

/* Test negative overflow */
void test_add_safe_negative_overflow(void) {
    int32_t result;
    error_t err = add_safe(INT32_MIN, -1, &result);
    TEST_ASSERT_EQUAL(ERROR_UNDERFLOW, err);
}

/* Test multiplication overflow */
void test_multiply_safe_overflow(void) {
    int32_t result;
    error_t err = multiply_safe(INT32_MAX, 2, &result);
    TEST_ASSERT_EQUAL(ERROR_OVERFLOW, err);
}
```

### 8.4 Timeout Pattern

**Purpose**: Test timeout detection and recovery

**Pattern**:
```c
/* Use mock time (from Section 4.5) */

/* Test timeout after expected duration */
void test_wait_for_ready_times_out(void) {
    mock_time_ms = 0;
    error_t result = wait_for_ready_start(1000);  /* 1000ms timeout */
    
    mock_time_ms = 1000;  /* Advance to timeout */
    result = wait_for_ready_check();
    TEST_ASSERT_EQUAL(ERROR_TIMEOUT, result);
}

/* Test recovery after timeout */
void test_operation_recovers_after_timeout(void) {
    /* Simulate timeout */
    mock_time_ms = 1000;
    error_t result = operation_execute(100);  /* 100ms timeout */
    TEST_ASSERT_EQUAL(ERROR_TIMEOUT, result);
    
    /* Reset and try again */
    mock_time_ms = 0;
    operation_reset();
    result = operation_execute(100);
    TEST_ASSERT_EQUAL(ERROR_NONE, result);  /* Success after recovery */
}
```

### 8.5 Corrupted Data Pattern

**Purpose**: Inject corrupted data and verify rejection

**Pattern**:
```c
/* Test invalid checksum */
void test_packet_invalid_checksum_rejected(void) {
    packet_t packet = {
        .data = {0x01, 0x02, 0x03},
        .checksum = 0xFF  /* Invalid checksum */
    };
    
    error_t result = packet_validate(&packet);
    TEST_ASSERT_EQUAL(ERROR_INVALID_CHECKSUM, result);
}

/* Test out-of-sequence packet */
void test_packet_out_of_sequence_rejected(void) {
    /* Receive packet sequence: 1, 2, 5 (missing 3, 4) */
    packet_receive(1);
    packet_receive(2);
    error_t result = packet_receive(5);
    TEST_ASSERT_EQUAL(ERROR_OUT_OF_SEQUENCE, result);
}

/* Test corrupted state machine data */
void test_fsm_invalid_state_enters_error_state(void) {
    /* Corrupt state to invalid value */
    fsm_corrupt_state(99);  /* Invalid state */
    
    fsm_update();
    
    TEST_ASSERT_EQUAL(STATE_ERROR, fsm_get_state());
}
```

### 8.6 Hardware Fault Pattern

**Purpose**: Mock hardware failures and verify response

**Pattern**:
```c
/* Test hardware read failure */
void test_sensor_read_hardware_fault(void) {
    mock_hardware_inject_fault(FAULT_SENSOR_DISCONNECTED);
    
    sensor_reading_t reading;
    error_t result = sensor_read(0, &reading);
    
    TEST_ASSERT_EQUAL(ERROR_HARDWARE_FAULT, result);
    TEST_ASSERT_FALSE(reading.valid);  /* Data marked invalid */
}

/* Test hardware timeout */
void test_hardware_write_timeout(void) {
    mock_hardware_set_response_time(2000);  /* 2 seconds */
    
    error_t result = hardware_write(0x1234, 1000);  /* 1 second timeout */
    TEST_ASSERT_EQUAL(ERROR_TIMEOUT, result);
}

/* Test hardware fault recovery */
void test_system_recovers_from_hardware_fault(void) {
    /* Inject fault */
    mock_hardware_inject_fault(FAULT_TEMPORARY);
    error_t result = system_operation();
    TEST_ASSERT_EQUAL(ERROR_HARDWARE_FAULT, result);
    
    /* Clear fault */
    mock_hardware_clear_fault();
    
    /* Retry */
    result = system_operation();
    TEST_ASSERT_EQUAL(ERROR_NONE, result);  /* Recovered */
}
```

---

## 9. Parameterized and Table-Driven Test Patterns

### 9.1 Array-Driven Test Pattern

**Purpose**: Test multiple inputs with table of test vectors

**Pattern**:
```c
/* Test vector structure */
typedef struct {
    uint32_t input;
    uint32_t expected_output;
    const char* description;
} test_vector_t;

/* Test table */
static const test_vector_t test_vectors[] = {
    {0,   0,   "Zero input"},
    {1,   2,   "Minimum positive"},
    {10,  20,  "Normal value"},
    {50,  100, "Mid-range"},
    {100, 200, "Maximum valid"},
};

/* Table-driven test */
void test_double_value_table_driven(void) {
    const uint32_t num_vectors = sizeof(test_vectors) / sizeof(test_vectors[0]);
    
    for (uint32_t i = 0; i < num_vectors; i++) {
        uint32_t actual = double_value(test_vectors[i].input);
        
        /* Assert with descriptive message */
        char message[100];
        snprintf(message, sizeof(message), "Test vector %u: %s", 
                 i, test_vectors[i].description);
        
        if (actual != test_vectors[i].expected_output) {
            TEST_FAIL_MESSAGE(message);
        }
    }
}
```

### 9.2 Boundary Table Pattern

**Purpose**: All boundaries in one table

**Pattern**:
```c
/* Boundary test vectors */
typedef struct {
    int32_t value;
    error_t expected_error;
    const char* description;
} boundary_test_t;

static const boundary_test_t boundaries[] = {
    {-1,   ERROR_OUT_OF_RANGE, "Below minimum"},
    {0,    ERROR_NONE,         "Minimum valid"},
    {1,    ERROR_NONE,         "Above minimum"},
    {99,   ERROR_NONE,         "Below maximum"},
    {100,  ERROR_NONE,         "Maximum valid"},
    {101,  ERROR_OUT_OF_RANGE, "Above maximum"},
};

void test_set_value_boundaries(void) {
    for (uint32_t i = 0; i < 6; i++) {
        error_t result = set_value(boundaries[i].value);
        TEST_ASSERT_EQUAL_MESSAGE(boundaries[i].expected_error, result,
                                  boundaries[i].description);
    }
}
```

### 9.3 Error Code Table Pattern

**Purpose**: All error conditions in table

**Pattern**:
```c
/* Error injection test vectors */
typedef struct {
    const char* description;
    void (*setup_fault)(void);
    error_t expected_error;
} error_test_t;

/* Fault injection helpers */
void inject_null_pointer(void)      { mock_return_null_pointer = true; }
void inject_timeout(void)           { mock_inject_timeout = true; }
void inject_hardware_fault(void)    { mock_hardware_fault = true; }

static const error_test_t error_tests[] = {
    {"NULL pointer",     inject_null_pointer,   ERROR_NULL_POINTER},
    {"Timeout",          inject_timeout,        ERROR_TIMEOUT},
    {"Hardware fault",   inject_hardware_fault, ERROR_HARDWARE_FAULT},
};

void test_error_handling_comprehensive(void) {
    for (uint32_t i = 0; i < 3; i++) {
        /* Setup fault */
        error_tests[i].setup_fault();
        
        /* Execute function */
        error_t result = function_under_test();
        
        /* Verify error code */
        TEST_ASSERT_EQUAL_MESSAGE(error_tests[i].expected_error, result,
                                  error_tests[i].description);
        
        /* Clear fault for next test */
        mock_reset();
    }
}
```

---

## 10. Test Documentation Patterns

### 10.1 Test Header Comment Pattern

**Purpose**: Document test purpose, requirements, coverage

**Pattern**:
```c
/* ==================================================================
 * Test Suite: Sensor Manager
 * Module: sensor_manager.c
 * 
 * Purpose: Unit tests for sensor reading and validation functions
 * 
 * Requirements Covered:
 * - REQ-SENSOR-001: Read sensor value from channel
 * - REQ-SENSOR-002: Validate sensor input range
 * - REQ-SENSOR-003: Detect sensor faults
 * 
 * Coverage Targets (SIL 3):
 * - Statement coverage: 100%
 * - Branch coverage: 100%
 * - Condition coverage: 100%
 * 
 * Test Configuration:
 * - Test Framework: Unity 2.5.2
 * - Mock: mock_hardware.c (sensor HAL)
 * - Build: gcc --coverage
 * 
 * Author: [Name]
 * Date: 2026-03-13
 * Reviewed by: [Reviewer]
 * ================================================================== */

#include "unity.h"
#include "sensor_manager.h"
/* ... test code ... */
```

### 10.2 Test Case Comment Pattern

**Purpose**: Document each test case purpose and coverage

**Pattern**:
```c
/* ------------------------------------------------------------------
 * Test: sensor_read_valid_channel_returns_success
 * 
 * Purpose: Verify sensor_read returns success for valid channel
 * 
 * Requirement: REQ-SENSOR-001
 * 
 * Equivalence Class: Valid channel (0-9)
 * Boundary: N/A
 * 
 * Coverage:
 * - Statement: sensor_read function body
 * - Branch: channel validation (true path)
 * 
 * Preconditions:
 * - Sensor manager initialized
 * - Hardware mock configured for success
 * 
 * Expected Result:
 * - Function returns ERROR_NONE
 * - Reading struct populated with valid data
 * ------------------------------------------------------------------ */
void test_sensor_read_valid_channel_returns_success(void) {
    uint8_t channel = 5;
    sensor_reading_t reading;
    
    error_t result = sensor_read(channel, &reading);
    
    TEST_ASSERT_EQUAL(ERROR_NONE, result);
    TEST_ASSERT_TRUE(reading.valid);
}
```

### 10.3 Test Result Recording Pattern

**Purpose**: Traceability from test to requirement

**Pattern**:
```bash
# After test execution, record results in traceability database

# Command: Traceability Manager CLI
traceability-mgr link-test-result \
    --test-id "TEST-SENSOR-001" \
    --req-id "REQ-SENSOR-001" \
    --status "PASS" \
    --coverage "100%"

# Generated entry in traceability database:
# TEST-SENSOR-001 → REQ-SENSOR-001 [PASS, 100% coverage]
```

**Traceability Matrix Entry**:
```markdown
| Requirement | Test Case | Status | Coverage |
|-------------|-----------|--------|----------|
| REQ-SENSOR-001 | TEST-SENSOR-001 | PASS | 100% |
| REQ-SENSOR-002 | TEST-SENSOR-002 | PASS | 100% |
| REQ-SENSOR-003 | TEST-SENSOR-003 | PASS | 100% |
```

### 10.4 Coverage Report Interpretation Pattern

**Purpose**: Read and interpret gcov/lcov output

**gcov Output**:
```
File 'sensor_manager.c'
Lines executed:100.00% of 50
Branches executed:100.00% of 20
Taken at least once:100.00% of 20
Calls executed:100.00% of 10
```

**Interpretation**:
- **Lines executed: 100%** → All statements covered ✓
- **Branches executed: 100%** → All if/else covered ✓
- **Taken at least once: 100%** → Both true/false paths covered ✓
- **Calls executed: 100%** → All function calls covered ✓

**lcov HTML Report**:
```bash
# Generate HTML coverage report
lcov --capture --directory build/test --output-file coverage.info
genhtml coverage.info --output-directory coverage_html

# Open in browser
xdg-open coverage_html/index.html
```

### 10.5 Test Report Entry Pattern

**Purpose**: Standard fields for test log

**Pattern**:
```markdown
## Test Execution Report

**Test Suite**: Sensor Manager Unit Tests  
**Date**: 2026-03-13  
**Tester**: John Doe  
**Environment**: Ubuntu 22.04, GCC 11.4.0

### Summary

| Metric | Value |
|--------|-------|
| Total Tests | 25 |
| Passed | 25 |
| Failed | 0 |
| Skipped | 0 |
| Statement Coverage | 100.0% |
| Branch Coverage | 100.0% |
| Condition Coverage | 100.0% |
| Execution Time | 0.45 seconds |

### Test Results

| Test ID | Test Name | Result | Duration |
|---------|-----------|--------|----------|
| TEST-SENSOR-001 | test_sensor_read_valid_channel | PASS | 0.02s |
| TEST-SENSOR-002 | test_sensor_read_null_pointer | PASS | 0.01s |
| TEST-SENSOR-003 | test_sensor_read_invalid_channel | PASS | 0.01s |
| ... | ... | ... | ... |

### Coverage Details

**Module**: sensor_manager.c
- Lines: 50/50 (100.0%)
- Functions: 5/5 (100.0%)
- Branches: 20/20 (100.0%)

### Defects Found

None

### Traceability

| Requirement | Test Cases | Status |
|-------------|------------|--------|
| REQ-SENSOR-001 | TEST-SENSOR-001 | PASS |
| REQ-SENSOR-002 | TEST-SENSOR-002, TEST-SENSOR-003 | PASS |
| REQ-SENSOR-003 | TEST-SENSOR-004, TEST-SENSOR-005 | PASS |
```

---

## Summary

This resource provides a comprehensive catalog of unit testing patterns for EN 50128 railway safety software using the Unity test framework. Key takeaways:

**Coverage Requirements (SIL 3-4)**:
- 100% statement, branch, and condition coverage (MANDATORY)
- MC/DC recommended (minimum N+1 tests for N conditions)
- Verified with gcov/lcov + custom MC/DC analyzer

**Test Design Patterns**:
1. **Equivalence Partitioning** - Representative values per class
2. **Boundary Value** - Test at min, max, ±1
3. **State Transition** - All FSM transitions
4. **Decision Table** - All boolean combinations
5. **Error Guessing** - Known failure modes

**Test Implementation**:
- Unity framework (lightweight, C-native, MISRA C compliant)
- Test fixtures (setUp/tearDown) for clean state
- Mocking patterns for hardware, time, dependencies
- Table-driven tests for comprehensive coverage

**Error Path Testing**:
- NULL pointer checks
- Out-of-range values
- Arithmetic overflow
- Timeouts
- Corrupted data
- Hardware faults

**Documentation**:
- Test header comments with requirements, coverage targets
- Test case comments with equivalence class, boundary, coverage
- Traceability Manager integration (test → requirement)
- Coverage reports (gcov/lcov HTML)

**Next Steps**:
1. Review this catalog before writing tests
2. Follow `workflows/unit-testing-workflow.md` for step-by-step process
3. Use patterns from this resource for test design
4. Verify 100% coverage with gcov/lcov (SIL 3-4)
5. Document traceability with Traceability Manager CLI

**Traceability**:
- Tests trace to Software Requirements Specification (DOC-5) via Traceability Manager
- Test results documented in Component Test Report (DOC-14)
- Coverage verified in Component Test Report and Software Source Code Verification Report (DOC-19)

---

**Document Control**:
- **Version**: 1.0
- **Date**: 2026-03-13
- **Author**: EN 50128 Implementation Team
- **Approved by**: [Pending]
- **Next Review**: [After first project use]
