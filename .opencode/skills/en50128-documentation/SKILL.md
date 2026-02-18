---
name: en50128-documentation
description: EN 50128 compliant documentation templates for all mandatory deliverables including SRS, SAS, SDS, and test plans
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  document-types: SRS, SAS, SDS, SQAP, SCMP
---

## What I do

I provide templates and guidelines for all mandatory EN 50128 documentation per Section 5:
- Software Requirements Specification (SRS)
- Software Architecture Specification (SAS)
- Software Design Specification (SDS)
- Software Quality Assurance Plan (SQAP)
- Software Configuration Management Plan (SCMP)
- Test plans and reports
- Verification and validation documentation

## When to use me

Use this skill when:
- Creating any EN 50128 mandatory document
- Reviewing document completeness
- Ensuring document consistency
- Preparing deliverable packages
- Supporting certification activities

## EN 50128 Documentation Requirements

**All documentation requirements are based on:**
- **EN 50128:2011 Annex C** - Document requirements table
- **Table A.2** - Requirements specification techniques
- **Table A.3** - Architecture and design techniques
- **Table A.4** - Implementation techniques
- **Table A.5** - Verification and testing techniques
- **Table A.6** - Integration techniques
- **Table A.7** - Validation techniques
- **Table A.8** - Software analysis techniques
- **Table A.9** - Quality assurance techniques (3 MANDATORY for ALL SILs)
- **Table A.21** - Test coverage requirements

**Standard Reference:** `std/EN50128-2011.md` Annex C, all technique tables

## Mandatory Documentation by Phase

### Phase 1: Planning
- [ ] Software Quality Assurance Plan (SQAP)
- [ ] Software Configuration Management Plan (SCMP)
- [ ] Software Verification Plan (SVP)
- [ ] Software Validation Plan (SVaP)

### Phase 2: Requirements
- [ ] Software Requirements Specification (SRS)
- [ ] Requirements Traceability Matrix
- [ ] Requirements Verification Report

### Phase 3: Design
- [ ] Software Architecture Specification (SAS)
- [ ] Software Design Specification (SDS)
- [ ] Interface Specifications
- [ ] Design Verification Report

### Phase 4: Implementation
- [ ] Source Code
- [ ] Unit Test Specifications
- [ ] Unit Test Reports
- [ ] Code Review Records

### Phase 5: Testing
- [ ] Integration Test Specification
- [ ] Integration Test Report
- [ ] System Test Specification
- [ ] System Test Report
- [ ] Coverage Reports

### Phase 6: Validation
- [ ] Validation Test Specification
- [ ] Validation Test Report
- [ ] Software Assessment Report

## Document Templates

All EN 50128 document templates are available in the `templates/` directory. Each template includes:
- Standard document header (Document ID, Version, Date, Author, Reviewer, Approver, SIL Level, Status)
- Document Control table (version history)
- Approvals table (signature section with SIL-specific requirements)
- EN 50128-compliant structure and content guidance

### Available Templates

| Template File | Document Type | EN 50128 Reference | Lifecycle Phase |
|---------------|---------------|-------------------|-----------------|
| **`DOCUMENT-HEADER-TEMPLATE.md`** | General header structure (mandatory for ALL documents) | Annex C | All phases |
| **`SQAP-template.md`** | Software Quality Assurance Plan | Section 6.5, Table A.9 | Phase 1 (Planning) |
| **`SCMP-template.md`** | Software Configuration Management Plan | Section 6.6, Table A.9 | Phase 1 (Planning) |
| **`SVP-template.md`** | Software Verification Plan | Section 6.2, Table A.5 | Phase 1 (Planning) |
| **`SVaP-template.md`** | Software Validation Plan | Section 7.7, Table A.7 | Phase 1 (Planning) |
| **`SRS-template.md`** | Software Requirements Specification | Section 7.2, Table A.2 | Phase 2 (Requirements) |
| **`SAS-template.md`** | Software Architecture Specification | Section 7.3, Table A.3 | Phase 3 (Architecture & Design) |
| **`SDS-template.md`** | Software Design Specification | Section 7.4, Table A.4 | Phase 3 (Architecture & Design) |

### Template Usage

1. **Always start with the general header template** (`DOCUMENT-HEADER-TEMPLATE.md`)
2. **Select the appropriate document-specific template** from the table above
3. **Follow the template structure exactly** - sections, tables, and required fields are all mandatory for EN 50128 compliance
4. **Fill in all fields** marked with `[placeholders]`
5. **Adjust SIL-specific sections** based on your target SIL level (0, 1, 2, 3, 4)
6. **Maintain traceability** - update Requirements Traceability Matrix (RTM) with every document change

### Template Compliance Verification

**Quality Assurance (QA)** and **Verification (VER)** roles SHALL verify template compliance during document reviews:

#### Template Compliance Checklist
- [ ] Standard header table present with all required fields (Document ID, Version, Date, Project, SIL Level, Author, Reviewer, Approver, Status)
- [ ] Document ID follows format: `DOC-<TYPE>-<YYYY>-<NNN>` (e.g., `DOC-SQAP-2026-001`)
- [ ] Version follows format: `MAJOR.MINOR` (0.1 for draft, 1.0 for first approved version)
- [ ] Document Control table present with version history
- [ ] Approvals table present with SIL-appropriate signature requirements
- [ ] All template sections present (no missing sections)
- [ ] Content follows template guidance (structure, format, required information)

**Non-compliance**: Documents that do not follow the template SHALL be marked as **Draft** status and returned to author for correction.

### SIL-Specific Template Requirements

| SIL Level | Approval Requirements | Additional Requirements |
|-----------|----------------------|-------------------------|
| **SIL 0-1** | Author + Reviewer + PM | Standard header, document control, approvals |
| **SIL 2** | Author + Reviewer + QA Manager + PM | Above + MISRA C compliance planning, static analysis planning |
| **SIL 3-4** | Author + Independent Reviewer + QA Manager + Safety Manager + PM + Customer (for SRS/SQAP) | Above + Independent verification/validation, traceability matrix (RTM) mandatory, enhanced safety analysis |

### Accessing Templates

**File Location**: `.opencode/skills/en50128-documentation/templates/`

**Reading Templates**:
```bash
# View general header template
cat .opencode/skills/en50128-documentation/templates/DOCUMENT-HEADER-TEMPLATE.md

# View SQAP template
cat .opencode/skills/en50128-documentation/templates/SQAP-template.md

# List all templates
ls -l .opencode/skills/en50128-documentation/templates/
```

**For detailed template descriptions**, see: `templates/README.md`

## Document Review Checklist

### General Quality
- [ ] Follows standard template
- [ ] All sections complete
- [ ] Version control maintained
- [ ] Approvals present
- [ ] References correct
- [ ] Acronyms defined

### Technical Content
- [ ] Accurate and complete
- [ ] SIL level stated
- [ ] Requirements traceable
- [ ] Consistent with related docs
- [ ] EN 50128 compliance demonstrated

### Safety Critical (SIL 3-4)
- [ ] Independent review performed
- [ ] Safety analysis included
- [ ] Hazards addressed
- [ ] Verification evidence provided

## References
- EN 50128:2011 Section 5 (Documentation)
- EN 50128:2011 Annex B (Document Guidelines)
- ISO/IEC 15289 (Documentation Management)
