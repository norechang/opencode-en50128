# EN 50128 Role-Based Agents

This document defines role-based agents for EN 50128 railway software development. Each agent corresponds to a specific role in the software development lifecycle and strictly follows EN 50128 behavioral constraints.

## Agent Invocation Syntax

Agents are invoked using the `@agent` syntax in OpenCode:

```
@cod plan --sil 3 --project MyProject
@pm execute-phase 2
@req create-srs --based-on assets/sample_system/System-Requirements-Specification.md
@ver verify-phase 4 --sil 3
@qua review-document docs/SRS.md --type srs --sil 3
```

**Normal workflow**: You invoke only `@cod` and `@pm`. They orchestrate all other agents internally.  
**Direct invocation**: You may invoke any agent directly for targeted tasks.

See `docs/USER-GUIDE.md` for complete usage instructions and the V-Model example.

**Related Documents**:
- **`docs/USER-GUIDE.md`** - Complete usage guide with agent commands and V-Model example (START HERE)
- **`LIFECYCLE.md`** - Complete EN 50128 V-Model software development lifecycle
- **`TOOLS.md`** - Comprehensive tool catalog with usage information for agents (CRITICAL)
- **`.opencode/agents/`** - Agent definition files (one per role)
- **`.opencode/skills/`** - Domain-specific skills loaded internally by agents
- **`std/EN50128-2011.md`** - Full EN 50128 standard (LLM-friendly Markdown)
- **`std/EN 50126-1-2017.md`** - RAMS standard Part 1
- **`std/EN 50126-2-2017.md`** - RAMS standard Part 2

---

## Agent Tool Usage Protocol

**CRITICAL**: Before invoking ANY tool, agents MUST follow this protocol to ensure effective tool selection and EN 50128 compliance.

### Tool Examination Workflow

```
┌─────────────────────────────────────────────────────────────┐
│ STEP 1: IDENTIFY TASK REQUIREMENTS                          │
│ - What is the task? (static analysis, coverage, etc.)       │
│ - What SIL level? (0, 1, 2, 3, 4)                          │
│ - What EN 50128 table applies? (A.2-A.21)                  │
└─────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────┐
│ STEP 2: CONSULT TOOLS.md                                    │
│ - Read TOOLS.md to identify available tools                 │
│ - Check tool classification (M/HR/R for SIL level)          │
│ - Check Tool Confidence Level (T1/T2/T3)                    │
└─────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────┐
│ STEP 3: VERIFY TOOL AVAILABILITY                            │
│ - Check if tool is installed: which <tool_name>             │
│ - Verify version meets requirements                         │
│ - Check qualification status (for T2/T3 tools)              │
└─────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────┐
│ STEP 4: SELECT MOST EFFECTIVE TOOL                          │
│ - Prefer MANDATORY tools for SIL level                      │
│ - Use multiple tools for thoroughness (SIL 3+)              │
│ - Consider tool output format (XML/JSON for automation)     │
│ - Select custom EN50128 tools when applicable               │
└─────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────┐
│ STEP 5: EXECUTE TOOL WITH PROPER FLAGS                      │
│ - Use SIL-appropriate flags and thresholds                  │
│ - Generate machine-readable output                          │
│ - Document tool invocation in agent deliverable             │
└─────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────┐
│ STEP 6: VERIFY AND DOCUMENT RESULTS                         │
│ - T1: Inspect output for correctness                        │
│ - T2: Cross-reference with other tools                      │
│ - T3: Verify qualification evidence exists                  │
│ - Include results in agent deliverable                      │
└─────────────────────────────────────────────────────────────┘
```

### Tool Selection Decision Matrix

| Task | SIL 3 MANDATORY Tool(s) | Alternative/Additional | Custom EN50128 Tool |
|------|-------------------------|------------------------|---------------------|
| **Static Analysis** | Cppcheck, Clang | Splint, PC-lint Plus | check_misra.py |
| **Complexity Analysis** | Lizard (CCN ≤ 10) | - | - |
| **Coverage Analysis** | gcov, lcov | Bullseye | - |
| **MC/DC Analysis** | Manual + gcov | Bullseye | mcdc_analyzer.py (RECOMMENDED) |
| **Memory Analysis** | Valgrind (HR) | AddressSanitizer | - |
| **Version Control** | Git | - | workspace.py |
| **Build** | gcc, make | - | - |
| **Documentation** | - | Doxygen | enhelp.py |

