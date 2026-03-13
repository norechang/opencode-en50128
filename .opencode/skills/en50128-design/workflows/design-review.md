# Design Review Workflow

**Purpose**: Guide reviewers through the design review process for Software Architecture Specifications, Software Design Specifications, and Software Interface Specifications per EN 50128 requirements.

**EN 50128 Reference**: Section 6.2 (Verification), Section 7.3 (Design)

**Applicable Documents**:
- Software Architecture Specification (SAS) - DOC-009-SAS
- Software Design Specification (SDS) - DOC-010-SDS
- Software Interface Specifications (SIS) - DOC-011-SIS

**Roles**: PEER (all SILs), QUA (all SILs), SAFETY_MGR (SIL 3-4), VER (SIL 3-4), VAL (SIL 3-4), PM (all SILs)

**Prerequisites**:
- Design document completed by Designer (DES)
- Design document submitted for review (Draft → Review state)
- All prerequisite documents approved (SRS, SQAP, SCMP, SVP)
- Traceability matrix complete (SIL 3-4)

---

## Review Workflow Overview

### SIL-Dependent Review Workflows

**SIL 0-2** (4 reviews):
```
┌──────────────────────────────────────┐
│ 1. Author Self-Review                │ DES reviews own work
├──────────────────────────────────────┤
│ 2. Peer Review                       │ PEER (another designer/engineer)
├──────────────────────────────────────┤
│ 3. Quality Assurance Review          │ QUA (template, quality, compliance)
├──────────────────────────────────────┤
│ 4. Project Manager Approval          │ PM (final approval)
└──────────────────────────────────────┘
```

**SIL 3-4** (8 reviews):
```
┌──────────────────────────────────────┐
│ 1. Author Self-Review                │ DES reviews own work
├──────────────────────────────────────┤
│ 2. Peer Review                       │ PEER (another designer/engineer)
├──────────────────────────────────────┤
│ 3. Quality Assurance Review          │ QUA (template, quality, compliance)
├──────────────────────────────────────┤
│ 4. Safety Manager Review             │ SAFETY_MGR (safety requirements, defensive programming)
├──────────────────────────────────────┤
│ 5. Independent Verification          │ VER (static analysis, complexity, MISRA C design)
├──────────────────────────────────────┤
│ 6. Validation Review                 │ VAL (testability, acceptance criteria)
├──────────────────────────────────────┤
│ 7. Assessor Review (Optional)        │ ASSESSOR (if required by contract/regulation)
├──────────────────────────────────────┤
│ 8. Project Manager Approval          │ PM (final approval)
└──────────────────────────────────────┘
```

---

## Review Process Flow

### Workflow Manager Integration

**Submit Design for Review**:
```bash
# Designer submits document for review
workspace.py workflow submit Software-Architecture-Specification --for-review

# System transitions document to "Review" state
# System notifies reviewers based on SIL level
```

**Review and Approve**:
```bash
# Each reviewer approves with comments
workspace.py workflow review Software-Architecture-Specification \
  --role PEER \
  --approve \
  --comment "Architecture is well-structured, modules have clear responsibilities, cyclomatic complexity within limits"
```

**Review and Reject**:
```bash
# Reviewer rejects with detailed issues
workspace.py workflow review Software-Architecture-Specification \
  --role QUA \
  --reject \
  --comment "Issues found: (1) Traceability incomplete - 5 requirements not traced to architecture components, (2) Module 'DataProcessor' complexity = 12 (exceeds SIL 3 limit of 10), (3) Defensive programming missing in hardware interface module"
```

**Check Review Status**:
```bash
# View all approvals and pending reviews
workspace.py workflow status Software-Architecture-Specification --approvals
```

---

## Review Steps

### 1. Author Self-Review

**Role**: Designer (DES)  
**Objective**: Ensure design document is complete, correct, and ready for peer review

**EN 50128 Reference**: Section 6.5 (Quality Assurance), Table A.9 (Software Quality Assurance Measures)

#### 1.1 Completeness Check

- [ ] **Document Header Complete**:
  - [ ] Document ID follows SQAP scheme (e.g., DOC-009-SAS-TCS-001)
  - [ ] Document Control table with version, date, author, changes
  - [ ] Approvals table with SIL-appropriate roles
  - [ ] Project name, SIL level, status

- [ ] **All Required Sections Present** (per template):
  - [ ] Introduction (purpose, scope, definitions, references)
  - [ ] Architecture/design description
  - [ ] Component/module specifications
  - [ ] Interface specifications
  - [ ] Data structures and types
  - [ ] Error handling approach
  - [ ] Performance and resource requirements
  - [ ] Safety requirements implementation
  - [ ] Traceability matrix (SIL 3-4 mandatory)

- [ ] **All TODOs Resolved**:
  - [ ] No `TODO`, `FIXME`, `XXX`, `TBD` markers in document
  - [ ] All placeholder sections filled in
  - [ ] All diagrams complete and labeled

#### 1.2 Correctness Check

- [ ] **Requirements Traceability**:
  - [ ] Every software requirement from SRS is traced to architecture component OR design element
  - [ ] Traceability matrix is complete (100% for SIL 3-4)
  - [ ] Bidirectional traceability: Requirements → Design AND Design → Requirements
  - [ ] No orphaned design elements (design without requirement)

**Tool Integration**:
```bash
# Validate requirements-to-architecture traceability
traceability.py validate --matrix requirements_to_architecture --sil 3

# Check for gaps (requirements without architecture coverage)
traceability.py check-gaps --source SRS --target SAS
```

- [ ] **Architectural/Design Consistency**:
  - [ ] All components referenced in architecture diagrams are documented in component specifications
  - [ ] All interfaces referenced are documented in interface specifications
  - [ ] Data flows are consistent across diagrams and specifications
  - [ ] No contradictions between sections

- [ ] **C Language Constraints Satisfied** (SIL 2+):
  - [ ] Static allocation only (no dynamic memory)
  - [ ] Fixed-width types specified (uint8_t, uint16_t, uint32_t)
  - [ ] No recursion in design
  - [ ] Bounded execution time for all functions
  - [ ] All error handling specified

- [ ] **Cyclomatic Complexity Within Limits**:
  - [ ] SIL 0-1: ≤ 20 per function
  - [ ] SIL 2: ≤ 15 per function
  - [ ] SIL 3-4: ≤ 10 per function
  - [ ] Complex algorithms decomposed into smaller functions

#### 1.3 Safety Requirements Check

- [ ] **Defensive Programming Designed**:
  - [ ] Input validation for all public interfaces (NULL checks, range checks, state checks)
  - [ ] Error detection mechanisms specified (CRC, plausibility checks, hardware fault detection)
  - [ ] Error handling approach defined (return codes, logging, propagation)
  - [ ] Fail-safe behavior specified for all error conditions

- [ ] **Safety Requirements Traced**:
  - [ ] All safety requirements from SRS (Section 5) have corresponding design elements
  - [ ] Safety-critical functions identified and marked in design
  - [ ] Fault detection and diagnostic features designed
  - [ ] Safety monitoring and watchdog mechanisms specified

#### 1.4 EN 50128 Techniques Applied

Check that **MANDATORY** and **HIGHLY RECOMMENDED** techniques from EN 50128 Table A.3 are applied:

**SIL 2+** (MANDATORY):
- [ ] **Modular Approach (Technique 19)**: Architecture is decomposed into well-defined modules with clear interfaces
- [ ] **Structured Methodology (Technique 1)**: Design follows structured approach (hierarchical decomposition, top-down design)

**SIL 3-4** (HIGHLY RECOMMENDED):
- [ ] **Defensive Programming (Technique 2)**: Input validation, error detection, fail-safe design
- [ ] **Fault Detection and Diagnosis (Technique 3)**: Mechanisms for detecting and diagnosing faults
- [ ] **Fully Defined Interface (Technique 7)**: All interfaces completely specified (data types, ranges, error codes)
- [ ] **Information Encapsulation (Technique 4)**: Modules hide internal data and expose only public interfaces
- [ ] **Modelling (Technique 5)**: Architecture/design diagrams (block diagrams, data flow diagrams, state machines)

#### 1.5 MISRA C Design Considerations

- [ ] **Data Types**:
  - [ ] Fixed-width types planned (uint8_t, uint16_t, uint32_t, int8_t, int16_t, int32_t)
  - [ ] No implicit type conversions in design
  - [ ] Character types explicitly signed or unsigned

- [ ] **Memory Management**:
  - [ ] All data structures statically allocated (no malloc/calloc/realloc/free)
  - [ ] Array sizes specified and bounded
  - [ ] Stack usage estimated and within target limits

- [ ] **Control Flow**:
  - [ ] No recursion (highly recommended SIL 3-4)
  - [ ] All loops have bounded iteration counts
  - [ ] No goto statements in design logic

- [ ] **Error Handling**:
  - [ ] All functions return error codes (or use out parameters for errors)
  - [ ] Error handling approach consistent across all modules
  - [ ] Errors propagated or handled at appropriate level

#### 1.6 Review Checklist Execution

Run through **Architecture Review Checklist** (if architecture document):
- Located at: `.opencode/skills/en50128-design/resources/architecture-review-checklist.md`
- Address all checklist items before submitting for peer review

#### 1.7 Fix Issues and Update Document

- [ ] Fix all issues found during self-review
- [ ] Update document version and change log
- [ ] Generate updated traceability matrix (if modified)
- [ ] Commit changes to version control

**Git Commands**:
```bash
# Stage design document changes
git add docs/architecture/Software-Architecture-Specification.md

# Commit with descriptive message
git commit -m "Design: Complete self-review, fix traceability gaps and complexity issues in SAS"

# Push to feature branch
git push origin feature/architecture-design
```

#### 1.8 Submit for Peer Review

**Workflow Manager**:
```bash
# Submit design document for review
workspace.py workflow submit Software-Architecture-Specification --for-review

# System transitions document from "Draft" to "Review" state
# System notifies PEER reviewer
```

**Output**:
- [ ] Design document status: **Review**
- [ ] PEER reviewer notified
- [ ] Self-review comments documented in review notes

---

### 2. Peer Review

**Role**: PEER (another designer or senior engineer)  
**Objective**: Technical review of architecture/design by experienced peer

**EN 50128 Reference**: Section 6.5 (Quality Assurance), Table A.9 Technique 7 (Software Reviews)

