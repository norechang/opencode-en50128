# Requirements Elicitation Workflow

**Purpose**: Systematically gather and document software requirements from stakeholders, system requirements, and safety analysis.

**EN 50128 Reference**: Section 7.2 Software Requirements

**Role**: Requirements Engineer (REQ)

**Prerequisites**:
- Software Quality Assurance Plan (SQAP) approved (DOC-001)
- Software Configuration Management Plan (SCMP) approved (DOC-003)
- System Requirements available
- Hazard Log available (for safety requirements)

---

## Workflow Steps

### 1. Preparation Phase

**Objective**: Establish foundation for requirements elicitation

#### 1.1 Review Input Documents
- [ ] Read System Requirements Specification
- [ ] Review Hazard Log (safety requirements)
- [ ] Review SQAP (quality requirements, standards)
- [ ] Review SCMP (configuration requirements)
- [ ] Identify all stakeholders

**Deliverable**: Stakeholder list, input document register

#### 1.2 Plan Elicitation Sessions
- [ ] Schedule stakeholder interviews
- [ ] Prepare questionnaires
- [ ] Identify elicitation techniques to use:
  - Interviews (one-on-one or group)
  - Workshops (collaborative sessions)
  - Document analysis (existing specs)
  - Observation (existing system behavior)
  - Prototyping (for unclear requirements)

**Deliverable**: Elicitation plan with schedule

---

### 2. Elicitation Phase

**Objective**: Gather raw requirements from all sources

#### 2.1 System Requirements Analysis
- [ ] For each system requirement:
  - [ ] Identify software-relevant requirements
  - [ ] Decompose high-level system requirements into software requirements
  - [ ] Note traceability link (SYSTEM-REQ-XXX → REQ-XXX-XXX)
  - [ ] Identify any ambiguities or gaps

**Technique**: Structured decomposition (EN 50128 Table A.2, D.52)

**Example**:
```
System Requirement: SYS-001
"The train control system shall maintain speed within ±2 km/h of target speed."

Derived Software Requirements:
- REQ-SPEED-001: Read speed sensor value (interface requirement)
- REQ-SPEED-002: Calculate speed error (functional requirement)
- REQ-SPEED-003: Apply control algorithm (functional requirement)
- REQ-SPEED-004: Output actuator command (interface requirement)
- REQ-SPEED-005: Detect sensor failure (safety requirement)
```

#### 2.2 Hazard Analysis Review (Safety Requirements)
- [ ] For each hazard in Hazard Log:
  - [ ] Identify software mitigations required
  - [ ] Derive safety requirements
  - [ ] Assign SIL level based on hazard severity
  - [ ] Note traceability link (HAZARD-XXX → REQ-SAFE-XXX)

**EN 50128 Reference**: Section 7.1 (Hazard Analysis), Table A.8

**Example**:
```
Hazard: HAZ-005
"Overspeed condition: Train exceeds safe speed limit"
Severity: Catastrophic (SIL 4)

Derived Safety Requirements:
- REQ-SAFE-010: Detect speed exceeding limit within 100ms (SIL 4)
- REQ-SAFE-011: Apply emergency brake within 200ms of detection (SIL 4)
- REQ-SAFE-012: Enter safe state and log event (SIL 4)
- REQ-SAFE-013: Require operator confirmation before resuming (SIL 4)
```

#### 2.3 Stakeholder Interviews
- [ ] Conduct interviews with:
  - System engineers
  - Domain experts (railway operations)
  - Safety engineers
  - Hardware engineers (for interfaces)
  - Test engineers (testability)
  - Maintenance engineers (maintainability)

- [ ] For each interview:
  - [ ] Ask open-ended questions
  - [ ] Document functional needs
  - [ ] Document performance needs
  - [ ] Document interface needs
  - [ ] Document quality attributes
  - [ ] Clarify ambiguities
  - [ ] Capture rationale

**Interview Questions Template**:
```
1. What is the primary function this software must perform?
2. What are the inputs? (data types, ranges, sources)
3. What are the outputs? (data types, ranges, destinations)
4. What are the timing requirements? (response time, throughput)
5. What are the error conditions? (how should system respond?)
6. What are the safety implications? (hazards, mitigations)
7. What are the dependencies? (other systems, hardware)
8. How will this be tested? (testability considerations)
```

