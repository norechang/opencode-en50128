# Safety Engineering Activities — EN 50128 Lifecycle Reference

> **Standard**: EN 50128:2011 Railway Software Standard  
> **Scope**: SAF (Safety Engineer) role across the EN 50128 V-Model software lifecycle.  
> Covers: phase activities, cross-cutting artifacts, deliverable ownership, hazard-to-validation
> traceability chain, and Table A.8 software analysis technique matrix.  
> **Version**: 1.0  
> **Date**: 2026-03-24  
> **References**: `TRACEABILITY.md`, `DELIVERABLES.md`, `WORKFLOW.md`, `AGENTS.md`,
> `LIFECYCLE.md`, `ORGANIZATION.md`,
> `std/EN50128-2011.md` §6.3, §7.1, §7.2, Table A.8,
> `std/EN 50126-1-2017.md` §6.3, `std/EN 50126-2-2017.md` §10

---

## Terminology Notes

**Phase numbering convention**: This document uses EN 50128 platform phase numbers (1–10)
throughout. EN 50126 defines a separate 12-phase system lifecycle (Phase 1 Concept through
Phase 12 Decommissioning). Where EN 50126 phases are referenced they are always qualified
explicitly as **EN 50126 Phase N**. An unqualified "Phase N" in this document always means
an EN 50128 software lifecycle phase.

Before reading the diagrams, note these critical distinctions:

| Term | Source | Position in this lifecycle |
|------|--------|---------------------------|
| **EN 50128 phases 1–10** | EN 50128 platform lifecycle (`LIFECYCLE.md`) | Planning (1) → Requirements (2) → Design (3) → Component Design (4) → Implementation (5) → Integration (6) → Validation (7) → Assessment (8) → Deployment (9) → Maintenance (10) |
| **Phase 0** | Platform extension (not in EN 50128 or EN 50126) | Convenience label for pre-software system-level inputs that arrive from the EN 50126 system lifecycle. No normative phase number in either standard. |
| **EN 50126 lifecycle phases** | EN 50126-1:2017 §6.1, 12 phases | Concept (1) → … → Risk Analysis (3) → System Requirements (4) → Architecture (5) → … → System Validation (9) → … — **distinct numbering from EN 50128** |
| **Hazard Log** | SAF cross-cutting artifact | Created EN 50128 Phase 2, updated EN 50128 Phases 3 and 7; NOT an Annex C item |
| **System Safety Requirements Specification (S4)** | EN 50126 system-level output | Phase 0 input (platform convention); produced from EN 50126 RAMS analysis, not by SAF |
| **Safety Requirements in SRS** | EN 50128 §7.2.4.13 | REQ-SAFE-xxx entries in Annex C item 6 (SRS); SAF derives, REQ records |
| **Table A.8** | EN 50128 §6.3 | **Software** analysis techniques (5 entries: Static, Dynamic, CCD, ETA, SEEA) |
| **FMEA / FTA / HAZOP** | EN 50126 + D.27/D.30/D.32 | System-level techniques applied **in support of** software via EN 50128 §7.1 — NOT in Table A.8 |
| **Safety Case** | EN 50129 | Not an EN 50128 Annex C deliverable; no platform lifecycle item |

---

## Section 1 — SAF Activity Map Across the V-Model

SAF has **no primary Annex C deliverable**. Its outputs are cross-cutting artifacts
(Hazard Log, FMEA/FTA reports) that support Annex C items owned by REQ, DES, TST, VAL.
SAF appears in TRACEABILITY.md Diagram 3 as a cross-cutting role alongside VER, QUA, and CM.