**Independence Requirement**:
- PEER reviewer **SHOULD NOT** be the same person as author (DES)
- PEER reviewer **CAN** be from same team/organization (SIL 0-2)
- PEER reviewer **SHOULD** be independent of author for SIL 3-4 (but not as strict as VER/VAL independence)

#### 2.1 Preparation

- [ ] **Receive Review Notification**:
  ```bash
  # Check review assignments
  workspace.py workflow pending-reviews --role PEER --assigned-to me
  ```

- [ ] **Download Design Document**:
  - [ ] Software Architecture Specification (DOC-009)
  - [ ] Software Design Specification (DOC-010)
  - [ ] Software Interface Specifications (DOC-011)

- [ ] **Gather Reference Documents**:
  - [ ] Software Requirements Specification (SRS) - DOC-006
  - [ ] Hazard Log - DOC-014 (for safety requirements)
  - [ ] Software Quality Assurance Plan (SQAP) - DOC-001
  - [ ] EN 50128 Table A.3 (Software Architecture techniques)
  - [ ] MISRA C:2012 Guidelines (for design considerations)

- [ ] **Allocate Review Time**:
  - Small design (< 10 pages): 2-4 hours
  - Medium design (10-30 pages): 4-8 hours
  - Large design (> 30 pages): 8-16 hours

#### 2.2 Architectural/Design Quality Review

**Focus Areas**:

##### 2.2.1 Architectural Structure (if SAS)

- [ ] **Modularity**:
  - [ ] Architecture is decomposed into well-defined modules/components
  - [ ] Each module has a single, clear responsibility
  - [ ] Module boundaries are logical and maintainable
  - [ ] Module sizes are reasonable (500-2000 LOC target per module)

- [ ] **Coupling and Cohesion**:
  - [ ] **Low coupling**: Modules have minimal dependencies on each other
  - [ ] **High cohesion**: Elements within a module are closely related
  - [ ] Interfaces between modules are minimal and well-defined
  - [ ] No circular dependencies between modules

- [ ] **Layering**:
  - [ ] Architecture follows layered structure (application → middleware → drivers → hardware abstraction)
  - [ ] Higher layers depend only on lower layers (no upward dependencies)
  - [ ] Layer boundaries are clear and consistent

- [ ] **Scalability and Maintainability**:
  - [ ] New features can be added without major restructuring
  - [ ] Modules can be tested independently (testability)
  - [ ] Design supports future evolution

**Common Architecture Anti-Patterns to Detect**:
- **God Object**: One module that does everything (violates Single Responsibility Principle)
- **Spaghetti Code**: No clear structure, modules depend on everything
- **Lava Flow**: Dead code or unused components in design
- **Golden Hammer**: Using one pattern/approach for all problems
- **Tight Coupling**: Modules cannot be changed independently

##### 2.2.2 Design Detail (if SDS)

- [ ] **Function Specifications**:
  - [ ] Every function has clear specification (purpose, inputs, outputs, preconditions, postconditions)
  - [ ] Function complexity within limits (≤10 for SIL 3-4, ≤15 for SIL 2)
  - [ ] Function size reasonable (< 50 lines target, < 200 lines maximum)

- [ ] **Data Structures**:
  - [ ] All data structures specified (types, sizes, ranges)
  - [ ] Data structures use fixed-width types (uint8_t, uint16_t, uint32_t)
  - [ ] Array sizes are bounded and justified (no variable-length arrays)
  - [ ] Memory layout considerations documented (alignment, padding for hardware interfaces)

- [ ] **Algorithms**:
  - [ ] Algorithms clearly described (pseudocode, flowcharts, state machines)
  - [ ] Algorithmic complexity analyzed (time and space)
  - [ ] Worst-case execution time (WCET) estimated for safety-critical functions
  - [ ] No recursive algorithms (highly recommended SIL 3-4)

- [ ] **State Machines** (if applicable):
  - [ ] All states defined and documented
  - [ ] All transitions defined with conditions and actions
  - [ ] Invalid state transitions prevented
  - [ ] Initial state and reset behavior specified

##### 2.2.3 Interface Design (if SIS)

- [ ] **Internal Interfaces** (software-to-software):
  - [ ] Function signatures specified (return type, parameters, error codes)
  - [ ] Data types fully defined (no ambiguous types)
  - [ ] Calling conventions documented (who validates inputs, who handles errors)
  - [ ] Shared data structures specified with access rules

- [ ] **Hardware Interfaces** (software-to-hardware):
  - [ ] Memory-mapped I/O addresses specified
  - [ ] Register layouts documented (bit fields, masks, reset values)
  - [ ] Hardware timing requirements specified (setup time, hold time, access latency)
  - [ ] Hardware fault detection specified (parity errors, bus faults, watchdog)

- [ ] **External Interfaces** (software-to-external system):
  - [ ] Communication protocols specified (CAN, UART, Ethernet, etc.)
  - [ ] Message formats defined (byte order, encoding, CRC)
  - [ ] Timing requirements specified (baudrate, timeout, retry)
  - [ ] Error handling specified (malformed messages, timeouts, protocol violations)

- [ ] **HMI Interfaces** (human-machine interface):
  - [ ] Display formats specified (screens, alarms, indicators)
  - [ ] Input methods specified (buttons, touchscreen, keypad)
  - [ ] User feedback specified (visual, audible, tactile)
  - [ ] Safety-critical information presentation specified (alarms, warnings)

#### 2.3 Requirements Traceability Review

- [ ] **Traceability Matrix Completeness**:
  ```bash
  # Validate traceability matrix
  traceability.py validate --matrix requirements_to_architecture --sil 3
  
  # Check for gaps (requirements without design coverage)
  traceability.py check-gaps --source SRS --target SAS
  
  # Check for orphans (design elements without requirement)
  traceability.py check-orphans --source SRS --target SAS
  ```

- [ ] **Traceability Coverage**:
  - [ ] Every software requirement from SRS is traced to design element
  - [ ] Coverage is 100% for SIL 3-4 (mandatory)
  - [ ] Coverage is ≥ 90% for SIL 2 (highly recommended)
  - [ ] Coverage is ≥ 80% for SIL 0-1 (recommended)

- [ ] **Traceability Accuracy**:
  - [ ] Trace links are accurate (design element actually implements requirement)
  - [ ] Trace links are complete (all aspects of requirement covered)
  - [ ] No incorrect trace links (design element does not match requirement)

- [ ] **Requirements Coverage Analysis**:
  - [ ] All functional requirements have corresponding design elements
  - [ ] All performance requirements addressed (timing, throughput, resource limits)
  - [ ] All interface requirements addressed (hardware, software, external, HMI)
  - [ ] All safety requirements addressed (fault detection, error handling, fail-safe behavior)
  - [ ] All quality requirements addressed (reliability, maintainability, testability)

#### 2.4 Safety Requirements Review

- [ ] **Defensive Programming**:
  - [ ] Input validation specified for all public interfaces:
    - [ ] NULL pointer checks (all pointer parameters)
    - [ ] Range checks (all numeric parameters within valid range)
    - [ ] State checks (function called in valid state)
    - [ ] Bounds checks (array indices within bounds)
  - [ ] Return value checking specified (all function calls checked for errors)
  - [ ] Defensive copies specified (data not modified unexpectedly)

- [ ] **Error Detection**:
  - [ ] Hardware fault detection specified:
    - [ ] Memory faults (ECC, parity, checksums)
    - [ ] Communication faults (CRC, parity, timeout)
    - [ ] Sensor faults (plausibility checks, redundancy)
    - [ ] Processor faults (watchdog, dual execution)
  - [ ] Software fault detection specified:
    - [ ] Assertion checks (invariants verified)
    - [ ] Range checks (data within expected range)
    - [ ] Sequence checks (operations in correct order)

- [ ] **Error Handling**:
  - [ ] Error return codes defined (success, errors, severity levels)
  - [ ] Error propagation approach specified (return to caller, log and continue, fail-safe)
  - [ ] Error recovery actions specified (retry, fallback, shutdown)
  - [ ] Fail-safe behavior specified (safe state on unrecoverable error)

- [ ] **Safety-Critical Functions Identified**:
  - [ ] Functions that implement safety requirements marked as safety-critical
  - [ ] Safety-critical functions have extra scrutiny (complexity, testing, reviews)
  - [ ] Safety-critical data protected (checksums, redundancy, validation)

**Example Safety Design Pattern**:
```c
// Defensive programming pattern for safety-critical function
error_t SafeCriticalFunction(const sensor_data_t* sensor_data, control_output_t* output) {
    // Input validation (defensive programming)
    if (sensor_data == NULL) return ERROR_NULL_POINTER;
    if (output == NULL) return ERROR_NULL_POINTER;
    if (sensor_data->timestamp < last_timestamp) return ERROR_STALE_DATA;
    
    // Plausibility check (error detection)
    if (sensor_data->speed > MAX_PLAUSIBLE_SPEED) {
        log_error("Sensor data plausibility check failed");
        return ERROR_IMPLAUSIBLE_DATA;
    }
    
    // Range check (error detection)
    if (sensor_data->speed < 0 || sensor_data->speed > MAX_SPEED) {
        log_error("Sensor data out of range");
        return ERROR_OUT_OF_RANGE;
    }
    
    // Safety-critical computation
    if (sensor_data->speed > OVERSPEED_THRESHOLD) {
        // Fail-safe behavior: activate emergency brake
        output->emergency_brake = BRAKE_ACTIVE;
        log_warning("Overspeed detected, emergency brake activated");
    } else {
        output->emergency_brake = BRAKE_INACTIVE;
    }
    
    return SUCCESS;
}
```

#### 2.5 MISRA C Design Review

- [ ] **MISRA C Compliance Considerations**:
  - [ ] Fixed-width types used consistently (uint8_t, uint16_t, uint32_t)
  - [ ] No implicit type conversions in design
  - [ ] No pointer arithmetic (use array indexing)
  - [ ] No function pointers (highly recommended SIL 3-4)
  - [ ] No recursion (highly recommended SIL 3-4)
  - [ ] No dynamic memory allocation (mandatory SIL 2+)

- [ ] **MISRA C Design Violations**:
  - [ ] If MISRA C deviations are planned, they must be justified and documented
  - [ ] Deviations must have rationale (why deviation is necessary)
  - [ ] Deviations must have approval (from Safety Manager or QA)
  - [ ] Deviations tracked in MISRA C Deviation Log

#### 2.6 Complexity Review

