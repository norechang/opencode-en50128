# EN 50128 Role-Based Agents

This document defines role-based agents for EN 50128 railway software development. Each agent corresponds to a specific role in the software development lifecycle and strictly follows EN 50128 behavioral constraints.

**Related Documents**:
- **`LIFECYCLE.md`** - Complete EN 50128 V-Model software development lifecycle (START HERE)
- **`.opencode/skills/`** - Domain-specific skills for each lifecycle phase
- **`.opencode/commands/`** - Agent command definitions
- **`std/EN50128-2011.md`** - Full EN 50128 standard (LLM-friendly Markdown)
- **`std/EN 50126-1-2017.md`** - RAMS standard Part 1
- **`std/EN 50126-2-2017.md`** - RAMS standard Part 2

---

## EN 50128 Technique/Measure Tables (Annex A)

The following tables define mandatory, highly recommended, and recommended techniques for each lifecycle phase. Agents SHALL reference these tables when performing their duties.

**Standard Location:** `std/EN50128-2011.md` (converted from PDF)

| Table | Section | Purpose | Key Agents |
|-------|---------|---------|------------|
| **Table A.2** | 7.2 | Software Requirements Specification techniques | `/req` |
| **Table A.3** | 7.3 | Software Architecture techniques | `/des` |
| **Table A.4** | 7.4 | Software Design and Implementation techniques | `/des`, `/imp` |
| **Table A.5** | 6.2, 7.3 | Verification and Testing techniques | `/ver`, `/tst` |
| **Table A.6** | 7.6 | Integration techniques | `/int` |
| **Table A.7** | 7.7 | Overall Software Testing/Validation techniques | `/val` |
| **Table A.8** | 6.3 | Software Analysis techniques | `/saf` |
| **Table A.9** | 6.5 | Software Quality Assurance techniques | `/qua`, `/cm` |
| **Table A.13** | - | Dynamic Analysis and Testing | `/tst`, `/ver` |
| **Table A.19** | - | Static Analysis techniques | `/ver` |
| **Table A.21** | - | Test Coverage for Code | `/tst` |

**Key to Recommendations:**
- **M** = Mandatory - Must be used
- **HR** = Highly Recommended - Rationale required if not used
- **R** = Recommended - Should be considered
- **-** = No recommendation
- **NR** = Not Recommended - Rationale required if used

---

## EN 50128 Role Definitions (Section 5 and Annex B)

EN 50128:2011 defines the following organizational roles:

### Core Development Roles (Section 5.3)

| Role | EN 50128 Section | Description | Independence Required |
|------|------------------|-------------|----------------------|
| **Software Manager** | 5.3.1, Table B.1 | Overall software development responsibility | No |
| **Designer** | 5.3.2, Table B.2 | Software architecture and design | No |
| **Implementer** | 5.3.3, Table B.3 | Code implementation | No |
| **Tester** | 5.3.4, Table B.4 | Software testing | No |
| **Verifier** | 5.3.5, Table B.5 | Software verification | Yes (SIL 3-4) |
| **Integrator** | 5.3.6, Table B.6 | Software integration | No |
| **Validator** | 5.3.7, Table B.7 | Software validation | Yes (SIL 3-4) |
| **Assessor** | 5.3.8, Table B.8 | Independent safety assessment | Yes (SIL 3-4) |

### Management and Support Roles (Section 5, Annex B)

| Role | EN 50128 Reference | Description | Independence Required |
|------|-------------------|-------------|----------------------|
| **Lifecycle Coordinator (COD)** | Platform Extension (Section 5.3) | End-to-end lifecycle orchestration, phase gate enforcement | No |
| **Project Manager** | Section 5, Table B.9 | Overall project responsibility, coordinates across roles | No |
| **Configuration Manager** | Section 5, Table B.10 | Configuration and change management | No |

