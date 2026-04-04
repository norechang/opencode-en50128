# QUA Review Report — Item 18 (Iteration 2)
## Software Source Code and Supporting Documentation — TDC Project

---

## Document Control

| Field | Value |
|-------|-------|
| **Document ID** | QUA-REVIEW-ITEM18-2026-002 |
| **Version** | 1.0 |
| **Date** | 2026-04-04 |
| **Author** | QUA |
| **Status** | Final |

---

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Author (QUA) | QUA | QUA | 2026-04-04 |
| Approver (PM) | PM | ___ | ___ |

---

## 1. Review Summary

| Property | Value |
|----------|-------|
| **Project** | TDC (Train Door Control System) |
| **SIL Level** | 3 |
| **Phase** | 5 (Implementation and Testing) |
| **Annex C Item** | 18 (Software Source Code and supporting documentation) |
| **Document Reviewed** | DOC-SOURCECODE-2026-001 v1.0 |
| **Review Date** | 2026-04-04 |
| **Iteration Number** | 2 of 3 |
| **QUA Check Type** | `template_compliance` (standard format-gate) |
| **Overall Result** | ✅ **PASS** |

---

## 2. Review Scope

Per EN 50128:2011 §6.5 and `tasks/QUALITY_PROCESS.md`, QUA performs **FORMAT-GATE checking only**:

| Check | What QUA Verifies | What QUA Does NOT Verify |
|-------|-------------------|--------------------------|
| GF-001 | Document ID format matches `DOC-SOURCECODE-YYYY-NNN` | Code correctness, logic |
| GF-002 | Document Control table has 5 required fields | MISRA C compliance |
| GF-003 | Approvals table has Track A roles (Author, QUA, PM) | Cyclomatic complexity |
| GF-004 | Required sections present (Manifest, Build Instructions, Change Summary) | Static analysis results |
| — | Package structure | Traceability completeness (VER responsibility per §7.5.4.10) |

**Critical scope reminder**: QUA checks that Item 18 has proper **package documentation structure**. QUA does NOT review code quality, MISRA compliance, or verify that all design units are implemented — those are VER responsibilities under §7.5.4.10(c).

---

## 3. Iteration History

### 3.1 Iteration 1 (FAILED)

**Date**: 2026-04-04  
**Result**: ❌ FAIL — 4 defects found  
**Defects**:

| Defect ID | Rule | Description |
|-----------|------|-------------|
| DEFECT-18-001 | GF-001 | Document ID missing — no Document Control table present |
| DEFECT-18-002 | GF-002 | Document Control table missing all required fields |
| DEFECT-18-003 | GF-003 | Approvals table missing |
| DEFECT-18-004 | GF-004 | Required sections missing (Manifest, Build Instructions, Change Summary) |

**Root Cause**: IMP delivered source code files (`.c`, `.h`) without a formal package wrapper document containing Document Control metadata and required sections per §7.5.4.

**Remediation Required**: IMP to create `SOFTWARE-SOURCE-CODE-PACKAGE.md` as the Item 18 package wrapper document with all four defects addressed.

---

### 3.2 Iteration 2 (Current Review)

**Date**: 2026-04-04  
**Submission**: `examples/TDC/src/SOFTWARE-SOURCE-CODE-PACKAGE.md`  
**IMP Claims**: All four defects from iteration 1 fixed

---

## 4. Format-Gate Check Results (Iteration 2)

### 4.1 GF-001: Document ID Format

**Rule**: Document ID must match pattern `DOC-SOURCECODE-YYYY-NNN`

**Found** (line 10):
```
| **Document ID** | DOC-SOURCECODE-2026-001 |
```

**Check**:
- Pattern match: ✅ `DOC-SOURCECODE-2026-001` matches `DOC-SOURCECODE-YYYY-NNN`
- Abbreviation correct: ✅ `SOURCECODE` is correct for Annex C Item 18
- Year valid: ✅ 2026
- Sequence number: ✅ 001 (3 digits)

**Result**: ✅ **PASS**  
**Defect Status**: DEFECT-18-001 **CLOSED** (fixed)

---

### 4.2 GF-002: Document Control Table

**Rule**: Document Control table must have all 5 required fields: Document ID, Version, Date, Author, Status

**Found** (lines 6-14):

| Field | Value | Present? | Populated? |
|-------|-------|----------|------------|
| Document ID | `DOC-SOURCECODE-2026-001` | ✅ Yes | ✅ Yes |
| Version | `1.0` | ✅ Yes | ✅ Yes |
| Date | `2026-04-04` | ✅ Yes | ✅ Yes |
| Author | `IMP` | ✅ Yes | ✅ Yes |
| Status | `Draft` | ✅ Yes | ✅ Yes |

