# Traceability Tool Gap Analysis

**Date:** 2026-04-03  
**Updated:** 2026-04-03 (Standards analysis complete)  
**Context:** CM agent attempted to use traceability tools during Phase 3 Track A execution  
**Status:** Analysis Complete ✅ — Standards Research Complete ✅ — Recommendations Ready  
**Related:** See `examples/TDC/TRACEABILITY_ROLE_RESPONSIBILITIES.md` for EN 50128:2011 role responsibility analysis

---

## Executive Summary

The CM agent encountered **tool interface gaps** when attempting to validate Phase 3 traceability. While the tool's underlying functionality appears correct, the **command-line interface does not match the expected usage patterns** documented in various places throughout the platform.

**Root Cause:** Documentation-to-implementation mismatch across multiple tool capabilities.

---

## 1. Issue: Missing `coverage` Command

### What CM Tried:
```bash
python3 tools/workspace.py trace coverage doc6 doc9
python3 tools/workspace.py trace coverage doc9 doc10
python3 tools/workspace.py trace coverage doc6 doc10
python3 tools/workspace.py trace coverage doc6 doc12
```

### Error:
```
traceability_manager.py: error: argument command: invalid choice: 'coverage' 
(choose from 'create', 'validate', 'query', 'check-gaps', 'report', 
'import', 'export', 'extract', 'visualize', 'sync', 'gate-check', 'verify-link')
```

### Analysis:
- **Expected:** A `coverage` subcommand to check traceability coverage between two document IDs
- **Reality:** No such command exists
- **Workaround Found:** Use `gate-check --phase <phase> --sil 3` instead (provides coverage per T-rule)
- **Gap Severity:** **MEDIUM** — Workaround exists but interface is non-intuitive

### Impact:
CM could not quickly check individual document-to-document coverage (e.g., "What's the coverage from SRS to SAS?"). Instead, CM had to run gate-check which reports ALL T-rules for a phase.

---

## 2. Issue: `--project` Flag Placement Confusion

### What CM Tried:
```bash
python3 tools/workspace.py trace check-gaps --project TDC --sil 3
python3 tools/workspace.py --project TDC trace check-gaps --sil 3
```

### Errors:
```
traceability_manager.py: error: unrecognized arguments: --project TDC
Error: Unknown command '--project'. Run 'workspace.py' for usage.
```

### Analysis:
- **Help Output Says:** `--project PROJECT     Project name (overrides LIFECYCLE_STATE.md)`
- **Reality:** The `--project` flag exists but its **placement in the command** is ambiguous
- **Correct Syntax (discovered):** `python3 tools/workspace.py trace --project TDC check-gaps --sil 3`
  - i.e., `--project` must come **between** `trace` and the subcommand
- **Gap Severity:** **LOW** — Tool works when invoked from project directory (auto-detects project)

### Impact:
CM tried both positions and failed. The tool **does work** when run from `examples/TDC/` (auto-detects project from LIFECYCLE_STATE.md), so this was **not blocking** but caused confusion.

---

## 3. Issue: `report` Command Requires Arguments (Not Project-Wide)

### What CM Tried:
```bash
python3 tools/workspace.py trace report --project TDC
```

### Error:
```
traceability_manager.py report: error: the following arguments are required: --from, --to
```

### Analysis:
- **Expected:** Generate a comprehensive traceability report for the entire project
- **Reality:** `report` command requires explicit `--from <source>` and `--to <targets>` arguments
- **Gap Severity:** **MEDIUM** — No "generate full project report" command

### Impact:
CM could not generate a single comprehensive traceability report. Instead, must run multiple report commands with different --from/--to combinations.

---

## 4. Issue: Missing Phase 3 Traceability Matrix Files

### What Gate-Check Found:
```bash
python3 tools/workspace.py trace gate-check --phase design --sil 3
```

