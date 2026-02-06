#!/usr/bin/env python3
"""
Table Formatter for PyMuPDF4LLM Output
Enhances table formatting in converted Markdown for better LLM readability
"""

import re


class TableFormatter:
    """Formats and cleans up Markdown tables from PDF conversion"""
    
    def __init__(self):
        self.table_pattern = re.compile(
            r'(\|[^\n]+\|[\n\r]+)(\|[-:\s|]+\|[\n\r]+)((?:\|[^\n]+\|[\n\r]+)+)',
            re.MULTILINE
        )
    
    def format_tables(self, markdown_text):
        """
        Main entry point: format all tables in the Markdown text
        
        Args:
            markdown_text: Raw Markdown text with tables
        
        Returns:
            Formatted Markdown text
        """
        # Find all tables
        formatted = markdown_text
        
        # Process each table
        formatted = self.table_pattern.sub(self._format_single_table, formatted)
        
        # Clean up table-related whitespace issues
        formatted = self._clean_table_whitespace(formatted)
        
        return formatted
    
    def _format_single_table(self, match):
        """Format a single table match"""
        header = match.group(1)
        separator = match.group(2)
        rows = match.group(3)
        
        # Parse table structure
        header_cells = self._parse_row(header)
        row_list = [self._parse_row(row) for row in rows.strip().split('\n') if row.strip()]
        
        if not header_cells:
            return match.group(0)  # Return original if parsing fails
        
        # Calculate column widths
        num_cols = len(header_cells)
        col_widths = [len(cell) for cell in header_cells]
        
        for row in row_list:
            for i, cell in enumerate(row):
                if i < num_cols:
                    col_widths[i] = max(col_widths[i], len(cell))
        
        # Minimum width per column
        col_widths = [max(w, 3) for w in col_widths]
        
        # Build formatted table
        formatted_table = []
        
        # Header
        formatted_header = '| ' + ' | '.join(
            cell.ljust(col_widths[i]) for i, cell in enumerate(header_cells)
        ) + ' |'
        formatted_table.append(formatted_header)
        
        # Separator
        formatted_separator = '|' + '|'.join(
            '-' * (col_widths[i] + 2) for i in range(num_cols)
        ) + '|'
        formatted_table.append(formatted_separator)
        
        # Rows
        for row in row_list:
            # Pad row if it has fewer cells than header
            padded_row = row + [''] * (num_cols - len(row))
            formatted_row = '| ' + ' | '.join(
                cell.ljust(col_widths[i]) for i, cell in enumerate(padded_row[:num_cols])
            ) + ' |'
            formatted_table.append(formatted_row)
        
        return '\n'.join(formatted_table) + '\n'
    
    def _parse_row(self, row_text):
        """Parse a table row into cells"""
        # Remove leading/trailing pipes and split
        row_text = row_text.strip()
        if row_text.startswith('|'):
            row_text = row_text[1:]
        if row_text.endswith('|'):
            row_text = row_text[:-1]
        
        # Split by pipe and clean each cell
        cells = [cell.strip() for cell in row_text.split('|')]
        return cells
    
    def _clean_table_whitespace(self, text):
        """Clean up whitespace around tables"""
        # Ensure blank line before tables
        text = re.sub(r'([^\n])\n(\|[^\n]+\|)', r'\1\n\n\2', text)
        
        # Ensure blank line after tables
        text = re.sub(r'(\|[^\n]+\|)\n([^\n|])', r'\1\n\n\2', text)
        
        # Remove excessive blank lines (more than 2)
        text = re.sub(r'\n{4,}', '\n\n\n', text)
        
        return text
    
    def extract_table_caption(self, text, table_position):
        """
        Try to extract a caption/title for a table from preceding text
        
        Args:
            text: Full document text
            table_position: Position of the table in the text
        
        Returns:
            Caption text or None
        """
        # Look at the 200 characters before the table
        context_start = max(0, table_position - 200)
        context = text[context_start:table_position]
        
        # Look for common caption patterns
        caption_patterns = [
            r'Table\s+[\dA-Z.]+[:\s—-]+([^\n]+)',
            r'Tableau\s+[\dA-Z.]+[:\s—-]+([^\n]+)',  # French
            r'##\s*([^\n]*Table[^\n]*)',
        ]
        
        for pattern in caption_patterns:
            match = re.search(pattern, context, re.IGNORECASE)
            if match:
                return match.group(1).strip()
        
        return None


def format_markdown_tables(markdown_text):
    """
    Convenience function to format tables in Markdown text
    
    Args:
        markdown_text: Markdown text with tables
    
    Returns:
        Formatted Markdown text
    """
    formatter = TableFormatter()
    return formatter.format_tables(markdown_text)


if __name__ == "__main__":
    # Simple test
    test_table = """
Some text before.

| Column 1 | Col 2 | Column 3 |
|---|---|---|
| Short | Medium text | Long content here |
| A | B | C |

Text after.
"""
    
    print("Original:")
    print(test_table)
    print("\nFormatted:")
    print(format_markdown_tables(test_table))
