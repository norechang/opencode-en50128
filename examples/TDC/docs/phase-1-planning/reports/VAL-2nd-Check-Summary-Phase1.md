# VAL 2nd-Check Summary — Phase 1 Planning

## Document Control

| Field | Value |
|-------|-------|
| **Document ID** | VAL-2CHECK-TDC-PHASE1-001 |
| **Version** | 1.0 |
| **Date** | 2026-03-30 |
| **Status** | FINAL |
| **Author** | Software Validator (VAL) Team |
| **Project** | TDC (Train Door Control) |
| **SIL Level** | SIL 3 |
| **Review Type** | Track B — VAL 2nd-Check (Fitness-for-Use) |
| **Phase** | Phase 1 — Planning |

---

## Executive Summary

**Active Workspace**: TDC (Train Door Control System)  
**SIL Level**: SIL 3 (Independent VAL mandatory, reports to VMGR)  
**Phase**: Phase 1 — Planning  
**Completion**: 15%

This VAL 2nd-Check Summary documents the independent fitness-for-use review of Phase 1 Planning deliverables from the **validation perspective**. VAL performed 2nd-check reviews on three documents (SQAP, SCMP, SVP) per EN 50128:2011 Annex C Table C.1.

### Review Summary

**Documents Reviewed (2nd-Check)**: 3  
**Documents Excluded**: 1 (SVaP — VAL self-authored, no 2nd-check required)

| # | Document | Annex C Item | VAL Review Type | Result |
|---|----------|--------------|-----------------|--------|
| 1 | Software Quality Assurance Plan (SQAP) | 1 | 2nd-check | ✅ **CONCUR** |
| 2 | Software Configuration Management Plan (SCMP) | 3 | 2nd-check | ✅ **CONCUR** |
| 3 | Software Verification Plan (SVP) | 4 | 2nd-check | ✅ **CONCUR** |
| 4 | Software Validation Plan (SVaP) | 5 | *Self-authored* | N/A (no 2nd-check) |

### VAL Overall Assessment

**✅ VAL CONCURS WITH ALL THREE 2nd-CHECK DOCUMENTS**

- **Total Findings**: 0 Critical, 0 Major, 3 Minor (observations only)
- **Fitness-for-Use Assessment**: ✅ All plans support successful validation of TDC system
- **Operational Fitness**: ✅ Plans adequately protect customer/operational interests
- **Safety Adequacy**: ✅ Safety requirements sufficiently addressed for validation needs
- **Cross-Plan Consistency**: ✅ All plans align from validation perspective
- **Practicality**: ✅ Approaches are practical for field validation

**VAL Recommendation to VMGR**: All Phase 1 planning documents are fit-for-use from the validation perspective. VAL recommends **APPROVAL** for COD Phase 1 gate check progression.

---

## 1. VAL 2nd-Check Scope and Methodology

### 1.1 VAL 2nd-Check Definition

Per EN 50128 §6.3 and SVaP Section 17.1, VAL 2nd-check provides a **complementary perspective** to VER 1st-check:

- **VER 1st-check** (completed): Technical correctness, normative compliance, traceability, completeness
- **VAL 2nd-check** (this review): **Fitness-for-use**, operational adequacy, customer perspective, validation support

**VAL does NOT duplicate VER technical verification.** VAL confirms plans support **intended operational use** and **successful validation** in Phase 7.

### 1.2 VAL 2nd-Check Focus Areas (SIL 3)

**Critical validation perspective items**:
1. Do plans adequately support **operational validation** in target environment (DCU hardware)?
2. Are **customer acceptance** criteria and processes clear and achievable?
3. Are **safety requirements** adequately planned for validation (SSRS → validation tests)?
4. Will the approach enable **"right product"** demonstration?
5. Are **SW/HW integration** validation provisions sufficient?
6. Is the **target DCU hardware** validation environment feasible?
7. Are **performance validation** requirements (mandatory SIL 3) achievable?
8. Do plans support VAL's **release decision authority** (AGREE/DISAGREE per §5.1.2.8)?

### 1.3 VAL Acceptance Criteria (SVaP Section 17.2.2)

**VAL 2nd-Check Rule**:
- **CONCUR**: No Major or Critical findings from validation perspective → document approved
- **QUALIFIED CONCUR**: Minor findings only → document approved with observations
- **DISSENT**: Major or Critical findings → escalate to VMGR, block gate progression

