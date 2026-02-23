# Configuration Audit Report

**Document ID:** DOC-CAR-YYYY-NNN  
**Project:** [Project Name]  
**System/Subsystem:** [System Name]  
**SIL Level:** [0 | 1 | 2 | 3 | 4]

---

## Document Control

| Version | Date | Author | Change Description | Status |
|---------|------|--------|-------------------|--------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft | Draft |

---

## Approvals (SIL-Dependent)

| Role | Name | Signature | Date | SIL Requirement |
|------|------|-----------|------|----------------|
| **Configuration Manager** | [Name] | [Signature] | YYYY-MM-DD | All SILs |
| **Project Manager** | [Name] | [Signature] | YYYY-MM-DD | All SILs |
| **Quality Assurance** | [Name] | [Signature] | YYYY-MM-DD | SIL 1+ |
| **Independent Verifier** | [Name] | [Signature] | YYYY-MM-DD | SIL 3-4 |
| **Assessor** | [Name] | [Signature] | YYYY-MM-DD | SIL 3-4 |

**Independence Note (SIL 3-4):**
- Verifier SHALL NOT be Requirements Manager, Designer, Implementer, Integrator, or Tester
- Validator SHALL NOT report to Project Manager
- Assessor SHALL be independent of development organization

---

## Executive Summary

**Audit Type:** [Physical Configuration Audit (PCA) | Functional Configuration Audit (FCA) | Internal Configuration Audit | Baseline Audit]

**Audit Date:** YYYY-MM-DD  
**Audit Location:** [Location]  
**Baseline/Release Audited:** [Baseline ID or Release version]

**Overall Result:** [Pass | Pass with Observations | Fail]

**Key Findings:**
- [Summary finding 1]
- [Summary finding 2]
- [Summary finding 3]

**Critical Issues:** [Number]  
**Major Issues:** [Number]  
**Minor Issues:** [Number]  
**Observations:** [Number]

---

## 1. Audit Information

### 1.1 Audit Identification

| Field | Value |
|-------|-------|
| **Audit ID** | AUDIT-YYYY-NNN |
| **Audit Type** | [PCA \| FCA \| Internal \| Baseline] |
| **Audit Objective** | [Describe audit purpose and objectives] |
| **Baseline/Release** | [Version X.Y or Baseline-YYYY-MM-DD] |
| **Configuration Items Audited** | [Number] |
| **Audit Start Date** | YYYY-MM-DD |
| **Audit End Date** | YYYY-MM-DD |
| **Audit Duration** | [X days] |

### 1.2 Audit Team

| Name | Role | Organization | Independence Status |
|------|------|--------------|-------------------|
| [Name] | Lead Auditor | [Org] | [Independent / Not Applicable] |
| [Name] | Configuration Manager | [Org] | N/A |
| [Name] | Technical Auditor | [Org] | [Independent / Not Applicable] |
| [Name] | Quality Auditor | [Org] | [Independent / Not Applicable] |

**Independence Verification (SIL 3-4):**
- [ ] Lead Auditor is independent of development team
- [ ] No conflicts of interest identified
- [ ] Independence documented and approved

### 1.3 Audit Scope

**Configuration Items Included:**
- [ ] Software Requirements Specification (SRS)
- [ ] Software Architecture Specification (SAS)
- [ ] Software Design Specification (SDS)
- [ ] Source code (all modules)
- [ ] Test specifications and reports
- [ ] Verification reports
- [ ] Validation reports
- [ ] Safety documentation (Hazard Log, FMEA, FTA, Safety Case)
- [ ] Planning documents (SQAP, SCMP, SVP, SVaP)
- [ ] Interface specifications
- [ ] Build scripts and makefiles
- [ ] Configuration management database
- [ ] Change requests and records

**Baseline Information:**
- **Baseline ID:** [Baseline-YYYY-MM-DD or Version X.Y]
- **Baseline Date:** YYYY-MM-DD
- **Baseline Status:** [Draft | Released | Archived]
- **Previous Baseline:** [Previous baseline ID]

---

## 2. Audit Criteria

### 2.1 EN 50128 Requirements (Section 6.6)

**Configuration Management Requirements:**
- [ ] Configuration identification complete
- [ ] Configuration control procedures followed
- [ ] Configuration status accounting accurate
- [ ] Configuration audits performed
- [ ] All configuration items under version control

