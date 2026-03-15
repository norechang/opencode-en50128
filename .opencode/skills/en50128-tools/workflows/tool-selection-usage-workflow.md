# Tool Selection and Usage Workflow

**EN 50128 Reference**: Section 6.7 - Software tools and their validation  
**Scope**: Tool selection criteria and usage patterns for SIL 0-4 projects  
**Target Roles**: All agents (REQ, DES, IMP, TST, VER, INT, VAL, SAF, QUA, CM, PM, COD)  
**Document**: This workflow guides agents in selecting and using appropriate tools

---

## Table of Contents

1. [Overview](#1-overview)
2. [Tool Selection Process](#2-tool-selection-process)
3. [Tool Selection by Agent Role](#3-tool-selection-by-agent-role)
4. [SIL-Specific Tool Requirements](#4-sil-specific-tool-requirements)
5. [Tool Usage Patterns](#5-tool-usage-patterns)
6. [Tool Integration Examples](#6-tool-integration-examples)
7. [Tool Troubleshooting](#7-tool-troubleshooting)
8. [References](#8-references)

---

## 1. Overview

### 1.1 Purpose

This workflow provides guidance for agents on:
- **Selecting appropriate tools** for each development task
- **Using tools correctly** according to EN 50128 requirements
- **Verifying tool results** to ensure correctness
- **Integrating tools** into development workflows

### 1.2 Tool Catalog Reference

All tools referenced in this workflow are documented in `TOOLS.md`.

**Tool Categories**:
1. **Development tools**: Compilers, editors, build systems
2. **Verification tools**: Static analyzers, complexity analyzers
3. **Testing tools**: Test frameworks, coverage tools
4. **Analysis tools**: Memory analyzers, profilers
5. **Management tools**: Version control, workflow management, traceability
6. **Custom EN50128 tools**: Python scripts for EN 50128-specific tasks

### 1.3 Tool Qualification Status

Before using any tool, agents MUST verify:
- ✅ Tool is qualified/validated (per Tool Qualification Workflow)
- ✅ Tool version matches baseline (check Tool-Baseline.md)
- ✅ Tool classification is appropriate for task (T1/T2/T3)

```bash
# Check tool qualification status
cat docs/tool-qualification/Tool-Baseline.md | grep <tool-name>

# Verify tool version
<tool-name> --version

# Check Tool Qualification Report exists
ls docs/tool-qualification/*-Qualification-Report.md
```

---

## 2. Tool Selection Process

### 2.1 Tool Selection Decision Tree

```
START: Need to perform a task
  |
  ├─ What is the task category?
  │   ├─ Compilation/Build → Section 2.2: Development Tools
  │   ├─ Static Analysis → Section 2.3: Verification Tools
  │   ├─ Testing → Section 2.4: Testing Tools
  │   ├─ Memory Analysis → Section 2.5: Analysis Tools
  │   ├─ Version Control → Section 2.6: Management Tools
  │   └─ EN 50128-specific → Section 2.7: Custom Tools
  |
  ├─ What is the SIL level?
  │   ├─ SIL 0-1 → Fewer tool requirements
  │   ├─ SIL 2 → More tool requirements
  │   └─ SIL 3-4 → MANDATORY tool requirements
  |
  ├─ Is the tool qualified?
  │   ├─ YES → Proceed to usage
  │   └─ NO → Qualify tool first (Tool Qualification Workflow)
  |
  └─ Use tool according to Section 5: Tool Usage Patterns
```

### 2.2 Development Tools Selection

**Task**: Compile C source code, build executables

**Tool Selection**:

| SIL Level | Compiler | Build System | Editor | Notes |
|-----------|----------|--------------|--------|-------|
| **SIL 0-1** | GCC (any recent version) | Make or CMake | Any editor | Tool qualification recommended |
| **SIL 2** | GCC (baselined version) | Make | Any editor | Tool qualification MANDATORY |
| **SIL 3-4** | **GCC (qualified, version locked)** | **Make (qualified)** | Any editor (T1) | Full qualification MANDATORY |

**Selected Tools**:
- **Compiler**: GCC 13.3.0 (T3 - qualified per DOC-TQR-GCC-001)
- **Build System**: GNU Make 4.3 (T2 - validated)
- **Editor**: vim/emacs/vscode (T1 - no qualification, code reviewed)

**Usage**: See Section 5.1 for compilation patterns.

### 2.3 Verification Tools Selection

**Task**: Static analysis, complexity analysis, MISRA C checking

**Tool Selection**:

| SIL Level | Static Analysis | Complexity | MISRA C Checker | Notes |
|-----------|----------------|------------|-----------------|-------|
| **SIL 0-1** | Cppcheck (recommended) | Lizard (recommended) | Optional | Basic validation |
| **SIL 2** | Cppcheck (validated) | Lizard (validated) | Cppcheck + PC-lint | Validation MANDATORY |
| **SIL 3-4** | **Cppcheck + Clang (both validated)** | **Lizard (validated)** | **PC-lint Plus (certified)** | Multiple tools MANDATORY |

**Selected Tools (SIL 3)**:
- **Static Analyzer #1**: Cppcheck 2.13.0 (T2 - validated per DOC-TVR-CPPCHECK-001)
- **Static Analyzer #2**: Clang Static Analyzer 18.x (T2 - validated)
- **Complexity Analyzer**: Lizard 1.17.x (T2 - validated per DOC-TVR-LIZARD-001)
- **MISRA C Checker**: PC-lint Plus (T2 - certified by Gimpel Software)

**Usage**: See Section 5.2 for verification patterns.

### 2.4 Testing Tools Selection

**Task**: Unit testing, integration testing, coverage measurement

**Tool Selection**:

| SIL Level | Test Framework | Coverage Tool | MC/DC Analysis | Notes |
|-----------|----------------|---------------|----------------|-------|
| **SIL 0-1** | Unity or CUnit | gcov/lcov | Not required | Basic testing |
| **SIL 2** | Unity or CUnit | gcov/lcov (validated) | Recommended | Branch coverage MANDATORY |
| **SIL 3-4** | **Unity (validated)** | **gcov/lcov (validated)** | **MANDATORY (mcdc_analyzer.py)** | Condition coverage MANDATORY |

**Selected Tools (SIL 3)**:
- **Test Framework**: Unity 2.5.x (T2 - validated per DOC-TVR-UNITY-001)
- **Coverage Tool**: gcov 13.3.0 + lcov 1.16 (T2 - validated)
- **MC/DC Analyzer**: mcdc_analyzer.py (T1 - output verified, custom tool)

**Usage**: See Section 5.3 for testing patterns.

### 2.5 Analysis Tools Selection

**Task**: Memory leak detection, runtime error detection

**Tool Selection**:

| SIL Level | Memory Analyzer | Runtime Sanitizer | Notes |
|-----------|-----------------|-------------------|-------|
| **SIL 0-1** | Valgrind (recommended) | AddressSanitizer (optional) | Basic analysis |
| **SIL 2** | Valgrind (highly recommended) | AddressSanitizer (recommended) | Findings manually reviewed |
| **SIL 3-4** | **Valgrind (highly recommended)** | **AddressSanitizer (recommended)** | All findings MUST be reviewed |

**Selected Tools (SIL 3)**:
- **Memory Analyzer**: Valgrind 3.21.0 (T1 - findings verified by code review)
- **Runtime Sanitizer**: AddressSanitizer (GCC built-in, T1)

**Usage**: See Section 5.4 for analysis patterns.

### 2.6 Management Tools Selection

**Task**: Version control, configuration management, workflow management

**Tool Selection**:

| SIL Level | Version Control | Workflow Manager | Traceability Manager | Notes |
|-----------|----------------|------------------|----------------------|-------|
| **SIL 0-1** | Git | Optional | Optional | Basic CM |
| **SIL 2** | Git (version recorded) | workspace.py wf | workspace.py trace | CM MANDATORY |
| **SIL 3-4** | **Git (version locked)** | **workspace.py wf (required)** | **workspace.py trace (required)** | Full CM MANDATORY |

**Selected Tools (SIL 3)**:
- **Version Control**: Git 2.43.0 (T1 - repository state verified by CM audits)
- **Workflow Manager**: workspace.py wf (T1 - workflow state verified by reviews)
- **Traceability Manager**: workspace.py trace (T1 - traceability verified by reviews)

**Usage**: See Section 5.5 for management patterns.

### 2.7 Custom EN50128 Tools Selection

**Task**: EN 50128-specific tasks (traceability, validation, reports)

**Custom Tools Available**:

| Tool | Purpose | Classification | Status |
|------|---------|----------------|--------|
| **workspace.py trace** | Traceability management | T1 (output verified) | ✅ Production-ready |
| **workspace.py wf** | Workflow management | T1 (workflow verified) | ✅ Production-ready |
| **validate_srs_template.py** | SRS template validation | T1 (findings verified) | ✅ Production-ready |
| **validate_sas_sds_template.py** | SAS/SDS template validation | T1 (findings verified) | ✅ Production-ready |
| **validate_test_doc_template.py** | Test doc template validation | T1 (findings verified) | ✅ Production-ready |
| **mcdc_analyzer.py** | MC/DC coverage analysis | T1 (results verified) | ✅ Production-ready |
| **enhelp.py** | EN 50128 reference lookup | T1 (information only) | ✅ Production-ready |

**Usage**: See Section 6 for integration examples.

---

## 3. Tool Selection by Agent Role

### 3.1 Requirements Engineer (REQ) Tools

**Primary Tasks**:
- Requirements elicitation
- Requirements specification
- Traceability management

**Tools Required**:

| Tool | Purpose | Usage Frequency |
|------|---------|-----------------|
| **Markdown editor** | Write Software Requirements Specification | Daily |
| **workspace.py trace** | Manage requirements traceability | Daily |
| **workspace.py wf** | Submit SRS for review/approval | Per document |
| **validate_srs_template.py** | Validate SRS template compliance | Per document |
| **Git** | Version control of requirements | Daily |
| **enhelp.py** | EN 50128 reference (Table A.2) | As needed |

**Tool Usage Example**:

```bash
# REQ agent workflow
# Step 1: Create SRS using template
cp .opencode/skills/en50128-requirements/templates/Software-Requirements-Specification-template.md \
   docs/requirements/SRS_Project.md

# Step 2: Edit SRS (use any editor)
vim docs/requirements/SRS_Project.md

# Step 3: Validate SRS template compliance
python3 tools/scripts/validate_srs_template.py docs/requirements/SRS_Project.md --sil 3

# Step 4: Add traceability links
python3 tools/workspace.py trace add \
  --from "SYS-REQ-001" \
  --to "REQ-FUNC-001" \
  --type "system-to-sw"

# Step 5: Submit SRS for review
python3 tools/workspace.py wf submit \
  --document "docs/requirements/SRS_Project.md" \
  --type "SRS" \
  --version "1.0" \
  --approver "QUA" \
  --sil 3

# Step 6: Commit to version control
git add docs/requirements/SRS_Project.md
git commit -m "Add SRS for Project (REQ-001)"
```

### 3.2 Designer (DES) Tools

**Primary Tasks**:
- Software architecture design
- Software detailed design
- Interface design

**Tools Required**:

| Tool | Purpose | Usage Frequency |
|------|---------|-----------------|
| **Markdown editor** | Write SAS/SDS | Daily |
| **Graphviz (dot)** | Generate architecture diagrams | Per design |
| **workspace.py trace** | Manage design traceability (SRS → SAS → SDS) | Daily |
| **workspace.py wf** | Submit SAS/SDS for review | Per document |
| **validate_sas_sds_template.py** | Validate SAS/SDS template compliance | Per document |
| **Git** | Version control of design | Daily |

**Tool Usage Example**:

```bash
# DES agent workflow
# Step 1: Create SAS using template
cp .opencode/skills/en50128-design/templates/Software-Architecture-Specification-template.md \
   docs/design/SAS_Project.md

# Step 2: Edit SAS (add modules, interfaces)
vim docs/design/SAS_Project.md

# Step 3: Generate architecture diagram
dot -Tpng docs/design/architecture.dot -o docs/design/architecture.png

# Step 4: Validate SAS template compliance
python3 tools/scripts/validate_sas_sds_template.py docs/design/SAS_Project.md --type SAS --sil 3

# Step 5: Add traceability (SRS → SAS)
python3 tools/workspace.py trace add \
  --from "REQ-FUNC-001" \
  --to "MOD-CTRL" \
  --type "sw-to-arch"

# Step 6: Submit SAS for review
python3 tools/workspace.py wf submit \
  --document "docs/design/SAS_Project.md" \
  --type "SAS" \
  --version "1.0" \
  --approver "QUA" \
  --sil 3
```

### 3.3 Implementer (IMP) Tools

**Primary Tasks**:
- C code implementation
- Unit test implementation
- MISRA C compliance

**Tools Required**:

| Tool | Purpose | Usage Frequency |
|------|---------|-----------------|
| **GCC (qualified)** | Compile C code | Every build |
| **Make** | Build system | Every build |
| **Code editor** | Write C code | Daily |
| **Cppcheck** | Static analysis (pre-commit) | Every commit |
| **Unity** | Unit test framework | Per unit test |
| **gcov/lcov** | Unit test coverage | Per unit test run |
| **Git** | Version control | Daily |

**Tool Usage Example**:

```bash
# IMP agent workflow
# Step 1: Implement C module
vim src/control/door_controller.c

# Step 2: Implement unit tests
vim tests/unit/test_door_controller.c

# Step 3: Build code (with SIL 3 flags)
make CFLAGS="-std=c11 -Wall -Wextra -Werror -DSIL_LEVEL=3" all

# Step 4: Run unit tests with coverage
make test-coverage

# Step 5: Check coverage (SIL 3: 100% required)
lcov --summary coverage.info
# Expected: 100% line coverage, 100% branch coverage

# Step 6: Run static analysis
cppcheck --enable=all --xml src/control/door_controller.c 2> cppcheck-report.xml

# Step 7: Commit code
git add src/control/door_controller.c tests/unit/test_door_controller.c
git commit -m "Implement door_controller module (IMP-001)"
```

### 3.4 Tester (TST) Tools

**Primary Tasks**:
- Integration testing
- Test execution
- Coverage analysis

**Tools Required**:

| Tool | Purpose | Usage Frequency |
|------|---------|-----------------|
| **Unity** | Test framework | Daily |
| **gcov/lcov** | Coverage measurement | Every test run |
| **mcdc_analyzer.py** | MC/DC analysis (SIL 3-4) | Every test run |
| **Make** | Build test executables | Every test run |
| **Git** | Version control of tests | Daily |

**Tool Usage Example**:

```bash
# TST agent workflow
# Step 1: Build tests
make tests

# Step 2: Run tests with coverage instrumentation
make test-coverage

# Step 3: Generate coverage report
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage-report

# Step 4: Analyze MC/DC coverage (SIL 3)
python3 tools/mcdc/mcdc_analyzer.py \
  --gcda tests/unit/test_door_controller.gcda \
  --source src/control/door_controller.c \
  --output mcdc-report.json

# Step 5: Verify coverage meets SIL requirements
# SIL 3: Statement 100%, Branch 100%, MC/DC 100%
python3 tools/scripts/check_coverage_sil.py coverage.info --sil 3
```

### 3.5 Verifier (VER) Tools

**Primary Tasks**:
- Static analysis
- Complexity analysis
- Verification evidence collection

**Tools Required**:

| Tool | Purpose | Usage Frequency |
|------|---------|-----------------|
| **Cppcheck (validated)** | Static analysis | Per verification run |
| **Clang Static Analyzer** | Static analysis (cross-check) | Per verification run |
| **Lizard** | Complexity analysis | Per verification run |
| **gcov/lcov** | Coverage verification | Per verification run |
| **Git** | Access to source code | Daily |

**Tool Usage Example**:

```bash
# VER agent workflow
# Step 1: Run static analysis with Cppcheck
cppcheck --enable=all --xml --xml-version=2 \
  --suppress=missingInclude \
  src/ 2> verification/cppcheck-report.xml

# Step 2: Run static analysis with Clang (cross-check)
scan-build -o verification/clang-analysis make

# Step 3: Run complexity analysis
lizard -l c -C 10 -w src/ > verification/complexity-report.txt
# SIL 3 requirement: CCN ≤ 10

# Step 4: Verify coverage (cross-check TST results)
lcov --summary coverage.info > verification/coverage-summary.txt

# Step 5: Create Verification Report
# Document all findings, evidence, conclusions
```

### 3.6 Integrator (INT) Tools

**Primary Tasks**:
- Component integration
- Integration testing
- Interface testing

**Tools Required**:

| Tool | Purpose | Usage Frequency |
|------|---------|-----------------|
| **GCC** | Build integrated system | Every integration |
| **Make** | Build system | Every integration |
| **Unity** | Integration test framework | Daily |
| **Valgrind** | Memory leak detection | Per integration test |
| **Git** | Version control | Daily |

**Tool Usage Example**:

```bash
# INT agent workflow
# Step 1: Build integrated system
make clean
make all

# Step 2: Run integration tests
make integration-tests

# Step 3: Run memory leak detection
valgrind --leak-check=full --track-origins=yes \
  ./tests/integration/integration_test > valgrind-report.txt 2>&1

# Step 4: Analyze Valgrind results
grep "definitely lost" valgrind-report.txt
# Expected: "0 bytes in 0 blocks" (no leaks)
```

### 3.7 Validator (VAL) Tools

**Primary Tasks**:
- System validation
- Acceptance testing
- Operational scenario testing

**Tools Required**:

| Tool | Purpose | Usage Frequency |
|------|---------|-----------------|
| **Test executables** | System testing | Daily |
| **Validation test scripts** | Automated validation | Daily |
| **Git** | Access to validated baseline | Daily |

**Tool Usage Example**:

```bash
# VAL agent workflow
# Step 1: Build release version
make release

# Step 2: Run system validation tests
./tests/validation/run-all-validation-tests.sh

# Step 3: Document validation results
# Create Validation Report with test results
```

### 3.8 Quality Assurance (QUA) Tools

**Primary Tasks**:
- Code review
- Document review
- Quality audits

**Tools Required**:

| Tool | Purpose | Usage Frequency |
|------|---------|-----------------|
| **Git** | Access to code/documents | Daily |
| **Cppcheck** | Static analysis review | Per code review |
| **Lizard** | Complexity review | Per code review |
| **validate_*_template.py** | Document template compliance | Per document review |
| **workspace.py wf** | Approve/reject documents | Daily |

**Tool Usage Example**:

```bash
# QUA agent workflow
# Step 1: Review code for MISRA C compliance
cppcheck --enable=all src/module.c

# Step 2: Review complexity
lizard -l c src/module.c
# Check: All functions CCN ≤ 10 (SIL 3)

# Step 3: Review document template compliance
python3 tools/scripts/validate_srs_template.py docs/requirements/SRS.md --sil 3

# Step 4: Approve document in workflow
python3 tools/workspace.py wf approve \
  --workflow-id "WF-2026-040" \
  --approver "QUA" \
  --decision "APPROVE" \
  --comment "SRS complies with template, all reviews passed"
```

### 3.9 Configuration Manager (CM) Tools

**Primary Tasks**:
- Version control
- Change control
- Baseline management

**Tools Required**:

| Tool | Purpose | Usage Frequency |
|------|---------|-----------------|
| **Git** | Version control system | Daily |
| **workspace.py wf** | Change request workflow | Per CR |
| **workspace.py trace** | Traceability audit | Weekly |

**Tool Usage Example**:

```bash
# CM agent workflow
# Step 1: Create baseline
git tag -a baseline-v1.0 -m "Baseline version 1.0 (Phase 4 complete)"
git push --tags

# Step 2: Audit traceability
python3 tools/workspace.py trace report \
  --report-type orphan-requirements \
  --output traceability-audit.txt

# Step 3: Review change requests
python3 tools/workspace.py wf status --filter "type=CR"
```

### 3.10 Lifecycle Coordinator (COD) Tools

**Primary Tasks**:
- Lifecycle orchestration
- Phase gate enforcement
- Compliance monitoring

**Tools Required**:

| Tool | Purpose | Usage Frequency |
|------|---------|-----------------|
| **workspace.py wf** | Document workflow status | Daily |
| **workspace.py trace** | Traceability status | Daily |
| **Git** | Access to all artifacts | Daily |
| **enhelp.py** | EN 50128 reference | Daily |

**Tool Usage Example**:

```bash
# COD agent workflow
# Step 1: Check phase gate criteria
python3 tools/workspace.py wf status --filter "phase=requirements"

# Step 2: Verify traceability completeness
python3 tools/workspace.py trace report --report-type coverage

# Step 3: Authorize phase transition (if criteria met)
# Update LIFECYCLE_STATE.md
```

---

## 4. SIL-Specific Tool Requirements

### 4.1 SIL 0 Tool Requirements

**Tool Qualification**: Recommended (not mandatory)

**Minimum Tool Set**:
- Compiler: GCC (any recent version)
- Build: Make
- Version Control: Git
- Editor: Any

**Verification Tools**: Recommended but not required
- Static analysis: Optional
- Coverage: Optional

**Process**: Lightweight tool qualification recommended for reproducibility.

### 4.2 SIL 1-2 Tool Requirements

**Tool Qualification**: MANDATORY for T2 and T3 tools

**Minimum Tool Set**:
- Compiler: GCC (baselined version, T3 qualification required)
- Build: Make (T2 validation required)
- Static Analyzer: Cppcheck (T2 validation required)
- Coverage: gcov/lcov (T2 validation required)
- Version Control: Git (T1, version recorded)

**Verification Tools**: MANDATORY
- Static analysis: Cppcheck (validated)
- Complexity: Lizard (validated)
- Coverage: gcov/lcov (validated)
- SIL 2 coverage requirement: Statement (HR), Branch (**M**)

**Process**: Tool Qualification Reports required for T2/T3 tools (highly recommended).

### 4.3 SIL 3-4 Tool Requirements

**Tool Qualification**: MANDATORY for T2 and T3 tools

**Minimum Tool Set**:
- Compiler: GCC (qualified, version locked, T3)
- Build: Make (validated, T2)
- Static Analyzer #1: Cppcheck (validated, T2)
- Static Analyzer #2: Clang (validated, T2) - **Multiple tools required**
- Complexity: Lizard (validated, CCN ≤ 10, T2)
- Coverage: gcov/lcov (validated, T2)
- MC/DC: mcdc_analyzer.py (T1)
- Version Control: Git (T1, version locked)
- Workflow Manager: workspace.py wf (T1, required)
- Traceability Manager: workspace.py trace (T1, required)

**Verification Tools**: MANDATORY (multiple tools for cross-checking)
- Static analysis: Cppcheck **AND** Clang (both validated)
- Complexity: Lizard (validated, CCN ≤ 10)
- Coverage: gcov/lcov (validated)
- SIL 3-4 coverage requirement: Statement (**M** 100%), Branch (**M** 100%), MC/DC (**M** 100%)

**Process**: 
- Tool Qualification Reports **MANDATORY** for all T2/T3 tools
- Tool versions **LOCKED** (any update requires re-qualification + CR)
- CI/CD tool version checks **MANDATORY**
- Independent verification tools (cross-checking)

---

## 5. Tool Usage Patterns

### 5.1 Compilation Pattern (GCC)

**Standard SIL 3 Compilation Flags**:

```bash
# SIL 3 compilation flags (from qualified GCC usage)
CFLAGS="-std=c11 \
        -Wall -Wextra -Werror -pedantic \
        -O2 \
        -DSIL_LEVEL=3 \
        -DMISRA_C_2012 \
        -fstack-protector-strong \
        -D_FORTIFY_SOURCE=2 \
        -fno-common \
        -fno-builtin-malloc -fno-builtin-calloc"

# Compile
gcc $CFLAGS -c src/module.c -o obj/module.o

# Link
gcc $CFLAGS obj/*.o -o bin/executable
```

**Makefile Pattern**:

```makefile
# SIL 3 Makefile
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic -O2 \
         -DSIL_LEVEL=3 -DMISRA_C_2012 \
         -fstack-protector-strong -D_FORTIFY_SOURCE=2 \
         -fno-common -fno-builtin-malloc -fno-builtin-calloc

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

all: bin/executable

bin/executable: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) bin/executable
```

### 5.2 Static Analysis Pattern (Cppcheck + Clang)

**Cppcheck Pattern (T2 validated tool)**:

```bash
# Run Cppcheck (per Tool Validation Report DOC-TVR-CPPCHECK-001)
cppcheck --enable=all \
         --xml --xml-version=2 \
         --suppress=missingInclude \
         --inline-suppr \
         src/ 2> verification/cppcheck-report.xml

# Parse results
grep "<error " verification/cppcheck-report.xml | wc -l
# Expected: 0 errors for SIL 3 critical code
```

**Clang Static Analyzer Pattern (T2 validated tool, cross-check)**:

```bash
# Run Clang analyzer (cross-check Cppcheck)
scan-build -o verification/clang-analysis \
           --status-bugs \
           make clean all

# Check results
ls verification/clang-analysis/
# Expected: No bug reports for SIL 3 critical code
```

**Combined Analysis Pattern (SIL 3-4 REQUIRED)**:

```bash
# VER agent: Run both analyzers (SIL 3 requirement)
echo "Running static analysis (SIL 3: multiple tools required)"

# Analyzer 1: Cppcheck
cppcheck --enable=all --xml src/ 2> verification/cppcheck-report.xml
CPPCHECK_ERRORS=$(grep -c "<error " verification/cppcheck-report.xml)

# Analyzer 2: Clang
scan-build -o verification/clang-analysis make clean all
CLANG_BUGS=$(ls verification/clang-analysis/ | wc -l)

# Report
echo "Cppcheck errors: $CPPCHECK_ERRORS"
echo "Clang bugs: $CLANG_BUGS"

if [ $CPPCHECK_ERRORS -eq 0 ] && [ $CLANG_BUGS -eq 0 ]; then
    echo "✅ Static analysis PASSED (both tools)"
else
    echo "❌ Static analysis FAILED"
    exit 1
fi
```

### 5.3 Coverage Analysis Pattern (gcov/lcov)

**Coverage Measurement Pattern (SIL 3)**:

```bash
# Step 1: Compile with coverage instrumentation
make clean
make CFLAGS="$CFLAGS --coverage" tests

# Step 2: Run tests
./tests/unit/test_all

# Step 3: Generate coverage data
lcov --capture --directory . --output-file coverage.info

# Step 4: Filter out system headers
lcov --remove coverage.info '/usr/*' --output-file coverage.info

# Step 5: Generate HTML report
genhtml coverage.info --output-directory coverage-report

# Step 6: Check coverage percentages
lcov --summary coverage.info
# SIL 3 requirement: Statement 100%, Branch 100%
```

**Coverage Verification Pattern (SIL 3)**:

```bash
# Verify coverage meets SIL requirements
STATEMENT_COV=$(lcov --summary coverage.info | grep "lines" | awk '{print $2}' | sed 's/%//')
BRANCH_COV=$(lcov --summary coverage.info | grep "branches" | awk '{print $2}' | sed 's/%//')

if (( $(echo "$STATEMENT_COV >= 100" | bc -l) )) && \
   (( $(echo "$BRANCH_COV >= 100" | bc -l) )); then
    echo "✅ Coverage PASSED (Statement: $STATEMENT_COV%, Branch: $BRANCH_COV%)"
else
    echo "❌ Coverage FAILED (SIL 3 requires 100%)"
    echo "   Statement: $STATEMENT_COV% (required: 100%)"
    echo "   Branch: $BRANCH_COV% (required: 100%)"
    exit 1
fi
```

### 5.4 Memory Analysis Pattern (Valgrind)

**Valgrind Pattern (T1 tool, findings verified)**:

```bash
# Run Valgrind memory leak detection
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-report.txt \
         ./executable

# Check for leaks
grep "definitely lost" valgrind-report.txt
# Expected: "0 bytes in 0 blocks"

grep "indirectly lost" valgrind-report.txt
# Expected: "0 bytes in 0 blocks"

# Verify no errors
grep "ERROR SUMMARY" valgrind-report.txt
# Expected: "ERROR SUMMARY: 0 errors from 0 contexts"
```

### 5.5 Traceability Management Pattern (workspace.py trace)

**Traceability Pattern**:

```bash
# Add traceability link (System → Software requirement)
python3 tools/workspace.py trace add \
  --from "SYS-REQ-001" \
  --to "REQ-FUNC-001" \
  --type "system-to-sw"

# Add traceability link (Software requirement → Architecture)
python3 tools/workspace.py trace add \
  --from "REQ-FUNC-001" \
  --to "MOD-CTRL" \
  --type "sw-to-arch"

# Add traceability link (Architecture → Design)
python3 tools/workspace.py trace add \
  --from "MOD-CTRL" \
  --to "control_process()" \
  --type "arch-to-design"

# Validate traceability completeness
python3 tools/workspace.py trace validate --sil 3
# Expected: 100% forward traceability, 100% backward traceability

# Generate traceability report
python3 tools/workspace.py trace report --report-type coverage
```

---

## 6. Tool Integration Examples

### 6.1 Complete IMP Agent Workflow (SIL 3)

```bash
#!/bin/bash
# IMP agent complete workflow: Implement and verify C module (SIL 3)

set -e

MODULE="door_controller"

echo "=== IMP Agent Workflow: $MODULE (SIL 3) ==="

# Step 1: Implement C module
echo "Step 1: Implementing C module"
# (Code written manually in editor)

# Step 2: Compile with SIL 3 flags
echo "Step 2: Compiling with SIL 3 flags"
gcc -std=c11 -Wall -Wextra -Werror -pedantic -O2 \
    -DSIL_LEVEL=3 -DMISRA_C_2012 \
    -fstack-protector-strong -D_FORTIFY_SOURCE=2 \
    -c src/control/$MODULE.c -o obj/$MODULE.o

# Step 3: Run static analysis (pre-commit check)
echo "Step 3: Running static analysis"
cppcheck --enable=all --error-exitcode=1 src/control/$MODULE.c

# Step 4: Check complexity
echo "Step 4: Checking complexity (SIL 3: CCN ≤ 10)"
lizard -l c -C 10 -w src/control/$MODULE.c

# Step 5: Build and run unit tests
echo "Step 5: Building and running unit tests with coverage"
make CFLAGS="--coverage" test-$MODULE

# Step 6: Verify coverage (SIL 3: 100%)
echo "Step 6: Verifying coverage"
lcov --capture --directory . --output-file coverage-$MODULE.info
STATEMENT_COV=$(lcov --summary coverage-$MODULE.info | grep "lines" | awk '{print $2}' | sed 's/%//')
if (( $(echo "$STATEMENT_COV >= 100" | bc -l) )); then
    echo "✅ Coverage: $STATEMENT_COV% (PASSED)"
else
    echo "❌ Coverage: $STATEMENT_COV% (FAILED, SIL 3 requires 100%)"
    exit 1
fi

# Step 7: Commit to version control
echo "Step 7: Committing to version control"
git add src/control/$MODULE.c tests/unit/test_$MODULE.c
git commit -m "Implement $MODULE module (SIL 3, IMP-001)"

echo "✅ IMP workflow complete for $MODULE"
```

### 6.2 Complete VER Agent Workflow (SIL 3)

```bash
#!/bin/bash
# VER agent complete workflow: Verify software (SIL 3)

set -e

echo "=== VER Agent Workflow (SIL 3) ==="

# Step 1: Run static analysis (Cppcheck)
echo "Step 1: Running Cppcheck"
cppcheck --enable=all --xml --xml-version=2 src/ 2> verification/cppcheck-report.xml
CPPCHECK_ERRORS=$(grep -c "<error " verification/cppcheck-report.xml || true)
echo "Cppcheck errors: $CPPCHECK_ERRORS"

# Step 2: Run static analysis (Clang - cross-check)
echo "Step 2: Running Clang Static Analyzer (cross-check)"
scan-build -o verification/clang-analysis make clean all
CLANG_BUGS=$(ls verification/clang-analysis/ 2>/dev/null | wc -l)
echo "Clang bugs: $CLANG_BUGS"

# Step 3: Run complexity analysis
echo "Step 3: Running complexity analysis (SIL 3: CCN ≤ 10)"
lizard -l c -C 10 -w src/ > verification/complexity-report.txt
COMPLEX_FUNCTIONS=$(grep "WARN" verification/complexity-report.txt | wc -l)
echo "Complex functions (CCN > 10): $COMPLEX_FUNCTIONS"

# Step 4: Verify coverage
echo "Step 4: Verifying coverage (SIL 3: Statement/Branch 100%)"
lcov --summary coverage.info > verification/coverage-summary.txt
STATEMENT_COV=$(grep "lines" verification/coverage-summary.txt | awk '{print $2}' | sed 's/%//')
BRANCH_COV=$(grep "branches" verification/coverage-summary.txt | awk '{print $2}' | sed 's/%//')
echo "Statement coverage: $STATEMENT_COV%"
echo "Branch coverage: $BRANCH_COV%"

# Step 5: Verify traceability
echo "Step 5: Verifying traceability"
python3 tools/workspace.py trace validate --sil 3 > verification/traceability-status.txt
TRACE_GAPS=$(grep "Gap" verification/traceability-status.txt | wc -l)
echo "Traceability gaps: $TRACE_GAPS"

# Step 6: Generate Verification Report
echo "Step 6: Generating Verification Report"
cat > verification/Verification-Report.md <<EOF
# Verification Report

**Project**: Train Door Control System
**SIL Level**: 3
**Date**: $(date +%Y-%m-%d)

## Static Analysis Results

### Cppcheck
- Errors: $CPPCHECK_ERRORS
- Status: $([ $CPPCHECK_ERRORS -eq 0 ] && echo "✅ PASSED" || echo "❌ FAILED")

### Clang Static Analyzer
- Bugs: $CLANG_BUGS
- Status: $([ $CLANG_BUGS -eq 0 ] && echo "✅ PASSED" || echo "❌ FAILED")

## Complexity Analysis

- Functions with CCN > 10: $COMPLEX_FUNCTIONS
- Status: $([ $COMPLEX_FUNCTIONS -eq 0 ] && echo "✅ PASSED" || echo "❌ FAILED")

## Coverage Analysis

- Statement Coverage: $STATEMENT_COV%
- Branch Coverage: $BRANCH_COV%
- Status: $([ $(echo "$STATEMENT_COV >= 100" | bc -l) -eq 1 ] && [ $(echo "$BRANCH_COV >= 100" | bc -l) -eq 1 ] && echo "✅ PASSED" || echo "❌ FAILED")

## Traceability

- Traceability Gaps: $TRACE_GAPS
- Status: $([ $TRACE_GAPS -eq 0 ] && echo "✅ PASSED" || echo "❌ FAILED")

## Verification Conclusion

$([ $CPPCHECK_ERRORS -eq 0 ] && [ $CLANG_BUGS -eq 0 ] && [ $COMPLEX_FUNCTIONS -eq 0 ] && [ $TRACE_GAPS -eq 0 ] && [ $(echo "$STATEMENT_COV >= 100" | bc -l) -eq 1 ] && echo "✅ Software VERIFIED for SIL 3" || echo "❌ Verification FAILED - issues must be resolved")
EOF

echo "✅ VER workflow complete"
cat verification/Verification-Report.md
```

---

## 7. Tool Troubleshooting

### 7.1 Common Tool Issues

**Issue 1: Tool version mismatch**

```bash
# Problem: Tool version doesn't match baseline
$ cppcheck --version
Cppcheck 2.14.0  # ERROR: Expected 2.13.0

# Solution: Install correct version or update baseline (requires CR for SIL 3-4)
sudo apt install cppcheck=2.13.0  # Install baselined version
# OR submit Change Request to update tool baseline
```

**Issue 2: Tool not qualified**

```bash
# Problem: Tool not in Tool-Baseline.md

# Solution: Qualify tool first (see Tool Qualification Workflow)
# 1. Classify tool (T1/T2/T3)
# 2. Validate/qualify tool
# 3. Create Tool Qualification Report
# 4. Add to Tool-Baseline.md
```

**Issue 3: Coverage not reaching 100% (SIL 3-4)**

```bash
# Problem: Coverage is 95%, SIL 3 requires 100%

# Solution: Identify uncovered code
lcov --list coverage.info | grep "0.0%"

# Add tests to cover missing lines/branches
# Rerun tests and verify 100% coverage
```

**Issue 4: Static analyzer false positives**

```bash
# Problem: Cppcheck reports false positive

# Solution: Suppress false positive (document reason)
# In code:
// cppcheck-suppress nullPointer  // False positive: ptr checked by assert
*ptr = value;

# In Verification Report: Document all suppressions
```

---

## 8. References

### 8.1 Tool Documentation

- **TOOLS.md**: Comprehensive tool catalog (904 lines)
- **Tool-Baseline.md**: Baselined tool versions
- **Tool Qualification Reports**: `docs/tool-qualification/*-Qualification-Report.md`
- **Tool Validation Reports**: `docs/tool-qualification/*-Validation-Report.md`

### 8.2 Workflow References

- **Tool Qualification Workflow**: `.opencode/skills/en50128-tools/workflows/tool-qualification-workflow.md`
- **Tool Selection Workflow**: This document

### 8.3 EN 50128 References

- **Section 6.7**: Software tools and their validation
- **Table A.4**: Design and implementation techniques (tool requirements)
- **Table A.19**: Static analysis techniques
- **Table A.21**: Test coverage requirements

---

**END OF WORKFLOW**
