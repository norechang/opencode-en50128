# Risk Register

**Document ID:** DOC-RR-YYYY-NNN  
**Project:** [Project Name]  
**System/Subsystem:** [System Name]  
**SIL Level:** [0 | 1 | 2 | 3 | 4]

---

## Document Control

| Version | Date | Author | Change Description | Status |
|---------|------|--------|-------------------|--------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft | Draft |

---

## 1. Risk Register Overview

**Purpose:** Track and manage all project risks throughout the lifecycle.

**Risk Management Process:**
1. **Identification:** Continuous risk identification by all team members
2. **Analysis:** Assess probability and impact for each risk
3. **Prioritization:** Calculate risk score (Probability × Impact)
4. **Mitigation:** Develop and execute mitigation strategies
5. **Monitoring:** Track risk status and trigger conditions
6. **Control:** Execute contingency plans when risks materialize

**Risk Score Calculation:**
- **Risk Score = Probability × Impact**
- Probability: High (3), Medium (2), Low (1)
- Impact: High (3), Medium (2), Low (1)
- Score Range: 1 (lowest) to 9 (highest)

**Risk Thresholds:**
- **Critical (Score 9):** Immediate escalation to senior management
- **High (Score 6-8):** Active mitigation required, weekly review
- **Medium (Score 3-4):** Mitigation planned, bi-weekly review
- **Low (Score 1-2):** Monitor only, monthly review

---

## 2. Risk Register

### 2.1 Active Risks

| Risk ID | Risk Title | Category | Probability | Impact | Score | Status | Owner |
|---------|-----------|----------|-----------|--------|-------|--------|-------|
| RISK-001 | [Risk title] | [Category] | [H/M/L] | [H/M/L] | [1-9] | [Active/Mitigated/Closed] | [Name] |
| RISK-002 | MISRA C violations exceed budget | Technical | M (2) | H (3) | 6 | Active | IMP, QUA |
| RISK-003 | Coverage target not achieved | Technical | M (2) | H (3) | 6 | Active | TST, VER |
| RISK-004 | Independent resources unavailable (SIL 3-4) | Resource | L (1) | H (3) | 3 | Active | PM, VMGR |
| RISK-005 | Complexity exceeds SIL limits | Technical | M (2) | M (2) | 4 | Active | DES, IMP |
| RISK-006 | Requirements volatility | Requirements | M (2) | M (2) | 4 | Active | REQ, PM |
| RISK-007 | Static analysis tool license delay | Resource | L (1) | M (2) | 2 | Active | PM |
| RISK-008 | Safety assessment delay (SIL 3-4) | Schedule | L (1) | H (3) | 3 | Active | ASR, PM |
| RISK-009 | Integration interface mismatches | Technical | M (2) | M (2) | 4 | Active | INT, DES |
| RISK-010 | Defect backlog growth | Quality | M (2) | M (2) | 4 | Active | IMP, TST |

---

## 3. Risk Details

### RISK-001: [Risk Title]

**Category:** [Technical | Schedule | Resource | Safety | Compliance | External]  
**Identified By:** [Name]  
**Date Identified:** YYYY-MM-DD  
**Status:** [Active | Mitigated | Closed | Realized]

**Description:**
[Detailed description of the risk, including conditions under which it might occur]

**Probability:**
- **Rating:** [High (3) | Medium (2) | Low (1)]
- **Justification:** [Why this probability rating?]

**Impact:**
- **Rating:** [High (3) | Medium (2) | Low (1)]
- **Justification:** [What would be the impact if this risk occurs?]
- **Impact Areas:**
  - Schedule impact: [Description]
  - Cost impact: [Description]
  - Quality impact: [Description]
  - Safety impact: [Description]

**Risk Score:** [Probability × Impact = 1-9]

**Triggers:**
- [Trigger condition 1 - early warning sign]
- [Trigger condition 2 - early warning sign]

**Mitigation Strategy:**
[Proactive actions to reduce probability or impact BEFORE risk occurs]
1. [Mitigation action 1]
2. [Mitigation action 2]

