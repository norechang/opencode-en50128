# EN 50128 Traceability Role Responsibilities - Standards Analysis

> **Project**: TDC (Train Door Control System) SIL 3  
> **Date**: 2026-04-03  
> **Purpose**: Determine role responsibilities for creating and validating traceability evidence per EN 50128:2011  
> **Status**: Standards Analysis Complete ✅

---

## Executive Summary

**CRITICAL FINDING**: EN 50128:2011 does NOT assign traceability creation to a single role. Instead:

1. **Each document author is responsible for tracing their document** to its inputs per §5.3.2.7
2. **CM is responsible for managing traceability artifacts** per §6.5.4.15 (configuration management)
3. **VER is responsible for verifying traceability completeness** per §6.5.4.14–6.5.4.17
4. **VAL performs 2nd check of traceability** per two-track workflow
5. **COD enforces traceability at gate checks** per lifecycle authority

**CONCLUSION**: The current gap (14 missing CSV files in Phase 3) is a **WORKFLOW INTEGRATION ISSUE**, not a tool problem. The CM agent should have used the `trace extract`, `trace sync`, and `trace create` commands to produce machine-readable evidence from the documents.

---

## 1. EN 50128:2011 Standard Citations

### 1.1 General Traceability Requirement (§5.3.2.7)

> **§5.3.2.7**: "For each document, traceability shall be provided in terms of a unique reference number and a defined and documented relationship with other documents."

**Interpretation**: Each document author must provide traceability when they create the document. This is not a separate CM activity — it's intrinsic to document creation.

**Platform Implementation**: 
- REQ creates SRS → REQ must trace SRS requirements to S1 (System Requirements) and S4 (System Safety Requirements)
- DES creates SAS → DES must trace SAS components to SRS requirements
- DES creates SDS → DES must trace SDS modules to SAS components and SRS requirements
- TST creates test specs → TST must trace test cases to requirements/design

---

### 1.2 Configuration Management Responsibility (§6.5.4.15)

> **§6.5.4.15**: "Within the context of this European Standard, and to a degree appropriate to the specified software safety integrity level, traceability shall particularly address:
> 
> a) traceability of requirements to the design or other objects which fulfil them,
> b) traceability of design objects to the implementation objects which instantiate them,
> c) traceability of requirements and design objects to the tests (component, integration, overall test) and analyses that verify them.
> 
> **Traceability shall be the subject of configuration management.**"

**Interpretation**: CM is responsible for **managing** traceability artifacts (baselines, version control, change tracking), NOT for creating the initial traces.

**Platform Implementation**:
- CM maintains the `evidence/traceability/` directory under version control
- CM ensures traceability artifacts are baselined (included in formal releases)
- CM tracks changes to traceability when documents are updated via CCB

---

### 1.3 Annex D.59 Additional Guidance

> **Annex D, Section D.59 (informative)**: "The output of the Traceability process shall be the subject of formal Configuration Management." (line 6818)

**Interpretation**: Confirms that CM manages the traceability **outputs** (CSV files, RTM documents), not the traceability **creation process**.

---

### 1.4 Verification Responsibility (§6.5.4.14–6.5.4.17)

> **§6.5.4.14**: "Traceability to requirements shall be an important consideration in the validation of a safety-related system and means shall be provided to allow this to be demonstrated throughout all phases of the lifecycle."

> **§6.2.4.11(a)**: "Once the Software Verification Plan has been established, verification shall address:
> a) that the Software Verification Plan meets the general requirements for readability and **traceability** in 5.3.2.7 to 5.3.2.10 and in **6.5.4.14 to 6.5.4.17**"

**Per-Phase VER Traceability Verification Clauses**:
- **Phase 1**: §6.2.4.11(a) — SVP meets §5.3.2.7–5.3.2.10, §6.5.4.14–6.5.4.17
- **Phase 2**: §7.2.4.22(b) — SRS meets §5.3.2.7–5.3.2.10, §6.5.4.14–6.5.4.17
- **Phase 3**: §7.3.4.41(c), §7.3.4.41(d), §7.3.4.41(e) — SAS, SIS, SDS meet traceability requirements
- **Phase 4**: §7.4.4.13 — Component Design Verification
- **Phase 5**: §7.5.4.10 — Source Code Verification
- **Phase 6**: §7.6.4.13 — Integration Verification

