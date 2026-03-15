# Requirements Quality Checklist

**Purpose**: Verify that each requirement meets EN 50128 quality standards.

**Usage**: Use this checklist for:
- Self-review by Requirements Engineer (REQ)
- Peer review by another REQ engineer
- Quality Assurance (QUA) review
- Verification (VER) review

**Standard References**:
- EN 50128:2011 Section 7.2 (Software Requirements)
- IEEE 29148:2018 (Requirements Engineering)

---

## Individual Requirement Quality Attributes

For **each requirement**, verify the following quality attributes:

### 1. Unambiguous ✓

**Definition**: Requirement has exactly ONE interpretation. No ambiguity.

**Check**:
- [ ] No vague terms ("quickly", "reliable", "efficient", "adequate", "appropriate")
- [ ] No ambiguous pronouns ("it", "this", "that" without clear antecedent)
- [ ] No subjective language ("user-friendly", "easy", "intuitive")
- [ ] Technical terms defined in glossary
- [ ] Quantitative values specified (no "some", "many", "few")

**Examples**:
```
❌ AMBIGUOUS:
"The system shall respond quickly to sensor input."
Problem: "quickly" is subjective, not measurable

✅ UNAMBIGUOUS:
"The system SHALL respond to sensor input within 50 milliseconds."
Clarity: "50 milliseconds" is precise and measurable

❌ AMBIGUOUS:
"The system shall be reliable."
Problem: "reliable" is vague, not measurable

✅ UNAMBIGUOUS:
"The system SHALL achieve Mean Time Between Failures (MTBF) ≥ 10,000 hours."
Clarity: Specific metric (MTBF) with quantitative threshold
```

**Action if NO**: Rewrite requirement with precise, quantitative language.

---

### 2. Testable (Verifiable) ✓

**Definition**: Requirement can be verified by Test, Analysis, Inspection, or Demonstration.

**Check**:
- [ ] Objective acceptance criteria defined
- [ ] Measurable quantities specified (time, count, percentage, etc.)
- [ ] Clear pass/fail criteria
- [ ] Verification method identified (Test, Analysis, Inspection, Demonstration)

**Examples**:
```
❌ NOT TESTABLE:
"The system shall be maintainable."
Problem: "maintainable" cannot be objectively measured

✅ TESTABLE:
"The system SHALL provide diagnostic codes for all fault conditions,
accessible via maintenance interface within 5 seconds."
Verification: Test (measure diagnostic code availability and response time)

❌ NOT TESTABLE:
"The software shall be well-structured."
Problem: "well-structured" is subjective

✅ TESTABLE:
"All software functions SHALL have cyclomatic complexity ≤ 10."
Verification: Analysis (use complexity analysis tool)
```

**Verification Methods**:
- **Test**: Execute test case, measure result
- **Analysis**: Static analysis, complexity analysis, formal proof
- **Inspection**: Code review, document review, checklist
- **Demonstration**: Show functionality in operational environment

**Action if NO**: Add measurable acceptance criteria or rewrite to make verifiable.

---

### 3. Clear ✓

**Definition**: Requirement is easily understood by all stakeholders (engineers, testers, customers).

**Check**:
- [ ] Simple sentence structure (avoid nested clauses)
- [ ] Consistent terminology (no synonyms for same concept)
- [ ] No jargon (or jargon defined in glossary)
- [ ] Active voice (not passive)
- [ ] One requirement per sentence (atomic)

**Examples**:
```
❌ UNCLEAR:
"The utilization of sensor input data for the effectuation of control
algorithm computation shall be implemented."
Problem: Overly complex, passive voice, jargon

✅ CLEAR:
"The system SHALL read sensor data and calculate control commands."
Clarity: Simple, active voice, direct

❌ UNCLEAR:
"It shall be validated."
Problem: Ambiguous pronoun "it" - what shall be validated?

✅ CLEAR:
"The speed sensor data SHALL be validated before processing."
Clarity: Explicit subject (speed sensor data)
```

**Action if NO**: Simplify language, use active voice, define jargon.

---

### 4. Correct ✓

**Definition**: Requirement accurately reflects stakeholder needs and system requirements.

**Check**:
- [ ] Traces to valid source (system requirement, hazard, stakeholder need)
- [ ] Consistent with source (no misinterpretation)
- [ ] Validated by stakeholders
- [ ] No contradictions with other requirements
- [ ] Aligns with domain knowledge (railway operations, safety)

