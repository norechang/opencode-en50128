# Software Validation Plan

**Document ID:** DOC-SVaP-YYYY-NNN  
**Document Type:** Software-Validation-Plan  
**Phase:** Phase 1 — Planning (Annex C item 5)  
**EN 50128 Reference:** §6.3.4.2–6.3.4.6, §7.7.4.1  
**Author Role:** VAL (§6.3.4.3 — written under responsibility of Validator)  
**1st Check:** VER | **2nd Check:** none

---

## Document Control

| Version | Date | Author | Reviewer | Approver | Changes |
|---------|------|--------|----------|----------|---------|
| 0.1 | YYYY-MM-DD | [VAL Name] | [VER Name] | [VMGR/PM Name] | Initial draft |

**Configuration Item:** [CI ID]  
**Baseline:** [Baseline ID]

---

## Approvals

| Role | Name | Signature | Date | SIL Level |
|------|------|-----------|------|-----------|
| Validator (VAL) | [Name] | [Signature] | YYYY-MM-DD | [0/1/2/3/4] |
| Verifier (VER) — 1st Check | [Name] | [Signature] | YYYY-MM-DD | [0/1/2/3/4] |
| Quality Assurance (QUA) — Format Gate | [Name] | [Signature] | YYYY-MM-DD | [0/1/2/3/4] |
| V&V Manager (VMGR) | [Name] | [Signature] | YYYY-MM-DD | [3/4 only] |
| Project Manager (PM) | [Name] | [Signature] | YYYY-MM-DD | [0/1/2] |

**Independence Declaration (SIL 3-4):**  
Validator [Name] declares independence from the Requirements Manager, Designer, Implementer,
Integrator, Tester, and Verifier per EN 50128 §5.1.2.10f. Validator does not report to the
Project Manager. Validator reports to [Safety Authority / Customer representative].

---

## 1. Introduction

### 1.1 Purpose

This Software Validation Plan (SVaP) defines the strategy, methods, resources, and acceptance
criteria for validating [Software Component / System Name] at SIL [level]. It is produced per
EN 50128:2011 §6.3.4.2–6.3.4.6 and covers the validation activities to be performed in Phase 7.

### 1.2 Scope

| Item | Value |
|------|-------|
| Software component | [Name and version] |
| SIL level | [0 / 1 / 2 / 3 / 4] |
| Target platform | [Hardware / OS description] |
| Operational environment | [Railway subsystem, operational context] |
| Validation phase | Phase 7 — Validation |
| Standards applied | EN 50128:2011, EN 50126, [others] |

### 1.3 References

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-SRS-YYYY-NNN | Software Requirements Specification | X.Y |
| DOC-SVP-YYYY-NNN | Software Verification Plan | X.Y |
| DOC-SQAP-YYYY-NNN | Software Quality Assurance Plan | X.Y |
| DOC-SCMP-YYYY-NNN | Software Configuration Management Plan | X.Y |
| STD-EN50128 | EN 50128:2011 Railway Applications | — |

### 1.4 Definitions and Abbreviations

| Term | Definition |
|------|-----------|
| VAL | Software Validator |
| SVaP | Software Validation Plan |
| SIL | Safety Integrity Level |
| SRS | Software Requirements Specification |
| TST | Tester |
| VER | Verifier |
| VMGR | V&V Manager |
| WCET | Worst-Case Execution Time |

---

## 2. Validation Organization and Independence

### 2.1 Validation Team

| Role | Name | Organization | Responsibilities |
|------|------|--------------|-----------------|
| Validator (VAL) | [Name] | [Organization] | Overall validation authority; release decision |
| Validation Tester | [Name] | [Organization] | Execute validation test cases |
| Customer Representative | [Name] | [Organization] | Witness acceptance tests; sign off |

### 2.2 Independence Statement (SIL 3-4)

Per EN 50128 §5.1.2.10f, the Validator:
- Is NOT the Requirements Manager, Designer, Implementer, Integrator, Tester, or Verifier
- Does NOT report to the Project Manager
- Has an independent reporting line to: [Safety Authority / Customer]
- [Names of excluded persons and their development roles]

