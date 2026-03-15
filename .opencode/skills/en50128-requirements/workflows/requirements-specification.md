# Requirements Specification Workflow

**Purpose**: Create the formal Software Requirements Specification (SRS) document compliant with EN 50128 Section 7.2.

**EN 50128 Reference**: Section 7.2 Software Requirements Specification

**Deliverable**: Software Requirements Specification (SRS) - DOC-006-SRS

**Role**: Requirements Engineer (REQ)

**Prerequisites**:
- Requirements elicitation completed
- Requirements analysis completed
- Traceability matrices established
- Software Quality Assurance Plan (SQAP) approved
- Software Configuration Management Plan (SCMP) approved

---

## Workflow Overview

```
┌──────────────────────────────────────┐
│ 1. Preparation                       │ Gather materials, review template
├──────────────────────────────────────┤
│ 2. Document Structure Setup          │ Create document from template
├──────────────────────────────────────┤
│ 3. Write Introduction                │ Purpose, scope, definitions
├──────────────────────────────────────┤
│ 4. Document Requirements             │ Functional, performance, interface, safety, quality
├──────────────────────────────────────┤
│ 5. Add Traceability Matrices         │ System→Software, Hazards→Safety, Requirements→Tests
├──────────────────────────────────────┤
│ 6. Add Supporting Information        │ Glossary, abbreviations, references
├──────────────────────────────────────┤
│ 7. Internal Review                   │ Self-review, peer review
├──────────────────────────────────────┤
│ 8. Quality Assurance Review          │ QUA template + quality check
├──────────────────────────────────────┤
│ 9. Verification Review (SIL 3-4)     │ Independent VER review
├──────────────────────────────────────┤
│ 10. Validation Review                │ VAL approval
├──────────────────────────────────────┤
│ 11. Finalize and Baseline            │ CM baseline creation
└──────────────────────────────────────┘
```

---

## Workflow Steps

### 1. Preparation Phase

**Objective**: Gather all necessary inputs and understand requirements

#### 1.1 Review Input Documents
- [ ] System Requirements Specification (if external system)
- [ ] Hazard Log (for safety requirements)
- [ ] Software Quality Assurance Plan (SQAP) - quality standards, document ID scheme
- [ ] Software Configuration Management Plan (SCMP) - version control, baseline process
- [ ] Stakeholder requirements (from elicitation)
- [ ] Requirements register (collected raw requirements)

#### 1.2 Review SRS Template
- [ ] Locate template: `.opencode/skills/en50128-requirements/templates/Software-Requirements-Specification-template.md`
- [ ] Review required sections per EN 50128 Section 7.2
- [ ] Review SIL-specific requirements (from deliverable metadata: `deliverables/requirements/Software-Requirements-Specification.yaml`)

**Key Template Sections**:
1. Document Control (header, version, approvals)
2. Introduction (purpose, scope, definitions, references)
3. Functional Requirements
4. Performance Requirements
5. Interface Requirements
6. Safety Requirements (SIL 1+)
7. Quality Requirements
8. Constraints
9. Traceability Matrix (SIL 3+ mandatory)

#### 1.3 Identify SIL Level and Techniques
- [ ] Confirm project SIL level (0, 1, 2, 3, or 4)
- [ ] Review EN 50128 Table A.2 techniques for SIL level:
  - **SIL 0**: Techniques optional
  - **SIL 1-2**: Structured Methodology, Modelling, Decision Tables (Recommended)
  - **SIL 3-4**: Formal Methods, Structured Methodology, Modelling, Decision Tables (Highly Recommended)

---

### 2. Document Structure Setup

**Objective**: Create SRS document from template with proper header

#### 2.1 Copy Template
- [ ] Copy template to project document location: `docs/SRS/Software-Requirements-Specification.md`
- [ ] Rename file if needed (maintain `.md` extension)

**Command**:
```bash
mkdir -p docs/SRS
cp .opencode/skills/en50128-requirements/templates/Software-Requirements-Specification-template.md \
   docs/SRS/Software-Requirements-Specification.md
```