```
╔══════════════════════════════════════════════════════════════════════════════════════════╗
║         SAF Activity Map — EN 50128 V-Model (Phase 0 [platform ext.], Phases 1–10)      ║
╚══════════════════════════════════════════════════════════════════════════════════════════╝

Phase 0 — SYSTEM LEVEL INPUTS  [platform extension — not an EN 50128 or EN 50126 phase]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 S3  System Safety Plan                    ──► feeds EN 50128 Phase 1 SQAP, SVP, SVaP
 S4  System Safety Requirements Spec       ──► feeds EN 50128 Phase 2 SRS (§7.2.2 normative input)

 SAF ACTIVITY: None. S3 and S4 are outputs of the EN 50126 system lifecycle RAMS analysis.
               SAF consumes S4 as input in EN 50128 Phase 2.

 ─────────────────────────────────────────────────────────────────────────────────────────
Phase 1 — PLANNING (§5, §6.5, §6.6)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 SAF ACTIVITY: None as primary. SAF reviews SQAP to confirm safety analysis
               activities are planned and Table A.8 technique selection is
               recorded. SAF coordinates with PM on hazard analysis schedule.

 ─────────────────────────────────────────────────────────────────────────────────────────
Phase 2 — REQUIREMENTS (§7.2)              ◄── PRIMARY SAF ENGAGEMENT
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 Trigger:    PM assigns SAF parallel with REQ; both start from S4 and S1.
 Input:      S4 (System Safety Requirements Specification), S1 (System Requirements Spec)
 Activity:   a) Hazard identification — identify software-relevant hazards from S4
             b) Preliminary risk assessment — severity × frequency → risk level
             c) SIL assignment — tolerable hazard rates per EN 50126-2 Table 8
             d) Safety requirements derivation — produce REQ-SAFE-xxx entries
             e) Coordinate with REQ — safety requirements recorded in SRS (§7.2.4.13)
             f) Software Error Effect Analysis (SEEA) — Table A.8 entry 5 (HR SIL 3–4)
 Output:     Hazard Log (cross-cutting artifact; subject to CM version control per §6.6)
             REQ-SAFE-xxx requirements (embedded in SRS — Annex C item 6; author: REQ+SAF)
 Clause:     §7.2.4.13 (safety function identification), §7.2.4.3 (SIL derivation)

 ─────────────────────────────────────────────────────────────────────────────────────────
Phase 3 — ARCHITECTURE AND DESIGN (§7.3)   ◄── SECONDARY SAF ENGAGEMENT
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 Trigger:    PM assigns SAF after SDS draft is available (parallel with DES review).
 Input:      SRS (with REQ-SAFE-xxx), SAS, SDS (draft)
 Activity:   a) FMEA on software architecture — failure mode analysis of key modules
                (system-level technique from EN 50126/D.27, applied via §7.1)
             b) FTA for critical hazards (severity ≥ 8) — top-down causal analysis
                (system-level technique from EN 50126/D.30, applied via §7.1)
             c) Verify design addresses all safety requirements from SRS
             d) Update Hazard Log with design-phase findings (new failure modes, mitigations)
             e) Static Software Analysis on architecture — Table A.8 entry 1 (HR SIL 1–4)
 Output:     Updated Hazard Log
             FMEA Report (cross-cutting artifact; CM-controlled per §6.6)
             FTA Report (cross-cutting artifact; CM-controlled per §6.6)
             Input to SAS review: safety-relevant architecture decisions (Annex C item 9;
             TRACEABILITY.md Diagram 3: SAS authored by DES + SAF)
 Clause:     §7.3.4.2 (architecture basis), Table A.8 (technique selection)

 ─────────────────────────────────────────────────────────────────────────────────────────
Phase 4 — COMPONENT DESIGN (§7.4)
Phase 5 — IMPLEMENTATION AND TESTING (§7.5)
Phase 6 — INTEGRATION (§7.6)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 SAF ACTIVITY: Monitoring / advisory only.
               SAF reviews outputs for new safety implications but produces no primary
               artifact. IMP and TST apply safety requirements through MISRA C compliance,
               defensive programming, and safety-tagged test cases (REQ-SAFE-xxx coverage).
               SAF escalates newly identified hazards to PM for CCB evaluation.

 ─────────────────────────────────────────────────────────────────────────────────────────
Phase 7 — VALIDATION (§7.7)                ◄── CONFIRMATION ACTIVITY
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 Trigger:    PM assigns SAF to support VAL's independence check.
 Input:      Software Validation Report (draft), Hazard Log (current baseline)
 Activity:   a) Confirm all REQ-SAFE-xxx requirements are covered by test evidence
             b) Confirm all Hazard Log items reach CLOSED or ACCEPTED-RESIDUAL status
             c) Confirm safety case evidence is consistent with validation results
             d) Report to PM: any unclosed hazard blocks Validation Report sign-off
 Output:     Safety confirmation (input to VAL for Validation Report §7.7.4.8(b))
             Final Hazard Log baseline
 Clause:     §7.7.4.8(b) (validation shall confirm safety requirements met), T13

 ─────────────────────────────────────────────────────────────────────────────────────────
Phase 8 — ASSESSMENT (§6.4)
━━━━━━━━━━━━━━━━━━━━━━━━━━
 SAF ACTIVITY: Evidence provision only.
               The INDEPENDENT ASSESSOR (ASR) — not SAF — performs assessment (§6.4.4.1).
               ASR is mandatory SIL 1–4 per §6.4.1.1 and must be independent from project
               AND supplier (§5.1.2.5–5.1.2.7). SAF provides:
                 - Hazard Log final baseline
                 - FMEA/FTA reports
                 - Safety requirements coverage evidence
               ASR independently evaluates all lifecycle evidence. SAF does NOT review
               or contribute to the Software Assessment Plan (item 45) or
               Software Assessment Report (item 46).

 ─────────────────────────────────────────────────────────────────────────────────────────
Phase 9 — DEPLOYMENT (§9.1)
Phase 10 — MAINTENANCE (§9.2)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 SAF ACTIVITY: CCB-triggered only.
               If a CCB change request affects safety requirements or SIL assignment,
               SAF re-engages to update the Hazard Log and re-derive safety requirements.
               Entry point: Phase 2 (if SIL changes) or Phase 3 (if design change only).
               §6.6.4.2: all changes shall initiate return to an appropriate lifecycle phase.

 ─────────────────────────────────────────────────────────────────────────────────────────
CROSS-CUTTING (all phases)
━━━━━━━━━━━━━━━━━━━━━━━━━━
 SAF: Hazard/safety analysis updates  (TRACEABILITY.md Diagram 3, cross-cutting row)
 VER: Ongoing verification activities
 QUA: Ongoing audits / template checks
 CM:  Configuration management / baselines (including Hazard Log versioning)
```

