# EN 50128 Lifecycle Coordination Skill

## Skill Overview

**Purpose**: Lifecycle orchestration patterns for EN 50128 V-Model compliance

**Primary User**: Lifecycle Coordinator (COD) agent

**When to Use**:
- Phase planning and initialization
- Phase gate reviews
- Phase transitions
- Traceability management
- Document coordination
- Iteration handling

**Key Capabilities**:
1. V-Model phase management
2. SIL-dependent gate criteria
3. Deliverable tracking per Annex C
4. Traceability enforcement
5. Agent coordination across phases

---

## V-Model Phase Management

### V-Model Structure

The EN 50128 V-Model is MANDATORY for SIL 2-4 projects:

```
System Requirements ────────────────────► System Validation
       │                                        ▲
       │                                        │
       ▼                                        │
Software Requirements ──────────────► Software Validation
(SRS - Section 7.2)                    (Section 7.7)
       │                                        ▲
       │                                        │
       ▼                                        │
Software Architecture ──────────────► Integration Testing
(SAS - Section 7.3)                    (Section 7.6)
       │                                        ▲
       │                                        │
       ▼                                        │
Software Design ────────────────────► Module Testing
(SDS - Section 7.3)                    (Section 7.4)
       │                                        ▲
       │                                        │
       ▼                                        │
Implementation ─────────────────────► Unit Testing
(Code - Section 7.4)                   (Section 7.4)

◄───── Verification (6.2) Throughout ──────►
◄───── Quality Assurance (6.5) Throughout ──►
◄───── Configuration Management (6.6) Throughout ──►
◄───── Safety Management Throughout ───────►
```

### Phase Dependencies

| Phase | Depends On | Enables | Parallel Activities |
|-------|-----------|---------|---------------------|
| 0. Initialization | Project creation | Planning | - |
| 1. Planning | Initialization | Requirements | CM, QUA setup |
| 2. Requirements | Planning | Design | SAF (hazards), VER, QUA |
| 3. Design | Requirements | Implementation | VER, QUA, SAF (design review) |
| 4. Implementation | Design | Integration | VER (static), QUA (code review), TST (unit) |
| 5. Integration | Implementation | Validation | VER, QUA, TST (integration) |
| 6. Validation | Integration | Assessment/Deployment | VER, QUA, TST (system) |
| 7. Assessment | Validation (SIL 3-4) | Deployment | ASR (independent) |
| 8. Deployment | Validation or Assessment | Maintenance | CM, VER |

### Parallel Activities (All Phases)

These activities run THROUGHOUT the lifecycle:

1. **Configuration Management (CM)** - Section 6.6
   - Version control
   - Change management
   - Baseline establishment
   - Traceability maintenance

2. **Quality Assurance (QUA)** - Section 6.5
   - Reviews
   - Audits
   - Quality gates
   - Metrics collection

3. **Verification (VER)** - Section 6.2
   - Document verification
   - Code verification
   - Test verification
   - Evidence collection

4. **Safety Management (SAF)** - Throughout
   - Hazard analysis
   - Safety requirements
   - Safety case development
   - Risk management

---

## Phase Gate Criteria

### Gate Structure

Each phase gate has:
1. **Entry Criteria** - Prerequisites to start phase
2. **Exit Criteria** - Requirements to complete phase
3. **Deliverables** - Required documents per Annex C
4. **Quality Criteria** - Metrics, coverage, compliance
5. **Traceability** - RTM completeness
6. **Verification** - Reviews, approvals

### SIL-Dependent Criteria

| Criterion Type | SIL 0-1 | SIL 2 | SIL 3-4 |
|----------------|---------|-------|---------|
| Documentation | Basic | Standard | Complete + Independent Review |
| Traceability | Recommended | Highly Recommended | **MANDATORY** |
| Coverage | Statement (HR) | Statement (HR), Branch (M) | Statement (M), Branch (M), Condition (M) |
| Static Analysis | Optional | Highly Recommended | **MANDATORY** |
| Verification | Internal | Internal | **Independent** |
| Validation | Internal | Internal | **Independent** |
| Assessment | Optional | Optional | **MANDATORY** |

