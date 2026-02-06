---
name: en50128-verification
description: EN 50128 software verification techniques and static analysis for C
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  language: C
  section: "6.2"
  sil_applicability: "0-4"
---

## What I do

I provide verification techniques, static analysis patterns, and evidence collection methods required by EN 50128 Section 6.2:
- Independent verification for SIL 3-4 (mandatory)
- Static analysis (mandatory SIL 3-4)
- Control flow and data flow analysis (mandatory SIL 3-4)
- Traceability verification (mandatory SIL 3-4)
- Metrics collection and analysis
- Verification evidence collection

## When to use me

Use this skill when:
- Performing software verification activities
- Running static analysis on C code
- Verifying traceability matrices
- Collecting verification evidence
- Analyzing code metrics
- Preparing verification reports

## Verification Techniques (EN 50128 Table A.5)

**EN 50128 Section 6.2, 7.3, Table A.5** defines verification and testing techniques.

**Verification Techniques (subset of Table A.5):**

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | Formal Proof | D.29 | - | R | HR |
| 2 | Probabilistic Testing | D.44 | R | R | - |
| 3 | **Static Analysis** | Table A.19 | - | HR | **M** |
| 5 | Metrics | D.37 | - | R | HR |
| 7 | **Traceability** | D.58 | R | HR | **M** |
| 9 | Software Error Effect Analysis | D.25 | - | R | HR |
| 10 | Software Fault Tree Analysis | D.25 | - | R | HR |

**Mandatory for SIL 3-4:**
- **Static Analysis (3)** - **MANDATORY** (see Table A.19 below)
- **Traceability (7)** - **MANDATORY**

**Highly Recommended for SIL 3-4:**
- Formal Proof, Metrics, Software Error Effect Analysis, Fault Tree Analysis

**Approved Combination (SIL 3-4):**
- **3, 5, 7, 8 + one from {1, 2, 6}**
- (Static Analysis, Metrics, Traceability, [Testing] + Formal Proof OR Probabilistic Testing)

**Independence Requirements:**
- **SIL 3-4:** Verification **MUST** be performed by independent verifier (not developer/designer/implementer)

**Standard Reference:** `std/EN50128-2011.md` Section 6.2, Table A.5

## Static Analysis Techniques (EN 50128 Table A.19)

**EN 50128 Annex A, Table A.19** defines static analysis techniques:

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

**Mandatory for SIL 3-4:**
- **Control Flow Analysis (2)** - **MANDATORY**
- **Data Flow Analysis (3)** - **MANDATORY**

**Highly Recommended for SIL 3-4:**
- Boundary Value Analysis, Range Checking, Semantic Analysis, Code Review, Fagan Inspection, Complexity Metrics

**Tools for Static Analysis:**
- **PC-lint Plus:** MISRA C compliance, control/data flow
- **Cppcheck:** General static analysis
- **Clang Static Analyzer:** Deep analysis
- **Lizard:** Complexity metrics
- **SonarQube:** Code quality metrics

**Requirements:**
- Static Analysis is **MANDATORY** for SIL 3-4
- Control Flow and Data Flow Analysis are **MANDATORY** for SIL 3-4
- Tools SHALL be qualified per Annex C
- Analysis results SHALL be documented in verification reports

**Standard Reference:** `std/EN50128-2011.md` Annex A, Table A.19

## Verification Overview

**Independent Verification**: MANDATORY for SIL 3-4 (Highly Recommended for SIL 2)
- Verifier must be independent from designer and implementer
- Verification activities performed throughout lifecycle
- Evidence-based verification

## Static Analysis (Mandatory SIL 3-4)

### PC-lint Plus Configuration

```bash
# Run PC-lint Plus with MISRA C:2012
pclp64 \
    -i"$PROJECT_ROOT/include" \
    --misra3 \
    +ffn \
    -b \
    au-misra3.lnt \
    source.c

# Generate HTML report
pclp64 --misra3 --html=report.html source.c
```

