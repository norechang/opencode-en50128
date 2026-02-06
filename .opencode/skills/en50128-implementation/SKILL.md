---
name: en50128-implementation
description: C programming patterns with MISRA C:2012 compliance for EN 50128 railway safety software
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  language: C
  coding-standard: MISRA C:2012
---

## What I do

I provide C implementation patterns and practices for EN 50128 Section 7.4:
- Enforce MISRA C:2012 compliance (mandatory SIL 2+)
- Ensure static allocation only (no malloc/free for SIL 2+)
- Validate all pointers before use
- Check all function return values
- Apply defensive programming throughout
- Maintain complexity within limits

## When to use me

Use this skill when:
- Implementing C code from design
- Writing unit tests for C code
- Performing code reviews
- Checking MISRA C compliance
- Addressing safety-critical implementation concerns

## Implementation Techniques (EN 50128 Table A.4)

**EN 50128 Section 7.4, Table A.4** defines software design and implementation techniques:

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | Formal Methods | D.28 | - | R | HR |
| 2 | Modelling | Table A.17 | R | HR | HR |
| 3 | Structured Methodology | D.52 | R | HR | HR |
| 4 | **Modular Approach** | D.38 | HR | **M** | **M** |
| 5 | Components | Table A.20 | HR | HR | HR |
| 6 | **Design and Coding Standards** | Table A.12 | HR | HR | **M** |
| 7 | Analysable Programs | D.2 | HR | HR | HR |
| 8 | **Strongly Typed Programming Language** | D.49 | R | HR | HR |
| 9 | Structured Programming | D.53 | R | HR | HR |
| 10 | Programming Language | Table A.15 | R | HR | HR |
| 11 | Language Subset | D.35 | - | - | HR |
| 12 | Object Oriented Programming | Table A.22, D.57 | R | R | R |
| 13 | Procedural Programming | D.60 | R | HR | HR |
| 14 | Metaprogramming | D.59 | R | R | R |

**Mandatory Techniques:**
- **SIL 3-4:** Design and Coding Standards (6) is **MANDATORY**
- **SIL 2+:** Modular Approach (4) is **MANDATORY**

**Key Implementation Techniques:**
- **Technique 6 (Coding Standards):** MISRA C:2012 **MANDATORY** for SIL 3-4
- **Technique 4 (Modular Approach):** **MANDATORY** for SIL 2+
- **Technique 8 (Strongly Typed):** C with fixed-width types (uint8_t, uint16_t, etc.)
- **Technique 9 (Structured Programming):** No goto, structured control flow

**Approved Combinations:**
- **SIL 3-4:** 4, 5, 6, 8 + **one from** {1 or 2}
  - (Modular Approach, Components, Design/Coding Standards, Strongly Typed Language + Formal Methods OR Modelling)
  
- **SIL 1-2:** 3, 4, 5, 6 + **one from** {8, 9, or 10}
  - (Structured Methodology, Modular Approach, Components, Design/Coding Standards + Strongly Typed Language OR Structured Programming OR Programming Language)

**Standard Reference:** `std/EN50128-2011.md` Section 7.4, Table A.4

## MISRA C:2012 Core Rules

### Rule 21.3: No Dynamic Memory (Mandatory SIL 2+)
```c
// FORBIDDEN for SIL 2+
uint8_t* buffer = malloc(256);
free(buffer);

// REQUIRED for SIL 2+
static uint8_t buffer[256];
```

### Rule 17.7: Use Return Values
```c
// FORBIDDEN: Ignoring return value
function();

// REQUIRED: Check return value
error_t err = function();
if (err != SUCCESS) {
    handle_error(err);
}
```

### Fixed-Width Types (Rule 4.6)
```c
// REQUIRED
uint32_t counter;
int16_t temperature;

// FORBIDDEN
unsigned long counter;
int temperature;
```

## Module Implementation Pattern