**Contingency Plan:**
[Reactive actions to take IF risk occurs]
1. [Contingency action 1]
2. [Contingency action 2]

**Owner:** [Name]  
**Mitigation Status:** [Not Started | In Progress | Complete]  
**Next Review Date:** YYYY-MM-DD

---

### RISK-002: MISRA C Violations Exceed Budget (SIL 2+)

**Category:** Technical / Compliance  
**Identified By:** [Name]  
**Date Identified:** YYYY-MM-DD  
**Status:** Active

**Description:**
For SIL 2+ projects, MISRA C:2012 compliance is MANDATORY with zero mandatory violations. Risk that code implementation generates excessive MISRA C violations (especially mandatory violations), requiring significant rework and delaying project.

**Probability:**
- **Rating:** Medium (2)
- **Justification:** C programming is complex; developers may not be fully trained on MISRA C initially; static analysis reveals violations late in implementation phase.

**Impact:**
- **Rating:** High (3)
- **Justification:** MISRA C mandatory violations are BLOCKING for SIL 2+; extensive rework required; potential schedule delay of 2-4 weeks per 10K LOC; EN 50128 compliance at risk.
- **Impact Areas:**
  - Schedule impact: 2-4 week delay per 10K LOC to fix violations
  - Cost impact: Rework cost + static analysis tool cost
  - Quality impact: Rushed fixes may introduce defects
  - Safety impact: Non-compliant code cannot be certified (SIL 2+)

**Risk Score:** 2 × 3 = 6 (High Risk)

**Triggers:**
- Early static analysis shows >50 mandatory violations per 1K LOC
- Developers unfamiliar with MISRA C rules
- Code reviews reveal non-MISRA C patterns
- Static analysis tool not integrated in CI pipeline

**Mitigation Strategy:**
1. **Early MISRA C training** for all implementers (2 days)
2. **Static analysis integration** in CI pipeline from day 1 (PC-lint Plus)
3. **MISRA C coding templates** provided to all implementers
4. **Code review checklist** includes MISRA C compliance
5. **Weekly MISRA C metrics** tracked and reviewed
6. **Budget 10% extra effort** for MISRA C refactoring

**Contingency Plan:**
1. **Allocate dedicated refactoring sprint** (2 weeks) after initial implementation
2. **Bring in MISRA C expert consultant** for code review and fixes
3. **Prioritize mandatory violations** (must be zero) over required/advisory
4. **Negotiate schedule extension** with customer if needed

**Owner:** Implementer (IMP), Quality Assurance (QUA)  
**Mitigation Status:** In Progress  
**Next Review Date:** YYYY-MM-DD (weekly)

**Action Items:**
| Action | Responsible | Due Date | Status |
|--------|------------|----------|--------|
| MISRA C training for team | QUA | YYYY-MM-DD | In Progress |
| PC-lint Plus license procurement | PM | YYYY-MM-DD | Complete |
| CI pipeline integration | IMP | YYYY-MM-DD | Not Started |
| MISRA C coding template creation | IMP | YYYY-MM-DD | Not Started |

---

### RISK-003: Test Coverage Target Not Achieved (SIL 2+)

**Category:** Technical / Quality  
**Identified By:** [Name]  
**Date Identified:** YYYY-MM-DD  
**Status:** Active

**Description:**
EN 50128 requires 100% branch coverage (SIL 2+) and 100% statement/branch/condition coverage (SIL 3-4). Risk that test suite cannot achieve required coverage due to dead code, unreachable branches, complex error conditions, or insufficient test development effort.

**Probability:**
- **Rating:** Medium (2)
- **Justification:** Coverage targets are strict (100%); error handling paths may be difficult to test; defensive programming creates many branches; late test development reduces time to close coverage gaps.

**Impact:**
- **Rating:** High (3)
- **Justification:** Coverage is MANDATORY per EN 50128 Table A.21; insufficient coverage is BLOCKING for SIL 2+; requires extensive test development and potential code refactoring; delays validation phase.
- **Impact Areas:**
  - Schedule impact: 1-3 week delay to close coverage gaps
  - Cost impact: Additional test development effort, potential code refactoring
  - Quality impact: Untested code may contain defects
  - Safety impact: Coverage is certification requirement (SIL 2+)

