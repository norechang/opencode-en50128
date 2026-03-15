#!/usr/bin/env python3
"""
validate_test_doc_template.py - EN 50128 Test Document Template Validator

PURPOSE:
    Validate test documentation (Component/Integration/Overall Test Specifications
    and Reports) against EN 50128 templates per EN 50128:2011 Section 7.4, 7.5, 7.7.

USAGE:
    python3 validate_test_doc_template.py <test_document.md> --sil <0-4>

VALIDATION CHECKS:
    1. Document ID format: DOC-XXX-YYYY-NNN
    2. Document Control table: 5 required fields
    3. Approvals table: SIL-specific approvers
    4. Required sections (test spec/report specific)
    5. Traceability section: Links to requirements, design, code
    6. Coverage data (for test reports): Statement/Branch/Condition percentages

OUTPUT:
    - Validation report (PASS/FAIL)
    - List of issues (missing sections, incorrect format, etc.)
    - Compliance percentage

AUTHOR: OpenCode Architecture Transformation Phase 3
DATE: 2026-03-15
VERSION: 1.0
REFERENCE: EN 50128:2011 Table A.5, A.13, A.21
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

class TestDocValidator:
    """Validator for EN 50128 test documentation templates"""
    
    def __init__(self, doc_path: str, sil_level: int):
        self.doc_path = Path(doc_path)
        self.sil_level = sil_level
        self.issues: List[ValidationIssue] = []
        self.content = ""
        self.checks_passed = 0
        self.checks_total = 0
        
        # Required sections (common to all test documents)
        self.required_sections = [
            "STANDARD HEADER",
            "DOCUMENT CONTROL",
            "APPROVALS",
            "EXECUTIVE SUMMARY",
            "INTRODUCTION",
            "TEST EXECUTION SUMMARY",
            "TRACEABILITY"
        ]
    
    def load_document(self) -> bool:
        """Load the test document"""
        try:
            with open(self.doc_path, 'r', encoding='utf-8') as f:
                self.content = f.read()
            return True
        except Exception as e:
            self.issues.append(ValidationIssue("ERROR", "File I/O", 
                f"Failed to load document: {e}"))
            return False
    
    def check_document_id(self) -> bool:
        """Check Document ID format: DOC-XXX-YYYY-NNN"""
        self.checks_total += 1
        pattern = r'\|\s*\*\*Document ID\*\*\s*\|\s*(\S+)\s*\|'
        match = re.search(pattern, self.content)
        
        if not match:
            self.issues.append(ValidationIssue("ERROR", "STANDARD HEADER",
                "Document ID field not found in STANDARD HEADER table"))
            return False
        
        doc_id = match.group(1)
        
        # Check format: DOC-XXX-YYYY-NNN
        if not re.match(r'^DOC-[A-Z]+-\d{4}-\d{3}$', doc_id):
            self.issues.append(ValidationIssue("ERROR", "STANDARD HEADER",
                f"Document ID '{doc_id}' does not match format DOC-XXX-YYYY-NNN"))
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
        """Check APPROVALS table has SIL-appropriate approvers"""
        self.checks_total += 1
        
        if "## APPROVALS" not in self.content:
            self.issues.append(ValidationIssue("ERROR", "APPROVALS",
                "APPROVALS section not found"))
            return False
        
        # Extract APPROVALS section
        section_start = self.content.find("## APPROVALS")
        section_end = self.content.find("##", section_start + 1)
        section_content = self.content[section_start:section_end if section_end != -1 else None]
        
        # Required approvers for all SIL levels
        required_approvers = ["Author", "Technical Reviewer", "QA Manager", "Project Manager"]
        
        # Additional approvers for SIL 2+
        if self.sil_level >= 2:
            required_approvers.append("Safety Manager")
        
        # Additional approvers for SIL 3-4
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
            if section not in self.content:
                missing_sections.append(section)
        
        if missing_sections:
            self.issues.append(ValidationIssue("ERROR", "Document Structure",
                f"Missing required sections: {', '.join(missing_sections)}"))
            return False
        
        self.checks_passed += 1
        return True
    
    def check_traceability(self) -> bool:
        """Check TRACEABILITY section exists and has proper links"""
        self.checks_total += 1
        
        if "## TRACEABILITY" not in self.content and "TRACEABILITY" not in self.content:
            self.issues.append(ValidationIssue("WARNING", "TRACEABILITY",
                "TRACEABILITY section not found or not clearly marked"))
            return False
        
        # Extract traceability section
        pattern = r'## [\d.]* TRACEABILITY|## TRACEABILITY'
        match = re.search(pattern, self.content)
        
        if not match:
            self.issues.append(ValidationIssue("WARNING", "TRACEABILITY",
                "TRACEABILITY section header not found"))
            return False
        
        section_start = match.end()
        section_end = self.content.find("##", section_start)
        section_content = self.content[section_start:section_end if section_end != -1 else None]
        
        # Check for requirement references (REQ-XXX format)
        if not re.search(r'REQ-\d+', section_content):
            self.issues.append(ValidationIssue("WARNING", "TRACEABILITY",
                "No requirement references (REQ-XXX) found in TRACEABILITY section"))
        
        self.checks_passed += 1
        return True
    
    def check_coverage_data(self) -> bool:
        """Check coverage data for test reports (Statement/Branch/Condition)"""
        self.checks_total += 1
        
        # Only check if this is a test report (contains "Report" in title or path)
        if "Report" not in self.doc_path.name and "report" not in self.content.lower():
            self.checks_passed += 1
            return True  # Skip for specifications
        
        # Check for coverage percentages
        coverage_types = ["Statement", "Branch", "Condition"]
        found_coverage = []
        
        for coverage_type in coverage_types:
            pattern = rf'{coverage_type}\s*Coverage[:\s]*\[?\d+\.?\d*%?\]?'
            if re.search(pattern, self.content, re.IGNORECASE):
                found_coverage.append(coverage_type)
        
        if not found_coverage:
            self.issues.append(ValidationIssue("WARNING", "Coverage Data",
                "No coverage data found (Statement/Branch/Condition). Required for SIL 2+ test reports."))
            
            if self.sil_level >= 2:
                return False
        
        # For SIL 3-4, all three coverage types are MANDATORY
        if self.sil_level >= 3:
            missing_coverage = [ct for ct in coverage_types if ct not in found_coverage]
            if missing_coverage:
                self.issues.append(ValidationIssue("ERROR", "Coverage Data",
                    f"Missing MANDATORY coverage types for SIL {self.sil_level}: {', '.join(missing_coverage)}"))
                return False
        
        self.checks_passed += 1
        return True
    
    def generate_report(self) -> str:
        """Generate validation report"""
        compliance_percentage = (self.checks_passed / self.checks_total * 100) if self.checks_total > 0 else 0
        
        result = "PASS" if self.checks_passed == self.checks_total else "FAIL"
        
        report = f"""
