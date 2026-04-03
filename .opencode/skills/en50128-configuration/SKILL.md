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
| `std/EN50128-2011.md` §6.6 | Change control nine aspects (a–i), §6.6.4.2 re-entry |
| `std/EN50128-2011.md` §6.6.3 | CM normative output documents |
| `std/EN50128-2011.md` §6.2.4.7–8 | VER functional completeness obligation; VER evidence retention |
| `std/EN50128-2011.md` §6.2.4.13(a) | VER report content: identity/configuration of items verified |
| `std/EN50128-2011.md` §6.3.4.9–10 | VAL verification-complete check; baseline stated in Validation Report |
| `std/EN50128-2011.md` §9.1.4.2–3 | Baseline recording and reproducibility |
| `std/EN50128-2011.md` §9.1.4.13 | Deployment Record as tracked evidence artifact |
| `std/EN50128-2011.md` §9.2.4 | Maintenance-phase change assessment and Software Change Records |
| `std/EN50128-2011.md` D.48 | SCM records every version of every significant deliverable |
| `tasks/BASELINE_MANAGEMENT.md` | Authoritative baseline lifecycle: Diagram 1 (gate map), Diagram 2 (creation procedure), terminology, role boundaries |
| `activities/baseline-management.yaml` | Machine-readable form of tasks/BASELINE_MANAGEMENT.md — primary runtime reference for CM baseline capability |
| `DELIVERABLES.md` | Annex C Table C.1 deliverable matrix; per-item 2nd-check assignments |
| `activities/deliverables.yaml` | Machine-readable deliverable catalogue |
| `WORKFLOW.md` | Authority structure (Diagram 1), per-phase loop (Diagram 2), CCB re-entry (Diagram 4) |
| `document-registry.yaml` (this skill dir) | Canonical document-to-path and evidence-to-path lookup table |

---

## Terminology — EN 50128 Only

The following terms are **NOT** used in EN 50128:2011 and MUST NOT appear in any CM
deliverable, agent output, or template:

| Forbidden term | Source standard | EN 50128 equivalent / correct clause |
|---------------|----------------|--------------------------------------|
| FCA (Functional Configuration Audit) | MIL-STD-973 / IEEE 828 | Functional completeness is VER's obligation — §6.2.4.7 |
| PCA (Physical Configuration Audit) | MIL-STD-973 / IEEE 828 | CM presence-check at baseline: §6.6, D.48 |

See `tasks/BASELINE_MANAGEMENT.md` Terminology note for the complete EN 50128 mapping.

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
│       └── manifest.yaml               # CI manifest (Steps 4–5 in tasks/BASELINE_MANAGEMENT.md Diagram 2)
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
│   │   └── Software-Requirements-Verification-Report-template.md
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
│   │   └── Software-Component-Design-Verification-Report-template.md
│   └── evidence/
│       └── design-review/              # design inspection records, checklists
│
├── phase-5-implementation-testing/
│   ├── src/                            # source code tree (IMP-owned)
│   ├── Software-Source-Code-Verification-Report-template.md
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
│   ├── Software-Integration-Verification-Report-template.md
│   ├── Overall-Software-Test-Report.md
│   ├── Software-Validation-Report-template.md
│   ├── Tools-Validation-Report-template.md
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
    ├── Software-Maintenance-Verification-Report-template.md
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

## Baseline Capability — Runtime Reference

For the complete baseline procedure, CM MUST load `activities/baseline-management.yaml`.
That file is the machine-readable form of `tasks/BASELINE_MANAGEMENT.md` (ISA PASS) and is the
single authoritative runtime reference for:

- `baselines[]` — gate-to-baseline map (8 gates, triggers, CI scope, VER/VAL requirements)
- `baseline_creation_procedure` — 7-step procedure (Steps 1–7; pre-conditions, RACI, checks)
- `change_request_baseline_path` — CR re-entry steps CR1–CR8 and archival rules
- `terminology` — EN 50128 audit concept ownership table (no FCA/PCA)
- `cm_role_boundary` — what CM does and does NOT do at a baseline event
- `role_responsibilities` — per-role RACI at baseline creation

**Baseline name → gate → trigger — quick index (detail in `baseline-management.yaml`):**

