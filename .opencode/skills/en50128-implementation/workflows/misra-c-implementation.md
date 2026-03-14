# MISRA C:2012 Implementation Workflow

**Skill**: en50128-implementation  
**Role**: Implementer (IMP)  
**Phase**: Implementation & Testing (Phase 4)  
**EN 50128 Reference**: Section 7.4, Table A.4 (Technique 6: Design and Coding Standards)

---

## Purpose

This workflow guides the implementation of C code following MISRA C:2012 coding standards, which is **MANDATORY** for SIL 3-4 projects per EN 50128 Table A.4 Technique 6.

**Key Objectives**:
- Implement code that is **100% MISRA C:2012 compliant** (SIL 3-4)
- Ensure zero mandatory rule violations
- Document and justify any required deviations
- Produce analyzable, maintainable, safe code

---

## Prerequisites

### Required Inputs
- [ ] Software Design Specification (DOC-10) - APPROVED
- [ ] Software Interface Specifications (DOC-11) - APPROVED
- [ ] Module specifications with interfaces defined
- [ ] Traceability matrix (Design → Code)

### Required Tools
```bash
# Verify tool availability
which gcc && gcc --version           # GCC compiler
which cppcheck && cppcheck --version # Static analyzer
which pc-lint                        # PC-lint Plus (if available)
which lizard && lizard --version     # Complexity analyzer

# Check project build system
ls Makefile || ls CMakeLists.txt
```

### Required Knowledge
- MISRA C:2012 mandatory rules
- Project coding standards
- C99 or C11 standard features
- Module design from SDS

---

## MISRA C:2012 Rule Categories

### Mandatory Rules (143 rules)
**ZERO violations allowed** for SIL 3-4 projects.

**Key Mandatory Rules**:
- **Rule 1.3**: No undefined behavior
- **Rule 2.1**: No unreachable code
- **Rule 2.2**: No dead code
- **Rule 8.1**: Types explicit
- **Rule 9.1**: No uninitialized variables
- **Rule 21.3**: No malloc/calloc/realloc/free (SIL 2+)
- **Rule 21.6**: No stdio.h functions (snprintf/vsnprintf allowed)

### Required Rules (10 rules)
**Must comply or document deviation** with technical rationale.

### Advisory Rules (125 rules)
**Should comply** - deviations permitted with justification.

**Reference**: See `resources/misra-c-coding-patterns.md` for complete rule catalog.

---

## Step 1: Setup Development Environment

### 1.1 Configure Compiler Flags

**For SIL 3-4 projects:**
```makefile
# Makefile configuration
CC = gcc
CFLAGS = -std=c99 \
         -Wall -Wextra -Werror \
         -pedantic \
         -Wstrict-prototypes \
         -Wmissing-prototypes \
         -Wold-style-definition \
         -Wconversion \
         -Wsign-conversion \
         -Wcast-qual \
         -Wcast-align \
         -Wshadow \
         -Wpointer-arith \
         -Wwrite-strings \
         -Wredundant-decls \
         -Wnested-externs \
         -Winline \
         -Wno-long-long \
         -fno-common

# Safety flags (SIL 2+)
CFLAGS += -fno-builtin \
          -fstack-protector-all \
          -D_FORTIFY_SOURCE=2

# Optimization (after testing)
CFLAGS += -O2 -g
```

**Rationale**:
- `-std=c99`: MISRA C:2012 based on C99
- `-Wall -Wextra -Werror`: Treat warnings as errors
- `-Wconversion -Wsign-conversion`: Detect implicit conversions (MISRA Rule 10.x)
- `-fno-builtin`: Prevent compiler optimizations that violate MISRA
- `-fstack-protector-all`: Stack overflow protection (SIL 2+)

### 1.2 Configure Static Analysis

**Cppcheck Configuration:**
```bash
# Create .cppcheck configuration
cat > .cppcheck <<EOF
# MISRA C:2012 checks
--addon=misra
--addon=cert
--addon=threadsafety

# Error detection
--enable=all
--inconclusive
--inline-suppr

# Output format
--xml
--xml-version=2

# Suppression file
--suppressions-list=.cppcheck-suppressions
EOF
```

**PC-lint Plus Configuration (if available):**
```bash
# Create std.lnt file
cat > std.lnt <<EOF
// MISRA C:2012 configuration
au-misra3.lnt
au-misra3-amd1.lnt
au-misra3-amd2.lnt

// Project-specific options
-w4          // Warning level 4
+e900        // Enable all errors
-zero(99)    // Continue after 99 messages
EOF
```

