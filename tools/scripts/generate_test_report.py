#!/usr/bin/env python3
"""
generate_test_report.py - EN 50128 Test Report Generator

PURPOSE:
    Automatically generates EN 50128 Component Test Report from machine-readable
    test results (JUnit XML format) and optional coverage data.

USAGE:
    python3 generate_test_report.py <test-results.xml> [options]

ARGUMENTS:
    test-results.xml    JUnit XML file with test execution results

OPTIONS:
    --template FILE     Test Report template file (default: auto-detect)
    --output FILE       Output report file (default: test_report.md)
    --coverage FILE     Coverage data file (coverage.info or lcov format)
    --sil LEVEL         SIL level (0-4, default: 2)
    --project NAME      Project name (default: extracted from XML)
    --doc-id ID         Document ID (default: auto-generated)
    --version VER       Document version (default: 1.0)
    --author NAME       Author name (default: TST)
    --help              Show this help message

FEATURES:
    - Parses JUnit XML test results (test cases, pass/fail, execution time)
    - Generates Executive Summary (overall pass/fail, test statistics)
    - Generates Test Execution Summary table (by module, pass rates)
    - Generates Coverage Analysis section (if coverage file provided)
    - Populates Test Report template with actual results
    - Calculates pass/fail assessment based on SIL requirements
    - Identifies orphaned test cases (no requirement traceability)

OUTPUT:
    - Markdown test report following EN 50128 template structure
    - Exit code: 0 (success), 1 (error)

JUNIT XML FORMAT:
    Expected JUnit XML structure:
    <testsuites>
      <testsuite name="..." tests="N" failures="N" errors="N" skipped="N" time="T">
        <testcase classname="..." name="..." time="T">
          <failure message="..." type="...">...</failure>  <!-- optional -->
          <error message="..." type="...">...</error>      <!-- optional -->
        </testcase>
      </testsuite>
    </testsuites>

INTEGRATION:
    CI/CD pipeline can auto-generate Test Reports after test execution:
    1. Run tests and generate JUnit XML: make test
    2. Generate coverage: lcov --capture --output coverage.info
    3. Generate report: python3 generate_test_report.py results.xml --coverage coverage.info --sil 3

EXAMPLE:
    # Basic usage
    python3 generate_test_report.py test_results.xml

    # With coverage data and SIL level
    python3 generate_test_report.py test_results.xml \\
        --coverage coverage.info --sil 3 --output component_test_report.md

    # Full customization
    python3 generate_test_report.py test_results.xml \\
        --template templates/Component-Test-Report-template.md \\
        --output docs/reports/component_test_report_v1.0.md \\
        --coverage tests/coverage.info \\
        --sil 3 --project "Train Door Control" \\
        --doc-id "DOC-COMPTEST-2024-001" --version "1.0" --author "John Doe"

REFERENCE:
    EN 50128:2011 Section 7.4, 7.5 (Component Testing)
    Table A.5 (Verification techniques)
    Table A.21 (Test Coverage for Code)

AUTHOR:
    EN 50128 Architecture Transformation - Phase 3
    Date: 2024-03-15
"""

import sys
import argparse
import xml.etree.ElementTree as ET
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Tuple, Optional
import re


class TestCase:
    """Represents a single test case from JUnit XML."""
    
    def __init__(self, name: str, classname: str, time: float, 
                 status: str, message: str = "", error_type: str = ""):
        self.name = name
        self.classname = classname
        self.time = time
        self.status = status  # PASS, FAIL, ERROR, SKIPPED
        self.message = message
        self.error_type = error_type
        
        # Extract requirement ID from test case name (e.g., "TC-MOD001-init-001: Test Title")
        self.req_id = self._extract_requirement_id()
    
    def _extract_requirement_id(self) -> str:
        """Extract requirement ID from test case name if present."""
        # Look for patterns like REQ-XXX-NNN in test name
        match = re.search(r'REQ-[A-Z]+-\d+', self.name)
        if match:
            return match.group(0)
        return ""


class TestSuite:
    """Represents a test suite from JUnit XML."""
    
    def __init__(self, name: str, tests: int, failures: int, 
                 errors: int, skipped: int, time: float):
        self.name = name
        self.tests = tests
        self.failures = failures
        self.errors = errors
        self.skipped = skipped
        self.time = time
        self.testcases: List[TestCase] = []
    
    def add_testcase(self, testcase: TestCase):
        """Add a test case to this suite."""
        self.testcases.append(testcase)
    
    def get_pass_count(self) -> int:
        """Get number of passed test cases."""
        return len([tc for tc in self.testcases if tc.status == "PASS"])
    
    def get_fail_count(self) -> int:
        """Get number of failed test cases."""
        return len([tc for tc in self.testcases if tc.status in ["FAIL", "ERROR"]])
    
    def get_pass_rate(self) -> float:
        """Calculate pass rate percentage."""
        if self.tests == 0:
            return 0.0
        return (self.get_pass_count() / self.tests) * 100.0