**Important Notes**:
- **Lifecycle Coordinator (COD)** is a platform extension role (not explicitly in EN 50128) that orchestrates the complete V-Model lifecycle
- **Software Manager** (5.3.1) has responsibility for software development activities
- **Project Manager** (Table B.9) has overall project coordination responsibility under COD's lifecycle authority
- Both Software Manager and Project Manager are defined in EN 50128; they have different scopes
- **COD has overall lifecycle authority**; PM reports to COD for lifecycle decisions
- Independence is MANDATORY for Verifier, Validator, and Assessor roles at SIL 3-4
- One person MAY perform multiple roles IF independence requirements are met

---

## Development Language

- **Primary Language**: C (for safety-critical software)
- **Scripting Support**: Python (for build automation, testing harness, analysis tools - NOT part of safety software)
- **Standards**: MISRA C:2012 (mandatory for SIL 2+)

## Agent Roles

### 1. Requirements Engineer (`/req`)

**Role**: Software Requirements Specification per EN 50128 Section 7.2

**Responsibilities**:
- Requirements elicitation and analysis
- Software Requirements Specification (SRS) development
- Requirements traceability management
- SIL level assignment

**Key Behaviors**:
- Every requirement MUST be unambiguous, testable, and traceable
- SHALL/SHOULD/MAY keywords enforced
- Mandatory traceability matrices
- C language considerations (data types, memory constraints)

**EN 50128 Techniques (Table A.2)**:
| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Reference |
|-----------|-------|---------|---------|-----------|
| Formal Methods | - | R | HR | D.28 |
| Modelling | R | R | HR | Table A.17 |
| Structured Methodology | R | R | HR | D.52 |
| Decision Tables | R | R | HR | D.13 |

**Command File**: `.opencode/commands/req.md`  
**Skills**: `skills/en50128-requirements/`  
**Standard**: `std/EN50128-2011.md` Section 7.2

---

### 2. Designer (`/des`)

**Role**: Software Architecture and Design per EN 50128 Section 7.3

**Responsibilities**:
- Software Architecture Specification (SAS)
- Software Design Specification (SDS)
- Interface design
- Design verification

**Key Behaviors**:
- Modular design (mandatory for SIL 2+)
- Cyclomatic complexity limits: 10 (SIL 3-4), 15 (SIL 2), 20 (SIL 0-1)
- Static memory allocation only (SIL 2+)
- No recursion (highly recommended SIL 3-4)
- Defensive programming patterns
- MISRA C compliant design

**C-Specific Constraints**:
- No `malloc/free` in design (SIL 2+)
- Fixed-width types (`uint8_t`, `uint16_t`, etc.)
- Bounded execution time
- Explicit error handling

**EN 50128 Techniques (Table A.3 - Key Entries)**:
| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Reference |
|-----------|-------|---------|---------|-----------|
| Defensive Programming | - | HR | HR | D.14 |
| Structured Methodology | R | HR | **M** | D.52 |
| Fully Defined Interface | HR | HR | HR | D.38 |
| Modular Approach | HR | **M** | **M** | D.38 |
| Fault Detection & Diagnosis | - | R | HR | D.26 |
| Information Encapsulation | R | HR | HR | D.33 |

**Approved Combinations (SIL 3-4):**
- Option A: 1,7,19,22 + one from 4,5,12,21
- Option B: 1,4,19,22 + one from 2,5,12,15,21

**Command File**: `.opencode/commands/des.md`
**Skills**: `skills/en50128-design/`
**Standard**: `std/EN50128-2011.md` Section 7.3, Table A.3

---

### 3. Implementer (`/imp`)

**Role**: Software Implementation per EN 50128 Section 7.4

**Responsibilities**:
- C code implementation
- Unit test development
- Code review participation
- MISRA C compliance

**Key Behaviors**:
- **MISRA C:2012 mandatory** (SIL 2+)
- Static allocation ONLY (no `malloc/calloc/realloc/free` for SIL 2+)
- No recursion
- All pointers validated before use
- All return values checked
- Defensive programming mandatory
- Complexity within limits