- [ ] **Cyclomatic Complexity**:
  - [ ] All functions within SIL-appropriate limits:
    - SIL 0-1: ≤ 20
    - SIL 2: ≤ 15
    - SIL 3-4: ≤ 10
  - [ ] Complex functions decomposed into smaller functions
  - [ ] Complexity analysis documented in design

**Cyclomatic Complexity Guide**:
```
Complexity = Number of decision points + 1

Example:
function Process(x) {
    if (x > 10) {        // Decision 1
        if (x < 20) {    // Decision 2
            return x;
        } else {         // Decision 3
            return 20;
        }
    } else {
        return 0;
    }
}
Complexity = 3 + 1 = 4 (acceptable for all SILs)
```

- [ ] **Nesting Depth**:
  - [ ] Control flow nesting ≤ 4 levels (recommended for all SILs)
  - [ ] Deeply nested logic refactored into helper functions

- [ ] **Function Size**:
  - [ ] Functions < 50 lines (target)
  - [ ] Functions < 200 lines (maximum)
  - [ ] Large functions justified and documented

#### 2.7 Performance and Resource Review

- [ ] **Timing Requirements**:
  - [ ] Worst-case execution time (WCET) estimated for all functions
  - [ ] Timing requirements met (from SRS performance requirements)
  - [ ] Timing analysis approach specified (measurement, static analysis, calculation)

- [ ] **Memory Requirements**:
  - [ ] RAM usage estimated (stack + data + heap)
  - [ ] ROM/Flash usage estimated (code + constants)
  - [ ] Memory usage within target limits (from SRS constraints)
  - [ ] Stack usage analyzed for worst-case (deepest call chain)

- [ ] **CPU Usage**:
  - [ ] CPU utilization estimated (percentage of CPU time)
  - [ ] CPU margin available for future enhancements (target ≤ 70% utilization)

#### 2.8 Testability Review

- [ ] **Unit Testability**:
  - [ ] Functions can be tested in isolation (no hidden dependencies)
  - [ ] Function inputs and outputs are observable
  - [ ] Test points identified for internal state verification

- [ ] **Integration Testability**:
  - [ ] Interfaces support integration testing (stimulus and observation)
  - [ ] Integration test approach feasible (bottom-up, top-down, sandwich)

- [ ] **Validation Testability**:
  - [ ] System behavior can be validated against requirements
  - [ ] Test equipment and instrumentation needs identified

#### 2.9 Common Design Issues Checklist

Check for these **common design problems**:

**Architectural Issues**:
- [ ] **Unclear module boundaries**: Modules have overlapping responsibilities
- [ ] **Tight coupling**: Modules cannot be changed independently
- [ ] **Missing error handling**: No error detection or recovery mechanisms
- [ ] **Performance bottlenecks**: Serial processing where parallel would be better
- [ ] **Resource overload**: Memory or CPU usage exceeds target limits

**Design Detail Issues**:
- [ ] **Overly complex functions**: Cyclomatic complexity exceeds limits
- [ ] **Insufficient input validation**: Missing NULL checks, range checks, state checks
- [ ] **Race conditions**: Shared data without synchronization (if multithreaded)
- [ ] **Magic numbers**: Hardcoded constants without named definitions
- [ ] **Incomplete specifications**: Vague function descriptions, undefined error codes

**Interface Issues**:
- [ ] **Ambiguous data types**: Using `int` instead of `uint16_t`
- [ ] **Undefined error codes**: Errors not specified or documented
- [ ] **Missing timing requirements**: Interface timing not specified
- [ ] **Incompatible protocols**: Mismatch between sender and receiver expectations

**Safety Issues**:
- [ ] **No defensive programming**: Missing input validation
- [ ] **No fault detection**: Hardware faults not detected
- [ ] **No fail-safe behavior**: System behavior undefined on errors
- [ ] **Inadequate error handling**: Errors ignored or not propagated

**MISRA C Issues**:
- [ ] **Dynamic memory allocation**: malloc/free used (forbidden SIL 2+)
- [ ] **Recursion**: Functions call themselves (highly recommended to avoid SIL 3-4)
- [ ] **Unbounded loops**: Loop iteration count not bounded
- [ ] **Variable-length arrays**: Array size not fixed at compile-time

#### 2.10 Peer Review Report

Document findings in **Peer Review Report**:

**Template**:
```markdown
# Peer Review Report - [Document Name]

**Reviewer**: [PEER name]
**Date**: [Review date]
**Document**: [Document ID and version]
**Review Duration**: [Hours spent on review]

## Summary

[Overall assessment: Approved / Approved with minor changes / Rejected]

## Strengths

1. [What the design does well]
2. [Positive aspects]
3. [Good practices observed]

## Issues Found

### Critical Issues (must fix before approval)

1. **[Issue title]**
   - **Location**: [Section/page/component]
   - **Description**: [What is wrong]
   - **Impact**: [Why this is critical]
   - **Recommendation**: [How to fix]

2. ...

### Major Issues (should fix)

1. **[Issue title]**
   - **Location**: [Section/page/component]
   - **Description**: [What is wrong]
   - **Impact**: [Potential consequences]
   - **Recommendation**: [How to fix]

2. ...

### Minor Issues (nice to fix)

1. **[Issue title]**
   - **Location**: [Section/page/component]
   - **Description**: [What could be improved]
   - **Recommendation**: [Suggestion]

2. ...

## Checklist Results

- [ ] Modularity: [Pass/Fail/N/A]
- [ ] Traceability: [Pass/Fail/N/A]
- [ ] Defensive Programming: [Pass/Fail/N/A]
- [ ] Complexity: [Pass/Fail/N/A]
- [ ] MISRA C Design: [Pass/Fail/N/A]
- [ ] Testability: [Pass/Fail/N/A]

## Recommendation

[Approved / Approved with changes / Rejected with rework required]

## Reviewer Signature

[Name, Date, Role]
```

#### 2.11 Submit Review Decision

**Approve**:
```bash
# Approve design document
workspace.py workflow review Software-Architecture-Specification \
  --role PEER \
  --approve \
  --comment "Architecture is well-structured with clear module boundaries. Traceability is complete. Complexity within limits. Defensive programming patterns applied. Recommend approval."
```

**Reject**:
```bash
# Reject design document with issues
workspace.py workflow review Software-Architecture-Specification \
  --role PEER \
  --reject \
  --comment "Critical issues found: (1) Module DataProcessor has cyclomatic complexity 14 (exceeds SIL 3 limit of 10), (2) Hardware interface module missing defensive programming (no NULL checks), (3) Traceability incomplete (5 requirements not traced). Recommend rework and resubmission."
```

---

### 3. Quality Assurance Review

**Role**: Quality Assurance (QUA)  
**Objective**: Verify design document compliance with templates, standards, and quality criteria

**EN 50128 Reference**: Section 6.5 (Software Quality Assurance), Table A.9 (QA Measures)

**Independence Requirement**:
- QUA **MUST BE** independent of Designer (different person)
- QUA **CAN** be from same organization (all SILs)

#### 3.1 Preparation

- [ ] **Receive QUA Review Notification**:
  ```bash
  # Check QUA review assignments
  workspace.py workflow pending-reviews --role QUA --assigned-to me
  ```

- [ ] **Download Design Document** (already peer-reviewed)

- [ ] **Gather QA References**:
  - [ ] Software Quality Assurance Plan (SQAP) - DOC-001
  - [ ] Design document template
  - [ ] EN 50128 Section 7.3 (Architecture and Design)
  - [ ] EN 50128 Table A.3 (Architecture techniques)
  - [ ] MISRA C:2012 Guidelines

#### 3.2 Template Compliance Check

- [ ] **Document ID Format** (per SQAP):
  - [ ] Format: `DOC-009-SAS-[PROJECT]-[NNN]` (Architecture)
  - [ ] Format: `DOC-010-SDS-[PROJECT]-[NNN]` (Design)
  - [ ] Format: `DOC-011-SIS-[PROJECT]-[NNN]` (Interfaces)
  - [ ] PROJECT code is consistent across all documents
  - [ ] Document number (NNN) is unique and sequential

- [ ] **Document Control Table Present**:
  - [ ] Version column (e.g., 0.1, 1.0, 1.1)
  - [ ] Date column (ISO 8601 format: YYYY-MM-DD)
  - [ ] Author column (full name and role)
  - [ ] Change Description column (description of changes)
  - [ ] Status column (Draft, Review, Approved, Baseline)

- [ ] **Approvals Table Present with SIL-Appropriate Roles**:
  - **SIL 0-2**: Author (DES), PEER, QUA, PM
  - **SIL 3-4**: Author (DES), PEER, QUA, SAFETY_MGR, VER, VAL, PM (and optionally ASSESSOR)

- [ ] **All Required Sections Present** (per template):
  - [ ] Section 1: Introduction (Purpose, Scope, Definitions, References)
  - [ ] Section 2: Architecture/Design Overview
  - [ ] Section 3: Component/Module Specifications
  - [ ] Section 4: Interface Specifications
  - [ ] Section 5: Data Structures and Types
  - [ ] Section 6: Error Handling
  - [ ] Section 7: Performance and Resources
  - [ ] Section 8: Safety Requirements
  - [ ] Section 9: Traceability Matrix (SIL 3-4 mandatory)

- [ ] **Section Numbering Consistent**:
  - [ ] Sections numbered consecutively (1, 2, 3, ...)
  - [ ] Subsections numbered correctly (1.1, 1.2, 1.3, ...)
  - [ ] No skipped numbers

- [ ] **References Complete**:
  - [ ] All referenced documents listed in References section
  - [ ] Document IDs correct (e.g., DOC-006-SRS)
  - [ ] References formatted consistently

#### 3.3 Content Quality Check

- [ ] **Writing Quality**:
  - [ ] Language is clear and unambiguous
  - [ ] Technical terms defined or referenced in glossary
  - [ ] Spelling and grammar correct
  - [ ] Consistent terminology (no synonyms for same concept)

- [ ] **Diagram Quality**:
  - [ ] All diagrams have titles and figure numbers
  - [ ] All diagrams have legends/keys (if needed)
  - [ ] Diagram elements are labeled
  - [ ] Diagrams are readable (font size, contrast)

- [ ] **Table Quality**:
  - [ ] All tables have titles and table numbers
  - [ ] Table headers present
  - [ ] Table data is complete (no empty cells without explanation)

- [ ] **Traceability Quality** (SIL 3-4):
  - [ ] Traceability matrix is machine-readable (CSV or Markdown table)
  - [ ] Traceability matrix is complete (no gaps)
  - [ ] Traceability matrix is accurate (links verified)

