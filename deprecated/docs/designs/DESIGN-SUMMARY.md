# EN 50128 Workflow and Traceability Tools - Design Summary

**Version**: 1.0  
**Date**: 2026-03-13  
**Status**: Design Phase Complete  
**Author**: OpenCode AI Agent

---

## Executive Summary

This document summarizes the comprehensive design for two critical EN 50128 platform tools that support the document-centric architecture transition:

1. **Traceability Manager** (`tools/traceability_manager.py`)
2. **Workflow Manager** (`tools/workflow_manager.py`)

Both tools have been designed with complete specifications including use cases, CLI interfaces, data models, storage formats, integration architecture, and implementation plans.

---

## Design Documents Created

### 1. Traceability Manager Design (`docs/designs/TRACEABILITY-MANAGER-DESIGN.md`)

**Size**: ~800 lines (~35 pages)

**Contents**:
- **8 Use Cases**: Create, validate, query, report, import, check gaps, extract, visualize
- **10 CLI Commands**: Complete command-line interface specification
- **Data Models**: TraceabilityLink, TraceabilityMatrix, ArtifactType, LinkType, ValidationRules
- **Storage Formats**: CSV (primary), JSON (index), Markdown (embedding)
- **SIL-Dependent Validation**: Mandatory 100% traceability for SIL 3-4
- **Gap Detection**: Orphans, untested requirements, unallocated requirements, dangling refs
- **Integration**: Deliverables metadata, LIFECYCLE_STATE.md, workspace.py

**Key Features**:
- ✅ Bidirectional traceability (forward: REQ→Design→Code→Test, backward: Test→Code→Design→REQ)
- ✅ SIL-dependent validation rules (80% coverage SIL 0 → 100% coverage SIL 3-4)
- ✅ Multiple output formats (CSV/JSON/Markdown) with automatic synchronization
- ✅ Auto-extraction of traceability from documents (regex-based with confidence scoring)
- ✅ Visualization support (Mermaid diagrams, GraphViz DOT)

---

### 2. Workflow Manager Design (`docs/designs/WORKFLOW-MANAGER-DESIGN.md`)

**Size**: ~900 lines (~40 pages)

**Contents**:
- **9 Use Cases**: Submit, review, approve, reject, baseline, gate-check, change requests, etc.
- **10 CLI Commands**: Complete command-line interface specification
- **Data Models**: WorkflowState, Approval, Rejection, ChangeRequest, PhaseGateCriteria
- **Storage Formats**: YAML (workflow state), JSON Lines (history), Git tags (baselines)
- **SIL-Dependent Workflows**: 4 approvals (SIL 0-2) → 8 approvals (SIL 3-4)
- **Independence Validation**: EN 50128 Section 5.1.2.10 enforcement for SIL 3-4
- **Integration**: workspace.py extension, LIFECYCLE_STATE.md, Git, deliverables metadata

**Key Features**:
- ✅ Document lifecycle tracking (Draft → Review → Approved → Baseline)
- ✅ SIL-dependent review routing (sequential workflows for SIL 3-4)
- ✅ Independence validation (VER/VAL cannot review own work)
- ✅ Configuration baselines with Git tags (immutable snapshots)
- ✅ Change control workflow (CCB approval for baselined documents)
- ✅ Phase gate validation (verify prerequisites before phase advancement)

---

### 3. Tool Integration Architecture (`docs/designs/TOOL-INTEGRATION-ARCHITECTURE.md`)

**Size**: ~600 lines (~25 pages)

**Contents**:
- **System Overview**: How tools fit into EN 50128 platform ecosystem
- **Component Diagrams**: Internal architecture for both tools
- **Data Flow Diagrams**: Step-by-step workflows with tool interactions
- **Integration Points**: 5 key integration scenarios with code examples
- **File System Organization**: Complete directory structure
- **Tool Communication**: Python API, CLI, configuration files
- **End-to-End Workflows**: Requirements phase completion with both tools
- **Performance Considerations**: Optimization strategies for large projects

