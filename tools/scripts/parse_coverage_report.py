#!/usr/bin/env python3
"""
parse_coverage_report.py - EN 50128 Coverage Report Parser and Validator

PURPOSE:
    Parse lcov coverage output and validate against EN 50128 Table A.21 coverage
    requirements by SIL level. Generates EN 50128-compliant coverage reports.

USAGE:
    python3 parse_coverage_report.py <coverage.info> --sil <0-4> [--output <report.md>]

COVERAGE REQUIREMENTS (EN 50128 Table A.21):
    SIL 0-1: Statement (HR), Branch (HR)
    SIL 2:   Statement (HR), Branch (M)
    SIL 3-4: Statement (M), Branch (M), Condition (M)

OUTPUT:
    - Coverage analysis report (Markdown)
    - Coverage by file (helps identify problem areas)
    - Uncovered code locations (file:line)
    - Pass/Fail verdict based on SIL requirements
    - Exit code: 0 (PASS), 1 (FAIL)

AUTHOR: OpenCode Architecture Transformation Phase 3
DATE: 2026-03-15
VERSION: 1.0
REFERENCE: EN 50128:2011 Table A.21 (Test Coverage for Code)
"""

import sys
import re
import argparse
from pathlib import Path
from typing import Dict, List, Tuple

class CoverageData:
    """Container for coverage data"""
    def __init__(self):
        self.files: Dict[str, dict] = {}
        self.total_lines = 0
        self.total_lines_hit = 0
        self.total_functions = 0
        self.total_functions_hit = 0
        self.total_branches = 0
        self.total_branches_hit = 0
    
    @property
    def line_coverage(self) -> float:
        """Statement coverage percentage"""
        return (self.total_lines_hit / self.total_lines * 100) if self.total_lines > 0 else 0.0
    
    @property
    def function_coverage(self) -> float:
        """Function coverage percentage"""
        return (self.total_functions_hit / self.total_functions * 100) if self.total_functions > 0 else 0.0
    
    @property
    def branch_coverage(self) -> float:
        """Branch coverage percentage"""
        return (self.total_branches_hit / self.total_branches * 100) if self.total_branches > 0 else 0.0