### Example: Verifier (VER) Agent Tool Usage

**Scenario**: VER agent needs to perform static analysis for SIL 3 project

```python
# STEP 1: Identify requirements
# Task: Static analysis
# SIL: 3
# EN 50128 Reference: Table A.19 (MANDATORY SIL 3-4)

# STEP 2: Consult TOOLS.md
# Read: "MANDATORY Tools (SIL 3)" section
# Find: Cppcheck (MANDATORY), Clang (MANDATORY)

# STEP 3: Verify availability
bash: which cppcheck  # Check Cppcheck installed
bash: which clang     # Check Clang installed

# STEP 4: Select tools
# Decision: Use BOTH Cppcheck AND Clang (multiple tools for SIL 3)

# STEP 5: Execute with proper flags
bash: cppcheck --enable=all --xml --xml-version=2 src/ 2> cppcheck_report.xml
bash: scan-build -o analysis_results make

# STEP 6: Document results
# Include in Verification Report:
# - Tool versions (Cppcheck 2.13.0, Clang 18.x)
# - Invocation commands
# - Number of issues found
# - Classification of issues (critical/warning/info)
# - Remediation status
```

### Tool Availability Check Commands

Before using a tool, agents should verify installation:

```bash
# Check system tool availability
which gcc && gcc --version
which gcov && gcov --version
which lcov && lcov --version
which cppcheck && cppcheck --version
which clang && clang --version
which valgrind && valgrind --version
which git && git --version

# Check Python tool availability (requires venv active)
source venv/bin/activate
which lizard && lizard --version
python3 tools/mcdc/mcdc_analyzer.py --help
python3 tools/workspace.py --help
python3 tools/enhelp.py --help
```

### Tool Installation References

If a required tool is missing:

```bash
# System tools
./install_tools.sh --check    # Check installation status
./install_tools.sh            # Install all tools
./install_tools.sh --minimal  # Install MANDATORY only

# Python tools
./install_python.sh           # Setup venv and install packages
./install_python.sh --check   # Check Python environment
```

### Agent Responsibilities for Tool Management

| Agent | Tool Responsibilities | Key Tools |
|-------|----------------------|-----------|
| **IMP** | Compilation, unit testing | gcc, make, gcov |
| **TST** | Testing, coverage | gcov, lcov, mcdc_analyzer.py |
| **VER** | Static analysis, complexity | cppcheck, clang, lizard |
| **INT** | Integration builds, memory checks | gcc, make, valgrind |
| **VAL** | System testing, validation | All test tools |
| **QUA** | Quality checks, reviews | All analysis tools |
| **CM** | Version control | git |
| **COD** | Tool compliance verification | All tools |

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
| **V&V Manager (VMGR)** | Platform Extension (Section 5.1.2.10) | Independent V&V authority, manages Verifier team, provides final V&V approval | Yes (SIL 3-4) |
| **Project Manager** | Section 5, Table B.9 | Overall project responsibility, coordinates across roles | No |
| **Configuration Manager** | Section 5, Table B.10 | Configuration and change management | No |

**Important Notes**:
- **Lifecycle Coordinator (COD)** is a platform extension role (not explicitly in EN 50128) that orchestrates the complete V-Model lifecycle
- **V&V Manager (VMGR)** is a platform extension role (based on EN 50128 Section 5.1.2.10e "Verifier can report to Validator") that provides independent V&V authority for SIL 3-4 projects
- **Software Manager** (5.3.1) has responsibility for software development activities
- **Project Manager** (Table B.9) has overall project coordination responsibility under COD's lifecycle authority
- Both Software Manager and Project Manager are defined in EN 50128; they have different scopes
- **COD has overall lifecycle authority**; PM reports to COD for lifecycle decisions
- **VMGR is INDEPENDENT from COD and PM** (SIL 3-4); coordinates with COD but does not report to COD
- Independence is MANDATORY for Verifier, Validator, and Assessor roles at SIL 3-4
- Independence is MANDATORY for VMGR at SIL 3-4 (manages independent V&V team)
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
- Software Requirements Specification development
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

**Skill**: `en50128-requirements`  
**Standard**: `std/EN50128-2011.md` Section 7.2

---

### 2. Designer (`/des`)