| Gate | Baseline Name | VER report | VAL role |
|------|--------------|-----------|---------|
| 1 | `planning-baseline` | SQAVR | 2nd check (items 1,3,4; item 5 exempt) |
| 2 | `requirements-baseline` | REQVER | 2nd check |
| 3 | `design-baseline` | ARCHDESIGNVER | 2nd check |
| 4 | `component-design-baseline` | COMPDESIGNVER | 2nd check |
| 5 | `implementation-baseline` | SOURCECODEVER | 2nd check |
| 6 | `integration-baseline` | VER review (INTVER produced in Phase 7) | 2nd check |
| 7 | `release-baseline` ★ | INTVER | Formal VALRPT (§6.3.4.10) |
| 9 | `deployment-baseline` | DEPLOYVER | 2nd check (items 36–39; item 40 exempt) |
| per-CR | `per-cr-baseline` | MAINTVER | 2nd check |

★ `release-baseline` is the most critical. §6.3.4.10 requires VALRPT to explicitly state this
baseline. §9.1.4.3 requires reproducibility throughout the operational lifetime.

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

**§6.6.4.2**: ALL changes SHALL initiate a return to an appropriate lifecycle phase.
CM identifies the re-entry scope; COD authorizes re-entry. See `WORKFLOW.md` Diagram 4
and `activities/baseline-management.yaml` `change_request_baseline_path`.

---

## §6.6.3 Output Documents

Per §6.6.3, the normative CM outputs are:
1. **Modified software and documentation** — all changed CIs at their new versions
2. **Software Change Records** (§9.2.4) — one per approved CR; stored in `changes/`
3. **New Configuration Records** — updated SCMP, configuration status accounting records

The SCMP is a **planning input** written in Phase 1 per §6.6.4.1; it is not itself a §6.6.3
output.

---

## §6.2.4.8 Evidence Retention

Results of each verification activity SHALL be retained in a format defined or referenced in the
SVP. CM is responsible for ensuring VER evidence is stored at canonical `evidence/` paths and
included in the baseline manifest at each gate. **CM stores; VER produces.**

---

## Violation Alarm Protocol

| Severity | Condition | CM action |
|----------|-----------|-----------|
| CRITICAL | Document written to unregistered path | Invoke PM immediately via `task` tool |
| CRITICAL | Baseline created without COD authorization (gate-check not passed) | Invoke PM immediately via `task` tool |
| CRITICAL | CI changed without an approved CR | Invoke PM immediately via `task` tool |
| CRITICAL | VCS tag deleted or force-pushed without CCB approval + Change Record | Invoke PM immediately via `task` tool |
| MAJOR | Evidence artifact not stored in canonical path | Log; report at next status accounting |
| MAJOR | CR missing one of the nine §6.6.4.1(a–i) aspects | Log; return CR to originator |
| MINOR | Version tag missing or inconsistent | Log; correct at next baseline cycle |

---

## Traceability Evidence Management (§6.5.4.15, Table A.9)

**Normative Basis**:
- §5.3.2.7: "For each document, traceability shall be provided in terms of a unique reference number and a defined and documented relationship with other documents."
- §6.5.4.15: "Traceability shall be the subject of configuration management."
- Table A.9 Row 7: Traceability is **MANDATORY** at SIL 3–4

**Role Responsibilities**:

| Activity | Role | Reference |
|----------|------|-----------|
| Create trace links when authoring documents | REQ, DES, IMP, TST, INT | §5.3.2.7 |
| **Manage traceability artifacts under version control** | **CM** | **§6.5.4.15** |
| Verify traceability completeness and correctness | VER | §6.5.4.14–6.5.4.17 |
| Validate traceability (2nd check) | VAL | §6.3, Annex C |
| Enforce traceability at phase gates | COD | §5.3 |

### CM Traceability Workflow (Per Phase)

**Phase 2 (Requirements):**
1. After REQ produces SRS and TST produces Overall SW Test Spec:
2. CM extracts traceability using `workspace.py trace extract` or `trace sync`
3. CM creates CSV evidence files in `evidence/traceability/`:
   - `docS1_to_doc6.csv` (System Requirements → SRS)
   - `docS4_to_doc6.csv` (System Safety Requirements → SRS)
   - `doc6_to_doc7.csv` (SRS → Overall SW Test Spec)
   - `doc7_to_doc6.csv` (Overall SW Test Spec → SRS backward)
4. CM may create Markdown RTM for human readability (optional summary artifact)
5. CM validates before Track A completion:
   ```bash
   cd {workspace_root}
   python3 tools/workspace.py trace validate --sil {sil_level}
   python3 tools/workspace.py trace gate-check --phase requirements --sil {sil_level}
   ```
