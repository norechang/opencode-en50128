# QUA Review Report — Software Source Code (Item 18)

## Document Control

| Field | Value |
|-------|-------|
| **Document ID** | QUA-REVIEW-ITEM18-2026-001 |
| **Version** | 1.0 |
| **Date** | 2026-04-04 |
| **Author** | QUA (Quality Assurance Engineer) |
| **Status** | Review Complete |

---

## Review Summary

| Property | Value |
|----------|-------|
| **Deliverable Reviewed** | Software Source Code and Supporting Documentation (Item 18) |
| **Annex C Item** | 18 |
| **Phase** | Phase 5 (Implementation and Testing) |
| **Project** | TDC (Train Door Control System) |
| **SIL Level** | 3 |
| **Document Type** | SOURCECODE |
| **QUA Check Type** | `template_compliance` (3 iteration limit) |
| **Iteration Number** | **1 of 3** |
| **Submitted By** | IMP (Implementer) |
| **Submission Path** | `examples/TDC/src/` (30 files: 21 .c + 9 .h + TRACEABILITY.md) |

---

## Review Scope

Per EN 50128:2011 §6.5 and `tasks/QUALITY_PROCESS.md`, QUA checks **FORMAT and PACKAGE STRUCTURE only** for Item 18 (Software Source Code). QUA does **NOT** check:

- ❌ Code correctness, MISRA C compliance, or static analysis results (VER responsibility per §7.5.4.10(c))
- ❌ Cyclomatic complexity values (VER responsibility)
- ❌ Traceability link completeness (VER responsibility per TRACEABILITY.md T-rules)
- ❌ Test coverage adequacy (TST/VER responsibility)

QUA checks:
- ✅ Document ID format (GF-001)
- ✅ Document Control table (GF-002)
- ✅ Approvals table (GF-003)
- ✅ Required sections (GF-004):
  - Source Code Package Manifest
  - Build Instructions
  - Change Summary

---

## Review Execution

### Active Workspace Context

```
Active Workspace: TDC (SIL 3)
Phase: Phase 4 (Component Design) — ✅ COMPLETE
Completion: 60% (Phases 1-4 complete and gate-passed; Phase 5 authorized to begin)
Path: examples/TDC/
```

### Canonical Path Confirmation

✅ **CM Query**: Canonical path for Item 18 confirmed as `examples/TDC/src/`

### Deliverable Metrics (Informational — NOT QUA-checked)

| Metric | Value | SIL 3 Target | Technical Owner |
|--------|-------|--------------|-----------------|
| Total functions | 99 (97 design units + 2 helpers) | 97 | VER verifies |
| cppcheck | 0 errors, 0 warnings | Clean | VER verifies |
| lizard CCN | Max 10 (at SIL 3 limit) | ≤10 | VER verifies |
| MISRA C:2012 | Zero mandatory violations claimed | 0 | VER verifies |
| Dynamic memory | None claimed | Prohibited | VER verifies |
| Recursion | None claimed | Prohibited | VER verifies |
| Function pointers | None claimed | Prohibited (HR) | VER verifies |
| Traceability | 100% per TRACEABILITY.md | 100% | VER verifies |

**QUA Position**: Above metrics are **NOTED but NOT verified** by QUA. VER has full authority to independently verify these claims in Item 19 (Software Source Code Verification Report).

---

## Format Review Results

### Rule GF-001: Document ID Format

**Status**: ❌ **FAIL**

**Check**: Document Control table must contain a Document ID field matching pattern `DOC-SOURCECODE-YYYY-NNN`.

**Finding**: **No Document Control table found** in the submitted package.

**Location Checked**:
- `src/TRACEABILITY.md` — Contains informal document ID `DOC-SRCCODE-2026-001-TRACE` on line 4, but this is embedded in a traceability matrix, NOT in a formal Document Control table.
- No package-level README, MANIFEST, or formal deliverable wrapper document found.

**Expected**: A formal package manifest document (e.g., `src/PACKAGE-MANIFEST.md`) with:
```markdown
## Document Control

| Field | Value |
|-------|-------|
| Document ID | DOC-SOURCECODE-2026-001 |
| Version | 1.0 |
| Date | 2026-04-04 |
| Author | IMP |
| Status | Draft |
```

**Severity**: ERROR

---

### Rule GF-002: Document Control Table

**Status**: ❌ **FAIL**

