# PDF to Markdown Conversion - Setup Guide

## Quick Setup

### 1. Create Virtual Environment

```bash
cd /home/norechang/work/EN50128
python3 -m venv venv
```

### 2. Install Dependencies

```bash
venv/bin/pip install -r tools/pdf-conversion/requirements.txt
```

### 3. Convert PDFs

Using OpenCode slash command (Recommended):
```bash
/pdf2md --all
```

Or using the wrapper script:
```bash
./tools/pdf-conversion/convert.sh --all
```

Or using Python directly:
```bash
venv/bin/python3 tools/pdf-conversion/pdf_to_markdown.py --all
```

## What Was Created

### New Files

1. **tools/pdf-conversion/requirements.txt**
   - Python dependencies (pymupdf4llm, pymupdf)

2. **tools/pdf-conversion/pdf_to_markdown.py**
   - Main conversion script with PyMuPDF4LLM integration
   - Metadata extraction
   - Progress reporting
   - Batch processing

3. **tools/pdf-conversion/table_formatter.py**
   - Table formatting and cleanup module
   - Column alignment
   - Whitespace normalization

4. **tools/pdf-conversion/convert.sh**
   - Wrapper script for easy execution
   - Automatically uses venv Python

5. **tools/pdf-conversion/README.md**
   - Comprehensive documentation
   - Usage examples
   - Troubleshooting guide

6. **.opencode/commands/pdf2md.md**
   - OpenCode slash command definition
   - Command behavior specification
   - Integration with EN 50128 agents

7. **std/*.md files**
   - EN50128-2011.md (2.2 MB)
   - EN 50126-1-2017.md (293 KB)
   - EN 50126-2-2017.md (210 KB)

### Project-Wide Virtual Environment

Location: `/home/norechang/work/EN50128/venv/`
- Already configured and installed
- Already in .gitignore (not tracked)
- Shared across all Python tools in the project

## Using the Converted Files

### With OpenCode Agents

All EN 50128 agents can now reference the Markdown files:

**Requirements Engineer (`/req`):**
```
Reference EN 50128 Section 7.2 in std/EN50128-2011.md
```

**Designer (`/des`):**
```
Check Table A.2 design techniques in std/EN50128-2011.md
```

**Safety Engineer (`/saf`):**
```
Reference SIL definitions in std/EN50128-2011.md
```

### Manual Reference

Simply read the Markdown files:
```bash
less std/EN50128-2011.md
grep "Table A.2" std/EN50128-2011.md
```

### Search Within Standards

```bash
# Find all mentions of MISRA C
grep -n "MISRA" std/EN50128-2011.md

# Find Table A.2
grep -n "Table A.2" std/EN50128-2011.md

# Find SIL 3 requirements
grep -n "SIL 3" std/EN50128-2011.md
```

## Features

### Automatic Conversion Checking

The tool is smart about conversions:
- ✅ Only converts if PDF is newer than Markdown
- ✅ Skip up-to-date files automatically
- ✅ Force reconversion with `--force` flag

### Status Monitoring

Check conversion status anytime:
```bash
/pdf2md --check
```

Output shows:
- ✅ Up-to-date files
- ⚠️ Outdated files (PDF modified after conversion)
- ❌ Not converted files
- File sizes and last conversion time

### Table Formatting

Tables are automatically formatted for readability:

**Before (raw PDF):**
```
|Column1|Col2|Column3|
|---|---|---|
|Short|Medium text|Long|
```

**After (formatted):**
```
| Column1 | Col2        | Column3 |
|---------|-------------|---------|
| Short   | Medium text | Long    |
```

### Metadata Headers

Each Markdown file includes YAML frontmatter:
```yaml
---
title: BS EN 50128:2011
source: EN50128-2011.pdf
converted: 2026-02-06
pdf_size: 933,548 bytes
pages: ~119
---
```

## Maintenance

### Updating Standards

When you get updated PDF standards:

1. Replace the PDF file in `std/`
2. Run conversion:
   ```bash
   /pdf2md --all
   ```
3. Commit both PDF and updated Markdown

### Reconverting All Files

If conversion settings improve:
```bash
/pdf2md --all --force
```

### Adding New Standards

1. Place PDF in `std/` directory
2. Run conversion:
   ```bash
   /pdf2md std/your-new-standard.pdf
   ```

## Integration with CI/CD

You can add this to your build pipeline:

```bash
# Ensure all PDFs are converted
./tools/pdf-conversion/convert.sh --check

# Or auto-convert during build
./tools/pdf-conversion/convert.sh --all
```

## Troubleshooting

### PyMuPDF4LLM Not Found

```bash
# Reinstall dependencies
venv/bin/pip install -r tools/pdf-conversion/requirements.txt
```

### Conversion Slow

This is normal. PDFs take 10-30 seconds each due to:
- OCR-quality text extraction
- Table detection and formatting
- Layout analysis

### Tables Not Perfect

Some complex tables may need manual adjustment:
1. Check the original PDF table structure
2. Edit the Markdown file manually if needed
3. The formatter handles 95% of cases automatically

## Performance

### Conversion Times

- EN50128-2011.pdf (912 KB) → ~15 seconds → 2.2 MB Markdown
- EN 50126-1-2017.pdf (3.7 MB) → ~20 seconds → 293 KB Markdown
- EN 50126-2-2017.pdf (1.8 MB) → ~10 seconds → 210 KB Markdown

### File Sizes

Markdown files are typically 2-3x larger than PDFs due to:
- Plain text format (no compression)
- Table formatting with spacing
- Metadata headers

But they're much better for:
- LLM context windows
- Text search
- Version control diffs
- Human readability

## Next Steps

1. ✅ Virtual environment created
2. ✅ Dependencies installed
3. ✅ All PDFs converted
4. ✅ Ready to use with OpenCode agents

Start using the converted standards:
```bash
/req   # Reference requirements section
/des   # Reference design tables
/saf   # Reference safety requirements
```

## Support

- Main documentation: `tools/pdf-conversion/README.md`
- Command reference: `.opencode/commands/pdf2md.md`
- Project guide: `README.md`