#### 2.4 Document Analysis
- [ ] Analyze existing documentation:
  - Previous system versions (legacy requirements)
  - Industry standards (IEC 62278, EN 50126, etc.)
  - Railway regulations
  - Customer specifications
  - Interface control documents

- [ ] Extract requirements and note sources

#### 2.5 C Language Constraints Analysis
- [ ] For each requirement, consider C implementation:
  - [ ] Data types: Identify fixed-width types needed (uint8_t, uint16_t, etc.)
  - [ ] Memory: Static allocation sufficient? (mandatory SIL 2+)
  - [ ] Timing: Real-time constraints achievable in C?
  - [ ] Interfaces: Hardware register access, communication protocols
  - [ ] Error handling: Return codes, error enumerations
  - [ ] Safety: Defensive programming patterns needed

**Example**:
```
Elicited Requirement (raw):
"The system shall read the speed sensor."

With C Constraints:
REQ-INTERFACE-001: Speed Sensor Data Acquisition

The system SHALL read the speed sensor value via SPI interface and store
the result in a uint16_t variable representing speed in km/h with range [0, 300].

Data type: uint16_t
Range: [0, 300] km/h
Interface: SPI bus, address 0x4000
Timing: Maximum read time 10 milliseconds
Error handling: Return ERROR_TIMEOUT if read exceeds 10ms
                 Return ERROR_OUT_OF_RANGE if value > 300

SIL Level: 3
Rationale: Speed data is safety-critical input for train control.
```

---

### 3. Documentation Phase

**Objective**: Organize raw requirements into structured format

#### 3.1 Create Requirements Register
- [ ] Create master requirements list (spreadsheet or database)
- [ ] Columns:
  - Requirement ID (unique)
  - Title (short description)
  - Type (Functional, Performance, Interface, Safety, Quality, Constraint)
  - Description (detailed statement using SHALL/SHOULD/MAY)
  - Rationale (why requirement exists)
  - Source (stakeholder, system req, hazard, standard)
  - SIL Level (0, 1, 2, 3, 4)
  - Priority (Mandatory, Highly Recommended, Recommended)
  - Verification Method (Test, Analysis, Inspection, Demonstration)
  - Status (Draft, Under Review, Approved, Implemented)

**Tool**: Spreadsheet, database, or requirements management tool

#### 3.2 Assign Unique IDs
- [ ] Follow ID format: `REQ-<MODULE>-<NNN>`
  - MODULE: Component or subsystem (e.g., SPEED, BRAKE, DOOR, COMM)
  - NNN: Sequential number (001, 002, ...)

**Examples**:
- `REQ-SPEED-001`: Speed sensor reading
- `REQ-BRAKE-010`: Emergency brake activation
- `REQ-DOOR-005`: Door lock status check
- `REQ-COMM-020`: CAN bus message transmission

#### 3.3 Write Requirements Statements
- [ ] For each requirement:
  - [ ] Use modal verbs correctly:
    - **SHALL**: Mandatory requirement (must be implemented)
    - **SHOULD**: Highly recommended (strong preference, rationale needed if not implemented)
    - **MAY**: Optional (discretionary, nice-to-have)
    - **WILL**: Statement of fact (not a requirement)
  - [ ] Make unambiguous (single interpretation)
  - [ ] Make testable (verifiable by objective criteria)
  - [ ] Make atomic (one requirement per ID)
  - [ ] Make implementation-free (what, not how)

**Good Example**:
```
REQ-BRAKE-010: Emergency Brake Activation Time

The braking system SHALL activate the emergency brake within 200 milliseconds
of receiving the emergency brake command signal.

Rationale: Rapid braking response is critical for collision avoidance.
SIL Level: 4
Verification Method: Test (timing measurement with oscilloscope)
```

**Bad Example**:
```
REQ-BRAKE-BAD: The system should brake quickly when needed.

Problems:
- "should" vs "SHALL" (ambiguous priority)
- "quickly" (not measurable)
- "when needed" (not specific)
- Not testable
```

