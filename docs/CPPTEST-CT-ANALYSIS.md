# Parasoft C/C++test CT 2025.2 — EN 50128 Applicability Analysis

**Document status**: Analysis (informational — not a controlled deliverable)  
**Date**: 2026-03-26  
**Tool version**: C/C++test CT 2025.2.0 (build 10.7.3.20251120B1193)  
**Purpose**: Evaluate Parasoft C/C++test CT for use in EN 50128 railway safety software development on this platform; identify the tool's EN 50128 §6.7 classification, coverage metric applicability, evidential gaps it closes vs. the current platform stack, integration path, and qualification obligations.

---

## 1. Tool Overview

### 1.1 Product Identity

| Attribute | Value |
|---|---|
| Product name | Parasoft C/C++test CT |
| Version | 2025.2.0 (build 10.7.3.20251120B1193) |
| Publisher | Parasoft Corporation |
| Installation path | `/home/norechang/bin/cpptest-ct/` |
| License | Local license; EULA accepted (`parasoft.eula.accepted=true`) |
| Safety certification | TÜV SÜD certified for safety-related software development |

### 1.2 Key Binaries

| Binary | Path | Function |
|---|---|---|
| `cpptestct` | `<INSTALL>/cpptestct` | Top-level launcher (version, machine ID) |
| `cpptestcc` | `<INSTALL>/bin/cpptestcc` | Compiler instrumentation wrapper — prefixes `CC` commands to inject coverage probes |
| `cpptestcov` | `<INSTALL>/bin/cpptestcov` | Coverage data compute + report generation |
| `cpptestmcp` | `<INSTALL>/integration/mcp/cpptestmcp` | MCP server for LLM agent integration |

### 1.3 What the Tool Does

C/C++test CT provides **dynamic code coverage instrumentation and reporting** for C and C++ programs. It operates by wrapping the compilation command (`cpptestcc`) to inject lightweight probes into object code at build time. When the instrumented binary executes (whether driven by a test framework or any other harness), the probes emit a coverage log (`.clog`). The `cpptestcov compute` step reduces the log against source-map files (`.map`) to produce structured coverage data, which `cpptestcov report` renders in multiple output formats.

The tool does **not** replace the test framework; it wraps whatever build produces test executables. It is test-framework-agnostic.

---

## 2. Coverage Metrics

### 2.1 Supported Metrics

C/C++test CT supports eight coverage metrics, each controlled by a compiler-wrapper flag:

| # | Metric | Flag | Abbreviation |
|---|---|---|---|
| 1 | Line Coverage | `-line-coverage` | LC |
| 2 | Statement Coverage | `-statement-coverage` | SC |
| 3 | Block Coverage | `-block-coverage` | BC |
| 4 | Decision/Branch Coverage | `-decision-coverage` | DC |
| 5 | Simple Condition Coverage | `-simple-condition-coverage` | SCC |
| 6 | **Modified Condition/Decision Coverage** | **`-mcdc-coverage`** | **MC/DC** |
| 7 | Function Coverage | `-function-coverage` | FC |
| 8 | Call Coverage | `-call-coverage` | CC |

All metrics have an `-optimized-*-coverage` variant that reduces runtime overhead at the cost of some probe granularity — acceptable for performance-constrained targets, but the standard variant is preferred for normative evidence.

Multiple metrics can be enabled simultaneously by combining flags.

### 2.2 Mapping to EN 50128 Table A.21

EN 50128:2011 Table A.21 — *Test Coverage for Code* — defines five numbered coverage items. The table below maps each item to the corresponding C/C++test CT metric:

| Table A.21 Item | Description | EN 50128 Recommendation by SIL | C/C++test CT Metric |
|---|---|---|---|
| 1 | Statement | SIL 0: R, SIL 1: HR, SIL 2: HR, SIL 3: HR, SIL 4: HR | SC (`-statement-coverage`) |
| 2 | Branch | SIL 0: —, SIL 1: R, SIL 2: R, SIL 3: HR, SIL 4: HR | DC (`-decision-coverage`) |
| 3 | Compound Condition (MC/DC) | SIL 0: —, SIL 1: R, SIL 2: R, SIL 3: HR, SIL 4: HR | MC/DC (`-mcdc-coverage`) |
| 4 | Data Flow | SIL 0: —, SIL 1: —, SIL 2: —, SIL 3: R, SIL 4: R | Not directly supported (see §5.3) |
| 5 | Path | SIL 0: —, SIL 1: R, SIL 2: R, SIL 3: HR, SIL 4: HR | Not directly supported (see §5.3) |

