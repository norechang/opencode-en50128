#!/usr/bin/env python3
"""
Traceability Manager Tool for EN 50128 Projects

Purpose: Create, maintain, and validate traceability matrices across the
         EN 50128 software development lifecycle.

Usage:
    python3 tools/traceability_manager.py <command> [options]

Commands:
    create       Create new traceability matrix template
    validate     Validate traceability completeness
    query        Query traceability links
    report       Generate traceability report
    import       Import traceability data
    export       Export traceability data
    check-gaps   Detect traceability gaps
    extract      Auto-extract traceability from documents
    visualize    Generate traceability visualizations
    sync         Synchronize CSV/JSON/Markdown formats

EN 50128 Compliance:
    - SIL 3-4: 100% traceability MANDATORY (Table A.9, Technique 7)
    - SIL 1-2: Traceability Highly Recommended
    - SIL 0: Traceability Recommended

Version: 1.0
Date: 2026-03-13
"""

import argparse
import csv
import json
import os
import re
import sys
from dataclasses import dataclass, asdict, field
from datetime import datetime
from enum import Enum
from pathlib import Path
from typing import List, Dict, Optional, Set, Tuple

# ============================================================================
# Data Models
# ============================================================================

class ArtifactType(Enum):
    """EN 50128 artifact types for traceability."""
    
    # Requirements
    SYSTEM_REQUIREMENT = "system_requirement"
    SOFTWARE_REQUIREMENT = "software_requirement"
    SAFETY_REQUIREMENT = "safety_requirement"
    INTERFACE_REQUIREMENT = "interface_requirement"
    
    # Design
    ARCHITECTURE_COMPONENT = "architecture_component"
    DESIGN_COMPONENT = "design_component"
    INTERFACE_SPECIFICATION = "interface_specification"
    
    # Implementation
    SOURCE_FILE = "source_file"
    FUNCTION = "function"
    MODULE = "module"
    
    # Testing
    TEST_CASE = "test_case"
    TEST_PROCEDURE = "test_procedure"
    TEST_RESULT = "test_result"
    
    # Verification
    VERIFICATION_RECORD = "verification_record"
    REVIEW_RECORD = "review_record"
    
    # Safety
    HAZARD = "hazard"
    SAFETY_MECHANISM = "safety_mechanism"
    
    # Other
    DELIVERABLE = "deliverable"
    CHANGE_REQUEST = "change_request"

class LinkType(Enum):
    """Types of traceability links."""
    
    ALLOCATED_TO = "allocated_to"        # Requirement → Architecture
    IMPLEMENTS = "implements"             # Design → Code
    TESTS = "tests"                       # Test → Requirement
    VERIFIES = "verifies"                 # Verification → Requirement
    DERIVES_FROM = "derives_from"         # SW Req → System Req
    REFINES = "refines"                   # Design → Architecture
    SATISFIES = "satisfies"               # Code → Design
    MITIGATES = "mitigates"               # Safety Mechanism → Hazard
    DEPENDS_ON = "depends_on"             # Generic dependency

@dataclass
class TraceabilityLink:
    """Represents a single traceability link between two artifacts."""
    
    # Link identifiers
    source_id: str
    source_type: str
    target_id: str
    target_type: str
    
    # Link metadata
    link_type: str = "allocated_to"
    rationale: str = ""
    
    # Verification data
    verified: bool = False
    verified_by: str = ""
    verified_date: str = ""
    
    # Quality metadata
    confidence: str = "high"  # high, medium, low
    source_document: str = ""
    
    # Traceability
    created_date: str = ""
    modified_date: str = ""
    version: str = "1.0"
    
    def __post_init__(self):
        """Initialize timestamps if not provided."""
        if not self.created_date:
            self.created_date = datetime.now().isoformat()
        if not self.modified_date:
            self.modified_date = self.created_date

@dataclass
class TraceabilityMatrix:
    """Represents a complete traceability matrix between two artifact types."""
    
    # Matrix metadata
    name: str
    source_type: str
    target_type: str
    project: str
    
    # Links
    links: List[TraceabilityLink] = field(default_factory=list)
    
    # Validation metadata
    coverage: float = 0.0
    completeness: float = 0.0
    sil_level: int = 0
    
    # Status
    status: str = "draft"  # draft, review, approved, baseline
    approved_by: str = ""
    approved_date: str = ""
    
    # File paths
    csv_path: str = ""
    json_path: str = ""
    markdown_path: str = ""
    
    # Version control
    version: str = "1.0"
    baseline: str = ""
    
    # Timestamps
    created_date: str = ""
    modified_date: str = ""
    
    def __post_init__(self):
        """Initialize timestamps if not provided."""
        if not self.created_date:
            self.created_date = datetime.now().isoformat()
        if not self.modified_date:
            self.modified_date = self.created_date

# ============================================================================
# Traceability Manager Core
# ============================================================================

