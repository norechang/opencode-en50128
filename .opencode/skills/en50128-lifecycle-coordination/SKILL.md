---
name: en50128-lifecycle-coordination
description: Project management and coordination for EN 50128 railway software development
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  role: lifecycle-coordinator
---

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

The EN 50128 V-Model is highly recommended per §5.3, Figures 3–4; alternative lifecycle models are permissible per §5.3.2.14 with appropriate justification:

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
| 3. Design | Requirements | Component Design | VER, QUA, SAF (design review) |
| 4. Component Design | Design | Implementation | VER, QUA |
| 5. Implementation | Component Design | Integration | VER (static), QUA (code review), TST (unit) |
| 6. Integration | Implementation | Validation | VER, QUA, TST (integration) |
| 7. Validation | Integration | Assessment/Deployment | VER, QUA, TST (system) |
| 8. Assessment | Validation (SIL 1-4) | Deployment | ASR (independent) |
| 9. Deployment | Validation or Assessment | Maintenance | CM, VER |

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

**Deliverables**: See [`DELIVERABLES.md`](../../../DELIVERABLES.md) — Phase 1: Planning (Annex C items 1–5).

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

**Deliverables**: See [`DELIVERABLES.md`](../../../DELIVERABLES.md) — Phase 2: Requirements (Annex C items 6–8).

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

**Deliverables**: See [`DELIVERABLES.md`](../../../DELIVERABLES.md) — Phase 3: Architecture & Design (Annex C items 9–14) and Phase 4: Component Design (Annex C items 15–17).

> Note: Component Design Specification and Component Test Specification (items 15–16) are Phase 4 deliverables listed here for gate awareness; they are formally required by the Phase 4 gate.

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

### Phase 4 Gate: Component Design Complete

**Purpose**: Verify detailed component designs and component test specifications are complete and approved

**Deliverables**: See [`DELIVERABLES.md`](../../../DELIVERABLES.md) — Phase 4: Component Design (Annex C items 15–17).

**Design Quality**:
- [ ] Component design traceable to Software Design Specification
- [ ] Component test strategies defined (test cases traceable to component requirements)
- [ ] Complexity limits respected per SIL (≤10 SIL 3-4, ≤15 SIL 2, ≤20 SIL 0-1)

**SIL-Specific**:
- **SIL 0-1**: Component designs recommended
- **SIL 2**: Component designs highly recommended; VER review highly recommended
- **SIL 3-4**: Component designs, test specs, and VER report MANDATORY

---

### Phase 5 Gate: Implementation & Testing Complete

**Purpose**: Verify code complete, MISRA C compliant, tested, coverage adequate

**Deliverables**: See [`DELIVERABLES.md`](../../../DELIVERABLES.md) — Phase 5: Implementation & Testing (Annex C items 18–20).

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

### Phase 6 Gate: Integration Complete

**Purpose**: Verify components integrated, interfaces tested, performance adequate

**Deliverables**: See [`DELIVERABLES.md`](../../../DELIVERABLES.md) — Phase 6: Integration (Annex C items 21–22).

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

### Phase 7 Gate: Validation Complete

**Purpose**: Verify software meets requirements, customer acceptance obtained

**Deliverables**: See [`DELIVERABLES.md`](../../../DELIVERABLES.md) — Phase 7: Validation (Annex C items 23–27).

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

### Phase 8 Gate: Assessment Complete (SIL 1-4)

**Purpose**: Independent assessment by Assessor, safety case approved

**Deliverables**: See [`DELIVERABLES.md`](../../../DELIVERABLES.md) — Phase 8: Assessment (Annex C items 45–46).

**Independence (SIL 1-4)**:
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
- **SIL 0**: Assessment exempt per §6.4.1.2
- **SIL 1-2**: Assessment MANDATORY per §6.4.1.1 and §5.1.2.4
- **SIL 3-4**: Assessment MANDATORY, independent Assessor MANDATORY

---

### Phase 9 Gate: Deployment Complete

**Purpose**: Software deployed, maintenance established

**Deliverables**: See [`DELIVERABLES.md`](../../../DELIVERABLES.md) — Phase 9: Deployment (Annex C items 36–40) and Phase 10: Maintenance (Annex C items 41–44).

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
- [ ] Baseline 8 established
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