#### 2.2 Fill in Document Header
- [ ] **Document ID**: Format `DOC-006-SRS-[PROJECT]-001` (per SQAP document ID scheme)
- [ ] **Title**: "Software Requirements Specification"
- [ ] **Project Name**: Your railway project name (e.g., "Train Control System")
- [ ] **Prepared By**: Requirements Engineer name
- [ ] **SIL**: Safety Integrity Level (0, 1, 2, 3, or 4)
- [ ] **Date**: Current date

**Example Header**:
```markdown
# Software Requirements Specification

**Document ID**: DOC-006-SRS-TCS-001  
**Project**: Train Control System  
**Prepared By**: Jane Smith (Requirements Engineer)  
**Date**: 2026-03-13  
**SIL**: 3  
**Status**: Draft

---

## DOCUMENT CONTROL

| Version | Date | Author | Change Description | Status |
|---------|------|--------|--------------------|--------|
| 0.1 | 2026-03-13 | J. Smith | Initial draft | Draft |
| | | | | |

---

## APPROVALS

| Role | Name | Signature | Date | SIL Requirement |
|------|------|-----------|------|-----------------|
| Author (REQ) | Jane Smith | | | All SILs |
| Verifier (VER) | | | | SIL 3-4 Mandatory |
| Validator (VAL) | | | | SIL 3-4 Mandatory |
| Project Manager (PM) | | | | All SILs |
```

---

### 3. Write Introduction Section

**Objective**: Provide context and overview of SRS document

#### 3.1 Purpose (Section 1.1)
- [ ] State purpose of this document
- [ ] Identify intended audience
- [ ] Describe how document will be used

**Example**:
```markdown
### 1.1 Purpose

This Software Requirements Specification (SRS) defines the software requirements
for the Train Control System (TCS) in accordance with EN 50128:2011 Section 7.2.

This document is intended for:
- Software designers (for architecture and design)
- Software implementers (for coding)
- Software testers (for test planning and execution)
- Software verifiers (for verification planning)
- Software validators (for validation planning)
- Project management (for planning and tracking)

This document serves as the baseline for all subsequent software development
activities (design, implementation, testing, verification, validation).
```

#### 3.2 Scope (Section 1.2)
- [ ] Define scope of software system
- [ ] Identify what is **in scope**
- [ ] Identify what is **out of scope**
- [ ] Describe system boundaries

**Example**:
```markdown
### 1.2 Scope

**In Scope:**
- Speed sensor data acquisition and validation
- Overspeed detection and emergency braking control
- Train position determination via GPS and odometer
- Communication with central control via CAN bus
- Operator interface (display and controls)
- Safety monitoring and fault detection
- Data logging and diagnostics

**Out of Scope:**
- Hardware design (sensors, actuators, control unit)
- Mechanical braking system design
- Power supply and electrical distribution
- Central control station software (separate system)
- Passenger information and entertainment systems

**System Boundaries:**
- Input interfaces: Speed sensors, GPS, odometer, operator controls
- Output interfaces: Brake actuators, throttle control, display, CAN bus
- Safety functions: Overspeed detection, collision avoidance, emergency braking
```

#### 3.3 Definitions and Abbreviations (Section 1.3)
- [ ] Define technical terms used in document
- [ ] List abbreviations and acronyms
- [ ] Reference SQAP glossary if available

**Example**:
```markdown
### 1.3 Definitions and Abbreviations

**Definitions:**
- **Safe State**: A system state where no hazard can occur (e.g., emergency brake applied, power off)
- **Safety-Critical Function**: A function whose failure could result in a hazardous event
- **Safety Integrity Level (SIL)**: Discrete level (0-4) for specifying safety requirements

**Abbreviations:**
- **CAN**: Controller Area Network
- **EN**: European Norm (European Standard)
- **GPS**: Global Positioning System
- **MTBF**: Mean Time Between Failures
- **SIL**: Safety Integrity Level
- **SRS**: Software Requirements Specification
- **TCS**: Train Control System
- **WCET**: Worst-Case Execution Time
```

