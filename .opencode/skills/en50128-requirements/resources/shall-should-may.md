# Modal Verb Usage Guide (SHALL/SHOULD/MAY)

**Purpose**: Define correct usage of modal verbs in requirements statements per RFC 2119.

**Standard Reference**: RFC 2119 - Key words for use in RFCs to Indicate Requirement Levels

**Application**: EN 50128 software requirements specification

---

## RFC 2119 Standard Keywords

### 1. SHALL (MUST) - Mandatory Requirement

**Definition**: Absolute requirement that MUST be implemented.

**Usage**: Use SHALL when the requirement is:
- **Mandatory** for all SIL levels
- **Safety-critical** (failure could cause hazard)
- **Regulatory** (required by standard or law)
- **Functionally essential** (system cannot work without it)

**Examples**:
```
✅ CORRECT:
REQ-001: The system SHALL validate all sensor inputs before processing.
REQ-002: The emergency brake SHALL activate within 200 milliseconds.
REQ-003: All functions SHALL return an error code on failure.

❌ INCORRECT:
REQ-BAD: The system must validate inputs. (Use SHALL, not "must")
REQ-BAD: The system will validate inputs. (Use SHALL for requirements, not "will")
```

**Test Implication**: ALL SHALL requirements MUST be tested and verified (100% test coverage for SIL 3-4).

---

### 2. SHALL NOT (MUST NOT) - Prohibition

**Definition**: Absolute prohibition. This action MUST NOT be performed.

**Usage**: Use SHALL NOT for:
- **Forbidden actions** (e.g., dynamic memory allocation in SIL 2+)
- **Safety constraints** (e.g., no recursion in SIL 3-4)
- **Regulatory prohibitions**

**Examples**:
```
✅ CORRECT:
REQ-010: The system SHALL NOT use dynamic memory allocation (malloc, free).
REQ-011: Safety-critical functions SHALL NOT use recursion.
REQ-012: The system SHALL NOT proceed without sensor validation.

❌ INCORRECT:
REQ-BAD: The system must not use malloc. (Use SHALL NOT, not "must not")
REQ-BAD: Don't use malloc. (Too informal, use SHALL NOT)
```

**Verification**: Code inspection, static analysis, code review MUST verify prohibition is enforced.

---

### 3. SHOULD (RECOMMENDED) - Highly Recommended

**Definition**: Strong recommendation. May be valid reasons NOT to implement, but rationale REQUIRED.

**Usage**: Use SHOULD when:
- **Highly recommended** but not absolutely mandatory
- **Best practice** that should normally be followed
- **Important** but system can function without it
- **Rationale required** if not implemented

**Examples**:
```
✅ CORRECT:
REQ-020: The system SHOULD log all fault events to non-volatile memory.
REQ-021: Diagnostic data SHOULD be available via a maintenance interface.
REQ-022: The system SHOULD provide operator warnings before entering safe state.

❌ INCORRECT:
REQ-BAD: The system should probably log faults. (Too weak, remove "probably")
REQ-BAD: It would be nice if... (Use SHOULD, not informal language)
```

**Decision**: If SHOULD requirement NOT implemented:
- Document rationale in design decision log
- Obtain approval from stakeholders
- Document in Software Design Specification

**Example Rationale**:
```
REQ-020: System SHOULD log all fault events.
Decision: NOT IMPLEMENTED in v1.0
Rationale: Non-volatile memory unavailable on target hardware v1.0.
          Will be added in v2.0 when EEPROM module available.
Approved by: Project Manager, Safety Engineer (2026-03-15)
```

---

### 4. SHOULD NOT (NOT RECOMMENDED) - Discouraged

**Definition**: Action is NOT recommended. May be acceptable in specific circumstances, but rationale REQUIRED.

**Usage**: Use SHOULD NOT for:
- **Discouraged practices** (e.g., recursion in SIL 3-4)
- **Not recommended** but not absolutely forbidden
- **Requires justification** if done