**Role**: Software Architecture and Design per EN 50128 Section 7.3

**Responsibilities**:
- Software Architecture Specification
- Software Design Specification
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

**Skill**: `en50128-design`  
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

**Skill**: `en50128-implementation`  
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

**Skill**: `en50128-testing`  
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

**Skill**: `en50128-safety`  
**Standard**: `std/EN50128-2011.md` Section 7.1, EN 50126

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

**Skill**: `en50128-verification`  
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

**Skill**: `en50128-validation`  
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

**Skill**: `en50128-quality`  
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

**Skill**: `en50128-integration`
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
- Monitor project status via LIFECYCLE_STATE.md

**Key Commands**:
- `/pm status` - Overall project status report (reads LIFECYCLE_STATE.md)
- `/pm status <phase-id>` - Specific phase execution status
- `/pm execute-phase <phase-id>` - Automated phase orchestration with QUA flow
- `/pm resolve-defects <phase-id>` - Coordinate defect resolution after VER/VAL rejection

**Independence Constraints**:
- **SIL 3-4:** Validator SHALL NOT report to Project Manager
- **SIL 3-4:** PM has NO influence on Validator's decisions

**Skill**: `en50128-project-management`
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

**Skill**: `en50128-configuration`
**Standard**: `std/EN50128-2011.md` Section 6.6, Table A.9

---

### 12. V&V Manager (`/vmgr`)

**Role**: Verification and Validation Management (Platform Extension Role for SIL 3-4)

**EN 50128 Basis**: Section 5.1.2.10e "Verifier can report to... Validator"

**Responsibilities**:
- Independent V&V authority for SIL 3-4 projects
- Manages Verifier team (VER reports to VMGR)
- Provides final V&V approval/rejection for phase gates
- Coordinates with COD (but does NOT report to COD)
- Ensures independence from development organization (PM, REQ, DES, IMP, INT, TST)
- Reviews and approves all Verification Reports
- Reviews and approves all Validation Reports
- Provides V&V status to COD for gate check decisions

**Key Behaviors**:
- **MANDATORY for SIL 3-4** (highly recommended for SIL 2)
- **Independent authority** - VMGR decisions CANNOT be overridden by COD or PM
- **Reports to Safety Authority / Customer** (not PM, not COD)
- **Coordinates with COD** - provides approval/rejection, COD enforces gate based on VMGR decision
- **Manages VER team** - VER agents report to VMGR (EN 50128 5.1.2.10e)
- **Performs Validation activities** - VMGR acts as Validator role (VAL)
- **Independence preservation** - VMGR SHALL NOT be influenced by project schedule/cost pressures
- **Quality gate enforcement** - VER/VAL reports must pass QUA template compliance before VMGR review

**V&V Workflow (SIL 3-4)**:
1. VER creates Verification Report
2. VER submits to QUA for template compliance check (1 pass)
3. QUA approves/rejects (if rejected, VER fixes and resubmits ONCE)
4. VER submits to VMGR for technical review
5. VMGR reviews and approves/rejects Verification Report
6. VMGR performs Validation activities (as VAL role)
7. VMGR creates Validation Report
8. VMGR submits to QUA for template compliance check (1 pass)
9. QUA approves/rejects (if rejected, VMGR fixes and resubmits ONCE)
10. VMGR informs COD of V&V approval/rejection
11. COD enforces gate based on VMGR decision (CANNOT override)

**Authority Structure**:
```
        Safety Authority / Customer
                |
        ┌───────┴───────┐
        |               |
    COD (Lifecycle)  VMGR (Independent V&V)
        |               |
    PM (Team)       VER (Verification)
        |
    REQ, DES, IMP, INT, TST, QUA, CM, SAF
```

**EN 50128 References**:
- **Section 5.1.2.10e**: "Verifier can report to the Project Manager or to the Validator" (PRIMARY)
- **Section 5.1.2.10f**: "Validator shall not report to the Project Manager" (INDEPENDENCE)
- **Section 5.1.2.8**: "The Validator shall give agreement/disagreement for the software release"
- **Section 5.1.2.10i**: "A person who is Verifier shall neither be Requirements Manager, Designer, Implementer, Integrator, Tester nor Validator"
- **Section 5.1.2.10j**: "A person who is Validator shall neither be Requirements Manager, Designer, Implementer, Integrator, Tester nor Verifier"