### 1.3 Setup Traceability Tracking

```bash
# Initialize traceability for code implementation
workspace.py trace create \
    --from design \
    --to code \
    --sil 3

# Extract traceability from design documents
workspace.py trace extract \
    --document docs/DOC-10-SDS.md \
    --type design_to_code \
    --merge

# Mark design item as implementing
# (Use trace update after implementation complete)
```

---

## Step 2: Implement Module Header File (.h)

### 2.1 Header File Structure

**Template:**
```c
/**
 * @file    brake_controller.h
 * @brief   Brake control system interface
 * @author  [Name]
 * @date    2026-03-13
 * @version 1.0.0
 * 
 * EN 50128 Traceability:
 * - Implements: DOC-10 MOD-001 (Brake Controller Module)
 * - SIL Level: 3
 * - MISRA C:2012: Compliant
 */

#ifndef BRAKE_CONTROLLER_H
#define BRAKE_CONTROLLER_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/
#include <stdint.h>    /* MISRA C:2012 Rule 21.2 - Standard integers */
#include <stdbool.h>   /* MISRA C:2012 Rule 21.2 - Boolean type */
#include "error_codes.h"

/*******************************************************************************
 * DEFINES AND MACROS
 ******************************************************************************/
/** @brief Maximum brake level percentage */
#define BRAKE_MAX_LEVEL     (100U)

/** @brief Minimum safe speed in km/h */
#define BRAKE_MIN_SPEED     (10U)

/*******************************************************************************
 * TYPES AND STRUCTURES
 ******************************************************************************/
/**
 * @brief Brake controller state (opaque type)
 * @note  Internal structure defined in .c file (information hiding)
 */
typedef struct brake_state_t brake_state_t;

/**
 * @brief Brake application mode
 */
typedef enum {
    BRAKE_MODE_NORMAL = 0,   /**< Normal braking */
    BRAKE_MODE_EMERGENCY = 1, /**< Emergency braking */
    BRAKE_MODE_HOLDING = 2    /**< Holding brake active */
} brake_mode_t;

/*******************************************************************************
 * PUBLIC FUNCTION DECLARATIONS
 ******************************************************************************/
/**
 * @brief Initialize brake controller
 * @param[in,out] state Pointer to brake state structure
 * @return SUCCESS or error code
 * @pre state != NULL
 * @post state is initialized if SUCCESS returned
 * @note Complexity: 3
 */
error_t brake_init(brake_state_t* state);

/**
 * @brief Apply brake based on speed
 * @param[in,out] state Pointer to brake state structure
 * @param[in]     speed Current speed in km/h [0..300]
 * @param[out]    level Calculated brake level [0..100]
 * @return SUCCESS or error code
 * @pre state != NULL, level != NULL, speed validated
 * @post Brake level calculated if SUCCESS
 * @note Complexity: 8
 */
error_t brake_apply(brake_state_t* state, uint16_t speed, uint8_t* level);

/**
 * @brief Activate emergency brake
 * @param[in,out] state Pointer to brake state structure
 * @return SUCCESS or error code
 * @pre state != NULL
 * @post Emergency brake active if SUCCESS
 * @note Complexity: 5
 */
error_t brake_emergency(brake_state_t* state);

#endif /* BRAKE_CONTROLLER_H */
```

**MISRA C Compliance Checks**:
- ✅ **Rule 8.1**: All types explicitly declared
- ✅ **Rule 8.2**: Function prototypes have named parameters
- ✅ **Rule 8.4**: All declarations visible
- ✅ **Rule 8.5**: Single definition for external identifiers
- ✅ **Rule 21.1**: `#define`/`#undef` not used for reserved identifiers
- ✅ **Rule 20.1**: Include guards present (`#ifndef BRAKE_CONTROLLER_H`)

### 2.2 Opaque Type Pattern (Information Hiding)

**Why**: MISRA C encourages information hiding (EN 50128 Table A.3 Technique 15)

**Header (brake_controller.h):**
```c
// Public: Opaque pointer
typedef struct brake_state_t brake_state_t;
```

**Implementation (brake_controller.c):**
```c
// Private: Full definition
struct brake_state_t {
    uint8_t current_level;
    bool emergency_active;
    uint32_t last_update_time;
    brake_mode_t mode;
};
```

