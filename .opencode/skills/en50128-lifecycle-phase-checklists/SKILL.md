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

**Load trigger**: Load at the start of any `@cod gate-check <phase>` or `@cod start-phase <phase>`.
Apply only the section for the target phase; the others are reference.

**Deliverables for each phase**: see `DELIVERABLES.md` (Annex C Table C.1) and
`activities/phase-N-*.yaml §gate_check §criteria`. These checklists cover quality,
technique, and SIL-specific criteria not captured in the deliverables matrix.

---

## Phase 1 — Planning

**Quality criteria**:
- [ ] All planning documents internally consistent and cross-referencing
- [ ] Quality gates defined for all subsequent phases (SQAP covers full lifecycle)
- [ ] V&V strategy established: VER and VAL roles identified with independence level per SIL
- [ ] Configuration management operational (repo initialized, naming convention agreed)

**Team organization**:
- [ ] All roles assigned with named individuals or team designations
- [ ] SIL-required independence satisfied (SIL 3–4: VAL independent of PM; ASR independent of supplier)
- [ ] Reporting structure documented in SQAP (source: `ORGANIZATION.md` for SIL-tiered charts)
- [ ] Tool qualification plan in place if tool failure could affect SIL classification

**SIL-specific**:
- SIL 0–1: Basic SQAP and SCMP sufficient; SVP/SVaP optional
- SIL 2: MISRA C compliance plan required; static analysis tooling nominated
- SIL 3–4: SVP authored by VER (not PM); SVaP authored by VMGR (not PM); formal tool qualification plan required

---

## Phase 2 — Requirements

**Requirements quality**:
- [ ] All requirements unambiguous (no undefined terms; single clear interpretation)
- [ ] All requirements testable (acceptance criterion defined for each)
- [ ] Unique IDs assigned to all requirements
- [ ] SHALL/SHOULD/MAY keywords used correctly (RFC 2119 or project standard)
- [ ] SIL levels assigned to all requirements
- [ ] C language constraints reflected (data types, timing, memory)

**Traceability**:
- [ ] RTM complete: system requirements → software requirements (bidirectional, rule T2)
- [ ] No orphan software requirements (or justified)

**Safety**:
- [ ] Hazard analysis initiated or updated (FMEA/FTA as appropriate for SIL)
- [ ] Safety requirements identified and linked to hazards
- [ ] Hazard log established

**EN 50128 Table A.2 techniques**:
- [ ] Structured Methodology (R SIL 0–1; HR SIL 2–4)
- [ ] Modelling (R all; HR SIL 3–4)
- [ ] Formal Methods (R SIL 1–2; HR SIL 3–4)

**SIL-specific**:
- SIL 0–1: Informal methods acceptable; traceability recommended
- SIL 2: Structured methodology and traceability highly recommended
- SIL 3–4: Traceability MANDATORY; formal/semi-formal methods highly recommended

---

## Phase 3 — Architecture & Design

**Architecture quality**:
- [ ] Modular design (MANDATORY SIL 2+)
- [ ] Module interfaces fully specified and unambiguous
- [ ] No dynamic memory allocation (MANDATORY SIL 2+)
- [ ] No recursion (HR SIL 3–4)
- [ ] Bounded execution time for all modules

**Design quality (C-specific)**:
- [ ] Cyclomatic complexity limits defined: SIL 3–4 ≤ 10; SIL 2 ≤ 15; SIL 0–1 ≤ 20
- [ ] Fixed-width integer types specified (uint8_t, uint32_t, etc.)
- [ ] Error handling strategy defined for all identified failure modes
- [ ] Defensive programming patterns specified

**Traceability**:
- [ ] RTM updated: requirements → architecture → design modules (bidirectional, rules T3–T4)
- [ ] No orphan design elements (or justified)

**Safety design**:
- [ ] Safety-critical functions identified and isolated
- [ ] Fault detection / diagnosis mechanisms defined (R SIL 1–2; HR SIL 3–4)
- [ ] FMEA/FTA updated to reflect architecture decisions

**EN 50128 Table A.3 techniques**:
- [ ] Structured Methodology (HR SIL 1–2; M SIL 3–4)
- [ ] Modular Approach (HR SIL 0–1; M SIL 2+)
- [ ] Design and Coding Standards defined (HR SIL 0–2; M SIL 3–4)
- [ ] Defensive Programming (HR SIL 1–4)

**SIL-specific**:
- SIL 0–1: Basic modular design; informal methods
- SIL 2: Static allocation MANDATORY; modular approach MANDATORY
- SIL 3–4: All above + structured methodology MANDATORY; complexity limits enforced; no recursion HR

---

## Phase 4 — Component Design

**Design quality**:
- [ ] Component design traceable to SDS (rule T5)
- [ ] Test strategies defined per component (test cases traceable to component requirements)
- [ ] Complexity limits respected per SIL

**SIL-specific**:
- SIL 0–1: Component designs recommended; VER review optional
- SIL 2: Component designs highly recommended; VER review highly recommended
- SIL 3–4: Component designs, test specifications, and VER report MANDATORY

---

## Phase 5 — Implementation & Testing

