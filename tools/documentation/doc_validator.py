#!/usr/bin/env python3
"""
EN 50128 Document Template Validator

Validates EN 50128 document templates against the mandatory header structure
and compliance rules defined in DOCUMENT-HEADER-TEMPLATE.md.

Usage:
    python3 doc_validator.py <template-file>
    python3 doc_validator.py --validate-all-templates
    python3 doc_validator.py --report <output-file>

Author: EN 50128 Platform Team
Version: 1.0
Date: 2026-03-10
"""

import re
import sys
import os
import json
from pathlib import Path
from typing import Dict, List, Tuple, Optional
from dataclasses import dataclass, asdict
from enum import Enum


class SeverityLevel(Enum):
    """Validation finding severity levels"""
    CRITICAL = "CRITICAL"  # Must fix - blocks approval
    ERROR = "ERROR"        # Should fix - compliance issue
    WARNING = "WARNING"    # Should fix - best practice violation
    INFO = "INFO"          # Informational - suggestion


@dataclass
class ValidationFinding:
    """Represents a validation finding"""
    severity: SeverityLevel
    rule_id: str
    rule_description: str
    line_number: Optional[int]
    message: str
    suggestion: Optional[str] = None

    def to_dict(self) -> Dict:
        """Convert to dictionary for JSON serialization"""
        result = asdict(self)
        result['severity'] = self.severity.value
        return result


@dataclass
class ValidationResult:
    """Overall validation result for a document"""
    file_path: str
    valid: bool
    findings: List[ValidationFinding]
    
    def to_dict(self) -> Dict:
        """Convert to dictionary for JSON serialization"""
        return {
            'file_path': self.file_path,
            'valid': self.valid,
            'findings': [f.to_dict() for f in self.findings],
            'summary': {
                'total': len(self.findings),
                'critical': sum(1 for f in self.findings if f.severity == SeverityLevel.CRITICAL),
                'error': sum(1 for f in self.findings if f.severity == SeverityLevel.ERROR),
                'warning': sum(1 for f in self.findings if f.severity == SeverityLevel.WARNING),
                'info': sum(1 for f in self.findings if f.severity == SeverityLevel.INFO),
            }
        }


