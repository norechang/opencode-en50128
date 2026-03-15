# EN 50128 Tool Integration Architecture

**Version**: 1.0  
**Date**: 2026-03-13  
**Status**: Design Phase

---

## 1. System Overview

This document describes the architecture and integration of the **Traceability Manager** and **Workflow Manager** tools within the EN 50128 platform ecosystem.

```
┌─────────────────────────────────────────────────────────────────────────┐
│                        EN 50128 Platform                                 │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                           │
│  ┌────────────────┐  ┌──────────────────┐  ┌──────────────────┐       │
│  │ User Commands  │  │  Agent Workflows │  │  Skill Knowledge │       │
│  │  /req, /des,   │  │  REQ, DES, IMP,  │  │  en50128-design, │       │
│  │  /imp, /tst    │  │  TST, VER, VAL   │  │  en50128-testing │       │
│  └───────┬────────┘  └────────┬─────────┘  └────────┬─────────┘       │
│          │                     │                      │                  │
│          └─────────────────────┼──────────────────────┘                  │
│                                │                                         │
│                                ▼                                         │
│  ┌─────────────────────────────────────────────────────────────────┐   │
│  │                    Tool Infrastructure Layer                     │   │
│  ├─────────────────────────────────────────────────────────────────┤   │
│  │                                                                   │   │
│  │  ┌──────────────────┐         ┌──────────────────┐             │   │
│  │  │ Traceability Mgr │         │  Workflow Mgr    │             │   │
│  │  │                  │         │                  │             │   │
│  │  │ • Create traces  │◄────────┤ • Doc lifecycle  │             │   │
│  │  │ • Validate       │         │ • Reviews        │             │   │
│  │  │ • Query          │─────────►│ • Approvals      │             │   │
│  │  │ • Report         │         │ • Baselines      │             │   │
│  │  └────────┬─────────┘         └────────┬─────────┘             │   │
│  │           │                             │                        │   │
│  └───────────┼─────────────────────────────┼────────────────────────┘   │
│              │                             │                            │
│              ▼                             ▼                            │
│  ┌─────────────────────────────────────────────────────────────────┐   │
│  │                  Infrastructure Layer                            │   │
│  ├─────────────────────────────────────────────────────────────────┤   │
│  │                                                                   │   │
│  │  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐          │   │
│  │  │ Workspace    │  │ Deliverables │  │ Document     │          │   │
│  │  │ Manager      │  │ Metadata     │  │ Validator    │          │   │
│  │  │              │  │              │  │              │          │   │
│  │  │ workspace.py │  │ YAML loaders │  │ doc_         │          │   │
│  │  │              │  │              │  │ validator.py │          │   │
│  │  └──────┬───────┘  └──────┬───────┘  └──────┬───────┘          │   │
│  │         │                  │                  │                   │   │
│  └─────────┼──────────────────┼──────────────────┼───────────────────┘   │
│            │                  │                  │                       │
│            ▼                  ▼                  ▼                       │
│  ┌─────────────────────────────────────────────────────────────────┐   │
│  │                      Data Layer                                  │   │
│  ├─────────────────────────────────────────────────────────────────┤   │
│  │                                                                   │   │
│  │  ┌────────────────┐  ┌───────────────┐  ┌────────────────┐     │   │
│  │  │ LIFECYCLE_     │  │ evidence/     │  │ .workflow/     │     │   │
│  │  │ STATE.md       │  │ traceability/ │  │ *.yaml         │     │   │
│  │  │                │  │ *.csv, *.json │  │                │     │   │
│  │  └────────────────┘  └───────────────┘  └────────────────┘     │   │
│  │                                                                   │   │
│  │  ┌────────────────┐  ┌───────────────┐  ┌────────────────┐     │   │
│  │  │ deliverables/  │  │ docs/         │  │ Git Repository │     │   │
│  │  │ */DOC-*.yaml   │  │ *.md          │  │ (baselines)    │     │   │
│  │  └────────────────┘  └───────────────┘  └────────────────┘     │   │
│  │                                                                   │   │
│  └───────────────────────────────────────────────────────────────────┘   │
│                                                                           │
└───────────────────────────────────────────────────────────────────────────┘
```

---

## 2. Traceability Manager Architecture

### 2.1 Component Diagram

