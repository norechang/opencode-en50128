# Software Architecture Design Workflow

**Purpose**: Create Software Architecture Specification (SAS) compliant with EN 50128 Section 7.3.

**EN 50128 Reference**: Section 7.3 Software Architecture and Design

**Deliverable**: Software Architecture Specification (SAS) - DOC-009-SAS

**Role**: Designer (DES)

**Prerequisites**:
- Software Requirements Specification (SRS) approved (DOC-006)
- Software Quality Assurance Plan (SQAP) approved (DOC-001)
- Software Configuration Management Plan (SCMP) approved (DOC-003)
- Software Verification Plan (SVP) reviewed (DOC-004)

---

## Workflow Overview

```
┌──────────────────────────────────────┐
│ 1. Preparation                       │ Review SRS, identify architectural drivers
├──────────────────────────────────────┤
│ 2. Architectural Analysis            │ Analyze requirements, constraints, quality attributes
├──────────────────────────────────────┤
│ 3. Architectural Design              │ Define structure, components, interfaces
├──────────────────────────────────────┤
│ 4. Apply EN 50128 Techniques         │ Modular Approach (M), Structured Methodology (M SIL 3-4)
├──────────────────────────────────────┤
│ 5. Apply Safety Patterns             │ Defensive programming, fault detection
├──────────────────────────────────────┤
│ 6. Apply C Design Constraints        │ Static allocation, complexity limits, MISRA C
├──────────────────────────────────────┤
│ 7. Document Architecture             │ Create SAS document from template
├──────────────────────────────────────┤
│ 8. Architectural Review              │ Self-review, peer review
├──────────────────────────────────────┤
│ 9. Quality Assurance Review          │ QUA template + design quality check
├──────────────────────────────────────┤
│ 10. Verification Review (SIL 3-4)    │ Independent VER review
├──────────────────────────────────────┤
│ 11. Finalize and Baseline            │ CM baseline creation
└──────────────────────────────────────┘
```

---

## Workflow Steps

### 1. Preparation Phase

**Objective**: Understand requirements and architectural drivers

#### 1.1 Review Software Requirements Specification (SRS)
- [ ] Read SRS (DOC-006) completely
- [ ] Identify functional requirements (Section 2)
- [ ] Identify performance requirements (Section 3) - timing, throughput, resources
- [ ] Identify interface requirements (Section 4) - hardware, software, communication
- [ ] Identify safety requirements (Section 5) - SIL levels, fault handling
- [ ] Identify quality requirements (Section 6) - reliability, maintainability
- [ ] Identify constraints (Section 7) - C language, MISRA C, static allocation, no recursion
- [ ] Note traceability requirements (Section 8) - 100% for SIL 3-4

**Extract Architectural Drivers**:
```
Architectural Driver: Key requirement that significantly influences architecture

Examples:
- Performance: "Control loop cycle time SHALL be ≤50ms" → Real-time architecture needed
- Safety: "Overspeed detection SHALL occur within 100ms" → Time-critical safety architecture
- Resource: "System SHALL operate with 128KB RAM" → Memory-constrained architecture
- Interface: "System SHALL communicate via CAN bus at 1 Mbps" → Communication architecture
- Constraint: "Static allocation only (SIL 2+)" → Fixed-size data structures
```

#### 1.2 Review Related Documents
- [ ] System Requirements Specification - architectural context
- [ ] Hazard Log - safety architecture requirements
- [ ] SQAP - quality standards, architectural principles
- [ ] SCMP - configuration management approach
- [ ] SVP - verification requirements for architecture

#### 1.3 Identify SIL Level and EN 50128 Techniques
- [ ] Confirm project SIL level (0, 1, 2, 3, 4)
- [ ] Review EN 50128 Table A.3 mandatory techniques:
  - **SIL 2+**: Modular Approach (19) is **MANDATORY**
  - **SIL 3-4**: Structured Methodology (1) and Modular Approach (19) are **MANDATORY**
  - **SIL 3-4 Highly Recommended**: Defensive Programming (2), Fault Detection (3), Fully Defined Interface (7), Modelling (5)

**SIL 3-4 Approved Combinations** (EN 50128 Table A.3):
- **Option A**: 1 (Structured Methodology), 7 (Fully Defined Interface), 19 (Modular Approach), 22 (Memorisation) + one from {4, 5, 12, 21}
- **Option B**: 1, 4 (Information Encapsulation), 19, 22 + one from {2, 5, 12, 15, 21}

#### 1.4 Identify C Language Constraints
- [ ] **Static allocation only** (SIL 2+): All data structures must be fixed-size arrays
- [ ] **No dynamic memory** (SIL 2+): No malloc, calloc, realloc, free
- [ ] **No recursion** (highly recommended SIL 3-4): All function calls must be non-recursive
- [ ] **Cyclomatic complexity limits**: ≤10 (SIL 3-4), ≤15 (SIL 2), ≤20 (SIL 0-1)
- [ ] **Fixed-width types**: uint8_t, uint16_t, uint32_t (no int, long, short)
- [ ] **MISRA C:2012 compliance**: Architecture must support MISRA C implementation