**Result**: ✅ **PASS** — all 5 fields present and populated  
**Defect Status**: DEFECT-18-002 **CLOSED** (fixed)

---

### 4.3 GF-003: Approvals Table

**Rule**: For SIL 3 Track A deliverables, Approvals table must have: Author, Reviewer (QUA), Approver (PM)

**Found** (lines 18-24):

| Required Role | Found in Table | Name | Status |
|---------------|----------------|------|--------|
| Author | ✅ Yes (line 22) | `IMP` | Signed |
| Reviewer (QUA) | ✅ Yes (line 23) | `QUA` | Pending |
| Approver (PM) | ✅ Yes (line 24) | `PM` | Pending |

**Table Structure Check**:
- Required columns present: ✅ Role, Name, Signature, Date
- Track A roles correct: ✅ Author (IMP), Reviewer (QUA), Approver (PM)

**Result**: ✅ **PASS** — all 3 required Track A roles present with correct structure  
**Defect Status**: DEFECT-18-003 **CLOSED** (fixed)

**Note**: QUA and PM signatures are pending — this is correct for iteration 2 (QUA signs upon PASS; PM signs after VER approval).

---

### 4.4 GF-004: Required Sections

**Rule**: Per `sourcecode-sections.yaml`, the following sections are mandatory:
1. Source Code Package Manifest
2. Build Instructions
3. Change Summary

**Found**:

| Required Section | Found? | Location | Content Present? |
|------------------|--------|----------|------------------|
| Source Code Package Manifest | ✅ Yes | Line 50: `## 2. Source Code Package Manifest` | ✅ Yes (§2.1–§2.4) |
| Build Instructions | ✅ Yes | Line 112: `## 3. Build Instructions` | ✅ Yes (§3.1–§3.7) |
| Change Summary | ✅ Yes | Line 216: `## 4. Change Summary` | ✅ Yes (table + detail) |

**Section Content Verification** (format only — QUA does not verify technical correctness):

#### §2. Source Code Package Manifest
- ✅ §2.1 Header Files: 9 files listed with SHA-256 hashes
- ✅ §2.2 Implementation Files: 21 files listed with SHA-256 hashes
- ✅ §2.3 Supporting Documentation: 1 file (`TRACEABILITY.md`)
- ✅ §2.4 Summary: Total file count (31 files)

#### §3. Build Instructions
- ✅ §3.1 Compiler Requirements (table format)
- ✅ §3.2 Mandatory Compiler Flags (code block)
- ✅ §3.3 Include Paths
- ✅ §3.4 Build Commands
- ✅ §3.5 Example Makefile Fragment
- ✅ §3.6 Dependencies (table)
- ✅ §3.7 Static Analysis Results (informational — VER verifies in Item 19)

#### §4. Change Summary
- ✅ Change table with Version, Date, Author, Description
- ✅ Change detail paragraph
- ✅ Deviation record (DEV-001, DEV-002 documented)

**Result**: ✅ **PASS** — all 3 required sections present with proper formatting  
**Defect Status**: DEFECT-18-004 **CLOSED** (fixed)

---

## 5. Additional Observations (Informational — Not Defects)

### 5.1 File Count Verification

**Manifest declares**: 31 total files (9 `.h` + 21 `.c` + 1 `TRACEABILITY.md`)

**QUA Note**: QUA checks that a manifest **exists** and is **formatted properly**. QUA does NOT verify:
- That all 31 files physically exist on disk
- That SHA-256 hashes are correct
- That the file list is complete relative to SCDS DOC-COMPDES-2026-001

These are **VER responsibilities** per §7.5.4.10(c) (Software Code Verification, Item 19).

---

### 5.2 File Location Discrepancy (CM Responsibility)

**Observation**: The package manifest document is currently located at:
```
examples/TDC/src/SOFTWARE-SOURCE-CODE-PACKAGE.md
```

**CM canonical path** (per CM query-location):
```
examples/TDC/docs/phase-5-implementation-testing/src/SOFTWARE-SOURCE-CODE-PACKAGE.md
```

**QUA Disposition**: This is a **CM configuration management issue**, not a QUA format-gate defect. The document itself meets all format requirements (GF-001 through GF-004). File placement is under CM authority per EN 50128:2011 §6.6.

**Recommendation**: QUA recommends PM route to CM for canonical path relocation before baseline creation at gate-check. This does not block QUA PASS, but should be resolved before final Phase 5 gate approval.

---

### 5.3 Static Analysis Results (§3.7)