#### 3.4 Classify Requirements
- [ ] Assign type to each requirement:
  - **Functional**: What the system does
  - **Performance**: Timing, throughput, resource usage
  - **Interface**: Hardware/software/communication interfaces
  - **Safety**: Safety-critical functions, fault handling
  - **Quality**: Reliability, maintainability, portability
  - **Constraint**: Design/implementation/regulatory constraints

#### 3.5 Assign SIL Levels
- [ ] For each requirement, determine SIL level:
  - Trace to hazard (from Hazard Log)
  - Use hazard severity as basis
  - Safety functions inherit SIL from hazard
  - Supporting functions may have lower SIL

**SIL Assignment Rules**:
- SIL 4: Hazard severity = Catastrophic (death of many people)
- SIL 3: Hazard severity = Critical (death of individuals)
- SIL 2: Hazard severity = Serious (serious injuries)
- SIL 1: Hazard severity = Minor (minor injuries)
- SIL 0: Non-safety related

**Example**:
```
Hazard: HAZ-005 (Overspeed) → Severity: Catastrophic → SIL 4

Requirements:
- REQ-SAFE-010: Detect overspeed (SIL 4 - direct safety function)
- REQ-SAFE-011: Apply emergency brake (SIL 4 - direct safety function)
- REQ-SPEED-001: Read speed sensor (SIL 4 - provides data for safety function)
- REQ-DISPLAY-020: Display speed to operator (SIL 1 - informational only)
```

---

### 4. Validation Phase

**Objective**: Ensure requirements are complete, correct, and consistent

#### 4.1 Requirements Quality Check
- [ ] For each requirement, verify:
  - [ ] Unambiguous (single interpretation)
  - [ ] Testable (can be verified objectively)
  - [ ] Clear (easily understood)
  - [ ] Correct (accurately reflects need)
  - [ ] Feasible (technically and economically possible)
  - [ ] Atomic (cannot be decomposed further)
  - [ ] Necessary (essential capability)
  - [ ] Implementation-free (does not prescribe solution)

**Use Checklist**: `resources/requirement-quality-checklist.md`

#### 4.2 Completeness Check
- [ ] All system requirements addressed
- [ ] All hazards mitigated
- [ ] All interfaces specified
- [ ] All quality attributes specified
- [ ] All constraints identified
- [ ] No TBDs (To Be Determined) remaining

#### 4.3 Consistency Check
- [ ] No conflicting requirements
- [ ] Terminology consistent
- [ ] All requirement IDs unique
- [ ] All references valid

#### 4.4 Traceability Check
- [ ] All requirements trace to source (system req, hazard, stakeholder)
- [ ] All system requirements covered by at least one software requirement
- [ ] All hazards mitigated by at least one safety requirement

**Tool**: `workspace.py trace validate --phase requirements`

---

### 5. Review and Approval Phase

**Objective**: Obtain stakeholder consensus and formal approval

#### 5.1 Internal Review
- [ ] Self-review by REQ engineer
- [ ] Peer review by another REQ engineer (if available)
- [ ] Fix identified issues

#### 5.2 Stakeholder Review
- [ ] Distribute requirements to stakeholders
- [ ] Conduct review meeting
- [ ] Collect feedback and comments
- [ ] Track issues in issue log
- [ ] Resolve or defer issues
- [ ] Update requirements based on feedback

#### 5.3 Quality Assurance Review
- [ ] Submit to QUA agent for review
- [ ] QUA checks:
  - Requirements quality (checklist)
  - Compliance with SQAP
  - Document template compliance
- [ ] Address QUA findings
- [ ] Obtain QUA approval

#### 5.4 Verification Review (SIL 3-4 Independent Review)
- [ ] Submit to VER agent for independent verification
- [ ] VER checks:
  - All requirements testable
  - Traceability complete
  - SIL assignments justified
  - Verification methods defined
- [ ] Address VER findings
- [ ] Obtain VER approval

**EN 50128 Requirement**: Independent verification mandatory for SIL 3-4

#### 5.5 Final Approval
- [ ] Obtain approval from:
  - Requirements Engineer (REQ) - Author
  - Verifier (VER) - First check
  - Validator (VAL) - Second check
  - Project Manager (PM) - Overall approval

