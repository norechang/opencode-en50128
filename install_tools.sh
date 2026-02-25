#!/bin/bash
# EN 50128 Railway Software Development Platform
# System Tools Installation Script
#
# This script installs system-level development and analysis tools required
# for EN 50128 SIL 3 railway software development.
#
# WARNING: This script requires root privileges (sudo) to install system packages.
#
# Usage:
#   ./install_tools.sh                # Install all recommended tools
#   ./install_tools.sh --minimal      # Install only MANDATORY SIL 3 tools
#   ./install_tools.sh --check        # Check installation status
#   ./install_tools.sh --list         # List available tools

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
NC='\033[0m' # No Color

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

print_mandatory() {
    echo -e "${MAGENTA}[MANDATORY SIL 3]${NC} $1"
}

# ============================================================================
# Detect OS and Package Manager
# ============================================================================

detect_os() {
    if [ -f /etc/os-release ]; then
        . /etc/os-release
        OS=$ID
        OS_VERSION=$VERSION_ID
    else
        print_error "Cannot detect OS. Manual installation required."
        exit 1
    fi
    
    case "$OS" in
        ubuntu|debian)
            PKG_MANAGER="apt-get"
            PKG_UPDATE="sudo apt-get update"
            PKG_INSTALL="sudo apt-get install -y"
            ;;
        fedora|rhel|centos)
            PKG_MANAGER="dnf"
            PKG_UPDATE="sudo dnf check-update || true"
            PKG_INSTALL="sudo dnf install -y"
            ;;
        arch|manjaro)
            PKG_MANAGER="pacman"
            PKG_UPDATE="sudo pacman -Sy"
            PKG_INSTALL="sudo pacman -S --noconfirm"
            ;;
        darwin|macos)
            if ! command -v brew &> /dev/null; then
                print_error "Homebrew not found. Install from: https://brew.sh"
                exit 1
            fi
            PKG_MANAGER="brew"
            PKG_UPDATE="brew update"
            PKG_INSTALL="brew install"
            ;;
        *)
            print_error "Unsupported OS: $OS"
            print_info "Manual installation required. See TOOLS.md for package list."
            exit 1
            ;;
    esac
    
    print_success "Detected OS: $OS (Package manager: $PKG_MANAGER)"
}

# ============================================================================
# Check if Tool is Installed
# ============================================================================

is_installed() {
    command -v "$1" &> /dev/null
}

check_tool() {
    local tool=$1
    local display_name=$2
    local mandatory=$3
    
    if is_installed "$tool"; then
        local version=$($tool --version 2>&1 | head -n1 || echo "unknown")
        print_success "${display_name} installed: ${version}"
        return 0
    else
        if [ "$mandatory" = "true" ]; then
            print_error "${display_name} NOT INSTALLED (MANDATORY for SIL 3)"
        else
            print_warning "${display_name} not installed (recommended)"
        fi
        return 1
    fi
}

# ============================================================================
# Tool Installation Functions
# ============================================================================

install_build_tools() {
    print_header "Installing Build Tools"
    
    case "$PKG_MANAGER" in
        apt-get)
            $PKG_INSTALL build-essential make cmake
            ;;
        dnf)
            $PKG_INSTALL gcc gcc-c++ make cmake
            ;;
        pacman)
            $PKG_INSTALL base-devel cmake
            ;;
        brew)
            $PKG_INSTALL gcc make cmake
            ;;
    esac
    
    print_success "Build tools installed"
}

install_mandatory_tools() {
    print_header "Installing MANDATORY SIL 3 Tools"
    
    print_mandatory "These tools are REQUIRED for EN 50128 SIL 3 compliance"
    echo ""
    
    # GCC (already handled by build-essential)
    print_info "Installing GCC and gcov..."
    # gcov comes with gcc
    
    # lcov - Coverage report generator (MANDATORY SIL 3)
    print_info "Installing lcov (coverage reports - MANDATORY SIL 3)..."
    case "$PKG_MANAGER" in
        apt-get|dnf)
            $PKG_INSTALL lcov
            ;;
        pacman)
            $PKG_INSTALL lcov
            ;;
        brew)
            $PKG_INSTALL lcov
            ;;
    esac
    
    # Cppcheck - Static analyzer (MANDATORY SIL 3)
    print_info "Installing Cppcheck (static analysis - MANDATORY SIL 3)..."
    case "$PKG_MANAGER" in
        apt-get|dnf|pacman)
            $PKG_INSTALL cppcheck
            ;;
        brew)
            $PKG_INSTALL cppcheck
            ;;
    esac
    
    # Clang Static Analyzer (MANDATORY SIL 3)
    print_info "Installing Clang (static analysis - MANDATORY SIL 3)..."
    case "$PKG_MANAGER" in
        apt-get)
            $PKG_INSTALL clang clang-tools
            ;;
        dnf)
            $PKG_INSTALL clang clang-analyzer
            ;;
        pacman)
            $PKG_INSTALL clang
            ;;
        brew)
            $PKG_INSTALL llvm
            ;;
    esac
    
    print_success "Mandatory SIL 3 tools installed"
    echo ""
}

