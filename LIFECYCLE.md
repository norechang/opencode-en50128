# EN 50128 Software Development Lifecycle

This document defines the complete software development lifecycle for EN 50128:2011 compliant railway safety software development. All projects in this workspace SHALL follow this lifecycle.

## Document Information

| Property | Value |
|----------|-------|
| **Standard** | EN 50128:2011 Railway Software Standard |
| **Section** | Section 6: Software Lifecycle Issues |
| **Lifecycle Model** | V-Model (Highly Recommended / Industry Standard for SIL 2-4 per §5.3, Figures 3–4) |
| **Language** | C (MISRA C:2012 for SIL 2+) |
| **Version** | 1.3 |

---

## 1. Lifecycle Overview

### 1.1 EN 50128 V-Model

The V-Model is highly recommended for SIL 2-4 and is the industry-standard lifecycle model per EN 50128:2011 §5.3 (Figures 3 and 4). Alternative lifecycle models are permissible per §5.3.2.14 provided equivalent safety assurance is demonstrated. The V-Model shows the relationship between development phases (left side) and verification/validation phases (right side).

```
┌─────────────────────────────────────────────────────────────────┐
│                    EN 50128 V-Model Lifecycle                   │
│              (Orchestrated by Lifecycle Coordinator)            │
└─────────────────────────────────────────────────────────────────┘

    System Requirements ────────────────────► System Validation
           │                                        ▲
           │ ┌────────────────────────────────────┐ │
           ▼ │  COD Phase Gates (SIL-dependent)   │ │
    Software Requirements ──────────────► Software Validation
    (Software Requirements Specification - Section 7.2)       │          (Section 7.7)
           │                  │                     ▲
           │                  │                     │
           ▼                  │                     │
    Software Architecture ───┼──────────► Integration Testing
    (Software Architecture Specification - Section 7.3)      │          (Section 7.6)
           │                 │                      ▲
           │                 │                      │
           ▼                 │                      │
     Component Design ───────┼──────────► Component Testing
     (Software Component Design - Section 7.4)         │          (Section 7.5)
            │                 │                      ▲
            │                 │                      │
            ▼                 │                      │
     Component Implementation ┴──────────► Unit Testing
     (Code - Section 7.5 "Component implementation and testing")
           │                                        │
           └────────────────────────────────────────┘

    ◄────────── Lifecycle Coordinator (COD) - Overall Orchestration ──────►
    ◄────────── Verification (Section 6.2) Throughout ──────────►
    ◄────────── Quality Assurance (Section 6.5) Throughout ──────►
    ◄────────── Configuration Management (Section 6.6) Throughout ►
    ◄────────── Safety Management Throughout ────────────────────►
```

### 1.2 Lifecycle Phases

The EN 50128 lifecycle consists of the following phases (orchestrated by Lifecycle Coordinator):

0. **Initialization** (Platform Extension — COD-specific)
1. **Software Planning & Management** (Sections 5, 6.5, 6.6)
2. **Software Requirements** (Section 7.2)
3. **Software Architecture & Design** (Section 7.3)
4. **Software Component Design** (Section 7.4)
5. **Software Implementation & Testing** (Section 7.5)
6. **Software Integration** (Section 7.6)
7. **Software Validation** (Section 7.7)
8. **Software Assessment** (Section 6.4) — mandatory for SIL 1–4 per §6.4.1.1 and §5.1.2.4; SIL 0 exempt per §6.4.1.2
9. **Software Deployment** (Section 9.1)
10. **Software Maintenance** (Section 9.2)

**Continuous cross-cutting activities** (not discrete phases): Software Verification (Section 6.2), Quality Assurance (Section 6.5), Configuration Management (Section 6.6), Safety Management.

**Total**: 11 phases (0–10); 46 Annex C deliverables tracked across phases (see Section 25)

**Lifecycle Coordinator (COD)**: The COD agent (`@cod`) orchestrates the complete lifecycle with SIL-dependent phase gate enforcement. See COD sections at the end of each phase for gate checkpoint details.

---

## 2. Phase 0: Initialization (COD-Specific)

### 2.1 Objectives
- Initialize project workspace and lifecycle tracking
- Establish SIL level and project identity
- Generate system-level input documents required for Phase 2 (Requirements)

### 2.2 Key Activities
1. Run `@cod plan --sil <level> --project <name>` to create `LIFECYCLE_STATE.md`
2. Run `@cod generate-system` to generate the four mandatory system-level documents:
   - System Requirements Specification
   - System Architecture Description
   - System Safety Plan
   - System Safety Requirements Specification
3. Review generated documents; refine if needed before Phase 2

### 2.3 Commands

| Command | Purpose |
|---------|---------|
| `@cod plan --sil <level> --project <name>` | Initialize LIFECYCLE_STATE.md, define SIL level |
| `@cod generate-system` | Generate 4 system docs from TYPICAL-SYSTEMS.md catalogue |
| `@cod generate-system --system <N>` | Generate non-interactively using system N from catalogue |

