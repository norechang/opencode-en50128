# EN 50128 Software Development Lifecycle

This document defines the complete software development lifecycle for EN 50128:2011 compliant railway safety software development. All projects in this workspace SHALL follow this lifecycle.

## Document Information

| Property | Value |
|----------|-------|
| **Standard** | EN 50128:2011 Railway Software Standard |
| **Section** | Section 6: Software Lifecycle Issues |
| **Lifecycle Model** | V-Model (Mandatory for SIL 2-4) |
| **Language** | C (MISRA C:2012 for SIL 2+) |
| **Version** | 1.0 |

---

## 1. Lifecycle Overview

### 1.1 EN 50128 V-Model

The V-Model is MANDATORY for SIL 2-4 and shows the relationship between development phases (left side) and verification/validation phases (right side).

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
    Software Design ─────────┼──────────► Module Testing
    (Software Design Specification - Section 7.3)      │          (Section 7.4)
           │                 │                      ▲
           │                 │                      │
           ▼                 │                      │
    Implementation ──────────┴──────────► Unit Testing
    (Code - Section 7.4)                 (Section 7.4)
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

1. **Software Planning & Management** (Sections 5, 6.5, 6.6)
2. **Software Requirements** (Section 7.2)
3. **Software Architecture & Design** (Section 7.3)
4. **Software Implementation & Testing** (Section 7.4, 7.5)
5. **Software Integration** (Section 7.6)
6. **Software Validation** (Section 7.7)
7. **Software Assessment** (Section 6.4)
8. **Software Deployment & Maintenance** (Section 7.8)

**Lifecycle Coordinator (COD)**: The COD agent (`/cod`) orchestrates the complete lifecycle with SIL-dependent phase gate enforcement. See COD sections at the end of each phase for gate checkpoint details.

---

## 2. Phase 1: Software Planning (Sections 5, 6.5, 6.6)

### 2.1 Objectives
- Define project organization and responsibilities
- Establish quality assurance plan
- Define verification and validation strategies
- Establish configuration management
- Determine SIL levels

### 2.2 Key Activities
1. Establish Software Quality Assurance Plan (SQAP)
2. Establish Software Configuration Management Plan (SCMP)
3. Establish Software Verification Plan (SVP)
4. Establish Software Validation Plan (SVaP)
5. Define project standards and guidelines

### 2.3 Agents Involved
- Project Manager (`/pm`) - overall project coordination, CCB leadership
- Software Manager - software development responsibility (per EN 50128 Section 5.3.1)
- Configuration Manager (`/cm`) - version control, change management, baselines
- Quality Assurance (`/qua`) - SQAP development and enforcement
- Safety Engineer (`/saf`) - safety planning and SIL determination

**Note**: EN 50128 defines both "Project Manager" (Table B.9) and "Software Manager" (Section 5.3.1). Project Manager has overall project coordination responsibility, while Software Manager focuses on software development activities.

### 2.4 Deliverables
- [ ] Software Quality Assurance Plan (SQAP)
- [ ] Software Configuration Management Plan (SCMP)
- [ ] Software Verification Plan (SVP)
- [ ] Software Validation Plan (SVaP)
- [ ] Project Standards Document
- [ ] Tool Qualification Plan (if applicable)

### 2.5 EN 50128 References
- Section 5: Organizational requirements
- Section 6.5: Software quality assurance
- Section 6.6: Modification and change control
- Table A.1: Software lifecycle phases and related documents

### 2.6 Entry Criteria
- System requirements available
- SIL level determined
- Project authorization obtained

### 2.7 Exit Criteria
- All planning documents approved
- Quality gates defined
- Verification/validation strategies established
- Configuration management in place

### 2.8 Phase Gate (COD Checkpoint)

**Command**: `/cod gate-check planning`

The Lifecycle Coordinator (COD) enforces phase gate compliance before allowing transition to Phase 2 (Requirements). Gate enforcement is SIL-dependent:

- **SIL 0-1**: Advisory mode - COD provides warnings if criteria not met, but allows user override
- **SIL 2**: Semi-strict mode - COD requires justification for proceeding with incomplete criteria
- **SIL 3-4**: Strict gatekeeper mode - COD BLOCKS transition until all mandatory criteria satisfied

**Gate Checklist**:
- [ ] SQAP (Software Quality Assurance Plan) approved and baselined
- [ ] SCMP (Software Configuration Management Plan) approved and baselined
- [ ] SVP (Software Verification Plan) approved and baselined
- [ ] SVaP (Software Validation Plan) approved and baselined
- [ ] Project standards document complete
- [ ] Tool qualification plan prepared (if applicable)
- [ ] Configuration management system operational
- [ ] Project organization defined with role assignments
- [ ] SIL level determined and documented
- [ ] LIFECYCLE_STATE.md initialized (via `/cod plan --sil [0-4] --project [name]`)

**EN 50128 Reference**: Section 5.3.2.5 - "All activities to be performed during a phase shall be defined and planned prior to commencement"

**COD Behavior**:
- Verifies all planning deliverables present in project repository
- Checks document approval status in LIFECYCLE_STATE.md
- Validates configuration management baseline established
- For SIL 3-4: BLOCKS any `/req` invocation until gate passed

---

## 3. Phase 2: Software Requirements (Section 7.2)

### 3.1 Objectives
- Define complete, unambiguous software requirements
- Establish requirements traceability
- Assign SIL levels to requirements
- Identify safety requirements

