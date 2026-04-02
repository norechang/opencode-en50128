# Hazard Log

**Document Type**: Cross-cutting safety artifact (outside Annex C Table C.1)  
**Standard**: EN 50128:2011 §7.1, §7.2.4.13, §6.6  
**Template version**: 2.0

---

## Document Control

| Field | Value |
|-------|-------|
| **Document ID** | DOC-HAZLOG-2026-001 |
| **Version** | 0.3 |
| **Date** | 2026-04-02 |
| **Project** | TDC (Train Door Control System) |
| **SIL Level** | SIL 3 |
| **Author** | SAF (Safety Engineer) |
| **Status** | approved |

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 0.1 | 2026-04-02 | SAF | Initial draft — Phase 2 hazard analysis; 10 software hazards identified; SEEA preliminary |
| 0.2 | 2026-04-02 | SAF | Phase 2 update — SIL assignments confirmed per EN 50126-2 Table 8; all 21 REQ-SAFE-xxx requirements linked to hazards (15 × SIL 3, 6 × SIL 2); system hazard traceability table (Section 8) completed; H-001..H-010 / SW-HAZ cross-reference table added; hazard naming convention aligned with S4 input mapping; coordination with REQ confirmed — SIL tags to be reflected in SRS §7.2.4.13 |
| 0.3 | 2026-04-02 | SAF | Phase 3 update — FMEA (DOC-FMEA-2026-001) and FTA (DOC-FTA-2026-001) completed on SAS DOC-SAS-2026-001 v0.1; 49 failure modes analysed; all 10 existing hazards mitigated; 1 new hazard added (SW-HAZ-011 — SPI cross-channel transient denial-of-service); 15/15 SEEA findings validated; 3 FMEA open issues; 3 FTA open issues; 2 FTA critical/high findings for VER Phase 5; architectural mitigation strategies updated for all 10 hazards; Phase 3 FMEA/FTA section added (Section 6); Hazard summary updated |

## Approvals

> **Note**: Per SIL 3 requirements, Hazard Log approval follows Track B (Independent V&V) chain.
> VER and VAL review this artifact in Track B; their sign-off is recorded in
> their respective verification/validation reports.
> ASR independently reviews all safety evidence; ASR sign-off is in item 46.
>
> **Track B Approval Chain (Phase 2)**:

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author** (SAF) | Safety Engineer | SIGNED | 2026-04-02 |
| **QUA Review** | Quality Assurance | APPROVED | 2026-04-02 |
| **VER Review** | Verifier | APPROVED (via Item 8) | 2026-04-02 |
| **VMGR Approval** | V&V Manager | APPROVED WITH COMMENTS | 2026-04-02 |
| **COD Approval** | Lifecycle Coordinator | APPROVED | 2026-04-02 |

> **Approval Notes**: Hazard Log v0.2 reviewed and approved via Track B Independent V&V process.
> VER verified hazard analysis completeness in DOC-REQVER-2026-001 (Item 8).
> VMGR granted final approval (APPROVED WITH COMMENTS) on 2026-04-02.
> COD authorized use in Phase 2 gate transition.

---

## 1. Introduction

### 1.1 Purpose

This Hazard Log documents all software-relevant hazards identified for the **Train Door
Control System (TDC)** in accordance with EN 50128:2011 §7.1 and EN 50126:2017. It is a
living document, maintained by SAF and CM-controlled per §6.6.

The Hazard Log provides:
- Complete hazard identification (HAZ-xxx) with severity, frequency, risk, and SIL
  assignment derived from system-level hazards in S4
- REQ-SAFE-xxx safety requirement derivation and links (§7.2.4.13)
- Mitigation strategy and residual risk assessment
- Hazard closure status for Validation phase (§7.7.4.8(b)) — populated in Phase 7
- SEEA preliminary findings (SIL 3 — HR per Table A.8 entry 5)

**Phase 2 scope**: Initial hazard analysis. FMEA and FTA on software architecture are
Phase 3 activities (secondary SAF phase). CCF analysis section is included per SQAP
selection (HR at SIL 3 per EN 50126-2:2017 Table F.2 item 11).

**Phase 3 update (v0.3)**: FMEA (DOC-FMEA-2026-001) and FTA (DOC-FTA-2026-001) completed
on SAS DOC-SAS-2026-001 v0.1. 49 failure modes analysed across 8 components; 5 fault trees
constructed; 1 new hazard added (SW-HAZ-011 — SPI cross-channel transient denial-of-safe-
operation); 15/15 SEEA findings validated against SAS Appendix B; all 21 REQ-SAFE-xxx
confirmed allocated to components. Phase 3 findings recorded in Section 6 of this document.

### 1.2 Scope

This Hazard Log covers software-relevant hazards in the TDC system, including:
- Software-induced hazardous states (incorrect door control commands)
- Hardware-software interface failures relevant to software behaviour (sensor processing,
  CAN bus communication with TCMS, lock state management)
- Systematic software failures (watchdog, state machine, memory corruption)

**Out of scope**: Pure mechanical lock failure, pure electrical supply failures, and pure
hardware sensor failures where software cannot contribute to or mitigate the outcome.
These are covered by the System Hazard Analysis (DOC-SYS-SAF-2026-001, Section 2).

**System-level hazards traced**: HAZ-001 through HAZ-009 from
DOC-SYS-SAF-2026-001 §2.1.

### 1.3 Safety Analysis Techniques Applied

Per EN 50128 Table A.8 (§6.3) and EN 50126:

| Technique | Source | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 | Applied |
|-----------|--------|-------|-------|-------|-------|-------|---------|
| Static Software Analysis | Table A.8 entry 1 | R | HR | HR | HR | HR | Yes — planned Phase 5 (VER) |
| Dynamic Software Analysis | Table A.8 entry 2 | — | R | R | HR | HR | Yes — planned Phase 5/7 (TST/VER) |
| Cause Consequence Diagrams | Table A.8 entry 3 | R | R | R | R | R | No — FTA provides equivalent |
| Event Tree Analysis | Table A.8 entry 4 | — | R | R | R | R | No — system-level FTA sufficient |
| Software Error Effect Analysis (SEEA) | Table A.8 entry 5 | — | R | R | HR | HR | Yes — preliminary in this document (Phase 2); updated Phase 3 |
| FMEA (EN 50126 D.27, via §7.1) | EN 50126 | — | R | HR | HR | HR | Yes — Phase 3 activity (DOC-FMEA-2026-001) |
| FTA (EN 50126 D.30, via §7.1) | EN 50126 | — | R | HR | HR | HR | Yes — system FTA complete; SW FTA Phase 3 |
| CCF Analysis (EN 50126 D.9/D.11, via §7.1) | EN 50126-2 Table F.2 item 11 | — | — | R | HR | HR | Selected — see Section 4 |

> **Note**: FMEA, FTA, and CCF are EN 50126 system-level techniques applied to support
> software analysis via EN 50128 §7.1. They are NOT Table A.8 entries. CCF is
> **Highly Recommended** (not Mandatory) at SIL 3–4 per EN 50126-2:2017 Table F.2 item 11.

### 1.4 References