**Benefits**:
- Encapsulation (clients cannot access internal fields)
- Prevents accidental modification
- Allows internal structure changes without API changes
- Compliant with MISRA C Rule 8.8 (static storage when possible)

---

## Step 3: Implement Module Source File (.c)

### 3.1 Source File Structure

```c
/**
 * @file    brake_controller.c
 * @brief   Brake control system implementation
 * @author  [Name]
 * @date    2026-03-13
 * @version 1.0.0
 * 
 * EN 50128 Traceability:
 * - Implements: DOC-10 MOD-001 (Brake Controller Module)
 * - Tests: DOC-16 TEST-BRAKE-001
 * - SIL Level: 3
 * - MISRA C:2012: Compliant (0 mandatory violations)
 * 
 * MISRA Deviations: None
 */

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/
#include "brake_controller.h"
#include "safety_log.h"
#include "system_time.h"
#include <string.h>  /* memset - MISRA Rule 21.6 allowed */

/*******************************************************************************
 * PRIVATE DEFINES
 ******************************************************************************/
/** @brief Maximum train speed in km/h */
#define MAX_TRAIN_SPEED     (300U)

/** @brief Brake calculation coefficient */
#define BRAKE_COEFF         (2U)

/*******************************************************************************
 * PRIVATE TYPES
 ******************************************************************************/
/**
 * @brief Brake controller state (full definition)
 */
struct brake_state_t {
    uint8_t current_level;      /**< Current brake level [0..100] */
    bool emergency_active;      /**< Emergency brake flag */
    uint32_t last_update_time;  /**< Last update timestamp */
    brake_mode_t mode;          /**< Current brake mode */
};

/*******************************************************************************
 * PRIVATE FUNCTION DECLARATIONS
 ******************************************************************************/
static bool validate_speed(uint16_t speed);
static uint8_t calculate_brake_level(uint16_t speed);
static error_t transition_mode(brake_state_t* state, brake_mode_t new_mode);

/*******************************************************************************
 * PRIVATE FUNCTION IMPLEMENTATIONS
 ******************************************************************************/
/**
 * @brief Validate speed input
 * @param[in] speed Speed value to validate
 * @return true if valid, false otherwise
 * @note Complexity: 2
 */
static bool validate_speed(uint16_t speed)
{
    bool result = false;
    
    if (speed <= MAX_TRAIN_SPEED) {
        result = true;
    }
    
    return result;
}

/**
 * @brief Calculate brake level from speed
 * @param[in] speed Current speed [0..300]
 * @return Brake level [0..100]
 * @pre speed is validated
 * @note Complexity: 4
 */
static uint8_t calculate_brake_level(uint16_t speed)
{
    uint8_t level;
    uint16_t temp;
    
    /* Linear calculation: level = speed / BRAKE_COEFF */
    temp = speed / BRAKE_COEFF;
    
    /* Saturate to max */
    if (temp > BRAKE_MAX_LEVEL) {
        level = (uint8_t)BRAKE_MAX_LEVEL;
    } else {
        level = (uint8_t)temp;  /* MISRA Rule 10.3: Explicit cast */
    }
    
    return level;
}

/**
 * @brief Transition brake mode with validation
 * @param[in,out] state Pointer to brake state
 * @param[in]     new_mode New mode to transition to
 * @return SUCCESS or error code
 * @note Complexity: 6
 */
static error_t transition_mode(brake_state_t* state, brake_mode_t new_mode)
{
    error_t result = SUCCESS;
    
    /* Validate state machine transition */
    switch (state->mode) {
        case BRAKE_MODE_NORMAL:
            /* Can transition to any mode */
            state->mode = new_mode;
            break;
            
        case BRAKE_MODE_EMERGENCY:
            /* Emergency mode sticky - requires reset */
            if (new_mode != BRAKE_MODE_EMERGENCY) {
                safety_log("Cannot exit emergency mode");
                result = ERROR_INVALID_STATE;
            }
            break;
            
        case BRAKE_MODE_HOLDING:
            /* Can transition to normal or emergency */
            if ((new_mode == BRAKE_MODE_NORMAL) || 
                (new_mode == BRAKE_MODE_EMERGENCY)) {
                state->mode = new_mode;
            } else {
                result = ERROR_INVALID_STATE;
            }
            break;
            
        default:
            safety_log("Invalid brake mode");
            result = ERROR_INVALID_STATE;
            break;
    }
    
    return result;
}

/*******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS
 ******************************************************************************/
error_t brake_init(brake_state_t* state)
{
    error_t result;
    
    /* MISRA Rule 9.1: Check for NULL before use */
    if (state == NULL) {
        safety_log("NULL pointer in brake_init");
        result = ERROR_NULL_POINTER;
    } else {
        /* Initialize all fields (MISRA Rule 9.1) */
        (void)memset(state, 0, sizeof(*state));
        
        state->current_level = 0U;
        state->emergency_active = false;
        state->last_update_time = system_get_time();
        state->mode = BRAKE_MODE_NORMAL;
        
        result = SUCCESS;
    }
    
    return result;
}

error_t brake_apply(brake_state_t* state, uint16_t speed, uint8_t* level)
{
    error_t result;
    
    /* Input validation (MISRA Rule 17.7 - check all inputs) */
    if ((state == NULL) || (level == NULL)) {
        safety_log("NULL pointer in brake_apply");
        result = ERROR_NULL_POINTER;
    } else if (!validate_speed(speed)) {
        safety_log("Invalid speed value");
        result = ERROR_INVALID_PARAMETER;
    } else {
        /* Perform calculation */
        *level = calculate_brake_level(speed);
        state->current_level = *level;
        state->last_update_time = system_get_time();
        
        result = SUCCESS;
    }
    
    return result;
}

error_t brake_emergency(brake_state_t* state)
{
    error_t result;
    
    if (state == NULL) {
        safety_log("NULL pointer in brake_emergency");
        result = ERROR_NULL_POINTER;
    } else {
        /* Maximum brake immediately */
        state->current_level = (uint8_t)BRAKE_MAX_LEVEL;
        state->emergency_active = true;
        state->last_update_time = system_get_time();
        
        /* Transition to emergency mode */
        result = transition_mode(state, BRAKE_MODE_EMERGENCY);
        
        if (result == SUCCESS) {
            safety_log("Emergency brake activated");
        }
    }
    
    return result;
}
```

