# Software Architecture Specification (SAS)

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 Section 7.3, Table A.3

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | [DOC-XXX-YYYY-NNN] |
| **Version** | [X.Y] |
| **Date** | [YYYY-MM-DD] |
| **Project** | [Project Name] |
| **SIL Level** | [0, 1, 2, 3, or 4] |
| **Author** | [Name], [Role] |
| **Reviewer** | [Name], [Role] |
| **Approver** | [Name], [Role] |
| **Status** | [Draft \| Review \| Approved \| Baseline] |

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft | - |

## APPROVALS

**SIL 0-2 Requirements**: Author, Technical Reviewer, QA Manager, Project Manager  
**SIL 3-4 Requirements**: Author, Technical Reviewer (independent), QA Manager, Safety Manager, Independent Verifier, Independent Validator, Assessor, Project Manager

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author** | [Name] | | YYYY-MM-DD |
| **Technical Reviewer** | [Name] | | YYYY-MM-DD |
| **QA Manager** | [Name] | | YYYY-MM-DD |
| **Safety Manager** (SIL 2+) | [Name] | | YYYY-MM-DD |
| **Project Manager** | [Name] | | YYYY-MM-DD |
| **Independent Verifier** (SIL 3-4) | [Name] | | YYYY-MM-DD |
| **Independent Validator** (SIL 3-4) | [Name] | | YYYY-MM-DD |
| **Assessor** (SIL 3-4) | [Name] | | YYYY-MM-DD |

---

## 1. INTRODUCTION

### 1.1 Purpose

[State the purpose of this Software Architecture Specification. Example:]

This Software Architecture Specification (SAS) defines the high-level software architecture for the [Project Name] system. It describes the architectural design, module decomposition, interfaces, and design patterns used to implement the software requirements in accordance with EN 50128:2011 Section 7.3.

**Intended Audience**:
- Software designers and implementers
- Verification and validation teams
- Safety engineers
- Project management

### 1.2 Scope

[Define the scope of the architecture. Example:]

This SAS covers the complete software architecture for [Project Name], including:
- Logical architecture (module decomposition)
- Process architecture (task allocation, scheduling)
- Data architecture (data structures, data flow)
- Safety architecture (fault detection, redundancy)
- C implementation patterns

**Out of Scope**:
- Detailed design (covered by Software Design Specification)
- Hardware architecture (covered by Hardware Architecture Specification)

### 1.3 SIL Classification

**Target SIL Level**: [0, 1, 2, 3, 4]

**EN 50128 Architecture Techniques** (Table A.3):

| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Applied |
|-----------|-------|---------|---------|---------|
| Defensive Programming | - | HR | HR | **Yes** |
| Structured Methodology | R | HR | **M** | **Yes** |
| Modular Approach | HR | **M** | **M** | **Yes** |
| Information Encapsulation | R | HR | HR | **Yes** |

**Key Architectural Constraints (SIL-specific)**:
- **SIL 2+**: Modular approach **MANDATORY**
- **SIL 2+**: Static memory allocation **MANDATORY**
- **SIL 3-4**: No recursion **HIGHLY RECOMMENDED**
- **SIL 3-4**: Defensive programming **HIGHLY RECOMMENDED**
- **SIL 3-4**: Complexity ≤ 10 **REQUIRED**

### 1.4 Definitions and Acronyms

| Term | Definition |
|------|------------|
| **Module** | Self-contained software component with defined interfaces |
| **Component** | Collection of related modules implementing a feature |
| **Interface** | Defined set of functions/data for module communication |
| **RTOS** | Real-Time Operating System |
| **ISR** | Interrupt Service Routine |

### 1.5 References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems |
| **[SRS]** | Software Requirements Specification, DOC-SRS-YYYY-NNN |
| **[MISRAC]** | MISRA C:2012 Guidelines for the use of the C language in critical systems |

### 1.6 Overview

[Provide a brief overview of the document structure.]

---

## 2. ARCHITECTURE OVERVIEW

### 2.1 System Context Diagram

[Provide context diagram showing software within system]

