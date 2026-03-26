# EN 50128 Tools Skill

**EN 50128 Reference**: Section 6.7 — Software Tools and Their Validation
**Target Roles**: All agents (REQ, DES, IMP, TST, VER, INT, VAL, SAF, QUA, CM, PM, COD)

This skill is the **operational gateway** for all tool-related agent tasks. It maps agent
actions to the concrete files, commands, and workflows that implement EN 50128 §6.7 policy.

Policy authority → `TOOLS.md`
Operational detail → `activities/tool-management.yaml`
Per-tool metadata → `tools/catalog/<tool-id>.yaml`

---

## 1 — Before Using Any Tool: 6-Step Protocol

Every agent MUST execute these steps before invoking any tool:

```
STEP 1 — Read the catalog entry
  tools/catalog/<tool-id>.yaml
  Confirm: tcl, version, key_flags, qualification_status.status

STEP 2 — Check qualification status
  status = not_required  → proceed (T1)
  status = validated     → proceed (T2, evidence complete)
  status = qualified     → proceed (T3, evidence complete)
  status = to_be_provided → record a deviation before proceeding;
                            do NOT treat the tool as fully trusted

STEP 3 — Verify installation and version
  which <tool> && <tool> --version
  Version MUST match the version field in tools/catalog/<tool-id>.yaml

STEP 4 — Verify tool versions match baseline (T2 and T3 tools)
  bash tools/tool-validation/check-tool-versions.sh

STEP 5 — Invoke with SIL-appropriate flags
  Use key_flags from tools/catalog/<tool-id>.yaml exactly.
  Document the exact invocation in the deliverable.

STEP 6 — Document results
  T1: record output summary and reviewer identity
  T2: cross-reference output with at least one other independent tool
  T3: verify qualification evidence is present and referenced
  Record: tool id, version, exact invocation, output summary
```

---

## 2 — Finding the Right Tool for a Task

### By agent role — read `activities/tool-management.yaml §agent_tool_selection`

| Agent | Primary tasks | Catalog IDs |
|-------|--------------|-------------|
| IMP | Compile, build, static analysis | `gcc` `make` `cppcheck` `misra-checker` `unity` `gcov-lcov` |
| TST | Test execution, coverage, MC/DC | `unity` `gcov-lcov` `parse-coverage-report` `mcdc-analyzer` `generate-test-report` |
| VER | Static analysis (all), complexity, coverage review | `cppcheck` `clang` `lizard` `gcov-lcov` `parse-coverage-report` `misra-checker` `pclint` `valgrind` |
| INT | Build, integration tests, hardware emulation | `gcc` `make` `unity` `valgrind` `qemu` |
| VAL | System testing, coverage, traceability | `unity` `gcov-lcov` `qemu` `workspace` |
| QUA | Document validation, tool qualification oversight | `validate-srs` `validate-sas-sds` `tool-validation-scripts` `workspace` |
| CM | Version control, baseline, version checks | `git` `workspace` `tool-validation-scripts` |
| COD | Lifecycle management, traceability | `workspace` `workflow-manager` |
| PM | Project status, reporting | `workspace` `workflow-manager` `generate-test-report` |
| REQ | Requirements, traceability | `workspace` `git` `validate-srs` |
| DES | Architecture, design validation | `workspace` `git` `validate-sas-sds` |
| SAF | Safety analysis support | `workspace` `git` |

### By task category — read `activities/tool-management.yaml §usage_patterns`