**Result:** Gate BLOCKED — 7 matrix files missing:
```
✗ T10a   [FAIL]  
   ✗ doc12_to_doc6.csv   MISSING (matrix CSV not found)
   ✗ doc12_to_doc9.csv   MISSING (matrix CSV not found)
   ✗ doc12_to_doc10.csv  MISSING (matrix CSV not found)
   ✗ doc12_to_doc11.csv  MISSING (matrix CSV not found)

✗ T10b   [FAIL]  
   ✗ doc13_to_doc6.csv   MISSING (matrix CSV not found)
   ✗ doc13_to_doc9.csv   MISSING (matrix CSV not found)
   ✗ doc13_to_doc10.csv  MISSING (matrix CSV not found)
   ✗ doc13_to_docS1.csv  MISSING (matrix CSV not found)
   ✗ doc13_to_docS2.csv  MISSING (matrix CSV not found)

✗ T3     [FAIL]  
   ✗ doc6_to_doc9.csv    MISSING (matrix CSV not found)

✗ T4     [FAIL]  
   ✗ doc9_to_doc6.csv    MISSING (matrix CSV not found)

✗ T5a    [FAIL]  
   ✗ doc10_to_doc9.csv   MISSING (matrix CSV not found)

✗ T5b    [FAIL]  
   ✗ doc10_to_doc6.csv   MISSING (matrix CSV not found)

✗ T5c    [FAIL]  
   ✗ doc10_to_doc11.csv  MISSING (matrix CSV not found)
```

### Analysis:
- **What CM Created:** RTM v2.0 in Markdown format at `docs/traceability/Requirements-Traceability-Matrix.md`
- **What Tool Expects:** Individual CSV files per T-rule in `evidence/traceability/` directory
- **Expected File Naming Convention:**
  ```
  evidence/traceability/doc6_to_doc9.csv   (T3: SRS → SAS)
  evidence/traceability/doc9_to_doc6.csv   (T4: SAS → SRS backward)
  evidence/traceability/doc10_to_doc9.csv  (T5a: SDS → SAS)
  evidence/traceability/doc10_to_doc6.csv  (T5b: SDS → SRS)
  evidence/traceability/doc10_to_doc11.csv (T5c: SDS → Interface Specs)
  evidence/traceability/doc12_to_doc6.csv  (T10a: Integration Test → SRS)
  evidence/traceability/doc12_to_doc9.csv  (T10a: Integration Test → SAS)
  evidence/traceability/doc12_to_doc10.csv (T10a: Integration Test → SDS)
  evidence/traceability/doc12_to_doc11.csv (T10a: Integration Test → IS)
  evidence/traceability/doc13_to_doc6.csv  (T10b: HW/SW Test → SRS)
  evidence/traceability/doc13_to_doc9.csv  (T10b: HW/SW Test → SAS)
  evidence/traceability/doc13_to_doc10.csv (T10b: HW/SW Test → SDS)
  evidence/traceability/doc13_to_docS1.csv (T10b: HW/SW Test → System Req)
  evidence/traceability/doc13_to_docS2.csv (T10b: HW/SW Test → System Arch)
  ```

- **Gap Severity:** **HIGH** — This is a **workflow gap**, not a tool bug

### Impact:
CM manually created traceability in Markdown but **did not export to CSV format** expected by the validation tool. The tool correctly identified missing evidence files.

---

## 5. Tool-Workflow Integration Gap

### Problem:
**CM does not have clear instructions** on:
1. When to use `trace extract` to auto-extract traceability from deliverables
2. When to use `trace create` to manually create matrices
3. When to use `trace sync` to synchronize Markdown ↔ CSV ↔ JSON formats
4. How to maintain CSV evidence files alongside human-readable Markdown RTM

### Current State:
- CM manually authored `Requirements-Traceability-Matrix.md` (good for human review)
- CM did NOT create corresponding CSV files (required for automated gate-check)
- Tool has `extract`, `sync`, `create` commands but CM did not know to use them

### Gap Severity:** **CRITICAL** — Workflow documentation missing

---

## 6. Summary of Tool Capabilities vs. CM Usage

