# QUA Review Criteria

This directory contains the format-check rules QUA applies to every Annex C deliverable.

**Authority**: `tasks/QUALITY_PROCESS.md` (ISA PASS), `activities/quality-process.yaml`

---

## Architecture

QUA format-gate checks consist of two layers applied together:

```
Layer 1: generic-format-checker.yaml        ← universal; applies to every document
Layer 2: sections/<doc-key>-sections.yaml   ← document-specific required section list
```

### Layer 1 — Generic Format Checker

**File**: `generic-format-checker.yaml`

Three rules applied to every deliverable regardless of type:

| Rule | What it checks |
|------|---------------|
| GF-001 | Document ID format: `DOC-<ABBREV>-<YYYY>-<NNN>` |
| GF-002 | Document Control table: all five required fields present and non-empty |
| GF-003 | Approvals table: correct columns and minimum roles (Author, Reviewer QUA, Approver PM) |

The checker is **parameterized** — supply `doc_abbreviation` and `sil_level` at runtime.

### Layer 2 — Document-Specific Sections Supplement

**Directory**: `sections/`

One YAML file per document type. Lists the mandatory section headings for that document
type, derived from the normative EN 50128:2011 output clauses.

Rule GF-004 (Required Sections) is defined by this layer.

---

## Sections Index

| Annex C item | Doc key | Sections file | qua_check_type |
|---|---|---|---|
| 1 | SQAP | `sections/sqap-sections.yaml` | template_compliance |
| 2 | SQAVR | `sections/sqavr-sections.yaml` | template_compliance_one_pass |
| 3 | SCMP | `sections/scmp-sections.yaml` | template_compliance |
| 4 | SVP | `sections/svp-sections.yaml` | template_compliance_one_pass |
| 5 | SVaP | `sections/svap-sections.yaml` | template_compliance_one_pass |
| 6 | SRS | `sections/srs-sections.yaml` | template_compliance |
| 7 | OTSTSPEC | `sections/otstspec-sections.yaml` | template_compliance |
| 8 | REQVER | `sections/reqver-sections.yaml` | template_compliance_one_pass |
| 9 | SAS | `sections/sas-sections.yaml` | template_compliance |
| 10 | SDS | `sections/sds-sections.yaml` | template_compliance |
| 11 | INTERFACES | `sections/interfaces-sections.yaml` | template_compliance |
| 12 | INTTESTSPEC | `sections/inttestspec-sections.yaml` | template_compliance |
| 13 | HWINTTESTSPEC | `sections/hwinttestspec-sections.yaml` | template_compliance |
| 14 | ARCHDESIGNVER | `sections/archdesignver-sections.yaml` | template_compliance_one_pass |
| 15 | COMPDESIGN | `sections/compdesign-sections.yaml` | template_compliance |
| 16 | COMPTESTSPEC | `sections/comptestspec-sections.yaml` | template_compliance |
| 17 | COMPDESIGNVER | `sections/compdesignver-sections.yaml` | template_compliance_one_pass |
| 18 | SOURCECODE | `sections/sourcecode-sections.yaml` | template_compliance |
| 19 | SOURCECODEVER | `sections/sourcecodever-sections.yaml` | template_compliance_one_pass |
| 20 | COMPTESTRPT | `sections/comptestrpt-sections.yaml` | template_compliance |
| 21 | INTTESTRPT | `sections/inttestrpt-sections.yaml` | template_compliance |
| 22 | HWINTTESTRPT | `sections/hwinttestrpt-sections.yaml` | template_compliance |
| 23 | INTVER | `sections/intver-sections.yaml` | template_compliance_one_pass |
| 24 | OVERALLTESTRPT | `sections/overalltestrpt-sections.yaml` | template_compliance |
| 25 | VALRPT | `sections/valrpt-sections.yaml` | template_compliance_one_pass |
| 26 | TOOLSVALRPT | `sections/toolsvalrpt-sections.yaml` | template_compliance_one_pass |
| 27 | RELEASENOTE | `sections/releasenote-sections.yaml` | template_compliance |
| 36 | DEPLOYPLAN | `sections/deployplan-sections.yaml` | template_compliance |
| 37 | DEPLOYMAN | `sections/deployman-sections.yaml` | template_compliance |
| 38 | RELEASENOTES | `sections/releasenotes-sections.yaml` | template_compliance |
| 39 | DEPLOYREC | `sections/deployrec-sections.yaml` | template_compliance |
| 40 | DEPLOYVER | `sections/deployver-sections.yaml` | template_compliance_one_pass |
| 41 | MAINTPLAN | `sections/maintplan-sections.yaml` | template_compliance |
| 42 | CHANGEREC | `sections/changerec-sections.yaml` | template_compliance |
| 43 | MAINTREC | `sections/maintrec-sections.yaml` | template_compliance |
| 44 | MAINTVER | `sections/maintver-sections.yaml` | template_compliance_one_pass |

**Phase 8 items (45, 46)**: NO QUA touchpoint. ASR is fully independent.
QUA MUST NOT check items 45 or 46.

---

## qua_check_type Values

| Value | Iteration limit | Applies to |
|-------|----------------|-----------|
| `template_compliance` | 3; then PM escalates | Development deliverables (Track A) |
| `template_compliance_one_pass` | 1 resubmission; then NCR MAJOR + PM escalation | VER and VAL reports (Track B format check) |
| `none` | — | Phase 8 ASR documents |

Full iteration-limit logic: `en50128-quality` SKILL.md §3 (Format-Gate Algorithm).

---

## What QUA Checks — and What It Does Not

**QUA checks (FORMAT only)**:
- Document ID present and correctly formatted
- Document Control table with all required fields
- Approvals table with minimum required roles
- Required section headings present

**QUA does NOT check**:
- Technical correctness of any content
- MISRA C compliance (VER, §7.5.4.10)
- Traceability link completeness (VER, T1–T15 per `TRACEABILITY.md`)
- Test coverage figures (TST/VER)
- Static analysis results (VER)
- Safety argument adequacy (SAF/VER)

---

## Severity Levels

| Severity | Meaning |
|----------|---------|
| `error` | Must be fixed before QUA accepts the document |
| `warning` | Should be fixed; does not block acceptance |

All three generic rules (GF-001, GF-002, GF-003) are `error` severity.
Section checks (GF-004) are `error` severity for mandatory sections.
