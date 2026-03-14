# Hazard Analysis and Risk Assessment Workflow

**EN 50128 Compliance**: Section 7.1 (Software Requirements), Section 6.3 (Software Analysis)  
**EN 50126 Compliance**: Section 6.3 (Risk Assessment), Life Cycle Phase 3  
**SIL Applicability**: ALL (0, 1, 2, 3, 4) - **MANDATORY for all SIL levels**  
**Workflow Type**: Safety Analysis  
**Prerequisites**: System Definition (EN 50126 Phase 2), Operational Context

---

## Purpose

This workflow provides systematic guidance for **hazard identification**, **risk assessment**, **SIL determination**, and **Hazard Log management** per EN 50126-1:2017 Section 6.3 and EN 50128:2011 Section 7.1. The Hazard Log is **MANDATORY for ALL SIL levels** and forms the foundation for deriving safety requirements and determining Safety Integrity Levels.

**Key Activities**:
1. Systematic hazard identification (preliminary, system-level, software-level)
2. Risk analysis (consequence severity, probability of occurrence)
3. Risk evaluation (risk matrix, ALARP assessment)
4. SIL determination per EN 50126-2 (Tolerable Hazard Rate)
5. Hazard Log creation, baseline, and lifecycle management
6. Traceability from hazards to safety requirements

---

## EN 50126 Risk Assessment Process

**EN 50126-1:2017 Section 6.3** defines the risk assessment process:

```
┌─────────────────────────────────────────────────────────────────────┐
│                     RISK ASSESSMENT (Phase 3)                        │
├─────────────────────────────────────────────────────────────────────┤
│                                                                       │
│  ┌────────────────────────────────────────────────────────────────┐ │
│  │                    RISK ANALYSIS                                │ │
│  │  - Hazard identification                                        │ │
│  │  - Consequence analysis (severity)                              │ │
│  │  - Probability estimation (frequency/likelihood)                │ │
│  │  - Broadly acceptable risk decision                             │ │
│  └─────────────────┬──────────────────────────────────────────────┘ │
│                    │                                                  │
│                    ▼                                                  │
│           Is risk broadly acceptable?                                 │
│                    │                                                  │
│           NO ──────┴──────► Apply Risk Acceptance Principle (RAP):   │
│                              - Code of Practice (CoP)                 │
│                              - Reference System Comparison            │
│                              - Explicit Risk Estimation (ERE)         │
│                    │                                                  │
│                    ▼                                                  │
│  ┌────────────────────────────────────────────────────────────────┐ │
│  │                   RISK EVALUATION                               │ │
│  │  - Compare risk against acceptance criteria (RAC)               │ │
│  │  - Determine if risk is tolerable or ALARP                      │ │
│  │  - Specify safety requirements (risk reduction measures)        │ │
│  │  - Determine SIL level per EN 50126-2                           │ │
│  └────────────────────────────────────────────────────────────────┘ │
│                                                                       │
└─────────────────────────────────────────────────────────────────────┘
                             │
                             ▼
               ┌─────────────────────────────┐
               │   HAZARD LOG (Baseline)     │
               │ - All identified hazards    │
               │ - Risk classifications      │
               │ - SIL determinations        │
               │ - Safety requirements       │
               │ - Risk reduction measures   │
               └─────────────────────────────┘
```

**Risk Acceptance Principles (RAP)**:
- **Code of Practice (CoP)**: Apply industry-standard practices (e.g., MISRA C, defensive programming)
- **Reference System Comparison**: Compare with similar proven system
- **Explicit Risk Estimation (ERE)**: Quantitative or qualitative risk estimation (severity × probability)

---

## Section 1: Preliminary Hazard Analysis (PHA)

**Objective**: Identify high-level hazards early in the lifecycle (Concept phase) to inform system definition.

**Timing**: Life Cycle Phase 1-2 (Concept, System Definition)

### 1.1 PHA Process

**Step 1: Define System Boundaries**

Clearly define what is included in the system under consideration:

```markdown
## System Boundary Definition

**System**: Train Control and Monitoring System (TCMS)

**Included**:
- Train control computer (TCC) with C software
- Input/output interfaces (sensors, actuators)
- Communication networks (MVB, Ethernet)
- Human-Machine Interface (HMI)

**Excluded** (interfaces only):
- Traction control (separate system, interface via MVB)
- Brake control (separate system, interface via MVB)
- Door control (separate system, interface via discrete I/O)

**Operational Context**:
- High-speed passenger trains (up to 350 km/h)
- Urban metro (up to 100 km/h)
- Operating environment: -40°C to +70°C, vibration, EMI
```

**Step 2: Identify Preliminary Hazards**

Use systematic techniques to identify hazards:

**Technique 1: Functional Decomposition**

Break system into functions and identify hazard for each function:

| Function | Potential Hazard | Consequence |
|----------|------------------|-------------|
| Train speed monitoring | Speed exceeds safe limit | Derailment, collision |
| Door control interlock | Doors open while train moving | Passenger fall, injury/death |
| Brake command | Brake fails to apply when commanded | Collision, derailment |
| Emergency brake | Emergency brake fails to activate | Collision, derailment |
| Alarm monitoring | Critical alarm not displayed | Delayed response, hazard escalation |

**Technique 2: "What-If" Analysis**

Ask "what if" questions for each system element:

```markdown
## What-If Analysis: Train Speed Monitoring

**Q**: What if the speed sensor fails?
**A**: Speed reading is incorrect or unavailable → Train may exceed speed limit → Hazard

**Q**: What if the speed calculation has a software bug?
**A**: Speed is calculated incorrectly → Train control decisions based on wrong speed → Hazard

**Q**: What if the communication link between sensor and TCC fails?
**A**: Speed data not received → Train may operate without speed monitoring → Hazard

**Q**: What if the TCC loses power during operation?
**A**: All monitoring functions lost → Train operates without safety monitoring → Hazard
```

**Technique 3: Checklist-Based Identification**

Use railway-specific hazard checklists:

**Generic Railway Hazards**:
- Collision (train-to-train, train-to-obstacle)
- Derailment (speed, track condition, wheel-rail interface)
- Fire (electrical, mechanical)
- Passenger injury (doors, acceleration, emergency evacuation)
- Electric shock (high voltage equipment)
- Environmental (extreme temperature, flooding, earthquake)

**Software-Specific Hazards** (EN 50128 Section 7.1):
- Incorrect output (wrong command to actuator)
- Delayed output (timing violation)
- Missing output (no command when required)
- Unexpected output (spurious command)
- Data corruption (memory error, communication error)

### 1.2 Preliminary Hazard Log

Create preliminary Hazard Log with initial hazard list:

```markdown
# Preliminary Hazard Log (PHA)

**Project**: Train Control and Monitoring System (TCMS)  
**Date**: 2026-03-14  
**Phase**: Phase 1-2 (Concept, System Definition)  
**Status**: Preliminary

| Hazard ID | Hazard Description | Potential Consequence | Severity | Likelihood | Risk Level |
|-----------|-------------------|----------------------|----------|------------|-----------|
| HAZ-001 | Train speed exceeds safe limit due to incorrect speed calculation | Derailment, passenger injury/death | Catastrophic | Remote | High |
| HAZ-002 | Doors open while train moving due to interlock failure | Passenger fall, injury/death | Catastrophic | Improbable | High |
| HAZ-003 | Emergency brake fails to activate due to software error | Collision, passenger injury/death | Catastrophic | Remote | High |
| HAZ-004 | Critical alarm not displayed due to HMI software bug | Delayed response, hazard escalation | Critical | Occasional | Medium |
| HAZ-005 | Train control computer loses power during operation | Loss of all safety functions | Catastrophic | Improbable | High |
| HAZ-006 | Communication link failure between TCC and safety devices | Loss of safety monitoring | Critical | Occasional | Medium |
| HAZ-007 | Memory corruption in safety-critical software | Unpredictable behavior | Catastrophic | Remote | High |
| HAZ-008 | Software timing violation in real-time control loop | Delayed or missed safety action | Critical | Occasional | Medium |
```

