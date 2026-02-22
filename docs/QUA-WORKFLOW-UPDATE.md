# QUA Document Template Compliance Workflow Update

**Date**: 2026-02-19  
**Purpose**: Integrate explicit QUA document template compliance checks before VER verification  
**Scope**: All EN 50128 lifecycle phases  

---

## Executive Summary

**Problem**: QUA document template compliance checks were documented in the QUA agent specification but were NOT explicitly integrated into the workflow before VER verification. This could lead to non-compliant documents entering verification, causing rework delays.

**Solution**: Updated LIFECYCLE.md, AGENTS.md, and qua.md to add explicit QUA template compliance checks BEFORE VER verification in every phase.

**Impact**: Prevents non-compliant documents from entering verification (SIL 3-4), reduces rework, improves efficiency.

---

## Changes Made

### 1. LIFECYCLE.md Updates

#### Phase 2: Requirements (Section 3)
- **Key Activities** (3.2): Added activity 6: "QA document template compliance check (MANDATORY before VER for SIL 3-4)"
- **Agents Involved** (3.3): Clarified QUA role: "Document template compliance check BEFORE VER"
- **Deliverables** (3.5): Added deliverable: "QA Document Template Compliance Report (MANDATORY SIL 3-4, BEFORE VER)"
- **Gate Checklist** (3.11): Added gate criteria: "QA document template compliance verified (MANDATORY SIL 3-4)"

#### Phase 3: Architecture & Design (Section 4)
- **Key Activities** (4.2): Added activity 8: "QA document template compliance check (MANDATORY before VER for SIL 3-4)"
- **Agents Involved** (4.3): Clarified QUA role: "Document template compliance check BEFORE VER"
- **Deliverables** (4.5): Added deliverable: "QA Document Template Compliance Report (MANDATORY SIL 3-4, BEFORE VER)"
- **Gate Checklist** (4.12): Added gate criteria: "QA document template compliance verified (MANDATORY SIL 3-4)"

#### Phase 4: Implementation & Testing (Section 5)
- **Deliverables** (5.5): Changed "Code Review Report" to "QA Code Review Report (MANDATORY - includes template compliance for code documentation)"
- **Gate Checklist** (5.13): Changed to emphasize: "QA code review report approved (MANDATORY - includes MISRA C compliance check)"

#### Phase 5: Integration (Section 6)
- **Deliverables** (6.5): Added deliverable: "QA Integration Test Review Report (includes template compliance)"
- **Gate Checklist** (6.11): Added gate criteria: "QA integration test review approved (includes template compliance)"

#### Phase 6: Validation (Section 7)
- **Deliverables** (7.5): Added deliverable: "QA Validation Review Report (includes template compliance)"
- **Gate Checklist** (7.11): Added gate criteria: "QA validation review approved (includes template compliance)"

#### Workflow Example (Section 11.1)
Updated complete SIL 3 workflow to include explicit QUA calls:
- **After Phase 2 (Requirements)**: Added `/qua` step with explicit template compliance checks before `/ver`
- **After Phase 3 (Design)**: Added `/qua` step with template compliance and design review before `/ver`
- **After Phase 4 (Implementation)**: Moved `/qua` BEFORE `/ver` (was after), emphasized template compliance
- **After Phase 5 (Integration)**: Added `/qua` step for integration test review before `/ver`
- **After Phase 6 (Validation)**: Added `/qua` step for validation review before `/ver`

---

### 2. AGENTS.md Updates

#### Example Workflow (lines 681-750)
Completely restructured workflow to show QUA at correct checkpoints:

**Before Update**:
```bash
# 1. REQ → 2. DES → 3. SAF → 4. IMP → 5. QUA (code review) → 6. TST → 7. INT → 8. VER → 9. VAL
```

**After Update**:
```bash
# 1. REQ → 2. SAF → 3. QUA (template) → 4. DES → 5. QUA (template) → 6. IMP → 7. TST → 
# 8. QUA (code review, BEFORE VER) → 9. VER → 10. INT → 11. QUA (test review) → 12. VAL → 
# 13. QUA (validation review)
```

