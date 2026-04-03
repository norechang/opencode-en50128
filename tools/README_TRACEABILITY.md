# Traceability Manager Tool

**Version**: 1.0  
**Date**: 2026-03-13  
**Status**: Production Ready

---

## Overview

> ⚠ **IMPORTANT — Official Workflow**: The official EN 50128 traceability workflow for this platform uses **manual CSV creation** by the Configuration Manager (CM). The `trace extract` command is **OPTIONAL/EXPERIMENTAL** and may produce incorrect semantic mappings due to proximity-based heuristics. For compliance, use manual CSV creation as documented in `TRACEABILITY.md` Section 13 and `.opencode/skills/en50128-configuration/SKILL.md`.

The **Traceability Manager** is a Python-based CLI tool for creating, maintaining, and validating traceability matrices across the EN 50128 software development lifecycle. It ensures bidirectional traceability from system requirements through software requirements, architecture, design, implementation, testing, and verification.

**Key Features**:
- ✅ Create and maintain traceability matrices (CSV, Markdown, JSON formats)
- ✅ Validate traceability completeness (SIL-dependent thresholds)
- ✅ Detect gaps (orphan requirements, untested requirements, unimplemented requirements)
- ✅ Bidirectional queries (forward: REQ→Design→Code→Test, backward: Test→Code→Design→REQ)
- ✅ Generate traceability reports for EN 50128 deliverables
- ✅ Import/export traceability data in multiple formats
- ⚠ Auto-extract traceability from documents (OPTIONAL/EXPERIMENTAL)
- ✅ Generate visualizations (Mermaid, GraphViz DOT)
- ✅ Synchronize CSV/JSON/Markdown formats

**EN 50128 Compliance**:
- **SIL 3-4**: 100% traceability MANDATORY (EN 50128 Table A.9, Technique 7)
- **SIL 1-2**: Traceability Highly Recommended (95% target)
- **SIL 0**: Traceability Recommended (80% target)

---

## Installation

### Prerequisites

```bash
# Python 3.8 or higher
python3 --version

# Required libraries
pip install openpyxl  # For Excel import/export (optional)
```

### Verify Installation

```bash
python3 tools/traceability_manager.py --help
```

---

## Commands

The Traceability Manager provides 10 commands:

| Command | Purpose | Status |
|---------|---------|--------|
| `create` | Create new traceability matrix template | ✅ Complete |
| `validate` | Validate traceability completeness | ✅ Complete |
| `query` | Query traceability links | ✅ Complete |
| `check-gaps` | Detect traceability gaps | ✅ Complete |
| `report` | Generate traceability report | ✅ Complete |
| `import` | Import traceability data | ✅ Complete |
| `export` | Export traceability data | ✅ Complete |
| `extract` | Auto-extract traceability from documents | ⚠ OPTIONAL/EXPERIMENTAL |
| `visualize` | Generate traceability visualizations | ✅ Complete |
| `sync` | Synchronize CSV/JSON/Markdown formats | ✅ Complete |

---

## Quick Start

### 1. Manual CSV Creation (Official Workflow — RECOMMENDED)

**For EN 50128 compliance, use manual CSV creation**:

1. Read deliverables produced by document authors
2. Extract trace relationships (e.g., COMP-001 → REQ-SAFE-007)
3. Create CSV file with canonical naming: `doc{source}_to_doc{target}.csv`
4. Use standard CSV format (see Section 4 "Data Models")
5. Validate: `python3 tools/workspace.py trace validate --phase design --sil 3`

**Example** (Phase 3 — Architecture to Requirements):
```csv
source_id,source_type,target_id,target_type,link_type,rationale,verified,verified_by,verified_date,source_document,target_document
COMP-001-SKN,component,REQ-SAFE-007,requirement,implements,SKN implements safety interlock,true,VER,2026-03-28,doc9,doc6
COMP-001-SKN,component,REQ-SAFE-002,requirement,implements,SKN monitors door sensor,true,VER,2026-03-28,doc9,doc6
```

**See**: `TRACEABILITY.md` Section 13 and `.opencode/skills/en50128-configuration/SKILL.md` for detailed per-phase workflows.

---

### 2. Create Traceability Matrix (Alternative — Template Creation)

Create a new traceability matrix between requirements and architecture:

```bash
python3 tools/traceability_manager.py create \
  --from requirements \
  --to architecture
```

**Output**:
- `evidence/traceability/requirements_to_architecture.csv` (primary data)
- `evidence/traceability/requirements_to_architecture.json` (query index)
- `evidence/traceability/requirements_to_architecture.md` (report)