#### 3.4 References (Section 1.4)
- [ ] List all referenced documents
- [ ] Include document IDs, titles, versions
- [ ] Reference EN 50128:2011 standard

**Example**:
```markdown
### 1.4 References

| Ref | Document ID | Title | Version |
|-----|-------------|-------|---------|
| [1] | EN 50128:2011 | Railway applications - Software for railway control and protection systems | 2011 |
| [2] | DOC-001-SQAP-TCS-001 | Software Quality Assurance Plan | 1.0 |
| [3] | DOC-003-SCMP-TCS-001 | Software Configuration Management Plan | 1.0 |
| [4] | SYSTEM-REQ-001 | Train Control System Requirements Specification | 2.0 |
| [5] | HAZARD-LOG-001 | Hazard Log | 1.5 |
| [6] | MISRA-C:2012 | Guidelines for the use of the C language in critical systems | March 2013 |
```

---

### 4. Document Requirements

**Objective**: Write all software requirements in structured format

#### 4.1 Functional Requirements (Section 2)
- [ ] Group by subsystem or functional area
- [ ] For each functional requirement:
  - [ ] Unique ID: `REQ-FUNC-NNN`
  - [ ] Title: Short description
  - [ ] Description: SHALL/SHOULD/MAY statement
  - [ ] Rationale: Why requirement exists
  - [ ] SIL level: 0, 1, 2, 3, or 4
  - [ ] Verification method: Test, Analysis, Inspection, Demonstration
  - [ ] Acceptance criteria: Measurable, testable
  - [ ] Dependencies: Other requirements
  - [ ] Source: System req, stakeholder, hazard

**Template**:
```markdown
## 2. Functional Requirements

### 2.1 Speed Sensor Interface

#### REQ-FUNC-001: Speed Sensor Data Acquisition

**Description:**
The system SHALL read the speed sensor value via SPI interface at address 0x4000
and store the result in a uint16_t variable representing speed in km/h with
range [0, 300] within 10 milliseconds of initiation.

**Rationale:**
Timely and accurate speed data is required for speed control and overspeed
detection functions.

**SIL Level:** 3

**Priority:** Mandatory (M)

**Source:** System Requirement SYS-CTRL-001

**Verification Method:** Test (unit test + hardware integration test)

**Acceptance Criteria:**
1. Speed value read completes within 10 milliseconds (measured)
2. Speed value stored in uint16_t variable with range [0, 300] km/h
3. SPI communication at address 0x4000 verified
4. Error returned if timeout exceeds 10 milliseconds

**Dependencies:**
- None (foundational requirement)

**Traceability:**
- Backward: SYS-CTRL-001 (System requirement for speed monitoring)
- Forward: TC-FUNC-001-01, TC-FUNC-001-02, TC-FUNC-001-03 (test cases)
```

**Repeat for all functional requirements**, grouped by subsystem:
- 2.1 Speed Sensor Interface (REQ-FUNC-001 to REQ-FUNC-010)
- 2.2 Position Determination (REQ-FUNC-011 to REQ-FUNC-020)
- 2.3 Control Logic (REQ-FUNC-021 to REQ-FUNC-030)
- 2.4 Communication Interface (REQ-FUNC-031 to REQ-FUNC-040)
- etc.

#### 4.2 Performance Requirements (Section 3)
- [ ] Timing requirements (response time, latency, throughput)
- [ ] Resource requirements (CPU, memory, storage)
- [ ] Capacity requirements (number of items, data rates)

