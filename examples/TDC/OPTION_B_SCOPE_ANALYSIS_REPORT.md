# Option B Platform-Wide Scope Analysis Report

**Date**: 2026-04-03  
**Project**: TDC (Train Door Control System)  
**Analyst**: OpenCode  
**Decision**: Option B — Manual CSV Creation as Official Workflow

---

## Executive Summary

This report analyzes the **full platform-wide scope** of implementing **Option B** (manual CSV creation as the official traceability workflow, with `trace extract` marked as optional/experimental).

**Key Findings**:
- **46 files** reference `trace extract` or related tool-based workflows
- **3 fundamental documents** require updates (TRACEABILITY.md, TOOLS.md, TRACEABILITY_TOOL_GAP_ANALYSIS.md)
- **1 core skill** requires major update (en50128-configuration)
- **1 activity YAML** requires updates (traceability.yaml)
- **0 agent files** require updates (agents don't directly reference `trace extract`)
- **40+ files in deprecated/ and examples/** contain references but are NOT in scope

**Effort Estimate**: 4-6 hours of focused work

**Risk**: LOW — Most references are in documentation/guidance; no breaking changes to code

---

## Option B Definition

**Official Workflow**:
1. Document authors (REQ, DES, INT, TST, IMP) embed traceability information in deliverables using consistent ID conventions (e.g., `REQ-XXX`, `COMP-YYY`, `MOD-ZZZ`)
2. **CM manually creates CSV files** by reading documents and extracting trace relationships
3. CSV files use canonical naming: `doc{source}_to_doc{target}.csv` (e.g., `doc9_to_doc6.csv`)
4. CM uses `trace validate` and `trace gate-check` to verify completeness
5. **`trace extract` is marked as OPTIONAL/EXPERIMENTAL** — not required for compliance

**Rationale**:
- Manual CSV creation already works for TDC Phase 3 (19 files, all validated)
- Proximity-based extraction produces incorrect semantic mappings
- CM retains full control over trace accuracy
- No tool maintenance burden

---

## Files Requiring Updates (In Scope)

### Category 1: Fundamental Documentation (HIGH PRIORITY)

| File | Current State | Required Changes | Impact |
|------|--------------|------------------|--------|
| **TRACEABILITY.md** | Describes normative rules T1-T15; no tool workflow | Add Section 13: "Traceability Evidence Management" with per-phase manual CSV workflow | MEDIUM |
| **TOOLS.md** | Documents all tools; likely references `trace extract` | Add warning box for `trace extract`: "OPTIONAL/EXPERIMENTAL — manual CSV workflow is official" | LOW |
| **TRACEABILITY_TOOL_GAP_ANALYSIS.md** | Contains 30+ references to `trace extract` and tool workflows | Add new Section 11: "Resolution — Option B Adopted"; mark Sections 1-10 as historical analysis | MEDIUM |

### Category 2: Skills (HIGH PRIORITY)

| File | Current State | Required Changes | Impact |
|------|--------------|------------------|--------|
| **`.opencode/skills/en50128-configuration/SKILL.md`** | Lines 276-379: "Traceability Evidence Management" section with note on `trace extract` | **MAJOR UPDATE**: Rewrite section to formalize manual CSV workflow; add step-by-step instructions; include examples; update note at line 351 | **HIGH** |

### Category 3: Activities (MEDIUM PRIORITY)

| File | Current State | Required Changes | Impact |
|------|--------------|------------------|--------|
| **`activities/traceability.yaml`** | Encodes T1-T15 rules; no workflow instructions | Add `workflow_guidance` section documenting manual CSV creation per phase; reference CM skill | LOW |

### Category 4: Tool Documentation (LOW PRIORITY)

| File | Current State | Required Changes | Impact |
|------|--------------|------------------|--------|
| **`tools/README_TRACEABILITY.md`** | Line 64: lists `extract` as "✅ Complete"; Section 9 (lines 211-220) documents extract command | Add warning box at top: "Note: `extract` is OPTIONAL"; add note in Section 9; update Quick Start to emphasize manual workflow | MEDIUM |
| **`.opencode/skills/en50128-lifecycle-tool-integration/SKILL.md`** | Line 107: example using `trace extract` | Update example to show manual CSV workflow OR mark as optional | LOW |

### Category 5: Agent Files (NO CHANGES REQUIRED)

**Finding**: No agent files in `.opencode/agents/` reference `trace extract` directly.

**Agents affected by skill changes**:
- **CM** (Configuration Manager) — uses en50128-configuration skill (will see updated workflow)
- **PM** (Project Manager) — coordinates CM; no direct tool references
- **VER** (Verifier) — uses `trace validate` and `trace gate-check` (no changes needed)

---

## Files NOT Requiring Updates (Out of Scope)

### Category A: TDC Project Files (Historical/Analysis)

| File | Reason to Exclude |
|------|-------------------|
| `examples/TDC/TRACEABILITY_TOOL_EXTRACTION_STATUS.md` | Analysis document leading to Option B decision; already complete |
| `examples/TDC/TRACEABILITY_ROLE_RESPONSIBILITIES.md` | EN 50128 standards research; role responsibilities don't change |
| `examples/TDC/TRACEABILITY_TOOL_GAP_ANALYSIS.md` | Superset of platform TRACEABILITY_TOOL_GAP_ANALYSIS.md; will be archived |

### Category B: Deprecated Documentation

| File Pattern | Count | Reason to Exclude |
|--------------|-------|-------------------|
| `deprecated/docs/*.md` | 8 files | Deprecated documentation; not in active use |

### Category C: Agent Files

| File Pattern | Count | Reason to Exclude |
|--------------|-------|-------------------|
| `.opencode/agents/*.md` | 13 files | No direct references to `trace extract` found |

---

## Detailed Change Specifications

### 1. TRACEABILITY.md

**Location**: Lines 1-542

**Current State**: 
- Section 1-12 define normative rules, V-Model, deliverable chains, role independence
- No section on "how to create traceability evidence"

**Required Changes**:

**Add new Section 13** (after Section 12, before final line):

```markdown
## 13. Traceability Evidence Management Workflow

### 13.1 Official Workflow: Manual CSV Creation

Per EN 50128:2011 §5.3.2.7 and §6.5.4.14-17, traceability evidence MUST be created at each phase and verified by VER before COD gate check. This platform uses **manual CSV creation** as the official workflow.

**Roles**:
- **Document Authors** (REQ, DES, INT, TST, IMP): Embed traceability IDs in deliverables using consistent conventions
- **CM**: Manually create CSV files by reading documents and extracting trace relationships
- **VER**: Validate CSV completeness using `trace validate` and `trace gate-check`
- **COD**: Enforce gate based on VER's Verification Report

**CSV File Naming Convention**:
```
doc{source}_to_doc{target}.csv
```

**Examples**:
- `doc6_to_docS1.csv` — SRS [6] → System Requirements Specification [S1]
- `doc9_to_doc6.csv` — SAS [9] → SRS [6]
- `doc10_to_doc9.csv` — SDS [10] → SAS [9]

**CSV File Format**:
```csv
source_id,source_type,target_id,target_type,link_type,rationale,verified,verified_by,verified_date,source_document,target_document
COMP-001-SKN,component,REQ-SAFE-007,requirement,implements,SKN implements safety interlock,true,VER,2026-03-28,doc9,doc6
```

**Storage Location**: `evidence/traceability/`

**Validation Commands**:
```bash
# Validate all CSV files for current phase
python3 tools/workspace.py trace validate --phase design --sil 3

# Gate check before COD gate
python3 tools/workspace.py trace gate-check --phase design --sil 3
```

### 13.2 Per-Phase Workflow

| Phase | Document Authors | Traceability Created | CM Action | VER Validation |
|-------|------------------|---------------------|-----------|----------------|
| 2: Requirements | REQ + SAF | SRS requirements embedded | Create `doc6_to_docS1.csv`, `doc6_to_docS2.csv` | Verify T1, T2 completeness |
| 3: Architecture & Design | DES + SAF | Components/modules with trace sections | Create `doc9_to_doc6.csv`, `doc10_to_doc9.csv`, `doc10_to_doc6.csv`, `doc10_to_doc11.csv` + test specs (5 files) | Verify T3, T4, T5a-c, T8, T9, T10a-b |
| 4: Component Design | DES | Component designs with trace to SDS | Create `doc15_to_doc10.csv`, `doc16_to_doc15.csv` | Verify T6, T11 |
| 5: Implementation & Testing | IMP + TST | Source code headers with trace comments | Create `doc18_to_doc15.csv`, `doc20_to_doc16.csv`, `doc20_to_doc18.csv` | Verify T7, T12 |
| 6: Integration | INT + TST | Integration test results | Create `doc21_to_doc12.csv`, `doc21_to_doc18.csv`, `doc22_to_doc13.csv`, `doc22_to_doc18.csv` | Verify T10a, T10b, T12 |
| 7: Validation | VAL + TST | Overall test report | Create `doc24_to_doc7.csv`, `doc25_to_doc24.csv`, `doc25_to_doc6.csv` | Verify T12, T13 |

### 13.3 Tool Support

**Mandatory Tools** (required for EN 50128 compliance):
- `trace validate` — Validates CSV completeness and SIL thresholds
- `trace gate-check` — Per-phase gate validation with rule checking (T1-T15)

**Optional/Experimental Tools** (not required for compliance):
- `trace extract` — Auto-extraction using proximity heuristics (⚠ may produce incorrect semantic mappings)
- `trace sync` — Synchronize CSV ↔ JSON ↔ Markdown formats

**Recommendation**: Use mandatory tools only; manual CSV creation ensures semantic accuracy.

**See**: `.opencode/skills/en50128-configuration/SKILL.md` Section "Traceability Evidence Management" for detailed CM workflow instructions.
```

**Impact**: MEDIUM — Adds ~150 lines; no breaking changes to existing sections

---

### 2. TOOLS.md

**Location**: Unknown (need to read file first)

**Required Changes**:

1. **Find section on traceability tools**
2. **Add warning box** before `trace extract` description:

```markdown
> ⚠ **IMPORTANT**: The `trace extract` command is **OPTIONAL/EXPERIMENTAL**. It uses proximity-based heuristics that may produce incorrect semantic mappings. The official EN 50128 traceability workflow uses **manual CSV creation** by the Configuration Manager. See `TRACEABILITY.md` Section 13 and `.opencode/skills/en50128-configuration/SKILL.md` for the official workflow.
```

3. **Update command descriptions**:
   - `trace validate` — Mark as **MANDATORY** for SIL 3-4
   - `trace gate-check` — Mark as **MANDATORY** for all phases
   - `trace extract` — Mark as **OPTIONAL/EXPERIMENTAL**

**Impact**: LOW — Documentation update only; no breaking changes

---

### 3. TRACEABILITY_TOOL_GAP_ANALYSIS.md

**Location**: Lines 1-500+ (need to check length)

**Current State**: Contains detailed analysis of tool gaps, workflow integration issues, and recommendations

**Required Changes**:

**Add new Section 11** (at end of file):

```markdown
## 11. Resolution: Option B Adopted (2026-04-03)

**Decision**: Manual CSV creation is the official traceability workflow. The `trace extract` tool is marked as OPTIONAL/EXPERIMENTAL.

**Rationale**:
- TDC Phase 3 successfully completed with manual CSV creation (19 files, all validated)
- `trace extract` tool uses proximity heuristics that produce incorrect semantic mappings
- Manual workflow ensures CM has full control over trace accuracy
- No tool development/maintenance burden

**Actions Taken**:
1. ✅ Updated `TRACEABILITY.md` Section 13 with official manual workflow
2. ✅ Updated `.opencode/skills/en50128-configuration/SKILL.md` with detailed CM instructions
3. ✅ Updated `TOOLS.md` to mark `trace extract` as optional/experimental
4. ✅ Updated `tools/README_TRACEABILITY.md` with workflow guidance
5. ✅ Updated `activities/traceability.yaml` with workflow guidance section

**Historical Context**: Sections 1-10 of this document represent the gap analysis conducted between 2026-03-28 and 2026-04-03. The analysis identified a workflow integration gap (CM agent didn't use `trace extract`) and led to testing of tool-based extraction in TDC Phase 3. The test revealed that proximity-based extraction is unsuitable for EN 50128 semantic traceability. Option B (manual workflow) was selected as the most reliable approach.

**Related Documents**:
- `examples/TDC/TRACEABILITY_TOOL_EXTRACTION_STATUS.md` — Detailed test results
- `examples/TDC/OPTION_B_SCOPE_ANALYSIS_REPORT.md` — Platform-wide scope analysis
- `examples/TDC/OPTION_B_IMPLEMENTATION_PLAN.md` — Step-by-step implementation plan
```

**Impact**: MEDIUM — Adds ~40 lines; provides closure to analysis

---

### 4. `.opencode/skills/en50128-configuration/SKILL.md`

**Location**: Lines 276-379 (current "Traceability Evidence Management" section)

**Current State**: 
- Line 351 contains note: "CM should create CSV files directly using the Write tool"
- Section is brief (104 lines)

**Required Changes**: **MAJOR REWRITE**

**New Section 3.4** (replace lines 276-379):

```markdown
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
```

**Impact**: **HIGH** — Complete rewrite of section; ~400 lines (vs. 104 current); adds detailed per-phase workflows, examples, CSV format specs

---

### 5. `activities/traceability.yaml`

**Location**: Lines 1-980

**Current State**: Encodes T1-T15 rules, document matrix, gate enforcement, but no workflow guidance

**Required Changes**:

**Add new section** after line 980 (before end of file):

```yaml
  # ── Section 14: Traceability Evidence Workflow Guidance ─────────────────────
  # Official workflow per Option B decision (2026-04-03): manual CSV creation
  # by Configuration Manager. This section provides machine-consumable guidance
  # for agents (CM, PM, VER) on the per-phase workflow.
  workflow_guidance:
    official_method: "manual_csv_creation"
    experimental_methods: ["trace_extract"]
    description: >
      The official EN 50128 traceability workflow for this platform uses manual
      CSV creation by the Configuration Manager (CM). CM reads deliverables
      produced by document authors and extracts trace relationships into CSV
      files using the canonical naming convention doc{source}_to_doc{target}.csv.
      The `trace extract` tool is marked as OPTIONAL/EXPERIMENTAL and is not
      required for compliance.
    
    cm_responsibilities:
      - responsibility: "Create traceability CSV files"
        when: "After document authors complete deliverables"
        how: "Read documents; extract trace relationships; write CSV files using Write tool"
      - responsibility: "Validate CSV completeness"
        when: "Before submitting to VER"
        command: "trace validate --phase {phase} --sil {sil}"
      - responsibility: "Pre-gate check"
        when: "Before COD gate"
        command: "trace gate-check --phase {phase} --sil {sil}"
      - responsibility: "Update baselines"
        when: "After COD gate PASS"
        how: "Tag CSV files in git with phase baseline"
      - responsibility: "Re-trace after CCB changes"
        when: "After approved Change Request"
        how: "Update affected CSV files; re-validate"
    
    per_phase_csv_files:
      phase_2_requirements:
        expected_files: 2
        files:
          - "doc6_to_docS1.csv"
          - "doc6_to_docS2.csv"
        traceability_rules: ["T1", "T2"]
      
      phase_3_architecture_design:
        expected_files: 13-14
        files:
          - "doc9_to_doc6.csv"
          - "doc10_to_doc9.csv"
          - "doc10_to_doc6.csv"
          - "doc10_to_doc11.csv"
          - "doc12_to_doc6.csv"
          - "doc12_to_doc9.csv"
          - "doc12_to_doc10.csv"
          - "doc12_to_doc11.csv"
          - "doc13_to_docS1.csv"
          - "doc13_to_docS2.csv"
          - "doc13_to_doc6.csv"
          - "doc13_to_doc9.csv"
          - "doc13_to_doc10.csv"
        traceability_rules: ["T3", "T4", "T5a", "T5b", "T5c", "T10a", "T10b"]
      
      phase_4_component_design:
        expected_files: 2
        files:
          - "doc15_to_doc10.csv"
          - "doc16_to_doc15.csv"
        traceability_rules: ["T6", "T11"]
      
      phase_5_implementation_testing:
        expected_files: 3
        files:
          - "doc18_to_doc15.csv"
          - "doc20_to_doc16.csv"
          - "doc20_to_doc18.csv"
        traceability_rules: ["T7", "T12"]
      
      phase_6_integration:
        expected_files: 4
        files:
          - "doc21_to_doc12.csv"
          - "doc21_to_doc18.csv"
          - "doc22_to_doc13.csv"
          - "doc22_to_doc18.csv"
        traceability_rules: ["T12"]
      
      phase_7_validation:
        expected_files: 3
        files:
          - "doc24_to_doc7.csv"
          - "doc25_to_doc24.csv"
          - "doc25_to_doc6.csv"
        traceability_rules: ["T12", "T13"]
    
    mandatory_tools:
      - tool: "trace validate"
        purpose: "Validate CSV completeness and SIL thresholds"
        required_for: "SIL 3-4 compliance"
      - tool: "trace gate-check"
        purpose: "Per-phase gate validation with rule checking (T1-T15)"
        required_for: "All phases"
    
    optional_tools:
      - tool: "trace extract"
        purpose: "Auto-extraction using proximity heuristics"
        status: "OPTIONAL/EXPERIMENTAL"
        warning: "May produce incorrect semantic mappings"
      - tool: "trace sync"
        purpose: "Synchronize CSV ↔ JSON ↔ Markdown formats"
        status: "OPTIONAL"
    
    references:
      - "TRACEABILITY.md Section 13"
      - ".opencode/skills/en50128-configuration/SKILL.md Section 3.4"
      - "tools/README_TRACEABILITY.md"
```

**Impact**: LOW — Adds ~120 lines at end of file; no changes to existing sections; provides machine-consumable workflow for agents

---

### 6. `tools/README_TRACEABILITY.md`

**Location**: Lines 1-552

**Current State**: 
- Line 64: lists `extract` as "✅ Complete"
- Section 9 (lines 211-220): documents extract command usage

**Required Changes**:

**1. Add warning box at top** (after line 9, before "**Key Features**"):

```markdown
> ⚠ **IMPORTANT — Official Workflow**: The official EN 50128 traceability workflow for this platform uses **manual CSV creation** by the Configuration Manager (CM). The `trace extract` command is **OPTIONAL/EXPERIMENTAL** and may produce incorrect semantic mappings due to proximity-based heuristics. For compliance, use manual CSV creation as documented in `TRACEABILITY.md` Section 13 and `.opencode/skills/en50128-configuration/SKILL.md`.
```

**2. Update Table** (line 64):

```markdown
| `extract` | Auto-extract traceability from documents | ⚠ OPTIONAL/EXPERIMENTAL |
```

**3. Update Section 9** (lines 211-220):

Add note before the command example:

```markdown
> ⚠ **Note**: This command is OPTIONAL/EXPERIMENTAL. It uses proximity-based heuristics to extract traceability links from documents. For EN 50128 compliance, use manual CSV creation as documented in `TRACEABILITY.md` Section 13.
```

**4. Update Section 2 "Quick Start"** (add new step 1a):

```markdown
### 1a. Manual CSV Creation (Official Workflow)

**For EN 50128 compliance, use manual CSV creation**:

1. Read deliverables produced by document authors
2. Extract trace relationships (e.g., COMP-001 → REQ-SAFE-007)
3. Create CSV file with canonical naming: `doc{source}_to_doc{target}.csv`
4. Use standard CSV format (see Section 4 "Data Models")
5. Validate: `python3 tools/workspace.py trace validate --phase design --sil 3`

**Example** (Phase 3 — Architecture to Requirements):
```csv
source_id,source_type,target_id,target_type,link_type,rationale,verified,verified_by,verified_date,source_document,target_document
COMP-001-SKN,component,REQ-SAFE-007,requirement,implements,SKN implements safety interlock,true,VER,2026-03-28,doc9,doc6
COMP-001-SKN,component,REQ-SAFE-002,requirement,implements,SKN monitors door sensor,true,VER,2026-03-28,doc9,doc6
```

**See**: `TRACEABILITY.md` Section 13 and `.opencode/skills/en50128-configuration/SKILL.md` for detailed per-phase workflows.
```

**Impact**: MEDIUM — Adds ~50 lines; updates existing sections with warnings; no breaking changes

---

### 7. `.opencode/skills/en50128-lifecycle-tool-integration/SKILL.md`

**Location**: Line 107 (example using `trace extract`)

**Required Changes**:

**Replace line 107 example** with manual workflow example:

```markdown
# Manual CSV creation (official workflow)
# CM reads SAS and creates doc9_to_doc6.csv manually
# See .opencode/skills/en50128-configuration/SKILL.md Section 3.4

# Validate traceability (mandatory for SIL 3-4)
python3 tools/workspace.py trace validate \
  --phase design \
  --sil 3

# Gate check before COD gate (mandatory for all phases)
python3 tools/workspace.py trace gate-check \
  --phase design \
  --sil 3

# Optional: Extract traceability from documents (experimental)
# ⚠ WARNING: Uses proximity heuristics; may produce incorrect mappings
# python3 tools/workspace.py trace extract \
#   --document docs/phase-3-architecture-design/Software-Architecture-Specification.md \
#   --type component_to_requirement \
#   --merge
```

**Impact**: LOW — Single line update; comments out experimental example

---

## Summary of Changes by Priority

### HIGH PRIORITY (Must Complete)

| File | Section | Lines to Add/Modify | Effort |
|------|---------|---------------------|--------|
| `.opencode/skills/en50128-configuration/SKILL.md` | Section 3.4 (rewrite) | ~400 lines (replace 104) | 2-3 hours |

### MEDIUM PRIORITY (Should Complete)

| File | Section | Lines to Add/Modify | Effort |
|------|---------|---------------------|--------|
| `TRACEABILITY.md` | Add Section 13 | ~150 lines | 1-1.5 hours |
| `TRACEABILITY_TOOL_GAP_ANALYSIS.md` | Add Section 11 | ~40 lines | 15 minutes |
| `tools/README_TRACEABILITY.md` | Add warning box, update sections | ~50 lines | 30 minutes |

### LOW PRIORITY (Nice to Have)

| File | Section | Lines to Add/Modify | Effort |
|------|---------|---------------------|--------|
| `TOOLS.md` | Add warning box, update descriptions | ~20 lines | 15 minutes |
| `activities/traceability.yaml` | Add workflow_guidance section | ~120 lines | 30 minutes |
| `.opencode/skills/en50128-lifecycle-tool-integration/SKILL.md` | Update example | 1 line | 5 minutes |

---

## Total Effort Estimate

| Priority | Hours | Files |
|----------|-------|-------|
| HIGH | 2-3 | 1 |
| MEDIUM | 2-2.5 | 3 |
| LOW | 1 | 3 |
| **TOTAL** | **5-6.5** | **7** |

---

## Risk Assessment

| Risk | Likelihood | Impact | Mitigation |
|------|-----------|--------|------------|
| Breaking changes to existing workflows | LOW | HIGH | No code changes; documentation only |
| Agent confusion from mixed messages | LOW | MEDIUM | Consistent warnings across all docs |
| Users still try to use `trace extract` | MEDIUM | LOW | Clear warnings + document official workflow |
| TDC Phase 3 evidence invalidated | NONE | N/A | No changes to existing CSV files |

**Overall Risk**: **LOW**

---

## Validation Plan

After implementing all changes:

1. ✅ **Grep validation**: Search for `trace extract` in all platform files → should return only:
   - Documented warnings ("OPTIONAL/EXPERIMENTAL")
   - Historical references (deprecated/, examples/TDC/analysis docs)
   - Tool source code (tools/traceability_manager.py)

2. ✅ **TDC Phase 3 re-validation**:
   ```bash
   cd examples/TDC
   python3 ../../tools/workspace.py trace validate --sil 3
   python3 ../../tools/workspace.py trace gate-check --phase design --sil 3
   ```
   Expected: ✓ PASS (no changes to CSV files)

3. ✅ **Skill loading test**: Load CM skill in agent context → verify Section 3.4 reflects manual workflow

4. ✅ **Documentation consistency**: Verify TRACEABILITY.md Section 13 ↔ CM skill Section 3.4 ↔ README_TRACEABILITY.md alignment

---

## Next Steps

See companion document: `examples/TDC/OPTION_B_IMPLEMENTATION_PLAN.md` for step-by-step implementation instructions.

---

## References

- **Option B Decision**: `examples/TDC/TRACEABILITY_TOOL_EXTRACTION_STATUS.md` Section "Path Forward"
- **Tool Analysis**: `TRACEABILITY_TOOL_GAP_ANALYSIS.md` Sections 1-10
- **EN 50128 Standards**: §5.3.2.7 (traceability), §6.5.4.14-17 (traceability QA), Annex D.59 (traceability process)
- **TDC Phase 3 Evidence**: `examples/TDC/evidence/traceability/` (19 CSV files, all validated)
