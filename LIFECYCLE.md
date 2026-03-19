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
- [ ] Software Quality Assurance Plan (SQAP) — written by **VER** (§6.5.4.3; Annex C "Written by" blank)
- [ ] **Software Quality Assurance Verification Report (SQAVR)** — written by VER (Annex C item 2)
- [ ] Software Configuration Management Plan (SCMP) — written by CM
- [ ] Software Verification Plan (SVP) — written by **VER** (not PM)
- [ ] Software Validation Plan (SVaP) — written by **VAL** (not PM)
- [ ] Project Standards Document
- [ ] Tool Qualification Plan (if applicable)

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

The Lifecycle Coordinator (COD) enforces phase gate compliance before allowing transition to Phase 2 (Requirements). Gate enforcement is SIL-dependent:

- **SIL 0-1**: Advisory mode - COD provides warnings if criteria not met, but allows user override
- **SIL 2**: Semi-strict mode - COD requires justification for proceeding with incomplete criteria
- **SIL 3-4**: Strict gatekeeper mode - COD BLOCKS transition until all mandatory criteria satisfied

**Gate Checklist**:
- [ ] SQAP (Software Quality Assurance Plan) approved and baselined — written by **VER** (§6.5.4.3)
- [ ] **SQAVR (Software Quality Assurance Verification Report) approved** — written by VER (Annex C item 2, newly required)
- [ ] SCMP (Software Configuration Management Plan) approved and baselined — written by CM
- [ ] SVP (Software Verification Plan) approved and baselined — written by **VER** (not PM)
- [ ] SVaP (Software Validation Plan) approved and baselined — written by **VAL** (not PM)
- [ ] Project standards document complete
- [ ] Tool qualification plan prepared (if applicable)
- [ ] Configuration management system operational
- [ ] Project organization defined with role assignments
- [ ] SIL level determined and documented
- [ ] LIFECYCLE_STATE.md initialized (via `@cod plan --sil [0-4] --project [name]`)

**EN 50128 Reference**: Section 5.3.2.5 - "All activities to be performed during a phase shall be defined and planned prior to commencement"

**COD Behavior**:
- Verifies all planning deliverables present in project repository
- Checks document approval status in LIFECYCLE_STATE.md
- Validates configuration management baseline established
- For SIL 3-4: BLOCKS Phase 2 (Requirements) until gate passed

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
- [ ] Software Requirements Specification
- [ ] traceability (embedded in Software Requirements Specification)
- [ ] Hazard Log
- [ ] Safety Requirements Specification
- [ ] **QA Document Template Compliance Report (MANDATORY SIL 3-4, BEFORE VER)**
- [ ] Requirements Review Report

### 4.6 Requirements Quality Checklist
- [ ] All requirements unambiguous
- [ ] All requirements testable
- [ ] All requirements traceable
- [ ] SHALL/SHOULD/MAY keywords used correctly
- [ ] SIL levels assigned
- [ ] C language constraints considered
- [ ] Safety requirements identified

### 4.7 EN 50128 Techniques/Measures (Table A.2)

**Mandatory for Requirements Specification:**

| Technique/Measure | SIL 0 | SIL 1-2 | SIL 3-4 | Reference |
|-------------------|-------|---------|---------|-----------|
| Formal Methods | - | R | HR | D.28 |
| Modelling | R | R | HR | Table A.17 |
| Structured Methodology | R | R | HR | D.52 |
| Decision Tables | R | R | HR | D.13 |

**Key:** M = Mandatory, HR = Highly Recommended, R = Recommended, - = No recommendation

**Requirements (per EN 50128 7.2.4):**
- One or more techniques from Table A.2 SHALL be selected
- Natural language description PLUS formal/semiformal notation
- All requirements SHALL be unambiguous, testable, and traceable

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

The Lifecycle Coordinator (COD) enforces requirements phase completion before allowing transition to Phase 3 (Design).

**Gate Checklist**:
- [ ] Software Requirements Specification complete, reviewed, and approved
- [ ] All requirements unambiguous, testable, and traceable
- [ ] traceability (embedded in Software Requirements Specification) complete (forward to system requirements)
- [ ] SIL levels assigned to all requirements
- [ ] Hazard Log established and all hazards analyzed
- [ ] Safety requirements identified and specified
- [ ] **QA document template compliance verified (MANDATORY SIL 3-4)**
- [ ] Requirements review report approved
- [ ] SHALL/SHOULD/MAY keywords used correctly
- [ ] C language constraints considered in requirements
- [ ] Requirements baseline established by Configuration Manager
- [ ] USER APPROVAL obtained for requirement establishment (mandatory via `@cod approve-requirement`)

**EN 50128 Requirements (Section 7.2)**:
- Techniques from Table A.2 applied (Structured Methodology HR for SIL 3-4)
- Requirements unambiguous and verifiable (mandatory)
- Traceability to system requirements (mandatory SIL 3-4)

**COD Behavior**:
- **User approval verification**: COD SHALL verify user explicitly approved requirement activities
- Validates traceability completeness (all requirements traced bidirectionally)
- Checks SIL assignment for all requirements
- Verifies hazard analysis completeness (FMEA/FTA for SIL 3-4)
- For SIL 3-4: BLOCKS Phase 3 (Design) until gate passed
- For SIL 2: Requires justification if criteria incomplete
- For SIL 0-1: Provides warnings only

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
- [ ] Software Architecture Specification
- [ ] Software Design Specification
- [ ] Interface Control Document (ICD)
- [ ] Design Traceability Matrix
- [ ] **QA Document Template Compliance Report (MANDATORY SIL 3-4, BEFORE VER)**
- [ ] Design Review Report
- [ ] FMEA/FTA Results (SIL 3-4)

### 5.6 Design Constraints by SIL

#### SIL 2+ Mandatory Constraints
- Static memory allocation ONLY (no malloc/free)
- Fixed-width integer types (uint8_t, uint16_t, uint32_t)
- Defensive programming mandatory
- Error handling for all functions
- Modular design

#### SIL 3-4 Additional Constraints
- Cyclomatic complexity ≤ 10 per function
- No recursion (highly recommended)
- Redundant safety mechanisms
- Independent verification required

### 5.7 Design Review Checklist
- [ ] Architecture traceable to requirements
- [ ] Module interfaces clearly defined
- [ ] Static allocation used (SIL 2+)
- [ ] Complexity limits defined
- [ ] Error handling comprehensive
- [ ] MISRA C compliance considered
- [ ] Safety mechanisms designed

### 5.8 EN 50128 Techniques/Measures (Table A.3)

**Software Architecture Techniques (EN 50128 Section 7.3):**

| Technique/Measure | SIL 0 | SIL 1-2 | SIL 3-4 | Reference |
|-------------------|-------|---------|---------|-----------|
| **Design & Safety** ||||
| Defensive Programming | - | HR | HR | D.14 |
| Fault Detection & Diagnosis | - | R | HR | D.26 |
| Error Detecting Codes | - | R | HR | D.19 |
| Failure Assertion Programming | - | R | HR | D.24 |
| Software Error Effect Analysis | - | R | HR | D.25 |
| **Recovery** ||||
| Retry Fault Recovery | - | R | HR | D.46 |
| Memorising Executed Cases | - | R | HR | D.36 |
| Backward Recovery | - | NR | R | D.5 |
| Forward Recovery | - | NR | R | D.30 |
| **Structure** ||||
| Information Encapsulation | R | HR | HR | D.33 |
| Fully Defined Interface | HR | HR | HR | D.38 |
| Structured Methodology | R | HR | **M** | D.52 |
| **Analysis** ||||
| Formal Methods | - | R | HR | D.28 |
| Modelling | R | R | HR | Table A.17 |

**Approved Combinations:**
- **SIL 3-4:** Options: (a) 1,7,19,22 + one from 4,5,12,21 OR (b) 1,4,19,22 + one from 2,5,12,15,21
- **SIL 1-2:** 1,19,22 + one from 2,4,5,7,12,15,21

**Key:** M = Mandatory, HR = Highly Recommended, R = Recommended, NR = Not Recommended

### 5.9 EN 50128 References
- Section 7.3: Software architecture and design  
- Table A.3: Software architecture techniques
- Annex D: Technique descriptions

### 5.10 Entry Criteria
- Software Requirements Specification approved
- Design standards defined
- FMEA/FTA planned (SIL 3-4)

### 5.11 Exit Criteria
- Software Architecture Specification and Software Design Specification complete and approved
- Design traceable to requirements
- Design review passed
- Complexity limits established

### 5.12 Phase Gate (COD Checkpoint)

**Command**: `@cod gate-check design`

The Lifecycle Coordinator (COD) enforces design phase completion before allowing transition to Phase 4 (Component Design).

**Gate Checklist**:
- [ ] Software Architecture Specification complete and approved
- [ ] Software Design Specification complete and approved
- [ ] Interface Control Document (ICD) complete
- [ ] Design Traceability Matrix complete (requirements → design modules)
- [ ] All interfaces fully defined and documented
- [ ] **QA document template compliance verified (MANDATORY SIL 3-4)**
- [ ] Design review report approved
- [ ] FMEA/FTA results documented (highly recommended SIL 3-4)
- [ ] Cyclomatic complexity limits defined (≤10 for SIL 3-4, ≤15 for SIL 2)
- [ ] Defensive programming patterns designed (mandatory SIL 2+)
- [ ] Error handling strategy defined for all functions
- [ ] Static memory allocation confirmed (no malloc/free for SIL 2+)
- [ ] Safety mechanisms designed (fault detection, redundancy, etc.)
- [ ] Modular design verified (mandatory SIL 2+)
- [ ] Design baseline established by Configuration Manager

**EN 50128 Requirements (Section 7.3, Table A.3)**:
- Structured Methodology applied (mandatory SIL 3-4)
- Modular Approach used (mandatory SIL 2+)
- Defensive Programming patterns defined (highly recommended SIL 2+)
- Approved technique combinations used (per Table A.3)

**COD Behavior**:
- Validates design traceability to ALL requirements (traceability completeness)
- Checks complexity limits appropriate for SIL level
- Verifies defensive programming patterns documented
- Confirms static allocation strategy (SIL 2+)
- For SIL 3-4: BLOCKS Phase 4 (Component Design) until gate passed
- For SIL 2: Requires justification if FMEA/FTA not performed
- For SIL 0-1: Provides warnings only

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
- [ ] Software Component Design Specification (Annex C item 15) — written by DES
- [ ] Software Component Test Specification (Annex C item 16) — written by TST
- [ ] Software Component Design Verification Report (Annex C item 17) — written by VER

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

**Gate Checklist**:
- [ ] Software Component Design Specification complete and approved (Annex C item 15, written by DES)
- [ ] Software Component Test Specification complete (Annex C item 16, written by TST)
- [ ] Software Component Design Verification Report approved (Annex C item 17, written by VER)
- [ ] Component design traceable to Software Design Specification
- [ ] Component test strategies defined (test cases traceable to component requirements)
- [ ] Component design baseline established by Configuration Manager