| Reference | Document |
|-----------|----------|
| [S4] | System Safety Requirements Specification, DOC-SYS-SAF-2026-001, v1.0 |
| [S4-Plan] | System Safety Plan, DOC-SYS-PLAN-2026-001, v1.0 |
| [SRS] | Software Requirements Specification, DOC-SRS-2026-001 (in progress — Phase 2) |
| [SAS] | Software Architecture Specification, DOC-SAS-2026-001 v0.1 DRAFT (Phase 3) |
| [FMEA] | FMEA Report — Software Architecture Failure Mode and Effects Analysis, DOC-FMEA-2026-001 v0.1 |
| [FTA] | FTA Report — Fault Tree Analysis for Critical Top Events, DOC-FTA-2026-001 v0.1 |
| [EN50128] | EN 50128:2011 Railway applications — Software standard |
| [EN50126-1] | EN 50126-1:2017 RAMS Part 1 |
| [EN50126-2] | EN 50126-2:2017 RAMS Part 2 |

---

## 2. Hazard Analysis Summary

### 2.1 Hazard Count by Severity

| Severity (score) | Count |
|-----------------|-------|
| Catastrophic (9–10) | 3 |
| Critical (7–8) | 5 |
| Moderate (4–6) | 3 |
| Minor (1–3) | 0 |
| **Total** | **11** |

> **Phase 3 update**: SW-HAZ-011 (SPI cross-channel transient denial-of-safe-operation)
> added from FMEA/FTA findings. Severity = 5 (Moderate); SIL 2.

### 2.2 Hazard Status Summary

| Status | Count |
|--------|-------|
| OPEN | 11 |
| CLOSED | 0 |
| ACCEPTED-RESIDUAL | 0 |

### 2.3 SIL Distribution

| SIL | Count |
|-----|-------|
| SIL 4 | 0 |
| SIL 3 | 7 |
| SIL 2 | 4 |
| SIL 1 | 0 |
| SIL 0 | 0 |

> **Note**: No hazard exceeds the project SIL cap of SIL 3. No escalation to PM required.
> The SIL 3 project ceiling is sufficient for all identified software hazards.

---

## 3. Hazard Register

---

### SW-HAZ-001: Door Opens While Train in Motion

| Field | Value |
|-------|-------|
| **HAZ-ID** | SW-HAZ-001 |
| **Description** | Software commands door open (or fails to inhibit open command) while train speed > 5 km/h, enabling a passenger to fall from the moving train |
| **Source** | S4 HAZ-003 (DOC-SYS-SAF-2026-001 §2.1); SF-001 Speed Interlock |
| **Severity** | 10 (Catastrophic — fatality) |
| **Frequency** | 3 (Remote — speed interlock must fail AND door command must occur) |
| **Risk Level** | 30 |
| **SIL Assignment** | **SIL 3** — THR ≥ 10⁻⁷/hr to < 10⁻⁶/hr; Intolerable risk class per S4 |
| **Mitigation** | (1) Speed Monitor module (SPM) checks TCMS speed every 20 ms before permitting door open command; (2) fail-safe default: on speed data timeout (200 ms) assume "moving" and inhibit all open commands; (3) redundant speed sources (2oo2) validated at software level before use; (4) cross-channel comparison — second channel must independently confirm speed ≤ 5 km/h |
| **Residual Risk** | 3 (after dual-channel 2oo2 + fail-safe + timeout detection) |
| **REQ-SAFE-xxx** | REQ-SAFE-001, REQ-SAFE-002, REQ-SAFE-003 |
| **Status** | OPEN |
| **Evidence** | [Populated Phase 7] |
| **Acceptance Authority** | N/A |

---

### SW-HAZ-002: Door Closes on Passenger (Obstacle Not Detected)

| Field | Value |
|-------|-------|
| **HAZ-ID** | SW-HAZ-002 |
| **Description** | Software fails to detect obstacle in door path, or detects obstacle but does not trigger reversal within 150 ms, causing passenger entrapment or crushing |
| **Source** | S4 HAZ-002, HAZ-004 (DOC-SYS-SAF-2026-001 §2.1); SF-003 Obstacle Detection and Reversal |
| **Severity** | 8 (Critical — serious injury) |
| **Frequency** | 5 (Occasional — depends on sensor status and passenger behaviour) |
| **Risk Level** | 40 |
| **SIL Assignment** | **SIL 3** — Intolerable risk; derived from S4 SIL 3 for SF-003 |
| **Mitigation** | (1) Obstacle Detector module (OBD) polls sensor data every 20 ms; (2) response time requirement: reversal command issued ≤ 100 ms from obstacle detection (leaving 50 ms margin for hardware actuation); (3) sensor self-test at each cycle — sensor fault triggers immediate safe state (door re-opens); (4) motor current monitoring provides backup detection: current > 150 N equivalent → immediate reversal |
| **Residual Risk** | 8 (moderate — residual risk from dual sensor failure; mitigated by mechanical 150 N force limiter) |
| **REQ-SAFE-xxx** | REQ-SAFE-004, REQ-SAFE-005, REQ-SAFE-006 |
| **Status** | OPEN |
| **Evidence** | [Populated Phase 7] |
| **Acceptance Authority** | N/A |

---

### SW-HAZ-003: False Door Lock Indication Allows Departure

| Field | Value |
|-------|-------|
| **HAZ-ID** | SW-HAZ-003 |
| **Description** | Software reports "all doors locked" to TCMS when one or more doors are not fully locked, allowing train departure with a door ajar and risk of passenger fall |
| **Source** | S4 HAZ-001, HAZ-005 (DOC-SYS-SAF-2026-001 §2.1); SF-002 Departure Interlock, SF-005 Door Position Verification |
| **Severity** | 10 (Catastrophic — fatality) |
| **Frequency** | 3 (Remote — requires dual sensor failure or software logic error) |
| **Risk Level** | 30 |
| **SIL Assignment** | **SIL 3** — Intolerable; S4 assigns SIL 3 to HAZ-001 and HAZ-005 |
| **Mitigation** | (1) Door State Machine (DSM) requires 2oo2 sensor agreement before setting LOCKED state; (2) departure interlock: "all doors locked" signal withheld until ALL door DSM instances report LOCKED; (3) cross-channel verification of lock state every 20 ms; (4) lock sensor fault → door state forced to UNLOCKED until repaired; (5) CRC protection on lock status data structures |
| **Residual Risk** | 3 (requires simultaneous dual-sensor failure AND software logic bypass — probability < 10⁻⁷/hr) |
| **REQ-SAFE-xxx** | REQ-SAFE-007, REQ-SAFE-008, REQ-SAFE-009 |
| **Status** | OPEN |
| **Evidence** | [Populated Phase 7] |
| **Acceptance Authority** | N/A |

---

### SW-HAZ-004: Loss of Door Position Indication

| Field | Value |
|-------|-------|
| **HAZ-ID** | SW-HAZ-004 |
| **Description** | Software loses or corrupts door position data, causing the door state machine to operate on stale or invalid position information, potentially reporting incorrect state to TCMS and operator |
| **Source** | S4 HAZ-001, HAZ-005 (DOC-SYS-SAF-2026-001 §2.1); SF-005 Door Position Verification; SAFE-DIAG-003 |
| **Severity** | 7 (Critical — loss of safety-relevant information) |
| **Frequency** | 4 (Occasional — sensor or communication faults can occur) |
| **Risk Level** | 28 |
| **SIL Assignment** | **SIL 3** — Position verification is SIL 3 per SF-005; incorrect position data can contribute directly to HAZ-001 and HAZ-005 |
| **Mitigation** | (1) CRC-16 protection on all sensor data structures; (2) position sensor timeout: if no update within 100 ms, assume "door open" (fail-safe); (3) cross-channel comparison of position data from both DCU channels; (4) sensor discrepancy detection (2oo2 disagreement) → door state forced to OPEN/UNKNOWN; (5) all position data validated for range and plausibility before use |
| **Residual Risk** | 4 |
| **REQ-SAFE-xxx** | REQ-SAFE-009, REQ-SAFE-010, REQ-SAFE-011 |
| **Status** | OPEN |
| **Evidence** | [Populated Phase 7] |
| **Acceptance Authority** | N/A |