**Examples**:
```
✅ CORRECT:
REQ-030: The system SHOULD NOT use floating-point arithmetic in safety-critical functions.
REQ-031: Function complexity SHOULD NOT exceed cyclomatic complexity of 10.
REQ-032: The system SHOULD NOT rely on external time synchronization for safety functions.

❌ INCORRECT:
REQ-BAD: Try to avoid floating-point. (Use SHOULD NOT, not "try to avoid")
```

**Decision**: If SHOULD NOT requirement IS implemented (action taken despite discouragement):
- Document rationale in design decision log
- Perform impact analysis (safety, performance, maintainability)
- Obtain approval from Safety Engineer and Project Manager

---

### 5. MAY (OPTIONAL) - Optional

**Definition**: Truly optional. Implementation is discretionary.

**Usage**: Use MAY for:
- **Nice-to-have** features
- **Optional enhancements**
- **Discretionary functionality**
- **No impact if not implemented**

**Examples**:
```
✅ CORRECT:
REQ-040: The system MAY provide a graphical visualization of train position.
REQ-041: The operator interface MAY support multiple languages.
REQ-042: Diagnostic reports MAY be exported to PDF format.

❌ INCORRECT:
REQ-BAD: The system may or may not... (Too vague, clarify if optional or conditional)
REQ-BAD: The system can provide... (Use MAY for optional, "can" is ambiguous)
```

**Test Implication**: MAY requirements are optional to test. Test only if implemented.

---

### 6. WILL - Statement of Fact (NOT a Requirement)

**Definition**: Statement of fact, external behavior, or future action. NOT a requirement on the system being specified.

**Usage**: Use WILL for:
- **External entities** (users, other systems, hardware)
- **Environmental facts**
- **Assumed behavior** (not system responsibility)

**Examples**:
```
✅ CORRECT:
"The operator WILL provide train destination via the touchscreen interface."
(Describes user action, not system requirement)

"The speed sensor WILL provide data in km/h units."
(Describes hardware behavior, not software requirement)

"The train WILL be equipped with redundant braking systems."
(Describes system context, not software requirement)

❌ INCORRECT:
REQ-BAD: The system WILL validate sensor data.
(This is a requirement on the system → Use SHALL, not WILL)
```

**Conversion to Requirements**:
```
Statement of fact:
"The operator WILL provide train destination via touchscreen."

Corresponding system requirement:
REQ-050: The system SHALL accept train destination input from the touchscreen interface.
```

---

## Modal Verb Decision Tree

```
Is this a requirement on the system being specified?
│
├─ NO → Use WILL (statement of fact about external entity)
│
└─ YES → Is it absolutely mandatory?
    │
    ├─ YES → Is it something the system MUST do?
    │   │
    │   ├─ YES → Use SHALL (mandatory action)
    │   │
    │   └─ NO → Use SHALL NOT (prohibited action)
    │
    └─ NO → Is it highly recommended (rationale required if not done)?
        │
        ├─ YES → Is it something the system SHOULD do?
        │   │
        │   ├─ YES → Use SHOULD (recommended action)
        │   │
        │   └─ NO → Use SHOULD NOT (discouraged action)
        │
        └─ NO → Is it truly optional (no impact if not done)?
            │
            └─ YES → Use MAY (optional action)
```

---

## SIL-Specific Guidance

### SIL 0 (Non-Safety)
- SHALL: Mandatory functional requirements
- SHOULD: Recommended best practices
- MAY: Optional features
- **Flexibility**: More MAY requirements acceptable

### SIL 1-2 (Safety-Related)
- SHALL: Mandatory functional and safety requirements
- SHALL NOT: Safety constraints (e.g., no dynamic allocation for SIL 2+)
- SHOULD: Highly recommended practices
- MAY: Optional features (use sparingly in safety requirements)
- **Constraint**: More SHALL requirements, fewer MAY

### SIL 3-4 (Safety-Critical)
- SHALL: Vast majority of requirements (especially safety-critical)
- SHALL NOT: Strict safety constraints (no dynamic allocation, no recursion)
- SHOULD: Rare (use only for truly non-critical features)
- MAY: Very rare (avoid in safety requirements)
- **Strict**: Almost all safety requirements use SHALL

---

## Common Mistakes and Corrections

