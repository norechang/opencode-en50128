# Static Analysis Guidelines for EN 50128

**Purpose**: Comprehensive guidelines for configuring, executing, and interpreting static analysis tools for EN 50128 compliant C software.

**Scope**: Tool setup, configuration, thresholds, defect severity classification, and result interpretation for all SIL levels.

**Audience**: Verifiers (VER), Implementers (IMP), Quality Assurance (QUA)

**EN 50128 Reference**:
- Table A.5, Technique 3 "Static Analysis" (**MANDATORY** SIL 3-4)
- Table A.19 "Static Analysis Techniques"
- Section 7.5.4.10 "Software Source Code Verification"

**Related Documents**:
- `workflows/static-analysis-workflow.md` - Execution workflow
- `resources/verification-tools-reference.md` - Tool catalog
- `resources/common-verification-defects.md` - Defect patterns

---

## Table of Contents

1. [Static Analysis Overview](#1-static-analysis-overview)
2. [Tool Selection by SIL Level](#2-tool-selection-by-sil-level)
3. [Cppcheck Configuration](#3-cppcheck-configuration)
4. [PC-lint Plus Configuration](#4-pc-lint-plus-configuration)
5. [Clang Static Analyzer Configuration](#5-clang-static-analyzer-configuration)
6. [Lizard Complexity Analysis](#6-lizard-complexity-analysis)
7. [Defect Severity Classification](#7-defect-severity-classification)
8. [Result Interpretation Guidelines](#8-result-interpretation-guidelines)
9. [False Positive Handling](#9-false-positive-handling)
10. [Thresholds and Targets by SIL](#10-thresholds-and-targets-by-sil)
11. [Continuous Integration Setup](#11-continuous-integration-setup)
12. [Tool Qualification Requirements](#12-tool-qualification-requirements)

---

## 1. Static Analysis Overview

### Purpose of Static Analysis

Static analysis provides automated detection of:
- **Control flow issues**: Unreachable code, infinite loops, missing returns
- **Data flow issues**: Uninitialized variables, unused variables, use-after-free
- **MISRA C compliance**: All 178 rules + 16 directives (MISRA C:2012)
- **Semantic errors**: Type mismatches, API misuse, resource leaks
- **Complexity violations**: Functions exceeding cyclomatic complexity limits
- **Security issues**: Buffer overflows, integer overflows, NULL pointer dereferences

### EN 50128 Static Analysis Requirements

**Table A.5, Technique 3 "Static Analysis"**:
- SIL 0: Not recommended (-)
- SIL 1-2: Highly Recommended (HR)
- SIL 3-4: **MANDATORY (M)**

**Table A.19 "Static Analysis Techniques"** (SIL 3-4):

| Technique | EN 50128 Ref | SIL 0 | SIL 1-2 | SIL 3-4 | Description |
|-----------|--------------|-------|---------|---------|-------------|
| **Boundary Value Analysis** | Table A.19 #1 | R | HR | HR | Test boundary conditions in code |
| **Control Flow Analysis** | Table A.19 #2 | R | HR | **M** | Analyze program control paths |
| **Data Flow Analysis** | Table A.19 #3 | R | HR | **M** | Analyze variable lifecycles |
| **Range Checking** | Table A.19 #4 | R | HR | HR | Verify value ranges |
| **Semantic Analysis** | Table A.19 #5 | R | HR | HR | Verify meaning and intent |
| **Stack Usage Analysis** | Table A.19 #6 | R | HR | HR | Measure stack consumption |
| **Timing and Sizing Analysis** | Table A.19 #7 | - | R | HR | Verify resource usage |
| **Metrics** | Table A.19 #8 | R | HR | HR | Measure complexity, coupling, etc. |

**Key Point**: For SIL 3-4, Control Flow Analysis and Data Flow Analysis are **MANDATORY**.

### Static Analysis Tool Categories

**General Static Analysis**:
- Cppcheck: Multi-purpose C/C++ static analyzer
- Clang Static Analyzer: Deep semantic analysis

**MISRA C Compliance**:
- PC-lint Plus: Industry-standard MISRA C checker (all 178 rules + 16 directives)
- Cppcheck MISRA addon: Basic MISRA checking

**Complexity Analysis**:
- Lizard: Cyclomatic complexity (CCN), function length, parameter count

**Specialized Analysis**:
- Valgrind: Runtime memory analysis (not true static analysis, but complements)
- AddressSanitizer: Runtime memory safety (not true static analysis)

### Multi-Tool Strategy (SIL 3-4)

For SIL 3-4, use **multiple independent tools** to increase defect detection:

```
Cppcheck (General)
    ↓
PC-lint Plus (MISRA C)
    ↓
Clang Static Analyzer (Deep Semantic)
    ↓
Lizard (Complexity)
    ↓
Cross-check results → Comprehensive defect coverage
```

**Rationale**: No single tool detects all defects. Multiple tools provide:
- Broader defect coverage (each tool has strengths)
- Cross-validation (multiple tools find same issue → higher confidence)
- Reduced false negatives (missed defects)

---

## 2. Tool Selection by SIL Level

### SIL 0 (Advisory Mode)

**Minimum Tools**:
- Cppcheck (basic checking)
- Compiler warnings (`-Wall -Wextra`)

**Optional Tools**:
- Lizard (complexity awareness)

**Configuration**: Low rigor, focus on obvious errors.

**Defect Threshold**: No formal threshold, advisory only.

### SIL 1 (Basic Quality)

**Recommended Tools**:
- Cppcheck (general static analysis)
- Lizard (complexity ≤ 20)
- Compiler warnings (`-Wall -Wextra -Werror`)

**Configuration**: Moderate rigor, enable common checks.

**Defect Threshold**: Zero critical defects (uninitialized variables, NULL derefs).

### SIL 2 (Formal Quality)

**Required Tools**:
- Cppcheck (control/data flow analysis)
- PC-lint Plus (MISRA C:2012 - Mandatory rules only)
- Lizard (complexity ≤ 15)
- Compiler warnings (`-Wall -Wextra -Werror -pedantic`)

**Configuration**: High rigor, MISRA C Mandatory rules.

**Defect Thresholds**:
- Zero MISRA C Mandatory violations
- Zero critical static analysis issues
- 100% functions with CCN ≤ 15

### SIL 3-4 (Maximum Rigor)

**MANDATORY Tools**:
- Cppcheck (all checks enabled, control/data flow)
- PC-lint Plus (MISRA C:2012 - all 178 rules + 16 directives)
- Clang Static Analyzer (deep semantic analysis)
- Lizard (complexity ≤ 10 for SIL 4, ≤ 12 for SIL 3)
- Compiler warnings (`-Wall -Wextra -Werror -pedantic -Wconversion`)

**Configuration**: Maximum rigor, all checks enabled.

**Defect Thresholds**:
- Zero MISRA C Mandatory violations
- Zero MISRA C Required violations (OR documented deviations)
- Zero critical static analysis issues
- Zero high-severity static analysis issues (OR documented justifications)
- 100% functions with CCN ≤ 10 (SIL 4) or ≤ 12 (SIL 3)

**Additional Requirements**:
- Tool qualification documented (Tool Confidence Level T2 or T3)
- Independent verification with multiple tools (cross-check)
- Formal defect tracking and resolution process

---

## 3. Cppcheck Configuration

### Tool Overview

**Cppcheck** is a general-purpose C/C++ static analyzer focusing on:
- Undefined behavior
- Memory leaks
- Uninitialized variables
- NULL pointer dereferences
- Out-of-bounds access
- Control flow issues
- MISRA C (with addon)

**Strengths**:
- Fast execution
- Good control/data flow analysis
- Few false positives
- XML output for automation

**Limitations**:
- Less comprehensive MISRA C checking than PC-lint Plus
- May miss complex semantic issues

### Installation

```bash
# Ubuntu/Debian
sudo apt install cppcheck

# Or build from source for latest version
git clone https://github.com/danmar/cppcheck.git
cd cppcheck
make MATCHCOMPILER=yes FILESDIR=/usr/share/cppcheck HAVE_RULES=yes
sudo make install

# Verify version (use 2.10+ for best results)
cppcheck --version
```

### Basic Configuration (SIL 0-1)

```bash
# Basic checking
cppcheck --enable=warning,style,performance,portability src/

# Output to file
cppcheck --enable=warning,style,performance,portability src/ 2> cppcheck_report.txt
```

**Options Explained**:
- `--enable=warning`: Enable warning checks
- `--enable=style`: Enable style checks
- `--enable=performance`: Enable performance checks
- `--enable=portability`: Enable portability checks

### Advanced Configuration (SIL 2)

```bash
# Enable all checks except MISRA (MISRA requires addon)
cppcheck --enable=all \
         --suppress=missingInclude \
         --inline-suppr \
         --xml --xml-version=2 \
         --output-file=cppcheck_report.xml \
         src/
```

**Options Explained**:
- `--enable=all`: Enable ALL checks (warning, style, performance, portability, unusedFunction, missingInclude)
- `--suppress=missingInclude`: Suppress "include file not found" warnings (common in embedded systems)
- `--inline-suppr`: Allow inline suppressions with `// cppcheck-suppress` comments
- `--xml --xml-version=2`: Generate XML output for automation
- `--output-file=FILE`: Write to file (use `2> FILE` for stderr capture)

### Maximum Rigor Configuration (SIL 3-4)

```bash
# Maximum rigor with MISRA C addon
cppcheck --enable=all \
         --addon=misra \
         --addon=cert \
         --inline-suppr \
         --suppress=missingInclude \
         --suppress=unmatchedSuppression \
         --xml --xml-version=2 \
         --inconclusive \
         --platform=unix64 \
         --std=c11 \
         --checkers-report=checkers_report.txt \
         src/ 2> cppcheck_report.xml

# Generate HTML report from XML
cppcheck-htmlreport --file=cppcheck_report.xml \
                    --report-dir=cppcheck_html \
                    --source-dir=src/
```

**Options Explained**:
- `--addon=misra`: Enable MISRA C:2012 checking (requires `misra.json` config)
- `--addon=cert`: Enable SEI CERT C coding standard checking
- `--inconclusive`: Report inconclusive findings (may have false positives, but thorough for SIL 3-4)
- `--platform=unix64`: Specify target platform (unix32, unix64, win32, win64, native)
- `--std=c11`: Specify C standard (c89, c99, c11, c17)
- `--checkers-report=FILE`: Report which checkers were enabled

### MISRA C Addon Configuration

**Create `misra.json`** configuration file:

```json
{
  "script": "misra.py",
  "args": ["--rule-texts=misra_rules.txt"],
  "cppcheck": {
    "enable": ["warning", "style", "performance", "portability"],
    "suppressions": [
      "missingInclude"
    ]
  }
}
```

**Create `misra_rules.txt`** with MISRA C rule texts (required for full rule checking):

```
Rule 1.1: Required: The program shall contain no violations of the standard C syntax and constraints
Rule 1.2: Advisory: Language extensions should not be used
Rule 1.3: Required: There shall be no occurrence of undefined or critical unspecified behavior
...
[All 178 rules + 16 directives from MISRA C:2012]
```

**Note**: MISRA C:2012 rule texts are proprietary and must be purchased from MISRA. See https://www.misra.org.uk/

**Run with MISRA addon**:

```bash
cppcheck --enable=all --addon=misra.json src/ 2> cppcheck_misra_report.xml
```

### Platform-Specific Configuration (Embedded Systems)

For embedded systems (typical for railway safety software):

```bash
# ARM Cortex-M4 example (32-bit)
cppcheck --enable=all \
         --addon=misra \
         --platform=unix32 \
         --std=c11 \
         -DSTM32F4 \
         -D__ARM_ARCH_7EM__ \
         -I./include \
         -I./drivers/include \
         --xml --xml-version=2 \
         src/ 2> cppcheck_report.xml
```

**Options Explained**:
- `--platform=unix32`: 32-bit platform (matches ARM Cortex-M)
- `-DMACRO`: Define preprocessor macros for target
- `-I./path`: Include directories for header files

### Suppressing False Positives

**Inline Suppression** (use sparingly, document rationale):

```c
// cppcheck-suppress uninitvar
// Rationale: Variable initialized by hardware register read
uint32_t status = UART1->SR;

// cppcheck-suppress nullPointer
// Rationale: Pointer validated by previous assert()
assert(ptr != NULL);
*ptr = value;  // cppcheck would warn about potential NULL deref
```

**Suppression File** (`suppressions.txt`):

```
// Suppress specific warning in specific file
uninitvar:src/hal/uart.c:145

// Suppress specific warning in all files
missingInclude

// Suppress all warnings in specific file (use very sparingly)
*:src/third_party/vendor_lib.c
```

**Use suppression file**:

```bash
cppcheck --enable=all --suppressions-list=suppressions.txt src/
```

### Interpreting Cppcheck Output

**XML Output Structure**:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<results version="2">
  <cppcheck version="2.13.0"/>
  <errors>
    <error id="uninitvar" severity="error" msg="Uninitialized variable: x" verbose="The variable 'x' is used before being initialized.">
      <location file="src/main.c" line="45" column="10"/>
    </error>
    <error id="nullPointer" severity="error" msg="Possible null pointer dereference: ptr" verbose="Null pointer dereference">
      <location file="src/sensor.c" line="123" column="5"/>
    </error>
  </errors>
</results>
```

**Severity Levels**:
- `error`: Definite bug (uninitialized variable, NULL deref, buffer overflow)
- `warning`: Potential bug (unused variable, suspicious code)
- `style`: Code style issue (inefficient code, readability)
- `performance`: Performance issue (unnecessary copy, inefficient algorithm)
- `portability`: Portability issue (platform-specific code)
- `information`: Informational message

**Priority for SIL 3-4**:
1. **error**: MUST be fixed (zero tolerance)
2. **warning**: SHOULD be fixed or justified
3. **style**, **performance**, **portability**: Consider fixing for quality

---

## 4. PC-lint Plus Configuration

### Tool Overview

**PC-lint Plus** (formerly Gimpel PC-lint) is the **industry-standard MISRA C checker**:
- All 178 MISRA C:2012 rules
- All 16 MISRA C:2012 directives
- Highly configurable with `.lnt` files
- Excellent rule coverage and accuracy
- Fewer false positives than Cppcheck MISRA addon

**Strengths**:
- Comprehensive MISRA C:2012 support
- Customizable with project-specific configurations
- Good error messages with rationale
- Industry-proven for safety-critical software

**Limitations**:
- Commercial tool (requires license)
- Steeper learning curve (`.lnt` configuration files)

### Installation

**PC-lint Plus** is a commercial tool. Purchase from Gimpel Software:
- https://www.gimpel-online.com/pclintplus.html

**Typical installation**:
```bash
# Linux installation (example path)
export PATH=/opt/pclp/bin:$PATH

# Verify version
pclp64 --version
```

### Basic MISRA C Configuration (SIL 2)

**Create `project.lnt`** configuration file:

```
// project.lnt - MISRA C:2012 configuration for SIL 2

// Load MISRA C:2012 rules (Mandatory only for SIL 2)
au-misra3.lnt           // MISRA C:2012 rules

// Suppress Directives (not enforced for SIL 2)
-fdr                    // Do not report directive violations

// Suppress Required rules (enforced for SIL 3-4 only)
-e9026                  // Suppress Required rule checks (SIL 2)

// Suppress Advisory rules
-e9???                  // Suppress all Advisory rules

// Enable only Mandatory rules (143 rules)
// [Mandatory rules are enabled by default with au-misra3.lnt]

// Include paths
-i./include
-i./drivers/include

// Define preprocessor macros for target
+dSTM32F4
+d__ARM_ARCH_7EM__

// Source file extensions
+fsc                    // .c files are C source

// Output format
-width(0)               // No line width limit for output
-hF1                    // Output file:line format
```

**Run PC-lint Plus**:

```bash
pclp64 project.lnt src/*.c > pclint_report.txt 2>&1
```

### Maximum Rigor MISRA C Configuration (SIL 3-4)

**Create `project-sil4.lnt`** configuration file:

```
// project-sil4.lnt - MISRA C:2012 configuration for SIL 3-4

// Load MISRA C:2012 rules (all 178 rules + 16 directives)
au-misra3.lnt           // MISRA C:2012 rules

// Enable ALL rule categories
+fdr                    // Report directive violations (16 directives)
// Do NOT suppress Required or Advisory rules - enforce ALL

// Include paths
-i./include
-i./drivers/include
-i./CMSIS/Include       // ARM CMSIS headers

// Define preprocessor macros for target
+dSTM32F4
+d__ARM_ARCH_7EM__
+d__GNUC__              // If using GCC
+d__ARM_EABI__

// Source file extensions
+fsc                    // .c files are C source
+fhdr=h                 // .h files are headers

// Strong type checking (required for MISRA C)
+fll                    // Enable long long (if C99/C11)
+fas                    // Enable anonymous unions/structs (if needed)

// Output format
-width(0)               // No line width limit for output
-hF1                    // Output file:line format
-html(report.html)      // Generate HTML report
-xml(report.xml)        // Generate XML report

// Error message enhancement
-t                      // Tab character handling
-u                      // Suppress unused suppression messages
```

**Run PC-lint Plus (SIL 3-4)**:

```bash
pclp64 project-sil4.lnt src/*.c > pclint_sil4_report.txt 2>&1
```

### Deviation Handling

**MISRA C:2012 Deviations** are allowed for Required and Advisory rules (NOT Mandatory) if:
1. Deviation is formally documented
2. Rationale is provided
3. Risk assessment performed
4. Alternative measures described

**Create Deviation File** (`misra_deviations.lnt`):

```
// misra_deviations.lnt - Approved MISRA C deviations

// Deviation DEV-001: Rule 2.3 (Required) - Unused type declarations
// Rationale: Type defined for API consistency, not all variants use it
// Location: src/api.h:45
// Risk: Low - no functional impact
// Alternative: Document unused types
-esym(9003, unused_type_t)  // Suppress Rule 2.3 for specific type

// Deviation DEV-002: Rule 8.13 (Advisory) - Pointer should be const
// Rationale: Pointer passed to hardware driver that doesn't use const
// Location: src/hal/uart.c:89
// Risk: Low - function does not modify data
// Alternative: Wrapper function with const interface
-esym(9005, uart_send_buffer)  // Suppress Rule 8.13 for specific function
```

**Use deviations**:

```bash
pclp64 project-sil4.lnt misra_deviations.lnt src/*.c > pclint_report.txt 2>&1
```

**Important**: ALL deviations must be documented in `docs/deviations/MISRA-DEV-NNN.md` with formal approval.

### Interpreting PC-lint Plus Output

**Output Format**:

```
src/main.c  45  Error 9007: Side effects on right hand side of logical operator '||' [MISRA Rule 13.5 Required]
src/sensor.c  123  Error 9003: Could define variable 'sensor_data' at block scope [MISRA Rule 8.9 Advisory]
src/uart.c  67  Error 9005: Pointer parameter 'buffer' (line 67) could be declared as pointing to const [MISRA Rule 8.13 Advisory]
```

**Severity Interpretation**:
- `Error 90xx`: MISRA C:2012 rule violation
  - `9001-9143`: Rule violations (rule number = last 3 digits)
  - Mandatory rules: MUST be fixed (zero tolerance SIL 2+)
  - Required rules: MUST be fixed OR deviated (SIL 3-4)
  - Advisory rules: SHOULD be considered (SIL 3-4)

**Rule Categories**:
- **Mandatory** (143 rules): Zero violations for SIL 2+ (no deviations allowed)
- **Required** (35 rules): Zero violations OR documented deviations for SIL 3-4
- **Advisory** (109 rules): Should be followed for SIL 3-4, deviations allowed

**Summary Generation**:

```bash
# Count violations by severity
grep -c "Error 90" pclint_report.txt

# Count Mandatory violations (rules with "Required" that are actually Mandatory - check MISRA C:2012 document)
grep "Error 90" pclint_report.txt | grep "Required" | wc -l

# Generate summary report
python3 tools/metrics/misra_compliance.py pclint_report.txt > misra_summary.txt
```

---

## 5. Clang Static Analyzer Configuration

### Tool Overview

**Clang Static Analyzer** is a deep semantic analyzer focusing on:
- Path-sensitive analysis (tracks program paths)
- NULL pointer dereferences
- Use-after-free
- Memory leaks
- Division by zero
- Buffer overflows
- Security vulnerabilities

**Strengths**:
- Deep path-sensitive analysis (finds complex bugs)
- Excellent memory safety checking
- Part of LLVM project (well-maintained)
- HTML reports with execution paths

**Limitations**:
- Slower than Cppcheck (deep analysis takes time)
- May have false positives for complex code

### Installation

```bash
# Ubuntu/Debian
sudo apt install clang clang-tools

# Verify version (use LLVM 14+ for best results)
clang --version
scan-build --version
```

### Basic Configuration (SIL 0-2)

```bash
# Run on existing Makefile project
scan-build make

# Specify output directory
scan-build -o analysis_results make

# View HTML report
firefox analysis_results/*/index.html
```

### Advanced Configuration (SIL 3-4)

```bash
# Maximum rigor with all checkers
scan-build \
    -o analysis_results \
    --use-cc=clang --use-c++=clang++ \
    -enable-checker alpha \
    -enable-checker security \
    -enable-checker unix \
    -enable-checker core \
    -maxloop 10 \
    --status-bugs \
    -v \
    make clean all

# Options Explained:
# -enable-checker alpha: Enable experimental checkers (more thorough)
# -enable-checker security: Enable security checkers
# -enable-checker unix: Enable UNIX/POSIX API checkers
# -enable-checker core: Enable core checkers (NULL deref, div-by-zero, etc.)
# -maxloop 10: Analyze loop bodies up to 10 iterations (default 4)
# --status-bugs: Return non-zero exit status if bugs found
# -v: Verbose output
```

### Available Checkers

**List all checkers**:

```bash
clang -cc1 -analyzer-checker-help
```

**Key Checkers for SIL 3-4**:

| Checker | Description | Priority |
|---------|-------------|----------|
| `core.NullDereference` | NULL pointer dereference | **Critical** |
| `core.DivideZero` | Division by zero | **Critical** |
| `core.UndefinedBinaryOperatorResult` | Undefined binary operation result | **Critical** |
| `core.uninitialized.Assign` | Uninitialized value assignment | **Critical** |
| `core.uninitialized.Branch` | Branch on uninitialized value | **Critical** |
| `deadcode.DeadStores` | Dead store (assignment never read) | High |
| `security.insecureAPI.strcpy` | Insecure strcpy/strcat use | **Critical** |
| `security.insecureAPI.DeprecatedOrUnsafeBufferHandling` | Unsafe buffer handling | **Critical** |
| `unix.Malloc` | Memory management errors | High |
| `alpha.core.CastToStruct` | Dangerous struct casts | High |
| `alpha.security.ArrayBound` | Array out-of-bounds | **Critical** |

### Enabling Specific Checkers

```bash
# Enable specific checkers only
scan-build \
    -enable-checker core.NullDereference \
    -enable-checker core.DivideZero \
    -enable-checker core.uninitialized.Assign \
    -enable-checker security.insecureAPI.strcpy \
    -enable-checker alpha.security.ArrayBound \
    -o analysis_results \
    make
```

### Suppressing False Positives

Clang Static Analyzer has limited suppression mechanisms. Use:

**1. Assert-based suppression**:

```c
#include <assert.h>

void function(int* ptr) {
    // Clang will understand this assertion and not warn about NULL deref
    assert(ptr != NULL);
    *ptr = 42;  // No warning
}
```

**2. Explicit NULL checks**:

```c
void function(int* ptr) {
    if (ptr == NULL) {
        return;  // Early exit
    }
    *ptr = 42;  // Clang knows ptr is not NULL here
}
```

**3. Inline comments** (limited support):

```c
// Clang does not have inline suppression like cppcheck
// Instead, refactor code to make analysis clearer
```

### Interpreting Clang Analyzer Output

**HTML Report Structure**:

Open `analysis_results/[date]/index.html` in browser:

- Summary table with bug counts by type
- Each bug links to detailed report showing:
  - Bug type (e.g., "NULL pointer dereference")
  - File and line number
  - **Execution path** (shows how bug can be triggered)
  - Code context with highlighting

**Example Bug Report**:

```
Bug Type: Null pointer dereference
File: src/sensor.c
Line: 145
Path:
  1. Line 120: Assuming 'sensor' is null
  2. Line 125: Taking true branch (condition 'sensor == NULL' is true)
  3. Line 130: Entering function 'process_sensor'
  4. Line 145: Null pointer dereference (accessing 'sensor->value')
```

**Text Output** (if using `--status-bugs`):

```bash
scan-build: 5 bugs found.
scan-build: Run 'scan-view /path/to/analysis_results/...' to examine bug reports.
```

**Extract Summary**:

```bash
# Count bugs by type
grep -r "Bug Type:" analysis_results/*/report-*.html | sort | uniq -c
```

---

## 6. Lizard Complexity Analysis

### Tool Overview

**Lizard** is a code complexity analyzer supporting multiple languages including C:
- Cyclomatic Complexity (CCN)
- Function length (lines of code)
- Parameter count
- Nested depth

**Strengths**:
- Fast execution
- Multiple output formats (text, XML, HTML, CSV)
- Supports multiple languages
- Easy to integrate into CI/CD

**Limitations**:
- Does not analyze semantic issues (only structure)
- Cyclomatic complexity is an approximation (not precise CFG analysis)

### Installation

```bash
# Install via pip
pip3 install lizard

# Verify installation
lizard --version
```

### Basic Configuration (SIL 0-1)

```bash
# Analyze source directory with CCN threshold 20
lizard src/ -l c --CCN 20
```

### SIL 2 Configuration (CCN ≤ 15)

```bash
# Analyze with CCN threshold 15, show functions exceeding limit
lizard src/ -l c --CCN 15 --warning_only

# Output to XML
lizard src/ -l c --CCN 15 --xml > lizard_report.xml

# Output to HTML
lizard src/ -l c --CCN 15 --html > lizard_report.html
```

### SIL 3-4 Configuration (CCN ≤ 10 for SIL 4, ≤ 12 for SIL 3)

```bash
# SIL 4: CCN ≤ 10
lizard src/ -l c --CCN 10 --arguments 5 --length 150 --warning_only --xml > lizard_sil4_report.xml

# SIL 3: CCN ≤ 12
lizard src/ -l c --CCN 12 --arguments 5 --length 150 --warning_only --xml > lizard_sil3_report.xml

# Options Explained:
# -l c: Analyze C language only
# --CCN 10: Cyclomatic Complexity threshold (warn if exceeded)
# --arguments 5: Parameter count threshold (warn if >5 parameters)
# --length 150: Function length threshold (warn if >150 LOC)
# --warning_only: Show only functions exceeding thresholds
# --xml: Output XML format for automation
```

### Advanced Options

```bash
# Exclude test files
lizard src/ -l c --CCN 10 --exclude "*/tests/*" --exclude "*/test_*"

# Include nested functions in complexity
lizard src/ -l c --CCN 10 --modified

# Sort by complexity (descending)
lizard src/ -l c --sort cyclomatic_complexity

# Generate CSV for spreadsheet analysis
lizard src/ -l c --csv > lizard_report.csv
```

### Interpreting Lizard Output

**Text Output**:

```
================================================
  NLOC    CCN   token  PARAM  length  location  
------------------------------------------------
      45      6     89      3      50  calculate_speed@src/speed.c:120-170
      67     12    145      4      75  parse_message@src/protocol.c:200-275
     123     15    234      5     130  process_state@src/state.c:50-180
================================================
Total nloc   Avg.CCN  Avg.token  Fun Cnt  Warning cnt   Fun Rt   nloc Rt  
-----------  -------  ---------  -------  -----------   ------   -------  
      4567      6.2       89.5      156            3     0.98      0.95  

3 file(s) analyzed.
==========================================================================================
!! 3 functions exceed CCN threshold (>10)
!!   Line 200: parse_message@src/protocol.c, CCN = 12
!!   Line 50: process_state@src/state.c, CCN = 15
!!   Line 300: validate_config@src/config.c, CCN = 11
==========================================================================================
```

**Columns**:
- **NLOC**: Non-comment lines of code
- **CCN**: Cyclomatic Complexity Number
- **token**: Token count (indicator of function complexity)
- **PARAM**: Parameter count
- **length**: Total lines (including comments)
- **location**: Function name and file location

**XML Output** (for automation):

```xml
<?xml version="1.0" ?>
<cppncss>
  <measure type="Function">
    <item name="calculate_speed@src/speed.c:120-170">
      <value name="nloc">45</value>
      <value name="CCN">6</value>
      <value name="token">89</value>
      <value name="PARAM">3</value>
      <value name="length">50</value>
    </item>
  </measure>
</cppncss>
```

**Summary Statistics**:

```bash
# Generate summary report
python3 tools/metrics/complexity_summary.py lizard_report.xml
```

**Example summary**:

```
Complexity Summary:
- Total Functions: 156
- Average CCN: 6.2
- Maximum CCN: 15
- Functions with CCN ≤ 10: 153 (98%)
- Functions with CCN > 10: 3 (2%)
  - parse_message() CCN=12
  - process_state() CCN=15
  - validate_config() CCN=11

SIL 4 Target: CCN ≤ 10 for 100% functions
Status: FAIL (3 functions exceed threshold)
```

---

## 7. Defect Severity Classification

### EN 50128 Severity Mapping

**Critical**: Blocks phase gate, violates MANDATORY EN 50128 requirement, potential safety hazard

**High**: Violates Highly Recommended EN 50128 requirement, significant quality issue

**Medium**: Violates Recommended EN 50128 requirement, moderate quality issue

**Low**: Code style issue, minor quality improvement

**Info**: Informational, no action required

### Cppcheck Severity → EN 50128 Severity

| Cppcheck Severity | EN 50128 Severity | Action Required (SIL 3-4) |
|-------------------|-------------------|---------------------------|
| `error` | **Critical** | **MUST FIX** (zero tolerance) |
| `warning` | **High** | **SHOULD FIX** or justify |
| `style` | Medium | Consider fixing |
| `performance` | Low | Consider for optimization |
| `portability` | Low | Consider for portability |
| `information` | Info | Informational only |

### PC-lint Plus Severity → EN 50128 Severity

| MISRA C Rule Category | EN 50128 Severity | Action Required (SIL 3-4) |
|-----------------------|-------------------|---------------------------|
| **Mandatory** (143 rules) | **Critical** | **MUST FIX** (zero tolerance, no deviations) |
| **Required** (35 rules) | **High** | **MUST FIX** or document deviation |
| **Advisory** (109 rules) | Medium | **SHOULD CONSIDER** (deviations allowed) |

### Clang Analyzer Bug Type → EN 50128 Severity

| Clang Bug Type | EN 50128 Severity | Action Required (SIL 3-4) |
|----------------|-------------------|---------------------------|
| Null pointer dereference | **Critical** | **MUST FIX** |
| Division by zero | **Critical** | **MUST FIX** |
| Uninitialized value | **Critical** | **MUST FIX** |
| Use-after-free | **Critical** | **MUST FIX** |
| Buffer overflow | **Critical** | **MUST FIX** |
| Memory leak | **High** | **SHOULD FIX** (especially in safety functions) |
| Dead store | Medium | Consider fixing for clarity |
| Insecure API usage | **High** | **SHOULD FIX** (strcpy → strncpy) |

### Complexity Violation Severity

| CCN Violation | Target (SIL) | EN 50128 Severity | Action Required |
|---------------|--------------|-------------------|-----------------|
| CCN > 20 | SIL 0-1 | Medium | Consider refactoring |
| CCN > 15 | SIL 2 | **High** | **MUST REFACTOR** |
| CCN > 12 | SIL 3 | **High** | **MUST REFACTOR** |
| CCN > 10 | SIL 4 | **Critical** | **MUST REFACTOR** |

### Defect Triage Process

**1. Classify defect severity** (Critical, High, Medium, Low, Info)

**2. Assess safety impact**:
- Is this in a safety-critical function (SIL 3-4)?
- Could this cause hazardous behavior?
- Does this violate defensive programming principles?

**3. Determine action**:
- **Critical**: MUST fix before phase gate (block)
- **High**: SHOULD fix or provide justification/deviation
- **Medium**: Consider fixing or defer to later phase
- **Low/Info**: Optional improvement

**4. Document decision**:
- If fixed: Document fix in commit message, reference defect ID
- If deferred: Create defect tracking issue, assign to future phase
- If false positive: Document rationale, add suppression if appropriate
- If deviated (MISRA C): Create formal deviation document

### Example Defect Records

**Critical Defect**:

```markdown
**Defect ID**: DEF-VER-001
**Tool**: Cppcheck
**Severity**: Critical (error)
**Location**: src/braking.c:234
**Message**: "Uninitialized variable: braking_force"
**Safety Impact**: Variable used in safety-critical braking calculation could result in undefined braking behavior (Hazard HAZ-001).
**EN 50128 Violation**: Table A.3 Technique 2 "Defensive Programming" (HR SIL 3-4)
**Action**: **MUST FIX** - Initialize to safe default value (MAX_BRAKING_FORCE)
**Status**: Open
**Assigned to**: Implementer (IMP)
```

**High Defect**:

```markdown
**Defect ID**: DEF-VER-012
**Tool**: PC-lint Plus
**Severity**: High (MISRA C Required)
**Location**: src/uart.c:67
**Message**: "Error 9005: Pointer parameter 'buffer' could be declared as pointing to const [MISRA Rule 8.13 Required]"
**Safety Impact**: None (code quality issue)
**EN 50128 Violation**: MISRA C:2012 Rule 8.13 (Required)
**Action**: **FIX** or **DEVIATE** - Add const qualifier OR document deviation
**Status**: Open
**Assigned to**: Implementer (IMP)
```

**False Positive**:

```markdown
**Defect ID**: DEF-VER-025
**Tool**: Cppcheck
**Severity**: Medium (warning)
**Location**: src/hal/dma.c:145
**Message**: "Variable 'dma_status' is assigned a value that is never used"
**Rationale**: Variable assigned for debugging purposes (visible in debugger), intentionally not used in release build.
**Action**: **SUPPRESS** with inline comment
**Status**: Closed (suppressed)
**Suppression**:
```c
// cppcheck-suppress unusedVariable
// Rationale: Debug variable, visible in debugger, not used in release
volatile uint32_t dma_status = DMA1->ISR;
```
```

---

## 8. Result Interpretation Guidelines

### Cross-Tool Validation (SIL 3-4)

When multiple tools report the same issue, confidence is HIGH:

**Example**:

- Cppcheck: "src/sensor.c:145 - Possible null pointer dereference"
- Clang: "src/sensor.c:145 - NULL pointer dereference"
- **Interpretation**: HIGH confidence, MUST investigate and fix

### Tool-Specific Strengths

| Issue Type | Best Tool(s) | Interpretation |
|------------|--------------|----------------|
| MISRA C compliance | PC-lint Plus | Trust PC-lint as authoritative source |
| Uninitialized variables | Clang, Cppcheck | Both tools good, cross-check increases confidence |
| NULL pointer dereference | Clang (path-sensitive) | Clang most accurate (path analysis) |
| Complexity | Lizard | Lizard accurate for CCN measurement |
| Control flow | Cppcheck, Clang | Both tools complement each other |
| Memory leaks | Clang | Clang best for memory issues (path analysis) |

### Context-Aware Interpretation

**Example 1: Hardware Register Access**

```c
// False positive: Cppcheck warns "Variable 'status' is assigned but never used"
volatile uint32_t status = UART1->SR;  // Read clears interrupt flag
// Interpretation: SUPPRESS - Reading hardware register has side effect (clears flag)
```

**Example 2: Defensive NULL Check**

```c
// True positive: Clang warns "NULL pointer dereference"
if (ptr != NULL) {
    // ... (no use of ptr here)
}
// Later...
*ptr = 42;  // Clang warns: ptr could be NULL
// Interpretation: FIX - NULL check too far from use, add another check or restructure
```

**Example 3: Intentional Fall-Through**

```c
// Cppcheck warns "Switch case fall-through"
switch (state) {
    case STATE_INIT:
        initialize();
        // Intentional fall-through to STATE_READY
    case STATE_READY:
        ready();
        break;
}
// Interpretation: ANNOTATE with explicit comment
```

Fix:
```c
switch (state) {
    case STATE_INIT:
        initialize();
        /* FALLTHRU */ // Explicit fall-through annotation
    case STATE_READY:
        ready();
        break;
}
```

### Statistical Analysis

**Defect Density** (defects per KLOC):

```
Defect Density = (Total Defects) / (KLOC)

Example:
- Total Defects: 23 (after triage, excluding false positives)
- KLOC: 15.234 (from Lizard NLOC)
- Defect Density = 23 / 15.234 = 1.51 defects/KLOC
```

**Industry Benchmarks** (safety-critical software):
- Excellent: <1 defect/KLOC
- Good: 1-2 defects/KLOC
- Acceptable: 2-5 defects/KLOC
- Poor: >5 defects/KLOC

**Critical Defect Density**:

```
Critical Defect Density = (Critical Defects) / (KLOC)

Target for SIL 3-4: 0 critical defects/KLOC (zero tolerance)
```

---

## 9. False Positive Handling

### Identifying False Positives

**Criteria for False Positive**:
1. Tool reports issue, but code is actually correct
2. Tool misunderstands code intent (e.g., hardware register side effects)
3. Tool limitation (e.g., complex path analysis beyond tool capability)

**Process**:
1. Investigate reported issue thoroughly (assume tool is correct first)
2. If confident code is correct, document rationale
3. Add suppression with detailed comment
4. Record in defect tracking system as "False Positive (Suppressed)"

### Suppression Best Practices

**DO**:
- Add detailed comment explaining why suppression is justified
- Use tool-specific suppression mechanisms (inline or suppression file)
- Document all suppressions in verification report
- Review suppressions periodically (may become obsolete with code changes)

**DON'T**:
- Suppress without investigation (lazy suppression)
- Suppress critical issues without strong justification
- Suppress entire files (use specific line/function suppression)
- Over-suppress (if many suppressions needed, code may have real issues)

### Suppression Examples

**Cppcheck Inline Suppression**:

```c
// GOOD: Detailed rationale
// cppcheck-suppress uninitvar
// Rationale: Variable initialized by hardware DMA transfer before this function is called.
// DMA setup in init_dma() guarantees buffer[0..255] is valid.
uint8_t first_byte = buffer[0];

// BAD: No rationale
// cppcheck-suppress uninitvar
uint8_t first_byte = buffer[0];
```

**PC-lint Suppression**:

```c
// GOOD: Specific suppression with rationale
/*lint -e{9005} Rationale: Pointer cannot be const - passed to hardware driver API */
void uart_send(uint8_t* buffer, uint32_t length);

// BAD: Blanket suppression
/*lint -e* */  // Suppresses ALL warnings (NEVER do this)
```

### Suppression Tracking

**Suppression Log** (`docs/verification/suppression_log.md`):

```markdown
# Static Analysis Suppression Log

## Suppression SUP-001
- **Tool**: Cppcheck
- **Rule**: uninitvar
- **Location**: src/hal/dma.c:145
- **Message**: "Uninitialized variable: buffer[0]"
- **Rationale**: Variable initialized by DMA hardware before function call. DMA setup in init_dma() guarantees buffer validity.
- **Risk Assessment**: Low - DMA initialization is verified in integration testing.
- **Reviewer**: Jane Smith (VER)
- **Approved by**: Alice Brown (VMGR)
- **Date**: 2026-03-13

## Suppression SUP-002
- **Tool**: PC-lint Plus
- **Rule**: MISRA Rule 8.13 (Required)
- **Location**: src/hal/uart.c:67
- **Message**: "Pointer parameter 'buffer' could be declared const"
- **Rationale**: Pointer passed to vendor HAL library (ST HAL) which does not use const in API.
- **Risk Assessment**: Low - Function does not modify buffer, verified by code review.
- **Alternative Considered**: Wrapper function with const interface (deferred to Phase 8 maintenance).
- **Reviewer**: Jane Smith (VER)
- **Approved by**: Alice Brown (VMGR)
- **Date**: 2026-03-14
```

---

## 10. Thresholds and Targets by SIL

### SIL 0 (Advisory)

| Metric | Threshold | Action if Exceeded |
|--------|-----------|-------------------|
| MISRA C Mandatory Violations | N/A | Informational |
| Critical Static Analysis Issues | N/A | Informational |
| Cyclomatic Complexity (CCN) | >20 | Informational |
| Defect Density | N/A | Informational |

**Rationale**: SIL 0 is non-safety, advisory mode only.

### SIL 1 (Basic Quality)

| Metric | Threshold | Action if Exceeded |
|--------|-----------|-------------------|
| MISRA C Mandatory Violations | 0 | **Recommended**: Fix |
| Critical Static Analysis Issues | 0 | **Recommended**: Fix |
| Cyclomatic Complexity (CCN) | ≤20 | **Recommended**: Refactor |
| Defect Density | <5 defects/KLOC | **Recommended**: Improve |

**Rationale**: SIL 1 establishes basic quality practices.

### SIL 2 (Formal Quality)

| Metric | Threshold | Action if Exceeded |
|--------|-----------|-------------------|
| MISRA C Mandatory Violations | 0 | **MUST FIX** (zero tolerance) |
| MISRA C Required Violations | 0 OR deviated | **SHOULD FIX** or deviate |
| Critical Static Analysis Issues | 0 | **MUST FIX** (zero tolerance) |
| High Static Analysis Issues | 0 OR justified | **SHOULD FIX** or justify |
| Cyclomatic Complexity (CCN) | ≤15 | **MUST REFACTOR** |
| Defect Density | <2 defects/KLOC | **SHOULD IMPROVE** |

**Rationale**: SIL 2 requires formal quality measures per EN 50128.

### SIL 3 (High Safety)

| Metric | Threshold | Action if Exceeded |
|--------|-----------|-------------------|
| MISRA C Mandatory Violations | 0 | **MUST FIX** (zero tolerance, blocks phase gate) |
| MISRA C Required Violations | 0 OR deviated | **MUST FIX** or formal deviation |
| MISRA C Advisory Violations | 0 OR deviated | **SHOULD FIX** (deviations allowed) |
| Critical Static Analysis Issues | 0 | **MUST FIX** (zero tolerance, blocks phase gate) |
| High Static Analysis Issues | 0 OR justified | **MUST FIX** or formal justification |
| Cyclomatic Complexity (CCN) | ≤12 | **MUST REFACTOR** (blocks phase gate) |
| Defect Density | <1 defect/KLOC | **Target**: Excellent quality |
| Critical Defect Density | 0 | **MUST FIX** (zero critical defects) |

**Rationale**: SIL 3 requires independent verification, multiple tools, zero tolerance for critical issues (EN 50128 Table A.5, A.19).

### SIL 4 (Maximum Safety)

| Metric | Threshold | Action if Exceeded |
|--------|-----------|-------------------|
| MISRA C Mandatory Violations | 0 | **MUST FIX** (zero tolerance, blocks phase gate) |
| MISRA C Required Violations | 0 OR deviated | **MUST FIX** or formal deviation with risk assessment |
| MISRA C Advisory Violations | 0 OR deviated | **MUST CONSIDER** (deviations allowed) |
| Critical Static Analysis Issues | 0 | **MUST FIX** (zero tolerance, blocks phase gate) |
| High Static Analysis Issues | 0 | **MUST FIX** or formal justification with risk assessment |
| Cyclomatic Complexity (CCN) | ≤10 | **MUST REFACTOR** (zero tolerance, blocks phase gate) |
| Defect Density | <1 defect/KLOC | **Target**: Excellent quality |
| Critical Defect Density | 0 | **MUST FIX** (zero critical defects) |

**Rationale**: SIL 4 is maximum safety integrity, zero tolerance for issues that could compromise safety (EN 50128 Table A.1).

### Phase Gate Blocking Criteria (SIL 3-4)

**Phase gate BLOCKED if**:
1. Critical static analysis issues > 0 (ANY critical issue blocks)
2. MISRA C Mandatory violations > 0 (ANY mandatory violation blocks)
3. Cyclomatic complexity violations > 0 (ANY function exceeding CCN threshold blocks for SIL 4)
4. Critical defects unresolved (see defect severity classification)

**Phase gate CONDITIONAL if**:
1. High static analysis issues > 0 (require justification or fix plan)
2. MISRA C Required violations > 0 without deviations (require deviations or fix plan)
3. Cyclomatic complexity violations > 0 for SIL 3 (require refactoring plan)

---

## 11. Continuous Integration Setup

### CI/CD Pipeline Integration

**Example GitLab CI** (`.gitlab-ci.yml`):

```yaml
stages:
  - build
  - test
  - static-analysis
  - report

variables:
  EVIDENCE_DIR: "docs/reports/evidence/CI-${CI_PIPELINE_ID}"

# Stage 1: Build
build:
  stage: build
  script:
    - make clean
    - make all
  artifacts:
    paths:
      - build/
    expire_in: 1 week

# Stage 2: Unit Tests with Coverage
test:
  stage: test
  script:
    - make test COVERAGE=1
    - lcov --capture --directory . --output-file coverage.info
    - lcov --summary coverage.info
  artifacts:
    paths:
      - coverage.info
      - build/test/
    reports:
      coverage_report:
        coverage_format: cobertura
        path: coverage.xml
    expire_in: 1 week
  coverage: '/lines\.*: (\d+\.\d+)%/'

# Stage 3: Static Analysis
static-analysis:cppcheck:
  stage: static-analysis
  script:
    - mkdir -p ${EVIDENCE_DIR}/static-analysis
    - cppcheck --enable=all --addon=misra --xml --xml-version=2 src/ 2> ${EVIDENCE_DIR}/static-analysis/cppcheck_report.xml
    - cppcheck-htmlreport --file=${EVIDENCE_DIR}/static-analysis/cppcheck_report.xml --report-dir=${EVIDENCE_DIR}/static-analysis/cppcheck_html
    - python3 tools/ci/check_cppcheck.py ${EVIDENCE_DIR}/static-analysis/cppcheck_report.xml
  artifacts:
    paths:
      - ${EVIDENCE_DIR}/static-analysis/
    expire_in: 1 month
  allow_failure: false  # MUST pass for SIL 3-4

static-analysis:pclint:
  stage: static-analysis
  script:
    - mkdir -p ${EVIDENCE_DIR}/static-analysis
    - pclp64 project-sil4.lnt src/*.c > ${EVIDENCE_DIR}/static-analysis/pclint_report.txt 2>&1 || true
    - python3 tools/ci/check_misra.py ${EVIDENCE_DIR}/static-analysis/pclint_report.txt
  artifacts:
    paths:
      - ${EVIDENCE_DIR}/static-analysis/pclint_report.txt
    expire_in: 1 month
  allow_failure: false  # MUST pass for SIL 3-4

static-analysis:clang:
  stage: static-analysis
  script:
    - mkdir -p ${EVIDENCE_DIR}/static-analysis/clang_analysis
    - scan-build -o ${EVIDENCE_DIR}/static-analysis/clang_analysis --status-bugs make clean all
  artifacts:
    paths:
      - ${EVIDENCE_DIR}/static-analysis/clang_analysis/
    expire_in: 1 month
  allow_failure: false  # MUST pass for SIL 3-4

static-analysis:complexity:
  stage: static-analysis
  script:
    - mkdir -p ${EVIDENCE_DIR}/complexity
    - lizard src/ -l c --CCN 10 --xml > ${EVIDENCE_DIR}/complexity/lizard_report.xml
    - python3 tools/ci/check_complexity.py ${EVIDENCE_DIR}/complexity/lizard_report.xml --ccn-threshold 10
  artifacts:
    paths:
      - ${EVIDENCE_DIR}/complexity/
    expire_in: 1 month
  allow_failure: false  # MUST pass for SIL 4

# Stage 4: Generate Report
generate-report:
  stage: report
  script:
    - python3 tools/ci/generate_verification_summary.py ${EVIDENCE_DIR} > verification_summary.md
    - cat verification_summary.md
  artifacts:
    paths:
      - verification_summary.md
    expire_in: 1 month
  dependencies:
    - static-analysis:cppcheck
    - static-analysis:pclint
    - static-analysis:clang
    - static-analysis:complexity
    - test
```

### CI/CD Gating Scripts

**`tools/ci/check_cppcheck.py`** (fail if critical issues):

```python
#!/usr/bin/env python3
import sys
import xml.etree.ElementTree as ET

def check_cppcheck(xml_file):
    tree = ET.parse(xml_file)
    root = tree.getroot()
    
    critical_count = 0
    error_count = 0
    
    for error in root.findall('.//error'):
        severity = error.get('severity')
        if severity == 'error':
            error_count += 1
            print(f"ERROR: {error.get('msg')} at {error.find('location').get('file')}:{error.find('location').get('line')}")
            critical_count += 1
    
    print(f"\nCppcheck Summary:")
    print(f"  Total Errors: {error_count}")
    print(f"  Critical Issues: {critical_count}")
    
    if critical_count > 0:
        print("\n❌ FAIL: Critical issues found!")
        sys.exit(1)  # Fail CI pipeline
    else:
        print("\n✅ PASS: No critical issues")
        sys.exit(0)

if __name__ == "__main__":
    check_cppcheck(sys.argv[1])
```

**`tools/ci/check_misra.py`** (fail if mandatory violations):

```python
#!/usr/bin/env python3
import sys
import re

def check_misra(report_file):
    mandatory_violations = 0
    required_violations = 0
    
    with open(report_file, 'r') as f:
        for line in f:
            if 'MISRA' in line and 'Mandatory' in line:
                mandatory_violations += 1
                print(f"MANDATORY VIOLATION: {line.strip()}")
            elif 'MISRA' in line and 'Required' in line:
                required_violations += 1
    
    print(f"\nMISRA C Compliance Summary:")
    print(f"  Mandatory Violations: {mandatory_violations}")
    print(f"  Required Violations: {required_violations}")
    
    if mandatory_violations > 0:
        print("\n❌ FAIL: Mandatory MISRA C violations found!")
        sys.exit(1)  # Fail CI pipeline
    elif required_violations > 5:  # Allow up to 5 required violations (with deviations)
        print("\n⚠️ WARNING: Many required violations (document deviations)")
        sys.exit(1)
    else:
        print("\n✅ PASS: MISRA C Mandatory compliance achieved")
        sys.exit(0)

if __name__ == "__main__":
    check_misra(sys.argv[1])
```

**`tools/ci/check_complexity.py`** (fail if CCN exceeded):

```python
#!/usr/bin/env python3
import sys
import xml.etree.ElementTree as ET

def check_complexity(xml_file, ccn_threshold):
    tree = ET.parse(xml_file)
    root = tree.getroot()
    
    violations = []
    
    for item in root.findall('.//item'):
        ccn = int(item.find("./value[@name='CCN']").text)
        name = item.get('name')
        if ccn > ccn_threshold:
            violations.append((name, ccn))
    
    print(f"\nComplexity Analysis (CCN threshold: {ccn_threshold}):")
    print(f"  Total Functions: {len(root.findall('.//item'))}")
    print(f"  Violations: {len(violations)}")
    
    if violations:
        print("\nFunctions exceeding CCN threshold:")
        for name, ccn in violations:
            print(f"  ❌ {name}: CCN={ccn}")
        print(f"\n❌ FAIL: {len(violations)} function(s) exceed CCN threshold!")
        sys.exit(1)  # Fail CI pipeline
    else:
        print("\n✅ PASS: All functions within CCN threshold")
        sys.exit(0)

if __name__ == "__main__":
    check_complexity(sys.argv[1], int(sys.argv[3]))
```

---

## 12. Tool Qualification Requirements

### EN 50128 Tool Confidence Levels

**EN 50128 Section 6.7 "Software Tools"** defines tool qualification requirements.

**Tool Confidence Level (TCL)**:

| TCL | Description | Qualification Required |
|-----|-------------|------------------------|
| **T1** | Tool output inspected/verified by user | No formal qualification (output must be reviewed) |
| **T2** | Tool output used directly, tool verified in practice | **Qualification required**: Evidence of correct behavior |
| **T3** | Tool output used directly, tool safety-critical | **Full qualification required**: Formal verification, documentation |

### Static Analysis Tools Classification

| Tool | Typical TCL | Qualification Approach |
|------|-------------|------------------------|
| Cppcheck | **T1** | Output must be reviewed by verifier, no formal qualification needed |
| PC-lint Plus | **T2** | Qualification evidence: Industry use, vendor documentation, sample tests |
| Clang Static Analyzer | **T1** | Output must be reviewed by verifier, no formal qualification needed |
| Lizard | **T1** | Output must be reviewed by verifier (CCN calculation straightforward) |

**Rationale**:
- **T1 (Cppcheck, Clang, Lizard)**: Verifier inspects all tool output, verifies findings are correct, assesses false positives. Tool errors will be caught by human review.
- **T2 (PC-lint Plus)**: MISRA C checker output trusted (with spot-checks). Tool has industry track record, vendor qualification data available.

### Tool Qualification Documentation

For **T2 tools** (PC-lint Plus for SIL 3-4), create Tool Qualification Report:

**Tool Qualification Report Template** (`docs/tool-qualification/TQR-PC-lint-Plus.md`):

```markdown
# Tool Qualification Report: PC-lint Plus

**Tool Name**: PC-lint Plus  
**Vendor**: Gimpel Software (www.gimpel-online.com)  
**Version**: 2.1.0  
**Purpose**: MISRA C:2012 compliance checking  
**Tool Confidence Level**: T2  
**Qualification Date**: 2026-03-01  
**Qualified by**: Jane Smith (VER)  
**Approved by**: Alice Brown (VMGR)

## Tool Description

PC-lint Plus is a static analysis tool for C/C++ with comprehensive MISRA C:2012 support (all 178 rules + 16 directives).

## Tool Confidence Level Justification

**TCL T2** because:
- Tool output (MISRA C violations) is used directly in verification reports
- Tool findings trusted with spot-checks (not 100% manual review of all findings)
- Tool has established track record in safety-critical industries

## Qualification Approach

### 1. Vendor Documentation Review

- Vendor provides MISRA C:2012 compliance matrix
- Tool certified by MIRA (Motor Industry Research Association) for MISRA compliance
- Industry use: >10,000 installations in automotive, aerospace, medical, railway industries

### 2. Sample Test Suite

Test suite of 50 C code samples covering MISRA C:2012 rules:
- Positive tests: Code compliant with MISRA C (tool should report 0 violations)
- Negative tests: Code with intentional MISRA C violations (tool should detect all violations)

**Test Results**: 50/50 tests passed (100% accuracy)

### 3. Cross-Check with Manual Review

For critical project code (10% sample):
- Manual MISRA C review by independent verifier
- PC-lint Plus output compared to manual review findings
- Agreement: 98% (2% false positives, 0% false negatives)

**Conclusion**: PC-lint Plus is accurate and reliable for MISRA C checking.

### 4. Known Limitations

- False positives: ~2% (typically related to complex macros or vendor-specific extensions)
- False negatives: 0% observed in test suite
- Mitigation: Verifier reviews all PC-lint findings, assesses false positives

## Qualification Evidence

- Vendor MISRA C certification: `docs/tool-qualification/evidence/PC-lint-Plus-MISRA-Cert.pdf`
- Test suite results: `docs/tool-qualification/evidence/PC-lint-Plus-Test-Suite-Results.xlsx`
- Sample manual review comparison: `docs/tool-qualification/evidence/PC-lint-Plus-Cross-Check-Report.pdf`

## Qualification Validity

**Valid for**: PC-lint Plus version 2.x (major version)  
**Re-qualification required if**: Tool upgraded to version 3.x or configuration significantly changed

## Approval

**Qualified by**: _Jane Smith_ (VER) - 2026-03-01  
**Approved by**: _Alice Brown_ (VMGR) - 2026-03-01
```

### Tool Qualification for SIL Levels

| SIL Level | Tool Qualification Required |
|-----------|----------------------------|
| **SIL 0-1** | No formal qualification (T1 acceptable) |
| **SIL 2** | **Recommended**: Document tool usage and rationale |
| **SIL 3-4** | **MANDATORY**: Formal tool qualification for T2/T3 tools per EN 50128 Section 6.7 |

---

## Summary

Static analysis is **MANDATORY for SIL 3-4** (EN 50128 Table A.5, Table A.19) and requires:

1. **Multiple Tools**: Cppcheck, PC-lint Plus, Clang Static Analyzer, Lizard (SIL 3-4)
2. **Zero Tolerance**: Zero critical issues, zero MISRA C Mandatory violations (SIL 2+)
3. **Complexity Limits**: CCN ≤ 10 (SIL 4), CCN ≤ 12 (SIL 3), CCN ≤ 15 (SIL 2)
4. **Independent Verification**: Independent verifier reviews all tool output (SIL 3-4)
5. **Tool Qualification**: T2 tools (PC-lint Plus) require qualification evidence (SIL 3-4)
6. **CI/CD Integration**: Automated checks in CI pipeline, fail if thresholds exceeded

**For VER Agent**: Use these guidelines to configure tools correctly, interpret results accurately, and classify defects appropriately.

**For IMP Agent**: Use these guidelines to understand what static analysis will check and write compliant code from the start.

**For QUA Agent**: Use these guidelines to verify that VER has applied appropriate rigor and tool configuration for the project SIL level.

---

**END OF GUIDELINES**
