# Tool Reference Migration Guide

## Overview

This document maps old placeholder tool references to the new unified workspace CLI commands for the Traceability Manager and Workflow Manager tools.

---

## Traceability Tool Mappings

### Old Placeholder References → New Workspace Commands

| Old Command (DOES NOT EXIST) | New Command (WORKING) |
|------------------------------|----------------------|
| `python3 tools/traceability/extract_traces.py` | `workspace.py trace extract` |
| `python3 tools/traceability/check_traceability.py` | `workspace.py trace validate` |
| `python3 tools/traceability/generate_matrix.py` | `workspace.py trace create` |
| `python3 tools/traceability/find_gaps.py` | `workspace.py trace check-gaps` |
| `python3 tools/traceability/check_forward_trace.py` | `workspace.py trace query --direction forward` |
| `python3 tools/traceability/check_backward_trace.py` | `workspace.py trace query --direction backward` |
| `python3 tools/traceability/check_all_traces.py` | `workspace.py trace validate --phase <phase>` |
| `python3 tools/traceability/trace_checker.py` | `workspace.py trace validate` |

---

## Detailed Command Migrations

### 1. Extract Traceability Links

**OLD (placeholder)**:
```bash
python3 tools/traceability/extract_traces.py \
  --input src/door_control.c \
  --output traces/code_to_requirements.yaml
```

**NEW (working)**:
```bash
workspace.py trace extract \
  --document src/door_control.c \
  --type code_to_requirements \
  --merge
```

---

### 2. Validate Traceability Completeness

**OLD (placeholder)**:
```bash
python3 tools/traceability/check_traceability.py \
  --source traces/requirements.yaml \
  --target traces/design.yaml \
  --sil 3
```

**NEW (working)**:
```bash
workspace.py trace validate \
  --phase design \
  --sil 3
```

---

### 3. Generate Traceability Matrix

**OLD (placeholder)**:
```bash
python3 tools/traceability/generate_matrix.py \
  --from requirements \
  --to design
```

**NEW (working)**:
```bash
workspace.py trace create \
  --from requirements \
  --to design
```

---

### 4. Find Traceability Gaps

**OLD (placeholder)**:
```bash
python3 tools/traceability/find_gaps.py \
  --phase design \
  --sil 3
```

**NEW (working)**:
```bash
workspace.py trace check-gaps \
  --phase design \
  --sil 3
```

---

### 5. Check Forward Traceability

**OLD (placeholder)**:
```bash
python3 tools/traceability/check_forward_trace.py \
  --requirements SRS.md \
  --code src/ \
  --tests tests/
```

**NEW (working)**:
```bash
workspace.py trace query \
  --source SW-REQ-015 \
  --direction forward
```

---

### 6. Check Backward Traceability

**OLD (placeholder)**:
```bash
python3 tools/traceability/check_backward_trace.py \
  --code src/ \
  --requirements SRS.md
```

**NEW (working)**:
```bash
workspace.py trace query \
  --target ARCH-COMP-005 \
  --direction backward
```

---

### 7. Generate Traceability Report

**OLD (placeholder)**:
```bash
python3 tools/traceability/generate_report.py \
  --from requirements \
  --to architecture,design,tests \
  --output docs/traceability_report.md
```

**NEW (working)**:
```bash
workspace.py trace report \
  --from requirements \
  --to architecture,design,tests \
  --format markdown \
  --output docs/traceability_report.md
```

---

### 8. Import Traceability Data

**OLD (placeholder)**:
```bash
python3 tools/traceability/import_traces.py \
  --file legacy_traces.csv \
  --type requirements_to_design
```

**NEW (working)**:
```bash
workspace.py trace import \
  --file legacy_traces.csv \
  --type requirements_to_design
```

---

### 9. Visualize Traceability

**OLD (placeholder)**:
```bash
python3 tools/traceability/visualize.py \
  --from requirements \
  --to verification \
  --format mermaid
```

**NEW (working)**:
```bash
workspace.py trace visualize \
  --from requirements \
  --to verification \
  --format mermaid
```

---

