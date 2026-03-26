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
| 1.0 | YYYY-MM-DD | [Author Name] | Initial version |

---

## 1. Tool Identification

**Tool Name**: [Full tool name]  
**Tool Version**: [Exact version number (e.g., 13.3.0)]  
**Tool Vendor**: [Vendor/Organization name]  
**Tool Purpose**: [Brief description of what the tool does]  
**Target Platform**: [Platform on which tool runs (e.g., x86-64 Linux, Ubuntu 22.04)]

---

## 2. Tool Classification

**Classification**: T3 - Full Qualification Required

**Justification**:

[Provide detailed justification for T3 classification]

- **Purpose**: [What does the tool do?]
- **Output**: [What does the tool produce? (e.g., machine code, executables)]
- **Usage**: [How is the output used? (e.g., executed directly on target system)]
- **Verification**: [Is the output verified by other means? (e.g., NO - code not independently verified)]
- **Impact of tool error**:
  - [What happens if the tool has a bug?]
  - [Example: Incorrect code generation → software safety failure]
  - [Example: Compiler bug → undetected software defect]
  - [Example: Optimizer error → incorrect runtime behavior]
- **Conclusion**: [Why T3? (e.g., Tool errors directly affect software safety, no independent verification)]

**QUA Review**: [✅ Approved / ❌ Rejected] by [QUA Name] on [Date]

---

## 3. Tool Specification

### 3.1 Tool Functionality

[Describe what the tool does in detail]

**Input**: [What inputs does the tool accept? (e.g., C source files .c/.h)]  
**Output**: [What outputs does the tool produce? (e.g., object files .o, executables)]  
**Functionality**: [Key features/capabilities (e.g., compilation, optimization, linking)]

### 3.2 Tool Usage in Project

**Agents Using Tool**: [List agent roles that use this tool (e.g., IMP, TST, INT)]

**Usage Commands**:
```bash
[Example commands used in this project]
[Include all relevant compiler flags, options, etc.]

# Example:
# gcc -std=c11 -Wall -Wextra -Werror -pedantic -O2 \
#     -DSIL_LEVEL=3 -DMISRA_C_2012 \
#     -fstack-protector-strong -D_FORTIFY_SOURCE=2 \
#     -o output source.c
```

**Usage Scenarios**:
[List specific ways tool is used in this project]
1. [Scenario 1 (e.g., Compile source files to object files)]
2. [Scenario 2 (e.g., Link object files to executable)]
3. [Scenario 3 (e.g., Generate assembly listings for code review)]
4. [etc.]

### 3.3 Tool Constraints and Limitations

**Constraints**:
[List any constraints on tool usage in this project]
- **Version locked**: [Tool] [Version] (no updates without re-qualification)
- **Platform**: [Specific platform only (e.g., x86-64 Linux only)]
- **Language**: [Language standard only (e.g., C11 only, no C++, no GNU extensions)]
- **Optimization**: [Specific optimization level only (e.g., -O2 only, not -O3)]
- [Other constraints]

**Known Limitations**:
[List known tool limitations/bugs]
- [Example: Tool test suite: 99.8% pass rate (0.2% known failures)]
- [Example: Known failures documented in tool bug database]
- [Example: None of the known failures affect safety-critical code patterns used in this project]

---

## 4. Supplier Qualification Evidence

### 4.1 Supplier Test Suite Results

**Source**: [URL or document reference for supplier test results]

**Test Statistics**:
- Total tests: [Number]
- Passed: [Number] ([Percentage]%)
- Failed: [Number] ([Percentage]%)
- Failures analyzed: [Analysis of failures - do they affect this project?]

**Test Coverage**:
- [Language] standard compliance: [✅ Comprehensive / ⚠️ Partial / ❌ Insufficient]
- Code generation correctness: [✅ Comprehensive / ⚠️ Partial / ❌ Insufficient]
- Optimization correctness: [✅ Comprehensive / ⚠️ Partial / ❌ Insufficient]
- Platform-specific ([Platform]): [✅ Comprehensive / ⚠️ Partial / ❌ Insufficient]

### 4.2 Industry Usage

**Safety-Critical Projects Using [Tool Name]**:
- [Domain 1] ([Standard]): [Description of usage (e.g., Multiple ASIL-D certified projects)]
- [Domain 2] ([Standard]): [Description of usage (e.g., Multiple DAL-A certified projects)]
- [Domain 3] ([Standard]): [Description of usage (e.g., Multiple SIL 4 certified projects)]

