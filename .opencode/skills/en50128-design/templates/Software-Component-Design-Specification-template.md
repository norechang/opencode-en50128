# Software Component Design Specification (SCDS)

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 Sections 7.4.4.1–7.4.4.6, Table A.4, Annex C item 15

> **One SCDS per component.** Copy this template once per software component.
> Written by the Designer (DES) on the basis of the Software Design Specification (§7.4.4.1).

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | [DOC-015-SCDS-{COMPONENT}-NNN] |
| **Version** | [X.Y] |
| **Date** | [YYYY-MM-DD] |
| **Project** | [Project Name] |
| **Component Name** | [Component Name] |
| **Component ID** | [COMP-XXX] |
| **SIL Level** | [0, 1, 2, 3, or 4] |
| **Author** | [Name], Designer |
| **Reviewer** | [Name], Verifier |
| **Approver** | [Name], [Role] |
| **Status** | [Draft \| Review \| Approved \| Baseline] |

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft | - |

## APPROVALS

**SIL 0–2**: Author (DES), QUA, VER, PM  
**SIL 3–4**: Author (DES), QUA, VER (independent), VAL (independent), PM

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author (DES)** | [Name] | | YYYY-MM-DD |
| **QUA** | [Name] | | YYYY-MM-DD |
| **VER** | [Name] | | YYYY-MM-DD |
| **VAL** (SIL 3–4) | [Name] | | YYYY-MM-DD |
| **PM** | [Name] | | YYYY-MM-DD |

---

## 1. INTRODUCTION

### 1.1 Purpose

[State the purpose of this document. Example:]

This Software Component Design Specification (SCDS) provides the complete detailed design for the [Component Name] software component. It specifies all software units, interfaces, data structures, algorithms, and technique/measure selections required to implement this component in C, in accordance with EN 50128:2011 §7.4.4.

**Intended Audience**:
- Software implementers (IMP)
- Component testers (TST)
- Independent verifier (VER)

### 1.2 Scope

This SCDS covers the [Component Name] component only. It describes:
- All software units (functions) within the component
- Interfaces to other components and the environment
- Internal data structures and type definitions
- Algorithms and control flow for each software unit
- SIL-specific technique and measure selection
- Complexity limits and traceability

**Out of Scope**:
- System-level architecture (covered by SAS)
- Other components (each has its own SCDS)
- Source code (produced during Phase 5: Implementation)

### 1.3 SIL Classification

**Component SIL Level**: [0, 1, 2, 3, or 4] *(no further apportionment within this component — §7.4.4.3c)*

**EN 50128 Design Techniques Applied** (Table A.4):

| Technique | SIL 0 | SIL 1 | SIL 2 | SIL 3-4 | Applied |
|-----------|-------|-------|-------|---------|---------|
| Modular Approach | HR | **M** | **M** | **M** | [Yes/No] |
| Design and Coding Standards | HR | HR | HR | **M** | [Yes/No] |
| Structured Methodology | R | HR | HR | HR | [Yes/No] |
| Structured Programming | R | HR | HR | **M** | [Yes/No] |
| Analysable Programs | R | R | HR | **M** | [Yes/No] |
| Defensive Programming | R | HR | HR | HR | [Yes/No] |
| Formal Methods | - | R | R | HR | [Yes/No] |

**SIL-Specific Design Constraints**:
- **SIL 2+**: MISRA C:2012 compliance **MANDATORY**
- **SIL 2+**: Static memory allocation only (no `malloc`/`calloc`/`realloc`/`free`) **MANDATORY**
- **SIL 3-4**: Cyclomatic complexity ≤ 10 per function **REQUIRED**
- **SIL 3-4**: Structured programming **MANDATORY**
- **SIL 3-4**: No recursion (highly recommended)

### 1.4 Definitions and Acronyms

| Term | Definition |
|------|------------|
| **Unit** | Lowest-level software element: a single function or subroutine |
| **Component** | A cohesive group of software units with defined interfaces |
| **WCET** | Worst-Case Execution Time |
| **Complexity** | Cyclomatic complexity (McCabe metric) |

### 1.5 References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications — Software for railway control and protection systems |
| **[SDS]** | Software Design Specification, DOC-010-SDS-YYYY-NNN |
| **[SRS]** | Software Requirements Specification, DOC-006-SRS-YYYY-NNN |
| **[SAS]** | Software Architecture Specification, DOC-009-SAS-YYYY-NNN |
| **[SIS]** | Software Interface Specifications, DOC-011-SIS-YYYY-NNN |
| **[MISRAC]** | MISRA C:2012 Guidelines for the use of the C language in critical systems |

---