# Test Document Template Validation Report

**Document**: {self.doc_path.name}
**SIL Level**: {self.sil_level}
**Validation Result**: **{result}**

## Summary

- **Checks Performed**: {self.checks_total}
- **Checks Passed**: {self.checks_passed}
- **Checks Failed**: {self.checks_total - self.checks_passed}
- **Compliance**: {compliance_percentage:.1f}%

## Validation Checks

1. ✓ Document ID format validation
2. ✓ STANDARD HEADER completeness
3. ✓ DOCUMENT CONTROL table structure
4. ✓ APPROVALS table (SIL-specific)
5. ✓ Required sections presence
6. ✓ TRACEABILITY section validation
7. ✓ Coverage data validation (test reports)

## Issues Found

"""
        
        if not self.issues:
            report += "✅ **No issues found. Document is template-compliant.**\n"
        else:
            report += f"❌ **{len(self.issues)} issue(s) found:**\n\n"
            for i, issue in enumerate(self.issues, 1):
                report += f"{i}. {issue}\n"
        
        report += f"""

## Recommendation

{'✅ **APPROVED**: Document meets EN 50128 template requirements.' if result == 'PASS' else '❌ **REJECTED**: Document does not meet template requirements. Please address issues above.'}

---

**Validator**: validate_test_doc_template.py v1.0
**Reference**: EN 50128:2011 Section 7.4, 7.5, 7.7, Table A.5
**Date**: {self.get_current_date()}
"""
        return report
    
    def get_current_date(self) -> str:
        """Get current date in YYYY-MM-DD format"""
        from datetime import datetime
        return datetime.now().strftime("%Y-%m-%d")
    
    def validate(self) -> Tuple[bool, str]:
        """Run all validation checks"""
        if not self.load_document():
            return False, self.generate_report()
        
        # Run all checks
        self.check_document_id()
        self.check_standard_header()
        self.check_document_control()
        self.check_approvals()
        self.check_required_sections()
        self.check_traceability()
        self.check_coverage_data()
        
        # Generate report
        report = self.generate_report()
        success = self.checks_passed == self.checks_total
        
        return success, report

def main():
    parser = argparse.ArgumentParser(
        description="Validate EN 50128 test documentation against templates",
        epilog="Example: python3 validate_test_doc_template.py Component-Test-Report.md --sil 3"
    )
    parser.add_argument("document", help="Path to test document (Markdown format)")
    parser.add_argument("--sil", type=int, choices=[0, 1, 2, 3, 4], required=True,
                        help="SIL level (0-4)")
    parser.add_argument("--output", help="Output validation report to file")
    
    args = parser.parse_args()
    
    # Validate document
    validator = TestDocValidator(args.document, args.sil)
    success, report = validator.validate()
    
    # Print report
    print(report)
    
    # Save to file if requested
    if args.output:
        with open(args.output, 'w', encoding='utf-8') as f:
            f.write(report)
        print(f"\nValidation report saved to: {args.output}")
    
    # Exit with appropriate code
    sys.exit(0 if success else 1)

if __name__ == "__main__":
    main()
