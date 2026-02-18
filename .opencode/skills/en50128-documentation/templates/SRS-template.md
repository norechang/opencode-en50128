# Software Requirements Specification (SRS)

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 Section 7.2, Table A.2

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SRS-YYYY-NNN |
| **Version** | 0.1 (Draft) → 1.0 (Approved) |
| **Date** | YYYY-MM-DD |
| **Project** | [Project Name] |
| **SIL Level** | [0, 1, 2, 3, 4] |
| **Author** | [Name], Requirements Engineer |
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

**SIL 0-2 Requirements**: Author, Reviewer, Project Manager  
**SIL 3-4 Requirements**: Author, Independent Reviewer, Safety Manager, Project Manager, Customer

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author** | [REQ Engineer Name] | | |
| **Technical Reviewer** | [Reviewer Name] | | |
| **Safety Manager** (if safety-critical) | [Safety Name] | | |
| **QA Manager** | [QA Name] | | |
| **Project Manager** | [PM Name] | | |
| **Customer Representative** (SIL 3-4) | [Customer Name] | | |

---

## 1. INTRODUCTION

### 1.1 Purpose

[State the purpose of this Software Requirements Specification. Example:]

This Software Requirements Specification (SRS) defines the complete set of software requirements for the [Project Name] system. It provides a detailed description of functional requirements, performance requirements, interface requirements, and safety requirements in accordance with EN 50128:2011 Section 7.2.

**Intended Audience**:
- Software designers and implementers
- Verification and validation teams
- Safety engineers
- Project management
- Customer/certification authorities

### 1.2 Scope

[Define the scope of the software. Example:]

This SRS applies to the [Project Name] software, which [brief description of software purpose and functionality].

**System Context**: [Describe how software fits into larger system]

**In Scope**:
- [List major functional areas]
- [List interfaces]
- [List safety functions]

**Out of Scope**:
- Hardware requirements (covered by Hardware Specification)
- System-level requirements (covered by System Requirements Specification)

### 1.3 SIL Classification

**Target SIL Level**: [0, 1, 2, 3, 4]

**Rationale**: [Explain SIL level selection based on hazard analysis per EN 50126/50129]

**EN 50128 Requirements Specification Techniques** (Table A.2):

| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Applied |
|-----------|-------|---------|---------|---------|
| Formal Methods | - | R | HR | [Yes/No] |
| Modelling | R | R | HR | [Yes/No] |
| Structured Methodology | R | R | HR | **Yes** (mandatory) |

### 1.4 Definitions and Acronyms

| Term | Definition |
|------|------------|
| **SHALL** | Mandatory requirement (must be implemented) |
| **SHOULD** | Recommended requirement (highly desirable) |
| **MAY** | Optional requirement (nice to have) |
| **SIL** | Safety Integrity Level (0-4 per EN 50128) |
| **MISRA C** | Motor Industry Software Reliability Association C coding standard |
| **RTM** | Requirements Traceability Matrix |

[Add project-specific terms]

### 1.5 References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems |
| **[SYSREQ]** | System Requirements Specification, [Document ID] |
| **[HAZLOG]** | Hazard Log, [Document ID] |
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-YYYY-NNN |
| **[MISRAC]** | MISRA C:2012 Guidelines for the use of the C language in critical systems |

### 1.6 Overview

[Provide a brief overview of the document structure and how to read it.]

---

## 2. GENERAL DESCRIPTION

### 2.1 System Context

[Provide context diagram showing software within larger system]

```
┌─────────────────────────────────────────┐
│         System Boundary                 │
│  ┌──────────────────────────────────┐  │
│  │   [Software Name]                │  │
│  │                                  │  │
│  │   [Major Components]             │  │
│  └──────────────────────────────────┘  │
│       ▲              ▲              ▲   │
│       │              │              │   │
└───────┼──────────────┼──────────────┼───┘
        │              │              │
    [Sensor]      [Actuator]     [HMI]
```

**System Interfaces**:
- Hardware interfaces: [List sensors, actuators, processors]
- Software interfaces: [List external systems, libraries]
- Communication interfaces: [List protocols, buses]
- User interfaces: [List HMI, displays]

