# Tools Validation Report

**Document ID:** DOC-TOOLSVALRPT-YYYY-NNN  
**Document Type:** Tools-Validation-Report  
**Phase:** Phase 7 — Validation (Annex C item 26)  
**EN 50128 Reference:** §6.7, §6.7.4.2–6.7.4.11  
**Author Role:** VAL  
**Applicability:** Conditional — required when tool qualification evidence is needed  
**1st Check:** VER | **2nd Check:** none

---

## Document Control

| Version | Date | Author | Reviewer | Approver | Changes |
|---------|------|--------|----------|----------|---------|
| 0.1 | YYYY-MM-DD | [VAL Name] | [QUA Name] | [VMGR Name] | Initial draft |

**Configuration Item:** [CI ID]  
**Baseline:** [Baseline ID]

---

## Approvals

| Role | Name | Signature | Date | SIL Level |
|------|------|-----------|------|-----------|
| Validator (VAL) | [Name] | [Signature] | YYYY-MM-DD | [0/1/2/3/4] |
| Quality Assurance (QUA) — Format Gate | [Name] | [Signature] | YYYY-MM-DD | [0/1/2/3/4] |
| Verifier (VER) — item † | [Name] | [Signature] | YYYY-MM-DD | [3/4 only] |
| V&V Manager (VMGR) — Final V&V | [Name] | [Signature] | YYYY-MM-DD | [3/4 only] |
| Configuration Manager (CM) | [Name] | [Signature] | YYYY-MM-DD | [0/1/2/3/4] |

---

## 1. Introduction

### 1.1 Purpose

This Tools Validation Report documents the qualification of software tools used in the
development, verification, and validation of [Software Component / Project Name] at SIL [level],
per EN 50128:2011 §6.7. It confirms that tool failures cannot adversely affect software safety
without detection.

### 1.2 Scope

| Item | Value |
|------|-------|
| Project | [Name] |
| SIL level | [0/1/2/3/4] |
| Tools covered | See Section 2 |
| Standards applied | EN 50128:2011 §6.7 |

### 1.3 Tool Classification Definitions (§6.7.3)

| Class | Definition | Validation Requirement |
|-------|-----------|----------------------|
| **T1** | No influence on executable code (e.g., text editors, version control) | None required |
| **T2** | Supports testing or verification; incorrect output detectable by other means (e.g., test frameworks, coverage tools) | HR for SIL 1–4 |
| **T3** | Generates or translates executable code; output errors may propagate undetected (e.g., compilers, linkers, code generators) | Evidence mandatory SIL 3-4 (§6.7.4.4) |

---

## 2. Tool Inventory

| Tool ID | Tool Name | Version | Vendor | Class | Used for | Config Item ID |
|---------|-----------|---------|--------|-------|----------|---------------|
| TOOL-001 | [Name] | [X.Y.Z] | [Vendor] | T[1/2/3] | [Purpose] | [CI ID] |
| TOOL-002 | [Name] | [X.Y.Z] | [Vendor] | T[1/2/3] | [Purpose] | [CI ID] |
| TOOL-003 | gcc | [version] | FSF | T3 | Compilation | [CI ID] |
| TOOL-004 | gcov / lcov | [version] | FSF | T2 | Coverage measurement | [CI ID] |
| TOOL-005 | cppcheck | [version] | Cppcheck team | T2 | Static analysis | [CI ID] |
| TOOL-006 | Unity | [version] | ThrowTheSwitch | T2 | Unit test framework | [CI ID] |
| TOOL-007 | git | [version] | Git project | T1 | Version control | N/A |
| ... | ... | ... | ... | ... | ... | ... |

**T1 tools:** [count] — no validation required  
**T2 tools:** [count] — validation HR  
**T3 tools:** [count] — evidence mandatory (SIL 3-4)

---

## 3. T2 and T3 Tool Classification Justification (§6.7.4.2)

For each T2 and T3 tool, justify the classification.

### 3.1 TOOL-003 — [Compiler name] (T3)

**Justification:** The compiler translates C source code into executable binary. Compiler
defects can introduce faults into the executable that are not present in the source code and
may not be detectable by testing of the binary alone. Classification T3 is mandatory.

**Potential failure modes:**
- Incorrect code optimisation producing wrong results
- Incorrect register allocation causing data corruption
- Incorrect handling of volatile variables

**Mitigation approach (§6.7.4.4):** [select one or more]  
- [ ] Tool validation (this section, §6.7.4.5)  
- [ ] History of successful use (§6.7.4.4a)  
- [ ] Diverse redundant code (§6.7.4.4c)  
- [ ] High object-code test coverage (§6.7.4.6 Note 2)  
- [ ] Other: [describe]

### 3.2 TOOL-004 — [Coverage tool name] (T2)

**Justification:** Coverage measurement tool produces coverage metrics used in verification.
Incorrect coverage reports could lead to incorrect release decisions. However, the coverage
data is reviewed against test results, providing an independent detection mechanism. T2.

**Potential failure modes:**
- Under-reporting of uncovered branches (misleading pass)
- Incorrect source mapping