```c
// brake_controller.h - Public Interface
#ifndef BRAKE_CONTROLLER_H
#define BRAKE_CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>
#include "error_codes.h"

typedef struct brake_state_t brake_state_t;

error_t brake_init(brake_state_t* state);
error_t brake_apply(brake_state_t* state, uint16_t speed, uint8_t* level);
error_t brake_emergency(brake_state_t* state);

#endif
```

```c
// brake_controller.c - Implementation
#include "brake_controller.h"

#define MAX_BRAKE_LEVEL  100U
#define MIN_SAFE_SPEED   10U

struct brake_state_t {
    uint8_t current_level;
    bool emergency_active;
    uint32_t last_update_time;
};

static bool validate_speed(uint16_t speed) {
    return (speed <= MAX_TRAIN_SPEED);
}

error_t brake_init(brake_state_t* state) {
    if (state == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    state->current_level = 0U;
    state->emergency_active = false;
    state->last_update_time = get_system_time();
    
    return SUCCESS;
}

error_t brake_apply(brake_state_t* state, uint16_t speed, uint8_t* level) {
    // Input validation
    if ((state == NULL) || (level == NULL)) {
        return ERROR_NULL_POINTER;
    }
    
    if (!validate_speed(speed)) {
        safety_log("Invalid speed");
        return ERROR_INVALID_SPEED;
    }
    
    // Calculate and apply
    *level = calculate_brake_level(speed);
    state->current_level = *level;
    state->last_update_time = get_system_time();
    
    return SUCCESS;
}
```

## Error Handling Pattern

```c
// error_codes.h
typedef enum {
    SUCCESS = 0,
    ERROR_NULL_POINTER = 1,
    ERROR_INVALID_PARAMETER = 2,
    ERROR_OUT_OF_RANGE = 3,
    ERROR_TIMEOUT = 4,
    ERROR_HARDWARE_FAULT = 5
} error_t;

// Usage with comprehensive checking
error_t process_sensor(const sensor_data_t* input, processed_data_t* output) {
    error_t status;
    
    if ((input == NULL) || (output == NULL)) {
        return ERROR_NULL_POINTER;
    }
    
    status = validate_sensor_data(input);
    if (status != SUCCESS) {
        log_error("Validation failed", status);
        return status;
    }
    
    status = perform_calculation(input, output);
    if (status != SUCCESS) {
        log_error("Calculation failed", status);
        return status;
    }
    
    return SUCCESS;
}
```

## Defensive Programming

### Input Validation
```c
error_t safe_function(const input_t* input, output_t* output) {
    // NULL checks
    if ((input == NULL) || (output == NULL)) {
        safety_log("NULL pointer");
        return ERROR_NULL_POINTER;
    }
    
    // Range validation
    if ((input->value < INPUT_MIN) || (input->value > INPUT_MAX)) {
        safety_log("Out of range");
        return ERROR_OUT_OF_RANGE;
    }
    
    // Plausibility check
    if (!is_plausible_value(input->value)) {
        safety_log("Implausible value");
        return ERROR_INVALID_PARAMETER;
    }
    
    // Rate of change check
    static uint32_t last_value = 0U;
    int32_t delta = (int32_t)input->value - (int32_t)last_value;
    
    if ((delta > MAX_RATE) || (delta < -MAX_RATE)) {
        safety_log("Unsafe rate of change");
        return ERROR_OUT_OF_RANGE;
    }
    
    last_value = input->value;
    
    // Process validated input
    output->result = input->value * 2U;
    
    return SUCCESS;
}
```

## Buffer Management - Static Allocation

```c
#define BUFFER_SIZE 256U

typedef struct {
    uint8_t data[BUFFER_SIZE];
    uint16_t head;
    uint16_t tail;
    uint16_t count;
} circular_buffer_t;

error_t buffer_init(circular_buffer_t* buffer) {
    if (buffer == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    buffer->head = 0U;
    buffer->tail = 0U;
    buffer->count = 0U;
    
    return SUCCESS;
}

error_t buffer_write(circular_buffer_t* buffer, uint8_t value) {
    if (buffer == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    if (buffer->count >= BUFFER_SIZE) {
        return ERROR_BUFFER_FULL;
    }
    
    buffer->data[buffer->head] = value;
    buffer->head = (buffer->head + 1U) % BUFFER_SIZE;
    buffer->count++;
    
    return SUCCESS;
}
```

