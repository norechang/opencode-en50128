# Configuration Audit Report

**TEMPLATE VERSION**: 3.0  
**REFERENCE**: EN 50128:2011 §6.6, §6.2.4.8, §6.2.4.13(a), §9.1.4.2–3, D.48

> **Note on terminology**: EN 50128:2011 does not define "FCA" or "PCA". Those terms belong to
> MIL-STD-973 / IEEE 828 and MUST NOT appear in any EN 50128 deliverable. For the correct EN 50128
> ownership mapping see `tasks/BASELINE_MANAGEMENT.md` Terminology note.

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | [DOC-CAR-YYYYMMDD-NNN] |
| **Version** | [X.Y] |
| **Date** | [YYYY-MM-DD] |
| **Project** | [Project Name] |
| **SIL Level** | [0 \| 1 \| 2 \| 3 \| 4] |
| **Audit Type** | [Baseline Audit \| Internal Process Audit \| Post-CR Audit] |
| **Gate / Trigger** | [Gate N — `<baseline-name>` \| Internal audit — no gate \| Post-CR audit — CR-YYYYMMDD-NNN] |
| **Author** | [Name], Configuration Manager |
| **Reviewer** | [Name], [Role] |
| **Approver** | [Name], Project Manager |
| **Status** | [Draft \| Review \| Approved] |

**Permitted Audit Types:**

| Type | When | Gate? |
|------|------|-------|
| Baseline Audit | Triggered at each COD phase gate (Gates 1–7, 9) | Yes — gate authorizes baseline creation |
| Internal Process Audit | CM-initiated quality check between gates | No |
| Post-CR Audit | After CCB-approved CR is implemented and affected gate(s) re-passed | No new gate; per-CR baseline tagged |

---

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft | — |

---

## APPROVALS

CM is author. PM approves. VER and VAL do NOT sign this report — they produce their own
Verification and Validation Reports, which CM checks for presence only (§6.2.4.8, §6.3.4.10).
ASR does NOT sign this report — ASR reviews the release-baseline artefacts and produces the
Assessment Report (§6.4.4.10).

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Configuration Manager (Author)** | [Name] | | YYYY-MM-DD |
| **Quality Assurance** | [Name] | | YYYY-MM-DD |
| **Project Manager (Approver)** | [Name] | | YYYY-MM-DD |

---

## 1. Audit Identification

| Field | Value |
|-------|-------|
| **Audit ID** | CAR-YYYYMMDD-NNN |
| **Gate Number** | [Gate N \| N/A for internal audits] |
| **Baseline Authorized** | [Yes — COD gate-check PASS on YYYY-MM-DD \| N/A] |
| **Baseline Name** | [`<baseline-name>` \| N/A] |
| **VCS Tag** | [`<project>-gate<N>-<baseline-name>-<YYYYMMDD>` \| N/A] |
| **Manifest Path** | [`baselines/<baseline-name>/manifest.yaml` \| N/A] |
| **Audit Start Date** | YYYY-MM-DD |
| **Audit End Date** | YYYY-MM-DD |
| **Configuration Items Audited** | [Number] |

---

## 2. Audit Scope

CM audits **presence, version consistency, and path correctness** of configuration items.
CM does NOT audit content correctness — that is the role of VER (§6.2.4.7), VAL (§6.3.4.9),
and SAF (for safety artefacts).

### 2.1 Configuration Items in Scope

Items in scope are determined by the gate. Authoritative item list:
`activities/baseline-management.yaml` → `baselines[gate_<N>].content_scope`.