**Key Changes**:
- Added `/qua` step 3: Document template compliance after requirements (BEFORE VER)
- Added `/qua` step 5: Design document template compliance (BEFORE VER)
- Moved `/qua` step 8: Code review now explicitly BEFORE VER (was step 5, after IMP)
- Added `/qua` step 11: Integration test review (MANDATORY SIL 3-4)
- Added `/qua` step 13: Validation review (MANDATORY SIL 3-4)

**Explicit Comments Added**:
- Step 3: "# 3. QUA: Document template compliance (MANDATORY SIL 3-4, BEFORE VER)"
- Step 5: "# 5. QUA: Design document template compliance (MANDATORY SIL 3-4, BEFORE VER)"
- Step 8: "# 8. QUA: Code review (MANDATORY all SILs, BEFORE VER)"
- Step 11: "# 11. QUA: Integration test review (MANDATORY SIL 3-4)"
- Step 13: "# 13. QUA: Validation review (MANDATORY SIL 3-4)"

---

### 3. .opencode/commands/qua.md Updates

#### Role and Responsibilities (lines 5-15)
**Before**: "Document template compliance verification"

**After**: "Document template compliance verification (BEFORE VER)" with new section:

```markdown
### Document Template Compliance (MANDATORY)

**CRITICAL**: QA document template compliance checks MUST occur **BEFORE** the Verifier (VER) 
performs independent verification. This is a quality gate that prevents non-compliant 
documents from entering the verification process.

**Workflow Position**: QUA → VER → Approval
```

#### QA Responsibilities (lines 32-46)
**Added**:
- Item 1: "**BEFORE VER**: Verify all documents follow standard template (quality gate)"
- Item 5: "Reject non-compliant documents for SIL 3-4 projects (BEFORE VER)"
- Item 7: "Generate QA Template Compliance Report"

**New Section**: Template Compliance Workflow by Phase
```markdown
**Template Compliance Workflow by Phase:**
- **Phase 1 (Planning)**: QUA checks SQAP, SCMP, SVP, SVaP → then VER verifies
- **Phase 2 (Requirements)**: QUA checks SRS, RTM, Hazard Log, Test Spec → then VER verifies
- **Phase 3 (Design)**: QUA checks SAS, SDS, ICD → then VER verifies
- **Phase 4 (Implementation)**: QUA code review (includes doc compliance) → then VER verifies
- **Phase 5 (Integration)**: QUA checks integration test docs → then VER verifies
- **Phase 6 (Validation)**: QUA checks validation test docs → then VER verifies
```

---

## Workflow Summary: QUA Checkpoints

| Phase | When to Call QUA | What QUA Checks | Deliverable | Mandatory? |
|-------|------------------|-----------------|-------------|------------|
| **1. Planning** | After PM/CM create plans | SQAP, SCMP, SVP, SVaP template compliance | QA Template Compliance Report | SIL 3-4: M |
| **2. Requirements** | After REQ/SAF create docs | SRS, RTM, Hazard Log template compliance | QA Template Compliance Report | SIL 3-4: M |
| **3. Design** | After DES/SAF create docs | SAS, SDS, ICD template compliance + design review | QA Template + Design Review Report | SIL 3-4: M |
| **4. Implementation** | After IMP/TST, BEFORE VER | Code review (MISRA C, complexity, defensive programming) | QA Code Review Report | ALL: M |
| **5. Integration** | After INT, BEFORE VER | Integration test docs template compliance | QA Integration Test Review | SIL 3-4: M |
| **6. Validation** | After VAL, BEFORE VER | Validation docs template compliance | QA Validation Review Report | SIL 3-4: M |

**M** = Mandatory  
**ALL** = Mandatory for ALL SIL levels (0, 1, 2, 3, 4)

---

## Rationale

### Why QUA BEFORE VER?

1. **Quality Gate**: QUA acts as a quality gate to catch template non-compliance early
2. **Efficiency**: Prevents non-compliant documents from entering expensive verification process
3. **Independence**: VER can focus on technical verification, not administrative compliance
4. **EN 50128 Compliance**: Table A.9 requires Company Quality System (M) and Traceability (M SIL 3-4)
5. **Reduce Rework**: Catching template issues early reduces downstream rework

### EN 50128 Requirements