**Phase 5 (Implementation)**:
- [ ] Forward: All design modules → source files
- [ ] Forward: All source files → unit tests
- [ ] Backward: All source files → design
- [ ] Backward: All unit tests → requirements
- [ ] No untested source files

**Phase 6 (Integration)**:
- [ ] Forward: All components → integration tests
- [ ] Backward: All integration tests → requirements
- [ ] Interface coverage complete

**Phase 7 (Validation)**:
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

See [`DELIVERABLES.md`](../../../DELIVERABLES.md) for the complete Annex C Table C.1 document control summary (all phases, document names, author roles, and check columns).

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
| **Baseline 3** | Component Design | Component Design Specs, Component Test Specs | Component Design gate passed |
| **Baseline 4** | Implementation | Source Code, Unit Tests | Implementation gate passed |
| **Baseline 5** | Integration | Integration Tests, Reports | Integration gate passed |
| **Baseline 6** | Validation | Validation Report | Validation gate passed |
| **Baseline 7** | Assessment | Assessment Report | Assessment gate passed (SIL 1-4) |
| **Baseline 8** | Deployment | Release Package | Deployment complete |

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
| **4. Component Design** | DES | TST | VER, QUA, CM |
| **5. Implementation** | IMP | TST, SAF | VER, QUA, CM |
| **6. Integration** | INT | TST | VER, VAL, QUA, CM |
| **7. Validation** | VAL | TST | VER, QUA, CM |
| **8. Assessment** | ASR (external) | VER | CM |
| **9. Deployment** | PM | CM | VER, VAL, CM |

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
| 4. Component Design | Not Started | - | - | - | - |
| 5. Implementation | Not Started | - | - | - | - |
| 6. Integration | Not Started | - | - | - | - |
| 7. Validation | Not Started | - | - | - | - |
| 8. Assessment | Not Started | - | - | - | Required for SIL 3 |
| 9. Deployment | Not Started | - | - | - | - |

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
5. Run @cod gate-check design
```

---

## Comprehensive Workflows

This skill includes **4 comprehensive workflows** (~300 pages, ~12,000 lines) in the `workflows/` directory:

### 1. Phase Gate Management Workflow

**File**: `workflows/phase-gate-management-workflow.md` (2,319 lines, ~93 pages)

**Purpose**: Complete phase gate enforcement with SIL-specific criteria for all 8 lifecycle phases

**Content**:
- **Gate Structure**: Entry criteria, exit criteria, deliverables, quality metrics, traceability, verification, gate decision
- **8 Complete Phase Gates**: Planning (1), Requirements (2), Design (3), Component Design (4), Implementation (5), Integration (6), Validation (7), Assessment (8, SIL 1-4), Deployment (9)
- **SIL-Dependent Enforcement**: Advisory (SIL 0-1), Semi-strict (SIL 2), Strict (SIL 3-4)
- **Python Gate Checker**: Complete gate validation script (~400 lines) with automated criteria checking
- **Tool Integration**: `workspace.py trace`, `workspace.py wf` examples for each gate
- **Complete Examples**: Full SIL 3 gate sequence from planning through deployment

**Key Features**:
- **Mandatory Deliverables** per EN 50128 Annex C Table C.1 for each phase
- **Quality Thresholds**: Coverage (statement, branch, MC/DC), complexity (CCN ≤10 SIL 3-4), MISRA C compliance (zero mandatory violations SIL 2+)
- **Traceability Gates**: RTM validation at each phase (100% coverage MANDATORY SIL 3-4)
- **Approval Workflows**: SIL-specific approval chains (PM, QUA, VER, VAL, SAF, ASR)
- **Gate Decisions**: PASS (proceed), BLOCK (fix issues, MANDATORY SIL 3-4), CONDITIONAL (proceed with actions, SIL 0-2)

**Usage**:
```bash
# Check if phase is ready for gate
@cod gate-check requirements

