#!/usr/bin/env python3
"""
validate_srs_template.py - EN 50128 SRS Template Validator

PURPOSE:
    Validate Software Requirements Specification (SRS) documents against EN 50128
    templates per EN 50128:2011 Section 7.2, Table A.2.

USAGE:
    python3 validate_srs_template.py <srs.md> --sil <0-4>

VALIDATION CHECKS:
    1. Document ID format: DOC-REQ-YYYY-NNN
    2. STANDARD HEADER: Required fields (Document ID, Version, Date, etc.)
    3. DOCUMENT CONTROL: Version history table with required columns
    4. APPROVALS: SIL-specific approvers
       - SIL 0-2: Author, Technical Reviewer, QA Manager, Project Manager (4)
       - SIL 2+: + Safety Manager (5)
       - SIL 3-4: + Independent Verifier, Validator, Assessor (8)
    5. Required sections: Introduction, General Description, Functional Requirements, etc.
    6. Requirements format: SHALL/SHOULD/MAY keywords used correctly
    7. Requirements ID format: REQ-XXX-NNN or SWREQ-NNN
    8. Traceability: References to System Requirements, Hazard Log

OUTPUT:
    - Validation report (PASS/FAIL)
    - List of issues (missing sections, incorrect format, etc.)
    - Compliance percentage

AUTHOR: OpenCode Architecture Transformation Phase 3
DATE: 2026-03-15
VERSION: 1.0
REFERENCE: EN 50128:2011 Section 7.2, Table A.2
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

class SRSValidator:
    """Validator for EN 50128 Software Requirements Specification"""
    
    def __init__(self, doc_path: str, sil_level: int):
        self.doc_path = Path(doc_path)
        self.sil_level = sil_level
        self.issues: List[ValidationIssue] = []
        self.content = ""
        self.checks_passed = 0
        self.checks_total = 0
        
        # Required sections per EN 50128 Section 7.2
        self.required_sections = [
            "STANDARD HEADER",
            "DOCUMENT CONTROL",
            "APPROVALS",
            "INTRODUCTION",
            "GENERAL DESCRIPTION",
            "FUNCTIONAL REQUIREMENTS",
            "PERFORMANCE REQUIREMENTS",
            "INTERFACE REQUIREMENTS",
            "SAFETY REQUIREMENTS",
            "TRACEABILITY"
        ]
    
    def load_document(self) -> bool:
        """Load the SRS document"""
        try:
            with open(self.doc_path, 'r', encoding='utf-8') as f:
                self.content = f.read()
            return True
        except Exception as e:
            self.issues.append(ValidationIssue("ERROR", "File I/O", 
                f"Failed to load document: {e}"))
            return False
    
    def check_document_id(self) -> bool:
        """Check Document ID format: DOC-REQ-YYYY-NNN"""
        self.checks_total += 1
        pattern = r'\|\s*\*\*Document ID\*\*\s*\|\s*(\S+)\s*\|'
        match = re.search(pattern, self.content)
        
        if not match:
            self.issues.append(ValidationIssue("ERROR", "STANDARD HEADER",
                "Document ID field not found in STANDARD HEADER table"))
            return False
        
        doc_id = match.group(1)
        
        # Check format: DOC-REQ-YYYY-NNN or DOC-REQ-SRS-NNN
        if not re.match(r'^DOC-REQ-(SRS-\d{3}|\d{4}-\d{3})$', doc_id):
            self.issues.append(ValidationIssue("ERROR", "STANDARD HEADER",
                f"Document ID '{doc_id}' does not match format DOC-REQ-YYYY-NNN or DOC-REQ-SRS-NNN"))
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
        
        # Check for DOCUMENT CONTROL section
        if "## DOCUMENT CONTROL" not in self.content:
            self.issues.append(ValidationIssue("ERROR", "DOCUMENT CONTROL",
                "DOCUMENT CONTROL section not found"))
            return False
        
        # Check for required columns
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
        
        # Check for APPROVALS section
        if "## APPROVALS" not in self.content:
            self.issues.append(ValidationIssue("ERROR", "APPROVALS",
                "APPROVALS section not found"))
            return False
        
        # Extract APPROVALS section
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
            # Check for approver role in table
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
            # Check for both "## SECTION" and "##SECTION" formats
            if f"## {section}" not in self.content.upper() and f"##{section}" not in self.content.upper():
                missing_sections.append(section)
        
        if missing_sections:
            self.issues.append(ValidationIssue("ERROR", "Structure",
                f"Missing required sections: {', '.join(missing_sections)}"))
            return False
        
        self.checks_passed += 1
        return True
    
    def check_requirements_format(self) -> bool:
        """Check requirements use SHALL/SHOULD/MAY keywords"""
        self.checks_total += 1
        
        # Extract FUNCTIONAL REQUIREMENTS section
        func_req_pattern = r'##\s*\d+\.\s*FUNCTIONAL REQUIREMENTS'
        match = re.search(func_req_pattern, self.content, re.IGNORECASE)
        
        if not match:
            self.issues.append(ValidationIssue("WARNING", "FUNCTIONAL REQUIREMENTS",
                "FUNCTIONAL REQUIREMENTS section not found for requirements format check"))
            return True  # Don't fail, just warn
        
        section_start = match.end()
        section_end = self.content.find("##", section_start + 1)
        section_content = self.content[section_start:section_end if section_end != -1 else None]
        
        # Check for SHALL/SHOULD/MAY keywords
        has_shall = bool(re.search(r'\bSHALL\b', section_content))
        has_should = bool(re.search(r'\bSHOULD\b', section_content))
        has_may = bool(re.search(r'\bMAY\b', section_content))
        
        if not (has_shall or has_should or has_may):
            self.issues.append(ValidationIssue("WARNING", "FUNCTIONAL REQUIREMENTS",
                "No SHALL/SHOULD/MAY keywords found in requirements. "
                "Requirements should use these keywords per EN 50128."))
        
        self.checks_passed += 1
        return True
    
    def check_requirement_ids(self) -> bool:
        """Check requirement ID format: REQ-XXX-NNN or SWREQ-NNN"""
        self.checks_total += 1
        
        # Find all requirement IDs in the document
        req_id_pattern = r'\b(REQ-[A-Z]+-\d{3}|SWREQ-\d{3})\b'
        req_ids = re.findall(req_id_pattern, self.content)
        
        if not req_ids:
            self.issues.append(ValidationIssue("WARNING", "Requirements IDs",
                "No requirement IDs found in format REQ-XXX-NNN or SWREQ-NNN. "
                "Each requirement should have a unique ID."))
            return True  # Don't fail, just warn
        
        # Check for duplicate IDs
        unique_ids = set(req_ids)
        if len(req_ids) != len(unique_ids):
            duplicates = [id for id in unique_ids if req_ids.count(id) > 1]
            self.issues.append(ValidationIssue("ERROR", "Requirements IDs",
                f"Duplicate requirement IDs found: {', '.join(duplicates)}"))
            return False
        
        self.checks_passed += 1
        return True
    
    def check_traceability(self) -> bool:
        """Check traceability section references system requirements"""
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
        
        # Check for traceability references
        has_sys_req = bool(re.search(r'System Requirement|SYSREQ', section_content, re.IGNORECASE))
        has_hazard = bool(re.search(r'Hazard|HAZLOG', section_content, re.IGNORECASE))
        
        if not has_sys_req:
            self.issues.append(ValidationIssue("WARNING", "TRACEABILITY",
                "No references to System Requirements found. "
                "SRS should trace to System Requirements."))
        
        if not has_hazard and self.sil_level >= 2:
            self.issues.append(ValidationIssue("WARNING", "TRACEABILITY",
                f"No references to Hazard Log found (recommended for SIL {self.sil_level})."))
        
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
        self.check_requirements_format()
        self.check_requirement_ids()
        self.check_traceability()
        
        return len([i for i in self.issues if i.severity == "ERROR"]) == 0
    
    def generate_report(self) -> str:
        """Generate validation report"""
        errors = [i for i in self.issues if i.severity == "ERROR"]
        warnings = [i for i in self.issues if i.severity == "WARNING"]
        
        compliance = (self.checks_passed / self.checks_total * 100) if self.checks_total > 0 else 0
        overall_status = "PASS" if len(errors) == 0 else "FAIL"
        
        report = f"""
