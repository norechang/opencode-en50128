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

I provide comprehensive patterns, templates, workflows, and resources for software architecture and design compliant with EN 50128 Section 7.3:
- **Workflows**: Step-by-step processes for architecture design, software design, interface design, and design review
- **Resources**: Guidelines for defensive programming, complexity management, modularity, MISRA C design, and architecture review
- **Templates**: Software Architecture Specification (DOC-9), Software Design Specification (DOC-10), and Software Interface Specifications (DOC-11) templates
- **Techniques**: EN 50128 Table A.3 techniques (Modular Approach, Structured Methodology, Defensive Programming, Fault Detection)
- **C Language**: MISRA C:2012 compliant design patterns with static allocation, bounded complexity, and safety patterns

## When to use me

Use this skill when:
- **Starting architecture phase**: Follow `workflows/architecture-design.md` to create Software Architecture Specification (DOC-9)
- **Designing modules**: Use `workflows/software-design.md` to create Software Design Specification (DOC-10)
- **Defining interfaces**: Follow `workflows/interface-design.md` to specify internal, hardware, external, and HMI interfaces (DOC-11)
- **Reviewing design**: Apply `workflows/design-review.md` for SIL-dependent peer, QUA, VER, VAL, and PM reviews
- **Applying defensive patterns**: Reference `resources/defensive-programming-patterns.md` for 18 comprehensive safety patterns
- **Managing complexity**: Use `resources/complexity-guidelines.md` for SIL-dependent complexity limits and reduction strategies
- **Ensuring modularity**: Apply `resources/modularity-guidelines.md` for modular design principles (MANDATORY SIL 2+)
- **MISRA C design**: Follow `resources/misra-c-design-guidelines.md` for design decisions affecting MISRA C compliance

## How to use this skill

### For Designers (DES)

**Complete Architecture and Design Phase Workflow:**

```
1. ARCHITECTURE DESIGN (workflows/architecture-design.md)
   ├─ Review input documents (SRS DOC-5, Hazard Log DOC-21, SQAP DOC-2, SCMP DOC-3)
   ├─ Identify architectural components (decompose system into subsystems/components)
   ├─ Define component interfaces (data, control, timing)
   ├─ Apply EN 50128 Table A.3 techniques:
   │    ├─ Structured Methodology (MANDATORY SIL 3-4)
   │    ├─ Modular Approach (MANDATORY SIL 2+)
   │    ├─ Defensive Programming (Highly Recommended SIL 3-4)
   │    └─ Fault Detection and Diagnosis (Highly Recommended SIL 3-4)
   ├─ Design safety architecture (fault detection, fail-safe, redundancy)
   ├─ Allocate requirements to components (traceability)
   ├─ Document in Software Architecture Specification (DOC-9)
   └─ Submit for review (PEER → QUA → VER → VAL → PM)

2. SOFTWARE DESIGN (workflows/software-design.md)
   ├─ Decompose architectural components into modules
   ├─ Design module interfaces (function signatures, data structures)
   ├─ Specify functions (parameters, return values, error handling)
   ├─ Design data structures (structs, enums, arrays - MISRA C compliant)
   ├─ Apply complexity limits (≤10 CCN for SIL 3-4, ≤15 for SIL 2)
   ├─ Apply defensive programming patterns (input validation, error detection)
   ├─ Ensure static allocation only (SIL 2+) - no dynamic memory
   ├─ Document algorithms (pseudocode, flowcharts)
   ├─ Document in Software Design Specification (DOC-10)
   └─ Submit for review (PEER → QUA → VER → VAL → PM)

3. INTERFACE DESIGN (workflows/interface-design.md)
   ├─ Define internal interfaces (SW-SW communication between modules)
   ├─ Define hardware interfaces (SW-HW, memory-mapped I/O, GPIO, ADC, timers)
   ├─ Define external interfaces (SW-external system, CAN, UART, SPI, I2C)
   ├─ Define HMI interfaces (SW-user, displays, buttons, indicators)
   ├─ Specify interface protocols (data formats, timing, error handling)
   ├─ Apply defensive programming at interfaces (validation, error detection)
   ├─ Document in Software Interface Specifications (DOC-11)
   └─ Submit for review (PEER → QUA → VER → VAL → PM)

4. DESIGN REVIEW (workflows/design-review.md)
   ├─ Self-review (use resources/architecture-review-checklist.md)
   ├─ PEER review (technical correctness, clarity)
   ├─ QUA review (process compliance, EN 50128, MISRA C)
   ├─ SAFETY_MGR review (hazard mitigation, SIL 3-4)
   ├─ VER review (traceability, completeness, SIL 3-4)
   ├─ VAL review (testability, SIL 3-4)
   ├─ PM review (project alignment, risks)
   └─ Rework if rejected (all reviewers must re-approve)

5. BASELINE & APPROVAL
   ├─ All reviews pass (SIL 0-2: 4 approvals, SIL 3-4: 8 approvals)
   ├─ Documents baselined (CM locks versions: DOC-9 v1.0, DOC-10 v1.0, DOC-11 v1.0)
   └─ Proceed to implementation phase
```