# COD validates:
# ✓ Software Requirements Specification (SRS) complete
# ✓ Traceability: System Req → Software Req (100%)
# ✓ Requirements count: 42 (38 functional, 4 safety)
# ✓ QUA review: APPROVED
# ✓ VER review: APPROVED
# 
# Gate Decision: PASS
# Authorization: Proceed to Design phase (Phase 3)
```

**EN 50128 References**:
- Section 5.3 (Software Lifecycle)
- Annex C Table C.1 (Document Control Summary)
- Section 6.2 (Verification)
- Section 6.5 (Quality Assurance)

---

### 2. V-Model Orchestration Workflow

**File**: `workflows/v-model-orchestration-workflow.md` (1,507 lines, ~60 pages)

**Purpose**: Phase initialization, execution, transition, and agent coordination across the complete V-Model lifecycle

**Content**:
- **Phase Initialization**: Entry criteria, resource allocation, tool setup, agent assignment
- **Phase Execution**: Progress tracking, deliverable creation, parallel activities (CM, QUA, VER, SAF)
- **Phase Transition**: Exit criteria, baseline establishment, handoff protocols, LIFECYCLE_STATE.md updates
- **Agent Coordination**: Phase-to-agent mapping, multi-agent coordination patterns, cross-cutting activities
- **LIFECYCLE_STATE.md Management**: Complete structure, update triggers, state tracking, Python management script (~150 lines)
- **Python Automation**: Phase transition checker (~200 lines), agent status tracker (~150 lines)
- **Complete Example**: Full SIL 3 project lifecycle from initialization through deployment

**Key Features**:
- **9 Phase Definitions**: Planning, Requirements, Design, Component Design, Implementation, Integration, Validation, Assessment (SIL 1-4), Deployment
- **Agent Orchestration**: COD coordinates 12 agents (REQ, DES, IMP, TST, INT, VER, VAL, SAF, QUA, CM, PM, ASR)
- **Parallel Activities**: CM (version control), QUA (reviews), VER (verification), SAF (hazard analysis) run throughout
- **State Management**: LIFECYCLE_STATE.md tracks current phase, deliverables, metrics, agent status, gate history
- **Baseline Management**: CM establishes baselines at each phase gate, COD enforces baseline control

**Usage**:
```bash
# Initialize phase
@cod init-phase design --sil 3

# COD checks:
# ✓ Previous phase (requirements) complete
# ✓ Gate 2 (Requirements) PASSED
# ✓ Baseline established (v1.0.0)
# ✓ Agents assigned: DES (primary), VER, QUA, SAF (reviews)
# 
# Phase 3 (Design) initialized
# Status: IN_PROGRESS

# Execute phase with progress tracking
@cod execute-phase design

# COD orchestrates:
# - DES creates Software Architecture Specification (SAS)
# - DES creates Software Design Specification (SDS)
# - DES creates Software Interface Specifications (SIS)
# - SAF reviews design for safety implications
# - QUA performs design review
# - VER verifies design completeness and traceability
# 
# Progress: 75% (3/4 deliverables complete)

# Transition to next phase
@cod transition-phase --from design --to implementation

# COD validates:
# ✓ Design phase complete (100%)
# ✓ Gate 3 (Design) PASSED
# ✓ Baseline v2.0.0 established
# ✓ Handoff to IMP agent
# 
# Current phase: Implementation (Phase 4)
```

**LIFECYCLE_STATE.md Structure**:
```yaml
project:
  name: "Railway Door Control System"
  sil: 3
  baseline: "v2.0.0"
  
phases:
  requirements:
    status: COMPLETE
    start_date: "2026-02-15"
    end_date: "2026-02-28"
    deliverables:
      - id: SRS-v1.0
        status: APPROVED
    baseline: "v1.0.0"
    gate_status: PASSED
    
  design:
    status: COMPLETE
    start_date: "2026-03-01"
    end_date: "2026-03-15"
    deliverables:
      - id: SAS-v1.0
        status: APPROVED
      - id: SDS-v1.0
        status: APPROVED
    baseline: "v2.0.0"
    gate_status: PASSED
    
  implementation:
    status: IN_PROGRESS
    start_date: "2026-03-16"
    deliverables: []