**MISRA C Compliance Checks**:
- ✅ **Rule 8.7**: Static functions declared static
- ✅ **Rule 8.13**: Const-correct parameters
- ✅ **Rule 9.1**: All variables initialized before use
- ✅ **Rule 10.3**: Explicit casts for type conversions
- ✅ **Rule 14.4**: Controlling expression is boolean
- ✅ **Rule 15.5**: Single exit point (one return per function encouraged)
- ✅ **Rule 17.7**: All return values used
- ✅ **Rule 21.3**: No dynamic memory allocation

### 3.2 MISRA C Patterns Applied

#### Pattern 1: NULL Pointer Checks (Mandatory)
```c
error_t function(type_t* ptr)
{
    error_t result;
    
    if (ptr == NULL) {  /* MISRA Rule 14.4 - boolean expression */
        result = ERROR_NULL_POINTER;
    } else {
        /* Safe to use ptr */
        result = SUCCESS;
    }
    
    return result;
}
```

#### Pattern 2: Explicit Type Casting (Rule 10.3)
```c
uint16_t value16 = 1000U;
uint8_t value8;

/* FORBIDDEN: Implicit narrowing cast */
value8 = value16;  /* MISRA Rule 10.3 violation */

/* REQUIRED: Explicit cast with range check */
if (value16 <= (uint16_t)UINT8_MAX) {
    value8 = (uint8_t)value16;  /* Compliant */
} else {
    /* Handle overflow */
}
```

#### Pattern 3: Fixed-Width Types (Rule 4.6)
```c
/* REQUIRED: Use <stdint.h> types */
uint8_t  count;      /* 0..255 */
uint16_t speed;      /* 0..65535 */
uint32_t timestamp;  /* Large values */
int16_t  temperature; /* Signed values */

/* FORBIDDEN: Platform-dependent types */
unsigned int count;       /* MISRA Rule 4.6 violation */
long timestamp;           /* MISRA Rule 4.6 violation */
```

#### Pattern 4: Boolean Type (Rule 14.4)
```c
#include <stdbool.h>  /* C99 boolean type */

/* REQUIRED: Use bool type */
bool is_valid(uint16_t value)
{
    bool result = false;
    
    if (value < MAX_VALUE) {
        result = true;
    }
    
    return result;
}

/* Use in conditions */
if (is_valid(speed)) {  /* Boolean expression */
    /* ... */
}
```