class DocumentValidator:
    """Validates EN 50128 document templates"""
    
    # Regex patterns for validation
    PATTERNS = {
        'doc_id': r'DOC-[A-Z0-9\-]{3,12}-\d{4}-\d{3}',
        'version': r'\d+\.\d+',
        'date': r'\d{4}-\d{2}-\d{2}',
        'sil_level': r'[0-4]',
    }
    
    # Required header fields (EXACT order and names per DOCUMENT-HEADER-TEMPLATE.md Section 2.1)
    REQUIRED_HEADER_FIELDS = [
        'Document ID',
        'Version',
        'Date',
        'Project',
        'SIL Level',
        'Author',
        'Reviewer',
        'Approver',
        'Status',
    ]
    
    # FORBIDDEN metadata fields at document top (per DOCUMENT-HEADER-TEMPLATE.md Section 2)
    # Only TEMPLATE VERSION and REFERENCE are allowed
    FORBIDDEN_METADATA_FIELDS = [
        'DOCUMENT ID',
        'VERSION',
        'DATE',
        'STATUS',
        'CLASSIFICATION',
        'PROJECT',
        'AUTHOR',
        'PREPARED BY',
        'REVIEWED BY',
        'APPROVED BY',
    ]
    
    # Valid status values
    VALID_STATUS_VALUES = ['Draft', 'Review', 'Approved', 'Baseline', 'Obsolete']
    
    # Required sections (markdown headers)
    REQUIRED_SECTIONS = [
        'STANDARD HEADER',
        'DOCUMENT CONTROL',
        'APPROVALS',
    ]
    
    def __init__(self, file_path: str):
        """Initialize validator with document path"""
        self.file_path = file_path
        self.content = ""
        self.lines = []
        self.findings: List[ValidationFinding] = []
        
    def load_document(self) -> bool:
        """Load document content"""
        try:
            with open(self.file_path, 'r', encoding='utf-8') as f:
                self.content = f.read()
                self.lines = self.content.split('\n')
            return True
        except FileNotFoundError:
            self.findings.append(ValidationFinding(
                severity=SeverityLevel.CRITICAL,
                rule_id="FILE-001",
                rule_description="File must exist",
                line_number=None,
                message=f"File not found: {self.file_path}",
                suggestion="Check file path and ensure file exists"
            ))
            return False
        except Exception as e:
            self.findings.append(ValidationFinding(
                severity=SeverityLevel.CRITICAL,
                rule_id="FILE-002",
                rule_description="File must be readable",
                line_number=None,
                message=f"Error reading file: {str(e)}",
                suggestion="Check file permissions and encoding"
            ))
            return False
    
    def validate(self) -> ValidationResult:
        """Run all validation checks"""
        if not self.load_document():
            return ValidationResult(
                file_path=self.file_path,
                valid=False,
                findings=self.findings
            )
        
        # Run validation checks
        self.check_document_title()
        self.check_template_version()
        self.check_en50128_reference()
        self.check_forbidden_metadata()  # NEW: Check for forbidden metadata fields
        self.check_standard_header()
        self.check_document_control()
        self.check_approvals_section()
        self.check_required_sections()
        self.check_table_of_contents()
        
        # Determine overall validity
        critical_count = sum(1 for f in self.findings if f.severity == SeverityLevel.CRITICAL)
        valid = (critical_count == 0)
        
        return ValidationResult(
            file_path=self.file_path,
            valid=valid,
            findings=self.findings
        )
    
    def check_document_title(self):
        """Check that document has a title (# heading at top)"""
        if not self.lines:
            return
        
        # Find first non-empty line
        first_line = None
        line_num = 0
        for i, line in enumerate(self.lines):
            if line.strip():
                first_line = line.strip()
                line_num = i + 1
                break
        
        if not first_line or not first_line.startswith('#'):
            self.findings.append(ValidationFinding(
                severity=SeverityLevel.ERROR,
                rule_id="TITLE-001",
                rule_description="Document must start with markdown title (# heading)",
                line_number=line_num,
                message="Document does not start with markdown title",
                suggestion="Add '# [Document Name]' as first line"
            ))
        elif not first_line.startswith('# '):
            self.findings.append(ValidationFinding(
                severity=SeverityLevel.WARNING,
                rule_id="TITLE-002",
                rule_description="Document title should have space after #",
                line_number=line_num,
                message="Document title should be '# Title' not '#Title'",
                suggestion="Add space after # in title"
            ))
    
    def check_template_version(self):
        """Check for template version metadata"""
        found = False
        for i, line in enumerate(self.lines):
            if re.search(r'\*\*TEMPLATE VERSION\*\*:', line, re.IGNORECASE):
                found = True
                # Check version format
                if not re.search(r'\d+\.\d+', line):
                    self.findings.append(ValidationFinding(
                        severity=SeverityLevel.WARNING,
                        rule_id="META-001",
                        rule_description="Template version should follow X.Y format",
                        line_number=i + 1,
                        message="Template version format invalid",
                        suggestion="Use format: **TEMPLATE VERSION**: X.Y"
                    ))
                break
        
        if not found:
            self.findings.append(ValidationFinding(
                severity=SeverityLevel.INFO,
                rule_id="META-002",
                rule_description="Template version should be included",
                line_number=None,
                message="Template version not found",
                suggestion="Add: **TEMPLATE VERSION**: X.Y at top of document"
            ))
    
    def check_en50128_reference(self):
        """Check for EN 50128 standard reference"""
        found = False
        for i, line in enumerate(self.lines):
            if re.search(r'\*\*REFERENCE\*\*:', line, re.IGNORECASE):
                found = True
                # Check if EN 50128 is mentioned
                if not re.search(r'EN\s*50128', line, re.IGNORECASE):
                    self.findings.append(ValidationFinding(
                        severity=SeverityLevel.WARNING,
                        rule_id="META-003",
                        rule_description="Reference should cite EN 50128 standard",
                        line_number=i + 1,
                        message="EN 50128 reference not found in REFERENCE field",
                        suggestion="Include: EN 50128:2011 Section X.Y"
                    ))
                break
        
        if not found:
            self.findings.append(ValidationFinding(
                severity=SeverityLevel.WARNING,
                rule_id="META-004",
                rule_description="EN 50128 reference should be included",
                line_number=None,
                message="REFERENCE field not found",
                suggestion="Add: **REFERENCE**: EN 50128:2011 Section X.Y"
            ))
    
    def check_forbidden_metadata(self):
        """
        Check for forbidden metadata fields at document top.
        Per DOCUMENT-HEADER-TEMPLATE.md Section 2, ONLY these are allowed:
        - TEMPLATE VERSION
        - REFERENCE
        """
        # Check first 30 lines before STANDARD HEADER
        header_line = None
        for i, line in enumerate(self.lines):
            if re.search(r'^##\s+STANDARD HEADER', line, re.IGNORECASE):
                header_line = i
                break
        
        if header_line is None:
            return  # Will be caught by check_standard_header
        
        # Check lines before STANDARD HEADER for forbidden metadata
        for i in range(min(header_line, 30)):
            line = self.lines[i]
            for forbidden in self.FORBIDDEN_METADATA_FIELDS:
                # Check for **FIELD**: format
                if re.search(rf'\*\*{re.escape(forbidden)}\*\*:', line, re.IGNORECASE):
                    self.findings.append(ValidationFinding(
                        severity=SeverityLevel.ERROR,
                        rule_id="META-005",
                        rule_description="Only TEMPLATE VERSION and REFERENCE allowed at document top",
                        line_number=i + 1,
                        message=f"Forbidden metadata field '{forbidden}' at document top",
                        suggestion=f"Remove '{forbidden}' - this field belongs in STANDARD HEADER table"
                    ))
    
    def check_standard_header(self):
        """Check for STANDARD HEADER section and table"""
        # Find STANDARD HEADER section
        header_line = None
        for i, line in enumerate(self.lines):
            if re.search(r'^##\s+STANDARD HEADER', line, re.IGNORECASE):
                header_line = i
                break
        
        if header_line is None:
            self.findings.append(ValidationFinding(
                severity=SeverityLevel.CRITICAL,
                rule_id="HEADER-001",
                rule_description="STANDARD HEADER section is mandatory",
                line_number=None,
                message="STANDARD HEADER section not found",
                suggestion="Add: ## STANDARD HEADER section with table"
            ))
            return
        
        # Check for table after header (within next 20 lines)
        table_found = False
        for i in range(header_line + 1, min(header_line + 20, len(self.lines))):
            if '|' in self.lines[i]:
                table_found = True
                break
        
        if not table_found:
            self.findings.append(ValidationFinding(
                severity=SeverityLevel.CRITICAL,
                rule_id="HEADER-002",
                rule_description="STANDARD HEADER table is mandatory",
                line_number=header_line + 1,
                message="STANDARD HEADER table not found after section heading",
                suggestion="Add markdown table with required fields"
            ))
            return
        
        # Check for required fields in header table
        # Find where STANDARD HEADER table ends (next ## section)
        header_table_end = header_line + 30
        for i in range(header_line + 1, min(header_line + 30, len(self.lines))):
            if re.match(r'^##\s+', self.lines[i]):  # Next section starts
                header_table_end = i
                break
        
        header_section = '\n'.join(self.lines[header_line:header_table_end])
        
        # Extract all fields from header table
        found_fields = []
        for i in range(header_line + 1, header_table_end):
            line = self.lines[i]
            # Match table rows: | **Field Name** | value |
            match = re.match(r'\|\s*\*\*([^*]+)\*\*\s*\|', line)
            if match:
                field_name = match.group(1).strip()
                found_fields.append(field_name)
        
        # Check for exactly 9 fields
        if len(found_fields) != 9:
            self.findings.append(ValidationFinding(
                severity=SeverityLevel.ERROR,
                rule_id="HEADER-004",
                rule_description="STANDARD HEADER must have exactly 9 fields",
                line_number=header_line + 1,
                message=f"Found {len(found_fields)} fields in STANDARD HEADER, expected 9",
                suggestion="STANDARD HEADER must have: Document ID, Version, Date, Project, SIL Level, Author, Reviewer, Approver, Status"
            ))
        
        # Check each required field is present
        for field in self.REQUIRED_HEADER_FIELDS:
            if field not in found_fields:
                self.findings.append(ValidationFinding(
                    severity=SeverityLevel.ERROR,
                    rule_id="HEADER-003",
                    rule_description=f"Required field '{field}' must be in STANDARD HEADER",
                    line_number=header_line + 1,
                    message=f"Required field '{field}' not found in STANDARD HEADER table",
                    suggestion=f"Add row: | **{field}** | [Value] |"
                ))
        
        # Check for forbidden field names (e.g., "Prepared by" instead of "Author")
        forbidden_names = {
            'Prepared by': 'Author',
            'Reviewed by': 'Reviewer',
            'Approved by': 'Approver',
        }
        for forbidden, correct in forbidden_names.items():
            if forbidden in found_fields:
                self.findings.append(ValidationFinding(
                    severity=SeverityLevel.ERROR,
                    rule_id="HEADER-005",
                    rule_description=f"Field name must be '{correct}' not '{forbidden}'",
                    line_number=header_line + 1,
                    message=f"Incorrect field name '{forbidden}' in STANDARD HEADER",
                    suggestion=f"Change '{forbidden}' to '{correct}'"
                ))
    
    def check_document_control(self):
        """Check for DOCUMENT CONTROL section and table"""
        control_line = None
        for i, line in enumerate(self.lines):
            if re.search(r'^##\s+DOCUMENT CONTROL', line, re.IGNORECASE):
                control_line = i
                break
        
        if control_line is None:
            self.findings.append(ValidationFinding(
                severity=SeverityLevel.CRITICAL,
                rule_id="CONTROL-001",
                rule_description="DOCUMENT CONTROL section is mandatory",
                line_number=None,
                message="DOCUMENT CONTROL section not found",
                suggestion="Add: ## DOCUMENT CONTROL section with version history table"
            ))
            return
        
        # Check for table with required columns (EXACTLY 5: Version, Date, Author, Changes, Approved By)
        control_section = '\n'.join(self.lines[control_line:min(control_line + 20, len(self.lines))])
        required_columns = ['Version', 'Date', 'Author', 'Changes', 'Approved By']
        
        # Find table header line
        header_found = False
        for i in range(control_line + 1, min(control_line + 10, len(self.lines))):
            line = self.lines[i]
            if '|' in line and 'Version' in line:
                header_found = True
                # Count columns
                columns = [col.strip() for col in line.split('|') if col.strip()]
                if len(columns) != 5:
                    self.findings.append(ValidationFinding(
                        severity=SeverityLevel.ERROR,
                        rule_id="CONTROL-003",
                        rule_description="DOCUMENT CONTROL table must have exactly 5 columns",
                        line_number=i + 1,
                        message=f"Found {len(columns)} columns, expected 5",
                        suggestion="Columns must be: Version | Date | Author | Changes | Approved By"
                    ))
                break
        
        if not header_found:
            self.findings.append(ValidationFinding(
                severity=SeverityLevel.ERROR,
                rule_id="CONTROL-002",
                rule_description="DOCUMENT CONTROL table header not found",
                line_number=control_line + 1,
                message="Table header with columns not found",
                suggestion="Add table header: | Version | Date | Author | Changes | Approved By |"
            ))
            return
        
        # Check for each required column
        for column in required_columns:
            if column not in control_section:
                self.findings.append(ValidationFinding(
                    severity=SeverityLevel.ERROR,
                    rule_id="CONTROL-002",
                    rule_description=f"DOCUMENT CONTROL table must have '{column}' column",
                    line_number=control_line + 1,
                    message=f"Column '{column}' not found in DOCUMENT CONTROL table",
                    suggestion=f"Add column: | {column} | ... |"
                ))
    
    def check_approvals_section(self):
        """Check for APPROVALS section and table"""
        approvals_line = None
        for i, line in enumerate(self.lines):
            if re.search(r'^##\s+APPROVALS', line, re.IGNORECASE):
                approvals_line = i
                break
        
        if approvals_line is None:
            self.findings.append(ValidationFinding(
                severity=SeverityLevel.CRITICAL,
                rule_id="APPROVAL-001",
                rule_description="APPROVALS section is mandatory",
                line_number=None,
                message="APPROVALS section not found",
                suggestion="Add: ## APPROVALS section with signature table"
            ))
            return
        
        # Check for SIL requirements note
        approvals_section = '\n'.join(self.lines[approvals_line:min(approvals_line + 30, len(self.lines))])
        if not re.search(r'SIL\s+[0-9\-]+\s+Requirements', approvals_section, re.IGNORECASE):
            self.findings.append(ValidationFinding(
                severity=SeverityLevel.WARNING,
                rule_id="APPROVAL-002",
                rule_description="APPROVALS section should list SIL-specific requirements",
                line_number=approvals_line + 1,
                message="SIL-specific approval requirements not documented",
                suggestion="Add: **SIL X-Y Requirements**: [List roles]"
            ))
        
        # Check for required columns in approvals table
        required_columns = ['Role', 'Name', 'Signature', 'Date']
        for column in required_columns:
            if column not in approvals_section:
                self.findings.append(ValidationFinding(
                    severity=SeverityLevel.ERROR,
                    rule_id="APPROVAL-003",
                    rule_description=f"APPROVALS table must have '{column}' column",
                    line_number=approvals_line + 1,
                    message=f"Column '{column}' not found in APPROVALS table",
                    suggestion=f"Add column: | {column} | ... |"
                ))
    
    def check_required_sections(self):
        """Check for all required sections"""
        found_sections = set()
        
        for line in self.lines:
            for section in self.REQUIRED_SECTIONS:
                if re.search(rf'^##\s+{re.escape(section)}', line, re.IGNORECASE):
                    found_sections.add(section)
        
        missing_sections = set(self.REQUIRED_SECTIONS) - found_sections
        for section in missing_sections:
            self.findings.append(ValidationFinding(
                severity=SeverityLevel.CRITICAL,
                rule_id="SECTION-001",
                rule_description=f"Section '{section}' is mandatory",
                line_number=None,
                message=f"Required section '{section}' not found",
                suggestion=f"Add: ## {section}"
            ))
    
    def check_table_of_contents(self):
        """Check for Table of Contents (recommended for long documents)"""
        # Check document length
        if len(self.lines) < 100:
            return  # Not required for short documents
        
        # Check for TOC
        has_toc = False
        for line in self.lines[:50]:  # TOC should be in first 50 lines
            if re.search(r'table\s+of\s+contents', line, re.IGNORECASE):
                has_toc = True
                break
        
        if not has_toc:
            self.findings.append(ValidationFinding(
                severity=SeverityLevel.INFO,
                rule_id="TOC-001",
                rule_description="Table of Contents recommended for documents > 3 pages",
                line_number=None,
                message="Table of Contents not found (document appears to be long)",
                suggestion="Add Table of Contents after APPROVALS section"
            ))