### 3. Populate Matrix

Edit the CSV file to add traceability links:

```csv
source_id,source_type,target_id,target_type,link_type,rationale,verified,verified_by,verified_date,confidence,source_document
SW-REQ-001,software_requirement,ARCH-COMP-001,architecture_component,allocated_to,Requirement allocated to architecture component,true,VER,2026-03-13,high,Software Requirements Specification
SW-REQ-002,software_requirement,ARCH-COMP-001,architecture_component,allocated_to,Another allocation,false,,,high,Software Requirements Specification
```

### 4. Validate Traceability

Validate traceability completeness for SIL 3:

```bash
python3 tools/traceability_manager.py validate \
  --phase design \
  --sil 3
```

**Output**:
```
======================================================================
Traceability Validation Report
======================================================================
Project:    TrainDoorControl
SIL Level:  3
Threshold:  100%
======================================================================

✓ PASS  requirements_to_architecture
       Coverage: 100.0% (50/50)

✓ PASS  architecture_to_design
       Coverage: 100.0% (10/10)

======================================================================
Overall Status: ✓ PASS
======================================================================
```

### 5. Query Traceability

Find all architecture components that implement a requirement (forward traceability):

```bash
python3 tools/traceability_manager.py query \
  --source SW-REQ-015 \
  --direction forward
```

Find all requirements traced to an architecture component (backward traceability):

```bash
python3 tools/traceability_manager.py query \
  --target ARCH-COMP-005 \
  --direction backward
```

### 6. Check for Gaps

Detect traceability gaps before phase gate:

```bash
python3 tools/traceability_manager.py check-gaps \
  --phase design \
  --sil 3
```

**Output**:
```
======================================================================
Traceability Gap Analysis (SIL 3)
======================================================================

Orphan Sources (no targets): 2
  - SW-REQ-037
  - SW-REQ-042

Orphan Targets (no sources): 0

Unverified Links: 5
  ⚠ WARNING: All links must be verified for SIL 3-4

Low Confidence Links: 3
  ⚠ Recommend manual review

======================================================================
```

### 7. Generate Report

Generate traceability report for inclusion in EN 50128 documents:

```bash
python3 tools/traceability_manager.py report \
  --from requirements \
  --to architecture,design,tests \
  --format markdown \
  --output docs/traceability_report.md
```

### 8. Import Traceability Data

Import existing traceability data from CSV/JSON/Excel:

```bash
python3 tools/traceability_manager.py import \
  --file legacy_traceability.csv \
  --type requirements_to_design \
  --format csv
```

### 9. Export Traceability Data

Export all traceability matrices to JSON:

```bash
python3 tools/traceability_manager.py export \
  --matrix all \
  --format json \
  --output traceability_export.json
```

### 10. Auto-Extract Traceability (OPTIONAL/EXPERIMENTAL)

> ⚠ **Note**: This command is OPTIONAL/EXPERIMENTAL. It uses proximity-based heuristics to extract traceability links from documents. For EN 50128 compliance, use manual CSV creation as documented in `TRACEABILITY.md` Section 13.

Automatically extract traceability links from design documents:

```bash
python3 tools/traceability_manager.py extract \
  --document docs/Software-Design-Specification.md \
  --type design_to_requirements \
  --merge
```

### 11. Generate Visualization

Generate Mermaid diagram for traceability:

```bash
python3 tools/traceability_manager.py visualize \
  --from requirements \
  --to architecture \
  --format mermaid \
  --output docs/traceability_diagram.md
```

### 12. Synchronize Formats

Synchronize CSV, JSON, and Markdown formats:

```bash
python3 tools/traceability_manager.py sync --matrix all
```

---

## Data Models

### Traceability Link

Each traceability link contains:

| Field | Type | Description | Example |
|-------|------|-------------|---------|
| `source_id` | string | Source artifact ID | `SW-REQ-015` |
| `source_type` | string | Source artifact type | `software_requirement` |
| `target_id` | string | Target artifact ID | `ARCH-COMP-005` |
| `target_type` | string | Target artifact type | `architecture_component` |
| `link_type` | string | Link relationship type | `allocated_to` |
| `rationale` | string | Human-readable explanation | `Requirement allocated to architecture component` |
| `verified` | boolean | Has link been verified? | `true` |
| `verified_by` | string | Role/person who verified | `VER` |
| `verified_date` | string | Verification date (ISO 8601) | `2026-03-13` |
| `confidence` | string | Confidence level | `high`, `medium`, `low` |
| `source_document` | string | Document where link established | `Software Requirements Specification` |