**Risk Score:** 2 × 3 = 6 (High Risk)

**Triggers:**
- Unit test coverage <80% statement at code complete
- Branch coverage <70% at integration
- Coverage not tracked during development
- Test-to-requirement traceability incomplete
- Complex functions (cyclomatic complexity >10) without adequate tests

**Mitigation Strategy:**
1. **Test-driven development (TDD)** for all safety-critical modules
2. **Coverage tracking from day 1** (gcov/lcov integrated in CI)
3. **Coverage review in code reviews** (minimum 90% statement per module)
4. **Early coverage analysis** (weekly) to identify gaps early
5. **Budget 30% effort for testing** (industry standard for SIL 2+)
6. **Dead code elimination** during design phase (reduce untestable code)
7. **Testability review** in design phase

**Contingency Plan:**
1. **Allocate dedicated testing sprint** (2 weeks) after integration
2. **Refactor complex functions** to improve testability (reduce complexity)
3. **Document coverage justification** for uncovered code (if safety-justified)
4. **Bring in test automation consultant** for difficult test cases
5. **Extend validation phase** if needed to achieve coverage

**Owner:** Tester (TST), Verifier (VER)  
**Mitigation Status:** In Progress  
**Next Review Date:** YYYY-MM-DD (weekly)

**Action Items:**
| Action | Responsible | Due Date | Status |
|--------|------------|----------|--------|
| TDD training for team | TST | YYYY-MM-DD | Not Started |
| gcov/lcov CI integration | TST | YYYY-MM-DD | Not Started |
| Coverage tracking dashboard | TST | YYYY-MM-DD | Not Started |
| Testability review in design phase | DES, TST | YYYY-MM-DD | Not Started |

---

### RISK-004: Independent Resources Unavailable (SIL 3-4)

**Category:** Resource / Organizational  
**Identified By:** [Name]  
**Date Identified:** YYYY-MM-DD  
**Status:** Active

**Description:**
For SIL 3-4 projects, EN 50128 MANDATES independent Verifier, Validator (V&V Manager), and Assessor roles. Risk that independent resources are unavailable, delayed, or lack required competencies, preventing phase gate approval and certification.

**Probability:**
- **Rating:** Low (1)
- **Justification:** Independence requirement is known early; resources can be planned in advance; multiple third-party assessment firms available.

**Impact:**
- **Rating:** High (3)
- **Justification:** Independence is MANDATORY (EN 50128 Section 5.1.2.10); lack of independent resources is BLOCKING for certification; project cannot proceed without V&V approval; potential project cancellation or de-scoping to lower SIL.
- **Impact Areas:**
  - Schedule impact: 4-12 week delay to find and onboard independent resources
  - Cost impact: Independent resources typically 50-100% more expensive
  - Quality impact: Rushed independence workaround may compromise quality
  - Safety impact: Independence ensures unbiased safety assessment

**Risk Score:** 1 × 3 = 3 (Medium Risk)

**Triggers:**
- Independent resource hiring delayed beyond project start +1 month
- Candidate independence verification fails (conflict of interest)
- Independent resource lacks EN 50128 competency
- Customer/Safety Authority rejects proposed independent organization

**Mitigation Strategy:**
1. **Early resource commitment** (6 months before project start)
2. **Pre-qualified vendor list** for independent V&V and assessment
3. **Independence verification process** documented and approved by customer
4. **Backup independent organizations** identified (minimum 2 options)
5. **Competency verification** for all independent resources (EN 50128 experience, SIL 3-4 projects)
6. **Contract independence clauses** ensure no conflicts of interest

**Contingency Plan:**
1. **Accelerate backup vendor onboarding** if primary vendor unavailable
2. **Negotiate timeline extension** with customer if resource delay occurs
3. **Consider de-scoping to SIL 2** if independence cannot be achieved (last resort)
4. **Engage Safety Authority early** for independence approval

