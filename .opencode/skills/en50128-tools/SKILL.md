# EN 50128 Tools Skill

**EN 50128 Reference**: Section 6.7 - Software tools and their validation  
**Purpose**: Tool qualification, selection, and usage for EN 50128-compliant railway software development  
**Target Roles**: All agents (REQ, DES, IMP, TST, VER, INT, VAL, SAF, QUA, CM, PM, COD)

---

## Overview

This skill provides comprehensive guidance for qualifying, selecting, and using software tools in EN 50128-compliant projects. Tool qualification is **MANDATORY** for SIL 1-4 projects (EN 50128 Section 6.7) to ensure that tools do not introduce undetected errors that could compromise software safety.

###

 Key Capabilities

- **Tool Classification**: Classify tools by Tool Confidence Level (T1/T2/T3) per EN 50128 Section 6.7.4
- **Tool Qualification**: Full qualification process for T3 tools (compilers, linkers)
- **Tool Validation**: Validation process for T2 tools (static analyzers, coverage tools)
- **Tool Selection**: Select appropriate tools for each agent role and SIL level
- **Tool Usage**: Use tools correctly according to EN 50128 requirements and Tool Qualification Reports
- **Tool Management**: Maintain tool baselines, version control, and change control

### EN 50128 Requirements Summary

| SIL | Tool Classification | T2 Validation | T3 Qualification | Report Required |
|-----|---------------------|---------------|------------------|-----------------|
| **0** | Recommended | Recommended | Recommended | No |
| **1** | **MANDATORY** | **MANDATORY** | **MANDATORY** | Highly Recommended |
| **2** | **MANDATORY** | **MANDATORY** | **MANDATORY** | Highly Recommended |
| **3** | **MANDATORY** | **MANDATORY** | **MANDATORY** | **MANDATORY** |
| **4** | **MANDATORY** | **MANDATORY** | **MANDATORY** | **MANDATORY** |

---

## Workflows

This skill provides 2 comprehensive workflows covering tool qualification and usage:

### 1. Tool Qualification Workflow

**File**: `.opencode/skills/en50128-tools/workflows/tool-qualification-workflow.md`  
**Size**: ~1,013 lines (~40 pages)  
**Purpose**: Qualify software tools for use in EN 50128 projects

**EN 50128 Coverage**:
- Section 6.7: Software tools and their validation
- Section 6.7.4: Tool classification (T1/T2/T3)
- Section 6.7.4.2: T1 tools (no qualification required)
- Section 6.7.4.3: T2 tools (validation required)
- Section 6.7.4.4: T3 tools (full qualification required)
- Section 6.7.4.5: Tool qualification process

**Key Content**:
1. **Tool Confidence Levels (T1/T2/T3)**: Detailed classification criteria with examples
2. **Tool Qualification Process**: 6-phase process (identification, classification, qualification, report, baseline, management)
3. **T1 Tools**: No qualification required (editors, reporting tools, Valgrind, Git)
4. **T2 Tools**: Validation required (Cppcheck, Clang, Lizard, gcov/lcov, Unity)
   - Validation test suite design
   - Validation test execution
   - Validation report creation
5. **T3 Tools**: Full qualification required (GCC, linker, Make)
   - Supplier qualification evidence
   - Project-specific validation
   - Assembly code review
   - Comparison testing
6. **Tool Qualification Reports**: Complete templates for T2 and T3 tools
7. **Tool Automation**: Automated validation test runners, CI/CD integration
8. **Complete Examples**:
   - Cppcheck validation (T2) for SIL 3 project (step-by-step)
   - GCC qualification (T3) for SIL 3 project (step-by-step)

**When to Use**:
- **Phase 1: Planning** - Qualify all tools before use (MANDATORY SIL 1-4)
- **Tool Updates** - Re-qualify tools after version updates (MANDATORY SIL 3-4)
- **New Tools** - Qualify any new tool before introduction to project

