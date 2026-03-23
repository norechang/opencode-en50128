# EN 50128 Deliverable Traceability

> **Standard**: EN 50128:2011 Railway Software Standard  
> **Scope**: Complete traceability of deliverables across all lifecycle phases (Phase 0–10), including system-level input documents, responsible roles, V&V correspondences, and inter-document traceability chains.  
> **Version**: 1.3  
> **Date**: 2026-03-23  
> **References**: `LIFECYCLE.md`, `DELIVERABLES.md`, `WORKFLOW.md`, `AGENTS.md`

---

## 1. Overview

This document defines the complete traceability structure for EN 50128:2011-compliant railway software development. It covers:

1. **Diagram 1** — V-Model: deliverables per phase, with V&V specification-to-report correspondences
2. **Diagram 2** — Deliverable-to-deliverable traceability chain (forward and backward)
3. **Diagram 3** — Roles per phase with authorship, 1st check (VER), 2nd check (VAL), and independence constraints
4. **Traceability rules** — Normative obligations from EN 50128:2011

Traceability is **bidirectional** (forward: system requirement → design → code → test; backward: test → code → design → requirement) per §5.3.2.7 ("for each document, traceability shall be provided in terms of a unique reference number and a defined and documented relationship with other documents"). Traceability completeness is checked by VER at each phase (§6.5.4.14–6.5.4.17) and enforced at every COD phase gate check on the basis of VER's Verification Report.

---

## 2. Diagram 1 — V-Model: Deliverables and Phases

The V-Model left side (specification/development) maps directly to right-side verification/validation activities. System-level documents (Phase 0) are mandatory inputs to Phase 2 per §7.2.2.

```
╔══════════════════════════════════════════════════════════════════════════════════════════╗
║             EN 50128 V-Model — Deliverables, Phases, and V&V Correspondence             ║
╚══════════════════════════════════════════════════════════════════════════════════════════╝

Phase 0  SYSTEM LEVEL INPUTS (COD-generated; pre-software-lifecycle)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 S1  System Requirements Specification                [docs/system/]
 S2  System Architecture Description                  [docs/system/]
 S3  System Safety Plan                               [docs/system/]
 S4  System Safety Requirements Specification         [docs/system/]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
        │S1,S4                                                   │S3
        ▼                                                         ▼
┌─────────────────────────────┐                   ┌──────────────────────────────────────┐
│   Phase 1: PLANNING         │                   │   Phase 7: VALIDATION                │
│  (§5, §6.5, §6.6)           │                   │  (§7.7)                              │
│                             │                   │                                      │
│  1  SQAP        ◄── S3,S4  │                   │ 23  SW Integration Verification Rpt  │
│  2  SQAP Ver. Report        │                   │     [note A — see Section 12]        │
│  3  SCMP                    │                   │ 24  Overall SW Test Report  ◄──[7]  │
│  4  SVP         ◄── S3     │                   │ 25  Software Validation Report       │
│  5  SVaP        ◄── S3     │                   │ 26  Tools Validation Report          │
│     [deviation D1]          │                   │ 27  Release Note                     │
└─────────────────────────────┘                   └──────────────────────────────────────┘
        │                                                         ▲
        │S1,S4                                                    │
        ▼                                                         │
┌─────────────────────────────┐                   ┌──────────────────────────────────────┐
│   Phase 2: REQUIREMENTS     │                   │   Phase 6: INTEGRATION               │
│  (§7.2)                     │                   │  (§7.6)                              │
│                             │                   │                                      │
│  6  SRS          ◄── S1,S4 │                   │ 21  SW Integration Test Report ◄─[12]│
│  7  Overall SW Test Spec ───┼───────────────────┼──► 24  Overall SW Test Report       │
│  8  SRS Verification Report │                   │ 22  SW/HW Integration Test Rpt ◄[13]│
└─────────────────────────────┘                   └──────────────────────────────────────┘
        │                                                         ▲
        │SRS                                                      │
        ▼                                                         │
┌─────────────────────────────┐                   ┌──────────────────────────────────────┐
│ Phase 3: ARCHITECTURE &     │                   │   Phase 5: IMPLEMENTATION            │
│         DESIGN (§7.3)       │                   │           & TESTING (§7.5)           │
│                             │                   │                                      │
│  9  SAS          ◄── SRS   │                   │ 18  Source Code & Documentation      │
│     [S2 informs; see §6]    │                   │ 19  Source Code Verification Report  │
│ 10  SDS          ◄── SRS   │                   │ 20  Software Component Test Report   │
│ 11  SW Interface Specs      │                   │     ◄── [16]  [deviation D2]         │
│ 12  SW Integration Test Spec┼──────────────────►│ (21 executed in Phase 6)             │
│ 13  SW/HW Integration Test  ┼──────────────────►│ (22 executed in Phase 6)             │
│     Specification           │                   └──────────────────────────────────────┘
│ 14  SW Arch and Design Ver.  │                                   ▲
│     Report [see full name   │                                   │
│     in Sections 4 and 11]   │                                   │
└─────────────────────────────┘                                   │
        │                                                         │
        │SDS                                                      │
        ▼                                                         │
┌─────────────────────────────────────────────────────────────────┘
│   Phase 4: COMPONENT DESIGN (§7.4)
│
│  15  Software Component Design Specification  ◄── SDS
│  16  Software Component Test Specification    ──────────────────────────► 20 Software Component Test Report
│  17  Software Component Design Verification Report
└──────────────────────────────────────────────────────────────────

─────────────────────────────────────────────────────────────────────────────────────────
  Phase 8: ASSESSMENT (§6.4)                │  Phase 9: DEPLOYMENT (§9.1)
  (mandatory SIL 1–4 per §6.4.1.1)          │
  (SIL 0 exempt per §6.4.1.2)               │  36  Software Release & Deployment Plan
                                             │  37  Software Deployment Manual
  45  Software Assessment Plan               │  38  Release Notes
  46  Software Assessment Report             │  39  Deployment Records
                                             │  40  Deployment Verification Report
─────────────────────────────────────────────┼──────[deviation D3]────────────────────
  Phase 10: MAINTENANCE (§9.2)              │
  (CCB-triggered; ongoing)                   │
                                             │
  41  Software Maintenance Plan              │
  42  Software Change Records                │
  43  Software Maintenance Records           │
  44  Software Maintenance Verification Rpt  │
      [deviation D4]                         │
─────────────────────────────────────────────┘

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
CROSS-CUTTING (all phases): VER (Verification §6.2) · QUA (Quality Assurance §6.5)
                             CM (Configuration Management §6.6) · SAF (Safety Management)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Notes for Diagram 1:
  [note A] Item 23 (Software Integration Verification Report): normative production clause is §7.6.4.11
           (Integration phase). Placed in Phase 7 per informative Annex C Table C.1. The normative
           vs. informative tension is a known standard ambiguity — see Section 12.
  [item 14] Full normative name: "Software Architecture and Design Verification Report"
            (abbreviated in this box for space; see Diagram 3 / Section 11 for full name).
  [deviation D1–D4]: Annex C Table C.1 phase-column deviations — see Section 12 for full details.
```