**System Documents Catalogue**: `assets/sample_system/TYPICAL-SYSTEMS.md`
- System 1: Train Door Control System (SIL 3)
- System 2: Level Crossing Protection System (SIL 4)
- System 3: ATP On-Board Unit (SIL 4)
- System 4: Platform Screen Door Control System (SIL 2)
- System 5: LRT Interlocking System (SIL 4)

### 2.4 Output
- `LIFECYCLE_STATE.md` — project state tracker (created by `@cod plan`)
- `docs/system/System-Requirements-Specification.md`
- `docs/system/System-Architecture-Description.md`
- `docs/system/System-Safety-Plan.md`
- `docs/system/System-Safety-Requirements-Specification.md`

### 2.5 EN 50128 References
- Section 7.2.2: System inputs required before software requirements (PRIMARY)
- Section 5.3: Lifecycle planning and documentation

---

## 3. Phase 1: Software Planning (Sections 5, 6.5, 6.6)

### 3.1 Objectives
- Define project organization and responsibilities
- Establish quality assurance plan
- Define verification and validation strategies
- Establish configuration management
- Determine SIL levels

### 3.2 Key Activities
1. Establish Software Quality Assurance Plan (SQAP)
2. Establish Software Configuration Management Plan (SCMP)
3. Establish Software Verification Plan (SVP)
4. Establish Software Validation Plan (SVaP)
5. Define project standards and guidelines

### 3.3 Agents Involved
- Project Manager (PM) - overall project coordination, CCB leadership
- Software Manager - software development responsibility (per EN 50128 Section 5.3.1)
- Configuration Manager (CM) - version control, change management, baselines
- Quality Assurance (QUA) - SQAP development and enforcement
- Safety Engineer (SAF) - safety planning and SIL determination

**Note**: EN 50128 defines both "Project Manager" (Table B.9) and "Software Manager" (Section 5.3.1). Project Manager has overall project coordination responsibility, while Software Manager focuses on software development activities.

### 3.4 Deliverables

See [`DELIVERABLES.md`](DELIVERABLES.md) — Phase 1: Planning (Annex C items 1–5).

### 3.5 EN 50128 References
- Section 5: Organizational requirements
- Section 6.5: Software quality assurance
- Section 6.6: Modification and change control
- Table A.1: Software lifecycle phases and related documents

### 3.6 Entry Criteria
- Phase 0 complete: `LIFECYCLE_STATE.md` initialized (via `@cod plan`)
- System-level documents available (via `@cod generate-system` or manually prepared)
- SIL level determined and documented
- Project authorization obtained

### 3.7 Exit Criteria
- All planning documents approved
- Quality gates defined
- Verification/validation strategies established
- Configuration management in place

### 3.8 Phase Gate (COD Checkpoint)

**Command**: `@cod gate-check planning`

Full gate checklist and COD enforcement behavior: see `.opencode/agents/cod.md` → Gate 1: Planning.

---

## 4. Phase 2: Software Requirements (Section 7.2)

### 4.1 Objectives
- Define complete, unambiguous software requirements
- Establish requirements traceability
- Assign SIL levels to requirements
- Identify safety requirements

### 4.2 Key Activities
1. Elicit requirements from stakeholders and system specification
2. Write Software Requirements Specification
3. Establish requirements traceability matrix
4. Perform hazard analysis
5. Define safety requirements
6. **QA document template compliance check (MANDATORY before VER for SIL 3-4)**
7. Review and approve requirements

### 4.3 Agents Involved
- Requirements Engineer (REQ) - PRIMARY
- Safety Engineer (SAF)
- Quality Assurance (QUA) - **Document template compliance check BEFORE VER**

### 4.4 Skills Required
- `en50128-requirements` - Requirements engineering patterns
- `en50128-safety` - Hazard analysis and safety requirements
- `en50128-documentation` - Software Requirements Specification templates

### 4.5 Deliverables

See [`DELIVERABLES.md`](DELIVERABLES.md) — Phase 2: Requirements (Annex C items 6–8).

### 4.6 Requirements Quality Checklist
- [ ] All requirements unambiguous
- [ ] All requirements testable
- [ ] All requirements traceable
- [ ] SHALL/SHOULD/MAY keywords used correctly
- [ ] SIL levels assigned
- [ ] C language constraints considered
- [ ] Safety requirements identified

### 4.7 EN 50128 Techniques/Measures (Table A.2)

See `.opencode/agents/req.md` for full Table A.2 technique/measure details.

### 4.8 EN 50128 References
- Section 7.2: Software requirements specification
- Table A.2: Software requirements specification techniques
- Section 7.2.4: Detailed requirements