**PC-lint Configuration File** (`pclint.lnt`):
```
// MISRA C:2012 compliance
+libclass(angle, foreign)
-strong(AJX)
+fll
-width(120)

// SIL-specific rules
// SIL 3-4: Complexity limit 10
-esym(818, *)  // Could be pointer to const
```

### Cppcheck with MISRA Addon

```bash
# Run Cppcheck with MISRA C:2012
cppcheck \
    --enable=all \
    --addon=misra \
    --suppress=missingIncludeSystem \
    --inline-suppr \
    --template='{file}:{line}: {severity}: {message} [{id}]' \
    --xml \
    --xml-version=2 \
    source.c 2> cppcheck_report.xml

# Generate HTML report
cppcheck-htmlreport \
    --file=cppcheck_report.xml \
    --report-dir=cppcheck_html \
    --source-dir=.
```

**Cppcheck Project File** (`cppcheck-project.xml`):
```xml
<?xml version="1.0" encoding="UTF-8"?>
<project>
    <paths>
        <dir name="src"/>
    </paths>
    <exclude>
        <path name="test/"/>
    </exclude>
    <libraries>
        <library>std</library>
    </libraries>
    <defines>
        <define name="TARGET_PLATFORM=RAILWAY"/>
        <define name="SIL_LEVEL=3"/>
    </defines>
</project>
```

### Clang Static Analyzer

```bash
# Run Clang Static Analyzer
clang --analyze \
    -Xanalyzer -analyzer-output=text \
    -Xanalyzer -analyzer-checker=core \
    -Xanalyzer -analyzer-checker=deadcode \
    -Xanalyzer -analyzer-checker=security \
    -Xanalyzer -analyzer-checker=unix \
    source.c

# Or use scan-build
scan-build -o analysis_results make
```

### Splint (Secure Programming Lint)

```bash
# Run splint for secure programming checks
splint \
    +posixlib \
    +checks \
    -warnposix \
    -exportlocal \
    source.c
```

## Cyclomatic Complexity Analysis

### Using Lizard

```bash
# Analyze complexity
lizard \
    --CCN 10 \
    --length 100 \
    --arguments 5 \
    --warnings_only \
    src/

# Generate HTML report
lizard -o complexity_report.html \
    --CCN 10 \
    src/

# Check specific file
lizard -w source.c
```

**Complexity Limits by SIL**:
```bash
# SIL 0-1: CCN <= 20
lizard --CCN 20 src/

# SIL 2: CCN <= 15
lizard --CCN 15 src/

# SIL 3-4: CCN <= 10
lizard --CCN 10 src/
```

### Python Script for Complexity Verification

```python
#!/usr/bin/env python3
"""Verify cyclomatic complexity meets SIL requirements."""

import sys
import subprocess
import json

SIL_COMPLEXITY_LIMITS = {
    0: 20,
    1: 20,
    2: 15,
    3: 10,
    4: 10
}

def check_complexity(source_dir, sil_level):
    """Check that all functions meet complexity limit."""
    limit = SIL_COMPLEXITY_LIMITS.get(sil_level, 10)
    
    result = subprocess.run(
        ['lizard', '--CCN', str(limit), '--warnings_only', source_dir],
        capture_output=True,
        text=True
    )
    
    if result.returncode != 0:
        print(f"ERROR: Functions exceed complexity limit ({limit}) for SIL {sil_level}")
        print(result.stdout)
        return False
    
    print(f"SUCCESS: All functions meet SIL {sil_level} complexity limit ({limit})")
    return True

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: check_complexity.py <source_dir> <sil_level>")
        sys.exit(1)
    
    source_dir = sys.argv[1]
    sil_level = int(sys.argv[2])
    
    if not check_complexity(source_dir, sil_level):
        sys.exit(1)
```

## Coverage Verification

### gcov/lcov for Coverage Analysis

