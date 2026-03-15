#!/usr/bin/env python3
"""
EN 50128 Template Batch Fixer

Automatically adds mandatory EN 50128 header structure to templates that are missing
required sections (STANDARD HEADER, DOCUMENT CONTROL, APPROVALS).

Usage:
    python3 template_fixer.py --file <template_file>        # Fix single template
    python3 template_fixer.py --fix-all                     # Fix all failing templates
    python3 template_fixer.py --dry-run                     # Preview changes without writing
"""

import os
import re
import sys
from pathlib import Path
from typing import List, Tuple, Optional
from dataclasses import dataclass


@dataclass
class TemplateInfo:
    """Information about a template file."""
    path: Path
    title: str
    has_standard_header: bool
    has_document_control: bool
    has_approvals: bool
    needs_fix: bool


def detect_template_title(content: str) -> Optional[str]:
    """Extract the title from the first # heading."""
    lines = content.split('\n')
    for line in lines[:20]:  # Check first 20 lines
        line = line.strip()
        if line.startswith('# ') and not line.startswith('##'):
            return line[2:].strip()
    return None


def has_section(content: str, section_name: str) -> bool:
    """Check if a section exists in the content."""
    pattern = rf'^## {re.escape(section_name)}\s*$'
    return bool(re.search(pattern, content, re.MULTILINE))


def analyze_template(file_path: Path) -> TemplateInfo:
    """Analyze a template file to determine what's missing."""
    content = file_path.read_text(encoding='utf-8')
    
    title = detect_template_title(content) or file_path.stem
    has_std_header = has_section(content, 'STANDARD HEADER')
    has_doc_control = has_section(content, 'DOCUMENT CONTROL')
    has_approvals = has_section(content, 'APPROVALS')
    
    needs_fix = not (has_std_header and has_doc_control and has_approvals)
    
    return TemplateInfo(
        path=file_path,
        title=title,
        has_standard_header=has_std_header,
        has_document_control=has_doc_control,
        has_approvals=has_approvals,
        needs_fix=needs_fix
    )


def generate_header_sections() -> str:
    """Generate the complete EN 50128 mandatory header structure."""
    return """**DOCUMENT ID**: DOC-[TYPE]-[YYYY]-[NNN]  
**VERSION**: 1.0  
**DATE**: YYYY-MM-DD  
**STATUS**: Draft  
**CLASSIFICATION**: Internal / Confidential / Public  
**TEMPLATE VERSION**: 2.0  
**REFERENCE**: EN 50128:2011 Section [X.Y]

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Project** | [Project Name] |
| **Prepared by** | [Author Name / Role] |
| **Reviewed by** | [Reviewer Name / Role] |
| **Approved by** | [Approver Name / Role] |
| **SIL Level** | [0 / 1 / 2 / 3 / 4] |

## DOCUMENT CONTROL

| Version | Date | Author | Reviewer | Changes |
|---------|------|--------|----------|---------|
| 1.0 | YYYY-MM-DD | [Name] | [Name] | Initial version |

## APPROVALS

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Author | [Name] | | |
| Reviewer | [Name] | | |
| Approver | [Name] | | |

**SIL-Specific Requirements**:
- **SIL 0-1**: Author, Reviewer recommended
- **SIL 2**: Author, Reviewer (mandatory), Approver (recommended)
- **SIL 3-4**: Author, Reviewer (mandatory, independent), Approver (mandatory), Verifier (VER) SHALL be independent, Validator (VAL) SHALL be independent

---

## Table of Contents

[To be added based on document structure]

---
"""


def fix_template(template_info: TemplateInfo, dry_run: bool = False) -> Tuple[bool, str]:
    """
    Fix a template by adding missing mandatory sections.
    
    Returns:
        Tuple of (success: bool, message: str)
    """
    content = template_info.path.read_text(encoding='utf-8')
    original_content = content
    
    # Find the first # heading (title)
    lines = content.split('\n')
    title_index = -1
    title_line = None
    
    for i, line in enumerate(lines):
        if line.strip().startswith('# ') and not line.strip().startswith('##'):
            title_index = i
            title_line = line
            break
    
    if title_index == -1:
        return False, f"❌ Could not find title heading in {template_info.path.name}"
    
    # Strategy: Insert header sections right after the title
    # Check what's missing and build the insertion
    sections_to_add = []
    
    if not template_info.has_standard_header or not template_info.has_document_control or not template_info.has_approvals:
        # Add complete header structure
        sections_to_add.append(generate_header_sections())
    
    if sections_to_add:
        # Insert after title
        new_lines = lines[:title_index + 1]  # Keep title
        new_lines.append('')  # Blank line
        new_lines.extend(sections_to_add[0].split('\n'))
        
        # Find where the actual content starts (skip any existing metadata lines)
        content_start_index = title_index + 1
        
        # Skip existing metadata lines (lines starting with **)
        while content_start_index < len(lines):
            line = lines[content_start_index].strip()
            if line and not line.startswith('**') and not line.startswith('##'):
                break
            content_start_index += 1
        
        # Skip the old DOCUMENT CONTROL and APPROVALS if they exist but are incomplete
        # Look for the next ## heading that's NOT STANDARD HEADER, DOCUMENT CONTROL, or APPROVALS
        skip_until_index = content_start_index
        for i in range(content_start_index, len(lines)):
            line = lines[i].strip()
            if line.startswith('## '):
                section_name = line[3:].strip()
                if section_name not in ['STANDARD HEADER', 'DOCUMENT CONTROL', 'APPROVALS']:
                    skip_until_index = i
                    break
        
        # Add the rest of the content
        if skip_until_index < len(lines):
            new_lines.extend(lines[skip_until_index:])
        
        new_content = '\n'.join(new_lines)
        
        if dry_run:
            return True, f"✅ Would fix {template_info.path.name} (dry run)"
        else:
            # Write the fixed content
            template_info.path.write_text(new_content, encoding='utf-8')
            return True, f"✅ Fixed {template_info.path.name}"
    else:
        return True, f"✓ {template_info.path.name} already compliant"


