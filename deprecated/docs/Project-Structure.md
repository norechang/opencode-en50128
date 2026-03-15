# EN 50128 Platform Structure

## Overview

This document describes the structure of the **EN 50128 Development Platform** - an OpenCode customization for railway software development.

**Important**: This is a **platform**, not a project. Actual development projects are created in the `examples/` directory.

## Directory Organization

```
EN50128/                                   # EN 50128 Development Platform Root
├── README.md                              # Platform overview and quick start
├── AGENTS.md                              # Agent definitions and workflows  
├── LIFECYCLE.md                           # Complete EN 50128 V-Model lifecycle
├── CHANGELOG.md                           # Version history
├── CONTRIBUTING.md                        # Contribution guidelines
├── GITHUB_SETUP.md                        # GitHub repository setup
├── LICENSE                                # License information
├── .gitignore                             # Git ignore rules
│
├── .opencode/                             # OpenCode Customization
│   ├── commands/                          # 12 EN 50128 agent command definitions
│   │   ├── cod.md                        # Lifecycle Coordinator (Section 5.3)
│   │   ├── req.md                        # Requirements Engineer (Table A.2)
│   │   ├── des.md                        # Designer (Table A.3)
│   │   ├── imp.md                        # Implementer (Table A.4)
│   │   ├── tst.md                        # Tester (Table A.5, A.21)
│   │   ├── int.md                        # Integrator (Table A.6)
│   │   ├── ver.md                        # Verifier (Table A.5, A.19)
│   │   ├── val.md                        # Validator (Table A.7)
│   │   ├── saf.md                        # Safety Engineer (Table A.8)
│   │   ├── qua.md                        # Quality Assurance (Table A.9)
│   │   ├── pm.md                         # Project Manager (Section 5)
│   │   └── cm.md                         # Configuration Manager (Section 6.6)
│   └── skills/                            # 13 Domain-Specific EN 50128 Skills
│       ├── en50128-lifecycle-coordination/ # Lifecycle orchestration patterns
│       ├── en50128-requirements/         # Requirements engineering patterns
│       ├── en50128-design/               # Architecture & design patterns
│       ├── en50128-implementation/       # C implementation with MISRA C
│       ├── en50128-testing/              # Testing methodologies & coverage
│       ├── en50128-integration/          # Integration techniques
│       ├── en50128-verification/         # Verification & static analysis
│       ├── en50128-validation/           # Validation & system testing
│       ├── en50128-safety/               # Safety analysis (FMEA, FTA, CCA)
│       ├── en50128-quality/              # Quality assurance processes
│       ├── en50128-documentation/        # Documentation templates
│       ├── en50128-project-management/   # Project management workflows
│       └── en50128-configuration/        # Configuration management
│
├── std/                                   # EN 50128 Standards (LLM-Friendly)
│   ├── EN50128-2011.md                   # Main railway standard (2.2 MB Markdown)
│   ├── EN 50126-1-2017.md                # RAMS Part 1 (293 KB)
│   ├── EN 50126-2-2017.md                # RAMS Part 2 (210 KB)
│   ├── EN50128-ABBREVIATIONS.md          # Official abbreviations
│   └── EN50128-TABLES-EXTRACTED.md       # All technique tables (A.2-A.23)
│
├── docs/                                  # Platform Documentation
│   ├── QUICKSTART.md                     # Getting started guide
│   ├── SETUP.md                          # Setup instructions
│   ├── Quick-Reference.md                # Quick reference
│   ├── Project-Structure.md              # This file
│   ├── EN50128-Compliance-Guide.md       # Compliance overview
│   ├── EN50128-Roles.md                  # Role descriptions
│   ├── Agent-Skill-*.md                  # Agent-skill mapping (3 files)
│   └── project-revision/                 # Project revision history (archived)
│       ├── PROJECT_REVISION_STATUS.md   # Overall revision status
│       ├── NEXT_STEPS.md                # Future enhancements
│       ├── CLEANUP_ANALYSIS.md          # Cleanup analysis
│       ├── PHASE_2A_COMPLETE.md         # Agent commands phase
│       ├── PHASE_2B_COMPLETE.md         # New skills phase
│       ├── PHASE_2C_COMPLETE.md         # Existing skills phase
│       ├── PHASE_2D_COMPLETE.md         # Master docs phase
│       └── PHASE_2E_COMPLETE.md         # Final verification phase
│
├── examples/                              # ⭐ Development Projects Directory
│   ├── README.md                         # Guide for creating EN 50128 projects
│   │
│   ├── train_door_control/               # SIL 3 Reference Implementation
│   │   ├── README.md                    # Project documentation
│   │   ├── LIFECYCLE_STATE.md           # COD lifecycle tracking (if COD used)
│   │   ├── Makefile                     # Build system with coverage
│   │   ├── docs/                        # EN 50128 documentation
│   │   │   └── requirements.md          # Software Requirements Specification
│   │   ├── src/                         # C source code (MISRA C compliant)
│   │   │   ├── door_control.c          # Main control logic
│   │   │   ├── door_control.h          # Public API
│   │   │   └── error_types.h           # Error definitions
│   │   ├── test/                        # Unity-based unit tests
│   │   │   ├── test_door_control.c     # Test suite
│   │   │   └── unity_config.h          # Unity configuration
│   │   ├── lib/                         # External libraries (Unity)
│   │   └── build/                       # Build artifacts (gitignored)
│   │
│   └── [your_project]/                   # ⭐ Your EN 50128 projects here
│       ├── README.md                    # Project documentation
│       ├── LIFECYCLE_STATE.md           # COD lifecycle tracking (COD managed)
│       ├── Makefile                     # Build system
│       ├── docs/                        # Requirements, design, safety docs
│       ├── src/                         # Your C source code
│       ├── test/                        # Your unit tests
│       └── build/                       # Build artifacts
│
└── tools/                                 # Platform Development Tools
    ├── pdf-conversion/                    # PDF to Markdown Converter
    │   ├── pdf_to_markdown.py            # Main conversion script
    │   ├── table_formatter.py            # Table formatting module
    │   ├── convert.sh                    # Wrapper script
    │   ├── requirements.txt              # Python dependencies
    │   └── README.md                     # Tool documentation
    └── static-analysis/                   # MISRA C Checking Tools
        ├── cppcheck-misra.py             # Cppcheck MISRA wrapper
        └── misra.json                    # MISRA C:2012 rules configuration
```

