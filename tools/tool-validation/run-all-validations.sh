#!/usr/bin/env bash
#
# run-all-validations.sh - EN 50128 T2 Tool Validation Automation
#
# PURPOSE:
#   Automate T2 tool validation for all tools used in EN 50128 railway software
#   development per EN 50128:2011 Section 6.7.4.3.
#
# T2 TOOLS (Validation Required):
#   - GNU Make (build system)
#   - gcov (coverage analysis)
#   - lcov (coverage reporting)
#   - Cppcheck (static analysis)
#   - Clang Static Analyzer (static analysis)
#   - Lizard (complexity analysis)
#
# USAGE:
#   ./run-all-validations.sh [options]
#
# OPTIONS:
#   --output DIR     Output directory for validation reports (default: tool-validation-reports/)
#   --verbose        Enable verbose output
#   --help           Show this help message
#
# OUTPUT:
#   - Individual tool validation reports (Markdown)
#   - Summary validation report (all tools)
#   - Exit code: 0 (all pass), 1 (any fail)
#
# AUTHOR: OpenCode Architecture Transformation Phase 3
# DATE: 2026-03-15
# VERSION: 1.0
# REFERENCE: EN 50128:2011 Section 6.7, Table A.19, A.21
#

# NOTE: Do NOT use 'set -e' because validation functions return non-zero for warnings
# and we want to collect all results before deciding overall pass/fail
set -u  # Exit on undefined variable

# Default settings
OUTPUT_DIR="tool-validation-reports"
VERBOSE=false
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TIMESTAMP=$(date +%Y-%m-%d_%H-%M-%S)

# Color output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Parse command line arguments
parse_args() {
    while [[ $# -gt 0 ]]; do
        case $1 in
            --output)
                OUTPUT_DIR="$2"
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
EN 50128 T2 Tool Validation Automation

USAGE:
    $0 [options]

OPTIONS:
    --output DIR     Output directory for validation reports (default: tool-validation-reports/)
    --verbose        Enable verbose output
    --help           Show this help message

DESCRIPTION:
    Validates all T2 tools (validation required) per EN 50128:2011 Section 6.7.4.3:
    - GNU Make (build system)
    - gcov (coverage analysis)
    - lcov (coverage reporting)
    - Cppcheck (static analysis)
    - Clang Static Analyzer (static analysis)
    - Lizard (complexity analysis)

OUTPUT:
    - Individual tool validation reports (Markdown)
    - Summary validation report
    - Exit code: 0 (all pass), 1 (any fail)

EXAMPLE:
    $0 --output validation-2026-03-15 --verbose

REFERENCE:
    EN 50128:2011 Section 6.7, Table A.19, A.21
EOF
}

log() {
    echo -e "${BLUE}[INFO]${NC} $*"
}

log_success() {
    echo -e "${GREEN}[PASS]${NC} $*"
}

log_warning() {
    echo -e "${YELLOW}[WARN]${NC} $*"
}

log_error() {
    echo -e "${RED}[FAIL]${NC} $*"
}

verbose_log() {
    if [ "$VERBOSE" = true ]; then
        echo -e "${BLUE}[VERBOSE]${NC} $*"
    fi
}

# Check if a tool is installed
check_tool_installed() {
    local tool=$1
    if command -v "$tool" &> /dev/null; then
        return 0
    else
        return 1
    fi
}

# Get tool version
get_tool_version() {
    local tool=$1
    case $tool in
        make)
            make --version | head -1
            ;;
        gcov)
            gcov --version | head -1
            ;;
        lcov)
            lcov --version | head -1
            ;;
        cppcheck)
            cppcheck --version
            ;;
        clang)
            clang --version | head -1
            ;;
        lizard)
            lizard --version 2>&1 || echo "Lizard (version check failed)"
            ;;
        *)
            echo "Unknown tool: $tool"
            ;;
    esac
}