**Examples**:
```
❌ INCORRECT:
System Requirement: "Train shall not exceed 120 km/h."
Software Requirement: "Speed limit is 150 km/h."
Problem: Contradicts system requirement

✅ CORRECT:
System Requirement: "Train shall not exceed 120 km/h."
Software Requirement: "The system SHALL trigger emergency brake when
speed exceeds 120 km/h."
Correctness: Aligns with system requirement
```

**Action if NO**: Validate with stakeholders, check traceability to source, resolve contradictions.

---

### 5. Feasible ✓

**Definition**: Requirement is technically and economically achievable with available technology, budget, and schedule.

**Check**:
- [ ] Technically possible with target hardware (CPU, memory, I/O)
- [ ] Achievable within project schedule
- [ ] Achievable within project budget
- [ ] No physical impossibilities (e.g., "response time = 0 milliseconds")
- [ ] C language implementation possible

**Examples**:
```
❌ INFEASIBLE:
"The system SHALL process 10 million sensor readings per millisecond."
Problem: Infeasible on target hardware (10 GHz equivalent)

✅ FEASIBLE:
"The system SHALL process 1000 sensor readings per second."
Feasibility: Achievable on target hardware (1 kHz sampling)

❌ INFEASIBLE:
"The system SHALL have zero latency."
Problem: Physical impossibility (speed of light, circuit delays)

✅ FEASIBLE:
"The system SHALL have response latency ≤ 10 milliseconds."
Feasibility: Achievable with real hardware
```

**Action if NO**: Revise requirement to be achievable, or obtain additional resources (hardware, budget, time).

---

### 6. Atomic ✓

**Definition**: Requirement expresses a SINGLE need. Cannot be decomposed further without losing meaning.

**Check**:
- [ ] One requirement per ID (not multiple requirements combined)
- [ ] No "and/or" conjunctions combining multiple requirements
- [ ] Can be implemented independently (or with clear dependencies)

**Examples**:
```
❌ NOT ATOMIC:
"The system shall read sensor data, validate it, and generate control commands."
Problem: Three distinct requirements combined (read, validate, generate)

✅ ATOMIC (split into 3):
REQ-001: "The system SHALL read speed sensor data via SPI interface."
REQ-002: "The system SHALL validate speed sensor data is within range [0, 300] km/h."
REQ-003: "The system SHALL generate control commands based on validated sensor data."
Atomicity: Each requirement expresses one need

❌ NOT ATOMIC:
"The system shall log faults and/or warnings."
Problem: "and/or" combines two requirements (faults, warnings)

✅ ATOMIC (split into 2):
REQ-010: "The system SHALL log all fault events."
REQ-011: "The system SHALL log all warning events."
```

**Action if NO**: Split requirement into multiple atomic requirements, each with unique ID.

---

### 7. Necessary ✓

**Definition**: Requirement documents an ESSENTIAL capability. Not superfluous or redundant.

**Check**:
- [ ] Capability is needed for system to function correctly
- [ ] Not redundant (not already stated by another requirement)
- [ ] Not "gold plating" (unnecessary feature creep)
- [ ] Justified by source (system req, hazard, stakeholder need)

**Examples**:
```
❌ UNNECESSARY:
"The system MAY display a 3D animated visualization of train position with
photorealistic graphics."
Problem: Gold plating, not essential for train control

✅ NECESSARY:
"The system SHALL display current train speed on the operator interface."
Necessity: Essential for operator awareness

❌ REDUNDANT:
REQ-001: "Speed shall be in range [0, 300] km/h."
REQ-002: "Speed shall not exceed 300 km/h."
Problem: REQ-002 is redundant (already covered by REQ-001)

✅ NECESSARY (consolidate):
REQ-001: "Speed SHALL be in range [0, 300] km/h."
```

**Action if NO**: Remove unnecessary requirement, or consolidate redundant requirements.

---

### 8. Implementation-Free ✓

**Definition**: Requirement states WHAT the system shall do, NOT HOW it shall be implemented.

**Check**:
- [ ] No design decisions (architecture, algorithms, data structures)
- [ ] No technology choices (specific libraries, frameworks) unless mandated
- [ ] Focuses on behavior and constraints, not solution
- [ ] Designer (DES) has freedom to choose implementation approach