```
┌────────────────────────────────────────────────────┐
│              Railway Control System                │
│                                                    │
│   ┌────────────────────────────────────────┐     │
│   │   [Software Name]                      │     │
│   │   ┌──────────────────────────────┐    │     │
│   │   │  Application Layer           │    │     │
│   │   │  ┌────┐ ┌────┐ ┌────┐       │    │     │
│   │   │  │Mod1│ │Mod2│ │Mod3│       │    │     │
│   │   │  └────┘ └────┘ └────┘       │    │     │
│   │   └──────────────────────────────┘    │     │
│   │   ┌──────────────────────────────┐    │     │
│   │   │  Hardware Abstraction Layer  │    │     │
│   │   └──────────────────────────────┘    │     │
│   └────────────────────────────────────────┘     │
│            ▲         ▲         ▲                  │
└────────────┼─────────┼─────────┼──────────────────┘
             │         │         │
         [Sensor]  [Actuator] [Network]
```

### 2.2 Architecture Goals

The architecture is designed to achieve the following goals:

1. **Safety**: Fail-safe design, fault detection, hazard mitigation
2. **Modularity**: Clear module boundaries, defined interfaces (mandatory SIL 2+)
3. **Testability**: Independent module testing, high coverage
4. **Maintainability**: Clear structure, information hiding, low complexity
5. **Performance**: Meet timing requirements, low CPU/memory usage
6. **Reliability**: Error handling, defensive programming, watchdog monitoring
7. **Certifiability**: EN 50128 compliance, traceability, evidence collection

### 2.3 Architecture Patterns

**Primary Patterns**:
- **Layered Architecture**: Separation of concerns (application, hardware abstraction)
- **Modular Decomposition**: Independent, cohesive modules (mandatory SIL 2+)
- **State Machine Pattern**: For control logic (recommended for safety-critical)
- **Defensive Programming**: Input validation, error checking (HR SIL 3-4)

**Avoided Patterns** (per EN 50128 constraints):
- ❌ Dynamic memory allocation (forbidden SIL 2+)
- ❌ Recursion (not recommended SIL 3-4)
- ❌ Function pointers (use with caution, SIL 3-4)

---

## 3. LOGICAL ARCHITECTURE

### 3.1 Module Decomposition

The software is decomposed into the following modules:

```
┌──────────────────────────────────────────────┐
│         Application Layer                    │
│  ┌────────────┐  ┌────────────┐             │
│  │  Control   │  │  Safety    │             │
│  │  Module    │  │  Module    │             │
│  └────────────┘  └────────────┘             │
│  ┌────────────┐  ┌────────────┐             │
│  │ Monitoring │  │ Diagnostic │             │
│  │  Module    │  │  Module    │             │
│  └────────────┘  └────────────┘             │
└──────────────────────────────────────────────┘
┌──────────────────────────────────────────────┐
│      Hardware Abstraction Layer (HAL)        │
│  ┌────────────┐  ┌────────────┐             │
│  │   Sensor   │  │  Actuator  │             │
│  │    HAL     │  │    HAL     │             │
│  └────────────┘  └────────────┘             │
│  ┌────────────┐  ┌────────────┐             │
│  │   Timer    │  │   Comm     │             │
│  │    HAL     │  │    HAL     │             │
│  └────────────┘  └────────────┘             │
└──────────────────────────────────────────────┘
```

### 3.2 Module Descriptions

#### 3.2.1 Control Module

**Module ID**: MOD-CTRL  
**SIL Level**: [0-4]  
**Implements**: REQ-FUNC-001, REQ-FUNC-002, REQ-FUNC-003

**Purpose**: Implements main control logic for [specific functionality, e.g., door control]

**Responsibilities**:
- Process control commands from train control system
- Execute control state machine
- Generate actuator commands
- Monitor system state

**Interfaces**:
- **Input**: `train_control_msg_t` (CAN messages from train control)
- **Input**: `sensor_data_t` (sensor readings from Sensor HAL)
- **Output**: `actuator_cmd_t` (commands to Actuator HAL)
- **Output**: `status_msg_t` (status to train control)

**Data Structures**:
```c
typedef enum {
    STATE_IDLE,
    STATE_OPENING,
    STATE_OPEN,
    STATE_CLOSING,
    STATE_CLOSED,
    STATE_FAULT
} control_state_t;

typedef struct {
    control_state_t state;
    uint32_t timestamp_ms;
    uint8_t error_code;
} control_module_state_t;
```

