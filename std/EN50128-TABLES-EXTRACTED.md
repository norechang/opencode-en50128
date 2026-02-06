# EN 50128:2011 Extracted Technique/Measure Tables

**Source:** EN 50128:2011 Annex A  
**Location:** `std/EN50128-2011.md`  
**Extraction Date:** 2026-02-06

This document contains technique and measure tables extracted from EN 50128:2011 Annex A for quick reference.

---

## Table A.6 – Integration (Section 7.6)

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | Functional and Black-box Testing | Table A.14 | HR | HR | HR |
| 2 | Performance Testing | Table A.18 | - | R | HR |

**Requirements:**
- One or more techniques SHALL be selected
- Applies to software integration and software/hardware integration

**EN 50128 Reference:** Section 7.6 (Integration), lines 3284-3404  
**Standard Location:** `std/EN50128-2011.md`

---

## Table A.7 – Overall Software Testing (Sections 6.2 and 7.7)

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | Performance Testing | Table A.18 | - | HR | **M** |
| 2 | Functional and Black-box Testing | Table A.14 | HR | HR | **M** |
| 3 | Modelling | Table A.17 | - | R | R |

**Requirements:**
- SIL 3-4 requires MANDATORY (M) performance testing AND functional/black-box testing
- Applies to overall software testing and final validation

**EN 50128 Reference:** Section 7.7 (Overall Software Testing / Final Validation), lines 3405-3520  
**Standard Location:** `std/EN50128-2011.md`

---

## Table A.8 – Software Analysis Techniques (Section 6.3)

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | Static Software Analysis | D.13, D.37, Table A.19 | R | HR | HR |
| 2 | Dynamic Software Analysis | Table A.13, Table A.14 | - | R | HR |
| 3 | Cause Consequence Diagrams | D.6 | R | R | R |
| 4 | Event Tree Analysis | D.22 | - | R | R |
| 5 | Software Error Effect Analysis | D.25 | - | R | HR |

**Requirements:**
- One or more of these techniques SHALL be selected
- Static analysis Highly Recommended for SIL 1-2 and SIL 3-4
- Software Error Effect Analysis Highly Recommended for SIL 3-4

**EN 50128 Reference:** Section 6.3 (Software Analysis)  
**Standard Location:** `std/EN50128-2011.md`

---

## Table A.9 – Software Quality Assurance (Section 6.5)

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | Accredited to EN ISO 9001 | 7.1 | R | HR | HR |
| 2 | Compliant with EN ISO 9001 | 7.1 | **M** | **M** | **M** |
| 3 | Compliant with ISO/IEC 90003 | 7.1 | R | R | R |
| 4 | Company Quality System | 7.1 | **M** | **M** | **M** |
| 5 | Software Configuration Management | D.48 | **M** | **M** | **M** |
| 6 | Checklists | D.7 | R | HR | HR |
| 7 | Traceability | D.58 | R | HR | **M** |
| 8 | Data Recording and Analysis | D.12 | HR | HR | **M** |

**Mandatory for ALL SIL Levels:**
- EN ISO 9001 compliance (item 2)
- Company Quality System (item 4)
- Software Configuration Management (item 5)

**Mandatory for SIL 3-4:**
- Traceability (item 7)
- Data Recording and Analysis (item 8)

**EN 50128 Reference:** Section 6.5 (Software Quality Assurance), lines 1905-2135  
**Standard Location:** `std/EN50128-2011.md`

---

## Table A.10 – Software Maintenance (Section 9.2)

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | Impact Analysis | D.32 | R | HR | HR |
| 2 | Regression Testing | - | R | HR | HR |
| 3 | Re-verification | - | HR | HR | **M** |
| 4 | Configuration Management | D.48 | **M** | **M** | **M** |

**Requirements:**
- Configuration Management is MANDATORY for all SIL levels
- Re-verification is MANDATORY for SIL 3-4
- Impact Analysis and Regression Testing are Highly Recommended for SIL 1+

**EN 50128 Reference:** Section 9.2 (Software Maintenance), lines 4163-4245  
**Standard Location:** `std/EN50128-2011.md`

**Note:** This table content is partially reconstructed from scattered references in Section 9.2

---