**Examples**:
```
❌ IMPLEMENTATION-SPECIFIC:
"The system shall use a Kalman filter to estimate speed."
Problem: Prescribes specific algorithm (Kalman filter)

✅ IMPLEMENTATION-FREE:
"The system SHALL estimate speed with accuracy ±1 km/h."
Freedom: Designer can choose Kalman filter, moving average, or other approach

❌ IMPLEMENTATION-SPECIFIC:
"The system shall store data in a linked list."
Problem: Prescribes data structure (linked list)

✅ IMPLEMENTATION-FREE:
"The system SHALL store up to 100 sensor readings."
Freedom: Designer can choose array, linked list, circular buffer, etc.

EXCEPTION - When Mandated:
"The system SHALL implement all modules in MISRA C:2012 compliant code."
Justification: Language and standard mandated by EN 50128 and SQAP
```

**Exceptions** (implementation details in requirements):
- **Language**: "Implement in C" (mandated by project)
- **Standards**: "Comply with MISRA C:2012" (mandated by EN 50128 SIL 2+)
- **Regulatory**: "Use certified compiler" (mandated by regulation)
- **Interface**: "Use SPI interface at address 0x4000" (hardware constraint)

**Action if NO**: Rewrite to focus on "what" (behavior, constraints), not "how" (solution).

---

## Requirements Set Quality Attributes

For the **entire requirements set**, verify:

### 9. Complete ✓

**Check**:
- [ ] All system requirements covered (100% traceability for SIL 3-4)
- [ ] All hazards mitigated (from Hazard Log)
- [ ] All interfaces specified (hardware, software, communication, user)
- [ ] All quality attributes specified (performance, reliability, maintainability)
- [ ] All constraints identified (language, standards, hardware, regulatory)
- [ ] All functional areas addressed
- [ ] No TBDs (To Be Determined)

**Verification**:
- Traceability matrix: System Requirements → Software Requirements (100% coverage)
- Traceability matrix: Hazards → Safety Requirements (all hazards mitigated)
- Interface checklist: All interfaces specified
- Stakeholder review: No missing capabilities

**Action if NO**: Identify gaps, elicit missing requirements, update SRS.

---

### 10. Consistent ✓

**Check**:
- [ ] No conflicting requirements (contradictions)
- [ ] Terminology consistent throughout (no synonyms for same concept)
- [ ] All requirement IDs unique within document
- [ ] Units consistent (e.g., all speed in km/h, all time in ms)
- [ ] Consistent level of abstraction (not mixing high-level and low-level)

**Examples of Inconsistency**:
```
❌ CONFLICTING:
REQ-001: "Response time SHALL be ≤ 50 ms."
REQ-002: "Response time SHALL be ≤ 100 ms."
Problem: Conflict (which is correct? 50ms or 100ms?)

✅ CONSISTENT:
REQ-001: "Sensor read response time SHALL be ≤ 50 ms."
REQ-002: "Control loop cycle time SHALL be ≤ 100 ms."
Consistency: Different requirements (sensor read vs. control loop)

❌ INCONSISTENT TERMINOLOGY:
REQ-001: "The system shall monitor speed."
REQ-002: "The system shall track velocity."
Problem: "speed" and "velocity" used inconsistently (same concept)

✅ CONSISTENT:
REQ-001: "The system SHALL monitor speed."
REQ-002: "The system SHALL monitor speed in range [0, 300] km/h."
Consistency: "speed" used consistently
```

**Verification**:
- Terminology review: Create glossary, enforce usage
- Requirements cross-check: Identify contradictions
- Unit check: All requirements use same units

**Action if NO**: Resolve contradictions, standardize terminology, unify units.

---

### 11. Traceable ✓

**Check**:
- [ ] All requirements have unique IDs (format: REQ-<TYPE>-<NNN>)
- [ ] Backward traceability: All requirements trace to source (system req, hazard, stakeholder)
- [ ] Forward traceability: All requirements trace to test cases (reference)
- [ ] All traceability links valid (referenced items exist)
- [ ] No orphan requirements (requirements without sources)
- [ ] 100% coverage for SIL 3-4 (MANDATORY)

**Traceability Matrices**:
- System Requirements → Software Requirements (backward)
- Hazards → Safety Requirements (backward)
- Software Requirements → Test Cases (forward)

**Verification**:
- Use traceability validation tool: `workspace.py trace validate --phase requirements`
- Use gap detection tool: `workspace.py trace check-gaps --phase requirements`
- Manual inspection of traceability matrices

