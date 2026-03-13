# EN 50128 Architecture Transition: Roles-Centric to Document-Centric

**Date**: 2026-03-13  
**Status**: PLANNING  
**Objective**: Transition from roles-based commands to document-centric workflow

---

## Executive Summary

### Current Architecture (Roles-Centric) ❌

Users invoke role-based commands:
```bash
/req    # Requirements Engineer
/des    # Designer
/imp    # Implementer
/tst    # Tester
/ver    # Verifier
/val    # Validator
/int    # Integrator
/saf    # Safety Engineer
/qua    # Quality Assurance
/cm     # Configuration Manager
/pm     # Project Manager
/cod    # Lifecycle Coordinator
/vmgr   # V&V Manager
```

**Problems:**
- User must know which role to invoke
- Workflow not intuitive for document creation
- Doesn't match EN 50128 document-centric process
- Commands mix role behavior with document creation

### Target Architecture (Document-Centric) ✅

Users work with documents directly:
```bash
# User works on documents naturally
"Create Software Requirements Specification for Train Control System, SIL 4"
"Review the Software Architecture Specification"
"Verify the Implementation"
"Generate Integration Test Report"
```

**Benefits:**
- Natural document-centric workflow (matches EN 50128 Annex C)
- System automatically invokes appropriate agents/skills
- Roles become background implementation details
- Cleaner separation: Documents (user-facing) vs Agents (system-facing)

---

## EN 50128 Document-Role Mapping (Annex C Table C.1)

### Document → Primary Role → Skills Mapping

| # | Document | Written By | 1st Check | 2nd Check | Primary Skill |
|---|----------|------------|-----------|-----------|---------------|
| **Planning Phase** |
| 1 | Software Quality Assurance Plan | PM/QUA | VER | VAL | `en50128-quality` |
| 2 | SQAP Verification Report | VER | VER | VAL | `en50128-verification` |
| 3 | Software Configuration Management Plan | CM | VER | VAL | `en50128-configuration` |
| 4 | Software Verification Plan | VER | - | VAL | `en50128-verification` |
| 5 | Software Validation Plan | VAL | VER | - | `en50128-validation` |
| **Requirements Phase** |
| 6 | Software Requirements Specification | REQ | VER | VAL | `en50128-requirements` |
| 7 | Overall Software Test Specification | TST | VER | VAL | `en50128-testing` |
| 8 | Software Requirements Verification Report | VER | - | VAL | `en50128-verification` |
| **Architecture & Design Phase** |
| 9 | Software Architecture Specification | DES | VER | VAL | `en50128-design` |
| 10 | Software Design Specification | DES | VER | VAL | `en50128-design` |
| 11 | Software Interface Specifications | DES | VER | VAL | `en50128-design` |
| 12 | Software Integration Test Specification | INT | VER | VAL | `en50128-integration` |
| 13 | SW/HW Integration Test Specification | INT | VER | VAL | `en50128-integration` |
| 14 | SW Architecture and Design Verification Report | VER | - | VAL | `en50128-verification` |
| **Component Design Phase** |
| 15 | Software Component Design Specification | DES | VER | VAL | `en50128-design` |
| 16 | Software Component Test Specification | TST | VER | VAL | `en50128-testing` |
| 17 | Software Component Design Verification Report | VER | - | VAL | `en50128-verification` |
| **Implementation & Testing Phase** |
| 18 | Software Source Code and Supporting Documentation | IMP | VER | VAL | `en50128-implementation` |
| 19 | Software Source Code Verification Report | VER | - | VAL | `en50128-verification` |
| 20 | Software Component Test Report | TST | VER | VAL | `en50128-testing` |
| **Integration Phase** |
| 21 | Software Integration Test Report | INT | VER | VAL | `en50128-integration` |
| 22 | SW/HW Integration Test Report | INT | VER | VAL | `en50128-integration` |
| 23 | Software Integration Verification Report | VER | - | - | `en50128-verification` |
| **Validation Phase** |
| 24 | Overall Software Test Report | TST | VER | VAL | `en50128-testing` |
| 25 | Software Validation Report | VAL | VER | - | `en50128-validation` |
| 26 | Tools Validation Report | VAL | VER | - | `en50128-validation` |
| **Application Data/Algorithms** |
| 28-35 | Application Documents | REQ/DES/TST/VER | VER | VAL | Multiple skills |
| **Deployment** |
| 36-40 | Deployment Documents | Various | VER | VAL | `en50128-validation` |
| **Maintenance** |
| 41-44 | Maintenance Documents | Various | VER | VAL | `en50128-configuration` |
| **Assessment** |
| 45 | Software Assessment Plan | ASR | VER | - | `en50128-verification` |
| 46 | Software Assessment Report | ASR | VER | - | `en50128-verification` |