**Severity Categories** (EN 50126-2:2017 Table 2):
- **Catastrophic**: Death, multiple severe injuries, major system loss
- **Critical**: Single severe injury, major injury to multiple persons, significant system loss
- **Marginal**: Minor injury, minor system damage
- **Negligible**: No injury, minimal system damage

**Likelihood Categories** (EN 50126-2:2017 Table 3):
- **Frequent**: Likely to occur frequently (> 10^-3 per hour)
- **Probable**: Will occur several times in system lifetime (10^-4 to 10^-3 per hour)
- **Occasional**: Likely to occur sometime in system lifetime (10^-5 to 10^-4 per hour)
- **Remote**: Unlikely, but possible in system lifetime (10^-6 to 10^-5 per hour)
- **Improbable**: Very unlikely, but conceivable (10^-7 to 10^-6 per hour)
- **Incredible**: Extremely unlikely (< 10^-7 per hour)

**Risk Matrix** (Severity × Likelihood → Risk Level):

```
                    LIKELIHOOD
         Frequent  Probable  Occasional  Remote  Improbable  Incredible
       ┌─────────┬─────────┬───────────┬───────┬───────────┬──────────┐
   C   │  HIGH   │  HIGH   │   HIGH    │ HIGH  │   HIGH    │  MEDIUM  │ Catastrophic
   a   ├─────────┼─────────┼───────────┼───────┼───────────┼──────────┤
   t   │  HIGH   │  HIGH   │   HIGH    │ MEDIUM│   MEDIUM  │   LOW    │ Critical
   a   ├─────────┼─────────┼───────────┼───────┼───────────┼──────────┤
   s   │  HIGH   │  MEDIUM │   MEDIUM  │  LOW  │    LOW    │   LOW    │ Marginal
   t   ├─────────┼─────────┼───────────┼───────┼───────────┼──────────┤
   r   │ MEDIUM  │   LOW   │    LOW    │  LOW  │    LOW    │   LOW    │ Negligible
   o   └─────────┴─────────┴───────────┴───────┴───────────┴──────────┘
   p
   h
   i
   c
       SEVERITY

HIGH: Unacceptable, immediate risk reduction required
MEDIUM: ALARP (As Low As Reasonably Practicable) - justify if not reduced further
LOW: Broadly acceptable, minimal additional measures required
```

---

## Section 2: System-Level Hazard Analysis

**Objective**: Detailed hazard identification and analysis at system level, including hardware and software interactions.

**Timing**: Life Cycle Phase 3 (Risk Analysis and Evaluation)

### 2.1 Systematic Hazard Identification Techniques

**Technique 1: Failure Modes and Effects Analysis (FMEA)**

See `fmea-workflow.md` for detailed FMEA process.

FMEA identifies hazards by analyzing failure modes of each component:

**Example: Speed Sensor FMEA (High-Level)**

| Component | Failure Mode | Local Effect | System Effect | Severity | Occurrence | Detection | RPN |
|-----------|--------------|--------------|---------------|----------|------------|-----------|-----|
| Speed Sensor | Sensor fails high | TCC receives incorrect high speed | Train may be slowed unnecessarily (safe failure) | Marginal | Remote | High (sensor monitoring) | Low |
| Speed Sensor | Sensor fails low | TCC receives incorrect low speed | Train may exceed speed limit (dangerous failure) | Catastrophic | Remote | Medium (plausibility check) | **High** |
| Speed Sensor | Sensor stuck | TCC receives constant value | Speed changes not detected | Critical | Occasional | Medium (rate-of-change check) | Medium |
| Speed Sensor | Sensor intermittent | TCC receives erratic values | Speed monitoring unreliable | Critical | Occasional | Medium (data quality check) | Medium |

**Hazards Identified**:
- **HAZ-001**: Train speed exceeds safe limit due to sensor fails low (FMEA Component: Speed Sensor, Failure Mode: Fails low)

**Technique 2: Fault Tree Analysis (FTA)**

See `fta-workflow.md` for detailed FTA process.

FTA starts with top event (hazard) and identifies causal factors:

**Example: Fault Tree for "Train Exceeds Speed Limit" (Simplified)**

```
                       TOP EVENT
                 Train Exceeds Speed Limit
                          │
                ┌─────────┴─────────┐
                │ OR Gate           │
        ┌───────┴───────┬───────────┴────────┬─────────────┐
        │               │                    │             │
   Speed Sensor    Speed Calculation   Communication   TCC Software
   Failure         Error              Failure         Timing Error
        │               │                    │             │
   ┌────┴────┐     ┌────┴────┐         ┌────┴────┐   ┌────┴────┐
   │ AND     │     │ OR      │         │ AND     │   │ OR      │
   │         │     │         │         │         │   │         │
 Sensor  No  │   Algorithm Software  │ Link   No  │ Real-time Watchdog
 Fails  Detec│   Bug      Data      │ Down   Detec│ Violation Failure
        tion │            Corrupt.  │        tion │
             │                       │             │
        Basic Events              Basic Events  Basic Events

Basic Events (Leaves):
- Sensor Fails: Hardware failure (λ = 10^-6/hr)
- No Detection: Software monitoring fails (λ = 10^-7/hr)
- Algorithm Bug: Software design error (systematic)
- Software Data Corruption: Memory error (λ = 10^-8/hr)
- Link Down: Communication failure (λ = 10^-5/hr)
- Real-time Violation: Timing deadline missed (systematic or hardware)
- Watchdog Failure: Watchdog timer fails (λ = 10^-7/hr)
```

**Hazards Identified**:
- **HAZ-001**: Train exceeds speed limit (TOP EVENT from FTA)

**Technique 3: Hazard and Operability Study (HAZOP)**

HAZOP uses guide words to explore deviations:

**HAZOP Guide Words**:
- **NO/NOT**: Complete negation (e.g., no signal, not operating)
- **MORE**: Quantitative increase (e.g., higher speed, longer duration)
- **LESS**: Quantitative decrease (e.g., lower voltage, shorter time)
- **AS WELL AS**: Qualitative increase (e.g., additional signal, extra step)
- **PART OF**: Qualitative decrease (e.g., signal missing component)
- **REVERSE**: Opposite effect (e.g., acceleration instead of braking)
- **OTHER THAN**: Complete substitution (e.g., wrong signal, incorrect data)
- **EARLY**: Timing deviation (e.g., command issued too early)
- **LATE**: Timing deviation (e.g., command issued too late)

**Example: HAZOP for "Train Speed Control" Function**

| Function | Guide Word | Deviation | Cause | Consequence | Hazard |
|----------|------------|-----------|-------|-------------|--------|
| Speed Control | NO | No speed control command | Software crash, power loss | Train operates without speed limiting | HAZ-001 |
| Speed Control | MORE | Speed limit set too high | Configuration error, software bug | Train exceeds safe speed for track | HAZ-001 |
| Speed Control | LESS | Speed limit set too low | Configuration error | Train slows unnecessarily (availability issue) | - |
| Speed Control | REVERSE | Acceleration command instead of brake | Software bug (sign error) | Train accelerates when should brake | HAZ-009 |
| Speed Control | LATE | Speed control command delayed | Real-time timing violation | Train exceeds limit before control applied | HAZ-008 |
| Speed Control | OTHER THAN | Wrong speed limit applied | GPS error, track database error | Train uses limit for wrong track section | HAZ-010 |