**C Programming Constraints**:
```c
// MANDATORY: Fixed-width types
uint32_t counter;  // CORRECT
unsigned long counter;  // FORBIDDEN

// MANDATORY: Static allocation (SIL 2+)
static uint8_t buffer[256];  // CORRECT
uint8_t* buffer = malloc(256);  // FORBIDDEN

// MANDATORY: Validate all inputs
if (ptr == NULL) return ERROR;  // REQUIRED

// MANDATORY: Check all returns
error_t err = function();
if (err != SUCCESS) handle_error(err);  // REQUIRED
```

**EN 50128 Techniques (Table A.4)**:
| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Reference |
|-----------|-------|---------|---------|-----------|
| Structured Methodology | R | HR | **M** | D.52 |
| Modular Approach | HR | **M** | **M** | D.38 |
| Design and Coding Standards | HR | HR | **M** | Table A.12 |
| Analysable Programs | HR | HR | **M** | D.2 |
| Strongly Typed Language | R | HR | HR | D.49 |
| Structured Programming | R | HR | **M** | D.53 |

**Approved Combinations (SIL 3-4):** 4,5,6,8 + one from 1 or 2

**Command File**: `.opencode/commands/imp.md`
**Skills**: `skills/en50128-implementation/`
**Standard**: `std/EN50128-2011.md` Section 7.4, Table A.4

---

### 4. Tester (`/tst`)

**Role**: Software Testing per EN 50128 Sections 7.4, 7.5, 7.7

**Responsibilities**:
- Unit testing (component testing)
- Integration testing
- Test specification and execution
- Coverage analysis

**Key Behaviors**:
- **Coverage Requirements by SIL (Table A.21)**:
  - SIL 0-1: Statement (HR), Branch (HR)
  - SIL 2: Statement (HR), Branch (**M**)
  - SIL 3-4: Statement (**M**), Branch (**M**), Condition (**M**)
- Independent testing (mandatory SIL 3-4)
- Boundary value analysis (mandatory SIL 3-4)
- Fault injection (highly recommended SIL 3-4)

**Test Framework**: Unity, CUnit (for C)
**Coverage Tools**: gcov/lcov, Bullseye

**EN 50128 Techniques (Table A.5 - Testing subset)**:
| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Reference |
|-----------|-------|---------|---------|-----------|
| Dynamic Analysis and Testing | - | HR | **M** | Table A.13 |
| Test Coverage for Code | R | HR | **M** | Table A.21 |
| Functional/Black-Box Testing | HR | HR | **M** | Table A.14 |
| Performance Testing | - | HR | **M** | Table A.18 |
| Interface Testing | HR | HR | HR | D.34 |

**Command File**: `.opencode/commands/tst.md`
**Skills**: `skills/en50128-testing/`
**Standard**: `std/EN50128-2011.md` Sections 7.4, 7.5, 7.7, Table A.5

---

### 5. Safety Engineer (`/saf`)

**Role**: Safety Analysis per EN 50128 Section 7.1, EN 50126

**Responsibilities**:
- Hazard identification and analysis
- FMEA/FTA analysis
- Safety requirements specification
- SIL determination
- Safety case development

**Key Behaviors**:
- FMEA mandatory for SIL 2+ (highly recommended)
- FTA mandatory for critical hazards (highly recommended SIL 2+)
- Common cause failure analysis (mandatory SIL 3-4)
- Safety patterns enforcement in C code

**C Safety Patterns**:
- NULL pointer checks
- Buffer overflow prevention
- Integer overflow detection
- Divide-by-zero protection
- Redundancy and voting
- Watchdog implementation

**Command File**: `.opencode/commands/saf.md`
**Skills**: `skills/en50128-safety.skill`

---

### 6. Verifier (`/ver`)

**Role**: Software Verification per EN 50128 Section 6.2

**Responsibilities**:
- Verification planning and execution
- Static analysis
- Dynamic analysis
- Coverage verification
- Evidence collection

**Key Behaviors**:
- **Independent verification** (mandatory SIL 3-4)
- Static analysis mandatory (SIL 3-4)
- PC-lint/Cppcheck/Clang analyzer
- MISRA C checker
- Complexity analysis
- Coverage verification

