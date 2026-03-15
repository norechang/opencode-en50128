# EN 50128 Quick Start Guide

**Target Audience**: Software engineers new to EN 50128 railway software development  
**Estimated Time**: 30 minutes  
**Prerequisites**: Basic C programming knowledge, Linux/Unix environment

---

## 📚 What You'll Learn

1. Understand the EN 50128 V-Model development lifecycle
2. Navigate EN 50128 role-based agents
3. Build and verify a complete SIL 3 example
4. Follow the lifecycle workflow for a new project

---

## Step 1: Understand the V-Model Lifecycle (5 min)

### Read the Master Lifecycle Document

```bash
cat LIFECYCLE.md
```

**Key Concepts**:
- **V-Model**: Requirements → Design → Implementation → Testing → Integration → Validation
- **SIL Levels**: Safety Integrity Level (0-4), higher = more stringent requirements
- **Traceability**: Every requirement must trace to design, code, and test
- **Quality Gates**: Entry/exit criteria for each phase

### EN 50128 8-Phase Lifecycle

```
Phase 1: Software Planning
Phase 2: Software Requirements  ← Start here for new projects
Phase 3: Software Architecture & Design
Phase 4: Software Implementation & Testing
Phase 5: Software Integration
Phase 6: Software Validation
Phase 7: Software Verification (continuous)
Phase 8: Software Assessment
```

**Next**: Each phase has specific deliverables and quality gates.

---

## Step 2: Review the Train Door Control Example (10 min)

### Navigate to the Example

```bash
cd examples/train_door_control
ls -la
```

**Files**:
```
README.md              # Overview and architecture
docs/requirements.md   # Software Requirements Specification (SRS)
src/door_control.h     # Public API
src/door_control.c     # Implementation (MISRA C:2012)
src/error_types.h      # Error definitions
test/test_door_control.c  # Unit tests (Unity framework)
Makefile               # Build system
```

### Review Requirements (Phase 2)

```bash
cat docs/requirements.md
```

**Key Sections**:
1. **System Overview**: Train door safety requirements
2. **Functional Requirements**: REQ-FUNC-001 through REQ-FUNC-011
3. **Safety Requirements**: REQ-SAFE-001 through REQ-SAFE-007
4. **Traceability Matrix**: Mapping requirements to tests
5. **Hazard Analysis**: 5 identified hazards

**Example Requirement**:
```
REQ-FUNC-001: Door Opening Control
SIL: 3
Priority: CRITICAL
Description: The system SHALL allow doors to open ONLY when ALL of the 
following conditions are met:
  1. Train speed is 0 km/h (both sensors agree)
  2. Door open command is active
  3. Emergency mode is NOT active
  4. No error conditions are present
```

### Review Implementation (Phase 4)

```bash
cat src/door_control.h    # API
cat src/door_control.c    # Implementation
```

**Key C Programming Patterns**:
```c
// 1. MISRA C:2012 Compliance
#include <stdint.h>    // Fixed-width types
#include <stdbool.h>   // Boolean type
#include <stddef.h>    // NULL definition

// 2. Fixed-width types (mandatory)
uint8_t door_open_cmd;    // CORRECT
unsigned char door_open_cmd;  // FORBIDDEN

// 3. Static allocation only (SIL 2+)
static door_control_state_t state;  // CORRECT
door_control_state_t* state = malloc(...);  // FORBIDDEN

// 4. Defensive programming (mandatory)
if (inputs == NULL) {
    return ERROR_NULL_POINTER;  // Always check pointers
}

// 5. Explicit error handling (mandatory)
error_t err = validate_inputs(inputs);
if (err != ERROR_NONE) {
    return err;  // Always check returns
}
```

### Review Tests (Phase 4)

```bash
cat test/test_door_control.c
```

**Test Structure**:
```c
void test_door_opens_when_conditions_met(void) {
    // Arrange: Setup test state
    door_control_inputs_t inputs = {...};
    door_control_outputs_t outputs;
    
    // Act: Call function under test
    error_t err = door_control_cycle(&inputs, &outputs);
    
    // Assert: Verify results
    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL(1, outputs.door_open_cmd);
}
```

---

## Step 3: Build and Verify the Example (5 min)

### Clean Build

```bash
cd examples/train_door_control
make clean
```

### Run Unit Tests

```bash
make test
```

