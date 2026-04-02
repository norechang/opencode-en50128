# Software Quality Assurance Verification Report

**Document ID:** DOC-SQAVR-2026-001  
**Document Type:** Software-Quality-Assurance-Verification-Report  
**Phase:** Phase 1 - Planning  
**EN 50128 Reference:** Annex C #2, Section 6.2.4.10-11, 6.5.4.7-8

---

## Document Control

**Document ID:** DOC-SQAVR-2026-001  
**Version:** 1.0  
**Date:** 2026-04-02  
**Author:** VER  
**Status:** Baseline

**Configuration Item:** DOC-SQAVR-2026-001  
**Baseline:** planning-baseline (Gate 1)

### Version History

| Version | Date | Author | Reviewer | Approver | Changes |
|---------|------|--------|----------|----------|---------|
| 0.1 | 2026-04-02 | VER | QUA | VMGR | Initial draft |
| 1.0 | 2026-04-02 | VER | QUA | VMGR | Baseline version for Phase 1 gate |

---

## Approvals

**EN 50128 Annex C Table C.1 Signature Chain**

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Written By: Software Verifier | [VER Name] | _____________ | 2026-04-02 |
| 1st Check: Software Verifier | [VER Name] | _____________ | 2026-04-02 |
| 2nd Check: Software Validator | [VAL Name] | _____________ | [PENDING] |

**Notes:**
- Signature authority per EN 50128 Annex C Table C.1 and project SQAP
- For SIL 3: Independence requirements apply per EN 50128 §6.2 (Verification) and §6.3 (Validation)
- VER authors and performs 1st Check; VAL performs 2nd Check; VMGR approves

---

## 1. Executive Summary

**Project:** TDC (Train Door Control System)  
**SIL Level:** 3  
**Verification Date:** 2026-04-02  
**Verifier:** [VER Name]  
**Verification Scope:** 
- Item 1: Software Quality Assurance Plan (DOC-SQAP-2026-001)
- Item 3: Software Configuration Management Plan (DOC-SCMP-2026-001)
- Item 5: Software Validation Plan (DOC-SVaP-2026-001)

**EXCLUDED FROM SCOPE (Independence Constraint):**
- Item 4: Software Verification Plan (DOC-SVP-2026-001) — **VER authored this document per §6.2.4.2; VER cannot self-check own plan** (deviation D8)

**Overall Verification Result:** **APPROVE**

**Summary:**  
The Verifier has reviewed three of the four QUA-accepted planning documents (items 1, 3, 5) for Phase 1 of the TDC project (SIL 3). All three documents fully comply with EN 50128:2011 requirements and demonstrate comprehensive, internally consistent planning for quality assurance, configuration management, and validation. No critical or major non-conformities were found. Minor observations have been documented for future improvement but do not impact approval.

**Key Findings:**
- **SQAP (item 1):** PASS — Comprehensive coverage of EN 50128 §6.5 requirements; SIL 3 obligations clearly documented; independence structure compliant.
- **SCMP (item 3):** PASS — Complete CM processes per §6.6; traceability management (T1–T15) fully defined; baseline management robust.
- **SVaP (item 5):** PASS — Validation strategy comprehensive per §6.3.4; acceptance criteria clear; independence requirements documented.
- **SVP (item 4):** NOT VERIFIED — VER authored item 4 and cannot perform self-check (independence constraint per §5.1.2.10). Item 4 is excluded from SQAVR scope per deviation D8.

---

## 2. Introduction

### 2.1 Purpose

This document reports the independent verification of the Phase 1 Planning documents for the TDC (Train Door Control System) project, in compliance with EN 50128:2011 Sections 6.2.4.10-11 and 6.5.4.7-8.

The SQAP Verification Report (SQAVR) verifies that the planning documents are:
- **Complete:** all EN 50128 Section 6.5.4.4-6, §6.6.4.1, and §6.3.4.2 requirements addressed
- **Internally consistent:** no contradictions between sections
- **Readable and traceable:** meet document quality requirements per §5.3.2.7-10
- **Covering all lifecycle phases:** QA, CM, validation activities defined for each phase

### 2.2 Scope

This verification covers:
- **Item 1:** Software Quality Assurance Plan (SQAP) — DOC-SQAP-2026-001
- **Item 3:** Software Configuration Management Plan (SCMP) — DOC-SCMP-2026-001
- **Item 5:** Software Validation Plan (SVaP) — DOC-SVaP-2026-001

