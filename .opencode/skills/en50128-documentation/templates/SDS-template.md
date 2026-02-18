# Software Design Specification (SDS)

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 Section 7.4, Table A.4

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SDS-YYYY-NNN |
| **Version** | 0.1 (Draft) → 1.0 (Approved) |
| **Date** | YYYY-MM-DD |
| **Project** | [Project Name] |
| **SIL Level** | [0, 1, 2, 3, 4] |
| **Author** | [Name], Designer |
| **Reviewer** | [Name], [Role] |
| **Approver** | [Name], Project Manager |
| **Status** | [Draft \| Review \| Approved \| Baseline] |

---

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft | - |
| 1.0 | YYYY-MM-DD | [Name] | First approved version | [PM Name] |

---

## APPROVALS

**SIL 0-2 Requirements**: Author, Technical Reviewer, Project Manager  
**SIL 3-4 Requirements**: Author, Independent Reviewer, QA Manager, Project Manager

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author** | [Designer Name] | | |
| **Technical Reviewer** | [Reviewer Name] | | |
| **QA Manager** | [QA Name] | | |
| **Project Manager** | [PM Name] | | |

---

## 1. INTRODUCTION

### 1.1 Purpose

[State the purpose of this Software Design Specification. Example:]

This Software Design Specification (SDS) provides detailed design descriptions for all software modules in the [Project Name] system. It specifies module-level interfaces, data structures, algorithms, and error handling strategies needed for implementation in accordance with EN 50128:2011 Section 7.4.

**Intended Audience**:
- Software implementers (coders)
- Unit testers
- Code reviewers
- Verification team

### 1.2 Scope

[Define the scope of the detailed design. Example:]

This SDS covers detailed design for all modules defined in the Software Architecture Specification (SAS), including:
- Module-level function specifications (APIs)
- Internal data structures
- Algorithm descriptions (pseudocode or flowcharts)
- Error handling and recovery
- C language implementation details

**Out of Scope**:
- High-level architecture (covered by SAS)
- Requirements (covered by SRS)
- Actual source code (covered by implementation phase)

### 1.3 SIL Classification

**Target SIL Level**: [0, 1, 2, 3, 4]

**EN 50128 Design Techniques** (Table A.4):

| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Applied |
|-----------|-------|---------|---------|---------|
| Structured Methodology | R | HR | **M** | **Yes** |
| Modular Approach | HR | **M** | **M** | **Yes** |
| Design and Coding Standards | HR | HR | **M** | **Yes** (MISRA C:2012) |
| Structured Programming | R | HR | **M** | **Yes** |

**Key Design Constraints (SIL-specific)**:
- **SIL 2+**: MISRA C:2012 compliance **MANDATORY**
- **SIL 2+**: Static memory allocation **MANDATORY**
- **SIL 2+**: Design and coding standards **MANDATORY**
- **SIL 3-4**: Structured programming **MANDATORY**
- **SIL 3-4**: Complexity ≤ 10 **REQUIRED**

### 1.4 Definitions and Acronyms

| Term | Definition |
|------|------------|
| **API** | Application Programming Interface (public functions) |
| **ISR** | Interrupt Service Routine |
| **WCET** | Worst-Case Execution Time |
| **Complexity** | Cyclomatic complexity (McCabe metric) |

### 1.5 References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems |
| **[SRS]** | Software Requirements Specification, DOC-SRS-YYYY-NNN |
| **[SAS]** | Software Architecture Specification, DOC-SAS-YYYY-NNN |
| **[MISRAC]** | MISRA C:2012 Guidelines for the use of the C language in critical systems |

### 1.6 Overview

[Provide a brief overview of the document structure.]

---

## 2. DESIGN OVERVIEW

### 2.1 Module Summary