**Template**:
```markdown
## 3. Performance Requirements

#### REQ-PERF-001: Speed Control Loop Cycle Time

**Description:**
The speed control loop SHALL complete one full cycle (sensor read, validation,
control calculation, actuator command) within 50 milliseconds.

**Rationale:**
Rapid control loop is required for stable and responsive speed control.

**SIL Level:** 3

**Priority:** Mandatory (M)

**Source:** System Requirement SYS-PERF-001

**Verification Method:** Test (timing measurement with oscilloscope)

**Acceptance Criteria:**
1. Control loop cycle time measured ≤ 50 milliseconds in all scenarios
2. Worst-Case Execution Time (WCET) analysis confirms ≤ 50 milliseconds

**Dependencies:**
- REQ-FUNC-001: Speed sensor read (contributes to loop time)
- REQ-FUNC-003: Control calculation (contributes to loop time)
```

#### 4.3 Interface Requirements (Section 4)
- [ ] Hardware interfaces (sensors, actuators, peripherals)
- [ ] Software interfaces (APIs, function calls, data structures)
- [ ] Communication interfaces (CAN, SPI, UART, Ethernet)
- [ ] User interfaces (displays, buttons, touchscreens)

**Template**:
```markdown
## 4. Interface Requirements

### 4.1 Hardware Interfaces

#### REQ-INTF-001: Speed Sensor SPI Interface

**Description:**
The system SHALL communicate with the speed sensor via SPI interface with
the following characteristics:
- SPI Mode: Mode 0 (CPOL=0, CPHA=0)
- Clock frequency: 1 MHz
- Chip select: Active low
- Data format: 16-bit unsigned integer (MSB first)
- Register address: 0x4000

**Rationale:**
SPI interface specification from speed sensor datasheet (HW-SENSOR-001).

**SIL Level:** 3

**Priority:** Mandatory (M)

**Source:** Hardware Specification HW-SENSOR-001

**Verification Method:** Test (integration test with actual hardware)

**Acceptance Criteria:**
1. SPI communication successful with sensor at 1 MHz
2. Correct data format (16-bit unsigned integer)
3. Chip select timing correct (per datasheet)
```

#### 4.4 Safety Requirements (Section 5)
- [ ] Safety functions (hazard detection, mitigation, recovery)
- [ ] Safety constraints (no dynamic memory, no recursion)
- [ ] Fault handling (error detection, safe state transitions)
- [ ] SIL assignments (trace to hazards)

**Note**: Safety requirements MANDATORY for SIL 1+ projects

**Template**:
```markdown
## 5. Safety Requirements

### 5.1 Overspeed Protection

#### REQ-SAFE-010: Overspeed Detection Time

**Description:**
The speed monitoring system SHALL detect when the current speed exceeds
the maximum safe speed limit within 100 milliseconds of the exceedance
occurring.

**Rationale:**
Rapid detection of overspeed condition is critical for timely activation
of emergency braking to prevent collision or derailment.

**SIL Level:** 4

**Priority:** Mandatory (M)

**Source:** Hazard HAZ-005 (Train overspeed - Catastrophic severity)

**Verification Method:** Test (timing measurement + fault injection)

**Acceptance Criteria:**
1. Detection latency measured ≤ 100 milliseconds in all test scenarios
2. No false negatives (all overspeed conditions detected)
3. False positive rate < 0.001% (1 per 100,000 samples)

**Dependencies:**
- REQ-FUNC-001: Speed sensor reading (must have valid speed data)
- REQ-SAFE-011: Emergency brake activation (triggered by detection)

**Traceability:**
- Backward: HAZ-005 (Overspeed hazard - Catastrophic severity)
- Forward: TC-SAFE-010-01, TC-SAFE-010-02, TC-SAFE-010-03 (test cases)
```

#### 4.5 Quality Requirements (Section 6)
- [ ] Reliability (MTBF, fault tolerance)
- [ ] Maintainability (diagnostics, logging, debuggability)
- [ ] Portability (platform independence, if applicable)

