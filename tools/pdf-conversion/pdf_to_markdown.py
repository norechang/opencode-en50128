#!/usr/bin/env python3
"""
PDF to Markdown Converter using PyMuPDF4LLM
Converts EN 50128 railway standards PDFs to LLM-friendly Markdown format

Usage:
    python3 pdf_to_markdown.py <pdf_file>           # Convert single PDF
    python3 pdf_to_markdown.py --all                # Convert all PDFs in std/
    python3 pdf_to_markdown.py --check              # Check conversion status
"""

import sys
import argparse
from pathlib import Path
from datetime import datetime
import re

try:
    import pymupdf4llm
except ImportError:
    print("Error: pymupdf4llm not installed")
    print("Install with: pip3 install -r tools/pdf-conversion/requirements.txt")
    sys.exit(1)

from table_formatter import format_markdown_tables


class PDFConverter:
    """Converts PDF files to LLM-optimized Markdown"""
    
    def __init__(self, std_dir="std"):
        self.std_dir = Path(std_dir)
        self.stats = {
            'converted': 0,
            'skipped': 0,
            'failed': 0,
            'total_size': 0
        }
    
    def convert_pdf(self, pdf_path, output_path=None, force=False):
        """
        Convert a single PDF to Markdown
        
        Args:
            pdf_path: Path to PDF file
            output_path: Output path (default: same name with .md extension)
            force: Force conversion even if output exists and is newer
        
        Returns:
            True if successful, False otherwise
        """
        pdf_path = Path(pdf_path)
        
        if not pdf_path.exists():
            print(f"❌ Error: PDF file not found: {pdf_path}")
            self.stats['failed'] += 1
            return False
        
        # Determine output path
        if output_path is None:
            output_path = pdf_path.with_suffix('.md')
        else:
            output_path = Path(output_path)
        
        # Check if conversion needed
        if not force and output_path.exists():
            pdf_mtime = pdf_path.stat().st_mtime
            md_mtime = output_path.stat().st_mtime
            if md_mtime > pdf_mtime:
                print(f"⏭️  Skipping {pdf_path.name} (Markdown is up-to-date)")
                self.stats['skipped'] += 1
                return True
        
        print(f"📄 Converting: {pdf_path.name}")
        print(f"   Output: {output_path}")
        
        try:
            # Convert PDF to Markdown using PyMuPDF4LLM
            print("   ⏳ Converting PDF to Markdown...")
            md_text = pymupdf4llm.to_markdown(
                str(pdf_path),
                page_chunks=False,       # Keep document as one piece
                write_images=False,      # Standards don't need images
                embed_images=False,
                show_progress=False,     # We'll handle our own progress
                margins=(0, 50, 0, 50),  # Better table detection
                dpi=150                  # Good quality for text
            )
            
            # Add metadata header
            print("   ⏳ Adding metadata...")
            md_text = self._add_metadata(md_text, pdf_path)
            
            # Format tables
            print("   ⏳ Formatting tables...")
            md_text = format_markdown_tables(md_text)
            
            # Clean up common issues
            md_text = self._clean_text(md_text)
            
            # Write output
            print("   ⏳ Writing output file...")
            output_path.write_text(md_text, encoding='utf-8')
            
            # Report success
            file_size = output_path.stat().st_size
            self.stats['converted'] += 1
            self.stats['total_size'] += file_size
            
            print(f"   ✅ Success! Generated {file_size:,} bytes")
            print()
            
            return True
            
        except Exception as e:
            print(f"   ❌ Error: {str(e)}")
            self.stats['failed'] += 1
            return False
    
    def _add_metadata(self, markdown_text, pdf_path):
        """Add YAML frontmatter metadata to the Markdown"""
        pdf_path = Path(pdf_path)
        
        # Extract title from first heading or filename
        title = self._extract_title(markdown_text, pdf_path)
        
        # Get PDF stats
        pdf_size = pdf_path.stat().st_size
        
        # Try to get page count (simple heuristic)
        page_count = self._estimate_page_count(markdown_text)
        
        metadata = f"""---
title: {title}
source: {pdf_path.name}
converted: {datetime.now().strftime('%Y-%m-%d')}
pdf_size: {pdf_size:,} bytes
pages: ~{page_count}
---

"""
        
        return metadata + markdown_text
    
    def _extract_title(self, markdown_text, pdf_path):
        """Extract document title from Markdown or filename"""
        # Try to find first heading
        heading_match = re.search(r'^#\s+(.+)$', markdown_text, re.MULTILINE)
        if heading_match:
            return heading_match.group(1).strip()
        
        # Fall back to filename
        return pdf_path.stem.replace('-', ' ').replace('_', ' ')
    
    def _estimate_page_count(self, markdown_text):
        """Estimate page count (rough heuristic)"""
        # Look for page markers if present
        page_markers = re.findall(r'Page\s+(\d+)', markdown_text, re.IGNORECASE)
        if page_markers:
            try:
                return max(int(p) for p in page_markers)
            except:
                pass
        
        # Fallback: estimate based on text length
        # Rough estimate: 3000 chars per page
        return max(1, len(markdown_text) // 3000)
    
    def _clean_text(self, markdown_text):
        """Clean up common conversion issues"""
        # Remove excessive blank lines (more than 2 consecutive)
        markdown_text = re.sub(r'\n{4,}', '\n\n\n', markdown_text)
        
        # Fix common OCR issues in EN standards
        # (Add more patterns as needed)
        
        # Normalize section numbering spacing
        markdown_text = re.sub(r'(\d+)\.(\d+)\.(\d+)\s+', r'\1.\2.\3 ', markdown_text)
        
        return markdown_text
    
    def convert_all(self, force=False):
        """Convert all PDF files in the std/ directory"""
        pdf_files = sorted(self.std_dir.glob('*.pdf'))
        
        if not pdf_files:
            print(f"❌ No PDF files found in {self.std_dir}/")
            return False
        
        print(f"📚 Found {len(pdf_files)} PDF file(s) in {self.std_dir}/")
        print()
        
        for pdf_file in pdf_files:
            self.convert_pdf(pdf_file, force=force)
        
        return True
    
    def check_status(self):
        """Check conversion status of PDFs"""
        pdf_files = sorted(self.std_dir.glob('*.pdf'))
        
        if not pdf_files:
            print(f"❌ No PDF files found in {self.std_dir}/")
            return
        
        print(f"📊 Conversion Status in {self.std_dir}/:")
        print()
        
        for pdf_file in pdf_files:
            md_file = pdf_file.with_suffix('.md')
            
            if md_file.exists():
                pdf_mtime = datetime.fromtimestamp(pdf_file.stat().st_mtime)
                md_mtime = datetime.fromtimestamp(md_file.stat().st_mtime)
                md_size = md_file.stat().st_size
                
                if md_mtime > pdf_mtime:
                    status = "✅ Up-to-date"
                else:
                    status = "⚠️  Outdated (PDF newer)"
                
                print(f"  {pdf_file.name}")
                print(f"    Status: {status}")
                print(f"    Markdown: {md_size:,} bytes")
                print(f"    Last converted: {md_mtime.strftime('%Y-%m-%d %H:%M:%S')}")
            else:
                print(f"  {pdf_file.name}")
                print(f"    Status: ❌ Not converted")
            print()
    
    def print_summary(self):
        """Print conversion summary"""
        print("="*60)
        print("Conversion Summary:")
        print(f"  ✅ Converted: {self.stats['converted']} file(s)")
        print(f"  ⏭️  Skipped: {self.stats['skipped']} file(s)")
        print(f"  ❌ Failed: {self.stats['failed']} file(s)")
        if self.stats['total_size'] > 0:
            print(f"  📊 Total Markdown: {self.stats['total_size']:,} bytes")
        print("="*60)


def main():
    parser = argparse.ArgumentParser(
        description='Convert EN 50128 PDF standards to Markdown',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  %(prog)s std/EN50128-2011.pdf          # Convert single file
  %(prog)s --all                         # Convert all PDFs
  %(prog)s --all --force                 # Force reconvert all
  %(prog)s --check                       # Check status
        """
    )
    
    parser.add_argument(
        'pdf_file',
        nargs='?',
        help='PDF file to convert'
    )
    
    parser.add_argument(
        '--all',
        action='store_true',
        help='Convert all PDFs in std/ directory'
    )
    
    parser.add_argument(
        '--check',
        action='store_true',
        help='Check conversion status without converting'
    )
    
    parser.add_argument(
        '--force',
        action='store_true',
        help='Force conversion even if Markdown exists and is newer'
    )
    
    parser.add_argument(
        '--std-dir',
        default='std',
        help='Directory containing PDF files (default: std)'
    )
    
    args = parser.parse_args()
    
    # Create converter
    converter = PDFConverter(std_dir=args.std_dir)
    
    # Execute command
    if args.check:
        converter.check_status()
    elif args.all:
        converter.convert_all(force=args.force)
        converter.print_summary()
    elif args.pdf_file:
        success = converter.convert_pdf(args.pdf_file, force=args.force)
        sys.exit(0 if success else 1)
    else:
        parser.print_help()
        sys.exit(1)


if __name__ == "__main__":
    main()
