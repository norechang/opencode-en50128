# Software Design Workflow

**Purpose**: Create Software Design Specification (SDS) with detailed component designs compliant with EN 50128 Section 7.3.4.20-7.3.4.24.

**EN 50128 Reference**: Section 7.3.4.20-7.3.4.24, Section 7.4 (Software Design and Implementation), Table A.4

**Deliverable**: Software Design Specification (SDS) - DOC-010-SDS

**Role**: Designer (DES)

**Prerequisites**:
- Software Requirements Specification (SRS) approved (DOC-006)
- Software Architecture Specification (SAS) approved (DOC-009)
- Software Interface Specifications approved (DOC-011)
- Software Quality Assurance Plan (SQAP) approved (DOC-001)
- Software Configuration Management Plan (SCMP) approved (DOC-003)
- Coding standards defined (Section 7.3.4.25-7.3.4.27)

---

## Workflow Overview

```
┌──────────────────────────────────────┐
│ 1. Preparation                       │ Review SAS, SRS, identify components
├──────────────────────────────────────┤
│ 2. Component Identification          │ Decompose architecture into detailed components
├──────────────────────────────────────┤
│ 3. Component Design                  │ Design each component (functions, data, algorithms)
├──────────────────────────────────────┤
│ 4. Interface Design                  │ Define component interfaces (APIs)
├──────────────────────────────────────┤
│ 5. Data Structure Design             │ Design data structures (static allocation SIL 2+)
├──────────────────────────────────────┤
│ 6. Algorithm Design                  │ Design algorithms (complexity limits)
├──────────────────────────────────────┤
│ 7. Error Handling Design             │ Design error detection, reporting, handling
├──────────────────────────────────────┤
│ 8. Apply C Design Constraints        │ MISRA C, static allocation, complexity, no recursion
├──────────────────────────────────────┤
│ 9. Apply EN 50128 Techniques         │ Structured Methodology (M), Modular Approach (M)
├──────────────────────────────────────┤
│ 10. Document Design                  │ Create SDS document from template
├──────────────────────────────────────┤
│ 11. Component Test Specification     │ Define unit test specification per component
├──────────────────────────────────────┤
│ 12. Traceability                     │ Trace components to architecture and requirements
├──────────────────────────────────────┤
│ 13. Design Review                    │ Self-review, peer review
├──────────────────────────────────────┤
│ 14. Quality Assurance Review         │ QUA template + design quality check
├──────────────────────────────────────┤
│ 15. Verification Review (SIL 3-4)    │ Independent VER review
├──────────────────────────────────────┤
│ 16. Finalize and Baseline            │ CM baseline creation
└──────────────────────────────────────┘
```

**EN 50128 Context**:
- **Section 7.3.4.20**: "A Software Design Specification shall be written, under the responsibility of the Designer, on the basis of the Software Requirements Specification, the Software Architecture Specification and the Software Interface Specification."
- **Section 7.3.4.22**: "The Software Design Specification shall describe the software design based on a decomposition into components with each component having a Software Component Design Specification and a Software Component Test Specification."

---

## Workflow Steps

### 1. Preparation Phase

**Objective**: Understand architecture, requirements, and design constraints

**EN 50128 Reference**: Section 7.3.4.21 - "The input documents shall be available, although not necessarily finalised, prior to the start of the design process."

#### 1.1 Review Software Architecture Specification (SAS)

- [ ] Read SAS (DOC-009) completely
- [ ] Identify architectural components (modules, layers)
- [ ] Identify architectural patterns (layered, time-triggered, event-driven)
- [ ] Identify module responsibilities and boundaries
- [ ] Identify architectural interfaces between modules
- [ ] Note safety architecture patterns (separation, redundancy, diversity)
- [ ] Note performance constraints (timing, throughput, memory)

**Extract Design Drivers from SAS**:
```
Design Driver: Architectural decision that influences detailed component design

Examples from SAS:
- Module: "Control Module handles periodic control loop (50ms cycle)" 
  → Design periodic control functions with ≤50ms WCET
- Safety: "Safety Monitor shall detect failures within 100ms"
  → Design fast failure detection algorithms
- Memory: "Total RAM allocation ≤ 128KB"
  → Design compact data structures, no waste
- Interface: "CAN bus communication at 1 Mbps"
  → Design message packing/unpacking functions
```

#### 1.2 Review Software Requirements Specification (SRS)

- [ ] Read SRS (DOC-006) completely
- [ ] Identify functional requirements that need component-level design
- [ ] Identify performance requirements (timing, accuracy)
- [ ] Identify interface requirements (hardware, software, communication)
- [ ] Identify safety requirements (SIL levels, fault handling)
- [ ] Identify quality requirements (reliability, maintainability)
- [ ] Identify constraints (C language, MISRA C, static allocation, no recursion)

**Map Requirements to Components**:
```
Requirement ID: REQ-CTRL-001
  Requirement: "System SHALL execute control loop every 50ms"
  Architectural Component: Control Module
  Design Components: control_init(), control_task(), control_periodic_callback()
  Design Constraints: WCET ≤ 50ms, complexity ≤ 10 (SIL 3-4)

Requirement ID: REQ-SAFE-012
  Requirement: "System SHALL detect overspeed within 100ms"
  Architectural Component: Safety Monitor Module
  Design Components: safety_check_speed(), safety_report_fault()
  Design Constraints: Fast execution, defensive programming mandatory
```

#### 1.3 Review Software Interface Specifications

- [ ] Read Software Interface Specifications (DOC-011)
- [ ] Identify hardware interfaces (GPIO, SPI, CAN, UART, ADC, PWM)
- [ ] Identify software interfaces (APIs, callbacks)
- [ ] Identify communication protocols (message formats, timing)
- [ ] Note interface timing constraints
- [ ] Note data types for interface data

**Interface Design Considerations**:
```
Hardware Interface Example:
  Interface: CAN Bus (ISO 11898)
  Architectural Module: Communication HAL
  Design Components:
    - can_init() - Initialize CAN controller
    - can_send_message() - Send CAN frame
    - can_receive_message() - Receive CAN frame
    - can_error_handler() - Handle CAN errors
  Data Structures:
    - can_message_t (ID, DLC, data[8], timestamp)
    - can_config_t (baudrate, filters)
  C Constraints:
    - Static allocation: Fixed-size message buffer (e.g., can_message_t tx_buffer[16])
    - No dynamic CAN ID allocation
```

#### 1.4 Review Coding Standards

- [ ] Read Coding Standards document (required per Section 7.3.4.25-7.3.4.27)
- [ ] Review MISRA C:2012 rules (mandatory SIL 2+)
- [ ] Review project-specific coding rules
- [ ] Review naming conventions
- [ ] Review documentation requirements (Doxygen, inline comments)
- [ ] Review error detection measures
- [ ] Review complexity limits: ≤10 (SIL 3-4), ≤15 (SIL 2), ≤20 (SIL 0-1)

**EN 50128 Section 7.3.4.25**: "Coding standards shall be developed and specify a) good programming practice, as defined by Table A.12, b) measures to avoid or detect errors which can be made during application of the language and are not detectable during the verification, c) procedures for source code documentation."

**Critical Coding Standards (C Language)**:
```
MISRA C:2012 (MANDATORY SIL 2+):
  - Rule 1.3: No undefined behavior
  - Rule 2.1: No unreachable code
  - Rule 8.9: Object defined at smallest scope
  - Rule 17.2: No recursion (MANDATORY SIL 3-4)
  - Rule 21.3: No malloc/calloc/realloc/free (MANDATORY SIL 2+)

Fixed-Width Types (MANDATORY):
  - Use uint8_t, uint16_t, uint32_t, int8_t, int16_t, int32_t
  - NO int, long, short, unsigned int, unsigned long

Static Allocation (MANDATORY SIL 2+):
  - All arrays: static uint8_t buffer[SIZE]
  - All structs: static structure_t instance
  - No malloc, calloc, realloc, free

Defensive Programming (MANDATORY SIL 3-4, HR SIL 2):
  - NULL pointer checks before dereference
  - Range checks on all inputs
  - Return value checks for all functions
  - Assertions for internal consistency
```

#### 1.5 Identify SIL Level and EN 50128 Techniques

- [ ] Confirm project SIL level (0, 1, 2, 3, 4)
- [ ] Review EN 50128 Table A.4 mandatory techniques:
  - **SIL 0**: Structured Programming (R), Modular Approach (HR)
  - **SIL 1-2**: Modular Approach (**M**), Structured Programming (HR)
  - **SIL 3-4**: Structured Methodology (**M**), Modular Approach (**M**), Design and Coding Standards (**M**), Analysable Programs (**M**), Structured Programming (**M**)

**EN 50128 Table A.4 - Software Design and Implementation Techniques/Measures**:

| ID | Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Reference |
|----|-----------|-------|---------|---------|-----------|
| 1 | Structured Methodology | R | HR | **M** | D.52 |
| 4 | Modular Approach | HR | **M** | **M** | D.38 |
| 5 | Design and Coding Standards | HR | HR | **M** | A.12 |
| 6 | Analysable Programs | HR | HR | **M** | D.2 |
| 7 | Structured Programming | R | HR | **M** | D.53 |
| 8 | Strongly Typed Language | R | HR | HR | D.49 |

**SIL 3-4 Approved Combination** (EN 50128 Table A.4 Note):
- **Combination**: Techniques 4, 5, 6, 8 + one from {1 or 2}
- **Typical**: 1 (Structured Methodology), 4 (Modular Approach), 5 (Design and Coding Standards), 6 (Analysable Programs), 7 (Structured Programming)

**EN 50128 Section 7.3.4.24**: "The Software Design Specification shall choose techniques and measures from Table A.4. The selected combination shall be justified as a set satisfying 4.8 and 4.9."

#### 1.6 Identify C Language Constraints

- [ ] **Static allocation only** (SIL 2+): All data structures must be fixed-size
- [ ] **No dynamic memory** (SIL 2+): No malloc, calloc, realloc, free
- [ ] **No recursion** (highly recommended SIL 3-4): All functions must be non-recursive
- [ ] **Cyclomatic complexity limits**: ≤10 (SIL 3-4), ≤15 (SIL 2), ≤20 (SIL 0-1)
- [ ] **Fixed-width types**: uint8_t, uint16_t, uint32_t (no int, long, short)
- [ ] **Bounded execution time**: All functions must have deterministic WCET
- [ ] **No undefined behavior**: All operations must be well-defined

**C Language Constraint Checklist for Design Phase**:
```
☑ Static Allocation (SIL 2+):
  - Design all data structures as fixed-size arrays
  - Design buffer sizes at design time (no runtime sizing)
  - Example: static uint8_t rx_buffer[256]; // CORRECT
  - Example: uint8_t* rx_buffer = malloc(size); // FORBIDDEN

☑ No Recursion (SIL 3-4):
  - Design all algorithms as iterative (loops, not recursive calls)
  - Example: Use loop-based tree traversal, not recursive traversal
  - Design call graph to verify no cycles

☑ Complexity Limits (SIL 3-4: ≤10):
  - Design functions to be simple and focused
  - Break complex logic into multiple functions
  - Use state machines instead of complex nested conditionals

☑ Fixed-Width Types:
  - Design all data structures with fixed-width types (uint8_t, uint16_t, etc.)
  - Document bit widths explicitly

☑ Bounded Execution Time:
  - Design algorithms with predictable execution time
  - Avoid unbounded loops (always use counted loops)
  - Document worst-case execution time (WCET) estimates
```

---

### 2. Component Identification Phase

**Objective**: Decompose architectural modules into detailed software components (functions, data structures)

**EN 50128 Reference**: Section 7.3.4.22 - "The Software Design Specification shall describe the software design based on a decomposition into components with each component having a Software Component Design Specification and a Software Component Test Specification."

#### 2.1 List Architectural Modules (from SAS)

**Input**: Software Architecture Specification (SAS) Section 3 (Module Decomposition)

- [ ] List all architectural modules from SAS
- [ ] For each module, note:
  - Module ID
  - Module name
  - Module responsibility
  - Module SIL level
  - Module interfaces (inputs, outputs)
  - Module dependencies

**Example Module List from SAS**:
```
Module ID: MOD-CTRL
  Name: Control Module
  Responsibility: Execute periodic control loop, compute control outputs
  SIL: 4
  Inputs: Sensor data (from Sensor HAL)
  Outputs: Control commands (to Actuator HAL)
  Dependencies: Sensor HAL, Actuator HAL, Safety Monitor

Module ID: MOD-SAFE
  Name: Safety Monitor Module
  Responsibility: Detect faults, monitor system health, enforce safety limits
  SIL: 4
  Inputs: System state (from Control Module)
  Outputs: Fault signals, safety actions
  Dependencies: None (independent safety function)
```