| Module ID | Module Name | SIL | C Files | Complexity | Status |
|-----------|-------------|-----|---------|------------|--------|
| MOD-CTRL | Control Module | [0-4] | control.h, control.c | ≤ 10 | Designed |
| MOD-SAFE | Safety Module | 4 | safety.h, safety.c | ≤ 10 | Designed |
| MOD-SENS | Sensor HAL | [0-4] | sensor_hal.h, sensor_hal.c | ≤ 8 | Designed |
| MOD-ACT | Actuator HAL | [0-4] | actuator_hal.h, actuator_hal.c | ≤ 8 | Designed |
| [Add more modules] | | | | | |

### 2.2 Design Conventions

**Naming Conventions**:
- Module prefix: `module_` (e.g., `control_init`, `safety_monitor`)
- Types: `module_type_t` (e.g., `control_state_t`)
- Constants: `MODULE_CONSTANT` (e.g., `CONTROL_MAX_RETRIES`)
- Static functions: `static module_private_function(...)`

**File Organization**:
- Header file (`.h`): Public API, type definitions, constants
- Source file (`.c`): Implementation, static (private) functions

**Commenting Standards**:
- Doxygen-style comments for all public functions
- Inline comments for complex logic

---

## 3. MODULE DESIGNS

### 3.1 MODULE: Control Module

**Module ID**: MOD-CTRL  
**SIL Level**: [0-4]  
**Implements Requirements**: REQ-FUNC-001, REQ-FUNC-002, REQ-FUNC-003, REQ-PERF-001  
**C Files**: `control.h`, `control.c`

---

#### 3.1.1 Purpose

The Control Module implements the main control logic for [specific functionality, e.g., door control]. It processes commands from the train control system, monitors sensor inputs, and generates actuator commands based on a state machine.

---

#### 3.1.2 Interfaces

**Public Functions** (API in `control.h`):

```c
/**
 * @brief Initialize control module
 * @pre System hardware initialized
 * @post Control module ready, state = IDLE
 * @return SUCCESS or error code
 */
error_t control_init(void);

/**
 * @brief Main control processing function (call every 50ms)
 * @param[in] sensor_data Current sensor readings
 * @param[in] cmd Command from train control system
 * @param[out] actuator_cmd Generated actuator commands
 * @return SUCCESS or error code
 */
error_t control_process(
    const sensor_data_t* sensor_data,
    const train_control_msg_t* cmd,
    actuator_cmd_t* actuator_cmd
);

/**
 * @brief Get current control state
 * @return Current state
 */
control_state_t control_get_state(void);

/**
 * @brief Get last error code
 * @return Error code (0 = no error)
 */
uint8_t control_get_error(void);
```

**Dependencies** (modules called by Control Module):
- Sensor HAL: `sensor_hal_read()` - Read sensor data
- Actuator HAL: `actuator_hal_write()` - Write actuator commands
- Safety Module: `safety_get_interlock()` - Check safety interlocks

---

#### 3.1.3 Data Structures

**State Enumeration**:
```c
typedef enum {
    CONTROL_STATE_IDLE,         ///< Idle, waiting for command
    CONTROL_STATE_OPENING,      ///< Door opening in progress
    CONTROL_STATE_OPEN,         ///< Door fully open
    CONTROL_STATE_CLOSING,      ///< Door closing in progress
    CONTROL_STATE_CLOSED,       ///< Door fully closed
    CONTROL_STATE_FAULT         ///< Fault detected
} control_state_t;
```

**Module State Structure** (internal, static):
```c
typedef struct {
    control_state_t state;          ///< Current state
    control_state_t prev_state;     ///< Previous state (for fault recovery)
    uint32_t state_entry_time_ms;   ///< Timestamp when entered current state
    uint32_t timeout_ms;            ///< Timeout for current operation
    uint8_t error_code;             ///< Last error code
    uint8_t retry_count;            ///< Number of retries attempted
} control_module_state_t;

static control_module_state_t g_control_state;  // Hidden from other modules
```

**Constants**:
```c
#define CONTROL_DOOR_OPEN_TIMEOUT_MS    2000U   ///< Max time to open door
#define CONTROL_DOOR_CLOSE_TIMEOUT_MS   3000U   ///< Max time to close door
#define CONTROL_MAX_RETRIES             3U      ///< Max retry attempts
```

