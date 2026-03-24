---
name: en50128-configuration
description: Software configuration management for EN 50128 railway software
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  role: configuration-manager
---

# EN 50128 Configuration Management Skill

**Primary user**: CM agent. Load this skill before any CM operation.

---

## Authoritative Sources

Read these before any operation — do not invent rules.

| File | Answers |
|------|---------|
| `std/EN50128-2011.md` §6.6 | Change control nine aspects (a–i), §6.6.4.2 re-entry, §6.6.3 outputs |
| `std/EN50128-2011.md` §6.2.4.8 | VER evidence retention obligation |
| `std/EN50128-2011.md` §9.1.4.2–3 | Deployment baseline recording and reproducibility |
| `std/EN50128-2011.md` §9.1.4.13 | Deployment Record as tracked evidence artifact |
| `DELIVERABLES.md` | Annex C Table C.1 deliverable matrix |
| `WORKFLOW.md` | Authority structure, CCB re-entry flow (Diagrams 1–4) |
| `BASELINE_MANAGEMENT.md` | Baseline types, CM presence-check role, EN 50128 audit terminology (no FCA/PCA), role boundaries at each gate |
| `activities/deliverables.yaml` | Machine-readable deliverable catalogue (CM registry is consistent with this) |
| `document-registry.yaml` (this skill dir) | Canonical document-to-path and evidence-to-path lookup table |

---

## Table A.9 Technique Obligations

| # | Technique | Ref | SIL 0 | SIL 1–2 | SIL 3–4 |
|---|-----------|-----|-------|---------|---------|
| 5 | Software Configuration Management | D.48 | **M** | **M** | **M** |
| 7 | Traceability | D.58 | R | HR | **M** |
| 8 | Data Recording and Analysis | D.12 | HR | HR | **M** |

SCM is MANDATORY at ALL SIL levels. Traceability and Data Recording are MANDATORY at SIL 3–4.

---

## Canonical Directory Layout

CM is the **sole authority** for this structure. All agents MUST call `query-location` before
writing any file. The layout below is normative for every project workspace.

```
{workspace_root}/
├── LIFECYCLE_STATE.md
├── changes/
│   └── CR-<YYYYMMDD>-<NNN>.md          # one file per change request
├── baselines/
│   └── <baseline-name>/
│       ├── manifest.yaml               # list of all CIs at baseline time
│       └── pca-fca-record.md           # PCA+FCA record (SIL 3-4)
│
├── phase-1-planning/
│   ├── Software-Quality-Assurance-Plan.md
│   ├── Software-Configuration-Management-Plan.md
│   ├── Software-Verification-Plan.md
│   ├── Software-Validation-Plan.md
│   ├── reports/
│   │   └── Software-Quality-Assurance-Verification-Report.md
│   └── evidence/                       # no evidence artifacts in Phase 1
│
├── phase-2-requirements/
│   ├── Software-Requirements-Specification.md
│   ├── Overall-Software-Test-Specification.md
│   ├── reports/
│   │   └── Software-Requirements-Verification-Report.md
│   └── evidence/                       # no evidence artifacts in Phase 2
│
├── phase-3-architecture-design/
│   ├── Software-Architecture-Specification.md
│   ├── Software-Design-Specification.md
│   ├── Software-Interface-Specifications.md
│   ├── Software-Integration-Test-Specification.md
│   ├── Software-Hardware-Integration-Test-Specification.md
│   ├── reports/
│   │   └── Software-Architecture-and-Design-Verification-Report.md
│   └── evidence/
│       └── design-analysis/            # FMEA/FTA raw outputs, analysis tool logs
│
├── phase-4-component-design/
│   ├── Software-Component-Design-Specification.md
│   ├── Software-Component-Test-Specification.md
│   ├── reports/
│   │   └── Software-Component-Design-Verification-Report.md
│   └── evidence/
│       └── design-review/              # design inspection records, checklists
│
├── phase-5-implementation-testing/
│   ├── src/                            # source code tree (IMP-owned)
│   ├── Software-Source-Code-Verification-Report.md
│   ├── Software-Component-Test-Report.md
│   └── evidence/
│       ├── static-analysis/            # MISRA checker raw output (.xml/.json)
│       ├── coverage/                   # gcov/lcov data files, HTML reports
│       ├── test-logs/                  # unit test execution logs
│       └── tool-qualification/         # tool qualification evidence (§7.4.4.14)
│
├── phase-6-integration/
│   ├── Software-Integration-Test-Report.md
│   ├── Software-Hardware-Integration-Test-Report.md
│   └── evidence/
│       ├── integration-test-logs/      # raw test execution logs
│       └── hw-integration-logs/        # hardware integration evidence
│
├── phase-7-validation/
│   ├── Software-Integration-Verification-Report.md
│   ├── Overall-Software-Test-Report.md
│   ├── Software-Validation-Report.md
│   ├── Tools-Validation-Report.md
│   ├── Release-Note.md
│   └── evidence/
│       ├── system-test-logs/           # system/acceptance test execution logs
│       └── validation-records/         # VAL evidence per §6.3.4
│
├── phase-8-assessment/
│   ├── Software-Assessment-Plan.md
│   ├── Software-Assessment-Report.md
│   └── evidence/
│       └── assessor-records/           # ASR review notes, checklists (§6.4.4.10)
│
├── phase-9-deployment/
│   ├── Software-Release-and-Deployment-Plan.md
│   ├── Software-Deployment-Manual.md
│   ├── Release-Notes.md
│   ├── Deployment-Records.md
│   ├── Deployment-Verification-Report.md
│   └── evidence/
│       └── deployment-records/         # §9.1.4.13 deployment evidence
│
└── phase-10-maintenance/
    ├── Software-Maintenance-Plan.md
    ├── Software-Change-Records.md
    ├── Software-Maintenance-Records.md
    ├── Software-Maintenance-Verification-Report.md
    └── evidence/
        └── maintenance-logs/           # change execution records
```