**Key Integration Points**:
1. **Workflow ↔ Traceability**: Phase gate checks call traceability validation
2. **Traceability ↔ Deliverables**: Use metadata to determine required matrices
3. **Workflow ↔ Lifecycle State**: Update LIFECYCLE_STATE.md on status changes
4. **Both ↔ workspace.py**: Unified CLI interface
5. **Both ↔ Agents/Skills**: Automatic invocation from agent workflows

---

## Design Highlights

### Traceability Manager Highlights

| Feature | Description | EN 50128 Compliance |
|---------|-------------|---------------------|
| **Multiple Storage Formats** | CSV (tools), JSON (queries), Markdown (documents) | Evidence requirements (Annex C) |
| **SIL-Dependent Validation** | 80% (SIL 0) → 100% (SIL 3-4) | Table A.9, Technique 7 (Mandatory SIL 3-4) |
| **Gap Detection** | Orphans, untested, unallocated, dangling refs | Verification requirements |
| **Bidirectional Queries** | Forward/backward traceability chains | RAMS lifecycle traceability |
| **Auto-Extraction** | Parse documents for requirement references | Automation efficiency |

### Workflow Manager Highlights

| Feature | Description | EN 50128 Compliance |
|---------|-------------|---------------------|
| **SIL-Dependent Workflows** | 4 approvals (SIL 0-2) → 8 approvals (SIL 3-4) | Section 6.2 (Verification), 6.3 (Validation) |
| **Independence Validation** | Enforce EN 50128 Section 5.1.2.10 rules | Mandatory SIL 3-4 independence |
| **Configuration Baselines** | Git tags with checksums, immutable snapshots | Section 6.4 (Configuration Management) |
| **Change Control** | CCB approval workflow for baselined documents | Section 6.4.2 (Change Control) |
| **Phase Gates** | Validate prerequisites before phase advancement | Section 5.3 (Lifecycle phasing) |

---

## CLI Interface Summary

### Traceability Manager Commands

```bash
# Core operations
traceability.py create --from requirements --to architecture
traceability.py validate --matrix requirements_to_architecture --sil 3
traceability.py query --source SW-REQ-015 --direction forward
traceability.py report --from requirements --to architecture,tests --format markdown

# Gap detection and maintenance
traceability.py check-gaps --phase design --sil 3
traceability.py import --file legacy.csv --type requirements_to_design
traceability.py export --matrix all --format json --output export.json

# Advanced features
traceability.py extract --document SDS.md --type design_to_requirements --merge
traceability.py visualize --from requirements --to verification --format mermaid
traceability.py sync --matrix requirements_to_architecture
```

### Workflow Manager Commands

```bash
# Document lifecycle
workspace.py workflow submit SRS --for-review
workspace.py workflow review SRS --role VER --approve --comment "..."
workspace.py workflow approve SRS
workspace.py workflow status --all --format markdown

# Baseline and phase management
workspace.py workflow baseline --phase requirements --tag REQ-BASELINE-v1.0.0
workspace.py workflow gate-check requirements --sil 3
workspace.py workflow advance-phase --to architecture

# Change control
workspace.py workflow change-request SRS --create --description "..." --impact high
workspace.py workflow change-request CR-001 --ccb-approve

# Administration
workspace.py workflow assign-reviewer SRS --role VER --person "John Smith"
workspace.py workflow history SRS
```

---

## Data Storage Architecture

### Directory Structure