### 4.9 Entry Criteria
- System requirements available
- SQAP approved
- Verification plan approved

### 4.10 Exit Criteria
- Software Requirements Specification complete and approved
- All requirements traceable to system requirements
- Requirements review passed
- Hazard analysis complete

### 4.11 Phase Gate (COD Checkpoint)

**Command**: `@cod gate-check requirements`

Full gate checklist and COD enforcement behavior: see `.opencode/agents/cod.md` → Gate 2: Requirements.

---

## 5. Phase 3: Software Architecture & Design (Section 7.3)

### 5.1 Objectives
- Define software architecture
- Design software modules and interfaces
- Ensure design meets requirements
- Apply defensive programming principles

### 5.2 Key Activities
1. Create Software Architecture Specification
2. Create Software Design Specification
3. Define module interfaces
4. Design data structures (static allocation for SIL 2+)
5. Define error handling strategy
6. Perform design reviews
7. Establish complexity limits
8. **QA document template compliance check (MANDATORY before VER for SIL 3-4)**

### 5.3 Agents Involved
- Designer (DES) - PRIMARY
- Safety Engineer (SAF)
- Quality Assurance (QUA) - **Document template compliance check BEFORE VER**
- Requirements Engineer (REQ) - for traceability

### 5.4 Skills Required
- `en50128-design` - Architecture and design patterns
- `en50128-safety` - Safety analysis (FMEA/FTA)
- `en50128-implementation` - MISRA C design patterns

### 5.5 Deliverables

See [`DELIVERABLES.md`](DELIVERABLES.md) — Phase 3: Architecture & Design (Annex C items 9–14).

### 5.6 Design Constraints by SIL

See `.opencode/agents/des.md` for full SIL-specific design constraints and design review checklist.

### 5.7 EN 50128 Techniques/Measures (Table A.3)

See `.opencode/agents/des.md` for full Table A.3 technique/measure details and approved SIL combinations.

### 5.8 EN 50128 References
- Section 7.3: Software architecture and design  
- Table A.3: Software architecture techniques
- Annex D: Technique descriptions

### 5.9 Entry Criteria
- Software Requirements Specification approved
- Design standards defined
- FMEA/FTA planned (SIL 3-4)

### 5.10 Exit Criteria
- Software Architecture Specification and Software Design Specification complete and approved
- Design traceable to requirements
- Design review passed
- Complexity limits established

### 5.11 Phase Gate (COD Checkpoint)

**Command**: `@cod gate-check design`

Full gate checklist and COD enforcement behavior: see `.opencode/agents/cod.md` → Gate 3: Design.

---

## 6. Phase 4: Software Component Design (Section 7.4)

### 6.1 Objectives
- Decompose software design into component-level specifications
- Define detailed component interfaces and data structures
- Specify component test strategies
- Verify component design against architecture design

### 6.2 Key Activities
1. Create Software Component Design Specification (decompose SDS to component level)
2. Create Software Component Test Specification
3. Perform component design reviews
4. Verify component design against Software Design Specification (VER)

### 6.3 Agents Involved
- Designer (DES) - PRIMARY (component design decomposition)
- Tester (TST) — component test specification
- Verifier (VER) — component design verification
- Quality Assurance (QUA) — document template compliance check

### 6.4 Deliverables

See [`DELIVERABLES.md`](DELIVERABLES.md) — Phase 4: Component Design (Annex C items 15–17).

### 6.5 EN 50128 References
- Section 7.4: Component design
- Table A.4: Component design techniques

### 6.6 Entry Criteria
- Software Design Specification approved (Phase 3 gate passed)
- Component design standards defined

### 6.7 Exit Criteria
- All component design specifications complete and reviewed
- Component test specifications complete
- Component design verification report approved
- Design traceable to Software Design Specification

### 6.8 Phase Gate (COD Checkpoint)

**Command**: `@cod gate-check component-design`

Full gate checklist and COD enforcement behavior: see `.opencode/agents/cod.md` → Gate 4: Component Design.

---

## 7. Phase 5: Software Implementation & Testing (Section 7.5)

### 7.1 Objectives
- Implement software modules in C
- Ensure MISRA C:2012 compliance
- Execute component (unit) tests
- Achieve required coverage

### 7.2 Key Activities
1. Implement C code following MISRA C:2012
2. Execute component tests per Software Component Test Specification
3. Measure code coverage
4. Perform static analysis
5. Conduct code reviews
6. Document code

### 7.3 Agents Involved
- Implementer (IMP) - PRIMARY
- Tester (TST)
- Verifier (VER)
- Quality Assurance (QUA)

### 7.4 Skills Required
- `en50128-implementation` - MISRA C coding patterns
- `en50128-testing` - Unit testing with Unity
- `en50128-verification` - Static analysis
- `en50128-design` - Design patterns reference

### 7.5 Deliverables