**COD Behavior**:
- For SIL 3-4: BLOCKS Phase 5 (Implementation) until gate passed
- For SIL 2: Requires justification if component design not verified
- For SIL 0-1: Provides warnings only

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
- [ ] Software Source Code and supporting documentation (Annex C item 18) — written by IMP
- [ ] **Software Component Test Report (Annex C item 20) — written by TST** (per §7.5.3 and Annex C Table C.1)
- [ ] Code Coverage Report (100% for SIL 3-4)
- [ ] Static Analysis Report (PC-lint/Cppcheck)
- [ ] Complexity Analysis Report (Lizard)
- [ ] **QA Code Review Report (MANDATORY - includes template compliance for code documentation)**
- [ ] Software Source Code Verification Report (Annex C item 19) — written by VER

### 7.6 MISRA C:2012 Compliance

#### Mandatory for SIL 2+
- All mandatory rules: ZERO violations
- Required rules: Violations must be justified
- Advisory rules: Recommended

#### Key MISRA Rules
- **Rule 21.3**: No dynamic memory allocation
- **Rule 17.7**: Check all function return values
- **Rule 4.6**: Use fixed-width types
- **Rule 14.4**: Boolean conditions explicit
- **Rule 8.7**: Internal linkage when possible

### 7.7 Coverage Requirements by SIL

| SIL Level | Statement | Branch | MC/DC | Notes |
|-----------|-----------|--------|-------|-------|
| SIL 0-1 | 80% | 70% | - | Recommended |
| SIL 2 | 100% | 100% | - | Mandatory |
| SIL 3-4 | 100% | 100% | 100% | Mandatory |

### 7.8 Implementation Checklist
- [ ] MISRA C:2012 compliant (zero mandatory violations)
- [ ] Static allocation only (SIL 2+)
- [ ] No recursion
- [ ] All pointers validated
- [ ] All return values checked
- [ ] Cyclomatic complexity ≤ limit
- [ ] Unit tests written
- [ ] Coverage requirements met
- [ ] Static analysis clean
- [ ] Code reviewed and approved

### 7.9 EN 50128 Techniques/Measures (Table A.4)

**Software Component Implementation and Testing (EN 50128 Section 7.5):**

| Technique/Measure | SIL 0 | SIL 1-2 | SIL 3-4 | Reference |
|-------------------|-------|---------|---------|-----------|
| **Methodology** ||||
| Formal Methods | - | R | HR | D.28 |
| Modelling | R | HR | HR | Table A.17 |
| Structured Methodology | R | HR | **M** | D.52 |
| Modular Approach | HR | **M** | **M** | D.38 |
| Components | HR | HR | HR | Table A.20 |
| **Coding** ||||
| Design and Coding Standards | HR | HR | **M** | Table A.12 |
| Analysable Programs | HR | HR | **M** | D.2 |
| Strongly Typed Language | R | HR | HR | D.49 |
| Structured Programming | R | HR | **M** | D.53 |
| Language Subset | - | - | HR | D.35 |
| **Paradigms** ||||
| Procedural Programming | R | HR | HR | D.60 |
| Object Oriented Programming | R | R | R | Table A.22, D.57 |

**Approved Combinations:**
- **SIL 3-4:** 4,5,6,8 + one from 1 or 2 (Modular Approach + Components + Standards + Strongly Typed + Formal Methods/Modelling)
- **SIL 1-2:** 3,4,5,6 + one from 8,9,10 (Structured + Modular + Components + Standards + language choice)

**Key:** M = Mandatory, HR = Highly Recommended, R = Recommended

**Additional Requirements:**
- MISRA C:2012 Mandatory for SIL 2+
- Static memory allocation Mandatory for SIL 2+
- No recursion Highly Recommended for SIL 3-4

### 7.10 EN 50128 References
- Section 7.5: Component implementation and testing
- Table A.4: Design and implementation techniques
- Table A.12: Coding standards (MISRA C)
- Table A.15: Programming languages

### 7.11 Entry Criteria
- Software Component Design Specification approved (Phase 4 gate passed)
- Coding standards defined
- Unit test framework ready
- Static analysis tools configured

### 7.12 Exit Criteria
- All code implemented and reviewed
- Component tests pass
- Coverage requirements met
- Static analysis clean
- Code traceable to component design

### 7.13 Phase Gate (COD Checkpoint)

**Command**: `@cod gate-check implementation-testing`

The Lifecycle Coordinator (COD) enforces implementation phase completion before allowing transition to Phase 6 (Integration).

**Gate Checklist**:
- [ ] All source code (*.c, *.h) complete and reviewed
- [ ] **Software Component Test Report complete (Annex C item 20, written by TST) — per §7.5.3**
- [ ] **QA code review report approved (MANDATORY - includes MISRA C compliance check)**
- [ ] MISRA C:2012 compliance verified - ZERO mandatory violations (SIL 2+)
- [ ] Unit tests written for all modules
- [ ] All unit tests pass (100% pass rate)
- [ ] Code coverage requirements met:
  - SIL 0-1: 80% statement, 70% branch (recommended)
  - SIL 2: 100% statement, 100% branch (mandatory)
  - SIL 3-4: 100% statement, 100% branch, 100% condition (mandatory)
- [ ] Static analysis clean (PC-lint/Cppcheck - zero critical issues)
- [ ] Cyclomatic complexity within limits (≤10 SIL 3-4, ≤15 SIL 2, ≤20 SIL 0-1)
- [ ] Implementation Traceability Matrix complete (design → code)
- [ ] Static memory allocation verified (no malloc/free/realloc for SIL 2+)
- [ ] No recursion (highly recommended SIL 3-4)
- [ ] All pointers validated before use
- [ ] All function return values checked
- [ ] Defensive programming implemented (input validation, error handling)
- [ ] Code baseline established by Configuration Manager

**EN 50128 Requirements (Section 7.5, Table A.4 / Table A.12)**:
- Structured Methodology applied (mandatory SIL 3-4, per §7.5.4.1 and Table A.4)
- Modular Approach used (mandatory SIL 2+, per Table A.4)
- Design and Coding Standards enforced (mandatory SIL 3-4, MISRA C:2012, per Table A.12)
- Analysable Programs (mandatory SIL 3-4, per Table A.4)
- Structured Programming (mandatory SIL 3-4, per Table A.4)

**COD Behavior**:
- Validates MISRA C compliance reports (zero mandatory violations for SIL 2+)
- Checks code coverage against SIL-specific thresholds
- Verifies complexity metrics for all functions
- Confirms traceability from code to design
- Validates unit test pass rate (must be 100%)
- For SIL 3-4: BLOCKS Phase 6 (Integration) until gate passed
- For SIL 2: Requires justification if coverage < 100% statement/branch
- For SIL 0-1: Provides warnings if recommended thresholds not met

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
- [ ] Software Integration Test Report (Annex C item 21) — written by INT
- [ ] Software/Hardware Integration Test Specification (Annex C item 13, produced in Phase 3) — input
- [ ] Software/Hardware Integration Test Report (Annex C item 22) — written by INT
- [ ] Integration Traceability Matrix

**Note**: Software Component Test Report (Annex C item 20) is a **Phase 5 deliverable** per §7.5.3 and Annex C Table C.1 — it is produced in Phase 5 (Component Implementation and Testing) and consumed as input to Phase 6.

### 8.6 EN 50128 Techniques/Measures (Table A.6)

**Integration (EN 50128 Section 7.6):**

| Technique/Measure | SIL 0 | SIL 1-2 | SIL 3-4 | Reference |
|-------------------|-------|---------|---------|-----------|
| Functional and Black-box Testing | HR | HR | HR | Table A.14 |
| Non-Regression Testing | R | HR | HR | D.36 |
| Performance Testing | - | R | HR | Table A.18 |
| Interface Testing | HR | HR | HR | D.34 |
| Modelling | - | R | R | Table A.17 |
| Equivalence Classes and Input Partition Testing | - | R | HR | D.18 |

**Key:** M = Mandatory, HR = Highly Recommended, R = Recommended

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

### 8.10 Integration Checklist
- [ ] Integration strategy defined (bottom-up / top-down / sandwich)
- [ ] All module interfaces tested
- [ ] Data flow between components verified
- [ ] Software/hardware integration performed on target
- [ ] Performance testing performed (mandatory SIL 3-4)
- [ ] Non-regression testing performed after each defect fix
- [ ] Integration traceability complete (tests → design)
- [ ] Integration defects resolved and retested

### 8.11 Phase Gate (COD Checkpoint)

**Command**: `@cod gate-check integration`

The Lifecycle Coordinator (COD) enforces integration phase completion before allowing transition to Phase 7 (Validation).

**Gate Checklist**:
- [ ] Software Integration Test Report complete (Annex C item 21, written by INT)
- [ ] Software/Hardware Integration Test Report complete (Annex C item 22, written by INT)
- [ ] All integration tests passed (100% pass rate)
- [ ] Interface testing complete for all module interfaces
- [ ] Performance testing complete (mandatory SIL 3-4)
- [ ] Non-regression testing performed
- [ ] Integration Traceability Matrix complete (tests → design requirements)
- [ ] Integration defects resolved and closed
- [ ] Integration baseline established by Configuration Manager

**EN 50128 Requirements (Section 7.6, Table A.6)**:
- Functional and black-box testing performed (HR for all SILs)
- Interface testing performed (HR for all SILs)
- Performance testing performed (HR SIL 3-4)
- Non-regression testing performed (HR SIL 3-4)

**COD Behavior**:
- Validates all integration tests passed (100% pass rate)
- Verifies interface testing completeness
- Confirms performance testing performed (SIL 3-4)
- Ensures integration traceability complete
- For SIL 3-4: BLOCKS Phase 7 (Validation) until gate passed
- For SIL 2: Requires justification if performance testing not performed
- For SIL 0-1: Provides warnings if recommended thresholds not met

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
- [ ] Overall Software Test Report (Annex C item 24) — written by TST
- [ ] Software Integration Verification Report (Annex C item 23) — written by VER
- [ ] Software Validation Report (Annex C item 25) — written by VAL
- [ ] **Tools Validation Report** (Annex C item 26) — HR for SIL 1+, R for SIL 0
- [ ] **Release Note** (§7.7.4.12 normative output — no Annex C number) — written by DES/PM
- [ ] **Software Validation Verification Report** (§6.3.3 normative output — no Annex C number) — written by VER
- [ ] User Acceptance Test Results
- [ ] Safety Validation Report
- [ ] Performance Test Results
- [ ] **QA Validation Review Report (includes template compliance)**
- [ ] Acceptance Certificate

### 9.6 Validation Testing Checklist
- [ ] All requirements validated (traceability to Overall Software Test Specification)
- [ ] Operational scenarios tested
- [ ] Safety requirements validated
- [ ] Performance requirements met (mandatory SIL 3-4)
- [ ] User acceptance obtained
- [ ] Validation team independent (mandatory SIL 3-4)
- [ ] Tools Validation Report complete (Annex C item 26, HR for SIL 1+)
- [ ] Release Note prepared (§7.7.4.12 normative — no Annex C number)

### 9.7 EN 50128 Techniques/Measures (Table A.7)

