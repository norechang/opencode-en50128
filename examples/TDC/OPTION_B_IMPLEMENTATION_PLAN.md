# Option B Implementation Plan

**Date**: 2026-04-03  
**Project**: TDC (Train Door Control System)  
**Decision**: Option B — Manual CSV Creation as Official Workflow  
**Companion Document**: `OPTION_B_SCOPE_ANALYSIS_REPORT.md`

---

## Executive Summary

This document provides a **step-by-step implementation plan** for updating the EN 50128 platform to formalize **manual CSV creation** as the official traceability workflow, with `trace extract` marked as optional/experimental.

**Total Effort**: 5-6.5 hours  
**Files to Update**: 7 files  
**Risk Level**: LOW (documentation updates only; no breaking changes)

---

## Implementation Sequence

Updates are sequenced to maintain consistency across the platform. Updates are grouped into **3 phases**:

1. **Phase 1: Core Documentation** (TRACEABILITY.md, TRACEABILITY_TOOL_GAP_ANALYSIS.md)
2. **Phase 2: Skills & Activities** (CM skill, traceability.yaml)
3. **Phase 3: Tool Documentation** (README_TRACEABILITY.md, TOOLS.md, lifecycle-tool-integration skill)

---

## Phase 1: Core Documentation (2-2.5 hours)

### Step 1.1: Update TRACEABILITY.md

**File**: `TRACEABILITY.md`  
**Location**: After Section 12 (line 542)  
**Effort**: 1-1.5 hours

**Action**: Add new Section 13 — "Traceability Evidence Management Workflow"

**Content to Add**:

<details>
<summary>Click to expand Section 13 content (150 lines)</summary>

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
| 3: Architecture & Design | DES + SAF | Components/modules with trace sections | Create `doc9_to_doc6.csv`, `doc10_to_doc9.csv`, `doc10_to_doc6.csv`, `doc10_to_doc11.csv` + test specs (9 more files) | Verify T3, T4, T5a-c, T8, T9, T10a-b |
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

**See**: `.opencode/skills/en50128-configuration/SKILL.md` Section 3.4 "Traceability Evidence Management" for detailed CM workflow instructions.
```

</details>

**Validation**:
```bash
# Check line count
wc -l TRACEABILITY.md
# Expected: ~692 lines (542 + 150)

# Verify Section 13 is present
grep -n "## 13. Traceability Evidence Management Workflow" TRACEABILITY.md
# Expected: line 543
```

---

### Step 1.2: Update TRACEABILITY_TOOL_GAP_ANALYSIS.md

**File**: `TRACEABILITY_TOOL_GAP_ANALYSIS.md`  
**Location**: End of file (after last section)  
**Effort**: 15 minutes

**Action**: Add new Section 11 — "Resolution: Option B Adopted"

**Content to Add**:

<details>
<summary>Click to expand Section 11 content (40 lines)</summary>

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
- `examples/TDC/OPTION_B_IMPLEMENTATION_PLAN.md` — Step-by-step implementation plan (this document)

**EN 50128 Compliance**: This decision is fully compliant with EN 50128:2011. §5.3.2.7 and §6.5.4.14-17 require traceability evidence but do not mandate a specific tool. Manual CSV creation satisfies all normative traceability requirements (T1-T15).
```

</details>

**Validation**:
```bash
# Verify Section 11 is present
grep -n "## 11. Resolution: Option B Adopted" TRACEABILITY_TOOL_GAP_ANALYSIS.md
# Expected: section header found
```

---

## Phase 2: Skills & Activities (2.5-3 hours)

### Step 2.1: Update Configuration Manager Skill

**File**: `.opencode/skills/en50128-configuration/SKILL.md`  
**Location**: Lines 276-379 (replace current Section 3.4)  
**Effort**: 2-3 hours (MAJOR rewrite)

**Action**: **COMPLETELY REWRITE** Section 3.4 "Traceability Evidence Management"

**Current State**: 104 lines (lines 276-379)  
**New State**: ~400 lines (detailed per-phase workflows, CSV format specs, examples)

**Content Overview**:

