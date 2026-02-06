# EN 50128 Project - Revision Summary

## Changes Made

### 1. OpenCode Agent Configuration

Created `.opencode/commands/` directory with 8 role-based agent definitions:

- **`req.md`** - Requirements Engineer
- **`des.md`** - Designer  
- **`imp.md`** - Implementer
- **`tst.md`** - Tester
- **`saf.md`** - Safety Engineer
- **`ver.md`** - Verifier
- **`val.md`** - Validator
- **`qua.md`** - Quality Assurance

Each agent file defines:
- Role and responsibilities per EN 50128
- Behavioral constraints by SIL level
- C language specific requirements
- Output artifacts
- Interaction with other agents

### 2. Role-Based Agent Behaviors

All agents now strictly follow EN 50128 standard requirements:

#### Requirements Engineer (`/req`)
- Structured requirements specification
- SHALL/SHOULD/MAY enforcement
- Traceability matrices mandatory
- C language considerations

#### Designer (`/des`)
- Cyclomatic complexity limits: 10 (SIL 3-4), 15 (SIL 2), 20 (SIL 0-1)
- Static memory allocation only (SIL 2+)
- No recursion (highly recommended SIL 3-4)
- MISRA C compliant design patterns

#### Implementer (`/imp`)
- **MISRA C:2012 mandatory for SIL 2+**
- No `malloc/calloc/realloc/free` for SIL 2+
- Fixed-width types (`uint8_t`, `uint16_t`, etc.)
- All pointers validated
- All return values checked
- Defensive programming mandatory

#### Tester (`/tst`)
- Coverage requirements by SIL:
  - SIL 2: Statement 100%, Branch 100%
  - SIL 3-4: Statement 100%, Branch 100%, Condition 100%
- Independent testing (mandatory SIL 3-4)
- Unity/CUnit test frameworks for C
- gcov/lcov coverage tools

#### Safety Engineer (`/saf`)
- Hazard analysis and FMEA/FTA
- C-specific failure modes (NULL pointers, buffer overflow, integer overflow)
- Safety patterns in C code
- Watchdog implementation
- Redundancy and voting patterns

#### Verifier (`/ver`)
- Independent verification (mandatory SIL 3-4)
- Static analysis: PC-lint, Cppcheck, Clang
- MISRA C compliance checking
- Complexity verification
- Evidence collection

#### Validator (`/val`)
- Independent validation (mandatory SIL 3-4)
- System testing on target hardware
- Operational scenario validation
- Python test harness for automation

#### Quality Assurance (`/qua`)
- Code review process (mandatory for all code)
- MISRA C compliance verification
- Quality metrics collection
- Audit and inspection processes

### 3. C Language Focus

#### Updated Skills
Created `skills/en50128-implementation.skill` with:
- MISRA C:2012 core rules
- C implementation patterns
- Module structure (header/implementation)
- Error handling patterns
- Defensive programming examples
- Buffer management (static allocation)
- Safe arithmetic operations
- State machine implementation
- Watchdog patterns
- Coding style guidelines

#### Existing Skills Updated
All skills now address C language requirements:
- `en50128-requirements.skill` - C data types and memory constraints
- `en50128-design.skill` - C module design, static allocation
- `en50128-testing.skill` - C unit testing with Unity/CUnit
- `en50128-safety.skill` - C safety patterns and defensive programming

### 4. MISRA C Compliance Tools

#### PC-lint Plus Configuration (`tools/static-analysis/pclint.lnt`)
- MISRA C:2012 checking enabled
- Rule 21.3: Dynamic memory prohibited (SIL 2+)
- NULL pointer checks
- Division by zero detection
- Buffer overflow detection
- Complexity limits by SIL
- Justified suppressions documented

#### Cppcheck Configuration (`tools/static-analysis/cppcheck-project.xml`)
- MISRA C:2012 addon enabled
- CERT C addon enabled
- Exhaustive checking
- Platform-specific checks

#### MISRA Compliance Checker (`tools/static-analysis/check_misra.py`)
Python script that:
- Runs PC-lint Plus
- Runs Cppcheck with MISRA addon
- Checks for dynamic memory allocation (forbidden SIL 2+)
- Checks for recursion
- Generates compliance report
- Returns exit code for CI/CD integration

### 5. Python for Scripting Only

Python explicitly designated for:
- Build automation (Makefile generation)
- Test harness (test execution, result collection)
- Analysis tools (coverage, metrics, static analysis)
- Report generation (markdown/PDF)
- Configuration management scripts

**Python MUST NOT be used for**:
- Safety-critical functions
- Code deployed to target system
- Any code subject to SIL requirements

### 6. Updated AGENTS.md

Completely rewritten to reflect:
- Role-based agent structure
- C as primary development language
- Python for scripting support only
- EN 50128 behavioral constraints
- Typical development workflow
- C language compliance summary
- Agent interaction diagram

## Agent Usage

### Invoke Agents via Slash Commands

```bash
# Requirements phase
/req

# Design phase
/des

# Implementation phase
/imp

# Testing phase
/tst

# Safety analysis
/saf

# Verification
/ver

# Validation
/val

# Quality assurance
/qua
```

Each agent loads its behavior from `.opencode/commands/<agent>.md` and references appropriate skills.

## Key Compliance Features

### SIL 2+ Requirements
- No dynamic memory allocation
- MISRA C:2012 compliance mandatory
- Static analysis mandatory
- 100% branch coverage

### SIL 3-4 Requirements
- Independent verification team
- Independent validation team
- Cyclomatic complexity ≤ 10
- 100% condition coverage
- No recursion (highly recommended)

### C Coding Standards
- Fixed-width types only
- Static allocation only (SIL 2+)
- All pointers validated
- All return values checked
- All errors handled explicitly
- Defensive programming throughout

## Verification

All agents are now:
1. ✓ Configured as OpenCode slash commands
2. ✓ Role-specific per EN 50128
3. ✓ C language focused
4. ✓ MISRA C:2012 compliant
5. ✓ SIL-aware behavioral constraints
6. ✓ Python for scripting support only
7. ✓ Tool configurations included

## Next Steps

To use the system:

1. **Select SIL level** for your project
2. **Invoke `/req`** to start requirements specification
3. **Use `/des`** for architecture and design
4. **Implement with `/imp`** following MISRA C
5. **Test with `/tst`** ensuring coverage requirements
6. **Analyze safety with `/saf`**
7. **Verify with `/ver`** using static analysis
8. **Validate with `/val`** on target hardware
9. **Quality check with `/qua`** throughout

Each agent will guide you through EN 50128-compliant development with C as the primary language.