---

### SW-HAZ-005: Software Commands Safe State Incorrectly (Spurious Lockout)

| Field | Value |
|-------|-------|
| **HAZ-ID** | SW-HAZ-005 |
| **Description** | Software triggers safe state (all doors locked, opening inhibited) when no actual hazard condition exists, trapping passengers at a station and causing service disruption. While not immediately life-threatening, repeated or extended lockouts may lead to secondary hazards (e.g., passenger forced egress from wrong side) |
| **Source** | S4 HAZ-006 (DOC-SYS-SAF-2026-001 §2.1); SF-007 Fault Isolation |
| **Severity** | 5 (Moderate — no direct injury; service disruption; secondary risk if egress obstructed) |
| **Frequency** | 4 (Occasional — diagnostic false positives or noise-induced watchdog triggers) |
| **Risk Level** | 20 |
| **SIL Assignment** | **SIL 2** — Derived from S4 HAZ-006 SIL 2; Tolerable ALARP risk class |
| **Mitigation** | (1) Watchdog timeout threshold set to 50 ms (not too tight) to avoid false triggers; (2) safe state trigger requires confirmation from BOTH channels (2oo2) except for immediate-safety cases (SW-HAZ-001); (3) fault logging with timestamp to distinguish genuine faults from transient noise; (4) selective door disablement (SF-007) allows isolating a single faulty door rather than locking all |
| **Residual Risk** | 4 |
| **REQ-SAFE-xxx** | REQ-SAFE-012, REQ-SAFE-013 |
| **Status** | OPEN |
| **Evidence** | [Populated Phase 7] |
| **Acceptance Authority** | N/A |

---

### SW-HAZ-006: Software Watchdog Failure (DCU Hang Not Detected)

| Field | Value |
|-------|-------|
| **HAZ-ID** | SW-HAZ-006 |
| **Description** | The software watchdog fails to detect a DCU processor hang or infinite loop, leaving the door control system in an undefined state where safety functions may not execute (speed interlock, obstacle detection) |
| **Source** | S4 HAZ-009 (DOC-SYS-SAF-2026-001 §2.1); SAFE-DIAG-006; SAFE-STATE-005 |
| **Severity** | 9 (Catastrophic — loss of all safety functions could lead to fatality if combined with other failures) |
| **Frequency** | 2 (Remote — dual-channel architecture reduces probability; watchdog is hardware-triggered) |
| **Risk Level** | 18 |
| **SIL Assignment** | **SIL 3** — Catastrophic severity; watchdog monitoring is SIL 3 per SAFE-DIAG-006; loss of watchdog removes primary safety function protection |
| **Mitigation** | (1) Hardware watchdog (independent of software) with 50 ms timeout; (2) cross-channel software watchdog — Channel B monitors Channel A execution cadence via SPI every 20 ms; (3) watchdog kick only permitted at defined safe point in execution cycle (not inside ISR or loop); (4) watchdog failure on either channel triggers safe state on both; (5) periodic memory CRC check to detect corruption causing infinite loop |
| **Residual Risk** | 2 (dual-channel independent watchdogs; hardware watchdog independent of software) |
| **REQ-SAFE-xxx** | REQ-SAFE-014, REQ-SAFE-015 |
| **Status** | OPEN |
| **Evidence** | [Populated Phase 7] |
| **Acceptance Authority** | N/A |

---

### SW-HAZ-007: CAN Bus Speed Data Loss (TCMS Communication Failure)

| Field | Value |
|-------|-------|
| **HAZ-ID** | SW-HAZ-007 |
| **Description** | Loss of speed data from TCMS via CAN bus (due to CAN fault, bus-off condition, or CRC error) is not detected in time, causing the speed interlock to operate on stale or default data; if the software defaults to "stationary" rather than "moving," door opening could be permitted while the train is in motion |
| **Source** | S4 HAZ-003 (DOC-SYS-SAF-2026-001 §2.1 FMEA: Communication Bus CAN); SAFE-STATE-002; SAFE-DIAG-003 |
| **Severity** | 10 (Catastrophic — same consequence as SW-HAZ-001 if speed interlock fails) |
| **Frequency** | 3 (Remote — CAN CRC + timeout provides detection; redundant channels) |
| **Risk Level** | 30 |
| **SIL Assignment** | **SIL 3** — CAN timeout detection is SIL 3 per SF-001; failure leads to same consequence as SW-HAZ-001 |
| **Mitigation** | (1) CAN message timeout detection at 200 ms (2 × 100 ms update interval); (2) on timeout: IMMEDIATELY assume "train moving" (SAFE-STATE-002) and inhibit door open commands; (3) CRC-16 on all CAN messages — CRC failure = message rejected = treat as timeout; (4) redundant CAN channels where available from TCMS; (5) software SHALL NOT use speed = 0 as default — default is speed = UNKNOWN → conservative action |
| **Residual Risk** | 3 |
| **REQ-SAFE-xxx** | REQ-SAFE-001, REQ-SAFE-003, REQ-SAFE-016 |
| **Status** | OPEN |
| **Evidence** | [Populated Phase 7] |
| **Acceptance Authority** | N/A |

---

### SW-HAZ-008: Memory Corruption Corrupts Safety-Critical Data

| Field | Value |
|-------|-------|
| **HAZ-ID** | SW-HAZ-008 |
| **Description** | Software memory corruption (stack overflow, heap corruption, pointer error, or EMI-induced bit flip) alters safety-critical data — door state, speed value, lock status, safe state flag — leading to incorrect door control decisions |
| **Source** | S4 HAZ-005, HAZ-009 (DOC-SYS-SAF-2026-001 §2.1 FMEA: DCU Processor); SAFE-SW-010; SAFE-SW-007 |
| **Severity** | 9 (Catastrophic — corrupted safety data can cause any of the above hazards) |
| **Frequency** | 2 (Remote — no dynamic memory allocation; static CRC protection applied) |
| **Risk Level** | 18 |
| **SIL Assignment** | **SIL 3** — Memory corruption affecting SIL 3 data structures is itself SIL 3 |
| **Mitigation** | (1) No dynamic memory allocation (SAFE-SW-007; MISRA C:2012 Rule 21.3); (2) CRC-16 protection on all safety-critical data structures updated every 20 ms cycle; (3) CRC mismatch → immediate safe state; (4) stack overflow protection: fixed stack sizes, stack canary values checked each cycle; (5) memory integrity check (ROM/RAM CRC) at boot and periodic (every 100 ms); (6) dual-channel cross-check detects single-channel corruption |
| **Residual Risk** | 2 |
| **REQ-SAFE-xxx** | REQ-SAFE-010, REQ-SAFE-017, REQ-SAFE-018 |
| **Status** | OPEN |
| **Evidence** | [Populated Phase 7] |
| **Acceptance Authority** | N/A |

---

### SW-HAZ-009: Emergency Release Mishandled by Software