---

#### 3.1.4 Algorithm Description

**State Machine** (simplified):

```
┌──────┐  door_open_cmd  ┌─────────┐  door_fully_open  ┌──────┐
│ IDLE │────────────────>│ OPENING │──────────────────>│ OPEN │
└──────┘                 └─────────┘                   └──────┘
   ▲                          │                            │
   │                          │ timeout                    │ door_close_cmd
   │                          ▼                            ▼
   │                      ┌───────┐                   ┌─────────┐
   └──────────────────────│ FAULT │<──────────────────│ CLOSING │
                          └───────┘  timeout          └─────────┘
                                                           │
                                                           │ door_fully_closed
                                                           ▼
                                                       ┌────────┐
                                                       │ CLOSED │
                                                       └────────┘
```

**Main Processing Logic** (pseudocode):

```
FUNCTION control_process(sensor_data, cmd, actuator_cmd):
    // 1. Validate inputs (defensive programming)
    IF sensor_data == NULL OR cmd == NULL OR actuator_cmd == NULL THEN
        RETURN ERROR_NULL_POINTER
    
    // 2. Check safety interlocks
    safety_status = safety_get_interlock()
    IF safety_status.emergency_stop THEN
        control_enter_fault_state(ERROR_EMERGENCY_STOP)
        actuator_cmd->door_pwm_duty_cycle = 0
        RETURN SUCCESS
    
    // 3. State machine processing
    SWITCH g_control_state.state:
        
        CASE CONTROL_STATE_IDLE:
            IF cmd->door_open_cmd == true AND is_safe_to_open(sensor_data) THEN
                control_transition_to_opening()
            ELSE IF cmd->door_close_cmd == true AND is_safe_to_close(sensor_data) THEN
                control_transition_to_closing()
            
        CASE CONTROL_STATE_OPENING:
            actuator_cmd->door_pwm_duty_cycle = 80  // 80% PWM for opening
            
            IF sensor_data->door_position_pct >= 95 THEN
                control_transition_to_open()
            ELSE IF timeout_exceeded(CONTROL_DOOR_OPEN_TIMEOUT_MS) THEN
                control_enter_fault_state(ERROR_TIMEOUT)
            ELSE IF sensor_data->obstacle_detected THEN
                control_transition_to_closing()  // Reverse direction
            
        CASE CONTROL_STATE_OPEN:
            actuator_cmd->door_pwm_duty_cycle = 0  // No motion
            
            IF cmd->door_close_cmd == true THEN
                control_transition_to_closing()
            
        CASE CONTROL_STATE_CLOSING:
            actuator_cmd->door_pwm_duty_cycle = 60  // 60% PWM for closing
            
            IF sensor_data->door_position_pct <= 5 THEN
                control_transition_to_closed()
            ELSE IF timeout_exceeded(CONTROL_DOOR_CLOSE_TIMEOUT_MS) THEN
                control_enter_fault_state(ERROR_TIMEOUT)
            ELSE IF sensor_data->obstacle_detected THEN
                control_transition_to_opening()  // Reopen
            
        CASE CONTROL_STATE_CLOSED:
            actuator_cmd->door_pwm_duty_cycle = 0  // No motion
            actuator_cmd->door_lock_enable = true  // Lock engaged
            
            IF cmd->door_open_cmd == true THEN
                control_transition_to_opening()
            
        CASE CONTROL_STATE_FAULT:
            actuator_cmd->door_pwm_duty_cycle = 0  // Fail-safe: no motion
            actuator_cmd->door_lock_enable = true  // Fail-safe: locked
            
            IF cmd->fault_clear_cmd == true AND retry_count < CONTROL_MAX_RETRIES THEN
                control_transition_to_idle()
                retry_count++
    
    RETURN SUCCESS
```

---

#### 3.1.5 Error Handling