### 2.2 System Functions (High-Level)

[Provide high-level functional overview. Example:]

The [Software Name] provides the following major functions:
1. **[Function Group 1]**: [Brief description]
2. **[Function Group 2]**: [Brief description]
3. **[Function Group 3]**: [Brief description]

### 2.3 User Characteristics

[Describe intended users. Example:]

**Primary Users**: Railway operators, maintenance personnel

**User Expertise**: [Describe expected training level, domain knowledge]

**User Environment**: [Describe operational environment - control room, trackside, etc.]

### 2.4 Constraints

[List design and implementation constraints. Example:]

**Programming Language**: C (MISRA C:2012 compliant for SIL 2+)

**Platform Constraints**:
- Target processor: [Specify CPU, e.g., ARM Cortex-M4]
- Memory: [Specify RAM/ROM limits]
- Operating system: [Specify RTOS or bare-metal]

**Regulatory Constraints**:
- EN 50128:2011 compliance mandatory
- EN 50126/50129 RAMS requirements
- [Other applicable standards]

**Development Constraints**:
- Static memory allocation only (SIL 2+)
- No dynamic memory allocation (malloc/free forbidden)
- No recursion (highly recommended SIL 3-4)
- Cyclomatic complexity ≤ 10 (SIL 3-4)

### 2.5 Assumptions and Dependencies

[List assumptions. Example:]

**Assumptions**:
- Hardware will be available by [Date]
- External system interfaces stable
- [Other assumptions]

**Dependencies**:
- Depends on [External System X] for [Functionality]
- Requires [Library Y] version [Z] or later
- [Other dependencies]

---

## 3. SOFTWARE REQUIREMENTS

### 3.1 Functional Requirements

#### 3.1.1 [Function Group 1 - e.g., Door Control]

**REQ-FUNC-001**: Door Opening Control  
**Priority**: High  
**SIL Level**: [0-4]  
**Traceability**: SYS-REQ-001

**Description**: The software SHALL open the door when commanded by the train control system AND the train is stationary AND at a station platform.

**Inputs**: 
- Door open command (boolean)
- Train speed (km/h)
- Platform detection signal (boolean)

**Outputs**:
- Door actuator control signal (PWM, 0-100%)

**Preconditions**:
- System initialized
- No emergency brake active
- Door not locked

**Postconditions**:
- Door fully open within 2.0 seconds
- Door open status reported to train control

**Error Handling**:
- IF door fails to open within 2.5 seconds, THEN raise fault alarm
- IF obstacle detected during opening, THEN stop door and reverse

**Verification Method**: Test (unit test, integration test, system test)

---

**REQ-FUNC-002**: Door Closing Control  
**Priority**: High  
**SIL Level**: [0-4]  
**Traceability**: SYS-REQ-002

**Description**: The software SHALL close the door when commanded by the train control system AND no obstacle is detected.

**Inputs**:
- Door close command (boolean)
- Obstacle detection sensor (boolean)

**Outputs**:
- Door actuator control signal (PWM, 0-100%)

**Preconditions**:
- Door currently open or partially open
- No emergency condition active

**Postconditions**:
- Door fully closed within 3.0 seconds
- Door locked status reported to train control

**Error Handling**:
- IF obstacle detected during closing, THEN immediately stop and reopen door
- IF door fails to close within 3.5 seconds, THEN raise fault alarm

**Verification Method**: Test (unit test, integration test, system test)

---

[Continue with additional functional requirements...]

#### 3.1.2 [Function Group 2 - e.g., Emergency Handling]

**REQ-FUNC-010**: Emergency Stop Response  
**Priority**: Critical  
**SIL Level**: 4  
**Traceability**: SYS-REQ-010, HAZ-001

**Description**: Upon receipt of an emergency stop signal, the software SHALL immediately halt all door movement and enter a safe state within 100 milliseconds.

**Inputs**:
- Emergency stop signal (boolean, active high)

**Outputs**:
- All door actuators disabled (0% PWM)
- Emergency status reported to train control

