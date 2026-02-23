# Examples Directory

This directory contains **actual EN 50128 project instances** developed using the EN 50128 platform.

## Purpose

Each subdirectory represents a complete, self-contained railway software project developed according to EN 50128:2011 standards. These are real development instances, not templates.

## Structure

```
examples/
├── README.md                          # This file
├── train_door_control2/               # SIL 3 train door control system (reference implementation)
│   ├── src/                          # C source code
│   ├── test/                         # Unit tests
│   ├── docs/                         # Project documentation
│   │   ├── system/                   # System-level documents (EN 50126/50129)
│   │   └── *.md                      # Software documents (EN 50128)
│   ├── build/                        # Build artifacts
│   ├── LIFECYCLE_STATE.md            # Lifecycle tracking
│   └── Makefile                      # Build system
│
└── [your-project-name]/               # Your EN 50128 project
    ├── src/                          # Your source code
    ├── test/                         # Your tests
    ├── docs/                         # Your documentation
    │   └── system/                   # System documents (mandatory per EN 50128 7.2.2)
    ├── LIFECYCLE_STATE.md            # Created by /cod plan
    └── ...
```

## Creating a New Project

### Prerequisites: System-Level Documents (EN 50128 Section 7.2.2)

Before starting any EN 50128 project, you need **4 system-level input documents**:
1. System Requirements Specification
2. System Architecture Description  
3. System Safety Plan
4. System Safety Requirements Specification

**Two Options**:

**Option A: Use Platform Templates** (Recommended for learning):
```bash
# Templates are automatically offered by REQ/DES agents when missing
# Or manually copy from platform templates:
mkdir -p examples/my_project/docs/system
cp assets/sample_system/*.md examples/my_project/docs/system/
# Then customize for your system
```

**Option B: Study Reference Implementation**:
```bash
# See complete examples at:
cat examples/train_door_control2/docs/system/README.md
# Review the 4 system documents to understand structure and content
```

### Option 1: Use OpenCode Agents (Recommended)

Start a new EN 50128 project using lifecycle coordinator and agents:

```bash
# 1. Initialize project with COD
mkdir -p examples/my_railway_project
cd examples/my_railway_project
/cod plan --sil 3 --project my_railway_project

# 2. REQ agent will check for system documents
/req
# If missing, REQ offers to copy templates from assets/sample_system/

# 3. Continue with requirements
# Define requirements, assign SIL levels

# 4. Continue with design
/des
# Create architecture and design

# 5. Implement
/imp
# Generate C code with MISRA C compliance

# 6. Test
/tst
# Create unit tests with coverage

# 7. ... continue through lifecycle with /cod gate-check
```

### Option 2: Copy Existing Example (Advanced)

Use the reference implementation as a starting point:

```bash
# Copy train_door_control2 as template
cp -r examples/train_door_control2 examples/my_project
cd examples/my_project

# Clean up
rm -rf build/
find . -name "*.o" -delete
find . -name "*.gcda" -delete
find . -name "*.gcno" -delete
rm LIFECYCLE_STATE.md

# Reinitialize with COD
/cod plan --sil 3 --project my_project

# Customize system documents in docs/system/
# Update docs/Software-*.md for your requirements
# Modify src/ with your code
# Adapt tests to your components
```

### Option 3: Manual Setup

Create project structure manually:

```bash
cd examples
mkdir -p my_project/{src,test,docs,build}
cd my_project

# Create initial files
touch README.md
touch docs/requirements.md
touch src/main.c
touch test/test_main.c
touch Makefile

# Start developing with agent support
/req  # Requirements engineering
/des  # Design
/imp  # Implementation
```

## Available Examples

### Train Door Control System (train_door_control2)

**Path**: `examples/train_door_control2/`

**Description**: Complete SIL 3 train door control system reference implementation demonstrating:
- Complete EN 50128 V-Model lifecycle (Phases 0-5 complete)
- System-level documents (EN 50126/50129) in `docs/system/`
- Software-level documents (EN 50128) in `docs/`
- MISRA C:2012 compliant implementation
- Comprehensive unit testing with Unity framework
- Full requirements traceability (100%)
- Defensive programming patterns
- Redundant safety checks and dual-channel architecture