```
┌────────────────────────────────────────────────────────────────┐
│                   Traceability Manager                         │
├────────────────────────────────────────────────────────────────┤
│                                                                 │
│  CLI Interface (traceability.py)                               │
│  ┌──────────────────────────────────────────────────────────┐ │
│  │ Commands:                                                 │ │
│  │ • create    • validate   • query     • report            │ │
│  │ • import    • export     • check-gaps • extract          │ │
│  │ • visualize • sync                                       │ │
│  └────────────────────────┬─────────────────────────────────┘ │
│                           │                                    │
│  ┌────────────────────────┴─────────────────────────────────┐ │
│  │              Traceability Core Engine                     │ │
│  ├───────────────────────────────────────────────────────────┤ │
│  │                                                            │ │
│  │  ┌─────────────────┐  ┌─────────────────┐               │ │
│  │  │ Matrix Manager  │  │ Link Manager    │               │ │
│  │  │                 │  │                 │               │ │
│  │  │ • Create matrix │  │ • Create link   │               │ │
│  │  │ • Load/save     │  │ • Validate link │               │ │
│  │  │ • Index mgmt    │  │ • Query links   │               │ │
│  │  └─────────────────┘  └─────────────────┘               │ │
│  │                                                            │ │
│  │  ┌─────────────────┐  ┌─────────────────┐               │ │
│  │  │ Validator       │  │ Gap Detector    │               │ │
│  │  │                 │  │                 │               │ │
│  │  │ • SIL rules     │  │ • Orphans       │               │ │
│  │  │ • Coverage      │  │ • Untested      │               │ │
│  │  │ • Completeness  │  │ • Dangling refs │               │ │
│  │  └─────────────────┘  └─────────────────┘               │ │
│  │                                                            │ │
│  │  ┌─────────────────┐  ┌─────────────────┐               │ │
│  │  │ Query Engine    │  │ Report Generator│               │ │
│  │  │                 │  │                 │               │ │
│  │  │ • Forward       │  │ • Markdown      │               │ │
│  │  │ • Backward      │  │ • JSON          │               │ │
│  │  │ • Bidirectional │  │ • HTML/Dashboard│               │ │
│  │  └─────────────────┘  └─────────────────┘               │ │
│  │                                                            │ │
│  └────────────────────────┬───────────────────────────────────┘ │
│                           │                                    │
│  ┌────────────────────────┴─────────────────────────────────┐ │
│  │                Storage Layer                              │ │
│  ├───────────────────────────────────────────────────────────┤ │
│  │                                                            │ │
│  │  ┌──────────┐  ┌──────────┐  ┌──────────┐               │ │
│  │  │ CSV      │  │ JSON     │  │ Markdown │               │ │
│  │  │ Writer/  │  │ Writer/  │  │ Writer/  │               │ │
│  │  │ Reader   │  │ Reader   │  │ Reader   │               │ │
│  │  └──────────┘  └──────────┘  └──────────┘               │ │
│  │                                                            │ │
│  │  ┌──────────────────────────────────────┐                │ │
│  │  │ Format Synchronizer                  │                │ │
│  │  │ (CSV ↔ JSON ↔ Markdown)              │                │ │
│  │  └──────────────────────────────────────┘                │ │
│  │                                                            │ │
│  └────────────────────────────────────────────────────────────┘ │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

### 2.2 Data Flow: Create and Validate Traceability Matrix

```
User Command
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ Step 1: Create Matrix Template                                  │
└─────────────────────────────────────────────────────────────────┘
     │
     │ $ traceability.py create --from requirements --to architecture
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ Matrix Manager                                                   │
│ • Creates empty CSV template: requirements_to_architecture.csv   │
│ • Reads deliverables metadata to determine source/target IDs     │
│ • Initializes JSON index                                         │
└─────────────────────────────────────────────────────────────────┘
     │
     │ Output: evidence/traceability/requirements_to_architecture.csv
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ Step 2: User Populates Matrix (Manual or Import)                │
└─────────────────────────────────────────────────────────────────┘
     │
     │ CSV:
     │ source_id,source_type,target_id,target_type,link_type,rationale
     │ SW-REQ-015,software_requirement,ARCH-COMP-005,architecture_component,allocated_to,Speed monitoring
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ Step 3: Validate Matrix                                         │
└─────────────────────────────────────────────────────────────────┘
     │
     │ $ traceability.py validate --matrix requirements_to_architecture --sil 3
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ Validator                                                        │
│ • Loads SIL 3 validation rules (100% coverage required)          │
│ • Loads CSV and parses links                                     │
│ • Calculates coverage: sources_with_targets / total_sources      │
│ • Checks for orphans, untested, dangling refs                    │
└─────────────────────────────────────────────────────────────────┘
     │
     │ Coverage: 100% ✅
     │ Orphans: 0 ✅
     │ Untested: 0 ✅
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ Report Generator                                                 │
│ • Generates validation report (Markdown)                         │
│ • Updates JSON index                                             │
│ • Syncs Markdown report for document embedding                   │
└─────────────────────────────────────────────────────────────────┘
     │
     │ Output: Validation Report (PASS/FAIL)
     │
     ▼
