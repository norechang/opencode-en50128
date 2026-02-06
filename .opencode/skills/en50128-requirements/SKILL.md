---
name: en50128-requirements
description: Requirements engineering patterns and workflows for EN 50128 railway software compliance
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  language: C
---

## What I do

I provide patterns, templates, and workflows for requirements engineering compliant with EN 50128 Section 7.2:
- Define requirement quality attributes (unambiguous, testable, traceable)
- Provide requirement templates with SIL classification
- Enforce SHALL/SHOULD/MAY keyword usage
- Maintain traceability matrices
- Consider C language constraints (data types, memory, real-time)

## When to use me

Use this skill when:
- Starting requirements specification phase
- Writing or reviewing software requirements
- Establishing requirements traceability
- Assigning SIL levels to requirements
- Validating requirement quality

## Requirements Techniques (EN 50128 Table A.2)

**EN 50128 Section 7.2, Table A.2** defines techniques for software requirements specification:

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | Formal Methods | D.28 | - | R | HR |
| 2 | Modelling | Table A.17 | R | R | HR |
| 3 | Structured Methodology | D.52 | R | R | HR |
| 4 | Decision Tables | D.13 | R | R | HR |

**Key Points:**
- **Formal Methods** are Highly Recommended for SIL 3-4
- **Modelling** is Highly Recommended for SIL 3-4
- **Structured Methodology** is Highly Recommended for SIL 3-4
- **Decision Tables** are Highly Recommended for SIL 3-4
- One or more techniques SHALL be selected per SIL level

**Standard Reference:** `std/EN50128-2011.md` Section 7.2, Table A.2

### 1. Formal Methods (D.28)

**Purpose:** Mathematical specification and verification of requirements

**Techniques:**
- **Z notation** - State-based formal specification
- **VDM (Vienna Development Method)** - Model-oriented specification
- **B-Method** - Event-based specification with refinement
- **Temporal Logic** - Specify timing and sequencing properties

**When to use:**
- SIL 3-4: Highly Recommended for critical safety requirements
- Complex state machines or protocols
- Requirements with strict timing constraints
- When mathematical proof of correctness is needed

**Example - Z Notation for Speed Validation:**
```
[SPEED]

SpeedRange
  min_speed: ℕ
  max_speed: ℕ
  current_speed: ℕ
  
  min_speed = 0
  max_speed = 300
  0 ≤ current_speed ≤ 300

ValidateSpeed
  ΔSpeedRange
  speed?: ℕ
  result!: {OK, ERROR}
  
  (speed? ≥ min_speed ∧ speed? ≤ max_speed) ⇒ result! = OK
  (speed? < min_speed ∨ speed? > max_speed) ⇒ result! = ERROR
```

**Corresponding C Requirement:**
```
REQ-FUNC-001: Speed Input Validation (Formal)

The speed sensor interface SHALL validate all speed readings using the
following formal specification:

Given: min_speed = 0, max_speed = 300
Input: speed_value (uint16_t)
Output: validation_result (error_t)

∀ speed_value ∈ ℕ:
  (0 ≤ speed_value ≤ 300) ⇒ validation_result = SUCCESS
  (speed_value < 0 ∨ speed_value > 300) ⇒ validation_result = ERROR_OUT_OF_RANGE

Rationale: Formal specification ensures unambiguous validation logic.
SIL Level: 3
```

### 2. Modelling (Table A.17)

**Purpose:** Visual and behavioral models of system requirements

**Modeling Techniques (from Table A.17):**
- **State Machines** - Model system states and transitions
- **Data Flow Diagrams** - Show data movement through system
- **Control Flow Diagrams** - Show control logic flow
- **Timing Diagrams** - Show temporal relationships
- **Petri Nets** - Model concurrent processes

**When to use:**
- All SIL levels (Recommended SIL 0, Highly Recommended SIL 3-4)
- Complex state-based behavior
- Concurrent or parallel operations
- Real-time systems with timing constraints

**Example - State Machine Model:**
```
State Machine: Sensor Monitoring

States:
  - INIT: Initial state
  - OPERATIONAL: Normal operation
  - DIAGNOSTIC: Self-test mode
  - FAILED: Sensor failure detected
  - SAFE_STATE: System in safe state

Transitions:
  INIT → OPERATIONAL: [Power-on self-test passed]
  OPERATIONAL → DIAGNOSTIC: [Diagnostic requested]
  OPERATIONAL → FAILED: [Sensor error detected]
  DIAGNOSTIC → OPERATIONAL: [Diagnostic passed]
  DIAGNOSTIC → FAILED: [Diagnostic failed]
  FAILED → SAFE_STATE: [Always]
  SAFE_STATE → INIT: [System reset]

Invariants:
  - System SHALL enter SAFE_STATE within 100ms of FAILED state
  - System SHALL NOT transition from SAFE_STATE to OPERATIONAL directly
```