| Task | Tools (catalog IDs) | SIL 3–4 note |
|------|---------------------|--------------|
| Compile C source | `gcc` | flags from `tools/catalog/gcc.yaml §key_flags.sil_3` |
| Build | `make` | — |
| Static analysis | `cppcheck` + `clang` | **both** mandatory SIL 3–4 |
| MISRA C check | `misra-checker` or `pclint` | `misra-checker` = platform T2; `pclint` = 3rd-party T2 |
| Cyclomatic complexity | `lizard` | CCN ≤ 10 enforced; fail build if exceeded |
| Statement/branch/condition coverage | `gcov-lcov` | compile with `-fprofile-arcs -ftest-coverage` |
| Parse coverage report | `parse-coverage-report` | platform T2; outputs structured markdown |
| MC/DC analysis | `mcdc-analyzer` | platform T1; all outputs reviewed by TST/VER |
| Unit test execution | `unity` | 3rd-party T2 |
| Memory / leak analysis | `valgrind` | T1; exit code 1 on any error |
| Hardware emulation | `qemu` | T1 for functional, T2 if used for timing/perf |
| Version control / baseline | `git` | T1; mandatory all SIL |
| Workspace / lifecycle mgmt | `workspace` | T1; use for wf submit/approve/baseline |
| Workflow orchestration | `workflow-manager` | T1 |
| Traceability | `workspace trace` | T1 |
| SRS template validation | `validate-srs` | platform T2 |
| SAS/SDS template validation | `validate-sas-sds` | platform T2 |
| Test report generation | `generate-test-report` | T1; output reviewed by TST/PM |
| Tool version verification | `tool-validation-scripts` | run at every phase gate |

---

## 3 — Concrete Invocation Patterns

All patterns are canonical. Read `activities/tool-management.yaml §usage_patterns` for
the authoritative source of each. Read `tools/catalog/<id>.yaml §key_flags` for full flag sets.

### Compilation (IMP, INT)
```sh
# SIL 3 — from tools/catalog/gcc.yaml §key_flags.sil_3
gcc -std=c11 -Wall -Wextra -Werror -pedantic -O2 \
    -DSIL_LEVEL=3 -DMISRA_C_2012 \
    -fstack-protector-strong -D_FORTIFY_SOURCE=2 \
    -fno-common -fno-builtin-malloc -fno-builtin-calloc \
    -fprofile-arcs -ftest-coverage \   # add for test builds
    -o <output> <sources>
```

### Static analysis — both mandatory at SIL 3–4 (VER, IMP)
```sh
cppcheck --enable=all --xml --xml-version=2 --addon=misra.py src/ 2> cppcheck.xml
scan-build -o analysis_results make
python3 tools/static-analysis/check_misra.py --src src/ --project <name>
```

### Complexity check (VER)
```sh
lizard src/ --CCN 10 --Threshold ccn=10    # exit non-zero if any function > CCN 10
```

### Coverage measurement (IMP, TST)
```sh
lcov --capture --directory . --output-file coverage.info
lcov --remove coverage.info '*/test/*' '*/unity/*' --output-file coverage.info
genhtml coverage.info --output-directory coverage_html
python3 tools/scripts/parse_coverage_report.py coverage.info \
    --sil 3 --output coverage-report.md
```

### MC/DC analysis (TST, VER)
```sh
python3 tools/mcdc/mcdc_analyzer.py analyze \
    -I src/ --sil 3 --project <name> --format all \
    -o docs/reports/MC-DC-Analysis.md src/**/*.c
python3 tools/mcdc/mcdc_analyzer.py report \
    --vectors docs/reports/MC-DC-Vectors.json \
    --results test/results/test-results.json \
    --sil 3 --project <name> \
    -o docs/reports/MC-DC-Coverage-Evidence.md
```

### Memory analysis (VER, INT)
```sh
valgrind --leak-check=full --show-leak-kinds=all \
         --track-origins=yes --error-exitcode=1 ./test_executable
```

### Tool version check (CM, QUA — every phase gate)
```sh
bash tools/tool-validation/check-tool-versions.sh
```

### Traceability (REQ, DES, VER, COD)
```sh
python3 tools/workspace.py trace create
python3 tools/workspace.py trace add <src_id> <dst_id>
python3 tools/workspace.py trace validate --phase <phase> --sil <n>
python3 tools/workspace.py trace check-gaps
python3 tools/workspace.py trace report
```

### Workflow submission and approval (all roles)
```sh
python3 tools/workspace.py wf submit <DOC-ID> --path <file> \
    --author-role <ROLE> --author-name '<Name>' --sil <n>
python3 tools/workspace.py wf review <DOC-ID> --action approve \
    --reviewer-role <ROLE> --reviewer-name '<Name>'
python3 tools/workspace.py wf approve <DOC-ID>
python3 tools/workspace.py wf baseline --phase <n>
python3 tools/workspace.py wf status --all --format markdown
```

