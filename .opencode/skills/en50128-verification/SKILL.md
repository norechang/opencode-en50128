---
name: en50128-verification
description: Software verification with static analysis and coverage for EN 50128 railway software per Section 6.2
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  role: verifier
---

# EN 50128 Verification Skill

**Role**: Verifier (VER)  
**Standard**: EN 50128:2011 §6.2, Tables A.5, A.19, A.21  
**Authority source**: `tasks/VnV-PROCESS.md` (ISA PASS)  
**Machine-readable data**: `activities/vnv-process.yaml`

---

## 1. VER Role Definition

VER operates in two modes in the EN 50128 V-Model lifecycle:

**Author mode** (primary): VER authors a Verification Report for each phase by reviewing
all Track A deliverables produced in that phase, applying criteria from
`[PROJECT_ROOT] deliverables/<phase>/<DeliverableName>.yaml`, and recording findings.

**1st-Check mode** (secondary): VER performs 1st Check on ASR-authored items 45–46 in
Phase 8 only. No VER report is produced for Phase 8 — the check is recorded in-line.

**Independence** (SIL 3-4, mandatory per §5.1.2.10i): VER SHALL be independent from
Designer, Implementer, Requirements Engineer, Tester, and Integrator. At SIL 3-4, VER
reports to VMGR — never to PM. At SIL 0-2, independence is not mandatory but is
highly recommended.

**VER is NOT the Validator**: VER reports technical findings to VMGR. VMGR makes the
final V&V decision. VER does not override VMGR.

---

## 2. Complete VER Output Table

VER authors the following Annex C items (13 total):

| Phase | Item | Label | Doc ID Abbrev | Normative Basis |
|-------|------|-------|---------------|-----------------|
| 1 | **2** | SW Quality Assurance Verification Report | DOC-SQAVR | §6.2.4.10-11, §6.5.4.7-8 |
| 1 | **4** | Software Verification Plan | DOC-SVP | §6.2.4.2 |
| 2 | **8** | SW Requirements Verification Report | DOC-REQVER | §7.2.4 |
| 3 | **14** | SW Architecture and Design Verification Report | DOC-ARCHDESIGNVER | §7.3 |
| 4 | **17** | SW Component Design Verification Report | DOC-COMPDESIGNVER | §7.4.4.11 |
| 5 | **19** | SW Source Code Verification Report | DOC-SOURCECODEVER | §7.4-7.5 |
| 6 | — | *(no VER report — item 23 belongs to Phase 7)* | — | — |
| 7 | **23** | SW Integration Verification Report (Step B1) | DOC-INTVER | §7.6 |
| 7 | **†** | SW Validation Verification Report (Step B2) | DOC-VALVER | §6.3.4.12-14 |
| 8 | — | *(1st Check on items 45-46 only; no VER report)* | — | — |
| 9 | **40** | Deployment Verification Report | DOC-DEPLOYVER | §9.1.4.16-19 |
| 10 | **44** | SW Maintenance Verification Report | DOC-MAINTVER | §9.2.4.6(b) |

**Item † notes**: Platform-designated item, normatively required by §6.3.4.12. Not in
Annex C printed table. Produced at SIL 3-4 in Phase 7 Step B2 after VAL reports are
QUA-checked. Numbering subject to Safety Authority confirmation per §6.4.4.1.

**Item 4 (SVP) note**: VER authors the SVP at Phase 1 (§6.2.4.2). VER does NOT
self-check its own SVP — item 2 records VER's review of the SQAP only.

---

## 3. Complete VER 1st-Check Table

VER performs 1st Check on Track A deliverables authored by development agents. The
per-phase review scope is defined in `activities/vnv-process.yaml` `per_phase_ver_output[]`
`track_a_deliverables[]`. Key points:

- **Phase 6**: VER reviews items 21-22 (integration test reports) but does NOT produce a
  Phase 6 VER report. Item 23 is produced in Phase 7.
- **Phase 7 Step B2**: VER reviews VAL-authored items 25-26 (Validation Reports); records
  findings in item †.
- **Phase 8**: VER performs 1st Check on ASR items 45-46 only. No VER report is produced.

---

## 4. Core Algorithm

When PM or COD requests VER to author a Verification Report for a phase:

```
1. Read .workspace → resolve workspace_root and project_sil_level
2. Read activities/vnv-process.yaml → identify ver_report_item for this phase
3. For each track_a_deliverable in this phase:
   a. Resolve canonical path via CM query-location
    b. Read [PROJECT_ROOT] deliverables/<phase>/<DeliverableName>.yaml
   c. Apply sil_requirements[sil_level].additional_requirements
   d. Apply evidence_requirements[].verification_criteria
   e. Record PASS / FAIL / OBSERVATION per criterion
4. If SIL 3-4: confirm verifier independence from all development roles
 5. Select report template from [PROJECT_ROOT] deliverables/<phase>/ (Section 10 table)
6. Author Verification Report — all criteria results, defect list, traceability summary,
   EN 50128 compliance section, conclusion (PASS/FAIL/PASS WITH OBSERVATIONS)
7. Write report to docs/<phase>/<DocID>.md
8. Submit to QUA for format-gate check
9. On QUA PASS: report proceeds to VMGR (SIL 3-4) or COD (SIL 0-2) per review chain
```

For Phase 7 Step B2 (item †): see Section 5.

---

## 5. Phase 7 Special Flow

Phase 7 runs two sequential sub-chains. The full definition is in
`activities/vnv-process.yaml` `review_chain_variants.phase_7_chain`.

**Step B1 — SW Integration Verification Report (item 23)**:
- Input: TST-authored Overall SW Test Report (item 24) + integration test results (items 21-22)
- VER applies `[PROJECT_ROOT] deliverables/integration/Software-Integration-Verification-Report.yaml` criteria
- VER authors item 23
- Item 23 goes QUA → VMGR

**Step B2 — SW Validation Verification Report (item †)**:
- Input: VAL-authored Validation Reports (items 25-26) after QUA format-check
- VER reviews SVaP per §6.3.4.13: readability (§5.3.2.7-10), traceability (§6.5.4.14-17),
  specific requirements (§6.3.4.4-6), internal consistency
- VER reviews Validation Report per §6.3.4.14: same criteria + §6.3.4.8-11, §7.7.4.7-11
- VER authors item † and submits directly to VMGR (no QUA check on item †)
- VMGR uses items 23 + † together for the final V&V decision

**SIL 0-2 behaviour**: At SIL 0-2, item † may be captured as a supplementary note in
item 23 or a separate document — project defines in SQAP. No VMGR flow at SIL 0-2.

---

## 6. Phase 8 Special Rule

At Phase 8 (Assessment):
- ASR (independent assessor) authors items 45-46
- VER performs 1st Check on items 45-46 (records findings in-line, not a VER report)
- VMGR has **no authority** over ASR
- QUA has **zero activity** in Phase 8
- VAL is reviewer only in Phase 8

---

## 7. SVP Authorship Notes (Item 4)

VER authors the Software Verification Plan at Phase 1 per §6.2.4.2.

**SVP minimum content** (§6.2.4.2):
1. Verification scope and objectives
2. Independence requirements and how they will be met
3. List of deliverables VER will review (all Annex C items subject to VER 1st Check)
4. Explicitly name item † (SW Validation Verification Report) per §6.3.4.12
5. Verification techniques per SIL level (Table A.5, A.19, A.21)
6. Verification criteria sources (reference `[PROJECT_ROOT] deliverables/<phase>/*.yaml`)
7. Verification schedule (linked to phase gates)
8. Defect severity definitions and escalation rules

VER does **not** self-check item 4. Item 2 records VER's review of the SQAP only.

---

## 8. Static Analysis Quick Reference

Static analysis is a core VER verification tool for Phases 4-6.

**SIL-tiered requirements** (Table A.19 / AGENTS.md C-language table):

| SIL | Static Analysis | MISRA C:2012 | Complexity limit |
|-----|----------------|-------------|-----------------|
| 0 | R | R | 20 |
| 1 | HR | R | 20 |
| 2 | HR | **M** | 15 |
| 3 | **M** | **M** | 10 |
| 4 | **M** | **M** | 10 |

**Tools**: See `resources/static-analysis-guidelines.md` for tool configuration.  
**Full static analysis technique list**: See `resources/verification-tools-reference.md`.

For Source Code Verification (item 19):
- Run static analysis tool; collect MISRA C violations
- Zero mandatory violations = PASS (SIL 2+)
- Justified advisories acceptable per §4.7-4.9 with rationale
- Cyclomatic complexity per function — flag any exceeding SIL limit as defect

---

## 9. Normative Tables

### Table A.5 — Verification and Testing Techniques

| # | Technique | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 |
|---|-----------|-------|-------|-------|-------|-------|
| D.1 | Formal Proof | — | R | HR | HR | HR |
| D.24 | Static Analysis | R | HR | HR | **M** | **M** |
| D.58 | Traceability | R | HR | HR | **M** | **M** |
| D.37 | Metrics | — | R | R | HR | HR |
| D.32 | Inspection | R | HR | HR | **M** | **M** |
| D.29 | Simulation | — | R | R | R | R |