User Review
```

---

## 3. Workflow Manager Architecture

### 3.1 Component Diagram

```
┌────────────────────────────────────────────────────────────────┐
│                    Workflow Manager                            │
├────────────────────────────────────────────────────────────────┤
│                                                                 │
│  CLI Interface (workspace.py workflow)                         │
│  ┌──────────────────────────────────────────────────────────┐ │
│  │ Commands:                                                 │ │
│  │ • submit      • review       • approve                   │ │
│  │ • baseline    • gate-check   • advance-phase             │ │
│  │ • status      • change-request • assign-reviewer         │ │
│  │ • history                                                │ │
│  └────────────────────────┬─────────────────────────────────┘ │
│                           │                                    │
│  ┌────────────────────────┴─────────────────────────────────┐ │
│  │              Workflow Core Engine                         │ │
│  ├───────────────────────────────────────────────────────────┤ │
│  │                                                            │ │
│  │  ┌─────────────────┐  ┌─────────────────┐               │ │
│  │  │ State Manager   │  │ Review Router   │               │ │
│  │  │                 │  │                 │               │ │
│  │  │ • Load/save     │  │ • SIL routing   │               │ │
│  │  │   workflow state│  │ • Sequential    │               │ │
│  │  │ • State         │  │   enforcement   │               │ │
│  │  │   transitions   │  │ • Notifications │               │ │
│  │  └─────────────────┘  └─────────────────┘               │ │
│  │                                                            │ │
│  │  ┌─────────────────┐  ┌─────────────────┐               │ │
│  │  │ Approval Mgr    │  │ Independence    │               │ │
│  │  │                 │  │ Validator       │               │ │
│  │  │ • Record        │  │                 │               │ │
│  │  │   approvals     │  │ • EN 50128      │               │ │
│  │  │ • Verify        │  │   Section 5.1.2 │               │ │
│  │  │   signatures    │  │ • Role conflicts│               │ │
│  │  └─────────────────┘  └─────────────────┘               │ │
│  │                                                            │ │
│  │  ┌─────────────────┐  ┌─────────────────┐               │ │
│  │  │ Baseline Mgr    │  │ Gate Checker    │               │ │
│  │  │                 │  │                 │               │ │
│  │  │ • Git tags      │  │ • Phase         │               │ │
│  │  │ • Manifest      │  │   validation    │               │ │
│  │  │ • Checksums     │  │ • Prerequisites │               │ │
│  │  └─────────────────┘  └─────────────────┘               │ │
│  │                                                            │ │
│  │  ┌─────────────────┐  ┌─────────────────┐               │ │
│  │  │ Change Mgr      │  │ Report Generator│               │ │
│  │  │                 │  │                 │               │ │
│  │  │ • CR workflow   │  │ • Status        │               │ │
│  │  │ • CCB approval  │  │ • Approvals     │               │ │
│  │  │ • Impact        │  │ • History       │               │ │
│  │  └─────────────────┘  └─────────────────┘               │ │
│  │                                                            │ │
│  └────────────────────────┬───────────────────────────────────┘ │
│                           │                                    │
│  ┌────────────────────────┴─────────────────────────────────┐ │
│  │                Storage Layer                              │ │
│  ├───────────────────────────────────────────────────────────┤ │
│  │                                                            │ │
│  │  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐   │ │
│  │  │ Workflow     │  │ History      │  │ Change       │   │ │
│  │  │ State Files  │  │ Logs         │  │ Requests     │   │ │
│  │  │ (.yaml)      │  │ (.log)       │  │ (.yaml)      │   │ │
│  │  └──────────────┘  └──────────────┘  └──────────────┘   │ │
│  │                                                            │ │
│  │  ┌──────────────────────────────────────┐                │ │
│  │  │ Git Integration (Baselines)          │                │ │
│  │  └──────────────────────────────────────┘                │ │
│  │                                                            │ │
│  └────────────────────────────────────────────────────────────┘ │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