### 2.3 Coordination with Verification (VER)

Validation begins after VER has approved Phase 6 deliverables and VMGR has authorised Phase 7
Track B Step B2. VAL coordinates with VER for the Validation Verification Report (item †) at
the end of Phase 7.

---

## 3. Validation Strategy (§6.3.4.4)

### 3.1 Justification of Approach

[Summarise the chosen validation strategy and justify it against §6.3.4.4. Explain why the
selected techniques from Table A.7 are appropriate for this SIL level and application domain.]

### 3.2 Validation Techniques Selected (Table A.7)

| # | Technique | SIL Recommendation | Selected | Justification |
|---|-----------|-------------------|----------|---------------|
| 1 | Performance Testing (A.18) | SIL 3-4: **M** | [Yes/No] | [Reason] |
| 2 | Functional and Black-box Testing (A.14) | SIL 3-4: **M** | [Yes/No] | [Reason] |
| 3 | Modelling (A.17) | SIL 3-4: R | [Yes/No] | [Reason] |
| 4 | Regression Testing | SIL 3-4: **M** | [Yes/No] | [Reason] |
| 5 | Boundary Value Analysis | SIL 3-4: **M** | [Yes/No] | [Reason] |
| 6 | Equivalence Classes | SIL 3-4: HR | [Yes/No] | [Reason] |

### 3.3 Relationship to Verification

Validation does not repeat unit or integration testing (those are VER/TST responsibilities).
Validation focuses on system-level behaviour against stakeholder needs in the target environment.

---

## 4. Validation Environment (§7.7.4.5)

### 4.1 Target Hardware

| Item | Description |
|------|-------------|
| Processor | [CPU type, frequency] |
| Memory | [RAM, Flash sizes] |
| I/O interfaces | [CAN, Ethernet, serial, digital I/O, etc.] |
| Operating system / RTOS | [Name, version] |
| Configuration | [Production-representative / HIL / simulator — justify] |

### 4.2 Test Equipment

| Equipment | Purpose | Calibration status |
|-----------|---------|-------------------|
| [Tool / bench] | [Purpose] | [Calibrated / N/A] |

### 4.3 Software Baseline to be Validated

| Item | Version | Configuration Item ID |
|------|---------|----------------------|
| Source code | [version] | [CI ID] |
| Executable / firmware | [version] | [CI ID] |
| Test harness | [version] | [CI ID] |

---

## 5. Validation Test Cases and Operational Scenarios

### 5.1 Functional Test Cases (MANDATORY SIL 3-4, Table A.14)

For each SRS requirement, at least one functional test case shall exist. List top-level test
groups; detailed test cases are in the Overall Software Test Specification (item 7).

| Test Group ID | SRS Requirement(s) | Technique | Pass Criterion |
|--------------|-------------------|-----------|---------------|
| FT-001 | REQ-xxx | Black-box | [Expected output / behaviour] |
| ... | ... | ... | ... |

### 5.2 Operational Scenarios

| Scenario ID | Name | Type | SRS Requirements Covered |
|-------------|------|------|--------------------------|
| SC-001 | Normal operation — [description] | Normal | REQ-xxx, REQ-yyy |
| SC-002 | Degraded mode — [description] | Degraded | REQ-xxx |
| SC-003 | Emergency — [description] | Safety-critical | REQ-xxx |
| SC-004 | Recovery — [description] | Recovery | REQ-xxx |
| ... | ... | ... | ... |

Each scenario shall include preconditions, step-by-step procedure, expected results, and
acceptance criterion. Detailed procedures are in Appendix A.

### 5.3 Performance Test Cases (MANDATORY SIL 3-4, Table A.18)

| Test ID | Parameter | Requirement (from SRS) | Measurement Method | Pass Criterion |
|---------|-----------|----------------------|--------------------|---------------|
| PT-001 | Response time — [function] | ≤ [X] ms | [Instrumentation] | No deadline miss |
| PT-002 | WCET — [task] | ≤ [X] µs | [Tool] | Within budget |
| PT-003 | Memory usage | ≤ [X] KB | [Tool] | Within allocation |
| PT-004 | CPU utilisation | ≤ [X] % | [Tool] | Peak within limit |
| ... | ... | ... | ... | ... |