### For Quality Assurance (QUA)

**Design Review Checklist:**
1. Verify document template compliance (DOC-9, DOC-10, DOC-11 templates)
2. Apply `resources/architecture-review-checklist.md` for completeness, correctness, consistency
3. Verify EN 50128 Table A.3 techniques applied (Modular Approach MANDATORY SIL 2+)
4. Verify MISRA C design compliance (static allocation, fixed-width types, no recursion for SIL 3-4)
5. Verify defensive programming applied (input validation, error handling, fail-safe)
6. Verify complexity within limits (≤10 CCN for SIL 3-4)
7. Verify traceability complete (requirements → architecture → design)

### For Verifiers (VER)

**Verification Checklist:**
1. Verify all requirements (SRS DOC-5) addressed in architecture/design
2. Verify traceability complete (100% for SIL 3-4)
3. Verify design is verifiable (static analysis, complexity analysis, unit testing)
4. Verify EN 50128 compliance (Table A.3 techniques, Table A.4 design techniques)
5. Verify safety requirements addressed (hazard mitigation, fault detection)
6. Run tool validations:
   ```bash
   traceability.py validate --matrix requirements_to_architecture --sil 3
   traceability.py validate --matrix architecture_to_design --sil 3
   lizard src/ --CCN 10 --warnings_only  # SIL 3-4
   ```
7. Create Software Architecture Verification Report (DOC-012) and Software Design Verification Report (DOC-013)

### For Validators (VAL)

**Validation Checklist:**
1. Verify design supports operational scenarios
2. Verify design is testable (unit tests, integration tests, system tests)
3. Verify test coverage targets achievable (100% branch + condition for SIL 3-4)
4. Provide validation approval

### For Safety Managers (SAFETY_MGR, SIL 3-4)

**Safety Review Checklist:**
1. Verify all hazards (Hazard Log DOC-21) addressed in safety architecture
2. Verify fault detection mechanisms defined (sensor validation, communication checks, watchdog)
3. Verify fail-safe behavior defined (safe state entry, emergency stop)
4. Verify defensive programming patterns applied (`resources/defensive-programming-patterns.md`)
5. Verify safety requirements traced to design elements

## Skill Structure

```
en50128-design/
├── SKILL.md                               (This file - comprehensive guide)
├── templates/
│   ├── Software-Architecture-Specification-template.md (DOC-9)
│   ├── Software-Design-Specification-template.md (DOC-10)
│   ├── Software-Interface-Specifications-template.md (DOC-11)
│   ├── Software-Architecture-Verification-Report-template.md (DOC-012)
│   └── Software-Design-Verification-Report-template.md (DOC-013)
├── workflows/
│   ├── architecture-design.md             (Create DOC-9 - ~45 pages)
│   ├── software-design.md                 (Create DOC-10 - ~40 pages)
│   ├── interface-design.md                (Create DOC-11 - ~50 pages)
│   └── design-review.md                   (Review process - ~50 pages)
├── resources/
│   ├── defensive-programming-patterns.md  (18 patterns - ~25 pages)
│   ├── complexity-guidelines.md           (Complexity management - ~20 pages)
│   ├── modularity-guidelines.md           (Modular design - ~50 pages)
│   ├── misra-c-design-guidelines.md       (MISRA C design - ~40 pages)
│   └── architecture-review-checklist.md   (Review checklist - ~35 pages)
└── tools/
    └── (Tool integration via Traceability Manager and Workflow Manager)
```

## Software Architecture Techniques (EN 50128 Table A.3)

