# Agent-Skill Relationship Diagram

## Complete Agent-Skill Mapping

```
┌─────────────────────────────────────────────────────────────────────────┐
│                     EN 50128 Agent-Skill Architecture                    │
└─────────────────────────────────────────────────────────────────────────┘

                           ┌──────────────────┐
                           │   User Invokes   │
                           │  Slash Command   │
                           └────────┬─────────┘
                                    │
                 ┌──────────────────┼──────────────────┐
                 │                  │                  │
                 ▼                  ▼                  ▼
         ┌──────────────┐   ┌──────────────┐   ┌──────────────┐
         │     /req     │   │     /des     │   │     /imp     │
         │ Requirements │   │   Designer   │   │ Implementer  │
         │   Engineer   │   │              │   │              │
         └──────┬───────┘   └──────┬───────┘   └──────┬───────┘
                │                  │                  │
                │ loads            │ loads            │ loads
                │                  │                  │
                ▼                  ▼                  ▼
    ┌────────────────────┐ ┌────────────────┐ ┌─────────────────────┐
    │  en50128-          │ │  en50128-      │ │  en50128-           │
    │  requirements      │ │  design        │ │  implementation     │
    │                    │ │                │ │                     │
    │ • REQ templates    │ │ • C modules    │ │ • MISRA C rules     │
    │ • Traceability     │ │ • Complexity   │ │ • Fixed-width types │
    │ • SIL assignment   │ │ • Static mem   │ │ • Error handling    │
    └────────────────────┘ └────────────────┘ └─────────────────────┘


         ┌──────────────┐   ┌──────────────┐   ┌──────────────┐
         │     /tst     │   │     /saf     │   │     /ver     │
         │    Tester    │   │    Safety    │   │   Verifier   │
         │              │   │   Engineer   │   │              │
         └──────┬───────┘   └──────┬───────┘   └──────┬───────┘
                │                  │                  │
                │ loads            │ loads            │ loads
                │                  │                  │
                ▼                  ▼                  ▼
    ┌────────────────────┐ ┌────────────────┐ ┌─────────────────────┐
    │  en50128-          │ │  en50128-      │ │  en50128-           │
    │  testing           │ │  safety        │ │  verification       │
    │                    │ │                │ │                     │
    │ • Unity tests      │ │ • FMEA/FTA     │ │ • PC-lint           │
    │ • Coverage (gcov)  │ │ • Hazards      │ │ • Cppcheck          │
    │ • Boundary tests   │ │ • Mitigations  │ │ • Lizard            │
    └────────────────────┘ └────────────────┘ └─────────────────────┘


         ┌──────────────┐   ┌──────────────┐
         │     /val     │   │     /qua     │
         │  Validator   │   │   Quality    │
         │              │   │  Assurance   │
         └──────┬───────┘   └──────┬───────┘
                │                  │
                │ loads            │ loads
                │                  │
                ▼                  ▼
    ┌────────────────────┐ ┌────────────────────┐
    │  en50128-          │ │  en50128-          │
    │  validation        │ │  quality           │
    │                    │ │                    │
    │ • System tests     │ │ • Code reviews     │
    │ • UAT              │ │ • SQAP             │
    │ • Scenarios        │ │ • Audits           │
    └────────────────────┘ └────────────────────┘


                    ┌─────────────────────────┐
                    │  en50128-documentation  │
                    │      (Shared Skill)     │
                    │                         │
                    │ • SRS, SAS, SDS         │
                    │ • Test Plans            │
                    │ • Reports               │
                    └─────────────────────────┘
                               ▲
                               │
                    ┌──────────┴──────────┐
                    │  All agents can use │
                    │  for documentation  │
                    └─────────────────────┘
```

## Data Flow Through Agents and Skills