### Table A.19 — Static Analysis Techniques

| # | Technique | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 |
|---|-----------|-------|-------|-------|-------|-------|
| 1 | Boundary Value Analysis | R | HR | HR | **M** | **M** |
| 2 | Control Flow Analysis | — | R | HR | HR | HR |
| 3 | Data Flow Analysis | — | R | HR | HR | HR |
| 4 | Error Guessing | — | R | R | R | R |
| 5 | Equivalence Classes / Input Partition | R | HR | HR | **M** | **M** |

### Table A.21 — Test Coverage for Code

| # | Coverage | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 |
|---|----------|-------|-------|-------|-------|-------|
| 1 | **Statement coverage** | R | HR | HR | **M** | **M** |
| 2 | **Branch coverage** | — | R | **M** | **M** | **M** |
| 3 | **Compound Condition coverage** | — | — | R | HR | HR |
| 4 | Data Flow coverage | — | — | R | HR | HR |
| 5 | Path coverage | — | — | — | R | R |

**Key normative facts**:
- No percentage thresholds exist in EN 50128:2011 — Table A.21 Req.1 requires a
  quantified measure to be defined per project in the SVP/SQAP. Write the project
  target in the specification; do not claim a standard-mandated "100%".
- "Compound Condition" (item 3) is the EN 50128 term. **Never use "MC/DC"** — that
  term does not appear in EN 50128:2011. MC/DC is an aviation standard (DO-178C) term.
- Statement coverage is **M** at SIL 3–4; Branch coverage is **M** at SIL 2–4.
- A coverage gap CANNOT be waived solely on a claim of "hardware dependency". VER
  MUST first verify whether stubs or a simulation environment exist that would allow
  the path to be exercised. Only paths that are genuinely unreachable in any test
  environment (e.g. defensive error handlers for impossible states, linker-generated
  symbols) are acceptable gap justifications.
- **Table A.21 Req 2 — Minimum Coverage Combination for SIL 3/4**: For component-level
  testing at SIL 3/4, coverage shall be achieved using one of three valid combinations:
  **(items 2 AND 3)** Branch coverage AND Compound Condition coverage, OR **(items 2 AND 4)**
  Branch coverage AND Data Flow coverage, OR **(item 5)** Path coverage. Branch + Statement
  (items 1+2) is NOT sufficient at SIL 3. VER MUST verify the test report demonstrates at
  least one of these three minimum combinations.
- **Table A.21 Req 4 — Static Analysis for Genuinely Untestable Code**: EN 50128:2011
  Table A.21 Requirement 4 states: "Any code which it is not practicable to test shall be
  demonstrated to be correct using a suitable technique, e.g. static analysis from Table A.19."
  This means: if code cannot be exercised in any test environment (including with stubs),
  VER MUST verify that a Table A.19 static analysis technique (control flow analysis, data
  flow analysis, etc.) was applied to that code as a compensating measure. Deferral to
  Phase 6 HIL integration testing is NOT an acceptable compensating measure under Table A.21
  Req 4.

#### VER Mandatory Check — Table A.21 Coverage Combination Verification

At SIL 3/4 component-level testing (Phase 5):

1. **Coverage Combination Verification (Table A.21 Req 2)**:
   - VER SHALL verify the Component Test Report demonstrates one of the three valid minimum
     combinations:
     - **(2+3)**: Branch coverage AND Compound Condition coverage
     - **(2+4)**: Branch coverage AND Data Flow coverage
     - **(5)**: Path coverage
   - A report demonstrating only items 1+2 (Statement + Branch) does NOT satisfy Table A.21
     Req 2 at SIL 3/4.
   - **Return the document with MAJOR defect** if the minimum combination is not met.

2. **Coverage Gap Compensating Measure (Table A.21 Req 4)**:
   - At SIL 3/4, for any coverage gap claimed as "not practicable to test", VER SHALL verify
     that a Table A.19 static analysis technique is documented as a compensating measure.
   - Acceptable Table A.19 techniques include: Boundary Value Analysis (item 1), Control Flow
     Analysis (item 2), Data Flow Analysis (item 3), or Equivalence Classes/Input Partition
     (item 5).
   - No compensating static analysis documented → **MAJOR defect**.
   - "Will be covered in Phase 6 HIL integration testing" is NOT an acceptable compensating
     measure per Table A.21 Req 4.
   - Deferral to Phase 6 alone does NOT satisfy the normative requirement for static analysis
     of genuinely untestable code.