**Error Codes**:
```c
#define CONTROL_ERROR_NONE              0U
#define CONTROL_ERROR_TIMEOUT           1U
#define CONTROL_ERROR_OBSTACLE          2U
#define CONTROL_ERROR_EMERGENCY_STOP    3U
#define CONTROL_ERROR_SENSOR_FAULT      4U
#define CONTROL_ERROR_INVALID_PARAM     5U
```

**Error Handling Strategy**:
1. **Timeout**: Enter FAULT state, raise alarm, allow retry (up to MAX_RETRIES)
2. **Obstacle**: Immediately reverse direction (if opening, close; if closing, open)
3. **Emergency Stop**: Immediately stop all motion, enter safe state
4. **Sensor Fault**: Use last valid value for 1 cycle, then enter FAULT state if persistent

**Recovery**: Manual or automatic retry (based on error severity)

---

#### 3.1.6 Complexity Analysis

**Estimated Cyclomatic Complexity**:
- `control_init()`: 3
- `control_process()`: 15 (main state machine)
- `control_transition_to_opening()`: 2
- `control_transition_to_closing()`: 2
- [Other functions]: < 5

**Total Module Complexity**: ~30  
**Max Function Complexity**: 15

**Complexity Reduction Plan** (if exceeds limit for SIL 3-4):
- Split `control_process()` into subfunctions per state
- Target: Each function ≤ 10 complexity

---

#### 3.1.7 Testing Strategy

**Unit Tests** (test cases):
- TC-UNIT-CTRL-001: Test initialization
- TC-UNIT-CTRL-002: Test IDLE → OPENING transition
- TC-UNIT-CTRL-003: Test OPENING → OPEN transition
- TC-UNIT-CTRL-004: Test timeout handling in OPENING state
- TC-UNIT-CTRL-005: Test obstacle detection and reversal
- [Additional test cases for all states and transitions]

**Coverage Target**: 100% statement, 100% branch (SIL 2+)

---

### 3.2 MODULE: Safety Module

**Module ID**: MOD-SAFE  
**SIL Level**: 4 (Safety-Critical)  
**Implements Requirements**: REQ-SAFE-001, REQ-SAFE-002, REQ-SAFE-003  
**C Files**: `safety.h`, `safety.c`

---

#### 3.2.1 Purpose

The Safety Module implements safety-critical functions including speed interlock, emergency stop detection, fault monitoring, and watchdog refresh. This is a SIL 4 module requiring independent verification and rigorous testing.

---

#### 3.2.2 Interfaces

**Public Functions** (API in `safety.h`):

```c
/**
 * @brief Initialize safety module
 * @pre Hardware watchdog configured
 * @post Safety module ready, all interlocks active
 * @return SUCCESS or error code
 */
error_t safety_init(void);

/**
 * @brief Monitor safety conditions (call every 10ms - CRITICAL)
 * @param[in] sensor_data Current sensor readings (primary and redundant)
 * @return SUCCESS or error code
 */
error_t safety_monitor(const sensor_data_t* sensor_data);

/**
 * @brief Refresh hardware watchdog (call every 100ms - CRITICAL)
 * @pre safety_monitor() called recently (< 100ms ago)
 * @post Watchdog timer refreshed
 */
void safety_watchdog_refresh(void);

/**
 * @brief Get safety interlock status
 * @return Interlock status structure
 */
safety_interlock_t safety_get_interlock(void);

/**
 * @brief Get active fault codes
 * @return Fault status structure
 */
fault_status_t safety_get_faults(void);
```

---

#### 3.2.3 Data Structures

**Safety Interlock Structure**:
```c
typedef struct {
    bool emergency_stop_active;     ///< true = emergency stop active
    bool speed_interlock_active;    ///< true = doors locked due to speed
    bool fault_detected;            ///< true = safety fault detected
    uint8_t fault_code;             ///< Active fault code (if any)
} safety_interlock_t;
```