1. **3.4.1 CM Responsibilities** — Table of responsibilities
2. **3.4.2 Per-Phase Workflow** — Detailed workflows for Phases 2-7 (6 sections)
3. **3.4.3 CSV File Naming Convention** — Document ID mapping table
4. **3.4.4 CSV File Format** — Column definitions, examples
5. **3.4.5 Validation Commands** — `trace validate` and `trace gate-check` examples
6. **3.4.6 Tool Support** — Mandatory vs. optional tools
7. **3.4.7 CCB Change Request Impact** — Re-tracing workflow
8. **3.4.8 Example: TDC Phase 3 Traceability** — Real-world example with validation results
9. **3.4.9 References** — Cross-references to other documents

**Content Source**: See `OPTION_B_SCOPE_ANALYSIS_REPORT.md` Section "Detailed Change Specifications" → Item 4 for full content

**Implementation Steps**:

1. **Read** current Section 3.4 (lines 276-379)
2. **Delete** lines 276-379
3. **Write** new Section 3.4 (~400 lines) using content from scope analysis report
4. **Verify** line numbers for cross-references in other sections

**Validation**:
```bash
# Check line count
wc -l .opencode/skills/en50128-configuration/SKILL.md
# Expected: ~600 lines (current 300 - 104 + 400)

# Verify section structure
grep -n "^### 3.4" .opencode/skills/en50128-configuration/SKILL.md
# Expected: 9 subsections (3.4.1 through 3.4.9)

# Verify TDC example is present
grep -n "TDC Phase 3 Traceability" .opencode/skills/en50128-configuration/SKILL.md
# Expected: Section 3.4.8 header found
```

---

### Step 2.2: Update Traceability Activity YAML

**File**: `activities/traceability.yaml`  
**Location**: After line 980 (before end of file)  
**Effort**: 30 minutes

**Action**: Add new section "workflow_guidance"

**Content Source**: See `OPTION_B_SCOPE_ANALYSIS_REPORT.md` Section "Detailed Change Specifications" → Item 5 for full YAML content (~120 lines)

**Key Subsections**:
- `official_method: "manual_csv_creation"`
- `cm_responsibilities` (5 items)
- `per_phase_csv_files` (6 phases with expected file lists)
- `mandatory_tools` (trace validate, trace gate-check)
- `optional_tools` (trace extract with warning, trace sync)
- `references`

**Validation**:
```bash
# Verify YAML is valid
python3 -c "import yaml; yaml.safe_load(open('activities/traceability.yaml'))"
# Expected: no errors

# Check for new section
grep -n "workflow_guidance:" activities/traceability.yaml
# Expected: section header found after line 980
```

---

## Phase 3: Tool Documentation (1-1.5 hours)

### Step 3.1: Update Traceability Tool README

**File**: `tools/README_TRACEABILITY.md`  
**Location**: Multiple locations  
**Effort**: 30 minutes

**Actions**:

1. **Add warning box** (after line 9, before "**Key Features**"):
   ```markdown
   > ⚠ **IMPORTANT — Official Workflow**: The official EN 50128 traceability workflow for this platform uses **manual CSV creation** by the Configuration Manager (CM). The `trace extract` command is **OPTIONAL/EXPERIMENTAL** and may produce incorrect semantic mappings due to proximity-based heuristics. For compliance, use manual CSV creation as documented in `TRACEABILITY.md` Section 13 and `.opencode/skills/en50128-configuration/SKILL.md`.
   ```

2. **Update commands table** (line 64):
   ```markdown
   | `extract` | Auto-extract traceability from documents | ⚠ OPTIONAL/EXPERIMENTAL |
   ```

3. **Update Section 9** (before line 211):
   ```markdown
   > ⚠ **Note**: This command is OPTIONAL/EXPERIMENTAL. It uses proximity-based heuristics to extract traceability links from documents. For EN 50128 compliance, use manual CSV creation as documented in `TRACEABILITY.md` Section 13.
   ```

4. **Add new Section 1a** (after Quick Start Section 1):
   See `OPTION_B_SCOPE_ANALYSIS_REPORT.md` → Item 6 for full content (~30 lines)

**Validation**:
```bash
# Verify warning box is present
grep -n "IMPORTANT — Official Workflow" tools/README_TRACEABILITY.md
# Expected: found near line 10

# Verify extract is marked experimental in table
grep "extract.*OPTIONAL/EXPERIMENTAL" tools/README_TRACEABILITY.md
# Expected: match found
```

---

### Step 3.2: Update TOOLS.md