install_recommended_tools() {
    print_header "Installing Recommended Tools"
    
    # Valgrind - Memory error detection (Highly Recommended SIL 3)
    print_info "Installing Valgrind (memory analysis - HR SIL 3)..."
    case "$PKG_MANAGER" in
        apt-get|dnf|pacman)
            $PKG_INSTALL valgrind
            ;;
        brew)
            print_warning "Valgrind not available on macOS (use Xcode Instruments instead)"
            ;;
    esac
    
    # Splint - Additional static checker
    print_info "Installing Splint (static analysis)..."
    case "$PKG_MANAGER" in
        apt-get|dnf|pacman)
            $PKG_INSTALL splint || print_warning "Splint not available in repositories"
            ;;
        brew)
            $PKG_INSTALL splint || print_warning "Splint not available via Homebrew"
            ;;
    esac
    
    # Git (should already be installed, but ensure it)
    print_info "Installing Git (version control - MANDATORY all SILs)..."
    case "$PKG_MANAGER" in
        apt-get|dnf|pacman)
            $PKG_INSTALL git
            ;;
        brew)
            $PKG_INSTALL git
            ;;
    esac
    
    print_success "Recommended tools installed"
    echo ""
}

install_optional_tools() {
    print_header "Installing Optional Development Tools"
    
    # Doxygen - Documentation generation
    print_info "Installing Doxygen (documentation)..."
    case "$PKG_MANAGER" in
        apt-get|dnf|pacman)
            $PKG_INSTALL doxygen graphviz
            ;;
        brew)
            $PKG_INSTALL doxygen graphviz
            ;;
    esac
    
    # ctags - Code navigation
    print_info "Installing Universal Ctags (code navigation)..."
    case "$PKG_MANAGER" in
        apt-get)
            $PKG_INSTALL universal-ctags || $PKG_INSTALL exuberant-ctags
            ;;
        dnf|pacman)
            $PKG_INSTALL ctags
            ;;
        brew)
            $PKG_INSTALL universal-ctags
            ;;
    esac
    
    print_success "Optional tools installed"
    echo ""
}

# ============================================================================
# Check Installation Status
# ============================================================================

check_installation() {
    print_header "Tool Installation Status Check"
    
    echo ""
    echo -e "${MAGENTA}MANDATORY for SIL 3 (EN 50128 Table A.x)${NC}"
    echo ""
    
    MANDATORY_OK=true
    
    # Build tools
    check_tool "gcc" "GCC Compiler" true || MANDATORY_OK=false
    check_tool "make" "GNU Make" true || MANDATORY_OK=false
    check_tool "gcov" "gcov (Coverage)" true || MANDATORY_OK=false
    check_tool "lcov" "lcov (Coverage Reports)" true || MANDATORY_OK=false
    
    # Static analysis (MANDATORY SIL 3 - Table A.19)
    check_tool "cppcheck" "Cppcheck (Static Analysis)" true || MANDATORY_OK=false
    check_tool "clang" "Clang (Static Analysis)" true || MANDATORY_OK=false
    
    # Version control (MANDATORY all SILs - Table A.9)
    check_tool "git" "Git (Version Control)" true || MANDATORY_OK=false
    
    echo ""
    echo -e "${BLUE}HIGHLY RECOMMENDED for SIL 3${NC}"
    echo ""
    
    # Dynamic analysis (MANDATORY SIL 3 - Table A.13)
    check_tool "valgrind" "Valgrind (Memory Analysis)" false
    
    echo ""
    echo -e "${BLUE}OPTIONAL Tools${NC}"
    echo ""
    
    check_tool "splint" "Splint (Static Analysis)" false
    check_tool "doxygen" "Doxygen (Documentation)" false
    check_tool "ctags" "Universal Ctags (Navigation)" false
    
    echo ""
    echo -e "${BLUE}PYTHON Tools (see install_python.sh)${NC}"
    echo ""
    
    # Check if venv is active
    if [ -n "$VIRTUAL_ENV" ]; then
        print_success "Virtual environment active: $VIRTUAL_ENV"
        check_tool "lizard" "Lizard (Complexity - MANDATORY SIL 3)" true
    else
        print_warning "Virtual environment not active (run: source venv/bin/activate)"
        print_info "Then run: pip install -r requirements.txt"
    fi
    
    echo ""
    echo -e "${YELLOW}COMMERCIAL Tools (manual installation required)${NC}"
    echo ""
    
    print_info "PC-lint Plus (MISRA C - Highly Recommended SIL 3)"
    print_info "  Status: Not checked (commercial license required)"
    print_info "  URL: https://pclintplus.com/"
    print_info ""
    print_info "Bullseye Coverage (MC/DC - Highly Recommended SIL 3)"
    print_info "  Status: Not checked (commercial license required)"
    print_info "  URL: https://www.bullseye.com/"
    
    echo ""
    
    if [ "$MANDATORY_OK" = true ]; then
        print_header "✓ All MANDATORY SIL 3 tools installed"
        print_success "System ready for EN 50128 SIL 3 development"
    else
        print_header "✗ Some MANDATORY tools missing"
        print_error "Run './install_tools.sh' to install missing tools"
        return 1
    fi
    
    echo ""
}