---

## Section 2 — SAF Deliverables and Annex C Position

EN 50128:2011 Annex C Table C.1 defines 46 standard deliverables. SAF has **no entry** in the
"Written by" column of Annex C — SAF outputs are cross-cutting artifacts outside the Annex C
catalogue.

```
╔══════════════════════════════════════════════════════════════════════════════════════════╗
║       SAF Artifacts vs. Annex C Deliverables — Ownership and Review Chain               ║
╚══════════════════════════════════════════════════════════════════════════════════════════╝

 ── Cross-cutting Artifacts (SAF-owned; outside Annex C Table C.1) ───────────────────────

 Artifact               Phase Created  Phase Updated  Baseline Owner  Reviewed By
 ─────────────────────────────────────────────────────────────────────────────────────────
 Hazard Log             Phase 2        Phases 3, 7    CM (§6.6)       VER (1st), VAL (2nd)
   Note: Living document. Closed at end of Phase 7 validation. CM controls versioning
         per §6.6. Content: HAZ-xxx entries with severity, frequency, SIL assignment,
         mitigation, residual risk, and link to REQ-SAFE-xxx requirements.

 FMEA Report(s)         Phase 3        Phase 3        CM (§6.6)       VER (1st), VAL (2nd)
   Note: Bottom-up failure analysis. One report per major subsystem or module group.
         Content: failure modes, effects, severity (1–10), occurrence, detection, RPN,
         mitigation actions.

 FTA Report(s)          Phase 3        Phase 3        CM (§6.6)       VER (1st), VAL (2nd)
    Note: Top-down causal analysis for hazards with severity ≥ 8 (Catastrophic/Critical).
          CCF analysis section is HR (Highly Recommended) SIL 3–4 per EN 50126-2:2017 Table F.2
          (item 11). Table A.8 does NOT contain a CCF entry; EN 50126 governs CCF at system level.
          EN 50126-1 Section 6.3 governs system-level quantitative FTA.

 ── Annex C Items Where SAF CONTRIBUTES (not primary author) ────────────────────────────

 Item  Document Name                        Phase  Primary Author  SAF Contribution
 ─────────────────────────────────────────────────────────────────────────────────────────
  6    Software Requirements Specification   2      REQ             Derives REQ-SAFE-xxx
                                                                    safety requirements;
                                                                    SIL levels recorded
                                                                    per §7.2.4.3
                                                    TRACEABILITY.md Diagram 3:
                                                    "Author: REQ + SAF" (Phase 2, item 6)

  9    Software Architecture Specification   3      DES             Reviews architecture
                                                                    against safety reqs;
                                                                    FMEA/FTA findings feed
                                                                    SAS safety section
                                                    TRACEABILITY.md Diagram 3:
                                                    "Author: DES + SAF" (Phase 3, item 9)

 25    Software Validation Report            7      VAL             SAF confirmation that
                                                                    all hazards closed
                                                                    (§7.7.4.8(b))

 ── What SAF Does NOT Own ──────────────────────────────────────────────────────────────

 "Safety Case": This is an EN 50129 concept (Safety Related Electronic Systems for
 Signalling). EN 50128:2011 Annex C contains no "Safety Case" item. EN 50128 §6.3 requires
 software analysis and §7.7 requires validation; the safety argument is assembled by VAL in
 the Software Validation Report (item 25). If a project requires a formal Safety Case per
 EN 50129, it is produced under EN 50129 governance, not EN 50128 Annex C governance.

 Software Assessment Plan (item 45) and Software Assessment Report (item 46): owned
 entirely by the independent Assessor (ASR). SAF has zero authorship or review role.
```

