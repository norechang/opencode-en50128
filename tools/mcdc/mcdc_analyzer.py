#!/usr/bin/env python3
"""
mcdc_analyzer.py - MC/DC analysis tool for EN 50128 SIL 3 C software.

Subcommands:
  analyze  - Static extraction of compound boolean expressions from C source,
             generates truth tables and minimal MC/DC test vectors.
  report   - Consumes MC-DC-Vectors.json + test-results.json, measures MC/DC
             coverage achieved, generates EN 50128 evidence document.

Usage:
  # Mode 1 - static analysis
  python3 tools/mcdc/mcdc_analyzer.py analyze \\
    -I examples/train_door_control2/src \\
    --sil 3 --project train_door_control2 \\
    --format all \\
    -o examples/train_door_control2/docs/reports/MC-DC-Analysis.md \\
    examples/train_door_control2/src/**/*.c

  # Mode 2 - coverage evidence
  python3 tools/mcdc/mcdc_analyzer.py report \\
    --vectors examples/train_door_control2/docs/reports/MC-DC-Vectors.json \\
    --results examples/train_door_control2/test/results/test-results.json \\
    --sil 3 --project train_door_control2 \\
    --doc-id DOC-MCDC-EVIDENCE-2026-001 \\
    --format evidence \\
    -o examples/train_door_control2/docs/reports/MC-DC-Coverage-Evidence.md
"""

from __future__ import annotations

import glob
import json
import os
import sys
from pathlib import Path
from typing import List, Optional

# ---------------------------------------------------------------------------
# Ensure the tool's own directory is on sys.path so relative imports work
# regardless of where the script is called from.
# ---------------------------------------------------------------------------
_TOOL_DIR = Path(__file__).resolve().parent
if str(_TOOL_DIR) not in sys.path:
    sys.path.insert(0, str(_TOOL_DIR))

from c_parser import extract_expressions
from mcdc_engine import analyze_all
from report_gen import write_analysis_report, write_vectors_json, write_evidence_document
from coverage_tracker import load_vectors_json, load_test_results, compute_coverage


# ---------------------------------------------------------------------------
# Argument parsing (stdlib only — no click dependency for portability)
# ---------------------------------------------------------------------------

def _parse_args_analyze(argv: List[str]) -> dict:
    """Parse arguments for the 'analyze' subcommand."""
    opts = {
        'include_dirs': [],
        'sil': 3,
        'project': 'unknown',
        'format': 'all',
        'output': None,
        'doc_id': 'DOC-MCDC-ANALYSIS-2026-001',
        'use_pycparser': False,
        'source_files': [],
    }

    i = 0
    while i < len(argv):
        arg = argv[i]
        if arg in ('-I', '--include'):
            i += 1
            opts['include_dirs'].append(argv[i])
        elif arg.startswith('-I'):
            opts['include_dirs'].append(arg[2:])
        elif arg in ('--sil',):
            i += 1
            opts['sil'] = int(argv[i])
        elif arg in ('--project',):
            i += 1
            opts['project'] = argv[i]
        elif arg in ('--format',):
            i += 1
            opts['format'] = argv[i]
        elif arg in ('-o', '--output'):
            i += 1
            opts['output'] = argv[i]
        elif arg in ('--doc-id',):
            i += 1
            opts['doc_id'] = argv[i]
        elif arg in ('--pycparser',):
            opts['use_pycparser'] = True
        elif not arg.startswith('-'):
            # Could be a glob pattern or direct file
            expanded = glob.glob(arg, recursive=True)
            if expanded:
                opts['source_files'].extend(expanded)
            else:
                opts['source_files'].append(arg)
        i += 1

    return opts


def _parse_args_report(argv: List[str]) -> dict:
    """Parse arguments for the 'report' subcommand."""
    opts = {
        'vectors': None,
        'results': None,
        'sil': 3,
        'project': 'unknown',
        'doc_id': 'DOC-MCDC-EVIDENCE-2026-001',
        'format': 'evidence',
        'output': None,
    }

    i = 0
    while i < len(argv):
        arg = argv[i]
        if arg in ('--vectors',):
            i += 1
            opts['vectors'] = argv[i]
        elif arg in ('--results',):
            i += 1
            opts['results'] = argv[i]
        elif arg in ('--sil',):
            i += 1
            opts['sil'] = int(argv[i])
        elif arg in ('--project',):
            i += 1
            opts['project'] = argv[i]
        elif arg in ('--doc-id',):
            i += 1
            opts['doc_id'] = argv[i]
        elif arg in ('--format',):
            i += 1
            opts['format'] = argv[i]
        elif arg in ('-o', '--output'):
            i += 1
            opts['output'] = argv[i]
        i += 1

    return opts


# ---------------------------------------------------------------------------
# Subcommand: analyze
# ---------------------------------------------------------------------------

