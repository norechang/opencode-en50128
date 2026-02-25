# EN 50128 Tool Catalog

**Purpose**: Comprehensive catalog of all tools used in EN 50128 railway software development, with usage information for agents.

**Target Audience**: Development agents (REQ, DES, IMP, TST, VER, VAL, INT, SAF, QUA, CM, COD, PM)

**Last Updated**: 2026-02-25

---

## Tool Classification

Per EN 50128 Section 6.7, tools are classified by Tool Confidence Level (TCL):

| TCL | Description | Qualification Required | EN 50128 Reference |
|-----|-------------|------------------------|-------------------|
| **T1** | No tool error affects output integrity | No qualification | Section 6.7.4.2 |
| **T2** | Tool errors may go undetected | Validation required | Section 6.7.4.3 |
| **T3** | Tool output not verified | Full qualification | Section 6.7.4.4 |

---

## Quick Reference

### Tool Selection Decision Tree

```
START: Need to perform a task
  |
  ├─ Task involves C compilation/linking?
  │   └─> Use: gcc, make (T3 - requires qualification)
  |
  ├─ Task involves static analysis?
  │   └─> Use: cppcheck, clang, lizard (T2 - validation required)
  |
  ├─ Task involves coverage analysis?
  │   └─> Use: gcov, lcov (T2 - validation required)
  |
  ├─ Task involves MC/DC analysis?
  │   └─> Use: mcdc_analyzer.py (T1 - output verified)
  |
  ├─ Task involves memory analysis?
  │   └─> Use: valgrind (T1 - output verified)
  |
  └─ Task involves documentation/reports?
      └─> Use: Custom Python scripts (T1 - output verified)
```

---

## MANDATORY Tools (SIL 3)

These tools are **REQUIRED** for EN 50128 SIL 3 compliance.

### 1. GCC (GNU Compiler Collection)

**Category**: Compiler (T3)  
**Status**: ✅ Installed  
**Version**: 13.3.0  
**EN 50128 Reference**: Section 7.4 (Implementation), Table A.4  
**Mandatory For**: All SIL levels  
**Installation**: `sudo apt-get install build-essential`

**Usage**:
```bash
# Compile C source with SIL 3 flags
gcc -std=c11 -Wall -Wextra -Werror -pedantic -O2 \
    -DSIL_LEVEL=3 -DMISRA_C_2012 \
    -fstack-protector-strong -D_FORTIFY_SOURCE=2 \
    -fno-common \
    -fno-builtin-malloc -fno-builtin-calloc \
    -o output file.c
```

**Agent Usage**:
- **IMP**: Compile C implementations
- **TST**: Build test executables
- **INT**: Build integrated components
- **VER**: Compiler warnings analysis

**TCL Classification**: T3 (Full qualification required)

**Qualification Requirements**:
- Compiler validation suite (e.g., Plum Hall Validation Suite)
- Documented in: `docs/tool-qualification/gcc-qualification.md`
- Evidence: Supplier qualification + project-specific validation

---

### 2. GNU Make

**Category**: Build System (T2)  
**Status**: ✅ Installed  
**Version**: 4.3  
**EN 50128 Reference**: Section 6.6 (Configuration Management)  
**Mandatory For**: All SIL levels  
**Installation**: Included with `build-essential`

**Usage**:
```bash
# Build project
make all

# Run tests
make test

# Generate coverage
make coverage

# Run static analysis
make verify
```

**Agent Usage**:
- **IMP**: Build automation
- **TST**: Test execution
- **VER**: Verification builds
- **INT**: Integration builds

**TCL Classification**: T2 (Validation required)

---

### 3. gcov (Coverage Tool)

**Category**: Coverage Analysis (T2)  
**Status**: ✅ Installed  
**Version**: 13.3.0 (part of GCC)  
**EN 50128 Reference**: Table A.21 (Test Coverage for Code - **MANDATORY SIL 3-4**)  
**Mandatory For**: SIL 3-4 (100% stmt/branch/condition)  
**Installation**: Included with `gcc`

**Usage**:
```bash
# Compile with coverage instrumentation
gcc -fprofile-arcs -ftest-coverage -o test test.c

# Run test
./test

# Generate coverage report
gcov test.c

# View results
cat test.c.gcov
```

**Agent Usage**:
- **TST**: Measure test coverage
- **VER**: Verify coverage requirements (SIL 3: 100% stmt/branch/condition)
- **VAL**: Coverage evidence collection

**TCL Classification**: T2 (Validation required)