### 3.2 Key Activities
1. Elicit requirements from stakeholders and system specification
2. Write Software Requirements Specification
3. Establish requirements traceability matrix
4. Perform hazard analysis
5. Define safety requirements
6. **QA document template compliance check (MANDATORY before VER for SIL 3-4)**
7. Review and approve requirements

### 3.3 Agents Involved
- Requirements Engineer (`/req`) - PRIMARY
- Safety Engineer (`/saf`)
- Quality Assurance (`/qua`) - **Document template compliance check BEFORE VER**

### 3.4 Skills Required
- `en50128-requirements` - Requirements engineering patterns
- `en50128-safety` - Hazard analysis and safety requirements
- `en50128-documentation` - Software Requirements Specification templates

### 3.5 Deliverables
- [ ] Software Requirements Specification
- [ ] traceability (embedded in Software Requirements Specification)
- [ ] Hazard Log
- [ ] Safety Requirements Specification
- [ ] **QA Document Template Compliance Report (MANDATORY SIL 3-4, BEFORE VER)**
- [ ] Requirements Review Report

### 3.6 Requirements Quality Checklist
- [ ] All requirements unambiguous
- [ ] All requirements testable
- [ ] All requirements traceable
- [ ] SHALL/SHOULD/MAY keywords used correctly
- [ ] SIL levels assigned
- [ ] C language constraints considered
- [ ] Safety requirements identified

### 3.7 EN 50128 Techniques/Measures (Table A.2)

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

### 3.8 EN 50128 References
- Section 7.2: Software requirements specification
- Table A.2: Software requirements specification techniques
- Section 7.2.4: Detailed requirements

### 3.9 Entry Criteria
- System requirements available
- SQAP approved
- Verification plan approved

### 3.10 Exit Criteria
- Software Requirements Specification complete and approved
- All requirements traceable to system requirements
- Requirements review passed
- Hazard analysis complete

### 3.11 Phase Gate (COD Checkpoint)

**Command**: `/cod gate-check requirements`

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
- [ ] USER APPROVAL obtained for requirement establishment (mandatory via `/cod approve-requirement`)

**EN 50128 Requirements (Section 7.2)**:
- Techniques from Table A.2 applied (Structured Methodology HR for SIL 3-4)
- Requirements unambiguous and verifiable (mandatory)
- Traceability to system requirements (mandatory SIL 3-4)

**COD Behavior**:
- **User approval verification**: COD SHALL verify user explicitly approved requirement activities
- Validates traceability completeness (all requirements traced bidirectionally)
- Checks SIL assignment for all requirements
- Verifies hazard analysis completeness (FMEA/FTA for SIL 3-4)
- For SIL 3-4: BLOCKS any `/des` invocation until gate passed
- For SIL 2: Requires justification if criteria incomplete
- For SIL 0-1: Provides warnings only

---

## 4. Phase 3: Software Architecture & Design (Section 7.3)

### 4.1 Objectives
- Define software architecture
- Design software modules and interfaces
- Ensure design meets requirements
- Apply defensive programming principles

### 4.2 Key Activities
1. Create Software Architecture Specification
2. Create Software Design Specification
3. Define module interfaces
4. Design data structures (static allocation for SIL 2+)
5. Define error handling strategy
6. Perform design reviews
7. Establish complexity limits
8. **QA document template compliance check (MANDATORY before VER for SIL 3-4)**

### 4.3 Agents Involved
- Designer (`/des`) - PRIMARY
- Safety Engineer (`/saf`)
- Quality Assurance (`/qua`) - **Document template compliance check BEFORE VER**
- Requirements Engineer (`/req`) - for traceability

### 4.4 Skills Required
- `en50128-design` - Architecture and design patterns
- `en50128-safety` - Safety analysis (FMEA/FTA)
- `en50128-implementation` - MISRA C design patterns

### 4.5 Deliverables
- [ ] Software Architecture Specification
- [ ] Software Design Specification
- [ ] Interface Control Document (ICD)
- [ ] Design Traceability Matrix
- [ ] **QA Document Template Compliance Report (MANDATORY SIL 3-4, BEFORE VER)**
- [ ] Design Review Report
- [ ] FMEA/FTA Results (SIL 3-4)

### 4.6 Design Constraints by SIL

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

### 4.7 Design Review Checklist
- [ ] Architecture traceable to requirements
- [ ] Module interfaces clearly defined
- [ ] Static allocation used (SIL 2+)
- [ ] Complexity limits defined
- [ ] Error handling comprehensive
- [ ] MISRA C compliance considered
- [ ] Safety mechanisms designed

### 4.8 EN 50128 Techniques/Measures (Table A.3)

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

### 4.9 EN 50128 References
- Section 7.3: Software architecture and design  
- Table A.3: Software architecture techniques
- Annex D: Technique descriptions

### 4.10 Entry Criteria
- Software Requirements Specification approved
- Design standards defined
- FMEA/FTA planned (SIL 3-4)

### 4.11 Exit Criteria
- Software Architecture Specification and Software Design Specification complete and approved
- Design traceable to requirements
- Design review passed
- Complexity limits established

### 4.12 Phase Gate (COD Checkpoint)

**Command**: `/cod gate-check design`

The Lifecycle Coordinator (COD) enforces design phase completion before allowing transition to Phase 4 (Implementation).

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
- For SIL 3-4: BLOCKS any `/imp` invocation until gate passed
- For SIL 2: Requires justification if FMEA/FTA not performed
- For SIL 0-1: Provides warnings only