## Safe Arithmetic Operations

```c
// Addition with overflow detection
error_t safe_add_u32(uint32_t a, uint32_t b, uint32_t* result) {
    if (result == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    if (a > (UINT32_MAX - b)) {
        safety_log("Integer overflow");
        return ERROR_OUT_OF_RANGE;
    }
    
    *result = a + b;
    return SUCCESS;
}

// Multiplication with overflow detection
error_t safe_multiply_u32(uint32_t a, uint32_t b, uint32_t* result) {
    if (result == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    if ((a != 0U) && (b > (UINT32_MAX / a))) {
        safety_log("Integer overflow");
        return ERROR_OUT_OF_RANGE;
    }
    
    *result = a * b;
    return SUCCESS;
}

// Division with zero check
error_t safe_divide_i32(int32_t num, int32_t den, int32_t* result) {
    if (result == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    if (den == 0) {
        safety_log("Division by zero");
        return ERROR_INVALID_PARAMETER;
    }
    
    if ((num == INT32_MIN) && (den == -1)) {
        safety_log("Division overflow");
        return ERROR_OUT_OF_RANGE;
    }
    
    *result = num / den;
    return SUCCESS;
}
```

## State Machine Implementation

```c
typedef enum {
    STATE_INIT,
    STATE_IDLE,
    STATE_OPERATIONAL,
    STATE_SAFE
} system_state_t;

typedef struct {
    system_state_t current_state;
    uint32_t state_entry_time;
} state_machine_t;

error_t sm_process_event(state_machine_t* sm, system_event_t event) {
    if (sm == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    system_state_t next_state = sm->current_state;
    
    switch (sm->current_state) {
        case STATE_INIT:
            if (event == EVENT_INIT_COMPLETE) {
                next_state = STATE_IDLE;
            }
            break;
            
        case STATE_IDLE:
            if (event == EVENT_START) {
                next_state = STATE_OPERATIONAL;
            } else if (event == EVENT_FAULT) {
                next_state = STATE_SAFE;
            }
            break;
            
        case STATE_OPERATIONAL:
            if (event == EVENT_STOP) {
                next_state = STATE_IDLE;
            } else if (event == EVENT_FAULT) {
                next_state = STATE_SAFE;
            }
            break;
            
        case STATE_SAFE:
            // Safe state - require manual intervention
            break;
            
        default:
            return ERROR_INVALID_STATE;
    }
    
    if (next_state != sm->current_state) {
        sm->current_state = next_state;
        sm->state_entry_time = get_system_time();
    }
    
    return SUCCESS;
}
```

## Coding Style

### Naming Conventions
```c
// Constants: UPPER_CASE
#define MAX_BUFFER_SIZE  256U

// Types: lower_case_t
typedef enum state_t state_t;
typedef struct sensor_data_t sensor_data_t;

// Functions: lower_case with module prefix
error_t brake_apply(void);

// Variables: lower_case
uint32_t current_speed;
```

### Comments
```c
/**
 * @brief Calculate braking force
 * @param[in]  speed Current speed in km/h [0..300]
 * @param[out] force Calculated force in N
 * @return SUCCESS or error code
 * @pre speed must be validated
 * @post force is in valid range
 */
error_t calculate_braking_force(uint16_t speed, uint32_t* force);
```

## Code Review Checklist

- [ ] MISRA C:2012 rules followed
- [ ] No dynamic memory allocation (SIL 2+)
- [ ] No recursion
- [ ] All pointers validated for NULL
- [ ] All return values checked
- [ ] All inputs range-checked
- [ ] Fixed-width types used
- [ ] Error handling comprehensive
- [ ] Cyclomatic complexity within limits
- [ ] Function length reasonable (<100 lines)

## References
- EN 50128:2011 Section 7.4 (Component Design & Implementation)
- MISRA C:2012 Guidelines
- ISO/IEC 9899:2018 (C Standard)
