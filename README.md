# EN 50128 Railway Software Development Project

A comprehensive framework for developing railway software compliant with **EN 50128:2011** standard.

## Overview

This project provides:
- **Specialized agents** for EN 50128 compliance tasks
- **Skills** with patterns, templates, and best practices
- **Documentation templates** for all mandatory deliverables
- **Reference standards** (EN 50128, EN 50126)
- **Workflows** for requirements, design, testing, and safety analysis

## Quick Start

### 1. Understand Your SIL Level

Determine the Safety Integrity Level (SIL) for your project:

| SIL | Risk Level | Example Applications |
|-----|------------|---------------------|
| 4 | Very High | Train control systems, automatic train protection |
| 3 | High | Signaling systems, interlocking |
| 2 | Medium | Passenger information systems with safety impact |
| 1 | Low | Non-critical monitoring systems |
| 0 | None | Administrative systems |

### 2. Available Agents

Use specialized agents via slash commands:

- `/req` - Requirements management and validation
- `/design` - Software architecture and design support
- `/verify` - Verification and testing activities
- `/quality` - Quality assurance and audits
- `/config` - Configuration management
- `/safety` - Safety analysis and hazard management
- `/docs` - Documentation generation and management
- `/check` - Compliance verification

See [AGENTS.md](AGENTS.md) for detailed agent documentation.

### 3. Example Workflow

#### Complete Requirements-to-Testing Flow

```bash
# 1. Extract and validate requirements
/req extract --source requirements.doc
/req validate --sil 3

# 2. Generate traceability matrix
/req trace --output docs/requirements/requirements-trace.md

# 3. Create design from requirements
/design template --sil 3
/design validate --requirements docs/requirements/requirements-trace.md

# 4. Generate test plan
/verify testplan --requirements docs/requirements/requirements-trace.md --sil 3

# 5. Check overall compliance
/check status --phase design
```

## Project Structure

```
EN50128/
├── AGENTS.md                      # Agent definitions and workflows
├── README.md                      # This file
├── std/                           # Reference standards
│   ├── EN50128-2011.pdf
│   ├── EN 50126-1-2017.pdf
│   └── EN 50126-2-2017.pdf
├── docs/                          # Documentation
│   ├── EN50128-Compliance-Guide.md
│   ├── Project-Structure.md
│   ├── plans/                     # SQAP, SCMP, SVP, SVaP
│   ├── requirements/              # SRS, traceability
│   ├── design/                    # SAS, SDS
│   ├── test/                      # Test plans and reports
│   ├── safety/                    # Hazard analysis, FMEA, FTA
│   └── reports/                   # Verification, validation, compliance
├── skills/                        # EN 50128 compliance skills
│   ├── en50128-requirements.skill
│   ├── en50128-design.skill
│   ├── en50128-testing.skill
│   ├── en50128-safety.skill
│   └── en50128-documentation.skill
├── templates/                     # Document templates
├── tools/                         # Tool configurations
└── src/                           # Source code
```

See [docs/Project-Structure.md](docs/Project-Structure.md) for detailed structure information.

## Key Features

### 1. Requirements Engineering

- Requirements extraction and validation
- Traceability matrix generation
- SIL-level assignment
- Requirements quality checking

**Skills:** [skills/en50128-requirements.skill](skills/en50128-requirements.skill)

### 2. Software Design

- Architecture and design templates
- Design patterns for safety-critical systems
- Defensive programming guidelines
- Modularity and complexity management

**Skills:** [skills/en50128-design.skill](skills/en50128-design.skill)

### 3. Verification and Testing

- Test planning and execution
- Code coverage analysis (statement, branch, MC/DC)
- Static analysis integration
- Test traceability

**Skills:** [skills/en50128-testing.skill](skills/en50128-testing.skill)

### 4. Safety Analysis

- Hazard identification and analysis
- FMEA (Failure Mode and Effects Analysis)
- FTA (Fault Tree Analysis)
- Safety case development
- SIL determination

**Skills:** [skills/en50128-safety.skill](skills/en50128-safety.skill)

### 5. Documentation Management

- All mandatory EN 50128 documents
- Document templates
- Version control and baselines
- Review checklists

**Skills:** [skills/en50128-documentation.skill](skills/en50128-documentation.skill)

## Mandatory Documentation

EN 50128 requires the following key documents:

### Planning Phase
- [ ] Software Quality Assurance Plan (SQAP)
- [ ] Software Configuration Management Plan (SCMP)
- [ ] Software Verification Plan (SVP)
- [ ] Software Validation Plan (SVaP)

### Requirements Phase
- [ ] Software Requirements Specification (SRS)
- [ ] Requirements Verification Report

### Design Phase
- [ ] Software Architecture Specification (SAS)
- [ ] Software Design Specification (SDS)
- [ ] Design Verification Report

### Implementation Phase
- [ ] Source Code
- [ ] Code Review Records
- [ ] Unit Test Reports

### Testing Phase
- [ ] Test Specifications
- [ ] Test Reports
- [ ] Coverage Reports

### Validation Phase
- [ ] Validation Test Report
- [ ] Software Assessment Report

### Deployment
- [ ] Software Deployment Document
- [ ] Software Maintenance Manual

## Compliance Requirements by SIL

### Code Coverage (Table A.5)