### 1.4 Independence Statement

As Software Validator for SIL 3:
- VAL is organizationally independent from development team (PM, QUA, CM, REQ, DES, IMP, TST, INT)
- VAL reports to VMGR (not PM or COD)
- VAL has NOT participated in requirements, design, implementation, integration, or verification of TDC software
- VAL 2nd-check perspective is complementary to VER 1st-check (no duplication)

---

## 2. Document Reviews

### 2.1 SQAP — Software Quality Assurance Plan (Item 1)

**Document ID**: DOC-TDC-SQAP-001 v1.0 DRAFT  
**VER 1st-Check Result**: ✅ APPROVE (0 Critical, 0 Major, 1 Minor)  
**VAL 2nd-Check Type**: Fitness-for-use from validation perspective

#### 2.1.1 Validation Perspective Assessment

**Operational Fitness**: ✅ **EXCELLENT**
- QUA format-gate review process supports VAL deliverable quality (items 25–27 in Phase 7)
- Two-track review workflow (Track A: QUA, Track B: VER/VAL) correctly separates format from technical review
- 1-Pass Rule for VER/VAL reports is practical and supports efficient validation workflow
- VAL independence requirements (Section 4.2.3) correctly specified — VAL reports to VMGR, not PM

**Customer Perspective**: ✅ **EXCELLENT**
- Quality organization structure protects customer interests through independent V&V (VMGR authority)
- Process audits (monthly at SIL 3) provide oversight of development quality
- Metrics collection (Section 15) enables customer visibility into project health
- NCR management (Section 14) ensures defects are tracked to closure before release

**Safety Adequacy**: ✅ **EXCELLENT**
- All EN 50128 Table A.9 mandatory techniques for SIL 3 correctly identified
- Safety-critical document review provisions (Section 11) include FMEA/FTA checklist
- QUA role boundaries (format-gate only) prevent QUA from diluting VER/VAL technical safety review
- VMGR final V&V decision authority protects safety assurance (cannot be overridden by PM/COD)

**Validation Support**: ✅ **EXCELLENT**
- SQAP Section 5.2 Phase 7 activities correctly describe VAL Track B coordination
- 1-Pass Rule (Section 8.2.2) applies to VAL reports (items 25, 26) — clear acceptance criteria
- Process audits will verify validation evidence is properly collected and retained
- Quality metrics (Section 15) will track validation test coverage and defect closure

**Cross-Plan Consistency**: ✅ Verified — SQAP references SCMP, SVP, SVaP correctly

#### 2.1.2 VAL Findings

**MINOR-VAL-SQAP-001**: SQAP Section 5.2 (Phase 7 QUA activities) states "This is the only phase where QUA checks VAL-authored formal Validation Reports" but does not clarify that QUA uses the 1-Pass Rule for VAL reports (items 25, 26). **Observation**: This is correctly stated in Section 8.2.2 (1-Pass Rule); cross-reference would improve clarity for readers.

**Impact**: MINOR — Content is correct; cross-reference would improve navigability.

#### 2.1.3 VAL 2nd-Check Result

**✅ CONCUR** — SQAP is fit-for-use from validation perspective. The plan adequately supports:
- VAL independence requirements (mandatory SIL 3)
- VAL deliverable quality assurance (QUA 1-Pass Rule)
- Customer/safety protection through independent V&V
- Validation evidence collection and retention

No rework required. Minor finding is advisory only.

---

### 2.2 SCMP — Software Configuration Management Plan (Item 3)

**Document ID**: DOC-TDC-SCMP-001 v1.0 DRAFT  
**VER 1st-Check Result**: ✅ APPROVE (0 Critical, 0 Major, 1 Minor)  
**VAL 2nd-Check Type**: Fitness-for-use from validation perspective

#### 2.2.1 Validation Perspective Assessment

**Operational Fitness**: ✅ **EXCELLENT**
- Baseline management procedure (Section 7) supports VAL's need for stable release baseline
- Change control process (Section 8) ensures VAL can track configuration changes during validation
- CCB operation (Section 8.4) correctly assigns COD lifecycle authority (PM cannot override)
- Backup and recovery procedures (Section 12) protect validation evidence from loss