**File**: `TOOLS.md`  
**Location**: Traceability tools section (need to find first)  
**Effort**: 15 minutes

**Actions**:

1. **Find traceability section**:
   ```bash
   grep -n "trace extract\|traceability.*tool\|Traceability Manager" TOOLS.md
   ```

2. **Add warning box** before `trace extract` description:
   ```markdown
   > ⚠ **IMPORTANT**: The `trace extract` command is **OPTIONAL/EXPERIMENTAL**. It uses proximity-based heuristics that may produce incorrect semantic mappings. The official EN 50128 traceability workflow uses **manual CSV creation** by the Configuration Manager. See `TRACEABILITY.md` Section 13 and `.opencode/skills/en50128-configuration/SKILL.md` for the official workflow.
   ```

3. **Update command status tags**:
   - `trace validate` → **MANDATORY (SIL 3-4)**
   - `trace gate-check` → **MANDATORY (all phases)**
   - `trace extract` → **OPTIONAL/EXPERIMENTAL**

**Validation**:
```bash
# Verify warning is present
grep -n "OPTIONAL/EXPERIMENTAL" TOOLS.md
# Expected: found in traceability section
```

---

### Step 3.3: Update Lifecycle Tool Integration Skill

**File**: `.opencode/skills/en50128-lifecycle-tool-integration/SKILL.md`  
**Location**: Line 107  
**Effort**: 5 minutes

**Action**: Replace `trace extract` example with manual workflow

**Current** (line 107):
```bash
python3 tools/workspace.py trace extract \
```

**Replace with**:
```bash
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

**Validation**:
```bash
# Verify trace extract is commented out
grep -n "# python3.*trace extract" .opencode/skills/en50128-lifecycle-tool-integration/SKILL.md
# Expected: line ~107
```

---

## Validation & Testing

### Post-Implementation Validation

After completing all updates, run the following validation suite:

#### 1. Grep Validation

**Purpose**: Ensure `trace extract` references are only in expected locations

```bash
# Search for trace extract in all platform files (exclude deprecated, examples, git)
grep -r "trace extract" --include="*.md" --include="*.yaml" --exclude-dir=".git" --exclude-dir="deprecated" --exclude-dir="examples" .

# Expected results:
# - TRACEABILITY.md Section 13.3 (marked as optional/experimental)
# - tools/README_TRACEABILITY.md (warning boxes + Section 9 note)
# - TOOLS.md (warning box)
# - .opencode/skills/en50128-lifecycle-tool-integration/SKILL.md (commented out example)
# - activities/traceability.yaml (listed in optional_tools with warning)
```

#### 2. TDC Phase 3 Re-Validation

**Purpose**: Ensure existing evidence is still valid

```bash
cd examples/TDC

# Validate all CSV files
python3 ../../tools/workspace.py trace validate --sil 3
# Expected: ✓ PASS

# Gate check for Phase 3
python3 ../../tools/workspace.py trace gate-check --phase design --sil 3
# Expected: ✓ PASS (all T-rules satisfied)
```

#### 3. Documentation Consistency Check

**Purpose**: Verify cross-references are correct

```bash
# Verify TRACEABILITY.md references CM skill
grep -n "en50128-configuration/SKILL.md" TRACEABILITY.md
# Expected: Section 13.3

# Verify CM skill references TRACEABILITY.md
grep -n "TRACEABILITY.md" .opencode/skills/en50128-configuration/SKILL.md
# Expected: Section 3.4.9

# Verify traceability.yaml references both
grep -n "TRACEABILITY.md\|en50128-configuration" activities/traceability.yaml
# Expected: workflow_guidance.references section
```

#### 4. Skill Loading Test

**Purpose**: Verify CM skill loads correctly in agent context

```bash
# Load CM skill and verify Section 3.4 structure
python3 -c "
import yaml
with open('.opencode/skills/en50128-configuration/SKILL.md') as f:
    content = f.read()
    if '### 3.4.1 CM Responsibilities' in content and \
       '### 3.4.2 Per-Phase Workflow' in content and \
       '### 3.4.8 Example: TDC Phase 3 Traceability' in content:
        print('✓ CM skill Section 3.4 structure valid')
    else:
        print('✗ CM skill Section 3.4 structure incomplete')
