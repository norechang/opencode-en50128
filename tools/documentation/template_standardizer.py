#!/usr/bin/env python3
"""
EN 50128 Template Standardizer

Standardizes ALL template headers to match DOCUMENT-HEADER-TEMPLATE.md Section 2 exactly.

MANDATORY STRUCTURE (from DOCUMENT-HEADER-TEMPLATE.md Section 2):
1. Document title (# heading)
2. TEMPLATE VERSION and REFERENCE metadata (2 lines only)
3. Horizontal rule (---)
4. ## STANDARD HEADER (exactly 9 fields in table)
5. ## DOCUMENT CONTROL (5 columns: Version, Date, Author, Changes, Approved By)
6. ## APPROVALS (SIL requirements + signature table)
7. Horizontal rule (---) before content sections

Author: EN 50128 Documentation Team
Version: 3.0 (Phase 3 - Full standardization)
Date: 2026-03-10
"""

import os
import re
import sys
from pathlib import Path
from typing import List, Tuple, Optional
import argparse

# ANSI colors
GREEN = '\033[92m'
RED = '\033[91m'
YELLOW = '\033[93m'
BLUE = '\033[94m'
RESET = '\033[0m'

class TemplateStandardizer:
    """Standardize template headers to match DOCUMENT-HEADER-TEMPLATE.md Section 2"""
    
    def __init__(self):
        self.templates_fixed = 0
        self.templates_failed = 0
        self.issues_found = []
        
    def standardize_template(self, filepath: str, dry_run: bool = False) -> Tuple[bool, List[str]]:
        """
        Standardize a single template file to match official format.
        
        Returns:
            (success, issues_list)
        """
        issues = []
        
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                content = f.read()
            
            # Extract document title (first # heading)
            title_match = re.search(r'^# (.+)$', content, re.MULTILINE)
            if not title_match:
                issues.append(f"No document title found (first # heading)")
                return False, issues
            
            doc_title = title_match.group(1).strip()
            
            # Extract TEMPLATE VERSION and REFERENCE if they exist
            template_version = self._extract_metadata(content, 'TEMPLATE VERSION')
            reference = self._extract_metadata(content, 'REFERENCE')
            
            if not template_version:
                template_version = "1.0"
                issues.append(f"No TEMPLATE VERSION found, using default: {template_version}")
            
            if not reference:
                reference = "EN 50128:2011 Section [X.Y], Table [A.N]"
                issues.append(f"No REFERENCE found, using placeholder: {reference}")
            
            # Find where main content starts (after header sections)
            content_start = self._find_content_start(content)
            
            if content_start == -1:
                issues.append("Could not find content start (first numbered section like ## 1.)")
                return False, issues
            
            # Extract main content (everything after headers)
            main_content = content[content_start:].strip()
            
            # Build standardized header
            standardized_header = self._build_standard_header(
                doc_title, 
                template_version, 
                reference
            )
            
            # Combine header + content
            new_content = standardized_header + "\n\n" + main_content
            
            # Write file (if not dry-run)
            if not dry_run:
                with open(filepath, 'w', encoding='utf-8') as f:
                    f.write(new_content)
                issues.append(f"{GREEN}✓ Template standardized successfully{RESET}")
            else:
                issues.append(f"{BLUE}[DRY RUN] Would standardize template{RESET}")
            
            return True, issues
            
        except Exception as e:
            issues.append(f"{RED}ERROR: {str(e)}{RESET}")
            return False, issues
    
    def _extract_metadata(self, content: str, field_name: str) -> Optional[str]:
        """Extract metadata field value (e.g., TEMPLATE VERSION, REFERENCE)"""
        # Try bold markdown format: **FIELD**: value
        pattern = rf'\*\*{re.escape(field_name)}\*\*:\s*(.+?)(?:\n|$)'
        match = re.search(pattern, content, re.IGNORECASE)
        if match:
            return match.group(1).strip()
        
        # Try plain format: FIELD: value
        pattern = rf'{re.escape(field_name)}:\s*(.+?)(?:\n|$)'
        match = re.search(pattern, content, re.IGNORECASE)
        if match:
            return match.group(1).strip()
        
        return None
    
    def _find_content_start(self, content: str) -> int:
        """
        Find where main content starts (after all header sections).
        
        Main content typically starts with:
        - ## 1. INTRODUCTION
        - ## 1. 
        - Or first section not in header area
        """
        lines = content.split('\n')
        
        # Look for first numbered section (## 1., ## 1. INTRODUCTION, etc.)
        for i, line in enumerate(lines):
            # Match: ## 1. or ## 1. SOMETHING
            if re.match(r'^##\s+1\.', line):
                # Return position of this line in original content
                return content.find(line)
        
        # Fallback: Look for section after APPROVALS
        approvals_match = re.search(r'^## APPROVALS\s*$', content, re.MULTILINE)
        if approvals_match:
            # Find next ## heading after APPROVALS
            after_approvals = content[approvals_match.end():]
            next_section = re.search(r'^## [^A]', after_approvals, re.MULTILINE)
            if next_section:
                return approvals_match.end() + next_section.start()
        
        # Fallback: Look for "Table of Contents" section
        toc_match = re.search(r'^## Table of Contents', content, re.MULTILINE)
        if toc_match:
            return toc_match.start()
        
        # Last resort: Look for first ## heading that's not a standard header section
        standard_sections = ['STANDARD HEADER', 'DOCUMENT CONTROL', 'APPROVALS', 'EN 50128 References']
        for match in re.finditer(r'^## (.+)$', content, re.MULTILINE):
            section_name = match.group(1).strip()
            if section_name not in standard_sections:
                return match.start()
        
        return -1
    
    def _build_standard_header(self, title: str, template_version: str, reference: str) -> str:
        """
        Build standardized header exactly matching DOCUMENT-HEADER-TEMPLATE.md Section 2.
        
        Structure:
        1. Title
        2. TEMPLATE VERSION + REFERENCE (2 lines only)
        3. ---
        4. ## STANDARD HEADER (9 fields)
        5. ## DOCUMENT CONTROL (5 columns)
        6. ## APPROVALS (SIL requirements + table)
        7. ---
        """
        header = f"""# {title}

**TEMPLATE VERSION**: {template_version}  
**REFERENCE**: {reference}

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | [DOC-XXX-YYYY-NNN] |
| **Version** | [X.Y] |
| **Date** | [YYYY-MM-DD] |
| **Project** | [Project Name] |
| **SIL Level** | [0, 1, 2, 3, or 4] |
| **Author** | [Name], [Role] |
| **Reviewer** | [Name], [Role] |
| **Approver** | [Name], [Role] |
| **Status** | [Draft \\| Review \\| Approved \\| Baseline] |

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft | - |

## APPROVALS

**SIL 0-2 Requirements**: Author, Technical Reviewer, QA Manager, Project Manager  
**SIL 3-4 Requirements**: Author, Technical Reviewer (independent), QA Manager, Safety Manager, Independent Verifier, Independent Validator, Assessor, Project Manager

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author** | [Name] | | YYYY-MM-DD |
| **Technical Reviewer** | [Name] | | YYYY-MM-DD |
| **QA Manager** | [Name] | | YYYY-MM-DD |
| **Safety Manager** (SIL 2+) | [Name] | | YYYY-MM-DD |
| **Project Manager** | [Name] | | YYYY-MM-DD |
| **Independent Verifier** (SIL 3-4) | [Name] | | YYYY-MM-DD |
| **Independent Validator** (SIL 3-4) | [Name] | | YYYY-MM-DD |
| **Assessor** (SIL 3-4) | [Name] | | YYYY-MM-DD |

---"""
        
        return header
    
    def find_all_templates(self, root_dir: str = '.opencode/skills') -> List[str]:
        """Find all template markdown files"""
        templates = []
        root_path = Path(root_dir)
        
        if not root_path.exists():
            print(f"{RED}ERROR: Directory not found: {root_dir}{RESET}")
            return templates
        
        # Find all *-template.md files
        for template_file in root_path.rglob('*-template.md'):
            templates.append(str(template_file))
        
        return sorted(templates)
    
    def standardize_all_templates(self, root_dir: str = '.opencode/skills', dry_run: bool = False):
        """Standardize all templates in the project"""
        print(f"\n{'='*80}")
        print(f"EN 50128 Template Standardization - Phase 3")
        print(f"Reference: DOCUMENT-HEADER-TEMPLATE.md Section 2")
        print(f"{'='*80}\n")
        
        if dry_run:
            print(f"{YELLOW}[DRY RUN MODE] - No files will be modified{RESET}\n")
        
        templates = self.find_all_templates(root_dir)
        
        if not templates:
            print(f"{RED}No templates found in {root_dir}{RESET}")
            return
        
        print(f"Found {len(templates)} templates\n")
        
        for i, template_path in enumerate(templates, 1):
            rel_path = os.path.relpath(template_path)
            print(f"\n[{i}/{len(templates)}] {BLUE}{rel_path}{RESET}")
            print(f"{'-'*80}")
            
            success, issues = self.standardize_template(template_path, dry_run)
            
            for issue in issues:
                print(f"  {issue}")
            
            if success:
                self.templates_fixed += 1
            else:
                self.templates_failed += 1
                self.issues_found.append(f"{rel_path}: {', '.join(issues)}")
        
        # Summary
        print(f"\n{'='*80}")
        print(f"STANDARDIZATION SUMMARY")
        print(f"{'='*80}")
        print(f"Templates processed: {len(templates)}")
        print(f"{GREEN}Successfully standardized: {self.templates_fixed}{RESET}")
        print(f"{RED}Failed: {self.templates_failed}{RESET}")
        
        if self.issues_found:
            print(f"\n{YELLOW}Issues encountered:{RESET}")
            for issue in self.issues_found:
                print(f"  - {issue}")
        
        print()

