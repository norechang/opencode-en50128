# EN 50128 Document Templates

This directory contains standardized templates for all EN 50128 mandatory deliverables.

**Template Version:** 1.0  
**Last Updated:** 2026-02-18  
**Standard:** EN 50128:2011  

---

## Available Templates

### General Template
- **`DOCUMENT-HEADER-TEMPLATE.md`** - Mandatory header structure for ALL documents

### Planning Phase Templates
- **`SQAP-template.md`** - Software Quality Assurance Plan
- **`SCMP-template.md`** - Software Configuration Management Plan
- **`SVP-template.md`** - Software Verification Plan
- **`SVaP-template.md`** - Software Validation Plan

### Requirements Phase Templates
- **`SRS-template.md`** - Software Requirements Specification
- **`RTM-template.md`** - Requirements Traceability Matrix

### Design Phase Templates
- **`SAS-template.md`** - Software Architecture Specification
- **`SDS-template.md`** - Software Design Specification

### Implementation Phase Templates
- **`Code-Review-Checklist.md`** - Code review checklist
- **`Unit-Test-Spec-template.md`** - Unit test specification

### Testing Phase Templates
- **`Integration-Test-Spec-template.md`** - Integration test specification
- **`System-Test-Spec-template.md`** - System test specification

### Verification/Validation Templates
- **`Verification-Report-template.md`** - Verification report
- **`Validation-Report-template.md`** - Validation report

---

## Template Compliance Requirements

**ALL documents MUST:**
1. Use the standard header from `DOCUMENT-HEADER-TEMPLATE.md`
2. Follow the document structure defined in the specific template
3. Include all mandatory sections for the target SIL level
4. Be reviewed for template compliance by QA/VER before approval

**Template Compliance Verification:**
- **QUA (Quality Assurance)** verifies template compliance during document reviews
- **VER (Verification)** verifies template compliance during independent verification
- **Non-compliance** results in document rejection (returned to Draft status)

---

## How to Use These Templates

### Step 1: Select Template
Choose the appropriate template for your document type.

### Step 2: Copy Template
Copy the template to your project directory:
```bash
cp .opencode/skills/en50128-documentation/templates/SQAP-template.md \\
   docs/plans/SQAP.md
```

### Step 3: Fill In Header
Complete all fields in the standard header using values from `DOCUMENT-HEADER-TEMPLATE.md`:
- Document ID (format: DOC-TYPE-YYYY-NNN)
- Version (format: X.Y)
- Date (format: YYYY-MM-DD)
- All roles (Author, Reviewer, Approver)
- SIL Level

### Step 4: Complete Content
Replace all `[placeholders]` with project-specific information.

### Step 5: Delete Instructions
Remove all instruction sections (like "Instructions for Use") before submission.

### Step 6: Submit for Review
Submit document for QA review and template compliance verification.

---

## EN 50128 Document Requirements by SIL

### SIL 0-1
- Standard header: Recommended
- Document Control table: Recommended
- Approvals table: Recommended (Author + Reviewer)
- Template compliance: Recommended

### SIL 2
- Standard header: Required
- Document Control table: Required
- Approvals table: Required (Author + Reviewer + QA)
- Template compliance: Required

### SIL 3-4
- Standard header: **MANDATORY**
- Document Control table: **MANDATORY**
- Approvals table: **MANDATORY** (Author + Reviewer + QA + Safety Manager + Independent Verifier/Validator)
- Template compliance: **MANDATORY**

---

## Template Maintenance

**Template Owner:** Quality Assurance (QA) Manager

**Review Frequency:** Annually or when EN 50128 requirements change

**Change Control:** Template changes require:
1. QA Manager approval
2. Configuration Manager approval
3. Update to template version number
4. Notification to all project teams

---

## References

- EN 50128:2011 Section 5 - Documentation Requirements
- EN 50128:2011 Annex C - Document Control Summary
- ISO/IEC 15289:2015 - Life-cycle information items (documentation)

---

## Template Checklist

Before using any template, verify:

- [ ] Latest template version obtained
- [ ] Standard header structure understood
- [ ] SIL-specific requirements identified
- [ ] Project-specific placeholders prepared
- [ ] Review and approval process understood
