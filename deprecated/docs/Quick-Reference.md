# EN 50128 Quick Reference Guide

## Agent Commands Quick Reference

### Requirements Agent (`/req`)
```bash
# Extract requirements from documents
/req extract --source <document>

# Validate requirements against EN 50128
/req validate --sil <0-4>

# Generate traceability matrix
/req trace --output <file>

# Generate requirements template
/req template --sil <0-4>
```

### Design Agent (`/design`)
```bash
# Generate design template
/design template --sil <0-4>

# Perform design review
/design review --checklist

# Validate design against requirements
/design validate --requirements <file>

# Generate design diagrams
/design diagram --type <uml-type>
```

### Verification Agent (`/verify`)
```bash
# Generate test plan
/verify testplan --sil <0-4>

# Analyze code coverage
/verify coverage --target <percentage>

# Perform static analysis
/verify static --input <directory>

# Generate test traceability
/verify trace
```

### Quality Agent (`/quality`)
```bash
# Perform quality audit
/quality audit

# Generate quality metrics
/quality metrics

# Check coding standards
/quality standards --language <c|cpp|ada> --standard <misra|autosar>

# Generate QA plan
/quality plan --sil <0-4>
```

### Configuration Management Agent (`/config`)
```bash
# Generate CM plan
/config plan

# Create baseline
/config baseline --version <version>

# Track configuration items
/config track

# Support release process
/config release --version <version>
```

### Safety Agent (`/safety`)
```bash
# Perform hazard analysis
/safety hazard --system <name>

# Generate FMEA template
/safety fmea --component <name>

# Generate FTA template
/safety fta --event <top-event>

# Determine SIL level
/safety sil --hazard <id>

# Generate safety case
/safety case --sil <0-4>
```

### Documentation Agent (`/docs`)
```bash
# Generate document from template
/docs generate --template <SRS|SAS|SDS|SQAP|SCMP>

# List all mandatory documents
/docs list --sil <0-4>

# Perform document review
/docs review --document <file>

# Create deliverable package
/docs package --version <version>
```

### Compliance Checker Agent (`/check`)
```bash
# Check overall compliance status
/check status --sil <0-4>

# Identify compliance gaps
/check gaps --phase <phase>

# Generate compliance report
/check report --output <file>

# Support certification preparation
/check cert --sil <0-4>
```

---

## SIL Level Requirements Summary

### SIL 0 - Non-Safety
- Basic software engineering practices
- Standard testing
- Basic documentation

### SIL 1 - Low Risk
- Structured development
- Code reviews recommended
- Testing: Statement coverage (HR)
- Independent testing recommended

### SIL 2 - Medium Risk
- Structured methods mandatory
- Code reviews mandatory
- Testing: Statement + Branch coverage (M)
- Static analysis highly recommended
- Independent testing highly recommended

### SIL 3 - High Risk
- Semi-formal methods recommended
- Defensive programming mandatory
- Testing: Statement + Branch + Condition coverage (M)
- MC/DC coverage recommended
- Independent verification team **mandatory**
- Independent validation team **mandatory**
- Static analysis mandatory

### SIL 4 - Very High Risk
- Formal methods recommended
- Diverse design highly recommended
- Testing: All coverage types (M)
- MC/DC coverage highly recommended
- Independent verification team **mandatory**
- Independent validation team **mandatory**
- Independent safety assessor **mandatory**
- Tool qualification mandatory
- Static analysis mandatory

**Legend:**
- **M** = Mandatory
- **HR** = Highly Recommended
- **R** = Recommended

---

## Mandatory Documents by Phase

### Planning
- [ ] SQAP - Software Quality Assurance Plan
- [ ] SCMP - Software Configuration Management Plan
- [ ] SVP - Software Verification Plan
- [ ] SVaP - Software Validation Plan

### Requirements
- [ ] SRS - Software Requirements Specification
- [ ] Requirements Traceability Matrix
- [ ] Requirements Verification Report

### Design
- [ ] SAS - Software Architecture Specification
- [ ] SDS - Software Design Specification
- [ ] Interface Specifications
- [ ] Design Verification Report

### Implementation
- [ ] Source Code
- [ ] Unit Test Specifications
- [ ] Unit Test Reports
- [ ] Code Review Records

### Integration & Testing
- [ ] Integration Test Specification
- [ ] Integration Test Report
- [ ] System Test Specification
- [ ] System Test Report
- [ ] Coverage Analysis Report

### Validation
- [ ] Validation Test Specification
- [ ] Validation Test Report
- [ ] Validation Summary Report

### Assessment
- [ ] Software Assessment Report
- [ ] Safety Case (for safety functions)
- [ ] Compliance Evidence Package

---

## Common Workflows

### New Project Setup
```bash
# 1. Check initial compliance requirements
/check status --sil 3

# 2. Generate planning documents
/docs generate --template SQAP --sil 3
/docs generate --template SCMP --sil 3
/quality plan --sil 3

# 3. Set up configuration management
/config plan
```

### Requirements Phase
```bash
# 1. Create requirements template
/req template --sil 3

# 2. Extract requirements (if from existing docs)
/req extract --source requirements.doc

# 3. Validate requirements
/req validate --sil 3

# 4. Generate traceability matrix
/req trace --output docs/requirements/trace.md
```

### Design Phase
```bash
# 1. Generate architecture template
/design template --type architecture --sil 3

# 2. Validate against requirements
/design validate --requirements docs/requirements/trace.md

# 3. Perform design review
/design review --checklist

# 4. Generate diagrams
/design diagram --type component
```

