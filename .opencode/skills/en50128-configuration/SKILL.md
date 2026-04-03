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

**Official Workflow**: This platform uses **manual CSV creation** as the official traceability workflow. CM reads deliverables and extracts trace relationships into CSV files using the canonical naming convention `doc{source}_to_doc{target}.csv`.

#### 3.4.1 CM Responsibilities

| Responsibility | When | How |
|----------------|------|-----|
| **Create traceability CSV files** | After document authors complete deliverables | Read documents; extract trace relationships; write CSV files using Write tool |
| **Validate CSV completeness** | Before submitting to VER | Run `trace validate --phase X --sil Y` |
| **Pre-gate check** | Before COD gate | Run `trace gate-check --phase X --sil Y` |
| **Update baselines** | After COD gate PASS | Tag CSV files in git with phase baseline |
| **Re-trace after CCB changes** | After approved Change Request | Update affected CSV files; re-validate |

#### 3.4.2 Per-Phase Workflow

**Phase 2: Requirements**

After REQ+SAF complete SRS [6]:

1. **Read** `docs/phase-2-requirements/Software-Requirements-Specification.md`
2. **Identify** all requirements (REQ-XXX-YYY-###) and their system sources (from S1, S4)
3. **Create CSV files**:
   - `evidence/traceability/doc6_to_docS1.csv` — SRS requirements → System Requirements Specification
   - `evidence/traceability/doc6_to_docS2.csv` — SRS requirements → System Architecture Description (if applicable)
4. **Format**: Use standard CSV format (see Section 3.4.4)
5. **Validate**: `python3 tools/workspace.py trace validate --phase requirements --sil {project_sil}`
6. **Gate check**: `python3 tools/workspace.py trace gate-check --phase requirements --sil {project_sil}`

Expected files: 2 CSV files (T1, T2)

---

**Phase 3: Architecture & Design**

After DES+SAF complete SAS [9], SDS [10], SIS [11], and INT completes test specs [12, 13]:

1. **Read** all Phase 3 deliverables
2. **Extract** component/module IDs and their trace relationships to requirements
3. **Create CSV files**:
   - `doc9_to_doc6.csv` — SAS components → SRS requirements (T3, T4)
   - `doc10_to_doc9.csv` — SDS modules → SAS components (T5a)
   - `doc10_to_doc6.csv` — SDS modules → SRS requirements (T5b)
   - `doc10_to_doc11.csv` — SDS modules → Interface Specifications (T5c)
   - `doc12_to_doc6.csv` — SW Integration Test Spec → SRS (T10a)
   - `doc12_to_doc9.csv` — SW Integration Test Spec → SAS (T10a)
   - `doc12_to_doc10.csv` — SW Integration Test Spec → SDS (T10a)
   - `doc12_to_doc11.csv` — SW Integration Test Spec → SIS (T10a)
   - `doc13_to_docS1.csv` — SW/HW Integration Test Spec → System Requirements (T10b)
   - `doc13_to_docS2.csv` — SW/HW Integration Test Spec → System Architecture (T10b)
   - `doc13_to_doc6.csv` — SW/HW Integration Test Spec → SRS (T10b)
   - `doc13_to_doc9.csv` — SW/HW Integration Test Spec → SAS (T10b)
   - `doc13_to_doc10.csv` — SW/HW Integration Test Spec → SDS (T10b)
4. **Validate**: `python3 tools/workspace.py trace validate --phase design --sil {project_sil}`
5. **Gate check**: `python3 tools/workspace.py trace gate-check --phase design --sil {project_sil}`

Expected files: 13-14 CSV files (T3, T4, T5a-c, T10a-b)

---

**Phase 4: Component Design**

After DES completes Software Component Design Spec [15] and TST completes Component Test Spec [16]:

1. **Read** component design and test specifications
2. **Create CSV files**:
   - `doc15_to_doc10.csv` — Component designs → SDS (T6)
   - `doc16_to_doc15.csv` — Component tests → Component designs (T11)
3. **Validate**: `python3 tools/workspace.py trace validate --phase component-design --sil {project_sil}`
4. **Gate check**: `python3 tools/workspace.py trace gate-check --phase component-design --sil {project_sil}`

Expected files: 2 CSV files (T6, T11)

---

**Phase 5: Implementation & Testing**

After IMP completes source code [18] and TST executes component tests [20]:

1. **Read** source code headers and test reports
2. **Create CSV files**:
   - `doc18_to_doc15.csv` — Source modules → Component designs (T7)
   - `doc20_to_doc16.csv` — Component test results → Component test specs (T12)
   - `doc20_to_doc18.csv` — Component test results → Source code (executed against)
3. **Validate**: `python3 tools/workspace.py trace validate --phase implementation-testing --sil {project_sil}`
4. **Gate check**: `python3 tools/workspace.py trace gate-check --phase implementation-testing --sil {project_sil}`

Expected files: 3 CSV files (T7, T12)

---

**Phase 6: Integration**

After INT+TST execute integration tests [21, 22]:

1. **Read** integration test reports
2. **Create CSV files**:
   - `doc21_to_doc12.csv` — SW Integration Test Report → SW Integration Test Spec (T12)
   - `doc21_to_doc18.csv` — SW Integration Test Report → Source code (executed against)
   - `doc22_to_doc13.csv` — SW/HW Integration Test Report → SW/HW Integration Test Spec (T12)
   - `doc22_to_doc18.csv` — SW/HW Integration Test Report → Source code (executed against)
3. **Validate**: `python3 tools/workspace.py trace validate --phase integration --sil {project_sil}`
4. **Gate check**: `python3 tools/workspace.py trace gate-check --phase integration --sil {project_sil}`

Expected files: 4 CSV files (T12)

---

**Phase 7: Validation**

After TST completes Overall Software Test Report [24] and VAL completes Validation Report [25]:

1. **Read** validation reports
2. **Create CSV files**:
   - `doc24_to_doc7.csv` — Overall SW Test Report → Overall SW Test Spec (T12)
   - `doc25_to_doc24.csv` — Validation Report → Overall SW Test Report
   - `doc25_to_doc6.csv` — Validation Report → SRS (confirms all requirements validated, T13)
3. **Validate**: `python3 tools/workspace.py trace validate --phase validation --sil {project_sil}`
4. **Gate check**: `python3 tools/workspace.py trace gate-check --phase validation --sil {project_sil}`

Expected files: 3 CSV files (T12, T13)

#### 3.4.3 CSV File Naming Convention

**Format**: `doc{source_id}_to_doc{target_id}.csv`

**Document ID Mapping** (from TRACEABILITY.md Section 11):

| Doc ID | Document Name | Phase |
|--------|--------------|-------|
| docS1 | System Requirements Specification | 0 |
| docS2 | System Architecture Description | 0 |
| docS3 | System Safety Plan | 0 |
| docS4 | System Safety Requirements Specification | 0 |
| doc6 | Software Requirements Specification | 2 |
| doc7 | Overall Software Test Specification | 2 |
| doc9 | Software Architecture Specification | 3 |
| doc10 | Software Design Specification | 3 |
| doc11 | Software Interface Specifications | 3 |
| doc12 | Software Integration Test Specification | 3 |
| doc13 | Software/Hardware Integration Test Specification | 3 |
| doc15 | Software Component Design Specification | 4 |
| doc16 | Software Component Test Specification | 4 |
| doc18 | Software Source Code and Supporting Documentation | 5 |
| doc20 | Software Component Test Report | 5 |
| doc21 | Software Integration Test Report | 6 |
| doc22 | Software/Hardware Integration Test Report | 6 |
| doc24 | Overall Software Test Report | 7 |
| doc25 | Software Validation Report | 7 |

**Examples**:
- `doc6_to_docS1.csv` — SRS → System Requirements
- `doc9_to_doc6.csv` — SAS → SRS
- `doc18_to_doc15.csv` — Source Code → Component Design

#### 3.4.4 CSV File Format

**Mandatory Columns**:
```csv
source_id,source_type,target_id,target_type,link_type,rationale,verified,verified_by,verified_date,source_document,target_document
```

**Example Row**:
```csv
COMP-001-SKN,component,REQ-SAFE-007,requirement,implements,SKN implements safety interlock requirement,true,VER,2026-03-28,doc9,doc6
```

**Column Definitions**:

| Column | Type | Description | Example |
|--------|------|-------------|---------|
| `source_id` | string | Source artifact ID | `COMP-001-SKN` |
| `source_type` | string | Source artifact type | `component` |
| `target_id` | string | Target artifact ID | `REQ-SAFE-007` |
| `target_type` | string | Target artifact type | `requirement` |
| `link_type` | string | Relationship type | `implements`, `tests`, `verifies` |
| `rationale` | string | Human-readable explanation | `SKN implements safety interlock requirement` |
| `verified` | boolean | Has VER verified this link? | `true`, `false` |
| `verified_by` | string | Role who verified | `VER` |
| `verified_date` | string | Verification date (ISO 8601) | `2026-03-28` |
| `source_document` | string | Source document ID | `doc9` |
| `target_document` | string | Target document ID | `doc6` |

**Artifact Types**: `requirement`, `component`, `module`, `function`, `test_case`, `interface`, `hazard`

**Link Types**: `implements`, `traces_to`, `allocated_to`, `tests`, `verifies`, `refines`, `derives_from`

#### 3.4.5 Validation Commands

**Validate CSV completeness** (checks coverage thresholds per SIL):
```bash
python3 tools/workspace.py trace validate --phase design --sil 3
```

**Output**:
```
======================================================================
Traceability Validation Report
======================================================================
Project:    TDC
SIL Level:  3
Threshold:  100%
======================================================================

✓ PASS  doc9_to_doc6.csv
       Coverage: 100.0% (51/51)

✓ PASS  doc10_to_doc9.csv
       Coverage: 100.0% (30/30)

======================================================================
Overall Status: ✓ PASS
======================================================================
```

**Gate check** (validates all T-rules for phase):
```bash
python3 tools/workspace.py trace gate-check --phase design --sil 3
```

**Output**:
```
======================================================================
Traceability Gate Check: Phase 3 (Architecture & Design)
======================================================================
SIL Level: 3 (100% coverage MANDATORY)

Rule T3: [6] → [9] (SRS requirements → SAS components)
  ✓ PASS: 100.0% coverage (51/51 requirements traced)

Rule T4: [9] → [6] (SAS components → SRS requirements)
  ✓ PASS: 100.0% coverage (8/8 components traced)

Rule T5a: [10] → [9] (SDS modules → SAS components)
  ✓ PASS: 100.0% coverage (30/30 modules traced)

Rule T5b: [10] → [6] (SDS modules → SRS requirements)
  ✓ PASS: 100.0% coverage (30/30 modules traced)

======================================================================
Overall Gate Status: ✓ PASS
======================================================================
```

#### 3.4.6 Tool Support

**Mandatory Tools** (required for compliance):
- `trace validate` — Coverage validation per SIL thresholds
- `trace gate-check` — Per-phase rule validation (T1-T15)

**Optional Tools** (not required for compliance):
- `trace extract` — ⚠ **OPTIONAL/EXPERIMENTAL** — Auto-extraction using proximity heuristics (may produce incorrect semantic mappings)
- `trace sync` — Synchronize CSV ↔ JSON ↔ Markdown formats
- `trace query` — Query traceability links
- `trace visualize` — Generate Mermaid/DOT diagrams

**Recommendation**: Use manual CSV creation for authoring; use `trace validate` and `trace gate-check` for verification.

#### 3.4.7 CCB Change Request Impact

When a Change Request (CR) is approved by the CCB, CM MUST:

1. **Identify affected phases** (per TRACEABILITY.md Section 10)
2. **Update all affected CSV files**
3. **Re-validate**: `python3 tools/workspace.py trace validate --phase X --sil Y`
4. **Submit to VER** for re-verification
5. **COD re-runs gate check** after VER approval

**Example**: CR changes SRS requirement REQ-SAFE-007
- Affected phases: 2-7 (all downstream phases)
- Affected CSV files: `doc9_to_doc6.csv`, `doc10_to_doc6.csv`, `doc18_to_doc15.csv` (via propagation), all test trace files
- CM must update all affected CSVs and re-validate

#### 3.4.8 Example: TDC Phase 3 Traceability

**TDC Project** (SIL 3) created 19 CSV files for Phase 3:

| File | Relationships | Rule | Status |
|------|--------------|------|--------|
| `doc6_to_docS1.csv` | 51 SRS → System Requirements | T1 | ✅ Validated |
| `doc6_to_docS2.csv` | 8 SRS → System Architecture | T1 | ✅ Validated |
| `doc9_to_doc6.csv` | 51 Components → Requirements | T3, T4 | ✅ Validated |
| `doc10_to_doc9.csv` | 30 Modules → Components | T5a | ✅ Validated |
| `doc10_to_doc6.csv` | 98 Modules → Requirements | T5b | ✅ Validated |
| `doc10_to_doc11.csv` | 30 Modules → Interfaces | T5c | ✅ Validated |
| `doc12_to_doc*.csv` | 4 files (Integration tests) | T10a | ✅ Validated |
| `doc13_to_doc*.csv` | 5 files (HW/SW tests) | T10b | ✅ Validated |

**Total**: 19 CSV files, 593 traceability relationships, 100% coverage (SIL 3 compliant)

**Validation**:
```bash
cd examples/TDC
python3 ../../tools/workspace.py trace validate --sil 3
# ✓ PASS

python3 ../../tools/workspace.py trace gate-check --phase design --sil 3
# ✓ PASS (all T-rules satisfied)
```

**Reference**: See `examples/TDC/evidence/traceability/` for complete CSV file set.

#### 3.4.9 References

- **TRACEABILITY.md** — Section 13: Traceability Evidence Management Workflow
- **TRACEABILITY.md** — Section 9: Normative Traceability Rules (T1-T15)
- **TRACEABILITY.md** — Section 11: Document Traceability Matrix
- **tools/README_TRACEABILITY.md** — Tool usage documentation
- **EN 50128:2011** — §5.3.2.7 (traceability), §6.5.4.14-17 (traceability QA)