---

## New Architecture Design

### 1. Document-Centric Entry Points

Users interact with documents, not roles:

```markdown
## User Interaction Model

### Creating Documents
User: "Create Software Requirements Specification for Train Control System, SIL 4"

System:
1. Identifies document type: "Software Requirements Specification" (DOC #6)
2. Looks up deliverable: deliverables/requirements/software-requirements-specification.yaml
3. Loads skill: .opencode/skills/en50128-requirements/
4. Loads template: .opencode/skills/en50128-requirements/templates/Software-Requirements-Specification-template.md
5. Invokes agent with Requirements Engineer (REQ) behavior
6. Creates document following template
7. Returns: DOC-SRS-2026-001.md

### Reviewing/Verifying Documents
User: "Verify the Software Requirements Specification"

System:
1. Identifies document: DOC-SRS-2026-001.md
2. Looks up verification workflow from deliverable metadata
3. Loads skill: .opencode/skills/en50128-verification/
4. Invokes agent with Verifier (VER) behavior
5. Performs verification per EN 50128 Section 6.2
6. Creates: DOC-SRS-VER-2026-001.md (Verification Report)

### Updating Documents
User: "Update the Software Architecture Specification to add new module"

System:
1. Identifies document: DOC-SAS-2026-001.md
2. Loads skill: .opencode/skills/en50128-design/
3. Invokes agent with Designer (DES) behavior
4. Updates document
5. Triggers configuration management workflow
```

### 2. System Components

```
┌─────────────────────────────────────────────────────────┐
│                    USER INTERFACE                        │
│  "Create SRS for Train Control, SIL 4"                  │
│  "Verify the SAS"                                        │
│  "Generate Integration Test Report"                      │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│              DOCUMENT INTENT PARSER                      │
│  - Identify document type from user intent               │
│  - Map to deliverable metadata                          │
│  - Determine required workflow                          │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│            DELIVERABLE METADATA (YAML)                   │
│  deliverables/<category>/<document>.yaml                 │
│  - Document ID mapping                                   │
│  - Template location                                     │
│  - Primary role/skill                                    │
│  - Verification workflow                                 │
│  - Validation workflow                                   │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│                   SKILL LOADER                           │
│  .opencode/skills/en50128-<domain>/                     │
│  - SKILL.md (domain instructions)                        │
│  - templates/ (document templates)                       │
│  - workflows/ (process workflows)                        │
│  - resources/ (references, tools)                        │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│                  AGENT INVOCATION                        │
│  Agent executes with:                                    │
│  - Role behavior (REQ, DES, IMP, VER, VAL, etc.)       │
│  - Skill instructions                                    │
│  - Document template                                     │
│  - EN 50128 constraints                                  │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│              DOCUMENT GENERATION                         │
│  Creates/updates document following:                     │
│  - Template structure                                    │
│  - EN 50128 compliance rules                            │
│  - SIL-level requirements                                │
│  - Traceability requirements                             │
└─────────────────────────────────────────────────────────┘
```

### 3. Deliverable Metadata Structure

Each document type has a YAML metadata file:

```yaml
# deliverables/requirements/software-requirements-specification.yaml
document_id: "DOC-SRS"
document_number: 6
name: "Software Requirements Specification"
phase: "Software requirements"
lifecycle_phase: "requirements"

# Primary authoring
written_by:
  role: "REQ"
  skill: "en50128-requirements"
  template: "Software-Requirements-Specification-template.md"

# Review workflow
first_check:
  role: "VER"
  skill: "en50128-verification"
  creates_document: "DOC-SRS-VER"

second_check:
  role: "VAL"
  skill: "en50128-validation"

# EN 50128 references
standard_references:
  - section: "7.2"
    title: "Software requirements"
  - table: "A.2"
    title: "Software Requirements Specification techniques"

# SIL-specific requirements
sil_requirements:
  sil_0:
    techniques_mandatory: []
    techniques_highly_recommended: []
  sil_1_2:
    techniques_mandatory: []
    techniques_highly_recommended: ["Structured Methodology"]
  sil_3_4:
    techniques_mandatory: ["Structured Methodology", "Traceability"]
    techniques_highly_recommended: ["Formal Methods", "Modelling"]

# Traceability
traces_from:
  - "System Requirements"
  - "Safety Requirements"
traces_to:
  - "Software Architecture Specification"
  - "Software Design Specification"
  - "Overall Software Test Specification"

# Configuration management
baseline_required: true
change_control_required: true
```