### 10. Synchronize Formats

**OLD (placeholder)**:
```bash
python3 tools/traceability/sync.py --matrix all
```

**NEW (working)**:
```bash
workspace.py trace sync --matrix all
```

---

## Workflow Tool Mappings

### Old References → New Workspace Commands

| Old Command (if any) | New Command (WORKING) |
|----------------------|----------------------|
| N/A (new capability) | `workspace.py wf submit` |
| N/A (new capability) | `workspace.py wf review` |
| N/A (new capability) | `workspace.py wf approve` |
| N/A (new capability) | `workspace.py wf baseline` |
| N/A (new capability) | `workspace.py wf status` |
| N/A (new capability) | `workspace.py wf history` |

---

## Workflow Commands (New Capability)

### 1. Submit Document for Review

```bash
workspace.py wf submit DOC-SRS-2026-001 \
  --path docs/Software-Requirements-Specification.md \
  --author-role REQ \
  --author-name "Jane Doe" \
  --sil 3
```

### 2. Review and Approve Document

```bash
workspace.py wf review DOC-SRS-2026-001 \
  --role VER \
  --name "John Smith" \
  --approve \
  --comment "Verification complete, traceability validated"
```

### 3. Review and Reject Document

```bash
workspace.py wf review DOC-SRS-2026-001 \
  --role QUA \
  --name "Bob Wilson" \
  --reject \
  --comment "Traceability incomplete (3 requirements not traced)"
```

### 4. Mark as Approved

```bash
workspace.py wf approve DOC-SRS-2026-001
```

### 5. Create Baseline

```bash
workspace.py wf baseline \
  --phase requirements \
  --tag REQ-BASELINE-v1.0.0 \
  --message "Requirements phase complete"
```

### 6. Check Workflow Status

```bash
workspace.py wf status --all --format markdown
```

### 7. View Document History

```bash
workspace.py wf history DOC-SRS-2026-001
```

---

## Pattern-Based Replacement Rules

### For automated replacement in skill files:

1. **extract_traces.py** → `workspace.py trace extract`
2. **check_traceability.py** → `workspace.py trace validate`
3. **generate_matrix.py** → `workspace.py trace create`
4. **find_gaps.py** → `workspace.py trace check-gaps`
5. **check_forward_trace.py** → `workspace.py trace query --direction forward`
6. **check_backward_trace.py** → `workspace.py trace query --direction backward`
7. **check_all_traces.py** → `workspace.py trace validate`
8. **trace_checker.py** → `workspace.py trace validate`

---

## Files to Update

### en50128-verification (4 workflows, 5 resources)
- `workflows/verification-planning.md`
- `workflows/static-analysis-workflow.md`
- `workflows/traceability-verification.md`
- `workflows/verification-reporting.md`
- `resources/verification-tools-reference.md`
- `resources/verification-metrics.md`
- `resources/traceability-verification-checklist.md`
- `SKILL.md`

### en50128-requirements (4 workflows, 2 resources)
- `workflows/*.md` (all 4)
- `resources/*.md` (2 files with tool references)
- `SKILL.md`

### en50128-design (4 workflows, 5 resources)
- `workflows/*.md` (all 4)
- `resources/*.md` (check for tool references)
- `SKILL.md`

### en50128-implementation (4 workflows, 4 resources)
- `workflows/*.md` (all 4)
- `resources/*.md` (check for tool references)
- `SKILL.md`

---

## Migration Strategy

1. **Phase 1**: Update verification skill (highest tool usage)
2. **Phase 2**: Update requirements skill
3. **Phase 3**: Update design skill
4. **Phase 4**: Update implementation skill
5. **Phase 5**: Update completion reports

---

## Testing After Migration

After updating each skill, verify:

1. ✅ All tool references use `workspace.py trace` or `workspace.py wf`
2. ✅ Command syntax is correct (matches tool help)
3. ✅ Argument flags match new tool interface
4. ✅ Examples are runnable and produce expected output
5. ✅ No references to placeholder tools remain

---

**Date**: 2026-03-13  
**Status**: Ready for Migration
