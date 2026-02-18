# Software Configuration Management Plan (SCMP)

**Project:** train_door_control2  
**Version:** 1.0  
**Date:** 2026-02-18  
**Configuration Manager:** Configuration Manager  
**Approved By:** Project Manager  

---

## 1. Introduction

### 1.1 Purpose
This Software Configuration Management Plan (SCMP) defines the configuration management processes and procedures for the train_door_control2 project, a SIL 3 railway software system. The purpose of this plan is to ensure that all configuration items are properly identified, controlled, and tracked throughout the software lifecycle in compliance with EN 50128:2011 Section 6.6.

### 1.2 Scope
This plan applies to all software development activities for the train_door_control2 project, including requirements specification, architecture design, implementation, testing, integration, verification, and validation. It covers all configuration items such as source code, documentation, test artifacts, build scripts, and tools.

### 1.3 Applicable Standards
- EN 50128:2011 Railway applications - Communication, signalling and processing systems - Software for railway control and protection systems (Section 6.6)
- EN 50126-1:2017 Railway Applications - The Specification and Demonstration of Reliability, Availability, Maintainability and Safety (RAMS)
- MISRA C:2012 Guidelines for the use of the C language in critical systems
- IEC 61508:2010 Functional safety of electrical/electronic/programmable electronic safety-related systems

### 1.4 Definitions and Abbreviations
- **CI:** Configuration Item
- **SCMP:** Software Configuration Management Plan
- **CCB:** Change Control Board
- **PCA:** Physical Configuration Audit
- **FCA:** Functional Configuration Audit
- **CR:** Change Request
- **SIL:** Safety Integrity Level
- **RTM:** Requirements Traceability Matrix

---

## 2. Configuration Management Organization

### 2.1 Roles and Responsibilities

**Configuration Manager:**
- Develop and maintain the SCMP
- Identify and track all configuration items
- Coordinate change control processes
- Conduct configuration audits (PCA, FCA)
- Maintain configuration status accounting
- Generate configuration status reports and metrics

**Change Control Board (CCB):**
- Membership: Project Manager (Chair), Configuration Manager, Safety Engineer, Technical Lead
- Evaluate change requests for safety impact, technical feasibility, and schedule impact
- Approve or reject change requests
- Meet weekly or as needed for urgent changes

**Project Manager:**
- Approve baseline releases
- Allocate resources for CM activities
- Review configuration status reports

**Development Team:**
- Submit change requests through the CM process
- Implement approved changes
- Provide information for impact analysis

### 2.2 CM Tools and Environment
- **Version Control:** Git with GitHub
- **CM Database:** Excel/CSV files for CI tracking and RTM
- **Build Automation:** Make with Jenkins CI/CD
- **Issue Tracking:** GitHub Issues
- **Documentation:** Markdown files in repository

---

## 3. Configuration Identification

### 3.1 Configuration Items (CIs)
The following types of CIs are managed:
- Source code files (`.c`, `.h`)
- Build scripts (`Makefile`, `CMakeLists.txt`)
- Documentation (SRS, SAS, SDS, test plans, reports)
- Test artifacts (test cases, test data, test results)
- Tools and compilers (with version numbers)
- Libraries and dependencies

### 3.2 Naming Conventions
All CIs follow the format: `CI-<TYPE>-<YEAR>-<SEQ>`
- **TYPE:** SRC (source), DOC (document), TEST (test), BUILD (build script)
- **YEAR:** Current year (e.g., 2026)
- **SEQ:** Sequential number (001, 002, etc.)

Examples:
- CI-SRC-2026-001: main.c
- CI-DOC-2026-001: SRS.md
- CI-TEST-2026-001: test_main.c

### 3.3 Version Numbering Scheme
Semantic versioning: `MAJOR.MINOR.PATCH`
- **MAJOR:** Incompatible changes
- **MINOR:** Backward-compatible new features
- **PATCH:** Backward-compatible bug fixes

### 3.4 Baseline Identification
Baselines follow: `baseline_SIL3_vX.Y.Z`
- Released on: 2026-02-18
- Next planned: baseline_SIL3_v1.1.0 (2026-04-01)

### 3.5 Document Control Procedures
All documents are stored in the repository under `docs/` with version control. Changes require CR approval and update the document header with version and date.

---

## 4. Configuration Control

### 4.1 Change Request Process
1. **Submission:** Developer submits CR with description, impact analysis, and affected CIs
2. **Evaluation:** Configuration Manager performs initial review
3. **Impact Analysis:** Designer and Safety Engineer assess technical and safety impact
4. **CCB Approval:** CCB evaluates and approves/rejects
5. **Implementation:** Developer implements change
6. **Reverification:** Tester and Verifier confirm requirements met
7. **Closure:** Configuration Manager updates baseline and closes CR

### 4.2 Change Control Board (CCB)
- **Membership:** Project Manager, Configuration Manager, Safety Engineer, Technical Lead
- **Frequency:** Weekly meetings, emergency meetings as needed
- **Approval Authority:** All changes require CCB approval for SIL 3