**New Hazards Identified**:
- **HAZ-009**: Train accelerates when should brake due to software sign error
- **HAZ-010**: Train uses incorrect speed limit due to wrong track data

### 2.2 Software-Specific Hazard Analysis

**EN 50128 Section 7.1** requires software hazard analysis to identify hazards arising from:
- Software failures (incorrect output, timing violations)
- Software-hardware interaction failures
- Software-human interface failures

**Technique: Software Hazard Analysis Checklist**

For each safety-critical software function, evaluate:

| Hazard Category | Question | Hazard Identified? |
|-----------------|----------|-------------------|
| **Incorrect Output** | Can software produce wrong value/command? | HAZ-001, HAZ-009 |
| **Missing Output** | Can software fail to produce required output? | HAZ-003 (emergency brake not activated) |
| **Unexpected Output** | Can software produce spurious output? | HAZ-011 (spurious brake command) |
| **Delayed Output** | Can software miss timing deadline? | HAZ-008 (timing violation) |
| **Data Corruption** | Can software data be corrupted? | HAZ-007 (memory corruption) |
| **Interface Failure** | Can software-hardware interface fail? | HAZ-006 (communication failure) |
| **Resource Exhaustion** | Can software run out of memory/CPU? | HAZ-012 (CPU overload, watchdog reset) |
| **State Machine Error** | Can software enter invalid state? | HAZ-013 (invalid operational mode) |

**New Hazards Identified**:
- **HAZ-011**: Spurious brake command causes unintended braking (passenger injury risk)
- **HAZ-012**: CPU overload causes watchdog reset (loss of all monitoring)
- **HAZ-013**: Software enters invalid state (unpredictable behavior)

### 2.3 Consequence Analysis

For each identified hazard, analyze the consequences:

**Example: HAZ-001 - Train Exceeds Speed Limit**

```markdown
## HAZ-001: Train Exceeds Speed Limit

### Hazard Description
The train speed exceeds the safe limit for the current track section due to incorrect speed calculation, sensor failure, or software error.

### Causal Factors
1. Speed sensor fails low (hardware failure)
2. Speed calculation algorithm has bug (software design error)
3. Speed monitoring software disabled or failed (software failure)
4. Communication link failure (sensor to TCC)
5. Real-time timing violation in speed monitoring loop (software timing error)

### Immediate Consequences
- Train speed not limited by software
- No automatic braking applied
- Driver may not be alerted (depends on HMI software)

### Escalation Consequences
- Train enters curve or restricted area at excessive speed
- Derailment due to excessive lateral forces
- Collision with another train or obstacle
- Passenger injury or death (multiple casualties possible)

### Worst-Case Scenario
- High-speed passenger train (300 km/h) enters 50 km/h speed restriction zone
- Derailment at high speed on embankment or bridge
- Multiple fatalities (> 10 deaths)

### Severity Classification
**Catastrophic** per EN 50126-2 Table 2:
- Multiple fatalities likely
- Major system loss (train destroyed, infrastructure damaged)
- Meets criteria for Catastrophic severity

### Mitigation Measures (Existing)
1. Dual redundant speed sensors (sensor fails detected by comparison)
2. Plausibility checks in software (rate-of-change, acceleration limits)
3. Driver awareness (driver can manually brake)
4. ATP (Automatic Train Protection) system as backup (if installed)

### Residual Risk Assessment
Even with mitigations, residual risk remains:
- Common cause failure (both sensors fail simultaneously due to EMI)
- Software bug in plausibility checks
- Driver incapacitated or distracted
- ATP system disabled or failed

**Preliminary Risk Classification**: HIGH (Catastrophic severity, Remote likelihood)
```

---

## Section 3: Risk Assessment and SIL Determination

**Objective**: Evaluate each hazard's risk, determine tolerability, and assign Safety Integrity Level (SIL).

**Timing**: Life Cycle Phase 3 (Risk Analysis and Evaluation)

### 3.1 Risk Analysis Process

For each hazard in Hazard Log:

**Step 1: Determine Consequence Severity**

Use EN 50126-2 Table 2 severity categories:

| Severity | Safety Consequences | Example Hazards |
|----------|---------------------|-----------------|
| **Catastrophic** | Death, multiple severe injuries | HAZ-001, HAZ-002, HAZ-003, HAZ-005, HAZ-007, HAZ-009 |
| **Critical** | Single severe injury, multiple major injuries | HAZ-004, HAZ-006, HAZ-008, HAZ-011, HAZ-013 |
| **Marginal** | Minor injury, minor system damage | HAZ-014 (non-critical alarm missed) |
| **Negligible** | No injury, minimal system effect | HAZ-015 (cosmetic HMI issue) |

**Step 2: Estimate Probability of Occurrence**

Two approaches:

**Approach A: Qualitative Likelihood Estimation**

Based on expert judgment and historical data:

| Likelihood | Description | Estimated Frequency |
|------------|-------------|---------------------|
| Frequent | Will occur frequently | > 10^-3 per hour |
| Probable | Will occur several times | 10^-4 to 10^-3 per hour |
| Occasional | May occur sometime | 10^-5 to 10^-4 per hour |
| Remote | Unlikely but possible | 10^-6 to 10^-5 per hour |
| Improbable | Very unlikely | 10^-7 to 10^-6 per hour |
| Incredible | Extremely unlikely | < 10^-7 per hour |

**Approach B: Quantitative Probability Estimation**

Calculate from component failure rates (for hardware) and software reliability estimates:

**Example: HAZ-001 - Train Exceeds Speed Limit (Quantitative)**

```
P(HAZ-001) = P(Speed Sensor Fails) × P(Software Monitoring Fails to Detect)
           = λ_sensor × P_software_no_detect
           = 10^-6 /hr × 0.01 (1% chance software fails to detect)
           = 10^-8 /hr

Category: Improbable (10^-7 to 10^-6 per hour)
```

**Step 3: Risk Evaluation (Risk Matrix)**

Combine severity and likelihood to determine risk level:

**Example: HAZ-001 Risk Evaluation**

- **Severity**: Catastrophic
- **Likelihood**: Improbable (10^-8 /hr with mitigations)
- **Risk Level** (from Risk Matrix): **HIGH**

**Risk Matrix Result**:
```
Catastrophic + Improbable = HIGH RISK
```

**Decision**: Risk is **NOT broadly acceptable** → Requires risk reduction measures and SIL determination.

### 3.2 SIL Determination per EN 50126-2

**EN 50126-2:2017 Section 10** defines Safety Integrity Levels based on **Tolerable Hazard Rate (THR)**.

**SIL Assignment Table** (EN 50126-2 Table 8):

| SIL | Tolerable Hazard Rate (THR) | Description |
|-----|----------------------------|-------------|
| **4** | 10^-9 to 10^-8 per hour | Catastrophic consequences, very stringent |
| **3** | 10^-8 to 10^-7 per hour | Critical consequences, stringent |
| **2** | 10^-7 to 10^-6 per hour | Marginal consequences, moderate |
| **1** | 10^-6 to 10^-5 per hour | Negligible consequences, basic |
| **0** | > 10^-5 per hour | Non-safety, no specific safety requirements |

**SIL Determination Process**:

1. **Determine Required THR**: Based on risk acceptance criteria and ALARP principle
2. **Calculate Hazard Rate**: From existing system (if applicable) or estimate
3. **Calculate Required Risk Reduction**: THR / Current Hazard Rate = Risk Reduction Factor
4. **Allocate Risk Reduction**: Across layers (inherent safety, protective measures, software SIL)
5. **Assign SIL**: Based on software contribution to risk reduction

**Example: HAZ-001 SIL Determination**