**Overall Software Testing/Validation (EN 50128 Section 7.7):**

| Technique/Measure | SIL 0 | SIL 1-2 | SIL 3-4 | Reference |
|-------------------|-------|---------|---------|-----------|
| Performance Testing | - | HR | **M** | Table A.18 |
| Functional and Black-box Testing | HR | HR | **M** | Table A.14 |
| Modelling | - | R | R | Table A.17 |

**Key:** M = Mandatory, HR = Highly Recommended, R = Recommended

**Independence Requirements:**
- **SIL 3-4:** Validator MUST be independent from development team
- **SIL 3-4:** Validator SHALL NOT report to Project Manager
- **SIL 2:** Independence highly recommended

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

The Lifecycle Coordinator (COD) enforces validation phase completion before allowing transition to Phase 8 (Assessment).

**Gate Checklist**:
- [ ] Software Validation Plan (SVaP) approved, at an **approved baseline** per §5.3.2.4, and followed (input document from Phase 1)
- [ ] Software Integration Verification Report complete (Annex C item 23, written by VER)
- [ ] Overall Software Test Report complete (Annex C item 24, written by TST)
- [ ] Software Validation Report complete and approved (Annex C item 25, written by VAL)
- [ ] **Tools Validation Report complete (Annex C item 26) — HR for SIL 1+, R for SIL 0**
- [ ] **Release Note prepared and approved (§7.7.4.12 normative — no Annex C number) — distinct from deployment "Release Notes" (item 38)**
- [ ] All validation tests executed and passed (100% pass rate)
- [ ] All software requirements validated (traceability completeness check)
- [ ] User Acceptance Test (UAT) results documented
- [ ] Customer acceptance obtained (sign-off required)
- [ ] Safety Validation Report complete
- [ ] All safety requirements validated
- [ ] Performance test results documented and requirements met (mandatory SIL 3-4)
- [ ] Operational scenarios tested in target environment
- [ ] **QA validation review approved (includes template compliance)**
- [ ] Acceptance certificate obtained
- [ ] Independent validation team verified (mandatory SIL 3-4)
- [ ] Validator independence from development confirmed (SIL 3-4)
- [ ] Validation traceability complete (tests → requirements)
- [ ] Validation baseline established by Configuration Manager

**EN 50128 Requirements (Section 7.7, Table A.7)**:
- Performance Testing performed (mandatory SIL 3-4)
- Functional and Black-box Testing performed (mandatory SIL 3-4)
- Independent validator assigned (mandatory SIL 3-4)
- Validator SHALL NOT report to Project Manager (SIL 3-4)

**COD Behavior**:
- Validates all validation tests passed (100% pass rate)
- Verifies customer acceptance obtained
- Checks safety requirements validation completeness
- Confirms performance requirements met (SIL 3-4)
- **Validates validator independence** (SIL 3-4): COD verifies validator is independent from development team and does NOT report to PM
- Ensures traceability complete (all requirements validated)
- For SIL 3-4: BLOCKS transition to assessment until gate passed AND independence verified
- For SIL 2: Requires justification if validator not independent
- For SIL 0-1: Provides warnings only

**Critical Independence Check (SIL 3-4)**:
COD SHALL verify validator role assignment and organizational independence before authorizing validation activities and gate passage.

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
- [ ] Software Verification Report
- [ ] Static Analysis Reports
- [ ] Review Records
- [ ] Traceability Verification
- [ ] Complexity Analysis
- [ ] Coverage Reports
- [ ] Verification Evidence Package

### 10.6 Verification Checklist
- [ ] Requirements verification complete
- [ ] Design verification complete
- [ ] Code verification complete
- [ ] Test verification complete
- [ ] Traceability verified
- [ ] MISRA C compliance verified
- [ ] Coverage verified
- [ ] Independent verification (SIL 3-4)

### 10.7 EN 50128 Techniques/Measures (Table A.5)

**Verification and Testing (EN 50128 Sections 6.2 and 7.3):**

| Technique/Measure | SIL 0 | SIL 1-2 | SIL 3-4 | Reference |
|-------------------|-------|---------|---------|-----------|
| **Verification** ||||
| Formal Proof | - | R | HR | D.29 |
| Static Analysis | - | HR | **M** | Table A.19 |
| Metrics | - | R | HR | D.37 |
| Traceability | R | HR | **M** | D.58 |
| Software Error Effect Analysis | - | R | HR | D.25 |
| **Testing** ||||
| Dynamic Analysis and Testing | - | HR | **M** | Table A.13 |
| Test Coverage for Code | R | HR | **M** | Table A.21 |
| Functional/Black-Box Testing | HR | HR | **M** | Table A.14 |
| Performance Testing | - | HR | **M** | Table A.18 |
| Interface Testing | HR | HR | HR | D.34 |

**Approved Combinations:**
- **SIL 3-4:** 3,5,7,8 + one from 1,2,6 (Dynamic Analysis + Traceability + Coverage + Functional + Formal/Static/SEEA)
- **SIL 1-2:** 5 + one from 2,3,8 (Traceability + Static/Dynamic/Functional)

**Key:** M = Mandatory, HR = Highly Recommended, R = Recommended

**Coverage Requirements (Table A.21):**

| SIL Level | Statement | Branch | Condition | MC/DC |
|-----------|-----------|--------|-----------|-------|
| SIL 0-1 | HR | HR | R | - |
| SIL 2 | HR | **M** | HR | R |
| SIL 3-4 | **M** | **M** | **M** | HR |

**NOTE:** Items 1,2,4,5,6,7 are for verification activities. Items 3,8,9,10 are for testing activities.

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
- [ ] **Software Assessment Plan** (Annex C item 45) — written by **ASR** (Assessor), NOT PM
- [ ] **Software Assessment Report** (Annex C item 46) — written by **ASR** (Assessor), NOT PM
- [ ] **Software Assessment Verification Report** (§6.4.4.6 normative output — no Annex C number) — written by VER
- [ ] Compliance Matrix
- [ ] Safety Case
- [ ] Approval Certificate
- [ ] Deployment Authorization

### 11.5 Assessment Checklist
- [ ] All lifecycle phases complete
- [ ] All deliverables produced
- [ ] Traceability complete
- [ ] Verification complete
- [ ] Validation complete
- [ ] MISRA C compliance verified
- [ ] Coverage requirements met
- [ ] Safety requirements satisfied
- [ ] EN 50128 compliance demonstrated

### 11.6 EN 50128 References
- **Section 6.4.1.1**: "The software shall be subjected to an independent assessment" — mandatory in practice for SIL 3-4
- **Section 6.4.4.1**: Assessment activities mandatory for SIL 3-4
- Section 6.4: Software assessment (general)
- Table A.1: Lifecycle requirements

### 11.7 Phase Gate (COD Checkpoint)

**Command**: `@cod gate-check assessment`

The Lifecycle Coordinator (COD) enforces assessment phase completion before allowing transition to Phase 9 (Deployment). This gate is MANDATORY for SIL 1–4 projects (per §6.4.1.1 and §5.1.2.4); SIL 0 projects are exempt per §6.4.1.2.

**Gate Checklist**:
- [ ] **Software Assessment Plan complete and approved (Annex C item 45) — written by ASR**
- [ ] **Software Assessment Report complete and approved (Annex C item 46) — written by ASR**
- [ ] Compliance Matrix complete (all EN 50128 requirements traced)
- [ ] Safety Case complete and approved
- [ ] All lifecycle phases verified complete
- [ ] All mandatory deliverables produced and approved (per Annex C Table C.1)
- [ ] End-to-end traceability verified complete (requirements → code → tests)
- [ ] Verification Evidence Package complete
- [ ] Validation results reviewed and accepted
- [ ] MISRA C:2012 compliance verified (zero mandatory violations for SIL 2+)
- [ ] Coverage requirements met (100% statement/branch/condition for SIL 3-4)
- [ ] All safety requirements satisfied and validated
- [ ] Independent assessor verified (mandatory SIL 1-4 per §5.1.2.4; exempt SIL 0 per §6.4.1.2)
- [ ] Assessor independence from development confirmed (SIL 1-4)
- [ ] Approval Certificate issued
- [ ] Deployment Authorization obtained
- [ ] Final release baseline established by Configuration Manager

**EN 50128 Requirements (Section 6.4)**:
- Independent assessor assigned (mandatory SIL 1-4 per §6.4.1.1 and §5.1.2.4; SIL 0 exempt per §6.4.1.2)
- Assessor SHALL be completely independent (SIL 1-4)
- All lifecycle artifacts reviewed
- EN 50128 compliance demonstrated

**COD Behavior**:
- Validates all lifecycle phases complete (Planning → Requirements → Design → Component Design → Implementation → Integration → Validation → Assessment)
- Verifies end-to-end traceability (traceability complete and verified)
- Checks all deliverables present per SIL level requirements
- Confirms safety case complete and approved
- **Validates assessor independence** (SIL 1-4): COD verifies assessor is independent from development team, PM, and validator
- Ensures approval certificate and deployment authorization obtained
- For SIL 1-4: BLOCKS deployment until gate passed AND independent assessment complete
- For SIL 0: Provides warnings only (assessment exempt per §6.4.1.2)

**Critical Independence Check (SIL 3-4)**:
COD SHALL verify assessor role assignment and complete organizational independence before authorizing deployment (SIL 1-4).

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

| Annex C # | Document Name | Written by | SIL 0 | SIL 1-4 |
|-----------|--------------|-----------|-------|---------|
| 36 | **Software Release and Deployment Plan** | PM / CM | R | HR |
| 37 | **Software Deployment Manual** | PM / DES | R | HR |
| 38 | **Release Notes** (plural) | PM / DES | HR | HR |
| 39 | **Deployment Records** | CM | R | HR |
| 40 | **Deployment Verification Report** | VER | R | HR |

**Important**: Item 38 **"Release Notes"** (plural) is the deployment-phase release notes document — distinct from the **Release Note** (singular) produced in the Validation phase per §7.7.4.12, which has no Annex C item number.

### 12.5 Deployment Checklist
- [ ] Software Release and Deployment Plan approved
- [ ] Software Deployment Manual complete
- [ ] Release Notes prepared and reviewed
- [ ] Deployment executed per plan
- [ ] Deployment Records maintained
- [ ] Deployment Verification Report signed off
- [ ] Deployment baseline established by Configuration Manager
- [ ] Deployment Authorization obtained from Phase 8 Assessment gate

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

**Gate Checklist**:
- [ ] Software Release and Deployment Plan complete and approved (Annex C item 36)
- [ ] Software Deployment Manual complete (Annex C item 37)
- [ ] Release Notes prepared (Annex C item 38, plural — deployment release notes)
- [ ] Deployment Records complete (Annex C item 39)
- [ ] Deployment Verification Report approved (Annex C item 40)
- [ ] Deployment baseline established by Configuration Manager

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

| Annex C # | Document Name | Written by | SIL 0 | SIL 1-4 |
|-----------|--------------|-----------|-------|---------|
| 41 | **Software Maintenance Plan** | PM / CM | R | HR |
| 42 | **Software Change Records** | CM | HR | HR |
| 43 | **Software Maintenance Records** | CM | R | HR |
| 44 | **Software Maintenance Verification Report** | VER | R | HR |