**Customer Perspective**: ✅ **EXCELLENT**
- Configuration Item identification scheme (Section 5) is clear and customer-accessible
- Baseline manifests (Appendix C) provide customer visibility into release contents
- Change Request template (Appendix B) addresses customer impact assessment (nine required aspects)
- Configuration status accounting (Section 14) enables customer to track project state

**Safety Adequacy**: ✅ **EXCELLENT**
- Baseline management preserves reproducibility per §9.1.4.3 — critical for safety case
- Traceability management (Section 10.4) supports VAL's end-to-end traceability verification
- Change control nine required aspects (§6.6.4.1) include safety impact analysis
- Phase re-entry procedure (Section 8.3) protects safety assurance when changes occur

**Validation Support**: ✅ **EXCELLENT**
- SCMP provides stable baseline for VAL Phase 7 validation activities
- Version control (Git) enables VAL to reproduce exact release configuration
- Baseline tag naming convention (Section 5.5) clearly identifies release baseline (`TDC-BL-RELEASE-v1.0`)
- Evidence artifact retention (Section 5.1) supports VAL evidence preservation

**Cross-Plan Consistency**: ✅ Verified — SCMP references SQAP, SVP, SVaP correctly

#### 2.2.2 VAL Findings

**MINOR-VAL-SCMP-001**: SCMP Section 7.2 defines Phase 7 baseline as "RELEASE" but does not explicitly state that this is the **critical baseline for VAL validation activities**. **Observation**: VAL will validate against `TDC-BL-RELEASE-v1.0` baseline; clarifying this in Section 7.2 would improve operational clarity.

**Impact**: MINOR — Baseline naming is correct; additional context would improve understanding for validation team.

#### 2.2.3 VAL 2nd-Check Result

**✅ CONCUR** — SCMP is fit-for-use from validation perspective. The plan adequately supports:
- Stable release baseline for validation (Phase 7)
- Configuration traceability during validation
- Customer visibility into release contents
- Safety assurance through reproducible baselines

No rework required. Minor finding is advisory only.

---

### 2.3 SVP — Software Verification Plan (Item 4)

**Document ID**: DOC-TDC-SVP-001 v1.0 DRAFT  
**VER 2nd-Check Result**: ✅ APPROVE (VER self-authored, performed 2nd-check)  
**VAL 2nd-Check Type**: Fitness-for-use from validation perspective

#### 2.3.1 Validation Perspective Assessment

**Operational Fitness**: ✅ **EXCELLENT**
- SVP verification activities (Phases 2–6) provide foundation for VAL validation activities (Phase 7)
- VER independence structure (Section 4.1) mirrors VAL independence — both report to VMGR
- VER 1-Pass Rule (Section 16.2.1) aligns with VAL 1-Pass Rule (SVaP Section 17.2.2)
- SVP Section 11.7 (Phase 7) correctly describes VER/VAL coordination in Track B

**Customer Perspective**: ✅ **EXCELLENT**
- Verification vs validation boundary (Section 1.4 table) clearly communicates roles to customer
- VER provides technical correctness assurance before VAL customer-facing validation
- VER traceability verification (Section 10) supports customer confidence in requirements coverage
- Independent VER reporting to VMGR (not PM) protects customer interests

**Safety Adequacy**: ✅ **EXCELLENT**
- All EN 50128 Table A.5 mandatory techniques for SIL 3 correctly applied by VER
- Static analysis (MISRA C, Cppcheck, Clang) ensures code safety before VAL validation
- Test coverage (100% statement/branch/condition) provides safety assurance foundation
- FMEA on safety-critical modules (Section 6.6) supports VAL safety validation scenarios

**Validation Support**: ✅ **EXCELLENT**
- SVP Section 11.7 describes Phase 7 VER activities supporting VAL:
  - VER produces SW Integration Verification Report (item 23) in Track B Step B1
  - VER produces SW Validation Verification Report (item †) in Track B Step B2
  - VER reviews VAL deliverables (items 25, 26) for technical correctness
- VER verification evidence (coverage, MISRA, traceability) enables VAL to focus on operational validation
- VER/VAL independence separation is correctly maintained — no role conflicts

**Cross-Plan Consistency**: ✅ Verified — SVP references SQAP, SCMP, SVaP correctly

#### 2.3.2 VAL Findings

