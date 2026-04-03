# Traceability Tool Extraction Status

**Date**: 2026-04-03  
**Project**: TDC (Train Door Control System)  
**Status**: Option A Hybrid Approach — Partial Implementation

---

## Summary

We have successfully **added structured `[Trace: XXX]` tags to all Phase 3 documents** (SAS and SDS), making them ready for tool-based extraction. However, the current `trace extract` tool uses proximity-based heuristics and **does not parse the structured tags**, resulting in incorrect trace mappings.

---

## What Was Accomplished

###  1. Added Structured Trace Tags to Documents

**Software Architecture Specification (SAS)**:
- Added trace tags to all 8 components (COMP-001 through COMP-008)
- Format: `**Traceability**: [Trace: REQ-XXX, REQ-YYY, SW-HAZ-ZZZ]`
- Example (COMP-001 SKN):
  ```markdown
  **Traceability**: [Trace: REQ-SAFE-002, REQ-SAFE-007, REQ-SAFE-008, REQ-SAFE-009, 
  REQ-SAFE-010, REQ-SAFE-012, REQ-SAFE-014, REQ-SAFE-015, REQ-SAFE-018, REQ-FUN-009, 
  REQ-PERF-005, REQ-INT-010, SW-HAZ-001, SW-HAZ-003, SW-HAZ-006, SW-HAZ-008, SW-HAZ-011]
  ```

**Software Design Specification (SDS)**:
- Added trace tags to all 30 modules (MOD-SKN-001 through MOD-HAL-005)
- Format: `**Traceability**: [Trace: COMP-XXX, REQ-YYY]`
- Example (MOD-SKN-001):
  ```markdown
  **Traceability**: [Trace: COMP-001, REQ-SAFE-009, REQ-SAFE-012, REQ-INT-010, SW-HAZ-011]
  ```

**Total**: 38 structured trace tag sections added across Phase 3 documents.

---

## What the Tool Extraction Revealed

### Current Tool Behavior (Proximity Heuristics)

The `trace extract` tool (lines 1471-1539 in `tools/traceability_manager.py`) uses this algorithm:

1. Find all **target** artifacts (e.g., REQ-XXX) in the document
2. For each target, search ±500 characters for a **source** artifact (e.g., COMP-XXX)
3. Link the nearest source to the target
4. Assign confidence based on distance (< 100 chars = high, < 300 = medium, else low)

### Problem: Proximity ≠ Semantic Relationship

**Example**:
- Tool extracted: `COMP-002 → REQ-SAFE-007` (incorrect)
- Manual CSV has: `COMP-001-SKN → REQ-SAFE-007` (correct)
  
**Root cause**: REQ-SAFE-007 appears in the text, and COMP-002 (SPM) happens to be the nearest component ID within 500 chars, but the semantic relationship is with COMP-001 (SKN).

**Test results**:
- Tool extracted: **64 links** from SAS
- Manual CSV has: **51 component-to-requirement links** (from `doc9_to_doc6.csv`)
- Accuracy: **Unknown** (spot-check shows mismatches)

---

## Why Proximity Heuristics Fail

1. **Requirements mentioned in multiple sections**: A requirement may be discussed in COMP-002's section but actually implemented by COMP-001.
2. **Narrative text distance**: The trace tag for COMP-001 may be far from where REQ-XXX is mentioned in body text.
3. **No semantic parsing**: The tool doesn't understand that `[Trace: REQ-XXX]` means "this component traces to REQ-XXX"—it just sees them as nearby text.

---

## Path Forward: Three Options

### **Option A1: Enhance the `trace extract` Tool** ✅ RECOMMENDED

**Change**: Modify `_extract_links_from_content()` to:
1. Parse `[Trace: ...]` tags explicitly using regex
2. Extract the component/module ID from the nearest section header (`### X.Y COMP-XXX:` or `### X.Y MOD-XXX —`)
3. Link that source ID to all targets listed in the trace tag