| CI Key | Canonical Path (from `document-registry.yaml`) | Expected Version | VCS Commit Hash | Present? | Version Match? |
|--------|------------------------------------------------|-----------------|-----------------|----------|----------------|
| SQAP | `phase-1-planning/Software-Quality-Assurance-Plan.md` | [X.Y] | [hash] | [Y/N] | [Y/N] |
| SCMP | `phase-1-planning/Software-Configuration-Management-Plan.md` | [X.Y] | [hash] | [Y/N] | [Y/N] |
| SVP | `phase-1-planning/Software-Verification-Plan.md` | [X.Y] | [hash] | [Y/N] | [Y/N] |
| SVaP | `phase-1-planning/Software-Validation-Plan.md` | [X.Y] | [hash] | [Y/N] | [Y/N] |
| SRS | `phase-2-requirements/Software-Requirements-Specification.md` | [X.Y] | [hash] | [Y/N] | [Y/N] |
| SAS | `phase-3-architecture-design/Software-Architecture-Specification.md` | [X.Y] | [hash] | [Y/N] | [Y/N] |
| SDS | `phase-3-architecture-design/Software-Design-Specification.md` | [X.Y] | [hash] | [Y/N] | [Y/N] |
| [Add all CIs for this gate — consult `baseline-management.yaml`] | | | | | |

**CM presence-check obligations** (§6.6, D.48):

- [ ] Each CI present at canonical path (`query-location` used to determine path)
- [ ] Each CI at expected version in VCS
- [ ] No CI changed outside an approved CR (`changes/CR-<YYYYMMDD>-<NNN>.md`)
- [ ] File integrity hashes recorded in baseline manifest

### 2.2 Evidence Artefacts in Scope

Evidence paths are canonical per `document-registry.yaml` evidence section.

| Evidence Type | Canonical Path | Present? | Integrity Check |
|---------------|---------------|----------|-----------------|
| static-analysis | `phase-5-implementation-testing/evidence/static-analysis/` | [Y/N] | [hash/N/A] |
| coverage | `phase-5-implementation-testing/evidence/coverage/` | [Y/N] | [hash/N/A] |
| test-logs | `phase-5-implementation-testing/evidence/test-logs/` | [Y/N] | [hash/N/A] |
| integration-test-logs | `phase-6-integration/evidence/integration-test-logs/` | [Y/N] | [hash/N/A] |
| [Add evidence types for this gate] | | | |

**CM evidence retention obligation** (§6.2.4.8): results of each verification SHALL be retained
in a format defined or referenced in the SVP. CM verifies presence and records paths in manifest.
CM does NOT judge whether the evidence content demonstrates adequate coverage — that is VER.

### 2.3 Required Signed Reports

CM checks reports are present and signed. CM does NOT re-perform the functional checks
those reports document.

| Report | Expected at This Gate | Present and Signed? | VMGR Approved? (SIL 3–4) |
|--------|----------------------|--------------------|-----------------------------|
| VER Verification Report | Yes — see tasks/BASELINE_MANAGEMENT.md Gate Quick Reference | [Y/N] | [Y/N/N/A] |
| VER report states identity/configuration of items verified (§6.2.4.13(a)) | Confirm field present | [Y/N] | — |
| VAL 2nd-check sign-off (non-Phase-7 gates) | See DELIVERABLES.md per-item | [Y/N] | — |
| VAL Validation Report stating this baseline (Phase 7 only) (§6.3.4.10) | Phase 7 only | [Y/N/N/A] | — |
| QUA template-compliance pass on all reports | Yes | [Y/N] | — |

**Note on Gate 1 SVaP**: Item 5 (SVaP) has no VAL 2nd check — VAL cannot 2nd-check its own
document. See DELIVERABLES.md.

**Note on Gate 6**: The formal INTVER report (Annex C item 23) is produced in Phase 7, not Gate 6.
At Gate 6, VER performs a review of integration test completeness; no separately named VER report
covers this gate. See tasks/BASELINE_MANAGEMENT.md Diagram 1 Gate 6 note.

**Note on Gate 9 DEPLOYVER**: Item 40 (DEPLOYVER) has no VAL 2nd check.
See DELIVERABLES.md.

---

## 3. CM Presence-Check Results

### 3.1 CI Presence and Version Control

**Repository Information:**

| Field | Value |
|-------|-------|
| Repository type | [Git] |
| Repository URL | [URL] |
| Baseline tag | [`<project>-gate<N>-<baseline-name>-<YYYYMMDD>`] |
| Tag commit | [commit-hash] |

**Version Control Findings:**

- [ ] All CIs registered in `document-registry.yaml`
- [ ] No CI written to an unregistered path
- [ ] Baseline tag created and protected (force-push disabled)
- [ ] No uncommitted changes in baseline tree
- [ ] Tag deletion requires CCB approval and Change Record (§9.1.4.2, D.48)

