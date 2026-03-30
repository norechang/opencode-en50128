---
name: en50128-lifecycle-tool-integration
description: workspace.py trace/wf command reference, EN 50128 coverage table, and statistics for COD lifecycle coordination
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  role: lifecycle-coordinator
---

# COD Tool Integration Reference

**Load trigger**: Load this skill when executing any `workspace.py trace` or `workspace.py wf`
command, or when reviewing EN 50128 coverage statistics.

**Canonical invocation**: `python3 tools/workspace.py <command>` from `[PROJECT_ROOT]`.

---

## Traceability Commands (`workspace.py trace`)

**Create a traceability link**:
```bash
python3 tools/workspace.py trace create \
  --from <SOURCE_ID> \
  --to <TARGET_ID>
```

**Validate traceability** (gap detection):
```bash
python3 tools/workspace.py trace validate --sil <0-4>

# With optional phase filter:
python3 tools/workspace.py trace validate --sil <0-4> --phase <phase>

# Output includes:
# - Forward coverage % (requirements → implementation)
# - Backward coverage % (implementation → requirements)
# - Gap detection
# - SIL compliance (PASS/FAIL)
```

**Check for traceability gaps**:
```bash
python3 tools/workspace.py trace check-gaps --sil <0-4>

# With optional phase filter:
python3 tools/workspace.py trace check-gaps --sil <0-4> --phase <phase>
```

**Generate RTM Reports**:
```bash
# Markdown report
python3 tools/workspace.py trace report \
  --from <SOURCE_TYPE> \
  --to <TARGET_TYPE> \
  --format markdown \
  --output docs/traceability/rtm.md

# CSV report
python3 tools/workspace.py trace report \
  --from <SOURCE_TYPE> \
  --to <TARGET_TYPE> \
  --format csv \
  --output docs/traceability/rtm.csv

```
Note: supported formats are markdown, csv, and json.
      HTML is not supported by the traceability tool.

**RTM Queries**:
```bash
# Forward query from a source artifact
python3 tools/workspace.py trace query \
  --source <SOURCE_ID> \
  --direction forward

# Backward query (upstream traceability)
python3 tools/workspace.py trace query \
  --source <SOURCE_ID> \
  --direction backward

# Query both directions
python3 tools/workspace.py trace query \
  --source <SOURCE_ID> \
  --direction both
```

**Import / Export traceability data**:
```bash
# Import from CSV
python3 tools/workspace.py trace import \
  --file <PATH> \
  --type <TYPE> \
  --format csv

# Export matrix
python3 tools/workspace.py trace export \
  --matrix <NAME|all> \
  --format csv \
  --output <PATH>
```

**Extract traceability items from a document**:
```bash
python3 tools/workspace.py trace extract \
  --document <PATH> \
  --type <TYPE>
```

**Visualize traceability**:
```bash
python3 tools/workspace.py trace visualize \
  --from <TYPE> \
  --to <TYPE> \
  --format mermaid \
  --output <PATH>
```

**Sync traceability matrix**:
```bash
python3 tools/workspace.py trace sync --matrix <NAME|all>
```

**Normative T-rule gate check** (reads `activities/traceability.yaml`):
```bash
# Check all T-rules applicable up to and including <phase>.
# Exits 0 = all rules PASS; 1 = one or more FAIL.
# Valid phases: planning | requirements | design | component-design |
#               implementation-testing | integration | validation
python3 tools/workspace.py trace gate-check \
    --phase <phase> \
    --sil <0-4>

# Example — Phase 2 (requirements) gate check at SIL 3:
python3 tools/workspace.py trace gate-check --phase requirements --sil 3

# Output includes per-rule PASS/FAIL with normative clause citations
# and a summary line.  T14 (100% coverage SIL 3-4) is reported as a
# PASS note showing the threshold applied.  T15 (VER process obligation)
# is reported as a Process Note — no matrix to check.
```

