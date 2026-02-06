---
name: en50128-design
description: Software architecture and design patterns for EN 50128 compliant C programs with MISRA C and defensive programming
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  language: C
  coding-standard: MISRA C:2012
---

## What I do

I provide design patterns and best practices for railway software architecture compliant with EN 50128 Section 7.3:
- Enforce modular design principles (mandatory SIL 2+)
- Apply cyclomatic complexity limits by SIL
- Ensure static memory allocation only (SIL 2+)
- Provide C-specific design patterns
- Enforce defensive programming techniques
- Ensure MISRA C:2012 compliance in design

## When to use me

Use this skill when:
- Creating software architecture (SAS)
- Designing software modules (SDS)
- Defining interfaces between components
- Applying defensive programming patterns
- Reviewing design for EN 50128 compliance
- Addressing safety architecture requirements

## Design Principles by SIL (EN 50128 Table A.4)

| Principle | SIL 0-1 | SIL 2 | SIL 3-4 |
|-----------|---------|-------|---------|
| Modularity | HR | HR | **M** |
| Structured Design | HR | HR | **M** |
| Defensive Programming | HR | HR | **M** |
| Fault Detection | R | HR | **M** |
| Error Handling | HR | HR | **M** |

**M**=Mandatory, **HR**=Highly Recommended, **R**=Recommended

## Cyclomatic Complexity Limits

- **SIL 0-1**: Maximum 20 per function
- **SIL 2**: Maximum 15 per function
- **SIL 3-4**: Maximum 10 per function

## C Memory Management (Critical for Safety)

### Static Allocation ONLY (SIL 2+)

```c
// CORRECT: Static allocation
#define BUFFER_SIZE 256U
static uint8_t buffer[BUFFER_SIZE];

// FORBIDDEN: Dynamic allocation for SIL 2+
uint8_t* buffer = malloc(size);  // NEVER for SIL 2+
```

### Module Structure

```c
// module_name.h - Public Interface
#ifndef MODULE_NAME_H
#define MODULE_NAME_H

#include <stdint.h>
#include "error_types.h"

// Opaque type
typedef struct module_state_t module_state_t;

// Public API
error_t module_init(module_state_t* state);
error_t module_process(module_state_t* state, const input_t* input);

#endif
```

```c
// module_name.c - Implementation
#include "module_name.h"

// Private structure
struct module_state_t {
    uint32_t internal_data;
    bool initialized;
};

// Private functions
static error_t validate_input(const input_t* input) {
    // Validation logic
}

// Public implementations
error_t module_init(module_state_t* state) {
    if (state == NULL) {
        return ERROR_NULL_POINTER;
    }
    state->internal_data = 0U;
    state->initialized = true;
    return SUCCESS;
}
```

## Defensive Programming Patterns

### Input Validation

```c
error_t safe_function(const input_t* input, output_t* output) {
    // NULL checks
    if ((input == NULL) || (output == NULL)) {
        return ERROR_NULL_POINTER;
    }
    
    // Range validation
    if ((input->value < MIN_VALUE) || (input->value > MAX_VALUE)) {
        return ERROR_OUT_OF_RANGE;
    }
    
    // Plausibility check
    if (!is_plausible_value(input->value)) {
        return ERROR_INVALID_PARAMETER;
    }
    
    // Process validated input
    output->result = input->value;
    return SUCCESS;
}
```

### Error Handling

```c
error_t operation(void) {
    error_t err;
    
    // Check every operation
    err = sub_operation_1();
    if (err != SUCCESS) {
        handle_error(err);
        return err;
    }
    
    err = sub_operation_2();
    if (err != SUCCESS) {
        handle_error(err);
        rollback_operation_1();
        return err;
    }
    
    return SUCCESS;
}
```

### Safe Arithmetic

