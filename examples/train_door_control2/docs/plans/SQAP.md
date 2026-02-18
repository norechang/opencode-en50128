# Software Quality Assurance Plan (SQAP)

## 1. Introduction
### 1.1 Purpose
Define quality assurance activities for the train_door_control2 project to ensure compliance with EN 50128:2011 requirements for SIL 3 railway software development. This plan establishes the quality assurance processes, responsibilities, standards, and activities necessary to deliver safe and reliable software.

### 1.2 Scope
- Software Component: Train Door Control System (train_door_control2)
- SIL Level: 3
- Development Phase: Full V-Model lifecycle (Requirements through Validation)
- QA Team: QA Manager (Jane Smith), QA Engineers (Bob Johnson, Alice Brown)

### 1.3 References
- EN 50128:2011 Railway applications - Communication, signalling and processing systems - Software for railway control and protection systems
- Software Requirements Specification (SRS) for train_door_control2
- Software Configuration Management Plan (SCMP) for train_door_control2
- Project Quality Plan for train_door_control2
- MISRA C:2012 Guidelines for the use of the C language in critical systems
- EN 50126:2017 Railway Applications - The Specification and Demonstration of Reliability, Availability, Maintainability and Safety (RAMS)

## 2. Quality Organization
### 2.1 QA Team
- QA Manager: Jane Smith
- QA Engineers: Bob Johnson, Alice Brown
- Independence: YES (QA team reports directly to Project Manager, separate from development team)

### 2.2 Responsibilities
- QA Manager: Overall quality oversight, audit approval, quality gate authorization, non-conformance escalation
- QA Engineers: Code reviews, design reviews, process audits, metrics collection, testing oversight
- Development Team: Quality compliance implementation, defect resolution, participation in reviews

## 3. Quality Standards
### 3.1 Coding Standards
- MISRA C:2012 (Mandatory for SIL 3)
- Project-specific coding guidelines for train door control logic
- Cyclomatic complexity limits: Maximum 10 for SIL 3
- No dynamic memory allocation (static allocation only)
- No recursion permitted
- Fixed-width integer types (uint8_t, uint16_t, etc.)

### 3.2 Documentation Standards
- EN 50128 required documents (SRS, SAS, SDS, SVP, SValP, etc.)
- Template compliance with EN 50128 Annex C Table C.1
- Mandatory traceability to requirements (SIL 3 requirement)
- Version control for all documents

### 3.3 Process Standards
- EN 50128 Section 5 V-Model software development lifecycle
- Change control procedures via Configuration Control Board (CCB)
- Configuration management (mandatory for all SIL levels)
- Independent verification and validation (mandatory for SIL 3)

## 4. Quality Activities
### 4.1 Code Reviews
- **Frequency**: All C code reviewed before integration into main branch
- **Participants**: Developer, Senior Developer (Reviewer), QA Engineer
- **Checklist**: MISRA C compliance, defensive programming, complexity limits, traceability
- **Exit Criteria**: Zero critical issues, all major issues resolved, traceability verified

### 4.2 Design Reviews
- **Frequency**: Architecture design (SAS), detailed design (SDS), interface designs
- **Participants**: Designer, Requirements Engineer, Safety Engineer, QA Engineer
- **Checklist**: Requirements traceability, complexity analysis, safety design, interface specifications
- **Exit Criteria**: Design approved by all participants, traceability complete, safety concerns addressed

### 4.3 Audits
- **Frequency**: Phase transitions, major milestones (every 2 weeks minimum)
- **Scope**: Process compliance, EN 50128 adherence, documentation completeness
- **Participants**: QA team, Project Manager, Independent Assessor (SIL 3)
- **Deliverable**: Audit report with findings, corrective action plans

### 4.4 Testing Oversight
- Review unit test plans and test cases for completeness
- Witness execution of critical safety-related tests
- Verify test coverage requirements met (100% statement, branch, condition for SIL 3)
- Approve test reports and coverage analysis results

## 5. Quality Metrics
### 5.1 Process Metrics
- Schedule adherence (planned vs actual phase completion)
- Defect detection rate (defects found per review/audit)
- Review effectiveness (defects found vs total defects)
- Non-conformance closure time

### 5.2 Product Metrics
- Cyclomatic complexity (maximum ≤ 10, average tracked)
- MISRA C compliance rate (target: 100%)
- Test coverage: 100% statement, 100% branch, 100% condition (SIL 3 mandatory)
- Defect density (defects per KLOC)
- Code review coverage (100% of code reviewed)

## 6. Non-Conformance Management
### 6.1 Detection
- Identified during code reviews, design reviews, audits, testing, static analysis
- Logged in non-conformance tracking system (GitHub Issues with NCR- prefix)

### 6.2 Resolution
- Root cause analysis performed for all non-conformances
- Corrective actions implemented and verified
- Preventive actions identified to avoid recurrence
- Process improvements documented and implemented

### 6.3 Tracking
- All non-conformances tracked to closure with NCR-YYYY-NNN format
- Monthly quality metrics report to management
- Escalation to CCB for critical safety-related issues

## 7. Quality Gates
### 7.1 Phase Exit Criteria
Each phase must meet SIL 3 quality criteria before proceeding:

**Requirements Phase**:
- [ ] All requirements reviewed and approved by QA
- [ ] Traceability matrix complete (SIL 3 mandatory)
- [ ] SIL levels assigned and justified
- [ ] Safety requirements identified and allocated

**Design Phase**:
- [ ] Architecture and detailed design reviewed by QA
- [ ] Cyclomatic complexity estimated ≤ 10
- [ ] Traceability to requirements complete (SIL 3 mandatory)
- [ ] Safety design patterns applied
- [ ] Static memory allocation strategy defined

**Implementation Phase**:
- [ ] All C code reviewed and approved
- [ ] MISRA C:2012 compliance verified (100%)
- [ ] Static allocation only (no malloc/free)
- [ ] Unit tests developed and pass
- [ ] Test coverage: 100% statement, branch, condition

**Integration Phase**:
- [ ] Component integration tested
- [ ] Interface testing completed
- [ ] Performance testing within limits
- [ ] Integration defects resolved

**Verification Phase**:
- [ ] Independent verification completed
- [ ] Static analysis passed (PC-lint/Cppcheck)
- [ ] Dynamic analysis completed
- [ ] Verification evidence collected

**Validation Phase**:
- [ ] Independent validation completed
- [ ] System testing on target hardware
- [ ] Operational scenarios validated
- [ ] Customer acceptance obtained

**Deployment**:
- [ ] All quality activities complete
- [ ] Documentation complete and approved
- [ ] Safety assessment completed (SIL 3)
- [ ] Release package configuration controlled

## 8. Tools
- Static analysis: PC-lint Plus (MISRA C), Cppcheck
- Complexity analysis: Lizard
- Coverage analysis: gcov/lcov (SIL 3: 100% statement/branch/condition)
- Code quality: Clang Static Analyzer
- Testing framework: Unity/CUnit
- Configuration management: Git
- Issue tracking: GitHub Issues
- Documentation: Markdown templates

## 9. Records
- Code review records (checklists and approvals)
- Design review records (meeting minutes and decisions)
- Audit reports (findings and corrective actions)
- Non-conformance reports (NCR-YYYY-NNN format)
- Quality metrics reports (monthly)
- Test reports and coverage analysis
- Meeting minutes for quality-related discussions

## 10. Approval
- QA Manager: _________________ Date: _______
- Project Manager: ____________ Date: _______
- Safety Manager: _____________ Date: _______