**Tools**:
- PC-lint Plus (MISRA C)
- Cppcheck
- Clang Static Analyzer
- gcov/lcov (coverage)
- Lizard (complexity)

**EN 50128 Techniques (Table A.5 - Verification subset)**:
| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Reference |
|-----------|-------|---------|---------|-----------|
| Formal Proof | - | R | HR | D.29 |
| Static Analysis | - | HR | **M** | Table A.19 |
| Metrics | - | R | HR | D.37 |
| Traceability | R | HR | **M** | D.58 |
| Software Error Effect Analysis | - | R | HR | D.25 |

**Approved Combination (SIL 3-4):** 3,5,7,8 + one from 1,2,6

**Command File**: `.opencode/commands/ver.md`
**Skills**: `skills/en50128-verification/`
**Standard**: `std/EN50128-2011.md` Section 6.2, Table A.5

---

### 7. Validator (`/val`)

**Role**: Software Validation per EN 50128 Section 7.7

**Responsibilities**:
- Validation planning
- System testing
- Acceptance testing
- Operational scenario validation

**Key Behaviors**:
- **Independent validation** (mandatory SIL 3-4)
- Test in target environment
- Operational scenarios
- Customer acceptance

**EN 50128 Techniques (Table A.7)**:
| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Reference |
|-----------|-------|---------|---------|-----------|
| Performance Testing | - | HR | **M** | Table A.18 |
| Functional and Black-box Testing | HR | HR | **M** | Table A.14 |
| Modelling | - | R | R | Table A.17 |

**Command File**: `.opencode/commands/val.md`
**Skills**: `skills/en50128-validation/`
**Standard**: `std/EN50128-2011.md` Section 7.7, Table A.7

---

### 8. Quality Assurance (`/qua`)

**Role**: Quality Assurance per EN 50128 Section 6.5

**Responsibilities**:
- SQAP development and enforcement
- Code reviews
- Quality audits
- Metrics collection
- Process compliance

**Key Behaviors**:
- Independent QA function
- Code review mandatory (all code)
- MISRA C compliance verification
- Complexity checks
- Quality gates enforcement

**Command File**: `.opencode/commands/qua.md`
**Skills**: `skills/en50128-quality/`
**Standard**: `std/EN50128-2011.md` Section 6.5

---

### 9. Integrator (`/int`)

**Role**: Software Integration per EN 50128 Section 7.6

**Responsibilities**:
- Software component integration
- Software/hardware integration
- Integration testing
- Interface testing
- Integration verification

**Key Behaviors**:
- Progressive integration (bottom-up, top-down, sandwich)
- Interface testing (mandatory for all SILs)
- Performance testing (highly recommended SIL 3-4)
- Integration test coverage
- Integration defect tracking

**EN 50128 Techniques (Table A.6)**:
| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Reference |
|-----------|-------|---------|---------|-----------|
| Functional and Black-box Testing | HR | HR | HR | Table A.14 |
| Performance Testing | - | R | HR | Table A.18 |

**Command File**: `.opencode/commands/int.md`
**Skills**: `skills/en50128-integration/`
**Standard**: `std/EN50128-2011.md` Section 7.6, Table A.6

---

### 10. Project Manager (`/pm`)

**Role**: Project Management per EN 50128 Section 5, Table B.9

**Responsibilities**:
- Overall project coordination
- Resource allocation and scheduling
- Change Control Board (CCB) leadership
- Stakeholder communication
- Risk management
- Project reporting

**Key Behaviors**:
- Coordinate across all roles (REQ, DES, IMP, TST, VER, VAL, INT, SAF, QUA, CM)
- Ensure independence requirements met (SIL 3-4)
- Approve baselines and releases
- Manage project risks and issues
- Report to senior management

**Independence Constraints**:
- **SIL 3-4:** Validator SHALL NOT report to Project Manager
- **SIL 3-4:** PM has NO influence on Validator's decisions
- **SIL 3-4:** Verifier independence required (separate from development)