# ============================================================================
# List Available Tools
# ============================================================================

list_tools() {
    print_header "EN 50128 Tool Classification"
    
    echo ""
    echo "For complete tool information, see: TOOLS.md"
    echo ""
    
    echo -e "${MAGENTA}MANDATORY for SIL 3 (Table A.x)${NC}"
    echo "  - gcc, gcov      (Compiler, coverage - always required)"
    echo "  - lcov           (Coverage reports - Table A.21)"
    echo "  - cppcheck       (Static analysis - Table A.19)"
    echo "  - clang          (Static analysis - Table A.19)"
    echo "  - lizard         (Complexity ≤10 - Table A.19)"
    echo "  - git            (Version control - Table A.9)"
    echo ""
    
    echo -e "${BLUE}HIGHLY RECOMMENDED for SIL 3${NC}"
    echo "  - valgrind       (Memory analysis - Table A.13)"
    echo "  - PC-lint Plus   (MISRA C - Table A.19) [COMMERCIAL]"
    echo ""
    
    echo -e "${BLUE}RECOMMENDED for SIL 3${NC}"
    echo "  - splint         (Static analysis - Table A.19)"
    echo "  - doxygen        (Documentation generation)"
    echo ""
    
    echo -e "${BLUE}CUSTOM EN 50128 Tools (Python)${NC}"
    echo "  - mcdc_analyzer  (MC/DC coverage analysis - Table A.21)"
    echo "  - workspace.py   (Project workspace management)"
    echo "  - enhelp.py      (Command help system)"
    echo "  - check_misra.py (MISRA C checking wrapper)"
    echo ""
    
    echo "Installation commands:"
    echo "  ./install_tools.sh             # Install all tools"
    echo "  ./install_tools.sh --minimal   # MANDATORY only"
    echo "  ./install_tools.sh --check     # Check status"
    echo ""
}

# ============================================================================
# Main Script
# ============================================================================

main() {
    case "${1:-install}" in
        --check)
            detect_os
            check_installation
            ;;
        --list)
            list_tools
            ;;
        --minimal)
            print_header "EN 50128 SIL 3 Tool Installation (MANDATORY ONLY)"
            print_warning "This will require root privileges (sudo)"
            echo ""
            read -p "Continue? (y/N): " -n 1 -r
            echo
            if [[ ! $REPLY =~ ^[Yy]$ ]]; then
                echo "Installation cancelled"
                exit 0
            fi
            
            detect_os
            print_info "Updating package manager..."
            $PKG_UPDATE
            
            install_build_tools
            install_mandatory_tools
            
            print_header "Installation Complete (MANDATORY tools only)"
            echo ""
            check_installation
            ;;
        --help|-h)
            echo "EN 50128 System Tools Installation"
            echo ""
            echo "Usage:"
            echo "  ./install_tools.sh              Install all recommended tools"
            echo "  ./install_tools.sh --minimal    Install only MANDATORY SIL 3 tools"
            echo "  ./install_tools.sh --check      Check installation status"
            echo "  ./install_tools.sh --list       List available tools"
            echo "  ./install_tools.sh --help       Show this help"
            echo ""
            echo "Note: This script requires root privileges (sudo) for installation."
            echo ""
            ;;
        *)
            print_header "EN 50128 SIL 3 Tool Installation (FULL)"
            print_warning "This will require root privileges (sudo)"
            echo ""
            read -p "Continue? (y/N): " -n 1 -r
            echo
            if [[ ! $REPLY =~ ^[Yy]$ ]]; then
                echo "Installation cancelled"
                exit 0
            fi
            
            detect_os
            print_info "Updating package manager..."
            $PKG_UPDATE
            
            install_build_tools
            install_mandatory_tools
            install_recommended_tools
            install_optional_tools
            
            print_header "Installation Complete"
            echo ""
            check_installation
            
            echo ""
            print_info "Next steps:"
            print_info "  1. Install Python tools: ./install_python.sh"
            print_info "  2. Activate venv: source venv/bin/activate"
            print_info "  3. Check status: ./install_tools.sh --check"
            print_info "  4. View tool catalog: cat TOOLS.md"
            echo ""
            ;;
    esac
}

main "$@"
