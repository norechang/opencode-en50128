---
name: en50128-lifecycle-phase-checklists
description: Per-phase gate checklists (Phase 1–9) with SIL-annotated criteria for all COD gate-check operations
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  role: lifecycle-coordinator
---

# Phase Gate Checklists

**Load trigger**: Load this skill at the start of any `@cod gate-check <phase>` or
`@cod start-phase <phase>` operation. Only the checklist section for the target phase
needs to be applied; the others are available for reference.

---

## Phase 1 Gate: Planning Complete

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

## Phase 2 Gate: Requirements Complete

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

## Phase 3 Gate: Architecture & Design Complete

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

## Phase 4 Gate: Component Design Complete

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

## Phase 5 Gate: Implementation & Testing Complete

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

## Phase 6 Gate: Integration Complete

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

## Phase 7 Gate: Validation Complete

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

## Phase 8 Gate: Assessment Complete (SIL 1-4)

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

## Phase 9 Gate: Deployment Complete

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