```markdown
## SIL Determination for HAZ-001

### Step 1: Determine Required THR

**Hazard**: Train exceeds speed limit (Catastrophic consequences)

**Risk Acceptance Criteria**:
- Railway duty holder requirement: Catastrophic hazard rate < 10^-8 per hour per train
- ALARP demonstration required if > 10^-9 per hour

**Required THR**: 10^-8 per hour (SIL 3 or 4)

### Step 2: Estimate Current Hazard Rate

**Without Software Safety Measures**:
- Speed sensor failure rate: λ = 10^-6 /hr
- No software monitoring: P(no detection) = 1.0
- Hazard rate = 10^-6 /hr (UNACCEPTABLE)

**With Hardware Mitigations Only** (dual sensors, voting):
- Dual redundant sensors with voter: λ = (10^-6)^2 / (2 × 10^6 hrs MTTR) ≈ 10^-9 /hr (common cause failures neglected)
- Still requires software monitoring for completeness

### Step 3: Calculate Required Risk Reduction

**Risk Reduction Factor** = Current Hazard Rate / THR
                         = 10^-6 /hr / 10^-8 /hr
                         = 100

**Interpretation**: Need 100× risk reduction to achieve tolerable risk level.

### Step 4: Allocate Risk Reduction

**Layered Safety Approach**:

| Layer | Measure | Risk Reduction | Residual Rate |
|-------|---------|----------------|---------------|
| **Layer 1**: Inherent Safety | Use reliable sensors, fail-safe design | 10× | 10^-7 /hr |
| **Layer 2**: Hardware Protection | Dual redundant sensors, 2oo2 voting | 10× | 10^-8 /hr |
| **Layer 3**: Software Safety (TCMS) | Speed monitoring, plausibility checks | 10× | 10^-9 /hr |
| **Layer 4**: Independent Protection | ATP (Automatic Train Protection) | 10× | 10^-10 /hr |

**Software Contribution**: 10× risk reduction required from TCMS software.

### Step 5: Assign SIL

**Software SIL** (EN 50128):
- Software must achieve 10× risk reduction → Probability of dangerous failure on demand (PFD) < 0.1
- For continuous operation: Software failure rate < 10^-7 /hr
- Per EN 50126-2 Table 8: **SIL 3** (10^-8 to 10^-7 /hr)

**SIL Assignment**: **SIL 3**

**Justification**:
- Catastrophic consequences (multiple fatalities possible)
- Software contributes significantly to risk reduction (Layer 3)
- Independent protection layer exists (ATP as Layer 4)
- SIL 3 requirements achievable with MISRA C, 100% branch coverage, defensive programming

**Alternative Consideration**:
- If ATP not available or software is sole protection: Consider **SIL 4**
- SIL 4 would require formal methods, 100% MC/DC coverage, T3 tool qualification
```

**SIL Determination Summary for All Hazards**:

| Hazard ID | Hazard Description | Severity | THR | Software SIL | Justification |
|-----------|-------------------|----------|-----|-------------|---------------|
| HAZ-001 | Train exceeds speed limit | Catastrophic | 10^-8 /hr | **SIL 3** | Software contributes 10× risk reduction, ATP available |
| HAZ-002 | Doors open while train moving | Catastrophic | 10^-8 /hr | **SIL 4** | Software is primary protection, no independent layer |
| HAZ-003 | Emergency brake fails to activate | Catastrophic | 10^-8 /hr | **SIL 3** | Software contributes, mechanical backup exists |
| HAZ-004 | Critical alarm not displayed | Critical | 10^-7 /hr | **SIL 2** | Driver can identify issue, lower consequences |
| HAZ-005 | TCC power loss during operation | Catastrophic | 10^-8 /hr | **SIL 0** | Hardware failure, software not causal |
| HAZ-006 | Communication link failure | Critical | 10^-7 /hr | **SIL 2** | Fail-safe protocol, detection mechanisms |
| HAZ-007 | Memory corruption in software | Catastrophic | 10^-8 /hr | **SIL 3** | ECC memory + software checks |
| HAZ-008 | Software timing violation | Critical | 10^-7 /hr | **SIL 2** | Watchdog monitoring, timing analysis |
| HAZ-009 | Acceleration instead of brake | Catastrophic | 10^-8 /hr | **SIL 3** | Software logic error, detection by monitoring |
| HAZ-011 | Spurious brake command | Critical | 10^-7 /hr | **SIL 2** | Passenger discomfort, no severe injury |
| HAZ-012 | CPU overload, watchdog reset | Catastrophic | 10^-8 /hr | **SIL 3** | Software resource management critical |
| HAZ-013 | Software invalid state | Critical | 10^-7 /hr | **SIL 2** | State machine monitoring, recovery logic |

---

## Section 4: Hazard Log Management

**Objective**: Create, baseline, maintain, and close out the Hazard Log throughout the software lifecycle.

**Timing**: Created in Phase 2-3, Baselined at Gate 1 (Requirements Complete), Updated throughout lifecycle, Closed at deployment.

### 4.1 Hazard Log Structure

**Hazard Log Template** (Markdown Format):