---

## 3. Diagram 2 — Deliverable-to-Deliverable Traceability Chain

This diagram shows the complete forward traceability chain from system-level inputs (Phase 0) through to validation reports, and highlights the V-Model specification-to-report pairs.

```
╔══════════════════════════════════════════════════════════════════════════════════════════╗
║         EN 50128 — Deliverable-to-Deliverable Traceability Chain (Forward)              ║
╚══════════════════════════════════════════════════════════════════════════════════════════╝

SYSTEM LEVEL (Phase 0 — COD-generated)
───────────────────────────────────────────────────────────────────────────────────────────
 S1  System Requirements Specification ──────────────────────────────────────────┐
 S2  System Architecture Description (informative input to SAS — see note*)  ┐   │
     [Note: S1 + S2 together constitute the "System Design Description" referenced   │
      in §7.3.4.33. No separate System Design Description is produced in this        │
      platform. This mapping must be confirmed in the project SQAP — see D9.]    ┐   │
 S3  System Safety Plan ──────────────────────────────────────────────────┐  │   │
 S4  System Safety Requirements Specification ────────────────────────┐   │  │   │
                                                                      │   │  │   │
PHASE 1: PLANNING                                                     │   │  │   │
───────────────────────────────────────────────────────────────────── │   │  │   │
 [1]  SQAP ◄─────────────────────────────────────── S3, S4 ──────────┘   │  │   │
 [3]  SCMP                                                                │  │   │
 [4]  SVP  ◄────────────────────────────────────── S3 ───────────────────┘  │   │
 [5]  SVaP ◄────────────────────────────────────── S3 ───────────────────────┘   │
                                                                                  │
PHASE 2: REQUIREMENTS                                                             │
───────────────────────────────────────────────────────────────────────────────── │
 [6]  Software Requirements Specification (SRS)                                   │
       ◄──── S1 (system requirements allocated to software; §7.2.2)               │
       ◄──── S4 (safety requirements allocated to software; §7.2.2) ◄─────────────┘
       │
       ├──► [7]  Overall Software Test Specification ──────────────────► [24] Overall SW Test Report
       │          (traces every SRS requirement; §7.2.4.19)
       │
       └──► [9]  Software Architecture Specification (SAS)
                  ◄──── [6] SRS (normative basis; §7.3.4.1)
                  ◄──── S2 (informative/contextual input only — NOT a §7.3.2 normative input**)
                  │
                  ├──► [10] Software Design Specification (SDS)
                  │          (normative basis per §7.3.4.20: [9] SAS + [6] SRS + [11] Interface Specs)
                  │          │
                  │          ├──► [15] Software Component Design Specification
                  │          │          │
                  │          │          ├──► [18] Source Code & Supporting Documentation
                  │          │          │          │
                  │          │          │          └──► verified by ──► [19] Source Code Verification Rpt
                  │          │          │                               executed in ──► [21] SW Integration Test Rpt
                  │          │          │                                            ──► [22] SW/HW Integration Test Rpt
                  │          │          │                                            ──► [24] Overall SW Test Report
                  │          │          │
                  │          │          └──► [16] Software Component Test Specification
                  │          │                     │
                  │          │                     └──► executes against [18] ──► [20] Software Component Test Report
                  │          │
                  │          └──► [17] Software Component Design Verification Report
                  │
                  ├──► [11] Software Interface Specifications
                  │          └──► verified in ──► [21] SW Integration Test Report
                  │                             ──► [22] SW/HW Integration Test Report
                  │
                  ├──► [12] Software Integration Test Specification ────► [21] SW Integration Test Report
                  │          (basis per §7.3.4.29: [6] SRS + [9] SAS + [10] SDS + [11] Interface Specs)
                  │
                  ├──► [13] SW/HW Integration Test Specification ───────► [22] SW/HW Integration Test Report
                  │          (basis per §7.3.4.33: System Design Description + [6] SRS + [9] SAS + [10] SDS)
                  │
                  └──► [14] Software Architecture and Design Verification Report

INTEGRATION EVIDENCE → VALIDATION
───────────────────────────────────────────────────────────────────────────────────────────
 [21] SW Integration Test Report            ─┐
 [22] SW/HW Integration Test Report         ─┼──► [23] Software Integration Verification Report
 [20] Software Component Test Report        ─┘          │
                                                         └──► [24] Overall SW Test Report
                                                                    │
                                                                    └──► [25] Software Validation Report
                                                                               │
                                                                               └──► Safety requirements
                                                                                    from S4 validated ✓

DEPLOYMENT & MAINTENANCE
───────────────────────────────────────────────────────────────────────────────────────────
 [25] SW Validation Report ──► [45] Assessment Plan ──► [46] Assessment Report ──► [36] Deployment Plan
 [46] Assessment Report    ──► [36] Release & Deployment Plan ──► [39] Deployment Records
 [39] Deployment Records   ──► [41] Maintenance Plan (CCB-triggered re-entry)
 [41] Maintenance Plan     ──► [42] Change Records ──► [43] Maintenance Records ──► [44] Maintenance Ver. Report

BACKWARD TRACEABILITY (all paths reversible)
───────────────────────────────────────────────────────────────────────────────────────────
 [25] SW Validation Report         ◄── [24] Overall SW Test Report
 [24]                              ◄── [21] + [22] + [20] test evidence
 [20] Software Component Test Rpt  ◄── [18] Source Code (executed against [16] specs)
 [18] Source Code                  ◄── [15] Software Component Design Specification
 [15]                              ◄── [10] Software Design Specification
 [10]                              ◄── [9]  Software Architecture Specification
 [9]                               ◄── [6]  Software Requirements Specification (§7.3.4.1)
 [6]                               ◄── S1   System Requirements Specification
 [6]                               ◄── S4   System Safety Requirements Specification

 * S2 (System Architecture Description): §7.2.2 lists S2 as an input to the Requirements phase
   (SRS). The SRS is then the sole normative input to §7.3 (Architecture phase) per §7.3.2.
   S2 may inform the SAS contextually but is not a §7.3.2 normative traceability source.
```