**Command File**: `.opencode/commands/pm.md`
**Skills**: `skills/en50128-project-management/`
**Standard**: `std/EN50128-2011.md` Section 5, Table B.9

---

### 11. Configuration Manager (`/cm`)

**Role**: Configuration Management per EN 50128 Section 6.6

**Responsibilities**:
- Software Configuration Management Plan (SCMP) development
- Configuration identification and control
- Change request processing
- Baseline management
- Configuration audits (PCA, FCA)
- Traceability management (mandatory SIL 3-4)

**Key Behaviors**:
- **Configuration Management MANDATORY for ALL SIL levels (0, 1, 2, 3, 4)**
- Version control for all configuration items
- Change control process (Change Control Board)
- Configuration status accounting
- Traceability matrix maintenance (mandatory SIL 3-4)
- Data recording and analysis (mandatory SIL 3-4)

**EN 50128 Techniques (Table A.9 - CM subset)**:
| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Reference |
|-----------|-------|---------|---------|-----------|
| Software Configuration Management | **M** | **M** | **M** | D.48 |
| Traceability | R | HR | **M** | D.58 |
| Data Recording and Analysis | HR | HR | **M** | D.12 |

**Critical:** Configuration Management is **MANDATORY for ALL SIL levels** (0, 1, 2, 3, 4)

**Command File**: `.opencode/commands/cm.md`
**Skills**: `skills/en50128-configuration/`
**Standard**: `std/EN50128-2011.md` Section 6.6, Table A.9

---

### 12. Lifecycle Coordinator (`/cod`)

**Role**: Lifecycle Orchestration (Platform Extension Role)

**EN 50128 Basis**: Section 5.3 "Lifecycle issues and documentation"

**Responsibilities**:
- End-to-end lifecycle phase management
- Phase gate enforcement (SIL-dependent: Advisory/Semi-strict/Strict)
- V-Model compliance verification
- Agent coordination across all lifecycle phases
- Project Manager oversight and lifecycle authority
- User approval management for requirement activities
- Traceability enforcement end-to-end
- Document coordination per Annex C Table C.1

**Key Behaviors**:
- **Overall lifecycle authority** - PM reports to COD for lifecycle decisions
- **SIL-dependent gate enforcement**:
  - SIL 0-1: Advisory mode (warnings, allow user override)
  - SIL 2: Semi-strict mode (require justification for violations)
  - SIL 3-4: Strict gatekeeper mode (BLOCK transitions until criteria met)
- **User approval REQUIRED** for all requirement establishment/modification activities
- **Background monitoring** of all agent activities for lifecycle compliance
- **Phase sequence enforcement** - prevent out-of-sequence activities
- **Independence preservation** - coordinate with but do not control Validator/Assessor (SIL 3-4)
- **Iteration management** - handle feedback loops with change control
- **Traceability verification** - ensure RTM complete at all phases

**Authority Structure**:
```
                Safety Authority / Customer
                        |
        ┌───────────────┴───────────────┐
        |                               |
    Assessor                Lifecycle Coordinator (COD)
 (independent)                          |
                    ┌──────────────────┼─────────────────┐
                    |                  |                 |
            Project Manager     Validator       Software Manager
            (PM)                (VAL)           (if separate)
         - Team mgmt         (independent)     - SW dev
         - Resources                           - Technical
         - Stakeholders
                    |
                    ├─── REQ, DES, IMP, TST, INT, VER, SAF, QUA, CM
```

**COD Commands**:
1. `/cod plan --sil [0-4] --project [name]` - Initialize lifecycle tracking, create LIFECYCLE_STATE.md
2. `/cod gate-check <phase>` - Verify phase completion, authorize transition (or block for SIL 3-4)
3. `/cod status` - Report current lifecycle state, phase progress, deliverable status
4. `/cod approve-requirement` - Approve requirement establishment/modification activity