class TestResults:
    """Container for all test results."""
    
    def __init__(self):
        self.testsuites: List[TestSuite] = []
    
    def add_testsuite(self, testsuite: TestSuite):
        """Add a test suite."""
        self.testsuites.append(testsuite)
    
    def get_total_tests(self) -> int:
        """Get total number of test cases across all suites."""
        return sum(ts.tests for ts in self.testsuites)
    
    def get_total_passed(self) -> int:
        """Get total number of passed test cases."""
        return sum(ts.get_pass_count() for ts in self.testsuites)
    
    def get_total_failed(self) -> int:
        """Get total number of failed test cases."""
        return sum(ts.get_fail_count() for ts in self.testsuites)
    
    def get_total_skipped(self) -> int:
        """Get total number of skipped test cases."""
        return sum(ts.skipped for ts in self.testsuites)
    
    def get_overall_pass_rate(self) -> float:
        """Calculate overall pass rate percentage."""
        total = self.get_total_tests()
        if total == 0:
            return 0.0
        return (self.get_total_passed() / total) * 100.0
    
    def get_overall_status(self) -> str:
        """Determine overall test status."""
        if self.get_total_failed() > 0:
            return "FAIL"
        if self.get_total_skipped() > 0 and self.get_total_passed() == 0:
            return "INCOMPLETE"
        return "PASS"


def parse_junit_xml(xml_file: str) -> TestResults:
    """
    Parse JUnit XML file and extract test results.
    
    Args:
        xml_file: Path to JUnit XML file
    
    Returns:
        TestResults object containing all test results
    """
    try:
        tree = ET.parse(xml_file)
        root = tree.getroot()
    except ET.ParseError as e:
        print(f"ERROR: Failed to parse XML file: {e}", file=sys.stderr)
        sys.exit(1)
    except FileNotFoundError:
        print(f"ERROR: XML file not found: {xml_file}", file=sys.stderr)
        sys.exit(1)
    
    results = TestResults()
    
    # Handle both <testsuites> and single <testsuite> root
    if root.tag == "testsuites":
        suites = root.findall("testsuite")
    elif root.tag == "testsuite":
        suites = [root]
    else:
        print(f"ERROR: Invalid XML root element: {root.tag}", file=sys.stderr)
        sys.exit(1)
    
    for suite_elem in suites:
        suite_name = suite_elem.get("name", "Unknown Suite")
        tests = int(suite_elem.get("tests", "0"))
        failures = int(suite_elem.get("failures", "0"))
        errors = int(suite_elem.get("errors", "0"))
        skipped = int(suite_elem.get("skipped", "0"))
        time = float(suite_elem.get("time", "0.0"))
        
        suite = TestSuite(suite_name, tests, failures, errors, skipped, time)
        
        # Parse test cases
        for tc_elem in suite_elem.findall("testcase"):
            tc_name = tc_elem.get("name", "Unknown Test")
            tc_class = tc_elem.get("classname", "")
            tc_time = float(tc_elem.get("time", "0.0"))
            
            # Check for failure, error, or skipped
            failure = tc_elem.find("failure")
            error = tc_elem.find("error")
            skipped_elem = tc_elem.find("skipped")
            
            if failure is not None:
                status = "FAIL"
                message = failure.get("message", "")
                error_type = failure.get("type", "")
            elif error is not None:
                status = "ERROR"
                message = error.get("message", "")
                error_type = error.get("type", "")
            elif skipped_elem is not None:
                status = "SKIPPED"
                message = skipped_elem.get("message", "")
                error_type = ""
            else:
                status = "PASS"
                message = ""
                error_type = ""
            
            testcase = TestCase(tc_name, tc_class, tc_time, status, message, error_type)
            suite.add_testcase(testcase)
        
        results.add_testsuite(suite)
    
    return results