| Field | Value |
|-------|-------|
| **HAZ-ID** | SW-HAZ-009 |
| **Description** | Software fails to correctly detect and handle an emergency release activation event: either (a) fails to report emergency release to TCMS/driver (allowing uninformed departure), or (b) spuriously reports emergency release (causing false alarm or unnecessary safe state) |
| **Source** | S4 HAZ-008 (DOC-SYS-SAF-2026-001 §2.1); SF-006 Emergency Release Monitoring; SAFE-COND-003 |
| **Severity** | 7 (Critical — uninformed departure with emergency release active could endanger passengers) |
| **Frequency** | 2 (Remote — emergency release is mechanical; software is monitoring only) |
| **Risk Level** | 14 |
| **SIL Assignment** | **SIL 2** — S4 assigns SIL 2 to SF-006; software role is monitoring/reporting, not control (mechanical is primary); consequence is Critical/Remote → Tolerable ALARP |
| **Mitigation** | (1) Emergency release sensor monitored every 20 ms; (2) emergency release detection: debounce filter (≥ 60 ms active) to avoid spurious detection from vibration; (3) on confirmed emergency release: immediately alert TCMS, inhibit departure interlock signal; (4) emergency release does NOT reset until explicitly cleared by maintenance (software state machine enforces this); (5) emergency release activation logged with timestamp |
| **Residual Risk** | 4 |
| **REQ-SAFE-xxx** | REQ-SAFE-019, REQ-SAFE-020 |
| **Status** | OPEN |
| **Evidence** | [Populated Phase 7] |
| **Acceptance Authority** | N/A |

---

### SW-HAZ-010: Selective Door Disablement Misuse (Bypass of Safety Interlock)

| Field | Value |
|-------|-------|
| **HAZ-ID** | SW-HAZ-010 |
| **Description** | Software implementing selective door disablement (SF-007) allows improper use that bypasses safety interlocks: e.g., disabling a door on the platform side without preventing departure, or disabling without proper authorization logging, masking a safety-relevant fault |
| **Source** | S4 SAFE-COND-001 (DOC-SYS-SAF-2026-001 §3.6); SF-007 Fault Isolation |
| **Severity** | 7 (Critical — disablement on platform side with train departure = fall hazard) |
| **Frequency** | 2 (Remote — requires driver action + software logic failure) |
| **Risk Level** | 14 |
| **SIL Assignment** | **SIL 2** — SF-007 is SIL 2 per S4 §4.2; selective disablement is a degraded-mode operation |
| **Mitigation** | (1) Speed interlock remains ACTIVE even when door is disabled — software SHALL NOT remove speed check for disabled doors; (2) platform-side disablement: software SHALL request TCMS confirmation before applying (driver authorization via TCMS command); (3) all disablement events logged with door ID, timestamp, channel ID; (4) disablement flag does NOT disable departure interlock for the disabled door — departure blocked if disabled door faces platform; (5) disabled door state visible on driver display |
| **Residual Risk** | 4 |
| **REQ-SAFE-xxx** | REQ-SAFE-012, REQ-SAFE-013, REQ-SAFE-021 |
| **Status** | OPEN |
| **Evidence** | [Populated Phase 7] |
| **Acceptance Authority** | N/A |

---

### SW-HAZ-011: SPI Cross-Channel Communication Failure — Denial of Safe Operation

| Field | Value |
|-------|-------|
| **HAZ-ID** | SW-HAZ-011 |
| **Description** | Recurring SPI transient errors between Channel A and Channel B cause the cross-channel comparison to fail repeatedly. The software correctly enters safe state (doors locked) on each transient, but because the transient is persistent or recurring at short intervals, the safe state cannot be exited. Passengers are trapped at the station indefinitely. This is distinct from SW-HAZ-005 (spurious safe state from logic fault): SW-HAZ-011 is caused by a communication channel failure that makes the cross-channel protocol unable to confirm recovery. |
| **Source** | FMEA Phase 3 — FM-TCI-003, FM-HAL-003 (DOC-FMEA-2026-001); OI-FMEA-001, OI-FTA-003 |
| **Severity** | 5 (Moderate — no direct injury during normal dwell; secondary risk if passengers attempt forced egress from incorrect side during extended delay) |
| **Frequency** | 3 (Remote — requires SPI transient AND software failure to distinguish transient from persistent fault) |
| **Risk Level** | 15 |
| **SIL Assignment** | **SIL 2** — Moderate severity × Remote frequency → Tolerable ALARP per EN 50126-2 Table 8; THR ≥ 10⁻⁶/hr to < 10⁻⁵/hr |
| **Mitigation** | (1) SPI transient filter: SKN to implement N-of-M consecutive failure threshold (≥ 3 consecutive failures in 5 cycles) before declaring permanent SPI fault and entering persistent safe state — single transient shall not cause persistent safe-state entry; (2) FMG to distinguish between transient SPI fault (recoverable) and persistent SPI fault (non-recoverable) using consecutive-failure counter; (3) on transient SPI: log event, alert TCMS, attempt recovery within 500 ms before declaring persistent fault; (4) persistent SPI fault: safe state confirmed, TCMS alerted, driver receives specific fault code (not generic safe state) |
| **Residual Risk** | 6 (with transient filter; residual risk = occasional SPI transient persisting beyond recovery threshold) |
| **REQ-SAFE-xxx** | REQ-SAFE-012 (existing — safe state trigger confirmation), REQ-SAFE-015 (existing — cross-channel watchdog) |
| **Status** | OPEN |
| **Evidence** | [Populated Phase 7] |
| **Acceptance Authority** | N/A |

> **Phase 3 note**: SW-HAZ-011 is a new hazard identified from Phase 3 FMEA/FTA analysis
> (FMEA open issue OI-FMEA-001; FTA open issue OI-FTA-003). The existing REQ-SAFE-012 and
> REQ-SAFE-015 partially cover this hazard but do not address the transient-vs-persistent
> distinction. DES must confirm that the SPI transient filter (OI-FMEA-001 action) is
> incorporated into the SAS before the SAS is baselined. Escalated to PM and DES for SAS
> update consideration.

---

## 4. Common Cause Failure (CCF) Analysis

> **EN 50128 / EN 50126-2 note**: CCF Analysis is **Highly Recommended** (HR) at SIL 3–4
> per EN 50126-2:2017 Table F.2 item 11. It is NOT Mandatory. This section is included
> because the SQAP (DOC-SQAP-2026-001) selects CCF analysis for the TDC project at SIL 3.
> CCF is an EN 50126 technique applied to software via EN 50128 §7.1; it is NOT a
> Table A.8 entry.

**CCF Analysis status**: Selected — per SQAP §4.2 (TDC SIL 3 project)

---

### CCF-001: Common Software Design Fault in Dual-Channel Processing

| Field | Value |
|-------|-------|
| **CCF-ID** | CCF-001 |
| **Scenario** | Both DCU channels share the same software binary compiled from the same source code. A systematic software error (e.g., incorrect speed threshold comparison operator) would defeat both channels simultaneously, removing the independence benefit of the 2oo2 architecture |
| **Related HAZ** | SW-HAZ-001, SW-HAZ-003, SW-HAZ-006 |
| **Cause type** | Common design fault |
| **Affected modules** | Speed Monitor (SPM), Door State Machine (DSM), Fault Manager (FMG) — all safety-critical modules |
| **β factor assumed** | 0.01 (per S4 FTA §2.4: common mode β = 0.01) |
| **Mitigation** | (1) Formal code review of all SIL 3 safety-critical modules by independent VER team; (2) static analysis (MISRA C:2012) applied to 100% of safety-critical code; (3) formal methods or structured walkthroughs for critical state machine transitions; (4) diverse compilers or compiler options between channels where feasible; (5) 100% MC/DC test coverage of safety-critical paths |
| **Status** | Partially Mitigated — residual CCF risk accepted with β = 0.01 and SIL 3 development process |

---

### CCF-002: Common EMI/Power Disturbance Affecting Both Channels