**EXCLUDED:**
- **Item 4:** Software Verification Plan (SVP) — DOC-SVP-2026-001  
  **Rationale:** VER authored the SVP per §6.2.4.2. VER cannot self-check its own SVP (independence constraint per §5.1.2.10). This exclusion is documented per deviation D8 (DELIVERABLES.md). Item 4 will undergo independent 2nd Check by VAL per `activities/phase-1-planning.yaml` line 43.

This report verifies the **planning documents as plan documents** — not the execution of QA/CM/validation activities. Activity execution is verified at each phase gate.

### 2.3 Reference Documents

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-SQAP-2026-001 | Software Quality Assurance Plan | 1.0 |
| DOC-SCMP-2026-001 | Software Configuration Management Plan | 1.0 |
| DOC-SVaP-2026-001 | Software Validation Plan | 1.0 |
| DOC-SVP-2026-001 | Software Verification Plan | 1.0 (not verified here) |
| STD-EN50128 | EN 50128:2011 Railway Applications | - |
| SQAP | Software Quality Assurance Plan (reference context) | 1.0 |
| WORKFLOW.md | Authority structure, two-track loop | - |
| DELIVERABLES.md | Annex C Table C.1, deviations D1–D8 | - |

### 2.4 Verification Team

| Role | Name | Organization | Independence |
|------|------|--------------|--------------|
| Lead Verifier | [VER Name] | [VER Organization] | Yes — independent from QUA, CM, VAL per §5.1.2.10e (SIL 3 MANDATORY) |

---

## 3. Verification Methodology

### 3.1 Verification Techniques Applied

Per EN 50128 Table A.5, the following verification techniques were applied:

| Technique | SIL 3 Requirement | Applied | Rationale |
|-----------|-----------------|---------|-----------|
| Plan-Based Verification (D.1) | **M** (MANDATORY) | **Yes** | Verified planning documents against EN 50128 normative requirements per §6.2.4.10-11 |
| Traceability (D.58) | **M** (MANDATORY) | **Yes** | Verified traceability of planning documents to EN 50128 §6.5, §6.6, §6.3.4 requirements |

### 3.2 Verification Activities

The following verification activities were performed for each document:

1. **Completeness Verification** — Verified document addresses all EN 50128 normative requirements for its type
2. **Internal Consistency Verification** — Verified no contradictions between document sections
3. **Readability and Traceability Verification** — Verified per §5.3.2.7-10
4. **Specific Requirements Verification** — Verified clause-by-clause compliance (§6.5.4 for SQAP, §6.6.4 for SCMP, §6.3.4 for SVaP)
5. **Coverage Verification** — Verified activities defined for all lifecycle phases
6. **Independence Verification** — Confirmed independence structure compliant with §5.1.2.10 (SIL 3)

---

## 4. Verification Criteria

### 4.1 SQAP Completeness Criteria (Item 1)

Per EN 50128 §6.5.4.4-6:

- [x] §6.5.4.4 — Quality System described
- [x] §6.5.4.5 — QA activities per lifecycle phase specified
- [x] §6.5.4.6 — QA tailored to this specific project (SIL 3, TDC railway door control system)
- [x] All normative sub-clauses of EN 50128 referenced
- [x] QA tools and techniques specified per Table A.9 (SIL 3)

### 4.2 SCMP Completeness Criteria (Item 3)

Per EN 50128 §6.6.4.1-2:

- [x] §6.6.4.1 — Change control process defined (nine aspects a–i)
- [x] §6.6.4.2 — Re-entry to lifecycle phase procedure defined
- [x] Configuration identification defined (CIs, baselines, version numbering)
- [x] Configuration control defined (CCB, change request lifecycle)
- [x] Configuration status accounting defined
- [x] Configuration audits defined (CM presence checks, VER functional completeness)
- [x] Traceability management defined (T1–T15 per TRACEABILITY.md)

### 4.3 SVaP Completeness Criteria (Item 5)

Per EN 50128 §6.3.4.2-3:

- [x] §6.3.4.2 — Validation approach defined on basis of input documents
- [x] §6.3.4.3 — Validation plan includes purpose, scope, organization, validation test specifications, acceptance criteria
- [x] Independence requirements defined per §5.1.2.10f (SIL 3 MANDATORY)
- [x] Validation techniques per Table A.7 (SIL 3)
- [x] Performance testing defined per Table A.18 (MANDATORY SIL 3)
- [x] Pre-existing software handling per §6.3.4.5 (N/A for TDC)
- [x] Release decision authority documented per §5.1.2.8

