# MISRA C:2012 Coding Patterns for EN 50128 Railway Safety Software

**Purpose**: Comprehensive reference catalog of MISRA C:2012 compliant coding patterns for implementing EN 50128 railway safety-critical software in C.

**Scope**: Implementation phase (Phase 4) - code writing, static analysis, MISRA C compliance verification

**Audience**: Implementers (IMP), Verifiers (VER), Quality Assurance (QUA)

**EN 50128 Reference**: 
- Section 7.4 "Component Design and Implementation"
- Table A.4, Technique 6 "Design and Coding Standards" (**MANDATORY** SIL 3-4, HR SIL 2)
- Table A.12 "Design and Coding Standards"

**MISRA C:2012 Standard**: Motor Industry Software Reliability Association C:2012 (Amendments 1, 2, 3)

**Related Documents**:
- `workflows/misra-c-implementation.md` - Step-by-step MISRA C implementation workflow
- `../en50128-design/resources/misra-c-design-guidelines.md` - Design phase MISRA C considerations
- `resources/common-pitfalls.md` - Common MISRA C violations and fixes

---

## Table of Contents

1. [MISRA C:2012 Rule Catalog Summary](#1-misra-c2012-rule-catalog-summary)
2. [Type Safety Patterns](#2-type-safety-patterns)
3. [Pointer and Array Patterns](#3-pointer-and-array-patterns)
4. [Control Flow Patterns](#4-control-flow-patterns)
5. [Function Patterns](#5-function-patterns)
6. [Variable and Initialization Patterns](#6-variable-and-initialization-patterns)
7. [Arithmetic and Expression Patterns](#7-arithmetic-and-expression-patterns)
8. [Preprocessor Patterns](#8-preprocessor-patterns)
9. [Standard Library Usage Patterns](#9-standard-library-usage-patterns)
10. [Header File Patterns](#10-header-file-patterns)
11. [MISRA C Deviation Process](#11-misra-c-deviation-process)
12. [Quick Reference Card](#12-quick-reference-card)

---

## 1. MISRA C:2012 Rule Catalog Summary

### 1.1 Rule Categories Overview

MISRA C:2012 contains **178 rules** and **16 directives** organized into 23 categories.

| Category | Rules | Key Focus | Tool Checkable |
|----------|-------|-----------|----------------|
| **Directives 1-5** | D.1.1-D.5.5 | Process requirements, compiler warnings, character sets | Partial |
| **Environment (Rule 1)** | 1.1-1.4 | Implementation-defined behavior, undefined behavior | Yes |
| **Unused Code (Rule 2)** | 2.1-2.7 | Dead code, unreachable code | Yes |
| **Comments (Rule 3)** | 3.1-3.2 | Comment syntax, nested comments | Yes |
| **Character Sets (Rule 4)** | 4.1-4.2 | Trigraphs, character escapes | Yes |
| **Identifiers (Rule 5)** | 5.1-5.9 | Name length, shadowing, reserved names | Yes |
| **Types (Rule 6)** | 6.1-6.2 | Bit-fields, char signedness | Partial |
| **Literals (Rule 7)** | 7.1-7.4 | Octal constants, Unicode, suffix usage | Yes |
| **Declarations (Rule 8)** | 8.1-8.14 | Type specifiers, linkage, extern, static | Yes |
| **Initialisation (Rule 9)** | 9.1-9.5 | Uninitialized variables, array init | Yes |
| **Essential Type (Rule 10)** | 10.1-10.8 | Implicit conversions, casts, essential types | Yes |
| **Pointer Type (Rule 11)** | 11.1-11.9 | Pointer conversions, function pointers | Yes |
| **Expressions (Rule 12)** | 12.1-12.5 | Operator precedence, side effects, evaluation order | Yes |
| **Side Effects (Rule 13)** | 13.1-13.6 | Increment/decrement, side effect ordering | Yes |
| **Control Flow (Rule 14)** | 14.1-14.4 | Unreachable code, infinite loops, goto | Yes |
| **Switch (Rule 15)** | 15.1-15.7 | Switch/case syntax, boolean conditions | Yes |
| **Control Flow (Rule 16)** | 16.1-16.7 | Switch statements, default case, fallthrough | Yes |
| **Functions (Rule 17)** | 17.1-17.8 | Varargs, recursion, return values | Yes |
| **Pointers/Arrays (Rule 18)** | 18.1-18.8 | Pointer arithmetic, array indexing | Partial |
| **Overlapping Storage (Rule 19)** | 19.1-19.2 | Object overlap, pointer aliasing | Partial |
| **Preprocessor (Rule 20)** | 20.1-20.14 | #include, macros, #define, #undef | Yes |
| **Standard Library (Rule 21)** | 21.1-21.21 | stdio, stdlib, string.h, time.h usage | Yes |
| **Resources (Rule 22)** | 22.1-22.10 | File operations, memory management | Partial |

### 1.2 Rule Classifications

**Three Classification Levels**:

1. **Mandatory (M)**: MUST be complied with. Deviation requires formal safety argument.
   - **143 mandatory rules** in MISRA C:2012
   - **SIL 3-4**: Zero mandatory violations allowed
   
2. **Required (R)**: MUST be complied with. Deviation acceptable with documented rationale.
   - **10 required rules** in MISRA C:2012
   
3. **Advisory (A)**: Recommended. Deviation permitted but should be documented.
   - **125 advisory rules** in MISRA C:2012

### 1.3 SIL Compliance Requirements

| SIL Level | Mandatory Rules | Required Rules | Advisory Rules | Deviation Process |
|-----------|-----------------|----------------|----------------|-------------------|
| **SIL 0** | Follow where practical | Follow where practical | Optional | Document if significant |
| **SIL 1** | Zero violations target | Comply or document | Follow best effort | Document deviations |
| **SIL 2** | **Zero violations** | Comply or document | Follow majority | Formal deviation register |
| **SIL 3** | **Zero violations** | Comply or document | Follow majority | Formal deviation with CCB approval |
| **SIL 4** | **Zero violations** | Comply or document | Follow majority | Formal deviation with CCB approval |

**EN 50128 Table A.12 Requirement**:
- **SIL 3-4**: Design and Coding Standards **MANDATORY** (M)
- **SIL 2**: Design and Coding Standards **Highly Recommended** (HR)
- **SIL 0-1**: Design and Coding Standards **Recommended** (R)

### 1.4 Key Mandatory Rules (Must Comply for SIL 3-4)

| Rule | Description | Impact | Check Method |
|------|-------------|--------|--------------|
| **Rule 1.3** | No undefined behavior | Critical | Static analysis |
| **Rule 2.1** | No unreachable code | Medium | Static analysis |
| **Rule 2.2** | No dead code | Medium | Static analysis + coverage |
| **Rule 8.1** | Types shall be explicitly specified | High | Compiler + static analysis |
| **Rule 9.1** | No uninitialized variables | Critical | Static analysis |
| **Rule 10.1** | Operands of inappropriate essential type | High | Static analysis |
| **Rule 14.3** | Controlling expressions not invariant | Medium | Static analysis |
| **Rule 17.7** | Return value shall be used | High | Static analysis |
| **Rule 21.3** | No malloc/calloc/realloc/free | Critical (SIL 2+) | Static analysis |
| **Rule 21.6** | stdio.h functions restricted | High | Static analysis |

### 1.5 Tool Support

**Static Analysis Tools** (EN 50128 Table A.19 - MANDATORY SIL 3-4):
- **Cppcheck** (with MISRA addon) - T1 confidence, free
- **PC-lint Plus** (Gimpel) - T2 confidence, commercial
- **Clang Static Analyzer** - T1 confidence, free
- **Polyspace** (MathWorks) - T2 confidence, commercial
- **LDRA Testbed** - T3 confidence (qualified), commercial

**MISRA C Compliance Check** (static analysis — use one of the qualified tools above):
```bash
# Cppcheck with MISRA C:2012 addon (T1/T2 confidence)
cppcheck --addon=misra --enable=all src/<module>.c 2> cppcheck_misra.txt

# Submit MISRA analysis report as a workflow artifact
python3 tools/workspace.py wf submit <DOC-MISRA-ID> \
    --path cppcheck_misra.txt \
    --author-role IMP \
    --author-name '<Name>' \
    --sil <level>
```
Note: `workflow-mgr verify-misra` does not exist in this platform.

---

## 2. Type Safety Patterns

### 2.1 Fixed-Width Integer Types (MANDATORY)

**Rule Reference**: MISRA C:2012 Directive 4.6 "typedefs that indicate size and signedness should be used"

**SIL Requirement**: **MANDATORY** for all SIL levels

**Pattern**:
```c
#include <stdint.h>  /* Fixed-width types */

/* MISRA VIOLATION: Native types (implementation-defined size) */
int speed;              /* 16 or 32 bits? */
unsigned int counter;   /* 16 or 32 bits? */
char buffer[100];       /* Signed or unsigned? */
long timestamp;         /* 32 or 64 bits? */

/* MISRA COMPLIANT: Fixed-width types (defined size) */
int32_t speed;          /* Always 32 bits, signed */
uint32_t counter;       /* Always 32 bits, unsigned */
uint8_t buffer[100];    /* Always 8 bits per element, unsigned */
int64_t timestamp;      /* Always 64 bits, signed */
```

**Rationale**:
- **Portability**: Fixed-width types have same size across all platforms
- **Predictability**: No surprises when moving from 16-bit to 32-bit microcontroller
- **Safety**: Prevents integer overflow due to unexpected type size

**Exceptions**:
- `size_t` for array indices and sizes (standard library convention)
- `bool` from `<stdbool.h>` for boolean values
- Function return types may use `int` if part of standard API

**Complete Type Set**:
```c
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Signed integers */
int8_t   i8;    /* -128 to 127 */
int16_t  i16;   /* -32768 to 32767 */
int32_t  i32;   /* -2147483648 to 2147483647 */
int64_t  i64;   /* -9223372036854775808 to 9223372036854775807 */

/* Unsigned integers */
uint8_t  u8;    /* 0 to 255 */
uint16_t u16;   /* 0 to 65535 */
uint32_t u32;   /* 0 to 4294967295 */
uint64_t u64;   /* 0 to 18446744073709551615 */

/* Boolean */
bool flag;      /* true or false */

/* Size and pointer difference */
size_t size;    /* Result of sizeof, array sizes */
ptrdiff_t diff; /* Pointer difference */
```

### 2.2 Boolean Type (MANDATORY)

**Rule Reference**: MISRA C:2012 Rule 14.4 "controlling expression of if/while/for/do shall have boolean essential type"

**Pattern**:
```c
#include <stdbool.h>  /* C99 boolean type */

/* MISRA VIOLATION: Integer used as boolean */
int is_active;
if (is_active) {  /* Rule 14.4 violation - integer, not boolean */
    /* ... */
}

/* MISRA COMPLIANT: Boolean type */
bool is_active;
if (is_active == true) {  /* Explicit boolean comparison */
    /* ... */
}
```

**Pre-C99 Pattern** (C89/C90):
```c
/* For C89 projects */
typedef enum {
    false = 0,
    true = 1
} bool;

bool is_valid = false;
```

**Comparison Patterns**:
```c
/* GOOD: Explicit boolean expressions */
if (value == 0)         { /* Numeric comparison */ }
if (ptr != NULL)        { /* Pointer comparison */ }
if (state == STATE_IDLE){ /* Enum comparison */ }
if (flag == true)       { /* Boolean comparison */ }

/* AVOID: Implicit conversion to boolean (MISRA Rule 14.4) */
if (value)   { /* Violation */ }
if (ptr)     { /* Violation */ }
if (!ptr)    { /* Violation */ }
```

### 2.3 Enumerated Types

**Rule Reference**: MISRA C:2012 Rule 10.4 "Essential type of operand"

**Pattern**:
```c
/* GOOD: Enum for state machine */
typedef enum {
    STATE_INIT = 0,
    STATE_IDLE = 1,
    STATE_RUNNING = 2,
    STATE_STOPPED = 3,
    STATE_ERROR = 4,
    STATE_MAX       /* Sentinel for bounds checking */
} system_state_t;

/* GOOD: Enum for error codes */
typedef enum {
    ERROR_NONE = 0,
    ERROR_NULL_POINTER = 1,
    ERROR_OUT_OF_RANGE = 2,
    ERROR_TIMEOUT = 3,
    ERROR_HARDWARE_FAULT = 4
} error_code_t;

/* Usage with bounds checking */
system_state_t current_state = STATE_INIT;

error_t set_state(system_state_t new_state) {
    /* Defensive check: validate enum range */
    if ((new_state < STATE_INIT) || (new_state >= STATE_MAX)) {
        return ERROR_OUT_OF_RANGE;
    }
    current_state = new_state;
    return ERROR_NONE;
}
```

**Switch with Enum** (MISRA Rule 16.4 - every switch must have default):
```c
/* MISRA COMPLIANT: Switch on enum with default */
switch (current_state) {
    case STATE_INIT:
        /* Handle init */
        break;
    case STATE_IDLE:
        /* Handle idle */
        break;
    case STATE_RUNNING:
        /* Handle running */
        break;
    case STATE_STOPPED:
        /* Handle stopped */
        break;
    case STATE_ERROR:
        /* Handle error */
        break;
    default:
        /* Defensive: should never reach here */
        log_error("Invalid state");
        current_state = STATE_ERROR;
        break;
}
```

### 2.4 Type Conversions and Casts

**Rule Reference**: MISRA C:2012 Rules 10.1-10.8 (implicit conversions, casts)

**Pattern 1: Explicit Casts (Required)**
```c
/* MISRA VIOLATION: Implicit conversion */
uint16_t u16_val = 1000;
uint8_t u8_val = u16_val;  /* Rule 10.3 violation - narrowing */

/* MISRA COMPLIANT: Explicit cast with range check */
uint16_t u16_val = 1000;
uint8_t u8_val;
if (u16_val <= 255U) {
    u8_val = (uint8_t)u16_val;  /* Explicit cast, range verified */
} else {
    u8_val = 255U;  /* Saturate */
}
```

**Pattern 2: Avoid Mixed Sign Operations**
```c
/* MISRA VIOLATION: Mixed signed/unsigned (Rule 10.4) */
int32_t signed_val = -100;
uint32_t unsigned_val = 200U;
int32_t result = signed_val + unsigned_val;  /* Violation */

/* MISRA COMPLIANT: Cast to common type */
int32_t signed_val = -100;
uint32_t unsigned_val = 200U;
int32_t result;

if (unsigned_val <= (uint32_t)INT32_MAX) {
    result = signed_val + (int32_t)unsigned_val;  /* Safe cast */
} else {
    /* Handle overflow */
    result = INT32_MAX;
}
```

**Pattern 3: Pointer Casts (Highly Restricted)**
```c
/* MISRA VIOLATION: Pointer cast without justification */
uint32_t* p_u32 = (uint32_t*)0x40000000;  /* Rule 11.4 violation */

/* MISRA COMPLIANT: Pointer cast with comment and volatile */
/* Deviation: Rule 11.4 - Memory-mapped hardware register */
volatile uint32_t* p_control_reg = (volatile uint32_t*)0x40000000UL;
```

### 2.5 Floating-Point Types (Avoid if Possible)

**Rule Reference**: MISRA C:2012 Directive 1.1 "Implementation-defined behavior documented"

**Recommendation**: **Avoid floating-point for SIL 3-4** (non-deterministic)

**If Required - Document Fully**:
```c
/* AVOID: Floating-point in safety-critical code */
float gain = 1.5f;
float output = input * gain;

/* PREFER: Fixed-point arithmetic (deterministic) */
int32_t gain = 150;  /* Represents 1.50 scaled by 100 */
int32_t output = (input * gain) / 100;
```

**If Floating-Point Unavoidable**:
```c
#include <math.h>
#include <float.h>

/* Document rounding mode, precision, exception handling */
double calculate_position(double velocity, double time) {
    double result = velocity * time;
    
    /* Defensive check: verify result is finite */
    if (!isfinite(result)) {
        log_error("Non-finite result");
        return 0.0;
    }
    
    return result;
}
```

---

## 3. Pointer and Array Patterns

### 3.1 NULL Pointer Check (MANDATORY)

**Rule Reference**: MISRA C:2012 Rule 1.3 "No undefined behavior", Rule 17.7 "Return value checked"

**SIL Requirement**: **MANDATORY** for all SIL levels

**Pattern**:
```c
/* MISRA COMPLIANT: Check all pointer parameters */
error_t process_data(const sensor_data_t* input, output_data_t* output) {
    /* NULL pointer checks (MANDATORY) */
    if (input == NULL) {
        return ERROR_NULL_POINTER;
    }
    if (output == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    /* Safe to use pointers */
    output->value = input->value * 2;
    return ERROR_NONE;
}
```

**Caller Responsibility**:
```c
/* Caller must check return value (Rule 17.7) */
error_t err;
sensor_data_t sensor;
output_data_t output;

err = process_data(&sensor, &output);
if (err != ERROR_NONE) {  /* MANDATORY: Check return value */
    /* Handle error */
    return err;
}
```

### 3.2 Array Bounds Checking (MANDATORY)

**Rule Reference**: MISRA C:2012 Rule 18.1 "Pointer arithmetic shall not produce out-of-bounds pointer"

**Pattern**:
```c
#define BUFFER_SIZE 100U

/* MISRA VIOLATION: No bounds check */
void unsafe_write(uint8_t* buffer, uint32_t index, uint8_t value) {
    buffer[index] = value;  /* Rule 18.1 violation if index >= BUFFER_SIZE */
}

/* MISRA COMPLIANT: Bounds check before access */
error_t safe_write(uint8_t* buffer, uint32_t buffer_size, 
                   uint32_t index, uint8_t value) {
    if (buffer == NULL) {
        return ERROR_NULL_POINTER;
    }
    if (index >= buffer_size) {
        return ERROR_OUT_OF_RANGE;
    }
    
    buffer[index] = value;  /* Safe: bounds verified */
    return ERROR_NONE;
}

/* Usage */
uint8_t buffer[BUFFER_SIZE];
error_t err = safe_write(buffer, BUFFER_SIZE, 50U, 0xAB);
if (err != ERROR_NONE) {
    /* Handle error */
}
```

### 3.3 Pointer Arithmetic (Restricted)

**Rule Reference**: MISRA C:2012 Rule 18.4 "Pointer arithmetic other than array indexing shall not be used"

**Pattern**:
```c
/* MISRA VIOLATION: Pointer arithmetic */
uint8_t* p = buffer;
p = p + 10;  /* Rule 18.4 violation */
*p = 0xFF;

/* MISRA COMPLIANT: Array indexing */
uint32_t index = 10U;
if (index < BUFFER_SIZE) {
    buffer[index] = 0xFF;  /* Array indexing preferred */
}
```

**Exception - Iteration** (Acceptable with justification):
```c
/* Deviation: Rule 18.4 - Pointer iteration for performance */
void clear_buffer(uint8_t* buffer, uint32_t size) {
    uint8_t* p = buffer;
    uint8_t* p_end = buffer + size;  /* End pointer */
    
    /* Pointer iteration (faster than indexing on some platforms) */
    while (p < p_end) {
        *p = 0U;
        p++;  /* Pointer arithmetic - deviation documented */
    }
}
```

### 3.4 Function Pointers (Avoid for SIL 3-4)

**Rule Reference**: MISRA C:2012 Rule 11.1 "Conversions between function pointer and other types"

**Recommendation**: **Highly avoid** function pointers for SIL 3-4 (reduces analyzability)

**If Required - Strict Pattern**:
```c
/* Function pointer type definition */
typedef error_t (*command_handler_t)(uint8_t param);

/* Function pointer table with validation */
#define MAX_COMMANDS 10U

static command_handler_t command_table[MAX_COMMANDS] = {
    &cmd_start,
    &cmd_stop,
    &cmd_reset,
    /* Initialize all entries */
};

/* Safe function pointer call with validation */
error_t execute_command(uint8_t cmd_id, uint8_t param) {
    /* Bounds check */
    if (cmd_id >= MAX_COMMANDS) {
        return ERROR_OUT_OF_RANGE;
    }
    
    /* NULL check (defensive) */
    if (command_table[cmd_id] == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    /* Call through function pointer */
    return command_table[cmd_id](param);
}
```

### 3.5 Const Correctness (MANDATORY)

**Rule Reference**: MISRA C:2012 Rule 11.8 "Cast shall not remove const or volatile qualification"

**Pattern**:
```c
/* MISRA VIOLATION: Removing const */
void bad_function(const uint8_t* input) {
    uint8_t* p = (uint8_t*)input;  /* Rule 11.8 violation */
    *p = 0xFF;  /* Modifying const data! */
}

/* MISRA COMPLIANT: Respect const */
void good_function(const uint8_t* input, uint8_t* output) {
    *output = *input;  /* Read from const, write to non-const */
}

/* const pointer vs pointer to const */
const uint8_t* p1;        /* Pointer to const data (data immutable) */
uint8_t* const p2 = &var; /* Const pointer (pointer immutable) */
const uint8_t* const p3 = &var; /* Both immutable */
```

---

## 4. Control Flow Patterns

### 4.1 No goto (MANDATORY)

**Rule Reference**: MISRA C:2012 Rule 15.1 "goto statement shall not be used"

**SIL Requirement**: **MANDATORY** for SIL 3-4

**Pattern**:
```c
/* MISRA VIOLATION: Using goto */
error_t bad_function(void) {
    if (condition1) goto error;
    if (condition2) goto error;
    return ERROR_NONE;
    
error:
    return ERROR_FAILURE;
}

/* MISRA COMPLIANT: Structured early returns */
error_t good_function(void) {
    if (condition1) {
        return ERROR_FAILURE;
    }
    if (condition2) {
        return ERROR_FAILURE;
    }
    return ERROR_NONE;
}
```

**Exception - Resource Cleanup** (Use structured pattern instead):
```c
/* PREFER: Structured cleanup (no goto) */
error_t process_with_cleanup(void) {
    error_t result = ERROR_NONE;
    bool resource_allocated = false;
    
    /* Allocate resource */
    result = allocate_resource();
    if (result != ERROR_NONE) {
        return result;  /* Early return (no cleanup needed) */
    }
    resource_allocated = true;
    
    /* Process */
    result = do_processing();
    
    /* Cleanup (always executed) */
    if (resource_allocated) {
        release_resource();
    }
    
    return result;
}
```

### 4.2 Switch Statement with Default (MANDATORY)

**Rule Reference**: MISRA C:2012 Rule 16.4 "Every switch shall have default case", Rule 16.3 "No fallthrough"

**Pattern**:
```c
/* MISRA COMPLIANT: Switch with default and no fallthrough */
switch (state) {
    case STATE_IDLE:
        handle_idle();
        break;  /* MANDATORY: break for each case */
        
    case STATE_RUNNING:
        handle_running();
        break;
        
    case STATE_STOPPED:
        handle_stopped();
        break;
        
    default:  /* MANDATORY: default case */
        /* Defensive: invalid state */
        log_error("Invalid state");
        state = STATE_ERROR;
        break;
}
```

**Intentional Fallthrough** (Requires comment per Rule 16.3):
```c
/* Deviation: Rule 16.3 - Intentional fallthrough with comment */
switch (command) {
    case CMD_EMERGENCY_STOP:
        emergency_flag = true;
        /* FALLTHROUGH - intentional */  /* Required comment */
        
    case CMD_NORMAL_STOP:
        stop_motor();
        break;
        
    default:
        break;
}
```

### 4.3 No Infinite Loops Without Break (MANDATORY)

**Rule Reference**: MISRA C:2012 Rule 14.4 "Controlling expression shall not be invariant"

**Pattern**:
```c
/* MISRA VIOLATION: Infinite loop without break */
void bad_main_loop(void) {
    while (1) {  /* Rule 14.4 violation - invariant condition */
        process_tasks();
    }
}

/* MISRA COMPLIANT: Loop with break condition */
void good_main_loop(void) {
    bool running = true;
    
    while (running == true) {  /* Non-invariant condition */
        process_tasks();
        
        if (shutdown_requested == true) {
            running = false;  /* Break condition */
        }
    }
}
```

**Alternative - Bounded Loop**:
```c
/* MISRA COMPLIANT: Bounded loop (finite iterations) */
#define MAX_ITERATIONS 10000U

void bounded_main_loop(void) {
    uint32_t iteration = 0U;
    
    while (iteration < MAX_ITERATIONS) {
        process_tasks();
        iteration++;
        
        if (shutdown_requested == true) {
            break;  /* Early exit allowed */
        }
    }
}
```

### 4.4 Single Entry/Exit (Recommended, Not Mandatory)

**EN 50128 Guidance**: Structured programming (Table A.4 Technique 8 - MANDATORY SIL 3-4)

**Pattern 1: Single Exit** (Traditional):
```c
error_t single_exit_function(uint32_t param) {
    error_t result = ERROR_NONE;
    
    if (param == 0U) {
        result = ERROR_INVALID_PARAMETER;
    } else if (param > MAX_VALUE) {
        result = ERROR_OUT_OF_RANGE;
    } else {
        result = process(param);
    }
    
    return result;  /* Single exit point */
}
```

**Pattern 2: Early Returns for Guards** (Acceptable for EN 50128):
```c
/* Early returns for precondition checks (defensive programming) */
error_t early_return_function(const data_t* input, output_t* output) {
    /* Guard clauses - early returns acceptable */
    if (input == NULL) {
        return ERROR_NULL_POINTER;
    }
    if (output == NULL) {
        return ERROR_NULL_POINTER;
    }
    if (input->value > MAX_INPUT) {
        return ERROR_OUT_OF_RANGE;
    }
    
    /* Main logic */
    output->result = process_input(input);
    return ERROR_NONE;  /* Single normal exit */
}
```

### 4.5 No Recursion (Highly Recommended SIL 3-4)

**Rule Reference**: MISRA C:2012 Rule 17.2 "Functions shall not call themselves, directly or indirectly"

**SIL Requirement**: **Highly Recommended** SIL 3-4 (avoid recursion for stack predictability)

**Pattern**:
```c
/* MISRA VIOLATION: Recursive function (Rule 17.2) */
uint32_t factorial_recursive(uint32_t n) {
    if (n <= 1U) {
        return 1U;
    }
    return n * factorial_recursive(n - 1U);  /* Recursion */
}

/* MISRA COMPLIANT: Iterative replacement */
uint32_t factorial_iterative(uint32_t n) {
    uint32_t result = 1U;
    uint32_t i;
    
    for (i = 2U; i <= n; i++) {
        /* Check overflow before multiplication */
        if (result > (UINT32_MAX / i)) {
            return 0U;  /* Overflow error */
        }
        result = result * i;
    }
    
    return result;
}
```

---

## 5. Function Patterns

### 5.1 Function Prototype Mandatory (MANDATORY)

**Rule Reference**: MISRA C:2012 Rule 8.1 "Types shall be explicitly specified", Rule 8.2 "Function types shall be in prototype form"

**Pattern**:
```c
/* MISRA VIOLATION: No prototype */
calculate(x, y) {  /* Rule 8.1, 8.2 violation */
    return x + y;
}

/* MISRA COMPLIANT: Full prototype in header */
/* sensor.h */
int32_t sensor_read(uint8_t channel);

/* sensor.c */
int32_t sensor_read(uint8_t channel) {
    /* Implementation */
    return 0;
}
```

### 5.2 Return Value Checked (MANDATORY)

**Rule Reference**: MISRA C:2012 Rule 17.7 "Return value shall not be ignored"

**SIL Requirement**: **MANDATORY** for all SIL levels

**Pattern**:
```c
/* MISRA VIOLATION: Ignoring return value */
void bad_caller(void) {
    sensor_read(CHANNEL_1);  /* Rule 17.7 violation - return ignored */
}

/* MISRA COMPLIANT: Check return value */
void good_caller(void) {
    error_t err;
    int32_t value;
    
    err = sensor_read(CHANNEL_1, &value);
    if (err != ERROR_NONE) {  /* MANDATORY: Check return */
        handle_error(err);
    }
}
```

**Exception - void Functions**:
```c
/* void functions have no return to check */
void log_message(const char* message) {
    /* Implementation */
    (void)message;  /* Cast to void if parameter unused (Rule 2.7) */
}

/* Caller */
log_message("System started");  /* No return to check */
```

### 5.3 Function Parameter Limit (Recommended)

**Guideline**: Maximum **5 parameters** per function (complexity management)

**Pattern**:
```c
/* BAD: Too many parameters (reduces readability) */
error_t configure_module(uint8_t mode, uint8_t priority, uint8_t timeout,
                         uint8_t retry, uint8_t channel, uint8_t flags,
                         uint8_t buffer_size);  /* 7 parameters */

/* GOOD: Use structure for related parameters */
typedef struct {
    uint8_t mode;
    uint8_t priority;
    uint8_t timeout;
    uint8_t retry;
    uint8_t channel;
    uint8_t flags;
    uint8_t buffer_size;
} module_config_t;

error_t configure_module(const module_config_t* config);  /* 1 parameter */
```

### 5.4 No Variable-Argument Functions (Restricted)

**Rule Reference**: MISRA C:2012 Rule 17.1 "Features of <stdarg.h> shall not be used"

**Pattern**:
```c
/* MISRA VIOLATION: Variable arguments */
#include <stdarg.h>
void log_printf(const char* format, ...) {  /* Rule 17.1 violation */
    va_list args;
    va_start(args, format);
    /* ... */
    va_end(args);
}

/* MISRA COMPLIANT: Fixed parameters */
void log_message(log_level_t level, const char* message) {
    /* Implementation */
}

void log_with_value(log_level_t level, const char* message, int32_t value) {
    /* Implementation */
}
```

### 5.5 Function Size Limit (Recommended)

**Guideline**: Maximum **60 lines** per function (EN 50128 analyzability)

**Rationale**: Smaller functions are easier to:
- Understand
- Test (achieve 100% coverage)
- Verify (static analysis)
- Review (code review)

**Pattern**:
```c
/* BAD: Large function (100+ lines) */
error_t process_sensor_data(void) {
    /* 100+ lines of code */
}

/* GOOD: Decompose into smaller functions */
static error_t validate_sensor_input(const sensor_data_t* data);
static error_t filter_sensor_data(sensor_data_t* data);
static error_t scale_sensor_value(sensor_data_t* data);

error_t process_sensor_data(void) {
    error_t err;
    sensor_data_t data;
    
    err = read_sensor(&data);
    if (err != ERROR_NONE) return err;
    
    err = validate_sensor_input(&data);
    if (err != ERROR_NONE) return err;
    
    err = filter_sensor_data(&data);
    if (err != ERROR_NONE) return err;
    
    err = scale_sensor_value(&data);
    if (err != ERROR_NONE) return err;
    
    return ERROR_NONE;
}
```

---

## 6. Variable and Initialization Patterns

### 6.1 Initialize All Variables (MANDATORY)

**Rule Reference**: MISRA C:2012 Rule 9.1 "Value of automatic variable shall not be used before initialized"

**SIL Requirement**: **MANDATORY** for all SIL levels

**Pattern**:
```c
/* MISRA VIOLATION: Uninitialized variable */
void bad_function(void) {
    int32_t value;  /* Rule 9.1 violation - not initialized */
    if (condition) {
        value = 10;
    }
    use_value(value);  /* May be uninitialized if !condition */
}

/* MISRA COMPLIANT: Initialize at declaration */
void good_function(void) {
    int32_t value = 0;  /* Always initialized */
    if (condition) {
        value = 10;
    }
    use_value(value);  /* Safe: always initialized */
}
```

**Array Initialization**:
```c
/* MISRA COMPLIANT: Array initialization */
uint8_t buffer[100] = {0};  /* Initialize all elements to zero */

/* Partial initialization (rest zeroed) */
uint8_t status[10] = {1, 2, 3};  /* [1,2,3,0,0,0,0,0,0,0] */

/* Designated initializers (C99) */
typedef struct {
    uint8_t id;
    uint8_t status;
    uint16_t value;
} sensor_t;

sensor_t sensor = {
    .id = 1,
    .status = 0,
    .value = 0
};  /* Explicit field initialization */
```

### 6.2 Minimum Scope (MANDATORY)

**Rule Reference**: MISRA C:2012 Rule 8.7 "Functions/objects with internal linkage declared static"

**Pattern**:
```c
/* MISRA VIOLATION: Unnecessary external linkage */
/* module.c */
uint32_t internal_counter = 0;  /* Rule 8.7 violation - should be static */

void increment_counter(void) {
    internal_counter++;
}

/* MISRA COMPLIANT: Internal linkage (static) */
/* module.c */
static uint32_t internal_counter = 0;  /* File scope, not visible externally */

void increment_counter(void) {
    internal_counter++;
}
```

**Function Scope**:
```c
/* MISRA COMPLIANT: Static helper function */
/* module.c */
static error_t validate_input(uint32_t value) {  /* File scope only */
    if (value > MAX_VALUE) {
        return ERROR_OUT_OF_RANGE;
    }
    return ERROR_NONE;
}

/* Public function (external linkage) */
error_t process_input(uint32_t value) {
    error_t err = validate_input(value);
    /* ... */
    return err;
}
```

### 6.3 No extern in .c Files (Recommended)

**Rule Reference**: MISRA C:2012 Rule 8.6 "Identifier with external linkage shall have one definition"

**Pattern**:
```c
/* BAD: extern declaration in .c file */
/* module.c */
extern uint32_t global_counter;  /* Should be in header */

/* GOOD: extern in header, definition in one .c */
/* global.h */
extern uint32_t global_counter;  /* Declaration */

/* global.c */
uint32_t global_counter = 0;  /* Definition */

/* module.c */
#include "global.h"  /* Include header for extern declarations */
```

### 6.4 const for Read-Only Data (MANDATORY)

**Rule Reference**: MISRA C:2012 Rule 11.8 "No cast removing const"

**Pattern**:
```c
/* MISRA COMPLIANT: const for read-only data */
static const uint32_t LOOKUP_TABLE[10] = {
    0, 1, 4, 9, 16, 25, 36, 49, 64, 81
};

error_t get_square(uint8_t index, uint32_t* result) {
    if (index >= 10U) {
        return ERROR_OUT_OF_RANGE;
    }
    *result = LOOKUP_TABLE[index];  /* Read from const table */
    return ERROR_NONE;
}
```

**const Parameters**:
```c
/* Input-only parameters: const pointer */
void process(const sensor_data_t* input, output_data_t* output) {
    output->value = input->value * 2;  /* Read input, write output */
}
```

### 6.5 volatile for Hardware Registers (MANDATORY)

**Rule Reference**: MISRA C:2012 Directive 1.1 "Implementation-defined behavior documented"

**Pattern**:
```c
/* Hardware register address (platform-specific) */
#define CONTROL_REG_ADDR 0x40000000UL

/* MISRA COMPLIANT: volatile for hardware access */
/* Deviation: Rule 11.4 - Memory-mapped I/O requires pointer cast */
volatile uint32_t* const p_control_reg = 
    (volatile uint32_t*)CONTROL_REG_ADDR;

void write_control_register(uint32_t value) {
    *p_control_reg = value;  /* volatile ensures write not optimized away */
}

uint32_t read_status_register(void) {
    return *p_control_reg;  /* volatile ensures fresh read */
}
```

---

## 7. Arithmetic and Expression Patterns

### 7.1 Signed Overflow Detection (MANDATORY)

**Rule Reference**: MISRA C:2012 Rule 1.3 "No undefined behavior" (signed overflow is undefined)

**Pattern**:
```c
/* MISRA VIOLATION: No overflow check */
int32_t add_unsafe(int32_t a, int32_t b) {
    return a + b;  /* Undefined behavior if overflow */
}

/* MISRA COMPLIANT: Overflow detection before addition */
error_t add_safe(int32_t a, int32_t b, int32_t* result) {
    if (result == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    /* Check for positive overflow: a + b > INT32_MAX */
    if ((b > 0) && (a > (INT32_MAX - b))) {
        return ERROR_OVERFLOW;
    }
    
    /* Check for negative overflow: a + b < INT32_MIN */
    if ((b < 0) && (a < (INT32_MIN - b))) {
        return ERROR_UNDERFLOW;
    }
    
    *result = a + b;  /* Safe: overflow checked */
    return ERROR_NONE;
}
```

**Multiplication Overflow**:
```c
error_t multiply_safe(int32_t a, int32_t b, int32_t* result) {
    if (result == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    /* Special case: zero */
    if ((a == 0) || (b == 0)) {
        *result = 0;
        return ERROR_NONE;
    }
    
    /* Check overflow: |a * b| > INT32_MAX */
    if ((a > 0) && (b > 0)) {
        if (a > (INT32_MAX / b)) {
            return ERROR_OVERFLOW;
        }
    } else if ((a < 0) && (b < 0)) {
        if (a < (INT32_MAX / b)) {
            return ERROR_OVERFLOW;
        }
    } else {  /* One negative, one positive */
        if ((a < 0) && (a < (INT32_MIN / b))) {
            return ERROR_UNDERFLOW;
        }
        if ((b < 0) && (b < (INT32_MIN / a))) {
            return ERROR_UNDERFLOW;
        }
    }
    
    *result = a * b;  /* Safe */
    return ERROR_NONE;
}
```

### 7.2 Division by Zero Check (MANDATORY)

**Rule Reference**: MISRA C:2012 Rule 1.3 "No undefined behavior" (division by zero is undefined)

**Pattern**:
```c
/* MISRA VIOLATION: No zero check */
int32_t divide_unsafe(int32_t numerator, int32_t denominator) {
    return numerator / denominator;  /* Undefined if denominator == 0 */
}

/* MISRA COMPLIANT: Check denominator before division */
error_t divide_safe(int32_t numerator, int32_t denominator, int32_t* result) {
    if (result == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    if (denominator == 0) {
        return ERROR_DIVIDE_BY_ZERO;
    }
    
    *result = numerator / denominator;  /* Safe */
    return ERROR_NONE;
}
```

### 7.3 Shift Operator Restrictions (MANDATORY)

**Rule Reference**: MISRA C:2012 Rule 12.2 "Right-hand operand of shift operator shall be 0 to width-1"

**Pattern**:
```c
/* MISRA VIOLATION: No shift count validation */
uint32_t shift_left_unsafe(uint32_t value, uint32_t count) {
    return value << count;  /* Undefined if count >= 32 */
}

/* MISRA COMPLIANT: Validate shift count */
error_t shift_left_safe(uint32_t value, uint32_t count, uint32_t* result) {
    if (result == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    if (count >= 32U) {  /* uint32_t is 32 bits */
        return ERROR_OUT_OF_RANGE;
    }
    
    *result = value << count;  /* Safe: count < 32 */
    return ERROR_NONE;
}
```

**Right Shift on Signed** (Implementation-defined):
```c
/* AVOID: Right shift on signed (implementation-defined) */
int32_t value = -100;
int32_t shifted = value >> 2;  /* Arithmetic or logical shift? */

/* PREFER: Right shift on unsigned only */
uint32_t uvalue = 100U;
uint32_t ushifted = uvalue >> 2;  /* Always logical shift */
```

### 7.4 Bitwise Operations on Unsigned Only (MANDATORY)

**Rule Reference**: MISRA C:2012 Rule 12.1 "Precedence of operators explicit"

**Pattern**:
```c
/* MISRA VIOLATION: Bitwise on signed */
int32_t mask = 0xFF00;  /* Signed */
int32_t result = value & mask;  /* Avoid bitwise on signed */

/* MISRA COMPLIANT: Bitwise on unsigned */
uint32_t mask = 0xFF00U;  /* Unsigned */
uint32_t result = value & mask;  /* Bitwise on unsigned only */
```

### 7.5 Compound Expressions - Side Effects (MANDATORY)

**Rule Reference**: MISRA C:2012 Rule 13.1 "Assignment operators in subexpressions"

**Pattern**:
```c
/* MISRA VIOLATION: Side effect in expression */
if ((x = get_value()) > 10) {  /* Rule 13.1 violation */
    /* ... */
}

/* MISRA COMPLIANT: Separate assignment and evaluation */
x = get_value();
if (x > 10) {
    /* ... */
}
```

**Increment/Decrement**:
```c
/* MISRA VIOLATION: Side effect in expression */
array[i++] = value;  /* Rule 13.3 violation */

/* MISRA COMPLIANT: Separate increment */
array[i] = value;
i++;
```

---

## 8. Preprocessor Patterns

### 8.1 Header Guard Pattern (MANDATORY)

**Rule Reference**: MISRA C:2012 Directive 4.10 "Precautions taken against multiple inclusion"

**Pattern**:
```c
/* module.h */
#ifndef MODULE_H
#define MODULE_H

/* Header contents */

#endif  /* MODULE_H */
```

**Naming Convention**:
```c
/* Format: <MODULE>_H */
/* sensor_manager.h */
#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

/* ... */

#endif  /* SENSOR_MANAGER_H */
```

### 8.2 Macro vs Inline Function (Prefer Inline for SIL 2+)

**Rule Reference**: MISRA C:2012 Directive 4.9 "Function-like macro could be replaced by function"

**Pattern**:
```c
/* AVOID: Function-like macro (hard to debug) */
#define MAX(a, b) ((a) > (b) ? (a) : (b))  /* Directive 4.9 */

/* PREFER: Inline function (type-safe, debuggable) */
static inline int32_t max_int32(int32_t a, int32_t b) {
    return (a > b) ? a : b;
}
```

**Exception - Simple Constants**:
```c
/* OK: Macro for constants */
#define MAX_SENSORS 10U
#define TIMEOUT_MS 1000U
```

### 8.3 #define for Constants vs const (Prefer const)

**Pattern**:
```c
/* AVOID: Macro constants (no type safety) */
#define BUFFER_SIZE 100
#define TIMEOUT 1000

/* PREFER: const variables (type-safe) */
static const uint32_t BUFFER_SIZE = 100U;
static const uint32_t TIMEOUT_MS = 1000U;
```

### 8.4 No #undef (MANDATORY)

**Rule Reference**: MISRA C:2012 Rule 20.5 "#undef shall not be used"

**Pattern**:
```c
/* MISRA VIOLATION: Using #undef */
#define TEMP_VALUE 100
/* ... */
#undef TEMP_VALUE  /* Rule 20.5 violation */

/* MISRA COMPLIANT: Avoid #undef, use scoped names */
#define MODULE_A_TEMP_VALUE 100  /* Unique name, no #undef needed */
```

### 8.5 Conditional Compilation (Minimize)

**Rule Reference**: MISRA C:2012 Directive 4.4 "Sections of code commented out"

**Pattern**:
```c
/* AVOID: Excessive conditional compilation */
#ifdef FEATURE_A
    code_a();
#endif
#ifdef FEATURE_B
    code_b();
#endif

/* PREFER: Configuration structure with runtime selection */
static const module_config_t config = {
    .feature_a_enabled = true,
    .feature_b_enabled = false
};

if (config.feature_a_enabled == true) {
    code_a();
}
```

---

## 9. Standard Library Usage Patterns

### 9.1 Forbidden Functions (MANDATORY SIL 2+)

**Rule Reference**: MISRA C:2012 Rules 21.x

| Function | Rule | Reason | SIL Level |
|----------|------|--------|-----------|
| `malloc`, `calloc`, `realloc`, `free` | 21.3 | Dynamic allocation forbidden | **SIL 2+** |
| `atoi`, `atof`, `atol` | 21.7 | No error indication | All |
| `system` | 21.8 | Invokes external program | All |
| `abort`, `exit`, `getenv` | 21.10 | Non-deterministic | All |
| `signal`, `raise` | 21.9 | Signal handling non-deterministic | All |
| `setjmp`, `longjmp` | 21.12 | Non-local jumps | All |

### 9.2 Allowed Standard Library Functions

**Safe String/Memory Functions**:
```c
#include <string.h>

/* OK: Memory operations */
memcpy(dest, src, size);   /* OK with bounds check */
memset(buffer, 0, size);   /* OK */
memmove(dest, src, size);  /* OK (handles overlap) */
memcmp(a, b, size);        /* OK */

/* OK: String length */
size_t len = strlen(str);  /* OK with null-terminated string */

/* AVOID: Unsafe string functions */
strcpy(dest, src);   /* Use strncpy or snprintf instead */
strcat(dest, src);   /* Use strncat or snprintf instead */
```

**Safe Alternatives**:
```c
/* PREFER: Bounded string copy */
#include <stdio.h>  /* For snprintf */

/* Safe string copy with bounds check */
error_t safe_string_copy(char* dest, const char* src, size_t dest_size) {
    if ((dest == NULL) || (src == NULL)) {
        return ERROR_NULL_POINTER;
    }
    if (dest_size == 0U) {
        return ERROR_INVALID_PARAMETER;
    }
    
    /* Use snprintf for bounded copy */
    int ret = snprintf(dest, dest_size, "%s", src);
    if ((ret < 0) || ((size_t)ret >= dest_size)) {
        return ERROR_BUFFER_OVERFLOW;
    }
    
    return ERROR_NONE;
}
```

### 9.3 No stdio.h Functions (Restricted)

**Rule Reference**: MISRA C:2012 Rule 21.6 "stdio.h input/output functions restricted"

**Pattern**:
```c
/* FORBIDDEN: Standard I/O */
#include <stdio.h>
printf("Value: %d\n", value);  /* Rule 21.6 violation */
scanf("%d", &value);           /* Rule 21.6 violation */
fopen("file.txt", "r");        /* Rule 21.6 violation */

/* EXCEPTION: snprintf/vsnprintf allowed for string formatting */
char buffer[100];
int ret = snprintf(buffer, sizeof(buffer), "Speed: %d", speed);
if (ret < 0) {
    /* Error */
}
```

**Logging Alternative**:
```c
/* Custom logging function (not using stdio) */
typedef enum {
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO
} log_level_t;

void log_message(log_level_t level, const char* message);
void log_with_value(log_level_t level, const char* message, int32_t value);
```

---

## 10. Header File Patterns

### 10.1 Include Guard Pattern (MANDATORY)

**Rule Reference**: MISRA C:2012 Directive 4.10 "Multiple inclusion protection"

**Complete Header Template**:
```c
/* sensor_manager.h */
#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

/* Include dependencies */
#include <stdint.h>
#include <stdbool.h>
#include "error_codes.h"

/* Public constants */
#define SENSOR_MAX_CHANNELS 10U

/* Public types */
typedef struct {
    uint8_t channel;
    uint16_t value;
    bool valid;
} sensor_reading_t;

/* Public function declarations (prototypes only) */
error_t sensor_init(void);
error_t sensor_read(uint8_t channel, sensor_reading_t* reading);
void sensor_shutdown(void);

#endif  /* SENSOR_MANAGER_H */
```

### 10.2 No Function Definitions in Headers (MANDATORY)

**Rule Reference**: MISRA C:2012 Rule 8.5 "External object/function declared once"

**Pattern**:
```c
/* BAD: Function definition in header */
/* module.h */
inline uint32_t add(uint32_t a, uint32_t b) {  /* Violation */
    return a + b;
}

/* GOOD: Only declaration in header, definition in .c */
/* module.h */
uint32_t add(uint32_t a, uint32_t b);  /* Declaration */

/* module.c */
uint32_t add(uint32_t a, uint32_t b) {  /* Definition */
    return a + b;
}
```

**Exception - static inline**:
```c
/* OK: static inline in header (treated as macro-like) */
/* utils.h */
static inline uint32_t min_uint32(uint32_t a, uint32_t b) {
    return (a < b) ? a : b;
}
```

### 10.3 No Variable Definitions in Headers (MANDATORY)

**Pattern**:
```c
/* BAD: Variable definition in header */
/* global.h */
uint32_t global_counter = 0;  /* Definition - multiple definition error! */

/* GOOD: Declaration in header, definition in ONE .c */
/* global.h */
extern uint32_t global_counter;  /* Declaration only */

/* global.c */
uint32_t global_counter = 0;  /* Definition (one place only) */
```

### 10.4 Include Order Convention

**Recommended Order**:
```c
/* module.c */

/* 1. Own header */
#include "module.h"

/* 2. System headers */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* 3. Project headers */
#include "error_codes.h"
#include "sensor_manager.h"
#include "utils.h"
```

### 10.5 Minimal Includes (Reduce Coupling)

**Pattern**:
```c
/* AVOID: Including unnecessary headers */
/* module.h */
#include "everything.h"  /* Bad - exposes too much */

/* PREFER: Forward declarations when possible */
/* module.h */
typedef struct sensor_data_t sensor_data_t;  /* Forward declaration */

error_t process_sensor(const sensor_data_t* data);  /* Pointer only, no definition needed */

/* module.c includes full definition */
#include "sensor_types.h"  /* Full struct definition */
```

---

## 11. MISRA C Deviation Process

### 11.1 When Deviations Are Acceptable

**Acceptable Reasons**:
1. **Hardware access**: Memory-mapped I/O requires pointer casts (Rule 11.4)
2. **Performance**: Pointer iteration faster than array indexing on some platforms (Rule 18.4)
3. **Legacy interface**: Interfacing with non-MISRA compliant code
4. **Toolchain limitation**: Compiler does not support MISRA-compliant alternative

**Unacceptable Reasons**:
- "Too difficult to comply"
- "Deadline pressure"
- "Code works fine"
- "Personal preference"

### 11.2 Deviation Documentation Template

**Inline Deviation Comment**:
```c
/* Deviation: MISRA C:2012 Rule 11.4
 * Rationale: Memory-mapped hardware register access requires pointer cast
 * Approved by: [Name], [Date]
 * Safety argument: Address verified in hardware specification (section 4.2.1)
 */
volatile uint32_t* const p_ctrl_reg = (volatile uint32_t*)0x40000000UL;
```

**Deviation Register Entry**:
```markdown
## Deviation Record: DEV-2024-003

**Rule**: MISRA C:2012 Rule 11.4 - Pointer cast

**Location**: `hardware_abstraction.c:45`

**Code**:
```c
volatile uint32_t* const p_ctrl_reg = (volatile uint32_t*)0x40000000UL;
```

**Rationale**: Memory-mapped I/O register access for control register. Hardware specification (Doc ID: HW-SPEC-001, Section 4.2.1) defines control register at fixed address 0x4000_0000.

**Safety Argument**: 
- Address is constant (not computed)
- volatile qualifier prevents optimization
- const pointer prevents reassignment
- Access tested in hardware integration tests (Test ID: HW-INT-005)

**Alternative Considered**: None - hardware requires direct memory access

**Approved by**: John Doe (Verifier), 2024-03-10

**Review**: Approved by CCB, 2024-03-12
```

### 11.3 Tool Suppression with Justification

**Cppcheck Inline Suppression**:
```c
/* cppcheck-suppress misra-c2012-11.4 */
/* Deviation: Rule 11.4 - Hardware register access */
volatile uint32_t* const p_status = (volatile uint32_t*)0x40000004UL;
```

**PC-lint Plus Suppression**:
```c
/*lint -e{9005} MISRA Rule 11.4 - Hardware register access */
volatile uint32_t* const p_control = (volatile uint32_t*)0x40000000UL;
```

### 11.4 Deviation Review and Approval Process

**Process Steps** (SIL 3-4):
1. **Developer**: Document deviation inline + register entry
2. **Peer Review**: Verify technical rationale
3. **QUA Review**: Check deviation justification adequate
4. **VER Review**: Verify safety argument (independent team SIL 3-4)
5. **CCB Approval**: Change Control Board approves deviation
6. **Traceability**: Link deviation to requirement, test, verification report

**Deviation Registration**:

No dedicated `register-deviation` subcommand exists in this platform.
Document the deviation in a Deviation Log file and submit it via the workflow:
```bash
# Submit deviation log as a versioned workflow artifact
python3 tools/workspace.py wf submit <DOC-DEVIATION-ID> \
    --path deviations/<module>_misra_deviations.md \
    --author-role IMP \
    --author-name '<Name>' \
    --sil <level>
```
The Deviation Log must include: rule number, file, line, rationale, risk assessment,
compensating measures, and approver name — all items that `register-deviation` was
intended to capture.

### 11.5 Example Deviations by Category

**Category 1: Hardware Access (Common)**
```c
/* Deviation: Rule 11.4 - Memory-mapped I/O */
volatile uint32_t* const GPIO_PORTA = (volatile uint32_t*)0x40010000UL;
```

**Category 2: Performance (Rare, Justify with Profiling Data)**
```c
/* Deviation: Rule 18.4 - Pointer iteration for performance
 * Profiling data: 20% faster than array indexing (see PERF-001)
 * Safety: Loop bounds verified, no out-of-bounds access possible
 */
uint8_t* p = buffer;
uint8_t* p_end = buffer + size;
while (p < p_end) {
    *p++ = 0U;
}
```

**Category 3: Standard Library (Justified for SIL 0-1 only)**
```c
/* Deviation: Rule 21.3 - Dynamic allocation (SIL 0 project only)
 * Rationale: Non-safety-critical application, dynamic allocation acceptable
 */
uint8_t* buffer = malloc(size);
if (buffer == NULL) {
    return ERROR_OUT_OF_MEMORY;
}
```

---

## 12. Quick Reference Card

### 12.1 Top 20 MISRA C Violations and Fixes

| # | Violation | Rule | Fix |
|---|-----------|------|-----|
| 1 | Uninitialized variable | 9.1 | Initialize at declaration |
| 2 | Ignoring return value | 17.7 | Check all function returns |
| 3 | No NULL pointer check | 1.3 | Check all pointers before use |
| 4 | Using malloc/free | 21.3 | Use static allocation (SIL 2+) |
| 5 | Implicit type conversion | 10.1 | Use explicit casts |
| 6 | Native types (int, long) | D.4.6 | Use fixed-width (uint32_t) |
| 7 | No switch default | 16.4 | Add default case to all switches |
| 8 | Using goto | 15.1 | Use structured returns |
| 9 | No array bounds check | 18.1 | Validate index before access |
| 10 | Function-like macro | D.4.9 | Use inline function |
| 11 | No header guard | D.4.10 | Add #ifndef/#define/#endif |
| 12 | Unreachable code | 2.1 | Remove or fix condition |
| 13 | Dead code | 2.2 | Remove unused code |
| 14 | Shift count out of range | 12.2 | Validate shift count < width |
| 15 | Division by zero | 1.3 | Check denominator != 0 |
| 16 | Signed overflow | 1.3 | Check before arithmetic |
| 17 | Recursion | 17.2 | Convert to iterative (SIL 3-4) |
| 18 | Mixed signed/unsigned | 10.4 | Cast to common type |
| 19 | Pointer arithmetic | 18.4 | Use array indexing |
| 20 | Variable shadowing | 5.3 | Use unique names |

### 12.2 MISRA C Compliance Checklist (20 Items)

**Type System**:
- [ ] All integer types are fixed-width (`uint32_t`, not `int`)
- [ ] Boolean type is `bool` from `<stdbool.h>`
- [ ] Enums have explicit values and bounds checking
- [ ] All casts are explicit with range verification

**Pointers and Arrays**:
- [ ] All pointers checked for NULL before use
- [ ] All array accesses bounds-checked
- [ ] No pointer arithmetic except documented deviations
- [ ] const used for read-only pointers

**Control Flow**:
- [ ] No goto statements
- [ ] All switch statements have default case
- [ ] No infinite loops without break condition
- [ ] No recursion (SIL 3-4)

**Functions**:
- [ ] All functions have prototypes
- [ ] All return values checked (Rule 17.7)
- [ ] Functions ≤ 60 lines
- [ ] Functions ≤ 5 parameters

**Variables**:
- [ ] All variables initialized at declaration
- [ ] Internal functions/variables declared static
- [ ] No dynamic allocation (malloc/free) for SIL 2+
- [ ] volatile used for hardware registers

**Standard Library**:
- [ ] No forbidden functions (malloc, atoi, system, etc.)
- [ ] No stdio.h except snprintf

**Other**:
- [ ] All header files have include guards
- [ ] Complexity ≤ 10 (SIL 3-4)

### 12.3 Tool Commands for Compliance Checking

**Cppcheck (MISRA addon)**:
```bash
# Check MISRA C:2012 compliance
cppcheck --addon=misra --enable=all --xml --xml-version=2 src/ 2> misra_report.xml

# With project-specific suppressions
cppcheck --addon=misra --enable=all --suppressions-list=.cppcheck-suppressions src/
```

**Lizard (Complexity)**:
```bash
# Check cyclomatic complexity (max 10 for SIL 3-4)
lizard src/ -l c -CCN 10 -w
```

**GCC Warnings (Catch Basic Issues)**:
```bash
# Compile with all warnings
gcc -std=c99 -Wall -Wextra -Werror -Wconversion -Wsign-conversion -pedantic src/module.c
```

**PC-lint Plus** (Commercial):
```bash
# Full MISRA C:2012 check
pclp64 --misra3 --xml=output.xml src/module.c
```

**MISRA Compliance Verification** (run the qualified static analysis tool directly):
```bash
# Cppcheck MISRA C:2012 full check
cppcheck --addon=misra --enable=all --xml src/sensor_manager.c 2> misra_report.xml

# PC-lint Plus full check (if available)
pclp64 --misra3 --xml=output.xml src/sensor_manager.c
```
Note: `workflow-mgr verify-misra` does not exist in this platform.

### 12.4 Documentation References

**MISRA C:2012 Standard**:
- MISRA C:2012 Guidelines (Third Edition, 2023)
- MISRA C:2012 Amendment 1 (2016)
- MISRA C:2012 Amendment 2 (2020)
- MISRA C:2012 Amendment 3 (2024)

**EN 50128 References**:
- Section 7.4 "Component Design and Implementation"
- Table A.4 Technique 6 "Design and Coding Standards"
- Table A.12 "Design and Coding Standards"

**Project Documents**:
- Software Architecture Specification (DOC-9)
- Software Design Specification (DOC-10)
- Coding Standards Document
- MISRA C Deviation Register

**Workflow Documents**:
- `workflows/misra-c-implementation.md` - Implementation workflow
- `../en50128-design/resources/misra-c-design-guidelines.md` - Design guidance
- `resources/common-pitfalls.md` - Common violations
- `resources/code-review-checklist.md` - Review checklist

---

## Summary

This resource provides a comprehensive catalog of MISRA C:2012 compliant coding patterns for EN 50128 railway safety software. Key takeaways:

1. **Zero Mandatory Violations** for SIL 3-4 projects (143 mandatory rules)
2. **Fixed-Width Types** (`uint32_t`) replace native types (`int`)
3. **Pointer Safety**: NULL checks, bounds checks, no pointer arithmetic
4. **Control Flow**: No goto, no infinite loops, no recursion (SIL 3-4)
5. **Functions**: All prototypes, all returns checked, ≤ 60 lines
6. **Variables**: Initialize all, minimize scope, use static
7. **Arithmetic**: Check overflow, check divide-by-zero, validate shift counts
8. **Preprocessor**: Header guards, prefer inline to macros
9. **Standard Library**: No malloc/free (SIL 2+), no stdio.h
10. **Deviations**: Document with rationale, register, CCB approval

**Next Steps**:
1. Review this catalog before implementation
2. Follow `workflows/misra-c-implementation.md` for step-by-step process
3. Use static analysis tools (Cppcheck, PC-lint) to verify compliance
4. Document all deviations with technical rationale
5. Review code against `resources/code-review-checklist.md`

**Traceability**:
- This resource traces to Software Design Specification (DOC-10)
- Implementation traces to Software Requirements Specification (DOC-5) via Traceability Manager
- MISRA C compliance verified in Software Source Code Verification Report (DOC-19)

---

**Document Control**:
- **Version**: 1.0
- **Date**: 2026-03-13
- **Author**: EN 50128 Implementation Team
- **Approved by**: [Pending]
- **Next Review**: [After first project use]
