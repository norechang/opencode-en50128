# Static Analysis Workflow for EN 50128

**Purpose**: Step-by-step workflow for executing static analysis on C source code compliant with EN 50128 Table A.19.

**Scope**: Source code verification phase - static analysis execution, defect detection, and reporting.

**Audience**: Verifiers (VER), Implementers (IMP), Quality Assurance (QUA)

**EN 50128 Reference**: 
- Section 6.2 "Software Verification"
- Section 7.5.4.10 "Software Source Code Verification"
- Table A.5, Technique 3 "Static Analysis" (**MANDATORY** SIL 3-4)
- Table A.19 "Static Analysis Techniques" (Control Flow, Data Flow **MANDATORY** SIL 3-4)

**Related Documents**:
- `workflows/verification-planning.md` - Static analysis strategy definition
- `resources/static-analysis-guidelines.md` - Tool configuration and thresholds
- `resources/verification-tools-reference.md` - Tool catalog
- `resources/common-verification-defects.md` - Defect patterns and fixes

---

## Table of Contents

1. [Workflow Overview](#1-workflow-overview)
2. [Prerequisites and Setup](#2-prerequisites-and-setup)
3. [Step 1: Prepare Source Code for Analysis](#step-1-prepare-source-code-for-analysis)
4. [Step 2: Run Cppcheck (General Static Analysis)](#step-2-run-cppcheck-general-static-analysis)
5. [Step 3: Run PC-lint Plus (MISRA C Compliance)](#step-3-run-pc-lint-plus-misra-c-compliance)
6. [Step 4: Run Clang Static Analyzer (Deep Analysis)](#step-4-run-clang-static-analyzer-deep-analysis)
7. [Step 5: Run Complexity Analysis (Lizard)](#step-5-run-complexity-analysis-lizard)
8. [Step 6: Analyze and Triage Results](#step-6-analyze-and-triage-results)
9. [Step 7: Document Findings](#step-7-document-findings)
10. [Step 8: Track Remediation](#step-8-track-remediation)
11. [Step 9: Generate Static Analysis Report](#step-9-generate-static-analysis-report)
12. [Continuous Integration Setup](#continuous-integration-setup)
13. [Tool-Specific Configurations](#tool-specific-configurations)

---

## 1. Workflow Overview

### Purpose of Static Analysis

Static analysis provides:
- **Control Flow Analysis**: Detect unreachable code, infinite loops, missing returns
- **Data Flow Analysis**: Detect uninitialized variables, unused variables, use-after-free
- **MISRA C Compliance**: Verify adherence to MISRA C:2012 coding standard
- **Semantic Analysis**: Detect logical errors, API misuse, type violations
- **Complexity Metrics**: Measure cyclomatic complexity (SIL 4: CCN ≤ 10)

### EN 50128 Requirements

| Technique | EN 50128 Ref | SIL 0 | SIL 1-2 | SIL 3-4 | Tools |
|-----------|--------------|-------|---------|---------|-------|
| **Static Analysis** | Table A.5 #3 | - | HR | **M** | Cppcheck, PC-lint, Clang |
| **Control Flow Analysis** | Table A.19 #2 | R | HR | **M** | Cppcheck, Clang |
| **Data Flow Analysis** | Table A.19 #3 | R | HR | **M** | Cppcheck, Clang |
| **Complexity Metrics** | Table A.19 #8 | R | HR | HR | Lizard |

### Workflow Phases

```
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 1: PREPARE SOURCE CODE                                    │
│ - Ensure code compiles cleanly                                  │
│ - Organize source files for analysis                            │
│ - Configure tool settings                                       │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 2: RUN CPPCHECK (General Static Analysis)                 │
│ - Control flow, data flow, style, performance                   │
│ - MISRA addon for basic MISRA C checking                        │
│ - Generate XML report                                            │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 3: RUN PC-LINT PLUS (MISRA C Compliance)                  │
│ - Comprehensive MISRA C:2012 checking                           │
│ - All 178 rules + 16 directives                                 │
│ - Generate detailed compliance report                           │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 4: RUN CLANG STATIC ANALYZER (Deep Analysis)              │
│ - Path-sensitive analysis                                       │
│ - Memory safety (NULL deref, use-after-free)                    │
│ - Security issues                                                │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 5: RUN LIZARD (Complexity Analysis)                       │
│ - Cyclomatic Complexity (CCN)                                   │
│ - Function length, parameter count                              │
│ - Threshold: CCN ≤ 10 (SIL 4)                                   │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 6: ANALYZE AND TRIAGE RESULTS                             │
│ - Review all findings                                            │
│ - Classify severity (Critical, High, Medium, Low)               │
│ - Identify false positives                                       │
│ - Create defect tickets                                          │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 7: DOCUMENT FINDINGS                                      │
│ - Static Analysis Findings Log                                  │
│ - Defect tracking system entries                                │
│ - False positive justifications                                 │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 8: TRACK REMEDIATION                                      │
│ - Developer fixes defects                                        │
│ - Verifier re-runs analysis                                      │
│ - Verify fix effectiveness                                       │
└─────────────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────────────┐
│ PHASE 9: GENERATE STATIC ANALYSIS REPORT                        │
│ - Summary of findings                                            │
│ - Tool versions and configurations                              │
│ - Pass/fail determination                                        │
│ - Approvals (VER → VMGR)                                        │
└─────────────────────────────────────────────────────────────────┘
```

### SIL-Dependent Requirements

| Aspect | SIL 0-1 | SIL 2 | SIL 3-4 |
|--------|---------|-------|---------|
| **Static Analysis** | Recommended | Highly Recommended | **MANDATORY** |
| **MISRA C Mandatory Rules** | Best effort | Zero violations | **Zero violations** |
| **Complexity Limit** | CCN ≤ 20 | CCN ≤ 15 | **CCN ≤ 10** |
| **Critical Issues** | Address major | Zero | **Zero** |
| **Tool Qualification** | Basic | Formal | **Formal with evidence** |
| **Independent Review** | Optional | Recommended | **MANDATORY** |

---

## 2. Prerequisites and Setup

### Required Tools

```bash
# Check tool availability
which cppcheck && cppcheck --version
which pclp64 && pclp64 --version  # PC-lint Plus
which clang && clang --version
which scan-build && scan-build --version
which lizard && lizard --version

# Expected versions (minimum):
# Cppcheck 2.13.0+
# PC-lint Plus 2.0+
# Clang 18.x+
# Lizard 1.17+
```

### Install Missing Tools

```bash
# Install Cppcheck
sudo apt-get install cppcheck

# Install Clang and scan-build
sudo apt-get install clang clang-tools

# Install Lizard (Python)
pip3 install lizard

# PC-lint Plus: Commercial license required
# Download from: https://pclintplus.com/
# License file: pclint.lic
```

### Project Structure

```
project/
├── src/                    # Source code
│   ├── module1.c
│   ├── module2.c
│   └── ...
├── include/                # Header files
│   ├── module1.h
│   ├── module2.h
│   └── ...
├── tools/
│   └── config/
│       ├── cppcheck-project.xml
│       ├── pclint.lnt
│       ├── clang-analyzer-config.yaml
│       └── lizard-config.yaml
├── reports/                # Analysis reports
│   ├── cppcheck/
│   ├── pclint/
│   ├── clang/
│   └── complexity/
└── docs/
    └── static-analysis/    # Static Analysis Reports
```

---

## Step 1: Prepare Source Code for Analysis

### 1.1 Ensure Clean Build

**Purpose**: Verify code compiles without errors before static analysis.

```bash
# Clean build
make clean
make all

# Expected: Zero compilation errors
# Warnings are OK (will be analyzed by static tools)
```

**If build fails**: Fix compilation errors first. Static analysis requires syntactically correct code.

### 1.2 Organize Source Files

```bash
# List all source files to be analyzed
find src/ -name "*.c" > src_files.txt
find include/ -name "*.h" > header_files.txt

# Count files
wc -l src_files.txt header_files.txt

# Example output:
#   25 src_files.txt
#   30 header_files.txt
#   55 total
```

### 1.3 Configure Tool Settings

**Create Cppcheck project file** (`tools/config/cppcheck-project.xml`):

```xml
<?xml version="1.0" encoding="UTF-8"?>
<project>
    <paths>
        <dir name="src"/>
        <dir name="include"/>
    </paths>
    <exclude>
        <path name="test/"/>
        <path name="build/"/>
    </exclude>
    <libraries>
        <library>std</library>
        <library>posix</library>
    </libraries>
    <defines>
        <define name="TARGET_PLATFORM=RAILWAY"/>
        <define name="SIL_LEVEL=4"/>
        <define name="EMBEDDED_TARGET"/>
    </defines>
    <includes>
        <dir name="include/"/>
    </includes>
</project>
```

**Create PC-lint configuration** (`tools/config/pclint.lnt`):

```
// PC-lint Plus Configuration for EN 50128 SIL 4

// MISRA C:2012 compliance
+libclass(angle, foreign)
-strong(AJX)
+fll
-width(120)

// Enable all MISRA C:2012 rules
au-misra3.lnt

// SIL 4 specific settings
// Complexity limit: 10
-function_complexity(10)

// Enable control flow analysis
+fce

// Enable data flow analysis
+fda

// Include paths
-i"include/"
-i"/usr/include"

// Suppress system header warnings
-wlib(1)

// Project-specific suppressions (with justification)
// None yet - add as needed with CCB approval
```

**Create Clang analyzer configuration** (`tools/config/clang-analyzer-config.yaml`):

```yaml
# Clang Static Analyzer Configuration
Checks: >
  core.*,
  deadcode.*,
  security.*,
  unix.*,
  nullability.*

AnalyzerOptions:
  - key: aggressive-binary-operation-simplification
    value: true
  - key: track-conditions
    value: true
  - key: inline-max-stack-depth
    value: 5
```

---

## Step 2: Run Cppcheck (General Static Analysis)

### 2.1 Execute Cppcheck

**Command** (full analysis):

```bash
# Run Cppcheck with all checks enabled
cppcheck \
    --enable=all \
    --addon=misra \
    --inline-suppr \
    --suppress=missingIncludeSystem \
    --suppress=unusedFunction \
    --template='{file}:{line}:{column}: {severity}: {message} [{id}]' \
    --xml \
    --xml-version=2 \
    --project=tools/config/cppcheck-project.xml \
    src/ 2> reports/cppcheck/cppcheck_report.xml

# Check exit code
if [ $? -eq 0 ]; then
    echo "✓ Cppcheck completed successfully"
else
    echo "✗ Cppcheck found issues"
fi
```

**Explanation of flags**:
- `--enable=all`: Enable all checks (warning, style, performance, portability, information)
- `--addon=misra`: Load MISRA C addon (basic MISRA checking)
- `--inline-suppr`: Allow inline suppressions in code
- `--suppress=missingIncludeSystem`: Ignore missing system headers
- `--suppress=unusedFunction`: Suppress unused function warnings (common in modular code)
- `--xml --xml-version=2`: Generate machine-readable XML report

### 2.2 Generate HTML Report

```bash
# Convert XML to HTML for human review
cppcheck-htmlreport \
    --file=reports/cppcheck/cppcheck_report.xml \
    --report-dir=reports/cppcheck/html \
    --source-dir=.

# Open report in browser
xdg-open reports/cppcheck/html/index.html
```

### 2.3 Extract Key Findings

```bash
# Count issues by severity
python3 << 'EOF'
import xml.etree.ElementTree as ET

tree = ET.parse('reports/cppcheck/cppcheck_report.xml')
root = tree.getroot()

severities = {}
for error in root.findall('.//error'):
    sev = error.get('severity', 'unknown')
    severities[sev] = severities.get(sev, 0) + 1

print("Cppcheck Results:")
for sev, count in sorted(severities.items(), key=lambda x: x[1], reverse=True):
    print(f"  {sev}: {count}")
EOF

# Expected output:
# Cppcheck Results:
#   style: 15
#   performance: 8
#   warning: 3
#   error: 0  # <-- MUST be zero for SIL 3-4
```

### 2.4 Review Critical Issues

**Critical severity**: `error`

```bash
# Extract all error-severity issues
grep 'severity="error"' reports/cppcheck/cppcheck_report.xml | \
    sed 's/.*msg="\([^"]*\)".*/\1/' | \
    sort | uniq -c

# SIL 3-4 Requirement: Zero errors
```

**Example critical issues**:
- Null pointer dereference
- Array out of bounds
- Memory leak
- Use after free
- Division by zero
- Uninitialized variable use

**Action**: All critical issues MUST be fixed before proceeding (SIL 2+).

---

## Step 3: Run PC-lint Plus (MISRA C Compliance)

### 3.1 Execute PC-lint Plus

**Command** (full MISRA C:2012 analysis):

```bash
# Run PC-lint Plus with MISRA C:2012
pclp64 \
    -i"include/" \
    --misra3 \
    +ffn \
    -b \
    tools/config/pclint.lnt \
    src/*.c \
    > reports/pclint/pclint_report.txt 2>&1

# Check exit code
if [ $? -eq 0 ]; then
    echo "✓ PC-lint Plus completed (no mandatory violations)"
else
    echo "✗ PC-lint Plus found MISRA C violations"
fi
```

**Explanation of flags**:
- `-i"include/"`: Add include path
- `--misra3`: Enable MISRA C:2012 checking
- `+ffn`: Print full file names
- `-b`: Brief output format
- `tools/config/pclint.lnt`: Load project configuration

### 3.2 Generate HTML Report

```bash
# Convert to HTML (if PC-lint supports, or use custom script)
pclp64 \
    --misra3 \
    --html=reports/pclint/pclint_report.html \
    tools/config/pclint.lnt \
    src/*.c

# Open report
xdg-open reports/pclint/pclint_report.html
```

### 3.3 Extract MISRA C Violations

**Count violations by rule category**:

```bash
# Count MISRA C violations
grep "Rule" reports/pclint/pclint_report.txt | \
    awk '{print $2}' | \
    sort | uniq -c | \
    sort -rn

# Example output:
#   15 Rule-8.7   (functions should be static)
#   10 Rule-10.1  (essential type violations)
#    5 Rule-17.7  (return value ignored)
#    0 Rule-21.3  (malloc/free not used - GOOD for SIL 2+)
```

**Extract mandatory violations**:

```bash
# MISRA C Mandatory rules MUST have zero violations (SIL 2+)
grep "Rule.*Mandatory" reports/pclint/pclint_report.txt | wc -l

# Expected: 0 (zero mandatory violations for SIL 2+)
```

### 3.4 Review MISRA C Mandatory Violations

**SIL 2+ Requirement**: **Zero mandatory rule violations**

If any mandatory violations found:
1. Document each violation in defect tracking system
2. Assign to developer for immediate fix
3. Re-run PC-lint after fix
4. Verify zero mandatory violations

**Example mandatory violations to fix immediately**:
- **Rule 1.3**: No undefined behavior
- **Rule 9.1**: All variables initialized before use
- **Rule 21.3**: No `malloc`, `calloc`, `realloc`, `free` (SIL 2+)

### 3.5 Review MISRA C Required/Advisory Violations

**Required rules**: Should be followed, deviations require justification

```bash
# Extract required rule violations
grep "Rule.*Required" reports/pclint/pclint_report.txt > \
    reports/pclint/required_violations.txt

# Count
wc -l reports/pclint/required_violations.txt
```

**Action**: 
- Review all required violations
- Fix where practical
- Document deviations with justification (see MISRA Deviation Process)

**Advisory rules**: Recommended, deviations acceptable

```bash
# Extract advisory rule violations
grep "Rule.*Advisory" reports/pclint/pclint_report.txt > \
    reports/pclint/advisory_violations.txt
```

**Action**: Review and fix where reasonable, document deviations if significant.

---

## Step 4: Run Clang Static Analyzer (Deep Analysis)

### 4.1 Execute Clang Static Analyzer with scan-build

**Command**:

```bash
# Clean build directory
make clean

# Run scan-build
scan-build \
    -o reports/clang \
    --use-analyzer=/usr/bin/clang \
    -enable-checker core \
    -enable-checker deadcode \
    -enable-checker security \
    -enable-checker unix \
    -enable-checker nullability \
    --status-bugs \
    make

# Check exit code
if [ $? -eq 0 ]; then
    echo "✓ Clang Static Analyzer found no bugs"
else
    echo "✗ Clang Static Analyzer found potential bugs"
fi
```

**Explanation of checkers**:
- `core`: Core checks (null dereference, divide by zero, stack address escape)
- `deadcode`: Dead code detection
- `security`: Security issues (buffer overflow, format string)
- `unix`: Unix API usage (malloc/free, file descriptors)
- `nullability`: Null pointer handling

### 4.2 View Clang Analysis Report

```bash
# Find the generated report directory
CLANG_REPORT_DIR=$(ls -td reports/clang/2* | head -1)

# Open HTML report
xdg-open "$CLANG_REPORT_DIR/index.html"

# Or view text summary
cat "$CLANG_REPORT_DIR/scan-build.log"
```

### 4.3 Extract Clang Findings

```bash
# Count bugs by type
grep "warn_" "$CLANG_REPORT_DIR/scan-build.log" | \
    awk '{print $NF}' | \
    sort | uniq -c

# Example output:
#   3 core.NullDereference
#   2 deadcode.DeadStores
#   1 security.insecureAPI.strcpy
```

### 4.4 Review Clang Critical Issues

**Critical Clang warnings**:
- **core.NullDereference**: Null pointer dereference
- **core.DivideZero**: Division by zero
- **core.StackAddressEscape**: Stack address escapes function scope
- **security.insecureAPI**: Use of unsafe functions (strcpy, sprintf)

**SIL 3-4 Requirement**: Zero critical issues

**Action**: Fix all critical issues, re-run analysis, verify zero bugs.

---

## Step 5: Run Complexity Analysis (Lizard)

### 5.1 Execute Lizard

**Command** (SIL 4: CCN ≤ 10):

```bash
# Run Lizard with complexity limit
lizard \
    --CCN 10 \
    --length 100 \
    --arguments 5 \
    --warnings_only \
    src/ \
    > reports/complexity/lizard_warnings.txt

# Check exit code
if [ $? -eq 0 ]; then
    echo "✓ All functions meet complexity limit (CCN ≤ 10)"
else
    echo "✗ Some functions exceed complexity limit"
fi
```

**Explanation of flags**:
- `--CCN 10`: Cyclomatic Complexity Number threshold (SIL 4)
- `--length 100`: Function length threshold (100 lines)
- `--arguments 5`: Parameter count threshold (5 parameters)
- `--warnings_only`: Only show violations

### 5.2 Generate HTML Report

```bash
# Generate full HTML report
lizard \
    --CCN 10 \
    --html \
    --output_file reports/complexity/lizard_report.html \
    src/

# Open report
xdg-open reports/complexity/lizard_report.html
```

### 5.3 Review Complexity Violations

```bash
# List functions exceeding complexity limit
cat reports/complexity/lizard_warnings.txt

# Example output:
# ================================================
#   NLOC  CCN  token  PARAM  length  location  
# ================================================
#     45   12    320      3      50  calculate_train_position@src/positioning.c:120
#     38   11    280      4      45  validate_signal_state@src/signals.c:200
```

**SIL 4 Requirement**: All functions CCN ≤ 10

**Action**: Refactor functions exceeding limit, re-run analysis.

### 5.4 Complexity Refactoring Guidelines

**Function exceeds CCN = 10**:

```c
// BEFORE: CCN = 12 (TOO HIGH for SIL 4)
error_t calculate_train_position(train_t* train) {
    if (train == NULL) return ERROR_NULL_POINTER;
    
    if (train->mode == MODE_AUTOMATIC) {
        if (train->speed > 0) {
            if (train->direction == FORWARD) {
                // Complex calculation...
                if (condition1) {
                    if (condition2) {
                        // More logic...
                    }
                }
            } else {
                // Reverse direction logic...
            }
        } else {
            // Stationary logic...
        }
    } else {
        // Manual mode logic...
    }
    return SUCCESS;
}

// AFTER: Refactored into smaller functions (CCN ≤ 10 each)
static error_t calculate_position_automatic(train_t* train) {
    // CCN = 5
    if (train->speed > 0) {
        return (train->direction == FORWARD) 
            ? calculate_position_forward(train)
            : calculate_position_reverse(train);
    }
    return calculate_position_stationary(train);
}

static error_t calculate_position_manual(train_t* train) {
    // CCN = 3
    // Manual mode logic
    return SUCCESS;
}

error_t calculate_train_position(train_t* train) {
    // CCN = 3 (NOW ACCEPTABLE)
    if (train == NULL) return ERROR_NULL_POINTER;
    
    return (train->mode == MODE_AUTOMATIC)
        ? calculate_position_automatic(train)
        : calculate_position_manual(train);
}
```

---

## Step 6: Analyze and Triage Results

### 6.1 Consolidate All Findings

**Create findings summary**:

```bash
# Generate consolidated report
python3 << 'EOF'
import xml.etree.ElementTree as ET

print("=" * 60)
print("STATIC ANALYSIS SUMMARY")
print("=" * 60)

# Cppcheck
try:
    tree = ET.parse('reports/cppcheck/cppcheck_report.xml')
    root = tree.getroot()
    errors = root.findall('.//error')
    print(f"\nCppcheck: {len(errors)} issues")
    
    severities = {}
    for error in errors:
        sev = error.get('severity', 'unknown')
        severities[sev] = severities.get(sev, 0) + 1
    
    for sev, count in sorted(severities.items()):
        print(f"  {sev}: {count}")
except:
    print("\nCppcheck: Report not found")

# PC-lint (count from text file)
try:
    with open('reports/pclint/pclint_report.txt') as f:
        lines = f.readlines()
    violations = [l for l in lines if 'Rule' in l]
    print(f"\nPC-lint Plus: {len(violations)} MISRA C violations")
    
    mandatory = [l for l in violations if 'Mandatory' in l]
    required = [l for l in violations if 'Required' in l]
    advisory = [l for l in violations if 'Advisory' in l]
    
    print(f"  Mandatory: {len(mandatory)}")
    print(f"  Required: {len(required)}")
    print(f"  Advisory: {len(advisory)}")
except:
    print("\nPC-lint Plus: Report not found")

# Clang (estimate from log)
print("\nClang Static Analyzer: See HTML report")

# Lizard
try:
    with open('reports/complexity/lizard_warnings.txt') as f:
        lines = f.readlines()
    violations = [l for l in lines if 'src/' in l]
    print(f"\nLizard: {len(violations)} complexity violations (CCN > 10)")
except:
    print("\nLizard: No violations (all functions CCN ≤ 10)")

print("\n" + "=" * 60)
EOF
```

### 6.2 Classify Findings by Severity

**Severity Classification**:

| Severity | Description | SIL 2+ Action | SIL 3-4 Action |
|----------|-------------|---------------|----------------|
| **Critical** | Safety impact, undefined behavior | MUST FIX | **MUST FIX** |
| **High** | Potential bug, MISRA mandatory violation | MUST FIX | **MUST FIX** |
| **Medium** | Code quality issue, MISRA required violation | Should fix or justify | Should fix or justify |
| **Low** | Style issue, MISRA advisory violation | Optional | Optional |

**Critical Issues** (examples):
- Null pointer dereference
- Buffer overflow
- Use after free
- Division by zero
- Uninitialized variable use
- MISRA C mandatory rule violations
- Complexity exceeding limit (SIL 4: CCN > 10)

**High Issues** (examples):
- Memory leak
- Dead code
- Unreachable code
- MISRA C required rule violations
- Missing return value check

**Medium Issues** (examples):
- Style violations
- Performance issues
- Unused variables
- MISRA C advisory rule violations

**Low Issues** (examples):
- Code formatting
- Comment style
- Informational messages

### 6.3 Create Defect Tickets

**For each Critical/High issue**:

```yaml
# Defect Ticket Template
defect_id: DEF-2026-001
title: "Null pointer dereference in calculate_speed()"
severity: Critical
type: Static Analysis
source: Cppcheck
file: src/speed_calc.c
line: 145
function: calculate_speed
description: |
  Cppcheck reports potential null pointer dereference:
  "sensor" pointer not checked before dereference at line 145.
  
  Code:
    uint32_t speed = sensor->pulse_count / time_ms;  // Line 145
    
  Issue: "sensor" may be NULL if validation fails earlier.
  
reproduction: |
  1. Call calculate_speed() with NULL sensor pointer
  2. Crash or undefined behavior
  
impact: |
  Safety impact: Could cause train control system to fail.
  SIL 4 Critical.
  
recommendation: |
  Add NULL pointer check:
    if (sensor == NULL) return ERROR_NULL_POINTER;
    uint32_t speed = sensor->pulse_count / time_ms;
  
assigned_to: Developer Name
due_date: 2026-03-15
status: Open
```

### 6.4 Identify False Positives

**Some findings may be false positives**:

```c
// Example: Cppcheck may flag this as "uninitialized variable"
error_t read_sensor(sensor_t* sensor, uint32_t* value) {
    if (sensor == NULL || value == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    // Cppcheck may warn: "value" not initialized
    // But this is intentional - value is OUTPUT parameter
    *value = sensor->data;  // Correct usage
    return SUCCESS;
}

// Suppress false positive with inline comment
error_t read_sensor(sensor_t* sensor, uint32_t* value) {
    if (sensor == NULL || value == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    // cppcheck-suppress uninitvar
    // Justification: value is output parameter, initialized by this function
    *value = sensor->data;
    return SUCCESS;
}
```

**Document false positives**:

```markdown
## False Positive Log

### FP-001: Uninitialized variable warning in read_sensor()
- **Tool**: Cppcheck
- **File**: src/sensors.c:120
- **Warning**: "uninitvar: Uninitialized variable: value"
- **Justification**: `value` is an output parameter, intentionally not initialized before use. Function initializes it before return.
- **Suppression**: Inline suppression added with comment
- **Approved by**: VER-2 (Alice Williams), 2026-03-13
```

---

## Step 7: Document Findings

### 7.1 Create Static Analysis Findings Log

**Template**: `reports/static-analysis-findings-log.md`

```markdown
# Static Analysis Findings Log

**Project**: Train Control System (TCS)
**SIL Level**: 4
**Analysis Date**: 2026-03-13
**Verifier**: Alice Williams (VER-2)

## Summary

| Tool | Total Issues | Critical | High | Medium | Low |
|------|--------------|----------|------|--------|-----|
| Cppcheck | 26 | 0 | 3 | 15 | 8 |
| PC-lint Plus | 30 | 0 | 10 | 15 | 5 |
| Clang Analyzer | 5 | 0 | 2 | 3 | 0 |
| Lizard | 2 | 0 | 2 | 0 | 0 |
| **Total** | **63** | **0** | **17** | **33** | **13** |

## Critical Issues (MUST FIX for SIL 4)
**Count**: 0 ✓

## High Issues (MUST FIX or JUSTIFY)
**Count**: 17

### High-1: Null pointer check missing in calculate_speed()
- **Tool**: Cppcheck
- **File**: src/speed_calc.c:145
- **Severity**: High
- **Description**: Pointer "sensor" not checked before dereference
- **Defect ID**: DEF-2026-001
- **Status**: Open
- **Assigned**: Developer Name

### High-2: MISRA C Rule 17.7 violation - Return value ignored
- **Tool**: PC-lint Plus
- **File**: src/comms.c:230
- **Severity**: High
- **Description**: Return value of send_message() ignored
- **Defect ID**: DEF-2026-002
- **Status**: Open
- **Assigned**: Developer Name

[... continue for all High issues ...]

## Medium Issues
**Count**: 33

[... list medium issues ...]

## Low Issues
**Count**: 13

[... list low issues ...]

## False Positives
**Count**: 3

[... document false positives ...]

## MISRA C Compliance Summary

| Rule Category | Mandatory | Required | Advisory |
|---------------|-----------|----------|----------|
| **Violations** | **0** ✓ | 10 | 5 |

**SIL 4 Requirement**: Zero mandatory violations ✓ PASS

## Complexity Analysis Summary

| Metric | Target (SIL 4) | Actual | Status |
|--------|----------------|--------|--------|
| Max CCN | ≤ 10 | 12 | ✗ FAIL |
| Functions > 10 CCN | 0 | 2 | ✗ FAIL |

**Functions exceeding CCN = 10**:
1. calculate_train_position() - CCN = 12 (DEF-2026-015)
2. validate_signal_state() - CCN = 11 (DEF-2026-016)

## Overall Status

**Pass/Fail**: ✗ FAIL
**Reason**: 17 High severity issues, 2 complexity violations

**Action Required**: Fix all High severity issues and complexity violations before Source Code Verification can pass.

## Approvals
- **Analyzed by**: Alice Williams (VER-2), 2026-03-13
- **Reviewed by**: [VMGR Name]
```

---

## Step 8: Track Remediation

### 8.1 Developer Fixes Defects

**Defect Resolution Workflow**:

```
1. Developer receives defect assignment (DEF-2026-001)
2. Developer analyzes issue and implements fix
3. Developer commits fix to version control
4. Developer marks defect as "Fixed"
5. Verifier re-runs static analysis
6. Verifier verifies fix effectiveness
7. If fixed: Verifier closes defect
8. If not fixed: Verifier reopens defect with notes
```

**Example Fix**:

```c
// BEFORE (DEF-2026-001): Null pointer check missing
uint32_t calculate_speed(sensor_t* sensor, uint32_t time_ms) {
    uint32_t speed = sensor->pulse_count / time_ms;  // Crash if sensor == NULL
    return speed;
}

// AFTER: Fixed - NULL check added
uint32_t calculate_speed(sensor_t* sensor, uint32_t time_ms) {
    // Fix for DEF-2026-001: Add NULL pointer check
    if (sensor == NULL) {
        return 0;  // Safe default
    }
    
    // Defensive: Also check divide-by-zero
    if (time_ms == 0) {
        return 0;  // Safe default
    }
    
    uint32_t speed = sensor->pulse_count / time_ms;
    return speed;
}
```

### 8.2 Re-run Static Analysis

**After fixes committed**:

```bash
# Re-run all static analysis tools
./scripts/run_static_analysis.sh

# Compare results
diff reports/cppcheck/cppcheck_report_v1.xml \
     reports/cppcheck/cppcheck_report_v2.xml

# Expected: Fewer issues in v2
```

### 8.3 Verify Fix Effectiveness

**Check specific defect is resolved**:

```bash
# Verify DEF-2026-001 fixed (Null pointer check)
grep "src/speed_calc.c:145" reports/cppcheck/cppcheck_report_v2.xml

# Expected: No match (issue resolved)
```

**Update defect ticket**:

```yaml
defect_id: DEF-2026-001
status: Verified Fixed
resolution: |
  Developer added NULL pointer check at src/speed_calc.c:142.
  Re-ran Cppcheck - no null pointer warning at line 145.
  Fix verified effective.
verified_by: Alice Williams (VER-2)
verified_date: 2026-03-14
```

### 8.4 Iterate Until All Critical/High Issues Resolved

**Repeat Steps 2-8 until**:
- Zero Critical issues
- Zero High issues (or all justified)
- Zero MISRA C mandatory violations (SIL 2+)
- All complexity violations resolved (CCN ≤ 10 for SIL 4)

---

## Step 9: Generate Static Analysis Report

### 9.1 Create Static Analysis Report

**Template**: `docs/static-analysis/Static-Analysis-Report-v1.0.md`

```markdown
# Static Analysis Report

**Document ID**: DOC-SA-2026-001
**Project**: Train Control System (TCS)
**SIL Level**: 4
**Analysis Date**: 2026-03-14
**Verifier**: Alice Williams (VER-2)
**Approved By**: John Doe (VMGR)

## Document Control

| Version | Date | Author | Change Description | Approval |
|---------|------|--------|-------------------|----------|
| 1.0 | 2026-03-14 | A. Williams | Initial release | J. Doe (VMGR) |

## 1. Introduction

This Static Analysis Report documents the results of static analysis performed on the Train Control System (TCS) source code per EN 50128 Section 7.5.4.10.

## 2. Scope

**Files Analyzed**:
- Source files: 25 files (5,500 SLOC)
- Header files: 30 files (1,200 SLOC)
- Total: 55 files (6,700 SLOC)

**Analysis Period**: 2026-03-13 to 2026-03-14

## 3. Static Analysis Techniques Applied

Per EN 50128 Table A.19 (MANDATORY for SIL 4):

| # | Technique | Status | Tool(s) |
|---|-----------|--------|---------|
| 2 | **Control Flow Analysis** | ✓ PASS | Cppcheck, Clang |
| 3 | **Data Flow Analysis** | ✓ PASS | Cppcheck, Clang |
| 6 | Code Review | ✓ PASS | Manual (separate report) |
| 8 | Complexity Metrics | ✓ PASS | Lizard |

## 4. Tools Used

| Tool | Version | Classification | Qualification | Purpose |
|------|---------|---------------|---------------|---------|
| Cppcheck | 2.13.0 | T2 | Qualified | General static analysis |
| PC-lint Plus | 2.0 | T2 | Qualified | MISRA C compliance |
| Clang Analyzer | 18.1 | T2 | Qualified | Deep semantic analysis |
| Lizard | 1.17 | T2 | Qualified | Complexity metrics |

## 5. Analysis Results

### 5.1 Summary

| Tool | Issues Found | Critical | High | Medium | Low |
|------|--------------|----------|------|--------|-----|
| Cppcheck | 26 → 8 | 0 | 0 | 5 | 3 |
| PC-lint Plus | 30 → 5 | 0 | 0 | 3 | 2 |
| Clang Analyzer | 5 → 0 | 0 | 0 | 0 | 0 |
| Lizard | 2 → 0 | 0 | 0 | 0 | 0 |
| **Final** | **13** | **0** | **0** | **8** | **5** |

**Note**: Initial analysis found 63 issues. After remediation (18 fixes), 13 low/medium issues remain (all justified or suppressed).

### 5.2 Critical Issues
**Count**: 0 ✓

### 5.3 High Issues
**Count**: 0 ✓

### 5.4 Medium Issues
**Count**: 8

All medium issues reviewed and justified (see Appendix A).

### 5.5 Low Issues
**Count**: 5

Low priority, informational only.

## 6. MISRA C Compliance

| Rule Category | Violations | Status |
|---------------|-----------|--------|
| Mandatory | 0 | ✓ PASS |
| Required | 3 | Justified (see deviations) |
| Advisory | 2 | Acceptable |

**SIL 4 Requirement**: Zero mandatory violations ✓ PASS

**MISRA Deviations**: 3 required rule deviations documented in MISRA Deviation Register (see Appendix B).

## 7. Complexity Analysis

| Metric | Target (SIL 4) | Actual | Status |
|--------|----------------|--------|--------|
| Max CCN | ≤ 10 | 9 | ✓ PASS |
| Mean CCN | - | 4.2 | ✓ PASS |
| Functions > 10 CCN | 0 | 0 | ✓ PASS |

## 8. Control Flow Analysis

**Findings**:
- Zero unreachable code
- Zero infinite loops (except main loop)
- All functions return appropriate values

**Status**: ✓ PASS

## 9. Data Flow Analysis

**Findings**:
- Zero uninitialized variable uses
- Zero unused variables (except intentional)
- All outputs assigned before use

**Status**: ✓ PASS

## 10. Defects Found and Resolved

**Total Defects Created**: 18
**Defects Fixed**: 18
**Defects Open**: 0

See Appendix C for full defect list.

## 11. Overall Assessment

**Static Analysis Status**: ✓ PASS

**Criteria Met**:
- ✓ Zero critical issues
- ✓ Zero high issues
- ✓ Zero MISRA C mandatory violations
- ✓ All functions CCN ≤ 10
- ✓ Control flow analysis passed
- ✓ Data flow analysis passed

**Recommendation**: Source code PASSES static analysis requirements for SIL 4.

## 12. Approvals

- **Analyzed by**: Alice Williams (VER-2), 2026-03-14
- **Reviewed by**: John Doe (VMGR), 2026-03-14
- **Status**: ✓ APPROVED

---

## Appendices

### Appendix A: Medium Issue Justifications
[Detail each medium issue and justification]

### Appendix B: MISRA C Deviation Register
[Document each MISRA deviation with approval]

### Appendix C: Defect List
[Full list of 18 defects with resolution details]

### Appendix D: Tool Configuration Files
[Cppcheck, PC-lint, Clang, Lizard configurations]

### Appendix E: Raw Tool Reports
[Links to XML/HTML reports from each tool]
```

---

## Continuous Integration Setup

### CI Pipeline Integration

**Automate static analysis in CI/CD pipeline**:

```yaml
# .gitlab-ci.yml (example)
static-analysis:
  stage: verify
  image: ubuntu:22.04
  before_script:
    - apt-get update
    - apt-get install -y cppcheck clang clang-tools python3-pip
    - pip3 install lizard
  script:
    # Run Cppcheck
    - cppcheck --enable=all --addon=misra --xml --xml-version=2 src/ 2> cppcheck_report.xml
    
    # Run Clang
    - scan-build -o clang_reports --status-bugs make
    
    # Run Lizard (SIL 4: CCN ≤ 10)
    - lizard --CCN 10 --warnings_only src/
    
    # Check for critical issues (exit non-zero if found)
    - python3 scripts/check_static_analysis_pass.py
  artifacts:
    paths:
      - cppcheck_report.xml
      - clang_reports/
    reports:
      junit: test-results.xml
  only:
    - merge_requests
    - main
```

**Fail build on critical issues**:

```python
# scripts/check_static_analysis_pass.py
import sys
import xml.etree.ElementTree as ET

tree = ET.parse('cppcheck_report.xml')
root = tree.getroot()

critical_count = 0
for error in root.findall('.//error'):
    severity = error.get('severity')
    if severity == 'error':
        critical_count += 1
        print(f"CRITICAL: {error.get('msg')} at {error.get('file')}:{error.get('line')}")

if critical_count > 0:
    print(f"\nFAIL: {critical_count} critical issues found")
    sys.exit(1)
else:
    print("\nPASS: No critical issues")
    sys.exit(0)
```

---

## Tool-Specific Configurations

### Cppcheck Configuration Reference

**Project file** (`cppcheck-project.xml`): See Step 1.3

**Common suppressions**:

```xml
<suppressions>
    <!-- Suppress system header warnings -->
    <suppress>missingIncludeSystem</suppress>
    
    <!-- Suppress unused function warnings (modular code) -->
    <suppress>unusedFunction</suppress>
    
    <!-- Project-specific suppressions -->
    <suppress>
        <id>uninitvar</id>
        <fileName>src/sensors.c</fileName>
        <lineNumber>120</lineNumber>
        <!-- Justification: Output parameter -->
    </suppress>
</suppressions>
```

### PC-lint Plus Configuration Reference

**Configuration file** (`pclint.lnt`): See Step 1.3

**Common suppressions**:

```
// Suppress specific warnings with justification
-esym(818, *)  // Pointer parameter could be pointer to const
// Justification: Function interface defined by external API

-esym(715, param_name)  // Symbol not referenced
// Justification: Reserved for future use
```

### Clang Configuration Reference

**Checker selection**: See Step 4.1

**Suppress false positives**:

```c
// Suppress specific Clang warning
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
uint32_t reserved_for_future;  // Intentionally unused now
#pragma clang diagnostic pop
```

---

## Summary

This static analysis workflow provides comprehensive, tool-based verification for EN 50128:

1. **Cppcheck**: General static analysis (control flow, data flow, style)
2. **PC-lint Plus**: MISRA C:2012 compliance (all 178 rules + 16 directives)
3. **Clang Static Analyzer**: Deep semantic analysis (memory safety, security)
4. **Lizard**: Complexity metrics (CCN ≤ 10 for SIL 4)

**Key Success Factors**:
- Run all tools on every commit (CI/CD integration)
- Zero tolerance for critical issues (SIL 2+)
- Zero MISRA C mandatory violations (SIL 2+)
- All complexity violations fixed (CCN ≤ 10 for SIL 4)
- Document all deviations with justification
- Independent verification (SIL 3-4)

**Next Steps**:
- Proceed to `workflows/traceability-verification.md` to verify traceability
- Proceed to `workflows/verification-reporting.md` to create Verification Reports
