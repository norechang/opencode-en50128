---
name: en50128-quality
description: Software quality assurance techniques and auditing for EN 50128 railway software
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  role: quality-assurance
---

# EN 50128 Quality Assurance Skill

**Role**: Quality Assurance Engineer (QUA)  
**Standard**: EN 50128:2011 §6.5, Table A.9  
**Authority source**: `tasks/QUALITY_PROCESS.md` (ISA PASS)  
**Machine-readable data**: `activities/quality-process.yaml`

---

## 1. QUA Role Definition

QUA is the **FORMAT gate-keeper** in the EN 50128 V-Model lifecycle. QUA sits between
deliverable production and the PM→COD handoff on every phase (Track A). QUA also checks
VER and VAL report FORMAT before VMGR reviews technical content (Track B).

**QUA checks four things on every deliverable — nothing else:**

| Check | What it covers |
|-------|---------------|
| Document ID format | `DOC-[ABBREV]-[YYYY]-[NNN]` regex match |
| Document Control table | Version, Date, Author, Status fields present |
| Approvals table | Correct roles for SIL level present and signed |
| Required sections | Document-type-specific mandatory section headings present |

**QUA does NOT check:**
- Technical correctness of requirements, design, or code
- MISRA C compliance, cyclomatic complexity, static analysis results
- Traceability link completeness (VER checks T1–T15 per `TRACEABILITY.md`)
- Test adequacy or coverage figures
- Tool qualification evidence

These are VER/IMP/TST responsibilities. QUA audits that VER evidence *exists* (process
audit capability) — QUA does not independently re-execute those checks.

**Independence**: QUA SHALL NOT report to DES, IMP, TST, or Software Manager. QUA
reports to COD/PM. Independence is platform governance policy — EN 50128:2011 does not
contain a normative QUA independence requirement (see `ORGANIZATION.md` Independence
Reference Matrix: QUA = "No" at all SIL levels).

---

## 2. Deliverable Touchpoints

QUA has a touchpoint on **every Annex C deliverable** except items 45 and 46 (ASR
documents — fully independent, no QUA role). The authoritative touchpoint table is in
`tasks/QUALITY_PROCESS.md` Diagram 2 and `activities/quality-process.yaml`
`deliverable_touchpoints[]`.

**qua_check_type values** (from `quality-process.yaml`):

| Value | Meaning | Iteration limit |
|-------|---------|-----------------|
| `template_compliance` | Standard format-gate check | 3 iterations, then PM escalates |
| `template_compliance_one_pass` | VER or VAL report — 1-Pass Rule | 1 resubmission; 2nd rejection = process failure |
| `none` | Phase 8 ASR documents — no QUA role | — |

**Summary counts** (from `quality-process.yaml` `deliverable_touchpoint_summary`):
- Items with standard QUA check: 23
- Items with 1-Pass Rule (VER/VAL reports): 14
- Items with no QUA check (ASR): 2
- Total in scope: 37 (items 1–27 + 36–46; §8 items 28–35 excluded)

**Phase 8 rule**: QUA has ZERO activity. Do not review, check, or comment on items 45
(Software Assessment Plan) or 46 (Software Assessment Report).

---

## 3. Format-Gate Algorithm

When PM submits a deliverable for QUA review:

```
1. Read .workspace → resolve workspace root
2. Invoke CM query-location to confirm canonical path of deliverable
3. Read deliverable at canonical path
4. Identify document type → load [SKILL_ROOT] review-criteria/generic-format-checker.yaml
5. Identify sections supplement → load [SKILL_ROOT] review-criteria/sections/<doc-key>-sections.yaml
6. Apply generic checks (Document ID, Document Control, Approvals)
7. Apply sections check (all required sections present?)
8. Collect all failures
9. Determine qua_check_type from quality-process.yaml for this annex_c_item
10. Write QUA Review Report to canonical path (CM query-location for QUAREPORT)
11. Report PASS or FAIL to PM
```

