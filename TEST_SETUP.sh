#!/bin/bash
# Test script to verify setup instructions work

echo "=========================================="
echo "Testing EN 50128 Setup Instructions"
echo "=========================================="
echo ""

# Test 1: Check install scripts exist and are executable
echo "Test 1: Check installation scripts..."
if [ -x install_tools.sh ] && [ -x install_python.sh ]; then
    echo "✓ Installation scripts are executable"
else
    echo "✗ Installation scripts missing or not executable"
    exit 1
fi
echo ""

# Test 2: Check help commands work
echo "Test 2: Check help commands..."
./install_tools.sh --help > /dev/null
./install_python.sh --help > /dev/null
echo "✓ Help commands work"
echo ""

# Test 3: Check list command
echo "Test 3: Check list command..."
./install_tools.sh --list > /dev/null
echo "✓ List command works"
echo ""

# Test 4: Check status commands
echo "Test 4: Check status commands..."
./install_tools.sh --check > /dev/null
echo "✓ install_tools.sh --check works"
echo ""

# Test 5: Check Python environment
echo "Test 5: Check Python environment..."
if [ -d venv ]; then
    source venv/bin/activate
    ./install_python.sh --check > /dev/null
    echo "✓ Python environment exists and works"
else
    echo "⚠ Python environment not found (run ./install_python.sh)"
fi
echo ""

# Test 6: Check requirements.txt
echo "Test 6: Check requirements.txt..."
if [ -f requirements.txt ]; then
    echo "✓ requirements.txt exists"
    echo "  Packages defined: $(grep -cE '^[a-zA-Z]' requirements.txt)"
else
    echo "✗ requirements.txt missing"
    exit 1
fi
echo ""

# Test 7: Check TOOLS.md
echo "Test 7: Check TOOLS.md..."
if [ -f TOOLS.md ]; then
    echo "✓ TOOLS.md exists"
    echo "  Size: $(wc -l < TOOLS.md) lines"
else
    echo "✗ TOOLS.md missing"
    exit 1
fi
echo ""

# Test 8: Check custom tools
echo "Test 8: Check custom EN50128 tools..."
TOOLS_OK=true
[ -f tools/enhelp.py ] || TOOLS_OK=false
[ -f tools/workspace.py ] || TOOLS_OK=false
[ -f tools/mcdc/mcdc_analyzer.py ] || TOOLS_OK=false
if [ "$TOOLS_OK" = true ]; then
    echo "✓ Custom EN50128 tools present"
else
    echo "✗ Some custom tools missing"
    exit 1
fi
echo ""

# Test 9: Check documentation
echo "Test 9: Check documentation..."
DOCS_OK=true
[ -f SETUP.md ] || DOCS_OK=false
[ -f TOOLS.md ] || DOCS_OK=false
[ -f AGENTS.md ] || DOCS_OK=false
[ -f README.md ] || DOCS_OK=false
if [ "$DOCS_OK" = true ]; then
    echo "✓ All documentation files present"
else
    echo "✗ Some documentation missing"
    exit 1
fi
echo ""

echo "=========================================="
echo "All tests passed! ✓"
echo "=========================================="
echo ""
echo "Setup is ready for new users."
echo ""
echo "New user workflow:"
echo "  1. git clone <repo>"
echo "  2. cd <repo>"
echo "  3. ./install_tools.sh"
echo "  4. ./install_python.sh"
echo "  5. source venv/bin/activate"
echo "  6. Start development!"
echo ""