See [`DELIVERABLES.md`](DELIVERABLES.md) — Phase 5: Implementation & Testing (Annex C items 18–20).

**Note**: Software Component Test Report (Annex C item 20) is a **Phase 5 deliverable** per §7.5.3 and Annex C Table C.1 — it is produced here and consumed as input to Phase 6.

### 7.6 MISRA C:2012 Compliance and Coverage Requirements

See `.opencode/agents/imp.md` for MISRA C:2012 rules, coverage requirements by SIL, and implementation checklist.

### 7.7 EN 50128 Techniques/Measures (Table A.4)

See `.opencode/agents/imp.md` for full Table A.4 technique/measure details and approved SIL combinations.

### 7.8 EN 50128 References
- Section 7.5: Component implementation and testing
- Table A.4: Design and implementation techniques
- Table A.12: Coding standards (MISRA C)
- Table A.15: Programming languages

### 7.9 Entry Criteria
- Software Component Design Specification approved (Phase 4 gate passed)
- Coding standards defined
- Unit test framework ready
- Static analysis tools configured

### 7.10 Exit Criteria
- All code implemented and reviewed
- Component tests pass
- Coverage requirements met
- Static analysis clean
- Code traceable to component design

### 7.11 Phase Gate (COD Checkpoint)

**Command**: `@cod gate-check implementation-testing`

Full gate checklist and COD enforcement behavior: see `.opencode/agents/cod.md` → Gate 5: Implementation & Testing.

---

## 8. Phase 6: Software Integration (Section 7.6)

### 8.1 Objectives
- Integrate software modules progressively
- Perform integration testing
- Verify module interfaces
- Test software/hardware integration
- Validate integrated system behavior

### 8.2 Key Activities
1. Plan integration strategy (bottom-up, top-down, or sandwich)
2. Integrate modules incrementally
3. Execute integration tests
4. Test module interfaces (functional and non-functional)
5. Verify data flow between components
6. Perform performance testing (highly recommended SIL 3-4)
7. Resolve integration issues

### 8.3 Agents Involved
- Integrator (INT) - PRIMARY
- Tester (TST)
- Implementer (IMP)
- Designer (DES)
- Verifier (VER)
- Configuration Manager (CM) - for integration baselines

### 8.4 Skills Required
- `en50128-integration` - Integration strategies and testing
- `en50128-testing` - Integration test techniques
- `en50128-verification` - Integration verification

### 8.5 Deliverables

See [`DELIVERABLES.md`](DELIVERABLES.md) — Phase 6: Integration (Annex C items 21–22).

**Note**: Software Component Test Report (Annex C item 20) is a **Phase 5 deliverable** per §7.5.3 and Annex C Table C.1 — it is produced in Phase 5 (Component Implementation and Testing) and consumed as input to Phase 6.

### 8.6 EN 50128 Techniques/Measures (Table A.6)

See `.opencode/agents/int.md` for full Table A.6 technique/measure details.

### 8.7 EN 50128 References
- Section 7.6: Software integration
- Table A.6: Integration techniques and measures
- Table A.14: Functional/black-box test techniques
- Table A.18: Performance testing techniques

### 8.8 Entry Criteria
- All software modules implemented and unit-tested
- Implementation phase gate passed
- Integration test specifications available
- Integration environment ready (target hardware available for SW/HW integration)

### 8.9 Exit Criteria
- All integration tests pass (100% pass rate)
- All module interfaces verified
- Software/hardware integration verified
- Performance requirements met (SIL 3-4)
- Integration defects resolved
- Integration traceability complete

### 8.9 Integration Checklist

See `.opencode/agents/int.md` for the full integration checklist.

### 8.10 Phase Gate (COD Checkpoint)

**Command**: `@cod gate-check integration`

Full gate checklist and COD enforcement behavior: see `.opencode/agents/cod.md` → Gate 6: Integration.

---

## 9. Phase 7: Software Validation (Section 7.7)

### 9.1 Objectives
- Validate software against system requirements
- Demonstrate software meets intended purpose
- Obtain customer/user acceptance
- Confirm safety requirements satisfied

### 9.2 Key Activities
1. Execute overall software test plan (SVaP)
2. Perform functional and black-box testing
3. Perform performance testing (mandatory SIL 3-4)
4. Validate operational scenarios in target environment
5. Conduct user acceptance testing
6. Validate Tools Validation Report (if applicable)
7. Prepare Release Note
8. Obtain customer acceptance sign-off

### 9.3 Agents Involved
- Validator (VAL) - PRIMARY (must be independent for SIL 3-4)
- Tester (TST)
- Quality Assurance (QUA)
- Safety Engineer (SAF) - for safety validation activities
- Configuration Manager (CM) - for validation baseline

### 9.4 Skills Required
- `en50128-validation` - System testing and acceptance validation
- `en50128-testing` - Test execution and coverage analysis
- `en50128-quality` - QA validation review

