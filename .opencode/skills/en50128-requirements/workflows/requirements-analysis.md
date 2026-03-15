# Requirements Analysis Workflow

**Purpose**: Analyze, refine, and validate raw requirements to ensure completeness, correctness, consistency, and traceability.

**EN 50128 Reference**: Section 7.2 Software Requirements, Table A.2

**Role**: Requirements Engineer (REQ)

**Prerequisites**:
- Requirements elicitation completed (`requirements-elicitation.md`)
- Raw requirements collected from all sources
- System Requirements Specification available
- Hazard Log available

---

## Workflow Steps

### 1. Requirements Classification

**Objective**: Organize requirements by type and priority

#### 1.1 Classify by Type
- [ ] Group requirements into categories:
  - **Functional Requirements** (REQ-FUNC-XXX): System behavior, features
  - **Performance Requirements** (REQ-PERF-XXX): Timing, throughput, resources
  - **Interface Requirements** (REQ-INTF-XXX): Hardware, software, communication
  - **Safety Requirements** (REQ-SAFE-XXX): Safety functions, fault handling
  - **Quality Requirements** (REQ-QUAL-XXX): Reliability, maintainability
  - **Constraint Requirements** (REQ-CONS-XXX): Design, implementation, regulatory

**Example Classification**:
```
REQ-FUNC-001: Read speed sensor value
REQ-PERF-002: Process sensor data within 50ms
REQ-INTF-003: Communicate via CAN bus at 1 Mbps
REQ-SAFE-004: Detect sensor failure within 100ms
REQ-QUAL-005: Achieve MTBF ≥ 10,000 hours
REQ-CONS-006: Implement in MISRA C:2012 compliant code
```

#### 1.2 Assign SIL Levels
- [ ] For each requirement, determine Safety Integrity Level:
  1. Trace to hazard (from Hazard Log)
  2. Use hazard severity as basis for SIL assignment
  3. Safety functions inherit SIL from hazard
  4. Supporting functions may have lower SIL (justify)

**SIL Assignment Matrix**:
| Hazard Severity | SIL Level | Example |
|-----------------|-----------|---------|
| Catastrophic (death of many) | SIL 4 | Train collision prevention |
| Critical (death of individuals) | SIL 3 | Emergency braking |
| Serious (serious injuries) | SIL 2 | Door interlock |
| Minor (minor injuries) | SIL 1 | Passenger information |
| Negligible | SIL 0 | Entertainment system |

**Example**:
```
Hazard: HAZ-005 "Train overspeed" → Severity: Catastrophic → SIL 4

Requirements:
- REQ-SAFE-010: Detect overspeed condition (SIL 4 - direct safety function)
- REQ-SAFE-011: Apply emergency brake (SIL 4 - direct safety function)
- REQ-FUNC-001: Read speed sensor (SIL 4 - provides critical data)
- REQ-INTF-020: Display speed to operator (SIL 1 - informational only)

Rationale for REQ-INTF-020 lower SIL:
Display is for operator awareness only; safety function does not depend on display.
Safety function (overspeed detection) operates independently of display.
```

#### 1.3 Prioritize Requirements
- [ ] Assign priority level:
  - **Mandatory (M)**: Must be implemented
  - **Highly Recommended (HR)**: Strong preference, rationale if not implemented
  - **Recommended (R)**: Should be considered
  - **Optional (O)**: Nice-to-have, discretionary

- [ ] Priority considerations:
  - Safety requirements: Typically Mandatory
  - Regulatory requirements: Mandatory
  - Stakeholder critical needs: Mandatory or HR
  - Nice-to-have features: R or O

---

### 2. Requirements Decomposition

**Objective**: Break down complex high-level requirements into detailed, implementable requirements

**Technique**: Structured Methodology (EN 50128 Table A.2, D.52)

#### 2.1 Hierarchical Decomposition
- [ ] Start with system-level requirements
- [ ] Decompose into subsystem requirements
- [ ] Further decompose into component requirements
- [ ] Continue until requirements are atomic (cannot be decomposed further)

