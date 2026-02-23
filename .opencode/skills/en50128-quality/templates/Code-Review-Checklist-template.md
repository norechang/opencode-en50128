# Code Review Checklist

**Document ID:** DOC-CRC-YYYY-NNN  
**Project:** [Project Name]  
**System/Subsystem:** [System Name]  
**SIL Level:** [0 | 1 | 2 | 3 | 4]

---

## Document Control

| Version | Date | Author | Change Description | Status |
|---------|------|--------|-------------------|--------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft | Draft |

---

## Review Information

**Review Date:** YYYY-MM-DD  
**Reviewer:** [Name, Role]  
**Author:** [Name, Role]  
**Code Module:** [Module name or filename]  
**File Path:** [Path/to/file.c or file.h]  
**Version:** [Git commit hash or version]

**Review Type:** [Formal Inspection | Walkthrough | Desk Check | Pair Programming Review]

---

## 1. MISRA C Compliance (SIL 2+)

**MANDATORY for SIL 2+:** Zero mandatory MISRA C:2012 violations

### 1.1 Static Analysis

**Static Analysis Tool:** [PC-lint Plus | Cppcheck | Clang Static Analyzer | Other]  
**Analysis Date:** YYYY-MM-DD

| Check | Status | Notes |
|-------|--------|-------|
| Static analysis performed | ☐ Pass ☐ Fail | Tool: [name], Version: [version] |
| MISRA C mandatory violations | ☐ 0 violations ☐ [N] violations | **MUST be 0 for SIL 2+** |
| MISRA C required violations | ☐ [N] violations | Deviations documented: ☐ Yes ☐ No |
| MISRA C advisory violations | ☐ [N] violations | Deviations documented: ☐ Yes ☐ No |

**MISRA C Compliance Result:** ☐ PASS (0 mandatory violations) ☐ FAIL ([N] mandatory violations)

