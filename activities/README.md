# EN 50128 Activities Directory

This directory contains the **machine-readable YAML layer** for EN 50128:2011 lifecycle orchestration. It is the authoritative source for LLM agents executing lifecycle phases, checking gate criteria, routing V&V activities, and enforcing SIL-dependent rules.

---

## What is this directory for?

The top-level markdown documents (`LIFECYCLE.md`, `WORKFLOW.md`, `ORGANIZATION.md`, `DELIVERABLES.md`, `AGENTS.md`) are the **human-readable normative references** — ISA-reviewed and approved. This directory encodes the same information in **structured YAML** so that LLM agents can consume it at runtime without parsing prose.

Each YAML file answers specific questions an agent needs to act:

| Question | File |
|----------|------|
| What phases exist and in what order? | `lifecycle.yaml` |
| Who has authority over whom, and how does V&V routing work? | `workflow.yaml` |
| Who are the roles and what independence rules apply? | `organization.yaml` |
| What deliverables are required, who writes them, who checks them? | `deliverables.yaml` |
| Which agent maps to which EN 50128 role? | `roles.yaml` |
| What exactly happens in Phase N? | `phase-N-*.yaml` |

---

## File Inventory

### Context Files (non-phase)

| File | Contents |
|------|----------|
| `SCHEMA.md` | Full YAML schema reference — field definitions, two-track model, cross-file links |
| `lifecycle.yaml` | Complete V-Model FSM: 11 phases (0–10), SIL-conditional skips, cross-cutting activities, gate commands |
| `workflow.yaml` | Authority structure (COD / PM / VMGR), per-phase execution loop, Phase 7 specialized flow, CCB change-request re-entry |
| `organization.yaml` | SIL-tiered org charts, role independence matrix, permitted and prohibited role combinations |
| `deliverables.yaml` | Full Annex C catalogue (46 items): writer, 1st Check, 2nd Check, doc ID, path, platform deviations |
| `roles.yaml` | Agent-to-role mapping, independence requirements by SIL, track assignment (A or B), skills loaded |
| `baseline-management.yaml` | Baseline lifecycle, 8 gate baselines, 7-step creation procedure, CR re-entry path; source: `tasks/BASELINE_MANAGEMENT.md` |
| `quality-process.yaml` | QUA process: per-phase activities, all 46 Annex C touchpoints, two-track gate positions, Table A.9; source: `tasks/QUALITY_PROCESS.md` |
| `safety-process.yaml` | SAF process: phase activity map, cross-cutting artifacts, Table A.8 (5 entries), EN 50126 companion techniques; source: `tasks/SAFETY_ENGINEERING.md` |

### Phase Files

Each phase file is self-contained: it defines what to do, how to coordinate agents, and what transitions to take afterward.

| File | Phase | EN 50128 Section | Annex C Items | Key Notes |
|------|-------|-----------------|---------------|-----------|
| `phase-0-initialization.yaml` | 0 — Initialization | Platform extension | — | COD-only; creates `LIFECYCLE_STATE.md`; generates system docs |
| `phase-1-planning.yaml` | 1 — Planning | §5, §6.5, §6.6 | 1–5 | SQAP, SQAVR, SCMP, SVP, SVaP; VER/VAL author exceptions in Track A |
| `phase-2-requirements.yaml` | 2 — Requirements | §7.2 | 6–8 | SRS, Overall Test Spec, Req VER Report |
| `phase-3-architecture-design.yaml` | 3 — Architecture & Design | §7.3 | 9–14 | SAS, SDS, Interfaces, Integration Test Specs, Arch VER Report |
| `phase-4-component-design.yaml` | 4 — Component Design | §7.4 | 15–17 | Component Design Spec, Component Test Spec, Design VER Report |
| `phase-5-implementation-testing.yaml` | 5 — Implementation & Testing | §7.5 | 18–20 | Source code (MISRA C), Source Code VER Report, Component Test Report |
| `phase-6-integration.yaml` | 6 — Integration | §7.6 | 21–22 | SW + SW/HW Integration Test Reports; `verification.required: false` (item 23 in Phase 7) |
| `phase-7-validation.yaml` | 7 — Validation | §7.7 | 23–27 | Integration VER Report, Overall Test Report, Validation Reports, Release Note; **only phase where VAL authors reports** |
| `phase-8-assessment.yaml` | 8 — Assessment | §6.4 | 45–46 | **Mandatory SIL 1–4; SIL 0 exempt §6.4.1.2**; `executor: asr` (independent); `verification.required: false` |
| `phase-9-deployment.yaml` | 9 — Deployment | §9.1 | 36–40 | Release & Deployment Plan, Manual, Release Notes, Records, Deployment VER Report (item 40 platform deviation) |
| `phase-10-maintenance.yaml` | 10 — Maintenance | §9.2 | 41–44 | `recurring: true`; Maintenance Plan, Change Records, Maintenance Records, Maintenance VER Report (item 44 platform deviation) |

---

## Key Concepts

