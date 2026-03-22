# EN 50128 Agent Interaction Workflows

This document is the **fundamental reference for all agents** on how COD, PM, VMGR, and development agents interact during the EN 50128 software lifecycle, and how change requests re-enter already-closed phases.

All agents MUST consult this document when determining authority, sequencing, or re-entry scope.

---

## Document Index

| # | Diagram | Purpose |
|---|---------|---------|
| [1](#diagram-1) | COD / PM / VMGR Interaction — EN 50128 Lifecycle | Authority structure, per-phase execution loop, phase transition authority table, independence constraints |
| [2](#diagram-2) | CCB Change Request — Re-entry of Already-Closed Phases | Trigger → CCB → scope determination → per-phase re-entry loop → CM baseline |

---

## Diagram 1 — COD / PM / VMGR Interaction: EN 50128 Lifecycle {#diagram-1}

### Authority Structure

```
Safety Authority / Customer
├── COD (Lifecycle Coordinator) ◄──coordinate──► VMGR (Independent V&V Authority)
│     • Phase gates                (no report)     • Manages VER team
│     • Lifecycle state                            • Reviews VER reports
│     • Compliance                                 • Reviews VAL reports
│     • Cannot override VMGR  ◄── V&V approve/     • Final V&V decision
│                                  reject            (cannot be overridden)
│ authorizes phases                               manages
▼                                                    ▼
PM (Project Manager)                            VER (Verifier)
│  • Team coordination                          • Verification reports
│  • Resource mgmt                              • Static analysis
│  • Stakeholder comms                          • Coverage checks
│  • CCB leadership                             • Reports to VMGR
│  • Reports to COD for lifecycle
└──► orchestrates: REQ · DES · IMP · INT · TST · QUA · CM · SAF
```

### Per-Phase Execution Loop (SIL 3-4)

Two sequential tracks per phase. PM owns Track A; COD owns Track B.
Track B begins only after Track A completes (PM reports QUA PASS to COD).

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 TRACK A — Development  (PM orchestrates)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

USER → @pm execute-phase N
  │
  ▼
PM orchestrates dev agents (REQ · DES · IMP · INT · TST · SAF · CM)
  │  deliverable(s) produced
  ▼
QUA template check (1-pass rule)
  ├── FAIL ──► PM coordinates rework with author
  │             └── author re-submits → QUA re-checks (max 1 resubmission)
  └── PASS
        │
        ▼
      PM reports phase deliverables complete to COD
        │
        ▼
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 TRACK B — Independent V&V  (COD orchestrates)
 PM has NO authority over any agent in this track
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

COD receives phase-complete report from PM
  │
  ▼
COD → VMGR: assign VER to verify phase deliverables  [SIL 3-4 only]
  │          (SIL 0-2: COD invokes VER directly)
  ▼
VER performs verification of phase deliverables
  ├── REJECT deliverable ──► COD notifies PM; PM coordinates rework
  │                           → rework re-enters Track A from QUA check
  └── APPROVE → VER produces Verification Report
                  │
                  ▼
                QUA template check on VER report (1-pass rule)
                  ├── FAIL ──► VER re-issues report (max 1 resubmission)
                  └── PASS
                        │
                        ▼
                      VMGR reviews VER report  [SIL 3-4 only]
                        ├── REJECT ──► VER reworks report; QUA re-checks
                        └── APPROVE
                              │
                              ▼
                            COD invokes VAL (independent from VMGR and PM)
                              │
                              ▼
                            VAL performs validation; produces Validation Report
                              ├── REJECT deliverable ──► COD notifies PM; PM coordinates rework
                              │                           → rework re-enters Track A from QUA check
                              └── APPROVE → VAL Validation Report produced
                                              │
                                              ▼
                                            QUA template check on VAL report (1-pass rule)
                                              ├── FAIL ──► VAL re-issues report (max 1 resubmission)
                                              └── PASS
                                                    │
                                                    ▼
                                                  VMGR reviews VAL report  [SIL 3-4 only]
                                                    ├── REJECT ──► VAL reworks report; QUA re-checks
                                                    └── APPROVE ── VMGR V&V Decision (cannot be overridden)
                                                          │
                                                          ▼
                                                        COD gate-check:
                                                          ✓ All deliverables QUA-passed
                                                          ✓ VER report QUA-passed + VMGR-approved
                                                          ✓ VAL report QUA-passed + VMGR-approved
                                                          ✓ Traceability complete
                                                          ✓ Zero critical defects
                                                          │
                                                          ├── PASS ──► COD authorizes next phase
                                                          │             → @pm execute-phase N+1
                                                          └── FAIL ──► COD BLOCKS
                                                                        PM coordinates rework
                                                                        COD re-runs gate-check
```

### Phase Transition Authority Summary

```
Role  │ Can start phase? │ Can block phase? │ Can override?
──────┼──────────────────┼──────────────────┼──────────────────────────
COD   │ YES (authorizes) │ YES (gatekeeper) │ NOT VMGR decisions
PM    │ NO (requests)    │ NO               │ NOT COD / VMGR decisions
VMGR  │ NO               │ YES (V&V reject) │ Cannot be overridden
```

### Key Independence Constraints

```
PM   ──── NO AUTHORITY OVER ──────► VMGR / VAL / ASR
COD  ──── CANNOT OVERRIDE ─────────► VMGR decisions
VMGR ──── DOES NOT REPORT TO ──────► COD or PM
VMGR ──── REPORTS TO ──────────────► Safety Authority
VER  ──── REPORTS TO ──────────────► VMGR  (§5.1.2.10e)
VAL  ──── INDEPENDENT FROM ────────► VMGR and PM  (§5.1.2.10f/j)
```

---

## Diagram 2 — CCB Change Request: Re-entry of Already-Closed Phases {#diagram-2}

### Overview

There is **no informal rework path** for closed phases at SIL 3-4. Every backward movement MUST go through CCB and re-run the full gate chain. At SIL 0-1 COD warns rather than blocks, but CCB remains the correct mechanism.

### Flow

```
Trigger: defect found / enhancement needed in a CLOSED phase
  │
  ▼
PM raises Change Request (CR)
  │
  ▼
CCB meeting (PM chairs)
  ├── impact analysis: REQ, SAF, DES, IMP, TST, VER, CM
  ├── determines earliest affected phase
  └── vote: APPROVED / REJECTED
        │
        ├── REJECTED ──► CR closed; no action
        │
        └── APPROVED
              │
              ▼
            CM creates baseline branch; agents implement changes
              │
              ▼
            PM → COD: "CR implemented; re-entry required"
              │
              ▼
            COD determines scope (earliest affected phase):

              ┌──────────────────────────────────────────────┐
              │  CR type               Earliest re-entry     │
              │  ─────────────────     ────────────────────  │
              │  Requirements          Phase 2 onward        │
              │  Design (SAS/SDS)      Phase 3 onward        │
              │  Component design      Phase 4 onward        │
              │  Code / unit tests     Phase 5 onward        │
              │  Integration           Phase 6 onward        │
              └──────────────────────────────────────────────┘
              │
              ▼
            COD marks affected phases "re-entry-required"
            in LIFECYCLE_STATE.md
              │
              ▼
            For each affected phase (forward order):
              │
              ▼
            PM re-executes phase activities
              │
              ▼
            QUA (Track A) → COD → VMGR → VER → QUA → VAL → QUA → VMGR → COD gate-check
            (same two-track loop as Diagram 1 per-phase execution)
              │
              ▼
            COD gate-check → PASS → mark re-entry complete
              │
              ▼
            All affected gates re-pass
              │
              ▼
            CM creates updated baseline (post-CR)
              │
              ▼
            Lifecycle resumes from current (highest) phase
```