#### 2.2 Identify Software Components per Module

**Component**: A unit of design typically implemented as a set of C functions and data structures in a single `.c/.h` file pair.

**Component Identification Strategy**:
1. **Function-based**: Group related functions (e.g., control_init, control_run, control_shutdown)
2. **Data-based**: Group functions that operate on same data structure (e.g., queue_push, queue_pop, queue_is_full)
3. **Interface-based**: Group functions for same interface (e.g., can_init, can_send, can_receive)

**Component Decomposition Table**:
```
Module: MOD-CTRL (Control Module)
  Component: control_task
    Description: Main control task periodic execution
    Functions: control_init(), control_run(), control_shutdown()
    Data Structures: control_state_t (static)
    SIL: 4
    File: control_task.c/h
  
  Component: control_algorithm
    Description: Control algorithm computation (PID, state feedback)
    Functions: control_compute_pid(), control_update_state()
    Data Structures: pid_controller_t (static)
    SIL: 4
    File: control_algorithm.c/h
  
  Component: control_input
    Description: Input data validation and preprocessing
    Functions: control_validate_input(), control_filter_input()
    Data Structures: input_buffer_t[16] (static array)
    SIL: 4
    File: control_input.c/h

Module: MOD-SAFE (Safety Monitor Module)
  Component: safety_monitor
    Description: Continuous safety monitoring and fault detection
    Functions: safety_init(), safety_check_all(), safety_get_status()
    Data Structures: safety_status_t (static)
    SIL: 4
    File: safety_monitor.c/h
  
  Component: safety_fault_handler
    Description: Fault reporting and safe state transition
    Functions: safety_report_fault(), safety_enter_safe_state()
    Data Structures: fault_log_t[32] (static array)
    SIL: 4
    File: safety_fault_handler.c/h
```

- [ ] For each architectural module, identify software components
- [ ] For each component, specify:
  - Component ID
  - Component name
  - Component description
  - Responsible functions (list function signatures)
  - Data structures (list types)
  - SIL level (inherit from module or specify per component)
  - C file names (e.g., component.c, component.h)

#### 2.3 Assign Component IDs and SIL Levels

- [ ] Assign unique component IDs (e.g., COMP-CTRL-TASK-001)
- [ ] Assign SIL level to each component (from requirements traceability)
- [ ] Verify SIL consistency: Component SIL ≥ all requirements it implements

**Component Identification Checklist**:
```
☑ Each component has unique ID
☑ Each component has clear responsibility (single purpose)
☑ Each component has defined functions (API)
☑ Each component has defined data structures
☑ Each component has assigned SIL level
☑ Component SIL ≥ requirement SIL (for all requirements implemented)
☑ Component interfaces are minimized (low coupling)
☑ Component cohesion is maximized (functions related to same purpose)
```

**EN 50128 Section 7.3.4.23a**: "The Software Design Specification shall address software components traced back to software architecture and their safety integrity level."

---

### 3. Component Design Phase

**Objective**: Design each component in detail (functions, data structures, algorithms)

**EN 50128 Reference**: Section 7.3.4.22 - "each component having a Software Component Design Specification"

#### 3.1 Design Component Overview

For each component, create a **Component Design Specification** with:
- Component ID
- Component name and description
- Responsibility (what does this component do?)
- SIL level
- Dependencies (other components, modules)
- File names (C source and header)

**Component Design Specification Template**:
```
===============================================
COMPONENT DESIGN SPECIFICATION
===============================================

Component ID: COMP-CTRL-TASK-001
Component Name: Control Task
Description: Main periodic control task that executes control loop every 50ms

Responsibility:
  - Initialize control task
  - Execute periodic control algorithm
  - Coordinate sensor input and actuator output
  - Report control status

SIL Level: 4

Dependencies:
  - Sensor HAL (MOD-SENS)
  - Actuator HAL (MOD-ACT)
  - Control Algorithm (COMP-CTRL-ALG-002)
  - Safety Monitor (MOD-SAFE) for fault reporting

Files:
  - control_task.h (public API, types)
  - control_task.c (implementation)

Traceability:
  - REQ-CTRL-001: Execute control loop every 50ms
  - REQ-CTRL-005: Report control status to Safety Monitor
  - REQ-PERF-010: Control loop WCET ≤ 40ms
```

- [ ] Create Component Design Specification for each component
- [ ] Document component responsibility (single, clear purpose)
- [ ] Document component SIL level
- [ ] Document component dependencies (minimize coupling)
- [ ] Document file organization (header and source)
- [ ] Document traceability to requirements

#### 3.2 Design Component Functions (API)

For each component, design the **public API** (functions exposed in header file) and **private functions** (static functions in source file).

**Function Design Specification**:
```
Function Signature: error_t control_init(const control_config_t* config)

Purpose: Initialize control task with configuration

Parameters:
  - config: Pointer to control configuration structure (NOT NULL)
    - control_period_ms: Control loop period in milliseconds [10..1000]
    - control_mode: Control mode (MANUAL, AUTOMATIC) [enum]

Returns:
  - SUCCESS: Initialization successful
  - ERROR_NULL_POINTER: config is NULL
  - ERROR_INVALID_PERIOD: control_period_ms out of range
  - ERROR_HARDWARE: Hardware initialization failed

Preconditions:
  - System clock initialized
  - Interrupts disabled during initialization

Postconditions:
  - Control task initialized and ready to run
  - Static data structures initialized
  - Timers configured

Error Handling:
  - Validate config pointer (NULL check)
  - Validate control_period_ms range [10..1000]
  - Validate control_mode enum
  - Return error code on failure (no exceptions, no asserts)

SIL Level: 4

Complexity Target: ≤ 8 (well below SIL 4 limit of 10)

MISRA C Compliance:
  - Rule 8.13: config is const pointer (not modified)
  - Rule 17.7: Return value must be checked by caller
  - Rule 21.3: No dynamic memory allocation

Traceability:
  - REQ-CTRL-001: Initialize control loop
  - REQ-SAFE-003: Validate all inputs
```

- [ ] For each function, specify:
  - Function signature (name, parameters, return type)
  - Purpose (one-line description)
  - Parameters (name, type, constraints, valid ranges)
  - Return value (type, meaning, error codes)
  - Preconditions (what must be true before function is called)
  - Postconditions (what will be true after function executes)
  - Error handling (validation, error reporting)
  - SIL level
  - Complexity target (≤10 for SIL 3-4)
  - MISRA C compliance notes
  - Traceability to requirements

**Function Design Checklist (per function)**:
```
☑ Function name is descriptive (verb_noun pattern: get_status, set_mode)
☑ Function signature uses fixed-width types (uint8_t, uint16_t, etc.)
☑ All parameters validated (range checks, NULL checks)
☑ Return type is error_t or specific type (not void for critical functions)
☑ Preconditions documented
☑ Postconditions documented
☑ Error handling strategy documented
☑ Complexity target ≤ SIL limit (10 for SIL 3-4, 15 for SIL 2)
☑ No recursion (SIL 3-4)
☑ No dynamic memory allocation (SIL 2+)
☑ MISRA C compliance notes added
☑ Traceable to requirements
```

**EN 50128 Section 7.3.4.23b**: "The Software Design Specification shall address interfaces of software components with the environment."

**EN 50128 Section 7.3.4.23c**: "The Software Design Specification shall address interfaces between the software components."

#### 3.3 Design Private (Static) Functions

For each component, identify **private functions** (implementation details, not exposed in header).

**Private Function Example**:
```
Function Signature: static bool is_input_valid(const sensor_data_t* data)

Purpose: Validate sensor input data (internal helper function)

Parameters:
  - data: Pointer to sensor data structure (NOT NULL)

Returns:
  - true: Input is valid
  - false: Input is invalid (out of range, stale, etc.)

Visibility: Static (private to control_task.c)

Complexity Target: ≤ 5 (simple validation logic)

Usage: Called by control_run() to validate inputs before processing
```

- [ ] Identify private functions needed for implementation
- [ ] Mark private functions as `static` (C linkage)
- [ ] Document private functions (same level of detail as public API)
- [ ] Ensure private functions do not increase complexity unnecessarily

---

### 4. Interface Design Phase

**Objective**: Define precise interfaces for all component interactions

**EN 50128 Reference**: Section 7.3.4.23b, 7.3.4.23c - Component interfaces with environment and between components

#### 4.1 External Interfaces (Hardware, Software, Communication)

For components that interact with external systems (hardware, other software, communication buses), design external interfaces.

**Hardware Interface Example (CAN Bus)**:
```
Component: CAN HAL (Hardware Abstraction Layer)

Hardware: CAN controller (e.g., MCP2515, on-chip CAN peripheral)

Interface Type: SPI (for external controller) or Memory-Mapped I/O (for on-chip)

Functions:
  - error_t can_init(const can_config_t* config)
  - error_t can_send(const can_message_t* msg)
  - error_t can_receive(can_message_t* msg, uint32_t timeout_ms)
  - error_t can_set_filter(uint16_t filter_id, uint16_t mask)

Data Structures:
  - can_config_t: Configuration (baudrate, mode, interrupts)
  - can_message_t: CAN frame (ID, DLC, data[8], timestamp)

C Constraints:
  - Static allocation: static can_message_t tx_queue[16]; (fixed-size queue)
  - No dynamic CAN ID allocation
  - Bounded timeout: timeout_ms must be finite (no infinite wait)

Timing Constraints:
  - can_send() WCET: ≤ 500 µs
  - can_receive() WCET: ≤ 100 µs (if message available, else return TIMEOUT)
```

- [ ] For each external interface, specify:
  - Interface type (hardware: GPIO, SPI, CAN, UART; software: API; communication: protocol)
  - Functions for interface access
  - Data structures for interface data
  - Timing constraints (WCET, deadlines)
  - C constraints (static allocation, fixed-width types)
  - Error handling (timeout, CRC errors, framing errors)

#### 4.2 Internal Interfaces (Component-to-Component)

For components that interact with other components, design internal interfaces.

**Internal Interface Example**:
```
Provider Component: Sensor HAL
Consumer Component: Control Task

Interface: Sensor data provision

Functions (Sensor HAL API):
  - error_t sensor_init(void)
  - error_t sensor_read(sensor_data_t* data)
  - bool sensor_is_ready(void)

Data Flow:
  Control Task calls sensor_read() → Sensor HAL reads ADC → Returns sensor_data_t

Data Structure:
  typedef struct {
    uint16_t temperature;    // [0..1023] → 0..100°C
    uint16_t pressure;       // [0..1023] → 0..1000 kPa
    uint16_t speed;          // [0..65535] → 0..300 km/h
    uint32_t timestamp_ms;   // Milliseconds since boot
    uint8_t status;          // Sensor status flags (bit field)
  } sensor_data_t;

Synchronization: None (sensor_read() is blocking, returns when data ready)

Error Handling:
  - sensor_read() returns ERROR_NOT_READY if sensor not initialized
  - sensor_read() returns ERROR_TIMEOUT if sensor does not respond in 10ms
```

- [ ] For each internal interface, specify:
  - Provider component (who provides the interface)
  - Consumer component (who uses the interface)
  - Functions (API calls)
  - Data flow direction
  - Data structures exchanged
  - Synchronization (blocking, non-blocking, interrupt-driven)
  - Error handling

**Interface Design Checklist**:
```
☑ All interfaces clearly defined (provider, consumer)
☑ All function signatures specified (parameters, return types)
☑ All data structures specified (fixed-width types)
☑ Data flow direction documented
☑ Synchronization strategy documented (blocking, non-blocking, ISR)
☑ Error handling strategy documented (error codes, timeouts)
☑ Timing constraints documented (WCET, deadlines)
☑ C constraints applied (static allocation, no dynamic memory)
☑ MISRA C compliance (const pointers, return value checks)
```

**EN 50128 Section 7.3.4.23c**: "The Software Design Specification shall address interfaces between the software components."

---

### 5. Data Structure Design Phase

**Objective**: Design all data structures (global, module-local, component-local) with C language constraints

**EN 50128 Reference**: Section 7.3.4.23d - "The Software Design Specification shall address data structures."

#### 5.1 Identify Data Structure Requirements

- [ ] For each component, list all data structures needed:
  - Configuration data (parameters, settings)
  - State data (current state, mode, status)
  - Input/output buffers (sensor data, command data)
  - Internal working data (intermediate results, temporary storage)
  - Logging/diagnostic data (fault logs, event logs)

**Data Structure Identification Example**:
```
Component: Control Task

Data Structures Needed:
  1. control_config_t - Configuration (control period, mode, gains)
  2. control_state_t - Current state (position, velocity, error)
  3. control_output_t - Output commands (actuator commands)
  4. control_status_t - Status (health, faults, diagnostics)
  5. input_buffer_t[16] - Circular buffer for sensor inputs
```