**Corresponding C Requirements:**
```
REQ-STATE-001: Sensor State Machine

The sensor monitoring system SHALL implement the following states:
- INIT (0x00): Initial state after power-on
- OPERATIONAL (0x01): Normal sensor operation
- DIAGNOSTIC (0x02): Self-test in progress
- FAILED (0x03): Sensor failure detected
- SAFE_STATE (0x04): System in safe shutdown

Type: state_t (uint8_t enumeration)
SIL Level: 3

REQ-STATE-002: Safe State Transition Time

The system SHALL transition from FAILED to SAFE_STATE within 100 milliseconds.

Acceptance: Transition time measured < 100ms in all test scenarios.
SIL Level: 3
Verification Method: Test (timing measurement)
```

### 3. Structured Methodology (D.52)

**Purpose:** Systematic, disciplined approach to requirements engineering

**Structured Methods:**
- **SADT (Structured Analysis and Design Technique)**
- **SSADM (Structured Systems Analysis and Design Method)**
- **Yourdon Structured Method**
- **Jackson System Development (JSD)**

**Key Principles:**
- Top-down decomposition of requirements
- Hierarchical organization
- Consistent notation and terminology
- Systematic traceability
- Iterative refinement

**When to use:**
- All SIL levels (Highly Recommended SIL 3-4)
- Large, complex systems
- When requirements must be decomposed systematically
- When strong traceability is required

**Example - Hierarchical Decomposition:**
```
System: Railway Speed Control (SIL 3)

1. SYSTEM-LEVEL REQUIREMENTS
   SYS-001: Speed Monitoring and Control System
   
2. SUBSYSTEM REQUIREMENTS
   SS-001: Speed Sensor Interface Subsystem
   SS-002: Control Logic Subsystem
   SS-003: Actuator Interface Subsystem
   SS-004: Safety Monitoring Subsystem

3. COMPONENT REQUIREMENTS (SS-001: Speed Sensor Interface)
   COMP-001: Sensor Data Acquisition
     └─ REQ-FUNC-001: Read sensor value (uint16_t, range [0, 300])
     └─ REQ-FUNC-002: Validate sensor range
     └─ REQ-FUNC-003: Detect sensor failure
   
   COMP-002: Sensor Data Processing
     └─ REQ-FUNC-004: Convert raw value to km/h
     └─ REQ-FUNC-005: Apply calibration correction
     └─ REQ-FUNC-006: Filter noise (moving average)
   
   COMP-003: Sensor Error Handling
     └─ REQ-SAFE-001: Detect out-of-range values
     └─ REQ-SAFE-002: Detect communication timeout
     └─ REQ-SAFE-003: Initiate safe state on failure

4. DETAILED REQUIREMENTS (REQ-FUNC-001)
   The speed sensor interface SHALL read the sensor value via SPI bus
   and store the result in a uint16_t variable within 10 milliseconds.
   
   Traceability: SYS-001 → SS-001 → COMP-001 → REQ-FUNC-001
   SIL Level: 3
   Verification: Unit test with timing measurement
```

### 4. Decision Tables (D.13)

**Purpose:** Specify complex logic with multiple conditions and actions

**When to use:**
- Complex conditional logic (multiple inputs, multiple outputs)
- All possible combinations must be handled
- Safety-critical decision logic
- Input validation with multiple criteria
- State transition logic

**Decision Table Structure:**
```
┌─────────────────────┬───────────────────────────────────┐
│ CONDITIONS          │ Rule 1 | Rule 2 | Rule 3 | Rule 4 │
├─────────────────────┼───────────────────────────────────┤
│ Condition 1         │   T    │   T    │   F    │   F    │
│ Condition 2         │   T    │   F    │   T    │   F    │
├─────────────────────┼───────────────────────────────────┤
│ ACTIONS             │        │        │        │        │
├─────────────────────┼───────────────────────────────────┤
│ Action 1            │   X    │        │        │        │
│ Action 2            │        │   X    │   X    │        │
│ Action 3            │        │        │        │   X    │
└─────────────────────┴───────────────────────────────────┘
```

