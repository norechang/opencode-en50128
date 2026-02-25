#!/bin/bash
# EN 50128 Railway Software Development Platform
# Python Virtual Environment Setup Script
#
# This script initializes a Python virtual environment and installs
# all required Python packages for EN 50128 development tools.
#
# Usage:
#   ./install_python.sh              # Initialize venv and install packages
#   ./install_python.sh --upgrade    # Upgrade existing packages
#   ./install_python.sh --check      # Check installation status

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Platform root directory
PLATFORM_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
VENV_DIR="${PLATFORM_ROOT}/venv"
REQUIREMENTS_FILE="${PLATFORM_ROOT}/requirements.txt"

# ============================================================================
# Helper Functions
# ============================================================================

print_header() {
    echo -e "${BLUE}================================================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}================================================================${NC}"
}

print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠ $1${NC}"
}

print_error() {
    echo -e "${RED}✗ $1${NC}"
}

print_info() {
    echo -e "  $1"
}

# ============================================================================
# Check Python Version
# ============================================================================

check_python_version() {
    print_header "Checking Python Installation"
    
    if ! command -v python3 &> /dev/null; then
        print_error "Python 3 is not installed"
        echo ""
        echo "Please install Python 3.8 or higher:"
        echo "  Ubuntu/Debian: sudo apt-get install python3 python3-venv python3-pip"
        echo "  macOS: brew install python3"
        echo "  Other: https://www.python.org/downloads/"
        exit 1
    fi
    
    PYTHON_VERSION=$(python3 --version 2>&1 | awk '{print $2}')
    PYTHON_MAJOR=$(echo $PYTHON_VERSION | cut -d. -f1)
    PYTHON_MINOR=$(echo $PYTHON_VERSION | cut -d. -f2)
    
    print_success "Python ${PYTHON_VERSION} detected"
    
    if [ "$PYTHON_MAJOR" -lt 3 ] || ([ "$PYTHON_MAJOR" -eq 3 ] && [ "$PYTHON_MINOR" -lt 8 ]); then
        print_error "Python 3.8 or higher required (found ${PYTHON_VERSION})"
        exit 1
    fi
    
    # Check python3-venv package
    if ! python3 -m venv --help &> /dev/null; then
        print_error "python3-venv module not found"
        echo ""
        echo "Please install python3-venv:"
        echo "  Ubuntu/Debian: sudo apt-get install python3-venv"
        exit 1
    fi
    
    print_success "python3-venv module available"
    echo ""
}

# ============================================================================
# Create Virtual Environment
# ============================================================================

create_venv() {
    print_header "Creating Virtual Environment"
    
    if [ -d "$VENV_DIR" ]; then
        print_warning "Virtual environment already exists at: ${VENV_DIR}"
        read -p "Do you want to recreate it? (y/N): " -n 1 -r
        echo
        if [[ $REPLY =~ ^[Yy]$ ]]; then
            print_info "Removing existing virtual environment..."
            rm -rf "$VENV_DIR"
        else
            print_info "Keeping existing virtual environment"
            return 0
        fi
    fi
    
    print_info "Creating virtual environment at: ${VENV_DIR}"
    python3 -m venv "$VENV_DIR"
    print_success "Virtual environment created"
    echo ""
}

# ============================================================================
# Install Python Packages
# ============================================================================

install_packages() {
    print_header "Installing Python Packages"
    
    if [ ! -f "$REQUIREMENTS_FILE" ]; then
        print_error "requirements.txt not found at: ${REQUIREMENTS_FILE}"
        exit 1
    fi
    
    print_info "Activating virtual environment..."
    source "${VENV_DIR}/bin/activate"
    
    print_info "Upgrading pip..."
    pip install --upgrade pip
    
    print_info "Installing packages from requirements.txt..."
    pip install -r "$REQUIREMENTS_FILE"
    
    print_success "All packages installed"
    echo ""
}

# ============================================================================
# Install Custom Tools
# ============================================================================

