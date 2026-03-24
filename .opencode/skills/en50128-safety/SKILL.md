# EN 50128 Safety Engineering Skill

**Role**: Safety Engineer (SAF)  
**Standard**: EN 50128:2011 §6.3, §7.1, Table A.8  
**Authority source**: `tasks/SAFETY_ENGINEERING.md` (ISA PASS)  
**Machine-readable data**: `activities/safety-process.yaml`

---

## 1. SAF Role Definition

SAF is the **safety analysis authority** for the EN 50128 software lifecycle. SAF has
**no primary Annex C deliverable** — its outputs are cross-cutting artifacts (Hazard Log,
FMEA/FTA Reports) that support Annex C items authored by REQ, DES, and VAL.

**SAF independence**: EN 50128 §5.1.2 contains no independence clause for SAF. SAF may
collaborate with REQ, DES, and PM at all SIL levels (see `ORGANIZATION.md`).

**SAF phase footprint**:
- Phase 2 — PRIMARY: hazard analysis, SEEA, derives REQ-SAFE-xxx
- Phase 3 — SECONDARY: FMEA, FTA on architecture; updates Hazard Log
- Phases 4–6 — MONITORING only: no primary artifact; escalate to PM/CCB
- Phase 7 — CONFIRMATION: hazard closure check; unblocks Validation Report
- Phase 8 — EVIDENCE PROVISION only: ASR is independent; SAF ≠ ASR
- Phases 9–10 — CCB-triggered re-entry only (safety-impacting changes)

**Annex C items where SAF contributes** (not primary author):

| Item | Document | SAF contribution |
|------|----------|-----------------|
| 6 | Software Requirements Specification | Derives REQ-SAFE-xxx; §7.2.4.13 |
| 9 | Software Architecture Specification | Reviews safety architecture; FMEA/FTA findings feed SAS |
| 25 | Software Validation Report | Hazard closure confirmation; §7.7.4.8(b) |

Full phase activity map: `tasks/SAFETY_ENGINEERING.md` Section 1.

---

## 2. Authoritative Sources

| What you need | Where to find it |
|---------------|-----------------|
| Phase footprint, activities, artifact ownership | `tasks/SAFETY_ENGINEERING.md` (ISA PASS) |
| Machine-readable phase/artifact/table data | `activities/safety-process.yaml` |
| Annex C Table C.1 — full deliverable matrix | `DELIVERABLES.md` |
| Traceability rules T1–T15; hazard traceability chain | `TRACEABILITY.md` |
| Two-track model, authority, CCB re-entry | `WORKFLOW.md` |
| Independence matrix (SAF = "No" at all SIL levels) | `ORGANIZATION.md` |
| EN 50128 §6.3, §7.1, §7.2.4.13, §7.7.4.8, Table A.8 | `std/EN50128-2011.md` |
| System-level FMEA/FTA/HAZOP sources | `std/EN 50126-1-2017.md` §6.3, D.27, D.30, D.32 |
| CCF = HR SIL 3–4; Tolerable Hazard Rates | `std/EN 50126-2-2017.md` §10 Table 8, Table F.2 item 11 |
| Step-by-step analysis procedures | `workflows/safety-analysis-procedures.md` |
| Hazard Log template | `templates/Hazard-Log-template.md` |
| FMEA Report template | `templates/FMEA-template.md` |
| FTA Report template | `templates/FTA-template.md` |
| Canonical document paths | CM `query-location` |

---

## 3. Capability 1 — Hazard Analysis (Phase 2)

**Trigger**: PM assigns SAF parallel with REQ at Phase 2 start.  
**Inputs**: S4 (System Safety Requirements Specification), S1 (System Requirements Spec).  
**Output**: Hazard Log (initial baseline), REQ-SAFE-xxx requirements for inclusion in SRS.

