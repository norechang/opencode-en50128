# EN 50128 Project Structure

## Directory Organization

```
EN50128/
├── README.md                          # Project overview
├── AGENTS.md                          # Agent definitions and workflows
├── std/                               # Reference standards
│   ├── EN50128-2011.pdf              # Main standard
│   ├── EN 50126-1-2017.pdf           # RAMS Part 1
│   └── EN 50126-2-2017.pdf           # RAMS Part 2
├── docs/                              # Project documentation
│   ├── EN50128-Compliance-Guide.md   # Compliance overview
│   ├── plans/                         # Planning documents
│   │   ├── SQAP.md                   # Software Quality Assurance Plan
│   │   ├── SCMP.md                   # Configuration Management Plan
│   │   ├── SVP.md                    # Verification Plan
│   │   └── SVaP.md                   # Validation Plan
│   ├── requirements/                  # Requirements documentation
│   │   ├── SRS.md                    # Software Requirements Spec
│   │   └── requirements-trace.md     # Traceability matrix
│   ├── design/                        # Design documentation
│   │   ├── SAS.md                    # Software Architecture Spec
│   │   └── SDS.md                    # Software Design Spec
│   ├── test/                          # Test documentation
│   │   ├── test-plan.md              # Master test plan
│   │   ├── unit-tests/               # Unit test specs
│   │   ├── integration-tests/        # Integration test specs
│   │   └── validation-tests/         # Validation test specs
│   ├── safety/                        # Safety documentation
│   │   ├── hazard-log.md             # Hazard analysis
│   │   ├── fmea.md                   # FMEA analysis
│   │   ├── fta.md                    # Fault tree analysis
│   │   └── safety-case.md            # Safety case
│   └── reports/                       # Reports and assessments
│       ├── verification/             # Verification reports
│       ├── validation/               # Validation reports
│       └── compliance/               # Compliance reports
├── skills/                            # EN 50128 skills definitions
│   ├── en50128-requirements.skill    # Requirements engineering
│   ├── en50128-design.skill          # Design patterns
│   ├── en50128-testing.skill         # Testing methodologies
│   ├── en50128-safety.skill          # Safety analysis
│   └── en50128-documentation.skill   # Documentation templates
├── templates/                         # Document templates
│   ├── requirement-template.md
│   ├── design-template.md
│   ├── test-case-template.md
│   └── review-checklist.md
├── tools/                             # Tool configurations
│   ├── static-analysis/              # Static analysis configs
│   ├── coverage/                     # Coverage tool configs
│   └── build/                        # Build configurations
└── src/                               # Source code (to be added)
    ├── components/                    # Software components
    ├── interfaces/                    # Interface definitions
    ├── tests/                         # Test code
    └── config/                        # Configuration files
```

## File Naming Conventions

### Documents
- Use descriptive names with hyphens
- Include version number when appropriate
- Format: `<type>-<name>-v<version>.md`
- Examples:
  - `SRS-Braking-System-v1.0.md`
  - `test-plan-integration-v2.1.md`

### Requirements
- Format: `REQ-<TYPE>-<ID>`
- Types: FUNC, PERF, IF, SAFE, SEC, QUAL
- Examples:
  - `REQ-FUNC-001`: Functional requirement
  - `REQ-SAFE-042`: Safety requirement

### Design Elements
- Format: `DES-<TYPE>-<ID>`
- Types: ARCH, MOD, IF
- Examples:
  - `DES-ARCH-001`: Architecture element
  - `DES-MOD-025`: Module design

### Test Cases
- Format: `TC-<LEVEL>-<ID>`
- Levels: UNIT, INT, SYS, VAL
- Examples:
  - `TC-UNIT-001`: Unit test
  - `TC-SYS-123`: System test

### Source Code
- Follow language-specific conventions
- For C/C++: Use MISRA naming conventions
- Format: `<module>_<function>.c/.h`

## Version Control Structure

### Branch Strategy
```
main/                      # Production-ready baseline
├── develop/              # Integration branch
├── feature/<name>/       # Feature development
├── bugfix/<id>/          # Bug fixes
└── release/<version>/    # Release preparation
```

### Tag Strategy
```
v<major>.<minor>.<patch>-SIL<level>
Examples:
  v1.0.0-SIL3
  v2.1.5-SIL4
```

## Configuration Items (CIs)

### Software CIs
1. Source code files
2. Configuration files
3. Build scripts
4. Test scripts
5. Documentation

### Hardware CIs (if applicable)
1. Hardware specifications
2. Interface definitions
3. Deployment configurations

## Document Control

### Status Levels
- **Draft**: Work in progress
- **Review**: Under review
- **Approved**: Approved by stakeholders
- **Baseline**: Configuration controlled version