### 3.2 Data Flow: Document Review Workflow (SIL 3)

```
User: Author (REQ)
     │
     │ Step 1: Submit document for review
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ $ workspace.py workflow submit SRS --for-review                 │
└─────────────────────────────────────────────────────────────────┘
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ Workflow Manager: State Manager                                 │
│ • Loads SRS workflow state                                       │
│ • Transitions: Draft → Review                                    │
│ • Saves state: .workflow/Software-Requirements-Specification.yaml│
└─────────────────────────────────────────────────────────────────┘
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ Workflow Manager: Review Router                                 │
│ • Reads SIL level: 3                                             │
│ • Loads SIL 3 workflow: [PEER, QUA, SAFETY_MGR, VER, VAL, PM]  │
│ • Sets current_reviewer: PEER                                    │
│ • Notifies: PEER reviewer                                        │
└─────────────────────────────────────────────────────────────────┘
     │
     │ Email/notification to PEER: "Review SRS"
     │
     ▼
User: Peer Reviewer
     │
     │ Step 2: PEER reviews and approves
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ $ workspace.py workflow review SRS --role PEER --approve        │
│   --comment "Requirements well-structured"                      │
└─────────────────────────────────────────────────────────────────┘
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ Workflow Manager: Approval Manager                              │
│ • Records approval (PEER, timestamp, comment, signature)         │
│ • Advances to next reviewer: QUA                                 │
│ • Notifies: QUA reviewer                                         │
└─────────────────────────────────────────────────────────────────┘
     │
     │ [Similar flow for QUA, SAFETY_MGR reviewers...]
     │
     ▼
User: Verifier (VER)
     │
     │ Step 3: VER reviews (independent verification required)
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ $ workspace.py workflow review SRS --role VER --approve         │
│   --comment "Verification complete"                             │
└─────────────────────────────────────────────────────────────────┘
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ Workflow Manager: Independence Validator                        │
│ • Checks: Is VER same person as REQ, DES, IMP? (NO ✅)          │
│ • Validates EN 50128 Section 5.1.2.10i                          │
│ • Records approval with independent=true                         │
│ • Advances to next reviewer: VAL                                 │
└─────────────────────────────────────────────────────────────────┘
     │
     │ [Similar flow for VAL, PM reviewers...]
     │
     ▼
All Approvals Obtained
     │
     │ Step 4: Mark as approved
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ $ workspace.py workflow approve SRS                             │
└─────────────────────────────────────────────────────────────────┘
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ Workflow Manager: State Manager                                 │
│ • Validates all required approvals obtained (6/6 for SIL 3)     │
│ • Transitions: Review → Approved                                 │
│ • Updates LIFECYCLE_STATE.md: SRS status = Approved             │
└─────────────────────────────────────────────────────────────────┘
     │
     │ SRS now approved ✅
     │
     ▼
Configuration Manager (CM)
     │
     │ Step 5: Create baseline (after all deliverables approved)
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ $ workspace.py workflow baseline --phase requirements           │
│   --tag REQ-BASELINE-v1.0.0                                     │
└─────────────────────────────────────────────────────────────────┘
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ Workflow Manager: Baseline Manager                              │
│ • Validates all phase deliverables approved                      │
│ • Calculates checksums for all files                             │
│ • Creates Git tag: REQ-BASELINE-v1.0.0                          │
│ • Generates baseline manifest                                    │
│ • Transitions all deliverables: Approved → Baseline             │
└─────────────────────────────────────────────────────────────────┘
     │
     │ Baseline created ✅ (immutable Git tag)
     │
     ▼
Lifecycle Coordinator (COD)
     │
     │ Step 6: Gate check before advancing to next phase
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ $ workspace.py workflow gate-check requirements --sil 3         │
└─────────────────────────────────────────────────────────────────┘
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ Workflow Manager: Gate Checker                                  │
│ ✅ All deliverables approved                                     │
│ ✅ Baseline created                                              │
│ ✅ Traceability 100% complete (queries Traceability Manager)     │
│ ✅ QUA reviews passed                                            │
│ ✅ Independent VER approval                                      │
│ RESULT: GATE CHECK PASSED ✅                                     │
└─────────────────────────────────────────────────────────────────┘
     │
     │ Ready to advance to Phase 3 (Architecture & Design)
     │
     ▼
End
```