**Key note on Table A.21 Requirement 2** (SIL 3–4 component-level): coverage shall be measured according to items {2 and 3}, or {2 and 4}, or {5}. C/C++test CT directly satisfies the {2 and 3} combination (Branch + MC/DC), which is the most common choice for structured C code.

**No mandatory percentage threshold** is specified by EN 50128:2011 Table A.21. The standard requires a *quantified measure* (Req. 1) and notes that high percentages are difficult to achieve; the judgment of sufficiency belongs to the project's VER/VMGR roles.

---

## 3. EN 50128 §6.7 Tool Classification

### 3.1 Classification Definitions (§3.1.42–§3.1.44)

| Class | Definition |
|---|---|
| **T1** | Generates no outputs that can directly or indirectly contribute to the executable code of the software. No qualification required. |
| **T2** | Supports test or verification; errors can fail to reveal defects but cannot directly create errors in the executable software. Requires: specification/manual (§6.7.4.3), CM version control (§6.7.4.10–11). TVR recommended at SIL 3–4. |
| **T3** | Generates outputs that can directly or indirectly contribute to the executable code of the safety-related system. Full qualification evidence required (§6.7.4.4–§6.7.4.5). |

### 3.2 Classification of C/C++test CT Components

#### `cpptestcc` — Compiler Instrumentation Wrapper

**Classification: T3 in instrumented test builds; excluded from production builds.**

`cpptestcc` modifies the compiled output — it injects coverage probes into object code. Under the strict §3.1.44 definition, any tool that modifies the compiled binary is T3. However, the critical mitigating factor is:

> **The production binary is never compiled with `cpptestcc`.** Instrumented builds are exclusively used for test/coverage measurement. The release binary is compiled with the unmodified compiler (GCC/Clang/etc.) following the standard production build configuration.

This separation is the normative industry practice for coverage tools in functional safety contexts and is consistent with the approach described in IEC 61508-3. The T3 classification applies only within the test build configuration; the production build has no exposure to `cpptestcc` outputs. The SQAP and build procedure documentation must explicitly state this separation.

**Required evidence for the test build context**:
- Build configuration documentation distinguishing instrumented from production builds
- CI/CD gate preventing instrumented binaries from reaching deployment
- CM version lock on `cpptestcc` version per §6.7.4.10–11

#### `cpptestcov` — Coverage Compute and Report Tool

**Classification: T2**

`cpptestcov` reduces coverage probe data and produces coverage percentage reports. It does not modify the executable under test. Its error modes are: (a) reporting incorrect coverage percentages, (b) failing to detect uncovered code. Neither error mode injects faults into the production software. This matches the §3.1.43 definition exactly — the standard's own example is "a test coverage measurement tool."

**Required evidence for T2**:
- Specification / user guide — fulfilled: `manuals/cpptest_ct_user_guide.pdf` present on-disk
- CM version control — `cpptestcov 2025.2.0 (10.7.3.20251120B1193)` must be recorded in the tool catalog
- Tool Validation Report (TVR) — recommended by platform policy at SIL 3–4; normatively required if TVR is adopted as evidence per §6.7.4.4 Note 2

#### Coverage Suppression Mechanism (`cpptestcov suppress`)

**Classification: T2 (same as `cpptestcov`)**

Suppression excludes specific code regions from coverage counting. Errors in suppression could cause uncovered code to be silently excluded from the metric, masking a coverage gap. This is a T2 error mode (fails to reveal a defect; cannot create an error in production software).

**Mandatory control**: All suppression entries must be human-reviewed. Suppressed items appear in reports as `(+N)` annotations — they are never silently dropped. The VER agent must explicitly accept each suppression justification as part of the coverage evidence review.

#### `cpptestmcp` — MCP Server

**Classification: T1**

The MCP server exposes coverage data and suppression guidance to LLM agents. It does not produce any output that contributes to the executable code or to normative coverage verdicts. Its outputs are advisory. T1 — no qualification obligations.

### 3.3 Classification Summary