**Example - Speed Control System**:
```
LEVEL 1: SYSTEM REQUIREMENT
SYS-001: Speed Monitoring and Control System
  "The system shall monitor train speed and maintain it within specified limits."

LEVEL 2: SUBSYSTEM REQUIREMENTS
SS-001: Speed Sensor Subsystem
  "Acquire and validate speed sensor data."

SS-002: Control Logic Subsystem
  "Process speed data and generate control commands."

SS-003: Actuator Interface Subsystem
  "Execute control commands via brake/throttle actuators."

SS-004: Safety Monitoring Subsystem
  "Detect faults and initiate safe state."

LEVEL 3: COMPONENT REQUIREMENTS (SS-001)
COMP-001: Sensor Data Acquisition
  "Read raw sensor values from hardware interface."
  
  Detailed Requirements:
  - REQ-INTF-001: Read sensor via SPI at address 0x4000
  - REQ-PERF-002: Complete read within 10ms
  - REQ-FUNC-003: Store value in uint16_t variable

COMP-002: Sensor Data Validation
  "Validate sensor data is within acceptable range."
  
  Detailed Requirements:
  - REQ-SAFE-010: Validate range [0, 300] km/h
  - REQ-SAFE-011: Validate CRC checksum
  - REQ-SAFE-012: Detect communication timeout
  - REQ-SAFE-013: Return error code on validation failure

COMP-003: Sensor Error Handling
  "Handle sensor faults and initiate safe response."
  
  Detailed Requirements:
  - REQ-SAFE-020: Detect out-of-range values
  - REQ-SAFE-021: Detect sensor disconnection
  - REQ-SAFE-022: Enter safe state within 100ms of fault detection
  - REQ-SAFE-023: Log fault event with timestamp
```

**Traceability**:
```
SYS-001 → SS-001 → COMP-001 → REQ-INTF-001, REQ-PERF-002, REQ-FUNC-003
SYS-001 → SS-001 → COMP-002 → REQ-SAFE-010, REQ-SAFE-011, REQ-SAFE-012, REQ-SAFE-013
SYS-001 → SS-001 → COMP-003 → REQ-SAFE-020, REQ-SAFE-021, REQ-SAFE-022, REQ-SAFE-023
```

#### 2.2 Decision Table Analysis (Complex Logic)

**When to use**: Requirements with multiple conditions and actions

**Technique**: Decision Tables (EN 50128 Table A.2, D.13)

**Example - Sensor Validation Logic**:
```
Requirement: REQ-SAFE-100: Sensor Validation Decision Logic

Decision Table: Sensor Input Validation (SIL 3)

Conditions:
C1: Value in range [0, 300]
C2: CRC checksum valid
C3: Communication timeout occurred

Actions:
A1: Accept value (return SUCCESS)
A2: Return ERROR_TIMEOUT
A3: Return ERROR_CRC
A4: Return ERROR_OUT_OF_RANGE
A5: Enter SAFE_STATE

┌──────────────────┬──────────────────────────────────────────┐
│ CONDITIONS       │ R1  │ R2  │ R3  │ R4  │ R5  │ R6  │ R7  │ R8  │
├──────────────────┼──────────────────────────────────────────┤
│ C1: In range     │  T  │  T  │  T  │  T  │  F  │  F  │  F  │  F  │
│ C2: CRC valid    │  T  │  T  │  F  │  F  │  T  │  T  │  F  │  F  │
│ C3: Timeout      │  T  │  F  │  T  │  F  │  T  │  F  │  T  │  F  │
├──────────────────┼──────────────────────────────────────────┤
│ ACTIONS          │     │     │     │     │     │     │     │     │
├──────────────────┼──────────────────────────────────────────┤
│ A1: Accept       │     │  X  │     │     │     │     │     │     │
│ A2: ERROR_TIMEOUT│  X  │     │  X  │     │  X  │     │  X  │     │
│ A3: ERROR_CRC    │     │     │     │  X  │     │     │     │     │
│ A4: ERROR_RANGE  │     │     │     │     │     │  X  │     │     │
│ A5: SAFE_STATE   │     │     │  X  │     │     │  X  │  X  │  X  │
└──────────────────┴──────────────────────────────────────────┘
```