---

## Phase Gate Checklists

### Phase 1 Gate: Planning Complete

**Purpose**: Verify project foundation established

**Deliverables (Annex C Table C.1)**:
- [ ] Software Quality Assurance Plan (SQAP)
- [ ] Software Quality Assurance Verification Report
- [ ] Software Configuration Management Plan (SCMP)
- [ ] Software Verification Plan (SVP)
- [ ] Software Validation Plan (SVaP)

**Quality Criteria**:
- [ ] All planning documents approved
- [ ] Quality gates defined for all phases
- [ ] Verification/validation strategies established
- [ ] Configuration management operational

**Team Organization**:
- [ ] All roles assigned
- [ ] Independence requirements satisfied (SIL 3-4: Validator, Assessor independent)
- [ ] Reporting structure compliant with SIL level
- [ ] Team competency verified

**Tools**:
- [ ] Development environment configured
- [ ] Build system operational
- [ ] Version control initialized
- [ ] Tool qualification complete (if applicable)

**SIL-Specific**:
- **SIL 0-1**: Basic SQAP, SCMP
- **SIL 2**: Add MISRA C compliance plan, static analysis planning
- **SIL 3-4**: Add formal verification plan, independent role verification, assessor engagement

---

### Phase 2 Gate: Requirements Complete

**Purpose**: Verify requirements complete, unambiguous, testable, traceable

**Deliverables (Annex C Table C.1)**:
- [ ] Software Requirements Specification (SRS)
- [ ] Overall Software Test Specification
- [ ] Software Requirements Verification Report
- [ ] Requirements Traceability Matrix (RTM)
- [ ] Hazard Log (if applicable)

**Requirements Quality**:
- [ ] All requirements unambiguous (no undefined terms, clear meaning)
- [ ] All requirements testable (acceptance criteria defined)
- [ ] All requirements traceable (unique IDs assigned)
- [ ] SHALL/SHOULD/MAY keywords used correctly (RFC 2119)
- [ ] SIL levels assigned to all requirements
- [ ] C language constraints considered (data types, memory, timing)

**Traceability**:
- [ ] RTM complete: System Requirements → Software Requirements
- [ ] Forward traceability: All system requirements covered by software requirements
- [ ] Backward traceability: All software requirements traced to system requirements
- [ ] Orphan requirements identified and justified

**Safety**:
- [ ] Hazard analysis complete (FMEA/FTA as appropriate)
- [ ] Safety requirements identified and documented
- [ ] SIL levels assigned per hazard severity
- [ ] Hazard log established and maintained

**EN 50128 Techniques (Table A.2)**:
- [ ] One or more techniques applied:
  - Formal Methods (R for SIL 1-2, HR for SIL 3-4)
  - Modelling (R for all, HR for SIL 3-4)
  - Structured Methodology (R for all, HR for SIL 3-4)
  - Decision Tables (R for all, HR for SIL 3-4)

**SIL-Specific**:
- **SIL 0-1**: Basic requirements, informal methods OK
- **SIL 2**: Structured methodology, traceability highly recommended
- **SIL 3-4**: Formal/semiformal methods highly recommended, traceability MANDATORY

---

### Phase 3 Gate: Architecture & Design Complete

**Purpose**: Verify architecture and design complete, modular, traceable

**Deliverables (Annex C Table C.1)**:
- [ ] Software Architecture Specification (SAS)
- [ ] Software Design Specification (SDS)
- [ ] Software Interface Specifications
- [ ] Software Integration Test Specification
- [ ] Software/Hardware Integration Test Specification
- [ ] Software Architecture and Design Verification Report
- [ ] Software Component Design Specification
- [ ] Software Component Test Specification

