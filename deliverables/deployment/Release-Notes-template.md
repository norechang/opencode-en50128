# Release Notes

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 §9.1.4.5-9.1.4.6  
**ANNEX C ITEM**: #42

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-RELEASENOTES-[YYYY]-[NNN] |
| **Version** | [MAJOR.MINOR] |
| **Date** | [YYYY-MM-DD] |
| **Project** | [ProjectName] |
| **Software Release** | [Release Version] |
| **SIL Level** | [0 \| 1 \| 2 \| 3 \| 4] |
| **Author** | [AuthorName], PM/CM |
| **Reviewer** | [ReviewerName], VER |
| **Status** | [Draft \| Final \| Baseline] |

## DOCUMENT CONTROL

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft |
| 1.0 | YYYY-MM-DD | [Name] | Final release |

---

## 1. Release Identification

| Item | Value |
|------|-------|
| **Product Name** | [Product Name] |
| **Software Version** | [Version] |
| **Release Type** | [Initial Release / Maintenance Release / Patch] |
| **Release Date** | [YYYY-MM-DD] |
| **Previous Version** | [Previous version or "N/A — initial release"] |
| **Baseline Reference** | [SCMP Baseline ID] |

---

## 2. Application Conditions (§9.1.4.5(a))

This software is designed for use under the following conditions only:

| Condition | Specification |
|-----------|--------------|
| Target hardware | [Hardware platform, version] |
| Operating environment | [Temperature range, EMC class, etc.] |
| Required firmware/OS | [Firmware version, OS version] |
| Operational context | [Railway system type, speed limit, etc.] |
| SIL classification | SIL [X] per EN 50128:2011 |

**Any use outside these conditions requires re-assessment and re-validation.**

---

## 3. Compatibility Information (§9.1.4.5(b))

| Component | Compatible Versions | Incompatible Versions |
|-----------|-------------------|----------------------|
| Hardware platform | [Compatible versions] | [Incompatible versions] |
| Bootloader | [Compatible versions] | [Incompatible versions] |
| Configuration tool | [Compatible versions] | [Incompatible versions] |
| Application data | [Compatible versions] | [Incompatible versions] |

---

## 4. Restrictions and Known Issues (§9.1.4.5(c))

### 4.1 Operational Restrictions

| Restriction ID | Description | Reason | Reference |
|---------------|-------------|--------|-----------|
| REST-001 | [Restriction description] | [Safety/technical reason] | [Validation report section] |

### 4.2 Known Defects and Limitations

| Issue ID | Description | Workaround | Target Fix Version |
|----------|-------------|-----------|-------------------|
| — | No known safety-relevant defects | N/A | N/A |

### 4.3 Items Not Validated

| Item | Reason Not Validated | Risk Level |
|------|---------------------|-----------|
| [If any functionality not covered by validation] | [Reason] | [Risk] |

---

## 5. Changes from Previous Version

### 5.1 New Features / Enhancements

| Change ID | Description | Reference (SRS/CCB) |
|-----------|-------------|---------------------|
| CHG-001 | [Description] | [SRS requirement or CCB ID] |

### 5.2 Defect Fixes

| Defect ID | Description | Fix Description | Reference |
|-----------|-------------|----------------|-----------|
| DEF-001 | [Defect description] | [Fix description] | [CCB ID] |

### 5.3 Unchanged Safety-Critical Functions

All safety-critical functions from previous version [X.Y] remain unchanged EXCEPT as noted above.

---

## 6. Validation and Verification Status

| Activity | Status | Reference |
|----------|--------|-----------|
| Software validation completed | [Yes/No] | DOC-025-VALIDATION-REPORT |
| All verification reports signed | [Yes/No] | See verification plan |
| Assessment completed (SIL 1-4) | [Yes/No] | DOC-SAR-YYYY-NNN |
| Configuration baseline established | [Yes/No] | [Baseline ID] |

---

## 7. Release Authorization

This release is authorized for deployment per the Software Release and Deployment Plan (DOC-DEPLOYPLAN-YYYY-NNN).

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Project Manager | [Name] | [Signature] | [Date] |
| Lifecycle Coordinator (COD) | [Name] | [Signature] | [Date] |
| V&V Manager (VMGR) | [Name] | [Signature] | [SIL 3-4 only] |

---

**End of Release Notes**