#### 5.2 Design Data Structures (C Structs, Enums, Arrays)

For each data structure, design the C type definition with:
- Fixed-width types (uint8_t, uint16_t, uint32_t, int8_t, etc.)
- Static allocation (no pointers to dynamically allocated memory)
- Clear documentation (units, ranges, meaning)
- Alignment considerations (for performance and determinism)

**Data Structure Design Example (Control Configuration)**:
```c
/**
 * @brief Control task configuration
 * @details Configuration parameters for periodic control task
 * SIL: 4
 */
typedef struct {
    uint16_t period_ms;           ///< Control loop period [10..1000] ms
    uint8_t mode;                 ///< Control mode (MANUAL=0, AUTOMATIC=1)
    uint8_t reserved;             ///< Reserved for alignment (pad to 4 bytes)
    
    // PID controller gains (Q15 fixed-point: 1.0 = 32767)
    int16_t kp;                   ///< Proportional gain [-32768..32767] (Q15)
    int16_t ki;                   ///< Integral gain [-32768..32767] (Q15)
    int16_t kd;                   ///< Derivative gain [-32768..32767] (Q15)
    
    uint16_t output_limit;        ///< Output saturation limit [0..1023]
} control_config_t;

// Static allocation (SIL 2+ MANDATORY)
static control_config_t g_control_config;
```

**Data Structure Design Example (Circular Buffer)**:
```c
/**
 * @brief Sensor input circular buffer
 * @details Fixed-size circular buffer for sensor inputs (no dynamic allocation)
 * SIL: 4
 */
#define INPUT_BUFFER_SIZE 16  ///< Power of 2 for efficient modulo

typedef struct {
    sensor_data_t data[INPUT_BUFFER_SIZE];  ///< Sensor data array (static)
    uint8_t head;                            ///< Write index [0..15]
    uint8_t tail;                            ///< Read index [0..15]
    uint8_t count;                           ///< Number of items [0..16]
    uint8_t reserved;                        ///< Reserved for alignment
} input_buffer_t;

// Static allocation (SIL 2+ MANDATORY)
static input_buffer_t g_input_buffer;
```

- [ ] For each data structure, specify:
  - Type name (suffix `_t` for types)
  - Purpose and description
  - SIL level
  - All fields with fixed-width types (uint8_t, uint16_t, etc.)
  - Field ranges and units (document in comments)
  - Alignment/padding considerations (explicit reserved fields if needed)
  - Static allocation strategy (global static, module static, function static)

**Data Structure Design Checklist**:
```
☑ All types use fixed-width integer types (uint8_t, uint16_t, uint32_t, int8_t, etc.)
☑ NO use of int, long, short, unsigned int (platform-dependent sizes)
☑ All floating-point use is justified (or use fixed-point instead)
☑ All structures are statically allocated (static keyword)
☑ All arrays have compile-time constant sizes (e.g., [16], not [n])
☑ All fields are documented (Doxygen comments with ranges, units)
☑ Alignment is explicit (add reserved fields if needed for padding)
☑ No pointers to dynamically allocated memory (SIL 2+ MANDATORY)
☑ Enums are used for discrete states (not magic numbers)
☑ Bit fields are avoided (or carefully justified with explicit widths)
```

#### 5.3 Memory Allocation Strategy

- [ ] Document memory allocation strategy per SIL level:
  - **SIL 0-1**: Static or dynamic (if justified)
  - **SIL 2+**: Static allocation **MANDATORY**

**Memory Allocation Table**:
```
Data Structure          | Type             | Size (bytes) | Allocation | Justification
------------------------|------------------|--------------|------------|---------------------------
g_control_config        | control_config_t | 12           | Static     | SIL 4 (static MANDATORY)
g_control_state         | control_state_t  | 20           | Static     | SIL 4 (static MANDATORY)
g_input_buffer          | input_buffer_t   | 320          | Static     | SIL 4 (static MANDATORY)
g_fault_log             | fault_log_t[32]  | 1024         | Static     | SIL 4 (static MANDATORY)
TOTAL                   |                  | 1376         |            |

Maximum RAM Usage: 1376 bytes
Available RAM: 128 KB (131,072 bytes)
RAM Utilization: 1.05%
```

- [ ] Calculate total memory usage
- [ ] Verify memory usage fits within constraints (e.g., 128 KB RAM)
- [ ] Document allocation strategy (static global, static module, static function)

**EN 50128 Section 7.3.4.23d**: "The Software Design Specification shall address data structures."

**MISRA C:2012 Rule 21.3**: "The memory allocation and deallocation functions of <stdlib.h> shall not be used." (MANDATORY for SIL 2+)

---

### 6. Algorithm Design Phase

**Objective**: Design algorithms for each component function with complexity constraints

**EN 50128 Reference**: Section 7.3.4.23f - "The Software Design Specification shall address main algorithms and sequencing."

#### 6.1 Algorithm Identification

For each component function, identify the algorithm(s) needed.

**Algorithm Identification Example**:
```
Function: control_compute_pid()
  Algorithm: PID (Proportional-Integral-Derivative) control
  Inputs: setpoint, measured_value, dt
  Outputs: control_output
  Description: Compute PID control output from error signal
  Complexity Target: ≤ 8 (simple PID equation)

Function: safety_check_speed()
  Algorithm: Overspeed detection with hysteresis
  Inputs: current_speed, speed_limit, hysteresis
  Outputs: overspeed_fault (bool)
  Description: Detect overspeed condition with hysteresis to prevent oscillation
  Complexity Target: ≤ 5 (simple threshold with hysteresis)

Function: can_receive()
  Algorithm: Circular buffer dequeue
  Inputs: timeout_ms
  Outputs: can_message_t
  Description: Dequeue CAN message from circular buffer, wait for timeout
  Complexity Target: ≤ 6 (dequeue + timeout check)
```

- [ ] For each function, identify the algorithm
- [ ] Document algorithm inputs and outputs
- [ ] Document algorithm description (high-level logic)
- [ ] Set complexity target (≤10 for SIL 3-4)

#### 6.2 Algorithm Design (Pseudocode or Flowchart)

For each algorithm, design the logic using pseudocode or flowchart.

**Pseudocode Example (PID Control)**:
```
ALGORITHM: control_compute_pid
INPUTS: setpoint (uint16_t), measured_value (uint16_t), dt (uint16_t)
OUTPUTS: control_output (int16_t)
SIL: 4
COMPLEXITY TARGET: ≤ 8

PSEUDOCODE:
  // Compute error
  error = setpoint - measured_value
  
  // Proportional term
  P = kp * error
  
  // Integral term (with anti-windup)
  integral = integral + error * dt
  IF integral > integral_max THEN
    integral = integral_max
  END IF
  IF integral < integral_min THEN
    integral = integral_min
  END IF
  I = ki * integral
  
  // Derivative term
  D = kd * (error - previous_error) / dt
  previous_error = error
  
  // PID output (with saturation)
  output = P + I + D
  IF output > output_max THEN
    output = output_max
  END IF
  IF output < output_min THEN
    output = output_min
  END IF
  
  RETURN output

COMPLEXITY ANALYSIS:
  - Linear control flow (no nested loops)
  - 5 conditional statements (anti-windup, derivative, saturation)
  - Estimated cyclomatic complexity: 6 (within target ≤ 8)
```

**Flowchart Example (Overspeed Detection)**:
```
┌─────────────────────┐
│ START               │
└──────┬──────────────┘
       │
       ▼
┌─────────────────────┐
│ Read current_speed  │
│ Read speed_limit    │
└──────┬──────────────┘
       │
       ▼
   ┌───────────────────────┐
   │ speed > speed_limit?  │
   └───┬───────────────┬───┘
       │ YES           │ NO
       ▼               ▼
┌────────────────┐  ┌──────────────────────┐
│ Set fault flag │  │ speed < speed_limit  │
│                │  │   - hysteresis?      │
└────────┬───────┘  └───┬──────────────┬───┘
         │              │ YES          │ NO
         │              ▼              │
         │          ┌────────────────┐ │
         │          │ Clear fault    │ │
         │          │ flag           │ │
         │          └───────┬────────┘ │
         │                  │          │
         └──────────────────┴──────────┘
                    │
                    ▼
              ┌──────────┐
              │ RETURN   │
              └──────────┘

COMPLEXITY: 2 decision points → Cyclomatic Complexity = 3 (well within ≤ 10)
```

- [ ] For each algorithm, create pseudocode or flowchart
- [ ] Document algorithm inputs, outputs, and logic
- [ ] Estimate cyclomatic complexity (count decision points)
- [ ] Verify complexity ≤ target (10 for SIL 3-4, 15 for SIL 2)
- [ ] Identify opportunities to reduce complexity if needed

**Complexity Reduction Strategies**:
```
IF complexity > target THEN:
  1. Extract nested logic into separate functions
     Example: Replace nested if-else with function call
  
  2. Use lookup tables instead of complex conditionals
     Example: Replace switch-case with array lookup
  
  3. Simplify boolean expressions
     Example: Use De Morgan's laws to reduce nesting
  
  4. Use state machines for complex control flow
     Example: Replace nested if-else with state machine table
  
  5. Break function into multiple smaller functions
     Example: Split function into initialization + processing
```

#### 6.3 Algorithm Performance Analysis

- [ ] For each algorithm, analyze performance:
  - Worst-Case Execution Time (WCET)
  - Memory usage (stack, static data)
  - Determinism (bounded execution, no unbounded loops)

**Algorithm Performance Analysis Example**:
```
ALGORITHM: control_compute_pid
WCET ESTIMATE: 500 CPU cycles @ 100 MHz = 5 µs
  - Arithmetic operations: 200 cycles
  - Conditional branches: 100 cycles
  - Memory accesses: 200 cycles

MEMORY USAGE:
  - Stack: 32 bytes (local variables)
  - Static data: 20 bytes (integral, previous_error, config)

DETERMINISM:
  - No loops (linear control flow)
  - No recursion
  - Bounded execution (all paths have fixed number of operations)
  - WCET guarantee: 5 µs ± 0.5 µs
```

- [ ] Estimate WCET for each function
- [ ] Verify WCET meets timing requirements (e.g., control loop 50ms → each function WCET < 5ms)
- [ ] Document determinism properties (bounded loops, no recursion)

**EN 50128 Section 7.3.4.23f**: "The Software Design Specification shall address main algorithms and sequencing."

**EN 50128 Section 7.3.4.28b**: Design method shall facilitate "the clear and precise expression of... 3) sequencing and time related information."

---

### 7. Error Handling Design Phase

**Objective**: Design error detection, reporting, and handling for all components

**EN 50128 Reference**: Section 7.3.4.23g - "The Software Design Specification shall address error reporting mechanisms."

#### 7.1 Error Classification

Classify errors by severity and handling strategy:

**Error Severity Levels**:
```
CRITICAL (SIL 4):
  - System safety violated (e.g., overspeed, brake failure)
  - Action: Enter safe state immediately, report to Safety Monitor
  - Example: Sensor failure in safety-critical control loop

MAJOR (SIL 2-3):
  - System function degraded but safe (e.g., communication timeout)
  - Action: Report fault, attempt recovery, degrade to safe mode
  - Example: CAN bus timeout (switch to backup communication)

MINOR (SIL 0-1):
  - Non-critical function degraded (e.g., diagnostic failure)
  - Action: Log error, continue operation
  - Example: Non-critical sensor out of range

INFORMATIONAL:
  - Status information (not an error)
  - Action: Log for diagnostics
  - Example: Mode change, configuration update
```

- [ ] For each component, classify potential errors by severity
- [ ] Define error handling strategy per severity level

#### 7.2 Error Detection Strategy

**Defensive Programming (MANDATORY SIL 3-4, HR SIL 2)**:
```
1. Input Validation (ALL inputs):
   - NULL pointer checks
   - Range checks (min, max)
   - Enum value checks (valid enumeration)
   - Consistency checks (e.g., timestamp newer than previous)

2. Return Value Checks (ALL function calls):
   - Check error codes from all function calls
   - Handle all error conditions
   - Never ignore return values (MISRA C Rule 17.7)

3. Assertions (Internal Consistency):
   - Verify internal state consistency
   - Verify data structure invariants
   - Example: assert(buffer.count <= BUFFER_SIZE)

4. Watchdog Monitoring:
   - Periodically reset watchdog timer
   - Detect infinite loops or deadlocks
   - Timeout if task does not execute within expected period
```