```markdown
# Hazard Log - Train Control and Monitoring System (TCMS)

**Project**: TCMS Software Development  
**System**: Train Control and Monitoring System  
**Document ID**: DOC-SAF-HAZLOG-001  
**Version**: 2.0 (Baseline)  
**Date**: 2026-03-14  
**SIL Level**: SIL 3 (highest hazard SIL)  
**Status**: Baselined

---

## Document Control

| Field | Value |
|-------|-------|
| Document ID | DOC-SAF-HAZLOG-001 |
| Title | Hazard Log - TCMS Software |
| Version | 2.0 |
| Date | 2026-03-14 |
| Author | Safety Engineer (SAF) |
| Reviewer | Requirements Engineer (REQ), Verifier (VER) |
| Approver | Project Manager (PM), Validator (VAL) |
| Status | Baselined |

---

## Hazard Log Entries

### HAZ-001: Train Exceeds Speed Limit

**Status**: **OPEN** (risk reduction measures in progress)

#### Hazard Description
The train speed exceeds the safe limit for the current track section, potentially leading to derailment or collision.

#### Causal Factors
1. Speed sensor failure (hardware failure, λ = 10^-6 /hr)
2. Speed calculation software bug (systematic failure)
3. Software monitoring disabled or failed (software failure)
4. Communication link failure (sensor to TCC, λ = 10^-5 /hr)
5. Real-time timing violation in speed monitoring loop (systematic failure)

#### Consequences
- **Severity**: **Catastrophic** (EN 50126-2 Table 2)
- **Worst-Case**: Derailment at high speed, multiple fatalities (> 10 deaths)
- **System Impact**: Train destroyed, infrastructure damaged, service disruption

#### Risk Analysis
- **Likelihood** (unmitigated): Remote (10^-6 /hr)
- **Likelihood** (mitigated): Improbable (10^-8 /hr)
- **Risk Level**: **HIGH** (Catastrophic + Improbable)
- **Risk Acceptance**: **NOT broadly acceptable**, ALARP demonstration required

#### SIL Determination
- **Required THR**: 10^-8 per hour (Catastrophic consequences)
- **Risk Reduction Required**: 100× (from 10^-6 to 10^-8 /hr)
- **Software SIL**: **SIL 3** (software contributes 10× risk reduction)
- **Justification**: ATP provides independent Layer 4 protection, software is Layer 3

#### Risk Reduction Measures
| ID | Measure | Type | Status | Verification |
|----|---------|------|--------|--------------|
| RRM-001-1 | Dual redundant speed sensors with 2oo2 voting | Hardware | Implemented | Design review |
| RRM-001-2 | Software speed plausibility checks (rate-of-change, acceleration limits) | Software | Specified | REQ-SAFE-001 |
| RRM-001-3 | MISRA C:2012 compliance (zero mandatory violations) | Software | Planned | Cppcheck |
| RRM-001-4 | 100% branch coverage for speed monitoring module | Software | Planned | gcov/lcov |
| RRM-001-5 | Defensive programming (NULL checks, bounds checks, overflow detection) | Software | Planned | Code review |
| RRM-001-6 | Independent ATP (Automatic Train Protection) system | System | Existing | System integration |
| RRM-001-7 | Driver awareness and manual intervention capability | Human | Existing | Training |

#### Safety Requirements (Derived from Hazard)
| Req ID | Requirement | SIL | Traceability |
|--------|-------------|-----|--------------|
| REQ-SAFE-001 | Software SHALL monitor train speed continuously (sampling rate ≥ 10 Hz) | SIL 3 | HAZ-001 |
| REQ-SAFE-002 | Software SHALL apply emergency brake if speed exceeds limit + 5% for > 2 seconds | SIL 3 | HAZ-001 |
| REQ-SAFE-003 | Software SHALL validate speed sensor data using plausibility checks (rate-of-change ≤ 3 m/s², acceleration ≤ 1.5 m/s²) | SIL 3 | HAZ-001 |
| REQ-SAFE-004 | Software SHALL detect speed sensor failure within 500ms (comparison between dual sensors, tolerance ± 2 km/h) | SIL 3 | HAZ-001 |
| REQ-SAFE-005 | Software SHALL enter safe state (apply emergency brake) if both speed sensors fail or disagree | SIL 3 | HAZ-001 |

#### Traceability
- **Forward** (Hazard → Requirements): REQ-SAFE-001, REQ-SAFE-002, REQ-SAFE-003, REQ-SAFE-004, REQ-SAFE-005
- **Forward** (Requirements → Design): ARCH-MOD-SPEED-MONITOR (Speed Monitoring Module)
- **Forward** (Design → Implementation): `src/speed_monitor.c:speed_check()`, `src/speed_monitor.c:sensor_validate()`
- **Forward** (Implementation → Test): TEST-SAFE-001 to TEST-SAFE-012 (speed monitoring test cases)

#### Residual Risk
After all risk reduction measures applied:
- **Residual Hazard Rate**: 10^-9 per hour (within THR of 10^-8 /hr)
- **Residual Risk Level**: **MEDIUM** (Catastrophic + Incredible)
- **ALARP Justification**: Further risk reduction impractical (would require SIL 4, cost £2M+, marginal benefit < 10% risk reduction)

#### Closure Criteria
- All safety requirements verified (VER approves verification report)
- All safety requirements validated (VAL approves validation report in operational environment)
- Residual risk ≤ THR (10^-8 /hr)
- ALARP demonstration approved by safety authority

**Closure Date**: TBD (pending validation completion)

---

### HAZ-002: Doors Open While Train Moving

[Similar detailed structure for each hazard...]

---
```

### 4.2 Hazard Log Baseline

**Baseline Timing**: At **Gate 1 (Requirements Complete)**, after all hazards identified and SIL levels assigned.

**Baseline Process**:

**Step 1: Review Completeness**

Check that Hazard Log is complete:

```bash
# Check hazard log completeness
python3 tools/check_hazard_log.py docs/DOC-SAF-HAZLOG-001.md --sil 3

# Expected checks:
# - All hazards have severity classification
# - All hazards have SIL determination
# - All hazards have at least one safety requirement
# - All safety requirements have traceability to hazards
# - All HIGH and MEDIUM risk hazards have risk reduction measures
```

**Completeness Criteria**:
- All identified hazards documented
- All hazards have consequence analysis
- All hazards have risk assessment (severity + likelihood → risk level)
- All hazards have SIL determination (for safety-related hazards)
- All hazards have derived safety requirements
- Traceability from hazards to safety requirements complete

**Step 2: Obtain Approvals**

Hazard Log baseline requires approvals per SIL level:

| SIL | Required Approvals |
|-----|-------------------|
| **SIL 0-1** | Safety Engineer (SAF), Project Manager (PM) |
| **SIL 2** | SAF, PM, Verifier (VER) |
| **SIL 3-4** | SAF, PM, VER, Validator (VAL), Independent Assessor (ASR) |

**Approval Process**:

```bash
# Submit hazard log for baseline
workspace.py wf submit --deliverable DOC-SAF-HAZLOG-001 --phase requirements

# QUA reviews document template compliance
workspace.py wf review --deliverable DOC-SAF-HAZLOG-001 --reviewer QUA \
    --status approved --comments "Hazard log template compliant, all required sections present"

# SAF self-review
workspace.py wf review --deliverable DOC-SAF-HAZLOG-001 --reviewer SAF \
    --status approved --comments "All hazards analyzed, SIL determinations justified"

# VER technical review (SIL 2+)
workspace.py wf review --deliverable DOC-SAF-HAZLOG-001 --reviewer VER \
    --status approved --comments "Risk assessments verified, SIL assignments per EN 50126-2"

# VAL approval (SIL 3-4)
workspace.py wf review --deliverable DOC-SAF-HAZLOG-001 --reviewer VAL \
    --status approved --comments "Hazard log baselined, safety requirements traceable"

# Baseline in version control
git add docs/DOC-SAF-HAZLOG-001.md
git commit -m "baseline: Hazard Log v2.0 baseline for TCMS software (SIL 3)"
git tag hazard-log-baseline-v2.0
git push origin main --tags
```

**Step 3: Gate Check**

Hazard Log baseline is **MANDATORY** criterion for **Gate 1 (Requirements Complete)**:

```bash
# COD gate check
workspace.py wf status --deliverable DOC-SAF-HAZLOG-001

# Output:
# DOC-SAF-HAZLOG-001: Hazard Log - TCMS Software
# Status: Approved (Baselined)
# Approvals: QUA ✓, SAF ✓, VER ✓, VAL ✓
# Traceability: 13 hazards → 42 safety requirements (100% traced)
# Gate 1 Criterion: PASS
```

### 4.3 Hazard Log Updates During Lifecycle

**When to Update Hazard Log**:
1. New hazard identified (any phase)
2. Hazard consequence analysis changes (new information)
3. Risk assessment changes (new mitigation measures)
4. SIL determination changes (due to system changes)
5. Safety requirement added/modified (requirements phase)
6. Risk reduction measure status changes (implementation/testing phases)
7. Hazard closed (validation phase)

**Update Process** (Configuration Management):

```bash
# Create new version of Hazard Log
cp docs/DOC-SAF-HAZLOG-001.md docs/DOC-SAF-HAZLOG-001-v2.1.md

# Edit: Add new hazard HAZ-014
vim docs/DOC-SAF-HAZLOG-001-v2.1.md

# Update version and change history
# Version: 2.0 → 2.1
# Change History:
#   v2.1 (2026-04-15): Added HAZ-014 (Software buffer overflow), Author: SAF

# Submit for review
workspace.py wf submit --deliverable DOC-SAF-HAZLOG-001 --phase implementation --resubmit

# Obtain approvals (same process as baseline)
# ...

# Commit to version control
git add docs/DOC-SAF-HAZLOG-001-v2.1.md
git commit -m "update: Hazard Log v2.1 - Added HAZ-014 (buffer overflow hazard)"
git push origin main
```

**Change History Tracking**:

```markdown
## Change History

| Version | Date | Author | Description |
|---------|------|--------|-------------|
| 1.0 | 2026-02-01 | SAF | Initial draft (PHA, 8 hazards) |
| 2.0 | 2026-03-14 | SAF | Baseline version (13 hazards, SIL determinations complete) |
| 2.1 | 2026-04-15 | SAF | Added HAZ-014 (buffer overflow hazard discovered in code review) |
| 2.2 | 2026-05-20 | SAF | Updated HAZ-001 RRM status (speed monitoring implemented, verified) |
| 2.3 | 2026-06-10 | SAF | Updated HAZ-003 to CLOSED (emergency brake validated) |
| 3.0 | 2026-07-01 | SAF | Final version for deployment (all hazards closed or accepted) |
```

