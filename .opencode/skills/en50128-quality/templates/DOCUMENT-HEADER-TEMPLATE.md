# EN 50128 Document Header Template and Compliance Rules

**Version**: 2.0  
**Date**: 2026-03-10  
**Purpose**: Define mandatory header structure and documentation rules for ALL EN 50128 deliverables  
**Scope**: All project deliverables per EN 50128 Table C.1 (46 deliverables)

**Standard Reference**: EN 50128:2011 Section 5 (Documentation), Annex C (Document Control Summary)

---

## 1. INTRODUCTION

This document establishes the **mandatory** documentation standards for all EN 50128 deliverables. These rules ensure:
- **Traceability**: Documents can be uniquely identified and tracked
- **Configuration Management**: Version control and change management
- **Quality Assurance**: Consistent format for review and approval
- **Compliance**: Meeting EN 50128 Annex C requirements
- **Independence**: Clear role separation for SIL 3-4 projects

**Compliance Level**: MANDATORY for ALL SIL levels (0, 1, 2, 3, 4)

---

## 2. MANDATORY DOCUMENT HEADER STRUCTURE

ALL EN 50128 documents **SHALL** include the following header sections in this order:

### 2.1 Document Title and Metadata

```markdown
# [Document Full Name]

**TEMPLATE VERSION**: [X.Y]  
**REFERENCE**: EN 50128:2011 Section [X.Y], Table [A.N]

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | [DOC-XXX-YYYY-NNN] |
| **Version** | [X.Y] |
| **Date** | [YYYY-MM-DD] |
| **Project** | [Project Name] |
| **SIL Level** | [0, 1, 2, 3, or 4] |
| **Author** | [Name], [Role] |
| **Reviewer** | [Name], [Role] |
| **Approver** | [Name], [Role] |
| **Status** | [Draft \| Review \| Approved \| Baseline] |
```

**Rules**:
- Document title **MUST** match EN 50128 Table C.1 name
- All fields **MUST** be completed (no empty/placeholder values in final documents)
- Template version **SHOULD** be included for template tracking
- EN 50128 reference **MUST** cite applicable standard section(s)

### 2.2 Document Control Table

```markdown
## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft | - |
| 0.2 | YYYY-MM-DD | [Name] | Review comments addressed | - |
| 1.0 | YYYY-MM-DD | [Name] | First approved version | [Approver Name] |
```

**Rules**:
- **MUST** include complete version history from 0.1 onwards
- **MUST** document all changes (what changed, not why)
- **MUST** show approval signature for baseline versions
- **SHALL** be updated with every document revision

### 2.3 Approvals Table

```markdown
## APPROVALS

**SIL 0-2 Requirements**: [List roles]  
**SIL 3-4 Requirements**: [List roles including independent roles]

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author** | [Name] | | YYYY-MM-DD |
| **Technical Reviewer** | [Name] | | YYYY-MM-DD |
| **QA Manager** | [Name] | | YYYY-MM-DD |
| **Safety Manager** (SIL 2+) | [Name] | | YYYY-MM-DD |
| **Project Manager** | [Name] | | YYYY-MM-DD |
| **Independent Verifier** (SIL 3-4) | [Name] | | YYYY-MM-DD |
| **Independent Validator** (SIL 3-4) | [Name] | | YYYY-MM-DD |
| **Assessor** (SIL 3-4) | [Name] | | YYYY-MM-DD |
```

**Rules**:
- **MUST** list all required approvers per SIL level
- **MUST** follow EN 50128 Table C.1 "Written by" / "1st check" / "2nd check" roles
- **MUST** include date for each signature
- **SIL 3-4**: Independent roles (VER, VAL, ASR) **MANDATORY**

---

## 3. DOCUMENT ID FORMAT

### 3.1 Standard Format

**Format**: `DOC-<TYPE>-<YYYY>-<NNN>`

**Components**:
- `DOC` = Document prefix (constant)
- `<TYPE>` = Document type code (3-5 uppercase letters)
- `<YYYY>` = Year (4 digits)
- `<NNN>` = Sequential number (3 digits, zero-padded)

**Examples**:
- `DOC-SRS-2026-001` = Software Requirements Specification #1 in 2026
- `DOC-SQAP-2026-001` = Software Quality Assurance Plan #1 in 2026

### 3.2 Document Type Codes (EN 50128 Table C.1)