### 9.5 Deliverables

See [`DELIVERABLES.md`](DELIVERABLES.md) — Phase 7: Validation (Annex C items 23–26, 27).

**Additional normative outputs (no Annex C number)**:
- **Software Validation Verification Report** (`docs/reports/Software-Validation-Verification-Report.md`) — written by VER — required by §6.3.3

### 9.6 Validation Testing Checklist

See `.opencode/agents/val.md` for full validation testing checklist.

### 9.7 EN 50128 Techniques/Measures (Table A.7)

See `.opencode/agents/val.md` for full Table A.7 technique/measure details and independence requirements.

### 9.8 EN 50128 References
- Section 7.7: Overall software testing (validation)
- Table A.7: Overall software testing techniques
- Table A.14: Functional and black-box testing
- Table A.18: Performance testing

### 9.9 Entry Criteria
- Integration complete
- Validation plan (SVaP) approved and **at an approved baseline** per §5.3.2.4 — input document produced in Phase 1
- Target environment available
- Independent validator assigned (SIL 3-4)

### 9.10 Exit Criteria
- All validation tests pass
- Customer acceptance obtained
- Safety requirements validated
- Performance requirements met (SIL 3-4)
- Validation report approved

### 9.11 Phase Gate (COD Checkpoint)

**Command**: `@cod gate-check validation`

Full gate checklist and COD enforcement behavior: see `.opencode/agents/cod.md` → Gate 7: Validation.

---

## 10. Software Verification (Section 6.2 — Continuous)

**Note**: Software Verification is a **continuous cross-cutting activity** performed throughout all lifecycle phases, not a discrete sequential phase. It is documented here as a section for reference. Verification activities are triggered within each phase and are orchestrated by the Lifecycle Coordinator (COD).

### 10.1 Objectives
- Verify correctness throughout lifecycle
- Ensure compliance with standards
- Collect objective evidence
- Maintain quality

### 10.2 Key Activities (Throughout Lifecycle)
1. Perform static analysis
2. Conduct design reviews
3. Conduct code reviews
4. Verify traceability
5. Check complexity
6. Verify coverage
7. Collect evidence

### 10.3 Agents Involved
- Verifier (VER) - PRIMARY (must be independent for SIL 3-4)
- Quality Assurance (QUA)
- All other agents (peer verification)

### 10.4 Skills Required
- `en50128-verification` - Static analysis, verification methods
- `en50128-quality` - QA processes

### 10.5 Deliverables

See [`DELIVERABLES.md`](DELIVERABLES.md) for all Annex C documents — verification deliverables are produced within each phase as the VER role completes its phase-specific activities.

### 10.6 Verification Checklist

See `.opencode/agents/ver.md` for the full verification checklist.

### 10.7 EN 50128 Techniques/Measures (Table A.5)

See `.opencode/agents/ver.md` for full Table A.5 technique/measure details, coverage requirements (Table A.21), and approved SIL combinations.

### 10.8 EN 50128 References
- Section 6.2: Verification and testing
- Section 7.3: Software architecture verification
- Table A.5: Verification and testing techniques
- Table A.13: Dynamic analysis and testing
- Table A.19: Static analysis techniques
- Table A.21: Test coverage for code

### 10.9 Independence Requirements

| SIL Level | Verification Independence |
|-----------|---------------------------|
| SIL 0-1 | Not required |
| SIL 2 | Highly recommended |
| SIL 3-4 | Mandatory |

---

## 11. Phase 8: Software Assessment (Section 6.4)

### 11.1 Objectives
- Assess overall software quality
- Verify compliance with EN 50128
- Determine readiness for deployment
- Obtain safety approval

### 11.2 Key Activities
1. Review all lifecycle artifacts
2. Assess compliance with EN 50128
3. Review verification evidence
4. Review validation results
5. Assess safety case
6. Prepare assessment report

### 11.3 Agents Involved
- **Assessor** (independent, mandatory for SIL 1–4 per §6.4.1.1 and §5.1.2.4; SIL 0 exempt per §6.4.1.2; per EN 50128 Section 5.3.8, Table B.8)
- **Project Manager** (overall project responsibility)
- **Software Manager** (software development responsibility)
- Quality Assurance (QUA)

**Note**: The Assessor role is explicitly defined in EN 50128 Section 5.3.8 and MUST be completely independent for SIL 1–4. SIL 0 is exempt per §6.4.1.2 (ISO 9001 certified organisations).

### 11.4 Deliverables

See [`DELIVERABLES.md`](DELIVERABLES.md) — Phase 8: Assessment (Annex C items 45–46).

**Additional normative output (no Annex C number)**:
- **Software Assessment Verification Report** (`docs/reports/Software-Assessment-Verification-Report.md`) — written by VER — required by §6.4.4.6

