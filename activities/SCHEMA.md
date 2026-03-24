# EN 50128 Activities Directory — Schema Reference

This directory contains all machine-readable YAML files for EN 50128 lifecycle orchestration.
They are the authoritative machine-executable layer for LLM agents. The top-level markdown
documents (`LIFECYCLE.md`, `WORKFLOW.md`, `ORGANIZATION.md`, `DELIVERABLES.md`, `AGENTS.md`)
remain the human-readable normative references; these YAML files encode the same information
in structured, LLM-consumable form.

---

## File Index

| File | Purpose | Source |
|------|---------|--------|
| `lifecycle.yaml` | Phase sequence, SIL-conditional skips, cross-cutting activities, FSM transitions | `LIFECYCLE.md` |
| `workflow.yaml` | Authority structure, per-phase execution loop, Phase 7 flow, CCB re-entry | `WORKFLOW.md` |
| `organization.yaml` | Role definitions, independence rules by SIL tier, combination rules | `ORGANIZATION.md` |
| `deliverables.yaml` | Full Annex C catalogue (46 items), writer/checker, doc IDs, phase mapping | `DELIVERABLES.md` |
| `traceability.yaml` | Normative traceability rules (T1–T15), document matrix (traces_from/to), system inputs, V-Model correspondence, role independence, CCB impact, platform deviations D1–D9 | `TRACEABILITY.md` |
| `roles.yaml` | Agent-to-role mapping, SIL independence requirements, skills | `AGENTS.md` |
| `phase-0-initialization.yaml` | Phase 0: COD initialization activities and transitions | `LIFECYCLE.md §2` |
| `phase-1-planning.yaml` | Phase 1: Planning activities, deliverables, workflow, transitions | `LIFECYCLE.md §3` |
| `phase-2-requirements.yaml` | Phase 2: Requirements activities, deliverables, workflow, transitions | `LIFECYCLE.md §4` |
| `phase-3-architecture-design.yaml` | Phase 3: Architecture & Design activities, deliverables, workflow, transitions | `LIFECYCLE.md §5` |
| `phase-4-component-design.yaml` | Phase 4: Component Design activities, deliverables, workflow, transitions | `LIFECYCLE.md §6` |
| `phase-5-implementation-testing.yaml` | Phase 5: Implementation & Testing activities, deliverables, workflow, transitions | `LIFECYCLE.md §7` |
| `phase-6-integration.yaml` | Phase 6: Integration activities, deliverables, workflow, transitions | `LIFECYCLE.md §8` |
| `phase-7-validation.yaml` | Phase 7: Validation activities, deliverables, workflow, transitions | `LIFECYCLE.md §9` |
| `phase-8-assessment.yaml` | Phase 8: Assessment (mandatory SIL 1–4; SIL 0 exempt §6.4.1.2) | `LIFECYCLE.md §11` |
| `phase-9-deployment.yaml` | Phase 9: Deployment activities, deliverables, workflow, transitions | `LIFECYCLE.md §12` |
| `phase-10-maintenance.yaml` | Phase 10: Maintenance activities, deliverables, workflow, transitions | `LIFECYCLE.md §13` |
| `baseline-management.yaml` | Machine-readable baseline lifecycle: 8 gate baselines (Diagram 1), 7-step creation procedure (Diagram 2), CR re-entry path, role boundaries, EN 50128 terminology corrections | `tasks/BASELINE_MANAGEMENT.md (ISA PASS)` |

---

## Design Principles

These files are designed for **LLM agent runtime consumption**. Each file is self-contained:
it answers both "what to do" (declarative activity data) and "what happens next" (workflow
coordination logic and state transitions) in a single load.

**Three-layer schema** used in every phase file:

1. **`activities[]`** — declarative: what Track A agents produce (deliverables, criteria, agents,
   SIL conditions, parallel groups, dependencies)
2. **`workflow`** — procedural: intra-phase coordination logic (Track A→B handoff, SIL-conditional
   routing, QUA gate points, VMGR gateway rule)
3. **`transitions[]`** — state machine: inter-phase gate pass/fail/re-entry rules with guards

**Two-track execution model** (from `WORKFLOW.md`):

```
TRACK A — Development (PM orchestrates)
  dev agents (REQ · DES · IMP · INT · TST · SAF · CM) → QUA check → PM reports to COD

TRACK B — Independent V&V (COD coordinates)
  SIL 3–4:  COD → VMGR → VER → QUA → VMGR → [VAL → QUA → VMGR] → COD gate-check
  SIL 0–2:  COD → VER → QUA → [VAL] → COD gate-check
```