```
Algorithm:

1. Invoke CM query-location → obtain canonical path for Hazard Log
2. Read S4: list all system-level hazards and their Tolerable Hazard Rates (THR)
3. For each hazard:
   a. Determine if software-relevant (software can contribute to or prevent the hazard)
   b. Assign HAZ-xxx ID
   c. Record severity (1–10), frequency (1–10), risk level = severity × frequency
   d. Derive SIL assignment from THR using EN 50126-2 Table 8
   e. State mitigation strategy (defensive programming, watchdog, safe state, redundancy)
   f. State residual risk level after mitigation
   g. Status = OPEN
4. Derive REQ-SAFE-xxx safety requirements:
   a. One or more REQ-SAFE-xxx per HAZ-xxx entry
   b. Pass list to REQ for inclusion in SRS §7.2.4.13
   c. Record HAZ-xxx → REQ-SAFE-xxx link in Hazard Log
5. Apply SEEA if SIL 3–4 (Table A.8 entry 5 — HR SIL 3–4):
   a. For each software-relevant hazard: identify fault modes
      (NULL pointer, overflow, state machine stuck-at, uninitialized variable)
   b. Record fault → effect → safeguard in Hazard Log SEEA section
6. Write Hazard Log to canonical path using templates/Hazard-Log-template.md
7. Report to PM: Hazard Log created; REQ-SAFE-xxx list provided to REQ
```

**HAZ-xxx ID format**: `HAZ-[NNN]` (e.g. HAZ-001, HAZ-002)  
**REQ-SAFE-xxx ID format**: `REQ-SAFE-[NNN]`  
**Hazard Log field definitions**: see Section 7 below.

---

## 4. Capability 2 — FMEA / FTA (Phase 3)

**Trigger**: PM assigns SAF after SDS draft available (parallel with DES review).  
**Inputs**: SRS (with REQ-SAFE-xxx), SAS, SDS (draft), Hazard Log (Phase 2 baseline).  
**Output**: FMEA Report, FTA Report, Updated Hazard Log.

```
Algorithm — FMEA (bottom-up):

1. Invoke CM query-location → obtain canonical paths for FMEA Report and Hazard Log
2. Read SDS: identify all software modules and component boundaries
3. For each module:
   a. List failure modes (e.g. output stuck-at, computation error, timeout, deadlock)
   b. For each failure mode:
      - Effect on subsystem / system
      - Severity (1–10): 1–3 minor, 4–6 moderate, 7–8 critical, 9–10 catastrophic
      - Occurrence (1–10)
      - Detection (1–10, inverse: 1 = always detected, 10 = undetectable)
      - RPN = Severity × Occurrence × Detection
      - Recommended action if RPN ≥ threshold (project-defined, typically ≥ 100)
4. Write FMEA Report using templates/FMEA-template.md
5. Update Hazard Log: link failure modes to HAZ-xxx entries; update mitigations

Algorithm — FTA (top-down, for hazards with severity ≥ 8):

1. Invoke CM query-location → obtain canonical path for FTA Report
2. For each severity ≥ 8 hazard in Hazard Log:
   a. Define top event (the hazard condition)
   b. Decompose using AND/OR gates to immediate causes
   c. Continue to basic events (software faults, hardware faults, operator errors)
   d. Calculate minimal cut sets
   e. If SIL 3–4: include CCF Analysis section
      - CCF is HR (Highly Recommended) per EN 50126-2:2017 Table F.2 item 11
      - NOT Mandatory; include if project SQAP selects it
      - Typical CCF causes: common design faults, shared HW platform, EMI, common power
   f. Calculate top-event probability if quantitative data available
3. Write FTA Report using templates/FTA-template.md
4. Update Hazard Log: add FTA findings; update residual risk and mitigation entries
```

**Report field definitions**: see Sections 8 and 9 below.

---

## 5. Capability 3 — Software Error Effect Analysis (SEEA) (Phase 2–3)

**Normative basis**: EN 50128:2011 Table A.8 entry 5 — SEEA is a **software-specific**
technique (HR SIL 3–4). It analyses the effect of each software component fault on the
software system as a whole.

**Scope** (software fault modes to analyse):

| Fault Mode | How to analyse |
|-----------|---------------|
| NULL pointer dereference | Identify all pointer dereferences; confirm null check guards |
| Integer overflow | Identify all arithmetic; confirm range checks or saturating arithmetic |
| State machine stuck-at | Identify all state variables; confirm timeout / watchdog exits |
| Uninitialized variable | Confirm all variables have explicit initialization before use |
| Array out-of-bounds | Identify all array accesses; confirm bounds checks |
| Division by zero | Identify all divisions; confirm non-zero denominator check |