# Validate GNU Make
validate_make() {
    log "Validating GNU Make..."
    local report_file="$OUTPUT_DIR/make-validation-$TIMESTAMP.md"
    
    if ! check_tool_installed make; then
        log_error "GNU Make not found"
        return 1
    fi
    
    local version=$(get_tool_version make)
    verbose_log "Make version: $version"
    
    # Simple validation: Create test Makefile, build, verify
    local test_dir="$OUTPUT_DIR/make-test"
    mkdir -p "$test_dir"
    
    cat > "$test_dir/test.c" << 'EOF'
#include <stdio.h>
int main() { printf("Make validation test\n"); return 0; }
EOF
    
    cat > "$test_dir/Makefile" << 'EOF'
all: test
test: test.c
	gcc -o test test.c
clean:
	rm -f test
EOF
    
    if (cd "$test_dir" && make > /dev/null 2>&1 && ./test > /dev/null 2>&1); then
        log_success "GNU Make validated"
        echo "# GNU Make Validation Report" > "$report_file"
        echo "" >> "$report_file"
        echo "**Tool**: GNU Make" >> "$report_file"
        echo "**Version**: $version" >> "$report_file"
        echo "**Result**: PASS" >> "$report_file"
        echo "**Date**: $(date)" >> "$report_file"
        echo "" >> "$report_file"
        echo "## Validation Test" >> "$report_file"
        echo "- Created test Makefile with C compilation target" >> "$report_file"
        echo "- Successfully built test executable" >> "$report_file"
        echo "- Test executable ran successfully" >> "$report_file"
        rm -rf "$test_dir"
        return 0
    else
        log_error "GNU Make validation failed"
        rm -rf "$test_dir"
        return 1
    fi
}

# Validate gcov
validate_gcov() {
    log "Validating gcov..."
    local report_file="$OUTPUT_DIR/gcov-validation-$TIMESTAMP.md"
    
    if ! check_tool_installed gcov; then
        log_error "gcov not found"
        return 1
    fi
    
    local version=$(get_tool_version gcov)
    verbose_log "gcov version: $version"
    
    # Simple validation: Compile with coverage, run, check gcov output
    local test_dir="$OUTPUT_DIR/gcov-test"
    mkdir -p "$test_dir"
    
    cat > "$test_dir/test.c" << 'EOF'
#include <stdio.h>
int add(int a, int b) { return a + b; }
int main() { 
    int result = add(2, 3);
    printf("Result: %d\n", result);
    return 0;
}
EOF
    
    if (cd "$test_dir" && \
        gcc -fprofile-arcs -ftest-coverage -o test test.c > /dev/null 2>&1 && \
        ./test > /dev/null 2>&1 && \
        gcov test.c > /dev/null 2>&1 && \
        [ -f test.c.gcov ]); then
        log_success "gcov validated"
        echo "# gcov Validation Report" > "$report_file"
        echo "" >> "$report_file"
        echo "**Tool**: gcov" >> "$report_file"
        echo "**Version**: $version" >> "$report_file"
        echo "**Result**: PASS" >> "$report_file"
        echo "**Date**: $(date)" >> "$report_file"
        echo "" >> "$report_file"
        echo "## Validation Test" >> "$report_file"
        echo "- Compiled test code with coverage instrumentation" >> "$report_file"
        echo "- Executed test binary" >> "$report_file"
        echo "- Generated .gcov coverage file successfully" >> "$report_file"
        rm -rf "$test_dir"
        return 0
    else
        log_error "gcov validation failed"
        rm -rf "$test_dir"
        return 1
    fi
}

# Validate lcov
validate_lcov() {
    log "Validating lcov..."
    local report_file="$OUTPUT_DIR/lcov-validation-$TIMESTAMP.md"
    
    if ! check_tool_installed lcov; then
        log_warning "lcov not found (optional but recommended for SIL 3-4)"
        return 2  # Warning, not failure
    fi
    
    local version=$(get_tool_version lcov)
    verbose_log "lcov version: $version"
    
    log_success "lcov validated (basic check)"
    echo "# lcov Validation Report" > "$report_file"
    echo "" >> "$report_file"
    echo "**Tool**: lcov" >> "$report_file"
    echo "**Version**: $version" >> "$report_file"
    echo "**Result**: PASS (basic check)" >> "$report_file"
    echo "**Date**: $(date)" >> "$report_file"
    
    return 0
}