---

## Section 3 — Hazard-to-Validation Traceability Chain

This diagram shows the complete forward traceability chain for safety-tagged artifacts, from
system-level hazard identification through to assessment. Traceability rules (T1–T15) are
from TRACEABILITY.md §9.

```
╔══════════════════════════════════════════════════════════════════════════════════════════╗
║      Hazard-to-Validation Traceability Chain (EN 50128 Safety Thread)                   ║
╚══════════════════════════════════════════════════════════════════════════════════════════╝

SYSTEM LEVEL (Phase 0 [platform ext.] — EN 50126 system lifecycle outputs)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

 EN 50126 RAMS Analysis
  │  (System-level FMEA, FTA, HAZOP at system level per EN 50126-1 §6.3)
  ▼
 S4: System Safety Requirements Specification
  │  (Tolerable Hazard Rates per SIL; EN 50126-2 Table 8)
  │
  └──────────────────────────────────────────────────────────────────────┐
                                                                         │
PHASE 2 — REQUIREMENTS (§7.2)                                            │
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                                            │
 SAF: Initial hazard analysis    ◄── S4 (normative per §7.2.2) ◄────────┘
  │
  ├──► Hazard Log (HAZ-xxx entries)                  [cross-cutting; CM-controlled]
  │      │  severity, frequency, SIL assignment, mitigation, residual risk
  │      │
  │      └──► T2: each hazard must trace to a safety requirement in SRS
  │
  └──► REQ-SAFE-xxx derived safety requirements
         │  (SAF derives; REQ records in SRS §7.2.4.13)
         ▼
        SRS [item 6]  ◄── T1 (all S1 system reqs → SRS)
          │            ◄── T2 (all S4 safety reqs → SRS REQ-SAFE-xxx entries)
          │
          ▼
        VER: Software Requirements Verification Report [item 8]
          │  (checks SRS completeness including safety req's per §7.2.4.22)
          │  (checks traceability T1, T2, T9 per §6.5.4.14–6.5.4.17)
          │

PHASE 3 — ARCHITECTURE AND DESIGN (§7.3)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 SAF: FMEA / FTA on software architecture    ◄── SRS REQ-SAFE-xxx, SDS
  │
  ├──► FMEA Report (software-level failure mode analysis; Table A.8 / EN 50126)
  │      │  feeds SAS safety mechanisms section
  │
  ├──► FTA Report (top-down causal analysis for critical hazards)
   │      │  CCF Analysis section (HR SIL 3–4 per EN 50126-2:2017 Table F.2)
  │
  └──► Updated Hazard Log (new failure modes, mitigations, SIL confirmation)
         │
         ▼
        SAS [item 9]  ◄── T3 (SRS reqs → architecture elements)
          │  (safety architecture: redundancy, safe states, fault detection)
          │  ◄── T4 (architecture elements → SRS reqs, including REQ-SAFE-xxx)
          │
          ▼
        SDS [item 10] ◄── T5a (design elements → architecture)
          │            ◄── T5b (design elements → SRS reqs)
          │

PHASE 4–5 — COMPONENT DESIGN + IMPLEMENTATION (§7.4, §7.5)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 (SAF: monitoring / advisory only)
          │
          ▼
        Source Code [item 18]  ◄── T7 (code → component design spec)
          │  MISRA C:2012 (mandatory SIL 2+); defensive programming
          │  Safety-tagged functions identified per §7.2.4.13
          │
          ▼
        Software Component Test Report [item 20]
          │  REQ-SAFE-xxx test cases must exist (T8, T9 from Overall SW Test Spec)
          │

PHASE 6 — INTEGRATION (§7.6)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 (SAF: monitoring / advisory only)
          │
          ▼
        SW Integration Test Report [item 21]   ◄── T10a (traces to SRS, SAS, SDS, Interfaces)
        SW/HW Integration Test Report [item 22] ◄── T10b (traces to System Design Desc, SRS)
          │  Safety functions tested end-to-end under operational conditions
          │

PHASE 7 — VALIDATION (§7.7)
━━━━━━━━━━━━━━━━━━━━━━━━━━━
 SAF: confirms all HAZ-xxx entries closed; all REQ-SAFE-xxx covered by test evidence
          │
          ▼
        Overall SW Test Report [item 24]  ◄── T12 (traces to Overall SW Test Spec [item 7])
          │  All REQ-SAFE-xxx test cases must appear with PASS result
          │
          ▼
        Software Validation Report [item 25]
          │  §7.7.4.8(b): "validation shall demonstrate all safety requirements are met"
          │  ◄── T13 (validation report confirms all SRS reqs including REQ-SAFE-xxx)
          │

PHASE 8 — ASSESSMENT (§6.4) — INDEPENDENT
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
          │
          ▼
        ASR reviews entire safety evidence chain:
          Hazard Log ──► REQ-SAFE-xxx ──► Architecture ──► Code ──► Tests ──► Validation
          │  ASR independent from project AND supplier (§5.1.2.5–5.1.2.7)
          │  Mandatory SIL 1–4 (§6.4.1.1); SIL 0 exempt per §6.4.1.2
          ▼
        Software Assessment Report [item 46]
          │  §6.4.4.8: "software is fit for its intended purpose and safety integrity level"
          │

          ▼  (Assessment pass)

PHASE 9 — DEPLOYMENT
━━━━━━━━━━━━━━━━━━━━
        Software Release and Deployment Plan [item 36]
          │  Safety-critical software released only after Validator authorisation (§6.3.4.16);
          │  ASR fitness assessment complete (§6.4.4.8)
          │

BACKWARD TRACEABILITY (all links are reversible per §5.3.2.7)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 Software Validation Report [25]  ◄── Overall SW Test Report [24]
 Overall SW Test Report [24]      ◄── Integration Test Reports [21, 22]
 Integration Test Reports         ◄── Source Code [18] + Component Tests [20]
 Source Code [18]                 ◄── Component Design Spec [15]
 Component Design Spec [15]       ◄── SDS [10]
 SDS [10]                         ◄── SAS [9]
 SAS [9]                          ◄── SRS REQ-SAFE-xxx [6]
 SRS REQ-SAFE-xxx [6]             ◄── S4 System Safety Requirements Specification
 S4                               ◄── EN 50126 RAMS Hazard Analysis

 Traceability rules T1–T15 checked by VER at each phase gate per §6.5.4.14–6.5.4.17.
 COD blocks phase progression when VER flags gaps (TRACEABILITY.md §7).
```

