# EN 50128 Verification Skill
---
name: en50128-verification
---

**Role**: Verifier (VER)  
**Standard**: EN 50128:2011 §6.2, Tables A.5, A.19, A.21  
**Authority source**: `tasks/VnV-PROCESS.md` (ISA PASS)  
**Machine-readable data**: `activities/vnv-process.yaml`

---

## 1. VER Role Definition

VER operates in two modes in the EN 50128 V-Model lifecycle:

**Author mode** (primary): VER authors a Verification Report for each phase by reviewing
all Track A deliverables produced in that phase, applying criteria from
`deliverables/<phase>/<DeliverableName>.yaml`, and recording findings.

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
   b. Read deliverables/<phase>/<DeliverableName>.yaml
   c. Apply sil_requirements[sil_level].additional_requirements
   d. Apply evidence_requirements[].verification_criteria
   e. Record PASS / FAIL / OBSERVATION per criterion
4. If SIL 3-4: confirm verifier independence from all development roles
 5. Select report template from deliverables/<phase>/ (Section 10 table)
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
- VER applies `deliverables/integration/Software-Integration-Verification-Report.yaml` criteria
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
6. Verification criteria sources (reference `deliverables/<phase>/*.yaml`)
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
| 1 | Statement coverage | R | HR | HR | HR | HR |
| 2 | Branch coverage | — | R | HR | HR | HR |
| 3 | Compound condition coverage | — | — | R | HR | HR |
| 4 | MC/DC coverage | — | — | — | R | HR |

**Note**: EN 50128 does not specify a mandatory percentage threshold for coverage;
the requirement is to apply the technique at the stated level. Full coverage (100%) is
a project-defined acceptance criterion documented in the SVP.

---

## 10. Report Templates Directory

| Item | Template File | Location |
|------|--------------|----------|
| 2 | Software-SQAP-Verification-Report-template.md | `deliverables/planning/` |
| 4 | *(SVP — not a report template; author per §6.2.4.2)* | — |
| 8 | Software-Requirements-Verification-Report-template.md | `deliverables/requirements/` |
| 14 | Software-Architecture-Design-Verification-Report-template.md | `deliverables/architecture/` |
| 17 | Software-Component-Design-Verification-Report-template.md | `deliverables/component-design/` |
| 19 | Software-Source-Code-Verification-Report-template.md | `deliverables/implementation/` |
| 23 | Software-Integration-Verification-Report-template.md | `deliverables/integration/` |
| † | Software-Validation-Verification-Report-template.md | `deliverables/validation/` |
| 40 | Software-Deployment-Verification-Report-template.md | `deliverables/deployment/` |
| 44 | Software-Maintenance-Verification-Report-template.md | `deliverables/maintenance/` |

---

## 11. Tool Integration

VER uses `workspace.py wf` commands from `activities/workflow.yaml`:

```bash
# Record VER review result (1st Check)
python3 workspace.py wf review --item <annex_c_item> --result PASS|FAIL \
  --reviewer VER --report <path-to-ver-report>

# Submit VER report for QUA format-gate check
python3 workspace.py wf submit --item <annex_c_item> --doc <path>

# Log defect found during verification
python3 workspace.py wf log-defect --ncr <DEF-ID> --severity MINOR|MAJOR|CRITICAL \
  --item <annex_c_item> --description "<description>"
```

Reference: `en50128-lifecycle-tool-integration` skill → workspace.py command reference.
