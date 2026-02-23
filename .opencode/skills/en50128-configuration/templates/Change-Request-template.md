# Change Request

**Document ID:** DOC-CR-YYYY-NNN  
**Project:** [Project Name]  
**System/Subsystem:** [System Name]  
**SIL Level:** [0 | 1 | 2 | 3 | 4]

---

## Document Control

| Version | Date | Author | Change Description | Status |
|---------|------|--------|-------------------|--------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft | Draft |

---

## Change Request Information

### CR Identification

| Field | Value |
|-------|-------|
| **CR Number** | CR-YYYY-NNN |
| **CR Title** | [Short descriptive title] |
| **Originator** | [Name, Role] |
| **Date Submitted** | YYYY-MM-DD |
| **Priority** | [Critical \| High \| Medium \| Low] |
| **Category** | [Defect \| Enhancement \| Documentation \| Other] |
| **Status** | [Submitted \| Under Review \| Approved \| Rejected \| Implemented \| Closed] |

---

## Change Description

### Problem/Opportunity Statement

[Describe the problem being addressed or opportunity being pursued]

**Current Situation:**
- [Describe current state]
- [Impact of current situation]

**Desired Situation:**
- [Describe desired state]
- [Expected benefits]

### Affected Configuration Items

| Configuration Item | Current Version | Document ID | Impact Level |
|-------------------|----------------|-------------|--------------|
| [CI Name] | [Version] | [DOC-XXX-YYYY-NNN] | [High \| Medium \| Low] |

**Impact Level Definitions:**
- **High:** Requires architecture/design changes, affects multiple components
- **Medium:** Requires module-level changes, affects specific components
- **Low:** Minor changes, documentation updates, no functional impact

---

## Change Analysis

### Technical Analysis

**Scope of Change:**
- [List affected modules/components]
- [List affected interfaces]
- [List affected requirements (with traceability IDs)]

**Technical Approach:**
```
[Describe proposed solution/implementation approach]
```

**Alternatives Considered:**
1. **Alternative 1:** [Description]
   - Pros: [List advantages]
   - Cons: [List disadvantages]
2. **Alternative 2:** [Description]
   - Pros: [List advantages]
   - Cons: [List disadvantages]

**Recommended Approach:** [Selected alternative with rationale]

### Safety Analysis (EN 50128 Section 6.4)

**Safety Impact Assessment:**
- [ ] No safety impact
- [ ] Potential safety impact - analysis required
- [ ] Known safety impact - mitigation required

**Hazard Analysis:**
| Hazard ID | Description | Risk Level | Mitigation |
|-----------|-------------|-----------|------------|
| [HAZ-NNN] | [Hazard description] | [SIL] | [Mitigation approach] |

**Safety Approval Required:** [Yes/No]

### Impact Analysis

**Requirements Impact:**
- New requirements: [Number]
- Modified requirements: [List requirement IDs]
- Deleted requirements: [List requirement IDs]

**Design Impact:**
- Architecture changes: [Yes/No - describe]
- Module design changes: [List affected modules]
- Interface changes: [List affected interfaces]

**Implementation Impact:**
- New source files: [Number]
- Modified source files: [List file names]
- Deleted source files: [List file names]
- Estimated LOC change: [+NNN/-NNN]

**Testing Impact:**
- New test cases required: [Number]
- Modified test cases: [Number]
- Regression testing scope: [Describe]

**Documentation Impact:**
| Document | Document ID | Change Required |
|----------|-------------|----------------|
| [Document Name] | [DOC-XXX-YYYY-NNN] | [Describe change] |

**Verification/Validation Impact:**
- [ ] Reverification required
- [ ] Revalidation required
- [ ] Re-assessment required (SIL 3-4)

---

## Resource Estimation

### Effort Estimate

| Activity | Estimated Effort (hours) | Resources Required |
|----------|------------------------|-------------------|
| Requirements update | [Hours] | [Role] |
| Design update | [Hours] | [Role] |
| Implementation | [Hours] | [Role] |
| Unit testing | [Hours] | [Role] |
| Integration testing | [Hours] | [Role] |
| Verification | [Hours] | [Role] |
| Validation | [Hours] | [Role] |
| Documentation update | [Hours] | [Role] |
| **Total** | **[Total Hours]** | - |

### Schedule Impact

**Estimated Duration:** [X weeks/months]

**Critical Path Impact:**
- [ ] No impact on critical path
- [ ] Impacts critical path - delay of [X days/weeks]

**Milestone Impact:**
- [List affected milestones with new dates]

### Cost Estimate

| Cost Category | Estimated Cost |
|---------------|----------------|
| Development effort | [Currency amount] |
| Testing effort | [Currency amount] |
| Verification effort | [Currency amount] |
| Documentation | [Currency amount] |
| Tools/equipment | [Currency amount] |
| **Total Estimated Cost** | **[Total]** |

---

## Risk Assessment

| Risk ID | Risk Description | Probability | Impact | Mitigation Strategy |
|---------|-----------------|------------|--------|-------------------|
| [RISK-NNN] | [Description] | [H/M/L] | [H/M/L] | [Mitigation approach] |

---

## Change Control Board Review

### CCB Meeting Information

**Meeting Date:** YYYY-MM-DD  
**CCB Members Present:**
- [Name, Role]
- [Name, Role]
- [Name, Role]

