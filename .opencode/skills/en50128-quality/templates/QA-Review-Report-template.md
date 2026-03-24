# QUA Review Report

**TEMPLATE VERSION**: 3.0  
**REFERENCE**: EN 50128:2011 §6.5.4.5(c), §6.5.4.5(e)  
**PURPOSE**: FORMAT gate-check record — QUA checks document structure only

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | QUA-REVIEW-[YYYY]-[NNN] |
| **Version** | 1.0 |
| **Date** | [YYYY-MM-DD] |
| **Project** | [Project Name] |
| **SIL Level** | [0 \| 1 \| 2 \| 3 \| 4] |
| **Author** | [Name], QUA |
| **Status** | [Draft \| Final] |

## DOCUMENT CONTROL

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | YYYY-MM-DD | [Name] | Initial review report |

---

## 1. Review Identification

| Field | Value |
|-------|-------|
| **Review ID** | QUA-REVIEW-YYYY-NNN |
| **Review Type** | Format Gate Check |
| **Annex C Item** | [item number, e.g. 6] |
| **qua_check_type** | [template_compliance \| template_compliance_one_pass] |
| **Iteration** | [1 \| 2 \| 3] |
| **Document Reviewed** | [Document ID and title] |
| **Document Version** | [X.Y] |
| **Document Path** | [canonical path per CM] |
| **Review Date** | YYYY-MM-DD |
| **Reviewer** | [Name], QUA |

---

## 2. Generic Format Check Results

### GF-001 — Document ID Format

| Field | Result |
|-------|--------|
| Expected pattern | `DOC-[ABBREV]-[YYYY]-[NNN]` |
| Found | [value found or "NOT FOUND"] |
| Result | PASS / FAIL |

### GF-002 — Document Control Table

| Required field | Present | Non-empty |
|----------------|---------|-----------|
| Document ID | Yes / No | Yes / No |
| Version | Yes / No | Yes / No |
| Date | Yes / No | Yes / No |
| Author | Yes / No | Yes / No |
| Status | Yes / No | Yes / No |
| **Result** | **PASS / FAIL** | |

### GF-003 — Approvals Table

| Required role | Present |
|---------------|---------|
| Author | Yes / No |
| Reviewer (QUA) | Yes / No |
| Approver (PM) | Yes / No |
| **Result** | **PASS / FAIL** |

---

## 3. Required Sections Check

**Sections supplement loaded**: `review-criteria/sections/[doc-key]-sections.yaml`

| Section | Present |
|---------|---------|
| [Section heading 1] | Yes / No |
| [Section heading 2] | Yes / No |
| [Section heading N] | Yes / No |
| **Result** | **PASS / FAIL** |

---

## 4. Defect List

*(Complete if any check above is FAIL. Leave blank if all PASS.)*

| Defect ID | Rule | Location | Issue | Fix Required |
|-----------|------|----------|-------|-------------|
| D-001 | GF-001 | Document Control table | Document ID format incorrect | Update to DOC-[ABBREV]-YYYY-NNN |
| D-002 | SEC-003 | Document body | Section "3. Safety Requirements" missing | Add required section |

---

## 5. Overall Result

| | |
|-|-|
| **GF-001 Document ID** | PASS / FAIL |
| **GF-002 Document Control** | PASS / FAIL |
| **GF-003 Approvals Table** | PASS / FAIL |
| **Required Sections** | PASS / FAIL |
| **OVERALL** | **PASS / FAIL** |

---

## 6. Disposition

**If PASS**: Deliverable approved for next review step (VER 1st check / VMGR review).  
PM notified: all format checks satisfied. Deliverable may proceed.

**If FAIL**: Deliverable returned to author for defect correction.  
Iteration [N] of [3 / 1] permitted.  
Author must address all FAIL items before resubmission.

| Field | Value |
|-------|-------|
| **Disposition** | APPROVED FOR NEXT STEP / RETURNED TO AUTHOR |
| **Next step** | [VER 1st check \| VMGR review \| Author rework] |
| **Resubmission deadline** | [YYYY-MM-DD or phase gate] |
| **Escalation trigger** | [N/A \| Iteration limit reached — PM must escalate] |

---

*This report documents a FORMAT check only. It does not constitute technical review,
verification, or validation of document content. Technical content review is performed
by VER (§6.2) after QUA PASS.*
