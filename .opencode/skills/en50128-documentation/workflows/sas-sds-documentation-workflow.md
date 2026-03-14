# Software Architecture and Design Specification (SAS/SDS) Documentation Workflow

**Workflow ID**: DOC-WF-002  
**EN 50128 Reference**: Section 7.3 (Software Architecture and Design)  
**Last Updated**: 2026-03-14  
**Version**: 1.0

---

## Table of Contents

1. [Overview](#1-overview)
2. [EN 50128 Architecture and Design Requirements](#2-en-50128-architecture-and-design-requirements)
3. [SAS vs SDS: Document Separation](#3-sas-vs-sds-document-separation)
4. [Software Architecture Specification (SAS) Structure](#4-software-architecture-specification-sas-structure)
5. [Software Design Specification (SDS) Structure](#5-software-design-specification-sds-structure)
6. [Architecture and Design Patterns](#6-architecture-and-design-patterns)
7. [SIL-Specific Architecture Requirements](#7-sil-specific-architecture-requirements)
8. [Design Traceability](#8-design-traceability)
9. [Architecture and Design Review](#9-architecture-and-design-review)
10. [Template Validation](#10-template-validation)
11. [Tool Integration](#11-tool-integration)
12. [Automation Scripts](#12-automation-scripts)
13. [Example Scenarios](#13-example-scenarios)

---

## 1. Overview

### 1.1 Purpose

This workflow provides comprehensive guidance for creating, reviewing, and approving **Software Architecture Specification (SAS)** and **Software Design Specification (SDS)** documents in compliance with EN 50128:2011 Section 7.3. The SAS and SDS are the **primary deliverables of Phase 3 (Software Architecture and Design)** and define the high-level architecture and detailed design for implementation.

### 1.2 Scope

**This workflow covers**:
- EN 50128 Section 7.3 mandatory requirements for architecture and design
- SAS document structure and content guidance (high-level architecture)
- SDS document structure and content guidance (detailed design)
- Architecture and design patterns (Table A.3 techniques)
- SIL-specific architecture requirements (SIL 0-4)
- Design traceability (SRS → SAS → SDS → Code)
- Architecture and design review workflows (SIL-dependent)
- Template validation and compliance checking
- Tool integration (workspace.py wf, workspace.py trace)
- Automation scripts for validation and extraction

**Out of Scope**:
- Software Requirements Specification (see SRS workflow)
- Code implementation (see Implementation skill)
- Test design (see Test Documentation workflow)

### 1.3 Key EN 50128 Requirements

| Requirement | EN 50128 Reference | Mandatory For |
|-------------|-------------------|---------------|
| **Architecture shall be modular** | Table A.3, Technique 19 | **MANDATORY SIL 2+** |
| **Structured methodology used** | Table A.3, Technique 1 | **MANDATORY SIL 3-4** |
| **Information encapsulation** | Table A.3, Technique 20 | HR SIL 3-4 |
| **Defensive programming** | Table A.3, Technique 14 | HR SIL 3-4 |
| **Architecture traces to SRS** | Section 7.3.4.7 | All SIL levels |
| **Design verifiable and testable** | Section 7.3.4.8 | All SIL levels |
| **Independent review** | Table A.5, Section 5 | **MANDATORY SIL 3-4** |

### 1.4 Workflow Roles

| Role | Responsibility | Independence Required |
|------|----------------|----------------------|
| **Designer (DES)** | Create SAS and SDS, define architecture and detailed design | No |
| **Requirements Engineer (REQ)** | Provide SRS, clarify requirements | No |
| **Safety Engineer (SAF)** | Verify safety architecture patterns | No (but separate from DES) |
| **Quality Assurance (QUA)** | Template compliance check, process compliance | No |
| **Verifier (VER)** | Technical review of architecture and design | **Yes (SIL 3-4)** |
| **Implementer (IMP)** | Validate design is implementable in C | No |
| **Project Manager (PM)** | Approve SAS/SDS baseline | No |

---

## 2. EN 50128 Architecture and Design Requirements

### 2.1 Section 7.3 Key Requirements

EN 50128:2011 Section 7.3 defines the mandatory requirements for Software Architecture and Design.

#### 2.1.1 Input Documents (Section 7.3.2)

The SAS and SDS SHALL be based on the following input documents:

1. **Software Requirements Specification (SRS)** - Complete software requirements (PRIMARY INPUT)
2. **System Architecture Description** - System context, HW/SW allocation
3. **Software Quality Assurance Plan (SQAP)** - Quality requirements, design standards
4. **Software Verification Plan (SVP)** - Verification criteria for design

#### 2.1.2 Output Documents (Section 7.3.3)

Phase 3 (Software Architecture and Design) SHALL produce:

1. **Software Architecture Specification (SAS)** - High-level architecture (THIS WORKFLOW)
2. **Software Design Specification (SDS)** - Detailed design (THIS WORKFLOW)
3. **Software Interface Specifications** - Detailed interface definitions (can be part of SDS)
4. **Software Integration Test Specification** - Integration test plan (see Test Documentation workflow)
5. **Software Architecture and Design Verification Report** - Verification of SAS/SDS (VER role)

#### 2.1.3 Architecture Requirements (Section 7.3.4)

**Software Architecture Specification SHALL** (Section 7.3.4.2 to 7.3.4.11):

- **Decompose software into components** with defined interfaces (modular approach)
- **Define data structures and data flow** between components
- **Define control flow and timing** (execution model, task scheduling)
- **Address safety requirements** from SRS (fault detection, redundancy, fail-safe behavior)
- **Define resource usage** (CPU, memory, I/O)
- **Describe implementation constraints** (C language, MISRA C, static allocation)
- **Trace to SRS** (all requirements allocated to architecture elements)
- **Be verifiable and testable** (architecture can be validated through integration testing)

**Software Design Specification SHALL** (Section 7.3.4.12 to 7.3.4.20):

- **Refine architecture into detailed design** (modules, functions, data structures)
- **Define module interfaces** in detail (function signatures, data types)
- **Define algorithms and logic** (control flow, state machines, calculations)
- **Define error handling** for each module (input validation, fault detection)
- **Specify complexity limits** (cyclomatic complexity ≤ 10 for SIL 3-4)
- **Include C language implementation guidance** (coding patterns, MISRA C compliance)
- **Trace to SAS and SRS** (design elements trace to architecture and requirements)

#### 2.1.4 Architecture Techniques (Table A.3)

EN 50128 Table A.3 defines techniques for software architecture. The SAS/SDS SHALL apply a justified combination of techniques based on SIL level.

| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Description | Reference |
|-----------|-------|---------|---------|-------------|-----------|
| **Structured Methodology** | R | HR | **M** | Systematic approach to architecture and design | D.52 |
| **Modular Approach** | HR | **M** | **M** | Decomposition into independent modules | D.38 |
| **Information Encapsulation** | R | HR | HR | Hide internal module state, expose interfaces only | D.33 |
| **Defensive Programming** | - | HR | HR | Input validation, error checking, fault tolerance | D.14 |
| **Fully Defined Interface** | HR | HR | HR | Precise interface specifications (data types, timing) | D.38 |
| **Fault Detection and Diagnosis** | - | R | HR | Built-in fault detection mechanisms | D.26 |
| **Static Memory Allocation** | R | HR | **M** | No dynamic allocation (implicit from implementation constraints) | - |

**Key**:
- **M** = Mandatory (must use)
- **HR** = Highly Recommended (rationale required if not used)
- **R** = Recommended (should consider)

**Typical SIL 3-4 Combination**:
- **MANDATORY**: Structured Methodology, Modular Approach
- **HIGHLY RECOMMENDED**: Information Encapsulation, Defensive Programming, Fully Defined Interface, Fault Detection and Diagnosis

### 2.2 Modular Approach (MANDATORY SIL 2+)

**Definition**: Decompose software into **independent, cohesive modules** with well-defined interfaces.

**Requirements** (SIL 2+):
- Each module has a **single, clear responsibility**
- Modules communicate via **defined interfaces only** (no direct access to internal state)
- Modules are **independently testable** (unit tests)
- Module dependencies form a **directed acyclic graph (DAG)** (no circular dependencies)

**Example Module Structure**:
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
└──────────────────────────────────────────────┘
```

### 2.3 Information Encapsulation (HR SIL 3-4)

**Definition**: Hide module internal state, expose only defined public interfaces.

**C Language Pattern**:
```c
// control.h (PUBLIC interface)
typedef struct control_module_state_t control_module_state_t;  // Opaque type

void control_init(void);
error_t control_process(void);
control_state_t control_get_state(void);

// control.c (PRIVATE implementation)
struct control_module_state_t {
    control_state_t state;
    uint32_t timestamp_ms;
    uint8_t error_code;
};

static control_module_state_t g_control_state;  // Hidden from other modules

static error_t validate_input(const sensor_data_t* data);  // Private function
```

---

## 3. SAS vs SDS: Document Separation

### 3.1 When to Use SAS vs SDS

EN 50128 distinguishes between **Software Architecture Specification (SAS)** and **Software Design Specification (SDS)**.

| Document | Abstraction Level | Content | Audience |
|----------|-------------------|---------|----------|
| **SAS** | **High-Level** | Architecture overview, module decomposition, data flow, process architecture | Architects, system engineers, safety engineers |
| **SDS** | **Detailed** | Module design, function design, algorithms, data structures, interfaces | Implementers, testers, verifiers |

### 3.2 SAS Content (High-Level Architecture)

**Software Architecture Specification (SAS)** defines:

1. **Architecture Overview**: Goals, patterns, constraints
2. **Logical Architecture**: Module decomposition, responsibilities
3. **Process Architecture**: Task allocation, scheduling, timing
4. **Data Architecture**: Data flow, global data, data structures
5. **Safety Architecture**: Redundancy, fault detection, fail-safe behavior
6. **C Implementation Constraints**: MISRA C, static allocation, no recursion

**SAS Traces**: SRS → SAS (requirements to architecture elements)

### 3.3 SDS Content (Detailed Design)

**Software Design Specification (SDS)** defines:

1. **Module Design**: Detailed design for each module (functions, state machines, algorithms)
2. **Interface Design**: Function signatures, data types, protocols
3. **Algorithm Design**: Control flow, calculations, logic
4. **State Machine Design**: States, transitions, events (if applicable)
5. **Error Handling Design**: Input validation, error codes, fault detection
6. **Data Structure Design**: Detailed data types, memory layout

**SDS Traces**: SAS → SDS, SRS → SDS (architecture and requirements to detailed design)

### 3.4 Small Projects: Combined SAS/SDS

For **small projects** (< 10 modules, < 10,000 lines of code), SAS and SDS **MAY be combined** into a single document:

**Combined Document Title**: Software Architecture and Design Specification (SADS)

**Structure**: Follow SAS structure, but add detailed design sections for each module inline.

**Rationale**: Reduces documentation overhead for small projects while maintaining EN 50128 compliance.

**SIL 3-4 Note**: Combined SADS still requires independent review of both architecture and detailed design.

---

## 4. Software Architecture Specification (SAS) Structure

### 4.1 Standard SAS Template

The SAS SHALL follow the standard template located at:

```
.opencode/skills/en50128-design/templates/Software-Architecture-Specification-template.md
```

**Template Structure** (731 lines):

```markdown
# Software Architecture Specification (SAS)

## STANDARD HEADER
- Document ID: DOC-SAS-YYYY-NNN
- Version, Date, Project, SIL Level
- Author, Reviewer, Approver, Status

## DOCUMENT CONTROL
- Version history table

## APPROVALS
- SIL-specific approval signatures

---

## 1. INTRODUCTION
  1.1 Purpose
  1.2 Scope
  1.3 SIL Classification
  1.4 Definitions and Acronyms
  1.5 References
  1.6 Overview

## 2. ARCHITECTURE OVERVIEW
  2.1 System Context Diagram
  2.2 Architecture Goals
  2.3 Architecture Patterns

## 3. LOGICAL ARCHITECTURE
  3.1 Module Decomposition
  3.2 Module Descriptions
    3.2.1 [Module 1]
    3.2.2 [Module 2]
    ...
  3.3 Module Interface Matrix
  3.4 Information Encapsulation

## 4. PROCESS ARCHITECTURE
  4.1 Task Allocation
  4.2 Interrupt Service Routines (ISRs)
  4.3 Timing Analysis

## 5. DATA ARCHITECTURE
  5.1 Data Model
  5.2 Data Structures (C Implementation)
  5.3 Static Memory Allocation (Mandatory SIL 2+)
  5.4 Data Flow Diagram

## 6. SAFETY ARCHITECTURE
  6.1 Safety Functions
  6.2 Redundancy and Diversity
  6.3 Fault Detection and Diagnosis
  6.4 Safe States

## 7. C IMPLEMENTATION CONSTRAINTS
  7.1 MISRA C Compliance (Mandatory SIL 2+)
  7.2 Defensive Programming (Highly Recommended SIL 3-4)
  7.3 No Recursion (Highly Recommended SIL 3-4)
  7.4 Complexity Limits

## 8. TRACEABILITY
  8.1 Requirements to Architecture Traceability

## 9. ARCHITECTURE EVALUATION
  9.1 Architecture Quality Metrics
  9.2 Architecture Review Checklist

## 10. COMPLIANCE MATRIX
  10.1 EN 50128 Section 7.3 Compliance
  10.2 EN 50128 Table A.3 Compliance

## 11. REFERENCES
  11.1 Normative References
  11.2 Project References

## APPENDICES
  Appendix A: Module Template
  Appendix B: Glossary

## DOCUMENT HISTORY
```

### 4.2 SAS Section Guidance

#### 4.2.1 Section 2: Architecture Overview

**Purpose**: Provide high-level architecture overview and design philosophy.

**Key Content**:
- **System Context Diagram**: Show software within larger system (hardware, external interfaces)
- **Architecture Goals**: Safety, modularity, testability, maintainability, performance, reliability
- **Architecture Patterns**: Layered architecture, modular decomposition, state machines, defensive programming

**Example**:
```markdown
## 2.2 Architecture Goals

The architecture is designed to achieve the following goals:

1. **Safety**: Fail-safe design, fault detection, hazard mitigation (SIL 4)
2. **Modularity**: Clear module boundaries, defined interfaces (MANDATORY SIL 2+)
3. **Testability**: Independent module testing, high coverage (≥100% for SIL 3-4)
4. **Maintainability**: Clear structure, information hiding, low complexity (≤10 for SIL 3-4)
5. **Performance**: Meet timing requirements (50ms control loop), low CPU/memory usage
6. **Reliability**: Error handling, defensive programming, watchdog monitoring
7. **Certifiability**: EN 50128 compliance, traceability, evidence collection

## 2.3 Architecture Patterns

**Primary Patterns**:
- **Layered Architecture**: Separation of concerns (Application Layer, HAL)
- **Modular Decomposition**: Independent, cohesive modules (MANDATORY SIL 2+)
- **State Machine Pattern**: For control logic (recommended for safety-critical)
- **Defensive Programming**: Input validation, error checking (HR SIL 3-4)

**Avoided Patterns** (per EN 50128 constraints):
- ❌ Dynamic memory allocation (forbidden SIL 2+)
- ❌ Recursion (not recommended SIL 3-4)
- ❌ Function pointers (use with caution, SIL 3-4)
```

#### 4.2.2 Section 3: Logical Architecture

**Purpose**: Define module decomposition and module responsibilities.

**Key Content**:
- **Module Decomposition Diagram**: Visual representation of modules and layers
- **Module Descriptions**: For each module, define purpose, responsibilities, interfaces, data structures, key functions, complexity estimate
- **Module Interface Matrix**: Table showing which modules communicate and how
- **Information Encapsulation**: Demonstrate how module state is hidden

**Example Module Description**:
```markdown
#### 3.2.1 Control Module

**Module ID**: MOD-CTRL  
**SIL Level**: 3  
**Implements**: REQ-FUNC-001, REQ-FUNC-002, REQ-FUNC-003

**Purpose**: Implements main control logic for door control

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
\```c
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
\```

**Key Functions**:
- `void control_init(void)` - Initialize control module
- `error_t control_process(void)` - Main processing function (called every 50ms)
- `control_state_t control_get_state(void)` - Get current state

**Complexity**: Estimated ≤ 8 (target ≤ 10 for SIL 3-4)

**C Files**: `control.h`, `control.c`
```

#### 4.2.3 Section 4: Process Architecture

**Purpose**: Define execution model (bare-metal vs. RTOS), task allocation, scheduling, timing.

**Key Content**:
- **Task Allocation**: Define tasks/threads (if RTOS) or cyclic executive (if bare-metal)
- **ISRs**: Interrupt Service Routines (trigger, purpose, max duration, priority)
- **Timing Analysis**: Demonstrate that worst-case execution time meets requirements

**Example (Bare-Metal Cyclic Executive - Recommended SIL 3-4)**:
```markdown
### 4.1 Task Allocation

**Execution Model**: Bare-metal cyclic executive (50ms cycle)

**Rationale**: Deterministic, simple, no RTOS overhead, easier to certify (SIL 3-4)

**Main Loop** (50ms cycle):
\```c
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
\```

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
```

#### 4.2.4 Section 6: Safety Architecture

**Purpose**: Define safety mechanisms (redundancy, fault detection, fail-safe behavior).

**Key Content** (SIL 2+):
- **Safety Functions**: Critical safety functions (e.g., emergency stop, speed interlock)
- **Redundancy and Diversity**: Redundant sensors, diverse technologies, voting logic
- **Fault Detection**: Plausibility checks, range checks, timeout detection
- **Safe States**: Definition of safe state, fail-safe design

**Example**:
```markdown
### 6.2 Redundancy and Diversity

**Redundant Speed Monitoring**:
- Primary speed sensor: Hall effect sensor (wheel rotation)
- Secondary speed sensor: Doppler radar (ground speed) - DIVERSE TECHNOLOGY
- Software comparison: Raise fault if disagreement > 10%

**Voting Strategy**: 1-out-of-2 (1oo2) - Either sensor can trigger safety action (lock doors)

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
```

---

## 5. Software Design Specification (SDS) Structure

### 5.1 Standard SDS Template

The SDS SHALL follow a similar template to SAS, but with **detailed design** content.

**Template Structure** (estimated 800+ lines):

```markdown
# Software Design Specification (SDS)

## STANDARD HEADER
- Document ID: DOC-SDS-YYYY-NNN
- Version, Date, Project, SIL Level
- Author, Reviewer, Approver, Status

## DOCUMENT CONTROL
## APPROVALS

---

## 1. INTRODUCTION
  1.1 Purpose
  1.2 Scope
  1.3 SIL Classification
  1.4 Definitions and Acronyms
  1.5 References (including SAS reference)
  1.6 Overview

## 2. DESIGN OVERVIEW
  2.1 Architecture Summary (reference SAS)
  2.2 Design Philosophy
  2.3 Design Constraints

## 3. MODULE DETAILED DESIGN
  3.1 [Module 1] Detailed Design
    3.1.1 Module Structure
    3.1.2 Function Specifications
    3.1.3 State Machine Design (if applicable)
    3.1.4 Algorithm Design
    3.1.5 Error Handling
    3.1.6 Data Structures
  3.2 [Module 2] Detailed Design
    ...

## 4. INTERFACE DETAILED DESIGN
  4.1 Module-to-Module Interfaces
  4.2 Hardware Interfaces
  4.3 Software Interfaces
  4.4 Communication Protocols

## 5. DATA STRUCTURE DETAILED DESIGN
  5.1 Global Data Structures
  5.2 Module-Specific Data Structures
  5.3 Memory Layout

## 6. ALGORITHM DESIGN
  6.1 [Algorithm 1]
  6.2 [Algorithm 2]
  ...

## 7. ERROR HANDLING DESIGN
  7.1 Error Code Definitions
  7.2 Error Detection Mechanisms
  7.3 Error Recovery Strategies

## 8. TRACEABILITY
  8.1 Architecture to Design Traceability
  8.2 Requirements to Design Traceability

## 9. DESIGN EVALUATION
  9.1 Complexity Analysis
  9.2 Design Review Checklist

## 10. COMPLIANCE MATRIX
  10.1 EN 50128 Section 7.3 Compliance
  10.2 EN 50128 Table A.4 Compliance

## 11. REFERENCES

## APPENDICES
  Appendix A: Function Template
  Appendix B: State Machine Template
  Appendix C: Glossary

## DOCUMENT HISTORY
```

### 5.2 SDS Section Guidance

#### 5.2.1 Section 3: Module Detailed Design

**Purpose**: Provide detailed design for each module (function-level).

**For Each Module, Document**:

1. **Module Structure**: Internal organization, submodules, helper functions
2. **Function Specifications**: For each function, define signature, purpose, inputs, outputs, preconditions, postconditions, algorithm, error handling
3. **State Machine Design**: If module implements a state machine, define states, events, transitions, actions
4. **Algorithm Design**: Pseudocode or flowchart for complex algorithms
5. **Error Handling**: How module detects and handles errors
6. **Data Structures**: Detailed data type definitions

**Example Function Specification**:
```markdown
#### 3.1.2.1 Function: control_process()

**Function Signature**:
\```c
error_t control_process(const sensor_data_t* sensor_data, const train_control_msg_t* cmd);
\```

**Purpose**: Main control processing function, called every 50ms. Executes control state machine and generates actuator commands.

**Inputs**:
- `sensor_data`: Pointer to sensor data structure (door position, obstacle sensor, speed)
- `cmd`: Pointer to train control command structure (open/close commands, emergency stop)

**Outputs**:
- Returns: `error_t` (SUCCESS or error code)
- Side effect: Updates `g_actuator_cmd` global (actuator commands)

**Preconditions**:
- `control_init()` has been called
- `sensor_data` is not NULL and contains valid data
- `cmd` is not NULL

**Postconditions**:
- State machine updated based on inputs
- Actuator commands generated
- Status message prepared for transmission

**Algorithm** (pseudocode):
\```
1. Validate inputs (sensor_data != NULL, cmd != NULL)
2. Check for emergency stop condition
   IF emergency_stop THEN
     transition to STATE_FAULT
     disable all actuators
     RETURN SUCCESS
3. Read current state from g_control_state
4. Execute state machine:
   CASE STATE_IDLE:
     IF cmd.open AND speed == 0 AND at_platform THEN
       transition to STATE_OPENING
   CASE STATE_OPENING:
     Set actuator PWM to 80% (open direction)
     IF door_position >= 95% THEN
       transition to STATE_OPEN
   CASE STATE_OPEN:
     Set actuator PWM to 0% (hold position)
     IF cmd.close THEN
       transition to STATE_CLOSING
   ... (continue for all states)
5. Update actuator commands based on new state
6. RETURN SUCCESS
\```

**Error Handling**:
- IF `sensor_data == NULL`: RETURN ERROR_NULL_POINTER
- IF `cmd == NULL`: RETURN ERROR_NULL_POINTER
- IF state transition invalid: Log warning, remain in current state

**Complexity**: Estimated cyclomatic complexity = 8 (within limit ≤ 10 for SIL 3)

**Traceability**: Implements REQ-FUNC-001, REQ-FUNC-002, REQ-FUNC-003
```

#### 5.2.2 Section 6: Algorithm Design

**Purpose**: Document complex algorithms in detail (beyond simple function-level logic).

**For Each Complex Algorithm, Document**:
- **Purpose**: What the algorithm does
- **Inputs/Outputs**: Data inputs and outputs
- **Algorithm Description**: Pseudocode, flowchart, or mathematical formula
- **Complexity**: Time complexity (Big-O), space complexity
- **Rationale**: Why this algorithm was chosen
- **Traceability**: Which requirements the algorithm fulfills

**Example Algorithm**:
```markdown
### 6.1 Speed Sensor Plausibility Check Algorithm

**Purpose**: Detect faulty speed sensors by comparing primary and secondary sensor readings.

**Inputs**:
- `speed_primary`: Primary speed sensor reading (km/h * 10)
- `speed_secondary`: Secondary speed sensor reading (km/h * 10)

**Outputs**:
- `plausibility_ok`: Boolean (true = sensors agree, false = fault detected)
- `fault_code`: Error code if fault detected

**Algorithm**:
\```c
bool speed_plausibility_check(uint16_t speed_primary, uint16_t speed_secondary, uint8_t* fault_code) {
    // Range check (0-200 km/h valid)
    if (speed_primary > 2000 || speed_secondary > 2000) {
        *fault_code = FAULT_SPEED_OUT_OF_RANGE;
        return false;
    }
    
    // Calculate absolute difference
    uint16_t diff = (speed_primary > speed_secondary) ? 
                    (speed_primary - speed_secondary) : 
                    (speed_secondary - speed_primary);
    
    // Check disagreement (> 10% of higher reading)
    uint16_t threshold = (speed_primary > speed_secondary ? speed_primary : speed_secondary) / 10;
    if (diff > threshold) {
        *fault_code = FAULT_SPEED_DISAGREEMENT;
        return false;
    }
    
    // Sensors agree
    *fault_code = 0;
    return true;
}
\```

**Complexity**: 
- Time: O(1) (constant time)
- Space: O(1) (no dynamic allocation)

**Rationale**: Simple comparison algorithm, no division (uses multiplication for threshold), suitable for real-time embedded system.

**Traceability**: Implements REQ-SAFE-002 (redundant speed monitoring)
```

---

## 6. Architecture and Design Patterns

### 6.1 Layered Architecture Pattern

**Purpose**: Separate concerns by organizing modules into layers (Application Layer, Hardware Abstraction Layer).

**Benefits**:
- **Portability**: HAL can be replaced for different hardware platforms
- **Testability**: Application Layer can be tested independently (mock HAL)
- **Maintainability**: Clear separation of concerns

**Structure**:
```
┌──────────────────────────────────────────────┐
│         Application Layer                    │
│  ┌────────────┐  ┌────────────┐             │
│  │  Control   │  │  Safety    │             │
│  │  Module    │  │  Module    │             │
│  └────────────┘  └────────────┘             │
└──────────────────────────────────────────────┘
           ▲              ▲
           │              │
           └──────┬───────┘
                  │
┌──────────────────────────────────────────────┐
│      Hardware Abstraction Layer (HAL)        │
│  ┌────────────┐  ┌────────────┐             │
│  │   Sensor   │  │  Actuator  │             │
│  │    HAL     │  │    HAL     │             │
│  └────────────┘  └────────────┘             │
└──────────────────────────────────────────────┘
           ▲              ▲
           │              │
    [Hardware]      [Hardware]
```

**Design Rules**:
- Application Layer MAY call HAL functions
- HAL MAY NOT call Application Layer functions (dependency inversion if needed via callbacks)
- Application Layer modules communicate horizontally (peer-to-peer)

### 6.2 State Machine Pattern (Recommended for Control Logic)

**Purpose**: Implement control logic as a finite state machine (FSM) for clarity and testability.

**Benefits**:
- **Clarity**: States and transitions are explicit
- **Testability**: Each state and transition can be tested independently
- **Safety**: Prevents invalid state transitions
- **Maintainability**: Easy to extend with new states

**Example State Machine** (Door Control):
```
┌─────────────────────────────────────────────────────┐
│                  STATE_IDLE                         │
│  Entry: Actuator off                                │
│  During: Monitor for open command                   │
│  Exit: None                                         │
└─────────────────────────────────────────────────────┘
          │
          │ cmd.open AND speed==0 AND at_platform
          ▼
┌─────────────────────────────────────────────────────┐
│                STATE_OPENING                        │
│  Entry: Set actuator PWM to 80% (open direction)    │
│  During: Monitor door position                      │
│  Exit: None                                         │
└─────────────────────────────────────────────────────┘
          │
          │ door_position >= 95%
          ▼
┌─────────────────────────────────────────────────────┐
│                  STATE_OPEN                         │
│  Entry: Set actuator PWM to 0% (hold)               │
│  During: Monitor for close command                  │
│  Exit: None                                         │
└─────────────────────────────────────────────────────┘
          │
          │ cmd.close AND no_obstacle
          ▼
┌─────────────────────────────────────────────────────┐
│                STATE_CLOSING                        │
│  Entry: Set actuator PWM to 80% (close direction)   │
│  During: Monitor door position, obstacle sensor     │
│  Exit: None                                         │
└─────────────────────────────────────────────────────┘
          │
          │ door_position <= 5%
          ▼
┌─────────────────────────────────────────────────────┐
│                 STATE_CLOSED                        │
│  Entry: Engage door lock                            │
│  During: Wait for next cycle                        │
│  Exit: Disengage lock                               │
└─────────────────────────────────────────────────────┘
          │
          │ cmd.open AND speed==0 AND at_platform
          └──────────────> STATE_IDLE

     ANY STATE
          │
          │ emergency_stop
          ▼
┌─────────────────────────────────────────────────────┐
│                  STATE_FAULT                        │
│  Entry: Disable all actuators, raise alarm          │
│  During: Wait for fault clear                       │
│  Exit: None                                         │
└─────────────────────────────────────────────────────┘
```

**C Implementation Pattern**:
```c
typedef enum {
    STATE_IDLE,
    STATE_OPENING,
    STATE_OPEN,
    STATE_CLOSING,
    STATE_CLOSED,
    STATE_FAULT
} control_state_t;

static control_state_t g_current_state = STATE_IDLE;

error_t control_process(const sensor_data_t* sensor_data, const train_control_msg_t* cmd) {
    // Check for emergency stop (transition from any state)
    if (cmd->emergency_stop) {
        transition_to_state(STATE_FAULT);
        return SUCCESS;
    }
    
    // Execute state machine
    switch (g_current_state) {
        case STATE_IDLE:
            if (cmd->open && sensor_data->speed == 0 && sensor_data->at_platform) {
                transition_to_state(STATE_OPENING);
            }
            break;
        
        case STATE_OPENING:
            set_actuator_pwm(80);  // Open direction
            if (sensor_data->door_position >= 95) {
                transition_to_state(STATE_OPEN);
            }
            break;
        
        case STATE_OPEN:
            set_actuator_pwm(0);  // Hold position
            if (cmd->close && !sensor_data->obstacle_detected) {
                transition_to_state(STATE_CLOSING);
            }
            break;
        
        case STATE_CLOSING:
            set_actuator_pwm(80);  // Close direction
            if (sensor_data->obstacle_detected) {
                transition_to_state(STATE_OPENING);  // Reverse on obstacle
            } else if (sensor_data->door_position <= 5) {
                transition_to_state(STATE_CLOSED);
            }
            break;
        
        case STATE_CLOSED:
            engage_door_lock();
            if (cmd->open && sensor_data->speed == 0 && sensor_data->at_platform) {
                disengage_door_lock();
                transition_to_state(STATE_IDLE);
            }
            break;
        
        case STATE_FAULT:
            disable_all_actuators();
            raise_alarm();
            // Wait for fault clear (not shown)
            break;
        
        default:
            // Invalid state - should never happen
            return ERROR_INVALID_STATE;
    }
    
    return SUCCESS;
}

static void transition_to_state(control_state_t new_state) {
    // Log transition
    log_state_transition(g_current_state, new_state);
    
    // Execute exit actions for old state (if any)
    // ...
    
    // Update state
    g_current_state = new_state;
    
    // Execute entry actions for new state (if any)
    // ...
}
```

### 6.3 Defensive Programming Pattern (HR SIL 3-4)

**Purpose**: Validate all inputs, check all outputs, handle all errors explicitly.

**Key Techniques**:

1. **Input Validation**: Check all function parameters
2. **Output Validation**: Check all function return values
3. **Range Checks**: Ensure values within valid range
4. **Null Pointer Checks**: Verify pointers before dereferencing
5. **Error Propagation**: Propagate errors up the call stack
6. **Assertions**: Use assertions for internal consistency checks (debug builds)

**Example**:
```c
error_t process_sensor_data(const sensor_data_t* data, result_t* output) {
    // Input validation (defensive programming)
    if (data == NULL) {
        log_error(ERROR_NULL_POINTER, "data parameter is NULL");
        return ERROR_NULL_POINTER;
    }
    if (output == NULL) {
        log_error(ERROR_NULL_POINTER, "output parameter is NULL");
        return ERROR_NULL_POINTER;
    }
    
    // Range check
    if (data->door_position > 100) {
        log_error(ERROR_OUT_OF_RANGE, "door_position > 100");
        return ERROR_OUT_OF_RANGE;
    }
    
    // Process data (core logic)
    error_t result = calculate_output(data, output);
    
    // Check result (output validation)
    if (result != SUCCESS) {
        log_error(result, "calculate_output failed");
        return result;  // Propagate error
    }
    
    // Verify output is valid
    if (output->value > MAX_OUTPUT_VALUE) {
        log_error(ERROR_OUT_OF_RANGE, "output value exceeds maximum");
        return ERROR_OUT_OF_RANGE;
    }
    
    return SUCCESS;
}
```

### 6.4 Static Memory Allocation Pattern (MANDATORY SIL 2+)

**Purpose**: Eliminate dynamic memory allocation to avoid memory leaks, heap fragmentation, non-determinism.

**Design Rules**:
- **All data SHALL be statically allocated** (global or static variables)
- **No `malloc`, `calloc`, `realloc`, `free`** (forbidden)
- **Fixed-size arrays** (no variable-length arrays)
- **Pre-allocated buffers** for temporary data

**Example**:
```c
// CORRECT: Static allocation
static sensor_data_t g_sensor_data;
static uint8_t g_rx_buffer[256];
static control_module_state_t g_control_state;

// INCORRECT: Dynamic allocation (FORBIDDEN for SIL 2+)
// sensor_data_t* data = malloc(sizeof(sensor_data_t));  // FORBIDDEN
// uint8_t* buffer = calloc(256, 1);  // FORBIDDEN
```

**Memory Layout**:
```
ROM (Flash): [Code: 64KB] [Constants: 8KB] [Total: 72KB]
RAM (SRAM):  [Data: 16KB] [Stack: 4KB] [Heap: 0KB - NO HEAP]
             [Total RAM: 20KB]
```

---

## 7. SIL-Specific Architecture Requirements

### 7.1 Architecture Requirements by SIL Level

| Requirement | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 |
|-------------|-------|-------|-------|-------|-------|
| **Modular Approach** | HR | **M** | **M** | **M** | **M** |
| **Information Encapsulation** | R | HR | HR | HR | HR |
| **Defensive Programming** | - | HR | HR | HR | HR |
| **Static Memory Allocation** | R | HR | **M** | **M** | **M** |
| **No Recursion** | R | R | HR | HR | HR |
| **Complexity ≤ 10** | No | No | No | **Required** | **Required** |
| **Redundancy** | No | No | Optional | **Required** | **Required** |
| **Fault Detection** | No | R | HR | HR | **M** (implicit) |
| **Independent Review** | No | No | No | **M** | **M** |

### 7.2 SIL 3-4 Enhanced Architecture

For SIL 3-4 projects, the architecture SHALL include:

#### 7.2.1 Redundant Safety-Critical Components

**Requirement**: Safety-critical functions SHALL use redundant components with diverse technologies where possible.

**Example**:
```markdown
### Safety Module - Redundant Speed Monitoring

**Primary Speed Sensor**: Hall effect sensor (digital, wheel rotation)  
**Secondary Speed Sensor**: Doppler radar (analog, ground speed) - DIVERSE TECHNOLOGY

**Voting Logic**: 1-out-of-2 (1oo2)
- IF primary speed > 5 km/h OR secondary speed > 5 km/h THEN lock doors

**Fault Detection**:
- IF |primary - secondary| > 10% of higher reading THEN raise alarm
- IF sensor out of range (> 200 km/h) THEN raise alarm, use conservative safe value
```

#### 7.2.2 Fault Detection Architecture

**Requirement**: Architecture SHALL include built-in fault detection mechanisms.

**Fault Detection Mechanisms**:

| Fault Type | Detection Method | Response | Module |
|------------|------------------|----------|--------|
| **Sensor failure** | Plausibility check, range check | Use default safe value, raise alarm | Safety Module |
| **Actuator failure** | Feedback monitoring (position sensor) | Disable actuator, enter safe state | Control Module |
| **Software lockup** | Hardware watchdog timeout | System reset to safe state | Safety Module (watchdog refresh) |
| **Communication loss** | Timeout on CAN messages (100ms) | Use last valid command or safe default | Communication HAL |
| **Speed sensor mismatch** | Compare primary/secondary (> 10% diff) | Lock doors (fail-safe), raise alarm | Safety Module |

#### 7.2.3 Complexity Limits (SIL 3-4)

**Requirement**: All functions SHALL have cyclomatic complexity ≤ 10.

**Enforcement**:
- **Design Phase**: Estimate complexity during design review
- **Implementation Phase**: Measure complexity with Lizard tool
- **If complexity > 10**: Refactor function into smaller functions

**Example Refactoring**:
```c
// BAD: Complexity = 15 (too high for SIL 3-4)
error_t process_complex(const data_t* input, result_t* output) {
    if (input == NULL) return ERROR_NULL_POINTER;
    if (output == NULL) return ERROR_NULL_POINTER;
    
    if (input->mode == MODE_A) {
        if (input->value > 100) {
            // ... complex logic (5 branches)
        } else {
            // ... complex logic (5 branches)
        }
    } else if (input->mode == MODE_B) {
        // ... complex logic (5 branches)
    }
    
    return SUCCESS;
}

// GOOD: Refactored into 3 functions, each with complexity ≤ 8
error_t process_complex(const data_t* input, result_t* output) {
    if (input == NULL) return ERROR_NULL_POINTER;
    if (output == NULL) return ERROR_NULL_POINTER;
    
    if (input->mode == MODE_A) {
        return process_mode_a(input, output);  // Complexity = 7
    } else if (input->mode == MODE_B) {
        return process_mode_b(input, output);  // Complexity = 6
    }
    
    return ERROR_INVALID_MODE;
}
```

---

## 8. Design Traceability

### 8.1 Traceability Fundamentals

**Design Traceability** links requirements to architecture to detailed design:

```
SRS (Requirements) → SAS (Architecture) → SDS (Detailed Design) → Code
```

**Traceability is MANDATORY for SIL 3-4** (EN 50128 Table A.9, Technique 7).

### 8.2 Requirements to Architecture Traceability (SAS)

The SAS SHALL include a **Requirements to Architecture Traceability** table (Section 8.1):

```markdown
## 8.1 Requirements to Architecture Traceability

| Requirement | Architecture Element | Module | Notes |
|-------------|---------------------|--------|-------|
| REQ-FUNC-001 | Door opening logic | MOD-CTRL (Control Module) | control.c |
| REQ-FUNC-002 | Door closing logic | MOD-CTRL (Control Module) | control.c |
| REQ-SAFE-001 | Speed interlock | MOD-SAFE (Safety Module) | safety.c |
| REQ-SAFE-002 | Watchdog refresh | MOD-SAFE (Safety Module) | safety.c |
| REQ-PERF-001 | 50ms control loop | Process Architecture (Section 4.1) | main.c |
| REQ-IF-HW-001 | Door position sensor | Sensor HAL | sensor_hal.c |
| REQ-IF-SW-001 | CAN communication | Communication HAL | can_hal.c |

**Traceability Completeness**: 100% of requirements traced to architecture elements.
```

### 8.3 Architecture to Design Traceability (SDS)

The SDS SHALL include an **Architecture to Design Traceability** table (Section 8.1):

```markdown
## 8.1 Architecture to Design Traceability

| Architecture Element (SAS) | Design Element (SDS) | Functions | Notes |
|---------------------------|---------------------|-----------|-------|
| MOD-CTRL (Control Module) | Control Module Detailed Design (Section 3.1) | control_init(), control_process(), control_get_state() | Implements state machine |
| MOD-SAFE (Safety Module) | Safety Module Detailed Design (Section 3.2) | safety_init(), safety_monitor(), safety_watchdog_refresh() | Monitors speed interlock |
| Sensor HAL | Sensor HAL Detailed Design (Section 3.5) | sensor_hal_read(), sensor_hal_init() | Reads ADC, GPIO |

**Traceability Completeness**: 100% of architecture elements traced to detailed design.
```

### 8.4 Using `workspace.py trace` for Design Traceability

See SRS workflow Section 6.3 for `workspace.py trace` usage. Design traceability links are added similarly:

```bash
# Link requirement to architecture (SAS)
python3 tools/workspace.py trace add \
  --from "REQ-FUNC-001" \
  --to "MOD-CTRL" \
  --type "sw-to-arch" \
  --description "Control module implements door opening"

# Link architecture to design (SDS)
python3 tools/workspace.py trace add \
  --from "MOD-CTRL" \
  --to "control_process()" \
  --type "arch-to-design" \
  --description "Door opening state machine in control_process()"

# Link design to code (during implementation)
python3 tools/workspace.py trace add \
  --from "control_process()" \
  --to "src/control/control.c:45" \
  --type "design-to-code" \
  --description "Implementation of control_process()"
```

---

## 9. Architecture and Design Review

### 9.1 Review Workflow

The SAS and SDS SHALL undergo the following review workflow:

```
┌─────────────────────────────────────────────────────────────────┐
│ STEP 1: Designer Creates SAS/SDS Draft (DES)                    │
│ - Decompose SRS into architecture (SAS)                         │
│ - Refine architecture into detailed design (SDS)                │
│ - Status: Draft (Version 0.1)                                   │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ STEP 2: Template Compliance Check (QUA) - MANDATORY SIL 3-4     │
│ - Verify document follows template structure                    │
│ - Check header, version control, approvals table                │
│ - Validate all mandatory sections present                       │
│ - Run automated template validator (see Section 10)             │
│ - Decision: PASS → Step 3, FAIL → Return to DES (1 iteration)   │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ STEP 3: Technical Review (VER) - Independent for SIL 3-4        │
│ - Review architecture completeness (all req covered)            │
│ - Review modular approach (MANDATORY SIL 2+)                    │
│ - Review complexity estimates (≤10 for SIL 3-4)                 │
│ - Review traceability (100% SRS → SAS → SDS)                    │
│ - Review Table A.3 techniques applied                           │
│ - Decision: APPROVE → Step 4, REJECT → Return to DES            │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ STEP 4: Safety Review (SAF) - For SIL 2+ projects               │
│ - Review safety architecture (redundancy, fault detection)      │
│ - Verify fail-safe design patterns                              │
│ - Verify defensive programming patterns (SIL 3-4)               │
│ - Decision: APPROVE → Step 5, REJECT → Return to DES            │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ STEP 5: Implementability Review (IMP) - Recommended             │
│ - Verify design is implementable in C                           │
│ - Verify static allocation feasible                             │
│ - Verify timing requirements achievable                         │
│ - Decision: APPROVE → Step 6, REJECT → Return to DES            │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ STEP 6: Approval and Baseline (PM)                              │
│ - PM approves SAS/SDS as project baseline                       │
│ - CM creates baseline (Version 1.0)                             │
│ - Status: Approved, Baseline                                    │
│ - Workflow tool: Submit via workspace.py wf (see Section 11.2)  │
└─────────────────────────────────────────────────────────────────┘
                          ↓
              SAS/SDS APPROVED (Baseline 1.0)
```

### 9.2 Review Criteria

#### 9.2.1 VER Technical Review Checklist (SAS)

VER SHALL verify the following for SAS:

**Architecture Completeness**:
- [ ] All SRS requirements allocated to architecture elements
- [ ] All modules have defined responsibilities
- [ ] All interfaces documented (module-to-module, hardware, software)

**Modular Approach (MANDATORY SIL 2+)**:
- [ ] Software decomposed into independent modules
- [ ] Module dependencies form DAG (no circular dependencies)
- [ ] Each module has single, clear responsibility

**Information Encapsulation (HR SIL 3-4)**:
- [ ] Module internal state hidden (opaque types)
- [ ] Modules expose only defined public interfaces

**Safety Architecture (SIL 2+)**:
- [ ] Redundancy specified for safety-critical functions (SIL 3-4)
- [ ] Fault detection mechanisms defined
- [ ] Safe states defined, fail-safe design demonstrated

**Traceability**:
- [ ] 100% traceability from SRS to architecture elements
- [ ] Requirements Traceability Matrix (RTM) updated

**Result**: APPROVE or REJECT

#### 9.2.2 VER Technical Review Checklist (SDS)

VER SHALL verify the following for SDS:

**Design Completeness**:
- [ ] All architecture elements refined into detailed design
- [ ] All functions specified (signature, algorithm, error handling)
- [ ] All data structures defined

**Complexity (SIL 3-4)**:
- [ ] Estimated complexity ≤ 10 for all functions
- [ ] Complex functions refactored if needed

**Defensive Programming (HR SIL 3-4)**:
- [ ] Input validation specified for all functions
- [ ] Error handling specified for all functions
- [ ] Null pointer checks specified

**Implementability**:
- [ ] Design is implementable in C within constraints
- [ ] Static allocation feasible (buffer sizes defined)
- [ ] No recursion (call graph analysis)

**Traceability**:
- [ ] 100% traceability from SAS to detailed design
- [ ] 100% traceability from SRS to detailed design (indirect via SAS)

**Result**: APPROVE or REJECT

---

## 10. Template Validation

### 10.1 Automated Template Validator

The template validator script checks SAS/SDS documents for compliance with the standard template.

**Script Location**: `tools/scripts/validate_sas_sds_template.py`

### 10.2 Validator Script (Complete Implementation)

```python
#!/usr/bin/env python3
"""
SAS/SDS Template Validator
Validates Software Architecture Specification and Software Design Specification documents.

Usage:
    python3 tools/scripts/validate_sas_sds_template.py <sas_or_sds_file.md> --type <SAS|SDS> [--sil <0-4>]

Exit Codes:
    0 - Template validation passed
    1 - Template validation failed (issues found)
    2 - File not found or other error
"""

import sys
import re
import argparse
from pathlib import Path
from typing import List

class SASSDSTemplateValidator:
    """Validates SAS/SDS documents against EN 50128 template."""
    
    # Required sections for SAS
    REQUIRED_SECTIONS_SAS = [
        "STANDARD HEADER",
        "DOCUMENT CONTROL",
        "APPROVALS",
        "1. INTRODUCTION",
        "2. ARCHITECTURE OVERVIEW",
        "3. LOGICAL ARCHITECTURE",
        "4. PROCESS ARCHITECTURE",
        "5. DATA ARCHITECTURE",
        "6. SAFETY ARCHITECTURE",
        "7. C IMPLEMENTATION CONSTRAINTS",
        "8. TRACEABILITY",
        "9. ARCHITECTURE EVALUATION",
        "10. COMPLIANCE MATRIX",
        "11. REFERENCES",
    ]
    
    # Required sections for SDS
    REQUIRED_SECTIONS_SDS = [
        "STANDARD HEADER",
        "DOCUMENT CONTROL",
        "APPROVALS",
        "1. INTRODUCTION",
        "2. DESIGN OVERVIEW",
        "3. MODULE DETAILED DESIGN",
        "4. INTERFACE DETAILED DESIGN",
        "5. DATA STRUCTURE DETAILED DESIGN",
        "7. ERROR HANDLING DESIGN",
        "8. TRACEABILITY",
        "9. DESIGN EVALUATION",
        "10. COMPLIANCE MATRIX",
        "11. REFERENCES",
    ]
    
    # Required header fields
    REQUIRED_HEADER_FIELDS = [
        "Document ID",
        "Version",
        "Date",
        "Project",
        "SIL Level",
        "Author",
        "Reviewer",
        "Approver",
        "Status",
    ]
    
    def __init__(self, doc_file: Path, doc_type: str, sil_level: int = None):
        self.doc_file = doc_file
        self.doc_type = doc_type.upper()  # "SAS" or "SDS"
        self.sil_level = sil_level
        self.content = ""
        self.issues: List[str] = []
        self.warnings: List[str] = []
        
    def validate(self) -> bool:
        """Run all validation checks. Returns True if passed, False if failed."""
        try:
            self.content = self.doc_file.read_text(encoding='utf-8')
        except FileNotFoundError:
            print(f"ERROR: File not found: {self.doc_file}", file=sys.stderr)
            return False
        except Exception as e:
            print(f"ERROR: Failed to read file: {e}", file=sys.stderr)
            return False
        
        # Run validation checks
        self._check_document_id()
        self._check_version()
        self._check_header_fields()
        self._check_document_control()
        self._check_approvals_table()
        self._check_required_sections()
        self._check_traceability()
        self._check_modular_approach()
        self._check_complexity_estimates()
        
        # Print results
        self._print_results()
        
        return len(self.issues) == 0
    
    def _check_document_id(self):
        """Check Document ID format: DOC-SAS-YYYY-NNN or DOC-SDS-YYYY-NNN"""
        pattern = rf'DOC-{self.doc_type}-\d{{4}}-\d{{3}}'
        match = re.search(pattern, self.content)
        if not match:
            self.issues.append(f"Document ID not found or invalid format. Expected: DOC-{self.doc_type}-YYYY-NNN (e.g., DOC-{self.doc_type}-2026-001)")
        else:
            doc_id = match.group(0)
            print(f"✓ Document ID: {doc_id}")
    
    def _check_version(self):
        """Check Version format: MAJOR.MINOR"""
        pattern = r'\|\s*\*\*Version\*\*\s*\|\s*(\d+\.\d+)\s*\|'
        match = re.search(pattern, self.content)
        if not match:
            self.issues.append("Version not found or invalid format. Expected: X.Y (e.g., 1.0, 0.1)")
        else:
            version = match.group(1)
            major, minor = map(int, version.split('.'))
            if major == 0:
                self.warnings.append(f"Version {version} is draft (major version = 0)")
            print(f"✓ Version: {version}")
    
    def _check_header_fields(self):
        """Check all required header fields are present."""
        missing_fields = []
        for field in self.REQUIRED_HEADER_FIELDS:
            pattern = rf'\|\s*\*\*{re.escape(field)}\*\*\s*\|'
            if not re.search(pattern, self.content):
                missing_fields.append(field)
        
        if missing_fields:
            self.issues.append(f"Missing header fields: {', '.join(missing_fields)}")
        else:
            print(f"✓ All header fields present ({len(self.REQUIRED_HEADER_FIELDS)} fields)")
    
    def _check_document_control(self):
        """Check Document Control table is present."""
        if "## DOCUMENT CONTROL" not in self.content:
            self.issues.append("DOCUMENT CONTROL section missing")
        else:
            if not re.search(r'\|\s*Version\s*\|\s*Date\s*\|\s*Author\s*\|', self.content):
                self.issues.append("Document Control version history table missing")
            else:
                print("✓ Document Control section present")
    
    def _check_approvals_table(self):
        """Check Approvals table is present."""
        if "## APPROVALS" not in self.content:
            self.issues.append("APPROVALS section missing")
        else:
            print("✓ Approvals section present")
    
    def _check_required_sections(self):
        """Check all required sections are present."""
        required_sections = self.REQUIRED_SECTIONS_SAS if self.doc_type == "SAS" else self.REQUIRED_SECTIONS_SDS
        missing_sections = []
        for section in required_sections:
            pattern = rf'^##+ {re.escape(section)}'
            if not re.search(pattern, self.content, re.MULTILINE):
                missing_sections.append(section)
        
        if missing_sections:
            self.issues.append(f"Missing required sections: {', '.join(missing_sections)}")
        else:
            print(f"✓ All required sections present ({len(required_sections)} sections)")
    
    def _check_traceability(self):
        """Check Traceability section is present."""
        if "Traceability" not in self.content and "TRACEABILITY" not in self.content:
            if self.sil_level and self.sil_level >= 3:
                self.issues.append("Traceability section missing (MANDATORY for SIL 3-4)")
            else:
                self.warnings.append("Traceability section not found (recommended)")
        else:
            print("✓ Traceability section present")
    
    def _check_modular_approach(self):
        """Check for evidence of modular approach (MANDATORY SIL 2+)."""
        if self.doc_type == "SAS":
            if "Module Decomposition" not in self.content and "LOGICAL ARCHITECTURE" not in self.content:
                if self.sil_level and self.sil_level >= 2:
                    self.issues.append("Module Decomposition section missing (MANDATORY for SIL 2+)")
                else:
                    self.warnings.append("Module Decomposition section not found")
            else:
                print("✓ Modular approach documented (Module Decomposition present)")
    
    def _check_complexity_estimates(self):
        """Check for complexity estimates (SIL 3-4)."""
        if self.doc_type == "SDS":
            complexity_count = len(re.findall(r'[Cc]omplexity.*\d+', self.content))
            if complexity_count == 0:
                if self.sil_level and self.sil_level >= 3:
                    self.warnings.append("No complexity estimates found (required for SIL 3-4 to ensure ≤10)")
            else:
                print(f"✓ Found {complexity_count} complexity estimate(s)")
    
    def _print_results(self):
        """Print validation results."""
        print("\n" + "="*70)
        print(f"{self.doc_type} TEMPLATE VALIDATION RESULTS")
        print("="*70)
        
        if len(self.issues) == 0 and len(self.warnings) == 0:
            print(f"\n✓✓✓ VALIDATION PASSED ✓✓✓")
            print(f"{self.doc_type} document complies with EN 50128 template.")
        elif len(self.issues) == 0:
            print(f"\n✓ VALIDATION PASSED (with warnings)")
            print(f"Found {len(self.warnings)} warning(s):")
            for i, warning in enumerate(self.warnings, 1):
                print(f"  {i}. WARNING: {warning}")
        else:
            print(f"\n✗✗✗ VALIDATION FAILED ✗✗✗")
            print(f"Found {len(self.issues)} issue(s):")
            for i, issue in enumerate(self.issues, 1):
                print(f"  {i}. ERROR: {issue}")
            
            if self.warnings:
                print(f"\nAlso found {len(self.warnings)} warning(s):")
                for i, warning in enumerate(self.warnings, 1):
                    print(f"  {i}. WARNING: {warning}")
        
        print("="*70)


def main():
    parser = argparse.ArgumentParser(
        description="Validate SAS/SDS document against EN 50128 template"
    )
    parser.add_argument(
        "doc_file",
        type=Path,
        help="Path to SAS or SDS markdown file"
    )
    parser.add_argument(
        "--type",
        choices=["SAS", "SDS"],
        required=True,
        help="Document type: SAS (Software Architecture Specification) or SDS (Software Design Specification)"
    )
    parser.add_argument(
        "--sil",
        type=int,
        choices=[0, 1, 2, 3, 4],
        help="SIL level (0-4). If not specified, will attempt to extract from document."
    )
    
    args = parser.parse_args()
    
    if not args.doc_file.exists():
        print(f"ERROR: File not found: {args.doc_file}", file=sys.stderr)
        sys.exit(2)
    
    validator = SASSDSTemplateValidator(args.doc_file, args.type, args.sil_level)
    passed = validator.validate()
    
    sys.exit(0 if passed else 1)


if __name__ == "__main__":
    main()
```

### 10.3 Using the Validator

```bash
# Validate SAS document
python3 tools/scripts/validate_sas_sds_template.py docs/design/SAS_Train_Door_Control.md --type SAS --sil 3

# Validate SDS document
python3 tools/scripts/validate_sas_sds_template.py docs/design/SDS_Train_Door_Control.md --type SDS --sil 3
```

---

## 11. Tool Integration

### 11.1 Overview

This workflow integrates with the following tools:

| Tool | Purpose | Usage in Workflow |
|------|---------|-------------------|
| **workspace.py wf** | Document workflow management (submission, approval tracking) | Submit SAS/SDS for review, track approval status |
| **workspace.py trace** | Traceability management (RTM) | Add traceability links (SRS → SAS → SDS), verify completeness |
| **validate_sas_sds_template.py** | Automated template validation | QUA template compliance check (Step 2) |
| **Git** | Version control | Commit SAS/SDS changes, track document history |

### 11.2 Document Workflow Management (`workspace.py wf`)

See SRS workflow Section 7.3 for complete examples. SAS/SDS workflow is identical:

```bash
# Submit SAS for review
python3 tools/workspace.py wf submit \
  --document "docs/design/SAS_Train_Door_Control.md" \
  --type "SAS" \
  --version "0.1" \
  --approver "QUA" \
  --sil 3

# Submit SDS for review
python3 tools/workspace.py wf submit \
  --document "docs/design/SDS_Train_Door_Control.md" \
  --type "SDS" \
  --version "0.1" \
  --approver "QUA" \
  --sil 3
```

---

## 12. Automation Scripts

### 12.1 SAS/SDS Template Validator

**Script**: `tools/scripts/validate_sas_sds_template.py` (see Section 10.2 for complete implementation)

**Purpose**: Automated validation of SAS/SDS documents against EN 50128 template.

---

## 13. Example Scenarios

### 13.1 Scenario 1: Create SAS and SDS for SIL 3 Project (End-to-End)

**Project**: Train Door Control System  
**SIL Level**: 3  
**Duration**: 3 weeks

#### Week 1: Create Software Architecture Specification (SAS)

**Day 1-2: Architecture Design**

```bash
# Review approved SRS (input document)
# Identify major functional areas:
#   - Door control (opening, closing, state machine)
#   - Safety monitoring (speed interlock, emergency stop)
#   - Sensor interface (position, speed, obstacle)
#   - Actuator control (PWM output, lock control)
#   - Communication (CAN bus interface)

# Decompose into modules (modular approach - MANDATORY SIL 2+):
#   - Control Module (MOD-CTRL)
#   - Safety Module (MOD-SAFE)
#   - Sensor HAL (MOD-SENSOR-HAL)
#   - Actuator HAL (MOD-ACTUATOR-HAL)
#   - Communication HAL (MOD-COMM-HAL)

# Define layered architecture:
#   Application Layer: Control, Safety
#   Hardware Abstraction Layer: Sensor HAL, Actuator HAL, Communication HAL
```

**Day 3-4: SAS Document Creation**

```bash
# Create SAS using template
# Use: .opencode/skills/en50128-design/templates/Software-Architecture-Specification-template.md

# Document:
#   - Section 2: Architecture Overview (goals, patterns)
#   - Section 3: Logical Architecture (5 modules described)
#   - Section 4: Process Architecture (bare-metal cyclic executive, 50ms)
#   - Section 5: Data Architecture (static allocation, data structures)
#   - Section 6: Safety Architecture (redundant speed sensors, fault detection)
#   - Section 7: C Implementation Constraints (MISRA C, no recursion, complexity ≤10)
#   - Section 8: Traceability (50 requirements → 5 modules)

# Add traceability links (SRS → SAS)
python3 tools/workspace.py trace add --from "REQ-FUNC-001" --to "MOD-CTRL" --type "sw-to-arch"
python3 tools/workspace.py trace add --from "REQ-SAFE-001" --to "MOD-SAFE" --type "sw-to-arch"
# ... (continue for all 50 requirements)
```

**Day 5: SAS Review and Approval**

```bash
# Validate template
python3 tools/scripts/validate_sas_sds_template.py docs/design/SAS_Train_Door_Control.md --type SAS --sil 3

# Submit for review
python3 tools/workspace.py wf submit --document "docs/design/SAS_Train_Door_Control.md" --type "SAS" --version "0.1" --approver "QUA" --sil 3

# QUA approves (template compliance)
python3 tools/workspace.py wf approve --workflow-id "WF-2026-030" --approver "QUA" --decision "APPROVE"

# VER reviews and approves (technical review)
python3 tools/workspace.py wf approve --workflow-id "WF-2026-030" --approver "VER" --decision "APPROVE"

# SAF reviews and approves (safety architecture)
python3 tools/workspace.py wf approve --workflow-id "WF-2026-030" --approver "SAF" --decision "APPROVE"

# PM approves baseline (SAS v1.0)
python3 tools/workspace.py wf approve --workflow-id "WF-2026-030" --approver "PM" --decision "APPROVE"
```

#### Week 2-3: Create Software Design Specification (SDS)

**Week 2, Day 1-3: Detailed Module Design**

```bash
# For each module in SAS, create detailed design:

# Control Module (MOD-CTRL):
#   - Functions: control_init(), control_process(), control_get_state(), transition_to_state()
#   - State machine: 6 states (IDLE, OPENING, OPEN, CLOSING, CLOSED, FAULT)
#   - Complexity estimate: control_process() = 8 (within ≤10 limit)

# Safety Module (MOD-SAFE):
#   - Functions: safety_init(), safety_monitor(), safety_watchdog_refresh(), speed_plausibility_check()
#   - Redundant speed monitoring algorithm
#   - Complexity estimate: safety_monitor() = 7

# Sensor HAL, Actuator HAL, Communication HAL:
#   - Interface functions
#   - Data structures
#   - Error handling
```

**Week 2, Day 4-5: SDS Document Creation**

```bash
# Create SDS document
# Document:
#   - Section 3: Module Detailed Design (5 modules, ~15 functions total)
#   - Section 4: Interface Detailed Design (function signatures, data types)
#   - Section 6: Algorithm Design (speed plausibility check, state machine logic)
#   - Section 7: Error Handling Design (error codes, validation patterns)
#   - Section 8: Traceability (5 modules → 15 functions)

# Add traceability links (SAS → SDS)
python3 tools/workspace.py trace add --from "MOD-CTRL" --to "control_process()" --type "arch-to-design"
python3 tools/workspace.py trace add --from "MOD-SAFE" --to "safety_monitor()" --type "arch-to-design"
# ... (continue for all functions)
```

**Week 3, Day 1: SDS Review and Approval**

```bash
# Validate template
python3 tools/scripts/validate_sas_sds_template.py docs/design/SDS_Train_Door_Control.md --type SDS --sil 3

# Submit for review
python3 tools/workspace.py wf submit --document "docs/design/SDS_Train_Door_Control.md" --type "SDS" --version "0.1" --approver "QUA" --sil 3

# QUA, VER, SAF, IMP, PM approve (same workflow as SAS)
# ...

# Baseline SDS v1.0
```

#### Summary

| Milestone | Duration | Outcome |
|-----------|----------|---------|
| Architecture design | 2 days | 5 modules identified, layered architecture |
| SAS document creation | 2 days | SAS v0.1 with traceability |
| SAS review and approval | 1 day | SAS v1.0 baseline |
| Detailed module design | 3 days | 15 functions designed, complexity ≤10 |
| SDS document creation | 2 days | SDS v0.1 with traceability |
| SDS review and approval | 1 day | SDS v1.0 baseline |
| **Total** | **11 days (~2.5 weeks)** | **SAS and SDS approved and baselined** |

---

## 14. Conclusion

This workflow provides comprehensive guidance for creating, reviewing, and approving Software Architecture Specification (SAS) and Software Design Specification (SDS) documents in compliance with EN 50128:2011 Section 7.3. By following this workflow, you will:

✓ Create high-quality, EN 50128-compliant architecture and design documents  
✓ Apply modular approach (MANDATORY SIL 2+)  
✓ Implement SIL-appropriate architecture techniques (Table A.3)  
✓ Design for complexity ≤ 10 (SIL 3-4)  
✓ Implement defensive programming patterns (SIL 3-4)  
✓ Achieve 100% traceability (SRS → SAS → SDS → Code)  
✓ Obtain independent review and approval (SIL 3-4)

**Key Success Factors**:
- **Modular approach** (independent modules, defined interfaces)
- **Information encapsulation** (hide internal state)
- **Static memory allocation** (no dynamic allocation)
- **Complexity limits** (≤10 for SIL 3-4)
- **Complete traceability** (requirements to architecture to design)

**Next Steps After SAS/SDS Approval**:
1. **Implementation Phase** (Phase 4) - Implement C code based on approved SDS
2. **Unit Testing** - Create unit tests for each module
3. **Traceability** - Continue forward traceability (SDS → Code → Tests)

---

**END OF WORKFLOW**
