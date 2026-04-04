# Software Change Control Request (CCR)

**DOCUMENT TYPE**: Software Change Control Request  
**EN 50128 REFERENCE**: EN 50128:2011 §6.6.4.1 (Change Control), §6.6.4.2 (Re-entry)  
**PROJECT**: TDC (Train Door Control System)  
**SIL LEVEL**: 3

---

## DOCUMENT CONTROL

| Field | Value |
|-------|-------|
| **CCR ID** | CCR-SVP-001 |
| **Date Submitted** | 2026-04-04 |
| **Requester** | Quality Assurance Engineer (QUA) |
| **Requester Role** | QUA |
| **Document Affected** | Software Verification Plan (SVP) |
| **Document ID** | DOC-SVP-2026-001 |
| **Document Item** | Annex C Item 4 |
| **Current Version** | v1.0 |
| **Proposed Version** | v1.1 |
| **Change Type** | Correction (Error Fix) |
| **Priority** | Medium |
| **Status** | APPROVED |

---

## CCB APPROVAL

| Field | Value |
|-------|-------|
| **CCB Chair** | Project Manager (PM) |
| **CCB Meeting Date** | 2026-04-04 |
| **Decision** | **APPROVED** |
| **Authorized By** | PM (CCB Chair) |
| **Authorization Date** | 2026-04-04 |

---

## §6.6.4.1 NINE REQUIRED ASPECTS

### (a) Unique Identification of the Change

**CCR ID**: CCR-SVP-001  
**Document**: Software Verification Plan (DOC-SVP-2026-001)  
**Baseline**: Phase 1 Planning Baseline (planning-baseline)  
**Version**: v1.0 → v1.1

### (b) Recording of the Reasons for the Change

**Reason**: Correction of normative standard citations in Section 3.3 Table (Test Coverage Techniques)

**Defects Identified**:

1. **Error 1 — Fabricated row 4 (MC/DC Coverage)** (Line 362):
   - Current text: `| **4** | MC/DC Coverage | A.21 | R | **N/A** | — | Not adopted for SIL 3 (HR threshold met by compound condition) |`
   - Issue: MC/DC (Modified Condition/Decision Coverage) is a DO-178C aviation standard term. It does NOT exist in EN 50128:2011 Table A.21. This row was fabricated and must be removed.
   - Impact: Non-compliance with EN 50128:2011 requirements; incorrect citation of non-existent standard technique.

2. **Error 2 — Wrong SIL 3 recommendation level for rows 1 and 2** (Lines 359-360):
   - Row 1 (Statement Coverage): Current shows "HR" but EN 50128:2011 Table A.21 row 1 specifies **M** (Mandatory) for SIL 3-4
   - Row 2 (Branch Coverage): Current shows "HR" but EN 50128:2011 Table A.21 row 2 specifies **M** (Mandatory) for SIL 2-4
   - Impact: Understates mandatory requirements; creates compliance risk for SIL 3 project.

**Discovery Source**: Independent audit of SVP Section 3.3 against EN 50128:2011 Table A.21 (Test Coverage for Code)

### (c) Analysis of the Consequences of the Change

**Impact Assessment**:

| Category | Impact | Details |
|----------|--------|---------|
| **Project Schedule** | None | Correction does not affect timeline |
| **Project Resources** | None | No additional resources required |
| **Project Targets** | None | Project-defined 100% coverage targets at lines 367-369 remain unchanged and are CORRECT |
| **SIL 3 Compliance** | **Positive** | Corrects normative standard citations; improves EN 50128:2011 compliance |
| **Safety Functions** | None | No impact on safety requirements or architecture |
| **Verification Activities** | None | Verification methods unchanged; only table citations corrected |
| **Validation Activities** | None | No impact on Software Validation Plan (SVaP) |
| **Other Deliverables** | None | No other Phase 1-5 deliverables affected |
| **Traceability** | None | No traceability matrix changes required |

