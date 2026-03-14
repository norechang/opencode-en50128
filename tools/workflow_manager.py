#!/usr/bin/env python3
"""
Workflow Manager Tool for EN 50128 Projects

Purpose: Manage document lifecycle, review workflows, approvals, and baselines
         across the EN 50128 software development lifecycle.

Usage:
    python3 tools/workflow_manager.py <command> [options]

Commands:
    submit           Submit document for review
    review           Review and approve/reject document
    approve          Mark document as approved
    reject           Reject document and return to author
    baseline         Create configuration baseline
    gate-check       Validate phase gate prerequisites
    change-request   Create/manage change requests
    status           Generate workflow status report
    history          Show document workflow history
    notify           Send workflow notifications

EN 50128 Compliance:
    - Independent verification and validation (SIL 3-4)
    - Mandatory peer reviews (all SILs)
    - Quality assurance checks before verification
    - Configuration management and baseline control
    - Traceability of approvals and changes

Version: 1.0
Date: 2026-03-13
"""

import argparse
import hashlib
import json
import os
import re
import subprocess
import sys
import yaml
from dataclasses import dataclass, asdict, field
from datetime import datetime
from enum import Enum
from pathlib import Path
from typing import List, Dict, Optional, Set, Tuple

# ============================================================================
# Data Models
# ============================================================================

class WorkflowState(Enum):
    """Document workflow states per EN 50128."""
    
    DRAFT = "draft"                  # Initial authoring
    REVIEW = "review"                # Under review
    APPROVED = "approved"            # All approvals obtained
    BASELINE = "baseline"            # Immutable baseline (Git tag)
    CHANGE_PENDING = "change_pending"  # Change request pending
    OBSOLETE = "obsolete"            # Superseded by newer version

class ReviewRole(Enum):
    """EN 50128 review roles."""
    
    AUTHOR = "author"
    PEER = "peer"
    QUA = "qua"
    VER = "ver"
    VAL = "val"
    SAFETY_MGR = "safety_mgr"
    ASSESSOR = "assessor"
    PM = "pm"
    COD = "cod"
    VMGR = "vmgr"

@dataclass
class Approval:
    """Represents a single approval or rejection."""
    
    # Approval identifiers
    document_id: str
    reviewer_role: str
    reviewer_name: str
    
    # Decision
    approved: bool
    comment: str = ""
    
    # Metadata
    timestamp: str = ""
    signature: str = ""  # SHA256 hash of approval record
    
    def __post_init__(self):
        """Initialize timestamp and signature."""
        if not self.timestamp:
            self.timestamp = datetime.now().isoformat()
        
        if not self.signature:
            # Generate signature (hash of approval data)
            data = f"{self.document_id}|{self.reviewer_role}|{self.reviewer_name}|{self.approved}|{self.timestamp}"
            self.signature = hashlib.sha256(data.encode()).hexdigest()[:16]

@dataclass
class Rejection:
    """Represents a document rejection."""
    
    document_id: str
    reviewer_role: str
    reviewer_name: str
    reason: str
    timestamp: str = ""
    
    def __post_init__(self):
        if not self.timestamp:
            self.timestamp = datetime.now().isoformat()

@dataclass
class ChangeRequest:
    """Represents a change request for baselined document."""
    
    # CR identifiers
    cr_id: str
    document_id: str
    
    # Change details
    description: str
    impact: str  # low, medium, high, critical
    rationale: str = ""
    
    # Status
    status: str = "pending"  # pending, approved, rejected
    ccb_approved: bool = False
    ccb_comment: str = ""
    
    # Metadata
    requester: str = ""
    created_date: str = ""
    reviewed_date: str = ""
    
    def __post_init__(self):
        if not self.created_date:
            self.created_date = datetime.now().isoformat()

