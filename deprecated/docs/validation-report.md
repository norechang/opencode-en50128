# EN 50128 Document Template Validation Report

**Date**: 2026-03-10

**Total Files**: 35
**Passed**: 12
**Failed**: 23

## Summary

| File | Status | Critical | Errors | Warnings | Info |
|------|--------|----------|--------|----------|------|
| Change-Request-template.md | ❌ FAIL | 4 | 1 | 1 | 2 |
| Configuration-Audit-Report-template.md | ❌ FAIL | 2 | 1 | 2 | 2 |
| Software-Architecture-Specification-template.md | ✅ PASS | 0 | 0 | 0 | 1 |
| Software-Architecture-and-Design-Verification-Report-template.md | ❌ FAIL | 2 | 0 | 1 | 2 |
| Software-Design-Specification-template.md | ✅ PASS | 0 | 0 | 0 | 1 |
| Software-Interface-Specifications-template.md | ❌ FAIL | 2 | 0 | 2 | 2 |
| Software-Configuration-Management-Plan-template.md | ✅ PASS | 0 | 0 | 0 | 1 |
| Software-Quality-Assurance-Plan-template.md | ❌ FAIL | 2 | 0 | 2 | 2 |
| Software-Validation-Plan-template.md | ✅ PASS | 0 | 0 | 0 | 1 |
| Software-Verification-Plan-template.md | ✅ PASS | 0 | 0 | 0 | 1 |
| Software-Source-Code-Verification-Report-template.md | ❌ FAIL | 2 | 0 | 1 | 2 |
| Hardware-Software-Integration-Test-Report-template.md | ❌ FAIL | 2 | 0 | 2 | 2 |
| Hardware-Software-Integration-Test-Specification-template.md | ❌ FAIL | 2 | 0 | 2 | 2 |
| Software-Integration-Test-Report-template.md | ❌ FAIL | 2 | 0 | 2 | 2 |
| Software-Integration-Test-Specification-template.md | ❌ FAIL | 2 | 0 | 2 | 2 |
| Software-Integration-Verification-Report-template.md | ❌ FAIL | 2 | 0 | 1 | 2 |
| project-state-template.md | ❌ FAIL | 6 | 0 | 1 | 1 |
| Gate-Check-Report-template.md | ❌ FAIL | 4 | 2 | 1 | 2 |
| LIFECYCLE_STATE-template.md | ❌ FAIL | 6 | 0 | 1 | 2 |
| Project-Plan-template.md | ❌ FAIL | 2 | 1 | 2 | 2 |
| Risk-Register-template.md | ❌ FAIL | 4 | 1 | 1 | 2 |
| Status-Report-template.md | ❌ FAIL | 6 | 0 | 1 | 2 |
| Code-Review-Checklist-template.md | ❌ FAIL | 4 | 1 | 1 | 2 |
| QA-Review-Report-template.md | ❌ FAIL | 2 | 1 | 2 | 2 |
| Software-Requirements-Specification-template.md | ✅ PASS | 0 | 0 | 0 | 1 |
| Software-Requirements-Verification-Report-template.md | ❌ FAIL | 2 | 0 | 1 | 2 |
| FMEA-template.md | ✅ PASS | 0 | 0 | 1 | 2 |
| FTA-template.md | ✅ PASS | 0 | 0 | 1 | 2 |
| Hazard-Log-template.md | ✅ PASS | 0 | 0 | 2 | 2 |
| Safety-Case-template.md | ✅ PASS | 0 | 0 | 1 | 2 |
| Component-Test-Report-template.md | ✅ PASS | 0 | 0 | 2 | 2 |
| Component-Test-Specification-template.md | ✅ PASS | 0 | 0 | 2 | 2 |
| Overall-Software-Test-Report-template.md | ❌ FAIL | 2 | 0 | 2 | 2 |
| Overall-Software-Test-Specification-template.md | ❌ FAIL | 2 | 0 | 2 | 2 |
| Release-Note-template.md | ❌ FAIL | 2 | 1 | 2 | 2 |

## Detailed Findings

### Change-Request-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[ERROR]** CONTROL-002: Column 'Changes' not found in DOCUMENT CONTROL table
  - Suggestion: Add column: | Changes | ... |