---

## Section 4 — EN 50128 Table A.8: Software Analysis Technique Matrix

Table A.8 (§6.3) defines **software** analysis techniques. These are **distinct from**
system-level FMEA/FTA/HAZOP (which are EN 50126 techniques applied via §7.1 in support
of software but not listed in Table A.8 itself).

```
╔══════════════════════════════════════════════════════════════════════════════════════════╗
║      EN 50128:2011 Table A.8 — Software Analysis Techniques (§6.3)                      ║
╚══════════════════════════════════════════════════════════════════════════════════════════╝

 Source: EN 50128:2011 §6.3, Table A.8
 Normative note: "One or more of these techniques shall be selected to satisfy the
                 Software Safety Integrity Level being addressed."

 ─────────────────────────────────────────────────────────────────────────────────────────
 #   Technique / Measure                  Ref        SIL 0  SIL 1  SIL 2  SIL 3  SIL 4
 ─────────────────────────────────────────────────────────────────────────────────────────
 1   Static Software Analysis             D.13       R      HR     HR     HR     HR
                                          D.37
                                          Table A.19

 2   Dynamic Software Analysis            Table A.13  -      R      R      HR     HR
                                          Table A.14

 3   Cause Consequence Diagrams           D.6         R      R      R      R      R

 4   Event Tree Analysis                  D.22        -      R      R      R      R

 5   Software Error Effect Analysis       D.25        -      R      R      HR     HR
     (SEEA)
 ─────────────────────────────────────────────────────────────────────────────────────────
 Legend: M = Mandatory  HR = Highly Recommended  R = Recommended  - = No recommendation
 ─────────────────────────────────────────────────────────────────────────────────────────

Notes:
 (a) Table A.8 has exactly 5 techniques. Common Cause Failure Analysis (CCF), FMEA, FTA,
     and HAZOP do NOT appear in Table A.8. They are system-level techniques referenced in
     EN 50126 and applied to software per §7.1 (software safety requirements specification).
     See the companion table below for the EN 50126-derived techniques.

 (b) Static Software Analysis (entry 1) covers: MISRA C compliance checking, control flow
     analysis, data flow analysis, cyclomatic complexity, dead code detection.
     Tool references: Table A.19 (static analysis sub-techniques).

 (c) Dynamic Software Analysis (entry 2) covers: execution profiling, memory analysis,
     timing analysis, runtime fault injection. Tool references: Table A.13 (dynamic testing
     methods), Table A.14 (functional/black-box testing).

 (d) Software Error Effect Analysis (SEEA, entry 5) is software-specific: analyse the
     effects on the software system of each software component fault. Analogous to FMEA
     but scoped to software failure modes (NULL pointer, overflow, state machine stuck-at,
     uninitialized variable, etc.). HR at SIL 3–4.
```