**Rationale**:
EN 50128 requires independent Verifier and Validator roles for SIL 3-4 (Section 5.1.2.10) and allows Verifier to report to Validator (5.1.2.10e). VMGR is a **platform extension role** that:
- Formalizes the "Validator manages Verifier" organizational structure
- Provides single point of V&V authority for large SIL 3-4 projects
- Ensures independence from development organization (COD, PM)
- Combines Validator responsibilities with Verifier team management
- Simplifies coordination with COD while preserving independence

**VMGR Commands**:
1. `/vmgr status` - Report V&V status for all phases
2. `/vmgr review-verification <phase>` - Review VER report and approve/reject
3. `/vmgr review-validation <phase>` - Review VAL activities for phase
4. `/vmgr approve-gate <phase>` - Provide V&V approval/rejection to COD
5. `/vmgr independence-check` - Verify independence requirements met

**Skill**: `en50128-vv-management` (planned)
**Standard**: `std/EN50128-2011.md` Section 5.1.2.10

---

### 13. Lifecycle Coordinator (`/cod`)

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
- **Traceability verification** - ensure traceability complete at all phases

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
- Phase 2: Requirements (Software Requirements Specification, traceability, Hazard Log)
- Phase 3: Architecture & Design (Software Architecture Specification, Software Design Specification, Software Interface Specifications)
- Phase 4: Implementation & Testing (Source Code, Unit Tests)
- Phase 5: Integration (Integration Tests)
- Phase 6: Validation (System Tests, Validation Report)
- Phase 7: Assessment (Assessment Report) [SIL 3-4 only]
- Phase 8: Deployment (Release Package, Deployment)

**Phase Gate Criteria** (per phase, per SIL):
- Deliverables complete per Annex C Table C.1
- Quality criteria met (coverage, complexity, MISRA C, etc.)
- Traceability complete (embedded in Software Requirements Specification, up-to-date)
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

**Skill**: `en50128-lifecycle-coordination`  
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
     │ (Software Requirements Specification, Traceability)
     │ COD Gate Check: @cod gate-check phase-2
     ▼
┌─────────┐
│   DES   │ Design
│         │ - Architecture design
│         │ - Module design
│         │ - Interface design
└────┬────┘
     │ (Software Architecture Specification, Software Design Specification)
     │ COD Gate Check: @cod gate-check phase-3
     ▼
┌─────────┐
│   IMP   │ Implementation (C)
│         │ - Code modules
│         │ - Unit tests
│         │ - MISRA C compliance
└────┬────┘
     │ (Source code, Unit tests)
     │ COD Gate Check: @cod gate-check phase-4
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
     │ COD Gate Check: @cod gate-check phase-5
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
     │ COD Gate Check: @cod gate-check phase-6
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
# ── USER INVOKES ONLY TWO COMMANDS ────────────────────────────────────────────

# Initialize lifecycle (COD creates LIFECYCLE_STATE.md)
@cod plan --sil 3 --project MyProject

# Execute each phase (PM orchestrates all agents internally)
@pm execute-phase 1    # Planning: SQAP, SCMP, SVP, SVaP
@cod gate-check phase-1

@pm execute-phase 2    # Requirements: SRS, Hazard Log
@cod gate-check phase-2

@pm execute-phase 3    # Design: SAS, SDS, SIS, FMEA
@cod gate-check phase-3

@pm execute-phase 4    # Implementation + Unit Testing
# PM internally invokes:
#   @imp implement-all --sil 3        → src/, include/
#   @tst create-unit-tests --sil 3    → tests/unit/
#   @tst run-unit-tests --sil 3       → coverage must be 100% (SIL 3)
#   @qua review-code --sil 3          → Code-Review-Report.md (APPROVED)
# COD independently invokes (not PM):
#   @ver verify-phase 4 --sil 3       → Verification-Report-Phase4.md
# VMGR reviews and approves (SIL 3-4)
@cod gate-check phase-4

@pm execute-phase 5    # Integration
# PM internally invokes:
#   @int plan-integration             → Integration-Plan.md
#   @tst create-integration-tests     → tests/integration/
#   @tst run-integration-tests        → test-results/integration/
#   @int create-integration-report    → Integration-Test-Report.md
#   @qua review-document ...          → QA review loop
# COD independently invokes:
#   @ver verify-phase 5 --sil 3       → Verification-Report-Phase5.md
@cod gate-check phase-5