---

## query-location Algorithm

1. Receive document key (e.g. `SQAP`, `SRS`, `COMPTESTRPT`).
2. Look up key in `document-registry.yaml` (this skill dir) → get `phase_dir` and `filename`.
3. Resolve `{workspace_root}` from `.workspace` JSON → `examples/<project_name>/`.
4. Return absolute path: `{workspace_root}/{phase_dir}/{filename}`.
5. If key not found: raise MAJOR violation — caller must provide a new key for CM to register.

## evidence-path Algorithm

1. Receive evidence type (e.g. `static-analysis`, `coverage`, `test-log`).
2. Look up `evidence_type` in `document-registry.yaml` evidence section → get `phase_dir` and `subdir`.
3. Resolve `{workspace_root}` from `.workspace` JSON.
4. Return absolute path: `{workspace_root}/{phase_dir}/evidence/{subdir}/`.
5. Create the directory if it does not exist (evidence-init capability).

---

## Baseline Types (per phase gate)

| Gate | Baseline Name | Trigger | PCA+FCA required (SIL 3–4) |
|------|--------------|---------|---------------------------|
| Gate 1 | `planning-baseline` | Phase 1 complete | No (planning docs only) |
| Gate 2 | `requirements-baseline` | Phase 2 complete | Yes |
| Gate 3 | `design-baseline` | Phase 3 complete | Yes |
| Gate 4 | `component-design-baseline` | Phase 4 complete | Yes |
| Gate 5 | `implementation-baseline` | Phase 5 complete | Yes |
| Gate 6 | `integration-baseline` | Phase 6 complete | Yes |
| Gate 7 | `release-baseline` | Phase 7 complete | Yes — full PCA+FCA |
| Gate 9 | `deployment-baseline` | Phase 9 complete | Yes — §9.1.4.2–3 |

**§9.1.4.2**: Before delivering a software release, the software baseline SHALL be recorded and kept
traceable under CM control.  
**§9.1.4.3**: The release SHALL be reproducible throughout its baseline lifecycle.

---

## §6.6.4.1 Change Control — Nine Required Aspects

Every Software Change Record MUST address all nine aspects (a–i):

| # | Aspect | Key clause |
|---|--------|-----------|
| a | Unique identification of the change | §6.6.4.1(a) |
| b | Recording of the reasons for the change | §6.6.4.1(b) |
| c | Analysis of the consequences of the change | §6.6.4.1(c) |
| d | Approval of the change by authorised personnel | §6.6.4.1(d) |
| e | Updating of all affected documents | §6.6.4.1(e) |
| f | Recording of all affected software items (CIs) | §6.6.4.1(f) |
| g | Implementation, verification and test of the change | §6.6.4.1(g) |
| h | Reporting to all relevant parties | §6.6.4.1(h) |
| i | Maintaining traceability of the change throughout the lifecycle | §6.6.4.1(i) |

**§6.6.4.2**: ALL changes, regardless of size or urgency, SHALL initiate a return to an appropriate
lifecycle phase. CM identifies the re-entry scope; COD authorizes re-entry.

---

## §6.6.3 Output Documents

Per §6.6.3, the normative CM outputs are:
1. **Modified software and documentation** — all changed CIs at their new versions
2. **Software Change Records** (§9.2.4.11) — one per approved CR; stored in `changes/`
3. **New Configuration Records** — updated SCMP, configuration status accounting records

The SCMP is a **planning input** (written in Phase 1), not a §6.6.3 output.

---

## §6.2.4.8 Evidence Retention

Results of each verification activity SHALL be retained in a format defined or referenced in the
SVP. CM is responsible for ensuring VER evidence is stored in the canonical `evidence/` paths and
is included in the baseline manifest at each gate.

---

## Violation Alarm Protocol

| Severity | Condition | CM action |
|----------|-----------|-----------|
| CRITICAL | Document written to unregistered path | Invoke PM immediately via `task` tool |
| CRITICAL | Baseline created without PCA+FCA (SIL 3–4) | Invoke PM immediately via `task` tool |
| CRITICAL | CI changed without an approved CR | Invoke PM immediately via `task` tool |
| MAJOR | Evidence artifact not stored in canonical path | Log; report at next status accounting |
| MAJOR | CR missing one of the nine §6.6.4.1(a–i) aspects | Log; return CR to originator |
| MINOR | Version tag missing or inconsistent | Log; correct at next baseline cycle |