#### 3.4 EN 50128 Compliance Check

- [ ] **Mandatory Techniques Applied** (EN 50128 Table A.3):
  - **SIL 2+**:
    - [ ] Modular Approach (19): Architecture decomposed into modules
  - **SIL 3-4**:
    - [ ] Structured Methodology (1): Structured design approach
    - [ ] Modular Approach (19): Architecture decomposed into modules

- [ ] **Highly Recommended Techniques Applied** (SIL 3-4):
  - [ ] Defensive Programming (2): Input validation, error detection
  - [ ] Fault Detection and Diagnosis (3): Fault detection mechanisms
  - [ ] Fully Defined Interface (7): All interfaces completely specified
  - [ ] Information Encapsulation (4): Data hiding, public interfaces
  - [ ] Modelling (5): Architecture/design diagrams

- [ ] **Technique Application Documented**:
  - [ ] Document explicitly states which EN 50128 techniques are used
  - [ ] Evidence of technique application in document (e.g., modularity shown in architecture diagram)

#### 3.5 MISRA C Design Compliance

- [ ] **Static Allocation Only** (SIL 2+):
  - [ ] No dynamic memory allocation in design (malloc, calloc, realloc, free)
  - [ ] All data structures have fixed sizes
  - [ ] Array sizes specified and bounded

- [ ] **Fixed-Width Types**:
  - [ ] All data types specified with fixed-width types (uint8_t, uint16_t, uint32_t)
  - [ ] No ambiguous types (int, long, short)

- [ ] **No Recursion** (highly recommended SIL 3-4):
  - [ ] No recursive function calls in design
  - [ ] Call graphs are acyclic

- [ ] **Bounded Execution Time**:
  - [ ] All loops have bounded iteration counts
  - [ ] Worst-case execution time (WCET) estimated

#### 3.6 Complexity Compliance

- [ ] **Cyclomatic Complexity Within Limits**:
  - [ ] SIL 0-1: All functions ≤ 20 complexity
  - [ ] SIL 2: All functions ≤ 15 complexity
  - [ ] SIL 3-4: All functions ≤ 10 complexity

- [ ] **Complexity Analysis Documented**:
  - [ ] Complexity estimates provided for complex functions
  - [ ] Complexity reduction approach documented (if needed)

#### 3.7 Traceability Compliance (SIL 3-4 Mandatory)

- [ ] **Traceability Matrix Present**:
  - [ ] Requirements-to-Architecture matrix (for SAS)
  - [ ] Requirements-to-Design matrix (for SDS)
  - [ ] Requirements-to-Interface matrix (for SIS)

- [ ] **Traceability Coverage**:
  - [ ] 100% coverage for SIL 3-4 (mandatory)
  - [ ] ≥ 90% coverage for SIL 2 (highly recommended)
  - [ ] ≥ 80% coverage for SIL 0-1 (recommended)

**Tool Validation**:
```bash
# Validate traceability matrix
traceability.py validate --matrix requirements_to_architecture --sil 3

# Generate traceability report
traceability.py report --matrix requirements_to_architecture --format markdown --output traceability-report.md
```

#### 3.8 Safety Requirements Compliance

- [ ] **Safety Requirements Addressed**:
  - [ ] All safety requirements from SRS (Section 5) have corresponding design elements
  - [ ] Safety-critical functions identified
  - [ ] Defensive programming applied to safety-critical functions

- [ ] **Defensive Programming Specified**:
  - [ ] Input validation for all public interfaces
  - [ ] Error detection mechanisms specified
  - [ ] Error handling approach defined
  - [ ] Fail-safe behavior specified

#### 3.9 Configuration Management Compliance

- [ ] **Version Control**:
  - [ ] Document committed to Git repository
  - [ ] Commit messages descriptive
  - [ ] Branch naming follows convention (e.g., `feature/architecture-design`)

- [ ] **Change Management**:
  - [ ] Changes to baseline require Change Request (CR)
  - [ ] Change history documented in Document Control table

#### 3.10 Quality Metrics

- [ ] **Document Size Reasonable**:
  - [ ] SAS: 20-50 pages typical
  - [ ] SDS: 30-100 pages typical (depends on component count)
  - [ ] SIS: 10-30 pages typical (depends on interface count)

- [ ] **Review Efficiency**:
  - [ ] No excessive rework iterations (≤ 2 iterations target)
  - [ ] Issues found in peer review addressed

#### 3.11 QA Review Report

Document QA findings in **QA Review Report**:

**Template**:
```markdown
# Quality Assurance Review Report - [Document Name]

**QA Reviewer**: [QUA name]
**Date**: [Review date]
**Document**: [Document ID and version]
**SIL**: [0/1/2/3/4]

## Summary

[Overall QA assessment: Pass / Pass with minor corrections / Fail]

## Template Compliance

- [ ] Document ID format correct
- [ ] Document Control table complete
- [ ] Approvals table with SIL-appropriate roles
- [ ] All required sections present
- [ ] Section numbering consistent
- [ ] References complete

**Result**: [Pass/Fail]

## Content Quality

- [ ] Writing quality (clear, unambiguous)
- [ ] Diagram quality (titled, labeled, readable)
- [ ] Table quality (titled, complete)
- [ ] Traceability quality (complete, accurate)

**Result**: [Pass/Fail]

## EN 50128 Compliance

- [ ] Mandatory techniques applied (SIL 2+: Modular Approach; SIL 3-4: Structured Methodology)
- [ ] Highly Recommended techniques applied (SIL 3-4: Defensive Programming, Fault Detection, Fully Defined Interface, etc.)
- [ ] Technique application documented

**Result**: [Pass/Fail]

## MISRA C Design Compliance

- [ ] Static allocation only (SIL 2+)
- [ ] Fixed-width types
- [ ] No recursion (SIL 3-4 HR)
- [ ] Bounded execution time

**Result**: [Pass/Fail]

## Complexity Compliance

- [ ] Cyclomatic complexity within limits (SIL 0-1: ≤20, SIL 2: ≤15, SIL 3-4: ≤10)
- [ ] Complexity analysis documented

**Result**: [Pass/Fail]

## Traceability Compliance (SIL 3-4)

- [ ] Traceability matrix present
- [ ] Traceability coverage 100% (SIL 3-4)
- [ ] Traceability validated with tool

**Result**: [Pass/Fail]

## Issues Found

### Critical Issues (block approval)

1. [Issue description with section reference]
2. ...

### Minor Issues (corrections needed)

1. [Issue description with section reference]
2. ...

## Recommendation

[Pass / Pass with corrections / Fail (rework required)]

## QA Signature

[Name, Date, Role]
```

#### 3.12 Submit QA Decision

**Pass**:
```bash
# QA approval
workspace.py workflow review Software-Architecture-Specification \
  --role QUA \
  --approve \
  --comment "QA review passed. Template compliance verified. EN 50128 techniques applied. MISRA C design compliant. Complexity within limits. Traceability 100% (SIL 3). No critical issues found."
```

**Pass with Corrections**:
```bash
# QA approval with minor corrections
workspace.py workflow review Software-Architecture-Specification \
  --role QUA \
  --approve \
  --comment "QA review passed with minor corrections needed: (1) Fix typo in Section 3.2, (2) Add figure number to diagram on page 12, (3) Complete Reference [5] citation. Author to fix before baseline."
```

**Fail**:
```bash
# QA rejection
workspace.py workflow review Software-Architecture-Specification \
  --role QUA \
  --reject \
  --comment "QA review failed. Critical issues: (1) Traceability matrix incomplete (85% coverage, need 100% for SIL 3), (2) Mandatory technique 'Modular Approach' not evidenced in architecture, (3) Cyclomatic complexity not documented for complex functions. Rework required."
```

---

### 4. Safety Manager Review (SIL 3-4 Only)

**Role**: Safety Manager (SAFETY_MGR)  
**Objective**: Verify safety requirements are correctly addressed in design

**EN 50128 Reference**: Section 7.1 (Software Safety Requirements), Section 6.8 (Software Assessment)

**Applicability**: **SIL 3-4 only** (highly recommended for SIL 2)

**Independence Requirement**:
- SAFETY_MGR **SHOULD** be independent of Designer (different person)
- SAFETY_MGR **CAN** be from same organization

#### 4.1 Preparation

- [ ] **Receive Safety Review Notification**:
  ```bash
  # Check safety review assignments
  workspace.py workflow pending-reviews --role SAFETY_MGR --assigned-to me
  ```

- [ ] **Download Design Document** (already peer-reviewed and QUA-reviewed)

- [ ] **Gather Safety References**:
  - [ ] Software Requirements Specification (SRS) - Section 5 (Safety Requirements)
  - [ ] Hazard Log - DOC-014
  - [ ] Failure Mode and Effects Analysis (FMEA) - if available
  - [ ] Fault Tree Analysis (FTA) - if available
  - [ ] EN 50128 Section 7.1 (Software Safety Requirements)
  - [ ] EN 50126 (RAMS standard)

#### 4.2 Safety Requirements Coverage

- [ ] **All Safety Requirements Traced**:
  - [ ] Every safety requirement from SRS Section 5 has corresponding design element
  - [ ] Safety-critical functions identified in design
  - [ ] Safety mechanisms specified (fault detection, error handling, fail-safe)

**Tool Validation**:
```bash
# Validate safety requirements traceability
traceability.py query --requirement-type safety --target SAS

# Check for gaps in safety requirements coverage
traceability.py check-gaps --source SRS --target SAS --requirement-type safety
```

- [ ] **Safety Integrity Level (SIL) Appropriate Design**:
  - [ ] Design rigor matches SIL level (SIL 3-4 requires highest rigor)
  - [ ] Mandatory EN 50128 techniques applied (Modular Approach, Structured Methodology)
  - [ ] Highly Recommended techniques applied (Defensive Programming, Fault Detection, Fully Defined Interface)

#### 4.3 Defensive Programming Review

- [ ] **Input Validation**:
  - [ ] All safety-critical functions validate inputs:
    - [ ] NULL pointer checks (all pointer parameters)
    - [ ] Range checks (all numeric parameters within valid range)
    - [ ] State checks (function called in valid state)
    - [ ] Bounds checks (array indices within bounds)
  - [ ] Invalid inputs detected and rejected (fail-safe)

- [ ] **Return Value Checking**:
  - [ ] All function calls have return values checked
  - [ ] Errors propagated to caller or handled locally
  - [ ] Critical errors trigger fail-safe behavior