### 4.4 Internal Consistency Criteria (All Documents)

- [x] No contradictions between document sections
- [x] All cross-references within documents valid
- [x] Terminology used consistently throughout
- [x] Metrics and thresholds defined consistently

### 4.5 Readability and Traceability Criteria (All Documents)

Per §5.3.2.7-10:

- [x] Document structure clear and logical (§5.3.2.7)
- [x] Terminology defined and used consistently (§5.3.2.8)
- [x] Traceability to EN 50128 requirements established (§5.3.2.9)
- [x] Document management information present (§5.3.2.10)

---

## 5. Verification Results

### 5.1 SQAP Completeness Verification (Item 1)

**Completeness Result:** **PASS**

| EN 50128 Requirement | SQAP Section | Status | Notes |
|----------------------|--------------|--------|-------|
| §6.5.4.3 — SQAP written under VER responsibility | Introduction, Deviation D8 | **PASS** | QUA authors under VER direction; VER 1st-checks; VAL 2nd-checks |
| §6.5.4.4 — Quality System | Section 1 | **PASS** | ISO 9001:2015 compliance documented; QA role, authority, independence defined |
| §6.5.4.5 — QA activities per phase | Section 5 | **PASS** | All 10 phases covered; Phase 8 zero activity documented |
| §6.5.4.6 — QA tailoring to project | Sections 1.3, 7.1 | **PASS** | SIL 3 obligations mapped per Table A.9; TDC-specific context |
| QA tools and techniques | Section 7 | **PASS** | All Table A.9 techniques adopted (T1–T8); tool qualification status documented |
| QA touchpoints (37 of 46 items) | Section 1.6 | **PASS** | Format-gate position defined; 1-Pass Rule documented |
| Traceability management | Section 8 | **PASS** | T1–T15 traceability rules; QUA audits VER traceability checks |
| Non-conformance management | Section 9 | **PASS** | NCR severity definitions; escalation rules; gate impact documented |
| Quality metrics | Section 10 | **PASS** | 12 metrics defined (M1–M12); thresholds, reporting frequency specified |
| Training requirements | Section 11 | **PASS** | Training topics, frequency, evidence defined for all roles |

**Overall SQAP Completeness:** All EN 50128 §6.5.4 requirements fully addressed. No gaps identified.

### 5.2 SCMP Completeness Verification (Item 3)

**Completeness Result:** **PASS**

| EN 50128 Requirement | SCMP Section | Status | Notes |
|----------------------|--------------|--------|-------|
| §6.6.4.1 — Change control (9 aspects) | Section 4.1 | **PASS** | All nine aspects (a–i) explicitly mapped to CM process steps |
| §6.6.4.1(a) — Unique identification | Section 4.1.1 | **PASS** | CR ID format: `CR-<YYYYMMDD>-<NNN>` |
| §6.6.4.1(b) — Recording of reasons | Section 4.1.1 | **PASS** | Required in CR submission template |
| §6.6.4.1(c) — Analysis of consequences | Section 4.1.2 | **PASS** | CM impact analysis procedure defined |
| §6.6.4.1(d) — Approval by authorized personnel | Section 4.1.3 | **PASS** | CCB composition, quorum, decision authority defined |
| §6.6.4.1(e) — Updating all affected documents | Section 4.1.4 | **PASS** | Implementation procedure includes affected CI updates |
| §6.6.4.1(f) — Recording affected software items | Section 4.1.2 | **PASS** | CM impact analysis identifies all affected CIs |
| §6.6.4.1(g) — Implementation, verification, test | Sections 4.1.4-5 | **PASS** | VER review of changes mandatory before merge |
| §6.6.4.1(h) — Reporting to relevant parties | Sections 4.1.7, 5.1 | **PASS** | Configuration status accounting defined |
| §6.6.4.1(i) — Maintaining traceability | Section 4.1.6, 5.2 | **PASS** | T1–T15 traceability updates per CR; workspace.py trace command |
| §6.6.4.2 — Re-entry to lifecycle phase | Section 4.1.8 | **PASS** | CM identifies re-entry phase; COD authorizes; procedure documented |
| Configuration identification | Section 3 | **PASS** | Document registry, evidence paths, version numbering, Git branch strategy |
| Baseline management | Section 7 | **PASS** | 8 baselines (Gates 1–9); manifest format; creation procedure |
| Traceability management | Section 5.2 | **PASS** | T1–T15 rules; workspace.py trace tool; matrix naming convention |
| CM role boundary | Section 2.3 | **PASS** | CM presence checks vs. VER functional completeness clearly distinguished |