---

## 4. Diagram 3 — Authorship, Verification Chain, and Independence Reference

```
╔══════════════════════════════════════════════════════════════════════════════════════════╗
║       EN 50128 — Authorship, Verification Chain, and Independence per Phase             ║
╚══════════════════════════════════════════════════════════════════════════════════════════╝

 Legend:  * = Independent required (mandatory SIL 3-4; HR SIL 2)
          † = Independent from project AND supplier (mandatory SIL 1-4 per §6.4.1.1)
          (a) = Annex C footnote "a" — writer assigned by project SQAP
          1st = First Check (VER)  |  2nd = Second Check (VAL)

────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Phase    Doc#  Document Name                                  Author(s)         1st Chk  2nd Chk  Special / Independence Notes
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Phase 0  S1    System Requirements Specification              COD               —        —        COD-generated; mandatory input to Phase 2 (§7.2.2)
          S2    System Architecture Description                COD               —        —        Informative input to SAS (not §7.3.2 normative); see §6
          S3    System Safety Plan                             COD               —        —        Feeds SQAP, SVP, SVaP in Phase 1
          S4    System Safety Requirements Spec                COD               —        —        Feeds SRS safety req's in Phase 2 (§7.2.2)

 Phase 1  1     Software Quality Assurance Plan                VER (resp.) /     VER      VAL      §6.5.4.3: written "under responsibility of Verifier";
                                                               QUA (author)                        VER holds normative responsibility. If QUA authors
                                                               [project SQAP]                      under VER direction, this must be documented in SQAP.
                                                                                                   Normatively mandatory ALL SIL per §6.5.4.3.
          2     Software Quality Assurance Verification Report VER               —        VAL
          3     Software Configuration Management Plan         CM                VER      VAL      (§5.3.2.4 — SCMP shall be drawn up at start of project);
                                                                                                   §6.6.4.1 governs the Change Management Process *content*
                                                                                                   described within the SCMP, not the obligation to produce it.
          4     Software Verification Plan                     VER               —        VAL      (§6.2.4.2); VER writes own plan
          5     Software Validation Plan                       VAL               VER      —        (§6.3.4.2); DEVIATION D1: placed Phase 1 — see §12

 Phase 2  6     Software Requirements Specification            REQ + SAF         VER      VAL      USER APPROVAL REQUIRED; §7.2.4.1
          7     Overall Software Test Specification            TST               VER      VAL      Traces all SRS requirements (§7.2.4.16, §7.2.4.19)
          8     Software Requirements Verification Report      VER               —        VAL

 Phase 3  9     Software Architecture Specification            DES + SAF         VER      VAL      Normative input basis: SRS per §7.3.4.1
          10    Software Design Specification                   DES               VER      VAL
          11    Software Interface Specifications               DES               VER      VAL      Plural form per §7.3.3 item 3
          12    Software Integration Test Specification         INT               VER      VAL      Spec → Report [21]; §7.3.4.29, §7.3.4.31
          13    Software/Hardware Integration Test Specification INT               VER      VAL      Spec → Report [22]
          14    Software Architecture and Design               VER               —        VAL
                Verification Report

 Phase 4  15    Software Component Design Specification        DES               VER      VAL
          16    Software Component Test Specification          TST               VER      VAL      Spec → Report [20]; §7.4.4.7
          17    Software Component Design Verification Report  VER               —        —

 Phase 5  18    Software Source Code and Supporting            IMP               VER      VAL      MISRA C:2012 mandatory SIL 2+; §7.5.4.1
                Documentation
          19    Software Source Code Verification Report       VER               —        —        2nd Check: blank per Annex C Table C.1.
                                                                                                   Any project decision to add VAL 2nd check
                                                                                                   must be documented in SQAP as a project addition.
          20    Software Component Test Report                 TST               VER      VAL      DEVIATION D2: Phase 5 — see §12

 Phase 6  21    Software Integration Test Report               INT + TST         VER      VAL      Executes spec [12]
          22    Software/Hardware Integration Test Report       INT + TST         VER      VAL      Executes spec [13]

 Phase 7  23    Software Integration Verification Report       VER*              —        —        Normative production clause: §7.6.4.11 (Integration);
                                                                                                   placed Phase 7 per informative Annex C. See §12.
          24    Overall Software Test Report                   TST               VER      VAL      PM track; executes spec [7]
          25    Software Validation Report                     VAL*  (a)         VER      —        VAL MUST BE INDEPENDENT SIL 3-4 (§5.1.2.10f)
          26    Tools Validation Report                        VAL*  (a)         VER      —        VAL MUST BE INDEPENDENT SIL 3-4
          27    Release Note                                   DES   (a)         VER      VAL      §7.7.4.12 normative; author per §9.1.4.4 (Designer
                                                                                                   responsibility). Authorship must be confirmed in SQAP.

 Phase 8  45    Software Assessment Plan                       ASR†              VER      —        † ASR independent from project AND supplier
          46    Software Assessment Report                     ASR†              VER      —          (§5.1.2.5–5.1.2.7). Mandatory SIL 1–4 (§6.4.1.1);
                                                                                                     SIL 0 exempt per §6.4.1.2.

 Phase 9  36    Software Release and Deployment Plan           PM  (a)           VER      VAL      Author per project SQAP (Annex C footnote a); §9.1.4.1
          37    Software Deployment Manual                     DES (a)           VER      VAL      Author per project SQAP (Annex C footnote a)
          38    Release Notes                                  PM  (a)           VER      VAL      Plural; distinct from item 27 (singular Release Note)
          39    Deployment Records                             CM  (a)           VER      VAL      Author per project SQAP (Annex C footnote a)
          40    Deployment Verification Report                 VER               —        —        DEVIATION D3: Phase 9 — see §12

 Phase 10 41    Software Maintenance Plan                      PM                VER      VAL      CCB-triggered re-entry
          42    Software Change Records                        PM                VER      VAL      (typo in std: "Software Chang Records")
          43    Software Maintenance Records                   PM                VER      VAL
          44    Software Maintenance Verification Report       VER               —        VAL      DEVIATION D4: Phase 10 — see §12.
                                                                                                   2nd Check (VAL) is a project addition; verify against
                                                                                                   printed Annex C Table C.1 and document in SQAP if blank.

 Cross-   —     Ongoing Verification activities                VER*              —        VMGR     * Independence mandatory SIL 3-4 (§5.1.2.10e)
 cutting  —     Ongoing QA audits / template checks            QUA               —        —        VMGR communicates V&V outcomes to COD (no hierarchical
          —     Configuration Management / baselines           CM                —        —        reporting relationship — §5.1.2.10f; VMGR independent)
          —     Hazard/safety analysis updates                 SAF               —        —
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
```