**Note**: Annex C item 42 contains a typo in the standard — "Software Chang Records". The correct name per Section 9.2.4 is **"Software Change Records"**.

### 13.5 Maintenance Checklist
- [ ] Software Maintenance Plan established and approved
- [ ] All changes processed via CCB
- [ ] Software Change Records maintained for every change
- [ ] Software Maintenance Records updated after each activity
- [ ] Software Maintenance Verification Report produced for each maintenance release
- [ ] Configuration baselines updated
- [ ] Modified software re-validated at appropriate SIL level

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

### 14.1 Role and Authority

The **Lifecycle Coordinator (COD)** is a platform extension role (based on EN 50128 Section 5.3 "Lifecycle issues and documentation") that provides end-to-end lifecycle orchestration with phase gate enforcement. COD has overall lifecycle authority and sits above the Project Manager in the organizational structure.

**Authority Structure**:
```
        Safety Authority / Customer
                |
    ┌───────────┴───────────┐
    |                       |
Assessor          Lifecycle Coordinator (COD)
(independent)               |
            ┌───────────────┼────────────┐
            |               |            |
    Project Manager   Validator    Software Manager
    (PM)              (VAL)        (if separate)
    - Team mgmt       (independent)
    - Resources
    - Stakeholders
            |
            ├─── REQ, DES, IMP, TST, INT, VER, SAF, QUA, CM
```

### 14.2 COD Commands

| Command | Purpose | When to Use |
|---------|---------|-------------|
| `@cod plan --sil [0-4] --project [name]` | Initialize lifecycle tracking | At project start (Phase 0) |
| `@cod generate-system` | Generate 4 system-level documents | After `@cod plan`, before Phase 1 |
| `@cod gate-check <phase>` | Verify phase completion, authorize transition | After each phase completion |
| `@cod status` | View current lifecycle state | Anytime during project |
| `@cod approve-requirement` | Approve requirement activities | Before REQ activities begin |

### 14.3 SIL-Dependent Gate Enforcement

COD adapts its enforcement behavior based on project SIL level:

| SIL Level | Enforcement Mode | Behavior |
|-----------|------------------|----------|
| **SIL 0-1** | Advisory | Provides warnings if criteria not met, allows user override |
| **SIL 2** | Semi-strict | Requires justification to proceed with incomplete criteria |
| **SIL 3-4** | Strict Gatekeeper | **BLOCKS** phase transitions until all mandatory criteria satisfied |

### 14.4 Phase Gates Managed by COD

COD manages 9 phase gates corresponding to the EN 50128 lifecycle phases that have defined completion criteria (Phases 1–7, 8–10; Phase 0 is initialization and Verification is a continuous cross-cutting activity):

1. **Planning Gate** - Verify SQAP, SQAVR, SCMP, SVP, SVaP before requirements
2. **Requirements Gate** - Verify Software Requirements Specification, traceability, hazard analysis, user approval before design
3. **Design Gate** - Verify Software Architecture Specification, Software Design Specification, traceability, complexity limits before implementation
4. **Implementation Gate** - Verify MISRA C compliance, coverage, unit tests before integration
5. **Integration Gate** - Verify integration tests, interfaces, baseline before validation
6. **Validation Gate** - Verify validation tests, customer acceptance, validator independence before assessment
7. **Assessment Gate** - Verify assessment report, safety case, assessor independence before deployment
8. **Deployment Gate** - Verify deployment records, deployment verification report
9. **Maintenance Gate** - Verify maintenance plan, change records

### 14.5 Background Monitoring

COD operates as a **background orchestrator** that:
- Intercepts agent invocations to validate lifecycle context
- Blocks out-of-sequence activities (SIL 3-4) or warns (SIL 0-2)
- Requires user approval for requirement activities (all SIL levels)
- Tracks deliverables in `LIFECYCLE_STATE.md`
- Enforces phase gates with SIL-dependent authority
- Preserves independence of Validator and Assessor roles (does NOT control them)

### 14.6 LIFECYCLE_STATE.md

COD maintains project state in `LIFECYCLE_STATE.md` (project root), which tracks:
- Current phase and status
- Deliverable completion status
- Phase gate pass/fail status
- Traceability status (traceability completeness)
- Agent activity log
- Approval history (requirements, reviews, baselines)
- Change requests and resolution

**Location**: Project root (e.g., `examples/train_door_control/LIFECYCLE_STATE.md`)

### 14.7 User Approval Workflow

COD enforces **mandatory user approval** for all requirement establishment and modification activities:

1. PM begins requirements phase activities on behalf of REQ
2. COD intercepts the activity
3. COD prompts user: "Requirement activity requires explicit approval. Approve? [Y/N]"
4. If approved: COD allows REQ activities to proceed and logs approval in LIFECYCLE_STATE.md
5. If denied: COD blocks the requirement phase activity

**Rationale**: Requirements are the foundation of safety-critical systems. Explicit user approval ensures conscious decision-making and accountability.

### 14.8 Independence Preservation

COD coordinates with but does NOT control independent roles:

- **Validator (SIL 3-4)**: COD verifies validator independence and does NOT report to PM, but COD does not direct validation activities
- **Assessor (SIL 3-4)**: COD verifies assessor complete independence, but COD does not control assessment process
- **Verifier (SIL 3-4)**: COD verifies verifier independence from implementer, but COD does not direct verification activities

COD's role is **lifecycle compliance enforcement**, not **technical oversight** of independent roles.

---

## 15. Lifecycle Workflow Examples

### 15.1 Example: Complete SIL 3 Project Workflow

```bash
# Phase 0: Initialization (COD)
@cod plan --sil 3 --project train_door_control
# Initialize lifecycle tracking, create LIFECYCLE_STATE.md
# COD monitors all subsequent activities

# Generate system-level documents
@cod generate-system
# Prompts for selection from 5 typical railway systems (TYPICAL-SYSTEMS.md)
# Generates: System-Requirements-Specification.md, System-Architecture.md,
#            Hazard-Log.md, RAMS-Requirements.md in docs/system/

# Phase 1: Planning
@pm execute-phase 1
# PM coordinates: project planning, CCB setup, SQAP, SCMP, SVP, SVaP
# Internally: QUA establishes quality processes, CM establishes version control

# COD Phase Gate Check
@cod gate-check planning
# COD verifies all planning documents approved before allowing requirements phase

# Phase 2: Requirements
@pm execute-phase 2
# PM coordinates: REQ creates SRS from system-level inputs
# Internally: SAF performs hazard analysis, QUA checks template compliance,
#             VER verifies requirements, CM baselines requirements
# USER APPROVAL required before REQ activities proceed

# COD Phase Gate Check
@cod gate-check requirements
# COD verifies SRS complete, traceability complete, hazard analysis done, user approval obtained
# COD verifies QA template compliance check performed (MANDATORY SIL 3-4)

# Phase 3: Architecture & Design
@pm execute-phase 3
# PM coordinates: DES creates SAS, SDS, interface specs
# Internally: SAF performs FMEA/FTA, QUA checks template compliance,
#             VER verifies design, CM baselines design

# COD Phase Gate Check
@cod gate-check design
# COD verifies design complete, traceability to requirements, complexity limits defined
# COD verifies QA template compliance check performed (MANDATORY SIL 3-4)

# Phase 4: Component Design
@pm execute-phase 4
# PM coordinates: DES produces Software Component Design Specifications, Test Specifications
# Internally: QUA checks template compliance, VER verifies component designs, CM baselines

# COD Phase Gate Check
@cod gate-check component-design
# COD verifies component designs complete, test specifications ready

# Phase 5: Implementation & Unit Testing
@pm execute-phase 5
# PM coordinates: IMP implements C code (MISRA C:2012), TST writes and executes unit tests
# Internally: QUA performs code review (MISRA C compliance, complexity ≤10),
#             VER runs static analysis, CM baselines code
# COD independently coordinates: VMGR reviews and approves verification (SIL 3-4)

# COD Phase Gate Check
@cod gate-check implementation-testing
# COD verifies MISRA C compliance, coverage met (100% for SIL 3), complexity ≤10
# COD verifies QA code review performed (MANDATORY all SILs)

# Phase 6: Integration
@pm execute-phase 6
# PM coordinates: INT integrates components, TST executes integration tests
# Internally: QUA reviews integration test report, VER verifies integration,
#             CM establishes integration baseline

# COD Phase Gate Check
@cod gate-check integration
# COD verifies all integration tests pass, interfaces tested, baseline established
# COD verifies QA integration test review performed (MANDATORY SIL 3-4)

# Phase 7: Validation
# COD coordinates VAL directly (independence requirement — VAL does not report to PM)
@cod gate-check validation
# COD verifies all tests pass, customer acceptance, validator independence
# COD verifies QA validation review performed (MANDATORY SIL 3-4)

# Phase 8: Assessment (mandatory SIL 1-4 per §6.4.1.1; SIL 0 exempt per §6.4.1.2)
# Independent assessor reviews all lifecycle artifacts and issues approval certificate
@cod gate-check assessment
# COD verifies assessment complete, assessor independence, deployment authorization

# Phase 9: Deployment
@pm execute-phase 9
# PM coordinates: CM establishes final baseline, deployment package prepared

# COD Status Check (anytime)
@cod status
# View current phase, progress, deliverable status, gate compliance
```

### 15.2 Example: Quick Prototyping (SIL 0-1)

```bash
# Simplified workflow for lower SIL levels
@cod plan --sil 0 --project prototype  # Optional for SIL 0-1 (advisory mode)
@pm execute-phase 2  # Requirements (no user approval gate for SIL 0-1)
@pm execute-phase 3  # Basic design
@pm execute-phase 5  # Implement and test (80% coverage)
@pm execute-phase 6  # Integration
@cod gate-check validation  # COD provides warnings only, does not block transitions
```

### 15.3 Example: Iterative Development (SIL 2)

```bash
# Initial project setup
@cod plan --sil 2 --project iterative_system
@cod generate-system

# Iteration planning
@pm execute-phase 1  # Plan iteration, coordinate team, establish baselines

# Development cycle
@pm execute-phase 2  # Refine requirements for iteration (user approval required)
@cod gate-check requirements  # Semi-strict: requires justification if incomplete
@pm execute-phase 3  # Design iteration features
@cod gate-check design  # Semi-strict mode
@pm execute-phase 5  # Implement with MISRA C:2012, unit test (100% branch - mandatory SIL 2)
@pm execute-phase 6  # Integration testing
@cod gate-check implementation-testing  # Semi-strict: checks MISRA C, coverage

# Iteration completion
@cod gate-check integration
@pm execute-phase 9  # Merge to main, tag baseline
@cod status  # Check overall progress and compliance
```

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

| Phase | Mandatory Documents |
|-------|---------------------|
| Planning | SQAP, SCMP, SVP, SVaP |
| Requirements | Software Requirements Specification, traceability, Hazard Log |
| Design | Software Architecture Specification, Software Design Specification, ICD |
| Implementation | Source Code, Unit Tests, Coverage Report |
| Integration | Integration Test Report |
| Validation | Validation Report, UAT Results |
| Verification | Verification Report, Evidence Package |
| Assessment | Assessment Report, Safety Case |