### Mistake 1: Using "must" instead of SHALL
```
❌ WRONG: The system must validate inputs.
✅ CORRECT: The system SHALL validate inputs.
```

### Mistake 2: Using "will" for system requirements
```
❌ WRONG: The system will validate inputs.
✅ CORRECT: The system SHALL validate inputs.
(Use WILL only for external entities: "The user will provide input.")
```

### Mistake 3: Using "should" for mandatory requirements
```
❌ WRONG: The system should apply emergency brake on overspeed.
✅ CORRECT: The system SHALL apply emergency brake on overspeed.
(Safety-critical requirements are mandatory → SHALL, not SHOULD)
```

### Mistake 4: Vague modal verbs
```
❌ WRONG: The system might validate inputs.
✅ CORRECT: The system MAY validate inputs (if optional).
          OR: The system SHALL validate inputs (if mandatory).
```

### Mistake 5: Mixing SHALL and MUST
```
❌ WRONG: The system SHALL validate inputs, and must check range.
✅ CORRECT: The system SHALL validate inputs and SHALL check range.
(Consistent terminology: use SHALL throughout)
```

### Mistake 6: Using "can" ambiguously
```
❌ WRONG: The system can provide diagnostics.
✅ CORRECT: The system MAY provide diagnostics. (if optional)
          OR: The system SHALL provide diagnostics. (if mandatory)
("can" is ambiguous - is it capability or requirement?)
```

---

## EN 50128 Mapping

**EN 50128** does not explicitly mandate RFC 2119 keywords, but they align well with EN 50128 recommendation levels:

| EN 50128 Level | RFC 2119 Keyword | Usage |
|----------------|------------------|-------|
| **Mandatory (M)** | SHALL / SHALL NOT | Absolute requirement or prohibition |
| **Highly Recommended (HR)** | SHOULD / SHOULD NOT | Strong recommendation, rationale if not followed |
| **Recommended (R)** | SHOULD (weaker) or MAY (stronger) | Suggested practice, optional |
| **Not Recommended (NR)** | SHOULD NOT | Discouraged, rationale if done |
| **-** (No recommendation) | MAY | Truly optional |

---

## Verification Implications

| Modal Verb | Test Coverage Requirement | Verification Method |
|------------|---------------------------|---------------------|
| SHALL | 100% (all SILs) | Test, Analysis, Inspection, Demonstration |
| SHALL NOT | 100% (prohibition verified) | Inspection, Static Analysis, Code Review |
| SHOULD | If implemented: 100% | Test if implemented; document rationale if not |
| SHOULD NOT | If implemented: verify rationale | Inspection, review rationale |
| MAY | If implemented: 100% | Test if implemented; no test if not |
| WILL (fact) | N/A (not a requirement) | N/A |

**SIL 3-4 Special Requirements**:
- ALL SHALL requirements: 100% test coverage MANDATORY
- Branch coverage: 100% MANDATORY
- Condition coverage: 100% MANDATORY
- MC/DC coverage: HIGHLY RECOMMENDED

---

## Checklist

Before finalizing requirements, verify:

- [ ] All requirements use one of: SHALL, SHALL NOT, SHOULD, SHOULD NOT, MAY
- [ ] No "must", "will" (for system reqs), "might", "can", "could"
- [ ] Safety-critical requirements (SIL 2+) use SHALL or SHALL NOT
- [ ] Optional features use MAY
- [ ] External entity behavior uses WILL (not SHALL)
- [ ] Consistent modal verb usage throughout document
- [ ] SHOULD requirements have rationale if not implemented
- [ ] SHOULD NOT requirements have rationale if implemented

---

## Standard References

- **RFC 2119** - Key words for use in RFCs to Indicate Requirement Levels (March 1997)
- **EN 50128:2011** - Railway Software Standard (requirement levels: M, HR, R, NR)
- **ISO/IEC/IEEE 29148:2018** - Systems and software engineering - Life cycle processes - Requirements engineering

---

## Related Resources

- `requirement-patterns.md` - Common requirement patterns with modal verbs
- `testability-guidelines.md` - How to make SHALL requirements testable
- `requirement-quality-checklist.md` - Quality checklist including modal verb usage