**MINOR-VAL-SVP-001**: SVP Section 1.4 (Verification vs Validation Boundary) table includes row "Release decision" showing VER=No, VAL=Yes. **Observation**: While technically correct (VAL has final AGREE/DISAGREE authority per §5.1.2.8), it may be helpful to clarify that VER's APPROVE recommendation is a prerequisite for VAL's release decision. VAL cannot release software that VER has rejected.

**Impact**: MINOR — The authority structure is correct; additional context would clarify the sequential relationship (VER APPROVE → VAL AGREE).

#### 2.3.3 VAL 2nd-Check Result

**✅ CONCUR** — SVP is fit-for-use from validation perspective. The plan adequately supports:
- VER activities provide foundation for VAL validation
- VER/VAL independence properly maintained
- Customer understanding of verification vs validation roles
- Phase 7 VER/VAL coordination workflow

No rework required. Minor finding is advisory only.

---

### 2.4 SVaP — Software Validation Plan (Item 5)

**Document ID**: DOC-TDC-SVaP-001 v1.0 DRAFT  
**VER 1st-Check Result**: ✅ APPROVE (0 Critical, 0 Major, 1 Minor)  
**VAL 2nd-Check Type**: **N/A — VAL self-authored this document**

Per EN 50128 Annex C Table C.1 and `deliverables/planning/Software-Validation-Plan.yaml`:
- **Written By**: VAL (this document is VAL-authored)
- **1st Check**: VER (completed — result: APPROVE)
- **2nd Check**: `null` — **No 2nd-check required for SVaP**

**VAL Assessment**: SVaP self-authorship prevents VAL from performing 2nd-check (independence conflict). VER performed 1st-check and approved SVaP. This deviation is documented in SQAP Section 20 (Platform Deviations) and will be reviewed by ISA in Phase 8.

**No VAL 2nd-check performed on item 5.**

---

## 3. VER Verification Report Review

### 3.1 Software Quality Assurance Verification Report (SQAVR)

**Document ID**: DOC-TDC-SQAVR-002 v1.0 DRAFT  
**Author**: VER Team  
**VER Review Results**: 4/4 documents APPROVE (0 Critical, 0 Major, 4 Minor)

#### 3.1.1 VAL Assessment of VER Report

**From Validation Perspective**:

**VER Findings Appropriateness**: ✅ **APPROPRIATE**
- VER identified 4 MINOR findings (observations only) — all are editorial/clarification improvements
- No Critical or Major findings — consistent with high-quality planning deliverables
- VER findings focus on technical correctness and normative compliance (appropriate for 1st-check)
- VER did NOT overstep into validation fitness-for-use domain (correct role separation)

**VER Conclusions Support Validation Needs**: ✅ **SUPPORTIVE**
- VER confirmed all planning documents are technically correct and SIL 3 compliant
- VER verified EN 50128 mandatory techniques (Tables A.5, A.7, A.9) correctly identified
- VER confirmed VAL independence requirements correctly specified
- VER traceability verification (system docs → planning docs) provides foundation for validation

**VER Recommendations Consider Operational Fitness**: ✅ **ADEQUATE**
- VER Section 11.4 recommendations to VMGR include operational feasibility assessment
- VER confirmed all approaches are "practical and achievable for SIL 3 project"
- VER did not identify any technical barriers that would prevent successful validation

#### 3.1.2 VAL Concurrence with VER Findings

VAL has reviewed all 4 VER MINOR findings and **CONCURS** with VER assessment:

| VER Finding ID | Document | VAL Concurrence | VAL Comment |
|----------------|----------|-----------------|-------------|
| MINOR-SQAVR-SQAP-001 | SQAP | ✅ CONCUR | Deviation rationale enhancement is reasonable |
| MINOR-SQAVR-SCMP-001 | SCMP | ✅ CONCUR | Document registry reference would improve clarity |
| MINOR-SQAVR-SVP-001 | SVP | ✅ CONCUR | Phase 6/7 report clarification is helpful |
| MINOR-SQAVR-SVaP-001 | SVaP | ✅ CONCUR | WCET tool clarification is useful for validation planning |

All VER findings are advisory only and do not require rework before gate check.

---

## 4. Cross-Plan Consistency (Validation View)

### 4.1 VAL Independence Provisions

**Consistency Check**: Are VAL independence requirements consistently specified across all four plans?

