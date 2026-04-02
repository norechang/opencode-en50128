# QUA Self-Review Report — SQAP

**DOCUMENT TYPE**: QUA Working Document (Not an Annex C deliverable)  
**PURPOSE**: Document QUA self-review of SQAP per deviation D8  
**DATE**: 2026-04-02  
**REVIEWER**: Quality Assurance Engineer (QUA)

---

## DOCUMENT UNDER REVIEW

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SQAP-2026-001 |
| **Document Name** | Software Quality Assurance Plan |
| **Annex C Item** | 1 |
| **Version** | 1.0 |
| **Date** | 2026-04-02 |
| **Author** | QUA |
| **Path** | `/home/norechang/test/opencode-en50128/examples/TDC/docs/phase-1-planning/Software-Quality-Assurance-Plan.md` |

---

## REVIEW CONTEXT

**QUA Check Type**: Self-review (deviation D8 special case)

**Deviation D8**: Per DELIVERABLES.md and SQAP Section 1.2, QUA authors the SQAP under VER direction and responsibility (§6.5.4.3). QUA CANNOT perform the 2nd check on its own plan due to self-certification conflict. This self-review is for FORMAT ONLY to ensure the document meets basic template requirements before submission to VER for 1st check.

**Iteration**: 1 of 3 (standard template_compliance check type)

---

## FORMAT-GATE CHECKS

### GF-001: Document ID Format

**Rule**: Document ID must match pattern `DOC-<ABBREV>-<YYYY>-<NNN>` where ABBREV = "SQAP"

**Expected**: `DOC-SQAP-YYYY-NNN`

**Actual**: `DOC-SQAP-2026-001`

**Result**: ✅ **PASS**

---

### GF-002: Document Control Table

**Rule**: Document Control table must be present with all five required fields populated and non-empty.

**Required Fields**:
- Document ID
- Version
- Date
- Author
- Status

**Actual** (from lines 11-21):
```
| Field | Value |
|-------|-------|
| **Document ID** | DOC-SQAP-2026-001 |
| **Version** | 1.0 |
| **Date** | 2026-04-02 |
| **Project** | TDC (Train Door Control System) |
| **SIL Level** | SIL 3 |
| **Author** | Quality Assurance Engineer (QUA) |
| **Status** | DRAFT — Awaiting VER 1st Check |
```

**Result**: ✅ **PASS** — All five required fields present and non-empty

---

### GF-003: Approvals Table

**Rule**: Approvals table must be present with columns Role, Name, Signature, Date and roles: Author, 1st Check (VER), 2nd Check (VAL), Approver (PM) for SIL 3.

**Expected Roles** (SIL 3, Track A development deliverable):
- Author (QUA)
- 1st Check (VER)
- 2nd Check (VAL)
- Approver (PM)

**Actual** (from lines 34-41):
```
| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author (QUA)** | [QUA Name] | [PENDING] | [PENDING] |
| **1st Check (VER)** | [VER Name] | [PENDING] | [PENDING] |
| **2nd Check (VAL)** | [VAL Name] | [PENDING] | [PENDING] |
| **Approver (PM)** | [PM Name] | [PENDING] | [PENDING] |
```

**Note**: Deviation D8 is correctly documented in line 43: "Per deviation D8 (DELIVERABLES.md), QUA authors the SQAP under VER direction and responsibility (§6.5.4.3). QUA cannot perform the 2nd check on its own document due to self-certification conflict. VER performs 1st check; VAL performs 2nd check."

**Result**: ✅ **PASS** — Approvals table correct; deviation D8 documented

---

### GF-004: Required Sections

**Rule**: All required sections per `sqap-sections.yaml` must be present.

**Required Sections** (from `review-criteria/sections/sqap-sections.yaml`):

| # | Required Heading | Notes | Present? |
|---|------------------|-------|----------|
| 1 | "Introduction" | Document purpose, scope, applicable standards | ✅ Yes (Section "INTRODUCTION") |
| 2 | "Lifecycle Model" | §6.5.4.5(a): activities, entry/exit criteria, I/O, quality activities, responsible entities | ✅ Yes (Section "2. LIFECYCLE MODEL") |
| 3 | "Documentation Structure" | §6.5.4.5(b) | ✅ Yes (Section "3. DOCUMENTATION STRUCTURE") |
| 4 | "Documentation Control" | §6.5.4.5(c): roles for write/check/approval, distribution, archiving | ✅ Yes (Section "4. DOCUMENTATION CONTROL") |
| 5 | "Deviations" | §6.5.4.5(d): tracking and tracing of deviations; platform deviations D1–D8 must be listed | ✅ Yes (Section "Platform Deviations" in INTRODUCTION) |
| 6 | "Quality Assurance Methods" | §6.5.4.5(e): techniques per Table A.9 for the project SIL level | ✅ Yes (Section "7. METHODS, MEASURES AND TOOLS") |
| 7 | "Technique Selection Justification" | §6.5.4.5(f): justification per §4.7–4.9 for each technique selection | ✅ Yes (Section "7.1 EN 50128 Table A.9 Techniques for SIL 3" includes justification column) |
| 8 | "Update Procedure" | §6.5.4.9: frequency, responsibility, method for plan updates | ✅ Yes (Section "4.3 Document Update Procedure") |
| 9 | "Role Assignments" | Who performs QUA, VER, VAL, CM roles; independence declarations | ✅ Yes (Section "1.5 Role Assignments") |

**Result**: ✅ **PASS** — All 9 required sections present

---

## OVERALL RESULT

**Format-Gate Outcome**: ✅ **PASS**

**Defects Found**: 0

**Iteration Count**: 1

---

## DISPOSITION

Per deviation D8, this self-review confirms the SQAP meets FORMAT requirements (GF-001, GF-002, GF-003, GF-004).

**Next Step**: Submit SQAP to VER for 1st check (technical content verification).

**Note**: QUA self-review does NOT constitute a formal QUA check per the two-track workflow. VER performs the 1st check; VAL performs the 2nd check. This self-review is a working document only.

---

## SIGN-OFF

| Field | Value |
|-------|-------|
| **Reviewed By** | Quality Assurance Engineer (QUA) |
| **Date** | 2026-04-02 |
| **Outcome** | PASS (format only) |
| **Next Action** | Forward to VER for technical verification |

---

**END OF QUA SELF-REVIEW REPORT**