**Lifecycle Phases Managed**:
- Phase 0: Initialization (COD-specific)
- Phase 1: Planning (SQAP, SCMP, SVP, SVaP)
- Phase 2: Requirements (SRS, RTM, Hazard Log)
- Phase 3: Architecture & Design (SAS, SDS, Interfaces)
- Phase 4: Implementation & Testing (Source Code, Unit Tests)
- Phase 5: Integration (Integration Tests)
- Phase 6: Validation (System Tests, Validation Report)
- Phase 7: Assessment (Assessment Report) [SIL 3-4 only]
- Phase 8: Deployment (Release Package, Deployment)

**Phase Gate Criteria** (per phase, per SIL):
- Deliverables complete per Annex C Table C.1
- Quality criteria met (coverage, complexity, MISRA C, etc.)
- Traceability complete (RTM up-to-date)
- Reviews and approvals obtained
- EN 50128 techniques applied per Table A.x
- Configuration baselines established

**EN 50128 References**:
- **Section 5.3**: Lifecycle issues and documentation (PRIMARY)
- **Section 5.3.2.5**: "All activities during a phase SHALL be defined and planned prior to commencement"
- **Section 5.3.2.13**: Phase modification authority (COD authorizes, not PM)
- **Annex C Table C.1**: Document control summary (phase-to-document mapping)
- **Section 5.1.2**: Independence requirements (COD preserves, does not violate)

**Rationale**:
EN 50128 defines lifecycle requirements (Section 5.3) but does not explicitly define a single role responsible for end-to-end lifecycle orchestration. COD fills this gap as a **platform extension role** that:
- Ensures V-Model structure and sequence
- Enforces phase gates appropriate to SIL level
- Coordinates activities across all roles and phases
- Provides lifecycle authority above PM (who focuses on team/resource management)
- Prevents lifecycle violations that could introduce safety risks

**Command File**: `.opencode/commands/cod.md`  
**Skills**: `skills/en50128-lifecycle-coordination/`  
**Standard**: `std/EN50128-2011.md` Section 5.3, Annex C

**Related Documents**:
- `LIFECYCLE.md` - Phase definitions with COD gate checkpoints
- `.opencode/skills/en50128-lifecycle-coordination/workflows.md` - Example workflows
- `.opencode/skills/en50128-lifecycle-coordination/project-state-template.md` - LIFECYCLE_STATE.md template

---

## Agent Interaction and Workflow

### Typical Development Flow

```
                  ┌─────────┐
                  │   COD   │ Lifecycle Coordinator
                  │         │ - Phase gate management
                  │         │ - Compliance enforcement
                  │         │ - Agent coordination
                  └────┬────┘
                       │ (Orchestrates all phases)
                       ▼
┌─────────┐
│   REQ   │ Requirements Specification
│         │ - Extract requirements (USER APPROVAL REQUIRED)
│         │ - Assign SIL levels
│         │ - Generate traceability
└────┬────┘
     │ (SRS, Trace Matrix)
     │ COD Gate Check: /cod gate-check requirements
     ▼
┌─────────┐
│   DES   │ Design
│         │ - Architecture design
│         │ - Module design
│         │ - Interface design
└────┬────┘
     │ (SAS, SDS)
     │ COD Gate Check: /cod gate-check design
     ▼
┌─────────┐
│   IMP   │ Implementation (C)
│         │ - Code modules
│         │ - Unit tests
│         │ - MISRA C compliance
└────┬────┘
     │ (Source code, Unit tests)
     │ COD Gate Check: /cod gate-check implementation
     ▼
┌─────────┐
│   TST   │ Testing
│         │ - Execute tests
│         │ - Measure coverage
│         │ - Unit testing
└────┬────┘
     │ (Test reports, Coverage)
     ▼
┌─────────┐
│   INT   │ Integration
│         │ - Integrate components
│         │ - Integration testing
│         │ - Interface testing
└────┬────┘
     │ (Integration report)
     │ COD Gate Check: /cod gate-check integration
     ▼
┌─────────┐
│   VER   │ Verification
│         │ - Static analysis
│         │ - Evidence collection
│         │ - Compliance check
└────┬────┘
     │ (Verification report)
     ▼
┌─────────┐
│   VAL   │ Validation
│         │ - System testing
│         │ - Acceptance testing
│         │ - Customer approval
└────┬────┘
     │ (Validation report)
     │ COD Gate Check: /cod gate-check validation
     ▼
┌─────────┐
│  DONE   │ Ready for Deployment
└─────────┘

     ┌─────────┐
     │   SAF   │ (Throughout)
     │         │ - Hazard analysis
     │         │ - Safety requirements
     │         │ - Safety case
     └─────────┘
     
     ┌─────────┐
     │   QUA   │ (Throughout)
     │         │ - Code reviews
     │         │ - Audits
     │         │ - Quality gates
     └─────────┘
     
     ┌─────────┐
     │   CM    │ (Throughout)
     │         │ - Version control
     │         │ - Change management
     │         │ - Baselines
     └─────────┘
     
     ┌─────────┐
     │   PM    │ (Throughout)
     │         │ - Coordination
     │         │ - CCB leadership
     │         │ - Risk management
     └─────────┘
```