**Code quality (C-specific)**:
- [ ] MISRA C:2012 compliance (MANDATORY SIL 2+): mandatory rules satisfied; deviations justified in deviation log
- [ ] No dynamic memory allocation; no recursion (HR SIL 3–4)
- [ ] Fixed-width integer types used throughout
- [ ] All pointer dereferences validated; all return values checked
- [ ] All external inputs validated (defensive programming)
- [ ] Cyclomatic complexity measured and within SIL limit for every function

**Static analysis** (MANDATORY SIL 3–4; HR SIL 2):
- [ ] Static analysis tool run (e.g., PC-lint Plus, Cppcheck, Clang Static Analyzer)
- [ ] All violations resolved or entered in deviation log with justification
- [ ] No dead code; no unreachable code

**Unit testing**:
- [ ] All units tested; all unit tests passing
- [ ] Coverage measured and meets SIL threshold:
  - SIL 0–1: Statement HR; Branch HR
  - SIL 2: Statement HR; Branch **M**
  - SIL 3–4: Statement **M**; Branch **M**; Condition **M** (or data flow HR)
- [ ] Boundary value tests included; error handling paths tested
- [ ] Fault injection testing (HR SIL 3–4)

**Code review** (MANDATORY all SIL levels):
- [ ] QUA code review conducted; MISRA C and defensive programming verified
- [ ] All review findings resolved

**Traceability**:
- [ ] RTM updated: design → source files → unit tests (bidirectional, rules T6–T8)
- [ ] No untested source files (or justified)

**EN 50128 Table A.4 techniques**:
- [ ] Structured Programming (HR SIL 1–2; M SIL 3–4)
- [ ] Design and Coding Standards (HR SIL 0–2; M SIL 3–4)
- [ ] Analysable Programs (HR SIL 0–2; M SIL 3–4)

---

## Phase 6 — Integration

**Integration execution**:
- [ ] Integration strategy (bottom-up / top-down / incremental) executed as planned
- [ ] All components integrated without conflict; build system produces executable

**Integration testing**:
- [ ] All integration tests executed and passing
- [ ] Interface testing complete (HR all SIL levels): data flow across interfaces; error handling at interfaces; boundary conditions
- [ ] Performance testing: timing requirements verified; WCET measured (HR SIL 3–4)
- [ ] Regression testing performed after each integration step

**Traceability**:
- [ ] RTM updated: components → integration tests (rules T9–T10); interface coverage complete

**EN 50128 Table A.6 techniques**:
- [ ] Functional/Black-box Testing (HR all SIL levels)
- [ ] Performance Testing (R SIL 1–2; HR SIL 3–4)

**SIL-specific**:
- SIL 0–1: Basic integration testing
- SIL 2: Interface testing HR; performance testing R
- SIL 3–4: Interface testing HR; performance testing HR; WCET analysis HR

---

## Phase 7 — Validation

**Validation testing**:
- [ ] Overall Software Test Specification executed in full
- [ ] All system tests passing; testing performed in target environment or representative simulator
- [ ] Operational scenarios tested; performance testing complete (HR SIL 1–2; M SIL 3–4)
- [ ] Functional/black-box testing complete (HR SIL 0–2; M SIL 3–4)

**Requirements validation**:
- [ ] RTM complete end-to-end: requirements → design → code → tests → results (rule T11)
- [ ] 100% requirements coverage (every requirement has at least one passing test)

**Independence (SIL 3–4)**:
- [ ] Validation performed by independent Validator (VAL)
- [ ] VAL does NOT report to PM (§5.1.2.10f)
- [ ] VAL independence documented

**Customer acceptance**:
- [ ] Acceptance criteria met; customer sign-off obtained; deviations documented

**EN 50128 Table A.7 techniques**:
- [ ] Performance Testing (HR SIL 1–2; M SIL 3–4)
- [ ] Functional/Black-box Testing (HR SIL 0–2; M SIL 3–4)

**SIL-specific**:
- SIL 0–1: Basic system testing; customer acceptance
- SIL 2: Functional and performance testing HR
- SIL 3–4: Independent validation MANDATORY; performance and functional testing MANDATORY

---

## Phase 8 — Assessment

**Independence** (MANDATORY SIL 1–4 per §6.4.1.1; exempt SIL 0 per §6.4.1.2):
- [ ] Assessor independent from supplier (or Safety Authority discretion)
- [ ] Assessor independence documented; no reporting to COD or PM

**Assessment activities**:
- [ ] Process compliance audit performed (all EN 50128 lifecycle requirements)
- [ ] All lifecycle documents reviewed; all evidence reviewed
- [ ] Safety case evaluated; traceability verified end-to-end (rule T15)

**Findings**:
- [ ] All findings documented in Assessment Report; all addressed or accepted with justification
- [ ] No open critical findings; residual risks accepted and documented

**Safety Authority**:
- [ ] Safety Authority notified and approval obtained if required by applicable regulation

---

## Phase 9 — Deployment

**Release package**:
- [ ] Release package complete (executable, libraries, configuration, documentation)
- [ ] Package verified against CM baseline; signed/authenticated (SIL 3–4)

**Deployment**:
- [ ] Deployment procedure followed; deployment records complete (what/when/where/who)
- [ ] Post-deployment verification performed (smoke tests, operational checks)

**Maintenance**:
- [ ] Maintenance plan established; change control process active
- [ ] Defect tracking system operational; maintenance team assigned and trained

**Configuration management**:
- [ ] Final release baselined and tagged in repository
- [ ] All artifacts archived; traceability complete from requirements to deployed code (rule T15)