**Key Functions**:
- `void control_init(void)` - Initialize control module
- `error_t control_process(void)` - Main processing function (called every 50ms)
- `control_state_t control_get_state(void)` - Get current state

**Complexity**: Estimated ≤ 8 (target ≤ 10 for SIL 3-4)

**C Files**: `control.h`, `control.c`

---

#### 3.2.2 Safety Module

**Module ID**: MOD-SAFE  
**SIL Level**: 4  
**Implements**: REQ-SAFE-001, REQ-SAFE-002, REQ-SAFE-003

**Purpose**: Implements safety-critical functions (fault detection, fail-safe behavior)

**Responsibilities**:
- Monitor safety-critical conditions
- Detect faults (sensor failures, timing violations)
- Enforce fail-safe behavior (e.g., lock doors if speed > 5 km/h)
- Refresh watchdog timer

**Interfaces**:
- **Input**: `sensor_data_t` (primary and redundant sensor readings)
- **Output**: `safety_cmd_t` (safety commands to actuators)
- **Output**: `fault_status_t` (fault codes, diagnostic info)

**Data Structures**:
```c
typedef struct {
    bool emergency_stop_active;
    bool speed_interlock_active;
    bool watchdog_ok;
    uint8_t fault_count;
} safety_module_state_t;
```

**Key Functions**:
- `void safety_init(void)` - Initialize safety module
- `error_t safety_monitor(void)` - Check safety conditions (called every 10ms)
- `void safety_watchdog_refresh(void)` - Refresh watchdog (called every 100ms)
- `fault_status_t safety_get_faults(void)` - Get active faults

**Complexity**: Estimated ≤ 10 (target ≤ 10 for SIL 4)

**C Files**: `safety.h`, `safety.c`

---

[Continue with additional modules: Monitoring Module, Diagnostic Module, Sensor HAL, Actuator HAL, Timer HAL, Communication HAL]

### 3.3 Module Interface Matrix

| Module | Interfaces With | Data Flow | Interface Type |
|--------|-----------------|-----------|----------------|
| Control Module | Train Control System | Commands (in), Status (out) | CAN bus |
| Control Module | Sensor HAL | Sensor data (in) | Function call |
| Control Module | Actuator HAL | Actuator commands (out) | Function call |
| Control Module | Safety Module | Safety status (in), Control override (out) | Function call |
| Safety Module | Sensor HAL | Redundant sensor data (in) | Function call |
| Safety Module | Actuator HAL | Safety interlock (out) | Function call |
| Safety Module | Watchdog HW | Watchdog refresh (out) | GPIO |

### 3.4 Information Encapsulation

**Encapsulation Strategy** (EN 50128 Table A.3, Technique 20):

Each module SHALL encapsulate its internal state and expose ONLY defined interfaces.

**Example** (Control Module):
```c
// control.h (PUBLIC interface)
typedef struct control_module_state_t control_module_state_t;  // Opaque type

void control_init(void);
error_t control_process(void);
control_state_t control_get_state(void);

// control.c (PRIVATE implementation)
static control_module_state_t g_control_state;  // Hidden from other modules

static error_t validate_input(const sensor_data_t* data);  // Private function
static void transition_state(control_state_t new_state);   // Private function
```

**Benefits**:
- Prevents unauthorized access to internal state
- Reduces coupling between modules
- Improves testability (clear interface boundaries)

---

## 4. PROCESS ARCHITECTURE

### 4.1 Task Allocation

**Execution Model**: [Select one: bare-metal cyclic executive, RTOS with tasks, interrupt-driven]

#### 4.1.1 Option A: Bare-Metal Cyclic Executive (Recommended for SIL 3-4)