**Owner:** Project Manager (PM), V&V Manager (VMGR)  
**Mitigation Status:** In Progress  
**Next Review Date:** YYYY-MM-DD (monthly)

**Action Items:**
| Action | Responsible | Due Date | Status |
|--------|------------|----------|--------|
| Identify 3 independent V&V vendors | PM | YYYY-MM-DD | In Progress |
| Request vendor qualifications | PM | YYYY-MM-DD | Not Started |
| Draft independence verification procedure | QUA | YYYY-MM-DD | Not Started |
| Customer approval of independence approach | PM | YYYY-MM-DD | Not Started |

---

### RISK-005: Cyclomatic Complexity Exceeds SIL Limits

**Category:** Technical / Design  
**Identified By:** [Name]  
**Date Identified:** YYYY-MM-DD  
**Status:** Active

**Description:**
EN 50128 recommends cyclomatic complexity limits: ≤10 (SIL 3-4), ≤15 (SIL 2). Risk that implemented functions exceed complexity limits, requiring refactoring and potentially introducing defects.

**Probability:**
- **Rating:** Medium (2)
- **Justification:** Complex algorithms and error handling naturally increase complexity; developers may not monitor complexity during implementation; requirements creep adds branches.

**Impact:**
- **Rating:** Medium (2)
- **Justification:** Complexity limits are HIGHLY RECOMMENDED (not mandatory) but expected by assessors; high complexity reduces testability and maintainability; refactoring is time-consuming and risky.
- **Impact Areas:**
  - Schedule impact: 1-2 weeks to refactor complex functions
  - Cost impact: Refactoring effort + potential retest
  - Quality impact: Refactoring may introduce defects
  - Safety impact: High complexity reduces confidence in correctness

**Risk Score:** 2 × 2 = 4 (Medium Risk)

**Triggers:**
- Complexity analysis shows >10% of functions exceed limits
- Design review identifies complex algorithms without decomposition
- Code review flags functions with deep nesting (>5 levels)

**Mitigation Strategy:**
1. **Design for simplicity** - decompose complex functions during design phase
2. **Complexity analysis in CI** (Lizard tool, daily builds)
3. **Complexity review in code reviews** (reject functions exceeding limits)
4. **Refactoring budget** (5% of implementation effort)
5. **Complexity dashboard** (track max/average complexity)

**Contingency Plan:**
1. **Allocate refactoring sprint** (1 week) after code complete
2. **Pair programming for complex modules** (reduce complexity through collaboration)
3. **Document complexity justification** for functions that cannot be simplified

**Owner:** Designer (DES), Implementer (IMP)  
**Mitigation Status:** In Progress  
**Next Review Date:** YYYY-MM-DD (bi-weekly)

---

### RISK-006: Requirements Volatility

**Category:** Requirements / Scope  
**Identified By:** [Name]  
**Date Identified:** YYYY-MM-DD  
**Status:** Active

**Description:**
Risk that requirements change frequently after requirements baseline, causing rework in design, implementation, testing, and documentation; impacts traceability and schedule.

**Probability:**
- **Rating:** Medium (2)
- **Justification:** Railway projects often evolve during development; customer needs may change; regulatory requirements may be clarified; interface changes from external systems.

**Impact:**
- **Rating:** Medium (2)
- **Justification:** Requirements changes trigger rework across all downstream phases; traceability must be updated; retesting required; change control overhead.
- **Impact Areas:**
  - Schedule impact: 1-3 weeks per major requirements change
  - Cost impact: Rework effort across multiple phases
  - Quality impact: Late changes increase defect risk
  - Safety impact: Requirements changes may introduce new hazards

**Risk Score:** 2 × 2 = 4 (Medium Risk)

**Triggers:**
- Requirements change rate >10% per month
- Requirements baseline delayed
- Customer feedback reveals missing requirements
- External interface specifications change

**Mitigation Strategy:**
1. **Robust requirements elicitation** (workshops, prototypes)
2. **Early customer review** of requirements (multiple iterations before baseline)
3. **Change control process** (CCB approval for all changes)
4. **Requirements stability metric** (track change rate weekly)
5. **Impact analysis for all changes** (technical, schedule, cost, safety)
6. **Contingency buffer** (10% schedule buffer for requirements changes)

