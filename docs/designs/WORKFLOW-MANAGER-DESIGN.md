# Workflow Manager Tool - Design Document

**Version**: 1.0  
**Date**: 2026-03-13  
**Status**: Design Phase  
**Author**: OpenCode AI Agent

---

## 1. Executive Summary

The **Workflow Manager** is a Python-based CLI tool for managing document lifecycle, review workflows, approvals, and baselines across the EN 50128 software development lifecycle. It extends the existing `tools/workspace.py` functionality to support SIL-dependent review processes, approval tracking, and phase gate validation.

**Key Features**:
- Track document lifecycle states (Draft → Review → Approved → Baseline)
- Manage SIL-dependent review workflows (4 approvals for SIL 0-2, 8 approvals for SIL 3-4)
- Track approvals and signatures with role-based access control
- Create configuration baselines (Git tags) with immutable snapshots
- Phase gate validation (verify prerequisites before advancing phases)
- Generate workflow status reports and approval tracking dashboards
- Integration with Git, LIFECYCLE_STATE.md, and deliverables metadata

**EN 50128 Compliance**:
- Independent verification and validation for SIL 3-4
- Mandatory peer reviews for all SILs
- Quality assurance checks before verification
- Configuration management and baseline control
- Traceability of approvals and changes

---

## 2. Use Cases

### UC-1: Track Document Lifecycle
**Actor**: All roles (REQ, DES, IMP, QUA, VER, VAL, etc.)  
**Goal**: Track document as it progresses through workflow states

**Scenario**:
1. REQ creates Software Requirements Specification (SRS) - status: **Draft**
2. REQ marks document ready for review: `workflow.py submit SRS --for-review`
3. System transitions SRS to **Review** state
4. System notifies reviewers (Peer, QUA, VER, VAL, PM) based on SIL level
5. Each reviewer approves or rejects with comments
6. Once all approvals obtained, REQ marks as approved: `workflow.py approve SRS`
7. System transitions SRS to **Approved** state
8. CM creates baseline: `workflow.py baseline SRS --tag v1.0.0`
9. System transitions SRS to **Baseline** state with Git tag

**Output**:
- Document state stored in `.workflow/{document_id}.yaml`
- State transitions logged in `.workflow/history/{document_id}.log`
- Approval records with timestamps and signatures
- Git baseline tag (immutable snapshot)

---

### UC-2: SIL-Dependent Review Workflow
**Actor**: Project Manager (PM), Configuration Manager (CM)  
**Goal**: Route document through appropriate review workflow based on SIL level

**Scenario - SIL 0-2** (4 approvals):
1. Author (REQ) submits Software Requirements Specification
2. System routes to: **Author → Peer Reviewer → QUA → PM**
3. Each reviewer approves in sequence
4. After 4 approvals, document marked **Approved**

**Scenario - SIL 3-4** (8 approvals):
1. Author (REQ) submits Software Requirements Specification
2. System routes to: **Author → Peer Reviewer → QUA → Safety Manager → Independent VER → Independent VAL → Assessor → PM**
3. Each reviewer approves in sequence
4. **Independence check**: VER and VAL must be different people from author, peer, PM
5. After 8 approvals, document marked **Approved**

**Output**:
- Workflow routing based on SIL level
- Independence validation (SIL 3-4)
- Approval tracking with role verification
- Rejection handling (return to author with comments)

---

### UC-3: Approval Tracking with Signatures
**Actor**: All reviewers  
**Goal**: Track who approved, when, and with what comments

**Scenario**:
1. VER reviewer assigned to verify Software Design Specification
2. VER runs: `workflow.py review SDS --role VER --approve --comment "Static analysis passed, complexity within limits"`
3. System records:
   - Reviewer: VER (John Doe)
   - Timestamp: 2026-03-13T10:30:00Z
   - Decision: Approved
   - Comment: "Static analysis passed, complexity within limits"
   - Signature: SHA256 hash of approval record
4. System advances document to next review stage
5. PM can view all approvals: `workflow.py status SDS --approvals`

**Output**:
- Approval record with timestamp, role, person, comment, signature
- Audit trail of all review activities
- Verification of role-based permissions (VER can only approve as VER, not as PM)

---

### UC-4: Rejection and Rework Workflow
**Actor**: Quality Assurance (QUA)  
**Goal**: Reject document with issues and return to author for fixes

**Scenario**:
1. QUA reviews Software Design Specification
2. QUA finds issues: missing traceability, complexity violations
3. QUA runs: `workflow.py review SDS --role QUA --reject --comment "Traceability incomplete (3 requirements not traced), cyclomatic complexity violation in module X"`
4. System:
   - Records rejection with comments
   - Transitions document back to **Draft** state
   - Notifies author (DES) with rejection comments
   - Increments rework iteration counter
5. DES fixes issues and resubmits: `workflow.py submit SDS --for-review`
6. System routes through review workflow again (all reviewers must re-approve)

**Output**:
- Rejection record with detailed comments
- Document returned to Draft state
- Rework iteration counter (for metrics)
- Notification to author with action items

---

### UC-5: Create Configuration Baseline
**Actor**: Configuration Manager (CM)  
**Goal**: Create immutable baseline of approved deliverables with Git tag

**Scenario**:
1. All Phase 2 (Requirements) deliverables approved:
   - Software Requirements Specification ✅
   - Software Test Specification ✅
   - Software Verification Plan ✅
2. CM runs: `workflow.py baseline --phase requirements --tag REQ-BASELINE-v1.0.0 --project TrainControl`
3. System:
   - Validates all required deliverables are **Approved**
   - Creates Git tag: `REQ-BASELINE-v1.0.0`
   - Transitions all deliverables to **Baseline** state
   - Generates baseline manifest (list of files, versions, checksums)
   - Updates LIFECYCLE_STATE.md with baseline reference
4. After baseline, any changes require Change Request (CR)

**Output**:
- Git tag (immutable snapshot)
- Baseline manifest with file checksums
- Baseline metadata (date, approver, deliverables included)
- LIFECYCLE_STATE.md updated with baseline info

---

### UC-6: Phase Gate Validation
**Actor**: Lifecycle Coordinator (COD), Project Manager (PM)  
**Goal**: Validate all prerequisites met before advancing to next lifecycle phase