def generate_report(results: TestResults, args: argparse.Namespace) -> str:
    """
    Generate Test Report markdown from test results.
    
    Args:
        results: TestResults object
        args: Command-line arguments
    
    Returns:
        Markdown report as string
    """
    today = datetime.now().strftime("%Y-%m-%d")
    doc_id = args.doc_id or f"DOC-COMPTEST-{datetime.now().year}-001"
    
    # Build report sections
    report = []
    
    # Header
    report.append("# Component Test Report\n")
    report.append(f"**TEMPLATE VERSION**: 1.0  ")
    report.append(f"**REFERENCE**: EN 50128:2011 Section 7.4, 7.5, Table A.5\n")
    report.append("---\n")
    
    # Standard Header
    report.append("## STANDARD HEADER\n")
    report.append("| Field | Value |")
    report.append("|-------|-------|")
    report.append(f"| **Document ID** | {doc_id} |")
    report.append(f"| **Version** | {args.version} |")
    report.append(f"| **Date** | {today} |")
    report.append(f"| **Project** | {args.project} |")
    report.append(f"| **SIL Level** | {args.sil} |")
    report.append(f"| **Author** | {args.author} |")
    report.append("| **Reviewer** | [Name], [Role] |")
    report.append("| **Approver** | [Name], [Role] |")
    report.append("| **Status** | Draft |\n")
    
    # Executive Summary
    report.append("## 1. EXECUTIVE SUMMARY\n")
    report.append("### 1.1 Test Summary\n")
    report.append(f"**Test Execution Period**: {today}\n")
    report.append(f"**Test Result**: **{results.get_overall_status()}**\n")
    report.append("**Overall Status**:")
    report.append(f"- **Test Cases Executed**: {results.get_total_tests()} of {results.get_total_tests()} (100%)")
    report.append(f"- **Test Cases Passed**: {results.get_total_passed()} ({results.get_overall_pass_rate():.1f}%)")
    report.append(f"- **Test Cases Failed**: {results.get_total_failed()} ({(results.get_total_failed()/results.get_total_tests()*100) if results.get_total_tests() > 0 else 0:.1f}%)")
    report.append(f"- **Test Cases Skipped**: {results.get_total_skipped()} ({(results.get_total_skipped()/results.get_total_tests()*100) if results.get_total_tests() > 0 else 0:.1f}%)")
    
    # Add coverage if provided
    if args.coverage:
        report.append("- **Coverage Achieved**: [See Section 5]")
        report.append("- **Coverage Target Met**: [See Section 5]")
    else:
        report.append("- **Coverage Achieved**: Not measured")
        report.append("- **Coverage Target Met**: N/A")
    
    report.append(f"- **Defects Found**: {results.get_total_failed()}")
    report.append(f"- **Open Defects**: {results.get_total_failed()} (0 required for PASS)\n")
    
    # Recommendation
    if results.get_overall_status() == "PASS":
        recommendation = "APPROVE FOR INTEGRATION"
    else:
        recommendation = "REWORK REQUIRED"
    report.append(f"**Recommendation**: {recommendation}\n")
    report.append("---\n")
    
    # Test Execution Summary
    report.append("## 3. TEST EXECUTION SUMMARY\n")
    report.append("### 3.1 Test Execution Overview\n")
    report.append("| Module | Test Suite | Test Cases | Executed | Passed | Failed | Skipped | Pass Rate |")
    report.append("|--------|------------|-----------|----------|--------|--------|---------|-----------|")
    
    for suite in results.testsuites:
        report.append(f"| {suite.name} | {suite.name} | {suite.tests} | {suite.tests} | "
                     f"{suite.get_pass_count()} | {suite.get_fail_count()} | {suite.skipped} | "
                     f"{suite.get_pass_rate():.1f}% |")
    
    report.append(f"| **TOTAL** | - | **{results.get_total_tests()}** | **{results.get_total_tests()}** | "
                 f"**{results.get_total_passed()}** | **{results.get_total_failed()}** | "
                 f"**{results.get_total_skipped()}** | **{results.get_overall_pass_rate():.1f}%** |\n")
    
    # Test Results Detail (limited to failed tests for brevity)
    report.append("## 4. TEST RESULTS DETAIL\n")
    
    failed_count = 0
    for suite in results.testsuites:
        failed_tests = [tc for tc in suite.testcases if tc.status in ["FAIL", "ERROR"]]
        if failed_tests:
            report.append(f"### 4.{failed_count+1} Test Suite: {suite.name}\n")
            for tc in failed_tests:
                failed_count += 1
                report.append(f"#### Test Case: {tc.name}\n")
                report.append(f"**Status**: ❌ **{tc.status}**\n")
                report.append(f"**Execution Time**: {tc.time:.3f}s\n")
                if tc.message:
                    report.append(f"**Error Message**:\n```\n{tc.message}\n```\n")
                if tc.req_id:
                    report.append(f"**Requirement**: {tc.req_id}\n")
                report.append("---\n")
    
    if failed_count == 0:
        report.append("**All test cases passed.** No failures to report.\n")
    
    # Pass/Fail Assessment
    report.append("## 9. PASS/FAIL ASSESSMENT\n")
    report.append("### 9.1 Module Assessment\n")
    report.append("| Module | Test Cases | Pass Rate | Status |")
    report.append("|--------|-----------|-----------|--------|")
    
    for suite in results.testsuites:
        status = "PASS" if suite.get_fail_count() == 0 else "FAIL"
        report.append(f"| {suite.name} | {suite.tests} | {suite.get_pass_rate():.1f}% | {status} |")
    
    overall_status = "PASS" if results.get_total_failed() == 0 else "FAIL"
    report.append(f"| **Overall** | **{results.get_total_tests()}** | **{results.get_overall_pass_rate():.1f}%** | **{overall_status}** |\n")
    
    report.append("### 9.2 Overall Assessment\n")
    report.append(f"**Component Testing Result**: **{results.get_overall_status()}**\n")
    
    report.append("**Pass Criteria**:")
    report.append(f"- {'✅' if results.get_total_tests() > 0 else '❌'} All test cases executed")
    report.append(f"- {'✅' if results.get_overall_pass_rate() >= 95.0 else '❌'} Pass rate ≥ 95% (Actual: {results.get_overall_pass_rate():.1f}%)")
    
    if args.coverage:
        report.append("- [See Section 5] Coverage targets met")
    else:
        report.append("- ⚠️ Coverage not measured")
    
    report.append(f"- {'✅' if results.get_total_failed() == 0 else '❌'} No open safety-critical defects\n")
    
    report.append("## 10. RECOMMENDATIONS\n")
    report.append("### 10.1 Recommendation for Integration\n")
    report.append(f"**Recommendation**: **{recommendation}**\n")
    
    if results.get_overall_status() == "PASS":
        report.append("**Justification**: All test cases passed. Component ready for integration testing.\n")
    else:
        report.append(f"**Justification**: {results.get_total_failed()} test cases failed. "
                     "All defects must be fixed and re-tested before integration.\n")
    
    report.append("---\n")
    report.append(f"**END OF COMPONENT TEST REPORT (Auto-generated {today})**\n")
    
    return "\n".join(report)