```
Algorithm:

1. Obtain module list from SDS (Phase 3) or preliminary design (Phase 2)
2. For each module:
   a. List fault modes from the table above
   b. For each fault mode:
      - Effect on this module: degraded / incorrect / no output
      - Propagation: how does this fault affect other modules?
      - Effect on system: safe state / unsafe / no effect
      - Safeguard: MISRA C rule, defensive check, watchdog, safe state handler
3. Record in Hazard Log SEEA section; link to HAZ-xxx where applicable
4. Flag unmitigated unsafe faults to PM for escalation
```

**When required**: SIL 3–4 (HR). Document in SQAP that SEEA is selected or waived with
justification per §4.7.

---

## 6. Capability 4 — Hazard Closure Confirmation (Phase 7)

**Trigger**: PM assigns SAF to support VAL independence check (Phase 7).  
**Inputs**: Software Validation Report (draft), Hazard Log (current baseline), Overall SW
Test Report (item 24).  
**Output**: Safety confirmation memo to PM; Final Hazard Log baseline.

```
Algorithm:

1. Invoke CM query-location → obtain canonical path for Hazard Log (current baseline)
2. For each HAZ-xxx entry in Hazard Log:
   a. Confirm status is CLOSED or ACCEPTED-RESIDUAL
      - CLOSED: all REQ-SAFE-xxx linked to this hazard have PASS test results in item 24
      - ACCEPTED-RESIDUAL: residual risk formally accepted by Safety Authority / PM; signed
   b. If status is still OPEN: record in hazard-closure-gap list
3. For each REQ-SAFE-xxx in SRS:
   a. Confirm at least one test case in item 24 covers this requirement with PASS result
   b. If no test coverage: record in coverage-gap list
4. Compile result:
   - If hazard-closure-gap list is empty AND coverage-gap list is empty:
     → CONFIRMATION PASS: report to PM; VAL may sign Validation Report (§7.7.4.8(b))
   - If any gap exists:
     → CONFIRMATION FAIL: report gaps to PM; Validation Report sign-off is BLOCKED
5. Write Final Hazard Log baseline; submit to CM for archiving
6. Report to PM: PASS or FAIL with gap list
```

**Phase 7 clause**: §7.7.4.8(b) — "the validation shall demonstrate that all safety
requirements are met." Any unclosed hazard = validation not demonstrable = blocks sign-off.

---

## 7. Hazard Log Field Definitions

| Field | Description | Format |
|-------|-------------|--------|
| `HAZ-ID` | Unique hazard identifier | `HAZ-[NNN]` |
| `Description` | Hazard event description | Free text |
| `Source` | Which S4 entry or analysis identified it | S4-ref or "FMEA" / "FTA" |
| `Severity` | Consequence severity (1–10) | Integer 1–10 |
| `Frequency` | Likelihood of occurrence (1–10) | Integer 1–10 |
| `Risk Level` | Severity × Frequency | Integer 1–100 |
| `SIL Assignment` | Derived from THR per EN 50126-2 Table 8 | SIL 0 / 1 / 2 / 3 / 4 |
| `Mitigation` | Software safeguard strategy | Free text |
| `Residual Risk` | Risk level after mitigation | Integer 1–100 |
| `REQ-SAFE-xxx` | Linked safety requirements | List of REQ-SAFE-xxx IDs |
| `Status` | Current closure status | `OPEN` / `CLOSED` / `ACCEPTED-RESIDUAL` |
| `Evidence` | Test report reference (Phase 7) | Item 24 test case ID |
| `Acceptance Authority` | For ACCEPTED-RESIDUAL: who accepted | Role + name |

---

## 8. FMEA Report Field Definitions

| Field | Description |
|-------|-------------|
| Module | Software module or component name (from SDS) |
| Failure Mode | How the module can fail |
| Effect (local) | Effect on the module's output or behaviour |
| Effect (system) | Effect on the overall software system |
| Severity (S) | 1–10 |
| Occurrence (O) | 1–10 |
| Detection (D) | 1–10 (1 = always detected) |
| RPN | S × O × D |
| HAZ-xxx links | Which Hazard Log entries this failure mode contributes to |
| Mitigation Action | Defensive programming, watchdog, safe state, MISRA rule |
| Status | Open / Mitigated / Accepted |

