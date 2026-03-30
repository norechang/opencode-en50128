# Project Plan - Train Door Control System

**Project ID:** TDC-2026  
**Project Name:** Train Door Control System (train_door_control2)  
**SIL Level:** 3  
**Version:** 1.0  
**Date:** 2026-02-18  

---

## 1. Executive Summary

The Train Door Control System is a safety-critical railway software system responsible for controlling passenger door operations on high-speed trains. This SIL 3 system must achieve the highest safety integrity level to prevent hazardous failures that could result in passenger injury or system malfunction.

The project will develop software compliant with EN 50128:2011, using the V-Model lifecycle with strict phase gate enforcement. The system will implement door control logic, safety interlocks, and diagnostic functions.

---

## 2. Project Objectives

### 2.1 Primary Objectives
- Develop SIL 3 compliant train door control software
- Achieve 100% statement, branch, and condition coverage
- Implement MISRA C:2012 coding standards
- Obtain independent validation and assessment approval
- Deploy to operational railway systems

### 2.2 Success Criteria
- All EN 50128 phase gates passed
- Independent Validator approval obtained
- Safety Authority certification received
- System deployed and operational by target date

---

## 3. Scope and Deliverables

### 3.1 In Scope
- Software Requirements Specification (SRS)
- Software Architecture Specification (SAS)
- Software Design Specification (SDS)
- C code implementation with MISRA C compliance
- Unit, integration, and system testing
- Verification and validation reports
- Independent assessment

### 3.2 Out of Scope
- Hardware design and implementation
- Mechanical door mechanisms
- Train network integration (interfaces only)
- Maintenance and support post-deployment

### 3.3 Key Deliverables
- Software Source Code and Documentation
- Test Reports and Coverage Analysis
- Verification and Validation Reports
- Safety Case and Assessment Report
- Deployment Package

---

## 4. Lifecycle Model

### 4.1 Selected Model
**V-Model** (EN 50128 Section 5.3.2.1 - MANDATORY for SIL 3)

### 4.2 Phase Structure
1. **Planning** (Phase 1): Establish quality and configuration plans
2. **Requirements** (Phase 2): Define software requirements
3. **Architecture & Design** (Phase 3): Design system architecture
4. **Implementation & Testing** (Phase 4): Code and unit test
5. **Integration** (Phase 5): Integrate components
6. **Validation** (Phase 6): System validation
7. **Assessment** (Phase 7): Independent assessment (SIL 3)
8. **Deployment** (Phase 8): Release and deployment

### 4.3 Phase Gates
- **SIL 3**: Strict gatekeeper mode
- All criteria must be satisfied before phase transition
- COD enforces gate compliance

### 4.4 Iterations
- Feedback loops between validation and earlier phases
- Change control process for iterations
- Traceability maintained across iterations

---

## 5. Schedule and Milestones

### 5.1 Overall Timeline
- **Start Date:** 2026-02-18
- **Target Completion:** 2027-02-18 (12 months)
- **Critical Path:** Requirements → Design → Implementation → Validation

### 5.2 Phase Milestones

| Phase | Start Date | End Date | Duration | Key Milestones |
|-------|------------|----------|----------|----------------|
| Planning | 2026-02-18 | 2026-03-18 | 1 month | SQAP, SCMP, SVP, SVaP approved |
| Requirements | 2026-03-19 | 2026-05-19 | 2 months | SRS approved, RTM complete |
| Architecture & Design | 2026-05-20 | 2026-08-20 | 3 months | SAS, SDS approved |
| Implementation & Testing | 2026-08-21 | 2026-11-21 | 3 months | Code complete, unit tests passed |
| Integration | 2026-11-22 | 2026-12-22 | 1 month | Integration tests passed |
| Validation | 2026-12-23 | 2027-01-23 | 1 month | System validation complete |
| Assessment | 2027-01-24 | 2027-02-07 | 2 weeks | Assessment report approved |
| Deployment | 2027-02-08 | 2027-02-18 | 1 week | System deployed |

### 5.3 Dependencies
- Phase transitions require COD gate approval
- Independent Validator availability
- Safety Authority review cycles