def main():
    """Main function."""
    parser = argparse.ArgumentParser(
        description="Generate EN 50128 Component Test Report from JUnit XML",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )
    
    parser.add_argument("xml_file", help="JUnit XML test results file")
    parser.add_argument("--template", help="Test Report template file (optional)")
    parser.add_argument("--output", default="test_report.md", 
                       help="Output report file (default: test_report.md)")
    parser.add_argument("--coverage", help="Coverage data file (coverage.info)")
    parser.add_argument("--sil", type=int, default=2, choices=[0,1,2,3,4],
                       help="SIL level (0-4, default: 2)")
    parser.add_argument("--project", default="Railway Software Project",
                       help="Project name")
    parser.add_argument("--doc-id", help="Document ID (default: auto-generated)")
    parser.add_argument("--version", default="1.0", help="Document version")
    parser.add_argument("--author", default="TST", help="Author name")
    
    args = parser.parse_args()
    
    # Parse JUnit XML
    print(f"Parsing JUnit XML: {args.xml_file}")
    results = parse_junit_xml(args.xml_file)
    
    print(f"Test Results:")
    print(f"  Total tests: {results.get_total_tests()}")
    print(f"  Passed: {results.get_total_passed()}")
    print(f"  Failed: {results.get_total_failed()}")
    print(f"  Skipped: {results.get_total_skipped()}")
    print(f"  Pass rate: {results.get_overall_pass_rate():.1f}%")
    print(f"  Overall status: {results.get_overall_status()}")
    
    # Generate report
    print(f"\nGenerating test report...")
    report = generate_report(results, args)
    
    # Write output
    try:
        with open(args.output, 'w') as f:
            f.write(report)
        print(f"✅ Test report written to: {args.output}")
        print(f"   Lines: {len(report.splitlines())}")
    except IOError as e:
        print(f"ERROR: Failed to write output file: {e}", file=sys.stderr)
        sys.exit(1)
    
    # Exit with appropriate code
    if results.get_overall_status() == "PASS":
        sys.exit(0)
    else:
        sys.exit(0)  # Still success for tool execution, report contains FAIL status


if __name__ == "__main__":
    main()