**Interpretation**: VER is responsible for **verifying** that traceability exists and is complete. VER does NOT create the traces — VER checks that the document authors created them correctly.

**Platform Implementation**:
- VER runs `trace validate --sil 3` to check traceability completeness
- VER runs `trace gate-check --phase design --sil 3` before producing Verification Report
- VER documents traceability findings in each phase's Verification Report (Items 2, 8, 14, 17, 19, 23, etc.)

---

### 1.5 Validation 2nd Check (§6.3, Two-Track Workflow)

> **§6.3.1.1**: "The objective of software validation is to demonstrate that the processes and their outputs are such that the software is of the defined software safety integrity level, fulfils the software requirements and is fit for its intended application. This activity is performed by the Validator."

**Interpretation**: VAL performs independent 2nd check of all deliverables, including traceability artifacts. VAL reviews VER's traceability verification report.

**Platform Implementation** (per `WORKFLOW.md`):
- Track A: PM orchestrates development + VER 1st check
- Track B: VMGR coordinates VAL 2nd check
- Both tracks must complete before COD gate-check

---

## 2. Role Responsibility Matrix

| Activity | Responsible Role | EN 50128 Reference | Platform Implementation |
|----------|------------------|-------------------|-------------------------|
| **Create traceability when authoring documents** | REQ, DES, IMP, TST, INT (document authors) | §5.3.2.7 | Authors embed trace IDs in documents; CM extracts to CSV using `trace extract` or `trace sync` |
| **Manage traceability artifacts under version control** | CM | §6.5.4.15, §6.6.1.2 | CM maintains `evidence/traceability/*.csv` in git baseline; creates CSV files if authors only provide Markdown |
| **Verify traceability completeness and correctness** | VER | §6.5.4.14–6.5.4.17, per-phase clauses | VER runs `trace validate`, `trace gate-check`; documents findings in Verification Reports |
| **Validate traceability (2nd check)** | VAL | §6.3, Annex C Table C.1 | VAL reviews VER report + runs independent checks; reports to VMGR |
| **Enforce traceability at phase gates** | COD | §5.3, lifecycle authority | COD runs `@cod gate-check` — BLOCKS gate if VER/VAL not complete |

---

## 3. TDC Phase 3 Gap Analysis

### 3.1 What Happened

**Phase 3 Track A Execution**:
1. ✅ PM invoked DES agent → produced SAS, SDS, SIS (Items 9, 10, 11)
2. ✅ PM invoked INT agent → produced Integration Test Specs (Items 12, 13)
3. ✅ PM invoked CM agent → produced `Requirements-Traceability-Matrix.md` (774 lines, Markdown format)
4. ❌ CM agent did NOT create 14 CSV evidence files required for automated validation
5. ✅ QUA reviewed all documents → 71% first-pass acceptance
6. ⏳ VER has NOT been invoked yet (Track B pending)

**Root Cause**: CM agent created high-quality Markdown RTM but did NOT use the traceability tools (`trace extract`, `trace sync`, `trace create`) to produce machine-readable CSV files.

---

### 3.2 What Should Have Happened

**Correct Phase 3 Track A Workflow**:

1. **DES creates design documents** (SAS, SDS, SIS)
   - DES embeds trace IDs in documents:
     - SAS components reference SRS requirements: `[Trace: SRS-REQ-001, SRS-REQ-002]`
     - SDS modules reference SAS components: `[Trace: SAS-COMP-DCS]`
     - SDS modules reference SRS requirements: `[Trace: SRS-REQ-001]`

2. **INT creates integration test specs** (Items 12, 13)
   - INT embeds trace IDs: `[Trace: SRS-REQ-001, SAS-COMP-DCS, SDS-MOD-001]`

3. **CM consolidates traceability**:
   - **EITHER**: CM runs `trace extract` on all Phase 3 documents → auto-generates CSV files
   - **OR**: CM manually creates CSV files using `trace create`
   - **OR**: CM updates existing CSV files using `trace sync`
   - CM produces Markdown RTM as **summary/reporting artifact** (not the normative evidence)

