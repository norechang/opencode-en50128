# Verification Report Templates - Index

This directory contains EN 50128 compliant verification report templates for all lifecycle phases.

## Template Structure

All verification report templates follow this standard structure:

1. **Header** - Document ID, Type, Phase, EN 50128 Reference
2. **Document Control** - Version history, configuration item, baseline
3. **Approvals** - VER, QUA, VMGR/PM signatures with independence declaration
4. **Executive Summary** - Project, SIL, scope, overall result
5. **Introduction** - Purpose, scope, references, verification team
6. **Verification Methodology** - Techniques (Table A.5), activities, tools
7. **Verification Criteria** - Phase-specific criteria from phase definitions
8. **Verification Results** - Detailed results per criterion with evidence
9. **Defects and Issues** - Critical/Major/Minor defects, observations
10. **Traceability Analysis** - Traceability metrics and issues
11. **EN 50128 Compliance** - Table A.x techniques, independence requirements
12. **Metrics** - Phase-specific quality metrics
13. **Recommendations** - Mandatory actions, suggested improvements
14. **Conclusion** - Overall assessment, conditions for approval, verifier statement
15. **Appendices** - Checklist, traceability matrix, defect details, tool output

## Available Templates

### Phase 2: Requirements Specification
- **Software-Requirements-Verification-Report.md**
  - Verifies: SRS, Hazard Log, Overall Software Test Specification
  - EN 50128 Reference: Annex C #8, Section 7.2
  - Doc ID: DOC-REQVER-YYYY-NNN

### Phase 3: Architecture and Design
- **Software-Architecture-Design-Verification-Report.md**
  - Verifies: SAS, SDS, Software Interface Specifications, Integration Test Specifications
  - EN 50128 Reference: Annex C #14, Section 7.3
  - Doc ID: DOC-DESVER-YYYY-NNN

### Phase 4: Component Design
- **Software-Component-Design-Verification-Report.md**
  - Verifies: Software Component Design Specification, Software Component Test Specification
  - EN 50128 Reference: Annex C #17, Section 7.4
  - Doc ID: DOC-COMPVER-YYYY-NNN

### Phase 5: Implementation and Testing
- **Software-Source-Code-Verification-Report.md**
  - Verifies: Software Source Code, Software Component Test Report
  - EN 50128 Reference: Annex C #20, Section 7.5
  - Doc ID: DOC-IMPVER-YYYY-NNN
  - **Special Requirements:**
    - MISRA C:2012 compliance (zero mandatory violations SIL 2+)
    - Static analysis (PC-lint, Cppcheck, Clang)
    - Complexity analysis (≤10 SIL 3-4)
    - Coverage analysis (100% statement/branch/MC-DC SIL 3-4)

### Phase 6: Integration
- **Software-Integration-Verification-Report.md**
  - Verifies: Software Integration Test Report, Software/Hardware Integration Test Report
  - EN 50128 Reference: Annex C #23, Section 7.6
  - Doc ID: DOC-INTVER-YYYY-NNN

## Usage Instructions

### For VER Agent

1. **Select Template** - Choose template matching current phase
2. **Copy Template** - Copy template to project `docs/reports/` directory
3. **Update Header** - Fill in document ID, date, project name
4. **Fill Document Control** - Add version, author, reviewer, approver
5. **Complete Approvals** - Add verifier name, obtain signatures (QUA → VMGR for SIL 3-4)
6. **Execute Verification** - Perform verification activities per template sections
7. **Document Results** - Fill all verification results sections with evidence
8. **Record Defects** - Document all defects and issues found
9. **Calculate Metrics** - Compute and record all metrics
10. **Write Conclusion** - Provide overall assessment and verifier statement
11. **Submit to QUA** - Submit for template compliance review (SIL 3-4 MANDATORY)
12. **Submit to VMGR** - After QUA approval, submit for technical review (SIL 3-4)

### For QUA Agent

When reviewing verification reports for template compliance:

1. **Check Document ID** - Format DOC-[TYPE]VER-YYYY-NNN
2. **Check Document Control** - Version table complete
3. **Check Approvals** - All required signatures present
4. **Check Section Structure** - All 12 main sections + 4 appendices present
5. **Check Independence** - Independence declaration present (SIL 3-4)
6. **Check Traceability** - Traceability section complete
7. **Check EN 50128 Compliance** - Table A.5 techniques documented
8. **Check Metrics** - Metrics section complete with targets/actuals

### For VMGR (SIL 3-4)

When reviewing verification reports for technical adequacy:

1. **Verify QUA Approval** - Ensure QUA template review passed
2. **Review Verification Methods** - Ensure appropriate techniques applied
3. **Review Results** - Verify all criteria checked with evidence
4. **Review Defects** - Assess criticality and resolution status
5. **Review Traceability** - Verify 100% traceability achieved
6. **Review Metrics** - Verify metrics meet SIL requirements
7. **Approve/Reject** - Provide final technical approval or request corrections

## SIL-Specific Requirements

### SIL 0-1
- QUA template review: **Optional**
- VMGR technical review: **Not required** (PM approval sufficient)
- Independence: **Not required**

### SIL 2
- QUA template review: **Recommended**
- VMGR technical review: **Not required** (PM approval sufficient)
- Independence: **Recommended**

### SIL 3-4
- QUA template review: **MANDATORY**
- VMGR technical review: **MANDATORY**
- Independence: **MANDATORY** (VER must be independent from development)

## EN 50128 References

- **Section 6.2** - Verification
- **Section 7.x** - Phase-specific requirements
- **Table A.5** - Verification and Testing techniques
- **Annex C** - Document control summary

## Template Maintenance

**Owner:** en50128-verification skill  
**Last Updated:** 2026-02-21  
**Version:** 1.0

When updating templates:
1. Update this INDEX.md with changes
2. Update version number in template header
3. Document rationale for changes
4. Obtain QUA review of template changes