- [ ] **Defensive Copies**:
  - [ ] Shared data protected from unexpected modification
  - [ ] Critical data validated before use

**Example Defensive Programming in Design**:
```c
// Safety-critical function design with defensive programming
error_t SafeFunction(const sensor_data_t* sensor, control_output_t* output) {
    // Input validation (defensive programming)
    if (sensor == NULL) {
        log_error("NULL sensor pointer");
        *output = SAFE_STATE;  // Fail-safe
        return ERROR_NULL_POINTER;
    }
    if (output == NULL) {
        log_error("NULL output pointer");
        return ERROR_NULL_POINTER;
    }
    
    // Plausibility check (fault detection)
    if (sensor->speed < 0 || sensor->speed > MAX_PLAUSIBLE_SPEED) {
        log_error("Sensor plausibility check failed");
        *output = SAFE_STATE;  // Fail-safe
        return ERROR_IMPLAUSIBLE_DATA;
    }
    
    // Safety-critical computation
    if (sensor->speed > OVERSPEED_THRESHOLD) {
        output->brake = BRAKE_EMERGENCY;  // Fail-safe action
        log_warning("Overspeed detected, emergency brake");
    } else {
        output->brake = BRAKE_NORMAL;
    }
    
    return SUCCESS;
}
```

#### 4.4 Fault Detection and Diagnosis

- [ ] **Hardware Fault Detection**:
  - [ ] Memory faults detected (ECC, parity, checksums)
  - [ ] Communication faults detected (CRC, parity, timeout, sequence errors)
  - [ ] Sensor faults detected (plausibility checks, range checks, cross-validation)
  - [ ] Processor faults detected (watchdog timer, dual execution, signature analysis)

- [ ] **Software Fault Detection**:
  - [ ] Assertion checks for invariants
  - [ ] Range checks for data validity
  - [ ] Sequence checks for operation order
  - [ ] Timing checks for real-time constraints

- [ ] **Diagnostic Approach**:
  - [ ] Fault detection mechanisms specified
  - [ ] Fault isolation approach specified (which component failed)
  - [ ] Fault logging specified (error codes, timestamps, context)
  - [ ] Fault recovery or fail-safe behavior specified

#### 4.5 Fail-Safe Behavior

- [ ] **Safe State Defined**:
  - [ ] Safe state identified for each subsystem (e.g., brakes applied, power off, isolate fault)
  - [ ] Transition to safe state specified on unrecoverable errors
  - [ ] Safe state maintained until operator intervention

- [ ] **Fail-Safe Design Patterns**:
  - [ ] **Fail-Safe Defaults**: Default to safe values on errors
  - [ ] **Redundancy**: Critical data or functions duplicated
  - [ ] **Voting**: Multiple sources compared, majority wins
  - [ ] **Watchdog**: System reset if software hangs
  - [ ] **Error Containment**: Faults isolated to prevent propagation

#### 4.6 Safety-Critical Functions

- [ ] **Safety-Critical Functions Identified**:
  - [ ] Functions that implement safety requirements marked in design
  - [ ] Safety criticality level specified (critical, important, non-critical)

- [ ] **Safety-Critical Function Design**:
  - [ ] Extra scrutiny applied (complexity, defensive programming, testing)
  - [ ] Cyclomatic complexity ≤ 10 (SIL 3-4)
  - [ ] 100% test coverage required (statement, branch, MC/DC)

#### 4.7 Hazard Mitigation

- [ ] **Hazards from Hazard Log Addressed**:
  - [ ] Each hazard has corresponding mitigation in design
  - [ ] Mitigation effectiveness analyzed (risk reduced to acceptable level)

**Example Hazard-to-Design Traceability**:
```
Hazard: Overspeed condition (train exceeds safe speed limit)
Mitigation Design:
  1. Speed sensor redundancy (2 independent sensors)
  2. Speed plausibility check (cross-validate sensors)
  3. Overspeed detection function (compare speed to threshold)
  4. Emergency brake activation (fail-safe action on overspeed)
  5. Watchdog timer (detect software hang in overspeed detection)
```

#### 4.8 Safety Review Report

Document safety findings in **Safety Review Report**:

**Template**:
```markdown
# Safety Manager Review Report - [Document Name]

**Safety Manager**: [SAFETY_MGR name]
**Date**: [Review date]
**Document**: [Document ID and version]
**SIL**: [3 or 4]

## Summary

[Overall safety assessment: Approved / Approved with changes / Rejected]

## Safety Requirements Coverage

- [ ] All safety requirements from SRS traced to design
- [ ] Safety-critical functions identified
- [ ] Safety mechanisms specified

**Result**: [Pass/Fail]

## Defensive Programming

- [ ] Input validation specified for all safety-critical functions
- [ ] Return value checking specified
- [ ] Defensive copies specified for shared data

**Result**: [Pass/Fail]

## Fault Detection and Diagnosis

- [ ] Hardware fault detection specified
- [ ] Software fault detection specified
- [ ] Diagnostic approach specified

**Result**: [Pass/Fail]

## Fail-Safe Behavior

- [ ] Safe state defined for each subsystem
- [ ] Transition to safe state on errors
- [ ] Fail-safe design patterns applied

**Result**: [Pass/Fail]

## Hazard Mitigation

- [ ] All hazards from Hazard Log addressed
- [ ] Mitigation effectiveness analyzed

**Result**: [Pass/Fail]

## Safety Issues Found

### Critical Safety Issues (must fix)

1. [Issue description with safety impact]
2. ...

### Major Safety Issues (should fix)

1. [Issue description with safety impact]
2. ...

## Recommendation

[Approved / Approved with changes / Rejected (safety concerns)]

## Safety Manager Signature

[Name, Date, Role]
```

#### 4.9 Submit Safety Review Decision

**Approve**:
```bash
# Safety Manager approval
workspace.py workflow review Software-Architecture-Specification \
  --role SAFETY_MGR \
  --approve \
  --comment "Safety review approved. All safety requirements traced. Defensive programming applied to safety-critical functions. Fault detection mechanisms specified. Fail-safe behavior defined. Hazards mitigated."
```

**Reject**:
```bash
# Safety Manager rejection
workspace.py workflow review Software-Architecture-Specification \
  --role SAFETY_MGR \
  --reject \
  --comment "Safety review failed. Critical safety issues: (1) Overspeed detection function missing defensive programming (no sensor plausibility check), (2) Fail-safe behavior not specified for communication timeout, (3) Watchdog mechanism not specified. Rework required."
```

---

### 5. Independent Verification (SIL 3-4 Only)

**Role**: Verifier (VER)  
**Objective**: Independent verification that design meets requirements and EN 50128 standards

**EN 50128 Reference**: Section 6.2 (Software Verification), EN 50128 Section 5.1.2.10 (Independence)

**Applicability**: **SIL 3-4 mandatory** (highly recommended for SIL 2)

**Independence Requirement** (EN 50128 Section 5.1.2.10):
- VER **MUST BE** different person from Designer (DES)
- VER **MUST BE** different person from Implementer (IMP)
- VER **MUST BE** different person from Tester (TST)
- VER **CAN BE** same person as Integrator
- VER **CANNOT BE** same person as Validator (VAL)
- VER **CAN** be from same organization (SIL 3-4)
- VER **REPORTS TO** V&V Manager (VMGR) for SIL 3-4 (not to PM)

#### 5.1 Preparation

- [ ] **Receive VER Review Notification**:
  ```bash
  # Check verification review assignments
  workspace.py workflow pending-reviews --role VER --assigned-to me
  ```

- [ ] **Verify Independence**:
  ```bash
  # Workflow Manager checks independence automatically
  # VER cannot review document authored by self
  ```

- [ ] **Download Design Document** (already peer-reviewed, QUA-reviewed, safety-reviewed)

- [ ] **Gather Verification References**:
  - [ ] Software Requirements Specification (SRS) - DOC-006
  - [ ] Software Verification Plan (SVP) - DOC-004
  - [ ] Hazard Log - DOC-014
  - [ ] EN 50128 Section 6.2 (Verification)
  - [ ] EN 50128 Table A.5 (Verification techniques)
  - [ ] EN 50128 Table A.19 (Static Analysis techniques)

#### 5.2 Verification Objectives

**EN 50128 Section 6.2.2**: Verification shall provide evidence that:
1. Design correctly and completely implements requirements
2. Design is consistent (no internal contradictions)
3. Design is traceable to requirements
4. Design is feasible to implement
5. Design meets EN 50128 quality criteria

#### 5.3 Requirements Verification

- [ ] **Requirements Traceability Verification**:
  - [ ] Every software requirement from SRS is traced to design element (forward traceability)
  - [ ] Every design element is traced to requirement (backward traceability)
  - [ ] Traceability coverage is 100% for SIL 3-4 (mandatory)
  - [ ] Traceability links are accurate (design actually implements requirement)

**Tool-Based Verification**:
```bash
# Validate traceability matrix
traceability.py validate --matrix requirements_to_architecture --sil 3

# Generate traceability verification report
traceability.py report --matrix requirements_to_architecture \
  --format markdown \
  --output verification-traceability-report.md
```

- [ ] **Requirements Coverage Analysis**:
  - [ ] All functional requirements have corresponding design elements
  - [ ] All performance requirements addressed (timing, throughput, resources)
  - [ ] All interface requirements addressed (hardware, software, external, HMI)
  - [ ] All safety requirements addressed (fault detection, error handling, fail-safe)
  - [ ] All quality requirements addressed (reliability, maintainability, testability)
  - [ ] All constraints satisfied (C language, MISRA C, static allocation, no recursion)

#### 5.4 Design Consistency Verification

- [ ] **Internal Consistency**:
  - [ ] All components referenced in architecture diagrams are documented
  - [ ] All interfaces referenced are specified
  - [ ] Data flows are consistent across diagrams and specifications
  - [ ] No contradictions between sections

- [ ] **Interface Consistency**:
  - [ ] Interfaces match between caller and callee (function signatures, data types, error codes)
  - [ ] Hardware interfaces match hardware specifications
  - [ ] External interfaces match protocol specifications
  - [ ] HMI interfaces match user requirements

#### 5.5 Design Correctness Verification

- [ ] **Functional Correctness**:
  - [ ] Design logic correctly implements requirements (desk check, inspection)
  - [ ] Algorithms are correct (mathematical verification, simulation)
  - [ ] State machines are complete (all states and transitions defined, no unreachable states)