**SIL-Specific Requirements:**
- **SIL 0:** Basic configuration management
- **SIL 1-2:** Formal configuration management with traceability
- **SIL 3-4:** Mandatory traceability, data recording, independent audits

### 2.2 Audit Checklist

The following checklist items were evaluated during the audit:

#### Configuration Identification
- [ ] All configuration items uniquely identified
- [ ] Configuration item naming conventions followed (DOC-XXX-YYYY-NNN)
- [ ] Configuration items registered in CM database
- [ ] Version numbering scheme consistently applied
- [ ] Configuration item relationships documented

#### Configuration Control
- [ ] All changes processed through Change Control Board (CCB)
- [ ] Change requests properly documented
- [ ] Change impact analysis performed for all changes
- [ ] Change approvals obtained (SIL-appropriate)
- [ ] Change implementation tracking maintained
- [ ] No unauthorized changes detected

#### Version Control
- [ ] All configuration items under version control (Git/SVN)
- [ ] Version control repository structure correct
- [ ] Commit messages follow conventions
- [ ] Branch management policy followed
- [ ] Tag/release management correct
- [ ] No uncommitted changes in baseline

#### Baselines
- [ ] Baseline definition complete
- [ ] Baseline contents documented
- [ ] Baseline approval obtained
- [ ] Baseline archived and retrievable
- [ ] Baseline changes properly controlled
- [ ] Baseline traceability maintained

#### Traceability (Mandatory SIL 3-4)
- [ ] Requirements traceability complete (forward and backward)
- [ ] Design traceability to requirements
- [ ] Code traceability to design
- [ ] Test traceability to requirements
- [ ] Traceability matrix up-to-date
- [ ] No orphaned requirements or design elements

#### Document Control
- [ ] All documents follow template structure
- [ ] Document IDs assigned correctly
- [ ] Version control tables complete
- [ ] Approval tables complete with SIL-appropriate roles
- [ ] Document status correct (Draft/Released/Archived)
- [ ] Document references correct and up-to-date

#### Physical Configuration (PCA)
- [ ] Delivered items match baseline definition
- [ ] Source code matches repository baseline
- [ ] Build artifacts reproducible from source
- [ ] Documentation matches code version
- [ ] Installation media verified
- [ ] Release notes accurate and complete

#### Functional Configuration (FCA)
- [ ] All requirements implemented
- [ ] All tests executed successfully
- [ ] Coverage criteria met (SIL-dependent)
- [ ] Verification activities complete
- [ ] Validation activities complete (SIL 3-4)
- [ ] Defects resolved or documented

---

## 3. Audit Findings

### 3.1 Configuration Item Verification

#### 3.1.1 Planning Documents

| Document | Document ID | Expected Version | Actual Version | Status | Issues |
|----------|-------------|-----------------|----------------|--------|--------|
| Software Quality Assurance Plan | DOC-SQAP-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |
| Software Configuration Management Plan | DOC-SCMP-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |
| Software Verification Plan | DOC-SVP-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |
| Software Validation Plan | DOC-SVaP-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |

#### 3.1.2 Requirements Documents

| Document | Document ID | Expected Version | Actual Version | Status | Issues |
|----------|-------------|-----------------|----------------|--------|--------|
| Software Requirements Specification | DOC-SRS-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |
| Requirements Traceability Matrix | (Embedded in SRS) | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |

#### 3.1.3 Design Documents

| Document | Document ID | Expected Version | Actual Version | Status | Issues |
|----------|-------------|-----------------|----------------|--------|--------|
| Software Architecture Specification | DOC-SAS-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |
| Software Design Specification | DOC-SDS-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |
| Software Interface Specifications | DOC-SIS-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |

#### 3.1.4 Source Code

| Module/File | Expected Version | Actual Version | Repository Tag | Status | Issues |
|-------------|-----------------|----------------|----------------|--------|--------|
| [module.c] | [Git commit hash] | [Actual hash] | [tag] | [Pass/Fail] | [Issue description] |
| [module.h] | [Git commit hash] | [Actual hash] | [tag] | [Pass/Fail] | [Issue description] |

**Source Code Statistics:**
- Total source files: [Number]
- Total lines of code: [Number]
- MISRA C violations (SIL 2+): [Number mandatory violations - MUST be 0 for SIL 2+]
- Cyclomatic complexity: Max [Number] (Limit: ≤10 SIL 3-4, ≤15 SIL 2)

#### 3.1.5 Test Documents