**Fault Status Structure**:
```c
typedef struct {
    uint8_t speed_sensor_mismatch:1;    ///< Redundant sensors disagree
    uint8_t emergency_stop:1;           ///< Emergency stop active
    uint8_t watchdog_timeout:1;         ///< Watchdog timeout occurred
    uint8_t communication_loss:1;       ///< CAN communication lost
    uint8_t reserved:4;                 ///< Reserved for future use
} fault_status_t;
```

**Module State** (internal, static):
```c
typedef struct {
    safety_interlock_t interlock;
    fault_status_t faults;
    uint32_t last_monitor_time_ms;      ///< Timestamp of last safety_monitor() call
    uint32_t watchdog_refresh_count;    ///< Number of watchdog refreshes
    uint16_t speed_primary_kmh;         ///< Primary speed sensor reading
    uint16_t speed_secondary_kmh;       ///< Secondary speed sensor reading
} safety_module_state_t;

static safety_module_state_t g_safety_state;
```

**Constants**:
```c
#define SAFETY_SPEED_THRESHOLD_KMH      50U     ///< Speed above which doors must be locked (5.0 km/h * 10)
#define SAFETY_SPEED_MISMATCH_THRESHOLD 100U    ///< Max difference between sensors (10.0 km/h * 10)
#define SAFETY_WATCHDOG_PERIOD_MS       100U    ///< Watchdog refresh period
#define SAFETY_MONITOR_TIMEOUT_MS       20U     ///< Max time between safety_monitor() calls
```

---

#### 3.2.4 Algorithm Description

**Speed Interlock Logic** (REQ-SAFE-001):

```
FUNCTION safety_check_speed_interlock(sensor_data):
    // Read redundant speed sensors
    speed_primary = sensor_data->speed_primary_kmh
    speed_secondary = sensor_data->speed_secondary_kmh
    
    // Check sensor disagreement (fault detection)
    speed_diff = ABS(speed_primary - speed_secondary)
    IF speed_diff > SAFETY_SPEED_MISMATCH_THRESHOLD THEN
        g_safety_state.faults.speed_sensor_mismatch = 1
        // Fail-safe: Lock doors
        g_safety_state.interlock.speed_interlock_active = true
        RETURN
    
    // Use maximum speed (fail-safe: if either sensor shows high speed, lock doors)
    speed_max = MAX(speed_primary, speed_secondary)
    
    // Apply speed interlock
    IF speed_max > SAFETY_SPEED_THRESHOLD_KMH THEN
        g_safety_state.interlock.speed_interlock_active = true
    ELSE
        g_safety_state.interlock.speed_interlock_active = false
```

**Watchdog Refresh Logic** (REQ-SAFE-002):

```
FUNCTION safety_watchdog_refresh():
    // Check that safety_monitor() was called recently
    time_since_monitor = current_time_ms - g_safety_state.last_monitor_time_ms
    
    IF time_since_monitor > SAFETY_MONITOR_TIMEOUT_MS THEN
        // Safety monitor not running - DO NOT refresh watchdog
        // Watchdog will timeout and reset system (fail-safe)
        RETURN
    
    // Refresh external hardware watchdog
    HARDWARE_WATCHDOG_REFRESH()
    
    // Increment refresh counter (for diagnostics)
    g_safety_state.watchdog_refresh_count++
```

---

#### 3.2.5 Error Handling

**Fault Detection**:
- Speed sensor mismatch → Set fault flag, activate speed interlock (fail-safe)
- Emergency stop signal → Immediately activate emergency interlock
- Communication loss → Timeout detection, activate fail-safe mode
- Watchdog timeout → Hardware resets system (external to software)

**Fail-Safe Principle**: In case of any doubt or fault, assume worst case and activate interlocks.

---

#### 3.2.6 Complexity Analysis

**Estimated Cyclomatic Complexity**:
- `safety_init()`: 3
- `safety_monitor()`: 8
- `safety_watchdog_refresh()`: 4
- `safety_check_speed_interlock()`: 5
- [Other functions]: < 5

**Total Module Complexity**: ~25  
**Max Function Complexity**: 8