- [ ] **Error Handling Correctness**:
  - [ ] All error conditions are detected
  - [ ] All error conditions are handled (fail-safe behavior, logging, propagation)
  - [ ] Error handling is consistent across design

#### 5.6 Static Analysis (EN 50128 Table A.19 - Mandatory SIL 3-4)

**Note**: Full static analysis occurs during implementation phase, but design review should verify **design is analyzable**:

- [ ] **Design Complexity Analysis**:
  - [ ] Cyclomatic complexity estimated for all functions
  - [ ] Complexity within limits (≤10 for SIL 3-4, ≤15 for SIL 2)
  - [ ] Complex functions decomposed

**Tool-Based Complexity Analysis** (if pseudocode/flowcharts available):
```bash
# Analyze design complexity from pseudocode (if available)
# (Full complexity analysis happens in implementation phase)
lizard --CCN 10 design-pseudocode/
```

- [ ] **Design Data Flow Analysis**:
  - [ ] All variables initialized before use (in design logic)
  - [ ] No unused variables in design
  - [ ] No unreachable code paths in design logic

- [ ] **Design Control Flow Analysis**:
  - [ ] All paths through design logic are reachable
  - [ ] All loops have termination conditions
  - [ ] No infinite loops in design

#### 5.7 EN 50128 Compliance Verification

- [ ] **Mandatory Techniques Applied** (EN 50128 Table A.3):
  - **SIL 2+**:
    - [ ] Modular Approach (19): Architecture is modular
  - **SIL 3-4**:
    - [ ] Structured Methodology (1): Design follows structured approach
    - [ ] Modular Approach (19): Architecture is modular

- [ ] **Highly Recommended Techniques Applied** (SIL 3-4):
  - [ ] Defensive Programming (2): Input validation, error detection
  - [ ] Fault Detection and Diagnosis (3): Fault detection mechanisms
  - [ ] Fully Defined Interface (7): All interfaces completely specified
  - [ ] Information Encapsulation (4): Data hiding, public interfaces
  - [ ] Modelling (5): Architecture/design diagrams

- [ ] **Technique Justification**:
  - [ ] If Highly Recommended technique NOT used, rationale documented
  - [ ] Alternative techniques justified

#### 5.8 MISRA C Design Verification

- [ ] **MISRA C Compliance** (SIL 2+ Mandatory):
  - [ ] Static allocation only (no malloc/calloc/realloc/free)
  - [ ] Fixed-width types (uint8_t, uint16_t, uint32_t)
  - [ ] No recursion (highly recommended SIL 3-4)
  - [ ] Bounded loops (all loops have iteration limits)
  - [ ] No function pointers (highly recommended SIL 3-4)

- [ ] **MISRA C Deviations**:
  - [ ] If MISRA C deviations are planned, they are documented
  - [ ] Deviations have rationale and approval
  - [ ] Deviations tracked in MISRA C Deviation Log

#### 5.9 Safety Verification

- [ ] **Safety Requirements Verification**:
  - [ ] All safety requirements from SRS Section 5 are traced to design elements
  - [ ] Safety-critical functions identified in design
  - [ ] Defensive programming applied to safety-critical functions

- [ ] **Fault Detection Verification**:
  - [ ] Hardware fault detection mechanisms specified
  - [ ] Software fault detection mechanisms specified
  - [ ] Fault detection coverage adequate (all critical faults detected)

- [ ] **Fail-Safe Behavior Verification**:
  - [ ] Safe state defined and reachable
  - [ ] Fail-safe behavior on all error conditions
  - [ ] No unhandled errors in safety-critical functions

#### 5.10 Testability Verification

- [ ] **Unit Testability**:
  - [ ] Functions can be tested in isolation
  - [ ] Inputs and outputs are observable
  - [ ] Test points identified for internal state

- [ ] **Integration Testability**:
  - [ ] Interfaces support integration testing
  - [ ] Integration test approach feasible

- [ ] **Validation Testability**:
  - [ ] System behavior can be validated against requirements
  - [ ] Acceptance criteria are testable

#### 5.11 Verification Report

Document verification findings in **Verification Report** (formal deliverable):

**Template**: `.opencode/skills/en50128-verification/templates/Verification-Report-template.md`

**Key Sections**:
1. **Verification Summary**: Overall verification result (Pass/Fail)
2. **Requirements Traceability Verification**: Traceability coverage, gaps, orphans
3. **Design Consistency Verification**: Internal consistency, interface consistency
4. **Design Correctness Verification**: Functional correctness, error handling
5. **Static Analysis Verification**: Complexity, data flow, control flow
6. **EN 50128 Compliance Verification**: Mandatory techniques applied
7. **MISRA C Design Verification**: MISRA C compliance, deviations
8. **Safety Verification**: Safety requirements, fault detection, fail-safe behavior
9. **Testability Verification**: Unit, integration, validation testability
10. **Issues Found**: Critical issues, major issues, minor issues
11. **Verification Conclusion**: Recommendation (Approve/Reject)

#### 5.12 Submit Verification Decision

**Approve**:
```bash
# VER approval
workspace.py workflow review Software-Architecture-Specification \
  --role VER \
  --approve \
  --comment "Independent verification passed. Requirements traceability 100% (SIL 3). Design consistency verified. Cyclomatic complexity within limits. EN 50128 mandatory techniques applied. MISRA C design compliant. Safety requirements verified. Design is correct, complete, and implementable. Recommend approval."
```

**Reject**:
```bash
# VER rejection
workspace.py workflow review Software-Architecture-Specification \
  --role VER \
  --reject \
  --comment "Independent verification failed. Critical issues: (1) Requirements traceability incomplete (REQ-SAFE-005 not traced to design), (2) Design inconsistency between architecture diagram and component specification (interface mismatch), (3) Error handling logic incorrect in overspeed detection (fail-safe behavior not guaranteed). Rework required."
```

---

### 6. Validation Review (SIL 3-4 Only)

**Role**: Validator (VAL)  
**Objective**: Verify design is fit for intended purpose and can be validated against requirements

**EN 50128 Reference**: Section 6.3 (Software Validation), EN 50128 Section 5.1.2.10 (Independence)

**Applicability**: **SIL 3-4 mandatory** (highly recommended for SIL 2)

**Independence Requirement** (EN 50128 Section 5.1.2.10):
- VAL **MUST BE** different person from Designer (DES)
- VAL **MUST BE** different person from Implementer (IMP)
- VAL **MUST BE** different person from Tester (TST)
- VAL **CANNOT BE** same person as Verifier (VER)
- VAL **MUST NOT** report to Project Manager (PM) for SIL 3-4
- VAL **REPORTS TO** V&V Manager (VMGR) or directly to customer/safety authority

#### 6.1 Preparation

- [ ] **Receive VAL Review Notification**:
  ```bash
  # Check validation review assignments
  workspace.py workflow pending-reviews --role VAL --assigned-to me
  ```

- [ ] **Verify Independence**:
  ```bash
  # Workflow Manager checks independence automatically
  # VAL cannot review document authored by self, VER, PM
  ```

- [ ] **Download Design Document** (already verified by VER)

- [ ] **Gather Validation References**:
  - [ ] Software Requirements Specification (SRS) - DOC-006
  - [ ] Software Validation Plan (SVaP) - DOC-005
  - [ ] System Requirements Specification (if available)
  - [ ] User requirements (operational scenarios)
  - [ ] EN 50128 Section 6.3 (Validation)

#### 6.2 Validation Objectives

**EN 50128 Section 6.3.2**: Validation shall provide evidence that:
1. Design meets user needs and operational requirements
2. Design is fit for intended purpose
3. Design can be validated through testing
4. Design supports acceptance criteria

#### 6.3 Operational Requirements Review

- [ ] **User Needs Satisfied**:
  - [ ] Design meets user requirements (from stakeholder requirements, user stories)
  - [ ] Design supports operational scenarios (normal operation, degraded operation, emergency operation)
  - [ ] Design is usable by intended users (operators, maintainers)

- [ ] **System Context Satisfied**:
  - [ ] Design fits within system architecture
  - [ ] Design integrates with external systems (hardware, communication, HMI)
  - [ ] Design meets system-level requirements (if applicable)

#### 6.4 Acceptance Criteria Review

- [ ] **Acceptance Criteria Defined**:
  - [ ] Each requirement has testable acceptance criteria
  - [ ] Acceptance criteria are measurable (quantitative, objective)
  - [ ] Acceptance criteria are achievable (design supports measurement)

- [ ] **Validation Test Approach Feasible**:
  - [ ] System testing approach is feasible (test environment, test equipment, test procedures)
  - [ ] Operational scenarios can be simulated or replicated
  - [ ] Acceptance testing approach is defined

#### 6.5 Validation Testability Review

- [ ] **System-Level Testability**:
  - [ ] System behavior can be observed (outputs, indicators, logs)
  - [ ] System inputs can be controlled (stimuli, scenarios, test cases)
  - [ ] Test instrumentation is feasible (test points, debug interfaces)

- [ ] **Operational Scenario Testability**:
  - [ ] Normal operation scenarios can be tested
  - [ ] Degraded operation scenarios can be tested (fault injection, failure simulation)
  - [ ] Emergency scenarios can be tested (safety-critical conditions)

#### 6.6 Fitness for Purpose Review

- [ ] **Design Meets Intended Purpose**:
  - [ ] Design solves the problem (user needs, operational requirements)
  - [ ] Design is appropriate for railway safety-critical application
  - [ ] Design is feasible to implement and validate

- [ ] **Design is Usable**:
  - [ ] HMI design is usable by operators (clear, intuitive, safe)
  - [ ] Maintenance is feasible (diagnostics, logging, configuration)
  - [ ] Training requirements are reasonable

#### 6.7 Validation Review Report

Document validation findings in **Validation Review Report**:

**Template**:
```markdown
# Validation Review Report - [Document Name]

**Validator**: [VAL name]
**Date**: [Review date]
**Document**: [Document ID and version]
**SIL**: [3 or 4]

## Summary

[Overall validation assessment: Approved / Approved with changes / Rejected]

## Operational Requirements

- [ ] User needs satisfied
- [ ] System context satisfied
- [ ] Operational scenarios supported

**Result**: [Pass/Fail]

## Acceptance Criteria

- [ ] Acceptance criteria defined for all requirements
- [ ] Acceptance criteria are measurable and achievable
- [ ] Validation test approach feasible

**Result**: [Pass/Fail]

## Validation Testability

- [ ] System-level testability (inputs, outputs, instrumentation)
- [ ] Operational scenario testability (normal, degraded, emergency)

**Result**: [Pass/Fail]

## Fitness for Purpose

- [ ] Design meets intended purpose
- [ ] Design is usable by operators and maintainers
- [ ] Design is appropriate for railway safety-critical application

**Result**: [Pass/Fail]

## Validation Issues Found

### Critical Validation Issues (must fix)

1. [Issue description with validation impact]
2. ...

### Major Validation Issues (should fix)

1. [Issue description with validation impact]
2. ...

## Recommendation

[Approved / Approved with changes / Rejected (validation concerns)]

## Validator Signature

[Name, Date, Role]
```