---

## 5. V-Model Specification-to-Report Correspondence

The V-Model's defining characteristic is that every specification document created on the left (development) side has a corresponding test/verification report on the right (V&V) side.

| Specification (Left Side) | Doc # | Phase Created | Report (Right Side) | Doc # | Phase Produced |
|---------------------------|-------|---------------|---------------------|-------|----------------|
| Overall Software Test Specification | 7 | 2: Requirements | Overall Software Test Report | 24 | 7: Validation |
| Software Integration Test Specification | 12 | 3: Architecture & Design | Software Integration Test Report | 21 | 6: Integration |
| Software/Hardware Integration Test Specification | 13 | 3: Architecture & Design | Software/Hardware Integration Test Report | 22 | 6: Integration |
| Software Component Test Specification | 16 | 4: Component Design | Software Component Test Report | 20 | 5: Implementation & Testing |

---

## 6. System-Level to Software-Level Traceability

System-level documents (Phase 0) are mandatory inputs to Phase 2 per EN 50128:2011 §7.2.2. Note that S2 (System Architecture Description) is a §7.2.2 input to the Requirements phase (and thus informs the SRS), but the SRS is then the sole normative input to the Architecture phase per §7.3.2 and §7.3.4.1. S2 is not a §7.3.2 normative input to the SAS.