### 4.3 Branch Management Strategy
- **main:** Production releases only
- **develop:** Integration branch
- **feature/***: Feature development
- **release/***: Release preparation
- **hotfix/***: Emergency fixes

---

## 5. Configuration Status Accounting

### 5.1 CI Status Tracking
CI status states: Draft, Review, Approved, Released, Obsolete

### 5.2 Configuration Database
- Tool: Excel/CSV files in `docs/cm/`
- Retention: Project lifecycle + 10 years

### 5.3 Status Reporting
- **Monthly:** Configuration status report
- **Quarterly:** Metrics report (mandatory SIL 3)

### 5.4 Change History Tracking
All changes recorded in Git commit history and CR database.

---

## 6. Configuration Audits and Reviews

### 6.1 Physical Configuration Audit (PCA)
- **Frequency:** Before each baseline release
- **Checklist:** Appendix A

### 6.2 Functional Configuration Audit (FCA)
- **Frequency:** Before each baseline release
- **Checklist:** Appendix B

### 6.3 Periodic Reviews
- CM process review: Quarterly
- Tool audits: Annually

### 6.4 Audit Reporting
Reports to Project Manager and Quality Assurance.

---

## 7. Interface Control and Third-Party Management

### 7.1 Interface Identification
- Software interfaces: Door control API
- Hardware interfaces: Sensor inputs, actuator outputs
- External systems: Train control system

### 7.2 Interface Change Control
All interface changes require CCB approval and impact analysis.

### 7.3 Third-Party Component Management
- Vendor: None (all custom development)
- Licenses: MIT for any open-source components

---

## 8. Build and Release Management

### 8.1 Build Procedures
- Automated build using Make
- Build verification: Unit tests pass, no compilation errors

### 8.2 Release Criteria
- All tests passed (100% coverage SIL 3)
- PCA and FCA passed
- Documentation approved
- Traceability verified

### 8.3 Deployment Configuration
- Target: Embedded railway controller
- Installation: Via secure update mechanism

### 8.4 Rollback Procedures
Rollback to previous baseline within 30 minutes.

---

## 9. Traceability Management (MANDATORY SIL 3-4)

### 9.1 Traceability Requirements
- Requirements to design: 100%
- Design to code: 100%
- Code to tests: 100%
- Bi-directional verified

### 9.2 Traceability Matrix Maintenance
- Tool: CSV file `docs/traceability/rtm.csv`
- Update: Each CR closure
- Verification: Before baseline release

---

## 10. Data Recording and Analysis (MANDATORY SIL 3-4)

### 10.1 Metrics Collection
- Change request metrics
- Defect metrics
- Audit metrics
- Baseline metrics

### 10.2 Analysis and Reporting
- Monthly metrics reports
- Quarterly trend analysis

---

## 11. Training Requirements

### 11.1 CM Tool Training
- Git version control
- Build automation
- Issue tracking

### 11.2 Process Training
- Change request process
- Audit procedures
- Baseline management

### 11.3 Role-Specific Training
- Configuration Manager: EN 50128 CM requirements
- CCB members: Change evaluation

---

## Appendices

### Appendix A: Physical Configuration Audit (PCA) Checklist

- [ ] All CIs listed in baseline manifest present
- [ ] CI version numbers match manifest
- [ ] File checksums match recorded values
- [ ] Build reproducible from baseline
- [ ] Source files have correct version headers
- [ ] Tool versions recorded
- [ ] No unauthorized files in baseline
- [ ] Archive and retrieval procedures tested

### Appendix B: Functional Configuration Audit (FCA) Checklist

- [ ] All requirements traced to design (100%)
- [ ] All design elements traced to code (100%)
- [ ] All code traced to tests (100%)
- [ ] All tests passed
- [ ] Coverage requirements met (Statement 100%, Branch 100%, Condition 100% SIL 3)
- [ ] All defects resolved
- [ ] All documents approved
- [ ] MISRA C compliance verified
- [ ] Static analysis passed

### Appendix C: Change Request Template

**Change Request: CR-XXXX**  
**Title:** [Brief description]  
**Submitted By:** [Name]  
**Date:** [YYYY-MM-DD]  
**Priority:** [Critical/High/Medium/Low]  
**SIL Level:** 3  

**Affected CIs:**  
- [List CIs]  

**Description:**  
[Detailed description]  

**Impact Analysis:**  
[Technical, safety, schedule impact]  

**Reverification Required:**  
[Unit tests, static analysis, etc.]  

**Approval:** [PM Signature]  
**Implementation:** [IMP Signature]  
**Verification:** [VER Signature]  
**Closure Date:** [YYYY-MM-DD]

### Appendix D: Baseline Manifest Template

Baseline Manifest: baseline_SIL3_vX.Y.Z  
Created: [Date]  
Baseline Status: RELEASED  
SIL Level: 3  
Configuration Manager: [Name]  

**Source Files:**  
CI-SRC-2026-XXX [Name] [Version] [SHA256] [Status]  

**Documentation:**  
CI-DOC-2026-XXX [Name] [Version] [SHA256] [Status]  

**Test Artifacts:**  
CI-TEST-2026-XXX [Name] [Version] [SHA256] [Status]  

**Traceability Status:**  
Requirements to Design: 100% traced  
Design to Code: 100% traced  
Code to Tests: 100% traced  

**Audits:**  
PCA: PASSED [Date]  
FCA: PASSED [Date]

### Appendix E: Configuration Status Report Template

**Configuration Status Report**  
**Month:** [Month Year]  
**Baseline:** [Current baseline]  

**Summary:**  
- Total CIs: [Number]  
- Released: [Number]  
- Under Review: [Number]  

**Change Requests:**  
- Submitted: [Number]  
- Approved: [Number]  
- Closed: [Number]  

**Audits:**  
- Last PCA: [Date] (PASS/FAIL)  
- Last FCA: [Date] (PASS/FAIL)