---

### 2. Architectural Analysis Phase

**Objective**: Analyze requirements to identify architectural components, interfaces, and quality attributes

#### 2.1 Functional Decomposition
- [ ] Group related requirements into functional areas
- [ ] Identify major subsystems or components
- [ ] Apply Structured Methodology (EN 50128 D.52, MANDATORY SIL 3-4)

**Example - Train Control System**:
```
System: Train Control System (SIL 3)

Functional Areas (from SRS):
1. Speed Monitoring
   - Requirements: REQ-FUNC-001 to REQ-FUNC-010
   - Functions: Read sensors, validate data, calculate speed
   
2. Control Logic
   - Requirements: REQ-FUNC-011 to REQ-FUNC-020
   - Functions: Compare speed to limits, generate control commands
   
3. Safety Monitoring
   - Requirements: REQ-SAFE-001 to REQ-SAFE-020
   - Functions: Detect faults, manage safe state, log events
   
4. Communication
   - Requirements: REQ-INTF-001 to REQ-INTF-010
   - Functions: CAN bus interface, message handling
   
5. Operator Interface
   - Requirements: REQ-INTF-011 to REQ-INTF-020
   - Functions: Display, user input, alarms

Architectural Components (derived):
- Speed Sensor Interface Module
- Control Algorithm Module
- Safety Monitor Module
- Communication Interface Module
- Operator Interface Module
- System Manager Module (coordinator)
```

#### 2.2 Identify Interfaces
- [ ] Internal interfaces (between components within software)
- [ ] External interfaces (hardware, other software systems, users)
- [ ] Apply Fully Defined Interface (EN 50128 D.38, HR for all SILs)

**Interface Types**:
```
Hardware Interfaces:
- Speed sensor (SPI, address 0x4000)
- Brake actuator (PWM output, GPIO pin 12)
- CAN transceiver (CAN peripheral)
- Display controller (I2C, address 0x3C)

Software Interfaces:
- Function calls between modules
- Data structures passed between components
- Callback functions for events

Communication Interfaces:
- CAN bus messages (ID, data length, payload format)
- UART diagnostic protocol
```

#### 2.3 Identify Quality Attributes
- [ ] Performance: Timing constraints, throughput, latency
- [ ] Reliability: Fault tolerance, error handling, MTBF
- [ ] Safety: Fault detection, safe state management, SIL compliance
- [ ] Maintainability: Modularity, diagnostics, logging
- [ ] Portability: Platform independence (if required)

**Quality Attribute Scenarios**:
```
Performance Scenario 1:
Stimulus: Speed sensor reading available
Response: System processes reading and updates control output
Measure: Response time ≤ 50ms (95th percentile)
Architectural Impact: Real-time scheduling, low-latency data paths

Safety Scenario 1:
Stimulus: Sensor failure detected
Response: System enters safe state (emergency brake)
Measure: Safe state reached within 100ms
Architectural Impact: Fault detection module, safety monitor, independent watchdog

Reliability Scenario 1:
Stimulus: Transient sensor error
Response: System filters error, continues operation
Measure: MTBF ≥ 10,000 hours
Architectural Impact: Error filtering, redundant sensors, graceful degradation
```

#### 2.4 Identify Safety Architecture Requirements
- [ ] Review safety requirements (SRS Section 5)
- [ ] Identify safety-critical components (based on SIL assignment)
- [ ] Apply Fault Detection and Diagnosis (EN 50128 D.26, HR for SIL 3-4)
- [ ] Apply Defensive Programming patterns (EN 50128 D.14, HR for SIL 3-4)

**Safety Architecture Patterns**:
- **Separation**: Isolate safety-critical functions from non-safety functions
- **Redundancy**: Duplicate critical sensors/actuators
- **Diversity**: Use different algorithms/implementations for critical functions
- **Monitoring**: Independent safety monitor (watchdog)
- **Safe State**: Defined safe state (emergency brake, power off)

---

### 3. Architectural Design Phase

**Objective**: Define architectural structure, components, and interfaces

**Mandatory Technique**: Modular Approach (EN 50128 D.38, MANDATORY SIL 2+)

#### 3.1 Define Architectural Style
- [ ] Choose architectural style appropriate for requirements

**Common Railway Software Architectures**:

**1. Layered Architecture**:
```
┌─────────────────────────────────────────┐
│  Application Layer                      │ Control logic, safety functions
├─────────────────────────────────────────┤
│  Service Layer                          │ Data processing, algorithms
├─────────────────────────────────────────┤
│  Hardware Abstraction Layer (HAL)       │ Sensor/actuator interfaces
├─────────────────────────────────────────┤
│  Hardware                               │ Microcontroller, sensors, actuators
└─────────────────────────────────────────┘

Benefits: Clear separation of concerns, testability
SIL Applicability: All SILs
```