**Key Outputs**:
- Tool Classification justifications
- Tool Validation Reports (T2 tools, MANDATORY SIL 3-4)
- Tool Qualification Reports (T3 tools, MANDATORY SIL 1-4)
- Tool Baseline (tool versions, checksums)
- Validation test suites (automated)

### 2. Tool Selection and Usage Workflow

**File**: `.opencode/skills/en50128-tools/workflows/tool-selection-usage-workflow.md`  
**Size**: ~600 lines (~24 pages)  
**Purpose**: Select and use appropriate tools for each agent role and SIL level

**EN 50128 Coverage**:
- Section 6.7: Software tools and their validation (usage requirements)
- Table A.4: Design and implementation techniques (tool requirements)
- Table A.19: Static analysis techniques
- Table A.21: Test coverage requirements (coverage tool usage)

**Key Content**:
1. **Tool Selection Process**: Decision tree for selecting tools by task category
2. **Tool Selection by Category**:
   - Development tools (compilers, build systems)
   - Verification tools (static analyzers, complexity analyzers)
   - Testing tools (test frameworks, coverage tools)
   - Analysis tools (memory analyzers)
   - Management tools (version control, workflow management)
   - Custom EN50128 tools (Python scripts)
3. **Tool Selection by Agent Role**: Complete tool lists for each agent (REQ, DES, IMP, TST, VER, INT, VAL, QUA, CM, COD)
4. **SIL-Specific Tool Requirements**:
   - SIL 0: Minimal tool requirements
   - SIL 1-2: Baselined tools, validation required
   - SIL 3-4: Locked tool versions, multiple tools for cross-checking
5. **Tool Usage Patterns**: Standard patterns for compilation, static analysis, coverage, memory analysis, traceability
6. **Tool Integration Examples**: Complete agent workflows (IMP, VER) with all tools integrated
7. **Tool Troubleshooting**: Common tool issues and solutions

**When to Use**:
- **Phase 1: Planning** - Select tools for project based on SIL level
- **All Phases** - Reference for correct tool usage in agent workflows
- **Tool Issues** - Troubleshoot tool problems

**Key Outputs**:
- Tool selection for project (by agent role)
- Tool usage examples for all agents
- SIL-specific tool configurations
- Tool integration scripts

---

## Tool Integration

### Tool Catalog Reference

All tools are documented in the project-level **TOOLS.md** file (904 lines):

```bash
# View tool catalog
cat TOOLS.md

# Tool catalog structure:
# - Tool Classification (T1/T2/T3 definitions)
# - MANDATORY Tools (SIL 3): GCC, Make, Cppcheck, Clang, Lizard, gcov/lcov
# - HIGHLY RECOMMENDED Tools (SIL 3): Valgrind, PC-lint Plus
# - RECOMMENDED Tools: Additional tools
# - CUSTOM EN50128 Tools: workspace.py (wf/trace), validation scripts
# - Tool Selection Guidelines for Agents
# - Tool Qualification Status
```

### workspace.py Integration

Tools are managed through workspace.py for workflow and traceability:

**1. Tool Qualification Document Workflow** (`workspace.py wf`):

```bash
# Submit Tool Qualification Report for review
python3 tools/workspace.py wf submit \
  --document "docs/tool-qualification/GCC-Qualification-Report.md" \
  --type "TOOL-QUALIFICATION" \
  --version "1.0" \
  --approver "QUA" \
  --sil 3

# QUA reviews and approves
python3 tools/workspace.py wf approve \
  --workflow-id "WF-2026-040" \
  --approver "QUA" \
  --decision "APPROVE"

# VER reviews and approves
python3 tools/workspace.py wf approve \
  --workflow-id "WF-2026-040" \
  --approver "VER" \
  --decision "APPROVE"

# PM final approval
python3 tools/workspace.py wf approve \
  --workflow-id "WF-2026-040" \
  --approver "PM" \
  --decision "APPROVE"

# Check workflow status
python3 tools/workspace.py wf status --workflow-id "WF-2026-040"
```

**2. Tool Baseline Management** (`workspace.py wf baseline`):

