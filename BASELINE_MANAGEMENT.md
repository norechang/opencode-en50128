# Baseline Management — Lifecycle Diagrams

This document covers baseline management across the EN 50128 V-Model lifecycle.

| # | Diagram | Purpose |
|---|---------|---------|
| [1](#diagram-1) | Lifecycle Baseline Map | All 8 baselines across phases 1–9, triggers, and required evidence |
| [2](#diagram-2) | Single Baseline Creation Flow | Per-baseline role interaction sequence (generic, all SIL tiers) |

**Authoritative sources**: `std/EN50128-2011.md` §6.6, §6.2.4.7–8, §6.2.4.13, §6.3.4.9–10, §9.1.4.2–3, §9.2.4, D.48; `WORKFLOW.md`; `DELIVERABLES.md`.

---

## Terminology note

EN 50128:2011 does **not** define "FCA" (Functional Configuration Audit) or "PCA" (Physical
Configuration Audit). Those terms come from MIL-STD-973 / IEEE 828 and are not used in this
standard. The EN 50128 equivalent activities are:

| Concept | EN 50128 owner | Clause |
|---------|---------------|--------|
| "Physical" check — each CI matches VCS and build artefacts | CM | §6.6, D.48 |
| Functional completeness — requirements satisfied per phase | VER | §6.2.4.7 |
| VER report documents identity/configuration of items verified | VER | §6.2.4.13(a) |
| VER evidence retained in format defined/referenced in SVP | CM (presence check) | §6.2.4.8 |
| Verification process complete | VAL | §6.3.4.9 |
| Baseline stated in Validation Report | VAL | §6.3.4.10 |
| CM records baseline under configuration control | CM | §9.1.4.2 |

**CM's role at a baseline event is record-keeping and presence-checking: verify that the required
signed documents and evidence artefacts are present, correctly versioned, and stored at canonical
paths. CM does NOT independently judge functional completeness — that is VER's and VAL's
responsibility, exercised during the phase and captured in their reports, which CM then checks
for presence.**

---

## Diagram 1 — Lifecycle Baseline Map {#diagram-1}

One baseline is created at each COD phase gate. The baseline name, trigger event, content
scope, and required signed evidence are shown for each gate.

```
V-MODEL PHASES               GATE    BASELINE CREATED        VER RPT  VAL RPT  §
────────────────────────────────────────────────────────────────────────────────
Legend: VER RPT = required VER Verification Report
        VAL RPT: "YES" = formal Validation Report (Phase 7 only)
                 "2nd check" = VAL 2nd-check of deliverables per DELIVERABLES.md
                 "—" = no formal VAL report; see DELIVERABLES.md for per-item
                       check assignments (some Phase 9 items have 2nd check)
────────────────────────────────────────────────────────────────────────────────

 PHASE 1 — Planning
  ┌───────────────────────────┐
  │ SQAP · SCMP · SVP · SVaP │──── Gate 1 ──► planning-baseline    Yes      2nd
  └───────────────────────────┘                Content: plans only  (SQAVR)  check*

  * Gate 1 VAL 2nd check applies to items 1 (SQAP), 3 (SCMP), 4 (SVP) only.
    Item 5 (SVaP) has no VAL 2nd check. See DELIVERABLES.md for per-item detail.

 PHASE 2 — Requirements
  ┌───────────────────────────┐
  │ SRS · OTSTSPEC            │
  │ REQVER                    │──── Gate 2 ──► requirements-        Yes      2nd   §6.2.4
  └───────────────────────────┘                baseline             (REQVER) check

 PHASE 3 — Architecture & Design
  ┌───────────────────────────┐
  │ SAS · SDS · INTERFACES    │
  │ INTTESTSPEC               │──── Gate 3 ──► design-baseline      Yes      2nd   §6.2.4
  │ HWINTTESTSPEC             │                                     (ARCH-   check
  │ ARCHDESIGNVER             │                                      DESIGN
  └───────────────────────────┘                                      VER)

 PHASE 4 — Component Design
  ┌───────────────────────────┐
  │ COMPDESIGN · COMPTESTSPEC │──── Gate 4 ──► component-design-    Yes      2nd   §6.2.4
  │ COMPDESIGNVER             │                baseline             (COMP-   check
  └───────────────────────────┘                                      DESIGN
                                                                     VER)

 PHASE 5 — Implementation & Testing
  ┌───────────────────────────┐
  │ Source code               │
  │ SOURCECODEVER             │
  │ COMPTESTRPT               │──── Gate 5 ──► implementation-      Yes      2nd   §6.2.4
  │ evidence/                 │                baseline             (SOURCE  check §7.5.4
  │   static-analysis/        │                                      CODE-
  │   coverage/               │                                      VER)
  │   test-logs/              │
  └───────────────────────────┘

 PHASE 6 — Integration
  ┌───────────────────────────┐
  │ INTTESTRPT                │
  │ HWINTTESTRPT              │──── Gate 6 ──► integration-         Yes†     2nd   §7.6.4
  │ evidence/                 │                baseline                      check
  │   integration-test-logs/  │
  └───────────────────────────┘

  † Gate 6 VER: VER performs integration test completeness review at Gate 6.
    The formal INTVER report (Annex C item 23) is produced in Phase 7 per Annex C.
    At Gate 6 no separate named VER report covers this gate; integration test
    completeness evidence is reviewed by VER as part of Gate 6 sign-off.

 PHASE 7 — Validation
  ┌───────────────────────────┐
  │ INTVER                    │
  │ OVERALLTESTRPT            │
  │ VALRPT                    │──── Gate 7 ──► release-baseline  ★  Yes      YES   §6.3.4
  │ TOOLSVALRPT (if appl.)    │                                     (INTVER) (VALRPT §9.1.4.2
  │ RELEASENOTE               │                                             + TOOLS §9.1.4.3
  │ evidence/                 │                                              VALRPT)
  │   system-test-logs/       │
  └───────────────────────────┘
  ★ release-baseline: VER and VAL both produce formal reports here.
    §6.3.4.10: Validation Report SHALL state the software baseline validated.
    §9.1.4.2:  Baseline SHALL be recorded under CM control before delivery.
    §9.1.4.3:  Release SHALL be reproducible throughout baseline lifecycle.

  [PHASE 8 — Assessment]
  No new baseline. ASR reviews release-baseline artefacts.
  §6.4.4.10: Assessor assesses CM system and evidence of its use.
  §6.4.4.13: Assessor assesses V&V activities and supporting evidence.
  CM provides ASR read-only access; stores ASR records in
  phase-8-assessment/evidence/assessor-records/

 PHASE 9 — Deployment
  ┌───────────────────────────┐
  │ DEPLOYPLAN · DEPLOYMAN    │
  │ RELEASENOTES              │──── Gate 9 ──► deployment-baseline  Yes      2nd   §9.1.4.2
  │ DEPLOYREC · DEPLOYVER     │                                     (DEPLOY  check‡ §9.1.4.3
  │ evidence/                 │                                      VER)
  │   deployment-records/     │
  └───────────────────────────┘
  §9.1.4.13: Deployment Record gives evidence that intended software
             has been loaded. Stored under CM control.

  ‡ Gate 9 VAL 2nd check applies to DEPLOYPLAN, DEPLOYMAN, RELEASENOTES, DEPLOYREC
    (Annex C items 36–39). DEPLOYVER (item 40) has no VAL 2nd check.
    See DELIVERABLES.md for authoritative per-item check assignments.

────────────────────────────────────────────────────────────────────────────────
CHANGE REQUEST PATH (any closed gate)
────────────────────────────────────────────────────────────────────────────────

 Post-gate defect / change need
       │
       ▼
 CCB approves CR  (see WORKFLOW.md Diagram 4)
       │
       ▼
 CM creates baseline BRANCH from the affected gate baseline
       │
       ▼
 PM re-executes affected phases → full Track A + Track B loop per phase
 (each phase produces new VER report; VAL re-confirms if Phase 7 affected)
 Basis: §6.6.4.2 — all changes SHALL initiate a return to an appropriate
        lifecycle phase; §9.2.4 (maintenance-phase changes)
       │
       ▼
 All affected COD gates re-pass → CM creates updated post-CR baseline
       │
       ▼
 CM archives superseded baseline (never deleted)
 Basis: §9.1.4.2 — baseline shall remain traceable under CM control;
        D.48 — every version of every significant deliverable shall be recorded
```

---

## Diagram 2 — Single Baseline Creation Flow {#diagram-2}

This flow applies to every baseline creation event (Gates 1–7, Gate 9).
The baseline is created **after** COD gate-check passes — meaning VER and VAL have
already done their work and produced their reports. CM's job here is confirmation
and record-keeping, not functional assessment.

```
 PRE-CONDITION: VER Verification Report produced and VMGR-approved (SIL 3-4).
                VAL 2nd-check (or VAL Report in Phase 7) produced and approved.
                COD gate-check PASS.
                  │
                  ▼
 ┌──────────────────────────────────────────────────────────────────────────┐
 │  STEP 1 — COD authorizes baseline; PM notifies CM                       │
 │                                                                          │
 │  COD ──► PM: "Gate N passed; baseline to be created"                    │
 │  PM  ──► CM: "Phase N complete; please prepare baseline"                │
 └──────────────────────────────────────────────────────────────────────────┘
                  │
                  ▼
 ┌──────────────────────────────────────────────────────────────────────────┐
 │  STEP 2 — CM checks CI presence and version control (CM responsibility) │
 │                                                                          │
 │  CM queries document-registry.yaml for all CIs in scope of Gate N.     │
 │  For each CI, CM verifies:                                               │
 │    ✓ Document present at canonical path (query-location)                │
 │    ✓ Document at expected version in VCS                                 │
 │    ✓ Evidence artefacts present at canonical evidence paths             │
 │    ✓ File integrity (hashes recorded)                                   │
 │                                                                          │
 │  CM does NOT judge whether content is correct — that is VER's role.    │
 │                                                                          │
 │  If any CI missing or at wrong path:                                    │
 │    → CM raises CRITICAL violation; invokes PM via task tool             │
 │    → PM coordinates author to correct; CM re-validates                  │
 └──────────────────────────────────────────────────────────────────────────┘
                  │
                  ▼
 ┌──────────────────────────────────────────────────────────────────────────┐
 │  STEP 3 — CM checks required signed reports are present                 │
 │           (CM responsibility — presence only, not content)              │
 │                                                                          │
 │  CM verifies:                                                            │
 │    ✓ VER Verification Report for Phase N is present and signed          │
 │      Basis: §6.2.4.8 — "results of each verification shall be          │
 │      retained in a format defined or referenced in the SVP"             │
 │    ✓ VER report documents identity/configuration of items verified      │
 │      Basis: §6.2.4.13(a)                                                │
 │    ✓ VMGR approval on VER report (SIL 3–4)                             │
 │    ✓ VAL 2nd-check sign-off present (all phases except Phase 7)        │
 │    ✓ VAL Validation Report present and states the baseline (Phase 7)   │
 │      Basis: §6.3.4.10 — "Validation Report shall fully state the       │
 │      software baseline that has been validated"                          │
 │    ✓ §6.3.4.9 satisfied — Validator has checked verification complete  │
 │      (evidenced by VAL report content, not re-checked by CM)            │
 │    ✓ QUA template check passed on all reports                           │
 │                                                                          │
 │  What CM does NOT do:                                                    │
 │    ✗ CM does not re-verify requirements traceability (VER's job)        │
 │    ✗ CM does not judge whether test coverage is adequate (VER/TST)      │
 │    ✗ CM does not assess whether defects are safety-critical (SAF/VER)   │
 │    ✗ CM does not confirm validation strategy is sufficient (VAL)        │
 │                                                                          │
 │  If any required report is missing or unsigned:                         │
 │    → CM raises CRITICAL violation; invokes PM via task tool             │
 │    → process returns to appropriate Track B step in WORKFLOW.md         │
 └──────────────────────────────────────────────────────────────────────────┘
                  │
                  ▼
 ┌──────────────────────────────────────────────────────────────────────────┐
 │  STEP 4 — CM records build environment                                  │
 │                                                                          │
 │  CM records in manifest:                                                 │
 │    • Compiler name and version                                           │
 │    • Compiler flags and build configuration                             │
 │    • Static analysis tool name and version                              │
 │    • Coverage tool name and version                                     │
 │    • OS and build host information                                       │
 │  Basis: §9.1.4.3 — release SHALL be reproducible                       │
 │  Basis: D.48 — SCM records every version of every significant item     │
 └──────────────────────────────────────────────────────────────────────────┘
                  │
                  ▼
 ┌──────────────────────────────────────────────────────────────────────────┐
 │  STEP 5 — CM creates baseline manifest                                  │
 │                                                                          │
 │  Stored at: baselines/<baseline-name>/manifest.yaml                     │
 │  Content:                                                                │
 │    • Baseline name, gate number, phase name, date                       │
 │    • All CIs: doc key · filename · VCS commit hash · version            │
 │    • All evidence artefacts: type · path · file hash                    │
 │    • VER Verification Report reference + approval status                │
 │    • VAL report reference (Phase 7) or 2nd-check reference              │
 │    • QUA pass record for all reports                                     │
 │    • Build environment record (from Step 4)                             │
 │    • Open defect list with disposition (CM records, VER determines)     │
 │                                                                          │
 │  Basis: §9.1.4.2 — baseline SHALL be recorded and kept traceable       │
 │  under configuration management control                                 │
 └──────────────────────────────────────────────────────────────────────────┘
                  │
                  ▼
 ┌──────────────────────────────────────────────────────────────────────────┐
 │  STEP 6 — CM creates immutable VCS tag                                  │
 │                                                                          │
 │  Tag format: <project>-gate<N>-<baseline-name>-<YYYYMMDD>               │
 │  Example:    myproject-gate5-implementation-baseline-20260324           │
 │                                                                          │
  │  Tag is PROTECTED — force-push disabled; deletion requires CCB          │
  │  approval and a new Change Record.                                       │
  │  Basis: §9.1.4.2 (baseline shall remain traceable under CM control)     │
  │         D.48 (every version of every significant deliverable recorded)   │
  │                                                                          │
  │  Basis: §9.1.4.3 — release SHALL be reproducible from this tag         │
 └──────────────────────────────────────────────────────────────────────────┘
                  │
                  ▼
 ┌──────────────────────────────────────────────────────────────────────────┐
 │  STEP 7 — CM notifies COD: baseline complete                            │
 │                                                                          │
 │  CM ────────────────────────────────────────────────► COD               │
 │     "Gate N baseline complete: <baseline-name>"                          │
 │     "All CIs present ✓ | VER report present ✓ | VCS tag: <tag>"        │
 │     "Manifest: baselines/<baseline-name>/manifest.yaml"                 │
 │                                                                          │
 │  COD records baseline reference in LIFECYCLE_STATE.md                   │
 │  and confirms gate N closed.                                             │
 └──────────────────────────────────────────────────────────────────────────┘

 ─────────────────────────────────────────────────────────────────────────────
 ROLE RESPONSIBILITIES SUMMARY
 ─────────────────────────────────────────────────────────────────────────────

  Who               What they do                              When       §
  ────────────────  ────────────────────────────────────────  ─────────  ──────
  VER               Verifies phase deliverables; produces     Phase      §6.2.4.7
                    Verification Report stating identity       execution  §6.2.4.13
                    and configuration of items verified
  VAL               Checks verification is complete;          Phase 7    §6.3.4.9
                    Validation Report states the baseline      (reports)  §6.3.4.10
                    validated; 2nd-check on other phases       All phases
  VMGR              Approves VER and VAL reports               Track B    Platform
  QUA               Template/compliance check on all reports  Track A+B  §6.5.4
  CM (Step 2)       Checks CIs present at canonical paths;   Baseline   §6.6, D.48
                    correct VCS versions; evidence stored      creation
  CM (Step 3)       Checks required signed reports present;  Baseline   §6.2.4.8
                    does NOT re-perform functional checking    creation   §6.3.4.10
  CM (Steps 4–6)    Records build env; writes manifest;       Baseline   §9.1.4.2
                    creates VCS tag                            creation   §9.1.4.3
  COD               Authorizes baseline creation after        Gate       Platform
                    gate-check passes                          check

 RACI per step (A=Accountable/Authorizes, R=Responsible/Acts, C=Consulted, I=Informed)
 Note: this uses standard RACI notation. Step 1 uses A for COD (authorizes baseline
 creation) and R for PM (responsible for notifying CM per COD's instruction).
 ─────────────────────────────────────────────────────────────────────────────
  Step │ CM  │ PM  │ VER │ VAL │ VMGR│ COD │ QUA
 ──────┼─────┼─────┼─────┼─────┼─────┼─────┼────
   1   │ I   │ R   │     │     │     │ A   │
   2   │ A   │     │     │     │     │     │
   3   │ A   │     │     │     │     │     │     (reports produced earlier by VER/VAL)
   4   │ A   │     │     │     │     │     │
   5   │ A   │     │     │     │     │     │
   6   │ A   │     │     │     │     │     │
   7   │ R   │     │     │     │     │ I   │
```

---

## Gate Baseline Quick Reference

| Gate | Phase | Baseline Name | VER report required | VAL report required | Key clause |
|------|-------|--------------|---------------------|---------------------|-----------|
| 1 | Planning | `planning-baseline` | SQAVR | 2nd check (items 1,3,4; SVaP exempt — see DELIVERABLES.md) | §6.6 |
| 2 | Requirements | `requirements-baseline` | REQVER | 2nd check | §6.2.4 |
| 3 | Architecture & Design | `design-baseline` | ARCHDESIGNVER | 2nd check | §6.2.4 |
| 4 | Component Design | `component-design-baseline` | COMPDESIGNVER | 2nd check | §6.2.4 |
| 5 | Implementation & Testing | `implementation-baseline` | SOURCECODEVER | 2nd check | §6.2.4, §7.5.4 |
| 6 | Integration | `integration-baseline` | VER review of integration test evidence† | 2nd check | §7.6.4 |
| 7 | Validation ★ | `release-baseline` | INTVER | VALRPT | §6.3.4, §9.1.4.2–3 |
| — | Assessment | *(no new baseline)* | — | — | §6.4.4.10 |
| 9 | Deployment | `deployment-baseline` | DEPLOYVER | 2nd check (items 36–39; DEPLOYVER exempt — see DELIVERABLES.md) | §9.1.4.2–3 |
| 10 | Maintenance | per-CR baseline | MAINTVER | — | §6.6.4.1, §6.6.4.2, §9.2.4 |

† At Gate 6, the formal INTVER report (Annex C item 23) is not yet produced; VER performs
  a review of integration test completeness. The formal INTVER report is produced in Phase 7
  per Annex C. See Diagram 1 Gate 6 notes.

★ `release-baseline` is the most critical: it is the official software release candidate.
  §6.3.4.10 requires the Validation Report to explicitly state this baseline.
  §9.1.4.3 requires it to remain reproducible for the entire operational lifetime.
  CM's role is to record and preserve this baseline — not to validate it.