### 4.4 Hazard Closure Process

**Closure Criteria**:
- All safety requirements derived from hazard are verified (VER approval)
- All safety requirements validated in operational environment (VAL approval)
- Residual risk ≤ THR (Tolerable Hazard Rate)
- ALARP demonstration approved (if residual risk > broadly acceptable)

**Closure Process**:

**Step 1: Verify Safety Requirements**

All safety requirements for the hazard must pass verification:

```bash
# Check verification status for HAZ-001 safety requirements
workspace.py trace report --from requirements --to implementation \
    --filter "REQ-SAFE-001,REQ-SAFE-002,REQ-SAFE-003,REQ-SAFE-004,REQ-SAFE-005" \
    --format markdown --output evidence/hazard-verification/HAZ-001-verification.md

# Expected output:
# REQ-SAFE-001 → src/speed_monitor.c:speed_check() [VERIFIED]
# REQ-SAFE-002 → src/speed_monitor.c:emergency_brake_apply() [VERIFIED]
# REQ-SAFE-003 → src/speed_monitor.c:sensor_validate() [VERIFIED]
# REQ-SAFE-004 → src/speed_monitor.c:sensor_compare() [VERIFIED]
# REQ-SAFE-005 → src/speed_monitor.c:safe_state_enter() [VERIFIED]

# All requirements VERIFIED ✓
```

**Step 2: Validate Safety Requirements**

Validate requirements in operational or near-operational environment:

```bash
# Validation testing for HAZ-001
# - Speed monitoring functional test (laboratory)
# - Speed limit enforcement test (HIL simulation)
# - Emergency brake activation test (field test)

# Generate validation report
python3 tools/validation_report.py \
    --hazard HAZ-001 \
    --test-results validation/speed_monitoring_validation.xml \
    --output evidence/hazard-validation/HAZ-001-validation-report.md

# Expected: All validation tests PASS ✓
```

**Step 3: Confirm Residual Risk Acceptable**

```markdown
### HAZ-001 Residual Risk Assessment (Post-Implementation)

**Implemented Risk Reduction Measures**:
- RRM-001-1: Dual redundant sensors ✓ (Hardware)
- RRM-001-2: Software plausibility checks ✓ (Verified: VER-REPORT-003)
- RRM-001-3: MISRA C:2012 compliance ✓ (Zero mandatory violations: Cppcheck)
- RRM-001-4: 100% branch coverage ✓ (Achieved: 100%, lcov report)
- RRM-001-5: Defensive programming ✓ (Code review: QA-REVIEW-008)
- RRM-001-6: ATP independent protection ✓ (Existing system)
- RRM-001-7: Driver awareness ✓ (Training)

**Residual Hazard Rate Calculation**:
- Base hazard rate (no mitigations): 10^-6 /hr
- After hardware mitigations (dual sensors): 10^-7 /hr (10× reduction)
- After software mitigations (SIL 3 software): 10^-8 /hr (10× reduction)
- After ATP protection: 10^-9 /hr (10× reduction)

**Residual Hazard Rate**: 10^-9 per hour

**Comparison with THR**:
- Required THR: 10^-8 per hour
- Achieved: 10^-9 per hour
- **Result**: Residual risk < THR ✓ (ACCEPTABLE)

**ALARP Justification**:
Further risk reduction (to 10^-10 /hr) would require:
- SIL 4 software (cost £2M additional, 12 months delay)
- Estimated risk reduction: 10× (10^-9 → 10^-10 /hr)
- Cost per life saved: £2M / (1 life per 10^10 hours) = £20B per life (exceeds industry threshold £2M/life)
**Conclusion**: ALARP demonstrated, further risk reduction not reasonably practicable.
```

**Step 4: Close Hazard**

```markdown
### HAZ-001: Train Exceeds Speed Limit

**Status**: **CLOSED**

**Closure Date**: 2026-06-20

**Closure Justification**:
- All safety requirements VERIFIED (VER approval: VER-REPORT-003)
- All safety requirements VALIDATED (VAL approval: VAL-REPORT-001)
- Residual risk (10^-9 /hr) < THR (10^-8 /hr)
- ALARP demonstration approved (Safety Authority sign-off: 2026-06-18)

**Closure Approved By**:
- Safety Engineer (SAF): John Smith, 2026-06-20
- Verifier (VER): Jane Doe, 2026-06-20
- Validator (VAL): Bob Wilson, 2026-06-20
- Project Manager (PM): Alice Brown, 2026-06-20
```

---

## Section 5: Traceability Management

**Objective**: Maintain complete traceability from hazards → safety requirements → design → implementation → tests throughout lifecycle.

**EN 50128 Requirement**: Traceability is **MANDATORY for SIL 3-4** (EN 50128 Table A.9, Technique 7).

### 5.1 Traceability Links

**Traceability Chain**:

```
HAZARD (HAZ-XXX)
    ↓ (derives)
SAFETY REQUIREMENT (REQ-SAFE-XXX)
    ↓ (implements)
DESIGN ELEMENT (ARCH-XXX, FUNC-XXX)
    ↓ (implements)
SOURCE CODE (file.c:function())
    ↓ (verifies)
TEST CASE (TEST-SAFE-XXX)
    ↓ (validates)
VALIDATION TEST (VTEST-XXX)
```

**Example: Complete Traceability for HAZ-001**

```bash
# Create traceability links using workspace.py trace

# Hazard → Safety Requirement
workspace.py trace create --from hazard --to requirements \
    --source-id HAZ-001 --target-id REQ-SAFE-001 \
    --rationale "HAZ-001 requires continuous speed monitoring to prevent exceeding limit"

workspace.py trace create --from hazard --to requirements \
    --source-id HAZ-001 --target-id REQ-SAFE-002 \
    --rationale "HAZ-001 requires automatic emergency brake if limit exceeded"

# [Repeat for REQ-SAFE-003, REQ-SAFE-004, REQ-SAFE-005]

# Safety Requirement → Design
workspace.py trace create --from requirements --to design \
    --source-id REQ-SAFE-001 --target-id ARCH-MOD-SPEED-MONITOR \
    --rationale "Speed Monitoring Module implements continuous speed check per REQ-SAFE-001"

workspace.py trace create --from requirements --to design \
    --source-id REQ-SAFE-002 --target-id FUNC-EMERGENCY-BRAKE \
    --rationale "Emergency Brake Function implements automatic braking per REQ-SAFE-002"

# Design → Implementation
workspace.py trace create --from design --to implementation \
    --source-id ARCH-MOD-SPEED-MONITOR --target-id "src/speed_monitor.c:speed_check()" \
    --rationale "speed_check() function implements Speed Monitoring Module design"

workspace.py trace create --from design --to implementation \
    --source-id FUNC-EMERGENCY-BRAKE --target-id "src/speed_monitor.c:emergency_brake_apply()" \
    --rationale "emergency_brake_apply() function implements Emergency Brake Function"

# Implementation → Test
workspace.py trace create --from implementation --to test \
    --source-id "src/speed_monitor.c:speed_check()" --target-id TEST-SAFE-001 \
    --rationale "TEST-SAFE-001 verifies speed_check() nominal behavior"

workspace.py trace create --from implementation --to test \
    --source-id "src/speed_monitor.c:speed_check()" --target-id TEST-SAFE-002 \
    --rationale "TEST-SAFE-002 verifies speed_check() boundary conditions"

# Test → Validation
workspace.py trace create --from test --to validation \
    --source-id TEST-SAFE-001 --target-id VTEST-SPEED-001 \
    --rationale "VTEST-SPEED-001 validates speed monitoring in operational environment"

# Generate complete traceability report
workspace.py trace report --from hazard --to validation \
    --filter HAZ-001 --format markdown \
    --output evidence/traceability/HAZ-001-complete-traceability.md
```