**Key constraint**: `activities[]` contains ONLY Track A agents. VER, VAL, VMGR MUST NOT
appear in `activities[]` — they belong in `verification:`, `validation:`, and `workflow:`.

---

## Phase File Schema

```yaml
phase:
  id: string            # Unique phase ID (e.g., "requirements")
  number: integer       # Phase number (0–10)
  name: string          # Human-readable phase name
  en50128_section: string  # Normative clause (e.g., "§7.2")
  description: string   # Why this phase exists; what it produces; normative basis.
                        # Written for LLM consumption — concise but complete.

  # ── TRACK A: Agent activities (PM-orchestrated, dev agents only) ──────────
  # VER, VAL, VMGR MUST NOT appear here.
  activities:
    - agent: string           # One of: req, saf, des, imp, int, tst, cm, qua, pm
      task_description: string
      owner: string
      deliverables:
        - path: string        # Relative path from project root
          doc_id: string      # DOC-<TYPE>-YYYY-NNN
          doc_type: string    # Exact EN 50128 document name
          annex_c_item: integer   # Annex C item number (null if none)
          qua_required: boolean
      dependencies: []        # 0-based indices of activities that must complete first
      parallel_group: integer # Activities with same group number may run in parallel

  # ── Completion criteria (checked by COD at gate) ─────────────────────────
  completion_criteria:
    all_deliverables_qua_accepted: boolean
    traceability_complete: boolean
    coverage_requirements: {}   # domain-specific coverage metrics (omit if N/A)
    custom_checks: []           # list of plain-language gate criteria

  # ── TRACK B: Verification (COD-orchestrated via VMGR at SIL 3–4) ─────────
  verification:
    required: boolean
    verifier: "ver"
    produces:             # Verification report deliverable(s)
      - doc_type: string
        annex_c_item: integer
        path: string
    criteria: []          # What VER checks

  # ── TRACK B: Validation (COD-orchestrated via VMGR at SIL 3–4) ──────────
  validation:
    required_sil: []      # SIL levels requiring VAL report authorship
    validator: "val"
    independence_required_sil: [3, 4]
    produces:             # Validation report deliverable(s)
      - doc_type: string
        annex_c_item: integer
        path: string
    criteria: []

  # ── Workflow: intra-phase coordination logic ─────────────────────────────
  # Describes the Track A → Track B handoff and SIL-conditional routing.
  # An LLM agent reads this block to know HOW to coordinate agents.
  workflow:
    track_a:
      description: string         # What PM does in Track A
      completion_signal: string   # What PM reports to COD when Track A is done
    track_b:
      sil_34:
        description: string       # COD→VMGR→VER→[VAL] sequence
        vmgr_gateway: true        # COD MUST route through VMGR at SIL 3–4
      sil_02:
        description: string       # COD→VER→[VAL] direct sequence
    rework_path: string           # What happens if Track B rejects a deliverable

  # ── Transitions: inter-phase state machine ───────────────────────────────
  # An LLM agent reads this block to know WHAT STATE to move to after this phase.
  transitions:
    - event: string               # "gate_pass" | "gate_fail" | "skip"
      guard: string               # Boolean condition (e.g., "sil >= 1")
      target: string              # Next phase id, or "re_entry" for same phase
      action: string              # What COD/PM does on this transition

  # ── Gate check configuration ─────────────────────────────────────────────
  gate_check:
    command: string               # e.g., "@cod gate-check planning"
    mandatory_sil: []             # SIL levels where gate is mandatory
    blocking_sil: []              # SIL levels where gate BLOCKS transition
    criteria: []                  # Gate pass criteria (summary)
```

---

## Cross-file References

Phase files reference other files by key:
- `deliverables.yaml` → by `annex_c_item` number
- `roles.yaml` → by `agent` short code
- `workflow.yaml` → phase files implement the patterns defined there
- `organization.yaml` → independence rules apply to `verification.required` and `validation.independence_required_sil`

---

## Normative Basis

- EN 50128:2011 Section 5.3 (Lifecycle)
- EN 50128:2011 Section 5.1.2.10 (Independence wall, SIL 3–4)
- EN 50128:2011 Annex C Table C.1 (Document Control Summary)
- `LIFECYCLE.md` v1.9 (ISA PASS)
- `WORKFLOW.md` (ISA PASS)
- `ORGANIZATION.md` (ISA PASS)
- `DELIVERABLES.md` (ISA PASS)
- `AGENTS.md` (ISA PASS)