**Decomposed Requirements**:
```
REQ-SAFE-100: Sensor Validation Decision Logic (Parent)

Child Requirements (derived from decision table):

REQ-SAFE-101: Timeout + In Range + CRC Valid
  The system SHALL return ERROR_TIMEOUT when timeout occurs,
  value is in range, and CRC is valid. (Rule 1)
  SIL: 3

REQ-SAFE-102: Accept Valid Input
  The system SHALL accept the sensor value and return SUCCESS when
  no timeout occurs, value is in range, and CRC is valid. (Rule 2)
  SIL: 3

REQ-SAFE-103: Timeout + In Range + CRC Invalid → Safe State
  The system SHALL return ERROR_TIMEOUT and enter SAFE_STATE when
  timeout occurs, value is in range, but CRC is invalid. (Rule 3)
  SIL: 3

REQ-SAFE-104: CRC Invalid (No Timeout)
  The system SHALL return ERROR_CRC when CRC is invalid, value is
  in range, and no timeout occurred. (Rule 4)
  SIL: 3

REQ-SAFE-105: Out of Range + Timeout
  The system SHALL return ERROR_TIMEOUT when value is out of range
  and timeout occurred. (Rule 5)
  SIL: 3

REQ-SAFE-106: Out of Range → Safe State
  The system SHALL return ERROR_OUT_OF_RANGE and enter SAFE_STATE
  when value is out of range, CRC is valid, and no timeout. (Rule 6)
  SIL: 3

REQ-SAFE-107: Multiple Errors + Timeout → Safe State
  The system SHALL return ERROR_TIMEOUT and enter SAFE_STATE when
  value is out of range, CRC is invalid, and timeout occurred. (Rule 7)
  SIL: 3

REQ-SAFE-108: Multiple Errors (No Timeout) → Safe State
  The system SHALL enter SAFE_STATE when value is out of range,
  CRC is invalid, and no timeout occurred. (Rule 8)
  SIL: 3
```

**Verification**: All 8 rules must be tested (100% decision table coverage)

---

### 3. Requirements Refinement

**Objective**: Improve quality of requirements statements

#### 3.1 Apply Requirements Quality Attributes
- [ ] For each requirement, verify:

**Unambiguous** (single interpretation):
- Avoid: "The system shall respond quickly."
- Use: "The system SHALL respond within 100 milliseconds."

**Testable** (verifiable by objective criteria):
- Avoid: "The system shall be reliable."
- Use: "The system SHALL have Mean Time Between Failures (MTBF) ≥ 10,000 hours."

**Clear** (easily understood):
- Avoid: "The system shall utilize sensor input to effectuate control."
- Use: "The system SHALL read sensor data and generate control commands."

**Correct** (accurately reflects need):
- Validate with stakeholders
- Cross-check with system requirements
- Verify against domain knowledge

**Feasible** (technically and economically possible):
- Avoid: "The system SHALL process 1 million sensor readings per millisecond." (infeasible on target hardware)
- Use: "The system SHALL process 1000 sensor readings per second." (feasible)

**Atomic** (one requirement per ID):
- Avoid: "The system shall read sensor data, validate it, and generate control commands."
- Split into 3 requirements:
  - REQ-001: "The system SHALL read sensor data."
  - REQ-002: "The system SHALL validate sensor data."
  - REQ-003: "The system SHALL generate control commands."

**Necessary** (essential capability):
- Avoid: "The system MAY display a 3D animation of train position." (nice-to-have)
- Use: "The system SHALL display current train speed." (necessary for operator)

**Implementation-free** (what, not how):
- Avoid: "The system shall use a Kalman filter to estimate speed." (prescribes solution)
- Use: "The system SHALL estimate speed with accuracy ±1 km/h." (describes need)

**Use Checklist**: `resources/requirement-quality-checklist.md`

#### 3.2 Apply Modal Verb Standards (RFC 2119)
- [ ] Review each requirement statement
- [ ] Ensure correct modal verb usage:

**SHALL** = Mandatory requirement (must be implemented):
- "The system SHALL validate all sensor inputs before processing."

**SHALL NOT** = Prohibition (must not do):
- "The system SHALL NOT use dynamic memory allocation." (SIL 2+ constraint)

**SHOULD** = Highly recommended (strong preference, rationale if not done):
- "The system SHOULD log all fault events to non-volatile memory."

**SHOULD NOT** = Not recommended (discouraged, rationale if done):
- "The system SHOULD NOT use recursion." (SIL 3+ constraint)

**MAY** = Optional (discretionary, nice-to-have):
- "The system MAY provide a diagnostic interface for maintenance."

**WILL** = Statement of fact (not a requirement, describes external behavior):
- "The operator WILL provide input via touchscreen." (describes user action)

**Common Mistakes**:
- ❌ "The system must..." → Use "The system SHALL..."
- ❌ "The system will..." → Clarify: Is this mandatory (SHALL) or external fact (WILL)?
- ❌ "The system should..." → Is this HR (SHOULD) or mandatory (SHALL)?
- ❌ "Quickly", "reliable", "efficient" → Not measurable, specify quantitatively