**Contingency Plan:**
1. **Negotiate change freeze** after requirements baseline
2. **Defer non-critical changes** to future release
3. **Escalate to customer** if change rate exceeds threshold
4. **Negotiate schedule extension** if critical changes required

**Owner:** Requirements Engineer (REQ), Project Manager (PM)  
**Mitigation Status:** In Progress  
**Next Review Date:** YYYY-MM-DD (weekly during requirements phase)

---

## 4. Risk Categories

### 4.1 Technical Risks

| Risk ID | Risk Title | Score | Status |
|---------|-----------|-------|--------|
| RISK-002 | MISRA C violations exceed budget | 6 | Active |
| RISK-003 | Coverage target not achieved | 6 | Active |
| RISK-005 | Complexity exceeds SIL limits | 4 | Active |
| RISK-009 | Integration interface mismatches | 4 | Active |

### 4.2 Schedule Risks

| Risk ID | Risk Title | Score | Status |
|---------|-----------|-------|--------|
| RISK-008 | Safety assessment delay (SIL 3-4) | 3 | Active |

### 4.3 Resource Risks

| Risk ID | Risk Title | Score | Status |
|---------|-----------|-------|--------|
| RISK-004 | Independent resources unavailable (SIL 3-4) | 3 | Active |
| RISK-007 | Static analysis tool license delay | 2 | Active |

### 4.4 Requirements/Scope Risks

| Risk ID | Risk Title | Score | Status |
|---------|-----------|-------|--------|
| RISK-006 | Requirements volatility | 4 | Active |

### 4.5 Quality Risks

| Risk ID | Risk Title | Score | Status |
|---------|-----------|-------|--------|
| RISK-010 | Defect backlog growth | 4 | Active |

---

## 5. Risk Summary

### 5.1 Risk Score Distribution

| Risk Level | Count | Risk IDs |
|-----------|-------|----------|
| Critical (9) | [N] | [List] |
| High (6-8) | [N] | RISK-002, RISK-003 |
| Medium (3-4) | [N] | RISK-004, RISK-005, RISK-006, RISK-009, RISK-010 |
| Low (1-2) | [N] | RISK-007 |

### 5.2 Risk Trend

| Month | Critical | High | Medium | Low | Total |
|-------|---------|------|--------|-----|-------|
| YYYY-MM | [N] | [N] | [N] | [N] | [N] |

**Trend Analysis:**
[Describe whether risks are increasing, decreasing, or stable]

---

## 6. Closed Risks

| Risk ID | Risk Title | Date Closed | Closure Reason |
|---------|-----------|-------------|----------------|
| [RISK-XXX] | [Risk title] | YYYY-MM-DD | [Mitigated / No longer applicable / Realized and resolved] |

---

## 7. Realized Risks (Issues)

| Risk ID | Risk Title | Date Realized | Impact | Resolution Status |
|---------|-----------|--------------|--------|------------------|
| [RISK-XXX] | [Risk title] | YYYY-MM-DD | [Actual impact] | [Open / Resolved] |

---

## EN 50128 References

- **Section 6.1:** Software Management and Organization
- **Section 6.7:** Risk management as part of software development

## EN 50126 RAMS References

- **Section 7.4:** Hazard and risk management
- **Annex C:** Risk assessment and management techniques

---

**Template Version:** 1.0  
**EN 50128:2011 Compliance:** Section 6.1, 6.7  
**Skill Owner:** Project Manager (`/pm`)

---

## Instructions for Use

1. **Continuous Risk Identification:** All team members should identify risks throughout the project
2. **Risk Review Frequency:**
   - Critical/High risks: Weekly
   - Medium risks: Bi-weekly
   - Low risks: Monthly
3. **Risk Status Updates:** Update risk status in every status meeting
4. **Escalation:** Critical risks (score 9) escalate to senior management immediately
5. **Risk Closure:** Close risks only when fully mitigated or no longer applicable
6. **Lessons Learned:** Document realized risks and their resolutions for future projects