```bash
# Compile with coverage instrumentation
gcc -fprofile-arcs -ftest-coverage -O0 source.c -o test

# Run tests
./test

# Generate coverage data
gcov source.c

# Generate HTML report with lcov
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_html

# Check coverage thresholds
lcov --summary coverage.info
```

### Python Script for Coverage Verification

```python
#!/usr/bin/env python3
"""Verify test coverage meets SIL requirements."""

import sys
import subprocess
import re

SIL_COVERAGE_REQUIREMENTS = {
    0: {'statement': 80, 'branch': 70},
    1: {'statement': 90, 'branch': 80},
    2: {'statement': 100, 'branch': 100},
    3: {'statement': 100, 'branch': 100, 'condition': 100},
    4: {'statement': 100, 'branch': 100, 'condition': 100}
}

def check_coverage(coverage_file, sil_level):
    """Check coverage meets SIL requirements."""
    requirements = SIL_COVERAGE_REQUIREMENTS.get(sil_level, {})
    
    # Parse lcov summary
    result = subprocess.run(
        ['lcov', '--summary', coverage_file],
        capture_output=True,
        text=True
    )
    
    # Extract coverage percentages
    lines_match = re.search(r'lines\.*:\s+([\d.]+)%', result.stdout)
    branches_match = re.search(r'branches\.*:\s+([\d.]+)%', result.stdout)
    
    if not lines_match or not branches_match:
        print("ERROR: Could not parse coverage data")
        return False
    
    line_coverage = float(lines_match.group(1))
    branch_coverage = float(branches_match.group(1))
    
    # Check requirements
    passed = True
    
    if line_coverage < requirements.get('statement', 0):
        print(f"FAIL: Statement coverage {line_coverage}% < {requirements['statement']}%")
        passed = False
    else:
        print(f"PASS: Statement coverage {line_coverage}% >= {requirements['statement']}%")
    
    if branch_coverage < requirements.get('branch', 0):
        print(f"FAIL: Branch coverage {branch_coverage}% < {requirements['branch']}%")
        passed = False
    else:
        print(f"PASS: Branch coverage {branch_coverage}% >= {requirements['branch']}%")
    
    return passed

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: check_coverage.py <coverage.info> <sil_level>")
        sys.exit(1)
    
    if not check_coverage(sys.argv[1], int(sys.argv[2])):
        sys.exit(1)
```

## MISRA C Compliance Verification

### MISRA C:2012 Rule Categories

**Mandatory Rules**: Must be followed (no deviations)
**Required Rules**: Should be followed (deviations require justification)
**Advisory Rules**: Recommended (deviations acceptable)

### Common MISRA C Violations to Check

```c
// Rule 8.7: Functions/objects should have internal linkage
// VIOLATION: Function not declared static
void helper_function(void);  // Should be static if only used in this file

// CORRECT:
static void helper_function(void);

// Rule 10.1: Operands shall not be of inappropriate essential type
// VIOLATION: Implicit type conversion
uint8_t a = 255;
uint8_t b = a + 1;  // Overflow

// CORRECT:
uint8_t a = 255U;
uint16_t temp = (uint16_t)a + 1U;
uint8_t b = (temp > 255U) ? 255U : (uint8_t)temp;

// Rule 11.5: Conversion from pointer to void into pointer to object
// VIOLATION: Cast from void* without explicit cast
void* ptr = get_buffer();
uint8_t* data = ptr;  // Implicit conversion

// CORRECT:
void* ptr = get_buffer();
uint8_t* data = (uint8_t*)ptr;  // Explicit cast

// Rule 14.4: The controlling expression of an if statement shall have boolean type
// VIOLATION: Non-boolean condition
uint32_t value = get_value();
if (value) {  // Should be explicit comparison
    // ...
}

// CORRECT:
uint32_t value = get_value();
if (value != 0U) {
    // ...
}

// Rule 17.7: Return value of function shall be used
// VIOLATION: Ignoring return value
read_sensor(&value);  // Return value ignored

// CORRECT:
error_t err = read_sensor(&value);
if (err != SUCCESS) {
    handle_error(err);
}

// Rule 21.3: malloc/free shall not be used
// VIOLATION: Dynamic memory
uint8_t* buffer = malloc(size);

// CORRECT (SIL 2+):
static uint8_t buffer[BUFFER_SIZE];
```

