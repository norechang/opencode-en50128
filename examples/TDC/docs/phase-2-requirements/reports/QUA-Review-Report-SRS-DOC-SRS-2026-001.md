# QUA Review Report — Software Requirements Specification

**REVIEW REPORT METADATA**

| Field | Value |
|-------|-------|
| **Report ID** | QUA-REVIEW-2026-001 |
| **Review Date** | 2026-04-02 |
| **Reviewer Role** | Quality Assurance Engineer (QUA) |
| **Reviewer Name** | [QUA Name] |
| **Review Type** | Format-Gate Check (Track A) |
| **Iteration** | 1 of 3 |

---

## DOCUMENT UNDER REVIEW

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SRS-2026-001 |
| **Document Title** | Software Requirements Specification (SRS) |
| **Version** | 0.1 DRAFT |
| **Date** | 2026-04-02 |
| **Annex C Item** | 6 (Software Requirements Specification) |
| **Author** | Requirements Engineer (REQ) |
| **SIL Level** | SIL 3 |
| **Project** | TDC (Train Door Control System) |
| **Phase** | 2 (Requirements Specification) |

---

## REVIEW SCOPE

This QUA review is a **FORMAT-GATE CHECK** per EN 50128 §6.5 and `tasks/QUALITY_PROCESS.md`. QUA checks FORMAT and STRUCTURE only:

| Check | Description |
|-------|-------------|
| **GF-001** | Document ID format: `DOC-<ABBREV>-<YYYY>-<NNN>` |
| **GF-002** | Document Control table: 5 required fields present and non-empty |
| **GF-003** | Approvals table: correct columns and Track A roles (Author, QUA, PM) |
| **GF-004** | Required sections: all mandatory SRS sections present |

**QUA does NOT check**:
- Technical correctness of requirements (VER responsibility)
- MISRA C compliance (VER responsibility)
- Traceability link completeness (VER responsibility per `TRACEABILITY.md` T1-T15)
- Test adequacy (TST responsibility)
- Safety analysis content (SAF responsibility)

---

## AUDIT FINDINGS

### Finding GF-002-A: Document Control Table Structure
- **Rule**: GF-002 (Document Control Table)
- **Severity**: MEDIUM
- **Location**: Lines 8-26 (STANDARD HEADER and DOCUMENT CONTROL sections)
- **Description**: The document contains TWO tables where ONE "Document Control" table is expected:
  - A "STANDARD HEADER" table (lines 10-20) contains all required Document Control fields (Document ID, Version, Date, Author, Status) plus additional fields (Project, SIL Level, Reviewer, Approver).
  - A "DOCUMENT CONTROL" table (lines 22-26) appears to be a version history table with different fields (Version, Date, Author, Changes, Approved By).
  - **Result**: Ambiguous — unclear which table is the official Document Control table.
- **Required**: A single table labeled "DOCUMENT CONTROL" with exactly the five required fields: Document ID, Version, Date, Author, Status (all non-empty).
- **Fix Suggestion**: 
  1. Rename the "STANDARD HEADER" table to "DOCUMENT CONTROL".
  2. Keep the five required fields: Document ID, Version, Date, Author, Status.
  3. Optional additional fields (Project, SIL Level) are permitted but not required.
  4. Rename the second "DOCUMENT CONTROL" table to "VERSION HISTORY" or "DOCUMENT HISTORY" if you wish to retain the version change log.

---

### Finding GF-003-A: Approvals Table Format Non-Compliance
- **Rule**: GF-003 (Approvals Table)
- **Severity**: HIGH
- **Location**: Lines 28-44 (APPROVALS section)
- **Description**: The Approvals table uses non-standard column headers and structure:
  - **Found**: Columns "Written By", "1st Check", "2nd Check", "Date"
  - **Required**: Columns "Role", "Name", "Signature", "Date"
  - **Issue**: The table does not separate Role, Name, and Signature into distinct columns. Each cell contains multi-line text with role, name placeholder, and signature line combined.
- **Required Format**:
```markdown
## APPROVALS

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Author | [Name] | _____________ | 2026-04-02 |
| Reviewer (QUA) | [Name] | _____________ | [Date] |
| Approver (PM) | [Name] | _____________ | [Date] |
```
- **Fix Suggestion**: Replace the Approvals table with the standard four-column format (Role, Name, Signature, Date) and separate the multi-line content into distinct columns.

---

### Finding GF-003-B: Approvals Table Incorrect Roles (CRITICAL)
- **Rule**: GF-003 (Approvals Table — Track A Roles)
- **Severity**: HIGH
- **Location**: Lines 32-34 (APPROVALS table roles)
- **Description**: The Approvals table lists the following roles:
  - "Written By": Requirements Engineer (REQ)
  - "1st Check": Software Verifier (VER)
  - "2nd Check": Software Validator (VAL)
  
  **This is INCORRECT for a Track A development deliverable.**
  
  Per EN 50128 two-track approval model (`WORKFLOW.md` Diagram 1-2, `tasks/QUALITY_PROCESS.md` Diagram 2):
  - **Track A (development deliverable sign-off)**: Author → QUA → PM
  - **Track B (independent V&V review)**: VER → VMGR, VAL → VMGR (separate from Approvals table)
  
  VER and VAL are **Track B roles** — they review the deliverable AFTER QUA approves the format and PM accepts the document for phase gate submission. VER and VAL DO NOT sign the Approvals table on development deliverables.
  
