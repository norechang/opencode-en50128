# Deliverable Management Tools

Python tools for managing EN 50128 deliverable definitions.

## Tools

### 1. loader.py

**Purpose**: Load and query deliverable definitions

**Usage**:
```python
from pathlib import Path
from tools.deliverables.loader import DeliverableLoader

# Initialize loader
loader = DeliverableLoader(Path("deliverables"))

# Load a deliverable
srs = loader.load_deliverable("DOC-006-SRS")
print(f"Deliverable: {srs.name}")
print(f"Written by: {srs.written_by}")
print(f"Phase: {srs.phase}")

# Get SIL 3 evidence requirements
evidence = loader.get_required_evidence("DOC-006-SRS", sil=3)
print(f"SIL 3 evidence items: {len(evidence)}")
for ev in evidence:
    print(f"  - {ev.evidence_id}: {ev.description}")

# Check dependencies
deps = loader.get_dependencies("DOC-006-SRS")
print(f"Dependencies: {deps}")

# Check if mandatory for SIL level
is_mandatory = loader.is_mandatory("DOC-006-SRS", sil=3)
print(f"Mandatory for SIL 3: {is_mandatory}")
```

**Key Methods**:
- `load_deliverable(deliverable_id)` - Load deliverable definition
- `get_required_evidence(deliverable_id, sil)` - Get evidence for SIL level
- `get_dependencies(deliverable_id)` - Get prerequisite deliverables
- `get_dependents(deliverable_id)` - Get dependent deliverables
- `get_sil_requirements(deliverable_id, sil)` - Get SIL-specific requirements
- `is_mandatory(deliverable_id, sil)` - Check if mandatory for SIL
- `list_deliverables_by_phase(phase)` - List deliverables in a phase

### 2. validator.py

**Purpose**: Validate deliverable YAML files against schema

**Usage**:
```bash
# Validate single file
python3 tools/deliverables/validator.py deliverables/requirements/Software-Requirements-Specification.yaml

# Validate all deliverables
python3 tools/deliverables/validator.py --all

# Specify deliverables directory
python3 tools/deliverables/validator.py --all --deliverables-dir /path/to/deliverables
```

**Output**:
```
✅ requirements/Software-Requirements-Specification.yaml
✅ implementation/Software-Source-Code-Verification-Report.yaml
❌ planning/Software-Quality-Assurance-Plan.yaml
   Validation error at sil_requirements.sil_3: 'mandatory' is a required property

📊 Results: 2/3 valid
```

### 3. dependency_graph.py (TODO)

**Purpose**: Build and query deliverable dependency graph

**Planned Features**:
- Topological sort (correct build order)
- Cycle detection
- Transitive dependencies
- Critical path analysis

### 4. evidence_checker.py (TODO)

**Purpose**: Check evidence completeness for deliverables

**Planned Features**:
- Scan evidence/ directory
- Match evidence to requirements
- Calculate completeness %
- Report missing evidence

## Installation

No external dependencies beyond standard library for core functionality.

For schema validation:
```bash
pip install pyyaml jsonschema
```

## Testing

```bash
# Test loader
cd /home/norechang/work/EN50128
python3 -c "
from pathlib import Path
from tools.deliverables.loader import DeliverableLoader

loader = DeliverableLoader(Path('deliverables'))
srs = loader.load_deliverable('DOC-006-SRS')
print(f'✓ Loaded: {srs.name}')
print(f'✓ Phase: {srs.phase}')
print(f'✓ Evidence items: {len(srs.evidence_requirements)}')
"

# Test validator
python3 tools/deliverables/validator.py deliverables/requirements/Software-Requirements-Specification.yaml
```

## Directory Structure

```
tools/deliverables/
├── README.md                  # This file
├── loader.py                  # Deliverable loader
├── validator.py               # Schema validator
├── dependency_graph.py        # TODO: Dependency graph tool
└── evidence_checker.py        # TODO: Evidence completeness checker
```

## See Also

- `deliverables/schema/README.md` - Schema documentation
- `PHASE1_DELIVERABLE_METADATA_SYSTEM.md` - Phase 1 detailed design
