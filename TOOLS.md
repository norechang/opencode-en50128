# EN 50128 Tool Catalog

**EN 50128 Reference**: Section 6.7 — Software Tools and Their Validation
**Purpose**: Fundamental policy document for tool classification, qualification,
and management. Authoritative reference for all agents on tool selection and TCL rules.

**Operational detail** (workflows, usage patterns, qualification process):
→ `activities/tool-management.yaml`

**Per-tool metadata** (version, flags, qualification status, evidence paths):
→ `tools/catalog/<tool-id>.yaml`

**Validation suite stubs** (for platform-developed T2 tools):
→ `tools/tool-validation/<tool-id>/`

**Report templates**:
→ `deliverables/tools/Tool-Qualification-Report-template.md` (T3)
→ `deliverables/tools/Tool-Validation-Report-template.md` (T2)

---

## Tool Confidence Levels (TCL)

Per EN 50128 Section 6.7, every tool must be classified before use in a SIL project.

| TCL | Description | Qualification Required | EN 50128 Reference |
|-----|-------------|------------------------|-------------------|
| **T1** | Output verified by human review or independent process | No | §6.7.4.2 |
| **T2** | Output used directly; verified by another independent tool/process | Validation test suite + report | §6.7.4.3 |
| **T3** | Output not verified by other means; errors directly affect safety | Full qualification evidence + report | §6.7.4.4 |

**Classification Decision Tree** (see `activities/tool-management.yaml` for full algorithm):
```
Is tool output verified by review or independent process? → YES → T1
                                                         ↓ NO
Is output used directly in the project?            → NO (info only) → T1
                                                         ↓ YES
Is output verified by another independent tool?    → YES → T2
                                                         ↓ NO
                                                         T3
```

---

## 3rd-Party vs. Platform-Developed Tools

This distinction is **critical for ISA evaluation**.

### 3rd-Party Tools (supplier-originated)

Evidence package = **supplier evidence** + **project-specific validation**.

Supplier evidence may include: the supplier's own test suite results, ISO/IEC
conformance documentation, evidence of use in equivalent safety-critical domains
(ASIL-D, DO-178C, SIL-4 projects), or certifications.

### Platform-Developed Tools (built within this project)

Evidence package = **project-produced evidence only**. No supplier evidence exists.

Key implications:
- T1 classification is only defensible if **every tool output is verified by an
  independent human reviewer**. Document which role verifies what output.
- T2 classification requires a **project-authored validation test suite** and formal
  report. The project cannot rely on any external evidence.
- The ISA will scrutinise platform-developed T2/T3 tools more closely than
  well-established 3rd-party tools.

**`to_be_provided` status**: Acceptable during development. **Must be resolved
before ISA evaluation.** See `activities/tool-management.yaml §to_be_provided_tracker`
for the full list of tools requiring evidence.

---

## SIL Requirements Summary

| Requirement | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 |
|-------------|-------|-------|-------|-------|-------|
| Tool classification (TCL) | R | **M** | **M** | **M** | **M** |
| T2 tool validation | R | **M** | **M** | **M** | **M** |
| T3 tool qualification | R | **M** | **M** | **M** | **M** |
| Tool qualification report | — | HR | HR | **M** | **M** |
| Tool version control | HR | HR | **M** | **M** | **M** |
| Validation test suite | — | R | HR | **M** | **M** |
| Multiple static analyzers | — | — | HR | **M** | **M** |
| Tool version lock (CR to update) | — | — | HR | **M** | **M** |

**Legend**: M = Mandatory, HR = Highly Recommended, R = Recommended, — = No requirement

---

## Master Tool Catalog

All tools used in this platform. See `tools/catalog/<id>.yaml` for full details.

### Third-Party Tools