| Field | Value |
|-------|-------|
| **CCF-ID** | CCF-002 |
| **Scenario** | An electromagnetic disturbance or power supply fluctuation simultaneously corrupts memory or computation on both DCU channels, causing both to output the same incorrect door control command |
| **Related HAZ** | SW-HAZ-001, SW-HAZ-008 |
| **Cause type** | Shared HW platform / EMI / common power supply |
| **Affected modules** | All software modules (common hardware platform — dual STM32H743) |
| **β factor assumed** | 0.01 (as above) |
| **Mitigation** | (1) Physical separation of both MCUs on PCB with independent power regulation; (2) independent watchdogs on each channel (hardware watchdog — not software); (3) memory CRC check every 100 ms — EMI-induced bit flip detected before safety decision; (4) hardware EMC filtering per EN 50121-3-2; (5) diverse supply regulators for each channel |
| **Status** | Partially Mitigated — EMC qualification testing required (Phase 9 hardware validation) |

---

## 5. Software Error Effect Analysis (SEEA)

> **EN 50128 Table A.8 entry 5**: SEEA is HR at SIL 3–4.
> This section contains preliminary SEEA findings for Phase 2 based on known software
> modules (from S4 §4.2 software safety function allocation). A full SEEA update against
> the Software Architecture Specification (SAS) will be performed in Phase 3.

**Software modules (from S4 §4.2)**:
- **SPM**: Speed Monitor
- **DSM**: Door State Machine
- **OBD**: Obstacle Detector
- **FMG**: Fault Manager
- **SKN**: Safety Kernel (cross-channel, departure interlock, safe state)
- **CAN-DRV**: CAN Bus Driver (TCMS communication)

| Module | Fault Mode | Effect (module) | Effect (system) | Safeguard | HAZ link |
|--------|-----------|-----------------|-----------------|-----------|----------|
| SPM | NULL pointer dereference (speed data buffer) | SPM produces no speed output or garbage value | Speed interlock disabled → door may open while moving | Null check guard before buffer access; fail-safe: NULL → assume speed HIGH | SW-HAZ-001, SW-HAZ-007 |
| SPM | Integer overflow (speed value from CAN) | Speed value wraps to 0 or negative | System interprets train as stationary → door open permitted | Range check: valid speed 0–300 km/h; out-of-range → reject + log + treat as UNKNOWN | SW-HAZ-001, SW-HAZ-007 |
| SPM | Stale data (no CAN update within 200 ms) | SPM uses outdated speed reading | Speed interlock may act on incorrect speed | Timestamp validation on every CAN message; timeout → UNKNOWN → assume moving | SW-HAZ-007 |
| DSM | State machine stuck-at (e.g., stuck in OPENING) | Door does not complete transition to OPEN or CLOSED | Door remains in intermediate state; lock cannot be confirmed | Watchdog timeout on state: each state has 2 s max dwell before watchdog triggers safe state | SW-HAZ-003, SW-HAZ-004 |
| DSM | Uninitialized lock status variable | Lock status = undefined on first check | Departure interlock may read uninitialised = "locked" | Explicit initialization to UNKNOWN in startup sequence; MISRA Rule 9.3 enforced | SW-HAZ-003 |
| DSM | Array out-of-bounds (door index) | Wrong door's state read or overwritten | Incorrect lock status reported for platform-side door | Bounds check: door index validated 0 ≤ idx < MAX_DOORS before array access | SW-HAZ-003, SW-HAZ-004 |
| OBD | NULL pointer dereference (obstacle sensor data) | OBD produces no obstacle detection output | Obstacle not detected → door closes on passenger | Null check before sensor read; NULL → treat as OBSTACLE_DETECTED (fail-safe) | SW-HAZ-002 |
| OBD | Integer overflow (force sensor current reading) | Force value overflows; current check bypassed | Excessive closing force not detected | Saturating arithmetic: force value capped at MAX_FORCE before comparison | SW-HAZ-002 |
| OBD | Timing fault (ISR misses 20 ms cycle) | Obstacle detection delayed beyond 100 ms budget | Obstacle response time violation → passenger injury | Execution time monitoring: if OBD task overruns > 25 ms, FMG triggers safe state | SW-HAZ-002 |
| FMG | State machine stuck-at (stuck in FAULT_ACTIVE) | FMG holds safe state permanently even after fault cleared | Passengers trapped — cannot open doors at station | Stuck-state detection: FMG has maximum safe-state dwell time before degraded mode; driver override with TCMS authorization | SW-HAZ-005 |
| FMG | Uninitialized fault counter | Fault counter = random value; spurious or missed fault escalation | Wrong fault management decisions | Explicit initialization to 0 at startup and after safe state recovery | SW-HAZ-005 |
| SKN | Division by zero (duty cycle calculation) | SKN produces NaN or trap | Safety kernel may halt or produce undefined motor command | Non-zero denominator guard before all divisions; MISRA Rule 15.5 enforced | SW-HAZ-001, SW-HAZ-003 |
| SKN | Uninitialized departure interlock flag | Interlock flag may default to "clear" | Train departure permitted before all doors confirmed locked | Flag initialized to LOCKED_UNKNOWN at startup; departure signal output only when flag = ALL_LOCKED | SW-HAZ-003 |
| CAN-DRV | NULL pointer (receive buffer) | CAN message dropped silently | Speed data or TCMS command lost; system acts on stale data | Null check on receive buffer pointer; buffer full → oldest non-safety message discarded; safety messages never dropped | SW-HAZ-007 |
| CAN-DRV | Integer overflow (message sequence counter) | Counter wraps to 0; replayed message accepted | Old or duplicate TCMS command executed | Sequence counter overflow handled: if counter wraps, previous sequence stored and difference checked modulo 256 | SW-HAZ-007 |

---

## 6. Phase 3 FMEA / FTA Findings

> **Phase 3 secondary SAF activity** per EN 50128 §7.1 and EN 50126-1:2017 Annex D.27 (FMEA)
> and Annex D.30 (FTA). Full details in DOC-FMEA-2026-001 and DOC-FTA-2026-001.

### 6.1 FMEA Summary

**Reference**: DOC-FMEA-2026-001 v0.1 — FMEA Report, Software Architecture Failure Mode and Effects Analysis

| Parameter | Result |
|-----------|--------|
| Components analysed | 8 (SKN, SPM, OBD, DSM, FMG, TCI, DGN, HAL) |
| Failure modes analysed | 49 (across all 8 components) |
| Failure modes with RPN ≥ 100 (critical threshold) | **0** — maximum RPN = 48 (FM-OBD-001, FM-FMG-005) |
| Unmitigated single-point failures in SIL 3 functions | **0** |
| SEEA findings validated against SAS Appendix B | **15/15** |
| REQ-SAFE-xxx requirements allocated to components | **21/21** (100%) |
| New hazards identified | **1** (SW-HAZ-011 — see Section 3) |
| FMEA open issues | **3** (OI-FMEA-001, OI-FMEA-002, OI-FMEA-003) |

**FMEA Open Issues**:

| Issue ID | Priority | Description | Owner | Phase |
|----------|----------|-------------|-------|-------|
| OI-FMEA-001 | MEDIUM | SPI transient filter not specified in SAS. SKN must implement N-of-M consecutive failure threshold before declaring persistent SPI fault. New hazard SW-HAZ-011 raised. | DES | Phase 3 / SAS update |
| OI-FMEA-002 | LOW | SPM speed boundary unit test for maximum speed value (300 km/h) should be added to verify the range check does not overflow. | TST | Phase 5 |
| OI-FMEA-003 | **HIGH** | CRC-16 polynomial inconsistency between Channel A and Channel B. If Channel A uses 0x8005 and Channel B uses 0x1021, all cross-channel CRC comparisons will fail permanently, causing permanent safe state. DES must confirm a single CRC polynomial is mandated in SAS and all component specifications. | DES | Phase 3 / SAS update |

