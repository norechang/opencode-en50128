#!/usr/bin/env python3
"""
validate_sas_sds_template.py - EN 50128 SAS/SDS Template Validator

PURPOSE:
    Validate Software Architecture Specification (SAS) and Software Design 
    Specification (SDS) documents against EN 50128 templates per EN 50128:2011 
    Section 7.3 (SAS) and Section 7.4 (SDS).

USAGE:
    python3 validate_sas_sds_template.py <doc.md> --type <sas|sds> --sil <0-4>

VALIDATION CHECKS:
    1. Document ID format: DOC-DES-YYYY-NNN or DOC-DES-SAS/SDS-NNN
    2. STANDARD HEADER: Required fields
    3. DOCUMENT CONTROL: Version history table
    4. APPROVALS: SIL-specific approvers
    5. Required sections (document type specific)
    6. Architecture diagrams presence (SAS only)
    7. Modular approach documented (SIL 2+ MANDATORY)
    8. Interface specifications present
    9. Traceability to SRS
    10. Design constraints documented (MISRA C, static allocation, complexity limits)

OUTPUT:
    - Validation report (PASS/FAIL)
    - List of issues (missing sections, incorrect format, etc.)
    - Compliance percentage

AUTHOR: OpenCode Architecture Transformation Phase 3
DATE: 2026-03-15
VERSION: 1.0
REFERENCE: EN 50128:2011 Section 7.3 (SAS), Section 7.4 (SDS), Table A.3, A.4
"""

import sys
import re
import argparse
from pathlib import Path
from typing import List, Tuple, Dict

class ValidationIssue:
    """Represents a validation issue found in the document"""
    def __init__(self, severity: str, section: str, message: str):
        self.severity = severity  # ERROR, WARNING, INFO
        self.section = section
        self.message = message
    
    def __str__(self):
        return f"[{self.severity}] {self.section}: {self.message}"

