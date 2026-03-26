---
name: en50128-validation
description: EN 50128 software validation and system testing for railway C applications
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  language: C
  section: "7.7"
  sil_applicability: "0-4"
---

# EN 50128 Validation Skill

This skill provides authoritative guidance for the **Software Validator (VAL)** role per
EN 50128:2011 §7.7, §5.3.7, §5.1.2.8, §6.3.4.2, Table B.7.

---

## 1. Role Definition

### Author Mode (Phase 1 and Phase 7)

VAL **authors** two categories of document:
- **Item 5 — Software Validation Plan (SVaP)**: authored in Phase 1 under §6.3.4.2; mandatory
  at all SIL levels (normative override); 1st-check by VER; no 2nd-check.
- **Phase 7 outputs** — Software Validation Report (item 25), Tools Validation Report (item 26,
  if applicable), Release Note (item 27 per §7.7.4.12). These are produced only in Phase 7.

### 2nd-Check Mode (Phases 1–6, 9–10)

In all other phases VAL reviews deliverables as **2nd Check only** — no VAL report produced.
See the 2nd-Check Table (§4 below) for the complete per-phase list.

### Independence by SIL

| SIL | Independence | Reporting |
|-----|-------------|-----------|
| SIL 0-1 | Not required | May report to PM |
| SIL 2 | HR | Recommended separation from development |
| SIL 3-4 | **Mandatory** | SHALL NOT report to PM (§5.1.2.10f); reports to Safety Authority or Customer |

VAL's release decision (agree/disagree per §5.1.2.8) is FINAL and cannot be overridden by PM,
COD, or VMGR.

---

## 2. Complete VAL Output Table

VAL produces formal documents in Phase 1 and Phase 7 only.

| Phase | Item | Label | Abbrev | Condition |
|-------|------|-------|--------|-----------|
| 1 | 5 | Software Validation Plan | SVaP | All SIL levels (M by §6.3.4.2) |
| 7 | 25 | Software Validation Report | VALRPT | All SIL levels |
| 7 | 26 | Tools Validation Report | TOOLSVALRPT | If tool qualification required |
| 7 | 27 | Release Note | RELEASENOTE | Mandatory per §7.7.4.12 |

**Note on item 27**: Authorship unspecified in Annex C footnote 'a'. Assign in SQAP. Distinct
from "Release Notes" (plural, item 38, Phase 9). Confirm against printed standard.

---

## 3. Complete 2nd-Check Table

| Phase | Items VAL 2nd-Checks | Note |
|-------|---------------------|------|
| 1 | 1, 2, 3, 4, 5 | Items 1–5; all planning deliverables |
| 2 | 6, 7, 8 | SRS, OTSS, REQVER |
| 3 | 9, 10, 11, 12, 13, 14 | Architecture, design, interfaces, integration test specs, ARCHDESIGNVER |
| 4 | 15, 16 | Component design spec, component test spec; item 17 (VER report) not 2nd-checked |
| 5 | 18, 20 | Source code, unit test report; item 19 (VER report) not 2nd-checked |
| 6 | 21, 22 | Integration test spec, integration test report; item 23 (VER report) not 2nd-checked |
| 7 | — | VAL produces reports (items 25–26); does not 2nd-check in Phase 7 |
| 8 | — | Phase 8 is ASR-driven; VAL has no touchpoint |
| 9 | 36, 37, 38, 39 | Deployment plan, manual, release notes, records |
| 10 | 41, 42, 43 | Maintenance records, change records, maintenance plan |

**Rule**: VAL does NOT 2nd-check VER reports (items 2, 8, 14, 17, 19, 23, 40, 44, †) except
via the Phase 7 Track B Step B2 flow where VMGR coordinates both VER and VAL reviews together.

---

## 4. Core Algorithm

### Phase 1 — Author SVaP

