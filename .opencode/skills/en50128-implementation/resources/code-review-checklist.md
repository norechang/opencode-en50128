# Code Review Checklist for EN 50128 Railway Safety Software

**Purpose**: Comprehensive checklist for reviewing C code in EN 50128-compliant railway safety software development. Covers completeness, correctness, consistency, EN 50128 compliance, MISRA C, safety, quality, traceability, tool validation, review process, and references.

**Scope**: Code review during implementation phase (Phase 4) - applies to all peer reviews, QUA reviews, and VER reviews

**Audience**: Implementers (IMP - self-review), Peer Reviewers (PEER), Quality Assurance (QUA), Verifiers (VER)

**EN 50128 Reference**:
- Section 6.5 "Software Quality Assurance"
- Table A.9, Technique 7 "Software Reviews" (Highly Recommended all SILs)
- Section 7.5.3 "Code Review"

**Related Documents**:
- `workflows/code-review-workflow.md` - Step-by-step code review workflow
- `resources/misra-c-coding-patterns.md` - MISRA C compliant patterns
- `resources/common-pitfalls.md` - Common violations and fixes

---

## Table of Contents

1. [How to Use This Checklist](#1-how-to-use-this-checklist)
2. [Completeness Checklist (12 items)](#2-completeness-checklist)
3. [Correctness Checklist (15 items)](#3-correctness-checklist)
4. [Consistency Checklist (10 items)](#4-consistency-checklist)
5. [EN 50128 Compliance Checklist (12 items)](#5-en-50128-compliance-checklist)
6. [MISRA C Compliance Checklist (20 items)](#6-misra-c-compliance-checklist)
7. [Safety Checklist (18 items)](#7-safety-checklist)
8. [Quality Checklist (15 items)](#8-quality-checklist)
9. [Traceability Checklist (8 items)](#9-traceability-checklist)
10. [Tool Validation Checklist (6 items)](#10-tool-validation-checklist)
11. [Review Process Checklist (8 items)](#11-review-process-checklist)
12. [References](#12-references)

**Total Checklist Items**: 124 items

---

## 1. How to Use This Checklist

### 1.1 Review Roles and Responsibilities

**Author (IMP) - Self-Review**:
- Complete **all sections** before submitting for peer review
- Mark items as ✓ (compliant), ✗ (non-compliant), N/A (not applicable)
- Document non-compliance issues and remediation plan
- **Tool**: Use Workflow Manager CLI to initiate self-review

**Peer Reviewer (PEER)**:
- Review completeness, correctness, consistency (Sections 2-4)
- Verify MISRA C compliance (Section 6)
- Check basic safety patterns (Section 7)
- Focus on **readability, maintainability, testability**
- **SIL Level**: All SIL levels (0-4)

**Quality Assurance (QUA)**:
- Review ALL sections (Sections 2-11)
- Verify EN 50128 compliance (Section 5)
- Verify MISRA C compliance with static analysis results (Section 6)
- Check traceability completeness (Section 9)
- Ensure tool validation performed (Section 10)
- **SIL Level**: Mandatory for SIL 2+, Recommended for SIL 0-1

**Verifier (VER)** - Independent Review (SIL 3-4):
- Review ALL sections with focus on safety and compliance
- Verify static analysis results (Section 6, 10)
- Verify safety patterns implemented correctly (Section 7)
- Verify independent testing feasible (Section 8)
- **SIL Level**: MANDATORY for SIL 3-4, Highly Recommended for SIL 2

### 1.2 Review Workflow

```
┌──────────────┐
│ Author (IMP) │ 1. Self-review with checklist
│  Self-Review │    ✓ Sections 2-8 minimum
└──────┬───────┘    ✓ Fix obvious issues
       │
       ▼
┌──────────────┐
│ PEER Review  │ 2. Peer review (same team)
│              │    ✓ Sections 2-4, 6, 7
└──────┬───────┘    ✓ Provide feedback
       │
       ▼
┌──────────────┐
│ QUA Review   │ 3. Quality Assurance review
│              │    ✓ ALL sections (2-11)
└──────┬───────┘    ✓ Approve or reject
       │
       ▼ (SIL 3-4 only)
┌──────────────┐
│ VER Review   │ 4. Independent Verifier review
│ (Independent)│    ✓ ALL sections with safety focus
└──────┬───────┘    ✓ Final approval
       │
       ▼
┌──────────────┐
│   APPROVED   │ Code ready for integration
└──────────────┘
```

### 1.3 Checklist Notation

- **✓** - Item checked and compliant
- **✗** - Item checked and non-compliant (document issue)
- **N/A** - Item not applicable to this code
- **?** - Item uncertain (requires discussion)

### 1.4 Non-Compliance Handling

**For each ✗ (non-compliant item)**:
1. Document issue in review comments
2. Assign severity: **Critical** / **Major** / **Minor**
3. Require remediation before approval (Critical, Major)
4. Allow minor issues with justification (Minor)

**Severity Definitions**:
- **Critical**: Safety impact, MISRA mandatory violation, undefined behavior → **MUST FIX**
- **Major**: Quality impact, testability issue, MISRA required violation → **SHOULD FIX**
- **Minor**: Style issue, readability issue, MISRA advisory violation → **MAY FIX**

---

## 2. Completeness Checklist

**Purpose**: Verify all required code artifacts present

| # | Item | ✓/✗/N/A | Comments |
|---|------|---------|----------|
| 2.1 | Header file (`.h`) exists for public interfaces | | |
| 2.2 | Source file (`.c`) exists with implementation | | |
| 2.3 | Unit test file (`test_<module>.c`) exists | | |
| 2.4 | All functions declared in header have implementation in source | | |
| 2.5 | All public functions have doxygen-style comments | | |
| 2.6 | Module header comment includes purpose, author, date, requirements | | |
| 2.7 | Function header comments include purpose, parameters, return values, errors | | |
| 2.8 | Copyright notice present in header and source files | | |
| 2.9 | Include guards present in header file (`#ifndef MODULE_H`) | | |
| 2.10 | All external dependencies (includes) documented | | |
| 2.11 | All error codes defined and documented | | |
| 2.12 | Module initialization and shutdown functions provided (if stateful) | | |

**Review Notes**:
```
[Reviewer adds notes here about completeness issues]
```

---

## 3. Correctness Checklist

**Purpose**: Verify code implements requirements correctly

| # | Item | ✓/✗/N/A | Comments |
|---|------|---------|----------|
| 3.1 | Code implements all requirements in Software Requirements Specification (DOC-5) | | |
| 3.2 | Code matches design in Software Design Specification (DOC-10) | | |
| 3.3 | All function parameters validated (NULL checks, range checks) | | |
| 3.4 | All return values from function calls checked (MISRA Rule 17.7) | | |
| 3.5 | All error paths return appropriate error codes | | |
| 3.6 | All arithmetic operations check for overflow/underflow | | |
| 3.7 | All division operations check for divide-by-zero | | |
| 3.8 | All array accesses have bounds checks | | |
| 3.9 | All pointers validated before dereference | | |
| 3.10 | All variables initialized before use (MISRA Rule 9.1) | | |
| 3.11 | All loops have termination conditions (no infinite loops) | | |
| 3.12 | All switch statements have default case (MISRA Rule 16.4) | | |
| 3.13 | All state machine transitions are valid | | |
| 3.14 | All resource allocations have corresponding deallocations (if applicable) | | |
| 3.15 | Logic correctly implements requirements (no off-by-one errors, etc.) | | |

**Review Notes**:
```
[Reviewer adds notes here about correctness issues]
```

---

## 4. Consistency Checklist

**Purpose**: Verify code follows project conventions and style

| # | Item | ✓/✗/N/A | Comments |
|---|------|---------|----------|
| 4.1 | Naming conventions followed (functions, variables, types, constants) | | |
| 4.2 | Indentation consistent (spaces/tabs, 4 spaces per level) | | |
| 4.3 | Brace style consistent (K&R, Allman, etc.) | | |
| 4.4 | Comment style consistent (// vs /* */) | | |
| 4.5 | Error codes consistent with project error code enum | | |
| 4.6 | Return types consistent (error_t for functions that can fail) | | |
| 4.7 | Include order consistent (own header, system, project) | | |
| 4.8 | Type usage consistent (uint32_t, not unsigned int) | | |
| 4.9 | Formatting consistent with project clang-format / coding standard | | |
| 4.10 | Module structure consistent with other modules (init, process, shutdown) | | |

**Review Notes**:
```
[Reviewer adds notes here about consistency issues]
```

---

## 5. EN 50128 Compliance Checklist

**Purpose**: Verify code complies with EN 50128 requirements

| # | Item | ✓/✗/N/A | Comments | SIL |
|---|------|---------|----------|-----|
| 5.1 | Code follows structured programming (no goto, single entry/exit) | | | 3-4 M |
| 5.2 | Code uses modular approach (functions ≤ 60 lines) | | | 2+ M |
| 5.3 | Code uses defensive programming (input validation, error checking) | | | 3-4 HR |
| 5.4 | Code complexity ≤ 10 cyclomatic complexity (SIL 3-4), ≤ 15 (SIL 2) | | | 2+ |
| 5.5 | Code uses no dynamic memory allocation (malloc/free) | | | 2+ M |
| 5.6 | Code uses no recursion | | | 3-4 HR |
| 5.7 | Code uses design and coding standards (MISRA C) | | | 3-4 M |
| 5.8 | Code is analyzable (no complex pointer arithmetic, unions, bit-fields) | | | 3-4 M |
| 5.9 | Code has traceability to requirements (comments with REQ-IDs) | | | 3-4 M |
| 5.10 | Code has unit tests achieving required coverage (100% SIL 3-4) | | | 3-4 M |
| 5.11 | Code has static analysis report (Cppcheck, PC-lint) | | | 3-4 M |
| 5.12 | Code review completed per EN 50128 Section 6.5 | | | All HR |

**Review Notes**:
```
[Reviewer adds notes here about EN 50128 compliance issues]
```

---

## 6. MISRA C Compliance Checklist

**Purpose**: Verify MISRA C:2012 mandatory and required rules compliance

### 6.1 Type Safety (4 items)

| # | Rule | Item | ✓/✗/N/A | Comments |
|---|------|------|---------|----------|
| 6.1 | D.4.6 | All integer types are fixed-width (uint32_t, not int) | | |
| 6.2 | R.10.1-10.8 | No implicit type conversions (explicit casts with range check) | | |
| 6.3 | R.10.4 | No mixed signed/unsigned operations | | |
| 6.4 | R.12.5 | sizeof() operator used correctly | | |

### 6.2 Pointer and Array Safety (5 items)

| # | Rule | Item | ✓/✗/N/A | Comments |
|---|------|------|---------|----------|
| 6.5 | R.1.3 | All pointers checked for NULL before dereference | | |
| 6.6 | R.18.1 | All array accesses have bounds checks | | |
| 6.7 | R.18.4 | No pointer arithmetic (except documented deviations) | | |
| 6.8 | R.11.8 | No cast removing const or volatile | | |
| 6.9 | R.11.1 | No conversions between function pointer and other types | | |

### 6.3 Control Flow (4 items)

| # | Rule | Item | ✓/✗/N/A | Comments |
|---|------|------|---------|----------|
| 6.10 | R.15.1 | No goto statements | | |
| 6.11 | R.16.4 | All switch statements have default case | | |
| 6.12 | R.16.3 | No switch fallthrough (or documented with comment) | | |
| 6.13 | R.14.4 | No infinite loops (or documented with break condition) | | |

### 6.4 Functions (3 items)

| # | Rule | Item | ✓/✗/N/A | Comments |
|---|------|------|---------|----------|
| 6.14 | R.8.2 | All functions have prototype in header | | |
| 6.15 | R.17.7 | All function return values checked | | |
| 6.16 | R.17.2 | No recursion | | |

### 6.5 Variables (2 items)

| # | Rule | Item | ✓/✗/N/A | Comments |
|---|------|------|---------|----------|
| 6.17 | R.9.1 | All variables initialized at declaration | | |
| 6.18 | R.8.7 | Internal functions/variables declared static | | |

### 6.6 Standard Library (2 items)

| # | Rule | Item | ✓/✗/N/A | Comments |
|---|------|------|---------|----------|
| 6.19 | R.21.3 | No malloc/calloc/realloc/free (SIL 2+) | | |
| 6.20 | R.21.6 | No stdio.h functions (except snprintf) | | |

**Static Analysis Results**:
```
[Paste Cppcheck/PC-lint output summary here]

Example:
Cppcheck 2.13.0
  - 0 mandatory violations
  - 0 required violations
  - 2 advisory violations (documented deviations)
```

**Review Notes**:
```
[Reviewer adds notes here about MISRA C compliance issues]
```

---

## 7. Safety Checklist

**Purpose**: Verify defensive programming and safety patterns implemented

### 7.1 Input Validation (4 items)

| # | Item | ✓/✗/N/A | Comments |
|---|------|---------|----------|
| 7.1 | NULL pointer checks: All pointer parameters checked for NULL | | |
| 7.2 | Range validation: All numeric inputs validated against min/max | | |
| 7.3 | Plausibility checks: Sensor values checked for plausibility (not stuck, not out-of-physics) | | |
| 7.4 | Array bounds: All array indices validated before access | | |

### 7.2 Error Handling (3 items)

| # | Item | ✓/✗/N/A | Comments |
|---|------|---------|----------|
| 7.5 | Return value checking: All function return values checked (MISRA 17.7) | | |
| 7.6 | Error propagation: Errors propagated to caller (not silently ignored) | | |
| 7.7 | Error logging: Errors logged for diagnostics (if logging available) | | |

### 7.3 Safe Arithmetic (4 items)

| # | Item | ✓/✗/N/A | Comments |
|---|------|---------|----------|
| 7.8 | Overflow detection: Signed addition/subtraction checked for overflow | | |
| 7.9 | Multiplication overflow: Multiplication checked for overflow | | |
| 7.10 | Division by zero: All division operations check denominator != 0 | | |
| 7.11 | Shift count validation: Shift counts validated (0 to width-1) | | |

### 7.4 Hardware Fault Detection (3 items)

| # | Item | ✓/✗/N/A | Comments |
|---|------|---------|----------|
| 7.12 | Watchdog: Watchdog timer implemented and kicked regularly | | |
| 7.13 | Read-back verification: Critical writes verified with read-back | | |
| 7.14 | Memory integrity: Memory integrity checks (CRC, parity, ECC) implemented | | |

### 7.5 Redundancy (2 items)

| # | Item | ✓/✗/N/A | Comments |
|---|------|---------|----------|
| 7.15 | Dual-channel: Critical signals processed in dual channels (if required) | | |
| 7.16 | Voting: Triple modular redundancy (TMR) or voting implemented (if required) | | |

### 7.6 Fail-Safe (2 items)

| # | Item | ✓/✗/N/A | Comments |
|---|------|---------|----------|
| 7.17 | Fail-safe state: System enters safe state on error detection | | |
| 7.18 | Error recovery: Error recovery procedure implemented (or deliberate no-recovery) | | |

**Review Notes**:
```
[Reviewer adds notes here about safety issues]
```

---

## 8. Quality Checklist

**Purpose**: Verify code quality, maintainability, testability

### 8.1 Readability (4 items)

| # | Item | ✓/✗/N/A | Comments |
|---|------|---------|----------|
| 8.1 | Variable names descriptive and meaningful (not `x`, `tmp`, `val`) | | |
| 8.2 | Function names describe purpose clearly (`sensor_read`, not `read`) | | |
| 8.3 | Magic numbers replaced with named constants (#define or const) | | |
| 8.4 | Code commented adequately (not over-commented, not under-commented) | | |

### 8.2 Maintainability (4 items)

| # | Item | ✓/✗/N/A | Comments |
|---|------|---------|----------|
| 8.5 | Functions single-purpose (do one thing well) | | |
| 8.6 | No code duplication (DRY principle - Don't Repeat Yourself) | | |
| 8.7 | Module coupling low (minimal dependencies between modules) | | |
| 8.8 | Module cohesion high (related functions grouped together) | | |

### 8.3 Testability (4 items)

| # | Item | ✓/✗/N/A | Comments |
|---|------|---------|----------|
| 8.9 | Functions testable (no hidden dependencies, no global state mutations) | | |
| 8.10 | Unit tests exist for all functions | | |
| 8.11 | Unit tests achieve required coverage (100% SIL 3-4, 95% SIL 2) | | |
| 8.12 | Test mocks/stubs provided for external dependencies | | |

### 8.4 Performance (3 items)

| # | Item | ✓/✗/N/A | Comments |
|---|------|---------|----------|
| 8.13 | No obvious performance issues (unnecessary loops, allocations) | | |
| 8.14 | Execution time bounded (no unbounded loops, recursion) | | |
| 8.15 | Memory usage bounded (no dynamic allocation, fixed stack usage) | | |

**Review Notes**:
```
[Reviewer adds notes here about quality issues]
```

---

## 9. Traceability Checklist

**Purpose**: Verify traceability to requirements and design

| # | Item | ✓/✗/N/A | Comments |
|---|------|---------|----------|
| 9.1 | Module header lists all requirements implemented (REQ-XXX-NNN) | | |
| 9.2 | Each function comment lists requirements it implements | | |
| 9.3 | Traceability Manager database updated (code → requirements) | | |
| 9.4 | All requirements in SRS have corresponding code implementation | | |
| 9.5 | All code traces to design specification (SDS) | | |
| 9.6 | Unit tests trace to requirements (TEST-XXX-NNN → REQ-XXX-NNN) | | |
| 9.7 | Traceability matrix complete (no orphan code, no missing requirements) | | |
| 9.8 | Bi-directional traceability verified (forward and backward) | | |

**Traceability Verification**:
```bash
# Normative T-rule gate check — primary command for phase gate compliance.
# Checks all T-rules applicable up to and including the implementation-testing phase
# (includes T7: source code → component design, T6, T5a/b/c, T3, T4, T1, T2).
# Exits 0 = all PASS; 1 = one or more FAIL.
# Matrix naming convention: evidence/traceability/doc<FROM>_to_doc<TO>.csv
python3 tools/workspace.py trace gate-check \
    --phase implementation-testing \
    --sil 3

# Per-matrix gap detection (individual matrix only; does not check T-rules):
python3 tools/workspace.py trace check-gaps --sil 3

# Query traceability for specific module
python3 tools/workspace.py trace query --source DOC-10:MOD-001 --direction forward

# Expected gate-check output: all T-rules PASS with 100% coverage (SIL 3-4)
```

**Review Notes**:
```
[Reviewer adds notes here about traceability issues]
```

---

## 10. Tool Validation Checklist

**Purpose**: Verify tool validation performed and results acceptable

| # | Tool | Item | ✓/✗/N/A | Results |
|---|------|------|---------|---------|
| 10.1 | Cppcheck | Static analysis performed (MISRA C addon) | | [0 violations] |
| 10.2 | Lizard | Complexity analysis performed (CCN ≤ 10 for SIL 3-4) | | [Max: X] |
| 10.3 | gcov/lcov | Coverage analysis performed (100% SIL 3-4) | | [X%] |
| 10.4 | PC-lint Plus | Advanced static analysis (if available) | | [0 violations] |
| 10.5 | Valgrind | Memory leak detection (if applicable) | | [0 leaks] |
| 10.6 | Compiler | Compilation with -Wall -Wextra -Werror (zero warnings) | | [0 warnings] |

**Tool Command Examples**:
```bash
# Cppcheck MISRA C
cppcheck --addon=misra --enable=all --xml src/module.c 2> cppcheck.xml

# Lizard complexity
lizard src/module.c -l c -CCN 10

# gcov coverage
gcc --coverage test_module.c module.c -o test_module
./test_module
gcov module.c

# Valgrind memory check
valgrind --leak-check=full ./test_module
```

**Review Notes**:
```
[Reviewer adds notes here about tool validation issues]
```

---

## 11. Review Process Checklist

**Purpose**: Verify review process followed correctly

| # | Item | ✓/✗/N/A | Comments |
|---|------|---------|----------|
| 11.1 | Author self-review completed before peer review | | |
| 11.2 | Peer review completed (at least one peer reviewer) | | |
| 11.3 | QUA review completed (mandatory for SIL 2+) | | |
| 11.4 | VER review completed (mandatory for SIL 3-4, independent team) | | |
| 11.5 | All review comments addressed by author | | |
| 11.6 | All Critical and Major issues resolved | | |
| 11.7 | Review report generated and archived (Workflow Manager) | | |
| 11.8 | Code approved by all required reviewers | | |

**Review Timeline**:
```
Author Self-Review:    [Date]
Peer Review:           [Date] by [Reviewer Name]
QUA Review:            [Date] by [QA Name]
VER Review:            [Date] by [Verifier Name] (SIL 3-4 only)
Final Approval:        [Date]
```

**Review Notes**:
```
[Reviewer adds overall assessment here]
```

---

## 12. References

### 12.1 EN 50128 Standard

- **Section 6.5**: Software Quality Assurance
- **Section 7.4**: Component Design and Implementation
- **Section 7.5**: Component Testing
- **Table A.4**: Software Design and Implementation Techniques
- **Table A.9**: Software Quality Assurance Techniques
- **Table A.12**: Design and Coding Standards
- **Table A.19**: Static Analysis
- **Annex D.14**: Defensive Programming

### 12.2 MISRA C:2012 Standard

- **MISRA C:2012 Guidelines** (Third Edition, 2023)
- **Amendment 1** (2016)
- **Amendment 2** (2020)
- **Amendment 3** (2024)

### 12.3 Project Documents

- **Software Requirements Specification** (DOC-5)
- **Software Architecture Specification** (DOC-9)
- **Software Design Specification** (DOC-10)
- **Software Source Code** (DOC-18)
- **Software Source Code Verification Report** (DOC-19)
- **Component Test Specification** (DOC-13)
- **Component Test Report** (DOC-14)

### 12.4 Workflow and Resource Documents

- `workflows/code-review-workflow.md` - Detailed code review process
- `workflows/misra-c-implementation.md` - MISRA C implementation workflow
- `workflows/defensive-coding-implementation.md` - Defensive programming workflow
- `workflows/unit-testing-workflow.md` - Unit testing workflow
- `resources/misra-c-coding-patterns.md` - MISRA C pattern catalog
- `resources/unit-testing-patterns.md` - Unit testing pattern catalog
- `resources/common-pitfalls.md` - Common violations and fixes

### 12.5 Tool Documentation

- **Cppcheck Manual**: https://cppcheck.sourceforge.io/manual.pdf
- **Lizard Documentation**: https://github.com/terryyin/lizard
- **gcov/lcov Manual**: https://gcc.gnu.org/onlinedocs/gcc/Gcov.html
- **PC-lint Plus User Guide**: https://pclintplus.com/
- **Workflow Manager CLI**: `tools/workflow_manager.py --help`
- **Traceability Manager CLI**: `tools/README_TRACEABILITY.md`

---

## Appendix A: Review Report Template

**Code Review Report**

**Module**: [module_name]  
**File(s)**: [list of files reviewed]  
**Author**: [author name]  
**Reviewer**: [reviewer name]  
**Review Date**: [date]  
**Review Type**: [ ] Self-Review  [ ] Peer Review  [ ] QUA Review  [ ] VER Review  
**SIL Level**: [ ] 0  [ ] 1  [ ] 2  [ ] 3  [ ] 4

### Summary

**Checklist Completion**:
- Completeness: [X/12 items]
- Correctness: [X/15 items]
- Consistency: [X/10 items]
- EN 50128 Compliance: [X/12 items]
- MISRA C Compliance: [X/20 items]
- Safety: [X/18 items]
- Quality: [X/15 items]
- Traceability: [X/8 items]
- Tool Validation: [X/6 items]
- Review Process: [X/8 items]

**Total**: [X/124 items] ([Y%] compliant)

### Issues Found

| # | Severity | Category | Description | Action Required |
|---|----------|----------|-------------|-----------------|
| 1 | Critical | MISRA C | Rule 9.1 violation: uninitialized variable | MUST FIX |
| 2 | Major | Safety | Missing NULL pointer check | SHOULD FIX |
| 3 | Minor | Style | Inconsistent naming | MAY FIX |

### Recommendations

[List general recommendations for improvement]

### Approval Decision

[ ] **APPROVED** - Code meets all requirements, ready for next phase  
[ ] **APPROVED WITH MINOR ISSUES** - Code acceptable, minor issues documented  
[ ] **REJECTED** - Code does not meet requirements, rework required

**Approver Signature**: _______________  
**Date**: _______________

---

## Appendix B: Quick Reference - Top 20 Review Focus Areas

**For Peer Reviewers (PEER)** - Focus on these 20 items:

1. ✓ NULL pointer checks before all pointer dereferences
2. ✓ Array bounds checks before all array accesses
3. ✓ Return values checked for all function calls (MISRA 17.7)
4. ✓ Variables initialized at declaration (MISRA 9.1)
5. ✓ Fixed-width types used (uint32_t, not int)
6. ✓ No goto statements (MISRA 15.1)
7. ✓ Switch default case present (MISRA 16.4)
8. ✓ No implicit type conversions (MISRA 10.1)
9. ✓ Division by zero checks
10. ✓ Overflow checks on arithmetic operations
11. ✓ Function prototypes in header
12. ✓ No recursion (SIL 3-4)
13. ✓ No malloc/free (SIL 2+)
14. ✓ Functions ≤ 60 lines
15. ✓ Complexity ≤ 10 (SIL 3-4)
16. ✓ Descriptive variable/function names
17. ✓ Code comments adequate
18. ✓ Unit tests exist
19. ✓ No code duplication (DRY)
20. ✓ Traceability to requirements (REQ-XXX-NNN)

**For QUA Reviewers** - Focus on ALL items + static analysis results

**For VER Reviewers (SIL 3-4)** - Focus on safety items (Section 7) + independence verification

---

## Appendix C: Workflow Manager Integration

**Note**: `workflow-mgr` and `code-review` subcommands do not exist in this platform.
Use `python3 tools/workspace.py wf` with the document ID for the source code module
(e.g., `DOC-SRC-YYYY-NNN`) or the implementation review record (e.g., `DOC-UTR-YYYY-001`).

**Author submits implementation artifact for review**:
```bash
python3 tools/workspace.py wf submit <DOC-SRC-ID> \
  --path src/<module>.c \
  --author-role IMP \
  --author-name "John Doe" \
  --sil <level>
```

**Peer reviewer records approval**:
```bash
python3 tools/workspace.py wf review <DOC-SRC-ID> \
  --role PEER \
  --name "Jane Smith" \
  --approve \
  --comment "Peer review passed — no critical findings"
```

**QUA reviewer records approval**:
```bash
python3 tools/workspace.py wf review <DOC-SRC-ID> \
  --role QUA \
  --name "QA Lead" \
  --approve \
  --comment "QUA review passed — MISRA static analysis clean"
```

**VER reviewer records approval (SIL 3-4, independent)**:
```bash
python3 tools/workspace.py wf review <DOC-SRC-ID> \
  --role VER \
  --name "Verifier Name" \
  --approve \
  --comment "Independent VER review passed — coverage 100%"
```

**Final approval after all reviews**:
```bash
python3 tools/workspace.py wf approve <DOC-SRC-ID>
```

**Check review status**:
```bash
python3 tools/workspace.py wf status --document <DOC-SRC-ID> --approvals
```

---

## Summary

This comprehensive checklist provides **124 review items** across 11 categories for reviewing C code in EN 50128-compliant railway safety software. Key takeaways:

**Review Roles**:
- **Author (IMP)**: Self-review all sections before peer review
- **Peer (PEER)**: Focus on completeness, correctness, readability
- **QUA**: Review all sections, verify compliance, approve/reject
- **VER (SIL 3-4)**: Independent review with safety focus

**Critical Focus Areas**:
1. **MISRA C Compliance**: Zero mandatory violations (SIL 3-4)
2. **Safety Patterns**: Defensive programming, error handling, fail-safe
3. **EN 50128 Compliance**: Structured programming, no recursion, complexity ≤ 10
4. **Traceability**: Code → Requirements → Tests (complete and bi-directional)
5. **Tool Validation**: Static analysis, complexity, coverage (100% SIL 3-4)

**Severity Levels**:
- **Critical**: MUST FIX (safety impact, mandatory MISRA violations)
- **Major**: SHOULD FIX (quality impact, required MISRA violations)
- **Minor**: MAY FIX (style issues, advisory MISRA violations)

**Workflow Integration**:
- Use Workflow Manager CLI for review process automation
- Use Traceability Manager CLI for traceability verification
- Use static analysis tools (Cppcheck, Lizard, gcov) for objective metrics

**Next Steps**:
1. Print or bookmark this checklist for code reviews
2. Customize checklist for project-specific requirements
3. Integrate with Workflow Manager for automation
4. Track review metrics (defect density, review duration)
5. Continuously improve based on lessons learned

**Traceability**:
- Code review results documented in Software Source Code Verification Report (DOC-19)
- Review artifacts archived per EN 50128 Section 6.6 (Configuration Management)

---

**Document Control**:
- **Version**: 1.0
- **Date**: 2026-03-13
- **Author**: EN 50128 Implementation Team
- **Approved by**: [Pending]
- **Next Review**: [After first project use]