**Preconditions**: None (SHALL respond in any state)

**Postconditions**:
- All door movement stopped
- System in safe state (fail-safe)
- Emergency status logged

**Error Handling**:
- IF emergency signal processing fails, THEN hardware watchdog triggers system reset

**Verification Method**: Test (unit test, integration test, safety test), Static Analysis, FMEA

---

[Continue with additional safety-critical requirements...]

### 3.2 Performance Requirements

**REQ-PERF-001**: Response Time  
**Priority**: High  
**SIL Level**: [0-4]  
**Traceability**: SYS-PERF-001

**Description**: The software SHALL process all input signals and update outputs within 50 milliseconds (20 Hz control loop).

**Acceptance Criteria**: Measured worst-case execution time ≤ 50ms

**Verification Method**: Performance Testing (oscilloscope, profiler)

---

**REQ-PERF-002**: CPU Utilization  
**Priority**: Medium  
**SIL Level**: [0-4]  
**Traceability**: SYS-PERF-002

**Description**: The software SHALL consume no more than 80% of available CPU cycles under worst-case load.

**Acceptance Criteria**: Measured CPU usage ≤ 80% during stress testing

**Verification Method**: Performance Testing (profiler)

---

**REQ-PERF-003**: Memory Footprint  
**Priority**: High  
**SIL Level**: [0-4]  
**Traceability**: SYS-PERF-003

**Description**: 
- The software SHALL use no more than [X] KB of RAM (data + stack)
- The software SHALL use no more than [Y] KB of ROM (code + constants)

**Acceptance Criteria**: 
- Measured RAM usage ≤ [X] KB with 10% margin
- Measured ROM usage ≤ [Y] KB

**Verification Method**: Static Analysis (linker map), Performance Testing

---

[Continue with additional performance requirements...]

### 3.3 Interface Requirements

#### 3.3.1 Hardware Interfaces

**REQ-IF-HW-001**: Door Position Sensor Interface  
**Priority**: High  
**SIL Level**: [0-4]  
**Traceability**: SYS-IF-001

**Description**: The software SHALL read door position from an analog sensor via ADC channel 0.

**Interface Specification**:
- **Signal Type**: Analog voltage, 0-5V
- **Encoding**: 0V = fully closed, 5V = fully open
- **Sampling Rate**: 100 Hz (minimum)
- **Resolution**: 12-bit ADC (0-4095 counts)
- **Conversion**: Position (%) = (ADC_value / 4095) * 100

**Error Handling**:
- IF ADC read fails, THEN use last valid value and raise diagnostic warning
- IF sensor value out of range (< -5% or > 105%), THEN raise sensor fault

**Verification Method**: Integration Test, Interface Test

---

**REQ-IF-HW-002**: Door Actuator Control Interface  
**Priority**: High  
**SIL Level**: [0-4]  
**Traceability**: SYS-IF-002

**Description**: The software SHALL control door actuator via PWM signal on GPIO pin 12.

**Interface Specification**:
- **Signal Type**: PWM, 0-100% duty cycle
- **Frequency**: 10 kHz
- **Range**: 0% = no motion, 100% = maximum speed
- **Update Rate**: 50 Hz (minimum)

**Error Handling**:
- IF PWM output fails, THEN disable actuator and raise critical fault

**Verification Method**: Integration Test, Interface Test

---

[Continue with additional hardware interface requirements...]

#### 3.3.2 Software Interfaces

**REQ-IF-SW-001**: Train Control System Interface  
**Priority**: High  
**SIL Level**: [0-4]  
**Traceability**: SYS-IF-010

**Description**: The software SHALL communicate with the train control system via CAN bus using protocol [Specify Protocol].

**Interface Specification**:
- **Protocol**: CAN 2.0B
- **Baud Rate**: 500 kbps
- **Message Format**: [Specify CAN message IDs and data layout]
- **Update Rate**: 20 Hz (50ms cycle)