### Implementation Phase
```bash
# 1. Check coding standards
/quality standards --language c --standard misra

# 2. Perform static analysis
/verify static --input src/

# 3. Run unit tests with coverage
/verify coverage --target 100 --level unit
```

### Testing Phase
```bash
# 1. Generate test plan
/verify testplan --sil 3

# 2. Check test coverage
/verify coverage --target 100

# 3. Verify test traceability
/verify trace

# 4. Generate test report
/docs generate --template test-report
```

### Safety Analysis
```bash
# 1. Perform hazard analysis
/safety hazard --system braking-system

# 2. Generate FMEA
/safety fmea --component brake-controller

# 3. Perform FTA
/safety fta --event "train-collision"

# 4. Create safety case
/safety case --sil 3
```

### Pre-Certification
```bash
# 1. Check overall status
/check status

# 2. Identify gaps
/check gaps --sil 3

# 3. Generate compliance report
/check report --output compliance-report.md

# 4. Create deliverable package
/docs package --version 1.0
```

---

## Code Coverage Targets

### By SIL Level

| SIL | Statement | Branch | Condition | MC/DC |
|-----|-----------|--------|-----------|-------|
| 0 | - | - | - | - |
| 1 | 80%+ (HR) | 70%+ (HR) | - | - |
| 2 | 100% (HR) | 100% (M) | 80%+ (HR) | - |
| 3 | 100% (M) | 100% (M) | 100% (M) | 80%+ (HR) |
| 4 | 100% (M) | 100% (M) | 100% (M) | 100% (HR) |

---

## Testing Techniques by SIL

### SIL 0-1
- Equivalence partitioning (HR)
- Boundary value analysis (HR)
- Error guessing (R)

### SIL 2
- Equivalence partitioning (HR)
- Boundary value analysis (HR)
- Control flow testing (HR)
- Data flow testing (HR)

### SIL 3-4
- Equivalence partitioning (M)
- Boundary value analysis (M)
- Control flow testing (M)
- Data flow testing (M)
- Fault injection (HR)
- Robustness testing (M for SIL 4)

---

## Tool Qualification (Annex C)

### Tool Classes

**T1**: No influence on executable code
- Documentation tools
- Version control (monitoring only)
- No qualification required

**T2**: Verification and validation tools
- Test tools
- Static analyzers
- Coverage tools
- **Validation required**: Tool itself must be validated

**T3**: Code generation and translation tools
- Compilers
- Code generators
- Linkers
- **High confidence required**: Tool qualification or increased verification

### Qualification Methods
1. **Increased confidence from use**: Proven in use
2. **Evaluation of development process**: Assess tool development
3. **Validation of software tool**: Test the tool itself
4. **Development in accordance with EN 50128**: Tool developed to same standard

---

## Independence Requirements

### SIL 1-2
- Independent testing: **Highly Recommended**
- Independent V&V: Recommended

### SIL 3
- Independent verification team: **Mandatory**
- Independent validation team: **Mandatory**
- Independent safety assessor: **Mandatory**

### SIL 4
- Independent verification team: **Mandatory** (different organization)
- Independent validation team: **Mandatory** (different organization)
- Independent safety assessor: **Mandatory** (different organization)
- Tool qualification: **Mandatory**

---

## Complexity Limits

### Cyclomatic Complexity
- **SIL 0-1**: < 20 per function
- **SIL 2**: < 15 per function
- **SIL 3-4**: < 10 per function

### Code Size
- **Max lines per function**: 100-200
- **Max functions per module**: 20-30
- **Max nesting depth**: 4-5 levels

---

## Review Checklist Quick Links

Located in skills files:

1. **Requirements Review**: [skills/en50128-requirements.skill](skills/en50128-requirements.skill)
2. **Design Review**: [skills/en50128-design.skill](skills/en50128-design.skill)
3. **Code Review**: [skills/en50128-design.skill](skills/en50128-design.skill)
4. **Test Review**: [skills/en50128-testing.skill](skills/en50128-testing.skill)
5. **Safety Review**: [skills/en50128-safety.skill](skills/en50128-safety.skill)
6. **Document Review**: [skills/en50128-documentation.skill](skills/en50128-documentation.skill)

---

## Common EN 50128 Terms

- **CCB**: Change Control Board
- **CI**: Configuration Item
- **FCA**: Functional Configuration Audit
- **FMEA**: Failure Mode and Effects Analysis
- **FTA**: Fault Tree Analysis
- **ISA**: Independent Safety Assessor
- **MC/DC**: Modified Condition/Decision Coverage
- **PCA**: Physical Configuration Audit
- **RAMS**: Reliability, Availability, Maintainability, Safety
- **SIL**: Safety Integrity Level
- **SQAP**: Software Quality Assurance Plan
- **SRS**: Software Requirements Specification
- **V&V**: Verification and Validation

---

## Emergency Contacts and Escalation

### Compliance Issues
1. Review relevant skill file
2. Consult AGENTS.md for workflow
3. Use `/check gaps` to identify specific issues
4. Escalate to QA Manager or Safety Manager

### Safety Issues
1. Document in hazard log immediately
2. Use `/safety hazard` to analyze
3. Notify Safety Manager
4. Perform immediate risk assessment
5. Implement mitigation if required

### Tool Issues
1. Check tool qualification status
2. Review tool validation records
3. Consider alternative tools
4. Escalate to Configuration Manager

---

For detailed information, see:
- [README.md](README.md) - Full project overview
- [AGENTS.md](AGENTS.md) - Detailed agent documentation
- [docs/EN50128-Compliance-Guide.md](docs/EN50128-Compliance-Guide.md) - Complete compliance guide
- [docs/Project-Structure.md](docs/Project-Structure.md) - Project organization