- **[CRITICAL]** APPROVAL-001: APPROVALS section not found
  - Suggestion: Add: ## APPROVALS section with signature table
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[CRITICAL]** SECTION-001: Required section 'APPROVALS' not found
  - Suggestion: Add: ## APPROVALS
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Configuration-Audit-Report-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[ERROR]** CONTROL-002: Column 'Changes' not found in DOCUMENT CONTROL table
  - Suggestion: Add column: | Changes | ... |
- **[WARNING]** APPROVAL-002: SIL-specific approval requirements not documented
  - Suggestion: Add: **SIL X-Y Requirements**: [List roles]
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Software-Architecture-Specification-template.md

- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Software-Architecture-and-Design-Verification-Report-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Software-Design-Specification-template.md

- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Software-Interface-Specifications-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[WARNING]** APPROVAL-002: SIL-specific approval requirements not documented
  - Suggestion: Add: **SIL X-Y Requirements**: [List roles]
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Software-Configuration-Management-Plan-template.md

- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Software-Quality-Assurance-Plan-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[WARNING]** APPROVAL-002: SIL-specific approval requirements not documented
  - Suggestion: Add: **SIL X-Y Requirements**: [List roles]
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Software-Validation-Plan-template.md

- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Software-Verification-Plan-template.md

- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Software-Source-Code-Verification-Report-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Hardware-Software-Integration-Test-Report-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[WARNING]** APPROVAL-002: SIL-specific approval requirements not documented
  - Suggestion: Add: **SIL X-Y Requirements**: [List roles]
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Hardware-Software-Integration-Test-Specification-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[WARNING]** APPROVAL-002: SIL-specific approval requirements not documented
  - Suggestion: Add: **SIL X-Y Requirements**: [List roles]
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Software-Integration-Test-Report-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[WARNING]** APPROVAL-002: SIL-specific approval requirements not documented
  - Suggestion: Add: **SIL X-Y Requirements**: [List roles]
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Software-Integration-Test-Specification-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[WARNING]** APPROVAL-002: SIL-specific approval requirements not documented
  - Suggestion: Add: **SIL X-Y Requirements**: [List roles]
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Software-Integration-Verification-Report-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### project-state-template.md

- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[CRITICAL]** CONTROL-001: DOCUMENT CONTROL section not found
  - Suggestion: Add: ## DOCUMENT CONTROL section with version history table
- **[CRITICAL]** APPROVAL-001: APPROVALS section not found
  - Suggestion: Add: ## APPROVALS section with signature table
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[CRITICAL]** SECTION-001: Required section 'DOCUMENT CONTROL' not found
  - Suggestion: Add: ## DOCUMENT CONTROL
- **[CRITICAL]** SECTION-001: Required section 'APPROVALS' not found
  - Suggestion: Add: ## APPROVALS
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Gate-Check-Report-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[ERROR]** HEADER-003: Required field 'Reviewer' not found in STANDARD HEADER table
  - Suggestion: Add row: | **Reviewer** | [Value] |
- **[ERROR]** HEADER-003: Required field 'Approver' not found in STANDARD HEADER table
  - Suggestion: Add row: | **Approver** | [Value] |
- **[CRITICAL]** CONTROL-001: DOCUMENT CONTROL section not found
  - Suggestion: Add: ## DOCUMENT CONTROL section with version history table
- **[CRITICAL]** APPROVAL-001: APPROVALS section not found
  - Suggestion: Add: ## APPROVALS section with signature table
- **[CRITICAL]** SECTION-001: Required section 'DOCUMENT CONTROL' not found
  - Suggestion: Add: ## DOCUMENT CONTROL
- **[CRITICAL]** SECTION-001: Required section 'APPROVALS' not found
  - Suggestion: Add: ## APPROVALS
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### LIFECYCLE_STATE-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[CRITICAL]** CONTROL-001: DOCUMENT CONTROL section not found
  - Suggestion: Add: ## DOCUMENT CONTROL section with version history table
- **[CRITICAL]** APPROVAL-001: APPROVALS section not found
  - Suggestion: Add: ## APPROVALS section with signature table
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[CRITICAL]** SECTION-001: Required section 'DOCUMENT CONTROL' not found
  - Suggestion: Add: ## DOCUMENT CONTROL
- **[CRITICAL]** SECTION-001: Required section 'APPROVALS' not found
  - Suggestion: Add: ## APPROVALS
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Project-Plan-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[ERROR]** CONTROL-002: Column 'Changes' not found in DOCUMENT CONTROL table
  - Suggestion: Add column: | Changes | ... |