```
project_root/
├── LIFECYCLE_STATE.md                      # Project state (updated by Workflow Manager)
│
├── docs/                                   # EN 50128 deliverables
│   ├── Software-Requirements-Specification.md
│   ├── Software-Architecture-Specification.md
│   └── ...
│
├── evidence/                               # Evidence artifacts
│   └── traceability/                       # Traceability Manager storage
│       ├── requirements_to_architecture.csv        # Primary storage (tool-friendly)
│       ├── requirements_to_architecture.json       # Query index (fast lookups)
│       ├── requirements_to_architecture.md         # Human-readable (for documents)
│       └── index.json                              # Master index
│
├── .workflow/                              # Workflow Manager storage
│   ├── Software-Requirements-Specification.yaml    # Document workflow state
│   ├── history/
│   │   └── Software-Requirements-Specification.log # Event history (audit trail)
│   ├── change-requests/
│   │   ├── CR-001.yaml                             # Change request records
│   │   └── index.yaml
│   ├── baselines/
│   │   ├── REQ-BASELINE-v1.0.0.yaml                # Baseline manifests
│   │   └── index.yaml
│   └── config.yaml                                 # Workflow configuration
│
├── deliverables/                           # Deliverable metadata (read by both tools)
│   └── requirements/
│       └── Software-Requirements-Specification.yaml
│
└── tools/                                  # Tool implementations
    ├── workspace.py                        # Extended with workflow/traceability
    ├── workflow_manager.py                 # NEW: Workflow Manager
    └── traceability_manager.py             # NEW: Traceability Manager
```

---

## Implementation Approach

### Recommended Implementation Order

#### Phase 1: Traceability Manager Core (Week 1)
**Priority**: HIGH (blocking for Requirements phase completion)

**Tasks**:
1. ✅ Design complete (DONE)
2. ⏳ Implement data models (TraceabilityLink, TraceabilityMatrix)
3. ⏳ Implement CSV/JSON/Markdown parsers
4. ⏳ Implement `create` command (create empty matrix template)
5. ⏳ Implement `import` command (import CSV data)
6. ⏳ Implement `validate` command (SIL-dependent validation)
7. ⏳ Implement `report` command (generate Markdown reports)
8. ⏳ Test with example data

**Deliverable**: Working traceability tool for Requirements phase

---

#### Phase 2: Workflow Manager Core (Week 1-2)
**Priority**: HIGH (blocking for document approval workflow)

**Tasks**:
1. ✅ Design complete (DONE)
2. ⏳ Implement data models (WorkflowState, Approval, Rejection)
3. ⏳ Implement YAML state persistence
4. ⏳ Extend workspace.py with `workflow` subcommand
5. ⏳ Implement `submit`, `review`, `approve` commands
6. ⏳ Implement SIL-dependent workflow routing
7. ⏳ Implement independence validation (EN 50128 5.1.2.10)
8. ⏳ Test with example SIL 3 workflow

**Deliverable**: Working workflow tool for document reviews

---

#### Phase 3: Integration and Advanced Features (Week 2-3)
**Priority**: MEDIUM

**Tasks**:
1. ⏳ Traceability Manager: `query`, `check-gaps`, `export` commands
2. ⏳ Workflow Manager: `baseline`, `gate-check`, `change-request` commands
3. ⏳ Integration: Workflow calls Traceability for gate checks
4. ⏳ Integration: Both tools update LIFECYCLE_STATE.md
5. ⏳ Integration: Use deliverables metadata for requirements
6. ⏳ Test end-to-end: Requirements phase with both tools

**Deliverable**: Fully integrated tools with phase gate support

---

#### Phase 4: Advanced Features and Automation (Week 3-4)
**Priority**: LOW (nice-to-have)

**Tasks**:
1. ⏳ Traceability Manager: `extract` (auto-extraction from documents)
2. ⏳ Traceability Manager: `visualize` (Mermaid/GraphViz diagrams)
3. ⏳ Workflow Manager: Automatic reviewer notifications
4. ⏳ Workflow Manager: Overdue review detection
5. ⏳ Performance optimizations (caching, indexing)
6. ⏳ Web UI/dashboard (future enhancement)

**Deliverable**: Production-ready tools with automation

---

## Testing Strategy

### Unit Tests

**Traceability Manager**:
- Test CSV/JSON/Markdown parsing
- Test SIL-dependent validation rules
- Test gap detection algorithms (orphans, untested, etc.)
- Test coverage calculation
- Test query engine (forward/backward queries)