---

## 9. FTA Report Field Definitions

| Field | Description |
|-------|-------------|
| Top Event | The hazard condition being analysed (HAZ-xxx reference) |
| Gate structure | AND / OR logic decomposition to basic events |
| Basic Events | Software faults, hardware faults, operator errors |
| Minimal Cut Sets | Smallest combinations of basic events causing top event |
| Cut Set Probability | If quantitative data available |
| CCF Section | Common Cause Failure analysis (HR SIL 3–4; NOT Mandatory) |
| CCF Causes | Common design fault, shared HW, EMI, common power supply |

---

## 10. EN 50128 Table A.8 — Software Analysis Techniques (Corrected)

Source: EN 50128:2011 §6.3, Table A.8. **Exactly 5 entries.** FMEA, FTA, HAZOP, and CCF
are **NOT** in Table A.8 (they are EN 50126 system-level techniques applied via §7.1).

| # | Technique | Ref | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 |
|---|-----------|-----|-------|-------|-------|-------|-------|
| 1 | Static Software Analysis | D.13, D.37, Table A.19 | R | HR | HR | HR | HR |
| 2 | Dynamic Software Analysis | Table A.13, A.14 | — | R | R | HR | HR |
| 3 | Cause Consequence Diagrams | D.6 | R | R | R | R | R |
| 4 | Event Tree Analysis | D.22 | — | R | R | R | R |
| 5 | Software Error Effect Analysis (SEEA) | D.25 | — | R | R | HR | HR |

Legend: M = Mandatory, HR = Highly Recommended, R = Recommended, — = No recommendation

**Table A.8 does NOT contain**: FMEA, FTA, HAZOP, CCF, Markov Analysis.
These are system-level techniques. See companion table in `tasks/SAFETY_ENGINEERING.md`
Section 4 and `activities/safety-process.yaml` `companion_techniques[]`.

---

## 11. Artifact CM Control Rules

All SAF artifacts are **cross-cutting** — outside Annex C Table C.1 but subject to §6.6
CM control.

| Artifact | Created | Updated | Baseline Owner | Reviewed By |
|----------|---------|---------|----------------|-------------|
| Hazard Log | Phase 2 | Phases 3, 7 | CM (§6.6) | VER (1st), VAL (2nd) |
| FMEA Report | Phase 3 | Phase 3 | CM (§6.6) | VER (1st), VAL (2nd) |
| FTA Report | Phase 3 | Phase 3 | CM (§6.6) | VER (1st), VAL (2nd) |

**Document ID format**: `DOC-[ABBREV]-[YYYY]-[NNN]`  
- Hazard Log: `DOC-HAZLOG-[YYYY]-[NNN]`  
- FMEA Report: `DOC-FMEA-[YYYY]-[NNN]`  
- FTA Report: `DOC-FTA-[YYYY]-[NNN]`

**Before writing any artifact**: invoke CM `query-location` to obtain the canonical path.
Never hard-code file paths.

---

## 12. Tool Integration

SAF uses `workspace.py` commands for artifact registration and status updates:

```bash
# Register a new cross-cutting artifact with CM
python3 workspace.py cm register --id DOC-HAZLOG-2026-001 --type HAZLOG \
  --path <canonical-path> --phase 2

# Update Hazard Log baseline after Phase 3 update
python3 workspace.py cm baseline --id DOC-HAZLOG-2026-001 --phase 3 \
  --label "Phase3-FMEA-update"

# Query canonical path for an artifact
python3 workspace.py cm query-location --doc HAZLOG

# Update hazard status (bulk update after Phase 7 closure check)
python3 workspace.py wf update-safety --hazlog <path> --phase 7
```

Reference: `en50128-lifecycle-tool-integration` skill → workspace.py command reference.

---

*Grounded in: `tasks/SAFETY_ENGINEERING.md` (ISA PASS), `activities/safety-process.yaml`,
`WORKFLOW.md`, `DELIVERABLES.md`, `TRACEABILITY.md`, `ORGANIZATION.md`,
`std/EN50128-2011.md` §6.3 Table A.8, §7.1, §7.2.4.13, §7.7.4.8,
`std/EN 50126-1-2017.md` §6.3, `std/EN 50126-2-2017.md` §10 Table 8, Table F.2.*