### Table A.8 vs. System-Level Analysis Techniques (EN 50126)

The following techniques are **NOT in Table A.8** but are commonly used in railway safety
engineering and applied *in support of* software analysis via §7.1:

```
 ─────────────────────────────────────────────────────────────────────────────────────────
 Technique                           Source         Applicability to Software
 ─────────────────────────────────────────────────────────────────────────────────────────
  Failure Mode and Effects Analysis   EN 50126        Applied at software level (EN 50128 Phase 3)
  (FMEA)                              D.27            per §7.1; informs SAS/SDS safety
                                     IEC 60812       sections. HR SIL 2; HR SIL 3–4
                                                     per EN 50126 risk tables.

  Fault Tree Analysis (FTA)           EN 50126        Top-down analysis of critical hazards
                                     D.30            (severity ≥ 8). CCF analysis is a
                                     IEC 61025       HR sub-activity SIL 3–4 per
                                                     EN 50126-2:2017 Table F.2.
                                                     HR SIL 2; HR SIL 3–4.

 Hazard and Operability Study        EN 50126        HAZOP at software interfaces / data
 (HAZOP)                             D.32            streams. HR SIL 2; HR SIL 3–4.

  Common Cause Failure Analysis       EN 50126        HR SIL 3–4 per EN 50126-2:2017 Table F.2.
  (CCF)                               D.9 / D.11      Must be included in FTA scope.
                                                     Typically addresses: common design
                                                     faults, shared hardware platform,
                                                     common power supply, EMI.

 Markov Analysis                     EN 50126        Quantitative availability / reliability
                                                     modelling. R SIL 2; R SIL 3–4.
 ─────────────────────────────────────────────────────────────────────────────────────────
 Note: The SIL recommendation levels above are from EN 50126 RAMS tables, not Table A.8.
       When cited in an EN 50128 project SQAP, they must be attributed to EN 50126 and
       applied via the §7.1 gateway ("software safety requirements based on RAMS analysis").
```