**Workflow Manager**:
- Test workflow state persistence (YAML read/write)
- Test SIL-dependent workflow routing
- Test independence validation rules
- Test approval/rejection logic
- Test phase gate validation

### Integration Tests

**Both Tools**:
- Test complete Requirements phase workflow (end-to-end)
- Test Workflow Manager calling Traceability Manager (gate checks)
- Test both tools updating LIFECYCLE_STATE.md
- Test with SIL 0, 2, 3, 4 scenarios
- Test with large projects (1000+ requirements, 100+ documents)

### Acceptance Tests

**Use Case Validation**:
- Execute all 8 Traceability Manager use cases
- Execute all 9 Workflow Manager use cases
- Verify EN 50128 compliance (independence, approvals, traceability)
- Validate with real EN 50128 projects

---

## Success Criteria

### Traceability Manager

- ✅ All 10 CLI commands implemented and functional
- ✅ SIL-dependent validation rules enforced (80% SIL 0 → 100% SIL 3-4)
- ✅ CSV/JSON/Markdown formats synchronized correctly
- ✅ Gap detection identifies all orphans, untested, unallocated requirements
- ✅ Bidirectional queries return correct traceability chains
- ✅ Integration with deliverables metadata working
- ✅ Performance: Validate 1000+ link matrix in <2 seconds

### Workflow Manager

- ✅ All 10 CLI commands implemented and functional
- ✅ SIL-dependent workflows route correctly (4 vs. 8 approvals)
- ✅ Independence validation enforces EN 50128 Section 5.1.2.10
- ✅ Git baselines created correctly with checksums
- ✅ Phase gate validation calls Traceability Manager
- ✅ Change control workflow operational (CCB approval)
- ✅ LIFECYCLE_STATE.md updated correctly on state changes

---

## Agent and Skill Integration

### Agent Workflow Enhancement

**Each agent should be updated to use tools automatically**:

**Example: Requirements Engineer (REQ) Agent**

```python
# When user invokes: /req create SRS for Train Control, SIL 3

# Step 1: REQ agent loads en50128-requirements skill
load_skill("en50128-requirements")

# Step 2: REQ agent creates SRS using template
create_document("Software-Requirements-Specification.md", template="SRS-template.md")

# Step 3: REQ agent initializes workflow (automatic)
bash("workspace.py workflow submit SRS --for-review")

# Step 4: REQ agent creates traceability matrices (automatic)
bash("traceability.py create --from system-requirements --to requirements")
bash("traceability.py create --from requirements --to architecture")
bash("traceability.py create --from requirements --to tests")

# Step 5: REQ agent prompts user to populate traceability
print("Traceability matrices created. Populate links and validate with:")
print("  traceability.py validate --phase requirements --sil 3")
```

**Similar updates needed for**:
- `/des` (Designer) - use Traceability Manager for architecture→design traceability
- `/imp` (Implementer) - use Traceability Manager for design→code traceability
- `/tst` (Tester) - use Traceability Manager for requirements→tests traceability
- `/ver` (Verifier) - use both tools for verification workflow
- `/val` (Validator) - use both tools for validation workflow
- `/cod` (Lifecycle Coordinator) - use Workflow Manager for gate checks

---

## Skill Documentation Enhancement

**Each skill should document tool integration**:

### Example: en50128-requirements/SKILL.md

```markdown
## Tool Integration

### Workflow Manager

After creating or modifying requirements documents:

```bash
# Submit for review
workspace.py workflow submit <document_id> --for-review

# Check approval status
workspace.py workflow status <document_id>

# View workflow history
workspace.py workflow history <document_id>
```

### Traceability Manager

After establishing requirements:

```bash
# Create traceability matrices
traceability.py create --from system-requirements --to requirements
traceability.py create --from requirements --to architecture
traceability.py create --from requirements --to tests

# Validate traceability
traceability.py validate --phase requirements --sil <level>