# Phase 6: Validation — COD invokes VAL directly (independence)
# @val validate-phase 6 --sil 3       → Validation-Report.md
@cod gate-check phase-6

# Phase 7: Assessment (SIL 3-4 only)
@cod gate-check phase-7

@pm execute-phase 8    # Deployment: release package, final baseline

@cod finish            # Final compliance check, project archived
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

## Agent-to-Skill Mapping

Each agent **internally loads its skill** when invoked. Users do not load skills directly — agents load them automatically as their first step.

### Core Development Skills

| Agent | `@agent` Syntax | Skill Loaded Internally | EN 50128 Section |
|-------|----------------|------------------------|------------------|
| `@req` | `@req create-srs` | `en50128-requirements` | Section 7.2 |
| `@des` | `@des create-sas` | `en50128-design` | Section 7.3 |
| `@imp` | `@imp implement-all` | `en50128-implementation` | Section 7.4 |
| `@tst` | `@tst run-unit-tests` | `en50128-testing` | Sections 7.4, 7.5, 7.7 |
| `@ver` | `@ver verify-phase 4` | `en50128-verification` | Section 6.2 |
| `@val` | `@val validate-phase 6` | `en50128-validation` | Section 7.7 |
| `@int` | `@int plan-integration` | `en50128-integration` | Section 7.6 |
| `@saf` | `@saf perform-fmea` | `en50128-safety` | Sections 7.1, 6.3 |

### Management and Support Skills

| Agent | `@agent` Syntax | Skill Loaded Internally | EN 50128 Section |
|-------|----------------|------------------------|------------------|
| `@qua` | `@qua review-document` | `en50128-quality` | Section 6.5 |
| `@cm` | `@cm create-baseline` | `en50128-configuration` | Section 6.6 |
| `@cod` | `@cod plan` | `en50128-lifecycle-coordination` | Section 5.3 |
| `@pm` | `@pm execute-phase` | `en50128-project-management` | Section 5, Table B.9 |
| `@vmgr` | `@vmgr review-verification` | (planned: `en50128-vv-management`) | Section 5.1.2.10e |

## Standard References

- EN 50128:2011 - Railway Software Standard
- EN 50126:2017 - RAMS
- MISRA C:2012 - C Coding Standard
- IEC 61508 - Functional Safety

---

## EN 50128 Role Independence Reference

This section provides a quick reference for EN 50128:2011 Section 5 and Annex B organizational role independence requirements.

### Role Independence Matrix

| Role | SIL 0-1 | SIL 2 | SIL 3-4 |
|------|---------|-------|---------|
| Project Manager | No | No | No |
| Software Manager | No | No | No |
| Configuration Manager | No | No | No |
| Designer | No | No | No |
| Implementer | No | No | No |
| Tester | No | HR | HR |
| Verifier | No | HR | **M** |
| Integrator | No | No | No |
| Validator | No | HR | **M** |
| Assessor | N/A | N/A | **M** |

**Legend**: **M** = Mandatory, **HR** = Highly Recommended, **No** = Not required

### Role Combination Rules

**Allowed Combinations** (when independence is not required):

- Software Manager + Designer
- Designer + Implementer
- Implementer + Tester (SIL 0-2 only)
- Integrator + Tester

**Prohibited Combinations** (for SIL 3-4):

- Designer/Implementer + Verifier
- Any development role + Validator
- Any role + Assessor
- Implementer + Tester (own code)

**Best Practice for SIL 3-4 Projects**:
- Separate teams for Development and Verification/Validation
- Independent Assessor (often external to the organization)
- Clear organizational separation with independent reporting lines

### Role Definitions (EN 50128 Section 5, Annex B)

#### Project Manager (Section 5, Table B.9)

**Responsibility**: Overall project responsibility and coordination

**Key Activities**: Overall project planning, coordinate between all roles, resource allocation, schedule management, risk management, stakeholder communication, ensure standards compliance, project-level decision making.

**Independence**: Not required. Oversees the entire project including hardware, system, and software aspects.

#### Software Manager (Section 5.3.1, Table B.1)

**Responsibility**: Overall responsibility for software development activities

**Key Activities**: Establish software development plans, allocate resources, monitor progress, ensure quality assurance, coordinate with other roles, report to management.