### Document template validation (QUA, REQ, DES)
```sh
python3 tools/scripts/validate_srs_template.py <SRS-file>
python3 tools/scripts/validate_sas_sds_template.py <SAS-or-SDS-file>
```

---

## 4 — Tool Qualification Workflows

### Checking open qualification gaps
The `to_be_provided` tracker is in `activities/tool-management.yaml §to_be_provided_tracker`.
All gaps MUST be resolved before Phase 8 (ISA evaluation).

### Running a T2 validation suite (VER, QUA)
```
NOTE: A T2 TVR in §6.7.4.5 format is produced as a PROJECT POLICY EXTENSION
under §6.7.4.4 Note 2 — it is NOT a normative §6.7.4.5 obligation for T2 tools.
The normative T2 minimum is §6.7.4.3 (spec/manual) + §6.7.4.10/§6.7.4.11 (CM).
Record this distinction in the TVR document header.

1. Read tools/tool-validation/<tool-id>/VALIDATION-PLAN.md
2. Execute all test cases in tools/tool-validation/<tool-id>/
3. Document results in the TVR using:
   deliverables/tools/Tool-Validation-Report-template.md
4. Submit via:
   python3 tools/workspace.py wf submit <TVR-DOC-ID> --path <tvr-file> \
       --author-role VER --sil <n>
5. Obtain QUA + VER + PM sign-off (wf approve)
6. Update qualification_status.status to 'validated' in tools/catalog/<id>.yaml
```

### Producing a T3 qualification report (VER, QUA)
```
1. Assemble supplier evidence (certifications, test suite results, industry use)
2. Execute project-specific validation tests
3. Complete:  deliverables/tools/Tool-Qualification-Report-template.md
4. Submit + obtain QUA + VER + PM sign-off
5. Update qualification_status.status to 'qualified' in tools/catalog/<id>.yaml
```

### Full 6-phase qualification process
Read `activities/tool-management.yaml §tool_qualification_process` for the complete
phase-by-phase process (responsible roles, outputs, and gate criteria per phase).

---

## 5 — Key Policy Points (from TOOLS.md)

- **T1**: no qualification doc required — record independent review method in catalog entry
- **T2 normative minimum** (§6.7.4.3, §6.7.4.10, §6.7.4.11): tool specification or manual +
  justified version lock + version-change re-justification. These apply at all SILs once T2.
- **T2 project policy extension** (§6.7.4.4 Note 2 — permissive, not a §6.7.4.5 mandate):
  validation test suite + Tool Validation Report (TVR) in §6.7.4.5 format. Project policy
  makes this mandatory at SIL 2+; HR at SIL 1. The TVR exceeds the normative minimum.
  §6.7.4.5 is **T3-only** as a normative obligation (Table 1).
- **T3**: full qualification evidence (§6.7.4.4) + report per §6.7.4.5 mandatory at SIL 1–4.
  §6.7.4.5 lists the seven normative items: (a) validation activities, (b) manual version,
  (c) functions validated, (d) tools/equipment used, (e) results, (f) test cases, (g) discrepancies.
- **T3 classification test**: Does the tool generate outputs which can *directly or indirectly
  contribute to the executable code (including data)* of the safety-related system? (§3.1.44)
- **Build systems** (e.g. make): individually evaluate for T3 per TOOLS.md Section 3 — if
  Makefile configuration propagates undetected into compiled output, tool may be T3.
- **Platform-developed T2 tools**: project produces all evidence; no supplier evidence available
- **Two independent static analyzers** (both `cppcheck` AND `clang`): mandatory SIL 3–4
- **`to_be_provided`**: must be closed before ISA evaluation; COD tracks closure at gate checks
- **Version lock**: T2/T3 tool version changes require a CCB change request (§6.7.4.11 is an
  unconditional SHALL for all T2/T3 tool version changes regardless of SIL)

Full policy → `TOOLS.md`
Full SIL matrix → `TOOLS.md §Section 5`
ISA evaluation scope → `TOOLS.md §Section 7`
