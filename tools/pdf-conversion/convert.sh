#!/bin/bash
# Wrapper script for PDF to Markdown converter
# Uses project-wide virtual environment

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
VENV_PYTHON="$PROJECT_ROOT/venv/bin/python3"
CONVERTER_SCRIPT="$SCRIPT_DIR/pdf_to_markdown.py"

# Check if venv exists
if [ ! -f "$VENV_PYTHON" ]; then
    echo "Error: Virtual environment not found at $PROJECT_ROOT/venv"
    echo "Please create it first:"
    echo "  python3 -m venv venv"
    echo "  venv/bin/pip install -r tools/pdf-conversion/requirements.txt"
    exit 1
fi

# Run the converter with the venv Python
exec "$VENV_PYTHON" "$CONVERTER_SCRIPT" "$@"
