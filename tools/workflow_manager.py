#!/usr/bin/env python3
"""
Workflow Manager Tool for EN 50128 Projects

Purpose: Manage document lifecycle, review workflows, approvals, and baselines
         across the EN 50128 software development lifecycle.

Usage:
    python3 tools/workflow_manager.py <command> [options]

Commands:
    submit           Submit document for review
    review           Review and approve/reject document (use --approve or --reject)
    approve          Finalize document as approved (after all review approvals obtained)
    baseline         Create configuration baseline
    gate-check       Validate phase gate prerequisites
    status           Generate workflow status report
    history          Show document workflow history

EN 50128 Compliance:
    - Independent verification and validation (SIL 3-4)
    - Mandatory peer reviews (all SILs)
    - Quality assurance checks before verification
    - Configuration management and baseline control
    - Traceability of approvals and changes

Version: 1.1
Date: 2026-03-15
"""

import argparse
import hashlib
import json
import os
import re
import subprocess
import sys
try:
    import yaml
except ImportError:
    print(
        "Error: pyyaml is required. Install it with: pip install pyyaml",
        file=sys.stderr,
    )
    sys.exit(1)
from dataclasses import dataclass, asdict, field
from datetime import datetime
from enum import Enum
from pathlib import Path
from typing import List, Dict, Optional, Set, Tuple

# ============================================================================
# Phase Approval Chains — EN 50128 deterministic gate enforcement
# ============================================================================
#
# Encodes the corrected SIL-conditional, phase-specific approval chains derived
# from the gap analysis of agent interaction flows against EN 50128:2011.
#
# Structure per entry:
#   "chain": ordered list of role steps that MUST appear in the document
#            approval records (roles are lowercase, matching ReviewRole.value).
#            The list is ordered; each role must approve AFTER the previous one.
#   "independence_forbidden": for SIL 3-4 only — pairs of roles that MUST NOT
#            be performed by the same person within a phase gate.
#   "blocked_from_chain": roles that are explicitly forbidden from the approval
#            chain for a given (phase, sil_group) combination.
#   "notes": human-readable rationale (EN 50128 reference).
#
# SIL grouping:
#   sil_low  = SIL 0-2  (PM-led flat chain; independence not mandatory)
#   sil_high = SIL 3-4  (independence mandatory; COD/VMGR/VAL coordination)
#
# Phase numbering follows LIFECYCLE.md:
#   1 = Planning          (SQAP, SCMP, SVP, SVaP)
#   2 = Requirements      (SRS, Hazard Log)
#   3 = Architecture &    (SAS, SDS, SIS, FMEA)
#         Design
#   4 = Implementation    (Source code, Unit Tests)
#         & Unit Testing
#   5 = Integration       (Integration Tests)
#   6 = Validation        (System Tests, Validation Report)
#   7 = Assessment        (SIL 3-4 only: Assessment-Ready gate)
#   8 = Deployment        (Release Package)
#
# NOTE: Phase 7 in the prior gap analysis mapped to "Validation/System Testing"
# and Phase 8 to "Assessment-Ready delivery".  The mapping here follows
# LIFECYCLE.md numbering exactly; Phase 7 = Assessment-Ready, Phase 8 =
# Deployment.

