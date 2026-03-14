#!/usr/bin/env python3
"""
EN 50128 Template Cleanup Script

Removes duplicate old header sections from templates that were fixed by the batch fixer.
The batch fixer added new mandatory headers at the top, but some templates had old
duplicate sections (Document Control, Approvals) that need to be removed.

Usage:
    python3 template_cleanup.py --file <template_file>    # Clean single template
    python3 template_cleanup.py --clean-all               # Clean all templates
    python3 template_cleanup.py --dry-run                 # Preview changes
"""

import os
import re
import sys
from pathlib import Path
from typing import List, Tuple, Optional
from dataclasses import dataclass


@dataclass
class DuplicateSection:
    """Information about a duplicate section to remove."""
    name: str
    start_line: int
    end_line: int


def find_duplicate_sections(content: str) -> List[DuplicateSection]:
    """
    Find duplicate old header sections that appear after the new mandatory headers.
    
    Strategy:
    1. Find the end of the new mandatory headers (marked by "## Table of Contents" or "---")
    2. Look for old duplicate sections after that:
       - "## Document Control" (not "## DOCUMENT CONTROL")
       - "## Approvals" or "## Approvals (SIL-Dependent)" (not "## APPROVALS")
    3. Identify the range of lines to remove (section + content until next ## or ---)
    """
    lines = content.split('\n')
    duplicates = []
    
    # Find where new mandatory headers end
    # Look for "## Table of Contents" or the separator "---" after APPROVALS
    new_header_end = -1
    found_approvals = False
    
    for i, line in enumerate(lines):
        if line.strip() == '## APPROVALS':
            found_approvals = True
        elif found_approvals and (line.strip() == '---' or line.strip().startswith('## Table of Contents')):
            new_header_end = i
            break
    
    if new_header_end == -1:
        # Fallback: look for first --- after line 30
        for i in range(30, len(lines)):
            if lines[i].strip() == '---':
                new_header_end = i
                break
    
    if new_header_end == -1:
        return duplicates  # No clear separation, don't remove anything
    
    # Now look for duplicate sections AFTER new_header_end
    i = new_header_end + 1
    while i < len(lines):
        line = lines[i].strip()
        
        # Check for duplicate "## Document Control" (case-sensitive, not "DOCUMENT CONTROL")
        if re.match(r'^## Document Control\s*$', line):
            # Find end of this section (next ## heading or ---)
            section_end = i + 1
            while section_end < len(lines):
                next_line = lines[section_end].strip()
                if next_line.startswith('## ') or next_line == '---':
                    # Include the separator if it's ---
                    if next_line == '---':
                        section_end += 1
                    break
                section_end += 1
            
            duplicates.append(DuplicateSection(
                name='Document Control (old)',
                start_line=i,
                end_line=section_end
            ))
            i = section_end
            continue
        
        # Check for duplicate "## Approvals" or "## Approvals (SIL-Dependent)"
        if re.match(r'^## Approvals\s*(\(SIL-Dependent\))?\s*$', line):
            # Find end of this section (next ## heading or ---)
            section_end = i + 1
            while section_end < len(lines):
                next_line = lines[section_end].strip()
                if next_line.startswith('## ') or next_line == '---':
                    # Include the separator if it's ---
                    if next_line == '---':
                        section_end += 1
                    break
                section_end += 1
            
            duplicates.append(DuplicateSection(
                name='Approvals (old)',
                start_line=i,
                end_line=section_end
            ))
            i = section_end
            continue
        
        i += 1
    
    return duplicates


def remove_duplicate_sections(content: str, duplicates: List[DuplicateSection]) -> str:
    """Remove duplicate sections from content."""
    if not duplicates:
        return content
    
    lines = content.split('\n')
    
    # Sort duplicates by start_line in reverse order (remove from bottom to top)
    duplicates_sorted = sorted(duplicates, key=lambda d: d.start_line, reverse=True)
    
    for dup in duplicates_sorted:
        # Remove lines from start_line to end_line (exclusive)
        del lines[dup.start_line:dup.end_line]
    
    return '\n'.join(lines)


