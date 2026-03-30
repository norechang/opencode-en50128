---
name: en50128-testing
description: Software testing methodologies with coverage analysis for EN 50128 C programs using Unity test framework
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  language: C
  test-framework: Unity
---

# EN 50128 Testing Skill

This skill provides the TST agent with authoritative reference data, test specification
and report generation algorithms, Table A.5/A.21 technique tables, and defect remediation
logic for software testing per EN 50128 §5.3.4, §7.4–7.7.
**Load this skill before performing any TST activity.**

---

## 1. Authoritative Sources

| What you need | Where to find it |
|---------------|-----------------|
| Phase 2 activities, item 7 deliverable paths | `activities/phase-2-requirements.yaml` |
| Phase 4 activities, item 16 deliverable paths | `activities/phase-4-component-design.yaml` |
| Phase 5 activities, item 20 deliverable paths | `activities/phase-5-implementation-testing.yaml` |
| Phase 7 activities, item 24 deliverable paths | `activities/phase-7-validation.yaml` |
| Item 7/16/20/24 ownership, doc IDs, SIL obligations | `activities/deliverables.yaml` |
| Annex C Table C.1 — full deliverable ownership catalogue | `DELIVERABLES.md` |
| Traceability rules T1–T15 (human-readable) | `TRACEABILITY.md` |
| Traceability obligations T1–T15 (machine-readable, agent consumption) | `activities/traceability.yaml` |
| Authority structure, two-track loop, CCB re-entry | `WORKFLOW.md` |
| Independence matrix (TST = HR at SIL 3–4) | `ORGANIZATION.md` |
| §5.3.4, §7.4–7.7, Table A.5, A.13, A.21 | `std/EN50128-2011.md` |
| Component Test Specification template | `[PROJECT_ROOT] deliverables/component-design/Component-Test-Specification-template.md` |
| Component Test Report template | `[PROJECT_ROOT] deliverables/implementation/Component-Test-Report-template.md` |
| Overall Software Test Specification template | `[PROJECT_ROOT] deliverables/requirements/Overall-Software-Test-Specification-template.md` |
| Overall Software Test Report template | `[PROJECT_ROOT] deliverables/validation/Overall-Software-Test-Report-template.md` |
| Source code (TST input, item 18) | CM `query-location --doc source-code` |
| Component Design Spec (item 15) | CM `query-location --doc component-design-spec` |

---

## 2. TST Phase Footprint

| Annex C Item | Document | Owner | Phase |
|---|---|---|---|
| 7 | Overall Software Test Specification | **TST** | 2 |
| 16 | Software Component Test Specification | **TST** | 4 |
| 18 | Software Source Code | IMP | 5 |
| 20 | Software Component Test Report | **TST** | 5 |
| 21 | Software Integration Test Report | INT | 6 |
| 22 | HW/SW Integration Test Report | INT | 6 |
| 24 | Overall Software Test Report | **TST** | 7 |

- TST independence: HR at SIL 3–4 (tester must be independent from implementer). See `ORGANIZATION.md`.
- TST MUST NOT also act as VER (independence boundary — separate oversight roles).
- TST MUST NOT contact QUA or VER directly — route all submissions through PM.

---

## 3. write-test-specs Algorithm (items 7 and 16)

Follow these steps in order. Do not skip steps.

1. **Invoke CM `query-location`** via `task` tool with `--doc component-test-spec` (item 16)
   or `--doc overall-sw-test-spec` (item 7). Record the canonical path.

2. **Read `.workspace`** to confirm active project name, SIL level, and base path.

3. **Verify prerequisites**:
   - Item 16 (Phase 4): locate Software Component Design Specification (item 15).
   - Item 7 (Phase 2): locate SRS (item 6). If either prerequisite is missing, halt and report to PM.

 4. **Load the appropriate template** (`[PROJECT_ROOT] deliverables/component-design/Component-Test-Specification-template.md` or
    `[PROJECT_ROOT] deliverables/requirements/Overall-Software-Test-Specification-template.md`). Instantiate it for the project.

5. **Derive test cases** — for each requirement in scope:
   - Normal-operation test case (happy path, verifiable output).
   - Boundary-value test cases (min−1, min, min+1, max−1, max, max+1) — **M SIL 3–4**.
   - Error-condition test cases (NULL inputs, invalid ranges, return-value errors).
   - Safety-critical-path test cases where the requirement has a SIL designation.

6. **Embed traceability** in every test case header:
   ```
   /* TC-[TYPE]-[NNN]: [short description]
    * Tests: REQ-[ID]
    * SIL: <level>
    * Coverage target: [Statement|Branch|Compound Condition] per SVP/SQAP
    */
   ```

7. **Specify coverage targets**: cite the SVP/SQAP project-defined target — do not
   substitute a generic percentage. Apply Table A.21 technique obligations per SIL
   (see Section 5 below).

8. **Apply mandatory Table A.5 techniques** by SIL level (see Section 4 below).

9. **Return** the completed specification document path and a traceability summary
   (requirements covered, gaps) to PM.

---

## 4. execute-component-tests Algorithm (item 20)

1. **Invoke CM `query-location`** via `task` tool with `--doc component-test-report`.
   Record the canonical output path.

2. **Verify item 18 (source code) exists**. Halt and report to PM if missing.

3. **Build unit tests** with gcov instrumentation:
   ```
   gcc -fprofile-arcs -ftest-coverage -g -O0 -o <test_binary> <src>.c <test>.c unity.c
   ```

4. **Execute tests**. Capture Unity XML output (machine-readable — required per §7.6.4.5b).

