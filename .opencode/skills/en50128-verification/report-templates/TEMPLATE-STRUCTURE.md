# Verification Report Template Structure

This document defines the standard structure for all EN 50128 verification reports.

## Standard Sections (All Reports)

### 1. Header Block
```markdown
# [Report Title]
**Document ID:** DOC-[TYPE]VER-YYYY-NNN
**Document Type:** [Type]
**Phase:** Phase [N] - [Phase Name]
**EN 50128 Reference:** Annex C #[N], Section 7.[N]
```

### 2. Document Control Table
- Version history
- Configuration Item ID
- Baseline ID

### 3. Approvals Table
- Verifier (VER)
- Quality Assurance (QUA)
- V&V Manager (VMGR) - SIL 3-4 only
- Project Manager (PM) - SIL 0-2
- Independence Declaration - SIL 3-4 only

### 4. Executive Summary
- Project name, SIL level
- Verification date range
- Verifier name
- Verification scope (deliverables verified)
- Overall result (PASS/FAIL/PASS WITH OBSERVATIONS)
- Brief summary

### 5. Introduction
- 5.1 Purpose
- 5.2 Scope (list of deliverables)
- 5.3 Reference Documents (table)
- 5.4 Verification Team (table with independence column)

### 6. Verification Methodology
- 6.1 Verification Techniques Applied (EN 50128 Table A.5)
- 6.2 Verification Activities (numbered list)
- 6.3 Tools Used (table)

### 7. Verification Criteria
Phase-specific criteria from phase definition YAML file

### 8. Verification Results
Phase-specific results sections with:
- Template compliance checks
- Quality checks
- Traceability metrics
- Evidence references
- Issue IDs

### 9. Defects and Issues
- 9.1 Critical Defects (table)
- 9.2 Major Defects (table)
- 9.3 Minor Defects (table)
- 9.4 Observations (table)

### 10. Traceability Analysis
Phase-specific traceability:
- Requirements → Architecture → Design → Code → Tests
- Summary metrics (%, counts)
- Traceability issues table

### 11. EN 50128 Compliance
- 11.1 Table A.[N] Techniques (phase-specific)
- 11.2 Independence Requirements (SIL 3-4)

### 12. Metrics
Phase-specific metrics:
- Quality metrics
- Complexity metrics
- Coverage metrics
- Traceability metrics

### 13. Recommendations
- 13.1 Mandatory Actions
- 13.2 Suggested Improvements

### 14. Conclusion
- 14.1 Overall Assessment
- 14.2 Conditions for Approval (checklist)
- 14.3 Verifier Statement (certification with signature)

### 15. Appendices
- Appendix A: Verification Checklist
- Appendix B: Traceability Matrix
- Appendix C: Defect Details
- Appendix D: Tool Output (phase-specific)

## Phase-Specific Variations

### Phase 2: Requirements
- Verify: SRS, Hazard Log, Overall Software Test Specification
- Focus: Traceability, testability, hazard coverage
- Tool Output: Requirements analysis, traceability reports

### Phase 3: Architecture & Design
- Verify: SAS, SDS, Interface Specs, Integration Test Specs
- Focus: Modular decomposition, interfaces, complexity
- Tool Output: Complexity metrics, architecture analysis

### Phase 4: Component Design
- Verify: Component Design Spec, Component Test Spec
- Focus: Detailed design, algorithms, test coverage
- Tool Output: Complexity metrics, design analysis

### Phase 5: Implementation
- Verify: Source Code, Component Test Report
- Focus: MISRA C compliance, static analysis, coverage
- Tool Output: MISRA checker, static analysis, coverage reports
- **MOST DETAILED PHASE** - includes code quality metrics

### Phase 6: Integration
- Verify: SW Integration Test Report, SW/HW Integration Test Report
- Focus: Interface testing, integration strategy, performance
- Tool Output: Integration test results, performance data

## Workflow Integration

### VER Creates Report
1. Copy template from `.opencode/skills/en50128-verification/report-templates/`
2. Fill all sections with verification evidence
3. Submit to QUA for template compliance review (SIL 3-4 MANDATORY)

### QUA Reviews Template Compliance
1. Check document structure (12 sections + 4 appendices)
2. Check Document ID format
3. Check Document Control and Approvals tables
4. **1-pass rule:** Approve or reject with ONE resubmission
5. Create QA Template Compliance Review Report

### VMGR Reviews Technical Content (SIL 3-4)
1. Verify QUA approval obtained
2. Review verification methods and techniques
3. Review results and evidence
4. Review defects and resolutions
5. Approve or reject for gate transition

### COD Gate Check
1. Verify QUA template compliance approval
2. Verify VMGR technical approval (SIL 3-4)
3. Verify all defects resolved or justified
4. Authorize phase transition

## Cross-References

- **Phase Definitions:** `.opencode/skills/en50128-project-management/phase-definitions/phase-*.yaml`
- **VER Command:** `.opencode/commands/ver.md`
- **QUA Command:** `.opencode/commands/qua.md`
- **VMGR Command:** `.opencode/commands/vmgr.md`
- **COD Command:** `.opencode/commands/cod.md`