## Key Concepts

### Lifecycle Coordinator (COD)

The **Lifecycle Coordinator (COD)** is a platform extension role that orchestrates the complete EN 50128 software development lifecycle with SIL-dependent phase gate enforcement.

**When to Use COD:**
- **SIL 3-4 projects**: MANDATORY - COD provides strict phase gate enforcement
- **SIL 2 projects**: RECOMMENDED - COD provides semi-strict enforcement with justification requirements
- **SIL 0-1 projects**: OPTIONAL - COD provides advisory warnings only

**COD Initialization:**
```bash
# Initialize lifecycle tracking for your project
/cod plan --sil 3 --project train_door_control

# This creates LIFECYCLE_STATE.md in your project root
# Format: examples/[project_name]/LIFECYCLE_STATE.md
```

**COD Commands:**
| Command | Purpose | When to Use |
|---------|---------|-------------|
| `/cod plan --sil [0-4] --project [name]` | Initialize lifecycle tracking | At project start |
| `/cod gate-check <phase>` | Verify phase completion, authorize transition | After each phase |
| `/cod status` | View current lifecycle state and progress | Anytime during project |
| `/cod approve-requirement` | Approve requirement activities | Auto-triggered when `/req` invoked |

**SIL-Dependent Behavior:**
- **SIL 0-1**: Advisory mode - warnings only, allows user override
- **SIL 2**: Semi-strict mode - requires justification for incomplete criteria
- **SIL 3-4**: Strict gatekeeper - BLOCKS transitions until criteria met

**Phase Gates Enforced by COD:**
1. Planning gate (`/cod gate-check planning`)
2. Requirements gate (`/cod gate-check requirements`)
3. Design gate (`/cod gate-check design`)
4. Implementation gate (`/cod gate-check implementation`)
5. Integration gate (`/cod gate-check integration`)
6. Validation gate (`/cod gate-check validation`)
7. Assessment gate (`/cod gate-check assessment`)

**LIFECYCLE_STATE.md:**
COD maintains project state in `LIFECYCLE_STATE.md` (project root):
- Current phase and status
- Deliverable completion status
- Phase gate pass/fail status
- Traceability status (RTM completeness)
- Agent activity log
- Approval history

**Example: Using COD in a Project:**
```bash
# 1. Initialize project with COD
cd examples/my_sil3_project
/cod plan --sil 3 --project my_sil3_project

# 2. Proceed through lifecycle with phase gates
/pm   # Project setup
/cm   # Configuration management
/qua  # Quality assurance planning
/cod gate-check planning  # COD verifies planning complete

/req  # Requirements (COD requires user approval)
/cod gate-check requirements  # COD verifies SRS, RTM, hazard analysis

/des  # Design
/cod gate-check design  # COD verifies SAS, SDS, traceability

/imp  # Implementation
/cod gate-check implementation  # COD verifies MISRA C, coverage, complexity

# ... continue through integration, validation, assessment

# 3. Check status anytime
/cod status  # View current phase, deliverables, gate status
```

**Authority Structure with COD:**
```
    Lifecycle Coordinator (COD)
             |
    ┌────────┼────────┐
    |        |        |
   PM   Validator  Assessor
   |    (indep)    (indep)
   |
   └─── REQ, DES, IMP, TST, INT, VER, SAF, QUA, CM
```

- **COD**: Overall lifecycle authority, phase gate enforcement
- **PM**: Team/resource management, reports to COD for lifecycle decisions
- **Validator/Assessor**: Independent roles (SIL 3-4), coordinated by COD but not controlled

### Platform vs. Project

- **Platform (Repository Root)**: EN 50128 customization for OpenCode
  - Agents, skills, standards, documentation
  - Reusable across all EN 50128 projects
  - Version controlled as a unit
  
- **Projects (`examples/` directory)**: Individual railway software development instances
  - Each project is self-contained
  - Uses platform agents and skills
  - Follows EN 50128 lifecycle
  - Can be version controlled independently

### Why No `src/` in Root?

The root directory contains the **platform**, not a project. All project source code goes in `examples/[project_name]/src/`.

**Before (incorrect)**:
```
EN50128/
├── src/              # ❌ Confusing - is this platform code or project code?
└── examples/
    └── train_door_control/
        └── src/      # ❌ Duplicate structure
```

**After (correct)**:
```
EN50128/              # ✅ Platform only
└── examples/         # ✅ All projects here
    ├── train_door_control/
    │   └── src/      # ✅ Clear - this is project code
    └── your_project/
        └── src/      # ✅ Clear - this is your project code
```

**Notes:**
- **`std/`** contains LLM-friendly Markdown versions of EN 50128 standards
- **`docs/project-revision/`** archives all Phase completion reports  
- **`examples/`** is where ALL development happens
- **`examples/train_door_control/`** provides a complete SIL 3 reference
- Empty placeholder directories have been removed

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