| Document | Document ID | Expected Version | Actual Version | Status | Issues |
|----------|-------------|-----------------|----------------|--------|--------|
| Component Test Specification | DOC-CTS-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |
| Component Test Report | DOC-CTR-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |
| Integration Test Specification | DOC-ITS-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |
| Integration Test Report | DOC-ITR-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |
| Overall Software Test Specification | DOC-OSTS-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |
| Overall Software Test Report | DOC-OSTR-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |

**Test Coverage (SIL-Dependent):**
- Statement coverage: [X%] (SIL 3-4 requirement: 100%)
- Branch coverage: [X%] (SIL 2+ requirement: 100%)
- Condition coverage: [X%] (SIL 3-4 requirement: 100%)

#### 3.1.6 Verification and Validation Documents

| Document | Document ID | Expected Version | Actual Version | Status | Issues |
|----------|-------------|-----------------|----------------|--------|--------|
| Software Verification Report | DOC-SVR-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |
| Software Validation Report | DOC-SVaR-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |
| Assessment Report (SIL 3-4) | DOC-AR-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |

#### 3.1.7 Safety Documents

| Document | Document ID | Expected Version | Actual Version | Status | Issues |
|----------|-------------|-----------------|----------------|--------|--------|
| Hazard Log | DOC-HL-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |
| FMEA | DOC-FMEA-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |
| FTA | DOC-FTA-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |
| Safety Case | DOC-SC-YYYY-NNN | [X.Y] | [X.Y] | [Pass/Fail] | [Issue description] |

### 3.2 Configuration Control Verification

#### 3.2.1 Change Control Review

**Change Requests Processed Since Last Audit:** [Number]

| CR ID | Title | Status | CCB Approval | Implementation Verified | Issues |
|-------|-------|--------|--------------|------------------------|--------|
| CR-YYYY-NNN | [Title] | [Status] | [Yes/No] | [Yes/No] | [Issue description] |

**Findings:**
- [ ] All changes processed through CCB
- [ ] All changes have proper approvals
- [ ] All changes properly implemented
- [ ] No unauthorized changes detected
- [ ] Change traceability maintained

#### 3.2.2 Version Control Review

**Repository Information:**
- Repository type: [Git | SVN | Other]
- Repository URL: [URL]
- Baseline tag: [tag-name]
- Baseline commit: [commit-hash]

**Findings:**
- [ ] All configuration items under version control
- [ ] Commit history clean and complete
- [ ] Branching strategy followed
- [ ] No uncommitted changes in baseline
- [ ] Repository tags correct

#### 3.2.3 Baseline Integrity

**Baseline:** [Baseline-YYYY-MM-DD or Version X.Y]

**Baseline Verification:**
- [ ] Baseline definition document exists
- [ ] Baseline contents match CM database
- [ ] Baseline archived and retrievable
- [ ] Baseline build reproducible
- [ ] Baseline checksums verified (MD5/SHA-256)

**Baseline Checksums:**
| File/Artifact | Expected Checksum | Actual Checksum | Status |
|---------------|------------------|-----------------|--------|
| [artifact.bin] | [checksum] | [checksum] | [Match/Mismatch] |

### 3.3 Traceability Verification (Mandatory SIL 3-4)

#### 3.3.1 Requirements Traceability

**Total Requirements:** [Number]

**Traceability Status:**
- Requirements with design traceability: [Number / Total] ([X%])
- Requirements with code traceability: [Number / Total] ([X%])
- Requirements with test traceability: [Number / Total] ([X%])
- Orphaned requirements: [Number] (MUST be 0 for SIL 3-4)

**Orphaned Requirements (if any):**
| Requirement ID | Title | Issue |
|---------------|-------|-------|
| [REQ-NNN] | [Title] | [No design/code/test traceability] |

#### 3.3.2 Backward Traceability

**Test Cases Without Requirement Traceability:** [Number] (MUST be 0 for SIL 3-4)

| Test Case ID | Issue |
|--------------|-------|
| [TC-NNN] | No requirement traceability |

### 3.4 Document Control Review

**Total Documents Audited:** [Number]

**Document Control Findings:**
- Documents following template structure: [Number / Total] ([X%])
- Documents with correct ID format: [Number / Total] ([X%])
- Documents with complete version control tables: [Number / Total] ([X%])
- Documents with complete approval tables: [Number / Total] ([X%])
- Documents with SIL-appropriate approvals: [Number / Total] ([X%])