**Coverage Requirements by SIL**:
- **SIL 0-1**: Statement (HR), Branch (HR)
- **SIL 2**: Statement (HR), Branch (**M**)
- **SIL 3-4**: Statement (**M**), Branch (**M**), Condition/MC/DC (**M**)

---

### 4. lcov (Coverage Report Generator)

**Category**: Coverage Reporting (T2)  
**Status**: ✅ Installed  
**Version**: 1.x  
**EN 50128 Reference**: Table A.21 (Test Coverage for Code)  
**Mandatory For**: SIL 3-4 (HTML reports required)  
**Installation**: `sudo apt-get install lcov`

**Usage**:
```bash
# Capture coverage data
lcov --capture --directory . --output-file coverage.info

# Generate HTML report
genhtml coverage.info --output-directory coverage_html

# View report
xdg-open coverage_html/index.html
```

**Agent Usage**:
- **TST**: Generate coverage reports
- **VER**: Coverage evidence documentation
- **VAL**: Present coverage to stakeholders
- **QUA**: Quality gate enforcement (100% coverage check)

**TCL Classification**: T2 (Validation required)

---

### 5. Cppcheck (Static Analyzer)

**Category**: Static Analysis (T2)  
**Status**: ✅ Installed  
**Version**: 2.13.0  
**EN 50128 Reference**: Table A.19 (Static Analysis - **MANDATORY SIL 3-4**)  
**Mandatory For**: SIL 3-4  
**Installation**: `sudo apt-get install cppcheck`

**Usage**:
```bash
# Basic check
cppcheck src/

# With MISRA addon
cppcheck --enable=all --addon=misra.py src/

# Generate XML report
cppcheck --enable=all --xml --xml-version=2 src/ 2> report.xml
```

**Agent Usage**:
- **VER**: Static analysis (MANDATORY SIL 3)
- **IMP**: Pre-commit checks
- **QUA**: Code quality gate
- **DES**: Design verification

**TCL Classification**: T2 (Validation required)

**Capabilities**:
- Null pointer dereference detection
- Buffer overflow detection
- Memory leaks
- Unused variables/functions
- MISRA C:2012 compliance (with addon)

---

### 6. Clang Static Analyzer

**Category**: Static Analysis (T2)  
**Status**: ✅ Installed  
**Version**: 18.x  
**EN 50128 Reference**: Table A.19 (Static Analysis - **MANDATORY SIL 3-4**)  
**Mandatory For**: SIL 3-4  
**Installation**: `sudo apt-get install clang clang-tools`

**Usage**:
```bash
# Analyze single file
clang --analyze -Xanalyzer -analyzer-output=text file.c

# Scan entire project
scan-build make

# HTML report
scan-build -o analysis_results make
```

**Agent Usage**:
- **VER**: Static analysis (MANDATORY SIL 3) - secondary tool to Cppcheck
- **IMP**: Code quality checks
- **QUA**: Independent verification

**TCL Classification**: T2 (Validation required)

**Capabilities**:
- Dead code detection
- Use-after-free
- Null pointer dereference
- Memory leaks
- API misuse

---

### 7. Lizard (Complexity Analyzer)

**Category**: Complexity Analysis (T1)  
**Status**: ✅ Installed (via pip)  
**Version**: 1.17+  
**EN 50128 Reference**: Table A.19 (Static Analysis - CCN measurement)  
**Mandatory For**: SIL 3-4 (CCN ≤ 10 MANDATORY)  
**Installation**: `pip install lizard`

**Usage**:
```bash
# Analyze all C files
lizard src/ --CCN 10

# Generate HTML report
lizard src/ --CCN 10 --html > complexity_report.html

# Fail if CCN > 10
lizard src/ --CCN 10 --Threshold ccn=10
```

**Agent Usage**:
- **VER**: Cyclomatic complexity verification (MANDATORY SIL 3)
- **DES**: Design complexity validation (at design phase)
- **IMP**: Implementation complexity check
- **QUA**: Quality gate (CCN ≤ 10 for SIL 3)

**TCL Classification**: T1 (No qualification - output verified by inspection)

**Complexity Limits by SIL**:
- **SIL 0-1**: CCN ≤ 20 (recommended)
- **SIL 2**: CCN ≤ 15 (highly recommended)
- **SIL 3-4**: CCN ≤ 10 (**MANDATORY**)

---

### 8. Git (Version Control)

**Category**: Configuration Management (T2)  
**Status**: ✅ Installed  
**Version**: 2.x  
**EN 50128 Reference**: Table A.9 (Software Configuration Management - **MANDATORY all SILs**)  
**Mandatory For**: **ALL SIL levels (0, 1, 2, 3, 4)**  
**Installation**: `sudo apt-get install git`