**Template**:
```markdown
## 6. Quality Requirements

#### REQ-QUAL-001: System Reliability

**Description:**
The Train Control System software SHALL achieve a Mean Time Between Failures
(MTBF) of at least 10,000 hours of continuous operation.

**Rationale:**
High reliability is required for railway safety-critical systems to minimize
unscheduled maintenance and operational disruptions.

**SIL Level:** 3

**Priority:** Highly Recommended (HR)

**Source:** Stakeholder requirement (Railway Operator)

**Verification Method:** Analysis (reliability modeling + field data)

**Acceptance Criteria:**
1. MTBF ≥ 10,000 hours (calculated from failure data)
2. Failure rate λ ≤ 0.0001 failures/hour
```

#### 4.6 Constraints (Section 7)
- [ ] Design constraints (architecture, patterns, modularity)
- [ ] Implementation constraints (language, coding standards, tools)
- [ ] Regulatory constraints (EN 50128, national regulations)

**Template**:
```markdown
## 7. Constraints

### 7.1 Implementation Constraints

#### REQ-CONS-001: Static Memory Allocation

**Description:**
All data structures SHALL use static memory allocation. Dynamic memory
allocation functions (malloc, calloc, realloc, free) SHALL NOT be used.

**Rationale:**
Dynamic memory allocation can lead to memory leaks, fragmentation, and
non-deterministic behavior, which are unacceptable in safety-critical
systems (EN 50128 Section 7.4.4.3, SIL 2+ constraint).

**SIL Level:** 3

**Priority:** Mandatory (M)

**Source:** EN 50128:2011 Section 7.4.4.3

**Verification Method:** Inspection (code review + static analysis)

**Acceptance Criteria:**
1. No usage of malloc, calloc, realloc, free in source code
2. Static analysis confirms no dynamic memory allocation
3. All arrays and buffers have fixed sizes at compile time
```

---

### 5. Add Traceability Matrices (Section 8)

**Objective**: Provide traceability links to sources and targets

**Note**: Traceability MANDATORY for SIL 3-4 (EN 50128 Table A.9)

#### 5.1 System Requirements to Software Requirements (Backward Traceability)
- [ ] Include CSV or Markdown table: `traceability/system_to_software_requirements.csv`
- [ ] Verify 100% coverage of system requirements (SIL 3-4 mandatory)

**Example**:
```markdown
## 8. Traceability Matrices

### 8.1 System Requirements to Software Requirements

| System Req ID | System Requirement Title | Software Req ID | Coverage |
|---------------|--------------------------|-----------------|----------|
| SYS-CTRL-001 | Speed monitoring and control | REQ-FUNC-001 | Partial |
| SYS-CTRL-001 | Speed monitoring and control | REQ-FUNC-002 | Partial |
| SYS-CTRL-001 | Speed monitoring and control | REQ-FUNC-003 | Partial |
| SYS-SAFE-005 | Emergency braking | REQ-SAFE-010 | Full |
| SYS-SAFE-005 | Emergency braking | REQ-SAFE-011 | Full |
```

**Coverage**: Full (software req fully satisfies system req), Partial (additional SW reqs needed)

#### 5.2 Hazards to Safety Requirements (Backward Traceability)
- [ ] Include CSV or Markdown table: `traceability/hazard_to_safety_requirements.csv`
- [ ] Verify all hazards mitigated

**Example**:
```markdown
### 8.2 Hazards to Safety Requirements

| Hazard ID | Hazard Description | Severity | SIL | Safety Req ID | Mitigation Type |
|-----------|-------------------|----------|-----|---------------|-----------------|
| HAZ-005 | Train overspeed | Catastrophic | 4 | REQ-SAFE-010 | Detection |
| HAZ-005 | Train overspeed | Catastrophic | 4 | REQ-SAFE-011 | Mitigation |
| HAZ-010 | Sensor failure undetected | Critical | 3 | REQ-SAFE-020 | Detection |
```

#### 5.3 Software Requirements to Test Cases (Forward Traceability)
- [ ] Include CSV or Markdown table: `traceability/requirements_to_testcases.csv`
- [ ] Note: Full test case details in Overall Software Test Specification (DOC-007)