**Example - Sensor Validation Decision Table:**
```
Decision Table: Sensor Validation (SIL 3)

Requirement: REQ-SAFE-010: Sensor Input Validation

┌──────────────────────────┬────────────────────────────────────────────┐
│ CONDITIONS               │ R1  │ R2  │ R3  │ R4  │ R5  │ R6  │ R7  │ R8  │
├──────────────────────────┼────────────────────────────────────────────┤
│ Value in range [0,300]   │  T  │  T  │  T  │  T  │  F  │  F  │  F  │  F  │
│ CRC checksum valid       │  T  │  T  │  F  │  F  │  T  │  T  │  F  │  F  │
│ Timeout occurred         │  T  │  F  │  T  │  F  │  T  │  F  │  T  │  F  │
├──────────────────────────┼────────────────────────────────────────────┤
│ ACTIONS                  │     │     │     │     │     │     │     │     │
├──────────────────────────┼────────────────────────────────────────────┤
│ Accept value             │     │  X  │     │     │     │     │     │     │
│ Return ERROR_TIMEOUT     │  X  │     │  X  │     │  X  │     │  X  │     │
│ Return ERROR_CRC         │     │     │     │  X  │     │     │     │     │
│ Return ERROR_OUT_OF_RANGE│     │     │     │     │     │  X  │     │     │
│ Enter SAFE_STATE         │     │     │  X  │     │     │  X  │  X  │  X  │
└──────────────────────────┴────────────────────────────────────────────┘

Legend: T = True, F = False, X = Action performed
```

**Corresponding C Requirements:**
```
REQ-SAFE-010: Sensor Validation Decision Logic

The sensor validation function SHALL implement the following decision logic:

Rule 1: IF (value in range) AND (CRC valid) AND (timeout)
        THEN return ERROR_TIMEOUT

Rule 2: IF (value in range) AND (CRC valid) AND (NOT timeout)
        THEN accept value, return SUCCESS

Rule 3: IF (value in range) AND (CRC invalid) AND (timeout)
        THEN return ERROR_TIMEOUT, enter SAFE_STATE

Rule 4: IF (value in range) AND (CRC invalid) AND (NOT timeout)
        THEN return ERROR_CRC

Rule 5: IF (value out of range) AND (CRC valid) AND (timeout)
        THEN return ERROR_TIMEOUT

Rule 6: IF (value out of range) AND (CRC valid) AND (NOT timeout)
        THEN return ERROR_OUT_OF_RANGE, enter SAFE_STATE

Rule 7: IF (value out of range) AND (CRC invalid) AND (timeout)
        THEN return ERROR_TIMEOUT, enter SAFE_STATE

Rule 8: IF (value out of range) AND (CRC invalid) AND (NOT timeout)
        THEN enter SAFE_STATE

SIL Level: 3
Verification: Decision table test coverage (all 8 rules tested)
```

**C Implementation Structure:**
```c
// Decision table implementation for sensor validation
error_t validate_sensor_input(uint16_t value, bool crc_valid, bool timeout)
{
    // Check range
    bool in_range = (value >= 0) && (value <= 300);
    
    // Decision table logic (8 rules)
    if (in_range && crc_valid && timeout) {
        // Rule 1
        return ERROR_TIMEOUT;
    }
    else if (in_range && crc_valid && !timeout) {
        // Rule 2: Accept value
        return SUCCESS;
    }
    else if (in_range && !crc_valid && timeout) {
        // Rule 3: CRC error + timeout → safe state
        enter_safe_state();
        return ERROR_TIMEOUT;
    }
    else if (in_range && !crc_valid && !timeout) {
        // Rule 4: CRC error only
        return ERROR_CRC;
    }
    else if (!in_range && crc_valid && timeout) {
        // Rule 5: Out of range + timeout
        return ERROR_TIMEOUT;
    }
    else if (!in_range && crc_valid && !timeout) {
        // Rule 6: Out of range → safe state
        enter_safe_state();
        return ERROR_OUT_OF_RANGE;
    }
    else if (!in_range && !crc_valid && timeout) {
        // Rule 7: Multiple errors → safe state
        enter_safe_state();
        return ERROR_TIMEOUT;
    }
    else {
        // Rule 8: Multiple errors → safe state
        enter_safe_state();
        return ERROR_INVALID;
    }
}
```

## Requirements Quality Attributes

Each requirement MUST be:
- **Unambiguous**: Single interpretation only
- **Testable**: Can be verified objectively
- **Clear**: Easily understood by stakeholders
- **Correct**: Accurately reflects stakeholder needs
- **Feasible**: Technically and economically possible
- **Atomic**: Cannot be decomposed further
- **Necessary**: Documents essential capability
- **Implementation-free**: Does not prescribe solution

## Requirements Template

```markdown
### REQ-[TYPE]-[ID]: [Title]

**Type**: [Functional|Performance|Interface|Safety|Security]
**SIL**: [0|1|2|3|4]
**Priority**: [Mandatory|Highly Recommended|Recommended]
**Source**: [Reference to source document]

**Description**:
The system SHALL/SHOULD/MAY [action] [condition].

**Rationale**:
[Why this requirement exists]

**Acceptance Criteria**:
1. [Testable criterion 1]
2. [Testable criterion 2]

**Dependencies**:
- REQ-[ID]: [Description]

**Verification Method**: [Test|Analysis|Inspection|Demonstration]
```

