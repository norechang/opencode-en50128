---
name: en50128-requirements
description: Requirements engineering patterns and workflows for EN 50128 railway software compliance
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  language: C
---

## What I do

I provide patterns, templates, and workflows for requirements engineering compliant with EN 50128 Section 7.2:
- Define requirement quality attributes (unambiguous, testable, traceable)
- Provide requirement templates with SIL classification
- Enforce SHALL/SHOULD/MAY keyword usage
- Maintain traceability matrices
- Consider C language constraints (data types, memory, real-time)

## When to use me

Use this skill when:
- Starting requirements specification phase
- Writing or reviewing software requirements
- Establishing requirements traceability
- Assigning SIL levels to requirements
- Validating requirement quality

## Requirements Quality Attributes (EN 50128 Table A.3)

Each requirement MUST be:
- **Unambiguous**: Single interpretation only
- **Testable**: Can be verified objectively
- **Clear**: Easily understood by stakeholders
- **Correct**: Accurately reflects stakeholder needs
- **Feasible**: Technically and economically possible
- **Atomic**: Cannot be decomposed further
- **Necessary**: Documents essential capability
- **Implementation-free**: Does not prescribe solution

## Requirements Template

```markdown
### REQ-[TYPE]-[ID]: [Title]

**Type**: [Functional|Performance|Interface|Safety|Security]
**SIL**: [0|1|2|3|4]
**Priority**: [Mandatory|Highly Recommended|Recommended]
**Source**: [Reference to source document]

**Description**:
The system SHALL/SHOULD/MAY [action] [condition].

**Rationale**:
[Why this requirement exists]

**Acceptance Criteria**:
1. [Testable criterion 1]
2. [Testable criterion 2]

**Dependencies**:
- REQ-[ID]: [Description]

**Verification Method**: [Test|Analysis|Inspection|Demonstration]
```

## Language Requirements

- **SHALL**: Mandatory requirement
- **SHOULD**: Highly recommended
- **MAY**: Optional
- **WILL**: Statement of fact (not requirement)

## C Language Considerations

Requirements must address:
- **Data types**: Specify fixed-width types (uint8_t, uint16_t, etc.)
- **Memory**: Static allocation requirements (SIL 2+)
- **Ranges**: Min/max values, bounds
- **Error handling**: Required error detection and handling
- **Real-time**: Timing constraints, WCET requirements
- **Safety**: Fault detection, safe states

Example:
```
REQ-FUNC-001: Speed Input Validation

The speed sensor interface SHALL validate all speed readings are within
the range [0, 300] km/h using uint16_t data type before processing.

Rationale: Prevent out-of-range values from causing system malfunction.

Acceptance: Speed values outside [0, 300] km/h are rejected with error code.
```

## Requirements Classification

### By Type
- **Functional**: What the system shall do
- **Performance**: Timing, throughput, resource usage
- **Interface**: Hardware/software interfaces, protocols
- **Safety**: Safety-critical functions, fault handling
- **Security**: Protection against threats

### By SIL Level
- **SIL 0**: Non-safety related
- **SIL 1**: Minor injury potential
- **SIL 2**: Serious injury potential (MISRA C mandatory)
- **SIL 3**: Death of individuals (independent V&V mandatory)
- **SIL 4**: Death of many people (formal methods recommended)

## Traceability

### Forward Traceability
- Requirements → Design Elements
- Requirements → Test Cases
- Requirements → Code Modules

### Backward Traceability
- Requirements ← Stakeholder Needs
- Requirements ← System Requirements
- Requirements ← Safety Requirements

## Verification Methods (EN 50128 Table A.19)

| SIL | Test | Analysis | Review | Simulation |
|-----|------|----------|--------|------------|
| 0   | HR   | HR       | HR     | R          |
| 1-2 | HR   | HR       | HR     | HR         |
| 3-4 | M    | HR       | M      | HR         |

**Legend**: M = Mandatory, HR = Highly Recommended, R = Recommended

## Requirements Review Checklist

- [ ] Unique identifier assigned
- [ ] Unambiguous wording
- [ ] Testable and measurable
- [ ] SHALL/SHOULD/MAY used correctly
- [ ] SIL level assigned
- [ ] Verification method defined
- [ ] Traceability to source documented
- [ ] Dependencies identified
- [ ] Acceptance criteria are measurable
- [ ] Implementation-independent
- [ ] C language constraints considered

## Common Patterns

### Safety Requirement Pattern
```
The system SHALL [action] when [condition] to prevent [hazard].
```

### Interface Requirement Pattern
```
The [component] SHALL provide [interface] to [other component] with [constraints].
```

### Performance Requirement Pattern
```
The system SHALL [action] within [time/resource constraint] under [conditions].
```

## References
- EN 50128:2011 Section 7.2 (Software Requirements)
- EN 50128:2011 Annex A Tables A.2, A.3, A.19
- EN 50126:2017 (RAMS Requirements)