**Resource**: `resources/shall-should-may.md`

#### 3.3 Add C Language Implementation Details
- [ ] For each requirement, specify C constraints:

**Data Types** (use fixed-width types):
```
REQ-FUNC-010: Speed Variable Type
  The current speed SHALL be stored in a uint16_t variable with
  range [0, 300] representing speed in km/h.
  
  Type: uint16_t
  Range: [0, 300] km/h
  Resolution: 1 km/h
```

**Memory Allocation** (static only for SIL 2+):
```
REQ-CONS-020: Static Memory Allocation
  All data structures SHALL use static memory allocation.
  Dynamic memory allocation (malloc, calloc, realloc, free) SHALL NOT be used.
  
  Rationale: Prevent memory leaks and fragmentation (SIL 3 constraint).
  SIL: 3
```

**Error Handling** (return codes):
```
REQ-FUNC-030: Error Return Codes
  All functions that can fail SHALL return an error_t enumeration with
  the following values:
  - SUCCESS (0x00): Operation successful
  - ERROR_TIMEOUT (0x01): Communication timeout
  - ERROR_OUT_OF_RANGE (0x02): Value out of acceptable range
  - ERROR_CRC (0x03): Checksum validation failed
  - ERROR_INVALID (0xFF): Invalid input parameter
  
  Type: error_t (uint8_t enumeration)
```

**Timing** (real-time constraints):
```
REQ-PERF-040: Sensor Read Response Time
  The system SHALL complete a sensor read operation within 10 milliseconds
  from initiation to data availability.
  
  Measurement: Worst-Case Execution Time (WCET)
  Verification: Timing analysis + hardware timing measurement
```

---

### 4. Consistency and Completeness Analysis

**Objective**: Ensure requirements set is internally consistent and complete

#### 4.1 Consistency Checks
- [ ] **Terminological consistency**: Same terms used throughout
  - Create glossary of terms
  - Ensure consistent usage
  - No synonyms (e.g., "speed" vs "velocity" – pick one)

- [ ] **No conflicting requirements**:
  - Check for contradictions
  - Example conflict:
    - REQ-001: "Response time SHALL be ≤ 50ms"
    - REQ-002: "Response time SHALL be ≥ 100ms"
    → CONFLICT! Resolve with stakeholders

- [ ] **Consistent units**: All requirements use same units
  - Speed: km/h (not mix of km/h and m/s)
  - Time: milliseconds (not mix of ms, s, μs)
  - Memory: bytes (not mix of bytes, KB, bits)

- [ ] **Consistent levels of abstraction**: Requirements at similar detail level
  - Don't mix high-level ("The system shall control speed") with low-level ("Variable shall be uint16_t")
  - Use hierarchical decomposition to organize levels

#### 4.2 Completeness Checks
- [ ] **All system requirements covered**:
  - For each system requirement, at least one software requirement exists
  - Traceability matrix: System Req → Software Req (100% for SIL 3+)

- [ ] **All hazards mitigated**:
  - For each hazard in Hazard Log, mitigating requirements exist
  - Traceability matrix: Hazard → Safety Requirements

- [ ] **All interfaces specified**:
  - Hardware interfaces (sensors, actuators, peripherals)
  - Software interfaces (APIs, function calls)
  - Communication interfaces (CAN, SPI, UART, Ethernet)
  - User interfaces (displays, buttons, touchscreens)

- [ ] **All quality attributes specified**:
  - Performance (timing, throughput, latency)
  - Reliability (MTBF, fault tolerance)
  - Maintainability (diagnostics, logging)
  - Portability (platform independence, if applicable)

- [ ] **All constraints specified**:
  - Programming language (C, MISRA C:2012)
  - Coding standards (MISRA C, project-specific)
  - Hardware constraints (memory, CPU, peripherals)
  - Regulatory constraints (EN 50128, national regulations)

- [ ] **No TBDs (To Be Determined)**:
  - All placeholders resolved
  - All unknowns clarified with stakeholders

**Tool**: `tools/completeness-checker.py`

---

### 5. Traceability Analysis

**Objective**: Establish and verify traceability links

**EN 50128 Requirement**: Traceability is MANDATORY for SIL 3-4 (Table A.9)

