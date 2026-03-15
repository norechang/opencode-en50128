# EN 50128 Deliverables - Exact Standard Mapping

**Standard**: EN 50128:2011 Railway Software  
**Purpose**: Complete mapping of lifecycle deliverables with exact names from EN 50128 Section 7  
**Date**: 2026-02-20

---

## Important Note on Terminology

EN 50128 uses **EXACT** document names in Section 7 output specifications. All platform phase definitions, agent commands, and QUA checkers MUST use these exact names.

**Naming Convention**:
- EN 50128 uses **singular or plural** based on the section definition
- Example: "Software Interface Specification**s**" (plural - 7.3.3 item 3)
- Example: "Software Architecture Specification" (singular - 7.3.3 item 1)

---

## Section 7.2: Software Requirements

**EN 50128 Reference**: Section 7.2.3 Output documents

| # | Exact Document Name (EN 50128) | Clause | Written by | File Path |
|---|--------------------------------|--------|------------|-----------|
| 1 | **Software Requirements Specification** | 7.2.4.1 | Requirements Manager | `docs/SRS.md` |
| 2 | **Overall Software Test Specification** | 7.2.4.16 | Tester | `docs/test/Overall-Software-Test-Specification.md` |
| 3 | **Software Requirements Verification Report** | 7.2.4.27 | Verifier | `docs/reports/Software-Requirements-Verification-Report.md` |

**Notes**:
- Requirements Traceability Matrix (RTM) is implicit in SRS (not a separate deliverable per EN 50128)
- Hazard Log is best practice (not in Section 7.2 outputs, but recommended)

---

## Section 7.3: Architecture and Design

**EN 50128 Reference**: Section 7.3.3 Output documents

| # | Exact Document Name (EN 50128) | Clause | Written by | File Path |
|---|--------------------------------|--------|------------|-----------|
| 1 | **Software Architecture Specification** | 7.3.4.1 | Designer | `docs/Software-Architecture-Specification.md` |
| 2 | **Software Design Specification** | 7.3.4.20 | Designer | `docs/Software-Design-Specification.md` |
| 3 | **Software Interface Specification**s** | 7.3.4.18 | Designer | `docs/Software-Interface-Specifications.md` |
| 4 | **Software Integration Test Specification** | 7.3.4.25 | Integrator | `docs/test/Software-Integration-Test-Specification.md` |
| 5 | **Software/Hardware Integration Test Specification** | 7.3.4.33 | Integrator | `docs/test/Software-Hardware-Integration-Test-Specification.md` |
| 6 | **Software Architecture and Design Verification Report** | 7.3.4.40 | Verifier | `docs/reports/Software-Architecture-and-Design-Verification-Report.md` |

**Key Points**:
- Item 3 is **plural**: "Software Interface Specification**s**" (covers all interfaces)
- Items 4 and 5: Test **Specifications** created in Phase 3, Test **Reports** created in Phase 6
- Item 5: Use forward slash "/" not hyphen in "Software/Hardware"

---

## Section 7.4: Component Design

**EN 50128 Reference**: Section 7.4.3 Output documents

| # | Exact Document Name (EN 50128) | Clause | Written by | File Path |
|---|--------------------------------|--------|------------|-----------|
| 1 | **Software Component Design Specification** | 7.4.4.1 | Designer | `docs/Software-Component-Design-Specification.md` |
| 2 | **Software Component Test Specification** | 7.4.4.7 | Tester | `docs/test/Software-Component-Test-Specification.md` |
| 3 | **Software Component Design Verification Report** | 7.4.4.11 | Verifier | `docs/reports/Software-Component-Design-Verification-Report.md` |

**Key Points**:
- All names are **singular** (one specification per component set)
- Item 2: Test **Specification** created in Phase 4, Test **Report** created in Phase 5

---

## Section 7.5: Component Implementation and Testing

**EN 50128 Reference**: Section 7.5.3 Output documents

| # | Exact Document Name (EN 50128) | Clause | Written by | File Path |
|---|--------------------------------|--------|------------|-----------|
| 1 | **Software Source Code and supporting documentation** | 7.5.4.1 | Implementer | `src/` + supporting docs |
| 2 | **Software Component Test Report** | 7.5.4.5 | Tester | `docs/reports/Software-Component-Test-Report.md` |
| 3 | **Software Source Code Verification Report** | 7.5.4.8 | Verifier | `docs/reports/Software-Source-Code-Verification-Report.md` |

**Key Points**:
- Item 1: "Software Source Code" (not just "Source Code")
- Item 1: Lowercase "and" and "supporting documentation"
- Item 2: "Report" (execution results), not "Specification"

