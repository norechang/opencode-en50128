# EN 50128 Software Compliance Overview

## Introduction

EN 50128:2011 is the European standard for "Railway applications - Communication, signalling and processing systems - Software for railway control and protection systems."

This project provides tools, templates, and guidance for developing railway software compliant with EN 50128.

## Standard References

The `/std` directory contains the following reference documents:
- **EN 50128:2011** - Software for railway control and protection systems
- **EN 50126-1:2017** - RAMS specification and demonstration (Part 1)
- **EN 50126-2:2017** - RAMS systematic failure management (Part 2)

## Safety Integrity Levels (SIL)

EN 50128 defines five SIL levels based on risk:

| SIL | Risk Level | Hazard Impact | Tolerable Hazard Rate |
|-----|------------|---------------|----------------------|
| 4 | Very High | Catastrophic - Multiple fatalities | 10^-9 to 10^-8 /hour |
| 3 | High | Critical - Single fatality | 10^-8 to 10^-7 /hour |
| 2 | Medium | Marginal - Serious injuries | 10^-7 to 10^-6 /hour |
| 1 | Low | Negligible - Minor injuries | 10^-6 to 10^-5 /hour |
| 0 | None | Non-safety related | No requirement |

## Software Development Lifecycle

### Phase 1: Software Planning (Section 6.2)
- Software Quality Assurance Plan (SQAP)
- Software Configuration Management Plan (SCMP)
- Software Verification Plan
- Software Validation Plan

### Phase 2: Software Requirements (Section 7.2)
- Requirements specification
- Requirements analysis
- Requirements validation
- Traceability establishment

### Phase 3: Software Architecture and Design (Section 7.3)
- Architecture specification
- Design specification
- Design verification
- Interface definition

### Phase 4: Component Design and Implementation (Section 7.4)
- Detailed component design
- Coding
- Code reviews
- Unit testing

### Phase 5: Software Integration (Section 7.5)
- Integration planning
- Integration testing
- Interface testing
- System integration

### Phase 6: Software Validation (Section 7.6)
- Validation testing
- System testing
- Acceptance testing

### Phase 7: Assessment and Approval (Section 8)
- Independent safety assessment
- Quality records review
- Approval for deployment

### Phase 8: Deployment and Maintenance (Section 9)
- Installation and commissioning
- Change management
- Problem resolution
- Decommissioning

## Key Technical Requirements

### Development Techniques by SIL (Table A.3, A.4)

#### Requirements Engineering
- Structured methods: HR (all SILs)
- Semi-formal methods: HR (SIL 3-4)
- Formal methods: R (SIL 3-4)

#### Design
- Modular design: M (SIL 2-4), HR (SIL 0-1)
- Structured design: M (SIL 2-4), HR (SIL 0-1)
- Defensive programming: M (SIL 3-4), HR (SIL 0-2)

#### Coding Standards
- Coding standards: M (all SILs)
- Structured programming: M (SIL 2-4), HR (SIL 0-1)
- No dynamic objects: HR (SIL 3-4)
- No dynamic variables: R (SIL 3-4)

### Verification Requirements (Table A.5)

#### Code Coverage by SIL
| Coverage Type | SIL 0-1 | SIL 2 | SIL 3-4 |
|---------------|---------|-------|---------|
| Statement | HR | HR | M |
| Branch | HR | M | M |
| Condition | R | HR | M |
| MC/DC | - | R | HR |

#### Testing Techniques
- Boundary value analysis: M (SIL 3-4), HR (SIL 0-2)
- Equivalence partitioning: HR (all SILs)
- Error guessing: R (all SILs)
- Fault injection: HR (SIL 2-4)

### Independence Requirements

#### SIL 3-4 Requirements
- Independent verification team
- Independent validation team
- Independent safety assessor
- Separation of design and test responsibilities

## Mandatory Documentation

1. **Software Quality Assurance Plan (SQAP)**
2. **Software Configuration Management Plan (SCMP)**
3. **Software Requirements Specification (SRS)**
4. **Software Architecture Specification (SAS)**
5. **Software Design Specification (SDS)**
6. **Software Test Plan**
7. **Software Test Reports**
8. **Software Validation Report**
9. **Software Assessment Report**
10. **Software Maintenance Manual**

## Tools and Techniques

### Recommended Tools by SIL
- **Version Control**: Mandatory for all SILs (Git, SVN)
- **Issue Tracking**: Mandatory for all SILs
- **Static Analysis**: HR for SIL 2+, M for SIL 3-4
- **Code Coverage**: HR for SIL 2+, M for SIL 3-4
- **Requirements Management**: HR for all SILs

### Programming Languages
- **C/C++**: Most common, with MISRA C/C++ for safety
- **Ada**: Recommended for SIL 4
- **Structured Text (IEC 61131-3)**: For PLC systems

