# Verification Tools Reference for EN 50128

**Purpose**: Comprehensive tool catalog with versions, capabilities, qualification requirements, and usage for EN 50128 verification.

**Scope**: All verification tools for SIL 0-4 projects.

**Audience**: Verifiers (VER), V&V Managers (VMGR), Implementers (IMP)

---

## Tool Catalog Summary

| Tool | Category | EN 50128 TCL | SIL Level | Purpose |
|------|----------|--------------|-----------|---------|
| **Cppcheck** | Static Analysis | T1 | All | General static analysis, control/data flow |
| **PC-lint Plus** | MISRA C | T2 | 2+ | MISRA C:2012 compliance (178 rules + 16 directives) |
| **Clang Static Analyzer** | Static Analysis | T1 | All | Deep semantic analysis, path-sensitive |
| **Lizard** | Complexity | T1 | All | Cyclomatic complexity (CCN), function metrics |
| **GCC** | Compiler | T1 | All | GNU C Compiler with warnings |
| **gcov** | Coverage | T1 | All | Statement, branch, condition coverage |
| **lcov** | Coverage Reporting | T1 | All | gcov result visualization (HTML reports) |
| **Valgrind** | Memory Analysis | T1 | 2+ | Memory leaks, invalid access (runtime) |
| **AddressSanitizer** | Memory Safety | T1 | 2+ | Memory errors (runtime, compile-time instrumentation) |
| **Git** | Version Control | T1 | All | Configuration management |
| **Unity** | Unit Testing | T1 | All | C unit test framework |
| **CMock** | Mocking | T1 | All | Mock generation for Unity |

---

## 1. Cppcheck

**Category**: Static Analysis  
**License**: GPL v3 (Open Source)  
**Website**: https://cppcheck.sourceforge.io/  
**Latest Version**: 2.13.0 (as of 2024)  
**EN 50128 Tool Confidence Level**: **T1** (output inspection required)

### Capabilities
- Control flow analysis (unreachable code, infinite loops)
- Data flow analysis (uninitialized variables, unused variables)
- NULL pointer dereference detection
- Buffer overflow detection
- MISRA C basic checking (with addon)
- XML/HTML output for automation

### Installation
```bash
# Ubuntu/Debian
sudo apt install cppcheck

# From source
git clone https://github.com/danmar/cppcheck.git
cd cppcheck && make && sudo make install
```

### Usage (SIL 3-4)
```bash
cppcheck --enable=all --addon=misra --xml --xml-version=2 src/ 2> cppcheck_report.xml
```

### Qualification Status
- **T1**: No formal qualification required
- **Verification**: Verifier must inspect all findings
- **Evidence**: Tool output archived as verification evidence

---

## 2. PC-lint Plus

**Category**: MISRA C Compliance  
**License**: Commercial (Gimpel Software)  
**Website**: https://www.gimpel-online.com/pclintplus.html  
**Latest Version**: 2.1.0 (as of 2024)  
**EN 50128 Tool Confidence Level**: **T2** (qualified in practice)

### Capabilities
- MISRA C:2012 all 178 rules + 16 directives
- Industry-standard MISRA C checker
- Highly configurable (.lnt files)
- Excellent rule coverage

### Installation
Commercial license required. Contact Gimpel Software.

### Usage (SIL 3-4)
```bash
pclp64 project-sil4.lnt src/*.c > pclint_report.txt 2>&1
```

### Qualification Status
- **T2**: Qualification evidence required for SIL 3-4
- **Industry Use**: >10,000 installations in safety-critical domains
- **MIRA Certified**: Tool certified by MIRA for MISRA C compliance
- **Qualification Report**: Create Tool Qualification Report (see `resources/static-analysis-guidelines.md` Section 12)

---

## 3. Clang Static Analyzer

**Category**: Static Analysis (Semantic)  
**License**: Apache 2.0 (Open Source, LLVM)  
**Website**: https://clang-analyzer.llvm.org/  
**Latest Version**: LLVM 18.x (as of 2024)  
**EN 50128 Tool Confidence Level**: **T1** (output inspection required)

### Capabilities
- Path-sensitive analysis
- NULL pointer dereference detection
- Use-after-free detection
- Memory leak detection
- Division by zero detection
- Security vulnerability detection
- HTML reports with execution paths

### Installation
```bash
sudo apt install clang clang-tools
```

### Usage (SIL 3-4)
```bash
scan-build -o analysis_results \
    -enable-checker alpha \
    -enable-checker security \
    --status-bugs make clean all
```