**2. Time-Triggered Architecture** (EN 50128 D.56, HR for SIL 3-4):
```
┌─────────────────────────────────────────┐
│  Periodic Tasks (fixed cycle time)      │
│  - Task 1: Read sensors (10ms cycle)    │
│  - Task 2: Control logic (50ms cycle)   │
│  - Task 3: Safety monitor (100ms cycle) │
│  - Task 4: Communication (200ms cycle)  │
└─────────────────────────────────────────┘

Benefits: Deterministic timing, analyzable worst-case execution time
SIL Applicability: SIL 3-4 (highly recommended)
```

**3. Event-Driven Architecture** (EN 50128 D.21, R for SIL 3-4):
```
┌─────────────────────────────────────────┐
│  Event Handlers                         │
│  - Sensor interrupt → process reading   │
│  - CAN message received → handle msg    │
│  - Timer expired → check watchdog       │
└─────────────────────────────────────────┘

Benefits: Responsive to external events
SIL Applicability: SIL 0-2 (may use), SIL 3-4 (use with caution - timing analysis required)
```

**Recommended for Railway SIL 3-4**: **Time-Triggered Layered Architecture**
- Combines deterministic timing (time-triggered) with clear structure (layered)
- Supports cyclomatic complexity analysis (fixed execution paths)
- Facilitates WCET analysis (worst-case execution time)

#### 3.2 Define Architectural Components (Modules)
- [ ] Apply Modular Approach (EN 50128 D.38, MANDATORY SIL 2+)
- [ ] Each module has single, well-defined responsibility (functional cohesion)
- [ ] Minimize coupling between modules (loose coupling)

**Module Definition Template**:
```markdown
### Module: Speed Sensor Interface

**Responsibility**: Acquire and validate speed sensor data

**Inputs**:
- Hardware: Speed sensor (SPI, address 0x4000)

**Outputs**:
- Data: speed_value (uint16_t, range [0, 300] km/h)
- Status: error_code (error_t enumeration)

**Functions**:
- sensor_init(): Initialize SPI interface
- sensor_read(uint16_t* speed): Read sensor value
- sensor_validate(uint16_t speed): Validate range and CRC
- sensor_error_handle(error_t error): Handle sensor errors

**Data Structures**:
- sensor_config_t: Configuration (SPI mode, clock, address)
- sensor_state_t: Current state (INIT, OPERATIONAL, FAILED)

**Performance**:
- sensor_read() WCET: 10ms

**Safety**:
- SIL 3 (provides data for safety-critical control)
- Defensive programming: NULL checks, range validation
- Fault detection: Timeout, CRC validation, out-of-range detection

**Memory**:
- Static allocation only
- Buffer size: 16 bytes (fixed)

**Complexity**:
- All functions ≤ 10 cyclomatic complexity (SIL 3)

**Dependencies**:
- Hardware Abstraction Layer (HAL): SPI functions
```

**Example - Train Control System Architecture**:
```
Module Hierarchy:

System Manager (SIL 3)
├── Speed Sensor Interface (SIL 3)
│   ├── SPI Driver (HAL)
│   └── Sensor Validation
├── Control Algorithm (SIL 3)
│   ├── Speed Error Calculation
│   ├── PID Controller
│   └── Command Generation
├── Safety Monitor (SIL 3)
│   ├── Overspeed Detection
│   ├── Fault Detection
│   ├── Safe State Manager
│   └── Watchdog
├── Brake Actuator Interface (SIL 3)
│   ├── PWM Driver (HAL)
│   └── Actuator Status
├── Communication Interface (SIL 1)
│   ├── CAN Driver (HAL)
│   ├── Message Encoder/Decoder
│   └── Message Handler
├── Operator Interface (SIL 1)
│   ├── Display Driver (HAL)
│   ├── Button Handler
│   └── Alarm Manager
└── Diagnostics (SIL 0)
    ├── Event Logger
    └── Diagnostic Reporter
```

#### 3.3 Define Interfaces Between Modules
- [ ] Apply Fully Defined Interface (EN 50128 D.38, HR for all SILs)
- [ ] Specify function signatures (parameters, return types)
- [ ] Specify data structures passed between modules
- [ ] Specify calling conventions (synchronous, asynchronous, interrupt context)

**Interface Definition Template**:
```c
/**
 * @interface Speed Sensor Interface → Control Algorithm
 * @description Provides validated speed data to control algorithm
 * @sil 3
 */

/**
 * @brief Get current validated speed
 * @param[out] speed Pointer to speed value (km/h)
 * @return error_t SUCCESS or error code
 * @precondition sensor_init() has been called
 * @postcondition If SUCCESS, *speed contains valid speed in range [0, 300]
 * @sil 3
 * @wcet 1ms
 */
error_t sensor_get_speed(uint16_t* speed);

/**
 * @brief Get sensor status
 * @return sensor_state_t Current sensor state (OPERATIONAL, FAILED, etc.)
 * @sil 3
 * @wcet <1ms
 */
sensor_state_t sensor_get_status(void);
```