**Action if NO**: Establish traceability links, fix broken links, identify orphan requirements.

---

## SIL-Specific Checklist

### SIL 0 (Non-Safety)
- [ ] All requirements meet basic quality attributes (1-8)
- [ ] Requirements set is reasonably complete and consistent
- [ ] Traceability recommended but not mandatory

### SIL 1-2 (Safety-Related)
- [ ] All requirements meet quality attributes (1-8)
- [ ] Requirements set is complete and consistent
- [ ] Safety requirements identified (SIL 1+)
- [ ] Traceability highly recommended
- [ ] MISRA C considerations for SIL 2+ (data types, memory allocation)
- [ ] QUA review completed

### SIL 3-4 (Safety-Critical)
- [ ] All requirements meet quality attributes (1-8) - **MANDATORY**
- [ ] Requirements set is complete and consistent - **MANDATORY**
- [ ] Safety requirements identified with SIL assignments - **MANDATORY**
- [ ] 100% traceability (system→software, hazards→safety) - **MANDATORY**
- [ ] All requirements testable with objective acceptance criteria - **MANDATORY**
- [ ] Formal methods applied for safety-critical requirements - **HIGHLY RECOMMENDED**
- [ ] C language constraints considered (data types, memory, timing) - **MANDATORY**
- [ ] Independent VER review completed - **MANDATORY**
- [ ] VAL review completed - **MANDATORY**

---

## Review Process

### Step 1: Self-Review by REQ Engineer
- [ ] Use this checklist for every requirement
- [ ] Fix all issues identified
- [ ] Document any deviations with rationale

### Step 2: Peer Review (if available)
- [ ] Another REQ engineer reviews SRS
- [ ] Focus on requirements quality (checklist items 1-8)
- [ ] Focus on requirements set quality (checklist items 9-11)
- [ ] Document findings, address, re-review

### Step 3: Quality Assurance (QUA) Review
- [ ] QUA verifies document template compliance
- [ ] QUA verifies requirements quality (this checklist)
- [ ] QUA approval required

### Step 4: Verification (VER) Review (SIL 3-4 Independent)
- [ ] VER verifies requirements are testable
- [ ] VER verifies traceability is complete (100% for SIL 3-4)
- [ ] VER verifies SIL assignments justified
- [ ] VER approval required (MANDATORY for SIL 3-4)

### Step 5: Validation (VAL) Review
- [ ] VAL verifies requirements meet stakeholder needs
- [ ] VAL approval required

---

## Common Issues and Fixes

### Issue 1: Vague Language
**Problem**: "The system shall respond quickly."
**Fix**: "The system SHALL respond within 50 milliseconds."

### Issue 2: Ambiguous Pronouns
**Problem**: "It shall be validated."
**Fix**: "The speed sensor data SHALL be validated."

### Issue 3: Untestable Requirements
**Problem**: "The system shall be user-friendly."
**Fix**: "The operator SHALL be able to initiate emergency brake within 2 seconds."

### Issue 4: Multiple Requirements in One
**Problem**: "The system shall read, validate, and process sensor data."
**Fix**: Split into 3 requirements:
- REQ-001: "The system SHALL read sensor data."
- REQ-002: "The system SHALL validate sensor data."
- REQ-003: "The system SHALL process sensor data."

### Issue 5: Implementation Prescription
**Problem**: "The system shall use a linked list."
**Fix**: "The system SHALL store up to 100 readings."

### Issue 6: Missing SIL Assignment
**Problem**: Requirement without SIL level.
**Fix**: Assign SIL based on hazard analysis traceability.

---

## Tools

**Validation Tools**:
- `tools/requirement-validator.py` - Validate requirement format and basic quality
- `workspace.py trace validate` - Check traceability completeness
- `workspace.py trace check-gaps` - Find missing traceability links
- `workspace.py trace report` - Generate traceability reports

**Manual Review**:
- Use this checklist for each requirement
- Document findings in review record

---

## Standard References

- **EN 50128:2011 Section 7.2** - Software Requirements Specification
- **IEEE 29148:2018** - Requirements Engineering
- **RFC 2119** - Modal verb usage (SHALL, SHOULD, MAY)

---

## Related Resources

- `shall-should-may.md` - Modal verb usage guide
- `requirement-patterns.md` - Common requirement patterns
- `testability-guidelines.md` - How to make requirements testable
- `workflows/requirements-analysis.md` - Requirements analysis workflow