**Scenario**:
1. Project completing Phase 2 (Requirements), preparing to advance to Phase 3 (Architecture & Design)
2. COD runs: `workflow.py gate-check requirements --sil 3 --project TrainControl`
3. System validates:
   - ✅ All mandatory deliverables for Phase 2 (SIL 3) exist
   - ✅ All deliverables in **Approved** or **Baseline** state
   - ✅ Traceability matrices 100% complete (SIL 3 requirement)
   - ✅ All QUA reviews passed
   - ✅ Independent VER approval obtained
   - ❌ **FAIL**: Software Verification Plan missing VAL approval
4. System reports: **Gate Check FAILED - Missing VAL approval for Software Verification Plan**
5. PM ensures VAL approves Software Verification Plan
6. COD re-runs gate check: **Gate Check PASSED**
7. COD advances to Phase 3: `workflow.py advance-phase --to architecture --project TrainControl`

**Output**:
- Gate check report (PASS/FAIL with details)
- List of missing prerequisites
- Phase transition confirmation (if passed)
- LIFECYCLE_STATE.md updated with new phase

---

### UC-7: Generate Workflow Status Report
**Actor**: Project Manager (PM), Quality Assurance (QUA)  
**Goal**: Generate comprehensive workflow status report for project review meeting

**Scenario**:
1. PM preparing for weekly status meeting
2. PM runs: `workflow.py status --project TrainControl --format markdown`
3. System generates report:
   - **Overall Project Status**: Phase 2 (Requirements) - 85% complete
   - **Deliverables Status**:
     - Software Requirements Specification: **Approved** ✅
     - Software Test Specification: **Review** (pending VER approval) ⏳
     - Software Verification Plan: **Draft** (author: VER) 📝
   - **Approval Metrics**:
     - Total approvals: 12/16 (75%)
     - Average approval time: 2.3 days
     - Rejections: 1 (SDS rejected by QUA, reworked, re-approved)
   - **Blockers**:
     - Software Test Specification waiting for VER approval (3 days overdue)
   - **Next Actions**:
     - VER to complete review of Software Test Specification by 2026-03-15
     - VER to complete Software Verification Plan by 2026-03-18
4. PM uses report in status meeting

**Output**:
- Workflow status report (Markdown/JSON/HTML)
- Approval metrics and trends
- Blockers and overdue reviews
- Actionable next steps

---

### UC-8: Handle Change Requests After Baseline
**Actor**: Configuration Manager (CM), Change Control Board (CCB)  
**Goal**: Process change request for baselined document

**Scenario**:
1. Software Requirements Specification baselined as v1.0.0
2. Customer requests new requirement after baseline
3. REQ submits change request: `workflow.py change-request SRS --description "Add requirement SW-REQ-051: Support emergency stop button" --impact high`
4. System:
   - Creates Change Request (CR-001)
   - Sets SRS status to **Change Pending**
   - Notifies CCB members (PM, CM, Safety Manager, QUA)
5. CCB reviews and approves: `workflow.py change-request CR-001 --ccb-approve --comment "Safety-critical change, requires full re-verification"`
6. REQ updates SRS (creates new branch from baseline tag)
7. REQ submits updated SRS for review (full review workflow required)
8. After approvals, CM creates new baseline: v1.1.0
9. System records change traceability: v1.0.0 → CR-001 → v1.1.0

**Output**:
- Change Request record (CR-001) with impact analysis
- CCB approval record
- New baseline (v1.1.0) with change traceability
- Change history log

---

### UC-9: Independent Reviewer Assignment (SIL 3-4)
**Actor**: V&V Manager (VMGR), Project Manager (PM)  
**Goal**: Ensure independent reviewers assigned for SIL 3-4 projects

**Scenario**:
1. SIL 3 project requires independent VER and VAL reviewers
2. PM attempts to assign VER role to same person as DES (designer)
3. PM runs: `workflow.py assign-reviewer SDS --role VER --person "Jane Doe"`
4. System checks independence rules:
   - Jane Doe is author of SDS (role: DES)
   - **VIOLATION**: VER cannot review own work (EN 50128 Section 5.1.2.10i)
5. System rejects assignment: **ERROR: Independence violation - VER cannot be same person as DES (EN 50128 5.1.2.10i)**
6. PM assigns independent reviewer: `workflow.py assign-reviewer SDS --role VER --person "John Smith"`
7. System validates: John Smith has no conflict (not DES, not REQ, not IMP)
8. System accepts assignment ✅

**Output**:
- Independence validation for reviewer assignments
- Rejection of conflicting assignments with EN 50128 reference
- Approval record with independence verification

---

## 3. CLI Interface Design

### 3.1 Integration Approach

**Recommended**: Extend `tools/workspace.py` with workflow commands (Option B from design questions).

**Rationale**:
- `workspace.py` already manages project context and LIFECYCLE_STATE.md
- Workflow is inherently project-specific (needs project context)
- Unified CLI interface better for users (one tool instead of two)
- Can leverage existing workspace infrastructure

**Implementation**: Add `workflow` subcommand to `workspace.py`:

```bash
workspace.py workflow <command> [options]
```

---

### 3.2 Commands

#### 3.2.1 `submit` - Submit Document for Review

```bash
workspace.py workflow submit <document_id> [--for-review] [--message <msg>]
```

**Arguments**:
- `<document_id>`: Document identifier (e.g., "SRS", "Software-Requirements-Specification")
- `--for-review`: Mark ready for review (transition to Review state)
- `--message`: Submission message/notes

**Example**:
```bash
workspace.py workflow submit SRS --for-review --message "Requirements complete, ready for peer review"
# Output: SRS submitted for review. Notified: Peer Reviewer, QUA, VER, VAL, PM
```

---

#### 3.2.2 `review` - Review and Approve/Reject Document

```bash
workspace.py workflow review <document_id> --role <role> [--approve|--reject] [--comment <text>]
```

**Arguments**:
- `<document_id>`: Document identifier
- `--role`: Reviewer role (PEER, QUA, VER, VAL, SAFETY_MGR, ASSESSOR, PM)
- `--approve`: Approve document (advance to next review stage)
- `--reject`: Reject document (return to Draft with comments)
- `--comment`: Review comments (required for rejection, optional for approval)

**Example**:
```bash
workspace.py workflow review SRS --role VER --approve --comment "Verification complete, traceability validated"
# Output: SRS approved by VER. Next reviewer: VAL
```

---

#### 3.2.3 `approve` - Mark Document as Approved