def clean_template(file_path: Path, dry_run: bool = False) -> Tuple[bool, str, int]:
    """
    Clean a template by removing duplicate old header sections.
    
    Returns:
        Tuple of (success: bool, message: str, num_removed: int)
    """
    try:
        content = file_path.read_text(encoding='utf-8')
        duplicates = find_duplicate_sections(content)
        
        if not duplicates:
            return True, f"✓ {file_path.name} - No duplicates found", 0
        
        if dry_run:
            dup_names = ', '.join([d.name for d in duplicates])
            return True, f"✅ Would remove from {file_path.name}: {dup_names} ({len(duplicates)} sections)", len(duplicates)
        
        # Remove duplicates
        cleaned_content = remove_duplicate_sections(content, duplicates)
        
        # Write back
        file_path.write_text(cleaned_content, encoding='utf-8')
        
        dup_names = ', '.join([d.name for d in duplicates])
        return True, f"✅ Cleaned {file_path.name}: Removed {dup_names} ({len(duplicates)} sections)", len(duplicates)
    
    except Exception as e:
        return False, f"❌ Error cleaning {file_path.name}: {e}", 0


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
        description='Clean EN 50128 templates by removing duplicate old header sections'
    )
    parser.add_argument('--file', type=str, help='Clean a single template file')
    parser.add_argument('--clean-all', action='store_true', help='Clean all templates')
    parser.add_argument('--dry-run', action='store_true', help='Preview changes without writing')
    parser.add_argument('--analyze', action='store_true', help='Analyze templates to find duplicates')
    
    args = parser.parse_args()
    
    # Determine project root
    script_dir = Path(__file__).parent
    project_root = script_dir.parent.parent
    
    if args.file:
        # Clean single file
        file_path = Path(args.file)
        if not file_path.exists():
            print(f"❌ File not found: {file_path}")
            return 1
        
        success, message, num_removed = clean_template(file_path, dry_run=args.dry_run)
        print(message)
        return 0 if success else 1
    
    elif args.clean_all or args.analyze:
        # Find all templates
        print("🔍 Finding all templates...")
        all_templates = find_all_templates(project_root)
        print(f"✅ Found {len(all_templates)} templates\n")
        
        if args.analyze:
            print("📊 Analyzing for duplicate sections...\n")
            templates_with_duplicates = []
            
            for template_path in all_templates:
                content = template_path.read_text(encoding='utf-8')
                duplicates = find_duplicate_sections(content)
                if duplicates:
                    templates_with_duplicates.append((template_path, duplicates))
            
            if templates_with_duplicates:
                print(f"📋 Found {len(templates_with_duplicates)} templates with duplicate sections:\n")
                for i, (template_path, duplicates) in enumerate(templates_with_duplicates, 1):
                    dup_list = ', '.join([f"{d.name} (lines {d.start_line}-{d.end_line})" for d in duplicates])
                    print(f"{i:2}. {template_path.name:60} - {dup_list}")
            else:
                print("✅ No templates have duplicate sections!")
            
            return 0
        
        if args.clean_all:
            print("🧹 Cleaning templates...")
            cleaned_count = 0
            no_duplicates_count = 0
            failed_count = 0
            total_sections_removed = 0
            
            for template_path in all_templates:
                success, message, num_removed = clean_template(template_path, dry_run=args.dry_run)
                print(f"   {message}")
                
                if success:
                    if num_removed > 0:
                        cleaned_count += 1
                        total_sections_removed += num_removed
                    else:
                        no_duplicates_count += 1
                else:
                    failed_count += 1
            
            print(f"\n📊 Summary:")
            print(f"   ✅ Cleaned: {cleaned_count} templates")
            print(f"   ✓ No duplicates: {no_duplicates_count} templates")
            print(f"   ❌ Failed: {failed_count} templates")
            print(f"   🗑️  Total sections removed: {total_sections_removed}")
            
            if args.dry_run:
                print(f"\n💡 This was a dry run. Run without --dry-run to apply changes.")
            else:
                print(f"\n✅ All cleanup complete! Run validation tool to verify.")
            
            return 0 if failed_count == 0 else 1
    
    else:
        parser.print_help()
        return 1


if __name__ == '__main__':
    sys.exit(main())