**Error Detection Example (Input Validation)**:
```c
/**
 * @brief Validate sensor data
 * @param[in] data Pointer to sensor data (NOT NULL)
 * @return true if valid, false if invalid
 */
static bool validate_sensor_data(const sensor_data_t* data)
{
    // NULL pointer check
    if (data == NULL) {
        return false;
    }
    
    // Range checks
    if (data->temperature > 1023) {  // ADC 10-bit: [0..1023]
        return false;
    }
    if (data->pressure > 1023) {
        return false;
    }
    if (data->speed > 65535) {  // 16-bit: [0..65535]
        return false;
    }
    
    // Timestamp consistency (monotonic increasing)
    static uint32_t last_timestamp = 0;
    if (data->timestamp_ms < last_timestamp) {
        return false;  // Timestamp went backwards (error)
    }
    last_timestamp = data->timestamp_ms;
    
    // Status flag check (bit 7 = valid data)
    if ((data->status & 0x80) == 0) {
        return false;  // Status indicates invalid data
    }
    
    return true;  // All checks passed
}
```

- [ ] For each component function, design error detection:
  - Input validation (NULL, range, enum, consistency)
  - Return value checks (for all function calls)
  - Internal consistency checks (assertions, invariants)

**EN 50128 Table A.3 Technique 2**: Defensive Programming (HR for SIL 3-4) - D.14

#### 7.3 Error Reporting Strategy

**Error Reporting Mechanism**:
```
1. Error Codes (Function Return Values):
   - All functions return error_t (enum or uint8_t)
   - Error codes are unique and meaningful
   - Example: SUCCESS, ERROR_NULL_POINTER, ERROR_TIMEOUT, ERROR_HARDWARE

2. Error Logging (Fault Log):
   - Log all critical and major errors
   - Include: timestamp, error code, component ID, context
   - Fixed-size circular buffer (static allocation)

3. Safety Monitor Notification:
   - Report critical errors to Safety Monitor immediately
   - Safety Monitor decides on safe state transition
   - Example: safety_report_fault(FAULT_SENSOR_FAILURE, SENSOR_SPEED)

4. Diagnostic Interface:
   - Provide diagnostic functions to query error status
   - Example: get_last_error(), get_fault_count(), get_fault_log()
```

**Error Code Design Example**:
```c
/**
 * @brief Error codes
 */
typedef enum {
    SUCCESS = 0,              ///< Operation successful
    ERROR_NULL_POINTER = 1,   ///< NULL pointer passed as argument
    ERROR_INVALID_PARAM = 2,  ///< Invalid parameter (out of range)
    ERROR_TIMEOUT = 3,        ///< Operation timed out
    ERROR_HARDWARE = 4,       ///< Hardware failure
    ERROR_NOT_READY = 5,      ///< Component not initialized
    ERROR_OVERFLOW = 6,       ///< Buffer overflow
    ERROR_UNDERFLOW = 7,      ///< Buffer underflow
    ERROR_CRC = 8,            ///< CRC check failed
    ERROR_UNKNOWN = 255       ///< Unknown error
} error_t;
```

**Fault Log Design Example**:
```c
/**
 * @brief Fault log entry
 */
typedef struct {
    uint32_t timestamp_ms;    ///< Timestamp (milliseconds since boot)
    uint8_t component_id;     ///< Component ID (MOD-CTRL, MOD-SAFE, etc.)
    uint8_t error_code;       ///< Error code (from error_t enum)
    uint16_t context;         ///< Context-specific information (e.g., line number)
} fault_log_entry_t;

#define FAULT_LOG_SIZE 32  ///< Circular buffer size (power of 2)

/**
 * @brief Fault log (circular buffer)
 */
typedef struct {
    fault_log_entry_t entries[FAULT_LOG_SIZE];  ///< Log entries (static)
    uint8_t head;                                 ///< Write index [0..31]
    uint8_t count;                                ///< Number of entries [0..32]
} fault_log_t;

// Static allocation (SIL 2+ MANDATORY)
static fault_log_t g_fault_log;

/**
 * @brief Log fault to circular buffer
 */
void fault_log_add(uint8_t component_id, uint8_t error_code, uint16_t context)
{
    // Add entry to circular buffer
    g_fault_log.entries[g_fault_log.head].timestamp_ms = get_time_ms();
    g_fault_log.entries[g_fault_log.head].component_id = component_id;
    g_fault_log.entries[g_fault_log.head].error_code = error_code;
    g_fault_log.entries[g_fault_log.head].context = context;
    
    // Update head and count (circular buffer logic)
    g_fault_log.head = (g_fault_log.head + 1) & (FAULT_LOG_SIZE - 1);  // Wrap-around
    if (g_fault_log.count < FAULT_LOG_SIZE) {
        g_fault_log.count++;
    }
}
```

- [ ] Design error code enumeration (unique, meaningful codes)
- [ ] Design fault log structure (circular buffer, static allocation)
- [ ] Design fault logging functions (add, query)
- [ ] Design error reporting to Safety Monitor (for critical errors)

**EN 50128 Section 7.3.4.23g**: "The Software Design Specification shall address error reporting mechanisms."

#### 7.4 Error Handling and Recovery

**Error Handling Strategy**:
```
1. Local Recovery (if possible):
   - Retry operation (with retry limit, e.g., 3 attempts)
   - Use default value (safe default)
   - Degrade to backup mode (e.g., use last known good value)

2. Component-Level Recovery:
   - Reinitialize component
   - Reset state to known safe state
   - Report error to higher-level component

3. System-Level Recovery:
   - Report to Safety Monitor
   - Safety Monitor decides on safe state transition
   - Example: Enter SAFE_STOP state (halt all motion)

4. No Recovery (Critical Errors):
   - Enter safe state immediately
   - Halt system
   - Require manual intervention or system reset
   - Example: Critical hardware failure (brake actuator failure)
```

**Error Handling Example**:
```c
/**
 * @brief Read sensor with retry and error handling
 */
error_t sensor_read_with_retry(sensor_data_t* data)
{
    error_t result;
    uint8_t retry_count = 0;
    const uint8_t MAX_RETRIES = 3;
    
    // Input validation
    if (data == NULL) {
        fault_log_add(COMP_SENSOR, ERROR_NULL_POINTER, __LINE__);
        return ERROR_NULL_POINTER;
    }
    
    // Retry loop (bounded)
    while (retry_count < MAX_RETRIES) {
        result = sensor_read_raw(data);
        
        if (result == SUCCESS) {
            // Validate data
            if (validate_sensor_data(data)) {
                return SUCCESS;  // Success
            } else {
                result = ERROR_INVALID_PARAM;
            }
        }
        
        retry_count++;
        delay_ms(10);  // Wait before retry
    }
    
    // All retries failed
    fault_log_add(COMP_SENSOR, result, retry_count);
    
    // Use last known good value (degraded mode)
    *data = g_last_good_sensor_data;
    
    // Report to Safety Monitor (critical error)
    safety_report_fault(FAULT_SENSOR_FAILURE, SENSOR_SPEED);
    
    return result;  // Return error code
}
```

- [ ] For each error type, design recovery strategy
- [ ] Document retry logic (with bounded retry count)
- [ ] Document degraded mode operation (safe defaults, backup values)
- [ ] Document safe state transition (for critical errors)

**EN 50128 Table A.3 Technique 3**: Fault Detection and Diagnosis (R for SIL 1-2, HR for SIL 3-4) - D.26

---

### 8. Apply C Design Constraints

**Objective**: Ensure all designs comply with C language constraints for EN 50128

**EN 50128 Reference**: Table A.4, Table A.12 (Good Programming Practice)

#### 8.1 Static Allocation Review (SIL 2+ MANDATORY)

- [ ] Review all data structures: Verify all are statically allocated
- [ ] Search for forbidden functions: No malloc, calloc, realloc, free
- [ ] Verify all arrays have compile-time constant sizes
- [ ] Verify all pointers point to static storage (not dynamic memory)

**Static Allocation Verification Checklist**:
```
☑ No malloc() calls in any design
☑ No calloc() calls in any design
☑ No realloc() calls in any design
☑ No free() calls in any design
☑ All arrays declared as: type array[SIZE] where SIZE is compile-time constant
☑ All structs declared as: static type_t instance;
☑ All buffers are fixed-size (e.g., uint8_t buffer[256], not uint8_t* buffer)
☑ No variable-length arrays (VLAs) (int array[n] where n is runtime variable)
```

**MISRA C:2012 Rule 21.3**: "The memory allocation and deallocation functions of <stdlib.h> shall not be used." (MANDATORY for SIL 2+)

#### 8.2 Recursion Review (SIL 3-4 HR, MANDATORY for this project)

- [ ] Review all function call graphs: Verify no recursive calls
- [ ] Identify any recursive algorithms: Refactor to iterative
- [ ] Document call graph (ensure acyclic)

**Recursion Verification**:
```
FORBIDDEN PATTERN (Recursion):
  void factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);  // RECURSIVE CALL FORBIDDEN
  }

ALLOWED PATTERN (Iteration):
  int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {  // ITERATIVE LOOP OK
      result *= i;
    }
    return result;
  }
```

**MISRA C:2012 Rule 17.2**: "Functions shall not call themselves, either directly or indirectly." (MANDATORY for SIL 3-4)

#### 8.3 Complexity Review

- [ ] Review all function designs: Estimate cyclomatic complexity
- [ ] Verify complexity ≤ target: 10 (SIL 3-4), 15 (SIL 2), 20 (SIL 0-1)
- [ ] Refactor high-complexity functions (break into smaller functions, use lookup tables, simplify conditionals)

**Complexity Calculation (McCabe Cyclomatic Complexity)**:
```
Complexity = Number of decision points + 1

Decision points:
  - if, else if
  - switch (case)
  - for, while, do-while loops
  - Logical operators (&&, ||) in conditions
  - Ternary operator (? :)

Example:
  int compute(int x) {
    if (x > 10) {        // Decision 1
      return x * 2;
    } else if (x > 5) {  // Decision 2
      return x + 10;
    } else {
      return x;
    }
  }
  Complexity = 2 + 1 = 3 ✓ (within limit)

Example (High Complexity):
  int complex_function(int a, int b, int c) {
    if (a > 0) {             // Decision 1
      if (b > 0) {           // Decision 2
        if (c > 0) {         // Decision 3
          return a + b + c;
        } else {
          return a + b;
        }
      } else {
        return a;
      }
    } else if (a < 0) {      // Decision 4
      return -a;
    } else {
      return 0;
    }
  }
  Complexity = 4 + 1 = 5 ✓ (within limit, but nested)

REFACTORED (Lower Nesting):
  int compute_positive(int a, int b, int c) {
    return a + b + c;
  }
  
  int complex_function(int a, int b, int c) {
    if (a > 0 && b > 0 && c > 0) return compute_positive(a, b, c);
    if (a > 0 && b > 0) return a + b;
    if (a > 0) return a;
    if (a < 0) return -a;
    return 0;
  }
  Complexity = 4 + 1 = 5 (same, but flatter structure, easier to understand)
```

