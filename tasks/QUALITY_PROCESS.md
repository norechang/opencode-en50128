# EN 50128 Quality Assurance Process — Workflow, Deliverable Touchpoints, and SIL Obligations

> **Document**: `tasks/QUALITY_PROCESS.md`  
> **Standard**: EN 50128:2011 Railway Software Standard  
> **Scope**: QUA role across all lifecycle phases — tasks, triggers, outputs, deliverable touchpoints, two-track position, SIL-tiered obligations  
> **Normative Basis**: §6.5 (Software Quality Assurance), Table A.9, §6.5.4.3, §6.5.4.14–17  
> **Date**: 2026-03-24  
> **References**: `WORKFLOW.md`, `DELIVERABLES.md`, `LIFECYCLE.md`, `ORGANIZATION.md`, `TRACEABILITY.md`, `AGENTS.md`

---

## Index

| # | Diagram | Content |
|---|---------|---------|
| [1](#diagram-1) | QUA Tasks Across the V-Model Lifecycle | Per-phase activity, trigger, and output |
| [2](#diagram-2) | QUA Touchpoints on All Annex C Deliverables | Which of the 46 items QUA checks, and how |
| [3](#diagram-3) | QUA in the Two-Track Workflow | Track A gate-keeper and Track B report check |
| [4](#diagram-4) | Table A.9 SIL-Tiered Obligations | Techniques M/HR/R by SIL, mapped to phases |

---

## Key Definitions

**QUA template compliance check**: QUA reviews a deliverable for format and structure correctness
(Document ID format, Document Control table, Approvals table, required sections present, SIL-appropriate
approvers). QUA checks FORMAT — not technical content. Technical content review is performed by VER
(1st Check column, DELIVERABLES.md) after QUA accepts the document.

**1-Pass Rule**: Applies to VER/VAL reports only. If QUA rejects a VER or VAL report for template
non-compliance, VER/VAL may resubmit once. If the resubmission also fails, PM/COD is notified
(process failure — training intervention required). Development deliverables allow up to 3 iterations
before PM escalates.

**Independence**: QUA SHALL NOT report to DES, IMP, TST, or Software Manager. QUA reports
to COD/PM directly. QUA decisions to reject deliverables CANNOT be overridden by the development
team. At SIL 3–4 QUA MUST be a documented independent function.
*(Platform governance policy — EN 50128:2011 does not define a normative QUA independence
requirement. §6.5.2 is the Input Documents clause only. See ORGANIZATION.md Independence
Reference Matrix, which records QUA independence as "No" at all SIL levels.)*

---

## Diagram 1 — QUA Tasks Across the V-Model Lifecycle {#diagram-1}

```
╔══════════════════════════════════════════════════════════════════════════════════════════╗
║               EN 50128 — QUA Activities Across the V-Model Lifecycle                    ║
╚══════════════════════════════════════════════════════════════════════════════════════════╝

  PHASE 0 — INITIALIZATION
  ─────────────────────────────────────────────────────────────────────────────────────────
  QUA activity:   NONE
  Rationale:      COD generates system-level documents (S1–S4). QUA is not yet
                  instantiated; the SQAP that governs QUA does not yet exist.

  PHASE 1 — PLANNING  (§5, §6.5, §6.6)
  ─────────────────────────────────────────────────────────────────────────────────────────
  Trigger:        PM invokes @pm execute-phase 1
  QUA activities:
    [A] SQAP authorship — QUA writes the Software Quality Assurance Plan (item 1)
        under VER direction and responsibility (§6.5.4.3, deviation D8).
        QUA cannot 2nd-check its own plan (self-certification conflict).
        Normatively MANDATORY at all SIL per §6.5.4.3 "shall be written."
    [B] Template compliance check on all Phase 1 deliverables:
        • Item 1  SQAP                       (exception: QUA authors; VER 1st-checks)
        • Item 2  SQAVR                      (produced by VER; QUA checks VER report)
        • Item 3  SCMP                       (produced by CM)
        • Item 4  SVP                        (produced by VER; QUA checks VER document)
        • Item 5  SVaP                       (produced by VAL; QUA checks VAL document)
    Note: Items 4 and 5 are author-exceptions — VER and VAL author their own planning
    documents in Track A. QUA still performs template compliance on all five items.
  QUA output:     QUA Review Reports for items 1–5
  Gate input to COD: All items QUA-PASS before PM reports Track A complete

  PHASE 2 — REQUIREMENTS  (§7.2)
  ─────────────────────────────────────────────────────────────────────────────────────────
  Trigger:        PM invokes @pm execute-phase 2; REQ+SAF produce SRS; TST produces
                  Overall Test Spec; VER produces Requirements VER Report
  QUA activities:
    [A] Template compliance: Item 6  SRS
    [B] Template compliance: Item 7  Overall Software Test Specification
    [C] Template compliance: Item 8  Software Requirements Verification Report
        (QUA checks VER's report before VMGR reviews it — SIL 3–4: 1-Pass Rule applies)
    [D] Traceability audit: VER checks T1–T2 (§6.5.4.14–17); QUA audits traceability
        completeness evidence (mandatory SIL 3–4 per Table A.9 Technique 7)
  QUA output:     QUA Review Reports for items 6–8;
                  Traceability Audit Report (SIL 3–4)

  PHASE 3 — ARCHITECTURE & DESIGN  (§7.3)
  ─────────────────────────────────────────────────────────────────────────────────────────
  Trigger:        PM invokes @pm execute-phase 3; DES+SAF produce SAS, SDS, Interface
                  Specs, Integration Test Specs; VER produces Architecture VER Report
  QUA activities:
    [A] Template compliance: Item 9   Software Architecture Specification
    [B] Template compliance: Item 10  Software Design Specification
    [C] Template compliance: Item 11  Software Interface Specifications
    [D] Template compliance: Item 12  Software Integration Test Specification
    [E] Template compliance: Item 13  Software/Hardware Integration Test Specification
    [F] Template compliance: Item 14  Software Architecture and Design Verification Report
        (QUA checks VER's report; 1-Pass Rule applies; VMGR reviews after QUA PASS)
    [G] Traceability audit: VER checks T3–T5c (§7.3.4.42–7.3.4.43); QUA audits
        traceability completeness evidence (SIL 3–4)
  QUA output:     QUA Review Reports for items 9–14;
                  Traceability Audit Report (SIL 3–4)

  PHASE 4 — COMPONENT DESIGN  (§7.4)
  ─────────────────────────────────────────────────────────────────────────────────────────
  Trigger:        PM invokes @pm execute-phase 4; DES produces Component Design Spec;
                  TST produces Component Test Spec; VER produces Component Design VER Report
  QUA activities:
    [A] Template compliance: Item 15  Software Component Design Specification
    [B] Template compliance: Item 16  Software Component Test Specification
    [C] Template compliance: Item 17  Software Component Design Verification Report
        Note: Item 17 has no VAL 2nd check (blank in DELIVERABLES.md); QUA template
        compliance still applies before VER produces and VMGR reviews this report
    [D] Traceability audit: VER checks T6, T11 (§7.4.4.13); QUA audits (SIL 3–4)
  QUA output:     QUA Review Reports for items 15–17;
                  Traceability Audit Report (SIL 3–4)

  PHASE 5 — IMPLEMENTATION & TESTING  (§7.5)
  ─────────────────────────────────────────────────────────────────────────────────────────
  Trigger:        PM invokes @pm execute-phase 5; IMP produces source code; TST produces
                  Component Test Report; VER produces Source Code VER Report
  QUA activities:
    [A] Template compliance: Item 18  Software Source Code and Supporting Documentation
        QUA checks FORMAT of the source code delivery package (document structure,
        Document ID, required sections). QUA does NOT perform code inspection or
        coding standards checking — that is VER's duty under §7.5.4.10.
    [B] Template compliance + 1-Pass Rule: Item 19  Software Source Code Verification Report
        VER performs the actual code review (§7.5.4.10): MISRA C compliance, coding
        standards, cyclomatic complexity, correctness of implementation against SDS.
        VER records findings in item 19. QUA then checks that item 19 is FORMAT-correct
        before VMGR reviews it. 1-Pass Rule applies.
        Note: Code review execution (MISRA checking, static analysis, complexity
        measurement) belongs to VER (§7.5.4.10(c)) and IMP+TST — not to QUA.
    [C] Template compliance: Item 20  Software Component Test Report
    [D] Traceability audit: VER checks T7, T12 (§7.5.4.10); QUA audits (SIL 3–4)
        QUA audits the EVIDENCE that VER performed traceability checking and that
        the evidence is recorded and CM-controlled (§6.5.4.14–17, Table A.9 T7).
        QUA does not independently re-check traceability links.
    [E] QA process data recording (Table A.9 Technique 8 — D.12):
        QUA records QA process data per the SQAP: NCR counts, gate pass/fail rates,
        process audit findings, QUA review outcomes. QUA verifies that measurement
        data required by T8 (coverage reports, defect counts, complexity distributions)
        has been produced by IMP/TST/VER and is placed under CM control.
        QUA does NOT run measurement tools (cppcheck, gcov, lizard) itself — those
        are IMP/TST/VER responsibilities. QUA audits that the evidence exists.
        SIL obligation: HR SIL 0–2; MANDATORY SIL 3–4 (Table A.9 T8).
  QUA output:     QUA Review Reports for items 18–20;
                  QA Process Data Record (SIL 3–4, Table A.9 T8);
                  Traceability Audit Report (SIL 3–4)

  PHASE 6 — INTEGRATION  (§7.6)
  ─────────────────────────────────────────────────────────────────────────────────────────
  Trigger:        PM invokes @pm execute-phase 6; INT+TST produce Integration Test Reports
  QUA activities:
    [A] Template compliance: Item 21  Software Integration Test Report
    [B] Template compliance: Item 22  Software/Hardware Integration Test Report
    [C] Traceability audit: VER checks T10a, T10b, T12 (§7.6.4.13); QUA audits (SIL 3–4)
  Note: Item 23 (Software Integration Verification Report) is produced in Phase 7 per
  Annex C, not Phase 6 (platform placement follows informative Annex C Table C.1).
  QUA output:     QUA Review Reports for items 21–22;
                  Traceability Audit Report (SIL 3–4)

  PHASE 7 — VALIDATION  (§7.7)
  ─────────────────────────────────────────────────────────────────────────────────────────
  Trigger:        PM orchestrates TST (Track A); COD→VMGR coordinates VER+VAL (Track B)
  QUA activities — Track A:
    [A] Template compliance: Item 24  Overall Software Test Report (TST-produced)
  QUA activities — Track B:
    [B] Template compliance: Item 23  Software Integration Verification Report
        (produced by VER; 1-Pass Rule applies; VMGR reviews after QUA PASS)
    [C] Template compliance: Item 25  Software Validation Report
        (produced by VAL; 1-Pass Rule applies; VMGR reviews after QUA PASS)
    [D] Template compliance: Item 26  Tools Validation Report
        (produced by VAL; 1-Pass Rule applies; if applicable)
    [E] Template compliance: Item 27  Release Note
        (author unresolved in Annex C — see DELIVERABLES.md Note 3)
  Note: This is the only phase where QUA template-checks VAL-authored formal Validation
  Reports. QUA checks FORMAT only; VMGR reviews technical content (SIL 3–4).
  QUA output:     QUA Review Reports for items 23–27;
                  QA Template Compliance Reports (for VER/VAL reports, 1-Pass Rule)

  PHASE 8 — ASSESSMENT  (§6.4)
  ─────────────────────────────────────────────────────────────────────────────────────────
  QUA activity:   NONE
  Rationale:      ASR (Assessor) is fully independent from the project AND supplier
                  (§5.1.2.5–5.1.2.7). ASR is not directed by COD, PM, or QUA.
                  COD does not coordinate QUA activities during Phase 8.
                  Items 45–46 are ASR-authored; VER performs 1st check only; no VAL
                  2nd check and no QUA template compliance step (ASR operates outside
                  the standard Track A → QUA → PM → COD chain).
  Mandatory:      SIL 1–4 per §6.4.1.1; SIL 0 exempt §6.4.1.2

  PHASE 9 — DEPLOYMENT  (§9.1)
  ─────────────────────────────────────────────────────────────────────────────────────────
  Trigger:        PM invokes @pm execute-phase 9; PM/DES/CM produce deployment docs;
                  VER produces Deployment VER Report
  QUA activities:
    [A] Template compliance: Item 36  Software Release and Deployment Plan
    [B] Template compliance: Item 37  Software Deployment Manual
    [C] Template compliance: Item 38  Release Notes
    [D] Template compliance: Item 39  Deployment Records
    [E] Template compliance: Item 40  Deployment Verification Report
        (VER-authored; no VAL 2nd check per Annex C — see deviation D3;
         1-Pass Rule applies to this VER report)
  QUA output:     QUA Review Reports for items 36–40

  PHASE 10 — MAINTENANCE  (§9.2, recurring per CCB CR)
  ─────────────────────────────────────────────────────────────────────────────────────────
  Trigger:        Each CCB-approved Change Request; PM re-executes affected phases
  QUA activities:
    [A] Template compliance: Item 41  Software Maintenance Plan
    [B] Template compliance: Item 42  Software Change Records
    [C] Template compliance: Item 43  Software Maintenance Records
    [D] Template compliance: Item 44  Software Maintenance Verification Report
        (VER-authored; VAL 2nd check assigned — see deviation D4; 1-Pass Rule on VER report)
    [E] Process audit: Verify CCB change control procedures followed (MANDATORY SIL 3–4)
    [F] Traceability impact audit: Verify all downstream traceability links re-checked
        for each CR scope (MANDATORY SIL 3–4 per §6.5.4.14–17, continuous traceability
        obligation applicable through maintenance per §9.2.4)
  QUA output:     QUA Review Reports for items 41–44;
                  Process Audit Report (SIL 3–4)

  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  CROSS-CUTTING — Active throughout all phases
  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  [P] Process audits
      SIL 3–4: Monthly (MANDATORY, Table A.9 Technique 8)
      SIL 2:   Quarterly (HR)
      SIL 0–1: Optional
      Output:  Process Audit Reports

  [M] Quality metrics collection and trend analysis
      SIL 3–4: Per phase (MANDATORY, Table A.9 Technique 8)
      SIL 1–2: Per phase (HR)
      SIL 0:   Optional
      Output:  Quality Metrics Reports

  [T] Traceability audits (distinct from VER traceability checking)
      VER checks technical completeness of traceability (§6.5.4.14–17)
      QUA audits the evidence that VER traceability checking was performed, recorded,
      and baselines under CM control (§6.5.4.15)
      SIL 3–4: MANDATORY (Table A.9 Technique 7)
      SIL 1–2: HR
      Output:  Traceability Audit Reports

  [N] Non-conformance management
      QUA logs and tracks NCRs; escalates to PM/COD if unresolved
      SIL 3–4: MANDATORY recording and trend analysis
      Output:  Non-Conformance Reports (NCRs)
```

---

## Diagram 2 — QUA Touchpoints on All Annex C Deliverables {#diagram-2}

**Legend**:
- `[QUA]` — QUA performs template compliance check before VER 1st check or before VMGR review
- `[QUA-VER]` — QUA checks a VER-authored report (1-Pass Rule applies)
- `[QUA-VAL]` — QUA checks a VAL-authored report (1-Pass Rule applies; Phase 7 only)
- `[—]` — QUA has NO template compliance check for this item
- `Writer → QUA check → VER 1st → VAL 2nd → VMGR (SIL 3–4)` — full check chain

```
╔══════════════════════════════════════════════════════════════════════════════════════════╗
║         EN 50128 — QUA Touchpoints on Annex C Deliverables (Items 1–46)                 ║
╚══════════════════════════════════════════════════════════════════════════════════════════╝

 #   Document Name                                Writer    QUA check  1st Chk  2nd Chk
─────────────────────────────────────────────────────────────────────────────────────────
 PHASE 1: PLANNING
─────────────────────────────────────────────────────────────────────────────────────────
  1  Software Quality Assurance Plan              QUA       [QUA]*     VER      VAL
     * QUA authors under VER direction (§6.5.4.3, deviation D8)
       VER holds normative §6.5.4.3 responsibility; QUA performs authoring.
       QUA cannot 2nd-check its own document (self-certification conflict).

  2  Software QA Verification Report              VER       [QUA-VER]  —        VAL
     1-Pass Rule applies. VMGR reviews after QUA PASS (SIL 3–4).

  3  Software Configuration Management Plan       CM        [QUA]      VER      VAL

  4  Software Verification Plan                   VER       [QUA-VER]  —        VAL
     1-Pass Rule applies. VER authors own planning document (Track A exception).

  5  Software Validation Plan                     VAL       [QUA-VAL]  VER      —
     1-Pass Rule applies. VAL authors own planning document (Track A exception).
     No VAL 2nd check (VAL cannot 2nd-check its own document).
     Platform deviation D1: placed Phase 1 (Annex C places in Phase 2).

─────────────────────────────────────────────────────────────────────────────────────────
 PHASE 2: REQUIREMENTS
─────────────────────────────────────────────────────────────────────────────────────────
  6  Software Requirements Specification          REQ+SAF   [QUA]      VER      VAL
     USER APPROVAL REQUIRED (SRS) before COD gate. Ref: §7.2.4.1.

  7  Overall Software Test Specification          TST       [QUA]      VER      VAL

  8  Software Requirements Verification Report    VER       [QUA-VER]  —        VAL
     1-Pass Rule applies.

─────────────────────────────────────────────────────────────────────────────────────────
 PHASE 3: ARCHITECTURE & DESIGN
─────────────────────────────────────────────────────────────────────────────────────────
  9  Software Architecture Specification          DES+SAF   [QUA]      VER      VAL

 10  Software Design Specification                DES       [QUA]      VER      VAL

 11  Software Interface Specifications            DES       [QUA]      VER      VAL
     Plural form per §7.3.3 item 3.

 12  Software Integration Test Specification      INT       [QUA]      VER      VAL

 13  Software/Hardware Integration Test Spec.     INT       [QUA]      VER      VAL

 14  Software Architecture and Design             VER       [QUA-VER]  —        VAL
     Verification Report
     1-Pass Rule applies.

─────────────────────────────────────────────────────────────────────────────────────────
 PHASE 4: COMPONENT DESIGN
─────────────────────────────────────────────────────────────────────────────────────────
 15  Software Component Design Specification      DES       [QUA]      VER      VAL

 16  Software Component Test Specification        TST       [QUA]      VER      VAL

 17  Software Component Design Verification Rpt   VER       [QUA-VER]  —        —
     1-Pass Rule applies. No VAL 2nd check (blank in Annex C Table C.1).

─────────────────────────────────────────────────────────────────────────────────────────
 PHASE 5: IMPLEMENTATION & TESTING
─────────────────────────────────────────────────────────────────────────────────────────
 18  Software Source Code and Supporting Docs     IMP       [QUA]      VER      VAL
      QUA checks FORMAT only. VER performs code review (§7.5.4.10: MISRA C,
      coding standards, complexity, correctness). VER records findings in item 19.

 19  Software Source Code Verification Report     VER       [QUA-VER]  —        VAL
     1-Pass Rule applies. 2nd Check (VAL) is project addition — see deviation D6.

 20  Software Component Test Report               TST       [QUA]      VER      VAL
     Platform deviation D2: Phase 5 (Annex C places in Integration phase).

─────────────────────────────────────────────────────────────────────────────────────────
 PHASE 6: INTEGRATION
─────────────────────────────────────────────────────────────────────────────────────────
 21  Software Integration Test Report             INT+TST   [QUA]      VER      VAL

 22  Software/Hardware Integration Test Report    INT+TST   [QUA]      VER      VAL

─────────────────────────────────────────────────────────────────────────────────────────
 PHASE 7: VALIDATION  ★ Only phase where VAL authors formal Validation Reports
─────────────────────────────────────────────────────────────────────────────────────────
 23  Software Integration Verification Report     VER       [QUA-VER]  —        —
     1-Pass Rule applies. No VAL 2nd check (blank in Annex C). VMGR reviews (SIL 3–4).
     Normative production clause: §7.6.4.11 (Integration); placed Phase 7 per Annex C.

 24  Overall Software Test Report                 TST       [QUA]      VER      VAL
     Track A deliverable; QUA checks before PM reports to COD.

 25  Software Validation Report                   VAL       [QUA-VAL]  VER      —
     1-Pass Rule applies. VAL MUST BE INDEPENDENT SIL 3–4 (§5.1.2.10(f)).
     No 2nd Check (VAL cannot 2nd-check its own report).

 26  Tools Validation Report                      VAL       [QUA-VAL]  VER      —
     1-Pass Rule applies. Same independence constraint as item 25.
     HR SIL 1+; R SIL 0.

 27  Release Note (§7.7.4.12 normative)           —         [QUA]      VER      VAL
     Authorship unresolved in Annex C (footnote a). Author per project SQAP.
     See DELIVERABLES.md Note 3 for Annex C numbering ambiguity.

─────────────────────────────────────────────────────────────────────────────────────────
 PHASE 8: ASSESSMENT  ★ QUA has NO touchpoint — ASR is fully independent
─────────────────────────────────────────────────────────────────────────────────────────
 45  Software Assessment Plan                     ASR       [—]        VER      —
 46  Software Assessment Report                   ASR       [—]        VER      —
     ASR is independent from the project AND supplier (§5.1.2.5–5.1.2.7).
     QUA does NOT check ASR documents. VER performs independent 1st check only.
     No VAL 2nd check. Mandatory SIL 1–4 (§6.4.1.1); SIL 0 exempt (§6.4.1.2).

─────────────────────────────────────────────────────────────────────────────────────────
 PHASE 9: DEPLOYMENT
─────────────────────────────────────────────────────────────────────────────────────────
 36  Software Release and Deployment Plan         PM        [QUA]      VER      VAL

 37  Software Deployment Manual                   DES       [QUA]      VER      VAL
     Author per project SQAP (Annex C footnote a).

 38  Release Notes (plural — distinct from item 27)  PM     [QUA]      VER      VAL

 39  Deployment Records                           CM        [QUA]      VER      VAL
     Author per project SQAP (Annex C footnote a).

 40  Deployment Verification Report               VER       [QUA-VER]  —        —
     1-Pass Rule applies. No VAL 2nd check (blank in Annex C).
     Platform deviation D3: Phase 9 (Annex C places in Maintenance phase).

─────────────────────────────────────────────────────────────────────────────────────────
 PHASE 10: MAINTENANCE  (recurring per CCB Change Request)
─────────────────────────────────────────────────────────────────────────────────────────
 41  Software Maintenance Plan                    PM        [QUA]      VER      VAL

 42  Software Change Records                      PM        [QUA]      VER      VAL
     Annex C typo ("Software Chang Records") — correct name per §9.2.4.

 43  Software Maintenance Records                 PM        [QUA]      VER      VAL

 44  Software Maintenance Verification Report     VER       [QUA-VER]  —        VAL
     1-Pass Rule applies. VAL 2nd check is a project addition — see deviation D4.
     Platform deviation D4: Phase 10 (Annex C places in Assessment phase).

─────────────────────────────────────────────────────────────────────────────────────────
 SECTION 8 ITEMS (generic platform only — not applicable to bespoke software)
─────────────────────────────────────────────────────────────────────────────────────────
 28  Application Requirements Specification       REQ       [QUA]      VER      VAL
 29  Application Preparation Plan                 REQ/DES   [QUA]      VER      VAL
 30  Application Test Specification               TST       [QUA]      VER      VAL
 31  Application Architecture and Design          DES       [QUA]      VER      VAL
 32  Application Preparation Verification Report  VER       [QUA-VER]  —        —
 33  Application Test Report                      TST       [QUA]      VER      VAL
 34  Source Code of Application Data/Algorithms   DES       [QUA]      VER      VAL
 35  Application Data/Algorithms VER Report       VER       [QUA-VER]  —        VAL

─────────────────────────────────────────────────────────────────────────────────────────
 QUA TOUCHPOINT SUMMARY
─────────────────────────────────────────────────────────────────────────────────────────
 Total Annex C items (bespoke scope, excl. §8): 37 (items 1–27 + 36–46)
 Items with QUA template check [QUA]:            23  (development deliverables)
 Items with QUA check on VER report [QUA-VER]:   11  (items 2, 4, 8, 14, 17, 19, 23, 32*,
                                                       35*, 40, 44)  *§8 scope only
 Items with QUA check on VAL report [QUA-VAL]:    3  (items 5, 25, 26)
 Items with NO QUA check [—]:                     2  (items 45, 46 — ASR documents)
─────────────────────────────────────────────────────────────────────────────────────────
```

---

## Diagram 3 — QUA in the Two-Track Workflow {#diagram-3}

This diagram shows exactly where QUA intervenes in the per-phase execution loop defined
in `WORKFLOW.md` Diagrams 2 and 3. QUA is a **gate within Track A** and a **gate within
Track B** — it never performs technical verification (that is VER's role) and never
performs technical validation (that is VAL's role).

```
╔══════════════════════════════════════════════════════════════════════════════════════════╗
║                     EN 50128 — QUA in the Two-Track Workflow                            ║
╚══════════════════════════════════════════════════════════════════════════════════════════╝

 ══════════════════════════════════════════════════════════════════════
  TRACK A  —  Development  (PM orchestrates)
  QUA role: MANDATORY gate between deliverable production and PM→COD handoff
 ══════════════════════════════════════════════════════════════════════

  USER → @pm execute-phase N
    │
    ▼
  PM orchestrates development agents
  (REQ · DES · IMP · INT · TST · SAF · CM as applicable)
    │  deliverable produced
    ▼
 ┌─────────────────────────────────────────────────────────────┐
 │               QUA TEMPLATE CHECK (Track A gate)             │
 │                                                             │
 │  QUA checks:                                                │
 │  ✓ Document ID format correct                               │
 │  ✓ Document Control table present and complete              │
 │  ✓ Approvals table with SIL-appropriate roles               │
 │  ✓ All required sections present                            │
 │  ✓ No obvious structural violations                         │
 │                                                             │
 │  QUA does NOT check technical content (that is VER's role)  │
 └─────────────────────────────────────────────────────────────┘
    │
    ├── FAIL ──► PM notifies author; author fixes; resubmits
    │            └── re-check → FAIL again → PM escalates (max 3 iterations)
    │
     └── PASS
           │
           ▼
         PM marks deliverable QUA-ACCEPTED in LIFECYCLE_STATE.md
          │
          ▼
        [repeat for each deliverable in the phase]
          │
          ▼
        All phase deliverables QUA-ACCEPTED
          │
          ▼
        PM reports Track A complete to COD

 ══════════════════════════════════════════════════════════════════════
  TRACK B  —  Independent V&V  (COD coordinates; SIL 3–4 shown)
  QUA role: TEMPLATE gate on VER reports (and VAL reports in Phase 7)
  PM has NO authority over any agent in this track
 ══════════════════════════════════════════════════════════════════════

  COD receives Track A complete from PM
    │
    ▼
  COD → VMGR: "request verification of phase deliverables"
    │           [no direct COD→VER path at SIL 3–4]
    │
    ▼
  VMGR assigns VER; VER performs technical verification
    │  VER produces Verification Report
    │
    ▼
 ┌─────────────────────────────────────────────────────────────┐
 │          QUA TEMPLATE CHECK — VER REPORT (1-Pass Rule)      │
 │                                                             │
 │  QUA checks FORMAT of VER report:                           │
 │  ✓ Document ID format correct                               │
 │  ✓ Document Control table present                           │
 │  ✓ Approvals table with SIL-appropriate roles               │
 │    (VER, VMGR, COD for SIL 3–4)                            │
 │  ✓ All required sections present                            │
 │  ✓ No obvious formatting violations                         │
 │                                                             │
 │  1-PASS RULE:                                               │
 │  ─ VER may resubmit ONCE if rejected                        │
 │  ─ If second review fails → escalate to PM/COD              │
 │    (process failure: VER does not know own template)        │
 └─────────────────────────────────────────────────────────────┘
    │
    ├── FAIL ──► VER re-issues report (once only)
    │            └── re-check → FAIL again → PM/COD notified (process failure)
    │
    └── PASS
          │
          ▼
        VMGR reviews VER report (technical content)
          ├── REJECT ──► VER reworks technical content; new report → QUA re-checks
          └── APPROVE
                │
                ▼
              [Phase 7 only — Step B2: Validation]
              VMGR assigns VAL; VAL performs final validation
                │  VAL produces Validation Reports (items 25, 26)
                │
                ▼
 ┌─────────────────────────────────────────────────────────────┐
 │         QUA TEMPLATE CHECK — VAL REPORT (1-Pass Rule)       │
 │                                                             │
 │  Same template compliance checks as VER report above.       │
 │  QUA checks FORMAT; VMGR reviews technical content.         │
 │  1-PASS RULE applies identically.                           │
 └─────────────────────────────────────────────────────────────┘
                │
                ├── FAIL ──► VAL re-issues (once only) → re-check
                │            → FAIL again → PM/COD notified
                │
                └── PASS
                      │
                      ▼
                    VMGR reviews VAL reports (technical content)
                      ├── REJECT ──► VAL reworks; new report → QUA re-checks
                      └── APPROVE — VMGR Final V&V Decision
                            │       (cannot be overridden by COD or PM)
                            ▼
                          VMGR reports V&V outcome to COD

 ══════════════════════════════════════════════════════════════════════
  COD GATE CHECK  (reads QUA-passed and VMGR-approved reports)
 ══════════════════════════════════════════════════════════════════════

  ✓ All phase deliverables QUA-passed (Track A)
  ✓ VER Verification Report QUA-passed and VMGR-approved (Track B, SIL 3–4)
    or VER report QUA-passed and received directly (SIL 0–2)
  ✓ VAL reports QUA-passed and VMGR-approved (Phase 7 only; SIL 3–4)
  ✓ Traceability complete (from VER Verification Report findings)
  ✓ Zero critical open defects
    │
    ├── PASS ──► COD authorizes next phase
    └── FAIL ──► COD BLOCKS; PM coordinates rework; COD re-runs gate

 ══════════════════════════════════════════════════════════════════════
  SIL 0–2 VARIATION (no VMGR)
 ══════════════════════════════════════════════════════════════════════

  Track A is identical (QUA template checks mandatory at all SIL).
  Track B simplified:
    COD invokes VER directly → VER produces report → QUA template check
    (1-Pass Rule still applies) → QUA PASS → COD receives VER report
    Phase 7: COD invokes VAL directly → VAL produces reports → QUA checks
    → COD receives reports directly

 ══════════════════════════════════════════════════════════════════════
  QUA POSITION SUMMARY
 ══════════════════════════════════════════════════════════════════════

  ┌────────────────────────────────────────────────────────────────┐
  │               QUA IS A GATE, NOT A REVIEWER                    │
  │                                                                │
  │  QUA gate 1 (Track A): between deliverable production          │
  │                          and PM→COD handoff                    │
  │  QUA gate 2 (Track B): between VER report production           │
  │                          and VMGR technical review (SIL 3–4)  │
  │                          or COD receipt (SIL 0–2)             │
  │  QUA gate 3 (Track B, Phase 7 only): between VAL report        │
  │                          production and VMGR review (SIL 3–4) │
  │                                                                │
  │  COD CANNOT open a gate-check until QUA has passed ALL         │
  │  deliverables for that phase.                                  │
  │                                                                │
  │  QUA reports to COD/PM — NOT to DES/IMP/TST (platform governance policy;
  │  see ORGANIZATION.md — EN 50128:2011 §6.5.2 is Input Documents only).         │
  │  QUA decisions cannot be overridden by development team.       │
  └────────────────────────────────────────────────────────────────┘
```

---

## Diagram 4 — Table A.9 SIL-Tiered Obligations {#diagram-4}

This table maps EN 50128:2011 Table A.9 (Software Quality Assurance Techniques) to the
lifecycle phases where each technique is exercised, and shows the SIL-dependent
obligation level. Sources: §6.5, Table A.9, §6.5.4.14–17, §6.5.1.1, §6.5.1.2.

```
╔══════════════════════════════════════════════════════════════════════════════════════════╗
║              EN 50128 Table A.9 — SIL-Tiered QA Obligations Mapped to Lifecycle         ║
╚══════════════════════════════════════════════════════════════════════════════════════════╝

 ───────────────────────────────────────────────────────────────────────────────────────
  TECHNIQUE 1 — Accredited to EN ISO 9001  (§7.1)
  SIL 0: R  |  SIL 1–2: HR  |  SIL 3–4: HR
 ───────────────────────────────────────────────────────────────────────────────────────
  Lifecycle trigger: Phase 0 (project initialization)
  Activity: Organisation holds EN ISO 9001 accreditation
  QUA role: Confirm accreditation certificate exists and is in scope; record in SQAP
  Notes: Accreditation ≠ compliance; Technique 2 (compliance) is MANDATORY even if
         Technique 1 (accreditation) is only HR. These are distinct obligations.

 ───────────────────────────────────────────────────────────────────────────────────────
  TECHNIQUE 2 — Compliant with EN ISO 9001  (§7.1)         ★ MANDATORY ALL SIL
  SIL 0: M  |  SIL 1–2: M  |  SIL 3–4: M
 ───────────────────────────────────────────────────────────────────────────────────────
  Lifecycle trigger: Continuous (all phases)
  Activity: Quality management system compliant with ISO 9001:2015
  QUA role: Develop and maintain SQAP (item 1) documenting how quality system complies;
            conduct process audits to verify compliance; report non-conformances
  Phases active: 1 (SQAP written), 2–10 (SQAP enforced through audits)
  Output: SQAP; Process Audit Reports; NCRs

 ───────────────────────────────────────────────────────────────────────────────────────
  TECHNIQUE 3 — Compliant with ISO/IEC 90003  (§7.1)
  SIL 0: R  |  SIL 1–2: R  |  SIL 3–4: R
 ───────────────────────────────────────────────────────────────────────────────────────
  Lifecycle trigger: Phase 1 (referenced in SQAP)
  Activity: Apply ISO/IEC 90003:2014 software engineering guidelines for ISO 9001
  QUA role: Note ISO/IEC 90003 applicability in SQAP if adopted; no mandatory audit
  Notes: Recommended only at all SIL. ISO/IEC 90003 provides guidance on applying
         ISO 9001 to software — useful but not required by the standard.

 ───────────────────────────────────────────────────────────────────────────────────────
  TECHNIQUE 4 — Company Quality System  (§7.1)             ★ MANDATORY ALL SIL
  SIL 0: M  |  SIL 1–2: M  |  SIL 3–4: M
 ───────────────────────────────────────────────────────────────────────────────────────
  Lifecycle trigger: Continuous (all phases)
  Activity: Organisation has a documented company quality management system
  QUA role: Reference company QMS in SQAP; verify project practices are consistent
            with company QMS procedures; audit for QMS compliance
  Phases active: 1 (SQAP documents QMS reference), 2–10 (audited continuously)
  Output: SQAP (QMS reference section); Process Audit Reports

 ───────────────────────────────────────────────────────────────────────────────────────
  TECHNIQUE 5 — Software Configuration Management  (D.48)  ★ MANDATORY ALL SIL
  SIL 0: M  |  SIL 1–2: M  |  SIL 3–4: M
 ───────────────────────────────────────────────────────────────────────────────────────
  Lifecycle trigger: Phase 1 (SCMP produced); continuous thereafter
  Activity: SCM processes for version control, baselines, change control per §6.6
  QUA role: Audit CM processes at each phase gate (SIL 3–4); verify:
            • All deliverables placed under CM from first issue (§6.5.4.10)
            • Changes to CM items authorised and recorded (§6.5.4.11)
            • Traceability is under CM control (§6.5.4.15)
            • Baseline integrity maintained between phases
  Phases active: 1 (SCMP reviewed), 2–10 (CM audited at each gate)
  Output: Process Audit Reports (CM section); NCRs for CM violations
  Note: CM is performed by CM agent; QUA audits CM process but does not own it.

 ───────────────────────────────────────────────────────────────────────────────────────
  TECHNIQUE 6 — Checklists  (D.7)
  SIL 0: R  |  SIL 1–2: HR  |  SIL 3–4: HR
 ───────────────────────────────────────────────────────────────────────────────────────
  Lifecycle trigger: Each deliverable review; each audit
  Activity: Structured checklists for reviews, inspections, audits
  QUA role: Maintain and apply checklists for:
            Phase 1–4:  Document template compliance checklists (Document ID,
                        Document Control table, Approvals table, required sections)
            Phase 5:    Template compliance checklists for items 18–20 only
                        (source code delivery package format, VER report format,
                        test report format). Code review checklists covering MISRA C
                        compliance, cyclomatic complexity, defensive programming, and
                        coding standards are VER tools under §7.5.4.10 — not QUA tools.
            Phase 5–7:  Test report template compliance checklists (plan, specification,
                        report format — format only, not test coverage adequacy)
            All phases: Process audit checklists
  Phases active: All phases where QUA performs template compliance or process audit
  Output: Completed checklists included in QUA Review Reports

 ───────────────────────────────────────────────────────────────────────────────────────
  TECHNIQUE 7 — Traceability  (D.58)                       ★ MANDATORY SIL 3–4
  SIL 0: R  |  SIL 1–2: HR  |  SIL 3–4: M
 ───────────────────────────────────────────────────────────────────────────────────────
  Lifecycle trigger: Each phase gate; mandatory per §6.5.4.14–17
  Activity: Bi-directional traceability S1→SRS→SAS→SDS→Code→Test (forward and backward)
  QUA role: QUA audits the EVIDENCE of traceability (that VER checked it and recorded
            findings in the Verification Report; that traceability is under CM control
            per §6.5.4.15). QUA does NOT independently check traceability links
            (that is VER's technical responsibility per §6.5.4.14–17 and TRACEABILITY.md).
  Phases active and mandatory traceability rules checked at each gate:
    Phase 2: T1, T2       (system → software requirements)
    Phase 3: T3–T5c       (requirements → architecture → design)
    Phase 4: T6, T11      (design → component; component test traces)
    Phase 5: T7, T12      (component design → code; test reports ← specs)
    Phase 6: T10a, T10b   (integration test traces to SRS/SAS/SDS/interfaces)
    Phase 7: T8, T9, T13  (test spec ↔ requirements; validation → SRS)
  Traceability rule reference: TRACEABILITY.md Section 9 (rules T1–T15)
  Output: Traceability Audit Reports (per-phase gate, SIL 3–4)

 ───────────────────────────────────────────────────────────────────────────────────────
  TECHNIQUE 8 — Data Recording and Analysis  (D.12)        ★ MANDATORY SIL 3–4
  SIL 0: HR  |  SIL 1–2: HR  |  SIL 3–4: M
 ───────────────────────────────────────────────────────────────────────────────────────
  Lifecycle trigger: Each phase gate (SIL 3–4); periodic (SIL 1–2)
  Activity: Collect, record, and trend-analyze quality metrics across the lifecycle
  QUA role: Collect and report metrics at each phase:
            Phase 2:  Requirements count, SIL distribution, complexity
            Phase 3:  Design module count, interface count, coupling metrics
            Phase 5:  SLOC, comment density, cyclomatic complexity distribution,
                      MISRA C violation counts (mandatory/required/advisory),
                      defect density (defects/KLOC)
            Phase 5–7: Statement coverage %, branch coverage %,
                       condition coverage % (SIL 3–4), test case count,
                       defect detection rate, defect removal efficiency
            All phases: NCR counts by severity; open vs. closed trends
  Phases active: All phases (SIL 3–4 mandatory per-phase; SIL 1–2 periodic)
  Output: Quality Metrics Reports (per phase); trend charts in SQAP updates

 ═══════════════════════════════════════════════════════════════════════════════════════
  OBLIGATION SUMMARY BY PHASE
 ═══════════════════════════════════════════════════════════════════════════════════════

  Phase     | T1    | T2    | T3    | T4    | T5    | T6    | T7    | T8
  ──────────+───────+───────+───────+───────+───────+───────+───────+───────
  Ph 0      | R/HR  | M     | R     | M     | M     | —     | —     | —
  Ph 1      | R/HR  | M     | R     | M     | M     | R/HR  | R/HR  | HR/M
  Ph 2      | —     | M     | R     | M     | M     | R/HR  | HR/M  | HR/M
  Ph 3      | —     | M     | R     | M     | M     | R/HR  | HR/M  | HR/M
  Ph 4      | —     | M     | R     | M     | M     | R/HR  | HR/M  | HR/M
  Ph 5      | —     | M     | R     | M     | M     | R/HR  | HR/M  | HR/M
  Ph 6      | —     | M     | R     | M     | M     | R/HR  | HR/M  | HR/M
  Ph 7      | —     | M     | R     | M     | M     | R/HR  | HR/M  | HR/M
  Ph 8      | —     | —     | —     | —     | —     | —     | —     | —
  Ph 9      | —     | M     | R     | M     | M     | R/HR  | R/HR  | HR/M
  Ph 10     | —     | M     | R     | M     | M     | R/HR  | HR/M  | HR/M
  ──────────+───────+───────+───────+───────+───────+───────+───────+───────

  Cell format: SIL 0–2 obligation / SIL 3–4 obligation
  M = Mandatory · HR = Highly Recommended · R = Recommended · — = not active this phase

  Legend:
    T1 = Accredited to EN ISO 9001
    T2 = Compliant with EN ISO 9001 (MANDATORY ALL SIL)
    T3 = Compliant with ISO/IEC 90003 (R all SIL)
    T4 = Company Quality System (MANDATORY ALL SIL)
    T5 = Software Configuration Management (MANDATORY ALL SIL)
    T6 = Checklists (R SIL 0; HR SIL 1–4)
    T7 = Traceability (R SIL 0; HR SIL 1–2; MANDATORY SIL 3–4)
    T8 = Data Recording and Analysis (HR SIL 0–2; MANDATORY SIL 3–4)

  Note: Phase 8 (Assessment) is excluded — QUA has no active obligation in this phase.
        ASR independently governs all Phase 8 activities (§6.4.1.1, §5.1.2.5–5.1.2.7).

 ═══════════════════════════════════════════════════════════════════════════════════════
  MANDATORY BASELINE (minimum QUA activities, independent of SIL level)
 ═══════════════════════════════════════════════════════════════════════════════════════

  These apply at ALL SIL levels (0 through 4) without exception:

  1. Produce SQAP (§6.5.4.3 "shall be written")
  2. Implement quality system compliant with EN ISO 9001 (T2, MANDATORY ALL SIL)
  3. Use company quality management system (T4, MANDATORY ALL SIL)
  4. Enforce software configuration management (T5, MANDATORY ALL SIL)
  5. Enforce quality gates — no phase transition without QUA approval

  Below SIL 3–4, the SQAP MAY document a rationale for not applying HR/M+ techniques,
  per EN 50128:2011 Section 1 (SIL-appropriate application principle). The Safety
  Authority must accept any downward deviation from HR obligations.
```

---

## Notes and Known Standard Ambiguities

| ID | Item | Issue | Resolution |
|----|------|-------|------------|
| D1 | Item 5 (SVaP) | Annex C places SVaP in Phase 2; platform places it in Phase 1 alongside the other planning documents | Platform deviation; SVaP authorship (VAL) and self-certification conflict documented in SQAP |
| D2 | Item 20 (Software Component Test Report) | Annex C places item 20 in Integration phase; platform places it in Phase 5 (Implementation & Testing) where it is produced | Platform deviation; document in SQAP |
| D3 | Item 40 (Deployment Verification Report) | Annex C places item 40 in Maintenance phase; platform places it in Phase 9 (Deployment) where it is produced | Platform deviation; no VAL 2nd check per Annex C; document in SQAP |
| D4 | Item 44 (Software Maintenance Verification Report) | Annex C places item 44 in Assessment phase; platform places it in Phase 10 (Maintenance) where it is produced | Platform deviation; VAL 2nd check is a project addition beyond Annex C; document in SQAP |
| D6 | Item 19 (Source Code VER Report) | Annex C Table C.1: 2nd Check blank; this platform assigns VAL 2nd check | Project addition beyond Annex C; document in SQAP |
| D7 | Item 44 (Maintenance VER Report) | Annex C Table C.1: 2nd Check may be blank | If blank in printed standard, platform assignment of VAL 2nd check is project addition; document in SQAP |
| D8 | Item 1 (SQAP) | §6.5.4.3: "under responsibility of Verifier"; Annex C Written By: blank | Platform assigns QUA as author under VER direction; SQAP must document this role split |
| — | Phase 8 QUA exemption | QUA has no track-A or track-B role; ASR is fully independent | Grounded in §5.1.2.5–5.1.2.7; document in SQAP that QUA scope excludes Phase 8 |
| — | Table A.9 mandatory floor | T2, T4, T5 are MANDATORY at ALL SIL (including SIL 0) | No SIL-based waiver is available for these three techniques |
| — | D5 | Not used — numbering gap preserved to maintain alignment with DELIVERABLES.md deviation register | N/A |

---

*References: EN 50128:2011 §6.5, §6.5.4.3, §6.5.4.5, §6.5.4.10, §6.5.4.11, §6.5.4.14–17, §7.5.4.10, §9.2.4, Table A.9, Annex C Table C.1*  
*(Note: §6.5.2 is the Input Documents clause only — it contains no independence or organisational authority requirement.)*  
*Grounded in: `WORKFLOW.md`, `DELIVERABLES.md`, `LIFECYCLE.md`, `ORGANIZATION.md`, `TRACEABILITY.md`*