**SIL Level**: 3 (High safety integrity)

**Current Status**: Phase 5 (Integration) Complete ✅

**Key Documents**:
- **System Documents** (4):
  - `docs/system/System-Requirements-Specification.md` (71 system requirements)
  - `docs/system/System-Architecture-Description.md` (dual-channel architecture)
  - `docs/system/System-Safety-Plan.md` (safety management)
  - `docs/system/System-Safety-Requirements-Specification.md` (9 hazards, 7 safety functions)
- **Software Documents**:
  - `docs/Software-Requirements-Specification.md` (50 software requirements)
  - `docs/Software-Architecture-Specification.md` (8 modules)
  - `docs/Software-Design-Specification.md` (detailed design)
  - `docs/Software-Component-Design-Specification.md` (53 components)
  - `docs/Requirements-Traceability-Matrix.md` (complete traceability)

**Source Code**: 
- `src/` - 8 modules, 53 components, ~3,740 lines C
- `test/` - Unit tests with Unity framework
- Zero compilation warnings with strict GCC flags

**Key Features**:
- ✅ Static memory allocation only (no dynamic allocation)
- ✅ Cyclomatic complexity ≤ 10 (SIL 3 compliant)
- ✅ 100% defensive programming coverage
- ✅ Complete traceability (system → software → design → code → tests)
- ✅ Fail-safe error handling throughout
- ✅ Dual-channel processing with 2oo2 sensor redundancy

**Build & Test**:
```bash
cd examples/train_door_control2/src
make all           # Build static library
make clean         # Clean build artifacts
make check         # Run static analysis (requires cppcheck)
make complexity    # Analyze complexity (requires lizard)
```

**Use Cases**:
- **Reference implementation** for SIL 3 projects
- **Learning EN 50128** complete lifecycle example
- **Template for safety-critical C code** with best practices
- **Study system/software document relationships**
- **Testing framework example** with Unity integration

**See Also**:
- `examples/train_door_control2/docs/system/README.md` - System document guide
- `examples/train_door_control2/src/README.md` - Implementation status
- `examples/train_door_control2/LIFECYCLE_STATE.md` - Phase tracking

---

## Project Naming Conventions

When creating new projects in `examples/`, follow these naming conventions:

### Directory Names
- Use lowercase with underscores: `train_door_control`, `signal_interlocking`
- Be descriptive but concise
- Indicate project domain: `braking_system`, `atp_module`

### Project Structure (Standard)
```
your_project/
├── README.md              # Project overview, SIL level, status
├── LIFECYCLE_STATE.md     # Created by /cod plan, tracks phase progress
├── Makefile               # Build system
├── docs/                  # Documentation
│   ├── system/            # System-level documents (EN 50126/50129) ⚠️ REQUIRED
│   │   ├── README.md                                      # System docs guide
│   │   ├── System-Requirements-Specification.md          # System requirements
│   │   ├── System-Architecture-Description.md            # HW/SW architecture
│   │   ├── System-Safety-Plan.md                         # Safety management
│   │   └── System-Safety-Requirements-Specification.md   # Hazards, safety functions
│   ├── Software-Requirements-Specification.md    # Software requirements (EN 50128)
│   ├── Software-Architecture-Specification.md    # Software architecture
│   ├── Software-Design-Specification.md          # Software detailed design
│   ├── Requirements-Traceability-Matrix.md       # Traceability (system→SW→code→tests)
│   └── plans/                                     # SQAP, SCMP, SVP, SVaP
├── src/                   # C source code
│   ├── *.c                # Implementation files
│   ├── *.h                # Header files
│   └── common/            # Common types and error codes
├── test/                  # Unit tests
│   ├── test_*.c           # Unity test files
│   └── unity_config.h     # Unity configuration
├── build/                 # Build artifacts (gitignored)
│   ├── *.o                # Object files
│   ├── *.gcda/gcno        # Coverage data
│   └── test_runner        # Test executable
└── lib/                   # External libraries (Unity, etc.)
```

**⚠️ CRITICAL**: The `docs/system/` directory with 4 system documents is **MANDATORY** per EN 50128 Section 7.2.2. REQ and DES agents will check for these files and offer to copy templates if missing.

---

## SIL Level Guidelines