```

**EN 50128 References**:
- Section 5.3.2 (Lifecycle Requirements)
- Section 5.3.2.5 ("All activities to be performed during a phase shall be defined and planned prior to commencement")
- Annex C Table C.1 (Phase-to-deliverable mapping)

---

### 3. Traceability and RTM Management Workflow

**File**: `workflows/traceability-rtm-workflow.md` (1,481 lines, ~59 pages)

**Purpose**: Complete Requirements Traceability Matrix (RTM) management with bidirectional traceability and gap detection

**Content**:
- **RTM Structure**: System Req → Software Req → Architecture → Design → Code → Unit Tests → Integration Tests → System Tests → Validation Results
- **RTM Creation**: Phase 2 (Requirements) initialization with system requirements traceability
- **RTM Updates**: Phase-by-phase update procedures (Phases 3-6)
- **Bidirectional Traceability**: Forward coverage (requirements → implementation), backward coverage (implementation → requirements)
- **Gap Detection**: 6 gap types (uncovered requirements, orphan design, untraced code, untested code, untested requirements, unvalidated tests)
- **SIL-Specific Requirements**: 100% coverage MANDATORY SIL 3-4, HR SIL 2, R SIL 0-1
- **Complete workspace.py Commands**: 60+ trace command examples with full syntax
- **RTM Audit**: Independent verification, audit checklist, audit report template
- **Python RTM Gap Detector**: Complete script (~250 lines) with detailed gap analysis
- **Complete Example**: Full SIL 3 door control RTM with 42 requirements traced end-to-end

**Key Features**:
- **Bidirectional Links**: Every requirement traces forward to implementation/tests AND backward from implementation/tests to requirements
- **Gap Detection Algorithms**: 6 gap types with automated detection
  1. **Uncovered Requirements**: Requirements with no design link
  2. **Orphan Design**: Design elements with no requirements link
  3. **Untraced Code**: Code with no design link
  4. **Untested Code**: Code with no unit test link
  5. **Untested Requirements**: Requirements with no test coverage
  6. **Unvalidated Tests**: Tests with no validation result
- **Coverage Metrics**: Forward coverage %, backward coverage %, gap count
- **SIL Compliance**: Automated SIL threshold checking (100% MANDATORY SIL 3-4)

**Usage**:
```bash
# Initialize RTM (Phase 2 - Requirements)
workspace.py trace init --project door-control --sil 3

# Add requirements to RTM
workspace.py trace add-requirement \
  --req-id REQ-DOOR-001 \
  --description "Door shall close within 3 seconds" \
  --sil 3

# Link system requirement to software requirement
workspace.py trace link \
  --from SYSTEM-REQ-010 \
  --to REQ-DOOR-001 \
  --type requirements

# Phase 3 (Design): Link requirements to design
workspace.py trace link \
  --from REQ-DOOR-001 \
  --to DES-DOOR-010 \
  --type design

# Phase 4 (Implementation): Link design to code and tests
workspace.py trace link \
  --from DES-DOOR-010 \
  --to src/door_control.c:50 \
  --type implementation

workspace.py trace link \
  --from src/door_control.c:50 \
  --to TEST-DOOR-050 \
  --type unit_test

# Validate traceability (detect gaps)
workspace.py trace validate --sil 3

# Output:
# RTM Validation Report (SIL 3)
# ==============================
# 
# ✓ Forward Coverage: 100% (42/42 requirements traced)
# ✓ Backward Coverage: 100% (42/42 design elements traced)
# ✓ No gaps detected
# 
# Traceability Complete: YES

# Generate RTM report
workspace.py trace report \
  --format markdown \
  --output docs/traceability/requirements_traceability_matrix.md

# RTM audit (independent verification)
workspace.py trace audit --sil 3 --auditor VER

# Output: RTM Audit Report with verification evidence
```

**Gap Detection Example** (gaps present):
```bash
workspace.py trace validate --sil 3