**Section 6.5** (Software Quality Assurance):
- "The software quality assurance plan shall ensure that the software is developed in accordance with the requirements of this standard"
- Quality assurance is **continuous throughout the lifecycle**

**Table A.9** (Software Quality Assurance techniques):
- Technique 2: EN ISO 9001 Compliance (MANDATORY all SILs)
- Technique 4: Company Quality System (MANDATORY all SILs)
- Technique 7: Traceability (MANDATORY SIL 3-4)

**Document Templates** (Annex C Table C.1):
- All documents SHALL follow standard structure
- Document ID, Document Control, Approvals table MANDATORY

---

## Verification (Current Project: train_door_control2)

### Current Status
- **Phase 1 (Planning)**: ✅ Template compliance WAS checked (see LIFECYCLE_STATE.md line 37)
- **Phase 2 (Requirements)**: ⚠️ Template compliance checked by VER, NOT by QUA first
  - Verification Report (Requirements-Verification.md) shows VER performed template checks
  - **Missing**: QUA template compliance report generated BEFORE VER

### Recommended Next Steps for Current Project

1. **Retroactive QUA Check** (Optional for Phase 2):
   - Generate QA Template Compliance Report for Phase 2 documents
   - Document that template compliance was verified (by VER) but without separate QUA report
   - Add note to LIFECYCLE_STATE.md

2. **Going Forward** (Phase 3+):
   - **Phase 3 (Design)**: Call `/qua` AFTER design docs created, BEFORE `/ver`
   - **Phase 4 (Implementation)**: Call `/qua` for code review BEFORE `/ver`
   - **Phase 5 (Integration)**: Call `/qua` for integration test review BEFORE `/ver`
   - **Phase 6 (Validation)**: Call `/qua` for validation review BEFORE `/ver`

---

## Gate Criteria Updates

All phase gate checklists now include:
- **Phase 2**: "QA document template compliance verified (MANDATORY SIL 3-4)"
- **Phase 3**: "QA document template compliance verified (MANDATORY SIL 3-4)"
- **Phase 4**: "QA code review report approved (MANDATORY - includes MISRA C compliance check)"
- **Phase 5**: "QA integration test review approved (includes template compliance)"
- **Phase 6**: "QA validation review approved (includes template compliance)"

COD gate-check commands will now verify QUA reports are present before authorizing phase transitions (SIL 3-4).

---

## Impact Assessment

### Benefits ✅
1. **Earlier defect detection**: Template issues caught by QUA before VER
2. **Clearer workflow**: Explicit QUA checkpoints in every phase
3. **Reduced rework**: Non-compliant docs don't enter verification
4. **Better compliance**: Aligns with EN 50128 Section 6.5 quality assurance requirements
5. **Efficiency**: VER focuses on technical verification, not template compliance

### Risks ⚠️
1. **Additional step**: Adds QUA step before VER in each phase (but SHOULD already be doing this)
2. **Workflow length**: Slightly longer workflow (but more robust)
3. **Resource needs**: Requires QUA availability before VER (independence preserved)

### Mitigation
- QUA and VER can work in parallel on different aspects (QUA: template, VER: technical)
- QUA template checks are fast (checklist-based)
- Tools can automate template compliance checks (future enhancement)

---

## Conclusion

This update **explicitly integrates QUA document template compliance checks** into the workflow **BEFORE VER verification** for all lifecycle phases. This aligns with EN 50128 Section 6.5 quality assurance requirements and prevents non-compliant documents from entering verification, reducing rework and improving efficiency.

**Status**: ✅ **COMPLETE** - LIFECYCLE.md, AGENTS.md, and qua.md updated

**Next Action**: Apply updated workflow starting Phase 3 (Design) for train_door_control2 project

---

## References

- **EN 50128:2011 Section 6.5**: Software Quality Assurance
- **EN 50128:2011 Table A.9**: Software Quality Assurance techniques
- **EN 50128:2011 Annex C Table C.1**: Document control summary
- **LIFECYCLE.md**: Complete V-Model lifecycle with phase gates
- **AGENTS.md**: Role-based agent definitions and workflows
- **.opencode/commands/qua.md**: Quality Assurance agent specification
- **LIFECYCLE_STATE.md**: Current project state tracking