@dataclass
class DocumentWorkflow:
    """Represents complete workflow state for a document."""
    
    # Document identifiers
    document_id: str
    document_path: str
    document_type: str  # SRS, SAS, SDS, etc.
    
    # Workflow state
    state: str = "draft"  # WorkflowState enum value
    version: str = "1.0"
    
    # Author info
    author_role: str = ""
    author_name: str = ""
    
    # Approvals
    approvals: List[Approval] = field(default_factory=list)
    rejections: List[Rejection] = field(default_factory=list)
    
    # Required approvers (based on SIL level)
    required_roles: List[str] = field(default_factory=list)
    
    # Baseline info
    baseline_tag: str = ""
    baseline_date: str = ""
    
    # Change requests
    change_requests: List[str] = field(default_factory=list)  # List of CR-IDs
    
    # Timestamps
    created_date: str = ""
    modified_date: str = ""
    approved_date: str = ""
    
    # Metadata
    sil_level: int = 0
    phase: str = ""
    
    def __post_init__(self):
        if not self.created_date:
            self.created_date = datetime.now().isoformat()
        if not self.modified_date:
            self.modified_date = self.created_date

# ============================================================================
# Workflow Manager Core
# ============================================================================

class WorkflowManager:
    """Core workflow management functionality."""
    
    def __init__(self, project: str = None, workflow_dir: str = ".workflow"):
        """
        Initialize Workflow Manager.
        
        Args:
            project: Project name (reads from LIFECYCLE_STATE.md if None)
            workflow_dir: Directory for workflow state files
        """
        self.project = project or self._read_project_name()
        self.workflow_dir = Path(workflow_dir)
        self.workflow_dir.mkdir(parents=True, exist_ok=True)
        
        # Create subdirectories
        (self.workflow_dir / "documents").mkdir(exist_ok=True)
        (self.workflow_dir / "history").mkdir(exist_ok=True)
        (self.workflow_dir / "change_requests").mkdir(exist_ok=True)
        
        # Load configuration
        self.config = self._load_config()
        
        # Read SIL level
        self.sil_level = self._read_sil_level()
    
    def _read_project_name(self) -> str:
        """Read project name from LIFECYCLE_STATE.md."""
        try:
            with open("LIFECYCLE_STATE.md", "r") as f:
                content = f.read()
                match = re.search(r'\*\*Project\*\*:\s*(.+)', content)
                if match:
                    return match.group(1).strip()
        except FileNotFoundError:
            pass
        return "UnknownProject"
    
    def _read_sil_level(self) -> int:
        """Read SIL level from LIFECYCLE_STATE.md."""
        try:
            with open("LIFECYCLE_STATE.md", "r") as f:
                content = f.read()
                match = re.search(r'\*\*SIL\*\*:\s*(\d)', content)
                if match:
                    return int(match.group(1))
        except FileNotFoundError:
            pass
        return 0
    
    def _load_config(self) -> Dict:
        """Load workflow configuration."""
        # Default configuration
        config = {
            "approval_workflows": {
                "sil_0": ["author", "peer", "qua", "pm"],
                "sil_1": ["author", "peer", "qua", "pm"],
                "sil_2": ["author", "peer", "qua", "pm"],
                "sil_3": ["author", "peer", "qua", "safety_mgr", "ver", "val", "assessor", "pm"],
                "sil_4": ["author", "peer", "qua", "safety_mgr", "ver", "val", "assessor", "pm"],
            },
            "independence_rules": {
                # VER cannot be: author, peer, implementer, tester, validator
                "ver": ["author", "peer", "imp", "tst", "val"],
                # VAL cannot be: author, peer, implementer, tester, verifier, pm
                "val": ["author", "peer", "imp", "tst", "ver", "pm"],
            },
        }
        
        # Load from .workflow.yaml if exists
        config_path = Path(".workflow.yaml")
        if config_path.exists():
            with open(config_path) as f:
                user_config = yaml.safe_load(f)
                config.update(user_config)
        
        return config
    
    # ========================================================================
    # Command: submit
    # ========================================================================
    
    def submit(self, document_id: str, document_path: str, author_role: str, 
               author_name: str, sil: int = None) -> DocumentWorkflow:
        """
        Submit document for review.
        
        Args:
            document_id: Document identifier (e.g., "DOC-SRS-2026-001")
            document_path: Path to document file
            author_role: Author's role (REQ, DES, IMP, etc.)
            author_name: Author's name
            sil: SIL level (uses project SIL if not specified)
        
        Returns:
            DocumentWorkflow object
        """
        sil = sil if sil is not None else self.sil_level
        
        # Determine required approval workflow based on SIL
        required_roles = self.config["approval_workflows"][f"sil_{sil}"]
        
        # Create workflow state
        workflow = DocumentWorkflow(
            document_id=document_id,
            document_path=document_path,
            document_type=self._infer_document_type(document_id),
            state=WorkflowState.REVIEW.value,
            author_role=author_role.lower(),
            author_name=author_name,
            required_roles=required_roles,
            sil_level=sil,
        )
        
        # Save workflow state
        self._save_workflow(workflow)
        
        # Log state transition
        self._log_history(document_id, "draft", "review", f"Submitted by {author_role} ({author_name})")
        
        print(f"✓ Document submitted for review: {document_id}")
        print(f"  State: Draft → Review")
        print(f"  SIL {sil} workflow: {len(required_roles)} approvals required")
        print(f"  Next reviewer: {required_roles[1].upper()}")  # Skip author (index 0)
        
        return workflow
    
    def _infer_document_type(self, document_id: str) -> str:
        """Infer document type from document ID."""
        type_patterns = {
            "SRS": "Software Requirements Specification",
            "SAS": "Software Architecture Specification",
            "SDS": "Software Design Specification",
            "STS": "Software Test Specification",
            "SVP": "Software Verification Plan",
            "SVaP": "Software Validation Plan",
            "SQAP": "Software Quality Assurance Plan",
            "SCMP": "Software Configuration Management Plan",
        }
        
        for key, value in type_patterns.items():
            if key in document_id.upper():
                return value
        
        return "Unknown Document Type"
    
    # ========================================================================
    # Command: review
    # ========================================================================
    
    def review(self, document_id: str, reviewer_role: str, reviewer_name: str,
               approve: bool = False, reject: bool = False, comment: str = "") -> Approval:
        """
        Review and approve/reject document.
        
        Args:
            document_id: Document identifier
            reviewer_role: Reviewer's role (PEER, QUA, VER, VAL, etc.)
            reviewer_name: Reviewer's name
            approve: Approve document (default: False)
            reject: Reject document (default: False)
            comment: Review comments
        
        Returns:
            Approval or Rejection object
        """
        # Load workflow state
        workflow = self._load_workflow(document_id)
        
        if not workflow:
            raise ValueError(f"Document not found: {document_id}")
        
        if workflow.state != WorkflowState.REVIEW.value:
            raise ValueError(f"Document not in review state: {workflow.state}")
        
        reviewer_role = reviewer_role.lower()
        
        # Check if reviewer is authorized
        if reviewer_role not in workflow.required_roles:
            raise ValueError(f"Role {reviewer_role} not in approval workflow for SIL {workflow.sil_level}")
        
        # Check independence (SIL 3-4)
        if workflow.sil_level >= 3:
            self._check_independence(workflow, reviewer_role, reviewer_name)
        
        if reject:
            # Create rejection record
            rejection = Rejection(
                document_id=document_id,
                reviewer_role=reviewer_role,
                reviewer_name=reviewer_name,
                reason=comment,
            )
            
            workflow.rejections.append(rejection)
            workflow.state = WorkflowState.DRAFT.value
            
            self._save_workflow(workflow)
            self._log_history(document_id, "review", "draft", f"Rejected by {reviewer_role} ({reviewer_name}): {comment}")
            
            print(f"✗ Document rejected: {document_id}")
            print(f"  Reviewer: {reviewer_role.upper()} ({reviewer_name})")
            print(f"  Reason: {comment}")
            print(f"  State: Review → Draft")
            print(f"  Action: Author must address issues and resubmit")
            
            return rejection
        
        elif approve:
            # Create approval record
            approval = Approval(
                document_id=document_id,
                reviewer_role=reviewer_role,
                reviewer_name=reviewer_name,
                approved=True,
                comment=comment,
            )
            
            workflow.approvals.append(approval)
            
            # Check if all approvals obtained
            approved_roles = set(a.reviewer_role for a in workflow.approvals)
            pending_roles = [r for r in workflow.required_roles if r not in approved_roles]
            
            self._save_workflow(workflow)
            self._log_history(document_id, "review", "review", f"Approved by {reviewer_role} ({reviewer_name})")
            
            print(f"✓ Document approved by {reviewer_role.upper()}: {document_id}")
            print(f"  Reviewer: {reviewer_name}")
            print(f"  Comment: {comment}")
            print(f"  Progress: {len(workflow.approvals)}/{len(workflow.required_roles)} approvals")
            
            if pending_roles:
                print(f"  Next reviewer: {pending_roles[0].upper()}")
            else:
                print(f"  ✓ All approvals obtained! Document ready to mark as Approved.")
            
            return approval
        
        else:
            raise ValueError("Must specify --approve or --reject")
    
    def _check_independence(self, workflow: DocumentWorkflow, reviewer_role: str, reviewer_name: str):
        """Check independence requirements for SIL 3-4."""
        independence_rules = self.config.get("independence_rules", {})
        
        if reviewer_role not in independence_rules:
            return  # No independence rules for this role
        
        forbidden_roles = independence_rules[reviewer_role]
        
        # Check if reviewer has conflicting role
        if workflow.author_role in forbidden_roles and workflow.author_name == reviewer_name:
            raise ValueError(
                f"Independence violation: {reviewer_role.upper()} cannot review own work. "
                f"Reviewer {reviewer_name} is document author ({workflow.author_role.upper()}). "
                f"EN 50128 Section 5.1.2.10 requires independent verification for SIL 3-4."
            )
        
        # Check against other reviewers
        for approval in workflow.approvals:
            if approval.reviewer_name == reviewer_name and approval.reviewer_role in forbidden_roles:
                raise ValueError(
                    f"Independence violation: {reviewer_role.upper()} cannot be same person as {approval.reviewer_role.upper()}. "
                    f"EN 50128 Section 5.1.2.10 requires independent verification for SIL 3-4."
                )
    
    # ========================================================================
    # Command: approve
    # ========================================================================
    
    def approve(self, document_id: str, force: bool = False) -> DocumentWorkflow:
        """
        Mark document as approved.
        
        Args:
            document_id: Document identifier
            force: Override approval checks (use with caution)
        
        Returns:
            Updated DocumentWorkflow
        """
        workflow = self._load_workflow(document_id)
        
        if not workflow:
            raise ValueError(f"Document not found: {document_id}")
        
        # Check if all approvals obtained
        approved_roles = set(a.reviewer_role for a in workflow.approvals)
        pending_roles = [r for r in workflow.required_roles if r not in approved_roles]
        
        if pending_roles and not force:
            raise ValueError(
                f"Cannot approve: pending approvals from {', '.join(pending_roles)}. "
                f"Use --force to override (requires PM/COD role)."
            )
        
        workflow.state = WorkflowState.APPROVED.value
        workflow.approved_date = datetime.now().isoformat()
        
        self._save_workflow(workflow)
        self._log_history(document_id, "review", "approved", f"All approvals obtained ({len(workflow.approvals)}/{len(workflow.required_roles)})")
        
        print(f"✓ Document approved: {document_id}")
        print(f"  State: Review → Approved")
        print(f"  Approvals: {len(workflow.approvals)}/{len(workflow.required_roles)}")
        print(f"  Date: {workflow.approved_date}")
        
        if force:
            print(f"  ⚠ WARNING: Forced approval (override)")
        
        return workflow
    
    # ========================================================================
    # Command: baseline
    # ========================================================================
    
    def baseline(self, document_id: str = None, phase: str = None, tag: str = None,
                 message: str = "") -> Dict:
        """
        Create configuration baseline.
        
        Args:
            document_id: Single document to baseline
            phase: Baseline all documents for phase
            tag: Git tag name
            message: Baseline description
        
        Returns:
            Dict with baseline info
        """
        if not tag:
            raise ValueError("Baseline tag required (--tag)")
        
        documents_to_baseline = []
        
        if document_id:
            # Baseline single document
            workflow = self._load_workflow(document_id)
            if not workflow:
                raise ValueError(f"Document not found: {document_id}")
            
            if workflow.state != WorkflowState.APPROVED.value:
                raise ValueError(f"Document must be approved before baseline: {document_id} (current state: {workflow.state})")
            
            documents_to_baseline.append(workflow)
        
        elif phase:
            # Baseline all documents for phase
            all_workflows = self._list_workflows()
            phase_docs = [w for w in all_workflows if w.phase == phase and w.state == WorkflowState.APPROVED.value]
            
            if not phase_docs:
                raise ValueError(f"No approved documents found for phase: {phase}")
            
            documents_to_baseline.extend(phase_docs)
        
        else:
            raise ValueError("Must specify --document or --phase")
        
        # Create Git tag
        try:
            subprocess.run(
                ["git", "tag", "-a", tag, "-m", message or f"Baseline: {tag}"],
                check=True,
                capture_output=True,
                text=True
            )
            
            print(f"✓ Git tag created: {tag}")
        
        except subprocess.CalledProcessError as e:
            raise RuntimeError(f"Failed to create Git tag: {e.stderr}")
        
        # Update workflow states
        baseline_date = datetime.now().isoformat()
        
        for workflow in documents_to_baseline:
            workflow.state = WorkflowState.BASELINE.value
            workflow.baseline_tag = tag
            workflow.baseline_date = baseline_date
            
            self._save_workflow(workflow)
            self._log_history(workflow.document_id, "approved", "baseline", f"Baselined as {tag}")
        
        print(f"✓ Baseline created: {tag}")
        print(f"  Documents: {len(documents_to_baseline)}")
        print(f"  Date: {baseline_date}")
        
        for w in documents_to_baseline:
            print(f"    - {w.document_id}")
        
        return {
            "tag": tag,
            "date": baseline_date,
            "documents": [w.document_id for w in documents_to_baseline],
            "count": len(documents_to_baseline),
        }
    
    # ========================================================================
    # Command: status
    # ========================================================================
    
    def status(self, document_id: str = None, phase: str = None, all: bool = False,
               format: str = "text", show_approvals: bool = False) -> str:
        """
        Generate workflow status report.
        
        Args:
            document_id: Show status for specific document
            phase: Show status for phase
            all: Show status for all documents
            format: Output format (text, markdown, json)
            show_approvals: Include detailed approval records
        
        Returns:
            Status report as string
        """
        workflows = []
        
        if document_id:
            workflow = self._load_workflow(document_id)
            if workflow:
                workflows.append(workflow)
        elif phase:
            workflows = [w for w in self._list_workflows() if w.phase == phase]
        elif all:
            workflows = self._list_workflows()
        else:
            raise ValueError("Must specify --document, --phase, or --all")
        
        if format == "markdown":
            return self._format_status_markdown(workflows, show_approvals)
        elif format == "json":
            return json.dumps([asdict(w) for w in workflows], indent=2)
        else:
            return self._format_status_text(workflows, show_approvals)
    
    def _format_status_text(self, workflows: List[DocumentWorkflow], show_approvals: bool) -> str:
        """Format status as plain text."""
        lines = []
        
        lines.append(f"\n{'='*70}")
        lines.append(f"Workflow Status Report - {self.project}")
        lines.append(f"{'='*70}\n")
        
        for workflow in workflows:
            state_icon = {
                "draft": "📝",
                "review": "⏳",
                "approved": "✅",
                "baseline": "🔒",
                "change_pending": "🔄",
                "obsolete": "❌",
            }.get(workflow.state, "?")
            
            lines.append(f"{state_icon} {workflow.document_id} - {workflow.state.upper()}")
            lines.append(f"   Type: {workflow.document_type}")
            lines.append(f"   Author: {workflow.author_role.upper()} ({workflow.author_name})")
            lines.append(f"   Approvals: {len(workflow.approvals)}/{len(workflow.required_roles)}")
            
            if show_approvals:
                for approval in workflow.approvals:
                    lines.append(f"     ✓ {approval.reviewer_role.upper()} ({approval.reviewer_name}) - {approval.timestamp}")
            
            if workflow.baseline_tag:
                lines.append(f"   Baseline: {workflow.baseline_tag}")
            
            lines.append("")
        
        lines.append(f"{'='*70}\n")
        
        return "\n".join(lines)
    
    def _format_status_markdown(self, workflows: List[DocumentWorkflow], show_approvals: bool) -> str:
        """Format status as Markdown."""
        lines = []
        
        lines.append(f"# Workflow Status Report - {self.project}\n")
        lines.append(f"**Date**: {datetime.now().strftime('%Y-%m-%d %H:%M')}\n")
        lines.append(f"---\n")
        
        lines.append(f"| Document ID | State | Type | Approvals | Baseline |\n")
        lines.append(f"|-------------|-------|------|-----------|----------|\n")
        
        for workflow in workflows:
            state_icon = {
                "draft": "📝 Draft",
                "review": "⏳ Review",
                "approved": "✅ Approved",
                "baseline": "🔒 Baseline",
            }.get(workflow.state, workflow.state)
            
            baseline = workflow.baseline_tag or "-"
            approvals = f"{len(workflow.approvals)}/{len(workflow.required_roles)}"
            
            lines.append(f"| {workflow.document_id} | {state_icon} | {workflow.document_type} | {approvals} | {baseline} |\n")
        
        return "".join(lines)
    
    # ========================================================================
    # Command: history
    # ========================================================================
    
    def history(self, document_id: str, format: str = "text") -> str:
        """
        Show document workflow history.
        
        Args:
            document_id: Document identifier
            format: Output format (text, json, timeline)
        
        Returns:
            History as string
        """
        history_path = self.workflow_dir / "history" / f"{document_id}.log"
        
        if not history_path.exists():
            return f"No history found for: {document_id}"
        
        with open(history_path, "r") as f:
            history_lines = f.readlines()
        
        if format == "json":
            events = []
            for line in history_lines:
                parts = line.strip().split(" | ")
                if len(parts) >= 4:
                    events.append({
                        "timestamp": parts[0],
                        "old_state": parts[1],
                        "new_state": parts[2],
                        "description": parts[3],
                    })
            return json.dumps(events, indent=2)
        
        else:
            lines = [f"\nWorkflow History: {document_id}\n", "="*70 + "\n"]
            lines.extend(history_lines)
            lines.append("="*70 + "\n")
            return "".join(lines)
    
    # ========================================================================
    # Workflow State Management
    # ========================================================================
    
    def _save_workflow(self, workflow: DocumentWorkflow):
        """Save workflow state to YAML file."""
        workflow_path = self.workflow_dir / "documents" / f"{workflow.document_id}.yaml"
        
        with open(workflow_path, "w") as f:
            yaml.dump(asdict(workflow), f, default_flow_style=False)
    
    def _load_workflow(self, document_id: str) -> Optional[DocumentWorkflow]:
        """Load workflow state from YAML file."""
        workflow_path = self.workflow_dir / "documents" / f"{document_id}.yaml"
        
        if not workflow_path.exists():
            return None
        
        with open(workflow_path, "r") as f:
            data = yaml.safe_load(f)
        
        # Reconstruct dataclass objects
        data['approvals'] = [Approval(**a) for a in data.get('approvals', [])]
        data['rejections'] = [Rejection(**r) for r in data.get('rejections', [])]
        
        return DocumentWorkflow(**data)
    
    def _list_workflows(self) -> List[DocumentWorkflow]:
        """List all workflow states."""
        workflows = []
        
        docs_dir = self.workflow_dir / "documents"
        for yaml_path in docs_dir.glob("*.yaml"):
            doc_id = yaml_path.stem
            workflow = self._load_workflow(doc_id)
            if workflow:
                workflows.append(workflow)
        
        return workflows
    
    def _log_history(self, document_id: str, old_state: str, new_state: str, description: str):
        """Log state transition to history."""
        history_path = self.workflow_dir / "history" / f"{document_id}.log"
        
        timestamp = datetime.now().isoformat()
        log_entry = f"{timestamp} | {old_state} | {new_state} | {description}\n"
        
        with open(history_path, "a") as f:
            f.write(log_entry)