**Check**: Document Control table with five required fields (Document ID, Version, Date, Author, Status) must be present and non-empty.

**Finding**: **No Document Control table found**.

**Location Checked**:
- `src/TRACEABILITY.md` — No Document Control table (has informal header fields on lines 4–9, but not structured as a formal table).
- No package-level manifest document.

**Expected**: Document Control table with all five fields populated in a formal package manifest.

**Severity**: ERROR

---

### Rule GF-003: Approvals Table

**Status**: ❌ **FAIL**

**Check**: Approvals table with columns Role/Name/Signature/Date and minimum required roles (Author, Reviewer (QUA), Approver (PM)) must be present.

**Finding**: **No Approvals table found** in the submitted package.

**Location Checked**:
- `src/TRACEABILITY.md` — No Approvals table.
- No package-level manifest document.

**Expected**: Approvals table in package manifest:
```markdown
## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Author | IMP | ___ | YYYY-MM-DD |
| Reviewer (QUA) | QUA | ___ | YYYY-MM-DD |
| Approver (PM) | PM | ___ | YYYY-MM-DD |
```

**Note**: VER, VAL, VMGR are Track B roles — they do NOT appear in the Approvals table on development deliverables. Track A sign-off only.

**Severity**: ERROR

---

### Rule GF-004: Required Sections

**Status**: ❌ **FAIL** (3 of 3 required sections missing)

**Check**: Per `sourcecode-sections.yaml`, three mandatory sections must be present:
1. **Source Code Package Manifest** — list of all source files with version/hash
2. **Build Instructions** — how to compile; compiler version, flags, target
3. **Change Summary** — what changed relative to previous delivery (or 'Initial release')

**Findings**:

| Required Section | Status | Finding |
|------------------|--------|---------|
| Source Code Package Manifest | ❌ MISSING | `TRACEABILITY.md` §1 provides file-to-component mapping but NOT a formal manifest with version/hash/baseline metadata |
| Build Instructions | ❌ MISSING | No Makefile, build.sh, BUILD.md, or build instructions found in `src/` |
| Change Summary | ❌ MISSING | No change summary or release notes section |

**Location Checked**:
- `src/TRACEABILITY.md` — Excellent technical content (unit-to-function mapping, requirements coverage, static analysis results summary), but **missing the three required package structure sections**.
- `src/` directory — No Makefile, no BUILD.md, no README.md, no PACKAGE-MANIFEST.md.

**Expected Structure**:

A formal package manifest document (e.g., `src/SOFTWARE-SOURCE-CODE-PACKAGE.md`) with:

```markdown
# Software Source Code — Item 18
## TDC Train Door Control System

## Document Control
[Document ID table as per GF-002]

## Approvals
[Approvals table as per GF-003]

## Source Code Package Manifest
| File | Component | Module | SCDS Ref | Version | SHA-256 Hash |
|------|-----------|--------|----------|---------|--------------|
| tdc_types.h | Shared | — | SCDS §2 | 1.0 | <hash> |
| skn_comparator.c | SKN | MOD-SKN-001 | SCDS §3.1 | 1.0 | <hash> |
[... all 30 files listed]

## Build Instructions
### Compiler
- GCC 11.2.0 or later
- Target: ARM Cortex-M4
- Flags: -std=c11 -Wall -Wextra -O2 -DSIL_LEVEL=3

### Build Command
```bash
make clean
make all TARGET=arm-cortex-m4
```

### Dependencies
- CMSIS 5.8.0
- Unity 2.5.2 (for tests/)

## Change Summary
Initial release — first delivery of TDC source code package (Phase 5).
```

**Severity**: ERROR (3 missing sections)

---

## Overall Review Result

### Decision: ❌ **FAIL**

**Reason**: Four critical format defects (GF-001, GF-002, GF-003, GF-004) prevent QUA acceptance. The submitted package contains **excellent source code** with comprehensive headers and a detailed `TRACEABILITY.md` document, but it **lacks the formal package structure** required by EN 50128 deliverable format standards.

**Defect Count**: 4 errors (all severity=ERROR)

**Confidence**: **HIGH** — QUA format rules are unambiguous; defects are clear-cut.

---

## Defect List

