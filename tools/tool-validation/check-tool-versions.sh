#!/usr/bin/env bash
#
# check-tool-versions.sh - EN 50128 Tool Version Checker
#
# PURPOSE:
#   Check installed tool versions against EN 50128 minimum requirements.
#   Verifies that all required development tools are installed and meet
#   minimum version requirements for safety-critical railway software.
#
# TOOLS CHECKED:
#   - GCC (GNU Compiler Collection) - T3, MANDATORY all SILs
#   - GNU Make (Build System) - T2, MANDATORY all SILs
#   - gcov (Coverage Analysis) - T2, MANDATORY SIL 3-4
#   - lcov (Coverage Reporting) - T2, MANDATORY SIL 3-4
#   - Cppcheck (Static Analysis) - T2, MANDATORY SIL 3-4
#   - Clang (Static Analysis) - T2, MANDATORY SIL 3-4
#   - Lizard (Complexity Analysis) - T1, MANDATORY SIL 3-4
#   - Git (Version Control) - T2, MANDATORY all SILs
#   - Python3 (Scripting Support) - T1, MANDATORY for tooling
#
# USAGE:
#   ./check-tool-versions.sh [options]
#
# OPTIONS:
#   --output FILE    Output file for version report (default: stdout)
#   --sil LEVEL      SIL level to check (0-4, default: 3)
#   --verbose        Enable verbose output
#   --help           Show this help message
#
# OUTPUT:
#   - Tool version compatibility report (Markdown)
#   - Exit code: 0 (all OK), 1 (missing tool), 2 (version mismatch)
#
# AUTHOR: OpenCode Architecture Transformation Phase 3
# DATE: 2026-03-15
# VERSION: 1.0
# REFERENCE: EN 50128:2011 Section 6.7, TOOLS.md
#

# NOTE: Do NOT use 'set -e' because we want to check all tools before exiting
set -u  # Exit on undefined variable

# Default settings
OUTPUT_FILE=""
SIL_LEVEL=3
VERBOSE=false
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TIMESTAMP=$(date +%Y-%m-%d_%H-%M-%S)

# Color output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Exit codes
EXIT_SUCCESS=0
EXIT_MISSING_TOOL=1
EXIT_VERSION_MISMATCH=2

# Tool requirements (tool_name:min_version:tcl:sil_required)
# Format: tool_name:min_version:tcl:sil_level (0=all, 3=SIL3-4, 2=SIL2+)
declare -A TOOL_REQUIREMENTS=(
    ["gcc"]="11.0:T3:0"
    ["make"]="4.0:T2:0"
    ["gcov"]="11.0:T2:3"
    ["lcov"]="1.14:T2:3"
    ["cppcheck"]="2.10:T2:3"
    ["clang"]="14.0:T2:3"
    ["lizard"]="1.17:T1:3"
    ["git"]="2.0:T2:0"
    ["python3"]="3.8:T1:0"
)

# Tool check results
declare -a TOOL_RESULTS=()
MISSING_TOOLS=0
VERSION_MISMATCHES=0
WARNINGS=0

# Parse command line arguments
parse_args() {
    while [[ $# -gt 0 ]]; do
        case $1 in
            --output)
                OUTPUT_FILE="$2"
                shift 2
                ;;
            --sil)
                SIL_LEVEL="$2"
                if [[ ! "$SIL_LEVEL" =~ ^[0-4]$ ]]; then
                    echo "Error: Invalid SIL level: $SIL_LEVEL (must be 0-4)"
                    exit 1
                fi
                shift 2
                ;;
            --verbose)
                VERBOSE=true
                shift
                ;;
            --help)
                show_help
                exit 0
                ;;
            *)
                echo "Unknown option: $1"
                show_help
                exit 1
                ;;
        esac
    done
}

