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

```
USER → @pm execute-phase N
  │
  ▼
PM: orchestrates dev agents → deliverable produced
  │
  ▼
QUA template check (1-pass rule)
  ├── FAIL ──► loops back to author (PM coordinates rework)
  └── PASS
        │
        ▼
      VER verification
        ├── REJECT ──► loops back to PM (rework required)
        └── APPROVE
              │
              ▼
            VER report → QUA template check (1-pass rule)
              ├── FAIL ──► loops back to VER (re-issue report)
              └── PASS
                    │
                    ▼
                  VMGR reviews VER report
                    ├── REJECT ──► loops to VER rework
                    └── APPROVE
                          │
                          ▼
                        COD invokes VAL (independent from VMGR and PM)
                          │
                          ▼
                        VAL Validation Report
                          │
                          ▼
                        QUA template check (1-pass rule)
                          ├── FAIL ──► loops back to VAL (re-issue report)
                          └── PASS
                                │
                                ▼
                              VMGR reviews VAL report
                                ├── REJECT ──► loops to VAL rework
                                └── APPROVE ── VMGR V&V Decision (cannot be overridden)
                                      │
                                      ▼
                                    COD gate-check:
                                      ✓ VER report VMGR-approved
                                      ✓ VAL report VMGR-approved
                                      ✓ All deliverables QUA-passed
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
            QUA → VER → VMGR full approval chain
            (same loop as Diagram 1 per-phase execution)
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