### 18.2 Document Templates

Templates available in:
- `docs/templates/` - Generic templates
- `.opencode/skills/en50128-documentation/` - EN 50128 specific templates

---

## 19. Tool Qualification

### 19.1 Tool Categories (EN 50128 Section 6.7)

**T1**: Tools generating code → Requires qualification
**T2**: Tools supporting testing → May require qualification
**T3**: Development tools → Typically no qualification required

### 19.2 Tools Used in This Workspace

| Tool | Category | Qualification Required | Status |
|------|----------|------------------------|--------|
| GCC | T1 | Yes (SIL 3-4) | Industry accepted |
| Unity | T2 | Recommended | Open source |
| Cppcheck | T3 | No | - |
| PC-lint Plus | T3 | No | - |
| gcov/lcov | T2 | Recommended | Industry accepted |

---

## 20. Configuration Management

### 20.1 Configuration Management Agent

**Agent:** Configuration Manager (CM) - EN 50128 Section 6.6, Table A.9

**CRITICAL:** Configuration Management is **MANDATORY for ALL SIL levels (0, 1, 2, 3, 4)**

### 20.2 Version Control

All artifacts SHALL be under version control:
- Source code (Git)
- Requirements documents (Git)
- Design documents (Git)
- Test artifacts (Git)
- All deliverables (Git)

**Configuration Manager Responsibilities:**
- Maintain SCMP (Software Configuration Management Plan)
- Enforce version control practices
- Manage configuration items
- Process change requests

### 20.3 Baseline Management

Baselines SHALL be established at:
- Requirements freeze → Requirements Baseline
- Design freeze → Design Baseline
- Code freeze → Implementation Baseline
- Integration complete → Integration Baseline
- Release → Release Baseline

**Each baseline requires:**
- Configuration Manager approval
- Formal baseline identification
- Baseline documentation
- Configuration audit (PCA/FCA for releases)

### 20.4 Change Management

All changes SHALL go through formal change control:
1. Change request submitted
2. Impact assessment performed (by CM)
3. Change Control Board (CCB) review
4. Project Manager approval
5. Traceability updated (mandatory SIL 3-4)
6. Implementation performed
7. Verification performed
8. Regression testing performed
9. Change closed by Configuration Manager

**Change Control Board (CCB):**
- Led by Project Manager (PM)
- Configuration Manager (CM) - secretary
- Technical representatives (DES, IMP, TST, VER)
- Safety Engineer (SAF) - for safety-critical changes

### 20.5 Traceability Management

**Configuration Manager SHALL maintain traceability matrices:**
- Requirements → Design
- Design → Code
- Requirements → Tests
- All bidirectional links

**Mandatory for SIL 3-4** (Table A.9, Technique 7 - Traceability)

### 20.6 Configuration Management Activities

The Configuration Manager (CM) is responsible for:
- Version control operations (Git)
- Baseline creation and management
- Change request processing
- Traceability matrix updates
- Configuration audits (PCA/FCA)

### 20.7 EN 50128 Techniques/Measures (Table A.9 - CM subset)

| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Reference |
|-----------|-------|---------|---------|-----------|
| Software Configuration Management | **M** | **M** | **M** | D.48 |
| Traceability | R | HR | **M** | D.58 |
| Data Recording and Analysis | HR | HR | **M** | D.12 |

**Key:** M = Mandatory, HR = Highly Recommended, R = Recommended

**CRITICAL:** SCM is MANDATORY for ALL SIL levels.

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
- `.opencode/agents/` - Agent definition files (cod.md, pm.md, req.md, des.md, imp.md, tst.md, int.md, ver.md, val.md, saf.md, qua.md, cm.md, vmgr.md)
- `.opencode/skills/en50128-lifecycle-coordination/` - COD patterns and workflows
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

---

**Document Status**: Approved  
**Next Review**: [Date]  
**Approval**: [Signature]

---

## 24. EN 50128 Deliverable Reference

**Standard**: EN 50128:2011 Railway Software  
**Purpose**: Complete mapping of lifecycle deliverables with exact names from EN 50128 Section 7

### Important Note on Terminology

EN 50128 uses **EXACT** document names in Section 7 output specifications. All platform phase definitions, agent commands, and QUA checkers MUST use these exact names.

**Naming Convention**:
- EN 50128 uses **singular or plural** based on the section definition
- Example: "Software Interface Specification**s**" (plural - 7.3.3 item 3)
- Example: "Software Architecture Specification" (singular - 7.3.3 item 1)

### Annex C Table C.1: Complete Document Inventory

**EN 50128 Reference**: Annex C (informative) Table C.1 — Documents Control Summary

Annex C lists **46 numbered documents** across all lifecycle phases. The table below is the authoritative reference for document names, ownership, and review responsibility. SIL recommendation levels apply to the existence/use of each document.

**Legend** (from Table A.1 SIL columns):
- **M** = Mandatory
- **HR** = Highly Recommended (justification required if not used)
- **R** = Recommended
- **-** = No recommendation

**NOTE**: Annex C Table C.1 is *informative*, not normative. The normative SIL requirements for individual documents are in the corresponding Section 7.x clauses. The SIL columns in the table below are from Table A.1.

---

#### Planning Phase (Annex C items 1–5)

| # | Exact Document Name (EN 50128) | Written by | 1st Check | 2nd Check | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 | File Path |
|---|-------------------------------|-----------|-----------|-----------|-------|-------|-------|-------|-------|-----------|
| 1 | **Software Quality Assurance Plan** | VER (§6.5.4.3) | VER | VAL | HR | HR | HR | HR | HR | `docs/plans/SQAP.md` |
| 2 | **Software Quality Assurance Verification Report** | VER | — | VAL | HR | HR | HR | HR | HR | `docs/reports/Software-Quality-Assurance-Verification-Report.md` |
| 3 | **Software Configuration Management Plan** | CM (see B.10) | VER | VAL | HR | HR | HR | HR | HR | `docs/plans/SCMP.md` |
| 4 | **Software Verification Plan** | VER | — | VAL | HR | HR | HR | HR | HR | `docs/plans/SVP.md` |
| 5 | **Software Validation Plan** | VAL | VER | — | HR | HR | HR | HR | HR | `docs/plans/SVaP.md` |

**Key corrections from prior version**:
- Item 1 (SQAP) is written by **VER** under §6.5.4.3 ("under the responsibility of the Verifier"); Annex C "Written by" column is blank for item 1
- Item 2 (**Software Quality Assurance Verification Report**) was missing — now added
- Item 4 (SVP) is written by **VER**, not PM
- Item 5 (SVaP) is written by **VAL**, not PM
- All planning documents are **HR** (Highly Recommended) for ALL SIL levels — NOT mandatory

**IMPORTANT — Normative "shall" requirements override Annex C informative SIL columns**: The planning documents above carry "HR" in Annex C (Table C.1, which is *informative*). However, the following normative clauses use "shall" and impose binding obligations regardless of SIL level:
- **§5.3.2.4** — "A Software Development Plan shall be produced" (encompasses SVP, SVaP, SQAP, SCMP)
- **§6.2.4.2** — "A Software Verification Plan shall be produced" (item 4, SVP)
- **§6.3.4.2** — "A Software Validation Plan shall be produced" (item 5, SVaP)
- **§6.5.4.3** — "A Software Quality Assurance Plan shall be written, under the responsibility of the Verifier" (item 1, SQAP)
- **§6.6.4.1** — "A Software Configuration Management Plan shall be produced" (item 3, SCMP)

Agents (COD, PM, QUA) SHALL enforce production of all five planning documents for all SIL levels on the basis of these normative clauses.

---

#### Software Requirements Phase (Annex C items 6–8)

| # | Exact Document Name (EN 50128) | Written by | 1st Check | 2nd Check | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 | File Path |
|---|-------------------------------|-----------|-----------|-----------|-------|-------|-------|-------|-------|-----------|
| 6 | **Software Requirements Specification** | REQ | VER | VAL | HR | HR | HR | HR | HR | `docs/Software-Requirements-Specification.md` |
| 7 | **Overall Software Test Specification** | TST | VER | VAL | HR | HR | HR | HR | HR | `docs/test/Overall-Software-Test-Specification.md` |
| 8 | **Software Requirements Verification Report** | VER | — | VAL | HR | HR | HR | HR | HR | `docs/reports/Software-Requirements-Verification-Report.md` |

---

#### Architecture and Design Phase (Annex C items 9–14)

| # | Exact Document Name (EN 50128) | Written by | 1st Check | 2nd Check | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 | File Path |
|---|-------------------------------|-----------|-----------|-----------|-------|-------|-------|-------|-------|-----------|
| 9 | **Software Architecture Specification** | DES | VER | VAL | HR | HR | HR | HR | HR | `docs/Software-Architecture-Specification.md` |
| 10 | **Software Design Specification** | DES | VER | VAL | HR | HR | HR | HR | HR | `docs/Software-Design-Specification.md` |
| 11 | **Software Interface Specifications** | DES | VER | VAL | HR | HR | HR | HR | HR | `docs/Software-Interface-Specifications.md` |
| 12 | **Software Integration Test Specification** | INT | VER | VAL | HR | HR | HR | HR | HR | `docs/test/Software-Integration-Test-Specification.md` |
| 13 | **Software/Hardware Integration Test Specification** | INT | VER | VAL | HR | HR | HR | HR | HR | `docs/test/Software-Hardware-Integration-Test-Specification.md` |
| 14 | **Software Architecture and Design Verification Report** | VER | — | VAL | HR | HR | HR | HR | HR | `docs/reports/Software-Architecture-and-Design-Verification-Report.md` |

**Key**: Item 11 is **plural** — "Software Interface Specification**s**"

---

#### Component Design Phase (Annex C items 15–16)

| # | Exact Document Name (EN 50128) | Written by | 1st Check | 2nd Check | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 | File Path |
|---|-------------------------------|-----------|-----------|-----------|-------|-------|-------|-------|-------|-----------|
| 15 | **Software Component Design Specification** | DES | VER | VAL | R | HR | HR | HR | HR | `docs/Software-Component-Design-Specification.md` |
| 16 | **Software Component Test Specification** | TST | VER | VAL | R | HR | HR | HR | HR | `docs/test/Software-Component-Test-Specification.md` |

---

#### Component Implementation and Testing Phase (Annex C items 17–20)

| # | Exact Document Name (EN 50128) | Written by | 1st Check | 2nd Check | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 | File Path |
|---|-------------------------------|-----------|-----------|-----------|-------|-------|-------|-------|-------|-----------|
| 17 | **Software Component Design Verification Report** | VER | — | — | R | HR | HR | HR | HR | `docs/reports/Software-Component-Design-Verification-Report.md` |
| 18 | **Software Source Code and supporting documentation** | IMP | VER | VAL | HR | HR | HR | HR | HR | `src/` + supporting docs |
| 19 | **Software Source Code Verification Report** | VER | — | VAL | HR | HR | HR | HR | HR | `docs/reports/Software-Source-Code-Verification-Report.md` |
| 20 | **Software Component Test Report** | TST | VER | VAL | R | HR | HR | HR | HR | `docs/reports/Software-Component-Test-Report.md` |

