# EN 50128 Railway Software Development Platform

**OpenCode customization for EN 50128:2011 compliant railway software development**

## Overview

This project transforms OpenCode into an **EN 50128 compliant development platform** providing:
- **12 specialized agents** for EN 50128 lifecycle management and compliance tasks (Lifecycle Coordinator, Requirements, Design, Implementation, Testing, Verification, Validation, Safety, Quality, Integration, Project Management, Configuration Management)
- **12 domain-specific skills** with patterns, templates, and best practices
- **Complete EN 50128 standards** in LLM-friendly Markdown format (2.7 MB)
- **EN 50128 V-Model lifecycle** implementation with phase gate enforcement
- **Production-ready workflows** for safety-critical railway software

**This is a development platform, not a project template.** All actual development projects are created in the `examples/` directory.

## Quick Start

### Getting Help

```bash
# List all available commands
/enhelp

# Get detailed help for a specific command
/enhelp cod
/enhelp workspace
/enhelp req
```

### Creating Your First EN 50128 Project

1. **Create a project directory in examples/**:
   ```bash
   mkdir -p examples/my_railway_project
   cd examples/my_railway_project
   ```

2. **Initialize lifecycle tracking with COD**:
   ```bash
   /cod plan --sil 3 --project my_railway_project
   # COD creates lifecycle plan and LIFECYCLE_STATE.md
   ```

3. **Start with requirements** (COD will request approval):
   ```bash
   /req  # Begin with Requirements Engineering
   # COD monitors: User approval required for requirements
   # Define requirements, assign SIL levels, establish traceability
   ```

4. **Follow the EN 50128 V-Model lifecycle**:
   ```bash
   /des  # Architecture & Design
   /cod gate-check design  # COD verifies phase completion
   
   /saf  # Safety Analysis (FMEA, FTA)
   /imp  # Implementation (C + MISRA C:2012)
   /cod gate-check implementation  # COD enforces quality gates
   
   /tst  # Unit Testing with coverage
   /ver  # Verification (static analysis)
   /int  # Component Integration
   /cod gate-check integration
   
   /val  # Validation (system testing)
   /cod gate-check validation
   
   /cm   # Configuration Management (throughout)
   /qua  # Quality Assurance (throughout)
   /pm   # Project coordination (reports to COD)
   ```

5. **Reference the working example**: 
   - See `examples/train_door_control/` for a complete SIL 3 implementation
   - Use it as a reference for structure, code style, and documentation

### Working with Multiple Projects

The platform supports multiple concurrent projects with independent lifecycle tracking:

```bash
# Check which workspace is active
/workspace status
# or
/ws status

# List all available projects
/workspace list
# or
/ws list

# Switch between projects
/workspace switch train_door_control2
# or
/ws switch train_door_control2

# Create a new project
/workspace create brake_controller --sil 4
# or
/ws create brake_controller --sil 4
```

**Important**: All agents automatically work on the active workspace. When you switch workspaces, each project preserves its own phase progress, completion status, and documentation.

See [Workspace Management](#workspace-management) section for detailed information.

### Understanding the Platform

#### 1. Understand Your SIL Level

Determine the Safety Integrity Level (SIL) for your project:

| SIL | Risk Level | Example Applications |
|-----|------------|---------------------|
| 4 | Very High | Train control systems, automatic train protection |
| 3 | High | Signaling systems, interlocking |
| 2 | Medium | Passenger information systems with safety impact |
| 1 | Low | Non-critical monitoring systems |
| 0 | None | Administrative systems |

#### 2. Available Agents

Use specialized agents via slash commands:

- `/cod` - **Lifecycle Coordinator** - Lifecycle orchestration, phase gates, V-Model compliance
- `/req` - Requirements Engineer - Requirements specification and management
- `/des` - Designer - Software architecture and design
- `/imp` - Implementer - C code implementation with MISRA C compliance
- `/tst` - Tester - Unit and integration testing with coverage analysis
- `/int` - Integrator - Component integration and interface testing
- `/ver` - Verifier - Static analysis and verification evidence collection
- `/val` - Validator - System testing and acceptance validation
- `/saf` - Safety Engineer - Hazard analysis, FMEA, and safety case
- `/qua` - Quality Assurance - Code reviews, audits, and quality gates
- `/pm` - Project Manager - Project coordination and CCB leadership (reports to COD)
- `/cm` - Configuration Manager - Version control and baseline management
- `/workspace` (or `/ws`) - Workspace management - Switch between projects
- `/enhelp` - Display help information for all commands

**Note:** COD (Lifecycle Coordinator) is the primary orchestrator. For SIL 3-4 projects, COD enforces strict phase gates. For SIL 0-2, COD provides advisory guidance.

**Getting Help:**
```bash
# List all available commands
/enhelp

# Get detailed help for a specific command
/enhelp cod
/enhelp workspace
/enhelp req
```

See [AGENTS.md](AGENTS.md) for detailed agent documentation.

#### 3. Example Workflow

#### Complete SIL 3 Development Flow

```bash
# 1. Requirements Engineering
/req
# Define requirements, assign SIL levels, establish traceability

# 2. Architecture and Design
/des
# Create software architecture (SAS) and design (SDS)

# 3. Safety Analysis
/saf
# Perform FMEA/FTA, define safety requirements

# 4. Implementation
/imp
# Implement C code with MISRA C:2012 compliance

# 5. Unit Testing
/tst
# Execute unit tests, measure coverage (100% for SIL 3)

# 6. Verification
/ver
# Run static analysis, verify complexity, code reviews

# 7. Integration
/int
# Integrate components, interface testing

# 8. Validation
/val
# System testing, UAT, safety validation

# 9. Configuration Management (Throughout)
/cm
# Version control, change management, baselines

# 10. Quality Assurance (Throughout)
/qua
# Code reviews, audits, quality gates
```

## Workspace Management

The platform supports **multiple concurrent projects** with independent lifecycle states. Each project in the `examples/` directory is a separate workspace.

### Key Concepts

- **Workspace**: An independent EN 50128 project with its own lifecycle tracking
- **Active Workspace**: The current project you're working on
- **Workspace Switching**: Ability to pause one project and resume another without losing context

### Workspace Commands

Use `/workspace` (or `/ws` for short) to manage workspaces:

```bash
# List all available workspaces
/workspace list
# or
/ws list

# Show current workspace status
/workspace status
# or
/ws status

# Switch to a different workspace
/workspace switch train_door_control2
# or
/ws switch train_door_control2

# Create a new workspace
/workspace create brake_controller --sil 4
# or
/ws create brake_controller --sil 4
```

### How It Works

1. **Workspace State File**: `.workspace` (JSON) at platform root tracks:
   - Active workspace name
   - All workspace metadata (SIL level, current phase, completion %)
   - Last accessed timestamp

2. **Per-Workspace Tracking**: Each workspace has:
   - Independent `LIFECYCLE_STATE.md` tracking phase progress
   - Complete documentation in `docs/` directory
   - Source code in `src/` directory
   - Test code in `test/` directory

3. **Agent Context**: All agents automatically operate on the active workspace:
   - Read `.workspace` file to determine active project
   - Operate on files in `examples/<active_workspace>/`
   - Display workspace context in responses

### Example: Multi-Project Workflow

```bash
# Working on train door control system
$ /ws status
📁 Active Workspace: train_door_control (SIL 3)
   Phase: Architecture & Design (Phase 3) | Completion: 75%

$ /des
# Work on design for train_door_control...

# Need to switch to brake controller project
$ /ws switch brake_controller
✅ Workspace switched to: brake_controller
   SIL Level: 4
   Phase: Requirements (Phase 2) | Completion: 30%

$ /req
# Work on requirements for brake_controller...

# Switch back to train door control
$ /ws switch train_door_control
✅ Workspace switched to: train_door_control
   (Context preserved - still at Phase 3, 75%)

$ /des
# Resume design work exactly where you left off...
```

### Available Example Projects

The platform includes complete example projects:

1. **`train_door_control`** (SIL 3)
   - Complete implementation (Phase 7 - Validation, 85% complete)
   - Train door control system with safety interlocks
   - Full documentation, C source code, unit tests
   - Use as reference for new projects

2. **`train_door_control2`** (SIL 3)
   - In-progress project (Phase 3 - Architecture, 30% complete)
   - Demonstrates system-level input documents
   - 4 EN 50128 Section 7.2.2 system documents
   - Shows requirements-to-design transition

### Creating New Workspaces

When creating a new workspace, the platform automatically:
- Creates directory structure (`docs/`, `src/`, `test/`, `tools/`)
- Generates README.md with project information
- Creates Makefile skeleton for C projects
- Initializes git repository (optional)

```bash
# Create new SIL 4 project
$ /ws create automatic_train_protection --sil 4

✅ Workspace created: automatic_train_protection
   Path: examples/automatic_train_protection/
   SIL Level: 4
   
Next steps:
  1. Switch to workspace: /ws switch automatic_train_protection
  2. Initialize lifecycle: /cod plan --sil 4 --project automatic_train_protection
  3. Begin requirements: /req
```

### Workspace Directory Structure

Each workspace follows EN 50128 structure:

```
examples/<workspace_name>/
├── LIFECYCLE_STATE.md          # Phase tracking (managed by COD)
├── README.md                   # Project overview
├── Makefile                    # Build configuration
├── docs/                       # EN 50128 documentation
│   ├── system/                 # System-level inputs (Section 7.2.2)
│   ├── plans/                  # SQAP, SCMP, SVP, SVaP
│   ├── Software-Requirements-Specification.md
│   ├── Software-Architecture-Specification.md
│   ├── Software-Design-Specification.md
│   └── ...                     # Other EN 50128 documents
├── src/                        # C source code
│   ├── <module>.h
│   └── <module>.c
├── test/                       # Unit and integration tests
│   └── test_<module>.c
└── tools/                      # Build and analysis scripts
```

### Detailed Workflows and Best Practices

For comprehensive workspace management workflows, see:
- **[Workspace Workflows and Best Practices](docs/WORKSPACE-WORKFLOWS.md)** - Detailed multi-project workflows, common scenarios, troubleshooting, and advanced tips

**Topics covered**:
- Parallel development on multiple projects
- Maintenance on production while developing new features
- Using reference implementations
- Best practices for workspace naming and organization
- Troubleshooting common issues

### Best Practices

1. **Always check active workspace** before starting work:
   ```bash
   /ws status
   ```

2. **Use descriptive workspace names**:
   - Good: `train_door_control`, `automatic_brake_system`
   - Bad: `project1`, `test`

3. **Complete phase transitions** before switching workspaces:
   ```bash
   /cod gate-check design  # Complete current phase
   /ws switch other_project  # Then switch
   ```

4. **Regular status checks** when returning to a workspace:
   ```bash
   /ws switch train_door_control
   /cod status  # See detailed phase progress
   ```

5. **Archive completed projects**:
   ```bash
   /ws archive train_door_control  # Mark as completed
   ```

## Documentation

### Core Platform Documentation

Essential references in root directory:

1. **[LIFECYCLE.md](LIFECYCLE.md)** - Complete EN 50128 V-Model lifecycle (1637 lines)
   - All 10 lifecycle phases (Initialization → Deployment)
   - Entry/exit criteria, deliverables, agent workflows
   - COD gate enforcement (SIL-dependent: Advisory/Semi-strict/Strict)
   
2. **[AGENTS.md](AGENTS.md)** - Role-based agent definitions (837 lines)
   - All 12 agents with EN 50128 role mappings (Section 5, Annex B)
   - Responsibilities, techniques from Annex A tables
   - C language constraints and MISRA C:2012 compliance
   
3. **[PHASES-VS-DOCUMENTS.md](PHASES-VS-DOCUMENTS.md)** - Phase-to-document reference (580 lines)
   - Complete mapping: 10 phases → 30+ documents
   - Exact EN 50128 document names from Section 7.X.3
   - V-Model correspondence (Specification → Report)
   - Quick command reference for all phases
   
4. **[EN50128-DELIVERABLES-MAPPING.md](EN50128-DELIVERABLES-MAPPING.md)** - Document naming guide (264 lines)
   - Exact names from EN 50128 Section 7 (with pluralization rules)
   - File naming strategy (hyphens, case conventions)
   - Document ID format (`DOC-<TYPE>-YYYY-NNN`)
   - QUA checker mappings

### Supporting Documentation

5. **[CONTRIBUTING.md](CONTRIBUTING.md)** - Contribution guidelines
6. **[CHANGELOG.md](CHANGELOG.md)** - Version history and releases
7. **[GITHUB_SETUP.md](GITHUB_SETUP.md)** - Git/GitHub setup and workflow

## Project Structure

This is an **EN 50128 platform** (not a project). Actual development projects go in `examples/`.

```
EN50128/                                   # EN 50128 Development Platform
│
├── AGENTS.md                              # 11 agent definitions and workflows
├── LIFECYCLE.md                           # Complete EN 50128 V-Model lifecycle
├── README.md                              # This file (platform overview)
│
├── .opencode/                             # OpenCode customization
│   ├── commands/                          # 11 EN 50128 agent commands
│   │   ├── req.md                        # Requirements Engineer
│   │   ├── des.md                        # Designer
│   │   ├── imp.md                        # Implementer (C + MISRA C)
│   │   ├── tst.md                        # Tester
│   │   ├── int.md                        # Integrator
│   │   ├── ver.md                        # Verifier (static analysis)
│   │   ├── val.md                        # Validator (system testing)
│   │   ├── saf.md                        # Safety Engineer (FMEA, FTA)
│   │   ├── qua.md                        # Quality Assurance
│   │   ├── pm.md                         # Project Manager
│   │   └── cm.md                         # Configuration Manager
│   └── skills/                            # 12 domain-specific EN 50128 skills
│       ├── en50128-requirements/         # Requirements engineering
│       ├── en50128-design/               # Architecture & design patterns
│       ├── en50128-implementation/       # C implementation with MISRA C
│       ├── en50128-testing/              # Testing methodologies
│       ├── en50128-integration/          # Integration techniques
│       ├── en50128-verification/         # Verification & static analysis
│       ├── en50128-validation/           # Validation & system testing
│       ├── en50128-safety/               # Safety analysis (FMEA, FTA)
│       ├── en50128-quality/              # Quality assurance
│       ├── en50128-documentation/        # Documentation templates
│       ├── en50128-project-management/   # Project management
│       └── en50128-configuration/        # Configuration management
│
├── std/                                   # EN 50128 Standards (LLM-friendly)
│   ├── EN50128-2011.md                   # Main railway standard (2.2 MB)
│   ├── EN 50126-1-2017.md                # RAMS Part 1 (293 KB)
│   ├── EN 50126-2-2017.md                # RAMS Part 2 (210 KB)
│   ├── EN50128-ABBREVIATIONS.md          # Official abbreviations
│   └── EN50128-TABLES-EXTRACTED.md       # All technique tables (A.2-A.23)
│
├── docs/                                  # Platform documentation
│   ├── QUICKSTART.md                     # Getting started guide
│   ├── SETUP.md                          # Setup instructions
│   ├── EN50128-Compliance-Guide.md       # Compliance overview
│   ├── Project-Structure.md              # Detailed structure
│   └── project-revision/                 # Project revision history (archived)
│
├── examples/                              # ⭐ YOUR PROJECTS GO HERE
│   ├── README.md                         # Guide for creating projects
│   ├── train_door_control/               # Complete SIL 3 reference implementation
│   │   ├── src/                         # C source code (MISRA C compliant)
│   │   ├── test/                        # Unity-based unit tests
│   │   ├── docs/                        # Requirements, design, safety
│   │   ├── Makefile                     # Build system with coverage
│   │   └── README.md                    # Project documentation
│   └── [your_project]/                   # Your EN 50128 project here
│
└── tools/                                 # Platform development tools
    ├── pdf-conversion/                    # PDF to Markdown converter
    └── static-analysis/                   # MISRA C checking tools
```

**Key Points**:
- **Platform root** = EN 50128 customization for OpenCode (agents, skills, standards)
- **`examples/`** = Where all actual railway software projects are developed
- **No `src/` in root** = This is not a project; projects go in `examples/`

**Note**: See [docs/Project-Structure.md](docs/Project-Structure.md) for complete details.

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

### 5. PDF to Markdown Conversion

Convert EN 50128 standard PDFs to LLM-friendly Markdown for easy reference and AI agent integration.

**Features:**
- LLM-optimized conversion using PyMuPDF4LLM
- Table formatting and cleanup
- Metadata extraction
- Batch processing support

**Usage:**
```bash
# Convert all standards (via OpenCode)
/pdf2md --all

# Convert single file
/pdf2md std/EN50128-2011.pdf

# Check conversion status
/pdf2md --check

# Direct script usage
./tools/pdf-conversion/convert.sh --all
```

**Documentation:** [tools/pdf-conversion/README.md](tools/pdf-conversion/README.md)

### 6. Documentation Management

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
| 2.0.0 | 2026-02-21 | Complete EN 50128 compliance implementation: All 10 V-Model phases defined with exact EN 50128 document names; Phase definitions for Phases 2-7 operational (Requirements → Validation); 12 agents fully operational with SIL-dependent behaviors; Comprehensive documentation consolidated (7 informatic files removed); See [REMOVED_FILES.md](REMOVED_FILES.md) for details |
| 1.0.0 | 2026-02-06 | Initial complete platform: 11 agents, 12 skills, complete EN 50128 standards; Working SIL 3 example (train_door_control) |
| 0.1.0 | 2026-02-06 | Initial project setup with agents, skills, and documentation |

---

**Note**: This project provides guidance and tools for EN 50128 compliance. Actual certification requires independent safety assessment by qualified assessors and approval by relevant railway authorities.