**Data Types** (C language):
```c
typedef struct {
    uint8_t door_open_cmd;      // 0=no command, 1=open
    uint8_t door_close_cmd;     // 0=no command, 1=close
    uint8_t emergency_stop;     // 0=normal, 1=emergency
} train_control_msg_t;

typedef struct {
    uint8_t door_position;      // 0-100 (%)
    uint8_t door_status;        // 0=closed, 1=open, 2=moving, 3=fault
    uint8_t fault_code;         // 0=no fault, 1-255=fault codes
} door_status_msg_t;
```

**Error Handling**:
- IF CAN message not received within 100ms, THEN assume communication fault
- IF invalid message received, THEN ignore and log error

**Verification Method**: Integration Test, Interface Test

---

[Continue with additional software interface requirements...]

#### 3.3.3 User Interfaces

**REQ-IF-UI-001**: Diagnostic Display Interface  
**Priority**: Low  
**SIL Level**: 0  
**Traceability**: SYS-IF-020

**Description**: The software MAY provide diagnostic information via serial console (UART) for maintenance purposes.

**Interface Specification**:
- **Protocol**: UART, 115200 baud, 8N1
- **Format**: ASCII text, newline-terminated
- **Content**: System status, fault codes, diagnostic counters

**Note**: This interface is for maintenance only and is NOT safety-critical.

**Verification Method**: Manual Test

---

### 3.4 Safety Requirements

**REQ-SAFE-001**: Fail-Safe Door Locking  
**Priority**: Critical  
**SIL Level**: 4  
**Traceability**: HAZ-001 (doors open while train moving)

**Description**: The software SHALL ensure that doors remain locked whenever train speed exceeds 5 km/h. This is a safety-critical requirement to prevent passenger injury.

**Safety Mechanism**: Redundant speed monitoring with independent verification

**Inputs**:
- Train speed (primary sensor)
- Train speed (secondary sensor, diverse technology)

**Outputs**:
- Door lock command (energize lock solenoid)

**Failure Mode**: IF speed sensor fails, THEN lock doors by default (fail-safe)

**Verification Method**: Safety Test, FMEA, Fault Injection

**Hazard Mitigation**: Mitigates HAZ-001 (doors open during train motion causing passenger fall)

---

**REQ-SAFE-002**: Watchdog Monitoring  
**Priority**: Critical  
**SIL Level**: 4  
**Traceability**: HAZ-002 (software lockup causing unsafe state)

**Description**: The software SHALL refresh an external hardware watchdog timer every 100ms. IF the software fails to refresh the watchdog, the hardware SHALL reset the system into a safe state.

**Safety Mechanism**: External hardware watchdog (independent of software)

**Watchdog Timeout**: 200ms (2x refresh period for margin)

**Safe State**: Upon watchdog reset, all actuators disabled, doors locked

**Verification Method**: Safety Test, Fault Injection (deliberate watchdog timeout)

**Hazard Mitigation**: Mitigates HAZ-002 (software lockup or infinite loop)

---

[Continue with additional safety requirements...]

### 3.5 C Language Implementation Constraints

**REQ-IMPL-001**: MISRA C Compliance  
**Priority**: High  
**SIL Level**: 2+ (Mandatory)  
**Traceability**: EN 50128 Table A.4

**Description**: All source code SHALL comply with MISRA C:2012 guidelines. Deviations SHALL be documented and justified.

**Acceptance Criteria**: PC-lint Plus reports 100% compliance (or documented deviations ≤ 5%)

**Verification Method**: Static Analysis (PC-lint Plus)

---

**REQ-IMPL-002**: Fixed-Width Integer Types  
**Priority**: High  
**SIL Level**: All  
**Traceability**: MISRA C Rule 4.6, EN 50128 best practice

**Description**: The software SHALL use fixed-width integer types (`uint8_t`, `uint16_t`, `uint32_t`, `int8_t`, etc.) instead of platform-dependent types (`int`, `long`, `unsigned`).

**Rationale**: Ensures portability and predictable behavior across platforms

**Verification Method**: Static Analysis, Code Review

---

**REQ-IMPL-003**: Static Memory Allocation  
**Priority**: Critical  
**SIL Level**: 2+ (Mandatory)  
**Traceability**: EN 50128 Table A.4

