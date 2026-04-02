# Software Verification Plan (SVP)

**DOCUMENT TYPE**: Software Verification Plan  
**EN 50128 DELIVERABLE**: Annex C Item 4  
**STANDARD REFERENCE**: EN 50128:2011 Section 6.2.4.2  
**PROJECT**: TDC (Train Door Control System)  
**SIL LEVEL**: 3

---

## DOCUMENT CONTROL

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SVP-2026-001 |
| **Version** | 1.0 |
| **Date** | 2026-04-02 |
| **Project** | TDC (Train Door Control System) |
| **SIL Level** | SIL 3 |
| **Author** | Verifier (VER) |
| **Status** | DRAFT — Awaiting QUA Format Check |

---

## VERSION HISTORY

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-04-02 | VER | Initial SVP draft for SIL 3 TDC project | - |
| 1.0 | 2026-04-02 | VER | Baseline version for Phase 1 gate | [Pending VAL] |

---

## APPROVALS

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author (VER)** | [VER Name] | [PENDING] | [PENDING] |
| **2nd Check (VAL)** | [VAL Name] | [PENDING] | [PENDING] |
| **Approver (VMGR)** | [VMGR Name] | [PENDING] | [PENDING] |

**Note**: Per EN 50128:2011 §6.2.4.2, VER authors the SVP under VER responsibility. VER does NOT self-check its own SVP (item 4). Per deviation D8 (DELIVERABLES.md), VAL performs 2nd check; VMGR approves (SIL 3 requirement). VER's review of other Phase 1 planning documents is recorded in the Software Quality Assurance Verification Report (SQAVR, item 2).

---

## INTRODUCTION

### Purpose

This Software Verification Plan (SVP) defines the verification strategy, organization, processes, techniques, criteria, tools, and evidence management for the Train Door Control System (TDC) software development at Safety Integrity Level 3 (SIL 3). This plan establishes the framework for independent technical verification of all software deliverables throughout the EN 50128:2011 V-Model lifecycle (Phases 1–10).

**Normative Basis**: EN 50128:2011 §6.2.4.2 mandates: "A Software Verification Plan shall be written, under the responsibility of the Verifier."

**Verification Definition**: Verification is the process of confirming that each software deliverable correctly implements the specifications, requirements, and design from which it was derived — answering the question: **"Are we building the product right?"**

This SVP governs all software verification activities from Phase 1 (Planning) through Phase 10 (Maintenance) and ensures compliance with:
- EN 50128:2011 Railway Software Standard (SIL 3 requirements, Tables A.5, A.19, A.21)
- EN 50126-1:2017 RAMS Part 1 (Generic RAMS process)
- MISRA C:2012 Guidelines for the use of C language in critical systems
- ISO 9001:2015 Quality management systems

### Scope

This SVP applies to **all software deliverables** in the TDC Software lifecycle at SIL 3. The plan covers:

1. **Verification Strategy** — Per-phase verification approach (Phases 1–10) per §6.2.4.3
2. **Independence Organization** — VER role, MANDATORY independence from Designer/Implementer at SIL 3 per §5.1.2.10e
3. **Verification Techniques** — SIL 3 MANDATORY techniques per Tables A.5, A.19, A.21
4. **Static Analysis** — MISRA C:2012 compliance, data flow analysis, control flow analysis (MANDATORY SIL 3)
5. **Test Coverage** — Statement, branch, compound condition coverage (MANDATORY SIL 3)
6. **Traceability** — Requirements → Design → Code → Tests (T1–T15) (MANDATORY SIL 3)
7. **Verification Reports** — 13 Verification Reports per lifecycle phase (items 2, 8, 14, 17, 19, 23, †, 40, 44)
8. **Evidence Management** — Collection, storage, and CM control of verification evidence
9. **Tool Qualification** — Verification tool identification and qualification status (T1/T2/T3)
10. **Metrics and Reporting** — Defect severity definitions, escalation rules, reporting structure

**Out of Scope**: 
- Software validation (covered by Software Validation Plan, item 5)
- System-level verification (covered by System Verification Plan)
- Hardware verification (covered by Hardware Verification Plan)
- Independent safety assessment (covered by Software Assessment Plan, item 45)

### Applicable Standards

This SVP is compliant with:

| Standard | Title | Application |
|----------|-------|-------------|
| **EN 50128:2011** | Railway Software Standard | Software verification requirements (SIL 3) |
| **EN 50126-1:2017** | RAMS - Part 1 | Overall RAMS framework |
| **EN 50126-2:2017** | RAMS - Part 2 | Safety process and risk assessment |
| **MISRA C:2012** | C Coding Standard | MANDATORY coding standard for SIL 3 |
| **ISO 9001:2015** | Quality Management Systems | Quality system compliance |

### References

This SVP references the following project documents:

| Document ID | Document Name | Annex C Item | Location |
|-------------|---------------|--------------|----------|
| DOC-SQAP-2026-001 | Software Quality Assurance Plan | 1 | `docs/phase-1-planning/Software-Quality-Assurance-Plan.md` |
| DOC-SCMP-2026-001 | Software Configuration Management Plan | 3 | `docs/phase-1-planning/Software-Configuration-Management-Plan.md` |
| DOC-SVaP-2026-001 | Software Validation Plan | 5 | `docs/phase-1-planning/Software-Validation-Plan.md` |
| DOC-SYS-PLAN-2026-001 | System Safety Plan | N/A (System-level) | `docs/system/System-Safety-Plan.md` |
| DOC-SYS-SAF-2026-001 | System Safety Requirements Specification | N/A (System-level) | `docs/system/System-Safety-Requirements-Specification.md` |

**Platform References**:
- `DELIVERABLES.md` — Annex C Table C.1 deliverable registry
- `WORKFLOW.md` — Authority structure, two-track loop, Phase 7 special flow
- `tasks/VnV-PROCESS.md` — V&V process reference (ISA PASS)
- `activities/vnv-process.yaml` — Machine-readable V&V workflow
- `TRACEABILITY.md` — T1–T15 traceability rules
- `LIFECYCLE.md` — EN 50128 V-Model lifecycle phases
- `std/EN50128-2011.md` — Full EN 50128 standard (LLM-friendly Markdown)

### Relationship to Other Plans

| Plan | Relationship to SVP |
|------|-------------------|
| **SQAP** (item 1) | Defines quality framework; SVP implements verification quality processes |
| **SCMP** (item 3) | Defines configuration management for verification artifacts and evidence |
| **SVaP** (item 5) | Defines validation (different from verification); VER reviews VAL reports per §6.3.4.12–14 |
| **Overall SW Test Spec** (item 7) | Test plan; SVP defines test verification criteria and coverage requirements |

### Platform Deviations Relevant to SVP

This SVP adopts the following platform deviations from EN 50128:2011:

| Deviation ID | Description | Justification | Impact on SVP |
|--------------|-------------|---------------|---------------|
| **D7** | Software Validation Verification Report (item †) produced in Phase 7 Step B2; normatively required by §6.3.4.12–14 but not assigned an Annex C item number | ISA finding F-01; mandatory output per §6.3.4.12 | VER SHALL produce item † at Phase 7; explicitly named in this SVP per §6.2.4.2 requirement |
| **D8** | VER authors SVP; VER cannot self-check own plan (self-certification conflict); VAL performs 2nd check instead | §6.2.4.2 assigns responsibility to VER; independence integrity | VER does NOT produce SQAVR (item 2) for item 4 (SVP) self-check; item 2 covers SQAP, SCMP, SVaP only |

**Safety Authority Approval**: All deviations are subject to Safety Authority review and approval per project Safety Plan.

---

## 1. VERIFICATION ORGANIZATION

### 1.1 Verifier (VER) Role and Responsibilities

**Role**: Verifier (VER)

**EN 50128 Reference**: Section 5.3.5, Annex B Table B.5

**Primary Responsibilities**:
1. **Author this SVP** (item 4) per §6.2.4.2 — defines verification strategy for all lifecycle phases
2. **Perform independent technical verification** of all Track A deliverables per phase
3. **Produce Verification Reports** for each phase (13 total: items 2, 8, 14, 17, 19, 23, †, 40, 44)
4. **Execute SIL 3 verification techniques** per Tables A.5, A.19, A.21 (static analysis, dynamic analysis, traceability, coverage)
5. **Check traceability** (T1–T15 technical completeness per §6.5.4.14–17)
6. **Record verification findings** — defects, observations, compliance status in Verification Reports
7. **Submit Verification Reports to VMGR** (SIL 3 requirement) for technical review and approval
8. **Store verification evidence** at CM canonical evidence paths per SCMP
9. **Perform Phase 7 Step B2 review** — produce Software Validation Verification Report (item †) reviewing VAL's SVaP and Validation Report per §6.3.4.12–14
10. **Perform Phase 8 1st Check** — review ASR-authored items 45–46 only (no VER report produced for Phase 8)

