---
name: en50128-integration
description: Software integration strategies and testing for EN 50128 compliant C programs
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  language: C
---

# EN 50128 Integration Skill

This skill provides the INT agent with authoritative reference data, integration test
specification and report generation algorithms, Table A.6 technique table, and defect
remediation logic for software integration per EN 50128 §5.3.6 and §7.6.
**Load this skill before performing any INT activity.**

---

## 1. Authoritative Sources

| What you need | Where to find it |
|---------------|-----------------|
| Phase 3 activities, items 12/13 deliverable paths | `activities/phase-3-architecture-design.yaml` |
| Phase 6 activities, items 21/22 deliverable paths | `activities/phase-6-integration.yaml` |
| Item 12/13/21/22 ownership, doc IDs, SIL obligations | `activities/deliverables.yaml` |
| Annex C Table C.1 — full deliverable ownership catalogue | `DELIVERABLES.md` |
| Traceability rules T1–T15 (human-readable) | `TRACEABILITY.md` |
| Traceability obligations T1–T15 (machine-readable, agent consumption) | `activities/traceability.yaml` |
| Authority structure, two-track loop, CCB re-entry | `WORKFLOW.md` |
| Independence matrix (INT = No at all SIL levels) | `ORGANIZATION.md` |
| §5.3.6, §7.6, Table A.6 integration requirements | `std/EN50128-2011.md` |
| SW Integration Test Specification template | `templates/Software-Integration-Test-Specification-template.md` |
| SW Integration Test Report template | `templates/Software-Integration-Test-Report-template.md` |
| HW/SW Integration Test Specification template | `templates/Hardware-Software-Integration-Test-Specification-template.md` |
| HW/SW Integration Test Report template | `templates/Hardware-Software-Integration-Test-Report-template.md` |
| Software Architecture Specification (item 9) | CM `query-location --doc sas` |
| Software Design Specification (item 10) | CM `query-location --doc sds` |

---

## 2. INT Phase Footprint

| Annex C Item | Document | Owner | Phase |
|---|---|---|---|
| 12 | Software Integration Test Specification | **INT** | 3 |
| 13 | HW/SW Integration Test Specification | **INT** | 3 |
| 21 | Software Integration Test Report | **INT** | 6 |
| 22 | HW/SW Integration Test Report | **INT** | 6 |
| 23 | Software Integration Verification Report | VER | 6 |

- INT independence: Not required at any SIL level (see `ORGANIZATION.md`).
- INT + TST MAY be the same person (§5.1.2.10c); HR to be separate at SIL 3–4.
- INT MUST NOT act as VER (VER verifies INT output — independence boundary).
- INT MUST NOT contact QUA or VER directly — route all submissions through PM.

---

## 3. write-integration-test-specs Algorithm (items 12 and 13)

Follow these steps in order. Do not skip steps.

1. **Invoke CM `query-location`** via `task` tool with `--doc sw-integration-test-spec`
   (item 12) and `--doc hw-sw-integration-test-spec` (item 13). Record canonical paths.

2. **Read `.workspace`** to confirm active project name, SIL level, and base path.

3. **Verify Phase 3 prerequisites**: locate SAS (item 9) and SDS (item 10). If missing,
   halt and report to PM.

4. **Choose integration strategy** from the SAS component hierarchy:
   - **Bottom-up**: start with lowest-level modules; no stubs required; preferred for C.
   - **Top-down**: start with highest-level module; requires stubs for lower levels.
   - **Sandwich**: combine both directions; recommended when both H/W and S/W risks exist.
   Document the rationale for the chosen strategy in Section 2 of the specification.

5. **Load template** `Software-Integration-Test-Specification-template.md`. Instantiate
   for the project. For each interface in the SAS/SDS:

   a. Create an interface test case:
      ```
      TC-INT-[NNN]: [Interface name] — normal data flow
      Tests: SAS §<section> / SDS §<section>
      SIL: <level>
      Type: Interface (M SIL 3-4)
      ```
   b. Create error-condition test cases: NULL pointer, invalid ranges, error propagation
      across the interface boundary.
   c. Create performance test cases (HR SIL 3–4): timing constraints from the SDS.

6. **Apply Table A.6 mandatory and HR techniques** by SIL level (see Section 5 below).

7. **Produce item 13** (HW/SW Integration Test Specification) using template
   `Hardware-Software-Integration-Test-Specification-template.md` — covers target
   hardware interaction, memory-mapped I/O interfaces, timing under hardware load.

8. **Return** specification document paths and traceability summary to PM.

---

## 4. write-integration-test-reports Algorithm (items 21 and 22)