4. **Result**: 14 CSV files created in `evidence/traceability/`:
   - `doc6_to_doc9.csv` (SRS → SAS)
   - `doc9_to_doc6.csv` (SAS → SRS backward)
   - `doc10_to_doc9.csv` (SDS → SAS)
   - `doc10_to_doc6.csv` (SDS → SRS)
   - `doc10_to_doc11.csv` (SDS → Interface Specs)
   - `doc12_to_doc6.csv`, `doc12_to_doc9.csv`, `doc12_to_doc10.csv`, `doc12_to_doc11.csv` (Integration Test Spec → all upstream)
   - `doc13_to_doc6.csv`, `doc13_to_doc9.csv`, `doc13_to_doc10.csv`, `doc13_to_docS1.csv`, `doc13_to_docS2.csv` (HW/SW Integration Test Spec → all upstream)

5. **QUA reviews** → checks that CSV files exist and Markdown RTM is consistent

6. **VER runs validation** (Track B):
   ```bash
   trace validate --sil 3
   trace gate-check --phase design --sil 3
   ```
   - Should return: ✅ ALL CHECKS PASSED
   - VER produces Item 14 (Architecture and Design Verification Report)

7. **VMGR coordinates VAL 2nd check** → VAL reviews VER report + runs independent checks

8. **COD gate-check** → `@cod gate-check design` → PASSES

---

## 4. Recommended Actions

### 4.1 Immediate: Fix Phase 3 Gap

**Option A: Manual CSV Creation** (fastest for one-time fix):
```bash
# User or CM agent manually creates 14 CSV files
# Format: source_id,target_id,rationale,verification_method,status
```

**Option B: Tool-Assisted Extraction** (recommended):
```bash
# CM agent uses traceability tools to extract from existing documents
cd examples/TDC
trace extract --from docs/phase-2-requirements/Software-Requirements-Specification.md \
              --to docs/phase-3-architecture-design/Software-Architecture-Specification.md \
              --output evidence/traceability/doc6_to_doc9.csv

trace extract --from docs/phase-3-architecture-design/Software-Architecture-Specification.md \
              --to docs/phase-3-architecture-design/Software-Design-Specification.md \
              --output evidence/traceability/doc10_to_doc9.csv

# Repeat for all 14 missing files
```

---

### 4.2 Long-Term: Update CM Agent Instructions

**File**: `.opencode/agents/cm.md`

**Add to CM Phase 3 Activities Section**:

```markdown
### Traceability Evidence Creation (Phase 3)

Per §5.3.2.7 and §6.5.4.15, CM is responsible for managing traceability artifacts under configuration control. While document authors (REQ, DES, TST, INT) create the initial trace references within their documents, CM must ensure machine-readable evidence files exist for automated validation.

**Mandatory Activities**:
1. Extract trace relationships from all Phase 3 documents using `trace extract` or `trace sync`
2. Create CSV evidence files in `evidence/traceability/` for all T-rules applicable to Phase 3:
   - T3: SRS → SAS (`doc6_to_doc9.csv`)
   - T4: SAS → SRS backward (`doc9_to_doc6.csv`)
   - T5a: SDS → SAS (`doc10_to_doc9.csv`)
   - T5b: SDS → SRS (`doc10_to_doc6.csv`)
   - T5c: SDS → Interface Specs (`doc10_to_doc11.csv`)
   - T10a: Integration Test Spec → Requirements/Architecture/Design/Interfaces (4 files)
   - T10b: HW/SW Integration Test Spec → all upstream documents (5 files)
3. Produce Markdown RTM (`Requirements-Traceability-Matrix.md`) as summary/reporting artifact
4. Baseline all CSV files and RTM in git

**Validation**:
```bash
trace validate --sil 3
trace gate-check --phase design --sil 3
```

Both commands must return ✅ ALL CHECKS PASSED before CM work is complete.
```

---

### 4.3 Long-Term: Update PM Phase Execution Workflow

**File**: `.opencode/agents/pm.md`

**Add to Phase 3 Execution Checklist**:

```markdown
- [ ] DES produces SAS, SDS, SIS with embedded trace IDs
- [ ] INT produces Integration Test Specs with embedded trace IDs
- [ ] **CM extracts traceability to CSV using `trace extract` or `trace sync`**
- [ ] **CM validates traceability completeness: `trace validate --sil 3`**
- [ ] **CM validates gate-check readiness: `trace gate-check --phase design --sil 3`**
- [ ] QUA reviews all deliverables (including CSV files)
- [ ] PM signals Track A complete → hand off to COD for Track B coordination
```