**Example**:
```markdown
### 8.3 Software Requirements to Test Cases (Forward Reference)

| Requirement ID | Requirement Title | SIL | Test Case IDs |
|----------------|-------------------|-----|---------------|
| REQ-FUNC-001 | Read speed sensor value | 3 | TC-FUNC-001-01, TC-FUNC-001-02, TC-FUNC-001-03 |
| REQ-SAFE-010 | Overspeed detection time | 4 | TC-SAFE-010-01, TC-SAFE-010-02, TC-SAFE-010-03, TC-SAFE-010-04 |

**Note:** Detailed test case specifications are provided in the Overall Software
Test Specification (DOC-007-TEST-TCS-001).
```

---

### 6. Add Supporting Information

**Objective**: Provide additional context and references

#### 6.1 Glossary (Appendix A)
- [ ] Define all technical terms
- [ ] Reference SQAP glossary if available

#### 6.2 Abbreviations (Appendix B)
- [ ] List all abbreviations used in document

#### 6.3 EN 50128 Techniques Applied (Appendix C)
- [ ] Document which EN 50128 Table A.2 techniques were used
- [ ] Provide examples of technique application

**Example**:
```markdown
## Appendix C: EN 50128 Techniques Applied (Table A.2)

This SRS was developed using the following EN 50128 Table A.2 techniques
(Highly Recommended for SIL 3):

1. **Structured Methodology (D.52)**: Hierarchical decomposition of system
   requirements into software requirements (Section 2-7).

2. **Modelling (Table A.17)**: State machine models for sensor monitoring
   (REQ-FUNC-010, Figure 2.1) and safety monitoring (REQ-SAFE-005, Figure 5.1).

3. **Decision Tables (D.13)**: Decision table for sensor validation logic
   (REQ-SAFE-100, Table 5.2).

4. **Formal Methods (D.28)**: Formal specification for overspeed detection
   (REQ-SAFE-010, Appendix D).
```

---

### 7. Internal Review

**Objective**: Self-review and peer review before formal reviews

#### 7.1 Self-Review by REQ Engineer
- [ ] Use checklist: `resources/requirement-quality-checklist.md`
- [ ] Check all requirements against quality attributes:
  - [ ] Unambiguous
  - [ ] Testable
  - [ ] Clear
  - [ ] Correct
  - [ ] Feasible
  - [ ] Atomic
  - [ ] Necessary
  - [ ] Implementation-free
- [ ] Verify all SHALL/SHOULD/MAY used correctly
- [ ] Verify all SIL assignments justified
- [ ] Verify all traceability links valid

#### 7.2 Peer Review
- [ ] Request review from another REQ engineer (if available)
- [ ] Conduct review meeting
- [ ] Document findings in review record
- [ ] Address findings and update SRS

---

### 8. Quality Assurance Review

**Objective**: QUA verifies document template compliance and quality standards

#### 8.1 Submit to QUA Agent
- [ ] Send SRS to QUA agent for review
- [ ] QUA uses validation tool: `tools/documentation/doc_validator.py`

**QUA Checklist**:
- [ ] Document header compliant with DOCUMENT-HEADER-TEMPLATE.md Section 2
- [ ] Document ID format correct (DOC-006-SRS-[PROJECT]-NNN)
- [ ] DOCUMENT CONTROL table format correct
- [ ] APPROVALS table format correct with SIL-specific roles
- [ ] All required sections present (per template and SIL level)
- [ ] Requirements follow standard format (ID, description, rationale, etc.)
- [ ] All requirements use SHALL/SHOULD/MAY correctly
- [ ] Traceability matrices present (mandatory for SIL 3-4)

**Command**:
```bash
python tools/documentation/doc_validator.py --file docs/SRS/Software-Requirements-Specification.md --sil 3
```

#### 8.2 Address QUA Findings
- [ ] Review QUA report
- [ ] Fix all critical and error-level findings
- [ ] Update SRS document
- [ ] Resubmit to QUA (if needed)

#### 8.3 Obtain QUA Approval
- [ ] QUA signs APPROVALS table
- [ ] QUA approval recorded in configuration management

---