### 11.5 Assessment Checklist

> **See** `.opencode/agents/cod.md` → Phase Gate Reference → Gate 7: Assessment Gate for the full assessment checklist, COD behavior, and independence verification procedure.

### 11.6 EN 50128 References
- **Section 6.4.1.1**: "The software shall be subjected to an independent assessment" — mandatory in practice for SIL 3-4
- **Section 6.4.4.1**: Assessment activities mandatory for SIL 3-4
- Section 6.4: Software assessment (general)
- Table A.1: Lifecycle requirements

### 11.7 Phase Gate (COD Checkpoint)

**Command**: `@cod gate-check assessment`

> **See** `.opencode/agents/cod.md` → Phase Gate Reference → Gate 7: Assessment Gate for the full gate checklist, EN 50128 requirements, COD behavior, and critical independence check.

---

## 12. Phase 9: Software Deployment (Section 9.1)

### 12.1 Objectives
- Deploy validated and assessed software to operational environment
- Ensure controlled and traceable deployment
- Verify deployment correctness
- Update configuration records

### 12.2 Key Activities
1. Prepare Software Release and Deployment Plan
2. Prepare Software Deployment Manual
3. Prepare Release Notes (plural — deployment release notes)
4. Execute deployment to target environment
5. Record deployment activities (Deployment Records)
6. Verify deployment correctness (Deployment Verification Report)
7. Establish deployment baseline

### 12.3 Agents Involved
- Project Manager (PM) - PRIMARY coordination
- Configuration Manager (CM) - deployment records, baseline management
- Designer (DES) - deployment manual, release notes
- Verifier (VER) - deployment verification report

### 12.4 Deliverables

See [`DELIVERABLES.md`](DELIVERABLES.md) — Phase 9: Deployment (Annex C items 36–40).

**Important**: Item 38 **"Release Notes"** (plural) is the deployment-phase release notes document — distinct from the **Release Note** (singular, doc 27) produced in the Validation phase per §7.7.4.12.

### 12.5 Deployment Checklist

> **See** `.opencode/agents/cod.md` → Phase Gate Reference → Gate 8: Deployment Gate for the full deployment checklist and COD gate behavior.

### 12.6 EN 50128 References
- Section 9.1: Software deployment
- Annex C Table C.1: Items 36–40

### 12.7 Entry Criteria
- Phase 8 Assessment gate passed (deployment authorization obtained)
- Target environment available and prepared
- Software Release and Deployment Plan approved

### 12.8 Exit Criteria
- Deployment Verification Report approved
- Deployment Records complete
- Deployment baseline established
- Operational system accepted

### 12.9 Phase Gate (COD Checkpoint)

**Command**: `@cod gate-check deployment`

> **See** `.opencode/agents/cod.md` → Phase Gate Reference → Gate 8: Deployment Gate for the full gate checklist and COD behavior.

---

## 13. Phase 10: Software Maintenance (Section 9.2)

### 13.1 Objectives
- Manage software changes after deployment
- Maintain configuration control during operation
- Document all changes and maintenance activities
- Verify maintenance changes meet original SIL requirements

### 13.2 Key Activities
1. Establish Software Maintenance Plan
2. Process change requests via Change Control Board (CCB)
3. Record all change requests and resolutions (Software Change Records)
4. Record all maintenance activities (Software Maintenance Records)
5. Verify maintenance changes (Software Maintenance Verification Report)
6. Update configuration baselines after each maintenance release

### 13.3 Agents Involved
- Project Manager (PM) - CCB leadership, change approval
- Configuration Manager (CM) - change records, maintenance records, baseline management
- Verifier (VER) - maintenance verification
- All technical agents as needed (REQ, DES, IMP, TST, VER per change scope)

### 13.4 Deliverables

See [`DELIVERABLES.md`](DELIVERABLES.md) — Phase 10: Maintenance (Annex C items 41–44).

**Note**: Annex C item 42 contains a typo in the standard — "Software Chang Records". The correct name per Section 9.2.4 is **"Software Change Records"**.

### 13.5 Maintenance Checklist

> **See** `.opencode/agents/cm.md` → Configuration Management Reference → Maintenance Activities for the full maintenance checklist and change management procedures.

### 13.6 EN 50128 References
- Section 9.2: Software maintenance
- Annex C Table C.1: Items 41–44

### 13.7 Entry Criteria
- Phase 9 Deployment complete
- Software Maintenance Plan approved
- CCB operational

### 13.8 Exit Criteria (per maintenance release)
- Software Change Records complete for all changes
- Software Maintenance Verification Report approved
- Maintenance baseline established

---

## 14. Lifecycle Coordinator (COD) Overview

> **See** `.opencode/agents/cod.md` → Phase Gate Reference for the complete COD authority structure, commands, SIL-dependent enforcement, phase gate list, background monitoring, LIFECYCLE_STATE.md, user approval workflow, and independence preservation rules.