class SASSDSValidator:
    """Validator for EN 50128 Software Architecture/Design Specification"""
    
    def __init__(self, doc_path: str, doc_type: str, sil_level: int):
        self.doc_path = Path(doc_path)
        self.doc_type = doc_type.lower()  # 'sas' or 'sds'
        self.sil_level = sil_level
        self.issues: List[ValidationIssue] = []
        self.content = ""
        self.checks_passed = 0
        self.checks_total = 0
        
        # Required sections per EN 50128
        if self.doc_type == 'sas':
            self.required_sections = [
                "STANDARD HEADER",
                "DOCUMENT CONTROL",
                "APPROVALS",
                "INTRODUCTION",
                "SYSTEM OVERVIEW",
                "ARCHITECTURAL DESIGN",
                "MODULE DECOMPOSITION",
                "INTERFACE DESIGN",
                "DATA ARCHITECTURE",
                "TRACEABILITY"
            ]
        else:  # sds
            self.required_sections = [
                "STANDARD HEADER",
                "DOCUMENT CONTROL",
                "APPROVALS",
                "INTRODUCTION",
                "MODULE DESIGN",
                "INTERFACE SPECIFICATIONS",
                "DATA STRUCTURES",
                "ALGORITHMS",
                "ERROR HANDLING",
                "TRACEABILITY"
            ]
    
    def load_document(self) -> bool:
        """Load the SAS/SDS document"""
        try:
            with open(self.doc_path, 'r', encoding='utf-8') as f:
                self.content = f.read()
            return True
        except Exception as e:
            self.issues.append(ValidationIssue("ERROR", "File I/O", 
                f"Failed to load document: {e}"))
            return False
    
    def check_document_id(self) -> bool:
        """Check Document ID format: DOC-DES-YYYY-NNN or DOC-DES-SAS/SDS-NNN"""
        self.checks_total += 1
        pattern = r'\|\s*\*\*Document ID\*\*\s*\|\s*(\S+)\s*\|'
        match = re.search(pattern, self.content)
        
        if not match:
            self.issues.append(ValidationIssue("ERROR", "STANDARD HEADER",
                "Document ID field not found in STANDARD HEADER table"))
            return False
        
        doc_id = match.group(1)
        
        # Check format: DOC-DES-YYYY-NNN or DOC-DES-SAS/SDS-NNN
        doc_type_upper = self.doc_type.upper()
        if not re.match(rf'^DOC-DES-({doc_type_upper}-\d{{3}}|\d{{4}}-\d{{3}})$', doc_id):
            self.issues.append(ValidationIssue("ERROR", "STANDARD HEADER",
                f"Document ID '{doc_id}' does not match format DOC-DES-YYYY-NNN or DOC-DES-{doc_type_upper}-NNN"))
            return False
        
        self.checks_passed += 1
        return True
    
    def check_standard_header(self) -> bool:
        """Check STANDARD HEADER table has required fields"""
        self.checks_total += 1
        required_fields = [
            "Document ID",
            "Version",
            "Date",
            "Project",
            "SIL Level",
            "Author",
            "Status"
        ]
        
        missing_fields = []
        for field in required_fields:
            pattern = rf'\|\s*\*\*{field}\*\*\s*\|'
            if not re.search(pattern, self.content):
                missing_fields.append(field)
        
        if missing_fields:
            self.issues.append(ValidationIssue("ERROR", "STANDARD HEADER",
                f"Missing required fields: {', '.join(missing_fields)}"))
            return False
        
        self.checks_passed += 1
        return True
    
    def check_document_control(self) -> bool:
        """Check DOCUMENT CONTROL table exists and has required columns"""
        self.checks_total += 1
        
        if "## DOCUMENT CONTROL" not in self.content:
            self.issues.append(ValidationIssue("ERROR", "DOCUMENT CONTROL",
                "DOCUMENT CONTROL section not found"))
            return False
        
        required_columns = ["Version", "Date", "Author", "Changes", "Approved By"]
        section_start = self.content.find("## DOCUMENT CONTROL")
        section_end = self.content.find("##", section_start + 1)
        section_content = self.content[section_start:section_end if section_end != -1 else None]
        
        missing_columns = []
        for column in required_columns:
            if column not in section_content:
                missing_columns.append(column)
        
        if missing_columns:
            self.issues.append(ValidationIssue("ERROR", "DOCUMENT CONTROL",
                f"Missing required columns: {', '.join(missing_columns)}"))
            return False
        
        self.checks_passed += 1
        return True
    
    def check_approvals(self) -> bool:
        """Check APPROVALS table has SIL-specific approvers"""
        self.checks_total += 1
        
        if "## APPROVALS" not in self.content:
            self.issues.append(ValidationIssue("ERROR", "APPROVALS",
                "APPROVALS section not found"))
            return False
        
        section_start = self.content.find("## APPROVALS")
        section_end = self.content.find("##", section_start + 1)
        section_content = self.content[section_start:section_end if section_end != -1 else None]
        
        # Required approvers based on SIL level
        required_approvers = [
            "Author",
            "Technical Reviewer",
            "QA Manager",
            "Project Manager"
        ]
        
        if self.sil_level >= 2:
            required_approvers.append("Safety Manager")
        
        if self.sil_level >= 3:
            required_approvers.extend([
                "Independent Verifier",
                "Independent Validator",
                "Assessor"
            ])
        
        missing_approvers = []
        for approver in required_approvers:
            pattern = rf'\|\s*\*\*{approver}\*\*'
            if not re.search(pattern, section_content):
                missing_approvers.append(approver)
        
        if missing_approvers:
            self.issues.append(ValidationIssue("ERROR", "APPROVALS",
                f"Missing required approvers for SIL {self.sil_level}: {', '.join(missing_approvers)}"))
            return False
        
        self.checks_passed += 1
        return True
    
    def check_required_sections(self) -> bool:
        """Check all required sections are present"""
        self.checks_total += 1
        missing_sections = []
        
        for section in self.required_sections:
            # Check for both "## SECTION" and "##SECTION" and numbered sections
            section_patterns = [
                f"## {section}",
                f"##{section}",
                rf"##\s*\d+\.\s*{section}"
            ]
            
            found = any(
                re.search(pattern, self.content, re.IGNORECASE) 
                for pattern in section_patterns
            )
            
            if not found:
                missing_sections.append(section)
        
        if missing_sections:
            self.issues.append(ValidationIssue("ERROR", "Structure",
                f"Missing required sections: {', '.join(missing_sections)}"))
            return False
        
        self.checks_passed += 1
        return True
    
    def check_architecture_diagrams(self) -> bool:
        """Check for architecture diagrams (SAS only)"""
        if self.doc_type != 'sas':
            return True  # Not applicable for SDS
        
        self.checks_total += 1
        
        # Look for diagram indicators (ASCII art, mermaid, plantuml)
        has_ascii_diagram = bool(re.search(r'┌|│|└|├|─', self.content))
        has_mermaid = bool(re.search(r'```mermaid', self.content, re.IGNORECASE))
        has_plantuml = bool(re.search(r'```plantuml', self.content, re.IGNORECASE))
        has_diagram_ref = bool(re.search(r'(diagram|figure|architecture)', self.content, re.IGNORECASE))
        
        if not (has_ascii_diagram or has_mermaid or has_plantuml):
            if has_diagram_ref:
                self.issues.append(ValidationIssue("WARNING", "Architecture Diagrams",
                    "Diagram references found but no actual diagrams detected. "
                    "SAS should include architecture diagrams (ASCII art, mermaid, or plantuml)."))
            else:
                self.issues.append(ValidationIssue("WARNING", "Architecture Diagrams",
                    "No architecture diagrams found. SAS should include visual representations "
                    "of the architecture (EN 50128 Section 7.3)."))
        
        self.checks_passed += 1
        return True
    
    def check_modular_approach(self) -> bool:
        """Check modular approach is documented (MANDATORY SIL 2+)"""
        self.checks_total += 1
        
        # Look for module-related keywords
        has_modules = bool(re.search(r'\bmodule\b', self.content, re.IGNORECASE))
        has_components = bool(re.search(r'\bcomponent\b', self.content, re.IGNORECASE))
        has_decomposition = bool(re.search(r'\bdecomposition\b', self.content, re.IGNORECASE))
        
        if not (has_modules or has_components or has_decomposition):
            severity = "ERROR" if self.sil_level >= 2 else "WARNING"
            self.issues.append(ValidationIssue(severity, "Modular Approach",
                f"No evidence of modular approach found. "
                f"{'MANDATORY' if self.sil_level >= 2 else 'Recommended'} per EN 50128 Table A.3 "
                f"for SIL {self.sil_level}."))
            if self.sil_level >= 2:
                return False
        
        self.checks_passed += 1
        return True
    
    def check_interface_specifications(self) -> bool:
        """Check interface specifications are present"""
        self.checks_total += 1
        
        # Look for interface section
        interface_pattern = r'##\s*\d*\.?\s*(INTERFACE|API)'
        has_interface_section = bool(re.search(interface_pattern, self.content, re.IGNORECASE))
        
        if not has_interface_section:
            self.issues.append(ValidationIssue("WARNING", "Interface Specifications",
                "No INTERFACE or API section found. Design should document module interfaces "
                "(EN 50128 Section 7.3/7.4)."))
        
        self.checks_passed += 1
        return True
    
    def check_traceability(self) -> bool:
        """Check traceability to SRS"""
        self.checks_total += 1
        
        # Find TRACEABILITY section
        traceability_pattern = r'##\s*\d*\.?\s*TRACEABILITY'
        match = re.search(traceability_pattern, self.content, re.IGNORECASE)
        
        if not match:
            self.issues.append(ValidationIssue("ERROR", "TRACEABILITY",
                "TRACEABILITY section not found"))
            return False
        
        section_start = match.end()
        section_end = self.content.find("##", section_start + 1)
        section_content = self.content[section_start:section_end if section_end != -1 else None]
        
        # Check for SRS references
        has_srs_ref = bool(re.search(r'SRS|Software Requirements|REQ-', section_content, re.IGNORECASE))
        
        if not has_srs_ref:
            self.issues.append(ValidationIssue("WARNING", "TRACEABILITY",
                "No references to SRS or requirements found. "
                f"{self.doc_type.upper()} should trace to SRS requirements."))
        
        self.checks_passed += 1
        return True
    
    def check_design_constraints(self) -> bool:
        """Check design constraints are documented (MISRA C, static allocation, complexity)"""
        self.checks_total += 1
        
        # Look for SIL-specific constraints
        has_misra = bool(re.search(r'MISRA', self.content, re.IGNORECASE))
        has_static_alloc = bool(re.search(r'static\s+(memory\s+)?allocation', self.content, re.IGNORECASE))
        has_complexity = bool(re.search(r'(cyclomatic\s+)?complexity|CCN', self.content, re.IGNORECASE))
        has_defensive = bool(re.search(r'defensive\s+programming', self.content, re.IGNORECASE))
        
        warnings = []
        
        if self.sil_level >= 2:
            if not has_misra:
                warnings.append("MISRA C:2012 compliance (MANDATORY SIL 2+)")
            if not has_static_alloc:
                warnings.append("Static memory allocation (MANDATORY SIL 2+)")
        
        if self.sil_level >= 3:
            if not has_complexity:
                warnings.append("Complexity limits (CCN ≤ 10 for SIL 3-4)")
            if not has_defensive:
                warnings.append("Defensive programming (HIGHLY RECOMMENDED SIL 3-4)")
        
        if warnings:
            self.issues.append(ValidationIssue("WARNING", "Design Constraints",
                f"Missing design constraints documentation: {', '.join(warnings)}"))
        
        self.checks_passed += 1
        return True
    
    def validate(self) -> bool:
        """Run all validation checks"""
        if not self.load_document():
            return False
        
        self.check_document_id()
        self.check_standard_header()
        self.check_document_control()
        self.check_approvals()
        self.check_required_sections()
        self.check_architecture_diagrams()
        self.check_modular_approach()
        self.check_interface_specifications()
        self.check_traceability()
        self.check_design_constraints()
        
        return len([i for i in self.issues if i.severity == "ERROR"]) == 0
    
    def generate_report(self) -> str:
        """Generate validation report"""
        errors = [i for i in self.issues if i.severity == "ERROR"]
        warnings = [i for i in self.issues if i.severity == "WARNING"]
        
        compliance = (self.checks_passed / self.checks_total * 100) if self.checks_total > 0 else 0
        overall_status = "PASS" if len(errors) == 0 else "FAIL"
        
        doc_type_name = "Software Architecture Specification" if self.doc_type == 'sas' else "Software Design Specification"
        en_section = "7.3" if self.doc_type == 'sas' else "7.4"
        table = "A.3" if self.doc_type == 'sas' else "A.4"
        
        report = f"""
EN 50128 {doc_type_name} ({self.doc_type.upper()}) Validation Report
{'=' * (60 + len(doc_type_name))}

Document: {self.doc_path.name}
Document Type: {self.doc_type.upper()}
SIL Level: {self.sil_level}
Date: {Path(__file__).stat().st_mtime}

OVERALL STATUS: {overall_status}

Checks Passed: {self.checks_passed}/{self.checks_total}
Compliance: {compliance:.1f}%

Errors: {len(errors)}
Warnings: {len(warnings)}

"""
        
        if errors:
            report += "ERRORS:\n"
            for issue in errors:
                report += f"  {issue}\n"
            report += "\n"
        
        if warnings:
            report += "WARNINGS:\n"
            for issue in warnings:
                report += f"  {issue}\n"
            report += "\n"
        
        if not errors and not warnings:
            report += "✓ All validation checks passed!\n\n"
        
        report += f"""
Validation Checks Performed:
1. Document ID format (DOC-DES-YYYY-NNN or DOC-DES-{self.doc_type.upper()}-NNN)
2. STANDARD HEADER with required fields
3. DOCUMENT CONTROL table with version history
4. APPROVALS table with SIL-specific approvers
5. Required sections ({', '.join(self.required_sections[:3])}...)
"""
        
        if self.doc_type == 'sas':
            report += "6. Architecture diagrams presence (ASCII art, mermaid, plantuml)\n"
        
        report += f"""7. Modular approach documented ({'MANDATORY' if self.sil_level >= 2 else 'recommended'} SIL {self.sil_level})
8. Interface specifications present
9. Traceability to SRS
10. Design constraints (MISRA C, static allocation, complexity limits)

Reference: EN 50128:2011 Section {en_section}, Table {table}
"""
        
        return report