### 9. Verification Review (SIL 3-4 Independent Review)

**Objective**: Independent VER agent verifies requirements are complete, correct, testable

**EN 50128 Requirement**: Independent verification MANDATORY for SIL 3-4

#### 9.1 Submit to VER Agent
- [ ] Send SRS to VER agent for independent verification
- [ ] VER performs technical review (separate from QUA template review)

**VER Checklist**:
- [ ] All requirements are testable (have objective acceptance criteria)
- [ ] All requirements have verification methods defined
- [ ] Traceability is complete (100% for SIL 3-4):
  - [ ] All system requirements covered
  - [ ] All hazards mitigated
  - [ ] All software requirements have test cases (forward reference)
- [ ] SIL assignments are justified (trace to hazards)
- [ ] EN 50128 techniques applied (Table A.2 for SIL level)
- [ ] No ambiguous or untestable requirements
- [ ] C language constraints considered (data types, memory, timing)

#### 9.2 Address VER Findings
- [ ] Review VER report
- [ ] Fix all findings
- [ ] Update SRS document
- [ ] Resubmit to VER (if needed)

#### 9.3 Obtain VER Approval
- [ ] VER signs APPROVALS table (First Check)
- [ ] VER creates Software Requirements Verification Report (DOC-008)
- [ ] VER approval recorded in configuration management

---

### 10. Validation Review

**Objective**: VAL verifies requirements meet stakeholder needs and system requirements

#### 10.1 Submit to VAL Agent
- [ ] Send SRS to VAL agent for validation planning review

**VAL Checklist**:
- [ ] All system requirements addressed
- [ ] All stakeholder needs addressed
- [ ] Requirements are validatable (can be demonstrated in operational environment)
- [ ] Safety requirements trace to hazards
- [ ] Requirements support safety case

#### 10.2 Address VAL Findings
- [ ] Review VAL feedback
- [ ] Update SRS if needed

#### 10.3 Obtain VAL Approval
- [ ] VAL signs APPROVALS table (Second Check)
- [ ] VAL approval recorded in configuration management

---

### 11. Finalize and Baseline

**Objective**: Publish approved SRS and create configuration baseline

#### 11.1 Update Document Status
- [ ] Change status from "Draft" to "Approved"
- [ ] Assign final version number (e.g., v1.0)
- [ ] Update DOCUMENT CONTROL table

**Example**:
```markdown
| Version | Date | Author | Change Description | Status |
|---------|------|--------|--------------------|--------|
| 0.1 | 2026-03-13 | J. Smith | Initial draft | Draft |
| 0.2 | 2026-03-15 | J. Smith | QUA review updates | Under Review |
| 1.0 | 2026-03-20 | J. Smith | VER/VAL approved | Approved |
```

#### 11.2 Create Configuration Baseline
- [ ] Notify Configuration Manager (CM)
- [ ] CM creates baseline: `SRS-v1.0`
- [ ] CM tags in version control: `git tag SRS-v1.0`

**Command**:
```bash
git add docs/SRS/Software-Requirements-Specification.md
git commit -m "SRS v1.0 - Approved by VER and VAL"
git tag SRS-v1.0
git push origin main --tags
```

#### 11.3 Distribute Document
- [ ] Publish SRS to project repository
- [ ] Notify downstream roles:
  - Designer (DES) - for architecture and design
  - Tester (TST) - for test planning
  - Safety Engineer (SAF) - for safety case
  - Validator (VAL) - for validation planning
  - Project Manager (PM) - for planning and tracking

#### 11.4 Record in Lifecycle State
- [ ] Update `LIFECYCLE_STATE.md` (if using COD agent)
- [ ] Mark requirements phase deliverable complete

---

## SIL-Specific Requirements

### SIL 0 (Non-Safety)
- SRS: Recommended but not mandatory
- Traceability: Optional
- Review: Internal review sufficient
- Techniques: Optional

