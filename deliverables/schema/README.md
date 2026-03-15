# EN 50128 Deliverable Metadata Schemas

## Overview

This directory contains JSON Schemas (expressed in YAML) for validating EN 50128 deliverable definitions.

## Schema Files

### 1. deliverable-schema.yaml

**Purpose**: Define the structure for EN 50128 deliverable metadata files

**Usage**: All deliverable YAML files (e.g., `Software-Requirements-Specification.yaml`) must conform to this schema.

**Key Sections**:
- **Basic Identification**: deliverable_id, number, name, abbreviation
- **Lifecycle Context**: phase, standard_section
- **Ownership**: written_by, first_check, second_check (from EN 50128 Table C.1)
- **Template**: Path to Markdown template
- **SIL Requirements**: SIL 0-4 specific requirements, techniques, evidence thresholds
- **Required Sections**: Document structure requirements
- **Evidence Requirements**: Required evidence artifacts per SIL level
- **Verification Criteria**: Completeness, correctness, consistency checks
- **Dependencies**: depends_on, feeds_into
- **Configuration Management**: Baseline requirements

### 2. evidence-schema.yaml

**Purpose**: Define the structure for evidence requirement definitions

**Usage**: Evidence requirements within deliverable definitions must conform to this schema.

**Key Fields**:
- **evidence_id**: Unique identifier (lowercase-hyphen-separated)
- **description**: What evidence is required
- **mandatory_sil**: Minimum SIL level where mandatory (0-4)
- **source**: Where evidence comes from (agent, tool, manual)
- **format**: Expected format (CSV, JSON, XML, Markdown, etc.)
- **storage_path**: Where evidence is stored (under `evidence/` directory)
- **tool**: Tool name if tool-generated
- **verification_criteria**: How to verify evidence is complete/correct
- **generation_command**: Command to generate evidence (if automated)
- **automation_level**: automatic, semi-automatic, manual

## Validation

### Using Python

```python
import yaml
import jsonschema
from pathlib import Path

# Load schema
with open('deliverables/schema/deliverable-schema.yaml') as f:
    schema = yaml.safe_load(f)

# Load deliverable definition
with open('deliverables/requirements/Software-Requirements-Specification.yaml') as f:
    deliverable = yaml.safe_load(f)

# Validate
try:
    jsonschema.validate(instance=deliverable, schema=schema)
    print("✓ Valid deliverable definition")
except jsonschema.ValidationError as e:
    print(f"✗ Validation error: {e.message}")
```

### Using validator.py tool

```bash
cd /home/norechang/work/EN50128
python3 tools/deliverables/validator.py deliverables/requirements/Software-Requirements-Specification.yaml
```

## Schema Version

**Version**: 1.0.0  
**Standard**: EN 50128:2011  
**Reference**: Annex C Table C.1 (Documents Control Summary)

## Examples

See:
- `deliverables/requirements/Software-Requirements-Specification.yaml` - Complete SRS definition
- `deliverables/implementation/Software-Source-Code-Verification-Report.yaml` - Verification report definition

## Schema Evolution

### Version History

| Version | Date | Changes |
|---------|------|---------|
| 1.0.0 | 2026-03-09 | Initial schema release |

### Backward Compatibility

Schema changes will maintain backward compatibility within major versions (1.x.x). Breaking changes will increment the major version (2.0.0).