**Usage**:
```bash
# Initialize repository
git init

# Create baseline
git tag -a Baseline-1 -m "Phase 1 complete"

# Track changes
git log --oneline

# Branch for parallel development
git checkout -b feature/safety-module
```

**Agent Usage**:
- **CM**: Configuration management (MANDATORY all SILs)
- **COD**: Baseline enforcement at phase gates
- **PM**: Change control board decisions
- **All agents**: Version tracking

**TCL Classification**: T2 (Validation required)

**Configuration Management Requirements (EN 50128 Section 6.6)**:
- Version control for ALL configuration items
- Baseline management at phase gates
- Change control process (Change Control Board)
- Traceability (MANDATORY SIL 3-4)

---

## HIGHLY RECOMMENDED Tools (SIL 3)

### 9. Valgrind (Memory Analyzer)

**Category**: Dynamic Analysis (T1)  
**Status**: ✅ Installed  
**Version**: 3.x  
**EN 50128 Reference**: Table A.13 (Dynamic Analysis and Testing - **MANDATORY SIL 3-4**)  
**Mandatory For**: Highly Recommended SIL 3-4  
**Installation**: `sudo apt-get install valgrind`

**Usage**:
```bash
# Memory leak detection
valgrind --leak-check=full --show-leak-kinds=all ./test

# Invalid memory access
valgrind --track-origins=yes ./test

# Generate XML report
valgrind --xml=yes --xml-file=valgrind_report.xml ./test
```

**Agent Usage**:
- **TST**: Memory leak detection during testing
- **VER**: Dynamic analysis verification
- **INT**: Integration testing memory validation
- **QUA**: Quality gate (zero memory errors)

**TCL Classification**: T1 (No qualification - output verified by test results)

**Note**: Not available on macOS (use Xcode Instruments instead)

---

### 10. PC-lint Plus (MISRA C Checker)

**Category**: MISRA C Compliance (T2)  
**Status**: ⚠️ Commercial (not installed by default)  
**Version**: 2.0+  
**EN 50128 Reference**: Table A.19 (Static Analysis - HR SIL 3-4)  
**Mandatory For**: Highly Recommended SIL 3-4  
**Installation**: Commercial license required  
**URL**: https://pclintplus.com/

**Usage**:
```bash
# Check MISRA C compliance
pclint64 -i config/pclint-config.lnt src/*.c

# Generate report
pclint64 -i config/pclint-config.lnt -html > misra_report.html src/*.c
```

**Agent Usage**:
- **VER**: MISRA C:2012 compliance verification (HR SIL 3)
- **IMP**: Pre-commit MISRA checks
- **QUA**: Zero mandatory MISRA violations (SIL 2+)

**TCL Classification**: T2 (Validation required)

**Alternative**: Cppcheck with MISRA addon (free, but less comprehensive)

---

## RECOMMENDED Tools

### 11. Splint (Static Checker)

**Category**: Static Analysis (T1)  
**Status**: ⚠️ Optional  
**Version**: 3.1.x  
**EN 50128 Reference**: Table A.19 (Static Analysis)  
**Mandatory For**: Recommended SIL 3  
**Installation**: `sudo apt-get install splint`

**Usage**:
```bash
# Check for common errors
splint +posixlib src/*.c

# Strict checking
splint +checks src/*.c
```

**Agent Usage**:
- **VER**: Additional static analysis
- **IMP**: Buffer overflow detection

**TCL Classification**: T1 (No qualification - output verified)

---

### 12. Doxygen (Documentation Generator)

**Category**: Documentation (T1)  
**Status**: ⚠️ Optional  
**Version**: 1.x  
**EN 50128 Reference**: Section 7.1 (Documentation)  
**Mandatory For**: Recommended  
**Installation**: `sudo apt-get install doxygen graphviz`

**Usage**:
```bash
# Generate documentation from code
doxygen Doxyfile

# View HTML docs
xdg-open docs/html/index.html
```

**Agent Usage**:
- **IMP**: API documentation generation
- **DES**: Design documentation
- **COD**: Deliverable generation

**TCL Classification**: T1 (No qualification - documentation verified)

---

## CUSTOM EN 50128 Tools (Python)

### 13. MC/DC Analyzer (mcdc_analyzer.py)

**Category**: Coverage Analysis (T1)  
**Status**: ✅ Available  
**Version**: 1.0  
**EN 50128 Reference**: Table A.21 (MC/DC coverage - **MANDATORY SIL 3-4**)  
**Mandatory For**: SIL 3-4  
**Location**: `tools/mcdc/mcdc_analyzer.py`