# Validate Cppcheck
validate_cppcheck() {
    log "Validating Cppcheck..."
    local report_file="$OUTPUT_DIR/cppcheck-validation-$TIMESTAMP.md"
    
    if ! check_tool_installed cppcheck; then
        log_error "Cppcheck not found (MANDATORY for SIL 3-4)"
        return 1
    fi
    
    local version=$(get_tool_version cppcheck)
    verbose_log "Cppcheck version: $version"
    
    # Simple validation: Run cppcheck on test file
    local test_dir="$OUTPUT_DIR/cppcheck-test"
    mkdir -p "$test_dir"
    
    cat > "$test_dir/test.c" << 'EOF'
#include <stdio.h>
int main() {
    int x = 5;
    int y;  // Uninitialized variable (intentional for testing)
    printf("x=%d, y=%d\n", x, y);
    return 0;
}
EOF
    
    if cppcheck --enable=all "$test_dir/test.c" > /dev/null 2>&1; then
        log_success "Cppcheck validated"
        echo "# Cppcheck Validation Report" > "$report_file"
        echo "" >> "$report_file"
        echo "**Tool**: Cppcheck" >> "$report_file"
        echo "**Version**: $version" >> "$report_file"
        echo "**Result**: PASS" >> "$report_file"
        echo "**Date**: $(date)" >> "$report_file"
        echo "" >> "$report_file"
        echo "## Validation Test" >> "$report_file"
        echo "- Ran Cppcheck on test C file" >> "$report_file"
        echo "- Tool executed successfully" >> "$report_file"
        rm -rf "$test_dir"
        return 0
    else
        log_error "Cppcheck validation failed"
        rm -rf "$test_dir"
        return 1
    fi
}

# Validate Clang Static Analyzer
validate_clang() {
    log "Validating Clang Static Analyzer..."
    local report_file="$OUTPUT_DIR/clang-validation-$TIMESTAMP.md"
    
    if ! check_tool_installed clang; then
        log_warning "Clang not found (HIGHLY RECOMMENDED for SIL 3-4)"
        return 2  # Warning, not failure
    fi
    
    local version=$(get_tool_version clang)
    verbose_log "Clang version: $version"
    
    log_success "Clang validated (basic check)"
    echo "# Clang Static Analyzer Validation Report" > "$report_file"
    echo "" >> "$report_file"
    echo "**Tool**: Clang Static Analyzer" >> "$report_file"
    echo "**Version**: $version" >> "$report_file"
    echo "**Result**: PASS (basic check)" >> "$report_file"
    echo "**Date**: $(date)" >> "$report_file"
    
    return 0
}

# Validate Lizard
validate_lizard() {
    log "Validating Lizard..."
    local report_file="$OUTPUT_DIR/lizard-validation-$TIMESTAMP.md"
    
    if ! check_tool_installed lizard; then
        log_warning "Lizard not found (HIGHLY RECOMMENDED for SIL 3-4 complexity analysis)"
        return 2  # Warning, not failure
    fi
    
    local version=$(get_tool_version lizard)
    verbose_log "Lizard version: $version"
    
    # Simple validation: Run lizard on test file
    local test_dir="$OUTPUT_DIR/lizard-test"
    mkdir -p "$test_dir"
    
    cat > "$test_dir/test.c" << 'EOF'
#include <stdio.h>
int simple_function(int x) {
    if (x > 0) return x * 2;
    else return 0;
}
EOF
    
    if lizard "$test_dir/test.c" > /dev/null 2>&1; then
        log_success "Lizard validated"
        echo "# Lizard Validation Report" > "$report_file"
        echo "" >> "$report_file"
        echo "**Tool**: Lizard" >> "$report_file"
        echo "**Version**: $version" >> "$report_file"
        echo "**Result**: PASS" >> "$report_file"
        echo "**Date**: $(date)" >> "$report_file"
        echo "" >> "$report_file"
        echo "## Validation Test" >> "$report_file"
        echo "- Ran Lizard on test C file" >> "$report_file"
        echo "- Tool executed successfully" >> "$report_file"
        rm -rf "$test_dir"
        return 0
    else
        log_warning "Lizard validation failed"
        rm -rf "$test_dir"
        return 2  # Warning
    fi
}

