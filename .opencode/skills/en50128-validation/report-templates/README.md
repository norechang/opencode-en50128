# Validation Report Templates

## Purpose

This directory contains EN 50128 compliant validation report templates that VAL agents (or VMGR for SIL 3-4) use to document independent validation activities for each lifecycle phase.

## Available Templates

| Phase | Template File | Doc ID Pattern | Validation Focus |
|-------|--------------|----------------|------------------|
| 2 | Software-Requirements-Validation-Report.md | DOC-REQVAL-YYYY-NNN | Requirements testability, completeness, consistency |
| 3 | Software-Architecture-Design-Validation-Report.md | DOC-DESVAL-YYYY-NNN | Architecture implementability, testability, safety patterns |
| 4 | Software-Component-Design-Validation-Report.md | DOC-COMPVAL-YYYY-NNN | Component implementability in C, test executability |
| 5 | Software-Source-Code-Validation-Report.md | DOC-IMPVAL-YYYY-NNN | Code execution on target, performance, error handling |
| 6 | Software-Integration-Validation-Report.md | DOC-INTVAL-YYYY-NNN | Integrated SW meets architecture, target HW performance |
| 7 | Software-Validation-Report.md | DOC-VALRPT-YYYY-NNN | **FINAL VALIDATION** - SW fit for intended application |

## Template Structure

All validation templates follow a similar structure to verification templates but with **validation-specific focus**:

1. Header (Doc ID, Type, Phase, EN 50128 Ref)
2. Document Control
3. Approvals (**VAL/VMGR**, QUA, Customer - SIL 3-4)
4. Executive Summary
5. Introduction
6. Validation Methodology (EN 50128 Table A.7 for Phase 7)
7. Validation Criteria (operational suitability, fitness for purpose)
8. Validation Results (testing in target environment, operational scenarios)
9. Issues and Observations
10. Operational Scenarios Validated
11. EN 50128 Compliance
12. Acceptance Testing (Phase 7)
13. Recommendations
14. Conclusion (with Validator approval/rejection statement)
15. Appendices

## Validation vs Verification

| Aspect | Verification (VER) | Validation (VAL/VMGR) |
|--------|-------------------|----------------------|
| **Question** | "Did we build it right?" | "Did we build the right thing?" |
| **Focus** | Conformance to specification | Fitness for intended use |
| **Method** | Document review, static analysis | Testing in target environment, operational scenarios |
| **Environment** | Development environment | Target environment (or validated simulation) |
| **Independence** | SIL 3-4: Independent from development | SIL 3-4: **MANDATORY** independent from development AND PM |
| **Performer** | VER agent | VAL agent (SIL 0-2), **VMGR** (SIL 3-4) |

## Usage Workflow

### For VAL Agent (SIL 0-2)

```bash
# 1. Copy template to project
cp .opencode/skills/en50128-validation/report-templates/[Template].md \
   docs/reports/[Project-Specific-Name].md

# 2. Perform validation activities
# - Execute tests in target environment
# - Test operational scenarios
# - Validate performance requirements
# - Confirm fitness for purpose

# 3. Document validation results with evidence

# 4. Submit to QUA for template compliance review (if applicable)

# 5. Submit to PM for approval
```

### For VMGR (SIL 3-4)

```bash
# VMGR acts as Validator for SIL 3-4 projects

# 1. Review VER report (ensure QUA approved)
# 2. Perform validation activities
#    - Independent testing in target environment
#    - Supplementary tests (validator's discretion)
#    - Operational scenario validation
#    - Customer acceptance testing

# 3. Create validation report
cp .opencode/skills/en50128-validation/report-templates/[Template].md \
   docs/reports/[Report].md

# 4. Submit to QUA for template compliance review (MANDATORY)
/qua review-report-template --report docs/reports/[Report].md --type validation

# 5. Fix any QUA-identified issues (1 resubmission allowed)

# 6. Provide final V&V approval/rejection to COD
/vmgr approve-gate [phase]
```

### For QUA Agent

```bash
# Review validation report for template compliance
/qua review-report-template --report docs/reports/[Report].md --type validation

# Check:
# - Document ID format: DOC-[TYPE]VAL-YYYY-NNN or DOC-VALRPT-YYYY-NNN (Phase 7)
# - Document Control table complete
# - Approvals table with VAL/VMGR, QUA, Customer (Phase 7)
# - All required sections present (13 for Phase 2-6, 15 for Phase 7)
# - Independence declaration (SIL 3-4)

# Output: QA-Template-Review-[Phase]-Validation.md
```

## SIL Requirements

| SIL | Validation Required | Independence | VMGR Performs | QUA Template Review |
|-----|---------------------|--------------|---------------|---------------------|
| 0-1 | Phases 2-7 | Not required | No (VAL) | Optional |
| 2 | Phases 2-7 | Recommended | No (VAL) | Recommended |
| 3-4 | Phases 2-7 | **MANDATORY** | **YES (VMGR)** | **MANDATORY** |

## Phase 7: Final Software Validation

Phase 7 validation is **the most critical validation activity**:

- **Performer:** VMGR (SIL 3-4 MANDATORY), VAL (SIL 0-2)
- **Independence:** MANDATORY SIL 3-4 - Validator does NOT report to PM (EN 50128 5.1.2.10f)
- **Environment:** Target hardware or validated simulation
- **Scope:** Complete software system validation
- **Activities:**
  - Overall software testing per Overall Software Test Specification
  - Validator supplementary tests (complex operational scenarios)
  - Normal operation, anticipated occurrences, undesired conditions
  - Performance testing (MANDATORY SIL 3-4 per Table A.7)
  - Functional/black-box testing (MANDATORY SIL 3-4 per Table A.7)
  - Customer acceptance testing
- **Output:** Software Validation Report + Release Note
- **Approval:** Customer sign-off REQUIRED

## EN 50128 References

- **Section 7.7** - Overall Software Testing / Validation
- **Section 5.1.2.8** - Validator gives agreement/disagreement for software release
- **Section 5.1.2.10f** - Validator shall NOT report to Project Manager (SIL 3-4)
- **Table A.7** - Overall Software Testing/Validation techniques
- **Annex C #25** - Software Validation Report

## Cross-References

- **Validation Criteria** - `.opencode/skills/en50128-validation/validation-criteria/`
- **Phase Definitions** - `.opencode/skills/en50128-project-management/phase-definitions/`
- **VAL Command** - `.opencode/commands/val.md`
- **VMGR Command** - `.opencode/commands/vmgr.md`
- **QUA Command** - `.opencode/commands/qua.md`

## Template Maintenance

**Owner:** VAL skill (`en50128-validation`)  
**Version:** 1.0  
**Last Updated:** 2026-02-21

To update templates:
1. Update template file
2. Update this README.md with changes
3. Obtain QUA review of template modifications
4. Update version number in template header