**Main Loop** (50ms cycle):
```c
void main(void) {
    system_init();
    control_init();
    safety_init();
    
    while (1) {
        // Read inputs
        sensor_data_t sensor_data = sensor_hal_read();
        train_control_msg_t cmd = comm_hal_receive();
        
        // Safety processing (highest priority)
        safety_monitor(&sensor_data);
        safety_watchdog_refresh();
        
        // Control processing
        control_process(&sensor_data, &cmd);
        
        // Write outputs
        actuator_hal_write(&actuator_cmd);
        comm_hal_send(&status_msg);
        
        // Wait for next cycle (50ms)
        timer_hal_wait_for_tick();
    }
}
```

**Rationale**: Deterministic, simple, no RTOS overhead, easier to certify (SIL 3-4)

#### 4.1.2 Option B: RTOS with Tasks (If RTOS required)

**Task Structure**:

| Task | Priority | Period | Worst-Case Execution Time | Stack Size |
|------|----------|--------|---------------------------|------------|
| Safety Task | 1 (Highest) | 10ms | 2ms | 512 bytes |
| Control Task | 2 | 50ms | 10ms | 1024 bytes |
| Communication Task | 3 | 100ms | 5ms | 512 bytes |
| Diagnostic Task | 4 (Lowest) | 1000ms | 20ms | 512 bytes |

**Schedulability Analysis**: [Provide analysis showing all deadlines met]

**RTOS Note**: If using RTOS, it MUST be qualified per EN 50128 Section 6.7 (Tool Qualification).

### 4.2 Interrupt Service Routines (ISRs)

**ISR List**:

| ISR | Trigger | Purpose | Max Duration | Priority |
|-----|---------|---------|--------------|----------|
| Emergency Stop ISR | GPIO falling edge | Immediately halt all motion | < 50µs | Highest |
| Timer ISR | Timer overflow (10ms) | Increment system tick, wake tasks | < 20µs | High |
| CAN RX ISR | CAN message received | Buffer incoming message | < 30µs | Medium |

**ISR Design Rules**:
- Keep ISRs short (< 100µs)
- NO blocking calls in ISRs
- NO dynamic memory allocation in ISRs
- Use flags/queues to signal tasks

### 4.3 Timing Analysis

**Control Loop Timing** (50ms cycle):

| Activity | Execution Time | Margin |
|----------|----------------|--------|
| Read inputs | 0.5ms | - |
| Safety monitor | 2.0ms | - |
| Control process | 10.0ms | - |
| Write outputs | 0.5ms | - |
| **Total** | **13.0ms** | **37ms (74%)** |

**Acceptance Criteria**: Total execution time ≤ 40ms (80% of 50ms cycle)

---

## 5. DATA ARCHITECTURE

### 5.1 Data Model

**Global Data Strategy**: Minimize global data, prefer encapsulated module state.

**Shared Data** (if unavoidable):
- Protected by mutexes (RTOS) or critical sections (bare-metal)
- Accessed via getter/setter functions (not direct access)

### 5.2 Data Structures (C Implementation)

#### 5.2.1 Sensor Data Structure

```c
typedef struct {
    uint16_t door_position_adc;     // ADC counts, 0-4095
    uint8_t door_position_pct;      // Percentage, 0-100
    bool obstacle_detected;         // true = obstacle present
    uint16_t speed_primary_kmh;     // km/h * 10 (e.g., 125 = 12.5 km/h)
    uint16_t speed_secondary_kmh;   // Redundant speed sensor
    uint32_t timestamp_ms;          // System timestamp
    bool data_valid;                // true = data valid
} sensor_data_t;
```

#### 5.2.2 Actuator Command Structure

```c
typedef struct {
    uint8_t door_pwm_duty_cycle;    // 0-100 (%)
    bool door_lock_enable;          // true = lock engaged
    bool emergency_stop;            // true = emergency stop active
    uint32_t timestamp_ms;          // Command timestamp
} actuator_cmd_t;
```

### 5.3 Static Memory Allocation (Mandatory SIL 2+)

**All data SHALL be statically allocated.**

**Example**:
```c
// CORRECT (static allocation)
static sensor_data_t g_sensor_data;
static uint8_t g_buffer[256];

// INCORRECT (dynamic allocation - FORBIDDEN for SIL 2+)
// sensor_data_t* data = malloc(sizeof(sensor_data_t));  // FORBIDDEN
```