---

## Section 7.6: Integration

**EN 50128 Reference**: Section 7.6.3 Output documents

| # | Exact Document Name (EN 50128) | Clause | Written by | File Path |
|---|--------------------------------|--------|------------|-----------|
| 1 | **Software Integration Test Report** | 7.6.4.3 | Tester | `docs/reports/Software-Integration-Test-Report.md` |
| 2 | **Software/Hardware Integration Test Report** | 7.6.4.3 | Tester | `docs/reports/Software-Hardware-Integration-Test-Report.md` |
| 3 | **Software Integration Verification Report** | 7.6.4.6 | Verifier | `docs/reports/Software-Integration-Verification-Report.md` |

**Key Points**:
- Items 1 and 2: Test **Reports** (execution results of specs from Phase 3)
- Item 2: Use forward slash "/" not hyphen in "Software/Hardware"
- V-Model: Specifications created in Phase 3, Reports created in Phase 6

---

## Section 7.7: Overall Software Testing / Validation

**EN 50128 Reference**: Section 7.7.3 Output documents

| # | Exact Document Name (EN 50128) | Clause | Written by | File Path |
|---|--------------------------------|--------|------------|-----------|
| 1 | **Overall Software Test Report** | 7.7.4.1 | Tester | `docs/reports/Overall-Software-Test-Report.md` |
| 2 | **Software Validation Report** | 7.7.4.6 | Validator | `docs/reports/Software-Validation-Report.md` |
| 3 | **Release Note** | 7.7.4.15 | Project Manager | `docs/Release-Note.md` |

**Key Points**:
- Item 1: Test **Report** (execution of Overall Software Test Specification from Phase 2)
- Item 3: "Release Note" (singular), not "Release Notes"
- V-Model: Overall Test Specification created in Phase 2, Report created in Phase 7

---

## Document Naming Conventions

### File Naming Strategy

**Option 1: EN 50128 Exact Names** (RECOMMENDED for strict compliance)
- File name matches EN 50128 document name exactly
- Example: `Software-Architecture-Specification.md`
- Example: `Software-Interface-Specifications.md` (plural!)
- **Advantage**: Immediately recognizable to assessors, zero ambiguity

**Option 2: Shortened Names** (NOT RECOMMENDED)
- File name uses abbreviations (e.g., SAS.md, SDS.md)
- **Disadvantage**: Requires mapping table, less clear for assessors

### Document ID Convention

**Format**: `DOC-<TYPE>-YYYY-NNN`

Where:
- `<TYPE>` = Abbreviated document type (see table below)
- `YYYY` = Year (4 digits)
- `NNN` = Sequential number (3 digits, zero-padded)

| EN 50128 Document Name | Abbreviation | Example ID |
|------------------------|--------------|------------|
| Software Requirements Specification | SRS | DOC-SRS-2026-001 |
| Overall Software Test Specification | OVERALLTESTSPEC | DOC-OVERALLTESTSPEC-2026-001 |
| Software Architecture Specification | SAS | DOC-SAS-2026-001 |
| Software Design Specification | SDS | DOC-SDS-2026-001 |
| Software Interface Specifications | INTERFACES | DOC-INTERFACES-2026-001 |
| Software Integration Test Specification | INTTESTSPEC | DOC-INTTESTSPEC-2026-001 |
| Software/Hardware Integration Test Specification | HWINTTESTSPEC | DOC-HWINTTESTSPEC-2026-001 |
| Software Component Design Specification | COMPDESIGN | DOC-COMPDESIGN-2026-001 |
| Software Component Test Specification | COMPTESTSPEC | DOC-COMPTESTSPEC-2026-001 |
| Software Source Code and supporting documentation | SOURCECODE | DOC-SOURCECODE-2026-001 |
| Software Component Test Report | COMPTESTRPT | DOC-COMPTESTRPT-2026-001 |
| Software Integration Test Report | INTTESTRPT | DOC-INTTESTRPT-2026-001 |
| Software/Hardware Integration Test Report | HWINTTESTRPT | DOC-HWINTTESTRPT-2026-001 |
| Overall Software Test Report | OVERALLTESTRPT | DOC-OVERALLTESTRPT-2026-001 |
| Software Validation Report | VALRPT | DOC-VALRPT-2026-001 |
| Release Note | RELEASE | DOC-RELEASE-2026-001 |