show_help() {
    cat << EOF
EN 50128 Tool Version Checker

Checks installed tool versions against EN 50128 minimum requirements.

USAGE:
    ./check-tool-versions.sh [options]

OPTIONS:
    --output FILE    Output file for version report (default: stdout)
    --sil LEVEL      SIL level to check (0-4, default: 3)
    --verbose        Enable verbose output
    --help           Show this help message

TOOLS CHECKED:
    - GCC (T3) - GNU Compiler Collection
    - GNU Make (T2) - Build system
    - gcov (T2) - Coverage analysis
    - lcov (T2) - Coverage reporting
    - Cppcheck (T2) - Static analysis
    - Clang (T2) - Static analysis
    - Lizard (T1) - Complexity analysis
    - Git (T2) - Version control
    - Python3 (T1) - Scripting support

EXIT CODES:
    0 - All tools OK
    1 - Missing required tool
    2 - Version mismatch (tool too old)

EXAMPLES:
    # Check all tools for SIL 3
    ./check-tool-versions.sh

    # Check tools for SIL 0 (basic toolset)
    ./check-tool-versions.sh --sil 0

    # Generate report to file
    ./check-tool-versions.sh --output tool-versions.md

    # Verbose mode
    ./check-tool-versions.sh --verbose

REFERENCE:
    EN 50128:2011 Section 6.7 (Software Tools)
    TOOLS.md (Tool Catalog)

EOF
}

# Log message (only if verbose)
log_verbose() {
    if [[ "$VERBOSE" == "true" ]]; then
        echo -e "${BLUE}[INFO]${NC} $1" >&2
    fi
}

# Compare two semantic versions (v1 >= v2)
# Returns: 0 if v1 >= v2, 1 otherwise
version_compare() {
    local v1="$1"
    local v2="$2"
    
    # Remove any 'v' prefix
    v1="${v1#v}"
    v2="${v2#v}"
    
    # Split versions into components
    IFS='.' read -ra V1 <<< "$v1"
    IFS='.' read -ra V2 <<< "$v2"
    
    # Compare major, minor, patch
    for i in 0 1 2; do
        local n1="${V1[i]:-0}"
        local n2="${V2[i]:-0}"
        
        # Remove any non-numeric suffix (e.g., "13.3.0-ubuntu1")
        n1="${n1%%[^0-9]*}"
        n2="${n2%%[^0-9]*}"
        
        if (( n1 > n2 )); then
            return 0
        elif (( n1 < n2 )); then
            return 1
        fi
    done
    
    return 0  # Equal
}

# Check if tool is required for current SIL level
# Args: tool_sil_requirement
# Returns: 0 if required, 1 otherwise
is_tool_required() {
    local tool_sil="$1"
    
    if [[ "$tool_sil" == "0" ]]; then
        return 0  # Required for all SILs
    elif [[ "$tool_sil" == "2" && "$SIL_LEVEL" -ge 2 ]]; then
        return 0  # Required for SIL 2+
    elif [[ "$tool_sil" == "3" && "$SIL_LEVEL" -ge 3 ]]; then
        return 0  # Required for SIL 3-4
    else
        return 1  # Not required
    fi
}