| Component | TCL | Applicable §6.7 Sub-clauses | Notes |
|---|---|---|---|
| `cpptestcc` | T3 (test builds only) | §6.7.4.1–5, §6.7.4.10–11 | TÜV SÜD FS Distribution Package provides primary qualification evidence; build separation mandatory |
| `cpptestcov` | T2 | §6.7.4.1–3, §6.7.4.10–11 | TVR required at SIL 3–4 by platform policy |
| Suppression mechanism | T2 | §6.7.4.1–3, §6.7.4.10–11 | All suppressions require VER sign-off |
| `cpptestmcp` | T1 | §6.7.4.1 | No qualification obligation |

---

## 4. Gap Analysis: Current Platform vs. C/C++test CT

### 4.1 Current Platform Coverage Stack

The platform currently uses two coverage tools in combination:

| Tool | Catalog ID | TCL | Capability |
|---|---|---|---|
| gcov / lcov | `gcov-lcov` | T2 | Statement + branch coverage; runtime instrumentation via GCC `--coverage` flag; lcov-format HTML/text reports |
| MC/DC Analyzer | `mcdc-analyzer` | T1 | **Static** MC/DC analysis — identifies independent condition pairs and generates test vectors from source code AST; does NOT instrument or measure runtime coverage |

### 4.2 The MC/DC Evidential Gap

The current `mcdc_analyzer.py` is a **T1 static analysis tool**. It identifies what MC/DC test vectors *should* be written and can confirm that a given test exercises a particular condition combination when provided with manually annotated test results. However, it does not:

- Instrument the binary to detect which branches were actually taken at runtime
- Provide automated runtime MC/DC coverage measurement
- Produce a machine-verifiable MC/DC coverage percentage without manual correlation

This is a significant evidential gap for SIL 3–4 gate checks. The chain of evidence for MC/DC currently is:

```
static analysis → manual test vector authoring → manual test execution
→ manually annotated results → human correlation → MC/DC coverage claim
```

Every step after "static analysis" is a manual process. The human correlation is the sole basis for the MC/DC coverage verdict, with no independent automated check.

### 4.3 How C/C++test CT Closes the Gap

With `cpptestcc -mcdc-coverage`, the MC/DC evidence chain becomes:

```
static analysis (mcdc_analyzer.py, retained) → test vector authoring
→ instrumented test execution (cpptestcc probes) → clog collection
→ cpptestcov compute → machine-verified MC/DC coverage report
```

The runtime measurement independently confirms which condition-decision pairs were exercised. The automated measurement is:

1. **Independent of the test author** — the probe fires regardless of how the test was written
2. **Audit-ready** — the `.clog` and coverage data files are artifacts that can be archived as evidence
3. **Machine-verifiable** — a coverage gate (e.g., "MC/DC ≥ 85% before gate-check") can be enforced automatically in CI

This is a materially stronger evidential basis than the current manual approach, and directly addresses the T1 limitation of `mcdc_analyzer.py`.

### 4.4 What gcov/lcov Continues to Provide

C/C++test CT supplements, not replaces, the current gcov/lcov stack:

| Capability | gcov/lcov | C/C++test CT |
|---|---|---|
| Statement coverage (runtime) | Yes | Yes |
| Branch/Decision coverage (runtime) | Yes | Yes |
| MC/DC coverage (runtime) | No | **Yes** |
| lcov-format output | Yes (native) | Yes (`cpptestcov report lcov`) |
| HTML report | Yes (genhtml) | Yes (built-in HTML report) |
| Compiler support | GCC only (gcov is GCC-specific) | GCC, Clang, ARM Compiler, GHS, IAR, TI, Wind River, QNX |
| Cross-compilation support | Limited | Extensive (see §6.2) |
| CI/CD integration | Manual lcov invocation | Native CI/CD workflow support |
| TÜV SÜD qualification | None | Yes (FS Distribution Package) |