```bash
workspace.py workflow approve <document_id> [--force]
```

**Arguments**:
- `<document_id>`: Document identifier
- `--force`: Override approval checks (requires PM role, use with caution)

**Description**: Transition document to Approved state after all reviews complete.

**Example**:
```bash
workspace.py workflow approve SRS
# Output: SRS marked as APPROVED. All required approvals obtained (8/8).
```

---

#### 3.2.4 `baseline` - Create Configuration Baseline

```bash
workspace.py workflow baseline [<document_id>|--phase <phase>] --tag <tag_name> [--message <msg>]
```

**Arguments**:
- `<document_id>`: Single document to baseline (optional)
- `--phase`: Baseline all deliverables for phase (e.g., "requirements", "design")
- `--tag`: Git tag name for baseline (e.g., "REQ-BASELINE-v1.0.0")
- `--message`: Baseline description

**Example**:
```bash
workspace.py workflow baseline --phase requirements --tag REQ-BASELINE-v1.0.0 --message "Requirements phase complete, all deliverables approved"
# Output: Baseline created: REQ-BASELINE-v1.0.0 (3 deliverables, Git tag created)
```

---

#### 3.2.5 `gate-check` - Validate Phase Gate Prerequisites

```bash
workspace.py workflow gate-check <phase> [--sil <level>] [--strict]
```

**Arguments**:
- `<phase>`: Phase identifier (requirements, design, implementation, integration, validation)
- `--sil`: SIL level (reads from LIFECYCLE_STATE.md if not specified)
- `--strict`: Strict mode (fail on warnings, not just errors)

**Example**:
```bash
workspace.py workflow gate-check requirements --sil 3
# Output: Gate Check PASSED. All prerequisites met. Ready to advance to Phase 3 (Architecture & Design).
```

---

#### 3.2.6 `advance-phase` - Advance to Next Lifecycle Phase

```bash
workspace.py workflow advance-phase --to <phase> [--force]
```

**Arguments**:
- `--to`: Target phase (architecture, design, implementation, etc.)
- `--force`: Skip gate check (requires COD role, use with caution)

**Example**:
```bash
workspace.py workflow advance-phase --to architecture
# Output: Phase advanced: Phase 2 (Requirements) → Phase 3 (Architecture & Design)
#         LIFECYCLE_STATE.md updated.
```

---

#### 3.2.7 `status` - Generate Workflow Status Report

```bash
workspace.py workflow status [<document_id>|--phase <phase>|--all] [--format <format>] [--approvals] [--history]
```

**Arguments**:
- `<document_id>`: Show status for specific document
- `--phase`: Show status for all deliverables in phase
- `--all`: Show status for entire project
- `--format`: Output format (text, markdown, json, html)
- `--approvals`: Include detailed approval records
- `--history`: Include state transition history

**Example**:
```bash
workspace.py workflow status --all --format markdown
# Output: Comprehensive workflow status report (Markdown format)
```

---

#### 3.2.8 `change-request` - Create/Manage Change Requests

```bash
workspace.py workflow change-request <document_id|cr_id> [--create] [--description <text>] [--impact <level>] [--ccb-approve|--ccb-reject] [--comment <text>]
```

**Arguments**:
- `<document_id>`: Document for new change request
- `<cr_id>`: Existing change request ID (e.g., CR-001)
- `--create`: Create new change request
- `--description`: Change description
- `--impact`: Impact level (low, medium, high, critical)
- `--ccb-approve`: CCB approves change request
- `--ccb-reject`: CCB rejects change request
- `--comment`: CCB comments

**Example**:
```bash
# Create change request
workspace.py workflow change-request SRS --create --description "Add emergency stop requirement" --impact high
# Output: Change Request created: CR-001

# CCB approval
workspace.py workflow change-request CR-001 --ccb-approve --comment "Approved, requires full re-verification"
# Output: CR-001 approved by CCB. SRS ready for modification.
```

---

#### 3.2.9 `assign-reviewer` - Assign Reviewer to Document

```bash
workspace.py workflow assign-reviewer <document_id> --role <role> --person <name> [--force]
```

**Arguments**:
- `<document_id>`: Document identifier
- `--role`: Reviewer role (PEER, QUA, VER, VAL, SAFETY_MGR, ASSESSOR, PM)
- `--person`: Person name or ID
- `--force`: Override independence checks (dangerous, use with caution)

**Example**:
```bash
workspace.py workflow assign-reviewer SRS --role VER --person "John Smith"
# Output: VER assigned to SRS: John Smith (independence validated ✅)
```

---

#### 3.2.10 `history` - Show Document Workflow History

```bash
workspace.py workflow history <document_id> [--format <format>]
```

**Arguments**:
- `<document_id>`: Document identifier
- `--format`: Output format (text, json, timeline)

**Example**:
```bash
workspace.py workflow history SRS
# Output:
# 2026-03-01 10:00 | Draft     | Created by REQ (Jane Doe)
# 2026-03-05 14:30 | Review    | Submitted for review
# 2026-03-06 09:15 | Review    | Approved by PEER (Alice Johnson)
# 2026-03-07 11:45 | Review    | Approved by QUA (Bob Wilson)
# 2026-03-08 16:00 | Review    | Approved by VER (John Smith)
# 2026-03-10 10:30 | Approved  | All approvals obtained
# 2026-03-12 14:00 | Baseline  | Baselined as REQ-BASELINE-v1.0.0
```

---

### 3.3 Global Options

```bash
--project <name>    Project name (overrides workspace context)
--sil <level>       SIL level (overrides LIFECYCLE_STATE.md)
--verbose, -v       Verbose output
--quiet, -q         Quiet mode (errors only)
--help, -h          Show help
```

---

## 4. Data Models

### 4.1 Document Workflow State