def cmd_analyze(argv: List[str]) -> int:
    opts = _parse_args_analyze(argv)

    if not opts['source_files']:
        print("ERROR: No source files specified.", file=sys.stderr)
        print("Usage: mcdc_analyzer.py analyze [options] <file.c> ...", file=sys.stderr)
        return 1

    # Filter to .c files only
    c_files = [f for f in opts['source_files'] if f.endswith('.c')]
    if not c_files:
        print("ERROR: No .c files found in the provided paths.", file=sys.stderr)
        return 1

    print(f"[INFO] Analyzing {len(c_files)} source file(s)...")
    for f in c_files:
        print(f"[INFO]   {f}")

    # Extract expressions
    expressions = extract_expressions(
        source_files=c_files,
        include_dirs=opts['include_dirs'] or None,
        use_pycparser=opts['use_pycparser'],
    )

    print(f"[INFO] Found {len(expressions)} compound boolean expression(s)")

    if not expressions:
        print("[WARN] No compound boolean expressions found. "
              "Check source file paths and include directories.", file=sys.stderr)

    # Run MC/DC engine
    results = analyze_all(expressions)

    total_vectors = sum(len(r.minimal_vectors) for r in results)
    print(f"[INFO] Total minimal MC/DC test vectors required: {total_vectors}")

    # Determine output paths
    output_base = opts['output']
    if output_base is None:
        output_base = 'MC-DC-Analysis.md'

    output_path = Path(output_base)
    # Derive JSON path: same directory, MC-DC-Vectors.json
    json_path = output_path.parent / 'MC-DC-Vectors.json'

    fmt = opts['format']
    if fmt in ('all', 'md', 'markdown'):
        write_analysis_report(
            results,
            str(output_path),
            project=opts['project'],
            sil_level=opts['sil'],
            doc_id=opts['doc_id'],
        )

    if fmt in ('all', 'json'):
        write_vectors_json(
            results,
            str(json_path),
            project=opts['project'],
            sil_level=opts['sil'],
        )
    elif fmt == 'all':
        # Already handled above
        pass

    if fmt == 'all':
        # Write both
        write_vectors_json(
            results,
            str(json_path),
            project=opts['project'],
            sil_level=opts['sil'],
        )

    # Print summary
    print(f"\n[SUMMARY] MC/DC Analysis Complete")
    print(f"  Expressions:     {len(expressions)}")
    print(f"  Total vectors:   {total_vectors}")
    achievable = sum(1 for r in results if r.is_achievable)
    print(f"  Achievable:      {achievable}/{len(results)}")
    print(f"  Analysis report: {output_path}")
    print(f"  Vectors JSON:    {json_path}")

    return 0


# ---------------------------------------------------------------------------
# Subcommand: report
# ---------------------------------------------------------------------------

def cmd_report(argv: List[str]) -> int:
    opts = _parse_args_report(argv)

    if not opts['vectors']:
        print("ERROR: --vectors <MC-DC-Vectors.json> is required.", file=sys.stderr)
        return 1

    if not opts['results']:
        print("ERROR: --results <test-results.json> is required.", file=sys.stderr)
        return 1

    if not Path(opts['vectors']).exists():
        print(f"ERROR: Vectors file not found: {opts['vectors']}", file=sys.stderr)
        return 1

    if not Path(opts['results']).exists():
        print(f"ERROR: Test results file not found: {opts['results']}", file=sys.stderr)
        return 1

    print(f"[INFO] Loading vectors from: {opts['vectors']}")
    vectors_data = load_vectors_json(opts['vectors'])

    # Inject project/sil from command line if overriding
    if opts['project'] != 'unknown':
        vectors_data['project'] = opts['project']
    if opts['sil'] != 3:
        vectors_data['sil_level'] = opts['sil']

    print(f"[INFO] Loading test results from: {opts['results']}")
    test_results = load_test_results(opts['results'])

    print(f"[INFO] Computing MC/DC coverage...")
    coverage = compute_coverage(vectors_data, test_results)

    # Determine output path
    output_path = opts['output'] or 'MC-DC-Coverage-Evidence.md'

    write_evidence_document(
        coverage,
        output_path,
        doc_id=opts['doc_id'],
    )

    # Print summary
    print(f"\n[SUMMARY] MC/DC Coverage Report Complete")
    print(f"  Project:           {coverage.project}")
    print(f"  SIL Level:         {coverage.sil_level}")
    print(f"  Expressions:       {coverage.total_expressions}")
    print(f"  Fully covered:     {coverage.fully_covered_expressions}/{coverage.total_expressions}")
    print(f"  Overall coverage:  {coverage.overall_coverage_pct:.1f}%")
    sil_status = "PASS" if coverage.meets_sil3_requirement else "FAIL"
    print(f"  SIL {coverage.sil_level} requirement:  {sil_status}")
    if coverage.gap_summary:
        print(f"\n  Coverage gaps:")
        for gap in coverage.gap_summary:
            print(f"    - {gap}")
    print(f"\n  Evidence document: {output_path}")

    return 0 if coverage.meets_sil3_requirement else 1


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main() -> int:
    argv = sys.argv[1:]

    if not argv or argv[0] in ('-h', '--help'):
        print(__doc__)
        return 0

    subcommand = argv[0]
    rest = argv[1:]

    if subcommand == 'analyze':
        return cmd_analyze(rest)
    elif subcommand == 'report':
        return cmd_report(rest)
    else:
        print(f"ERROR: Unknown subcommand '{subcommand}'. Use 'analyze' or 'report'.",
              file=sys.stderr)
        print(__doc__, file=sys.stderr)
        return 1


if __name__ == '__main__':
    sys.exit(main())
