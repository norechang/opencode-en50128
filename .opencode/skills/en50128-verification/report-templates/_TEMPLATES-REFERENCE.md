# Verification and Validation Report Templates - Quick Reference

## Purpose

This document provides quick reference for VER/VAL/VMGR agents to use report templates.

## Template Locations

### Verification Templates
**Location:** `.opencode/skills/en50128-verification/report-templates/`

| Phase | File | Doc ID | Section Count |
|-------|------|--------|---------------|
| 2 | Software-Requirements-Verification-Report.md | DOC-REQVER-YYYY-NNN | 12 + 4 appendices |
| 3 | Software-Architecture-Design-Verification-Report.md | DOC-DESVER-YYYY-NNN | 12 + 4 appendices |
| 4 | Software-Component-Design-Verification-Report.md | DOC-COMPVER-YYYY-NNN | 12 + 4 appendices |
| 5 | Software-Source-Code-Verification-Report.md | DOC-IMPVER-YYYY-NNN | 12 + 4 appendices |
| 6 | Software-Integration-Verification-Report.md | DOC-INTVER-YYYY-NNN | 12 + 4 appendices |

### Validation Templates
**Location:** `.opencode/skills/en50128-validation/report-templates/`

| Phase | File | Doc ID | Section Count |
|-------|------|--------|---------------|
| 2 | Software-Requirements-Validation-Report.md | DOC-REQVAL-YYYY-NNN | 13 + 2 appendices |
| 3 | Software-Architecture-Design-Validation-Report.md | DOC-DESVAL-YYYY-NNN | 13 + 2 appendices |
| 4 | Software-Component-Design-Validation-Report.md | DOC-COMPVAL-YYYY-NNN | 13 + 2 appendices |
| 5 | Software-Source-Code-Validation-Report.md | DOC-IMPVAL-YYYY-NNN | 13 + 2 appendices |
| 6 | Software-Integration-Validation-Report.md | DOC-INTVAL-YYYY-NNN | 13 + 2 appendices |
| 7 | Software-Validation-Report.md | DOC-VALRPT-YYYY-NNN | 15 + 3 appendices |

## Quick Usage

### VER Agent - Create Verification Report

```bash
# 1. Select phase-appropriate template
TEMPLATE=".opencode/skills/en50128-verification/report-templates/Software-[Phase]-Verification-Report.md"

# 2. Copy to project docs/reports
cp $TEMPLATE docs/reports/[Project]-[Phase]-Verification-Report.md

# 3. Fill all sections:
# - Update Document ID with project year/sequence
# - Complete Document Control table
# - Fill Approvals (VER, QUA, VMGR/PM)
# - Execute verification per Section 6 methodology
# - Document results in Section 8 with evidence
# - Record defects in Section 9
# - Calculate metrics in Section 12
# - Write conclusion in Section 14
# - Sign verifier statement

# 4. Submit to QUA (SIL 3-4 MANDATORY)
/qua review-report-template --report docs/reports/[Report].md --type verification

# 5. After QUA approval, submit to VMGR (SIL 3-4)
# VMGR reviews technical content after QUA approves format
```

### VAL Agent - Create Validation Report (SIL 0-2)

```bash
# 1. Select phase-appropriate template
TEMPLATE=".opencode/skills/en50128-validation/report-templates/Software-[Phase]-Validation-Report.md"

# 2. Copy to project docs/reports
cp $TEMPLATE docs/reports/[Project]-[Phase]-Validation-Report.md

# 3. Perform validation in target environment

# 4. Fill all sections with validation evidence

# 5. Submit to PM for approval (SIL 0-2)
```

### VMGR - Create Validation Report (SIL 3-4)