### 5.4 Acceptance Test Cases (Customer Acceptance)

| Test ID | Customer Requirement | Procedure Reference | Acceptance Criterion |
|---------|---------------------|--------------------|--------------------|
| UAT-001 | [User-facing requirement] | Appendix B | Customer sign-off |
| ... | ... | ... | ... |

---

## 6. Acceptance Criteria (§6.3.4.6)

### 6.1 Mandatory Acceptance Criteria (SIL 3-4)

- [ ] All functional test cases executed and passed (100%)
- [ ] All performance requirements met with measured evidence
- [ ] All operational scenarios executed and passed
- [ ] End-to-end requirements traceability complete (SRS → validation tests)
- [ ] Zero unresolved critical or high-severity defects
- [ ] All medium-severity defects reviewed, impact assessed, and dispositioned
- [ ] Verification process completeness confirmed per §6.3.4.9
- [ ] Customer acceptance obtained
- [ ] Software baseline fully identified (§6.3.4.10)
- [ ] All known deficiencies documented with impact assessment (§6.3.4.11)

### 6.2 Release Decision Criteria (§5.1.2.8 / §6.3.4.16)

VAL's AGREE decision for release shall be given only when all §6.1 criteria are met.
VAL's DISAGREE decision blocks release regardless of PM or COD direction.

---

## 7. Resources and Schedule

### 7.1 Validation Resources

| Resource | Requirement |
|----------|-------------|
| Target hardware | [Quantity and type] |
| Test environment | [Lab / HIL / field] |
| Validation team effort | [Person-days] |
| Customer availability | [Dates for UAT] |

### 7.2 Schedule

| Activity | Start | End | Predecessor |
|----------|-------|-----|-------------|
| Validation environment setup | | | Phase 6 complete |
| Functional testing | | | Env setup |
| Performance testing | | | Functional testing |
| Operational scenarios | | | Functional testing |
| Acceptance testing | | | All above |
| Validation Report authoring | | | All testing |
| VER item † review | | | Report submitted |

---

## 8. Deliverables

| Annex C Item | Deliverable | Author | Phase |
|-------------|-------------|--------|-------|
| 5 | Software Validation Plan (this document) | VAL | 1 |
| 25 | Software Validation Report | VAL | 7 |
| 26 | Tools Validation Report (if applicable) | VAL | 7 |
| 27 | Release Note (§7.7.4.12) | VAL / PM per SQAP | 7 |

---

## Appendix A: Operational Scenario Procedures

### SC-001: [Scenario Name]

**Type:** [Normal / Degraded / Emergency / Recovery]  
**SRS References:** [REQ IDs]

**Preconditions:**
- [State 1]
- [State 2]

**Procedure:**

| Step | Action | Expected Result |
|------|--------|----------------|
| 1 | [Action] | [Expected output] |
| 2 | [Action] | [Expected output] |
| ... | ... | ... |

**Acceptance Criterion:** [Pass/fail statement]  
**Actual Result:** [Filled during execution]  
**Result:** [ ] PASS  [ ] FAIL  
**Tester:** _____________ **Date:** _______

---

## Appendix B: User Acceptance Test Procedures

### UAT-001: [Test Name]

**Customer Requirement:** [Requirement]  
**Tester:** [Customer representative name and role]

**Preconditions:**
- [State]

**Procedure (user language — no technical jargon):**

| Step | Action | Expected Observation |
|------|--------|---------------------|
| 1 | [User action] | [What user should see / feel] |
| ... | ... | ... |

**Acceptance Criterion:** [Pass/fail statement]  
**Customer Feedback:** [Space for comments]  
**Result:** [ ] PASS  [ ] FAIL  
**Customer Signature:** _________________ **Date:** _______

---

**End of Software Validation Plan**