**Expected Output**:
```
Running test_door_control...
test_door_opens_when_conditions_met: PASS
test_door_stays_closed_when_speed_nonzero: PASS
...
15 Tests 0 Failures 0 Ignored
OK
```

### Generate Coverage Report

```bash
make coverage
```

**Expected Output**:
```
Overall coverage rate:
  lines......: 100.0%
  functions..: 100.0%
  branches...: 100.0%
```

**View HTML Report**:
```bash
xdg-open coverage_html/index.html  # Linux
open coverage_html/index.html      # macOS
```

### Run Static Analysis

```bash
make verify
```

**Expected Output**:
```
=== Cppcheck Static Analysis ===
Checking door_control.c...
[door_control.c:1]: (information) No violations found

=== Lizard Complexity Analysis ===
NLOC    CCN   Function
  45      8   door_control_cycle
  22      5   validate_inputs
  28      7   determine_door_commands

All functions have complexity ≤ 10 (SIL 3 compliant)
```

**SIL 3 Requirements Met**:
- ✅ 100% statement coverage
- ✅ 100% branch coverage
- ✅ Cyclomatic complexity ≤ 10
- ✅ MISRA C:2012 compliant
- ✅ No static analysis violations

---

## Step 4: Understand EN 50128 Roles (5 min)

### Read Role Definitions

```bash
cat docs/EN50128-Roles.md
```

**8 Role-Based Agents**:

| Agent | Role | Slash Command | When to Use |
|-------|------|---------------|-------------|
| **Requirements Engineer** | Requirements specification | `/req` | Phase 2: Define what the software must do |
| **Designer** | Architecture and design | `/des` | Phase 3: Define how the software is structured |
| **Implementer** | Code implementation | `/imp` | Phase 4: Write C code |
| **Tester** | Unit and integration testing | `/tst` | Phase 4/5: Test the code |
| **Safety Engineer** | Hazard analysis, FMEA, FTA | `/saf` | Throughout: Identify and mitigate hazards |
| **Verifier** | Static analysis, verification | `/ver` | Phase 7: Verify compliance |
| **Validator** | System testing, acceptance | `/val` | Phase 6: Validate against requirements |
| **Quality Assurance** | Code review, audits | `/qua` | Throughout: Ensure quality |

**Independence Requirements (SIL 3-4)**:
- **Verifier** MUST be independent from Designer/Implementer
- **Validator** MUST be independent from Developer team
- **Assessor** MUST be independent from entire project team

---

## Step 5: Follow a Complete Workflow (5 min)

### Example: Add New Feature "Platform Door Interlock"

#### Phase 2: Requirements (`/req`)

```bash
# Use requirements agent
/req

# Define new requirement
REQ-FUNC-012: Platform Door Sensor Interface
SIL: 3
Description: The system SHALL verify platform doors are closed 
before allowing train doors to open.

# Update traceability matrix
# Update hazard analysis
```

#### Phase 3: Design (`/des`)

```bash
# Use design agent
/des

# Design changes:
# 1. Add platform_door_closed input to door_control_inputs_t
# 2. Add validation in validate_inputs()
# 3. Add check in determine_door_commands()
# 4. Update cyclomatic complexity estimate
```

**Design Constraints (SIL 3)**:
- Cyclomatic complexity ≤ 10 for each function
- Static allocation only (no malloc/free)
- No recursion
- Defensive programming patterns

#### Phase 4: Implementation (`/imp`)

```bash
# Use implementation agent
/imp

# Implement code changes
# Write in MISRA C:2012 compliant style
# Add defensive checks
```

**C Code Example**:
```c
// In door_control.h
typedef struct {
    uint8_t door_open_cmd;
    uint8_t door_close_cmd;
    uint32_t speed_sensor_1_kmh;
    uint32_t speed_sensor_2_kmh;
    uint8_t door_closed_sensor_1;
    uint8_t door_closed_sensor_2;
    uint8_t door_locked_sensor_1;
    uint8_t door_locked_sensor_2;
    uint8_t emergency_mode;
    uint8_t platform_door_closed;  // NEW
} door_control_inputs_t;

// In door_control.c
static error_t validate_inputs(const door_control_inputs_t* inputs) {
    if (inputs == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    // Validate platform door sensor (NEW)
    if ((inputs->platform_door_closed != 0U) && 
        (inputs->platform_door_closed != 1U)) {
        return ERROR_INVALID_INPUT;
    }
    
    // ... rest of validation
}

static void determine_door_commands(
    const door_control_inputs_t* inputs,
    door_control_state_t* state,
    door_control_outputs_t* outputs
) {
    // Check platform door closed (NEW)
    if (inputs->platform_door_closed == 0U) {
        outputs->door_open_cmd = 0U;
        outputs->door_close_cmd = 1U;
        return;
    }
    
    // ... rest of logic
}
```