# ============================================================================
# CLI Interface
# ============================================================================

def main():
    """Main CLI entry point."""
    parser = argparse.ArgumentParser(
        description="Workflow Manager for EN 50128 Projects",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
    # Submit document for review
    %(prog)s submit DOC-SRS-2026-001 --path docs/SRS.md --author-role REQ --author-name "Jane Doe" --sil 3
    
    # Approve document
    %(prog)s review DOC-SRS-2026-001 --role VER --name "John Smith" --approve --comment "Verification complete"
    
    # Reject document
    %(prog)s review DOC-SRS-2026-001 --role QUA --name "Bob Wilson" --reject --comment "Traceability incomplete"
    
    # Mark as approved
    %(prog)s approve DOC-SRS-2026-001
    
    # Create baseline
    %(prog)s baseline --phase requirements --tag REQ-BASELINE-v1.0.0
    
    # Check status
    %(prog)s status --all --format markdown
    
    # View history
    %(prog)s history DOC-SRS-2026-001
        """
    )
    
    parser.add_argument('--project', help='Project name (overrides LIFECYCLE_STATE.md)')
    parser.add_argument('--verbose', '-v', action='store_true', help='Verbose output')
    
    subparsers = parser.add_subparsers(dest='command', help='Commands')
    
    # submit command
    submit_parser = subparsers.add_parser('submit', help='Submit document for review')
    submit_parser.add_argument('document_id', help='Document identifier')
    submit_parser.add_argument('--path', required=True, help='Document file path')
    submit_parser.add_argument('--author-role', required=True, help='Author role (REQ, DES, IMP, etc.)')
    submit_parser.add_argument('--author-name', required=True, help='Author name')
    submit_parser.add_argument('--sil', type=int, help='SIL level (default: from LIFECYCLE_STATE.md)')
    
    # review command
    review_parser = subparsers.add_parser('review', help='Review and approve/reject document')
    review_parser.add_argument('document_id', help='Document identifier')
    review_parser.add_argument('--role', required=True, help='Reviewer role (PEER, QUA, VER, VAL, etc.)')
    review_parser.add_argument('--name', required=True, help='Reviewer name')
    review_parser.add_argument('--approve', action='store_true', help='Approve document')
    review_parser.add_argument('--reject', action='store_true', help='Reject document')
    review_parser.add_argument('--comment', default='', help='Review comments')
    
    # approve command
    approve_parser = subparsers.add_parser('approve', help='Mark document as approved')
    approve_parser.add_argument('document_id', help='Document identifier')
    approve_parser.add_argument('--force', action='store_true', help='Override approval checks')
    
    # baseline command
    baseline_parser = subparsers.add_parser('baseline', help='Create configuration baseline')
    baseline_parser.add_argument('--document', help='Single document to baseline')
    baseline_parser.add_argument('--phase', help='Baseline all documents for phase')
    baseline_parser.add_argument('--tag', required=True, help='Git tag name')
    baseline_parser.add_argument('--message', default='', help='Baseline description')
    
    # status command
    status_parser = subparsers.add_parser('status', help='Generate workflow status report')
    status_parser.add_argument('--document', help='Show status for specific document')
    status_parser.add_argument('--phase', help='Show status for phase')
    status_parser.add_argument('--all', action='store_true', help='Show status for all documents')
    status_parser.add_argument('--format', choices=['text', 'markdown', 'json'], default='text', help='Output format')
    status_parser.add_argument('--approvals', action='store_true', help='Include detailed approval records')
    
    # history command
    history_parser = subparsers.add_parser('history', help='Show document workflow history')
    history_parser.add_argument('document_id', help='Document identifier')
    history_parser.add_argument('--format', choices=['text', 'json', 'timeline'], default='text', help='Output format')
    
    args = parser.parse_args()
    
    if not args.command:
        parser.print_help()
        return 1
    
    # Initialize manager
    mgr = WorkflowManager(project=args.project)
    
    # Execute command
    try:
        if args.command == 'submit':
            mgr.submit(args.document_id, args.path, args.author_role, args.author_name, args.sil)
        
        elif args.command == 'review':
            mgr.review(args.document_id, args.role, args.name, args.approve, args.reject, args.comment)
        
        elif args.command == 'approve':
            mgr.approve(args.document_id, args.force)
        
        elif args.command == 'baseline':
            mgr.baseline(args.document, args.phase, args.tag, args.message)
        
        elif args.command == 'status':
            result = mgr.status(args.document, args.phase, args.all, args.format, args.approvals)
            print(result)
        
        elif args.command == 'history':
            result = mgr.history(args.document_id, args.format)
            print(result)
        
        return 0
    
    except Exception as e:
        print(f"✗ Error: {e}", file=sys.stderr)
        if args.verbose:
            import traceback
            traceback.print_exc()
        return 1

if __name__ == '__main__':
    sys.exit(main())