| Type Code | Document Name | Table C.1 # |
|-----------|---------------|-------------|
| **SQAP** | Software Quality Assurance Plan | DOC-001 |
| **SQAP-VER** | Software Quality Assurance Verification Report | DOC-002 |
| **SCMP** | Software Configuration Management Plan | DOC-003 |
| **SVP** | Software Verification Plan | DOC-004 |
| **SVAP** | Software Validation Plan | DOC-005 |
| **SRS** | Software Requirements Specification | DOC-006 |
| **OSTS** | Overall Software Test Specification | DOC-007 |
| **SRS-VER** | Software Requirements Verification Report | DOC-008 |
| **SAS** | Software Architecture Specification | DOC-009 |
| **SDS** | Software Design Specification | DOC-010 |
| **SIS** | Software Interface Specifications | DOC-011 |
| **SITS** | Software Integration Test Specification | DOC-012 |
| **HWSITS** | Hardware/Software Integration Test Specification | DOC-013 |
| **SAD-VER** | Software Architecture and Design Verification Report | DOC-014 |
| **SCDS** | Software Component Design Specification | DOC-015 |
| **SCTS** | Software Component Test Specification | DOC-016 |
| **SCD-VER** | Software Component Design Verification Report | DOC-017 |
| **SRC** | Software Source Code and Supporting Documentation | DOC-018 |
| **SRC-VER** | Software Source Code Verification Report | DOC-019 |
| **SCTR** | Software Component Test Report | DOC-020 |
| **SITR** | Software Integration Test Report | DOC-021 |
| **HWSITR** | Hardware/Software Integration Test Report | DOC-022 |
| **SI-VER** | Software Integration Verification Report | DOC-023 |
| **OSTR** | Overall Software Test Report | DOC-024 |
| **SVAL** | Software Validation Report | DOC-025 |
| **TOOLS-VAL** | Tools Validation Report | DOC-026 |
| **ARS** | Application Requirements Specification | DOC-028 |
| **APP** | Application Preparation Plan | DOC-029 |
| **ATS** | Application Test Specification | DOC-030 |
| **AAD** | Application Architecture and Design | DOC-031 |
| **APP-VER** | Application Preparation Verification Report | DOC-032 |
| **ATR** | Application Test Report | DOC-033 |
| **ADA** | Source Code of Application Data/Algorithms | DOC-034 |
| **ADA-VER** | Application Data/Algorithms Verification Report | DOC-035 |
| **DEPLOY-PLAN** | Software Release and Deployment Plan | DOC-036 |
| **DEPLOY-MAN** | Software Deployment Manual | DOC-037 |
| **REL-NOTES** | Release Notes | DOC-038 |
| **DEPLOY-REC** | Deployment Records | DOC-039 |
| **DEPLOY-VER** | Deployment Verification Report | DOC-040 |
| **MAINT-PLAN** | Software Maintenance Plan | DOC-041 |
| **CHANGE-REC** | Software Change Records | DOC-042 |
| **MAINT-REC** | Software Maintenance Records | DOC-043 |
| **MAINT-VER** | Software Maintenance Verification Report | DOC-044 |
| **SAP** | Software Assessment Plan | DOC-045 |
| **SAR** | Software Assessment Report | DOC-046 |

**NOTE**: Deliverable #27 does not exist in EN 50128 Table C.1 (table jumps from 26 to 28).

### 3.3 Document ID Rules

**MUST**:
- Use exact type codes from the table above
- Use 4-digit year (current year)
- Use 3-digit zero-padded sequential number
- Be unique across the entire project
- Never reuse Document IDs (even for obsolete documents)

**SHOULD**:
- Start sequential numbering at 001 for each project
- Increment sequentially within each document type

---

## 4. VERSION NUMBERING

### 4.1 Format

**Format**: `MAJOR.MINOR`

**Examples**: `0.1`, `0.2`, `1.0`, `1.1`, `2.0`

### 4.2 Versioning Rules

**MAJOR version** (X.0):
- **MUST** increment for approved/baseline releases
- First approved version = 1.0
- Second approved version = 2.0
- **MUST** increment when document status changes to "Approved" or "Baseline"

**MINOR version** (X.Y):
- **MUST** increment for draft revisions
- Initial draft = 0.1
- Second draft = 0.2
- Minor corrections to approved document = 1.1, 1.2, etc.
- **SHALL NOT** exceed .9 (use major version increment instead)

**Version History**:
- **MUST** maintain complete version history in Document Control table
- **MUST** document what changed in each version
- **SHALL** include approval signature for baseline versions (X.0)