### MISRA Deviation Process

When MISRA rule deviation is necessary:

1. **Document Deviation**:
```c
/* MISRA Deviation: Rule 11.5
 * Justification: Hardware register access requires pointer cast
 * Risk Assessment: Low - register address is fixed and validated
 * Approved by: [Name], [Date]
 */
volatile uint32_t* reg = (volatile uint32_t*)HARDWARE_REG_ADDR;
```

2. **Log in Deviation Report**:
```
Deviation ID: DEV-001
Rule: MISRA C:2012 Rule 11.5
File: hardware.c:45
Justification: Hardware register access requires pointer cast
Alternative: None available for memory-mapped I/O
Risk: Low - address validated at build time
Approval: Safety Manager, 2024-01-15
```

## Verification Checklist

### Requirements Traceability
- [ ] All requirements traced to design elements
- [ ] All design elements traced to code
- [ ] All code traced to tests
- [ ] Bidirectional traceability verified

### Code Quality
- [ ] Static analysis run (PC-lint/Cppcheck)
- [ ] Zero critical issues
- [ ] All warnings reviewed
- [ ] MISRA C compliance verified
- [ ] Deviations documented and approved

### Complexity
- [ ] Cyclomatic complexity within limits
  - SIL 0-1: ≤ 20
  - SIL 2: ≤ 15
  - SIL 3-4: ≤ 10
- [ ] Function length reasonable (≤ 100 lines recommended)
- [ ] Nesting depth reasonable (≤ 4 levels)

### Testing
- [ ] All unit tests pass
- [ ] Coverage requirements met
  - SIL 2: 100% statement + branch
  - SIL 3-4: 100% statement + branch + condition
- [ ] Boundary values tested
- [ ] Error conditions tested

### Documentation
- [ ] Code comments adequate
- [ ] Design rationale documented
- [ ] Safety considerations documented
- [ ] MISRA deviations documented

### Memory Safety
- [ ] No dynamic allocation (SIL 2+)
- [ ] No recursion (highly recommended SIL 3-4)
- [ ] Buffer bounds checked
- [ ] Pointer validity checked
- [ ] Stack usage within limits

## Verification Report Template

```markdown
# Software Verification Report

## Project Information
- Project Name: [Name]
- Software Component: [Component]
- SIL Level: [0-4]
- Verification Date: [Date]
- Verifier: [Name] (Independent: Yes/No)

## Verification Activities

### 1. Static Analysis
- **Tool**: PC-lint Plus 2.0
- **Configuration**: MISRA C:2012, SIL 3 rules
- **Results**: 
  - Critical Issues: 0
  - Warnings: 5 (all reviewed and justified)
  - MISRA Deviations: 2 (documented in DEV-001, DEV-002)

### 2. Complexity Analysis
- **Tool**: Lizard 1.17
- **Limit**: CCN ≤ 10 (SIL 3)
- **Results**: 
  - Maximum CCN: 8 (function: process_safety_state)
  - Average CCN: 4.2
  - Passed: YES

### 3. Coverage Analysis
- **Tool**: gcov/lcov 1.15
- **Requirements**: 100% statement, branch, condition (SIL 3)
- **Results**:
  - Statement Coverage: 100%
  - Branch Coverage: 100%
  - Condition Coverage: 100%
  - Passed: YES

### 4. Traceability Verification
- All requirements traced to code: YES
- All code traced to tests: YES
- Bidirectional traceability complete: YES

## Verification Conclusion
- Overall Result: PASS
- Verification Complete: YES
- Ready for Validation: YES

## Approvals
- Verifier: [Signature], [Date]
- Project Manager: [Signature], [Date]
```