**Interface Types**:
- **Function calls**: Synchronous, blocking (most common in SIL 3-4)
- **Data sharing**: Global variables (avoid), shared memory with mutex
- **Message passing**: Queues (event-driven systems)
- **Callbacks**: Function pointers (use with caution in SIL 3-4 - may increase complexity)

#### 3.4 Define Data Architecture
- [ ] Identify all data structures
- [ ] Apply Information Encapsulation (EN 50128 D.33, HR for SIL 3-4)
- [ ] Apply static allocation (MANDATORY SIL 2+)

**Data Structure Design**:
```c
/**
 * @struct sensor_data_t
 * @brief Speed sensor data structure
 * @sil 3
 */
typedef struct {
    uint16_t speed_kmh;        // Speed in km/h [0, 300]
    uint16_t crc;              // CRC checksum
    uint32_t timestamp_ms;     // Timestamp (milliseconds)
    sensor_state_t state;      // Sensor state
    error_t last_error;        // Last error code
} sensor_data_t;

// CORRECT: Static allocation (SIL 2+)
static sensor_data_t sensor_data;

// FORBIDDEN: Dynamic allocation (SIL 2+)
// sensor_data_t* sensor_data = malloc(sizeof(sensor_data_t));  // NEVER!
```

**Data Encapsulation** (EN 50128 D.33):
```c
// sensor.h - Public interface
error_t sensor_get_speed(uint16_t* speed);
sensor_state_t sensor_get_status(void);

// sensor.c - Private implementation
static sensor_data_t sensor_data;  // Encapsulated, not accessible outside module

error_t sensor_get_speed(uint16_t* speed) {
    if (speed == NULL) return ERROR_INVALID;  // Defensive programming
    if (sensor_data.state != SENSOR_OPERATIONAL) return ERROR_NOT_READY;
    *speed = sensor_data.speed_kmh;
    return SUCCESS;
}
```

#### 3.5 Define Control Flow
- [ ] Specify execution sequence (initialization, main loop, shutdown)
- [ ] Specify timing (cycle times, priorities)
- [ ] Apply Time-Triggered Architecture (EN 50128 D.56, HR for SIL 3-4)

**Time-Triggered Control Flow**:
```c
/**
 * @brief Main control loop (time-triggered)
 * @cycle 50ms
 * @sil 3
 */
void main_control_loop(void) {
    static uint32_t cycle_count = 0;
    
    // Task 1: Read sensors (every cycle, 50ms)
    sensor_read_all();
    
    // Task 2: Control algorithm (every cycle, 50ms)
    control_algorithm_execute();
    
    // Task 3: Safety monitor (every cycle, 50ms)
    safety_monitor_check();
    
    // Task 4: Communication (every 4 cycles, 200ms)
    if ((cycle_count % 4) == 0) {
        communication_send_status();
    }
    
    // Task 5: Diagnostics (every 20 cycles, 1000ms)
    if ((cycle_count % 20) == 0) {
        diagnostics_log_status();
    }
    
    cycle_count++;
}
```

---

### 4. Apply EN 50128 Techniques

**Objective**: Apply mandatory and highly recommended EN 50128 Table A.3 techniques

#### 4.1 Structured Methodology (D.52, MANDATORY SIL 3-4)
- [ ] Systematic, top-down decomposition
- [ ] Hierarchical module structure
- [ ] Clear traceability: Requirements → Architecture → Design

**Already Applied**:
- Functional decomposition (Section 2.1)
- Module hierarchy (Section 3.2)
- Traceability matrix (to be created in SAS document)

#### 4.2 Modular Approach (D.38, MANDATORY SIL 2+)
- [ ] Each module has single responsibility (functional cohesion)
- [ ] Modules are loosely coupled (minimal dependencies)
- [ ] Modules have well-defined interfaces
- [ ] Modules are testable in isolation (unit testing)

**Module Quality Criteria**:
```
Functional Cohesion (D.55, HR for SIL 3-4):
✅ Speed Sensor Interface module: All functions related to speed sensor
✅ Control Algorithm module: All functions related to control calculation
❌ Utility module: Miscellaneous unrelated functions (low cohesion - avoid)

Low Coupling (D.55, HR for SIL 3-4):
✅ Speed Sensor Interface depends only on HAL (1 dependency)
✅ Control Algorithm depends on Speed Sensor Interface (1 dependency)
❌ Every module depends on every other module (high coupling - avoid)
```

#### 4.3 Fully Defined Interface (D.38, HR for all SILs)
- [ ] All function signatures specified (parameters, return types, preconditions, postconditions)
- [ ] All data structures documented
- [ ] All calling conventions specified
- [ ] WCET (Worst-Case Execution Time) specified for time-critical functions

**Example** (already shown in Section 3.3):
```c
/**
 * @brief Get current validated speed
 * @param[out] speed Pointer to speed value (km/h)
 * @return error_t SUCCESS or error code
 * @precondition sensor_init() has been called
 * @postcondition If SUCCESS, *speed contains valid speed in range [0, 300]
 * @sil 3
 * @wcet 1ms
 */
error_t sensor_get_speed(uint16_t* speed);
```