---

## 5. Phase 4: Software Implementation & Testing (Section 7.4)

### 5.1 Objectives
- Implement software modules in C
- Ensure MISRA C:2012 compliance
- Develop unit tests
- Achieve required coverage

### 5.2 Key Activities
1. Implement C code following MISRA C:2012
2. Write unit tests (Unity framework)
3. Execute unit tests
4. Measure code coverage
5. Perform static analysis
6. Conduct code reviews
7. Document code

### 5.3 Agents Involved
- Implementer (`/imp`) - PRIMARY
- Tester (`/tst`)
- Verifier (`/ver`)
- Quality Assurance (`/qua`)

### 5.4 Skills Required
- `en50128-implementation` - MISRA C coding patterns
- `en50128-testing` - Unit testing with Unity
- `en50128-verification` - Static analysis
- `en50128-design` - Design patterns reference

### 5.5 Deliverables
- [ ] Source Code (*.c, *.h)
- [ ] Unit Test Code
- [ ] Unit Test Results
- [ ] Code Coverage Report (100% for SIL 3-4)
- [ ] Static Analysis Report (PC-lint/Cppcheck)
- [ ] Complexity Analysis Report (Lizard)
- [ ] **QA Code Review Report (MANDATORY - includes template compliance for code documentation)**
- [ ] Implementation Traceability Matrix

### 5.6 MISRA C:2012 Compliance

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

### 5.7 Coverage Requirements by SIL

| SIL Level | Statement | Branch | MC/DC | Notes |
|-----------|-----------|--------|-------|-------|
| SIL 0-1 | 80% | 70% | - | Recommended |
| SIL 2 | 100% | 100% | - | Mandatory |
| SIL 3-4 | 100% | 100% | 100% | Mandatory |

### 5.8 Implementation Checklist
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

### 5.9 EN 50128 Techniques/Measures (Table A.4)

**Software Design and Implementation (EN 50128 Section 7.4):**

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

### 5.10 EN 50128 References
- Section 7.4: Component design and implementation
- Table A.4: Design and implementation techniques
- Table A.12: Coding standards (MISRA C)
- Table A.15: Programming languages

### 5.11 Entry Criteria
- Software Design Specification approved
- Coding standards defined
- Unit test framework ready
- Static analysis tools configured

### 5.12 Exit Criteria
- All code implemented and reviewed
- Unit tests pass
- Coverage requirements met
- Static analysis clean
- Code traceable to design

### 5.13 Phase Gate (COD Checkpoint)

**Command**: `/cod gate-check implementation`

The Lifecycle Coordinator (COD) enforces implementation phase completion before allowing transition to Phase 5 (Integration).

**Gate Checklist**:
- [ ] All source code (*.c, *.h) complete and reviewed
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

**EN 50128 Requirements (Section 7.4, Table A.4)**:
- Structured Methodology applied (mandatory SIL 3-4)
- Modular Approach used (mandatory SIL 2+)
- Design and Coding Standards enforced (mandatory SIL 3-4, MISRA C:2012)
- Analysable Programs (mandatory SIL 3-4)
- Structured Programming (mandatory SIL 3-4)

**COD Behavior**:
- Validates MISRA C compliance reports (zero mandatory violations for SIL 2+)
- Checks code coverage against SIL-specific thresholds
- Verifies complexity metrics for all functions
- Confirms traceability from code to design
- Validates unit test pass rate (must be 100%)
- For SIL 3-4: BLOCKS any `/int` invocation until gate passed
- For SIL 2: Requires justification if coverage < 100% statement/branch
- For SIL 0-1: Provides warnings if recommended thresholds not met

---

## 6. Phase 5: Software Integration (Section 7.6)

### 6.1 Objectives
- Integrate software modules progressively
- Perform integration testing
- Verify module interfaces
- Test software/hardware integration
- Validate integrated system behavior

### 6.2 Key Activities
1. Plan integration strategy (bottom-up, top-down, or sandwich)
2. Integrate modules incrementally
3. Execute integration tests
4. Test module interfaces (functional and non-functional)
5. Verify data flow between components
6. Perform performance testing (highly recommended SIL 3-4)
7. Resolve integration issues

### 6.3 Agents Involved
- Integrator (`/int`) - PRIMARY
- Tester (`/tst`)
- Implementer (`/imp`)
- Designer (`/des`)
- Verifier (`/ver`)
- Configuration Manager (`/cm`) - for integration baselines

### 6.4 Skills Required
- `en50128-integration` - Integration strategies and testing
- `en50128-testing` - Integration test techniques
- `en50128-verification` - Integration verification

### 6.5 Deliverables
- [ ] Software Integration Plan
- [ ] Integration Test Specification
- [ ] Integration Test Results
- [ ] Interface Test Results
- [ ] Integration Coverage Report
- [ ] Performance Test Results (SIL 3-4)
- [ ] **QA Integration Test Review Report (includes template compliance)**
- [ ] Issue Resolution Log
- [ ] Integrated Software Baseline

### 6.6 Integration Testing Checklist
- [ ] Integration strategy defined (bottom-up/top-down/sandwich)
- [ ] All modules integrated progressively
- [ ] Interface tests executed (all interfaces)
- [ ] Data flow verified between components
- [ ] Error handling tested at boundaries
- [ ] Performance requirements met
- [ ] Integration issues documented and resolved
- [ ] Integration baseline established