**Key corrections**:
- Item 17 (Software Component Design Verification Report) belongs here per Annex C — it is the verification of the component design, produced after component design is implemented
- Item 18: lowercase "and supporting documentation" (not "Supporting Documentation")
- Item 19: Software Source Code **Verification** Report (not Component Test Report)
- **Item 20 (Software Component Test Report)** is a Phase 5 output per §7.5.3 and Annex C Table C.1 — not Phase 6

---

#### Integration Phase (Annex C items 21–22)

| # | Exact Document Name (EN 50128) | Written by | 1st Check | 2nd Check | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 | File Path |
|---|-------------------------------|-----------|-----------|-----------|-------|-------|-------|-------|-------|-----------|
| 21 | **Software Integration Test Report** | INT | VER | VAL | HR | HR | HR | HR | HR | `docs/reports/Software-Integration-Test-Report.md` |
| 22 | **Software/Hardware Integration Test Report** | INT | VER | VAL | HR | HR | HR | HR | HR | `docs/reports/Software-Hardware-Integration-Test-Report.md` |

**Key**: Item 20 (Software Component Test Report) is a **Phase 5 deliverable** per §7.5.3 and Annex C Table C.1 — produced during Component Implementation and Testing, consumed as input to Phase 6.

---

#### Overall Software Testing / Final Validation Phase (Annex C items 23–26)

| # | Exact Document Name (EN 50128) | Written by | 1st Check | 2nd Check | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 | File Path |
|---|-------------------------------|-----------|-----------|-----------|-------|-------|-------|-------|-------|-----------|
| 23 | **Software Integration Verification Report** | VER | — | — | HR | HR | HR | HR | HR | `docs/reports/Software-Integration-Verification-Report.md` |
| 24 | **Overall Software Test Report** | TST | VER | VAL | HR | HR | HR | HR | HR | `docs/reports/Overall-Software-Test-Report.md` |
| 25 | **Software Validation Report** | VAL | VER | — | HR | HR | HR | HR | HR | `docs/reports/Software-Validation-Report.md` |
| 26 | **Tools Validation Report** | (see note) | VER | — | R | HR | HR | HR | HR | `docs/reports/Tools-Validation-Report.md` |

**Key corrections**:
- Item 23 (**Software Integration Verification Report**) is in the **Overall software testing / Final validation** phase per Annex C — not in Integration
- Item 26 (**Tools Validation Report**) was missing from prior version — now added (HR for SIL 1+)
- Item 25: Written by **VAL**, 1st check by VER
- **Release Note** (§7.7.4.12): A normative output of §7.7 but has **no Annex C item number**. It is not "item 27". The file `docs/Release-Note.md` should be produced at validation phase as a §7.7.4.12 normative requirement.

---

#### Systems Configured by Application Data/Algorithms (Annex C items 28–35)

These items apply only to **generic software platforms** (Section 8) — not to bespoke application software. They are out of scope for standard application development projects.

| # | Document Name | Written by | SIL 0 | SIL 1+ | Notes |
|---|--------------|-----------|-------|--------|-------|
| 28 | Application Requirements Specification | REQ or DES | HR | HR | Section 8 only |
| 29 | Application Preparation Plan | REQ or DES | HR | HR | Section 8 only; see NOTE 2 |
| 30 | Application Test Specification | TST | HR | HR | Section 8 only; see NOTE 2 |
| 31 | Application Architecture and Design | DES | HR | HR | Section 8 only; see NOTE 2 |
| 32 | Application Preparation Verification Report | VER | HR | HR | Section 8 only |
| 33 | Application Test Report | TST | HR | HR | Section 8 only |
| 34 | Source Code of Application Data/Algorithms | DES | HR | HR | Section 8 only |
| 35 | Application Data/Algorithms Verification Report | VER | HR | HR | Section 8 only |

---

#### Software Deployment Phase (Annex C items 36–40)

**This phase was absent from the prior lifecycle definition. It is now added.**

| # | Exact Document Name (EN 50128) | Written by | 1st Check | 2nd Check | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 | File Path |
|---|-------------------------------|-----------|-----------|-----------|-------|-------|-------|-------|-------|-----------|
| 36 | **Software Release and Deployment Plan** | PM / CM | VER | VAL | R | HR | HR | HR | HR | `docs/plans/Software-Release-and-Deployment-Plan.md` |
| 37 | **Software Deployment Manual** | PM / DES | VER | VAL | R | HR | HR | HR | HR | `docs/Software-Deployment-Manual.md` |
| 38 | **Release Notes** | PM / DES | VER | VAL | HR | HR | HR | HR | HR | `docs/Release-Notes.md` |
| 39 | **Deployment Records** | CM | VER | VAL | R | HR | HR | HR | HR | `docs/reports/Deployment-Records.md` |
| 40 | **Deployment Verification Report** | VER | — | — | R | HR | HR | HR | HR | `docs/reports/Deployment-Verification-Report.md` |

**Key**: Item 38 is **"Release Notes"** (plural) — this is the deployment release notes document distinct from the validation "Release Note" (singular, §7.7.4.12 normative, no Annex C number)

---

#### Software Maintenance Phase (Annex C items 41–44)

**This phase was absent from the prior lifecycle definition. It is now added.**

| # | Exact Document Name (EN 50128) | Written by | 1st Check | 2nd Check | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 | File Path |
|---|-------------------------------|-----------|-----------|-----------|-------|-------|-------|-------|-------|-----------|
| 41 | **Software Maintenance Plan** | (see note) | VER | VAL | R | HR | HR | HR | HR | `docs/plans/Software-Maintenance-Plan.md` |
| 42 | **Software Change Records** | (see note) | VER | VAL | HR | HR | HR | HR | HR | `docs/reports/Software-Change-Records.md` |
| 43 | **Software Maintenance Records** | (see note) | VER | VAL | R | HR | HR | HR | HR | `docs/reports/Software-Maintenance-Records.md` |
| 44 | **Software Maintenance Verification Report** | VER | — | VAL | R | HR | HR | HR | HR | `docs/reports/Software-Maintenance-Verification-Report.md` |

**Note**: Annex C item 42 shows "Software Chang Records" — this is a typo in the standard; the correct name from Section 9.2.4 is **"Software Change Records"**.

---

#### Software Assessment Phase (Annex C items 45–46)

| # | Exact Document Name (EN 50128) | Written by | 1st Check | 2nd Check | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 | File Path |
|---|-------------------------------|-----------|-----------|-----------|-------|-------|-------|-------|-------|-----------|
| 45 | **Software Assessment Plan** | ASR (Assessor) | VER | — | R | HR | HR | HR | HR | `docs/plans/Software-Assessment-Plan.md` |
| 46 | **Software Assessment Report** | ASR (Assessor) | VER | — | R | HR | HR | HR | HR | `docs/reports/Software-Assessment-Report.md` |

**Key correction**: Both items 45 and 46 are written by **ASR** (Assessor), NOT by PM. The 1st check is by VER. Assessment is **mandatory for SIL 1–4** per §6.4.1.1 and §5.1.2.4 — Annex C "HR" does not override normative "shall" clauses.

---

### Document Naming Conventions

**File Naming Strategy**

Use exact EN 50128 name with hyphens replacing spaces:
- `Software-Architecture-Specification.md` (recommended)
- `Software-Interface-Specifications.md` (plural — matches standard!)
- `Software-Hardware-Integration-Test-Report.md` (use hyphen in filename for "/")
- `SAS.md`, `SDS.md` — abbreviations NOT recommended

**Document ID Convention**

Format: `DOC-<TYPE>-YYYY-NNN`

