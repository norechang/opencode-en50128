# Software Maintenance Plan

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 §9.2.4.2-9.2.4.5  
**ANNEX C ITEM**: #37

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SMP-[YYYY]-[NNN] |
| **Version** | [X.Y] |
| **Date** | [YYYY-MM-DD] |
| **Project** | [Project Name] |
| **SIL Level** | [0 \| 1 \| 2 \| 3 \| 4] |
| **Author** | [Name], PM |
| **Reviewer** | [Name], QUA |
| **Approver** | [Name], COD |
| **Status** | [Draft \| Approved \| Baseline] |

## DOCUMENT CONTROL

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft |

---

## 1. Introduction

### 1.1 Purpose

This Software Maintenance Plan defines the policies, procedures, and responsibilities for maintaining [Project Name] software throughout its operational lifetime, in accordance with EN 50128:2011 Section 9.2.

### 1.2 Scope

**Software:** [Project Name] v[Version]  
**Maintenance Period:** [Start Date] to [End Date / "Until decommissioned"]  
**Maintenance Types Covered:**
- Corrective maintenance (defect fixing)
- Adaptive maintenance (environmental changes)
- Preventive maintenance (proactive improvement)

### 1.3 Reference Documents

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-SCMP-YYYY-NNN | Software Configuration Management Plan | X.Y |
| DOC-SQAP-YYYY-NNN | Software Quality Assurance Plan | X.Y |
| DOC-SVP-YYYY-NNN | Software Verification Plan | X.Y |
| STD-EN50128 | EN 50128:2011 Railway Applications | - |

---

## 2. Maintenance Organisation

| Role | Name | Responsibility |
|------|------|---------------|
| Maintenance Manager (PM) | [Name] | Overall maintenance oversight |
| Configuration Manager (CM) | [Name] | Change control and baseline management |
| Maintenance Engineer | [Name] | Analysis and implementation |
| Verifier (VER) | [Name] | Independent verification of changes |
| Quality Assurance (QUA) | [Name] | Process compliance |

---

## 3. Maintenance Process (§9.2.4.2)

### 3.1 Change Request Initiation

1. Problem/change identified and reported
2. Change Request (CR) raised (DOC-043-SMR template)
3. CR assigned unique ID by CM
4. Initial triage: safety-relevant / non-safety-relevant

### 3.2 Change Impact Analysis (§9.2.4.3)

For each change request:
- Assess safety impact (SIL level of affected components)
- Assess scope of changes (files, modules, interfaces affected)
- Determine re-verification scope
- Determine re-validation scope (if applicable)

### 3.3 Change Classification

| Class | Description | Process |
|-------|-------------|---------|
| Class A | Safety-critical change | Full V-Model re-entry from affected phase |
| Class B | Non-safety-critical change | Abbreviated process per §9.2 |
| Class C | Documentation correction | Review and approval only |

### 3.4 Implementation and Verification (§9.2.4.4)

1. CCB authorizes change
2. Change implemented by qualified engineer
3. Change reviewed and tested
4. Independent verification per §6.2 (scope depends on class)
5. Configuration management updated (new baseline)

---

## 4. Maintenance Records (§9.2.4.6)

All maintenance activities shall be documented per Maintenance Records template (DOC-043-SMR).

Records shall be retained for: [Project lifetime + 10 years (railway requirement)]

---

## 5. Emergency Maintenance

For safety-critical defects requiring immediate action:

1. Safety engineering assessment (SAF) performed immediately
2. Temporary mitigation measures identified
3. Emergency change authorized by COD
4. Expedited implementation and verification
5. Formal CCB review within [7 days]

---

## 6. Periodic Maintenance Reviews

| Review Type | Frequency | Participants |
|-------------|-----------|-------------|
| Outstanding defect review | [Monthly] | PM, CM, QUA |
| Safety monitoring review | [Quarterly] | PM, SAF, QUA |
| Configuration audit | [Annually] | CM, QUA, VER |

---

## 7. Tool and Environment Maintenance

When tools or environment change:
- Tool re-validation per EN 50128 §6.7 (if T3 tools affected)
- Re-verification of affected components
- Update to Software Assessment (SIL 1-4)

---

**End of Software Maintenance Plan**
