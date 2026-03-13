# Architecture Review Checklist for EN 50128 Railway Safety Software

**Purpose**: This document provides a comprehensive checklist for reviewing Software Architecture Specifications (DOC-9), Software Design Specifications (DOC-10), and Software Interface Specifications (DOC-11) to ensure completeness, correctness, consistency, and EN 50128 compliance.

**Scope**: Applies to design review activities during Software Architecture and Design phases.

**Audience**: Peer Reviewers (PEER), Quality Assurance (QUA), Safety Manager (SAFETY_MGR), Verifiers (VER), Validators (VAL), Project Manager (PM)

**EN 50128 Reference**: Table A.5 "Verification and Testing" techniques, Section 6.2 "Software Verification"

---

## Table of Contents

1. [Introduction](#1-introduction)
2. [Completeness Checks](#2-completeness-checks)
3. [Correctness Checks](#3-correctness-checks)
4. [Consistency Checks](#4-consistency-checks)
5. [EN 50128 Compliance Checks](#5-en-50128-compliance-checks)
6. [MISRA C Design Compliance](#6-misra-c-design-compliance)
7. [Safety and Reliability Checks](#7-safety-and-reliability-checks)
8. [Quality Attributes](#8-quality-attributes)
9. [Traceability Checks](#9-traceability-checks)
10. [Tool Validation Checks](#10-tool-validation-checks)
11. [Review Process](#11-review-process)
12. [References](#12-references)

---

## 1. Introduction

### 1.1 Purpose of Architecture Review

The architecture review ensures that the Software Architecture Specification (DOC-9), Software Design Specification (DOC-10), and Software Interface Specifications (DOC-11) are:
- ✅ **Complete**: All requirements addressed, all components documented
- ✅ **Correct**: Design is accurate and meets requirements
- ✅ **Consistent**: No contradictions or conflicts
- ✅ **Compliant**: Follows EN 50128 and MISRA C standards
- ✅ **Safe**: Hazards addressed, defensive programming applied
- ✅ **Verifiable**: Testable and analyzable

### 1.2 Review Types

**Peer Review** (PEER):
- Informal technical review by colleague
- Focus on correctness and clarity
- First line of defense

**Quality Assurance Review** (QUA):
- Formal review by independent QA
- Focus on process compliance and standards
- MANDATORY for all SIL levels

**Safety Review** (SAFETY_MGR):
- Review by Safety Manager
- Focus on safety requirements and hazard mitigation
- MANDATORY for SIL 3-4

**Verification Review** (VER):
- Independent verification by Verifier
- Focus on traceability and completeness
- MANDATORY for SIL 3-4

**Validation Review** (VAL):
- Review by Validator for testability
- Focus on operational scenarios
- MANDATORY for SIL 3-4

**Management Review** (PM):
- Final approval by Project Manager
- Focus on project alignment and risks

### 1.3 SIL-Dependent Review Requirements

| SIL Level | Required Reviewers | Review Depth |
|-----------|-------------------|--------------|
| **SIL 0** | PEER, QUA, PM | Basic (focus on completeness) |
| **SIL 1** | PEER, QUA, PM | Basic (focus on completeness) |
| **SIL 2** | PEER, QUA, PM | Moderate (add safety checks) |
| **SIL 3** | PEER, QUA, SAFETY_MGR, VER, VAL, PM | Rigorous (all checks) |
| **SIL 4** | PEER, QUA, SAFETY_MGR, VER, VAL, PM | Rigorous (all checks) |

### 1.4 Using This Checklist

**For Reviewers**:
1. Review document against this checklist
2. Mark each item: ✅ Pass, ❌ Fail, ⚠️ Comment
3. Document findings in review report
4. Provide clear, actionable feedback to author

**For Authors**:
1. Self-review against this checklist before submitting for review
2. Address all findings before resubmission
3. Update document based on feedback

---

## 2. Completeness Checks

### 2.1 Document Structure Completeness

**Software Architecture Specification (DOC-9)**:
- [ ] Document follows template structure (from `.opencode/skills/en50128-design/templates/`)
- [ ] Document Control section complete (ID, version, approvals)
- [ ] Introduction section complete (purpose, scope, audience, references)
- [ ] System Overview section complete (system context, boundaries, interfaces)
- [ ] Architectural Design section complete (components, interfaces, allocation)
- [ ] Safety Architecture section complete (safety requirements, fault detection, fail-safe)
- [ ] Traceability section complete (requirements-to-architecture matrix)

**Software Design Specification (DOC-10)**:
- [ ] Document follows template structure
- [ ] Document Control section complete
- [ ] Module/Component Design sections complete (all modules documented)
- [ ] Function Specifications complete (all public functions documented)
- [ ] Data Structure Specifications complete (all types documented)
- [ ] Algorithm Descriptions complete (all complex algorithms documented)
- [ ] Traceability section complete (architecture-to-design matrix)

**Software Interface Specifications (DOC-11)**:
- [ ] Document follows template structure
- [ ] All internal interfaces documented (SW-SW)
- [ ] All hardware interfaces documented (SW-HW)
- [ ] All external interfaces documented (SW-external system)
- [ ] All HMI interfaces documented (SW-user)
- [ ] Interface specifications complete (data formats, protocols, timing, error handling)

### 2.2 Requirements Coverage

- [ ] All software requirements (from SRS DOC-5) are addressed in architecture
- [ ] All safety requirements addressed (from Hazard Log)
- [ ] All interface requirements addressed (internal, hardware, external, HMI)
- [ ] All non-functional requirements addressed (performance, reliability, maintainability)
- [ ] Requirements traceability complete (forward trace: SRS → SAS → SDS)

**Verification Command**:
```bash
# Check requirements coverage
traceability.py check-gaps --source SRS --target SAS
traceability.py check-gaps --source SAS --target SDS
```

**Expected**: Zero gaps (all requirements traced)

### 2.3 Component/Module Coverage

- [ ] All architectural components defined in DOC-9
- [ ] All components decomposed into modules in DOC-10
- [ ] All modules have detailed design specifications
- [ ] All public functions documented
- [ ] All data structures documented
- [ ] All interfaces documented (DOC-11)

### 2.4 Interface Coverage

- [ ] All interfaces between modules documented
- [ ] All hardware interfaces documented (memory-mapped I/O, GPIO, ADC, timers, etc.)
- [ ] All external interfaces documented (CAN, UART, SPI, I2C, etc.)
- [ ] All HMI interfaces documented (displays, buttons, indicators, etc.)
- [ ] Interface error handling documented

### 2.5 Missing Information

- [ ] No "TBD" (To Be Determined) placeholders (unless tracked as open issue)
- [ ] No "TODO" comments (unless tracked as open issue)
- [ ] All references complete (document IDs, section numbers)
- [ ] All diagrams have captions and are referenced in text
- [ ] All tables have headers and are referenced in text

---

## 3. Correctness Checks

### 3.1 Requirements Correctness

- [ ] Architecture correctly implements all requirements (no misunderstanding)
- [ ] Safety requirements correctly implemented (hazards mitigated)
- [ ] Performance requirements achievable (WCET analysis, memory budget)
- [ ] Functional requirements correctly mapped to components/modules

**Review Method**: For each requirement, verify that design element correctly addresses it.

**Example**:
```
Requirement REQ-SPEED-001: "System SHALL monitor train speed every 100ms"
Architecture: SpeedMonitorComponent with 100ms timer interrupt
✅ Correct: Timer period matches requirement

Requirement REQ-BRAKE-002: "System SHALL apply emergency brake if speed > 120 km/h"
Design: brake_controller.c, function emergency_brake_check()
  - Checks speed > 120 km/h ✅
  - Calls brake_apply(BRAKE_EMERGENCY) ✅
✅ Correct: Logic matches requirement
```

### 3.2 Logic Correctness

- [ ] Control flow logic is correct (state machines, decision logic)
- [ ] Algorithms are correct (no off-by-one errors, correct formulas)
- [ ] Error handling logic is correct (all errors detected and handled)
- [ ] Boundary conditions handled correctly (min/max values, edge cases)

**Review Method**: Walkthrough algorithms and control flow diagrams.

**Example State Machine Review**:
```
State: IDLE → Event: START_REQUEST → Next State: RUNNING ✅
State: RUNNING → Event: STOP_REQUEST → Next State: STOPPED ✅
State: RUNNING → Event: ERROR_DETECTED → Next State: ERROR ✅
State: ERROR → Event: RESET → Next State: IDLE ✅

Check: All states have transitions for all possible events? ✅
Check: No deadlock states? ✅
Check: Initial state defined? ✅
```

### 3.3 Calculation Correctness

- [ ] All formulas are mathematically correct
- [ ] Units are consistent (e.g., km/h vs. m/s)
- [ ] Scaling factors are correct (e.g., ADC counts → physical units)
- [ ] Integer arithmetic checked for overflow (use wider types for intermediate results)
- [ ] Fixed-point arithmetic checked for precision loss

**Example**:
```c
// Requirement: Convert ADC value (0-4095) to voltage (0-5V)
// Formula: voltage = (adc_value * 5.0) / 4095.0

// BAD: Integer division (loses precision)
uint16_t voltage_mv = (adc_value * 5000) / 4095;  // May overflow if adc_value > 13

// GOOD: Use wider type for intermediate result
uint32_t voltage_mv = ((uint32_t)adc_value * 5000) / 4095;  // No overflow
✅ Correct: Uses uint32_t to prevent overflow
```

### 3.4 Data Type Correctness

- [ ] All variables have appropriate types (range, signedness)
- [ ] Fixed-width types used (`uint8_t`, `int32_t`, etc.)
- [ ] No implicit type conversions (all casts explicit and documented)
- [ ] No type punning (union abuse)

**Example**:
```c
// Requirement: Store sensor value (range: -1000 to +1000)
int16_t sensor_value;  // Range: -32768 to +32767 ✅ Sufficient

// Requirement: Store ADC value (range: 0 to 4095)
uint16_t adc_value;  // Range: 0 to 65535 ✅ Sufficient

// BAD: Type too small
uint8_t adc_value;  // Range: 0 to 255 ❌ Insufficient (ADC is 12-bit)
```

---

## 4. Consistency Checks

### 4.1 Internal Consistency

- [ ] Component interfaces consistent across documents (DOC-9, DOC-10, DOC-11)
- [ ] Function signatures consistent (header vs. design specification)
- [ ] Data structures consistent (type definitions match across documents)
- [ ] State machines consistent (states and transitions match across diagrams and text)

**Example**:
```
DOC-9 (Architecture): SpeedMonitorComponent has interface "getSpeed() → uint16_t"
DOC-10 (Design): Function speed_monitor_get_speed() → uint16_t ✅ Consistent
DOC-11 (Interface): speed_monitor_get_speed(uint16_t* speed) → error_t ❌ Inconsistent!

Action: Resolve inconsistency (likely DOC-11 is correct pattern for EN 50128)
```

### 4.2 Naming Consistency

- [ ] Naming conventions consistent across documents
- [ ] Module names consistent (e.g., `speed_monitor` vs. `SpeedMonitor` vs. `speedMonitor`)
- [ ] Function names follow convention (e.g., `module_verb_noun()`)
- [ ] Variable names descriptive and consistent
- [ ] Constants named consistently (e.g., `MAX_SPEED` vs. `SPEED_MAX`)

**Naming Convention (Example)**:
```
Modules: lowercase_with_underscores (e.g., speed_monitor)
Functions: module_verb_noun() (e.g., speed_monitor_get_value)
Types: lowercase_t (e.g., sensor_data_t, error_t)
Constants: UPPERCASE_WITH_UNDERSCORES (e.g., MAX_SPEED, MIN_PRESSURE)
Enums: TYPE_VALUE (e.g., STATE_IDLE, ERROR_TIMEOUT)
```

### 4.3 Cross-Document Consistency

- [ ] Architecture components (DOC-9) match design modules (DOC-10)
- [ ] Interface specifications (DOC-11) match architecture and design
- [ ] Requirements (DOC-5) consistently referenced across documents
- [ ] Terminology consistent (same terms used across documents)

**Review Method**: Create mapping table and verify consistency.

| DOC-9 Component | DOC-10 Module | DOC-11 Interface |
|-----------------|---------------|------------------|
| SpeedMonitorComponent | speed_monitor.c | speed_monitor.h ✅ |
| BrakeControllerComponent | brake_controller.c | brake_controller.h ✅ |

### 4.4 Version Consistency

- [ ] All document references use correct version numbers
- [ ] All documents reference same baseline requirements (SRS version)
- [ ] Document dependencies clearly stated (e.g., "Based on SRS v1.2")

---

## 5. EN 50128 Compliance Checks

### 5.1 Mandatory Techniques Applied (Table A.3 - Architecture)

**SIL 3-4 MANDATORY Techniques** (Table A.3):

- [ ] **Structured Methodology** (Technique 22, MANDATORY SIL 3-4)
  - Architecture follows structured decomposition (top-down or bottom-up)
  - Clear component hierarchy
  - Documented design process

- [ ] **Modular Approach** (Technique 19, MANDATORY SIL 2+)
  - System decomposed into independent modules
  - Modules have well-defined interfaces
  - Modules have single responsibilities (see `modularity-guidelines.md`)

**For SIL 3-4 projects, verify at least one approved combination**:
- Option A: Techniques 1,7,19,22 + one from {4,5,12,21}
- Option B: Techniques 1,4,19,22 + one from {2,5,12,15,21}

**Checklist**:
- [ ] Architecture document cites applied techniques (with EN 50128 Table A.3 reference)
- [ ] Evidence of technique application (e.g., modular architecture diagram, interface specifications)

### 5.2 Defensive Programming (SIL 3-4 Highly Recommended)

**EN 50128 Table A.3 Technique 2** (Highly Recommended SIL 3-4):

- [ ] Input validation at all module boundaries (NULL checks, range checks)
- [ ] Error detection mechanisms (hardware faults, communication faults)
- [ ] Error handling patterns (return codes, safe states)
- [ ] Fail-safe behavior defined (safe state entry on error)

**Reference**: See `.opencode/skills/en50128-design/resources/defensive-programming-patterns.md`

### 5.3 Fully Defined Interface (Highly Recommended SIL 1+)

**EN 50128 Table A.3 Technique 7**:

- [ ] All interfaces fully specified (data types, ranges, units)
- [ ] Interface timing specified (execution time, latency)
- [ ] Interface error conditions specified
- [ ] Interface protocols documented (e.g., function call sequence)

### 5.4 SIL-Dependent Rigor

| Check | SIL 0-1 | SIL 2 | SIL 3-4 |
|-------|---------|-------|---------|
| Modular Approach | Recommended | **MANDATORY** | **MANDATORY** |
| Defensive Programming | - | Recommended | **Highly Recommended** |
| Structured Methodology | Recommended | Highly Recommended | **MANDATORY** |
| Complexity Limits | ≤20 CCN | ≤15 CCN | **≤10 CCN** |
| Static Allocation | Recommended | **Highly Recommended** | **MANDATORY** |

---

## 6. MISRA C Design Compliance

### 6.1 Type System Compliance

**Reference**: See `.opencode/skills/en50128-design/resources/misra-c-design-guidelines.md`

- [ ] Fixed-width types used (`uint8_t`, `int32_t`, etc.) - no native types (`int`, `long`)
- [ ] Boolean type used (`bool` from `<stdbool.h>`) - not `int`
- [ ] Enums used for symbolic constants (states, error codes)
- [ ] Type conversions minimized and documented

### 6.2 Memory Management Compliance

- [ ] Static allocation only (SIL 2+) - no `malloc/calloc/realloc/free`
- [ ] Memory budget documented (static memory, stack usage)
- [ ] No unbounded memory usage (all arrays fixed-size)

**SIL 3-4 Mandatory**: Zero dynamic allocation

### 6.3 Control Flow Compliance

- [ ] No recursion (SIL 3-4 mandatory, SIL 2 highly recommended)
- [ ] All loops bounded (maximum iterations documented)
- [ ] Structured programming (no `goto` except single-level error cleanup with deviation)
- [ ] All switch statements have `default` clause

### 6.4 Error Handling Compliance

- [ ] All fallible functions return `error_t`
- [ ] Output parameters used for results (pointers)
- [ ] All function inputs validated (defensive programming)
- [ ] Errors propagated up call stack

### 6.5 Function Design Compliance

- [ ] Read-only parameters marked `const`
- [ ] Function complexity within limits (≤10 for SIL 3-4)
- [ ] Functions documented (parameters, return value, side effects)

### 6.6 Data Structure Compliance

- [ ] Struct fields ordered largest-to-smallest (minimize padding)
- [ ] Bit fields avoided (or unsigned types used with documentation)
- [ ] Unions avoided (or tagged unions used)
- [ ] Arrays passed with size parameter

---

## 7. Safety and Reliability Checks

### 7.1 Hazard Mitigation

**Reference**: Hazard Log (DOC-21)

- [ ] All identified hazards addressed in architecture
- [ ] Hazard mitigation mechanisms documented
- [ ] Safety requirements traced to design elements
- [ ] Fail-safe behavior defined for all hazardous states

**Review Method**: For each hazard in Hazard Log, verify mitigation in architecture.

**Example**:
```
Hazard H-001: "Unintended acceleration due to sensor failure"
Mitigation (Architecture):
  - Redundant speed sensors (SpeedSensor1, SpeedSensor2)
  - Cross-validation in SpeedMonitorComponent
  - Fail-safe: Set speed to 0 if sensors disagree > threshold
✅ Hazard addressed
```

### 7.2 Fault Detection and Handling

- [ ] Fault detection mechanisms defined (sensor validation, communication checks, watchdog)
- [ ] Fault handling procedures defined (error logging, safe state entry, operator notification)
- [ ] Fault tolerance mechanisms defined (redundancy, voting, graceful degradation)
- [ ] Failure modes analyzed (FMEA performed, reference DOC-24)

### 7.3 Defensive Programming Patterns

- [ ] Input validation at all module boundaries (NULL checks, range checks, plausibility checks)
- [ ] Error detection (hardware faults, communication faults, sensor cross-validation)
- [ ] Error handling (return codes, logging, error propagation)
- [ ] Fail-safe patterns (safe state entry, watchdog timers, emergency stop)

**Reference**: See `.opencode/skills/en50128-design/resources/defensive-programming-patterns.md` for 18 patterns

### 7.4 Safety Integrity Requirements

- [ ] Safety-critical functions identified (SIL level assigned)
- [ ] Safety-critical data identified (protected from corruption)
- [ ] Safety communication protocols defined (CRC, sequence numbers, timeouts)
- [ ] Safety timing constraints defined (response time, deadlines)

---

## 8. Quality Attributes

### 8.1 Modularity

**Reference**: See `.opencode/skills/en50128-design/resources/modularity-guidelines.md`

- [ ] Modules have single, clear responsibility (SRP)
- [ ] Modules have high cohesion (related functions grouped)
- [ ] Modules have low coupling (minimal dependencies)
- [ ] Module size is manageable (200-1000 LOC target, 200-500 for SIL 3-4)
- [ ] Module interfaces are minimal and stable

**Metrics**:
- [ ] Afferent coupling (Ca): Number of modules depending on this module
- [ ] Efferent coupling (Ce): Number of modules this module depends on
- [ ] Instability (I = Ce / (Ca + Ce)): Target < 0.5 for stable modules

### 8.2 Complexity

**Reference**: See `.opencode/skills/en50128-design/resources/complexity-guidelines.md`

- [ ] Cyclomatic complexity within limits:
  - SIL 0-1: ≤ 20 (recommended)
  - SIL 2: ≤ 15 (highly recommended)
  - SIL 3-4: **≤ 10 (mandatory)**

**Verification**: Run Lizard or Cppcheck on design pseudocode or implementation.

```bash
# Check complexity
lizard src/ --CCN 10 --warnings_only
```

- [ ] Complex functions decomposed into smaller helpers
- [ ] Complexity reduction strategies applied (extract functions, guard clauses, lookup tables)

### 8.3 Testability

- [ ] Modules can be tested in isolation (unit testing)
- [ ] Interfaces support mocking (dependency injection or function pointers)
- [ ] Test points defined (inputs, outputs, internal states)
- [ ] Test coverage targets achievable:
  - SIL 0-1: Statement + Branch (HR)
  - SIL 2: Statement + Branch (**M**)
  - SIL 3-4: Statement + Branch + Condition (**M**)

**Review Question**: "Can this module be unit tested to 100% branch coverage?" (SIL 3-4)

### 8.4 Maintainability

- [ ] Architecture is understandable (clear diagrams, documentation)
- [ ] Modules are self-contained (changes localized)
- [ ] Naming is consistent and descriptive
- [ ] Design rationale documented (why decisions were made)

### 8.5 Portability

- [ ] Platform-specific code isolated (HAL layer)
- [ ] Fixed-width types used (no platform-dependent sizes)
- [ ] No compiler-specific extensions (or documented with deviation)
- [ ] Endianness handled explicitly (if relevant)

### 8.6 Performance

- [ ] Worst-case execution time (WCET) analyzed for critical functions
- [ ] Memory usage within budget (static + stack)
- [ ] Throughput requirements achievable (processing rate, latency)
- [ ] Real-time constraints met (deadlines, jitter)

**Design Phase**: Document WCET estimates in design specification.

---

## 9. Traceability Checks

### 9.1 Forward Traceability

**Requirements → Architecture → Design → Code**

- [ ] All requirements (SRS DOC-5) traced to architecture components (SAS DOC-9)
- [ ] All architecture components traced to design modules (SDS DOC-10)
- [ ] All design modules will be traced to code (implementation)
- [ ] Traceability matrices complete and up-to-date

**Verification Commands**:
```bash
# Check forward traceability
traceability.py validate --matrix requirements_to_architecture --sil 3
traceability.py validate --matrix architecture_to_design --sil 3

# Check for gaps
traceability.py check-gaps --source SRS --target SAS
traceability.py check-gaps --source SAS --target SDS
```

**SIL-Dependent Coverage**:
- SIL 0-1: 80% coverage (recommended)
- SIL 2: 90% coverage (highly recommended)
- SIL 3-4: **100% coverage (mandatory)**

### 9.2 Backward Traceability

**Code → Design → Architecture → Requirements**

- [ ] All design elements trace back to architecture components
- [ ] All architecture components trace back to requirements
- [ ] No orphaned design elements (not traced to any requirement)

**Verification**:
```bash
# Find orphaned items
traceability.py check-orphans --type design_element
traceability.py check-orphans --type architecture_component
```

**Expected**: Zero orphans (all design elements justify their existence)

### 9.3 Traceability Documentation

- [ ] Traceability matrices embedded in design documents (DOC-9, DOC-10)
- [ ] Traceability matrices machine-readable (for tool validation)
- [ ] Traceability rationale documented (why design element addresses requirement)

**Example Traceability Entry**:
```markdown
## Traceability: SRS Requirement → Architecture Component

| Requirement ID | Requirement Title | Architecture Component | Rationale |
|----------------|-------------------|------------------------|-----------|
| REQ-SPEED-001 | Monitor train speed every 100ms | SpeedMonitorComponent | Component implements 100ms timer interrupt to read speed sensor |
| REQ-BRAKE-002 | Apply emergency brake if speed > 120 km/h | BrakeControllerComponent | Component checks speed threshold and triggers emergency brake |
```

---

## 10. Tool Validation Checks

### 10.1 Traceability Manager Validation

**Command**:
```bash
traceability.py validate --matrix requirements_to_architecture --sil 3
traceability.py validate --matrix architecture_to_design --sil 3
```

**Expected Results**:
- [ ] Validation passes (no errors)
- [ ] Coverage ≥ 100% (SIL 3-4), ≥ 90% (SIL 2), ≥ 80% (SIL 0-1)
- [ ] No broken links (all referenced items exist)
- [ ] No orphaned items (all design elements traced)

### 10.2 Complexity Analysis Validation

**Command**:
```bash
lizard src/ --CCN 10 --warnings_only  # SIL 3-4
lizard src/ --CCN 15 --warnings_only  # SIL 2
```

**Expected Results**:
- [ ] All functions within complexity limits
- [ ] No functions exceed threshold (SIL 3-4: CCN ≤ 10)

### 10.3 Static Analysis (Design Phase)

**Command** (on pseudocode or early implementation):
```bash
cppcheck --enable=all --xml --xml-version=2 src/ 2> cppcheck_report.xml
```

**Expected Results**:
- [ ] No critical errors (null pointer dereference, buffer overflow)
- [ ] No MISRA C mandatory violations (SIL 3-4)
- [ ] Warnings reviewed and addressed

### 10.4 Workflow Manager Validation

**Command**:
```bash
workspace.py workflow status --document DOC-9  # Architecture
workspace.py workflow status --document DOC-10 # Design
workspace.py workflow status --document DOC-11 # Interfaces
```

**Expected Results**:
- [ ] All documents have passed required reviews (PEER, QUA, VER, VAL, PM)
- [ ] No open review rejections
- [ ] Documents in "Approved" state (ready for baseline)

---

## 11. Review Process

### 11.1 Pre-Review (Author Self-Review)

**Before submitting for review**:
1. Author performs self-review using this checklist
2. Author addresses obvious issues
3. Author ensures document completeness
4. Author runs tool validations (traceability, complexity)
5. Author submits document for review via Workflow Manager

**Command**:
```bash
workspace.py workflow submit DOC-9 --for-review --reviewers PEER,QUA,VER,VAL,PM
```

### 11.2 Peer Review (PEER)

**Focus**: Technical correctness, clarity

**Process**:
1. PEER reads document thoroughly
2. PEER reviews against checklist (Sections 2-4: Completeness, Correctness, Consistency)
3. PEER documents findings in review report
4. PEER approves or rejects via Workflow Manager

**Command**:
```bash
workspace.py workflow review DOC-9 --role PEER --approve --comments "Design looks good, minor comments on Section 3.2"
```

**Review Report Template**:
```markdown
## Peer Review Report - DOC-9 Software Architecture Specification

**Reviewer**: John Smith (PEER)
**Date**: 2026-03-13
**Document Version**: 1.0

### Summary
Overall assessment: APPROVED with minor comments

### Findings
1. Section 3.2: SpeedMonitorComponent - Clarify timer interrupt priority
   - Severity: Minor
   - Action: Document interrupt priority in Section 3.2.3

2. Section 4.1: Interface to BrakeController - Add error handling for CAN timeout
   - Severity: Minor
   - Action: Add error handling specification in Section 4.1.2

### Checklist Results
- Completeness: ✅ Pass
- Correctness: ✅ Pass (with minor comments)
- Consistency: ✅ Pass

### Recommendation
APPROVE with minor revisions
```

### 11.3 Quality Assurance Review (QUA)

**Focus**: Process compliance, standards, quality attributes

**Process**:
1. QUA reviews against checklist (Sections 5-8: EN 50128, MISRA C, Safety, Quality)
2. QUA verifies document template compliance
3. QUA checks traceability
4. QUA approves or rejects

**Command**:
```bash
workspace.py workflow review DOC-9 --role QUA --approve
```

### 11.4 Safety Review (SAFETY_MGR, SIL 3-4)

**Focus**: Hazard mitigation, safety requirements

**Process**:
1. SAFETY_MGR reviews Section 7 (Safety and Reliability Checks)
2. SAFETY_MGR verifies hazard mitigation
3. SAFETY_MGR checks defensive programming patterns
4. SAFETY_MGR approves or rejects

**Command**:
```bash
workspace.py workflow review DOC-9 --role SAFETY_MGR --approve
```

### 11.5 Verification Review (VER, SIL 3-4)

**Focus**: Traceability, completeness, verifiability

**Process**:
1. VER reviews Sections 2, 9 (Completeness, Traceability)
2. VER runs tool validations (traceability.py)
3. VER verifies all requirements addressed
4. VER approves or rejects

**Command**:
```bash
workspace.py workflow review DOC-9 --role VER --approve
```

### 11.6 Validation Review (VAL, SIL 3-4)

**Focus**: Testability, operational scenarios

**Process**:
1. VAL reviews Section 8.3 (Testability)
2. VAL verifies design is testable (unit tests, integration tests, system tests)
3. VAL checks that test coverage targets are achievable
4. VAL approves or rejects

**Command**:
```bash
workspace.py workflow review DOC-9 --role VAL --approve
```

### 11.7 Management Review (PM)

**Focus**: Project alignment, risks, schedule

**Process**:
1. PM reviews high-level architecture
2. PM verifies project risks addressed
3. PM checks schedule impact
4. PM provides final approval

**Command**:
```bash
workspace.py workflow review DOC-9 --role PM --approve
```

### 11.8 Rework Process

**If review is REJECTED**:
1. Author reviews all findings
2. Author updates document to address findings
3. Author resubmits document for review
4. **All reviewers must re-approve** (even if their findings were minor)

**Command**:
```bash
workspace.py workflow resubmit DOC-9 --version 1.1 --changes "Addressed PEER and QUA findings"
```

### 11.9 Baseline and Approval

**After all reviews pass**:
1. Document moves to "Approved" state
2. Document is baselined (version locked)
3. Document is archived
4. Subsequent changes require Change Control

**Command**:
```bash
workspace.py workflow baseline DOC-9 --version 1.0
```

---

## 12. References

### 12.1 EN 50128 References

- **Section 6.2**: Software Verification
- **Table A.3**: Software Architecture techniques
- **Table A.4**: Software Design and Implementation techniques
- **Table A.5**: Verification and Testing techniques
- **Table A.19**: Static Analysis (MANDATORY SIL 3-4)

### 12.2 Related Workflow Documents

- `.opencode/skills/en50128-design/workflows/architecture-design.md` - Architecture design process
- `.opencode/skills/en50128-design/workflows/software-design.md` - Detailed design process
- `.opencode/skills/en50128-design/workflows/interface-design.md` - Interface design process
- `.opencode/skills/en50128-design/workflows/design-review.md` - Design review process

### 12.3 Related Resource Documents

- `.opencode/skills/en50128-design/resources/defensive-programming-patterns.md` - 18 defensive patterns
- `.opencode/skills/en50128-design/resources/complexity-guidelines.md` - Complexity management
- `.opencode/skills/en50128-design/resources/modularity-guidelines.md` - Modular design principles
- `.opencode/skills/en50128-design/resources/misra-c-design-guidelines.md` - MISRA C design considerations

### 12.4 Tool Documentation

- `docs/designs/TRACEABILITY-MANAGER-DESIGN.md` - Traceability validation tool
- `docs/designs/WORKFLOW-MANAGER-DESIGN.md` - Document workflow management tool

### 12.5 Templates

- `.opencode/skills/en50128-design/templates/` - Design document templates (DOC-9, DOC-10, DOC-11)

---

**Document Control**:
- **Version**: 1.0
- **Date**: 2026-03-13
- **Author**: EN50128 Design Skill Enhancement (Phase 2)
- **Status**: Draft
- **Review Status**: Pending QUA review

---

**END OF DOCUMENT**