```bash
# Baseline tool versions
python3 tools/workspace.py wf baseline \
  --name "Tool-Baseline-v1.0" \
  --documents "docs/tool-qualification/Tool-Baseline.md" \
  --sil 3

# Record baseline in Git
git tag -a tool-baseline-v1.0 -m "Tool baseline version 1.0 (SIL 3)"
```

**3. Tool Usage in Traceability** (`workspace.py trace`):

Tools are referenced in traceability links:

```bash
# Example: Traceability link includes tool used for verification
# (Traceability links document which tools verified requirements)
python3 tools/workspace.py trace add \
  --from "REQ-FUNC-001" \
  --to "TEST-FUNC-001" \
  --type "sw-to-test"

# Traceability report includes tool information
python3 tools/workspace.py trace report --report-type coverage
```

### Automation Scripts

The tools skill includes automation scripts for tool validation:

**1. Automated Tool Validation Runner** (`tools/tool-validation/run-all-validations.sh`):

```bash
#!/bin/bash
# Run validation tests for all T2 tools

./run-all-validations.sh
# Validates: Cppcheck, Lizard, gcov/lcov, Unity
# Outputs: Validation results for each tool
```

**2. Tool Version Check** (`tools/tool-validation/check-tool-versions.sh`):

```bash
#!/bin/bash
# Verify tool versions match baseline

./check-tool-versions.sh
# Checks: GCC, Cppcheck, Lizard versions
# Fails if versions don't match baseline (SIL 3-4)
```

**3. CI/CD Tool Validation** (`.github/workflows/tool-validation.yml`):

```yaml
name: Tool Validation

on:
  push:
  schedule:
    - cron: '0 0 * * 0'  # Weekly

jobs:
  validate-tools:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Install tools
        run: sudo apt-get install -y gcc cppcheck lcov
      - name: Run tool validation suite
        run: ./tools/tool-validation/run-all-validations.sh
```

---

## Templates

### Tool Qualification Report Template

**File**: `deliverables/tools/Tool-Qualification-Report-template.md`  
**Purpose**: Document tool qualification evidence for T3 tools (compilers, linkers)  
**Mandatory For**: SIL 1-4 (T3 tools)

**Template Sections**:
1. Document Control
2. Tool Identification (name, version, vendor, purpose)
3. Tool Classification (T1/T2/T3 justification)
4. Tool Specification (functionality, usage, constraints)
5. Qualification Evidence (supplier qualification, certifications)
6. Project-Specific Validation (validation tests, results)
7. Tool Qualification Conclusion (qualified/not qualified)
8. Tool Configuration Management (version control, change control)
9. Approvals (QUA, VER, PM)
10. Appendices (validation results, supplier docs, configurations)

**Usage Example**:

```bash
# Create GCC Qualification Report from template
cp deliverables/tools/Tool-Qualification-Report-template.md \
   docs/tool-qualification/GCC-Qualification-Report.md

# Fill in template sections
vim docs/tool-qualification/GCC-Qualification-Report.md

# Submit for review
python3 tools/workspace.py wf submit \
  --document "docs/tool-qualification/GCC-Qualification-Report.md" \
  --type "TOOL-QUALIFICATION" \
  --version "1.0" \
  --approver "QUA" \
  --sil 3
```

### Tool Validation Report Template

**File**: `deliverables/tools/Tool-Validation-Report-template.md`  
**Purpose**: Document tool validation evidence for T2 tools (static analyzers, coverage tools)  
**Mandatory For**: SIL 3-4 (T2 tools)

**Template Sections**:
1. Document Control
2. Tool Identification (name, version, classification)
3. Tool Classification (T2 justification)
4. Validation Test Suite (tests, expected results)
5. Validation Results (test execution, results, analysis)
6. Validation Conclusion (validated/not validated)
7. Tool Usage Constraints (usage flags, limitations)
8. Approvals (QUA, VER, PM)

**Usage Example**:

```bash
# Create Cppcheck Validation Report from template
cp deliverables/tools/Tool-Validation-Report-template.md \
   docs/tool-qualification/Cppcheck-Validation-Report.md

# Fill in template sections
vim docs/tool-qualification/Cppcheck-Validation-Report.md

# Run validation tests
cd tests/tool-validation/cppcheck-validation
./run-validation.sh > validation-results.txt

# Include validation results in report
# Submit for review
python3 tools/workspace.py wf submit \
  --document "docs/tool-qualification/Cppcheck-Validation-Report.md" \
  --type "TOOL-VALIDATION" \
  --version "1.0" \
  --approver "QUA" \
  --sil 3
```

---

## EN 50128 Coverage Summary

### Standards Covered

| EN 50128 Section/Table | Title | Workflow Coverage |
|------------------------|-------|-------------------|
| **Section 6.7** | Software tools and their validation | Workflow 1 (complete) |
| **Section 6.7.4** | Tool classification (T1/T2/T3) | Workflow 1 (complete) |
| **Section 6.7.4.2** | T1 tools (no qualification) | Workflow 1 Section 5 |
| **Section 6.7.4.3** | T2 tools (validation required) | Workflow 1 Section 6 |
| **Section 6.7.4.4** | T3 tools (full qualification) | Workflow 1 Section 7 |
| **Section 6.7.4.5** | Tool qualification process | Workflow 1 Section 4 |
| **Table A.4** | Design/implementation techniques (tools) | Workflow 2 Section 4 |
| **Table A.19** | Static analysis techniques | Workflow 2 Section 5.2 |
| **Table A.21** | Test coverage requirements | Workflow 2 Section 5.3 |

### Lifecycle Phase Coverage

| Phase | Tool Activities | Workflow Coverage |
|-------|-----------------|-------------------|
| **Phase 1: Planning** | Tool qualification, tool selection, tool baseline | Workflow 1 (qualification), Workflow 2 (selection) |
| **Phase 2: Requirements** | Tool usage (REQ agent) | Workflow 2 Section 3.1 |
| **Phase 3: Design** | Tool usage (DES agent) | Workflow 2 Section 3.2 |
| **Phase 4: Implementation** | Tool usage (IMP agent) | Workflow 2 Section 3.3 |
| **Phase 5: Testing** | Tool usage (TST agent) | Workflow 2 Section 3.4 |
| **Phase 6: Integration** | Tool usage (INT agent) | Workflow 2 Section 3.6 |
| **Phase 7: Validation** | Tool usage (VAL agent) | Workflow 2 Section 3.7 |
| **All Phases** | Tool verification (VER agent), tool quality (QUA agent) | Workflow 2 Sections 3.5, 3.8 |

### SIL-Specific Coverage

| SIL | Tool Requirements | Workflow Coverage |
|-----|-------------------|-------------------|
| **SIL 0** | Tool qualification recommended | Workflow 1 Section 4, Workflow 2 Section 4.1 |
| **SIL 1-2** | Tool qualification MANDATORY, reports highly recommended | Workflow 1 Sections 6-7, Workflow 2 Section 4.2 |
| **SIL 3-4** | Tool qualification MANDATORY, reports MANDATORY, multiple tools required | Workflow 1 Sections 6-7 (complete), Workflow 2 Section 4.3 |

### Tool Coverage

| Tool | Classification | Workflow Coverage |
|------|----------------|-------------------|
| **GCC** | T3 (compiler) | Workflow 1 Section 7.4 (complete qualification example) |
| **GNU Make** | T2 (build system) | Workflow 2 Section 2.2 |
| **Cppcheck** | T2 (static analyzer) | Workflow 1 Section 6.4 (complete validation example) |
| **Clang Static Analyzer** | T2 (static analyzer) | Workflow 2 Section 5.2 |
| **Lizard** | T2 (complexity) | Workflow 1 Section 6.4, Workflow 2 Section 5.2 |
| **gcov/lcov** | T2 (coverage) | Workflow 2 Section 5.3 |
| **Unity** | T2 (test framework) | Workflow 2 Section 2.4 |
| **Valgrind** | T1 (memory analyzer) | Workflow 2 Section 5.4 |
| **Git** | T1 (version control) | Workflow 2 Section 2.6 |
| **workspace.py wf** | T1 (workflow manager) | Workflow 2 Section 2.6 |
| **workspace.py trace** | T1 (traceability) | Workflow 2 Section 5.5 |

