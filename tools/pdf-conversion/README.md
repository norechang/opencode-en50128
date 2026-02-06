# PDF to Markdown Converter

Convert EN 50128 railway standard PDFs to LLM-friendly Markdown format using PyMuPDF4LLM.

## Overview

This tool converts PDF standards documents (EN 50128, EN 50126) into Markdown format optimized for:
- LLM context and AI agent analysis
- Easy reference during development
- Integration with OpenCode EN 50128 agent skills
- Standard compliance verification

## Features

- **LLM-Optimized**: Uses PyMuPDF4LLM for high-quality conversion
- **Table Formatting**: Automatic table cleanup and formatting
- **Metadata Extraction**: Adds YAML frontmatter with document info
- **Smart Updates**: Only converts when PDF is newer than Markdown
- **Batch Processing**: Convert all PDFs at once or individually
- **Status Checking**: View conversion status of all documents

## Installation

### Prerequisites

- Python 3.7 or higher
- pip3

### Install Dependencies

```bash
pip3 install -r tools/pdf-conversion/requirements.txt
```

This installs:
- `pymupdf4llm` - PDF to Markdown conversion optimized for LLMs
- `pymupdf` - PDF processing library

## Usage

### OpenCode Slash Command (Recommended)

Within OpenCode, use the `/pdf2md` command:

```bash
# Convert all PDFs
/pdf2md --all

# Convert single PDF
/pdf2md std/EN50128-2011.pdf

# Check conversion status
/pdf2md --check

# Force reconversion
/pdf2md --all --force
```

### Direct Script Usage

```bash
# Convert single PDF
python3 tools/pdf-conversion/pdf_to_markdown.py std/EN50128-2011.pdf

# Convert all PDFs in std/ directory
python3 tools/pdf-conversion/pdf_to_markdown.py --all

# Check status
python3 tools/pdf-conversion/pdf_to_markdown.py --check

# Force reconversion even if Markdown exists
python3 tools/pdf-conversion/pdf_to_markdown.py --all --force

# Use custom directory
python3 tools/pdf-conversion/pdf_to_markdown.py --all --std-dir /path/to/pdfs
```

## Output Format

### Directory Structure

```
std/
├── EN50128-2011.pdf          # Original PDF
├── EN50128-2011.md           # Generated Markdown
├── EN 50126-1-2017.pdf
├── EN 50126-1-2017.md
├── EN 50126-2-2017.pdf
└── EN 50126-2-2017.md
```

### Markdown Format

Each converted file includes:

1. **YAML Frontmatter** - Metadata about the document
```yaml
---
title: EN 50128:2011 - Railway applications — Software for railway control...
source: EN50128-2011.pdf
converted: 2026-02-06
pdf_size: 933,548 bytes
pages: ~103
---
```

2. **Formatted Content** - Document text with:
   - Preserved heading hierarchy
   - Formatted tables with proper alignment
   - Section numbers and references
   - Clean whitespace

3. **Enhanced Tables** - Tables are automatically formatted for readability:
```markdown
| Technique/Measure      | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 |
|------------------------|-------|-------|-------|-------|-------|
| Defensive Programming  | R     | R     | HR    | HR    | M     |
| Static Analysis        | R     | R     | HR    | M     | M     |
```

## Conversion Process

1. **Check if needed**: Skip if Markdown exists and is newer than PDF (unless `--force`)
2. **Convert PDF**: Use PyMuPDF4LLM with optimal settings
3. **Add metadata**: Insert YAML frontmatter
4. **Format tables**: Clean up and align tables
5. **Clean text**: Remove excessive whitespace
6. **Write output**: Save as UTF-8 Markdown

## Configuration

### Conversion Settings

The script uses these PyMuPDF4LLM settings optimized for standards documents:

```python
pymupdf4llm.to_markdown(
    page_chunks=False,       # Keep document as one piece
    write_images=False,      # Standards don't need images
    embed_images=False,
    margins=(0, 50, 0, 50),  # Better table detection
    dpi=150                  # Good quality for text
)
```

### Table Formatting

The `table_formatter.py` module:
- Normalizes column widths
- Fixes broken table rows
- Improves alignment
- Cleans up whitespace
- Preserves content integrity

## Integration with EN 50128 Agents

The converted Markdown files can be referenced by all EN 50128 OpenCode agents:

| Agent | Use Case |
|-------|----------|
| **Requirements Engineer** (`/req`) | Reference Section 7.2 requirements specification |
| **Designer** (`/des`) | Access Table A.2 design techniques and measures |
| **Implementer** (`/imp`) | Check MISRA C compliance requirements |
| **Tester** (`/tst`) | Verify test coverage requirements by SIL |
| **Safety Engineer** (`/saf`) | Reference SIL definitions and safety tables |
| **Verifier** (`/ver`) | Access verification technique requirements |
| **Validator** (`/val`) | Check validation requirements |
| **Quality Assurance** (`/qua`) | Reference quality assurance standards |