### 4. Skill Structure (Enhanced)

Each skill becomes the complete domain knowledge:

```
.opencode/skills/en50128-requirements/
├── SKILL.md                          # Main skill instructions
├── templates/
│   ├── Software-Requirements-Specification-template.md
│   └── Software-Requirements-Verification-Report-template.md
├── workflows/
│   ├── requirements-elicitation.md   # How to elicit requirements
│   ├── requirements-analysis.md      # How to analyze requirements
│   ├── requirements-specification.md # How to write SRS
│   └── traceability-management.md    # How to manage traceability
├── resources/
│   ├── requirement-patterns.md       # Common requirement patterns
│   ├── shall-should-may.md          # RFC 2119 keywords
│   └── testability-guidelines.md     # Making requirements testable
└── tools/
    └── requirement-validator.py      # Custom validation tools
```

**SKILL.md** becomes comprehensive domain knowledge:
```markdown
# EN 50128 Requirements Engineering Skill

## Role Behavior: Requirements Engineer (REQ)

When acting as Requirements Engineer, you SHALL:
- Elicit requirements from stakeholders and system specifications
- Analyze requirements for completeness, consistency, correctness
- Specify requirements following SHALL/SHOULD/MAY keywords
- Assign SIL levels to requirements
- Create traceability matrices
- Review requirements with stakeholders
- Baseline requirements after approval

## Documents Created
- Software Requirements Specification (SRS) - EN 50128 Doc #6
- Application Requirements Specification (ARS) - EN 50128 Doc #28

## EN 50128 Compliance (Section 7.2, Table A.2)

### MANDATORY Techniques (SIL 3-4)
- Structured Methodology
- Traceability

### Highly Recommended (SIL 3-4)
- Formal Methods
- Modelling
- Decision Tables

## Workflows
- [Requirements Elicitation](workflows/requirements-elicitation.md)
- [Requirements Analysis](workflows/requirements-analysis.md)
- [Requirements Specification](workflows/requirements-specification.md)
- [Traceability Management](workflows/traceability-management.md)

## Templates
- [SRS Template](templates/Software-Requirements-Specification-template.md)
- [ARS Template](templates/Application-Requirements-Specification-template.md)

## Resources
- [Requirement Patterns](resources/requirement-patterns.md)
- [SHALL/SHOULD/MAY Keywords](resources/shall-should-may.md)
- [Testability Guidelines](resources/testability-guidelines.md)

## Tools
- [Requirement Validator](tools/requirement-validator.py)

## Example Interactions

### Creating SRS
User: "Create Software Requirements Specification for Train Control System, SIL 4"

Agent (with REQ behavior):
1. Load SRS template
2. Interview user for requirements
3. Analyze system requirements
4. Elicit functional and non-functional requirements
5. Assign SIL levels
6. Create traceability matrix
7. Generate SRS document
8. Submit for verification

### Updating Requirements
User: "Add emergency brake requirement to SRS"

Agent (with REQ behavior):
1. Load existing SRS
2. Elicit new requirement details
3. Analyze impact on existing requirements
4. Update requirement ID sequence
5. Update traceability matrix
6. Update SRS document
7. Trigger change control workflow
```

---

## Migration Plan

### Phase 1: Deliverable Metadata Enhancement ✅ (Already Exists)

Current state:
- ✅ `deliverables/` directory with YAML files exists
- ✅ 44 deliverable metadata files already created
- ✅ Schema defined in `deliverables/schema/deliverable-schema.yaml`

**Action**: Enhance existing YAML files with:
- `written_by.skill` mapping
- `first_check.skill` mapping
- `second_check.skill` mapping
- Workflow definitions

### Phase 2: Skill Enhancement (Current Phase)

**Objective**: Make skills comprehensive domain knowledge

For each skill directory:
1. **Enhance SKILL.md** to include:
   - Role behavior definition (REQ, DES, IMP, VER, VAL, etc.)
   - Document creation workflows
   - EN 50128 compliance rules (Section X, Table Y)
   - SIL-specific requirements
   - Example interactions