class TraceabilityManager:
    """Core traceability management functionality."""
    
    def __init__(self, project: str = None, evidence_dir: str = "evidence/traceability"):
        """
        Initialize Traceability Manager.
        
        Args:
            project: Project name (reads from LIFECYCLE_STATE.md if None)
            evidence_dir: Directory for traceability evidence
        """
        self.project = project or self._read_project_name()
        self.evidence_dir = Path(evidence_dir)
        self.evidence_dir.mkdir(parents=True, exist_ok=True)
        
        # Load configuration
        self.config = self._load_config()
        
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
    
    def _load_config(self) -> Dict:
        """Load traceability configuration."""
        # Default configuration
        config = {
            "sil_thresholds": {
                0: 0.80,  # 80% coverage for SIL 0
                1: 0.90,  # 90% coverage for SIL 1
                2: 0.95,  # 95% coverage for SIL 2
                3: 1.00,  # 100% coverage for SIL 3 (MANDATORY)
                4: 1.00,  # 100% coverage for SIL 4 (MANDATORY)
            },
            "artifact_patterns": {
                "software_requirement": r"(SW-REQ-[A-Z]+-[A-Z0-9]+-\d+|REQ-[A-Z]+-[A-Z0-9]+-\d+)",
                "system_requirement": r"SYS-REQ-[A-Z]+-[A-Z0-9]+-\d+",
                "architecture_component": r"ARCH-[A-Z]+-[A-Z0-9]+-\d+",
                "design_component": r"DES-[A-Z]+-[A-Z0-9]+-\d+",
                "test_case": r"TEST-[A-Z]+-[A-Z0-9]+-\d+",
                "function": r"[a-z_][a-z0-9_]*\(\)",
            }
        }
        
        # Load from .traceability.yaml if exists
        config_path = Path(".traceability.yaml")
        if config_path.exists():
            import yaml
            with open(config_path) as f:
                user_config = yaml.safe_load(f)
                config.update(user_config)
        
        return config
    
    # ========================================================================
    # Command: create
    # ========================================================================
    
    def create_matrix(self, source_type: str, target_type: str, output_path: str = None) -> TraceabilityMatrix:
        """
        Create new traceability matrix template.
        
        Args:
            source_type: Source artifact type (e.g., "requirements")
            target_type: Target artifact type (e.g., "architecture")
            output_path: Optional output path (default: evidence/traceability/)
        
        Returns:
            TraceabilityMatrix: Created matrix
        """
        matrix_name = f"{source_type}_to_{target_type}"
        
        # Create matrix object
        matrix = TraceabilityMatrix(
            name=matrix_name,
            source_type=source_type,
            target_type=target_type,
            project=self.project,
        )
        
        # Set file paths
        if output_path:
            base_path = Path(output_path)
        else:
            base_path = self.evidence_dir / matrix_name
        
        matrix.csv_path = str(base_path.with_suffix('.csv'))
        matrix.json_path = str(base_path.with_suffix('.json'))
        matrix.markdown_path = str(base_path.with_suffix('.md'))
        
        # Create empty CSV template
        self._write_csv(matrix)
        
        # Create JSON index
        self._write_json(matrix)
        
        # Create Markdown report
        self._write_markdown(matrix)
        
        print(f"✓ Created traceability matrix: {matrix_name}")
        print(f"  CSV:      {matrix.csv_path}")
        print(f"  JSON:     {matrix.json_path}")
        print(f"  Markdown: {matrix.markdown_path}")
        
        return matrix
    
    # ========================================================================
    # Command: validate
    # ========================================================================
    
    def validate(self, matrix_name: str = None, phase: str = None, sil: int = 0) -> Dict:
        """
        Validate traceability completeness.
        
        Args:
            matrix_name: Specific matrix to validate (e.g., "requirements_to_architecture")
            phase: Validate all matrices for lifecycle phase
            sil: SIL level (0-4) for validation thresholds
        
        Returns:
            Dict with validation results
        """
        results = {
            "project": self.project,
            "sil": sil,
            "threshold": self.config["sil_thresholds"][sil],
            "matrices": [],
            "overall_pass": True,
        }
        
        # Determine which matrices to validate
        if matrix_name:
            matrices_to_validate = [matrix_name]
        elif phase:
            matrices_to_validate = self._get_phase_matrices(phase)
        else:
            # Validate all matrices
            matrices_to_validate = [p.stem for p in self.evidence_dir.glob("*.csv")]
        
        for name in matrices_to_validate:
            matrix_result = self._validate_matrix(name, sil)
            results["matrices"].append(matrix_result)
            
            if not matrix_result["pass"]:
                results["overall_pass"] = False
        
        # Print results
        self._print_validation_results(results)
        
        return results
    
    def _validate_matrix(self, matrix_name: str, sil: int) -> Dict:
        """Validate a single traceability matrix."""
        csv_path = self.evidence_dir / f"{matrix_name}.csv"
        
        if not csv_path.exists():
            return {
                "name": matrix_name,
                "pass": False,
                "error": "Matrix file not found",
                "coverage": 0.0,
            }
        
        # Load matrix
        matrix = self._read_csv(str(csv_path))
        
        # Calculate coverage
        sources = set()
        sources_with_targets = set()
        
        for link in matrix.links:
            sources.add(link.source_id)
            if link.target_id:
                sources_with_targets.add(link.source_id)
        
        coverage = len(sources_with_targets) / len(sources) if sources else 0.0
        threshold = self.config["sil_thresholds"][sil]
        
        return {
            "name": matrix_name,
            "pass": coverage >= threshold,
            "coverage": coverage,
            "threshold": threshold,
            "total_sources": len(sources),
            "traced_sources": len(sources_with_targets),
            "untraceable_sources": len(sources) - len(sources_with_targets),
        }
    
    def _get_phase_matrices(self, phase: str) -> List[str]:
        """Get required traceability matrices for a lifecycle phase."""
        phase_matrices = {
            "requirements": [
                "system_requirements_to_software_requirements",
                "software_requirements_to_tests",
            ],
            "design": [
                "system_requirements_to_software_requirements",
                "software_requirements_to_architecture",
                "architecture_to_design",
                "software_requirements_to_tests",
            ],
            "implementation": [
                "design_to_code",
                "code_to_unit_tests",
            ],
            "integration": [
                "architecture_to_integration_tests",
                "design_to_integration_tests",
            ],
            "validation": [
                "software_requirements_to_validation_tests",
                "code_to_validation_tests",
            ],
        }
        
        return phase_matrices.get(phase, [])
    
    def _print_validation_results(self, results: Dict):
        """Print validation results to console."""
        print(f"\n{'='*70}")
        print(f"Traceability Validation Report")
        print(f"{'='*70}")
        print(f"Project:    {results['project']}")
        print(f"SIL Level:  {results['sil']}")
        print(f"Threshold:  {results['threshold']*100:.0f}%")
        print(f"{'='*70}\n")
        
        for matrix in results["matrices"]:
            status = "✓ PASS" if matrix["pass"] else "✗ FAIL"
            print(f"{status}  {matrix['name']}")
            print(f"       Coverage: {matrix['coverage']*100:.1f}% ({matrix['traced_sources']}/{matrix['total_sources']})")
            
            if not matrix["pass"]:
                print(f"       ⚠ {matrix['untraceable_sources']} sources not traced")
            print()
        
        print(f"{'='*70}")
        overall_status = "✓ PASS" if results["overall_pass"] else "✗ FAIL"
        print(f"Overall Status: {overall_status}")
        print(f"{'='*70}\n")
    
    # ========================================================================
    # Command: query
    # ========================================================================
    
    def query(self, source_id: str = None, target_id: str = None, direction: str = "forward") -> List[TraceabilityLink]:
        """
        Query traceability links.
        
        Args:
            source_id: Source artifact ID (e.g., "SW-REQ-015")
            target_id: Target artifact ID (e.g., "ARCH-COMP-005")
            direction: Query direction (forward, backward, both)
        
        Returns:
            List of TraceabilityLink objects
        """
        all_matrices = list(self.evidence_dir.glob("*.csv"))
        results = []
        
        for csv_path in all_matrices:
            matrix = self._read_csv(str(csv_path))
            
            for link in matrix.links:
                if source_id and link.source_id == source_id:
                    if direction in ["forward", "both"]:
                        results.append(link)
                
                if target_id and link.target_id == target_id:
                    if direction in ["backward", "both"]:
                        results.append(link)
        
        # Print results
        self._print_query_results(results, source_id, target_id, direction)
        
        return results
    
    def _print_query_results(self, results: List[TraceabilityLink], source_id: str, target_id: str, direction: str):
        """Print query results to console."""
        print(f"\n{'='*70}")
        print(f"Traceability Query Results")
        print(f"{'='*70}")
        
        if source_id:
            print(f"Source:    {source_id}")
        if target_id:
            print(f"Target:    {target_id}")
        print(f"Direction: {direction}")
        print(f"Found:     {len(results)} links")
        print(f"{'='*70}\n")
        
        for link in results:
            print(f"{link.source_id} → {link.target_id}")
            print(f"  Type:       {link.link_type}")
            print(f"  Rationale:  {link.rationale}")
            print(f"  Verified:   {link.verified} (by {link.verified_by})")
            print()
    
    # ========================================================================
    # Command: check-gaps
    # ========================================================================
    
    def check_gaps(self, phase: str = None, sil: int = 0) -> Dict:
        """
        Detect traceability gaps.
        
        Args:
            phase: Lifecycle phase to check
            sil: SIL level
        
        Returns:
            Dict with gap analysis
        """
        gaps = {
            "orphan_sources": [],      # Sources with no target
            "orphan_targets": [],      # Targets with no source
            "unverified_links": [],    # Links not verified
            "low_confidence": [],      # Auto-extracted links with low confidence
        }
        
        # Determine matrices to check
        if phase:
            matrices = self._get_phase_matrices(phase)
        else:
            matrices = [p.stem for p in self.evidence_dir.glob("*.csv")]
        
        # Collect all sources and targets
        all_sources = set()
        all_targets = set()
        traced_sources = set()
        traced_targets = set()
        
        for matrix_name in matrices:
            csv_path = self.evidence_dir / f"{matrix_name}.csv"
            if not csv_path.exists():
                continue
            
            matrix = self._read_csv(str(csv_path))
            
            for link in matrix.links:
                all_sources.add(link.source_id)
                all_targets.add(link.target_id)
                
                if link.target_id:
                    traced_sources.add(link.source_id)
                    traced_targets.add(link.target_id)
                
                if not link.verified:
                    gaps["unverified_links"].append({
                        "matrix": matrix_name,
                        "link": f"{link.source_id} → {link.target_id}",
                    })
                
                if link.confidence == "low":
                    gaps["low_confidence"].append({
                        "matrix": matrix_name,
                        "link": f"{link.source_id} → {link.target_id}",
                    })
        
        # Identify orphans
        gaps["orphan_sources"] = list(all_sources - traced_sources)
        gaps["orphan_targets"] = list(all_targets - traced_targets)
        
        # Print results
        self._print_gap_analysis(gaps, sil)
        
        return gaps
    
    def _print_gap_analysis(self, gaps: Dict, sil: int):
        """Print gap analysis to console."""
        print(f"\n{'='*70}")
        print(f"Traceability Gap Analysis (SIL {sil})")
        print(f"{'='*70}\n")
        
        print(f"Orphan Sources (no targets): {len(gaps['orphan_sources'])}")
        for source in gaps['orphan_sources'][:10]:  # Show first 10
            print(f"  - {source}")
        if len(gaps['orphan_sources']) > 10:
            print(f"  ... and {len(gaps['orphan_sources']) - 10} more")
        print()
        
        print(f"Orphan Targets (no sources): {len(gaps['orphan_targets'])}")
        for target in gaps['orphan_targets'][:10]:
            print(f"  - {target}")
        if len(gaps['orphan_targets']) > 10:
            print(f"  ... and {len(gaps['orphan_targets']) - 10} more")
        print()
        
        print(f"Unverified Links: {len(gaps['unverified_links'])}")
        if sil >= 3:
            print("  ⚠ WARNING: All links must be verified for SIL 3-4")
        print()
        
        print(f"Low Confidence Links: {len(gaps['low_confidence'])}")
        if gaps['low_confidence']:
            print("  ⚠ Recommend manual review")
        print()
        
        print(f"{'='*70}\n")
    
    # ========================================================================
    # Command: report
    # ========================================================================
    
    def report(self, source_type: str, target_types: List[str], format: str = "markdown", output: str = None) -> str:
        """
        Generate traceability report.
        
        Args:
            source_type: Source artifact type
            target_types: List of target artifact types
            format: Output format (markdown, csv, json, html)
            output: Output file path
        
        Returns:
            Report content as string
        """
        report_lines = []
        
        # Header
        report_lines.append(f"# Traceability Report: {source_type}")
        report_lines.append(f"\n**Project**: {self.project}")
        report_lines.append(f"**Date**: {datetime.now().strftime('%Y-%m-%d %H:%M')}")
        report_lines.append(f"\n---\n")
        
        # For each target type
        for target_type in target_types:
            matrix_name = f"{source_type}_to_{target_type}"
            csv_path = self.evidence_dir / f"{matrix_name}.csv"
            
            if not csv_path.exists():
                report_lines.append(f"\n## {source_type} → {target_type}")
                report_lines.append(f"\n⚠ Matrix not found: {matrix_name}\n")
                continue
            
            matrix = self._read_csv(str(csv_path))
            
            # Calculate metrics
            total_sources = len(set(link.source_id for link in matrix.links))
            traced_sources = len(set(link.source_id for link in matrix.links if link.target_id))
            coverage = traced_sources / total_sources if total_sources > 0 else 0.0
            
            report_lines.append(f"\n## {source_type} → {target_type}")
            report_lines.append(f"\n**Coverage**: {coverage*100:.1f}% ({traced_sources}/{total_sources})")
            report_lines.append(f"**Total Links**: {len(matrix.links)}\n")
            
            # Traceability table
            report_lines.append(f"\n| Source ID | Target ID | Link Type | Verified |\n")
            report_lines.append(f"|-----------|-----------|-----------|----------|\n")
            
            for link in sorted(matrix.links, key=lambda x: x.source_id):
                verified_icon = "✓" if link.verified else "✗"
                report_lines.append(f"| {link.source_id} | {link.target_id} | {link.link_type} | {verified_icon} |\n")
            
            report_lines.append("\n")
        
        report_content = "".join(report_lines)
        
        # Write to file if output specified
        if output:
            with open(output, "w") as f:
                f.write(report_content)
            print(f"✓ Report written to: {output}")
        else:
            print(report_content)
        
        return report_content
    
    # ========================================================================
    # Command: import
    # ========================================================================
    
    def import_data(self, file_path: str, matrix_type: str, format: str = None) -> TraceabilityMatrix:
        """
        Import traceability data from external file.
        
        Args:
            file_path: Input file path
            matrix_type: Matrix type (e.g., "requirements_to_architecture")
            format: Input format (csv, json, excel) - auto-detected if None
        
        Returns:
            TraceabilityMatrix with imported links
        """
        input_path = Path(file_path)
        
        if not input_path.exists():
            raise FileNotFoundError(f"Import file not found: {file_path}")
        
        # Auto-detect format
        if not format:
            format = input_path.suffix.lstrip('.')
            if format in ['xls', 'xlsx']:
                format = 'excel'
        
        # Parse matrix type to get source/target
        parts = matrix_type.split('_to_')
        if len(parts) != 2:
            raise ValueError(f"Invalid matrix type format: {matrix_type} (expected: source_to_target)")
        
        source_type, target_type = parts
        
        # Import based on format
        if format == 'csv':
            links = self._import_csv(file_path)
        elif format == 'json':
            links = self._import_json(file_path)
        elif format == 'excel':
            links = self._import_excel(file_path)
        else:
            raise ValueError(f"Unsupported import format: {format}")
        
        # Create matrix with imported links
        matrix = TraceabilityMatrix(
            name=matrix_type,
            source_type=source_type,
            target_type=target_type,
            project=self.project,
            links=links,
        )
        
        # Set output paths
        base_path = self.evidence_dir / matrix_type
        matrix.csv_path = str(base_path.with_suffix('.csv'))
        matrix.json_path = str(base_path.with_suffix('.json'))
        matrix.markdown_path = str(base_path.with_suffix('.md'))
        
        # Write to standard format
        self._write_csv(matrix)
        self._write_json(matrix)
        self._write_markdown(matrix)
        
        print(f"✓ Imported {len(links)} traceability links from {file_path}")
        print(f"  Format: {format}")
        print(f"  Matrix: {matrix_type}")
        print(f"  Output: {matrix.csv_path}")
        
        return matrix
    
    def _import_csv(self, file_path: str) -> List[TraceabilityLink]:
        """Import links from CSV file."""
        links = []
        
        with open(file_path, 'r') as f:
            reader = csv.DictReader(f)
            for row in reader:
                link = TraceabilityLink(
                    source_id=row.get('source_id', ''),
                    source_type=row.get('source_type', ''),
                    target_id=row.get('target_id', ''),
                    target_type=row.get('target_type', ''),
                    link_type=row.get('link_type', 'allocated_to'),
                    rationale=row.get('rationale', ''),
                    verified=row.get('verified', 'false').lower() == 'true',
                    verified_by=row.get('verified_by', ''),
                    verified_date=row.get('verified_date', ''),
                    confidence=row.get('confidence', 'high'),
                    source_document=row.get('source_document', ''),
                )
                links.append(link)
        
        return links
    
    def _import_json(self, file_path: str) -> List[TraceabilityLink]:
        """Import links from JSON file."""
        with open(file_path, 'r') as f:
            data = json.load(f)
        
        links = []
        for link_data in data.get('links', []):
            link = TraceabilityLink(
                source_id=link_data.get('source_id', ''),
                source_type=link_data.get('source_type', ''),
                target_id=link_data.get('target_id', ''),
                target_type=link_data.get('target_type', ''),
                link_type=link_data.get('link_type', 'allocated_to'),
                rationale=link_data.get('rationale', ''),
                verified=link_data.get('verified', False),
                verified_by=link_data.get('verified_by', ''),
                verified_date=link_data.get('verified_date', ''),
                confidence=link_data.get('confidence', 'high'),
                source_document=link_data.get('source_document', ''),
            )
            links.append(link)
        
        return links
    
    def _import_excel(self, file_path: str) -> List[TraceabilityLink]:
        """Import links from Excel file."""
        try:
            import openpyxl
        except ImportError:
            raise ImportError("openpyxl library required for Excel import. Install: pip install openpyxl")
        
        workbook = openpyxl.load_workbook(file_path)
        sheet = workbook.active
        
        links = []
        headers = [cell.value for cell in sheet[1]]
        
        for row in sheet.iter_rows(min_row=2, values_only=True):
            row_dict = dict(zip(headers, row))
            
            link = TraceabilityLink(
                source_id=row_dict.get('source_id', ''),
                source_type=row_dict.get('source_type', ''),
                target_id=row_dict.get('target_id', ''),
                target_type=row_dict.get('target_type', ''),
                link_type=row_dict.get('link_type', 'allocated_to'),
                rationale=row_dict.get('rationale', ''),
                verified=str(row_dict.get('verified', 'false')).lower() == 'true',
                verified_by=row_dict.get('verified_by', ''),
                verified_date=row_dict.get('verified_date', ''),
                confidence=row_dict.get('confidence', 'high'),
                source_document=row_dict.get('source_document', ''),
            )
            links.append(link)
        
        return links
    
    # ========================================================================
    # Command: export
    # ========================================================================
    
    def export_data(self, matrix_name: str, format: str, output_path: str) -> str:
        """
        Export traceability data to external format.
        
        Args:
            matrix_name: Matrix name (or "all" for all matrices)
            format: Output format (csv, json, excel, markdown)
            output_path: Output file path
        
        Returns:
            Output file path
        """
        if matrix_name == "all":
            # Export all matrices
            matrices = [p.stem for p in self.evidence_dir.glob("*.csv")]
            
            if format == "json":
                # Combine all matrices into single JSON
                all_data = []
                for name in matrices:
                    csv_path = self.evidence_dir / f"{name}.csv"
                    matrix = self._read_csv(str(csv_path))
                    all_data.append({
                        'name': matrix.name,
                        'source_type': matrix.source_type,
                        'target_type': matrix.target_type,
                        'links': [asdict(link) for link in matrix.links],
                    })
                
                with open(output_path, 'w') as f:
                    json.dump({'project': self.project, 'matrices': all_data}, f, indent=2)
                
                print(f"✓ Exported {len(matrices)} matrices to {output_path}")
                
            else:
                raise ValueError("Export all matrices only supported for JSON format")
        
        else:
            # Export single matrix
            csv_path = self.evidence_dir / f"{matrix_name}.csv"
            
            if not csv_path.exists():
                raise FileNotFoundError(f"Matrix not found: {matrix_name}")
            
            matrix = self._read_csv(str(csv_path))
            
            if format == "csv":
                # Copy CSV
                import shutil
                shutil.copy(matrix.csv_path, output_path)
            
            elif format == "json":
                data = {
                    'name': matrix.name,
                    'source_type': matrix.source_type,
                    'target_type': matrix.target_type,
                    'project': self.project,
                    'links': [asdict(link) for link in matrix.links],
                }
                with open(output_path, 'w') as f:
                    json.dump(data, f, indent=2)
            
            elif format == "markdown":
                # Copy Markdown
                import shutil
                shutil.copy(matrix.markdown_path, output_path)
            
            elif format == "excel":
                self._export_excel(matrix, output_path)
            
            else:
                raise ValueError(f"Unsupported export format: {format}")
            
            print(f"✓ Exported {matrix_name} to {output_path}")
            print(f"  Format: {format}")
            print(f"  Links: {len(matrix.links)}")
        
        return output_path
    
    def _export_excel(self, matrix: TraceabilityMatrix, output_path: str):
        """Export matrix to Excel format."""
        try:
            import openpyxl
        except ImportError:
            raise ImportError("openpyxl library required for Excel export. Install: pip install openpyxl")
        
        workbook = openpyxl.Workbook()
        sheet = workbook.active
        sheet.title = matrix.name[:31]  # Excel sheet name limit
        
        # Headers
        headers = ['source_id', 'source_type', 'target_id', 'target_type', 
                   'link_type', 'rationale', 'verified', 'verified_by', 'verified_date',
                   'confidence', 'source_document']
        sheet.append(headers)
        
        # Data rows
        for link in matrix.links:
            sheet.append([
                link.source_id, link.source_type, link.target_id, link.target_type,
                link.link_type, link.rationale, str(link.verified).lower(), link.verified_by,
                link.verified_date, link.confidence, link.source_document,
            ])
        
        workbook.save(output_path)
    
    # ========================================================================
    # Command: extract
    # ========================================================================
    
    def extract(self, document_path: str, link_type: str, merge: bool = False) -> List[TraceabilityLink]:
        """
        Auto-extract traceability links from documents.
        
        Args:
            document_path: Document file path (Markdown, C source, etc.)
            link_type: Link type (e.g., "design_to_requirements", "code_to_requirements")
            merge: Merge with existing matrix (default: False)
        
        Returns:
            List of extracted TraceabilityLink objects
        """
        doc_path = Path(document_path)
        
        if not doc_path.exists():
            raise FileNotFoundError(f"Document not found: {document_path}")
        
        # Read document content
        with open(doc_path, 'r') as f:
            content = f.read()
        
        # Parse link_type to determine source/target types
        # link_type format: "source_to_target" (e.g., "design_to_requirements")
        parts = link_type.split('_to_')
        if len(parts) != 2:
            raise ValueError(f"Invalid link type format: {link_type} (expected: source_to_target)")
        
        source_type, target_type = parts
        
        # Extract links using pattern matching
        extracted_links = self._extract_links_from_content(content, source_type, target_type, doc_path.name)
        
        print(f"\n{'='*70}")
        print(f"Traceability Extraction Results")
        print(f"{'='*70}")
        print(f"Document:      {document_path}")
        print(f"Link Type:     {link_type}")
        print(f"Extracted:     {len(extracted_links)} links")
        print(f"{'='*70}\n")
        
        # Show extracted links
        for link in extracted_links[:10]:  # Show first 10
            print(f"{link.source_id} → {link.target_id} (confidence: {link.confidence})")
        
        if len(extracted_links) > 10:
            print(f"... and {len(extracted_links) - 10} more")
        
        print()
        
        # Merge with existing matrix if requested
        if merge:
            matrix_name = f"{source_type}_to_{target_type}"
            csv_path = self.evidence_dir / f"{matrix_name}.csv"
            
            if csv_path.exists():
                existing_matrix = self._read_csv(str(csv_path))
                
                # Merge: keep existing links, add new ones
                existing_ids = set((link.source_id, link.target_id) for link in existing_matrix.links)
                new_links = [link for link in extracted_links 
                            if (link.source_id, link.target_id) not in existing_ids]
                
                existing_matrix.links.extend(new_links)
                
                # Update files
                self._write_csv(existing_matrix)
                self._write_json(existing_matrix)
                self._write_markdown(existing_matrix)
                
                print(f"✓ Merged {len(new_links)} new links into {matrix_name}")
                print(f"  Total links: {len(existing_matrix.links)}")
            
            else:
                # Create new matrix
                matrix = TraceabilityMatrix(
                    name=matrix_name,
                    source_type=source_type,
                    target_type=target_type,
                    project=self.project,
                    links=extracted_links,
                )
                
                base_path = self.evidence_dir / matrix_name
                matrix.csv_path = str(base_path.with_suffix('.csv'))
                matrix.json_path = str(base_path.with_suffix('.json'))
                matrix.markdown_path = str(base_path.with_suffix('.md'))
                
                self._write_csv(matrix)
                self._write_json(matrix)
                self._write_markdown(matrix)
                
                print(f"✓ Created new matrix {matrix_name} with {len(extracted_links)} links")
        
        return extracted_links
    
    def _extract_links_from_content(self, content: str, source_type: str, target_type: str, 
                                     source_document: str) -> List[TraceabilityLink]:
        """Extract traceability links from document content using pattern matching."""
        links = []
        
        # Get patterns from config
        patterns = self.config.get('artifact_patterns', {})
        
        # Determine patterns based on artifact types
        target_pattern = patterns.get(target_type)
        if not target_pattern:
            # Use generic pattern
            target_pattern = r'[A-Z]+-[A-Z]+-[A-Z0-9]+-\d+'
        
        # Find all target artifact references
        target_matches = re.finditer(target_pattern, content)
        
        # For each match, try to determine source artifact
        # Heuristic: look for section headers or explicit source IDs near the reference
        for match in target_matches:
            target_id = match.group(0)
            
            # Try to find source ID in surrounding context
            start = max(0, match.start() - 500)
            end = min(len(content), match.end() + 500)
            context = content[start:end]
            
            # Look for source artifact pattern
            source_pattern = patterns.get(source_type, r'[A-Z]+-[A-Z]+-[A-Z0-9]+-\d+')
            source_match = re.search(source_pattern, context)
            
            if source_match:
                source_id = source_match.group(0)
                
                # Determine confidence based on proximity
                distance = abs(source_match.start() - (match.start() - start))
                if distance < 100:
                    confidence = "high"
                elif distance < 300:
                    confidence = "medium"
                else:
                    confidence = "low"
                
                link = TraceabilityLink(
                    source_id=source_id,
                    source_type=source_type,
                    target_id=target_id,
                    target_type=target_type,
                    link_type="allocated_to",
                    rationale=f"Auto-extracted from {source_document}",
                    verified=False,
                    confidence=confidence,
                    source_document=source_document,
                )
                
                links.append(link)
        
        # Deduplicate links
        unique_links = {}
        for link in links:
            key = (link.source_id, link.target_id)
            if key not in unique_links:
                unique_links[key] = link
            else:
                # Keep higher confidence link
                if link.confidence == "high":
                    unique_links[key] = link
        
        return list(unique_links.values())
    
    # ========================================================================
    # Command: visualize
    # ========================================================================
    
    def visualize(self, source_type: str, target_type: str, format: str = "mermaid", 
                  output: str = None) -> str:
        """
        Generate traceability visualization.
        
        Args:
            source_type: Source artifact type or specific artifact ID
            target_type: Target artifact type
            format: Visualization format (mermaid, dot, svg, png)
            output: Output file path
        
        Returns:
            Visualization content as string
        """
        # Collect all relevant matrices
        all_matrices = []
        
        # Start from source_type and trace to target_type
        # This is a simplified version - full implementation would do graph traversal
        matrix_name = f"{source_type}_to_{target_type}"
        csv_path = self.evidence_dir / f"{matrix_name}.csv"
        
        if not csv_path.exists():
            raise FileNotFoundError(f"Matrix not found: {matrix_name}")
        
        matrix = self._read_csv(str(csv_path))
        
        # Generate visualization based on format
        if format == "mermaid":
            viz_content = self._generate_mermaid(matrix)
        elif format == "dot":
            viz_content = self._generate_dot(matrix)
        else:
            raise ValueError(f"Unsupported visualization format: {format}")
        
        # Write to file if output specified
        if output:
            with open(output, 'w') as f:
                f.write(viz_content)
            print(f"✓ Visualization written to: {output}")
        else:
            print(viz_content)
        
        return viz_content
    
    def _generate_mermaid(self, matrix: TraceabilityMatrix) -> str:
        """Generate Mermaid diagram."""
        lines = []
        
        lines.append("```mermaid")
        lines.append("graph LR")
        lines.append(f"  subgraph {matrix.source_type}")
        
        # Collect unique sources
        sources = set(link.source_id for link in matrix.links)
        for source in sorted(sources):
            lines.append(f"    {source.replace('-', '_')}[\"{source}\"]")
        
        lines.append("  end")
        lines.append(f"  subgraph {matrix.target_type}")
        
        # Collect unique targets
        targets = set(link.target_id for link in matrix.links if link.target_id)
        for target in sorted(targets):
            lines.append(f"    {target.replace('-', '_')}[\"{target}\"]")
        
        lines.append("  end")
        lines.append("")
        
        # Add links
        for link in matrix.links:
            if link.target_id:
                source_clean = link.source_id.replace('-', '_')
                target_clean = link.target_id.replace('-', '_')
                lines.append(f"  {source_clean} --> {target_clean}")
        
        lines.append("```")
        
        return "\n".join(lines)
    
    def _generate_dot(self, matrix: TraceabilityMatrix) -> str:
        """Generate GraphViz DOT format."""
        lines = []
        
        lines.append("digraph traceability {")
        lines.append("  rankdir=LR;")
        lines.append("  node [shape=box];")
        lines.append("")
        
        # Source subgraph
        lines.append(f"  subgraph cluster_source {{")
        lines.append(f"    label=\"{matrix.source_type}\";")
        
        sources = set(link.source_id for link in matrix.links)
        for source in sorted(sources):
            lines.append(f"    \"{source}\";")
        
        lines.append("  }")
        lines.append("")
        
        # Target subgraph
        lines.append(f"  subgraph cluster_target {{")
        lines.append(f"    label=\"{matrix.target_type}\";")
        
        targets = set(link.target_id for link in matrix.links if link.target_id)
        for target in sorted(targets):
            lines.append(f"    \"{target}\";")
        
        lines.append("  }")
        lines.append("")
        
        # Links
        for link in matrix.links:
            if link.target_id:
                lines.append(f"  \"{link.source_id}\" -> \"{link.target_id}\";")
        
        lines.append("}")
        
        return "\n".join(lines)
    
    # ========================================================================
    # Command: sync
    # ========================================================================
    
    def sync(self, matrix_name: str) -> TraceabilityMatrix:
        """
        Synchronize CSV, JSON, and Markdown formats.
        
        Args:
            matrix_name: Matrix name (or "all" for all matrices)
        
        Returns:
            TraceabilityMatrix (or None if "all")
        """
        if matrix_name == "all":
            # Sync all matrices
            matrices = list(self.evidence_dir.glob("*.csv"))
            
            for csv_path in matrices:
                name = csv_path.stem
                self._sync_single_matrix(name)
            
            print(f"✓ Synchronized {len(matrices)} matrices")
            return None
        
        else:
            # Sync single matrix
            return self._sync_single_matrix(matrix_name)
    
    def _sync_single_matrix(self, matrix_name: str) -> TraceabilityMatrix:
        """Synchronize single matrix across all formats."""
        csv_path = self.evidence_dir / f"{matrix_name}.csv"
        
        if not csv_path.exists():
            raise FileNotFoundError(f"Matrix not found: {matrix_name}")
        
        # Read CSV (primary source)
        matrix = self._read_csv(str(csv_path))
        
        # Update JSON index
        self._write_json(matrix)
        
        # Regenerate Markdown report
        self._write_markdown(matrix)
        
        print(f"✓ Synchronized {matrix_name}")
        print(f"  CSV:      {matrix.csv_path}")
        print(f"  JSON:     {matrix.json_path}")
        print(f"  Markdown: {matrix.markdown_path}")
        
        return matrix
    
    # ========================================================================
    # CSV/JSON/Markdown I/O
    # ========================================================================
    
    def _read_csv(self, csv_path: str) -> TraceabilityMatrix:
        """Read traceability matrix from CSV file."""
        matrix_name = Path(csv_path).stem
        links = []
        
        try:
            with open(csv_path, 'r') as f:
                reader = csv.DictReader(f)
                for row in reader:
                    link = TraceabilityLink(
                        source_id=row.get('source_id', ''),
                        source_type=row.get('source_type', ''),
                        target_id=row.get('target_id', ''),
                        target_type=row.get('target_type', ''),
                        link_type=row.get('link_type', 'allocated_to'),
                        rationale=row.get('rationale', ''),
                        verified=row.get('verified', 'false').lower() == 'true',
                        verified_by=row.get('verified_by', ''),
                        verified_date=row.get('verified_date', ''),
                        confidence=row.get('confidence', 'high'),
                        source_document=row.get('source_document', ''),
                    )
                    links.append(link)
        except FileNotFoundError:
            pass
        
        # Parse matrix name to get source/target types
        parts = matrix_name.split('_to_')
        source_type = parts[0] if len(parts) > 0 else "unknown"
        target_type = parts[1] if len(parts) > 1 else "unknown"
        
        matrix = TraceabilityMatrix(
            name=matrix_name,
            source_type=source_type,
            target_type=target_type,
            project=self.project,
            links=links,
            csv_path=csv_path,
        )
        
        # Set JSON and Markdown paths
        base_path = Path(csv_path).with_suffix('')
        matrix.json_path = str(base_path.with_suffix('.json'))
        matrix.markdown_path = str(base_path.with_suffix('.md'))
        
        return matrix
    
    def _write_csv(self, matrix: TraceabilityMatrix):
        """Write traceability matrix to CSV file."""
        fieldnames = [
            'source_id', 'source_type', 'target_id', 'target_type',
            'link_type', 'rationale', 'verified', 'verified_by', 'verified_date',
            'confidence', 'source_document',
        ]
        
        with open(matrix.csv_path, 'w', newline='') as f:
            writer = csv.DictWriter(f, fieldnames=fieldnames)
            writer.writeheader()
            
            for link in matrix.links:
                writer.writerow({
                    'source_id': link.source_id,
                    'source_type': link.source_type,
                    'target_id': link.target_id,
                    'target_type': link.target_type,
                    'link_type': link.link_type,
                    'rationale': link.rationale,
                    'verified': str(link.verified).lower(),
                    'verified_by': link.verified_by,
                    'verified_date': link.verified_date,
                    'confidence': link.confidence,
                    'source_document': link.source_document,
                })
    
    def _write_json(self, matrix: TraceabilityMatrix):
        """Write traceability matrix to JSON file (for queries)."""
        data = {
            'name': matrix.name,
            'source_type': matrix.source_type,
            'target_type': matrix.target_type,
            'project': matrix.project,
            'links': [asdict(link) for link in matrix.links],
            'coverage': matrix.coverage,
            'version': matrix.version,
            'created_date': matrix.created_date,
            'modified_date': matrix.modified_date,
        }
        
        with open(matrix.json_path, 'w') as f:
            json.dump(data, f, indent=2)
    
    def _write_markdown(self, matrix: TraceabilityMatrix):
        """Write traceability matrix to Markdown file (for embedding in documents)."""
        lines = []
        
        lines.append(f"# Traceability Matrix: {matrix.name}\n\n")
        lines.append(f"**Project**: {matrix.project}  \n")
        lines.append(f"**Source Type**: {matrix.source_type}  \n")
        lines.append(f"**Target Type**: {matrix.target_type}  \n")
        lines.append(f"**Version**: {matrix.version}  \n")
        lines.append(f"**Status**: {matrix.status}  \n")
        lines.append(f"\n---\n\n")
        
        if matrix.links:
            lines.append("| Source ID | Target ID | Link Type | Verified | Rationale |\n")
            lines.append("|-----------|-----------|-----------|----------|------------|\n")
            
            for link in matrix.links:
                verified_icon = "✓" if link.verified else "✗"
                lines.append(f"| {link.source_id} | {link.target_id} | {link.link_type} | {verified_icon} | {link.rationale} |\n")
        else:
            lines.append("*No traceability links defined yet.*\n")
        
        lines.append(f"\n---\n\n")
        lines.append(f"*Generated: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}*\n")
        
        with open(matrix.markdown_path, 'w') as f:
            f.writelines(lines)