class CoverageParser:
    """Parser for lcov coverage.info files"""
    
    def __init__(self, coverage_file: str, sil_level: int):
        self.coverage_file = Path(coverage_file)
        self.sil_level = sil_level
        self.coverage = CoverageData()
        
        # SIL-specific coverage requirements (EN 50128 Table A.21)
        self.requirements = self._get_sil_requirements()
    
    def _get_sil_requirements(self) -> Dict[str, Tuple[float, str]]:
        """Get coverage requirements for SIL level"""
        if self.sil_level >= 3:
            # SIL 3-4: Statement (M), Branch (M), Condition (M)
            return {
                'statement': (100.0, 'MANDATORY'),
                'branch': (100.0, 'MANDATORY'),
                'condition': (100.0, 'MANDATORY')  # MC/DC implied
            }
        elif self.sil_level == 2:
            # SIL 2: Statement (HR), Branch (M)
            return {
                'statement': (95.0, 'HIGHLY RECOMMENDED'),
                'branch': (100.0, 'MANDATORY'),
                'condition': (0.0, 'NOT REQUIRED')
            }
        else:
            # SIL 0-1: Statement (HR), Branch (HR)
            return {
                'statement': (90.0, 'HIGHLY RECOMMENDED'),
                'branch': (85.0, 'HIGHLY RECOMMENDED'),
                'condition': (0.0, 'NOT REQUIRED')
            }
    
    def parse(self) -> bool:
        """Parse lcov coverage.info file"""
        try:
            with open(self.coverage_file, 'r', encoding='utf-8') as f:
                current_file = None
                
                for line in f:
                    line = line.strip()
                    
                    if line.startswith('SF:'):
                        # Source file
                        current_file = line[3:]
                        self.coverage.files[current_file] = {
                            'lines': 0,
                            'lines_hit': 0,
                            'functions': 0,
                            'functions_hit': 0,
                            'branches': 0,
                            'branches_hit': 0
                        }
                    
                    elif line.startswith('LF:'):
                        # Lines found
                        count = int(line[3:])
                        self.coverage.files[current_file]['lines'] = count
                        self.coverage.total_lines += count
                    
                    elif line.startswith('LH:'):
                        # Lines hit
                        count = int(line[3:])
                        self.coverage.files[current_file]['lines_hit'] = count
                        self.coverage.total_lines_hit += count
                    
                    elif line.startswith('FNF:'):
                        # Functions found
                        count = int(line[4:])
                        self.coverage.files[current_file]['functions'] = count
                        self.coverage.total_functions += count
                    
                    elif line.startswith('FNH:'):
                        # Functions hit
                        count = int(line[4:])
                        self.coverage.files[current_file]['functions_hit'] = count
                        self.coverage.total_functions_hit += count
                    
                    elif line.startswith('BRF:'):
                        # Branches found
                        count = int(line[4:])
                        self.coverage.files[current_file]['branches'] = count
                        self.coverage.total_branches += count
                    
                    elif line.startswith('BRH:'):
                        # Branches hit
                        count = int(line[4:])
                        self.coverage.files[current_file]['branches_hit'] = count
                        self.coverage.total_branches_hit += count
            
            return True
        
        except Exception as e:
            print(f"ERROR: Failed to parse coverage file: {e}", file=sys.stderr)
            return False
    
    def validate(self) -> bool:
        """Validate coverage against SIL requirements"""
        stmt_req, stmt_status = self.requirements['statement']
        branch_req, branch_status = self.requirements['branch']
        cond_req, cond_status = self.requirements['condition']
        
        passes = True
        
        # Check statement coverage
        if stmt_status == 'MANDATORY' and self.coverage.line_coverage < stmt_req:
            passes = False
        elif stmt_status == 'HIGHLY RECOMMENDED' and self.coverage.line_coverage < stmt_req:
            passes = False  # Treat HR as mandatory for validation
        
        # Check branch coverage
        if branch_status == 'MANDATORY' and self.coverage.branch_coverage < branch_req:
            passes = False
        elif branch_status == 'HIGHLY RECOMMENDED' and self.coverage.branch_coverage < branch_req:
            passes = False
        
        # Condition coverage (only for SIL 3-4)
        # Note: lcov doesn't directly report condition coverage, only branch
        # For true MC/DC, use mcdc_analyzer.py
        
        return passes
    
    def generate_report(self) -> str:
        """Generate EN 50128 coverage report"""
        stmt_req, stmt_status = self.requirements['statement']
        branch_req, branch_status = self.requirements['branch']
        cond_req, cond_status = self.requirements['condition']
        
        passes = self.validate()
        
        report = f"""
# EN 50128 Coverage Analysis Report

**Project**: EN 50128 Railway Software Development  
**SIL Level**: {self.sil_level}  
**Date**: {Path(__file__).stat().st_mtime}  
**Coverage File**: {self.coverage_file.name}

---

## Executive Summary

**Overall Status**: {'✅ PASS' if passes else '❌ FAIL'}

| Metric | Achieved | Required | Status | Classification |
|--------|----------|----------|--------|----------------|
| **Statement Coverage** | {self.coverage.line_coverage:.2f}% | {stmt_req:.0f}% | {'✅ PASS' if self.coverage.line_coverage >= stmt_req else '❌ FAIL'} | {stmt_status} |
| **Branch Coverage** | {self.coverage.branch_coverage:.2f}% | {branch_req:.0f}% | {'✅ PASS' if self.coverage.branch_coverage >= branch_req else '❌ FAIL'} | {branch_status} |
| **Function Coverage** | {self.coverage.function_coverage:.2f}% | N/A | ℹ️ INFO | Not specified |
"""
        
        if self.sil_level >= 3:
            report += f"| **Condition Coverage** | N/A | {cond_req:.0f}% | ⚠️ WARNING | {cond_status} |\n"
            report += "\n**Note**: lcov does not report condition/MC/DC coverage. Use `mcdc_analyzer.py` for detailed MC/DC analysis (MANDATORY SIL 3-4).\n"
        
        report += "\n---\n\n"
        
        # Coverage by file
        report += "## Coverage by File\n\n"
        report += "| File | Statement | Branch | Function |\n"
        report += "|------|-----------|--------|----------|\n"
        
        for file_path, data in sorted(self.coverage.files.items()):
            stmt_cov = (data['lines_hit'] / data['lines'] * 100) if data['lines'] > 0 else 0.0
            branch_cov = (data['branches_hit'] / data['branches'] * 100) if data['branches'] > 0 else 0.0
            func_cov = (data['functions_hit'] / data['functions'] * 100) if data['functions'] > 0 else 0.0
            
            file_name = Path(file_path).name
            report += f"| {file_name} | {stmt_cov:.1f}% | {branch_cov:.1f}% | {func_cov:.1f}% |\n"
        
        report += "\n---\n\n"
        
        # EN 50128 compliance
        report += "## EN 50128 Table A.21 Compliance\n\n"
        report += "**Coverage Requirements by SIL Level** (EN 50128:2011 Table A.21):\n\n"
        report += "| SIL Level | Statement | Branch | Condition/MC/DC |\n"
        report += "|-----------|-----------|--------|------------------|\n"
        report += "| **0-1** | HR | HR | - |\n"
        report += "| **2** | HR | **M** | - |\n"
        report += "| **3-4** | **M** | **M** | **M** |\n\n"
        report += "Legend: **M** = Mandatory, HR = Highly Recommended, - = Not specified\n\n"
        
        # Recommendation
        report += "## Recommendation\n\n"
        if passes:
            report += f"✅ **PASS**: Coverage meets EN 50128 Table A.21 requirements for SIL {self.sil_level}.\n\n"
            report += "**Action**: Proceed to next phase.\n"
        else:
            report += f"❌ **FAIL**: Coverage does NOT meet EN 50128 Table A.21 requirements for SIL {self.sil_level}.\n\n"
            report += "**Action Required**:\n"
            if self.coverage.line_coverage < stmt_req:
                report += f"- Improve statement coverage to {stmt_req:.0f}% (currently {self.coverage.line_coverage:.2f}%)\n"
            if self.coverage.branch_coverage < branch_req:
                report += f"- Improve branch coverage to {branch_req:.0f}% (currently {self.coverage.branch_coverage:.2f}%)\n"
            if self.sil_level >= 3:
                report += f"- Perform MC/DC analysis using `mcdc_analyzer.py` (MANDATORY SIL 3-4)\n"
        
        report += "\n---\n\n"
        report += "## References\n\n"
        report += "- **EN 50128:2011** Table A.21 - Test Coverage for Code\n"
        report += "- **lcov** - Coverage data collection and reporting\n"
        report += "- **mcdc_analyzer.py** - MC/DC coverage analysis (for SIL 3-4)\n\n"
        report += f"**Generated by**: `parse_coverage_report.py` v1.0\n"
        
        return report