**Architecture Quality**:
- [ ] Modular design (MANDATORY for SIL 2+)
- [ ] Module dependencies minimal and documented
- [ ] Interface definitions complete and unambiguous
- [ ] Static memory allocation only (SIL 2+)
- [ ] No dynamic memory allocation (malloc/free forbidden for SIL 2+)
- [ ] No recursion (highly recommended SIL 3-4)

**Design Quality (C-Specific)**:
- [ ] Cyclomatic complexity within limits:
  - SIL 3-4: ≤ 10 per function
  - SIL 2: ≤ 15 per function
  - SIL 0-1: ≤ 20 per function
- [ ] Fixed-width types specified (uint8_t, uint16_t, uint32_t, etc.)
- [ ] Bounded execution time for all functions
- [ ] Defensive programming patterns applied
- [ ] Error handling strategy defined for all failure modes

**Traceability**:
- [ ] RTM updated: Requirements → Architecture → Design
- [ ] All requirements mapped to architectural components
- [ ] All architectural components mapped to design modules
- [ ] No orphan design elements (or justified)

**Safety Design**:
- [ ] Fault detection and diagnosis mechanisms defined (R for SIL 1-2, HR for SIL 3-4)
- [ ] Safety-critical functions identified
- [ ] Defensive programming applied to safety functions
- [ ] Error handling covers all identified failure modes from FMEA

**EN 50128 Techniques (Table A.3)**:
- [ ] Structured Methodology (R for SIL 0-1, HR for SIL 1-2, M for SIL 3-4)
- [ ] Modular Approach (HR for SIL 0-1, M for SIL 2+)
- [ ] Design and Coding Standards defined (HR for SIL 0-2, M for SIL 3-4)
- [ ] Defensive Programming (HR for SIL 1-4)
- [ ] Information Encapsulation (R for SIL 0-1, HR for SIL 2+)

**SIL-Specific**:
- **SIL 0-1**: Basic modular design, informal methods
- **SIL 2**: Modular approach MANDATORY, static allocation MANDATORY
- **SIL 3-4**: All above + structured methodology MANDATORY, complexity ≤10, no recursion

---

### Phase 4 Gate: Implementation & Testing Complete

**Purpose**: Verify code complete, MISRA C compliant, tested, coverage adequate

**Deliverables (Annex C Table C.1)**:
- [ ] Software Source Code and Supporting Documentation
- [ ] Software Source Code Verification Report
- [ ] Software Component Test Report
- [ ] Software Component Design Verification Report

**Code Quality (C-Specific)**:
- [ ] MISRA C:2012 compliance (MANDATORY for SIL 2+):
  - All mandatory rules satisfied
  - All required rules satisfied or deviated with justification
  - Advisory rules considered
  - Deviation log maintained
- [ ] Static allocation only (no malloc/calloc/realloc/free for SIL 2+)
- [ ] No recursion (highly recommended SIL 3-4)
- [ ] Fixed-width integer types (uint8_t, uint16_t, uint32_t, int8_t, etc.)
- [ ] All pointers validated before use
- [ ] All return values checked
- [ ] All inputs validated (defensive programming)
- [ ] Complexity within limits per SIL level

**Static Analysis**:
- [ ] Static analysis performed (PC-lint Plus, Cppcheck, Clang Static Analyzer)
- [ ] All violations resolved or justified in deviation log
- [ ] Complexity analysis performed (Lizard, SonarQube, or similar)
- [ ] All functions within cyclomatic complexity limits
- [ ] No dead code
- [ ] No unreachable code

**Unit Testing**:
- [ ] Unit tests written for all components
- [ ] All unit tests passing
- [ ] Unit test coverage measured:
  - **SIL 0-1**: Statement (HR), Branch (HR)
  - **SIL 2**: Statement (HR), Branch (**M**)
  - **SIL 3-4**: Statement (**M**), Branch (**M**), Condition (**M**)
- [ ] Coverage gaps justified or additional tests added
- [ ] Boundary value testing performed
- [ ] Error handling paths tested
- [ ] Fault injection testing (HR for SIL 3-4)