**Overall SCMP Completeness:** All EN 50128 §6.6.4 requirements fully addressed. CM canonical path authority documented.

### 5.3 SVaP Completeness Verification (Item 5)

**Completeness Result:** **PASS**

| EN 50128 Requirement | SVaP Section | Status | Notes |
|----------------------|--------------|--------|-------|
| §6.3.4.2 — SVaP written on basis of input documents | Section 1.2 | **PASS** | Input documents: SQAP, SCMP, SVP, System Req, System Safety Req |
| §6.3.4.3 — SVaP content requirements | Sections 2–11 | **PASS** | Purpose, scope, organization, test specifications, acceptance criteria all present |
| §6.3.4.4 — Validation criteria defined | Section 7 | **PASS** | Acceptance criteria per SIL 3 defined; 10 criteria with evidence requirements |
| §6.3.4.5 — Pre-existing software | Section 3.4 | **PASS** | N/A for TDC (no pre-existing software); documented per §6.3.4.5 requirement |
| §6.3.4.6 — Validation techniques per Table A.7 | Section 3.2 | **PASS** | All MANDATORY techniques for SIL 3 adopted (functional/black-box testing, performance testing, boundary value analysis, regression testing) |
| Independence requirements (§5.1.2.10f) | Sections 1.3, 2.3 | **PASS** | VAL independence from DES/IMP/TST/VER/INT documented; VAL reports to VMGR |
| Release decision authority (§5.1.2.8) | Sections 1.3, 7.3 | **PASS** | VAL final AGREE/DISAGREE authority documented; cannot be overridden |
| Operational scenarios | Section 4.2.1 | **PASS** | 15 scenarios defined (normal, degraded, emergency, recovery, environmental) |
| Performance testing (MANDATORY SIL 3) | Section 4.4 | **PASS** | Timing analysis, load testing, resource usage, reliability testing per Table A.18 |
| Traceability to requirements | Section 5 | **PASS** | T13 (SW Req → Validation Report); 100% coverage requirement documented |
| Validation evidence management | Section 6 | **PASS** | Evidence types, storage, review, archival procedures defined |

**Overall SVaP Completeness:** All EN 50128 §6.3.4 requirements fully addressed. Platform deviation D1 (SVaP in Phase 1) justified per §5.3.2.4.

### 5.4 Internal Consistency Verification

**Consistency Result:** **PASS**

| Document | Check | Status | Findings |
|----------|-------|--------|----------|
| **SQAP** | No contradictions found | **PASS** | All sections consistent; no conflicts in QA procedures |
| SQAP | All cross-references valid | **PASS** | All references to SCMP, SVP, SVaP, DELIVERABLES.md, WORKFLOW.md validated |
| SQAP | Consistent terminology | **PASS** | "QUA", "VER", "VAL", "VMGR", "NCR", "1-Pass Rule" used consistently |
| SQAP | Consistent quality metrics | **PASS** | M1–M12 metrics thresholds consistent across Sections 10 and 5 |
| **SCMP** | No contradictions found | **PASS** | All sections consistent; CM role vs. VER role clearly distinguished |
| SCMP | All cross-references valid | **PASS** | All references to SQAP, SVP, TRACEABILITY.md, BASELINE_MANAGEMENT.md validated |
| SCMP | Consistent terminology | **PASS** | "CM", "CCB", "CI", "baseline", "manifest", "T1–T15" used consistently |
| SCMP | Consistent version numbering | **PASS** | MAJOR.MINOR.PATCH scheme used consistently in Sections 3.4 and 7 |
| **SVaP** | No contradictions found | **PASS** | All sections consistent; validation vs. verification distinction clear |
| SVaP | All cross-references valid | **PASS** | All references to SQAP, SCMP, SVP, SRS, Hazard Log validated |
| SVaP | Consistent terminology | **PASS** | "VAL", "VMGR", "validation", "acceptance", "AGREE/DISAGREE" used consistently |
| SVaP | Consistent test scenarios | **PASS** | 15 scenarios (SCEN-VAL-001 to -015) cross-referenced correctly |

