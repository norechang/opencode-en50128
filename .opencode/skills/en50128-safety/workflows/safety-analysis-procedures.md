# Safety Analysis Procedures

**Role**: Safety Engineer (SAF)  
**Standard**: EN 50128:2011 §6.3, §7.1, Table A.8  
**Authority source**: `tasks/SAFETY_ENGINEERING.md` (ISA PASS)  
**Data source**: `activities/safety-process.yaml`

> This file contains a quick-reference summary of the step-by-step algorithms
> for each SAF capability. Full algorithms with field definitions and normative
> citations are in `SKILL.md`. Templates are in `templates/`.

---

## Hazard Analysis (Phase 2)

```
Input:  S4 (System Safety Requirements Spec), S1 (System Requirements Spec)
Output: Hazard Log (initial), REQ-SAFE-xxx list for REQ

Steps:
  1. CM query-location → Hazard Log canonical path
  2. Parse S4: enumerate all hazards relevant to software
  3. Per hazard: assign HAZ-xxx; score severity (1–10) × frequency (1–10)
  4. Derive SIL from THR using EN 50126-2:2017 Table 8
  5. State mitigation strategy; compute residual risk
  6. Derive REQ-SAFE-xxx; record HAZ-xxx → REQ-SAFE-xxx links
  7. Run SEEA (HR SIL 3–4; Table A.8 entry 5) — see SEEA section below
  8. Write Hazard Log → templates/Hazard-Log-template.md
  9. Report REQ-SAFE-xxx list to REQ for inclusion in SRS §7.2.4.13
```

---

## FMEA (Phase 3 — bottom-up)

```
Input:  SRS + REQ-SAFE-xxx, SAS, SDS (draft), Hazard Log (Phase 2 baseline)
Output: FMEA Report, Updated Hazard Log

Steps:
  1. CM query-location → FMEA Report canonical path
  2. Read SDS: list all modules and component boundaries
  3. Per module: list failure modes (stuck-at, computation error, timeout, deadlock)
  4. Per failure mode: score S × O × D; compute RPN
  5. Flag RPN ≥ project threshold (default 100) for recommended action
  6. Link failure modes to HAZ-xxx entries in Hazard Log
  7. Write FMEA Report → templates/FMEA-template.md
  8. Update Hazard Log with new failure modes and mitigations
```

---

## FTA (Phase 3 — top-down, hazards with severity ≥ 8)

```
Input:  Hazard Log (current), SDS, FMEA Report
Output: FTA Report, Updated Hazard Log

Steps:
  1. CM query-location → FTA Report canonical path
  2. Filter Hazard Log: select HAZ-xxx entries with severity ≥ 8
  3. Per selected hazard:
     a. Define top event
     b. Decompose with AND/OR gates to basic events
     c. Compute minimal cut sets
     d. If SIL 3–4 AND project SQAP selects CCF:
        → Add CCF Analysis section (HR — not Mandatory)
        → EN 50126-2:2017 Table F.2 item 11
     e. Compute top-event probability if quantitative data available
  4. Write FTA Report → templates/FTA-template.md
  5. Update Hazard Log: FTA findings, residual risk, cut set mitigations
```

---

## SEEA (Phases 2–3, HR SIL 3–4)

```
Technique: Table A.8 entry 5 — Software Error Effect Analysis
           Software-specific; analyses effects of software component faults
           on the software system. Distinct from system-level FMEA (EN 50126).

Fault modes to analyse:
  - NULL pointer dereference
  - Integer overflow / underflow
  - State machine stuck-at
  - Uninitialized variable
  - Array out-of-bounds
  - Division by zero

Per fault mode:
  - Effect on module, effect on system
  - Safeguard: MISRA C rule, bounds check, watchdog, safe state handler
  - If no safeguard: flag to PM for escalation

Record: in Hazard Log SEEA section; link to HAZ-xxx where applicable.
When required: HR at SIL 3–4. Document selection or waiver in SQAP per §4.7.
```

---

## Hazard Closure Confirmation (Phase 7)

```
Input:  Hazard Log (current baseline), Validation Report (draft), Overall SW Test Report
Output: PASS or FAIL memo to PM; Final Hazard Log baseline

Steps:
  1. CM query-location → Hazard Log canonical path (current baseline)
  2. Per HAZ-xxx entry:
     - CLOSED: all linked REQ-SAFE-xxx have PASS test results in Overall SW Test Report
     - ACCEPTED-RESIDUAL: signed acceptance on file from Safety Authority / PM
     - OPEN: add to hazard-closure-gap list
  3. Per REQ-SAFE-xxx in SRS:
     - Confirm at least one test case with PASS result exists in item 24
     - If missing: add to coverage-gap list
  4. Compile result:
     - Both lists empty → CONFIRMATION PASS → VAL may sign Validation Report §7.7.4.8(b)
     - Any gap → CONFIRMATION FAIL → Validation Report sign-off BLOCKED
  5. Write Final Hazard Log baseline; submit to CM for archiving
  6. Report to PM with PASS / FAIL and gap list
```

---

## Key Normative Facts (Quick Reference)

| Fact | Normative basis |
|------|----------------|
| Table A.8 has exactly 5 entries | EN 50128:2011 §6.3 |
| FMEA/FTA/HAZOP/CCF NOT in Table A.8 | EN 50128:2011 §6.3 (not listed) |
| CCF is HR SIL 3–4 — not Mandatory | EN 50126-2:2017 Table F.2 item 11 |
| No Safety Case in EN 50128 | EN 50128:2011 Annex C (no such item) |
| SAF has no independence requirement | EN 50128:2011 §5.1.2 (no clause) |
| Release authority = Validator | EN 50128:2011 §6.3.4.16 |
| ASR fitness assessment | EN 50128:2011 §6.4.4.8 |
| VER independence clause | EN 50128:2011 §5.1.2.10i |
| Hazard closure blocks Validation Report | EN 50128:2011 §7.7.4.8(b) |