**Violations Requiring Attention:**
| Rule | Severity | Line | Description | Action |
|------|----------|------|-------------|--------|
| [Rule X.Y] | [M/R/A] | [Line #] | [Description] | [Fix / Deviation (justify)] |

---

## 2. Complexity Limits

**SIL-Dependent Limits:**
- **SIL 3-4:** Cyclomatic complexity ≤ 10
- **SIL 2:** Cyclomatic complexity ≤ 15
- **SIL 0-1:** Cyclomatic complexity ≤ 20

### 2.1 Cyclomatic Complexity

**Complexity Analysis Tool:** [Lizard | McCabe IQ | Understand | Manual]  
**Analysis Date:** YYYY-MM-DD

| Function | Complexity | Limit | Status | Action Required |
|----------|-----------|-------|--------|----------------|
| [function_name()] | [N] | [10/15/20] | ☐ Pass ☐ Fail | [Refactor if failed] |

**Overall Complexity Result:** ☐ PASS (all functions within limit) ☐ FAIL ([N] functions exceed limit)

### 2.2 Function Length

| Check | Status | Notes |
|-------|--------|-------|
| All functions < 200 LOC (recommended) | ☐ Yes ☐ No | Functions exceeding: [list if any] |
| Nesting depth < 5 levels (recommended) | ☐ Yes ☐ No | Functions exceeding: [list if any] |

---

## 3. Defensive Programming (HR for SIL 2+, M for SIL 3-4)

### 3.1 Input Validation

| Check | Status | Issues Found |
|-------|--------|--------------|
| All pointer parameters validated (NULL checks) | ☐ All ☐ Most ☐ Some ☐ None | [Lines with missing checks] |
| All array indices bounds-checked | ☐ All ☐ Most ☐ Some ☐ None | [Lines with missing checks] |
| Function parameter ranges validated | ☐ All ☐ Most ☐ Some ☐ None | [Lines with missing checks] |
| Preconditions documented and enforced | ☐ Yes ☐ Partial ☐ No | [Missing preconditions] |

**Example Issues:**
```c
// ISSUE: Missing NULL check (Line XXX)
void process_data(uint8_t* data) {
    // MISSING: if (data == NULL) return ERROR;
    for (int i = 0; i < 100; i++) {
        data[i] = 0;  // Potential NULL pointer dereference
    }
}

// CORRECT: With defensive check
void process_data(uint8_t* data) {
    if (data == NULL) return ERROR;  // Defensive programming
    for (int i = 0; i < 100; i++) {
        data[i] = 0;
    }
}
```

### 3.2 Return Value Checking

| Check | Status | Issues Found |
|-------|--------|--------------|
| All function return values checked | ☐ All ☐ Most ☐ Some ☐ None | [Lines with unchecked returns] |
| Error codes propagated correctly | ☐ Yes ☐ Partial ☐ No | [Lines with issues] |
| Postconditions verified | ☐ Yes ☐ Partial ☐ No | [Missing postconditions] |

**Example Issues:**
```c
// ISSUE: Unchecked return value (Line XXX)
error_t status = initialize_hardware();
start_processing();  // Proceeds even if initialization failed!

// CORRECT: Check return value
error_t status = initialize_hardware();
if (status != SUCCESS) {
    return status;  // Propagate error
}
start_processing();
```

### 3.3 Arithmetic Safety

| Check | Status | Issues Found |
|-------|--------|--------------|
| Division operations check for zero divisor | ☐ All ☐ Most ☐ Some ☐ None | [Lines with missing checks] |
| Integer overflow protection | ☐ All ☐ Most ☐ Some ☐ None | [Lines with potential overflow] |
| Type conversions safe (no truncation) | ☐ All ☐ Most ☐ Some ☐ None | [Lines with unsafe conversions] |

**Example Issues:**
```c
// ISSUE: No zero division check (Line XXX)
uint32_t result = total / count;  // count could be zero!

// CORRECT: Check for zero
if (count == 0) {
    return ERROR_DIVIDE_BY_ZERO;
}
uint32_t result = total / count;

// ISSUE: Potential overflow (Line XXX)
uint16_t a = 60000;
uint16_t b = 10000;
uint16_t sum = a + b;  // Overflow! Result wraps around

// CORRECT: Overflow protection
uint16_t a = 60000;
uint16_t b = 10000;
if (a > (UINT16_MAX - b)) {
    return ERROR_OVERFLOW;
}
uint16_t sum = a + b;
```

### 3.4 Assertions and Invariants

| Check | Status | Notes |
|-------|--------|-------|
| Assertions used for invariants | ☐ Yes ☐ No | [Opportunities for assertions] |
| Critical preconditions asserted | ☐ Yes ☐ Partial ☐ No | [Missing assertions] |
| Assertions do not have side effects | ☐ Verified ☐ Issues found | [Issues if any] |

---

## 4. Memory Management (SIL 2+)

### 4.1 Static Allocation (MANDATORY for SIL 2+)

| Check | Status | Violations |
|-------|--------|-----------|
| No `malloc()` calls | ☐ Pass ☐ Fail | [Lines with violations] |
| No `calloc()` calls | ☐ Pass ☐ Fail | [Lines with violations] |
| No `realloc()` calls | ☐ Pass ☐ Fail | [Lines with violations] |
| No `free()` calls | ☐ Pass ☐ Fail | [Lines with violations] |
| No variable-length arrays (VLA) | ☐ Pass ☐ Fail | [Lines with violations] |

**SIL 2+ Compliance:** ☐ PASS (static allocation only) ☐ FAIL (dynamic allocation found)

### 4.2 Data Types

| Check | Status | Issues |
|-------|--------|--------|
| Fixed-width types used (`uint8_t`, `uint16_t`, etc.) | ☐ All ☐ Most ☐ Some | [Lines with platform-dependent types] |
| No implicit type conversions | ☐ Yes ☐ Issues found | [Lines with implicit conversions] |
| Pointer types clearly defined | ☐ Yes ☐ Issues found | [Lines with unclear pointer usage] |

**Example Issues:**
```c
// ISSUE: Platform-dependent type (Line XXX)
unsigned int counter;  // Size varies by platform (16/32/64 bits)

// CORRECT: Fixed-width type
uint32_t counter;  // Always 32 bits

// ISSUE: Implicit conversion (Line XXX)
uint8_t small = 255;
uint16_t large = small + 1;  // Implicit promotion

// BETTER: Explicit conversion
uint8_t small = 255;
uint16_t large = (uint16_t)small + 1U;
```

### 4.3 Buffer Management

| Check | Status | Issues |
|-------|--------|--------|
| Buffer sizes explicitly defined | ☐ Yes ☐ No | [Buffers with implicit sizes] |
| Buffer overflows prevented | ☐ Yes ☐ Potential issues | [Lines with potential overflows] |
| String operations safe (no `strcpy`, use `strncpy`) | ☐ Yes ☐ Issues found | [Lines with unsafe functions] |

---

## 5. Control Flow

### 5.1 Recursion (Highly Recommended: NO recursion for SIL 3-4)

| Check | Status | Issues |
|-------|--------|--------|
| No recursive functions | ☐ Yes ☐ No - recursion found | [Recursive functions found] |
| If recursion used, maximum depth proven | ☐ N/A ☐ Yes ☐ No | [Analysis reference] |

**SIL 3-4:** Recursion NOT recommended - requires strong justification

### 5.2 Loop Control

| Check | Status | Issues |
|-------|--------|--------|
| All loops have bounded iterations | ☐ Yes ☐ No | [Lines with unbounded loops] |
| Loop termination guaranteed | ☐ Yes ☐ No | [Lines with questionable termination] |
| Loop counters not modified in loop body | ☐ Yes ☐ Issues found | [Lines with counter modification] |

**Example Issues:**
```c
// ISSUE: Unbounded loop (Line XXX)
while (wait_for_signal()) {
    // What if signal never arrives? Infinite loop!
}

// BETTER: Bounded with timeout
uint32_t timeout = MAX_WAIT_CYCLES;
while (wait_for_signal() && timeout > 0) {
    timeout--;
}
if (timeout == 0) {
    return ERROR_TIMEOUT;
}
```

### 5.3 Switch Statements

| Check | Status | Issues |
|-------|--------|--------|
| All switch statements have `default` case | ☐ Yes ☐ Missing | [Lines missing default] |
| No fall-through between cases (unless commented) | ☐ Yes ☐ Issues found | [Lines with fall-through] |
| All enum values covered | ☐ Yes ☐ Missing | [Missing cases] |

---

## 6. Error Handling

### 6.1 Error Detection

| Check | Status | Notes |
|-------|--------|-------|
| All error conditions identified | ☐ Complete ☐ Incomplete | [Missing error cases] |
| Error codes defined and used consistently | ☐ Yes ☐ No | [Inconsistencies found] |
| Error handling strategy clear | ☐ Yes ☐ No | [Unclear error paths] |

### 6.2 Error Propagation

| Check | Status | Issues |
|-------|--------|--------|
| Errors propagated to caller appropriately | ☐ Yes ☐ Issues | [Lines with swallowed errors] |
| Error logging adequate | ☐ Yes ☐ Inadequate | [Missing error logs] |
| Fail-safe behavior implemented | ☐ Yes ☐ N/A ☐ No | [Missing fail-safe logic] |

---

## 7. Coding Style and Maintainability

### 7.1 Naming Conventions

| Check | Status | Issues |
|-------|--------|--------|
| Naming conventions followed consistently | ☐ Yes ☐ Issues | [Non-conforming names] |
| Variable names descriptive | ☐ Yes ☐ Some unclear | [Unclear variable names] |
| Function names descriptive (verb + noun) | ☐ Yes ☐ Some unclear | [Unclear function names] |
| Constants named with UPPER_CASE | ☐ Yes ☐ Issues | [Non-conforming constants] |

### 7.2 Comments and Documentation

| Check | Status | Issues |
|-------|--------|--------|
| File header comment present | ☐ Yes ☐ No | |
| Function header comments present | ☐ All ☐ Most ☐ Some ☐ None | [Functions missing headers] |
| Complex logic commented | ☐ Adequate ☐ Inadequate | [Lines needing comments] |
| Comments accurate and up-to-date | ☐ Yes ☐ Stale comments found | [Lines with stale comments] |
| No commented-out code | ☐ Clean ☐ Found | [Lines with commented code] |

### 7.3 Code Structure

| Check | Status | Issues |
|-------|--------|--------|
| Indentation consistent (spaces or tabs) | ☐ Yes ☐ No | [Inconsistent indentation] |
| Line length reasonable (< 120 chars recommended) | ☐ Yes ☐ Issues | [Excessively long lines] |
| One statement per line | ☐ Yes ☐ Issues | [Multiple statements per line] |
| Braces used consistently (K&R, Allman, etc.) | ☐ Yes ☐ Inconsistent | [Inconsistent brace style] |

### 7.4 Magic Numbers and Constants

| Check | Status | Issues |
|-------|--------|--------|
| No magic numbers (use named constants) | ☐ Yes ☐ Issues | [Lines with magic numbers] |
| Constants defined in appropriate scope | ☐ Yes ☐ Issues | [Misplaced constants] |
| Enumerations used for related constants | ☐ Yes ☐ Opportunities | [Could use enums] |

**Example Issues:**
```c
// ISSUE: Magic numbers (Line XXX)
if (temperature > 85) {
    trigger_alarm();
}

// CORRECT: Named constant
#define MAX_SAFE_TEMPERATURE_C 85
if (temperature > MAX_SAFE_TEMPERATURE_C) {
    trigger_alarm();
}
```

---

## 8. Header Files (for .h files)

### 8.1 Header Guards

| Check | Status | Issues |
|-------|--------|--------|
| Header guard present | ☐ Yes ☐ No | |
| Header guard unique | ☐ Yes ☐ No | [Potential conflicts] |
| Header guard naming convention followed | ☐ Yes ☐ No | [Non-conforming name] |

**Example:**
```c
// CORRECT header guard
#ifndef MODULE_NAME_H
#define MODULE_NAME_H

// Header contents

#endif /* MODULE_NAME_H */
```

### 8.2 Header Content

| Check | Status | Issues |
|-------|--------|--------|
| Only declarations in header (no definitions) | ☐ Yes ☐ Issues | [Definitions found in header] |
| No executable code in header | ☐ Yes ☐ Issues | [Executable code found] |
| All public functions declared | ☐ Yes ☐ Missing | [Undeclared functions] |
| Private functions not in header | ☐ Yes ☐ Issues | [Private functions in header] |

---

## 9. Safety and Reliability (EN 50128 Specific)

### 9.1 Safety Requirements Implementation

| Check | Status | Reference |
|-------|--------|-----------|
| All safety requirements implemented | ☐ Yes ☐ No | [Missing requirements] |
| Safety requirements traced to code | ☐ Yes ☐ Incomplete | [Requirements without traceability] |
| Safety mechanisms correct | ☐ Yes ☐ Issues | [Issues with safety logic] |

### 9.2 Fault Detection and Diagnosis (R for SIL 2, HR for SIL 3-4)

| Check | Status | Notes |
|-------|--------|-------|
| Fault detection mechanisms implemented | ☐ Yes ☐ N/A ☐ No | [Specify mechanisms] |
| Diagnostic coverage adequate | ☐ Yes ☐ N/A ☐ No | [Coverage percentage] |
| Fault response appropriate | ☐ Yes ☐ N/A ☐ Issues | [Issues with response] |

### 9.3 Redundancy and Voting (if applicable)

| Check | Status | Notes |
|-------|--------|-------|
| Redundancy implemented correctly | ☐ Yes ☐ N/A ☐ Issues | [Issues with redundancy] |
| Voting logic correct | ☐ Yes ☐ N/A ☐ Issues | [Issues with voting] |
| Common cause failures considered | ☐ Yes ☐ N/A ☐ No | [Missing CCF analysis] |

### 9.4 Watchdog Implementation (if applicable)

| Check | Status | Notes |
|-------|--------|-------|
| Watchdog servicing correct | ☐ Yes ☐ N/A ☐ Issues | [Issues with watchdog] |
| Watchdog timeout appropriate | ☐ Yes ☐ N/A ☐ No | [Timeout value] |
| Watchdog failure handling implemented | ☐ Yes ☐ N/A ☐ No | [Missing failure handling] |

---

## 10. Code Reuse and Dependencies

### 10.1 Code Reuse

| Check | Status | Notes |
|-------|--------|-------|
| Reused code properly validated | ☐ Yes ☐ N/A ☐ No | [Validation reference] |
| Reused code SIL-appropriate | ☐ Yes ☐ N/A ☐ No | [SIL mismatch issues] |
| Reused code documented | ☐ Yes ☐ N/A ☐ No | [Documentation reference] |

### 10.2 External Dependencies

| Check | Status | Notes |
|-------|--------|-------|
| External libraries documented | ☐ Yes ☐ N/A ☐ No | [Library list] |
| External libraries SIL-certified | ☐ Yes ☐ N/A ☐ No | [Certification reference] |
| Dependency versions controlled | ☐ Yes ☐ N/A ☐ No | [Version management] |

---

## 11. Testing Considerations

### 11.1 Testability

| Check | Status | Notes |
|-------|--------|-------|
| Code structure testable | ☐ Yes ☐ Issues | [Testability issues] |
| Test points identified | ☐ Yes ☐ Inadequate | [Missing test points] |
| Unit tests exist for this module | ☐ Yes ☐ No | [Test file reference] |

### 11.2 Coverage Potential

| Check | Status | Notes |
|-------|--------|-------|
| All branches reachable | ☐ Yes ☐ No | [Unreachable code] |
| All conditions testable | ☐ Yes ☐ No | [Untestable conditions] |
| Coverage achievable (statement, branch, condition) | ☐ Yes ☐ Challenges | [Coverage challenges] |

---

## 12. Overall Assessment

### 12.1 Defect Summary

| Severity | Count | Status |
|----------|-------|--------|
| **Critical** (EN 50128 mandatory violation, safety risk) | [N] | MUST fix before approval |
| **Major** (Highly recommended practice violation) | [N] | SHOULD fix before approval |
| **Minor** (Recommended practice violation) | [N] | MAY defer to future release |
| **Observations** (Improvement opportunities) | [N] | For consideration |

### 12.2 Review Result

**Overall Result:** ☐ PASS ☐ PASS with Minor Issues ☐ FAIL - Rework Required

**Key Strengths:**
- [Positive observation 1]
- [Positive observation 2]

**Key Weaknesses:**
- [Issue 1]
- [Issue 2]

**Critical Issues Blocking Approval:**
1. [Critical issue 1]
2. [Critical issue 2]

### 12.3 Approval Decision

**Decision:** ☐ Approve ☐ Approve with Conditions ☐ Reject - Require Rework

**Conditions for Approval (if applicable):**
1. [Condition 1]
2. [Condition 2]

**Reviewer Signature:** ______________________  
**Date:** YYYY-MM-DD

---

## 13. Corrective Actions

| Issue # | Description | Location | Severity | Assigned To | Target Date | Status |
|---------|-------------|----------|----------|-------------|-------------|--------|
| 1 | [Issue description] | [File:Line] | [C/M/m/O] | [Name] | YYYY-MM-DD | [Open/In Progress/Closed] |

**Legend:** C = Critical, M = Major, m = Minor, O = Observation

---

## EN 50128 References

- **Section 6.5:** Software Quality Assurance
- **Table A.9:** Software Quality Assurance techniques (Code reviews: M for SIL 3-4, HR for SIL 1-2)
- **Section 7.4:** Software Design and Implementation
- **Table A.4:** Software Design and Implementation techniques
- **Table A.12:** Design and Coding Standards
- **Annex A:** Techniques and Measures

## MISRA C:2012 References

- **MISRA C:2012 Guidelines:** Mandatory, Required, and Advisory rules
- **MISRA Compliance:2020:** Guidance on achieving and demonstrating compliance

---

**Template Version:** 1.0  
**EN 50128:2011 Compliance:** Section 6.5, Table A.9  
**Skill Owner:** Quality Assurance (`/qua`)

---

## Instructions for Use

1. **Before Review:** Print or open this checklist, read the code thoroughly
2. **During Review:** Check each item systematically, document all issues
3. **After Review:** Complete assessment, make approval decision, create corrective action plan
4. **For SIL 2+:** Focus on MISRA C compliance (zero mandatory violations required)
5. **For SIL 3-4:** Emphasize defensive programming, complexity limits, and safety mechanisms
6. **Re-Review:** After corrections, verify all critical and major issues resolved