**Complexity Reduction Strategies**:
1. Extract nested logic into separate functions
2. Use lookup tables instead of nested if-else
3. Simplify boolean expressions (De Morgan's laws)
4. Use state machines for complex control flow
5. Replace switch-case with array-based dispatch

- [ ] Estimate complexity for all functions at design phase
- [ ] Refactor if complexity > target
- [ ] Document complexity analysis in design

#### 8.4 Fixed-Width Types Review

- [ ] Review all type definitions: Verify use of fixed-width types (uint8_t, uint16_t, uint32_t, int8_t, int16_t, int32_t)
- [ ] Search for platform-dependent types: No int, long, short, unsigned int, unsigned long, unsigned short
- [ ] Review floating-point usage: Justify (or use fixed-point instead)

**Fixed-Width Type Checklist**:
```
☑ Use uint8_t instead of unsigned char
☑ Use uint16_t instead of unsigned short
☑ Use uint32_t instead of unsigned int or unsigned long
☑ Use int8_t instead of signed char
☑ Use int16_t instead of short
☑ Use int32_t instead of int or long
☑ Avoid size_t (platform-dependent, use uint32_t or uint16_t)
☑ Avoid ptrdiff_t (platform-dependent)
☑ Use bool (from stdbool.h) for boolean types (or uint8_t)
```

**MISRA C:2012 Directive 4.6**: "typedefs that indicate size and signedness should be used in place of the basic numerical types." (ADVISORY, but MANDATORY for this project)

#### 8.5 Bounded Execution Review

- [ ] Review all loops: Verify all loops are bounded (no infinite loops, except main task loop with watchdog)
- [ ] Review all function calls: Verify no blocking calls without timeout
- [ ] Document worst-case execution time (WCET) for all functions

**Bounded Loop Checklist**:
```
FORBIDDEN (Unbounded Loop):
  while (data_available()) {  // UNBOUNDED: Could loop forever
    process_data();
  }

ALLOWED (Bounded Loop):
  uint8_t max_iterations = 100;
  uint8_t count = 0;
  while (data_available() && count < max_iterations) {  // BOUNDED: Max 100 iterations
    process_data();
    count++;
  }

ALLOWED (Main Task Loop with Watchdog):
  while (1) {  // Infinite loop OK for main task
    watchdog_reset();  // Reset watchdog to prove liveness
    execute_task();
    delay_until_next_period();
  }
```

- [ ] Verify all loops have explicit bounds (for, while with counter)
- [ ] Verify all blocking calls have timeouts (e.g., wait_for_event(timeout_ms))
- [ ] Document WCET for each function

**EN 50128 Section 7.3.4.28b**: Design method shall facilitate "sequencing and time related information."

---

### 9. Apply EN 50128 Techniques (Table A.4)

**Objective**: Apply mandatory EN 50128 design techniques per SIL level

**EN 50128 Reference**: Section 7.3.4.24, Table A.4

#### 9.1 Verify Technique Application

Review Table A.4 and verify all mandatory techniques are applied:

**SIL 3-4 Mandatory Techniques** (from Table A.4):
1. **Structured Methodology** (M) - D.52
2. **Modular Approach** (M) - D.38
3. **Design and Coding Standards** (M) - A.12
4. **Analysable Programs** (M) - D.2
5. **Structured Programming** (M) - D.53

**Technique Verification Checklist (SIL 3-4)**:
```
☑ Structured Methodology (M):
  - Systematic design process followed (requirements → architecture → design → code)
  - Design documented with standard notation (UML, flowcharts, pseudocode)
  - Design reviews performed at each phase
  - Traceability maintained (requirements → design → code)

☑ Modular Approach (M):
  - System decomposed into modules with clear responsibilities
  - Module interfaces well-defined (function signatures, data structures)
  - Module coupling minimized (few dependencies)
  - Module cohesion maximized (related functions grouped)
  - Information hiding applied (static functions for private implementation)

☑ Design and Coding Standards (M):
  - Coding standards defined and documented (MISRA C:2012 + project rules)
  - Coding standards referenced in SQAP (Section 7.3.4.27)
  - Good programming practice applied (Table A.12)
  - Error detection measures specified
  - Source code documentation procedures defined

☑ Analysable Programs (M):
  - Program structure is simple and understandable
  - Control flow is straightforward (no goto, minimal nesting)
  - Data flow is clear (no hidden side effects)
  - Complexity is low (≤ 10 for SIL 3-4)
  - Static analysis can be performed effectively

☑ Structured Programming (M):
  - Control structures are limited (if-else, for, while, switch-case)
  - No goto statements
  - Single entry, single exit for functions (or minimal early returns with justification)
  - No arbitrary jumps (setjmp/longjmp forbidden)
```

**EN 50128 Annex D.52 (Structured Methodology)**:
- "A structured methodology imposes a disciplined approach to the design process."
- "Examples: SSADM, JSD, Yourdon, Jackson, SADT, OOD."
- For C programs: Use systematic decomposition (requirements → architecture → detailed design → pseudocode → code)

**EN 50128 Annex D.38 (Modular Approach)**:
- "The structure of software shall be modular with strong partitioning."
- "Modules shall have high functional cohesion and low coupling."
- "Interfaces shall be clearly defined and minimal."

**EN 50128 Annex D.2 (Analysable Programs)**:
- "The program structure shall facilitate comprehension, review, and testing."
- "Avoid complex data structures, deeply nested control structures, and obscure programming practices."

**EN 50128 Annex D.53 (Structured Programming)**:
- "Use only structured control constructs: sequence, selection (if-else, switch-case), iteration (for, while)."
- "Avoid goto, break (except in switch), continue."
- "Single entry, single exit per function (recommended)."

#### 9.2 Document Technique Justification

**EN 50128 Section 7.3.4.24**: "The Software Design Specification shall choose techniques and measures from Table A.4. The selected combination shall be justified as a set satisfying 4.8 and 4.9."

- [ ] Document which techniques from Table A.4 are applied
- [ ] Justify the selected combination per Section 4.8 and 4.9
- [ ] For SIL 3-4, verify approved combination is used

**Technique Justification Example (SIL 4)**:
```
EN 50128 TABLE A.4 TECHNIQUE JUSTIFICATION
Project: Train Control System
SIL Level: 4

SELECTED TECHNIQUES:
1. Structured Methodology (M) - Applied
   Justification: Systematic design process from SRS → SAS → SDS → Code.
                  UML diagrams, flowcharts, and pseudocode used for design documentation.
                  Design reviews performed at each phase (peer, QUA, VER).
                  Full traceability from requirements to code maintained.

2. Modular Approach (M) - Applied
   Justification: System decomposed into 8 modules (Control, Safety, Sensor HAL, etc.).
                  Each module has clear responsibility and minimal interfaces.
                  Module coupling: Low (modules communicate via well-defined APIs).
                  Module cohesion: High (related functions grouped per module).
                  Information hiding: Static functions used for private implementation.

3. Design and Coding Standards (M) - Applied
   Justification: MISRA C:2012 mandatory for all code (zero mandatory violations).
                  Project coding standards document defines naming, commenting, error handling.
                  Coding standards referenced in SQAP (Section 5.3).
                  Static analysis tools (PC-lint Plus, Cppcheck) used to enforce standards.

4. Analysable Programs (M) - Applied
   Justification: All functions designed with complexity ≤ 10 (SIL 4 limit).
                  Control flow is straightforward (no goto, minimal nesting).
                  Data flow is explicit (no global variables except static module data).
                  Static analysis performed with Cppcheck, Clang Static Analyzer.

5. Structured Programming (M) - Applied
   Justification: Only structured control constructs used (if-else, for, while, switch-case).
                  No goto, setjmp, longjmp.
                  Single entry, single exit for functions (with justified early returns for error handling).
                  No arbitrary jumps or complex control flow.

6. Strongly Typed Language (HR) - Applied
   Justification: C with fixed-width types (uint8_t, uint16_t, uint32_t, int8_t, etc.).
                  MISRA C:2012 enforces strong typing (no implicit conversions).
                  All function parameters and return values explicitly typed.

APPROVED COMBINATION (SIL 3-4):
  Table A.4 Note: 4, 5, 6, 8 + one from {1 or 2}
  Our combination: 1, 2, 3, 4, 5, 6 (exceeds minimum requirements)

JUSTIFICATION PER SECTION 4.8 AND 4.9:
  Section 4.8: Techniques are appropriate for SIL 4 (all mandatory techniques applied).
  Section 4.9: Techniques are compatible (no conflicts).
               Structured Methodology provides overall process framework.
               Modular Approach provides architectural structure.
               Design and Coding Standards enforce quality.
               Analysable Programs and Structured Programming ensure comprehension and verification.
```

- [ ] Create technique justification document (include in SDS Section 10)
- [ ] Verify all mandatory techniques for SIL level are applied
- [ ] Verify approved combination is used (for SIL 3-4)

---

### 10. Document Design (Create SDS)

**Objective**: Create the formal Software Design Specification (SDS) document

**EN 50128 Reference**: Section 7.3.4.20-7.3.4.24

#### 10.1 Copy SDS Template

- [ ] Copy template: `.opencode/skills/en50128-design/templates/Software-Design-Specification-template.md`
- [ ] Create SDS document: `docs/design/Software-Design-Specification.md`
- [ ] Fill in document header (Document ID, Version, Project, SIL, Author, etc.)

**Command**:
```bash
mkdir -p docs/design
cp .opencode/skills/en50128-design/templates/Software-Design-Specification-template.md \
   docs/design/Software-Design-Specification.md
```

#### 10.2 Fill in SDS Sections

**EN 50128 Section 7.3.4.23**: The Software Design Specification shall address:
- a) software components traced back to software architecture and their safety integrity level
- b) interfaces of software components with the environment
- c) interfaces between the software components
- d) data structures
- e) allocation and tracing of requirements on components
- f) main algorithms and sequencing
- g) error reporting mechanisms

**SDS Template Sections** (from template):
1. Introduction (Purpose, Scope, SIL, Definitions, References)
2. Design Overview (Module summary, Design conventions)
3. Module Designs (One section per module)
   - Module overview
   - Component designs (Component Design Specification per component)
     - Component ID, Name, Description
     - Functions (API specifications)
     - Data structures
     - Algorithms (pseudocode/flowcharts)
     - Error handling
     - Complexity analysis
     - Traceability to architecture and requirements
4. Traceability to Architecture (Architecture components → Design components → Requirements)
5. Component Interfaces (External and internal interfaces)
6. Data Structures (Global, module-local, component-local)
7. Algorithms and Sequencing (Main algorithms, control flow, timing)
8. Error Reporting Mechanisms (Error codes, fault log, Safety Monitor reporting)
9. Component Test Specifications (Unit test plan per component)
10. Coding Standards (MISRA C:2012, project-specific rules)
11. Technique Justification (Table A.4 techniques, justification per Section 4.8, 4.9)

- [ ] Fill in Section 1 (Introduction): Purpose, Scope, SIL, Definitions, References
- [ ] Fill in Section 2 (Design Overview): Module summary, Design conventions
- [ ] Fill in Section 3 (Module Designs): For each module:
  - Module overview
  - For each component:
    - Component Design Specification (ID, Name, Description, SIL, Functions, Data Structures, Algorithms, Error Handling, Complexity, Traceability)
- [ ] Fill in Section 4 (Traceability): Architecture → Design → Requirements traceability matrix
- [ ] Fill in Section 5 (Component Interfaces): External and internal interfaces
- [ ] Fill in Section 6 (Data Structures): All data structures with C definitions
- [ ] Fill in Section 7 (Algorithms): Main algorithms with pseudocode/flowcharts
- [ ] Fill in Section 8 (Error Reporting): Error codes, fault log, reporting mechanisms
- [ ] Fill in Section 9 (Component Test Specifications): Unit test plan per component (or reference to separate document)
- [ ] Fill in Section 10 (Coding Standards): Reference to Coding Standards document (Section 7.3.4.25-7.3.4.27)
- [ ] Fill in Section 11 (Technique Justification): Table A.4 techniques and justification

**Section 3 Example (Component Design Specification)**:
```markdown
### 3.1 Control Module (MOD-CTRL)

#### 3.1.1 Module Overview

**Module ID**: MOD-CTRL  
**Module Name**: Control Module  
**Responsibility**: Execute periodic control loop, compute control outputs  
**SIL Level**: 4  
**Files**: `control_task.c`, `control_task.h`, `control_algorithm.c`, `control_algorithm.h`

#### 3.1.2 Component: Control Task (COMP-CTRL-TASK-001)

**Component ID**: COMP-CTRL-TASK-001  
**Component Name**: Control Task  
**Description**: Main periodic control task that executes control loop every 50ms

**SIL Level**: 4

**Dependencies**:
- Sensor HAL (MOD-SENS) - for sensor input
- Actuator HAL (MOD-ACT) - for actuator output
- Control Algorithm (COMP-CTRL-ALG-002) - for control computation
- Safety Monitor (MOD-SAFE) - for fault reporting

**Files**:
- `control_task.h` (public API, types)
- `control_task.c` (implementation)

**Traceability**:
- REQ-CTRL-001: Execute control loop every 50ms → control_init(), control_run()
- REQ-CTRL-005: Report control status → control_get_status()
- REQ-PERF-010: Control loop WCET ≤ 40ms → Verified in algorithm design

##### 3.1.2.1 Functions

**Function: control_init()**
```c
error_t control_init(const control_config_t* config);
```
- **Purpose**: Initialize control task with configuration
- **Parameters**:
  - `config`: Pointer to control configuration (NOT NULL)
    - `period_ms`: Control loop period [10..1000] ms
    - `mode`: Control mode (MANUAL=0, AUTOMATIC=1)
- **Returns**:
  - `SUCCESS`: Initialization successful
  - `ERROR_NULL_POINTER`: config is NULL
  - `ERROR_INVALID_PARAM`: period_ms out of range or invalid mode
- **Preconditions**: System clock initialized, interrupts disabled
- **Postconditions**: Control task initialized, timer configured
- **Error Handling**: Validate config pointer (NULL check), validate period_ms range, validate mode enum
- **SIL**: 4
- **Complexity Target**: ≤ 8
- **MISRA C**: Rule 8.13 (const pointer), Rule 17.7 (check return value)
- **Traceability**: REQ-CTRL-001

[Continue for all functions...]

##### 3.1.2.2 Data Structures

**control_config_t** (Configuration)
```c
typedef struct {
    uint16_t period_ms;    ///< Control loop period [10..1000] ms
    uint8_t mode;          ///< Control mode (0=MANUAL, 1=AUTOMATIC)
    uint8_t reserved;      ///< Alignment padding
    int16_t kp;            ///< Proportional gain (Q15 fixed-point)
    int16_t ki;            ///< Integral gain (Q15 fixed-point)
    int16_t kd;            ///< Derivative gain (Q15 fixed-point)
} control_config_t;