```
1. Read .workspace; resolve canonical path via CM query-location --doc svap
2. Draft SVaP (item 5) per §6.3.4.2–6.3.4.5:
   - Scope, SIL level, validation environment description
   - Validation methods selected per SIL tier (Table A.7)
   - Acceptance criteria for all requirements
   - Planned operational scenarios (normal, degraded, emergency, recovery)
   - Performance test plan (MANDATORY SIL 3-4)
   - Tools and independence declaration
3. Submit SVaP to QUA for format-gate (Track A)
4. Submit QUA-passed SVaP to VER for 1st-check
5. After VER 1st-check PASS: submit to VMGR (SIL 3-4) or COD (SIL 0-2) for acceptance
```

### Phase 7 — Perform Validation

```
1. Receive tasking from COD (SIL 0-2) or VMGR (SIL 3-4) after VER item 23 is approved
2. Read LIFECYCLE_STATE.md; confirm Phase 7 Track B Step B2 authorisation
3. Execute validation activities per SVaP:
   a. Functional/black-box testing — verify all SRS requirements (M SIL 3-4)
   b. Performance testing — timing, throughput, WCET, resource usage (M SIL 3-4)
   c. Operational scenario testing — normal, degraded, emergency, recovery
   d. Acceptance testing — customer acceptance criteria
   e. End-to-end traceability check — SRS → unit tests → integration → system tests
4. Invoke CM query-location --doc valrpt for canonical path
5. Author Software Validation Report (item 25) per §7.7.4.6–7.7.4.11
6. Author Tools Validation Report (item 26) if tool qualification evidence required
7. Author Release Note (item 27) per §7.7.4.12
8. Submit items 25–26 to QUA for format-gate (1-Pass Rule)
9. After QUA PASS: submit to VER for item † (Validation Verification Report)
10. After VER item † PASS + QUA format check: submit package to VMGR for FINAL V&V decision
11. Issue release decision: AGREE or DISAGREE (§5.1.2.8) — this decision is FINAL
```

### 2nd-Check (all other phases)

```
1. Receive deliverable from COD/VMGR after VER has issued its report
2. Review deliverable against SRS, design, and SIL requirements for technical correctness
3. Confirm all VER-identified defects are resolved before 2nd-checking
4. Record 2nd-check outcome: PASS or FAIL with defect list
5. Return outcome to VMGR (SIL 3-4) or COD (SIL 0-2)
```

---

## 5. Phase 7 Track B Flow

```
Track A (TST)               Track B
─────────────────           ─────────────────────────────────────────
TST authors item 24         Step B1: VER reviews item 24
(Overall SW Test Report) →  VER authors item 23 (SW Integration VER Report)
                            ↓ QUA format-gate → VMGR review
                            Step B2: VMGR assigns VAL
                            VAL executes validation (items 25–26–27)
                            ↓ QUA format-gate (1-Pass Rule)
                            ↓ VER authors item † (SW Validation VER Report)
                            ↓ QUA format-gate on item †
                            VMGR reviews items 23 + 25(+26) + † together
                            VMGR issues FINAL V&V DECISION to COD
                            VAL issues release decision (AGREE/DISAGREE)
```

**Key rules**:
- VAL does NOT receive tasking from PM in Phase 7 at SIL 3-4 (§5.1.2.10f)
- VMGR coordinates but does not override VAL's release decision
- Item 27 (Release Note) may be authored by VAL or PM per SQAP assignment

---

## 6. Release Decision Authority

Per EN 50128 §5.1.2.8, VAL gives agreement/disagreement for software release.

**Release criteria (SIL 3-4)**:
- All SRS requirements validated with pass result
- Performance requirements met (measured evidence)
- All operational scenarios executed and passed
- Zero unresolved critical/high-severity defects
- End-to-end traceability complete (SRS → validation tests)
- VER item † approved by VMGR
- Safety case approved (SAF)
- Configuration baseline established (CM)

**AGREE** → Forward to VMGR for FINAL V&V decision; software may proceed to deployment.  
**DISAGREE** → Block release; return defect list; PM/COD cannot override.