### 6.7 EN 50128 Techniques/Measures (Table A.6)

**Software Integration (EN 50128 Section 7.6):**

| Technique/Measure | SIL 0 | SIL 1-2 | SIL 3-4 | Reference |
|-------------------|-------|---------|---------|-----------|
| Functional and Black-box Testing | HR | HR | HR | Table A.14 |
| Performance Testing | - | R | HR | Table A.18 |

**Key:** M = Mandatory, HR = Highly Recommended, R = Recommended

**Additional Requirements:**
- Integration testing SHALL verify all interfaces between software components
- Integration testing SHALL verify software/hardware interfaces
- Progressive integration approach SHALL be used (bottom-up, top-down, or sandwich)
- Performance testing HIGHLY RECOMMENDED for SIL 3-4

### 6.8 EN 50128 References
- Section 7.6: Software integration
- Table A.6: Software integration techniques
- Table A.14: Functional and black-box testing
- Table A.18: Performance testing

### 6.9 Entry Criteria
- All modules unit tested and passed
- Integration test plan approved
- Integration environment ready
- Configuration management in place

### 6.10 Exit Criteria
- All integration tests pass
- All interfaces verified (functional and performance)
- Software baseline established
- Integration issues resolved
- Ready for validation

### 6.11 Phase Gate (COD Checkpoint)

**Command**: `/cod gate-check integration`

The Lifecycle Coordinator (COD) enforces integration phase completion before allowing transition to Phase 6 (Validation).

**Gate Checklist**:
- [ ] Software Integration Plan complete and approved
- [ ] Integration Test Specification complete
- [ ] All integration tests executed and passed (100% pass rate)
- [ ] All module interfaces tested (functional and non-functional)
- [ ] Interface Test Results documented
- [ ] Data flow between components verified
- [ ] Error handling tested at all component boundaries
- [ ] Performance test results documented (highly recommended SIL 3-4)
- [ ] Integration coverage report complete
- [ ] **QA integration test review approved (includes template compliance)**
- [ ] All integration issues documented and resolved
- [ ] Integration strategy followed (bottom-up/top-down/sandwich)
- [ ] Software/hardware interface testing complete
- [ ] Integrated software baseline established by Configuration Manager
- [ ] Integration traceability complete (modules → integrated system)

**EN 50128 Requirements (Section 7.6, Table A.6)**:
- Functional and Black-box Testing applied (highly recommended all SILs)
- Performance Testing applied (highly recommended SIL 3-4)
- Progressive integration approach used
- All interfaces verified

**COD Behavior**:
- Validates all integration tests passed (100% pass rate)
- Checks interface testing completeness (all interfaces tested)
- Verifies performance testing performed (SIL 3-4)
- Confirms integration issues resolved (no open critical/high issues)
- Validates baseline established
- For SIL 3-4: BLOCKS any `/val` invocation until gate passed
- For SIL 2: Requires justification if performance testing not performed
- For SIL 0-1: Provides warnings only

---

## 7. Phase 6: Software Validation (Section 7.7)

### 7.1 Objectives
- Validate software meets requirements
- Validate in operational environment
- Obtain customer acceptance
- Demonstrate safety requirements

### 7.2 Key Activities
1. Execute validation test suite
2. Perform operational scenario testing
3. Conduct user acceptance testing
4. Validate safety requirements
5. Perform performance testing (mandatory SIL 3-4)

### 7.3 Agents Involved
- Validator (`/val`) - PRIMARY (MUST be independent for SIL 3-4)
- Tester (`/tst`)
- Safety Engineer (`/saf`)
- Customer/End User

**CRITICAL:** For SIL 3-4, Validator MUST be independent and SHALL NOT report to Project Manager.

### 7.4 Skills Required
- `en50128-validation` - System testing and UAT
- `en50128-safety` - Safety validation
- `en50128-testing` - Test execution

### 7.5 Deliverables
- [ ] Software Validation Plan (SVaP)
- [ ] Software Validation Report
- [ ] Validation Test Results
- [ ] User Acceptance Test Results
- [ ] Safety Validation Report
- [ ] Performance Test Results
- [ ] **QA Validation Review Report (includes template compliance)**
- [ ] Acceptance Certificate

### 7.6 Validation Testing Checklist
- [ ] All requirements validated
- [ ] Operational scenarios tested
- [ ] Safety requirements validated
- [ ] Performance requirements met (mandatory SIL 3-4)
- [ ] User acceptance obtained
- [ ] Validation team independent (mandatory SIL 3-4)

### 7.7 EN 50128 Techniques/Measures (Table A.7)

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

### 7.8 EN 50128 References
- Section 7.7: Overall software testing (validation)
- Table A.7: Overall software testing techniques
- Table A.14: Functional and black-box testing
- Table A.18: Performance testing

### 7.9 Entry Criteria
- Integration complete
- Validation plan (SVaP) approved
- Target environment available
- Independent validator assigned (SIL 3-4)

### 7.10 Exit Criteria
- All validation tests pass
- Customer acceptance obtained
- Safety requirements validated
- Performance requirements met (SIL 3-4)
- Validation report approved

### 7.11 Phase Gate (COD Checkpoint)

**Command**: `/cod gate-check validation`

The Lifecycle Coordinator (COD) enforces validation phase completion before allowing transition to Phase 7 (Assessment).