---

## Usage Examples

### Example 1: Qualify GCC for SIL 3 Project

```bash
# Step 1: Classify GCC (T3 - full qualification required)
# (See Workflow 1 Section 7.4)

# Step 2: Obtain supplier qualification evidence
wget https://gcc.gnu.org/testresults/13.3.0/gcc-testresults-13.3.0.html \
  -O docs/tool-qualification/gcc-testresults.html

# Step 3: Perform project-specific validation
cd tests/tool-qualification/gcc-validation
gcc -std=c11 -Wall -Wextra -Werror -O2 \
    -o test-compiler test-compiler.c
./test-compiler
# Expected: "All GCC validation tests PASSED"

# Step 4: Create Tool Qualification Report
cp deliverables/tools/Tool-Qualification-Report-template.md \
   docs/tool-qualification/GCC-Qualification-Report.md
vim docs/tool-qualification/GCC-Qualification-Report.md

# Step 5: Submit for review and approval
python3 tools/workspace.py wf submit \
  --document "docs/tool-qualification/GCC-Qualification-Report.md" \
  --type "TOOL-QUALIFICATION" \
  --version "1.0" \
  --approver "QUA" \
  --sil 3

# Step 6: Obtain approvals (QUA, VER, PM)
# (See Workflow 1 Section 10.2 for complete example)

# Step 7: Baseline GCC version
gcc --version > docs/tool-qualification/gcc-version.txt
sha256sum $(which gcc) > docs/tool-qualification/gcc-checksum.txt
git add docs/tool-qualification/
git commit -m "Add GCC 13.3.0 qualification evidence (SIL 3)"
git tag -a gcc-qualified-v13.3.0 -m "GCC 13.3.0 qualified for SIL 3"
```

### Example 2: Validate Cppcheck for SIL 3 Project

```bash
# Step 1: Classify Cppcheck (T2 - validation required)
# (See Workflow 1 Section 6.4)

# Step 2: Create validation test suite
mkdir -p tests/tool-validation/cppcheck-validation
cd tests/tool-validation/cppcheck-validation

# Create test files (see Workflow 1 Section 6.4 for complete examples)
# - test-null-pointer.c
# - test-buffer-overflow.c
# - test-uninitialized-variable.c
# - test-clean-code.c
# - run-validation.sh

# Step 3: Execute validation tests
chmod +x run-validation.sh
./run-validation.sh > validation-results.txt 2>&1
cat validation-results.txt
# Expected: "All validation tests PASSED"

# Step 4: Create Tool Validation Report
cp deliverables/tools/Tool-Validation-Report-template.md \
   docs/tool-qualification/Cppcheck-Validation-Report.md
vim docs/tool-qualification/Cppcheck-Validation-Report.md

# Step 5: Submit for review and approval
python3 tools/workspace.py wf submit \
  --document "docs/tool-qualification/Cppcheck-Validation-Report.md" \
  --type "TOOL-VALIDATION" \
  --version "1.0" \
  --approver "QUA" \
  --sil 3

# Step 6: Obtain approvals (QUA, VER, PM)
# (See Workflow 1 Section 10.1 for complete example)

# Step 7: Baseline Cppcheck version
cppcheck --version > docs/tool-qualification/cppcheck-version.txt
sha256sum $(which cppcheck) > docs/tool-qualification/cppcheck-checksum.txt
git add docs/tool-qualification/
git commit -m "Add Cppcheck 2.13.0 validation evidence (SIL 3)"
git tag -a cppcheck-validated-v2.13.0 -m "Cppcheck 2.13.0 validated"
```

### Example 3: Select Tools for IMP Agent (SIL 3 Project)