#### 4.4 Defensive Programming (D.14, HR for SIL 3-4)
- [ ] Validate all inputs (NULL checks, range checks)
- [ ] Check all return values
- [ ] Assert preconditions
- [ ] Handle all error cases

**See**: `resources/defensive-programming-patterns.md` for comprehensive guide

#### 4.5 Fault Detection and Diagnosis (D.26, HR for SIL 3-4)
- [ ] Detect hardware faults (sensor failures, actuator failures)
- [ ] Detect software faults (assertion failures, unexpected states)
- [ ] Provide diagnostic information (error codes, logs)
- [ ] Initiate safe state on critical faults

**Fault Detection Architecture**:
```
Safety Monitor Module:
├── Sensor Fault Detection
│   ├── Timeout detection
│   ├── Out-of-range detection
│   ├── CRC validation
│   └── Consistency checking (redundant sensors)
├── Actuator Fault Detection
│   ├── Actuator status monitoring
│   └── Feedback loop validation
├── Software Fault Detection
│   ├── Watchdog timer
│   ├── Stack overflow detection
│   ├── Assertion failures
│   └── Unexpected state transitions
└── Safe State Manager
    ├── Emergency brake activation
    ├── Power-off sequence
    └── Fault logging
```

#### 4.6 Modelling (Table A.17, HR for SIL 3-4)
- [ ] Create architectural models (state machines, data flow, control flow)
- [ ] Use standard notations (UML, SysML, SDL)

**State Machine Model - Sensor Module**:
```
States:
  INIT        → Initial state after power-on
  CALIBRATING → Performing sensor calibration
  OPERATIONAL → Normal operation
  DIAGNOSTIC  → Self-test mode
  FAILED      → Sensor fault detected
  SAFE_STATE  → Emergency safe state

Transitions:
  INIT → CALIBRATING: [Power-on complete]
  CALIBRATING → OPERATIONAL: [Calibration successful]
  CALIBRATING → FAILED: [Calibration failed]
  OPERATIONAL → DIAGNOSTIC: [Diagnostic requested]
  OPERATIONAL → FAILED: [Sensor error detected]
  DIAGNOSTIC → OPERATIONAL: [Diagnostic passed]
  DIAGNOSTIC → FAILED: [Diagnostic failed]
  FAILED → SAFE_STATE: [Always within 100ms]
  SAFE_STATE → INIT: [System reset]
```

**Data Flow Diagram - Speed Control**:
```
[Speed Sensor] → [Sensor Interface] → speed_value →
[Control Algorithm] → control_command →
[Actuator Interface] → [Brake Actuator]

[Safety Monitor] ← speed_value, control_command
[Safety Monitor] → emergency_brake_command → [Actuator Interface]
```

---

### 5. Apply Safety Architecture Patterns

**Objective**: Ensure architecture meets safety requirements

#### 5.1 Separation of Safety-Critical and Non-Safety Functions
- [ ] Identify safety-critical modules (based on SIL assignment)
- [ ] Isolate safety-critical modules from non-safety modules
- [ ] Prevent non-safety code from interfering with safety code

**Example**:
```
Safety-Critical (SIL 3):
- Speed Sensor Interface
- Control Algorithm
- Safety Monitor
- Brake Actuator Interface

Non-Safety (SIL 0-1):
- Operator Display
- Diagnostics
- Communication (status messages)

Architectural Separation:
- Safety-critical modules in separate source files
- Safety-critical data in separate memory region (if hardware supports)
- Safety-critical functions called first in main loop (highest priority)
```

#### 5.2 Redundancy
- [ ] Duplicate critical sensors/actuators (hardware redundancy)
- [ ] Duplicate critical calculations (software redundancy)
- [ ] Voting mechanism (2-out-of-3, 2-out-of-2 with diagnostics)

**Example**:
```c
/**
 * @brief Get speed from redundant sensors with voting
 * @param[out] speed Voted speed value
 * @return error_t SUCCESS or error code
 * @sil 4
 */
error_t get_redundant_speed(uint16_t* speed) {
    uint16_t speed1, speed2, speed3;
    error_t err1, err2, err3;
    
    // Read 3 independent sensors
    err1 = sensor1_read(&speed1);
    err2 = sensor2_read(&speed2);
    err3 = sensor3_read(&speed3);
    
    // 2-out-of-3 voting (median)
    if ((err1 == SUCCESS) && (err2 == SUCCESS) && (err3 == SUCCESS)) {
        *speed = median(speed1, speed2, speed3);
        return SUCCESS;
    }
    
    // Handle sensor failures
    return ERROR_REDUNDANCY_FAILURE;
}
```

#### 5.3 Diversity
- [ ] Use different algorithms for critical functions
- [ ] Use different hardware (if available)
- [ ] Cross-check results from diverse implementations