### Link Types

| Link Type | Description | Example |
|-----------|-------------|---------|
| `allocated_to` | Requirement allocated to component | SW-REQ → ARCH-COMP |
| `implements` | Code implements requirement | Function → SW-REQ |
| `tests` | Test case tests requirement | TEST → SW-REQ |
| `verifies` | Verification record verifies requirement | VER-REC → SW-REQ |
| `derives_from` | SW requirement derives from system requirement | SW-REQ → SYS-REQ |
| `refines` | Design refines architecture | DESIGN → ARCH |
| `satisfies` | Code satisfies design | Code → DESIGN |
| `mitigates` | Safety mechanism mitigates hazard | SAFETY-MECH → HAZARD |
| `depends_on` | Generic dependency | Artifact A → Artifact B |

---

## Artifact Types

The Traceability Manager supports the following EN 50128 artifact types:

### Requirements
- `system_requirement` - System-level requirements (SYS-REQ-XXX)
- `software_requirement` - Software requirements (SW-REQ-XXX)
- `safety_requirement` - Safety requirements (SAFETY-REQ-XXX)
- `interface_requirement` - Interface requirements (IF-REQ-XXX)

### Design
- `architecture_component` - Architecture components (ARCH-COMP-XXX)
- `design_component` - Design components (DES-COMP-XXX)
- `interface_specification` - Interface specifications (IF-SPEC-XXX)

### Implementation
- `source_file` - Source code files (.c, .h)
- `function` - C functions
- `module` - Software modules

### Testing
- `test_case` - Test cases (TEST-XXX)
- `test_procedure` - Test procedures (TEST-PROC-XXX)
- `test_result` - Test results (TEST-RESULT-XXX)

### Verification
- `verification_record` - Verification records (VER-REC-XXX)
- `review_record` - Review records (REVIEW-REC-XXX)

### Safety
- `hazard` - Hazards (HAZARD-XXX)
- `safety_mechanism` - Safety mechanisms (SAFETY-MECH-XXX)

---

## SIL-Dependent Validation

The Traceability Manager enforces SIL-dependent validation thresholds:

| SIL Level | Coverage Threshold | Verification Required | Testing Required |
|-----------|-------------------|----------------------|------------------|
| SIL 0 | 80% | No | No |
| SIL 1 | 90% | No | No |
| SIL 2 | 95% | No | Yes |
| SIL 3 | **100% (MANDATORY)** | **Yes (MANDATORY)** | **Yes (MANDATORY)** |
| SIL 4 | **100% (MANDATORY)** | **Yes (MANDATORY)** | **Yes (MANDATORY)** |

**EN 50128 Reference**: Table A.9, Technique 7 (Traceability)

---

## Phase-Specific Matrices

The Traceability Manager validates phase-specific traceability matrices:

### Requirements Phase
- `system_requirements_to_software_requirements`
- `software_requirements_to_tests`

### Design Phase
- `system_requirements_to_software_requirements`
- `software_requirements_to_architecture`
- `architecture_to_design`
- `software_requirements_to_tests`

### Implementation Phase
- `design_to_code`
- `code_to_unit_tests`

### Integration Phase
- `architecture_to_integration_tests`
- `design_to_integration_tests`

### Validation Phase
- `software_requirements_to_validation_tests`
- `code_to_validation_tests`

---

## Storage Formats

The Traceability Manager maintains traceability data in three synchronized formats:

### 1. CSV (Primary Storage)

CSV is the **primary storage format** for traceability matrices. All modifications should be made to CSV files.

**Location**: `evidence/traceability/*.csv`

**Example**:
```csv
source_id,source_type,target_id,target_type,link_type,rationale,verified,verified_by,verified_date,confidence,source_document
SW-REQ-001,software_requirement,ARCH-COMP-001,architecture_component,allocated_to,Requirement allocated to architecture,true,VER,2026-03-13,high,SRS
```

### 2. JSON (Query Index)

JSON format is optimized for fast queries and programmatic access.

**Location**: `evidence/traceability/*.json`

**Example**:
```json
{
  "name": "requirements_to_architecture",
  "source_type": "software_requirement",
  "target_type": "architecture_component",
  "project": "TrainDoorControl",
  "links": [
    {
      "source_id": "SW-REQ-001",
      "source_type": "software_requirement",
      "target_id": "ARCH-COMP-001",
      "target_type": "architecture_component",
      "link_type": "allocated_to",
      "rationale": "Requirement allocated to architecture",
      "verified": true,
      "verified_by": "VER",
      "verified_date": "2026-03-13",
      "confidence": "high",
      "source_document": "SRS"
    }
  ]
}
```