def validate_file(file_path: str) -> ValidationResult:
    """Validate a single document file"""
    validator = DocumentValidator(file_path)
    return validator.validate()


def find_all_templates(base_path: str = ".opencode/skills") -> List[str]:
    """Find all template files in skills directory"""
    templates = []
    base = Path(base_path)
    
    if not base.exists():
        return templates
    
    for template_file in base.rglob("*-template.md"):
        templates.append(str(template_file))
    
    for template_file in base.rglob("*Template*.md"):
        templates.append(str(template_file))
    
    return sorted(set(templates))


def print_validation_result(result: ValidationResult, verbose: bool = True):
    """Print validation result to console"""
    print(f"\n{'='*80}")
    print(f"Validating: {result.file_path}")
    print(f"{'='*80}")
    
    if result.valid and not result.findings:
        print("✅ PASS: No issues found")
        return
    
    summary = result.to_dict()['summary']
    print(f"\n📊 Summary:")
    print(f"   Total Findings: {summary['total']}")
    print(f"   🔴 Critical: {summary['critical']}")
    print(f"   🟠 Errors: {summary['error']}")
    print(f"   🟡 Warnings: {summary['warning']}")
    print(f"   🔵 Info: {summary['info']}")
    
    if not verbose:
        status = "✅ PASS" if result.valid else "❌ FAIL"
        print(f"\nResult: {status}")
        return
    
    # Group findings by severity
    critical = [f for f in result.findings if f.severity == SeverityLevel.CRITICAL]
    errors = [f for f in result.findings if f.severity == SeverityLevel.ERROR]
    warnings = [f for f in result.findings if f.severity == SeverityLevel.WARNING]
    info = [f for f in result.findings if f.severity == SeverityLevel.INFO]
    
    def print_findings(findings: List[ValidationFinding], emoji: str):
        for finding in findings:
            line_info = f"Line {finding.line_number}" if finding.line_number else "Unknown line"
            print(f"\n{emoji} [{finding.rule_id}] {line_info}")
            print(f"   Rule: {finding.rule_description}")
            print(f"   Issue: {finding.message}")
            if finding.suggestion:
                print(f"   💡 Suggestion: {finding.suggestion}")
    
    if critical:
        print(f"\n\n🔴 CRITICAL ISSUES ({len(critical)}):")
        print_findings(critical, "🔴")
    
    if errors:
        print(f"\n\n🟠 ERRORS ({len(errors)}):")
        print_findings(errors, "🟠")
    
    if warnings:
        print(f"\n\n🟡 WARNINGS ({len(warnings)}):")
        print_findings(warnings, "🟡")
    
    if info:
        print(f"\n\n🔵 INFO ({len(info)}):")
        print_findings(info, "🔵")
    
    status = "✅ PASS" if result.valid else "❌ FAIL"
    print(f"\n{'-'*80}")
    print(f"Result: {status}")
    print(f"{'-'*80}\n")