---

## 4. Tool Integration Points

### 4.1 Traceability Manager ↔ Workflow Manager Integration

#### Integration Point 1: Phase Gate Validation

**Scenario**: Workflow Manager needs to validate traceability before allowing phase advancement

**Flow**:
```python
# workflow_manager.py - Gate Checker

def validate_phase_gate(phase: str, sil_level: int) -> GateCheckResult:
    result = GateCheckResult()
    
    # ... other gate checks ...
    
    # Check traceability completeness (via Traceability Manager)
    if criteria.require_traceability_complete:
        traceability_result = check_traceability_for_phase(phase, sil_level)
        if not traceability_result.passed:
            result.add_error(f"Traceability incomplete: {traceability_result.message}")
    
    return result

def check_traceability_for_phase(phase: str, sil_level: int) -> TraceabilityResult:
    """Call Traceability Manager to validate traceability."""
    
    # Import traceability manager
    from traceability_manager import TraceabilityManager
    
    tm = TraceabilityManager()
    
    # Validate all required matrices for phase
    required_matrices = get_required_matrices_for_phase(phase)
    
    for matrix_name in required_matrices:
        validation = tm.validate_matrix(matrix_name, sil_level)
        if not validation.passed:
            return TraceabilityResult(
                passed=False,
                message=f"Matrix {matrix_name}: {validation.message}"
            )
    
    return TraceabilityResult(passed=True, message="All traceability complete")
```

#### Integration Point 2: Baseline Creation

**Scenario**: When Workflow Manager creates baseline, it should verify traceability is complete

**Flow**:
```python
# workflow_manager.py - Baseline Manager

def create_baseline(phase: str, tag: str) -> BaselineManifest:
    # Before creating baseline, validate traceability
    from traceability_manager import TraceabilityManager
    
    tm = TraceabilityManager()
    matrices = get_required_matrices_for_phase(phase)
    
    for matrix_name in matrices:
        validation = tm.validate_matrix(matrix_name, sil_level)
        if not validation.passed:
            raise BaselineError(
                f"Cannot create baseline: Traceability incomplete for {matrix_name}"
            )
    
    # Proceed with baseline creation
    # ... create Git tag, manifest, etc. ...
```

---

### 4.2 Traceability Manager ↔ Deliverables Metadata Integration

#### Integration Point 3: Determine Required Matrices from Metadata

**Scenario**: Traceability Manager uses deliverables metadata to determine which matrices are required

**Flow**:
```python
# traceability_manager.py

def get_required_matrices_for_deliverable(deliverable_id: str) -> List[str]:
    """Determine required traceability matrices from deliverable metadata."""
    
    from deliverables.loader import load_deliverable
    
    metadata = load_deliverable(deliverable_id)
    
    matrices = []
    
    # Check depends_on (backward traceability)
    for dep in metadata.get('depends_on', []):
        matrix_name = f"{normalize_name(dep)}_to_{normalize_name(deliverable_id)}"
        matrices.append(matrix_name)
    
    # Check feeds_into (forward traceability)
    for feed in metadata.get('feeds_into', []):
        matrix_name = f"{normalize_name(deliverable_id)}_to_{normalize_name(feed)}"
        matrices.append(matrix_name)
    
    return matrices

# Example:
# Software Requirements Specification metadata:
#   depends_on: ["System-Requirements-Specification"]
#   feeds_into: ["Software-Architecture-Specification"]
# 
# Returns: [
#   "system_requirements_to_software_requirements",
#   "software_requirements_to_software_architecture"
# ]
```

---

### 4.3 Workflow Manager ↔ LIFECYCLE_STATE.md Integration

#### Integration Point 4: Update Lifecycle State

**Scenario**: Workflow Manager updates LIFECYCLE_STATE.md when documents change status