| ID | Rule | Severity | Location | Fix Suggestion |
|----|------|----------|----------|----------------|
| **DEFECT-18-001** | GF-001 | ERROR | Package root | Create `src/SOFTWARE-SOURCE-CODE-PACKAGE.md` with Document Control table containing Document ID = `DOC-SOURCECODE-2026-001` |
| **DEFECT-18-002** | GF-002 | ERROR | Package root | Add Document Control table with all five fields (Document ID, Version, Date, Author, Status) to package manifest |
| **DEFECT-18-003** | GF-003 | ERROR | Package root | Add Approvals table with columns Role/Name/Signature/Date and roles: Author, Reviewer (QUA), Approver (PM) |
| **DEFECT-18-004** | GF-004 | ERROR | Package root | Add three required sections to package manifest: (1) Source Code Package Manifest (file list with version/hash), (2) Build Instructions (compiler, flags, commands), (3) Change Summary (initial release or delta from prior version) |

---

## Remediation Guidance

### Recommended Action

IMP shall create a formal package manifest document (suggested filename: `src/SOFTWARE-SOURCE-CODE-PACKAGE.md`) that serves as the **deliverable wrapper** for Item 18. This document shall contain:

1. **Document Control table** (GF-002) with Document ID = `DOC-SOURCECODE-2026-001` (GF-001)
2. **Approvals table** (GF-003) with Track A sign-off roles
3. **Source Code Package Manifest** (GF-004) — table of all 30 files with version/hash metadata
4. **Build Instructions** (GF-004) — compiler, flags, build commands, dependencies
5. **Change Summary** (GF-004) — "Initial release" for first delivery

The existing `TRACEABILITY.md` is **excellent technical content** and should be **retained** as supporting documentation. It provides unit-to-function mapping, requirements coverage, and static analysis summary — all valuable for VER review. However, it does not replace the formal package manifest.

### QUA Check Type and Iteration Limit

- **QUA Check Type**: `template_compliance` (standard development deliverable)
- **Iteration Limit**: **3 iterations** (this is iteration 1 of 3)
- **Next Step**: IMP creates package manifest → resubmits to PM → PM routes to QUA for iteration 2 review

---

## Non-Conformance Report

**NCR Trigger**: Not required at iteration 1. If iteration 3 also results in FAIL, QUA shall raise NCR against IMP and escalate to PM for mandatory training intervention per `en50128-quality` skill §3 iteration enforcement rules.

---

## Disposition

**Disposition**: ❌ **RETURNED TO AUTHOR (IMP)**

Item 18 is **NOT approved** for VER review (Track B). IMP shall address all four defects (DEFECT-18-001 through DEFECT-18-004) and resubmit via PM.

**Track A Status**: BLOCKED — awaiting IMP remediation.

**Track B Status**: NOT STARTED — VER cannot begin Item 19 (Software Source Code Verification Report) until QUA accepts Item 18.

**Next Action**: PM routes defect list to IMP for remediation.

---

## QUA Technical Observations (Informational Only — NOT Defects)

The following observations are **NON-BLOCKING** and provided as informational context for VER/PM:

1. ✅ **Code Quality** (Informational): Source code files have excellent headers with `@file`, `@brief`, `@details`, `@safety`, `@misra_compliance`, `@en50128_references` tags. This is **exemplary practice** for SIL 3 code.

2. ✅ **Traceability Documentation** (Informational): `TRACEABILITY.md` provides comprehensive unit-to-function mapping (§2), requirements coverage (§3), static analysis summary (§4), and gap analysis (§5). This will greatly assist VER verification.

3. ⚠️ **Build System** (Observation): No Makefile or build scripts found. IMP should provide build instructions in the package manifest (resolves DEFECT-18-004 Build Instructions section).

4. ℹ️ **Metrics Claims** (Informational): IMP claims 0 cppcheck errors, max CCN=10, zero MISRA mandatory violations, 100% traceability. QUA does **NOT verify** these claims — VER has full authority to independently validate in Item 19.

---

## EN 50128 References

- **§6.5** — Software Quality Assurance (QUA role definition)
- **§7.5.4** — Component Implementation and Testing (source code requirements)
- **Table A.9** — Software Quality Assurance Techniques (SIL 3: T2 Company Quality System = M)
- **Annex C Item 18** — Software Source Code and supporting documentation

---

## Approval

| Role | Name | Signature | Date |
|------|------|-----------|------|
| QUA (Format Review) | QA Engineer | QUA | 2026-04-04 |

---

**End of QUA Review Report — Item 18 Iteration 1**