"
```

#### 5. YAML Syntax Validation

**Purpose**: Ensure YAML files are syntactically correct

```bash
# Validate traceability.yaml
python3 -c "import yaml; yaml.safe_load(open('activities/traceability.yaml')); print('✓ traceability.yaml valid')"
# Expected: ✓ traceability.yaml valid
```

---

## Rollback Plan

If issues arise during implementation, use the following rollback strategy:

### Git Rollback

**Before starting implementation**, create a checkpoint:

```bash
git checkout -b option-b-implementation
git add .
git commit -m "Checkpoint: Before Option B implementation"
```

**If rollback needed**:

```bash
# Discard all changes
git checkout main
git branch -D option-b-implementation

# Or: Rollback specific file
git checkout main -- <file_path>
```

### File-by-File Rollback

If only specific files need rollback:

```bash
# Restore original TRACEABILITY.md
git restore TRACEABILITY.md

# Restore original CM skill
git restore .opencode/skills/en50128-configuration/SKILL.md
```

---

## Success Criteria

Implementation is complete when:

- ✅ All 7 files updated per specification
- ✅ Grep validation passes (no unexpected `trace extract` references)
- ✅ TDC Phase 3 re-validation passes (`trace validate` + `trace gate-check` both ✓ PASS)
- ✅ Documentation consistency check passes (all cross-references valid)
- ✅ YAML syntax validation passes
- ✅ All warning boxes present where specified
- ✅ Manual workflow documented in Section 13 of TRACEABILITY.md
- ✅ CM skill Section 3.4 contains 9 subsections with per-phase workflows
- ✅ `trace extract` marked as OPTIONAL/EXPERIMENTAL in all user-facing docs

---

## Timeline

| Phase | Duration | Files | Cumulative |
|-------|----------|-------|------------|
| **Phase 1: Core Documentation** | 2-2.5 hours | 2 | 2-2.5 hours |
| **Phase 2: Skills & Activities** | 2.5-3 hours | 2 | 4.5-5.5 hours |
| **Phase 3: Tool Documentation** | 1-1.5 hours | 3 | 5.5-7 hours |
| **Validation & Testing** | 30 minutes | — | **6-7.5 hours** |

**Recommended schedule**: Single focused work session (6-8 hours) OR 2 sessions (Phase 1+2 day 1, Phase 3+validation day 2)

---

## Post-Implementation Actions

After successful implementation:

1. **Commit changes**:
   ```bash
   git add .
   git commit -m "Implement Option B: Manual CSV traceability workflow

   - Add TRACEABILITY.md Section 13 (manual workflow)
   - Rewrite CM skill Section 3.4 (per-phase workflows)
   - Mark trace extract as OPTIONAL/EXPERIMENTAL in all docs
   - Update traceability.yaml with workflow guidance
   - Add warning boxes to README_TRACEABILITY.md and TOOLS.md
   
   Ref: examples/TDC/OPTION_B_SCOPE_ANALYSIS_REPORT.md
   Ref: examples/TDC/OPTION_B_IMPLEMENTATION_PLAN.md"
   ```

2. **Archive analysis documents**:
   - Move `TRACEABILITY_TOOL_EXTRACTION_STATUS.md` to `examples/TDC/archive/`
   - Keep `OPTION_B_SCOPE_ANALYSIS_REPORT.md` and `OPTION_B_IMPLEMENTATION_PLAN.md` as permanent records

3. **Update TDC LIFECYCLE_STATE.md**:
   - Add note: "Traceability workflow: Manual CSV creation (Option B adopted 2026-04-03)"

4. **Communicate to team** (if applicable):
   - Update internal documentation
   - Notify developers of official workflow
   - Update training materials

---

## References

- **Scope Analysis**: `examples/TDC/OPTION_B_SCOPE_ANALYSIS_REPORT.md`
- **Tool Test Results**: `examples/TDC/TRACEABILITY_TOOL_EXTRACTION_STATUS.md`
- **Gap Analysis**: `TRACEABILITY_TOOL_GAP_ANALYSIS.md` Sections 1-10
- **EN 50128 Standard**: §5.3.2.7 (traceability), §6.5.4.14-17 (traceability QA)
- **TDC Evidence**: `examples/TDC/evidence/traceability/` (19 CSV files, all validated)

---

**END OF IMPLEMENTATION PLAN**