---

## 5. DOCUMENT STATUS VALUES

| Status | Description | Use When | Approval Required |
|--------|-------------|----------|-------------------|
| **Draft** | Document under development | Initial creation, major revisions | No |
| **Review** | Document under review | Submitted for peer/QA/technical review | No |
| **Approved** | Document approved for use | Passed all reviews and approvals | Yes |
| **Baseline** | Document under configuration control | Included in project baseline, versioned | Yes |
| **Obsolete** | Document no longer valid | Superseded by newer version | N/A |

**Status Transition Rules**:
- Draft → Review: Submitted by Author
- Review → Approved: All required reviews complete per SIL level
- Approved → Baseline: Entered into configuration management
- Baseline → Obsolete: New baseline version released

**MANDATORY**: Document status **MUST** match approval state. Documents SHALL NOT be marked "Approved" without all required signatures.

---

## 6. SIL-SPECIFIC APPROVAL REQUIREMENTS

### 6.1 Approval Signatures per SIL Level

**SIL 0**:
- Author: REQUIRED
- Reviewer: RECOMMENDED
- QA Manager: RECOMMENDED

**SIL 1**:
- Author: REQUIRED
- Technical Reviewer: REQUIRED
- QA Manager: RECOMMENDED
- Project Manager: REQUIRED

**SIL 2**:
- Author: REQUIRED
- Technical Reviewer: REQUIRED
- QA Manager: REQUIRED
- Safety Manager: RECOMMENDED (for safety-critical documents)
- Project Manager: REQUIRED

**SIL 3-4**:
- Author: REQUIRED
- Technical Reviewer: REQUIRED (**independent** if document is VER/VAL deliverable)
- QA Manager: REQUIRED
- Safety Manager: REQUIRED
- Independent Verifier: REQUIRED (for verification deliverables)
- Independent Validator: REQUIRED (for validation deliverables)
- Independent Assessor: REQUIRED (for assessment deliverables)
- Project Manager: REQUIRED (except VAL/ASR reports - they report to safety authority)

### 6.2 Independence Requirements (SIL 3-4)

**EN 50128 Section 5.1.2.6-5.1.2.7**: Independence MANDATORY for:
- **Verifier (VER)**: Writes verification reports (DOC-008, DOC-012, DOC-014, DOC-017, DOC-019, DOC-023, DOC-040, DOC-044)
- **Validator (VAL)**: Writes validation reports (DOC-025, DOC-026)
- **Assessor (ASR)**: Writes assessment reports (DOC-045, DOC-046)

**Independence Criteria**:
- NOT part of development team (REQ, DES, IMP, INT, TST)
- NOT reporting to Project Manager
- NO financial interest in project success
- Separate organizational reporting structure

---

## 7. DATE FORMAT

**Format**: `YYYY-MM-DD` (ISO 8601)

**Examples**:
- ✅ `2026-03-10`
- ❌ `03/10/2026` (incorrect)
- ❌ `10-Mar-2026` (incorrect)

**Rules**:
- **MUST** use ISO 8601 format throughout document
- **MUST** use for all date fields (header, Document Control, Approvals)
- **SHOULD** use UTC timezone or explicitly state timezone if not UTC

---

## 8. MANDATORY DOCUMENT SECTIONS

### 8.1 All Documents MUST Include

1. **Document Title and Metadata** (Section 2.1)
2. **Document Control Table** (Section 2.2)
3. **Approvals Table** (Section 2.3)
4. **Table of Contents** (for documents > 3 pages)
5. **Introduction** (Purpose, Scope, Definitions)
6. **EN 50128 References** (applicable sections and tables)
7. **Content Sections** (per document type requirements)
8. **Traceability** (for requirements, design, test documents)

### 8.2 SIL 3-4 Documents MUST Also Include

- **Independence Statement** (for VER/VAL/ASR documents)
- **Technique Selection Justification** (per Annex A tables)
- **Complete Traceability Matrix** (bidirectional for requirements)
- **Safety Analysis** (FMEA/FTA references where applicable)
- **Tool Qualification** (if automated tools used)

---

## 9. TEMPLATE COMPLIANCE VALIDATION RULES

### 9.1 Mandatory Checks (QA/VER SHALL Verify)

**Header Compliance**:
- [ ] Document ID follows `DOC-<TYPE>-<YYYY>-<NNN>` format exactly
- [ ] Document type code matches Table C.1 deliverable
- [ ] Version number follows `MAJOR.MINOR` format
- [ ] Date format is `YYYY-MM-DD` (ISO 8601)
- [ ] SIL level explicitly stated (0, 1, 2, 3, or 4)
- [ ] All mandatory header fields completed (no empty cells)
- [ ] Status matches approval state