# RTM Validation Report (SIL 3)
# ==============================
# 
# ❌ GAPS DETECTED (6 gaps)
# 
# Uncovered Requirements (2):
# - REQ-DOOR-025: No design link
# - REQ-DOOR-026: No design link
# 
# Orphan Design (1):
# - DES-DOOR-999: No requirements link (orphan)
# 
# Untraced Code (0): None
# 
# Untested Code (2):
# - src/door_control.c:150: No unit test link
# - src/door_control.c:200: No unit test link
# 
# Untested Requirements (1):
# - REQ-DOOR-030: No test coverage
# 
# Unvalidated Tests (0): None
# 
# Forward Coverage: 95% (40/42 requirements traced)
# Backward Coverage: 98% (41/42 design elements traced)
# 
# ❌ Traceability Complete: NO
# ❌ SIL 3 Threshold: FAIL (requires 100%)
# 
# ACTION: Fix gaps before proceeding to gate check
```

**EN 50128 References**:
- Table A.9 (Traceability: MANDATORY SIL 3-4, HR SIL 2)
- Section 5.3.2.7 ("For each document, traceability shall be provided")
- Section 6.2 (Verification - traceability verification required)

---

### 4. Iteration and Change Management Workflow

**File**: `workflows/iteration-change-management-workflow.md` (1,543 lines, ~62 pages)

**Purpose**: Handle feedback loops, change control, and regression testing throughout lifecycle with formal Change Request (CR) process

**Content**:
- **EN 50128 Iteration Principles**: Section 5.3.2.2 explicitly allows iterations with change control
- **Feedback Loop Detection**: Algorithm to identify target phase and iteration scope based on issue type
- **Change Request Process**: Formal CR workflow with Change Control Board (CCB) approval (SIL-dependent)
- **Iteration Execution**: Step-by-step process to return to target phase, update artifacts, maintain traceability
- **Regression Testing Requirements**: SIL-dependent test selection (full regression SIL 3-4, affected + related SIL 2)
- **Traceability Updates**: Maintain RTM bidirectional links during iteration (MANDATORY SIL 2+)
- **LIFECYCLE_STATE.md Change Log**: Iteration tracking for audit trail
- **Tool Integration**: `workspace.py trace` and `workspace.py wf` for iteration management
- **Python Automation**: CR impact analyzer (~250 lines), regression test selector (~200 lines)
- **Complete Examples**: SIL 3 requirements feedback iteration, SIL 2 design feedback iteration

**Key Features**:
- **5 Iteration Types**: Requirements feedback, design feedback, implementation feedback, validation feedback, safety feedback
- **Feedback Loop Algorithm**: Determines target phase based on issue type and severity
- **CR Document Template**: Complete change request document with impact analysis, CCB review, implementation tracking
- **CCB Composition**: SIL-dependent (SIL 0: PM only, SIL 1: PM + QUA, SIL 2: PM + QUA + CM, SIL 3-4: PM + QUA + CM + SAF + VER + ASR)
- **Iteration Scope Calculation**: All phases from target phase to current phase must be updated
- **Regression Test Selection**:
  - **SIL 0-1**: Optional (affected tests recommended)
  - **SIL 2**: Affected + related tests (1 hop) MANDATORY
  - **SIL 3-4**: Full regression suite (ALL tests) MANDATORY

**Usage** (SIL 3 requirements iteration):
```bash
# STEP 1: VAL detects missing requirement
@val validate-system
# Output: ❌ System Test Failed: TEST-SYS-025 (missing requirement for audible alert)

# STEP 2: VAL creates change request
# CR-DOOR-0001: Add requirement for audible alert on timeout

# STEP 3: Impact analysis
python3 tools/cr_impact_analyzer.py \
  --cr-id CR-DOOR-0001 \
  --affected-req NEW \
  --change-type add \
  --rtm-file docs/traceability/requirements_traceability_matrix.md

# Output:
# Downstream Impact: Requirements, Design, Implementation, Tests
# Regression Tests (SIL 3): 25 tests (FULL SUITE)
# Effort Estimate: 72 person-hours

# STEP 4: CCB approval (SIL 3 = PM + QUA + CM + SAF + VER)
# CCB Decision: APPROVED
# Safety Approval: APPROVED (SAF)

# STEP 5: COD authorizes iteration
@cod start-iteration \
  --cr-id CR-DOOR-0001 \
  --trigger-phase validation \
  --target-phase requirements \
  --reason "Add missing requirement"

# COD updates LIFECYCLE_STATE.md:
# iterations:
#   - iteration_id: ITER-001
#     cr_id: CR-DOOR-0001
#     status: IN_PROGRESS

# STEP 6-8: Update artifacts (REQ, DES, IMP)
# REQ adds REQ-DOOR-025
# DES creates DES-DOOR-030
# IMP implements alert_controller.c

# STEP 9: Update traceability
workspace.py trace add-requirement --req-id REQ-DOOR-025 --sil 3
workspace.py trace link --from REQ-DOOR-025 --to DES-DOOR-030 --type design
workspace.py trace link --from DES-DOOR-030 --to src/alert_controller.c:50 --type implementation
workspace.py trace link --from src/alert_controller.c:50 --to TEST-DOOR-080 --type unit_test