**Memory Layout** (example):
```
ROM (Flash): [Code: 64KB] [Constants: 8KB]
RAM (SRAM):  [Data: 16KB] [Stack: 4KB] [Heap: 0KB - NO HEAP]
```

### 5.4 Data Flow Diagram

```
[Train Control] ──CAN──> [Comm HAL] ──msg──> [Control Module]
                                                     │
[Sensors] ──ADC/GPIO──> [Sensor HAL] ──data─────────┘
                                           │
                                           └────> [Safety Module]
                                                       │
[Actuators] <──PWM/GPIO── [Actuator HAL] <──cmd──────┴────────[Control Module]
```

---

## 6. SAFETY ARCHITECTURE

### 6.1 Safety Functions

**Safety-Critical Functions** (SIL 4):
1. Emergency stop detection and response (< 100ms)
2. Speed interlock (doors locked if speed > 5 km/h)
3. Obstacle detection and door reversal
4. Watchdog monitoring (system reset if lockup)

### 6.2 Redundancy and Diversity

**Redundant Speed Monitoring**:
- Primary speed sensor: Hall effect sensor
- Secondary speed sensor: Doppler radar (diverse technology)
- Software comparison: Raise fault if disagreement > 10%

**Voting Strategy**: 1-out-of-2 (either sensor can trigger safety action)

### 6.3 Fault Detection and Diagnosis

**Fault Detection Mechanisms**:

| Fault Type | Detection Method | Response | Detection Time |
|------------|------------------|----------|----------------|
| Sensor failure | Plausibility check, range check | Use default safe value, raise alarm | < 100ms |
| Actuator failure | Feedback monitoring | Disable actuator, enter safe state | < 200ms |
| Software lockup | Hardware watchdog timeout | System reset to safe state | < 200ms |
| Communication loss | Timeout on CAN messages | Use last valid command or safe default | < 150ms |
| Speed sensor mismatch | Compare primary/secondary | Lock doors (fail-safe), raise alarm | < 50ms |

### 6.4 Safe States

**Safe State Definition**: System state where no hazard exists or risk is minimized.

**Primary Safe State**:
- All door actuators disabled (0% PWM)
- All doors locked (lock solenoid energized)
- Emergency status reported to train control
- System ready to restart after fault cleared

**Fail-Safe Design**:
- Door locks are "normally closed" (energize to unlock) – power loss = doors locked ✓
- Emergency stop is active-high – wire break = emergency stop ✓

---

## 7. C IMPLEMENTATION CONSTRAINTS

### 7.1 MISRA C Compliance (Mandatory SIL 2+)

All code SHALL comply with MISRA C:2012. Specific rules enforced:
- Rule 4.6: Use fixed-width types (`uint8_t` not `unsigned char`)
- Rule 8.13: Pointer parameters that do not modify data SHALL be `const`
- Rule 21.3: `malloc`, `free`, `calloc`, `realloc` SHALL NOT be used
- [List additional critical MISRA C rules]

### 7.2 Defensive Programming (Highly Recommended SIL 3-4)

**Input Validation Pattern**:
```c
error_t process_data(const data_t* input, result_t* output) {
    // Validate all inputs
    if (input == NULL) {
        return ERROR_NULL_POINTER;
    }
    if (output == NULL) {
        return ERROR_NULL_POINTER;
    }
    if (input->value > MAX_VALUE || input->value < MIN_VALUE) {
        return ERROR_OUT_OF_RANGE;
    }
    
    // Process data...
    
    return SUCCESS;
}
```

### 7.3 No Recursion (Highly Recommended SIL 3-4)

**All functions SHALL be non-recursive.**

Rationale: Eliminates stack overflow risk, ensures bounded execution time.

Verification: Static analysis (call graph analysis)

### 7.4 Complexity Limits

**Cyclomatic Complexity Limits**:
- **SIL 0-1**: ≤ 20
- **SIL 2**: ≤ 15
- **SIL 3-4**: ≤ 10

**Enforcement**: Lizard, PC-lint analysis during code review

---

## 8. TRACEABILITY

### 8.1 Requirements to Architecture Traceability