| EN 50128 Document Name | Abbreviation | Example ID |
|------------------------|--------------|------------|
| Software Quality Assurance Plan | SQAP | DOC-SQAP-2026-001 |
| Software Quality Assurance Verification Report | SQAVR | DOC-SQAVR-2026-001 |
| Software Configuration Management Plan | SCMP | DOC-SCMP-2026-001 |
| Software Verification Plan | SVP | DOC-SVP-2026-001 |
| Software Validation Plan | SVaP | DOC-SVaP-2026-001 |
| Software Requirements Specification | SRS | DOC-SRS-2026-001 |
| Overall Software Test Specification | OTSTSPEC | DOC-OTSTSPEC-2026-001 |
| Software Requirements Verification Report | REQVER | DOC-REQVER-2026-001 |
| Software Architecture Specification | SAS | DOC-SAS-2026-001 |
| Software Design Specification | SDS | DOC-SDS-2026-001 |
| Software Interface Specifications | INTERFACES | DOC-INTERFACES-2026-001 |
| Software Integration Test Specification | INTTESTSPEC | DOC-INTTESTSPEC-2026-001 |
| Software/Hardware Integration Test Specification | HWINTTESTSPEC | DOC-HWINTTESTSPEC-2026-001 |
| Software Architecture and Design Verification Report | ARCHDESIGNVER | DOC-ARCHDESIGNVER-2026-001 |
| Software Component Design Specification | COMPDESIGN | DOC-COMPDESIGN-2026-001 |
| Software Component Test Specification | COMPTESTSPEC | DOC-COMPTESTSPEC-2026-001 |
| Software Component Design Verification Report | COMPDESIGNVER | DOC-COMPDESIGNVER-2026-001 |
| Software Source Code and supporting documentation | SOURCECODE | DOC-SOURCECODE-2026-001 |
| Software Component Test Report | COMPTESTRPT | DOC-COMPTESTRPT-2026-001 |
| Software Source Code Verification Report | SOURCECODEVER | DOC-SOURCECODEVER-2026-001 |
| Software Integration Test Report | INTTESTRPT | DOC-INTTESTRPT-2026-001 |
| Software/Hardware Integration Test Report | HWINTTESTRPT | DOC-HWINTTESTRPT-2026-001 |
| Software Integration Verification Report | INTVER | DOC-INTVER-2026-001 |
| Overall Software Test Report | OVERALLTESTRPT | DOC-OVERALLTESTRPT-2026-001 |
| Software Validation Report | VALRPT | DOC-VALRPT-2026-001 |
| Tools Validation Report | TOOLSVALRPT | DOC-TOOLSVALRPT-2026-001 |
| Release Note (§7.7.4.12 normative, no Annex C #) | RELEASENOTE | DOC-RELEASENOTE-2026-001 |
| Software Release and Deployment Plan | DEPLOYPLAN | DOC-DEPLOYPLAN-2026-001 |
| Software Deployment Manual | DEPLOYMAN | DOC-DEPLOYMAN-2026-001 |
| Release Notes | RELEASENOTES | DOC-RELEASENOTES-2026-001 |
| Deployment Records | DEPLOYREC | DOC-DEPLOYREC-2026-001 |
| Deployment Verification Report | DEPLOYVER | DOC-DEPLOYVER-2026-001 |
| Software Maintenance Plan | MAINTPLAN | DOC-MAINTPLAN-2026-001 |
| Software Change Records | CHANGEREC | DOC-CHANGEREC-2026-001 |
| Software Maintenance Records | MAINTREC | DOC-MAINTREC-2026-001 |
| Software Maintenance Verification Report | MAINTVER | DOC-MAINTVER-2026-001 |
| Software Assessment Plan | ASSESSPLAN | DOC-ASSESSPLAN-2026-001 |
| Software Assessment Report | ASSESSRPT | DOC-ASSESSRPT-2026-001 |

### Document Type Mapping (for QUA checkers)

| EN 50128 Document Name | doc_type (YAML) | QUA Checker File |
|------------------------|-----------------|------------------|
| Software Quality Assurance Plan | `SQAP` | `sqap-checker.yaml` |
| Software Quality Assurance Verification Report | `SQAVR` | `sqavr-checker.yaml` |
| Software Requirements Specification | `SRS` | `srs-checker.yaml` |
| Overall Software Test Specification | `Overall-Test-Spec` | `overall-test-spec-checker.yaml` |
| Software Architecture Specification | `SAS` | `sas-checker.yaml` |
| Software Design Specification | `SDS` | `sds-checker.yaml` |
| Software Interface Specifications | `Interface-Specs` | `interface-specs-checker.yaml` |
| Software Integration Test Specification | `Integration-Test-Spec` | `integration-test-spec-checker.yaml` |
| Software/Hardware Integration Test Specification | `HW-Integration-Test-Spec` | `hw-integration-test-spec-checker.yaml` |
| Software Component Design Specification | `Component-Design-Spec` | `component-design-spec-checker.yaml` |
| Software Component Test Specification | `Component-Test-Spec` | `component-test-spec-checker.yaml` |

### Compliance Verification Checklist

- [ ] All phase definitions use exact EN 50128 document names from Annex C Table C.1
- [ ] All file paths match EN 50128 naming (with hyphens for spaces)
- [ ] All QUA checkers match exact document names (with correct singular/plural)
- [ ] All agent commands reference exact EN 50128 deliverables
- [ ] Document IDs follow DOC-<TYPE>-YYYY-NNN convention
- [ ] V-Model alignment: Test Specs in design phases, Test Reports in execution phases
- [ ] Verification Reports follow EN 50128 naming conventions
- [ ] "Software/Hardware" uses forward slash "/" not hyphen
- [ ] "Software Interface Specifications" is **plural**
- [ ] "Release Note" (§7.7.4.12 normative, no Annex C number) is distinct from "Release Notes" (item 38, plural, deployment phase)
- [ ] Document #2 (Software Quality Assurance Verification Report) is included
- [ ] Document #26 (Tools Validation Report) is included
- [ ] Deployment phase documents (#36–40) are included
- [ ] Maintenance phase documents (#41–44) are included
- [ ] Assessment phase documents (#45–46) authored by Assessor (ASR), not PM
- [ ] SVP (item 4) written by VER, SVaP (item 5) written by VAL

---

## 25. Phase-to-Document Complete Reference

**Standard**: EN 50128:2011 Railway Software  
**Purpose**: Complete reference of all lifecycle phases and their deliverable documents, aligned to Annex C Table C.1 (46 numbered documents)

### Quick Reference Table

| Phase | Annex C Items | EN 50128 Section | Documents | Phase Definition File |
|-------|--------------|-----------------|-----------|----------------------|
| Phase 0: Initialization | — | Platform Extension | 1 document | N/A (COD internal) |
| Phase 1: Planning | 1–5 | 5, 6.5, 6.6 | 5 documents | N/A (manual setup) |
| Phase 2: Requirements | 6–8 | 7.2 | 3 documents | `phase-2-requirements.yaml` |
| Phase 3: Architecture & Design | 9–14 | 7.3 | 6 documents | `phase-3-architecture-design.yaml` |
| Phase 4: Component Design | 15–17 | 7.4 | 3 documents | `phase-4-component-design.yaml` |
| Phase 5: Implementation & Testing | 18–20 | 7.5 | 3 documents | `phase-5-implementation-testing.yaml` |
| Phase 6: Integration | 21–22 | 7.6 | 2 documents | `phase-6-integration.yaml` |
| Phase 7: Validation | 23–26 | 7.7 | 4 documents | `phase-7-validation.yaml` |
| Phase 8: Assessment | 45–46 | 6.4 | 2 documents | Mandatory SIL 1-4 (§6.4.1.1, §5.1.2.4); SIL 0 exempt |
| Phase 9: Deployment | 36–40 | 9.1 | 5 documents | Not yet created |
| Phase 10: Maintenance | 41–44 | 9.2 | 4 documents | Not yet created |
| (Section 8 only) | 28–35 | 8 | 8 documents | N/A — generic software platforms only |

**Total Annex C Documents**: 46 (items 1–46)  
**Applicable to bespoke application software**: 37 (items 1–26 + 36–46; items 28–35 are Section 8 generic platform only; Release Note is a normative §7.7.4.12 requirement with no Annex C number)

### Phase 0: Initialization (Platform Extension)

**Purpose**: Initialize lifecycle tracking and project structure  
**Owner**: Lifecycle Coordinator (COD)  
**Command**: `@cod plan --sil [0-4] --project [name]`

| # | Document Name | File Path | Owner | Notes |
|---|---------------|-----------|-------|-------|
| — | **LIFECYCLE_STATE.md** | `LIFECYCLE_STATE.md` | COD | Platform extension — not an EN 50128 document |

### Phase 1: Planning (EN 50128 Sections 5, 6.5, 6.6) — Annex C items 1–5

**Purpose**: Establish project organization, quality assurance, and configuration management  
**Primary Agents**: QUA, CM, VER, VAL  
**EN 50128 Reference**: Section 5.3.2.5 - "All activities during a phase SHALL be defined and planned"

| Annex C # | Document Name | File Path | Written by | EN 50128 Ref | SIL 0 | SIL 1-4 |
|-----------|--------------|-----------|-----------|--------------|-------|---------|
| 1 | **Software Quality Assurance Plan** | `docs/plans/SQAP.md` | VER (§6.5.4.3) | 6.5.4.3 | HR | HR |
| 2 | **Software Quality Assurance Verification Report** | `docs/reports/Software-Quality-Assurance-Verification-Report.md` | VER | 6.5 | HR | HR |
| 3 | **Software Configuration Management Plan** | `docs/plans/SCMP.md` | CM | 6.6.4.1 | HR | HR |
| 4 | **Software Verification Plan** | `docs/plans/SVP.md` | VER | 6.2.4.2 | HR | HR |
| 5 | **Software Validation Plan** | `docs/plans/SVaP.md` | VAL | 6.3.4.2 | HR | HR |

**Key corrections from prior version**:
- Item 1 (SQAP) is written by **VER** per §6.5.4.3 (not QUA)
- Item 2 (Software Quality Assurance Verification Report) was **missing** — now added
- Item 4 (SVP) is written by **VER** (not PM)
- Item 5 (SVaP) is written by **VAL** (not PM)
- All planning documents are **HR** for all SIL levels — NOT mandatory in Annex C

**Phase Gate**: `@cod gate-check planning` (MANDATORY all SIL levels)

### Phase 2: Requirements (EN 50128 Section 7.2) — Annex C items 6–8

**Purpose**: Define complete, unambiguous software requirements  
**Primary Agent**: REQ  
**Supporting Agents**: SAF, QUA, VER

| Annex C # | Document Name | File Path | Written by | EN 50128 Clause | SIL 0 | SIL 1-4 |
|-----------|--------------|-----------|-----------|-----------------|-------|---------|
| 6 | **Software Requirements Specification** | `docs/Software-Requirements-Specification.md` | REQ | 7.2.4.1 | HR | HR |
| 7 | **Overall Software Test Specification** | `docs/test/Overall-Software-Test-Specification.md` | TST | 7.2.4.16 | HR | HR |
| 8 | **Software Requirements Verification Report** | `docs/reports/Software-Requirements-Verification-Report.md` | VER | 7.2.4.20 | HR | HR |

**Best Practice**: Hazard Log - `docs/Hazard-Log.md` - SAF (EN 50126 / EN 50129) — not an Annex C document

**Phase Gate**: `@cod gate-check requirements` (MANDATORY all SIL levels)

### Phase 3: Architecture & Design (EN 50128 Section 7.3) — Annex C items 9–14

**Purpose**: Define software architecture, design, and interfaces  
**Primary Agent**: DES  
**Supporting Agents**: SAF, QUA, INT, VER

| Annex C # | Document Name | File Path | Written by | EN 50128 Clause | SIL 0 | SIL 1-4 |
|-----------|--------------|-----------|-----------|-----------------|-------|---------|
| 9 | **Software Architecture Specification** | `docs/Software-Architecture-Specification.md` | DES | 7.3.4.1 | HR | HR |
| 10 | **Software Design Specification** | `docs/Software-Design-Specification.md` | DES | 7.3.4.20 | HR | HR |
| 11 | **Software Interface Specifications** | `docs/Software-Interface-Specifications.md` | DES | 7.3.4.18 | HR | HR |
| 12 | **Software Integration Test Specification** | `docs/test/Software-Integration-Test-Specification.md` | INT | 7.3.4.25 | HR | HR |
| 13 | **Software/Hardware Integration Test Specification** | `docs/test/Software-Hardware-Integration-Test-Specification.md` | INT | 7.3.4.29 | HR | HR |
| 14 | **Software Architecture and Design Verification Report** | `docs/reports/Software-Architecture-and-Design-Verification-Report.md` | VER | 7.3.4.38 | HR | HR |

**Important Naming Notes**:
- #11: **PLURAL** - "Software Interface Specification**s**"
- #13: Use forward slash **"/"** not hyphen - "Software/Hardware"
- #12 and #13: Test **Specifications** created in Phase 3, Test **Reports** created in Phase 6 (V-Model)

**Phase Gate**: `@cod gate-check architecture-design` (MANDATORY all SIL levels)

### Phase 4: Component Design (EN 50128 Section 7.4) — Annex C items 15–17

**Purpose**: Decompose design into components with detailed specifications  
**Primary Agents**: DES, TST  
**Supporting Agents**: QUA, VER

| Annex C # | Document Name | File Path | Written by | EN 50128 Clause | SIL 0 | SIL 1-4 |
|-----------|--------------|-----------|-----------|-----------------|-------|---------|
| 15 | **Software Component Design Specification** | `docs/Software-Component-Design-Specification.md` | DES | 7.4.4.1 | R | HR |
| 16 | **Software Component Test Specification** | `docs/test/Software-Component-Test-Specification.md` | TST | 7.4.4.7 | R | HR |
| 17 | **Software Component Design Verification Report** | `docs/reports/Software-Component-Design-Verification-Report.md` | VER | 7.4.4.11 | R | HR |

**Key correction**: Items 15–17 are only **R** (Recommended) for SIL 0, **HR** for SIL 1-4 — not mandatory.

**Phase Gate**: `@cod gate-check component-design` (MANDATORY all SIL levels)

### Phase 5: Implementation & Testing (EN 50128 Section 7.5) — Annex C items 18–20

**Purpose**: Implement source code and execute unit/component tests  
**Primary Agents**: IMP, TST  
**Supporting Agents**: QUA, VER

| Annex C # | Document Name | File Path | Written by | EN 50128 Clause | SIL 0 | SIL 1-4 |
|-----------|--------------|-----------|-----------|-----------------|-------|---------|
| 18 | **Software Source Code and supporting documentation** | `src/` + docs | IMP | 7.5.4.1 | HR | HR |
| 19 | **Software Source Code Verification Report** | `docs/reports/Software-Source-Code-Verification-Report.md` | VER | 7.5.4.8 | HR | HR |
| 20 | **Software Component Test Report** | `docs/reports/Software-Component-Test-Report.md` | TST | 7.5.4.5 | R | HR |

**Key Requirements**:
- MISRA C:2012 compliance (ZERO mandatory violations for SIL 2+)
- Static allocation only (no `malloc`/`free` for SIL 2+)
- Cyclomatic complexity ≤10 (SIL 3-4), ≤15 (SIL 2)
- Coverage: 100% statement/branch/MC/DC (SIL 3-4)
- **Item 20 (Software Component Test Report)** is a normative §7.5.3 output — per §7.5.4.5 "A Software Component Test Report shall be written, under the responsibility of the Tester"

**Phase Gate**: `@cod gate-check implementation-testing` (MANDATORY all SIL levels)

### Phase 6: Integration (EN 50128 Section 7.6) — Annex C items 21–22

**Purpose**: Integrate components and test software-hardware integration  
**Primary Agent**: INT  
**Supporting Agents**: TST, QUA, VER

| Annex C # | Document Name | File Path | Written by | EN 50128 Clause | SIL 0 | SIL 1-4 |
|-----------|--------------|-----------|-----------|-----------------|-------|---------|
| 21 | **Software Integration Test Report** | `docs/reports/Software-Integration-Test-Report.md` | INT | 7.6.4.3 | HR | HR |
| 22 | **Software/Hardware Integration Test Report** | `docs/reports/Software-Hardware-Integration-Test-Report.md` | INT | 7.6.4.7 | HR | HR |

**Note**: Item 20 (Software Component Test Report) is a **Phase 5 deliverable** per §7.5.3 — it is an input to Phase 6, not produced in Phase 6.

**V-Model Correspondence**:
- Software Integration Test Specification (Phase 3, item 12) → Software Integration Test Report (Phase 6, item 21)
- Software/Hardware Integration Test Specification (Phase 3, item 13) → Software/Hardware Integration Test Report (Phase 6, item 22)
- Software Component Test Specification (Phase 4, item 16) → Software Component Test Report (**Phase 5**, item 20)

**Phase Gate**: `@cod gate-check integration` (MANDATORY all SIL levels)

### Phase 7: Validation (EN 50128 Section 7.7) — Annex C items 23–26

**Purpose**: Overall software testing and validation for fitness of use  
**Primary Agents**: TST, VAL  
**Supporting Agents**: QUA, VER

| Annex C # | Document Name | File Path | Written by | EN 50128 Clause | SIL 0 | SIL 1-4 |
|-----------|--------------|-----------|-----------|-----------------|-------|---------|
| 23 | **Software Integration Verification Report** | `docs/reports/Software-Integration-Verification-Report.md` | VER | 7.7.4 | HR | HR |
| 24 | **Overall Software Test Report** | `docs/reports/Overall-Software-Test-Report.md` | TST | 7.7.4.1 | HR | HR |
| 25 | **Software Validation Report** | `docs/reports/Software-Validation-Report.md` | VAL | 7.7.4.6 | HR | HR |
| 26 | **Tools Validation Report** | `docs/reports/Tools-Validation-Report.md` | (project-specific) | 6.7 | R | HR |

**Additional normative outputs (no Annex C number)**:
- **Release Note** (`docs/Release-Note.md`) — written by DES/PM — required by §7.7.4.12; has no Annex C item number
- **Software Validation Verification Report** (`docs/reports/Software-Validation-Verification-Report.md`) — written by VER — required by §6.3.3; has no Annex C item number

**Key corrections from prior version**:
- Item 23 (**Software Integration Verification Report**) is in the **Validation** phase per Annex C — not in Integration
- Item 26 (**Tools Validation Report**) was **missing** — now added (HR for SIL 1-4, R for SIL 0)
- **Release Note** is a normative §7.7.4.12 output — it has **no Annex C item number**; prior versions incorrectly labelled it "item 27"

**V-Model Correspondence**:
- Overall Software Test Specification (Phase 2, item 7) → Overall Software Test Report (Phase 7, item 24)

**Phase Gate**: `@cod gate-check validation` (MANDATORY all SIL levels)

### Phase 8: Assessment (EN 50128 Section 6.4) — Annex C items 45–46

**Purpose**: Independent safety assessment  
**Primary Agent**: Assessor (ASR — must be independent)  
**Supporting Agents**: VER

**Note**: Per §6.4.1.1 ("The software shall be subjected to an independent assessment") and §5.1.2.4 ("An Assessor shall be appointed"), assessment is **mandatory for SIL 1–4**. SIL 0 is the only exemption (§6.4.1.2 — ISO 9001 certified organisations). Annex C shows "R" for SIL 0 and "HR" for SIL 1-4, but the underlying normative clauses §6.4.1.1 and §5.1.2.4 use "shall" for SIL 1–4 without qualification. COD enforces the Phase 8 gate for all SIL 1–4 projects.

| Annex C # | Document Name | File Path | Written by | EN 50128 Clause | SIL 0 | SIL 1-4 |
|-----------|--------------|-----------|-----------|-----------------|-------|---------|
| 45 | **Software Assessment Plan** | `docs/plans/Software-Assessment-Plan.md` | ASR | 6.4.4.4 | R | HR |
| 46 | **Software Assessment Report** | `docs/reports/Software-Assessment-Report.md` | ASR | 6.4.4.16 | R | HR |

**Key correction**: Both items written by **ASR** (Assessor), NOT PM. Assessor must be fully independent. Assessment is **mandatory for SIL 1–4** per §6.4.1.1 and §5.1.2.4 — Annex C "HR" does not override normative "shall" clauses.

**Additional normative output (no Annex C number)**:
- **Software Assessment Verification Report** (`docs/reports/Software-Assessment-Verification-Report.md`) — written by VER — required by §6.4.4.6; has no Annex C item number

**Phase Gate**: `@cod gate-check assessment` (MANDATORY for SIL 1–4; SIL 0 exempt per §6.4.1.2)

### Phase 9: Deployment (EN 50128 Section 9.1) — Annex C items 36–40

**Purpose**: Deploy software to operational environment  
**Primary Agents**: PM, CM, VER

**This phase was absent from the prior lifecycle definition and is now added per Annex C.**

| Annex C # | Document Name | File Path | Written by | EN 50128 Clause | SIL 0 | SIL 1-4 |
|-----------|--------------|-----------|-----------|-----------------|-------|---------|
| 36 | **Software Release and Deployment Plan** | `docs/plans/Software-Release-and-Deployment-Plan.md` | PM / CM | 9.1.4 | R | HR |
| 37 | **Software Deployment Manual** | `docs/Software-Deployment-Manual.md` | PM / DES | 9.1.4.6 | R | HR |
| 38 | **Release Notes** | `docs/Release-Notes.md` | PM / DES | 9.1.4.4 | HR | HR |
| 39 | **Deployment Records** | `docs/reports/Deployment-Records.md` | CM | 9.1.4.13 | R | HR |
| 40 | **Deployment Verification Report** | `docs/reports/Deployment-Verification-Report.md` | VER | 9.1.4.16 | R | HR |

**Key**: Item 38 is **"Release Notes"** (plural) — this is the deployment release notes, distinct from the validation "Release Note" (singular, §7.7.4.12 normative, no Annex C number).

### Phase 10: Maintenance (EN 50128 Section 9.2) — Annex C items 41–44

**Purpose**: Manage software changes after deployment  
**Primary Agents**: PM, CM, VER

**This phase was absent from the prior lifecycle definition and is now added per Annex C.**

| Annex C # | Document Name | File Path | Written by | EN 50128 Clause | SIL 0 | SIL 1-4 |
|-----------|--------------|-----------|-----------|-----------------|-------|---------|
| 41 | **Software Maintenance Plan** | `docs/plans/Software-Maintenance-Plan.md` | PM / CM | 9.2.4.5 | R | HR |
| 42 | **Software Change Records** | `docs/reports/Software-Change-Records.md` | CM | 9.2.4.10 | HR | HR |
| 43 | **Software Maintenance Records** | `docs/reports/Software-Maintenance-Records.md` | CM | 9.2.4 | R | HR |
| 44 | **Software Maintenance Verification Report** | `docs/reports/Software-Maintenance-Verification-Report.md` | VER | 9.2.4 | R | HR |

**Note**: Annex C item 42 contains a typo — "Software Chang Records". The correct name from Section 9.2.4 is **"Software Change Records"**.

### Summary Statistics

**Documents by Phase (per Annex C Table C.1)**

| Phase | Annex C Items | Documents | SIL 0 Level | SIL 1-4 Level |
|-------|--------------|-----------|-------------|---------------|
| Phase 0: Initialization | — | 1 | N/A | N/A |
| Phase 1: Planning | 1–5 | 5 | HR | HR |
| Phase 2: Requirements | 6–8 | 3 | HR | HR |
| Phase 3: Architecture & Design | 9–14 | 6 | HR | HR |
| Phase 4: Component Design | 15–17 | 3 | R | HR |
| Phase 5: Implementation & Testing | 18–19 | 2 | HR | HR |
| Phase 6: Integration | 20–22 | 3 | R (×1), HR (×2) | HR |
| Phase 7: Validation | 23–26 | 4 | HR (×3), R (×1) | HR |
| Phase 8: Assessment | 45–46 | 2 | R | HR |
| Phase 9: Deployment | 36–40 | 5 | HR (×1), R (×4) | HR |
| Phase 10: Maintenance | 41–44 | 4 | HR (×1), R (×3) | HR |
| Section 8 (generic platform only) | 28–35 | 8 | HR | HR |
| **TOTAL (Annex C)** | **1–46** | **46** | — | — |
| **Total for bespoke app (excl. §8)** | **1–26, 36–46** | **37** | — | — |

**V-Model Specification → Report Correspondence**

| Specification (Left side) | Annex C # | Phase Created | Report (Right side) | Annex C # | Phase Produced |
|---------------------------|-----------|--------------|---------------------|-----------|----------------|
| Overall Software Test Specification | 7 | 2: Requirements | Overall Software Test Report | 24 | 7: Validation |
| Software Integration Test Specification | 12 | 3: Architecture & Design | Software Integration Test Report | 21 | 6: Integration |
| Software/Hardware Integration Test Specification | 13 | 3: Architecture & Design | Software/Hardware Integration Test Report | 22 | 6: Integration |
| Software Component Test Specification | 16 | 4: Component Design | Software Component Test Report | 20 | 5: Implementation & Testing |