#### 6.8 Submit Validation Review Decision

**Approve**:
```bash
# VAL approval
workspace.py workflow review Software-Architecture-Specification \
  --role VAL \
  --approve \
  --comment "Validation review approved. Design meets user needs and operational requirements. Acceptance criteria defined and measurable. Validation test approach feasible. Design is fit for intended railway safety-critical purpose. Recommend approval."
```

**Reject**:
```bash
# VAL rejection
workspace.py workflow review Software-Architecture-Specification \
  --role VAL \
  --reject \
  --comment "Validation review failed. Validation concerns: (1) Emergency operation scenario not supported in design (requirement REQ-OPS-007), (2) Acceptance criteria for performance requirements not measurable (need quantitative metrics), (3) HMI design not usable for emergency brake activation (safety-critical operation requires clearer interface). Rework required."
```

---

### 7. Project Manager Approval (All SILs)

**Role**: Project Manager (PM)  
**Objective**: Final approval of design document for project baseline

**EN 50128 Reference**: Section 5, Table B.9 (Project Manager role)

**Applicability**: **All SILs** (final approval)

**Independence Requirement**: None (PM coordinates project, not independent)

#### 7.1 Preparation

- [ ] **Receive PM Approval Notification**:
  ```bash
  # Check PM approval assignments
  workspace.py workflow pending-reviews --role PM --assigned-to me
  ```

- [ ] **Download Design Document** (already reviewed by all prior reviewers)

- [ ] **Review All Prior Approvals**:
  ```bash
  # View all approvals
  workspace.py workflow status Software-Architecture-Specification --approvals
  ```

#### 7.2 PM Approval Criteria

- [ ] **All Prior Reviews Approved**:
  - [ ] Author self-review complete
  - [ ] PEER review approved
  - [ ] QUA review approved
  - [ ] SAFETY_MGR review approved (SIL 3-4)
  - [ ] VER review approved (SIL 3-4)
  - [ ] VAL review approved (SIL 3-4)

- [ ] **Document Quality**:
  - [ ] Document is complete and professional
  - [ ] Document follows template and standards
  - [ ] Document is ready for project baseline

- [ ] **Project Impact**:
  - [ ] Design supports project schedule
  - [ ] Design is within project resources (budget, personnel, equipment)
  - [ ] Design is acceptable to stakeholders (customer, safety authority)

#### 7.3 PM Approval Decision

**Approve**:
```bash
# PM final approval
workspace.py workflow review Software-Architecture-Specification \
  --role PM \
  --approve \
  --comment "Project Manager approval. All prior reviews approved (PEER, QUA, SAFETY_MGR, VER, VAL). Document is complete and ready for baseline. Design supports project schedule and resources. Recommend baseline creation."
```

**Reject** (rare, usually only if project constraints violated):
```bash
# PM rejection (rare)
workspace.py workflow review Software-Architecture-Specification \
  --role PM \
  --reject \
  --comment "Project Manager rejection. Design exceeds project resource constraints (estimated 256KB RAM, target is 128KB). Recommend design optimization to reduce memory footprint before approval."
```

---

### 8. Rework and Re-Review (If Rejected)

**Scenario**: Design document rejected by one or more reviewers

#### 8.1 Rework Process

**Author (DES) Responsibilities**:
1. **Collect All Rejection Comments**:
   ```bash
   # View all review comments
   workspace.py workflow status Software-Architecture-Specification --comments
   ```

2. **Analyze Issues**:
   - Group issues by type (traceability, complexity, safety, etc.)
   - Prioritize issues (critical, major, minor)
   - Identify root causes (incomplete analysis, misunderstanding, oversight)

3. **Create Rework Plan**:
   - [ ] List all issues to fix
   - [ ] Estimate effort for each issue
   - [ ] Identify dependencies (some fixes may impact others)
   - [ ] Schedule rework tasks

4. **Fix Issues**:
   - [ ] Address all critical issues (blockers)
   - [ ] Address all major issues (should fix)
   - [ ] Address minor issues if time permits
   - [ ] Update document version and change log

5. **Update Traceability** (if changed):
   ```bash
   # Update traceability matrix
   traceability.py update --matrix requirements_to_architecture --changes rework-changes.csv
   
   # Validate updated traceability
   traceability.py validate --matrix requirements_to_architecture --sil 3
   ```

6. **Self-Review Rework**:
   - [ ] Review all changes for correctness
   - [ ] Ensure no new issues introduced
   - [ ] Verify all rejection comments addressed

7. **Document Rework**:
   - [ ] Update Document Control table with new version
   - [ ] Document changes in change log (reference rejection comments)
   - [ ] Clear previous review comments (or mark as "addressed")

8. **Commit Rework to Version Control**:
   ```bash
   # Stage reworked design document
   git add docs/architecture/Software-Architecture-Specification.md
   
   # Commit with reference to rejection
   git commit -m "Design: Rework SAS per review comments (traceability gaps fixed, complexity reduced, defensive programming added)"
   
   # Push to feature branch
   git push origin feature/architecture-design-rework
   ```

9. **Resubmit for Review**:
   ```bash
   # Resubmit design document (full review cycle)
   workspace.py workflow submit Software-Architecture-Specification --for-review --rework-iteration 2
   ```

#### 8.2 Re-Review Process

**Important**: After rework, **ALL REVIEWERS MUST RE-REVIEW** the document:
- PEER, QUA, SAFETY_MGR, VER, VAL, PM must all re-approve
- Previous approvals are **INVALIDATED** by rework (document changed)
- Re-review focuses on:
  1. Verifying rejection comments are addressed
  2. Ensuring no new issues introduced
  3. Re-approving if satisfactory

**Re-Review Workflow**:
```
┌──────────────────────────────────────┐
│ 1. Author Self-Review (rework)       │ DES verifies all issues fixed
├──────────────────────────────────────┤
│ 2. Peer Re-Review                    │ PEER verifies rejection comments addressed
├──────────────────────────────────────┤
│ 3. QA Re-Review                      │ QUA verifies quality restored
├──────────────────────────────────────┤
│ 4. Safety Manager Re-Review (SIL 3-4)│ SAFETY_MGR verifies safety issues fixed
├──────────────────────────────────────┤
│ 5. Independent Re-Verification (SIL 3-4)│ VER verifies rework correctness
├──────────────────────────────────────┤
│ 6. Validation Re-Review (SIL 3-4)    │ VAL verifies fitness for purpose
├──────────────────────────────────────┤
│ 7. PM Re-Approval                    │ PM final approval
└──────────────────────────────────────┘
```

#### 8.3 Rework Iteration Limit

**Best Practice**:
- **Target**: ≤ 1 rework iteration (first review identifies most issues)
- **Acceptable**: 2 rework iterations (complex designs may need refinement)
- **Concerning**: ≥ 3 rework iterations (indicates poor initial quality or misunderstood requirements)

**If ≥ 3 Rework Iterations**:
- [ ] Root cause analysis: Why are issues persisting?
- [ ] Process improvement: What can prevent future issues?
- [ ] Training needs: Does author need additional training?
- [ ] Schedule impact: Update project schedule with delays

---

### 9. Finalize and Baseline

**Role**: Configuration Manager (CM), with coordination from Designer (DES)  
**Objective**: Create immutable baseline of approved design document

**EN 50128 Reference**: Section 6.6 (Configuration Management)

**Prerequisites**:
- [ ] All SIL-appropriate reviews approved (PEER, QUA, SAFETY_MGR, VER, VAL, PM)
- [ ] Document status: **Approved**
- [ ] No outstanding issues or rework items

#### 9.1 Pre-Baseline Checklist

- [ ] **All Approvals Obtained**:
  ```bash
  # Verify all approvals
  workspace.py workflow status Software-Architecture-Specification --approvals
  ```

- [ ] **Document Finalized**:
  - [ ] All TODOs resolved
  - [ ] All placeholders filled
  - [ ] Document version is stable (e.g., 1.0, not 0.9)
  - [ ] Change log is complete

- [ ] **Traceability Finalized** (SIL 3-4):
  - [ ] Traceability matrix is complete (100%)
  - [ ] Traceability matrix is committed to Git
  - [ ] Traceability validation passed

- [ ] **Git Repository Clean**:
  ```bash
  # Verify no uncommitted changes
  git status
  
  # Verify all changes pushed to remote
  git log origin/main..HEAD
  ```

#### 9.2 Create Baseline

**Configuration Manager (CM) Actions**:

1. **Merge Feature Branch to Main**:
   ```bash
   # Checkout main branch
   git checkout main
   
   # Merge feature branch (approved design)
   git merge --no-ff feature/architecture-design
   
   # Push to main
   git push origin main
   ```

2. **Create Git Tag (Baseline)**:
   ```bash
   # Create annotated tag (immutable baseline)
   git tag -a ARCH-BASELINE-v1.0.0 -m "Architecture Design Baseline v1.0.0 (SIL 3) - Software Architecture Specification approved"
   
   # Push tag to remote
   git push origin ARCH-BASELINE-v1.0.0
   ```

3. **Update Workflow Status**:
   ```bash
   # Transition document to "Baseline" state
   workspace.py workflow baseline Software-Architecture-Specification --tag ARCH-BASELINE-v1.0.0
   ```

4. **Generate Baseline Manifest**:
   ```bash
   # Generate baseline manifest (files, versions, checksums)
   workspace.py baseline manifest --tag ARCH-BASELINE-v1.0.0 --output baselines/ARCH-BASELINE-v1.0.0-manifest.md
   ```

5. **Update LIFECYCLE_STATE.md**:
   - [ ] Mark Phase 3 (Architecture & Design) deliverables as **Baseline**
   - [ ] Record baseline tag (ARCH-BASELINE-v1.0.0)
   - [ ] Update phase status to "Complete"

#### 9.3 Baseline Immutability