PHASE_APPROVAL_CHAINS: Dict = {

    # ------------------------------------------------------------------
    # Phase 1: Planning  (SQAP, SCMP — PM-authored; SVP, SVaP — VMGR/VER)
    # ------------------------------------------------------------------
    1: {
        "sil_low": {
            # SIL 0-2: PM orchestrates all planning documents
            "chain": ["author", "qua", "pm"],
            "blocked_from_chain": [],
            "independence_forbidden": [],
            "notes": (
                "SIL 0-2: PM-led flat approval chain for all planning documents. "
                "EN 50128 Section 5.3: lifecycle planning mandatory for all SILs."
            ),
        },
        "sil_high": {
            # SIL 3-4: SQAP and SCMP follow normal QUA→PM chain.
            # SVP: COD instructs VMGR; VMGR directs VER to author SVP;
            #      VER submits → QUA (template check) → VMGR (approve).
            # SVaP: VMGR authors → QUA (template check) → VMGR self-approves
            #       (as plan author) → COD (gate).
            # PM has NO authority over SVP or SVaP at SIL 3-4.
            "chain": ["author", "qua", "vmgr", "cod"],
            "blocked_from_chain": ["pm"],   # PM blocked from SVP/SVaP chain
            "independence_forbidden": [
                # VER must not be the same person as the document author
                # for any planning doc they verify (EN 50128 §5.1.2.10i)
                ("ver", "author"),
                # VAL must not report to PM (EN 50128 §5.1.2.10f)
                ("val", "pm"),
            ],
            "notes": (
                "SIL 3-4: COD initiates; VMGR manages VER for SVP authoring; "
                "PM is BLOCKED from SVP/SVaP chain. "
                "EN 50128 §5.1.2.10e (VER reports to VMGR), "
                "§5.1.2.10f (VAL independent of PM)."
            ),
        },
    },

    # ------------------------------------------------------------------
    # Phase 2: Requirements  (SRS, Hazard Log)
    # ------------------------------------------------------------------
    2: {
        "sil_low": {
            "chain": ["author", "qua", "pm"],
            "blocked_from_chain": [],
            "independence_forbidden": [],
            "notes": (
                "SIL 0-2: PM-led flat approval chain. "
                "EN 50128 §7.2: Software Requirements Specification mandatory."
            ),
        },
        "sil_high": {
            # Standard dev-phase SIL 3-4 chain:
            # owner → QUA (template) → VER (verify) → QUA (VER report template)
            # → VMGR (approve VER report) → COD (gate)
            "chain": ["author", "qua", "ver", "vmgr", "cod"],
            "blocked_from_chain": [],
            "independence_forbidden": [
                ("ver", "author"),   # VER ≠ requirements author (§5.1.2.10i)
                ("ver", "val"),      # VER ≠ VAL (§5.1.2.10j)
                ("val", "pm"),       # VAL not under PM (§5.1.2.10f)
            ],
            "notes": (
                "SIL 3-4 standard dev-phase chain. "
                "EN 50128 §5.1.2.10: independent VER mandatory; "
                "VMGR approves VER report; COD holds gate."
            ),
        },
    },

    # ------------------------------------------------------------------
    # Phase 3: Architecture & Design  (SAS, SDS, SIS, FMEA)
    # ------------------------------------------------------------------
    3: {
        "sil_low": {
            "chain": ["author", "qua", "pm"],
            "blocked_from_chain": [],
            "independence_forbidden": [],
            "notes": "SIL 0-2: PM-led flat approval chain. EN 50128 §7.3.",
        },
        "sil_high": {
            "chain": ["author", "qua", "ver", "vmgr", "cod"],
            "blocked_from_chain": [],
            "independence_forbidden": [
                ("ver", "author"),
                ("ver", "val"),
                ("val", "pm"),
            ],
            "notes": (
                "SIL 3-4: independent VER mandatory; VMGR approves; COD gates. "
                "EN 50128 §7.3 + §5.1.2.10."
            ),
        },
    },

    # ------------------------------------------------------------------
    # Phase 4: Implementation & Unit Testing  (Source, Unit Tests)
    # ------------------------------------------------------------------
    4: {
        "sil_low": {
            "chain": ["author", "qua", "pm"],
            "blocked_from_chain": [],
            "independence_forbidden": [],
            "notes": "SIL 0-2: PM-led flat approval chain. EN 50128 §7.4.",
        },
        "sil_high": {
            "chain": ["author", "qua", "ver", "vmgr", "cod"],
            "blocked_from_chain": [],
            "independence_forbidden": [
                ("ver", "author"),   # VER ≠ implementer (§5.1.2.10i)
                ("ver", "val"),
                ("val", "pm"),
            ],
            "notes": (
                "SIL 3-4: VER must be independent from implementer. "
                "EN 50128 §7.4 + §5.1.2.10i."
            ),
        },
    },

    # ------------------------------------------------------------------
    # Phase 5: Integration  (Integration Tests, Integration Report)
    # ------------------------------------------------------------------
    5: {
        "sil_low": {
            "chain": ["author", "qua", "pm"],
            "blocked_from_chain": [],
            "independence_forbidden": [],
            "notes": "SIL 0-2: PM-led flat approval chain. EN 50128 §7.6.",
        },
        "sil_high": {
            "chain": ["author", "qua", "ver", "vmgr", "cod"],
            "blocked_from_chain": [],
            "independence_forbidden": [
                ("ver", "author"),
                ("ver", "val"),
                ("val", "pm"),
            ],
            "notes": (
                "SIL 3-4: VER verifies integration evidence; VMGR approves; "
                "COD gates. EN 50128 §7.6 + §5.1.2.10."
            ),
        },
    },

    # ------------------------------------------------------------------
    # Phase 6: Validation  (System Tests, Validation Report)
    # ------------------------------------------------------------------
    6: {
        "sil_low": {
            "chain": ["author", "qua", "pm"],
            "blocked_from_chain": [],
            "independence_forbidden": [],
            "notes": "SIL 0-2: PM-led flat approval chain. EN 50128 §7.7.",
        },
        "sil_high": {
            # COD invokes VAL directly (independence from PM).
            # VAL performs system testing → QUA (template) → VMGR (reviews
            # VAL report) → COD (gate; CANNOT override VMGR decision).
            # VER report must already be VMGR-approved before VAL begins.
            "chain": ["val", "qua", "vmgr", "cod"],
            "blocked_from_chain": ["pm"],   # PM cannot direct VAL (§5.1.2.10f)
            "independence_forbidden": [
                ("val", "ver"),     # VAL ≠ VER (§5.1.2.10j)
                ("val", "author"),  # VAL ≠ dev team member
                ("val", "pm"),      # VAL not under PM (§5.1.2.10f)
            ],
            "notes": (
                "SIL 3-4: COD invokes VAL independently; PM BLOCKED. "
                "VAL decision is FINAL (§5.1.2.8); VMGR reviews but cannot "
                "override VAL release decision. EN 50128 §7.7 + §5.1.2.10f/j."
            ),
        },
    },

    # ------------------------------------------------------------------
    # Phase 7: Assessment-Ready  (compile artifact package for ASR)
    # ------------------------------------------------------------------
    7: {
        "sil_low": {
            # For SIL 0-2 there is no mandatory external ASR.
            # PM notifies COD; COD checks completeness.
            "chain": ["pm", "cod"],
            "blocked_from_chain": [],
            "independence_forbidden": [],
            "notes": (
                "SIL 0-2: PM notifies COD of assessment readiness; "
                "COD verifies completeness. No external ASR mandatory."
            ),
        },
        "sil_high": {
            # PM → CM: compile artifact package.
            # PM → COD: notify ready.
            # COD: gate-check completeness (no ASR agent; ASR is external).
            # PASS → CM creates Assessment-Ready Baseline.
            "chain": ["pm", "cm", "cod"],
            "blocked_from_chain": [],
            "independence_forbidden": [
                ("val", "pm"),
            ],
            "notes": (
                "SIL 3-4: PM+CM compile package; COD checks completeness; "
                "ASR is EXTERNAL (no platform agent). "
                "PASS → CM creates Assessment-Ready Baseline. "
                "EN 50128 §5.3: all lifecycle artifacts must be complete."
            ),
        },
    },

    # ------------------------------------------------------------------
    # Phase 8: Deployment  (Release Package)
    # ------------------------------------------------------------------
    8: {
        "sil_low": {
            "chain": ["pm", "cm", "cod"],
            "blocked_from_chain": [],
            "independence_forbidden": [],
            "notes": "SIL 0-2: PM authorizes; CM baselines; COD closes lifecycle.",
        },
        "sil_high": {
            # CM → VAL (final sign-off) → QUA (final quality gate)
            # → COD (authorizes release).
            "chain": ["cm", "val", "qua", "cod"],
            "blocked_from_chain": ["pm"],   # PM cannot authorize final release
            "independence_forbidden": [
                ("val", "pm"),
                ("val", "ver"),
            ],
            "notes": (
                "SIL 3-4: CM compiles; VAL provides final sign-off (§5.1.2.8); "
                "QUA final quality gate; COD authorizes deployment. "
                "PM is BLOCKED from final release chain."
            ),
        },
    },
}