## Compliance Workflow

### 1. Project Initiation
```bash
# Set up project with appropriate SIL level
/check status --sil 3
```

### 2. Requirements Phase
```bash
# Extract requirements
/req extract --source spec.doc

# Validate requirements
/req validate --sil 3

# Generate traceability
/req trace --output requirements-trace.md
```

### 3. Design Phase
```bash
# Generate architecture template
/design template --sil 3

# Validate design
/design validate --requirements requirements-trace.md

# Perform design review
/design review --checklist
```

### 4. Implementation Phase
```bash
# Check coding standards
/quality standards --language c --standard misra

# Perform static analysis
/verify static --sil 3
```

### 5. Testing Phase
```bash
# Generate test plan
/verify testplan --sil 3

# Run tests with coverage
/verify coverage --target 100

# Verify traceability
/verify trace
```

### 6. Safety Analysis
```bash
# Perform hazard analysis
/safety hazard --system braking

# Generate FMEA
/safety fmea --component brake-controller

# Create safety case
/safety case --sil 3
```

### 7. Documentation
```bash
# List mandatory documents
/docs list --sil 3

# Generate missing documents
/docs generate --template SRS

# Review documentation
/docs review --phase requirements
```

### 8. Compliance Check
```bash
# Overall compliance status
/check status

# Identify gaps
/check gaps

# Generate compliance report
/check report --output compliance-report.pdf
```

## Common Compliance Challenges

### 1. Traceability
- **Challenge**: Maintaining bidirectional traceability
- **Solution**: Use requirements management tools and traceability matrices

### 2. Independence
- **Challenge**: Ensuring independence for SIL 3-4
- **Solution**: Separate teams, independent assessment

### 3. Code Coverage
- **Challenge**: Achieving 100% coverage for SIL 4
- **Solution**: Comprehensive test design, dead code elimination

### 4. Documentation
- **Challenge**: Maintaining up-to-date documentation
- **Solution**: Document-driven development, version control

### 5. Tool Qualification
- **Challenge**: Qualifying development tools
- **Solution**: Tool validation per EN 50128 Annex C

## Best Practices

### 1. Start with Planning
- Define SIL levels early
- Create comprehensive plans (SQAP, SCMP, etc.)
- Establish traceability from the beginning

### 2. Apply Defensive Programming
- Validate all inputs
- Check all outputs
- Handle all error conditions
- Use assertions for safety-critical code

### 3. Implement Strong Configuration Management
- Version control for all artifacts
- Baseline management
- Change control process
- Audit trail

### 4. Perform Regular Reviews
- Peer reviews for all code
- Design reviews at architecture and detailed levels
- Documentation reviews
- Independent safety reviews

### 5. Maintain Evidence
- Keep all verification records
- Document all design decisions
- Track all defects and resolutions
- Preserve audit trail

## Assessment and Certification

### Independent Safety Assessment (ISA)
Required for SIL 1-4:
- Review of development process
- Review of technical documentation
- Review of verification evidence
- Assessment report with approval/conditions

### Certification Bodies
- National railway authorities
- Notified bodies (e.g., TÜV, Lloyd's Register)
- Independent safety assessors

## Maintenance and Change Management

### Change Process
1. Change request submitted
2. Impact analysis performed
3. Safety impact assessed
4. Change approved by CCB
5. Implementation with verification
6. Regression testing
7. Documentation updated
8. Change deployed

### Version Management
- Major version: Significant changes requiring re-certification
- Minor version: Bug fixes and minor enhancements
- Patch version: Critical safety patches

## Abbreviations

- **CCB**: Change Control Board
- **CM**: Configuration Management
- **FCA**: Functional Configuration Audit
- **FMEA**: Failure Mode and Effects Analysis
- **FTA**: Fault Tree Analysis
- **ISA**: Independent Safety Assessor
- **MC/DC**: Modified Condition/Decision Coverage
- **PCA**: Physical Configuration Audit
- **QA**: Quality Assurance
- **RAMS**: Reliability, Availability, Maintainability, Safety
- **SCMP**: Software Configuration Management Plan
- **SIL**: Safety Integrity Level
- **SQAP**: Software Quality Assurance Plan
- **SRS**: Software Requirements Specification
- **V&V**: Verification and Validation

## References

- EN 50128:2011 - Railway applications - Software for railway control and protection systems
- EN 50126-1:2017 - Railway applications - RAMS (Part 1)
- EN 50126-2:2017 - Railway applications - RAMS (Part 2)
- EN 50129:2018 - Safety related electronic systems for signalling
- IEC 61508 - Functional safety of electrical/electronic/programmable electronic safety-related systems
- CENELEC standards for railway applications
