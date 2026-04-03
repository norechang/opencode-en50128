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

### 3.4 Traceability Evidence Management (§5.3.2.7, §6.5.4.14-17)

**Normative Requirement**: EN 50128:2011 §5.3.2.7 requires bidirectional traceability for all deliverables. §6.5.4.14-17 requires traceability to be checked at each phase gate by VER and enforced by COD.

**Official Workflow**: This platform uses **manual CSV creation** as the official traceability workflow. CM reads deliverables and extracts trace relationships into CSV files.

**Complete workflow specification**: See **TRACEABILITY.md Section 13** for:
- Section 13.1: Roles and responsibilities
- Section 13.1.2: CSV file naming convention
- Section 13.1.3: CSV file format specification
- Section 13.1.4: Validation commands
- Section 13.2: Per-phase workflow (Phases 2-7)
- Section 13.3: Tool support (mandatory vs. optional)
- Section 13.4: CCB change request impact procedures
- Section 13.5: TDC Phase 3 example

**Tool usage**: See **tools/README_TRACEABILITY.md** for complete command reference and **activities/traceability.yaml** for machine-consumable T-rule definitions.

#### 3.4.1 Quick Reference for CM Agents

**CM Responsibilities** (from TRACEABILITY.md Section 13.1.1):

| Responsibility | When | Command/Action |
|----------------|------|----------------|
| **Create traceability CSV files** | After document authors complete deliverables | Read documents; extract trace relationships; write CSV files to `evidence/traceability/` using naming convention `doc{source}_to_doc{target}.csv` |
| **Validate CSV completeness** | Before submitting to VER | `python3 tools/workspace.py trace validate --sil {project_sil}` |
| **Pre-gate check** | Before COD gate | `python3 tools/workspace.py trace gate-check --phase {phase} --sil {project_sil}` |
| **Update baselines** | After COD gate PASS | Tag CSV files in git with phase baseline |
| **Re-trace after CCB changes** | After approved Change Request | Update affected CSV files (see TRACEABILITY.md Section 13.4); re-validate |

#### 3.4.2 CSV File Format Quick Reference

**Mandatory Columns** (from TRACEABILITY.md Section 13.1.3):
```csv
source_id,source_type,target_id,target_type,link_type,rationale,verified,verified_by,verified_date,source_document,target_document
```

**Example Row**:
```csv
COMP-001-SKN,component,REQ-SAFE-007,requirement,implements,SKN implements safety interlock requirement,true,VER,2026-03-28,doc9,doc6
```

**Artifact Types**: `requirement`, `component`, `module`, `function`, `test_case`, `interface`, `hazard`

**Link Types**: `implements`, `traces_to`, `allocated_to`, `tests`, `verifies`, `refines`, `derives_from`

**Storage Location**: `evidence/traceability/` (in project baseline)

#### 3.4.3 Per-Phase CSV File Checklist

See **TRACEABILITY.md Section 13.2** for detailed per-phase workflows. Quick reference:

| Phase | Expected Files | Key T-Rules | Validation Command |
|-------|---------------|-------------|-------------------|
| **2: Requirements** | 3-4 CSV files | T1, T2, T9 | `trace gate-check --phase requirements --sil {sil}` |
| **3: Architecture & Design** | 13-15 CSV files | T3, T4, T5a-c, T8, T9, T10a-b | `trace gate-check --phase design --sil {sil}` |
| **4: Component Design** | 2 CSV files | T6, T11 | `trace gate-check --phase component-design --sil {sil}` |
| **5: Implementation & Testing** | 3 CSV files | T7, T12 | `trace gate-check --phase implementation-testing --sil {sil}` |
| **6: Integration** | 4 CSV files | T12 | `trace gate-check --phase integration --sil {sil}` |
| **7: Validation** | 3 CSV files | T12, T13 | `trace gate-check --phase validation --sil {sil}` |

**Document ID Mapping** (from TRACEABILITY.md Section 13.1.2):
- docS1 = System Requirements Specification
- docS2 = System Architecture Description
- docS4 = System Safety Requirements Specification
- doc6 = Software Requirements Specification [Phase 2]
- doc7 = Overall Software Test Specification [Phase 2]
- doc9 = Software Architecture Specification [Phase 3]
- doc10 = Software Design Specification [Phase 3]
- doc11 = Software Interface Specifications [Phase 3]
- doc12 = Software Integration Test Specification [Phase 3]
- doc13 = Software/Hardware Integration Test Specification [Phase 3]
- doc15 = Software Component Design Specification [Phase 4]
- doc16 = Software Component Test Specification [Phase 4]
- doc18 = Software Source Code and Supporting Documentation [Phase 5]
- doc20 = Software Component Test Report [Phase 5]
- doc21 = Software Integration Test Report [Phase 6]
- doc22 = Software/Hardware Integration Test Report [Phase 6]
- doc24 = Overall Software Test Report [Phase 7]
- doc25 = Software Validation Report [Phase 7]

#### 3.4.4 Tool Usage Quick Reference

**Mandatory Tools** (from TRACEABILITY.md Section 13.3):
```bash
# Validate all CSV files
python3 tools/workspace.py trace validate --sil 3

# Gate check for specific phase
python3 tools/workspace.py trace gate-check --phase design --sil 3
```

**Optional Tools** (use with caution):
- `trace extract` — ⚠ OPTIONAL/EXPERIMENTAL (may produce incorrect semantic mappings)
- `trace sync` — Synchronize CSV ↔ JSON ↔ Markdown formats
- `trace query` — Query traceability links
- `trace visualize` — Generate diagrams

**Recommendation**: Always use manual CSV creation; use mandatory validation tools only.

#### 3.4.5 Example: TDC Phase 3 Workflow

See **TRACEABILITY.md Section 13.5** for complete TDC Phase 3 example (19 CSV files, 593 relationships, 100% coverage).

**Reference**: `examples/TDC/evidence/traceability/` contains the complete CSV file set demonstrating manual workflow for SIL 3 project.

---

## 4. Software Configuration Management Report (SCMR)

See DELIVERABLES.md for SCMR template and requirements (EN 50128:2011 Annex C, Document 27).
