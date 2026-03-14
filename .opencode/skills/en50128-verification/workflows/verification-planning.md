# Software Verification Planning Workflow for EN 50128

**Purpose**: Step-by-step workflow for creating Software Verification Plan (SVP) compliant with EN 50128 Section 6.2.

**Scope**: Verification planning phase - defines verification strategies, techniques, tools, and responsibilities for the entire software lifecycle.

**Audience**: Verifiers (VER), V&V Managers (VMGR), Project Managers (PM)

**EN 50128 Reference**: 
- Section 6.2.4 "Software Verification Documentation"
- Section 6.2.4.1-6.2.4.9 "Software Verification Plan requirements"
- Table A.5 "Verification and Testing techniques"
- Table A.19 "Static Analysis techniques"
- Table A.21 "Test Coverage for Code"

**Related Documents**:
- `resources/verification-tools-reference.md` - Tool catalog and qualifications
- `workflows/static-analysis-workflow.md` - Static analysis execution
- `workflows/traceability-verification.md` - Traceability verification process
- `workflows/verification-reporting.md` - Verification report creation

---

## Table of Contents

1. [Workflow Overview](#1-workflow-overview)
2. [Inputs and Prerequisites](#2-inputs-and-prerequisites)
3. [Step 1: Establish Verification Context](#step-1-establish-verification-context)
4. [Step 2: Select Verification Techniques (Table A.5)](#step-2-select-verification-techniques-table-a5)
5. [Step 3: Define Static Analysis Strategy (Table A.19)](#step-3-define-static-analysis-strategy-table-a19)
6. [Step 4: Define Coverage Requirements (Table A.21)](#step-4-define-coverage-requirements-table-a21)
7. [Step 5: Select and Qualify Tools](#step-5-select-and-qualify-tools)
8. [Step 6: Define Verification Activities per Phase](#step-6-define-verification-activities-per-phase)
9. [Step 7: Establish Independence Requirements](#step-7-establish-independence-requirements)
10. [Step 8: Document Verification Plan](#step-8-document-verification-plan)
11. [Step 9: Review and Approval](#step-9-review-and-approval)
12. [Verification Planning Checklist](#verification-planning-checklist)
13. [Tool Integration Commands](#tool-integration-commands)
14. [Example Verification Plan Outline](#example-verification-plan-outline)

---

## 1. Workflow Overview

### Purpose of Software Verification Plan (SVP)

The Software Verification Plan:
- Defines **all verification activities** for the software lifecycle
- Specifies **techniques and tools** per EN 50128 Tables A.5, A.19, A.21
- Establishes **verification criteria** for each phase
- Documents **roles and independence** requirements (critical for SIL 3-4)
- Provides **traceability approach** from requirements to code to tests

### EN 50128 Requirements Summary

| Requirement | Section | Key Content |
|-------------|---------|-------------|
| **SVP is MANDATORY** | 6.2.4.1 | "Verification shall be documented by at least a Software Verification Plan" |
| **Techniques Selection** | 6.2.4.5 | Must select from Tables A.5, A.6, A.7, A.8 and justify combination |
| **Verification Activities** | 6.2.4.6 | Describe activities for correctness and consistency checking |
| **SVP Content** | 6.2.4.9 | Must address: strategies, techniques, roles, coverage, structure |
| **Independence** | 5.1.2.10 | Verifier MUST be independent from designer/implementer (SIL 3-4) |

### Workflow Phases

```
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 1: ESTABLISH CONTEXT                                      │
│ - Identify SIL level, project scope, lifecycle model            │
│ - Review system requirements and software architecture          │
│ - Identify safety-critical functions                            │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 2: SELECT VERIFICATION TECHNIQUES (EN 50128 TABLE A.5)    │
│ - Static Analysis (MANDATORY SIL 3-4)                           │
│ - Traceability (MANDATORY SIL 3-4)                              │
│ - Metrics, Testing, etc. per SIL requirements                   │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 3: DEFINE STATIC ANALYSIS STRATEGY (TABLE A.19)           │
│ - Control Flow Analysis (MANDATORY SIL 3-4)                     │
│ - Data Flow Analysis (MANDATORY SIL 3-4)                        │
│ - Complexity Metrics, Code Review, etc.                         │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 4: DEFINE COVERAGE REQUIREMENTS (TABLE A.21)              │
│ - Statement Coverage (100% MANDATORY SIL 2+)                    │
│ - Branch Coverage (100% MANDATORY SIL 2+)                       │
│ - Condition Coverage (100% MANDATORY SIL 3-4)                   │
│ - MC/DC (Highly Recommended SIL 3-4)                            │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 5: SELECT AND QUALIFY TOOLS                               │
│ - Static analysis: Cppcheck, PC-lint Plus, Clang                │
│ - Coverage: gcov/lcov, Bullseye                                 │
│ - Complexity: Lizard                                             │
│ - Tool qualification per EN 50128 Annex B.7                     │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 6: DEFINE VERIFICATION ACTIVITIES PER LIFECYCLE PHASE     │
│ - Requirements verification (7.2.4.22)                           │
│ - Architecture/Design verification (7.3.4.41, 7.3.4.42)         │
│ - Component design verification (7.4.4.13)                       │
│ - Source code verification (7.5.4.10)                            │
│ - Integration verification (7.6.4.13)                            │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 7: ESTABLISH INDEPENDENCE REQUIREMENTS                    │
│ - Define verifier independence (MANDATORY SIL 3-4)              │
│ - Separate verification team from development                   │
│ - Reporting structure to VMGR (SIL 3-4)                         │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 8: DOCUMENT VERIFICATION PLAN                             │
│ - Use SVP template (DOC-SVP-YYYY-NNN)                          │
│ - Complete all sections per EN 50128 6.2.4.9                    │
│ - Include technique justifications                              │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 9: REVIEW AND APPROVAL                                    │
│ - QUA template compliance check                                 │
│ - VMGR/VAL technical review                                     │
│ - PM/COD approval and baseline                                  │
└─────────────────────────────────────────────────────────────────┘
```

### SIL-Dependent Requirements

| Aspect | SIL 0-1 | SIL 2 | SIL 3-4 |
|--------|---------|-------|---------|
| **Independence** | Not required | Recommended | **MANDATORY** |
| **Static Analysis** | Recommended | Highly Recommended | **MANDATORY** |
| **Control Flow Analysis** | Recommended | Highly Recommended | **MANDATORY** |
| **Data Flow Analysis** | Recommended | Highly Recommended | **MANDATORY** |
| **Traceability** | Recommended | Highly Recommended | **MANDATORY** |
| **Statement Coverage** | Highly Recommended | 100% | **100% MANDATORY** |
| **Branch Coverage** | Highly Recommended | **100% MANDATORY** | **100% MANDATORY** |
| **Condition Coverage** | Recommended | Recommended | **100% MANDATORY** |
| **MC/DC** | - | Recommended | Highly Recommended |
| **Tool Qualification** | Basic | Formal | **Formal with evidence** |

---

## 2. Inputs and Prerequisites

### Required Input Documents

1. **Software Requirements Specification (SRS)** - DOC-SRS-YYYY-NNN
   - All software requirements to be verified
   - SIL level assignments
   - Safety requirements
   
2. **Software Architecture Specification (SAS)** - DOC-SAS-YYYY-NNN (if available)
   - High-level architecture
   - Module decomposition
   - Interface definitions

3. **Software Quality Assurance Plan (SQAP)** - DOC-SQAP-YYYY-NNN
   - Quality objectives and metrics
   - Review and audit processes
   - Coding standards (MISRA C:2012)

4. **Software Configuration Management Plan (SCMP)** - DOC-SCMP-YYYY-NNN
   - Version control strategy
   - Baseline management
   - Change control process

5. **Project Context**
   - SIL level (0, 1, 2, 3, or 4)
   - Target platform (embedded hardware, OS, compiler)
   - Safety requirements and constraints
   - Project schedule and resources

### Prerequisites

- [ ] Verifier role assigned (independent for SIL 3-4)
- [ ] V&V Manager assigned (SIL 3-4)
- [ ] SIL level determined
- [ ] Software Requirements Specification available
- [ ] SQAP and SCMP completed
- [ ] Verification team resources identified
- [ ] Tool budget and procurement approved

---

## Step 1: Establish Verification Context

### 1.1 Identify SIL Level and Scope

**Purpose**: Determine SIL-specific verification requirements.

**Actions**:

```bash
# Review SRS for SIL level
grep -i "SIL" DOC-SRS-*.md

# Identify safety requirements
grep -i "@trace.*REQ-SAF" DOC-SRS-*.md
```

**Document in SVP**:

```markdown
## 1. Verification Context

### 1.1 Project Overview
- **Project Name**: Train Control System (TCS)
- **Software Component**: Interlocking Logic Module
- **SIL Level**: SIL 4
- **Target Platform**: ARM Cortex-M7, bare-metal (no OS)
- **Programming Language**: C (MISRA C:2012 compliant)

### 1.2 Scope of Verification
This Software Verification Plan covers verification activities for:
- Software Requirements (Phase 2)
- Software Architecture and Design (Phase 3)
- Component Design (Phase 4)
- Implementation and Unit Testing (Phase 5)
- Integration (Phase 6)
- Validation support (Phase 7)

### 1.3 SIL-Specific Requirements
For SIL 4, the following are MANDATORY:
- Independent verification team (5.1.2.10)
- Static Analysis (Table A.5, technique 3)
- Control Flow Analysis (Table A.19, technique 2)
- Data Flow Analysis (Table A.19, technique 3)
- Traceability (Table A.5, technique 7)
- 100% Statement, Branch, Condition Coverage (Table A.21)
```

### 1.2 Review Safety Requirements

**Purpose**: Identify safety-critical functions requiring enhanced verification.

**Actions**:

```bash
# Extract safety requirements
python3 tools/requirements/extract_requirements.py \
    --input DOC-SRS-*.md \
    --filter safety \
    --output safety_requirements.yaml

# Count safety requirements by severity
grep -c "SEVERITY: Critical" safety_requirements.yaml
grep -c "SEVERITY: High" safety_requirements.yaml
```

**Document in SVP**:

```markdown
### 1.4 Safety-Critical Functions

The following functions have been identified as safety-critical (SIL 4):

| Function ID | Description | Safety Requirement | Verification Focus |
|-------------|-------------|-------------------|-------------------|
| FUNC-001 | Train speed calculation | REQ-SAF-001 | Algorithm correctness, overflow protection |
| FUNC-002 | Emergency brake activation | REQ-SAF-002 | Response time, fail-safe behavior |
| FUNC-003 | Signal state monitoring | REQ-SAF-003 | Input validation, fault detection |
| FUNC-004 | Route interlocking logic | REQ-SAF-004 | State machine correctness, deadlock prevention |

**Enhanced Verification for Safety Functions**:
- Formal review with safety engineer present
- 100% MC/DC coverage (not just condition coverage)
- Fault injection testing
- Independent verification by separate verifier
```

### 1.3 Identify Lifecycle Model

**Purpose**: Understand verification touchpoints in lifecycle.

**Document in SVP**:

```markdown
### 1.5 Software Lifecycle Model
This project follows the EN 50128 V-Model:

```
Requirements → Architecture → Design → Implementation
     ↓              ↓           ↓           ↓
  Validation ← Integration ← Unit Testing ← Code
```

**Verification Touchpoints**:
1. Phase 2: Requirements Verification (7.2.4.22)
2. Phase 3: Architecture & Design Verification (7.3.4.41, 7.3.4.42)
3. Phase 4: Component Design Verification (7.4.4.13)
4. Phase 5: Source Code Verification (7.5.4.10)
5. Phase 6: Integration Verification (7.6.4.13)
6. Phase 7: Validation support (6.3.4)
```

---

## Step 2: Select Verification Techniques (Table A.5)

### 2.1 Review EN 50128 Table A.5

**EN 50128 Table A.5 - Verification and Testing (Section 6.2, 7.3)**

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | Formal Proof | D.29 | - | R | HR |
| 2 | Probabilistic Testing | D.44 | R | R | - |
| 3 | **Static Analysis** | Table A.19 | - | HR | **M** |
| 4 | **Dynamic Analysis and Testing** | Table A.13 | - | HR | **M** |
| 5 | Metrics | D.37 | - | R | HR |
| 6 | Simulation | D.42 | R | R | R |
| 7 | **Traceability** | D.58 | R | HR | **M** |
| 8 | **Test Coverage for Code** | Table A.21 | R | HR | **M** |
| 9 | Software Error Effect Analysis | D.25 | - | R | HR |
| 10 | Software Fault Tree Analysis | D.25 | - | R | HR |

**Key**: M = Mandatory, HR = Highly Recommended, R = Recommended, - = No recommendation

### 2.2 Select MANDATORY Techniques (SIL 3-4)

**For SIL 3-4, the following are MANDATORY**:

```markdown
### 2. Verification Techniques (EN 50128 Table A.5)

#### 2.1 Mandatory Techniques (SIL 4)

The following techniques from Table A.5 are MANDATORY for SIL 4:

**Technique 3: Static Analysis (Table A.19)**
- **Status**: MANDATORY
- **Rationale**: Required by EN 50128 for SIL 3-4
- **Implementation**: See Section 3 (Static Analysis Strategy)
- **Tools**: Cppcheck, PC-lint Plus, Clang Static Analyzer
- **Deliverable**: Static Analysis Report per phase

**Technique 4: Dynamic Analysis and Testing (Table A.13)**
- **Status**: MANDATORY
- **Rationale**: Required by EN 50128 for SIL 3-4
- **Implementation**: Unit testing (Unity framework), integration testing
- **Tools**: Unity, gcov/lcov for coverage
- **Deliverable**: Test Reports with coverage metrics

**Technique 7: Traceability (D.58)**
- **Status**: MANDATORY
- **Rationale**: Required by EN 50128 for SIL 3-4
- **Implementation**: Bidirectional traceability from requirements → design → code → tests
- **Tools**: @trace tags, Traceability Manager (`workspace.py trace`)
- **Deliverable**: Traceability Matrix per phase

**Technique 8: Test Coverage for Code (Table A.21)**
- **Status**: MANDATORY
- **Rationale**: Required by EN 50128 for SIL 3-4
- **Implementation**: 100% statement, branch, condition coverage
- **Tools**: gcov, lcov, Bullseye Coverage
- **Deliverable**: Coverage Report with 100% targets met
```

### 2.3 Select Highly Recommended Techniques

```markdown
#### 2.2 Highly Recommended Techniques (SIL 4)

The following techniques are HIGHLY RECOMMENDED for SIL 4 and SHALL be applied:

**Technique 1: Formal Proof (D.29)**
- **Status**: Highly Recommended (applied for critical algorithms)
- **Rationale**: Provides mathematical proof of algorithm correctness
- **Implementation**: Applied to safety-critical functions (FUNC-001, FUNC-004)
- **Tools**: Manual proof with Frama-C for assertion checking
- **Deliverable**: Formal Proof Document for critical algorithms

**Technique 5: Metrics (D.37)**
- **Status**: Highly Recommended (applied)
- **Rationale**: Quantitative quality assessment
- **Implementation**: Cyclomatic complexity (CCN ≤ 10), code quality metrics
- **Tools**: Lizard (complexity), SonarQube (quality)
- **Deliverable**: Metrics Report per phase

**Technique 9: Software Error Effect Analysis (D.25)**
- **Status**: Highly Recommended (applied)
- **Rationale**: Identify error propagation paths
- **Implementation**: Analyze impact of input errors, hardware faults
- **Tools**: Manual analysis with Fault Injection testing
- **Deliverable**: Software FMEA Report

**Technique 10: Software Fault Tree Analysis (D.25)**
- **Status**: Highly Recommended (applied to critical functions)
- **Rationale**: Top-down hazard analysis
- **Implementation**: FTA for safety-critical failures
- **Tools**: Manual FTA with tool support (optional)
- **Deliverable**: Fault Tree Analysis Report
```

### 2.4 Justification of Combination

**EN 50128 Requirement** (6.2.4.5): "The selected combination shall be justified as a set satisfying 4.8, 4.9 and 4.10."

```markdown
#### 2.3 Justification of Technique Combination

**Selected Techniques**: 1, 3, 4, 5, 7, 8, 9, 10

**Approved Combination (Table A.5 Note)**:
- Required: **3, 5, 7, 8** (Static Analysis, Metrics, Traceability, Test Coverage)
- Plus ONE from: **1, 2, 6** → Selected: **1** (Formal Proof)
- Additional: **4, 9, 10** (Dynamic Testing, SEEA, FTA)

**Justification**:
1. **Completeness**: Combination covers static verification (3), dynamic verification (4), requirements verification (7), and quantitative assessment (5, 8)
2. **Safety**: Error effect analysis (9) and fault tree analysis (10) address safety integrity per EN 50128 4.8
3. **Correctness**: Formal proof (1) for critical algorithms provides mathematical correctness assurance
4. **Traceability**: Technique 7 ensures bidirectional traceability per EN 50128 4.9
5. **Independence**: All techniques can be performed by independent verifier per EN 50128 4.10

This combination satisfies EN 50128 requirements 4.8 (Safety Integrity), 4.9 (Functionality and Performance), and 4.10 (Verification and Independence).
```

---

## Step 3: Define Static Analysis Strategy (Table A.19)

### 3.1 Review EN 50128 Table A.19

**EN 50128 Table A.19 - Static Analysis Techniques**

| # | TECHNIQUE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-----------|-----|-------|---------|---------|
| 1 | Boundary Value Analysis | D.4 | R | HR | HR |
| 2 | **Control Flow Analysis** | D.9 | R | HR | **M** |
| 3 | **Data Flow Analysis** | D.11 | R | HR | **M** |
| 4 | Range Checking | D.45 | R | HR | HR |
| 5 | Semantic Analysis | D.41 | - | R | HR |
| 6 | **Code Review / Walkthrough** | D.56, D.61 | HR | HR | HR |
| 7 | **Fagan Inspection** | D.23 | - | R | HR |
| 8 | Complexity Metrics | D.8, D.37 | R | HR | HR |

### 3.2 Define MANDATORY Static Analysis (SIL 3-4)

```markdown
### 3. Static Analysis Strategy (EN 50128 Table A.19)

#### 3.1 Mandatory Static Analysis Techniques (SIL 4)

**Technique 2: Control Flow Analysis (MANDATORY SIL 4)**
- **Description**: Analyze control flow paths, unreachable code, infinite loops
- **Tools**: 
  - Cppcheck (--enable=style,warning,performance)
  - Clang Static Analyzer (control flow checker)
  - PC-lint Plus (control flow rules)
- **Criteria**:
  - Zero unreachable code
  - Zero infinite loops (except intentional main loop)
  - All paths return appropriate values
  - No dead code
- **Frequency**: Every source code commit
- **Deliverable**: Control Flow Analysis Report (part of Static Analysis Report)

**Technique 3: Data Flow Analysis (MANDATORY SIL 4)**
- **Description**: Analyze data flow, uninitialized variables, unused variables
- **Tools**:
  - Cppcheck (--enable=style)
  - Clang Static Analyzer (data flow checker)
  - PC-lint Plus (data flow rules)
- **Criteria**:
  - Zero uninitialized variable uses
  - Zero unused variables (except intentional)
  - All outputs assigned before use
  - No use-after-free
- **Frequency**: Every source code commit
- **Deliverable**: Data Flow Analysis Report (part of Static Analysis Report)

#### 3.2 Highly Recommended Static Analysis Techniques

**Technique 1: Boundary Value Analysis (Highly Recommended)**
- **Description**: Test boundary conditions in code
- **Implementation**: Applied in unit tests and code review
- **Tools**: Manual review + unit test framework (Unity)
- **Criteria**: All array accesses, arithmetic operations checked for bounds
- **Frequency**: Code review (every function)

**Technique 4: Range Checking (Highly Recommended)**
- **Description**: Verify variable ranges and arithmetic safety
- **Implementation**: Static analysis + runtime assertions
- **Tools**: Cppcheck, PC-lint Plus, manual review
- **Criteria**: All inputs validated, arithmetic overflow protected
- **Frequency**: Code review + static analysis

**Technique 5: Semantic Analysis (Highly Recommended)**
- **Description**: Check logical consistency and correctness
- **Implementation**: Code review with semantic checkers
- **Tools**: Clang Static Analyzer, PC-lint Plus
- **Criteria**: Logical consistency, correct API usage
- **Frequency**: Code review

**Technique 6: Code Review / Walkthrough (Highly Recommended)**
- **Description**: Manual code inspection by peers
- **Implementation**: 4-person review process (Author → PEER → QUA → VER)
- **Criteria**: See Code Review Checklist (en50128-implementation skill)
- **Frequency**: All code before commit
- **Deliverable**: Code Review Report

**Technique 7: Fagan Inspection (Highly Recommended for critical functions)**
- **Description**: Formal inspection process
- **Implementation**: Formal inspection for safety-critical functions
- **Roles**: Moderator, Author, Reviewers (3-5 people), Scribe
- **Frequency**: Safety-critical functions only
- **Deliverable**: Fagan Inspection Report

**Technique 8: Complexity Metrics (Highly Recommended)**
- **Description**: Measure cyclomatic complexity
- **Tools**: Lizard
- **Criteria**: CCN ≤ 10 for SIL 4
- **Frequency**: Every source code commit
- **Deliverable**: Complexity Metrics Report
```

### 3.3 Define Tool Configuration

```markdown
#### 3.3 Static Analysis Tool Configuration

**Cppcheck Configuration**:
```bash
# Run Cppcheck with all checks enabled
cppcheck \
    --enable=all \
    --addon=misra \
    --inline-suppr \
    --suppress=missingIncludeSystem \
    --template='{file}:{line}: {severity}: {message} [{id}]' \
    --xml \
    --xml-version=2 \
    src/ 2> cppcheck_report.xml

# Convert to HTML report
cppcheck-htmlreport \
    --file=cppcheck_report.xml \
    --report-dir=reports/cppcheck \
    --source-dir=.
```

**PC-lint Plus Configuration** (`pclint.lnt`):
```
// MISRA C:2012 compliance
+libclass(angle, foreign)
-strong(AJX)
+fll
-width(120)

// SIL 4 specific rules
// Complexity limit 10
-esym(818, *)  // Could be pointer to const

// Enable control flow analysis
+fce  // Enable control flow errors
+fda  // Enable data flow analysis
```

**Clang Static Analyzer Configuration**:
```bash
# Run scan-build with all checkers
scan-build \
    -enable-checker core \
    -enable-checker deadcode \
    -enable-checker security \
    -enable-checker unix \
    -enable-checker nullability \
    -o analysis_results \
    make
```

**Lizard Complexity Configuration**:
```bash
# Check complexity limit (SIL 4: CCN ≤ 10)
lizard \
    --CCN 10 \
    --length 100 \
    --arguments 5 \
    --warnings_only \
    --html \
    --output_file reports/complexity.html \
    src/
```
```

---

## Step 4: Define Coverage Requirements (Table A.21)

### 4.1 Review EN 50128 Table A.21

**EN 50128 Table A.21 - Test Coverage for Code**

| # | TECHNIQUE | Ref | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 |
|---|-----------|-----|-------|-------|-------|-------|-------|
| 1 | **Entry Points (statement)** | D.17 | - | HR | **M** | **M** | **M** |
| 2 | **Statement coverage** | D.17 | - | HR | **M** | **M** | **M** |
| 3 | **Branch coverage** | D.17 | R | HR | **M** | **M** | **M** |
| 4 | Compound condition coverage | D.7 | - | R | R | R | HR |
| 5 | **Condition coverage** | D.7 | - | R | R | **M** | **M** |
| 6 | **Data flow coverage** | D.10 | - | R | R | **M** | **M** |
| 7 | **MC/DC (Modified Condition/Decision)** | D.36 | - | - | R | HR | HR |

### 4.2 Define Coverage Targets

```markdown
### 4. Test Coverage Requirements (EN 50128 Table A.21)

#### 4.1 MANDATORY Coverage (SIL 4)

**Statement Coverage (Technique 1, 2 - MANDATORY)**
- **Target**: 100% of all executable statements
- **Tool**: gcov, lcov
- **Threshold**: 100.0% (no exceptions)
- **Exclusions**: None (defensive code, error handlers must be tested)
- **Verification**: lcov report with line-by-line coverage

**Branch Coverage (Technique 3 - MANDATORY)**
- **Target**: 100% of all branches (if/else, switch, loops)
- **Tool**: gcov, lcov, Bullseye
- **Threshold**: 100.0% (no exceptions)
- **Verification**: Branch coverage report showing all paths taken

**Condition Coverage (Technique 5 - MANDATORY)**
- **Target**: 100% of all boolean conditions
- **Tool**: gcov with condition tracking, Bullseye
- **Threshold**: 100.0% (no exceptions)
- **Verification**: Condition coverage report showing true/false evaluation

**Data Flow Coverage (Technique 6 - MANDATORY)**
- **Target**: All def-use pairs covered
- **Tool**: Manual analysis + gcov
- **Threshold**: 100% of def-use pairs
- **Verification**: Data flow analysis document

#### 4.2 Highly Recommended Coverage (SIL 4)

**MC/DC Coverage (Technique 7 - Highly Recommended)**
- **Target**: 100% MC/DC for safety-critical functions (FUNC-001, FUNC-002, FUNC-003, FUNC-004)
- **Tool**: Bullseye Coverage, tools/mcdc/mcdc_analyzer.py
- **Threshold**: 100.0% for safety functions, 90%+ for non-safety
- **Rationale**: Provides strong assurance of decision correctness
- **Verification**: MC/DC coverage report with independence pairs

**Compound Condition Coverage (Technique 4 - Highly Recommended)**
- **Target**: All compound boolean expressions
- **Implementation**: Covered by MC/DC analysis
- **Threshold**: 100% for safety functions

#### 4.3 Coverage Measurement Process

**Tool Setup**:
```bash
# Compile with coverage instrumentation
CFLAGS="-fprofile-arcs -ftest-coverage -O0 -g"
gcc $CFLAGS -o test_suite tests/*.c src/*.c

# Run all tests
./test_suite

# Generate coverage data
lcov --capture --directory . --output-file coverage.info

# Filter system headers
lcov --remove coverage.info '/usr/*' --output-file coverage_filtered.info

# Generate HTML report
genhtml coverage_filtered.info --output-directory reports/coverage

# Check thresholds
lcov --summary coverage_filtered.info
```

**Coverage Thresholds**:
```bash
# SIL 4 Thresholds (100% MANDATORY)
python3 tools/coverage/check_coverage.py \
    --coverage-file coverage_filtered.info \
    --sil 4 \
    --statement 100.0 \
    --branch 100.0 \
    --condition 100.0

# Expected output:
# Statement Coverage: 100.0% (PASS)
# Branch Coverage: 100.0% (PASS)
# Condition Coverage: 100.0% (PASS)
# MC/DC Coverage (safety functions): 100.0% (PASS)
```

**Coverage Reporting**:
- Coverage reports generated after EVERY test run
- Coverage trends tracked over time
- Coverage gaps documented and justified
- Uncoverable code marked with justification comments
```

---

## Step 5: Select and Qualify Tools

### 5.1 Tool Selection Criteria

```markdown
### 5. Verification Tools

#### 5.1 Tool Selection Criteria

Per EN 50128 Annex B.7, tools shall be:
1. **Appropriate**: Suitable for the verification task
2. **Qualified**: Proven reliability and accuracy
3. **Traceable**: Tool output can be traced to verification criteria
4. **Maintainable**: Tool configuration under version control

**Tool Classification** (EN 50128 Annex B.7):

**Class T1**: Tools that do not influence executable code
- Examples: Editors, version control, report generators
- Qualification: None required

**Class T2**: Tools that support testing or verification
- Examples: Static analyzers, test harnesses, coverage tools
- Qualification: Tool output verified by alternative means

**Class T3**: Tools that generate executable code or data
- Examples: Code generators, compilers, linkers
- Qualification: Formal tool qualification process

#### 5.2 Selected Tools

**Static Analysis Tools (Class T2)**:

| Tool | Version | Purpose | Classification | Qualification Status |
|------|---------|---------|---------------|---------------------|
| **Cppcheck** | 2.13.0+ | General static analysis | T2 | Qualified (cross-check with PC-lint) |
| **PC-lint Plus** | 2.0+ | MISRA C:2012 compliance | T2 | Qualified (vendor certification) |
| **Clang Static Analyzer** | 18.x+ | Deep semantic analysis | T2 | Qualified (cross-check with Cppcheck) |
| **Lizard** | 1.17+ | Complexity metrics | T2 | Qualified (manual verification sample) |

**Coverage Tools (Class T2)**:

| Tool | Version | Purpose | Classification | Qualification Status |
|------|---------|---------|---------------|---------------------|
| **gcov** | 13.x+ (GCC) | Statement/branch coverage | T2 | Qualified (GCC test suite) |
| **lcov** | 2.0+ | Coverage report generation | T2 | Qualified (cross-check with manual) |
| **Bullseye Coverage** | 9.x+ | MC/DC coverage (optional) | T2 | Qualified (vendor certification) |

**Test Tools (Class T2)**:

| Tool | Version | Purpose | Classification | Qualification Status |
|------|---------|---------|---------------|---------------------|
| **Unity** | 2.5+ | Unit test framework | T2 | Qualified (manual verification) |
| **Custom test harness** | v1.0 | Integration testing | T2 | Qualified (reviewed and approved) |

**Development Tools (Class T3)**:

| Tool | Version | Purpose | Classification | Qualification Status |
|------|---------|---------|---------------|---------------------|
| **GCC** | 13.2+ | C compiler | T3 | **Formal qualification required** |
| **GNU ld** | 2.41+ | Linker | T3 | **Formal qualification required** |

#### 5.3 Tool Qualification Process

**For Class T2 Tools** (Static analyzers, coverage tools):

1. **Vendor Qualification** (if available):
   - Obtain vendor qualification certificate
   - Review vendor test suite results
   - Document in Tool Qualification Report

2. **Cross-Check Qualification**:
   - Run tool on known test cases
   - Compare results with manual analysis
   - Compare results with other tools
   - Document discrepancies

3. **Sample Verification**:
   - Select representative code samples (10% minimum)
   - Manually verify tool output
   - Document verification results

**For Class T3 Tools** (Compiler, linker):

1. **Formal Qualification**:
   - Follow EN 50128 Annex B.7 formal process
   - Generate qualification test suite
   - Document all deviations from standard
   - Maintain qualification evidence

2. **Compiler Back-to-Back Testing** (Highly Recommended SIL 4):
   - Compile code with two independent compilers
   - Compare object code output
   - Document any differences

#### 5.4 Tool Configuration Management

All tool configurations under version control:
```
tools/
  └── config/
      ├── cppcheck-project.xml
      ├── pclint.lnt
      ├── clang-analyzer-config.yaml
      ├── lizard-config.yaml
      └── coverage-thresholds.yaml
```

**Version Control Requirements**:
- Tool configuration files in Git
- Changes require CCB approval
- Tool versions documented in SCMP
- Tool updates require re-qualification
```

### 5.2 Tool Qualification Evidence

```markdown
#### 5.5 Tool Qualification Evidence

**Evidence Location**: `docs/tool-qualification/`

**Required Documents**:
1. **Tool Qualification Plan** (per tool)
2. **Tool Qualification Report** (per tool)
3. **Tool Validation Test Cases** (per tool)
4. **Tool Validation Results** (per tool)
5. **Tool Configuration Files** (under version control)

**Example Tool Qualification Report Structure**:
```
# Tool Qualification Report: Cppcheck 2.13.0

## 1. Tool Information
- Tool Name: Cppcheck
- Version: 2.13.0
- Vendor: Cppcheck Project
- Classification: T2 (verification support)
- Purpose: Static analysis (control flow, data flow, MISRA C)

## 2. Qualification Method
- Cross-check with PC-lint Plus
- Manual verification of sample (15 files, 2000 lines)
- Vendor test suite review

## 3. Qualification Test Cases
- Test Case 1: Uninitialized variable detection (10 cases)
- Test Case 2: NULL pointer dereference (15 cases)
- Test Case 3: Buffer overflow detection (12 cases)
- Test Case 4: MISRA C Rule 10.1 (type violations, 20 cases)
- ...

## 4. Qualification Results
- Test Cases Passed: 57/60 (95%)
- Failures: 3 false negatives (documented in Known Limitations)
- Cross-check agreement with PC-lint: 98%

## 5. Known Limitations
- False negative: Cppcheck may miss some complex pointer aliasing (mitigated by PC-lint)
- Configuration: Must use `--enable=all` for full coverage

## 6. Approval
- Qualified By: [Verifier Name]
- Approved By: [VMGR Name]
- Date: 2026-03-13
```
```

---

## Step 6: Define Verification Activities per Phase

### 6.1 Requirements Phase Verification (7.2.4.22)

```markdown
### 6. Verification Activities per Lifecycle Phase

#### 6.1 Requirements Phase Verification (Phase 2)

**Reference**: EN 50128 Section 7.2.4.22

**Verification Objectives**:
- Verify Software Requirements Specification correctness and completeness
- Verify traceability from system requirements to software requirements
- Verify SIL level assignments
- Verify testability of all requirements

**Verification Activities**:

1. **Requirements Review**:
   - **Method**: Formal document review (Fagan Inspection)
   - **Participants**: REQ (author), VER (independent), SAF (safety), QUA, PM
   - **Checklist**: Requirements Review Checklist (en50128-requirements skill)
   - **Criteria**:
     - All requirements unambiguous (SHALL/SHOULD/MAY keywords)
     - All requirements testable (verification criteria defined)
     - All safety requirements identified and marked
     - All requirements have unique IDs
     - Traceability complete (system → software)
   - **Deliverable**: Requirements Review Report

2. **Traceability Verification**:
   - **Method**: Automated trace checking + manual review
   - **Tool**: `workspace.py trace validate --phase requirements`
   - **Criteria**:
     - All system requirements traced to software requirements
     - No orphan software requirements (all have source)
     - Traceability matrix bidirectional
   - **Deliverable**: Traceability Matrix (Requirements Phase)

3. **Safety Requirements Analysis**:
   - **Method**: Manual analysis with safety engineer
   - **Criteria**:
     - All hazards from Hazard Log addressed
     - All safety requirements have correct SIL level
     - Safety requirements have failure rates specified
   - **Deliverable**: Safety Requirements Analysis Report

**Verification Report**:
- **Document**: Software Requirements Verification Report (DOC-SRS-VER-YYYY-NNN)
- **Author**: Verifier (independent for SIL 4)
- **Approval**: VMGR (SIL 4)

**Entry Criteria**:
- Software Requirements Specification complete
- SQAP approved
- Verification team assigned

**Exit Criteria**:
- All requirements reviewed and approved
- Zero open defects (severity Critical or High)
- Traceability matrix complete
- Software Requirements Verification Report approved
```

### 6.2 Architecture and Design Phase Verification (7.3.4.41, 7.3.4.42)

```markdown
#### 6.2 Architecture and Design Phase Verification (Phase 3)

**Reference**: EN 50128 Sections 7.3.4.41, 7.3.4.42

**Verification Objectives**:
- Verify Software Architecture Specification correctness
- Verify Software Design Specification correctness
- Verify traceability from requirements to design
- Verify modularity and interface definitions

**Verification Activities**:

1. **Architecture Review**:
   - **Method**: Formal document review
   - **Checklist**: Architecture Review Checklist (en50128-design skill)
   - **Criteria**:
     - Modular architecture (required for SIL 2+)
     - Interface definitions complete
     - Design patterns appropriate (defensive programming)
     - Memory allocation strategy (static only for SIL 2+)
     - Complexity estimates within limits
   - **Deliverable**: Architecture Review Report

2. **Design Review**:
   - **Method**: Formal document review + walkthrough
   - **Checklist**: Design Review Checklist (en50128-design skill)
   - **Criteria**:
     - All requirements allocated to design elements
     - All interfaces fully specified
     - Error handling strategy defined
     - State machines verified (if applicable)
     - Timing and resource budgets defined
   - **Deliverable**: Design Review Report

3. **Traceability Verification**:
   - **Method**: Automated + manual trace checking
   - **Tool**: `workspace.py trace validate --phase design`
   - **Criteria**:
     - All requirements traced to design elements
     - All design elements traced to requirements
     - Traceability matrix bidirectional
   - **Deliverable**: Traceability Matrix (Design Phase)

4. **Interface Verification**:
   - **Method**: Interface consistency checking
   - **Criteria**:
     - All interfaces documented (function signatures, data structures)
     - Interface contracts defined (preconditions, postconditions)
     - No inconsistencies between modules
   - **Deliverable**: Interface Verification Report

**Verification Report**:
- **Document**: Software Architecture and Design Verification Report (DOC-SAS-VER-YYYY-NNN)
- **Author**: Verifier (independent for SIL 4)
- **Approval**: VMGR (SIL 4)

**Entry Criteria**:
- Software Architecture Specification complete
- Software Design Specification complete
- Requirements Verification passed

**Exit Criteria**:
- All design documents reviewed and approved
- Zero open defects (severity Critical or High)
- Traceability matrix complete (requirements → design)
- Architecture and Design Verification Report approved
```

### 6.3 Component Design Verification (7.4.4.13)

```markdown
#### 6.3 Component Design Verification (Phase 4)

**Reference**: EN 50128 Section 7.4.4.13

**Verification Objectives**:
- Verify Software Component Design Specification correctness
- Verify detailed design completeness
- Verify traceability from high-level design to component design
- Verify unit test specifications

**Verification Activities**:

1. **Component Design Review**:
   - **Method**: Formal review + PDL/pseudocode inspection
   - **Criteria**:
     - All modules have detailed design specifications
     - All functions have documented interfaces
     - All algorithms described in sufficient detail
     - Complexity estimates provided (target: CCN ≤ 10)
     - Memory usage estimates provided
   - **Deliverable**: Component Design Review Report

2. **Unit Test Specification Review**:
   - **Method**: Review unit test specifications
   - **Criteria**:
     - All functions have unit tests specified
     - Coverage targets defined (100% statement, branch, condition)
     - Boundary value tests specified
     - Error condition tests specified
   - **Deliverable**: Unit Test Specification Review Report

3. **Traceability Verification**:
   - **Method**: Automated + manual trace checking
   - **Criteria**:
     - All design elements traced to component design
     - All component design elements traced to unit tests
   - **Deliverable**: Traceability Matrix (Component Design Phase)

**Verification Report**:
- **Document**: Software Component Design Verification Report (DOC-SCD-VER-YYYY-NNN)
- **Author**: Verifier (independent for SIL 4)
- **Approval**: VMGR (SIL 4)

**Entry Criteria**:
- Software Component Design Specification complete
- Unit Test Specifications complete
- Design Verification passed

**Exit Criteria**:
- All component design documents reviewed and approved
- Unit test specifications approved
- Traceability matrix complete (design → component design → unit tests)
- Component Design Verification Report approved
```

### 6.4 Source Code Verification (7.5.4.10)

```markdown
#### 6.4 Source Code Verification (Phase 5)

**Reference**: EN 50128 Section 7.5.4.10

**Verification Objectives**:
- Verify source code correctness and compliance
- Verify MISRA C:2012 compliance (MANDATORY SIL 2+)
- Verify traceability from design to code
- Verify unit test coverage (100% MANDATORY SIL 2+)

**Verification Activities**:

1. **Static Analysis** (MANDATORY SIL 3-4):
   - **Method**: Automated static analysis with multiple tools
   - **Tools**: Cppcheck, PC-lint Plus, Clang Static Analyzer
   - **Workflow**: See `workflows/static-analysis-workflow.md`
   - **Criteria**:
     - Zero critical issues
     - Zero MISRA C mandatory rule violations (SIL 2+)
     - All warnings reviewed and justified
     - Control flow analysis passed
     - Data flow analysis passed
   - **Deliverable**: Static Analysis Report

2. **Code Review** (Highly Recommended SIL 3-4):
   - **Method**: 4-person review (Author → PEER → QUA → VER)
   - **Checklist**: Code Review Checklist (en50128-implementation skill, 124 items)
   - **Criteria**:
     - MISRA C compliance manual check
     - Defensive programming patterns applied
     - Error handling complete
     - Memory safety (no dynamic allocation, pointer checks)
     - Complexity within limits (CCN ≤ 10 for SIL 4)
   - **Deliverable**: Code Review Report (per module)

3. **Complexity Analysis** (Highly Recommended SIL 3-4):
   - **Method**: Automated complexity measurement
   - **Tool**: Lizard
   - **Command**: `lizard --CCN 10 --warnings_only src/`
   - **Criteria**: All functions CCN ≤ 10 (SIL 4)
   - **Deliverable**: Complexity Metrics Report

4. **Coverage Analysis** (MANDATORY SIL 2+):
   - **Method**: Automated coverage measurement with gcov/lcov
   - **Criteria**:
     - 100% statement coverage (MANDATORY SIL 2+)
     - 100% branch coverage (MANDATORY SIL 2+)
     - 100% condition coverage (MANDATORY SIL 3-4)
     - 100% MC/DC coverage for safety functions (HR SIL 3-4)
   - **Deliverable**: Coverage Report

5. **Traceability Verification**:
   - **Method**: @trace tag verification + manual check
   - **Tool**: `workspace.py trace validate --phase implementation`
   - **Criteria**:
     - All design elements traced to code
     - All functions have @trace tags
     - All code traced to unit tests
   - **Deliverable**: Traceability Matrix (Code Phase)

**Verification Report**:
- **Document**: Software Source Code Verification Report (DOC-SRC-VER-YYYY-NNN)
- **Author**: Verifier (independent for SIL 4)
- **Approval**: VMGR (SIL 4)

**Entry Criteria**:
- Source code complete
- Unit tests complete and passing
- Component Design Verification passed

**Exit Criteria**:
- Static analysis passed (zero critical issues)
- Code review passed (all items approved)
- Complexity within limits (CCN ≤ 10 for SIL 4)
- Coverage targets met (100% statement, branch, condition for SIL 4)
- Traceability complete (design → code → tests)
- Software Source Code Verification Report approved
```

### 6.5 Integration Verification (7.6.4.13)

```markdown
#### 6.5 Integration Verification (Phase 6)

**Reference**: EN 50128 Section 7.6.4.13

**Verification Objectives**:
- Verify software component integration correctness
- Verify interface consistency
- Verify integration test coverage
- Verify system-level behavior

**Verification Activities**:

1. **Integration Test Review**:
   - **Method**: Review integration test specifications and results
   - **Criteria**:
     - All interfaces tested
     - All integration scenarios covered
     - Performance requirements verified
     - Error conditions tested
   - **Deliverable**: Integration Test Review Report

2. **Interface Consistency Check**:
   - **Method**: Automated interface checking + manual review
   - **Criteria**:
     - No interface mismatches
     - All data types consistent
     - All function signatures match declarations
   - **Deliverable**: Interface Consistency Report

3. **Integration Coverage Analysis**:
   - **Method**: Coverage measurement for integration tests
   - **Criteria**:
     - Integration test coverage targets met
     - All module interactions tested
   - **Deliverable**: Integration Coverage Report

4. **Traceability Verification**:
   - **Method**: Verify traceability through integration
   - **Criteria**:
     - All requirements verified through integration tests
     - All interfaces tested
   - **Deliverable**: Traceability Matrix (Integration Phase)

**Verification Report**:
- **Document**: Software Integration Verification Report (DOC-INT-VER-YYYY-NNN)
- **Author**: Verifier (independent for SIL 4)
- **Approval**: VMGR (SIL 4)

**Entry Criteria**:
- Software components integrated
- Integration tests complete and passing
- Source Code Verification passed

**Exit Criteria**:
- Integration tests passed
- Interface consistency verified
- Integration coverage targets met
- Software Integration Verification Report approved
```

---

## Step 7: Establish Independence Requirements

### 7.1 Independence Requirements (EN 50128 Section 5.1.2.10)

```markdown
### 7. Independence Requirements (SIL 4)

**EN 50128 Requirement**: For SIL 3-4, the Verifier SHALL be independent from the Designer and Implementer.

#### 7.1 Independence Policy

**Verifier Independence (MANDATORY SIL 4)**:
- Verifier SHALL NOT be Requirements Manager, Designer, Implementer, Integrator, Tester, or Validator
- Verifier SHALL NOT report to Project Manager (reports to VMGR)
- Verifier SHALL have authority to reject work products
- Verifier decisions CANNOT be overridden by PM or development team

**V&V Manager Independence (MANDATORY SIL 4)**:
- VMGR reports to Safety Authority / Customer (NOT to PM or COD)
- VMGR has final V&V approval authority
- VMGR manages Verifier team
- VMGR coordinates with COD but does not report to COD

#### 7.2 Verification Team Organization

**Organizational Structure (SIL 4)**:
```
        Safety Authority / Customer
                |
        ┌───────┴───────┐
        |               |
    COD (Lifecycle)  VMGR (Independent V&V)
        |               |
    PM (Team)       VER Team (Verification)
        |
    REQ, DES, IMP, INT, TST, QUA, CM, SAF
```

**Verification Team Roles**:
- **V&V Manager (VMGR)**: John Doe (independent, reports to Safety Authority)
- **Lead Verifier (VER-LEAD)**: Jane Smith (independent, reports to VMGR)
- **Verifier 1 (VER-1)**: Bob Jones (independent, requirements/design verification)
- **Verifier 2 (VER-2)**: Alice Williams (independent, code verification)
- **Verifier 3 (VER-3)**: Charlie Brown (independent, integration verification)

**Independence Assurance**:
- Verifiers have NOT participated in development activities for this project
- Verifiers are in separate organizational unit from development team
- Verifiers report to VMGR, not PM
- Verifiers have no schedule or cost pressures from PM

#### 7.3 Communication and Reporting

**Reporting Structure**:
1. VER team reports verification findings to VMGR
2. VMGR reviews and approves all Verification Reports
3. VMGR informs COD of V&V approval/rejection for gate check
4. COD enforces gate based on VMGR decision (CANNOT override VMGR)

**Defect Reporting**:
- VER discovers defect → logs in defect tracking system
- VER notifies VMGR and PM (informational)
- PM coordinates fix with development team
- VER re-verifies fix independently
- VMGR approves resolution

**Gate Check Process**:
- VER completes verification activities
- VER submits Verification Report to QUA (template compliance)
- QUA approves/rejects (1 pass only)
- VER submits to VMGR for technical review
- VMGR approves/rejects Verification Report
- VMGR informs COD of V&V decision (approve/reject)
- COD enforces gate (if VMGR rejects, gate BLOCKED)
```

---

## Step 8: Document Verification Plan

### 8.1 Software Verification Plan Template

```markdown
### 8. Software Verification Plan Document

**Document ID**: DOC-SVP-2026-001  
**Project**: Train Control System (TCS)  
**SIL Level**: SIL 4  
**Author**: Jane Smith (VER-LEAD)  
**Approved By**: John Doe (VMGR)  
**Date**: 2026-03-13

---

## Document Control

| Version | Date | Author | Change Description | Approval |
|---------|------|--------|-------------------|----------|
| 1.0 | 2026-03-13 | J. Smith | Initial release | J. Doe (VMGR) |

---

## Table of Contents

1. Introduction
2. Verification Context
3. Verification Techniques (Table A.5)
4. Static Analysis Strategy (Table A.19)
5. Test Coverage Requirements (Table A.21)
6. Verification Tools
7. Verification Activities per Phase
8. Independence Requirements
9. Verification Responsibilities
10. Verification Schedule
11. Verification Deliverables
12. Verification Criteria
13. Appendices

---

## 1. Introduction

### 1.1 Purpose
This Software Verification Plan defines the verification activities, techniques, tools, and responsibilities for the Train Control System (TCS) software development project.

### 1.2 Scope
This plan covers verification activities for all software lifecycle phases from Requirements (Phase 2) through Integration (Phase 6), supporting Validation (Phase 7) and Assessment (Phase 8).

### 1.3 References
- EN 50128:2011 Railway applications — Communication, signalling and processing systems — Software for railway control and protection systems
- Software Requirements Specification (DOC-SRS-2026-001)
- Software Quality Assurance Plan (DOC-SQAP-2026-001)
- Software Configuration Management Plan (DOC-SCMP-2026-001)

### 1.4 Definitions and Abbreviations
[See EN 50128 Section 3]

---

## 2. Verification Context

[Content from Step 1 above]

---

## 3. Verification Techniques (Table A.5)

[Content from Step 2 above]

---

## 4. Static Analysis Strategy (Table A.19)

[Content from Step 3 above]

---

## 5. Test Coverage Requirements (Table A.21)

[Content from Step 4 above]

---

## 6. Verification Tools

[Content from Step 5 above]

---

## 7. Verification Activities per Phase

[Content from Step 6 above]

---

## 8. Independence Requirements

[Content from Step 7 above]

---

## 9. Verification Responsibilities

### 9.1 Roles and Responsibilities

| Role | Name | Responsibilities |
|------|------|-----------------|
| **V&V Manager (VMGR)** | John Doe | Overall V&V authority, manage VER team, final V&V approval |
| **Lead Verifier (VER-LEAD)** | Jane Smith | Coordinate verification activities, author SVP, report to VMGR |
| **Verifier 1 (VER-1)** | Bob Jones | Requirements and design verification |
| **Verifier 2 (VER-2)** | Alice Williams | Code verification and static analysis |
| **Verifier 3 (VER-3)** | Charlie Brown | Integration verification |

### 9.2 Verification Authority

- Verifiers have authority to **reject** any work product that does not meet verification criteria
- Verifier rejections CANNOT be overridden by PM or development team
- VMGR has final V&V approval authority for all phases

---

## 10. Verification Schedule

### 10.1 Verification Milestones

| Phase | Milestone | Verification Activity | Duration | Completion Date |
|-------|-----------|----------------------|----------|----------------|
| Phase 2 | Requirements Complete | Requirements Verification | 2 weeks | 2026-04-15 |
| Phase 3 | Design Complete | Architecture & Design Verification | 3 weeks | 2026-06-01 |
| Phase 4 | Component Design Complete | Component Design Verification | 2 weeks | 2026-07-15 |
| Phase 5 | Code Complete | Source Code Verification | 4 weeks | 2026-10-01 |
| Phase 6 | Integration Complete | Integration Verification | 3 weeks | 2026-11-15 |

### 10.2 Verification Effort Estimate

| Phase | Verification Effort (person-weeks) |
|-------|-----------------------------------|
| Phase 2 | 4 |
| Phase 3 | 6 |
| Phase 4 | 4 |
| Phase 5 | 8 |
| Phase 6 | 6 |
| **Total** | **28** |

---

## 11. Verification Deliverables

### 11.1 Verification Reports

| # | Document | Author | Approver | Frequency |
|---|----------|--------|----------|-----------|
| DOC-SVP-2026-001 | Software Verification Plan | VER-LEAD | VMGR | Once |
| DOC-SQAP-VER-2026-001 | SQAP Verification Report | VER-1 | VMGR | Once (after SQAP) |
| DOC-SRS-VER-2026-001 | Software Requirements Verification Report | VER-1 | VMGR | Phase 2 |
| DOC-SAS-VER-2026-001 | SW Architecture & Design Verification Report | VER-1 | VMGR | Phase 3 |
| DOC-SCD-VER-2026-001 | Software Component Design Verification Report | VER-1 | VMGR | Phase 4 |
| DOC-SRC-VER-2026-001 | Software Source Code Verification Report | VER-2 | VMGR | Phase 5 |
| DOC-INT-VER-2026-001 | Software Integration Verification Report | VER-3 | VMGR | Phase 6 |
| DOC-VAL-VER-2026-001 | Software Validation Verification Report | VMGR | VAL | Phase 7 |

### 11.2 Traceability Matrices

- Traceability Matrix (Requirements Phase) - Phase 2
- Traceability Matrix (Design Phase) - Phase 3
- Traceability Matrix (Component Design Phase) - Phase 4
- Traceability Matrix (Code Phase) - Phase 5
- Traceability Matrix (Integration Phase) - Phase 6

### 11.3 Analysis Reports

- Static Analysis Report - Per commit (Phase 5)
- Complexity Metrics Report - Per commit (Phase 5)
- Coverage Report - Per test run (Phase 5, 6)
- Code Review Reports - Per module (Phase 5)

---

## 12. Verification Criteria

### 12.1 Entry Criteria (per phase)

**Requirements Phase**:
- [ ] Software Requirements Specification complete
- [ ] SQAP approved
- [ ] Verification team assigned

**Design Phase**:
- [ ] Software Architecture Specification complete
- [ ] Software Design Specification complete
- [ ] Requirements Verification passed

**Component Design Phase**:
- [ ] Software Component Design Specification complete
- [ ] Unit Test Specifications complete
- [ ] Design Verification passed

**Implementation Phase**:
- [ ] Source code complete
- [ ] Unit tests complete and passing
- [ ] Component Design Verification passed

**Integration Phase**:
- [ ] Software components integrated
- [ ] Integration tests complete and passing
- [ ] Source Code Verification passed

### 12.2 Exit Criteria (per phase)

**Requirements Phase**:
- [ ] All requirements reviewed and approved
- [ ] Zero open defects (severity Critical or High)
- [ ] Traceability matrix complete (system → software)
- [ ] Software Requirements Verification Report approved by VMGR

**Design Phase**:
- [ ] All design documents reviewed and approved
- [ ] Zero open defects (severity Critical or High)
- [ ] Traceability matrix complete (requirements → design)
- [ ] Architecture and Design Verification Report approved by VMGR

**Component Design Phase**:
- [ ] All component design documents reviewed and approved
- [ ] Unit test specifications approved
- [ ] Traceability matrix complete (design → component design → unit tests)
- [ ] Component Design Verification Report approved by VMGR

**Implementation Phase**:
- [ ] Static analysis passed (zero critical issues)
- [ ] Code review passed (all items approved)
- [ ] Complexity within limits (CCN ≤ 10 for SIL 4)
- [ ] Coverage targets met (100% statement, branch, condition for SIL 4)
- [ ] Traceability complete (design → code → tests)
- [ ] Software Source Code Verification Report approved by VMGR

**Integration Phase**:
- [ ] Integration tests passed
- [ ] Interface consistency verified
- [ ] Integration coverage targets met
- [ ] Software Integration Verification Report approved by VMGR

### 12.3 Acceptance Criteria

**Overall Verification Acceptance**:
- All Verification Reports approved by VMGR
- All traceability matrices complete and verified
- All static analysis passed (zero critical issues, zero MISRA C mandatory violations)
- All coverage targets met (100% statement, branch, condition for SIL 4)
- All code reviews passed
- All complexity metrics within limits (CCN ≤ 10 for SIL 4)
- Zero open defects severity Critical or High

---

## 13. Appendices

### Appendix A: Verification Checklists
- Requirements Review Checklist
- Architecture Review Checklist
- Design Review Checklist
- Code Review Checklist (124 items)
- Integration Test Review Checklist

### Appendix B: Tool Configuration Files
- Cppcheck project configuration
- PC-lint Plus configuration
- Clang analyzer configuration
- Lizard complexity configuration
- Coverage threshold configuration

### Appendix C: Traceability Tag Format
```c
/**
 * @brief Calculate train speed from wheel sensor
 * @trace REQ-FUNC-001 Train speed calculation
 * @trace DES-ARCH-003 Speed calculation module
 * @sil 4
 */
uint32_t calculate_train_speed(uint32_t wheel_pulses, uint32_t time_ms);
```

### Appendix D: Tool Qualification Reports
- Cppcheck Tool Qualification Report
- PC-lint Plus Tool Qualification Report
- Clang Static Analyzer Tool Qualification Report
- Lizard Tool Qualification Report
- gcov Tool Qualification Report
- GCC Compiler Tool Qualification Report

### Appendix E: Verification Metrics
- Defect density targets: < 0.1 defects per KLOC
- Code review coverage: 100% of all source code
- Static analysis coverage: 100% of all source code
- Test coverage: 100% statement, branch, condition (SIL 4)
```

---

## Step 9: Review and Approval

### 9.1 Quality Assurance Template Compliance Check

**Before VMGR review**, the Software Verification Plan MUST pass QUA template compliance check (MANDATORY SIL 3-4).

```bash
# QUA checks SVP template compliance
python3 tools/quality/check_template_compliance.py \
    --document DOC-SVP-2026-001.md \
    --template templates/Software-Verification-Plan-template.md \
    --sil 4

# Expected output:
# ✓ Document ID format: DOC-SVP-2026-001 (correct)
# ✓ Document Control table present
# ✓ Approvals table present with VMGR
# ✓ All required sections present
# ✓ EN 50128 references correct
# ✓ Table A.5 techniques documented
# ✓ Table A.19 techniques documented
# ✓ Table A.21 coverage requirements documented
# ✓ Independence requirements documented (SIL 4)
# ✓ Tool qualification documented
# TEMPLATE COMPLIANCE: PASS
```

**QUA Review Process**:
1. VER-LEAD submits SVP to QUA
2. QUA performs template compliance check (automated + manual)
3. QUA approves OR rejects with findings (1 pass only)
4. If rejected: VER-LEAD fixes issues and resubmits ONCE
5. If approved: SVP proceeds to VMGR technical review

### 9.2 VMGR Technical Review

**VMGR reviews SVP for technical correctness**:

```markdown
## VMGR Review Checklist

### Verification Scope
- [ ] All lifecycle phases covered (Requirements through Integration)
- [ ] SIL level correctly identified (SIL 4)
- [ ] Safety-critical functions identified

### Technique Selection (Table A.5)
- [ ] All MANDATORY techniques selected (Static Analysis, Testing, Traceability, Coverage)
- [ ] Highly Recommended techniques justified (Formal Proof, Metrics, SEEA, FTA)
- [ ] Technique combination justified per EN 50128 4.8, 4.9, 4.10

### Static Analysis (Table A.19)
- [ ] MANDATORY techniques selected (Control Flow, Data Flow)
- [ ] Highly Recommended techniques justified (Boundary Value, Range Checking, etc.)
- [ ] Tool configuration documented

### Coverage (Table A.21)
- [ ] 100% Statement coverage required (MANDATORY SIL 4)
- [ ] 100% Branch coverage required (MANDATORY SIL 4)
- [ ] 100% Condition coverage required (MANDATORY SIL 4)
- [ ] MC/DC coverage for safety functions (Highly Recommended)

### Tool Selection
- [ ] Tools appropriate for verification tasks
- [ ] Tool qualification process documented
- [ ] Tool configuration under version control

### Independence (SIL 4)
- [ ] Verifier independence documented
- [ ] VMGR independence documented
- [ ] Organizational structure shows separation
- [ ] Reporting structure correct (VER → VMGR, not PM)

### Verification Activities
- [ ] Activities defined for each phase
- [ ] Entry/exit criteria defined
- [ ] Verification deliverables identified
- [ ] Verification schedule realistic

### Completeness
- [ ] All EN 50128 6.2.4.9 requirements addressed
- [ ] All verification reports identified
- [ ] Traceability approach documented
- [ ] Defect management process defined

**VMGR Decision**: ☐ APPROVE  ☐ REJECT  ☐ APPROVE WITH COMMENTS

**VMGR Signature**: ___________________________  Date: ___________
```

### 9.3 PM/COD Approval and Baseline

**After VMGR approval**:

1. **PM Review**:
   - Verify resource allocation (verification team)
   - Verify schedule (verification milestones)
   - Approve budget for tools and training
   - PM signature

2. **COD Approval**:
   - Verify SVP aligns with overall lifecycle plan
   - Verify independence requirements met (SIL 4)
   - Approve SVP as project baseline
   - COD signature

3. **Baseline**:
   - CM places SVP under configuration control
   - SVP baseline label: `SVP-v1.0-BASELINE`
   - Changes require CCB approval

```bash
# Baseline SVP in Git
git tag -a SVP-v1.0-BASELINE -m "Software Verification Plan baseline"
git push origin SVP-v1.0-BASELINE

# Record baseline in SCMP
echo "DOC-SVP-2026-001.md | SVP-v1.0-BASELINE | 2026-03-13 | Approved by VMGR/PM/COD" \
    >> docs/baselines.log
```

---

## Verification Planning Checklist

### Planning Checklist

Use this checklist to ensure all verification planning steps are complete:

**Step 1: Establish Context**
- [ ] SIL level identified and documented
- [ ] Project scope defined
- [ ] Safety-critical functions identified
- [ ] Lifecycle model documented

**Step 2: Select Verification Techniques (Table A.5)**
- [ ] All MANDATORY techniques selected (SIL 3-4: Static Analysis, Testing, Traceability, Coverage)
- [ ] Highly Recommended techniques selected (SIL 3-4: Formal Proof, Metrics, SEEA, FTA)
- [ ] Technique combination justified per EN 50128 4.8, 4.9, 4.10

**Step 3: Define Static Analysis Strategy (Table A.19)**
- [ ] MANDATORY techniques selected (SIL 3-4: Control Flow, Data Flow)
- [ ] Highly Recommended techniques selected (Boundary Value, Range Checking, Code Review, etc.)
- [ ] Tool configuration documented (Cppcheck, PC-lint, Clang)

**Step 4: Define Coverage Requirements (Table A.21)**
- [ ] Statement coverage target: 100% (MANDATORY SIL 2+)
- [ ] Branch coverage target: 100% (MANDATORY SIL 2+)
- [ ] Condition coverage target: 100% (MANDATORY SIL 3-4)
- [ ] MC/DC coverage for safety functions (Highly Recommended SIL 3-4)

**Step 5: Select and Qualify Tools**
- [ ] All verification tools selected (static analysis, coverage, testing)
- [ ] Tool classification determined (T1, T2, T3)
- [ ] Tool qualification process documented
- [ ] Tool configuration under version control

**Step 6: Define Verification Activities per Phase**
- [ ] Requirements verification activities defined (7.2.4.22)
- [ ] Architecture & design verification activities defined (7.3.4.41, 7.3.4.42)
- [ ] Component design verification activities defined (7.4.4.13)
- [ ] Source code verification activities defined (7.5.4.10)
- [ ] Integration verification activities defined (7.6.4.13)

**Step 7: Establish Independence Requirements**
- [ ] Verifier independence documented (MANDATORY SIL 3-4)
- [ ] VMGR independence documented (MANDATORY SIL 3-4)
- [ ] Organizational structure documented
- [ ] Reporting structure correct (VER → VMGR, VMGR → Safety Authority)

**Step 8: Document Verification Plan**
- [ ] SVP document created from template
- [ ] All sections complete per EN 50128 6.2.4.9
- [ ] Verification activities documented per phase
- [ ] Verification deliverables identified
- [ ] Verification schedule documented
- [ ] Entry/exit criteria defined per phase

**Step 9: Review and Approval**
- [ ] QUA template compliance check passed
- [ ] VMGR technical review passed
- [ ] PM approved (resources, schedule, budget)
- [ ] COD approved and baselined
- [ ] SVP under configuration control

---

## Tool Integration Commands

### Verification Planning Tool Commands

```bash
# 1. Create Software Verification Plan from template
python3 tools/documents/create_document.py \
    --template templates/Software-Verification-Plan-template.md \
    --output DOC-SVP-2026-001.md \
    --project "Train Control System" \
    --sil 4

# 2. Extract safety requirements for verification planning
python3 tools/requirements/extract_requirements.py \
    --input DOC-SRS-*.md \
    --filter safety \
    --output safety_requirements.yaml

# 3. Generate verification technique selection (Table A.5)
python3 tools/verification/select_techniques.py \
    --sil 4 \
    --output verification_techniques.md

# 4. Generate static analysis strategy (Table A.19)
python3 tools/verification/static_analysis_strategy.py \
    --sil 4 \
    --output static_analysis_strategy.md

# 5. Generate coverage requirements (Table A.21)
python3 tools/verification/coverage_requirements.py \
    --sil 4 \
    --output coverage_requirements.md

# 6. Check tool availability
./install_tools.sh --check

# 7. Generate tool qualification checklist
python3 tools/verification/tool_qualification_checklist.py \
    --tool cppcheck \
    --version 2.13.0 \
    --classification T2 \
    --output tool-qualification/cppcheck-checklist.md

# 8. Verify SVP template compliance (QUA check)
python3 tools/quality/check_template_compliance.py \
    --document DOC-SVP-2026-001.md \
    --template templates/Software-Verification-Plan-template.md \
    --sil 4

# 9. Baseline SVP
git tag -a SVP-v1.0-BASELINE -m "Software Verification Plan baseline"
git push origin SVP-v1.0-BASELINE
```

---

## Example Verification Plan Outline

### Minimal SVP Outline (SIL 0-1)

For SIL 0-1 projects, a simplified SVP is acceptable:

```markdown
# Software Verification Plan (SIL 1)

## 1. Introduction
- Project: [Name]
- SIL Level: 1
- Scope: [Phases covered]

## 2. Verification Techniques
- Static Analysis: Recommended (Cppcheck)
- Traceability: Recommended (@trace tags)
- Code Review: Highly Recommended (peer review)
- Testing: Highly Recommended (unit tests)

## 3. Verification Activities
- Requirements Review
- Design Review
- Code Review
- Unit Testing

## 4. Verification Tools
- Cppcheck 2.13.0 (static analysis)
- gcov (coverage measurement, target 90%)
- Unity (unit testing framework)

## 5. Verification Responsibilities
- Verifier: [Name]
- Reviewer: [Name]

## 6. Verification Deliverables
- Requirements Verification Report
- Design Verification Report
- Code Verification Report

## 7. Verification Criteria
- Zero critical defects
- 90% code coverage
- All code reviewed
```

### Full SVP Outline (SIL 3-4)

For SIL 3-4 projects, a comprehensive SVP is MANDATORY (see Step 8.1 above for full template).

---

## Summary

This workflow provides a comprehensive, step-by-step process for creating a Software Verification Plan compliant with EN 50128:

1. **Establish context**: Understand SIL level, project scope, safety requirements
2. **Select techniques**: Choose verification techniques from EN 50128 Tables A.5, A.19, A.21
3. **Define strategies**: Detail static analysis, coverage, and testing strategies
4. **Qualify tools**: Select and qualify verification tools per EN 50128 Annex B.7
5. **Plan activities**: Define verification activities for each lifecycle phase
6. **Ensure independence**: Establish independent verification organization (SIL 3-4)
7. **Document plan**: Create comprehensive SVP document
8. **Review and approve**: QUA template check → VMGR technical review → PM/COD approval

**Key Success Factors**:
- Early planning (create SVP before design phase)
- Clear technique selection with justification
- Tool qualification before use
- Independent verification team (SIL 3-4)
- Comprehensive documentation
- Rigorous review and approval process

**Next Steps**:
- Proceed to `workflows/static-analysis-workflow.md` to execute static analysis
- Proceed to `workflows/traceability-verification.md` to verify traceability
- Proceed to `workflows/verification-reporting.md` to create Verification Reports