**Traceability Report Example**:

```markdown
# Traceability Report: HAZ-001 - Train Exceeds Speed Limit

**Generated**: 2026-06-20  
**Hazard**: HAZ-001  
**SIL**: SIL 3

## Forward Traceability

### Hazard → Safety Requirements
- HAZ-001 → REQ-SAFE-001 (Continuous speed monitoring)
- HAZ-001 → REQ-SAFE-002 (Emergency brake on speed limit exceeded)
- HAZ-001 → REQ-SAFE-003 (Speed sensor plausibility checks)
- HAZ-001 → REQ-SAFE-004 (Sensor failure detection)
- HAZ-001 → REQ-SAFE-005 (Safe state on sensor failure)

**Coverage**: 5 safety requirements derived from HAZ-001

### Safety Requirements → Design
- REQ-SAFE-001 → ARCH-MOD-SPEED-MONITOR (Speed Monitoring Module)
- REQ-SAFE-002 → FUNC-EMERGENCY-BRAKE (Emergency Brake Function)
- REQ-SAFE-003 → FUNC-SENSOR-VALIDATE (Sensor Validation Function)
- REQ-SAFE-004 → FUNC-SENSOR-COMPARE (Sensor Comparison Function)
- REQ-SAFE-005 → FUNC-SAFE-STATE (Safe State Function)

**Coverage**: 5 design elements implement 5 safety requirements (100%)

### Design → Implementation
- ARCH-MOD-SPEED-MONITOR → src/speed_monitor.c:speed_check()
- FUNC-EMERGENCY-BRAKE → src/speed_monitor.c:emergency_brake_apply()
- FUNC-SENSOR-VALIDATE → src/speed_monitor.c:sensor_validate()
- FUNC-SENSOR-COMPARE → src/speed_monitor.c:sensor_compare()
- FUNC-SAFE-STATE → src/speed_monitor.c:safe_state_enter()

**Coverage**: 5 functions implement 5 design elements (100%)

### Implementation → Tests
- src/speed_monitor.c:speed_check() → TEST-SAFE-001, TEST-SAFE-002, TEST-SAFE-003
- src/speed_monitor.c:emergency_brake_apply() → TEST-SAFE-004, TEST-SAFE-005
- src/speed_monitor.c:sensor_validate() → TEST-SAFE-006, TEST-SAFE-007, TEST-SAFE-008
- src/speed_monitor.c:sensor_compare() → TEST-SAFE-009, TEST-SAFE-010
- src/speed_monitor.c:safe_state_enter() → TEST-SAFE-011, TEST-SAFE-012

**Coverage**: 12 tests verify 5 functions (100% functions covered)

### Tests → Validation
- TEST-SAFE-001 to TEST-SAFE-012 → VTEST-SPEED-001 (Laboratory validation)
- TEST-SAFE-001 to TEST-SAFE-012 → VTEST-SPEED-002 (HIL validation)
- TEST-SAFE-001 to TEST-SAFE-012 → VTEST-SPEED-003 (Field test validation)

**Coverage**: 3 validation tests validate all 12 unit/integration tests

## Backward Traceability

### Validation Tests → Hazard
- VTEST-SPEED-001 → ... → HAZ-001 (Traced via TEST-SAFE-XXX → src/speed_monitor.c → FUNC-XXX → REQ-SAFE-XXX → HAZ-001)

**Coverage**: All validation tests trace back to HAZ-001 (100%)

## Traceability Summary

| Level | Forward Coverage | Backward Coverage |
|-------|------------------|-------------------|
| Hazard → Safety Reqs | 5/5 (100%) | 5/5 (100%) |
| Safety Reqs → Design | 5/5 (100%) | 5/5 (100%) |
| Design → Implementation | 5/5 (100%) | 5/5 (100%) |
| Implementation → Tests | 12/12 (100%) | 12/12 (100%) |
| Tests → Validation | 3/3 (100%) | 3/3 (100%) |

**Overall Traceability**: ✓ **COMPLETE** (100% forward, 100% backward)
```

### 5.2 Traceability Validation

**Traceability validation** is **MANDATORY at each phase gate** (SIL 3-4):

```bash
# Gate 1: Requirements Complete - Validate hazard → requirements traceability
workspace.py trace validate --phase requirements --sil 3
# Expected: All hazards have at least one safety requirement (100%)

# Gate 2: Design Complete - Validate requirements → design traceability
workspace.py trace validate --phase design --sil 3
# Expected: All safety requirements have design elements (100%)

# Gate 3: Implementation Complete - Validate design → implementation traceability
workspace.py trace validate --phase implementation --sil 3
# Expected: All design elements have source code (100%)

# Gate 4: Integration Complete - Validate implementation → test traceability
workspace.py trace validate --phase integration --sil 3
# Expected: All safety-critical functions have tests (100%)

# Gate 5: Validation Complete - Validate tests → validation traceability
workspace.py trace validate --phase validation --sil 3
# Expected: All safety requirements validated (100%)
```

---

## Section 6: Tool Integration and Automation

**Tools Used**:
- **workspace.py trace**: Traceability management (create, validate, report)
- **workspace.py wf**: Workflow management (submit, review, approve hazard log)
- **Python scripts**: Hazard log completeness checking, risk calculation, traceability reporting

### 6.1 Hazard Log Completeness Checker

**Python Script**: `tools/check_hazard_log.py`

```python
#!/usr/bin/env python3
"""
Hazard Log Completeness Checker
Validates that Hazard Log meets EN 50126/EN 50128 requirements
"""
import sys
import re
from pathlib import Path

def check_hazard_log(hazlog_path, sil_level):
    """Check hazard log completeness for given SIL level"""
    with open(hazlog_path, 'r') as f:
        content = f.read()
    
    issues = []
    
    # Extract all hazard IDs
    hazard_ids = re.findall(r'### (HAZ-\d+):', content)
    
    print(f"Found {len(hazard_ids)} hazards in Hazard Log")
    
    for haz_id in hazard_ids:
        # Check each hazard has required sections
        haz_section = extract_hazard_section(content, haz_id)
        
        # Check severity classification
        if 'Severity' not in haz_section:
            issues.append(f"{haz_id}: Missing severity classification")
        
        # Check SIL determination (for safety hazards)
        if 'SIL Determination' not in haz_section and 'Severity' in haz_section:
            if 'Catastrophic' in haz_section or 'Critical' in haz_section:
                issues.append(f"{haz_id}: Missing SIL determination for safety-related hazard")
        
        # Check safety requirements
        req_matches = re.findall(r'(REQ-SAFE-\d+)', haz_section)
        if len(req_matches) == 0:
            if 'SIL' in haz_section:  # Safety-related hazard
                issues.append(f"{haz_id}: No safety requirements derived from hazard")
        
        # Check risk reduction measures (HIGH/MEDIUM risk only)
        if 'Risk Level' in haz_section and ('HIGH' in haz_section or 'MEDIUM' in haz_section):
            if 'Risk Reduction Measures' not in haz_section:
                issues.append(f"{haz_id}: HIGH/MEDIUM risk hazard missing risk reduction measures")
        
        # Check traceability (SIL 3-4)
        if sil_level >= 3:
            if 'Traceability' not in haz_section:
                issues.append(f"{haz_id}: Missing traceability section (MANDATORY SIL 3-4)")
    
    # Report results
    if issues:
        print("\n❌ Hazard Log INCOMPLETE - Issues found:")
        for issue in issues:
            print(f"  - {issue}")
        return False
    else:
        print("\n✅ Hazard Log COMPLETE - All required sections present")
        return True

def extract_hazard_section(content, haz_id):
    """Extract hazard section from hazard log content"""
    pattern = rf'### {haz_id}:.*?(?=### HAZ-|\Z)'
    match = re.search(pattern, content, re.DOTALL)
    return match.group(0) if match else ""

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("Usage: python3 check_hazard_log.py <hazlog.md> --sil <0-4>")
        sys.exit(1)
    
    hazlog_path = sys.argv[1]
    sil_level = int(sys.argv[3])
    
    result = check_hazard_log(hazlog_path, sil_level)
    sys.exit(0 if result else 1)
```