**Example**:
```c
/**
 * @brief Calculate control command with diverse algorithms
 * @param speed Current speed
 * @param target Target speed
 * @param[out] command Control command
 * @return error_t SUCCESS or error code
 * @sil 3
 */
error_t control_calculate_diverse(uint16_t speed, uint16_t target, 
                                   int16_t* command) {
    int16_t command_pid;     // PID controller
    int16_t command_lookup;  // Lookup table controller
    
    // Algorithm 1: PID controller
    command_pid = pid_controller(speed, target);
    
    // Algorithm 2: Lookup table (diverse implementation)
    command_lookup = lookup_table_controller(speed, target);
    
    // Cross-check (results should be similar)
    if (abs(command_pid - command_lookup) > TOLERANCE) {
        // Mismatch detected - use safe value
        *command = SAFE_COMMAND_VALUE;
        return ERROR_DIVERSITY_MISMATCH;
    }
    
    // Use PID result (both agree)
    *command = command_pid;
    return SUCCESS;
}
```

#### 5.4 Independent Safety Monitor (Watchdog)
- [ ] Separate module that monitors system health
- [ ] Independent of control logic (separate execution, separate data)
- [ ] Can force safe state if system fails

**Safety Monitor Architecture**:
```c
/**
 * @brief Safety monitor (independent watchdog)
 * @sil 4
 * @cycle 100ms (must run periodically)
 */
void safety_monitor_execute(void) {
    // Check 1: Control loop is running (heartbeat)
    if (!control_loop_heartbeat_received()) {
        enter_safe_state(ERROR_CONTROL_LOOP_TIMEOUT);
        return;
    }
    
    // Check 2: Speed is within safe limits
    uint16_t speed;
    if (sensor_get_speed(&speed) == SUCCESS) {
        if (speed > MAX_SAFE_SPEED) {
            enter_safe_state(ERROR_OVERSPEED);
            return;
        }
    } else {
        enter_safe_state(ERROR_SENSOR_FAILED);
        return;
    }
    
    // Check 3: Actuator is responding
    if (!actuator_is_operational()) {
        enter_safe_state(ERROR_ACTUATOR_FAILED);
        return;
    }
    
    // All checks passed
    safety_status = SAFE;
}
```

---

### 6. Apply C Language Design Constraints

**Objective**: Ensure architecture is implementable in C with EN 50128/MISRA C constraints

#### 6.1 Static Memory Allocation (MANDATORY SIL 2+)
- [ ] All data structures have fixed size at compile time
- [ ] No malloc, calloc, realloc, free
- [ ] All arrays have constant size

**Architecture Implication**:
```c
// CORRECT: Static allocation with fixed buffer size
#define SENSOR_BUFFER_SIZE 100U
static sensor_data_t sensor_buffer[SENSOR_BUFFER_SIZE];
static uint16_t sensor_buffer_index = 0U;

error_t sensor_buffer_add(sensor_data_t data) {
    if (sensor_buffer_index >= SENSOR_BUFFER_SIZE) {
        return ERROR_BUFFER_FULL;  // Fixed-size buffer, can overflow
    }
    sensor_buffer[sensor_buffer_index] = data;
    sensor_buffer_index++;
    return SUCCESS;
}

// FORBIDDEN: Dynamic allocation
// sensor_data_t* sensor_buffer = malloc(size * sizeof(sensor_data_t));  // NEVER for SIL 2+
```

**Architectural Decision**: Choose buffer sizes at design time based on worst-case analysis.

#### 6.2 No Recursion (Highly Recommended SIL 3-4)
- [ ] All function calls are non-recursive
- [ ] Call graph is acyclic (no cycles)
- [ ] Enables WCET analysis (worst-case execution time)

**Architecture Implication**:
```c
// FORBIDDEN: Recursive function (SIL 3-4)
/*
uint32_t factorial(uint32_t n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);  // Recursive call - FORBIDDEN SIL 3-4
}
*/

// CORRECT: Iterative implementation
uint32_t factorial(uint32_t n) {
    uint32_t result = 1U;
    for (uint32_t i = 2U; i <= n; i++) {
        result *= i;
    }
    return result;
}
```

#### 6.3 Cyclomatic Complexity Limits
- [ ] Ensure architectural decomposition supports complexity limits
- [ ] Each function ≤10 (SIL 3-4), ≤15 (SIL 2), ≤20 (SIL 0-1)

**Architecture Implication**: Break complex functions into smaller helper functions.

```c
// BAD: High complexity (too many branches)
error_t process_sensor_data_complex(sensor_data_t* data) {
    if (data == NULL) return ERROR_INVALID;
    if (data->state == FAILED) return ERROR_FAILED;
    if (data->speed > 300) return ERROR_OUT_OF_RANGE;
    if (data->crc != calculate_crc(data)) return ERROR_CRC;
    // ... many more branches ... (complexity > 10)
}

// GOOD: Decompose into helper functions (each with low complexity)
error_t validate_sensor_data(sensor_data_t* data);  // Complexity: 5
error_t process_sensor_data(sensor_data_t* data);   // Complexity: 3
error_t calculate_speed(sensor_data_t* data);       // Complexity: 4

error_t process_sensor_data_decomposed(sensor_data_t* data) {
    error_t err;
    
    err = validate_sensor_data(data);
    if (err != SUCCESS) return err;
    
    err = process_sensor_data(data);
    if (err != SUCCESS) return err;
    
    return calculate_speed(data);
}
// Total complexity: 3 (within limit)
```