## Language Requirements

- **SHALL**: Mandatory requirement
- **SHOULD**: Highly recommended
- **MAY**: Optional
- **WILL**: Statement of fact (not requirement)

## C Language Considerations

Requirements must address:
- **Data types**: Specify fixed-width types (uint8_t, uint16_t, etc.)
- **Memory**: Static allocation requirements (SIL 2+)
- **Ranges**: Min/max values, bounds
- **Error handling**: Required error detection and handling
- **Real-time**: Timing constraints, WCET requirements
- **Safety**: Fault detection, safe states

Example:
```
REQ-FUNC-001: Speed Input Validation

The speed sensor interface SHALL validate all speed readings are within
the range [0, 300] km/h using uint16_t data type before processing.

Rationale: Prevent out-of-range values from causing system malfunction.

Acceptance: Speed values outside [0, 300] km/h are rejected with error code.
```

## Requirements Classification

### By Type
- **Functional**: What the system shall do
- **Performance**: Timing, throughput, resource usage
- **Interface**: Hardware/software interfaces, protocols
- **Safety**: Safety-critical functions, fault handling
- **Security**: Protection against threats

### By SIL Level
- **SIL 0**: Non-safety related
- **SIL 1**: Minor injury potential
- **SIL 2**: Serious injury potential (MISRA C mandatory)
- **SIL 3**: Death of individuals (independent V&V mandatory)
- **SIL 4**: Death of many people (formal methods recommended)

## Traceability

### Forward Traceability
- Requirements → Design Elements
- Requirements → Test Cases
- Requirements → Code Modules

### Backward Traceability
- Requirements ← Stakeholder Needs
- Requirements ← System Requirements
- Requirements ← Safety Requirements

## Verification Methods (EN 50128 Table A.19)

| SIL | Test | Analysis | Review | Simulation |
|-----|------|----------|--------|------------|
| 0   | HR   | HR       | HR     | R          |
| 1-2 | HR   | HR       | HR     | HR         |
| 3-4 | M    | HR       | M      | HR         |

**Legend**: M = Mandatory, HR = Highly Recommended, R = Recommended

## Requirements Review Checklist

- [ ] Unique identifier assigned
- [ ] Unambiguous wording
- [ ] Testable and measurable
- [ ] SHALL/SHOULD/MAY used correctly
- [ ] SIL level assigned
- [ ] Verification method defined
- [ ] Traceability to source documented
- [ ] Dependencies identified
- [ ] Acceptance criteria are measurable
- [ ] Implementation-independent
- [ ] C language constraints considered

## Common Patterns

### Safety Requirement Pattern
```
The system SHALL [action] when [condition] to prevent [hazard].
```

### Interface Requirement Pattern
```
The [component] SHALL provide [interface] to [other component] with [constraints].
```

### Performance Requirement Pattern
```
The system SHALL [action] within [time/resource constraint] under [conditions].
```

## Standard References

- **EN 50128:2011 Section 7.2** - Software Requirements Specification - `std/EN50128-2011.md`
- **EN 50128:2011 Table A.2** - Requirements Specification Techniques - `std/EN50128-2011.md`
- **EN 50128:2011 Reference D.28** - Formal Methods - `std/EN50128-2011.md`
- **EN 50128:2011 Reference D.52** - Structured Methodology - `std/EN50128-2011.md`
- **EN 50128:2011 Reference D.13** - Decision Tables - `std/EN50128-2011.md`
- **EN 50128:2011 Table A.17** - Modelling Techniques - `std/EN50128-2011.md`
- **EN 50126-1:2017 Section 7** - RAMS Requirements - `std/EN 50126-1-2017.md`

## Interaction with Other Agents

**Provides requirements to:**
- `/des` - Designer (forward traceability to design elements)
- `/tst` - Tester (requirements must be testable)
- `/ver` - Verifier (requirements verification)
- `/val` - Validator (requirements validation)

**Coordinates with:**
- `/saf` - Safety Engineer (safety requirements specification)
- `/pm` - Project Manager (requirements approval, change control)
- `/cm` - Configuration Manager (requirements traceability, version control)

**Receives input from:**
- Stakeholders (user needs, system requirements)
- `/saf` - Safety Engineer (safety constraints, hazards)
- `/pm` - Project Manager (project scope, priorities)

## Abbreviations

- **REQ** = Requirements Engineer (you)
- **SRS** = Software Requirements Specification
- **SIL** = Safety Integrity Level
- **M** = Mandatory
- **HR** = Highly Recommended
- **R** = Recommended

**Reference:** `std/EN50128-ABBREVIATIONS.md`