**After Baseline Creation**:
- [ ] Design document is **IMMUTABLE** (cannot be changed without Change Request)
- [ ] Git tag is **IMMUTABLE** (tag cannot be moved or deleted)
- [ ] Any changes require **Change Request (CR)** and Change Control Board (CCB) approval
- [ ] Changes create a **NEW VERSION** (e.g., v1.1.0, v2.0.0)

**Change Control Process** (if changes needed after baseline):
1. Submit Change Request (CR) to Change Control Board (CCB)
2. CCB reviews CR (impact analysis, risk assessment, approval)
3. If approved, create new feature branch from baseline tag
4. Implement changes in new feature branch
5. Re-review changes (impact-based review, not full review)
6. Merge changes to main and create new baseline tag (v1.1.0, v2.0.0)

---

## Common Design Review Issues and Solutions

### Issue Category 1: Traceability Problems

**Issue**: Traceability matrix incomplete (not all requirements traced to design)  
**Impact**: Cannot verify all requirements are implemented  
**Solution**:
- Use traceability tool to identify gaps: `traceability.py check-gaps`
- Add missing trace links between requirements and design elements
- Verify trace links are accurate (design actually implements requirement)

**Issue**: Orphaned design elements (design without corresponding requirement)  
**Impact**: Over-design, unnecessary complexity  
**Solution**:
- Use traceability tool to identify orphans: `traceability.py check-orphans`
- Either trace orphan to existing requirement, or remove orphan from design

---

### Issue Category 2: Architectural Problems

**Issue**: Poor modularity (modules have overlapping responsibilities)  
**Impact**: Tight coupling, difficult to test, difficult to maintain  
**Solution**:
- Apply Single Responsibility Principle (each module does one thing well)
- Refactor modules with clear boundaries
- Define explicit interfaces between modules

**Issue**: Tight coupling (modules depend heavily on each other)  
**Impact**: Changes to one module require changes to many others  
**Solution**:
- Minimize inter-module dependencies
- Use interfaces or abstraction layers to decouple modules
- Apply Dependency Inversion Principle (depend on abstractions, not concrete implementations)

**Issue**: God Object (one module does everything)  
**Impact**: High complexity, difficult to test, violates Single Responsibility Principle  
**Solution**:
- Decompose God Object into smaller, focused modules
- Each new module has single, clear responsibility
- Redistribute responsibilities across modules

---

### Issue Category 3: Complexity Problems

**Issue**: Cyclomatic complexity exceeds SIL limits (e.g., complexity = 15 for SIL 3, limit is 10)  
**Impact**: Difficult to test, error-prone, difficult to maintain  
**Solution**:
- Decompose complex function into smaller helper functions
- Extract conditional logic into separate functions
- Simplify nested conditionals (guard clauses, early returns)

**Example**:
```c
// BEFORE: Complexity = 15 (exceeds SIL 3 limit of 10)
error_t ProcessData(data_t* data) {
    if (data != NULL) {
        if (data->valid) {
            if (data->type == TYPE_A) {
                if (data->value > 10) {
                    if (data->value < 100) {
                        // Process TYPE_A data
                        if (data->flag1) {
                            // ...
                        } else if (data->flag2) {
                            // ...
                        } else {
                            // ...
                        }
                    }
                }
            } else if (data->type == TYPE_B) {
                // ...
            } else {
                // ...
            }
        }
    }
    return SUCCESS;
}

// AFTER: Decomposed into smaller functions, complexity reduced
error_t ProcessData(data_t* data) {
    if (data == NULL) return ERROR_NULL_POINTER;
    if (!data->valid) return ERROR_INVALID_DATA;
    
    if (data->type == TYPE_A) {
        return ProcessTypeA(data);  // Complexity moved to helper
    } else if (data->type == TYPE_B) {
        return ProcessTypeB(data);  // Complexity moved to helper
    } else {
        return ERROR_UNKNOWN_TYPE;
    }
}

error_t ProcessTypeA(data_t* data) {  // Complexity = 5 (OK for SIL 3)
    if (data->value < 10 || data->value >= 100) {
        return ERROR_OUT_OF_RANGE;
    }
    
    if (data->flag1) {
        // ...
    } else if (data->flag2) {
        // ...
    } else {
        // ...
    }
    return SUCCESS;
}
```

---

### Issue Category 4: Safety Problems

**Issue**: Missing defensive programming (no input validation)  
**Impact**: Undefined behavior on invalid inputs, safety hazard  
**Solution**:
- Add NULL pointer checks for all pointer parameters
- Add range checks for all numeric parameters
- Add state checks (function called in valid state)
- Add bounds checks (array indices within bounds)

**Issue**: No fail-safe behavior specified  
**Impact**: Undefined behavior on errors, potential safety hazard  
**Solution**:
- Define safe state for each subsystem
- Specify transition to safe state on unrecoverable errors
- Ensure safe state is maintained until operator intervention

**Issue**: Hardware faults not detected  
**Impact**: Hardware failures may go undetected, leading to safety hazard  
**Solution**:
- Add memory fault detection (ECC, parity, checksums)
- Add communication fault detection (CRC, parity, timeout)
- Add sensor fault detection (plausibility checks, redundancy)
- Add processor fault detection (watchdog, dual execution)

---

### Issue Category 5: MISRA C Problems

**Issue**: Dynamic memory allocation used (malloc/free) in design  
**Impact**: MISRA C violation (forbidden for SIL 2+), unpredictable memory usage  
**Solution**:
- Replace dynamic allocation with static allocation
- Use fixed-size arrays or data structures
- Pre-allocate all memory at initialization

**Issue**: Recursion used in design  
**Impact**: MISRA C highly recommended to avoid (SIL 3-4), unbounded stack usage  
**Solution**:
- Replace recursion with iteration (loops)
- Use explicit stack data structure if needed

**Issue**: Ambiguous data types (int, long, short)  
**Impact**: MISRA C violation, platform-dependent behavior  
**Solution**:
- Use fixed-width types (uint8_t, uint16_t, uint32_t, int8_t, int16_t, int32_t)
- Explicitly specify signed or unsigned

---

### Issue Category 6: Interface Problems

**Issue**: Ambiguous interface specification (data types not fully defined)  
**Impact**: Implementation inconsistencies, integration defects  
**Solution**:
- Specify exact data types (uint16_t, not "integer")
- Specify valid ranges (e.g., 0-100, not "positive")
- Specify error codes (exact numeric values or enums)
- Specify timing requirements (exact milliseconds, not "fast")

**Issue**: Interface mismatch (caller and callee have different expectations)  
**Impact**: Integration defects, runtime errors  
**Solution**:
- Review both sides of interface (caller and callee)
- Ensure data types match exactly
- Ensure error codes match exactly
- Ensure calling conventions match (who validates inputs, who handles errors)

---

### Issue Category 7: Testability Problems

**Issue**: Design is not testable (cannot observe internal state)  
**Impact**: Cannot verify correctness, difficult to debug  
**Solution**:
- Add test points (interfaces to observe internal state)
- Make internal state accessible for testing (test-only interfaces)
- Design for dependency injection (substitute test doubles for real components)

**Issue**: No acceptance criteria defined  
**Impact**: Cannot validate design meets requirements  
**Solution**:
- Define quantitative, measurable acceptance criteria for each requirement
- Ensure acceptance criteria are testable (can be measured in validation testing)

---

## Review Workflow Summary

### SIL 0-2 Review Workflow (4 reviewers)

1. **Author Self-Review** (DES): Completeness, correctness, traceability
2. **Peer Review** (PEER): Architectural quality, design detail, common issues
3. **QA Review** (QUA): Template compliance, EN 50128 compliance, MISRA C design
4. **PM Approval** (PM): Final approval for baseline

### SIL 3-4 Review Workflow (8 reviewers)

1. **Author Self-Review** (DES): Completeness, correctness, traceability
2. **Peer Review** (PEER): Architectural quality, design detail, common issues
3. **QA Review** (QUA): Template compliance, EN 50128 compliance, MISRA C design
4. **Safety Manager Review** (SAFETY_MGR): Safety requirements, defensive programming, fail-safe behavior
5. **Independent Verification** (VER): Requirements verification, consistency, correctness, EN 50128 compliance
6. **Validation Review** (VAL): Operational requirements, acceptance criteria, fitness for purpose
7. **PM Approval** (PM): Final approval for baseline

---

## Tool Integration Summary

**Workflow Manager** (`workspace.py workflow ...`):
- Submit design for review: `workspace.py workflow submit <document> --for-review`
- Approve/reject review: `workspace.py workflow review <document> --role <role> --approve/--reject --comment "..."`
- Check review status: `workspace.py workflow status <document> --approvals`
- Create baseline: `workspace.py workflow baseline <document> --tag <tag>`

**Traceability Manager** (`traceability.py ...`):
- Validate traceability: `traceability.py validate --matrix requirements_to_architecture --sil 3`
- Check gaps: `traceability.py check-gaps --source SRS --target SAS`
- Check orphans: `traceability.py check-orphans --source SRS --target SAS`
- Generate report: `traceability.py report --matrix requirements_to_architecture --format markdown`

**Version Control** (`git ...`):
- Commit changes: `git add <file> && git commit -m "message"`
- Create baseline tag: `git tag -a <tag> -m "message" && git push origin <tag>`
- Merge to main: `git checkout main && git merge --no-ff <branch> && git push origin main`

---

## References

- **EN 50128:2011 Section 6.2**: Software Verification
- **EN 50128:2011 Section 6.3**: Software Validation
- **EN 50128:2011 Section 6.5**: Software Quality Assurance
- **EN 50128:2011 Section 6.6**: Configuration Management
- **EN 50128:2011 Section 7.3**: Software Architecture and Design
- **EN 50128:2011 Table A.3**: Software Architecture and Design Techniques
- **EN 50128:2011 Table A.5**: Verification and Testing Techniques
- **EN 50128:2011 Table A.9**: Software Quality Assurance Measures
- **EN 50128:2011 Table A.19**: Static Analysis Techniques
- **EN 50128:2011 Section 5.1.2.10**: Independence Requirements (SIL 3-4)
- **MISRA C:2012**: C Coding Standard for Safety-Critical Systems
- **Workflow Manager Design**: `docs/designs/WORKFLOW-MANAGER-DESIGN.md`
- **Traceability Manager Design**: `docs/designs/TRACEABILITY-MANAGER-DESIGN.md`

---

**END OF DESIGN REVIEW WORKFLOW**
