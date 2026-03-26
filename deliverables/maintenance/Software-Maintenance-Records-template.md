# Software Maintenance Records

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 §9.2.4.6(a)  
**ANNEX C ITEM**: #43

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SMR-[YYYY]-[NNN] |
| **Version** | [MAJOR.MINOR] |
| **Date** | [YYYY-MM-DD] |
| **Project** | [ProjectName] |
| **SIL Level** | [0 \| 1 \| 2 \| 3 \| 4] |
| **Author** | [AuthorName], CM |
| **Reviewer** | [ReviewerName], QUA |
| **Status** | [Active — updated continuously] |

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 1.0 | YYYY-MM-DD | [AuthorName] | Initial version | [ApproverName] |

---

## 1. Purpose

This document constitutes the Software Maintenance Records for [Project Name], providing a complete and auditable history of all maintenance activities performed on the software throughout its operational lifetime, per EN 50128:2011 §9.2.4.6(a).

---

## 2. Maintenance Activity Log

### 2.1 Summary Table

| Record ID | Date | Type | Change Request | Component | Summary | Result |
|-----------|------|------|---------------|-----------|---------|--------|
| SMR-001 | YYYY-MM-DD | [Corrective/Adaptive/Preventive] | CR-YYYY-NNN | [Component] | [Summary] | [Closed/Ongoing] |

---

## 3. Maintenance Record: SMR-001

### 3.1 Activity Identification

| Field | Value |
|-------|-------|
| **Record ID** | SMR-001 |
| **Change Request** | CR-YYYY-NNN |
| **Maintenance Type** | [Corrective / Adaptive / Preventive] |
| **Date Started** | [YYYY-MM-DD] |
| **Date Completed** | [YYYY-MM-DD] |
| **Responsible Engineer** | [Name] |

### 3.2 Summary of Change

[Brief description of what was changed and why]

### 3.3 Components Modified

| Component | Previous Version | New Version | CI Baseline |
|-----------|-----------------|------------|-------------|
| [Component] | [Version] | [Version] | [Baseline ID] |

### 3.4 Verification Evidence

| Evidence | Document ID | Result |
|----------|-------------|--------|
| Maintenance Verification Report | DOC-044-SMVR-YYYY-NNN | [Pass/Fail] |
| Test report | [ID] | [Pass/Fail] |
| Change record closed | CR-YYYY-NNN | [Closed] |

### 3.5 Configuration Baseline

**New Baseline Created:** [Baseline ID]  
**Baseline Date:** [YYYY-MM-DD]  
**Baseline Contents:** [Description]

---

## 4. Outstanding Maintenance Items

| CR ID | Priority | Description | Target Version | Status |
|-------|----------|-------------|---------------|--------|
| [CR ID] | [Priority] | [Description] | [Version] | [Status] |

---

## 5. Maintenance Metrics

| Metric | Value | Period |
|--------|-------|--------|
| Total CRs raised | [Count] | [Period] |
| Safety-critical CRs | [Count] | [Period] |
| Average resolution time | [Days] | [Period] |
| Open CRs | [Count] | Current |

---

## 6. Records Retention

Maintenance records shall be retained for the operational lifetime of the software plus 10 years, in accordance with railway regulations.

**Archive location:** [Location / repository]  
**Retention period:** [End date or "Until decommissioned + 10 years"]

---

## 7. References

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-SCMP-YYYY-NNN | Software Configuration Management Plan | [Version] |
| DOC-MAINTPLAN-YYYY-NNN | Software Maintenance Plan | [Version] |
| STD-EN50128 | EN 50128:2011 §9.2 (Software Maintenance), §6.6 (Configuration Management) | — |

---

**End of Software Maintenance Records**