```python
@dataclass
class WorkflowState:
    """Represents the current workflow state of a document."""
    
    # Document identifiers
    document_id: str            # e.g., "SRS", "Software-Requirements-Specification"
    document_title: str         # Human-readable title
    document_type: str          # Deliverable type (from metadata)
    document_path: str          # File path
    
    # Workflow state
    status: WorkflowStatus      # Draft, Review, Approved, Baseline
    phase: str                  # Lifecycle phase (requirements, design, etc.)
    sil_level: int              # SIL level (0-4)
    
    # Authorship
    author_role: str            # Role (REQ, DES, IMP, etc.)
    author_name: str            # Person name
    created_date: str           # ISO 8601 timestamp
    modified_date: str          # ISO 8601 timestamp
    
    # Review workflow
    current_reviewer: str       # Current reviewer role (or None if approved)
    pending_reviewers: List[str]  # List of remaining reviewers
    approvals: List[Approval]   # List of approval records
    rejections: List[Rejection] # List of rejection records (if any)
    
    # Baseline
    baseline_tag: str           # Git tag (if baselined)
    baseline_date: str          # Baseline date
    
    # Change control
    change_requests: List[str]  # List of CR IDs affecting this document
    version: str                # Document version
    
    # Metadata
    checksum: str               # SHA256 checksum of document
    file_size: int              # File size in bytes
```

---

### 4.2 Workflow Status Enumeration

```python
class WorkflowStatus(Enum):
    """EN 50128 document workflow states."""
    
    DRAFT = "draft"             # Document being authored
    REVIEW = "review"           # Document in review workflow
    APPROVED = "approved"       # All reviews complete, approved for use
    BASELINE = "baseline"       # Configuration baseline created (immutable)
    CHANGE_PENDING = "change_pending"  # Change request pending CCB approval
    OBSOLETE = "obsolete"       # Superseded by newer version
```

---

### 4.3 Approval Record

```python
@dataclass
class Approval:
    """Represents a single approval in the review workflow."""
    
    # Reviewer identity
    reviewer_role: str          # Role (PEER, QUA, VER, VAL, etc.)
    reviewer_name: str          # Person name
    
    # Approval details
    approved: bool              # True = approved, False = rejected
    timestamp: str              # ISO 8601 timestamp
    comment: str                # Review comments
    
    # Verification
    signature: str              # SHA256 hash of approval record (for integrity)
    independent: bool           # Was this an independent review? (SIL 3-4)
    
    # Traceability
    document_id: str            # Document being reviewed
    document_version: str       # Document version at time of review
    document_checksum: str      # Document checksum at time of review
```

---

### 4.4 Rejection Record

```python
@dataclass
class Rejection:
    """Represents a rejection in the review workflow."""
    
    # Reviewer identity
    reviewer_role: str
    reviewer_name: str
    
    # Rejection details
    timestamp: str
    comment: str                # Required - must explain rejection reasons
    issues: List[Issue]         # Structured issue list
    
    # Resolution
    resolved: bool              # Has rejection been addressed?
    resolution_date: str        # Date issues resolved
    resolution_comment: str     # How issues were resolved
    
    # Rework tracking
    rework_iteration: int       # Rework iteration number
```

---

### 4.5 Issue (for Rejections)

```python
@dataclass
class Issue:
    """Represents a specific issue identified during review."""
    
    issue_id: str               # e.g., "ISS-001"
    severity: str               # critical, major, minor
    category: str               # traceability, complexity, style, safety, etc.
    description: str            # Issue description
    location: str               # Location in document (line number, section, etc.)
    recommendation: str         # How to fix
    
    # Resolution
    resolved: bool
    resolution: str             # How issue was fixed
```

---

### 4.6 Review Workflow Definition

```python
@dataclass
class ReviewWorkflow:
    """Defines the review workflow for a SIL level."""
    
    sil_level: int
    reviewers: List[str]        # Ordered list of reviewer roles
    require_independence: bool  # Require independent VER/VAL?
    allow_parallel: bool        # Allow parallel reviews (vs. sequential)?
    
    # Approval rules
    min_approvals: int          # Minimum number of approvals required
    require_all: bool           # Require all reviewers to approve?
    allow_delegation: bool      # Allow reviewer to delegate?
    
    # Timing
    review_timeout_days: int    # Days before review is overdue

# SIL-dependent workflows
REVIEW_WORKFLOWS = {
    0: ReviewWorkflow(
        sil_level=0,
        reviewers=["PEER", "PM"],
        require_independence=False,
        allow_parallel=True,
        min_approvals=2,
        require_all=True,
        allow_delegation=True,
        review_timeout_days=7
    ),
    
    1: ReviewWorkflow(
        sil_level=1,
        reviewers=["PEER", "QUA", "PM"],
        require_independence=False,
        allow_parallel=True,
        min_approvals=3,
        require_all=True,
        allow_delegation=True,
        review_timeout_days=7
    ),
    
    2: ReviewWorkflow(
        sil_level=2,
        reviewers=["PEER", "QUA", "PM"],
        require_independence=False,
        allow_parallel=False,  # Sequential for rigor
        min_approvals=3,
        require_all=True,
        allow_delegation=False,
        review_timeout_days=5
    ),
    
    3: ReviewWorkflow(
        sil_level=3,
        reviewers=["PEER", "QUA", "SAFETY_MGR", "VER", "VAL", "PM"],
        require_independence=True,  # VER and VAL must be independent
        allow_parallel=False,
        min_approvals=6,
        require_all=True,
        allow_delegation=False,
        review_timeout_days=5
    ),
    
    4: ReviewWorkflow(
        sil_level=4,
        reviewers=["PEER", "QUA", "SAFETY_MGR", "VER", "VAL", "ASSESSOR", "PM"],
        require_independence=True,
        allow_parallel=False,
        min_approvals=7,
        require_all=True,
        allow_delegation=False,
        review_timeout_days=5
    ),
}
```

---

### 4.7 Change Request

```python
@dataclass
class ChangeRequest:
    """Represents a change request for a baselined document."""
    
    # CR identifiers
    cr_id: str                  # e.g., "CR-001"
    document_id: str            # Document being changed
    
    # Change details
    description: str            # What is being changed
    rationale: str              # Why change is needed
    impact: str                 # low, medium, high, critical
    impact_analysis: str        # Detailed impact analysis
    
    # Affected artifacts
    affected_documents: List[str]     # Other documents impacted
    affected_requirements: List[str]  # Requirements impacted
    affected_code: List[str]          # Code files impacted
    
    # CCB workflow
    ccb_status: str             # pending, approved, rejected
    ccb_decision_date: str      # Date of CCB decision
    ccb_approver: str           # CCB member who approved
    ccb_comment: str            # CCB comments
    
    # Implementation
    implemented: bool           # Has change been implemented?
    implementation_date: str
    new_baseline: str           # New baseline tag (if applicable)
    
    # Metadata
    submitted_by: str           # Person who submitted CR
    submitted_date: str
    priority: str               # low, medium, high, urgent
```