#### Phase 4: Testing (`/tst`)

```bash
# Use testing agent
/tst

# Write unit tests
# Aim for 100% coverage (SIL 3 requirement)
```

**Unit Test Example**:
```c
void test_door_blocked_when_platform_door_open(void) {
    // Arrange
    door_control_inputs_t inputs = {
        .door_open_cmd = 1,
        .speed_sensor_1_kmh = 0,
        .speed_sensor_2_kmh = 0,
        .door_closed_sensor_1 = 1,
        .door_closed_sensor_2 = 1,
        .door_locked_sensor_1 = 1,
        .door_locked_sensor_2 = 1,
        .emergency_mode = 0,
        .platform_door_closed = 0  // Platform door OPEN
    };
    
    door_control_state_t state = {0};
    door_control_outputs_t outputs = {0};
    
    // Act
    error_t err = door_control_cycle(&inputs, &outputs);
    
    // Assert
    TEST_ASSERT_EQUAL(ERROR_NONE, err);
    TEST_ASSERT_EQUAL(0, outputs.door_open_cmd);  // Door MUST stay closed
    TEST_ASSERT_EQUAL(1, outputs.door_close_cmd);
}
```

**Run Tests**:
```bash
make test
make coverage  # Verify 100% coverage
```

#### Phase 7: Verification (`/ver`)

```bash
# Use verification agent
/ver

# Run static analysis
make verify

# Check:
# - MISRA C compliance
# - Cyclomatic complexity ≤ 10
# - No violations
# - Coverage 100%
```

#### Phase 6: Validation (`/val`)

```bash
# Use validation agent
/val

# System testing
# Integration with platform door controller
# Operational scenarios
# Customer acceptance
```

---

## Key Takeaways

### ✅ DO (Mandatory for SIL 2+)

1. **Use MISRA C:2012** for all C code
2. **Static allocation only** (no malloc/free)
3. **Fixed-width types** (uint8_t, uint32_t)
4. **Validate all inputs** (NULL checks, range checks)
5. **Check all return values** (error_t everywhere)
6. **Achieve 100% coverage** (statement + branch for SIL 3)
7. **Keep complexity low** (≤10 for SIL 3)
8. **Maintain traceability** (requirement → design → code → test)
9. **Use defensive programming** (fail-safe defaults)
10. **Document everything** (SRS, SAS, SDS, test reports)

### ❌ DON'T (Forbidden for SIL 2+)

1. **No dynamic memory** (malloc, calloc, realloc, free)
2. **No recursion** (highly recommended to avoid for SIL 3-4)
3. **No undefined types** (use fixed-width types)
4. **No unchecked pointers** (always validate before use)
5. **No unchecked returns** (always check error codes)
6. **No unbounded loops** (all loops must terminate)
7. **No function pointers** (highly recommended to avoid for SIL 3-4)
8. **No complex functions** (complexity must be ≤10 for SIL 3)

### 📊 SIL 3 Compliance Checklist

- ✅ MISRA C:2012 compliance
- ✅ 100% statement coverage
- ✅ 100% branch coverage
- ✅ Cyclomatic complexity ≤ 10
- ✅ Static memory allocation only
- ✅ No recursion
- ✅ Defensive programming patterns
- ✅ Independent verification
- ✅ Traceability matrix (requirement ↔ code ↔ test)
- ✅ Static analysis (Cppcheck, PC-lint)
- ✅ Hazard analysis (FMEA/FTA)
- ✅ Code review (peer review + QA)

---

## Next Steps

### 1. Deep Dive into Lifecycle

```bash
# Read complete lifecycle documentation
cat LIFECYCLE.md

# Focus on quality gates and entry/exit criteria
grep -A 20 "Entry Criteria" LIFECYCLE.md
grep -A 20 "Exit Criteria" LIFECYCLE.md
```

### 2. Explore Skills