**On PASS**: PM is notified; deliverable proceeds to VER (Track A) or VMGR (Track B for
VER/VAL reports).

**On FAIL**: Return defect list to PM. PM routes to document author for fix. Track iteration
count per item.

**Iteration limit enforcement**:
- `template_compliance` items: after 3 FAIL cycles, QUA raises NCR against author; escalates
  to PM for mandatory training intervention. Do not block indefinitely — escalate.
- `template_compliance_one_pass` items (VER/VAL reports): 1 resubmission allowed. On 2nd
  rejection: QUA raises NCR severity=MAJOR, flags as process failure to PM; PM must
  escalate to VMGR for SIL 3–4, or handle per SQAP for lower SIL.

---

## 4. Generic Format Checker

**File**: `[SKILL_ROOT] review-criteria/generic-format-checker.yaml`

The generic checker is parameterized by `doc_abbreviation` (e.g. `SQAP`, `SRS`) and
`sil_level` (0–4). It enforces three universal rules:

### Rule GF-001: Document ID Format

```
Pattern:  DOC-<ABBREV>-<YYYY>-<NNN>
Example:  DOC-SRS-2026-001
Severity: error
```

Check that the Document Control table contains a `Document ID` field whose value matches
`DOC-[A-Z]+-[0-9]{4}-[0-9]{3}`. The abbreviation segment must match the expected
abbreviation for the document type (from `deliverables.yaml` `abbreviation` field).

### Rule GF-002: Document Control Table

Required fields: `Document ID`, `Version`, `Date`, `Author`, `Status`.
All five fields must be present and non-empty.
Severity: error.

### Rule GF-003: Approvals Table

Required columns: `Role`, `Name`, `Signature`, `Date`.
Required roles by SIL (minimum):

| SIL | Required roles |
|-----|---------------|
| 0–2 | Author, Reviewer (QUA), Approver (PM) |
| 3–4 | Author, Reviewer (QUA), Approver (PM) — plus independent VER sign-off managed by VMGR outside this table |

Note: VER, VAL, VMGR are Track B roles. They do not appear as Approvals table signatories
on development deliverables. Approvals table lists Track A sign-off only.
Severity: error.

---

## 5. Sections Supplement

**Directory**: `[SKILL_ROOT] review-criteria/sections/`

Each file lists the mandatory section headings for one document type. The generic checker
loads the appropriate supplement based on document type and checks that every listed
section heading is present in the document (exact string match, case-insensitive).

Section files follow the naming convention: `<doc-key>-sections.yaml`
where `<doc-key>` is the lowercase abbreviation from `deliverables.yaml`.

**Available supplements** (one per document type with QUA touchpoint):