**Functional Change**: NO — This is a documentation correction only. The project-defined coverage targets (100% statement, 100% branch, 100% compound condition) specified in lines 367-369 are already correct and remain unchanged.

**Re-entry Scope** (§6.6.4.2): None required. This is an editorial correction to a Phase 1 planning document with no impact on Phase 2-5 completed work. Phase 5 gate-check may proceed without re-work.

### (d) Approval of the Change by Authorised Personnel

**CCB Approval**:
- **CCB Chair**: Project Manager (PM)
- **CCB Date**: 2026-04-04
- **Decision**: **APPROVED**
- **Rationale**: Editorial correction to normative standard citations; no functional impact; improves EN 50128:2011 compliance; no re-work required for Phases 2-5.

**Approvals Required** (per SCMP §6.2):
- [x] CCB Chair (PM) — APPROVED 2026-04-04
- [x] Configuration Manager (CM) — APPROVED 2026-04-04
- [ ] VMGR Technical Review — NOT REQUIRED (editorial change per §6.6.4.1(c))

### (e) Updating of All Affected Documents

**Documents to Update**:

| Document | Version | Action | Responsible |
|----------|---------|--------|-------------|
| Software Verification Plan (DOC-SVP-2026-001) | v1.0 → v1.1 | Apply corrections to Section 3.3 Table | CM |
| DOC-SVP-2026-001.yaml (workflow file) | N/A | Update version to v1.1; add CCR-SVP-001 note | CM |
| LIFECYCLE_STATE.md | N/A | Add Phase 1 note: SVP updated to v1.1 via CCR-SVP-001 | CM |

**Documents NOT Affected**:
- All Phase 2-5 deliverables (SRS, OSTS, SAS, SDS, SIS, SCDS, SCTS, source code, test reports, verification reports)
- No other Phase 1 planning documents (SQAP, SCMP, SVaP)

### (f) Recording of All Affected Software Items (CIs)

**Configuration Items Affected**:

| CI ID | CI Name | Version | Change |
|-------|---------|---------|--------|
| DOC-SVP-2026-001 | Software Verification Plan | v1.0 → v1.1 | Section 3.3 Table corrections (3 lines changed, 1 row removed) |

**Total CIs Affected**: 1

### (g) Implementation, Verification and Test of the Change

**Implementation Steps**:

1. **Apply corrections to SVP**:
   - Remove row 4 (MC/DC Coverage) from Section 3.3 Table (Line 362)
   - Fix row 1: Change "HR" to "M" in SIL 3 column (Line 359)
   - Fix row 2: Change "HR" to "M" in SIL 3 column (Line 360)
   - Update Version History: Add v1.1 revision entry
   - Update Document Control: Change version to v1.1

2. **Update workflow YAML**: Update DOC-SVP-2026-001.yaml to reflect v1.1 and add CCR-SVP-001 note

3. **Update LIFECYCLE_STATE.md**: Add Phase 1 note about SVP v1.1 via CCR-SVP-001

**Verification**:
- CM to verify: All 3 table rows corrected per EN 50128:2011 Table A.21
- CM to verify: Version metadata updated (v1.0 → v1.1)
- CM to verify: Revision history entry added
- CM to verify: Workflow YAML and LIFECYCLE_STATE.md updated

**Testing**: Not applicable (documentation-only change)

**Verification Status**: ✅ COMPLETE (2026-04-04)

### (h) Reporting to All Relevant Parties

**Notification Recipients**:

| Role | Name/Agent | Notification Method | Status |
|------|------------|-------------------|--------|
| Project Manager (CCB Chair) | PM | CCR document approval | ✅ COMPLETE |
| Configuration Manager | CM | CCR document author + implementer | ✅ COMPLETE |
| Verifier | VER | Email notification (SVP is Item 4, VER-authored) | PENDING |
| V&V Manager | VMGR | Email notification (VMGR approved SVP v1.0) | PENDING |
| Lifecycle Coordinator | COD | Email notification (gate-check affected) | PENDING |
| Quality Assurance | QUA | CCR document requester | ✅ COMPLETE |