---

### 4.8 Phase Gate Criteria

```python
@dataclass
class PhaseGateCriteria:
    """Defines phase gate validation criteria."""
    
    phase: str                  # Phase identifier (requirements, design, etc.)
    sil_level: int              # SIL level
    
    # Deliverables
    required_deliverables: List[str]  # Mandatory deliverables for phase
    optional_deliverables: List[str]  # Optional deliverables
    
    # State requirements
    require_all_approved: bool        # All deliverables must be approved?
    require_baseline: bool            # Baseline required before advancing?
    
    # Quality gates
    require_qua_review: bool          # QUA review mandatory?
    require_ver_approval: bool        # VER approval mandatory?
    require_val_approval: bool        # VAL approval mandatory? (SIL 3-4)
    
    # Traceability gates
    require_traceability_complete: bool  # 100% traceability required?
    min_traceability_coverage: float     # Minimum coverage (0.0-1.0)
    
    # Testing gates
    require_test_plan: bool           # Test plan required?
    require_test_execution: bool      # Tests executed?
    min_test_coverage: float          # Minimum test coverage
    
    # Verification gates
    require_static_analysis: bool     # Static analysis completed?
    require_complexity_check: bool    # Complexity check passed?
    require_misra_compliance: bool    # MISRA C compliance verified?

# Example: SIL 3 Requirements Phase gate criteria
REQUIREMENTS_GATE_SIL3 = PhaseGateCriteria(
    phase="requirements",
    sil_level=3,
    required_deliverables=[
        "Software-Requirements-Specification",
        "Software-Test-Specification",
        "Software-Verification-Plan"
    ],
    optional_deliverables=[],
    require_all_approved=True,
    require_baseline=False,  # Baseline after gate check passes
    require_qua_review=True,
    require_ver_approval=True,
    require_val_approval=True,
    require_traceability_complete=True,
    min_traceability_coverage=1.0,  # 100% for SIL 3
    require_test_plan=True,
    require_test_execution=False,  # Not yet (requirements phase)
    min_test_coverage=0.0,
    require_static_analysis=False,  # Not yet (no code in requirements phase)
    require_complexity_check=False,
    require_misra_compliance=False
)
```

---

### 4.9 Baseline Manifest

```python
@dataclass
class BaselineManifest:
    """Represents a configuration baseline."""
    
    # Baseline identifiers
    baseline_tag: str           # Git tag (e.g., "REQ-BASELINE-v1.0.0")
    baseline_name: str          # Human-readable name
    phase: str                  # Phase being baselined
    
    # Metadata
    created_date: str           # ISO 8601 timestamp
    created_by: str             # Person who created baseline
    description: str            # Baseline description
    sil_level: int              # SIL level
    
    # Deliverables included
    deliverables: List[BaselineDeliverable]
    
    # Git metadata
    git_commit: str             # Git commit SHA
    git_tag: str                # Git tag name
    
    # Verification
    checksum: str               # SHA256 of entire baseline
    signed: bool                # Digitally signed? (SIL 3-4)
    signature: str              # Digital signature

@dataclass
class BaselineDeliverable:
    """Represents a single deliverable in a baseline."""
    
    document_id: str
    document_path: str
    version: str
    checksum: str               # SHA256 checksum
    file_size: int
    approved_by: List[str]      # List of approver roles
```

---

## 5. Data Storage Formats

### 5.1 Workflow State Files

**Location**: `.workflow/{document_id}.yaml`

**Format**:
```yaml
document_id: Software-Requirements-Specification
document_title: "Software Requirements Specification - Train Control System"
document_type: deliverable
document_path: docs/Software-Requirements-Specification.md

status: approved
phase: requirements
sil_level: 3

author_role: REQ
author_name: Jane Doe
created_date: "2026-03-01T10:00:00Z"
modified_date: "2026-03-10T14:30:00Z"

current_reviewer: null  # All reviews complete
pending_reviewers: []

approvals:
  - reviewer_role: PEER
    reviewer_name: Alice Johnson
    approved: true
    timestamp: "2026-03-06T09:15:00Z"
    comment: "Requirements well-structured, traceability clear"
    signature: "sha256:abc123..."
    independent: false
    document_version: "1.0"
    document_checksum: "sha256:def456..."
  
  - reviewer_role: QUA
    reviewer_name: Bob Wilson
    approved: true
    timestamp: "2026-03-07T11:45:00Z"
    comment: "Template compliance verified, quality criteria met"
    signature: "sha256:ghi789..."
    independent: false
    document_version: "1.0"
    document_checksum: "sha256:def456..."
  
  - reviewer_role: VER
    reviewer_name: John Smith
    approved: true
    timestamp: "2026-03-08T16:00:00Z"
    comment: "Verification complete, traceability validated"
    signature: "sha256:jkl012..."
    independent: true  # Independent verifier (SIL 3)
    document_version: "1.0"
    document_checksum: "sha256:def456..."

rejections: []  # No rejections

baseline_tag: "REQ-BASELINE-v1.0.0"
baseline_date: "2026-03-12T14:00:00Z"

change_requests: []
version: "1.0"
checksum: "sha256:def456..."
file_size: 45823
```

---

### 5.2 Workflow History Log

**Location**: `.workflow/history/{document_id}.log`

**Format** (JSON Lines):
```json
{"timestamp": "2026-03-01T10:00:00Z", "event": "created", "actor_role": "REQ", "actor_name": "Jane Doe", "status": "draft", "comment": "Initial creation"}
{"timestamp": "2026-03-05T14:30:00Z", "event": "submitted", "actor_role": "REQ", "actor_name": "Jane Doe", "status": "review", "comment": "Requirements complete, ready for peer review"}
{"timestamp": "2026-03-06T09:15:00Z", "event": "approved", "actor_role": "PEER", "actor_name": "Alice Johnson", "status": "review", "comment": "Requirements well-structured, traceability clear"}
{"timestamp": "2026-03-07T11:45:00Z", "event": "approved", "actor_role": "QUA", "actor_name": "Bob Wilson", "status": "review", "comment": "Template compliance verified"}
{"timestamp": "2026-03-08T16:00:00Z", "event": "approved", "actor_role": "VER", "actor_name": "John Smith", "status": "review", "comment": "Verification complete"}
{"timestamp": "2026-03-10T10:30:00Z", "event": "approved_final", "actor_role": "PM", "actor_name": "Mary Brown", "status": "approved", "comment": "All approvals obtained"}
{"timestamp": "2026-03-12T14:00:00Z", "event": "baselined", "actor_role": "CM", "actor_name": "Tom Green", "status": "baseline", "comment": "Baselined as REQ-BASELINE-v1.0.0"}
```