# STEP 10: Regression testing (SIL 3 = FULL)
python3 tools/regression_test_selector.py --sil 3 --rtm-file rtm.md --output tests.txt
./scripts/run_regression_tests.sh tests.txt
# Result: 25/25 PASS

# STEP 11: VER verifies, VAL validates
@ver verify-iteration --iteration-id ITER-001
# Result: APPROVED (traceability 100%, coverage 100%)

@val validate-iteration --iteration-id ITER-001
# Result: APPROVED (TEST-SYS-025 now PASS)

# STEP 12: COD completes iteration
@cod complete-iteration --iteration-id ITER-001

# COD updates LIFECYCLE_STATE.md:
# iterations:
#   - iteration_id: ITER-001
#     status: COMPLETE
#     artifacts_updated: [REQ-DOOR-025, DES-DOOR-030, src/alert_controller.c, TEST-DOOR-080]
#     regression_tests_passed: 25
#     traceability_validated: true

# ✓ Iteration COMPLETE
# ✓ Ready to proceed to Assessment phase
```

**Iteration Completion Criteria** (SIL 3-4):
- ✓ All iteration scope phases re-completed
- ✓ **Full regression suite passed** (MANDATORY)
- ✓ Traceability updated and validated (100% coverage)
- ✓ VER re-verification complete
- ✓ VAL re-validation complete
- ✓ Baselines updated
- ✓ CR closed with all approvals

**EN 50128 References**:
- Section 5.3.2.2 ("The lifecycle model shall take into account the possibility of iterations in and between phases")
- Section 6.4 (Problem Reporting and Change Control)
- Section 6.6 (Configuration Management)

---

## Workflow Selection by SIL

| Task | Workflow | SIL 0-1 | SIL 2 | SIL 3-4 | Key Features |
|------|----------|---------|-------|---------|--------------|
| **Phase Gate Check** | Phase Gate Management | Advisory | Semi-strict | Strict | BLOCK on violations (SIL 3-4) |
| **Phase Transition** | V-Model Orchestration | Informal | Structured | Formal | Baseline control (SIL 2+) |
| **Traceability** | RTM Management | Optional | HR | **MANDATORY** | 100% coverage required (SIL 3-4) |
| **Iteration** | Change Management | Informal | CR required | Formal CR + CCB | Full regression (SIL 3-4) |

---

## Tool Integration

All workflows include extensive `workspace.py` command examples for traceability and workflow management:

### Traceability Commands (`workspace.py trace`)

**RTM Initialization**:
```bash
workspace.py trace init --project <name> --sil <0-4>
```

**Add Requirements**:
```bash
workspace.py trace add-requirement \
  --req-id REQ-XXX-NNN \
  --description "Requirement text" \
  --sil <0-4>
```

**Link Artifacts** (bidirectional):
```bash
# System Req → Software Req
workspace.py trace link \
  --from SYSTEM-REQ-010 \
  --to REQ-XXX-001 \
  --type requirements

# Software Req → Design
workspace.py trace link \
  --from REQ-XXX-001 \
  --to DES-XXX-010 \
  --type design

# Design → Implementation
workspace.py trace link \
  --from DES-XXX-010 \
  --to src/module.c:50 \
  --type implementation

# Implementation → Unit Test
workspace.py trace link \
  --from src/module.c:50 \
  --to TEST-XXX-050 \
  --type unit_test

# Unit Test → Integration Test
workspace.py trace link \
  --from TEST-XXX-050 \
  --to TEST-INT-100 \
  --type integration_test

# Integration Test → System Test
workspace.py trace link \
  --from TEST-INT-100 \
  --to TEST-SYS-200 \
  --type system_test

# System Test → Validation Result
workspace.py trace link \
  --from TEST-SYS-200 \
  --to VALIDATION-RESULT-001 \
  --type validation
```

**Validate Traceability** (gap detection):
```bash
workspace.py trace validate --sil <0-4>

# Output includes:
# - Forward coverage % (requirements → implementation)
# - Backward coverage % (implementation → requirements)
# - Gap detection (6 types)
# - SIL compliance (PASS/FAIL)
```

**Generate RTM Reports**:
```bash
# Markdown report
workspace.py trace report \
  --format markdown \
  --output docs/traceability/rtm.md

# PDF report
workspace.py trace report \
  --format pdf \
  --output docs/traceability/rtm.pdf

# HTML report (interactive)
workspace.py trace report \
  --format html \
  --output docs/traceability/rtm.html