- [ ] Approvals recorded in document header (APPROVALS table)

---

### 6. Baseline and Release Phase

**Objective**: Place approved requirements under configuration management

#### 6.1 Create Baseline
- [ ] Assign version number (e.g., v1.0)
- [ ] Tag in version control (Git)
- [ ] Notify Configuration Manager (CM)
- [ ] CM creates baseline: `SRS-v1.0`

**Tool**: `tools/workspace.py baseline create`

#### 6.2 Distribute Document
- [ ] Publish to project repository
- [ ] Notify downstream roles:
  - Designer (DES) - for architecture
  - Tester (TST) - for test planning
  - Safety Engineer (SAF) - for safety case
  - Validator (VAL) - for validation planning

---

## SIL-Specific Requirements

### SIL 0 (Non-Safety)
- Requirements elicitation: Basic interviews and document analysis sufficient
- Techniques: Optional (use as needed)
- Traceability: Recommended but not mandatory
- Review: Internal review sufficient

### SIL 1-2 (Safety-Related)
- Requirements elicitation: Structured methodology recommended (Table A.2)
- Techniques: At least one technique from Table A.2 recommended
- Traceability: Highly recommended to system requirements
- Review: QUA review recommended
- MISRA C considerations: Mandatory for SIL 2+

### SIL 3-4 (Safety-Critical)
- Requirements elicitation: Structured methodology HIGHLY RECOMMENDED (Table A.2)
- Techniques: Formal Methods, Modelling, Decision Tables HIGHLY RECOMMENDED
- Traceability: 100% MANDATORY to system requirements
- Review: Independent VER review MANDATORY
- Formal specification: Highly recommended for safety-critical requirements
- C constraints: All safety requirements must consider implementation constraints

---

## Common Pitfalls

### 1. Ambiguous Requirements
**Problem**: "The system shall respond quickly."
**Solution**: "The system SHALL respond within 100 milliseconds."

### 2. Implementation Prescription
**Problem**: "The system shall use a linked list to store data."
**Solution**: "The system SHALL store up to 100 sensor readings."

### 3. Multiple Requirements in One
**Problem**: "The system shall read sensor data and validate the range."
**Solution**: Split into:
- REQ-001: "The system SHALL read sensor data via SPI interface."
- REQ-002: "The system SHALL validate sensor data is within range [0, 300]."

### 4. Untestable Requirements
**Problem**: "The system shall be reliable."
**Solution**: "The system SHALL have MTBF ≥ 10,000 hours."

### 5. Missing SIL Assignment
**Problem**: Requirement without SIL level
**Solution**: Assign SIL based on hazard analysis traceability

---

## Tools and Templates

**Workflows**:
- `requirements-elicitation.md` (this file)
- `requirements-analysis.md` - Analyze and decompose requirements
- `requirements-specification.md` - Write Software Requirements Specification
- `traceability-management.md` - Manage traceability matrices

**Resources**:
- `requirement-patterns.md` - Common requirement patterns
- `shall-should-may.md` - Modal verb usage (RFC 2119)
- `testability-guidelines.md` - How to make requirements testable
- `requirement-quality-checklist.md` - Quality verification checklist

**Tools**:
- `tools/requirement-validator.py` - Validate requirement format and quality
- `workspace.py trace validate` - Check traceability completeness
- `workspace.py trace check-gaps` - Find missing traceability links

**Templates**:
- `templates/Software-Requirements-Specification-template.md` - SRS template

---

## Standard References

- **EN 50128:2011 Section 7.2** - Software Requirements Specification
- **EN 50128:2011 Table A.2** - Requirements Specification Techniques
- **EN 50128:2011 Annex D.28** - Formal Methods
- **EN 50128:2011 Annex D.52** - Structured Methodology
- **EN 50126:2017** - RAMS Requirements
- **RFC 2119** - Key words for use in RFCs to Indicate Requirement Levels

---

## Next Workflow

After completing requirements elicitation, proceed to:
- **`requirements-analysis.md`** - Analyze and refine requirements
- **`traceability-management.md`** - Establish traceability matrices
- **`requirements-specification.md`** - Write formal Software Requirements Specification document