**Independence**: Not required. Focuses specifically on software development. In software-only projects, may be the same person as Project Manager.

#### Designer (Section 5.3.2, Table B.2)

**Responsibility**: Software architecture and design

**Key Activities**: Create Software Architecture Specification, create Software Design Specification, define interfaces, apply design techniques per Table A.4, participate in design reviews.

**Independence**: Not required (but designer should not assess their own design). **Agent**: `@des`

#### Implementer (Section 5.3.3, Table B.3)

**Responsibility**: Software implementation (coding)

**Key Activities**: Implement software in C (MISRA C:2012 for SIL 2+), follow coding standards, implement defensive programming, participate in code reviews, create unit tests.

**Independence**: Not required (but implementer should not test their own code alone). **Agent**: `@imp`

#### Tester (Section 5.3.4, Table B.4)

**Responsibility**: Software testing

**Key Activities**: Develop test specifications, execute tests, record test results, perform coverage analysis, report defects.

**Independence**: Not required for SIL 0-2; Highly recommended for SIL 3-4. **Agent**: `@tst`

#### Verifier (Section 5.3.5, Table B.5)

**Responsibility**: Software verification

**Key Activities**: Plan verification activities, perform static analysis, conduct reviews, verify traceability, check compliance with standards, collect evidence.

**Independence**: Not required for SIL 0-1; Highly recommended for SIL 2; **MANDATORY for SIL 3-4**. For SIL 3-4, verifier MUST NOT be designer or implementer. **Agent**: `@ver`

#### Integrator (Section 5.3.6, Table B.6)

**Responsibility**: Software integration

**Key Activities**: Plan integration strategy, integrate software modules, resolve integration issues, perform integration testing, document integration results.

**Independence**: Not required. **Agent**: `@int`

#### Validator (Section 5.3.7, Table B.7)

**Responsibility**: Software validation

**Key Activities**: Plan validation activities, perform system testing, conduct acceptance testing, validate operational scenarios, obtain customer acceptance.

**Independence**: Not required for SIL 0-1; Highly recommended for SIL 2; **MANDATORY for SIL 3-4**. For SIL 3-4, validator MUST NOT be involved in development and MUST NOT report to Project Manager. **Agent**: `@val`

#### Assessor (Section 5.3.8, Table B.8)

**Responsibility**: Independent safety assessment

**Key Activities**: Review all lifecycle artifacts, assess compliance with EN 50128, review safety case, verify independence of verification/validation, issue assessment report, approve for deployment.

**Independence**: **MANDATORY for SIL 3-4**. Assessor MUST be completely independent of development, often external to the organization. Required for final approval before deployment.

#### Configuration Manager (Section 5, Table B.10)

**Responsibility**: Configuration and change management

**Key Activities**: Establish and maintain configuration management system, control configuration items, manage baselines, control changes, maintain version control, manage release process, track configuration status, conduct configuration audits.

**Independence**: Not required. **Agent**: `@cm`

### Agent Mapping to EN 50128 Roles

| EN 50128 Role | Agent | `@agent` Syntax | Independence Notes |
|---------------|-------|----------------|-------------------|
| Project Manager | PM | `@pm` | Not required |
| Software Manager | PM | `@pm` | Not required (combined with PM in this platform) |
| Configuration Manager | CM | `@cm` | Not required |
| Designer | Designer | `@des` | Not required |
| Implementer | Implementer | `@imp` | Not required |
| Tester | Tester | `@tst` | Highly recommended for SIL 3-4 |
| Verifier | Verifier | `@ver` | **Mandatory for SIL 3-4** |
| Integrator | Integrator | `@int` | Not required |
| Validator | Validator | `@val` | **Mandatory for SIL 3-4** |
| Assessor | (external) | N/A | **Mandatory for SIL 3-4** |

**Additional Agents** (platform extensions):
- Safety Engineer (`@saf`) — Supports safety analysis per Section 7.1
- Requirements Engineer (`@req`) — Supports requirements phase per Section 7.2
- Quality Assurance (`@qua`) — Supports QA per Section 6.5
- V&V Manager (`@vmgr`) — Independent V&V authority for SIL 3-4 (Section 5.1.2.10e)
- Lifecycle Coordinator (`@cod`) — End-to-end lifecycle orchestration (Section 5.3)
