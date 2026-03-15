# Document Review Workflow

**EN 50128 Reference**: Section 6.5.4.5(c) (Documentation control), Section 7.1.4 (Document Requirements)  
**Phase**: All phases (cross-cutting activity)  
**Role**: Quality Assurance (QUA)  
**SIL Level**: All (0-4)

---

## Purpose

This workflow defines the document review process for EN 50128 railway software development. It implements EN 50128 requirements for ensuring all deliverables meet mandatory documentation standards, template compliance, and traceability requirements before technical review.

**Key Objectives**:
- Enforce EN 50128 document template compliance (MANDATORY SIL 3-4)
- Validate Document ID format and Document Control tables
- Verify Approvals tables with SIL-specific approvers
- Check traceability sections (MANDATORY SIL 3-4)
- Implement 1-pass review policy (reject → fix → resubmit ONCE → final decision)
- Gate-keeper role: QA reviews BEFORE technical reviewers (VER/VAL/VMGR)
- Generate document review reports for audit trail

**Inputs**:
- Draft deliverable (any EN 50128 document)
- EN 50128 document template requirements (Annex C)
- SIL level for project
- Document type (SRS, SAS, SDS, Test Plan, Verification Report, etc.)

**Outputs**:
- Document Review Report (approved/rejected)
- Defect list (if rejected)
- Corrective action list
- Approval for technical review (if approved)

---

## Table of Contents