static control_config_t g_control_config;  // Static allocation (SIL 4 MANDATORY)
```

[Continue for all data structures...]

##### 3.1.2.3 Algorithms

**Algorithm: control_run() - Main control loop**

```
ALGORITHM: control_run()
INPUTS: None (reads from Sensor HAL)
OUTPUTS: Actuator commands (to Actuator HAL)
SIL: 4
COMPLEXITY TARGET: ≤ 10

PSEUDOCODE:
  1. Read sensor data (sensor_read(&sensor_data))
  2. Validate sensor data (validate_sensor_data(&sensor_data))
     IF invalid THEN
       Report fault to Safety Monitor
       Use last known good data
     END IF
  3. Compute control output (control_compute_pid(setpoint, measured_value, dt))
  4. Saturate output (limit to [0..1023])
  5. Send command to actuator (actuator_write(command))
  6. Update status
  7. RETURN SUCCESS

COMPLEXITY ANALYSIS:
  - 2 conditional branches (sensor validation, output saturation)
  - No nested loops
  - Estimated cyclomatic complexity: 3 (well within ≤ 10)

WCET ESTIMATE: 35 µs (within 40 ms budget)
```

[Continue for all algorithms...]

##### 3.1.2.4 Error Handling

**Error Detection**:
- Input validation: Check sensor_data for NULL, range, timestamp consistency
- Return value checks: Check return values from sensor_read(), actuator_write()
- Internal consistency: Check control state is INITIALIZED before running

**Error Reporting**:
- Log all errors to fault log (fault_log_add())
- Report critical errors to Safety Monitor (safety_report_fault())

**Error Recovery**:
- Sensor failure: Use last known good sensor data (degraded mode)
- Actuator failure: Enter safe state via Safety Monitor

[Continue...]
```

- [ ] Document all components in SDS (following template structure)
- [ ] Include all required content per EN 50128 Section 7.3.4.23 (a-g)

---

### 11. Component Test Specification Phase

**Objective**: Define unit test specification for each component

**EN 50128 Reference**: Section 7.3.4.22 - "each component having... a Software Component Test Specification"

#### 11.1 Component Test Specification Overview

Each component MUST have a **Component Test Specification** that defines:
- Test cases for all component functions
- Expected inputs and outputs
- Coverage targets (statement, branch, condition coverage per SIL)
- Test environment (unit test framework: Unity, CUnit, etc.)

**EN 50128 Section 7.3.4.22**: "The Software Design Specification shall describe the software design based on a decomposition into components with each component having a Software Component Design Specification and a Software Component Test Specification."

#### 11.2 Define Unit Test Cases per Component

For each component, define unit test cases:

**Component Test Specification Example**:
```
===============================================
COMPONENT TEST SPECIFICATION
===============================================

Component ID: COMP-CTRL-TASK-001
Component Name: Control Task
SIL Level: 4
Test Framework: Unity (unit test framework for C)

COVERAGE TARGETS (SIL 4):
  - Statement Coverage: 100% (MANDATORY)
  - Branch Coverage: 100% (MANDATORY)
  - Condition Coverage: 100% (MANDATORY)
  - MC/DC Coverage: 100% (HIGHLY RECOMMENDED)

TEST CASES:

TC-CTRL-TASK-001: Test control_init() with valid configuration
  Preconditions: System initialized
  Inputs: config = {period_ms=50, mode=AUTOMATIC, kp=1000, ki=500, kd=200}
  Expected Output: SUCCESS
  Postconditions: Control task initialized, timer configured
  Coverage: Nominal path

TC-CTRL-TASK-002: Test control_init() with NULL pointer
  Preconditions: System initialized
  Inputs: config = NULL
  Expected Output: ERROR_NULL_POINTER
  Postconditions: Control task not initialized
  Coverage: Error path (NULL check)

TC-CTRL-TASK-003: Test control_init() with invalid period
  Preconditions: System initialized
  Inputs: config = {period_ms=5, mode=AUTOMATIC, ...}  // period < 10
  Expected Output: ERROR_INVALID_PARAM
  Postconditions: Control task not initialized
  Coverage: Error path (range check)

TC-CTRL-TASK-004: Test control_init() with invalid mode
  Preconditions: System initialized
  Inputs: config = {period_ms=50, mode=99, ...}  // mode not 0 or 1
  Expected Output: ERROR_INVALID_PARAM
  Postconditions: Control task not initialized
  Coverage: Error path (enum check)

TC-CTRL-TASK-005: Test control_run() with valid sensor data
  Preconditions: Control task initialized, sensor data valid
  Inputs: sensor_data = {temp=512, pressure=768, speed=100, timestamp=1000, status=0x80}
  Expected Output: SUCCESS, actuator command sent
  Postconditions: Control output computed and sent to actuator
  Coverage: Nominal path

TC-CTRL-TASK-006: Test control_run() with invalid sensor data
  Preconditions: Control task initialized, sensor data invalid (out of range)
  Inputs: sensor_data = {temp=2000, ...}  // temp > 1023
  Expected Output: SUCCESS (degraded mode), last known good data used
  Postconditions: Fault logged, Safety Monitor notified, last good data used
  Coverage: Error path (sensor validation failure)

[Continue for all functions in component...]

TEST ENVIRONMENT:
  - Unity test framework (v2.5.2)
  - PC-based unit test (x86-64 Linux)
  - Hardware abstraction: Mock functions for sensor_read(), actuator_write()
  - Coverage tool: gcov + lcov

TEST EXECUTION:
  - Automated test execution via Makefile: make test
  - Coverage report generation: make coverage
  - Test report: tests/component-tests/control_task_test_report.md
```

- [ ] For each component, create Component Test Specification
- [ ] Define test cases for all functions (nominal + error paths)
- [ ] Define coverage targets per SIL level (100% statement/branch/condition for SIL 3-4)
- [ ] Define test environment (unit test framework, mocks, coverage tools)

**Coverage Requirements by SIL** (EN 50128 Table A.21):
```
SIL 0:   Statement (R), Branch (R)
SIL 1:   Statement (HR), Branch (HR)
SIL 2:   Statement (HR), Branch (M)
SIL 3:   Statement (M), Branch (M), Condition (M)
SIL 4:   Statement (M), Branch (M), Condition (M), MC/DC (HR)
```

#### 11.3 Document Component Test Specifications

Component Test Specifications can be:
1. **Embedded in SDS** (Section 8 per component)
2. **Separate document** (e.g., `docs/design/Component-Test-Specifications.md`)
3. **Embedded in test code** (as Doxygen comments in test files)

- [ ] Choose documentation approach (embedded in SDS recommended)
- [ ] Document all Component Test Specifications
- [ ] Reference Component Test Specifications in SDS Section 9

---

### 12. Traceability Phase

**Objective**: Establish traceability from requirements through architecture to detailed design

**EN 50128 Reference**: Section 7.3.4.23a, 7.3.4.23e

#### 12.1 Create Traceability Matrix (Architecture → Design → Requirements)

**EN 50128 Section 7.3.4.23a**: "The Software Design Specification shall address software components traced back to software architecture and their safety integrity level."

**EN 50128 Section 7.3.4.23e**: "The Software Design Specification shall address allocation and tracing of requirements on components."

**Traceability Matrix Format**:
```
Requirement ID | Architectural Component | Design Component | Function(s) | SIL | Verification Method
---------------|-------------------------|------------------|-------------|-----|---------------------
REQ-CTRL-001   | MOD-CTRL                | COMP-CTRL-TASK   | control_init(), control_run() | 4 | Unit Test + Integration Test
REQ-CTRL-005   | MOD-CTRL                | COMP-CTRL-TASK   | control_get_status() | 4 | Unit Test
REQ-SAFE-012   | MOD-SAFE                | COMP-SAFE-MON    | safety_check_speed() | 4 | Unit Test + FMEA
REQ-PERF-010   | MOD-CTRL                | COMP-CTRL-TASK   | control_run() | 4 | WCET Analysis
[Continue...]
```

- [ ] For each requirement, identify:
  - Architectural component (from SAS)
  - Design component (from SDS)
  - Function(s) that implement the requirement
  - SIL level (verify consistency)
  - Verification method (unit test, integration test, analysis)
- [ ] Verify 100% traceability (all requirements traced to design)
- [ ] Verify SIL consistency (design SIL ≥ requirement SIL)

**Traceability Verification Checklist**:
```
☑ All requirements are traced to at least one design component
☑ All design components are traced to at least one requirement (or architectural decision)
☑ All architectural components are traced to design components
☑ SIL levels are consistent (design SIL ≥ requirement SIL ≥ architectural module SIL)
☑ Orphan requirements identified (requirements with no design component)
☑ Orphan design components identified (components with no requirement justification)
```

#### 12.2 Bidirectional Traceability

- [ ] **Forward Traceability**: Requirements → Architecture → Design
- [ ] **Backward Traceability**: Design → Architecture → Requirements
- [ ] Verify both directions are complete (no gaps)

**Forward Traceability Example**:
```
REQ-CTRL-001: "System SHALL execute control loop every 50ms"
  → Architectural Component: MOD-CTRL (Control Module)
    → Design Component: COMP-CTRL-TASK-001 (Control Task)
      → Functions: control_init() (setup timer), control_run() (execute control loop)
        → Unit Tests: TC-CTRL-TASK-001 (test init), TC-CTRL-TASK-005 (test run)
```

**Backward Traceability Example**:
```
Function: safety_check_speed()
  ← Design Component: COMP-SAFE-MON-001 (Safety Monitor)
    ← Architectural Component: MOD-SAFE (Safety Monitor Module)
      ← Requirement: REQ-SAFE-012 ("System SHALL detect overspeed within 100ms")
```

#### 12.3 Include Traceability Matrix in SDS

- [ ] Add traceability matrix to SDS Section 4 (Traceability to Architecture)
- [ ] Use table format (Markdown, CSV, or embedded spreadsheet)
- [ ] Verify traceability matrix is complete and consistent

**SDS Section 4 Example**:
```markdown
## 4. TRACEABILITY TO ARCHITECTURE

### 4.1 Traceability Matrix

| Requirement ID | Requirement Description | Arch Component | Design Component | Function(s) | SIL | Verification |
|----------------|-------------------------|----------------|------------------|-------------|-----|--------------|
| REQ-CTRL-001   | Execute control loop every 50ms | MOD-CTRL | COMP-CTRL-TASK | control_init(), control_run() | 4 | Unit Test + Integration Test |
| REQ-CTRL-005   | Report control status | MOD-CTRL | COMP-CTRL-TASK | control_get_status() | 4 | Unit Test |
| REQ-SAFE-012   | Detect overspeed within 100ms | MOD-SAFE | COMP-SAFE-MON | safety_check_speed() | 4 | Unit Test + FMEA |
| REQ-PERF-010   | Control loop WCET ≤ 40ms | MOD-CTRL | COMP-CTRL-TASK | control_run() | 4 | WCET Analysis |
| [Continue...] | | | | | | |

### 4.2 Traceability Verification

- Total Requirements: 150
- Requirements Traced to Design: 150 (100%)
- Design Components Traced to Requirements: 45/45 (100%)
- Orphan Requirements: 0
- Orphan Design Components: 0
- SIL Consistency: Verified (all design SIL ≥ requirement SIL)
```

---

### 13. Design Review Phase

**Objective**: Review design for completeness, correctness, consistency, and compliance

#### 13.1 Self-Review

- [ ] Designer performs self-review of SDS
- [ ] Use SDS checklist (see Section 13.4)
- [ ] Fix issues found in self-review
- [ ] Document self-review (date, findings, resolutions)

#### 13.2 Peer Review

- [ ] Peer designer (or lead designer) performs technical review
- [ ] Focus on:
  - Design correctness (algorithms, data structures)
  - Design completeness (all requirements addressed)
  - Design consistency (interfaces match, data types consistent)
  - C language constraints (static allocation, complexity, no recursion)
  - MISRA C compliance (types, error handling)
  - Traceability completeness
- [ ] Document peer review findings
- [ ] Fix issues found in peer review
- [ ] Peer reviewer approves SDS (or requests revision)