**Usage**:
```bash
# Analyze C source for MC/DC
python3 tools/mcdc/mcdc_analyzer.py analyze \
  -I examples/train_door_control2/src \
  --sil 3 --project train_door_control2 \
  --format all \
  -o docs/reports/MC-DC-Analysis.md \
  src/**/*.c

# Generate coverage evidence
python3 tools/mcdc/mcdc_analyzer.py report \
  --vectors docs/reports/MC-DC-Vectors.json \
  --results test/results/test-results.json \
  --sil 3 --project train_door_control2 \
  -o docs/reports/MC-DC-Coverage-Evidence.md
```

**Agent Usage**:
- **TST**: MC/DC test case generation (SIL 3 MANDATORY)
- **VER**: MC/DC coverage verification
- **VAL**: Evidence documentation

**TCL Classification**: T1 (Output verified by manual inspection)

**Capabilities**:
- Static extraction of boolean expressions from C source
- Truth table generation
- Minimal MC/DC test vector generation
- Coverage tracking against test results
- EN 50128 evidence document generation

---

### 14. Workspace Manager (workspace.py)

**Category**: Project Management (T1)  
**Status**: ✅ Available  
**Version**: 1.0  
**EN 50128 Reference**: Platform Extension  
**Location**: `tools/workspace.py`

**Usage**:
```bash
# List workspaces
python3 tools/workspace.py list

# Switch workspace
python3 tools/workspace.py switch train_door_control2

# Create new workspace
python3 tools/workspace.py create my_project --sil 3

# Check status
python3 tools/workspace.py status
```

**Agent Usage**:
- **COD**: Workspace lifecycle management
- **PM**: Multi-project coordination
- **All agents**: Workspace context awareness

**TCL Classification**: T1 (No safety impact)

---

### 15. EN50128 Help System (enhelp.py)

**Category**: Documentation (T1)  
**Status**: ✅ Available  
**Version**: 1.0  
**EN 50128 Reference**: Platform Extension  
**Location**: `tools/enhelp.py`

**Usage**:
```bash
# List all commands
python3 tools/enhelp.py

# Get help for specific command
python3 tools/enhelp.py req

# Search by topic
python3 tools/enhelp.py --search "static analysis"
```

**Agent Usage**:
- **All agents**: Command reference lookup
- **COD**: Training and onboarding

**TCL Classification**: T1 (No safety impact)

---

### 16. MISRA C Checker Wrapper (check_misra.py)

**Category**: Static Analysis (T2)  
**Status**: ✅ Available  
**Version**: 1.0  
**EN 50128 Reference**: Table A.19  
**Location**: `tools/static-analysis/check_misra.py`

**Usage**:
```bash
# Run MISRA C checks (wraps Cppcheck)
python3 tools/static-analysis/check_misra.py --src src/ --project train_door_control2
```

**Agent Usage**:
- **VER**: MISRA C compliance verification wrapper
- **IMP**: Pre-commit MISRA checks
- **QUA**: MISRA compliance reporting

**TCL Classification**: T2 (Wraps Cppcheck - validation required)

---

## Tool Selection Guidelines for Agents

### Before Using a Tool, Agents MUST:

1. **Check Tool Availability**:
   ```bash
   # Check if tool is installed
   which <tool_name>
   
   # Or consult TOOLS.md (this file)
   ```

2. **Verify Tool Classification (TCL)**:
   - T1: Use directly, verify output
   - T2: Use with validation, document results
   - T3: Use only with full qualification evidence

3. **Check SIL Level Requirements**:
   - MANDATORY vs Highly Recommended vs Recommended
   - Refer to EN 50128 Table references

4. **Select Most Effective Tool**:
   - Prefer MANDATORY tools over alternatives
   - Prefer specialized tools over general-purpose
   - Consider tool output format (XML/JSON preferred for automation)

### Tool Selection Examples

**Example 1: Static Analysis (SIL 3)**
```
Task: Perform static analysis on C code
Agent: VER (Verifier)
SIL Level: 3

Decision Tree:
1. Check MANDATORY tools for SIL 3 (Table A.19)
   - Cppcheck: ✅ MANDATORY, installed
   - Clang: ✅ MANDATORY, installed
2. Select both (use multiple tools for thoroughness)
3. Generate reports from both
4. Document results in Verification Report

Command:
  cppcheck --enable=all --xml src/ 2> cppcheck.xml
  scan-build -o analysis_results make
```

