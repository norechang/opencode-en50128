# QUA Review Criteria - Rule-Based Checkers

This directory contains rule-based checkers for QUA (Quality Assurance) document reviews.

## Purpose

When a document owner (REQ, SAF, TST, DES, IMP, etc.) submits a deliverable to QUA for internal quality review, QUA applies **automated rule-based checks** to verify:

1. **Template Compliance**: Document follows EN 50128 template structure
2. **Quality Standards**: Document meets quality criteria (completeness, consistency, format)
3. **Content Requirements**: Document contains required sections and information

## Review Process

```
Owner Agent → QUA Review → Pass/Fail + Defect List
                ↓
         [If FAIL: Return to Owner]
                ↓
         Owner fixes defects
                ↓
         Resubmit (max 3 iterations)
```

## Checker Files

Each document type has a corresponding checker file:

| Document Type | Checker File | Description | Status |
|---------------|--------------|-------------|--------|
| SRS | `srs-checker.yaml` | Software Requirements Specification | ✅ Complete |
| RTM | `rtm-checker.yaml` | Requirements Traceability Matrix | ⏳ Pending |
| Hazard-Log | `hazard-log-checker.yaml` | Hazard Analysis and Safety | ✅ Complete |
| Test-Spec | `test-spec-checker.yaml` | Test Specifications | ✅ Complete |
| SAS | `sas-checker.yaml` | Software Architecture Specification | ✅ Complete |
| SDS | `sds-checker.yaml` | Software Design Specification | ✅ Complete |
| Source-Code | `source-code-checker.yaml` | C Implementation | ⏳ Pending |

## Checker YAML Schema

```yaml
document_type: string             # Document type (e.g., "SRS", "Hazard-Log")
checker_version: string           # Checker version (e.g., "1.0")

# Template compliance checks
template_checks:
  - id: string                    # Check ID (e.g., "SRS-T001")
    name: string                  # Check name
    description: string           # What this check does
    severity: string              # "error" or "warning"
    rule_type: string             # "regex", "section_exists", "table_exists", "field_format"
    rule_params:                  # Parameters specific to rule_type
      pattern: string             # Regex pattern (for regex rule_type)
      section: string             # Section name (for section_exists)
      table: string               # Table name (for table_exists)
      field: string               # Field name (for field_format)
    expected: string              # Expected result
    failure_message: string       # Message shown on failure
    fix_suggestion: string        # How to fix this issue

# Quality standards checks
quality_checks:
  - id: string
    name: string
    description: string
    severity: string
    rule_type: string
    rule_params: {}
    expected: string
    failure_message: string
    fix_suggestion: string

# Content requirement checks
content_checks:
  - id: string
    name: string
    description: string
    severity: string
    rule_type: string
    rule_params: {}
    expected: string
    failure_message: string
    fix_suggestion: string
```

## Rule Types

### 1. `regex`
Match content against a regular expression.
```yaml
rule_type: "regex"
rule_params:
  pattern: "^DOC-[A-Z]+-[0-9]{4}-[0-9]{3}$"
  search_section: "Document Control"  # Optional: limit search to section
```

### 2. `section_exists`
Check that a section exists in the document.
```yaml
rule_type: "section_exists"
rule_params:
  section: "1. Introduction"
  level: 1                            # Heading level (1-6)
```

### 3. `table_exists`
Check that a table exists with specific columns.
```yaml
rule_type: "table_exists"
rule_params:
  table_header: "Document Control"
  required_columns: ["Field", "Value"]
```

### 4. `field_format`
Check that a field has correct format.
```yaml
rule_type: "field_format"
rule_params:
  field_name: "Document ID"
  format_pattern: "^DOC-[A-Z]+-[0-9]{4}-[0-9]{3}$"
```

### 5. `count_minimum`
Check that at least N items exist (requirements, test cases, etc.).
```yaml
rule_type: "count_minimum"
rule_params:
  item_pattern: "^REQ-[A-Z]+-[0-9]{3}"
  minimum_count: 1
```

### 6. `all_items_match`
Check that all items of a type match a pattern.
```yaml
rule_type: "all_items_match"
rule_params:
  item_pattern: "^REQ-[A-Z]+-[0-9]{3}"
  field_pattern: "SIL [0-4]"
  field_description: "SIL level"
```

## Severity Levels

- **error**: Must be fixed before QUA accepts document (blocks acceptance)
- **warning**: Should be fixed but doesn't block acceptance (for user visibility)

## Implementation

QUA agent loads the appropriate checker file based on document type and applies all checks sequentially. Results are collected into a **QUA Review Report**:

```markdown
# QUA Review Report

**Document**: docs/SRS.md (DOC-SRS-2026-001)
**Reviewer**: QUA Agent
**Date**: 2026-02-20
**Result**: FAIL

## Defects Found (2 errors, 1 warning)

### Error: SRS-T001 - Document ID Format
**Severity**: error
**Location**: Document Control table
**Issue**: Document ID "DOC-SRS-2026-1" does not match required format
**Expected**: DOC-XXX-YYYY-NNN (e.g., DOC-SRS-2026-001)
**Fix**: Update Document ID to "DOC-SRS-2026-001"

### Error: SRS-C005 - Missing SIL Level
**Severity**: error
**Location**: Requirement REQ-TDC-023
**Issue**: Requirement does not specify SIL level
**Expected**: All requirements must have "SIL [0-4]" field
**Fix**: Add SIL level to REQ-TDC-023

### Warning: SRS-Q002 - Long Requirement Text
**Severity**: warning
**Location**: Requirement REQ-TDC-045
**Issue**: Requirement text exceeds 500 characters (may be ambiguous)
**Expected**: Requirements should be concise (< 500 chars)
**Fix**: Consider splitting REQ-TDC-045 into multiple requirements

## Summary
- ❌ Template Compliance: 1 error
- ❌ Quality Standards: 1 warning
- ❌ Content Requirements: 1 error
- **Overall: FAIL (2 errors must be fixed)**
```

## Usage in PM Workflow

```python
# Pseudocode
result = qua.review_document(
    doc_path="docs/SRS.md",
    doc_type="SRS",
    checker="srs-checker.yaml"
)

if result.status == "FAIL":
    # Send defects to owner agent
    owner.fix_defects(
        doc_path="docs/SRS.md",
        defects=result.defects
    )
    # Resubmit (max 3 iterations)
```