2. **Add workflows/** subdirectory:
   - Step-by-step process workflows
   - Decision trees
   - Checklists

3. **Add resources/** subdirectory:
   - Reference materials
   - Patterns and examples
   - Guidelines and best practices

4. **Add tools/** subdirectory (if needed):
   - Custom validation scripts
   - Analysis tools
   - Report generators

### Phase 3: Document Intent Parser

**Objective**: Understand user intent and map to documents/workflows

Create a document intent parsing system:
```python
# tools/document-intent-parser.py
class DocumentIntentParser:
    def parse(self, user_input: str) -> Intent:
        """
        Parse user intent and map to document workflow.
        
        Examples:
        - "Create SRS for Train Control, SIL 4"
          → Intent: CREATE, Document: SRS, Context: {project: Train Control, sil: 4}
        
        - "Verify the Software Architecture"
          → Intent: VERIFY, Document: SAS, Context: {}
        
        - "Update Integration Test Report with new results"
          → Intent: UPDATE, Document: SITR, Context: {update_type: test_results}
        """
        # Parse using NLP or pattern matching
        # Return Intent object
        pass
```

### Phase 4: Command Deprecation

**Objective**: Retire role-based commands

Files to deprecate (move to `.opencode/commands/_deprecated/`):
- ❌ `req.md` - Requirements Engineer command
- ❌ `des.md` - Designer command
- ❌ `imp.md` - Implementer command
- ❌ `tst.md` - Tester command
- ❌ `ver.md` - Verifier command
- ❌ `val.md` - Validator command
- ❌ `int.md` - Integrator command
- ❌ `saf.md` - Safety Engineer command
- ❌ `qua.md` - Quality Assurance command

Files to keep (management/coordination):
- ✅ `cm.md` - Configuration Manager (cross-cutting)
- ✅ `pm.md` - Project Manager (coordination)
- ✅ `cod.md` - Lifecycle Coordinator (orchestration)
- ✅ `vmgr.md` - V&V Manager (SIL 3-4 authority)

Files to keep (utilities):
- ✅ `workspace.md` - Workspace management
- ✅ `enhelp.md` - EN 50128 help
- ✅ `pdf2md.md` - PDF conversion

### Phase 5: AGENTS.md Update

**Objective**: Rewrite AGENTS.md to document-centric model

New structure:
```markdown
# EN 50128 Document-Centric Architecture

## Overview
This platform follows a document-centric architecture where users work with
EN 50128 deliverables directly. The system automatically invokes appropriate
agents and skills based on document type and workflow requirements.

## Document Types (EN 50128 Annex C Table C.1)
[Map all 46 documents to skills and workflows]

## Skills (Domain Knowledge)
[Document each skill as comprehensive domain]

## Agents (Background Actors)
Agents execute in the background with role-specific behavior:
- Requirements Engineer (REQ) - For SRS, ARS documents
- Designer (DES) - For SAS, SDS, SIS documents
- Implementer (IMP) - For source code documents
- Tester (TST) - For test specification/report documents
- Verifier (VER) - For verification reports
- Validator (VAL) - For validation reports
- Integrator (INT) - For integration documents
...

## User Interaction Examples
[Show document-centric interactions]
```

---

## Skills Coverage Verification (EN 50128 Table C.1)

### Current Skills (14)

| Skill | Covers Documents | EN 50128 Roles |
|-------|------------------|----------------|
| `en50128-configuration` | DOC-3, DOC-42, DOC-43 | CM |
| `en50128-design` | DOC-9, DOC-10, DOC-11, DOC-15, DOC-31 | DES |
| `en50128-documentation` | DOC-1, DOC-3, DOC-4, DOC-5 | PM, VER, VAL |
| `en50128-implementation` | DOC-18, DOC-19 | IMP |
| `en50128-integration` | DOC-12, DOC-13, DOC-21, DOC-22, DOC-23 | INT |
| `en50128-lifecycle-coordination` | Phase management | COD |
| `en50128-project-management` | Project coordination | PM |
| `en50128-quality` | DOC-1, DOC-2, Quality reviews | QUA |
| `en50128-requirements` | DOC-6, DOC-28 | REQ |
| `en50128-safety` | Hazard analysis, FMEA, FTA | SAF |
| `en50128-testing` | DOC-7, DOC-16, DOC-20, DOC-24, DOC-30, DOC-33 | TST |
| `en50128-validation` | DOC-5, DOC-25, DOC-26, DOC-36-40 | VAL |
| `en50128-verification` | DOC-2, DOC-4, DOC-8, DOC-14, DOC-17, DOC-19, DOC-23, DOC-32, DOC-35, DOC-40, DOC-44 | VER |

### Coverage Analysis

#### ✅ Fully Covered Phases
- Planning (DOC 1-5) ✅
- Requirements (DOC 6-8) ✅
- Architecture & Design (DOC 9-14) ✅
- Component Design (DOC 15-17) ✅
- Implementation & Testing (DOC 18-20) ✅
- Integration (DOC 21-23) ✅
- Validation (DOC 24-26) ✅
- Application Data (DOC 28-35) ✅
- Deployment (DOC 36-40) ✅

#### ❌ Gaps to Address

1. **Software Assessment (DOC 45-46)** - Assessor role
   - DOC-45: Software Assessment Plan
   - DOC-46: Software Assessment Report
   - **Solution**: Create `en50128-assessment/` skill OR extend `en50128-verification/` with assessment workflows

2. **Software Maintenance (DOC 41-44)**
   - DOC-41: Software Maintenance Plan
   - DOC-43: Software Maintenance Records
   - DOC-44: Software Maintenance Verification Report
   - **Solution**: Create `en50128-maintenance/` skill OR extend `en50128-configuration/`

3. **Component Design Specification (DOC-15)**
   - Currently in `en50128-design/` but needs more detailed component-level workflows
   - **Solution**: Add component design workflows to `en50128-design/`

---

## Implementation Checklist

### ✅ Already Complete
- [x] Deliverable metadata files created (44 YAML files)
- [x] Deliverable schema defined
- [x] Skills directory structure exists (14 skills)
- [x] Templates standardized (35 templates, Phase 3 complete)
- [x] Document header structure standardized

### 🔄 In Progress (Phase 2: Skill Enhancement)

**Progress**: 2 of 13 skills complete (15%)

#### ✅ Completed Skills
- [x] **en50128-requirements** (COMPLETE - 2026-03-13)
  - 4 workflows (~120 pages): elicitation, analysis, specification, traceability
  - 2 resources (~40 pages): patterns, testability guidelines
  - Enhanced SKILL.md with "How to Use This Skill" section
  - Report: `docs/phase2-requirements-skill-enhancement.md`
  
- [x] **en50128-design** (COMPLETE - 2026-03-13)
  - 4 workflows (~185 pages): architecture, software design, interface design, design review
  - 5 resources (~170 pages): defensive programming, complexity, modularity, MISRA C, review checklist
  - Enhanced SKILL.md with "How to Use This Skill" section
  - Report: `docs/phase2-design-skill-enhancement.md`

#### 🔄 In Progress
- [ ] **en50128-implementation** (NEXT - High Priority)
  - Target: 4-5 workflows, 4-5 resources, ~250-300 pages
  - Focus: MISRA C coding, defensive patterns, unit testing, code review

#### 📋 Remaining Skills (11 of 13)
- [ ] en50128-verification (High Priority - 11 verification reports)
- [ ] en50128-testing (High Priority - critical for quality)
- [ ] en50128-integration (Medium Priority)
- [ ] en50128-validation (Medium Priority)
- [ ] en50128-quality (Medium Priority)
- [ ] en50128-configuration (Medium Priority)
- [ ] en50128-safety (Lower Priority)
- [ ] en50128-documentation (Lower Priority)
- [ ] en50128-project-management (Lower Priority)
- [ ] en50128-lifecycle-coordination (Lower Priority)
- [ ] en50128-vv-management (Lower Priority)

#### Phase 2 Tasks (In Progress)
- [x] Enhance SKILL.md files with comprehensive role behavior (2 of 13 complete)
- [x] Add workflows/ to skills (2 of 13 complete)
- [x] Add resources/ to skills (2 of 13 complete)
- [ ] Add tools/ where needed (future)
- [ ] Update deliverable YAML files with skill mappings (future)

### 📋 Todo (Future Phases)
- [ ] Create document intent parser
- [ ] Deprecate role-based commands
- [ ] Update AGENTS.md to document-centric model
- [ ] Create user guide for document-centric workflow
- [ ] Add assessment skill (if needed)
- [ ] Add maintenance skill (if needed)

### ✅ Tool Infrastructure (Complete - 2026-03-13)
- [x] **Traceability Manager Design** - Complete specification (35 pages)
  - 8 use cases, 10 CLI commands, 5 data models
  - SIL-dependent validation (80% SIL 0 → 100% SIL 3-4)
  - CSV/JSON/Markdown storage with auto-sync
  - Gap detection (orphans, untested, unallocated)
  - Location: `docs/designs/TRACEABILITY-MANAGER-DESIGN.md`
- [x] **Workflow Manager Design** - Complete specification (40 pages)
  - 9 use cases, 10 CLI commands, 6 data models
  - SIL-dependent workflows (4 approvals SIL 0-2 → 8 approvals SIL 3-4)
  - Independence validation (EN 50128 Section 5.1.2.10)
  - Configuration baselines with Git tags
  - Change control workflow (CCB approval)
  - Location: `docs/designs/WORKFLOW-MANAGER-DESIGN.md`
- [x] **Tool Integration Architecture** - Complete specification (25 pages)
  - System overview and component diagrams
  - 5 key integration points with code examples
  - End-to-end workflow examples
  - Performance considerations
  - Location: `docs/designs/TOOL-INTEGRATION-ARCHITECTURE.md`
- [x] **Design Summary and Index** - Implementation guide (18 pages + index)
  - 4-phase implementation roadmap
  - Testing strategy and success criteria
  - Agent and skill integration guidance
  - Location: `docs/designs/DESIGN-SUMMARY.md`, `docs/designs/README.md`

**Total Design Content**: ~2,750 lines (~118 pages)

**Next Steps**:
1. Implement Phase 1: Traceability Manager Core (Week 1)
2. Implement Phase 1: Workflow Manager Core (Week 1-2)
3. Integration testing (Week 2-3)
4. Advanced features (Week 3-4)

See `docs/designs/README.md` for complete tool design index.

---

## Skills Enhancement Order

Prioritize by document creation frequency and lifecycle order:

1. **en50128-requirements** (High Priority - Phase Start)
   - DOC-6: Software Requirements Specification
   - Most critical for project start

2. **en50128-design** (High Priority - Architecture Phase)
   - DOC-9: Software Architecture Specification
   - DOC-10: Software Design Specification
   - DOC-11: Software Interface Specifications

3. **en50128-implementation** (High Priority - Coding Phase)
   - DOC-18: Software Source Code
   - Most frequent during development

4. **en50128-verification** (High Priority - Throughout)
   - 11 verification reports across all phases
   - Most cross-cutting skill

5. **en50128-testing** (High Priority - Throughout)
   - DOC-7, DOC-16, DOC-20, DOC-24
   - Critical for quality

6. **en50128-integration** (Medium Priority)
   - DOC-12, DOC-13, DOC-21, DOC-22, DOC-23

7. **en50128-validation** (Medium Priority - End)
   - DOC-5, DOC-25, DOC-26

8. **en50128-quality** (Medium Priority - Throughout)
   - DOC-1, DOC-2, Quality reviews

9. **en50128-configuration** (Medium Priority - Throughout)
   - DOC-3, Change management

10. **en50128-documentation** (Low Priority - Planning)
    - DOC-1, DOC-4, DOC-5 (plans)

11. **en50128-safety** (Low Priority - Specialized)
    - Hazard analysis, FMEA, FTA

12. **en50128-project-management** (Low Priority - Coordination)
    - Project coordination

13. **en50128-lifecycle-coordination** (Low Priority - Orchestration)
    - Phase management

14. **en50128-validation** (Low Priority - Deployment)
    - Deployment documents

---

## Success Criteria

### User Experience
- ✅ User can request document creation by name (not role)
- ✅ System automatically invokes correct agent/skill
- ✅ Document generation follows templates automatically
- ✅ Verification/validation workflows triggered automatically
- ✅ Traceability managed automatically

### Technical
- ✅ All 46 EN 50128 documents mapped to skills
- ✅ All skills have comprehensive SKILL.md
- ✅ All skills have workflows/ for processes
- ✅ All skills have resources/ for guidance
- ✅ All deliverable YAML files have skill mappings
- ✅ Role-based commands deprecated gracefully

### Compliance
- ✅ 100% EN 50128 Annex C coverage
- ✅ All mandatory techniques documented in skills
- ✅ SIL-level requirements enforced per document
- ✅ Traceability requirements enforced
- ✅ Independence requirements preserved (VER, VAL, ASR)

---

## References

1. **EN 50128:2011 Annex C Table C.1** - Document Control Summary
2. **EN 50128:2011 Annex B** - Key software roles and responsibilities
3. **DOCUMENT-HEADER-TEMPLATE.md** - Template structure
4. **deliverables/** - Existing deliverable metadata
5. **.opencode/skills/** - Existing skills structure

---

**Next Action**: Begin Phase 2 - Enhance skills starting with `en50128-requirements`