**Code Review**:
- [ ] Code review conducted (QUA) - MANDATORY for ALL code
- [ ] MISRA C compliance verified in review
- [ ] Defensive programming verified
- [ ] Safety-critical code double-checked (SAF involved)
- [ ] All review findings addressed

**Traceability**:
- [ ] RTM updated: Design → Source Code → Unit Tests
- [ ] All design elements implemented in code
- [ ] All source files mapped to design components
- [ ] All unit tests mapped to design elements and requirements

**EN 50128 Techniques (Table A.4)**:
- [ ] Structured Methodology (R for SIL 0-1, HR for SIL 1-2, M for SIL 3-4)
- [ ] Modular Approach (HR for SIL 0-1, M for SIL 2+)
- [ ] Design and Coding Standards (HR for SIL 0-2, M for SIL 3-4)
- [ ] Analysable Programs (HR for SIL 0-2, M for SIL 3-4)
- [ ] Structured Programming (R for SIL 0-1, HR for SIL 1-2, M for SIL 3-4)

**SIL-Specific**:
- **SIL 0-1**: Basic coding standards, basic testing
- **SIL 2**: MISRA C MANDATORY, branch coverage MANDATORY, static analysis HR
- **SIL 3-4**: All above + static analysis MANDATORY, all coverage types MANDATORY

---

### Phase 5 Gate: Integration Complete

**Purpose**: Verify components integrated, interfaces tested, performance adequate

**Deliverables (Annex C Table C.1)**:
- [ ] Software Integration Test Report
- [ ] Software/Hardware Integration Test Report
- [ ] Software Integration Verification Report

**Integration Activities**:
- [ ] Integration strategy executed (bottom-up, top-down, or sandwich)
- [ ] All components integrated without conflicts
- [ ] Build system produces executable successfully
- [ ] Integration incremental and controlled (not "big bang")

**Integration Testing**:
- [ ] Integration test specification followed
- [ ] All integration tests executed
- [ ] All integration tests passing
- [ ] Interface testing complete (MANDATORY for all SILs - HR)
- [ ] Performance testing complete (R for SIL 1-2, HR for SIL 3-4)
- [ ] Regression testing performed after each integration step

**Interface Testing**:
- [ ] All module interfaces tested
- [ ] All hardware interfaces tested (if applicable)
- [ ] Data flow across interfaces verified
- [ ] Interface error handling tested
- [ ] Boundary conditions tested at interfaces

**Performance Testing** (SIL 3-4):
- [ ] Timing requirements verified
- [ ] Memory usage verified (static allocation limits)
- [ ] Throughput requirements met
- [ ] Worst-case execution time (WCET) verified
- [ ] Resource utilization acceptable (CPU, memory, I/O)

**EN 50128 Techniques (Table A.6)**:
- [ ] Functional and Black-box Testing (HR for all SILs)
- [ ] Performance Testing (R for SIL 1-2, HR for SIL 3-4)

**SIL-Specific**:
- **SIL 0-1**: Basic integration testing
- **SIL 2**: Interface testing highly recommended, performance testing recommended
- **SIL 3-4**: Interface testing highly recommended, performance testing HIGHLY RECOMMENDED

---

### Phase 6 Gate: Validation Complete

**Purpose**: Verify software meets requirements, customer acceptance obtained

**Deliverables (Annex C Table C.1)**:
- [ ] Overall Software Test Report
- [ ] Software Validation Report
- [ ] Tools Validation Report (if applicable)

**Validation Testing**:
- [ ] Overall Software Test Specification executed completely
- [ ] All system tests passing
- [ ] Testing performed in target environment (or representative simulator)
- [ ] Operational scenarios tested
- [ ] Performance testing complete (HR for SIL 1-2, M for SIL 3-4)
- [ ] Functional/black-box testing complete (HR for SIL 0-2, M for SIL 3-4)