**Advantages**:
- Documents are already prepared with structured tags
- Future documents can use the same convention
- Automated, scalable approach

**Effort**: ~2-4 hours to modify tool + test

---

### **Option A2: Use Manual CSV for Phase 3, Tool for Future Phases** 

**Approach**:
- Keep the 19 manually-created Phase 3 CSV files (already validated)
- For future phases (4-10), instruct DES/INT/TST to embed `[Trace: ...]` tags from the start
- Enhance tool before Phase 4 begins

**Advantages**:
- No rework of Phase 3 evidence
- Proof-of-concept for tool-based extraction in future phases

**Effort**: Minimal for Phase 3; deferred for Phase 4

---

### **Option B: Manual CSV Creation Only** (Current Fallback)

**Approach**:
- Document manual CSV creation as the official workflow
- Update CM skill: "CM shall manually create CSV files by reading documents"
- `trace extract` tool remains optional/experimental

**Advantages**:
- Already working for Phase 3
- No tool development needed
- CM retains full control over semantic accuracy

**Disadvantages**:
- Labor-intensive for large projects
- Prone to human error

---

## Recommendation

**Adopt Option A1** with a phased rollout:

1. **Immediate (Phase 3)**: Keep manual CSVs as authoritative
2. **Short-term (before Phase 4)**: Enhance `trace extract` to parse `[Trace: ...]` tags
3. **Medium-term (Phase 4+)**: Use tool-based extraction as primary method, manual review as verification

**Rationale**:
- Phase 3 documents are already instrumented with trace tags (38 sections)
- Tool enhancement is a one-time investment that benefits all future phases
- Maintains EN 50128 traceability rigor while improving efficiency

---

## Files Modified

### Phase 3 Documents (Trace Tags Added):
- `examples/TDC/docs/phase-3-architecture-design/Software-Architecture-Specification.md`
- `examples/TDC/docs/phase-3-architecture-design/Software-Design-Specification.md`

### Configuration:
- `examples/TDC/.traceability.yaml` — Updated component pattern to `COMP-[0-9]{3}`

### Evidence (Manual CSVs — Unchanged):
- `examples/TDC/evidence/traceability/doc9_to_doc6.csv` (51 links, COMP→REQ)
- `examples/TDC/evidence/traceability/doc10_to_doc6.csv` (98 links, MOD→REQ)
- `examples/TDC/evidence/traceability/doc10_to_doc9.csv` (30 links, MOD→COMP)
- ... (16 other Phase 3 CSV files)

---

## Next Steps (User Decision Required)

**Question for User**:

Which option should we pursue?

1. **Option A1**: Enhance `trace extract` tool to parse `[Trace: ...]` tags → automated extraction
2. **Option A2**: Keep manual CSVs for Phase 3; enhance tool before Phase 4
3. **Option B**: Adopt manual CSV creation as the official workflow; document in CM skill

**If Option A1 or A2 selected**, next actions:
- [ ] Modify `tools/traceability_manager.py` `_extract_links_from_content()` function
- [ ] Add regex to parse `[Trace: X, Y, Z]` patterns
- [ ] Extract section headers to identify source artifact IDs
- [ ] Test extraction on SAS and SDS
- [ ] Compare tool output vs. manual CSVs
- [ ] Update CM skill with hybrid workflow

**If Option B selected**, next actions:
- [ ] Update `.opencode/skills/en50128-configuration/SKILL.md` to formalize manual CSV workflow
- [ ] Update TRACEABILITY.md with per-phase manual workflow instructions
- [ ] Mark `trace extract` as optional/experimental in TOOLS.md

---

## References

- **Tool source**: `tools/traceability_manager.py` lines 1376-1539 (`extract` and `_extract_links_from_content`)
- **Manual CSVs**: `examples/TDC/evidence/traceability/doc*.csv`
- **Traceability rules**: `TRACEABILITY.md` Rules T1-T15
- **EN 50128**: §5.3.2.7 (traceability), §6.5.4.14-17 (traceability QA), Annex D.59 (traceability process)