def main():
    parser = argparse.ArgumentParser(
        description="Validate EN 50128 Software Architecture/Design Specification documents",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python3 validate_sas_sds_template.py docs/SAS.md --type sas --sil 3
  python3 validate_sas_sds_template.py docs/SDS.md --type sds --sil 3

Exit Codes:
  0 - Validation passed
  1 - Validation failed (errors found)

Reference:
  EN 50128:2011 Section 7.3 (Software Architecture Specification)
  EN 50128:2011 Section 7.4 (Software Design Specification)
  Table A.3 (Architecture Techniques)
  Table A.4 (Design and Implementation Techniques)
        """
    )
    
    parser.add_argument("doc_file", help="Path to SAS/SDS document (.md file)")
    parser.add_argument("--type", required=True, choices=['sas', 'sds'],
                        help="Document type: sas (architecture) or sds (design)")
    parser.add_argument("--sil", type=int, required=True, choices=[0, 1, 2, 3, 4],
                        help="SIL level (0-4)")
    
    args = parser.parse_args()
    
    # Check file exists
    if not Path(args.doc_file).exists():
        print(f"ERROR: File not found: {args.doc_file}", file=sys.stderr)
        return 1
    
    # Create validator and run validation
    validator = SASSDSValidator(args.doc_file, args.type, args.sil)
    is_valid = validator.validate()
    
    # Print report
    print(validator.generate_report())
    
    # Return exit code
    return 0 if is_valid else 1

if __name__ == "__main__":
    sys.exit(main())