---

### 5.3 Change Request Files

**Location**: `.workflow/change-requests/{cr_id}.yaml`

**Format**:
```yaml
cr_id: CR-001
document_id: Software-Requirements-Specification

description: "Add requirement SW-REQ-051: Support emergency stop button"
rationale: "Customer requirement - emergency stop button required for safety compliance"
impact: high
impact_analysis: |
  Affected components:
  - Software Requirements Specification (add SW-REQ-051)
  - Software Architecture Specification (add Emergency Stop Handler component)
  - Software Design Specification (design emergency stop logic)
  - Emergency Brake Controller (modify to handle emergency stop)
  - All test specifications (add test cases for emergency stop)
  
  Estimated effort: 40 hours
  Safety impact: High (safety-critical function)
  Schedule impact: +2 weeks (full re-verification required)

affected_documents:
  - Software-Requirements-Specification
  - Software-Architecture-Specification
  - Software-Design-Specification
  - Software-Test-Specification

affected_requirements:
  - SW-REQ-017  # Related: emergency brake triggering

affected_code:
  - src/emergency_brake_controller.c
  - src/train_control.c

ccb_status: approved
ccb_decision_date: "2026-03-15T10:00:00Z"
ccb_approver: "Mary Brown (PM)"
ccb_comment: "Approved, requires full re-verification per SIL 3 requirements"

implemented: true
implementation_date: "2026-03-20T16:30:00Z"
new_baseline: "REQ-BASELINE-v1.1.0"

submitted_by: Jane Doe (REQ)
submitted_date: "2026-03-13T14:00:00Z"
priority: high
```

---

### 5.4 Baseline Manifest

**Location**: `.workflow/baselines/{baseline_tag}.yaml`

**Format**:
```yaml
baseline_tag: REQ-BASELINE-v1.0.0
baseline_name: "Requirements Phase Baseline"
phase: requirements

created_date: "2026-03-12T14:00:00Z"
created_by: Tom Green (CM)
description: "Requirements phase complete, all deliverables approved for SIL 3"
sil_level: 3

deliverables:
  - document_id: Software-Requirements-Specification
    document_path: docs/Software-Requirements-Specification.md
    version: "1.0"
    checksum: "sha256:abc123def456..."
    file_size: 45823
    approved_by: [PEER, QUA, VER, VAL, PM]
  
  - document_id: Software-Test-Specification
    document_path: docs/Software-Test-Specification.md
    version: "1.0"
    checksum: "sha256:ghi789jkl012..."
    file_size: 32451
    approved_by: [PEER, QUA, VER, VAL, PM]
  
  - document_id: Software-Verification-Plan
    document_path: docs/Software-Verification-Plan.md
    version: "1.0"
    checksum: "sha256:mno345pqr678..."
    file_size: 18934
    approved_by: [PEER, QUA, VER, VAL, PM]

git_commit: "7f8e9c2d1a3b5f6e4d8c9a7b5e3f1d2c4a6b8e0"
git_tag: REQ-BASELINE-v1.0.0

checksum: "sha256:baseline_manifest_checksum..."
signed: true
signature: "sha256:digital_signature..."
```

---

### 5.5 Directory Structure

```
project_root/
├── .workflow/
│   ├── {document_id}.yaml              # Workflow state for each document
│   ├── history/
│   │   └── {document_id}.log           # Event history (JSON Lines)
│   ├── change-requests/
│   │   ├── CR-001.yaml
│   │   ├── CR-002.yaml
│   │   └── index.yaml                  # CR index
│   ├── baselines/
│   │   ├── REQ-BASELINE-v1.0.0.yaml
│   │   ├── ARCH-BASELINE-v1.0.0.yaml
│   │   └── index.yaml                  # Baseline index
│   └── config.yaml                     # Workflow configuration
```

---

## 6. Integration with Existing Infrastructure

### 6.1 workspace.py Integration

**Implementation Approach**: Add `workflow` subcommand to existing `workspace.py`

**Code Structure**:
```python
# tools/workspace.py (extended)

class WorkspaceManager:
    def __init__(self):
        self.workflow_manager = WorkflowManager()  # New module
    
    def workflow(self, args):
        """Handle workflow subcommand."""
        return self.workflow_manager.execute(args)

# tools/workflow_manager.py (new module)

class WorkflowManager:
    def execute(self, args):
        command = args.command
        if command == 'submit':
            return self.submit_document(args)
        elif command == 'review':
            return self.review_document(args)
        elif command == 'approve':
            return self.approve_document(args)
        # ... other commands
    
    def submit_document(self, args):
        # Implementation
        pass
```

---

### 6.2 LIFECYCLE_STATE.md Integration

**Read Operations**:
- Detect current phase
- Detect SIL level
- Determine required deliverables

**Write Operations**:
- Update deliverable status (Draft → Review → Approved → Baseline)
- Record baseline tags
- Update phase advancement

**Example**:
```python
# Read lifecycle state
lifecycle = parse_lifecycle_state("LIFECYCLE_STATE.md")
current_phase = lifecycle.current_phase
sil_level = lifecycle.sil_level

# Update deliverable status
update_deliverable_status(
    lifecycle_state_path="LIFECYCLE_STATE.md",
    document_id="Software-Requirements-Specification",
    old_status="Review",
    new_status="Approved",
    metadata={"approved_by": ["PEER", "QUA", "VER", "VAL", "PM"]}
)
```

---

### 6.3 Deliverables Metadata Integration

**Use deliverables YAML files to:**
1. Determine required approvals (based on `verification_criteria.reviews`)
2. Validate deliverable completeness (based on `sections_required`)
3. Identify dependencies (based on `depends_on`)
4. Determine evidence requirements (based on `evidence_requirements`)

**Example**:
```python
# Load deliverable metadata
srs_metadata = load_deliverable("deliverables/requirements/Software-Requirements-Specification.yaml")

# Extract review requirements
required_roles = srs_metadata['verification_criteria']['reviews']
# Returns: ['PEER', 'QUA', 'VER', 'VAL', 'PM'] for SIL 3

# Validate workflow state matches metadata
validate_workflow_against_metadata(
    workflow_state=workflow_state,
    metadata=srs_metadata
)
```

