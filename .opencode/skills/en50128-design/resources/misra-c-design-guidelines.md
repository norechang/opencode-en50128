# MISRA C Design Guidelines for EN 50128 Railway Safety Software

**Purpose**: This document provides comprehensive guidance on applying MISRA C:2012 principles during the software design phase (not just coding) for EN 50128-compliant railway safety software. It covers design decisions that affect MISRA C compliance, including type selection, memory management, control flow, error handling, and data structure design.

**Scope**: Applies to Software Architecture Specification (DOC-9) and Software Design Specification (DOC-10) development.

**Audience**: Designers (DES), Implementers (IMP), Verifiers (VER), Quality Assurance (QUA)

**EN 50128 Reference**: Table A.12 "Design and Coding Standards" - **MANDATORY SIL 3-4**, Highly Recommended SIL 2

---

## Table of Contents

1. [Introduction to MISRA C Design Considerations](#1-introduction-to-misra-c-design-considerations)
2. [Type System Design](#2-type-system-design)
3. [Memory Management Design](#3-memory-management-design)
4. [Control Flow Design](#4-control-flow-design)
5. [Error Handling Design](#5-error-handling-design)
6. [Function Design](#6-function-design)
7. [Data Structure Design](#7-data-structure-design)
8. [Interface Design](#8-interface-design)
9. [Concurrency Design](#9-concurrency-design)
10. [MISRA C Deviations Process](#10-misra-c-deviations-process)
11. [Design Review Checklist](#11-design-review-checklist)
12. [References](#12-references)

---

## 1. Introduction to MISRA C Design Considerations

### 1.1 What is MISRA C?

**MISRA C** (Motor Industry Software Reliability Association C) is a set of software development guidelines for the C programming language designed to promote **safety, security, portability, and reliability** in embedded systems.

**Current Version**: MISRA C:2012 (Amendment 1: 2016, Amendment 2: 2020, Amendment 3: 2024)

**Key Principles**:
- **Type safety**: Prevent type confusion and implicit conversions
- **Memory safety**: Prevent buffer overflows, memory leaks, dangling pointers
- **Control flow safety**: Prevent unreachable code, infinite loops, undefined behavior
- **Predictability**: Ensure deterministic, analyzable behavior

### 1.2 EN 50128 Requirements for MISRA C

**Table A.12: Design and Coding Standards**

| SIL Level | Requirement | Rationale |
|-----------|-------------|-----------|
| **SIL 0** | Recommended (R) | Improves code quality |
| **SIL 1** | Highly Recommended (HR) | Reduces coding errors |
| **SIL 2** | Highly Recommended (HR) | Strongly advised for safety-critical code |
| **SIL 3** | **MANDATORY (M)** | Essential for safety integrity |
| **SIL 4** | **MANDATORY (M)** | Critical for highest safety level |

**EN 50128 Section 7.4.4.3**: "A coding standard shall be defined and applied. For SIL 3 and SIL 4, the coding standard shall be based on a recognized standard such as MISRA C."

### 1.3 Design Phase vs. Implementation Phase

**Design Phase Decisions** (this document):
- ✅ **Type system**: Which types to use (fixed-width vs. native)?
- ✅ **Memory management**: Static vs. dynamic allocation?
- ✅ **Control flow**: Structured programming? Recursion allowed?
- ✅ **Error handling**: Return codes vs. exceptions? How to propagate errors?
- ✅ **Function design**: Parameter passing? Return value conventions?
- ✅ **Data structures**: How to organize data? Alignment? Padding?

**Implementation Phase** (coding):
- Applying MISRA C rules to code (checked by static analyzer)
- Enforcing design decisions in implementation
- Documenting deviations

**Key Insight**: Many MISRA C violations can be **prevented by design**. If the architecture/design violates MISRA C principles, implementation will be difficult and error-prone.

### 1.4 MISRA C Rule Categories

**Directives** (D): High-level process requirements (not always checkable by tools)
- Example: Directive 4.1 "Run-time failures shall be minimized"

**Rules** (R): Specific technical requirements (checkable by tools)
- Example: Rule 8.7 "Functions and objects should not be defined with external linkage if referenced in only one translation unit"

**Rule Classifications**:
- **Mandatory**: Must be followed (deviation requires formal justification)
- **Required**: Must be followed (deviation may be acceptable with justification)
- **Advisory**: Recommended (deviations allowed)

**SIL-Dependent Compliance**:
- **SIL 3-4**: Zero mandatory rule violations (checked by static analyzer)
- **SIL 2**: Zero mandatory violations highly recommended
- **SIL 0-1**: Follow advisory rules as much as possible

---

## 2. Type System Design

### 2.1 Fixed-Width Integer Types (MANDATORY)

**MISRA C Recommendation**: Use fixed-width types from `<stdint.h>` for all integer variables.

**Design Decision**: **Always use fixed-width types** (uint8_t, uint16_t, uint32_t, etc.) instead of native types (char, short, int, long).

**Rationale**:
- **Portability**: Native types have implementation-defined sizes (int may be 16 or 32 bits)
- **Predictability**: Fixed-width types have known sizes across platforms
- **Safety**: Prevents integer overflow/underflow due to unexpected type sizes

**Design Phase Action**:
```c
// BAD: Native types (implementation-defined sizes)
int speed;              // 16 or 32 bits?
unsigned int counter;   // 16 or 32 bits?
char buffer[100];       // signed or unsigned?

// GOOD: Fixed-width types (defined sizes)
int32_t speed;          // Always 32 bits
uint32_t counter;       // Always 32 bits (unsigned)
uint8_t buffer[100];    // Always 8 bits per element (unsigned)
```

**Architecture Specification (DOC-9)**: Document type conventions.
```markdown
## Type Conventions

All integer types SHALL use fixed-width types from <stdint.h>:
- int8_t, uint8_t (8-bit signed/unsigned)
- int16_t, uint16_t (16-bit signed/unsigned)
- int32_t, uint32_t (32-bit signed/unsigned)
- int64_t, uint64_t (64-bit signed/unsigned, if supported)

Native types (int, long, char) SHALL NOT be used except:
- Function return types (error_t, which is typedef'd to int32_t)
- Loop counters (size_t for array indices)
```

### 2.2 Boolean Type

**MISRA C Recommendation**: Use `<stdbool.h>` for boolean values.

**Design Decision**: Use `bool` type for all boolean variables.

```c
// BAD: Integer as boolean
int is_valid;           // 0 = false, 1 = true? What about 2?

// GOOD: Boolean type
bool is_valid;          // true or false (explicit)
```

**Exception (C89/C90)**: If using C89 (pre-C99), define a bool type:
```c
// For C89 compatibility
typedef enum {
    false = 0,
    true = 1
} bool;
```

### 2.3 Enumerated Types

**MISRA C Rule 10.4**: "The value of a complex expression of integer type may only be cast to a narrower integer type if the value is within the range of the target type."

**Design Decision**: Use enums for symbolic constants and state machines.

```c
// GOOD: Enum for states
typedef enum {
    STATE_IDLE = 0,
    STATE_RUNNING = 1,
    STATE_STOPPED = 2,
    STATE_ERROR = 3
} system_state_t;

system_state_t current_state = STATE_IDLE;

// GOOD: Enum for error codes
typedef enum {
    ERROR_NONE = 0,
    ERROR_NULL_POINTER = 1,
    ERROR_OUT_OF_RANGE = 2,
    ERROR_TIMEOUT = 3
} error_code_t;
```

**Guideline**: Always specify underlying type (C23) or ensure enum values fit in int.

```c
// C23: Explicit underlying type
typedef enum : uint8_t {
    STATE_IDLE = 0,
    STATE_RUNNING = 1,
    STATE_STOPPED = 2
} system_state_t;
```

### 2.4 Type Conversions and Casts

**MISRA C Rules 10.1-10.8**: Restrict implicit conversions and casts.

**Design Decision**: Minimize type conversions. Design interfaces to use consistent types.

```c
// BAD: Mixed types requiring conversions
uint16_t sensor_value;
int32_t control_output;

void control_update(uint16_t input, int32_t* output) {
    *output = (int32_t)input * 2;  // Explicit cast required
}

// GOOD: Consistent types
int32_t sensor_value;
int32_t control_output;

void control_update(int32_t input, int32_t* output) {
    *output = input * 2;  // No cast required
}
```

**Design Guideline**: Document expected ranges for all types.
```c
// Design Specification (DOC-10)
// Function: sensor_read
// Input: None
// Output: sensor_value (uint16_t, range: 0-4095, representing ADC counts)
// Errors: ERROR_TIMEOUT if sensor not responding
```

### 2.5 Floating-Point Types

**MISRA C Directive 1.1**: "Any implementation-defined behavior shall be documented."

**Design Decision**: Avoid floating-point if possible (SIL 3-4). If required, use fixed-point arithmetic or document floating-point behavior.

**Rationale**:
- Floating-point operations may have non-deterministic execution time
- Floating-point behavior is implementation-defined (IEEE 754 not guaranteed)
- Floating-point is difficult to test exhaustively

```c
// BAD: Floating-point for control (non-deterministic)
float control_gain = 1.5f;
float output = input * control_gain;

// GOOD: Fixed-point arithmetic (deterministic)
int32_t control_gain = 150;  // Represents 1.50 (scaled by 100)
int32_t output = (input * control_gain) / 100;
```

**If Floating-Point Required** (e.g., for non-safety-critical calculations):
- Document rounding mode
- Document exception handling (overflow, underflow, NaN, infinity)
- Use double (not float) for better precision
- Validate results for reasonableness (e.g., check for NaN/infinity)

---

## 3. Memory Management Design

### 3.1 Static vs. Dynamic Allocation

**MISRA C Rule 21.3**: "The memory allocation and deallocation functions of <stdlib.h> shall not be used."

**Design Decision**: **Static allocation ONLY** for SIL 2+ (no malloc/calloc/realloc/free).

**Rationale**:
- Dynamic allocation is non-deterministic (allocation time varies)
- Memory leaks risk (forgot to free)
- Memory fragmentation (allocation may fail unpredictably)
- Dangling pointers (use after free)

**Design Phase Action**: Document memory allocation strategy in Software Architecture Specification (DOC-9).

```markdown
## Memory Allocation Strategy

All memory SHALL be allocated statically at compile time (SIL 2+):
- Global/static variables for persistent state
- Stack variables for temporary state
- No dynamic allocation (malloc/calloc/realloc/free forbidden)

Maximum stack usage: 4096 bytes per task
Maximum static memory: 64 KB
```

### 3.2 Static Allocation Patterns

**Pattern 1: Static Arrays** (simplest)
```c
// Design: Fixed-size sensor array
#define MAX_SENSORS 10

static sensor_t sensors[MAX_SENSORS];  // Static array
static uint8_t sensor_count = 0;

error_t sensor_allocate(sensor_t** sensor) {
    if (sensor_count >= MAX_SENSORS) return ERROR_OUT_OF_RESOURCES;
    
    *sensor = &sensors[sensor_count];
    sensor_count++;
    
    return SUCCESS;
}
```

**Pattern 2: Static Pool Allocator** (more flexible)
```c
// Design: Memory pool for control blocks
#define MAX_CONTROL_BLOCKS 20

typedef struct {
    control_block_t blocks[MAX_CONTROL_BLOCKS];
    bool allocated[MAX_CONTROL_BLOCKS];
} control_pool_t;

static control_pool_t pool;

error_t control_allocate(control_block_t** block) {
    for (uint8_t i = 0; i < MAX_CONTROL_BLOCKS; i++) {
        if (!pool.allocated[i]) {
            pool.allocated[i] = true;
            *block = &pool.blocks[i];
            return SUCCESS;
        }
    }
    return ERROR_OUT_OF_RESOURCES;
}

void control_deallocate(control_block_t* block) {
    for (uint8_t i = 0; i < MAX_CONTROL_BLOCKS; i++) {
        if (&pool.blocks[i] == block) {
            pool.allocated[i] = false;
            return;
        }
    }
}
```

**Pattern 3: Compile-Time Sized Buffers**
```c
// Design: Fixed-size message queue
#define MESSAGE_QUEUE_SIZE 32
#define MESSAGE_MAX_LENGTH 64

typedef struct {
    uint8_t data[MESSAGE_MAX_LENGTH];
    uint8_t length;
} message_t;

typedef struct {
    message_t messages[MESSAGE_QUEUE_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t count;
} message_queue_t;

static message_queue_t queue;
```

### 3.3 Stack vs. Heap

**MISRA C Directive 4.12**: "Dynamic memory allocation shall not be used."

**Design Decision**: Use stack for temporary variables, static for persistent state.

**Stack Guidelines**:
- Small temporary variables (< 100 bytes)
- Function parameters and return values
- Loop counters

**Static Guidelines**:
- Module state (persistent across function calls)
- Large buffers (> 100 bytes)
- Arrays and structs

**Example**:
```c
// Stack: Temporary calculation
error_t calculate_speed(int32_t* speed) {
    int32_t temp1, temp2;  // Stack (temporary)
    temp1 = sensor_read();
    temp2 = temp1 * SCALE_FACTOR;
    *speed = temp2 / DIVISOR;
    return SUCCESS;
}

// Static: Persistent state
static uint16_t sensor_history[100];  // Static (persistent)
static uint8_t history_index = 0;
```

### 3.4 Memory Limits Documentation

**Design Phase**: Document memory limits in Software Architecture Specification (DOC-9).

```markdown
## Memory Budget

| Module | Static Memory (bytes) | Stack Usage (bytes) |
|--------|-----------------------|---------------------|
| Sensor Manager | 2048 | 256 |
| Control Logic | 1024 | 512 |
| Actuator Driver | 512 | 128 |
| Communication | 4096 | 1024 |
| Total | 7680 | 1920 |

Maximum allowed:
- Total static memory: 64 KB
- Maximum stack per task: 4096 bytes
```

---

## 4. Control Flow Design

### 4.1 No Recursion (Highly Recommended SIL 3-4)

**MISRA C Rule 17.2**: "Functions shall not call themselves, either directly or indirectly."

**Design Decision**: **No recursion** (SIL 3-4 mandatory, SIL 2 highly recommended).

**Rationale**:
- Recursion uses unbounded stack space (risk of stack overflow)
- Difficult to determine worst-case execution time (WCET)
- Difficult to verify correctness

**Design Phase Action**: Identify recursive algorithms and redesign iteratively.

**Example: Recursive to Iterative**
```c
// BAD: Recursive (unbounded stack)
uint32_t factorial_recursive(uint32_t n) {
    if (n <= 1) return 1;
    return n * factorial_recursive(n - 1);  // Recursion forbidden
}

// GOOD: Iterative (bounded stack)
uint32_t factorial_iterative(uint32_t n) {
    uint32_t result = 1;
    for (uint32_t i = 2; i <= n; i++) {  // Fixed iterations
        result *= i;
    }
    return result;
}
```

**Example: Tree Traversal (Recursive → Iterative)**
```c
// BAD: Recursive tree traversal
void tree_traverse_recursive(tree_node_t* node) {
    if (node == NULL) return;
    process(node);
    tree_traverse_recursive(node->left);   // Recursion
    tree_traverse_recursive(node->right);  // Recursion
}

// GOOD: Iterative tree traversal (explicit stack)
#define MAX_TREE_DEPTH 32

void tree_traverse_iterative(tree_node_t* root) {
    tree_node_t* stack[MAX_TREE_DEPTH];
    uint8_t stack_top = 0;
    
    if (root == NULL) return;
    
    stack[stack_top++] = root;
    
    while (stack_top > 0) {
        tree_node_t* node = stack[--stack_top];
        process(node);
        
        if (node->right != NULL && stack_top < MAX_TREE_DEPTH) {
            stack[stack_top++] = node->right;
        }
        if (node->left != NULL && stack_top < MAX_TREE_DEPTH) {
            stack[stack_top++] = node->left;
        }
    }
}
```

### 4.2 Bounded Loops (MANDATORY SIL 3-4)

**MISRA C Directive 4.1**: "Run-time failures shall be minimized."

**Design Decision**: All loops must have **bounded iteration counts** (SIL 3-4).

**Rationale**:
- Infinite loops risk system hang
- Unbounded loops make WCET analysis impossible

**Design Pattern**: Use counter with maximum limit.

```c
// BAD: Unbounded loop (may run forever)
while (sensor_read() != EXPECTED_VALUE) {
    // Wait indefinitely (may hang)
}

// GOOD: Bounded loop with timeout
#define MAX_RETRIES 1000

uint16_t retries = 0;
while (sensor_read() != EXPECTED_VALUE && retries < MAX_RETRIES) {
    retries++;
    delay_ms(10);
}

if (retries >= MAX_RETRIES) {
    return ERROR_TIMEOUT;  // Handle timeout
}
```

**Design Guideline**: Document maximum iteration counts in design specification.

```c
// Design Specification (DOC-10)
// Function: wait_for_sensor_ready
// Description: Waits for sensor to become ready (bounded wait)
// Maximum Iterations: 1000 (= 10 seconds with 10ms delay per iteration)
// WCET: 10.5 seconds (including timeout handling)
```

### 4.3 Structured Programming (MANDATORY)

**MISRA C Rule 15.1**: "The goto statement shall not be used."

**Design Decision**: Use structured control flow (if/else, while, for, switch). **No goto** (with very rare exceptions for error handling).

**Rationale**:
- Structured code is easier to understand and verify
- goto creates spaghetti code (difficult control flow)

```c
// BAD: Using goto
error_t process_data(void) {
    if (init() != SUCCESS) goto error;
    if (read_data() != SUCCESS) goto error;
    if (validate_data() != SUCCESS) goto error;
    if (write_result() != SUCCESS) goto error;
    
    return SUCCESS;
    
error:
    cleanup();
    return ERROR;
}

// GOOD: Structured error handling
error_t process_data(void) {
    error_t err;
    
    err = init();
    if (err != SUCCESS) {
        cleanup();
        return err;
    }
    
    err = read_data();
    if (err != SUCCESS) {
        cleanup();
        return err;
    }
    
    err = validate_data();
    if (err != SUCCESS) {
        cleanup();
        return err;
    }
    
    err = write_result();
    if (err != SUCCESS) {
        cleanup();
        return err;
    }
    
    return SUCCESS;
}
```

**Exception**: goto may be acceptable for single-level error cleanup (MISRA C permits with deviation):
```c
// Acceptable: Single-level cleanup with goto (document deviation)
error_t complex_function(void) {
    resource_t* res1 = NULL;
    resource_t* res2 = NULL;
    error_t err = SUCCESS;
    
    res1 = acquire_resource1();
    if (res1 == NULL) {
        err = ERROR_RESOURCE1;
        goto cleanup;
    }
    
    res2 = acquire_resource2();
    if (res2 == NULL) {
        err = ERROR_RESOURCE2;
        goto cleanup;
    }
    
    err = process(res1, res2);
    
cleanup:
    if (res2 != NULL) release_resource2(res2);
    if (res1 != NULL) release_resource1(res1);
    
    return err;
}
```

### 4.4 Switch Statements

**MISRA C Rule 16.1**: "All switch statements shall be well-formed."
**MISRA C Rule 16.3**: "An unconditional break statement shall terminate every switch-clause."
**MISRA C Rule 16.4**: "Every switch statement shall have a default clause."

**Design Decision**: All switch statements must have default clause and explicit break.

```c
// GOOD: Well-formed switch
switch (state) {
    case STATE_IDLE:
        handle_idle();
        break;  // Explicit break
    
    case STATE_RUNNING:
        handle_running();
        break;  // Explicit break
    
    case STATE_STOPPED:
        handle_stopped();
        break;  // Explicit break
    
    default:
        // Handle unexpected state (defensive programming)
        handle_error(ERROR_INVALID_STATE);
        break;
}
```

---

## 5. Error Handling Design

### 5.1 Return Codes vs. Exceptions

**MISRA C**: C has no native exceptions. Use return codes.

**Design Decision**: All functions that can fail SHALL return error_t (error code).

**Rationale**:
- Explicit error handling (caller must check return value)
- No hidden control flow (unlike exceptions)
- Predictable performance (no exception unwinding)

**Design Pattern**:
```c
// error_codes.h
typedef enum {
    SUCCESS = 0,
    ERROR_NULL_POINTER = 1,
    ERROR_OUT_OF_RANGE = 2,
    ERROR_TIMEOUT = 3,
    ERROR_CRC_MISMATCH = 4,
    // ... more error codes
} error_t;

// All fallible functions return error_t
error_t sensor_read(sensor_t* sensor, uint16_t* value);
error_t control_update(int32_t input, int32_t* output);
error_t actuator_set(uint8_t value);
```

### 5.2 Output Parameters

**MISRA C Rule 17.8**: "A function parameter should not be modified."

**Design Decision**: Use output parameters (pointers) for function results. Return error code.

```c
// GOOD: Error code returned, result via output parameter
error_t sensor_read(sensor_t* sensor, uint16_t* value) {
    if (sensor == NULL || value == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    *value = adc_read(sensor->channel);
    return SUCCESS;
}

// Caller
uint16_t sensor_value;
error_t err = sensor_read(&sensor, &sensor_value);
if (err != SUCCESS) {
    handle_error(err);
}
```

### 5.3 Defensive Parameter Validation

**MISRA C Directive 4.14**: "The validity of values received from external sources shall be checked."

**Design Decision**: Validate ALL function inputs (defensive programming).

```c
error_t control_update(const sensor_data_t* input, control_output_t* output) {
    // Validate pointers (MANDATORY)
    if (input == NULL) return ERROR_NULL_POINTER;
    if (output == NULL) return ERROR_NULL_POINTER;
    
    // Validate ranges (MANDATORY)
    if (input->speed < MIN_SPEED || input->speed > MAX_SPEED) {
        return ERROR_OUT_OF_RANGE;
    }
    
    // Function body
    output->value = calculate_control(input->speed);
    
    return SUCCESS;
}
```

### 5.4 Error Propagation

**Design Decision**: Errors SHALL be propagated up the call stack (caller checks return value).

```c
// GOOD: Error propagation
error_t high_level_function(void) {
    error_t err;
    
    err = mid_level_function();
    if (err != SUCCESS) {
        log_error("mid_level_function failed", err);
        return err;  // Propagate error
    }
    
    return SUCCESS;
}

error_t mid_level_function(void) {
    error_t err;
    
    err = low_level_function();
    if (err != SUCCESS) {
        return err;  // Propagate error
    }
    
    return SUCCESS;
}
```

**Anti-Pattern: Ignoring Errors** (FORBIDDEN)
```c
// BAD: Ignoring error return value
sensor_read(&sensor, &value);  // Error not checked!
control_update(value, &output);  // May fail silently
```

**MISRA C Rule 17.7**: "The value returned by a function having non-void return type shall be used."

**Design Enforcement**: Use `(void)` cast if intentionally ignoring return value (rare).
```c
// Explicitly ignore return value (document why)
(void)printf("Debug: value = %d\n", value);  // printf failure is non-critical
```

---

## 6. Function Design

### 6.1 Function Parameters

**MISRA C Rule 8.13**: "A pointer should point to a const-qualified type whenever possible."

**Design Decision**: Use `const` for read-only parameters.

```c
// GOOD: const for read-only parameters
error_t process_data(const sensor_data_t* input, result_data_t* output) {
//                    ^^^^^                       (read-only)
    if (input == NULL || output == NULL) return ERROR_NULL_POINTER;
    
    output->value = input->raw_value * SCALE_FACTOR;  // Read input
    // input->raw_value = 0;  // Compile error (const)
    
    return SUCCESS;
}
```

**Design Guideline**: Document parameter direction (in, out, in/out).

```c
// Design Specification (DOC-10)
// Function: control_update
// Parameters:
//   - input (const sensor_data_t*) [IN]: Sensor data (read-only)
//   - output (control_output_t*) [OUT]: Control output (write-only)
// Returns: error_t (SUCCESS or error code)
```

### 6.2 Function Return Values

**MISRA C Rule 17.7**: "The value returned by a function having non-void return type shall be used."

**Design Decision**: Functions that always succeed return void. Functions that can fail return error_t.

```c
// Always succeeds → void return
void led_set(bool state) {
    gpio_write(LED_PIN, state);  // Cannot fail
}

// Can fail → error_t return
error_t sensor_read(sensor_t* sensor, uint16_t* value) {
    if (sensor == NULL || value == NULL) return ERROR_NULL_POINTER;
    
    *value = adc_read(sensor->channel);
    if (*value > MAX_ADC_VALUE) return ERROR_OUT_OF_RANGE;
    
    return SUCCESS;
}
```

### 6.3 Function Complexity

**MISRA C Directive 4.1**: "Run-time failures shall be minimized."

**Design Decision**: Cyclomatic complexity ≤ 10 (SIL 3-4), ≤ 15 (SIL 2).

**Design Phase**: Decompose complex functions into smaller helpers (see `complexity-guidelines.md`).

```c
// BAD: Complex function (CCN > 10)
error_t process_sensor_data(sensor_t* sensor, result_t* result) {
    // 20 if statements, 3 loops, 2 switch statements → CCN = 25
}

// GOOD: Decomposed into smaller functions
static error_t validate_sensor(const sensor_t* sensor);  // CCN = 3
static error_t read_sensor(sensor_t* sensor, uint16_t* raw);  // CCN = 2
static error_t filter_sensor_data(uint16_t raw, uint16_t* filtered);  // CCN = 4
static error_t calculate_result(uint16_t filtered, result_t* result);  // CCN = 3

error_t process_sensor_data(sensor_t* sensor, result_t* result) {  // CCN = 5
    error_t err;
    
    err = validate_sensor(sensor);
    if (err != SUCCESS) return err;
    
    uint16_t raw, filtered;
    
    err = read_sensor(sensor, &raw);
    if (err != SUCCESS) return err;
    
    err = filter_sensor_data(raw, &filtered);
    if (err != SUCCESS) return err;
    
    err = calculate_result(filtered, result);
    if (err != SUCCESS) return err;
    
    return SUCCESS;
}
```

### 6.4 Function Side Effects

**MISRA C Directive 4.1**: "Run-time failures shall be minimized."

**Design Decision**: Minimize side effects. Document all side effects in design specification.

**Side Effect**: Function modifies state outside its scope (global variables, I/O, etc.).

```c
// BAD: Hidden side effect (global variable)
static uint32_t call_count;  // Global state

uint16_t sensor_read(void) {
    call_count++;  // Hidden side effect (modifies global)
    return adc_read(SENSOR_CHANNEL);
}

// GOOD: Explicit side effect (documented)
static uint32_t call_count;  // Global state

// Design Specification:
// Side effects: Increments global call_count (for diagnostics)
uint16_t sensor_read(void) {
    call_count++;  // Documented side effect
    return adc_read(SENSOR_CHANNEL);
}

// BETTER: No side effects (caller manages statistics)
uint16_t sensor_read(sensor_t* sensor) {
    sensor->call_count++;  // Caller-visible state
    return adc_read(sensor->channel);
}
```

---

## 7. Data Structure Design

### 7.1 Struct Alignment and Padding

**MISRA C Directive 1.1**: "Any implementation-defined behavior shall be documented."

**Design Decision**: Document struct layout (alignment, padding) if size-critical.

**Rationale**: Compilers insert padding for alignment (implementation-defined).

```c
// Example: Padding inserted by compiler
typedef struct {
    uint8_t a;   // 1 byte
    // 3 bytes padding (align b to 4-byte boundary)
    uint32_t b;  // 4 bytes
    uint8_t c;   // 1 byte
    // 3 bytes padding (align struct size to 4-byte boundary)
} poorly_aligned_t;  // Total: 12 bytes (not 6!)

// Better: Reorder fields to minimize padding
typedef struct {
    uint32_t b;  // 4 bytes (largest first)
    uint8_t a;   // 1 byte
    uint8_t c;   // 1 byte
    // 2 bytes padding
} better_aligned_t;  // Total: 8 bytes (not 12)
```

**Design Guideline**: Order struct fields from largest to smallest type.

**For Size-Critical Structs**: Use `__attribute__((packed))` (GCC) or `#pragma pack` (MSVC) with deviation.
```c
// Deviation required: Packed struct (non-portable)
typedef struct __attribute__((packed)) {
    uint8_t a;   // 1 byte
    uint32_t b;  // 4 bytes (no padding)
    uint8_t c;   // 1 byte
} packed_t;  // Total: 6 bytes (exactly)

// Document deviation: "Packed attribute used to match hardware register layout"
```

### 7.2 Bit Fields

**MISRA C Directive 1.1**: "Any implementation-defined behavior shall be documented."
**MISRA C Rule 6.1**: "Bit-fields shall only be declared with an appropriate type."

**Design Decision**: Avoid bit fields if possible (implementation-defined). If required, use unsigned types and document layout.

```c
// BAD: Bit field with signed type
typedef struct {
    int flag1 : 1;  // Signed bit field (MISRA C violation)
    int flag2 : 1;
} bad_bitfield_t;

// GOOD: Bit field with unsigned type
typedef struct {
    uint8_t flag1 : 1;  // Unsigned bit field
    uint8_t flag2 : 1;
    uint8_t flag3 : 1;
    uint8_t reserved : 5;
} good_bitfield_t;

// Document layout:
// bit 0: flag1
// bit 1: flag2
// bit 2: flag3
// bits 3-7: reserved (must be 0)
```

**Alternative: Explicit Bit Manipulation** (more portable)
```c
// More portable: Explicit bit masks
#define FLAG1_MASK 0x01
#define FLAG2_MASK 0x02
#define FLAG3_MASK 0x04

typedef struct {
    uint8_t flags;  // Bit 0 = flag1, bit 1 = flag2, bit 2 = flag3
} explicit_flags_t;

// Accessors
bool get_flag1(const explicit_flags_t* f) {
    return (f->flags & FLAG1_MASK) != 0;
}

void set_flag1(explicit_flags_t* f, bool value) {
    if (value) {
        f->flags |= FLAG1_MASK;
    } else {
        f->flags &= ~FLAG1_MASK;
    }
}
```

### 7.3 Unions

**MISRA C Rule 19.2**: "The union keyword should not be used."

**Design Decision**: Avoid unions if possible (type confusion risk). If required, use tagged unions.

**Rationale**: Unions allow type punning (reading data as different type), which is error-prone.

```c
// BAD: Untagged union (type confusion risk)
typedef union {
    uint32_t as_uint32;
    float as_float;
} untagged_union_t;

untagged_union_t u;
u.as_float = 3.14f;
uint32_t bits = u.as_uint32;  // Type punning (dangerous)

// GOOD: Tagged union (explicit type tracking)
typedef enum {
    DATA_TYPE_INT,
    DATA_TYPE_FLOAT
} data_type_t;

typedef struct {
    data_type_t type;  // Tag (identifies active member)
    union {
        int32_t as_int;
        float as_float;
    } data;
} tagged_union_t;

// Accessor (checks tag)
error_t get_int(const tagged_union_t* tu, int32_t* value) {
    if (tu->type != DATA_TYPE_INT) return ERROR_TYPE_MISMATCH;
    *value = tu->data.as_int;
    return SUCCESS;
}
```

### 7.4 Array Design

**MISRA C Rule 18.1**: "A pointer resulting from arithmetic on a pointer operand shall address an element of the same array."

**Design Decision**: Always pass array size with array pointer.

```c
// BAD: Array without size (buffer overflow risk)
void process_array(uint8_t* array) {
    for (uint8_t i = 0; i < 100; i++) {  // Hardcoded size (wrong if array < 100)
        array[i] = 0;
    }
}

// GOOD: Array with size parameter
void process_array(uint8_t* array, size_t array_size) {
    if (array == NULL) return;
    
    for (size_t i = 0; i < array_size; i++) {
        array[i] = 0;
    }
}

// Better: Use compile-time array size
#define ARRAY_SIZE 100

void process_array(uint8_t array[ARRAY_SIZE]) {
    for (uint8_t i = 0; i < ARRAY_SIZE; i++) {
        array[i] = 0;
    }
}

// Best: Pass array by reference with size
void process_array_safe(uint8_t (*array)[100]) {
    for (uint8_t i = 0; i < 100; i++) {
        (*array)[i] = 0;
    }
}
```

---

## 8. Interface Design

### 8.1 Header File Design

**MISRA C Directive 4.10**: "Precautions shall be taken in order to prevent the contents of a header file being included more than once."

**Design Decision**: All header files SHALL have include guards.

```c
// module.h
#ifndef MODULE_H
#define MODULE_H

// Header contents

#endif /* MODULE_H */
```

**Alternative (C23)**: Use `#pragma once` (not MISRA C compliant, requires deviation).

### 8.2 Minimal Interface Exposure

**MISRA C Rule 8.7**: "Functions and objects should not be defined with external linkage if they are referenced in only one translation unit."

**Design Decision**: Expose only necessary functions in header. Keep helpers static.

```c
// module.h (Public interface - minimal)
error_t module_init(module_t* module);
error_t module_process(module_t* module, uint16_t input, uint16_t* output);

// module.c (Implementation)
static error_t validate_input(uint16_t input);  // Internal (static)
static error_t apply_filter(uint16_t input, uint16_t* output);  // Internal

error_t module_init(module_t* module) {
    // Public function
}

error_t module_process(module_t* module, uint16_t input, uint16_t* output) {
    error_t err = validate_input(input);
    if (err != SUCCESS) return err;
    
    return apply_filter(input, output);
}

static error_t validate_input(uint16_t input) {
    // Internal helper (not in header)
}

static error_t apply_filter(uint16_t input, uint16_t* output) {
    // Internal helper (not in header)
}
```

### 8.3 Const Correctness in Interfaces

**MISRA C Rule 8.13**: "A pointer should point to a const-qualified type whenever possible."

**Design Decision**: All read-only interface parameters SHALL be const.

```c
// GOOD: Const correctness
error_t calculate(const input_t* input, output_t* output);
//                ^^^^^                  (read-only)

bool is_valid(const sensor_data_t* data);
//            ^^^^^                       (read-only)

void log_message(const char* message);
//               ^^^^^                   (read-only)
```

---

## 9. Concurrency Design

### 9.1 Shared Data Protection

**MISRA C Directive 4.11**: "Automatic allocation shall not be used with recursive function calls or in functions used in multi-threaded environments without adequate protection."

**Design Decision**: Document all shared data. Protect with mutexes or disable interrupts.

```c
// Design: Shared data (accessed by ISR and main loop)
static volatile uint16_t sensor_value;  // volatile = may change unexpectedly

// ISR: Write sensor_value
void sensor_isr(void) {
    sensor_value = adc_read(SENSOR_CHANNEL);  // Write (atomic on 16-bit platform)
}

// Main loop: Read sensor_value
uint16_t get_sensor_value(void) {
    uint16_t value;
    
    // Critical section: Disable interrupts (platform-specific)
    __disable_irq();
    value = sensor_value;  // Read (atomic)
    __enable_irq();
    
    return value;
}
```

**Design Guideline**: Document critical sections in design specification.

```markdown
## Critical Sections

Function: get_sensor_value
Critical Section: Reading sensor_value (shared with ISR)
Protection: Disable interrupts (10 µs max)
```

### 9.2 Volatile Keyword

**MISRA C Rule 1.3**: "There shall be no undefined or critical unspecified behavior in the code."

**Design Decision**: Use `volatile` for hardware registers and ISR-shared data.

```c
// Hardware register (memory-mapped I/O)
#define GPIO_BASE 0x40020000
#define GPIO_IDR (*(volatile uint32_t*)(GPIO_BASE + 0x10))

uint32_t read_gpio(void) {
    return GPIO_IDR;  // volatile prevents compiler optimization
}

// ISR-shared data
static volatile bool data_ready;  // volatile = may change in ISR

void main_loop(void) {
    while (!data_ready) {  // volatile prevents optimization
        // Wait
    }
    process_data();
}

void isr(void) {
    data_ready = true;  // Set by ISR
}
```

---

## 10. MISRA C Deviations Process

### 10.1 When Deviations Are Acceptable

**MISRA C Guidelines**: Deviations are allowed if:
1. **Technical necessity**: No alternative exists
2. **Safety not compromised**: Deviation does not introduce hazards
3. **Documented**: Rationale and impact documented
4. **Reviewed**: Deviation reviewed and approved by QUA/VER
5. **Tracked**: All deviations tracked in Deviations Log

### 10.2 Deviation Documentation

**Design Phase**: Document anticipated deviations in Software Design Specification (DOC-10).

**Deviation Record**:
```markdown
## MISRA C Deviations

### Deviation 1: Packed Struct for Hardware Register

**Rule**: Directive 1.1 (Implementation-defined behavior)
**Location**: `sensor.h`, line 45, struct `sensor_register_t`
**Rationale**: Packed struct required to match hardware register layout (16-byte aligned, no padding)
**Impact**: Non-portable (GCC-specific `__attribute__((packed))`)
**Mitigation**: Platform-specific code isolated to HAL module. Tested on target hardware.
**Approval**: Approved by QUA (2026-03-13), VER (2026-03-14)

### Deviation 2: goto for Error Cleanup

**Rule**: Rule 15.1 (No goto statement)
**Location**: `control.c`, line 123, function `control_complex_operation`
**Rationale**: Single-level error cleanup (goto cleanup pattern) improves readability and reduces code duplication
**Impact**: Minimal (single goto to end of function)
**Mitigation**: Code review by QUA confirmed no control flow complexity
**Approval**: Approved by QUA (2026-03-15), VER (2026-03-16)
```

### 10.3 Deviations Tracking

**Tool**: Static analyzer (Cppcheck, PC-lint Plus) reports deviations.

**Process**:
1. Run static analyzer: `cppcheck --enable=all --addon=misra.json src/`
2. Review violations
3. Fix violations OR document deviation
4. Suppress false positives: `/* cppcheck-suppress misraRule16.3 */`
5. Update Deviations Log

**Example Suppression**:
```c
// Suppress false positive (document reason)
/* cppcheck-suppress misraRule16.3
 * Rationale: Intentional fallthrough with comment */
switch (state) {
    case STATE_A:
        handle_a();
        /* fallthrough */  // MISRA C allows with comment
    case STATE_B:
        handle_b();
        break;
}
```

---

## 11. Design Review Checklist

### 11.1 Type System Review

- [ ] All integer types use fixed-width types (`uint8_t`, `int32_t`, etc.)
- [ ] Boolean values use `bool` type (from `<stdbool.h>`)
- [ ] Enums used for symbolic constants (states, error codes)
- [ ] Type conversions minimized (consistent types across interfaces)
- [ ] Floating-point avoided (or documented if required)

### 11.2 Memory Management Review

- [ ] Static allocation only (SIL 2+) - no `malloc/calloc/realloc/free`
- [ ] Memory budget documented (static + stack limits)
- [ ] Large buffers allocated statically (not on stack)
- [ ] No unbounded memory usage (all arrays fixed-size)

### 11.3 Control Flow Review

- [ ] No recursion (SIL 3-4 mandatory)
- [ ] All loops bounded (maximum iterations documented)
- [ ] Structured programming (no `goto` except single-level error cleanup with deviation)
- [ ] All switch statements have `default` clause and explicit `break`

### 11.4 Error Handling Review

- [ ] All fallible functions return `error_t`
- [ ] Output parameters used for results (pointers)
- [ ] All function inputs validated (NULL checks, range checks)
- [ ] Errors propagated up call stack (callers check return values)

### 11.5 Function Design Review

- [ ] Read-only parameters marked `const`
- [ ] Functions documented (parameters [IN/OUT/INOUT], return value, side effects)
- [ ] Function complexity ≤ 10 (SIL 3-4), ≤ 15 (SIL 2)
- [ ] Functions that always succeed return `void`, fallible functions return `error_t`

### 11.6 Data Structure Review

- [ ] Struct fields ordered largest-to-smallest (minimize padding)
- [ ] Bit fields avoided (or unsigned types used with documentation)
- [ ] Unions avoided (or tagged unions used)
- [ ] Arrays passed with size parameter

### 11.7 Interface Design Review

- [ ] All headers have include guards
- [ ] Minimal interface exposure (only necessary functions public)
- [ ] Read-only parameters marked `const`
- [ ] All public functions documented in header

### 11.8 Concurrency Review

- [ ] Shared data documented (ISR-shared, multi-threaded)
- [ ] Critical sections protected (mutexes, disable interrupts)
- [ ] `volatile` used for hardware registers and ISR-shared data

### 11.9 Deviations Review

- [ ] All MISRA C deviations documented (rule, location, rationale, approval)
- [ ] Deviations tracked in Deviations Log
- [ ] Static analyzer suppressions documented

---

## 12. References

### 12.1 MISRA C:2012 Standard

- **MISRA C:2012**: "Guidelines for the use of the C language in critical systems" (March 2013)
- **Amendment 1** (2016): Coverage of C99
- **Amendment 2** (2020): Coverage of C11
- **Amendment 3** (2024): Coverage of C17/C18

### 12.2 EN 50128 References

- **Section 7.4.4.3**: Coding standards (MISRA C mandatory SIL 3-4)
- **Table A.12**: Design and Coding Standards techniques
- **Annex D.10**: Coding Standards definition

### 12.3 Related Workflow Documents

- `.opencode/skills/en50128-design/workflows/architecture-design.md` - Architecture design with MISRA C considerations
- `.opencode/skills/en50128-design/workflows/software-design.md` - Detailed design with MISRA C patterns
- `.opencode/skills/en50128-design/workflows/design-review.md` - MISRA C compliance review

### 12.4 Related Resource Documents

- `.opencode/skills/en50128-design/resources/defensive-programming-patterns.md` - MISRA C defensive patterns
- `.opencode/skills/en50128-design/resources/complexity-guidelines.md` - Cyclomatic complexity (MISRA C Directive 4.1)
- `.opencode/skills/en50128-design/resources/modularity-guidelines.md` - Module design (MISRA C Rule 8.7, 8.8)

### 12.5 Tool Documentation

- **Cppcheck**: Open-source static analyzer with MISRA C addon (https://cppcheck.sourceforge.io/)
- **PC-lint Plus**: Commercial static analyzer with comprehensive MISRA C checking (https://pclintplus.com/)
- **Clang Static Analyzer**: LLVM-based analyzer (https://clang-analyzer.llvm.org/)

---

**Document Control**:
- **Version**: 1.0
- **Date**: 2026-03-13
- **Author**: EN50128 Design Skill Enhancement (Phase 2)
- **Status**: Draft
- **Review Status**: Pending QUA review

---

**END OF DOCUMENT**