**Mark a traceability link as role-verified**:
```bash
python3 tools/workspace.py trace verify-link \
    --matrix <MATRIX_NAME> \
    --source <SOURCE_ID> \
    --target <TARGET_ID> \
    --name '<Reviewer Name or Role>'
# Optional: --date YYYY-MM-DD  (defaults to today)
# Writes verified=true, verified_by, verified_date back to the CSV
# and regenerates the JSON/MD sidecar files.
```

---

## Matrix Naming Convention

All traceability matrix CSVs live under `evidence/traceability/` and follow:

```
doc<FROM>_to_doc<TO>.csv
```

where `<FROM>` and `<TO>` are Annex C document numbers or system-document
identifiers (S1–S4).  Examples:

| T-Rule | Matrix file | Description |
|--------|-------------|-------------|
| T1 | `docS1_to_doc6.csv` | System Requirements → SRS |
| T2 | `docS4_to_doc6.csv` | Safety Plan → SRS |
| T3 | `doc6_to_doc9.csv` | SRS → Architecture |
| T4 | `doc9_to_doc6.csv` | Architecture → SRS (backward) |
| T5a | `doc10_to_doc9.csv` | Design Spec → Architecture |
| T5b | `doc10_to_doc6.csv` | Design Spec → SRS |
| T5c | `doc10_to_doc11.csv` | Design Spec → Interface Spec |
| T6 | `doc15_to_doc10.csv` | Component Design → Design Spec |
| T7 | `doc18_to_doc15.csv` | Source Code → Component Design |
| T8 | `doc7_to_doc6.csv` | Overall Test Spec → SRS |
| T9 | `doc6_to_doc7.csv` | SRS → Overall Test Spec (backward) |
| T10a | `doc12_to_doc6.csv` etc. | Integration Test Spec → SRS/Arch/Design/Interface |
| T11 | `doc16_to_doc15.csv` | Component Test Spec → Component Design |
| T12a | `doc20_to_doc16.csv` | Component Test Report → Component Test Spec |
| T13 | `doc25_to_doc6.csv` | Validation Report → SRS |

---

## Tool Limitations

| Command | Scope | Notes |
|---------|-------|-------|
| `trace validate --sil N` | Per-matrix gap detection | Does NOT check T1–T15 normative rules; use for individual matrix completeness |
| `trace check-gaps --sil N` | Per-matrix gap listing | Same scope limitation as `validate` |
| `trace gate-check --phase P --sil N` | T1–T15 normative rules | Primary phase gate command; cumulative (all rules up to phase P) |
| `trace verify-link` | Single link sign-off | Marks one (source, target) pair verified in named matrix CSV |

---

## Workflow Management Commands (`workspace.py wf`)

**Document Submission**:
```bash
python3 tools/workspace.py wf submit <DOCUMENT_ID> \
  --path <path-to-document> \
  --author-role <ROLE> \
  --author-name '<Name>' \
  --sil <0-4>
```

**Document Review** (record a review decision):
```bash
# Approve
python3 tools/workspace.py wf review <DOCUMENT_ID> \
  --role <ROLE> \
  --name '<Name>' \
  --approve \
  --comment "Review findings / rationale"

# Reject
python3 tools/workspace.py wf review <DOCUMENT_ID> \
  --role <ROLE> \
  --name '<Name>' \
  --reject \
  --comment "<finding summary>"
```

**Document Approval** (final approve after all reviews):
```bash
python3 tools/workspace.py wf approve <DOCUMENT_ID>

# Force approve (use with caution):
python3 tools/workspace.py wf approve <DOCUMENT_ID> --force
```

**Check Workflow Status**:
```bash
# All documents
python3 tools/workspace.py wf status --all --format markdown

# Specific document
python3 tools/workspace.py wf status --document <DOCUMENT_ID>

# Filter by phase
python3 tools/workspace.py wf status --phase <PHASE> --format markdown

# Show approval details
python3 tools/workspace.py wf status --document <DOCUMENT_ID> --approvals
```

**Document Workflow History**:
```bash
python3 tools/workspace.py wf history <DOCUMENT_ID>

# JSON output (structured):
python3 tools/workspace.py wf history <DOCUMENT_ID> --format json

# NOTE: --format timeline is accepted by argparse but NOT implemented in
# workflow_manager.py; it silently falls through to plain-text output.
# Use --format json or omit --format for reliable results.
```