```c
// Overflow detection
error_t safe_add_u32(uint32_t a, uint32_t b, uint32_t* result) {
    if (result == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    if (a > (UINT32_MAX - b)) {
        return ERROR_OVERFLOW;
    }
    
    *result = a + b;
    return SUCCESS;
}

// Division by zero check
error_t safe_divide(int32_t num, int32_t den, int32_t* result) {
    if (result == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    if (den == 0) {
        return ERROR_DIVIDE_BY_ZERO;
    }
    
    *result = num / den;
    return SUCCESS;
}
```

## Design Patterns for Safety

### State Machine Pattern

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

error_t sm_process_event(state_machine_t* sm, event_t event) {
    // Validate, transition, handle entry/exit
}
```

### Watchdog Pattern

```c
void main_safety_task(void) {
    watchdog_t wd;
    watchdog_init(&wd);
    
    while (1) {
        error_t status = perform_safety_function();
        if (status != SUCCESS) {
            enter_safe_state();
            break;
        }
        watchdog_feed(&wd);
        delay_ms(100);
    }
}
```

### Redundancy Pattern

```c
error_t read_redundant_sensor(sensor_value_t* value) {
    sensor_value_t ch_a = read_channel_a();
    sensor_value_t ch_b = read_channel_b();
    
    if (abs(ch_a - ch_b) < TOLERANCE) {
        *value = (ch_a + ch_b) / 2U;
        return SUCCESS;
    }
    
    return ERROR_SENSOR_DISAGREEMENT;
}
```

## MISRA C Compliance

### Data Types
```c
// USE: Fixed-width types
uint32_t counter;
int16_t temperature;

// AVOID: Implementation-defined types
unsigned long counter;
int temperature;
```

### No Recursion (Highly Recommended SIL 3-4)
```c
// AVOID: Recursive functions
void recursive_func(int n) {
    if (n > 0) recursive_func(n-1);
}

// USE: Iterative approach
void iterative_func(int n) {
    for (int i = 0; i < n; i++) {
        // Process
    }
}
```

## Interface Design

### Hardware Interface
```c
typedef struct {
    volatile uint32_t* base_address;
    uint32_t timeout_ms;
} hw_interface_t;

error_t hw_read(hw_interface_t* iface, uint32_t* value) {
    if (!iface || !value) return ERROR_NULL_POINTER;
    if (!is_address_valid(iface->base_address)) return ERROR_INVALID_ADDRESS;
    
    *value = *(iface->base_address);
    return SUCCESS;
}
```

### Software Interface
```c
/**
 * @brief Calculate safe braking distance
 * @param[in]  speed Current speed in km/h [0..300]
 * @param[in]  conditions Track conditions
 * @param[out] distance Calculated distance in meters
 * @return SUCCESS or error code
 * @pre speed is validated
 * @post distance is positive or zero
 */
error_t calculate_braking_distance(
    uint16_t speed,
    track_conditions_t conditions,
    uint32_t* distance
);
```

## Design Review Checklist

### Architecture Level
- [ ] All requirements addressed
- [ ] SIL-appropriate techniques used
- [ ] Safety functions isolated
- [ ] Fault detection mechanisms defined
- [ ] Interfaces clearly specified
- [ ] Traceability complete

### Module Level
- [ ] Single, well-defined responsibility
- [ ] Minimal coupling
- [ ] Maximal cohesion
- [ ] Comprehensive error handling
- [ ] Resource usage defined
- [ ] Timing constraints specified

### Code Level
- [ ] Defensive programming applied
- [ ] All inputs validated
- [ ] All outputs checked
- [ ] Error paths defined
- [ ] Resource limits enforced
- [ ] Traceable to design

## Complexity Metrics

Keep functions simple:
- Maximum lines per function: 100-200
- Maximum functions per module: 20-30
- Maximum nesting depth: 4-5 levels

## References
- EN 50128:2011 Section 7.3 (Software Architecture and Design)
- EN 50128:2011 Table A.4 (Design Techniques)
- MISRA C:2012 (Coding Standard)