```
┌─────────────────────────────────────────────────────────────────────────┐
│                      EN 50128 Development Workflow                       │
└─────────────────────────────────────────────────────────────────────────┘

   User: "Create requirements for train door control"
      │
      ▼
   ┌──────────────────────────────────────────────────────────┐
   │  /req (Requirements Engineer)                            │
   │  Loads: en50128-requirements                             │
   │                                                          │
   │  Actions:                                                │
   │  • Applies REQ-[TYPE]-[ID] template                      │
   │  • Enforces SHALL/SHOULD/MAY keywords                    │
   │  • Assigns SIL levels                                    │
   │  • Creates traceability matrix                           │
   │                                                          │
   │  Output: SRS with REQ-FUNC-001, REQ-SAF-001, etc.        │
   └────────────────────────┬─────────────────────────────────┘
                            │
                            │ Requirements flow to Design
                            ▼
   ┌──────────────────────────────────────────────────────────┐
   │  /des (Designer)                                         │
   │  Loads: en50128-design                                   │
   │                                                          │
   │  Actions:                                                │
   │  • Creates C module architecture                         │
   │  • Ensures cyclomatic complexity ≤ 10 (SIL 3)            │
   │  • Designs with static allocation only                   │
   │  • Defines error_t return types                          │
   │  • Creates state machines                                │
   │                                                          │
   │  Output: SAS, SDS with C headers and module specs        │
   └────────────────────────┬─────────────────────────────────┘
                            │
                            │ Design flows to Implementation
                            ▼
   ┌──────────────────────────────────────────────────────────┐
   │  /imp (Implementer)                                      │
   │  Loads: en50128-implementation                           │
   │                                                          │
   │  Actions:                                                │
   │  • Writes MISRA C:2012 compliant code                    │
   │  • Uses uint8_t, uint16_t (not int, long)                │
   │  • Static allocation: static uint8_t buffer[256]         │
   │  • Validates all pointers: if (ptr == NULL) return ERROR │
   │  • Checks all returns: if (result != SUCCESS) handle()   │
   │                                                          │
   │  Output: .c/.h files with defensive programming          │
   └────────────────────────┬─────────────────────────────────┘
                            │
                            │ Code flows to Testing
                            ▼
   ┌──────────────────────────────────────────────────────────┐
   │  /tst (Tester)                                           │
   │  Loads: en50128-testing                                  │
   │                                                          │
   │  Actions:                                                │
   │  • Creates Unity tests                                   │
   │  • Measures coverage with gcov/lcov                      │
   │  • Validates 100% statement + branch + MC/DC (SIL 3)     │
   │  • Tests boundary values                                 │
   │  • Fault injection tests                                 │
   │                                                          │
   │  Output: Test suite with 100% coverage                   │
   └────────────────────────┬─────────────────────────────────┘
                            │
                            │ Tests flow to Verification
                            ▼
   ┌──────────────────────────────────────────────────────────┐
   │  /ver (Verifier)                                         │
   │  Loads: en50128-verification                             │
   │                                                          │
   │  Actions:                                                │
   │  • Runs PC-lint Plus (MISRA C:2012 checker)              │
   │  • Runs Cppcheck with MISRA addon                        │
   │  • Checks complexity with Lizard (CCN ≤ 10)              │
   │  • Verifies coverage meets SIL requirements              │
   │  • Collects verification evidence                        │
   │                                                          │
   │  Output: Verification report with evidence               │
   └────────────────────────┬─────────────────────────────────┘
                            │
                            │ Verified code flows to Validation
                            ▼
   ┌──────────────────────────────────────────────────────────┐
   │  /val (Validator)                                        │
   │  Loads: en50128-validation                               │
   │                                                          │
   │  Actions:                                                │
   │  • Performs system testing on target hardware            │
   │  • Validates operational scenarios                       │
   │  • User acceptance testing (UAT)                         │
   │  • Performance validation                                │
   │  • Customer approval                                     │
   │                                                          │
   │  Output: Validation report with acceptance               │
   └────────────────────────┬─────────────────────────────────┘
                            │
                            ▼
                      ┌─────────────┐
                      │   APPROVED  │
                      │ FOR RELEASE │
                      └─────────────┘


   ┌──────────────────────────────────────────────────────────┐
   │  /saf (Safety Engineer) - Throughout Process            │
   │  Loads: en50128-safety                                   │
   │                                                          │
   │  Actions:                                                │
   │  • Identifies hazards (HAZOP)                            │
   │  • Performs FMEA on design                               │
   │  • Creates Fault Tree Analysis (FTA)                     │
   │  • Reviews safety requirements                           │
   │  • Validates safety mitigations in code                  │
   │                                                          │
   │  Output: Safety case, FMEA/FTA reports                   │
   └──────────────────────────────────────────────────────────┘

   ┌──────────────────────────────────────────────────────────┐
   │  /qua (Quality Assurance) - Throughout Process          │
   │  Loads: en50128-quality                                  │
   │                                                          │
   │  Actions:                                                │
   │  • Reviews all code (MISRA C compliance)                 │
   │  • Audits processes                                      │
   │  • Collects quality metrics                              │
   │  • Manages non-conformances                              │
   │  • Enforces quality gates                                │
   │                                                          │
   │  Output: Code review records, audit reports, SQAP        │
   └──────────────────────────────────────────────────────────┘
```