---

## Section 5 — SAF Role: Independence and Boundaries

```
╔══════════════════════════════════════════════════════════════════════════════════════════╗
║       SAF Independence Requirements and Prohibited Boundaries                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════╝

 Role        Independence Required?   Basis
 ─────────────────────────────────────────────────────────────────────────────────────────
 SAF         No                       EN 50128 has no §5.1.2 independence clause for SAF.
                                      SAF may be part of the development team at all SILs.

 VER         HR SIL 2; M SIL 3–4     §5.1.2.10i — shall not be Requirements Manager,
                                      Designer, Implementer, Integrator, Tester, or Validator

 VAL         HR SIL 2; M SIL 3–4     §5.1.2.10f — independent from all development roles

 ASR         M SIL 1–4               §6.4.1.1, §5.1.2.5–5.1.2.7 — independent from
             (SIL 0: exempt §6.4.1.2) project AND supplier. ASR ≠ SAF. SAF cannot be ASR.

 ─────────────────────────────────────────────────────────────────────────────────────────
  SAF boundaries:

   ┌──────────────────────────────────────────────────────────────────────────────────────┐
   │  ALLOWED: SAF + REQ   (SAF derives safety reqs; REQ records in SRS — §7.2.4.13)    │
   │  ALLOWED: SAF + DES   (SAF reviews design for safety compliance — EN 50128 Phase 3) │
   │  ALLOWED: SAF + PM    (SAF provides hazard status for gate checks)                  │
   │                                                                                      │
   │  BOUNDARY: SAF provides evidence to ASR but CANNOT be the assessor (§6.4.4.1)      │
   │  BOUNDARY: SAF does not perform independent verification (VER role — §6.2)          │
   │  BOUNDARY: SAF does not perform validation sign-off (VAL role — §6.3)               │
   └──────────────────────────────────────────────────────────────────────────────────────┘

  Note: EN 50128:2011 specifies independence requirements only for VER, VAL, and ASR
  (ORGANIZATION.md independence matrix). No independence clause in §5.1.2 applies to SAF.
  Any project document claiming "SAF + REQ prohibited SIL 3–4" or similar has no normative
  basis. SAF may collaborate freely with REQ and DES at all SIL levels.
```


*Grounded in: `TRACEABILITY.md`, `DELIVERABLES.md`, `ORGANIZATION.md`, `WORKFLOW.md`,
`LIFECYCLE.md`, `AGENTS.md`,
`std/EN50128-2011.md` §6.3 Table A.8, §7.1, §7.2.4.13, §7.7.4.8,
`std/EN 50126-1-2017.md` §6.3, `std/EN 50126-2-2017.md` §10.*  
*EN 50128:2011 — Railway Applications — Communication, Signalling and Processing Systems —
Software for Railway Control and Protection Systems*