### 3. Markdown (Document Embedding)

Markdown format is optimized for embedding in EN 50128 documents.

**Location**: `evidence/traceability/*.md`

**Example**:
```markdown
# Traceability Matrix: requirements_to_architecture

**Project**: TrainDoorControl  
**Source Type**: software_requirement  
**Target Type**: architecture_component  
**Version**: 1.0  
**Status**: approved  

---

| Source ID | Target ID | Link Type | Verified | Rationale |
|-----------|-----------|-----------|----------|-----------|
| SW-REQ-001 | ARCH-COMP-001 | allocated_to | ✓ | Requirement allocated to architecture |
```

---

## Configuration

The Traceability Manager can be configured via `.traceability.yaml`:

```yaml
sil_thresholds:
  0: 0.80
  1: 0.90
  2: 0.95
  3: 1.00
  4: 1.00

artifact_patterns:
  software_requirement: "(SW-REQ-[A-Z]+-[A-Z0-9]+-\\d+|REQ-[A-Z]+-[A-Z0-9]+-\\d+)"
  system_requirement: "SYS-REQ-[A-Z]+-[A-Z0-9]+-\\d+"
  architecture_component: "ARCH-[A-Z]+-[A-Z0-9]+-\\d+"
  design_component: "DES-[A-Z]+-[A-Z0-9]+-\\d+"
  test_case: "TEST-[A-Z]+-[A-Z0-9]+-\\d+"
  function: "[a-z_][a-z0-9_]*\\(\\)"
```

---

## EN 50128 Compliance Checklist

### Traceability Requirements (Table A.9, Technique 7)

| SIL Level | Requirement | Status |
|-----------|-------------|--------|
| SIL 0 | Traceability Recommended | ✅ Supported |
| SIL 1-2 | Traceability Highly Recommended | ✅ Supported |
| SIL 3-4 | Traceability MANDATORY | ✅ **Enforced** |

### Traceability Validation

- ✅ Forward traceability (requirements → implementation → verification)
- ✅ Backward traceability (verification → implementation → requirements)
- ✅ Coverage metrics (% of sources with targets)
- ✅ Gap detection (orphans, untested, unverified)
- ✅ SIL-dependent thresholds (80% SIL 0 → 100% SIL 3-4)

### Traceability Reports

- ✅ Traceability matrices embedded in deliverables
- ✅ Coverage metrics by artifact type
- ✅ Verification status by link
- ✅ Visualization (Mermaid, DOT)

---

## Troubleshooting

### Issue: Matrix file not found

**Symptom**: `Matrix file not found: requirements_to_architecture`

**Solution**: Create the matrix first using `create` command:
```bash
python3 tools/traceability_manager.py create --from requirements --to architecture
```

### Issue: Coverage validation fails

**Symptom**: `✗ FAIL requirements_to_architecture Coverage: 95.0% (47/50)`

**Solution**: 
1. Run `check-gaps` to identify missing links
2. Add missing traceability links to CSV file
3. Run `sync` to update JSON/Markdown
4. Re-validate

### Issue: Import fails with format error

**Symptom**: `Unsupported import format: xlsx`

**Solution**: Install openpyxl:
```bash
pip install openpyxl
```

### Issue: Extract command finds no links

**Symptom**: `Extracted: 0 links`

**Solution**: 
1. Check artifact ID patterns in document match configuration
2. Update `.traceability.yaml` with custom patterns if needed
3. Consider manual traceability entry

---

## Future Enhancements

- [ ] Integration with workspace.py (`workspace trace ...`)
- [ ] HTML report generation
- [ ] Excel import/export optimization
- [ ] Graph traversal for multi-hop queries
- [ ] Impact analysis (change propagation)
- [ ] Baseline comparison (diff between versions)
- [ ] REST API for programmatic access

---

## Related Documentation

- **Design Specification**: `docs/designs/TRACEABILITY-MANAGER-DESIGN.md`
- **Tool Integration**: `docs/designs/TOOL-INTEGRATION-ARCHITECTURE.md`
- **EN 50128 Standard**: `std/EN50128-2011.md`
- **Skills**: `.opencode/skills/en50128-verification/` (traceability workflows)

---

## Support

For issues, questions, or contributions:
- **Tool Location**: `tools/traceability_manager.py`
- **Evidence Directory**: `evidence/traceability/`
- **Design Documents**: `docs/designs/`

**Version**: 1.0  
**Last Updated**: 2026-03-13  
**Status**: Production Ready ✅