**Flow**:
```python
# workflow_manager.py - State Manager

def update_document_status(document_id: str, new_status: WorkflowStatus):
    """Update document status in workflow state AND LIFECYCLE_STATE.md."""
    
    # Update workflow state file
    workflow = load_workflow_state(document_id)
    workflow.status = new_status
    save_workflow_state(workflow)
    
    # Update LIFECYCLE_STATE.md
    lifecycle = parse_lifecycle_state("LIFECYCLE_STATE.md")
    
    # Find deliverable in lifecycle state
    for phase in lifecycle.phases:
        for deliverable in phase.deliverables:
            if deliverable.id == document_id:
                deliverable.status = new_status
                deliverable.last_updated = datetime.now().isoformat()
    
    # Write back to LIFECYCLE_STATE.md
    write_lifecycle_state("LIFECYCLE_STATE.md", lifecycle)
```

---

### 4.4 Both Tools ↔ workspace.py Integration

#### Integration Point 5: Unified CLI Interface

**Scenario**: Both tools accessible through workspace.py CLI

**Implementation**:
```python
# tools/workspace.py (extended)

class WorkspaceManager:
    def __init__(self):
        self.workflow_manager = WorkflowManager()
        self.traceability_manager = TraceabilityManager()
    
    def workflow(self, args):
        """Handle workflow subcommand."""
        return self.workflow_manager.execute(args)
    
    def traceability(self, args):
        """Handle traceability subcommand."""
        return self.traceability_manager.execute(args)

# CLI usage:
# workspace.py workflow submit SRS --for-review
# workspace.py traceability validate --phase requirements --sil 3
```

---

## 5. Agent and Skill Integration

### 5.1 Agent Workflow with Tools

#### Example: Requirements Engineer (REQ) Agent

```
User: "Create Software Requirements Specification for Train Control System, SIL 3"
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ REQ Agent (via /req command)                                    │
└─────────────────────────────────────────────────────────────────┘
     │
     │ Step 1: Load en50128-requirements skill
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ en50128-requirements skill                                       │
│ • Workflows: requirements-specification.md                       │
│ • Resources: requirement-quality-checklist.md                    │
│ • Templates: Software-Requirements-Specification-template.md     │
└─────────────────────────────────────────────────────────────────┘
     │
     │ Step 2: Create SRS document (using template)
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ REQ Agent: Create docs/Software-Requirements-Specification.md   │
└─────────────────────────────────────────────────────────────────┘
     │
     │ Step 3: Initialize workflow state
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ Workflow Manager                                                 │
│ $ workspace.py workflow submit SRS --for-review                 │
│ (Automatic: REQ agent calls this after document creation)        │
└─────────────────────────────────────────────────────────────────┘
     │
     │ Step 4: Create traceability matrix (backward: System → Software)
     │
     ▼
┌─────────────────────────────────────────────────────────────────┐
│ Traceability Manager                                             │
│ $ traceability.py create --from system-requirements              │
│   --to requirements                                              │
│ (Automatic: REQ agent calls this per en50128-requirements skill) │
└─────────────────────────────────────────────────────────────────┘
     │
     │ Output: SRS created, workflow initiated, traceability matrix ready
     │
     ▼
User: Review and approve document through workflow
```

---

### 5.2 Skill Integration with Tools

**en50128-requirements skill** (`.opencode/skills/en50128-requirements/SKILL.md`) should be updated:

```markdown
## Tool Integration

This skill integrates with the following tools:

### Workflow Manager
- **When to use**: After creating or modifying requirements documents
- **Commands**:
  - `workspace.py workflow submit <doc> --for-review` - Submit document for review
  - `workspace.py workflow status <doc>` - Check approval status

### Traceability Manager
- **When to use**: After establishing requirements traceability
- **Commands**:
  - `traceability.py create --from system-requirements --to requirements`
  - `traceability.py validate --matrix system_to_software_requirements --sil <level>`
  - `traceability.py report --from requirements --to architecture,tests`

## Agent Workflow Integration

When invoked via `/req` command, the agent should:

1. **Create requirements document** using template
2. **Initialize workflow** via Workflow Manager
3. **Create traceability matrices** via Traceability Manager
4. **Validate completeness** using both tools
5. **Generate reports** embedding traceability
```

Similar integration guidance should be added to:
- `en50128-design` skill (for DES agent)
- `en50128-implementation` skill (for IMP agent)
- `en50128-testing` skill (for TST agent)
- `en50128-verification` skill (for VER agent)
- `en50128-validation` skill (for VAL agent)

---

## 6. File System Organization

### 6.1 Project Directory Structure (with Tools)