# ============================================================================
# Gate Checker — deterministic EN 50128 gate enforcement
# ============================================================================


@dataclass
class GateViolation:
    """A single gate rule violation."""

    rule_id: str           # Short identifier, e.g. "CHAIN-ORDER-001"
    severity: str          # "BLOCK" | "WARN"
    description: str       # Human-readable description
    en50128_ref: str       # e.g. "§5.1.2.10i"
    actual: str = ""       # What was found
    expected: str = ""     # What was required


@dataclass
class GateResult:
    """Result of a gate-check invocation."""

    phase: int
    sil: int
    passed: bool
    violations: List[GateViolation] = field(default_factory=list)
    warnings: List[GateViolation] = field(default_factory=list)
    checked_documents: List[str] = field(default_factory=list)

    def to_text(self) -> str:
        """Render as human-readable text."""
        lines: List[str] = []
        status = "PASS" if self.passed else "FAIL"
        lines.append(f"\n{'='*70}")
        lines.append(
            f"Gate Check: Phase {self.phase} | SIL {self.sil} | {status}"
        )
        lines.append(f"{'='*70}")

        if self.checked_documents:
            lines.append(f"\nDocuments checked ({len(self.checked_documents)}):")
            for doc in self.checked_documents:
                lines.append(f"  - {doc}")

        if self.violations:
            lines.append(f"\nBLOCKING violations ({len(self.violations)}):")
            for v in self.violations:
                lines.append(f"  [{v.rule_id}] {v.description}")
                if v.actual:
                    lines.append(f"    Actual:   {v.actual}")
                if v.expected:
                    lines.append(f"    Expected: {v.expected}")
                lines.append(f"    Ref:      {v.en50128_ref}")

        if self.warnings:
            lines.append(f"\nWarnings ({len(self.warnings)}):")
            for w in self.warnings:
                lines.append(f"  [{w.rule_id}] {w.description}")
                lines.append(f"    Ref:      {w.en50128_ref}")

        if self.passed:
            lines.append(
                f"\nGate PASSED: Phase {self.phase} transition authorized."
            )
        else:
            lines.append(
                f"\nGate FAILED: Phase {self.phase} transition BLOCKED. "
                "Resolve all violations before proceeding."
            )

        lines.append(f"{'='*70}\n")
        return "\n".join(lines)

    def to_json(self) -> str:
        """Render as JSON."""
        return json.dumps(asdict(self), indent=2)