---

### 6.4 Git Integration

**Operations**:

1. **Create Baseline Tags**:
```bash
git tag -a REQ-BASELINE-v1.0.0 -m "Requirements phase baseline"
git push origin REQ-BASELINE-v1.0.0
```

2. **Verify Document Checksums**:
```bash
sha256sum docs/Software-Requirements-Specification.md
```

3. **Change Request Branches**:
```bash
# Create branch from baseline for change request
git checkout -b CR-001-emergency-stop REQ-BASELINE-v1.0.0
# Make changes
# Create new baseline after approval
git tag -a REQ-BASELINE-v1.1.0
```

**Python Integration**:
```python
import subprocess

def create_baseline_tag(tag_name: str, message: str):
    """Create Git tag for baseline."""
    subprocess.run(['git', 'tag', '-a', tag_name, '-m', message], check=True)
    subprocess.run(['git', 'push', 'origin', tag_name], check=True)

def get_file_checksum(file_path: str) -> str:
    """Calculate SHA256 checksum."""
    import hashlib
    with open(file_path, 'rb') as f:
        return hashlib.sha256(f.read()).hexdigest()
```

---

## 7. Validation and Verification

### 7.1 Independence Validation (SIL 3-4)

**EN 50128 Requirements**:
- Section 5.1.2.10i: "A person who is Verifier shall neither be Requirements Manager, Designer, Implementer, Integrator, Tester nor Validator"
- Section 5.1.2.10j: "A person who is Validator shall neither be Requirements Manager, Designer, Implementer, Integrator, Tester nor Verifier"

**Algorithm**:
```python
def validate_independence(document_id: str, reviewer_role: str, reviewer_name: str) -> bool:
    """Validate reviewer independence per EN 50128 Section 5.1.2.10."""
    
    workflow = load_workflow_state(document_id)
    
    # Load all roles for this person across all documents
    person_roles = get_all_roles_for_person(reviewer_name)
    
    # Independence rules (EN 50128 5.1.2.10i, 5.1.2.10j)
    conflicting_roles = {
        'VER': ['REQ', 'DES', 'IMP', 'INT', 'TST', 'VAL'],
        'VAL': ['REQ', 'DES', 'IMP', 'INT', 'TST', 'VER'],
    }
    
    if reviewer_role in conflicting_roles:
        conflicts = conflicting_roles[reviewer_role]
        for role in person_roles:
            if role in conflicts:
                raise IndependenceViolation(
                    f"Independence violation: {reviewer_role} cannot be same person as {role} "
                    f"(EN 50128 Section 5.1.2.10)"
                )
    
    return True
```

---

### 7.2 Phase Gate Validation

**Algorithm**:
```python
def validate_phase_gate(phase: str, sil_level: int) -> GateCheckResult:
    """Validate phase gate prerequisites."""
    
    criteria = load_phase_gate_criteria(phase, sil_level)
    result = GateCheckResult(phase=phase, sil_level=sil_level)
    
    # Check 1: All required deliverables exist
    for deliverable_id in criteria.required_deliverables:
        if not deliverable_exists(deliverable_id):
            result.add_error(f"Missing required deliverable: {deliverable_id}")
    
    # Check 2: All deliverables approved
    if criteria.require_all_approved:
        for deliverable_id in criteria.required_deliverables:
            workflow = load_workflow_state(deliverable_id)
            if workflow.status not in [WorkflowStatus.APPROVED, WorkflowStatus.BASELINE]:
                result.add_error(f"Deliverable not approved: {deliverable_id} (status: {workflow.status})")
    
    # Check 3: Quality gates
    if criteria.require_qua_review:
        for deliverable_id in criteria.required_deliverables:
            if not has_approval(deliverable_id, role='QUA'):
                result.add_error(f"Missing QUA approval: {deliverable_id}")
    
    # Check 4: Verification gates
    if criteria.require_ver_approval:
        for deliverable_id in criteria.required_deliverables:
            if not has_approval(deliverable_id, role='VER'):
                result.add_error(f"Missing VER approval: {deliverable_id}")
    
    # Check 5: Traceability gates
    if criteria.require_traceability_complete:
        traceability_result = validate_traceability_for_phase(phase, sil_level)
        if not traceability_result.passed:
            result.add_error(f"Traceability incomplete: {traceability_result.message}")
    
    # Determine pass/fail
    result.passed = len(result.errors) == 0
    return result
```

---

### 7.3 Approval Verification

**Verify Approval Integrity**:
```python
def verify_approval_signature(approval: Approval) -> bool:
    """Verify approval record hasn't been tampered with."""
    
    # Reconstruct approval record (without signature)
    record = {
        'reviewer_role': approval.reviewer_role,
        'reviewer_name': approval.reviewer_name,
        'approved': approval.approved,
        'timestamp': approval.timestamp,
        'comment': approval.comment,
        'document_id': approval.document_id,
        'document_version': approval.document_version,
        'document_checksum': approval.document_checksum,
    }
    
    # Calculate expected signature
    import hashlib
    import json
    expected_signature = hashlib.sha256(
        json.dumps(record, sort_keys=True).encode()
    ).hexdigest()
    
    # Compare with stored signature
    return f"sha256:{expected_signature}" == approval.signature
```

---

## 8. Workflow Automation

### 8.1 Automatic Reviewer Notification

**Trigger**: Document submitted for review

**Action**: Notify next reviewer(s) based on workflow

**Implementation**:
```python
def notify_reviewers(document_id: str, workflow: WorkflowState):
    """Notify pending reviewers."""
    
    # Determine notification method (email, CLI message, etc.)
    for reviewer_role in workflow.pending_reviewers:
        reviewer_person = get_assigned_reviewer(document_id, reviewer_role)
        
        message = f"""
        REVIEW REQUIRED
        
        Document: {workflow.document_title}
        Document ID: {document_id}
        Your Role: {reviewer_role}
        SIL Level: {workflow.sil_level}
        Phase: {workflow.phase}
        
        Review with:
          workspace.py workflow review {document_id} --role {reviewer_role} --approve --comment "..."
        
        Due Date: {calculate_due_date(workflow)}
        """
        
        send_notification(reviewer_person, message)
```