**Verification Report IDs**:
| EN 50128 Verification Report | Abbreviation | Example ID |
|------------------------------|--------------|------------|
| Software Requirements Verification Report | REQVER | DOC-REQVER-2026-001 |
| Software Architecture and Design Verification Report | ARCHDESIGNVER | DOC-ARCHDESIGNVER-2026-001 |
| Software Component Design Verification Report | COMPDESIGNVER | DOC-COMPDESIGNVER-2026-001 |
| Software Source Code Verification Report | SOURCECODEVER | DOC-SOURCECODEVER-2026-001 |
| Software Integration Verification Report | INTVER | DOC-INTVER-2026-001 |

---

## Document Type Mapping (for QUA checkers)

| EN 50128 Document Name | doc_type (YAML) | QUA Checker File |
|------------------------|-----------------|------------------|
| Software Requirements Specification | `SRS` | `srs-checker.yaml` |
| Overall Software Test Specification | `Overall-Test-Spec` | `overall-test-spec-checker.yaml` |
| Software Architecture Specification | `SAS` | `sas-checker.yaml` |
| Software Design Specification | `SDS` | `sds-checker.yaml` |
| Software Interface Specifications | `Interface-Specs` | `interface-specs-checker.yaml` |
| Software Integration Test Specification | `Integration-Test-Spec` | `integration-test-spec-checker.yaml` |
| Software/Hardware Integration Test Specification | `HW-Integration-Test-Spec` | `hw-integration-test-spec-checker.yaml` |
| Software Component Design Specification | `Component-Design-Spec` | `component-design-spec-checker.yaml` |
| Software Component Test Specification | `Component-Test-Spec` | `component-test-spec-checker.yaml` |

---

## Action Items for Platform Update

### 1. Phase Definition Files (`.opencode/skills/en50128-project-management/phase-definitions/`)

**Files to Update**:
- `phase-2-requirements.yaml` - Update deliverable paths and doc_types
- `phase-3-architecture-design.yaml` - Update deliverable paths and doc_types
- `phase-4-component-design.yaml` - Update deliverable paths and doc_types
- CREATE: `phase-5-implementation-testing.yaml`
- CREATE: `phase-6-integration.yaml`
- CREATE: `phase-7-validation.yaml`

**Changes Required**:
- Update `path:` to use full EN 50128 names (e.g., `docs/Software-Architecture-Specification.md`)
- Update `doc_type:` to match EN 50128 names
- Update `task_description:` to reference exact EN 50128 document names

### 2. QUA Checker Files (`.opencode/skills/en50128-quality/review-criteria/`)

**Files to Update**:
- `sas-checker.yaml` - Update `document_type:` and template checks
- `sds-checker.yaml` - Update `document_type:` and template checks
- RENAME: `interface-spec-checker.yaml` → `interface-specs-checker.yaml` (plural!)
- `integration-test-spec-checker.yaml` - Update to match EN 50128 terminology
- CREATE: `component-design-spec-checker.yaml`
- CREATE: `component-test-spec-checker.yaml`
- CREATE: `overall-test-spec-checker.yaml`

### 3. LIFECYCLE.md

**Updates Required**:
- Replace all document names with exact EN 50128 names from Section 7
- Update all file paths to use full names
- Add notes explaining EN 50128 singular/plural conventions

### 4. Agent Command Files (`.opencode/commands/`)

**Files to Update**:
- `des.md` - Update deliverable references (SAS, SDS, Interface Specs, Component Design)
- `tst.md` - Update deliverable references (all test specs and reports)
- `int.md` - Update deliverable references (integration test specs and reports)
- `imp.md` - Update deliverable references (Source Code)
- `ver.md` - Update deliverable references (all verification reports)
- `val.md` - Update deliverable references (Validation Report)

---

## Compliance Verification Checklist

- [ ] All phase definitions use exact EN 50128 document names
- [ ] All file paths match EN 50128 naming (with hyphens for spaces)
- [ ] All QUA checkers match exact document names (with correct singular/plural)
- [ ] All agent commands reference exact EN 50128 deliverables
- [ ] Document IDs follow DOC-<TYPE>-YYYY-NNN convention
- [ ] V-Model alignment: Test Specs in design phases, Test Reports in execution phases
- [ ] Verification Reports follow EN 50128 naming conventions
- [ ] "Software/Hardware" uses forward slash "/" not hyphen
- [ ] "Software Interface Specifications" is **plural**
- [ ] "Release Note" is **singular**

---

## References

- **EN 50128:2011**: Section 7 (Generic Software Development)
- **Standard File**: `std/EN50128-2011.md`
- **Key Clauses**:
  - 7.2.3 (Requirements output documents)
  - 7.3.3 (Architecture and Design output documents)
  - 7.4.3 (Component Design output documents)
  - 7.5.3 (Implementation and Testing output documents)
  - 7.6.3 (Integration output documents)
  - 7.7.3 (Validation output documents)