install_custom_tools() {
    print_header "Installing Custom EN 50128 Tools"
    
    source "${VENV_DIR}/bin/activate"
    
    # Note: Custom tools in tools/ directory can be installed in editable mode
    # if they have setup.py files. For now, they're used directly via python3 tools/...
    
    print_info "Custom tools available in tools/ directory:"
    print_info "  - tools/mcdc/mcdc_analyzer.py (MC/DC analysis)"
    print_info "  - tools/workspace.py (workspace management)"
    print_info "  - tools/enhelp.py (command help system)"
    print_info "  - tools/pdf-conversion/pdf_to_markdown.py (standards conversion)"
    print_info "  - tools/static-analysis/check_misra.py (MISRA C checker)"
    
    print_success "Custom tools are ready to use"
    echo ""
}

# ============================================================================
# Verify Installation
# ============================================================================

verify_installation() {
    print_header "Verifying Installation"
    
    source "${VENV_DIR}/bin/activate"
    
    print_info "Checking critical packages..."
    
    CRITICAL_PACKAGES=(
        "pymupdf4llm:PDF conversion"
        "pycparser:C parsing"
        "lizard:Complexity analysis (SIL 3 MANDATORY)"
        "pytest:Testing framework"
        "tabulate:Report formatting"
    )
    
    ALL_OK=true
    for pkg_info in "${CRITICAL_PACKAGES[@]}"; do
        IFS=':' read -r pkg desc <<< "$pkg_info"
        if pip show "$pkg" &> /dev/null; then
            VERSION=$(pip show "$pkg" | grep Version | awk '{print $2}')
            print_success "${pkg} ${VERSION} (${desc})"
        else
            print_error "${pkg} NOT INSTALLED (${desc})"
            ALL_OK=false
        fi
    done
    
    echo ""
    
    if [ "$ALL_OK" = true ]; then
        print_success "All critical packages installed successfully"
    else
        print_error "Some packages failed to install"
        return 1
    fi
    
    echo ""
    print_info "To activate virtual environment:"
    print_info "  source venv/bin/activate"
    echo ""
}

# ============================================================================
# Check Installation Status
# ============================================================================

check_status() {
    print_header "Installation Status Check"
    
    if [ ! -d "$VENV_DIR" ]; then
        print_error "Virtual environment not found at: ${VENV_DIR}"
        echo ""
        echo "Run './install_python.sh' to initialize"
        exit 1
    fi
    
    print_success "Virtual environment exists"
    
    source "${VENV_DIR}/bin/activate"
    
    echo ""
    print_info "Installed packages:"
    pip list
    
    echo ""
    print_info "Virtual environment location: ${VENV_DIR}"
    print_info "Python version: $(python --version)"
    print_info "Pip version: $(pip --version)"
    echo ""
}

# ============================================================================
# Upgrade Packages
# ============================================================================

upgrade_packages() {
    print_header "Upgrading Python Packages"
    
    if [ ! -d "$VENV_DIR" ]; then
        print_error "Virtual environment not found. Run './install_python.sh' first."
        exit 1
    fi
    
    source "${VENV_DIR}/bin/activate"
    
    print_info "Upgrading pip..."
    pip install --upgrade pip
    
    print_info "Upgrading all packages..."
    pip install --upgrade -r "$REQUIREMENTS_FILE"
    
    print_success "All packages upgraded"
    echo ""
}

# ============================================================================
# Main Script
# ============================================================================

main() {
    cd "$PLATFORM_ROOT"
    
    case "${1:-install}" in
        --check)
            check_status
            ;;
        --upgrade)
            upgrade_packages
            verify_installation
            ;;
        --help|-h)
            echo "EN 50128 Python Environment Setup"
            echo ""
            echo "Usage:"
            echo "  ./install_python.sh              Initialize venv and install packages"
            echo "  ./install_python.sh --upgrade    Upgrade existing packages"
            echo "  ./install_python.sh --check      Check installation status"
            echo "  ./install_python.sh --help       Show this help"
            echo ""
            ;;
        *)
            check_python_version
            create_venv
            install_packages
            install_custom_tools
            verify_installation
            
            print_header "Installation Complete"
            print_success "Python environment ready for EN 50128 development"
            echo ""
            print_info "Next steps:"
            print_info "  1. Activate virtual environment: source venv/bin/activate"
            print_info "  2. Install system tools: ./install_tools.sh"
            print_info "  3. Check available tools: cat TOOLS.md"
            print_info "  4. Get help: python3 tools/enhelp.py"
            echo ""
            ;;
    esac
}

main "$@"