### 5.5 Readability and Traceability Verification

**Readability/Traceability Result:** **PASS**

| Document | Criterion | Status | Evidence |
|----------|-----------|--------|----------|
| **SQAP** | Document structure clear (§5.3.2.7) | **PASS** | 12 sections with logical progression; TOC in Section 1.6 |
| SQAP | Terminology defined (§5.3.2.8) | **PASS** | Section 1.4 defines QUA, VER, VAL, NCR, 1-Pass Rule, Track A/B |
| SQAP | Traceability to EN 50128 (§5.3.2.9) | **PASS** | Table A.9 techniques T1–T8 mapped to TDC implementation in Section 7.1 |
| SQAP | Document management present (§5.3.2.10) | **PASS** | Document Control, Version History, Approvals tables present |
| **SCMP** | Document structure clear (§5.3.2.7) | **PASS** | 12 sections with logical progression; TOC in Section 1.6 |
| SCMP | Terminology defined (§5.3.2.8) | **PASS** | Section 1.4 defines CI, baseline, CCB, CR, canonical path, T1–T15 |
| SCMP | Traceability to EN 50128 (§5.3.2.9) | **PASS** | §6.6.4.1 nine aspects (a–i) explicitly mapped to CM process in Section 4.1 |
| SCMP | Document management present (§5.3.2.10) | **PASS** | Document Control, Version History, Approvals tables present |
| **SVaP** | Document structure clear (§5.3.2.7) | **PASS** | 12 sections with logical progression; TOC in Section 1.6 |
| SVaP | Terminology defined (§5.3.2.8) | **PASS** | Section 1.4 defines validation, acceptance testing, operational scenario, black-box testing, release decision |
| SVaP | Traceability to EN 50128 (§5.3.2.9) | **PASS** | Table A.7 techniques mapped to TDC implementation in Section 3.2 |
| SVaP | Document management present (§5.3.2.10) | **PASS** | Document Control, Version History, Approvals tables present |

### 5.6 Coverage Verification

**Coverage Result:** **PASS**

| Lifecycle Phase | SQAP QA Activities (Section 5) | SCMP CM Activities (Sections 3-8) | SVaP VAL Activities (Section 4) | Status |
|----------------|--------------------------------|-----------------------------------|--------------------------------|--------|
| **Phase 0** | NONE (COD generates; QUA not instantiated) | NONE (pre-project) | N/A | **N/A** |
| **Phase 1** | SQAP authorship; template compliance (5 items) | Document registry, baseline at Gate 1 | SVaP authorship | **PASS** |
| **Phase 2** | Template compliance; traceability audit (T1–T2) | Traceability matrix (T1–T2), baseline at Gate 2 | Requirements validation (customer review) | **PASS** |
| **Phase 3** | Template compliance; traceability audit (T3–T5c) | Traceability matrix (T3–T5c), baseline at Gate 3 | N/A (validation in Phase 7) | **PASS** |
| **Phase 4** | Template compliance; traceability audit (T6, T11) | Traceability matrix (T6, T8, T11), baseline at Gate 4 | N/A (validation in Phase 7) | **PASS** |
| **Phase 5** | Template compliance; evidence audit (MISRA, coverage); QA process data (T8) | Evidence storage initialization; traceability (T7, T12); baseline at Gate 5 | N/A (validation in Phase 7) | **PASS** |
| **Phase 6** | Template compliance; traceability audit (T10a, T10b, T12) | Traceability matrix (T10a, T10b); baseline at Gate 6 | N/A (validation in Phase 7) | **PASS** |
| **Phase 7** | Template compliance (Track A item 24); 1-Pass Rule (Track B items 23, 25–27) | Baseline at Gate 7 (release-baseline); traceability (T13–T15) | Test planning, test execution, performance validation, acceptance testing (Phase 7 activities) | **PASS** |
| **Phase 8** | **ZERO ACTIVITY** (ASR fully independent) | Read-only access to release-baseline | 2nd check on SVP (item 4) only; no VAL report | **PASS** |
| **Phase 9** | Template compliance (items 36–40) | Deployment records; baseline at Gate 9 | 2nd check on deployment items | **PASS** |
| **Phase 10** | Template compliance (items 41–44); CCB audit; traceability impact audit | Per-CR baseline; change records; traceability updates per CR | N/A (VAL not in maintenance loop) | **PASS** |