## 2. COMPONENT IDENTIFICATION

*(EN 50128 §7.4.4.3a, §7.4.4.3c)*

| Field | Value |
|-------|-------|
| **Component ID** | [COMP-XXX] |
| **Component Name** | [Component Name] |
| **SDS Entry** | Section [X.Y] of DOC-010-SDS-YYYY-NNN |
| **SIL Level** | [0–4] — no further apportionment within this component |
| **C Header File** | [`component_name.h`] |
| **C Source File** | [`component_name.c`] |

**Parent SDS Entry**: [Brief description of the component's role as stated in the SDS, e.g., "This component implements the door latch control loop (MOD-LATCH in SDS Section 3.3)."]

**Traceability to SRS**:

| SRS Requirement | Requirement Title |
|-----------------|-------------------|
| REQ-XXX-NNN | [Requirement title] |
| [Add all SRS requirements allocated to this component] | |

---

## 3. SOFTWARE UNITS

*(EN 50128 §7.4.4.3a)*

List every function/subroutine that constitutes this component. Each unit is traced to this component and to the SDS.

| Unit ID | Function Name | Type | Complexity Target | SDS Reference |
|---------|---------------|------|-------------------|---------------|
| UNIT-001 | `component_init` | Public | ≤ [N] | SDS §X.Y |
| UNIT-002 | `component_process` | Public | ≤ [N] | SDS §X.Y |
| UNIT-003 | `component_get_status` | Public | ≤ [N] | SDS §X.Y |
| UNIT-004 | `component_private_helper` | Private (static) | ≤ [N] | SDS §X.Y |
| [Add all units] | | | | |

**Complexity limit for this component (SIL [X])**: ≤ [10 / 15 / 20] per function.

---

## 4. INTERFACES

*(EN 50128 §7.4.4.3b)*

### 4.1 Public API

All public functions declared in `component_name.h`:

```c
/**
 * @brief Initialize the [Component Name] component.
 * @pre   [Precondition, e.g., hardware initialised]
 * @post  [Postcondition, e.g., component ready, state = IDLE]
 * @return ERROR_NONE on success, or error code on failure.
 */
error_t component_init(void);

/**
 * @brief Perform the main periodic processing for [Component Name].
 *        Call every [N] ms.
 * @param[in]  input   Pointer to input data structure (must not be NULL).
 * @param[out] output  Pointer to output data structure (must not be NULL).
 * @return ERROR_NONE on success, or error code on failure.
 */
error_t component_process(const component_input_t* input,
                           component_output_t*       output);

/**
 * @brief Retrieve the current status of the component.
 * @return Current component status value.
 */
component_status_t component_get_status(void);
```

### 4.2 Dependencies — Modules Called by This Component

| Called Module | Function Used | Purpose |
|---------------|---------------|---------|
| [Module Name] | `module_function()` | [Why this component calls it] |
| [Add all dependencies] | | |

### 4.3 Inputs and Outputs

**Input Data Structure** (`component_input_t`):

| Field | Type | Range / Units | Source | Description |
|-------|------|---------------|--------|-------------|
| `field_name` | `uint16_t` | [0–65535] | [Module/sensor] | [Description] |
| [Add all fields] | | | | |

**Output Data Structure** (`component_output_t`):

| Field | Type | Range / Units | Destination | Description |
|-------|------|---------------|-------------|-------------|
| `field_name` | `uint8_t` | [0–255] | [Module/actuator] | [Description] |
| [Add all fields] | | | | |

---

## 5. DATA STRUCTURES

*(EN 50128 §7.4.4.3d)*

All types use fixed-width integers (MISRA C:2012 Rule 6.1, mandatory SIL 2+). No dynamic allocation.

### 5.1 Type Definitions

```c
/* ---- Enumerations ---- */

typedef enum {
    COMPONENT_STATE_IDLE    = 0U,   /*!< Component idle, awaiting command */
    COMPONENT_STATE_ACTIVE  = 1U,   /*!< Component executing nominal operation */
    COMPONENT_STATE_FAULT   = 2U    /*!< Component fault detected */
} component_state_t;

/* ---- Input / Output structures ---- */

typedef struct {
    uint16_t field_a;   /*!< [Description, range, units] */
    uint8_t  field_b;   /*!< [Description, range, units] */
    bool     flag_c;    /*!< [Description] */
} component_input_t;

typedef struct {
    uint8_t field_x;    /*!< [Description, range, units] */
    bool    flag_y;     /*!< [Description] */
} component_output_t;

typedef uint8_t component_status_t; /*!< Bitmask: bit 0=ready, bit 1=fault, bits 2-7 reserved */
```

### 5.2 Internal State (Module-Private)

```c
typedef struct {
    component_state_t state;            /*!< Current operating state */
    component_state_t prev_state;       /*!< Previous state (for diagnostics) */
    uint32_t          state_entry_ms;   /*!< Timestamp of last state transition (ms) */
    uint8_t           error_code;       /*!< Most recent error code (0 = none) */
    uint8_t           retry_count;      /*!< Consecutive retry attempts */
} component_module_state_t;

static component_module_state_t g_component_state;  /* Hidden from other modules */
```

### 5.3 Constants

```c
#define COMPONENT_TIMEOUT_MS      (1000U)   /*!< Maximum operation timeout */
#define COMPONENT_MAX_RETRIES     (3U)      /*!< Maximum retry attempts before FAULT */
#define COMPONENT_INPUT_MIN       (0U)      /*!< Minimum valid input value */
#define COMPONENT_INPUT_MAX       (1000U)   /*!< Maximum valid input value */
```

**Static Allocation Justification**: All variables are statically allocated (`static` or file-scope). No `malloc`, `calloc`, `realloc`, or `free` is used anywhere in this component, complying with EN 50128 §7.4 and MISRA C:2012 Rule 21.3.

---

## 6. ALGORITHMS

*(EN 50128 §7.4.4.3d)*

Design is self-consistent and sufficient to transform into C code (§7.4.4.3 last paragraph). Algorithms are expressed as pseudocode.

### 6.1 `component_init`

```
FUNCTION component_init() → error_t:
    // 1. Initialise internal state to safe defaults
    g_component_state.state        ← COMPONENT_STATE_IDLE
    g_component_state.prev_state   ← COMPONENT_STATE_IDLE
    g_component_state.state_entry_ms ← current_time_ms()
    g_component_state.error_code   ← 0
    g_component_state.retry_count  ← 0

    // 2. Perform hardware / interface initialisation [if applicable]
    result ← [hardware_init_call()]
    IF result ≠ ERROR_NONE THEN
        g_component_state.state ← COMPONENT_STATE_FAULT
        g_component_state.error_code ← ERROR_INIT_FAILED
        RETURN ERROR_INIT_FAILED

    RETURN ERROR_NONE
```

**Estimated cyclomatic complexity**: 2

---

### 6.2 `component_process`

```
FUNCTION component_process(input*, output*) → error_t:

    // 1. Defensive input validation
    IF input = NULL OR output = NULL THEN
        RETURN ERROR_NULL_POINTER

    IF input.field_a > COMPONENT_INPUT_MAX OR
       input.field_a < COMPONENT_INPUT_MIN THEN
        RETURN ERROR_INVALID_INPUT

    // 2. Initialise output to safe defaults
    output.field_x ← 0
    output.flag_y  ← false

    // 3. State machine dispatch
    SWITCH g_component_state.state:

        CASE COMPONENT_STATE_IDLE:
            [Describe idle behaviour and transition triggers]
            IF [activation condition] THEN
                component_transition(COMPONENT_STATE_ACTIVE)

        CASE COMPONENT_STATE_ACTIVE:
            [Describe active processing, call private helpers as needed]
            result ← component_execute_operation(input, output)
            IF result ≠ ERROR_NONE THEN
                component_transition(COMPONENT_STATE_FAULT)
                g_component_state.error_code ← result
            ELSE IF [completion condition] THEN
                component_transition(COMPONENT_STATE_IDLE)

        CASE COMPONENT_STATE_FAULT:
            // Fail-safe: zero outputs, do not process
            output.field_x ← 0
            output.flag_y  ← false
            IF [fault clear condition] AND retry_count < COMPONENT_MAX_RETRIES THEN
                g_component_state.retry_count ← g_component_state.retry_count + 1
                component_transition(COMPONENT_STATE_IDLE)

        DEFAULT:
            // Should never be reached — defensive catch-all
            component_transition(COMPONENT_STATE_FAULT)
            RETURN ERROR_INVALID_STATE

    RETURN ERROR_NONE
```

**Estimated cyclomatic complexity**: 9

---

### 6.3 `component_get_status`

```
FUNCTION component_get_status() → component_status_t:
    status ← 0
    IF g_component_state.state ≠ COMPONENT_STATE_FAULT THEN
        status ← status | 0x01    // bit 0: ready
    IF g_component_state.state = COMPONENT_STATE_FAULT THEN
        status ← status | 0x02    // bit 1: fault
    RETURN status
```

**Estimated cyclomatic complexity**: 2

---

### 6.4 `component_transition` *(static — private)*

```
FUNCTION component_transition(new_state) → void:
    g_component_state.prev_state   ← g_component_state.state
    g_component_state.state        ← new_state
    g_component_state.state_entry_ms ← current_time_ms()
```

**Estimated cyclomatic complexity**: 1

---

### 6.5 [Additional Units]

[Add one subsection per additional software unit, following the pattern above.]

---

## 7. SIZE AND COMPLEXITY

*(EN 50128 §7.4.4.5)*

Size and complexity of this component are balanced. Each function is designed to remain within the cyclomatic complexity limit for SIL [X].

| Unit | Function | Estimated Complexity | SIL Limit | Status |
|------|----------|---------------------|-----------|--------|
| UNIT-001 | `component_init` | 2 | ≤ [N] | ✓ |
| UNIT-002 | `component_process` | 9 | ≤ [N] | ✓ |
| UNIT-003 | `component_get_status` | 2 | ≤ [N] | ✓ |
| UNIT-004 | `component_transition` | 1 | ≤ [N] | ✓ |
| **Maximum** | | **9** | **≤ [N]** | **✓ Compliant** |

**Complexity reduction strategy** (if any function exceeds the SIL limit): [Describe how the function will be split or refactored.]

---

## 8. TECHNIQUES AND MEASURES

*(EN 50128 §7.4.4.6)*

The following techniques from Table A.4 are applied to this component. The combination is justified as a set satisfying §4.8 and §4.9.

| Technique | Table A.4 ID | SIL [X] | Applied | Justification |
|-----------|-------------|---------|---------|---------------|
| Modular Approach | D.38 | M (SIL 1+) | **Yes** | Component is a self-contained module with defined API |
| Structured Methodology | D.52 | HR (SIL 3-4) | **Yes** | Pseudocode algorithms defined for every unit |
| Structured Programming | D.53 | M (SIL 3-4) | **Yes** | No GOTO, CONTINUE, or unstructured jumps |
| Design and Coding Standards | A.20 | M (SIL 3-4) | **Yes** | MISRA C:2012 applied; coding standard referenced in SQAP |
| Analysable Programs | D.2 | M (SIL 3-4) | **Yes** | Static analysis (PC-lint Plus / Cppcheck) planned |
| Defensive Programming | D.14 | HR (SIL 1+) | **Yes** | All public function inputs validated; NULL checks present |
| Formal Methods | D.28 | HR (SIL 3-4) | [Yes/No] | [Justify if not applied at SIL 3-4] |

**Combination Justification (§4.8 and §4.9)**:

The selected techniques collectively ensure that: (a) the component can be systematically specified, reviewed, and verified; (b) the code derived from this design will be statically analysable with quantified complexity; (c) defensive programming provides defence-in-depth against invalid inputs; and (d) the design coding standards (MISRA C:2012) eliminate entire classes of C language hazards.

---

## 9. TRACEABILITY MATRIX

*(EN 50128 §5.3.2.7, §6.5.4.14, §7.4.4.13b)*

### 9.1 SRS Requirements → Component

| SRS Requirement | Requirement Title | Unit(s) Implementing | Status |
|-----------------|-------------------|----------------------|--------|
| REQ-XXX-NNN | [Title] | UNIT-001, UNIT-002 | Traced |
| [Add all allocated requirements] | | | |

### 9.2 SDS Entry → Component

| SDS Entry | SDS Section | SCDS Section |
|-----------|-------------|--------------|
| [SDS component entry ID] | SDS §X.Y | Section 2 (Component Identification) |

### 9.3 Component → Software Units

| Component | Unit ID | Function Name |
|-----------|---------|---------------|
| [COMP-XXX] | UNIT-001 | `component_init` |
| [COMP-XXX] | UNIT-002 | `component_process` |
| [COMP-XXX] | UNIT-003 | `component_get_status` |
| [COMP-XXX] | UNIT-004 | `component_transition` |

### 9.4 Software Units → Component Test Specification

| Unit ID | Function Name | Test Case IDs (SCTS) |
|---------|---------------|----------------------|
| UNIT-001 | `component_init` | TC-COMP-XXX-001, TC-COMP-XXX-002 |
| UNIT-002 | `component_process` | TC-COMP-XXX-003 – TC-COMP-XXX-010 |
| UNIT-003 | `component_get_status` | TC-COMP-XXX-011 |
| UNIT-004 | `component_transition` | TC-COMP-XXX-012 |

---

## 10. DESIGN REVIEW CHECKLIST

*(EN 50128 §7.4.4.4 — document shall be readable, understandable and testable)*

### 10.1 Completeness (§7.4.4.2–§7.4.4.6)

- [ ] Author, configuration history (version/date/author/changes), and short description present (§7.4.4.2)
- [ ] All lowest software units identified and traced to SDS upper-level entry (§7.4.4.3a)
- [ ] Interfaces with environment and other components fully specified — inputs and outputs typed (§7.4.4.3b)
- [ ] SIL level stated; no further apportionment within the component (§7.4.4.3c)
- [ ] Detailed algorithms and data structures present for every unit (§7.4.4.3d)
- [ ] Design is self-consistent and sufficient to transform into code (§7.4.4.3 last paragraph)
- [ ] Size and complexity of the component are balanced (§7.4.4.5)
- [ ] Technique/measure selection from Table A.4 justified as a set per §4.8 and §4.9 (§7.4.4.6)

### 10.2 Quality (§7.4.4.4)

- [ ] Document is readable and understandable without reference to author
- [ ] Document is testable — all behaviours can be verified by test
- [ ] All functions have preconditions and postconditions defined
- [ ] Defensive programming applied to all public functions (null checks, range checks)
- [ ] Error codes defined and all error paths handled

### 10.3 SIL-Specific Constraints

- [ ] MISRA C:2012 design compliance confirmed (SIL 2+)
- [ ] Static allocation only — no `malloc`/`free` used (SIL 2+)
- [ ] Cyclomatic complexity ≤ [10 / 15 / 20] for all units (SIL-specific limit)
- [ ] No recursion (SIL 3-4 highly recommended)
- [ ] No unreachable code paths in algorithms

### 10.4 Traceability

- [ ] All SRS requirements allocated to this component are traced to at least one unit (§5.3.2.7)
- [ ] Component traced to SDS entry
- [ ] All units traced to test cases in the Component Test Specification

---

## 11. COMPLIANCE MATRIX

| EN 50128 Requirement | Section | Evidence in this Document | Status |
|----------------------|---------|--------------------------|--------|
| Author, configuration history, short description | §7.4.4.2 | STANDARD HEADER + DOCUMENT CONTROL | ✓ |
| All lowest software units identified and traced | §7.4.4.3a | Section 3 (Software Units) | ✓ |
| Detailed interfaces with environment and other components | §7.4.4.3b | Section 4 (Interfaces) | ✓ |
| SIL level stated; no further apportionment | §7.4.4.3c | Section 2 (Component Identification) | ✓ |
| Detailed algorithms and data structures | §7.4.4.3d | Sections 5–6 (Data Structures, Algorithms) | ✓ |
| Self-consistent; sufficient to transform into code | §7.4.4.3 ¶last | Section 6 (Algorithms — pseudocode) | ✓ |
| Readable, understandable and testable | §7.4.4.4 | Section 10.2 review checklist | ✓ |
| Size and complexity balanced | §7.4.4.5 | Section 7 (Size and Complexity) | ✓ |
| Techniques and measures from Table A.4 justified | §7.4.4.6 | Section 8 (Techniques and Measures) | ✓ |
| Traceability to SDS entry | §7.4.4.13a | Section 9.2 | ✓ |
| Modular Approach (M SIL 1+) | Table A.4 | Section 8 | ✓ |
| Design and Coding Standards (M SIL 3-4) | Table A.4 | Section 8 (MISRA C:2012) | ✓ |
| Structured Programming (M SIL 3-4) | Table A.4 | Section 8 | ✓ |

---

## APPENDIX A: FUNCTION DESIGN TEMPLATE

Use this template for each additional software unit not already described in Section 6:

```markdown
### [Section Number] `function_name` [Public | Private (static)]

**Unit ID**: UNIT-NNN  
**SDS Reference**: SDS §X.Y  
**Complexity Target**: ≤ [N]

**Prototype**:
\```c
error_t function_name(const input_type_t* input, output_type_t* output);
\```

**Purpose**: [One sentence.]

**Parameters**:
- `input` [in]:  [Type, range, units, source]
- `output` [out]: [Type, range, units, destination]

**Return**: ERROR_NONE on success; error code on failure.

**Preconditions**: [State before this function is called]

**Postconditions**: [Guaranteed state after this function returns]

**Algorithm**:
\```
PSEUDOCODE HERE
\```

**Error Handling**:
- [Error condition] → [Response and output value]

**Estimated Complexity**: [N]

**Test Cases**: TC-COMP-XXX-NNN, ...
```

---

## DOCUMENT HISTORY

This document is maintained under configuration control per SCMP. All changes require CCB approval.

**Current Version**: [Version from header]  
**Last Updated**: [Date from header]  
**Next Review**: [Before Phase 5: Implementation begins, or after any SDS change affecting this component]

---

**END OF DOCUMENT**