**EN 50128 Section 7.3, Table A.3** defines software architecture and design techniques:

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | Structured Methodology | D.52 | R | HR | **M** |
| 2 | Defensive Programming | D.14 | - | HR | HR |
| 3 | Fault Detection and Diagnosis | D.26 | - | R | HR |
| 4 | Information Encapsulation | D.33 | R | HR | HR |
| 5 | Modelling | Table A.17 | R | R | HR |
| 6 | Formal Methods | D.28 | - | R | HR |
| 7 | Fully Defined Interface | D.38 | HR | HR | HR |
| 8 | Structured Design | D.51 | R | HR | HR |
| 9 | Functional Cohesion | D.55 | R | R | HR |
| 10 | Coupling and Cohesion | D.55 | R | R | HR |
| 11 | Software Modules with Low Coupling | D.55 | R | HR | HR |
| 12 | Event-driven Programming | D.21 | - | - | R |
| 13 | Concurrency | D.11 | - | R | R |
| 14 | Interrupt | D.35 | - | - | R |
| 15 | Object-oriented Programming | D.39 | - | R | R |
| 16 | Design and Coding Standards | Table A.12 | HR | HR | HR |
| 17 | Software Design Notations | D.46 | R | R | HR |
| 18 | Data Flow Diagrams | D.10 | R | R | R |
| 19 | **Modular Approach** | D.38 | HR | **M** | **M** |
| 20 | Schedulability Analysis | D.40 | - | R | HR |
| 21 | Time-triggered Architecture | D.56 | - | R | HR |
| 22 | Memorisation of Data/Program Flow | D.36 | R | HR | HR |
| 23 | Failure Assertion Programming | D.24 | - | R | HR |

**Mandatory Techniques:**
- **SIL 3-4:** Structured Methodology (1) and Modular Approach (19) are **MANDATORY**
- **SIL 2+:** Modular Approach (19) is **MANDATORY**

**Key Highly Recommended for SIL 3-4:**
- Defensive Programming (2)
- Fault Detection and Diagnosis (3)
- Modelling (5)
- Formal Methods (6)
- Fully Defined Interface (7)

**Approved Combinations:**
- **SIL 3-4 Option A:** 1, 7, 19, 22 + one from {4, 5, 12, 21}
- **SIL 3-4 Option B:** 1, 4, 19, 22 + one from {2, 5, 12, 15, 21}
- **SIL 1-2:** 1, 7, 19, 22

**Standard Reference:** `std/EN50128-2011.md` Section 7.3, Table A.3

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

## Standard References

- **EN 50128:2011 Section 7.3** - Software Architecture and Design - `std/EN50128-2011.md`
- **EN 50128:2011 Table A.3** - Software Architecture techniques - `std/EN50128-2011.md`
- **EN 50128:2011 Table A.4** - Software Design and Implementation techniques - `std/EN50128-2011.md`
- **EN 50128:2011 Table A.12** - Design and Coding Standards - `std/EN50128-2011.md`
- **EN 50128:2011 Table A.19** - Static Analysis (MANDATORY SIL 3-4) - `std/EN50128-2011.md`
- **EN 50128:2011 Annex D.14** - Defensive Programming - `std/EN50128-2011.md`
- **EN 50128:2011 Annex D.38** - Modular Approach - `std/EN50128-2011.md`
- **MISRA C:2012** - C Coding Standard (MANDATORY SIL 3-4) - `docs/MISRA-C-2012.pdf`
- **EN 50126-1:2017 Section 7** - RAMS Requirements - `std/EN 50126-1-2017.md`

## Interaction with Other Agents

**Receives requirements from:**
- `/req` - Requirements Engineer (Software Requirements Specification DOC-5)
- `/saf` - Safety Engineer (Hazard Log DOC-21, safety requirements)

**Provides design to:**
- `/imp` - Implementer (implements design in C code)
- `/tst` - Tester (tests against design specifications)
- `/int` - Integrator (integrates modules per architecture)

**Coordinates with:**
- `/ver` - Verifier (design verification, traceability validation)
- `/val` - Validator (design validation, testability review)
- `/qua` - Quality Assurance (design reviews, EN 50128 compliance)
- `/pm` - Project Manager (design approval, change control)
- `/cm` - Configuration Manager (design baselines, version control)

**Submits for review to:**
- PEER → QUA → SAFETY_MGR (SIL 3-4) → VER (SIL 3-4) → VAL (SIL 3-4) → PM

## Abbreviations

- **DES** = Designer (you)
- **SAS** = Software Architecture Specification (DOC-9)
- **SDS** = Software Design Specification (DOC-10)
- **SIS** = Software Interface Specifications (DOC-11)
- **SIL** = Safety Integrity Level
- **CCN** = Cyclomatic Complexity Number
- **M** = Mandatory
- **HR** = Highly Recommended
- **R** = Recommended
- **MISRA C** = Motor Industry Software Reliability Association C
- **WCET** = Worst Case Execution Time

**Reference:** `std/EN50128-ABBREVIATIONS.md`