**Gate Checklist**:
- [ ] Software Validation Plan (SVaP) approved and followed
- [ ] Software Validation Report complete and approved
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

## 8. Phase 7: Software Verification (Section 6.2 - Continuous)

### 8.1 Objectives
- Verify correctness throughout lifecycle
- Ensure compliance with standards
- Collect objective evidence
- Maintain quality

### 8.2 Key Activities (Throughout Lifecycle)
1. Perform static analysis
2. Conduct design reviews
3. Conduct code reviews
4. Verify traceability
5. Check complexity
6. Verify coverage
7. Collect evidence

### 8.3 Agents Involved
- Verifier (`/ver`) - PRIMARY (must be independent for SIL 3-4)
- Quality Assurance (`/qua`)
- All other agents (peer verification)

### 8.4 Skills Required
- `en50128-verification` - Static analysis, verification methods
- `en50128-quality` - QA processes

### 8.5 Deliverables
- [ ] Software Verification Report
- [ ] Static Analysis Reports
- [ ] Review Records
- [ ] Traceability Verification
- [ ] Complexity Analysis
- [ ] Coverage Reports
- [ ] Verification Evidence Package

### 8.6 Verification Checklist
- [ ] Requirements verification complete
- [ ] Design verification complete
- [ ] Code verification complete
- [ ] Test verification complete
- [ ] Traceability verified
- [ ] MISRA C compliance verified
- [ ] Coverage verified
- [ ] Independent verification (SIL 3-4)

### 8.7 EN 50128 Techniques/Measures (Table A.5)

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

### 8.8 EN 50128 References
- Section 6.2: Verification and testing
- Section 7.3: Software architecture verification
- Table A.5: Verification and testing techniques
- Table A.13: Dynamic analysis and testing
- Table A.19: Static analysis techniques
- Table A.21: Test coverage for code

### 8.9 Independence Requirements

| SIL Level | Verification Independence |
|-----------|---------------------------|
| SIL 0-1 | Not required |
| SIL 2 | Highly recommended |
| SIL 3-4 | Mandatory |

---

## 9. Phase 8: Software Assessment (Section 6.4)

### 9.1 Objectives
- Assess overall software quality
- Verify compliance with EN 50128
- Determine readiness for deployment
- Obtain safety approval

### 9.2 Key Activities
1. Review all lifecycle artifacts
2. Assess compliance with EN 50128
3. Review verification evidence
4. Review validation results
5. Assess safety case
6. Prepare assessment report

### 9.3 Agents Involved
- **Assessor** (independent, mandatory for SIL 3-4, per EN 50128 Section 5.3.8, Table B.8)
- **Project Manager** (overall project responsibility)
- **Software Manager** (software development responsibility)
- Quality Assurance (`/qua`)

**Note**: The Assessor role is explicitly defined in EN 50128 Section 5.3.8 and MUST be completely independent for SIL 3-4.

### 9.4 Deliverables
- [ ] Software Assessment Report
- [ ] Compliance Matrix
- [ ] Safety Case
- [ ] Approval Certificate
- [ ] Deployment Authorization

### 9.5 Assessment Checklist
- [ ] All lifecycle phases complete
- [ ] All deliverables produced
- [ ] Traceability complete
- [ ] Verification complete
- [ ] Validation complete
- [ ] MISRA C compliance verified
- [ ] Coverage requirements met
- [ ] Safety requirements satisfied
- [ ] EN 50128 compliance demonstrated

### 9.6 EN 50128 References
- Section 6.4: Software assessment
- Table A.1: Lifecycle requirements

### 9.7 Phase Gate (COD Checkpoint)

**Command**: `/cod gate-check assessment`

The Lifecycle Coordinator (COD) enforces assessment phase completion before allowing transition to Phase 8 (Deployment). This gate is MANDATORY for SIL 3-4 projects.

**Gate Checklist**:
- [ ] Software Assessment Report complete and approved
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
- [ ] Independent assessor verified (mandatory SIL 3-4)
- [ ] Assessor independence from development confirmed (SIL 3-4)
- [ ] Approval Certificate issued
- [ ] Deployment Authorization obtained
- [ ] Final release baseline established by Configuration Manager

**EN 50128 Requirements (Section 6.4)**:
- Independent assessor assigned (mandatory SIL 3-4)
- Assessor SHALL be completely independent (SIL 3-4)
- All lifecycle artifacts reviewed
- EN 50128 compliance demonstrated

**COD Behavior**:
- Validates all lifecycle phases complete (Planning → Requirements → Design → Implementation → Integration → Validation → Assessment)
- Verifies end-to-end traceability (traceability complete and verified)
- Checks all deliverables present per SIL level requirements
- Confirms safety case complete and approved
- **Validates assessor independence** (SIL 3-4): COD verifies assessor is independent from development team, PM, and validator
- Ensures approval certificate and deployment authorization obtained
- For SIL 3-4: BLOCKS deployment until gate passed AND independent assessment complete
- For SIL 2: Requires justification if independent assessment not performed
- For SIL 0-1: Provides warnings only

**Critical Independence Check (SIL 3-4)**:
COD SHALL verify assessor role assignment and complete organizational independence before authorizing deployment.

---

## 10. Lifecycle Coordinator (COD) Overview

### 10.1 Role and Authority

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

### 10.2 COD Commands

