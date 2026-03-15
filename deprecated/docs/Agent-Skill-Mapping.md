# Agent-Skill Mapping for EN 50128

This document defines the explicit relationship between agent command files and their associated skills.

## Overview

Each EN 50128 agent is equipped with domain-specific skills that provide:
- Design patterns and templates
- Code examples and best practices
- EN 50128 compliance rules
- Tool integration instructions
- Domain-specific knowledge

## Agent to Skill Mapping

| Agent | Command File | Skill Name | Skill Directory | Status |
|-------|-------------|------------|-----------------|---------|
| **Requirements Engineer** | `.opencode/commands/req.md` | `en50128-requirements` | `.opencode/skills/en50128-requirements/` | ✅ Active |
| **Designer** | `.opencode/commands/des.md` | `en50128-design` | `.opencode/skills/en50128-design/` | ✅ Active |
| **Implementer** | `.opencode/commands/imp.md` | `en50128-implementation` | `.opencode/skills/en50128-implementation/` | ✅ Active |
| **Tester** | `.opencode/commands/tst.md` | `en50128-testing` | `.opencode/skills/en50128-testing/` | ✅ Active |
| **Safety Engineer** | `.opencode/commands/saf.md` | `en50128-safety` | `.opencode/skills/en50128-safety/` | ✅ Active |
| **Verifier** | `.opencode/commands/ver.md` | `en50128-verification` | `.opencode/skills/en50128-verification/` | ✅ Active |
| **Validator** | `.opencode/commands/val.md` | `en50128-validation` | `.opencode/skills/en50128-validation/` | ✅ Active |
| **Quality Assurance** | `.opencode/commands/qua.md` | `en50128-quality` | `.opencode/skills/en50128-quality/` | ✅ Active |

## Skill Loading Mechanism

### In Command Files

Each command file includes a "Reference Skills" section that instructs the agent to load its associated skill:

```markdown
## Reference Skills
- Load skill: `en50128-[name]`
```

### Skill File Structure

Each skill follows the OpenCode skill format:

```
.opencode/skills/en50128-[name]/
└── SKILL.md
```

The `SKILL.md` file contains:
- YAML frontmatter with metadata
- Domain-specific instructions
- Code patterns and examples
- Tool configurations
- Compliance rules

### Example: Designer Agent with Design Skill

**Command File** (`.opencode/commands/des.md`):
```markdown
# Designer Agent (DES)

You are a Software Designer specialized in EN 50128...

## Reference Skills
- Load skill: `en50128-design`
```

**Skill File** (`.opencode/skills/en50128-design/SKILL.md`):
```yaml
---
name: en50128-design
description: EN 50128 software architecture and design patterns for C
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  language: C
  section: "7.3"
---

# EN 50128 Design Skill

[Design patterns, examples, templates...]
```

## Skill Content Summary

### 1. en50128-requirements
**For**: Requirements Engineer (REQ)
**Provides**:
- Requirements template structure (REQ-[TYPE]-[ID])
- SHALL/SHOULD/MAY keyword enforcement
- Traceability matrix templates
- C language constraint considerations
- Verification method mapping

### 2. en50128-design
**For**: Designer (DES)
**Provides**:
- C module architecture patterns (header/implementation)
- Cyclomatic complexity limits by SIL (10/15/20)
- Static memory allocation patterns
- State machine design patterns
- Defensive programming patterns
- Interface design templates

### 3. en50128-implementation
**For**: Implementer (IMP)
**Provides**:
- MISRA C:2012 rule patterns
- Fixed-width type usage (`uint8_t`, `uint16_t`, etc.)
- Static allocation examples
- Error handling patterns (`error_t` return types)
- Safe arithmetic operations
- NULL pointer checking patterns
- Boundary validation examples

### 4. en50128-testing
**For**: Tester (TST)
**Provides**:
- Unity test framework patterns
- Coverage requirements by SIL (statement, branch, MC/DC)
- Test case template (Arrange-Act-Assert)
- gcov/lcov integration commands
- Boundary value test patterns
- Fault injection techniques

### 5. en50128-safety
**For**: Safety Engineer (SAF)
**Provides**:
- Hazard analysis templates (HAZOP, FMEA)
- FTA (Fault Tree Analysis) patterns
- Safety requirement templates
- C safety patterns (watchdog, redundancy, voting)
- Common cause failure analysis
- Safety case structure

### 6. en50128-verification
**For**: Verifier (VER)
**Provides**:
- Static analysis tool configurations (PC-lint, Cppcheck)
- Coverage verification procedures
- MISRA C compliance checking
- Complexity analysis (Lizard)
- Verification report templates
- Evidence collection checklists

### 7. en50128-validation
**For**: Validator (VAL)
**Provides**:
- System test planning templates
- Operational scenario templates
- Acceptance test procedures
- Target environment test setup
- Customer validation checklists
- Validation report structure

### 8. en50128-quality
**For**: Quality Assurance (QUA)
**Provides**:
- Code review checklists
- SQAP (Software Quality Assurance Plan) template
- Quality gate definitions by SIL
- Audit procedures
- Metrics collection templates
- Non-conformance tracking