def find_all_templates(base_dir: Path) -> List[Path]:
    """Find all template files in the project."""
    template_paths = []
    
    # Search in .opencode/skills/*/templates/
    skills_dir = base_dir / '.opencode' / 'skills'
    if skills_dir.exists():
        for skill_dir in skills_dir.iterdir():
            if skill_dir.is_dir():
                templates_dir = skill_dir / 'templates'
                if templates_dir.exists():
                    for file in templates_dir.glob('*.md'):
                        # Skip the DOCUMENT-HEADER-TEMPLATE.md itself
                        if 'DOCUMENT-HEADER-TEMPLATE' not in file.name:
                            template_paths.append(file)
                
                # Also check for templates in root of skill dir
                for file in skill_dir.glob('*-template.md'):
                    if 'DOCUMENT-HEADER-TEMPLATE' not in file.name:
                        template_paths.append(file)
    
    return sorted(template_paths)


def main():
    import argparse
    
    parser = argparse.ArgumentParser(
        description='Fix EN 50128 templates by adding mandatory header sections'
    )
    parser.add_argument('--file', type=str, help='Fix a single template file')
    parser.add_argument('--fix-all', action='store_true', help='Fix all failing templates')
    parser.add_argument('--dry-run', action='store_true', help='Preview changes without writing')
    parser.add_argument('--list', action='store_true', help='List all templates that need fixing')
    
    args = parser.parse_args()
    
    # Determine project root
    script_dir = Path(__file__).parent
    project_root = script_dir.parent.parent
    
    if args.file:
        # Fix single file
        file_path = Path(args.file)
        if not file_path.exists():
            print(f"❌ File not found: {file_path}")
            return 1
        
        template_info = analyze_template(file_path)
        if not template_info.needs_fix:
            print(f"✓ {file_path.name} is already compliant")
            return 0
        
        success, message = fix_template(template_info, dry_run=args.dry_run)
        print(message)
        return 0 if success else 1
    
    elif args.fix_all or args.list:
        # Find all templates
        print("🔍 Finding all templates...")
        all_templates = find_all_templates(project_root)
        print(f"✅ Found {len(all_templates)} templates\n")
        
        # Analyze all templates
        print("📊 Analyzing templates...")
        templates_to_fix = []
        compliant_templates = []
        
        for template_path in all_templates:
            template_info = analyze_template(template_path)
            if template_info.needs_fix:
                templates_to_fix.append(template_info)
            else:
                compliant_templates.append(template_info)
        
        print(f"✅ Analysis complete:")
        print(f"   - {len(templates_to_fix)} templates need fixing")
        print(f"   - {len(compliant_templates)} templates are compliant\n")
        
        if args.list:
            print("📋 Templates that need fixing:")
            for i, template in enumerate(templates_to_fix, 1):
                missing = []
                if not template.has_standard_header:
                    missing.append("STANDARD HEADER")
                if not template.has_document_control:
                    missing.append("DOCUMENT CONTROL")
                if not template.has_approvals:
                    missing.append("APPROVALS")
                print(f"{i:2}. {template.path.name:60} Missing: {', '.join(missing)}")
            return 0
        
        if args.fix_all:
            print("🔧 Fixing templates...")
            fixed_count = 0
            failed_count = 0
            
            for template in templates_to_fix:
                success, message = fix_template(template, dry_run=args.dry_run)
                print(f"   {message}")
                if success:
                    fixed_count += 1
                else:
                    failed_count += 1
            
            print(f"\n📊 Summary:")
            print(f"   ✅ Fixed: {fixed_count}")
            print(f"   ❌ Failed: {failed_count}")
            print(f"   ✓ Already compliant: {len(compliant_templates)}")
            
            if args.dry_run:
                print(f"\n💡 This was a dry run. Run without --dry-run to apply changes.")
            else:
                print(f"\n✅ All fixes applied! Run validation tool to verify.")
            
            return 0 if failed_count == 0 else 1
    
    else:
        parser.print_help()
        return 1


if __name__ == '__main__':
    sys.exit(main())