```bash
# For SIL 3-4, VMGR performs validation activities (not VAL agent)

# 1. Review VER report (ensure QUA approved)

# 2. Perform independent validation
# - Testing in target environment
# - Supplementary tests
# - Operational scenarios
# - Customer acceptance

# 3. Select phase-appropriate template
TEMPLATE=".opencode/skills/en50128-validation/report-templates/Software-[Phase]-Validation-Report.md"

# 4. Copy to project docs/reports
cp $TEMPLATE docs/reports/[Project]-[Phase]-Validation-Report.md

# 5. Fill all sections with validation evidence

# 6. Submit to QUA for template compliance (MANDATORY)
/qua review-report-template --report docs/reports/[Report].md --type validation

# 7. After QUA approval, provide V&V approval/rejection to COD
/vmgr approve-gate [phase]
```

## Template Section Checklist

### Verification Report Checklist (12 sections + 4 appendices)

- [ ] 1. Header (Doc ID, Type, Phase, EN 50128 Ref)
- [ ] 2. Document Control (version table, CI, baseline)
- [ ] 3. Approvals (VER, QUA, VMGR/PM, independence declaration)
- [ ] 4. Executive Summary (project, SIL, scope, result, summary)
- [ ] 5. Introduction (purpose, scope, references, team)
- [ ] 6. Verification Methodology (Table A.5 techniques, activities, tools)
- [ ] 7. Verification Criteria (phase-specific from YAML)
- [ ] 8. Verification Results (template compliance, quality, traceability)
- [ ] 9. Defects and Issues (critical/major/minor, observations)
- [ ] 10. Traceability Analysis (metrics, issues)
- [ ] 11. EN 50128 Compliance (Table A.x, independence)
- [ ] 12. Metrics (quality, complexity, coverage)
- [ ] 13. Recommendations (mandatory actions, improvements)
- [ ] 14. Conclusion (assessment, conditions, verifier statement)
- [ ] Appendix A: Verification Checklist
- [ ] Appendix B: Traceability Matrix
- [ ] Appendix C: Defect Details
- [ ] Appendix D: Tool Output

### Validation Report Checklist (13 sections + 2-3 appendices)

- [ ] 1. Header (Doc ID, Type, Phase, EN 50128 Ref)
- [ ] 2. Document Control (version table, CI, baseline)
- [ ] 3. Approvals (VAL/VMGR, QUA, Customer, independence declaration)
- [ ] 4. Executive Summary (project, SIL, scope, result, summary)
- [ ] 5. Introduction (purpose, scope, references, team)
- [ ] 6. Validation Methodology (Table A.7 for Phase 7, testing approach)
- [ ] 7. Validation Criteria (operational suitability, fitness for purpose)
- [ ] 8. Validation Results (testing results, operational scenarios)
- [ ] 9. Issues and Observations
- [ ] 10. Operational Scenarios Validated
- [ ] 11. EN 50128 Compliance (Table A.7 for Phase 7, independence)
- [ ] 12. Acceptance Testing (Phase 7 only - customer sign-off)
- [ ] 13. Recommendations
- [ ] 14. Conclusion (assessment, validator approval/rejection statement)
- [ ] Appendix A: Test Results
- [ ] Appendix B: Operational Scenario Details
- [ ] Appendix C: Customer Acceptance (Phase 7 only)

## QUA Template Compliance Review Checklist

When QUA reviews reports for template compliance:

### Verification Report (12 + 4)
- [ ] Document ID format: `DOC-[TYPE]VER-YYYY-NNN`
- [ ] Document Control table complete
- [ ] Approvals table with VER, QUA, VMGR (SIL 3-4) or PM (SIL 0-2)
- [ ] Independence declaration present (SIL 3-4)
- [ ] 12 main sections present (Executive Summary through Conclusion)
- [ ] 4 appendices present (Checklist, Traceability, Defects, Tool Output)
- [ ] EN 50128 references correct (Annex C #, Section 7.x)
- [ ] Verifier statement signed

### Validation Report (13 + 2-3)
- [ ] Document ID format: `DOC-[TYPE]VAL-YYYY-NNN` or `DOC-VALRPT-YYYY-NNN` (Phase 7)
- [ ] Document Control table complete
- [ ] Approvals table with VAL/VMGR, QUA, Customer (Phase 7)
- [ ] Independence declaration present (SIL 3-4)
- [ ] 13 main sections present (Phase 2-6) or 15 (Phase 7)
- [ ] 2-3 appendices present
- [ ] EN 50128 references correct (Annex C #25 for Phase 7)
- [ ] Validator statement with approval/rejection

## VMGR Technical Review Checklist (SIL 3-4)

After QUA template compliance approval:

### Verification Reports
- [ ] QUA template compliance approval obtained
- [ ] Verification techniques appropriate for SIL level (Table A.5)
- [ ] All phase criteria checked with evidence
- [ ] Defects properly categorized (critical/major/minor)
- [ ] Critical defects have resolution plan
- [ ] Traceability 100% complete
- [ ] Metrics meet SIL requirements
- [ ] EN 50128 techniques applied correctly
- [ ] Independence requirements met (SIL 3-4)
- [ ] Verifier statement credible

### Validation Reports
- [ ] QUA template compliance approval obtained
- [ ] Testing performed in target environment (or validated simulation)
- [ ] Operational scenarios cover intended use
- [ ] Performance requirements validated (M SIL 3-4)
- [ ] Functional/black-box testing complete (M SIL 3-4 Phase 7)
- [ ] Customer acceptance obtained (Phase 7)
- [ ] All issues tracked and resolved
- [ ] Independence requirements met (SIL 3-4)
- [ ] Validator approval/rejection clear

## Phase-Specific Notes

### Phase 2: Requirements
- **Verification:** Traceability (system→software), testability, hazard coverage
- **Validation:** Requirements testable, unambiguous, complete, consistent

### Phase 3: Architecture & Design
- **Verification:** Modular decomposition (M SIL 2+), interfaces, complexity ≤10 (SIL 3-4)
- **Validation:** Architecture implementable in C/MISRA C, design testable

### Phase 4: Component Design
- **Verification:** Algorithms specified, data structures fixed-size, complexity ≤10 (SIL 3-4)
- **Validation:** Components implementable, tests executable with Unity

### Phase 5: Implementation
- **Verification:** MISRA C (zero mandatory violations SIL 2+), static analysis, coverage 100% (SIL 3-4)
- **Validation:** Code executes on target, performance OK, error handling works

### Phase 6: Integration
- **Verification:** Integration tests cover all interfaces, performance tested (HR SIL 3-4)
- **Validation:** Integrated SW meets architecture, target HW performance OK

### Phase 7: Final Validation
- **Validation:** SW fit for intended application, customer acceptance, release authorization
- **MANDATORY:** Performance testing (M SIL 3-4), functional/black-box (M SIL 3-4)

## EN 50128 Cross-References

| Phase | Verification Annex C | Validation Annex C | Key Tables |
|-------|---------------------|-------------------|------------|
| 2 | #8 | - | A.2, A.5 |
| 3 | #14 | - | A.3, A.5 |
| 4 | #17 | - | A.4, A.5 |
| 5 | #20 | - | A.4, A.5, A.13, A.19, A.21 |
| 6 | #23 | - | A.6, A.5 |
| 7 | - | #25 | A.7, A.14, A.18 |

## Workflow Summary

```
Phase Start
    │
    ├─→ VER creates Verification Report
    │       │
    │       ├─→ QUA reviews template compliance (SIL 3-4 MANDATORY)
    │       │       └─→ 1-pass rule: Approve or reject (1 resubmit)
    │       │
    │       └─→ VMGR reviews technical content (SIL 3-4 MANDATORY)
    │
    ├─→ VAL/VMGR creates Validation Report
    │       │
    │       ├─→ QUA reviews template compliance (SIL 3-4 MANDATORY)
    │       │       └─→ 1-pass rule: Approve or reject (1 resubmit)
    │       │
    │       └─→ VMGR provides V&V approval/rejection (SIL 3-4)
    │
    └─→ COD Gate Check
            ├─→ Verify QUA approvals (SIL 3-4)
            ├─→ Verify VMGR V&V approval (SIL 3-4)
            ├─→ Verify all defects resolved
            └─→ Authorize phase transition
```

---

**Quick Reference Version:** 1.0  
**Last Updated:** 2026-02-21  
**Owner:** en50128-verification / en50128-validation skills