5. **Generate coverage data**:
   ```
   gcov <src>.c
   lcov --capture --directory . --output-file coverage.info
   genhtml coverage.info --output-directory coverage_html
   gcovr --json --output coverage.json
   ```

6. **Verify coverage meets the project-defined target** from the SVP/SQAP.
   Document any gaps with justification (required SIL 2+).

 7. **Load template** `[PROJECT_ROOT] deliverables/implementation/Component-Test-Report-template.md`. Fill:
   - Test execution summary (pass/fail counts, execution date, tester identity).
   - Coverage metrics table (coverage type, target, actual, status).
   - Defect list (reference to defect IDs in the project defect tracker).
   - Evidence references (XML result file, coverage HTML/JSON paths).

8. **Return** report path, pass/fail status, and coverage summary to PM.

---

## 5. Table A.5 Techniques (§7.4, §7.5, §7.7)

| # | Technique/Measure | Ref | SIL 0 | SIL 1–2 | SIL 3–4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | Formal Proof | D.29 | – | R | HR |
| 2 | Probabilistic Testing | D.44 | – | R | R |
| 3 | **Static Analysis** | A.19 | – | HR | **M** |
| 4 | **Dynamic Analysis and Testing** | A.13 | – | HR | **M** |
| 5 | **Test Coverage for Code** | A.21 | R | HR | **M** |
| 6 | Metrics | D.37 | – | R | HR |
| 7 | **Traceability** | D.58 | R | HR | **M** |
| 8 | Software Error Effect Analysis | D.25 | – | R | HR |
| 9 | **Functional/Black-Box Testing** | A.14 | HR | HR | **M** |
| 10 | **Performance Testing** | A.18 | – | HR | **M** |
| 11 | Interface Testing | D.34 | HR | HR | HR |
| 12 | **Regression Testing** | D.46 | HR | HR | **M** |
| 13 | **Boundary Value Analysis** | D.7 | R | HR | **M** |
| 14 | Equivalence Classes | D.20 | R | HR | HR |
| 15 | Error Guessing | D.21 | – | R | R |
| 16 | Cause Consequence Diagrams | D.9 | – | R | HR |

**Mandatory SIL 3–4**: items 4, 5, 7, 9, 10, 12, 13.
**Static analysis (item 3)** is owned by VER — TST provides coverage evidence; VER owns the Static Analysis Report (item 19).

---

## 6. Table A.21 Coverage Techniques

| # | Coverage Type | SIL 0 | SIL 1 | SIL 2 | SIL 3–4 |
|---|---------------|-------|-------|-------|---------|
| 1 | **Statement Coverage** | HR | HR | HR | **M** |
| 2 | **Branch Coverage** | HR | HR | **M** | **M** |
| 3 | **Compound Condition Coverage** | – | R | R | HR |
| 4 | Data Flow Coverage | – | R | R | HR |
| 5 | Path Coverage | – | – | – | R |

**Key normative facts**:
- No percentage thresholds exist in EN 50128:2011 — Table A.21 Req.1 requires a quantified
  measure to be defined per project in the SVP/SQAP. Write the project target in the
  specification; do not claim a standard-mandated "100%".
- "Compound Condition" (item 3) is the EN 50128 term. Never use "MC/DC" — that term is not
  in EN 50128:2011. Compound Condition is HR (not M) for SIL 3–4.
- Statement coverage is **M** at SIL 3–4; Branch coverage is **M** at SIL 2–4.

---

## 7. Defect Remediation (fix-defects)

When PM routes QUA/VER findings to TST, apply this table:

| Finding Code | Description | Action | Confidence |
|---|---|---|---|
| `T001` | Test case missing for requirement | Add test case from SRS requirement | HIGH — auto-fix |
| `T002` | Coverage gap — uncovered branch | Add test case targeting the uncovered branch | HIGH — auto-fix |
| `T003` | Traceability header missing in test | Add `/* TC-...: Tests: REQ-... */` header | HIGH — auto-fix |
| `T004` | Non-machine-readable result format | Convert to XML/JSON output | HIGH — auto-fix |
| `T005` | Boundary value not tested | Add min−1, min, min+1, max−1, max, max+1 cases | HIGH — auto-fix |
| `T006` | Coverage target not cited (SVP/SQAP) | Add reference to project-defined target | HIGH — auto-fix |
| `T007` | Wrong coverage term ("MC/DC" used) | Replace with "Compound Condition" | HIGH — auto-fix |
| `T008` | Algorithmic correctness of test assertions | Escalate to PM — requires REQ/DES review | LOW — escalate |
| `T009` | Safety-critical path not tested | Escalate to PM — requires SAF input | LOW — escalate |

---

## 8. Document Interactions

```
SRS (item 6, REQ) + SCDS (item 15, DES)
  └─► TST reads → writes: Overall SW Test Spec (item 7) [TST owns, Phase 2]
                           Component Test Spec (item 16)  [TST owns, Phase 4]
                                │
Source Code (item 18, IMP)      │
  └─► TST reads →               │
        executes item 16 → writes: Component Test Report (item 20) [TST owns, Phase 5]
        executes item 12 → returns results to INT (INT writes item 21) [Phase 6]
        executes item 7  → writes: Overall SW Test Report (item 24)   [TST owns, Phase 7]
                                                                              │
                                                                    VAL reads item 24
                                                                    → produces release decision
```

**TST provides to**: PM (all deliverables and results for routing), INT (integration test
execution results), VAL (system test execution results and item 24).

**TST receives from**: REQ (SRS item 6 for traceability), DES (SCDS item 15), IMP (source
code item 18), INT (integration test specifications item 12), PM (task assignment, defect routing).

**TST does NOT contact**: QUA, VER, or VAL directly. All submissions go through PM.