**Notification Date**: 2026-04-04

### (i) Maintaining Traceability of the Change Throughout the Lifecycle

**Traceability Record**:

| Trace Aspect | Value |
|--------------|-------|
| **Change Origin** | QUA independent audit of SVP Section 3.3 vs. EN 50128:2011 Table A.21 |
| **Change Approval** | CCB (PM chair) approved 2026-04-04 |
| **Change Implementation** | CM applied corrections 2026-04-04 |
| **Version Control** | DOC-SVP-2026-001 v1.0 → v1.1 |
| **Baseline Impact** | Phase 1 Planning Baseline updated (planning-baseline) |
| **Downstream Impact** | None — Phases 2-5 deliverables unaffected |
| **Gate Impact** | Phase 5 gate-check may proceed without re-work |
| **Traceability Matrix** | No changes required (no requirement or test case changes) |

**VCS Record**: Git commit with message: "CCR-SVP-001: Correct SVP Section 3.3 Table A.21 citations (v1.1)"

---

## DETAILED CHANGES

### Section 3.3 Test Coverage Techniques (Table)

**Line 359** — Row 1 (Statement Coverage):

```diff
- | **1** | Statement Coverage | A.21 | HR | **100%** | gcov/lcov | 5 (unit tests) |
+ | **1** | Statement Coverage | A.21 | M | **100%** | gcov/lcov | 5 (unit tests) |
```

**Line 360** — Row 2 (Branch Coverage):

```diff
- | **2** | Branch Coverage | A.21 | HR | **100%** | gcov/lcov | 5 (unit tests) |
+ | **2** | Branch Coverage | A.21 | M | **100%** | gcov/lcov | 5 (unit tests) |
```

**Line 362** — Row 4 (MC/DC Coverage) — **REMOVED**:

```diff
- | **4** | MC/DC Coverage | A.21 | R | **N/A** | — | Not adopted for SIL 3 (HR threshold met by compound condition) |
```

**Lines 367-369** — Project Coverage Targets — **UNCHANGED** (already correct):

```
- **Statement coverage**: ≥ 100% for all safety-critical modules (door control logic, emergency release, safety interlocks)
- **Branch coverage**: ≥ 100% for all safety-critical modules
- **Compound condition coverage**: ≥ 100% for Boolean expressions with multiple conditions in safety-critical modules
```

### Document Control Section

**Line 16** — Version:

```diff
- | **Version** | 1.0 |
+ | **Version** | 1.1 |
```

**Line 17** — Date:

```diff
- | **Date** | 2026-04-02 |
+ | **Date** | 2026-04-04 |
```

### Version History Section

**New Row**:

```markdown
| 1.1 | 2026-04-04 | VER/CM | CCR-SVP-001 — Corrected Table A.21 SIL 3 recommendation levels (Statement=M, Branch=M); removed fabricated MC/DC row (not in EN 50128:2011) | CCB (PM) |
```

---

## CONFIGURATION STATUS AFTER CHANGE

| Document | Old Version | New Version | Status | Baseline |
|----------|-------------|-------------|--------|----------|
| Software Verification Plan (DOC-SVP-2026-001) | v1.0 | v1.1 | UPDATED | planning-baseline (updated) |
| DOC-SVP-2026-001.yaml | N/A | N/A | UPDATED | N/A |
| LIFECYCLE_STATE.md | N/A | N/A | UPDATED | N/A |

---

## ATTACHMENTS

1. EN 50128:2011 Table A.21 (Test Coverage for Code) — normative reference
2. SVP v1.0 Section 3.3 (original) — lines 355-378
3. SVP v1.1 Section 3.3 (corrected) — lines 355-377 (1 row removed)

---

## CHANGE CONTROL RECORD SIGNATURE

**Configuration Manager**: CM  
**Date**: 2026-04-04  
**Status**: COMPLETE

**CCB Chair (Project Manager)**: PM  
**Date**: 2026-04-04  
**Approval**: APPROVED

---

**END OF DOCUMENT**