#### 5.1 Backward Traceability (Sources)
- [ ] For each software requirement, identify source:
  - System requirement (SYSTEM-REQ-XXX → REQ-XXX-XXX)
  - Hazard (HAZARD-XXX → REQ-SAFE-XXX)
  - Stakeholder need (STAKEHOLDER-XXX → REQ-XXX-XXX)
  - Standard/regulation (EN 50128 Section X.Y → REQ-CONS-XXX)

**Example Traceability Matrix** (backward):
| Software Requirement | Source Type | Source ID | Source Description |
|----------------------|-------------|-----------|-------------------|
| REQ-FUNC-001 | System Req | SYS-001 | Speed monitoring system |
| REQ-SAFE-010 | Hazard | HAZ-005 | Overspeed condition |
| REQ-INTF-020 | Hardware | HW-SPEC-001 | Speed sensor interface |
| REQ-CONS-030 | Standard | EN 50128 7.4.4.3 | No dynamic allocation (SIL 2+) |

#### 5.2 Forward Traceability (Targets)
- [ ] For each software requirement, identify target:
  - Design element (REQ-XXX-XXX → DESIGN-COMP-XXX)
  - Test case (REQ-XXX-XXX → TEST-CASE-XXX)
  - Code module (REQ-XXX-XXX → MODULE.c)

**Example Traceability Matrix** (forward):
| Software Requirement | Design Element | Test Case | Code Module |
|----------------------|----------------|-----------|-------------|
| REQ-FUNC-001 | DESIGN-SENSOR-001 | TC-001, TC-002 | sensor.c |
| REQ-SAFE-010 | DESIGN-SAFETY-010 | TC-100, TC-101, TC-102 | safety_monitor.c |

**Note**: Full forward traceability established in later phases (design, test, implementation)

#### 5.3 Traceability Verification
- [ ] **Completeness**:
  - All system requirements have ≥1 software requirement (backward)
  - All software requirements have ≥1 test case (forward - verified in test phase)
  - 100% coverage for SIL 3-4 (MANDATORY)

- [ ] **Correctness**:
  - All traceability links valid (referenced items exist)
  - No broken links
  - No orphan requirements (no source or no target)

**Tool**: `workspace.py trace validate --phase requirements`

**Workflow**: `traceability-management.md`

---

### 6. Requirements Documentation

**Objective**: Create formal Software Requirements Specification (SRS) document

#### 6.1 Organize Requirements
- [ ] Group by category:
  1. Functional Requirements
  2. Performance Requirements
  3. Interface Requirements
  4. Safety Requirements
  5. Quality Requirements
  6. Constraints

- [ ] Within each category, organize by subsystem or module

#### 6.2 Document Requirements
- [ ] Use SRS template: `templates/Software-Requirements-Specification-template.md`
- [ ] For each requirement, include:
  - Unique ID (REQ-XXX-NNN)
  - Title (short description)
  - Description (SHALL/SHOULD/MAY statement)
  - Rationale (why requirement exists)
  - SIL level (0, 1, 2, 3, 4)
  - Priority (M, HR, R)
  - Source (system req, hazard, stakeholder, standard)
  - Verification method (Test, Analysis, Inspection, Demonstration)
  - Acceptance criteria (measurable, testable)
  - Dependencies (other requirements)

**Example**:
```markdown
### REQ-SAFE-010: Overspeed Detection Time

**Type**: Safety Requirement
**SIL**: 4
**Priority**: Mandatory (M)
**Source**: HAZ-005 (Overspeed hazard)

**Description**:
The speed monitoring system SHALL detect when the current speed exceeds
the maximum safe speed limit within 100 milliseconds of the exceedance
occurring.

**Rationale**:
Rapid detection of overspeed condition is critical for timely activation
of emergency braking to prevent collision or derailment.

**Acceptance Criteria**:
1. Detection latency measured ≤ 100 milliseconds in all test scenarios
2. No false negatives (all overspeed conditions detected)
3. False positive rate < 0.001% (1 per 100,000 samples)

**Dependencies**:
- REQ-FUNC-001: Speed sensor reading (must have valid speed data)
- REQ-SAFE-011: Emergency brake activation (triggered by detection)

**Verification Method**: Test (timing measurement with hardware timing analyzer)

**Traceability**:
- Backward: HAZ-005 (Overspeed hazard - Catastrophic severity)
- Forward: TC-SAFE-010-001, TC-SAFE-010-002, TC-SAFE-010-003
```

#### 6.3 Create Traceability Matrices
- [ ] Include in SRS document (Section 8):
  - System Requirements → Software Requirements (backward)
  - Hazards → Safety Requirements (backward)
  - Software Requirements → Test Cases (forward - reference only)