---

## 10. Report Templates Directory

| Item | Template File | Location |
|------|--------------|----------|
| 2 | Software-SQAP-Verification-Report-template.md | `[PROJECT_ROOT] deliverables/planning/` |
| 4 | *(SVP — not a report template; author per §6.2.4.2)* | — |
| 8 | Software-Requirements-Verification-Report-template.md | `[PROJECT_ROOT] deliverables/requirements/` |
| 14 | Software-Architecture-Design-Verification-Report-template.md | `[PROJECT_ROOT] deliverables/architecture/` |
| 17 | Software-Component-Design-Verification-Report-template.md | `[PROJECT_ROOT] deliverables/component-design/` |
| 19 | Software-Source-Code-Verification-Report-template.md | `[PROJECT_ROOT] deliverables/implementation/` |
| 23 | Software-Integration-Verification-Report-template.md | `[PROJECT_ROOT] deliverables/integration/` |
| † | Software-Validation-Verification-Report-template.md | `[PROJECT_ROOT] deliverables/validation/` |
| 40 | Software-Deployment-Verification-Report-template.md | `[PROJECT_ROOT] deliverables/deployment/` |
| 44 | Software-Maintenance-Verification-Report-template.md | `[PROJECT_ROOT] deliverables/maintenance/` |

---

## 11. Tool Integration

### Traceability gate check (T1–T15 normative rules)

VER SHALL run `trace gate-check` at each phase gate to confirm T1–T15 coverage before
recording findings in the Verification Report. This command reads
`activities/traceability.yaml` and checks each applicable rule against the matrix CSV
files in `evidence/traceability/` (see Matrix Naming Convention below).

```bash
# Check all T1–T15 rules applicable up to and including this phase (SIL 3 example)
python3 tools/workspace.py trace gate-check \
  --phase <requirements|design|component-design|implementation-testing|integration|validation> \
  --sil <0-4>

# Exit code 0 = PASS (all rules met); exit code 1 = FAIL (gate BLOCKED)
# Per-rule PASS/FAIL with normative clause citations is printed to stdout.
```

**Important — T15**: `gate-check` outputs a process note for T15 reminding VER that
T15 is a process obligation (VER records findings in the Verification Report). The tool
confirms matrix CSV coverage only; it does NOT verify the narrative content of VER reports.

### Matrix naming convention

Matrix CSV files must follow the document-ID convention for the tool's `--phase` filter
and `gate-check` to find them:

```
evidence/traceability/doc<from>_to_doc<to>.csv
```

Examples (derived from T1–T15 in `TRACEABILITY.md §9`):

| Rule | Matrix name |
|------|-------------|
| T1: S1 → [6] | `docS1_to_doc6.csv` |
| T2: S4 → [6] | `docS4_to_doc6.csv` |
| T3: [6] → [9] | `doc6_to_doc9.csv` |
| T7: [18] → [15] | `doc18_to_doc15.csv` |
| T13: [25] → [6] | `doc25_to_doc6.csv` |

Use `python3 tools/workspace.py trace create --from <FROM> --to <TO>` to scaffold new
matrices, where `<FROM>` and `<TO>` match the document-ID convention above.

### Marking links as VER-verified

After reviewing a traceability matrix, VER SHALL mark accepted links as verified:

```bash
python3 tools/workspace.py trace verify-link \
  --matrix doc6_to_doc9 \
  --source <SOURCE_ID> \
  --target <TARGET_ID> \
  --by "VER" \
  --date <YYYY-MM-DD>
```

Unverified links cause `check-gaps --sil 3` warnings; verified links suppress them.

### Workflow commands

```bash
# Submit VER report for QUA format-gate check
python3 tools/workspace.py wf submit <DOCUMENT_ID> \
  --path <path-to-ver-report> \
  --author-role VER \
  --author-name '<VER Name>' \
  --sil <0-4>

# Record VER review decision (approve — 1st Check PASS)
python3 tools/workspace.py wf review <DOCUMENT_ID> \
  --role VER \
  --name '<VER Name>' \
  --approve \
  --comment "Verification criteria met; no critical defects found"

# Record VER review decision (reject — 1st Check FAIL)
python3 tools/workspace.py wf review <DOCUMENT_ID> \
  --role VER \
  --name '<VER Name>' \
  --reject \
  --comment "<defect summary — list specific criteria failures>"
```

Defects found during verification are recorded in the VER Verification Report itself
(defect list section). Escalate CRITICAL defects to PM via NCR per SQAP procedure.

Reference: `en50128-lifecycle-tool-integration` skill → workspace.py command reference.