**Document Control**:
- [ ] Document Control table present
- [ ] Complete version history from 0.1
- [ ] All changes documented
- [ ] Approval signatures for baseline versions

**Approvals**:
- [ ] Approvals table present
- [ ] All required approvers listed per SIL level
- [ ] Dates provided for all signatures
- [ ] Independence requirements met (SIL 3-4)
- [ ] Roles match EN 50128 Table C.1 (Written by / 1st check / 2nd check)

**Content**:
- [ ] Table of Contents present (if > 3 pages)
- [ ] Introduction section present
- [ ] EN 50128 references cited
- [ ] SIL-specific requirements addressed

### 9.2 Automated Validation Checks

The following checks **SHOULD** be automated using the validation tool (`tools/documentation/doc_validator.py`):

1. **Document ID format** (regex validation)
2. **Version number format** (regex validation)
3. **Date format** (ISO 8601 validation)
4. **Header table presence** (markdown table parsing)
5. **Required sections presence** (markdown header parsing)
6. **Document Control table presence**
7. **Approvals table presence**
8. **SIL level value** (0, 1, 2, 3, 4)
9. **Status value** (Draft, Review, Approved, Baseline, Obsolete)

### 9.3 Manual Validation Checks

The following checks **MUST** be performed manually by QA/VER:

1. **Content accuracy** (technical correctness)
2. **Completeness** (all required content present per document type)
3. **Traceability** (requirements traced to design, tests, etc.)
4. **Consistency** (no contradictions within document or with other documents)
5. **EN 50128 compliance** (techniques applied per Annex A tables)
6. **Independence verification** (SIL 3-4: verify independent roles)

---

## 10. NON-COMPLIANCE ACTIONS

### 10.1 Template Non-Compliance

**IF** a document does NOT follow this header template:
- QA/VER **SHALL REJECT** the document
- Document status **SHALL** be marked as "Draft"
- Document **SHALL NOT** proceed to approval until template compliance achieved

### 10.2 Approval Non-Compliance

**IF** a document lacks required approvals per SIL level:
- Document **SHALL NOT** be marked "Approved" or "Baseline"
- Missing approvals **SHALL** be identified and obtained
- Document **SHALL** remain in "Review" status

### 10.3 Version Control Non-Compliance

**IF** version numbering does not follow rules:
- Document **SHALL** be corrected immediately
- Version history **SHALL** be reconstructed if needed
- Configuration Management **SHALL** be notified

---

## 11. TOOL SUPPORT

### 11.1 Validation Tool

**Location**: `tools/documentation/doc_validator.py`

**Usage**:
```bash
# Validate single document
python3 tools/documentation/doc_validator.py path/to/document.md

# Validate all templates
python3 tools/documentation/doc_validator.py --validate-all-templates

# Generate validation report
python3 tools/documentation/doc_validator.py --report output.json
```

**Features**:
- Automated header structure validation
- Document ID format checking
- Version number validation
- Date format validation
- Required section presence checking
- SIL-specific requirement validation
- JSON/Markdown report generation

### 11.2 Template Generator

**Location**: `tools/documentation/template_generator.py`

**Usage**:
```bash
# Generate new document from template
python3 tools/documentation/template_generator.py --type SRS --project "MyProject" --sil 3
```

---

## 12. REFERENCES

### 12.1 EN 50128 References

- **Section 5**: Software Development Process
- **Section 5.3.2.7-5.3.2.10**: Readability requirements
- **Section 6.5.4.14-6.5.4.17**: Traceability requirements
- **Annex C**: Document Control Summary (Table C.1)
- **Table C.1**: Document list with "Written by" / "1st check" / "2nd check" roles

### 12.2 Related Standards

- **ISO/IEC 15289:2015**: Systems and software engineering - Content of life-cycle information items
- **IEEE Std 730-2014**: Software Quality Assurance Processes
- **ISO 8601**: Date and time format
- **IEEE 829-2008**: Software Test Documentation

---

## 13. REVISION HISTORY

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2024-01-01 | Platform Team | Initial version |
| 2.0 | 2026-03-10 | Platform Team | Major update: Added all 46 deliverable type codes, SIL-specific rules, validation rules, tool support |

---

**END OF DOCUMENT**