# ============================================================================
# CLI Interface
# ============================================================================

def main():
    """Main CLI entry point."""
    parser = argparse.ArgumentParser(
        description="Traceability Manager for EN 50128 Projects",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
    # Create new traceability matrix
    %(prog)s create --from requirements --to architecture
    
    # Validate traceability for SIL 3
    %(prog)s validate --phase design --sil 3
    
    # Query forward traceability
    %(prog)s query --source SW-REQ-015 --direction forward
    
    # Check for traceability gaps
    %(prog)s check-gaps --phase design --sil 3
    
    # Generate traceability report
    %(prog)s report --from requirements --to architecture,design,tests --format markdown
    
    # Import traceability from CSV
    %(prog)s import --file legacy_traces.csv --type requirements_to_design
    
    # Export traceability to JSON
    %(prog)s export --matrix all --format json --output traceability_export.json
    
    # Auto-extract traceability from document
    %(prog)s extract --document docs/Software-Design-Specification.md --type design_to_requirements --merge
    
    # Generate visualization
    %(prog)s visualize --from requirements --to architecture --format mermaid
    
    # Synchronize all formats
    %(prog)s sync --matrix all
        """
    )
    
    parser.add_argument('--project', help='Project name (overrides LIFECYCLE_STATE.md)')
    parser.add_argument('--verbose', '-v', action='store_true', help='Verbose output')
    
    subparsers = parser.add_subparsers(dest='command', help='Commands')
    
    # create command
    create_parser = subparsers.add_parser('create', help='Create new traceability matrix')
    create_parser.add_argument('--from', dest='source', required=True, help='Source artifact type')
    create_parser.add_argument('--to', dest='target', required=True, help='Target artifact type')
    create_parser.add_argument('--output', help='Output path (default: evidence/traceability/)')
    
    # validate command
    validate_parser = subparsers.add_parser('validate', help='Validate traceability completeness')
    validate_parser.add_argument('--matrix', help='Specific matrix to validate')
    validate_parser.add_argument('--phase', help='Validate all matrices for lifecycle phase')
    validate_parser.add_argument('--sil', type=int, required=True, help='SIL level (0-4)')
    
    # query command
    query_parser = subparsers.add_parser('query', help='Query traceability links')
    query_parser.add_argument('--source', help='Source artifact ID')
    query_parser.add_argument('--target', help='Target artifact ID')
    query_parser.add_argument('--direction', choices=['forward', 'backward', 'both'], default='forward', help='Query direction')
    
    # check-gaps command
    gaps_parser = subparsers.add_parser('check-gaps', help='Detect traceability gaps')
    gaps_parser.add_argument('--phase', help='Lifecycle phase to check')
    gaps_parser.add_argument('--sil', type=int, required=True, help='SIL level (0-4)')
    
    # report command
    report_parser = subparsers.add_parser('report', help='Generate traceability report')
    report_parser.add_argument('--from', dest='source', required=True, help='Source artifact type')
    report_parser.add_argument('--to', dest='targets', required=True, help='Comma-separated target types')
    report_parser.add_argument('--format', choices=['markdown', 'csv', 'json', 'html'], default='markdown', help='Output format')
    report_parser.add_argument('--output', help='Output file path')
    
    # import command
    import_parser = subparsers.add_parser('import', help='Import traceability data')
    import_parser.add_argument('--file', dest='file', required=True, help='Input file path')
    import_parser.add_argument('--type', dest='matrix_type', required=True, help='Matrix type (e.g., requirements_to_architecture)')
    import_parser.add_argument('--format', choices=['csv', 'json', 'excel'], help='Input format (auto-detected if not specified)')
    
    # export command
    export_parser = subparsers.add_parser('export', help='Export traceability data')
    export_parser.add_argument('--matrix', required=True, help='Matrix name (or "all" for all matrices)')
    export_parser.add_argument('--format', choices=['csv', 'json', 'excel', 'markdown'], required=True, help='Output format')
    export_parser.add_argument('--output', required=True, help='Output file path')
    
    # extract command
    extract_parser = subparsers.add_parser('extract', help='Auto-extract traceability from documents')
    extract_parser.add_argument('--document', required=True, help='Document file path')
    extract_parser.add_argument('--type', dest='link_type', required=True, help='Link type (e.g., design_to_requirements)')
    extract_parser.add_argument('--merge', action='store_true', help='Merge with existing matrix')
    
    # visualize command
    visualize_parser = subparsers.add_parser('visualize', help='Generate traceability visualization')
    visualize_parser.add_argument('--from', dest='source', required=True, help='Source artifact type')
    visualize_parser.add_argument('--to', dest='target', required=True, help='Target artifact type')
    visualize_parser.add_argument('--format', choices=['mermaid', 'dot', 'svg', 'png'], default='mermaid', help='Visualization format')
    visualize_parser.add_argument('--output', help='Output file path')
    
    # sync command
    sync_parser = subparsers.add_parser('sync', help='Synchronize CSV/JSON/Markdown formats')
    sync_parser.add_argument('--matrix', required=True, help='Matrix name (or "all" for all matrices)')
    
    args = parser.parse_args()
    
    if not args.command:
        parser.print_help()
        return 1
    
    # Initialize manager
    mgr = TraceabilityManager(project=args.project)
    
    # Execute command
    try:
        if args.command == 'create':
            mgr.create_matrix(args.source, args.target, args.output)
        
        elif args.command == 'validate':
            result = mgr.validate(args.matrix, args.phase, args.sil)
            return 0 if result['overall_pass'] else 1
        
        elif args.command == 'query':
            mgr.query(args.source, args.target, args.direction)
        
        elif args.command == 'check-gaps':
            mgr.check_gaps(args.phase, args.sil)
        
        elif args.command == 'report':
            targets = args.targets.split(',')
            mgr.report(args.source, targets, args.format, args.output)
        
        elif args.command == 'import':
            mgr.import_data(args.file, args.matrix_type, args.format)
        
        elif args.command == 'export':
            mgr.export_data(args.matrix, args.format, args.output)
        
        elif args.command == 'extract':
            mgr.extract(args.document, args.link_type, args.merge)
        
        elif args.command == 'visualize':
            mgr.visualize(args.source, args.target, args.format, args.output)
        
        elif args.command == 'sync':
            mgr.sync(args.matrix)
        
        return 0
    
    except Exception as e:
        print(f"✗ Error: {e}", file=sys.stderr)
        if args.verbose:
            import traceback
            traceback.print_exc()
        return 1

if __name__ == '__main__':
    sys.exit(main())