**Peer Review Checklist**:
```
☑ All components from architecture are designed in detail
☑ All functions have complete specifications (signature, parameters, return, error handling)
☑ All data structures are defined with fixed-width types
☑ All algorithms are documented (pseudocode/flowcharts)
☑ Complexity ≤ target for all functions (10 for SIL 3-4)
☑ Static allocation for all data structures (SIL 2+ MANDATORY)
☑ No recursion (SIL 3-4)
☑ Error handling is comprehensive (validation, reporting, recovery)
☑ Traceability is complete (requirements → design, design → requirements)
☑ Component Test Specifications are defined for all components
☑ EN 50128 Table A.4 techniques are applied and justified
```

#### 13.3 Design Walkthrough (Optional but Recommended for SIL 3-4)

- [ ] Present design to team (designer, peer reviewers, QUA, VER)
- [ ] Walk through key design decisions:
  - Component decomposition
  - Interface design
  - Algorithm design (especially safety-critical algorithms)
  - Error handling strategy
- [ ] Collect feedback
- [ ] Address feedback in SDS revision

#### 13.4 SDS Completeness Checklist

**EN 50128 Section 7.3.4.23 Compliance**:
```
☑ (a) Software components traced back to architecture with SIL levels
☑ (b) Interfaces of components with environment documented
☑ (c) Interfaces between components documented
☑ (d) Data structures documented
☑ (e) Allocation and tracing of requirements on components documented
☑ (f) Main algorithms and sequencing documented
☑ (g) Error reporting mechanisms documented
```

**SDS Content Checklist**:
```
☑ Section 1 (Introduction): Complete
☑ Section 2 (Design Overview): Complete
☑ Section 3 (Module Designs): All modules documented
  ☑ For each module: All components documented
    ☑ For each component:
      ☑ Component Design Specification complete
      ☑ All functions specified (signature, parameters, return, error handling)
      ☑ All data structures defined
      ☑ All algorithms documented (pseudocode/flowcharts)
      ☑ Complexity analysis documented
      ☑ Traceability to architecture and requirements documented
☑ Section 4 (Traceability): Traceability matrix complete, 100% coverage
☑ Section 5 (Component Interfaces): All interfaces documented
☑ Section 6 (Data Structures): All data structures documented with C definitions
☑ Section 7 (Algorithms): Main algorithms documented
☑ Section 8 (Error Reporting): Error codes, fault log, reporting mechanisms documented
☑ Section 9 (Component Test Specifications): Test specs for all components
☑ Section 10 (Coding Standards): Reference to Coding Standards document
☑ Section 11 (Technique Justification): Table A.4 techniques justified
```

**C Language Constraints Checklist**:
```
☑ All data structures use fixed-width types (uint8_t, uint16_t, uint32_t, etc.)
☑ All data structures are statically allocated (SIL 2+ MANDATORY)
☑ No dynamic memory allocation (malloc, calloc, realloc, free) (SIL 2+ MANDATORY)
☑ No recursion (SIL 3-4)
☑ Cyclomatic complexity ≤ 10 for all functions (SIL 3-4), ≤ 15 (SIL 2)
☑ All loops are bounded (no infinite loops except main task with watchdog)
☑ WCET documented for performance-critical functions
☑ MISRA C:2012 compliance considerations documented
```

---

### 14. Quality Assurance Review Phase

**Objective**: QUA agent reviews SDS for template compliance and design quality

**Role**: Quality Assurance (QUA)

#### 14.1 QUA Template Compliance Check

- [ ] QUA agent reviews SDS document structure
- [ ] Verify document header (Document ID, Version, Approvals table)
- [ ] Verify all required sections present (Sections 1-11)
- [ ] Verify SIL-specific content (e.g., SIL 3-4 requires independent reviewer approval)
- [ ] Generate QA Template Compliance Report

**QUA Template Compliance Checklist**:
```
☑ Document ID follows naming convention (DOC-010-SDS-YYYY-NNN)
☑ Document Control table complete (versions, dates, authors, changes)
☑ Approvals table complete with SIL-appropriate roles:
  - SIL 0-2: Author, Technical Reviewer, QA Manager, Project Manager
  - SIL 3-4: + Safety Manager, Independent Verifier, Independent Validator, Assessor
☑ All required sections present (Sections 1-11)
☑ Traceability matrix present (Section 4) - MANDATORY SIL 3-4
☑ Component Test Specifications present (Section 9) - MANDATORY all SILs
☑ Technique Justification present (Section 11) - MANDATORY SIL 3-4
```

#### 14.2 QUA Design Quality Check

- [ ] QUA agent reviews design quality:
  - Modular approach applied (MANDATORY SIL 2+)
  - Complexity within limits (≤10 for SIL 3-4)
  - Static allocation enforced (SIL 2+)
  - Defensive programming applied (HR SIL 3-4)
  - Error handling comprehensive
  - Traceability complete (100% for SIL 3-4)
- [ ] Generate QA Design Quality Report

**QUA Design Quality Checklist**:
```
☑ Modular Approach: Components have clear responsibilities, low coupling, high cohesion
☑ Complexity Limits: All functions ≤ 10 (SIL 3-4), ≤ 15 (SIL 2)
☑ Static Allocation: All data structures statically allocated (SIL 2+)
☑ No Dynamic Memory: No malloc/calloc/realloc/free (SIL 2+)
☑ No Recursion: All algorithms are iterative (SIL 3-4)
☑ Fixed-Width Types: All types are uint8_t, uint16_t, etc. (no int, long)
☑ Defensive Programming: Input validation, return value checks, assertions (SIL 3-4)
☑ Error Handling: Comprehensive error detection, reporting, recovery
☑ Traceability: 100% requirements traced to design (MANDATORY SIL 3-4)
☑ Test Specifications: Component Test Specification for all components
☑ MISRA C: Design supports MISRA C:2012 compliance (SIL 2+)
```

#### 14.3 QUA Approval or Rejection

- [ ] QUA agent provides approval or requests revision
- [ ] If rejected: Designer fixes issues and resubmits to QUA (1 pass only per EN 50128 QA flow)
- [ ] If approved: SDS proceeds to VER review (SIL 3-4) or finalization (SIL 0-2)

---

### 15. Verification Review Phase (SIL 3-4 MANDATORY)

**Objective**: Independent VER agent reviews SDS for correctness and compliance

**Role**: Verifier (VER) - **INDEPENDENT** for SIL 3-4

**EN 50128 Requirement**: Verification is MANDATORY for SIL 3-4 (Section 6.2, Table A.5)

#### 15.1 VER Technical Review

- [ ] VER agent (independent reviewer) performs technical review
- [ ] Focus on:
  - Design correctness (algorithms correct, data structures appropriate)
  - Requirements coverage (all requirements addressed in design)
  - Consistency (SAS ↔ SDS, SRS ↔ SDS)
  - C language constraints (static allocation, complexity, no recursion)
  - EN 50128 technique application (Table A.4)
  - Traceability completeness and accuracy
- [ ] VER agent documents findings in Verification Report (preliminary)

**VER Review Checklist** (SIL 3-4):
```
☑ All requirements from SRS are addressed in SDS
☑ Design is consistent with architecture (SAS)
☑ All interfaces are consistent (SDS ↔ Software Interface Spec)
☑ Algorithms are correct (logic, boundary conditions)
☑ Complexity analysis is accurate (complexity ≤ 10 for all functions)
☑ Static allocation enforced (no dynamic memory)
☑ No recursion (all algorithms iterative)
☑ Defensive programming applied (input validation, error handling)
☑ Error handling is comprehensive
☑ Traceability is complete (100% requirements → design)
☑ Component Test Specifications are adequate (coverage targets, test cases)
☑ EN 50128 Table A.4 techniques applied and justified
☑ MISRA C:2012 compliance supported by design
```

#### 15.2 VER Approval or Rejection

- [ ] VER agent provides approval or requests revision
- [ ] If rejected: Designer fixes issues and resubmits to QUA for template check, then VER for technical review (1 pass only)
- [ ] If approved: VER creates preliminary Verification Report (formal report created after implementation phase)

**Note**: Formal "Software Architecture and Design Verification Report" (DOC-014) is created by VER agent after BOTH SAS and SDS are complete and implementation phase begins. At SDS design phase, VER provides preliminary approval only.

---

### 16. Finalize and Baseline Phase

**Objective**: Finalize SDS and create configuration baseline

**Role**: Configuration Manager (CM)

#### 16.1 Incorporate All Review Feedback

- [ ] Designer incorporates all feedback from peer review, QUA, VER
- [ ] Update SDS to final version
- [ ] Update Document Control table (version, date, changes)
- [ ] Update Approvals table (collect all signatures/approvals)

#### 16.2 Final Approval

- [ ] Obtain final approvals from all required roles:
  - Author (DES)
  - Technical Reviewer (peer)
  - QA Manager (QUA)
  - Safety Manager (SIL 2+)
  - Independent Verifier (VER) (SIL 3-4)
  - Independent Validator (VAL) (SIL 3-4)
  - Assessor (SIL 3-4)
  - Project Manager (PM)

**EN 50128 Section 7.3.4.20**: "A Software Design Specification shall be written, under the responsibility of the Designer..."