**Overall Coverage:** All lifecycle phases have appropriate QA, CM, and validation activities defined. Phase 8 zero QA activity is correctly documented per ASR independence requirement.

---

## 6. Non-Conformities and Issues

### 6.1 Critical Non-Conformities

*Critical: MUST be resolved before SQAP approval*

**None Found.**

### 6.2 Major Non-Conformities

*Major: SHOULD be resolved*

**None Found.**

### 6.3 Minor Non-Conformities

| ID | Severity | Description | Document | Section | Recommendation |
|----|----------|-------------|----------|---------|----------------|
| NC-001 | Minor | SQAP references "docs/organization/org-chart.pdf" but file does not yet exist | SQAP | Section 1.5 | Create org chart before Gate 1; non-blocking for SQAP approval |
| NC-002 | Minor | SCMP manifest example shows placeholder `<hash>` but does not specify hash algorithm | SCMP | Section 7.3 | Document states SHA-256 in Section 7.3; manifest example should show "sha256" explicitly |
| NC-003 | Minor | SVaP Table 10.1 references "RTOS profiler" but does not specify which RTOS will be used | SVaP | Section 10.1 | Specify RTOS in Phase 3 (Architecture); non-blocking for SVaP approval |

### 6.4 Observations

| ID | Description | Recommendation |
|----|-------------|----------------|
| OBS-001 | SQAP Section 7.1 Table A.9 technique justifications are comprehensive and well-documented | No action required; best practice |
| OBS-002 | SCMP Section 2.3 explicitly distinguishes CM presence checks from VER functional completeness (good clarity) | No action required; best practice |
| OBS-003 | SVaP Section 4.2.1 defines 15 operational scenarios (exceeds minimum 10 for SIL 3) | No action required; exceeds requirement |
| OBS-004 | All three documents reference platform deviations D1–D8 consistently | No action required; traceability excellent |

---

## 7. EN 50128 Compliance

### 7.1 Section 6.5.4 Compliance (SQAP)

| Clause | Requirement | SQAP Response | Compliance |
|--------|-------------|---------------|------------|
| §6.5.4.3 | SQAP written under VER responsibility | Introduction, Deviation D8 | **PASS** |
| §6.5.4.4 | Quality System described | Section 1 | **PASS** |
| §6.5.4.5 | QA activities per phase | Section 5 | **PASS** |
| §6.5.4.6 | QA tailored to project | Sections 1.3, 7.1 | **PASS** |
| §6.5.4.14-17 | Readability requirements | All sections | **PASS** |

### 7.2 Section 6.6.4 Compliance (SCMP)

| Clause | Requirement | SCMP Response | Compliance |
|--------|-------------|---------------|------------|
| §6.6.4.1 | Change control (nine aspects a–i) | Section 4.1 | **PASS** |
| §6.6.4.2 | Re-entry to lifecycle phase | Section 4.1.8 | **PASS** |
| §6.6.3 | Configuration status reports | Section 5.1 | **PASS** |
| §9.1.4.2 | Baseline recorded under CM control | Section 7 | **PASS** |
| §9.1.4.3 | Reproducibility throughout operational lifetime | Section 7.3 (manifest) | **PASS** |

### 7.3 Section 6.3.4 Compliance (SVaP)

| Clause | Requirement | SVaP Response | Compliance |
|--------|-------------|---------------|------------|
| §6.3.4.2 | SVaP written on basis of input documents | Section 1.2 | **PASS** |
| §6.3.4.3 | SVaP content requirements | Sections 2–11 | **PASS** |
| §6.3.4.4 | Validation criteria defined | Section 7 | **PASS** |
| §6.3.4.5 | Pre-existing software handling | Section 3.4 (N/A) | **PASS** |
| §6.3.4.6 | Validation techniques (Table A.7) | Section 3.2 | **PASS** |

### 7.4 Independence Requirements (SIL 3)

**Verification Independence:** **COMPLIANT**

Evidence:
- VER [VER Name] is independent from SQAP author (QUA), SCMP author (CM), and SVaP author (VAL) per §5.1.2.10e
- VER reports to VMGR (SIL 3 requirement), not to PM
- No conflicts of interest identified
- VER did NOT verify item 4 (SVP) — self-check exclusion per deviation D8

**Validation Independence:** **COMPLIANT**