```
project_root/
├── LIFECYCLE_STATE.md                      # Lifecycle state (read/write by both tools)
├── docs/                                   # EN 50128 deliverables
│   ├── Software-Requirements-Specification.md
│   ├── Software-Architecture-Specification.md
│   └── ...
├── evidence/                               # Evidence artifacts
│   └── traceability/                       # Traceability Manager storage
│       ├── system_to_software_requirements.csv
│       ├── system_to_software_requirements.json
│       ├── system_to_software_requirements.md
│       ├── requirements_to_architecture.csv
│       ├── requirements_to_architecture.json
│       ├── requirements_to_architecture.md
│       └── index.json                      # Master index
├── .workflow/                              # Workflow Manager storage
│   ├── Software-Requirements-Specification.yaml  # Workflow state
│   ├── Software-Architecture-Specification.yaml
│   ├── history/                            # Event logs
│   │   ├── Software-Requirements-Specification.log
│   │   └── Software-Architecture-Specification.log
│   ├── change-requests/                    # Change requests
│   │   ├── CR-001.yaml
│   │   └── index.yaml
│   ├── baselines/                          # Baseline manifests
│   │   ├── REQ-BASELINE-v1.0.0.yaml
│   │   └── index.yaml
│   └── config.yaml                         # Workflow configuration
├── deliverables/                           # Deliverable metadata (read by both tools)
│   ├── requirements/
│   │   └── Software-Requirements-Specification.yaml
│   └── architecture/
│       └── Software-Architecture-Specification.yaml
└── tools/                                  # Tool implementations
    ├── workspace.py                        # Extended with workflow/traceability
    ├── workflow_manager.py                 # NEW: Workflow Manager module
    ├── traceability_manager.py             # NEW: Traceability Manager module
    └── ...
```

---

## 7. Tool Communication Protocols

### 7.1 Python API Integration

**Approach**: Tools import each other as Python modules for direct communication

```python
# workflow_manager.py calling traceability_manager.py

from traceability_manager import TraceabilityManager

def validate_phase_gate(phase: str, sil_level: int):
    tm = TraceabilityManager()
    result = tm.validate_phase_traceability(phase, sil_level)
    return result
```

**Advantages**:
- Direct function calls (fast, no IPC overhead)
- Type-safe (Python type hints)
- Easy debugging
- Shared data models

---

### 7.2 CLI Integration (for Agents/Skills)

**Approach**: Agents/skills call tools via CLI commands

```bash
# en50128-requirements skill (workflow.md)

# After creating SRS, submit for review
workspace.py workflow submit SRS --for-review

# Create traceability matrix
traceability.py create --from system-requirements --to requirements

# Validate traceability before phase gate
traceability.py validate --phase requirements --sil 3
```

**Advantages**:
- Simple for agents to invoke
- Language-agnostic (skills can use bash, Python, etc.)
- Clear audit trail (CLI commands logged)

---

### 7.3 Configuration File Integration

**Shared Configuration**: `.traceability.yaml` and `.workflow/config.yaml` can reference each other

```yaml
# .traceability.yaml

project: TrainControl
sil_level: 3
workflow_integration:
  enabled: true
  workflow_config: .workflow/config.yaml
validation:
  check_workflow_state: true  # Verify documents approved before validating traceability
```

```yaml
# .workflow/config.yaml

project: TrainControl
sil_level: 3
traceability_integration:
  enabled: true
  traceability_path: evidence/traceability/
phase_gates:
  requirements:
    require_traceability: true
    min_coverage: 1.0  # 100% for SIL 3
```

---

## 8. Tool Coordination Workflows

### 8.1 End-to-End: Requirements Phase Completion