| Coverage Type | SIL 0-1 | SIL 2 | SIL 3-4 |
|---------------|---------|-------|---------|
| Statement Coverage | HR | HR | **M** |
| Branch Coverage | HR | **M** | **M** |
| Condition Coverage | R | HR | **M** |
| MC/DC Coverage | - | R | HR |

**M** = Mandatory, **HR** = Highly Recommended, **R** = Recommended

### Testing Techniques (Table A.5)

| Technique | SIL 0-1 | SIL 2 | SIL 3-4 |
|-----------|---------|-------|---------|
| Boundary Value Analysis | HR | HR | **M** |
| Equivalence Partitioning | HR | HR | HR |
| Fault Injection | R | HR | HR |
| Error Guessing | R | R | R |

### Independence Requirements

**SIL 3-4 requires:**
- Independent verification team (separate from development)
- Independent validation team
- Independent safety assessor
- Tool qualification for development tools

## Getting Started with Development

### 1. Create Project Plans

```bash
# Generate SQAP template
/docs generate --template SQAP --sil 3

# Generate SCMP template
/docs generate --template SCMP --sil 3

# Generate verification plan
/docs generate --template SVP --sil 3
```

### 2. Define Requirements

```bash
# Create requirements specification
/req template --output docs/requirements/SRS.md --sil 3

# Validate requirements quality
/req validate --input docs/requirements/SRS.md
```

### 3. Develop Architecture

```bash
# Generate architecture template
/design template --type architecture --sil 3

# Perform design review
/design review --checklist
```

### 4. Implement with Quality Checks

```bash
# Check coding standards (MISRA C)
/quality standards --language c --standard misra

# Perform static analysis
/verify static --input src/
```

### 5. Execute Testing

```bash
# Generate test plan
/verify testplan --sil 3

# Run tests with coverage
/verify coverage --target 100 --sil 3
```

### 6. Safety Analysis

```bash
# Perform hazard analysis
/safety hazard --system <system-name>

# Generate FMEA
/safety fmea --component <component-name>

# Create safety case
/safety case --sil 3
```

### 7. Generate Compliance Report

```bash
# Check overall compliance
/check status

# Identify gaps
/check gaps --sil 3

# Generate report for assessor
/check report --output docs/reports/compliance/compliance-report.md
```

## Tools Integration

### Recommended Tools by SIL

#### All SILs
- **Version Control**: Git
- **Issue Tracking**: GitHub Issues, Jira
- **Build System**: Make, CMake
- **Documentation**: Markdown, LaTeX

#### SIL 2+
- **Static Analysis**: Coverity, PC-lint, Cppcheck
- **Code Coverage**: gcov, lcov, Bullseye
- **Requirements Management**: DOORS, Jama

#### SIL 3-4
- **Formal Methods**: SCADE, B-Method
- **Model Checking**: SPIN, NuSMV
- **Tool Qualification**: Per EN 50128 Annex C

## Best Practices

### 1. Traceability First
Establish bidirectional traceability from day one:
- Requirements ↔ Design
- Design ↔ Code
- Requirements ↔ Tests

### 2. Defensive Programming
For safety-critical code:
- Validate all inputs
- Check all outputs
- Handle all error conditions
- Use assertions liberally

### 3. Configuration Management
- Version control everything
- Establish baselines early
- Implement change control
- Maintain audit trail

### 4. Independent Review
For SIL 3-4:
- Separate development and testing teams
- Independent safety assessment
- Peer review all code and documents

### 5. Comprehensive Testing
- Achieve required coverage targets
- Test boundary conditions
- Perform fault injection
- Execute regression tests

## Common Pitfalls to Avoid

1. **Late traceability**: Establish from the beginning
2. **Insufficient independence**: Separate teams for SIL 3-4
3. **Poor documentation**: Keep docs updated throughout
4. **Tool over-reliance**: Qualify tools per Annex C
5. **Inadequate testing**: Meet coverage requirements
6. **Weak change control**: Implement rigorous CM process

## Certification Process

### 1. Preparation Phase
- Complete all mandatory documentation
- Gather all evidence
- Prepare traceability matrices
- Package deliverables

### 2. Assessment Phase
- Independent Safety Assessor (ISA) review
- Document review
- Process audit
- Technical review

### 3. Approval Phase
- Address findings
- Obtain approval
- Baseline release
- Archive evidence

## Support and Resources

### Reference Standards
Located in `/std` directory:
- EN 50128:2011 - Software for railway control systems
- EN 50126-1:2017 - RAMS specification
- EN 50126-2:2017 - RAMS systematic failure management

### Guidance Documents
- [EN50128 Compliance Guide](docs/EN50128-Compliance-Guide.md)
- [Project Structure](docs/Project-Structure.md)
- [AGENTS.md](AGENTS.md) - Agent usage guide

### Skills Library
Located in `/skills` directory with detailed patterns and examples.

## Contributing

When adding new templates or skills:
1. Follow the established naming conventions
2. Include SIL-level guidance
3. Provide examples
4. Reference standard sections
5. Update this README

## License

This framework is provided for railway software development compliant with EN 50128:2011.

## Version History

| Version | Date | Changes |
|---------|------|---------|
| 1.0 | 2026-02-06 | Initial project setup with agents, skills, and documentation |

---

**Note**: This project provides guidance and tools for EN 50128 compliance. Actual certification requires independent safety assessment by qualified assessors and approval by relevant railway authorities.
