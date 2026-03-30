# EN 50128 V&V Manager Skill
---
name: en50128-vmgr
---

**Role**: V&V Manager (VMGR)  
**Standard**: EN 50128:2011 §5.1.2.10(e–f), §6.3.4.12–14  
**Authority source**: `tasks/VnV-PROCESS.md` (ISA PASS), `WORKFLOW.md` (ISA PASS)  
**Machine-readable data**: `activities/vnv-process.yaml`

---

## 1. VMGR Role Definition

VMGR is a **platform extension role** — it does not appear in EN 50128:2011 Annex B.
Its normative basis is §5.1.2.10(e) (Verifier can report to Validator) and §5.1.2.10(f)
(Validator shall not report to PM). The platform implements the "reports to Validator"
option by naming a dedicated VMGR authority so the VER team reports to VMGR, not PM.

**VMGR is:**
- The independent V&V authority at SIL 3-4
- The sole reviewer and approver/rejector of all VER Verification Reports
- The sole reviewer and approver/rejector of all VAL Validation Reports
- The issuer of the Final V&V Decision (cannot be overridden)

**VMGR is NOT:**
- An Annex B EN 50128 role (it is a platform extension — must be approved by Safety Authority)
- A replacement for ASR (Assessor remains mandatory and fully independent from VMGR)
- A manager of VAL's decisions — VMGR coordinates; VAL holds release authority (§5.1.2.8)
- A performer of validation activities — VAL performs all validation; VMGR reviews output

---

## 2. SIL Activation and Platform Requirement

| SIL | VMGR present | V&V routing | Reference |
|-----|-------------|-------------|-----------|
| SIL 0 | No | COD → VER/VAL directly | §5.1.2.12 |
| SIL 1–2 | No | COD → VER/VAL directly; PM may oversee | §5.1.2.11 |
| SIL 3–4 | **Yes (required)** | COD → VMGR → VER/VAL only | §5.1.2.10(e–f); platform |

**Platform requirement** (deviation D-05 in `DELIVERABLES.md`): VMGR's use on any SIL 1-4
project must be approved by the Safety Authority and documented in the SQAP before use.
Source: `activities/vnv-process.yaml` `vmgr_extension.platform_requirement`.

---

## 3. Per-Phase Duty Table

| Phase(s) | VMGR duties |
|----------|-------------|
| 1–6, 9–10 (standard) | Assigns VER to verify phase deliverables; reviews VER Verification Reports (after QUA pass); approves or rejects VER output; reports V&V outcome to COD |
| 7 (Validation — special) | Coordinates both VER and VAL sequentially (Step B1 then Step B2); reviews VER Integration Verification Report (item 23); coordinates VAL final validation; reviews VAL Validation Reports (items 25–26); reviews SW Validation Verification Report (item †); provides FINAL V&V DECISION — cannot be overridden; reports final V&V outcome to COD |
| 8 (Assessment) | VER performs 1st Check on ASR deliverables (items 45–46) under VMGR coordination; ASR is fully independent from VMGR — VMGR has NO authority over ASR or its deliverables |

Source: `activities/vnv-process.yaml` `vmgr_extension.per_phase_duties`.

---

## 4. Standard-Phase VER Report Review Algorithm

**Applies to**: Phases 1–6, 9–10. Triggered after QUA template PASS on the VER
Verification Report for the phase.