# Check single tool
# Args: tool_name
check_tool() {
    local tool="$1"
    local requirements="${TOOL_REQUIREMENTS[$tool]}"
    
    IFS=':' read -r min_version tcl sil_req <<< "$requirements"
    
    log_verbose "Checking $tool (min: $min_version, TCL: $tcl, SIL: $sil_req)"
    
    # Check if tool is required for current SIL
    if ! is_tool_required "$sil_req"; then
        log_verbose "  → Skipped (not required for SIL $SIL_LEVEL)"
        TOOL_RESULTS+=("SKIP|$tool|N/A|$min_version|$tcl|Not required for SIL $SIL_LEVEL")
        return 0
    fi
    
    # Check if tool is installed
    if ! command -v "$tool" &> /dev/null; then
        echo -e "${RED}[ERROR]${NC} $tool not found (required for SIL $SIL_LEVEL)" >&2
        TOOL_RESULTS+=("ERROR|$tool|NOT INSTALLED|$min_version|$tcl|Missing required tool")
        ((MISSING_TOOLS++))
        return 1
    fi
    
    # Get installed version
    local installed_version=""
    case "$tool" in
        gcc)
            installed_version=$(gcc --version | head -n1 | grep -oP '\d+\.\d+\.\d+' | head -n1)
            ;;
        make)
            installed_version=$(make --version | head -n1 | grep -oP '\d+\.\d+' | head -n1)
            ;;
        gcov)
            installed_version=$(gcov --version | head -n1 | grep -oP '\d+\.\d+\.\d+' | head -n1)
            ;;
        lcov)
            installed_version=$(lcov --version | grep -oP '\d+\.\d+' | head -n1)
            ;;
        cppcheck)
            installed_version=$(cppcheck --version | grep -oP '\d+\.\d+\.\d+' | head -n1)
            ;;
        clang)
            installed_version=$(clang --version | head -n1 | grep -oP '\d+\.\d+\.\d+' | head -n1)
            ;;
        lizard)
            installed_version=$(lizard --version 2>&1 | grep -oP '\d+\.\d+\.\d+' | head -n1)
            if [[ -z "$installed_version" ]]; then
                # Try alternate version format
                installed_version=$(python3 -c "import lizard; print(lizard.__version__)" 2>/dev/null || echo "")
            fi
            ;;
        git)
            installed_version=$(git --version | grep -oP '\d+\.\d+\.\d+' | head -n1)
            ;;
        python3)
            installed_version=$(python3 --version | grep -oP '\d+\.\d+\.\d+' | head -n1)
            ;;
        *)
            echo -e "${YELLOW}[WARN]${NC} Unknown tool: $tool" >&2
            TOOL_RESULTS+=("WARN|$tool|UNKNOWN|$min_version|$tcl|Unknown version check method")
            ((WARNINGS++))
            return 2
            ;;
    esac
    
    if [[ -z "$installed_version" ]]; then
        echo -e "${YELLOW}[WARN]${NC} $tool version could not be determined" >&2
        TOOL_RESULTS+=("WARN|$tool|UNKNOWN|$min_version|$tcl|Version detection failed")
        ((WARNINGS++))
        return 2
    fi
    
    # Compare versions
    if version_compare "$installed_version" "$min_version"; then
        echo -e "${GREEN}[OK]${NC} $tool $installed_version (>= $min_version, $tcl)" >&2
        TOOL_RESULTS+=("OK|$tool|$installed_version|$min_version|$tcl|Version OK")
        return 0
    else
        echo -e "${RED}[ERROR]${NC} $tool $installed_version < $min_version (outdated)" >&2
        TOOL_RESULTS+=("ERROR|$tool|$installed_version|$min_version|$tcl|Version too old")
        ((VERSION_MISMATCHES++))
        return 2
    fi
}

# Generate Markdown report
generate_report() {
    cat << EOF
# EN 50128 Tool Version Report

**Project**: EN 50128 Railway Software Development  
**SIL Level**: $SIL_LEVEL  
**Date**: $(date +"%Y-%m-%d %H:%M:%S")  
**Reference**: EN 50128:2011 Section 6.7, TOOLS.md

---

## Summary

- **Total Tools Checked**: ${#TOOL_REQUIREMENTS[@]}
- **Missing Tools**: $MISSING_TOOLS
- **Version Mismatches**: $VERSION_MISMATCHES
- **Warnings**: $WARNINGS
- **Overall Status**: $(if [[ $MISSING_TOOLS -eq 0 && $VERSION_MISMATCHES -eq 0 ]]; then echo "✅ **PASS**"; elif [[ $MISSING_TOOLS -gt 0 ]]; then echo "❌ **FAIL** (missing tools)"; else echo "⚠️ **FAIL** (version mismatches)"; fi)

---

## Tool Version Details

| Status | Tool | Installed | Required | TCL | Notes |
|--------|------|-----------|----------|-----|-------|
EOF

    for result in "${TOOL_RESULTS[@]}"; do
        IFS='|' read -r status tool installed required tcl notes <<< "$result"
        
        local status_icon=""
        case "$status" in
            OK)
                status_icon="✅"
                ;;
            ERROR)
                status_icon="❌"
                ;;
            WARN)
                status_icon="⚠️"
                ;;
            SKIP)
                status_icon="➖"
                ;;
        esac
        
        echo "| $status_icon | **$tool** | $installed | $required | $tcl | $notes |"
    done

    cat << EOF

---

## Tool Confidence Levels (TCL)

Per EN 50128:2011 Section 6.7:

- **T1**: No tool error affects output integrity (no qualification required)
- **T2**: Tool errors may go undetected (validation required)
- **T3**: Tool output not verified (full qualification required)

---

## Recommendations