### Qualification Status
- **T1**: No formal qualification required
- **Verification**: Verifier reviews HTML reports with execution paths

---

## 4. Lizard

**Category**: Complexity Analysis  
**License**: MIT (Open Source)  
**Website**: https://github.com/terryyin/lizard  
**Latest Version**: 1.17.x (as of 2024)  
**EN 50128 Tool Confidence Level**: **T1** (output inspection required)

### Capabilities
- Cyclomatic Complexity (CCN)
- Function length (LOC)
- Parameter count
- Nested depth
- Multi-language support (C, C++, Python, Java, etc.)
- XML/HTML/CSV output

### Installation
```bash
pip3 install lizard
```

### Usage (SIL 3-4)
```bash
# SIL 4: CCN ≤ 10
lizard src/ -l c --CCN 10 --warning_only --xml > lizard_report.xml

# SIL 3: CCN ≤ 12
lizard src/ -l c --CCN 12 --warning_only --xml > lizard_report.xml
```

### Qualification Status
- **T1**: No formal qualification required
- **Verification**: Verifier reviews complexity metrics

---

## 5. GCC (GNU Compiler Collection)

**Category**: Compiler  
**License**: GPL v3 (Open Source)  
**Website**: https://gcc.gnu.org/  
**Latest Version**: GCC 13.x (as of 2024)  
**EN 50128 Tool Confidence Level**: **T1** (warnings inspected)

### Capabilities
- C11 compilation
- Extensive warning flags (`-Wall`, `-Wextra`, `-Werror`)
- Optimization levels
- Debug information generation (`-g`)
- Code coverage instrumentation (`-fprofile-arcs`, `-ftest-coverage`)

### Installation
```bash
sudo apt install gcc build-essential
```

### Usage (SIL 3-4)
```bash
# Compilation with maximum warnings
gcc -std=c11 -Wall -Wextra -Werror -pedantic -Wconversion \
    -O2 -g -fprofile-arcs -ftest-coverage \
    -o program src/*.c
```

### Warning Flags (SIL 3-4 MANDATORY)
- `-Wall`: Enable all common warnings
- `-Wextra`: Enable extra warnings
- `-Werror`: Treat warnings as errors (MANDATORY SIL 3-4)
- `-pedantic`: Strict ISO C compliance
- `-Wconversion`: Warn on implicit type conversions (MANDATORY SIL 3-4)

---

## 6. gcov

**Category**: Code Coverage  
**License**: GPL v3 (part of GCC)  
**Website**: https://gcc.gnu.org/onlinedocs/gcc/Gcov.html  
**EN 50128 Tool Confidence Level**: **T1** (output inspection required)

### Capabilities
- Statement coverage
- Branch coverage
- Condition coverage (with `-fbranch-probabilities`)
- Integrates with GCC

### Installation
Bundled with GCC.

### Usage (SIL 3-4)
```bash
# Compile with coverage
gcc -fprofile-arcs -ftest-coverage -o program src/*.c

# Run tests
./program

# Generate coverage report
gcov -b -c src/*.c
```

### Coverage Targets (SIL 3-4)
- Statement: 100% MANDATORY
- Branch: 100% MANDATORY
- Condition: 100% MANDATORY

---

## 7. lcov

**Category**: Coverage Visualization  
**License**: GPL v2 (Open Source)  
**Website**: https://github.com/linux-test-project/lcov  
**EN 50128 Tool Confidence Level**: **T1** (output inspection required)

### Capabilities
- gcov result aggregation
- HTML report generation with line-by-line coverage
- Coverage percentage calculation

### Installation
```bash
sudo apt install lcov
```

### Usage (SIL 3-4)
```bash
# Capture coverage data
lcov --capture --directory . --output-file coverage.info

# Generate HTML report
genhtml coverage.info --output-directory coverage_html

# View in browser
firefox coverage_html/index.html
```

---

## 8. Valgrind

**Category**: Memory Analysis (Runtime)  
**License**: GPL v2 (Open Source)  
**Website**: https://valgrind.org/  
**EN 50128 Tool Confidence Level**: **T1** (output inspection required)

### Capabilities
- Memory leak detection
- Invalid memory access detection
- Use of uninitialized values
- Double-free detection
- Stack overflow detection

### Installation
```bash
sudo apt install valgrind
```

### Usage (SIL 3-4)
```bash
valgrind --leak-check=full --show-leak-kinds=all \
         --track-origins=yes --verbose \
         --log-file=valgrind_report.txt \
         ./program
```