### Approval Workflow
1. Author creates/updates document
2. Peer review
3. QA review
4. Safety review (for safety docs)
5. Management approval
6. Baseline and archive

## Traceability Links

### Forward Traceability
```
Requirements → Design Elements → Code Modules → Test Cases
```

### Backward Traceability
```
Test Results ← Test Cases ← Code ← Design ← Requirements ← Stakeholder Needs
```

## Tool Integration

### Required Tools
1. **Version Control**: Git
2. **Issue Tracking**: GitHub Issues / Jira
3. **Build System**: Make / CMake
4. **Static Analysis**: Coverity / PC-lint
5. **Code Coverage**: gcov / lcov
6. **Documentation**: Markdown / LaTeX

### Tool Qualification
For SIL 3-4, tools must be qualified per EN 50128 Annex C:
- Tool classification (T1, T2, T3)
- Validation evidence
- Configuration management

## Baseline Management

### Baseline Types
1. **Requirements Baseline**: Approved SRS
2. **Design Baseline**: Approved architecture and design
3. **Implementation Baseline**: Code review and unit test complete
4. **Release Baseline**: Fully verified and validated software

### Baseline Procedure
1. Freeze all changes
2. Perform configuration audit
3. Generate baseline package
4. Archive with tag
5. Update configuration status

## Change Management

### Change Request Process
1. Submit change request (CR)
2. Impact analysis
   - Technical impact
   - Safety impact
   - Schedule impact
   - Cost impact
3. Review by CCB (Change Control Board)
4. Approval/rejection decision
5. Implementation (if approved)
6. Verification of change
7. Update documentation
8. Close CR

### Emergency Changes
- Fast-track process for critical safety issues
- Retrospective CCB review
- Full documentation required

## Access Control

### Document Access
- Public documents: General access
- Internal documents: Project team only
- Confidential documents: Authorized personnel only
- Safety documents: Safety team + assessors

### Repository Access
- Read access: All project members
- Write access: Developers with approval
- Merge access: Lead developers + QA
- Admin access: Configuration manager

## Archiving and Retention

### Retention Periods
- Development artifacts: Duration of operation + 10 years
- Safety evidence: Duration of operation + 15 years
- Quality records: Duration of operation + 10 years
- Baseline releases: Permanent

### Archive Format
- Digital archives: PDF/A for long-term preservation
- Backup frequency: Daily incremental, weekly full
- Off-site backup: Required for critical artifacts

## Project Phases and Deliverables

### Phase 1: Planning
**Deliverables:**
- SQAP (Software Quality Assurance Plan)
- SCMP (Software Configuration Management Plan)
- SVP (Software Verification Plan)
- SVaP (Software Validation Plan)

### Phase 2: Requirements
**Deliverables:**
- SRS (Software Requirements Specification)
- Requirements traceability matrix
- Requirements verification report

### Phase 3: Design
**Deliverables:**
- SAS (Software Architecture Specification)
- SDS (Software Design Specification)
- Interface specifications
- Design verification report

### Phase 4: Implementation
**Deliverables:**
- Source code
- Unit test specifications
- Unit test reports
- Code review records

### Phase 5: Integration & Testing
**Deliverables:**
- Integration test specifications
- Integration test reports
- System test specifications
- System test reports
- Coverage reports

### Phase 6: Validation
**Deliverables:**
- Validation test specifications
- Validation test reports
- Validation summary report

### Phase 7: Assessment
**Deliverables:**
- Software assessment report
- Safety case
- Compliance evidence package

### Phase 8: Deployment
**Deliverables:**
- Deployment documentation
- Installation procedures
- Maintenance manual
- User documentation

## Quality Gates

### Requirements Gate
- [ ] All requirements documented
- [ ] Requirements reviewed and approved
- [ ] Traceability established
- [ ] SIL levels assigned

### Design Gate
- [ ] Architecture complete
- [ ] Design reviewed
- [ ] Traceable to requirements
- [ ] Safety analysis complete

### Implementation Gate
- [ ] Code complete
- [ ] Code reviews done
- [ ] Unit tests pass
- [ ] Static analysis clean

### Integration Gate
- [ ] Integration complete
- [ ] Integration tests pass
- [ ] Interface testing complete
- [ ] Coverage targets met

### Release Gate
- [ ] All tests passed
- [ ] Documentation complete
- [ ] Safety assessment approved
- [ ] Quality records complete

## References
- EN 50128:2011 Section 5 - Software Configuration Management
- EN 50128:2011 Annex B - Documentation
- ISO/IEC 12207 - Software Life Cycle Processes
