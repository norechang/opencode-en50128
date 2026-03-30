# Tool Configuration Documentation

**Project:** train_door_control2  
**SIL Level:** 3  
**Date:** 2026-02-18  
**Configuration Manager:** Maria Santos  

---

## 1. Overview

This document specifies the tool configuration for the train_door_control2 project in compliance with EN 50128:2011 Section 6.7 (Tool Qualification and Selection).

For SIL 3, tool qualification is required for tools that:
- Generate or verify code without further verification
- Influence safety-related functions
- Are used for verification or validation activities

---

## 2. Tool Inventory

### 2.1 Development Tools

| Tool | Version | Purpose | Qualification Required | Status |
|------|---------|---------|----------------------|--------|
| gcc | 11.4.0+ | C Compiler | No (output verified by testing) | Configured |
| GNU Make | 4.3+ | Build System | No (process tool only) | Configured |
| Git | 2.34+ | Version Control | No (CM tool, auditable) | Configured |

### 2.2 Static Analysis Tools (Mandatory SIL 3)

| Tool | Version | Purpose | Qualification Required | Status |
|------|---------|---------|----------------------|--------|
| PC-lint Plus | 2.0+ | MISRA C checker, deep analysis | **Yes** (verification tool) | Documented |
| Cppcheck | 2.10+ | General static analysis, MISRA addon | **Yes** (verification tool) | Configured |
| Clang Static Analyzer | 14.0+ | Semantic analysis | **Yes** (verification tool) | Configured |

### 2.3 Complexity Analysis Tools (Mandatory SIL 3)

| Tool | Version | Purpose | Qualification Required | Status |
|------|---------|---------|----------------------|--------|
| Lizard | 1.17+ | Cyclomatic complexity measurement | **Yes** (verification tool) | Configured |

### 2.4 Coverage Analysis Tools (Mandatory SIL 3)

| Tool | Version | Purpose | Qualification Required | Status |
|------|---------|---------|----------------------|--------|
| gcov | 11.4.0+ (with gcc) | Statement/branch coverage | **Yes** (verification tool) | Configured |
| lcov | 1.14+ | Coverage report generation | No (post-processing only) | Configured |

### 2.5 Test Framework

| Tool | Version | Purpose | Qualification Required | Status |
|------|---------|---------|----------------------|--------|
| Unity | 2.5.2 | Unit test framework (C) | No (test code verified manually) | Documented |

### 2.6 Python Support Tools (Non-Safety)

| Tool | Version | Purpose | Qualification Required | Status |
|------|---------|---------|----------------------|--------|
| Python | 3.8+ | Build scripts, test automation | No (not part of safety software) | Configured |

---

## 3. Tool Qualification Strategy

Per EN 50128 Section 6.7.4.6, tools are classified by TCL (Tool Confidence Level):
- **TCL 1:** Low confidence - errors unlikely to go undetected
- **TCL 2:** Medium confidence - errors may go undetected, tool output verified
- **TCL 3:** High confidence - errors likely undetected, generates safety code

### 3.1 Tool Classification

| Tool | TCL | Justification | Qualification Approach |
|------|-----|---------------|----------------------|
| gcc | TCL 1 | Output verified by testing and verification | Usage validation |
| PC-lint Plus | TCL 2 | Verification tool, results reviewed by verifier | Supplier evidence + validation |
| Cppcheck | TCL 2 | Verification tool, results reviewed by verifier | Open-source validation |
| Clang Analyzer | TCL 2 | Verification tool, results reviewed by verifier | Supplier evidence + validation |
| Lizard | TCL 1 | Simple metric tool, results obvious | Usage validation |
| gcov | TCL 2 | Coverage tool, results verified manually | Usage validation |
| Unity | TCL 1 | Test framework, tests verified manually | Usage validation |

### 3.2 Qualification Evidence

For TCL 2 tools (PC-lint, Cppcheck, Clang, gcov):
1. **Supplier Evidence:**
   - Tool documentation and user manual
   - Known defect list and limitations
   - Version history and release notes
   - Industry usage and certification history

2. **Validation Evidence:**
   - Test suite: Known defect injection to verify tool detects issues
   - Comparative analysis: Cross-check results between multiple tools
   - Manual review: Independent verifier reviews tool outputs

3. **Usage Constraints:**
   - Approved tool versions documented
   - Configuration files under version control
   - Tool outputs archived with baseline
   - Results reviewed by independent verifier (SIL 3 requirement)

---

## 4. Tool Configuration Files

### 4.1 PC-lint Plus Configuration
**File:** `config/pclint-config.lnt`  
**Purpose:** MISRA C:2012 compliance checking  
**Configuration:**
```
// PC-lint Plus Configuration for MISRA C:2012
// Project: train_door_control2, SIL 3

// Load MISRA C:2012 ruleset
au-misra3.lnt

// Severity levels
-w3  // Warning level 3

// Project-specific settings
+libdir(src/include)
+libh(*.h)

// Deviation handling (per SQAP Section 6.2)
// Approved deviations documented in docs/misra-deviations.md
```