### SIL 1-2 (Safety-Related)
- SRS: MANDATORY
- Traceability: Highly recommended
- Safety requirements section: MANDATORY
- Review: QUA review recommended
- Techniques: At least one from Table A.2 recommended
- MISRA C considerations: MANDATORY for SIL 2

### SIL 3-4 (Safety-Critical)
- SRS: MANDATORY
- Traceability: 100% MANDATORY (system→software, hazards→safety, software→tests)
- Safety requirements section: MANDATORY
- Review: Independent VER review MANDATORY, VAL review MANDATORY
- Techniques: Multiple techniques from Table A.2 HIGHLY RECOMMENDED (Formal Methods, Structured Methodology, Modelling, Decision Tables)
- Formal specification: HIGHLY RECOMMENDED for safety-critical requirements
- C constraints: All safety requirements MUST consider implementation constraints

---

## Quality Checklist

Before submitting for review, verify:

**Document Structure**:
- [ ] All required sections present per template
- [ ] Document header compliant (ID, version, approvals)
- [ ] Consistent formatting throughout

**Requirements Quality**:
- [ ] All requirements have unique IDs
- [ ] All requirements use SHALL/SHOULD/MAY correctly
- [ ] All requirements are unambiguous (single interpretation)
- [ ] All requirements are testable (objective acceptance criteria)
- [ ] All requirements are atomic (one requirement per ID)
- [ ] All requirements are implementation-free (what, not how)

**Completeness**:
- [ ] All system requirements covered (100% for SIL 3-4)
- [ ] All hazards mitigated
- [ ] All interfaces specified
- [ ] All quality attributes specified
- [ ] All constraints identified
- [ ] No TBDs (To Be Determined)

**Traceability**:
- [ ] Backward traceability complete (software→system, safety→hazards)
- [ ] Forward traceability referenced (software→tests)
- [ ] All traceability links valid

**SIL-Specific**:
- [ ] SIL level assigned to all requirements
- [ ] SIL assignments justified
- [ ] EN 50128 techniques applied (per Table A.2)
- [ ] Safety requirements section complete (SIL 1+)
- [ ] 100% traceability (SIL 3-4)

---

## Tools and Templates

**Workflows**:
- `requirements-elicitation.md` - Gather requirements
- `requirements-analysis.md` - Analyze and refine requirements
- `traceability-management.md` - Manage traceability matrices
- `requirements-specification.md` - This workflow

**Resources**:
- `requirement-patterns.md` - Common requirement patterns
- `shall-should-may.md` - Modal verb usage guide
- `testability-guidelines.md` - How to make requirements testable
- `requirement-quality-checklist.md` - Quality verification checklist

**Tools**:
- `tools/requirement-validator.py` - Validate requirement format
- `workspace.py trace validate` - Check traceability completeness
- `workspace.py trace check-gaps` - Find missing traceability links
- `tools/documentation/doc_validator.py` - Validate document template compliance

**Templates**:
- `templates/Software-Requirements-Specification-template.md` - SRS template

---

## Standard References

- **EN 50128:2011 Section 7.2** - Software Requirements Specification
- **EN 50128:2011 Table A.2** - Requirements Specification Techniques
- **EN 50128:2011 Table A.9** - Traceability (MANDATORY SIL 3-4)
- **EN 50128:2011 Annex C Table C.1** - Document Control Summary (DOC-006)

---

## Deliverable

**Document**: Software Requirements Specification (SRS)
**Document ID**: DOC-006-SRS-[PROJECT]-001
**Template**: `.opencode/skills/en50128-requirements/templates/Software-Requirements-Specification-template.md`
**Deliverable Metadata**: `deliverables/requirements/Software-Requirements-Specification.yaml`

---

## Next Steps

After SRS is approved and baselined:
1. Designer (DES) creates Software Architecture Specification (DOC-009) based on SRS
2. Tester (TST) creates Overall Software Test Specification (DOC-007) based on SRS
3. Safety Engineer (SAF) updates safety case with software safety requirements
4. Lifecycle Coordinator (COD) performs gate check to authorize transition to design phase