| Plan | VAL Independence Statement | Reporting Line | Consistent? |
|------|---------------------------|----------------|-------------|
| SQAP | Section 4.2.3 — VAL reports to VMGR (not PM) | VAL → VMGR → Safety Authority | ✅ YES |
| SCMP | Section 4.3 — VMGR is independent from PM/COD | VMGR independent | ✅ YES |
| SVP | Section 1.4 — VAL performs validation, VER performs verification | Roles separated | ✅ YES |
| SVaP | Section 4.1.1 — VAL reports to VMGR, NOT PM | VAL → VMGR → Safety Authority | ✅ YES |

**Assessment**: ✅ **CONSISTENT** — All four plans correctly specify VAL independence per §5.1.2.10f (SIL 3 mandatory).

### 4.2 Phase 7 Validation Provisions

**Consistency Check**: Do all plans correctly describe Phase 7 validation activities?

| Plan | Phase 7 Validation Description | VAL Assessment |
|------|-------------------------------|----------------|
| SQAP | Section 5.2 Phase 7 — QUA checks VAL deliverables (items 25, 26), 1-Pass Rule | ✅ Correct |
| SCMP | Section 7.2 — RELEASE baseline (`TDC-BL-RELEASE-v1.0`) | ✅ Correct |
| SVP | Section 11.7 — VER produces items 23, † ; VAL produces items 25, 26, 27 | ✅ Correct |
| SVaP | Section 8.7 — VAL validation activities, release decision (AGREE/DISAGREE) | ✅ Correct |

**Assessment**: ✅ **CONSISTENT** — All four plans correctly describe Phase 7 validation workflow and VAL role.

### 4.3 Customer Acceptance Provisions

**Consistency Check**: Do plans adequately address customer acceptance criteria?

| Plan | Customer Acceptance Provision | VAL Assessment |
|------|------------------------------|----------------|
| SQAP | N/A (process plan) | N/A |
| SCMP | Section 8.2 — Change Request template includes customer impact | ✅ Adequate |
| SVP | Section 1.4 — VER not customer-facing | ✅ Correct |
| SVaP | Section 9 — Customer representative witnesses acceptance tests, signs certificate | ✅ Excellent |

**Assessment**: ✅ **ADEQUATE** — SVaP (item 5) correctly defines customer acceptance testing. Other plans appropriately defer to SVaP.

---

## 5. SIL 3 Validation Readiness Assessment

### 5.1 Operational Validation Environment

**Assessment Criterion**: Do plans support operational validation in target environment (DCU hardware)?

| Plan | Target Environment Support | VAL Assessment |
|------|---------------------------|----------------|
| SVaP | Section 7 — DCU hardware mandatory, -25°C to +55°C, 24 VDC | ✅ **EXCELLENT** |
| SVP | Section 1.4 — Verification may use development environment | ✅ Correct (not validation) |
| SCMP | Section 12 — Backup protects validation evidence | ✅ Supportive |
| SQAP | N/A | N/A |

**Readiness**: ✅ **READY** — SVaP Section 7 correctly mandates target DCU hardware for validation.

### 5.2 Safety Requirements Validation

**Assessment Criterion**: Are safety requirements adequately planned for validation?

| Plan | Safety Validation Support | VAL Assessment |
|------|--------------------------|----------------|
| SVaP | Section 11 — 100% SSRS coverage, hazard traceability (HAZ-001 to HAZ-009) | ✅ **EXCELLENT** |
| SVP | Section 6.6 — FMEA on safety-critical modules | ✅ Supportive |
| SQAP | Section 16 — Table A.9 mandatory safety techniques | ✅ Supportive |
| SCMP | Section 10.4 — Traceability maintenance | ✅ Supportive |

**Readiness**: ✅ **READY** — SVaP Section 11 mandates 100% SSRS coverage with hazard traceability.

### 5.3 Performance Validation (Mandatory SIL 3)

**Assessment Criterion**: Is performance validation adequately planned?

| Plan | Performance Validation Support | VAL Assessment |
|------|-------------------------------|----------------|
| SVaP | Section 10 — Timing, WCET, load, resource usage, 72-hour reliability | ✅ **EXCELLENT** |
| SVP | Section 7.6 — WCET analysis (VER timing bounds check) | ✅ Complementary |
| SQAP | N/A | N/A |
| SCMP | N/A | N/A |

**Readiness**: ✅ **READY** — SVaP Section 10 comprehensively addresses performance validation per EN 50128 Table A.7 (mandatory SIL 3).

### 5.4 Release Decision Authority