**Description**: The software SHALL use ONLY static memory allocation. Dynamic memory allocation functions (`malloc`, `calloc`, `realloc`, `free`) SHALL NOT be used.

**Rationale**: Eliminates memory leaks, heap fragmentation, non-deterministic behavior

**Verification Method**: Static Analysis (grep for forbidden functions), Code Review

---

**REQ-IMPL-004**: No Recursion  
**Priority**: High  
**SIL Level**: 3-4 (Highly Recommended)  
**Traceability**: EN 50128 Table A.4

**Description**: The software SHOULD NOT use recursive function calls (a function calling itself directly or indirectly).

**Rationale**: Eliminates stack overflow risk, ensures bounded execution time

**Verification Method**: Static Analysis (call graph analysis), Code Review

---

**REQ-IMPL-005**: Cyclomatic Complexity Limit  
**Priority**: High  
**SIL Level**: All  
**Traceability**: EN 50128 Table A.4

**Description**: Every function SHALL have cyclomatic complexity within the following limits:
- **SIL 0-1**: ≤ 20
- **SIL 2**: ≤ 15
- **SIL 3-4**: ≤ 10

**Rationale**: Lower complexity improves testability, readability, maintainability

**Verification Method**: Static Analysis (Lizard, PC-lint)

---

**REQ-IMPL-006**: Defensive Programming  
**Priority**: High  
**SIL Level**: All (Highly Recommended for SIL 3-4)  
**Traceability**: EN 50128 Table A.3

**Description**: The software SHALL implement defensive programming techniques:
- Validate all input parameters (pointer checks, range checks)
- Check all function return values
- Use assertions for internal consistency checks
- Handle all error conditions explicitly

**Example**:
```c
error_t process_data(const data_t* input, result_t* output) {
    // Defensive checks
    if (input == NULL) return ERROR_NULL_POINTER;
    if (output == NULL) return ERROR_NULL_POINTER;
    if (input->value > MAX_VALUE) return ERROR_OUT_OF_RANGE;
    
    // Process data...
    error_t result = do_processing(input);
    if (result != SUCCESS) return result;  // Check return value
    
    return SUCCESS;
}
```

**Verification Method**: Code Review, Static Analysis

---

**REQ-IMPL-007**: Error Handling Strategy  
**Priority**: High  
**SIL Level**: All  
**Traceability**: EN 50128 design best practices

**Description**: The software SHALL use explicit error return codes (NOT errno or setjmp/longjmp).

**Error Type Definition**:
```c
typedef enum {
    SUCCESS = 0,
    ERROR_NULL_POINTER,
    ERROR_OUT_OF_RANGE,
    ERROR_TIMEOUT,
    ERROR_HARDWARE_FAULT,
    // ... additional error codes
} error_t;
```

**All functions that can fail SHALL return `error_t`.**

**Verification Method**: Code Review, Static Analysis

---

[Continue with additional implementation constraint requirements...]

---

## 4. VERIFICATION AND TRACEABILITY

### 4.1 Verification Methods

Each requirement SHALL be verified using one or more of the following methods:

| Method | Description | Applicable To |
|--------|-------------|---------------|
| **Test** | Unit test, integration test, system test, validation test | Functional, performance, interface requirements |
| **Analysis** | Static analysis, dynamic analysis, timing analysis | Performance, safety, implementation requirements |
| **Inspection** | Code review, design review, document review | All requirements |
| **Demonstration** | Operational demonstration to customer | High-level functional requirements |

### 4.2 Requirements Traceability Matrix (RTM)

**Location**: `docs/traceability/RTM.md`

**Format**: Bidirectional traceability from system requirements to software requirements to design to code to tests.

| System Req | SW Req | Design | Code | Test | Status |
|------------|--------|--------|------|------|--------|
| SYS-001 | REQ-FUNC-001 | MOD-001 | door_ctrl.c:45 | TC-UNIT-001, TC-INT-001, TC-SYS-001 | Traced |

