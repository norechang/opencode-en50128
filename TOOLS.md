# EN 50128 Software Tools — Classification, Qualification, and Management Policy

> **Document**: `TOOLS.md`
> **Standard**: EN 50128:2011 Railway Software Standard
> **Scope**: Normative policy for software tool classification (TCL), qualification obligations,
> tool category requirements by SIL, and tool management across the lifecycle.
> **Normative Basis**: §6.7 (Support tools and languages), §6.6 (Configuration management),
> §7.3.4.12 (tool justification in architecture phase)
> **References**: `LIFECYCLE.md`, `DELIVERABLES.md`, `WORKFLOW.md`, `AGENTS.md`,
> `ORGANIZATION.md`, `std/EN50128-2011.md`

All agents MUST consult this document before selecting, invoking, or reporting on any tool.
Specific tool instances, versions, invocation flags, and qualification evidence are recorded in
downstream operational documents derived from this policy.

---

## Document Index

| # | Section | Content |
|---|---------|---------|
| [1](#section-1) | Tool Confidence Level (TCL) Classification | T1/T2/T3 definitions, classification decision tree |
| [2](#section-2) | Third-Party vs. Platform-Developed Tools | Origin policy and ISA implications |
| [3](#section-3) | Tool Category Framework | Required tool categories by lifecycle activity and minimum TCL |
| [4](#section-4) | Qualification and Validation Process | 6-phase qualification workflow diagram |
| [5](#section-5) | SIL Requirements Matrix | M/HR/R obligations at each SIL level |
| [6](#section-6) | Tool Management Obligations | Versioning, CM, lifecycle obligations |
| [7](#section-7) | ISA Evaluation Obligations | What the ISA will examine |

---

## Section 1 — Tool Confidence Level (TCL) Classification {#section-1}

EN 50128 §6.7 establishes three Tool Confidence Levels. Every tool used in a SIL project
SHALL be assigned a TCL before use (§6.7.4.1).

### TCL Definitions (§6.7.4, Table 1)

| TCL | Standard Definition | Applicable Sub-clauses |
|-----|--------------------|-----------------------|
| **T1** | The tool output is not used to directly support the development process and errors in the output cannot directly introduce errors into the executable software | §6.7.4.1 only |
| **T2** | The tool is used to support the development process but cannot introduce errors into the executable software unless errors are detected by independent processes | §6.7.4.1, 6.7.4.2, 6.7.4.3, 6.7.4.10, 6.7.4.11 |
| **T3** | The tool is used to support the development process and can introduce errors into the executable software that cannot be detected by independent processes | §6.7.4.1–6.7.4.5, 6.7.4.6–6.7.4.9 (as applicable), 6.7.4.10, 6.7.4.11 |

### TCL Classification Decision Tree

```
┌─────────────────────────────────────────────────────────────────────────┐
│                     TCL CLASSIFICATION DECISION TREE                    │
│                       EN 50128 §6.7 (Table 1)                           │
└─────────────────────────────────────────────────────────────────────────┘

  START: Does tool output directly support the development process?
  │
  ├── NO  ──► Is the tool output used in any way that could affect
  │           the executable software (even indirectly)?
  │           │
  │           ├── NO  ──► T1 (informational only — no qualification)
  │           └── YES ──► continue below ↓
  │
  └── YES ──► Can tool errors introduce faults into the executable
              software undetected by independent processes?
              │
              ├── NO  ──► Does an independent process (separate tool,
              │           manual review, diverse analysis) detect any
              │           errors the tool may produce?
              │           │
              │           ├── YES ──► T2 (validation test suite + report)
              │           └── NO  ──► T3 (full qualification evidence)
              │
              └── YES ──► T3 (full qualification evidence + report)

  KEY PRINCIPLE: When in doubt, assign the higher TCL.
  Downgrading from T3 to T2 or T1 REQUIRES documented justification (§6.7.4.2).
```

### TCL Assignment Obligations

- **T1**: No qualification document required. Record the basis for T1 assignment.
- **T2**: Validation test suite and validation report required (§6.7.4.3, §6.7.4.10, §6.7.4.11).
  - Tool SHALL have a specification or manual defining behaviour and constraints.
  - Configuration management SHALL ensure only justified versions are used.
  - Each new version SHALL be re-justified.
- **T3**: Full qualification evidence required (§6.7.4.4, §6.7.4.5). Evidence may include:
  - History of successful use in equivalent safety-critical environments (§6.7.4.4a)
  - Tool validation per §6.7.4.5 (documented test cases, results, discrepancies)
  - Diverse redundant code enabling detection of tool-introduced errors (§6.7.4.4c)
  - Compliance evidence from a risk analysis of the development process (§6.7.4.4d)

---

## Section 2 — Third-Party vs. Platform-Developed Tools {#section-2}

This distinction is critical for ISA evaluation. The evidence obligations differ substantially.

### Third-Party Tools (supplier-originated)

Evidence package = **supplier evidence** + **project-specific validation**.

Acceptable supplier evidence forms (§6.7.4.4):
- Supplier's own documented test suite and results
- ISO/IEC or other international standard conformance certifications
- Documented history of successful use in equivalent safety-critical domains
  (e.g. IEC 61508 SIL-4, DO-178C Level A, ASIL-D — for T3 tools)
- Vendor-published errata and bug-fix records demonstrating tool maturity

The project SHALL supplement supplier evidence with project-specific validation
demonstrating fitness for purpose in the actual development environment.

### Platform-Developed Tools (produced within the project)

Evidence package = **project-produced evidence only**. No supplier evidence exists.

```
┌──────────────────────────────────────────────────────────────────────┐
│           PLATFORM-DEVELOPED TOOL: EVIDENCE IMPLICATIONS             │
├──────────┬───────────────────────────────────────────────────────────┤
│ T1       │ Every tool output MUST be verified by an independent      │
│          │ human reviewer. Document which EN 50128 role performs     │
│          │ this review and record the review outcome.               │
├──────────┬───────────────────────────────────────────────────────────┤
│ T2       │ Project MUST produce a complete validation test suite     │
│          │ authored by the project. No external evidence exists.     │
│          │ Test suite SHALL cover: normal operation, boundary        │
│          │ conditions, error injection, and regression.             │
├──────────┬───────────────────────────────────────────────────────────┤
│ T3       │ Platform-developed T3 tools are STRONGLY DISCOURAGED.    │
│          │ Full qualification from scratch is required with no       │
│          │ supplier evidence to draw upon. Assign T3 to             │
│          │ platform-developed tools only with explicit COD/VMGR     │
│          │ approval and documented justification.                   │
└──────────┴───────────────────────────────────────────────────────────┘
```

**`to_be_provided` status**: Acceptable during development phases. Evidence gaps that remain
`to_be_provided` MUST be resolved and closed before ISA evaluation. The ISA will scrutinise
platform-developed T2 tools more closely than established third-party tools with industry
usage history.

---

## Section 3 — Tool Category Framework {#section-3}

EN 50128 §6.7.4.1 Note identifies the following categories of tools relevant to the software
development lifecycle. The table below defines the required tool categories, minimum TCL, and
EN 50128 reference for each. Specific tool instances that fulfil each category are
recorded in downstream operational documents.

```
  TOOL CATEGORIES BY LIFECYCLE ACTIVITY (EN 50128 §6.7.4.1 Note)
  ─────────────────────────────────────────────────────────────────
  a) Transformation / translation tools  (compilers, linkers, assemblers,
     code generators) — directly produce executable software → T3

  b) Verification and validation tools  (static analysers, coverage monitors,
     theorem provers, simulators, model checkers) → T2 minimum

  c) Diagnostic tools  (monitoring and maintaining software under operating
     conditions) → T1 minimum

  d) Infrastructure tools  (development support systems, build automation,
     test execution frameworks) → T2 minimum where output used directly

  e) Configuration control tools  (version control, baseline management) → T1
     (output independently verified by lifecycle review process)

  f) Application data tools  (parameter configuration, instrument range tools)
     → TCL depends on independence of output verification
```

### Tool Category Requirements by SIL

| Category | Lifecycle Phase(s) | Min TCL | Mandatory From | EN 50128 Ref |
|----------|--------------------|---------|----------------|--------------|
| Compiler / Linker / Assembler | Phase 5 (Implementation) | T3 | SIL 1+ | §6.7.4.4, §7.4, Table A.4 |
| Build automation | Phases 5–6 (Impl. + Integration) | T2 | SIL 1+ | §6.6, §6.7.4.2 |
| Static analysis | Phase 5 (Implementation) | T2 | SIL 2 (HR), SIL 3–4 (M) | Table A.19 |
| Complexity analysis | Phase 5 (Implementation) | T2 | SIL 3–4 (M) | Table A.19 |
| Code coverage measurement | Phase 5 (Implementation) | T2 | SIL 2 (HR), SIL 3–4 (HR) | Table A.21 |
| MC/DC coverage analysis | Phase 5 (Implementation) | T1 min | SIL 3–4 (HR) | Table A.21 |
| Dynamic / memory analysis | Phases 5–6 | T1 min | SIL 3–4 (HR) | Table A.13 |
| Test execution framework | Phases 4–7 (Testing) | T2 | SIL 1+ | Table A.5 |
| MISRA C compliance checker | Phase 5 (Implementation) | T2 | SIL 2 (M), SIL 3–4 (M) | Table A.19, §7.4 |
| Hardware emulation / simulation | Phase 6 (Integration) | T1/T2 | SIL 3–4 (HR) | §7.6, Table A.6 |
| Version control / CM | All phases | T1 | All SIL (M) | §6.6, Table A.9 |
| Documentation generation | All phases (optional) | T1 | — (optional) | §7.1 |
| Project / lifecycle management | All phases (platform) | T1 | — (platform ext.) | §5.3 |
| Document template validation | Phases 1–7 | T2 | SIL 2 (HR) | §6.5, Table A.9 |
| Reporting and traceability | All phases | T1 | — | §6.5 |

**Notes**:
- "SIL N (M)" = Mandatory from SIL N per the referenced Annex A table.
- "SIL N (HR)" = Highly Recommended from SIL N; rationale required if not used.
- Multiple independent static analysis tools are M at SIL 3–4 (Table A.19).
- The minimum TCL stated is a lower bound; projects MAY assign a higher TCL.

---

## Section 4 — Qualification and Validation Process {#section-4}

The tool qualification and validation process runs from tool selection through ISA evaluation.
It is activated at the phase where each tool is first introduced.

```
╔══════════════════════════════════════════════════════════════════════════════╗
║          TOOL QUALIFICATION PROCESS — EN 50128 §6.7                         ║
╚══════════════════════════════════════════════════════════════════════════════╝

  PHASE 1 — Selection and TCL Classification
  ┌────────────────────────────────────────────────────────────────────────┐
  │ • Identify tool category and lifecycle phase of use (§6.7.4.1)        │
  │ • Apply TCL decision tree (Section 1 of this document)                │
  │ • Record TCL assignment and justification (§6.7.4.2)                  │
  │ • Identify tool origin: third-party or platform-developed (Section 2) │
  │ • Select tool version; record in CM baseline (§6.7.4.10)              │
  └────────────────────────────────────────────────────────────────────────┘
                              │
                              ▼
  PHASE 2 — Evidence Gathering
  ┌────────────────────────────────────────────────────────────────────────┐
  │ FOR T2 TOOLS:                                                          │
  │ • Obtain tool specification or manual (§6.7.4.3)                      │
  │ • Gather supplier evidence (if third-party): certifications, test     │
  │   results, history of use in safety-critical domains (§6.7.4.4a)     │
  │ FOR T3 TOOLS (additional):                                            │
  │ • Gather full conformance evidence (§6.7.4.4)                        │
  │ • If evidence unavailable: apply §6.7.4.6 compensating measures       │
  │   (e.g. diverse redundant code, post-compilation checks)              │
  └────────────────────────────────────────────────────────────────────────┘
                              │
                              ▼
  PHASE 3 — Validation Test Suite (T2 and T3)
  ┌────────────────────────────────────────────────────────────────────────┐
  │ • Author project-specific validation test suite (§6.7.4.5)            │
  │ • Test coverage: normal operation, boundary conditions, error         │
  │   injection, and regression against known outputs                     │
  │ • For platform-developed tools: project authors ALL evidence          │
  │ • For third-party tools: supplement supplier evidence with            │
  │   project-specific validation for the deployment environment          │
  └────────────────────────────────────────────────────────────────────────┘
                              │
                              ▼
  PHASE 4 — Tool Validation Report (T2 and T3)
  ┌────────────────────────────────────────────────────────────────────────┐
  │ Report SHALL contain (§6.7.4.5):                                      │
  │   a) Record of validation activities                                  │
  │   b) Version of tool manual used                                      │
  │   c) Tool functions validated                                         │
  │   d) Tools and equipment used in validation                           │
  │   e) Results — pass or fail with reasons                             │
  │   f) Test cases and results for subsequent analysis                   │
  │   g) Discrepancies between expected and actual results               │
  │                                                                        │
  │ For T3: additionally document the selected evidence path              │
  │   (§6.7.4.4a–e) and any compensating measures (§6.7.4.6)             │
  └────────────────────────────────────────────────────────────────────────┘
                              │
                              ▼
  PHASE 5 — Version Control and Ongoing Qualification (§6.7.4.10–6.7.4.11)
  ┌────────────────────────────────────────────────────────────────────────┐
  │ • Lock tool version in CM baseline (T2 and T3 only)                   │
  │ • Version changes require a change request and re-justification       │
  │ • New version justification MAY reuse prior evidence if:              │
  │   a) functional differences do not affect toolset compatibility       │
  │   b) new version unlikely to contain significant new faults           │
  │ • Configuration management enforces version lock throughout lifecycle  │
  └────────────────────────────────────────────────────────────────────────┘
                              │
                              ▼
  PHASE 6 — ISA Evaluation Package
  ┌────────────────────────────────────────────────────────────────────────┐
  │ • All `to_be_provided` items MUST be resolved before ISA review       │
  │ • ISA evaluates: TCL justification, evidence completeness, version    │
  │   lock compliance, 3rd-party vs. platform-developed distinction       │
  │ • Output: Annex C Item 26 — Tools Validation Report (§7.7, Phase 7)  │
  │   (see DELIVERABLES.md for ownership and review chain)               │
  └────────────────────────────────────────────────────────────────────────┘
```

---

## Section 5 — SIL Requirements Matrix {#section-5}

Derived from EN 50128 §6.7 and Annex A Tables A.5, A.13, A.19, A.21.

| Obligation | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 |
|------------|-------|-------|-------|-------|-------|
| Assign TCL to every tool used | R | **M** | **M** | **M** | **M** |
| T2 tool: specification or manual | R | **M** | **M** | **M** | **M** |
| T2 tool: validation test suite | — | R | HR | **M** | **M** |
| T2 tool: validation report | — | R | HR | **M** | **M** |
| T3 tool: conformance evidence | R | **M** | **M** | **M** | **M** |
| T3 tool: qualification report | — | HR | HR | **M** | **M** |
| Tool version lock (CM, §6.7.4.10) | R | R | **M** | **M** | **M** |
| Version-change re-justification | — | R | **M** | **M** | **M** |
| Multiple independent static analyzers | — | — | HR | **M** | **M** |
| Compiler output independently verified | R | R | HR | **M** | **M** |
| Tools Validation Report (Annex C item 26) | — | HR | HR | **M** | **M** |

**Legend**: **M** = Mandatory · HR = Highly Recommended (rationale required if not applied) ·
R = Recommended · — = No specific requirement

---

## Section 6 — Tool Management Obligations {#section-6}

### Lifecycle Integration (§6.7.4.1)

Tools shall be selected as a coherent part of the software development activities (§6.7.4.1).
Tool selection SHALL be documented in the Software Development Plan or equivalent planning
document. Tool categories required for each lifecycle phase SHALL be identified at Phase 1
(Planning) and recorded in the Software Quality Assurance Plan (SQAP).

### Configuration Management (§6.7.4.10, §6.7.4.11)

```
  TOOL CM OBLIGATIONS (§6.7.4.10–6.7.4.11)
  ──────────────────────────────────────────
  ALL tools in T2 and T3:

  ┌─ Version lock ──────────────────────────────────────────────────────┐
  │  Only justified versions may be used. Version recorded in CM        │
  │  baseline. Version changes require a change request through CCB.    │
  └─────────────────────────────────────────────────────────────────────┘

  ┌─ Version-change re-justification ───────────────────────────────────┐
  │  Prior evidence MAY be reused if:                                   │
  │    a) functional differences will not affect toolset compatibility  │
  │    b) new version unlikely to contain significant new faults        │
  │  Otherwise: full re-validation required.                            │
  └─────────────────────────────────────────────────────────────────────┘

  ┌─ Evidence retention ────────────────────────────────────────────────┐
  │  All qualification and validation evidence SHALL be retained for    │
  │  the full software lifecycle (including maintenance phase).         │
  │  CM baseline includes: tool version, evidence document references,  │
  │  validation report identifier, and `to_be_provided` status.        │
  └─────────────────────────────────────────────────────────────────────┘
```

### Tool Selection in the Architecture Phase (§7.3.4.12)

The selection and justification of T2 and T3 tools SHALL be documented as part of the
Software Architecture Specification (SAS) activities in Phase 3 (see `LIFECYCLE.md`). The
SAS SHALL identify each tool's TCL, justification basis, and reference to qualification
evidence (§7.3.4.12).

### Automatic Translation and Code Generation (§6.7.4.9)

Where automatic code generation or similar automatic translation takes place, the suitability
of the translator for safety-related software SHALL be evaluated at the point in the
development lifecycle where development support tools are selected (Phase 3 or Phase 5 as
applicable). Translators are T3 by definition — they produce executable software output that
cannot be independently verified by a separate tool alone.

---

## Section 7 — ISA Evaluation Obligations {#section-7}

The Independent Safety Assessor (ASR) will examine tool qualification evidence as part of the
Phase 8 assessment. The ISA's review scope includes:

```
  ISA EVALUATION SCOPE — TOOLS (Phase 8, §6.4)
  ──────────────────────────────────────────────

  ┌─ TCL classification ────────────────────────────────────────────────┐
  │  • Is the assigned TCL correct for each tool's role?               │
  │  • Is T1 classification adequately justified (independent review)?  │
  │  • Is the T3 classification justification complete (§6.7.4.2)?     │
  └─────────────────────────────────────────────────────────────────────┘

  ┌─ T3 conformance evidence ───────────────────────────────────────────┐
  │  • Is evidence available per §6.7.4.4 (a–e)?                      │
  │  • If §6.7.4.6 compensating measures used: are they adequate?      │
  │  • Qualification report format compliance with §6.7.4.5?           │
  └─────────────────────────────────────────────────────────────────────┘

  ┌─ Platform-developed tools (heightened scrutiny) ────────────────────┐
  │  • T2 tools: is the project-authored validation test suite          │
  │    complete and independent of the tool's authors?                  │
  │  • T1 tools: are independent review records traceable to a role?   │
  │  • Are all `to_be_provided` items resolved?                        │
  └─────────────────────────────────────────────────────────────────────┘

  ┌─ Version control compliance ────────────────────────────────────────┐
  │  • Are T2/T3 tool versions locked in the CM baseline?               │
  │  • Are version-change justifications present (§6.7.4.11)?          │
  └─────────────────────────────────────────────────────────────────────┘

  ┌─ Tools Validation Report (Annex C item 26) ─────────────────────────┐
  │  • Produced in Phase 7 by VAL (see DELIVERABLES.md)                │
  │  • All tools used in the project must be accounted for             │
  │  • Evidence gaps = ISA finding; project must resolve before        │
  │    ISA issues final assessment report                              │
  └─────────────────────────────────────────────────────────────────────┘
```

**`to_be_provided` closure policy**: Any tool evidence recorded as `to_be_provided` is an
open qualification gap. The project SHALL track all open gaps and resolve them before
Phase 8 (Assessment). COD is responsible for ensuring no gaps remain open at the Phase 7
gate check (see `WORKFLOW.md`).

---

## References

| Document | Purpose |
|----------|---------|
| `std/EN50128-2011.md` | Normative standard — §6.7, §6.6, §7.3.4.12, §7.7, Annex A Tables A.5/A.13/A.19/A.21 |
| `LIFECYCLE.md` | Phase definitions — tool selection and qualification activities per phase |
| `DELIVERABLES.md` | Annex C item 26 (Tools Validation Report) — ownership and review chain |
| `WORKFLOW.md` | Phase gate authority — COD gate checks include tool qualification status |
| `AGENTS.md` | Agent role definitions — tool usage context per EN 50128 role |
| `ORGANIZATION.md` | Independence requirements — verifier and validator independence for T2/T3 evidence review |