**Authority**: VER has technical authority to APPROVE or REJECT deliverables based on verification criteria. VER reports findings to VMGR; VMGR makes final V&V decision (SIL 3).

**VER Does NOT**:
- Validate software against user requirements (VAL's responsibility per §6.3)
- Perform quality assurance format checks (QUA's responsibility per §6.5)
- Manage project schedule or resources (PM's responsibility)
- Override VMGR V&V decisions (VMGR has final authority at SIL 3)

### 1.2 Independence Requirements (MANDATORY SIL 3)

**EN 50128 Requirement**: §5.1.2.10e states: "The Verifier shall neither perform any tasks nor report to any person or body who performs any tasks of requirements management, software design, software implementation or software integration."

**TDC SIL 3 Independence Strategy**:

| Aspect | Independence Requirement | TDC Implementation |
|--------|------------------------|-------------------|
| **Organizational Independence** | VER SHALL NOT report to Designer, Implementer, Integrator, or Tester | VER reports to VMGR (not PM); VMGR is independent from COD and PM per §5.1.2.10f |
| **Personnel Independence** | VER SHALL NOT be the same individual as Designer, Implementer, Integrator, or Tester for the same component | VER team separate from development team; documented in org chart `docs/organization/org-chart.pdf` |
| **Technical Independence** | VER SHALL use separate tools and environment from development team | VER uses independent static analysis tools (Cppcheck, Clang Static Analyzer); independent test execution environment |
| **Role Combination Prohibition** | VER+VAL same person NOT permitted without explicit ASR approval per §5.1.2.10n | VER and VAL are separate individuals; documented in SQAP Section 1.5 |

**Independence Evidence**:
- Organization chart demonstrating VER independence reviewed quarterly and stored in `docs/organization/org-chart.pdf`
- Personnel assignments recorded in SQAP Appendix A
- Independence verified by VMGR before each phase gate
- ASR reviews independence structure during Phase 8 Assessment

**Independence Violations**: Any violation of VER independence SHALL be raised as a CRITICAL NCR by QUA and reported to VMGR and Safety Authority immediately.

### 1.3 VER Reporting Structure (SIL 3)

**Reporting Chain**:

```
Safety Authority
  │
  ├── ASR (Assessor) — independent from ALL project roles
  │
  └── VMGR (V&V Manager) — independent from COD and PM
        │
        ├── VER (Verifier) — reports to VMGR
        │     • Produces Verification Reports
        │     • Submits to VMGR for technical review
        │     • VMGR approves or rejects VER output
        │
        └── VAL (Validator) — reports to VMGR
              • Produces Validation Reports (Phase 7 only)
              • VMGR reviews VAL reports
              • VMGR provides FINAL V&V DECISION (cannot be overridden)
```

**Key Rules** (SIL 3):
- VER reports to VMGR (MANDATORY per §5.1.2.10e platform implementation)
- VER does NOT report to PM or COD
- VMGR reviews all VER Verification Reports before submission to COD
- VMGR cannot be bypassed at SIL 3
- VMGR final V&V decision cannot be overridden by COD or PM

### 1.4 VER Team Composition

**Minimum VER Team Size** (SIL 3): 2 full-time equivalent (FTE) personnel

| Role | Responsibilities | Qualification Requirements |
|------|-----------------|---------------------------|
| **Lead Verifier** | Oversee all verification activities; author Verification Reports; coordinate with VMGR | EN 50128:2011 §6.2 training; MISRA C:2012 certification; 5+ years railway software experience |
| **Static Analysis Verifier** | Execute MISRA C checks; data flow/control flow analysis; cyclomatic complexity analysis | MISRA C:2012 certification; Cppcheck/PC-lint tool training; static analysis expertise |

**Training Requirements** (MANDATORY SIL 3):
- EN 50128:2011 §6.2 Software Verification (initial + annual refresher)
- MISRA C:2012 Guidelines (initial + bi-annual refresher)
- Static analysis tools (Cppcheck, Clang Static Analyzer, PC-lint Plus) — tool qualification evidence
- Traceability checking (T1–T15 rules per `TRACEABILITY.md`)
- EN 50128 Table A.5, A.19, A.21 verification techniques

**Training Records**: Stored in `docs/training/VER-Training-Records.md` under CM control; reviewed quarterly by QUA.

---

## 2. VERIFICATION STRATEGY

### 2.1 Overall Verification Approach

The TDC Software verification strategy follows the EN 50128:2011 V-Model lifecycle with **independent technical verification at every phase**. VER operates in two modes:

**Mode 1: Author Mode** (primary) — VER authors a Verification Report for each phase by:
1. Reviewing all Track A deliverables produced in that phase
2. Applying SIL 3 verification techniques per Tables A.5, A.19, A.21
3. Checking traceability (T1–T15) per §6.5.4.14–17
4. Recording findings (PASS/FAIL/OBSERVATION) per criterion
5. Submitting Verification Report to QUA for format check (1-Pass Rule)
6. On QUA PASS: VMGR reviews technical content and approves or rejects

**Mode 2: 1st-Check Mode** (secondary) — VER performs 1st Check on ASR-authored items 45–46 in Phase 8 only (no VER report produced for Phase 8).

**Verification Scope**: VER reviews **37 of 46 Annex C deliverables**:
- Phase 1: items 1, 3, 4, 5 (VER reviews; produces item 2 SQAVR)
- Phase 2: items 6, 7 (VER reviews; produces item 8)
- Phase 3: items 9–13 (VER reviews; produces item 14)
- Phase 4: items 15–16 (VER reviews; produces item 17)
- Phase 5: items 18, 20 (VER reviews; produces item 19)
- Phase 6: items 21–22 (VER reviews; produces item 23 in Phase 7)
- Phase 7: item 24 + VAL items 25–26 (VER reviews; produces item 23 + item †)
- Phase 8: items 45–46 (VER 1st Check only; no VER report)
- Phase 9: items 36–39 (VER reviews; produces item 40)
- Phase 10: items 41–43 (VER reviews; produces item 44)

### 2.2 Per-Phase Verification Outputs

VER produces **13 Verification Reports** across the lifecycle:

| Phase | VER Report Item | Annex C Label | Input Deliverables | Normative Reference |
|-------|----------------|---------------|-------------------|-------------------|
| 1 | **2** | Software Quality Assurance Verification Report | Items 1, 3, 5 (not 4 — VER self-check exempt) | §6.2.4.10–11, §6.5.4.7–8 |
| 2 | **8** | Software Requirements Verification Report | Items 6, 7 | §7.2.4 |
| 3 | **14** | Software Architecture and Design Verification Report | Items 9–13 | §7.3 |
| 4 | **17** | Software Component Design Verification Report | Items 15–16 | §7.4.4.11 |
| 5 | **19** | Software Source Code Verification Report | Items 18, 20 | §7.4–7.5 |
| 6 | — | *(no VER report — item 23 belongs to Phase 7)* | Items 21–22 reviewed | — |
| 7 (B1) | **23** | Software Integration Verification Report | Items 21–22, 24 | §7.6 |
| 7 (B2) | **†** | Software Validation Verification Report | Items 5, 25–26 (VAL reports) | §6.3.4.12–14 |
| 8 | — | *(1st Check on items 45–46 only; no VER report)* | Items 45–46 reviewed | — |
| 9 | **40** | Deployment Verification Report | Items 36–39 | §9.1.4.16–19 |
| 10 | **44** | Software Maintenance Verification Report | Items 41–43 | §9.2.4.6(b) |

**Item † (Software Validation Verification Report)**:
- Platform-designated item per ISA finding F-01
- Normatively required by §6.3.4.12: "The verification process shall review the validation plan and the validation report"
- §6.3.4.13: "The validator shall review the validation plan for: readability, traceability, specific requirements, consistency with integration strategy"
- §6.3.4.14: "The validator shall review the validation report for: same criteria as plan + §6.3.4.8–11, §7.7.4.7–11"
- **Explicitly named in this SVP per §6.2.4.2 requirement**
- Produced at SIL 3–4 in Phase 7 Step B2 after VAL reports are QUA-checked
- Numbering subject to Safety Authority confirmation per §6.4.4.1

**Note**: VER does NOT self-check its own SVP (item 4). Item 2 (SQAVR) records VER's review of the SQAP (item 1), SCMP (item 3), and SVaP (item 5) only.

### 2.3 Phase 7 Special Flow (Two-Step Process)

Phase 7 (Validation) runs **two sequential sub-chains** per `activities/vnv-process.yaml`:

**Step B1 — Software Integration Verification Report (item 23)**:
- **Input**: TST-authored Overall SW Test Report (item 24) + integration test results (items 21–22)
- **VER applies**: Integration verification criteria per Table A.6
- **VER produces**: Software Integration Verification Report (item 23)
- **Flow**: Item 23 → QUA format check (1-Pass Rule) → VMGR technical review

**Step B2 — Software Validation Verification Report (item †)**:
- **Input**: VAL-authored Validation Reports (items 25–26) after QUA format check
- **VER applies**: §6.3.4.13–14 criteria:
  - Readability (§5.3.2.7–10)
  - Traceability (§6.5.4.14–17)
  - Specific requirements (§6.3.4.4–6)
  - Internal consistency
  - §6.3.4.8–11 validation evidence requirements
  - §7.7.4.7–11 validation report content requirements
- **VER produces**: Software Validation Verification Report (item †)
- **Flow**: Item † → QUA format check (1-Pass Rule) → VMGR final review
- **VMGR uses**: Items 23 + † together for final V&V decision

**SIL 0–2 Behavior**: At SIL 0–2, item † may be captured as a supplementary note in item 23 or a separate document — project defines in SQAP. No VMGR flow at SIL 0–2.

---

## 3. VERIFICATION TECHNIQUES (SIL 3 MANDATORY)

### 3.1 EN 50128 Table A.5 Technique Selection

The following verification techniques are applied per EN 50128:2011 Table A.5 for SIL 3:

| # | Technique | Table Ref | SIL 3 | TDC Selection | Applied In Phase | Justification |
|---|-----------|-----------|-------|---------------|-----------------|---------------|
| **D.24** | Static Analysis | A.5 | **M** | **ADOPTED** | 3, 4, 5, 6 | Data flow, control flow, MISRA C compliance (MANDATORY SIL 3) |
| **D.58** | Traceability | A.5 | **M** | **ADOPTED** | 2–7, 10 | T1–T15 requirements → code → tests (MANDATORY SIL 3) |
| **D.32** | Inspection | A.5 | **M** | **ADOPTED** | 2–5 | Requirements review, design review, code review (MANDATORY SIL 3) |
| **D.29** | Simulation | A.5 | R | ADOPTED | 6, 7 | Integration testing simulation (recommended) |
| **D.37** | Metrics | A.5 | HR | ADOPTED | 5, 6 | Cyclomatic complexity, defect density (highly recommended) |
| **D.1** | Formal Proof | A.5 | HR | NOT ADOPTED | — | Not cost-effective for TDC; static analysis + testing sufficient |

**Key**: **M** = Mandatory; **HR** = Highly Recommended; **R** = Recommended

**Techniques NOT ADOPTED**: Formal Proof (D.1) — justification: TDC door control logic is safety-critical but not mathematically complex; comprehensive static analysis (data flow + control flow) + MISRA C compliance + 100% statement/branch coverage provides sufficient rigor at SIL 3 without formal methods overhead.

### 3.2 Static Analysis Techniques (Table A.19 — MANDATORY SIL 3)

| # | Technique | Table Ref | SIL 3 | TDC Selection | Tool | Applied To |
|---|-----------|-----------|-------|---------------|------|-----------|
| **1** | Boundary Value Analysis | A.19 | **M** | **ADOPTED** | Cppcheck, manual review | Source code (Phase 5) |
| **2** | Control Flow Analysis | A.19 | HR | **ADOPTED** | Cppcheck `--enable=style`, Clang Static Analyzer | Source code (Phase 5) |
| **3** | Data Flow Analysis | A.19 | HR | **ADOPTED** | Cppcheck `--enable=all`, Clang Static Analyzer | Source code (Phase 5) |
| **4** | Error Guessing | A.19 | R | ADOPTED | Manual review | Requirements, design, code |
| **5** | Equivalence Classes / Input Partition | A.19 | **M** | **ADOPTED** | Manual analysis + test case generation | Unit tests (Phase 5) |

**SIL 3 Mandatory Compliance**:
- **MISRA C:2012 compliance**: ZERO violations of mandatory + required rules (Advisory rules may be justified per MISRA deviation procedure §4.7–4.9)
- **Cyclomatic complexity**: ≤ 10 per function (MANDATORY SIL 3)
- **Data flow analysis**: Uninitialized variables, unreachable code, unused variables (MANDATORY)
- **Control flow analysis**: Infinite loops, dead code, missing break statements (MANDATORY)

### 3.3 Test Coverage Techniques (Table A.21 — MANDATORY SIL 3)

| # | Coverage Type | Table Ref | SIL 3 | TDC Target | Tool | Measured In Phase |
|---|--------------|-----------|-------|-----------|------|------------------|
| **1** | Statement Coverage | A.21 | HR | **100%** | gcov/lcov | 5 (unit tests) |
| **2** | Branch Coverage | A.21 | HR | **100%** | gcov/lcov | 5 (unit tests) |
| **3** | Compound Condition Coverage | A.21 | HR | **100%** | gcov/lcov (manual verification) | 5 (safety-critical modules) |
| **4** | MC/DC Coverage | A.21 | R | **N/A** | — | Not adopted for SIL 3 (HR threshold met by compound condition) |

**EN 50128 Note**: EN 50128 does not specify a mandatory percentage threshold for coverage; the requirement is to apply the technique at the stated level. **Full coverage (100%)** is a TDC project-defined acceptance criterion documented in this SVP.

**SIL 3 Coverage Acceptance Criteria**:
- **Statement coverage**: ≥ 100% for all safety-critical modules (door control logic, emergency release, safety interlocks)
- **Branch coverage**: ≥ 100% for all safety-critical modules
- **Compound condition coverage**: ≥ 100% for Boolean expressions with multiple conditions in safety-critical modules
- **Integration coverage**: ≥ 95% statement coverage for integrated system (Phase 6)
- **Validation coverage**: ≥ 90% statement coverage for system-level tests (Phase 7)

**Coverage Deviation Procedure**: Any module with coverage < 100% SHALL:
1. Be identified in Software Source Code Verification Report (item 19)
2. Have justified rationale for uncovered code (unreachable error handlers, defensive programming)
3. Require VER approval before gate advancement
4. Be documented in Software Change Record if baseline modified

### 3.4 Dynamic Analysis and Testing (Table A.13)

| # | Technique | SIL 3 | TDC Selection | Applied In Phase |
|---|-----------|-------|---------------|-----------------|
| **1** | Functional and Black-Box Testing | **M** | **ADOPTED** | 5, 6, 7 |
| **2** | Performance Testing | HR | ADOPTED | 6, 7 |
| **3** | Interface Testing | HR | ADOPTED | 6 |
| **4** | Equivalence Classes and Input Partition Testing | **M** | **ADOPTED** | 5 |
| **5** | Boundary Value Analysis | **M** | **ADOPTED** | 5 |

**VER Responsibility**: VER verifies that TST has executed all MANDATORY techniques and that test evidence meets SIL 3 acceptance criteria.

---

## 4. TRACEABILITY MANAGEMENT (MANDATORY SIL 3)

### 4.1 Traceability Approach

**EN 50128 Requirement**: Table A.9 Technique 6 (Traceability) is **MANDATORY** for SIL 3.

**TDC Traceability Chain** (per `TRACEABILITY.md`):

```
System Requirements (S1, S4)
  ↓ T1
Software Requirements (SRS, item 6)
  ↓ T2                              ↓ T3
Overall Test Spec (item 7)         Software Architecture (SAS, item 9)
                                    ↓ T4
                                   Software Design (SDS, item 10)
                                    ↓ T5a, T5b, T5c
                                   Integration Test Specs (items 12–13) + Interface Specs (item 11)
                                    ↓ T6
                                   Software Component Design (item 15)
                                    ↓ T7                      ↓ T8
                                   Source Code (item 18)      Component Test Spec (item 16)
                                    ↓ T12                     ↓ T11
                                   Component Test Report (item 20)
                                    ↓ T10a, T10b              ↓ T14
                                   Integration Test Report (items 21–22)
                                    ↓ T15
                                   Overall Test Report (item 24)
                                    ↓ T13
                                   Validation Report (item 25)
```

**Complete Traceability Rules** (T1–T15):

| Rule | From → To | Direction | Checked In Phase | VER Report |
|------|----------|-----------|-----------------|-----------|
| **T1** | System Requirements → Software Requirements | Bidirectional | 2 | Item 8 |
| **T2** | Software Requirements → Overall Software Test Specification | Bidirectional | 2 | Item 8 |
| **T3** | Software Requirements → Software Architecture | Bidirectional | 3 | Item 14 |
| **T4** | Software Architecture → Software Design | Bidirectional | 3 | Item 14 |
| **T5a** | Software Design → Integration Test Specification | Bidirectional | 3 | Item 14 |
| **T5b** | Software Architecture → SW/HW Integration Test Specification | Bidirectional | 3 | Item 14 |
| **T5c** | Software Architecture → Software Interface Specifications | Bidirectional | 3 | Item 14 |
| **T6** | Software Design → Software Component Design | Bidirectional | 4 | Item 17 |
| **T7** | Software Component Design → Source Code | Bidirectional | 5 | Item 19 |
| **T8** | Software Component Design → Component Test Specification | Forward only | 4 | Item 17 |
| **T10a** | Integration Test Specification → Integration Test Report | Bidirectional | 6 | Item 23 (Phase 7) |
| **T10b** | SW/HW Integration Test Specification → SW/HW Integration Test Report | Bidirectional | 6 | Item 23 (Phase 7) |
| **T11** | Component Test Specification → Component Test Report | Bidirectional | 5 | Item 19 |
| **T12** | Source Code → Component Test Report | Bidirectional | 5 | Item 19 |
| **T13** | Software Requirements → Software Validation Report (via Overall Test Spec) | Bidirectional | 7 | Item † |
| **T14** | Component Test Reports → Overall Software Test Report | Bidirectional | 7 | Item 23 |
| **T15** | Integration Test Reports → Overall Software Test Report | Bidirectional | 7 | Item 23 |

**T15 Note**: T15 is a process obligation. VER records findings in Verification Report. The `trace gate-check` tool confirms matrix CSV coverage only; it does NOT verify the narrative content of VER reports.

### 4.2 Traceability Tools

**Primary Tool**: `workspace.py trace` command

**Usage Examples**:
```bash
# Check T1 traceability (System Req → SW Req)
python3 tools/workspace.py trace gate-check --phase requirements --sil 3

# Verify specific link
python3 tools/workspace.py trace verify-link \
  --matrix doc6_to_doc9 \
  --source REQ-FUNC-001 \
  --target ARCH-MOD-001 \
  --by "VER" \
  --date 2026-04-02

# Generate traceability coverage report
python3 tools/workspace.py trace --coverage
```

**Matrix Naming Convention**: Matrix CSV files follow the document-ID convention:
```
evidence/traceability/doc<from>_to_doc<to>.csv
```

**Examples**:
- T1: `docS1_to_doc6.csv` (System Req → SW Req)
- T3: `doc6_to_doc9.csv` (SW Req → SW Architecture)
- T7: `doc18_to_doc15.csv` (Component Design → Source Code)

### 4.3 VER Traceability Verification Criteria

**Per-Phase Gate Check** (MANDATORY before VER report submission):

```bash
# VER SHALL run trace gate-check at each phase gate before recording findings
python3 tools/workspace.py trace gate-check \
  --phase <requirements|design|component-design|implementation-testing|integration|validation> \
  --sil 3

# Exit code 0 = PASS (all rules met); exit code 1 = FAIL (gate BLOCKED)
```

**VER Records in Verification Report**:
1. Traceability rule coverage (T1–T15 applicable to this phase)
2. Per-rule PASS/FAIL with normative clause citations
3. Orphaned requirements (requirements with no downstream links)
4. Orphaned tests (tests with no upstream requirements)
5. Bidirectional consistency (forward and backward links match)
6. Traceability matrix completeness (all required links present)

**Acceptance Criteria**:
- **100% traceability coverage** for all T1–T15 rules applicable to this phase
- **Zero orphaned requirements** in safety-critical modules
- **Zero orphaned tests** in safety-critical modules
- **Bidirectional consistency**: forward link A→B SHALL have corresponding backward link B→A

**Traceability Defect Severity**:
- **CRITICAL**: Orphaned safety-critical requirement; missing T1, T3, T7, or T13 link
- **MAJOR**: Orphaned non-safety-critical requirement; missing T2, T4, T5, T6, T8, T10–12, T14–15 link
- **MINOR**: Documentation inconsistency; formatting issue in traceability matrix

---

## 5. VERIFICATION CRITERIA AND ACCEPTANCE THRESHOLDS

### 5.1 Per-Phase Verification Criteria

#### Phase 1: Planning

**Deliverables Verified**: Items 1 (SQAP), 3 (SCMP), 5 (SVaP)  
**VER Report**: Item 2 (Software Quality Assurance Verification Report)

**Verification Criteria**:
- [ ] SQAP defines SIL 3 quality processes (§6.5.4.3)
- [ ] SCMP defines CM baselines and change control (§6.6.4.1–2)
- [ ] SVaP defines validation strategy and acceptance criteria (§6.3.4.2)
- [ ] All plans reference EN 50128 SIL 3 mandatory techniques
- [ ] Independence requirements documented (SQAP Section 1.5)
- [ ] Tool qualification strategy defined (SQAP Section 7.2)

**Acceptance Threshold**: All criteria PASS

#### Phase 2: Requirements Specification

**Deliverables Verified**: Items 6 (SRS), 7 (Overall SW Test Specification)  
**VER Report**: Item 8 (Software Requirements Verification Report)

**Verification Criteria**:
- [ ] SRS requirements are complete, correct, consistent, unambiguous, verifiable, traceable (§7.2.4.14)
- [ ] All SIL 3 requirements identified and marked
- [ ] Traceability T1 (System Req → SW Req) 100% complete
- [ ] Traceability T2 (SW Req → Overall Test Spec) 100% complete
- [ ] Overall Test Spec covers all SRS requirements
- [ ] Test acceptance criteria defined for all SIL 3 requirements
- [ ] Safety requirements identified and cross-referenced to Hazard Log

**Acceptance Threshold**: All criteria PASS; zero CRITICAL defects

#### Phase 3: Architecture and Design

**Deliverables Verified**: Items 9–13 (SAS, SDS, Interfaces, Integration Test Specs)  
**VER Report**: Item 14 (Software Architecture and Design Verification Report)

**Verification Criteria**:
- [ ] SAS defines modular architecture with clear interfaces (§7.3.4.21)
- [ ] SDS component design traceable to SAS modules
- [ ] Interface specifications complete and consistent
- [ ] Traceability T3, T4, T5a, T5b, T5c 100% complete
- [ ] FMEA/FTA evidence exists (SAF-produced)
- [ ] Architecture meets SIL 3 constraints (no dynamic memory allocation, no recursion)
- [ ] Cyclomatic complexity estimates ≤ 10 per function

**Acceptance Threshold**: All criteria PASS; zero CRITICAL defects

#### Phase 4: Component Design

**Deliverables Verified**: Items 15 (Component Design), 16 (Component Test Spec)  
**VER Report**: Item 17 (Software Component Design Verification Report)

**Verification Criteria**:
- [ ] Component design specifications complete per SDS
- [ ] Traceability T6 (SDS → Component Design) 100% complete
- [ ] Traceability T8 (Component Design → Component Test Spec) 100% forward complete
- [ ] Component test specification covers all component functions
- [ ] Detailed design review records exist (VER/DES-produced)

**Acceptance Threshold**: All criteria PASS; zero CRITICAL defects

#### Phase 5: Implementation and Testing

**Deliverables Verified**: Items 18 (Source Code), 20 (Component Test Report)  
**VER Report**: Item 19 (Software Source Code Verification Report)

**Verification Criteria**:
- [ ] **MISRA C:2012 compliance**: ZERO violations of mandatory + required rules (SIL 3 MANDATORY)
- [ ] **Cyclomatic complexity**: ≤ 10 per function (SIL 3 MANDATORY)
- [ ] **Statement coverage**: ≥ 100% for safety-critical modules
- [ ] **Branch coverage**: ≥ 100% for safety-critical modules
- [ ] **Compound condition coverage**: ≥ 100% for Boolean expressions in safety-critical modules
- [ ] **Static analysis**: ZERO critical defects from Cppcheck, Clang Static Analyzer
- [ ] **Traceability T7** (Component Design → Code): 100% complete
- [ ] **Traceability T11, T12** (Component Test Spec / Code → Component Test Report): 100% complete
- [ ] No dynamic memory allocation (`malloc`, `calloc`, `realloc`, `free` prohibited)
- [ ] No recursion (direct or indirect)
- [ ] No function pointers in safety-critical modules
- [ ] All safety-critical functions have unit tests with 100% coverage

**Acceptance Threshold**: **All criteria PASS; ZERO CRITICAL defects; ZERO MISRA mandatory/required violations**

**Static Analysis Evidence**:
- Cppcheck report: `evidence/static-analysis/cppcheck-report.txt`
- Clang Static Analyzer report: `evidence/static-analysis/clang-sa-report.html`
- MISRA C compliance matrix: `evidence/static-analysis/misra-compliance-matrix.csv`
- Cyclomatic complexity report: `evidence/static-analysis/complexity-report.txt` (lizard tool)

**Coverage Evidence**:
- gcov data files: `evidence/coverage/*.gcda`
- lcov HTML report: `evidence/coverage/lcov-report/index.html`
- Coverage summary: `evidence/coverage/coverage-summary.txt`

#### Phase 6: Integration

**Deliverables Verified**: Items 21 (Integration Test Report), 22 (SW/HW Integration Test Report)  
**VER Report**: Item 23 (produced in Phase 7, not Phase 6)

**Verification Criteria**:
- [ ] Integration test specifications (items 12–13) executed completely
- [ ] Traceability T10a, T10b (Integration Test Spec → Integration Test Report) 100% complete
- [ ] Integration coverage ≥ 95% statement coverage
- [ ] All integration test cases PASS
- [ ] SW/HW interface testing complete

**Acceptance Threshold**: All criteria PASS; zero CRITICAL defects

**Note**: VER reviews items 21–22 during Phase 6 but does NOT produce a separate Verification Report at the close of Phase 6. Item 23 (SW Integration Verification Report) is produced in Phase 7 per Annex C Table C.1.

#### Phase 7: Validation (Two-Step Process)

**Step B1 — Software Integration Verification Report (item 23)**

**Deliverables Verified**: Items 21–22 (integration test reports), 24 (Overall SW Test Report)  
**VER Report**: Item 23 (Software Integration Verification Report)

**Verification Criteria**:
- [ ] Overall Software Test Report (item 24) covers all integration tests
- [ ] Traceability T14, T15 (Component Test Reports / Integration Test Reports → Overall Test Report) 100% complete
- [ ] All integration test cases PASS
- [ ] System-level coverage ≥ 90% statement coverage
- [ ] Integration defects resolved or waived with justification

**Step B2 — Software Validation Verification Report (item †)**

**Deliverables Verified**: Items 5 (SVaP), 25 (Software Validation Report), 26 (Tools Validation Report)  
**VER Report**: Item † (Software Validation Verification Report)

**Verification Criteria** (per §6.3.4.12–14):
- [ ] **SVaP readability** (§5.3.2.7–10): clear, unambiguous, complete
- [ ] **SVaP traceability** (§6.5.4.14–17): validation criteria traceable to system requirements
- [ ] **SVaP specific requirements** (§6.3.4.4–6): acceptance criteria defined per SIL 3
- [ ] **SVaP internal consistency**: no contradictions
- [ ] **Validation Report readability**: Same criteria as SVaP
- [ ] **Validation Report traceability** (T13): SW Req → Validation Report 100% complete
- [ ] **Validation evidence** (§6.3.4.8–11): test logs, acceptance test results, defect logs
- [ ] **Validation Report content** (§7.7.4.7–11): configuration, test results, deviations, conclusion
- [ ] Tools Validation Report (item 26) covers all T2 tools (if applicable)

**Acceptance Threshold**: All criteria PASS; VMGR final V&V decision APPROVE

#### Phase 8: Assessment

**Deliverables Verified**: Items 45 (Software Assessment Plan), 46 (Software Assessment Report)  
**VER Report**: None (VER performs 1st Check only; no separate VER report for Phase 8)

**VER 1st Check Criteria**:
- [ ] Assessment Plan scope covers all SIL 3 requirements
- [ ] Assessment Report references all Annex C deliverables
- [ ] ASR independence demonstrated
- [ ] ASR findings recorded
- [ ] ASR recommendations addressed

**Note**: ASR is fully independent from VMGR; VMGR has no authority over ASR. VER performs 1st Check on ASR deliverables but does not produce a Verification Report.

#### Phase 9: Deployment

**Deliverables Verified**: Items 36–39 (Deployment Plan, Manual, Notes, Records)  
**VER Report**: Item 40 (Deployment Verification Report)

**Verification Criteria**:
- [ ] Deployment Plan defines installation procedure per §9.1.4
- [ ] Deployment Manual complete and consistent with Release Package
- [ ] Release Notes identify all known issues
- [ ] Deployment Records demonstrate reproducibility (§9.1.4.3)
- [ ] Baseline manifest (manifest.yaml) matches deployed software

**Acceptance Threshold**: All criteria PASS; deployment reproducibility verified

#### Phase 10: Maintenance

**Deliverables Verified**: Items 41–43 (Maintenance Plan, Change Records, Maintenance Records)  
**VER Report**: Item 44 (Software Maintenance Verification Report)

**Verification Criteria**:
- [ ] Maintenance Plan defines change control per §9.2
- [ ] Software Change Records complete per §6.6.4.1 (nine aspects)
- [ ] Traceability impact analysis complete (all T1–T15 re-checked per CR scope)
- [ ] Re-verification scope identified per §6.6.4.2
- [ ] CCB approval recorded
- [ ] Regression testing complete

**Acceptance Threshold**: All criteria PASS; zero CRITICAL defects introduced by change

### 5.2 Defect Severity Definitions

| Severity | Definition | Example | VER Decision | Escalation |
|----------|------------|---------|--------------|------------|
| **CRITICAL** | Violation of MANDATORY (M) EN 50128 requirement; safety impact; SIL integrity compromise | Missing MISRA C compliance at SIL 3; orphaned safety-critical requirement | **REJECT** (gate blocked) | VMGR + PM + Safety Authority |
| **MAJOR** | Violation of HIGHLY RECOMMENDED (HR) technique without justification; significant technical defect | Missing coverage report; cyclomatic complexity > 10 | **REJECT** (must fix) | VMGR + PM |
| **MINOR** | Violation of RECOMMENDED (R) technique; technical improvement opportunity | Code style inconsistency; missing code comment | **PASS WITH OBSERVATIONS** | PM only |

**Escalation Rules**:
- **CRITICAL**: VER raises NCR; reports to VMGR and PM immediately; gate BLOCKED until resolved
- **MAJOR**: VER records in Verification Report; reports to VMGR; requires remediation before gate
- **MINOR**: VER records in Verification Report; may proceed with waiver; tracked in LIFECYCLE_STATE.md

---

## 6. VERIFICATION TOOLS

### 6.1 Tool Identification

| Tool | Purpose | Qualification Status | Vendor/Source | Version | Platform |
|------|---------|---------------------|---------------|---------|----------|
| **Cppcheck** | Static analysis (MISRA C, data flow, control flow) | T1 (platform tools per §6.7.4.4.2) | Open source | 2.10+ | Linux |
| **Clang Static Analyzer** | Static analysis (data flow, control flow) | T1 (platform tools per §6.7.4.4.2) | LLVM | 15.0+ | Linux |
| **gcov** | Code coverage measurement (statement, branch) | T2 (requires qualification per §6.7) | GCC | 11.0+ | Linux |
| **lcov** | Coverage report generation | T1 (platform tools per §6.7.4.4.2) | Open source | 1.15+ | Linux |
| **lizard** | Cyclomatic complexity measurement | T1 (platform tools per §6.7.4.4.2) | Open source | 1.17+ | Python |
| **Unity** | Unit test framework | T2 (requires qualification per §6.7) | ThrowTheSwitch.org | 2.5+ | C |
| **workspace.py** | Traceability checking, lifecycle state tracking | T1 (platform tools per §6.7.4.4.2) | Platform-provided | 1.0 | Python |
| **Git** | Version control, CM baselines | T1 (platform tools per §6.7.4.4.2) | Open source | 2.34+ | Linux |

### 6.2 Tool Qualification

**EN 50128 Tool Classification** (§6.7.4.4):
- **T1**: Tool cannot introduce errors; simple inspection sufficient; no separate qualification required
- **T2**: Tool may introduce errors; tool validation required (item 26 — Tools Validation Report, Phase 7)
- **T3**: Tool generates safety-critical outputs; full tool qualification required

**TDC Tool Qualification Strategy**:

| Tool | Class | Qualification Approach | Qualification Evidence | Qualified By |
|------|-------|----------------------|----------------------|--------------|
| **Cppcheck** | T1 | Inspection; manual review of static analysis reports | Cppcheck User Manual; tool usage log | VER |
| **Clang SA** | T1 | Inspection; manual review of static analysis reports | Clang SA documentation; tool usage log | VER |
| **gcov** | T2 | Tool validation per §6.7.4.5; cross-check with manual coverage | Tools Validation Report (item 26) | VAL (Phase 7) |
| **Unity** | T2 | Tool validation per §6.7.4.5; test framework verification | Tools Validation Report (item 26) | VAL (Phase 7) |
| **lcov** | T1 | Inspection; coverage report formatting only | lcov documentation | VER |
| **lizard** | T1 | Inspection; complexity calculation verified by manual count | Lizard documentation | VER |
| **workspace.py** | T1 | Platform validation; traceability tool verification | Platform validation evidence | Platform (COD) |
| **Git** | T1 | Platform validation; version control integrity | Platform validation evidence | Platform (CM) |

**Tool Qualification Outputs**:
- **Tools Validation Report** (item 26, Phase 7): VAL produces; covers gcov, Unity (T2 tools)
- **Tool Usage Logs**: VER maintains; stored in `evidence/tool-qualification/tool-usage-log.md`
- **Tool Qualification Records**: Stored in `evidence/tool-qualification/` under CM control

### 6.3 Tool Configuration

#### Cppcheck Configuration

**Command**:
```bash
cppcheck --enable=all --inconclusive --std=c11 --platform=unix64 \
  --suppress=missingIncludeSystem \
  --inline-suppr \
  --xml --xml-version=2 \
  --output-file=evidence/static-analysis/cppcheck-report.xml \
  src/
```

**Mandatory Checks** (SIL 3):
- `--enable=all`: All checks enabled (warning, style, performance, portability, information)
- `--inconclusive`: Report inconclusive findings (VER reviews and justifies)
- MISRA C:2012 addon: `--addon=misra` (requires MISRA C:2012 text file)

#### Clang Static Analyzer Configuration

**Command**:
```bash
scan-build -o evidence/static-analysis/clang-sa-report \
  --status-bugs \
  make clean all
```

**Mandatory Checks** (SIL 3):
- Data flow analysis: uninitialized variables, null pointer dereference
- Control flow analysis: dead code, unreachable code
- API usage: memory leaks, double free, use-after-free

#### gcov/lcov Configuration

**gcov Command**:
```bash
gcc -fprofile-arcs -ftest-coverage -g -O0 -o test_module test_module.c module.c
./test_module
gcov module.c
```

**lcov HTML Report**:
```bash
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory evidence/coverage/lcov-report
```

**Mandatory Thresholds** (SIL 3):
- Statement coverage ≥ 100% (safety-critical modules)
- Branch coverage ≥ 100% (safety-critical modules)

#### lizard Configuration

**Command**:
```bash
lizard -l c -w -o evidence/static-analysis/complexity-report.txt src/
```

**Mandatory Threshold** (SIL 3):
- Cyclomatic complexity ≤ 10 per function

---

## 7. VERIFICATION REPORTING

### 7.1 Verification Report Format

All Verification Reports SHALL follow EN 50128:2011 §6.2.4.13 format:

**Mandatory Sections**:
1. **Document Control**: Document ID, Version, Date, Project, SIL Level, Author, Status
2. **Version History**: Version, Date, Author, Changes, Approved By
3. **Approvals**: Author (VER), 2nd Check (VAL or —), Approver (VMGR or PM)
4. **Scope**: Phase, deliverables verified, verification techniques applied
5. **Verification Activities**: Per-deliverable verification tasks, criteria applied
6. **Verification Results**: PASS/FAIL/OBSERVATION per criterion
7. **Defect List**: Severity, description, affected CI, recommended action
8. **Traceability Summary**: T1–T15 coverage, orphaned items
9. **Static Analysis Summary** (Phases 3–6): MISRA C compliance, complexity, data flow, control flow
10. **Coverage Summary** (Phases 5–7): Statement, branch, compound condition coverage
11. **EN 50128 Compliance**: Table A.5, A.19, A.21 technique confirmation
12. **Identity/Configuration of Items Verified** (per §6.2.4.13(a)): Document IDs, versions, baseline reference
13. **Conclusion**: Overall PASS / FAIL / PASS WITH OBSERVATIONS; gate recommendation

**Template Location**: `deliverables/<phase>/<VerificationReportName>-template.md`

### 7.2 Verification Report Submission and Review

**Submission Flow** (SIL 3):

```
1. VER authors Verification Report
   ↓
2. VER submits to QUA for format check (1-Pass Rule)
   ├── QUA FAIL → VER re-issues (max 1 resubmission)
   └── QUA PASS → proceed
   ↓
3. QUA-PASSED report submitted to VMGR
   ↓
4. VMGR reviews technical content
   ├── VMGR REJECT → VER reworks; QUA re-checks
   └── VMGR APPROVE → proceed
   ↓
5. VMGR reports V&V outcome to COD
   ↓
6. COD gate-check (uses VMGR approval as input)
```

**1-Pass Rule** (VER/VAL reports only): 
- 1 resubmission allowed after QUA format check FAIL
- 2nd QUA rejection = process failure → escalate to VMGR + PM

### 7.3 Evidence Collection and Storage

**Evidence Requirements** (per §6.2.4.8):
- Verification results SHALL be retained in format defined or referenced in SVP
- Evidence SHALL be stored at CM canonical evidence paths
- Evidence SHALL be placed under version control (Git)
- Evidence SHALL be included in baseline manifest at phase gate

**CM Canonical Evidence Paths** (VER SHALL call CM `evidence-path` before storing):

| Evidence Type | CM Canonical Path | Phase | Produced By |
|---------------|-------------------|-------|-------------|
| **static-analysis** | `phase-5-implementation-testing/evidence/static-analysis/` | 5 | VER, IMP |
| **coverage** | `phase-5-implementation-testing/evidence/coverage/` | 5 | TST, VER |
| **unit-test-log** | `phase-5-implementation-testing/evidence/test-logs/` | 5 | TST |
| **tool-qualification** | `phase-5-implementation-testing/evidence/tool-qualification/` | 5 | VAL |
| **design-analysis** | `phase-3-architecture-design/evidence/design-analysis/` | 3 | SAF |
| **design-review** | `phase-4-component-design/evidence/design-review/` | 4 | VER, DES |
| **integration-test-log** | `phase-6-integration/evidence/integration-test-logs/` | 6 | INT, TST |
| **system-test-log** | `phase-7-validation/evidence/system-test-logs/` | 7 | VAL, TST |
| **validation-record** | `phase-7-validation/evidence/validation-records/` | 7 | VAL |

**Evidence Naming Convention**:
- **Static analysis**: `<tool>-report.<ext>` (e.g., `cppcheck-report.xml`, `clang-sa-report.html`)
- **Coverage**: `lcov-report/index.html`, `coverage-summary.txt`
- **Test logs**: `<test-suite>-<YYYYMMDD>.log` (e.g., `unit-tests-20260402.log`)
- **Complexity**: `complexity-report.txt` (lizard output)

**Evidence Archiving**:
- All evidence archived at baseline creation
- Baseline manifest (manifest.yaml) includes SHA-256 hash of evidence files
- Evidence stored in `baselines/<baseline-name>/evidence/` for reproducibility

---

## 8. VERIFICATION SCHEDULE AND RESOURCE ALLOCATION

### 8.1 Per-Phase Verification Schedule

| Phase | Phase Duration (weeks) | VER Effort (person-weeks) | VER Activities | VER Report Due |
|-------|----------------------|--------------------------|----------------|---------------|
| **1** | 2 | 1.0 | Review SQAP, SCMP, SVaP; produce SQAVR (item 2) | End of Phase 1 |
| **2** | 4 | 2.0 | Review SRS, Overall Test Spec; check T1, T2; produce item 8 | End of Phase 2 |
| **3** | 6 | 3.0 | Review SAS, SDS, Interfaces, Test Specs; check T3–T5c; produce item 14 | End of Phase 3 |
| **4** | 4 | 2.0 | Review Component Design, Component Test Spec; check T6, T8; produce item 17 | End of Phase 4 |
| **5** | 8 | 6.0 | Static analysis (MISRA C, complexity, data/control flow); coverage review; check T7, T11–12; produce item 19 | End of Phase 5 |
| **6** | 4 | 2.0 | Review integration test reports; check T10a–b | During Phase 6 (item 23 in Phase 7) |
| **7** | 6 | 4.0 | Review Overall Test Report; produce item 23 (B1); review VAL reports; produce item † (B2) | End of Phase 7 |
| **8** | 2 | 1.0 | 1st Check on ASR items 45–46 (no VER report) | During Phase 8 |
| **9** | 2 | 1.0 | Review Deployment Plan, Manual, Records; produce item 40 | End of Phase 9 |
| **10** | Ongoing | 0.5 per CR | Review change records; traceability impact analysis; produce item 44 per CR | Per CR closure |

**Total VER Effort (Phases 1–9)**: 22 person-weeks

**VER Team Allocation**:
- Lead Verifier: 50% FTE throughout project
- Static Analysis Verifier: 100% FTE during Phase 5 (8 weeks); 25% FTE other phases

### 8.2 Critical Path and Dependencies

**VER Critical Path Items**:
1. **Phase 5 Static Analysis** (8 weeks) — LONGEST VER activity; parallel to IMP code development
2. **Phase 7 Step B2** (2 weeks) — VER review of VAL reports; sequential after VAL completes
3. **Traceability Verification** (continuous) — VER checks T1–T15 at every gate; prerequisite for gate-check

**VER Dependencies**:
- **SQAP** (item 1) MUST be baselined before VER starts Phase 1 verification
- **SCMP** (item 3) MUST be baselined before VER stores evidence (canonical paths)
- **SVaP** (item 5) MUST be baselined before Phase 7 Step B2 (VER reviews VAL plan)
- **Tools Validation Report** (item 26) MUST be complete before VER uses T2 tools (gcov, Unity)

### 8.3 VER Resource Constraints

**Minimum VER Team Qualifications**:
- EN 50128:2011 §6.2 training certification
- MISRA C:2012 certification
- 5+ years railway software experience (Lead Verifier)
- Static analysis tool expertise (Cppcheck, Clang SA, PC-lint)

**Training Budget**: 40 hours per VER team member per year (SIL 3 requirement)

**Tool Licenses**: 
- Cppcheck, Clang SA, gcov, lcov, lizard, workspace.py: Open source (no license cost)
- PC-lint Plus (optional): Commercial license required if adopted

---

## 9. DEVIATION HANDLING

### 9.1 Deviation Types

| Deviation Type | Definition | Example | VER Action |
|---------------|------------|---------|------------|
| **MISRA C Deviation** | Justified violation of MISRA C:2012 advisory rule per §4.7–4.9 | Advisory Rule 2.3 violated with documented rationale | VER reviews justification; records in MISRA Compliance Matrix; approves or rejects |
| **Coverage Deviation** | Module with < 100% coverage with justified rationale | Unreachable error handler; defensive programming | VER reviews justification; records in Coverage Deviation Log; approves or rejects |
| **Traceability Deviation** | Missing traceability link with justified rationale | Legacy system interface (no upstream requirement) | VER reviews justification; records in Traceability Deviation Log; approves or rejects |
| **EN 50128 Technique Deviation** | Non-adoption of RECOMMENDED (R) technique with justification | Formal Proof not adopted (SIL 3 HR) | VER reviews justification; records in SVP Section 3.1; approved by VMGR |

### 9.2 Deviation Procedure

**Step 1: Developer Raises Deviation**
- Developer identifies need for deviation (e.g., MISRA C advisory rule violation)
- Developer documents justification per MISRA §4.7–4.9 (or equivalent)
- Developer submits deviation request to VER

**Step 2: VER Reviews Deviation**
- VER assesses technical justification
- VER confirms no safety impact
- VER confirms compliance with SIL 3 MANDATORY requirements maintained
- VER records decision in Deviation Log

**Step 3: VER Decision**
- **APPROVE**: Deviation recorded in Verification Report; included in baseline
- **REJECT**: Developer must remediate (remove violation or provide stronger justification)

**Step 4: VMGR Review** (SIL 3 — CRITICAL deviations only)
- VMGR reviews all CRITICAL deviations (safety impact)
- VMGR may escalate to Safety Authority if SIL integrity at risk

### 9.3 Deviation Tracking

**Deviation Log Location**: `evidence/<phase>/deviation-log.md`

**Deviation Log Fields**:
- Deviation ID: `DEV-<YYYY>-<NNN>` (e.g., `DEV-2026-001`)
- Type: MISRA C / Coverage / Traceability / EN 50128 Technique
- Phase: Phase number where deviation raised
- Affected CI: Document ID or source file
- Justification: Technical rationale per MISRA §4.7–4.9 or equivalent
- VER Decision: APPROVE / REJECT
- VER Reviewer: VER name
- Date: Decision date
- VMGR Review: (if CRITICAL) APPROVE / REJECT

**Deviation Reporting**:
- All deviations listed in Verification Report Appendix
- CRITICAL deviations reported to VMGR + Safety Authority
- Deviation metrics tracked in QUA Metrics Reports

---

## 10. COMPLIANCE MATRIX

### 10.1 EN 50128 §6.2 Compliance

| Clause | Requirement | SVP Section | Evidence |
|--------|-------------|-------------|----------|
| **§6.2.4.2** | SVP written under responsibility of Verifier | Cover page | This document (DOC-SVP-2026-001) |
| **§6.2.4.3** | SVP describes activities to ensure proper verification | Section 2 | Verification strategy per phase |
| **§6.2.4.4** | SVP may be sub-divided by phase or component | Section 2.2 | Per-phase verification outputs |
| **§6.2.4.5** | SVP documents criteria, techniques, and tools per Table A.5 | Section 3, 6 | SIL 3 technique selection; tool identification |
| **§6.2.4.6** | SVP describes activities to ensure correctness and completeness | Section 5 | Verification criteria and acceptance thresholds |
| **§6.2.4.7** | Functional, performance, and safety requirements verification | Section 5.1 | Per-phase verification criteria |
| **§6.2.4.8** | Verification results retained per SVP format | Section 7.3 | Evidence collection and storage |
| **§6.2.4.9** | SVP addresses organization, plans, techniques, tools, evidence | Sections 1, 2, 3, 6, 7 | Complete SVP structure |
| **§6.2.4.12–13** | Verification Reports per phase | Section 7.1 | Verification Report format |

### 10.2 EN 50128 Table A.5 Compliance (SIL 3)

| # | Technique | Table Ref | SIL 3 | SVP Section | TDC Selection |
|---|-----------|-----------|-------|-------------|---------------|
| **D.24** | Static Analysis | A.5 | **M** | 3.2 | **ADOPTED** (Cppcheck, Clang SA) |
| **D.58** | Traceability | A.5 | **M** | 4 | **ADOPTED** (T1–T15, workspace.py) |
| **D.32** | Inspection | A.5 | **M** | 3.1 | **ADOPTED** (requirements, design, code review) |
| **D.29** | Simulation | A.5 | R | 3.1 | ADOPTED (integration testing simulation) |
| **D.37** | Metrics | A.5 | HR | 3.1 | ADOPTED (cyclomatic complexity, defect density) |
| **D.1** | Formal Proof | A.5 | HR | 3.1 | NOT ADOPTED (justification documented) |

### 10.3 EN 50128 Table A.19 Compliance (SIL 3)

| # | Technique | SIL 3 | SVP Section | TDC Tool |
|---|-----------|-------|-------------|----------|
| **1** | Boundary Value Analysis | **M** | 3.2 | Cppcheck, manual review |
| **2** | Control Flow Analysis | HR | 3.2 | Cppcheck, Clang SA |
| **3** | Data Flow Analysis | HR | 3.2 | Cppcheck, Clang SA |
| **4** | Error Guessing | R | 3.2 | Manual review |
| **5** | Equivalence Classes / Input Partition | **M** | 3.2 | Manual analysis + test case generation |

### 10.4 EN 50128 Table A.21 Compliance (SIL 3)

| # | Coverage Type | SIL 3 | TDC Target | SVP Section | Tool |
|---|--------------|-------|-----------|-------------|------|
| **1** | Statement Coverage | HR | **100%** | 3.3 | gcov/lcov |
| **2** | Branch Coverage | HR | **100%** | 3.3 | gcov/lcov |
| **3** | Compound Condition Coverage | HR | **100%** | 3.3 | gcov/lcov (manual verification) |
| **4** | MC/DC Coverage | R | N/A | 3.3 | Not adopted for SIL 3 |

---

## 11. CONTINUOUS IMPROVEMENT

### 11.1 SVP Update Triggers

This SVP SHALL be reviewed and updated (if necessary) when:
- **Addition of new verification tools**: VER identifies tool qualification need; updates Section 6
- **Change in SIL level**: SIL level change requires re-evaluation of Table A.5, A.19, A.21 techniques
- **Change in verification approach or techniques**: VER identifies process improvement; updates Section 3
- **Identification of new verification activities**: New phase or deliverable added; updates Section 2.2
- **Lessons learned from Verification Reports**: VER identifies systemic issue; updates verification criteria
- **EN 50128 standard updates**: New standard version published; updates normative references
- **Tool qualification status changes**: T1 → T2 reclassification; updates Section 6.2

**Review Frequency**: Annually or when lifecycle phase gates fail verification criteria (whichever is sooner)

**Update Procedure**:
1. VER identifies SVP update trigger
2. VER drafts SVP update (new version number)
3. VER submits to QUA for format check
4. On QUA PASS: VAL performs 2nd check
5. VMGR approves SVP update (SIL 3)
6. CM baselines updated SVP; archives old version
7. COD notified of SVP update

### 11.2 Lessons Learned Process

**VER SHALL**:
- Record lessons learned in each Verification Report (Appendix section)
- Identify process improvements (verification technique effectiveness, tool usability)
- Identify systemic issues (repeated defect patterns, traceability gaps)
- Submit lessons learned summary to VMGR at end of each phase
- Update SVP if lessons learned identify verification process deficiency

**Lessons Learned Topics**:
- Verification technique effectiveness (Did static analysis catch defects that testing missed?)
- Tool usability (Were tools easy to use? Did they produce actionable results?)
- Verification criteria adequacy (Were acceptance thresholds appropriate for SIL 3?)
- Traceability completeness (Were T1–T15 rules sufficient? Were gaps identified?)
- Defect patterns (Are defects concentrated in specific modules or phases?)

**Lessons Learned Output**: Stored in `docs/lessons-learned/VER-Lessons-Learned-PhaseN.md`

---

## 12. REFERENCES

### 12.1 Normative References

| Reference | Title |
|-----------|-------|
| **EN 50128:2011** | Railway applications — Communication, signalling and processing systems — Software for railway control and protection systems |
| **EN 50126-1:2017** | Railway applications — The specification and demonstration of Reliability, Availability, Maintainability and Safety (RAMS) — Part 1: Generic RAMS process |
| **EN 50126-2:2017** | Railway applications — The specification and demonstration of Reliability, Availability, Maintainability and Safety (RAMS) — Part 2: Systems approach to safety |
| **MISRA C:2012** | Guidelines for the use of the C language in critical systems (Third Edition) |
| **ISO 9001:2015** | Quality management systems — Requirements |

### 12.2 Project References

| Document ID | Document Name | Location |
|-------------|---------------|----------|
| DOC-SQAP-2026-001 | Software Quality Assurance Plan | `docs/phase-1-planning/Software-Quality-Assurance-Plan.md` |
| DOC-SCMP-2026-001 | Software Configuration Management Plan | `docs/phase-1-planning/Software-Configuration-Management-Plan.md` |
| DOC-SVaP-2026-001 | Software Validation Plan | `docs/phase-1-planning/Software-Validation-Plan.md` |
| — | DELIVERABLES.md | `/home/norechang/test/opencode-en50128/DELIVERABLES.md` |
| — | WORKFLOW.md | `/home/norechang/test/opencode-en50128/WORKFLOW.md` |
| — | TRACEABILITY.md | `/home/norechang/test/opencode-en50128/TRACEABILITY.md` |
| — | LIFECYCLE.md | `/home/norechang/test/opencode-en50128/LIFECYCLE.md` |
| — | tasks/VnV-PROCESS.md | `/home/norechang/test/opencode-en50128/tasks/VnV-PROCESS.md` |
| — | activities/vnv-process.yaml | `/home/norechang/test/opencode-en50128/activities/vnv-process.yaml` |

---

## APPENDIX A: VERIFICATION REPORT TEMPLATES

All Verification Report templates are located in `deliverables/<phase>/` directory:

| Item | Template File |
|------|--------------|
| 2 | `deliverables/planning/Software-SQAP-Verification-Report-template.md` |
| 8 | `deliverables/requirements/Software-Requirements-Verification-Report-template.md` |
| 14 | `deliverables/architecture/Software-Architecture-Design-Verification-Report-template.md` |
| 17 | `deliverables/component-design/Software-Component-Design-Verification-Report-template.md` |
| 19 | `deliverables/implementation/Software-Source-Code-Verification-Report-template.md` |
| 23 | `deliverables/integration/Software-Integration-Verification-Report-template.md` |
| † | `deliverables/validation/Software-Validation-Verification-Report-template.md` |
| 40 | `deliverables/deployment/Software-Deployment-Verification-Report-template.md` |
| 44 | `deliverables/maintenance/Software-Maintenance-Verification-Report-template.md` |

---

## APPENDIX B: TRACEABILITY MATRIX TEMPLATES

Traceability matrices are stored in `evidence/traceability/` with naming convention:

```
evidence/traceability/doc<from>_to_doc<to>.csv
```

**T1–T15 Matrix Files**:
- T1: `docS1_to_doc6.csv` (System Req → SW Req)
- T2: `doc6_to_doc7.csv` (SW Req → Overall Test Spec)
- T3: `doc6_to_doc9.csv` (SW Req → SW Architecture)
- T4: `doc9_to_doc10.csv` (SW Architecture → SW Design)
- T5a: `doc10_to_doc12.csv` (SW Design → Integration Test Spec)
- T5b: `doc9_to_doc13.csv` (SW Architecture → SW/HW Integration Test Spec)
- T5c: `doc9_to_doc11.csv` (SW Architecture → SW Interface Specifications)
- T6: `doc10_to_doc15.csv` (SW Design → SW Component Design)
- T7: `doc15_to_doc18.csv` (SW Component Design → Source Code)
- T8: `doc15_to_doc16.csv` (SW Component Design → Component Test Spec)
- T10a: `doc12_to_doc21.csv` (Integration Test Spec → Integration Test Report)
- T10b: `doc13_to_doc22.csv` (SW/HW Integration Test Spec → SW/HW Integration Test Report)
- T11: `doc16_to_doc20.csv` (Component Test Spec → Component Test Report)
- T12: `doc18_to_doc20.csv` (Source Code → Component Test Report)
- T13: `doc6_to_doc25.csv` (SW Req → Validation Report)
- T14: `doc20_to_doc24.csv` (Component Test Reports → Overall Test Report)
- T15: `doc21_to_doc24.csv` (Integration Test Reports → Overall Test Report)

---

## APPENDIX C: ACRONYMS AND DEFINITIONS

| Term | Definition |
|------|------------|
| **ASR** | Assessor — Independent safety assessor per §6.4 |
| **CCB** | Change Control Board — Authority for approving changes to baselines |
| **CI** | Configuration Item — Any software artifact under configuration management |
| **CM** | Configuration Manager — Responsible for version control and baselines |
| **COD** | Lifecycle Coordinator — End-to-end lifecycle orchestration and phase gate enforcement |
| **DES** | Designer — Software architecture and design per §5.3.2 |
| **FTE** | Full-Time Equivalent — Staffing measure (1 FTE = 1 person full-time) |
| **HR** | Highly Recommended — EN 50128 technique recommendation level |
| **IMP** | Implementer — Code implementation per §5.3.3 |
| **INT** | Integrator — Software integration per §5.3.6 |
| **M** | Mandatory — EN 50128 technique requirement level |
| **MC/DC** | Modified Condition/Decision Coverage — Test coverage technique |
| **MISRA** | Motor Industry Software Reliability Association — C coding standard |
| **NCR** | Non-Conformance Report — Quality issue tracking |
| **PM** | Project Manager — Overall project responsibility per §5.1.2.4 |
| **QUA** | Quality Assurance Engineer — Software quality assurance per §6.5 |
| **R** | Recommended — EN 50128 technique recommendation level |
| **RAMS** | Reliability, Availability, Maintainability, Safety — EN 50126 |
| **REQ** | Requirements Engineer — Requirements specification per §7.2 |
| **RTM** | Requirements Traceability Matrix — Traceability artifact |
| **SAF** | Safety Engineer — Hazard analysis and safety case per §7.1 |
| **SCMP** | Software Configuration Management Plan — Annex C item 3 |
| **SIL** | Safety Integrity Level — 0 (lowest) to 4 (highest) |
| **SQAP** | Software Quality Assurance Plan — Annex C item 1 |
| **SRS** | Software Requirements Specification — Annex C item 6 |
| **SVaP** | Software Validation Plan — Annex C item 5 |
| **SVP** | Software Verification Plan — This document (Annex C item 4) |
| **TDC** | Train Door Control System — Project name |
| **TST** | Tester — Software testing per §5.3.4 |
| **VAL** | Validator — Software validation per §5.3.7 |
| **VCS** | Version Control System (Git) — Repository for all CIs under CM control |
| **VER** | Verifier — Software verification per §5.3.5 |
| **VMGR** | V&V Manager — Independent V&V authority for SIL 3-4 projects per §5.1.2.10e |

---

**END OF SOFTWARE VERIFICATION PLAN**