```bash
# Browse available skills
ls .opencode/skills/

# Read specific skill
cat .opencode/skills/en50128-requirements/SKILL.md
cat .opencode/skills/en50128-implementation/SKILL.md
```

### 3. Create Your Own Project

```bash
# Start with requirements
/req
# "Create requirements for a brake control system (SIL 3)"

# Follow the workflow:
# /req → /des → /saf → /imp → /tst → /ver → /val
```

### 4. Study EN 50128 Standard

```bash
# Read the actual standard (if available)
std/EN50128-2011.pdf

# Focus on:
# - Section 5.3: Roles and responsibilities
# - Section 7: Software development lifecycle
# - Table A.3: Techniques and measures (SIL 3)
# - Annex B: Role definitions
```

### 5. Learn MISRA C:2012

**Key Resources**:
- MISRA C:2012 Guidelines for the use of C in critical systems
- MISRA C:2012 Amendment 1 (2016)
- PC-lint Plus configuration files

**Common MISRA Rules**:
- Rule 1.3: No undefined behavior
- Rule 8.4: All functions must be declared before use
- Rule 10.1: Operands shall not be of inappropriate type
- Rule 17.7: Return value of non-void functions shall be used
- Rule 21.3: No malloc, calloc, realloc, free

---

## Troubleshooting

### Build Errors

**Problem**: `fatal error: unity.h: No such file or directory`

**Solution**:
```bash
# Install Unity test framework
git clone https://github.com/ThrowTheSwitch/Unity.git
export UNITY_ROOT=/path/to/Unity
```

**Problem**: `undefined reference to NULL`

**Solution**:
```c
// Add to top of .c file
#include <stddef.h>  // For NULL
```

### Test Failures

**Problem**: `ERROR_SENSOR_FAULT` when testing door open

**Solution**:
```c
// Ensure speed delta < 3 km/h per cycle
test_state.last_speed_kmh = 2;  // Close to current speed
inputs.speed_sensor_1_kmh = 0;
inputs.speed_sensor_2_kmh = 0;
```

**Problem**: Coverage < 100%

**Solution**:
```bash
# Generate coverage report to see uncovered lines
make coverage
xdg-open coverage_html/index.html

# Add tests for uncovered branches
```

### Static Analysis Warnings

**Problem**: Cppcheck warns about unused variables

**Solution**:
```c
// Use (void) cast to mark intentionally unused
(void)unused_param;
```

**Problem**: Complexity > 10

**Solution**:
```c
// Refactor into smaller functions
// Extract complex logic into helper functions
static bool is_speed_valid(const door_control_inputs_t* inputs) {
    // Speed validation logic
}
```

---

## Additional Resources

### Official Standards
- **EN 50128:2011** - Railway applications - Communication, signalling and processing systems - Software for railway control and protection systems
- **EN 50126:2017** - Railway applications - The specification and demonstration of Reliability, Availability, Maintainability and Safety (RAMS)
- **MISRA C:2012** - Guidelines for the use of the C language in critical systems
- **IEC 61508** - Functional safety of electrical/electronic/programmable electronic safety-related systems

### Tools
- **GCC** - GNU Compiler Collection (with -std=c11 -Wall -Wextra -Werror)
- **Unity** - Unit testing framework for C
- **gcov/lcov** - Code coverage analysis
- **Cppcheck** - Static analysis for C/C++
- **PC-lint Plus** - MISRA C checker (commercial)
- **Lizard** - Code complexity analyzer

### Online Resources
- **MISRA C Guidelines**: https://misra.org.uk/
- **Unity Test Framework**: https://github.com/ThrowTheSwitch/Unity
- **Railway Standards**: CENELEC (European Committee for Electrotechnical Standardization)

---

## Summary

You've learned:
1. ✅ EN 50128 V-Model lifecycle structure
2. ✅ How to navigate the train door control example
3. ✅ How to build, test, and verify EN 50128 software
4. ✅ Role-based agent workflow
5. ✅ SIL 3 compliance requirements
6. ✅ MISRA C:2012 coding patterns

**Next**: Start your own EN 50128-compliant project using the lifecycle workflow!

---

**Document Version**: 1.0  
**Last Updated**: 2026-02-06  
**Standard**: EN 50128:2011  
**Target SIL**: SIL 3  
**Language**: C (MISRA C:2012)