**FMEA Architectural Mitigation Update** — all 10 original hazards confirmed mitigated:

| HAZ-ID | Primary FMEA FM-IDs | Mitigation Confirmed |
|--------|---------------------|---------------------|
| SW-HAZ-001 | FM-SPM-001, FM-SPM-002, FM-SKN-001 | ✅ Fail-safe + 2oo2 + dual-channel in SAS Appendix B |
| SW-HAZ-002 | FM-OBD-001, FM-OBD-002, FM-OBD-003 | ✅ Polling + reversal + current backup in SAS Appendix B |
| SW-HAZ-003 | FM-DSM-001, FM-DSM-002, FM-DSM-003, FM-SKN-002 | ✅ 2oo2 + departure interlock in SAS Appendix B |
| SW-HAZ-004 | FM-DSM-004, FM-HAL-001 | ✅ CRC + timeout + fail-safe in SAS Appendix B |
| SW-HAZ-005 | FM-FMG-005, FM-FMG-006 | ✅ Stuck-state detection + driver override in SAS Appendix B |
| SW-HAZ-006 | FM-SKN-004, FM-SKN-005 | ✅ HW watchdog + cross-channel watchdog in SAS Appendix B |
| SW-HAZ-007 | FM-TCI-001, FM-TCI-002 | ✅ CAN timeout → assume moving in SAS Appendix B |
| SW-HAZ-008 | FM-DGN-001, FM-HAL-002 | ✅ CRC + memory check + no dynamic alloc in SAS Appendix B |
| SW-HAZ-009 | FM-DGN-002 | ✅ Debounce + TCMS alert in SAS Appendix B |
| SW-HAZ-010 | FM-FMG-007, FM-SKN-003 | ✅ Authorization + logging + interlock retained in SAS Appendix B |

### 6.2 FTA Summary

**Reference**: DOC-FTA-2026-001 v0.1 — FTA Report, Fault Tree Analysis for Critical Top Events

| Parameter | Result |
|-----------|--------|
| Top events analysed | 5 (FT-001 through FT-005) |
| Top events with unmitigated single-event minimal cut sets | **0** |
| Top events ADEQUATE (no open actions) | **3** (FT-001, FT-004, FT-005) |
| Top events CONDITIONALLY ADEQUATE | **2** (FT-002, FT-003 — pending VER Phase 5) |
| CCF paths bounded | ✅ Yes — β = 0.01 per S4 FTA §2.4 for all paths |
| FTA open issues | **3** (OI-FTA-001, OI-FTA-002, OI-FTA-003) |

**FTA Top Event Results**:

| FT-ID | Top Event | HAZ-ID | Result | Adequacy |
|-------|-----------|--------|--------|----------|
| FT-001 | Door Opens While Train in Motion | SW-HAZ-001 | All single-event MCS eliminated; 2oo2 AND gate requires simultaneous Channel A + Channel B failure | ADEQUATE |
| FT-002 | Door Fails to Lock | SW-HAZ-003 | Single-event MCS: SKN `handle_mismatch()` bypass path requires VER verification | CONDITIONALLY ADEQUATE |
| FT-003 | Obstacle Detection Failure | SW-HAZ-002 | Single-event MCS: OBD `disable_obstacle_detection()` suppression path requires VER verification | CONDITIONALLY ADEQUATE |
| FT-004 | Doors Fail to Enter Safe State | SW-HAZ-006 | All paths require dual hardware watchdog failure; independent hardware watchdogs | ADEQUATE |
| FT-005 | Door Position Sensor Failure | SW-HAZ-004 | All paths require dual sensor failure or CRC failure on both channels | ADEQUATE |

**FTA Open Issues**:

| Issue ID | Priority | Description | Owner | Phase |
|----------|----------|-------------|-------|-------|
| OI-FTA-001 | **CRITICAL** | VER must verify that SKN `handle_mismatch()` function cannot be bypassed on the path to `departure_interlock_ok`. Static analysis must confirm no alternative code path sets the departure interlock clear without going through the mismatch handler. | VER | Phase 5 |
| OI-FTA-002 | **HIGH** | VER must verify that OBD `disable_obstacle_detection()` cannot suppress a live obstacle detection event (i.e., the function can only be called in a non-detection state). Requires control flow analysis. | VER | Phase 5 |
| OI-FTA-003 | **HIGH** | Same CRC polynomial inconsistency as OI-FMEA-003. FTA FT-001 and FT-002 rely on cross-channel CRC comparison to eliminate single-event cut sets. If CRC polynomials differ, these cut sets re-open as single-event MCS. DES must resolve in SAS before Phase 5. | DES | Phase 3 / SAS update |

### 6.3 FMEA/FTA Phase 3 — Actions for Other Roles

| Action | Role | Priority | Status |
|--------|------|----------|--------|
| Resolve CRC polynomial inconsistency (OI-FMEA-003 / OI-FTA-003) — specify single CRC-16 polynomial in SAS and all component specifications | DES | **HIGH** | OPEN |
| Specify SPI transient filter algorithm in SAS (OI-FMEA-001) — N-of-M consecutive failure threshold for SKN | DES | MEDIUM | OPEN |
| Verify SKN `handle_mismatch()` bypass path (OI-FTA-001) via static analysis in Phase 5 | VER | CRITICAL | Deferred to Phase 5 |
| Verify OBD `disable_obstacle_detection()` suppression path (OI-FTA-002) via control flow analysis in Phase 5 | VER | HIGH | Deferred to Phase 5 |
| Add SPM boundary unit test for speed = 300 km/h (OI-FMEA-002) to Component Test Specification in Phase 4 | TST | LOW | Deferred to Phase 4 |

---

## 7. Safety Requirements Summary (HAZ → REQ-SAFE trace)

The following REQ-SAFE-xxx requirements are derived from this hazard analysis and SHALL
be incorporated into the Software Requirements Specification (SRS) by REQ, per EN 50128
§7.2.4.13. REQ must ensure each REQ-SAFE-xxx is tagged with its SIL level in the SRS.