```

**RTM Queries**:
```bash
# Find all design elements for a requirement
workspace.py trace query \
  --from REQ-XXX-001 \
  --target-type design

# Find all tests for a requirement
workspace.py trace query \
  --from REQ-XXX-001 \
  --target-type test

# Find upstream requirements for code
workspace.py trace query \
  --from src/module.c:50 \
  --direction backward \
  --target-type requirement
```

**RTM Audit**:
```bash
workspace.py trace audit \
  --sil <0-4> \
  --auditor VER \
  --output docs/verification/rtm_audit_report.md
```

---

### Workflow Management Commands (`workspace.py wf`)

**Document Submission**:
```bash
workspace.py wf submit-document \
  --document-id SRS-v1.0 \
  --title "Software Requirements Specification v1.0" \
  --phase requirements \
  --author "REQ Agent" \
  --status "Submitted for Review"
```

**Document Approval Workflow**:
```bash
# List pending approvals
workspace.py wf list-pending

# Approve document (QUA review)
workspace.py wf approve-document \
  --document-id SRS-v1.0 \
  --approver "QUA Agent" \
  --comment "Template compliance verified"

# Approve document (VER review)
workspace.py wf approve-document \
  --document-id SRS-v1.0 \
  --approver "VER Agent" \
  --comment "Requirements traceability complete"

# Check approval status
workspace.py wf status --document-id SRS-v1.0

# Output:
# Document: SRS-v1.0
# Status: APPROVED (2/2 approvals)
# Approvals:
#   - QUA Agent (2026-03-10): Template compliance verified
#   - VER Agent (2026-03-11): Requirements traceability complete
```

**Gate Check Workflow**:
```bash
# Submit gate check request
workspace.py wf request-gate-check \
  --phase requirements \
  --requestor "REQ Agent"

# COD performs gate check
@cod gate-check requirements

# Record gate decision
workspace.py wf record-gate-decision \
  --phase requirements \
  --decision PASS \
  --decision-date 2026-03-12 \
  --notes "All criteria met, proceed to design"
```

**Iteration Workflow**:
```bash
# Submit change request
workspace.py wf submit-cr \
  --cr-id CR-PROJ-0001 \
  --category requirements_change \
  --requestor "VAL Agent"

# Track CR approval
workspace.py wf approve-cr \
  --cr-id CR-PROJ-0001 \
  --approver "CCB"

# Track iteration progress
workspace.py wf update-iteration \
  --iteration-id ITER-001 \
  --artifact-updated REQ-PROJ-025 \
  --action added

# Close iteration
workspace.py wf close-iteration \
  --iteration-id ITER-001 \
  --status COMPLETE
```

**Baseline Management**:
```bash
# Create baseline
workspace.py wf create-baseline \
  --baseline-id v1.0.0 \
  --phase requirements \
  --date 2026-03-12

# Query baseline
workspace.py wf query-baseline \
  --baseline-id v1.0.0

