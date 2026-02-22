# Verification Report Templates

## Purpose

This directory contains EN 50128 compliant verification report templates that VER agents use to document independent verification activities for each lifecycle phase.

## Available Templates

| Phase | Template File | Doc ID Pattern | Deliverables Verified |
|-------|--------------|----------------|----------------------|
| 2 | Software-Requirements-Verification-Report.md | DOC-REQVER-YYYY-NNN | SRS, Hazard Log, Overall Test Spec |
| 3 | Software-Architecture-Design-Verification-Report.md | DOC-DESVER-YYYY-NNN | SAS, SDS, Interface Specs, Integration Test Specs |
| 4 | Software-Component-Design-Verification-Report.md | DOC-COMPVER-YYYY-NNN | Component Design Spec, Component Test Spec |
| 5 | Software-Source-Code-Verification-Report.md | DOC-IMPVER-YYYY-NNN | Source Code, Component Test Report |
| 6 | Software-Integration-Verification-Report.md | DOC-INTVER-YYYY-NNN | SW Integration Test Report, SW/HW Integration Test Report |

## Template Structure

All templates follow the same 12-section + 4-appendix structure defined in `TEMPLATE-STRUCTURE.md`:

1. Header (Doc ID, Type, Phase, EN 50128 Ref)
2. Document Control
3. Approvals (VER, QUA, VMGR/PM)
4. Executive Summary
5. Introduction
6. Verification Methodology
7. Verification Criteria (phase-specific)
8. Verification Results (phase-specific)
9. Defects and Issues
10. Traceability Analysis
11. EN 50128 Compliance
12. Metrics (phase-specific)
13. Recommendations
14. Conclusion
15. Appendices

## Usage Workflow

### For VER Agent

```bash
# 1. Copy template to project
cp .opencode/skills/en50128-verification/report-templates/[Template].md \
   docs/reports/[Project-Specific-Name].md

# 2. Fill in all sections
# - Update document ID with project year and sequence number
# - Complete Document Control and Approvals
# - Execute verification activities
# - Document results with evidence
# - Record defects and metrics
# - Write conclusion and sign

# 3. Submit to QUA for template compliance review (SIL 3-4 MANDATORY)
/qua review-report-template --report docs/reports/[Report].md --type verification

# 4. Fix any QUA-identified template issues (1 resubmission allowed)

# 5. Submit to VMGR for technical review (SIL 3-4 only)
# VMGR reviews after QUA approval
```

### For QUA Agent

```bash
# Review verification report for template compliance
/qua review-report-template --report docs/reports/[Report].md --type verification

# Check:
# - Document ID format: DOC-[TYPE]VER-YYYY-NNN
# - Document Control table complete
# - Approvals table with all required roles
# - All 12 main sections present
# - All 4 appendices present
# - Independence declaration (SIL 3-4)

# Output: QA-Template-Review-[Phase]-Verification.md
```

### For VMGR (SIL 3-4 only)

```bash
# Review verification report for technical adequacy
/vmgr review-verification [phase]

# Check:
# - QUA template compliance approval obtained
# - Verification techniques appropriate for SIL
# - All criteria checked with evidence
# - Defects properly categorized and tracked
# - Traceability complete (100%)
# - Metrics meet SIL requirements

# Approve or reject for gate transition
```

## SIL Requirements

| SIL | QUA Template Review | VMGR Technical Review | VER Independence |
|-----|--------------------|-----------------------|------------------|
| 0-1 | Optional | Not required | Not required |
| 2 | Recommended | Not required | Recommended |
| 3-4 | **MANDATORY** | **MANDATORY** | **MANDATORY** |

## EN 50128 References

- **Section 6.2** - Verification
- **Section 7.x** - Phase-specific verification requirements
- **Table A.5** - Verification and Testing techniques
- **Annex C** - Document control summary

## Phase-Specific Notes

### Phase 5 (Implementation) - Most Detailed

Phase 5 verification is the most detailed and includes:
- **MISRA C:2012 compliance** - Zero mandatory violations (SIL 2+)
- **Static analysis** - PC-lint Plus, Cppcheck, Clang Static Analyzer
- **Complexity analysis** - Cyclomatic complexity ≤10 (SIL 3-4)
- **Coverage analysis** - 100% statement/branch/MC-DC (SIL 3-4)
- **Defensive programming** - NULL checks, bounds checks, error handling
- **Memory management** - Static allocation only (SIL 2+), no recursion (HR SIL 3-4)

### Phase 6 (Integration) - Performance Focus

Phase 6 verification includes:
- **Interface testing** - All module and SW/HW interfaces
- **Integration strategy** - Bottom-up, top-down, or sandwich
- **Performance testing** - HR for SIL 3-4
- **Configuration management** - All items under control

## Cross-References

- **INDEX.md** - Template index with descriptions
- **TEMPLATE-STRUCTURE.md** - Detailed structure specification
- **Phase Definitions** - `.opencode/skills/en50128-project-management/phase-definitions/`
- **VER Command** - `.opencode/commands/ver.md`
- **QUA Command** - `.opencode/commands/qua.md`
- **VMGR Command** - `.opencode/commands/vmgr.md`

## Template Maintenance

**Owner:** VER skill (`en50128-verification`)  
**Version:** 1.0  
**Last Updated:** 2026-02-21

To update templates:
1. Update template file
2. Update INDEX.md with changes
3. Update this README.md if structure changes
4. Obtain QUA review of template modifications
5. Update version number in template header