**Mitigation approach:** Coverage tool outputs cross-checked against manual review of
untested branches for critical safety functions.

*(Repeat Section 3.x for each T2 and T3 tool)*

---

## 4. Tool Validation Activities (§6.7.4.5)

For each T3 tool (and T2 tools selected for validation), document validation activities.

### 4.1 TOOL-003 — [Compiler name] (T3)

**Validation approach:** [Tool validation per §6.7.4.5 / History of use / Other per §6.7.4.4]

**Tool manual / specification version:** [Manual version — §6.7.4.5(b)]

**Functions validated (§6.7.4.5(c)):**

| Function | Validation Approach | Test ID |
|----------|--------------------|---------| 
| Integer arithmetic | Compile and test representative calculations | TV-001 |
| Floating-point operations | Compile and test edge cases | TV-002 |
| Volatile variable handling | Verify no unwanted optimisation | TV-003 |
| Interrupt handler code generation | Verify correct entry/exit | TV-004 |
| ... | ... | ... |

**Tools and equipment used for validation (§6.7.4.5(d)):**

| Tool | Version | Purpose |
|------|---------|---------|
| [Reference compiler] | [version] | Cross-check compilation outputs |
| [Target hardware] | [version] | Execution environment |

**Validation test cases (§6.7.4.5(f)):**

| Test ID | Compiler Function Tested | Input | Expected Output | Actual Output | Result |
|---------|------------------------|-------|----------------|--------------|--------|
| TV-001 | Integer overflow behaviour | [input] | [expected] | [actual] | [PASS/FAIL] |
| TV-002 | Floating-point rounding | [input] | [expected] | [actual] | [PASS/FAIL] |
| TV-003 | volatile keyword respected | [source] | [no optimisation] | [actual] | [PASS/FAIL] |
| ... | ... | ... | ... | ... | ... |

**Discrepancies (§6.7.4.5(g)):**

| Discrepancy ID | Description | Impact | Resolution |
|---------------|-------------|--------|------------|
| DISC-001 | [If any] | [Impact] | [Resolution / Accepted] |

**Validation result (§6.7.4.5(e)):** [PASS / FAIL]

*(Repeat Section 4.x for each validated tool)*

---

## 5. Alternative Evidence for T3 Tools (§6.7.4.4)

For T3 tools where full validation per §6.7.4.5 is not performed, document alternative evidence.

| Tool ID | Tool | Evidence Type (§6.7.4.4 clause) | Evidence Description | Adequacy Assessment |
|---------|------|--------------------------------|---------------------|---------------------|
| TOOL-003 | [Compiler] | §6.7.4.4a — history of use | [N] years in [domain]; [N] projects; no known safety-relevant defects | [Adequate / Inadequate + justify] |
| ... | ... | ... | ... | ... |

---

## 6. Validation Results Summary

| Tool ID | Tool | Class | Validation Approach | Result |
|---------|------|-------|--------------------|----|
| TOOL-001 | [Name] | T1 | No validation required | N/A |
| TOOL-003 | [Name] | T3 | §6.7.4.5 validation | [PASS/FAIL] |
| TOOL-004 | [Name] | T2 | Alternative evidence | [Adequate/Inadequate] |
| ... | ... | ... | ... | ... |

**All T3 tools with adequate evidence:** [Yes / No]  
**Any tool qualification failures:** [None / List]

---

## 7. Tool Version Control (§6.7.4.10–6.7.4.11)

Per §6.7.4.10, only justified tool versions shall be used. Per §6.7.4.11, new versions require
a new justification.

| Tool | Version Used | Version Justified by | Config Item ID | Version Change Control |
|------|-------------|---------------------|---------------|----------------------|
| [Name] | [X.Y.Z] | This report, Section 4.x | [CI ID] | CCB approval required |
| ... | ... | ... | ... | ... |

**Tool versions are under CM control:** [Yes / No]  
**Reference:** SCMP DOC-SCMP-YYYY-NNN, §[section]

---

## 8. Conclusion

**Overall Tools Qualification Result:** [PASS / FAIL / CONDITIONAL]

**Summary:**  
[Brief statement: all T3 tools have adequate evidence of qualification; T2 tools with
validation are confirmed adequate; T1 tools require no action. Any conditions or restrictions.]

**Conditions for Use:**  
[Any restrictions on tool versions, operating environments, or usage that must be maintained
to preserve tool qualification.]

**Validator Statement:**  
I, [Validator Name], confirm that the tools used in the development, verification, and
validation of [Software Component / Project] have been qualified in accordance with
EN 50128:2011 §6.7 at SIL [level].

**Validator:** [Name]  
**Signature:** [Signature]  
**Date:** [Date]

---

## Appendix A: Tool Justification Records

[Detailed T2 and T3 tool classification justifications (§6.7.4.2) — one record per tool]

## Appendix B: Tool Test Evidence

[Detailed tool validation test logs, outputs, and evidence records (§6.7.4.5(d)–(g))]

## Appendix C: History-of-Use Records (§6.7.4.4a)

[For each tool using history-of-use evidence: list of prior projects, operational environments,
defect records, field experience summary]

---

**End of Tools Validation Report**
