"""
Deliverable definition loader and parser.
Loads YAML deliverable definitions and provides query interface.

Usage:
    from tools.deliverables.loader import DeliverableLoader
    
    loader = DeliverableLoader(Path("deliverables"))
    srs = loader.load_deliverable("DOC-006-SRS")
    
    # Get evidence for SIL 3
    evidence = loader.get_required_evidence("DOC-006-SRS", sil=3)
"""

import yaml
from pathlib import Path
from typing import Dict, List, Optional, Any
from dataclasses import dataclass, field


@dataclass
class EvidenceRequirement:
    """Evidence requirement definition."""
    evidence_id: str
    description: str
    mandatory_sil: int
    source: str
    format: str
    storage_path: str
    tool: Optional[str] = None
    automation_level: Optional[str] = None
    collect_on_agent_action: Optional[str] = None
    verification_criteria: List[str] = field(default_factory=list)
    generation_command: Optional[str] = None
    linked_deliverables: List[str] = field(default_factory=list)
    notes: Optional[str] = None


@dataclass
class DeliverableDefinition:
    """Complete deliverable definition."""
    deliverable_id: str
    number: int
    name: str
    abbreviation: str
    phase: str
    standard_section: str
    written_by: str
    first_check: str
    second_check: str
    template_path: str
    template_exists: bool
    sil_requirements: Dict[str, Any]
    required_sections: List[Dict[str, Any]]
    evidence_requirements: List[EvidenceRequirement]
    verification_criteria: Dict[str, List[str]]
    depends_on: List[Dict[str, str]]
    feeds_into: List[Dict[str, str]]
    baseline: Dict[str, Any]
    notes: Optional[str] = None
    tags: List[str] = field(default_factory=list)