class GateChecker:
    """
    Deterministic EN 50128 gate-check engine.

    Validates that approval chains recorded in .workflow/documents/*.yaml
    conform to PHASE_APPROVAL_CHAINS for the given (phase, SIL) combination.

    Rules evaluated
    ---------------
    1. CHAIN-ROLES    : all required roles must have approved at least one
                        document in scope for the phase.
    2. CHAIN-ORDER    : approvals must appear in the correct order within
                        each document (role at position N approved before
                        role at position N+1).
    3. BLOCKED-ROLES  : roles listed in blocked_from_chain must NOT appear
                        as approvers on any phase document.
    4. INDEPENDENCE   : for SIL 3-4, forbidden role-pairs must not map to
                        the same person name across a phase's documents.
    5. STATE-COMPLETE : all documents for the phase must be in state
                        "approved" or "baseline" before the gate passes.
    """

    def __init__(self, workflow_manager: "WorkflowManager"):
        self.mgr = workflow_manager

    def check(self, phase: int, sil: int) -> GateResult:
        """
        Perform gate check for the given phase and SIL level.

        Args:
            phase: Phase number (1–8)
            sil:   SIL level (0–4)

        Returns:
            GateResult with passed/failed status and list of violations.
        """
        self._sil = sil  # store for use in sub-checkers
        result = GateResult(phase=phase, sil=sil, passed=True)

        # Resolve chain spec
        if phase not in PHASE_APPROVAL_CHAINS:
            result.passed = False
            result.violations.append(GateViolation(
                rule_id="PHASE-UNKNOWN",
                severity="BLOCK",
                description=f"Phase {phase} has no defined approval chain.",
                en50128_ref="LIFECYCLE.md",
            ))
            return result

        sil_group = "sil_high" if sil >= 3 else "sil_low"
        chain_spec = PHASE_APPROVAL_CHAINS[phase][sil_group]
        required_chain: List[str] = chain_spec["chain"]
        blocked_roles: List[str] = chain_spec["blocked_from_chain"]
        independence_pairs: List[Tuple[str, str]] = chain_spec["independence_forbidden"]

        # Gather all documents registered for this phase
        phase_docs = self._get_phase_documents(phase)
        result.checked_documents = [d.document_id for d in phase_docs]

        if not phase_docs:
            result.violations.append(GateViolation(
                rule_id="DOCS-MISSING",
                severity="BLOCK",
                description=(
                    f"No workflow documents found for Phase {phase}. "
                    "Submit documents before running gate-check."
                ),
                en50128_ref="LIFECYCLE.md",
            ))
            result.passed = False
            return result

        # --- Rule 5: STATE-COMPLETE ---
        self._check_state_complete(phase_docs, result)

        # --- Rule 3: BLOCKED-ROLES ---
        self._check_blocked_roles(phase_docs, blocked_roles, result)

        # For each document evaluate chain rules
        for doc in phase_docs:
            # --- Rule 1: CHAIN-ROLES ---
            self._check_chain_roles(doc, required_chain, result)

            # --- Rule 2: CHAIN-ORDER ---
            self._check_chain_order(doc, required_chain, result)

        # --- Rule 4: INDEPENDENCE (SIL 3-4 only) ---
        if sil >= 3:
            self._check_independence(phase_docs, independence_pairs, result)

        # Determine overall pass/fail
        result.passed = len(result.violations) == 0

        return result

    # ------------------------------------------------------------------
    # Internal rule checkers
    # ------------------------------------------------------------------

    def _get_phase_documents(self, phase: int) -> List["DocumentWorkflow"]:
        """Return all documents whose .phase matches the given phase number."""
        all_docs = self.mgr._list_workflows()
        phase_str = str(phase)
        return [
            d for d in all_docs
            if str(d.phase).strip() == phase_str or str(d.phase).strip() == f"phase-{phase_str}"
        ]

    def _check_state_complete(
        self,
        docs: List["DocumentWorkflow"],
        result: GateResult,
    ) -> None:
        """Rule 5: all phase documents must be approved or baselined."""
        terminal_states = {WorkflowState.APPROVED.value, WorkflowState.BASELINE.value}
        for doc in docs:
            if doc.state not in terminal_states:
                result.violations.append(GateViolation(
                    rule_id="STATE-COMPLETE",
                    severity="BLOCK",
                    description=(
                        f"Document {doc.document_id} is not yet approved. "
                        "All phase documents must be in 'approved' or 'baseline' state."
                    ),
                    en50128_ref="EN 50128 §6.1 (phase completion criteria)",
                    actual=doc.state,
                    expected="approved | baseline",
                ))

    def _check_blocked_roles(
        self,
        docs: List["DocumentWorkflow"],
        blocked_roles: List[str],
        result: GateResult,
    ) -> None:
        """Rule 3: blocked roles must not appear as approvers."""
        for doc in docs:
            for approval in doc.approvals:
                if approval.reviewer_role.lower() in blocked_roles:
                    result.violations.append(GateViolation(
                        rule_id="BLOCKED-ROLE",
                        severity="BLOCK",
                        description=(
                            f"Role '{approval.reviewer_role.upper()}' is BLOCKED "
                            f"from the approval chain for this phase/SIL combination "
                            f"but appears as approver on {doc.document_id}."
                        ),
                        en50128_ref=(
                            "EN 50128 §5.1.2.10f (VAL independent of PM); "
                            "§5.1.2.10e (VER reports to VMGR)"
                        ),
                        actual=f"{approval.reviewer_role.upper()} approved {doc.document_id}",
                        expected=f"No {approval.reviewer_role.upper()} approval on this phase",
                    ))

    def _check_chain_roles(
        self,
        doc: "DocumentWorkflow",
        required_chain: List[str],
        result: GateResult,
    ) -> None:
        """Rule 1: all required chain roles must have approved the document."""
        approved_roles = {a.reviewer_role.lower() for a in doc.approvals}
        for required_role in required_chain:
            # "author" is the document author role, not a separate approval step
            if required_role == "author":
                continue
            if required_role not in approved_roles:
                result.violations.append(GateViolation(
                    rule_id="CHAIN-ROLES",
                    severity="BLOCK",
                    description=(
                        f"Required role '{required_role.upper()}' has not approved "
                        f"document {doc.document_id}."
                    ),
                    en50128_ref="PHASE_APPROVAL_CHAINS (EN 50128 §5.3)",
                    actual=f"Approved by: {', '.join(r.upper() for r in approved_roles) or 'none'}",
                    expected=f"Approval from: {required_role.upper()}",
                ))

    def _check_chain_order(
        self,
        doc: "DocumentWorkflow",
        required_chain: List[str],
        result: GateResult,
    ) -> None:
        """
        Rule 2: approvals must occur in the correct order.

        Checks that the timestamp of role[i] is strictly before role[i+1]
        for every consecutive pair in required_chain (excluding "author").
        """
        # Build role→earliest timestamp map
        role_ts: Dict[str, str] = {}
        for approval in doc.approvals:
            role = approval.reviewer_role.lower()
            ts = approval.timestamp
            if role not in role_ts or ts < role_ts[role]:
                role_ts[role] = ts

        # Walk required chain (skip "author" placeholder)
        chain_roles = [r for r in required_chain if r != "author"]
        for i in range(len(chain_roles) - 1):
            role_a = chain_roles[i]
            role_b = chain_roles[i + 1]

            ts_a = role_ts.get(role_a)
            ts_b = role_ts.get(role_b)

            if ts_a is None or ts_b is None:
                # Missing role already caught by CHAIN-ROLES; skip ordering
                continue

            if ts_a >= ts_b:
                result.violations.append(GateViolation(
                    rule_id="CHAIN-ORDER",
                    severity="BLOCK",
                    description=(
                        f"Approval order violated on {doc.document_id}: "
                        f"{role_a.upper()} must approve BEFORE {role_b.upper()}."
                    ),
                    en50128_ref="PHASE_APPROVAL_CHAINS (EN 50128 §5.3)",
                    actual=(
                        f"{role_a.upper()} approved at {ts_a}; "
                        f"{role_b.upper()} approved at {ts_b}"
                    ),
                    expected=f"{role_a.upper()} timestamp < {role_b.upper()} timestamp",
                ))

    def _check_independence(
        self,
        docs: List["DocumentWorkflow"],
        independence_pairs: List[Tuple[str, str]],
        result: GateResult,
    ) -> None:
        """
        Rule 4 (SIL 3-4 only): forbidden role-pairs must not map to the same
        person across a phase's documents.

        For each (role_a, role_b) pair in independence_pairs, collect all
        person names that performed role_a across the phase docs and all names
        that performed role_b.  If any name appears in both sets → violation.
        """
        if not independence_pairs:
            return

        # Build role→{person_names} map across the entire phase.
        # The sentinel key "author" always maps to the document author's name
        # so that independence_pairs can use "author" to mean "whoever wrote
        # this document" regardless of their actual role (req/des/imp/…).
        role_persons: Dict[str, Set[str]] = {}

        for doc in docs:
            # Include author under their actual role AND under the sentinel "author"
            if doc.author_role and doc.author_name:
                role_persons.setdefault(doc.author_role.lower(), set()).add(doc.author_name)
                role_persons.setdefault("author", set()).add(doc.author_name)

            for approval in doc.approvals:
                role = approval.reviewer_role.lower()
                role_persons.setdefault(role, set()).add(approval.reviewer_name)

        for (role_a, role_b) in independence_pairs:
            persons_a = role_persons.get(role_a, set())
            persons_b = role_persons.get(role_b, set())

            overlap = persons_a & persons_b
            if overlap:
                result.violations.append(GateViolation(
                    rule_id="INDEPENDENCE",
                    severity="BLOCK",
                    description=(
                        f"Independence violation: the same person(s) performed "
                        f"both '{role_a.upper()}' and '{role_b.upper()}' roles, "
                        f"which is FORBIDDEN for SIL {self._sil} "
                        f"per EN 50128 §5.1.2.10."
                    ),
                    en50128_ref="EN 50128 §5.1.2.10i/j",
                    actual=(
                        f"Person(s) in both roles: "
                        f"{', '.join(sorted(overlap))}"
                    ),
                    expected=(
                        f"'{role_a.upper()}' and '{role_b.upper()}' performed "
                        "by different, organizationally independent persons."
                    ),
                ))


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
                match = re.search(r'\|\s*\*\*Project Name\*\*\s*\|\s*(.+?)\s*\|', content)
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
                match = re.search(r'\|\s*\*\*SIL Level\*\*\s*\|\s*(\d)', content)
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
               author_name: str, sil: int = None, phase: int = None) -> DocumentWorkflow:
        """
        Submit document for review.
        
        Args:
            document_id: Document identifier (e.g., "DOC-SRS-2026-001")
            document_path: Path to document file
            author_role: Author's role (REQ, DES, IMP, etc.)
            author_name: Author's name
            sil: SIL level (uses project SIL if not specified)
            phase: Phase number this document belongs to (1-8); stored on the
                   workflow record so gate-check can find it.
        
        Returns:
            DocumentWorkflow object
        """
        sil = sil if sil is not None else self.sil_level
        
        # Determine required approval workflow from PHASE_APPROVAL_CHAINS when
        # phase is known; fall back to generic config chain when phase is None.
        if phase is not None and phase in PHASE_APPROVAL_CHAINS:
            sil_group = "sil_high" if sil >= 3 else "sil_low"
            required_roles = PHASE_APPROVAL_CHAINS[phase][sil_group]["chain"]
        else:
            required_roles = self.config["approval_workflows"][f"sil_{min(sil, 4)}"]
        
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
            phase=str(phase) if phase is not None else "",
        )
        
        # Save workflow state
        self._save_workflow(workflow)
        
        # Log state transition
        self._log_history(document_id, "draft", "review", f"Submitted by {author_role} ({author_name})")
        
        print(f"✓ Document submitted for review: {document_id}")
        print(f"  State: Draft → Review")
        print(f"  SIL {sil} workflow: {len(required_roles)} approvals required")
        next_rev = required_roles[1].upper() if len(required_roles) > 1 else "N/A"
        print(f"  Next reviewer: {next_rev}")
        
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
        
        # Document must be in REVIEW state before it can be approved
        if workflow.state != WorkflowState.REVIEW.value:
            raise ValueError(
                f"Cannot approve document '{document_id}': current state is "
                f"'{workflow.state}', expected '{WorkflowState.REVIEW.value}'. "
                f"Submit the document for review first."
            )
        
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
            # Baseline all documents for phase.
            # submit() stores phase as a string (str(int) e.g. "2" or the raw
            # string the caller passed).  Normalise both sides to lower-case
            # stripped strings so "--phase requirements" and "--phase 2" both
            # work regardless of how the value was recorded.
            phase_norm = str(phase).strip().lower()
            all_workflows = self._list_workflows()
            phase_docs = [
                w for w in all_workflows
                if str(w.phase).strip().lower() == phase_norm
                and w.state == WorkflowState.APPROVED.value
            ]
            
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
            format: Output format (text, json)
        
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
                parts = line.strip().split("\t")
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
        """Save workflow state to YAML file (atomic write)."""
        workflow_path = self.workflow_dir / "documents" / f"{workflow.document_id}.yaml"

        import io as _io
        buf = _io.StringIO()
        yaml.dump(asdict(workflow), buf, default_flow_style=False)

        tmp_path = Path(str(workflow_path) + ".tmp")
        tmp_path.write_text(buf.getvalue())
        os.replace(tmp_path, workflow_path)
    
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
        """Log state transition to history.

        Format: tab-separated fields so that pipe characters in ``description``
        (e.g. approval counts such as "2/3") cannot corrupt the record.
        Field order: timestamp<TAB>old_state<TAB>new_state<TAB>description
        """
        history_path = self.workflow_dir / "history" / f"{document_id}.log"
        
        timestamp = datetime.now().isoformat()
        # Sanitize each field so they contain no tabs (replace with space)
        def _s(v: str) -> str:
            return str(v).replace("\t", " ")
        log_entry = f"{_s(timestamp)}\t{_s(old_state)}\t{_s(new_state)}\t{_s(description)}\n"
        
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
    
    # Gate check (validates EN 50128 approval chains before phase transition)
    %(prog)s gate-check --phase 2 --sil 3
    %(prog)s gate-check --phase 4 --sil 3 --format json
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
    submit_parser.add_argument('--phase', type=int, help='Phase number the document belongs to (1-8)')
    submit_parser.add_argument('--sil', type=int, help='SIL level (default: from LIFECYCLE_STATE.md)')
    
    # review command
    review_parser = subparsers.add_parser('review', help='Review and approve/reject document')
    review_parser.add_argument('document_id', help='Document identifier')
    review_parser.add_argument('--role', required=True, help='Reviewer role (PEER, QUA, VER, VAL, etc.)')
    review_parser.add_argument('--name', required=True, help='Reviewer name')
    _review_action = review_parser.add_mutually_exclusive_group(required=True)
    _review_action.add_argument('--approve', action='store_true', help='Approve document')
    _review_action.add_argument('--reject', action='store_true', help='Reject document')
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
    history_parser.add_argument('--format', choices=['text', 'json'], default='text', help='Output format')

    # gate-check command
    gate_parser = subparsers.add_parser(
        'gate-check',
        help='Validate EN 50128 phase gate prerequisites',
    )
    gate_parser.add_argument(
        '--phase', type=int, required=True,
        help='Phase number to check (1-8)',
        choices=list(range(1, 9)),
    )
    gate_parser.add_argument(
        '--sil', type=int,
        help='SIL level override (default: from LIFECYCLE_STATE.md)',
        choices=[0, 1, 2, 3, 4],
    )
    gate_parser.add_argument(
        '--format', dest='gate_format',
        choices=['text', 'json'], default='text',
        help='Output format (default: text)',
    )

    args = parser.parse_args()
    
    if not args.command:
        parser.print_help()
        return 1
    
    # Initialize manager
    mgr = WorkflowManager(project=args.project)
    
    # Execute command
    try:
        if args.command == 'submit':
            mgr.submit(args.document_id, args.path, args.author_role, args.author_name, args.sil, args.phase)
        
        elif args.command == 'review':
            mgr.review(args.document_id, args.role, args.name, args.approve, args.reject, args.comment)
        
        elif args.command == 'approve':
            mgr.approve(args.document_id, args.force)
        
        elif args.command == 'baseline':
            mgr.baseline(document_id=args.document, phase=args.phase, tag=args.tag, message=args.message)
        
        elif args.command == 'status':
            result = mgr.status(document_id=args.document, phase=args.phase, all=args.all, format=args.format, show_approvals=args.approvals)
            print(result)
        
        elif args.command == 'history':
            result = mgr.history(args.document_id, args.format)
            print(result)

        elif args.command == 'gate-check':
            sil = args.sil if args.sil is not None else mgr.sil_level
            checker = GateChecker(mgr)
            gate_result = checker.check(phase=args.phase, sil=sil)
            if args.gate_format == 'json':
                print(gate_result.to_json())
            else:
                print(gate_result.to_text())
            # Exit code 1 on gate failure so CI pipelines can block progression
            if not gate_result.passed:
                return 1
        
        return 0
    
    except Exception as e:
        print(f"✗ Error: {e}", file=sys.stderr)
        if args.verbose:
            import traceback
            traceback.print_exc()
        return 1

if __name__ == '__main__':
    sys.exit(main())