**Baseline Management**:
```bash
# Create a baseline (--tag is required)
python3 tools/workspace.py wf baseline \
  --tag <TAG> \
  --phase <PHASE> \
  --message "<message>"

# Baseline a specific document
python3 tools/workspace.py wf baseline \
  --tag <TAG> \
  --document <DOCUMENT_ID>
```

**Gate Check**:
```bash
# Run gate check for a lifecycle phase
python3 tools/workspace.py wf gate-check --phase <1-8>

# With SIL filter:
python3 tools/workspace.py wf gate-check --phase <1-8> --sil <0-4>

# JSON output:
python3 tools/workspace.py wf gate-check --phase <1-8> --format json
```

---

## Workspace Commands

```bash
# List all workspaces
python3 tools/workspace.py list

# Show active workspace
python3 tools/workspace.py status

# Create a new workspace
python3 tools/workspace.py create <project_name> --sil <0-4>

# Switch to a workspace
python3 tools/workspace.py switch <project_name>

# Archive a workspace
python3 tools/workspace.py archive <project_name>
```

---

## EN 50128 Coverage

This skill set provides complete coverage of EN 50128 lifecycle management requirements:

| EN 50128 Section | Description | Workflow Coverage |
|------------------|-------------|-------------------|
| **Section 5.3** | Software Lifecycle | V-Model Orchestration (all phases) |
| **Section 5.3.2.2** | Iterations | Iteration and Change Management |
| **Section 5.3.2.5** | Phase Planning | V-Model Orchestration (phase initialization) |
| **Section 5.3.2.7** | Traceability | RTM Management (bidirectional traceability) |
| **Section 6.2** | Verification | Phase Gate Management (VER approval) |
| **Section 6.4** | Change Control | Iteration and Change Management (CR process) |
| **Section 6.5** | Quality Assurance | Phase Gate Management (QUA approval) |
| **Section 6.6** | Configuration Management | V-Model Orchestration (baseline management) |
| **Annex C Table C.1** | Document Control | Phase Gate Management (deliverables per phase) |

**Table A.9: Software Quality Assurance Techniques (Traceability)**:

| # | Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Workflow |
|---|-----------|-------|---------|---------|----------|
| 10 | Traceability | R | HR | **M** | **RTM Management Workflow** |

**Key Requirements Covered**:
- **V-Model Structure** (Section 5.3): Highly recommended per §5.3, Figures 3–4; alternative models permissible per §5.3.2.14
- **Iterations** (Section 5.3.2.2): "The lifecycle model shall take into account the possibility of iterations in and between phases"
- **Phase Planning** (Section 5.3.2.5): "All activities to be performed during a phase shall be defined and planned prior to commencement"
- **Traceability** (Section 5.3.2.7): "For each document, traceability shall be provided" — bidirectional traceability with 100% coverage SIL 3-4
- **Document Control** (Annex C Table C.1): Phase-to-document mapping for all 8 phases

---

## References

- **EN 50128:2011 Section 5.3** - Software Lifecycle (V-Model highly recommended per §5.3, Figures 3–4; alternative models permissible per §5.3.2.14)
- **EN 50128:2011 Section 5.3.2.2** - Iterations ("shall take into account the possibility of iterations")
- **EN 50128:2011 Section 5.3.2.5** - Phase Planning ("activities shall be defined and planned prior to commencement")
- **EN 50128:2011 Section 5.3.2.7** - Traceability ("traceability shall be provided")
- **EN 50128:2011 Section 6.2** - Software Verification
- **EN 50128:2011 Section 6.4** - Problem Reporting and Change Control
- **EN 50128:2011 Section 6.5** - Software Quality Assurance
- **EN 50128:2011 Section 6.6** - Software Configuration Management
- **EN 50128:2011 Annex C Table C.1** - Software Document Control Summary
- **EN 50128:2011 Table A.9** - Software Quality Assurance Techniques (Traceability MANDATORY SIL 3-4)