| Command | Purpose | When to Use |
|---------|---------|-------------|
| `/cod plan --sil [0-4] --project [name]` | Initialize lifecycle tracking | At project start (Phase 0) |
| `/cod gate-check <phase>` | Verify phase completion, authorize transition | After each phase completion |
| `/cod status` | View current lifecycle state | Anytime during project |
| `/cod approve-requirement` | Approve requirement activities | Auto-triggered when `/req` invoked |

### 10.3 SIL-Dependent Gate Enforcement

COD adapts its enforcement behavior based on project SIL level:

| SIL Level | Enforcement Mode | Behavior |
|-----------|------------------|----------|
| **SIL 0-1** | Advisory | Provides warnings if criteria not met, allows user override |
| **SIL 2** | Semi-strict | Requires justification to proceed with incomplete criteria |
| **SIL 3-4** | Strict Gatekeeper | **BLOCKS** phase transitions until all mandatory criteria satisfied |

### 10.4 Phase Gates Managed by COD

COD manages 8 phase gates corresponding to the EN 50128 lifecycle:

1. **Planning Gate** - Verify SQAP, SCMP, SVP, SVaP before requirements
2. **Requirements Gate** - Verify Software Requirements Specification, traceability, hazard analysis, user approval before design
3. **Design Gate** - Verify Software Architecture Specification, Software Design Specification, traceability, complexity limits before implementation
4. **Implementation Gate** - Verify MISRA C compliance, coverage, unit tests before integration
5. **Integration Gate** - Verify integration tests, interfaces, baseline before validation
6. **Validation Gate** - Verify validation tests, customer acceptance, validator independence before assessment
7. **Assessment Gate** - Verify assessment report, safety case, assessor independence before deployment
8. **Deployment Gate** - (Future) Verify deployment readiness

### 10.5 Background Monitoring

COD operates as a **background orchestrator** that:
- Intercepts agent invocations to validate lifecycle context
- Blocks out-of-sequence activities (SIL 3-4) or warns (SIL 0-2)
- Requires user approval for `/req` invocations (all SIL levels)
- Tracks deliverables in `LIFECYCLE_STATE.md`
- Enforces phase gates with SIL-dependent authority
- Preserves independence of Validator and Assessor roles (does NOT control them)

### 10.6 LIFECYCLE_STATE.md

COD maintains project state in `LIFECYCLE_STATE.md` (project root), which tracks:
- Current phase and status
- Deliverable completion status
- Phase gate pass/fail status
- Traceability status (traceability completeness)
- Agent activity log
- Approval history (requirements, reviews, baselines)
- Change requests and resolution

**Location**: Project root (e.g., `examples/train_door_control/LIFECYCLE_STATE.md`)

### 10.7 User Approval Workflow

COD enforces **mandatory user approval** for all requirement establishment and modification activities:

1. User invokes `/req` for requirement activities
2. COD intercepts the invocation
3. COD prompts user: "Requirement activity requires explicit approval. Approve? [Y/N]"
4. If approved: COD allows `/req` to proceed and logs approval in LIFECYCLE_STATE.md
5. If denied: COD blocks `/req` invocation

**Rationale**: Requirements are the foundation of safety-critical systems. Explicit user approval ensures conscious decision-making and accountability.

### 10.8 Independence Preservation

COD coordinates with but does NOT control independent roles:

- **Validator (SIL 3-4)**: COD verifies validator independence and does NOT report to PM, but COD does not direct validation activities
- **Assessor (SIL 3-4)**: COD verifies assessor complete independence, but COD does not control assessment process
- **Verifier (SIL 3-4)**: COD verifies verifier independence from implementer, but COD does not direct verification activities

COD's role is **lifecycle compliance enforcement**, not **technical oversight** of independent roles.

---

## 11. Lifecycle Workflow Examples

### 11.1 Example: Complete SIL 3 Project Workflow