# Generate traceability report
traceability.py report --from requirements --to architecture,tests --format markdown
```

## Automated Workflow

When invoked via `/req` command, the agent automatically:
1. Creates requirements document using template
2. Initializes workflow via Workflow Manager
3. Creates traceability matrices via Traceability Manager
4. Validates completeness using both tools
5. Generates reports embedding traceability
```

---

## Next Steps

### Immediate (Week 1)

1. **Implement Traceability Manager Core**:
   - Data models (Python dataclasses)
   - CSV/JSON/Markdown I/O
   - `create`, `import`, `validate`, `report` commands
   - Test with example Requirements phase data

2. **Implement Workflow Manager Core**:
   - Data models (Python dataclasses)
   - YAML state persistence
   - Extend workspace.py
   - `submit`, `review`, `approve` commands
   - Test with example SIL 3 review workflow

### Near-Term (Week 2-3)

3. **Integration Testing**:
   - Workflow Manager calls Traceability Manager for gate checks
   - Both tools update LIFECYCLE_STATE.md
   - Test end-to-end: Requirements phase complete workflow

4. **Advanced Commands**:
   - Traceability: `query`, `check-gaps`, `export`
   - Workflow: `baseline`, `gate-check`, `change-request`

### Long-Term (Week 4+)

5. **Agent and Skill Integration**:
   - Update agent workflows to use tools automatically
   - Add tool integration sections to skill documentation
   - Test with all lifecycle phases

6. **Advanced Features**:
   - Auto-extraction from documents
   - Visualization (Mermaid/GraphViz)
   - Reviewer notifications
   - Web dashboard

---

## Design Review Checklist

Before implementation, verify:

- ✅ **Use Cases**: All critical workflows covered (8 + 9 = 17 use cases)
- ✅ **CLI Interface**: Complete command specifications (10 + 10 = 20 commands)
- ✅ **Data Models**: All entities defined with data structures
- ✅ **Storage Formats**: CSV, JSON, YAML, Markdown formats specified
- ✅ **EN 50128 Compliance**: SIL-dependent rules, independence validation
- ✅ **Integration Points**: Tools communicate correctly (5 integration scenarios)
- ✅ **Architecture**: Component diagrams, data flows, file organization
- ✅ **Implementation Plan**: Phased approach with priorities
- ✅ **Testing Strategy**: Unit, integration, acceptance tests defined

---

## Design Approval

**Recommended**: Review design documents with stakeholders before implementation.

**Review Questions**:
1. Do the use cases cover all critical workflows for EN 50128 compliance?
2. Is the CLI interface intuitive and consistent with existing tools?
3. Are the data models sufficient for SIL 3-4 requirements?
4. Does the integration architecture support the document-centric transition?
5. Is the implementation plan realistic (3-4 weeks for core functionality)?

**After Approval**: Proceed to Phase 1 implementation (Traceability Manager Core).

---

## References

- **Design Documents**:
  - `docs/designs/TRACEABILITY-MANAGER-DESIGN.md` - Complete traceability tool design
  - `docs/designs/WORKFLOW-MANAGER-DESIGN.md` - Complete workflow tool design
  - `docs/designs/TOOL-INTEGRATION-ARCHITECTURE.md` - Integration architecture

- **EN 50128 Standard**:
  - `std/EN50128-2011.md` - Full standard (LLM-friendly Markdown)
  - Section 5.1.2.10 - Role definitions and independence
  - Section 6.2 - Verification
  - Section 6.3 - Validation
  - Section 6.4 - Configuration Management
  - Table A.9 - Quality Assurance techniques (Traceability: Mandatory SIL 3-4)

- **Related Documentation**:
  - `LIFECYCLE.md` - EN 50128 V-Model lifecycle phases
  - `AGENTS.md` - Agent role definitions
  - `TOOLS.md` - Comprehensive tool catalog
  - `docs/ARCHITECTURE-TRANSITION.md` - Document-centric architecture plan

---

**STATUS**: Design phase complete ✅  
**READY FOR**: Implementation Phase 1 (Traceability Manager Core)

---

**END OF DESIGN SUMMARY**