**Compliance**: All functions ≤ 10 complexity ✓ (SIL 4 requirement)

---

#### 3.2.7 Testing Strategy

**Unit Tests**:
- TC-UNIT-SAFE-001: Test speed interlock activation
- TC-UNIT-SAFE-002: Test speed sensor mismatch detection
- TC-UNIT-SAFE-003: Test watchdog refresh nominal case
- TC-UNIT-SAFE-004: Test watchdog refresh blocked when monitor not running
- TC-UNIT-SAFE-005: Test emergency stop detection

**Fault Injection Tests** (SIL 4 requirement):
- FI-001: Inject sensor mismatch, verify fail-safe response
- FI-002: Inject watchdog timeout, verify system reset
- FI-003: Inject communication loss, verify fail-safe mode

**Coverage Target**: 100% statement, 100% branch, 100% condition (SIL 4 requirement per Table A.21)

---

### 3.3 MODULE: [Additional Modules]

[Repeat structure above for each module:
- Sensor HAL Module
- Actuator HAL Module
- Communication HAL Module
- Diagnostic Module
- etc.]

---

## 4. TRACEABILITY

### 4.1 Requirements to Design Traceability

| Requirement | Architecture (SAS) | Design (SDS) | Function | Estimated Complexity |
|-------------|-------------------|--------------|----------|---------------------|
| REQ-FUNC-001 | MOD-CTRL | Section 3.1 | `control_process()` | 15 |
| REQ-FUNC-002 | MOD-CTRL | Section 3.1 | `control_process()` | 15 |
| REQ-SAFE-001 | MOD-SAFE | Section 3.2 | `safety_check_speed_interlock()` | 5 |
| REQ-SAFE-002 | MOD-SAFE | Section 3.2 | `safety_watchdog_refresh()` | 4 |
| [Add all requirements] | | | | |

**Traceability Completeness**: 100% of requirements SHALL be traced to design elements (functions).

### 4.2 Design to Test Traceability

| Module | Function | Unit Test Cases | Complexity | Coverage Target |
|--------|----------|-----------------|------------|-----------------|
| MOD-CTRL | `control_process()` | TC-UNIT-CTRL-001 to 010 | 15 | 100% statement, 100% branch |
| MOD-SAFE | `safety_monitor()` | TC-UNIT-SAFE-001 to 005 | 8 | 100% statement, branch, condition |
| [Add all modules] | | | | |

---

## 5. DESIGN QUALITY METRICS

### 5.1 Complexity Summary

| Module | Total Complexity | Max Function Complexity | Target (SIL 3-4) | Status |
|--------|------------------|------------------------|------------------|--------|
| MOD-CTRL | 30 | 15 | ≤ 10 per function | ⚠ Refactor needed |
| MOD-SAFE | 25 | 8 | ≤ 10 per function | ✓ Compliant |
| MOD-SENS | 15 | 6 | ≤ 10 per function | ✓ Compliant |
| MOD-ACT | 18 | 7 | ≤ 10 per function | ✓ Compliant |
| **TOTAL** | **88** | **15** | **≤ 10** | **1 module needs refactoring** |

**Action Items**:
- MOD-CTRL: Refactor `control_process()` to split state handling into separate functions
- Target: Reduce `control_process()` complexity from 15 to ≤ 10

### 5.2 Module Coupling

| Module | Depends On | Depended On By | Coupling Level |
|--------|------------|----------------|----------------|
| MOD-CTRL | MOD-SAFE, MOD-SENS, MOD-ACT | None | Medium |
| MOD-SAFE | MOD-SENS | MOD-CTRL | Low |
| MOD-SENS | None (HAL) | MOD-CTRL, MOD-SAFE | Low |
| MOD-ACT | None (HAL) | MOD-CTRL | Low |

**Design Goal**: Minimize coupling (ideally ≤ 3 dependencies per module)

---

## 6. DESIGN REVIEW CHECKLIST

### 6.1 General Design Quality