### 3.2 Build Environment Record (§9.1.4.3 Reproducibility)

Recorded in `baselines/<baseline-name>/manifest.yaml`. CM verifies these fields are present:

| Field | Recorded Value |
|-------|---------------|
| Compiler name and version | [e.g. gcc 12.3.0] |
| Compiler flags | [e.g. -std=c11 -Wall -Wextra -Werror] |
| Static analysis tool and version | [e.g. PC-lint Plus 2.0] |
| Coverage tool and version | [e.g. gcov 12.3.0 / lcov 1.16] |
| OS and build host | [e.g. Ubuntu 22.04 LTS, x86_64] |

**Basis**: §9.1.4.3 — release SHALL be reproducible throughout the baseline lifecycle.

### 3.3 Change Control Verification

**Change Requests since last baseline:** [Number]

| CR ID | Title | CCB Approved? | Affected CIs Updated? | Evidence Updated? | Status |
|-------|-------|--------------|----------------------|------------------|--------|
| CR-YYYYMMDD-NNN | [Title] | [Y/N] | [Y/N] | [Y/N] | [Open \| Closed] |

**§6.6.4.1 Coverage Check** — each closed CR MUST address all nine aspects:

| CR ID | (a) Unique ID | (b) Reason | (c) Consequences | (d) Authorised approval | (e) Docs updated | (f) Affected CIs recorded | (g) Impl/VER/test done | (h) Parties notified | (i) Traceability maintained |
|-------|--------------|------------|-----------------|------------------------|-----------------|--------------------------|----------------------|---------------------|-----------------------------|
| CR-YYYYMMDD-NNN | [Y/N] | [Y/N] | [Y/N] | [Y/N] | [Y/N] | [Y/N] | [Y/N] | [Y/N] | [Y/N] |

A "No" in any cell is a MAJOR violation. Log and return CR to PM for remediation.

**§6.6.4.2 Lifecycle Re-entry** — all approved CRs triggered return to appropriate lifecycle phase:

- [ ] Each CR in the table above had affected phases re-executed
- [ ] COD gate-checks re-passed for all phases re-entered
- [ ] Post-CR baseline created (separate from gate baseline) if applicable

### 3.4 Baseline Manifest Completeness

Manifest stored at `baselines/<baseline-name>/manifest.yaml`. CM verifies all required fields:

- [ ] Baseline name, gate number, phase name, creation date
- [ ] All CIs listed: doc key · filename · VCS commit hash · document version
- [ ] All evidence artefacts listed: type · canonical path · file hash
- [ ] VER Verification Report reference + VMGR approval status (SIL 3–4)
- [ ] VAL report reference (Phase 7) or per-item 2nd-check references (other gates)
- [ ] QUA template-compliance pass records for all reports
- [ ] Build environment record (§9.1.4.3)
- [ ] Open defect list with disposition (CM records; VER determines disposition)

---

## 4. Non-Conformances

### 4.1 CRITICAL — Must Resolve Before Baseline is Finalized

CRITICAL issues prevent baseline creation. CM invokes PM immediately via `task` tool.

| Issue ID | Description | Affected CI | EN 50128 Clause | Assigned To | Resolution Required By |
|----------|-------------|-------------|----------------|-------------|----------------------|
| CAR-CRIT-NNN | [e.g. CI present at non-canonical path] | [CI key] | §6.6, D.48 | [Name] | YYYY-MM-DD |

### 4.2 MAJOR — Must Resolve Before Next Baseline Cycle

| Issue ID | Description | Affected CI | EN 50128 Clause | Assigned To | Resolution Required By |
|----------|-------------|-------------|----------------|-------------|----------------------|
| CAR-MAJ-NNN | [e.g. CR missing §6.6.4.1(c) consequence analysis] | CR-YYYYMMDD-NNN | §6.6.4.1(c) | [Name] | YYYY-MM-DD |

### 4.3 MINOR — May Defer

| Issue ID | Description | Affected CI | EN 50128 Clause | Recommendation |
|----------|-------------|-------------|----------------|----------------|
| CAR-MIN-NNN | [e.g. version tag missing from evidence artefact] | [path] | D.48 | Correct at next baseline cycle |