## Examples

### Example 1: First Time Setup

```bash
# Install dependencies
pip3 install -r tools/pdf-conversion/requirements.txt

# Convert all standards
python3 tools/pdf-conversion/pdf_to_markdown.py --all
```

Output:
```
📚 Found 3 PDF file(s) in std/

📄 Converting: EN50128-2011.pdf
   Output: std/EN50128-2011.md
   ⏳ Converting PDF to Markdown...
   ⏳ Adding metadata...
   ⏳ Formatting tables...
   ⏳ Writing output file...
   ✅ Success! Generated 456,789 bytes

📄 Converting: EN 50126-1-2017.pdf
   Output: std/EN 50126-1-2017.md
   ⏳ Converting PDF to Markdown...
   ⏳ Adding metadata...
   ⏳ Formatting tables...
   ⏳ Writing output file...
   ✅ Success! Generated 523,123 bytes

📄 Converting: EN 50126-2-2017.pdf
   Output: std/EN 50126-2-2017.md
   ⏳ Converting PDF to Markdown...
   ⏳ Adding metadata...
   ⏳ Formatting tables...
   ⏳ Writing output file...
   ✅ Success! Generated 234,567 bytes

============================================================
Conversion Summary:
  ✅ Converted: 3 file(s)
  ⏭️  Skipped: 0 file(s)
  ❌ Failed: 0 file(s)
  📊 Total Markdown: 1,214,479 bytes
============================================================
```

### Example 2: Check Status

```bash
python3 tools/pdf-conversion/pdf_to_markdown.py --check
```

Output:
```
📊 Conversion Status in std/:

  EN50128-2011.pdf
    Status: ✅ Up-to-date
    Markdown: 456,789 bytes
    Last converted: 2026-02-06 14:30:00

  EN 50126-1-2017.pdf
    Status: ✅ Up-to-date
    Markdown: 523,123 bytes
    Last converted: 2026-02-06 14:30:15

  EN 50126-2-2017.pdf
    Status: ⚠️  Outdated (PDF newer)
    Markdown: 234,567 bytes
    Last converted: 2026-02-05 10:00:00
```

### Example 3: Update One File

```bash
python3 tools/pdf-conversion/pdf_to_markdown.py std/EN50128-2011.pdf
```

## Troubleshooting

### Error: pymupdf4llm not installed

```bash
pip3 install -r tools/pdf-conversion/requirements.txt
```

### Conversion is slow

- This is normal for large PDFs (10-30 seconds per document)
- PyMuPDF4LLM performs OCR-quality text extraction
- Tables require additional processing

### Tables not formatted correctly

The table formatter handles most cases, but some complex tables may need manual adjustment:
1. Check the original PDF table structure
2. Edit the Markdown file manually if needed
3. Consider adjusting margins in the conversion settings

### PDF not found

Ensure PDFs are in the `std/` directory or specify correct path:
```bash
python3 tools/pdf-conversion/pdf_to_markdown.py --std-dir /path/to/pdfs --all
```

## File Structure

```
tools/pdf-conversion/
├── README.md                    # This file
├── requirements.txt             # Python dependencies
├── pdf_to_markdown.py          # Main conversion script
└── table_formatter.py          # Table formatting module
```

## Safety Considerations

This tool is classified as **support tooling only** per AGENTS.md:

✅ **Permitted Uses:**
- Build automation and tooling
- Documentation generation
- Analysis and reporting
- Development support

❌ **NOT Permitted:**
- Safety-critical functions
- Code deployed to target system
- Software subject to SIL requirements

The tool:
- Does not modify source code
- Does not affect C compilation
- Provides reference documentation only
- Follows EN 50128 Python usage guidelines

## Development

### Testing Table Formatter

```bash
python3 tools/pdf-conversion/table_formatter.py
```

This runs a simple test of the table formatting functionality.

### Extending the Tool

To add new features:

1. **Custom post-processing**: Edit `_clean_text()` in `pdf_to_markdown.py`
2. **Enhanced metadata**: Modify `_add_metadata()` function
3. **Additional formats**: Extend with new output formats (HTML, etc.)
4. **Section extraction**: Add functions to extract specific sections

## License

This tool is part of the EN50128 project. See main LICENSE file.

## References

- [PyMuPDF4LLM GitHub](https://github.com/pymupdf/pymupdf4llm)
- [PyMuPDF Documentation](https://pymupdf.readthedocs.io/)
- EN 50128:2011 - Railway Software Standard
- EN 50126:2017 - RAMS Standard

## Support

For issues or questions:
1. Check this README
2. Review `.opencode/commands/pdf2md.md` for command usage
3. See main project CONTRIBUTING.md