---

### 8.2 Overdue Review Detection

**Trigger**: Daily cron job or on-demand check

**Action**: Identify overdue reviews and escalate

**Implementation**:
```python
def check_overdue_reviews():
    """Check for overdue reviews and escalate."""
    
    overdue_documents = []
    
    for workflow_file in glob('.workflow/*.yaml'):
        workflow = load_workflow_state(workflow_file)
        
        if workflow.status == WorkflowStatus.REVIEW:
            # Calculate days since submission
            days_pending = (datetime.now() - workflow.modified_date).days
            
            review_workflow = REVIEW_WORKFLOWS[workflow.sil_level]
            timeout_days = review_workflow.review_timeout_days
            
            if days_pending > timeout_days:
                overdue_documents.append({
                    'document_id': workflow.document_id,
                    'days_overdue': days_pending - timeout_days,
                    'current_reviewer': workflow.current_reviewer,
                })
    
    # Escalate to PM
    if overdue_documents:
        escalate_overdue_reviews(overdue_documents)
```

---

### 8.3 Automatic Baseline Creation (Optional)

**Trigger**: All deliverables for phase approved

**Action**: Suggest baseline creation to CM

**Implementation**:
```python
def suggest_baseline(phase: str):
    """Suggest baseline creation when phase complete."""
    
    criteria = load_phase_gate_criteria(phase)
    all_approved = True
    
    for deliverable_id in criteria.required_deliverables:
        workflow = load_workflow_state(deliverable_id)
        if workflow.status != WorkflowStatus.APPROVED:
            all_approved = False
            break
    
    if all_approved:
        print(f"""
        ✅ All {phase} deliverables approved!
        
        Suggest creating baseline:
          workspace.py workflow baseline --phase {phase} --tag {phase.upper()}-BASELINE-v1.0.0
        """)
```

---

## 9. Implementation Plan

### Phase 1: Core Infrastructure (Week 1)
1. ✅ Data models (WorkflowState, Approval, Rejection, etc.)
2. ✅ YAML parsers for workflow state files
3. ✅ Workflow state persistence (read/write .workflow/*.yaml)
4. ✅ Integration with workspace.py (add `workflow` subcommand)

### Phase 2: Basic Commands (Week 1-2)
1. ✅ `submit` command - Submit document for review
2. ✅ `review` command - Approve/reject document
3. ✅ `approve` command - Mark document as approved
4. ✅ `status` command - Show workflow status
5. ✅ `history` command - Show workflow history

### Phase 3: Review Workflow (Week 2)
1. ✅ SIL-dependent workflow routing
2. ✅ Sequential review enforcement
3. ✅ Independence validation (SIL 3-4)
4. ✅ Reviewer assignment (`assign-reviewer` command)

### Phase 4: Baseline Management (Week 2-3)
1. ✅ `baseline` command - Create Git baseline
2. ✅ Baseline manifest generation
3. ✅ Git tag creation and verification
4. ✅ Checksum calculation for baseline integrity

### Phase 5: Change Control (Week 3)
1. ✅ `change-request` command - Create/manage CRs
2. ✅ CCB workflow
3. ✅ Change traceability (baseline → CR → new baseline)
4. ✅ Impact analysis tracking

### Phase 6: Phase Gates (Week 3-4)
1. ✅ `gate-check` command - Validate phase gates
2. ✅ `advance-phase` command - Advance to next phase
3. ✅ Phase gate criteria definitions (SIL-dependent)
4. ✅ Integration with traceability validation

### Phase 7: Automation and Reporting (Week 4)
1. ⏳ Automatic reviewer notification
2. ⏳ Overdue review detection
3. ⏳ Workflow metrics and dashboards
4. ⏳ Integration with deliverables metadata

### Phase 8: Testing and Documentation (Week 4-5)
1. ⏳ Unit tests for all commands
2. ⏳ Integration tests with example projects
3. ⏳ User documentation and examples
4. ⏳ Agent/skill integration guide

---

## 10. Testing Strategy

### 10.1 Unit Tests
- Test workflow state persistence (read/write YAML)
- Test approval/rejection logic
- Test independence validation
- Test phase gate validation
- Test SIL-dependent workflow routing

### 10.2 Integration Tests
- Test complete review workflow (Draft → Review → Approved → Baseline)
- Test rejection and rework workflow
- Test change request workflow (Baseline → CR → new Baseline)
- Test phase advancement with gate checks
- Test with SIL 0, 2, 3, 4 scenarios

### 10.3 Acceptance Tests
- Use case scenarios (UC-1 through UC-9)
- Test with example EN 50128 projects
- Verify EN 50128 compliance (independence, reviews, baselines)

---

## 11. Success Criteria

1. ✅ **Functional Completeness**: All 10 CLI commands implemented and working
2. ✅ **EN 50128 Compliance**: SIL-dependent workflows, independence validation
3. ✅ **Data Integrity**: Workflow state persisted correctly, approval signatures verified
4. ✅ **Integration**: Works with workspace.py, LIFECYCLE_STATE.md, deliverables metadata
5. ✅ **Usability**: Clear CLI interface, helpful error messages, workflow guidance
6. ✅ **Traceability**: Full audit trail of approvals, rejections, changes
7. ✅ **Baseline Control**: Immutable baselines with Git tags, change control workflow

---

## 12. Future Enhancements

### Version 2.0
- Web UI for workflow management dashboard
- Email/Slack notifications for review assignments
- Automatic baseline creation when all deliverables approved
- Integration with JIRA/issue trackers for change requests
- Digital signatures for approvals (PKI integration)

### Version 3.0
- Workflow analytics and metrics dashboard
- Predictive modeling (estimate review time based on document size)
- AI-assisted review assignment (suggest best reviewers)
- Integration with CI/CD (automatic quality checks before approval)
- Multi-project workflow coordination

---

## 13. References

- **EN 50128:2011** - Railway applications - Software for railway control and protection systems
  - Section 5.1.2.10 - Role definitions and independence requirements
  - Section 6.4 - Configuration Management
  - Annex C - Document control requirements
- **EN 50126:2017** - RAMS standard (change control processes)
- **ISO/IEC 15288** - Systems and software engineering lifecycle processes
- **DO-178C** - Software lifecycle processes (aviation standard, similar workflows)

---

**END OF DESIGN DOCUMENT**
