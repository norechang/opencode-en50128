# Agent-Skill Linking: Complete Summary

## Overview

This document explains the explicit relationship between EN 50128 agent commands and their associated skills in the OpenCode framework.

## ✅ All Agents and Skills Configured

### Complete Mapping Table

| # | Agent Role | Command | Skill Name | Skill File | Status |
|---|------------|---------|------------|------------|--------|
| 1 | Requirements Engineer | `/req` | `en50128-requirements` | `.opencode/skills/en50128-requirements/SKILL.md` | ✅ |
| 2 | Designer | `/des` | `en50128-design` | `.opencode/skills/en50128-design/SKILL.md` | ✅ |
| 3 | Implementer | `/imp` | `en50128-implementation` | `.opencode/skills/en50128-implementation/SKILL.md` | ✅ |
| 4 | Tester | `/tst` | `en50128-testing` | `.opencode/skills/en50128-testing/SKILL.md` | ✅ |
| 5 | Safety Engineer | `/saf` | `en50128-safety` | `.opencode/skills/en50128-safety/SKILL.md` | ✅ |
| 6 | Verifier | `/ver` | `en50128-verification` | `.opencode/skills/en50128-verification/SKILL.md` | ✅ |
| 7 | Validator | `/val` | `en50128-validation` | `.opencode/skills/en50128-validation/SKILL.md` | ✅ |
| 8 | Quality Assurance | `/qua` | `en50128-quality` | `.opencode/skills/en50128-quality/SKILL.md` | ✅ |
| 9 | (Shared) | N/A | `en50128-documentation` | `.opencode/skills/en50128-documentation/SKILL.md` | ✅ |

**Total**: 8 agent commands + 9 skills (1 shared documentation skill)

## How Agents Load Skills

### 1. Command File References Skill

Each agent command file (`.opencode/commands/[name].md`) contains a "Reference Skills" section:

```markdown
## Reference Skills
- Load skill: `en50128-[name]`
```

**Example** (from `/req` agent):
```markdown
## Reference Skills
- Load skill: `en50128-requirements`
```

### 2. Skill Provides Domain Knowledge

Each skill file (`.opencode/skills/en50128-[name]/SKILL.md`) contains:
- YAML frontmatter with metadata
- Domain-specific instructions
- Code patterns and examples
- EN 50128 compliance rules
- Tool configurations

**Example** (from `en50128-requirements` skill):
```yaml
---
name: en50128-requirements
description: Requirements engineering patterns and workflows for EN 50128 railway software compliance
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  language: C
  section: "7.2"
---
```

### 3. Agent Applies Skill Knowledge

When invoked, the agent:
1. Reads its command file
2. Identifies the skill to load
3. Applies skill patterns to the task
4. Follows EN 50128 constraints
5. Generates compliant outputs

## Skill Content Summary

### 1. en50128-requirements (REQ Agent)
**Purpose**: Requirements engineering per EN 50128 Section 7.2  
**Provides**:
- Requirements template: `REQ-[TYPE]-[ID]`
- SHALL/SHOULD/MAY keyword enforcement
- Traceability matrix templates
- C language considerations (data types, memory, timing)
- SIL level assignment rules

**Key Patterns**:
```markdown
REQ-FUNC-001: Train Door Control
SIL: 3
The system SHALL prevent door opening when train speed > 0 km/h.
Verification Method: Test
```

---

### 2. en50128-design (DES Agent)
**Purpose**: Software architecture and design per EN 50128 Section 7.3  
**Provides**:
- C module architecture (header/implementation separation)
- Cyclomatic complexity limits: 10 (SIL 3-4), 15 (SIL 2), 20 (SIL 0-1)
- Static memory allocation patterns
- State machine design patterns
- Defensive programming patterns

**Key Patterns**:
```c
// Module header pattern
#ifndef MODULE_H
#define MODULE_H
error_t module_init(void);
#endif

// Static allocation pattern
static uint8_t buffer[256];  // GOOD
uint8_t* buffer = malloc(256);  // FORBIDDEN (SIL 2+)
```

---

### 3. en50128-implementation (IMP Agent)
**Purpose**: C code implementation per EN 50128 Section 7.4  
**Provides**:
- MISRA C:2012 compliance patterns
- Fixed-width types (`uint8_t`, `uint16_t`, not `int`, `long`)
- Static allocation examples
- Error handling with `error_t` return types
- NULL pointer validation
- Boundary checking patterns