**Example 2: Complexity Check (SIL 3)**
```
Task: Verify cyclomatic complexity ≤ 10
Agent: VER (Verifier)
SIL Level: 3

Decision Tree:
1. Check MANDATORY complexity tool
   - Lizard: ✅ Available (pip)
2. Run with threshold CCN=10
3. Fail build if any function exceeds CCN=10

Command:
  lizard src/ --CCN 10 --Threshold ccn=10
```

**Example 3: Coverage Analysis (SIL 3)**
```
Task: Measure test coverage (100% required)
Agent: TST (Tester)
SIL Level: 3

Decision Tree:
1. Check MANDATORY coverage tools (Table A.21)
   - gcov: ✅ MANDATORY, installed
   - lcov: ✅ MANDATORY, installed
2. Compile with coverage flags
3. Run tests
4. Generate HTML report with lcov

Command:
  gcc -fprofile-arcs -ftest-coverage test.c
  ./a.out
  lcov --capture --directory . --output-file coverage.info
  genhtml coverage.info --output-directory coverage_html
```

---

## Tool Qualification Status

Per EN 50128 Section 6.7, tool qualification requirements:

| Tool | TCL | Status | Evidence Location |
|------|-----|--------|-------------------|
| gcc | T3 | ⚠️ Requires qualification | `docs/tool-qualification/gcc-qualification.md` |
| make | T2 | ⚠️ Requires validation | `docs/tool-qualification/make-validation.md` |
| gcov | T2 | ⚠️ Requires validation | `docs/tool-qualification/gcov-validation.md` |
| lcov | T2 | ⚠️ Requires validation | `docs/tool-qualification/lcov-validation.md` |
| cppcheck | T2 | ⚠️ Requires validation | `docs/tool-qualification/cppcheck-validation.md` |
| clang | T2 | ⚠️ Requires validation | `docs/tool-qualification/clang-validation.md` |
| lizard | T1 | ✅ No qualification | Output verified |
| valgrind | T1 | ✅ No qualification | Output verified |
| git | T2 | ⚠️ Requires validation | `docs/tool-qualification/git-validation.md` |
| PC-lint | T2 | ⚠️ Requires validation | Supplier evidence |
| Custom Python | T1 | ✅ No qualification | Output verified |

**Note**: Tool qualification should be completed during Phase 1 (Planning) or early Phase 5 (Implementation).

---

## Installation Instructions

### Quick Start (New Users)

```bash
# Clone repository
git clone https://github.com/your-org/EN50128.git
cd EN50128

# Install system tools (requires sudo)
./install_tools.sh

# Install Python tools
./install_python.sh

# Verify installation
./install_tools.sh --check
source venv/bin/activate
./install_python.sh --check
```

### Manual Installation

See installation scripts:
- `install_tools.sh` - System tools (gcc, lcov, cppcheck, etc.)
- `install_python.sh` - Python virtual environment and packages

---

## Tool Updates and Maintenance

### Updating Tools

```bash
# Update system tools
sudo apt-get update && sudo apt-get upgrade

# Update Python packages
source venv/bin/activate
pip install --upgrade -r requirements.txt
```

### Version Pinning (Production Projects)

For production EN 50128 projects, **pin exact versions** for traceability:

```bash
# Generate exact version requirements
pip freeze > requirements-pinned.txt

# Document tool versions in Software Configuration Management Plan (SCMP)
```

---

## Agent Tool Usage Workflow

### Standard Tool Usage Pattern

```
1. READ TOOLS.md (this file)
   - Identify task requirements (static analysis, coverage, etc.)
   - Check SIL level constraints (MANDATORY/HR/R)

2. CHECK TOOL AVAILABILITY
   - Verify tool is installed: which <tool>
   - Check TCL classification

3. SELECT MOST EFFECTIVE TOOL
   - Prefer MANDATORY tools
   - Use multiple tools for thoroughness (SIL 3+)

4. EXECUTE TOOL
   - Use appropriate flags for SIL level
   - Generate machine-readable output (XML/JSON)

5. VERIFY OUTPUT
   - T1: Inspect output
   - T2: Cross-reference with other tools
   - T3: Check qualification evidence

6. DOCUMENT RESULTS
   - Include in agent deliverable (Verification Report, etc.)
   - Reference tool version and configuration
```

---

## References

- **EN 50128:2011**: Railway Applications - Software for Railway Control and Protection Systems
  - Section 6.7: Software Tools and Programming Languages
  - Table A.x: Technique/Measure tables
- **AGENTS.md**: Agent role definitions and responsibilities
- **LIFECYCLE.md**: EN 50128 V-Model lifecycle phases
- **Project SQAP**: Tool qualification requirements (project-specific)

---

## Changelog

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2026-02-25 | COD | Initial tool catalog creation |

---

**END OF TOOL CATALOG**