EOF

    if [[ $MISSING_TOOLS -gt 0 ]]; then
        cat << EOF
### ❌ Missing Tools

The following tools are **MISSING** and required for SIL $SIL_LEVEL:

EOF
        for result in "${TOOL_RESULTS[@]}"; do
            IFS='|' read -r status tool installed required tcl notes <<< "$result"
            if [[ "$status" == "ERROR" && "$installed" == "NOT INSTALLED" ]]; then
                echo "- **$tool** ($tcl) - $notes"
                echo "  - Install: See \`TOOLS.md\` for installation instructions"
            fi
        done
        echo ""
    fi

    if [[ $VERSION_MISMATCHES -gt 0 ]]; then
        cat << EOF
### ⚠️ Version Mismatches

The following tools are **OUTDATED** and should be updated:

EOF
        for result in "${TOOL_RESULTS[@]}"; do
            IFS='|' read -r status tool installed required tcl notes <<< "$result"
            if [[ "$status" == "ERROR" && "$installed" != "NOT INSTALLED" ]]; then
                echo "- **$tool** ($tcl) - Installed: $installed, Required: >= $required"
                echo "  - Update: See \`TOOLS.md\` for installation instructions"
            fi
        done
        echo ""
    fi

    if [[ $WARNINGS -gt 0 ]]; then
        cat << EOF
### ⚠️ Warnings

The following tools have warnings:

EOF
        for result in "${TOOL_RESULTS[@]}"; do
            IFS='|' read -r status tool installed required tcl notes <<< "$result"
            if [[ "$status" == "WARN" ]]; then
                echo "- **$tool** ($tcl) - $notes"
            fi
        done
        echo ""
    fi

    if [[ $MISSING_TOOLS -eq 0 && $VERSION_MISMATCHES -eq 0 ]]; then
        cat << EOF
### ✅ All Tools OK

All required tools are installed and meet minimum version requirements for SIL $SIL_LEVEL.

**Action**: No action required. Proceed with development.

EOF
    else
        cat << EOF
**Action Required**: Install missing tools and update outdated tools before proceeding.

**Reference**: \`TOOLS.md\` - EN 50128 Tool Catalog  
**Installation Scripts**: 
- \`./install_tools.sh\` - Install system tools
- \`./install_python.sh\` - Install Python tools

EOF
    fi

    cat << EOF
---

## References

- **EN 50128:2011** Section 6.7 - Software Tools
- **TOOLS.md** - EN 50128 Tool Catalog (project-specific)
- **install_tools.sh** - System tool installation script
- **install_python.sh** - Python tool installation script

**Generated by**: \`check-tool-versions.sh\` v1.0  
**Timestamp**: $(date +"%Y-%m-%d %H:%M:%S")
EOF
}

# Main execution
main() {
    parse_args "$@"
    
    echo "EN 50128 Tool Version Checker" >&2
    echo "==============================" >&2
    echo "SIL Level: $SIL_LEVEL" >&2
    echo "Checking ${#TOOL_REQUIREMENTS[@]} tools..." >&2
    echo "" >&2
    
    # Check all tools
    for tool in "${!TOOL_REQUIREMENTS[@]}"; do
        check_tool "$tool" || true  # Continue even if check fails
    done
    
    echo "" >&2
    echo "Check complete!" >&2
    echo "" >&2
    
    # Generate report
    if [[ -n "$OUTPUT_FILE" ]]; then
        generate_report > "$OUTPUT_FILE"
        echo "Report written to: $OUTPUT_FILE" >&2
    else
        generate_report
    fi
    
    # Determine exit code
    if [[ $MISSING_TOOLS -gt 0 ]]; then
        echo -e "${RED}[FAIL]${NC} $MISSING_TOOLS missing tool(s)" >&2
        exit $EXIT_MISSING_TOOL
    elif [[ $VERSION_MISMATCHES -gt 0 ]]; then
        echo -e "${YELLOW}[FAIL]${NC} $VERSION_MISMATCHES version mismatch(es)" >&2
        exit $EXIT_VERSION_MISMATCH
    else
        echo -e "${GREEN}[PASS]${NC} All tools OK" >&2
        exit $EXIT_SUCCESS
    fi
}

# Run main
main "$@"