**Key Patterns**:
```c
// Defensive programming pattern
error_t process(const data_t* input, data_t* output) {
    // Validate pointers
    if ((input == NULL) || (output == NULL)) {
        return ERROR_NULL_POINTER;
    }
    
    // Validate ranges
    if (input->value > MAX_VALUE) {
        return ERROR_OUT_OF_RANGE;
    }
    
    // Process
    output->result = calculate(input->value);
    
    return SUCCESS;
}
```

---

### 4. en50128-testing (TST Agent)
**Purpose**: Software testing per EN 50128 Sections 7.4, 7.5  
**Provides**:
- Unity test framework patterns
- Coverage requirements by SIL:
  - SIL 2: 100% statement + branch
  - SIL 3-4: 100% statement + branch + MC/DC
- gcov/lcov integration commands
- Boundary value test patterns
- Fault injection techniques

**Key Patterns**:
```c
// Unity test pattern
void test_boundary_values(void) {
    // Arrange
    input_t input = {.speed = 0};
    output_t output;
    
    // Act
    error_t result = process(&input, &output);
    
    // Assert
    TEST_ASSERT_EQUAL(SUCCESS, result);
}
```

---

### 5. en50128-safety (SAF Agent)
**Purpose**: Safety analysis per EN 50128 Section 7.1  
**Provides**:
- FMEA (Failure Mode and Effects Analysis) templates
- FTA (Fault Tree Analysis) patterns
- Hazard analysis procedures
- C safety patterns: watchdog, redundancy, voting
- Common cause failure analysis
- Safety case structure

**Key Patterns**:
```c
// Watchdog pattern
void safety_task(void) {
    while(1) {
        perform_safety_function();
        kick_watchdog();
        if (check_system_health() != OK) {
            enter_safe_state();
        }
    }
}

// Redundancy pattern with voting
typedef struct {
    sensor_value_t channel_a;
    sensor_value_t channel_b;
    sensor_value_t channel_c;
} triple_redundant_t;

sensor_value_t vote_majority(triple_redundant_t* sensors);
```

---

### 6. en50128-verification (VER Agent)
**Purpose**: Software verification per EN 50128 Section 6.4  
**Provides**:
- PC-lint Plus configuration for MISRA C:2012
- Cppcheck with MISRA addon setup
- Lizard complexity analysis commands
- gcov/lcov coverage verification
- Static analysis automation scripts
- Verification report templates

**Key Tools**:
```bash
# Static analysis
pclp64 --misra3 source.c
cppcheck --addon=misra --enable=all source.c

# Complexity check
lizard --CCN 10 --warnings_only src/

# Coverage verification
lcov --summary coverage.info
```

---

### 7. en50128-validation (VAL Agent)
**Purpose**: Software validation per EN 50128 Section 7.6  
**Provides**:
- System test planning templates
- Operational scenario test patterns
- User acceptance test (UAT) templates
- Performance validation procedures
- Hardware-in-the-loop (HIL) test patterns
- Customer validation checklists

**Key Patterns**:
```c
// Operational scenario validation
void validate_emergency_braking(void) {
    set_speed(100);  // km/h
    trigger_emergency_brake();
    
    // Validate immediate response (< 100ms for SIL 3-4)
    wait_ms(100);
    VALIDATE(get_brake_status() == BRAKE_EMERGENCY);
    
    // Validate stopping distance
    wait_until_stopped();
    VALIDATE(get_distance() <= MAX_STOPPING_DISTANCE);
}
```

---

### 8. en50128-quality (QUA Agent)
**Purpose**: Quality assurance per EN 50128 Section 6.3  
**Provides**:
- SQAP (Software Quality Assurance Plan) template
- Code review checklists (MISRA C, defensive programming)
- Design review checklists
- Process audit checklists
- Quality metrics collection scripts
- Non-conformance management templates
- Quality gate definitions

**Key Activities**:
- Code reviews (mandatory for all code)
- MISRA C compliance checking
- Complexity verification
- Audit procedures
- Metrics: defect density, coverage %, complexity

---

### 9. en50128-documentation (Shared)
**Purpose**: Documentation generation for all agents  
**Provides**:
- SRS (Software Requirements Specification) template
- SAS (Software Architecture Specification) template
- SDS (Software Design Specification) template
- SQAP (Software Quality Assurance Plan) template
- SCMP (Software Configuration Management Plan) template
- Test plan templates
- Verification/Validation report templates

**Usage**: Available to all agents for generating compliant documentation

---

## How to Use Agents with Skills

### Example Workflow