#### 6.4 Fixed-Width Types (MISRA C:2012)
- [ ] Use uint8_t, uint16_t, uint32_t, uint64_t
- [ ] Avoid int, long, short, char (implementation-defined size)

**Architecture Implication**:
```c
// CORRECT: Fixed-width types
typedef struct {
    uint16_t speed_kmh;        // Always 16 bits
    uint32_t timestamp_ms;     // Always 32 bits
    uint8_t state;             // Always 8 bits
} sensor_data_t;

// INCORRECT: Implementation-defined types
/*
typedef struct {
    int speed;           // Size depends on platform (16/32/64 bits)
    long timestamp;      // Size depends on platform
    char state;          // Size may vary
} sensor_data_bad_t;
*/
```

#### 6.5 MISRA C:2012 Compliance
- [ ] Architecture supports MISRA C implementation
- [ ] No prohibited language features (e.g., goto in complex patterns, bitwise operations on signed types)

**See**: `resources/misra-c-design-guidelines.md` for comprehensive guide

---

### 7. Document Architecture

**Objective**: Create Software Architecture Specification (SAS) document

#### 7.1 Use SAS Template
- [ ] Copy template: `.opencode/skills/en50128-design/templates/Software-Architecture-Specification-template.md`
- [ ] Fill in document header (Document ID, project name, SIL, version)

#### 7.2 Document Structure (SAS Sections)
1. **Introduction**
   - Purpose, scope, definitions, references
   
2. **Architectural Overview**
   - High-level description
   - Architectural style (layered, time-triggered, etc.)
   - Architectural drivers (performance, safety, constraints)
   
3. **Module Decomposition**
   - List of all modules
   - Responsibilities of each module
   - Module hierarchy (parent-child relationships)
   
4. **Module Specifications**
   - For each module:
     - Functions (signatures, preconditions, postconditions, WCET)
     - Data structures
     - Interfaces (inputs, outputs)
     - Performance requirements
     - Safety requirements (SIL level)
     - Memory requirements (static allocation)
     - Complexity requirements
     
5. **Interface Specifications**
   - Internal interfaces (module-to-module)
   - External interfaces (hardware, other systems)
   - Data structures passed between modules
   
6. **Data Architecture**
   - Global data structures
   - Data flow between modules
   - Data encapsulation strategy
   
7. **Control Flow**
   - Initialization sequence
   - Main loop structure (time-triggered cycles)
   - Shutdown sequence
   - Interrupt handling
   
8. **Safety Architecture**
   - Safety-critical modules (SIL assignment)
   - Fault detection mechanisms
   - Safe state definition and management
   - Redundancy and diversity (if applicable)
   
9. **EN 50128 Techniques Applied**
   - List techniques from Table A.3 applied
   - Provide evidence of application (references to sections)
   
10. **Traceability Matrix**
    - Requirements → Architectural Components
    - Requirements → Interfaces
    - 100% coverage for SIL 3-4 (MANDATORY)

**See**: `workflows/architecture-specification.md` for detailed SAS creation workflow

---

### 8. Architectural Review

**Objective**: Self-review and peer review before formal reviews

#### 8.1 Self-Review by Designer (DES)
- [ ] Use checklist: `resources/architecture-review-checklist.md`
- [ ] Verify all requirements addressed by architecture
- [ ] Verify all EN 50128 techniques applied
- [ ] Verify all C constraints considered

#### 8.2 Peer Review
- [ ] Request review from another designer (if available)
- [ ] Conduct review meeting
- [ ] Document findings in review record
- [ ] Address findings and update SAS

---

### 9. Quality Assurance Review

**Objective**: QUA verifies document template compliance and architectural quality

#### 9.1 Submit to QUA Agent
- [ ] Send SAS to QUA agent for review

**QUA Checklist**:
- [ ] Document header compliant
- [ ] All required sections present
- [ ] Modular approach applied (MANDATORY SIL 2+)
- [ ] Cyclomatic complexity limits specified
- [ ] Static allocation enforced
- [ ] Traceability matrix present (MANDATORY SIL 3-4)

#### 9.2 Address QUA Findings
- [ ] Review QUA report
- [ ] Fix all critical and error-level findings
- [ ] Update SAS document
- [ ] Obtain QUA approval

---

### 10. Verification Review (SIL 3-4 Independent Review)

**Objective**: Independent VER agent verifies architecture is correct, complete, and compliant

#### 10.1 Submit to VER Agent
- [ ] Send SAS to VER agent for independent verification