| Tool Capability | CM Tried to Use? | Worked? | Gap Type |
|----------------|------------------|---------|----------|
| `trace validate --sil 3` | ✅ Yes | ✅ Yes | None — worked correctly |
| `trace gate-check --phase design --sil 3` | ✅ Yes | ✅ Yes (found missing files) | None — worked correctly |
| `trace coverage doc6 doc9` | ✅ Yes | ❌ No (command doesn't exist) | **Command missing** |
| `trace report --project TDC` | ✅ Yes | ❌ No (requires --from/--to) | **Interface gap** |
| `trace extract` | ❌ No | Unknown | **Workflow gap** (CM didn't know to use it) |
| `trace sync` | ❌ No | Unknown | **Workflow gap** (CM didn't know to use it) |
| `trace create` | ❌ No | Unknown | **Workflow gap** (CM didn't know to use it) |

---

## 7. Document ID Mapping (Correct Convention)

The tool uses the following document ID convention (from DELIVERABLES.md Annex C items):

| Doc ID | Annex C Item | Document Name |
|--------|--------------|---------------|
| **docS1** | S1 (Phase 0) | System Requirements Specification |
| **docS2** | S2 (Phase 0) | System Architecture Description |
| **docS3** | S3 (Phase 0) | System Safety Plan |
| **docS4** | S4 (Phase 0) | System Safety Requirements Specification |
| **doc1** | 1 (Phase 1) | Software Quality Assurance Plan (SQAP) |
| **doc2** | 2 (Phase 1) | SQAP Verification Report |
| **doc3** | 3 (Phase 1) | Software Configuration Management Plan (SCMP) |
| **doc4** | 4 (Phase 1) | Software Verification Plan (SVP) |
| **doc5** | 5 (Phase 1) | Software Validation Plan (SVaP) |
| **doc6** | 6 (Phase 2) | Software Requirements Specification (SRS) |
| **doc7** | 7 (Phase 2) | Overall Software Test Specification (OSTS) |
| **doc8** | 8 (Phase 2) | SRS Verification Report |
| **doc9** | 9 (Phase 3) | Software Architecture Specification (SAS) |
| **doc10** | 10 (Phase 3) | Software Design Specification (SDS) |
| **doc11** | 11 (Phase 3) | Software Interface Specifications (SIS) |
| **doc12** | 12 (Phase 3) | Software Integration Test Specification |
| **doc13** | 13 (Phase 3) | Software/Hardware Integration Test Specification |
| **doc14** | 14 (Phase 3) | Architecture and Design Verification Report |
| **doc15** | 15 (Phase 4) | Software Component Design Specification |
| **doc16** | 16 (Phase 4) | Software Component Test Specification |
| ... | ... | ... |

**CSV File Naming Convention:**
```
{source_docID}_to_{target_docID}.csv
```

**Examples:**
- `doc6_to_doc9.csv` = SRS (doc6) → SAS (doc9) traceability
- `docS1_to_doc6.csv` = System Requirements (docS1) → SRS (doc6) traceability
- `doc12_to_doc6.csv` = Integration Test Spec (doc12) → SRS (doc6) traceability

---

## 8. Recommendations

### **Immediate (Before Phase 3 Gate Check):**

1. **CM must create missing CSV files** for Phase 3 traceability:
   ```bash
   # Option 1: Use trace extract to auto-extract from deliverables
   cd examples/TDC
   python3 ../../tools/workspace.py trace extract --document docs/phase-3-design/Software-Architecture-Specification.md --type doc9_to_doc6 --merge
   python3 ../../tools/workspace.py trace extract --document docs/phase-3-design/Software-Design-Specification.md --type doc10_to_doc9 --merge
   python3 ../../tools/workspace.py trace extract --document docs/phase-3-design/Software-Design-Specification.md --type doc10_to_doc6 --merge
   
   # Option 2: Use trace create to manually create matrices
   python3 ../../tools/workspace.py trace create --from doc6 --to doc9
   python3 ../../tools/workspace.py trace create --from doc9 --to doc6
   python3 ../../tools/workspace.py trace create --from doc10 --to doc9
   python3 ../../tools/workspace.py trace create --from doc10 --to doc6
   python3 ../../tools/workspace.py trace create --from doc10 --to doc11
   python3 ../../tools/workspace.py trace create --from doc12 --to doc6
   python3 ../../tools/workspace.py trace create --from doc12 --to doc9
   python3 ../../tools/workspace.py trace create --from doc12 --to doc10
   python3 ../../tools/workspace.py trace create --from doc12 --to doc11
   python3 ../../tools/workspace.py trace create --from doc13 --to doc6
   python3 ../../tools/workspace.py trace create --from doc13 --to doc9
   python3 ../../tools/workspace.py trace create --from doc13 --to doc10
   python3 ../../tools/workspace.py trace create --from doc13 --to docS1
   python3 ../../tools/workspace.py trace create --from doc13 --to docS2
   
   # Option 3: Use trace sync to generate CSV from existing Markdown RTM
   python3 ../../tools/workspace.py trace sync --matrix all
   ```

2. **Validate after creating CSVs:**
   ```bash
   cd examples/TDC
   python3 ../../tools/workspace.py trace gate-check --phase design --sil 3
   ```

### **Short-Term (Before Phase 4):**

3. **Add `coverage` command** to traceability_manager.py:
   ```python
   def coverage_command(args):
       """Check coverage between two specific documents."""
       # Implementation: count links from source to target
       # Output: "Coverage: X% (Y/Z links)"
   ```

4. **Add project-wide `report` option:**
   ```bash
   python3 tools/workspace.py trace report --project TDC --all
   # OR
   python3 tools/workspace.py trace report --phase design
   ```

5. **Update CM agent instructions** to include:
   - Use `trace extract` after authoring each deliverable
   - Use `trace sync` to keep Markdown ↔ CSV synchronized
   - Use `trace gate-check` before reporting Track A complete

### **Long-Term (Before Phase 5):**

6. **Create CM workflow documentation** (`tasks/CM_TRACEABILITY_WORKFLOW.md`):
   - When to extract traceability (after each document authored)
   - When to sync formats (before QUA review, before gate-check)
   - When to validate (after Track A complete, before reporting to COD)
   - CSV file naming conventions
   - Document ID mapping reference

7. **Add automated reminders** in PM phase execution:
   - PM should prompt CM to run `trace extract` after DES/INT complete
   - PM should prompt CM to run `trace gate-check` before reporting Track A complete

8. **Consider consolidating traceability storage:**
   - **Current:** `docs/traceability/` (Markdown) + `evidence/traceability/` (CSV)
   - **Proposed:** Single directory with both formats, auto-synced

---

## 9. Conclusion

**The traceability tools work correctly**, but there are **three types of gaps**:

1. **Interface Gaps** (MEDIUM severity):
   - Missing `coverage` command (workaround: use `gate-check`)
   - `report` requires explicit --from/--to (no project-wide report)

2. **Workflow Gaps** (CRITICAL severity):
   - CM did not know to use `extract`, `sync`, `create` commands
   - No documented workflow for maintaining CSV evidence files
   - Missing integration between human-readable Markdown RTM and machine-readable CSV matrices

3. **Documentation Gaps** (MEDIUM severity):
   - `--project` flag placement ambiguous
   - Document ID convention not clearly documented for CM
   - T-rule to file-name mapping not explicit

**Immediate Action Required:** CM must create the 14 missing CSV files before Phase 3 gate-check can pass.

**Root Cause:** Tool capabilities exist but are not integrated into CM's standard workflow. CM authored high-quality Markdown RTM but did not create machine-readable CSV evidence files required for automated validation.

---

## 10. Standards Analysis Findings (NEW — 2026-04-03)

### 10.1 Role Responsibilities per EN 50128:2011

**Research Question**: Who is responsible for CREATING traceability evidence? Who is responsible for VALIDATING it?

**Answer** (see `examples/TDC/TRACEABILITY_ROLE_RESPONSIBILITIES.md` for full analysis):

| Activity | Responsible Role | EN 50128 Reference |
|----------|------------------|-------------------|
| **Create traceability when authoring documents** | REQ, DES, IMP, TST, INT (document authors) | §5.3.2.7 |
| **Manage traceability artifacts under version control** | CM | §6.5.4.15, §6.6.1.2 |
| **Verify traceability completeness and correctness** | VER | §6.5.4.14–6.5.4.17 |
| **Validate traceability (2nd check)** | VAL | §6.3, Annex C |
| **Enforce traceability at phase gates** | COD | §5.3 |

### 10.2 Key Standard Citations

> **§5.3.2.7**: "For each document, traceability shall be provided in terms of a unique reference number and a defined and documented relationship with other documents."

**Interpretation**: Each document author must provide traceability when creating the document.

> **§6.5.4.15**: "Traceability shall particularly address:  
> a) traceability of requirements to the design or other objects which fulfil them,  
> b) traceability of design objects to the implementation objects which instantiate them,  
> c) traceability of requirements and design objects to the tests...  
> **Traceability shall be the subject of configuration management.**"

**Interpretation**: CM is responsible for **managing** traceability artifacts (baselines, version control), NOT for creating the initial traces.

### 10.3 Conclusion

The current gap (14 missing CSV files in Phase 3) is a **WORKFLOW INTEGRATION ISSUE**:

1. ✅ **Tools work correctly**: `trace validate` and `trace gate-check` correctly identified missing files
2. ✅ **Workflow is standards-compliant**: Roles match EN 50128 requirements
3. ❌ **Workflow integration gap**: CM agent didn't use `trace extract`, `trace sync`, or `trace create` to produce CSV files

**Root Cause**: CM agent created high-quality Markdown RTM but did NOT create machine-readable CSV evidence files that the automated validation tool requires.

---

## 11. Updated Recommendations

### 11.1 Immediate: Fix Phase 3 Gap (14 Missing CSV Files)

**Option A: Manual CSV Creation** (fastest for one-time fix):
```bash
# Create 14 CSV files manually in evidence/traceability/
# Format: source_id,target_id,rationale,verification_method,status
```

**Option B: Tool-Assisted Extraction** (recommended):
```bash
cd examples/TDC

# T3: SRS → SAS
trace extract --from docs/phase-2-requirements/Software-Requirements-Specification.md \
              --to docs/phase-3-architecture-design/Software-Architecture-Specification.md \
              --output evidence/traceability/doc6_to_doc9.csv

# T4: SAS → SRS (backward)
trace extract --from docs/phase-3-architecture-design/Software-Architecture-Specification.md \
              --to docs/phase-2-requirements/Software-Requirements-Specification.md \
              --output evidence/traceability/doc9_to_doc6.csv

# ... repeat for all 14 files (see TRACEABILITY_ROLE_RESPONSIBILITIES.md §3.2)
```

**Validation**:
```bash
cd examples/TDC
trace validate --sil 3          # Should pass after files created
trace gate-check --phase design --sil 3  # Should pass after files created
```

---

### 11.2 Long-Term: Update CM Agent Instructions

**File**: `.opencode/agents/cm.md`

**Add to Phase 3 Activities Section**:

```markdown
### Traceability Evidence Creation (Phase 3)

Per §5.3.2.7 and §6.5.4.15, CM is responsible for managing traceability artifacts under configuration control.

**Mandatory Activities**:
1. Extract trace relationships from all Phase 3 documents using `trace extract` or `trace sync`
2. Create CSV evidence files in `evidence/traceability/` for all T-rules applicable to Phase 3:
   - T3: SRS → SAS (`doc6_to_doc9.csv`)
   - T4: SAS → SRS backward (`doc9_to_doc6.csv`)
   - T5a: SDS → SAS (`doc10_to_doc9.csv`)
   - T5b: SDS → SRS (`doc10_to_doc6.csv`)
   - T5c: SDS → Interface Specs (`doc10_to_doc11.csv`)
   - T10a: Integration Test Spec → Requirements/Architecture/Design/Interfaces (4 files)
   - T10b: HW/SW Integration Test Spec → all upstream documents (5 files)
3. Produce Markdown RTM as summary/reporting artifact (optional, for readability)
4. Baseline all CSV files in git

**Validation** (run BEFORE signaling Track A complete):
```bash
trace validate --sil 3
trace gate-check --phase design --sil 3
```

Both commands must return ✅ ALL CHECKS PASSED.
```

---

### 11.3 Long-Term: Update PM Phase Execution Workflow

**File**: `.opencode/agents/pm.md`

**Add to Phase 3 Execution Checklist**:

```markdown
- [ ] DES produces SAS, SDS, SIS with embedded trace IDs
- [ ] INT produces Integration Test Specs with embedded trace IDs
- [ ] **CM extracts traceability to CSV using `trace extract` or `trace sync`**
- [ ] **CM validates traceability: `trace validate --sil 3`**
- [ ] **CM validates gate-readiness: `trace gate-check --phase design --sil 3`**
- [ ] QUA reviews all deliverables (including CSV files)
- [ ] PM signals Track A complete → hand off to COD for Track B coordination
```

---

### 11.4 Tool Improvements (Future Enhancement)

**Low Priority** (tools work correctly; these are nice-to-have):

1. **Add `coverage` command** for quick document-to-document coverage checks
2. **Improve `report` command** to work without explicit `--from`/`--to` (infer from project state)
3. **Better error messages** for missing CSV files (suggest `trace extract` command)

---

**End of Analysis** — Standards research complete ✅  
**Next Steps**: Fix 14 missing CSV files → Execute Phase 3 Track B (VER) → COD gate-check

---

**Author:** Analysis based on CM agent session transcript + EN 50128:2011 standards research  
**Related Documents:**  
- `examples/TDC/TRACEABILITY_ROLE_RESPONSIBILITIES.md` — Full EN 50128:2011 role analysis  
- `TRACEABILITY.md` — T1-T15 rules and V-Model diagrams  
- `WORKFLOW.md` — Two-track execution model