**Non-Conformances:**
| Document ID | Issue | Severity |
|-------------|-------|----------|
| [DOC-XXX-YYYY-NNN] | [Issue description] | [Critical/Major/Minor] |

---

## 4. Issues and Non-Conformances

### 4.1 Critical Issues

**Definition:** Issues that violate EN 50128 mandatory requirements or present safety risks. MUST be resolved before release.

| Issue ID | Description | Affected CI | EN 50128 Reference | Resolution Required |
|----------|-------------|-------------|-------------------|-------------------|
| CAR-CRIT-NNN | [Description] | [CI name] | [Section X.Y] | [Resolution action] |

### 4.2 Major Issues

**Definition:** Issues that violate highly recommended practices or significantly impact quality. SHOULD be resolved before release.

| Issue ID | Description | Affected CI | EN 50128 Reference | Resolution Required |
|----------|-------------|-------------|-------------------|-------------------|
| CAR-MAJ-NNN | [Description] | [CI name] | [Section X.Y] | [Resolution action] |

### 4.3 Minor Issues

**Definition:** Issues that violate recommended practices but do not impact safety or quality. MAY be deferred to future release.

| Issue ID | Description | Affected CI | EN 50128 Reference | Resolution Recommended |
|----------|-------------|-------------|-------------------|----------------------|
| CAR-MIN-NNN | [Description] | [CI name] | [Section X.Y] | [Resolution action] |

### 4.4 Observations

**Definition:** Areas for improvement that do not constitute non-conformances.

| Observation ID | Description | Recommendation |
|---------------|-------------|----------------|
| CAR-OBS-NNN | [Description] | [Recommendation] |

---

## 5. Audit Conclusions

### 5.1 Overall Assessment

**Audit Result:** [Pass | Pass with Observations | Fail]

**Summary:**
[Provide overall assessment of configuration management state, baseline integrity, and compliance with EN 50128 requirements]

**Compliance Assessment:**
- EN 50128 Section 6.6 (Configuration Management): [Compliant | Not Compliant]
- SIL-specific requirements: [Compliant | Not Compliant]
- Traceability requirements (SIL 3-4): [Compliant | Not Compliant]

### 5.2 Recommendations

1. **Immediate Actions Required:**
   - [Action 1 - address critical issues]
   - [Action 2 - address critical issues]

2. **Short-term Actions (before next baseline):**
   - [Action 1 - address major issues]
   - [Action 2 - address major issues]

3. **Long-term Improvements:**
   - [Improvement 1 - process improvements]
   - [Improvement 2 - tool improvements]

### 5.3 Release Readiness (if applicable)

**Release Approval:** [Approved | Approved with Conditions | Not Approved]

**Conditions for Approval (if applicable):**
1. [Condition 1]
2. [Condition 2]

**Release Blocking Issues:**
| Issue ID | Description | Resolution Status |
|----------|-------------|------------------|
| [CAR-CRIT-NNN] | [Description] | [Open/Resolved] |

---

## 6. Follow-Up Actions

### 6.1 Corrective Action Plan

| Issue ID | Corrective Action | Responsible | Target Date | Status |
|----------|------------------|-------------|-------------|--------|
| [CAR-XXX-NNN] | [Action description] | [Name] | YYYY-MM-DD | [Open/In Progress/Closed] |

### 6.2 Next Audit

**Next Audit Type:** [PCA | FCA | Internal | Baseline]  
**Planned Date:** YYYY-MM-DD  
**Focus Areas:**
- [Focus area 1]
- [Focus area 2]

---

## EN 50128 References

- **Section 6.6:** Software Configuration Management
- **Table A.9:** Software Quality Assurance techniques (includes Configuration Management)
- **Section 5.3.2.5:** Configuration management activities during phases
- **Annex C Table C.1:** Document control summary

## EN 50126 RAMS References

- **Section 8:** Configuration management in RAMS lifecycle
- **Annex B:** Configuration management requirements

---

## Appendices

### Appendix A: Audit Checklist (Complete)

[Attach complete audit checklist with all items marked]

### Appendix B: Configuration Item List

[Attach complete list of all configuration items audited]

### Appendix C: Traceability Matrix Review

[Attach traceability matrix or reference document]

### Appendix D: Evidence

[Attach evidence collected during audit: screenshots, logs, checksums, etc.]

---

**Template Version:** 1.0  
**EN 50128:2011 Compliance:** Section 6.6, Table A.9  
**Skill Owner:** Configuration Manager (`/cm`)