```bash
# Reference: Workflow 2 Section 3.3

# IMP agent tools for SIL 3:
# 1. GCC 13.3.0 (qualified, T3)
# 2. GNU Make 4.3 (validated, T2)
# 3. Cppcheck 2.13.0 (validated, T2)
# 4. Unity 2.5.x (validated, T2)
# 5. gcov/lcov (validated, T2)
# 6. Git 2.43.0 (T1)

# Verify tool versions
gcc --version | grep "13.3.0"
cppcheck --version | grep "2.13.0"

# Use tools in IMP workflow (see Workflow 2 Section 6.1)
```

---

## Integration with Other Skills

| Skill | Integration Point | Description |
|-------|-------------------|-------------|
| **en50128-requirements** | Tool usage | REQ agent uses workspace.py trace, validate_srs_template.py |
| **en50128-design** | Tool usage | DES agent uses workspace.py trace, validate_sas_sds_template.py, Graphviz |
| **en50128-implementation** | Tool usage | IMP agent uses GCC (qualified), Cppcheck (validated), Unity (validated) |
| **en50128-verification** | Tool usage | VER agent uses Cppcheck, Clang, Lizard (all validated) |
| **en50128-testing** | Tool usage | TST agent uses Unity, gcov/lcov, mcdc_analyzer.py (all validated) |
| **en50128-integration** | Tool usage | INT agent uses GCC, Make, Valgrind |
| **en50128-validation** | Tool usage | VAL agent uses test executables built with qualified tools |
| **en50128-quality** | Tool qualification | QUA agent reviews and approves Tool Qualification Reports |
| **en50128-configuration** | Tool baseline | CM agent maintains tool baseline, tool version control |
| **en50128-lifecycle-coordination** | Tool management | COD agent ensures tools qualified before Phase 2 (Requirements) |

---

## References

### Primary References

- **TOOLS.md**: Comprehensive tool catalog (904 lines)
- **Tool-Baseline.md**: Baselined tool versions for project
- **Tool Qualification Reports**: `docs/tool-qualification/*-Qualification-Report.md`
- **Tool Validation Reports**: `docs/tool-qualification/*-Validation-Report.md`

### EN 50128 Standard References

- **EN 50128:2011 Section 6.7**: Software tools and their validation (PRIMARY)
- **EN 50128:2011 Section 6.7.4**: Tool classification (T1/T2/T3)
- **EN 50128:2011 Section 6.7.4.2**: T1 tools (no qualification required)
- **EN 50128:2011 Section 6.7.4.3**: T2 tools (validation required)
- **EN 50128:2011 Section 6.7.4.4**: T3 tools (full qualification required)
- **EN 50128:2011 Section 6.7.4.5**: Tool qualification process
- **EN 50128:2011 Table A.4**: Design and implementation techniques (tool requirements)
- **EN 50128:2011 Table A.19**: Static analysis techniques
- **EN 50128:2011 Table A.21**: Test coverage requirements

### External Tool Documentation

- **GCC Documentation**: https://gcc.gnu.org/onlinedocs/
- **GCC Test Results**: https://gcc.gnu.org/testresults/
- **Cppcheck Manual**: https://cppcheck.sourceforge.io/manual.pdf
- **Clang Static Analyzer**: https://clang-analyzer.llvm.org/
- **Lizard Documentation**: https://github.com/terryyin/lizard
- **Valgrind Manual**: https://valgrind.org/docs/manual/manual.html
- **Unity Test Framework**: https://github.com/ThrowTheSwitch/Unity

---

## Skill Metadata

**Skill Name**: en50128-tools  
**Version**: 1.0  
**Last Updated**: 2026-03-14  
**Status**: ✅ Complete  
**Workflows**: 2 comprehensive workflows (~1,613 lines, ~65 pages)  
**Templates**: 2 templates (Tool Qualification Report, Tool Validation Report)  
**EN 50128 Coverage**: Section 6.7 (complete), Tables A.4, A.19, A.21  
**SIL Coverage**: All SIL levels (0, 1, 2, 3, 4)  
**Agent Coverage**: All agents (REQ, DES, IMP, TST, VER, INT, VAL, SAF, QUA, CM, PM, COD)

---

**END OF SKILL**