**Industry Acceptance**: [Summary of tool's acceptance in safety-critical development]

### 4.3 Tool Certification (if applicable)

**Certifications**:
- [Certification 1 (e.g., TÜV certification for safety-critical tools)]
- [Certification 2 (e.g., IEC 61508 certification)]
- [Certification 3 (e.g., EN 50128 pre-qualified tool listing)]

[If no certification: State "No industry certification available" and provide justification for use anyway]

### 4.4 [Language/Standard] Support (if applicable)

**[Standard] Compliance**:
- [Tool] supports [Standard] with appropriate flags
- [Tool] warnings cover [Standard] rules
- Additional [Standard] checking via [other tool]

**Documentation**: [URL or reference]

---

## 5. Project-Specific Validation

### 5.1 Tool Validation Tests

**Location**: [Path to validation tests (e.g., tests/tool-qualification/gcc-validation/)]

**Tests Performed**:
[List all validation tests]
1. **[Test 1 Name]**: [Description (e.g., Integer Arithmetic - Validate correct arithmetic code generation)]
2. **[Test 2 Name]**: [Description (e.g., Pointer Arithmetic - Validate correct pointer operations)]
3. **[Test 3 Name]**: [Description (e.g., Function Calls - Validate correct call/return sequences)]
4. **[Test 4 Name]**: [Description (e.g., Optimization Correctness - Validate optimizer doesn't break semantics)]
5. **[Test 5 Name]**: [Description (e.g., Platform-Specific - Validate platform code generation)]
6. **[Test 6 Name]**: [Description (e.g., Tool Flags - Validate that project flags produce correct code)]

**Test Results**: [✅ All tests PASSED / ❌ Some tests FAILED (see details below)]

[If tests passed: Include summary results]
[If tests failed: Include detailed failure analysis and mitigation]

### 5.2 Assembly Code Review (for compilers)

**Method**: [Description of assembly review process (e.g., Generate assembly listings for critical functions, review manually)]

**Example**:
```bash
[Command to generate assembly]
# gcc -S -std=c11 -O2 critical_function.c -o critical_function.s
# Review critical_function.s for correctness
```

**Results**: [Summary of assembly review results]
[Example: Assembly code review performed for 10 critical functions. All correct.]

### 5.3 Comparison Testing (if applicable)

**Method**: [Description of comparison testing (e.g., Compile same code with multiple tools, compare results)]

**Tools Used**:
- [Tool 1] [Version]
- [Tool 2] [Version]

**Results**: [Summary of comparison results]
[Example: Both tools produce functionally equivalent code (verified by testing).]

---

## 6. Tool Qualification Conclusion

[Tool Name] [Tool Version] is **[QUALIFIED / NOT QUALIFIED]** for use in this [SIL X] project:

- [✅ / ❌] [Evidence item 1 (e.g., Comprehensive supplier qualification evidence)]
- [✅ / ❌] [Evidence item 2 (e.g., Extensive industry usage in safety-critical domains)]
- [✅ / ❌] [Evidence item 3 (e.g., Project-specific validation tests passed)]
- [✅ / ❌] [Evidence item 4 (e.g., Assembly code review confirms correct code generation)]
- [✅ / ❌] [Evidence item 5 (e.g., Comparison testing confirms correctness)]

**Tool Version**: [Tool] [Version] (LOCKED for project, checksum: [SHA256 checksum])

**Qualification Valid Until**: [Condition for re-qualification (e.g., Tool update or re-qualification required)]

[If NOT QUALIFIED: Provide detailed reasons and remediation plan]

---

## 7. Tool Configuration Management

**Version Control**:
- Tool version recorded in Tool-Baseline.md
- Tool executable checksum: [SHA256 checksum]
- Tool version verified by [method (e.g., CI/CD on every build)]

**Change Control**:
- Any [Tool] update requires Change Request (CR)
- CR must include re-qualification plan
- CCB approval required before tool update

**Baseline Recording**:
```bash
# Commands used to record tool baseline
[tool-name] --version > docs/tool-qualification/[tool]-version.txt
sha256sum $(which [tool-name]) > docs/tool-qualification/[tool]-checksum.txt
```

**CI/CD Integration** (SIL 3-4):
```yaml
# Tool version check in CI/CD
- name: Check [Tool Name] version (LOCKED for SIL [X])
  run: |
    EXPECTED_VERSION="[Version]"
    ACTUAL_VERSION=$([command to get version])
    if [ "$ACTUAL_VERSION" != "$EXPECTED_VERSION" ]; then
      echo "ERROR: [Tool] version mismatch!"
      echo "Expected: $EXPECTED_VERSION (qualified)"
      echo "Actual: $ACTUAL_VERSION"
      echo "[Tool] version is LOCKED for this SIL [X] project."
      exit 1
    fi
```

---

## 8. Approvals

| Role | Name | Date | Signature |
|------|------|------|-----------|
| **QUA** | [QUA Agent Name] | YYYY-MM-DD | [Signature or "Approved via workflow WF-YYYY-NNN"] |
| **VER** | [VER Agent Name] | YYYY-MM-DD | [Signature or "Approved via workflow WF-YYYY-NNN"] |
| **PM** | [PM Name] | YYYY-MM-DD | [Signature or "Approved via workflow WF-YYYY-NNN"] |

---

## Appendices

### Appendix A: Validation Test Results

[Attach or link to validation test results]

**File**: `tests/tool-qualification/[tool]-validation/validation-results.txt`

```
[Paste validation test results here]
```

### Appendix B: Supplier Documentation

[List and attach or link to supplier-provided documentation]

1. [Supplier document 1 (e.g., Tool Test Suite Results)]
2. [Supplier document 2 (e.g., Tool Qualification Package)]
3. [Supplier document 3 (e.g., Tool Certification)]

### Appendix C: Tool Configuration Files

[Attach or link to tool configuration files used in project]

**Example: Makefile with tool flags**

```makefile
[Paste relevant configuration]
```

---

**END OF DOCUMENT**