| Requirement | Architecture Element | Module | Notes |
|-------------|---------------------|--------|-------|
| REQ-FUNC-001 | Door opening logic | MOD-CTRL (Control Module) | control.c |
| REQ-FUNC-002 | Door closing logic | MOD-CTRL (Control Module) | control.c |
| REQ-SAFE-001 | Speed interlock | MOD-SAFE (Safety Module) | safety.c |
| REQ-SAFE-002 | Watchdog refresh | MOD-SAFE (Safety Module) | safety.c |
| REQ-PERF-001 | 50ms control loop | Process Architecture (Section 4.1) | main.c |

**Traceability Completeness**: 100% of requirements SHALL be traced to architecture elements.

---

## 9. ARCHITECTURE EVALUATION

### 9.1 Architecture Quality Metrics

| Metric | Target | Actual | Status |
|--------|--------|--------|--------|
| Module count | ≤ 10 | [N] | [✓ / ✗] |
| Average complexity per module | ≤ 10 (SIL 3-4) | [N] | [✓ / ✗] |
| Interface count per module | ≤ 5 | [N] | [✓ / ✗] |
| Cyclic dependencies | 0 | [N] | [✓ / ✗] |
| Global data items | ≤ 5 | [N] | [✓ / ✗] |

### 9.2 Architecture Review Checklist

- [ ] Modular approach used (mandatory SIL 2+)
- [ ] All modules have defined interfaces
- [ ] Information encapsulation enforced
- [ ] Static memory allocation only (SIL 2+)
- [ ] No recursion (HR SIL 3-4)
- [ ] Defensive programming patterns specified (HR SIL 3-4)
- [ ] Complexity within limits (≤ 10 for SIL 3-4)
- [ ] Safety architecture addresses all hazards
- [ ] Traceability complete (100% requirements traced)

---

## 10. COMPLIANCE MATRIX

### 10.1 EN 50128 Section 7.3 Compliance

| Requirement | Section | Evidence | Status |
|-------------|---------|----------|--------|
| **Architecture established** | 7.3.2 | This document (SAS) | ✓ |
| **Modular approach (SIL 2+)** | Table A.3 | Section 3 (module decomposition) | ✓ |
| **Information encapsulation** | Table A.3 | Section 3.4 | ✓ |
| **Defensive programming (HR SIL 3-4)** | Table A.3 | Section 7.2 | ✓ |
| **Structured methodology (M SIL 3-4)** | Table A.3 | Entire document | ✓ |

### 10.2 EN 50128 Table A.3 Compliance (Architecture Techniques)

| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Applied |
|-----------|-------|---------|---------|---------|
| Defensive Programming | - | HR | HR | ✓ Yes |
| Structured Methodology | R | HR | **M** | ✓ Yes |
| Modular Approach | HR | **M** | **M** | ✓ Yes |
| Information Encapsulation | R | HR | HR | ✓ Yes |

---

## 11. REFERENCES

### 11.1 Normative References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems |
| **[MISRAC]** | MISRA C:2012 Guidelines for the use of the C language in critical systems |

### 11.2 Project References

| Reference | Document |
|-----------|----------|
| **[SRS]** | Software Requirements Specification, DOC-SRS-YYYY-NNN |
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-YYYY-NNN |

---

## APPENDICES

### Appendix A: Module Template

```markdown
#### Module Name

**Module ID**: MOD-[ID]  
**SIL Level**: [0-4]  
**Implements**: [REQ-IDs]

**Purpose**: [Brief description]

**Responsibilities**:
- [Responsibility 1]
- [Responsibility 2]

**Interfaces**:
- **Input**: [Data type, source]
- **Output**: [Data type, destination]

**Data Structures**:
\```c
typedef struct {
    // Fields
} module_state_t;
\```

**Key Functions**:
- `void module_init(void)` - Initialize
- `error_t module_process(void)` - Main processing

**Complexity**: [Estimated complexity]

**C Files**: `module.h`, `module.c`
```

### Appendix B: Glossary

[Add project-specific terminology]

---

## DOCUMENT HISTORY

This document is maintained under configuration control per SCMP. All changes SHALL be approved by the Change Control Board (CCB).

**Current Version**: [Version from header]  
**Last Updated**: [Date from header]  
**Next Review**: [Date - recommended per phase gate]

---

**END OF DOCUMENT**