When creating a new project, determine the appropriate SIL level:

| SIL | Risk Level | Example Projects | Techniques Required |
|-----|------------|------------------|---------------------|
| **4** | Very High | Train control, ATP | Most stringent (Table A.3: Option A or B) |
| **3** | High | Door control, signaling | Structured methodology (M), Modular (M) |
| **2** | Medium | Passenger info with safety | Modular approach (M), Design standards (HR) |
| **1** | Low | Monitoring systems | Basic structure recommended |
| **0** | None | Administrative systems | Minimal requirements |

**Independence Requirements (Critical for SIL 3-4)**:
- Verifier MUST be independent of implementer
- Validator MUST be independent of designer/implementer
- Safety assessor MUST be independent of development team

---

## Development Workflow

For each project in `examples/`, follow the EN 50128 V-Model lifecycle with COD (Lifecycle Coordinator) oversight:

### Phase 0: Project Initialization (`/cod`)
```bash
cd examples/your_project
/cod plan --sil 3 --project your_project
# Creates LIFECYCLE_STATE.md, initializes phase tracking
```

### Phase 1: Planning (`/pm` or manual)
```bash
# Create planning documents
# - Software Quality Assurance Plan (SQAP)
# - Software Configuration Management Plan (SCMP)
# - Software Verification Plan (SVP)
# - Software Validation Plan (SVaP)
```

### Phase 2: Requirements (`/req`)
```bash
/req
# REQ checks for system documents in docs/system/
# If missing, offers to copy templates from assets/sample_system/
# Then: Define software requirements in docs/Software-Requirements-Specification.md
# Assign SIL levels to each requirement
# Create traceability matrix (system → software requirements)
/cod gate-check requirements
```

### Phase 3: Architecture & Design (`/des`)
```bash
/des
# DES checks for system documents (if not already done)
# Create architecture in docs/Software-Architecture-Specification.md
# Create detailed design in docs/Software-Design-Specification.md
# Define module interfaces
/cod gate-check design
```

### Phase 4: Safety Analysis (`/saf`)
```bash
/saf
# Perform FMEA analysis
# Create fault trees (FTA)
# Document in safety analysis reports
```

### Phase 5: Implementation (`/imp`)
```bash
/imp
# Implement C code in src/
# Follow MISRA C:2012
# Use defensive programming
# Static allocation only (SIL 2+)
/cod gate-check implementation
```

### Phase 6: Testing (`/tst`)
```bash
/tst
# Create unit tests in test/
# Measure coverage (100% for SIL 3+)
# Document test results
```

### Phase 7: Verification (`/ver`)
```bash
/ver
# Run static analysis
# Verify complexity (≤10 for SIL 3-4)
# Check MISRA C compliance
# Collect evidence
```

### Phase 8: Validation (`/val`)
```bash
/val
# System testing
# Acceptance testing
# Operational scenarios
/cod gate-check validation
```

### Throughout: Configuration Management (`/cm`)
```bash
/cm
# Version control
# Baseline management
# Change control
```

---

## Quality Requirements

All projects in `examples/` MUST meet these quality standards:

### Code Quality (SIL 2+)
- ✅ **MISRA C:2012 compliant**
- ✅ **Static memory allocation only** (no malloc/free)
- ✅ **Cyclomatic complexity ≤ 10** (SIL 3-4) or ≤ 15 (SIL 2)
- ✅ **Defensive programming** (validate inputs, check returns)
- ✅ **No recursion** (highly recommended SIL 3-4)

### Test Coverage (by SIL)
- **SIL 0-1**: Statement (HR), Branch (HR)
- **SIL 2**: Statement (HR), Branch (M)
- **SIL 3-4**: Statement (M), Branch (M), Condition (M)

### Documentation
- ✅ README.md with project overview and SIL level
- ✅ Requirements specification (SRS)
- ✅ Architecture specification (SAS)
- ✅ Design specification (SDS)
- ✅ Test documentation
- ✅ Safety analysis (FMEA/FTA for SIL 2+)

---

## Building and Testing

### Standard Makefile Targets

All projects should support these targets:

```bash
make              # Build source code
make test         # Build and run unit tests
make coverage     # Generate coverage report
make clean        # Remove build artifacts
make static       # Run static analysis (cppcheck, etc.)
make complexity   # Check cyclomatic complexity
```