## Automated Verification Script

```python
#!/usr/bin/env python3
"""Complete verification workflow for EN 50128."""

import sys
import subprocess
import os

def run_verification(source_dir, sil_level):
    """Run all verification checks."""
    print(f"=== EN 50128 Verification for SIL {sil_level} ===\n")
    
    results = {}
    
    # 1. Static Analysis
    print("1. Running static analysis (Cppcheck)...")
    result = subprocess.run(
        ['cppcheck', '--enable=all', '--addon=misra', source_dir],
        capture_output=True
    )
    results['static_analysis'] = (result.returncode == 0)
    
    # 2. Complexity Check
    print("2. Checking cyclomatic complexity...")
    complexity_limits = {0: 20, 1: 20, 2: 15, 3: 10, 4: 10}
    limit = complexity_limits.get(sil_level, 10)
    result = subprocess.run(
        ['lizard', '--CCN', str(limit), '--warnings_only', source_dir],
        capture_output=True
    )
    results['complexity'] = (result.returncode == 0)
    
    # 3. Coverage Check (if coverage.info exists)
    if os.path.exists('coverage.info'):
        print("3. Verifying test coverage...")
        result = subprocess.run(
            ['lcov', '--summary', 'coverage.info'],
            capture_output=True,
            text=True
        )
        # Parse and check coverage (simplified)
        results['coverage'] = ('100.0%' in result.stdout)
    else:
        print("3. Coverage file not found (skipping)")
        results['coverage'] = None
    
    # 4. Summary
    print("\n=== Verification Results ===")
    for check, passed in results.items():
        if passed is None:
            status = "SKIPPED"
        elif passed:
            status = "PASS"
        else:
            status = "FAIL"
        print(f"{check}: {status}")
    
    # Overall result
    all_passed = all(r for r in results.values() if r is not None)
    print(f"\nOverall: {'PASS' if all_passed else 'FAIL'}")
    
    return 0 if all_passed else 1

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: verify.py <source_dir> <sil_level>")
        sys.exit(1)
    
    sys.exit(run_verification(sys.argv[1], int(sys.argv[2])))
```

## Tool Integration in Build System

### Makefile Integration

```makefile
# Verification targets
.PHONY: verify verify-static verify-complexity verify-coverage

# Complete verification
verify: verify-static verify-complexity verify-coverage
	@echo "=== All Verification Checks Passed ==="

# Static analysis
verify-static:
	cppcheck --enable=all --addon=misra --suppress=missingIncludeSystem src/
	clang --analyze src/*.c

# Complexity check
verify-complexity:
	lizard --CCN $(COMPLEXITY_LIMIT) --warnings_only src/

# Coverage check
verify-coverage:
	lcov --summary coverage.info
	@python3 tools/check_coverage.py coverage.info $(SIL_LEVEL)

# MISRA compliance
verify-misra:
	pclp64 --misra3 src/*.c
```

### CMake Integration

```cmake
# Verification targets
find_program(CPPCHECK cppcheck)
find_program(LIZARD lizard)
find_program(LCOV lcov)

if(CPPCHECK)
    add_custom_target(verify-static
        COMMAND ${CPPCHECK} --enable=all --addon=misra src/
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

if(LIZARD)
    add_custom_target(verify-complexity
        COMMAND ${LIZARD} --CCN ${COMPLEXITY_LIMIT} --warnings_only src/
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

# Add to verification target
add_custom_target(verify
    DEPENDS verify-static verify-complexity verify-coverage
)
```

## References

- EN 50128:2011 Section 6.4 (Software Verification)
- EN 50128:2011 Table A.5 (Verification Techniques)
- MISRA C:2012 Guidelines for C
- ISO/IEC 9899:2018 (C Standard)