---

## 6. Resource Allocation

### 6.1 Team Resources

| Role | FTE | Key Responsibilities | Start Date | End Date |
|------|-----|----------------------|------------|----------|
| Project Manager | 1.0 | Overall coordination | 2026-02-18 | 2027-02-18 |
| Requirements Engineer | 0.8 | Requirements development | 2026-03-01 | 2026-05-31 |
| Designer | 1.0 | Architecture and design | 2026-05-01 | 2026-08-31 |
| Implementer | 1.0 | Code implementation | 2026-08-01 | 2026-11-30 |
| Tester | 0.8 | Testing activities | 2026-08-01 | 2027-01-31 |
| Integrator | 0.6 | Integration activities | 2026-11-01 | 2026-12-31 |
| Verifier | 0.7 | Verification activities | 2026-08-01 | 2027-01-31 |
| Safety Engineer | 0.5 | Safety analysis | 2026-03-01 | 2027-02-18 |
| Quality Assurance | 0.5 | QA activities | 2026-02-18 | 2027-02-18 |
| Configuration Manager | 0.5 | CM activities | 2026-02-18 | 2027-02-18 |
| Validator | 0.3 | Independent validation | 2026-12-01 | 2027-02-18 |
| Assessor | 0.2 | Independent assessment | 2027-01-15 | 2027-02-07 |

**Total FTE:** 8.1

### 6.2 Tools and Environment
- Development: C compiler, MISRA C checker, static analysis tools
- Testing: Unit test framework, coverage tools
- Configuration: Git version control, document management
- Verification: PC-lint, Cppcheck, formal verification tools

---

## 7. Risk Management

### 7.1 Key Risks

| Risk ID | Description | Probability | Impact | Mitigation |
|---------|-------------|-------------|--------|------------|
| RISK-001 | Requirements changes during development | High | High | Strict change control, early stakeholder agreement |
| RISK-002 | SIL 3 compliance challenges | Medium | High | Dedicated safety engineering, independent verification |
| RISK-003 | Validator availability delays | Medium | Medium | Early engagement, backup validator identified |
| RISK-004 | Code complexity exceeding limits | Medium | High | Design reviews, complexity monitoring |
| RISK-005 | Testing coverage gaps | Low | High | Coverage analysis, boundary testing |

### 7.2 Risk Monitoring
- Weekly risk reviews during PM meetings
- Risk register updated monthly
- Escalation to Safety Authority for critical risks

---

## 8. Quality Assurance

### 8.1 Quality Objectives
- MISRA C:2012 compliance (100%)
- Test coverage: 100% statement, branch, condition
- Zero critical defects in validation
- All phase gates passed first time

### 8.2 Quality Activities
- Code reviews for all code
- Static analysis on all builds
- Independent verification and validation
- Regular quality audits

---

## 9. Communication Plan

### 9.1 Internal Communications
- Weekly team meetings
- Daily stand-ups during development phases
- Email distribution lists
- Document sharing via version control

### 9.2 External Communications
- Monthly progress reports to Safety Authority
- Stakeholder reviews at phase gates
- Validator updates weekly during validation
- Customer demonstrations quarterly

---

## 10. Change Control

### 10.1 Change Control Board
- Chaired by Project Manager
- Meets bi-weekly
- Reviews all change requests
- Approves changes per EN 50128 Section 6.6

### 10.2 Change Process
- Submit changes via Configuration Manager
- Impact assessment required
- Safety changes require Validator approval
- All changes traced to requirements

---

## 11. Dependencies and Assumptions

### 11.1 Assumptions
- System requirements available by project start
- Validator and Assessor available per schedule
- Safety Authority review cycles as planned
- Development tools qualified and available

### 11.2 Dependencies
- Hardware interface specifications available
- Safety requirements defined by system level
- Tool qualification complete before implementation

---

## 12. Approvals

**Prepared By:** Sarah Johnson (Project Manager)  
**Approved By:** Lifecycle Coordinator (COD)  
**Date:** 2026-02-18  

---

**Document ID:** PLAN-001  
**Version:** 1.0  
**Effective Date:** 2026-02-18