| Annex C item | Doc key | Sections file |
|---|---|---|
| 1 | SQAP | `sqap-sections.yaml` |
| 2 | SQAVR | `sqavr-sections.yaml` |
| 3 | SCMP | `scmp-sections.yaml` |
| 4 | SVP | `svp-sections.yaml` |
| 5 | SVaP | `svap-sections.yaml` |
| 6 | SRS | `srs-sections.yaml` |
| 7 | OTSTSPEC | `otstspec-sections.yaml` |
| 8 | REQVER | `reqver-sections.yaml` |
| 9 | SAS | `sas-sections.yaml` |
| 10 | SDS | `sds-sections.yaml` |
| 11 | INTERFACES | `interfaces-sections.yaml` |
| 12 | INTTESTSPEC | `inttestspec-sections.yaml` |
| 13 | HWINTTESTSPEC | `hwinttestspec-sections.yaml` |
| 14 | ARCHDESIGNVER | `archdesignver-sections.yaml` |
| 15 | COMPDESIGN | `compdesign-sections.yaml` |
| 16 | COMPTESTSPEC | `comptestspec-sections.yaml` |
| 17 | COMPDESIGNVER | `compdesignver-sections.yaml` |
| 18 | SOURCECODE | `sourcecode-sections.yaml` |
| 19 | SOURCECODEVER | `sourcecodever-sections.yaml` |
| 20 | COMPTESTRPT | `comptestrpt-sections.yaml` |
| 21 | INTTESTRPT | `inttestrpt-sections.yaml` |
| 22 | HWINTTESTRPT | `hwinttestrpt-sections.yaml` |
| 23 | INTVER | `intver-sections.yaml` |
| 24 | OVERALLTESTRPT | `overalltestrpt-sections.yaml` |
| 25 | VALRPT | `valrpt-sections.yaml` |
| 26 | TOOLSVALRPT | `toolsvalrpt-sections.yaml` |
| 27 | RELEASENOTE | `releasenote-sections.yaml` |
| 36 | DEPLOYPLAN | `deployplan-sections.yaml` |
| 37 | DEPLOYMAN | `deployman-sections.yaml` |
| 38 | RELEASENOTES | `releasenotes-sections.yaml` |
| 39 | DEPLOYREC | `deployrec-sections.yaml` |
| 40 | DEPLOYVER | `deployver-sections.yaml` |
| 41 | MAINTPLAN | `maintplan-sections.yaml` |
| 42 | CHANGEREC | `changerec-sections.yaml` |
| 43 | MAINTREC | `maintrec-sections.yaml` |
| 44 | MAINTVER | `maintver-sections.yaml` |

**Delivery-package documents** (item 18 SOURCECODE): sections check is minimal — checks
that a package manifest / index section exists. QUA does not inspect code content.

---

## 6. SQAP Authorship (Capability 2)

Per §6.5.4.3 and deviation D8 (`DELIVERABLES.md`):

- QUA **authors** the Software Quality Assurance Plan (item 1) under VER direction
- QUA **cannot 2nd-check its own plan** (self-certification conflict)
- VER performs the 1st check (SQAVR, item 2)
- The SQAP itself must document the role split (deviation D8)

**SQAP minimum content** (§6.5.4.5):
1. Lifecycle model definition (activities, entry/exit criteria, I/O, quality activities, responsible entities)
2. Documentation structure
3. Documentation control (roles for write/check/approval, distribution, archiving)
4. Tracking and tracing of deviations
5. Methods, measures and tools per SIL level (reference Table A.9)
6. Justifications for technique selections per §4.7–4.9
7. Platform deviations D1–D8 (from `DELIVERABLES.md`) — mandatory entry
8. Update procedure: frequency, responsibility, method (§6.5.4.9)

**Table A.9 — SIL-tiered obligations to document in SQAP**:

| # | Technique | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 |
|---|-----------|-------|-------|-------|-------|-------|
| T1 | EN ISO 9001 accreditation | R | HR | HR | HR | HR |
| T2 | EN ISO 9001 compliance | M | M | M | M | M |
| T3 | EN ISO 9001 certification | — | — | HR | HR | HR |
| T4 | Company Quality System | M | M | M | M | M |
| T5 | Software Configuration Management | M | M | M | M | M |
| T6 | Traceability | R | HR | HR | M | M |
| T7 | Metrics | — | R | R | R | R |
| T8 | Data Recording and Analysis | HR | HR | HR | M | M |

M = Mandatory, HR = Highly Recommended, R = Recommended, — = No recommendation.

---

## 7. Process Audit (Capability 3)

QUA audits that evidence **exists** — QUA does not re-execute technical checks.

**Per-phase audit scope** (from `tasks/QUALITY_PROCESS.md` Diagram 1):