```
┌─────────────────────────────────────────────────────────────────┐
│ Phase 2: Requirements - Complete Workflow with Tools            │
└─────────────────────────────────────────────────────────────────┘

REQ Agent: Create SRS
     │
     ▼
Workflow Manager: Initialize workflow (SRS → Draft)
     │
     ▼
Traceability Manager: Create traceability matrices
     │  • system_to_software_requirements
     │  • requirements_to_architecture (forward)
     │  • requirements_to_tests
     │
     ▼
REQ Agent: Populate traceability matrices
     │
     ▼
Traceability Manager: Validate matrices
     │  ✅ Coverage: 100%
     │  ✅ No orphans
     │  ✅ All requirements have test cases
     │
     ▼
Workflow Manager: Submit SRS for review (Draft → Review)
     │
     ▼
Workflow Manager: Route through reviewers (PEER → QUA → VER → VAL → PM)
     │  (Each approval recorded, independence validated)
     │
     ▼
Workflow Manager: All approvals obtained (Review → Approved)
     │
     ▼
Workflow Manager: Update LIFECYCLE_STATE.md (SRS = Approved)
     │
     ▼
COD: Check if all Phase 2 deliverables approved
     │  • SRS ✅
     │  • Software Test Specification ✅
     │  • Software Verification Plan ✅
     │
     ▼
Workflow Manager: Gate check (requirements phase, SIL 3)
     │  ├─► Check: All deliverables approved ✅
     │  ├─► Check: QUA reviews passed ✅
     │  ├─► Check: Independent VER approval ✅
     │  └─► Check: Traceability complete (calls Traceability Manager) ✅
     │
     ▼
Traceability Manager: Validate phase traceability
     │  ├─► Matrix: system_to_software_requirements (100% ✅)
     │  ├─► Matrix: requirements_to_tests (100% ✅)
     │  └─► Matrix: hazards_to_requirements (100% ✅)
     │
     ▼
Workflow Manager: Gate check PASSED ✅
     │
     ▼
Workflow Manager: Create baseline (REQ-BASELINE-v1.0.0)
     │  ├─► Calculate checksums
     │  ├─► Create Git tag
     │  ├─► Generate baseline manifest
     │  └─► Transition deliverables: Approved → Baseline
     │
     ▼
Workflow Manager: Update LIFECYCLE_STATE.md
     │  • Phase 2 status: Complete
     │  • Baseline: REQ-BASELINE-v1.0.0
     │
     ▼
COD: Advance to Phase 3 (Architecture & Design)
     │
     ▼
End (Ready for Architecture phase)
```

---

## 9. Performance Considerations

### 9.1 Traceability Manager Performance

**Large Matrix Handling** (1000+ links):

- **CSV storage**: Fast for sequential reads/writes
- **JSON index**: Enables O(1) lookup by source/target ID
- **Lazy loading**: Load matrices on-demand, not all at once
- **Caching**: Cache frequently-queried matrices in memory

**Optimization**:
```python
class TraceabilityManager:
    def __init__(self):
        self._matrix_cache = {}  # In-memory cache
        self._index_cache = {}   # Index cache
    
    def load_matrix(self, matrix_name: str) -> TraceabilityMatrix:
        if matrix_name in self._matrix_cache:
            return self._matrix_cache[matrix_name]  # Cache hit
        
        # Cache miss: load from disk
        matrix = self._load_from_disk(matrix_name)
        self._matrix_cache[matrix_name] = matrix
        return matrix
```

---

### 9.2 Workflow Manager Performance

**State File I/O**:

- Use YAML for human-readability (trade-off: slower than JSON)
- Cache workflow states in memory during CLI session
- Batch writes (update multiple documents, then write once)

**Git Operations**:

- Git tag creation is fast (milliseconds)
- Checksum calculation can be slow for large files
  - Solution: Use `hashlib` with chunked reads
  - Solution: Parallelize checksum calculation for multiple files

---

## 10. Summary

This architecture provides:

1. **Two Specialized Tools**:
   - **Traceability Manager**: Comprehensive traceability management across lifecycle
   - **Workflow Manager**: Document lifecycle, reviews, approvals, baselines

2. **Seamless Integration**:
   - Tools communicate via Python API (fast, type-safe)
   - Unified CLI interface via `workspace.py`
   - Shared data (LIFECYCLE_STATE.md, deliverables metadata)

3. **Agent and Skill Support**:
   - Tools invoked automatically by agents (REQ, DES, IMP, etc.)
   - Skills provide workflow guidance and tool integration
   - Document-centric architecture supported

4. **EN 50128 Compliance**:
   - SIL-dependent validation rules
   - Independence enforcement (SIL 3-4)
   - Full audit trail (approvals, traceability)
   - Configuration baselines with Git

5. **Scalability**:
   - Handles large projects (1000+ requirements)
   - Efficient caching and indexing
   - Modular design for future enhancements

**Next Steps**: Implement Phase 1 (core infrastructure) for both tools.

---

**END OF ARCHITECTURE DOCUMENT**