### CCB Decision

**Decision:** [Approved | Approved with Conditions | Rejected | Deferred]

**Conditions (if applicable):**
1. [Condition 1]
2. [Condition 2]

**Rejection Rationale (if applicable):**
[Explain why change was rejected]

**Deferral Rationale (if applicable):**
[Explain why change was deferred and when it will be reconsidered]

### CCB Approvals (SIL-Dependent)

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Configuration Manager** | [Name] | [Signature] | YYYY-MM-DD |
| **Project Manager** | [Name] | [Signature] | YYYY-MM-DD |
| **Software Manager** | [Name] | [Signature] | YYYY-MM-DD |
| **Designer** (if design impacted) | [Name] | [Signature] | YYYY-MM-DD |
| **Safety Engineer** (if safety impacted) | [Name] | [Signature] | YYYY-MM-DD |
| **Verifier** (SIL 2+, if verification impacted) | [Name] | [Signature] | YYYY-MM-DD |
| **Validator** (SIL 3-4, if validation impacted) | [Name] | [Signature] | YYYY-MM-DD |

**Independence Note (SIL 3-4):**
- Verifier SHALL NOT be Requirements Manager, Designer, Implementer, Integrator, or Tester
- Validator SHALL NOT report to Project Manager

---

## Implementation Plan

### Implementation Phases

**Phase 1: Requirements and Design**
- Start Date: YYYY-MM-DD
- End Date: YYYY-MM-DD
- Activities:
  - [ ] Update Software Requirements Specification
  - [ ] Update Software Design Specification
  - [ ] Update traceability matrices
  - [ ] Design review

**Phase 2: Implementation and Unit Testing**
- Start Date: YYYY-MM-DD
- End Date: YYYY-MM-DD
- Activities:
  - [ ] Implement code changes
  - [ ] MISRA C compliance check (SIL 2+)
  - [ ] Unit test implementation
  - [ ] Code review (QA)
  - [ ] Unit test execution

**Phase 3: Integration and Testing**
- Start Date: YYYY-MM-DD
- End Date: YYYY-MM-DD
- Activities:
  - [ ] Software integration
  - [ ] Integration testing
  - [ ] Regression testing
  - [ ] Coverage analysis (SIL-dependent)

**Phase 4: Verification and Validation**
- Start Date: YYYY-MM-DD
- End Date: YYYY-MM-DD
- Activities:
  - [ ] Static analysis (SIL 3-4)
  - [ ] Verification activities
  - [ ] Validation testing
  - [ ] Independent assessment (SIL 3-4)

**Phase 5: Documentation and Closure**
- Start Date: YYYY-MM-DD
- End Date: YYYY-MM-DD
- Activities:
  - [ ] Update all affected documentation
  - [ ] Configuration audit
  - [ ] Baseline update
  - [ ] Change closure

### Rollback Plan

**Rollback Criteria:**
- [Define conditions under which change should be rolled back]

**Rollback Procedure:**
1. [Step 1]
2. [Step 2]
3. [Restore baseline version [X.Y]]

---

## Implementation Tracking

### Implementation Status

| Work Item | Assigned To | Status | Completion Date |
|-----------|------------|--------|----------------|
| [Work item description] | [Name] | [Not Started \| In Progress \| Complete] | YYYY-MM-DD |

### Issues and Observations

| Issue ID | Description | Impact | Resolution | Status |
|----------|-------------|--------|------------|--------|
| [ISSUE-NNN] | [Description] | [H/M/L] | [Resolution approach] | [Open/Closed] |

---

## Change Closure

### Verification of Implementation

- [ ] All planned work items completed
- [ ] All affected configuration items updated
- [ ] All documentation updated
- [ ] Verification activities completed successfully
- [ ] Validation activities completed successfully (if required)
- [ ] Configuration audit passed (FCA if required)
- [ ] New baseline established
- [ ] Traceability updated

### Lessons Learned

**What went well:**
- [Observation 1]
- [Observation 2]

**What could be improved:**
- [Observation 1]
- [Observation 2]

**Recommendations for future changes:**
- [Recommendation 1]
- [Recommendation 2]

### Final Approval

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Configuration Manager** | [Name] | [Signature] | YYYY-MM-DD |
| **Project Manager** | [Name] | [Signature] | YYYY-MM-DD |

**Change Status:** [Closed]  
**Closure Date:** YYYY-MM-DD

---

## EN 50128 References

- **Section 6.6:** Software Configuration Management
- **Section 6.4:** Software Change Management
- **Table A.9:** Software Configuration Management techniques
- **Section 5.3.2.13:** Phase modification and change control

## EN 50126 RAMS References

- **Section 7.4:** Change management in RAMS lifecycle
- **Annex B:** Configuration management requirements

---

## Appendices

### Appendix A: Affected Requirements Traceability

| Requirement ID | Current Version | New Version | Change Description |
|---------------|----------------|-------------|-------------------|
| [REQ-NNN] | [X.Y] | [X.Y+1] | [Description] |

### Appendix B: Test Results Summary

[Attach test results or reference test report documents]

### Appendix C: Verification Evidence

[Attach verification reports or reference verification documents]

---

**Template Version:** 1.0  
**EN 50128:2011 Compliance:** Section 6.6, Table A.9  
**Skill Owner:** Configuration Manager (`/cm`)