**VER Checklist**:
- [ ] All requirements addressed by architecture (100% traceability for SIL 3-4)
- [ ] All EN 50128 Table A.3 mandatory techniques applied
- [ ] Modular approach applied (MANDATORY SIL 2+)
- [ ] Structured methodology applied (MANDATORY SIL 3-4)
- [ ] Interfaces fully defined
- [ ] Safety architecture adequate (fault detection, safe state, redundancy)
- [ ] C constraints considered (static allocation, no recursion, complexity limits)
- [ ] Architecture is implementable

#### 10.2 Address VER Findings
- [ ] Review VER report (Software Architecture and Design Verification Report - DOC-014)
- [ ] Fix all findings
- [ ] Update SAS document
- [ ] Obtain VER approval

---

### 11. Finalize and Baseline

**Objective**: Publish approved SAS and create configuration baseline

#### 11.1 Update Document Status
- [ ] Change status from "Draft" to "Approved"
- [ ] Assign final version number (e.g., v1.0)
- [ ] Update DOCUMENT CONTROL table

#### 11.2 Create Configuration Baseline
- [ ] Notify Configuration Manager (CM)
- [ ] CM creates baseline: `SAS-v1.0`
- [ ] CM tags in version control: `git tag SAS-v1.0`

#### 11.3 Distribute Document
- [ ] Publish SAS to project repository
- [ ] Notify downstream roles:
  - Designer (DES) - for detailed software design (DOC-010)
  - Implementer (IMP) - for coding guidance
  - Tester (TST) - for integration test planning
  - Verifier (VER) - already completed verification
  - Project Manager (PM) - for planning

---

## SIL-Specific Requirements

### SIL 0 (Non-Safety)
- Modular approach: Recommended but not mandatory
- EN 50128 techniques: Optional (use as needed)
- Traceability: Recommended but not mandatory
- Review: Internal review sufficient
- C constraints: Language choice (C or other), no strict constraints

### SIL 1-2 (Safety-Related)
- **Modular approach: MANDATORY for SIL 2+** (EN 50128 Table A.3)
- Structured methodology: Highly recommended
- Defensive programming: Highly recommended for SIL 2
- Traceability: Highly recommended
- Review: QUA review recommended
- C constraints:
  - **Static allocation MANDATORY for SIL 2+**
  - **MISRA C:2012 compliance MANDATORY for SIL 2+**
  - Cyclomatic complexity ≤15 (SIL 2)

### SIL 3-4 (Safety-Critical)
- **Modular approach: MANDATORY** (EN 50128 Table A.3, #19)
- **Structured methodology: MANDATORY** (EN 50128 Table A.3, #1)
- **Defensive programming: HIGHLY RECOMMENDED** (EN 50128 Table A.3, #2)
- **Fault detection: HIGHLY RECOMMENDED** (EN 50128 Table A.3, #3)
- **Fully defined interface: HIGHLY RECOMMENDED** (EN 50128 Table A.3, #7)
- **Modelling: HIGHLY RECOMMENDED** (EN 50128 Table A.3, #5)
- **Time-triggered architecture: HIGHLY RECOMMENDED** (EN 50128 Table A.3, #21)
- Traceability: 100% MANDATORY
- Review: Independent VER review MANDATORY
- C constraints:
  - **Static allocation MANDATORY**
  - **No recursion HIGHLY RECOMMENDED**
  - **MISRA C:2012 compliance MANDATORY**
  - **Cyclomatic complexity ≤10 MANDATORY**
  - **No dynamic memory allocation MANDATORY**

---

## Tools and Resources

**Workflows**:
- `architecture-design.md` - This workflow
- `software-design.md` - Detailed component design
- `interface-design.md` - Interface specification
- `design-review.md` - Design review process

**Resources**:
- `defensive-programming-patterns.md` - Defensive programming guide
- `complexity-guidelines.md` - Cyclomatic complexity management
- `modularity-guidelines.md` - Module design principles
- `architecture-review-checklist.md` - Architecture review checklist

**Templates**:
- `templates/Software-Architecture-Specification-template.md` - SAS template

---

## Standard References

- **EN 50128:2011 Section 7.3** - Software Architecture and Design
- **EN 50128:2011 Table A.3** - Software Architecture Techniques
- **EN 50128:2011 Annex D.38** - Modular Approach (MANDATORY SIL 2+)
- **EN 50128:2011 Annex D.52** - Structured Methodology (MANDATORY SIL 3-4)
- **EN 50128:2011 Annex D.14** - Defensive Programming
- **EN 50128:2011 Annex D.26** - Fault Detection and Diagnosis
- **MISRA C:2012** - C Coding Standard

---

## Deliverable

**Document**: Software Architecture Specification (SAS)  
**Document ID**: DOC-009-SAS-[PROJECT]-001  
**Template**: `.opencode/skills/en50128-design/templates/Software-Architecture-Specification-template.md`

---

## Next Steps

After SAS is approved and baselined:
1. Designer (DES) creates Software Design Specification (DOC-010) - detailed component design
2. Designer (DES) creates Software Interface Specifications (DOC-011) - detailed interface specs
3. Tester (TST) creates Software Integration Test Specification (DOC-012)
4. Lifecycle Coordinator (COD) performs gate check to authorize transition to detailed design phase