**PRECONDITION**: TST must have executed the integration tests and provided machine-readable
results (XML/JSON) to PM. PM routes results to INT. INT MUST NOT proceed without actual
TST results.

1. **Invoke CM `query-location`** via `task` tool with `--doc sw-integration-test-report`
   (item 21) and `--doc hw-sw-integration-test-report` (item 22). Record canonical paths.

2. **Read TST results** from the XML/JSON file provided by PM. Verify the file is present
   and non-empty. If results are missing, halt and report to PM.

3. **Load template** `Software-Integration-Test-Report-template.md`. Populate:
   - Executive summary: test period, overall PASS/FAIL verdict.
   - Component identity table: name, version, git commit SHA, configuration baseline.
   - Test results table: test case ID, result (PASS/FAIL), actual vs expected, date.
   - Coverage metrics: interface coverage (target 100%), branch coverage per SVP/SQAP.
   - Defect list: defect IDs, severity, status.
   - Evidence references: XML/JSON result file path, coverage data path.
   - Table A.6 compliance matrix (see Section 5).

4. **State whether exit criteria are met**. If not met, document failure circumstances
   explicitly per §7.6.4.5c.

5. **Produce item 22** from template `Hardware-Software-Integration-Test-Report-template.md`
   using the HW/SW test results subset from TST.

6. **Return** report paths and verdict to PM.

---

## 5. Table A.6 Techniques (§7.6)

| # | Technique/Measure | Ref | SIL 0 | SIL 1–2 | SIL 3–4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | **Functional and Black-Box Testing** | A.14 | HR | HR | HR |
| 2 | Non-functional Testing | – | R | R | R |
| 3 | **Interface Testing** | D.34 | HR | HR | **M** |
| 4 | **Performance Testing** | A.18 | – | R | HR |
| 5 | Structural Coverage (Statement) | A.21 | R | HR | HR |
| 6 | **Structural Coverage (Branch)** | A.21 | R | HR | **M** |
| 7 | Error Guessing | D.21 | – | R | R |
| 8 | Cause Consequence Diagrams | D.9 | – | R | HR |

**Mandatory SIL 3–4**: items 3 (Interface Testing) and 6 (Branch Coverage).
**HR SIL 3–4**: items 1 (Functional/Black-Box) and 4 (Performance Testing).
Document technique selection rationale in the integration test specification Section 2.

---

## 6. Defect Remediation (fix-defects)

When PM routes QUA/VER findings to INT, apply this table:

| Finding Code | Description | Action | Confidence |
|---|---|---|---|
| `I001` | Interface test case missing | Add test case for each untested interface | HIGH — auto-fix |
| `I002` | Traceability header missing | Add `TC-INT-NNN: Tests: SAS §<n>` header | HIGH — auto-fix |
| `I003` | Integration strategy not documented | Add strategy rationale to specification Section 2 | HIGH — auto-fix |
| `I004` | Machine-readable results not referenced | Add reference to TST XML/JSON file in report | HIGH — auto-fix |
| `I005` | Exit criteria verdict not stated | Add explicit PASS/FAIL verdict against each exit criterion | HIGH — auto-fix |
| `I006` | Failure circumstances not documented | Add failure description per §7.6.4.5c | HIGH — auto-fix |
| `I007` | Table A.6 compliance matrix missing | Add technique compliance matrix to report | HIGH — auto-fix |
| `I008` | HW/SW interface not covered | Escalate to PM — requires DES/hardware team input | LOW — escalate |
| `I009` | Performance result interpretation | Escalate to PM — requires SDS timing spec review | LOW — escalate |

---

## 7. Document Interactions

```
SAS (item 9, DES) + SDS (item 10, DES)
  └─► INT reads → writes: SW Integration Test Spec    (item 12) [INT owns, Phase 3]
                           HW/SW Integration Test Spec (item 13) [INT owns, Phase 3]
                                │
                                ├─► TST reads spec (item 12) → executes → returns XML/JSON results
                                │
Source Code (item 18, IMP) ─────┘
  └─► TST executes integration tests (Phase 6)
        │
        └─► TST returns results to PM
              │
              └─► PM routes results to INT
                    └─► INT writes: SW Integration Test Report    (item 21) [INT owns, Phase 6]
                                    HW/SW Integration Test Report (item 22) [INT owns, Phase 6]
                                          │
                                    VER reads → writes item 23 (SW Integration VER Report) [VER owns]
```

**INT provides to**: PM (all deliverables for QUA/VER routing), TST (spec items 12/13
for test execution), VER (items 21/22 for verification).

**INT receives from**: DES (SAS item 9, SDS item 10), TST via PM (test execution
results for items 21/22), PM (task assignment, defect routing).

**INT does NOT contact**: QUA or VER directly. All submissions go through PM.