| HAZ-ID | Severity | SIL | REQ-SAFE-xxx | Description (brief) | SRS Section | Status |
|--------|----------|-----|--------------|---------------------|-------------|--------|
| SW-HAZ-001 | 10 | SIL 3 | REQ-SAFE-001 | Speed Monitor: inhibit door open when speed > 5 km/h | §3.2 | Open — for REQ |
| SW-HAZ-001, SW-HAZ-007 | 10 | SIL 3 | REQ-SAFE-002 | Dual-channel speed confirmation before open permission | §3.2 | Open — for REQ |
| SW-HAZ-001, SW-HAZ-007 | 10 | SIL 3 | REQ-SAFE-003 | CAN timeout (200 ms) → assume "moving" → inhibit open | §3.2 | Open — for REQ |
| SW-HAZ-002 | 8 | SIL 3 | REQ-SAFE-004 | Obstacle detection: poll every 20 ms; reversal within 100 ms | §3.3 | Open — for REQ |
| SW-HAZ-002 | 8 | SIL 3 | REQ-SAFE-005 | Obstacle sensor fault → door re-opens (fail-safe) | §3.3 | Open — for REQ |
| SW-HAZ-002 | 8 | SIL 3 | REQ-SAFE-006 | Motor current monitoring: current > 150 N equivalent → reversal | §3.3 | Open — for REQ |
| SW-HAZ-003 | 10 | SIL 3 | REQ-SAFE-007 | Departure interlock: 2oo2 sensor agreement required for LOCKED state | §3.4 | Open — for REQ |
| SW-HAZ-003 | 10 | SIL 3 | REQ-SAFE-008 | "All doors locked" signal withheld until all DSM instances report LOCKED | §3.4 | Open — for REQ |
| SW-HAZ-003, SW-HAZ-004 | 10 | SIL 3 | REQ-SAFE-009 | Cross-channel lock state verification every 20 ms cycle | §3.4 | Open — for REQ |
| SW-HAZ-004, SW-HAZ-008 | 9 | SIL 3 | REQ-SAFE-010 | CRC-16 protection on all safety-critical data structures | §3.5 | Open — for REQ |
| SW-HAZ-004 | 7 | SIL 3 | REQ-SAFE-011 | Position sensor timeout (100 ms) → assume "door open" | §3.5 | Open — for REQ |
| SW-HAZ-005, SW-HAZ-010 | 5–7 | SIL 2 | REQ-SAFE-012 | Safe state trigger requires 2oo2 channel confirmation (except immediate-safety) | §3.6 | Open — for REQ |
| SW-HAZ-005, SW-HAZ-010 | 5–7 | SIL 2 | REQ-SAFE-013 | Selective door disablement: speed interlock remains active; departure interlock remains | §3.7 | Open — for REQ |
| SW-HAZ-006 | 9 | SIL 3 | REQ-SAFE-014 | Hardware watchdog: 50 ms timeout → safe state on both channels | §3.8 | Open — for REQ |
| SW-HAZ-006 | 9 | SIL 3 | REQ-SAFE-015 | Cross-channel software watchdog: Channel B monitors Channel A every 20 ms | §3.8 | Open — for REQ |
| SW-HAZ-007 | 10 | SIL 3 | REQ-SAFE-016 | CRC-16 on all CAN messages; CRC failure = reject + treat as timeout | §3.9 | Open — for REQ |
| SW-HAZ-008 | 9 | SIL 3 | REQ-SAFE-017 | No dynamic memory allocation (MISRA C:2012 Rule 21.3; SAFE-SW-007) | §4.1 | Open — for REQ |
| SW-HAZ-008 | 9 | SIL 3 | REQ-SAFE-018 | Memory integrity check (boot + every 100 ms); mismatch → safe state | §3.8 | Open — for REQ |
| SW-HAZ-009 | 7 | SIL 2 | REQ-SAFE-019 | Emergency release: debounce ≥ 60 ms; alert TCMS within 100 ms | §3.10 | Open — for REQ |
| SW-HAZ-009 | 7 | SIL 2 | REQ-SAFE-020 | Emergency release state latched until maintenance reset; departure inhibited | §3.10 | Open — for REQ |
| SW-HAZ-010 | 7 | SIL 2 | REQ-SAFE-021 | Selective disablement: TCMS authorization required; event logged with door ID + timestamp | §3.7 | Open — for REQ |

**Total derived safety requirements**: 21 (REQ-SAFE-001 through REQ-SAFE-021)  
**SIL 3 requirements**: 15 (REQ-SAFE-001 through REQ-SAFE-011, REQ-SAFE-014 through REQ-SAFE-018)  
**SIL 2 requirements**: 6 (REQ-SAFE-012, REQ-SAFE-013, REQ-SAFE-019 through REQ-SAFE-021)

> **Action for REQ**: Each REQ-SAFE-xxx listed above SHALL be incorporated into the SRS
> (DOC-SRS-2026-001) with its SIL level explicitly tagged. Reference: EN 50128 §7.2.4.13.
> The SRS section numbers above (§3.x) are indicative; REQ shall confirm final placement.

---

## 8. Hazard Closure Record (Phase 7)

> Populated by SAF in Phase 7 per §7.7.4.8(b). All entries must reach CLOSED or
> ACCEPTED-RESIDUAL before the Software Validation Report (item 25) sign-off.

| HAZ-ID | REQ-SAFE-xxx | Test Case (item 24) | Test Result | Closure Status | Date |
|--------|-------------|---------------------|-------------|----------------|------|
| SW-HAZ-001 | REQ-SAFE-001, 002, 003 | [TC-SPM-001 to TC-SPM-015] | [PENDING Phase 7] | OPEN | — |
| SW-HAZ-002 | REQ-SAFE-004, 005, 006 | [TC-OBD-001 to TC-OBD-010] | [PENDING Phase 7] | OPEN | — |
| SW-HAZ-003 | REQ-SAFE-007, 008, 009 | [TC-DSM-001 to TC-DSM-015] | [PENDING Phase 7] | OPEN | — |
| SW-HAZ-004 | REQ-SAFE-009, 010, 011 | [TC-DSM-016 to TC-DSM-020] | [PENDING Phase 7] | OPEN | — |
| SW-HAZ-005 | REQ-SAFE-012, 013 | [TC-FMG-001 to TC-FMG-010] | [PENDING Phase 7] | OPEN | — |
| SW-HAZ-006 | REQ-SAFE-014, 015 | [TC-WDG-001 to TC-WDG-005] | [PENDING Phase 7] | OPEN | — |
| SW-HAZ-007 | REQ-SAFE-001, 003, 016 | [TC-CAN-001 to TC-CAN-008] | [PENDING Phase 7] | OPEN | — |
| SW-HAZ-008 | REQ-SAFE-010, 017, 018 | [TC-MEM-001 to TC-MEM-008] | [PENDING Phase 7] | OPEN | — |
| SW-HAZ-009 | REQ-SAFE-019, 020 | [TC-EMR-001 to TC-EMR-005] | [PENDING Phase 7] | OPEN | — |
| SW-HAZ-010 | REQ-SAFE-012, 013, 021 | [TC-ISO-001 to TC-ISO-008] | [PENDING Phase 7] | OPEN | — |

| SW-HAZ-011 | REQ-SAFE-012, REQ-SAFE-015 | [TC-SPI-001 to TC-SPI-005] | [PENDING Phase 7] | OPEN | — |

---

## 9. System Hazard to Software Hazard Traceability

This table establishes the bidirectional traceability chain required by EN 50128 §7.2.4.13:
System Hazards (S4) → Software Hazards (this log) → SRS Safety Requirements.

**Traceability coverage**: 9 of 9 system hazards traced (HAZ-007 is SIL 1/Tolerable —
service disruption only; no dedicated software safety requirement derived).
**Traceability completeness**: 100% of safety-relevant system hazards have ≥ 1 software
hazard entry and ≥ 1 REQ-SAFE-xxx in SRS Section 3.