#### Pattern 5: Enum for Constants (Rule 10.4)
```c
/* PREFERRED: Use enum for related constants */
typedef enum {
    SPEED_MIN = 0,
    SPEED_MAX = 300,
    SPEED_NOMINAL = 80
} speed_limits_t;

/* FORBIDDEN: Multiple #defines */
#define SPEED_MIN 0
#define SPEED_MAX 300
/* ... harder to group */
```

---

## Step 4: Run Static Analysis

### 4.1 Cppcheck Analysis

```bash
# Run Cppcheck with MISRA addon
cppcheck --addon=misra \
         --enable=all \
         --inconclusive \
         --xml \
         --xml-version=2 \
         src/brake_controller.c \
         2> analysis/cppcheck_brake_controller.xml

# Check for violations
grep -i "error" analysis/cppcheck_brake_controller.xml
grep -i "misra" analysis/cppcheck_brake_controller.xml
```

**Expected Output (SIL 3-4):**
```
No MISRA mandatory violations found.
```

**If violations found:**
1. Review each violation
2. Fix code OR document deviation (Required/Advisory rules only)
3. Re-run analysis
4. Repeat until zero mandatory violations

### 4.2 Compiler Warnings Check

```bash
# Compile with all warnings
make clean
make CFLAGS="-Wall -Wextra -Werror -pedantic"

# MUST compile without errors for SIL 3-4
```

**Common Warnings to Fix**:
- `-Wconversion`: Implicit type conversions → Add explicit casts
- `-Wsign-conversion`: Signed/unsigned mismatch → Use correct types
- `-Wshadow`: Variable shadowing → Rename variables
- `-Wunused-parameter`: Unused parameters → Cast to `(void)` or remove

### 4.3 Complexity Analysis

```bash
# Run Lizard complexity analysis
lizard src/brake_controller.c \
       --CCN 10 \
       --warnings_only \
       --modified

# For SIL 3-4: CCN must be ≤ 10
```

**Output Example:**
```
================================================
  NLOC    CCN   token  PARAM  length  location  
------------------------------------------------
       3      2     18      1       5  validate_speed@10-14@brake_controller.c
       8      4     45      1      12  calculate_brake_level@20-31@brake_controller.c
      12      6     78      2      18  transition_mode@37-54@brake_controller.c
       9      3     52      1      14  brake_init@60-73@brake_controller.c
      11      4     68      3      17  brake_apply@75-91@brake_controller.c
       8      3     49      1      13  brake_emergency@93-105@brake_controller.c
------------------------------------------------
Total: 6 functions, average CCN: 3.67 (Max: 6)
```

**If CCN > 10**: Refactor function to reduce complexity (see `resources/complexity-guidelines.md`)

---

## Step 5: Update Traceability

### 5.1 Link Implementation to Design

```bash
# After implementation complete, create traceability links
# Links are typically created via inline document markers or bulk import

# For bulk import from CSV:
cat > traces_code.csv <<EOF
source_id,target_id,trace_type,status
DOC-10:MOD-001,src/brake_controller.c,design_to_code,implemented
DOC-10:MOD-001:brake_init,src/brake_controller.c:brake_init,design_to_code,implemented
DOC-10:MOD-001:brake_apply,src/brake_controller.c:brake_apply,design_to_code,implemented
DOC-10:MOD-001:brake_emergency,src/brake_controller.c:brake_emergency,design_to_code,implemented
EOF

workspace.py trace import --file traces_code.csv --format csv --merge
```

### 5.2 Verify Coverage

```bash
# Check all design items implemented
workspace.py trace check-gaps \
    --phase implementation \
    --sil 3

# Generate traceability report
workspace.py trace report \
    --from design \
    --to code \
    --format markdown \
    --output evidence/traceability/design_to_code_report.md

# Expected: 100% coverage (SIL 3-4)
```

---

## Step 6: Document Implementation

### 6.1 Update Implementation Log

Create `docs/implementation/IMPLEMENTATION_LOG.md`:

```markdown
# Implementation Log

## Module: brake_controller
- **File**: src/brake_controller.c, src/brake_controller.h
- **Implements**: DOC-10 MOD-001
- **Author**: [Name]
- **Date**: 2026-03-13
- **SIL Level**: 3

### Functions Implemented
| Function | Lines | CCN | Status |
|----------|-------|-----|--------|
| brake_init | 14 | 3 | Complete |
| brake_apply | 17 | 4 | Complete |
| brake_emergency | 13 | 3 | Complete |
| validate_speed | 5 | 2 | Complete |
| calculate_brake_level | 12 | 4 | Complete |
| transition_mode | 18 | 6 | Complete |

### MISRA C Compliance
- **Mandatory Violations**: 0
- **Required Violations**: 0
- **Advisory Violations**: 0
- **Deviations**: None

### Static Analysis Results
- **Cppcheck**: No errors
- **Compiler Warnings**: 0
- **Complexity**: Max CCN = 6 (within limit of 10)

### Traceability
- Design → Code: 100%
```

### 6.2 Add Inline Traceability Comments

```c
/**
 * @brief Apply brake based on speed
 * 
 * EN 50128 Traceability:
 * - Implements: DOC-10 MOD-001 Function brake_apply
 * - Requirement: DOC-6 REQ-FUNC-012 "System shall apply brake proportional to speed"
 * - Tested by: DOC-16 TEST-BRAKE-002
 * 
 * MISRA C:2012 Compliance:
 * - No violations
 * 
 * @param[in,out] state Pointer to brake state structure
 * @param[in]     speed Current speed in km/h [0..300]
 * @param[out]    level Calculated brake level [0..100]
 * @return SUCCESS or error code
 */
error_t brake_apply(brake_state_t* state, uint16_t speed, uint8_t* level)
{
    /* Implementation */
}
```

---

## Step 7: MISRA C Deviation Management

### 7.1 When Deviations are Acceptable

Deviations from **Required** or **Advisory** rules are permitted with:
1. Technical rationale
2. Safety impact analysis
3. Alternative measures
4. Approval from QUA

**Mandatory rules CANNOT be deviated** (SIL 3-4).

### 7.2 Document Deviation

Create `docs/misra_deviations/DEVIATION_LOG.md`:

```markdown
# MISRA C:2012 Deviation Log

## Deviation DEV-001

### Rule Violated
- **Rule**: MISRA C:2012 Rule 11.5 (Required)
- **Description**: "A conversion should not be performed from pointer to void into pointer to object"

### Location
- **File**: src/hardware_interface.c
- **Line**: 145
- **Function**: register_write()

### Code
```c
void register_write(uint32_t addr, uint32_t value)
{
    volatile uint32_t* reg = (uint32_t*)addr;  /* Deviation DEV-001 */
    *reg = value;
}
```

### Rationale
Hardware memory-mapped registers require casting integer address to pointer for direct register access. This is the only method to access hardware registers in embedded C.

### Safety Analysis
- **Risk**: Type confusion, invalid memory access
- **Mitigation**: 
  1. Address validated against valid register range
  2. Register addresses defined in hardware specification
  3. Read-back verification after write
  4. Memory protection unit (MPU) configured

### Alternative Considered
- Abstract register access through HAL → Rejected due to performance requirements

### Approval
- **Approved by**: QA Manager
- **Date**: 2026-03-13
- **Review Date**: 2026-06-13 (quarterly)
```

### 7.3 Inline Deviation Comment

```c
void register_write(uint32_t addr, uint32_t value)
{
    /* cppcheck-suppress misra-c2012-11.5 ; Deviation DEV-001 approved */
    volatile uint32_t* reg = (uint32_t*)addr;
    *reg = value;
}
```

---

## SIL-Dependent Requirements

### SIL 0-1: Advisory
- MISRA C compliance **recommended**
- Static analysis **recommended**
- Advisory rule deviations acceptable without formal approval

### SIL 2: Highly Recommended
- MISRA C compliance **highly recommended**
- Zero **mandatory** violations required
- **Required** rule deviations need rationale
- Static allocation only (no malloc/free)

### SIL 3-4: Mandatory
- MISRA C:2012 compliance **MANDATORY** (EN 50128 Table A.4)
- **ZERO mandatory violations** allowed
- Required rule deviations need:
  - Technical rationale
  - Safety analysis
  - QUA approval
- Advisory rule compliance **highly recommended**
- Static allocation only (no dynamic memory)
- Independent code review required

---

## Checklist

### Pre-Implementation
- [ ] Software Design Specification reviewed and understood
- [ ] Module interfaces defined
- [ ] Build environment configured
- [ ] Static analysis tools configured
- [ ] Traceability matrix initialized