### Two-Track Execution Model

Every phase (except Phase 0 and Phase 8) operates on two parallel tracks:

```
TRACK A — Development (PM orchestrates)
  dev agents: REQ · DES · IMP · INT · TST · SAF · CM · QUA
  → agents produce deliverables
  → QUA checks each deliverable
  → PM reports Track A complete to COD

TRACK B — Independent V&V (COD coordinates)
  SIL 3–4:  COD → VMGR → VER → QUA → VMGR → [VAL → QUA → VMGR] → COD gate-check
  SIL 0–2:  COD → VER  → QUA → [VAL] → COD gate-check
```

**Track assignment rule**: `activities[]` in each phase file contains ONLY Track A agents. VER, VAL, and VMGR never appear in `activities[]` — they belong exclusively in `verification:`, `validation:`, and `workflow:`.

**Phase 1 exception**: VER authors SVP (item 4) and VAL authors SVaP (item 5) — they appear in `activities[]` as document *authors* (not reviewers), with a `note:` field explaining the exception.

**Phase 8 exception**: ASR is the executor — not PM. ASR is fully independent and is not directed by PM or COD during assessment conduct.

### Three-Layer Schema (per phase file)

Each phase YAML encodes three layers:

1. **`activities[]`** — declarative: which agents produce which deliverables, in which parallel groups, with which dependencies
2. **`workflow:`** — procedural: Track A→B handoff, SIL-conditional routing, VMGR gateway rule, rework path
3. **`transitions[]`** — state machine: what COD does after gate pass / gate fail / phase re-entry

### VMGR Gateway Rule (SIL 3–4)

At SIL 3–4, COD MUST route ALL V&V through VMGR. There is no direct COD→VER or COD→VAL path. VMGR's Final V&V Decision cannot be overridden by COD or PM.

### VAL Report Authorship

VAL authors formal Validation Reports **only in Phase 7**. In all other phases, VAL acts as "2nd Check" reviewer on deliverables (Annex C checker column) but produces no report artifact.

### Platform Deviations from Annex C

Three Annex C Table C.1 phase-column assignments differ from the logical phase used by this platform. All three are documented in `DELIVERABLES.md` Notes 5–7 and must be recorded in the project SQAP:

| Item | Annex C Phase Column | Platform Assignment | Justification |
|------|---------------------|---------------------|---------------|
| 20 — Software Component Test Report | Integration | **Phase 5** (Implementation & Testing) | §7.5.4.5 normative clause; integration requires prior unit tests |
| 40 — Deployment Verification Report | Software maintenance | **Phase 9** (Deployment) | §9.1 normative clause; deployment must be verified before maintenance |
| 44 — Software Maintenance VER Report | Software assessment | **Phase 10** (Maintenance) | §9.2 normative clause; maintenance activities generate the report |

### Standard Typo

Annex C item 42 reads "Software Chang Records" in the printed standard. The correct name per §9.2.4 is **"Software Change Records"**. All files in this directory use the corrected name.

---

## Relationship to Other Files

```
/activities/        ← machine-readable YAML (this directory)
    ↑ encodes ↑
LIFECYCLE.md        ← human-readable lifecycle reference (ISA PASS v1.9)
WORKFLOW.md         ← human-readable authority & workflow reference (ISA PASS)
ORGANIZATION.md     ← human-readable organization reference (ISA PASS)
DELIVERABLES.md     ← human-readable Annex C catalogue (ISA PASS)
AGENTS.md           ← human-readable agent role reference (ISA PASS)
```

The markdown documents are the normative human reference. The YAML files are derived from them and must remain consistent. **Do not modify the ISA-passed markdown documents.** If a discrepancy is found between a YAML file and its source markdown, the markdown is authoritative.

---

## How Agents Use These Files

| Agent | Files consumed |
|-------|---------------|
| **COD** | `lifecycle.yaml`, `workflow.yaml`, all `phase-N-*.yaml` (transitions + gate_check) |
| **PM** | `phase-N-*.yaml` (activities), `deliverables.yaml`, `roles.yaml` |
| **VMGR** | `workflow.yaml` (V&V routing), `phase-N-*.yaml` (verification + validation blocks) |
| **VER** | `phase-N-*.yaml` (verification criteria), `deliverables.yaml` |
| **VAL** | `phase-7-validation.yaml` (produces reports), all phases (2nd Check role) |
| **QUA** | `deliverables.yaml` (template paths, doc IDs), `phase-N-*.yaml` (qua_required flags), `quality-process.yaml` |
| **CM** | `deliverables.yaml` (all 46 items for baseline management), `baseline-management.yaml` |
| **SAF** | `safety-process.yaml` (phase activity map, Table A.8, artifact list), `phase-N-*.yaml` (SAF activities) |
| **ASR** | `phase-8-assessment.yaml`, `deliverables.yaml` (all items for review) |

---

## Schema Reference

See `SCHEMA.md` in this directory for the complete field-level schema, including all allowed values, required vs optional fields, and annotated examples.