def generate_report(results: List[ValidationResult], output_file: str, format: str = 'json'):
    """Generate validation report"""
    if format == 'json':
        report = {
            'validation_date': '2026-03-10',
            'total_files': len(results),
            'passed': sum(1 for r in results if r.valid),
            'failed': sum(1 for r in results if not r.valid),
            'results': [r.to_dict() for r in results]
        }
        
        with open(output_file, 'w', encoding='utf-8') as f:
            json.dump(report, f, indent=2)
        
        print(f"✅ JSON report generated: {output_file}")
    
    elif format == 'markdown':
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write("# EN 50128 Document Template Validation Report\n\n")
            f.write(f"**Date**: 2026-03-10\n\n")
            f.write(f"**Total Files**: {len(results)}\n")
            f.write(f"**Passed**: {sum(1 for r in results if r.valid)}\n")
            f.write(f"**Failed**: {sum(1 for r in results if not r.valid)}\n\n")
            
            f.write("## Summary\n\n")
            f.write("| File | Status | Critical | Errors | Warnings | Info |\n")
            f.write("|------|--------|----------|--------|----------|------|\n")
            
            for result in results:
                summary = result.to_dict()['summary']
                status = "✅ PASS" if result.valid else "❌ FAIL"
                file_name = Path(result.file_path).name
                f.write(f"| {file_name} | {status} | {summary['critical']} | {summary['error']} | {summary['warning']} | {summary['info']} |\n")
            
            f.write("\n## Detailed Findings\n\n")
            for result in results:
                if result.findings:
                    f.write(f"### {Path(result.file_path).name}\n\n")
                    for finding in result.findings:
                        f.write(f"- **[{finding.severity.value}]** {finding.rule_id}: {finding.message}\n")
                        if finding.suggestion:
                            f.write(f"  - Suggestion: {finding.suggestion}\n")
                    f.write("\n")
        
        print(f"✅ Markdown report generated: {output_file}")