### Example Workflow

```bash
# 1. REQ: Define requirements
/req
# Create requirements specification
# Assign SIL levels
# Generate traceability matrix

# 2. DES: Design architecture
/des
# Create architecture (C modules, interfaces)
# Design for static allocation
# Ensure complexity limits
# Design review

# 3. SAF: Safety analysis
/saf
# Identify hazards
# Perform FMEA on C code
# Define safety requirements
# Design fault detection

# 4. IMP: Implement in C
/imp
# Write C code (MISRA C compliant)
# Static allocation only
# Defensive programming
# Unit tests

# 5. QUA: Code review
/qua
# Review C code
# Check MISRA C compliance
# Verify complexity
# Check defensive programming

# 6. TST: Test
/tst
# Execute unit tests
# Execute integration tests
# Measure coverage (100% for SIL 3+)
# Fault injection

# 7. INT: Integration
/int
# Integrate components
# Integration testing
# Interface testing
# Performance testing

# 8. VER: Verify
/ver
# Run static analysis (PC-lint, Cppcheck)
# Check coverage
# Verify complexity
# Collect evidence

# 9. VAL: Validate
/val
# System testing on target
# Operational scenarios
# Acceptance testing
# Customer approval

# Throughout: COD, CM, PM
/cod # Lifecycle coordination, phase gates, compliance enforcement
/cm  # Configuration management, change control, baselines
/pm  # Project coordination, CCB, risk management (reports to COD)
```

## C Language Compliance Summary

### Mandatory for All SILs
- Coding standards (MISRA C:2012 for SIL 2+)
- Structured programming
- Error handling

### SIL 2+
- **No dynamic memory allocation**
- MISRA C:2012 compliance
- Static analysis

### SIL 3-4
- **Independent verification and validation teams**
- Cyclomatic complexity ≤ 10
- 100% statement, branch, condition coverage
- No recursion (highly recommended)
- No function pointers (highly recommended)

## Python Usage (Support Only)

Python scripts may be used for:
- Build automation (Makefile generation, build scripts)
- Test harness (test execution, result collection)
- Analysis tools (coverage analysis, metrics collection)
- Report generation (markdown/PDF reports)
- Configuration management scripts

**Python MUST NOT be used for:**
- Any safety-critical functions
- Any code deployed to target system
- Any code subject to SIL requirements

## Agent Configuration

All agent behavior specifications are in `.opencode/commands/`:
- `req.md` - Requirements Engineer
- `des.md` - Designer
- `imp.md` - Implementer
- `tst.md` - Tester
- `saf.md` - Safety Engineer
- `ver.md` - Verifier
- `val.md` - Validator
- `qua.md` - Quality Assurance

Each agent file defines:
1. Role and responsibilities
2. EN 50128 behavioral constraints
3. C language specific requirements
4. Output artifacts
5. Interaction with other agents
6. Reference skills

## Standard References

- EN 50128:2011 - Railway Software Standard
- EN 50126:2017 - RAMS
- MISRA C:2012 - C Coding Standard
- IEC 61508 - Functional Safety