6. Both commands MUST return ✅ ALL CHECKS PASSED before CM signals Track A complete

**Phase 3 (Architecture & Design):**
1. After DES produces SAS, SDS, SIS and INT produces Integration Test Specs:
2. CM extracts traceability and creates CSV evidence files (14 files total):
   - T3: `doc6_to_doc9.csv` (SRS → SAS)
   - T4: `doc9_to_doc6.csv` (SAS → SRS backward)
   - T5a: `doc10_to_doc9.csv` (SDS → SAS)
   - T5b: `doc10_to_doc6.csv` (SDS → SRS)
   - T5c: `doc10_to_doc11.csv` (SDS → Interface Specs)
   - T10a: Integration Test Spec → Requirements/Architecture/Design/Interfaces (4 files):
     * `doc12_to_doc6.csv`, `doc12_to_doc9.csv`, `doc12_to_doc10.csv`, `doc12_to_doc11.csv`
   - T10b: HW/SW Integration Test Spec → all upstream documents (5 files):
     * `doc13_to_doc6.csv`, `doc13_to_doc9.csv`, `doc13_to_doc10.csv`, `doc13_to_docS1.csv`, `doc13_to_docS2.csv`
3. CM validates:
   ```bash
   python3 tools/workspace.py trace validate --sil {sil_level}
   python3 tools/workspace.py trace gate-check --phase design --sil {sil_level}
   ```

**Phase 4–6**: Similar pattern — CM extracts after document authors complete, validates before Track A complete.

### Traceability Tool Commands (workspace.py)

| Command | Purpose | Example |
|---------|---------|---------|
| `trace extract` | Extract trace links from documents to CSV | `trace extract --from docs/phase-2-requirements/SRS.md --to docs/phase-3-architecture-design/SAS.md --output evidence/traceability/doc6_to_doc9.csv` |
| `trace sync` | Synchronize Markdown RTM ↔ CSV files | `trace sync --project {project_name}` |
| `trace create` | Manually create trace link CSV file | `trace create --from doc6 --to doc9 --output evidence/traceability/doc6_to_doc9.csv` |
| `trace validate` | Validate all traceability for SIL level | `trace validate --sil 3` |
| `trace gate-check` | Check phase gate readiness | `trace gate-check --phase design --sil 3` |
| `trace query` | Query specific trace relationships | `trace query --from doc6 --to doc9` |
| `trace report` | Generate traceability report | `trace report --from doc6 --to doc9` |

**CSV File Format** (required for automated validation):
```csv
source_id,target_id,rationale,verification_method,status
SRS-REQ-001,SAS-COMP-DCS,DCS component implements door control requirements,Design review + test,verified
```

**Storage Location**:
- CSV files (normative evidence): `{workspace_root}/evidence/traceability/*.csv`
- Markdown RTM (optional summary): `{workspace_root}/docs/traceability/Requirements-Traceability-Matrix.md`

**Baseline Integration**:
- CM includes all CSV files in `evidence/traceability/` in baseline manifest
- VER verification reports reference traceability validation results
- COD gate-check requires `trace validate` and `trace gate-check` to pass

**Critical Rule**: CM MUST NOT signal Track A complete until both validation commands return ✅ ALL CHECKS PASSED. Missing or incomplete traceability evidence will BLOCK the phase gate.

### Document ID Mapping Reference

See `TRACEABILITY.md` Section 6 for complete mapping. Quick reference:

| Document | Doc ID | Phase |
|----------|--------|-------|
| System Requirements Specification | S1 (docS1) | 0 |
| System Architecture Description | S2 (docS2) | 0 |
| System Safety Plan | S3 (docS3) | 0 |
| System Safety Requirements | S4 (docS4) | 0 |
| Software Requirements Specification | 6 (doc6) | 2 |
| Overall Software Test Specification | 7 (doc7) | 2 |
| Software Architecture Specification | 9 (doc9) | 3 |
| Software Design Specification | 10 (doc10) | 3 |
| Software Interface Specifications | 11 (doc11) | 3 |
| SW Integration Test Specification | 12 (doc12) | 3 |
| SW/HW Integration Test Specification | 13 (doc13) | 3 |

Full mapping: `DELIVERABLES.md` Annex C Table C.1.