## Table A.11 – Data Preparation Techniques (Section 8.4)

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | Tabular Specification Methods | D.68 | R | R | R |
| 2 | Application Specific Language | D.69 | R | R | R |
| 3 | Simulation | D.42 | R | HR | HR |
| 4 | Functional Testing | D.42 | **M** | **M** | **M** |
| 5 | Checklists | D.7 | R | HR | HR |
| 6 | Fagan Inspection | D.23 | - | R | R |
| 7 | Formal Design Reviews | D.56 | R | HR | HR |
| 8 | Formal Proof of Correctness (of data) | D.29 | - | - | - |
| 9 | Walkthrough | D.56 | R | R | HR |

**Mandatory for ALL SIL Levels:**
- Functional Testing (item 4)

**Approved Combinations:**
- **SIL 1-2:** Techniques 1 and 4
- **SIL 3-4:** Techniques 1, 4, 5, and 7 **OR** Techniques 2, 3, and 6

**EN 50128 Reference:** Section 8.4 (Data Preparation), lines 3697-3815  
**Standard Location:** `std/EN50128-2011.md`

**Note:** Technique 8 (Formal Proof) applies to proof of correctness of data, not programs (see reference D.29)

---

## Table A.21 – Test Coverage for Code

| COVERAGE TYPE | SIL 0 | SIL 1-2 | SIL 3-4 |
|---------------|-------|---------|---------|
| **Statement Coverage** | HR | HR | **M** |
| **Branch Coverage** | HR | **M** | **M** |
| **Condition Coverage** | - | R | **M** |
| **Data Flow Coverage** | - | R | HR |
| **Path Coverage** | - | - | R |

**Requirements by SIL:**
- **SIL 0:** Statement (HR), Branch (HR)
- **SIL 1-2:** Statement (HR), Branch (**M**)
- **SIL 3-4:** Statement (**M**), Branch (**M**), Condition (**M**)

**EN 50128 Reference:** Annex A, Table A.21  
**Standard Location:** `std/EN50128-2011.md`

**Note:** This table defines minimum coverage requirements for component testing and integration testing.

---

## Previously Extracted Tables (for reference)

### Table A.2 – Software Requirements Specification (Section 7.2)

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | Formal Methods | D.28 | - | R | HR |
| 2 | Modelling | Table A.17 | R | R | HR |
| 3 | Structured Methodology | D.52 | R | R | HR |
| 4 | Decision Tables | D.13 | R | R | HR |

**See:** `PROJECT_REVISION_STATUS.md` for full details

---

### Table A.3 – Software Architecture (Section 7.3)

23 techniques with approved combinations for SIL 3-4 and SIL 1-2.  
**See:** `PROJECT_REVISION_STATUS.md` for full details

---

### Table A.4 – Software Design and Implementation (Section 7.4)

14 techniques with approved combination for SIL 3-4.  
**See:** `PROJECT_REVISION_STATUS.md` for full details

---

### Table A.5 – Verification and Testing (Sections 6.2, 7.3)

10 techniques split between verification and testing.  
**See:** `PROJECT_REVISION_STATUS.md` for full details

---

## Key to Recommendations

- **M** = Mandatory - Must be used
- **HR** = Highly Recommended - Rationale required if not used (Section 4.8)
- **R** = Recommended - Should be considered
- **-** = No recommendation for or against
- **NR** = Not Recommended - Rationale required if used

**Reference:** EN 50128:2011 Section 4.8, Annex A

---

## Usage Guidelines

1. **Selection:** Select techniques appropriate to SIL level (Section 4.6-4.7)
2. **Mandatory (M):** Must be used, no alternatives
3. **Highly Recommended (HR):** Document rationale if not used (Section 4.8)
4. **Approved Combinations:** When noted, assessor shall accept if correctly applied
5. **Documentation:** Record selections in SQAP (Section 4.7-4.9)
6. **Alternative Techniques:** Must be justified if not in tables (Section 4.9)

---

## Related Documents

- **Full Standard:** `std/EN50128-2011.md`
- **Abbreviations:** `std/EN50128-ABBREVIATIONS.md`
- **Full Table Extractions:** `PROJECT_REVISION_STATUS.md`
- **Project Agents:** `AGENTS.md`
- **Project Lifecycle:** `LIFECYCLE.md`

---

**Document Version:** 1.0  
**Last Updated:** 2026-02-06  
**Status:** Official Reference  
**Extracted By:** Automated analysis of EN 50128:2011 Markdown conversion
