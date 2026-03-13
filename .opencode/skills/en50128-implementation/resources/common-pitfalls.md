# Common Implementation Pitfalls and Fixes

**Document ID**: IMPL-RES-004  
**Version**: 1.0  
**Status**: Active  
**Part of**: EN 50128 Implementation Skill

---

## Table of Contents

1. [Introduction](#introduction)
2. [MISRA C Common Violations](#misra-c-common-violations)
3. [Defensive Programming Mistakes](#defensive-programming-mistakes)
4. [Unit Testing Anti-Patterns](#unit-testing-anti-patterns)
5. [Memory Management Pitfalls](#memory-management-pitfalls)
6. [Concurrency and Timing Issues](#concurrency-and-timing-issues)
7. [Integration and Interface Pitfalls](#integration-and-interface-pitfalls)
8. [Code Review Common Findings](#code-review-common-findings)
9. [Tool Usage Mistakes](#tool-usage-mistakes)

---

## 1. Introduction

This document catalogs the most common pitfalls encountered during EN 50128 safety-critical C implementation. Each pitfall includes:
- **Problem description** with WRONG code example
- **Root cause analysis**
- **Correct solution** with RIGHT code example
- **MISRA C rule reference** (where applicable)
- **EN 50128 reference**
- **SIL-specific guidance**
- **Detection strategy** (static analysis, code review, testing)

### Purpose

- **For Implementers (IMP)**: Avoid common mistakes during coding
- **For Code Reviewers (PEER, QUA)**: Focus on high-risk areas
- **For Verifiers (VER)**: Understand typical defect patterns
- **For Tool Users**: Configure tools to detect these issues

### Document Structure

This document is organized by pitfall category, with each section containing 5-10 specific pitfalls with complete before/after examples.

---

## 2. MISRA C Common Violations

### 2.1 Pitfall: Implicit Type Conversions (MISRA C Dir 4.6, Rule 10.1)

**Problem**: Using implementation-defined types instead of fixed-width types.

**Wrong Code**:
```c
// WRONG: Implicit conversions, non-portable types
int counter = 0;              // Size varies (16/32/64 bit)
unsigned long timeout = 1000; // Size varies (32/64 bit)
char buffer[256];             // char signedness varies

void updateCounter(void) {
    counter = timeout / 10;   // Implicit conversion long -> int
}
```

**Root Cause**:
- Implementation-defined integer sizes (int can be 16 or 32 bit)
- Implicit type conversions hide potential overflow/truncation
- Non-portable code breaks on different platforms

**Right Code**:
```c
// RIGHT: Fixed-width types, explicit conversions
#include <stdint.h>

static uint32_t counter = 0U;
static uint32_t timeout = 1000U;
static uint8_t buffer[256];

void updateCounter(void) {
    // Explicit conversion with range check
    uint32_t temp = timeout / 10U;
    if (temp <= UINT32_MAX) {
        counter = temp;  // Safe assignment
    }
}
```

**MISRA C Rules**:
- **Dir 4.6**: Use fixed-width types from `<stdint.h>` (Advisory)
- **Rule 10.1**: Operands shall not be of inappropriate essential type (Required)
- **Rule 10.3**: Value of expression shall not be assigned to narrower type (Required)

**EN 50128 Reference**: Table A.12 (Design and Coding Standards - Mandatory SIL 3-4)

**Detection**:
- **Cppcheck**: Enable `--enable=style` for type warnings
- **PC-lint Plus**: Enable message 9130 (bitwise/arithmetic type mismatch)
- **Code Review**: Check all type declarations for fixed-width types

**SIL Guidance**:
- **SIL 0-1**: Recommended
- **SIL 2+**: **MANDATORY** - All types must be fixed-width

---

### 2.2 Pitfall: Missing NULL Pointer Checks (MISRA C Rule 1.3)

**Problem**: Dereferencing pointers without validation.

**Wrong Code**:
```c
// WRONG: No NULL check before dereference
void processData(const uint8_t* data, uint16_t length) {
    uint16_t sum = 0U;
    for (uint16_t i = 0U; i < length; i++) {
        sum += data[i];  // CRASH if data == NULL
    }
    // Process sum...
}
```

**Root Cause**:
- Undefined behavior (C99 6.5.3.2) - dereferencing NULL pointer
- Can cause system crash or arbitrary code execution
- Violates defensive programming principle

**Right Code**:
```c
// RIGHT: Validate pointer before use
typedef enum {
    RESULT_SUCCESS = 0,
    RESULT_NULL_POINTER = 1,
    RESULT_INVALID_LENGTH = 2
} result_t;

result_t processData(const uint8_t* data, uint16_t length) {
    // Defensive checks
    if (data == NULL) {
        return RESULT_NULL_POINTER;  // Safe return
    }
    if (length == 0U) {
        return RESULT_INVALID_LENGTH;
    }
    
    uint16_t sum = 0U;
    for (uint16_t i = 0U; i < length; i++) {
        sum += data[i];  // Safe - data validated
    }
    // Process sum...
    return RESULT_SUCCESS;
}
```

**MISRA C Rules**:
- **Rule 1.3**: No undefined or critical unspecified behavior (Required)
- **Rule 21.18**: size_t parameter before pointer in string/memory functions (Mandatory)

**EN 50128 Reference**: 
- Table A.3 #1 (Defensive Programming - HR for SIL 1-4)
- Table A.4 #5 (Modular Approach - M for SIL 2+)

**Detection**:
- **Cppcheck**: `--enable=warning` detects possible NULL dereference
- **Clang**: `-Wpointer-arith -Wnull-dereference`
- **Code Review**: Check all functions accepting pointers

**SIL Guidance**:
- **SIL 0**: Recommended
- **SIL 1+**: **MANDATORY** - All pointer parameters must be validated

---

### 2.3 Pitfall: Array Index Out of Bounds (MISRA C Rule 18.1)

**Problem**: No bounds checking on array access.

**Wrong Code**:
```c
// WRONG: No bounds validation
#define MAX_SENSORS 10

static uint16_t sensorValues[MAX_SENSORS];

uint16_t getSensorValue(uint8_t sensorId) {
    return sensorValues[sensorId];  // DANGER: sensorId could be > 10
}

void updateSensor(uint8_t sensorId, uint16_t value) {
    sensorValues[sensorId] = value;  // Buffer overflow if sensorId >= 10
}
```

**Root Cause**:
- Undefined behavior (C99 6.5.6) - out-of-bounds access
- Can corrupt adjacent memory (stack/heap)
- Common source of security vulnerabilities (buffer overflow)

**Right Code**:
```c
// RIGHT: Explicit bounds checking
#define MAX_SENSORS 10

static uint16_t sensorValues[MAX_SENSORS];

typedef enum {
    SENSOR_SUCCESS = 0,
    SENSOR_INVALID_ID = 1
} sensor_result_t;

sensor_result_t getSensorValue(uint8_t sensorId, uint16_t* value) {
    // Validate index before access
    if (sensorId >= MAX_SENSORS) {
        return SENSOR_INVALID_ID;
    }
    if (value == NULL) {
        return SENSOR_INVALID_ID;
    }
    
    *value = sensorValues[sensorId];  // Safe - validated
    return SENSOR_SUCCESS;
}

sensor_result_t updateSensor(uint8_t sensorId, uint16_t value) {
    // Validate index before access
    if (sensorId >= MAX_SENSORS) {
        return SENSOR_INVALID_ID;
    }
    
    sensorValues[sensorId] = value;  // Safe - validated
    return SENSOR_SUCCESS;
}
```

**MISRA C Rules**:
- **Rule 18.1**: Pointer arithmetic shall not produce invalid pointer (Required)
- **Rule 18.6**: Address of object with automatic storage shall not be returned (Required)

**EN 50128 Reference**: Table A.3 #1 (Defensive Programming)

**Detection**:
- **Cppcheck**: `--enable=warning` detects array out of bounds
- **Clang**: `-Warray-bounds -Warray-bounds-pointer-arithmetic`
- **Runtime**: AddressSanitizer (`-fsanitize=address`)

**SIL Guidance**:
- **SIL 0-1**: Highly Recommended
- **SIL 2+**: **MANDATORY** - All array accesses must be bounds-checked

---

### 2.4 Pitfall: Uninitialized Variables (MISRA C Rule 9.1)

**Problem**: Using variables before initialization.

**Wrong Code**:
```c
// WRONG: Uninitialized local variable
uint32_t calculateChecksum(const uint8_t* data, uint16_t length) {
    uint32_t checksum;  // DANGER: Uninitialized
    
    if (data != NULL) {
        checksum = 0U;
        for (uint16_t i = 0U; i < length; i++) {
            checksum += data[i];
        }
    }
    
    return checksum;  // Returns garbage if data == NULL
}
```

**Root Cause**:
- Indeterminate value (C99 6.7.8) - reads undefined memory
- Non-deterministic behavior (different values each run)
- Hard to reproduce bugs

**Right Code**:
```c
// RIGHT: Initialize all variables at declaration
uint32_t calculateChecksum(const uint8_t* data, uint16_t length) {
    uint32_t checksum = 0U;  // SAFE: Initialized
    
    if (data != NULL) {
        for (uint16_t i = 0U; i < length; i++) {
            checksum += data[i];
        }
    }
    
    return checksum;  // Always returns valid value
}
```

**MISRA C Rules**:
- **Rule 9.1**: Value of object shall not be read if not initialized (Mandatory)
- **Rule 9.5**: Array with multiple initializers shall have explicit size (Required)

**EN 50128 Reference**: Table A.4 #6 (Analysable Programs - M for SIL 3-4)

**Detection**:
- **GCC**: `-Wuninitialized -Wmaybe-uninitialized`
- **Cppcheck**: `--enable=warning` detects uninitialized variables
- **Clang**: `-Wuninitialized -Wconditional-uninitialized`

**SIL Guidance**:
- **SIL 0-1**: Highly Recommended
- **SIL 2+**: **MANDATORY** - All variables must be initialized at declaration

---

### 2.5 Pitfall: Using goto (MISRA C Rule 15.1, 15.2)

**Problem**: Unstructured control flow with goto.

**Wrong Code**:
```c
// WRONG: goto creates spaghetti code
int processRequest(const uint8_t* request, uint16_t length) {
    if (request == NULL) goto error;
    if (length < MIN_LENGTH) goto error;
    
    uint8_t* buffer = allocateBuffer(length);
    if (buffer == NULL) goto error;
    
    if (!parseRequest(request, length, buffer)) goto cleanup;
    if (!validateRequest(buffer)) goto cleanup;
    
    processBuffer(buffer);
    
cleanup:
    freeBuffer(buffer);
    return 0;
    
error:
    logError("Request processing failed");
    return -1;
}
```

**Root Cause**:
- Violates structured programming (Dijkstra, 1968)
- Makes control flow hard to follow
- Prone to resource leaks (skipped cleanup)

**Right Code**:
```c
// RIGHT: Structured error handling
typedef enum {
    PROCESS_SUCCESS = 0,
    PROCESS_NULL_POINTER = 1,
    PROCESS_INVALID_LENGTH = 2,
    PROCESS_ALLOCATION_FAILED = 3,
    PROCESS_PARSE_FAILED = 4,
    PROCESS_VALIDATION_FAILED = 5
} process_result_t;

process_result_t processRequest(const uint8_t* request, uint16_t length) {
    process_result_t result = PROCESS_SUCCESS;
    
    // Validate inputs
    if (request == NULL) {
        return PROCESS_NULL_POINTER;
    }
    if (length < MIN_LENGTH) {
        return PROCESS_INVALID_LENGTH;
    }
    
    // Allocate buffer
    uint8_t* buffer = allocateBuffer(length);
    if (buffer == NULL) {
        return PROCESS_ALLOCATION_FAILED;
    }
    
    // Process with structured error handling
    if (!parseRequest(request, length, buffer)) {
        result = PROCESS_PARSE_FAILED;
    } else if (!validateRequest(buffer)) {
        result = PROCESS_VALIDATION_FAILED;
    } else {
        processBuffer(buffer);
    }
    
    // Always cleanup
    freeBuffer(buffer);
    
    return result;
}
```

**MISRA C Rules**:
- **Rule 15.1**: goto statement should not be used (Advisory)
- **Rule 15.2**: goto shall jump to later statement in same/enclosing block (Required)

**EN 50128 Reference**: Table A.4 #8 (Structured Programming - M for SIL 3-4)

**Detection**:
- **Cppcheck**: `--enable=style` warns on goto usage
- **PC-lint Plus**: Message 801 (goto discouraged)
- **Code Review**: Reject all goto usage (SIL 2+)

**SIL Guidance**:
- **SIL 0-1**: Recommended to avoid
- **SIL 2+**: **FORBIDDEN** - No goto allowed

---

### 2.6 Pitfall: Integer Overflow (MISRA C Rule 12.4)

**Problem**: No overflow protection on arithmetic operations.

**Wrong Code**:
```c
// WRONG: No overflow checking
uint16_t calculateTimeout(uint16_t base, uint16_t multiplier) {
    return base * multiplier;  // DANGER: Can overflow silently
}

uint32_t addCounters(uint32_t a, uint32_t b) {
    return a + b;  // DANGER: Overflow wraps around
}
```

**Root Cause**:
- Undefined behavior for signed overflow (C99 6.5)
- Wrapping behavior for unsigned (may be unintended)
- Can lead to incorrect safety calculations

**Right Code**:
```c
// RIGHT: Explicit overflow checking
typedef enum {
    MATH_SUCCESS = 0,
    MATH_OVERFLOW = 1
} math_result_t;

math_result_t calculateTimeout(uint16_t base, uint16_t multiplier, uint16_t* result) {
    if (result == NULL) {
        return MATH_OVERFLOW;
    }
    
    // Check for overflow before multiplication
    if (multiplier != 0U) {
        if (base > (UINT16_MAX / multiplier)) {
            return MATH_OVERFLOW;  // Would overflow
        }
    }
    
    *result = base * multiplier;
    return MATH_SUCCESS;
}

math_result_t addCounters(uint32_t a, uint32_t b, uint32_t* result) {
    if (result == NULL) {
        return MATH_OVERFLOW;
    }
    
    // Check for overflow before addition
    if (a > (UINT32_MAX - b)) {
        return MATH_OVERFLOW;  // Would overflow
    }
    
    *result = a + b;
    return MATH_SUCCESS;
}
```

**MISRA C Rules**:
- **Rule 12.4**: Evaluation of constant expressions should not overflow (Advisory)
- **Rule 18.1**: Pointer arithmetic shall not produce invalid pointer (Required)

**EN 50128 Reference**: Table A.3 #1 (Defensive Programming)

**Detection**:
- **GCC**: `-ftrapv` (trap on signed overflow)
- **Clang**: `-fsanitize=integer` (runtime overflow detection)
- **Code Review**: Check all arithmetic operations

**SIL Guidance**:
- **SIL 0-1**: Recommended
- **SIL 2+**: **MANDATORY** - All safety-critical arithmetic must check overflow

---

### 2.7 Pitfall: Divide by Zero (MISRA C Rule 1.3)

**Problem**: No validation before division or modulo operations.

**Wrong Code**:
```c
// WRONG: No zero check
uint32_t calculateAverage(uint32_t sum, uint16_t count) {
    return sum / count;  // CRASH if count == 0
}

uint8_t getModulo(uint16_t value, uint8_t divisor) {
    return (uint8_t)(value % divisor);  // CRASH if divisor == 0
}
```

**Root Cause**:
- Undefined behavior (C99 6.5.5) - division by zero
- Causes hardware exception (FPE signal on POSIX)
- System crash in safety-critical context

**Right Code**:
```c
// RIGHT: Validate divisor before operation
typedef enum {
    DIV_SUCCESS = 0,
    DIV_BY_ZERO = 1,
    DIV_NULL_RESULT = 2
} div_result_t;

div_result_t calculateAverage(uint32_t sum, uint16_t count, uint32_t* result) {
    if (result == NULL) {
        return DIV_NULL_RESULT;
    }
    if (count == 0U) {
        return DIV_BY_ZERO;  // Safe error return
    }
    
    *result = sum / count;  // Safe - count validated
    return DIV_SUCCESS;
}

div_result_t getModulo(uint16_t value, uint8_t divisor, uint8_t* result) {
    if (result == NULL) {
        return DIV_NULL_RESULT;
    }
    if (divisor == 0U) {
        return DIV_BY_ZERO;  // Safe error return
    }
    
    *result = (uint8_t)(value % divisor);  // Safe - divisor validated
    return DIV_SUCCESS;
}
```

**MISRA C Rules**:
- **Rule 1.3**: No undefined or critical unspecified behavior (Required)

**EN 50128 Reference**: Table A.3 #1 (Defensive Programming)

**Detection**:
- **Clang**: `-fsanitize=integer-divide-by-zero`
- **Cppcheck**: `--enable=warning` detects division by zero
- **Code Review**: Check all division and modulo operations

**SIL Guidance**:
- **SIL 0-1**: Highly Recommended
- **SIL 2+**: **MANDATORY** - All division must validate divisor != 0

---

### 2.8 Pitfall: Using Recursion (MISRA C Rule 17.2)

**Problem**: Unbounded stack usage from recursion.

**Wrong Code**:
```c
// WRONG: Recursive function
uint32_t factorial(uint32_t n) {
    if (n <= 1U) {
        return 1U;
    }
    return n * factorial(n - 1U);  // DANGER: Unbounded stack
}

// WRONG: Mutual recursion
void functionA(uint16_t depth);
void functionB(uint16_t depth);

void functionA(uint16_t depth) {
    if (depth > 0U) {
        functionB(depth - 1U);  // Calls B
    }
}

void functionB(uint16_t depth) {
    if (depth > 0U) {
        functionA(depth - 1U);  // Calls A
    }
}
```

**Root Cause**:
- Unbounded stack growth (stack overflow risk)
- Non-deterministic worst-case execution time
- Difficult to analyze memory usage

**Right Code**:
```c
// RIGHT: Iterative implementation
uint32_t factorial(uint32_t n) {
    uint32_t result = 1U;
    
    for (uint32_t i = 2U; i <= n; i++) {
        // Check overflow
        if (result > (UINT32_MAX / i)) {
            return 0U;  // Error: overflow
        }
        result *= i;
    }
    
    return result;  // Bounded stack, deterministic time
}

// RIGHT: State machine instead of mutual recursion
typedef enum {
    STATE_A,
    STATE_B,
    STATE_DONE
} state_t;

void processStates(uint16_t maxDepth) {
    state_t state = STATE_A;
    uint16_t depth = maxDepth;
    
    while ((depth > 0U) && (state != STATE_DONE)) {
        switch (state) {
            case STATE_A:
                // Do A's work
                state = STATE_B;
                depth--;
                break;
            case STATE_B:
                // Do B's work
                state = STATE_A;
                depth--;
                break;
            case STATE_DONE:
                break;
            default:
                state = STATE_DONE;
                break;
        }
    }
}
```

**MISRA C Rules**:
- **Rule 17.2**: Functions shall not call themselves directly or indirectly (Required)

**EN 50128 Reference**: Table A.4 #8 (Structured Programming - M for SIL 3-4)

**Detection**:
- **Cppcheck**: `--enable=warning` detects recursion
- **PC-lint Plus**: Message 534 (recursive call)
- **Call graph analysis**: Detect cycles in call graph

**SIL Guidance**:
- **SIL 0-1**: Highly Recommended to avoid
- **SIL 2+**: **FORBIDDEN** - No recursion allowed

---

## 3. Defensive Programming Mistakes

### 3.1 Pitfall: Ignoring Function Return Values

**Problem**: Not checking error return codes.

**Wrong Code**:
```c
// WRONG: Ignoring return values
void processData(const uint8_t* data, uint16_t length) {
    validateData(data, length);  // Returns error_t, ignored!
    
    transformData(data, length);  // What if validation failed?
    
    saveData(data, length);  // Saving invalid data!
}
```

**Root Cause**:
- Silent failures propagate through system
- Invalid data continues to be processed
- Violates fail-safe principle

**Right Code**:
```c
// RIGHT: Check all return values
typedef enum {
    RESULT_SUCCESS = 0,
    RESULT_VALIDATION_FAILED = 1,
    RESULT_TRANSFORM_FAILED = 2,
    RESULT_SAVE_FAILED = 3
} result_t;

result_t processData(const uint8_t* data, uint16_t length) {
    // Check validation
    result_t result = validateData(data, length);
    if (result != RESULT_SUCCESS) {
        return RESULT_VALIDATION_FAILED;  // Fail early
    }
    
    // Check transformation
    result = transformData(data, length);
    if (result != RESULT_SUCCESS) {
        return RESULT_TRANSFORM_FAILED;
    }
    
    // Check save
    result = saveData(data, length);
    if (result != RESULT_SUCCESS) {
        return RESULT_SAVE_FAILED;
    }
    
    return RESULT_SUCCESS;
}
```

**MISRA C Rules**:
- **Rule 17.7**: Return value of non-void function shall be used (Required)

**EN 50128 Reference**: Table A.3 #1 (Defensive Programming)

**Detection**:
- **GCC**: `-Wunused-result`
- **Cppcheck**: `--enable=warning` detects unused return values
- **Code Review**: Check all non-void function calls

**SIL Guidance**:
- **SIL 0-1**: Highly Recommended
- **SIL 2+**: **MANDATORY** - All return values must be checked

---

### 3.2 Pitfall: Missing Default Case in Switch

**Problem**: Switch without default case handling.

**Wrong Code**:
```c
// WRONG: No default case
typedef enum {
    STATE_IDLE = 0,
    STATE_ACTIVE = 1,
    STATE_ERROR = 2
} state_t;

void handleState(state_t state) {
    switch (state) {
        case STATE_IDLE:
            // Handle idle
            break;
        case STATE_ACTIVE:
            // Handle active
            break;
        case STATE_ERROR:
            // Handle error
            break;
        // MISSING: default case
    }
    // What if state has invalid value (e.g., 255)?
}
```

**Root Cause**:
- Enum can have values outside defined constants (memory corruption, etc.)
- No handler for unexpected values
- Silent failure continues execution

**Right Code**:
```c
// RIGHT: Always include default case
typedef enum {
    STATE_IDLE = 0,
    STATE_ACTIVE = 1,
    STATE_ERROR = 2
} state_t;

void handleState(state_t state) {
    switch (state) {
        case STATE_IDLE:
            // Handle idle
            break;
        case STATE_ACTIVE:
            // Handle active
            break;
        case STATE_ERROR:
            // Handle error
            break;
        default:
            // SAFE: Handle unexpected value
            logError("Invalid state: %d", (int)state);
            enterSafeState();
            break;
    }
}
```

**MISRA C Rules**:
- **Rule 16.1**: All switch statements shall be well-formed (Required)
- **Rule 16.4**: Every switch shall have default case (Required)

**EN 50128 Reference**: Table A.3 #1 (Defensive Programming)

**Detection**:
- **GCC**: `-Wswitch-default`
- **Cppcheck**: `--enable=style` warns on missing default
- **Code Review**: Verify all switch statements have default

**SIL Guidance**:
- **SIL 0-1**: Highly Recommended
- **SIL 2+**: **MANDATORY** - All switch must have default case

---

### 3.3 Pitfall: No Range Checking on Enums

**Problem**: Assuming enum values are always valid.

**Wrong Code**:
```c
// WRONG: No validation of enum parameter
typedef enum {
    SENSOR_TEMP = 0,
    SENSOR_PRESSURE = 1,
    SENSOR_FLOW = 2
} sensor_type_t;

static const char* sensorNames[] = {
    "Temperature",
    "Pressure",
    "Flow"
};

const char* getSensorName(sensor_type_t type) {
    return sensorNames[type];  // DANGER: type could be 255
}
```

**Root Cause**:
- Enum is just an integer (can have any value)
- Array access without bounds check
- Buffer overflow or crash

**Right Code**:
```c
// RIGHT: Validate enum before use
typedef enum {
    SENSOR_TEMP = 0,
    SENSOR_PRESSURE = 1,
    SENSOR_FLOW = 2,
    SENSOR_TYPE_COUNT  // Sentinel value
} sensor_type_t;

static const char* sensorNames[SENSOR_TYPE_COUNT] = {
    "Temperature",
    "Pressure",
    "Flow"
};

const char* getSensorName(sensor_type_t type) {
    // Validate enum range
    if ((uint32_t)type >= SENSOR_TYPE_COUNT) {
        return "Invalid";  // Safe default
    }
    
    return sensorNames[type];  // Safe - validated
}
```

**MISRA C Rules**:
- **Rule 10.3**: Value shall not be assigned to narrower or different essential type (Required)
- **Rule 18.1**: Pointer arithmetic shall not produce invalid pointer (Required)

**EN 50128 Reference**: Table A.3 #1 (Defensive Programming)

**Detection**:
- **Code Review**: Check all enum parameters are validated
- **Static Analysis**: Detect enum-to-array-index without bounds check

**SIL Guidance**:
- **SIL 0-1**: Highly Recommended
- **SIL 2+**: **MANDATORY** - All enum values must be range-checked before use

---

### 3.4 Pitfall: Magic Numbers

**Problem**: Using raw numeric literals without explanation.

**Wrong Code**:
```c
// WRONG: Magic numbers everywhere
void configureTimer(void) {
    TIMER_REG = 0x1234;      // What is 0x1234?
    TIMER_DIV = 16;          // Why 16?
    TIMER_CNT = 1000;        // What does 1000 represent?
}

bool isValidSpeed(uint16_t speed) {
    return (speed >= 10) && (speed <= 250);  // Why these limits?
}
```

**Root Cause**:
- Unclear intent (maintainability issue)
- Easy to make copy-paste errors
- Hard to update consistently

**Right Code**:
```c
// RIGHT: Named constants with documentation
// Timer configuration for 1ms tick
#define TIMER_PRESCALER_VALUE   0x1234U  // 16MHz / 0x1234 = 1kHz
#define TIMER_CLOCK_DIVIDER     16U      // Further divide by 16 for accuracy
#define TIMER_RELOAD_1MS        1000U    // 1000 ticks = 1ms

void configureTimer(void) {
    TIMER_REG = TIMER_PRESCALER_VALUE;
    TIMER_DIV = TIMER_CLOCK_DIVIDER;
    TIMER_CNT = TIMER_RELOAD_1MS;
}

// Speed limits from safety specification SRS-REQ-042
#define SPEED_MIN_KPH           10U      // Minimum valid speed
#define SPEED_MAX_KPH           250U     // Maximum valid speed

bool isValidSpeed(uint16_t speed) {
    return (speed >= SPEED_MIN_KPH) && (speed <= SPEED_MAX_KPH);
}
```

**MISRA C Rules**:
- **Rule 2.5**: Unused macro shall be removed (Advisory)
- **Dir 4.9**: Function-like macro should not be defined (Advisory)

**EN 50128 Reference**: Table A.4 #6 (Analysable Programs)

**Detection**:
- **Code Review**: Flag all numeric literals (except 0, 1, -1)
- **PC-lint Plus**: Message 1960 (magic number)

**SIL Guidance**:
- **SIL 0-1**: Recommended
- **SIL 2+**: **MANDATORY** - All numeric literals must be named constants (except 0, 1, -1)

---

### 3.5 Pitfall: Implicit Boolean Conversions

**Problem**: Using non-boolean values in boolean context.

**Wrong Code**:
```c
// WRONG: Implicit conversions to boolean
void processData(uint8_t* data, uint16_t length) {
    if (data) {  // Implicit: data != NULL
        // Process
    }
    
    if (length) {  // Implicit: length != 0
        // Process
    }
    
    uint8_t status = getStatus();
    if (status) {  // What does non-zero mean?
        // Handle
    }
}
```

**Root Cause**:
- Unclear intent (is non-zero success or failure?)
- Easy to misunderstand logic
- Error-prone during maintenance

**Right Code**:
```c
// RIGHT: Explicit comparisons
void processData(uint8_t* data, uint16_t length) {
    if (data != NULL) {  // Explicit NULL check
        // Process
    }
    
    if (length > 0U) {  // Explicit zero check
        // Process
    }
    
    uint8_t status = getStatus();
    if (status == STATUS_SUCCESS) {  // Explicit comparison
        // Handle
    }
}

// Even better: Use bool type
#include <stdbool.h>

bool isDataValid(const uint8_t* data, uint16_t length) {
    return (data != NULL) && (length > 0U);
}

void processData(uint8_t* data, uint16_t length) {
    if (isDataValid(data, length)) {  // Clear intent
        // Process
    }
}
```

**MISRA C Rules**:
- **Rule 14.4**: Controlling expression of if shall have bool type (Required)
- **Rule 10.1**: Operands shall not be of inappropriate essential type (Required)

**EN 50128 Reference**: Table A.4 #6 (Analysable Programs)

**Detection**:
- **Cppcheck**: `--enable=style` warns on implicit conversions
- **PC-lint Plus**: Enable all type conversion warnings
- **Code Review**: Check all if/while/for conditions

**SIL Guidance**:
- **SIL 0-1**: Recommended
- **SIL 2+**: **MANDATORY** - All boolean expressions must be explicit

---

## 4. Unit Testing Anti-Patterns

### 4.1 Pitfall: Testing Implementation Instead of Behavior

**Problem**: Tests tightly coupled to implementation details.

**Wrong Test**:
```c
// WRONG: Testing internal implementation
void test_calculateAverage_implementation(void) {
    // Test assumes specific algorithm
    uint32_t sum = 100;
    uint16_t count = 10;
    
    // Assumes implementation uses: sum / count
    uint32_t result = calculateAverage(sum, count);
    TEST_ASSERT_EQUAL_UINT32(10, result);
    
    // BRITTLE: Breaks if algorithm changes (e.g., rounding)
}
```

**Root Cause**:
- Tests break when implementation changes (even if behavior correct)
- Doesn't test actual requirements
- Maintenance burden

**Right Test**:
```c
// RIGHT: Test observable behavior and requirements
void test_calculateAverage_returns_correct_value(void) {
    // Test requirement: Average of [10, 20, 30] is 20
    uint32_t values[] = {10, 20, 30};
    uint16_t count = 3;
    
    uint32_t result = calculateAverageFromArray(values, count);
    TEST_ASSERT_EQUAL_UINT32(20, result);  // Test output, not algorithm
}

void test_calculateAverage_handles_zero_count(void) {
    // Test requirement: Shall return error for zero count
    uint32_t values[] = {10, 20, 30};
    
    error_t result = calculateAverageFromArray(values, 0);
    TEST_ASSERT_EQUAL(ERROR_INVALID_PARAM, result);  // Test behavior
}
```

**Best Practice**:
- Test **requirements** (SRS traceability)
- Test **observable behavior** (inputs → outputs)
- Test **edge cases** (boundary values)
- Don't test implementation details

**Detection**:
- **Code Review**: Check test names reference requirements (SRS-XXX)
- **Traceability**: Verify test → requirement mapping

---

### 4.2 Pitfall: No Negative Testing

**Problem**: Only testing success cases, ignoring error paths.

**Wrong Test**:
```c
// WRONG: Only happy path tested
void test_processData(void) {
    uint8_t data[] = {1, 2, 3};
    
    error_t result = processData(data, 3);
    TEST_ASSERT_EQUAL(SUCCESS, result);
    
    // MISSING: What if data == NULL?
    // MISSING: What if length == 0?
    // MISSING: What if data invalid?
}
```

**Root Cause**:
- Error paths not exercised
- Defensive checks not validated
- False sense of test coverage

**Right Test**:
```c
// RIGHT: Test both success and error cases
void test_processData_success(void) {
    uint8_t data[] = {1, 2, 3};
    
    error_t result = processData(data, 3);
    TEST_ASSERT_EQUAL(SUCCESS, result);
}

void test_processData_null_pointer(void) {
    error_t result = processData(NULL, 3);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
}

void test_processData_zero_length(void) {
    uint8_t data[] = {1, 2, 3};
    
    error_t result = processData(data, 0);
    TEST_ASSERT_EQUAL(ERROR_INVALID_LENGTH, result);
}

void test_processData_invalid_data(void) {
    uint8_t data[] = {0xFF, 0xFF, 0xFF};  // Invalid values
    
    error_t result = processData(data, 3);
    TEST_ASSERT_EQUAL(ERROR_INVALID_DATA, result);
}
```

**Best Practice**:
- **Test error paths** (NULL, zero, invalid, overflow)
- **Test boundary values** (min, max, min-1, max+1)
- **Test invalid state transitions**
- **Aim for 100% branch coverage** (SIL 3-4)

**EN 50128 Reference**: Table A.21 (Test Coverage - Branch M for SIL 3-4)

---

### 4.3 Pitfall: Test Interdependence

**Problem**: Tests depend on execution order or shared state.

**Wrong Test**:
```c
// WRONG: Tests share state
static uint32_t globalCounter = 0;

void test_incrementCounter(void) {
    incrementCounter();
    TEST_ASSERT_EQUAL_UINT32(1, globalCounter);  // Assumes globalCounter was 0
}

void test_decrementCounter(void) {
    decrementCounter();
    TEST_ASSERT_EQUAL_UINT32(0, globalCounter);  // Depends on previous test!
}
```

**Root Cause**:
- Tests break when run in different order
- Difficult to debug failures
- Not truly unit tests (integration tests)

**Right Test**:
```c
// RIGHT: Each test is independent
void setUp(void) {
    // Reset state before each test
    resetCounter();
}

void tearDown(void) {
    // Clean up after each test (if needed)
}

void test_incrementCounter(void) {
    // Test is self-contained
    uint32_t before = getCounter();
    incrementCounter();
    uint32_t after = getCounter();
    
    TEST_ASSERT_EQUAL_UINT32(before + 1, after);
}

void test_decrementCounter(void) {
    // Test is self-contained
    setCounter(5);  // Known starting state
    
    decrementCounter();
    
    TEST_ASSERT_EQUAL_UINT32(4, getCounter());
}
```

**Best Practice**:
- Use `setUp()` and `tearDown()` for test isolation
- Each test should run independently
- No shared mutable state between tests
- Test order should not matter

---

### 4.4 Pitfall: Mocking Everything

**Problem**: Over-mocking makes tests fragile and meaningless.

**Wrong Test**:
```c
// WRONG: Mocking everything, even simple functions
uint32_t mock_add(uint32_t a, uint32_t b) {
    return 5;  // Why mock addition?
}

void test_calculateTotal(void) {
    // Mocking basic math operations is pointless
    uint32_t result = mock_add(2, 3);
    TEST_ASSERT_EQUAL_UINT32(5, result);
    // What are we actually testing?
}
```

**Root Cause**:
- Over-mocking tests the mocks, not the code
- Loses confidence in tests
- Doesn't catch real integration issues

**Right Test**:
```c
// RIGHT: Mock only external dependencies
// Real calculation logic
uint32_t calculateTotal(uint32_t a, uint32_t b) {
    return a + b;  // Test this directly
}

// Mock only hardware/external dependencies
static uint8_t mock_sensorValue = 0;

uint8_t readSensor(void) {
    return mock_sensorValue;  // Mock hardware access
}

void test_processTemperature(void) {
    // Mock hardware sensor
    mock_sensorValue = 25;
    
    // Test real logic
    uint8_t result = processTemperature();
    
    TEST_ASSERT_EQUAL_UINT8(77, result);  // 25°C = 77°F
}
```

**Best Practice**:
- **Mock external dependencies** (hardware, I/O, OS)
- **Don't mock simple functions** (getters, math)
- **Don't mock the unit under test**
- **Use real code when possible**

---

### 4.5 Pitfall: No Coverage Measurement

**Problem**: Not measuring test coverage, missing untested code.

**Wrong Approach**:
```bash
# WRONG: Just run tests, no coverage
$ gcc -o test test.c unit.c
$ ./test
All tests passed!  # But what % of code is tested?
```

**Root Cause**:
- No visibility into untested code paths
- False confidence ("all tests pass")
- Can't verify SIL requirements (100% for SIL 3-4)

**Right Approach**:
```bash
# RIGHT: Measure coverage with gcov/lcov
$ gcc -fprofile-arcs -ftest-coverage -o test test.c unit.c
$ ./test
$ gcov unit.c
File 'unit.c'
Lines executed: 95.00% of 100
Branches executed: 90.00% of 50

$ lcov --capture --directory . --output-file coverage.info
$ genhtml coverage.info --output-directory coverage_html
```

**Best Practice**:
- **Always measure coverage** (statement, branch, condition)
- **Use coverage tools** (gcov/lcov for C)
- **Meet SIL requirements**:
  - SIL 0-1: Statement (HR), Branch (HR)
  - SIL 2: Statement (HR), Branch (**M**)
  - SIL 3-4: Statement (**M**), Branch (**M**), Condition (**M**)
- **Review uncovered lines** and add tests

**EN 50128 Reference**: Table A.21 (Test Coverage for Code)

**Tool Commands**:
```bash
# Statement coverage (SIL 2+ Mandatory)
gcov --branch-counts unit.c

# Branch coverage (SIL 2+ Mandatory)
lcov --summary coverage.info | grep branches

# MC/DC coverage (SIL 3-4 Highly Recommended)
python3 tools/mcdc/mcdc_analyzer.py --source unit.c --test test.c
```

---

## 5. Memory Management Pitfalls

### 5.1 Pitfall: Using Dynamic Allocation (SIL 2+)

**Problem**: Using malloc/free in safety-critical code.

**Wrong Code**:
```c
// WRONG: Dynamic allocation (FORBIDDEN SIL 2+)
void processMessage(uint16_t messageSize) {
    uint8_t* buffer = (uint8_t*)malloc(messageSize);  // FORBIDDEN
    if (buffer == NULL) {
        return;  // Out of memory
    }
    
    // Process message
    readMessage(buffer, messageSize);
    
    free(buffer);  // FORBIDDEN
}
```

**Root Cause**:
- Non-deterministic allocation time
- Memory fragmentation over time
- Unpredictable out-of-memory conditions
- Leaks from missed free() calls

**Right Code**:
```c
// RIGHT: Static allocation (MANDATORY SIL 2+)
#define MAX_MESSAGE_SIZE 256U

static uint8_t messageBuffer[MAX_MESSAGE_SIZE];  // Static allocation

error_t processMessage(uint16_t messageSize) {
    // Validate size against static buffer
    if (messageSize > MAX_MESSAGE_SIZE) {
        return ERROR_MESSAGE_TOO_LARGE;
    }
    
    // Use static buffer (deterministic, no fragmentation)
    readMessage(messageBuffer, messageSize);
    
    return SUCCESS;
}
```

**MISRA C Rules**:
- **Rule 21.3**: malloc/free shall not be used (Required)

**EN 50128 Reference**: Table A.4 #5 (Modular Approach - M for SIL 2+)

**Detection**:
- **Cppcheck**: `--enable=warning` detects malloc/free
- **PC-lint Plus**: Message 586 (function deprecated)
- **Code Review**: Zero tolerance for malloc/calloc/realloc/free (SIL 2+)

**SIL Guidance**:
- **SIL 0-1**: Recommended to avoid
- **SIL 2+**: **FORBIDDEN** - No dynamic memory allocation

---

### 5.2 Pitfall: Buffer Overruns

**Problem**: Writing beyond buffer boundaries.

**Wrong Code**:
```c
// WRONG: No bounds checking on string operations
void copyName(const char* source) {
    char destination[32];
    strcpy(destination, source);  // DANGER: source could be > 32 bytes
}

void appendData(uint8_t* buffer, const uint8_t* data, uint16_t dataLen) {
    for (uint16_t i = 0; i < dataLen; i++) {
        buffer[i] = data[i];  // DANGER: buffer size unknown
    }
}
```

**Root Cause**:
- Buffer overflow (stack/heap corruption)
- Security vulnerability (arbitrary code execution)
- Undefined behavior

**Right Code**:
```c
// RIGHT: Explicit bounds checking
#define NAME_MAX_LENGTH 32U

error_t copyName(const char* source) {
    static char destination[NAME_MAX_LENGTH];
    
    if (source == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    // Use safe string copy with explicit length
    size_t sourceLen = strnlen(source, NAME_MAX_LENGTH);
    if (sourceLen >= NAME_MAX_LENGTH) {
        return ERROR_NAME_TOO_LONG;
    }
    
    // Safe copy (includes null terminator)
    (void)strncpy(destination, source, NAME_MAX_LENGTH - 1U);
    destination[NAME_MAX_LENGTH - 1U] = '\0';  // Ensure null termination
    
    return SUCCESS;
}

error_t appendData(uint8_t* buffer, uint16_t bufferSize,
                   const uint8_t* data, uint16_t dataLen) {
    if ((buffer == NULL) || (data == NULL)) {
        return ERROR_NULL_POINTER;
    }
    
    // Validate data fits in buffer
    if (dataLen > bufferSize) {
        return ERROR_BUFFER_TOO_SMALL;
    }
    
    // Safe copy with explicit bounds
    for (uint16_t i = 0; i < dataLen; i++) {
        buffer[i] = data[i];
    }
    
    return SUCCESS;
}
```

**MISRA C Rules**:
- **Rule 21.17**: Use of string handling functions from <string.h> shall be justified (Mandatory)

**EN 50128 Reference**: Table A.3 #1 (Defensive Programming)

**Detection**:
- **AddressSanitizer**: `-fsanitize=address` (runtime)
- **Valgrind**: `valgrind --tool=memcheck`
- **Static Analysis**: Cppcheck, PC-lint Plus

**SIL Guidance**:
- **SIL 0-1**: Highly Recommended
- **SIL 2+**: **MANDATORY** - All buffer operations must be bounds-checked

---

### 5.3 Pitfall: Memory Leaks (Static Allocation)

**Problem**: Not releasing acquired resources.

**Wrong Code**:
```c
// WRONG: Resource leak (even without malloc)
static bool mutexAcquired = false;

void criticalSection(void) {
    acquireMutex();
    mutexAcquired = true;
    
    if (errorCondition()) {
        return;  // LEAK: Mutex not released!
    }
    
    // Do work
    
    releaseMutex();
    mutexAcquired = false;
}
```

**Root Cause**:
- Early return skips resource cleanup
- Resource remains locked/unavailable
- Deadlock or resource exhaustion

**Right Code**:
```c
// RIGHT: Structured cleanup on all paths
static bool mutexAcquired = false;

error_t criticalSection(void) {
    error_t result = SUCCESS;
    
    // Acquire resource
    acquireMutex();
    mutexAcquired = true;
    
    // Check for errors (but don't return early)
    if (errorCondition()) {
        result = ERROR_CONDITION;
    } else {
        // Do work
        result = doWork();
    }
    
    // Always release resource
    releaseMutex();
    mutexAcquired = false;
    
    return result;
}
```

**Better Pattern (RAII-like for C)**:
```c
// Even better: Use structured scope
error_t criticalSection(void) {
    error_t result = SUCCESS;
    
    // Acquire at scope start
    acquireMutex();
    
    // Process with all paths covered
    if (errorCondition()) {
        result = ERROR_CONDITION;
        goto cleanup;  // Acceptable use of goto for cleanup
    }
    
    result = doWork();
    
cleanup:
    // Always executed (single exit point)
    releaseMutex();
    return result;
}
```

**EN 50128 Reference**: Table A.3 #1 (Defensive Programming)

**Detection**:
- **Static Analysis**: Cppcheck `--enable=warning`
- **Code Review**: Verify all acquire/release pairs
- **Runtime**: Custom resource tracking

---

## 6. Concurrency and Timing Issues

### 6.1 Pitfall: Race Conditions on Shared Variables

**Problem**: Multiple contexts accessing shared data without synchronization.

**Wrong Code**:
```c
// WRONG: No synchronization on shared variable
static volatile uint32_t sharedCounter = 0;

// Called from ISR
void ISR_Handler(void) {
    sharedCounter++;  // RACE: Read-modify-write not atomic
}

// Called from main loop
uint32_t getCounter(void) {
    return sharedCounter;  // RACE: May read partial update
}
```

**Root Cause**:
- Read-modify-write operations not atomic
- Compiler may generate multiple instructions for `++`
- Interrupt can occur mid-operation

**Right Code**:
```c
// RIGHT: Atomic access with critical sections
static volatile uint32_t sharedCounter = 0;

// Called from ISR
void ISR_Handler(void) {
    // For 32-bit atomic increment, use atomic operations
    __atomic_fetch_add(&sharedCounter, 1, __ATOMIC_SEQ_CST);
}

// Called from main loop
uint32_t getCounter(void) {
    uint32_t value;
    
    // Disable interrupts for atomic read
    disableInterrupts();
    value = sharedCounter;
    enableInterrupts();
    
    return value;
}

// Alternative: Use mutex if not in ISR
uint32_t getCounterSafe(void) {
    acquireMutex(&counterMutex);
    uint32_t value = sharedCounter;
    releaseMutex(&counterMutex);
    
    return value;
}
```

**Best Practice**:
- **Use atomic operations** for simple types
- **Use critical sections** for compound operations
- **Use mutexes** for complex operations (not in ISR)
- **Minimize critical section duration**

**Detection**:
- **ThreadSanitizer**: `-fsanitize=thread` (runtime)
- **Code Review**: Check all shared variable access
- **Static Analysis**: Look for volatile without synchronization

---

### 6.2 Pitfall: Volatile Misuse

**Problem**: Not using volatile for hardware registers or ISR-shared data.

**Wrong Code**:
```c
// WRONG: Missing volatile for hardware register
#define UART_STATUS_REG (*(uint32_t*)0x40000000)

void waitForTxReady(void) {
    while ((UART_STATUS_REG & TX_READY_BIT) == 0) {
        // DANGER: Compiler may optimize loop away
        // (thinks register never changes)
    }
}

// WRONG: Missing volatile for ISR-shared flag
static bool dataReady = false;

void ISR_DataReceived(void) {
    dataReady = true;  // ISR sets flag
}

void processData(void) {
    while (!dataReady) {  // DANGER: Compiler may optimize loop away
        // Wait
    }
}
```

**Root Cause**:
- Compiler doesn't know value changes externally (hardware, ISR)
- Optimizer removes "unnecessary" reads
- Loop never exits

**Right Code**:
```c
// RIGHT: volatile for hardware registers
#define UART_STATUS_REG (*(volatile uint32_t*)0x40000000)

void waitForTxReady(void) {
    while ((UART_STATUS_REG & TX_READY_BIT) == 0) {
        // Compiler always reads register (not optimized away)
    }
}

// RIGHT: volatile for ISR-shared data
static volatile bool dataReady = false;

void ISR_DataReceived(void) {
    dataReady = true;  // ISR sets flag
}

void processData(void) {
    while (!dataReady) {  // Compiler always reads variable
        // Wait
    }
    
    // Better: Add timeout
    uint32_t timeout = TIMEOUT_VALUE;
    while (!dataReady && (timeout > 0)) {
        timeout--;
    }
    if (timeout == 0) {
        handleTimeout();
    }
}
```

**MISRA C Rules**:
- **Rule 13.1**: Initializer lists shall not contain persistent side effects (Required)

**EN 50128 Reference**: Table A.4 #6 (Analysable Programs)

**Detection**:
- **Code Review**: Check all hardware register accesses
- **Code Review**: Check all ISR-shared variables
- **Static Analysis**: Detect busy-wait loops without volatile

---

## 7. Integration and Interface Pitfalls

### 7.1 Pitfall: Inconsistent Interface Assumptions

**Problem**: Caller and callee have different assumptions about interface contract.

**Wrong Interface**:
```c
// module_a.h (Interface definition)
// AMBIGUOUS: Who allocates buffer? Who validates inputs?
void processData(uint8_t* buffer, uint16_t length);

// module_a.c (Implementation assumes caller validates)
void processData(uint8_t* buffer, uint16_t length) {
    // Assumes buffer != NULL and length > 0
    for (uint16_t i = 0; i < length; i++) {
        buffer[i] = transform(buffer[i]);
    }
}

// module_b.c (Caller assumes callee validates)
void caller(void) {
    uint8_t* data = getData();  // Could return NULL
    uint16_t len = getLength(); // Could return 0
    
    processData(data, len);  // CRASH if data == NULL
}
```

**Root Cause**:
- Unclear interface contract (preconditions/postconditions)
- No documentation of responsibilities
- Integration failures

**Right Interface**:
```c
// module_a.h (Clear interface contract)
/**
 * @brief Process data buffer with transformation
 * 
 * @param[in,out] buffer  Pointer to data buffer (must not be NULL)
 * @param[in]     length  Buffer length in bytes (must be > 0)
 * 
 * @return RESULT_SUCCESS if processed successfully
 * @return RESULT_NULL_POINTER if buffer is NULL
 * @return RESULT_INVALID_LENGTH if length is 0
 * 
 * @pre  buffer != NULL
 * @pre  length > 0
 * @post All bytes in buffer are transformed
 * 
 * @note  This function modifies buffer in-place
 * @trace SRS-REQ-042
 */
result_t processData(uint8_t* buffer, uint16_t length);

// module_a.c (Implementation validates ALL inputs - defensive)
result_t processData(uint8_t* buffer, uint16_t length) {
    // Always validate, even if documented as precondition
    if (buffer == NULL) {
        return RESULT_NULL_POINTER;
    }
    if (length == 0U) {
        return RESULT_INVALID_LENGTH;
    }
    
    // Safe to process
    for (uint16_t i = 0; i < length; i++) {
        buffer[i] = transform(buffer[i]);
    }
    
    return RESULT_SUCCESS;
}

// module_b.c (Caller still validates and checks result)
void caller(void) {
    uint8_t* data = getData();
    uint16_t len = getLength();
    
    // Caller also validates (defense in depth)
    result_t result = processData(data, len);
    if (result != RESULT_SUCCESS) {
        handleError(result);
        return;
    }
    
    // Continue processing
}
```

**Best Practice**:
- **Document interface contracts** (Doxygen-style)
- **Validate on both sides** (defense in depth)
- **Use Dbc (Design by Contract)** patterns
- **Clear parameter annotations** (`[in]`, `[out]`, `[in,out]`)

**EN 50128 Reference**: Table A.3 #3 (Fully Defined Interface - HR SIL 1-4)

---

### 7.2 Pitfall: Endianness Assumptions

**Problem**: Assuming byte order when communicating between systems.

**Wrong Code**:
```c
// WRONG: Assumes little-endian
void sendValue(uint32_t value) {
    uint8_t* bytes = (uint8_t*)&value;  // DANGER: Byte order varies
    uart_send(bytes[0]);  // May send MSB or LSB depending on CPU
    uart_send(bytes[1]);
    uart_send(bytes[2]);
    uart_send(bytes[3]);
}

uint32_t receiveValue(void) {
    uint32_t value;
    uint8_t* bytes = (uint8_t*)&value;
    bytes[0] = uart_receive();  // DANGER: May be wrong byte order
    bytes[1] = uart_receive();
    bytes[2] = uart_receive();
    bytes[3] = uart_receive();
    return value;
}
```

**Root Cause**:
- Different CPUs use different byte order (little/big endian)
- Communication protocol doesn't specify byte order
- Works on one platform, fails on another

**Right Code**:
```c
// RIGHT: Explicit byte order (network byte order = big-endian)
void sendValue(uint32_t value) {
    // Send MSB first (big-endian, network byte order)
    uart_send((uint8_t)((value >> 24) & 0xFFU));
    uart_send((uint8_t)((value >> 16) & 0xFFU));
    uart_send((uint8_t)((value >> 8) & 0xFFU));
    uart_send((uint8_t)(value & 0xFFU));
}

uint32_t receiveValue(void) {
    // Receive MSB first (big-endian)
    uint32_t value = 0U;
    value |= ((uint32_t)uart_receive()) << 24;
    value |= ((uint32_t)uart_receive()) << 16;
    value |= ((uint32_t)uart_receive()) << 8;
    value |= (uint32_t)uart_receive();
    return value;
}

// Or use standard functions
#include <arpa/inet.h>  // For htonl/ntohl

void sendValueStandard(uint32_t value) {
    uint32_t networkValue = htonl(value);  // Host to network (big-endian)
    uint8_t* bytes = (uint8_t*)&networkValue;
    for (uint8_t i = 0; i < 4U; i++) {
        uart_send(bytes[i]);
    }
}
```

**Best Practice**:
- **Always specify byte order** in communication protocols
- **Use explicit bit shifts** for serialization
- **Use standard functions** (htonl/ntohl) when available
- **Document endianness** in interface specifications

**EN 50128 Reference**: Table A.6 (Integration Techniques)

---

## 8. Code Review Common Findings

### 8.1 Finding: Insufficient Error Handling

**Example**:
```c
// WRONG: Incomplete error handling
error_t initialize(void) {
    if (initHardware() != SUCCESS) {
        return ERROR_HARDWARE;
    }
    
    if (loadConfig() != SUCCESS) {
        return ERROR_CONFIG;  // PROBLEM: Hardware not de-initialized
    }
    
    return SUCCESS;
}
```

**Fix**:
```c
// RIGHT: Proper cleanup on all error paths
error_t initialize(void) {
    error_t result;
    
    result = initHardware();
    if (result != SUCCESS) {
        return ERROR_HARDWARE;
    }
    
    result = loadConfig();
    if (result != SUCCESS) {
        // Clean up hardware before returning
        deinitHardware();
        return ERROR_CONFIG;
    }
    
    return SUCCESS;
}
```

**Review Checklist Item**: "All error paths properly clean up resources"

---

### 8.2 Finding: Inconsistent Naming Conventions

**Example**:
```c
// WRONG: Inconsistent naming
uint32_t GetSensorValue(void);      // PascalCase
void processSensorData(void);       // camelCase
void calculate_average(void);       // snake_case
#define MaxSensors 10                // Inconsistent
```

**Fix**:
```c
// RIGHT: Consistent naming (choose one style project-wide)
// Example: snake_case for C
uint32_t get_sensor_value(void);
void process_sensor_data(void);
void calculate_average(void);
#define MAX_SENSORS 10U              // UPPER_CASE for macros
```

**Review Checklist Item**: "Naming follows project coding standard"

---

### 8.3 Finding: Missing Traceability

**Example**:
```c
// WRONG: No traceability to requirements
void calculateBraking(uint16_t speed) {
    // Complex safety-critical calculation
    // Which requirement does this implement?
}
```

**Fix**:
```c
// RIGHT: Clear traceability
/**
 * @brief Calculate braking distance per SRS-SAFE-023
 * 
 * Implements emergency braking distance calculation
 * for speeds up to 250 km/h as specified in safety
 * requirements document.
 * 
 * @param speed  Current speed in km/h [0-250]
 * @return Braking distance in meters
 * 
 * @trace SRS-SAFE-023 (Emergency braking distance)
 * @trace SAS-ARCH-015 (Safety architecture)
 */
uint32_t calculateBraking(uint16_t speed) {
    // Implementation
}
```

**Review Checklist Item**: "All safety-critical functions have @trace tags"

---

## 9. Tool Usage Mistakes

### 9.1 Pitfall: Not Running Static Analysis

**Problem**: Skipping static analysis tools.

**Wrong Process**:
```bash
# WRONG: Only compile and test
$ gcc -o myapp main.c module.c
$ ./myapp
# Ship it!
```

**Right Process**:
```bash
# RIGHT: Run static analysis (MANDATORY SIL 3-4)
$ cppcheck --enable=all --xml --xml-version=2 src/ 2> cppcheck.xml
$ scan-build make  # Clang static analyzer
$ lizard -l c -w src/  # Complexity analysis

# Review results before proceeding
$ python3 tools/scripts/analyze_cppcheck.py cppcheck.xml
```

**EN 50128 Guidance**:
- **SIL 0-1**: Recommended
- **SIL 2**: Highly Recommended
- **SIL 3-4**: **MANDATORY** (Table A.19)

---

### 9.2 Pitfall: Ignoring Tool Warnings

**Problem**: Suppressing warnings without investigation.

**Wrong Approach**:
```c
// WRONG: Blindly suppressing warnings
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
void processData(void) {
    uint32_t unusedVar;  // Why is this here?
    // ...
}
#pragma GCC diagnostic pop
```

**Right Approach**:
```c
// RIGHT: Fix the issue, or document justification
void processData(void) {
    // Removed unusedVar - was dead code
    // ...
}

// Or if suppression justified:
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-align"
// Justification: Hardware register requires unaligned access
// This is documented exception in platform guide section 3.2
volatile uint32_t* reg = (volatile uint32_t*)0x40000001;
#pragma GCC diagnostic pop
```

**Best Practice**:
- **Fix warnings** (don't suppress)
- **If suppression required**: Document justification
- **Track deviations** (MISRA C deviation list)
- **Aim for zero warnings** (SIL 3-4)

---

## 10. Summary and Quick Reference

### Top 10 Critical Pitfalls (SIL 3-4)

1. **No NULL checks** → Always validate pointers
2. **Array out of bounds** → Always bounds-check array access
3. **Using malloc/free** → Use static allocation only (SIL 2+)
4. **Integer overflow** → Check before arithmetic
5. **Divide by zero** → Validate divisor != 0
6. **Ignoring return values** → Check all error codes
7. **No default in switch** → Always include default case
8. **Using recursion** → Use iteration instead
9. **Missing volatile** → Use for hardware/ISR-shared data
10. **No coverage measurement** → Measure and achieve 100% (SIL 3-4)

### Detection Strategy Matrix

| Pitfall Category | Static Analysis | Code Review | Runtime Testing |
|------------------|-----------------|-------------|-----------------|
| MISRA C violations | ✓ Primary | ✓ Secondary | - |
| Defensive programming | ✓ Secondary | ✓ Primary | ✓ Tertiary |
| Memory issues | ✓ Secondary | ✓ Secondary | ✓ Primary (ASan/Valgrind) |
| Concurrency | - | ✓ Primary | ✓ Primary (TSan) |
| Integration | - | ✓ Primary | ✓ Primary |
| Testing | - | ✓ Primary | ✓ Primary (coverage) |

### Tool Recommendations by Pitfall Type

**MISRA C Violations**:
- PC-lint Plus (best), Cppcheck, Clang

**Memory Issues**:
- AddressSanitizer (`-fsanitize=address`)
- Valgrind (`valgrind --tool=memcheck`)

**Concurrency Issues**:
- ThreadSanitizer (`-fsanitize=thread`)
- Code review (primary method)

**Coverage**:
- gcov/lcov (statement, branch)
- `tools/mcdc/mcdc_analyzer.py` (MC/DC for SIL 3-4)

---

## References

### EN 50128 Standard
- **Section 7.4**: Software Design and Implementation
- **Section 7.5**: Component Testing
- **Table A.3**: Software Architecture Techniques
- **Table A.4**: Software Design and Implementation Techniques
- **Table A.12**: Design and Coding Standards
- **Table A.19**: Static Analysis
- **Table A.21**: Test Coverage for Code

### MISRA C:2012
- **Rule 1.3**: No undefined behavior (Required)
- **Rule 9.1**: No uninitialized variables (Mandatory)
- **Rule 10.1**: No inappropriate type operations (Required)
- **Rule 12.4**: No constant overflow (Advisory)
- **Rule 15.1**: No goto (Advisory)
- **Rule 17.2**: No recursion (Required)
- **Rule 17.7**: Check return values (Required)
- **Rule 18.1**: No invalid pointers (Required)
- **Rule 21.3**: No malloc/free (Required)

### Related Resources
- `misra-c-coding-patterns.md` - Complete MISRA C pattern library
- `unit-testing-patterns.md` - Testing patterns and strategies
- `code-review-checklist.md` - 124-item review checklist
- `workflows/defensive-coding-implementation.md` - Defensive programming workflow

---

**Document Control**

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2026-03-13 | EN50128 Team | Initial release |

**Approval**

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Author (IMP) | | | |
| Reviewer (QUA) | | | |
| Approver (PM) | | | |

---

*This document is part of the EN 50128 Implementation Skill. For workflow guidance, see `workflows/` directory. For complete pattern libraries, see other files in `resources/` directory.*