**Recommended approach**: Retain gcov/lcov as the baseline coverage tool (it is already in the catalog, already qualified within the project's T2 framework, and familiar to the team). Add C/C++test CT alongside it, specifically for MC/DC coverage measurement at SIL 3–4. The lcov output compatibility means `parse_coverage_report.py` can consume both sources.

### 4.5 Cross-Compiler Coverage — Embedded Targets

gcov requires GCC instrumentation (`--coverage`) and is only available with GCC. For embedded targets using ARM Compiler 6 (Keil/armclang), Green Hills, IAR, TI, or Wind River compilers, gcov provides no coverage at all. C/C++test CT supports all of these with the same `cpptestcc` wrapper interface — the coverage collection mechanism is compiler-independent. This is a significant advantage for projects targeting non-GCC embedded toolchains.

---

## 5. Integration Path

### 5.1 Principle: Wrap the Existing Build, Keep Unity

The integration does not require changes to the test framework. Unity remains the test runner. `cpptestcc` wraps the compiler command in the build system so that the same Unity test binary is compiled with coverage probes:

```
# Without C/C++test CT (current):
gcc -fprofile-arcs -ftest-coverage -I unity/src unity/src/unity.c test_foo.c foo.c -o test_foo

# With C/C++test CT (instrumented test build):
cpptestcc -compiler gcc_13-64 -- gcc -I unity/src unity/src/unity.c test_foo.c foo.c -o test_foo
```

The `--` separator passes the remainder of the command verbatim to GCC. gcov flags (`-fprofile-arcs -ftest-coverage`) are dropped in the C/C++test CT build because the probe injection is done by `cpptestcc`, not GCC. The two coverage systems should not be active simultaneously on the same build.

### 5.2 Four-Step Workflow

```bash
# Step 1: Compile with cpptestcc instrumentation
cpptestcc -compiler gcc_13-64 \
  -mcdc-coverage -decision-coverage -statement-coverage \
  -- gcc -I unity/src unity/src/unity.c test_foo.c foo.c -o test_foo_cov

# Step 2: Execute the instrumented test binary (Unity runner, as normal)
./test_foo_cov

# Step 3: Compute coverage data from probe log
cpptestcov compute \
  -map=.cpptest/cpptestcc \
  -clog=cpptest_results.clog \
  -out=cov-data

# Step 4: Generate reports
cpptestcov report text  cov-data          # summary to stdout
cpptestcov report html  cov-data          # HTML drill-down
cpptestcov report lcov  cov-data          # lcov format (for parse_coverage_report.py)
```

### 5.3 Makefile Integration Pattern

The existing `examples/train_door_control2/Makefile` uses a `CC ?= gcc` pattern. The simplest integration is a parallel `coverage-mcdc` target:

```makefile
CPPTESTCC ?= /home/norechang/bin/cpptest-ct/bin/cpptestcc
CPPTESTCOV ?= /home/norechang/bin/cpptest-ct/bin/cpptestcov
CPPTEST_COMPILER ?= gcc_13-64
CPPTEST_METRICS ?= -mcdc-coverage -decision-coverage -statement-coverage

coverage-mcdc: $(SRCS) $(TEST_SRCS)
	$(CPPTESTCC) -compiler $(CPPTEST_COMPILER) $(CPPTEST_METRICS) \
	  -- $(CC) $(CFLAGS_TEST) $(SRCS) $(TEST_SRCS) -o $(TARGET)_cov
	./$(TARGET)_cov
	$(CPPTESTCOV) compute \
	  -map=.cpptest/cpptestcc \
	  -clog=cpptest_results.clog \
	  -out=cov-data-mcdc
	$(CPPTESTCOV) report text cov-data-mcdc
	$(CPPTESTCOV) report lcov cov-data-mcdc
```

This target runs in isolation; it does not interfere with the standard `coverage` target (which uses gcov/lcov).

### 5.4 CMake Integration

C/C++test CT ships a drop-in CMake plugin at `<INSTALL>/integration/cmake/cpptest-coverage.cmake`. For projects using CMake, `include(cpptest-coverage.cmake)` and call `cpptestcov_target_enable_coverage(target METRICS mcdc decision statement)`. This is the recommended integration path for CMake-based builds.

### 5.5 Output Compatibility with Existing Platform Tools

`cpptestcov report lcov cov-data` produces lcov-format output. The platform's `parse_coverage_report.py` (`tools/catalog/parse-coverage-report.yaml`) already consumes lcov format. No changes to `parse_coverage_report.py` are required for statement and branch coverage integration. For MC/DC coverage, `parse_coverage_report.py` would need extension — lcov format does not carry an MC/DC section. The cpptestcov text and HTML reports are the primary evidence for MC/DC; the lcov output is supplementary for the existing branch/statement pipeline.

### 5.6 Data Flow Coverage (Table A.21 Item 4)

Table A.21 item 4 (Data Flow) is not directly instrumented by C/C++test CT. For SIL 3–4 projects where the {2 and 4} combination is preferred over {2 and 3}, data flow coverage must be established by other means (e.g., manual data flow analysis, a dedicated data flow analysis tool). The {2 and 3} combination (Branch + MC/DC) is the simpler path and is equally valid per Table A.21 Req. 2.

### 5.7 Path Coverage (Table A.21 Item 5)

Path coverage is not instrumented by C/C++test CT. Path coverage is impractical for all but trivial functions due to exponential path explosion. EN 50128 Table A.21 lists Path as HR for SIL 3–4, but the explicit Req. 2 alternatives ({2,3}, {2,4}, or {5}) mean that satisfying {2 and 3} through Branch + MC/DC is normatively equivalent and far more tractable.

---

## 6. Supported Compilers Relevant to EN 50128 Embedded Targets

The following compilers supported by `cpptestcc` are directly relevant to EN 50128 embedded development:

| Compiler | Versions | Target Architectures |
|---|---|---|
| GNU GCC | 7–14 | x86_64, aarch32, aarch64, PowerPC |
| Clang | 12–19 | x86_64, aarch64, aarch32 |
| ARM Compiler 6 (armclang/Keil) | 6.14, 6.16, 6.22 | aarch32, aarch64 |
| Green Hills | ARM64, TRICORE, V850 | — |
| IAR BXARM | 8.50, 9.20 | ARM (static analysis only in CT) |
| TI ARM | — | ARM Cortex-M/R/A |
| TI MSP430 | — | MSP430 |
| TI TMS320 | — | DSP |
| Wind River Diab | 5.9 | Various |
| Wind River LLVM | 8, 9 | Various |
| QNX GCC | 8, 12 | x86_64, aarch64 |

Note: IAR support in C/C++test CT is currently limited to static analysis; runtime instrumentation for IAR requires verification against the specific IAR version in use.

---

## 7. TÜV SÜD Functional Safety Distribution Package

### 7.1 What It Is

Parasoft provides a **Functional Safety Distribution Package** for C/C++test CT, available from the Parasoft Customer Portal (requires registration). This package is the primary qualification evidence for T3 use of `cpptestcc` and T2 use of `cpptestcov`.

### 7.2 Package Contents (as documented in the user guide)

| Document | Purpose |
|---|---|
| Qualified platforms, environments, and functionalities list | Defines the exact configurations in which the tool has been qualified — must match project's build environment |
| Recommended configuration for functional safety | Tool configuration settings required to activate/disable features for safety use |
| Known unresolved FS-relevant defects + workarounds | Mandatory review item; project must confirm that no open defects affect the specific coverage metrics being used |
| TÜV SÜD certificate | Certifies that Parasoft's development process for C/C++test CT meets functional safety tool qualification requirements |

### 7.3 How It Maps to §6.7.4.4 (T3 Qualification Evidence)

EN 50128 §6.7.4.4 requires that for T3 tools, evidence shall be available that the tool output conforms to its specification. §6.7.4.4(a) accepts: documented tool development process corresponding to a recognised industry standard (which TÜV SÜD certification satisfies). The FS Distribution Package is the mechanism by which Parasoft delivers this evidence to customers.

**Without the FS Distribution Package**, using `cpptestcc` in a T3 capacity at SIL 3–4 would require the project to independently validate the compiler instrumentation — an impractical burden. **Obtaining the FS Distribution Package is a prerequisite** for formal SIL 3–4 use of `cpptestcc`.

### 7.4 Action Required

1. Register on the Parasoft Customer Portal
2. Download the FS Distribution Package for C/C++test CT 2025.2
3. Review the qualified platforms list — confirm the project's GCC version and OS are listed
4. Review the open defects list — confirm no open issues affect `-mcdc-coverage`, `-decision-coverage`
5. Record the FS Distribution Package version in the tool catalog entry alongside the tool version
6. Store the FS Distribution Package in the project's CM-controlled tool evidence repository

---

## 8. Coverage Suppression

### 8.1 Mechanism

`cpptestcov suppress` allows specific source regions to be excluded from coverage counting. Two methods:

1. **In-source annotation**: `//CPPTEST_SUPPRESS_COVERAGE` placed immediately before the region to exclude; suppresses the next coverage element
2. **Regex-based suppression file**: A suppression config file specifying patterns (file paths, function names, line ranges)

### 8.2 Report Transparency

Suppressed items are **never silently dropped**. Reports display them as `(+N)` where N is the count of suppressed items. For example: `Decision coverage: 87% (+3 suppressed)` means 87% of non-suppressed decisions were covered, and 3 decisions were explicitly excluded.

### 8.3 EN 50128 Obligations for Suppression

Under EN 50128, any suppression of coverage must be justified and documented. Each suppressed item must have an explicit rationale (e.g., dead code proven unreachable by static analysis, defensive code that cannot be triggered in any test scenario, generated code not subject to unit testing). The VER agent is responsible for reviewing and approving all suppressions as part of the coverage evidence review. Unsupported suppressions are a non-conformance.

Platform policy: a dedicated **Coverage Suppression Register** (a tracked artifact, e.g., `docs/reports/Coverage-Suppression-Register.md`) should record each suppression entry with: location, rationale, alternative evidence, and VER sign-off. This is not a current platform artifact — it would need to be added as a deliverable if C/C++test CT suppression is used in a SIL 3–4 project.

---

## 9. Requirements Traceability

### 9.1 Capability

C/C++test CT supports requirements-to-test-to-coverage traceability when using GoogleTest. Test cases annotate their associated requirement IDs via `RecordProperty`:

```cpp
TEST(BrakeController, EmergencyStop) {
    RecordProperty("req", "SRS-BRAKE-001");
    // ... test body
}
```

When coverage data is published to Parasoft DTP via `cpptestcov report dtp`, the Traceability Pack extension constructs a requirement → test case → coverage linkage, enabling Annex C item traceability reports.

### 9.2 Applicability to This Platform

This platform uses **Unity**, not GoogleTest. The `RecordProperty` mechanism is a GoogleTest API and is not available in Unity. Therefore, the automated requirements-to-coverage traceability feature is **not directly applicable** to the current platform without framework migration.

Manual traceability (test case ID → requirement ID → coverage data, cross-referenced by document) remains the path for Unity-based projects. This is consistent with current platform practice.

If a future project elects to use GoogleTest instead of Unity, the traceability chain is available. C/C++test CT ships with a bundled GoogleTest 1.17.0 (`<INSTALL>/googletest/googletest.zip`) and a complete GoogleTest + coverage example at `<INSTALL>/examples/CovGoogleTest/`.

---

## 10. Qualification Obligations Summary

| Component | Status | Action Required |
|---|---|---|
| `cpptestcc` (T3, test builds) | Qualification evidence needed | Obtain TÜV SÜD FS Distribution Package; verify qualified platform list; add to tool catalog; document build separation |
| `cpptestcov` (T2) | TVR needed for SIL 3–4 | Create Tool Validation Report using platform TVR template; add to tool catalog with version lock |
| Suppression mechanism (T2) | Process control needed | Define Coverage Suppression Register artifact; add to VER checklist |
| `cpptestmcp` (T1) | No qualification needed | Record in catalog for CM purposes |

The platform's existing Tool Validation Report template (`deliverables/tools/Tool-Validation-Report-template.md`) is the correct template for the `cpptestcov` TVR.

---

## 11. Recommendation

### 11.1 Summary Recommendation

**Adopt C/C++test CT for MC/DC coverage measurement at SIL 3–4, supplementing the existing gcov/lcov stack.**

The tool closes the most significant evidential gap in the current coverage infrastructure: the absence of automated runtime MC/DC measurement. The current `mcdc_analyzer.py` approach, while valid as a T1 static tool, relies entirely on manual correlation between static vectors and runtime test execution — a process with no independent automated check. `cpptestcc -mcdc-coverage` provides that automated check.

### 11.2 Recommended Use Profile

| Metric | Tool | Notes |
|---|---|---|
| Statement coverage | gcov/lcov (retain) | Unchanged — already in catalog |
| Branch/Decision coverage | gcov/lcov (primary) + C/C++test CT (secondary) | lcov output from both; C/C++test CT provides cross-compiler coverage |
| **MC/DC coverage** | **C/C++test CT (cpptestcc -mcdc-coverage)** | **Primary gap closed by this integration** |
| Data flow coverage | Not instrumented (use static analysis) | Table A.21 {2,3} combination preferred over {2,4} |
| Path coverage | Not required (HR, Table A.21 {2,3} satisfies Req. 2) | — |

### 11.3 Pre-Adoption Checklist

Before formal adoption on a SIL 3–4 project:

- [ ] Obtain Parasoft FS Distribution Package v2025.2 from Customer Portal
- [ ] Confirm `gcc_13-64` (or project-specific compiler ID) is in the qualified platforms list
- [ ] Review open defects list — confirm no issues affect `-mcdc-coverage`
- [ ] Add `cpptestcc` and `cpptestcov` to `tools/catalog/` as separate entries
- [ ] Create Tool Validation Report for `cpptestcov` (T2)
- [ ] Define build configuration separation (instrumented vs. production) in SQAP and Makefile documentation
- [ ] Define Coverage Suppression Register artifact and add to VER phase checklist
- [ ] Pilot integration on the `examples/train_door_control2` example project to validate the four-step workflow

### 11.4 Limitations and Constraints

- Requires Java JRE 17–21 on the build host (already present — `cpptestct` works)
- `cpptestcc` and `gcov` cannot both instrument the same build target simultaneously — parallel build configurations are required
- Requirements-to-coverage automated traceability requires GoogleTest; not available with Unity
- IAR compiler support is currently static analysis only in C/C++test CT; embedded IAR projects cannot use `-mcdc-coverage` instrumentation
- No percentage threshold is mandated by EN 50128 — the VER/VMGR roles must set project-specific thresholds and document the rationale

---

## Appendix A: File and Directory Reference

### C/C++test CT Installation

```
/home/norechang/bin/cpptest-ct/
  cpptestct                              Top-level launcher
  cpptestct.properties                   License config (EULA accepted, local license)
  bin/cpptestcc                          Compiler instrumentation wrapper
  bin/cpptestcov                         Coverage compute + report tool
  bin/commands/                          Subcommand implementations
  bin/engine/                            Coverage engine
  manuals/cpptest_ct_user_guide.pdf      User guide (primary documentation)
  integration/cmake/cpptest-coverage.cmake  CMake drop-in plugin
  integration/bazel/                     Bazel rules
  integration/mcp/cpptestmcp             MCP server
  integration/docker/cpptest-ct.dockerfile  Docker image builder
  examples/CovApplication/              CMake + Bazel example
  examples/CovGoogleTest/               GoogleTest + coverage example
  googletest/googletest.zip             Bundled GoogleTest 1.17.0
```

### Platform Files Relevant to This Integration

```
/home/norechang/work/EN50128/
  TOOLS.md                               Policy authority (ISA PASS v1.3)
  std/EN50128-2011.md                    §3.1.42–3.1.44 (T1/T2/T3), Table A.21
  tools/catalog/gcov-lcov.yaml           Current coverage tool (T2, to_be_provided)
  tools/catalog/mcdc-analyzer.yaml       Current MC/DC tool (T1, static only)
  tools/catalog/unity.yaml               Test framework (T2, to_be_provided)
  tools/mcdc/mcdc_analyzer.py            Static MC/DC analysis (retained)
  tools/mcdc/coverage_tracker.py
  tools/mcdc/report_gen.py
  deliverables/tools/Tool-Validation-Report-template.md   TVR template
  examples/train_door_control2/Makefile  Reference build system (Unity + gcov)
```

---

## Appendix B: EN 50128 Standard References

| Reference | Content |
|---|---|
| §3.1.42 | Tool class T1 definition |
| §3.1.43 | Tool class T2 definition |
| §3.1.44 | Tool class T3 definition |
| §6.7 | Software tools (complete section) |
| §6.7.4.2 | Justification requirement for T2/T3 |
| §6.7.4.3 | Specification/manual requirement for T2/T3 |
| §6.7.4.4 | Conformance evidence requirement for T3 |
| §6.7.4.5 | Tool Validation Report requirements |
| §6.7.4.10–11 | CM version control for T2/T3 |
| §6.7.4.12 / Table 1 | Tool class vs. applicable sub-clauses matrix |
| Table A.21 | Test Coverage for Code — metric recommendations by SIL |
| Table A.21 Req. 2 | SIL 3–4 component-level: {2,3} or {2,4} or {5} |
