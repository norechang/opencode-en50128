# Software Change Records

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 §9.2.4.6(b)  
**ANNEX C ITEM**: #36

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SCR-[YYYY]-[NNN] |
| **Version** | [X.Y] |
| **Date** | [YYYY-MM-DD] |
| **Project** | [Project Name] |
| **SIL Level** | [0 \| 1 \| 2 \| 3 \| 4] |
| **Author** | [Name], CM |
| **Reviewer** | [Name], QUA |
| **Status** | [Open \| In Progress \| Closed \| Rejected] |

---

## 1. Change Request Identification

| Field | Value |
|-------|-------|
| **Change Request ID** | CR-[YYYY]-[NNN] |
| **Date Raised** | [YYYY-MM-DD] |
| **Raised By** | [Name / Role / Organisation] |
| **Priority** | [Safety-Critical / High / Medium / Low] |
| **Type** | [Corrective / Adaptive / Preventive / Enhancement] |
| **Affected Software Version** | [Version where issue was found] |

---

## 2. Problem / Change Description

### 2.1 Summary

[One-sentence summary of the change or problem]

### 2.2 Detailed Description

[Full description of the defect, issue, or requested change]

### 2.3 Steps to Reproduce (for defects)

1. [Step 1]
2. [Step 2]
3. [Expected result]: [Expected]
4. [Actual result]: [Actual]

### 2.4 Affected Components

| Component | File / Module | Version |
|-----------|--------------|---------|
| [Component] | [File] | [Version] |

---

## 3. Safety Impact Assessment

| Item | Assessment |
|------|-----------|
| **Safety-relevant?** | [Yes / No / Under assessment] |
| **SIL level of affected function** | [SIL 0/1/2/3/4] |
| **Hazard reference** | [Hazard ID from Hazard Log, or "N/A"] |
| **Immediate mitigation required?** | [Yes / No] |
| **Mitigation measure** | [Description, or "N/A"] |

---

## 4. Change Classification

| Field | Value |
|-------|-------|
| **Change Class** | [Class A — safety-critical / Class B — non-safety-critical / Class C — documentation] |
| **Re-entry Phase** | [Phase number and name, or "N/A"] |
| **Re-verification scope** | [Description of what must be re-verified] |
| **Re-validation required?** | [Yes / No] |

---

## 5. CCB Decision

| Field | Value |
|-------|-------|
| **CCB Decision Date** | [YYYY-MM-DD] |
| **Decision** | [Approved / Rejected / Deferred] |
| **CCB Chair** | [Name] |
| **Target Version** | [Version in which this change will be implemented] |
| **Target Date** | [YYYY-MM-DD] |
| **Rejection / Deferral Reason** | [If applicable] |

---

## 6. Implementation Record

| Field | Value |
|-------|-------|
| **Implemented By** | [Name] |
| **Implementation Date** | [YYYY-MM-DD] |
| **Files Modified** | [List of modified files with versions] |
| **New Baseline** | [Baseline ID] |
| **Test Results** | [Pass / Fail — reference to test evidence] |

---

## 7. Verification Record

| Field | Value |
|-------|-------|
| **Verified By** | [Name, VER] |
| **Verification Date** | [YYYY-MM-DD] |
| **Verification Result** | [Pass / Fail / Conditional] |
| **Verification Report Reference** | [DOC ID] |

---

## 8. Closure

| Field | Value |
|-------|-------|
| **Closure Date** | [YYYY-MM-DD] |
| **Closed By** | [Name, CM] |
| **Closure Notes** | [Any notes on lessons learned or follow-up] |

---

## 9. Change History for this CR

| Date | Action | By | Notes |
|------|--------|----|-------|
| [Date] | CR raised | [Name] | — |
| [Date] | Safety assessment | [Name] | — |
| [Date] | CCB decision | [Name] | — |
| [Date] | Implementation | [Name] | — |
| [Date] | Verification | [Name] | — |
| [Date] | Closure | [Name] | — |

---

**End of Software Change Record**
