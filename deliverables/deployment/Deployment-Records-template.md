# Deployment Records

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 §9.1.4.13-9.1.4.15  
**ANNEX C ITEM**: #41

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-DEPLOYRECORDS-[YYYY]-[NNN] |
| **Version** | [X.Y] |
| **Date** | [YYYY-MM-DD] |
| **Project** | [Project Name] |
| **SIL Level** | [0 \| 1 \| 2 \| 3 \| 4] |
| **Author** | [Name], CM / Deployment Engineer |
| **Reviewer** | [Name], VER |
| **Status** | [Draft \| Final] |

## DOCUMENT CONTROL

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 0.1 | YYYY-MM-DD | [Name] | Initial deployment record |

---

## 1. Deployment Identification

| Field | Value |
|-------|-------|
| **Deployment ID** | DEPLOY-[YYYY]-[NNN] |
| **Software Release** | [Release ID / Version] |
| **Deployment Site** | [Site Name / Location] |
| **Deployment Date** | [YYYY-MM-DD] |
| **Deployment Engineer** | [Name] |
| **Authorization Reference** | DOC-DEPLOYPLAN-YYYY-NNN |
| **Deployment Manual Reference** | DOC-SDM-YYYY-NNN |

---

## 2. Software Verification on Target (§9.1.4.13)

### 2.1 Software Self-Identification Check

| Item | Expected | Actual | Result |
|------|----------|--------|--------|
| Product ID | [Expected] | [Actual] | [PASS/FAIL] |
| Software Version | [Expected] | [Actual] | [PASS/FAIL] |
| Build Date | [Expected] | [Actual] | [PASS/FAIL] |
| SIL Level Declared | [Expected] | [Actual] | [PASS/FAIL] |
| Checksum / CRC | [Expected] | [Actual] | [PASS/FAIL] |

### 2.2 Package Integrity Verification

| File | Expected Checksum | Actual Checksum | Result |
|------|------------------|-----------------|--------|
| [executable] | [SHA-256] | [SHA-256] | [PASS/FAIL] |
| [config] | [SHA-256] | [SHA-256] | [PASS/FAIL] |

---

## 3. Installation Record

| Step | Description | Result | Notes |
|------|-------------|--------|-------|
| 1 | System preparation | [PASS/FAIL] | [Notes] |
| 2 | Package transfer | [PASS/FAIL] | [Notes] |
| 3 | Package integrity check | [PASS/FAIL] | [Notes] |
| 4 | Software installation | [PASS/FAIL] | [Notes] |
| 5 | System configuration | [PASS/FAIL] | [Notes] |
| 6 | Installation verification | [PASS/FAIL] | [Notes] |

---

## 4. Acceptance Test Results (§9.1.4.14)

| Test ID | Description | Result | Signature |
|---------|-------------|--------|-----------|
| AT-001 | Software self-identification | [PASS/FAIL] | [Name] |
| AT-002 | [Safety function test] | [PASS/FAIL] | [Name] |
| AT-003 | [Operational test] | [PASS/FAIL] | [Name] |

**Overall Acceptance Result:** [PASS / FAIL]

---

## 5. Previous Version Disposition

| Item | Action | Evidence |
|------|--------|----------|
| Previous software binary | [Archived / Removed] | [Reference] |
| Previous configuration | [Archived / Removed] | [Reference] |

---

## 6. Deployment Confirmation

**Deployment Engineer Declaration:**  
I confirm that the software has been installed in accordance with the Software Deployment Manual (DOC-SDM-YYYY-NNN) and that all acceptance tests have passed.

| Field | Value |
|-------|-------|
| **Deployment Engineer** | [Name] |
| **Signature** | [Signature] |
| **Date** | [Date] |
| **Organisation** | [Organisation] |

**Site Manager Confirmation:**  
I confirm the deployment was witnessed and the system is operational.

| Field | Value |
|-------|-------|
| **Site Manager** | [Name] |
| **Signature** | [Signature] |
| **Date** | [Date] |

---

## 7. Issues During Deployment

| Issue ID | Description | Resolution | Status |
|----------|-------------|-----------|--------|
| — | [No issues] / [Issue description] | [Resolution] | [Resolved] |

---

**End of Deployment Records**