**Requirements Validation**:
- [ ] RTM complete end-to-end: Requirements → Design → Code → Tests → Results
- [ ] All requirements validated (every requirement has passing test)
- [ ] All test cases traceable to requirements
- [ ] 100% requirements coverage verified
- [ ] Acceptance criteria met for all requirements

**Independence (SIL 3-4)**:
- [ ] Validation performed by independent Validator
- [ ] Validator does NOT report to Project Manager
- [ ] Validator has no undue influence from development team
- [ ] Validator independence documented in organizational chart

**Customer Acceptance**:
- [ ] Customer/stakeholder acceptance testing performed
- [ ] Customer acceptance obtained (formal sign-off)
- [ ] All acceptance criteria met
- [ ] Any deviations documented and accepted by customer

**EN 50128 Techniques (Table A.7)**:
- [ ] Performance Testing (HR for SIL 1-2, M for SIL 3-4)
- [ ] Functional and Black-box Testing (HR for SIL 0-2, M for SIL 3-4)

**SIL-Specific**:
- **SIL 0-1**: Basic system testing, customer acceptance
- **SIL 2**: Functional testing highly recommended, performance testing highly recommended
- **SIL 3-4**: Independent validation MANDATORY, performance testing MANDATORY, functional testing MANDATORY

---

### Phase 7 Gate: Assessment Complete (SIL 3-4 Only)

**Purpose**: Independent assessment by Assessor, safety case approved

**Deliverables (Annex C Table C.1)**:
- [ ] Software Assessment Plan
- [ ] Software Assessment Report

**Independence (SIL 3-4)**:
- [ ] Assessment performed by independent Assessor
- [ ] Assessor independent from supplier (or Safety Authority discretion)
- [ ] Assessor independent from project
- [ ] Assessor independence documented

**Assessment Activities**:
- [ ] Process compliance audit performed (all EN 50128 requirements)
- [ ] All lifecycle documents reviewed
- [ ] All evidence reviewed (test results, reviews, verifications)
- [ ] Safety case evaluated
- [ ] Traceability verified end-to-end (requirements → deployment)

**Assessment Findings**:
- [ ] All findings documented in Assessment Report
- [ ] All findings addressed or accepted with justification
- [ ] No open critical findings
- [ ] Residual risks acceptable and documented

**Safety Authority**:
- [ ] Safety Authority notified (if required by regulation)
- [ ] Safety Authority approval obtained (if required)
- [ ] All Safety Authority comments addressed

**SIL-Specific**:
- **SIL 0-2**: Assessment optional
- **SIL 3-4**: Assessment MANDATORY, independent Assessor MANDATORY

---

### Phase 8 Gate: Deployment Complete

**Purpose**: Software deployed, maintenance established

**Deliverables (Annex C Table C.1)**:
- [ ] Software Release and Deployment Plan
- [ ] Software Deployment Manual
- [ ] Release Notes
- [ ] Deployment Records
- [ ] Deployment Verification Report
- [ ] Software Maintenance Plan

**Release Package**:
- [ ] Release package complete (executable, libraries, configuration, documentation)
- [ ] Release package verified against baseline
- [ ] Release package signed/authenticated (for SIL 3-4)
- [ ] Deployment Manual complete and tested

**Deployment**:
- [ ] Software deployed to operational environment
- [ ] Deployment procedure followed exactly
- [ ] Deployment verified (smoke tests, operational checks)
- [ ] Deployment records complete (what, when, where, who)

**Maintenance**:
- [ ] Maintenance plan established
- [ ] Change control process active
- [ ] Defect tracking system operational
- [ ] Maintenance team assigned and trained

**Configuration Management**:
- [ ] Final release baselined (version tagged in repository)
- [ ] Baseline 7 established
- [ ] Traceability complete from requirements to deployed code
- [ ] All artifacts archived for future reference

---

## Traceability Management

### Traceability Matrix (RTM) Structure

The Requirements Traceability Matrix SHALL maintain bidirectional traceability:

```
System Req → Software Req → Architecture → Design → Code → Unit Test → Integration Test → System Test → Validation Result
     ↑            ↑             ↑            ↑         ↑        ↑              ↑                ↑              ↑
     └────────────┴─────────────┴────────────┴─────────┴────────┴──────────────┴────────────────┴──────────────┘
                                    Bidirectional Traceability
```

### RTM Format Example

| System Req | Software Req | Design Module | Source File | Unit Test | Integration Test | System Test | Validation | Status |
|------------|--------------|---------------|-------------|-----------|------------------|-------------|------------|--------|
| SYS-001 | SWR-001, SWR-002 | door_control | door.c | test_door.c | int_test_01 | sys_test_05 | VAL-001 | ✓ |
| SYS-002 | SWR-003 | safety_monitor | safety.c | test_safety.c | int_test_02 | sys_test_06 | VAL-002 | ✓ |

### Traceability Verification (Per Phase)

**Phase 2 (Requirements)**:
- [ ] Forward: All system requirements → software requirements
- [ ] Backward: All software requirements → system requirements
- [ ] No orphan software requirements

**Phase 3 (Design)**:
- [ ] Forward: All software requirements → architecture components
- [ ] Forward: All architecture components → design modules
- [ ] Backward: All design modules → architecture → requirements
- [ ] No orphan design modules

**Phase 4 (Implementation)**:
- [ ] Forward: All design modules → source files
- [ ] Forward: All source files → unit tests
- [ ] Backward: All source files → design
- [ ] Backward: All unit tests → requirements
- [ ] No untested source files

**Phase 5 (Integration)**:
- [ ] Forward: All components → integration tests
- [ ] Backward: All integration tests → requirements
- [ ] Interface coverage complete

**Phase 6 (Validation)**:
- [ ] Forward: All requirements → system tests
- [ ] Backward: All system tests → requirements
- [ ] Forward: All system tests → validation results
- [ ] 100% requirements coverage
- [ ] All validation results PASS

### Traceability Gap Detection

COD SHALL detect and report:
1. **Orphan requirements**: Software requirements with no parent system requirement
2. **Uncovered requirements**: Requirements with no design/code/test
3. **Orphan code**: Source files not mapped to design
4. **Untested code**: Code not covered by unit/integration/system tests
5. **Unused tests**: Tests not mapped to requirements

---

## Document Coordination

### Annex C Document Control Summary

EN 50128 Annex C Table C.1 defines document control by phase:

| Phase | Documents | Written By | 1st Check | 2nd Check |
|-------|-----------|------------|-----------|-----------|
| **Planning** | SQAP, SCMP, SVP, SVaP | Various | VER | VAL |
| **Requirements** | SRS, Test Spec | REQ, TST | VER | VAL |
| **Design** | SAS, SDS, Interfaces | DES | VER | VAL |
| **Implementation** | Source Code, Reports | IMP, VER | VER | VAL |
| **Integration** | Integration Reports | INT | VER | VAL |
| **Validation** | Validation Report | VAL | VER | - |
| **Assessment** | Assessment Report | ASR | VER | - |
| **Deployment** | Deployment Docs | Various | VER | VAL |

### Document Approval Workflow

1. **Author** creates document
2. **1st Check** (usually VER) verifies document
3. **2nd Check** (usually VAL) validates document
4. **Baseline** established in configuration management
5. **Change Control** active for all changes

### Document Baseline Strategy

| Baseline | Phase | Contents | When Established |
|----------|-------|----------|------------------|
| **Baseline 0** | Planning | SQAP, SCMP, SVP, SVaP | Planning gate passed |
| **Baseline 1** | Requirements | SRS, RTM, Test Specs | Requirements gate passed |
| **Baseline 2** | Design | SAS, SDS, Interfaces | Design gate passed |
| **Baseline 3** | Implementation | Source Code, Unit Tests | Implementation gate passed |
| **Baseline 4** | Integration | Integration Tests, Reports | Integration gate passed |
| **Baseline 5** | Validation | Validation Report | Validation gate passed |
| **Baseline 6** | Assessment | Assessment Report | Assessment gate passed (SIL 3-4) |
| **Baseline 7** | Deployment | Release Package | Deployment complete |