---

## 15. Lifecycle Workflow Examples

> **See** `.opencode/agents/cod.md` → Phase Gate Reference → Workflow Examples for complete SIL 3, SIL 0-1, and SIL 2 workflow examples.

---

## 16. Traceability Requirements

### 16.1 Mandatory Traceability Links

```
System Requirements
        ↓
Software Requirements (Software Requirements Specification)
        ↓
Software Architecture (Software Architecture Specification)
        ↓
Software Design (Software Design Specification)
        ↓
Source Code (*.c, *.h)
        ↓
Unit Tests
        ↓
Integration Tests
        ↓
Validation Tests
```

### 16.2 Bidirectional Traceability

All traceability MUST be bidirectional:
- Forward: Requirement → Design → Code → Test
- Backward: Test → Code → Design → Requirement

### 16.3 Traceability Matrix Example

| Requirement | Design Module | Source File | Test Case | Status |
|-------------|---------------|-------------|-----------|--------|
| REQ-FUNC-001 | door_control | door_control.c | TC-001 | ✓ |
| REQ-SAFE-001 | fail_safe | door_control.c | TC-010 | ✓ |

---

## 17. Quality Gates

### 17.1 Phase Gate Criteria

Each phase has entry and exit criteria (quality gates) that MUST be satisfied:

| Phase | Entry Gate | Exit Gate |
|-------|------------|-----------|
| Requirements | System req available | Software Requirements Specification approved |
| Design | Software Requirements Specification approved | Software Architecture Specification/Software Design Specification approved |
| Implementation | Software Design Specification approved | Code reviewed, tests pass |
| Integration | Unit tests pass | Integration tests pass |
| Validation | Integration complete | Customer acceptance |

### 17.2 Quality Gate Reviews

All quality gates require:
- [ ] Deliverables complete
- [ ] Reviews passed
- [ ] Traceability verified
- [ ] Quality metrics met
- [ ] Approvals obtained

---

## 18. Documentation Requirements

### 18.1 Mandatory Documents by Phase

See [`DELIVERABLES.md`](DELIVERABLES.md) for the complete phase-to-document mapping (Annex C Table C.1).

### 18.2 Document Templates

Templates available in:
- `docs/templates/` - Generic templates
- `.opencode/skills/en50128-documentation/` - EN 50128 specific templates

---

## 19. Tool Qualification

> **See** `TOOLS.md` for the complete tool catalogue including T1/T2/T3 qualification categories (EN 50128 Section 6.7), qualification requirements by SIL level, and all tools used in this workspace.

---

## 20. Configuration Management

> **See** `.opencode/agents/cm.md` → Configuration Management Reference for the complete CM procedures including version control, baseline management, change management (CCB), traceability management, CM activities, and EN 50128 Table A.9 CM techniques.

**Note**: Configuration Management is **MANDATORY for ALL SIL levels (0, 1, 2, 3, 4)** per Table A.9.

---

## 21. SIL-Specific Requirements Summary

### 21.1 SIL 0-1 (Low Safety Integrity)

| Aspect | Requirement |
|--------|-------------|
| Lifecycle | V-Model recommended |
| Independence | Not required |
| Coverage | 80% statement, 70% branch |
| MISRA C | Recommended |
| Complexity | ≤ 20 |

### 21.2 SIL 2 (Medium Safety Integrity)

| Aspect | Requirement |
|--------|-------------|
| Lifecycle | V-Model mandatory |
| Independence | Highly recommended |
| Coverage | 100% statement, 100% branch |
| MISRA C | Mandatory |
| Complexity | ≤ 15 |
| Static Analysis | Mandatory |

### 21.3 SIL 3-4 (High Safety Integrity)

| Aspect | Requirement |
|--------|-------------|
| Lifecycle | V-Model mandatory |
| Independence | Mandatory (verification & validation) |
| Coverage | 100% statement, branch, MC/DC |
| MISRA C | Mandatory |
| Complexity | ≤ 10 |
| Static Analysis | Mandatory |
| FMEA/FTA | Mandatory |
| No Recursion | Highly recommended |
| No Dynamic Memory | Mandatory |

---

## 22. References

### 22.1 Standards
- EN 50128:2011 - Railway applications - Software for railway control and protection systems
- EN 50126:2017 - Railway applications - RAMS
- IEC 61508 - Functional safety
- MISRA C:2012 - Guidelines for the use of C