**Format**: CSV or Markdown table

#### 6.4 Add Supporting Information
- [ ] Glossary of terms
- [ ] List of abbreviations
- [ ] References (system requirements, standards, regulations)
- [ ] Assumptions and constraints
- [ ] Revision history

**Workflow**: `requirements-specification.md`

---

### 7. Requirements Review and Validation

**Objective**: Verify requirements quality before approval

#### 7.1 Self-Review
- [ ] REQ engineer reviews own work
- [ ] Use checklist: `resources/requirement-quality-checklist.md`
- [ ] Fix identified issues

#### 7.2 Peer Review
- [ ] Another REQ engineer reviews (if available)
- [ ] Focus on:
  - Quality attributes (unambiguous, testable, etc.)
  - Completeness (all sources covered)
  - Consistency (no conflicts)
  - Traceability (all links valid)

#### 7.3 Quality Assurance Review
- [ ] Submit to QUA agent
- [ ] QUA verifies:
  - Document template compliance
  - Requirements quality standards
  - SQAP compliance
- [ ] Address QUA findings
- [ ] Obtain QUA approval

#### 7.4 Verification Review (SIL 3-4 Independent)
- [ ] Submit to VER agent
- [ ] VER verifies:
  - All requirements testable
  - Traceability complete (100% for SIL 3+)
  - SIL assignments justified
  - Verification methods defined
  - EN 50128 techniques applied
- [ ] Address VER findings
- [ ] Obtain VER approval

**EN 50128**: Independent verification MANDATORY for SIL 3-4 (Section 6.2)

---

## SIL-Specific Requirements

### SIL 0 (Non-Safety)
- Requirements analysis: Basic analysis sufficient
- Decomposition: Recommended but not mandatory
- Traceability: Optional
- Review: Internal review sufficient

### SIL 1-2 (Safety-Related)
- Requirements analysis: Structured approach recommended
- Techniques: At least one technique from Table A.2
- Decomposition: Recommended for complex requirements
- Traceability: Highly recommended
- Review: QUA review recommended

### SIL 3-4 (Safety-Critical)
- Requirements analysis: Structured Methodology HIGHLY RECOMMENDED (D.52)
- Techniques: Multiple techniques HIGHLY RECOMMENDED (Formal Methods, Modelling, Decision Tables)
- Decomposition: MANDATORY for complex requirements
- Traceability: 100% MANDATORY (backward and forward)
- Review: Independent VER review MANDATORY
- Decision tables: HIGHLY RECOMMENDED for complex logic
- Formal specification: HIGHLY RECOMMENDED for safety-critical requirements

---

## Tools and Resources

**Workflows**:
- `requirements-elicitation.md` - Gather requirements from sources
- `requirements-analysis.md` - This workflow
- `requirements-specification.md` - Write formal SRS document
- `traceability-management.md` - Manage traceability matrices

**Resources**:
- `requirement-patterns.md` - Common requirement patterns and examples
- `shall-should-may.md` - Modal verb usage guide (RFC 2119)
- `testability-guidelines.md` - How to make requirements testable
- `requirement-quality-checklist.md` - Quality verification checklist

**Tools**:
- `tools/requirement-validator.py` - Validate requirement format and quality
- `workspace.py trace validate` - Check traceability completeness
- `workspace.py trace check-gaps` - Find missing traceability links
- `tools/completeness-checker.py` - Verify all sources covered

**Templates**:
- `templates/Software-Requirements-Specification-template.md`

---

## Standard References

- **EN 50128:2011 Section 7.2** - Software Requirements Specification
- **EN 50128:2011 Table A.2** - Requirements Specification Techniques
- **EN 50128:2011 Annex D.13** - Decision Tables
- **EN 50128:2011 Annex D.28** - Formal Methods
- **EN 50128:2011 Annex D.52** - Structured Methodology
- **EN 50128:2011 Table A.9** - Traceability (MANDATORY SIL 3-4)
- **RFC 2119** - Key words for Requirement Levels (SHALL, SHOULD, MAY)

---

## Next Steps

After completing requirements analysis:
1. **`traceability-management.md`** - Establish and maintain traceability matrices
2. **`requirements-specification.md`** - Write formal Software Requirements Specification document
3. Submit SRS for QUA review → VER review → VAL approval
4. Create baseline and proceed to design phase