## Documentation Skill (Shared)

### en50128-documentation
**For**: All agents
**Provides**:
- SRS (Software Requirements Specification) template
- SAS (Software Architecture Specification) template
- SDS (Software Design Specification) template
- SQAP (Software Quality Assurance Plan) template
- SCMP (Software Configuration Management Plan) template
- Document review checklists

This skill is available to all agents for generating documentation artifacts.

## How Agents Use Skills

### Automatic Loading
When an agent is invoked via slash command (e.g., `/des`), it should:
1. Read its command file (`.opencode/commands/des.md`)
2. Identify the skill to load from "Reference Skills" section
3. Load the skill using the `skill` tool: `skill(name="en50128-design")`
4. Apply skill patterns and knowledge to the task

### Manual Loading
Users or agents can explicitly load skills:
```
/des
Load the en50128-design skill
[Agent loads skill and confirms]
```

### Multiple Skills
Agents may load multiple skills when needed:
- Primary skill (role-specific)
- Documentation skill (for report generation)
- Additional skills for cross-functional work

## Skill Dependencies

```
en50128-requirements
    ↓ (requirements flow to design)
en50128-design
    ↓ (design flows to implementation)
en50128-implementation ←→ en50128-testing (TDD cycle)
    ↓ (code to verification)
en50128-verification
    ↓ (verified code to validation)
en50128-validation

en50128-safety (influences all stages)
en50128-quality (oversees all stages)
en50128-documentation (used by all agents)
```

## Skill Maintenance

### Adding New Skills
1. Create skill directory: `.opencode/skills/en50128-[name]/`
2. Create `SKILL.md` with proper YAML frontmatter
3. Update agent command file to reference the skill
4. Update this mapping document

### Updating Skills
1. Edit the `SKILL.md` file directly
2. Test with corresponding agent
3. Document changes in skill changelog

### Skill Versioning
Skills are versioned with the project. Major changes:
- Add version field to YAML frontmatter
- Track compatibility with EN 50128 standard version
- Maintain changelog in skill file

## Example Workflow: Using Agents with Skills

```bash
# 1. Requirements phase
/req
# REQ agent loads en50128-requirements skill
# Creates SRS with proper requirement structure
# Generates traceability matrices

# 2. Design phase
/des
# DES agent loads en50128-design skill
# Creates modular C architecture
# Ensures complexity limits
# Generates SAS/SDS documents

# 3. Safety analysis
/saf
# SAF agent loads en50128-safety skill
# Performs FMEA on C code
# Identifies hazards
# Defines safety requirements

# 4. Implementation
/imp
# IMP agent loads en50128-implementation skill
# Writes MISRA C compliant code
# Uses static allocation only
# Implements defensive programming

# 5. Testing
/tst
# TST agent loads en50128-testing skill
# Creates Unity tests
# Measures coverage with gcov
# Validates 100% coverage for SIL

# 6. Verification
/ver
# VER agent loads en50128-verification skill
# Runs static analysis (PC-lint, Cppcheck)
# Checks complexity with Lizard
# Collects evidence

# 7. Validation
/val
# VAL agent loads en50128-validation skill
# Performs system testing
# Validates operational scenarios
# Obtains customer acceptance

# 8. Quality review (throughout)
/qua
# QUA agent loads en50128-quality skill
# Performs code reviews
# Checks MISRA compliance
# Audits processes
```

## Verification of Skill Loading

To verify that skills are properly loaded:

1. **Check skill exists**:
   ```bash
   ls -la .opencode/skills/en50128-[name]/SKILL.md
   ```

2. **Validate YAML frontmatter**:
   ```bash
   head -20 .opencode/skills/en50128-[name]/SKILL.md
   ```

3. **Test agent invocation**:
   ```
   /[agent-command]
   List available skills
   ```

4. **Verify skill loading in agent**:
   Check that agent applies patterns from the skill in its responses

## Troubleshooting

### Skill Not Found
- Check skill directory name matches exactly (lowercase, hyphens only)
- Verify `SKILL.md` exists in skill directory
- Check YAML frontmatter is valid

### Agent Doesn't Apply Skill Knowledge
- Verify "Reference Skills" section in command file
- Check that skill name in command file matches directory name
- Ensure skill content is clear and actionable

### Multiple Skills Conflict
- Skills should be complementary, not conflicting
- Document skill precedence in command file
- Use explicit instructions in skill to resolve conflicts

## Future Enhancements

1. **Skill Composition**: Allow agents to compose multiple skills dynamically
2. **Skill Libraries**: Create reusable skill modules
3. **Skill Testing**: Add validation tests for skill content
4. **Skill Analytics**: Track which skills are most effective
5. **Custom Skills**: Allow users to add project-specific skills

## References

- OpenCode Skill Documentation: [OpenCode docs](https://opencode.ai/docs)
- EN 50128:2011 - Railway Software Standard
- MISRA C:2012 - C Coding Standard
- Project structure: `docs/Project-Structure.md`
- Agent definitions: `AGENTS.md`