Evidence:
- VAL [VAL Name] is independent from DES, IMP, TST, VER, INT per §5.1.2.10f
- VAL reports to VMGR (SIL 3 requirement), not to PM
- VAL has final release decision authority (AGREE/DISAGREE) per §5.1.2.8

---

## 8. Verification Summary

**SQAP completeness verification result:** **PASS**  
**SCMP completeness verification result:** **PASS**  
**SVaP completeness verification result:** **PASS**  
**Internal consistency result (all documents):** **PASS**  
**Readability/traceability result (all documents):** **PASS**  
**Coverage result (all documents):** **PASS**

**Overall Verification Decision:** **APPROVE**

**Rationale:**  
All three planning documents (SQAP, SCMP, SVaP) fully comply with EN 50128:2011 requirements for SIL 3. Completeness verification confirms all normative clauses are addressed. Internal consistency verification found zero contradictions. Readability and traceability verification confirms all §5.3.2 requirements met. Coverage verification confirms QA, CM, and validation activities defined for all lifecycle phases.

**Minor Non-Conformities (NC-001, NC-002, NC-003):** Three minor documentation issues identified (missing org chart file, hash algorithm example clarity, RTOS tool specification). These are non-blocking for SQAP approval and can be resolved during Phase 2 or Phase 3 activities.

**Independence Constraint (Item 4):** VER authored the SVP (item 4) per §6.2.4.2 and cannot perform self-check. Item 4 is excluded from this SQAVR scope per deviation D8. VAL will perform 2nd Check on item 4 per `activities/phase-1-planning.yaml`.

**Conditions for Approval:** None. All critical and major non-conformities: **ZERO**.

---

## 9. Conclusion

### 9.1 Conditions for Approval

- [x] All critical non-conformities resolved (zero found)
- [x] All major non-conformities resolved or justified (zero found)
- [x] All verification criteria met
- [x] Independent verification complete (SIL 3 requirement met)

### 9.2 Verifier Statement

I, [Verifier Name], hereby certify that:
1. I have independently verified the Software Quality Assurance Plan (item 1), Software Configuration Management Plan (item 3), and Software Validation Plan (item 5)
2. The verification activities were performed in accordance with the Software Verification Plan (DOC-SVP-2026-001)
3. The verification results documented in this report are accurate and complete
4. **[SIL 3]** I am independent from the SQAP author (QUA), SCMP author (CM), and SVaP author (VAL) per §5.1.2.10e
5. **[SIL 3 Independence Constraint]** I authored the SVP (item 4) per §6.2.4.2 and have excluded it from my verification scope to maintain independence integrity per §5.1.2.10

**Verifier:** [VER Name]  
**Signature:** [Signature]  
**Date:** 2026-04-02

---

## 10. Appendices

### Appendix A: Completeness Checklist

**EN 50128 §6.5.4 (SQAP) Requirements Checklist**

| Requirement | SQAP Section | Status | Evidence |
|-------------|--------------|--------|----------|
| §6.5.4.3 — SQAP written under VER responsibility | Introduction, Deviation D8 | ✓ | QUA authors under VER direction |
| §6.5.4.4 — Quality System described | Section 1 | ✓ | ISO 9001:2015 compliance |
| §6.5.4.5 — QA activities per phase | Section 5 | ✓ | All 10 phases covered |
| §6.5.4.6 — QA tailored to project | Sections 1.3, 7.1 | ✓ | SIL 3, TDC-specific |
| Table A.9 Technique T1 (ISO 9001 accreditation) | Section 7.1, row T1 | ✓ | HR adopted |
| Table A.9 Technique T2 (ISO 9001 compliance) | Section 7.1, row T2 | ✓ | **M** adopted |
| Table A.9 Technique T3 (ISO/IEC 90003) | Section 7.1, row T3 | ✓ | R adopted |
| Table A.9 Technique T4 (Company Quality System) | Section 7.1, row T4 | ✓ | **M** adopted |
| Table A.9 Technique T5 (SCM) | Section 7.1, row T5 | ✓ | **M** adopted (SCMP reference) |
| Table A.9 Technique T6 (Traceability) | Section 7.1, row T6 | ✓ | **M** adopted (T1–T15) |
| Table A.9 Technique T7 (Metrics) | Section 7.1, row T7 | ✓ | R adopted (M1–M12) |
| Table A.9 Technique T8 (Data Recording/Analysis) | Section 7.1, row T8 | ✓ | **M** adopted |

**EN 50128 §6.6.4 (SCMP) Requirements Checklist**