- **[WARNING]** APPROVAL-002: SIL-specific approval requirements not documented
  - Suggestion: Add: **SIL X-Y Requirements**: [List roles]
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Risk-Register-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[ERROR]** CONTROL-002: Column 'Changes' not found in DOCUMENT CONTROL table
  - Suggestion: Add column: | Changes | ... |
- **[CRITICAL]** APPROVAL-001: APPROVALS section not found
  - Suggestion: Add: ## APPROVALS section with signature table
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[CRITICAL]** SECTION-001: Required section 'APPROVALS' not found
  - Suggestion: Add: ## APPROVALS
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Status-Report-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[CRITICAL]** CONTROL-001: DOCUMENT CONTROL section not found
  - Suggestion: Add: ## DOCUMENT CONTROL section with version history table
- **[CRITICAL]** APPROVAL-001: APPROVALS section not found
  - Suggestion: Add: ## APPROVALS section with signature table
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[CRITICAL]** SECTION-001: Required section 'DOCUMENT CONTROL' not found
  - Suggestion: Add: ## DOCUMENT CONTROL
- **[CRITICAL]** SECTION-001: Required section 'APPROVALS' not found
  - Suggestion: Add: ## APPROVALS
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Code-Review-Checklist-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[ERROR]** CONTROL-002: Column 'Changes' not found in DOCUMENT CONTROL table
  - Suggestion: Add column: | Changes | ... |
- **[CRITICAL]** APPROVAL-001: APPROVALS section not found
  - Suggestion: Add: ## APPROVALS section with signature table
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[CRITICAL]** SECTION-001: Required section 'APPROVALS' not found
  - Suggestion: Add: ## APPROVALS
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### QA-Review-Report-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[ERROR]** CONTROL-002: Column 'Changes' not found in DOCUMENT CONTROL table
  - Suggestion: Add column: | Changes | ... |
- **[WARNING]** APPROVAL-002: SIL-specific approval requirements not documented
  - Suggestion: Add: **SIL X-Y Requirements**: [List roles]
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Software-Requirements-Specification-template.md

- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Software-Requirements-Verification-Report-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### FMEA-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### FTA-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Hazard-Log-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-003: EN 50128 reference not found in REFERENCE field
  - Suggestion: Include: EN 50128:2011 Section X.Y
- **[WARNING]** APPROVAL-002: SIL-specific approval requirements not documented
  - Suggestion: Add: **SIL X-Y Requirements**: [List roles]
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Safety-Case-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Component-Test-Report-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[WARNING]** APPROVAL-002: SIL-specific approval requirements not documented
  - Suggestion: Add: **SIL X-Y Requirements**: [List roles]
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Component-Test-Specification-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[WARNING]** APPROVAL-002: SIL-specific approval requirements not documented
  - Suggestion: Add: **SIL X-Y Requirements**: [List roles]
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Overall-Software-Test-Report-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[WARNING]** APPROVAL-002: SIL-specific approval requirements not documented
  - Suggestion: Add: **SIL X-Y Requirements**: [List roles]
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Overall-Software-Test-Specification-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[WARNING]** APPROVAL-002: SIL-specific approval requirements not documented
  - Suggestion: Add: **SIL X-Y Requirements**: [List roles]
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

### Release-Note-template.md

- **[INFO]** META-002: Template version not found
  - Suggestion: Add: **TEMPLATE VERSION**: X.Y at top of document
- **[WARNING]** META-004: REFERENCE field not found
  - Suggestion: Add: **REFERENCE**: EN 50128:2011 Section X.Y
- **[CRITICAL]** HEADER-001: STANDARD HEADER section not found
  - Suggestion: Add: ## STANDARD HEADER section with table
- **[ERROR]** CONTROL-002: Column 'Changes' not found in DOCUMENT CONTROL table
  - Suggestion: Add column: | Changes | ... |
- **[WARNING]** APPROVAL-002: SIL-specific approval requirements not documented
  - Suggestion: Add: **SIL X-Y Requirements**: [List roles]
- **[CRITICAL]** SECTION-001: Required section 'STANDARD HEADER' not found
  - Suggestion: Add: ## STANDARD HEADER
- **[INFO]** TOC-001: Table of Contents not found (document appears to be long)
  - Suggestion: Add Table of Contents after APPROVALS section