```bash
# Phase 0: Initialization (COD)
/cod plan --sil 3 --project train_door_control
# Initialize lifecycle tracking, create LIFECYCLE_STATE.md
# COD monitors all subsequent activities

# Phase 1: Planning
/pm   # Project coordination, establish CCB
/cm   # Establish SCMP, version control, baselines
/qua  # Establish SQAP, quality processes
# (Create SQAP, SCMP, SVP, SVaP documents)

# COD Phase Gate Check
/cod gate-check planning
# COD verifies all planning documents approved before allowing requirements phase

# Phase 2: Requirements
/req  # COD intercepts - requires user approval for requirement activities
# Create Software Requirements Specification, requirements.md
# Establish traceability matrix
# Assign SIL levels

/saf
# Perform hazard analysis
# Define safety requirements

/qua
# MANDATORY: Document template compliance check (SIL 3-4)
# Verify Document ID format (DOC-XXX-YYYY-NNN)
# Verify Document Control table present
# Verify Approvals table with correct SIL-specific roles
# Generate QA Template Compliance Report

/ver
# Independent verification (mandatory SIL 3-4)
# Verify requirements quality, traceability, safety analysis
# Verify QA template compliance was performed

/cm
# Baseline requirements (requirements freeze)

# COD Phase Gate Check
/cod gate-check requirements
# COD verifies Software Requirements Specification complete, traceability complete, hazard analysis done, user approval obtained
# COD verifies QA template compliance check performed (MANDATORY SIL 3-4)

# Phase 3: Design
/des
# Create Software Architecture Specification
# Create Software Design Specification
# Define interfaces

/saf
# Perform FMEA/FTA on design
# Design safety mechanisms

/qua
# MANDATORY: Document template compliance check (SIL 3-4)
# Design review - verify complexity limits, defensive programming
# Verify Document ID, Document Control, Approvals table
# Generate QA Template Compliance Report

/ver
# Independent verification (mandatory SIL 3-4)
# Verify design quality, traceability to requirements
# Verify QA template compliance and design review performed

/cm
# Baseline design (design freeze)

# COD Phase Gate Check
/cod gate-check design
# COD verifies design complete, traceability to requirements, complexity limits defined
# COD verifies QA template compliance check performed (MANDATORY SIL 3-4)

# Phase 4: Implementation & Unit Testing
/imp
# Implement C code (MISRA C:2012 compliant)
# Static allocation only (SIL 2+)
# Write unit tests

/tst
# Execute unit tests
# Measure coverage (100% statement, branch, condition for SIL 3)

/qua
# MANDATORY: Code review (includes template compliance for code documentation)
# Check MISRA C compliance (zero mandatory violations for SIL 2+)
# Verify complexity within limits (≤10 for SIL 3-4)
# Check defensive programming patterns
# Verify code documentation follows standards
# Generate QA Code Review Report

/ver
# Run static analysis (PC-lint, Cppcheck)
# Verify complexity (≤10 for SIL 3-4)
# Check MISRA C compliance
# Verify QA code review performed

# COD Phase Gate Check
/cod gate-check implementation
# COD verifies MISRA C compliance, coverage met (100% for SIL 3), complexity ≤10
# COD verifies QA code review performed (MANDATORY all SILs)

# Phase 5: Integration
/int
# Integrate components progressively
# Execute integration tests
# Interface testing
# Performance testing (highly recommended SIL 3-4)

/qua
# MANDATORY: Integration test review (includes template compliance)
# Verify integration test specification follows template
# Verify integration test results documentation complete
# Generate QA Integration Test Review Report

/ver
# Verify integration test coverage
# Verify all interfaces tested
# Verify QA review performed

/cm
# Establish integration baseline

# COD Phase Gate Check
/cod gate-check integration
# COD verifies all integration tests pass, interfaces tested, baseline established
# COD verifies QA integration test review performed (MANDATORY SIL 3-4)

# Phase 6: Validation
/val  # COD verifies validator independence (mandatory SIL 3-4)
# System testing on target environment
# User acceptance testing (UAT)
# Safety validation
# Performance testing (mandatory SIL 3-4)

/qua
# MANDATORY: Validation review (includes template compliance)
# Verify validation plan and report follow template
# Verify UAT results documentation complete
# Generate QA Validation Review Report

/ver
# Verify validation test coverage
# Verify all requirements validated
# Verify QA review performed

# Phase 7: Verification (continuous throughout)
/ver  # COD verifies verifier independence (mandatory SIL 3-4)
# Collect all verification evidence
# Verify complete traceability
# Generate verification report

# COD Phase Gate Check
/cod gate-check validation
# COD verifies all tests pass, customer acceptance, validator independence
# COD verifies QA validation review performed (MANDATORY SIL 3-4)

# Phase 8: Assessment
/qua
# Software assessment
# Compliance verification
# Generate assessment report

/cm
# Establish release baseline
# Archive all evidence

/pm
# Obtain deployment approval
# Coordinate with assessor

# COD Phase Gate Check
/cod gate-check assessment
# COD verifies assessment complete, assessor independence, deployment authorization

# COD Status Check (anytime)
/cod status
# View current phase, progress, deliverable status, gate compliance
```

### 11.2 Example: Quick Prototyping (SIL 0-1)

```bash
# Simplified workflow for lower SIL levels
/cod plan --sil 0 --project prototype  # Optional for SIL 0-1 (advisory mode)
/req  # Define basic requirements (no user approval required for SIL 0-1)
/des  # Basic design
/imp  # Implement and test
/tst  # Test with 80% coverage
/cm   # Basic version control
# COD provides warnings only, does not block transitions
```

### 11.3 Example: Iterative Development (SIL 2)

```bash
# Initial project setup
/cod plan --sil 2 --project iterative_system

# Iteration planning
/pm   # Plan iteration, coordinate team
/cm   # Create iteration branch

# Development cycle
/req  # Refine requirements for iteration (user approval required)
/cod gate-check requirements  # Semi-strict: requires justification if incomplete
/des  # Design iteration features
/cod gate-check design  # Semi-strict mode
/imp  # Implement with MISRA C:2012
/tst  # Unit test (100% branch coverage - mandatory SIL 2)
/int  # Integration testing
/ver  # Static analysis (mandatory SIL 2), code review
/qua  # Quality gates check
/cod gate-check implementation  # Semi-strict: checks MISRA C, coverage

# Iteration completion
/cm   # Merge to main, tag baseline
/pm   # Iteration review, plan next iteration
/cod status  # Check overall progress and compliance
```

---

## 12. Traceability Requirements

### 12.1 Mandatory Traceability Links

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

### 12.2 Bidirectional Traceability

All traceability MUST be bidirectional:
- Forward: Requirement → Design → Code → Test
- Backward: Test → Code → Design → Requirement

### 12.3 Traceability Matrix Example

| Requirement | Design Module | Source File | Test Case | Status |
|-------------|---------------|-------------|-----------|--------|
| REQ-FUNC-001 | door_control | door_control.c | TC-001 | ✓ |
| REQ-SAFE-001 | fail_safe | door_control.c | TC-010 | ✓ |

