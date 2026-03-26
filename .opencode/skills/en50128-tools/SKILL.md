# EN 50128 Tools Skill

**EN 50128 Reference**: Section 6.7 — Software Tools and Their Validation
**Target Roles**: All agents (REQ, DES, IMP, TST, VER, INT, VAL, SAF, QUA, CM, PM, COD)

---

## Authoritative Sources

Load these documents to answer any question about tool selection, classification,
qualification, or usage:

| Source | Contents |
|--------|----------|
| `TOOLS.md` | TCL classification policy, master tool catalog table, SIL requirements, agent responsibility matrix, agent usage protocol |
| `activities/tool-management.yaml` | Qualification process (6 phases), 3rd-party vs. platform-developed distinction, ISA requirements, tool classification decision tree, per-agent tool selection, usage patterns, to-be-provided tracker |
| `tools/catalog/<tool-id>.yaml` | Per-tool: origin, TCL, version, location, mandatory_by_sil, key_flags, qualification_status, evidence paths |
| `tools/tool-validation/<tool-id>/` | Validation suite stubs (README + VALIDATION-PLAN.md) for platform-developed T2 tools |
| `deliverables/tools/` | Tool Qualification Report template (T3), Tool Validation Report template (T2) |

---

## Key Policy Points

### TCL Classification (§6.7)
- **T1**: output verified by human or independent process → no qualification required
- **T2**: output used directly, verified by another tool/process → validation test suite + report
- **T3**: output not verified by other means → full qualification evidence + report

### 3rd-Party vs. Platform-Developed (critical for ISA)
- **3rd-party tools**: supplement project validation with supplier evidence (test suite, certifications, industry usage in safety-critical projects)
- **Platform-developed tools**: NO supplier evidence — project must produce ALL evidence from scratch; T1 classification requires documented independent review of every output; T2 requires a project-authored validation test suite
- **`to_be_provided`**: acceptable during development; **mandatory to resolve before ISA evaluation**

### Mandatory Tools for SIL 3-4
- Compiler: GCC (T3, qualified)
- Static analysis: Cppcheck AND Clang (both mandatory)
- Complexity: Lizard (CCN ≤ 10 mandatory)
- Coverage: gcov + lcov (statement + branch + condition mandatory)
- MC/DC: mcdc_analyzer.py (T1, mandatory)
- Version control: Git (T1, mandatory all SILs)
- Test framework: Unity (T2, mandatory)

### Platform-Developed T2 Tools — Validation Required Before ISA
| Tool | Validation Plan |
|------|----------------|
| `check_misra.py` | `tools/tool-validation/check-misra/VALIDATION-PLAN.md` |
| `parse_coverage_report.py` | `tools/tool-validation/parse-coverage-report/VALIDATION-PLAN.md` |
| `validate_srs_template.py` | `tools/tool-validation/validate-srs/VALIDATION-PLAN.md` |
| `validate_sas_sds_template.py` | `tools/tool-validation/validate-sas-sds/VALIDATION-PLAN.md` |

---

## Quick Tool Lookup

Find any tool by ID in `tools/catalog/`. Current catalog IDs:

**Third-party**: `gcc` · `make` · `cppcheck` · `clang` · `lizard` · `gcov-lcov` · `valgrind` · `git` · `unity` · `qemu` · `pclint` · `splint` · `doxygen`

**Platform-developed**: `mcdc-analyzer` · `workspace` · `enhelp` · `misra-checker` · `workflow-manager` · `generate-test-report` · `parse-coverage-report` · `validate-srs` · `validate-sas-sds` · `tool-validation-scripts`