## Skill Content Relationships

```
┌─────────────────────────────────────────────────────────────────────────┐
│                   Skills Enforce EN 50128 Constraints                    │
└─────────────────────────────────────────────────────────────────────────┘

                    ┌──────────────────────┐
                    │   C Language Focus   │
                    │   MISRA C:2012       │
                    └──────────┬───────────┘
                               │
              ┌────────────────┼────────────────┐
              │                │                │
              ▼                ▼                ▼
    ┌─────────────────┐ ┌──────────────┐ ┌─────────────────┐
    │ REQUIREMENTS    │ │    DESIGN    │ │ IMPLEMENTATION  │
    │                 │ │              │ │                 │
    │ • C constraints │ │ • Static mem │ │ • Fixed types   │
    │ • Data types    │ │ • Complexity │ │ • No malloc     │
    │ • Memory limits │ │ • Modules    │ │ • Defensive     │
    └─────────────────┘ └──────────────┘ └─────────────────┘
              │                │                │
              └────────────────┼────────────────┘
                               │
                               ▼
                    ┌──────────────────────┐
                    │  All Code Must Be:   │
                    │  • MISRA C compliant │
                    │  • Statically alloc  │
                    │  • Complexity ≤ lim  │
                    │  • 100% coverage     │
                    │  • Safety validated  │
                    └──────────────────────┘
```

## File Structure

```
EN50128/
├── .opencode/
│   ├── commands/                    # Agent command files
│   │   ├── req.md ──────────┐      # References skill
│   │   ├── des.md ──────────┤
│   │   ├── imp.md ──────────┤
│   │   ├── tst.md ──────────┤
│   │   ├── saf.md ──────────┤
│   │   ├── ver.md ──────────┤
│   │   ├── val.md ──────────┤
│   │   └── qua.md ──────────┤
│   │                         │
│   └── skills/               │     # Skill files
│       ├── en50128-requirements/SKILL.md ◄──┘
│       ├── en50128-design/SKILL.md ◄────────┘
│       ├── en50128-implementation/SKILL.md ◄─┘
│       ├── en50128-testing/SKILL.md ◄────────┘
│       ├── en50128-safety/SKILL.md ◄─────────┘
│       ├── en50128-verification/SKILL.md ◄───┘
│       ├── en50128-validation/SKILL.md ◄─────┘
│       ├── en50128-quality/SKILL.md ◄────────┘
│       └── en50128-documentation/SKILL.md (shared)
│
├── docs/
│   ├── Agent-Skill-Mapping.md           # Detailed mapping
│   └── Agent-Skill-Linking-Summary.md   # This summary
│
├── src/                                  # C source code
├── tools/                                # Static analysis tools
└── AGENTS.md                             # Agent definitions
```

## Quick Reference

### Invoke Agent with Skill

```bash
# Pattern: /[agent] → Loads skill → Applies patterns

/req    # → en50128-requirements    → REQ templates, traceability
/des    # → en50128-design          → C modules, complexity limits
/imp    # → en50128-implementation  → MISRA C, defensive programming
/tst    # → en50128-testing         → Unity tests, coverage
/saf    # → en50128-safety          → FMEA, FTA, hazards
/ver    # → en50128-verification    → PC-lint, Cppcheck, Lizard
/val    # → en50128-validation      → System tests, UAT
/qua    # → en50128-quality         → Reviews, audits, metrics
```

### Check Skills

```bash
# List all skills
ls .opencode/skills/*/SKILL.md

# Verify skill names
grep "^name:" .opencode/skills/*/SKILL.md

# Check command references
grep "Load skill:" .opencode/commands/*.md
```

## Summary

**✅ Complete Agent-Skill Mapping**
- 8 agents → 8 primary skills + 1 shared documentation skill
- Every agent has explicit skill reference
- All skills provide EN 50128 compliant patterns
- C language and MISRA C:2012 enforced throughout

**✅ EN 50128 Compliance**
- Requirements → Design → Implementation → Testing → Verification → Validation
- Safety and Quality oversight throughout
- Traceability maintained at every step
- SIL-appropriate rigor applied

**✅ Development Language**
- Primary: C (MISRA C:2012 for SIL 2+)
- Support: Python (tooling only, not safety-critical)
- Static allocation mandatory (SIL 2+)
- Defensive programming enforced

The agent-skill architecture provides a complete, compliant framework for EN 50128 railway software development using OpenCode.