---

## Iteration Handling

### Feedback Loops in V-Model

EN 50128 Section 5.3.2.2: "The lifecycle model shall take into account the possibility of iterations in and between phases."

**Common Iteration Patterns**:

1. **Requirements Feedback** (from Design):
   - Design reveals ambiguous/infeasible requirements
   - Return to Requirements phase
   - Update SRS
   - Update RTM
   - Re-verify design against updated requirements

2. **Design Feedback** (from Implementation):
   - Implementation reveals design issues
   - Return to Design phase
   - Update SDS
   - Update RTM
   - Re-implement affected code

3. **Validation Feedback** (from Validation):
   - System testing reveals requirement not met
   - Trace back to root cause (requirements/design/code)
   - Fix at appropriate level
   - Re-test affected areas
   - Update traceability

### Iteration Control

When iteration detected:

1. **COD detects iteration request** (from agent or user)
2. **Assess impact**:
   - Which phase to return to?
   - What artifacts affected?
   - What tests need re-execution?
3. **User approval required** (for requirements changes)
4. **Change control activated**:
   - Change Request (CR) created
   - Impact analysis performed
   - Change approved by CCB (Change Control Board)
5. **Execute iteration**:
   - Return to appropriate phase
   - Update affected artifacts
   - Maintain traceability
   - Re-verify/re-validate
6. **Update lifecycle state**:
   - Log iteration in `LIFECYCLE_STATE.md`
   - Update phase status
   - Track regression testing

### Regression Testing Requirements

After iteration:
- [ ] All affected unit tests re-executed
- [ ] All affected integration tests re-executed
- [ ] All affected system tests re-executed
- [ ] Regression test results documented
- [ ] Traceability updated

---

## Agent Coordination Patterns

### Phase-to-Agent Mapping

| Phase | Primary Agents | Supporting Agents | Cross-Cutting |
|-------|---------------|-------------------|---------------|
| **0. Init** | COD | - | - |
| **1. Planning** | PM | QUA, CM, VER, VAL, SAF | CM, QUA |
| **2. Requirements** | REQ | SAF, TST | VER, VAL, QUA, CM |
| **3. Design** | DES | INT, SAF | VER, VAL, QUA, CM |
| **4. Implementation** | IMP | TST, SAF | VER, QUA, CM |
| **5. Integration** | INT | TST | VER, VAL, QUA, CM |
| **6. Validation** | VAL | TST | VER, QUA, CM |
| **7. Assessment** | ASR (external) | VER | CM |
| **8. Deployment** | PM | CM | VER, VAL, CM |

### Agent Handoff Protocol

When phase transition authorized:

1. **COD announces phase transition**:
   ```
   Phase transition authorized: Design → Implementation
   
   Handoff from:
     - DES (Designer) - design artifacts complete
     - INT (Integrator) - integration test specs ready
   
   Handoff to:
     - IMP (Implementer) - begin C code implementation
     - TST (Tester) - begin unit test development
   
   Cross-cutting agents continue:
     - VER (Verifier) - verify source code
     - QUA (Quality) - conduct code reviews
     - CM (Config Mgmt) - baseline code
   ```

2. **Receiving agents acknowledge**
3. **COD monitors progress** in new phase
4. **COD verifies previous phase artifacts available**

---

## COD State Management

### LIFECYCLE_STATE.md Structure

Each project SHALL have `LIFECYCLE_STATE.md` in project root:

```markdown
# Project Lifecycle State

## Project Information
- **Project Name**: Train Door Control System
- **SIL Level**: 3
- **Lifecycle Model**: V-Model
- **COD Mode**: Strict Gatekeeper
- **Created**: 2026-02-10
- **Last Updated**: 2026-02-18

## Current Status
- **Current Phase**: Design (Phase 3)
- **Phase Started**: 2026-02-15
- **Days in Phase**: 3
- **Completion**: 75% (estimated)

## Phase History

| Phase | Status | Started | Completed | Gate Passed | Notes |
|-------|--------|---------|-----------|-------------|-------|
| 0. Initialization | Complete | 2026-02-10 | 2026-02-10 | N/A | COD initialized |
| 1. Planning | Complete | 2026-02-10 | 2026-02-10 | 2026-02-10 | All plans approved |
| 2. Requirements | Complete | 2026-02-10 | 2026-02-15 | 2026-02-15 | 42 requirements |
| 3. Design | In Progress | 2026-02-15 | - | - | 8/8 deliverables |
| 4. Implementation | Not Started | - | - | - | - |
| 5. Integration | Not Started | - | - | - | - |
| 6. Validation | Not Started | - | - | - | - |
| 7. Assessment | Not Started | - | - | - | Required for SIL 3 |
| 8. Deployment | Not Started | - | - | - | - |

## Deliverable Status

### Phase 3 (Design) - In Progress
- [x] Software Architecture Specification (SAS) - Approved 2026-02-16
- [x] Software Design Specification (SDS) - Approved 2026-02-17
- [ ] Software Interface Specifications - In Progress
- [ ] Software Integration Test Specification - Draft
- [x] Software Component Design Specification - Approved 2026-02-17
- [x] Software Component Test Specification - Approved 2026-02-18
- [ ] Architecture and Design Verification Report - Pending
- [x] Component Design Verification Report - Approved 2026-02-18

## Requirement Approval History

| Date | Activity | Scope | Approved By | Files Modified |
|------|----------|-------|-------------|----------------|
| 2026-02-11 | Establish | Initial SRS (42 requirements) | User | docs/SRS.md, docs/RTM.md |

## Change Log

| Date | Phase | Change Type | Description | Impact | CR# |
|------|-------|-------------|-------------|--------|-----|
| 2026-02-16 | Design | Clarification | Updated interface timing specs | Low | CR-001 |

## Gate Check History

| Date | Phase | Result | Criteria | Notes |
|------|-------|--------|----------|-------|
| 2026-02-10 | Planning | PASSED | 5/5 | All planning docs approved |
| 2026-02-15 | Requirements | PASSED | 6/6 | 42 requirements, 100% traceable |

## Traceability Status

- System Req → Software Req: 100% (38/38)
- Software Req → Design: 100% (42/42)
- Design → Code: 0% (not started)
- Code → Unit Tests: 0% (not started)
- Requirements → System Tests: 100% (42/42 specified)

## Metrics

- Requirements: 42 total (38 functional, 4 safety)
- Design Modules: 12
- Cyclomatic Complexity: Max 8 (target ≤10 for SIL 3)
- Lines of Code: 0 (not started)
- Test Coverage: 0% (not started)

## Agents Active

- DES (Designer) - Last activity: 2 hours ago
- INT (Integrator) - Last activity: 4 hours ago
- VER (Verifier) - REQUIRED (design verification pending)

## Next Steps

1. Complete Software Interface Specifications (DES)
2. Finalize Integration Test Specification (INT)
3. Perform design verification (VER)
4. Generate Architecture and Design Verification Report (VER)
5. Run /cod gate-check design
```

---

## Summary

This skill provides COD with:

1. **V-Model phase management** - Structure, dependencies, parallel activities
2. **Phase gate checklists** - SIL-dependent criteria for all 8 phases
3. **Traceability management** - RTM structure, verification, gap detection
4. **Document coordination** - Annex C mapping, approval workflows, baselines
5. **Iteration handling** - Feedback loops, change control, regression
6. **Agent coordination** - Phase-to-agent mapping, handoff protocols
7. **State management** - LIFECYCLE_STATE.md structure and content

**Key Principle**: COD orchestrates the lifecycle to ensure EN 50128 V-Model compliance while enabling efficient development. Be strict where safety demands (SIL 3-4), but be helpful and guiding at all times.