EN 50128 SRS Template Validation Report
========================================

Document: {self.doc_path.name}
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
        
        report += """
Validation Checks Performed:
1. Document ID format (DOC-REQ-YYYY-NNN or DOC-REQ-SRS-NNN)
2. STANDARD HEADER with required fields
3. DOCUMENT CONTROL table with version history
4. APPROVALS table with SIL-specific approvers
5. Required sections (Introduction, Functional Requirements, etc.)
6. Requirements format (SHALL/SHOULD/MAY keywords)
7. Requirement ID format (REQ-XXX-NNN or SWREQ-NNN)
8. Traceability to System Requirements and Hazard Log

Reference: EN 50128:2011 Section 7.2, Table A.2
"""
        
        return report

def main():
    parser = argparse.ArgumentParser(
        description="Validate EN 50128 Software Requirements Specification (SRS) documents",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python3 validate_srs_template.py docs/SRS.md --sil 3
  python3 validate_srs_template.py DOC-REQ-SRS-001.md --sil 0

Exit Codes:
  0 - Validation passed
  1 - Validation failed (errors found)

Reference:
  EN 50128:2011 Section 7.2 (Software Requirements Specification)
  Table A.2 (Requirements Specification Techniques)
        """
    )
    
    parser.add_argument("srs_file", help="Path to SRS document (.md file)")
    parser.add_argument("--sil", type=int, required=True, choices=[0, 1, 2, 3, 4],
                        help="SIL level (0-4)")
    
    args = parser.parse_args()
    
    # Check file exists
    if not Path(args.srs_file).exists():
        print(f"ERROR: File not found: {args.srs_file}", file=sys.stderr)
        return 1
    
    # Create validator and run validation
    validator = SRSValidator(args.srs_file, args.sil)
    is_valid = validator.validate()
    
    # Print report
    print(validator.generate_report())
    
    # Return exit code
    return 0 if is_valid else 1

if __name__ == "__main__":
    sys.exit(main())