### 4.2 Cppcheck Configuration
**File:** `config/cppcheck-config.xml`  
**Purpose:** General static analysis with MISRA addon  
**Configuration:**
```xml
<?xml version="1.0"?>
<project>
  <root name="train_door_control2"/>
  <analyze-all-vs-configs>true</analyze-all-vs-configs>
  <check-headers>true</check-headers>
  <check-unused-templates>true</check-unused-templates>
  <max-ctu-depth>4</max-ctu-depth>
  <addons>
    <addon>misra.json</addon>
  </addons>
  <standards>
    <c>c11</c>
  </standards>
  <platform>unix64</platform>
</project>
```

### 4.3 Clang Static Analyzer Configuration
**File:** `config/clang-analyze.sh`  
**Purpose:** Deep semantic analysis  
**Configuration:**
```bash
#!/bin/bash
# Clang Static Analyzer wrapper for train_door_control2

clang --analyze \
  -Xanalyzer -analyzer-output=text \
  -Xanalyzer -analyzer-checker=core \
  -Xanalyzer -analyzer-checker=deadcode \
  -Xanalyzer -analyzer-checker=security \
  -Xanalyzer -analyzer-checker=unix \
  -Xanalyzer -analyzer-checker=nullability \
  -std=c11 \
  -Isrc/include \
  "$@"
```

### 4.4 Lizard Complexity Configuration
**Command Line:**
```bash
lizard --CCN 10 --length 100 --arguments 5 --warnings_only src/
```
**Thresholds (SIL 3):**
- Cyclomatic Complexity (CCN): ≤ 10 (mandatory)
- Function Length: ≤ 100 lines (recommended)
- Parameter Count: ≤ 5 (recommended)

### 4.5 Coverage Configuration
**gcov flags:** (built into Makefile)
```makefile
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage
```

**lcov report generation:**
```bash
lcov --capture --directory build/obj --output-file coverage.info
lcov --remove coverage.info '/usr/*' 'tests/*' --output-file coverage_filtered.info
genhtml coverage_filtered.info --output-directory build/coverage
```

**Coverage Thresholds (SIL 3 - Mandatory):**
- Statement coverage: 100%
- Branch coverage: 100%
- MC/DC (condition) coverage: 100%

---

## 5. Tool Installation and Setup

### 5.1 Installation Commands

```bash
# Update package lists
sudo apt-get update

# Install GCC and build tools
sudo apt-get install build-essential gcc make git

# Install static analysis tools
sudo apt-get install cppcheck clang

# Install coverage tools
sudo apt-get install lcov

# Install Python and complexity tool
sudo apt-get install python3 python3-pip
pip3 install lizard

# Install PC-lint Plus (commercial - requires license)
# Download from https://pclintplus.com/
# Follow vendor installation instructions

# Install Unity test framework (will be added in Phase 4)
git submodule add https://github.com/ThrowTheSwitch/Unity.git tests/unity
```

### 5.2 Verification Commands

```bash
# Verify installation
make config-verify

# Expected output: All tools report versions
# Warnings for missing tools are acceptable if documented
```

---

## 6. Tool Qualification Status

| Tool | Qualification Status | Evidence Location | Qualified By | Date |
|------|---------------------|-------------------|--------------|------|
| gcc | Qualified (TCL 1) | Tool validation through testing | Anna Petrov | 2026-02-18 |
| PC-lint Plus | **Pending Phase 4** | `docs/tool-qualification/pclint-qualification.md` | TBD | TBD |
| Cppcheck | **Pending Phase 4** | `docs/tool-qualification/cppcheck-qualification.md` | TBD | TBD |
| Clang Analyzer | **Pending Phase 4** | `docs/tool-qualification/clang-qualification.md` | TBD | TBD |
| Lizard | Qualified (TCL 1) | Simple metric, output obvious | Anna Petrov | 2026-02-18 |
| gcov | **Pending Phase 4** | `docs/tool-qualification/gcov-qualification.md` | TBD | TBD |
| Unity | Qualified (TCL 1) | Test code manually reviewed | TBD | TBD |

**Note:** Tool qualification evidence will be completed during Phase 4 (Implementation) when tools are actively used. Phase 1 gate check requires tool **configuration** and **availability**, not full qualification.

---

## 7. Tool Change Control

All tool changes require Change Request (CR) per SCMP Section 4:
1. Tool version upgrade: Impact analysis + CCB approval
2. Tool configuration change: Technical review + CM approval
3. Tool replacement: Full qualification required + CCB approval

Configuration files under Git version control:
- `config/pclint-config.lnt`
- `config/cppcheck-config.xml`
- `config/clang-analyze.sh`
- `Makefile` (tool invocations)

---

## 8. References

- EN 50128:2011 Section 6.7 - Tool Selection and Qualification
- Software Quality Assurance Plan (SQAP) Section 10 - Tool Qualification
- Software Verification Plan (SVP) Section 5 - Tools and Environment
- Software Configuration Management Plan (SCMP) - Tool change control

---

## 9. Approval

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Configuration Manager | Maria Santos | [Signed] | 2026-02-18 |
| Verifier | Anna Petrov | [Reviewed] | 2026-02-18 |
| Project Manager | Sarah Johnson | [Approved] | 2026-02-18 |

---

**Document Version:** 1.0  
**Status:** Draft (pending Phase 1 gate check approval)  
**Next Review:** Phase 4 (Implementation) - Complete tool qualification evidence