| Tool | ID | Category | TCL | Mandatory From | Qualification Status |
|------|----|----------|-----|----------------|---------------------|
| GCC 13.3.0 | `gcc` | Compiler | T3 | SIL 1 | `to_be_provided` |
| GNU Make 4.3 | `make` | Build | T2 | SIL 1 | `to_be_provided` |
| Cppcheck 2.13.0 | `cppcheck` | Static Analysis | T2 | SIL 1 | `to_be_provided` |
| Clang SA 18.x | `clang` | Static Analysis | T2 | SIL 3 (mandatory) | `to_be_provided` |
| Lizard 1.17.x | `lizard` | Complexity | T2 | SIL 3 (mandatory) | `to_be_provided` |
| gcov 13.3.0 + lcov 1.16 | `gcov-lcov` | Coverage | T2 | SIL 2 | `to_be_provided` |
| Valgrind 3.21.0 | `valgrind` | Memory Analysis | T1 | SIL 3 (HR) | `not_required` |
| Git 2.43.0 | `git` | Config Mgmt | T1 | SIL 0 (M) | `not_required` |
| Unity 2.5.x | `unity` | Test Framework | T2 | SIL 3 (mandatory) | `to_be_provided` |
| QEMU 8.2.2 | `qemu` | HW Emulation | T1/T2 | SIL 3 (HR) | `to_be_provided` (T2 usage) |
| PC-lint Plus 2.0+ | `pclint` | MISRA C | T2 | SIL 3 (HR) | `to_be_provided` |
| Splint 3.1.x | `splint` | Static Analysis | T1 | — (optional) | `not_required` |
| Doxygen 1.x | `doxygen` | Documentation | T1 | — (optional) | `not_required` |

### Platform-Developed Tools

| Tool | ID | Category | TCL | Mandatory From | Qualification Status |
|------|----|----------|-----|----------------|---------------------|
| mcdc_analyzer.py | `mcdc-analyzer` | Coverage (MC/DC) | T1 | SIL 3 (mandatory) | `not_required` |
| workspace.py | `workspace` | Project Mgmt | T1 | — | `not_required` |
| enhelp.py | `enhelp` | Documentation | T1 | — | `not_required` |
| check_misra.py | `misra-checker` | MISRA Compliance | T2 | SIL 3 (HR) | `to_be_provided` |
| workflow_manager.py | `workflow-manager` | Lifecycle | T1 | — | `not_required` |
| generate_test_report.py | `generate-test-report` | Reporting | T1 | — | `not_required` |
| parse_coverage_report.py | `parse-coverage-report` | Coverage Analysis | T2 | SIL 2 | `to_be_provided` |
| validate_srs_template.py | `validate-srs` | Doc Validation | T2 | SIL 2 (HR) | `to_be_provided` |
| validate_sas_sds_template.py | `validate-sas-sds` | Doc Validation | T2 | SIL 2 (HR) | `to_be_provided` |
| check-tool-versions.sh + run-all-validations.sh | `tool-validation-scripts` | Tool Qual | T1 | SIL 2 | `not_required` |

---

## Agent Tool Responsibility Matrix

Primary tool responsibilities by agent role. See `activities/tool-management.yaml
§agent_tool_selection` for the complete per-agent tool list.

| Agent | Primary Tools | Mandatory SIL 3 Tools |
|-------|--------------|----------------------|
| **IMP** | gcc, make, git | gcc, make, cppcheck |
| **TST** | unity, gcov-lcov, mcdc-analyzer | unity, gcov-lcov, mcdc-analyzer |
| **VER** | cppcheck, clang, lizard, gcov-lcov | cppcheck + clang (both), lizard, parse-coverage-report |
| **INT** | gcc, make, unity, valgrind, qemu | gcc, make, unity |
| **VAL** | unity, gcov-lcov, qemu | — (project-specific) |
| **QUA** | validate-srs, validate-sas-sds, tool-validation-scripts | All T2/T3 qualification oversight |
| **CM** | git, workspace, tool-validation-scripts | git |
| **COD** | workspace, workflow-manager | workspace |
| **PM** | workspace, workflow-manager, git | workspace |

---

## Agent Tool Usage Protocol

Before using any tool, agents MUST:

1. **Check the master catalog table above** — identify the tool's TCL and whether it is mandatory for the project SIL.
2. **Read `tools/catalog/<id>.yaml`** — confirm version, key_flags, and qualification_status.
3. **Verify installation and version**: `which <tool> && <tool> --version`
4. **Check qualification status** — if `to_be_provided`, record the deviation before proceeding; do not treat unqualified T2/T3 tools as fully trusted.
5. **Execute with SIL-appropriate flags** from `tools/catalog/<id>.yaml`.
6. **Document results** — tool version, exact invocation, and output summary in the deliverable.

Full 6-step protocol: `activities/tool-management.yaml §agent_usage_protocol`

---

## References

- **EN 50128:2011** Section 6.7 — Software Tools and Their Validation
- **`activities/tool-management.yaml`** — operational workflows (qualification process, agent selection, usage patterns, to-be-provided tracker)
- **`tools/catalog/`** — per-tool metadata (version, flags, qualification status, evidence paths)
- **`tools/tool-validation/`** — validation suite runners and platform tool stubs
- **`deliverables/tools/`** — Tool Qualification and Validation Report templates
- **`AGENTS.md`** — agent role definitions (Tool Qualification section)