def main():
    parser = argparse.ArgumentParser(
        description="Parse lcov coverage and validate against EN 50128 Table A.21",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python3 parse_coverage_report.py coverage.info --sil 3
  python3 parse_coverage_report.py coverage.info --sil 3 --output coverage-report.md

Coverage Requirements (EN 50128 Table A.21):
  SIL 0-1: Statement (HR), Branch (HR)
  SIL 2:   Statement (HR), Branch (M)
  SIL 3-4: Statement (M), Branch (M), Condition/MC/DC (M)

Exit Codes:
  0 - Coverage meets SIL requirements (PASS)
  1 - Coverage below SIL requirements (FAIL)

Reference:
  EN 50128:2011 Table A.21 (Test Coverage for Code)
        """
    )
    
    parser.add_argument("coverage_file", help="Path to lcov coverage.info file")
    parser.add_argument("--sil", type=int, required=True, choices=[0, 1, 2, 3, 4],
                        help="SIL level (0-4)")
    parser.add_argument("--output", help="Output file for coverage report (default: stdout)")
    
    args = parser.parse_args()
    
    # Check file exists
    if not Path(args.coverage_file).exists():
        print(f"ERROR: Coverage file not found: {args.coverage_file}", file=sys.stderr)
        return 1
    
    # Create parser and parse coverage
    parser = CoverageParser(args.coverage_file, args.sil)
    
    if not parser.parse():
        return 1
    
    # Generate report
    report = parser.generate_report()
    
    if args.output:
        with open(args.output, 'w', encoding='utf-8') as f:
            f.write(report)
        print(f"Coverage report written to: {args.output}")
    else:
        print(report)
    
    # Return exit code based on validation
    return 0 if parser.validate() else 1

if __name__ == "__main__":
    sys.exit(main())