# Output:
# Baseline: v1.0.0
# Phase: Requirements
# Date: 2026-03-12
# Deliverables:
#   - SRS-v1.0 (APPROVED)
#   - Traceability Matrix v1.0 (100% coverage)
```

---

## Python Automation Scripts

All workflows include Python automation scripts for efficiency and consistency:

### Phase Gate Management
- **`tools/gate_checker.py`** (~400 lines) - Automated phase gate validation with SIL-specific criteria

### V-Model Orchestration
- **`tools/phase_transition_checker.py`** (~200 lines) - Validates phase transition readiness
- **`tools/agent_status_tracker.py`** (~150 lines) - Tracks agent activity and deliverable status
- **`tools/lifecycle_state_manager.py`** (~150 lines) - Manages LIFECYCLE_STATE.md updates

### Traceability and RTM
- **`tools/rtm_gap_detector.py`** (~250 lines) - Detects 6 types of traceability gaps with detailed reporting

### Iteration and Change Management
- **`tools/cr_impact_analyzer.py`** (~250 lines) - Analyzes CR impact on downstream artifacts and estimates effort
- **`tools/regression_test_selector.py`** (~200 lines) - Selects regression tests based on SIL level and changed artifacts

**Total Automation**: ~1,600 lines of Python scripts for lifecycle coordination

---

## EN 50128 Coverage

This skill provides complete coverage of EN 50128 lifecycle management requirements:

| EN 50128 Section | Description | Workflow Coverage |
|------------------|-------------|-------------------|
| **Section 5.3** | Software Lifecycle | V-Model Orchestration (all phases) |
| **Section 5.3.2.2** | Iterations | Iteration and Change Management |
| **Section 5.3.2.5** | Phase Planning | V-Model Orchestration (phase initialization) |
| **Section 5.3.2.7** | Traceability | RTM Management (bidirectional traceability) |
| **Section 6.2** | Verification | Phase Gate Management (VER approval) |
| **Section 6.4** | Change Control | Iteration and Change Management (CR process) |
| **Section 6.5** | Quality Assurance | Phase Gate Management (QUA approval) |
| **Section 6.6** | Configuration Management | V-Model Orchestration (baseline management) |
| **Annex C Table C.1** | Document Control | Phase Gate Management (deliverables per phase) |

**Table A.9: Software Quality Assurance Techniques (Traceability)**:

| # | Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Workflow |
|---|-----------|-------|---------|---------|----------|
| 10 | Traceability | R | HR | **M** | **RTM Management Workflow** |

**Key Requirements Covered**:
- **V-Model Structure** (Section 5.3): Highly recommended per §5.3, Figures 3–4; alternative models permissible per §5.3.2.14; implemented in V-Model Orchestration Workflow
- **Iterations** (Section 5.3.2.2): "The lifecycle model shall take into account the possibility of iterations in and between phases" - implemented in Iteration and Change Management Workflow
- **Phase Planning** (Section 5.3.2.5): "All activities to be performed during a phase shall be defined and planned prior to commencement" - implemented in V-Model Orchestration Workflow (phase initialization)
- **Traceability** (Section 5.3.2.7): "For each document, traceability shall be provided" - implemented in RTM Management Workflow (bidirectional traceability with 100% coverage SIL 3-4)
- **Document Control** (Annex C Table C.1): Phase-to-document mapping for all 8 phases - implemented in Phase Gate Management Workflow

---

## Statistics

**Total Content**:
- **Workflows**: 4 comprehensive workflows
- **Total Lines**: ~12,000 lines (Gate: 2,319, Orchestration: 1,507, RTM: 1,481, Iteration: 1,543)
- **Total Pages**: ~300 pages (assuming 40 lines/page)
- **Python Scripts**: 7 automation scripts (~1,600 lines total)
- **Tool Commands**: 60+ `workspace.py trace` and `workspace.py wf` examples
- **Complete Examples**: 30+ complete lifecycle scenarios (SIL 0, 2, 3, 4)

**Workflow Sizes**:
1. Phase Gate Management: 2,319 lines (~93 pages)
2. V-Model Orchestration: 1,507 lines (~60 pages)
3. Traceability and RTM: 1,481 lines (~59 pages)
4. Iteration and Change Management: 1,543 lines (~62 pages)

---

## References

- **EN 50128:2011 Section 5.3** - Software Lifecycle (V-Model highly recommended per §5.3, Figures 3–4; alternative models permissible per §5.3.2.14)
- **EN 50128:2011 Section 5.3.2.2** - Iterations ("shall take into account the possibility of iterations")
- **EN 50128:2011 Section 5.3.2.5** - Phase Planning ("activities shall be defined and planned prior to commencement")
- **EN 50128:2011 Section 5.3.2.7** - Traceability ("traceability shall be provided")
- **EN 50128:2011 Section 6.2** - Software Verification
- **EN 50128:2011 Section 6.4** - Problem Reporting and Change Control
- **EN 50128:2011 Section 6.5** - Software Quality Assurance
- **EN 50128:2011 Section 6.6** - Software Configuration Management
- **EN 50128:2011 Annex C Table C.1** - Software Document Control Summary
- **EN 50128:2011 Table A.9** - Software Quality Assurance Techniques (Traceability MANDATORY SIL 3-4)

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
8. **Comprehensive workflows** - 4 workflows (~300 pages) with complete automation
9. **Tool integration** - 60+ workspace.py commands for trace and workflow management
10. **Python automation** - 7 scripts (~1,600 lines) for efficiency

**Key Principle**: COD orchestrates the lifecycle to ensure EN 50128 V-Model compliance while enabling efficient development. Be strict where safety demands (SIL 3-4), but be helpful and guiding at all times.