def main():
    parser = argparse.ArgumentParser(
        description='Standardize EN 50128 template headers to match DOCUMENT-HEADER-TEMPLATE.md Section 2',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Dry run on single template
  python3 template_standardizer.py --file path/to/template.md --dry-run
  
  # Standardize single template
  python3 template_standardizer.py --file path/to/template.md
  
  # Dry run on all templates
  python3 template_standardizer.py --standardize-all --dry-run
  
  # Standardize all templates
  python3 template_standardizer.py --standardize-all
        """
    )
    
    parser.add_argument('--file', type=str, help='Path to single template file')
    parser.add_argument('--standardize-all', action='store_true', 
                       help='Standardize all templates in .opencode/skills')
    parser.add_argument('--root-dir', type=str, default='.opencode/skills',
                       help='Root directory to search for templates (default: .opencode/skills)')
    parser.add_argument('--dry-run', action='store_true',
                       help='Preview changes without modifying files')
    
    args = parser.parse_args()
    
    if not args.file and not args.standardize_all:
        parser.print_help()
        sys.exit(1)
    
    standardizer = TemplateStandardizer()
    
    if args.file:
        # Standardize single file
        print(f"\n{'='*80}")
        print(f"Standardizing: {args.file}")
        print(f"{'='*80}\n")
        
        if args.dry_run:
            print(f"{YELLOW}[DRY RUN MODE]{RESET}\n")
        
        success, issues = standardizer.standardize_template(args.file, args.dry_run)
        
        for issue in issues:
            print(issue)
        
        sys.exit(0 if success else 1)
    
    elif args.standardize_all:
        # Standardize all templates
        standardizer.standardize_all_templates(args.root_dir, args.dry_run)

if __name__ == '__main__':
    main()