### Limitations
- **Runtime tool**: Requires test execution (not pure static analysis)
- **Slowdown**: 10-50x slower execution
- **Target platform**: May not work on embedded targets (use host testing)

---

## 9. AddressSanitizer (ASan)

**Category**: Memory Safety (Runtime)  
**License**: Part of LLVM/GCC (Open Source)  
**EN 50128 Tool Confidence Level**: **T1** (output inspection required)

### Capabilities
- Buffer overflow detection
- Use-after-free detection
- Use-after-return detection
- Double-free detection
- Memory leak detection (with LeakSanitizer)

### Installation
Bundled with GCC 4.8+ and Clang 3.1+.

### Usage (SIL 3-4)
```bash
# Compile with AddressSanitizer
gcc -fsanitize=address -fno-omit-frame-pointer -O1 -g \
    -o program_asan src/*.c

# Run tests
./program_asan
```

### Advantages over Valgrind
- Faster (2-3x slowdown vs. 10-50x)
- Better accuracy
- More detailed error reports

---

## 10. Git

**Category**: Version Control / Configuration Management  
**License**: GPL v2 (Open Source)  
**Website**: https://git-scm.com/  
**EN 50128 Tool Confidence Level**: **T1** (usage audited)

### Capabilities
- Version control
- Branching and merging
- Commit history
- Tagging (for baselines)
- Diff and blame

### Installation
```bash
sudo apt install git
```

### Usage (Configuration Management)
```bash
# Tag baseline (Phase gate)
git tag -a BASELINE-PHASE5-001 -m "Phase 5 verified and approved"

# Commit verification report
git add docs/reports/DOC-IMPVER-2026-001.md
git commit -m "Add Phase 5 Source Code Verification Report (APPROVED)"
```

---

## 11. Unity Test Framework

**Category**: Unit Testing  
**License**: MIT (Open Source)  
**Website**: https://github.com/ThrowTheSwitch/Unity  
**EN 50128 Tool Confidence Level**: **T1** (test results inspected)

### Capabilities
- Lightweight C unit testing framework
- Assertion macros
- Test fixtures (setUp/tearDown)
- Embedded-friendly (no dynamic allocation)

### Installation
```bash
# Clone repository
git clone https://github.com/ThrowTheSwitch/Unity.git

# Include in project
cp Unity/src/unity.* project/test/
```

### Usage
```c
#include "unity.h"

void test_calculate_speed_valid(void) {
    TEST_ASSERT_EQUAL_UINT32(100, calculate_speed(&sensor, 1000));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_calculate_speed_valid);
    return UNITY_END();
}
```

---

## Tool Selection Matrix by SIL

| SIL Level | Mandatory Tools | Highly Recommended | Optional |
|-----------|-----------------|-------------------|----------|
| **SIL 0** | GCC | Cppcheck, Lizard | - |
| **SIL 1** | GCC, Cppcheck | Lizard, gcov/lcov | Valgrind |
| **SIL 2** | GCC, Cppcheck, PC-lint Plus, gcov/lcov, Lizard | Valgrind, AddressSanitizer | Clang |
| **SIL 3-4** | **GCC, Cppcheck, PC-lint Plus, Clang, Lizard, gcov/lcov** | **Valgrind, AddressSanitizer** | - |

---

## Tool Qualification Requirements by SIL

| SIL Level | T1 Tools | T2 Tools | T3 Tools |
|-----------|----------|----------|----------|
| **SIL 0-1** | No qualification | No qualification | N/A |
| **SIL 2** | Output inspection | Document tool usage | N/A |
| **SIL 3-4** | Output inspection MANDATORY | **Qualification Report MANDATORY** | Full qualification |

**T2 Tools for SIL 3-4** (Qualification Report required):
- PC-lint Plus (MISRA C checker)

**All other tools**: T1 (output inspection by verifier sufficient)

---

## Summary

For SIL 3-4 verification, the **mandatory toolchain** is:

1. **Cppcheck** - General static analysis
2. **PC-lint Plus** - MISRA C:2012 compliance (T2, requires qualification)
3. **Clang Static Analyzer** - Deep semantic analysis
4. **Lizard** - Complexity analysis (CCN ≤ 10 for SIL 4)
5. **GCC** - Compilation with `-Wall -Wextra -Werror -Wconversion`
6. **gcov + lcov** - Code coverage (100% statement/branch/condition)
7. **Git** - Configuration management

All tool output MUST be archived as verification evidence and reviewed by independent verifier (VER → VMGR for SIL 3-4).

**END OF REFERENCE**