| System Hazard (S4) | Severity (S4) | SIL (S4) | Software Hazard(s) | SRS Safety Requirements |
|-------------------|---------------|----------|--------------------|------------------------|
| HAZ-001: Train departs with door open | Catastrophic | SIL 3 | SW-HAZ-003, SW-HAZ-004 | REQ-SAFE-007 to 011 |
| HAZ-002: Door closes on passenger | Critical | SIL 3 | SW-HAZ-002 | REQ-SAFE-004 to 006 |
| HAZ-003: Door opens while moving | Catastrophic | SIL 3 | SW-HAZ-001, SW-HAZ-007 | REQ-SAFE-001 to 003, REQ-SAFE-016 |
| HAZ-004: Obstacle detected but door continues | Critical | SIL 3 | SW-HAZ-002 | REQ-SAFE-004 to 006 |
| HAZ-005: False door-locked signal | Catastrophic | SIL 3 | SW-HAZ-003, SW-HAZ-004, SW-HAZ-008 | REQ-SAFE-007 to 011, REQ-SAFE-017 to 018 |
| HAZ-006: Door fails to open at station | Marginal | SIL 2 | SW-HAZ-005 | REQ-SAFE-012 to 013 |
| HAZ-007: Door fails to close (service) | Marginal | SIL 1 | (Operational — no dedicated SW hazard; addressed by FMG fault logging) | — |
| HAZ-008: Emergency release spurious | Critical | SIL 2 | SW-HAZ-009 | REQ-SAFE-019 to 020 |
| HAZ-009: DCU software fault — loss of control | Critical | SIL 2 | SW-HAZ-006, SW-HAZ-008, SW-HAZ-010 | REQ-SAFE-013 to 015, REQ-SAFE-017 to 018, REQ-SAFE-021 |

> **Note on HAZ-007**: S4 classifies this as SIL 1/Tolerable. The software failure mode
> (door motor fault causing failure to close) is a service disruption, not a safety hazard.
> It is addressed by FMG fault logging (REQ-SAFE-013 logging element) and operational
> procedures. No dedicated SIL-bearing software safety requirement derived.

### 9.1 H-001..H-010 to SW-HAZ Cross-Reference (Phase 2 Alignment)

The user-facing hazard IDs (H-001..H-010) used in Phase 2 planning documents correspond
to the following software hazard IDs in this Hazard Log. The SW-HAZ numbering reflects the
mapping from system-level S4 hazards to software-specific hazard analyses.

| Phase 2 Planning ID | SW-HAZ ID (this log) | Description | SIL | REQ-SAFE-xxx |
|--------------------|----------------------|-------------|-----|-------------|
| H-001 (Door closes on passenger) | SW-HAZ-002 | Door closes on passenger — obstacle not detected | SIL 3 | REQ-SAFE-004, 005, 006 |
| H-002 (Door opens during train movement) | SW-HAZ-001 | Door opens while train in motion | SIL 3 | REQ-SAFE-001, 002, 003 |
| H-003 (Door fails to open at station) | SW-HAZ-005 | Software commands spurious safe state — door locked at station | SIL 2 | REQ-SAFE-012, 013 |
| H-004 (Multiple doors out of sync) | SW-HAZ-003 | False door lock indication allows departure | SIL 3 | REQ-SAFE-007, 008, 009 |
| H-005 (Door sensor failure undetected) | SW-HAZ-004 | Loss of door position indication | SIL 3 | REQ-SAFE-009, 010, 011 |
| H-006 (Emergency release fails) | SW-HAZ-009 | Emergency release mishandled by software | SIL 2 | REQ-SAFE-019, 020 |
| H-007 (Door control timing failure) | SW-HAZ-006 | Software watchdog failure — DCU hang not detected | SIL 3 | REQ-SAFE-014, 015 |
| H-008 (Communication loss with TCMS) | SW-HAZ-007 | CAN bus speed data loss — TCMS communication failure | SIL 3 | REQ-SAFE-001, 003, 016 |
| H-009 (Door position feedback incorrect) | SW-HAZ-008 | Memory corruption corrupts safety-critical data | SIL 3 | REQ-SAFE-010, 017, 018 |
| H-010 (Power supply failure affects safety) | SW-HAZ-010 | Selective door disablement misuse — bypass of safety interlock | SIL 2 | REQ-SAFE-012, 013, 021 |

> **Cross-reference note**: The SW-HAZ IDs trace to S4 system hazard entries
> (DOC-SYS-SAF-2026-001 §2.1). The H-001..H-010 planning IDs are aligned via this table.
> REQ shall use SW-HAZ IDs and REQ-SAFE-xxx IDs when authoring SRS §3 (safety requirements).

### 9.2 Phase 2 REQ Coordination Record

**Phase 2 SAF → REQ coordination** (per EN 50128 §7.2.4.13):

| Action | Status | Details |
|--------|--------|---------|
| SAF provides REQ-SAFE-001 to REQ-SAFE-021 to REQ | ✅ Complete | All 21 safety requirements listed in Section 7 of this document |
| SIL tags confirmed for each REQ-SAFE-xxx | ✅ Complete | 15 × SIL 3, 6 × SIL 2 — see Section 7 table |
| SRS section assignments communicated to REQ | ✅ Complete | §3.2 through §4.1 indicative placements noted in Section 7 |
| REQ to confirm final SRS placement | ⏳ Pending | REQ to confirm final §-numbers in SRS DOC-SRS-2026-001 |
| SIL assignment reconciliation with SRS | ⏳ Pending | REQ must ensure each REQ-SAFE-xxx carries its SIL level per §7.2.4.13 |

**Action required (REQ)**: Incorporate REQ-SAFE-001 through REQ-SAFE-021 into SRS
(DOC-SRS-2026-001) Section 3 with explicit SIL tags. Confirm final §-numbers back to SAF
for Hazard Log update. Reference: EN 50128 §7.2.4.13.

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

## Appendix C: SIL Assignment Rationale

All SIL assignments in this Hazard Log are derived from system-level analysis in
DOC-SYS-SAF-2026-001 and the EN 50126-2:2017 risk methodology. The following
rationale applies:

**SIL 3 assignments (SW-HAZ-001, 002, 003, 004, 006, 007, 008)**:
- All trace to S4 system hazards classified as "Intolerable" or "Unacceptable" risk
  (catastrophic or critical severity × occasional or more frequent)
- THR targets ≥ 10⁻⁷/hr to < 10⁻⁶/hr → SIL 3 per EN 50126-2 Table 8
- Software is the primary or significant contributor to the hazardous event
- System SIL cap is SIL 3 — no hazard exceeds the project ceiling ✅
- No SIL 4 assignment is needed or justified for this system

**SIL 2 assignments (SW-HAZ-005, 009, 010, 011)**:
- Trace to S4 hazards classified "Tolerable (ALARP)" (marginal or critical × remote)
- THR targets ≥ 10⁻⁶/hr to < 10⁻⁵/hr → SIL 2
- Software role is monitoring, reporting, or degraded-mode management (not primary
  safety control)
- SW-HAZ-011: Moderate severity (5) × Remote frequency (3) → Risk Level 15 → SIL 2 ✅
- Meets SIL 2 ≤ SIL 3 project ceiling ✅

**No SIL > 3 requirement**: No escalation to PM required. All hazards are within the
SIL 3 project envelope.

---

**END OF HAZARD LOG**

*Document ID*: DOC-HAZLOG-2026-001 v0.3  
*Phase 2 update*: 2026-04-02 — SIL assignments confirmed; 21 REQ-SAFE-xxx requirements linked; H-001..H-010 cross-reference table added; REQ coordination record established  
*Phase 3 update*: 2026-04-02 — FMEA (DOC-FMEA-2026-001 v0.1) and FTA (DOC-FTA-2026-001 v0.1) completed; 49 failure modes; 5 fault trees; 1 new hazard (SW-HAZ-011); 15/15 SEEA validated; 21/21 REQ-SAFE-xxx allocated; Phase 3 findings in Section 6  
*Next update*: Phase 7 — Hazard Closure Confirmation (§7.7.4.8(b))  
*Maintained by*: SAF (Safety Engineer), CM-controlled per §6.6  
*Review chain*: VER (1st), VAL (2nd) in Track B per WORKFLOW.md