### 4.4 Observations

| Observation ID | Description | Recommendation |
|---------------|-------------|----------------|
| CAR-OBS-NNN | [Process improvement suggestion] | [Action] |

---

## 5. Audit Conclusions

### 5.1 Baseline Creation Decision

| Item | Result |
|------|--------|
| All CIs present at canonical paths | [Pass \| Fail] |
| All CIs at expected versions in VCS | [Pass \| Fail] |
| No unauthorized changes detected | [Pass \| Fail] |
| Required VER report present and signed | [Pass \| Fail] |
| VER report states identity/configuration (§6.2.4.13(a)) | [Pass \| Fail] |
| VMGR approval on VER report (SIL 3–4) | [Pass \| Fail \| N/A] |
| VAL 2nd-check / VAL Report present (per gate) | [Pass \| Fail \| N/A] |
| Build environment recorded (§9.1.4.3) | [Pass \| Fail] |
| Manifest complete | [Pass \| Fail] |
| VCS tag created and protected | [Pass \| Fail] |
| **Overall Decision** | **[Baseline Created \| Blocked — CRITICAL issues open]** |

**Baseline may only be created after COD gate-check PASS. CM does not independently authorize
baseline creation.** (tasks/BASELINE_MANAGEMENT.md Diagram 2 Step 1; `activities/baseline-management.yaml`)

### 5.2 Corrective Action Plan

| Issue ID | Corrective Action | Responsible | Target Date | Status |
|----------|-----------------|-------------|-------------|--------|
| [CAR-XXX-NNN] | [Action] | [Name] | YYYY-MM-DD | [Open \| In Progress \| Closed] |

### 5.3 Next Audit

| Field | Value |
|-------|-------|
| **Next Audit Type** | [Baseline Audit — Gate N+1 \| Internal Process Audit \| Post-CR Audit] |
| **Planned Gate / Trigger** | [Gate N+1 \| Process review date \| Post-CR: CR-YYYYMMDD-NNN] |
| **Planned Date** | YYYY-MM-DD |
| **Focus Areas** | [Any open issues carried forward; specific CI categories if applicable] |

---

## 6. EN 50128 Clause Reference

| Clause | Relevance to this report |
|--------|--------------------------|
| §6.6 | Software Configuration Management — scope of CM duties |
| §6.6.4.1(a–i) | Nine required aspects of every Software Change Record |
| §6.6.4.2 | All changes SHALL initiate return to appropriate lifecycle phase |
| §6.2.4.8 | VER evidence retention — CM stores; VER produces |
| §6.2.4.13(a) | VER report shall state identity/configuration of items verified |
| §6.3.4.9 | VAL checks verification is complete (evidenced in VAL report) |
| §6.3.4.10 | VAL Validation Report shall state the baseline validated |
| §9.1.4.2 | Baseline shall be recorded and kept traceable under CM control |
| §9.1.4.3 | Release shall be reproducible throughout baseline lifecycle |
| §9.1.4.13 | Deployment Record as CM-tracked evidence artefact |
| §9.2.4 | Maintenance-phase change assessment and Software Change Records |
| D.48 | SCM records every version of every significant deliverable |

---

## Appendices

### Appendix A: Baseline Manifest (reference)

Full manifest at `baselines/<baseline-name>/manifest.yaml`. Summary reproduced here if needed.

### Appendix B: Configuration Item List

Complete list of all CIs audited (supplement to Section 2.1 table if too large for inline).

### Appendix C: Evidence Artefact List

Complete list of all evidence artefacts checked (supplement to Section 2.2 table).

### Appendix D: Audit Evidence

Screenshots, tool logs, checksum verification outputs collected during audit.

---

**Template Version**: 3.0  
**EN 50128:2011 Compliance**: §6.6, §6.2.4.8, §6.2.4.13(a), §9.1.4.2–3, D.48  
**Skill Owner**: Configuration Manager (`/cm`)  
**Authoritative baseline procedure**: `tasks/BASELINE_MANAGEMENT.md` + `activities/baseline-management.yaml`