**Observation**: IMP has included static analysis results in §3.7:
- cppcheck: PASS (0 errors, 0 warnings)
- lizard: PASS (Max CCN 10, within SIL-3 limit)

**QUA Disposition**: QUA acknowledges this information is present. QUA does NOT verify the accuracy or completeness of these results. **VER is responsible** for independent static analysis verification per §7.5.4.10(c) and will produce Item 19 (Software Code Verification Report) to confirm:
- MISRA C:2012 mandatory rule compliance
- Cyclomatic complexity CCN ≤ 10 for all functions (SIL 3)
- Static analysis tool evidence

This is **informational only** for QUA purposes — not a format-gate criterion.

---

## 6. Overall Assessment

### 6.1 Iteration 2 Summary

| Check | Iteration 1 Status | Iteration 2 Status | Fixed? |
|-------|-------------------|-------------------|--------|
| GF-001: Document ID Format | ❌ FAIL | ✅ PASS | ✅ Yes |
| GF-002: Document Control Table | ❌ FAIL | ✅ PASS | ✅ Yes |
| GF-003: Approvals Table | ❌ FAIL | ✅ PASS | ✅ Yes |
| GF-004: Required Sections | ❌ FAIL | ✅ PASS | ✅ Yes |

**All four defects from iteration 1 have been successfully remediated.**

---

### 6.2 Final Determination

**QUA Review Result**: ✅ **PASS**

**Rationale**:
- Document ID format compliant (GF-001): ✅
- Document Control table complete (GF-002): ✅
- Approvals table structure correct (GF-003): ✅
- All required sections present (GF-004): ✅
- Package manifest structure meets EN 50128:2011 §7.5.4 format requirements

**Format-gate approval**: Item 18 (DOC-SOURCECODE-2026-001 v1.0) is **approved for Track A handoff to VER**.

---

### 6.3 Iteration Count

- Iteration 1: FAIL (4 defects)
- Iteration 2: PASS (0 defects)
- **Total iterations used**: 2 of 3 allowed

**Iteration limit status**: Within acceptable range. No NCR raised. No PM escalation required.

---

## 7. Next Steps (Track A Workflow)

Per `WORKFLOW.md` Diagram 1 (Two-Track Execution Loop) and `tasks/QUALITY_PROCESS.md` Diagram 2:

1. ✅ **QUA signs Approvals table** (Reviewer role) — indicates format-gate PASS
2. **PM receives QUA PASS notification** — Item 18 cleared for VER submission
3. **PM submits Item 18 to VER** — VER performs Software Code Verification per §7.5.4.10:
   - MISRA C:2012 compliance check (mandatory rules at SIL 3)
   - Cyclomatic complexity verification (CCN ≤ 10)
   - Static analysis evidence review
   - Design-to-code traceability verification (T8: SCDS → Source Code)
   - VER produces Item 19 (Software Code Verification Report)
4. **VER report → QUA format-gate** (1-Pass Rule for VER reports per `template_compliance_one_pass`)
5. **VER report → VMGR for technical review** (Track B — independent verification authority)
6. **VMGR approves or rejects Item 19** — if approved, VER report baseline is created
7. **PM may proceed to gate-check** once Item 19 (VER) + Item 20 (Component Test Report) are VMGR-approved

---

## 8. QUA Signature

By signing this report, QUA certifies that:

✅ Item 18 (DOC-SOURCECODE-2026-001 v1.0) meets all format-gate requirements (GF-001 through GF-004)  
✅ All defects from iteration 1 have been successfully remediated  
✅ The deliverable is structurally compliant with EN 50128:2011 §7.5.4 package documentation requirements  
✅ QUA has performed FORMAT checking only — technical content verification is VER responsibility  

**QUA Reviewer**: QUA  
**Signature**: QUA  
**Date**: 2026-04-04  

---

## 9. References

| Document | ID | Description |
|----------|----|-------------|
| EN 50128:2011 | — | Railway software standard — §6.5 (QA), §7.5.4 (Code Implementation) |
| tasks/QUALITY_PROCESS.md | — | QUA role definition, two-track workflow, iteration limits |
| WORKFLOW.md | — | Track A/B execution loop, QUA gate position |
| Item 18 (reviewed) | DOC-SOURCECODE-2026-001 v1.0 | Software Source Code and supporting documentation |
| QUA Iteration 1 Report | QUA-REVIEW-ITEM18-2026-001 | Previous review (FAIL — 4 defects) |
| sourcecode-sections.yaml | — | Required sections definition for Item 18 |
| generic-format-checker.yaml | — | GF-001 through GF-004 rule definitions |

---

*End of QUA Review Report — Item 18 Iteration 2 — QUA-REVIEW-ITEM18-2026-002 v1.0*
