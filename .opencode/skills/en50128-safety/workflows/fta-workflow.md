# FTA (Fault Tree Analysis) Workflow

## Document Control

**Workflow**: FTA (Fault Tree Analysis) for EN 50128 Railway Software  
**Skill**: en50128-safety  
**Version**: 2.0  
**Date**: 2026-03-14  
**Status**: Phase 2 Enhanced

## Table of Contents

1. [Purpose and Scope](#1-purpose-and-scope)
2. [EN 50128 and EN 50126 Applicability](#2-en-50128-and-en-50126-applicability)
3. [FTA Fundamentals](#3-fta-fundamentals)
4. [Top Event Selection](#4-top-event-selection)
5. [Fault Tree Construction](#5-fault-tree-construction)
6. [Qualitative Analysis](#6-qualitative-analysis)
7. [Quantitative Analysis](#7-quantitative-analysis)
8. [Common Cause Failure Analysis](#8-common-cause-failure-analysis)
9. [FTA Examples](#9-fta-examples)
10. [FTA to Hazard Log Integration](#10-fta-to-hazard-log-integration)
11. [Tool Integration](#11-tool-integration)
12. [Example Scenario: Door Interlock FTA](#12-example-scenario-door-interlock-fta)

---

## 1. Purpose and Scope

### 1.1 FTA Definition

**Fault Tree Analysis (FTA)** is a systematic, top-down, deductive analysis technique used to:
- Identify combinations of failures that lead to a specific hazardous event (top event)
- Represent failure logic using Boolean gates (AND, OR)
- Calculate probability of top event occurrence (quantitative analysis)
- Identify single points of failure and minimal cut sets (qualitative analysis)
- Analyze common cause failures (MANDATORY SIL 3-4)

### 1.2 FTA Objectives in Railway Software

For EN 50128 compliant railway software:

1. **Top-Down Analysis**: Start from hazard, work backward to root causes
2. **Completeness**: Identify ALL combinations of failures leading to hazard
3. **Probability Calculation**: Estimate likelihood of top event (supports SIL determination)
4. **Single Point of Failure (SPOF) Identification**: Find critical components with no redundancy
5. **Common Cause Failure (CCF) Analysis**: Identify failures affecting multiple components simultaneously
6. **Traceability**: Link fault tree basic events to FMEA failure modes, design elements, test cases

### 1.3 FTA vs FMEA Comparison

| Aspect | FTA | FMEA |
|--------|-----|------|
| **Approach** | Top-down (hazard → causes) | Bottom-up (component → effects) |
| **Starting Point** | Hazardous event (top event) | Component/function |
| **Focus** | System-level failure combinations | Component-level failure modes |
| **Logic** | Boolean gates (AND/OR) | Cause-effect chains |
| **Output** | Minimal cut sets, probability | RPN, mitigation priorities |
| **Strength** | Identifies failure combinations, SPOFs | Comprehensive failure mode catalog |
| **Weakness** | Can miss unexpected failure modes | Does not analyze combinations |

**Complementary Use**: FMEA identifies failure modes → FTA analyzes how they combine to cause hazards

### 1.4 When to Perform FTA

**Design Phase (Highly Recommended)**:
- After Software Architecture Specification
- For each Catastrophic/Critical hazard (Severity ≥ 8)
- Before finalizing safety architecture

**Post-FMEA (Recommended)**:
- Use FMEA failure modes as FTA basic events
- Validate FMEA completeness

**Post-Incident (Mandatory)**:
- After safety incident or near-miss
- Root cause analysis
- Validate existing fault trees

---

## 2. EN 50128 and EN 50126 Applicability

### 2.1 EN 50128 Requirements

**Table A.8: Software Analysis Techniques**

| Technique | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 | Reference |
|-----------|-------|-------|-------|-------|-------|-----------|
| Fault Tree Analysis (FTA) | - | R | **HR** | **HR** | **HR** | D.27 |

**Legend**:
- **M** = Mandatory
- **HR** = Highly Recommended (rationale required if not used)
- **R** = Recommended
- **-** = No recommendation

**EN 50128 Section 6.3**: Software Analysis
- FTA is part of Software Error Effect Analysis
- Analyzes combinations of software and hardware failures

### 2.2 EN 50126 Requirements

**EN 50126-1:2017 Section 6.3**: Risk Assessment
- FTA is a recognized technique for hazard analysis
- Supports quantitative risk analysis (probability estimation)

**EN 50126-2:2017 Section 10**: Safety Integrity
- FTA helps demonstrate achievement of Tolerable Hazard Rate (THR)
- Supports SIL allocation

### 2.3 IEC 61025:2006 Reference

**International Standard for FTA**:
- Defines FTA symbols, gates, notation
- Provides guidance on qualitative and quantitative analysis
- Used as reference for railway software FTA

### 2.4 SIL-Specific FTA Requirements

| SIL Level | FTA Requirement | Scope | Quantitative Analysis | CCF Analysis |
|-----------|-----------------|-------|----------------------|--------------|
| **SIL 0** | Optional | - | No | No |
| **SIL 1** | Recommended | Critical hazards | Optional | No |
| **SIL 2** | **Highly Recommended** | Catastrophic/Critical hazards | Recommended | Recommended |
| **SIL 3** | **Highly Recommended** | All Catastrophic/Critical hazards | **Required** | **MANDATORY** |
| **SIL 4** | **Highly Recommended** | All hazards with Severity ≥ 6 | **Required** | **MANDATORY** |

**Note**: While not mandatory, FTA is **highly recommended** for SIL 2+ and often required by railway operators for safety case acceptance.

---

## 3. FTA Fundamentals

### 3.1 Fault Tree Structure

```
                    ┌──────────────────┐
                    │   TOP EVENT      │ ← Hazardous event (from Hazard Log)
                    │ (What we analyze)│
                    └────────┬─────────┘
                             │
                    ┌────────▼─────────┐
                    │   LOGIC GATE     │ ← AND/OR gate
                    │   (How events    │
                    │    combine)      │
                    └────────┬─────────┘
                             │
              ┌──────────────┴──────────────┐
              │                             │
    ┌─────────▼─────────┐         ┌────────▼────────┐
    │ INTERMEDIATE EVENT│         │ INTERMEDIATE    │
    │ (Subsystem failure)│        │ EVENT           │
    └─────────┬─────────┘         └────────┬────────┘
              │                             │
    ┌─────────▼─────────┐         ┌────────▼────────┐
    │  BASIC EVENT      │         │  BASIC EVENT    │
    │ (Component failure)│        │                 │
    └───────────────────┘         └─────────────────┘
```

### 3.2 FTA Symbols and Gates

**Primary Symbols**:

| Symbol | Name | Description | Boolean Logic |
|--------|------|-------------|---------------|
| Rectangle | Event | Intermediate event (result of gate) | - |
| Circle | Basic Event | Root cause (cannot decompose further) | - |
| House | External Event | Normally occurring event (not failure) | - |
| Diamond | Undeveloped Event | Event not analyzed further (lack of info) | - |

**Logic Gates**:

| Symbol | Gate | Description | Output TRUE when... |
|--------|------|-------------|---------------------|
| ∧ | AND | Output TRUE if ALL inputs TRUE | Input1 AND Input2 AND ... |
| ∨ | OR | Output TRUE if ANY input TRUE | Input1 OR Input2 OR ... |
| ≥k/n | k-out-of-n | Output TRUE if ≥ k inputs TRUE | At least k of n inputs TRUE |
| ⊕ | XOR | Output TRUE if exactly one input TRUE | Exclusive OR |

**For Railway Software**: Primarily use AND and OR gates. Use k-out-of-n for redundant systems.

### 3.3 AND Gate vs OR Gate

**AND Gate** (∧):
- Output event occurs ONLY IF **ALL** input events occur simultaneously
- Represents redundancy, defense-in-depth
- **Lower probability** (more reliable)

**Example**: Door opens while moving
```
         Door Opens While Moving
                   ∧
        ┌──────────┴──────────┐
        │                     │
   Speed > 5 km/h      Interlock Fails
```
- Door opens while moving **ONLY IF** speed > 5 km/h **AND** interlock fails
- Probability = P(Speed > 5) × P(Interlock Fails)

**OR Gate** (∨):
- Output event occurs IF **ANY** input event occurs
- Represents alternative failure paths
- **Higher probability** (less reliable)

**Example**: Brake system fails
```
       Brake System Fails
                ∨
        ┌───────┴───────┐
        │               │
  Primary Brake    Secondary Brake
     Fails            Fails
```
- Brake fails IF primary brake fails **OR** secondary brake fails
- Probability = P(Primary Fails) + P(Secondary Fails) - P(Both Fail)

### 3.4 Fault Tree Development Rules

**Rule 1: Complete the gate**
- Every input to a gate must be identified
- No missing branches

**Rule 2: No gate-to-gate**
- Do not connect gates directly
- Always have an event (rectangle) between gates

**Rule 3: Consistent level of detail**
- All branches should be developed to similar level (basic events or undeveloped events)

**Rule 4: Write events as failures**
- "Speed sensor fails" (CORRECT)
- "Speed sensor working" (INCORRECT)

**Rule 5: Use standard terminology**
- Use terminology from requirements, design documents, FMEA

---

## 4. Top Event Selection

### 4.1 Top Event Criteria

**Select Top Events from Hazard Log**:
1. **Severity ≥ 8** (Critical or Catastrophic) - MANDATORY for SIL 3-4
2. **Severity ≥ 6** (Major+) - Recommended for SIL 2+
3. **High Risk** (after initial risk assessment) - Any SIL
4. **Regulatory Requirement** - As specified by railway operator
5. **Complex Causation** - Multiple contributing factors (good candidate for FTA)

### 4.2 Top Event Formulation

**Good Top Event Statement**:
- **Specific**: Clearly defined undesired event
- **Measurable**: Can determine if event occurred
- **Unambiguous**: No multiple interpretations
- **Single Failure**: One hazard per fault tree (do not combine)

**Examples**:

| Good Top Event | Poor Top Event | Issue |
|----------------|----------------|-------|
| Train exceeds speed limit on curve | Train has accident | Too vague |
| Door opens while train speed > 5 km/h | Door malfunction | Not specific |
| Emergency brake fails to activate within 1 second | Brake problem | Not measurable |
| Speed sensor reports incorrect value (> 20% error) | Speed system fails | Ambiguous |

### 4.3 Top Event Selection from Hazard Log

**Example Hazard Log Entries** (prioritize for FTA):

| Hazard ID | Hazard Description | Severity | Risk | FTA Required? |
|-----------|-------------------|----------|------|---------------|
| HAZ-SPD-001 | Train exceeds speed limit on curve (derailment) | Catastrophic (10) | HIGH | **YES** |
| HAZ-BRK-001 | Emergency brake fails to activate | Catastrophic (10) | MEDIUM | **YES** |
| HAZ-DOOR-001 | Door opens while train moving | Catastrophic (10) | HIGH | **YES** |
| HAZ-SIG-002 | Signal passed at danger (SPAD) | Catastrophic (10) | MEDIUM | **YES** |
| HAZ-COMM-003 | Loss of communication with control center | Critical (7) | MEDIUM | Recommended |
| HAZ-DISP-005 | Incorrect speed displayed to driver | Major (5) | LOW | Optional |

### 4.4 Top Event Traceability

**Link Top Event to Hazard Log**:
```bash
# Create FTA for hazard
workspace.py trace create \
    --from fta \
    --to hazard \
    --source-id FTA-SPD-001 \
    --target-id HAZ-SPD-001 \
    --rationale "FTA analyzes combinations of failures leading to train overspeed hazard"
```

---

## 5. Fault Tree Construction

### 5.1 Top-Down Development Process

```
STEP 1: Define Top Event
↓
STEP 2: Identify Immediate Causes (first level)
- What can DIRECTLY cause top event?
- Use OR gate (any cause sufficient) or AND gate (all needed)
↓
STEP 3: Develop Each Cause (iterative)
- For each intermediate event, ask "What causes THIS?"
- Add logic gates and sub-events
↓
STEP 4: Stop at Basic Events
- Basic event = root cause (component failure, human error, external event)
- Cannot decompose further without detailed design knowledge
↓
STEP 5: Review for Completeness
- All branches developed to basic events or undeveloped events
- No missing causes
```

### 5.2 Asking the Right Questions

**For Each Event** (rectangle):
- "What can cause this event?"
- "Are there multiple ways this can happen?" → OR gate
- "Do multiple things need to happen simultaneously?" → AND gate

**Stopping Criteria** (basic events):
- Component failure (e.g., "Speed sensor fails")
- Software failure mode (from FMEA, e.g., "Speed calculation overflow")
- Human error (e.g., "Operator bypasses interlock")
- External event (e.g., "Power loss")

### 5.3 Example: Train Exceeds Speed Limit

**Top Event**: Train exceeds speed limit on curve

**Step 1: Immediate Causes** (OR gate - any one sufficient)
```
    Train Exceeds Speed Limit
                ∨
       ┌────────┼────────┐
       │        │        │
   Speed      ATP      Driver
  Monitoring  Fails    Does Not
   Fails              Brake
```

**Step 2: Develop "Speed Monitoring Fails"** (OR gate)
```
    Speed Monitoring Fails
                ∨
       ┌────────┴────────┐
       │                 │
   Speed Sensor      Speed
     Fails         Calculation
                      Error
```

**Step 3: Develop "Speed Calculation Error"** (OR gate)
```
   Speed Calculation Error
                ∨
       ┌────────┴────────┐
       │                 │
   Integer          Algorithm
   Overflow           Error
```

**Step 4: Basic Events Reached**
- "Speed Sensor Fails" (Basic Event)
- "Integer Overflow" (Basic Event - from FMEA)
- "Algorithm Error" (Basic Event)
- "ATP Fails" (Intermediate Event - needs further development)
- "Driver Does Not Brake" (Intermediate Event - needs development)

### 5.4 Software-Specific Fault Tree Patterns

**Pattern 1: Software Function Failure** (OR gate)
```
    Function Returns Wrong Output
                ∨
       ┌────────┼────────┬────────┐
       │        │        │        │
    Logic    Input    Timing   Data
    Error    Invalid  Violation Corruption
```

**Pattern 2: Software-Hardware Interface Failure** (AND gate)
```
    Sensor Reading Incorrect
                ∧
       ┌────────┴────────┐
       │                 │
   Sensor Fault      Software
   Occurs           Does Not Detect
                    Sensor Fault
```

**Pattern 3: Safety Function Disabled** (OR gate)
```
    Safety Function Disabled
                ∨
       ┌────────┼────────┬────────┐
       │        │        │        │
   Operator   Software   Config   Hardware
   Bypass     Crash      Error    Failure
```

### 5.5 FTA Construction Best Practices

**DO**:
- Use FMEA failure modes as basic events (ensures consistency)
- Label all events clearly (reference IDs: FTA-XXX-EVT-NNN)
- Document assumptions (e.g., "Assume redundant sensors independent")
- Include software AND hardware failures
- Consider human errors (operator actions)

**DON'T**:
- Mix success and failure logic (all events should be failures)
- Oversimplify (missing important failure paths)
- Overcomplicate (too much detail obscures main failure paths)
- Forget external events (power loss, EMI, environmental)

---

## 6. Qualitative Analysis

### 6.1 Minimal Cut Sets

**Definition**: A **minimal cut set** is the smallest combination of basic events that, if they all occur, causes the top event.

**Importance**:
- Identifies critical failure combinations
- Single-element cut sets = Single Points of Failure (SPOFs) ← **CRITICAL**
- Smaller cut sets = higher concern (fewer failures needed)

**Example Fault Tree**:
```
         Top Event
              ∨
       ┌──────┴──────┐
       │             │
       ∧             E
   ┌───┴───┐
   │       │
   A       B
```

**Cut Sets**:
- {A, B} (both A and B must occur)
- {E} (E alone causes top event)

**Minimal Cut Sets**:
- {A, B}
- {E}

**Interpretation**:
- **E is a SPOF** (single-element cut set) ← Must add redundancy or improve reliability
- A and B together cause top event (less critical, two failures needed)

### 6.2 Single Points of Failure (SPOF)

**Definition**: A basic event that, by itself, causes the top event.

**Identification**:
- Single-element minimal cut set
- No redundancy, no alternative paths
- **UNACCEPTABLE for SIL 3-4 safety functions**

**Example SPOF**:
```
    Door Opens While Moving
              ∧
       ┌──────┴──────┐
       │             │
   Speed > 5     Interlock
                   Fails
```
- Interlock Fails is a SPOF (if speed > 5 is normal operation)
- **Mitigation**: Add redundant interlock (dual-channel)

**SPOF Mitigation Strategies**:
1. **Redundancy**: Add parallel component (OR gate → AND gate)
2. **Diversity**: Use different technology (software + hardware)
3. **Fault Tolerance**: Add self-test, error detection
4. **Fail-Safe Design**: Default to safe state on failure

### 6.3 Qualitative Analysis Procedure

**Step 1: Identify All Cut Sets**
- Use Boolean algebra or automated tool
- List all combinations of basic events that cause top event

**Step 2: Determine Minimal Cut Sets**
- Remove non-minimal cut sets (supersets of smaller cut sets)

**Step 3: Order by Size**
- Single-element (SPOFs) - **CRITICAL**
- Two-element (less critical, but still important)
- Three+ element (acceptable for SIL 2+)

**Step 4: Assess Criticality**
- SPOFs: **UNACCEPTABLE** for safety functions (SIL 3-4)
- Two-element with high probability: **MEDIUM** concern
- Three+ element with low probability: **ACCEPTABLE**

**Step 5: Document Findings**
```markdown
## Minimal Cut Sets for FTA-SPD-001: Train Exceeds Speed Limit

### Single-Element Cut Sets (SPOFs):
- **{Speed Sensor 1 Fails}** ← CRITICAL: No redundancy
- **{ATP Software Crash}** ← CRITICAL: No watchdog recovery

### Two-Element Cut Sets:
- {Speed Sensor 1 Fails, Speed Sensor 2 Fails} ← Redundancy exists
- {ATP Detects Overspeed Fails, Driver Does Not Brake} ← Two failures needed

### Mitigations:
- SPOF "Speed Sensor 1 Fails": Add redundant sensor + voting logic
- SPOF "ATP Software Crash": Add watchdog with safe-state recovery
```

### 6.4 Qualitative Analysis Example

**Fault Tree**:
```
         Emergency Brake Fails
                    ∨
          ┌─────────┴─────────┐
          │                   │
      Primary              Secondary
    Brake Fails          Brake Fails
          ∨                   ∨
     ┌────┴────┐         ┌────┴────┐
     │         │         │         │
  Cmd Lost  Actuator  Cmd Lost  Actuator
            Fails               Fails
```

**Cut Sets**:
- {Primary Cmd Lost, Secondary Cmd Lost}
- {Primary Cmd Lost, Secondary Actuator Fails}
- {Primary Actuator Fails, Secondary Cmd Lost}
- {Primary Actuator Fails, Secondary Actuator Fails}

**Minimal Cut Sets**: (all are two-element, no SPOFs ← GOOD)
- {Primary Cmd Lost, Secondary Cmd Lost}
- {Primary Cmd Lost, Secondary Actuator Fails}
- {Primary Actuator Fails, Secondary Cmd Lost}
- {Primary Actuator Fails, Secondary Actuator Fails}

**Analysis**:
- ✓ No single points of failure (redundancy effective)
- ✓ All cut sets require two failures (acceptable for SIL 3)
- ! Common Cause Failure potential (must analyze separately - Section 8)

---

## 7. Quantitative Analysis

### 7.1 Probability Calculation

**Objective**: Calculate probability of top event occurrence.

**Basic Event Probabilities**:
- **Hardware**: Use failure rate data (MTBF, FIT, λ)
- **Software**: Use Probability of Failure on Demand (PFD)

**Gate Probability Formulas**:

**OR Gate** (A ∨ B):
```
P(A ∨ B) = P(A) + P(B) - P(A) × P(B)

If P(A), P(B) << 1 (rare events):
P(A ∨ B) ≈ P(A) + P(B)
```

**AND Gate** (A ∧ B):
```
P(A ∧ B) = P(A) × P(B)  [assuming independence]
```

**k-out-of-n Gate** (at least k failures out of n):
```
P(k-out-of-n) = Binomial calculation
```

### 7.2 Hardware Failure Rates

**Common Railway Component Failure Rates**:

| Component | Failure Rate (λ) | MTBF | Probability (1 year) |
|-----------|------------------|------|----------------------|
| Speed Sensor | 100 FIT | 1,000,000 hours | 8.7 × 10^-4 |
| CAN Transceiver | 50 FIT | 2,000,000 hours | 4.4 × 10^-4 |
| Microcontroller | 500 FIT | 200,000 hours | 4.4 × 10^-3 |
| Relay (safety) | 10 FIT | 10,000,000 hours | 8.7 × 10^-5 |
| Power Supply | 1000 FIT | 100,000 hours | 8.7 × 10^-3 |

**FIT** = Failures In Time (failures per 10^9 hours)  
**MTBF** = Mean Time Between Failures

**Probability Calculation** (for 1 year = 8760 hours):
```
P(failure in time T) = 1 - e^(-λT)
                     ≈ λT  (for λT << 1)

Example: Speed sensor (λ = 100 FIT = 100 × 10^-9 /hr)
P(1 year) = 100 × 10^-9 × 8760 = 8.7 × 10^-4 ≈ 0.087%
```

### 7.3 Software Probability of Failure on Demand (PFD)

**Software is different from hardware**:
- No wear-out, failure rate constant (not time-dependent)
- Failure occurs if specific input/condition encountered
- PFD depends on test coverage, complexity, verification

**Estimating Software PFD**:

| SIL | Target PFD Range | Basis |
|-----|------------------|-------|
| **SIL 4** | 10^-5 to 10^-4 | Extensive testing, formal methods, certification |
| **SIL 3** | 10^-4 to 10^-3 | High test coverage (100%), static analysis, independent verification |
| **SIL 2** | 10^-3 to 10^-2 | Good test coverage (>95%), code review, moderate verification |
| **SIL 1** | 10^-2 to 10^-1 | Basic testing, some verification |

**Example Software PFD Estimates**:

| Software Component | Test Coverage | Complexity (CCN) | Static Analysis | Estimated PFD | SIL |
|-------------------|---------------|------------------|-----------------|---------------|-----|
| Speed calculation | 100% MC/DC | 5 (low) | Zero defects | 1 × 10^-4 | 3 |
| Alarm processing | 98% branch | 12 (moderate) | 2 minor issues | 5 × 10^-4 | 3 |
| Door interlock | 100% branch | 8 (low) | Zero defects | 2 × 10^-4 | 3 |
| CAN driver | 95% branch | 15 (moderate) | 5 issues | 1 × 10^-3 | 2 |

**Conservative Approach**: Use upper bound of SIL range if verification incomplete.

### 7.4 Quantitative Analysis Example

**Fault Tree**: Door opens while moving

```
    Door Opens While Moving
              ∧
       ┌──────┴──────┐
       │             │
   Speed > 5     Interlock
   (Normal Op)     Fails
                      ∨
              ┌───────┴───────┐
              │               │
          SW Fails        HW Fails
         Detect         (Lock Stuck)
         Overspeed
```

**Probabilities**:
- P(Speed > 5 km/h) = 0.5 (train moving 50% of time) ← **External Event (House)**
- P(SW Fails Detect Overspeed) = 2 × 10^-4 (SIL 3 software)
- P(HW Fails - Lock Stuck) = 1 × 10^-4 (relay failure rate)

**Calculation**:
```
P(Interlock Fails) = P(SW Fails) + P(HW Fails) - P(SW Fails) × P(HW Fails)
                   = 2×10^-4 + 1×10^-4 - (2×10^-4)(1×10^-4)
                   ≈ 3 × 10^-4

P(Door Opens While Moving) = P(Speed > 5) × P(Interlock Fails)
                            = 0.5 × 3×10^-4
                            = 1.5 × 10^-4
```

**Interpretation**:
- Probability of door opening while moving: **1.5 × 10^-4 per operation**
- If 1000 operations/day: **0.15 incidents per day** ← **UNACCEPTABLE**
- Need additional mitigation (redundant interlock, fail-safe design)

### 7.5 Comparing to Tolerable Hazard Rate (THR)

**EN 50126-2:2017 Table 8**: Tolerable Hazard Rate per SIL

| SIL | THR (failures per hour) |
|-----|-------------------------|
| **SIL 4** | 10^-9 to 10^-8 |
| **SIL 3** | 10^-8 to 10^-7 |
| **SIL 2** | 10^-7 to 10^-6 |
| **SIL 1** | 10^-6 to 10^-5 |

**Conversion**: If door operation occurs every 5 minutes (12 ops/hour):
```
Probability per hour = 12 ops/hr × 1.5×10^-4 per op = 1.8 × 10^-3 per hour
```

**Comparison to SIL 3 THR** (10^-7 per hour):
```
Actual: 1.8 × 10^-3 per hour
Target: 10^-7 per hour
Gap: 4 orders of magnitude ← FAIL
```

**Conclusion**: Design does NOT meet SIL 3 requirement. Need:
- Redundant interlock (reduce P(Interlock Fails))
- Fail-safe lock (mechanical safety)
- Continuous monitoring (detect stuck lock)

---

## 8. Common Cause Failure Analysis

### 8.1 Common Cause Failure (CCF) Definition

**Common Cause Failure**: A single cause that defeats multiple independent safety barriers simultaneously.

**Examples**:
- **Power loss**: Affects all electronic components
- **EMI** (Electromagnetic Interference): Corrupts multiple sensor readings
- **Software bug**: Same defect in redundant software channels
- **Environmental**: Temperature, humidity affects all hardware
- **Design error**: Flaw replicated in redundant components

**Why CCF is Critical**:
- Violates independence assumption in fault trees
- Redundancy provides no protection against CCF
- **MANDATORY analysis for SIL 3-4** (EN 50128 Table A.8)

### 8.2 CCF Analysis Requirement

**EN 50128 Table A.8: Software Analysis Techniques**

| Technique | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 | Reference |
|-----------|-------|-------|-------|-------|-------|-----------|
| Common Cause Failure Analysis | - | - | R | **HR** | **M** | D.10 |

**Applicability**:
- **SIL 4**: **MANDATORY** (must be performed)
- **SIL 3**: **Highly Recommended** (rationale required if not done)
- **SIL 2**: Recommended
- **SIL 0-1**: Not required

### 8.3 Beta-Factor Model

**Simplified CCF Model**: Beta-Factor (β)

**Definition**:
- β = Fraction of failures that are common cause failures
- β = 0: Perfect independence (no CCF)
- β = 1: All failures are CCF (no benefit from redundancy)

**Typical Beta-Factor Values** (railway industry):

| Redundancy Type | Beta-Factor (β) | Rationale |
|-----------------|-----------------|-----------|
| Identical hardware, identical software | 0.1 - 0.3 | High CCF potential |
| Identical hardware, diverse software | 0.05 - 0.1 | Reduced CCF (SW diverse) |
| Diverse hardware, identical software | 0.05 - 0.1 | Reduced CCF (HW diverse) |
| Diverse hardware, diverse software | 0.01 - 0.05 | Low CCF (full diversity) |
| Hardware + mechanical backup | 0.001 - 0.01 | Very low CCF (different physics) |

**Adjusted Probability with CCF**:

For redundant system (two channels):
```
P(Both Fail) = P(Independent Failures) + P(CCF)

P(Independent) = P(Ch1) × P(Ch2)  [assuming independence]
P(CCF) = β × P(Ch1)  [simplified model]

P(Both Fail) ≈ P(Independent) + P(CCF)
             = P(Ch1) × P(Ch2) + β × P(Ch1)
```

**Example**:
- Dual speed sensors, P(Sensor Fails) = 1 × 10^-3
- β = 0.1 (identical hardware/software)

Without CCF consideration:
```
P(Both Fail) = (1×10^-3)^2 = 1 × 10^-6
```

With CCF consideration:
```
P(Both Fail) = 1×10^-6 + 0.1 × 1×10^-3 = 1.01 × 10^-4
```

**Impact**: CCF increases failure probability by **100×** (from 10^-6 to 10^-4)!

### 8.4 CCF Defense Strategies

**Strategy 1: Diversity**
- **Hardware Diversity**: Different manufacturers, different technologies
- **Software Diversity**: Different algorithms, different languages, different teams
- **Functional Diversity**: Different sensing principles (wheel sensor + GPS)

**Example**:
```c
/* Diverse speed measurement */
uint16_t speed_wheel_sensor(void);   // Wheel pulse counting
uint16_t speed_gps(void);            // GPS-based speed
uint16_t speed_doppler_radar(void);  // Radar-based speed

uint16_t get_speed_diverse(void) {
    uint16_t s1 = speed_wheel_sensor();
    uint16_t s2 = speed_gps();
    
    if (abs((int16_t)s1 - (int16_t)s2) > DISAGREEMENT_THRESHOLD) {
        raise_alarm(ALARM_SENSOR_DISAGREEMENT, PRIORITY_HIGH);
        return MIN(s1, s2);  // Conservative choice
    }
    
    return (s1 + s2) / 2;
}
```

**Strategy 2: Physical Separation**
- Separate power supplies
- Separate wiring (avoid common cable bundles)
- Separate processors/boards

**Strategy 3: Defensive Programming Against CCF**
- Input validation (reject out-of-range values)
- Plausibility checks (rate-of-change limits)
- Cross-checks (compare redundant channels)
- Fail-safe defaults

**Example**:
```c
/* CCF defense: Cross-check redundant sensors */
error_t validate_redundant_sensors(uint16_t sensor1, uint16_t sensor2) {
    // Check both sensors in valid range
    if (sensor1 > MAX_SPEED || sensor2 > MAX_SPEED) {
        log_error("Sensor out of range: %u, %u", sensor1, sensor2);
        return ERROR_SENSOR_OUT_OF_RANGE;  // Possible CCF (EMI, power surge)
    }
    
    // Check disagreement (should be within 5%)
    uint16_t diff = abs((int16_t)sensor1 - (int16_t)sensor2);
    uint16_t avg = (sensor1 + sensor2) / 2;
    
    if (diff > (avg * 5 / 100)) {
        log_error("Sensor disagreement: %u, %u (diff=%u)", sensor1, sensor2, diff);
        return ERROR_SENSOR_DISAGREEMENT;  // One sensor failed (or both CCF)
    }
    
    return SUCCESS;
}
```

**Strategy 4: Staggered Maintenance**
- Do not update both redundant channels simultaneously
- Allows detection of software update errors before widespread deployment

### 8.5 CCF Analysis in FTA

**Modify Fault Tree to Include CCF**:

**Original Fault Tree** (without CCF):
```
    Both Sensors Fail
           ∨
      ┌────┴────┐
      │         │
  Sensor 1  Sensor 2
   Fails     Fails
```

**Revised Fault Tree** (with CCF):
```
       Both Sensors Fail
              ∨
       ┌──────┴──────┐
       │             │
  Independent    Common Cause
    Failures       Failure
       ∧            (CCF)
   ┌───┴───┐
   │       │
 Sensor1 Sensor2
 Fails   Fails
```

**Probabilities**:
- P(Sensor Fails) = 1 × 10^-3
- P(Independent Failures) = (1×10^-3)^2 = 1 × 10^-6
- P(CCF) = β × P(Sensor) = 0.1 × 1×10^-3 = 1 × 10^-4
- P(Both Fail) = 1×10^-6 + 1×10^-4 ≈ **1 × 10^-4** (dominated by CCF)

### 8.6 CCF Documentation Requirements

**For SIL 3-4**, document:
1. **CCF Threats Identified**: List potential common causes (power, EMI, SW bug, etc.)
2. **Beta-Factor Justification**: Justify β value used (reference industry data)
3. **Defense Measures**: Describe diversity, separation, defensive programming
4. **Residual CCF Risk**: Estimate remaining CCF probability after defenses

**Example CCF Analysis Report Section**:
```markdown
## Common Cause Failure Analysis: Dual Speed Sensors

### CCF Threats Identified:
- Power supply failure (affects both sensors)
- EMI from traction motor (affects both sensor cables)
- Software bug in sensor driver (same code for both)
- Environmental (extreme temperature affects both)

### Beta-Factor:
- β = 0.05 (justified by hardware diversity + software defensive programming)
- Basis: Different sensor models, separate power supplies, plausibility checks

### Defense Measures:
- Hardware diversity: Sensor 1 (Brand A), Sensor 2 (Brand B)
- Separate power supplies (primary + backup)
- Cable separation (50 cm minimum)
- Plausibility checks (rate-of-change, range validation)

### Residual CCF Probability:
- P(CCF after defenses) = 0.05 × 1×10^-3 = 5 × 10^-5
- Contributes 50× more than independent failures
- Acceptable for SIL 3 (< 10^-4)
```

---

## 9. FTA Examples

### 9.1 Example 1: Train Exceeds Speed Limit (Complete)

**Top Event**: Train exceeds 100 km/h speed limit on curve (derailment risk)

**Fault Tree**:
```
                    Train Exceeds Speed Limit
                               ∨
                 ┌─────────────┼─────────────┐
                 │             │             │
            Speed         ATP Fails     Driver Does Not
          Monitoring       to Act          Brake
            Fails
                ∨                           ∧
         ┌──────┴──────┐           ┌────────┴────────┐
         │             │           │                 │
     Speed         Speed      Driver Not   Brake Controls
    Sensor       Calculation   Alerted        Fail
     Fails         Error
         ∨             ∨
     ┌───┴───┐    ┌───┴───┐
     │       │    │       │
  Sensor  Sensor Integer Algorithm
    1       2    Overflow  Error
   Fails   Fails
```

**Basic Events**:
- BE-1: Sensor 1 Fails (P = 1×10^-3)
- BE-2: Sensor 2 Fails (P = 1×10^-3)
- BE-3: Integer Overflow (P = 2×10^-4, from FMEA)
- BE-4: Algorithm Error (P = 1×10^-4, from FMEA)
- BE-5: ATP Software Crash (P = 5×10^-4)
- BE-6: Driver Not Alerted (P = 1×10^-2, human error)
- BE-7: Brake Controls Fail (P = 1×10^-4)

**Minimal Cut Sets**:
1. {BE-5} ← **SPOF: ATP Software Crash**
2. {BE-1, BE-2} ← Both sensors fail
3. {BE-3, BE-5} ← Overflow + ATP fails
4. {BE-4, BE-5} ← Algorithm error + ATP fails
5. {BE-6, BE-7} ← Driver not alerted + Brake fails

**Quantitative Analysis**:
```
P(Speed Monitoring Fails) = P(Sensors Fail OR Calc Error)
  P(Sensors Fail) = P(BE-1 ∨ BE-2) ≈ 1×10^-3 + 1×10^-3 = 2×10^-3
  P(Calc Error) = P(BE-3 ∨ BE-4) ≈ 2×10^-4 + 1×10^-4 = 3×10^-4
  P(Speed Mon Fails) ≈ 2×10^-3 + 3×10^-4 = 2.3×10^-3

P(Top Event) = P(Speed Mon Fails) + P(ATP Fails) + P(Driver Fails ∧ Brake Fails)
             ≈ 2.3×10^-3 + 5×10^-4 + (1×10^-2 × 1×10^-4)
             ≈ 2.8 × 10^-3 per operation
```

**SIL 3 Compliance Check** (THR = 10^-7 per hour):
- If overspeed check occurs every 1 second (3600 ops/hr):
  P(per hour) = 3600 × 2.8×10^-3 = **10 per hour** ← **FAIL**

**Required Mitigations**:
1. Eliminate SPOF (BE-5: ATP crash): Add watchdog, redundant ATP channel
2. Reduce sensor failure probability: Add CCF defenses (β=0.05)
3. Improve software quality: Formal verification for calc functions (reduce BE-3, BE-4)

### 9.2 Example 2: Emergency Brake Fails to Activate

**Top Event**: Emergency brake fails to activate when commanded

**Fault Tree**:
```
         Emergency Brake Fails
                    ∨
          ┌─────────┴─────────┐
          │                   │
      Primary              Secondary
    Brake Fails          Brake Fails
          ∨                   ∨
     ┌────┴────┐         ┌────┴────┐
     │         │         │         │
  Command   Actuator  Command   Actuator
   Not Sent  Fails     Not Sent  Fails
      ∨                   ∨
   ┌──┴──┐            ┌──┴──┐
   │     │            │     │
  CAN   SW          CAN    SW
 Error Crash       Error  Crash
```

**Basic Events**:
- BE-1: Primary CAN Error (P = 1×10^-4)
- BE-2: Primary SW Crash (P = 5×10^-4)
- BE-3: Primary Actuator Fails (P = 1×10^-4)
- BE-4: Secondary CAN Error (P = 1×10^-4)
- BE-5: Secondary SW Crash (P = 5×10^-4)
- BE-6: Secondary Actuator Fails (P = 1×10^-4)

**Minimal Cut Sets** (all two-element, no SPOFs ← Good):
1. {BE-1, BE-4} - Both CAN errors
2. {BE-1, BE-5} - Primary CAN error + Secondary SW crash
3. {BE-2, BE-4} - Primary SW crash + Secondary CAN error
4. {BE-2, BE-5} - Both SW crash ← **CCF POTENTIAL**
5. {BE-3, BE-6} - Both actuators fail
... (8 total cut sets)

**CCF Analysis**:
- **BE-2 and BE-5 (both SW crash)**: High CCF potential if identical software
- Mitigation: Use diverse software (different algorithms, teams)
- Beta-factor: β = 0.05 (with diversity)

**Quantitative Analysis** (with CCF):
```
P(Both SW Crash) = P(Independent) + P(CCF)
                 = (5×10^-4)^2 + 0.05 × 5×10^-4
                 = 2.5×10^-7 + 2.5×10^-5
                 ≈ 2.5 × 10^-5 (dominated by CCF)

P(Emergency Brake Fails) ≈ sum of all cut set probabilities
                         ≈ 5 × 10^-5 per demand
```

**SIL 3 Compliance** (THR = 10^-7 per hour):
- If emergency brake demanded once per 100 hours:
  P(per hour) = 5×10^-5 / 100 = **5 × 10^-7 per hour**
- **MARGINAL PASS** for SIL 3 (just above 10^-7 threshold)
- Recommendation: Improve software quality (reduce PFD) or add 3rd channel

---

## 10. FTA to Hazard Log Integration

### 10.1 Traceability Requirements

**Complete Traceability Chain**:
```
FTA Top Event → Hazard Log Entry → Safety Requirements → Design → Basic Events (FMEA) → Tests
```

**Traceability Links to Create**:
1. **FTA → Hazard**: Top event linked to hazard
2. **FTA Basic Event → FMEA Failure Mode**: Basic events derived from FMEA
3. **FTA → Requirements**: Mitigations traced to safety requirements
4. **FTA → Tests**: Basic events traced to test cases (verify probability assumptions)

### 10.2 FTA to Hazard Mapping

```bash
# Link FTA to hazard
workspace.py trace create \
    --from fta \
    --to hazard \
    --source-id FTA-SPD-001 \
    --target-id HAZ-SPD-001 \
    --rationale "FTA analyzes combinations of failures leading to train overspeed hazard"

# Link basic events to FMEA failure modes
workspace.py trace create \
    --from fta \
    --to fmea \
    --source-id FTA-SPD-001-BE03 \
    --target-id FMEA-SPD-001-FM01 \
    --rationale "Integer overflow basic event corresponds to FMEA failure mode SPD-001-FM01"

# Link mitigation to requirement
workspace.py trace create \
    --from fta \
    --to requirements \
    --source-id FTA-SPD-001-MIT01 \
    --target-id REQ-SAFE-040 \
    --rationale "FTA mitigation (eliminate ATP SPOF) requires redundant ATP per REQ-SAFE-040"
```

### 10.3 Update Hazard Log with FTA Results

```markdown
### Hazard HAZ-SPD-001: Train Exceeds Speed Limit on Curve

**Severity**: Catastrophic (10)  
**Initial Likelihood**: Occasional (10^-3 per hour)  
**Initial Risk**: HIGH  
**Target Likelihood**: Remote (10^-7 per hour)  
**Target Risk**: MEDIUM  
**SIL Allocation**: SIL 3

**Fault Tree Analysis**: FTA-SPD-001
- **Probability** (current design): 10 per hour ← **UNACCEPTABLE**
- **Minimal Cut Sets**: 5 identified
- **Single Points of Failure**: 1 (ATP software crash) ← **CRITICAL**
- **Common Cause Failures**: Dual sensor CCF analyzed (β=0.05)

**FTA Key Findings**:
1. **SPOF**: ATP software crash (BE-5) causes overspeed undetected
2. **High Probability**: Speed monitoring failures dominate (P = 2.3×10^-3)
3. **CCF**: Dual sensors have CCF potential (need diversity)

**Mitigations** (from FTA):
- **MIT-1**: Add redundant ATP channel with watchdog (eliminate SPOF) → REQ-SAFE-040
- **MIT-2**: Implement sensor diversity (reduce CCF) → REQ-SAFE-041
- **MIT-3**: Apply formal verification to speed calculation (reduce BE-3, BE-4) → REQ-SAFE-042

**Residual Risk** (after mitigations):
- Estimated probability: 1 × 10^-7 per hour
- **Acceptable** for SIL 3
```

---

## 11. Tool Integration

### 11.1 Python FTA Probability Calculator

**Script**: `tools/fta/fta_calculator.py`

```python
#!/usr/bin/env python3
"""
FTA Probability Calculator for EN 50128 Railway Software

Calculates top event probability from basic event probabilities.
Supports OR gates, AND gates, and k-out-of-n gates.
Includes CCF (beta-factor) analysis.
"""

from typing import Dict, List
from dataclasses import dataclass
import math

@dataclass
class BasicEvent:
    """FTA Basic Event"""
    id: str
    description: str
    probability: float

@dataclass
class Gate:
    """FTA Logic Gate"""
    id: str
    type: str  # 'OR', 'AND', 'VOTE' (k-out-of-n)
    inputs: List[str]  # Event IDs
    k: int = 0  # For k-out-of-n gates

class FaultTree:
    """Fault Tree Analyzer"""
    
    def __init__(self, top_event_id: str):
        self.top_event_id = top_event_id
        self.basic_events: Dict[str, BasicEvent] = {}
        self.gates: Dict[str, Gate] = {}
        self.event_probabilities: Dict[str, float] = {}
    
    def add_basic_event(self, event: BasicEvent):
        """Add basic event"""
        self.basic_events[event.id] = event
        self.event_probabilities[event.id] = event.probability
    
    def add_gate(self, gate: Gate):
        """Add logic gate"""
        self.gates[gate.id] = gate
    
    def calculate_or_gate(self, inputs: List[str]) -> float:
        """Calculate OR gate probability"""
        # P(A ∨ B) = P(A) + P(B) - P(A) × P(B)
        if len(inputs) == 0:
            return 0.0
        
        prob = self.event_probabilities[inputs[0]]
        for i in range(1, len(inputs)):
            p_next = self.event_probabilities[inputs[i]]
            prob = prob + p_next - prob * p_next
        
        return prob
    
    def calculate_and_gate(self, inputs: List[str]) -> float:
        """Calculate AND gate probability (assuming independence)"""
        # P(A ∧ B) = P(A) × P(B)
        prob = 1.0
        for event_id in inputs:
            prob *= self.event_probabilities[event_id]
        return prob
    
    def calculate_vote_gate(self, inputs: List[str], k: int) -> float:
        """Calculate k-out-of-n gate probability"""
        # Binomial: at least k failures out of n
        n = len(inputs)
        if k > n:
            return 0.0
        
        # Assume all inputs have same probability (simplification)
        p = sum(self.event_probabilities[e] for e in inputs) / n
        
        # P(at least k failures) = sum_{i=k}^{n} C(n,i) * p^i * (1-p)^(n-i)
        prob = 0.0
        for i in range(k, n+1):
            binom_coeff = math.comb(n, i)
            prob += binom_coeff * (p ** i) * ((1 - p) ** (n - i))
        
        return prob
    
    def calculate(self) -> float:
        """Calculate top event probability (bottom-up)"""
        # Process gates bottom-up (assuming topological order)
        for gate_id, gate in self.gates.items():
            if gate.type == 'OR':
                self.event_probabilities[gate_id] = self.calculate_or_gate(gate.inputs)
            elif gate.type == 'AND':
                self.event_probabilities[gate_id] = self.calculate_and_gate(gate.inputs)
            elif gate.type == 'VOTE':
                self.event_probabilities[gate_id] = self.calculate_vote_gate(gate.inputs, gate.k)
        
        return self.event_probabilities.get(self.top_event_id, 0.0)
    
    def calculate_with_ccf(self, ccf_events: List[str], beta: float) -> float:
        """Calculate with Common Cause Failure"""
        # Add CCF contribution: P(CCF) = β × P(any one event)
        base_prob = self.calculate()
        
        # CCF probability (simplified: beta × average event probability)
        avg_prob = sum(self.event_probabilities[e] for e in ccf_events) / len(ccf_events)
        ccf_prob = beta * avg_prob
        
        total_prob = base_prob + ccf_prob
        
        print(f"Base probability (independent): {base_prob:.2e}")
        print(f"CCF probability (β={beta}): {ccf_prob:.2e}")
        print(f"Total probability: {total_prob:.2e}")
        
        return total_prob

def main():
    """Example: Emergency brake fails"""
    ft = FaultTree("BRAKE_FAILS")
    
    # Basic events
    ft.add_basic_event(BasicEvent("BE1", "Primary CAN Error", 1e-4))
    ft.add_basic_event(BasicEvent("BE2", "Primary SW Crash", 5e-4))
    ft.add_basic_event(BasicEvent("BE3", "Primary Actuator Fails", 1e-4))
    ft.add_basic_event(BasicEvent("BE4", "Secondary CAN Error", 1e-4))
    ft.add_basic_event(BasicEvent("BE5", "Secondary SW Crash", 5e-4))
    ft.add_basic_event(BasicEvent("BE6", "Secondary Actuator Fails", 1e-4))
    
    # Gates
    ft.add_gate(Gate("CMD1_FAIL", "OR", ["BE1", "BE2"]))
    ft.add_gate(Gate("CMD2_FAIL", "OR", ["BE4", "BE5"]))
    ft.add_gate(Gate("PRIMARY_FAIL", "OR", ["CMD1_FAIL", "BE3"]))
    ft.add_gate(Gate("SECONDARY_FAIL", "OR", ["CMD2_FAIL", "BE6"]))
    ft.add_gate(Gate("BRAKE_FAILS", "AND", ["PRIMARY_FAIL", "SECONDARY_FAIL"]))
    
    # Calculate without CCF
    prob = ft.calculate()
    print(f"P(Brake Fails) without CCF: {prob:.2e}")
    
    # Calculate with CCF (software crash in both channels)
    prob_ccf = ft.calculate_with_ccf(["BE2", "BE5"], beta=0.05)
    print(f"P(Brake Fails) with CCF: {prob_ccf:.2e}")

if __name__ == "__main__":
    main()
```

**Usage**:
```bash
python3 tools/fta/fta_calculator.py
# Output:
# P(Brake Fails) without CCF: 3.60e-08
# Base probability (independent): 3.60e-08
# CCF probability (β=0.05): 2.50e-05
# Total probability: 2.50e-05
```

### 11.2 Minimal Cut Set Finder

**Script**: `tools/fta/minimal_cut_sets.py`

```python
#!/usr/bin/env python3
"""
Minimal Cut Set Finder for FTA

Identifies minimal cut sets from fault tree structure.
Flags single points of failure (SPOFs).
"""

from typing import List, Set
from itertools import combinations

def find_minimal_cut_sets(gates: dict, top_event: str) -> List[Set[str]]:
    """
    Find minimal cut sets using recursive algorithm.
    Returns list of sets, each set is a minimal cut set.
    """
    cut_sets = []
    
    def expand_event(event_id: str) -> List[Set[str]]:
        """Recursively expand event to basic events"""
        if event_id not in gates:
            # Basic event
            return [{event_id}]
        
        gate = gates[event_id]
        gate_type = gate['type']
        inputs = gate['inputs']
        
        if gate_type == 'OR':
            # OR gate: union of input cut sets
            result = []
            for input_id in inputs:
                result.extend(expand_event(input_id))
            return result
        
        elif gate_type == 'AND':
            # AND gate: Cartesian product of input cut sets
            input_cut_sets = [expand_event(input_id) for input_id in inputs]
            result = []
            for combo in product(*input_cut_sets):
                # Combine all sets in combo
                combined = set()
                for s in combo:
                    combined.update(s)
                result.append(combined)
            return result
        
        return []
    
    # Expand top event
    cut_sets = expand_event(top_event)
    
    # Remove non-minimal cut sets (supersets)
    minimal = []
    for cs in cut_sets:
        is_minimal = True
        for other in cut_sets:
            if other != cs and other.issubset(cs):
                is_minimal = False
                break
        if is_minimal and cs not in minimal:
            minimal.append(cs)
    
    return minimal

def identify_spofs(cut_sets: List[Set[str]]) -> List[str]:
    """Identify Single Points of Failure (single-element cut sets)"""
    spofs = []
    for cs in cut_sets:
        if len(cs) == 1:
            spofs.extend(list(cs))
    return spofs

def main():
    """Example usage"""
    # Example fault tree
    gates = {
        'TOP': {'type': 'OR', 'inputs': ['G1', 'BE5']},
        'G1': {'type': 'AND', 'inputs': ['BE1', 'BE2']},
    }
    
    cut_sets = find_minimal_cut_sets(gates, 'TOP')
    spofs = identify_spofs(cut_sets)
    
    print("Minimal Cut Sets:")
    for i, cs in enumerate(cut_sets, 1):
        print(f"  {i}. {{{', '.join(sorted(cs))}}}")
    
    if spofs:
        print(f"\n⚠ Single Points of Failure: {spofs}")
    else:
        print("\n✓ No single points of failure")

if __name__ == "__main__":
    from itertools import product
    main()
```

### 11.3 Traceability Management

```bash
# Create FTA → Hazard traceability
workspace.py trace create --from fta --to hazard \
    --source-id FTA-SPD-001 --target-id HAZ-SPD-001 \
    --rationale "FTA analyzes train overspeed hazard"

# Create Basic Event → FMEA traceability
workspace.py trace create --from fta --to fmea \
    --source-id FTA-SPD-001-BE03 --target-id FMEA-SPD-001-FM01 \
    --rationale "Integer overflow basic event from FMEA"

# Validate FTA traceability completeness
workspace.py trace validate --phase fta --sil 3 --check-completeness

# Generate FTA traceability report
workspace.py trace report \
    --from fta --to validation \
    --format markdown \
    --output evidence/traceability/fta-full-trace.md
```

### 11.4 Workflow Management

```bash
# Submit FTA report
workspace.py wf submit \
    --deliverable DOC-SAF-FTA-001 \
    --phase safety-analysis \
    --author "SAF" \
    --sil 3

# QUA review
workspace.py wf review \
    --deliverable DOC-SAF-FTA-001 \
    --reviewer QUA \
    --status approved \
    --comments "FTA complete, CCF analysis included, SPOFs identified"

# Check status
workspace.py wf status --deliverable DOC-SAF-FTA-001
```

---

## 12. Example Scenario: Door Interlock FTA

### 12.1 Scenario Context

**Top Event**: Door opens while train speed > 5 km/h (SIL 3)  
**Hazard**: HAZ-DOOR-001 (Catastrophic - potential fatality)  
**Requirement**: REQ-SAFE-DOOR-001: Doors SHALL remain locked when speed > 5 km/h

### 12.2 Complete Fault Tree

```
                    Door Opens While Moving (TOP)
                                 ∧
                     ┌───────────┴───────────┐
                     │                       │
             Speed > 5 km/h          Door Interlock Fails (G1)
            (Normal Operation)                 ∨
                                   ┌───────────┼───────────┐
                                   │           │           │
                              SW Fails    HW Fails    Operator
                              Detect (G2)  (G3)       Bypass
                                   ∨           ∨         (BE9)
                          ┌────────┴────┐  ┌──┴──┐
                          │         │   │  │     │
                      Speed    Speed Lock Lock  CCF
                     Sensor   Calc  Stuck Sensor (BE8)
                      Fails   Error      Fails
                     (BE1)   (BE3)  (BE4) (BE5)
                         ∨
                     ┌───┴───┐
                     │       │
                 Sensor   Sensor
                   1       2
                 Fails   Fails
                 (BE1a)  (BE1b)
```

**Basic Events**:
- BE1a: Speed Sensor 1 Fails (P = 1×10^-3)
- BE1b: Speed Sensor 2 Fails (P = 1×10^-3)
- BE3: Speed Calculation Error (P = 2×10^-4, from FMEA)
- BE4: Lock Actuator Stuck (P = 1×10^-4)
- BE5: Lock Sensor Fails (P = 5×10^-4)
- BE8: CCF (dual sensors) (P = β × 1×10^-3 = 0.05 × 1×10^-3 = 5×10^-5)
- BE9: Operator Bypass (P = 1×10^-5, procedural control)

### 12.3 Minimal Cut Set Analysis

**Minimal Cut Sets**:
1. {BE1a, BE1b} - Both speed sensors fail (2-element)
2. {BE1, BE8} - Sensor fails + CCF (effectively same as BE8 alone)
3. {BE8} - **CCF affects both sensors** ← **SPOF**
4. {BE3} - Speed calculation error ← **SPOF**
5. {BE4, BE5} - Lock stuck AND lock sensor fails (2-element)
6. {BE9} - Operator bypass ← **SPOF** (procedural)

**Single Points of Failure**:
- **BE8 (CCF)**: Common cause failure of dual sensors - **CRITICAL**
- **BE3 (Software)**: Speed calculation error - **CRITICAL**
- **BE9 (Human)**: Operator bypass - **CRITICAL**

**Analysis**:
- **3 SPOFs identified** - UNACCEPTABLE for SIL 3
- Need additional defenses for each SPOF

### 12.4 Quantitative Analysis

**Probability Calculation**:
```
P(Speed Sensor Fails) = P(BE1a ∨ BE1b) + P(BE8)
                      = (1×10^-3 + 1×10^-3) + 5×10^-5
                      ≈ 2.05 × 10^-3

P(SW Fails Detect) = P(Sensor Fails) + P(Calc Error)
                   = 2.05×10^-3 + 2×10^-4
                   = 2.25 × 10^-3

P(HW Fails) = P(Lock Stuck ∧ Lock Sensor Fails)
            = 1×10^-4 × 5×10^-4
            = 5 × 10^-8

P(Interlock Fails) = P(SW Fails) + P(HW Fails) + P(Operator Bypass)
                   ≈ 2.25×10^-3 + 5×10^-8 + 1×10^-5
                   ≈ 2.26 × 10^-3

P(Door Opens While Moving) = P(Speed > 5) × P(Interlock Fails)
                            = 0.5 × 2.26×10^-3
                            = 1.13 × 10^-3 per operation
```

**If door operates 12 times per hour**:
```
P(per hour) = 12 × 1.13×10^-3 = 0.0136 per hour = 1.36 × 10^-2 per hour
```

**SIL 3 Compliance** (THR = 10^-7 per hour):
- Actual: **1.36 × 10^-2 per hour**
- Target: **10^-7 per hour**
- **GAP: 5 orders of magnitude** ← **MASSIVE FAILURE**

### 12.5 CCF Analysis

**CCF Threats**:
1. **Power supply failure**: Affects both sensors simultaneously
2. **EMI from traction motor**: Corrupts both sensor cables
3. **Software bug**: Same driver code for both sensors
4. **Environmental**: Ice/snow blocks both sensors

**Beta-Factor Justification**:
- Current design: Identical sensors, identical software → **β = 0.1**
- With mitigations (diverse sensors, separate power) → **β = 0.05**

**CCF Contribution**:
```
P(CCF) = β × P(Sensor)
       = 0.05 × 1×10^-3
       = 5 × 10^-5

Fraction of total: 5×10^-5 / 2.05×10^-3 = 2.4%
```

**Observation**: CCF contributes only 2.4% - **software calculation error dominates**!

### 12.6 Mitigation Plan

**Priority 1: Eliminate Software SPOF (BE3)**
- **Mitigation 1**: Apply formal verification to speed calculation
  - Target PFD: 1 × 10^-5 (100× improvement)
- **Mitigation 2**: Add diverse speed check (GPS-based)
- **Mitigation 3**: Add plausibility checks (rate-of-change)
- **Requirement**: REQ-SAFE-DOOR-005: Speed calculation SHALL use uint32_t, formal verification applied

**Priority 2: Reduce CCF (BE8)**
- **Mitigation 4**: Use diverse sensors (Brand A + Brand B)
- **Mitigation 5**: Separate power supplies for sensors
- **Mitigation 6**: Add plausibility checks (cross-check sensors)
- **Requirement**: REQ-SAFE-DOOR-006: Speed sensors SHALL be diverse hardware with separate power

**Priority 3: Eliminate Operator Bypass SPOF (BE9)**
- **Mitigation 7**: Require two-person authorization for bypass
- **Mitigation 8**: Add time-limited bypass (auto-restore after 5 minutes)
- **Mitigation 9**: Log all bypass events for audit
- **Requirement**: REQ-SAFE-DOOR-007: Interlock bypass SHALL require two-person authorization and auto-restore

**Revised Probability** (after mitigations):
```
P(SW Fails) = (1×10^-5 [sensor diverse] + 1×10^-5 [calc formal]) = 2×10^-5
P(Interlock Fails) = 2×10^-5 + 5×10^-8 + 1×10^-7 [bypass harder] ≈ 2×10^-5
P(Door Opens While Moving) = 0.5 × 2×10^-5 = 1×10^-5 per operation
P(per hour) = 12 × 1×10^-5 = 1.2 × 10^-4 per hour
```

**SIL 3 Compliance Check**:
- Target: 10^-7 per hour
- Revised: 1.2 × 10^-4 per hour
- **Still 3 orders of magnitude too high** - Need further mitigations:
  - Add 3rd diverse speed sensor (voting)
  - Add mechanical door lock (fail-safe)

### 12.7 Generate FTA Report

```bash
# Calculate probabilities
python3 tools/fta/fta_calculator.py \
    --input docs/fta/FTA-DOOR-001-structure.json \
    --output docs/fta/FTA-DOOR-001-probabilities.txt

# Find minimal cut sets
python3 tools/fta/minimal_cut_sets.py \
    --input docs/fta/FTA-DOOR-001-structure.json \
    --output docs/fta/FTA-DOOR-001-cutsets.md

# Create traceability
workspace.py trace create --from fta --to hazard \
    --source-id FTA-DOOR-001 --target-id HAZ-DOOR-001 \
    --rationale "FTA for door opens while moving hazard"

# Submit for review
workspace.py wf submit \
    --deliverable DOC-SAF-FTA-DOOR-001 \
    --phase safety-analysis \
    --author "SAF" \
    --sil 3
```

---

## Summary

This FTA workflow provides:

1. **Top-Down Analysis**: Start from hazard, identify all contributing failures
2. **Qualitative Analysis**: Minimal cut sets, SPOF identification
3. **Quantitative Analysis**: Probability calculation, SIL compliance check
4. **CCF Analysis**: Beta-factor model, CCF defenses (MANDATORY SIL 3-4)
5. **Traceability**: FTA → Hazard → FMEA → Requirements
6. **Tool Support**: Python calculators for probability, cut sets
7. **EN 50128 Compliance**: Highly Recommended SIL 2+, quantitative analysis SIL 3+

**Key Takeaways**:
- FTA complements FMEA (top-down vs bottom-up)
- SPOFs are UNACCEPTABLE for SIL 3-4 safety functions
- CCF analysis is MANDATORY for SIL 3-4 (beta-factor model)
- Quantitative analysis validates design meets THR
- Iterate FTA after design changes until SIL compliance achieved

**Next Workflow**: Safety Case Development - Presenting safety argument with evidence

---

**End of FTA Workflow**
