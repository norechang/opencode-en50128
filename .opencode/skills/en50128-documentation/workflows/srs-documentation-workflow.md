# Software Requirements Specification (SRS) Documentation Workflow

**Workflow ID**: DOC-WF-001  
**EN 50128 Reference**: Section 7.2 (Software Requirements)  
**Last Updated**: 2026-03-14  
**Version**: 1.0

---

## Table of Contents

1. [Overview](#1-overview)
2. [EN 50128 SRS Requirements](#2-en-50128-srs-requirements)
3. [SRS Document Structure](#3-srs-document-structure)
4. [Requirements Elicitation and Documentation](#4-requirements-elicitation-and-documentation)
5. [SIL-Specific Content Requirements](#5-sil-specific-content-requirements)
6. [Requirements Traceability](#6-requirements-traceability)
7. [SRS Review and Approval](#7-srs-review-and-approval)
8. [Template Validation](#8-template-validation)
9. [Tool Integration](#9-tool-integration)
10. [Automation Scripts](#10-automation-scripts)
11. [Example Scenarios](#11-example-scenarios)

---

## 1. Overview

### 1.1 Purpose

This workflow provides comprehensive guidance for creating, reviewing, and approving Software Requirements Specification (SRS) documents in compliance with EN 50128:2011 Section 7.2. The SRS is the **primary deliverable of Phase 2 (Software Requirements)** and forms the foundation for all subsequent development activities.

### 1.2 Scope

**This workflow covers**:
- EN 50128 Section 7.2 mandatory requirements for SRS
- SRS document structure and content guidance
- Requirements elicitation techniques (Table A.2)
- SIL-specific content requirements (SIL 0-4)
- Requirements traceability (system → software requirements)
- SRS review and approval workflows (SIL-dependent)
- Template validation and compliance checking
- Tool integration (workspace.py wf, workspace.py trace)
- Automation scripts for validation and extraction

**Out of Scope**:
- Software Architecture Specification (see SAS/SDS workflow)
- Test specifications (see Test Documentation workflow)
- Configuration management (see Configuration skill)

### 1.3 Key EN 50128 Requirements

| Requirement | EN 50128 Reference | Mandatory For |
|-------------|-------------------|---------------|
| **SRS shall be complete, clear, precise, unequivocal** | Section 7.2.4.4 | All SIL levels |
| **SRS shall be verifiable and testable** | Section 7.2.4.4 | All SIL levels |
| **SRS shall be traceable to input documents** | Section 7.2.4.4 | All SIL levels |
| **SIL level assigned to each requirement** | Section 7.2.4.3 | All SIL levels |
| **Safety functions clearly identified** | Section 7.2.4.13 | All SIL levels |
| **Requirements specification techniques applied** | Section 7.2.4.15, Table A.2 | All SIL levels (SIL-specific) |
| **Independent review** | Table A.5, Section 5 | **MANDATORY SIL 3-4** |

### 1.4 Workflow Roles

| Role | Responsibility | Independence Required |
|------|----------------|----------------------|
| **Requirements Engineer (REQ)** | Create SRS, elicit requirements, maintain traceability | No |
| **Safety Engineer (SAF)** | Provide safety requirements, assign SIL levels | No (but separate from REQ) |
| **Quality Assurance (QUA)** | Template compliance check, process compliance | No |
| **Verifier (VER)** | Technical review of SRS content | **Yes (SIL 3-4)** |
| **Validator (VAL)** | Approve SRS for correctness and completeness | **Yes (SIL 3-4)** |
| **Project Manager (PM)** | Approve SRS baseline | No |

---

## 2. EN 50128 SRS Requirements

### 2.1 Section 7.2 Key Requirements

EN 50128:2011 Section 7.2 defines the mandatory requirements for Software Requirements Specification.

#### 2.1.1 Input Documents (Section 7.2.2)

The SRS SHALL be based on the following input documents:

1. **System Requirements Specification** - System-level functional and non-functional requirements
2. **System Safety Requirements Specification** - System-level safety requirements, hazard analysis
3. **System Architecture Description** - System context, hardware/software allocation
4. **External Interface Specifications** - SW/SW interfaces, SW/HW interfaces
5. **Software Quality Assurance Plan (SQAP)** - Quality requirements, process constraints
6. **Software Validation Plan (SVaP)** - Validation criteria, acceptance criteria

#### 2.1.2 Output Documents (Section 7.2.3)

Phase 2 (Software Requirements) SHALL produce:

1. **Software Requirements Specification (SRS)** - Complete software requirements (THIS WORKFLOW)
2. **Overall Software Test Specification** - System test specification (see Test Documentation workflow)
3. **Software Requirements Verification Report** - Verification of SRS (VER role, see Verification skill)

#### 2.1.3 Required Properties (Section 7.2.4.2)

The SRS SHALL express the following properties per ISO/IEC 9126:

| Property | Description | Examples |
|----------|-------------|----------|
| **Functionality** | What the software does | Functional requirements, capacity, response time |
| **Robustness** | Error handling, fault tolerance | Input validation, error codes, recovery |
| **Maintainability** | Code structure, documentation | Modular design, traceability, comments |
| **Safety** | Safety functions, SIL levels | Safety requirements, hazard mitigation |
| **Efficiency** | Performance, resource usage | CPU utilization, memory footprint, timing |
| **Usability** | User interfaces, ease of use | HMI requirements, diagnostics |
| **Portability** | Platform independence | Fixed-width types, abstraction layers |

#### 2.1.4 Quality Criteria (Section 7.2.4.4)

The SRS SHALL be:

- **Complete**: All system requirements allocated to software are captured
- **Clear**: Unambiguous language (SHALL/SHOULD/MAY keywords)
- **Precise**: Quantitative criteria where possible (timing, accuracy, ranges)
- **Unequivocal**: Single interpretation only
- **Verifiable**: Each requirement can be tested or analyzed
- **Testable**: Acceptance criteria defined for each requirement
- **Maintainable**: Structured, traceable, under configuration control
- **Feasible**: Achievable within constraints (C language, platform, time, budget)

#### 2.1.5 Interface Requirements (Section 7.2.4.6)

The SRS SHALL identify and document **all interfaces**:

- Hardware interfaces (sensors, actuators, processors)
- Software interfaces (external systems, libraries, RTOS)
- Communication interfaces (CAN, Ethernet, serial)
- User interfaces (HMI, displays, diagnostics)

#### 2.1.6 Safety Requirements (Section 7.2.4.13, 7.2.4.14)

The SRS SHALL:

- Clearly identify all **safety functions** (requirements related to achieving safety)
- Clearly identify all **non-safety functions** (requirements NOT related to safety)
- Assign **SIL level** to each safety function (per EN 50126 hazard analysis)
- Trace safety requirements to hazards in Hazard Log

### 2.2 Table A.2 Requirements Specification Techniques

EN 50128 Table A.2 defines techniques for requirements specification. The SRS SHALL apply a justified combination of techniques based on SIL level.

| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Description | Reference |
|-----------|-------|---------|---------|-------------|-----------|
| **Structured Methodology** | R | R | **HR** | Systematic approach to requirements elicitation and documentation | D.52 |
| **Modelling** | R | R | **HR** | Requirements models (state machines, data flow diagrams) | Table A.17 |
| **Decision Tables** | R | R | **HR** | Tabular representation of complex logic | D.13 |
| **Formal Methods** | - | R | **HR** | Mathematical specification (Z, VDM, B) | D.28 |
| **Hierarchical Structures** | R | R | R | Decomposition of requirements into levels | - |
| **Prototyping** | R | R | R | Early validation of requirements | - |

**Key**:
- **M** = Mandatory (must use)
- **HR** = Highly Recommended (rationale required if not used)
- **R** = Recommended (should consider)
- **-** = No recommendation

**Typical SIL 3-4 Combination**:
- **MANDATORY**: Structured Methodology (HR)
- **HIGHLY RECOMMENDED**: Modelling (state machines for control logic), Decision Tables (for complex conditions)
- **OPTIONAL**: Formal Methods (if mathematical proof required for critical safety functions)

### 2.3 Traceability Requirements (Section 7.2.4.4)

The SRS SHALL be **traceable back to all input documents** (Section 7.2.4.4).

**Traceability Matrix (RTM) SHALL capture**:

```
System Requirement → Software Requirement → Design → Code → Test
```

**Example**:
```
SYS-REQ-001 (System: Emergency stop within 100ms)
  → REQ-SAFE-010 (Software: Emergency stop response)
    → MOD-SAFE (Architecture: Safety Module)
      → safety.c:emergency_stop_handler() (Code)
        → TC-UNIT-SAFE-010, TC-INT-SAFE-010, TC-SYS-SAFE-010 (Tests)
```

**Traceability is MANDATORY for SIL 3-4** (EN 50128 Table A.9, Technique 7).

---

## 3. SRS Document Structure

### 3.1 Standard SRS Template

The SRS SHALL follow the standard template located at:

```
.opencode/skills/en50128-requirements/templates/Software-Requirements-Specification-template.md
```

**Template Structure** (787 lines):

```markdown
# Software Requirements Specification (SRS)

## STANDARD HEADER
- Document ID: DOC-SRS-YYYY-NNN
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

## 2. GENERAL DESCRIPTION
  2.1 System Context
  2.2 System Functions (High-Level)
  2.3 User Characteristics
  2.4 Constraints
  2.5 Assumptions and Dependencies

## 3. SOFTWARE REQUIREMENTS
  3.1 Functional Requirements
    3.1.1 [Function Group 1]
      REQ-FUNC-001: [Requirement Title]
      REQ-FUNC-002: [Requirement Title]
      ...
    3.1.2 [Function Group 2]
      REQ-FUNC-010: [Requirement Title]
      ...
  3.2 Performance Requirements
    REQ-PERF-001: [Performance requirement]
    ...
  3.3 Interface Requirements
    3.3.1 Hardware Interfaces
    3.3.2 Software Interfaces
    3.3.3 User Interfaces
  3.4 Safety Requirements
    REQ-SAFE-001: [Safety requirement]
    ...
  3.5 C Language Implementation Constraints
    REQ-IMPL-001: MISRA C Compliance
    REQ-IMPL-002: Fixed-Width Integer Types
    REQ-IMPL-003: Static Memory Allocation
    REQ-IMPL-004: No Recursion
    REQ-IMPL-005: Cyclomatic Complexity Limit
    REQ-IMPL-006: Defensive Programming
    REQ-IMPL-007: Error Handling Strategy
    ...

## 4. VERIFICATION AND TRACEABILITY
  4.1 Verification Methods
  4.2 Requirements Traceability Matrix (RTM)
  4.3 Requirements Quality Checklist

## 5. REQUIREMENTS SUMMARY
  5.1 Requirements Count by Category
  5.2 Requirements Count by SIL Level

## 6. COMPLIANCE MATRIX
  6.1 EN 50128 Section 7.2 Compliance
  6.2 EN 50128 Table A.2 Compliance

## 7. REFERENCES
  7.1 Normative References
  7.2 Project References

## APPENDICES
  Appendix A: Requirements Template
  Appendix B: Glossary

## DOCUMENT HISTORY
```

### 3.2 Mandatory Sections for All SIL Levels

| Section | Required Content | Verification |
|---------|------------------|--------------|
| **Standard Header** | Document ID, Version, SIL Level, Author, Reviewer, Approver, Status | QUA template check |
| **Document Control** | Version history with all changes logged | CM audit |
| **Approvals** | SIL-specific signatures (see Section 5.2) | QUA template check |
| **1. Introduction** | Purpose, scope, SIL classification, definitions, references | QUA review |
| **2. General Description** | System context, functions, constraints, assumptions | Technical review |
| **3. Software Requirements** | All requirements (functional, performance, interface, safety, implementation) | VER technical review |
| **4. Verification and Traceability** | Verification methods, RTM, quality checklist | VER verification |
| **5. Requirements Summary** | Count by category, count by SIL level | Automated validation |
| **6. Compliance Matrix** | EN 50128 Section 7.2 compliance, Table A.2 compliance | VER verification |
| **7. References** | Normative and project references | QUA review |

### 3.3 SIL-Specific Sections

| SIL Level | Additional Sections | Rationale |
|-----------|---------------------|-----------|
| **SIL 0-1** | Standard sections only | Basic documentation |
| **SIL 2** | 3.5 C Language Implementation Constraints (MISRA C mandatory) | Code quality enforcement |
| **SIL 3-4** | 3.4 Safety Requirements (expanded), 4.2 RTM (mandatory), 6.2 Table A.2 Compliance (detailed) | Safety criticality, traceability |

### 3.4 Document ID Format

**Format**: `DOC-SRS-YYYY-NNN`

**Examples**:
- `DOC-SRS-2026-001` - First SRS in 2026
- `DOC-SRS-2026-002` - Second SRS in 2026 (different project or major revision)

**Version Format**: `MAJOR.MINOR`
- `0.1`, `0.2`, ... - Draft versions
- `1.0` - First approved baseline
- `1.1`, `1.2`, ... - Minor updates (clarifications, corrections)
- `2.0` - Major revision (significant requirement changes, requires CCB approval)

---

## 4. Requirements Elicitation and Documentation

### 4.1 Requirements Elicitation Techniques

#### 4.1.1 Stakeholder Interviews

**Purpose**: Gather requirements from project stakeholders (customer, users, safety engineers, system engineers).

**Process**:
1. Identify stakeholders (customer, operators, maintainers, safety authority)
2. Prepare interview questions (functional needs, safety concerns, performance expectations)
3. Conduct interviews (document discussions, record audio if permitted)
4. Extract requirements (convert stakeholder needs into formal requirements)
5. Validate with stakeholders (review extracted requirements for accuracy)

**Example Interview Questions**:
- "What is the primary function of this software?"
- "What are the critical safety hazards?"
- "What are the performance requirements (timing, throughput)?"
- "What are the environmental constraints (temperature, EMI)?"
- "What interfaces are required (sensors, actuators, networks)?"

#### 4.1.2 System Requirements Analysis

**Purpose**: Decompose system requirements into software requirements.

**Process**:
1. Read System Requirements Specification (input document)
2. Identify requirements allocated to software (vs. hardware)
3. Decompose system requirements into detailed software requirements
4. Add software-specific requirements (implementation constraints, error handling)
5. Establish traceability (SYS-REQ → SW-REQ)

**Example Decomposition**:
```
SYS-REQ-001: "System shall detect obstacle and stop door movement within 100ms"
  → REQ-FUNC-015: "Software shall read obstacle sensor every 10ms"
  → REQ-FUNC-016: "Software shall detect obstacle condition (sensor = HIGH)"
  → REQ-FUNC-017: "Software shall stop door actuator within 20ms of obstacle detection"
  → REQ-PERF-005: "Obstacle detection latency shall be ≤ 50ms (worst case)"
```

#### 4.1.3 Hazard Analysis Review

**Purpose**: Derive safety requirements from hazard analysis (Hazard Log per EN 50126).

**Process**:
1. Review Hazard Log (provided by Safety Engineer)
2. Identify hazards mitigated by software
3. Create safety requirements for each software-mitigated hazard
4. Assign SIL level based on hazard severity (per EN 50126 risk analysis)
5. Establish traceability (HAZ-ID → REQ-SAFE-ID)

**Example Hazard Mitigation**:
```
HAZ-001: "Doors open during train movement (Risk: High, SIL 4)"
  → REQ-SAFE-001: "Software SHALL lock doors whenever train speed > 5 km/h (SIL 4)"
  → REQ-SAFE-002: "Software SHALL monitor speed from TWO independent sensors (SIL 4)"
  → REQ-SAFE-003: "Software SHALL lock doors if ANY speed sensor reads > 5 km/h (1oo2 voting, SIL 4)"
```

#### 4.1.4 Interface Analysis

**Purpose**: Define all software interfaces (hardware, software, communication, user).

**Process**:
1. Review System Architecture Description (input document)
2. Identify all interfaces where software interacts with external entities
3. Document interface requirements (signal type, timing, protocol, error handling)
4. Create interface control documents (ICD) if needed for complex interfaces

**Interface Categories**:
- **Hardware Interfaces**: Sensors (ADC), actuators (PWM), GPIOs, timers
- **Software Interfaces**: External systems (CAN messages, Ethernet packets), libraries, RTOS APIs
- **Communication Interfaces**: Protocols (CAN, Modbus, Profibus), data formats, timing
- **User Interfaces**: HMI screens, diagnostic displays, maintenance interfaces

### 4.2 Requirements Documentation Best Practices

#### 4.2.1 Requirement Format

Each requirement SHALL follow this standard format:

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

**Requirement Categories**:
- `REQ-FUNC-NNN` - Functional requirements
- `REQ-PERF-NNN` - Performance requirements
- `REQ-IF-HW-NNN` - Hardware interface requirements
- `REQ-IF-SW-NNN` - Software interface requirements
- `REQ-IF-UI-NNN` - User interface requirements
- `REQ-SAFE-NNN` - Safety requirements
- `REQ-IMPL-NNN` - Implementation constraints (C language, MISRA C, etc.)

#### 4.2.2 Keywords (Mandatory for ALL SIL Levels)

Requirements SHALL use the following keywords per RFC 2119:

| Keyword | Meaning | Usage |
|---------|---------|-------|
| **SHALL** | Mandatory requirement (must be implemented) | Safety-critical, essential functionality |
| **SHALL NOT** | Mandatory prohibition (must not be implemented) | Forbidden operations (e.g., "Software SHALL NOT use dynamic memory allocation") |
| **SHOULD** | Recommended requirement (highly desirable) | Best practices, recommended features |
| **SHOULD NOT** | Not recommended (avoid if possible) | Discouraged practices |
| **MAY** | Optional requirement (nice to have) | Convenience features, diagnostics |

**Examples**:
- ✓ CORRECT: "The software **SHALL** process inputs within 50ms"
- ✗ INCORRECT: "The software will process inputs quickly" (vague, no keyword)

#### 4.2.3 Quantitative Criteria (Mandatory SIL 2+)

Requirements SHALL include **quantitative acceptance criteria** where possible:

| Requirement Type | Quantitative Criteria Examples |
|------------------|-------------------------------|
| **Timing** | "SHALL respond within 50ms", "SHALL execute every 100ms" |
| **Accuracy** | "SHALL measure temperature with ±0.5°C accuracy" |
| **Throughput** | "SHALL process 1000 messages per second" |
| **Memory** | "SHALL use ≤ 256 KB RAM", "SHALL use ≤ 512 KB ROM" |
| **CPU** | "SHALL consume ≤ 80% CPU under worst-case load" |
| **Reliability** | "SHALL achieve MTBF ≥ 100,000 hours" |

**Examples**:
- ✓ CORRECT: "Software SHALL update display every 200ms ±10ms"
- ✗ INCORRECT: "Software SHALL update display regularly" (not quantitative)

#### 4.2.4 Avoiding Ambiguity

**Ambiguous Phrases to AVOID**:

| Avoid | Problem | Use Instead |
|-------|---------|-------------|
| "quickly", "slowly" | Subjective | Specify exact timing: "within 50ms" |
| "large", "small" | Subjective | Specify exact size: "≤ 1024 bytes" |
| "adequate", "sufficient" | Vague | Define specific criteria: "≥ 95% coverage" |
| "normally", "usually" | Uncertain | Define exact conditions: "when speed > 5 km/h" |
| "and/or" | Ambiguous logic | Specify: "AND" or "OR", not both |
| "etc.", "including" | Incomplete | List all items explicitly |

**Examples**:
- ✗ INCORRECT: "Software shall handle errors adequately"
- ✓ CORRECT: "Software SHALL detect errors within 10ms AND log error code to non-volatile memory AND transition to safe state within 50ms"

### 4.3 C Language Implementation Constraints

For C-based software, the SRS SHALL include implementation constraint requirements (Section 3.5).

#### 4.3.1 MISRA C Compliance (Mandatory SIL 2+)

```markdown
**REQ-IMPL-001**: MISRA C Compliance  
**Priority**: High  
**SIL Level**: 2+ (Mandatory)  
**Traceability**: EN 50128 Table A.4

**Description**: All source code SHALL comply with MISRA C:2012 guidelines. Deviations SHALL be documented with rationale and approved by Safety Engineer.

**Acceptance Criteria**: 
- PC-lint Plus static analysis reports 100% compliance
- OR documented deviations ≤ 5% with approved rationale

**Verification Method**: Static Analysis (PC-lint Plus, Cppcheck)
```

#### 4.3.2 Static Memory Allocation (Mandatory SIL 2+)

```markdown
**REQ-IMPL-003**: Static Memory Allocation  
**Priority**: Critical  
**SIL Level**: 2+ (Mandatory)  
**Traceability**: EN 50128 Table A.4

**Description**: The software SHALL use ONLY static memory allocation. Dynamic memory allocation functions (`malloc`, `calloc`, `realloc`, `free`) SHALL NOT be used.

**Rationale**: Eliminates memory leaks, heap fragmentation, non-deterministic behavior.

**Verification Method**: 
- Static Analysis (grep for forbidden functions)
- Code Review (QUA/VER)
- Linker configuration (no heap section)
```

#### 4.3.3 No Recursion (Highly Recommended SIL 3-4)

```markdown
**REQ-IMPL-004**: No Recursion  
**Priority**: High  
**SIL Level**: 3-4 (Highly Recommended)  
**Traceability**: EN 50128 Table A.4

**Description**: The software SHOULD NOT use recursive function calls (a function calling itself directly or indirectly).

**Rationale**: Eliminates stack overflow risk, ensures bounded execution time.

**Verification Method**: Static Analysis (call graph analysis), Code Review
```

#### 4.3.4 Cyclomatic Complexity Limit (Mandatory SIL 3-4)

```markdown
**REQ-IMPL-005**: Cyclomatic Complexity Limit  
**Priority**: High  
**SIL Level**: All  
**Traceability**: EN 50128 Table A.4

**Description**: Every function SHALL have cyclomatic complexity within the following limits:
- **SIL 0-1**: ≤ 20
- **SIL 2**: ≤ 15
- **SIL 3-4**: ≤ 10

**Rationale**: Lower complexity improves testability, readability, maintainability.

**Verification Method**: Static Analysis (Lizard, PC-lint)
```

---

## 5. SIL-Specific Content Requirements

### 5.1 Requirements by SIL Level

| Requirement Type | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 |
|------------------|-------|-------|-------|-------|-------|
| **Functional Requirements** | Required | Required | Required | Required | Required |
| **Performance Requirements** | Required | Required | Required | Required | Required |
| **Interface Requirements** | Required | Required | Required | Required | Required |
| **Safety Requirements** | Optional | Recommended | Required | **Detailed** | **Detailed + Redundancy** |
| **Implementation Constraints** | Basic | Basic | **MISRA C Mandatory** | **MISRA C + Complexity ≤10** | **MISRA C + No Recursion + Defensive** |
| **Requirements Traceability Matrix (RTM)** | Recommended | Recommended | Highly Recommended | **MANDATORY** | **MANDATORY** |
| **EN 50128 Table A.2 Techniques** | 1-2 techniques | 2 techniques | 2-3 techniques | **3+ techniques (incl. Modelling)** | **3+ techniques (incl. Modelling)** |

### 5.2 Approval Requirements by SIL Level

| SIL Level | Required Approvers | Independence Required | Approval Process |
|-----------|-------------------|----------------------|------------------|
| **SIL 0-1** | Author + Reviewer + PM | No | Standard review (internal team) |
| **SIL 2** | Author + Reviewer + QA Manager + PM | No | Enhanced review (QA involved) |
| **SIL 3-4** | Author + **Independent Reviewer** + QA Manager + Safety Manager + **Independent Verifier** + **Independent Validator** + Assessor + PM + **Customer** | **YES** | **Independent review (separate organization)** |

**SIL 3-4 Independence Requirements** (EN 50128 Section 5.1.2):
- **Verifier SHALL NOT be**: Requirements Manager, Designer, Implementer, Integrator, Tester, or Validator
- **Validator SHALL NOT be**: Requirements Manager, Designer, Implementer, Integrator, Tester, or Verifier
- **Validator SHALL NOT report to Project Manager** (independent authority)

### 5.3 SIL 3-4 Enhanced Safety Requirements

For SIL 3-4 projects, the SRS SHALL include **enhanced safety requirements**:

#### 5.3.1 Redundancy and Diversity

```markdown
**REQ-SAFE-010**: Redundant Speed Monitoring  
**Priority**: Critical  
**SIL Level**: 4  
**Traceability**: HAZ-001

**Description**: The software SHALL monitor train speed from TWO independent sensors using diverse technologies:
- Primary sensor: Hall effect sensor (wheel rotation)
- Secondary sensor: Doppler radar (ground speed)

**Voting Logic**: 1-out-of-2 (1oo2) - If EITHER sensor reads speed > 5 km/h, lock doors.

**Failure Mode**: If sensors disagree by > 10%, raise fault alarm AND lock doors (fail-safe).

**Verification Method**: Safety Test, FMEA, Fault Injection
```

#### 5.3.2 Fault Detection and Diagnosis

```markdown
**REQ-SAFE-020**: Sensor Plausibility Check  
**Priority**: Critical  
**SIL Level**: 4  
**Traceability**: HAZ-002

**Description**: The software SHALL perform plausibility checks on all sensor inputs:
- Range check: Sensor value within physical limits (e.g., speed 0-200 km/h)
- Rate-of-change check: Sensor value change within physical limits (e.g., acceleration ≤ 2 m/s²)
- Cross-check: Compare primary and secondary sensors (difference ≤ 10%)

**Failure Response**: If plausibility check fails, use conservative safe value AND raise diagnostic alarm.

**Verification Method**: Unit Test, Integration Test, Fault Injection
```

#### 5.3.3 Watchdog Monitoring

```markdown
**REQ-SAFE-030**: Hardware Watchdog  
**Priority**: Critical  
**SIL Level**: 4  
**Traceability**: HAZ-003

**Description**: The software SHALL refresh an external hardware watchdog timer every 100ms. If the software fails to refresh the watchdog within 200ms, the hardware SHALL reset the system into a safe state.

**Safe State**: Upon watchdog reset:
- All actuators disabled (0% PWM)
- All doors locked (solenoid energized)
- Emergency status reported (if communication available)

**Verification Method**: Safety Test, Fault Injection (deliberate watchdog timeout)
```

### 5.4 SIL 0-1 Basic Requirements

For SIL 0-1 projects, the SRS MAY use simplified documentation:

**Simplified Sections**:
- Fewer requirements (focus on essential functionality)
- Less detailed safety analysis (if any safety requirements exist)
- Standard code review (no independent review required)
- Basic traceability (recommended but not mandatory)

**Example SIL 0 Requirement**:
```markdown
**REQ-FUNC-100**: Diagnostic Display  
**Priority**: Low  
**SIL Level**: 0  
**Traceability**: SYS-REQ-050 (diagnostic feature request)

**Description**: The software MAY provide diagnostic information via serial console (UART, 115200 baud, 8N1) for maintenance purposes.

**Content**: System status, fault codes, uptime counter.

**Note**: This interface is for maintenance only and is NOT safety-critical.

**Verification Method**: Manual Test (inspection)
```

---

## 6. Requirements Traceability

### 6.1 Traceability Fundamentals

**Traceability** is the ability to link requirements across lifecycle phases:

```
System Requirements ← SRS → Architecture → Design → Code → Tests
      ↑                                                        ↓
      └────────────────────── Validation ←────────────────────┘
```

**Traceability is MANDATORY for SIL 3-4** (EN 50128 Table A.9, Technique 7).

### 6.2 Requirements Traceability Matrix (RTM)

The RTM SHALL be maintained in:

```
docs/traceability/RTM.md
```

**RTM Format** (managed by `workspace.py trace` tool):

```markdown
# Requirements Traceability Matrix (RTM)

**Project**: [Project Name]  
**Document**: DOC-SRS-2026-001  
**Last Updated**: 2026-03-14

## Traceability Table

| System Req | SW Req | Architecture | Design | Code | Unit Test | Integration Test | System Test | Status |
|------------|--------|--------------|--------|------|-----------|------------------|-------------|--------|
| SYS-REQ-001 | REQ-FUNC-001 | MOD-CTRL | door_ctrl_design | door_ctrl.c:45 | TC-UNIT-001 | TC-INT-001 | TC-SYS-001 | Traced |
| SYS-REQ-002 | REQ-FUNC-002 | MOD-CTRL | door_ctrl_design | door_ctrl.c:78 | TC-UNIT-002 | TC-INT-002 | TC-SYS-002 | Traced |
| SYS-REQ-010 | REQ-SAFE-001 | MOD-SAFE | safety_design | safety.c:120 | TC-UNIT-SAFE-001 | TC-INT-SAFE-001 | TC-SYS-SAFE-001 | Traced |
| SYS-REQ-011 | REQ-SAFE-002 | MOD-SAFE | safety_design | safety.c:145 | TC-UNIT-SAFE-002 | TC-INT-SAFE-002 | TC-SYS-SAFE-002 | Traced |
| HAZ-001 | REQ-SAFE-010 | MOD-SAFE | safety_design | safety.c:200 | TC-UNIT-SAFE-010 | TC-INT-SAFE-010 | TC-SYS-SAFE-010 | Traced |
```

**RTM Completeness Criteria**:
- **Forward Traceability**: Every requirement traces forward to tests (100% coverage)
- **Backward Traceability**: Every requirement traces backward to system requirements or hazards (100% coverage)
- **Bidirectional Traceability**: Both forward and backward links complete

### 6.3 Using `workspace.py trace` for RTM Management

The `workspace.py trace` command provides automated traceability management.

#### 6.3.1 Initialize RTM

```bash
# Initialize new RTM for project
python3 tools/workspace.py trace init --project "Train Door Control" --sil 3

# Output: RTM file created at docs/traceability/RTM.md
```

#### 6.3.2 Add Traceability Link

```bash
# Link system requirement to software requirement
python3 tools/workspace.py trace add \
  --from "SYS-REQ-001" \
  --to "REQ-FUNC-001" \
  --type "sys-to-sw" \
  --description "Door opening function"

# Link software requirement to design
python3 tools/workspace.py trace add \
  --from "REQ-FUNC-001" \
  --to "MOD-CTRL" \
  --type "sw-to-design" \
  --description "Control module implements door opening"

# Link design to code
python3 tools/workspace.py trace add \
  --from "MOD-CTRL" \
  --to "src/control/door_ctrl.c:45" \
  --type "design-to-code" \
  --description "door_open() function"

# Link code to tests
python3 tools/workspace.py trace add \
  --from "src/control/door_ctrl.c:45" \
  --to "tests/unit/test_door_ctrl.c:TestDoorOpen" \
  --type "code-to-test" \
  --description "Unit test for door_open()"
```

#### 6.3.3 Verify RTM Completeness

```bash
# Check for missing forward traceability (requirements without tests)
python3 tools/workspace.py trace verify --direction forward

# Check for missing backward traceability (requirements without system req)
python3 tools/workspace.py trace verify --direction backward

# Generate traceability report (HTML/PDF)
python3 tools/workspace.py trace report --format html --output docs/traceability/RTM_report.html
```

**Example Output**:
```
Traceability Verification Report
=================================

Forward Traceability: 98% (49/50 requirements traced to tests)
  Missing: REQ-FUNC-025 (no test case found)

Backward Traceability: 100% (50/50 requirements traced to system req)

Recommendation: Add test case for REQ-FUNC-025 to achieve 100% forward traceability.
```

#### 6.3.4 Generate Traceability Matrix

```bash
# Generate full RTM (Markdown format)
python3 tools/workspace.py trace matrix --output docs/traceability/RTM.md

# Generate RTM for specific SIL level (SIL 4 only)
python3 tools/workspace.py trace matrix --sil 4 --output docs/traceability/RTM_SIL4.md
```

### 6.4 Traceability in SRS Document

The SRS SHALL include a **Requirements Traceability Matrix summary** in Section 4.2:

```markdown
## 4.2 Requirements Traceability Matrix (RTM)

**Location**: `docs/traceability/RTM.md`

**Format**: Bidirectional traceability from system requirements to software requirements to design to code to tests.

| System Req | SW Req | Design | Code | Test | Status |
|------------|--------|--------|------|------|--------|
| SYS-001 | REQ-FUNC-001 | MOD-001 | door_ctrl.c:45 | TC-UNIT-001, TC-INT-001, TC-SYS-001 | Traced |
| SYS-002 | REQ-FUNC-002 | MOD-001 | door_ctrl.c:78 | TC-UNIT-002, TC-INT-002, TC-SYS-002 | Traced |
| ... | ... | ... | ... | ... | ... |

**RTM Completeness**: 100% of requirements traced forward (to tests) and backward (to system requirements).

**Tool**: Traceability maintained using `workspace.py trace` command.
```

---

## 7. SRS Review and Approval

### 7.1 Review Workflow

The SRS SHALL undergo the following review workflow:

```
┌─────────────────────────────────────────────────────────────────┐
│ STEP 1: Author Creates SRS Draft (REQ)                          │
│ - Elicit requirements from stakeholders                         │
│ - Analyze system requirements                                   │
│ - Document requirements in SRS template                         │
│ - Status: Draft (Version 0.1)                                   │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ STEP 2: Template Compliance Check (QUA) - MANDATORY SIL 3-4     │
│ - Verify document follows template structure                    │
│ - Check header, version control, approvals table                │
│ - Validate all mandatory sections present                       │
│ - Run automated template validator (see Section 8)              │
│ - Status: Draft (Version 0.2 if changes needed)                 │
│ - Decision: PASS → Step 3, FAIL → Return to REQ (1 iteration)   │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ STEP 3: Technical Review (VER) - Independent for SIL 3-4        │
│ - Review requirements completeness (all system req covered)     │
│ - Review requirements quality (unambiguous, testable)           │
│ - Review traceability (100% backward trace to system req)       │
│ - Review safety requirements (SIL levels assigned)              │
│ - Review Table A.2 techniques applied                           │
│ - Status: Review (Version 0.3 if changes needed)                │
│ - Decision: APPROVE → Step 4, REJECT → Return to REQ            │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ STEP 4: Safety Review (SAF) - For SIL 2+ projects               │
│ - Review safety requirements completeness                       │
│ - Verify SIL levels assigned correctly (per hazard analysis)    │
│ - Verify hazard mitigation requirements present                 │
│ - Verify fault detection requirements present                   │
│ - Status: Review (Version 0.4 if changes needed)                │
│ - Decision: APPROVE → Step 5, REJECT → Return to REQ            │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ STEP 5: Validation Review (VAL) - Independent for SIL 3-4       │
│ - Review SRS against customer needs and system requirements     │
│ - Verify all system requirements allocated to software          │
│ - Verify requirements are implementable                         │
│ - Status: Review (Version 0.5 if changes needed)                │
│ - Decision: APPROVE → Step 6, REJECT → Return to REQ            │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ STEP 6: Approval and Baseline (PM + Customer for SIL 3-4)       │
│ - PM approves SRS as project baseline                           │
│ - Customer approves SRS (SIL 3-4 MANDATORY)                     │
│ - CM creates baseline (Version 1.0)                             │
│ - Status: Approved, Baseline                                    │
│ - Workflow tool: Submit via workspace.py wf (see Section 9.2)   │
└─────────────────────────────────────────────────────────────────┘
                          ↓
                  SRS APPROVED (Baseline 1.0)
```

### 7.2 Review Criteria

#### 7.2.1 QUA Template Compliance Checklist

QUA SHALL verify the following (automated script available, see Section 8):

- [ ] **Document ID** follows format: `DOC-SRS-YYYY-NNN`
- [ ] **Version** follows format: `MAJOR.MINOR` (0.1 for draft, 1.0 for approved)
- [ ] **SIL Level** specified: 0, 1, 2, 3, or 4
- [ ] **Standard Header** table present with all fields (Document ID, Version, Date, Project, SIL Level, Author, Reviewer, Approver, Status)
- [ ] **Document Control** table present with version history
- [ ] **Approvals** table present with SIL-appropriate signature roles
- [ ] **All mandatory sections** present (1-7, see Section 3.2)
- [ ] **Requirements format** consistent (REQ-CAT-NNN format)
- [ ] **Keywords** used correctly (SHALL/SHOULD/MAY)
- [ ] **Traceability** table present (Section 4.2)

**Result**: PASS (proceed to technical review) or FAIL (return to author for corrections)

#### 7.2.2 VER Technical Review Checklist

VER SHALL verify the following:

**Completeness**:
- [ ] All system requirements allocated to software are captured
- [ ] All interfaces documented (hardware, software, communication, user)
- [ ] All safety requirements identified (with SIL levels assigned)
- [ ] All implementation constraints documented (MISRA C, static allocation, etc.)

**Quality**:
- [ ] Requirements are unambiguous (single interpretation, no vague terms)
- [ ] Requirements are testable (verification method specified, acceptance criteria defined)
- [ ] Requirements are consistent (no conflicts between requirements)
- [ ] Requirements use mandatory keywords (SHALL/SHOULD/MAY)
- [ ] Requirements include quantitative criteria where applicable

**Traceability**:
- [ ] 100% backward traceability (all SW req trace to system req or hazards)
- [ ] Requirements Traceability Matrix (RTM) present and complete

**EN 50128 Compliance**:
- [ ] Table A.2 techniques applied (structured methodology, modelling, etc.)
- [ ] Section 7.2 requirements met (see Section 2.1)

**Result**: APPROVE (proceed to safety review) or REJECT (return to author with findings)

#### 7.2.3 SAF Safety Review Checklist

SAF SHALL verify the following (for SIL 2+ projects):

**Safety Requirements**:
- [ ] All hazards from Hazard Log addressed
- [ ] Safety requirements clearly identified (Section 3.4)
- [ ] SIL levels assigned correctly (per EN 50126 risk analysis)
- [ ] Redundancy requirements specified for SIL 3-4 (diverse sensors, voting logic)
- [ ] Fault detection requirements specified (plausibility checks, watchdog)
- [ ] Fail-safe behavior specified (safe states, default values)

**Hazard Mitigation**:
- [ ] Each hazard traces to one or more safety requirements
- [ ] Safety requirements are sufficient to mitigate hazards

**Result**: APPROVE (proceed to validation review) or REJECT (return to author)

#### 7.2.4 VAL Validation Review Checklist

VAL SHALL verify the following (independent for SIL 3-4):

**Customer Needs**:
- [ ] SRS meets customer needs (all requested functionality captured)
- [ ] SRS is understandable to customer (clear language, no jargon)
- [ ] SRS includes acceptance criteria (customer can validate)

**System Allocation**:
- [ ] All system requirements allocated to software are captured in SRS
- [ ] Software requirements are implementable (feasible within constraints)

**Result**: APPROVE (proceed to PM approval) or REJECT (return to author)

### 7.3 Using `workspace.py wf` for Approval Workflow

The `workspace.py wf` command automates document submission and approval tracking.

#### 7.3.1 Submit SRS for Review

```bash
# Author (REQ) submits SRS for template compliance check (QUA)
python3 tools/workspace.py wf submit \
  --document "docs/requirements/SRS_Train_Door_Control.md" \
  --type "SRS" \
  --version "0.1" \
  --approver "QUA" \
  --sil 3

# Output: Workflow ID: WF-2026-001
#         Status: Pending QUA template check
#         Notification sent to QUA team
```

#### 7.3.2 QUA Approves (Template Compliance)

```bash
# QUA reviews and approves template compliance
python3 tools/workspace.py wf approve \
  --workflow-id "WF-2026-001" \
  --approver "QUA" \
  --decision "APPROVE" \
  --comment "Template compliance verified. All mandatory sections present."

# Output: Status: Pending VER technical review
#         Notification sent to VER team
```

#### 7.3.3 VER Approves (Technical Review)

```bash
# VER (independent for SIL 3-4) reviews and approves technical content
python3 tools/workspace.py wf approve \
  --workflow-id "WF-2026-001" \
  --approver "VER" \
  --decision "APPROVE" \
  --comment "Technical review complete. Requirements are complete, unambiguous, testable. Traceability 100%."

# Output: Status: Pending SAF safety review
#         Notification sent to SAF team
```

#### 7.3.4 SAF Approves (Safety Review)

```bash
# SAF reviews and approves safety content
python3 tools/workspace.py wf approve \
  --workflow-id "WF-2026-001" \
  --approver "SAF" \
  --decision "APPROVE" \
  --comment "Safety review complete. All hazards mitigated. SIL levels assigned correctly."

# Output: Status: Pending VAL validation review
#         Notification sent to VAL team
```

#### 7.3.5 VAL Approves (Validation Review)

```bash
# VAL (independent for SIL 3-4) reviews and approves against customer needs
python3 tools/workspace.py wf approve \
  --workflow-id "WF-2026-001" \
  --approver "VAL" \
  --decision "APPROVE" \
  --comment "Validation review complete. SRS meets customer needs and system requirements."

# Output: Status: Pending PM approval
#         Notification sent to PM
```

#### 7.3.6 PM Approves (Baseline)

```bash
# PM approves SRS as project baseline
python3 tools/workspace.py wf approve \
  --workflow-id "WF-2026-001" \
  --approver "PM" \
  --decision "APPROVE" \
  --comment "SRS approved as baseline. Version 1.0 created by CM."

# Output: Status: APPROVED
#         Baseline: Version 1.0
#         Workflow complete
```

#### 7.3.7 Check Workflow Status

```bash
# Check status of workflow
python3 tools/workspace.py wf status --workflow-id "WF-2026-001"

# Output:
# Workflow ID: WF-2026-001
# Document: SRS_Train_Door_Control.md
# Type: SRS
# SIL Level: 3
# Current Version: 1.0
# Status: APPROVED (Baseline)
# 
# Approval History:
#   2026-03-10 10:00 - QUA: APPROVE (Template compliance verified)
#   2026-03-11 14:30 - VER: APPROVE (Technical review complete)
#   2026-03-12 09:15 - SAF: APPROVE (Safety review complete)
#   2026-03-12 16:45 - VAL: APPROVE (Validation review complete)
#   2026-03-14 08:00 - PM: APPROVE (Baseline 1.0 created)
```

### 7.4 Rejection and Iteration

If any reviewer **REJECTS** the SRS:

```bash
# VER rejects SRS due to missing requirements
python3 tools/workspace.py wf approve \
  --workflow-id "WF-2026-001" \
  --approver "VER" \
  --decision "REJECT" \
  --comment "Missing: Requirements for CAN bus error handling (timeouts, invalid messages). Please add REQ-IF-SW-010 through REQ-IF-SW-015."

# Output: Status: REJECTED by VER
#         Returned to: REQ (author)
#         Action: Address findings and resubmit
```

**Author (REQ) addresses findings and resubmits**:

```bash
# REQ fixes issues and resubmits (Version 0.2)
python3 tools/workspace.py wf resubmit \
  --workflow-id "WF-2026-001" \
  --version "0.2" \
  --changes "Added CAN bus error handling requirements (REQ-IF-SW-010 to REQ-IF-SW-015)"

# Output: Status: Pending VER technical review (iteration 2)
#         Notification sent to VER team
```

**Iteration Limits** (SIL 3-4):
- **QUA template check**: 1 iteration allowed (if rejected, author must fix and resubmit ONCE)
- **VER/SAF/VAL technical reviews**: Unlimited iterations (until approved or project canceled)

---

## 8. Template Validation

### 8.1 Automated Template Validator

The template validator script checks SRS documents for compliance with the standard template.

**Script Location**: `tools/scripts/validate_srs_template.py`

### 8.2 Validator Script (Complete Implementation)

```python
#!/usr/bin/env python3
"""
SRS Template Validator
Validates Software Requirements Specification documents against EN 50128 template.

Usage:
    python3 tools/scripts/validate_srs_template.py <srs_file.md> [--sil <0-4>]

Exit Codes:
    0 - Template validation passed
    1 - Template validation failed (issues found)
    2 - File not found or other error
"""

import sys
import re
import argparse
from pathlib import Path
from typing import List, Tuple

class SRSTemplateValidator:
    """Validates SRS documents against EN 50128 template."""
    
    # Required sections for all SIL levels
    REQUIRED_SECTIONS = [
        "STANDARD HEADER",
        "DOCUMENT CONTROL",
        "APPROVALS",
        "1. INTRODUCTION",
        "2. GENERAL DESCRIPTION",
        "3. SOFTWARE REQUIREMENTS",
        "4. VERIFICATION AND TRACEABILITY",
        "5. REQUIREMENTS SUMMARY",
        "6. COMPLIANCE MATRIX",
        "7. REFERENCES",
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
    
    # SIL-specific approval roles
    SIL_APPROVERS = {
        0: ["Author", "Reviewer", "Project Manager"],
        1: ["Author", "Reviewer", "Project Manager"],
        2: ["Author", "Reviewer", "QA Manager", "Project Manager"],
        3: ["Author", "Technical Reviewer", "QA Manager", "Safety Manager", "Independent Verifier", "Independent Validator", "Assessor", "Project Manager"],
        4: ["Author", "Technical Reviewer", "QA Manager", "Safety Manager", "Independent Verifier", "Independent Validator", "Assessor", "Project Manager"],
    }
    
    def __init__(self, srs_file: Path, sil_level: int = None):
        self.srs_file = srs_file
        self.sil_level = sil_level
        self.content = ""
        self.issues: List[str] = []
        self.warnings: List[str] = []
        
    def validate(self) -> bool:
        """Run all validation checks. Returns True if passed, False if failed."""
        try:
            self.content = self.srs_file.read_text(encoding='utf-8')
        except FileNotFoundError:
            print(f"ERROR: File not found: {self.srs_file}", file=sys.stderr)
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
        self._check_requirements_format()
        self._check_keywords_usage()
        self._check_traceability()
        
        # Print results
        self._print_results()
        
        return len(self.issues) == 0
    
    def _check_document_id(self):
        """Check Document ID format: DOC-SRS-YYYY-NNN"""
        pattern = r'DOC-SRS-\d{4}-\d{3}'
        match = re.search(pattern, self.content)
        if not match:
            self.issues.append("Document ID not found or invalid format. Expected: DOC-SRS-YYYY-NNN (e.g., DOC-SRS-2026-001)")
        else:
            doc_id = match.group(0)
            print(f"✓ Document ID: {doc_id}")
    
    def _check_version(self):
        """Check Version format: MAJOR.MINOR"""
        # Look for version in header table
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
            # Check for version history table
            if not re.search(r'\|\s*Version\s*\|\s*Date\s*\|\s*Author\s*\|', self.content):
                self.issues.append("Document Control version history table missing")
            else:
                print("✓ Document Control section present")
    
    def _check_approvals_table(self):
        """Check Approvals table is present with SIL-specific roles."""
        if "## APPROVALS" not in self.content:
            self.issues.append("APPROVALS section missing")
            return
        
        # Extract SIL level if not provided
        if self.sil_level is None:
            sil_match = re.search(r'\|\s*\*\*SIL Level\*\*\s*\|\s*\[?(\d)\]?\s*\|', self.content)
            if sil_match:
                self.sil_level = int(sil_match.group(1))
            else:
                self.warnings.append("Could not determine SIL level from document. Skipping approvals check.")
                return
        
        # Check for required approvers based on SIL level
        required_approvers = self.SIL_APPROVERS.get(self.sil_level, [])
        missing_approvers = []
        for approver in required_approvers:
            pattern = rf'\|\s*\*\*{re.escape(approver)}\*\*'
            if not re.search(pattern, self.content, re.IGNORECASE):
                missing_approvers.append(approver)
        
        if missing_approvers:
            self.issues.append(f"Missing approvers for SIL {self.sil_level}: {', '.join(missing_approvers)}")
        else:
            print(f"✓ Approvals table present with all required roles (SIL {self.sil_level})")
    
    def _check_required_sections(self):
        """Check all required sections are present."""
        missing_sections = []
        for section in self.REQUIRED_SECTIONS:
            # Match section header (## or ###)
            pattern = rf'^##+ {re.escape(section)}'
            if not re.search(pattern, self.content, re.MULTILINE):
                missing_sections.append(section)
        
        if missing_sections:
            self.issues.append(f"Missing required sections: {', '.join(missing_sections)}")
        else:
            print(f"✓ All required sections present ({len(self.REQUIRED_SECTIONS)} sections)")
    
    def _check_requirements_format(self):
        """Check requirements follow standard format: REQ-CAT-NNN"""
        req_pattern = r'\*\*REQ-([A-Z]+)-(\d{3})\*\*'
        requirements = re.findall(req_pattern, self.content)
        
        if len(requirements) == 0:
            self.warnings.append("No requirements found in document (expected format: REQ-CAT-NNN)")
        else:
            print(f"✓ Found {len(requirements)} requirements in standard format")
            
            # Check for duplicate requirement IDs
            req_ids = [f"REQ-{cat}-{num}" for cat, num in requirements]
            duplicates = [req_id for req_id in req_ids if req_ids.count(req_id) > 1]
            if duplicates:
                self.issues.append(f"Duplicate requirement IDs: {', '.join(set(duplicates))}")
    
    def _check_keywords_usage(self):
        """Check requirements use SHALL/SHOULD/MAY keywords."""
        # Count keyword usage
        shall_count = len(re.findall(r'\bSHALL\b', self.content))
        should_count = len(re.findall(r'\bSHOULD\b', self.content))
        may_count = len(re.findall(r'\bMAY\b', self.content))
        
        if shall_count == 0 and should_count == 0 and may_count == 0:
            self.issues.append("No mandatory keywords (SHALL/SHOULD/MAY) found in requirements")
        else:
            print(f"✓ Keywords usage: SHALL ({shall_count}), SHOULD ({should_count}), MAY ({may_count})")
    
    def _check_traceability(self):
        """Check Requirements Traceability Matrix section is present."""
        if "4.2 Requirements Traceability Matrix" not in self.content and "Requirements Traceability Matrix" not in self.content:
            if self.sil_level and self.sil_level >= 3:
                self.issues.append("Requirements Traceability Matrix (RTM) missing (MANDATORY for SIL 3-4)")
            else:
                self.warnings.append("Requirements Traceability Matrix (RTM) not found (recommended)")
        else:
            print("✓ Requirements Traceability Matrix section present")
    
    def _print_results(self):
        """Print validation results."""
        print("\n" + "="*70)
        print("SRS TEMPLATE VALIDATION RESULTS")
        print("="*70)
        
        if len(self.issues) == 0 and len(self.warnings) == 0:
            print("\n✓✓✓ VALIDATION PASSED ✓✓✓")
            print("SRS document complies with EN 50128 template.")
        elif len(self.issues) == 0:
            print("\n✓ VALIDATION PASSED (with warnings)")
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
        description="Validate SRS document against EN 50128 template"
    )
    parser.add_argument(
        "srs_file",
        type=Path,
        help="Path to SRS markdown file"
    )
    parser.add_argument(
        "--sil",
        type=int,
        choices=[0, 1, 2, 3, 4],
        help="SIL level (0-4). If not specified, will attempt to extract from document."
    )
    
    args = parser.parse_args()
    
    if not args.srs_file.exists():
        print(f"ERROR: File not found: {args.srs_file}", file=sys.stderr)
        sys.exit(2)
    
    validator = SRSTemplateValidator(args.srs_file, args.sil_level)
    passed = validator.validate()
    
    sys.exit(0 if passed else 1)


if __name__ == "__main__":
    main()
```

### 8.3 Using the Validator

```bash
# Validate SRS document
python3 tools/scripts/validate_srs_template.py docs/requirements/SRS_Train_Door_Control.md --sil 3

# Example output (PASS):
# ✓ Document ID: DOC-SRS-2026-001
# ✓ Version: 1.0
# ✓ All header fields present (9 fields)
# ✓ Document Control section present
# ✓ Approvals table present with all required roles (SIL 3)
# ✓ All required sections present (7 sections)
# ✓ Found 50 requirements in standard format
# ✓ Keywords usage: SHALL (120), SHOULD (15), MAY (5)
# ✓ Requirements Traceability Matrix section present
# 
# ======================================================================
# SRS TEMPLATE VALIDATION RESULTS
# ======================================================================
# 
# ✓✓✓ VALIDATION PASSED ✓✓✓
# SRS document complies with EN 50128 template.
# ======================================================================

# Example output (FAIL):
# ✓ Document ID: DOC-SRS-2026-001
# ✗ Version not found or invalid format. Expected: X.Y
# ✗ Missing header fields: Reviewer, Approver
# ...
# 
# ======================================================================
# SRS TEMPLATE VALIDATION RESULTS
# ======================================================================
# 
# ✗✗✗ VALIDATION FAILED ✗✗✗
# Found 3 issue(s):
#   1. ERROR: Version not found or invalid format. Expected: X.Y (e.g., 1.0, 0.1)
#   2. ERROR: Missing header fields: Reviewer, Approver
#   3. ERROR: Missing required sections: 4. VERIFICATION AND TRACEABILITY
# ======================================================================
```

### 8.4 Integration with QUA Review

QUA SHALL run the template validator as part of Step 2 (Template Compliance Check):

```bash
# QUA runs validator before manual review
python3 tools/scripts/validate_srs_template.py docs/requirements/SRS_Train_Door_Control.md --sil 3

# If validator passes:
#   QUA performs manual review (check content readability, formatting)
#   QUA approves via workspace.py wf approve

# If validator fails:
#   QUA returns document to author with validator output
#   Author fixes issues and resubmits
```

---

## 9. Tool Integration

### 9.1 Overview

This workflow integrates with the following tools:

| Tool | Purpose | Usage in Workflow |
|------|---------|-------------------|
| **workspace.py wf** | Document workflow management (submission, approval tracking) | Submit SRS for review, track approval status |
| **workspace.py trace** | Requirements traceability management (RTM) | Add traceability links, verify completeness, generate RTM |
| **validate_srs_template.py** | Automated SRS template validation | QUA template compliance check (Step 2) |
| **extract_requirements.py** | Extract requirements from SRS for import into other tools | Generate requirement lists for test tools, design tools |
| **Git** | Version control | Commit SRS changes, track document history |

### 9.2 Document Workflow Management (`workspace.py wf`)

See Section 7.3 for complete examples of:
- `workspace.py wf submit` - Submit SRS for review
- `workspace.py wf approve` - Approve/reject SRS
- `workspace.py wf status` - Check workflow status
- `workspace.py wf resubmit` - Resubmit after rejection

### 9.3 Requirements Traceability Management (`workspace.py trace`)

See Section 6.3 for complete examples of:
- `workspace.py trace init` - Initialize RTM
- `workspace.py trace add` - Add traceability links
- `workspace.py trace verify` - Verify RTM completeness
- `workspace.py trace matrix` - Generate RTM report

### 9.4 Version Control (Git)

All SRS documents SHALL be under version control.

#### 9.4.1 Initial Commit

```bash
# Add SRS to Git
git add docs/requirements/SRS_Train_Door_Control.md

# Commit with descriptive message
git commit -m "Add SRS for Train Door Control System (DOC-SRS-2026-001 v0.1 - Draft)"

# Push to remote
git push origin main
```

#### 9.4.2 Update Commit (After Review)

```bash
# Update SRS based on review comments
git add docs/requirements/SRS_Train_Door_Control.md

# Commit with change description
git commit -m "Update SRS: Add CAN bus error handling requirements (REQ-IF-SW-010 to REQ-IF-SW-015) - v0.2"

git push origin main
```

#### 9.4.3 Baseline Commit (Approved SRS)

```bash
# Baseline SRS (Version 1.0 approved)
git add docs/requirements/SRS_Train_Door_Control.md

# Commit with baseline tag
git commit -m "Baseline SRS v1.0 - APPROVED by PM, VER, VAL, SAF (DOC-SRS-2026-001)"

# Create Git tag for baseline
git tag -a SRS-v1.0 -m "SRS Baseline 1.0 - Train Door Control System"

git push origin main --tags
```

---

## 10. Automation Scripts

### 10.1 SRS Template Validator

**Script**: `tools/scripts/validate_srs_template.py` (see Section 8.2 for complete implementation)

**Purpose**: Automated validation of SRS documents against EN 50128 template.

### 10.2 Requirements Extractor

**Script**: `tools/scripts/extract_requirements.py`

**Purpose**: Extract requirements from SRS for import into other tools (test management, traceability tools).

**Implementation** (150 lines):

```python
#!/usr/bin/env python3
"""
Requirements Extractor
Extracts requirements from SRS documents and exports to various formats.

Usage:
    python3 tools/scripts/extract_requirements.py <srs_file.md> --format <csv|json|xml>

Output Formats:
    - CSV: Spreadsheet import (Excel, Google Sheets)
    - JSON: Programmatic access, test tools
    - XML: DOORS, Polarion, other RM tools
"""

import sys
import re
import json
import csv
import argparse
from pathlib import Path
from typing import List, Dict
import xml.etree.ElementTree as ET
from xml.dom import minidom

class Requirement:
    """Represents a single software requirement."""
    def __init__(self, req_id: str, title: str, description: str = "", 
                 priority: str = "", sil: str = "", traceability: str = "",
                 verification: str = ""):
        self.req_id = req_id
        self.title = title
        self.description = description
        self.priority = priority
        self.sil = sil
        self.traceability = traceability
        self.verification = verification
    
    def to_dict(self) -> Dict:
        return {
            "req_id": self.req_id,
            "title": self.title,
            "description": self.description,
            "priority": self.priority,
            "sil": self.sil,
            "traceability": self.traceability,
            "verification": self.verification,
        }


class RequirementsExtractor:
    """Extracts requirements from SRS markdown documents."""
    
    def __init__(self, srs_file: Path):
        self.srs_file = srs_file
        self.requirements: List[Requirement] = []
    
    def extract(self) -> List[Requirement]:
        """Extract all requirements from SRS."""
        content = self.srs_file.read_text(encoding='utf-8')
        
        # Pattern to match requirement blocks
        req_pattern = r'\*\*REQ-[A-Z]+-\d{3}\*\*:[^\n]+(?:\n(?!\*\*REQ-).+)*'
        req_blocks = re.findall(req_pattern, content, re.MULTILINE)
        
        for block in req_blocks:
            req = self._parse_requirement_block(block)
            if req:
                self.requirements.append(req)
        
        return self.requirements
    
    def _parse_requirement_block(self, block: str) -> Requirement:
        """Parse a single requirement block."""
        # Extract requirement ID and title
        id_match = re.search(r'\*\*(REQ-[A-Z]+-\d{3})\*\*:\s*(.+)', block)
        if not id_match:
            return None
        
        req_id = id_match.group(1)
        title = id_match.group(2).strip()
        
        # Extract optional fields
        priority = self._extract_field(block, r'\*\*Priority\*\*:\s*(.+)')
        sil = self._extract_field(block, r'\*\*SIL Level\*\*:\s*(.+)')
        traceability = self._extract_field(block, r'\*\*Traceability\*\*:\s*(.+)')
        verification = self._extract_field(block, r'\*\*Verification Method\*\*:\s*(.+)')
        
        # Extract description (first paragraph after Description:)
        desc_match = re.search(r'\*\*Description\*\*:\s*(.+?)(?:\n\n|\*\*)', block, re.DOTALL)
        description = desc_match.group(1).strip() if desc_match else ""
        
        return Requirement(req_id, title, description, priority, sil, traceability, verification)
    
    def _extract_field(self, block: str, pattern: str) -> str:
        """Extract a single field value from requirement block."""
        match = re.search(pattern, block)
        return match.group(1).strip() if match else ""
    
    def export_csv(self, output_file: Path):
        """Export requirements to CSV format."""
        with output_file.open('w', newline='', encoding='utf-8') as f:
            writer = csv.writer(f)
            writer.writerow(["Requirement ID", "Title", "Description", "Priority", "SIL", "Traceability", "Verification"])
            
            for req in self.requirements:
                writer.writerow([
                    req.req_id,
                    req.title,
                    req.description,
                    req.priority,
                    req.sil,
                    req.traceability,
                    req.verification,
                ])
        
        print(f"Exported {len(self.requirements)} requirements to {output_file}")
    
    def export_json(self, output_file: Path):
        """Export requirements to JSON format."""
        data = {
            "source": str(self.srs_file),
            "count": len(self.requirements),
            "requirements": [req.to_dict() for req in self.requirements]
        }
        
        with output_file.open('w', encoding='utf-8') as f:
            json.dump(data, f, indent=2)
        
        print(f"Exported {len(self.requirements)} requirements to {output_file}")
    
    def export_xml(self, output_file: Path):
        """Export requirements to XML format (ReqIF-compatible)."""
        root = ET.Element("requirements")
        root.set("source", str(self.srs_file))
        root.set("count", str(len(self.requirements)))
        
        for req in self.requirements:
            req_elem = ET.SubElement(root, "requirement")
            req_elem.set("id", req.req_id)
            
            ET.SubElement(req_elem, "title").text = req.title
            ET.SubElement(req_elem, "description").text = req.description
            ET.SubElement(req_elem, "priority").text = req.priority
            ET.SubElement(req_elem, "sil").text = req.sil
            ET.SubElement(req_elem, "traceability").text = req.traceability
            ET.SubElement(req_elem, "verification").text = req.verification
        
        # Pretty print XML
        xml_str = minidom.parseString(ET.tostring(root)).toprettyxml(indent="  ")
        
        with output_file.open('w', encoding='utf-8') as f:
            f.write(xml_str)
        
        print(f"Exported {len(self.requirements)} requirements to {output_file}")


def main():
    parser = argparse.ArgumentParser(
        description="Extract requirements from SRS document"
    )
    parser.add_argument(
        "srs_file",
        type=Path,
        help="Path to SRS markdown file"
    )
    parser.add_argument(
        "--format",
        choices=["csv", "json", "xml"],
        default="csv",
        help="Output format (default: csv)"
    )
    parser.add_argument(
        "--output",
        type=Path,
        help="Output file (default: auto-generated based on format)"
    )
    
    args = parser.parse_args()
    
    if not args.srs_file.exists():
        print(f"ERROR: File not found: {args.srs_file}", file=sys.stderr)
        sys.exit(1)
    
    # Generate default output filename
    if not args.output:
        stem = args.srs_file.stem
        args.output = args.srs_file.parent / f"{stem}_requirements.{args.format}"
    
    # Extract requirements
    extractor = RequirementsExtractor(args.srs_file)
    extractor.extract()
    
    # Export to requested format
    if args.format == "csv":
        extractor.export_csv(args.output)
    elif args.format == "json":
        extractor.export_json(args.output)
    elif args.format == "xml":
        extractor.export_xml(args.output)


if __name__ == "__main__":
    main()
```

### 10.3 Using Requirements Extractor

```bash
# Extract requirements to CSV (Excel import)
python3 tools/scripts/extract_requirements.py docs/requirements/SRS_Train_Door_Control.md --format csv

# Output: docs/requirements/SRS_Train_Door_Control_requirements.csv
# Exported 50 requirements to docs/requirements/SRS_Train_Door_Control_requirements.csv

# Extract requirements to JSON (test tool import)
python3 tools/scripts/extract_requirements.py docs/requirements/SRS_Train_Door_Control.md --format json --output requirements.json

# Extract requirements to XML (DOORS import)
python3 tools/scripts/extract_requirements.py docs/requirements/SRS_Train_Door_Control.md --format xml
```

---

## 11. Example Scenarios

### 11.1 Scenario 1: Create SRS for SIL 3 Project (End-to-End)

**Project**: Train Door Control System  
**SIL Level**: 3  
**Duration**: 2 weeks

#### Step 1: Initialize Project and Elicit Requirements (Week 1, Days 1-3)

```bash
# Initialize traceability matrix
python3 tools/workspace.py trace init --project "Train Door Control" --sil 3

# Review input documents
# - System Requirements Specification
# - Hazard Log (from Safety Engineer)
# - System Architecture Description

# Elicit requirements through:
# - Stakeholder interviews (customer, operators)
# - System requirements analysis (decompose SYS-REQ → SW-REQ)
# - Hazard analysis review (HAZ → REQ-SAFE)
# - Interface analysis (hardware, software, communication)

# Create initial SRS draft (Version 0.1)
# Use template: .opencode/skills/en50128-requirements/templates/Software-Requirements-Specification-template.md
# Document ~50 requirements:
#   - 25 functional requirements (REQ-FUNC-001 to REQ-FUNC-025)
#   - 10 performance requirements (REQ-PERF-001 to REQ-PERF-010)
#   - 10 interface requirements (REQ-IF-xxx-001 to REQ-IF-xxx-010)
#   - 5 safety requirements (REQ-SAFE-001 to REQ-SAFE-005)
```

#### Step 2: Add Traceability Links (Week 1, Days 4-5)

```bash
# Link system requirements to software requirements
python3 tools/workspace.py trace add --from "SYS-REQ-001" --to "REQ-FUNC-001" --type "sys-to-sw"
python3 tools/workspace.py trace add --from "SYS-REQ-002" --to "REQ-FUNC-002" --type "sys-to-sw"
# ... (continue for all 50 requirements)

# Link hazards to safety requirements
python3 tools/workspace.py trace add --from "HAZ-001" --to "REQ-SAFE-001" --type "hazard-to-sw"
python3 tools/workspace.py trace add --from "HAZ-002" --to "REQ-SAFE-002" --type "hazard-to-sw"
# ... (continue for all safety requirements)

# Verify backward traceability (100% coverage required for SIL 3)
python3 tools/workspace.py trace verify --direction backward

# Expected output:
# Backward Traceability: 100% (50/50 requirements traced to system req or hazards)
```

#### Step 3: Submit SRS for Review (Week 2, Day 1)

```bash
# Validate template compliance (self-check before submission)
python3 tools/scripts/validate_srs_template.py docs/requirements/SRS_Train_Door_Control.md --sil 3

# If validation passes, submit for review
python3 tools/workspace.py wf submit \
  --document "docs/requirements/SRS_Train_Door_Control.md" \
  --type "SRS" \
  --version "0.1" \
  --approver "QUA" \
  --sil 3

# Output: Workflow ID: WF-2026-001
#         Status: Pending QUA template check
```

#### Step 4: QUA Template Compliance Check (Week 2, Day 1)

```bash
# QUA runs template validator
python3 tools/scripts/validate_srs_template.py docs/requirements/SRS_Train_Door_Control.md --sil 3

# Result: VALIDATION PASSED

# QUA approves
python3 tools/workspace.py wf approve \
  --workflow-id "WF-2026-001" \
  --approver "QUA" \
  --decision "APPROVE" \
  --comment "Template compliance verified."

# Status: Pending VER technical review
```

#### Step 5: VER Technical Review (Week 2, Days 2-3)

```bash
# VER (independent reviewer) performs technical review:
# - Check requirements completeness (all system req covered)
# - Check requirements quality (unambiguous, testable)
# - Check traceability (RTM 100% complete)
# - Check EN 50128 Table A.2 techniques applied

# VER finds issues:
# - Missing: CAN bus timeout requirements
# - Ambiguous: REQ-PERF-005 "fast response" not quantitative

# VER rejects
python3 tools/workspace.py wf approve \
  --workflow-id "WF-2026-001" \
  --approver "VER" \
  --decision "REJECT" \
  --comment "Missing CAN bus timeout requirements. REQ-PERF-005 needs quantitative criteria."

# Status: REJECTED by VER, returned to REQ
```

#### Step 6: REQ Addresses Findings and Resubmits (Week 2, Day 4)

```bash
# REQ updates SRS (Version 0.2):
# - Add REQ-IF-SW-010: "CAN timeout SHALL be 100ms"
# - Update REQ-PERF-005: "Response time SHALL be ≤ 50ms"

# Resubmit
python3 tools/workspace.py wf resubmit \
  --workflow-id "WF-2026-001" \
  --version "0.2" \
  --changes "Added CAN timeout requirement (REQ-IF-SW-010). Updated REQ-PERF-005 with quantitative criteria (≤ 50ms)."

# Status: Pending VER technical review (iteration 2)
```

#### Step 7: VER Approves (Week 2, Day 4)

```bash
# VER reviews changes and approves
python3 tools/workspace.py wf approve \
  --workflow-id "WF-2026-001" \
  --approver "VER" \
  --decision "APPROVE" \
  --comment "Technical review complete. All issues addressed."

# Status: Pending SAF safety review
```

#### Step 8: SAF Safety Review and Approval (Week 2, Day 5)

```bash
# SAF reviews safety requirements:
# - All hazards from Hazard Log mitigated
# - SIL levels assigned correctly
# - Redundancy specified for critical functions

# SAF approves
python3 tools/workspace.py wf approve \
  --workflow-id "WF-2026-001" \
  --approver "SAF" \
  --decision "APPROVE" \
  --comment "Safety review complete. All hazards mitigated."

# Status: Pending VAL validation review
```

#### Step 9: VAL Validation Review and Approval (Week 2, Day 5)

```bash
# VAL (independent validator) reviews against customer needs:
# - SRS meets all customer requirements
# - SRS is implementable within constraints

# VAL approves
python3 tools/workspace.py wf approve \
  --workflow-id "WF-2026-001" \
  --approver "VAL" \
  --decision "APPROVE" \
  --comment "Validation review complete. SRS meets customer needs."

# Status: Pending PM approval
```

#### Step 10: PM Approves Baseline (Week 2, Day 5)

```bash
# PM approves SRS as baseline
python3 tools/workspace.py wf approve \
  --workflow-id "WF-2026-001" \
  --approver "PM" \
  --decision "APPROVE" \
  --comment "SRS approved as baseline. Version 1.0."

# Status: APPROVED (Baseline)

# CM creates Git baseline
git add docs/requirements/SRS_Train_Door_Control.md
git commit -m "Baseline SRS v1.0 - APPROVED (DOC-SRS-2026-001)"
git tag -a SRS-v1.0 -m "SRS Baseline 1.0"
git push origin main --tags
```

#### Summary

| Milestone | Duration | Outcome |
|-----------|----------|---------|
| Requirements elicitation | 3 days | 50 requirements documented |
| Traceability setup | 2 days | RTM 100% complete |
| QUA review | 0.5 days | Template compliance verified |
| VER review (1st iteration) | 1 day | Issues found, rejected |
| REQ fixes and resubmit | 0.5 days | Issues addressed (v0.2) |
| VER review (2nd iteration) | 0.5 days | Approved |
| SAF review | 0.5 days | Approved |
| VAL review | 0.5 days | Approved |
| PM approval | 0.5 days | Baseline 1.0 created |
| **Total** | **9 days (< 2 weeks)** | **SRS approved and baselined** |

### 11.2 Scenario 2: Update Baseline SRS (Change Request)

**Situation**: Customer requests new feature (CAN bus diagnostic messages)  
**Change Request**: CR-2026-005  
**Impact**: Add 3 new requirements to SRS

#### Step 1: CCB Approves Change Request

```bash
# CCB (Change Control Board) reviews and approves CR-2026-005
# Impact assessment: Low impact (3 new non-safety requirements)
# Approval: Proceed with SRS update
```

#### Step 2: REQ Updates SRS (Version 1.1)

```bash
# REQ adds new requirements to SRS:
# - REQ-IF-SW-020: "Software SHALL send diagnostic message every 1 second"
# - REQ-IF-SW-021: "Diagnostic message SHALL include: uptime, fault count, CPU usage"
# - REQ-IF-SW-022: "Diagnostic message format SHALL follow CAN ID 0x200"

# Update Document Control table (version 1.1, change log)
# Add traceability links
python3 tools/workspace.py trace add --from "CR-2026-005" --to "REQ-IF-SW-020" --type "cr-to-sw"
python3 tools/workspace.py trace add --from "CR-2026-005" --to "REQ-IF-SW-021" --type "cr-to-sw"
python3 tools/workspace.py trace add --from "CR-2026-005" --to "REQ-IF-SW-022" --type "cr-to-sw"

# Submit updated SRS
python3 tools/workspace.py wf submit \
  --document "docs/requirements/SRS_Train_Door_Control.md" \
  --type "SRS" \
  --version "1.1" \
  --approver "QUA" \
  --sil 3 \
  --change-request "CR-2026-005"
```

#### Step 3: Fast-Track Review (Minor Change)

```bash
# For minor changes (non-safety requirements), fast-track review:
# QUA: Template check (automated)
# VER: Technical review (new requirements only)
# PM: Approve update

# QUA approves
python3 tools/workspace.py wf approve --workflow-id "WF-2026-020" --approver "QUA" --decision "APPROVE"

# VER approves
python3 tools/workspace.py wf approve --workflow-id "WF-2026-020" --approver "VER" --decision "APPROVE"

# PM approves (no need for SAF/VAL review for non-safety change)
python3 tools/workspace.py wf approve --workflow-id "WF-2026-020" --approver "PM" --decision "APPROVE"

# Baseline 1.1 created
git add docs/requirements/SRS_Train_Door_Control.md
git commit -m "Update SRS v1.1 - Add CAN diagnostic requirements (CR-2026-005)"
git tag -a SRS-v1.1 -m "SRS Baseline 1.1 - CAN diagnostic feature"
git push origin main --tags
```

---

## 12. Conclusion

This workflow provides comprehensive guidance for creating, reviewing, and approving Software Requirements Specification (SRS) documents in compliance with EN 50128:2011 Section 7.2. By following this workflow, you will:

✓ Create high-quality, EN 50128-compliant SRS documents  
✓ Ensure requirements are complete, unambiguous, testable, and traceable  
✓ Apply SIL-appropriate requirements specification techniques (Table A.2)  
✓ Implement SIL-dependent review and approval processes  
✓ Leverage automation tools for validation and traceability  
✓ Achieve 100% requirements traceability (mandatory SIL 3-4)  
✓ Obtain independent review and approval (SIL 3-4)

**Key Success Factors**:
- **Use the standard template** (consistency, completeness)
- **Document quantitative criteria** (testable, verifiable)
- **Maintain 100% traceability** (RTM up-to-date)
- **Apply Table A.2 techniques** (structured methodology, modelling)
- **Independent review for SIL 3-4** (separate verifier, validator)

**Next Steps After SRS Approval**:
1. **Architecture & Design Phase** (Phase 3) - Create Software Architecture Specification (SAS) based on approved SRS
2. **Test Planning** - Create Overall Software Test Specification based on approved SRS
3. **Traceability** - Continue forward traceability (SRS → SAS → SDS → Code → Tests)

---

**END OF WORKFLOW**
