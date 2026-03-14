# EN 50128 Template Standardization - Quick Reference

**Status**: ✅ COMPLETE (100% compliance)  
**Date**: 2026-03-10

---

## Current Status

✅ **All 35 templates are standardized and compliant**

| Metric | Value |
|--------|-------|
| Templates Standardized | 35/35 (100%) |
| Critical Errors | 0 |
| Errors | 0 |
| Compliance Rate | 100% |

---

## Quick Validation

```bash
# Validate single template
python3 tools/documentation/doc_validator.py path/to/template.md

# Validate all templates
python3 tools/documentation/doc_validator.py --validate-all-templates
```

**Expected Result**: ✅ PASS with 0 critical errors, 0 errors

---

## Template Header Structure (Reference)

### Correct Format

```markdown
# [Document Full Name]

**TEMPLATE VERSION**: [X.Y]  
**REFERENCE**: EN 50128:2011 Section [X.Y], Table [A.N]

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | [DOC-XXX-YYYY-NNN] |
| **Version** | [X.Y] |
| **Date** | [YYYY-MM-DD] |
| **Project** | [Project Name] |
| **SIL Level** | [0, 1, 2, 3, or 4] |
| **Author** | [Name], [Role] |
| **Reviewer** | [Name], [Role] |
| **Approver** | [Name], [Role] |
| **Status** | [Draft | Review | Approved | Baseline] |

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft | - |

## APPROVALS

**SIL 0-2 Requirements**: Author, Technical Reviewer, QA Manager, Project Manager  
**SIL 3-4 Requirements**: Author, Technical Reviewer (independent), QA Manager, Safety Manager, Independent Verifier, Independent Validator, Assessor, Project Manager

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author** | [Name] | | YYYY-MM-DD |
| **Technical Reviewer** | [Name] | | YYYY-MM-DD |
| **QA Manager** | [Name] | | YYYY-MM-DD |
| **Safety Manager** (SIL 2+) | [Name] | | YYYY-MM-DD |
| **Project Manager** | [Name] | | YYYY-MM-DD |
| **Independent Verifier** (SIL 3-4) | [Name] | | YYYY-MM-DD |
| **Independent Validator** (SIL 3-4) | [Name] | | YYYY-MM-DD |
| **Assessor** (SIL 3-4) | [Name] | | YYYY-MM-DD |

---
```

### Key Rules

1. ✅ **Metadata at top**: ONLY TEMPLATE VERSION and REFERENCE
2. ✅ **STANDARD HEADER**: EXACTLY 9 fields
3. ✅ **DOCUMENT CONTROL**: EXACTLY 5 columns
4. ✅ **Field names**: Author (not "Prepared by"), Reviewer (not "Reviewed by"), Approver (not "Approved by")

---

## Common Mistakes (What NOT to Do)

### ❌ DON'T: Add forbidden metadata at document top

```markdown
# Document Title

**DOCUMENT ID**: DOC-XXX-YYYY-NNN  ❌ FORBIDDEN
**VERSION**: 1.0  ❌ FORBIDDEN
**DATE**: YYYY-MM-DD  ❌ FORBIDDEN
**STATUS**: Draft  ❌ FORBIDDEN
**CLASSIFICATION**: Internal  ❌ FORBIDDEN
**TEMPLATE VERSION**: 1.0  ✓ OK
**REFERENCE**: EN 50128:2011  ✓ OK
```

### ❌ DON'T: Use wrong field names

```markdown
## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Prepared by** | [Name] |  ❌ Should be "Author"
| **Reviewed by** | [Name] |  ❌ Should be "Reviewer"
| **Approved by** | [Name] |  ❌ Should be "Approver"
```

### ❌ DON'T: Omit mandatory fields

```markdown
## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Project** | [Project Name] |
| **SIL Level** | [0/1/2/3/4] |

❌ Missing: Document ID, Version, Date, Author, Reviewer, Approver, Status
```

---

## Tools Available

### `doc_validator.py` - Validate Templates

```bash
# Single template
python3 tools/documentation/doc_validator.py template.md

# All templates
python3 tools/documentation/doc_validator.py --validate-all-templates

# Generate report
python3 tools/documentation/doc_validator.py --validate-all-templates \
  --report docs/validation-report.md --format markdown
```

### `template_standardizer.py` - Standardize Templates

```bash
# Preview changes (dry-run)
python3 tools/documentation/template_standardizer.py \
  --file template.md --dry-run

# Standardize single template
python3 tools/documentation/template_standardizer.py --file template.md

# Standardize all templates
python3 tools/documentation/template_standardizer.py --standardize-all
```

---

## Reference Documents

### Official Specification
- **DOCUMENT-HEADER-TEMPLATE.md Section 2** - Mandatory header structure (PRIMARY)

### Reports
- **Complete Journey**: `docs/SUMMARY.md` - Full 3-phase story
- **Phase 3 Report**: `docs/phase3-standardization-report.md` - Final standardization
- **Validation Report**: `docs/validation-report-phase3.md` - Current validation status

### EN 50128 Standard
- **EN 50128:2011 Annex C Table C.1** - Document Control Summary

---

## Template Locations

All templates are in: `.opencode/skills/*/templates/*.md`

### By Category (35 total)

- **Configuration**: `.opencode/skills/en50128-configuration/templates/` (2)
- **Design**: `.opencode/skills/en50128-design/templates/` (4)
- **Documentation**: `.opencode/skills/en50128-documentation/templates/` (4)
- **Implementation**: `.opencode/skills/en50128-implementation/templates/` (1)
- **Integration**: `.opencode/skills/en50128-integration/templates/` (6)
- **Lifecycle**: `.opencode/skills/en50128-lifecycle-coordination/templates/` (3)
- **Management**: `.opencode/skills/en50128-project-management/templates/` (3)
- **Quality**: `.opencode/skills/en50128-quality/templates/` (2)
- **Requirements**: `.opencode/skills/en50128-requirements/templates/` (2)
- **Safety**: `.opencode/skills/en50128-safety/templates/` (4)
- **Testing**: `.opencode/skills/en50128-testing/templates/` (4)
- **Validation**: `.opencode/skills/en50128-validation/templates/` (1)

---

## FAQs

### Q: Can I add custom fields to STANDARD HEADER?

**A**: ❌ No. STANDARD HEADER must have EXACTLY 9 fields as specified in DOCUMENT-HEADER-TEMPLATE.md Section 2. Any custom fields should be added to document content sections, not the header.

### Q: Can I put DOCUMENT ID in metadata at document top?

**A**: ❌ No. Only TEMPLATE VERSION and REFERENCE are allowed at document top. DOCUMENT ID belongs in the STANDARD HEADER table.

### Q: What if I need more columns in DOCUMENT CONTROL?

**A**: ❌ DOCUMENT CONTROL must have EXACTLY 5 columns: Version, Date, Author, Changes, Approved By. This is mandatory per Section 2.

### Q: Can I use "Prepared by" instead of "Author"?

**A**: ❌ No. Field names must be exact: Author, Reviewer, Approver (not "Prepared by", "Reviewed by", "Approved by").

### Q: How do I know if a template is compliant?

**A**: Run `python3 tools/documentation/doc_validator.py template.md`. If it shows ✅ PASS with 0 critical errors and 0 errors, it's compliant.

---

## Contact

**Team**: EN 50128 Documentation Team  
**Project**: Railway Safety Software Development  
**Standard**: EN 50128:2011

---

**Last Updated**: 2026-03-10  
**Status**: ✅ ALL TEMPLATES COMPLIANT
