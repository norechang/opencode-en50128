# EN 50128 Standard Document Header Template

**Purpose:** This template defines the mandatory header structure that ALL EN 50128 documents MUST follow.

**Applies to:** SRS, SAS, SDS, SQAP, SCMP, SVP, SVaP, Test Plans, Test Reports, Verification Reports, Validation Reports, and all other project deliverables.

**Standard Reference:** EN 50128:2011 Section 5 (Documentation), Annex C (Document Requirements)

---

## Mandatory Header Structure

```markdown
# [Document Title]

| Field | Value |
|-------|-------|
| **Document ID** | [DOC-TYPE-YYYY-NNN] |
| **Version** | [X.Y] |
| **Date** | [YYYY-MM-DD] |
| **Project** | [Project Name] |
| **SIL Level** | [0, 1, 2, 3, or 4] |
| **Author** | [Name, Role] |
| **Reviewer** | [Name, Role] |
| **Approver** | [Name, Role] |
| **Status** | [Draft \| Review \| Approved \| Baseline] |

---

## Document Control

| Version | Date | Author | Changes | Approval Status |
|---------|------|--------|---------|-----------------|
| 0.1 | YYYY-MM-DD | [Author Name] | Initial draft | Draft |
| 1.0 | YYYY-MM-DD | [Author Name] | First approved version | Approved |

---

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author** | [Author Name] | | YYYY-MM-DD |
| **Reviewer** | [Reviewer Name] | | YYYY-MM-DD |
| **QA Manager** | [QA Name] | | YYYY-MM-DD |
| **Safety Manager** | [Safety Name] | | YYYY-MM-DD |
| **Project Manager** | [PM Name] | | YYYY-MM-DD |

---

## Table of Contents

[Auto-generated based on document sections]

---

[Document content starts here]
```

---

## Document ID Format

**Format:** `DOC-<TYPE>-<YYYY>-<NNN>`

**Components:**
- `DOC` = Document prefix (constant)
- `<TYPE>` = Document type code (see table below)
- `<YYYY>` = Year (4 digits)
- `<NNN>` = Sequential number (3 digits, zero-padded)

**Document Type Codes:**

| Type Code | Document Type | Example |
|-----------|---------------|---------|
| `SQAP` | Software Quality Assurance Plan | DOC-SQAP-2026-001 |
| `SCMP` | Software Configuration Management Plan | DOC-SCMP-2026-001 |
| `SVP` | Software Verification Plan | DOC-SVP-2026-001 |
| `SVAP` | Software Validation Plan | DOC-SVAP-2026-001 |
| `SRS` | Software Requirements Specification | DOC-SRS-2026-001 |
| `SAS` | Software Architecture Specification | DOC-SAS-2026-001 |
| `SDS` | Software Design Specification | DOC-SDS-2026-001 |
| `STS` | Software Test Specification | DOC-STS-2026-001 |
| `STR` | Software Test Report | DOC-STR-2026-001 |
| `SVR` | Software Verification Report | DOC-SVR-2026-001 |
| `SVAR` | Software Validation Report | DOC-SVAR-2026-001 |
| `MISC` | Miscellaneous Document | DOC-MISC-2026-001 |

---

## Version Numbering

**Format:** `MAJOR.MINOR`

- **MAJOR version** (X): Incremented for:
  - Approved/baseline releases
  - Significant content changes
  - Document status change (Draft → Approved)
  
- **MINOR version** (.Y): Incremented for:
  - Draft revisions
  - Minor corrections
  - Review comments addressed

**Examples:**
- `0.1` = Initial draft
- `0.2` = Second draft revision
- `1.0` = First approved/baseline version
- `1.1` = Minor correction to approved document
- `2.0` = Second approved/baseline version (major update)

---

## Document Status Values

| Status | Description | Use When |
|--------|-------------|----------|
| `Draft` | Document under development | Initial creation, major revisions |
| `Review` | Document under review | Submitted for peer/QA/technical review |
| `Approved` | Document approved for use | Passed all reviews and approvals |
| `Baseline` | Document under configuration control | Included in project baseline |
| `Obsolete` | Document no longer valid | Superseded by newer version |

---

## Approval Signature Requirements

**SIL 0-1:**
- Author signature: Required
- Reviewer signature: Recommended
- QA Manager signature: Recommended

**SIL 2:**
- Author signature: Required
- Reviewer signature: Required
- QA Manager signature: Required

**SIL 3-4:**
- Author signature: Required
- Reviewer signature: Required (independent reviewer)
- QA Manager signature: Required
- Safety Manager signature: Required
- Independent Verifier/Validator signature: Required (for verification/validation documents)

---

## Template Compliance Checklist

**Quality Assurance (QA) and Verification (VER) SHALL verify:**

- [ ] Document ID follows format `DOC-<TYPE>-<YYYY>-<NNN>`
- [ ] Version number follows `MAJOR.MINOR` format
- [ ] All mandatory header fields completed (no empty cells)
- [ ] SIL level explicitly stated
- [ ] Document Control table present with version history
- [ ] Approvals table present with all required signatures
- [ ] Table of Contents present (for documents > 3 pages)
- [ ] Document status matches approval state
- [ ] Date format is YYYY-MM-DD (ISO 8601)

**Non-compliance Action:**
- QA/VER SHALL REJECT document if header template not followed
- Document status SHALL be marked as "Draft" until template compliance achieved

---

## References

- EN 50128:2011 Section 5 - Software Development Process
- EN 50128:2011 Annex C - Document Control Summary
- ISO/IEC 15289:2015 - Systems and software engineering - Content of life-cycle information items (documentation)
- IEEE Std 730-2014 - Software Quality Assurance Processes
