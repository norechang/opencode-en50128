# Hazard Log

**Document Type**: Cross-cutting safety artifact (outside Annex C Table C.1)  
**Standard**: EN 50128:2011 §7.1, §7.2.4.13, §6.6  
**Template version**: 2.0

---

## Document Control

| Field | Value |
|-------|-------|
| **Document ID** | DOC-HAZLOG-[YYYY]-[NNN] |
| **Version** | [MAJOR.MINOR] |
| **Date** | [YYYY-MM-DD] |
| **Project** | [ProjectName] |
| **SIL Level** | [0 / 1 / 2 / 3 / 4] |
| **Author** | [AuthorName] (SAF) |
| **Status** | [Draft \| Review \| Approved \| Baseline] |

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft — Phase 2 hazard analysis |

## Approvals

> **Note**: VER, VAL, and ASR do not appear in the Approvals table.
> VER and VAL review this artifact in Track B; their sign-off is recorded in
> their respective verification/validation reports — not here.
> ASR independently reviews all safety evidence; ASR sign-off is in item 46.
>
> Track A Approvals table (document release):

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author** (SAF) | [Name] | | YYYY-MM-DD |
| **Reviewer** (QUA) | [Name] | | YYYY-MM-DD |
| **Approver** (PM) | [Name] | | YYYY-MM-DD |

---

## 1. Introduction

### 1.1 Purpose

This Hazard Log documents all software-relevant hazards identified for **[Project Name]**
in accordance with EN 50128:2011 §7.1 and EN 50126:2017. It is a living document,
maintained by SAF and CM-controlled per §6.6.

The Hazard Log provides:
- Complete hazard identification (HAZ-xxx) with severity, frequency, risk, and SIL assignment
- REQ-SAFE-xxx safety requirement derivation and links (§7.2.4.13)
- Mitigation strategy and residual risk assessment
- Hazard closure status for Validation phase (§7.7.4.8(b))
- SEEA findings (if SIL 3–4; Table A.8 entry 5)

### 1.2 Scope

This Hazard Log covers software-relevant hazards in [system name], including:
- Software-induced hazardous states
- Hardware-software interface failures relevant to software behaviour
- Systematic software failures

Out of scope: pure mechanical failures, pure electrical supply failures, human factors
analysed entirely at system level. These are covered by the System Hazard Analysis (S4).

### 1.3 Safety Analysis Techniques Applied

Per EN 50128 Table A.8 (§6.3) and EN 50126:

| Technique | Source | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 | Applied |
|-----------|--------|-------|-------|-------|-------|-------|---------|
| Static Software Analysis | Table A.8 entry 1 | R | HR | HR | HR | HR | [Yes/No] |
| Dynamic Software Analysis | Table A.8 entry 2 | — | R | R | HR | HR | [Yes/No] |
| Cause Consequence Diagrams | Table A.8 entry 3 | R | R | R | R | R | [Yes/No] |
| Event Tree Analysis | Table A.8 entry 4 | — | R | R | R | R | [Yes/No] |
| Software Error Effect Analysis (SEEA) | Table A.8 entry 5 | — | R | R | HR | HR | [Yes/No] |
| FMEA (EN 50126 D.27, via §7.1) | EN 50126 | — | R | HR | HR | HR | [Yes/No] |
| FTA (EN 50126 D.30, via §7.1) | EN 50126 | — | R | HR | HR | HR | [Yes/No] |
| CCF Analysis (EN 50126 D.9/D.11, via §7.1) | EN 50126-2 Table F.2 | — | — | R | HR | HR | [Yes/No] |

> **Note**: FMEA, FTA, and CCF are EN 50126 system-level techniques applied to support
> software analysis via EN 50128 §7.1. They are NOT Table A.8 entries. CCF is
> **Highly Recommended** (not Mandatory) at SIL 3–4 per EN 50126-2:2017 Table F.2 item 11.

### 1.4 References

| Reference | Document |
|-----------|----------|
| [S4] | System Safety Requirements Specification (EN 50126 output) |
| [SRS] | Software Requirements Specification, DOC-SRS-[YYYY]-[NNN] |
| [SAS] | Software Architecture Specification, DOC-SAS-[YYYY]-[NNN] |
| [EN50128] | EN 50128:2011 Railway applications — Software standard |
| [EN50126-1] | EN 50126-1:2017 RAMS Part 1 |
| [EN50126-2] | EN 50126-2:2017 RAMS Part 2 |

---

## 2. Hazard Analysis Summary

### 2.1 Hazard Count by Severity

| Severity (score) | Count |
|-----------------|-------|
| Catastrophic (9–10) | [N] |
| Critical (7–8) | [N] |
| Moderate (4–6) | [N] |
| Minor (1–3) | [N] |
| **Total** | [N] |

### 2.2 Hazard Status Summary

| Status | Count |
|--------|-------|
| OPEN | [N] |
| CLOSED | [N] |
| ACCEPTED-RESIDUAL | [N] |

### 2.3 SIL Distribution

| SIL | Count |
|-----|-------|
| SIL 4 | [N] |
| SIL 3 | [N] |
| SIL 2 | [N] |
| SIL 1 | [N] |
| SIL 0 | [N] |

---

## 3. Hazard Register

### HAZ-001: [Hazard Title]

| Field | Value |
|-------|-------|
| **HAZ-ID** | HAZ-001 |
| **Description** | [Hazard event description] |
| **Source** | [S4 reference or analysis result] |
| **Severity** | [1–10] |
| **Frequency** | [1–10] |
| **Risk Level** | [Severity × Frequency] |
| **SIL Assignment** | [SIL 0/1/2/3/4] — per EN 50126-2 Table 8 |
| **Mitigation** | [Software safeguard strategy] |
| **Residual Risk** | [Integer 1–100] |
| **REQ-SAFE-xxx** | [REQ-SAFE-001, REQ-SAFE-002, ...] |
| **Status** | OPEN |
| **Evidence** | [Populated in Phase 7: test case ID] |
| **Acceptance Authority** | [For ACCEPTED-RESIDUAL: role + name] |