```bash
# 1. Requirements Engineering
/req
# Agent loads en50128-requirements skill
# Creates SRS with proper structure
# Generates traceability matrices

# 2. Design
/des
# Agent loads en50128-design skill
# Creates modular C architecture
# Ensures complexity limits
# Uses static allocation only

# 3. Implementation
/imp
# Agent loads en50128-implementation skill
# Writes MISRA C compliant code
# Uses fixed-width types
# Implements defensive programming

# 4. Testing
/tst
# Agent loads en50128-testing skill
# Creates Unity tests
# Measures coverage with gcov
# Validates 100% coverage

# 5. Safety Analysis
/saf
# Agent loads en50128-safety skill
# Performs FMEA
# Identifies hazards
# Defines mitigations

# 6. Verification
/ver
# Agent loads en50128-verification skill
# Runs PC-lint, Cppcheck
# Checks complexity
# Collects evidence

# 7. Validation
/val
# Agent loads en50128-validation skill
# Performs system testing
# Validates scenarios
# Obtains acceptance

# 8. Quality Review
/qua
# Agent loads en50128-quality skill
# Performs code review
# Checks MISRA compliance
# Audits processes
```

## Verification Commands

### Check All Skills Exist
```bash
ls -la .opencode/skills/*/SKILL.md
```

Expected output:
```
en50128-design/SKILL.md
en50128-documentation/SKILL.md
en50128-implementation/SKILL.md
en50128-quality/SKILL.md
en50128-requirements/SKILL.md
en50128-safety/SKILL.md
en50128-testing/SKILL.md
en50128-validation/SKILL.md
en50128-verification/SKILL.md
```

### Check Skill Names Match
```bash
for skill in .opencode/skills/*/SKILL.md; do
    dirname "$skill" | xargs basename
done
```

Expected: Names match those in command files

### Verify Command Files Reference Skills
```bash
grep -h "Load skill:" .opencode/commands/*.md | sort
```

Expected output:
```
- Load skill: `en50128-design`
- Load skill: `en50128-implementation`
- Load skill: `en50128-quality`
- Load skill: `en50128-requirements`
- Load skill: `en50128-safety`
- Load skill: `en50128-testing`
- Load skill: `en50128-validation`
- Load skill: `en50128-verification`
```

## Key Benefits of Agent-Skill Architecture

1. **Modularity**: Skills are reusable and can be updated independently
2. **Expertise**: Each skill encapsulates domain-specific knowledge
3. **Compliance**: Skills enforce EN 50128 and MISRA C rules automatically
4. **Consistency**: All agents apply the same patterns and standards
5. **Extensibility**: New skills can be added without modifying agents
6. **Maintainability**: Single source of truth for patterns and rules

## Skill Loading Mechanism

### Automatic Loading (Recommended)
When an agent command is invoked via slash command (e.g., `/des`), the OpenCode system:
1. Reads the command file (`.opencode/commands/des.md`)
2. Parses the "Reference Skills" section
3. Automatically loads the specified skill (`en50128-design`)
4. Makes skill knowledge available to the agent

### Manual Loading (If Needed)
Users can explicitly request skill loading:
```
/des
Please load the en50128-design skill
```

### Multiple Skills
Agents can load multiple skills when needed:
- Primary skill (role-specific)
- Documentation skill (for reports)
- Additional skills for cross-functional work

Example:
```
/imp
Load en50128-implementation and en50128-safety skills
```

## Troubleshooting

### Skill Not Found
**Problem**: Agent cannot find skill  
**Solution**:
1. Check skill directory name matches exactly (lowercase, hyphens only)
2. Verify `SKILL.md` exists in skill directory
3. Check YAML frontmatter is valid
4. Ensure skill name in command file matches directory name

### Agent Doesn't Apply Skill Knowledge
**Problem**: Agent doesn't follow skill patterns  
**Solution**:
1. Verify "Reference Skills" section in command file
2. Check skill content is clear and actionable
3. Explicitly instruct agent to follow skill patterns

### Skill Loading Confirmation
To verify a skill is loaded, ask the agent:
```
/des
List the skills you have loaded
```

## Summary

✅ **8 Agent Commands** → Each mapped to a specific skill  
✅ **9 Skills** → Covering all EN 50128 roles + documentation  
✅ **100% Coverage** → Every agent has its skill  
✅ **C Language Focus** → MISRA C:2012, static allocation, defensive programming  
✅ **EN 50128 Compliant** → All skills enforce standard requirements  

The agent-skill architecture provides a robust foundation for EN 50128 compliant railway software development with OpenCode.

## References

- Main Documentation: `docs/Agent-Skill-Mapping.md`
- Agent Definitions: `AGENTS.md`
- Project Structure: `docs/Project-Structure.md`
- OpenCode Skills: https://opencode.ai/docs
- EN 50128:2011 - Railway Software Standard
- MISRA C:2012 - C Coding Standard
