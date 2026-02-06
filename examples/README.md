# Examples Directory

This directory contains **actual EN 50128 project instances** developed using the EN 50128 platform.

## Purpose

Each subdirectory represents a complete, self-contained railway software project developed according to EN 50128:2011 standards. These are real development instances, not templates.

## Structure

```
examples/
├── README.md                          # This file
├── train_door_control/                # SIL 3 train door control system
│   ├── src/                          # C source code
│   ├── test/                         # Unit tests
│   ├── docs/                         # Project documentation
│   ├── build/                        # Build artifacts
│   └── Makefile                      # Build system
│
└── [your-project-name]/               # Your EN 50128 project
    ├── src/                          # Your source code
    ├── test/                         # Your tests
    ├── docs/                         # Your documentation
    └── ...
```

## Creating a New Project

### Option 1: Use OpenCode Agents (Recommended)

Start a new EN 50128 project from scratch:

```bash
# Create project directory
mkdir -p examples/my_railway_project
cd examples/my_railway_project

# Start with requirements
/req
# Define requirements, assign SIL levels

# Continue with design
/des
# Create architecture and design

# Implement
/imp
# Generate C code with MISRA C compliance

# Test
/tst
# Create unit tests with coverage

# ... continue through lifecycle
```

### Option 2: Copy Existing Example

Use an existing example as a starting point:

```bash
# Copy train door control as template
cp -r examples/train_door_control examples/my_project
cd examples/my_project

# Clean up
rm -rf build/
find . -name "*.o" -delete
find . -name "*.gcda" -delete
find . -name "*.gcno" -delete

# Customize
# - Update README.md with your project info
# - Modify src/ with your code
# - Update docs/ with your requirements/design
# - Adapt tests to your components
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

### 1. Train Door Control System

**Path**: `examples/train_door_control/`

**Description**: Complete SIL 3 train door control system demonstrating:
- Safety-critical door control logic
- MISRA C:2012 compliant implementation
- Comprehensive unit testing with Unity framework
- Full requirements traceability
- Defensive programming patterns
- Redundant safety checks

**SIL Level**: 3 (High safety integrity)

**Files**:
- `src/door_control.c` - Main control logic (~250 lines)
- `src/door_control.h` - Public API
- `src/error_types.h` - Error definitions
- `test/test_door_control.c` - Unit tests (~320 lines)
- `docs/requirements.md` - Complete SRS

**Key Features**:
- ✅ Static memory allocation only
- ✅ Cyclomatic complexity ≤ 10
- ✅ 100% statement/branch coverage
- ✅ Defensive programming throughout
- ✅ Fail-safe error handling

**Build & Test**:
```bash
cd examples/train_door_control
make test          # Run tests
make coverage      # Generate coverage report
make clean         # Clean build artifacts
```

**Use Cases**:
- Reference implementation for SIL 3 projects
- Learning EN 50128 compliance patterns
- Template for safety-critical C code
- Testing framework example

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
├── README.md              # Project overview, SIL level, requirements
├── Makefile               # Build system
├── docs/                  # Documentation
│   ├── requirements.md    # SRS (Software Requirements Specification)
│   ├── architecture.md    # SAS (Software Architecture Specification)
│   ├── design.md          # SDS (Software Design Specification)
│   └── safety.md          # Safety analysis (FMEA, FTA)
├── src/                   # C source code
│   ├── *.c                # Implementation files
│   ├── *.h                # Header files
│   └── error_types.h      # Common error definitions
├── test/                  # Unit tests
│   ├── test_*.c           # Unity test files
│   └── unity_config.h     # Unity configuration
├── build/                 # Build artifacts (gitignored)
│   ├── *.o                # Object files
│   ├── *.gcda/gcno        # Coverage data
│   └── test_runner        # Test executable
└── lib/                   # External libraries (Unity, etc.)
```

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

For each project in `examples/`, follow the EN 50128 V-Model lifecycle:

### 1. Requirements Phase (`/req`)
```bash
cd examples/your_project
/req
# Define requirements in docs/requirements.md
# Assign SIL levels to each requirement
# Create traceability matrix
```

### 2. Architecture & Design Phase (`/des`)
```bash
/des
# Create architecture in docs/architecture.md
# Create detailed design in docs/design.md
# Define module interfaces
```

### 3. Safety Analysis Phase (`/saf`)
```bash
/saf
# Perform FMEA analysis
# Create fault trees (FTA)
# Document in docs/safety.md
```

### 4. Implementation Phase (`/imp`)
```bash
/imp
# Implement C code in src/
# Follow MISRA C:2012
# Use defensive programming
# Static allocation only (SIL 2+)
```

### 5. Testing Phase (`/tst`)
```bash
/tst
# Create unit tests in test/
# Measure coverage (100% for SIL 3+)
# Document test results
```

### 6. Verification Phase (`/ver`)
```bash
/ver
# Run static analysis
# Verify complexity (≤10 for SIL 3-4)
# Check MISRA C compliance
# Collect evidence
```

### 7. Validation Phase (`/val`)
```bash
/val
# System testing
# Acceptance testing
# Operational scenarios
```

### 8. Configuration Management (`/cm`)
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
- **Lifecycle Guide**: `../../LIFECYCLE.md`
- **Agent Reference**: `../../AGENTS.md`
- **Skills**: `../../.opencode/skills/en50128-*/`
- **Standards**: `../../std/EN50128-2011.md`

### External Resources
- Unity Test Framework: https://github.com/ThrowTheSwitch/Unity
- MISRA C:2012 Guidelines: https://www.misra.org.uk
- EN 50128:2011 Standard: `../../std/EN50128-2011.md`

### Getting Help
- Review existing examples in this directory
- Consult `../../docs/QUICKSTART.md`
- Use OpenCode agents: `/req`, `/des`, `/imp`, etc.
- Check `../../docs/EN50128-Compliance-Guide.md`

---

## Summary

- **`examples/`** = Real EN 50128 project instances
- **Each project** = Self-contained, fully documented, compliant
- **Use agents** = `/req`, `/des`, `/imp`, `/tst`, `/ver`, `/val`
- **Follow standards** = MISRA C, EN 50128 technique tables
- **Maintain quality** = High coverage, low complexity, defensive programming

**Start your EN 50128 project here!**
