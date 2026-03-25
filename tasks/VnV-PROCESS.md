# EN 50128 V&V Process

This document describes the Verification and Validation (V&V) process for the EN 50128 platform. It covers the V&V lifecycle mapping, deliverables flow, role interactions, and the VMGR platform extension.

**Primary sources** (all agents MUST read these before acting on V&V matters):

| Document | Purpose |
|---|---|
| `WORKFLOW.md` | Authority structure, two-track execution loop, Phase 7 flow, CCB re-entry |
| `ORGANIZATION.md` | SIL-tiered org charts, independence matrix, role combination rules |
| `DELIVERABLES.md` | All 46 Annex C deliverables — Written By / 1st Check / 2nd Check assignments |
| `std/EN50128-2011.md` | Normative standard — §5.1.2, §6.2, §6.3, §6.4, §7.7 |

---

## Document Index

| # | Section | Purpose |
|---|---------|---------|
| [1](#diagram-1) | V&V in the Lifecycle | Which VER/VAL activities attach to which phases |
| [2](#diagram-2) | Deliverable Review Chain | Who writes, who checks 1st (VER), who checks 2nd (VAL) |
| [3](#diagram-3) | Role Interaction Model | COD ↔ VMGR ↔ VER/VAL interaction and independence wall |
| [4](#diagram-4) | VMGR Platform Extension | What VMGR is, normative basis, SIL-tiered activation |
| [5](#diagram-5) | Two-Track Loop per Phase | Track A (development) vs Track B (V&V), VMGR as SIL 3–4 gateway |
| [6](#diagram-6) | Phase 7 Special Flow | The only phase where VAL produces formal reports |

---

## Diagram 1 — V&V in the Lifecycle {#diagram-1}

VER produces a Verification Report at the close of **every phase** (1–6, 9, 10). VAL produces formal Validation Reports **only in Phase 7** (§7.7). In phases 1–6 and 9–10, VAL acts as "2nd Check" reviewer only — VAL does not author a report.

```
PHASE   TRACK A deliverables (Written By)          TRACK B — VER output            VAL output
─────   ──────────────────────────────────────────   ────────────────────────────    ──────────────────────
  1     SQAP (QUA)  ·  SCMP (CM)                    Item  2: SQAP VER Report         2nd Check on items 1–5
        SVP  (VER)  ·  SVaP (VAL)                   (VER reviews items 1, 3–5;
                                                     own SVP not self-checked)
  │
  2     SRS (REQ)  ·  Overall SW Test Spec (TST)    Item  8: SW Req. VER Report      2nd Check on items 6–8
  │
  3     SAS (DES)  ·  SDS (DES)                     Item 14: Arch. & Design VER      2nd Check on items 9–14
        SW Interface Specs (DES)                     Report
        SW Integration Test Spec (INT)
        SW/HW Integration Test Spec (INT)
  │
  4     SW Component Design Spec (DES)               Item 17: Component Design        2nd Check on items 15–16
        SW Component Test Spec (TST)                 VER Report                       (item 17 has no 2nd check)
  │
  5     SW Source Code + Supporting Docs (IMP)       Item 19: Source Code VER         2nd Check on items 18, 20
        SW Component Test Report (TST)               Report
  │
  6     SW Integration Test Report (INT)             (no separate VER report          2nd Check on items 21–22
        SW/HW Integration Test Report (INT)           produced in Phase 6 —
                                                     item 23 is in Phase 7)
  │
  7     Overall SW Test Report (TST)                 Item 23: SW Integration VER      Item 25: SW Validation Report ★
  ★     [Validation phase — VAL produces             Report                           Item 26: Tools Validation Report
        formal reports here only]                    Item †:  SW Validation VER       Item 27: Release Note (§7.7.4.12)
                                                     Report (§6.3.4.12–14;
                                                     see Diagram 6)
  │
  8     SW Assessment Plan (ASR)                     Item 45/46 1st Check (VER)       (ASR-driven; VAL role is reviewer)
        SW Assessment Report (ASR)
  │
  9     SW Release and Deployment Plan (PM)          Item 40: Deployment VER          2nd Check on items 36–39
        SW Deployment Manual (PM)                    Report
        Release Notes (PM)
        Deployment Records (PM)
  │
 10     SW Maintenance Plan (PM)                     Item 44: Maintenance VER         2nd Check on items 41–43
        SW Change Records (PM)                       Report
        SW Maintenance Records (PM)
```

**Key rules:**
- Item 23 (SW Integration Verification Report) belongs to **Phase 7**, not Phase 6 (Annex C Table C.1).
- Item 20 (SW Component Test Report) belongs to **Phase 5** on this platform (see `DELIVERABLES.md` Note 5).
- Item 4 (SVP) is written by **VER** — not PM.
- Item 5 (SVaP) is written by **VAL** — not PM.
- Items 45–46 (Assessment) are written by **ASR** — not PM.

---

## Diagram 2 — Deliverable Review Chain {#diagram-2}

Each Annex C deliverable passes through up to three review stages before being accepted. The chain is the same in all phases except Phase 7 (where VAL authors reports) and Phase 8 (ASR-authored).

```
┌───────────────────────────────────────────────────────────────────────────┐
│                     STANDARD DELIVERABLE REVIEW CHAIN                     │
│                      (Phases 1–6, 9–10 — typical)                         │
└───────────────────────────────────────────────────────────────────────────┘

  Author                1st Check              2nd Check          Accepted by
  ──────                ─────────              ─────────          ───────────
  REQ / DES /    ──►    VER                     VAL               VMGR (SIL 3–4)
  IMP / INT /           (Verification           (reviews          or COD (SIL 0–2)
  TST / QUA /           Report produced         deliverable
  CM / PM               at phase close)         only — no
                                                VAL report
                                                produced)

 ─────────────────────────────────────────────────────────────────────────────

┌───────────────────────────────────────────────────────────────────────────┐
│                    PHASE 7 DELIVERABLE REVIEW CHAIN                        │
│              (Validation phase — VAL authors formal reports)               │
└───────────────────────────────────────────────────────────────────────────┘

  Author                1st Check              2nd Check          Accepted by
  ──────                ─────────              ─────────          ───────────
  TST             ──►   VER              ──►   VAL               VMGR (SIL 3–4)
  (Overall SW           (item 23: SW           (reviews test      or COD (SIL 0–2)
  Test Report           Integration            evidence)
  item 24)              VER Report)

  VAL             ──►   VER              ──►   VMGR reviews       VMGR FINAL
  (Validation           (item †: SW            item † + VAL       V&V DECISION
  Reports               Validation             reports together   (SIL 3–4)
  items 25–26)          VER Report
                        §6.3.4.12–14)

 ─────────────────────────────────────────────────────────────────────────────

┌───────────────────────────────────────────────────────────────────────────┐
│                    PHASE 8 DELIVERABLE REVIEW CHAIN                        │
│                    (Assessment — ASR-authored)                              │
└───────────────────────────────────────────────────────────────────────────┘

  Author                1st Check              2nd Check
  ──────                ─────────              ─────────
  ASR             ──►   VER              ──►   (none — ASR has full independence)
  (items 45–46)         (1st check only)
```

**Annex C — Written By / 1st Check / 2nd Check per deliverable:**

| # | Document | Written By | 1st Check | 2nd Check |
|---|----------|------------|-----------|-----------|
| 1 | Software Quality Assurance Plan | QUA | VER | VAL |
| 2 | Software Quality Assurance Verification Report | VER | — | VAL |
| 3 | Software Configuration Management Plan | CM | VER | VAL |
| 4 | Software Verification Plan | VER | — | VAL |
| 5 | Software Validation Plan | VAL | VER | — |
| 6 | Software Requirements Specification | REQ | VER | VAL |
| 7 | Overall Software Test Specification | TST | VER | VAL |
| 8 | Software Requirements Verification Report | VER | — | VAL |
| 9 | Software Architecture Specification | DES | VER | VAL |
| 10 | Software Design Specification | DES | VER | VAL |
| 11 | Software Interface Specifications | DES | VER | VAL |
| 12 | Software Integration Test Specification | INT | VER | VAL |
| 13 | Software/Hardware Integration Test Specification | INT | VER | VAL |
| 14 | Software Architecture and Design Verification Report | VER | — | VAL |
| 15 | Software Component Design Specification | DES | VER | VAL |
| 16 | Software Component Test Specification | TST | VER | VAL |
| 17 | Software Component Design Verification Report | VER | — | — |
| 18 | Software Source Code and Supporting Documentation | IMP | VER | VAL |
| 19 | Software Source Code Verification Report | VER | — | VAL |
| 20 | Software Component Test Report | TST | VER | VAL |
| 21 | Software Integration Test Report | INT | VER | VAL |
| 22 | Software/Hardware Integration Test Report | INT | VER | VAL |
| 23 | Software Integration Verification Report | VER | — | — |
| 24 | Overall Software Test Report | TST | VER | VAL |
| 25 | Software Validation Report | VAL | VER | — |
| 26 | Tools Validation Report | VAL | VER | — |
| † | Software Validation Verification Report | VER | — | — |
| 27 | Release Note (§7.7.4.12) ‡ | — | VER | VAL |
| 36 | Software Release and Deployment Plan | PM | VER | VAL |
| 37 | Software Deployment Manual | PM | VER | VAL |
| 38 | Release Notes | PM | VER | VAL |
| 39 | Deployment Records | PM | VER | VAL |
| 40 | Deployment Verification Report | VER | — | — |
| 41 | Software Maintenance Plan | PM | VER | VAL |
| 42 | Software Change Records | PM | VER | VAL |
| 43 | Software Maintenance Records | PM | VER | VAL |
| 44 | Software Maintenance Verification Report | VER | — | VAL |
| 45 | Software Assessment Plan | ASR | VER | — |
| 46 | Software Assessment Report | ASR | VER | — |

> Full table with template paths: `DELIVERABLES.md`.

> **‡ Item 27 (Release Note, Phase 7):** Authorship is unresolved in Annex C (footnote `a` = project-specific assignment). §7.7.4.12 mandates the Release Note's content but does not assign authorship; §9.1.4.4 assigns the deployment-phase Release Note to the Designer (item 38 context). Projects shall designate the Phase 7 Release Note author explicitly in the SQAP. The blank "Written By" field reflects this unresolved ambiguity, not a deliberate assignment gap. See `DELIVERABLES.md` Note 3.

> **† Software Validation Verification Report:** Normatively required by §6.3.4.12 ("A Software Validation Verification Report shall be written, under the responsibility of the Verifier") and §6.3.4.13–6.3.4.14 (VER must verify the SVaP and the Software Validation Report; results recorded in this report). Not assigned an independent Annex C item number on this platform — produced as the output of VER's review of VAL reports in Phase 7 (Step B2). Must be explicitly named in the SVP (§6.2.4.2) and SQAP. Subject to Safety Authority confirmation of item numbering. See `DELIVERABLES.md` Note 8.

---

## Diagram 3 — Role Interaction Model {#diagram-3}

### SIL 3–4: Strict Independence

```
 SAFETY AUTHORITY / CUSTOMER
   │                   │
   ▼                   ▼
 COD ◄─── peer ────► ASR   (mandatory indep; §5.1.2.4–5.1.2.7, §6.4.1.1)
   │   coordination         No reporting to COD or PM
   │   (V&V outcome          Reviews ALL artifacts
   │    from VMGR)           External or internal at SA discretion
   │
   │  All V&V work routed
   │  through VMGR only
   │  (COD → VMGR, not COD → VER/VAL)
   ▼
 ══════════════════════ INDEPENDENCE WALL (§5.1.2.10(g–j)) ══════════════

 LEFT (Development)                │ RIGHT (Independent V&V)
 ──────────────────                │ ──────────────────────────────────
 PM                                │ VMGR  [platform ext.; basis §5.1.2.10(e–f)]
   │ orchestrates                  │   │ manages VER team
   ▼                               │   │ reviews VER + VAL reports
 REQ · DES · IMP                   │   │ provides final V&V approval
 INT · TST · SAF                   │   │ cannot be overridden by COD or PM
 QUA · CM                          │   │ does NOT report to COD or PM
                                   │   ▼
                                   │ VER  (Verifier — mandatory indep.)
                                   │   produces Verification Reports
                                   │   reports to VMGR
                                   │
                                   │ VAL  (Validator — mandatory indep.)
                                   │   releases software (§5.1.2.8, §6.3.4.16)
                                   │   SHALL NOT report to PM (§5.1.2.10(f))
                                   │   produces Validation Reports (Phase 7 only)

 ══════════════════════════════════════════════════════════════════════════
```

**Key rules at SIL 3–4:**
- COD routes ALL V&V work through VMGR — no direct COD→VER or COD→VAL.
- COD CANNOT override VMGR V&V decisions.
- PM has NO authority over VMGR, VER, VAL, or ASR.
- VAL is the **release authority** — software shall not be released without VAL agreement; VAL retains the explicit right to formally disagree and block release (§5.1.2.8, §6.3.4.16).
- VER+VAL same person: only with ASR approval (§5.1.2.10(n)).

### SIL 1–2: Permissive Organization

```
 SAFETY AUTHORITY / CUSTOMER
   │                   │
   ▼                   ▼
 COD                 ASR   (mandatory; §5.1.2.4, §5.1.2.11(k))
   │ authorizes              Reports to SA — independent from project
   ▼
 PM  (may oversee VER and VAL — §5.1.2.11(e))
   │ orchestrates
   ├──► REQ · DES · IMP · INT · TST · SAF · QUA · CM
   ├──► VER  (may report to PM; role-combination prohibition still M — §5.1.2.11(h))
   └──► VAL  (may report to PM; role-combination prohibition still M — §5.1.2.11(h))
              VAL = release authority (§6.3.4.16)
              VER + VAL may be same person (§5.1.2.11(d))
```

**Key rules at SIL 1–2:**
- No VMGR — COD interacts with VER and VAL directly.
- VER and VAL MUST NOT hold REQ/DES/IMP/INT/TST roles — mandatory prohibition regardless of org structure (§5.1.2.11(h)).
- ASR is mandatory; no ISO 9001 waiver at SIL 1–2.

### SIL 0: Minimal Organization

```
 SAFETY AUTHORITY / CUSTOMER
   │
   ▼
 COD
   │ authorizes
   ▼
 PM (orchestrates everything)
   ├──► REQ · DES · IMP · INT · TST · SAF · QUA · CM
    ├──► VER  (may report to PM; may be same person as INT/TST/VAL — §5.1.2.12(b))
   └──► VAL  (may report to PM; release authority — §6.3.4.16)
              ASR: waivable if ISO 9001 cert available (§6.4.1.2)
```

**Key rules at SIL 0:**
- INT + TST + VER + VAL for the same component may all be one person (§5.1.2.12(b)).
- Residual prohibition: REQ/DES/IMP shall not also be TST/INT for the same component (§5.1.2.12(d)); VER/VAL shall not be REQ/DES/IMP (§5.1.2.12(e)).

---

## Diagram 4 — VMGR Platform Extension {#diagram-4}

### What is VMGR?

VMGR (V&V Manager) is a **platform-defined independent authority**, not an Annex B role in EN 50128:2011. It is a coordination mechanism that implements the independence requirements of §5.1.2.10(e–f) at SIL 3–4.

```
 NORMATIVE BASIS
 ───────────────
 §5.1.2.10(e) — "The Verifier ... can report to the Project Manager
                  or to the Validator"
                 → Platform implements "reports to Validator" option
                   via a named VMGR authority, so VER team reports
                   to VMGR (not to PM).
                 → PLATFORM EXTENSION: COD routes ALL V&V work
                   through VMGR; no direct COD→VER or COD→VAL at
                   SIL 3–4. This routing rule exceeds the literal
                   text of §5.1.2.10(e) and is a platform
                   architectural decision. It must be approved by
                   the Safety Authority and documented in the SQAP.

 §5.1.2.10(f) — "The Validator shall not report to the Project Manager"
                 → VMGR sits on the independent side of the wall;
                   it is the structural anchor that prevents VAL from
                   being managed by PM.

 §5.1.2.10(g–j) — Mandatory independence wall (prohibitory "shall neither"
                   clauses): development roles shall not also be VER/VAL.
                   VMGR enforces this wall across the V&V stream.

 PLATFORM REQUIREMENT: VMGR must be approved by the Safety Authority
 and documented in the SQAP before use on any SIL 1–4 project.
 (ORGANIZATION.md — Platform Role Notice)
```

### SIL-tiered activation

| SIL Level | VMGR Present? | V&V Routing | Reference |
|---|---|---|---|
| SIL 0 | No | COD → VER/VAL directly | §5.1.2.12 |
| SIL 1–2 | No | COD → VER/VAL directly; PM may oversee | §5.1.2.11 |
| SIL 3–4 | **Yes — required** | COD → VMGR → VER/VAL only | §5.1.2.10(e–f), platform |

### What VMGR does per phase

```
 Phase 1–6, 9–10 (standard phases):
   VMGR assigns VER to verify phase deliverables
   VMGR reviews VER Verification Reports
   VMGR approves or rejects VER output
   VMGR reports V&V outcome to COD

 Phase 7 (Validation — special):
   VMGR coordinates both VER and VAL sequentially (see Diagram 6)
   VMGR reviews VER Integration Verification Report (item 23)
   VMGR coordinates VAL final validation
   VMGR reviews VAL Validation Reports (items 25–26)
   VMGR provides FINAL V&V DECISION — cannot be overridden by COD or PM
   VMGR reports final V&V outcome to COD

 Phase 8 (Assessment):
   ASR is fully independent from VMGR; VMGR has no authority over ASR
   VER performs 1st check on ASR deliverables (items 45–46) under VMGR

 All phases:
   VMGR cannot be bypassed at SIL 3–4
   VMGR does NOT report to COD or PM
   VMGR coordinates with COD (peer, no reporting relationship)
```

### VMGR is NOT:

- An Annex B EN 50128 role (it is a platform extension).
- A replacement for ASR (the Assessor remains mandatory and independent).
- A "manager" of VAL in the sense of directing VAL's decisions — VMGR coordinates; VAL holds release authority.
- Overridable by COD or PM.

---

## Diagram 5 — Two-Track Loop per Phase {#diagram-5}

Each phase (except Phase 7) runs two sequential tracks. PM owns Track A. COD coordinates Track B. At SIL 3–4, VMGR is the sole gateway between COD and the V&V stream.

```
 ┌──────────────────────────────────────────────────────────────────────┐
 │  TRACK A — Development  (PM orchestrates)                            │
 └──────────────────────────────────────────────────────────────────────┘
  USER → @pm execute-phase N
    │
    ▼
  PM orchestrates development agents
  (REQ · DES · IMP · INT · TST · SAF · CM as applicable to phase)
    │ phase deliverables produced
    ▼
  QUA template / format check
    ├── FAIL ──► PM coordinates rework with author → re-check
    └── PASS
          │
          ▼
        PM notifies COD: Track A complete for phase N

 ┌──────────────────────────────────────────────────────────────────────┐
 │  TRACK B — Independent Verification  (COD coordinates)              │
 │  PM has NO authority over any agent in this track                   │
 └──────────────────────────────────────────────────────────────────────┘

  COD receives Track A complete notification
    │
    ├── SIL 3–4 ──────────────────────────────────────────────────────┐
    │   COD → VMGR: request verification of phase deliverables        │
    │     │                                                           │
    │     ▼                                                           │
    │   VMGR assigns VER; VER verifies phase deliverables             │
    │     ├── REJECT deliverable ──► VMGR notifies COD                │
    │     │    COD notifies PM; PM coordinates rework                 │
    │     │    → rework re-enters Track A from QUA check              │
    │     └── APPROVE                                                 │
    │           │                                                     │
    │           ▼                                                     │
    │         VER produces Verification Report                        │
    │           │                                                     │
    │           ▼                                                     │
    │         QUA template check on VER report                        │
    │           ├── FAIL ──► VER re-issues (max 1 resubmission)       │
    │           └── PASS                                              │
    │                 │                                               │
    │                 ▼                                               │
    │               VMGR reviews VER report                           │
    │                 ├── REJECT ──► VER reworks; QUA re-checks       │
    │                 └── APPROVE                                     │
    │                       │                                         │
    │                       ▼                                         │
    │                     VMGR reports V&V outcome to COD             │
    └─────────────────────────────────────────────────────────────────┘
    ├── SIL 0–2 ──────────────────────────────────────────────────────┐
    │   COD invokes VER directly                                      │
    │     │ VER verifies phase deliverables → Verification Report     │
    │     ▼                                                           │
    │   QUA template check on VER report                              │
    │     ├── FAIL ──► VER re-issues                                  │
    │     └── PASS ──► COD receives VER report directly               │
    └─────────────────────────────────────────────────────────────────┘
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

> **VAL in Track B (phases 1–6, 9–10):** VAL reviews deliverables as 2nd Check reviewer — see `DELIVERABLES.md` column "2nd Check". VAL does **not** produce a Validation Report in these phases. VAL Validation Reports are produced **only in Phase 7** (§7.7).

---

## Diagram 6 — Phase 7 Special Flow {#diagram-6}

Phase 7 (§7.7 "Overall Software Testing / Final Validation") is the **only phase** where VAL authors formal Validation Reports. VER also produces item 23 (SW Integration Verification Report) here — this item belongs to Phase 7, not Phase 6.

```
 ┌──────────────────────────────────────────────────────────────────────┐
 │  TRACK A — Validation Activities  (PM orchestrates)                 │
 └──────────────────────────────────────────────────────────────────────┘
  USER → @pm execute-phase 7
    │
    ▼
  PM orchestrates TST (overall software testing)
    │ Item 24: Overall Software Test Report produced
    ▼
  QUA template check on test report
    ├── FAIL ──► PM coordinates rework → re-check
    └── PASS
          │
          ▼
        PM notifies COD: Track A complete

 ┌──────────────────────────────────────────────────────────────────────┐
 │  TRACK B — Independent V&V  (COD coordinates)                       │
 │  Sequential: Step B1 (VER) must complete before Step B2 (VAL)       │
 └──────────────────────────────────────────────────────────────────────┘

  COD receives Track A complete
    │
    ├── SIL 3–4 ──────────────────────────────────────────────────────┐
    │   COD → VMGR: request V&V for Phase 7                           │
    │     │                                                           │
    │     ▼                                                           │
    │   [Step B1 — Verification]                                      │
    │   VMGR assigns VER; VER produces Item 23:                       │
    │   Software Integration Verification Report                      │
    │     │                                                           │
    │     ▼                                                           │
    │   QUA template check on VER report                              │
    │     ├── FAIL ──► VER re-issues                                  │
    │     └── PASS                                                    │
    │           │                                                     │
    │           ▼                                                     │
    │         VMGR reviews VER report                                 │
    │           ├── REJECT ──► VER reworks; QUA re-checks             │
    │           └── APPROVE                                           │
    │                 │                                               │
    │                 ▼                                               │
    │   [Step B2 — Validation]                                        │
    │   VMGR assigns VAL; VAL performs final validation               │
    │     │ Reviews all phase evidence                                │
    │     │ Item 25: Software Validation Report                       │
    │     │ Item 26: Tools Validation Report (if applicable)          │
    │     │ Item 27: Release Note (§7.7.4.12) [authorship per SQAP — see Diagram 2 ‡]                         │
    │     │                                                           │
    │     ├── REJECT (evidence insufficient) ──► VMGR notifies COD   │
    │     │    COD notifies PM; PM coordinates rework                 │
    │     │    → rework re-enters Track A; full B1–B2 loop repeats    │
    │     └── APPROVE                                                 │
    │           │                                                     │
    │           ▼                                                     │
    │         QUA template check on VAL reports (items 25–26)         │
    │           ├── FAIL ──► VAL re-issues; QUA re-checks             │
    │           └── PASS                                              │
    │                 │                                               │
    │                 ▼                                               │
     │               VER produces Software Validation Verification     │
     │               Report (§6.3.4.12–6.3.4.14 — mandatory output    │
     │               recording VER's review of SVaP + Val. Report)    │
     │                 │                                               │
     │                 ▼                                               │
     │               QUA template check on VER Validation             │
     │               Verification Report (item †)                     │
     │                 ├── FAIL ──► VER re-issues (max 1 resubmission) │
     │                 └── PASS                                        │
     │                       │                                         │
     │                       ▼                                         │
     │               VMGR reviews VER report + VAL reports together    │
     │                 ├── REJECT ──► VAL/VER reworks; QUA re-checks   │
     │                 └── APPROVE — VMGR FINAL V&V DECISION           │
    │                       │       (cannot be overridden by COD/PM)  │
    │                       ▼                                         │
    │                     VMGR reports outcome to COD                 │
    └─────────────────────────────────────────────────────────────────┘
    ├── SIL 0–2 ──────────────────────────────────────────────────────┐
    │   COD invokes VER → item 23                                     │
    │   COD invokes VAL → items 25–27                                 │
    │   QUA checks all reports                                        │
    │   COD receives reports directly                                 │
    └─────────────────────────────────────────────────────────────────┘
    │
    ▼
  COD gate-check (Phase 7):
    ✓ Overall Software Test Report (item 24) QUA-passed
    ✓ SW Integration VER Report (item 23) QUA-passed and VMGR-approved (SIL 3–4)
    ✓ SW Validation Verification Report (item †) QUA-passed and VMGR-approved (SIL 3–4)
    ✓ Software Validation Report (item 25) QUA-passed and VMGR-approved (SIL 3–4)
    ✓ Tools Validation Report (item 26, if applicable) QUA-passed
    ✓ Release Note (item 27) present
    ✓ SVaP validation criteria satisfied — §6.3.4.4–6.3.4.6
    ✓ Zero critical open defects
    │
    ├── PASS ──► COD authorizes Phase 8 (Assessment) or Phase 9 (Deployment)
    └── FAIL ──► COD BLOCKS; coordinates rework; re-runs gate
```

> **Release Note note (item 27):** Normatively required by §7.7.4.12. Its Annex C item number (27) is based on sequential numbering after item 26. If the printed standard does not carry a formal item 27 entry, the Release Note remains a binding §7.7.4.12 output. See `DELIVERABLES.md` Note 3.

---

## Phase Transition Authority Summary

| Role | Can start phase? | Can block phase? | Can override? |
|------|-----------------|-----------------|---------------|
| COD  | YES (authorizes) | YES (gate check) | NOT VMGR decisions |
| PM   | NO (requests)    | NO               | NOT COD / VMGR decisions |
| VMGR | NO               | YES (V&V reject) | Cannot be overridden |
| VAL  | NO               | YES (release authority) | Cannot be overridden on release |
| ASR  | NO               | YES (assessment report) | Independent — reports to SA |

---

## Key Independence Constraints Summary

| Constraint | SIL | Reference |
|---|---|---|
| VAL shall not report to PM | 3–4 | §5.1.2.10(f) |
| COD routes ALL V&V work through VMGR — no direct COD→VER or COD→VAL | 3–4 | §5.1.2.10(e–f); platform |
| COD CANNOT override VMGR V&V decisions | 3–4 | Platform rule; basis §5.1.2.10(e–f) |
| VMGR does NOT report to COD or PM | 3–4 | §5.1.2.10(f); platform |
| VER reports to VMGR | 3–4 | §5.1.2.10(e); platform |
| VER/VAL shall not hold REQ/DES/IMP/INT/TST roles | 1–4 | §5.1.2.10(g–i), §5.1.2.11(h) |
| REQ/DES/IMP shall not be TST/INT for same component | 0–4 | §5.1.2.12(d), §5.1.2.10(g–h) |
| ASR is independent from ALL project roles including COD | 1–4 | §5.1.2.5–5.1.2.6, §5.1.2.11(k) (SIL 1–2), §5.1.2.10(m) (SIL 3–4), §6.4.1.1 |
| Software shall not be released without VAL sign-off | 0–4 | §5.1.2.8, §6.3.4.16 |
| VER+VAL same person (SIL 3–4): only with ASR approval | 3–4 | §5.1.2.10(n) |
| VER+VAL same person (SIL 1–2): permitted | 1–2 | §5.1.2.11(d) |
| VER+VAL roles shall remain unchanged throughout project | 0–4 | §5.1.2.14 |
| ASR may be waived at SIL 0 with ISO 9001 cert | 0 | §6.4.1.2 |

---

*References: EN 50128:2011 §5.1.2.4–5.1.2.14, §6.2.4.2, §6.3.4.2–6.3.4.16, §6.4.1.1–6.4.4.1, §7.7, Annex C Table C.1*