---

## 7. SVaP Authorship Notes (Item 5, §6.3.4.2)

- VAL authors the SVaP; VER performs 1st-check (cannot be overridden)
- No 2nd-check on SVaP per deliverables.yaml (`second_check: null`)
- Platform deviation: SVaP placed in Phase 1 (Planning) rather than Annex C "Software
  requirements" phase; justified by §6.3.4.3 and §5.3.2.4; document in SQAP

---

## 8. Validation Techniques (SIL-tiered, Table A.7)

| No. | Technique | SIL 0 | SIL 1-2 | SIL 3-4 |
|-----|-----------|-------|---------|---------|
| 1 | Performance Testing (Table A.18) | - | HR | **M** |
| 2 | Functional and Black-box Testing (Table A.14) | HR | HR | **M** |
| 3 | Modelling (Table A.17) | - | R | R |
| 4 | Regression Testing (D.46) | HR | HR | **M** |
| 5 | User Interface Testing | HR | HR | HR |
| 6 | Boundary Value Analysis (D.7) | R | HR | **M** |
| 7 | Equivalence Classes (D.20) | R | HR | HR |

**Legend**: **M** = Mandatory, **HR** = Highly Recommended, **R** = Recommended, **-** = No recommendation

---

## 9. Report Templates Directory

Use the Markdown templates in `deliverables/` when authoring VAL deliverables.
The `deliverables/` YAML files are machine-readable requirement specs (SIL criteria,
evidence requirements, verification criteria) — they complement but do not replace
the Markdown templates.

| Annex C Item | Markdown Template | Requirements Spec (YAML) |
|-------------|-------------------|--------------------------|
| 5 — Software Validation Plan | `deliverables/planning/Software-Validation-Plan-template.md` | `deliverables/planning/Software-Validation-Plan.yaml` |
| 25 — Software Validation Report | `deliverables/validation/Software-Validation-Report.md` | `deliverables/validation/Software-Validation-Report.yaml` |
| 26 — Tools Validation Report | `deliverables/validation/Tools-Validation-Report.md` | `deliverables/validation/Tools-Validation-Report.yaml` |
| 27 — Release Note | *(assign in SQAP; no platform template — §7.7.4.12)* | `deliverables/deployment/Release-Notes.yaml` |

---

## 10. Tool Integration

### workspace.py patterns (VAL)

```bash
# Submit SVaP to workflow after authoring
python3 tools/workflow_manager.py submit <DOC-SVaP-ID> --phase 1 --role VAL

# Submit Validation Report to QUA
python3 tools/workflow_manager.py submit <DOC-VALRPT-ID> --phase 7 --role VAL

# Record VAL approval/disagreement
python3 tools/workflow_manager.py review <DOC-VALRPT-ID> --role VAL \
    --name "<VAL name>" --approve --comment "Validation complete. AGREE for release."

# Check traceability completeness before release
python3 tools/workspace.py trace validate --phase validation --sil <level>

# Generate requirements coverage report
python3 tools/workspace.py trace report \
    --from requirements --to tests --format markdown \
    --output evidence/validation/requirements_coverage.md
```

---

## 11. Normative References

- EN 50128:2011 §5.1.2.8 — Release agreement authority
- EN 50128:2011 §5.1.2.10f — VAL shall not report to PM (SIL 3-4)
- EN 50128:2011 §5.3.7 / Table B.7 — Validator role and competence
- EN 50128:2011 §6.3.4.2–6.3.4.14 — Validation process requirements
- EN 50128:2011 §7.7.4.1–7.7.4.12 — Overall software testing and validation
- EN 50128:2011 Table A.7 — Overall software testing/validation techniques
- EN 50128:2011 Table A.14 — Functional and black-box testing
- EN 50128:2011 Table A.18 — Performance testing
- EN 50128:2011 Annex C Table C.1 — Deliverable matrix (items 5, 24–27)