- [ ] All modules from SAS have detailed designs
- [ ] All public functions documented (API comments)
- [ ] All data structures defined
- [ ] All algorithms described (pseudocode or flowcharts)
- [ ] Error handling specified for all functions
- [ ] Complexity within limits (≤ 10 for SIL 3-4)

### 6.2 EN 50128 Compliance (SIL-Specific)

- [ ] Modular approach used (mandatory SIL 2+)
- [ ] Static memory allocation only (mandatory SIL 2+)
- [ ] No recursion (highly recommended SIL 3-4)
- [ ] Defensive programming patterns (highly recommended SIL 3-4)
- [ ] MISRA C compliance planned (mandatory SIL 2+)
- [ ] Structured programming (mandatory SIL 3-4)
- [ ] Design and coding standards defined (mandatory SIL 3-4)

### 6.3 Traceability

- [ ] All requirements traced to design elements (100%)
- [ ] All design elements traced to test cases (100%)
- [ ] Traceability matrix up-to-date (RTM)

---

## 7. COMPLIANCE MATRIX

### 7.1 EN 50128 Section 7.4 Compliance

| Requirement | Section | Evidence | Status |
|-------------|---------|----------|--------|
| **Detailed design established** | 7.4.2 | This document (SDS) | ✓ |
| **Modular approach (M SIL 2+)** | Table A.4 | Section 3 (per-module design) | ✓ |
| **Structured programming (M SIL 3-4)** | Table A.4 | Section 3 (algorithms) | ✓ |
| **Design and coding standards (M SIL 3-4)** | Table A.4 | MISRA C:2012 compliance planned | ✓ |
| **Complexity within limits** | Table A.4 | Section 5.1 (complexity summary) | ⚠ (1 module needs refactoring) |

### 7.2 EN 50128 Table A.4 Compliance (Design Techniques)

| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Applied |
|-----------|-------|---------|---------|---------|
| Structured Methodology | R | HR | **M** | ✓ Yes |
| Modular Approach | HR | **M** | **M** | ✓ Yes |
| Design and Coding Standards | HR | HR | **M** | ✓ Yes (MISRA C:2012) |
| Structured Programming | R | HR | **M** | ✓ Yes |

---

## 8. REFERENCES

### 8.1 Normative References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems |
| **[MISRAC]** | MISRA C:2012 Guidelines for the use of the C language in critical systems |

### 8.2 Project References

| Reference | Document |
|-----------|----------|
| **[SRS]** | Software Requirements Specification, DOC-SRS-YYYY-NNN |
| **[SAS]** | Software Architecture Specification, DOC-SAS-YYYY-NNN |

---

## APPENDICES

### Appendix A: Function Design Template

```markdown
#### Function: module_function_name

**Prototype**:
\```c
error_t module_function_name(const input_t* input, output_t* output);
\```

**Purpose**: [Brief description]

**Parameters**:
- `input` [in]: [Description]
- `output` [out]: [Description]

**Return**: SUCCESS or error code

**Preconditions**: [State before function called]

**Postconditions**: [State after function returns]

**Algorithm**:
\```
PSEUDOCODE HERE
\```

**Error Handling**:
- [Error condition 1] → [Response]
- [Error condition 2] → [Response]

**Complexity**: [Estimated cyclomatic complexity]

**Test Cases**: [List test case IDs]
```

### Appendix B: State Machine Template

```markdown
#### State Machine: [Name]

**States**:
- STATE_1: [Description]
- STATE_2: [Description]

**Transitions**:
- STATE_1 → STATE_2: [Trigger condition]

**State Diagram**:
\```
[ASCII art or reference to external diagram]
\```

**Complexity**: [Estimated complexity]
```

---

## DOCUMENT HISTORY

This document is maintained under configuration control per SCMP. All changes SHALL be approved by the Change Control Board (CCB).

**Current Version**: [Version from header]  
**Last Updated**: [Date from header]  
**Next Review**: [Date - recommended before implementation phase]

---

**END OF DOCUMENT**