### Unity Test Framework

Projects use Unity for unit testing:

- **Include**: `lib/Unity/` (Git submodule or vendored)
- **Test files**: `test/test_*.c`
- **Configuration**: `test/unity_config.h`
- **Assertions**: `TEST_ASSERT_EQUAL()`, `TEST_ASSERT_TRUE()`, etc.

---

## Best Practices

### 1. Keep Projects Self-Contained
Each project should be independently buildable:
```bash
cd examples/your_project
make test  # Should work without additional setup
```

### 2. Document Traceability
Maintain traceability in code comments:
```c
/**
 * @brief Opens the train doors safely
 * @traceto REQ-FUNC-004, DES-MOD-002
 */
error_t door_open(door_t* door);
```

### 3. Use Consistent Error Handling
```c
// Define common error types
typedef enum {
    SUCCESS = 0,
    ERROR_NULL_POINTER,
    ERROR_INVALID_PARAMETER,
    ERROR_OUT_OF_RANGE,
    ERROR_HARDWARE_FAULT
} error_t;

// Always check and propagate errors
error_t result = subsystem_function();
if (result != SUCCESS) {
    return result;  // Propagate error
}
```

### 4. Version Control
Each project maintains its own git history:
```bash
cd examples/your_project
git add .
git commit -m "feat: implement door open with safety checks"
```

### 5. Safety-Critical Patterns
- **Input validation**: Check all pointers, ranges, states
- **Fail-safe defaults**: Default to safe state on error
- **Redundancy**: Duplicate critical checks
- **Watchdogs**: Implement timeout monitoring
- **Self-tests**: Periodic health checks

---

## Contributing New Examples

To contribute a new example project:

1. **Create project structure** following conventions above
2. **Implement** with EN 50128 compliance
3. **Document** thoroughly (README, requirements, design)
4. **Test** with high coverage (≥90% for SIL 2, 100% for SIL 3+)
5. **Verify** with static analysis and complexity checks
6. **Submit** with clear commit messages and PR description

Example contribution:
```bash
# Create new project
mkdir -p examples/signal_interlocking
cd examples/signal_interlocking

# Develop with agents
/req  # Requirements
/des  # Design
/imp  # Implementation
/tst  # Testing

# Verify quality
make test
make coverage
make static

# Commit and PR
git add examples/signal_interlocking
git commit -m "feat(example): add SIL 4 signal interlocking system"
git push origin feature/signal-interlocking
```

---

## Support and Resources

### EN 50128 Platform Resources
- **Main README**: `../../README.md` - Platform overview
- **Lifecycle Guide**: `../../LIFECYCLE.md` - Complete V-Model phases
- **Agent Reference**: `../../AGENTS.md` - 13 agent roles
- **Tutorial**: `../../TUTORIAL.md` - Step-by-step walkthrough
- **Skills**: `../../.opencode/skills/en50128-*/` - Domain-specific patterns
- **System Templates**: `../../assets/sample_system/` - System document templates
- **Standards**: `../../std/EN50128-2011.md` - Full EN 50128 standard

### External Resources
- Unity Test Framework: https://github.com/ThrowTheSwitch/Unity
- MISRA C:2012 Guidelines: https://www.misra.org.uk
- EN 50128:2011 Standard: Official standard document
- EN 50126:2017 RAMS: System-level safety management
- EN 50129:2018: Safety cases and acceptance

### Getting Help
- Review reference implementation: `train_door_control2/`
- Use OpenCode agents: `/req`, `/des`, `/imp`, `/cod`, etc.
- Check system document templates: `assets/sample_system/README.md`
- Follow tutorial: `../../TUTORIAL.md`
- Review lifecycle phases: `../../LIFECYCLE.md`

---

## Summary

- **`examples/`** = Real EN 50128 project instances
- **Each project** = Self-contained, fully documented, compliant
- **Use agents** = `/req`, `/des`, `/imp`, `/tst`, `/ver`, `/val`
- **Follow standards** = MISRA C, EN 50128 technique tables
- **Maintain quality** = High coverage, low complexity, defensive programming

**Start your EN 50128 project here!**