### 22.2 Related Documents
- `AGENTS.md` - Role-based agents including COD
- `.opencode/agents/cod.md` - **Authoritative source** for COD authority structure, commands, all 9 phase gate checklists, COD behavior blocks, and lifecycle workflow examples
- `.opencode/agents/cm.md` - **Authoritative source** for CM procedures: version control, baseline management, change management (CCB), traceability management, Table A.9 CM techniques
- `.opencode/agents/` - All agent definition files (req.md, des.md, imp.md, tst.md, int.md, ver.md, val.md, saf.md, qua.md, vmgr.md, pm.md)
- `TOOLS.md` - Complete tool catalogue including T1/T2/T3 qualification categories
- `.opencode/skills/` - Domain-specific skills for all lifecycle phases
- `docs/USER-GUIDE.md` - Complete platform user guide

---

## 23. Revision History

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2026-02-06 | EN50128 Team | Initial lifecycle definition |
| 1.1 | 2026-02-18 | EN50128 Team | Added Lifecycle Coordinator (COD) orchestration, phase gate checkpoints for all 8 phases, updated V-Model diagram |
| 1.2 | 2026-03-19 | EN50128 Team | ISA finding resolution: Added Phase 4 Component Design (§7.4) splitting it from Phase 5 Implementation (§7.5); renumbered Integration→Phase 6, Validation→Phase 7, Assessment→Phase 8, Deployment→Phase 9, Maintenance→Phase 10; removed Verification as discrete phase (now described as continuous cross-cutting activity); fixed V-Model diagram §7.4/7.5 labels; fixed SQAP ownership to VER (§6.5.4.3); removed fictitious Annex C item 27; moved SVaP to entry criteria in Validation phase; updated Assessment SIL note to reflect mandatory in practice (§6.4.1.1) for SIL 3-4; updated section numbering throughout (Sections 14–25); updated all COD gate references |
| 1.3 | 2026-03-19 | EN50128 Team | ISA finding resolution (v1.3): B4 — fixed clause ref §7.2.4.27→§7.2.4.20 for item 8 (Section 25 Phase 2); B5 — fixed clause refs for items 13 (§7.3.4.33→§7.3.4.29) and 14 (§7.3.4.40→§7.3.4.38) (Section 25 Phase 3); B6 — added SVaP approved baseline requirement per §5.3.2.4 to Phase 7 entry criteria (§9.9) and gate checklist (§9.11); B7 — corrected V-Model lifecycle model description from "mandatory" to "highly recommended per §5.3, Figures 3–4; alternative models permissible per §5.3.2.14" (header + §1.1); B8 — fixed gate command `@cod gate-check implementation` → `@cod gate-check implementation-testing` in Section 15 workflow examples; C1 — removed duplicate item 17 from Component Design Phase table in Section 24 (header corrected to "items 15–16"); C2 — added normative note to Planning table in Section 24 explaining §5.3.2.4/§6.2.4.2/§6.3.4.2/§6.5.4.3/§6.6.4.1 "shall" clauses override Annex C informative HR labels; C3 — replaced "(see note)" with explicit ownership in Section 24 Deployment table (item 36: PM/CM, item 37: PM/DES, item 38: PM/DES, item 39: CM, item 40: VER) |
| 1.4 | 2026-03-19 | EN50128 Team | Document reorganization: LIFECYCLE.md slimmed to lean V-Model reference (~900 lines from 2350). Operational content redistributed to authoritative agent files — per-phase gate checklists, COD behavior blocks, and workflow examples moved to `.opencode/agents/cod.md`; CM procedures (version control, baseline management, CCB change management, traceability management, Table A.9 CM subset) moved to `.opencode/agents/cm.md`; tool qualification catalogue moved to `TOOLS.md`. All operational content replaced with pointers. Sections 14, 15, 19, 20 replaced with pointer stubs. Phase-level checklists (§11.5, §12.5, §13.5) and gate blocks (§11.7, §12.9) replaced with pointers. Section 22 references updated to identify authoritative sources. |
| 1.5 | 2026-03-19 | EN50128 Team | Deliverables consolidation: All inline deliverable listings in phase sections (§3.4, §4.5, §5.5, §6.4, §7.5, §8.5, §9.5, §10.5, §11.4, §12.4, §13.4), §18.1, and all per-phase sub-tables in §24 and §25 replaced with pointers to `DELIVERABLES.md` (single source of truth for Annex C Table C.1). Normative notes, naming conventions, doc type mapping, compliance checklist, Quick Reference Table, Summary Statistics, and V-Model correspondence table retained in LIFECYCLE.md. Doc 27 (Release Note) updated to reflect its confirmed listing in DELIVERABLES.md. |

---

**Document Status**: Approved  
**Next Review**: [Date]  
**Approval**: [Signature]

---

## 24. Deliverable Reference

> **See [`DELIVERABLES.md`](DELIVERABLES.md)** — single source of truth for all Annex C deliverables, including:
> - Complete Annex C Table C.1 document inventory (46 numbered documents)
> - Document ID convention and naming rules
> - Normative override notes for planning documents
> - Key corrections and normative notes
> - Phase quick reference with YAML file names
> - Phase SIL level summary
> - V-Model specification → report correspondence table