**EN 50128 Table C.1**: SDS (Deliverable #10) is Written by DES, First Check by VER, Second Check by VAL.

#### 16.3 Create Configuration Baseline

- [ ] CM agent creates baseline for SDS
- [ ] Baseline includes:
  - Software Design Specification (SDS) (DOC-010)
  - Coding Standards document (referenced in SDS)
  - Component Test Specifications (embedded in SDS or separate)
  - Traceability matrix (embedded in SDS)
- [ ] Baseline is version-controlled (Git tag)
- [ ] Baseline is placed under change control (CCB approval required for changes)

**Baseline Command** (example):
```bash
# Commit SDS to repository
git add docs/design/Software-Design-Specification.md
git commit -m "SDS baseline for Phase 4 (Component Design)"

# Create Git tag for baseline
git tag -a SDS-v1.0-baseline -m "SDS v1.0 baseline (approved by DES, QUA, VER, VAL)"

# Push to remote repository
git push origin main --tags
```

- [ ] CM documents baseline in Configuration Status Accounting
- [ ] CM notifies PM and COD that SDS baseline is complete
- [ ] PM/COD performs gate check: Phase 4 (Component Design) → Phase 5 (Implementation)

**EN 50128 Section 6.6**: Configuration Management (mandatory for all SILs)

#### 16.4 Handoff to Implementation Phase

- [ ] SDS (baseline) is handed off to Implementer (IMP) for coding
- [ ] Component Test Specifications are handed off to Tester (TST) for test development
- [ ] Coding Standards are available to IMP for implementation
- [ ] PM/COD authorizes transition to Phase 5 (Implementation)

**Handoff Checklist**:
```
☑ SDS approved and baselined
☑ Coding Standards approved and available
☑ Component Test Specifications defined for all components
☑ Traceability matrix complete (requirements → architecture → design)
☑ All review findings addressed
☑ Baseline created in version control
☑ Change control process active (CCB approval for SDS changes)
☑ PM/COD gate check passed: Phase 4 → Phase 5
```

---

## Workflow Summary

**Software Design Workflow** (16 steps):
1. **Preparation**: Review SRS, SAS, interfaces, coding standards, identify constraints
2. **Component Identification**: Decompose architecture into detailed components
3. **Component Design**: Design each component (functions, data, algorithms)
4. **Interface Design**: Define all component interfaces (external, internal)
5. **Data Structure Design**: Design all data structures (C structs, static allocation)
6. **Algorithm Design**: Design algorithms (pseudocode, flowcharts, complexity)
7. **Error Handling Design**: Design error detection, reporting, recovery
8. **Apply C Design Constraints**: Enforce static allocation, no recursion, complexity limits, fixed-width types
9. **Apply EN 50128 Techniques**: Verify Table A.4 techniques applied and justified
10. **Document Design**: Create SDS from template with all sections
11. **Component Test Specification**: Define unit test specs for all components
12. **Traceability**: Establish requirements → architecture → design traceability
13. **Design Review**: Self-review, peer review, design walkthrough
14. **Quality Assurance Review**: QUA template compliance and design quality check
15. **Verification Review (SIL 3-4)**: Independent VER technical review
16. **Finalize and Baseline**: Incorporate feedback, final approval, create baseline

**Time Estimate**: 4-8 weeks (depending on project size and complexity)

**Artifacts Created**:
- Software Design Specification (SDS) (DOC-010)
- Component Test Specifications (embedded in SDS or separate)
- Traceability matrix (requirements → architecture → design)
- Coding Standards document (referenced in SDS)
- QA Template Compliance Report (from QUA)
- QA Design Quality Report (from QUA)
- Preliminary Verification Report (from VER, SIL 3-4)

---

## EN 50128 Standard References

### Primary References

**Section 7.3.4.20**: Software Design Specification requirement  
**Section 7.3.4.21**: Input documents available prior to design  
**Section 7.3.4.22**: Component decomposition (Component Design Specification + Component Test Specification)  
**Section 7.3.4.23**: SDS required content (a-g):
- (a) Components traced to architecture with SIL levels
- (b) Interfaces with environment
- (c) Interfaces between components
- (d) Data structures
- (e) Allocation and tracing of requirements
- (f) Main algorithms and sequencing
- (g) Error reporting mechanisms

**Section 7.3.4.24**: Technique selection from Table A.4, justification per 4.8 and 4.9  
**Section 7.3.4.25-7.3.4.27**: Coding standards requirements  
**Section 7.3.4.28**: Design method features (abstraction, modularity, comprehension, verification)

### Table A.4 - Software Design and Implementation Techniques/Measures

| ID | Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Reference |
|----|-----------|-------|---------|---------|-----------|
| 1 | Structured Methodology | R | HR | **M** | D.52 |
| 2 | Defensive Programming | - | - | HR | D.14 |
| 3 | Fault Detection and Diagnosis | - | R | HR | D.26 |
| 4 | Modular Approach | HR | **M** | **M** | D.38 |
| 5 | Design and Coding Standards | HR | HR | **M** | A.12 |
| 6 | Analysable Programs | HR | HR | **M** | D.2 |
| 7 | Structured Programming | R | HR | **M** | D.53 |
| 8 | Strongly Typed Language | R | HR | HR | D.49 |

**SIL 3-4 Approved Combination**: 4, 5, 6, 8 + one from {1 or 2}  
**Typical SIL 3-4 Combination**: 1, 4, 5, 6, 7

### Annex D - Technique Descriptions

**D.2 (Analysable Programs)**: Simple structure, clear control/data flow, low complexity  
**D.14 (Defensive Programming)**: Input validation, error checking, fail-safe defaults  
**D.26 (Fault Detection and Diagnosis)**: Error detection, fault isolation, recovery  
**D.38 (Modular Approach)**: High cohesion, low coupling, clear interfaces  
**D.52 (Structured Methodology)**: Disciplined design process, systematic decomposition  
**D.53 (Structured Programming)**: Structured control flow (if-else, for, while, switch-case), no goto  
**D.49 (Strongly Typed Language)**: Explicit types, no implicit conversions

### Table A.12 - Good Programming Practice

(Referenced from Section 7.3.4.25a)

Good programming practices for C:
- Clear naming conventions
- Consistent code formatting
- Comprehensive commenting (Doxygen)
- Error handling (return codes, assertions)
- Defensive programming (input validation)
- Avoid complex expressions
- Avoid side effects
- Use const for read-only data
- Check all function return values

### MISRA C:2012 References

**Rule 1.3**: No undefined behavior  
**Rule 2.1**: No unreachable code  
**Rule 8.9**: Object defined at smallest scope  
**Rule 8.13**: Pointer parameter that is not modified should be const  
**Rule 17.2**: No recursion (direct or indirect)  
**Rule 17.7**: Return value of non-void function shall be used  
**Rule 21.3**: No malloc, calloc, realloc, free (MANDATORY SIL 2+)  
**Directive 4.6**: Use typedefs for size and signedness (uint8_t, uint16_t, etc.)

### Related Documents

**Software Requirements Specification (SRS)** (DOC-006): Input document for design  
**Software Architecture Specification (SAS)** (DOC-009): Input document for design  
**Software Interface Specifications** (DOC-011): Input document for design  
**Coding Standards**: Referenced in SDS, mandatory per Section 7.3.4.25-7.3.4.27  
**Software Component Test Specification** (DOC-020): Derived from SDS Section 9  
**Software Architecture and Design Verification Report** (DOC-014): Created by VER after SAS and SDS complete

---

## Common Pitfalls and How to Avoid Them

### Pitfall 1: Incomplete Component Decomposition

**Problem**: Architecture modules not fully decomposed into detailed components  
**Impact**: Implementation phase lacks guidance, functions not clearly defined  
**Solution**: For each architectural module, systematically identify all functions and data structures. Use function-based, data-based, and interface-based decomposition strategies.

### Pitfall 2: Missing Error Handling Design

**Problem**: Error handling designed ad-hoc during implementation  
**Impact**: Inconsistent error handling, incomplete error detection  
**Solution**: Design error handling systematically in design phase (Section 7). Define error codes, fault log, reporting mechanism, recovery strategy for ALL components.

### Pitfall 3: Complexity Not Analyzed at Design Phase

**Problem**: Complexity only checked after implementation, leading to refactoring  
**Impact**: Wasted implementation effort, schedule delays  
**Solution**: Estimate cyclomatic complexity for all functions during algorithm design (Section 6). Use pseudocode to count decision points. Refactor high-complexity algorithms at design phase (break into smaller functions, use lookup tables).

### Pitfall 4: Dynamic Memory Allocation in Design

**Problem**: Design assumes dynamic memory (malloc/free) for SIL 2+ project  
**Impact**: Implementation violates MISRA C Rule 21.3, requires major redesign  
**Solution**: Apply C design constraints early (Section 8). Design all data structures as static (fixed-size arrays, static structs). Calculate total memory usage to verify feasibility.

### Pitfall 5: Recursion Not Identified Until Implementation

**Problem**: Recursive algorithm designed, later found to violate SIL 3-4 requirement  
**Impact**: Algorithm must be refactored to iterative, delays implementation  
**Solution**: Review all algorithms for recursion during design phase (Section 6, Section 8.2). Refactor recursive algorithms to iterative BEFORE implementation.

### Pitfall 6: Incomplete Traceability

**Problem**: Traceability matrix incomplete or inaccurate  
**Impact**: VER/VAL rejection, cannot verify requirements coverage  
**Solution**: Establish traceability systematically (Section 12). Use forward and backward traceability checks. Verify 100% coverage (all requirements → design, all design → requirements).

### Pitfall 7: Missing Component Test Specifications

**Problem**: Component Test Specifications not created during design phase  
**Impact**: Tester (TST) lacks guidance, test development delayed  
**Solution**: Create Component Test Specification for ALL components (Section 11). Define test cases, coverage targets, test environment during design phase.

### Pitfall 8: Insufficient Interface Definition

**Problem**: Interfaces between components not fully specified  
**Impact**: Integration failures, interface mismatches discovered late  
**Solution**: Define all interfaces explicitly (Section 4). Specify function signatures, data structures, synchronization, error handling for ALL interfaces (external and internal).

### Pitfall 9: Ignoring WCET Analysis

**Problem**: Worst-Case Execution Time not estimated, timing violations discovered late  
**Impact**: Performance requirements not met, requires algorithm redesign  
**Solution**: Estimate WCET for performance-critical functions (Section 6.3). Verify WCET meets timing requirements. Design algorithms with bounded execution time (no unbounded loops).

### Pitfall 10: Inadequate Technique Justification

**Problem**: EN 50128 Table A.4 technique justification is superficial or missing  
**Impact**: VER/VAL rejection, assessor rejection (SIL 3-4)  
**Solution**: Document technique justification thoroughly (Section 9.2). Explain HOW each technique is applied, WHY the combination is appropriate, and verify approved combination for SIL 3-4.

---

## Best Practices

1. **Start with Architecture**: Ensure SAS is approved before starting detailed design. SDS derives from SAS.

2. **Design Before Coding**: Complete SDS before starting implementation. Don't code first and document later.

3. **Apply C Constraints Early**: Consider static allocation, no recursion, complexity limits from the beginning of design. Don't assume features that will be forbidden.

4. **Use Pseudocode/Flowcharts**: Document algorithms with pseudocode or flowcharts. This clarifies logic and enables complexity analysis before coding.

5. **Design for Testability**: Design components with clear interfaces, minimal side effects, and testable functions. Consider test harness and mocks during design.

6. **Estimate Complexity at Design**: Count decision points in pseudocode to estimate cyclomatic complexity. Refactor at design phase if complexity exceeds target.

7. **Document Error Handling**: Design comprehensive error handling (detection, reporting, recovery) at design phase. Don't leave error handling to implementation.

8. **Maintain Traceability Continuously**: Update traceability matrix as design progresses. Don't wait until end to trace all requirements.

9. **Involve QUA and VER Early**: Engage QUA and VER during design (informal reviews) to catch issues early. Don't wait for formal review to discover major problems.

10. **Use Design Reviews Effectively**: Conduct peer review and design walkthrough. Multiple reviewers catch more issues than solo review.

---

## Tools and Resources

### Design Tools

**UML Tools**: PlantUML, draw.io (for architecture and component diagrams)  
**Flowchart Tools**: draw.io, Lucidchart (for algorithm flowcharts)  
**Markdown Editors**: VS Code, Typora (for SDS documentation)  
**Version Control**: Git (for SDS baseline and change control)

### Analysis Tools

**Complexity Analysis**: Lizard (Python tool for cyclomatic complexity)  
**Static Analysis**: Cppcheck, Clang Static Analyzer (for design feasibility check)  
**MISRA C Checker**: PC-lint Plus, Cppcheck (MISRA C:2012 rules)  
**Traceability**: Custom scripts (Python) or spreadsheet tools (CSV, Excel)

### Reference Documents

**EN 50128:2011**: `std/EN50128-2011.md` (Section 7.3.4, Table A.4, Annex D)  
**MISRA C:2012**: MISRA C Guidelines  
**SDS Template**: `.opencode/skills/en50128-design/templates/Software-Design-Specification-template.md`  
**Coding Standards**: Project-specific Coding Standards document

---

## Workflow Checklist Summary

Use this checklist to track progress through the Software Design workflow:

```
☐ 1. Preparation
  ☐ Review SRS, SAS, Software Interface Specs
  ☐ Review Coding Standards
  ☐ Identify SIL level and EN 50128 techniques
  ☐ Identify C language constraints

☐ 2. Component Identification
  ☐ List architectural modules
  ☐ Identify software components per module
  ☐ Assign component IDs and SIL levels

☐ 3. Component Design
  ☐ Create Component Design Specification for each component
  ☐ Design component functions (API and private)
  ☐ Document function specifications

☐ 4. Interface Design
  ☐ Design external interfaces (hardware, software, communication)
  ☐ Design internal interfaces (component-to-component)

☐ 5. Data Structure Design
  ☐ Identify data structure requirements
  ☐ Design data structures (C structs, enums, arrays)
  ☐ Document memory allocation strategy (static for SIL 2+)

☐ 6. Algorithm Design
  ☐ Identify algorithms for each function
  ☐ Design algorithms (pseudocode/flowcharts)
  ☐ Estimate complexity (≤10 for SIL 3-4)
  ☐ Analyze performance (WCET, memory, determinism)

☐ 7. Error Handling Design
  ☐ Classify errors by severity
  ☐ Design error detection strategy (defensive programming)
  ☐ Design error reporting strategy (error codes, fault log)
  ☐ Design error handling and recovery

☐ 8. Apply C Design Constraints
  ☐ Verify static allocation (SIL 2+)
  ☐ Verify no recursion (SIL 3-4)
  ☐ Verify complexity within limits
  ☐ Verify fixed-width types
  ☐ Verify bounded execution

☐ 9. Apply EN 50128 Techniques
  ☐ Verify all mandatory techniques applied (Table A.4)
  ☐ Document technique justification (Section 4.8, 4.9)

☐ 10. Document Design
  ☐ Copy SDS template
  ☐ Fill in all SDS sections (1-11)
  ☐ Include all Component Design Specifications

☐ 11. Component Test Specification
  ☐ Define test cases for all components
  ☐ Define coverage targets per SIL
  ☐ Document test environment

☐ 12. Traceability
  ☐ Create traceability matrix (requirements → architecture → design)
  ☐ Verify 100% traceability (forward and backward)
  ☐ Include traceability matrix in SDS Section 4

☐ 13. Design Review
  ☐ Self-review (DES)
  ☐ Peer review
  ☐ Design walkthrough (optional, recommended SIL 3-4)

☐ 14. Quality Assurance Review
  ☐ QUA template compliance check
  ☐ QUA design quality check
  ☐ QUA approval or revision request

☐ 15. Verification Review (SIL 3-4)
  ☐ VER technical review
  ☐ VER approval or revision request

☐ 16. Finalize and Baseline
  ☐ Incorporate all review feedback
  ☐ Obtain final approvals (DES, QUA, VER, VAL, PM)
  ☐ Create configuration baseline (CM)
  ☐ Handoff to Implementation Phase
  ☐ PM/COD gate check: Phase 4 → Phase 5
```

---

**END OF WORKFLOW**
