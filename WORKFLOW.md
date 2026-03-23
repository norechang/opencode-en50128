# EN 50128 Agent Interaction Workflows

This document is the **fundamental reference for all agents** on how COD, PM, VMGR, and development agents interact during the EN 50128 software lifecycle, and how change requests re-enter already-closed phases.

All agents MUST consult this document when determining authority, sequencing, or re-entry scope.

Detail workflows (machine-friendly format) are generated separately. This document covers high-level flow diagrams for the essential lifecycle activities.

---

## Document Index

| # | Diagram | Purpose |
|---|---------|---------|
| [1](#diagram-1) | Authority Structure | Organizational hierarchy by SIL tier |
| [2](#diagram-2) | Per-Phase Execution Loop | Two-track development and V&V flow |
| [3](#diagram-3) | Phase 7 Validation Flow | Validation-phase-specific V&V flow (VAL reports produced here only) |
| [4](#diagram-4) | CCB Change Request Re-entry | Trigger → CCB → scope → re-entry loop |

---

## Diagram 1 — Authority Structure {#diagram-1}

### SIL 3–4: Strict Independence

```
SAFETY AUTHORITY / CUSTOMER
│
├──────────────────────────────────────────────────────────────────┐
│                                                                  │
▼                                                                  ▼
COD  (Lifecycle Coordinator)         ASR  (Assessor)   ★MANDATORY INDEP
│  Phase gate authority              Independent from project
│  Lifecycle state                   §5.1.2.4–5.1.2.7, §6.4.1.1
│  Overall compliance                Reviews ALL artifacts
│  Cannot override VMGR              Appointed by SA / supplier
│                                    No reporting to COD or PM
│   ◄── V&V outcome ──────────────► VMGR  (Independent V&V Authority)
│        (from VMGR)                 ★MANDATORY INDEP [platform ext.]
│                                    Basis: §5.1.2.10(e–f)
│                                    Manages VER team
│                                    Reviews VER reports
│                                    Reviews VAL reports (Phase 7)
│                                    Final V&V approval
│                                    Cannot be overridden by COD/PM
│                                    Does NOT report to COD or PM
│    ══════════ INDEPENDENCE WALL (§5.1.2.10(g–j)) ═══════════════
│ authorizes phases
▼
PM  (Project Manager)
│  Team coordination · CCB leadership · Resource management
│  Reports to COD for lifecycle decisions
│  NO authority over VMGR, VER, VAL, or ASR
│
└──► orchestrates: REQ · DES · IMP · INT · TST · SAF · QUA · CM
```

> **Note**: For SIL 0–2 there is no VMGR. At SIL 1–2 VER and VAL may report to PM
> (§5.1.2.11(e)); COD interacts with VER and VAL directly. At SIL 0 the V&V stream
> may be further consolidated (§5.1.2.12). See `ORGANIZATION.md` for full SIL-tiered
> org charts.

---

## Diagram 2 — Per-Phase Execution Loop {#diagram-2}

Applies to all phases **except Phase 7** (Validation). Phase 7 has its own flow — see Diagram 3.

Two sequential tracks per phase. PM owns Track A; COD coordinates Track B.
Track B begins only after Track A is complete and PM reports QUA PASS to COD.

At SIL 3–4 COD routes all V&V work through VMGR. COD does **not** interact
with VER or VAL directly — VMGR is the sole gateway.

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 TRACK A — Development  (PM orchestrates)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

USER → @pm execute-phase N
  │
  ▼
PM orchestrates development agents
(REQ · DES · IMP · INT · TST · SAF · CM as applicable to phase)
  │  phase deliverable(s) produced
  ▼
QUA template check
  ├── FAIL ──► PM coordinates rework with author → re-check
  └── PASS
        │
        ▼
      PM reports phase deliverables complete to COD

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 TRACK B — Independent Verification  (COD coordinates)
 PM has NO authority over any agent in this track
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

COD receives phase-complete notification from PM
  │
  ▼
  ┌── SIL 3–4 ─────────────────────────────────────────────────┐
  │                                                             │
  │  COD → VMGR: request verification of phase deliverables    │
  │    │                                                        │
  │    ▼                                                        │
  │  VMGR assigns VER; VER verifies phase deliverables          │
  │    ├── REJECT deliverable ──► VMGR notifies COD             │
  │    │    COD notifies PM; PM coordinates rework              │
  │    │    → rework re-enters Track A from QUA check           │
  │    └── APPROVE                                              │
  │          │                                                  │
  │          ▼                                                  │
  │        VER produces Verification Report                     │
  │          │                                                  │
  │          ▼                                                  │
  │        QUA template check on VER report                     │
  │          ├── FAIL ──► VER re-issues (max 1 resubmission)    │
  │          └── PASS                                           │
  │                │                                            │
  │                ▼                                            │
  │              VMGR reviews VER report                        │
  │                ├── REJECT ──► VER reworks; QUA re-checks    │
  │                └── APPROVE                                  │
  │                      │                                      │
  │                      ▼                                      │
  │                    VMGR reports V&V outcome to COD          │
  │                                                             │
  └─────────────────────────────────────────────────────────────┘
  ┌── SIL 0–2 ─────────────────────────────────────────────────┐
  │                                                             │
  │  COD invokes VER directly                                   │
  │    │  VER verifies phase deliverables → Verification Report │
  │    ▼                                                        │
  │  QUA template check on VER report                           │
  │    ├── FAIL ──► VER re-issues                               │
  │    └── PASS ──► COD receives VER report directly            │
  │                                                             │
  └─────────────────────────────────────────────────────────────┘
  │
  ▼
COD gate-check:
  ✓ All phase deliverables QUA-passed
  ✓ VER Verification Report QUA-passed and VMGR-approved (SIL 3–4)
    or VER report received (SIL 0–2)
  ✓ Traceability complete
  ✓ Zero critical open defects
  │
  ├── PASS ──► COD authorizes next phase → @pm execute-phase N+1
  └── FAIL ──► COD BLOCKS; PM coordinates rework; COD re-runs gate
```

> **VAL in phases 1–6 and 9–10**: VAL reviews deliverables as **2nd Check** (see
> DELIVERABLES.md column "2nd Check"). VAL does **not** produce a Validation Report
> in these phases. VAL Validation Reports are produced only in Phase 7 (§7.7).

---

## Diagram 3 — Phase 7: Validation Flow {#diagram-3}

Phase 7 (§7.7 "Overall Software Testing / Final Validation") is the only phase where
VAL authors formal Validation Reports (items 25 and 26 per DELIVERABLES.md).

The VER Verification Report for this phase (item 23, Software Integration Verification
Report) is also produced here per Annex C.

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 TRACK A — Validation Activities  (PM orchestrates)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

USER → @pm execute-phase 7
  │
  ▼
PM orchestrates TST (overall software testing)
  │  Overall Software Test Report (item 24) produced
  ▼
QUA template check on test report
  ├── FAIL ──► PM coordinates rework → re-check
  └── PASS
        │
        ▼
      PM reports Track A complete to COD

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 TRACK B — Independent V&V  (COD coordinates)
 PM has NO authority over any agent in this track
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

COD receives Track A complete from PM
  │
  ▼
  ┌── SIL 3–4 ─────────────────────────────────────────────────────┐
  │                                                                 │
  │  COD → VMGR: request V&V for Phase 7                           │
  │    │                                                            │
  │    ▼                                                            │
  │  [Step B1 — Verification]                                       │
  │  VMGR assigns VER; VER produces Software Integration            │
  │  Verification Report (item 23)                                  │
  │    │                                                            │
  │    ▼                                                            │
  │  QUA template check on VER report                               │
  │    ├── FAIL ──► VER re-issues                                   │
  │    └── PASS                                                     │
  │          │                                                      │
  │          ▼                                                      │
  │        VMGR reviews VER report                                  │
  │          ├── REJECT ──► VER reworks; QUA re-checks              │
  │          └── APPROVE                                            │
  │                │                                                │
  │                ▼                                                │
  │  [Step B2 — Validation]                                         │
  │  VMGR assigns VAL; VAL performs final validation                │
  │    │  • Reviews all phase evidence                              │
  │    │  • Produces Software Validation Report (item 25)           │
  │    │  • Produces Tools Validation Report (item 26, if applicable)│
  │    │  • Produces Release Note (§7.7.4.12)†             │
  │    │                                                            │
  │    ├── REJECT (evidence insufficient) ──► VMGR notifies COD    │
  │    │    COD notifies PM; PM coordinates rework                  │
  │    │    → rework re-enters Track A; full B1–B2 loop repeats     │
  │    └── APPROVE                                                  │
  │          │                                                      │
  │          ▼                                                      │
  │        QUA template check on VAL reports                        │
  │          ├── FAIL ──► VAL re-issues; QUA re-checks              │
  │          └── PASS                                               │
  │                │                                                │
  │                ▼                                                │
  │              VMGR reviews VAL reports                           │
  │                ├── REJECT ──► VAL reworks; QUA re-checks        │
  │                └── APPROVE — VMGR Final V&V Decision            │
  │                      │       (cannot be overridden)             │
  │                      ▼                                          │
  │                    VMGR reports V&V outcome to COD              │
  │                                                                 │
  └─────────────────────────────────────────────────────────────────┘
  ┌── SIL 0–2 ─────────────────────────────────────────────────────┐
  │                                                                 │
  │  COD invokes VER directly → VER report (item 23)                │
  │  COD invokes VAL directly → VAL reports (items 25–27)           │
  │  QUA checks all reports                                         │
  │  COD receives reports directly                                  │
  │                                                                 │
  └─────────────────────────────────────────────────────────────────┘
  │
  ▼
COD gate-check (Phase 7):
  ✓ Overall Software Test Report (item 24) QUA-passed
  ✓ VER Integration Verification Report (item 23) QUA-passed and VMGR-approved (SIL 3–4)
  ✓ VAL Validation Report (item 25) QUA-passed and VMGR-approved (SIL 3–4)
  ✓ Tools Validation Report (item 26, if applicable) QUA-passed
  ✓ Release Note (item 27) present
  ✓ SVaP validation criteria satisfied — validation activities complete per §6.3.4.4–6.3.4.6
  ✓ Zero critical open defects
  │
  ├── PASS ──► COD authorizes Phase 8 (Assessment) or Phase 9 (Deployment)
  └── FAIL ──► COD BLOCKS; coordinates rework; re-runs gate
```

> **†** Release Note authorship is unresolved in Annex C Table C.1 — Annex C item 27 status uncertain against printed standard; §7.7.4.12 imposes the normative "shall produce" obligation regardless. See `DELIVERABLES.md` Note 3 for details.

---

## Diagram 4 — CCB Change Request: Re-entry of Already-Closed Phases {#diagram-4}

There is **no informal rework path** for closed phases at SIL 3–4. Every backward
movement MUST go through CCB and re-run the full gate chain. At SIL 0–1 COD warns
rather than blocks, but CCB remains the correct mechanism.

```
Trigger: defect found / enhancement needed in a CLOSED phase
  │
  ▼
PM raises Change Request (CR)
  │
  ▼
CCB meeting  (PM chairs; REQ · SAF · DES · IMP · TST · VER · CM participate)
  ├── impact analysis: determines earliest affected phase
  └── vote: APPROVED / REJECTED
        │
        ├── REJECTED ──► CR closed; no action
        │
        └── APPROVED
              │
              ▼
            CM creates baseline branch
              │
              ▼
            COD marks affected phases "re-entry-required" in LIFECYCLE_STATE.md
              │
              ┌───────────────────────────────────────────────┐
              │  CR scope             Earliest re-entry       │
              │  ─────────────────    ────────────────────    │
              │  Requirements         Phase 2 onward          │
              │  Architecture/Design  Phase 3 onward          │
              │  Component design     Phase 4 onward          │
              │  Code / unit tests    Phase 5 onward          │
              │  Integration          Phase 6 onward          │
              └───────────────────────────────────────────────┘
              │
              ▼
            For each affected phase (forward order):
            PM re-executes phase → full Track A + Track B loop
            (Diagrams 2 or 3 as applicable)
              │
              ▼
            All affected COD gates re-pass
              │
              ▼
            CM creates updated baseline (post-CR)
              │
              ▼
            Lifecycle resumes from current (highest) phase
```

---

## Phase Transition Authority Summary

| Role | Can start phase? | Can block phase? | Can override? |
|------|-----------------|-----------------|---------------|
| COD  | YES (authorizes) | YES (gate check) | NOT VMGR decisions |
| PM   | NO (requests)    | NO               | NOT COD / VMGR decisions |
| VMGR | NO               | YES (V&V reject) | Cannot be overridden |

## Key Independence Constraints (SIL 3–4)

| Constraint | Reference |
|---|---|
| PM has NO authority over VAL (§5.1.2.10(f)), VER (§5.1.2.10(e); platform routes VER through VMGR), ASR (§5.1.2.10(m)), or VMGR (platform rule, basis §5.1.2.10(e–f)) | §5.1.2.10(e–f), (f), (m) |
| COD routes ALL V&V work through VMGR — no direct COD→VER or COD→VAL | §5.1.2.10(e–f) |
| COD CANNOT override VMGR V&V decisions | Platform rule; basis §5.1.2.10(e–f) |
| VMGR does NOT report to COD or PM | §5.1.2.10(f); platform |
| VER reports to VMGR | §5.1.2.10(e) |
| VAL shall NOT report to PM | §5.1.2.10(f) |
| VAL operates independently; VMGR reviews VAL Validation Reports (Phase 7 only) and provides Final V&V approval — VAL does not report to VMGR but VMGR coordinates VAL work in Phase 7 (platform rule, basis §5.1.2.10(f–j)) | §5.1.2.10(f–j); platform |
| ASR is independent from all project roles including COD | §5.1.2.5–5.1.2.6, §6.4.1.1 |
