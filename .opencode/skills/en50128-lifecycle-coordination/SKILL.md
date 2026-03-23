---
name: en50128-lifecycle-coordination
description: Project management and coordination for EN 50128 railway software development
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  role: lifecycle-coordinator
---

# EN 50128 Lifecycle Coordination Skill

**Primary user**: COD agent. Load this skill before any COD operation.

---

## Authoritative Sources

Read these before any operation. They are the single source of truth — do not invent rules.

| File | Answers |
|------|---------|
| `LIFECYCLE.md` | V-Model phase definitions, phase entry/exit criteria, phase sequence |
| `WORKFLOW.md` | Authority structure (Diagrams 1–4), two-track execution loop, CCB re-entry flow |
| `ORGANIZATION.md` | SIL-tiered org charts, role combination rules, independence matrix |
| `DELIVERABLES.md` | Complete Annex C Table C.1 — all deliverables per phase, author roles |
| `AGENTS.md` | Role definitions, agent index, independence matrix |
| `TRACEABILITY.md` | Traceability rules T1–T15, gate enforcement requirements |
| `activities/lifecycle.yaml` | Machine-readable phase FSM, SIL requirements per phase |
| `activities/workflow.yaml` | Machine-readable authority structure, Track A/B, CCB re-entry |
| `activities/phase-N-*.yaml` | Per-phase deliverables, gate criteria, approval chain data |

---

## Phase Gate Structure

Each gate has six criteria types:

1. **Deliverables** — required documents present and document-controlled (see `DELIVERABLES.md` per phase; machine-readable: `activities/phase-N-*.yaml §gate_check`)
2. **Quality** — QUA template compliance on every deliverable and report (1-pass rule)
3. **Verification** — VER report exists, VMGR-approved (SIL 3–4); VER report exists (SIL 0–2)
4. **Validation** — VAL report exists, VMGR-approved (SIL 3–4 all phases; SIL 0–2 Phases 5, 7 only)
5. **Traceability** — RTM completeness for the phase (rules T1–T15 in `TRACEABILITY.md`)
6. **Independence** — VER/VAL/ASR independence constraints met per `ORGANIZATION.md`

---

## SIL-Dependent Gate Enforcement

| SIL | Mode | Behavior |
|-----|------|----------|
| 0–1 | Advisory | Warn on unmet criteria; allow user override with acknowledgment |
| 2 | Semi-strict | Require written justification for any gate bypass |
| 3–4 | Strict Gatekeeper | BLOCK all transitions until every mandatory criterion is satisfied; no override |

Full SIL-tiered criteria (coverage thresholds, static analysis requirements, technique mandates)
are in `activities/lifecycle.yaml §sil_requirements` and `LIFECYCLE.md`.

---

## Per-Phase Execution Loop

See `WORKFLOW.md` Diagram 2 (phases 1–6, 8–9) and Diagram 3 (Phase 7) for the canonical flow.
Summary for reference:

**Track A (PM orchestrates — development)**: agents produce deliverables → QUA template check →
PM reports Track A complete to COD.

**Track B (COD coordinates — independent V&V)**:
- SIL 3–4: COD → VMGR → VER (verify) → QUA (VER report) → VMGR (approve VER report) →
  COD → VAL (validate, via VMGR routing) → QUA (VAL report) → VMGR (approve VAL report) →
  VMGR ⇢ COD (V&V outcome — cannot be overridden)
- SIL 0–2: COD → VER directly (no VMGR); VAL only for Phases 5 and 7

COD does NOT invoke VER or VAL directly at SIL 3–4. VMGR is the sole gateway.

---

## CCB / Change Re-entry

See `WORKFLOW.md` Diagram 4 and `activities/workflow.yaml §ccb_re_entry` for the full flow.
Summary: PM leads CCB; COD determines re-entry scope (earliest affected phase); CM branches baseline;
all affected phase gates are re-run in forward phase order.

---

## Agent Handoff Protocol

When authorizing a phase transition, COD outputs:

```
Phase transition authorized: <FromPhase> → <ToPhase>

Handoff from:
  - <Role>: <artifact complete>
  ...

Handoff to:
  - <Role>: begin <activity>
  ...

Cross-cutting agents continue:
  - VER, QUA, CM (throughout)
```

---

## LIFECYCLE_STATE.md Schema (minimum required fields)

COD creates and maintains `examples/<project>/LIFECYCLE_STATE.md`. Required fields:

```markdown
# Project Lifecycle State

## Project Information
- **Project Name**: <name>
- **SIL Level**: <0–4>
- **COD Mode**: <Advisory | Semi-strict | Strict Gatekeeper>
- **Created**: <YYYY-MM-DD>
- **Last Updated**: <YYYY-MM-DD>

## Current Status
- **Current Phase**: <phase name and number>
- **Completion**: <N>%

## Phase History
| Phase | Status | Started | Completed | Gate Passed | Notes |
|-------|--------|---------|-----------|-------------|-------|

## Deliverable Status
<!-- per-phase checklist, updated each phase -->

## Gate Check History
| Date | Phase | Result | Notes |

## Traceability Status
<!-- forward/backward coverage percentages per phase -->

## Change Log
| Date | Phase | CR# | Description | Impact |
```

Additional sections (Requirement Approval History, Agents Active, Metrics, Next Steps)
are added by COD as the project progresses.

---

## Tool Integration

For `workspace.py trace` and `workspace.py wf` command reference, Python automation scripts,
and EN 50128 coverage statistics, load skill `en50128-lifecycle-tool-integration`.