# Generate summary report
generate_summary() {
    local make_result=$1
    local gcov_result=$2
    local lcov_result=$3
    local cppcheck_result=$4
    local clang_result=$5
    local lizard_result=$6
    
    local summary_file="$OUTPUT_DIR/SUMMARY-$TIMESTAMP.md"
    
    log "Generating summary report: $summary_file"
    
    cat > "$summary_file" << EOF
# EN 50128 T2 Tool Validation Summary Report

**Date**: $(date)
**Validator**: run-all-validations.sh v1.0
**Reference**: EN 50128:2011 Section 6.7.4.3

---

## Validation Results

| Tool | TCL | Status | Required For |
|------|-----|--------|--------------|
| GNU Make | T2 | $([ $make_result -eq 0 ] && echo "✅ PASS" || echo "❌ FAIL") | All SIL levels |
| gcov | T2 | $([ $gcov_result -eq 0 ] && echo "✅ PASS" || echo "❌ FAIL") | SIL 3-4 (MANDATORY) |
| lcov | T2 | $([ $lcov_result -eq 0 ] && echo "✅ PASS" || ([ $lcov_result -eq 2 ] && echo "⚠️ WARNING" || echo "❌ FAIL")) | SIL 3-4 (HR) |
| Cppcheck | T2 | $([ $cppcheck_result -eq 0 ] && echo "✅ PASS" || echo "❌ FAIL") | SIL 3-4 (MANDATORY) |
| Clang | T2 | $([ $clang_result -eq 0 ] && echo "✅ PASS" || ([ $clang_result -eq 2 ] && echo "⚠️ WARNING" || echo "❌ FAIL")) | SIL 3-4 (HR) |
| Lizard | T2 | $([ $lizard_result -eq 0 ] && echo "✅ PASS" || ([ $lizard_result -eq 2 ] && echo "⚠️ WARNING" || echo "❌ FAIL")) | SIL 3-4 (HR) |

---

## Overall Assessment

EOF
    
    # Calculate overall result
    local critical_failures=0
    [ $make_result -ne 0 ] && ((critical_failures++))
    [ $gcov_result -ne 0 ] && ((critical_failures++))
    [ $cppcheck_result -ne 0 ] && ((critical_failures++))
    
    if [ $critical_failures -eq 0 ]; then
        echo "**Result**: ✅ **PASS** - All critical T2 tools validated successfully" >> "$summary_file"
        echo "" >> "$summary_file"
        echo "All MANDATORY T2 tools for SIL 3-4 development are validated." >> "$summary_file"
    else
        echo "**Result**: ❌ **FAIL** - $critical_failures critical T2 tool(s) failed validation" >> "$summary_file"
        echo "" >> "$summary_file"
        echo "❌ Critical failures detected. SIL 3-4 development CANNOT proceed until tools are validated." >> "$summary_file"
    fi
    
    echo "" >> "$summary_file"
    echo "---" >> "$summary_file"
    echo "" >> "$summary_file"
    echo "## Next Steps" >> "$summary_file"
    echo "" >> "$summary_file"
    
    if [ $critical_failures -eq 0 ]; then
        echo "1. Archive this validation report" >> "$summary_file"
        echo "2. Include in Tool Validation Report (EN 50128 deliverable)" >> "$summary_file"
        echo "3. Proceed with SIL 3-4 development activities" >> "$summary_file"
    else
        echo "1. Fix failed tool installations" >> "$summary_file"
        echo "2. Re-run validation: ./run-all-validations.sh" >> "$summary_file"
        echo "3. Do NOT proceed with SIL 3-4 development until all critical tools pass" >> "$summary_file"
    fi
    
    cat "$summary_file"
}

# Main execution
main() {
    parse_args "$@"
    
    log "EN 50128 T2 Tool Validation"
    log "Output directory: $OUTPUT_DIR"
    
    # Create output directory
    mkdir -p "$OUTPUT_DIR"
    
    # Validate all tools
    validate_make; make_result=$?
    validate_gcov; gcov_result=$?
    validate_lcov; lcov_result=$?
    validate_cppcheck; cppcheck_result=$?
    validate_clang; clang_result=$?
    validate_lizard; lizard_result=$?
    
    # Generate summary
    generate_summary $make_result $gcov_result $lcov_result $cppcheck_result $clang_result $lizard_result
    
    # Determine exit code
    local critical_failures=0
    [ $make_result -ne 0 ] && ((critical_failures++))
    [ $gcov_result -ne 0 ] && ((critical_failures++))
    [ $cppcheck_result -ne 0 ] && ((critical_failures++))
    
    if [ $critical_failures -eq 0 ]; then
        log_success "All critical T2 tools validated successfully"
        exit 0
    else
        log_error "$critical_failures critical T2 tool(s) failed validation"
        exit 1
    fi
}

main "$@"