| Requirement | SCMP Section | Status | Evidence |
|-------------|--------------|--------|----------|
| §6.6.4.1(a) — Unique identification | Section 4.1.1 | ✓ | CR ID: `CR-<YYYYMMDD>-<NNN>` |
| §6.6.4.1(b) — Recording of reasons | Section 4.1.1 | ✓ | Required in CR template |
| §6.6.4.1(c) — Analysis of consequences | Section 4.1.2 | ✓ | CM impact analysis procedure |
| §6.6.4.1(d) — Approval by authorized personnel | Section 4.1.3 | ✓ | CCB composition, PM chair |
| §6.6.4.1(e) — Updating all affected documents | Section 4.1.4 | ✓ | Implementation procedure |
| §6.6.4.1(f) — Recording affected software items | Section 4.1.2 | ✓ | CM identifies all affected CIs |
| §6.6.4.1(g) — Implementation, verification, test | Sections 4.1.4-5 | ✓ | VER review mandatory |
| §6.6.4.1(h) — Reporting to relevant parties | Sections 4.1.7, 5.1 | ✓ | Configuration status accounting |
| §6.6.4.1(i) — Maintaining traceability | Sections 4.1.6, 5.2 | ✓ | T1–T15 updates per CR |
| §6.6.4.2 — Re-entry to lifecycle phase | Section 4.1.8 | ✓ | CM identifies; COD authorizes |

**EN 50128 §6.3.4 (SVaP) Requirements Checklist**

| Requirement | SVaP Section | Status | Evidence |
|-------------|--------------|--------|----------|
| §6.3.4.2 — SVaP written on basis of input documents | Section 1.2 | ✓ | SQAP, SCMP, SVP, System Req |
| §6.3.4.3 — SVaP content (purpose, scope, org, tests, acceptance) | Sections 2–11 | ✓ | All sections present |
| §6.3.4.4 — Validation criteria defined | Section 7 | ✓ | 10 acceptance criteria |
| §6.3.4.5 — Pre-existing software | Section 3.4 | ✓ | N/A for TDC |
| §6.3.4.6 — Validation techniques (Table A.7) | Section 3.2 | ✓ | All **M** techniques adopted |
| §5.1.2.10f — Independence (SIL 3 MANDATORY) | Sections 1.3, 2.3 | ✓ | VAL reports to VMGR |
| §5.1.2.8 — Release decision authority | Sections 1.3, 7.3 | ✓ | VAL AGREE/DISAGREE final |

### Appendix B: Defect Details

**NC-001: SQAP references missing org chart file**

- **Severity:** Minor
- **SQAP Section:** 1.5 (Role Assignments)
- **Description:** SQAP states "Organization chart demonstrating independence of VER, VAL, VMGR, and QUA from development team shall be maintained in `docs/organization/org-chart.pdf` and reviewed quarterly." File does not yet exist.
- **Impact:** Low — org chart can be created before Gate 1; SQAP approval not blocked
- **Recommendation:** Create `docs/organization/org-chart.pdf` before Gate 1 with roles: VMGR → VER / VAL; PM → DES/IMP/TST/INT/REQ; PM → QUA; PM → CM
- **Status:** OPEN (non-blocking)

**NC-002: SCMP manifest example hash placeholder**

- **Severity:** Minor
- **SCMP Section:** 7.3 (Baseline Manifest Format)
- **Description:** Manifest example YAML shows `sha256: <hash>` but uses placeholder instead of explicit algorithm name
- **Impact:** Low — Section 7.3 text states "SHA-256 hash" clearly; manifest example should match
- **Recommendation:** Update manifest example to show `sha256: "abcdef1234567890abcdef1234567890abcdef1234567890abcdef1234567890"` (example hash)
- **Status:** OPEN (non-blocking)

**NC-003: SVaP RTOS profiler not specified**

- **Severity:** Minor
- **SVaP Section:** 10.1 (Test Tools)
- **Description:** Table 10.1 lists "RTOS Profiler (IAR Embedded Workbench)" but TDC RTOS not yet selected
- **Impact:** Low — RTOS selection occurs in Phase 3 (Architecture); SVaP tool list can be updated via SCMP change control
- **Recommendation:** Document RTOS selection in Phase 3; update SVaP via CCB-approved CR if RTOS changes
- **Status:** OPEN (non-blocking)

---

**End of Software Quality Assurance Verification Report**