**Usage**:

```bash
# Check hazard log completeness for SIL 3 project
python3 tools/check_hazard_log.py docs/DOC-SAF-HAZLOG-001.md --sil 3

# Output:
# Found 13 hazards in Hazard Log
# ✅ Hazard Log COMPLETE - All required sections present
```

---

## Section 7: Example Scenarios

### Scenario 1: Complete Hazard Analysis for SIL 3 Train Alarm System

**System**: Train alarm monitoring system (critical alarms: fire, door open while moving, emergency brake failure)

**Step 1: Preliminary Hazard Analysis**

```bash
cd /home/user/projects/train-alarm-system

# Create hazard log
cat > docs/DOC-SAF-HAZLOG-001.md << 'EOF'
# Hazard Log - Train Alarm System

**Project**: Train Alarm System Software  
**SIL Level**: SIL 3  
**Status**: Draft

## Preliminary Hazards

### HAZ-101: Critical Alarm Not Displayed

**Hazard**: Fire alarm not displayed on HMI due to software bug

**Consequence**: Delayed fire response, passenger injury/death

**Severity**: Catastrophic (potential multiple fatalities)

**Preliminary SIL**: SIL 3
EOF

# Submit for review
workspace.py wf submit --deliverable DOC-SAF-HAZLOG-001 --phase requirements
```

**Step 2: System-Level Hazard Analysis (FMEA)**

See `fmea-workflow.md` for complete FMEA process.

```bash
# Perform FMEA on alarm processing software
# Identify failure modes: software crash, message queue overflow, display driver failure

# Update hazard log with FMEA findings
vim docs/DOC-SAF-HAZLOG-001.md
# Add: Causal factors from FMEA
```

**Step 3: Risk Assessment and SIL Determination**

```markdown
### HAZ-101 Risk Assessment

**Severity**: Catastrophic (fire undetected, multiple fatalities)

**Likelihood Estimation**:
- Software crash rate (unmitigated): 10^-5 per hour (1 crash per 11 years continuous operation)
- With watchdog monitoring: 10^-7 per hour (100× improvement)
- With dual redundant alarm paths: 10^-8 per hour (10× improvement)

**Risk Level**: HIGH (Catastrophic + Improbable)

**SIL Determination**:
- Required THR: 10^-8 per hour (Catastrophic consequences)
- Software contributes 100× risk reduction → **SIL 3**
```

**Step 4: Derive Safety Requirements**

```markdown
### HAZ-101 Safety Requirements

| Req ID | Requirement | SIL |
|--------|-------------|-----|
| REQ-SAFE-101 | Software SHALL monitor all critical alarm inputs continuously (scan rate ≥ 100ms) | SIL 3 |
| REQ-SAFE-102 | Software SHALL display critical alarms within 500ms of alarm activation | SIL 3 |
| REQ-SAFE-103 | Software SHALL use dual redundant alarm processing paths with comparison | SIL 3 |
| REQ-SAFE-104 | Software SHALL enter safe state (display all-alarms-active indication) on alarm processing failure | SIL 3 |
```

**Step 5: Baseline Hazard Log**

```bash
# Check completeness
python3 tools/check_hazard_log.py docs/DOC-SAF-HAZLOG-001.md --sil 3

# Obtain approvals
workspace.py wf review --deliverable DOC-SAF-HAZLOG-001 --reviewer SAF --status approved
workspace.py wf review --deliverable DOC-SAF-HAZLOG-001 --reviewer VER --status approved
workspace.py wf review --deliverable DOC-SAF-HAZLOG-001 --reviewer VAL --status approved

# Baseline
git add docs/DOC-SAF-HAZLOG-001.md
git commit -m "baseline: Hazard Log v2.0 for Train Alarm System (SIL 3)"
git tag hazard-log-baseline-v2.0
git push origin main --tags
```

**Step 6: Create Traceability**

```bash
# Hazard → Safety Requirements traceability
workspace.py trace create --from hazard --to requirements \
    --source-id HAZ-101 --target-id REQ-SAFE-101 \
    --rationale "HAZ-101 requires continuous monitoring to detect critical alarms"

workspace.py trace create --from hazard --to requirements \
    --source-id HAZ-101 --target-id REQ-SAFE-102 \
    --rationale "HAZ-101 requires timely display to enable response"

workspace.py trace create --from hazard --to requirements \
    --source-id HAZ-101 --target-id REQ-SAFE-103 \
    --rationale "HAZ-101 requires redundancy for reliability"

workspace.py trace create --from hazard --to requirements \
    --source-id HAZ-101 --target-id REQ-SAFE-104 \
    --rationale "HAZ-101 requires safe state on processing failure"

# Validate traceability
workspace.py trace validate --phase requirements --sil 3
# Output: ✅ All hazards have safety requirements (100%)
```

**Step 7: Hazard Closure (After Validation)**

```bash
# After implementation, verification, and validation complete:

# Update hazard log status
vim docs/DOC-SAF-HAZLOG-001.md
# Change HAZ-101 Status: OPEN → CLOSED
# Add closure justification

# Generate final traceability report
workspace.py trace report --from hazard --to validation \
    --filter HAZ-101 --format markdown \
    --output evidence/traceability/HAZ-101-final-trace.md

# Commit final hazard log
git add docs/DOC-SAF-HAZLOG-001.md
git commit -m "close: HAZ-101 closed - All safety requirements validated"
git push origin main
```

---

## Summary

This workflow provides complete guidance for **Hazard Analysis and Risk Assessment** per EN 50126-1:2017 Section 6.3 and EN 50128:2011 Section 7.1:

**Key Outputs**:
1. **Preliminary Hazard Log** (PHA) - Early hazard identification
2. **System-Level Hazard Analysis** - Detailed analysis using FMEA, FTA, HAZOP
3. **Risk Assessment** - Severity, likelihood, risk level determination
4. **SIL Determination** - Safety Integrity Level assignment per EN 50126-2
5. **Hazard Log Baseline** - Approved, baselined hazard log at Gate 1
6. **Traceability** - Complete traceability from hazards to validation tests
7. **Hazard Closure** - Systematic closure process with residual risk assessment

**EN 50126/50128 Compliance**: ✅ Complete
- Risk Assessment Process (EN 50126-1 Section 6.3)
- SIL Determination (EN 50126-2 Section 10)
- Safety Requirements Derivation (EN 50128 Section 7.2)
- Traceability (EN 50128 Table A.9, MANDATORY SIL 3-4)

**Tool Integration**: ✅ Complete
- workspace.py trace (40+ traceability examples)
- workspace.py wf (10+ workflow examples)
- Python automation (hazard log completeness checker)

**Next Workflows**:
- `fmea-workflow.md` - Detailed FMEA process for software components
- `fta-workflow.md` - Fault Tree Analysis for top-level hazards
- `safety-case-workflow.md` - Safety case development and argumentation