---

[Add HAZ-002, HAZ-003, etc. for each identified hazard]

---

## 4. Common Cause Failure (CCF) Analysis

> **EN 50128 / EN 50126-2 note**: CCF Analysis is **Highly Recommended** (HR) at SIL 3–4
> per EN 50126-2:2017 Table F.2 item 11. It is NOT Mandatory. Include this section if the
> project SQAP selects CCF analysis; otherwise note the justified waiver here.
> CCF is an EN 50126 technique applied to software via EN 50128 §7.1; it is NOT a
> Table A.8 entry.

**CCF Analysis status**: [Selected / Waived — see SQAP §[X] for justification]

### CCF-001: [Common Cause Failure Scenario]

| Field | Value |
|-------|-------|
| **CCF-ID** | CCF-001 |
| **Scenario** | [Description of common cause] |
| **Related HAZ** | [HAZ-xxx] |
| **Cause type** | [Common design fault / Shared HW platform / EMI / Common power supply] |
| **Affected modules** | [Module list] |
| **Mitigation** | [Diverse design, spatial separation, independent power, EMI shielding] |
| **Status** | [Mitigated / Partially Mitigated] |

---

## 5. Software Error Effect Analysis (SEEA)

> **EN 50128 Table A.8 entry 5**: SEEA is HR at SIL 3–4. Record findings per fault mode.
> This section is filled in Phase 2 (preliminary) and updated in Phase 3.

| Module | Fault Mode | Effect (module) | Effect (system) | Safeguard | HAZ link |
|--------|-----------|-----------------|-----------------|-----------|----------|
| [Module] | NULL pointer | [Effect] | [Effect] | Null check guard / MISRA Rule 17.3 | [HAZ-xxx] |
| [Module] | Integer overflow | [Effect] | [Effect] | Range check / saturating arithmetic | [HAZ-xxx] |
| [Module] | State stuck-at | [Effect] | [Effect] | Watchdog / timeout exit | [HAZ-xxx] |
| [Module] | Uninitialized var | [Effect] | [Effect] | Explicit initialization / MISRA Rule 9.3 | [HAZ-xxx] |
| [Module] | Array out-of-bounds | [Effect] | [Effect] | Bounds check | [HAZ-xxx] |
| [Module] | Division by zero | [Effect] | [Effect] | Non-zero denominator check | [HAZ-xxx] |

---

## 6. Safety Requirements Summary (HAZ → REQ-SAFE trace)

| HAZ-ID | Severity | SIL | REQ-SAFE-xxx | SRS Section | Status |
|--------|----------|-----|--------------|-------------|--------|
| HAZ-001 | [Score] | [SIL] | REQ-SAFE-001 | §[X] | [Open/Covered] |

---

## 7. Hazard Closure Record (Phase 7)

Populated by SAF in Phase 7 per §7.7.4.8(b). All entries must reach CLOSED or
ACCEPTED-RESIDUAL before Validation Report sign-off.

| HAZ-ID | REQ-SAFE-xxx | Test Case (item 24) | Test Result | Closure Status | Date |
|--------|-------------|---------------------|-------------|----------------|------|
| HAZ-001 | REQ-SAFE-001 | [TC-ID] | [PASS/FAIL] | [CLOSED/OPEN] | YYYY-MM-DD |

---

## Appendix A: Risk Matrix Reference

### Severity Scale (1–10)

| Score | Level | Description |
|-------|-------|-------------|
| 9–10 | Catastrophic | Death or multiple serious injuries |
| 7–8 | Critical | Single serious injury |
| 4–6 | Moderate | Minor injuries or significant service loss |
| 1–3 | Minor | No injury, minor inconvenience |

### Frequency Scale (1–10)

| Score | Level | Probability range (per operating hour) |
|-------|-------|----------------------------------------|
| 9–10 | Frequent | > 10⁻³ |
| 7–8 | Probable | 10⁻³ to 10⁻⁴ |
| 4–6 | Occasional | 10⁻⁴ to 10⁻⁶ |
| 1–3 | Remote/Improbable | < 10⁻⁶ |

### SIL Assignment from THR (EN 50126-2 Table 8)

| THR (per hour) | SIL |
|----------------|-----|
| ≥ 10⁻⁵ to < 10⁻⁴ | SIL 1 |
| ≥ 10⁻⁶ to < 10⁻⁵ | SIL 2 |
| ≥ 10⁻⁷ to < 10⁻⁶ | SIL 3 |
| ≥ 10⁻⁸ to < 10⁻⁷ | SIL 4 |

---

## Appendix B: EN 50128 Table A.8 (Normative Reference)

Source: EN 50128:2011 §6.3. **Exactly 5 entries.** FMEA, FTA, CCF, and HAZOP are NOT
in Table A.8 (they are EN 50126 techniques applied via §7.1).

| # | Technique | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 |
|---|-----------|-------|-------|-------|-------|-------|
| 1 | Static Software Analysis (D.13, D.37, Table A.19) | R | HR | HR | HR | HR |
| 2 | Dynamic Software Analysis (Table A.13, A.14) | — | R | R | HR | HR |
| 3 | Cause Consequence Diagrams (D.6) | R | R | R | R | R |
| 4 | Event Tree Analysis (D.22) | — | R | R | R | R |
| 5 | Software Error Effect Analysis — SEEA (D.25) | — | R | R | HR | HR |

---

**END OF HAZARD LOG**