| System Document (Phase 0) | Doc ID | Primary Software Document(s) | Standard Ref |
|---------------------------|--------|------------------------------|--------------|
| System Requirements Specification | S1 | Software Requirements Specification [6] | §7.2.2 |
| System Architecture Description | S2 | Software Requirements Specification [6] (via §7.2.2 inputs); informs SAS [9] contextually | §7.2.2 (normative for SRS); §7.3.4.1 (SAS based on SRS) |
| System Safety Plan | S3 | SQAP [1], SVP [4], SVaP [5] | §6.5.4.3, §6.2.4.2, §6.3.4.2, §6.3.4.3 |
| System Safety Requirements Specification | S4 | SRS [6] (safety req's section), SQAP [1] | §7.2.2 |

---

## 7. Phase Gate Enforcement (COD) and Traceability Checking (VER)

Per EN 50128:2011, **VER performs traceability completeness checking** at each phase, recording findings in the phase Verification Report (§6.5.4.14–6.5.4.17 applied per-phase via §6.2.4.11, §7.2.4.22, §7.3.4.42, §7.3.4.43, §7.4.4.13, §7.5.4.10, §7.6.4.13). **COD enforces the gate** by reading VER's report — COD does not itself verify traceability. COD blocks phase progression when VER has flagged traceability gaps.

```
╔═══════════════════════════════════════════════════════════════════════╗
║       VER Traceability Checking → COD Phase Gate Enforcement         ║
╚═══════════════════════════════════════════════════════════════════════╝

 ┌──────────┐   Track A (Development)                           ┌──────┐
 │          │──► PM orchestrates REQ/DES/IMP/INT/TST ──────────►│      │
 │   COD    │        ▼ QUA template check                       │ GATE │
 │(Lifecycle│   Track B (Independent V&V)                       │CHECK │
 │  Coord)  │──► VMGR coordinates VER ──────────────────────────►│      │
 │          │        ▼ VER checks traceability (per clauses      │PASS  │
 └──────────┘          below) → records in Verification Report  │  or  │
                      ▼ VMGR reviews and approves (SIL 3-4)     │BLOCK │
                      ▼ VMGR communicates V&V outcome to COD    └──────┘
                        (no hierarchical reporting relationship
                         — §5.1.2.10f; VMGR is independent)
      ▼
      COD reads VER Verification Report at gate check.
      COD BLOCKS if VER has flagged traceability gaps.

      Traceability checks performed by VER at each gate (per §6.5.4.14–6.5.4.17):
      ✓ [VER] Forward: all requirements traced to design/code/test
      ✓ [VER] Backward: all tests traced to requirements
      ✓ [VER] V&V reports reference correct deliverable baselines
      ✓ [VER] All 1st check (VER) sign-offs completed
      ✓ [CM]  Traceability is subject to configuration management (§6.5.4.15)
      ✓ [COD] All 2nd check (VAL) sign-offs completed (gate enforcement)

      Per-phase VER traceability checking clauses:
        Phase 1: §6.2.4.11(a)   — SVP meets §5.3.2.7–5.3.2.10, §6.5.4.14–6.5.4.17
        Phase 2: §7.2.4.22(b)   — SRS meets §5.3.2.7–5.3.2.10, §6.5.4.14–6.5.4.17
        Phase 3: §7.3.4.42(c–e) — SAS/SIS/SDS meet §5.3.2.7–5.3.2.10, §6.5.4.14–6.5.4.16
                 §7.3.4.43(a–b) — Integration Test Specs meet traceability requirements
        Phase 4: §7.4.4.13(b,d) — Component Design/Test Specs meet §5.3.2.7–5.3.2.10, §6.5.4.14–6.5.4.17
        Phase 5: §7.5.4.10(d)   — Source Code meets §5.3.2.7–5.3.2.10
        Phase 6: §7.6.4.13(b,d) — Integration Test Reports meet §5.3.2.7–5.3.2.10, §6.5.4.14–6.5.4.17

 Gate Commands:
   @cod gate-check planning              (Phase 1)
   @cod gate-check requirements          (Phase 2)
   @cod gate-check design                (Phase 3)
   @cod gate-check component-design      (Phase 4)
   @cod gate-check implementation-testing (Phase 5)
   @cod gate-check integration           (Phase 6)
   @cod gate-check validation            (Phase 7)
   @cod gate-check assessment            (Phase 8)
   @cod gate-check deployment            (Phase 9)
```

---

## 8. Role Independence Reference

Independence requirements directly affect traceability review authority — who may perform the 1st and 2nd checks on each deliverable.

| Role | SIL 0 | SIL 1 | SIL 2 | SIL 3-4 | Traceability Impact |
|------|-------|-------|-------|---------|---------------------|
| VER (Verifier) | Not required | Not required | HR | **Mandatory** (§5.1.2.10e) | Must be independent from authors of all documents VER checks |
| VAL (Validator) | Not required | Not required | HR | **Mandatory** (§5.1.2.10f) | Must be independent from all development roles |
| ASR (Assessor) | Exempt (§6.4.1.2) | **Mandatory** (§6.4.1.1) | **Mandatory** (§6.4.1.1) | **Mandatory** (§6.4.1.1) | Must be independent from project AND supplier (§5.1.2.5–5.1.2.7) |
| VMGR (V&V Manager) | N/A | N/A | N/A | **Mandatory** | Independent from COD and PM (§5.1.2.10f); manages VER team; provides final V&V approval; communicates outcomes to COD without hierarchical subordination |

> **IMPORTANT**: Assessment (ASR) is **mandatory for SIL 1 through SIL 4** per §6.4.1.1. The SIL 0 exemption under §6.4.1.2 applies only where an EN ISO 9001 certificate is held. SIL 1 is NOT exempt.

**Prohibited role combinations for SIL 3-4** (would compromise traceability review independence):

| Prohibited Combination | Reason |
|------------------------|--------|
| Designer/Implementer + Verifier | Cannot verify own work |
| Any development role + Validator | VAL must be independent |
| Any project role + Assessor | ASR must be independent from project |
| Implementer + Tester (own code) | Cannot test own implementation |

---

## 9. Normative Traceability Rules

The following rules are normatively required by EN 50128:2011. Each rule cites the specific clause that imposes the obligation.

| # | Rule | Scope | Standard Reference |
|---|------|-------|--------------------|
| T1 | All system requirements (S1) allocated to software must trace to SRS entries | S1 → [6] | §7.2.2 |
| T2 | All safety requirements (S4) must trace to identified safety requirements in SRS | S4 → [6] | §7.2.2 |
| T3 | All SRS requirements must trace to at least one architecture element in SAS | [6] → [9] | §7.3.4.2, §7.3.4.3 |
| T4 | All architecture elements in SAS must trace to SRS requirements | [9] → [6] | §7.3.4.2, §7.3.4.5 |
| T5a | All SDS design elements must trace to SAS architecture decisions | [10] → [9] | §7.3.4.20 |
| T5b | All SDS design elements must trace to SRS requirements | [10] → [6] | §7.3.4.20 |
| T5c | All SDS design elements must trace to Software Interface Specifications | [10] → [11] | §7.3.4.20 |
| T6 | All component design elements must trace to SDS | [15] → [10] | §7.4.4.1 |
| T7 | All source code modules must trace to component design specifications | [18] → [15] | §7.5.4.1 |
| T8 | All test cases in Overall SW Test Spec must trace to SRS requirements | [7] → [6] | §7.2.4.16, §7.2.4.19 |
| T9 | Every SRS requirement must have at least one test case in Overall SW Test Spec | [6] → [7] | §7.2.4.19 |
| T10a | SW Integration Test Spec test cases must trace to SRS, SAS, SDS, and Interface Specifications | [12] → [6],[9],[10],[11] | §7.3.4.29 |
| T10b | SW/HW Integration Test Spec test cases must trace to System Design Description (mapped to S1+S2 — see Phase 0 note and deviation D9), SRS, SAS, and SDS | [13] → S1+S2 (≡ System Design Description per §7.3.4.33 — see D9),[6],[9],[10] | §7.3.4.33 |
| T11 | All component test cases must trace to component design specifications | [16] → [15] | §7.4.4.7 |
| T12 | All test reports must reference specific test specification items | [20],[21],[22],[24] → [16],[12],[13],[7] | §7.5.4.5 ([20]), §7.6.4.3 ([21]), §7.6.4.7 ([22]), §7.7.4.1 ([24]) |
| T13 | Validation Report must confirm all SRS requirements are validated | [25] → [6] | §7.7.4.8(b) |
| T14 | Traceability is mandatory SIL 3-4; recommended SIL 0-2 (100% coverage required SIL 3-4) | All | §7.2, Table A.2 |
| T15 | VER checks traceability completeness per §6.5.4.14–6.5.4.17 at each phase; COD gate blocks phase progression if VER Verification Report flags traceability gaps | All gates | §6.5.4.14–6.5.4.17 (VER checking); §5.3.2.7 (COD enforcement) |

---

## 10. CCB Change Request Re-entry Traceability Impact

When a Change Request (CR) is approved by the CCB, all affected deliverables must be re-traced. COD marks impacted phases as "re-entry-required"; VER re-checks traceability completeness for all downstream links and records findings in updated Verification Reports before COD re-runs the gate check.

> **Note**: At SIL 3-4, all re-entries must be authorized by CCB per §9.2.4.2. COD blocks phase progression until CCB authorization is documented.

| CR Scope | Earliest Re-entry Phase | Affected Traceability Links |
|----------|------------------------|-----------------------------|
| System requirements (S1/S4) | Phase 2 (Requirements) | T1–T15 (all) |
| Software requirements | Phase 2 (Requirements) | T3–T15 |
| Architecture/Design | Phase 3 (Architecture & Design) | T5a–T5c, T6–T15 |
| Component Design | Phase 4 (Component Design) | T6–T15 |
| Source code / unit tests | Phase 5 (Implementation & Testing) | T7–T12 |
| Integration | Phase 6 (Integration) | T10a, T10b, T11–T13 |

---

## 11. Document Traceability Matrix (Summary)

| Doc# | Document Name | Phase | Traces FROM | Traces TO |
|------|--------------|-------|-------------|-----------|
| S1 | System Requirements Specification | 0 | Customer/System | [6] SRS |
| S2 | System Architecture Description | 0 | Customer/System | [6] SRS (via §7.2.2); [9] SAS (informative/contextual only — not §7.3.2 normative) |
| S3 | System Safety Plan | 0 | Customer/System | [1] SQAP, [4] SVP, [5] SVaP |
| S4 | System Safety Requirements Spec | 0 | Customer/Hazard Analysis | [6] SRS (safety req's) |
| 1 | Software Quality Assurance Plan | 1 | S3, S4 | All phases (enforces quality) |
| 3 | Software Configuration Management Plan | 1 | — | All phases (controls baselines) |
| 4 | Software Verification Plan | 1 | S3 | [2],[8],[14],[17],[19],[23],[40],[44] |
| 5 | Software Validation Plan | 1 | S3 | [25],[26] |
| 6 | Software Requirements Specification | 2 | S1, S4 | [7],[8],[9] |
| 7 | Overall Software Test Specification | 2 | [6] SRS | [24] Overall Software Test Report |
| 8 | Software Requirements Verification Report | 2 | [6] SRS | COD gate |
| 9 | Software Architecture Specification | 3 | [6] SRS (normative; §7.3.4.1); S2 (informative only) | [10],[11],[14] |
| 10 | Software Design Specification | 3 | [9] SAS, [6] SRS, [11] Interface Specs (all normative per §7.3.4.20) | [15],[17] |
| 11 | Software Interface Specifications | 3 | [9] SAS | [12],[13],[21],[22] |
| 12 | Software Integration Test Specification | 3 | [6] SRS, [9] SAS, [10] SDS, [11] Interface Specs (normative per §7.3.4.29) | [21] Software Integration Test Report |
| 13 | Software/Hardware Integration Test Specification | 3 | System Design Description (mapped to S1+S2 — see §7.3.4.33 note in Phase 0 and deviation D9), [6] SRS, [9] SAS, [10] SDS (normative per §7.3.4.33) | [22] SW/HW Integration Test Report |
| 14 | Software Architecture and Design Verification Report | 3 | [9],[10],[11] | COD gate |
| 15 | Software Component Design Specification | 4 | [10] SDS | [16],[17],[18] |
| 16 | Software Component Test Specification | 4 | [15] | [20] Software Component Test Report |
| 17 | Software Component Design Verification Report | 4 | [15] | COD gate |
| 18 | Software Source Code and Supporting Documentation | 5 | [15] | [19],[20],[21],[22],[24] |
| 19 | Software Source Code Verification Report | 5 | [18] | COD gate |
| 20 | Software Component Test Report | 5 | [16],[18] | [23],[24] |
| 21 | Software Integration Test Report | 6 | [12],[18] | [23],[24] |
| 22 | Software/Hardware Integration Test Report | 6 | [13],[18] | [23],[24] |
| 23 | Software Integration Verification Report | 7 | [21],[22],[20] | [25] |
| 24 | Overall Software Test Report | 7 | [7],[20],[21],[22] | [25] |
| 25 | Software Validation Report | 7 | [23],[24],[6] | [46] Software Assessment Report |
| 26 | Tools Validation Report | 7 | Tools used | [46] Software Assessment Report |
| 27 | Release Note | 7 | [25] | [36],[38] |
| 45 | Software Assessment Plan | 8 | [1] SQAP | [46] |
| 46 | Software Assessment Report | 8 | All prior docs | [36] Software Release and Deployment Plan |
| 36 | Software Release and Deployment Plan | 9 | [46],[27] | [39],[40] |
| 37 | Software Deployment Manual | 9 | [18],[36] | [39] |
| 38 | Release Notes | 9 | [36],[27] | [39] |
| 39 | Deployment Records | 9 | [36],[37],[38] | [41] Software Maintenance Plan |
| 40 | Deployment Verification Report | 9 | [36],[39] | COD gate |
| 41 | Software Maintenance Plan | 10 | [39] | [42],[43],[44] |
| 42 | Software Change Records | 10 | CCB CR | [43],[44] |
| 43 | Software Maintenance Records | 10 | [42] | [44] |
| 44 | Software Maintenance Verification Report | 10 | [41],[42],[43] | COD (re-entry gate) |

---

## 12. Platform Deviations from Annex C Table C.1

The following are documented platform deviations from the informative Annex C Table C.1 phase-column assignments or authorship assignments. **Each must be documented in the project SQAP and is subject to Safety Authority review.**

| ID | Doc# | Document Name | Annex C Position | Platform Assignment | Normative Justification |
|----|------|--------------|-----------------|---------------------|------------------------|
| D1 | 5 | Software Validation Plan | Requirements phase (Phase 2) | Phase 1: Planning | §6.3.4.3 ("written on the basis of input documents" — system docs available at project start); §5.3.2.4 ("plans shall be drawn up at the start of the project"). Validation planning must precede requirements elaboration to establish acceptance criteria. |
| D2 | 20 | Software Component Test Report | Integration phase (Phase 6) | Phase 5: Implementation & Testing | §7.5.4.5 normative production clause ("A Software Component Test Report shall be written"). Integration testing presupposes prior unit-test completion. The Annex C placement in the "Integration" phase column is an internal inconsistency in the standard (cf. Table A.1 which associates this document with "Component Implementation and Testing"). |
| D3 | 40 | Deployment Verification Report | Maintenance phase (Phase 10) | Phase 9: Deployment | §9.1 (normative deployment clause) — deployment must be verified before maintenance begins. |
| D4 | 44 | Software Maintenance Verification Report | Assessment phase (Phase 8) | Phase 10: Maintenance | §9.2 (normative maintenance clause) — maintenance activities generate the verification report. |
| D5 | 23 | Software Integration Verification Report | Phase 7 per Annex C | Normative production clause is §7.6.4.11 (Integration phase); platform places it in Phase 7 consistent with informative Annex C Table C.1. The normative vs. informative tension must be noted. Assessors SHALL apply §7.6.4.11 requirements (not §7.7) to this document's content. |
| D6 | 19 | Software Source Code Verification Report | 2nd Check: blank per Annex C Table C.1 | Platform default: blank (consistent with Annex C). If the project SQAP assigns VAL as 2nd check, this constitutes a project addition beyond Annex C requirements; it must be explicitly stated in the SQAP. |
| D7 | 44 | Software Maintenance Verification Report | 2nd Check: per Annex C Table C.1 | 2nd Check (VAL) assigned in this platform. Verify against printed Annex C Table C.1. If the printed standard shows blank, document as a deliberate project addition in the SQAP. |
| D8 | 1 | Software Quality Assurance Plan | Written by: blank (Annex C); §6.5.4.3: "under responsibility of Verifier" | QUA authors under VER direction and responsibility. The SQAP must document this role split: VER holds normative §6.5.4.3 responsibility; QUA may perform the authoring. |
| D9 | 13 | Software/Hardware Integration Test Specification | §7.3.4.33 requires a "System Design Description" as normative input | This platform has no standalone "System Design Description" document. The term is mapped to S1 (System Requirements Specification) + S2 (System Architecture Description) as joint inputs (see Section 11, doc 13 and Phase 0 note in Diagram 2). The SQAP must document this mapping and the Safety Authority must confirm it is adequate for the project context. |

---

*Document generated from: `LIFECYCLE.md` v1.9, `DELIVERABLES.md`, `WORKFLOW.md`, `AGENTS.md`*  
*EN 50128:2011 — Railway Applications — Communication, Signalling and Processing Systems — Software for Railway Control and Protection Systems*