**VMGR reviews technical content** — not format (that is QUA's job). For each phase,
confirm the following:

### Phase 1 — Planning (VER report: item 2, SQAVR)
- SQAP (item 1) covers all §6.5.4.5 minimum content sections
- SCMP (item 3) addresses §6.6 requirements
- SVP (item 4) was authored by VER, not PM; names item † as a required deliverable (§6.2.4.2)
- SVaP (item 5) was authored by VAL, not PM; covers §6.3.4.2 minimum content
- SIL level stated and consistent across all planning documents

### Phase 2 — Requirements (VER report: item 8, REQVER)
- SRS (item 6) requirements are unambiguous, verifiable, and complete
- Traceability T1 (System Requirements → SW Requirements) is present
- Traceability T2 (Hazard Log → safety requirements) is present
- Overall Software Test Specification (item 7) addresses all SRS requirements

### Phase 3 — Architecture and Design (VER report: item 14, ARCHDESIGNVER)
- SAS (item 9) shows modular decomposition with no circular dependencies
- SDS (item 10) covers all components identified in SAS
- Interface Specifications (item 11) are complete for all external and internal interfaces
- Integration Test Specifications (items 12–13) address all interfaces
- Traceability T3 (SRS → SAS) and T4 (SAS → SDS) are present

### Phase 4 — Component Design (VER report: item 17, COMPDESIGNVER)
- Every component design element addresses at least one SRS requirement (T5)
- Algorithm specifications are complete and unambiguous (all inputs, boundary values, error cases)
- Data structures use fixed-width types; no dynamic allocation
- State machines: all states reachable, all transitions defined, no undefined state/input
- Estimated cyclomatic complexity is within SIL limit (SIL 3-4: ≤ 10; SIL 2: ≤ 15)
- No prohibited constructs introduced (no recursion HR SIL 3-4; no function pointers HR SIL 3-4)

### Phase 5 — Implementation and Testing (VER report: item 19, SOURCECODEVER)
- Static analysis results: zero critical/high severity issues (SIL 3-4)
- MISRA C: zero mandatory violations (SIL 2+); advisory compliance ≥ 95% (SIL 3-4)
- Cyclomatic complexity: all functions within SIL limit
- Coverage evidence exists for statement, branch, condition (SIL 3-4)
- Traceability T6 (SDS → source code) is present

### Phase 6 — Integration (no separate VER report at phase close; item 23 is in Phase 7)
- Note: VER produces no Verification Report at the close of Phase 6. Item 23 belongs
  to Phase 7. VMGR confirms integration test results (items 21–22) are complete and
  that VER has reviewed them as part of the Phase 7 B1 step.

### Phase 9 — Deployment (VER report: item 40, DEPLOYVER)
- Release package complete per SCMP baseline
- Deployment records (item 39) signed; configuration consistent with Phase 7 baseline

### Phase 10 — Maintenance (VER report: item 44, MAINTVER)
- Change records (item 42) reference approved CRs
- Maintenance verification scope matches CCB-approved impact assessment

**Decision**:
- **APPROVE**: issue written approval; record via `workspace.py wf review`; report outcome to COD
- **REJECT**: return to VER with written findings identifying each criterion that failed; VER reworks, QUA re-checks, resubmits to VMGR

---

## 5. Phase 7 Combined Review Procedure

Phase 7 runs in two sequential sub-steps under VMGR coordination. Source:
`activities/vnv-process.yaml` `phase7_corrected_track_b_sil_34`.

```
B0  COD sends Phase 7 V&V request to VMGR
     │
B1  VMGR assigns VER
     VER produces SW Integration Verification Report (item 23)
     QUA template check on item 23
       → FAIL: VER re-issues
       → PASS: proceed
     VMGR reviews item 23 (technical review per Phase 6 integration scope)
       → REJECT: VER reworks; QUA re-checks; return to VMGR
       → APPROVE: proceed to B2
     │
B2  VMGR assigns VAL
     VAL performs final validation:
       reviews all phase evidence;
       produces SW Validation Report (item 25);
       produces Tools Validation Report (item 26, if applicable);
       produces Release Note §7.7.4.12 (item 27; authorship per SQAP — deviation D-04)
     VAL issues release decision: APPROVE or REJECT (§5.1.2.8)
       → VAL REJECT: VMGR notifies COD; COD notifies PM; PM coordinates rework
                     → full B1–B2 loop repeats
       → VAL APPROVE: proceed
     QUA template check on VAL reports (items 25, 26)
       → FAIL: VAL re-issues; QUA re-checks
       → PASS: proceed
     VER produces SW Validation Verification Report (item †, §6.3.4.12–14)
     QUA template check on item † (1-Pass Rule: max 1 resubmission)
       → FAIL: VER re-issues (max 1 time); 2nd rejection = process failure → escalate
       → PASS: proceed
     VMGR reviews item † AND items 25–26 together
       → REJECT: VER/VAL reworks; QUA re-checks
       → APPROVE: VMGR FINAL V&V DECISION GRANTED (cannot be overridden by COD or PM)
     │
B3  VMGR reports V&V outcome to COD
     COD records in LIFECYCLE_STATE.md and enforces Phase 7 gate
```

**Critical constraint**: VMGR MUST NOT issue the Final V&V Decision before item † has
passed QUA template check and VMGR has reviewed it alongside items 25–26.

---

## 6. VAL Report Review Criteria

**Applies to**: Phase 7 Step B2, after QUA template PASS on items 25 and 26.

### Item 25 — Software Validation Report
- All SRS requirements traced to at least one system test result (no requirement unvalidated)
- All operational scenarios defined in SVaP have been executed and results recorded
- Performance requirements met (response time, WCET, throughput, resource usage)
- Boundary value and equivalence class tests executed (§6.3.4.6, Table A.7)
- Regression tests executed (M SIL 3-4 per Table A.7 item 4)
- Non-conformances documented and dispositioned; zero open critical/high defects
- VAL release decision stated explicitly: APPROVE or REJECT (§5.1.2.8)
- Testing performed in target environment or certified high-fidelity simulation

### Item 26 — Tools Validation Report (if applicable)
- Tool qualification evidence complete for all tools used in the safety lifecycle
- Tool categories and qualification levels stated per §6.7
- Tool output errors identified and mitigated

**VMGR decision on VAL reports**:
- **APPROVE**: proceed to item † review
- **REJECT**: return to VAL with written findings; VAL reworks; QUA re-checks items 25–26;
  VER must re-issue item †; all three (items 25, 26, †) must repass QUA before VMGR
  re-reviews

---

## 7. Item † Review Criteria

**Normative basis**: §6.3.4.12, §6.3.4.13, §6.3.4.14  
**Writer**: VER  
**Phase**: 7, Track B Step B2 — after QUA check on VAL reports, before VMGR Final V&V Decision  
**Precondition**: Item † must be named in SVP (§6.2.4.2) and in SQAP.

**What item † must contain** (per §6.3.4.12–14):
- VER's review of SVaP (item 5) — was validation conducted per the approved plan? (§6.3.4.13)
- VER's review of the Software Validation Report (item 25) — are the results adequate? (§6.3.4.14)
- Statement of VER conclusion: agree or disagree with VAL's release decision

**VMGR checks in item †**:
- Item † explicitly references SVaP (item 5) — plan vs. execution consistency confirmed
- Item † explicitly references VAL report (item 25) — VER conclusion on VAL's adequacy stated
- Item † was named in SVP (§6.2.4.2) — no surprise deliverable
- Item † passed QUA template check (confirmed before VMGR review begins)
- VER's conclusion in item † is consistent with the technical evidence reviewed

**Combined review rule**: VMGR reviews item † and items 25–26 as a set. The Final V&V
Decision is issued only when all three are approved in the same review cycle.

---

## 8. Independence Enforcement Checklist

Perform before starting any V&V activity for a phase:

**VER team independence**:
- [ ] No VER team member held REQ, DES, IMP, INT, or TST role for the same component
- [ ] VER team organizational separation from development is documented (org chart reference)
- [ ] VER does not report to PM (§5.1.2.10e)

**VAL independence**:
- [ ] VAL has no development role involvement (REQ/DES/IMP/INT/TST for same system)
- [ ] VAL does not report to PM (§5.1.2.10f)
- [ ] VAL ≠ VER unless ASR has explicitly approved combination (§5.1.2.10n)

**VMGR independence**:
- [ ] VMGR has no development role involvement
- [ ] VMGR does not report to COD or PM
- [ ] VMGR ≠ ASR (ASR independently reviews VMGR's V&V output)

**If any item is unchecked**: block V&V activities; raise CRITICAL NCR via QUA; escalate
to PM for immediate Safety Authority notification. Do not proceed until resolved.

---

## 9. V&V Outcome Report to COD

After completing each phase V&V cycle, VMGR sends a structured outcome record to COD.
COD records this in `LIFECYCLE_STATE.md`.

**Standard phases (1–6, 9–10)**:

```
VMGR V&V Outcome — Phase <N>
  VER Report:  <Annex C item number> — <Document ID>
  Decision:    APPROVED | REJECTED
  Date:        <YYYY-MM-DD>
  Rationale:   <one paragraph: what was reviewed, which criteria were met or not met>
  VMGR:        <name / identifier>
```

**Phase 7 (Final V&V Decision)**:

```
VMGR Final V&V Decision — Phase 7
  VER Integration Report:  Item 23 — <Document ID>  APPROVED <date>
  VAL Validation Report:   Item 25 — <Document ID>  APPROVED <date>
  Tools Validation Report: Item 26 — <Document ID>  APPROVED <date> | N/A
  SW Val. Verification:    Item †  — <Document ID>  APPROVED <date>
  FINAL V&V DECISION:      GRANTED | REJECTED
  Date:                    <YYYY-MM-DD>
  Rationale:               <paragraph>
  VMGR:                    <name / identifier>
```

**Routing**: VMGR sends outcome to COD. COD cannot modify or override the decision.
COD records the outcome and enforces the gate accordingly.

---

## 10. Tool Integration

VMGR uses `workspace.py wf review` to record decisions in the workflow state.
Reference: `en50128-lifecycle-tool-integration` skill → workspace.py command reference.

```bash
# VMGR approves a VER Verification Report (standard phases)
python3 workspace.py wf review --item <annex_c_item> --role VMGR --approve \
  --comment "VER report technically adequate; all SIL criteria met"

# VMGR rejects a VER Verification Report
python3 workspace.py wf review --item <annex_c_item> --role VMGR --reject \
  --comment "<finding summary — specific criteria not met>"

# VMGR approves VAL reports (Phase 7)
python3 workspace.py wf review --item 25 --role VMGR --approve \
  --comment "VAL report adequate; all SRS requirements validated"

# VMGR approves item † (Phase 7)
python3 workspace.py wf review --item dagger --role VMGR --approve \
  --comment "Item † reviewed; VER conclusion consistent with VAL evidence"

# VMGR issues Final V&V Decision (Phase 7 — after all three approved)
python3 workspace.py wf final-vv-decision --role VMGR --approve \
  --comment "Items 23, 25, 26, † all approved; Final V&V Decision GRANTED"
```

Invoke CM `query-location --doc VMGR-OUTCOME` for the canonical path before writing
any VMGR outcome record to disk.