---

## 5. Platform vs. Standard Alignment

| Aspect | EN 50128:2011 | TDC Platform Implementation | Alignment Status |
|--------|---------------|----------------------------|------------------|
| **Traceability creation** | Document authors embed traces (§5.3.2.7) | Authors embed trace IDs in Markdown; CM extracts to CSV | ✅ ALIGNED |
| **CM responsibility** | Manage artifacts under config control (§6.5.4.15) | CM maintains `evidence/traceability/*.csv` in git | ✅ ALIGNED |
| **VER verification** | Verify completeness per phase (§6.5.4.14–6.5.4.17) | VER runs `trace validate`, `trace gate-check` | ✅ ALIGNED |
| **VAL 2nd check** | Independent validation (§6.3, Annex C) | VMGR coordinates VAL review of VER report | ✅ ALIGNED |
| **COD gate enforcement** | Lifecycle phase gates (§5.3) | COD blocks gate if traceability incomplete | ✅ ALIGNED |
| **Tool automation** | Not specified (informative Annex D only) | `trace extract`, `trace sync`, `trace create` commands | ✅ EXTENSION (compliant) |

**Overall Assessment**: The TDC platform's traceability workflow is **fully compliant** with EN 50128:2011. The Phase 3 gap is a **workflow integration issue** (CM agent didn't use available tools), not a standards compliance issue.

---

## 6. Conclusion

### 6.1 Standards Findings

EN 50128:2011 distributes traceability responsibilities across multiple roles:

1. **Document authors create traces** (§5.3.2.7)
2. **CM manages trace artifacts** (§6.5.4.15)
3. **VER verifies trace completeness** (§6.5.4.14–6.5.4.17)
4. **VAL validates traces (2nd check)** (§6.3)
5. **COD enforces at gates** (§5.3)

### 6.2 TDC Platform Status

✅ **Tools work correctly**: `trace validate` and `trace gate-check` correctly identified 14 missing CSV files  
✅ **Workflow is standards-compliant**: Two-track model with VER/VAL/COD roles matches EN 50128  
❌ **Workflow integration gap**: CM agent didn't use `trace extract`/`sync`/`create` commands  

### 6.3 Next Steps

1. ✅ **Complete standards research** (DONE — this document)
2. ⏳ **Create 14 missing CSV files** (immediate action required)
3. ⏳ **Update CM agent instructions** (add traceability workflow steps)
4. ⏳ **Execute Phase 3 Track B** (VER produces Item 14)
5. ⏳ **Phase 3 gate-check** (COD validates completeness)
6. ⏳ **Proceed to Phase 4** (if gate passes)

---

## 7. References

**EN 50128:2011 Standard**:
- §5.3.2.7 — General traceability requirement (line 1332)
- §6.2.4.11(a) — VER traceability verification (line 1607)
- §6.5.4.14–6.5.4.17 — Traceability QA requirements (lines 2045–2071)
- §6.6 — Configuration management (line 2073)
- Annex C Table C.1 — Deliverable authorship matrix (line 4755)
- Annex D.59 — Traceability process (line 6818)

**TDC Platform Documents**:
- `TRACEABILITY.md` — T1-T15 rules, V-Model diagrams, document ID mapping
- `DELIVERABLES.md` — Annex C deliverable matrix with doc IDs
- `WORKFLOW.md` — Two-track execution model (Track A/B)
- `AGENTS.md` — Role definitions
- `TRACEABILITY_TOOL_GAP_ANALYSIS.md` — Comprehensive gap analysis (Phase 3)
- `examples/TDC/LIFECYCLE_STATE.md` — Current project status

**Tools**:
- `tools/traceability_manager.py` — Validation tool
- `tools/workspace.py` — Workspace manager with `trace` commands

---

**Document Control**:
- **Author**: OpenCode AI (Research Agent)
- **Reviewer**: (awaiting user review)
- **Approver**: (pending)
- **Version**: 1.0
- **Status**: Draft — Standards Analysis Complete
