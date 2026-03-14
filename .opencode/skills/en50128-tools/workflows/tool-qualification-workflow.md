# Tool Qualification Workflow

**EN 50128 Reference**: Section 6.7 - Software tools and their validation  
**Scope**: Tool qualification for SIL 0-4 railway software development  
**Target Roles**: All agents (REQ, DES, IMP, TST, VER, INT, VAL, SAF, QUA, CM, PM, COD)  
**Document**: This workflow supports creation and management of Tool Qualification Reports

---

## Table of Contents

1. [Overview](#1-overview)
2. [EN 50128 Requirements](#2-en-50128-requirements)
3. [Tool Confidence Levels](#3-tool-confidence-levels)
4. [Tool Qualification Process](#4-tool-qualification-process)
5. [T1 Tools - No Qualification Required](#5-t1-tools---no-qualification-required)
6. [T2 Tools - Validation Required](#6-t2-tools---validation-required)
7. [T3 Tools - Full Qualification Required](#7-t3-tools---full-qualification-required)
8. [Tool Qualification Report](#8-tool-qualification-report)
9. [Tool Validation Automation](#9-tool-validation-automation)
10. [Complete Example Scenarios](#10-complete-example-scenarios)
11. [Tool Integration](#11-tool-integration)
12. [References](#12-references)

---

## 1. Overview

### 1.1 Purpose

This workflow defines the process for qualifying software tools used in EN 50128-compliant railway software development. Tool qualification ensures that tools used in the development lifecycle do not introduce undetected errors that could compromise software safety.

**Key Objectives**:
- Classify tools by Tool Confidence Level (TCL): T1, T2, T3
- Define qualification requirements for each TCL
- Provide step-by-step qualification procedures
- Document tool qualification evidence
- Maintain tool qualification status throughout project lifecycle

### 1.2 Scope

**Tools Covered**:
- **Development tools**: Compilers (gcc), build systems (make), editors
- **Verification tools**: Static analyzers (cppcheck, clang), complexity analyzers (lizard)
- **Testing tools**: Coverage tools (gcov, lcov), test frameworks (Unity, CUnit)
- **Analysis tools**: Memory analyzers (valgrind), profilers
- **Management tools**: Version control (git), configuration management
- **Custom tools**: Python scripts (traceability manager, workflow manager, validators)

**SIL Applicability**: All SIL levels (0, 1, 2, 3, 4)
- Tool qualification **MANDATORY** for SIL 1-4 (Section 6.7.4.5)
- Tool qualification **RECOMMENDED** for SIL 0

### 1.3 Key Definitions

| Term | Definition | EN 50128 Reference |
|------|------------|-------------------|
| **Tool Confidence Level (TCL)** | Classification of tool based on potential for undetected errors | Section 6.7.4 |
| **T1 Tool** | Tool errors cannot affect output integrity (no qualification needed) | Section 6.7.4.2 |
| **T2 Tool** | Tool errors may go undetected (validation required) | Section 6.7.4.3 |
| **T3 Tool** | Tool output not verified by other means (full qualification) | Section 6.7.4.4 |
| **Tool Qualification** | Process of demonstrating tool fitness for use | Section 6.7.4.5 |
| **Tool Validation** | Verification that tool produces correct results | Section 6.7.4.3 |

### 1.4 Workflow Integration

**Lifecycle Phase**: Throughout all phases (tool qualification done during Phase 1: Planning)

**Inputs**:
- TOOLS.md (tool catalog)
- Software Quality Assurance Plan (SQAP) - tool requirements
- Software Verification Plan (SVP) - verification tool requirements
- SIL level determination

**Outputs**:
- Tool Qualification Reports (for T2 and T3 tools)
- Tool Validation Results (for T2 tools)
- Tool Qualification Evidence (certificates, validation suites, test results)
- Tool Usage Guidelines

**Related Workflows**:
- Quality Assurance workflows (tool audits)
- Configuration Management workflows (tool version control)
- Verification workflows (static analysis tools)
- Testing workflows (coverage tools, test frameworks)

---

## 2. EN 50128 Requirements

### 2.1 Section 6.7: Software tools and their validation

**Key Requirements**:

```
EN 50128:2011 Section 6.7.4:
"Software tools shall be classified according to the potential for undetected
errors in the tool to result in software errors. Tools shall be validated or
qualified as appropriate to their classification."
```

**Mandatory Requirements by SIL**:

| Requirement | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 |
|-------------|-------|-------|-------|-------|-------|
| Tool classification (T1/T2/T3) | R | M | M | M | M |
| T2 tool validation | R | M | M | M | M |
| T3 tool qualification | R | M | M | M | M |
| Tool qualification report | - | HR | HR | M | M |
| Tool version control | HR | HR | M | M | M |
| Tool validation suite | - | R | HR | M | M |

**Key**: M = Mandatory, HR = Highly Recommended, R = Recommended, - = No recommendation

### 2.2 Tool Confidence Levels (Section 6.7.4)

**T1 - No Qualification Required** (Section 6.7.4.2):
- Definition: Tool errors cannot affect software integrity
- Reason: Tool output is verified by other means (e.g., review, testing)
- Examples: Editors, reporting tools, documentation generators
- Requirement: **No qualification needed**

**T2 - Validation Required** (Section 6.7.4.3):
- Definition: Tool errors may go undetected
- Reason: Tool output used directly but verified by other tools/processes
- Examples: Static analyzers, complexity tools, coverage tools
- Requirement: **Validation required** (demonstrate correctness on representative samples)

**T3 - Full Qualification Required** (Section 6.7.4.4):
- Definition: Tool output not verified by other means
- Reason: Tool errors directly affect software safety (e.g., compiler errors)
- Examples: Compilers, linkers, code generators
- Requirement: **Full qualification required** (comprehensive evidence of correctness)

### 2.3 Tool Qualification Process (Section 6.7.4.5)

**EN 50128 Section 6.7.4.5 Requirements**:

```
"Tool qualification shall involve:
a) Tool classification (T1, T2, or T3)
b) Tool specification (functionality, version, platform)
c) Tool validation or qualification evidence
d) Tool usage constraints and limitations
e) Tool version control and configuration management"
```

**Tool Qualification Report Contents** (SIL 3-4 MANDATORY):
1. Tool identification (name, version, vendor)
2. Tool classification justification (T1/T2/T3)
3. Tool usage description (purpose, scope, agents)
4. Validation/qualification evidence (test results, certificates)
5. Tool constraints and limitations
6. Tool version control procedures
7. Approval records

---

## 3. Tool Confidence Levels

### 3.1 T1 Tools - No Qualification Required

**Definition**: Tools whose output is verified by other means, such that tool errors cannot result in undetected software errors.

**Classification Criteria**:
- Tool output is reviewed by humans (e.g., documents)
- Tool output is verified by other tools (e.g., test results verified by manual inspection)
- Tool is used for information only (e.g., reporting, visualization)

**T1 Tool Examples**:

| Tool | Purpose | Why T1 | Verification Method |
|------|---------|--------|---------------------|
| **Text Editors** | Code editing | Human review | Code review process |
| **Markdown Editors** | Documentation | Human review | Document review |
| **Visualization Tools** | Traceability graphs | Information only | Manual inspection of data |
| **Reporting Tools** | Test reports | Information only | Test results verified independently |
| **Custom Python Scripts** | Analysis, reporting | Output verified | Script results reviewed manually |
| **Valgrind** | Memory analysis | Defect detection only | Findings verified by code inspection |
| **Git** | Version control | Configuration management | Repository state verified by CM |

**T1 Tool Qualification Process**:
1. **Document tool classification**: Explain why tool is T1
2. **Document verification method**: How tool output is verified
3. **No further qualification required**

**Example T1 Classification**:

```markdown
## Tool: Valgrind (Memory Analyzer)

**Classification**: T1 - No Qualification Required

**Justification**:
- Purpose: Detect memory errors (leaks, invalid access, uninitialized reads)
- Output: Memory error reports (findings)
- Verification: All Valgrind findings are manually inspected and verified by code review
- Impact of tool error: False negative (missed error) → detected by testing
                       False positive (spurious error) → dismissed during code review
- Conclusion: Tool errors cannot result in undetected software errors

**Usage**:
- Agent: IMP, TST, VER
- Command: valgrind --leak-check=full --track-origins=yes ./executable
- Output: Memory error report (text file)
- Verification: Manual review of all reported errors
```

### 3.2 T2 Tools - Validation Required

**Definition**: Tools whose output is used in the software development but is verified by other tools or processes, such that tool errors are likely to be detected.

**Classification Criteria**:
- Tool output is used directly (not just information)
- Tool output is verified by other tools or independent processes
- Tool errors are likely to be detected through verification

**T2 Tool Examples**:

| Tool | Purpose | Why T2 | Verification Method |
|------|---------|--------|---------------------|
| **Cppcheck** | Static analysis | Findings verified | Manual review + other analyzers |
| **Clang Static Analyzer** | Static analysis | Findings verified | Manual review + other analyzers |
| **Lizard** | Complexity analysis | Metrics verified | Manual review of flagged functions |
| **gcov** | Code coverage | Coverage verified | Manual inspection of uncovered code |
| **lcov** | Coverage reporting | Coverage verified | Manual inspection + gcov cross-check |
| **Unity** | Unit test framework | Test results verified | Test review + manual testing |
| **CUnit** | Unit test framework | Test results verified | Test review + manual testing |

**T2 Tool Qualification Process**:
1. **Tool Classification**: Document why tool is T2
2. **Tool Validation**: Demonstrate correctness on representative samples
3. **Validation Test Suite**: Create validation tests covering tool functionality
4. **Validation Results**: Document validation test results
5. **Tool Qualification Report**: Document all evidence (MANDATORY SIL 3-4)

**T2 Validation Requirements**:

| SIL | Validation Extent | Validation Evidence | Report Required |
|-----|-------------------|---------------------|-----------------|
| **SIL 0** | Basic validation | Informal testing | No |
| **SIL 1-2** | Representative samples | Test results documented | Highly Recommended |
| **SIL 3-4** | Comprehensive validation | Full test suite + results | **MANDATORY** |

### 3.3 T3 Tools - Full Qualification Required

**Definition**: Tools whose output is not verified by other means and is used directly in the software, such that tool errors may directly result in software errors.

**Classification Criteria**:
- Tool output is used directly in final software (e.g., compiled code)
- Tool output is NOT verified by other independent means
- Tool errors directly affect software safety

**T3 Tool Examples**:

| Tool | Purpose | Why T3 | Risk |
|------|---------|--------|------|
| **GCC** | C compiler | Generated code not verified | Incorrect code generation → safety failure |
| **GNU ld** | Linker | Linked executable not verified | Incorrect linking → runtime failure |
| **Make** | Build system | Build process not verified | Incorrect build → wrong software version |
| **Code Generators** | Auto-code generation | Generated code not fully reviewed | Incorrect generation → software errors |

**T3 Tool Qualification Process**:
1. **Tool Classification**: Document why tool is T3
2. **Tool Specification**: Define tool functionality, version, platform
3. **Qualification Evidence**: Obtain comprehensive evidence:
   - **Supplier qualification**: Tool vendor's qualification data (e.g., compiler validation suite)
   - **Project-specific validation**: Validate tool for project's usage scenarios
   - **Tool certification**: Industry-recognized certification (e.g., TÜV certification)
4. **Tool Qualification Report**: Comprehensive report (MANDATORY SIL 1-4)
5. **Tool Version Control**: Strict version control and configuration management

**T3 Qualification Requirements**:

| SIL | Qualification Extent | Evidence Required | Report Required |
|-----|----------------------|-------------------|-----------------|
| **SIL 0** | Basic validation | Informal testing | No |
| **SIL 1-2** | Supplier qualification + validation | Supplier docs + test results | **MANDATORY** |
| **SIL 3-4** | Full qualification | Supplier certification + validation suite + project validation | **MANDATORY** |

---

## 4. Tool Qualification Process

### 4.1 Overall Process Flow

```
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 1: TOOL IDENTIFICATION                                    │
│ - Identify all tools needed for project                         │
│ - Reference TOOLS.md (tool catalog)                             │
│ - Determine SIL level requirements                              │
└─────────────┬───────────────────────────────────────────────────┘
              ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 2: TOOL CLASSIFICATION                                    │
│ - Classify each tool: T1, T2, or T3                             │
│ - Document classification justification                         │
│ - Review classification with QUA                                │
└─────────────┬───────────────────────────────────────────────────┘
              ↓
         ┌────┴────┐
         │         │
    T1 Tools   T2/T3 Tools
         │         │
         ↓         ↓
    No further   Continue
    action
                 ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 3: TOOL QUALIFICATION/VALIDATION                          │
│                                                                  │
│ T2 Tools: VALIDATION                                            │
│ - Create validation test suite                                  │
│ - Execute validation tests                                      │
│ - Document validation results                                   │
│                                                                  │
│ T3 Tools: FULL QUALIFICATION                                    │
│ - Obtain supplier qualification evidence                        │
│ - Perform project-specific validation                           │
│ - Obtain certification (if required for SIL 3-4)                │
└─────────────┬───────────────────────────────────────────────────┘
              ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 4: TOOL QUALIFICATION REPORT                              │
│ - Create Tool Qualification Report (T2/T3, SIL 3-4 MANDATORY)   │
│ - Document all evidence                                         │
│ - Submit for QUA review                                         │
│ - Obtain approvals (PM, QUA, VER for SIL 3-4)                  │
└─────────────┬───────────────────────────────────────────────────┘
              ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 5: TOOL BASELINE AND CONFIGURATION MANAGEMENT             │
│ - Baseline tool versions (exact versions recorded)              │
│ - Configure CM for tool version control                         │
│ - Lock tool versions for project (SIL 3-4)                      │
│ - Document tool update procedures                               │
└─────────────┬───────────────────────────────────────────────────┘
              ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 6: ONGOING TOOL MANAGEMENT                                │
│ - Monitor tool issues (bugs, security vulnerabilities)          │
│ - Maintain tool qualification evidence                          │
│ - Re-qualify tools if updated (trigger re-qualification)        │
│ - Audit tool usage (QUA periodic audits)                        │
└─────────────────────────────────────────────────────────────────┘
```

### 4.2 Phase 1: Tool Identification

**Objective**: Identify all tools needed for the project.

**Steps**:

**Step 1.1: Review TOOLS.md**
```bash
# Review tool catalog
cat TOOLS.md

# Identify tools by agent role
# REQ: Requirements management, traceability
# DES: Design tools, modeling
# IMP: Compiler, build system, editors
# TST: Test frameworks, coverage tools
# VER: Static analyzers, complexity tools
# etc.
```

**Step 1.2: Document Tool List**

Create `docs/tool-qualification/Tool-List.md`:

```markdown
# Project Tool List

**Project**: [Project Name]
**SIL Level**: [0/1/2/3/4]
**Date**: YYYY-MM-DD

## Tools Identified

| Tool | Version | Purpose | Agent(s) | Classification | Status |
|------|---------|---------|----------|----------------|--------|
| gcc | 13.3.0 | C compiler | IMP, TST, INT | T3 | To be qualified |
| cppcheck | 2.13.0 | Static analyzer | VER | T2 | To be validated |
| gcov | 13.3.0 | Coverage tool | TST | T2 | To be validated |
| git | 2.43.0 | Version control | CM | T1 | No qualification |
| ... | ... | ... | ... | ... | ... |
```

**Step 1.3: Determine SIL Requirements**

Identify qualification requirements based on project SIL level:
- **SIL 0**: Tool qualification recommended (not mandatory)
- **SIL 1-2**: T2 and T3 tool qualification mandatory
- **SIL 3-4**: T2 and T3 tool qualification mandatory + Tool Qualification Reports mandatory

### 4.3 Phase 2: Tool Classification

**Objective**: Classify each tool as T1, T2, or T3.

**Step 2.1: Apply Classification Criteria**

For each tool, ask these questions:

**Question 1**: Is the tool output verified by other means?
- **Yes** → Likely T1
- **No** → Continue to Question 2

**Question 2**: Is the tool output used directly in software development?
- **Yes** → Continue to Question 3
- **No** (information only) → T1

**Question 3**: Is the tool output verified by another independent tool or process?
- **Yes** → T2
- **No** → T3

**Classification Decision Tree**:

```
START: Classify tool
  |
  ├─ Output verified by review/other means?
  │   ├─ YES → T1 (no qualification)
  │   └─ NO → Continue
  |
  ├─ Output used directly in development?
  │   ├─ NO (information only) → T1
  │   └─ YES → Continue
  |
  └─ Output verified by independent tool/process?
      ├─ YES → T2 (validation required)
      └─ NO → T3 (full qualification required)
```

**Step 2.2: Document Classification Justification**

For each tool, create a classification justification document:

```markdown
## Tool: [Tool Name]

**Classification**: [T1 / T2 / T3]

**Justification**:
- **Purpose**: [What does the tool do?]
- **Output**: [What does the tool produce?]
- **Usage**: [How is the output used?]
- **Verification**: [How is the output verified?]
- **Impact of tool error**: [What happens if the tool has a bug?]
  - False negative (missed error): [Impact]
  - False positive (spurious finding): [Impact]
  - Incorrect output: [Impact]
- **Conclusion**: [Why this classification is correct]

**Review**:
- Reviewed by: [Name]
- Role: QUA
- Date: YYYY-MM-DD
- Approval: [Approved / Rejected]
```

**Step 2.3: QUA Review of Classification**

All tool classifications MUST be reviewed by QUA agent (SIL 1-4 MANDATORY).

```bash
# Submit tool classification for QUA review
python3 tools/workspace.py wf submit \
  --document "docs/tool-qualification/Tool-Classification.md" \
  --type "TOOL-CLASSIFICATION" \
  --version "1.0" \
  --approver "QUA" \
  --sil 3
```

### 4.4 Phase 3: Tool Qualification/Validation

**Objective**: Qualify T2 and T3 tools according to EN 50128 requirements.

**Step 3.1: T2 Tool Validation**

For each T2 tool:

**3.1.1: Create Validation Test Suite**

Create a validation test suite that exercises the tool's functionality on representative samples.

**Example: Cppcheck Validation Test Suite** (`tests/tool-validation/cppcheck-validation/`)

```c
/* test-null-pointer.c - Test Cppcheck detects NULL pointer dereference */
#include <stddef.h>

void function_with_null_deref(void) {
    int* ptr = NULL;
    *ptr = 42;  /* ERROR: NULL pointer dereference - Cppcheck MUST detect */
}
```

```c
/* test-buffer-overflow.c - Test Cppcheck detects buffer overflow */
#include <string.h>

void function_with_overflow(void) {
    char buffer[10];
    strcpy(buffer, "This string is longer than 10 characters");  /* ERROR: Buffer overflow - Cppcheck MUST detect */
}
```

```c
/* test-uninitialized-variable.c - Test Cppcheck detects uninitialized variable */
void function_with_uninit(void) {
    int x;
    int y = x + 1;  /* ERROR: Uninitialized variable - Cppcheck MUST detect */
}
```

```c
/* test-clean-code.c - Test Cppcheck produces no false positives */
#include <stddef.h>

void clean_function(int* ptr) {
    if (ptr != NULL) {
        *ptr = 42;  /* OK: NULL check before dereference */
    }
}
```

**3.1.2: Create Validation Test Runner**

Create `tests/tool-validation/cppcheck-validation/run-validation.sh`:

```bash
#!/bin/bash
# Cppcheck Validation Test Suite Runner

echo "=== Cppcheck Validation Test Suite ==="
echo "Tool: Cppcheck"
echo "Version: $(cppcheck --version)"
echo "Date: $(date)"
echo ""

# Test 1: NULL pointer dereference detection
echo "Test 1: NULL pointer dereference detection"
cppcheck --enable=all test-null-pointer.c 2>&1 | grep -q "Null pointer dereference"
if [ $? -eq 0 ]; then
    echo "  PASS: Cppcheck detected NULL pointer dereference"
else
    echo "  FAIL: Cppcheck missed NULL pointer dereference"
    exit 1
fi

# Test 2: Buffer overflow detection
echo "Test 2: Buffer overflow detection"
cppcheck --enable=all test-buffer-overflow.c 2>&1 | grep -q "Buffer overrun"
if [ $? -eq 0 ]; then
    echo "  PASS: Cppcheck detected buffer overflow"
else
    echo "  FAIL: Cppcheck missed buffer overflow"
    exit 1
fi

# Test 3: Uninitialized variable detection
echo "Test 3: Uninitialized variable detection"
cppcheck --enable=all test-uninitialized-variable.c 2>&1 | grep -q "Uninitialized variable"
if [ $? -eq 0 ]; then
    echo "  PASS: Cppcheck detected uninitialized variable"
else
    echo "  FAIL: Cppcheck missed uninitialized variable"
    exit 1
fi

# Test 4: No false positives on clean code
echo "Test 4: No false positives on clean code"
cppcheck --enable=all test-clean-code.c 2>&1 | grep -q "error:"
if [ $? -ne 0 ]; then
    echo "  PASS: Cppcheck produced no false positives"
else
    echo "  FAIL: Cppcheck produced false positives on clean code"
    exit 1
fi

echo ""
echo "=== All validation tests PASSED ==="
echo "Cppcheck is validated for use in this project."
```

**3.1.3: Execute Validation Tests**

```bash
cd tests/tool-validation/cppcheck-validation
chmod +x run-validation.sh
./run-validation.sh > validation-results.txt 2>&1
```

**3.1.4: Document Validation Results**

Create `docs/tool-qualification/Cppcheck-Validation-Report.md`:

```markdown
# Cppcheck Validation Report

**Tool**: Cppcheck  
**Version**: 2.13.0  
**Classification**: T2 (Validation Required)  
**Project**: Train Door Control System  
**SIL Level**: 3  
**Date**: 2026-03-14

## Validation Test Suite

**Location**: `tests/tool-validation/cppcheck-validation/`

**Tests Executed**:
1. NULL pointer dereference detection
2. Buffer overflow detection
3. Uninitialized variable detection
4. Clean code (no false positives)

## Validation Results

**Test Execution Date**: 2026-03-14  
**Test Execution Command**: `./run-validation.sh`

**Results**:
```
=== Cppcheck Validation Test Suite ===
Tool: Cppcheck
Version: Cppcheck 2.13.0

Test 1: NULL pointer dereference detection
  PASS: Cppcheck detected NULL pointer dereference
Test 2: Buffer overflow detection
  PASS: Cppcheck detected buffer overflow
Test 3: Uninitialized variable detection
  PASS: Cppcheck detected uninitialized variable
Test 4: No false positives on clean code
  PASS: Cppcheck produced no false positives

=== All validation tests PASSED ===
```

## Validation Conclusion

Cppcheck 2.13.0 has been validated for use in this project:
- ✅ All validation tests passed
- ✅ Tool correctly detects common C defects
- ✅ Tool produces no false positives on clean code
- ✅ Tool is suitable for static analysis in SIL 3 development

## Tool Usage Constraints

- Use with flags: `--enable=all --xml --xml-version=2`
- All findings MUST be reviewed manually (not auto-accepted)
- Tool is T2: findings verified by code review and other analyzers

## Approval

| Role | Name | Date | Signature |
|------|------|------|-----------|
| QUA | [Name] | 2026-03-14 | [Signature] |
| VER | [Name] | 2026-03-14 | [Signature] |
| PM | [Name] | 2026-03-14 | [Signature] |
```

**Step 3.2: T3 Tool Qualification**

For each T3 tool:

**3.2.1: Obtain Supplier Qualification Evidence**

For commercial tools (e.g., GCC), obtain qualification evidence from tool supplier:
- Tool Qualification Report from vendor
- Compiler validation suite results (e.g., Plum Hall Validation Suite for GCC)
- Certification documents (e.g., TÜV certification for safety-critical compilers)

**Example: GCC Qualification Evidence**

```markdown
# GCC Qualification Evidence

**Tool**: GCC (GNU Compiler Collection)
**Version**: 13.3.0
**Classification**: T3 (Full Qualification Required)

## Supplier Evidence

1. **GCC Test Suite Results**:
   - Location: https://gcc.gnu.org/testresults/
   - GCC 13.3.0 test results: 99.8% pass rate
   - Failed tests documented and assessed (none affect safety-critical code)

2. **MISRA C Compliance**:
   - GCC supports MISRA C:2012 with appropriate flags
   - Documentation: https://gcc.gnu.org/onlinedocs/gcc/C-Dialect-Options.html

3. **Industry Usage**:
   - GCC widely used in safety-critical domains (automotive, aerospace, rail)
   - Multiple safety-certified projects use GCC

## Project-Specific Validation

1. **Compiler Options Validation**:
   - Validate that compiler flags produce correct code
   - Test: Compile reference programs, verify output correctness

2. **Platform-Specific Validation**:
   - Validate GCC on target platform (x86-64 Linux)
   - Test: Compile and run platform-specific code

3. **Code Generation Validation**:
   - Validate that GCC generates correct machine code
   - Test: Compile test programs, disassemble, verify assembly correctness
```

**3.2.2: Perform Project-Specific Validation**

Even with supplier qualification, perform project-specific validation:

**Example: GCC Project-Specific Validation**

Create `tests/tool-qualification/gcc-validation/test-compiler.c`:

```c
/* test-compiler.c - GCC validation test */
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

/* Test 1: Integer arithmetic */
void test_integer_arithmetic(void) {
    int32_t a = 100;
    int32_t b = 200;
    int32_t sum = a + b;
    assert(sum == 300);  /* Verify compiler generates correct add */
}

/* Test 2: Pointer arithmetic */
void test_pointer_arithmetic(void) {
    uint8_t array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    uint8_t* ptr = &array[0];
    ptr += 5;
    assert(*ptr == 5);  /* Verify compiler generates correct pointer add */
}

/* Test 3: Function calls */
static int32_t add(int32_t a, int32_t b) {
    return a + b;
}

void test_function_calls(void) {
    int32_t result = add(10, 20);
    assert(result == 30);  /* Verify compiler generates correct call/return */
}

/* Test 4: Optimization correctness */
void test_optimization(void) {
    volatile int32_t x = 10;  /* volatile prevents optimization */
    int32_t y = x + 1;
    assert(y == 11);  /* Verify optimizer doesn't break correctness */
}

int main(void) {
    test_integer_arithmetic();
    test_pointer_arithmetic();
    test_function_calls();
    test_optimization();
    
    printf("All GCC validation tests PASSED\n");
    return 0;
}
```

**Compile and Run Validation Tests**:

```bash
# Compile with SIL 3 flags
gcc -std=c11 -Wall -Wextra -Werror -pedantic -O2 \
    -DSIL_LEVEL=3 -DMISRA_C_2012 \
    -fstack-protector-strong -D_FORTIFY_SOURCE=2 \
    -o test-compiler test-compiler.c

# Run validation
./test-compiler

# Expected output: "All GCC validation tests PASSED"
```

**3.2.3: Create Tool Qualification Report**

Create comprehensive Tool Qualification Report (MANDATORY SIL 3-4).

See Section 8 for complete Tool Qualification Report template.

### 4.5 Phase 4: Tool Qualification Report

**Objective**: Document all tool qualification evidence in a formal report.

**Requirements**:
- **MANDATORY** for T2 and T3 tools at SIL 3-4
- **HIGHLY RECOMMENDED** for T2 and T3 tools at SIL 1-2
- **RECOMMENDED** for SIL 0

See Section 8 for complete report template and examples.

### 4.6 Phase 5: Tool Baseline and Configuration Management

**Objective**: Baseline tool versions and establish configuration management.

**Step 5.1: Record Exact Tool Versions**

Create `docs/tool-qualification/Tool-Baseline.md`:

```markdown
# Tool Baseline

**Project**: Train Door Control System
**SIL Level**: 3
**Baseline Date**: 2026-03-14
**Baseline Version**: 1.0

## Baseline Tool Versions

| Tool | Version | SHA256 Checksum (executable) | Qualification Status |
|------|---------|------------------------------|----------------------|
| gcc | 13.3.0 | abc123def456... | Qualified (Report: DOC-TQR-GCC-001) |
| cppcheck | 2.13.0 | 789ghi012jkl... | Validated (Report: DOC-TVR-CPPCHECK-001) |
| gcov | 13.3.0 | mno345pqr678... | Validated (Report: DOC-TVR-GCOV-001) |
| git | 2.43.0 | stu901vwx234... | T1 (No qualification) |

## Tool Version Control

**Policy**: Tool versions are LOCKED for this project (SIL 3).

**Change Procedure**:
1. Tool update requires Change Request (CR)
2. CR includes re-qualification plan
3. CCB approval required
4. Re-qualification performed before tool update
5. New baseline created after tool update
```

**Step 5.2: Lock Tool Versions (SIL 3-4)**

For SIL 3-4 projects, tool versions MUST be locked:

```bash
# Document installed tool versions
gcc --version > docs/tool-qualification/gcc-version.txt
cppcheck --version > docs/tool-qualification/cppcheck-version.txt
gcov --version > docs/tool-qualification/gcov-version.txt

# Compute checksums of tool executables
sha256sum $(which gcc) > docs/tool-qualification/gcc-checksum.txt
sha256sum $(which cppcheck) > docs/tool-qualification/cppcheck-checksum.txt
sha256sum $(which gcov) > docs/tool-qualification/gcov-checksum.txt

# Baseline in version control
git add docs/tool-qualification/
git commit -m "Baseline tool versions for SIL 3 project"
git tag -a tool-baseline-v1.0 -m "Tool baseline version 1.0"
```

**Step 5.3: Configure CI/CD Tool Version Checks**

Create `.github/workflows/tool-version-check.yml` (for SIL 3-4):

```yaml
name: Tool Version Check

on: [push, pull_request]

jobs:
  check-tool-versions:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Check GCC version
        run: |
          EXPECTED="gcc (GCC) 13.3.0"
          ACTUAL=$(gcc --version | head -n1)
          if [ "$ACTUAL" != "$EXPECTED" ]; then
            echo "ERROR: GCC version mismatch"
            echo "Expected: $EXPECTED"
            echo "Actual: $ACTUAL"
            exit 1
          fi
      
      - name: Check Cppcheck version
        run: |
          EXPECTED="Cppcheck 2.13.0"
          ACTUAL=$(cppcheck --version)
          if [ "$ACTUAL" != "$EXPECTED" ]; then
            echo "ERROR: Cppcheck version mismatch"
            exit 1
          fi
      
      - name: All tool versions correct
        run: echo "✅ All tool versions match baseline"
```

### 4.7 Phase 6: Ongoing Tool Management

**Objective**: Maintain tool qualification throughout project lifecycle.

**Step 6.1: Monitor Tool Issues**

- Subscribe to tool security advisories (e.g., GCC mailing lists)
- Monitor tool bug reports
- Track tool updates and patches

**Step 6.2: Tool Update Procedure (SIL 3-4)**

When a tool update is needed:

```
1. Create Change Request (CR):
   - Document reason for tool update (bug fix, security patch, new feature)
   - Document impact of tool update
   - Document re-qualification plan

2. CCB Reviews CR:
   - Assess impact on project
   - Approve/reject CR

3. Re-Qualify Tool:
   - Re-run validation test suite
   - Update Tool Qualification Report
   - QUA reviews updated report

4. Update Tool Baseline:
   - Update Tool-Baseline.md
   - Record new tool version and checksum
   - Create new baseline tag

5. Update Project:
   - Update all systems to new tool version
   - Verify CI/CD uses new version
   - Update documentation
```

**Step 6.3: Tool Audits (QUA)**

QUA agent performs periodic tool audits:
- Verify tool versions match baseline
- Verify tool qualification evidence is current
- Verify tool usage follows Tool Qualification Reports
- Document audit findings

---

## 5. T1 Tools - No Qualification Required

### 5.1 T1 Tool List

**T1 Tools Used in Project**:

| Tool | Purpose | Agent | Verification Method |
|------|---------|-------|---------------------|
| **vim / emacs / vscode** | Code editing | IMP | Code review |
| **Markdown editors** | Documentation | REQ, DES, QUA | Document review |
| **Git** | Version control | CM | Repository audits |
| **Valgrind** | Memory analysis | IMP, VER | Manual review of findings |
| **Python scripts (custom)** | Analysis, reporting | All | Output reviewed manually |
| **enhelp.py** | EN 50128 reference | All | Information only |
| **Graphviz** | Traceability visualization | REQ, VER | Manual inspection |

### 5.2 T1 Tool Documentation

For T1 tools, minimal documentation is required:

```markdown
## T1 Tool: [Tool Name]

**Classification**: T1 - No Qualification Required

**Purpose**: [Brief description]

**Agent(s)**: [Which agents use this tool]

**Verification Method**: [How is the output verified?]
- Example: "Code review verifies all code changes"
- Example: "Manual inspection of report findings"

**Conclusion**: Tool errors cannot result in undetected software errors due to [verification method].

**QUA Review**: ✅ Approved by [Name] on [Date]
```

### 5.3 T1 Tool Management

Even though T1 tools require no qualification:
- **Document tool usage** in project documentation
- **Record tool versions** in Tool-Baseline.md (for reproducibility)
- **Version control** tool configurations (e.g., .vimrc, .gitconfig)

---

## 6. T2 Tools - Validation Required

### 6.1 T2 Tool List

**T2 Tools Used in Project** (SIL 3 example):

| Tool | Purpose | Agent | Validation Status |
|------|---------|-------|-------------------|
| **Cppcheck 2.13.0** | Static analysis | VER | ✅ Validated |
| **Clang Static Analyzer 18.x** | Static analysis | VER | ✅ Validated |
| **Lizard 1.17.x** | Complexity analysis | VER, QUA | ✅ Validated |
| **gcov 13.3.0** | Coverage measurement | TST | ✅ Validated |
| **lcov 1.16** | Coverage reporting | TST | ✅ Validated |
| **Unity 2.5.x** | Unit test framework | TST | ✅ Validated |

### 6.2 T2 Validation Requirements by SIL

| SIL | Validation Extent | Validation Tests | Report Required |
|-----|-------------------|------------------|-----------------|
| **SIL 0** | Basic validation | 3-5 tests covering main functionality | No (recommended to document informally) |
| **SIL 1-2** | Representative samples | 10-20 tests covering key use cases | Highly Recommended |
| **SIL 3-4** | Comprehensive validation | 20+ tests covering all functionality | **MANDATORY** |

### 6.3 T2 Validation Test Suite Design

**Validation Test Suite Contents**:

1. **Positive Tests**: Tool correctly detects known defects
   - Example: Cppcheck detects NULL pointer dereference
   - Example: Lizard correctly calculates cyclomatic complexity

2. **Negative Tests**: Tool produces no false positives on clean code
   - Example: Cppcheck produces no errors on compliant code
   - Example: Lizard reports correct complexity for simple functions

3. **Boundary Tests**: Tool handles edge cases correctly
   - Example: Cppcheck handles maximum nesting depth
   - Example: Lizard handles very large functions

4. **Regression Tests**: Tool behavior consistent across versions
   - Example: Cppcheck 2.13.0 produces same results as 2.12.0 on reference code

**Test Suite Directory Structure**:

```
tests/tool-validation/
├── cppcheck-validation/
│   ├── test-null-pointer.c
│   ├── test-buffer-overflow.c
│   ├── test-uninitialized-variable.c
│   ├── test-clean-code.c
│   ├── run-validation.sh
│   └── validation-results.txt
├── lizard-validation/
│   ├── test-simple-function.c      # Expected CCN = 1
│   ├── test-complex-function.c     # Expected CCN = 15
│   ├── test-nested-loops.c         # Expected CCN = 10
│   ├── run-validation.sh
│   └── validation-results.txt
└── gcov-validation/
    ├── test-coverage-100.c         # Expected 100% coverage
    ├── test-coverage-partial.c     # Expected 50% coverage
    ├── run-validation.sh
    └── validation-results.txt
```

### 6.4 Example: Lizard Validation Test Suite

**File: `tests/tool-validation/lizard-validation/test-simple-function.c`**

```c
/* test-simple-function.c - Expected CCN = 1 (no branches) */

int simple_add(int a, int b) {
    return a + b;
}

/* Expected Lizard output: CCN = 1 */
```

**File: `tests/tool-validation/lizard-validation/test-complex-function.c`**

```c
/* test-complex-function.c - Expected CCN = 15 */

int complex_function(int x) {
    int result = 0;
    
    if (x > 0) {         /* +1 */
        if (x > 10) {    /* +1 */
            result = 1;
        } else if (x > 5) { /* +1 */
            result = 2;
        } else {
            result = 3;
        }
    } else if (x < 0) {  /* +1 */
        if (x < -10) {   /* +1 */
            result = -1;
        } else if (x < -5) { /* +1 */
            result = -2;
        } else {
            result = -3;
        }
    } else {
        result = 0;
    }
    
    switch (result) {
        case 1:          /* +1 */
            result += 10;
            break;
        case 2:          /* +1 */
            result += 20;
            break;
        case 3:          /* +1 */
            result += 30;
            break;
        case -1:         /* +1 */
            result -= 10;
            break;
        case -2:         /* +1 */
            result -= 20;
            break;
        case -3:         /* +1 */
            result -= 30;
            break;
        default:         /* +1 */
            result = 0;
            break;
    }
    
    return result;
}

/* Expected Lizard output: CCN = 15 (1 base + 14 decision points) */
```

**File: `tests/tool-validation/lizard-validation/run-validation.sh`**

```bash
#!/bin/bash
# Lizard Validation Test Suite Runner

echo "=== Lizard Validation Test Suite ==="
echo "Tool: Lizard"
echo "Version: $(lizard --version)"
echo "Date: $(date)"
echo ""

# Test 1: Simple function (CCN = 1)
echo "Test 1: Simple function (expected CCN = 1)"
ACTUAL_CCN=$(lizard test-simple-function.c | grep simple_add | awk '{print $2}')
if [ "$ACTUAL_CCN" = "1" ]; then
    echo "  PASS: Lizard correctly calculated CCN = 1"
else
    echo "  FAIL: Lizard calculated CCN = $ACTUAL_CCN (expected 1)"
    exit 1
fi

# Test 2: Complex function (CCN = 15)
echo "Test 2: Complex function (expected CCN = 15)"
ACTUAL_CCN=$(lizard test-complex-function.c | grep complex_function | awk '{print $2}')
if [ "$ACTUAL_CCN" = "15" ]; then
    echo "  PASS: Lizard correctly calculated CCN = 15"
else
    echo "  FAIL: Lizard calculated CCN = $ACTUAL_CCN (expected 15)"
    exit 1
fi

echo ""
echo "=== All validation tests PASSED ==="
echo "Lizard is validated for use in this project."
```

### 6.5 T2 Tool Validation Report Template

See Section 8.2 for complete T2 Tool Validation Report template.

---

## 7. T3 Tools - Full Qualification Required

### 7.1 T3 Tool List

**T3 Tools Used in Project** (SIL 3 example):

| Tool | Purpose | Agent | Qualification Status |
|------|---------|-------|----------------------|
| **GCC 13.3.0** | C compiler | IMP, TST, INT | ✅ Qualified |
| **GNU ld 2.40** | Linker | IMP, TST, INT | ✅ Qualified |
| **GNU Make 4.3** | Build system | IMP, TST, INT | ✅ Qualified |

### 7.2 T3 Qualification Requirements by SIL

| SIL | Qualification Evidence | Supplier Data | Certification | Report |
|-----|------------------------|---------------|---------------|--------|
| **SIL 0** | Basic validation | Not required | Not required | No |
| **SIL 1-2** | Supplier qualification + validation | Required | Recommended | **MANDATORY** |
| **SIL 3-4** | Full qualification | Required | Highly Recommended | **MANDATORY** |

### 7.3 T3 Qualification Evidence

**Required Evidence for T3 Tools**:

1. **Supplier Qualification Data**:
   - Tool Qualification Report from vendor
   - Validation suite results (e.g., compiler validation suite)
   - Test coverage of tool functionality
   - Known issues and limitations

2. **Industry Certification** (highly recommended SIL 3-4):
   - TÜV certification for safety-critical tools
   - IEC 61508 certification
   - EN 50128 pre-qualified tool listing

3. **Project-Specific Validation**:
   - Validation tests for project's usage scenarios
   - Platform-specific validation (target hardware)
   - Compiler options validation (flags used in project)

4. **Tool Qualification Report**:
   - Comprehensive report documenting all evidence
   - MANDATORY for SIL 1-4

### 7.4 Example: GCC Qualification

**File: `docs/tool-qualification/GCC-Qualification-Report.md`**

```markdown
# GCC Qualification Report

**Document ID**: DOC-TQR-GCC-001  
**Version**: 1.0  
**Date**: 2026-03-14  
**Project**: Train Door Control System  
**SIL Level**: 3

## Document Control

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2026-03-14 | [Author] | Initial version |

## 1. Tool Identification

**Tool Name**: GCC (GNU Compiler Collection)  
**Tool Version**: 13.3.0  
**Tool Vendor**: Free Software Foundation  
**Tool Purpose**: C compiler for safety-critical software  
**Target Platform**: x86-64 Linux (Ubuntu 22.04)

## 2. Tool Classification

**Classification**: T3 - Full Qualification Required

**Justification**:
- GCC generates machine code from C source code
- Generated code is executed directly on target system
- Generated code is NOT independently verified (not manually reviewed)
- Compiler errors can directly result in software safety failures
- Therefore: T3 classification (full qualification required)

**QUA Review**: ✅ Approved by [Name] on 2026-03-14

## 3. Tool Specification

### 3.1 Tool Functionality

GCC compiles C source code to machine code:
- **Input**: C source files (.c, .h)
- **Output**: Object files (.o), executables (ELF)
- **Functionality**: Compilation, optimization, linking

### 3.2 Tool Usage in Project

**Agents Using Tool**: IMP, TST, INT

**Compilation Flags**:
```bash
gcc -std=c11 -Wall -Wextra -Werror -pedantic -O2 \
    -DSIL_LEVEL=3 -DMISRA_C_2012 \
    -fstack-protector-strong -D_FORTIFY_SOURCE=2 \
    -fno-common \
    -fno-builtin-malloc -fno-builtin-calloc \
    -o output source.c
```

**Usage Scenarios**:
1. Compile source files to object files
2. Link object files to executable
3. Generate assembly listings (for code review)
4. Generate preprocessor output (for verification)

### 3.3 Tool Constraints and Limitations

**Constraints**:
- **Version locked**: GCC 13.3.0 (no updates without re-qualification)
- **Platform**: x86-64 Linux only
- **Language**: C11 only (no C++, no GNU extensions)
- **Optimization**: -O2 only (not -O3, not -Os)

**Known Limitations**:
- GCC test suite: 99.8% pass rate (0.2% known failures)
- Known failures documented in GCC bug database
- None of the known failures affect safety-critical code patterns used in this project

## 4. Supplier Qualification Evidence

### 4.1 GCC Test Suite Results

**Source**: https://gcc.gnu.org/testresults/13.3.0/

**Test Statistics**:
- Total tests: 150,000+
- Passed: 149,700+ (99.8%)
- Failed: 300 (0.2%)
- Failures analyzed: None affect project code patterns

**Test Coverage**:
- C11 standard compliance: ✅ Comprehensive
- Code generation correctness: ✅ Comprehensive
- Optimization correctness: ✅ Comprehensive
- Platform-specific (x86-64): ✅ Comprehensive

### 4.2 Industry Usage

**Safety-Critical Projects Using GCC**:
- Automotive (ISO 26262): Multiple ASIL-D certified projects
- Aerospace (DO-178C): Multiple DAL-A certified projects
- Railway (EN 50128): Multiple SIL 4 certified projects

**Industry Acceptance**: GCC is widely accepted for safety-critical development when properly qualified.

### 4.3 MISRA C Support

**MISRA C:2012 Compliance**:
- GCC supports MISRA C checking with appropriate flags
- GCC warnings cover many MISRA C rules
- Additional MISRA C checking via Cppcheck (T2 tool)

**Documentation**: https://gcc.gnu.org/onlinedocs/gcc/C-Dialect-Options.html

## 5. Project-Specific Validation

### 5.1 Compiler Validation Tests

**Location**: `tests/tool-qualification/gcc-validation/`

**Tests Performed**:
1. **Integer Arithmetic**: Validate correct arithmetic code generation
2. **Pointer Arithmetic**: Validate correct pointer operations
3. **Function Calls**: Validate correct call/return sequences
4. **Optimization Correctness**: Validate optimizer doesn't break semantics
5. **Platform-Specific**: Validate x86-64 code generation
6. **Compiler Flags**: Validate that project flags produce correct code

**Test Results**: ✅ All tests PASSED (see validation-results.txt)

### 5.2 Assembly Code Review

**Method**: Generate assembly listings for critical functions, review manually

**Example**:
```bash
gcc -S -std=c11 -O2 critical_function.c -o critical_function.s
# Review critical_function.s for correctness
```

**Results**: Assembly code review performed for 10 critical functions. All correct.

### 5.3 Comparison Testing

**Method**: Compile same code with multiple compilers, compare results

**Compilers Used**:
- GCC 13.3.0
- Clang 18.0.0

**Results**: Both compilers produce functionally equivalent code (verified by testing).

## 6. Tool Qualification Conclusion

GCC 13.3.0 is **QUALIFIED** for use in this SIL 3 project:
- ✅ Comprehensive supplier qualification evidence (GCC test suite)
- ✅ Extensive industry usage in safety-critical domains
- ✅ Project-specific validation tests passed
- ✅ Assembly code review confirms correct code generation
- ✅ Comparison testing with Clang confirms correctness

**Tool Version**: GCC 13.3.0 (LOCKED for project, checksum: abc123...)

**Qualification Valid Until**: Tool update or re-qualification required

## 7. Tool Configuration Management

**Version Control**:
- Tool version recorded in Tool-Baseline.md
- Tool executable checksum: abc123def456...
- Tool version verified by CI/CD on every build

**Change Control**:
- Any GCC update requires Change Request (CR)
- CR must include re-qualification plan
- CCB approval required before tool update

## 8. Approvals

| Role | Name | Date | Signature |
|------|------|------|-----------|
| QUA | [Name] | 2026-03-14 | [Signature] |
| VER | [Name] | 2026-03-14 | [Signature] |
| PM | [Name] | 2026-03-14 | [Signature] |
```

---

## 8. Tool Qualification Report

### 8.1 T3 Tool Qualification Report Template

**File**: `.opencode/skills/en50128-tools/templates/Tool-Qualification-Report-template.md`

```markdown
# [Tool Name] Qualification Report

**Document ID**: DOC-TQR-[TOOL]-[NNN]  
**Version**: X.Y  
**Date**: YYYY-MM-DD  
**Project**: [Project Name]  
**SIL Level**: [0/1/2/3/4]

---

## Document Control

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | YYYY-MM-DD | [Author] | Initial version |

---

## 1. Tool Identification

**Tool Name**: [Full tool name]  
**Tool Version**: [Exact version number]  
**Tool Vendor**: [Vendor name]  
**Tool Purpose**: [What does the tool do?]  
**Target Platform**: [Platform on which tool runs]

---

## 2. Tool Classification

**Classification**: [T1 / T2 / T3]

**Justification**:
[Explain why tool has this classification]
- [What is the tool output?]
- [How is the output used?]
- [Is the output verified?]
- [What is the impact of tool errors?]

**QUA Review**: [✅ Approved / ❌ Rejected] by [Name] on [Date]

---

## 3. Tool Specification

### 3.1 Tool Functionality

[Describe what the tool does]

**Input**: [What inputs does the tool accept?]  
**Output**: [What outputs does the tool produce?]  
**Functionality**: [Key features used in project]

### 3.2 Tool Usage in Project

**Agents Using Tool**: [List agent roles]

**Usage Commands**:
```bash
[Example commands used in project]
```

**Usage Scenarios**:
[List specific ways tool is used]

### 3.3 Tool Constraints and Limitations

**Constraints**:
[List any constraints on tool usage]
- [Version constraints]
- [Platform constraints]
- [Usage constraints]

**Known Limitations**:
[List known tool limitations]
- [Known bugs]
- [Test failures]
- [Feature gaps]

---

## 4. Qualification Evidence (T3 only)

### 4.1 Supplier Qualification Evidence

[Describe supplier-provided qualification evidence]
- [Validation suite results]
- [Certification documents]
- [Industry usage]

### 4.2 Industry Certification (if applicable)

[List any industry certifications]
- [TÜV certification]
- [IEC 61508 certification]
- [etc.]

### 4.3 Industry Usage

[Describe tool usage in similar safety-critical projects]

---

## 5. Validation Evidence (T2) / Project-Specific Validation (T3)

### 5.1 Validation Test Suite

**Location**: [Path to validation tests]

**Tests Performed**:
[List validation tests]

**Test Results**: [✅ PASSED / ❌ FAILED]

### 5.2 Validation Conclusion

[Summarize validation results]
- [Tool correctly performs intended function]
- [Tool produces no false positives/negatives]
- [Tool is suitable for project use]

---

## 6. Tool Qualification Conclusion

[Tool Name] [Tool Version] is **[QUALIFIED / NOT QUALIFIED]** for use in this [SIL X] project:
- [✅ / ❌] [Evidence item 1]
- [✅ / ❌] [Evidence item 2]
- [✅ / ❌] [Evidence item 3]

**Tool Version**: [Version] (LOCKED for project, checksum: [...])

**Qualification Valid Until**: [Date or condition for re-qualification]

---

## 7. Tool Configuration Management

**Version Control**:
- Tool version recorded in Tool-Baseline.md
- Tool executable checksum: [checksum]
- Tool version verified by [method]

**Change Control**:
- Tool updates require Change Request (CR)
- CR must include re-qualification plan
- CCB approval required

---

## 8. Approvals

| Role | Name | Date | Signature |
|------|------|------|-----------|
| QUA | [Name] | YYYY-MM-DD | [Signature] |
| VER | [Name] | YYYY-MM-DD | [Signature] |
| PM | [Name] | YYYY-MM-DD | [Signature] |

---

## Appendices

### Appendix A: Validation Test Results

[Attach or link to validation test results]

### Appendix B: Supplier Documentation

[Attach or link to supplier-provided documentation]

### Appendix C: Tool Configuration Files

[Attach or link to tool configuration files used in project]
```

### 8.2 T2 Tool Validation Report Template

**File**: `.opencode/skills/en50128-tools/templates/Tool-Validation-Report-template.md`

```markdown
# [Tool Name] Validation Report

**Document ID**: DOC-TVR-[TOOL]-[NNN]  
**Version**: X.Y  
**Date**: YYYY-MM-DD  
**Project**: [Project Name]  
**SIL Level**: [0/1/2/3/4]

---

## Document Control

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | YYYY-MM-DD | [Author] | Initial version |

---

## 1. Tool Identification

**Tool Name**: [Full tool name]  
**Tool Version**: [Exact version number]  
**Classification**: T2 (Validation Required)  
**Tool Purpose**: [What does the tool do?]

---

## 2. Tool Classification

**Classification**: T2 - Validation Required

**Justification**:
[Explain why tool is T2]
- [Tool output is used directly]
- [Tool output is verified by other means]
- [Impact of tool errors is likely to be detected]

**QUA Review**: ✅ Approved by [Name] on [Date]

---

## 3. Validation Test Suite

**Location**: [Path to validation tests]

**Tests Performed**:
[List validation tests with expected results]

| Test # | Test Description | Expected Result | Actual Result | Status |
|--------|------------------|-----------------|---------------|--------|
| 1 | [Test 1] | [Expected] | [Actual] | ✅ PASS |
| 2 | [Test 2] | [Expected] | [Actual] | ✅ PASS |
| ... | ... | ... | ... | ... |

---

## 4. Validation Results

**Test Execution Date**: YYYY-MM-DD  
**Test Executor**: [Name]

**Results Summary**:
```
[Paste validation test suite output]
```

**Results Analysis**:
- Total tests: [N]
- Passed: [N]
- Failed: [N]
- Pass rate: [N]%

---

## 5. Validation Conclusion

[Tool Name] [Tool Version] has been **VALIDATED** for use in this [SIL X] project:
- ✅ All validation tests passed
- ✅ Tool correctly detects [defects/issues/metrics]
- ✅ Tool produces no false positives on clean code
- ✅ Tool is suitable for use in [purpose]

---

## 6. Tool Usage Constraints

[List any constraints on tool usage]
- Use with flags: [flags]
- All findings MUST be reviewed manually
- Tool is T2: findings verified by [verification method]

---

## 7. Approvals

| Role | Name | Date | Signature |
|------|------|------|-----------|
| QUA | [Name] | YYYY-MM-DD | [Signature] |
| VER | [Name] | YYYY-MM-DD | [Signature] |
| PM | [Name] | YYYY-MM-DD | [Signature] |
```

---

## 9. Tool Validation Automation

### 9.1 Automated Validation Test Runner

Create a comprehensive automated tool validation runner:

**File**: `tools/tool-validation/run-all-validations.sh`

```bash
#!/bin/bash
# Automated Tool Validation Test Runner
# Runs validation tests for all T2 tools

set -e

echo "======================================"
echo "EN 50128 Tool Validation Test Suite"
echo "======================================"
echo "Date: $(date)"
echo "SIL Level: 3"
echo ""

FAILED_TOOLS=()

# Function to run validation for a tool
run_validation() {
    local tool_name=$1
    local validation_dir=$2
    
    echo "--------------------------------------"
    echo "Validating: $tool_name"
    echo "--------------------------------------"
    
    cd "$validation_dir"
    if ./run-validation.sh > validation-results.txt 2>&1; then
        echo "✅ $tool_name validation PASSED"
        cd - > /dev/null
        return 0
    else
        echo "❌ $tool_name validation FAILED"
        cat validation-results.txt
        FAILED_TOOLS+=("$tool_name")
        cd - > /dev/null
        return 1
    fi
}

# Run validation for each T2 tool
run_validation "Cppcheck" "tests/tool-validation/cppcheck-validation" || true
run_validation "Lizard" "tests/tool-validation/lizard-validation" || true
run_validation "gcov" "tests/tool-validation/gcov-validation" || true

echo ""
echo "======================================"
echo "Validation Summary"
echo "======================================"

if [ ${#FAILED_TOOLS[@]} -eq 0 ]; then
    echo "✅ ALL TOOL VALIDATIONS PASSED"
    echo "All T2 tools are validated for use in this project."
    exit 0
else
    echo "❌ TOOL VALIDATION FAILURES:"
    for tool in "${FAILED_TOOLS[@]}"; do
        echo "  - $tool"
    done
    echo ""
    echo "ACTION REQUIRED: Fix failed tool validations before proceeding."
    exit 1
fi
```

### 9.2 CI/CD Integration

Integrate tool validation into CI/CD pipeline:

**File**: `.github/workflows/tool-validation.yml`

```yaml
name: Tool Validation

on:
  # Run on every push to ensure tools remain validated
  push:
    branches: [ main, develop ]
  # Run weekly to catch tool regressions
  schedule:
    - cron: '0 0 * * 0'  # Every Sunday at midnight

jobs:
  validate-tools:
    runs-on: ubuntu-latest
    
    steps:
      - uses: actions/checkout@v3
      
      - name: Install tools
        run: |
          sudo apt-get update
          sudo apt-get install -y gcc cppcheck lcov
          pip3 install lizard
      
      - name: Run tool validation suite
        run: |
          chmod +x tools/tool-validation/run-all-validations.sh
          ./tools/tool-validation/run-all-validations.sh
      
      - name: Upload validation results
        if: always()
        uses: actions/upload-artifact@v3
        with:
          name: tool-validation-results
          path: tests/tool-validation/*/validation-results.txt
      
      - name: Check tool versions match baseline
        run: |
          # Verify tool versions haven't changed unexpectedly
          source tools/tool-validation/check-tool-versions.sh
```

### 9.3 Tool Version Check Script

**File**: `tools/tool-validation/check-tool-versions.sh`

```bash
#!/bin/bash
# Check that installed tool versions match baseline

BASELINE_FILE="docs/tool-qualification/Tool-Baseline.md"

check_tool_version() {
    local tool_name=$1
    local expected_version=$2
    local version_command=$3
    
    actual_version=$($version_command)
    
    if [[ "$actual_version" == *"$expected_version"* ]]; then
        echo "✅ $tool_name: $expected_version (correct)"
        return 0
    else
        echo "❌ $tool_name: Expected $expected_version, got $actual_version"
        return 1
    fi
}

echo "Checking tool versions against baseline..."
echo ""

FAILED=0

check_tool_version "GCC" "13.3.0" "gcc --version | head -n1" || FAILED=1
check_tool_version "Cppcheck" "2.13.0" "cppcheck --version" || FAILED=1
check_tool_version "Lizard" "1.17" "lizard --version" || FAILED=1

echo ""

if [ $FAILED -eq 0 ]; then
    echo "✅ All tool versions match baseline"
    exit 0
else
    echo "❌ Tool version mismatch detected"
    echo "ACTION REQUIRED: Tool versions must match baseline for SIL 3 project"
    exit 1
fi
```

---

## 10. Complete Example Scenarios

### 10.1 Example 1: Cppcheck Validation (T2) for SIL 3 Project

**Scenario**: Validate Cppcheck 2.13.0 for use as static analyzer in SIL 3 Train Door Control project.

**Step-by-Step Process**:

**Step 1: Classify Tool**

Create `docs/tool-qualification/Cppcheck-Classification.md`:

```markdown
## Tool: Cppcheck

**Classification**: T2 - Validation Required

**Justification**:
- **Purpose**: Static analysis of C code to detect defects
- **Output**: List of potential defects (NULL dereferences, buffer overflows, etc.)
- **Usage**: All Cppcheck findings are reviewed manually by VER agent
- **Verification**: 
  - Findings verified by manual code review
  - Findings cross-checked with Clang Static Analyzer
  - False positives dismissed during review
  - False negatives (missed errors) caught by code review + testing
- **Impact of tool error**:
  - False negative (missed defect): Detected by code review or testing
  - False positive (spurious finding): Dismissed during manual review
- **Conclusion**: Tool errors are likely to be detected through verification process
  → T2 classification (validation required)

**QUA Review**: ✅ Approved by Jane Smith on 2026-03-14
```

**Step 2: Create Validation Test Suite**

Create `tests/tool-validation/cppcheck-validation/`:

```bash
mkdir -p tests/tool-validation/cppcheck-validation
cd tests/tool-validation/cppcheck-validation
```

Create test files (see Section 6.4 for complete examples):
- `test-null-pointer.c` - Test NULL pointer detection
- `test-buffer-overflow.c` - Test buffer overflow detection
- `test-uninitialized-variable.c` - Test uninitialized variable detection
- `test-clean-code.c` - Test no false positives

Create `run-validation.sh` (see Section 6.4 for complete script).

**Step 3: Execute Validation**

```bash
chmod +x run-validation.sh
./run-validation.sh > validation-results.txt 2>&1
cat validation-results.txt
```

**Expected Output**:
```
=== Cppcheck Validation Test Suite ===
Tool: Cppcheck
Version: Cppcheck 2.13.0

Test 1: NULL pointer dereference detection
  PASS: Cppcheck detected NULL pointer dereference
Test 2: Buffer overflow detection
  PASS: Cppcheck detected buffer overflow
Test 3: Uninitialized variable detection
  PASS: Cppcheck detected uninitialized variable
Test 4: No false positives on clean code
  PASS: Cppcheck produced no false positives

=== All validation tests PASSED ===
```

**Step 4: Create Tool Validation Report**

Create `docs/tool-qualification/Cppcheck-Validation-Report.md` (see Section 8.2 template).

**Step 5: Submit for QUA Review**

```bash
python3 tools/workspace.py wf submit \
  --document "docs/tool-qualification/Cppcheck-Validation-Report.md" \
  --type "TOOL-VALIDATION" \
  --version "1.0" \
  --approver "QUA" \
  --sil 3
```

**Step 6: Obtain Approvals**

For SIL 3, approvals required: QUA, VER, PM

```bash
# QUA approval
python3 tools/workspace.py wf approve --workflow-id "WF-2026-040" --approver "QUA" --decision "APPROVE"

# VER approval
python3 tools/workspace.py wf approve --workflow-id "WF-2026-040" --approver "VER" --decision "APPROVE"

# PM approval
python3 tools/workspace.py wf approve --workflow-id "WF-2026-040" --approver "PM" --decision "APPROVE"
```

**Step 7: Baseline Tool Version**

```bash
# Record tool version and checksum
cppcheck --version > docs/tool-qualification/cppcheck-version.txt
sha256sum $(which cppcheck) > docs/tool-qualification/cppcheck-checksum.txt

# Update Tool-Baseline.md
# (Add Cppcheck entry with version and checksum)

# Commit to version control
git add docs/tool-qualification/
git commit -m "Add Cppcheck validation evidence (SIL 3)"
git tag -a cppcheck-validated-v2.13.0 -m "Cppcheck 2.13.0 validated"
```

**Step 8: Configure CI/CD**

Add Cppcheck version check to `.github/workflows/tool-version-check.yml`:

```yaml
- name: Check Cppcheck version
  run: |
    EXPECTED="Cppcheck 2.13.0"
    ACTUAL=$(cppcheck --version)
    if [ "$ACTUAL" != "$EXPECTED" ]; then
      echo "ERROR: Cppcheck version mismatch"
      exit 1
    fi
```

**Result**: Cppcheck 2.13.0 is now validated and ready for use in SIL 3 project.

### 10.2 Example 2: GCC Qualification (T3) for SIL 3 Project

**Scenario**: Qualify GCC 13.3.0 for use as C compiler in SIL 3 Train Door Control project.

**Step-by-Step Process**:

**Step 1: Classify Tool**

Create `docs/tool-qualification/GCC-Classification.md`:

```markdown
## Tool: GCC (GNU Compiler Collection)

**Classification**: T3 - Full Qualification Required

**Justification**:
- **Purpose**: Compile C source code to machine code
- **Output**: Object files (.o), executables (ELF binaries)
- **Usage**: Generated code runs directly on target system
- **Verification**: Generated code is NOT independently verified:
  - Code is not manually reviewed at assembly level (impractical)
  - Code is not verified by another independent compiler
  - Code correctness depends entirely on GCC correctness
- **Impact of tool error**:
  - Incorrect code generation → software safety failure
  - Compiler bug → undetected software defect
  - Optimizer error → incorrect runtime behavior
- **Conclusion**: Tool errors directly affect software safety, no independent verification
  → T3 classification (full qualification required)

**QUA Review**: ✅ Approved by Jane Smith on 2026-03-14
```

**Step 2: Obtain Supplier Qualification Evidence**

Gather GCC qualification evidence:

```bash
# Download GCC test results
wget https://gcc.gnu.org/testresults/13.3.0/gcc-testresults-13.3.0.html -O docs/tool-qualification/gcc-testresults.html

# Document supplier evidence
cat > docs/tool-qualification/GCC-Supplier-Evidence.md <<EOF
# GCC Supplier Qualification Evidence

## GCC Test Suite Results

**Source**: https://gcc.gnu.org/testresults/13.3.0/

**Statistics**:
- Total tests: 150,000+
- Pass rate: 99.8%
- Known failures: 300 (documented, none affect project)

## Industry Usage

GCC is used in multiple safety-certified projects:
- Automotive (ISO 26262 ASIL-D)
- Aerospace (DO-178C DAL-A)
- Railway (EN 50128 SIL 4)

## MISRA C Support

GCC supports MISRA C:2012 with appropriate compiler flags and external checkers.

**Documentation**: https://gcc.gnu.org/onlinedocs/gcc/
EOF
```

**Step 3: Perform Project-Specific Validation**

Create `tests/tool-qualification/gcc-validation/test-compiler.c` (see Section 7.4 for complete code).

```bash
mkdir -p tests/tool-qualification/gcc-validation
cd tests/tool-qualification/gcc-validation

# Compile test with SIL 3 flags
gcc -std=c11 -Wall -Wextra -Werror -pedantic -O2 \
    -DSIL_LEVEL=3 -DMISRA_C_2012 \
    -fstack-protector-strong -D_FORTIFY_SOURCE=2 \
    -o test-compiler test-compiler.c

# Run validation
./test-compiler
# Expected output: "All GCC validation tests PASSED"
```

**Step 4: Assembly Code Review**

Review generated assembly for critical functions:

```bash
# Generate assembly listing
gcc -S -std=c11 -O2 -fverbose-asm \
    ../../../src/safety/emergency_stop.c \
    -o emergency_stop.s

# Review assembly manually
# Verify:
# - Correct function prologue/epilogue
# - Correct stack frame setup
# - Correct parameter passing
# - No unexpected optimizations
# - Correct return sequence
```

**Step 5: Comparison Testing**

Compile same code with Clang, compare results:

```bash
# Compile with GCC
gcc -std=c11 -O2 -o test-gcc test-program.c

# Compile with Clang
clang -std=c11 -O2 -o test-clang test-program.c

# Run both, compare outputs
./test-gcc > output-gcc.txt
./test-clang > output-clang.txt

# Compare
diff output-gcc.txt output-clang.txt
# Expected: No differences (functionally equivalent)
```

**Step 6: Create Tool Qualification Report**

Create `docs/tool-qualification/GCC-Qualification-Report.md` (see Section 7.4 for complete example).

**Step 7: Submit for Review and Approval**

```bash
python3 tools/workspace.py wf submit \
  --document "docs/tool-qualification/GCC-Qualification-Report.md" \
  --type "TOOL-QUALIFICATION" \
  --version "1.0" \
  --approver "QUA" \
  --sil 3
```

Obtain approvals: QUA → VER → PM (all required for SIL 3).

**Step 8: Lock Tool Version**

```bash
# Record exact version
gcc --version > docs/tool-qualification/gcc-version.txt

# Compute checksum
sha256sum $(which gcc) > docs/tool-qualification/gcc-checksum.txt

# Update Tool-Baseline.md
# (Add GCC 13.3.0 entry with checksum)

# Commit and tag
git add docs/tool-qualification/
git commit -m "Add GCC 13.3.0 qualification evidence (SIL 3)"
git tag -a gcc-qualified-v13.3.0 -m "GCC 13.3.0 qualified for SIL 3"
```

**Step 9: Configure CI/CD Tool Version Lock**

```yaml
# .github/workflows/tool-version-check.yml
- name: Check GCC version (LOCKED for SIL 3)
  run: |
    EXPECTED_VERSION="13.3.0"
    ACTUAL_VERSION=$(gcc -dumpversion)
    if [ "$ACTUAL_VERSION" != "$EXPECTED_VERSION" ]; then
      echo "ERROR: GCC version mismatch!"
      echo "Expected: $EXPECTED_VERSION (qualified)"
      echo "Actual: $ACTUAL_VERSION"
      echo "GCC version is LOCKED for this SIL 3 project."
      echo "Any GCC update requires re-qualification (CR required)."
      exit 1
    fi
    echo "✅ GCC version correct: $EXPECTED_VERSION"
```

**Result**: GCC 13.3.0 is now fully qualified and locked for use in SIL 3 project. Any GCC update will trigger CI/CD failure and require formal change request + re-qualification.

---

## 11. Tool Integration

### 11.1 Integration with workspace.py

Tool qualification documents are managed through workspace.py workflows:

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
  --decision "APPROVE" \
  --comment "GCC qualification evidence complete and acceptable"

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

### 11.2 Integration with Configuration Management

Tool versions are baselined using configuration management:

```bash
# Baseline tool versions
python3 tools/workspace.py wf baseline \
  --name "Tool-Baseline-v1.0" \
  --documents "docs/tool-qualification/Tool-Baseline.md" \
  --sil 3

# Record baseline in Git
git tag -a tool-baseline-v1.0 -m "Tool baseline version 1.0 (SIL 3)"
```

### 11.3 Tool Usage in Agent Workflows

Agents reference Tool Qualification Reports when using tools:

**Example: VER agent using Cppcheck**

```bash
# VER agent: Run static analysis with qualified tool
# Reference: Tool Validation Report DOC-TVR-CPPCHECK-001

# Verify tool version matches baseline
EXPECTED="Cppcheck 2.13.0"
ACTUAL=$(cppcheck --version)
if [ "$ACTUAL" != "$EXPECTED" ]; then
    echo "ERROR: Cppcheck version mismatch (expected $EXPECTED, got $ACTUAL)"
    exit 1
fi

# Run Cppcheck with qualified flags (per Tool Validation Report)
cppcheck --enable=all --xml --xml-version=2 \
    --suppress=missingInclude \
    src/ 2> verification/cppcheck-report.xml

# Document tool usage in Verification Report
echo "Static analysis performed with Cppcheck 2.13.0 (qualified per DOC-TVR-CPPCHECK-001)"
```

---

## 12. References

### 12.1 EN 50128 Standard References

- **EN 50128:2011 Section 6.7**: Software tools and their validation
- **EN 50128:2011 Section 6.7.4**: Tool classification (T1/T2/T3)
- **EN 50128:2011 Section 6.7.4.2**: T1 tools (no qualification)
- **EN 50128:2011 Section 6.7.4.3**: T2 tools (validation required)
- **EN 50128:2011 Section 6.7.4.4**: T3 tools (full qualification required)
- **EN 50128:2011 Section 6.7.4.5**: Tool qualification process

### 12.2 Project References

- **TOOLS.md**: Comprehensive tool catalog
- **Tool-Baseline.md**: Baselined tool versions
- **SQAP**: Software Quality Assurance Plan (tool quality requirements)
- **SVP**: Software Verification Plan (verification tool requirements)

### 12.3 External References

- **GCC Documentation**: https://gcc.gnu.org/onlinedocs/
- **GCC Test Results**: https://gcc.gnu.org/testresults/
- **Cppcheck Manual**: https://cppcheck.sourceforge.io/manual.pdf
- **Lizard Documentation**: https://github.com/terryyin/lizard

---

**END OF WORKFLOW**