- **Required Roles** (Track A): Author, Reviewer (QUA), Approver (PM)
- **Fix Suggestion**: 
  1. Remove VER and VAL from the Approvals table.
  2. Replace with the Track A sign-off chain:
     - **Author**: Requirements Engineer (REQ)
     - **Reviewer (QUA)**: Quality Assurance Engineer (QUA)
     - **Approver (PM)**: Project Manager (PM)
  3. VER and VAL reviews occur AFTER PM approval, in Track B. Their review outcomes are recorded in separate VER and VAL reports (Annex C items 8, 25), not in the SRS Approvals table.

---

## PASSED CHECKS

### GF-001: Document ID Format — PASS ✅
- **Expected**: `DOC-SRS-YYYY-NNN`
- **Found**: `DOC-SRS-2026-001` (line 12)
- **Status**: PASS — Document ID matches required format.

---

### GF-004: Required Sections — PASS ✅
**Required Sections** (per `srs-sections.yaml`):
- ✅ Introduction (Section 1, line 47)
- ✅ System Context (Section 2.1, line 173)
- ✅ Software Requirements (Section 3, line 273)
- ✅ Safety Requirements (Section 3.4, line 1005)
- ✅ Interface Requirements (Section 3.3, line 757)
- ✅ Constraints (Section 2.4, line 232)
- ✅ Traceability (Section 4.2, line 1566)
- ✅ Glossary (Section 1.4, line 104)

**Status**: PASS — All required sections present and correctly labeled.

---

## SUMMARY STATISTICS

| Metric | Value |
|--------|-------|
| **Total Findings** | 3 |
| **HIGH Severity** | 2 (GF-003-A, GF-003-B) |
| **MEDIUM Severity** | 1 (GF-002-A) |
| **LOW Severity** | 0 |
| **Rules Checked** | 4 (GF-001, GF-002, GF-003, GF-004) |
| **Rules Passed** | 2 (GF-001, GF-004) |
| **Rules Failed** | 2 (GF-002, GF-003) |
| **Iteration** | 1 of 3 |
| **QUA Check Type** | `template_compliance` (3 iterations permitted) |

---

## FINAL RECOMMENDATION

**STATUS**: ❌ **FAIL** — Document RETURNED to REQ for format corrections.

**Rationale**: The document has TWO HIGH severity findings (GF-003-A, GF-003-B) and ONE MEDIUM severity finding (GF-002-A). These are structural format defects that must be corrected before the document can proceed to VER review (Track B).

**Critical Issues**:
1. **Approvals table roles are incorrect** (GF-003-B) — VER and VAL are Track B roles and SHALL NOT appear in the Approvals table for Track A development deliverables. The required Track A sign-off chain is: Author (REQ) → Reviewer (QUA) → Approver (PM).
2. **Approvals table format is non-standard** (GF-003-A) — Column headers must be: Role, Name, Signature, Date (four separate columns).
3. **Document Control table is duplicated/ambiguous** (GF-002-A) — Two tables exist where one "DOCUMENT CONTROL" table is required with exactly five fields.

**Impact**: These format defects violate EN 50128 §6.5 document control requirements and the platform's two-track approval model. The document cannot proceed to VER until the Approvals table correctly reflects Track A roles only and the Document Control table is unambiguous.

**Iteration Status**: This is iteration **1 of 3** in the QUA format-gate loop. REQ has **two more opportunities** to correct and resubmit before escalation to PM is required.

**Next Steps**:
1. PM SHALL route this review report to REQ for correction.
2. REQ SHALL address all three findings (GF-002-A, GF-003-A, GF-003-B).
3. REQ SHALL resubmit the corrected SRS to QUA for iteration 2 review.
4. QUA SHALL re-review the resubmitted document. If findings remain after iteration 3, PM SHALL escalate per SQAP process failure procedure.

---

## QUA CERTIFICATION

**QUA Review Completed**: 2026-04-02  
**Reviewed By**: Quality Assurance Engineer (QUA)  
**Signature**: _____________  
**Date**: 2026-04-02

**Quality Standard**: EN 50128:2011 §6.5 (Software Quality Assurance)  
**Review Criteria**: Generic Format Checker (GF-001 to GF-004) per `en50128-quality` skill  
**SRS Sections Checklist**: `review-criteria/sections/srs-sections.yaml`  
**Authority**: `tasks/QUALITY_PROCESS.md` (ISA PASS)  

---

**END OF QUA REVIEW REPORT**