| Phase | QUA audit check |
|-------|----------------|
| 1 | SQAP issued; SCMP issued; SVP produced by VER; SVaP produced by VAL |
| 2 | Hazard log initiated; SIL assignments recorded; traceability audit (VER performed T1–T2) |
| 3 | FMEA/FTA evidence exists (SAF); architecture meets SIL constraints (VER evidence, not QUA re-check) |
| 4 | Component test specs exist; component design reviewed |
| 5 | Static analysis report exists; MISRA evidence record exists; coverage record exists (QUA audits evidence, not values) |
| 6 | Integration test results recorded; SW/HW integration test results recorded |
| 7 | Validation report exists; Overall Software Test Report exists |
| 8 | **No QUA activity** |
| 9 | Release package complete; deployment records present |
| 10 | Maintenance records; change records per §9.2.4 |

**Audit output**: Audit Finding record → NCR if non-conformance found → PM for resolution.

---

## 8. Non-Conformance Management (Capability 4)

**NCR fields**:
- NCR ID: `NCR-[YYYY]-[NNN]`
- Phase: phase number where found
- Annex C item (if deliverable-related): item number
- Type: `format_defect` | `process_defect` | `evidence_missing`
- Severity: `MINOR` | `MAJOR` | `CRITICAL`
- Description: what was found
- Owner: agent/role responsible for fix
- Due: phase gate (must close before gate)
- Status: `OPEN` | `RESOLVED` | `WAIVED`
- Waiver authority: PM (MINOR/MAJOR) | COD (CRITICAL)

NCRs are tracked by QUA and reported at each phase gate. COD CANNOT pass a gate with
open CRITICAL NCRs. PM must resolve MAJOR/MINOR before gate; waiver requires COD approval.

---

## 9. Metrics Report (Capability 5)

Collected per SQAP. Mandatory at SIL 3–4 (Table A.9 T7/T8).

**Minimum metrics set**:
- NCR count by phase, severity, type
- Gate pass/fail rates by phase
- QUA review iterations per deliverable (PASS on 1st / 2nd / 3rd submission)
- Open NCR age (days since raised)
- Deliverable first-submission PASS rate (quality trend indicator)

Report format: QUA Metrics Report — `DOC-METRICSR-[YYYY]-[NNN]`.
Produced at each phase gate; archived under CM control.

---

## 10. QUA Review Report Output

**Document ID**: `QUA-REVIEW-[YYYY]-[NNN]`  
**Template**: `[PROJECT_ROOT] deliverables/quality/QA-Review-Report-template.md`  
**Canonical path**: obtain from CM `query-location --doc QUAREPORT`

The review report records:
- Document reviewed (Document ID, version, date)
- Annex C item number
- qua_check_type applied
- Iteration number (1, 2, or 3)
- Generic check results (GF-001, GF-002, GF-003)
- Sections check results (list of missing sections, if any)
- Overall result: PASS | FAIL
- Defect list (if FAIL): defect ID, rule, location, fix suggestion
- Disposition: approved for VER/VMGR review | returned to author

---

## 11. Tool Integration

QUA uses `workspace.py wf` commands from `activities/workflow.yaml`:

```bash
# Submit deliverable for QUA review (called by PM)
python3 tools/workspace.py wf submit <DOCUMENT_ID> \
  --path <path-to-document> \
  --author-role <AUTHOR_ROLE> \
  --author-name '<Author Name>' \
  --sil <0-4>

# Log QUA review result — PASS
python3 tools/workspace.py wf review <DOCUMENT_ID> \
  --role QUA \
  --name '<QUA Name>' \
  --approve \
  --comment "Format-gate PASS: all GF-001/GF-002/GF-003 and sections checks passed"

# Log QUA review result — FAIL
python3 tools/workspace.py wf review <DOCUMENT_ID> \
  --role QUA \
  --name '<QUA Name>' \
  --reject \
  --comment "<list of format defects found>"
```

NCRs raised by QUA are written as NCR records in the QUA Review Report and reported to
PM. NCR format and escalation rules are defined in Section 8 of this skill.

Reference: `en50128-lifecycle-tool-integration` skill → workspace.py command reference.