class DeliverableLoader:
    """Load and manage deliverable definitions."""
    
    def __init__(self, deliverables_dir: Path):
        """
        Initialize loader.
        
        Args:
            deliverables_dir: Path to deliverables/ directory
        """
        self.deliverables_dir = Path(deliverables_dir)
        self._cache: Dict[str, DeliverableDefinition] = {}
    
    def load_deliverable(self, deliverable_id: str) -> DeliverableDefinition:
        """
        Load a deliverable definition by ID.
        
        Args:
            deliverable_id: Deliverable ID (e.g., "DOC-006-SRS")
        
        Returns:
            DeliverableDefinition object
        
        Raises:
            FileNotFoundError: If deliverable definition not found
            ValueError: If YAML is invalid
        """
        if deliverable_id in self._cache:
            return self._cache[deliverable_id]
        
        # Find deliverable file (search all phase directories)
        deliverable_file = self._find_deliverable_file(deliverable_id)
        if not deliverable_file:
            raise FileNotFoundError(
                f"Deliverable {deliverable_id} not found in {self.deliverables_dir}"
            )
        
        # Load YAML
        try:
            with open(deliverable_file, 'r') as f:
                data = yaml.safe_load(f)
        except Exception as e:
            raise ValueError(f"Failed to parse {deliverable_file}: {e}")
        
        # Parse evidence requirements
        evidence_reqs = []
        for ev_data in data.get('evidence_requirements', []):
            evidence_reqs.append(EvidenceRequirement(
                evidence_id=ev_data['evidence_id'],
                description=ev_data['description'],
                mandatory_sil=ev_data['mandatory_sil'],
                source=ev_data['source'],
                format=ev_data['format'],
                storage_path=ev_data.get('storage_path', ''),
                tool=ev_data.get('tool'),
                automation_level=ev_data.get('automation_level'),
                collect_on_agent_action=ev_data.get('collect_on_agent_action'),
                verification_criteria=ev_data.get('verification_criteria', []),
                generation_command=ev_data.get('generation_command'),
                linked_deliverables=ev_data.get('linked_deliverables', []),
                notes=ev_data.get('notes')
            ))
        
        # Create deliverable object
        deliverable = DeliverableDefinition(
            deliverable_id=data['deliverable_id'],
            number=data['number'],
            name=data['name'],
            abbreviation=data['abbreviation'],
            phase=data['phase'],
            standard_section=data['standard_section'],
            written_by=data['written_by'],
            first_check=data['first_check'],
            second_check=data['second_check'],
            template_path=data['template_path'],
            template_exists=data.get('template_exists', False),
            sil_requirements=data['sil_requirements'],
            required_sections=data.get('required_sections', []),
            evidence_requirements=evidence_reqs,
            verification_criteria=data.get('verification_criteria', {}),
            depends_on=data.get('depends_on', []),
            feeds_into=data.get('feeds_into', []),
            baseline=data.get('baseline', {}),
            notes=data.get('notes'),
            tags=data.get('tags', [])
        )
        
        self._cache[deliverable_id] = deliverable
        return deliverable
    
    def _find_deliverable_file(self, deliverable_id: str) -> Optional[Path]:
        """
        Find deliverable YAML file by ID.
        
        Searches all phase directories for a file containing this deliverable_id.
        
        Args:
            deliverable_id: Deliverable ID (e.g., "DOC-006-SRS")
        
        Returns:
            Path to YAML file, or None if not found
        """
        # Search all phase directories
        for phase_dir in self.deliverables_dir.iterdir():
            if phase_dir.is_dir() and phase_dir.name != 'schema':
                # Search YAML files in this phase directory
                for yaml_file in phase_dir.glob("*.yaml"):
                    # Quick check: read first few lines for deliverable_id
                    try:
                        with open(yaml_file, 'r') as f:
                            content = f.read(500)  # Read first 500 chars
                            if f'deliverable_id: "{deliverable_id}"' in content:
                                return yaml_file
                    except Exception:
                        continue
        return None
    
    def get_required_evidence(self, deliverable_id: str, sil: int) -> List[EvidenceRequirement]:
        """
        Get evidence requirements for a deliverable at given SIL level.
        
        Args:
            deliverable_id: Deliverable ID
            sil: SIL level (0-4)
        
        Returns:
            List of evidence requirements mandatory for this SIL
        """
        deliverable = self.load_deliverable(deliverable_id)
        return [
            ev for ev in deliverable.evidence_requirements
            if ev.mandatory_sil <= sil
        ]
    
    def get_dependencies(self, deliverable_id: str) -> List[str]:
        """
        Get list of deliverable IDs this deliverable depends on.
        
        Args:
            deliverable_id: Deliverable ID
        
        Returns:
            List of deliverable IDs (e.g., ["DOC-001-SQAP", "DOC-003-SCMP"])
        """
        deliverable = self.load_deliverable(deliverable_id)
        return [dep['deliverable_id'] for dep in deliverable.depends_on]
    
    def get_dependents(self, deliverable_id: str) -> List[str]:
        """
        Get list of deliverable IDs that depend on this one.
        
        Args:
            deliverable_id: Deliverable ID
        
        Returns:
            List of deliverable IDs that feed from this one
        """
        deliverable = self.load_deliverable(deliverable_id)
        return [dep['deliverable_id'] for dep in deliverable.feeds_into]
    
    def get_sil_requirements(self, deliverable_id: str, sil: int) -> Dict[str, Any]:
        """
        Get SIL-specific requirements for a deliverable.
        
        Args:
            deliverable_id: Deliverable ID
            sil: SIL level (0-4)
        
        Returns:
            Dictionary of SIL requirements
        """
        deliverable = self.load_deliverable(deliverable_id)
        return deliverable.sil_requirements.get(f'sil_{sil}', {})
    
    def is_mandatory(self, deliverable_id: str, sil: int) -> bool:
        """
        Check if a deliverable is mandatory for given SIL level.
        
        Args:
            deliverable_id: Deliverable ID
            sil: SIL level (0-4)
        
        Returns:
            True if mandatory, False otherwise
        """
        sil_req = self.get_sil_requirements(deliverable_id, sil)
        return sil_req.get('mandatory', False)
    
    def list_deliverables_by_phase(self, phase: str) -> List[str]:
        """
        List all deliverable IDs in a phase.
        
        Args:
            phase: Phase name (e.g., "requirements", "architecture")
        
        Returns:
            List of deliverable IDs in this phase
        """
        phase_dir = self.deliverables_dir / phase
        if not phase_dir.exists():
            return []
        
        deliverable_ids = []
        for yaml_file in phase_dir.glob("*.yaml"):
            try:
                with open(yaml_file, 'r') as f:
                    data = yaml.safe_load(f)
                    deliverable_ids.append(data['deliverable_id'])
            except Exception:
                continue
        
        return sorted(deliverable_ids)
    
    def get_verification_criteria(self, deliverable_id: str) -> Dict[str, List[str]]:
        """
        Get verification criteria for a deliverable.
        
        Args:
            deliverable_id: Deliverable ID
        
        Returns:
            Dictionary with completeness, correctness, consistency checks
        """
        deliverable = self.load_deliverable(deliverable_id)
        return deliverable.verification_criteria


# Convenience functions for common queries
def load_srs(deliverables_dir: Path) -> DeliverableDefinition:
    """Load Software Requirements Specification."""
    loader = DeliverableLoader(deliverables_dir)
    return loader.load_deliverable("DOC-006-SRS")


def get_sil3_evidence(deliverable_id: str, deliverables_dir: Path) -> List[EvidenceRequirement]:
    """Get SIL 3 evidence requirements for a deliverable."""
    loader = DeliverableLoader(deliverables_dir)
    return loader.get_required_evidence(deliverable_id, sil=3)