**Assessment Criterion**: Do plans support VAL's release decision authority (AGREE/DISAGREE per §5.1.2.8)?

| Plan | Release Authority Support | VAL Assessment |
|------|--------------------------|----------------|
| SVaP | Section 8.7 — VAL release decision is FINAL, cannot be overridden | ✅ **EXCELLENT** |
| SQAP | Section 4.2.3 — VAL reports to VMGR, not PM | ✅ Supportive |
| SVP | Section 1.4 — VER confirms correctness, VAL gives release decision | ✅ Supportive |
| SCMP | Section 8.4 — CCB cannot override VAL decision | ✅ Supportive |

**Readiness**: ✅ **READY** — All plans correctly preserve VAL's final release authority.

---

## 6. VAL Findings Summary

### 6.1 Findings by Severity

| Severity | Count | Impact |
|----------|-------|--------|
| **CRITICAL** | 0 | No gate blockers |
| **MAJOR** | 0 | No rework required |
| **MINOR** | 3 | Observations only — advisory improvements |

### 6.2 Detailed VAL Findings

| Finding ID | Document | Section | Severity | Description | Recommendation |
|------------|----------|---------|----------|-------------|----------------|
| **MINOR-VAL-SQAP-001** | SQAP | 5.2 | MINOR | Phase 7 QUA activity description could cross-reference 1-Pass Rule | Add cross-reference to Section 8.2.2 |
| **MINOR-VAL-SCMP-001** | SCMP | 7.2 | MINOR | RELEASE baseline not explicitly identified as critical for validation | Clarify VAL validates against `TDC-BL-RELEASE-v1.0` |
| **MINOR-VAL-SVP-001** | SVP | 1.4 | MINOR | Release decision boundary could clarify VER APPROVE prerequisite | Clarify sequential relationship: VER → VAL |

### 6.3 Findings Disposition

**All VAL findings are MINOR (observations only)**:
- No rework required before Phase 1 gate check
- Findings are advisory improvements for operational clarity
- All plans are fit-for-use from validation perspective

---

## 7. VAL Recommendation to VMGR

### 7.1 Overall VAL Assessment

**✅ VAL CONCURS WITH ALL THREE 2nd-CHECK DOCUMENTS**

VAL has performed fitness-for-use review of:
1. Software Quality Assurance Plan (DOC-TDC-SQAP-001)
2. Software Configuration Management Plan (DOC-TDC-SCMP-001)
3. Software Verification Plan (DOC-TDC-SVP-001)

**VAL 2nd-Check Results**:
- **3 documents reviewed**: All ✅ CONCUR
- **0 Critical findings** from validation perspective
- **0 Major findings** from validation perspective
- **3 Minor findings** (observations only — no rework required)

### 7.2 Fitness-for-Use Confirmation

**VAL confirms all Phase 1 planning documents are FIT-FOR-USE** from validation perspective:

1. **Operational Fitness**: ✅ Plans support successful validation in target environment
2. **Customer Perspective**: ✅ Plans adequately protect customer interests
3. **Safety Adequacy**: ✅ Safety requirements sufficiently addressed for validation needs
4. **Validation Support**: ✅ Plans enable VAL Phase 7 validation activities
5. **Cross-Plan Consistency**: ✅ All plans align from validation perspective
6. **Practicality**: ✅ Approaches are practical for field validation

### 7.3 SIL 3 Validation Readiness

**VAL confirms TDC project is READY for Phase 1 gate progression** with respect to validation provisions:

- ✅ VAL independence requirements correctly specified (mandatory SIL 3)
- ✅ Target environment validation approach feasible (DCU hardware)
- ✅ Performance validation adequately planned (mandatory SIL 3)
- ✅ Safety requirements validation provisions sufficient
- ✅ Customer acceptance testing approach appropriate
- ✅ VAL release decision authority preserved

### 7.4 VAL Recommendation

**VAL recommends VMGR approval of Phase 1 Planning deliverables** for the following reasons:

1. **Fitness-for-Use**: All planning documents support intended operational use and successful validation
2. **Independence**: VAL independence requirements (SIL 3 mandatory) correctly specified across all plans
3. **Validation Provisions**: Phase 7 validation activities adequately planned (target environment, performance, safety)
4. **Customer Protection**: Plans protect customer interests through independent V&V and acceptance testing
5. **Safety Assurance**: Safety requirements validation provisions are sufficient for SIL 3
6. **Findings**: 0 Critical, 0 Major, 3 Minor (observations only — no rework required)