### During Implementation
- [ ] Header file created with opaque types
- [ ] Source file follows template structure
- [ ] All functions have Doxygen comments
- [ ] NULL checks on all pointer parameters
- [ ] Fixed-width types used (uint8_t, uint16_t, etc.)
- [ ] Explicit casts for all type conversions
- [ ] Boolean types used for true/false
- [ ] No dynamic memory allocation (SIL 2+)
- [ ] Complexity within limits (CCN ≤ 10 for SIL 3-4)

### Post-Implementation
- [ ] Cppcheck analysis: 0 mandatory violations
- [ ] Compiler warnings: 0 with `-Wall -Wextra -Werror`
- [ ] Complexity check: All functions within limit
- [ ] Traceability updated (Design → Code)
- [ ] Implementation log documented
- [ ] MISRA deviations documented (if any)
- [ ] Code ready for unit testing

---

## Tools and Commands Reference

### Static Analysis
```bash
# Cppcheck with MISRA
cppcheck --addon=misra --enable=all --xml src/module.c 2> analysis.xml

# PC-lint Plus (if available)
pclp64 std.lnt src/module.c

# Clang Static Analyzer
scan-build -o analysis/ make
```

### Complexity Analysis
```bash
# Lizard (SIL 3-4: CCN ≤ 10)
lizard src/ --CCN 10 --warnings_only

# Full report
lizard src/ -o lizard_report.html
```

### Compiler Warnings
```bash
# GCC with maximum warnings
gcc -std=c99 -Wall -Wextra -Werror -pedantic \
    -Wconversion -Wsign-conversion -Wcast-qual \
    -c src/module.c -o build/module.o
```

### Traceability
```bash
# Link design to code
workspace.py trace import --file traces_code.csv --format csv --merge

# Check coverage
workspace.py trace check-gaps --phase implementation --sil 3

# Generate report
workspace.py trace report --from design --to code --format markdown
```

---

## Common Issues and Solutions

### Issue 1: Implicit Type Conversion (Rule 10.3)
**Problem:**
```c
uint16_t value16 = 1000;
uint8_t value8 = value16;  /* Implicit narrowing - violation */
```

**Solution:**
```c
uint16_t value16 = 1000U;
uint8_t value8;

if (value16 <= (uint16_t)UINT8_MAX) {
    value8 = (uint8_t)value16;  /* Explicit cast with check */
} else {
    /* Handle overflow */
    value8 = UINT8_MAX;
}
```

### Issue 2: Uninitialized Variable (Rule 9.1)
**Problem:**
```c
error_t function(void)
{
    uint32_t value;  /* Uninitialized */
    
    if (condition) {
        value = 10U;
    }
    
    return value;  /* Potentially uninitialized - violation */
}
```

**Solution:**
```c
error_t function(void)
{
    uint32_t value = 0U;  /* Always initialize */
    
    if (condition) {
        value = 10U;
    }
    
    return value;
}
```

### Issue 3: Mixed Sign Comparison (Rule 10.1)
**Problem:**
```c
int16_t temp = -10;
uint16_t threshold = 100U;

if (temp < threshold) {  /* Mixed sign - violation */
    /* ... */
}
```

**Solution:**
```c
int16_t temp = -10;
int16_t threshold = 100;  /* Same sign */

if (temp < threshold) {
    /* ... */
}
```

---

## Related Resources

- **[MISRA C Coding Patterns](../resources/misra-c-coding-patterns.md)** - Compliant code pattern library
- **[Defensive Coding Workflow](defensive-coding-implementation.md)** - Defensive programming patterns
- **[Code Review Checklist](../resources/code-review-checklist.md)** - Comprehensive review checklist
- **[Common Pitfalls](../resources/common-pitfalls.md)** - Common MISRA violations and fixes

---

## References

1. **EN 50128:2011** Section 7.4 (Component Design and Implementation)
2. **EN 50128:2011** Table A.4 (Technique 6: Design and Coding Standards - MANDATORY SIL 3-4)
3. **MISRA C:2012** Guidelines for the use of the C language in critical systems
4. **ISO/IEC 9899:2018** (C17 Standard)
5. **`std/EN50128-2011.md`** - Full EN 50128 standard (project repository)
6. **TOOLS.md** - Tool catalog with MISRA C checkers