**RTM Completeness**: 100% of requirements SHALL be traced forward (to tests) and backward (to system requirements).

### 4.3 Requirements Quality Checklist

All requirements SHALL meet the following quality criteria:

- [ ] **Unique ID**: Each requirement has a unique identifier
- [ ] **Unambiguous**: Single interpretation (uses SHALL/SHOULD/MAY)
- [ ] **Testable**: Verification method identified, acceptance criteria defined
- [ ] **Complete**: All necessary information provided
- [ ] **Consistent**: No conflicts with other requirements
- [ ] **Traceable**: Linked to system requirements and tests
- [ ] **SIL Assigned**: SIL level specified for safety-critical requirements
- [ ] **C-Compatible**: Implementation feasible in C within constraints

---

## 5. REQUIREMENTS SUMMARY

### 5.1 Requirements Count by Category

| Category | Count | Critical | High | Medium | Low |
|----------|-------|----------|------|--------|-----|
| Functional | [N] | [N] | [N] | [N] | [N] |
| Performance | [N] | [N] | [N] | [N] | [N] |
| Interface - Hardware | [N] | [N] | [N] | [N] | [N] |
| Interface - Software | [N] | [N] | [N] | [N] | [N] |
| Interface - User | [N] | [N] | [N] | [N] | [N] |
| Safety | [N] | [N] | [N] | [N] | [N] |
| Implementation | [N] | [N] | [N] | [N] | [N] |
| **TOTAL** | **[N]** | **[N]** | **[N]** | **[N]** | **[N]** |

### 5.2 Requirements Count by SIL Level

| SIL Level | Count | Percentage |
|-----------|-------|------------|
| SIL 4 | [N] | [%] |
| SIL 3 | [N] | [%] |
| SIL 2 | [N] | [%] |
| SIL 1 | [N] | [%] |
| SIL 0 | [N] | [%] |
| **TOTAL** | **[N]** | **100%** |

---

## 6. COMPLIANCE MATRIX

### 6.1 EN 50128 Section 7.2 Compliance

| Requirement | Section | Evidence | Status |
|-------------|---------|----------|--------|
| **Requirements specification established** | 7.2.2 | This document (SRS) | ✓ |
| **Requirements unambiguous** | 7.2.3 | Section 4.3 (quality checklist) | ✓ |
| **Requirements testable** | 7.2.4 | Section 4.1 (verification methods) | ✓ |
| **Requirements traceable** | 7.2.5 | Section 4.2 (RTM) | ✓ |
| **SIL level assigned** | 7.2.6 | All requirements have SIL field | ✓ |
| **Safety requirements identified** | 7.2.7 | Section 3.4 | ✓ |

### 6.2 EN 50128 Table A.2 Compliance (Requirements Techniques)

| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Applied |
|-----------|-------|---------|---------|---------|
| Structured Methodology | R | R | HR | ✓ Yes |
| Decision Tables | R | R | HR | [Yes/No] |
| Modelling | R | R | HR | [Yes/No] |

---

## 7. REFERENCES

### 7.1 Normative References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems |
| **[MISRAC]** | MISRA C:2012 Guidelines for the use of the C language in critical systems |

### 7.2 Project References

| Reference | Document |
|-----------|----------|
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-YYYY-NNN |
| **[HAZLOG]** | Hazard Log, [Document ID] |

---

## APPENDICES

### Appendix A: Requirements Template

```markdown
**REQ-[CATEGORY]-NNN**: [Requirement Title]  
**Priority**: [Critical / High / Medium / Low]  
**SIL Level**: [0, 1, 2, 3, 4]  
**Traceability**: [Parent requirement ID, hazard ID]

**Description**: [Detailed requirement using SHALL/SHOULD/MAY]

**Inputs**: [Required inputs]  
**Outputs**: [Expected outputs]  
**Preconditions**: [System state before requirement applies]  
**Postconditions**: [System state after requirement fulfilled]  

**Error Handling**: [How errors are detected and handled]

**Verification Method**: [Test / Analysis / Inspection / Demonstration]  
**Acceptance Criteria**: [Specific pass/fail criteria]
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