---

## 13. Quality Gates

### 13.1 Phase Gate Criteria

Each phase has entry and exit criteria (quality gates) that MUST be satisfied:

| Phase | Entry Gate | Exit Gate |
|-------|------------|-----------|
| Requirements | System req available | Software Requirements Specification approved |
| Design | Software Requirements Specification approved | Software Architecture Specification/Software Design Specification approved |
| Implementation | Software Design Specification approved | Code reviewed, tests pass |
| Integration | Unit tests pass | Integration tests pass |
| Validation | Integration complete | Customer acceptance |

### 13.2 Quality Gate Reviews

All quality gates require:
- [ ] Deliverables complete
- [ ] Reviews passed
- [ ] Traceability verified
- [ ] Quality metrics met
- [ ] Approvals obtained

---

## 14. Documentation Requirements

### 14.1 Mandatory Documents by Phase

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

### 14.2 Document Templates

Templates available in:
- `docs/templates/` - Generic templates
- `.opencode/skills/en50128-documentation/` - EN 50128 specific templates

---

## 15. Tool Qualification

### 15.1 Tool Categories (EN 50128 Section 6.7)

**T1**: Tools generating code → Requires qualification
**T2**: Tools supporting testing → May require qualification
**T3**: Development tools → Typically no qualification required

### 15.2 Tools Used in This Workspace

| Tool | Category | Qualification Required | Status |
|------|----------|------------------------|--------|
| GCC | T1 | Yes (SIL 3-4) | Industry accepted |
| Unity | T2 | Recommended | Open source |
| Cppcheck | T3 | No | - |
| PC-lint Plus | T3 | No | - |
| gcov/lcov | T2 | Recommended | Industry accepted |

---

## 16. Configuration Management

### 16.1 Configuration Management Agent

**Agent:** Configuration Manager (`/cm`) - EN 50128 Section 6.6, Table A.9

**CRITICAL:** Configuration Management is **MANDATORY for ALL SIL levels (0, 1, 2, 3, 4)**

### 16.2 Version Control

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

### 16.3 Baseline Management

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

### 16.4 Change Management

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
- Led by Project Manager (`/pm`)
- Configuration Manager (`/cm`) - secretary
- Technical representatives (DES, IMP, TST, VER)
- Safety Engineer (`/saf`) - for safety-critical changes

### 16.5 Traceability Management

**Configuration Manager SHALL maintain traceability matrices:**
- Requirements → Design
- Design → Code
- Requirements → Tests
- All bidirectional links

**Mandatory for SIL 3-4** (Table A.9, Technique 7 - Traceability)

### 16.6 Configuration Management Tools

Use Configuration Manager agent for:
```bash
/cm  # Version control operations
/cm  # Baseline creation and management
/cm  # Change request processing
/cm  # Traceability matrix updates
/cm  # Configuration audits (PCA/FCA)
```

### 16.7 EN 50128 Techniques/Measures (Table A.9 - CM subset)

| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Reference |
|-----------|-------|---------|---------|-----------|
| Software Configuration Management | **M** | **M** | **M** | D.48 |
| Traceability | R | HR | **M** | D.58 |
| Data Recording and Analysis | HR | HR | **M** | D.12 |

**Key:** M = Mandatory, HR = Highly Recommended, R = Recommended

**CRITICAL:** SCM is MANDATORY for ALL SIL levels.

---

## 17. SIL-Specific Requirements Summary

### 17.1 SIL 0-1 (Low Safety Integrity)

| Aspect | Requirement |
|--------|-------------|
| Lifecycle | V-Model recommended |
| Independence | Not required |
| Coverage | 80% statement, 70% branch |
| MISRA C | Recommended |
| Complexity | ≤ 20 |

### 17.2 SIL 2 (Medium Safety Integrity)

| Aspect | Requirement |
|--------|-------------|
| Lifecycle | V-Model mandatory |
| Independence | Highly recommended |
| Coverage | 100% statement, 100% branch |
| MISRA C | Mandatory |
| Complexity | ≤ 15 |
| Static Analysis | Mandatory |

### 17.3 SIL 3-4 (High Safety Integrity)

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

## 18. References

### 18.1 Standards
- EN 50128:2011 - Railway applications - Software for railway control and protection systems
- EN 50126:2017 - Railway applications - RAMS
- IEC 61508 - Functional safety
- MISRA C:2012 - Guidelines for the use of C

### 18.2 Related Documents
- `AGENTS.md` - Role-based agents including COD
- `.opencode/commands/cod.md` - Lifecycle Coordinator agent definition
- `.opencode/skills/en50128-lifecycle-coordination/` - COD patterns and workflows
- `.opencode/skills/` - Domain-specific skills for all lifecycle phases
- `.opencode/commands/` - Agent command definitions (req, des, imp, tst, int, ver, val, saf, qua, cm, pm)
- `docs/EN50128-Compliance-Guide.md` - Compliance checklist

---

## 19. Revision History

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2026-02-06 | EN50128 Team | Initial lifecycle definition |
| 1.1 | 2026-02-18 | EN50128 Team | Added Lifecycle Coordinator (COD) orchestration, phase gate checkpoints for all 8 phases, updated V-Model diagram |

---

**Document Status**: Approved  
**Next Review**: [Date]  
**Approval**: [Signature]