def main():
    """Main entry point"""
    import argparse
    
    parser = argparse.ArgumentParser(
        description="EN 50128 Document Template Validator",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Validate single template
  python3 doc_validator.py path/to/template.md
  
  # Validate all templates
  python3 doc_validator.py --validate-all-templates
  
  # Generate JSON report
  python3 doc_validator.py --validate-all-templates --report report.json
  
  # Generate Markdown report
  python3 doc_validator.py --validate-all-templates --report report.md --format markdown
        """
    )
    
    parser.add_argument('file', nargs='?', help='Template file to validate')
    parser.add_argument('--validate-all-templates', action='store_true',
                       help='Validate all templates in .opencode/skills')
    parser.add_argument('--report', help='Generate report file (JSON or Markdown)')
    parser.add_argument('--format', choices=['json', 'markdown'], default='json',
                       help='Report format (default: json)')
    parser.add_argument('--quiet', action='store_true',
                       help='Suppress detailed output, show only summary')
    
    args = parser.parse_args()
    
    if args.validate_all_templates:
        print("🔍 Finding all template files...")
        templates = find_all_templates()
        
        if not templates:
            print("❌ No template files found in .opencode/skills/")
            sys.exit(1)
        
        print(f"✅ Found {len(templates)} template files\n")
        
        results = []
        for template in templates:
            result = validate_file(template)
            results.append(result)
            if not args.quiet:
                print_validation_result(result, verbose=True)
        
        # Summary
        passed = sum(1 for r in results if r.valid)
        failed = len(results) - passed
        
        print(f"\n{'='*80}")
        print(f"OVERALL SUMMARY")
        print(f"{'='*80}")
        print(f"Total Files: {len(results)}")
        print(f"✅ Passed: {passed}")
        print(f"❌ Failed: {failed}")
        
        # Generate report if requested
        if args.report:
            generate_report(results, args.report, args.format)
        
        sys.exit(0 if failed == 0 else 1)
    
    elif args.file:
        if not os.path.exists(args.file):
            print(f"❌ File not found: {args.file}")
            sys.exit(1)
        
        result = validate_file(args.file)
        print_validation_result(result, verbose=not args.quiet)
        
        sys.exit(0 if result.valid else 1)
    
    else:
        parser.print_help()
        sys.exit(1)


if __name__ == '__main__':
    main()