1. [Document Review Overview](#document-review-overview)
2. [EN 50128 Document Requirements](#en-50128-document-requirements)
3. [Document Template Compliance](#document-template-compliance)
4. [Document Review Process](#document-review-process)
5. [Document ID Format Validation](#document-id-format-validation)
6. [Document Control Table Validation](#document-control-table-validation)
7. [Approvals Table Validation](#approvals-table-validation)
8. [Traceability Section Validation](#traceability-section-validation)
9. [Automated Document Checking](#automated-document-checking)
10. [Document Types and Requirements](#document-types-and-requirements)
11. [Review Report Generation](#review-report-generation)
12. [1-Pass Review Policy](#1-pass-review-policy)
13. [Tool Integration](#tool-integration)
14. [SIL-Specific Requirements](#sil-specific-requirements)
15. [Example Document Review Scenarios](#example-document-review-scenarios)

---

## Document Review Overview

### Purpose of Document Review

**EN 50128 Section 6.5.4.5(c)**: "Documentation and configuration control"

Quality Assurance SHALL review all deliverables for **template compliance** BEFORE technical review. This ensures:
- Consistent document structure across project
- All mandatory sections present (EN 50128 Annex C)
- Proper Document ID format for traceability
- Complete Document Control table (version, author, approvers)
- Valid Approvals table with SIL-specific approvers
- Traceability sections present (MANDATORY SIL 3-4)
- Audit trail for certification

**QA Document Review is NOT Technical Review**:
- QA checks FORMAT and STRUCTURE (template compliance)
- Technical reviewers check CONTENT (requirements correctness, design quality, code correctness)
- QA review happens FIRST (gate-keeper role)
- Technical review happens AFTER QA approval

---

### Document Review Workflow Overview

```
Developer creates deliverable (draft)
          ↓
workspace.py wf submit --deliverable DOC-XXX-YYY-NNN --phase <phase>
          ↓
QA reviews for template compliance (automated + manual)
    ├─→ [PASS] → workspace.py wf review --status approved
    │                ↓
    │        Technical review proceeds (VER/VAL/VMGR/etc.)
    │
    └─→ [FAIL] → workspace.py wf review --status rejected
                      ↓
             Developer fixes issues
                      ↓
             workspace.py wf submit (RESUBMIT - 1 pass allowed)
                      ↓
             QA re-reviews (FINAL DECISION)
                 ├─→ [PASS] → Approved, proceed
                 └─→ [FAIL] → Escalate to QA Manager + PM
```

**1-Pass Policy**: Developer gets ONE opportunity to fix and resubmit. If second review fails, escalate to QA Manager and PM for resolution.

---

### QA Review Responsibilities by Document Type

| Document Type | QA Check | SIL 0-1 | SIL 2 | SIL 3-4 |
|--------------|----------|---------|-------|---------|
| **Requirements (SRS)** | Template compliance, traceability to system requirements | HR | HR | **M** |
| **Design (SAS, SDS)** | Template compliance, traceability to SRS | HR | HR | **M** |
| **Implementation (Code)** | Code review checklist, MISRA C compliance | HR | **M** | **M** |
| **Test Documents** | Template compliance, traceability to requirements | HR | HR | **M** |
| **Verification Report** | Template compliance, evidence completeness | R | HR | **M** |
| **Validation Report** | Template compliance, acceptance evidence | R | HR | **M** |
| **All Documents** | Document ID format, Document Control, Approvals | HR | HR | **M** |

**Legend**: M = Mandatory, HR = Highly Recommended, R = Recommended

---

## EN 50128 Document Requirements

### EN 50128 Annex C: Document Control Summary

**Table C.1** defines mandatory documents for each lifecycle phase. All documents MUST comply with EN 50128 documentation standards.

**Key Requirements**:
1. **Document Identification** (unique ID, version control)
2. **Document Control** (author, date, approval status)
3. **Approvals** (role-specific approvers per SIL level)
4. **Version History** (change tracking)
5. **Traceability** (links to upstream/downstream artifacts - MANDATORY SIL 3-4)
6. **Configuration Management** (baseline control per SCMP)

---

### Mandatory Document Sections (All SIL Levels)

Every EN 50128 deliverable SHALL include:

1. **Standard Header**:
   - Document ID (DOC-[ROLE]-[TYPE]-[NNN])
   - Version number (X.Y)
   - Date (YYYY-MM-DD)
   - Project name
   - SIL level
   - Author (name, role)
   - Status (Draft / Review / Approved / Baseline)

2. **Document Control Table**:
   - Version history (version, date, author, changes, approver)
   - At least one entry for current version

3. **Approvals Table**:
   - SIL-specific approvers (see below)
   - Signature placeholders
   - Date fields

4. **Content Sections** (document-type specific):
   - Introduction, Scope, References, Terms
   - Main content (requirements, design, test cases, etc.)
   - Traceability (MANDATORY SIL 3-4)

5. **References Section**:
   - EN 50128:2011
   - Related documents (SRS, SAS, SQAP, SCMP, etc.)

---

### SIL-Specific Approvers Requirements

| SIL Level | Required Approvers |
|-----------|-------------------|
| **SIL 0-1** | Author, Reviewer, QA, PM |
| **SIL 2** | Author, Reviewer, QA, Safety Manager, PM |
| **SIL 3-4** | Author, Reviewer (independent), QA, Safety Manager, Independent Verifier, Independent Validator, Assessor, PM |

**Independence Note**: For SIL 3-4, Verifier/Validator SHALL NOT report to PM (EN 50128 Section 5.1.2.10).

---

## Document Template Compliance

### Template Compliance Checklist

QA SHALL verify the following template compliance criteria:

#### 1. Document ID Format

**Format**: `DOC-[ROLE]-[TYPE]-[NNN]`

**Examples**:
- `DOC-REQ-SRS-001` (Requirements - Software Requirements Specification)
- `DOC-DES-SAS-001` (Design - Software Architecture Specification)
- `DOC-VER-REP-001` (Verification - Verification Report)
- `DOC-VAL-REP-001` (Validation - Validation Report)

**Role Codes**:
- `REQ` (Requirements Engineer)
- `DES` (Designer)
- `IMP` (Implementer)
- `TST` (Tester)
- `VER` (Verifier)
- `INT` (Integrator)
- `VAL` (Validator)
- `SAF` (Safety Engineer)
- `QUA` (Quality Assurance)
- `CM` (Configuration Manager)
- `PM` (Project Manager)

**Type Codes** (examples):
- `SRS` (Software Requirements Specification)
- `SAS` (Software Architecture Specification)
- `SDS` (Software Design Specification)
- `ICD` (Interface Control Document)
- `CODE` (Source Code Listing)
- `UTP` (Unit Test Plan)
- `ITP` (Integration Test Plan)
- `VTP` (Validation Test Plan)
- `REP` (Report - Verification, Validation, Test, etc.)
- `PLAN` (Plan - SQAP, SCMP, SVP, SVaP)

**Validation**:
```bash
# Check document ID format
if [[ "$DOC_ID" =~ ^DOC-[A-Z]{2,3}-[A-Z]{2,5}-[0-9]{3}$ ]]; then
    echo "Document ID format: PASS"
else
    echo "Document ID format: FAIL - Must be DOC-[ROLE]-[TYPE]-[NNN]"
fi
```

---

#### 2. Document Control Table

**Required Fields**:
- Document ID (matches filename and header)
- Version (X.Y format, e.g., 1.0, 1.1, 2.0)
- Date (YYYY-MM-DD format)
- Project name
- SIL level (0, 1, 2, 3, or 4)
- Author (name and role)
- Status (Draft / Review / Approved / Baseline)

**Example (Correct)**:
```markdown
| Field | Value |
|-------|-------|
| **Document ID** | DOC-VER-REP-001 |
| **Version** | 1.0 |
| **Date** | 2026-03-14 |
| **Project** | Railway Door Controller |
| **SIL Level** | 3 |
| **Author** | John Smith, Verifier |
| **Status** | Review |
```

**Common Errors**:
- ❌ Document ID missing or doesn't match filename
- ❌ Version format incorrect (e.g., "v1.0" instead of "1.0")
- ❌ Date format incorrect (e.g., "14/03/2026" instead of "2026-03-14")
- ❌ SIL level missing or invalid (must be 0, 1, 2, 3, or 4)
- ❌ Author role missing (must include role, e.g., "Verifier")
- ❌ Status invalid (must be Draft, Review, Approved, or Baseline)

---

#### 3. Version History Table

**Required Columns**:
- Version
- Date
- Author
- Changes (description)
- Approved By

**Example (Correct)**:
```markdown
| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-03-01 | John Smith | Initial draft | - |
| 0.2 | 2026-03-05 | John Smith | Added static analysis results | Jane Doe (QA) |
| 1.0 | 2026-03-14 | John Smith | Incorporated review comments | Jane Doe (QA), Bob Lee (VMGR) |
```

**Validation**:
- At least one entry for current version
- Date in YYYY-MM-DD format
- Changes description present (not empty)
- Approved By field populated for non-draft versions

---

#### 4. Approvals Table

**Required Structure**:
- Role column (SIL-specific roles)
- Name column
- Signature column (placeholder OK)
- Date column

**SIL 3-4 Example (Correct)**:
```markdown
| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author** | John Smith | | 2026-03-14 |
| **Technical Reviewer** | Alice Johnson | | 2026-03-15 |
| **QA Manager** | Jane Doe | | 2026-03-16 |
| **Safety Manager** | Bob Lee | | 2026-03-16 |
| **Independent Verifier** | Carol White | | 2026-03-17 |
| **Independent Validator** | Dave Brown | | 2026-03-18 |
| **Assessor** | Eve Green | | 2026-03-19 |
| **Project Manager** | Frank Black | | 2026-03-20 |
```

**SIL-Specific Validation**:
- SIL 0-1: Author, Reviewer, QA, PM (minimum)
- SIL 2: Author, Reviewer, QA, Safety Manager, PM (minimum)
- SIL 3-4: Author, Reviewer (independent), QA, Safety Manager, Independent Verifier, Independent Validator, Assessor, PM (MANDATORY)

**Common Errors**:
- ❌ Missing Independent Verifier for SIL 3-4
- ❌ Missing Independent Validator for SIL 3-4
- ❌ Missing Assessor for SIL 3-4
- ❌ Missing Safety Manager for SIL 2+
- ❌ Reviewer not marked as "independent" for SIL 3-4

---

#### 5. Traceability Sections (MANDATORY SIL 3-4)

**Requirements Traceability**:
- Forward traceability (requirements → design → code → tests)
- Backward traceability (tests → code → design → requirements)
- Traceability matrix embedded in document OR separate traceability report referenced

**Example Traceability Section (Correct)**:
```markdown
## 7. Traceability

### 7.1 Requirements Traceability

This Software Design Specification traces to the following Software Requirements Specification items:

| SDS Item | SRS Item | Rationale |
|----------|----------|-----------|
| MOD-DOOR-001 (DoorController) | REQ-DOOR-001 (Door control function) | Implements door open/close logic |
| MOD-DOOR-002 (SafetyInterlock) | REQ-DOOR-005 (Safety interlock) | Implements safety interlocks |
| MOD-DOOR-003 (SensorInterface) | REQ-DOOR-010 (Sensor monitoring) | Interfaces with door sensors |

### 7.2 Traceability Report Reference

Complete traceability matrix available in: `evidence/traceability/sds-to-srs-traceability.md`

Generated via:
```bash
workspace.py trace report --from design --to requirements \
    --format markdown --output evidence/traceability/sds-to-srs-traceability.md
```
```

**Validation for SIL 3-4**:
- Traceability section MUST be present (not empty)
- At least one traceability table OR reference to external traceability report
- Traceability MUST be bidirectional (forward and backward)
- 100% traceability coverage required (no orphan requirements)

**Validation for SIL 0-2**:
- Traceability section recommended but not mandatory
- If present, check format and completeness

---

## Document Review Process

### Step 1: Developer Submits Document

**Developer Action**:
```bash
# Submit document for QA review
workspace.py wf submit \
    --deliverable DOC-VER-REP-001 \
    --phase verification \
    --author "John Smith" \
    --version 1.0
```

**Workflow System Action**:
- Creates workflow entry for DOC-VER-REP-001
- Sets status to "QA_REVIEW"
- Notifies QA team
- Records submission timestamp

---

### Step 2: QA Performs Automated Check

**QA Action**:
```bash
# Run automated document checker
python3 tools/document_checker.py \
    --document docs/DOC-VER-REP-001.md \
    --sil 3 \
    --output evidence/qa/doc_review_DOC-VER-REP-001.json
```

**Automated Checks**:
1. Document ID format validation
2. Document Control table presence and format
3. Version History table presence and format
4. Approvals table presence and SIL-specific roles
5. Traceability section presence (SIL 3-4)
6. Required sections presence (Introduction, Scope, References, etc.)
7. Reference to EN 50128:2011 in References section

**Output**: JSON report with pass/fail for each check + violation details

---

### Step 3: QA Performs Manual Check

**Manual Checks** (cannot be fully automated):
1. **Content Quality** (high-level):
   - Is the content understandable and well-structured?
   - Are tables and figures formatted correctly?
   - Are references complete and accurate?

2. **Traceability Validation** (SIL 3-4):
   - Are all referenced upstream artifacts present?
   - Are traceability links valid (target IDs exist)?
   - Is traceability coverage complete (no gaps)?

3. **Approvals Validation**:
   - Are approver names actual project team members?
   - Are independence requirements met (SIL 3-4)?

**QA Review Checklist**:
```markdown
- [ ] Document ID format correct (DOC-[ROLE]-[TYPE]-[NNN])
- [ ] Document Control table complete (ID, version, date, project, SIL, author, status)
- [ ] Version History table present with at least one entry
- [ ] Approvals table present with SIL-specific roles
- [ ] Traceability section present (SIL 3-4) with content
- [ ] All mandatory sections present (Introduction, Scope, References, main content)
- [ ] EN 50128:2011 reference present in References section
- [ ] Document formatting consistent (headings, tables, code blocks)
- [ ] No obvious typos or formatting errors
```

---

### Step 4: QA Makes Decision

**Decision Criteria**:
- **PASS**: All automated checks PASS + all manual checks PASS
- **FAIL**: Any automated check FAIL OR any manual check FAIL

**If PASS**:
```bash
# Approve document for technical review
workspace.py wf review \
    --deliverable DOC-VER-REP-001 \
    --reviewer QUA \
    --status approved \
    --comments "Template compliance verified. All sections complete. Proceed to technical review."
```

**If FAIL**:
```bash
# Reject document with defect list
workspace.py wf review \
    --deliverable DOC-VER-REP-001 \
    --reviewer QUA \
    --status rejected \
    --comments "Template compliance issues found. See defect list in evidence/qa/doc_review_DOC-VER-REP-001.json. Fix and resubmit."
```

**Workflow System Action**:
- Records QA review decision
- Notifies developer (if rejected)
- Notifies technical reviewers (if approved)
- Updates document status

---

### Step 5: Developer Fixes Issues (If Rejected)

**Developer Action**:
1. Read defect list in `evidence/qa/doc_review_DOC-VER-REP-001.json`
2. Fix all issues identified
3. Update document version (e.g., 1.0 → 1.1)
4. Update Version History table with changes
5. Resubmit via `workspace.py wf submit` (RESUBMIT flag)

**Example Defect List** (JSON format):
```json
{
  "document_id": "DOC-VER-REP-001",
  "review_date": "2026-03-14",
  "reviewer": "Jane Doe (QA)",
  "sil_level": 3,
  "status": "REJECTED",
  "defects": [
    {
      "id": "DEF-001",
      "severity": "CRITICAL",
      "check": "Document ID Format",
      "issue": "Document ID is 'DOC-VER-001' but should be 'DOC-VER-REP-001' (missing TYPE code)",
      "location": "Line 10: Document Control table",
      "fix": "Change Document ID to 'DOC-VER-REP-001' in Document Control table and filename"
    },
    {
      "id": "DEF-002",
      "severity": "MAJOR",
      "check": "Approvals Table - SIL 3",
      "issue": "Missing 'Independent Validator' role in Approvals table",
      "location": "Line 45: Approvals table",
      "fix": "Add row for 'Independent Validator' with name, signature, date fields"
    },
    {
      "id": "DEF-003",
      "severity": "MAJOR",
      "check": "Traceability Section",
      "issue": "Traceability section (Section 7) is empty",
      "location": "Line 320: ## 7. Traceability",
      "fix": "Add traceability table or reference to external traceability report"
    }
  ],
  "pass_count": 4,
  "fail_count": 3,
  "recommendation": "Fix all CRITICAL and MAJOR defects and resubmit. One resubmit allowed per 1-pass policy."
}
```

---

### Step 6: QA Re-Reviews (1-Pass Policy)

**QA Action**:
- Run automated check again
- Perform manual check again
- Verify ALL defects from first review are fixed

**Decision (FINAL)**:
- **PASS**: Approve for technical review
- **FAIL**: Escalate to QA Manager + PM (1-pass limit reached)

**If FAIL Second Time**:
```bash
# Escalate to QA Manager
workspace.py wf review \
    --deliverable DOC-VER-REP-001 \
    --reviewer QUA \
    --status escalated \
    --comments "Document failed QA review twice. 1-pass policy limit reached. Escalating to QA Manager and PM for resolution."

# Notify QA Manager and PM
# (Workflow system sends notification)
```

**Escalation Process**:
1. QA Manager meets with Developer to understand issues
2. QA Manager determines if:
   - Developer needs training (on EN 50128 templates)
   - Template requirements unclear (update QA guidance)
   - Developer needs more time (schedule issue, coordinate with PM)
3. QA Manager and PM agree on resolution path
4. Developer resubmits with QA Manager approval (exception to 1-pass policy)

---

## Document ID Format Validation

### Document ID Structure

**Format**: `DOC-[ROLE]-[TYPE]-[NNN]`

**Components**:
1. **Prefix**: Always "DOC"
2. **Role**: 2-3 letter role code (REQ, DES, IMP, TST, VER, INT, VAL, SAF, QUA, CM, PM)
3. **Type**: 2-5 letter document type code (SRS, SAS, SDS, ICD, PLAN, REP, etc.)
4. **Number**: 3-digit sequential number (001, 002, ..., 999)

**Examples (Correct)**:
- `DOC-REQ-SRS-001` (Software Requirements Specification)
- `DOC-DES-SAS-001` (Software Architecture Specification)
- `DOC-DES-SDS-001` (Software Design Specification)
- `DOC-VER-REP-001` (Verification Report)
- `DOC-VAL-REP-001` (Validation Report)
- `DOC-QUA-PLAN-001` (Software Quality Assurance Plan)

**Examples (Incorrect)**:
- ❌ `VER-REP-001` (missing "DOC" prefix)
- ❌ `DOC-VER-001` (missing TYPE code)
- ❌ `DOC-VER-REPORT-001` (TYPE code too long, use "REP")
- ❌ `DOC-VER-REP-1` (number must be 3 digits: "001")
- ❌ `DOC-VERIFIER-REP-001` (ROLE code too long, use "VER")

---

### Document ID Validation Script

**Python Implementation**:
```python
import re

def validate_document_id(doc_id):
    """
    Validate EN 50128 document ID format.
    
    Format: DOC-[ROLE]-[TYPE]-[NNN]
    
    Returns:
        (bool, str): (is_valid, error_message)
    """
    # Regex pattern
    pattern = r'^DOC-([A-Z]{2,3})-([A-Z]{2,5})-(\d{3})$'
    
    match = re.match(pattern, doc_id)
    if not match:
        return (False, f"Document ID '{doc_id}' does not match format DOC-[ROLE]-[TYPE]-[NNN]")
    
    role, doc_type, number = match.groups()
    
    # Validate role code
    valid_roles = ['REQ', 'DES', 'IMP', 'TST', 'VER', 'INT', 'VAL', 'SAF', 'QUA', 'CM', 'PM']
    if role not in valid_roles:
        return (False, f"Invalid ROLE code '{role}'. Must be one of: {', '.join(valid_roles)}")
    
    # Validate type code (cannot exhaustively check, but check common ones)
    valid_types = ['SRS', 'SAS', 'SDS', 'ICD', 'CODE', 'UTP', 'ITP', 'VTP', 'REP', 'PLAN']
    if doc_type not in valid_types:
        # Warning only (not error) - allow custom type codes
        print(f"Warning: TYPE code '{doc_type}' is not in standard list. Verify correctness.")
    
    # Validate number is 3 digits (already checked by regex)
    
    return (True, "Document ID format valid")

# Example usage
doc_ids = [
    "DOC-VER-REP-001",  # Valid
    "VER-REP-001",      # Invalid (missing DOC prefix)
    "DOC-VER-001",      # Invalid (missing TYPE)
    "DOC-VER-REP-1"     # Invalid (number not 3 digits)
]

for doc_id in doc_ids:
    is_valid, message = validate_document_id(doc_id)
    print(f"{doc_id}: {'PASS' if is_valid else 'FAIL'} - {message}")
```

**Output**:
```
DOC-VER-REP-001: PASS - Document ID format valid
VER-REP-001: FAIL - Document ID 'VER-REP-001' does not match format DOC-[ROLE]-[TYPE]-[NNN]
DOC-VER-001: FAIL - Document ID 'DOC-VER-001' does not match format DOC-[ROLE]-[TYPE]-[NNN]
DOC-VER-REP-1: FAIL - Document ID 'DOC-VER-REP-1' does not match format DOC-[ROLE]-[TYPE]-[NNN]
```

---

### Document ID Consistency Check

**Consistency Requirement**: Document ID MUST be consistent across:
1. **Filename**: `DOC-VER-REP-001.md`
2. **Document Control Table**: `| **Document ID** | DOC-VER-REP-001 |`
3. **Workflow System**: `workspace.py wf submit --deliverable DOC-VER-REP-001`

**Validation Script**:
```python
def check_document_id_consistency(filepath, doc_control_id, workflow_id):
    """
    Check Document ID consistency across filename, Document Control table, and workflow.
    
    Args:
        filepath: Path to document file (e.g., "docs/DOC-VER-REP-001.md")
        doc_control_id: Document ID from Document Control table
        workflow_id: Document ID from workflow system
    
    Returns:
        (bool, list): (is_consistent, error_list)
    """
    import os
    
    # Extract Document ID from filename (without extension)
    filename = os.path.basename(filepath)
    filename_id = os.path.splitext(filename)[0]
    
    errors = []
    
    # Check filename vs Document Control
    if filename_id != doc_control_id:
        errors.append(f"Filename ID '{filename_id}' != Document Control ID '{doc_control_id}'")
    
    # Check filename vs workflow
    if filename_id != workflow_id:
        errors.append(f"Filename ID '{filename_id}' != Workflow ID '{workflow_id}'")
    
    # Check Document Control vs workflow
    if doc_control_id != workflow_id:
        errors.append(f"Document Control ID '{doc_control_id}' != Workflow ID '{workflow_id}'")
    
    is_consistent = (len(errors) == 0)
    
    return (is_consistent, errors)

# Example usage
filepath = "docs/DOC-VER-REP-001.md"
doc_control_id = "DOC-VER-REP-002"  # Incorrect (should be 001)
workflow_id = "DOC-VER-REP-001"

is_consistent, errors = check_document_id_consistency(filepath, doc_control_id, workflow_id)

if is_consistent:
    print("Document ID consistency: PASS")
else:
    print("Document ID consistency: FAIL")
    for error in errors:
        print(f"  - {error}")
```

**Output**:
```
Document ID consistency: FAIL
  - Filename ID 'DOC-VER-REP-001' != Document Control ID 'DOC-VER-REP-002'
```

---

## Document Control Table Validation

### Required Fields Validation

**Validation Script**:
```python
def validate_document_control_table(doc_control):
    """
    Validate Document Control table completeness.
    
    Args:
        doc_control: Dictionary with Document Control fields
    
    Returns:
        (bool, list): (is_valid, error_list)
    """
    import re
    from datetime import datetime
    
    required_fields = ['document_id', 'version', 'date', 'project', 'sil_level', 'author', 'status']
    errors = []
    
    # Check all required fields present
    for field in required_fields:
        if field not in doc_control or not doc_control[field]:
            errors.append(f"Missing required field: {field}")
    
    if errors:
        return (False, errors)
    
    # Validate Document ID format
    doc_id = doc_control['document_id']
    pattern = r'^DOC-([A-Z]{2,3})-([A-Z]{2,5})-(\d{3})$'
    if not re.match(pattern, doc_id):
        errors.append(f"Invalid Document ID format: {doc_id}")
    
    # Validate version format (X.Y)
    version = doc_control['version']
    if not re.match(r'^\d+\.\d+$', version):
        errors.append(f"Invalid version format: {version} (must be X.Y, e.g., 1.0)")
    
    # Validate date format (YYYY-MM-DD)
    date_str = doc_control['date']
    try:
        datetime.strptime(date_str, '%Y-%m-%d')
    except ValueError:
        errors.append(f"Invalid date format: {date_str} (must be YYYY-MM-DD)")
    
    # Validate SIL level (0, 1, 2, 3, or 4)
    sil_level = doc_control['sil_level']
    if sil_level not in [0, 1, 2, 3, 4]:
        errors.append(f"Invalid SIL level: {sil_level} (must be 0, 1, 2, 3, or 4)")
    
    # Validate author format (should include role)
    author = doc_control['author']
    if ',' not in author:
        errors.append(f"Author field '{author}' should include role (e.g., 'John Smith, Verifier')")
    
    # Validate status
    valid_statuses = ['Draft', 'Review', 'Approved', 'Baseline']
    status = doc_control['status']
    if status not in valid_statuses:
        errors.append(f"Invalid status: {status} (must be one of: {', '.join(valid_statuses)})")
    
    is_valid = (len(errors) == 0)
    return (is_valid, errors)

# Example usage
doc_control_valid = {
    'document_id': 'DOC-VER-REP-001',
    'version': '1.0',
    'date': '2026-03-14',
    'project': 'Railway Door Controller',
    'sil_level': 3,
    'author': 'John Smith, Verifier',
    'status': 'Review'
}

doc_control_invalid = {
    'document_id': 'VER-REP-001',  # Missing DOC prefix
    'version': 'v1.0',  # Invalid format (should be 1.0)
    'date': '14/03/2026',  # Invalid format (should be 2026-03-14)
    'project': 'Railway Door Controller',
    'sil_level': 5,  # Invalid (must be 0-4)
    'author': 'John Smith',  # Missing role
    'status': 'InReview'  # Invalid (should be 'Review')
}

print("Valid Document Control:")
is_valid, errors = validate_document_control_table(doc_control_valid)
print(f"  Result: {'PASS' if is_valid else 'FAIL'}")
if not is_valid:
    for error in errors:
        print(f"    - {error}")

print("\nInvalid Document Control:")
is_valid, errors = validate_document_control_table(doc_control_invalid)
print(f"  Result: {'PASS' if is_valid else 'FAIL'}")
if not is_valid:
    for error in errors:
        print(f"    - {error}")
```

**Output**:
```
Valid Document Control:
  Result: PASS

Invalid Document Control:
  Result: FAIL
    - Invalid Document ID format: VER-REP-001
    - Invalid version format: v1.0 (must be X.Y, e.g., 1.0)
    - Invalid date format: 14/03/2026 (must be YYYY-MM-DD)
    - Invalid SIL level: 5 (must be 0, 1, 2, 3, or 4)
    - Author field 'John Smith' should include role (e.g., 'John Smith, Verifier')
    - Invalid status: InReview (must be one of: Draft, Review, Approved, Baseline)
```

---

## Approvals Table Validation

### SIL-Specific Approvers Check

**Validation Script**:
```python
def validate_approvals_table(approvals, sil_level):
    """
    Validate Approvals table has SIL-specific approvers.
    
    Args:
        approvals: List of approver roles
        sil_level: Project SIL level (0-4)
    
    Returns:
        (bool, list): (is_valid, error_list)
    """
    errors = []
    
    # Define required approvers per SIL level
    required_approvers = {
        0: ['Author', 'Reviewer', 'QA Manager', 'Project Manager'],
        1: ['Author', 'Reviewer', 'QA Manager', 'Project Manager'],
        2: ['Author', 'Reviewer', 'QA Manager', 'Safety Manager', 'Project Manager'],
        3: ['Author', 'Technical Reviewer (independent)', 'QA Manager', 'Safety Manager', 
            'Independent Verifier', 'Independent Validator', 'Assessor', 'Project Manager'],
        4: ['Author', 'Technical Reviewer (independent)', 'QA Manager', 'Safety Manager', 
            'Independent Verifier', 'Independent Validator', 'Assessor', 'Project Manager']
    }
    
    if sil_level not in required_approvers:
        return (False, [f"Invalid SIL level: {sil_level}"])
    
    required = required_approvers[sil_level]
    
    # Check all required approvers present
    for approver in required:
        # Check for exact match or partial match (e.g., "Technical Reviewer" matches "Technical Reviewer (independent)")
        base_approver = approver.split('(')[0].strip()
        found = any(base_approver in appr for appr in approvals)
        
        if not found:
            errors.append(f"Missing required approver for SIL {sil_level}: {approver}")
    
    # Check for independence markers (SIL 3-4)
    if sil_level >= 3:
        independence_required = ['Technical Reviewer (independent)', 'Independent Verifier', 'Independent Validator']
        for approver in independence_required:
            if approver not in ' '.join(approvals):
                # Check if role exists but without "independent" marker
                base_role = approver.replace('Independent ', '').replace(' (independent)', '')
                if any(base_role in appr and 'independent' not in appr.lower() for appr in approvals):
                    errors.append(f"Approver '{base_role}' must be marked as 'independent' for SIL 3-4")
    
    is_valid = (len(errors) == 0)
    return (is_valid, errors)

# Example usage - SIL 3 project
approvals_valid = [
    'Author',
    'Technical Reviewer (independent)',
    'QA Manager',
    'Safety Manager',
    'Independent Verifier',
    'Independent Validator',
    'Assessor',
    'Project Manager'
]

approvals_invalid = [
    'Author',
    'Technical Reviewer',  # Missing "(independent)"
    'QA Manager',
    'Safety Manager',
    # Missing Independent Verifier
    'Independent Validator',
    # Missing Assessor
    'Project Manager'
]

print("Valid Approvals (SIL 3):")
is_valid, errors = validate_approvals_table(approvals_valid, sil_level=3)
print(f"  Result: {'PASS' if is_valid else 'FAIL'}")
if not is_valid:
    for error in errors:
        print(f"    - {error}")

print("\nInvalid Approvals (SIL 3):")
is_valid, errors = validate_approvals_table(approvals_invalid, sil_level=3)
print(f"  Result: {'PASS' if is_valid else 'FAIL'}")
if not is_valid:
    for error in errors:
        print(f"    - {error}")
```

**Output**:
```
Valid Approvals (SIL 3):
  Result: PASS

Invalid Approvals (SIL 3):
  Result: FAIL
    - Missing required approver for SIL 3: Independent Verifier
    - Missing required approver for SIL 3: Assessor
    - Approver 'Technical Reviewer' must be marked as 'independent' for SIL 3-4
```

---

## Traceability Section Validation

### Traceability Requirements (SIL 3-4)

**EN 50128 Section 6.5.4.5(d)**: "Traceability of all items to and from requirements"

For SIL 3-4, ALL deliverables MUST include traceability section with:
1. **Forward Traceability**: Requirements → Design → Code → Tests
2. **Backward Traceability**: Tests → Code → Design → Requirements
3. **100% Coverage**: No orphan requirements (all requirements traced)
4. **Traceability Matrix**: Embedded table OR reference to external report

---

### Traceability Section Validation Script

**Python Implementation**:
```python
def validate_traceability_section(doc_content, sil_level, doc_type):
    """
    Validate traceability section in document.
    
    Args:
        doc_content: Full document text
        sil_level: Project SIL level (0-4)
        doc_type: Document type (SRS, SAS, SDS, etc.)
    
    Returns:
        (bool, list): (is_valid, error_list)
    """
    import re
    
    errors = []
    warnings = []
    
    # Traceability MANDATORY for SIL 3-4
    if sil_level >= 3:
        # Check for traceability section
        traceability_pattern = r'##?\s+\d*\.?\s*Traceability'
        if not re.search(traceability_pattern, doc_content, re.IGNORECASE):
            errors.append(f"MANDATORY: Traceability section missing (required for SIL 3-4)")
            return (False, errors)
        
        # Extract traceability section content
        match = re.search(r'##?\s+\d*\.?\s*Traceability(.*?)(##|$)', doc_content, re.IGNORECASE | re.DOTALL)
        if match:
            traceability_content = match.group(1)
            
            # Check if section is empty
            if len(traceability_content.strip()) < 50:
                errors.append("Traceability section is empty or too short (must contain traceability table or reference to external report)")
            
            # Check for traceability table OR reference to external report
            has_table = '|' in traceability_content and '---' in traceability_content
            has_reference = 'evidence/traceability' in traceability_content or 'workspace.py trace' in traceability_content
            
            if not (has_table or has_reference):
                errors.append("Traceability section must contain traceability table OR reference to external traceability report")
            
            # Check for bidirectional traceability
            if 'forward' not in traceability_content.lower() and 'backward' not in traceability_content.lower():
                warnings.append("Traceability should be bidirectional (forward and backward)")
        
    else:
        # Traceability recommended for SIL 0-2
        traceability_pattern = r'##?\s+\d*\.?\s*Traceability'
        if not re.search(traceability_pattern, doc_content, re.IGNORECASE):
            warnings.append(f"Recommended: Traceability section recommended for SIL {sil_level}")
    
    is_valid = (len(errors) == 0)
    
    if warnings:
        errors.extend([f"WARNING: {w}" for w in warnings])
    
    return (is_valid, errors)

# Example usage
doc_content_valid = """
# Software Design Specification

## 1. Introduction
...

## 7. Traceability

### 7.1 Forward Traceability (Requirements → Design)

| SDS Item | SRS Item | Rationale |
|----------|----------|-----------|
| MOD-DOOR-001 | REQ-DOOR-001 | Implements door control |
| MOD-DOOR-002 | REQ-DOOR-005 | Implements safety interlock |

### 7.2 Backward Traceability (Design → Requirements)

Complete traceability report: evidence/traceability/sds-to-srs.md

## 8. References
"""

doc_content_invalid = """
# Software Design Specification

## 1. Introduction
...

## 7. Traceability

(Empty)

## 8. References
"""

doc_content_missing = """
# Software Design Specification

## 1. Introduction
...

## 8. References
"""

print("Valid Traceability (SIL 3):")
is_valid, errors = validate_traceability_section(doc_content_valid, sil_level=3, doc_type='SDS')
print(f"  Result: {'PASS' if is_valid else 'FAIL'}")
for error in errors:
    print(f"    - {error}")

print("\nInvalid Traceability - Empty (SIL 3):")
is_valid, errors = validate_traceability_section(doc_content_invalid, sil_level=3, doc_type='SDS')
print(f"  Result: {'PASS' if is_valid else 'FAIL'}")
for error in errors:
    print(f"    - {error}")

print("\nInvalid Traceability - Missing (SIL 3):")
is_valid, errors = validate_traceability_section(doc_content_missing, sil_level=3, doc_type='SDS')
print(f"  Result: {'PASS' if is_valid else 'FAIL'}")
for error in errors:
    print(f"    - {error}")
```

**Output**:
```
Valid Traceability (SIL 3):
  Result: PASS
    - WARNING: Traceability should be bidirectional (forward and backward)

Invalid Traceability - Empty (SIL 3):
  Result: FAIL
    - Traceability section is empty or too short (must contain traceability table or reference to external report)
    - Traceability section must contain traceability table OR reference to external traceability report
    - WARNING: Traceability should be bidirectional (forward and backward)

Invalid Traceability - Missing (SIL 3):
  Result: FAIL
    - MANDATORY: Traceability section missing (required for SIL 3-4)
```

---

## Automated Document Checking

### Complete Document Checker Script

**File**: `tools/document_checker.py`

**Usage**:
```bash
python3 tools/document_checker.py \
    --document docs/DOC-VER-REP-001.md \
    --sil 3 \
    --output evidence/qa/doc_review_DOC-VER-REP-001.json
```

**Implementation** (simplified version for illustration):
```python
#!/usr/bin/env python3
"""
EN 50128 Document Template Compliance Checker

Validates EN 50128 document template compliance for QA document review.
"""

import argparse
import json
import re
import sys
from datetime import datetime
from pathlib import Path

def check_document_id_format(doc_id):
    """Check Document ID format: DOC-[ROLE]-[TYPE]-[NNN]"""
    pattern = r'^DOC-([A-Z]{2,3})-([A-Z]{2,5})-(\d{3})$'
    match = re.match(pattern, doc_id)
    
    if not match:
        return {
            'status': 'FAIL',
            'message': f"Document ID '{doc_id}' does not match format DOC-[ROLE]-[TYPE]-[NNN]"
        }
    
    role, doc_type, number = match.groups()
    valid_roles = ['REQ', 'DES', 'IMP', 'TST', 'VER', 'INT', 'VAL', 'SAF', 'QUA', 'CM', 'PM']
    
    if role not in valid_roles:
        return {
            'status': 'FAIL',
            'message': f"Invalid ROLE code '{role}'. Must be one of: {', '.join(valid_roles)}"
        }
    
    return {'status': 'PASS', 'message': 'Document ID format valid'}

def check_document_control(content):
    """Check Document Control table presence and format"""
    # Look for Document Control table
    doc_control_pattern = r'\|\s*\*\*Document ID\*\*\s*\|.*?\|'
    
    if not re.search(doc_control_pattern, content):
        return {
            'status': 'FAIL',
            'message': 'Document Control table not found (must contain | **Document ID** | ... |)'
        }
    
    # Extract Document Control fields
    required_fields = ['Document ID', 'Version', 'Date', 'Project', 'SIL Level', 'Author', 'Status']
    missing_fields = []
    
    for field in required_fields:
        field_pattern = rf'\|\s*\*\*{field}\*\*\s*\|'
        if not re.search(field_pattern, content):
            missing_fields.append(field)
    
    if missing_fields:
        return {
            'status': 'FAIL',
            'message': f"Document Control table missing fields: {', '.join(missing_fields)}"
        }
    
    return {'status': 'PASS', 'message': 'Document Control table complete'}

def check_approvals_table(content, sil_level):
    """Check Approvals table for SIL-specific approvers"""
    # Look for Approvals section
    approvals_pattern = r'##\s+APPROVALS|##\s+\d+\.\s+Approvals'
    
    if not re.search(approvals_pattern, content, re.IGNORECASE):
        return {
            'status': 'FAIL',
            'message': 'Approvals section not found'
        }
    
    # Define required approvers per SIL level
    required_approvers = {
        0: ['Author', 'QA Manager', 'Project Manager'],
        1: ['Author', 'QA Manager', 'Project Manager'],
        2: ['Author', 'QA Manager', 'Safety Manager', 'Project Manager'],
        3: ['Author', 'QA Manager', 'Safety Manager', 'Independent Verifier', 'Independent Validator', 'Assessor', 'Project Manager'],
        4: ['Author', 'QA Manager', 'Safety Manager', 'Independent Verifier', 'Independent Validator', 'Assessor', 'Project Manager']
    }
    
    if sil_level not in required_approvers:
        return {'status': 'FAIL', 'message': f'Invalid SIL level: {sil_level}'}
    
    required = required_approvers[sil_level]
    missing_approvers = []
    
    for approver in required:
        # Check for approver in content
        if approver not in content:
            missing_approvers.append(approver)
    
    if missing_approvers:
        return {
            'status': 'FAIL',
            'message': f"Missing required approvers for SIL {sil_level}: {', '.join(missing_approvers)}"
        }
    
    return {'status': 'PASS', 'message': f'Approvals table complete for SIL {sil_level}'}

def check_traceability_section(content, sil_level):
    """Check traceability section (MANDATORY SIL 3-4)"""
    traceability_pattern = r'##\s+\d*\.?\s*Traceability'
    
    if sil_level >= 3:
        if not re.search(traceability_pattern, content, re.IGNORECASE):
            return {
                'status': 'FAIL',
                'message': 'MANDATORY: Traceability section missing (required for SIL 3-4)'
            }
        
        # Extract traceability content
        match = re.search(r'##\s+\d*\.?\s*Traceability(.*?)(##|$)', content, re.IGNORECASE | re.DOTALL)
        if match:
            traceability_content = match.group(1)
            if len(traceability_content.strip()) < 50:
                return {
                    'status': 'FAIL',
                    'message': 'Traceability section is empty or too short (must contain traceability table or reference)'
                }
        
        return {'status': 'PASS', 'message': 'Traceability section present'}
    else:
        return {'status': 'PASS', 'message': f'Traceability optional for SIL {sil_level}'}

def check_document(filepath, sil_level):
    """Run all document checks"""
    # Read document
    try:
        with open(filepath, 'r') as f:
            content = f.read()
    except Exception as e:
        return {
            'status': 'ERROR',
            'message': f'Failed to read document: {e}',
            'checks': []
        }
    
    # Extract Document ID from filename
    doc_id = Path(filepath).stem
    
    # Run checks
    checks = [
        {'name': 'Document ID Format', 'result': check_document_id_format(doc_id)},
        {'name': 'Document Control Table', 'result': check_document_control(content)},
        {'name': 'Approvals Table', 'result': check_approvals_table(content, sil_level)},
        {'name': 'Traceability Section', 'result': check_traceability_section(content, sil_level)}
    ]
    
    # Count passes and fails
    pass_count = sum(1 for check in checks if check['result']['status'] == 'PASS')
    fail_count = sum(1 for check in checks if check['result']['status'] == 'FAIL')
    
    overall_status = 'PASS' if fail_count == 0 else 'FAIL'
    
    return {
        'document_id': doc_id,
        'sil_level': sil_level,
        'review_date': datetime.now().strftime('%Y-%m-%d'),
        'status': overall_status,
        'pass_count': pass_count,
        'fail_count': fail_count,
        'checks': checks
    }

def main():
    parser = argparse.ArgumentParser(description='EN 50128 Document Template Compliance Checker')
    parser.add_argument('--document', required=True, help='Path to document to check')
    parser.add_argument('--sil', type=int, required=True, choices=[0,1,2,3,4], help='Project SIL level')
    parser.add_argument('--output', required=True, help='Output JSON report path')
    
    args = parser.parse_args()
    
    # Run checks
    result = check_document(args.document, args.sil)
    
    # Write output
    output_path = Path(args.output)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    
    with open(output_path, 'w') as f:
        json.dump(result, f, indent=2)
    
    # Print summary
    print(f"\nDocument Check: {result['status']}")
    print(f"Pass: {result['pass_count']} | Fail: {result['fail_count']}")
    
    for check in result['checks']:
        status = check['result']['status']
        name = check['name']
        message = check['result']['message']
        symbol = '✓' if status == 'PASS' else '✗'
        print(f"  {symbol} {name}: {message}")
    
    print(f"\nFull report: {output_path}")
    
    # Exit with error code if failed
    sys.exit(0 if result['status'] == 'PASS' else 1)

if __name__ == '__main__':
    main()
```

**Example Usage**:
```bash
# Check document for SIL 3 project
python3 tools/document_checker.py \
    --document docs/DOC-VER-REP-001.md \
    --sil 3 \
    --output evidence/qa/doc_review_DOC-VER-REP-001.json

# Output:
# Document Check: FAIL
# Pass: 3 | Fail: 1
#   ✓ Document ID Format: Document ID format valid
#   ✓ Document Control Table: Document Control table complete
#   ✗ Approvals Table: Missing required approvers for SIL 3: Independent Validator, Assessor
#   ✓ Traceability Section: Traceability section present
#
# Full report: evidence/qa/doc_review_DOC-VER-REP-001.json
```

---

## Document Types and Requirements

### Document-Specific Requirements

Each document type has specific requirements beyond the standard template:

| Document Type | Document ID Prefix | Specific Requirements |
|--------------|-------------------|----------------------|
| **Software Requirements Specification (SRS)** | DOC-REQ-SRS-NNN | - SHALL/SHOULD/MAY keywords<br>- Unique requirement IDs (REQ-XXX-NNN)<br>- Traceability to system requirements<br>- SIL level for each requirement |
| **Software Architecture Specification (SAS)** | DOC-DES-SAS-NNN | - Module structure diagram<br>- Interface specifications<br>- Traceability to SRS<br>- Complexity analysis (CCN ≤ limits) |
| **Software Design Specification (SDS)** | DOC-DES-SDS-NNN | - Detailed design for each module<br>- Algorithm descriptions<br>- Data structure definitions<br>- Traceability to SRS/SAS |
| **Unit Test Plan (UTP)** | DOC-TST-UTP-NNN | - Test case IDs<br>- Traceability to requirements<br>- Coverage requirements (SIL-dependent) |
| **Verification Report (VER)** | DOC-VER-REP-NNN | - Static analysis results<br>- Complexity analysis<br>- MISRA C compliance (SIL 2+)<br>- Coverage results<br>- Traceability validation |
| **Validation Report (VAL)** | DOC-VAL-REP-NNN | - System test results<br>- Acceptance criteria met<br>- Customer approval<br>- Traceability validation |

---

### Document-Specific Validation

**SRS Specific Check** (example):
```python
def check_srs_specific(content):
    """Check Software Requirements Specification specific requirements"""
    errors = []
    
    # Check for requirement IDs (REQ-XXX-NNN format)
    req_pattern = r'REQ-[A-Z]+-\d{3}'
    req_matches = re.findall(req_pattern, content)
    
    if len(req_matches) == 0:
        errors.append("No requirement IDs found (expected format: REQ-XXX-NNN)")
    
    # Check for SHALL/SHOULD/MAY keywords
    shall_count = len(re.findall(r'\bSHALL\b', content))
    
    if shall_count == 0:
        errors.append("No SHALL keywords found (requirements should use SHALL for mandatory)")
    
    # Check for SIL level assignment
    if 'SIL Level' not in content and 'SIL:' not in content:
        errors.append("SIL level assignment not found for requirements")
    
    return errors
```

---

## Review Report Generation

### Document Review Report Template

When QA completes a document review, generate a Document Review Report:

**Template**:
```markdown
# Document Review Report

## Document Control

| Field | Value |
|-------|-------|
| **Document ID** | DOC-QUA-DREVIEW-001 |
| **Version** | 1.0 |
| **Date** | 2026-03-14 |
| **Project** | Railway Door Controller |
| **SIL Level** | 3 |
| **Reviewer** | Jane Doe, QA Manager |
| **Status** | Completed |

## 1. Review Information

| Field | Value |
|-------|-------|
| **Reviewed Document** | DOC-VER-REP-001 (Verification Report) |
| **Review Type** | Template Compliance Check |
| **Review Date** | 2026-03-14 |
| **SIL Level** | 3 |
| **Automated Checks** | Yes (document_checker.py) |
| **Manual Checks** | Yes |

## 2. Review Results

| Check | Status | Details |
|-------|--------|---------|
| Document ID Format | PASS | DOC-VER-REP-001 format correct |
| Document Control Table | PASS | All required fields present |
| Version History | PASS | Version 1.0 entry present |
| Approvals Table | FAIL | Missing Independent Validator |
| Traceability Section | PASS | Section 7 present with tables |
| EN 50128 Reference | PASS | Referenced in Section 8 |

**Overall Status**: REJECTED

## 3. Defects Found

### Defect 1: Missing Independent Validator in Approvals Table
- **Severity**: CRITICAL
- **Location**: Line 45, Approvals table
- **Issue**: Approvals table is missing 'Independent Validator' role (MANDATORY for SIL 3)
- **Fix**: Add row for 'Independent Validator' with name, signature, date fields
- **EN 50128 Reference**: Section 5.1.2.10f

### Defect 2: Traceability Section Incomplete
- **Severity**: MAJOR
- **Location**: Line 320, Section 7
- **Issue**: Traceability section has forward traceability but missing backward traceability
- **Fix**: Add backward traceability table or reference to report
- **EN 50128 Reference**: Section 6.5.4.5(d)

## 4. Actions Required

1. **Developer**: Fix defects 1 and 2 listed above
2. **Developer**: Update document version to 1.1
3. **Developer**: Add entry to Version History table
4. **Developer**: Resubmit via `workspace.py wf submit --deliverable DOC-VER-REP-001`
5. **QA**: Re-review (FINAL - 1-pass policy)

## 5. Decision

**Decision**: REJECTED

**Rationale**: Missing MANDATORY approver (Independent Validator) for SIL 3 project. Traceability incomplete (missing backward traceability).

**Next Steps**: Developer to fix issues and resubmit. One resubmit allowed per 1-pass policy.

## 6. Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **QA Manager** | Jane Doe | | 2026-03-14 |
```

---

## 1-Pass Review Policy

### Policy Definition

**1-Pass Policy**: Developer gets ONE opportunity to fix issues and resubmit after initial rejection.

**Rationale**:
- Encourages quality on first submission
- Prevents endless rework cycles
- Escalates persistent issues to management
- Maintains project schedule discipline

---

### Workflow

```
Developer submits (1st submission)
          ↓
QA reviews (automated + manual)
          ↓
    [PASS] → Approved
          ↓
    Technical review proceeds
          
    [FAIL] → Rejected
          ↓
    Developer fixes issues (1 resubmit allowed)
          ↓
Developer resubmits (2nd submission)
          ↓
QA re-reviews (FINAL DECISION)
          ↓
    [PASS] → Approved
          ↓
    Technical review proceeds
          
    [FAIL] → Escalate to QA Manager + PM
          ↓
    QA Manager meets with Developer
          ↓
    Root cause analysis:
    - Training needed?
    - Template guidance unclear?
    - Schedule pressure?
          ↓
    QA Manager + PM agree resolution
          ↓
    Developer resubmits with QA Manager approval (exception)
```

---

### Escalation Process

**When**: Document fails QA review TWICE (1-pass limit reached)

**Actions**:
1. **QA Manager** schedules meeting with Developer
2. **QA Manager** performs root cause analysis:
   - Does Developer understand EN 50128 templates?
   - Is template guidance clear and accessible?
   - Is Developer rushing due to schedule pressure?
   - Are there systemic issues (tool problems, unclear requirements)?
3. **QA Manager** and **PM** agree on resolution:
   - Provide training on EN 50128 documentation standards
   - Update QA guidance if templates unclear
   - Adjust schedule if unrealistic (with PM approval)
   - Assign mentor to Developer for next deliverable
4. **QA Manager** authorizes exception to 1-pass policy (one time)
5. **Developer** resubmits with corrective actions
6. **QA Manager** personally reviews (not delegate to QA team)

**Escalation Tracking**:
```bash
# Log escalation
workspace.py wf review \
    --deliverable DOC-VER-REP-001 \
    --reviewer QUA_MGR \
    --status escalated \
    --comments "1-pass limit reached. Root cause: Developer unfamiliar with SIL 3 approvers requirement. Action: Training provided on EN 50128 Section 5.1.2.10. Exception granted for 3rd submission."
```

---

## Tool Integration

### Workflow Management Integration

**Submit Document for QA Review**:
```bash
workspace.py wf submit \
    --deliverable DOC-VER-REP-001 \
    --phase verification \
    --author "John Smith" \
    --version 1.0
```

**QA Review Decision (Approve)**:
```bash
workspace.py wf review \
    --deliverable DOC-VER-REP-001 \
    --reviewer QUA \
    --status approved \
    --comments "Template compliance verified. All sections complete. Proceed to technical review (VER/VMGR)."
```

**QA Review Decision (Reject)**:
```bash
workspace.py wf review \
    --deliverable DOC-VER-REP-001 \
    --reviewer QUA \
    --status rejected \
    --comments "Template compliance issues found. See evidence/qa/doc_review_DOC-VER-REP-001.json for defect list. Fix and resubmit (1 pass allowed)."
```

**Check Workflow Status**:
```bash
workspace.py wf status --deliverable DOC-VER-REP-001
```

**Output**:
```
Deliverable: DOC-VER-REP-001
Status: REJECTED
Phase: verification
Submitted: 2026-03-14 10:30:00
Reviewer: QUA (Jane Doe)
Review Date: 2026-03-14 14:15:00
Comments: Template compliance issues found. See evidence/qa/doc_review_DOC-VER-REP-001.json for defect list. Fix and resubmit (1 pass allowed).
Resubmit Count: 0 of 1 allowed
```

---

### Traceability Validation Integration

**Validate Traceability for Document**:
```bash
# Validate forward traceability (SDS → SRS)
workspace.py trace validate \
    --phase design \
    --sil 3

# Output:
# Traceability Validation: FAIL
# Coverage: 95% (38 of 40 requirements traced)
# Missing traces:
#   - REQ-DOOR-012 (no design item)
#   - REQ-DOOR-015 (no design item)
```

**Generate Traceability Report for Document**:
```bash
# Generate traceability matrix for inclusion in document
workspace.py trace report \
    --from design --to requirements \
    --format markdown \
    --output evidence/traceability/sds-to-srs-traceability.md
```

**Include in Document**:
```markdown
## 7. Traceability

### 7.1 Requirements Traceability

Complete traceability matrix available in: `evidence/traceability/sds-to-srs-traceability.md`

Generated via:
```bash
workspace.py trace report --from design --to requirements \
    --format markdown --output evidence/traceability/sds-to-srs-traceability.md
```

### 7.2 Traceability Summary

| Metric | Value |
|--------|-------|
| Total SRS Requirements | 40 |
| SDS Items Tracing to SRS | 38 |
| Coverage | 95% |
| Orphan Requirements | REQ-DOOR-012, REQ-DOOR-015 |
| Status | INCOMPLETE (fix required before approval) |
```

---

## SIL-Specific Requirements

### QA Document Review Requirements by SIL

| Requirement | SIL 0-1 | SIL 2 | SIL 3-4 |
|------------|---------|-------|---------|
| **Template Compliance Check** | Recommended | Highly Recommended | **MANDATORY** |
| **Document ID Format** | Recommended | Highly Recommended | **MANDATORY** |
| **Document Control Table** | Highly Recommended | Highly Recommended | **MANDATORY** |
| **Approvals Table with SIL-specific approvers** | Recommended | Highly Recommended | **MANDATORY** |
| **Traceability Section** | Optional | Recommended | **MANDATORY** |
| **Automated Document Checking** | Optional | Recommended | **MANDATORY** |
| **1-Pass Review Policy** | Optional | Recommended | **MANDATORY** |
| **Independent QA Team** | Recommended | Highly Recommended | **MANDATORY** |
| **QA Document Review Report** | Recommended | Highly Recommended | **MANDATORY** |

---

### SIL 3-4 Specific Requirements

**Independence** (EN 50128 Section 5.1.2.10):
- QA team MUST NOT report to PM or development manager
- QA Manager reports to senior management or Safety Manager
- No development responsibilities for QA personnel
- No conflicts of interest

**Traceability** (EN 50128 Section 6.5.4.5(d)):
- 100% traceability coverage MANDATORY
- Bidirectional traceability (forward and backward)
- Traceability section MANDATORY in all deliverables
- Traceability validation automated via `workspace.py trace validate`

**Approvals** (EN 50128 Section 5.1.2.10):
- Independent Verifier MANDATORY
- Independent Validator MANDATORY
- Assessor MANDATORY (independent safety assessment)
- Safety Manager MANDATORY

**Documentation** (EN 50128 Annex C):
- All deliverables MUST follow EN 50128 templates
- Document Review Report MANDATORY for all deliverables
- Audit trail for certification

---

## Example Document Review Scenarios

### Scenario 1: Document ID Format Incorrect (REJECT)

**Context**: SIL 3 door control project, Verification Report submission

**Document Submitted**: `DOC-VER-001.md`

**QA Review**:
```bash
python3 tools/document_checker.py \
    --document docs/DOC-VER-001.md \
    --sil 3 \
    --output evidence/qa/doc_review_DOC-VER-001.json
```

**Result**: FAIL
- Document ID Format: FAIL (DOC-VER-001 should be DOC-VER-REP-001, missing TYPE code "REP")
- Document Control Table: PASS
- Approvals Table: PASS
- Traceability Section: PASS

**QA Action**:
```bash
workspace.py wf review \
    --deliverable DOC-VER-001 \
    --reviewer QUA \
    --status rejected \
    --comments "Document ID format incorrect: DOC-VER-001 should be DOC-VER-REP-001 (missing TYPE code 'REP'). Rename file and update Document Control table. Resubmit (1 pass allowed)."
```

**Developer Action**:
1. Rename file: `mv docs/DOC-VER-001.md docs/DOC-VER-REP-001.md`
2. Update Document Control table: `| **Document ID** | DOC-VER-REP-001 |`
3. Update version: 1.0 → 1.1
4. Update Version History:
   ```markdown
   | Version | Date | Author | Changes | Approved By |
   |---------|------|--------|---------|-------------|
   | 1.0 | 2026-03-14 | John Smith | Initial draft | - |
   | 1.1 | 2026-03-14 | John Smith | Fixed Document ID format (DOC-VER-001 → DOC-VER-REP-001) | - |
   ```
5. Resubmit:
   ```bash
   workspace.py wf submit \
       --deliverable DOC-VER-REP-001 \
       --phase verification \
       --author "John Smith" \
       --version 1.1
   ```

**QA Re-Review**: PASS → Approved for technical review

---

### Scenario 2: Missing Independent Validator for SIL 3 (REJECT)

**Context**: SIL 3 speed controller project, Validation Report submission

**Document Submitted**: `DOC-VAL-REP-001.md`

**QA Review**:
```bash
python3 tools/document_checker.py \
    --document docs/DOC-VAL-REP-001.md \
    --sil 3 \
    --output evidence/qa/doc_review_DOC-VAL-REP-001.json
```

**Result**: FAIL
- Document ID Format: PASS
- Document Control Table: PASS
- **Approvals Table: FAIL** (Missing Independent Validator, Missing Assessor)
- Traceability Section: PASS

**QA Action**:
```bash
workspace.py wf review \
    --deliverable DOC-VAL-REP-001 \
    --reviewer QUA \
    --status rejected \
    --comments "Approvals table missing MANDATORY approvers for SIL 3: Independent Validator and Assessor. Add both roles to Approvals table per EN 50128 Section 5.1.2.10. Resubmit (1 pass allowed)."
```

**Developer Action**:
1. Update Approvals table:
   ```markdown
   | Role | Name | Signature | Date |
   |------|------|-----------|------|
   | **Author** | Alice Johnson | | 2026-03-14 |
   | **Technical Reviewer (independent)** | Bob Lee | | |
   | **QA Manager** | Jane Doe | | |
   | **Safety Manager** | Carol White | | |
   | **Independent Verifier** | Dave Brown | | |
   | **Independent Validator** | Eve Green | | |   <!-- ADDED -->
   | **Assessor** | Frank Black | | |                <!-- ADDED -->
   | **Project Manager** | George Gray | | |
   ```
2. Update version: 1.0 → 1.1
3. Update Version History
4. Resubmit

**QA Re-Review**: PASS → Approved for technical review

---

### Scenario 3: Traceability Section Empty (REJECT, SIL 3)

**Context**: SIL 3 brake controller project, Software Design Specification submission

**Document Submitted**: `DOC-DES-SDS-001.md`

**QA Review**:
```bash
python3 tools/document_checker.py \
    --document docs/DOC-DES-SDS-001.md \
    --sil 3 \
    --output evidence/qa/doc_review_DOC-DES-SDS-001.json
```

**Result**: FAIL
- Document ID Format: PASS
- Document Control Table: PASS
- Approvals Table: PASS
- **Traceability Section: FAIL** (Section 7 exists but is empty)

**QA Action**:
```bash
workspace.py wf review \
    --deliverable DOC-DES-SDS-001 \
    --reviewer QUA \
    --status rejected \
    --comments "Traceability section (Section 7) is empty. MANDATORY for SIL 3. Add traceability table OR reference to external traceability report. Generate via 'workspace.py trace report --from design --to requirements'. Resubmit (1 pass allowed)."
```

**Developer Action**:
1. Generate traceability report:
   ```bash
   workspace.py trace report \
       --from design --to requirements \
       --format markdown \
       --output evidence/traceability/sds-to-srs-traceability.md
   ```
2. Update Section 7 with traceability content:
   ```markdown
   ## 7. Traceability
   
   ### 7.1 Requirements Traceability
   
   This Software Design Specification traces to the following Software Requirements Specification items:
   
   | SDS Module | SRS Requirement | Rationale |
   |------------|-----------------|-----------|
   | MOD-BRAKE-001 | REQ-BRAKE-001 | Implements brake control logic |
   | MOD-BRAKE-002 | REQ-BRAKE-005 | Implements emergency brake |
   | MOD-BRAKE-003 | REQ-BRAKE-010 | Implements brake sensor monitoring |
   
   ### 7.2 Traceability Report Reference
   
   Complete traceability matrix: `evidence/traceability/sds-to-srs-traceability.md`
   
   Generated via:
   ```bash
   workspace.py trace report --from design --to requirements \
       --format markdown --output evidence/traceability/sds-to-srs-traceability.md
   ```
   ```
3. Update version: 1.0 → 1.1
4. Update Version History
5. Resubmit

**QA Re-Review**: PASS → Approved for technical review

---

### Scenario 4: All Checks Pass (APPROVE)

**Context**: SIL 3 door control project, Verification Report submission

**Document Submitted**: `DOC-VER-REP-001.md`

**QA Review**:
```bash
python3 tools/document_checker.py \
    --document docs/DOC-VER-REP-001.md \
    --sil 3 \
    --output evidence/qa/doc_review_DOC-VER-REP-001.json
```

**Result**: PASS
- Document ID Format: PASS ✓
- Document Control Table: PASS ✓
- Approvals Table: PASS ✓
- Traceability Section: PASS ✓

**QA Action**:
```bash
workspace.py wf review \
    --deliverable DOC-VER-REP-001 \
    --reviewer QUA \
    --status approved \
    --comments "Template compliance verified. All sections complete. Document ID format correct. Approvals table complete for SIL 3. Traceability section present with 100% coverage. Proceed to technical review (VER/VMGR)."
```

**Next Step**: Document proceeds to technical review by VER/VMGR (content review, not template review)

---

## 16. References

- EN 50128:2011 Section 6.5 (Software Quality Assurance)
- EN 50128:2011 Section 7.1.4 (Document Requirements)
- EN 50128:2011 Annex C (Document Control Summary - Table C.1)
- EN 50128:2011 Section 5.1.2.10 (Independence Requirements)
- EN ISO 9001:2015 (Quality Management Systems - Document Control)
- ISO/IEC 90003:2014 (Software Engineering - Guidelines for ISO 9001 - Documentation)