**VAL Decision**: ✅ **APPROVE — READY FOR PHASE 1 GATE CHECK**

---

## 8. Next Steps

### 8.1 Immediate Actions

1. **VMGR Review**: VMGR reviews this VAL 2nd-Check Summary alongside VER SQAVR (item 2)
2. **VMGR Decision**: VMGR issues FINAL V&V decision to COD (SIL 3 — cannot be overridden)
3. **COD Gate Check**: After VMGR approval, COD executes `@cod gate-check planning`

### 8.2 Phase 2 Preparation

After Phase 1 gate passes:
1. PM executes `@pm execute-phase 2` (Requirements Specification)
2. VAL performs 2nd-check on Phase 2 deliverables:
   - SRS (item 6)
   - Overall Test Specification (item 7)
   - Requirements Verification Report (item 8)

---

## 9. References

### 9.1 Normative References

| Reference | Title | Version |
|-----------|-------|---------|
| EN 50128:2011 | Railway applications — Software for railway control and protection systems | 2011 |
| EN 50126-1:2017 | Railway applications — RAMS — Part 1: Generic RAMS process | 2017 |
| EN 50126-2:2017 | Railway applications — RAMS — Part 2: Systems approach to safety | 2017 |

### 9.2 Project Documents Reviewed

| Document ID | Title | Version | Review Date |
|-------------|-------|---------|-------------|
| DOC-TDC-SQAP-001 | Software Quality Assurance Plan | 1.0 DRAFT | 2026-03-30 |
| DOC-TDC-SCMP-001 | Software Configuration Management Plan | 1.0 DRAFT | 2026-03-30 |
| DOC-TDC-SVP-001 | Software Verification Plan | 1.0 DRAFT | 2026-03-30 |
| DOC-TDC-SVaP-001 | Software Validation Plan | 1.0 DRAFT | 2026-03-30 (no 2nd-check) |
| DOC-TDC-SQAVR-002 | Software Quality Assurance Verification Report | 1.0 DRAFT | 2026-03-30 (reviewed) |

### 9.3 Process Documents

| Document | Location |
|----------|----------|
| Validation Skill | `.opencode/skills/en50128-validation/SKILL.md` |
| VnV Process Reference | `tasks/VnV-PROCESS.md` |
| Phase 1 Planning Activity | `activities/phase-1-planning.yaml` |
| Lifecycle State | `examples/TDC/LIFECYCLE_STATE.md` |

---

## Appendix A: VAL Independence Statement

**Independence Declaration** (EN 50128 §5.1.2.10f):

I, the undersigned Software Validator (VAL), declare that:

1. **Organizational Independence**: I am organizationally independent from the TDC project development team (PM, QUA, CM, REQ, DES, IMP, TST, INT) and verification team (VER).

2. **Reporting Line**: I report exclusively to the V&V Manager (VMGR), who is independent from the Project Manager (PM) and the Lifecycle Coordinator (COD).

3. **Role Separation**: I have NOT performed and SHALL NOT perform any of the following roles for the TDC project:
   - Requirements Engineer (REQ)
   - Designer (DES)
   - Implementer (IMP)
   - Tester (TST)
   - Integrator (INT)
   - Verifier (VER)

4. **Authority**: I have the authority to issue release decision (AGREE/DISAGREE per §5.1.2.8). My release decision SHALL NOT be overridden by PM, COD, or VMGR.

5. **2nd-Check Scope**: I performed 2nd-check on items 1, 3, 4 (SQAP, SCMP, SVP). I did NOT 2nd-check item 5 (SVaP) because I authored it (independence conflict).

**VAL Signature**: _____________  
**Date**: 2026-03-30

---

**End of VAL 2nd-Check Summary — Phase 1 Planning**

**Distribution**:
- VMGR (V&V Manager) — for final V&V decision
- COD (Lifecycle Coordinator) — for Phase 1 gate check preparation
- VER (Software Verifier) — for information
- PM (Project Manager) — for information (reports to COD, not VAL)
- QUA (Quality Assurance) — for information
- CM (Configuration Manager) — for baseline preparation

**Retention**: This report SHALL be archived under CM control per SCMP Section 14 and retained for project lifetime + 10 years per EN 50128 §9.3.
