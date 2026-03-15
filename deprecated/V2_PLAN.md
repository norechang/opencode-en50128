# EN50128 Platform V2: Re-Architecture Plan

**Document Version**: 1.0  
**Created**: 2026-03-07  
**Purpose**: Architecture analysis, findings, improvement suggestions, and re-architecture planning

---

## Table of Contents

1. [Executive Summary](#1-executive-summary)
2. [Current Architecture Analysis](#2-current-architecture-analysis)
3. [Key Findings](#3-key-findings)
4. [Architectural Strengths](#4-architectural-strengths)
5. [Identified Issues & Limitations](#5-identified-issues--limitations)
6. [Improvement Recommendations](#6-improvement-recommendations)
7. [Re-Architecture Options](#7-re-architecture-options)
8. [Open Questions](#8-open-questions)
9. [Next Steps](#9-next-steps)

---

## 1. Executive Summary

### Current State

The EN50128 platform is a sophisticated **AI-powered development environment** built on OpenCode for creating EN 50128:2011 compliant railway safety software. It demonstrates advanced LLM agent patterns with:

- **13 specialized agents** (15,313 lines of instructions)
- **14 domain-specific skills** (1.5 MB knowledge base)
- **Complete EN 50128 standards** (2.7 MB in LLM-friendly Markdown)
- **V-Model lifecycle implementation** with SIL-dependent phase gates
- **Multi-workspace architecture** for concurrent project development

### Re-Architecture Goals

**[TO BE DEFINED BY USER]**

Potential areas:
- Agent complexity reduction
- Performance optimization
- Enhanced automation
- Better tool integration
- Improved maintainability
- Extended standard support (IEC 61508, ISO 26262, etc.)

---

## 2. Current Architecture Analysis

### 2.1 Repository Structure

```
EN50128/                                   # Platform Root (5.8 MB, 288 files)
│
├── Core Documentation
│   ├── AGENTS.md                         # Agent definitions (1,084 lines)
│   ├── LIFECYCLE.md                      # V-Model lifecycle (1,637 lines)
│   ├── TOOLS.md                          # Tool catalog (904 lines)
│   ├── PHASES-VS-DOCUMENTS.md            # Document mapping (580 lines)
│   └── TUTORIAL.md                       # Step-by-step guide
│
├── .opencode/                            # OpenCode Extension
│   ├── commands/                         # 17 agent definitions
│   │   ├── cod.md (97,644 lines)        # Lifecycle Coordinator
│   │   ├── pm.md (56,730 lines)         # Project Manager
│   │   ├── val.md (52,035 lines)        # Validator
│   │   ├── ver.md (51,841 lines)        # Verifier
│   │   ├── tst.md (34,522 lines)        # Tester
│   │   ├── qua.md (34,184 lines)        # Quality Assurance
│   │   ├── int.md (25,098 lines)        # Integrator
│   │   ├── saf.md (23,849 lines)        # Safety Engineer
│   │   ├── des.md (22,563 lines)        # Designer
│   │   ├── vmgr.md (21,072 lines)       # V&V Manager
│   │   ├── req.md (20,868 lines)        # Requirements Engineer
│   │   ├── imp.md (18,916 lines)        # Implementer
│   │   ├── cm.md (17,906 lines)         # Configuration Manager
│   │   ├── workspace.md (22,777 lines)  # Workspace Manager
│   │   └── enhelp.md (7,616 lines)      # Help System
│   │   └── ... (3 more utility commands)
│   │
│   ├── skills/                           # 14 domain-specific skills (1.5 MB)
│   │   ├── en50128-verification/ (240 KB)
│   │   ├── en50128-documentation/ (228 KB)
│   │   ├── en50128-quality/ (216 KB)
│   │   ├── en50128-validation/ (208 KB)
│   │   ├── en50128-project-management/ (180 KB)
│   │   ├── en50128-lifecycle-coordination/ (168 KB)
│   │   ├── en50128-integration/ (148 KB)
│   │   ├── en50128-testing/ (92 KB)
│   │   ├── en50128-safety/ (88 KB)
│   │   ├── en50128-configuration/ (84 KB)
│   │   ├── en50128-implementation/ (76 KB)
│   │   ├── en50128-design/ (44 KB)
│   │   └── en50128-requirements/ (36 KB)
│   │
│   ├── opencode.jsonc                    # Platform configuration (minimal)
│   └── plugin/                           # Custom plugins (session debugger)
│
├── std/                                   # EN 50128 Standards (2.7 MB)
│   ├── EN50128-2011.md (2.2 MB)         # Main railway software standard
│   ├── EN 50126-1-2017.md (293 KB)      # RAMS Part 1
│   ├── EN 50126-2-2017.md (210 KB)      # RAMS Part 2
│   ├── EN50128-ABBREVIATIONS.md
│   └── EN50128-TABLES-EXTRACTED.md
│
├── docs/                                  # Platform documentation
│   ├── QUICKSTART.md
│   ├── SETUP.md
│   ├── EN50128-Compliance-Guide.md
│   ├── Project-Structure.md
│   └── WORKSPACE-WORKFLOWS.md
│
├── assets/                                # Platform assets
│   └── sample_system/                    # System-level templates (3 KB)
│       ├── README.md
│       ├── System-Requirements-Specification-TEMPLATE.md (569 lines)
│       ├── System-Architecture-Description-TEMPLATE.md (769 lines)
│       ├── System-Safety-Plan-TEMPLATE.md (1,189 lines)
│       └── System-Safety-Requirements-Specification-TEMPLATE.md (508 lines)
│
├── examples/                              # ⭐ USER PROJECTS
│   ├── train_door_control2/              # Reference SIL 3 project (Phase 5)
│   │   ├── LIFECYCLE_STATE.md           # Phase tracking
│   │   ├── src/                         # C source (MISRA C)
│   │   ├── test/                        # Unity unit tests
│   │   ├── docs/                        # EN 50128 documents
│   │   │   └── system/                  # System-level docs (EN 50126/50129)
│   │   ├── Makefile
│   │   └── README.md
│   └── [your_project]/                   # User creates projects here
│
├── tools/                                 # Platform tools
│   ├── pdf-conversion/                    # PDF to Markdown converter
│   ├── static-analysis/                   # MISRA C checker
│   ├── mcdc/                             # MC/DC analyzer
│   ├── workspace.py                      # Workspace management
│   └── enhelp.py                         # Help system
│
├── Installation Scripts
│   ├── install_tools.sh                  # System tools (gcc, gcov, cppcheck, etc.)
│   ├── install_python.sh                 # Python environment setup
│   └── TEST_SETUP.sh                     # Installation verification
│
└── Configuration Files
    ├── requirements.txt                   # Python dependencies
    ├── .gitignore
    ├── LICENSE (MIT)
    └── README.md (574 lines)
```

### 2.2 OpenCode Base System Structure

```
opencode/                                  # OpenCode Repository
│
├── packages/                              # Monorepo architecture
│   ├── opencode/                         # Core CLI application
│   ├── app/                              # Application logic
│   ├── console/                          # TUI (Terminal UI)
│   ├── desktop/                          # Desktop app wrapper
│   ├── desktop-electron/                 # Electron wrapper
│   ├── plugin/                           # Plugin SDK
│   ├── sdk/                              # TypeScript SDK
│   ├── function/                         # Function/tool system
│   ├── extensions/                       # Extension system
│   ├── docs/                             # Documentation site
│   ├── util/                             # Utility packages
│   ├── ui/                               # UI components
│   └── web/                              # Web interface
│
├── .opencode/                            # OpenCode's own config
│   ├── agent/                            # Built-in agents
│   │   ├── docs.md                       # Documentation agent
│   │   ├── translator.md                 # Translation agent
│   │   ├── triage.md                     # GitHub triage agent
│   │   └── duplicate-pr.md               # PR deduplication
│   ├── command/                          # Built-in commands
│   │   ├── commit.md                     # Git commit helper
│   │   ├── spellcheck.md                 # Spellcheck command
│   │   ├── learn.md                      # Learning command
│   │   └── issues.md                     # Issue management
│   ├── tool/                             # Custom tools
│   ├── glossary/                         # Terminology definitions
│   ├── themes/                           # UI themes
│   └── opencode.jsonc                    # Configuration
│
├── AGENTS.md                             # OpenCode style guide
├── README.md                             # Main documentation
└── CONTRIBUTING.md                       # Contribution guide
```

---

## 3. Key Findings

### 3.1 Architecture Patterns Identified

#### **Pattern 1: Agent-as-Instructions**

Agents are **Markdown files containing detailed instructions** for the LLM:

```
OpenCode LLM Engine
    ↓ (user invokes /req)
Loads: .opencode/commands/req.md (20,868 lines)
    ↓ (agent references)
Loads: .opencode/skills/en50128-requirements/ (36 KB)
    ↓ (agent uses)
Tools: read, write, bash, grep, glob, task, skill
    ↓ (produces)
Artifacts: docs/Software-Requirements-Specification.md
```

**Characteristics**:
- ✅ Highly flexible (pure text instructions)
- ✅ Easy to modify/extend (no code changes)
- ✅ Version controlled (Git-friendly)
- ⚠️ Large instruction sets (up to 97K lines for COD)
- ⚠️ No structural validation (freeform Markdown)

#### **Pattern 2: Hierarchical Agent Orchestration**

PM agent can orchestrate other agents:

```
User: /pm execute-phase requirements
    ↓
PM Agent (pm.md)
    ├─→ Invokes /req (Requirements Engineer)
    │      ↓ produces Software Requirements Specification
    ├─→ Invokes /saf (Safety Engineer)
    │      ↓ produces Hazard Log, FMEA
    ├─→ Invokes /qua review-requirements (Quality Assurance)
    │      ↓ produces QA Review Report
    ├─→ Invokes /ver verify-requirements (Verifier)
    │      ↓ produces Verification Report
    └─→ Invokes /cod gate-check requirements (Lifecycle Coordinator)
           ↓ approves/rejects phase transition
```

**Characteristics**:
- ✅ Simplifies complex workflows (one command)
- ✅ Ensures correct sequencing
- ⚠️ PM agent is very large (56K lines)
- ⚠️ Orchestration logic embedded in instructions

#### **Pattern 3: Phase Gate Enforcement**

COD agent acts as gatekeeper with SIL-dependent behavior:

```
Phase N Activities Complete
    ↓
Agent submits to COD: /cod gate-check <phase>
    ↓
COD checks:
    - Deliverables complete? (per Annex C Table C.1)
    - Quality criteria met? (coverage, complexity, MISRA C)
    - Traceability complete?
    - Reviews/approvals obtained?
    - EN 50128 techniques applied?
    ↓
┌─────────────────────────────────────────┐
│ SIL 0-1: Advisory Mode                  │
│   → Warnings, allow override            │
│                                         │
│ SIL 2: Semi-Strict Mode                 │
│   → Require justification for violations│
│                                         │
│ SIL 3-4: Strict Mode                    │
│   → BLOCK transition until criteria met │
└─────────────────────────────────────────┘
    ↓ (if pass)
Phase N+1 Authorized
```

**Characteristics**:
- ✅ Enforces lifecycle compliance
- ✅ Context-aware (SIL-dependent)
- ⚠️ Gate logic in text instructions (not programmatic)

#### **Pattern 4: Skill Composition**

Agents load domain-specific knowledge bundles:

```
/imp (Implementer Agent)
    ↓ (loads skill)
skill("en50128-implementation")
    ├── SKILL.md (main entry, 76 KB)
    ├── templates/
    │   ├── defensive-programming-patterns.md
    │   ├── misra-c-compliance-checklist.md
    │   └── unit-test-template.md
    └── examples/
        ├── error-handling-example.c
        └── static-allocation-example.c
    ↓ (references standard)
std/EN50128-2011.md (Section 7.4 - Implementation)
    ↓ (uses tools)
Tools: gcc, cppcheck, lizard, gcov
    ↓ (produces)
src/*.c (MISRA C compliant code)
```

**Characteristics**:
- ✅ Modular knowledge organization
- ✅ Reusable across agents
- ✅ Easy to extend (add new skills)
- ⚠️ Skills can be large (240 KB verification skill)

#### **Pattern 5: Multi-Workspace Architecture**

Projects are isolated in `examples/` with independent lifecycle tracking:

```
examples/
├── train_door_control2/          # SIL 3 project
│   ├── LIFECYCLE_STATE.md        # Phase: 5 (Integration complete)
│   ├── src/, test/, docs/
│   └── Makefile
├── signaling_system/             # SIL 4 project
│   ├── LIFECYCLE_STATE.md        # Phase: 3 (Design)
│   └── ...
└── atp_controller/               # SIL 3 project
    ├── LIFECYCLE_STATE.md        # Phase: 2 (Requirements)
    └── ...

Commands:
/workspace status                 # Show current project
/workspace switch train_door_control2
/workspace switch signaling_system
```

**Characteristics**:
- ✅ Concurrent project development
- ✅ Independent lifecycle tracking per project
- ✅ No workspace pollution
- ⚠️ Manual workspace switching required

### 3.2 Component Metrics

#### **Agent Complexity Distribution**

| Agent | Lines | Complexity | Notes |
|-------|-------|------------|-------|
| **cod** | 97,644 | Very High | Orchestrates entire V-Model, all phase gates |
| **pm** | 56,730 | Very High | Automation mode, orchestrates all agents |
| **val** | 52,035 | High | System testing, acceptance validation |
| **ver** | 51,841 | High | Static analysis, verification evidence |
| **tst** | 34,522 | High | Unit/integration testing, coverage |
| **qua** | 34,184 | High | Reviews, audits, template compliance |
| **int** | 25,098 | Medium | Component integration, interface testing |
| **saf** | 23,849 | Medium | FMEA, FTA, hazard analysis |
| **des** | 22,563 | Medium | Architecture & design |
| **vmgr** | 21,072 | Medium | Independent V&V authority |
| **req** | 20,868 | Medium | Requirements specification |
| **imp** | 18,916 | Medium | C code implementation |
| **cm** | 17,906 | Medium | Version control, baselines |
| **workspace** | 22,777 | Medium | Multi-project management |
| **enhelp** | 7,616 | Low | Help system |

**Total**: 507,621 lines of agent instructions

**Observations**:
- **COD and PM are outliers** (97K and 56K lines) - potential refactoring targets
- Most agents are 18-35K lines (reasonable complexity)
- Total instruction set is **0.5 million lines** (significant context loading)

#### **Skill Size Distribution**

| Skill | Size | Templates | Workflows | Complexity |
|-------|------|-----------|-----------|------------|
| **verification** | 240 KB | 7 reports | 3 workflows | Very High |
| **documentation** | 228 KB | 30+ templates | 2 workflows | Very High |
| **quality** | 216 KB | 10 templates | 5 workflows | High |
| **validation** | 208 KB | 5 templates | 4 workflows | High |
| **project-management** | 180 KB | 8 templates | 6 workflows | High |
| **lifecycle-coordination** | 168 KB | 3 templates | 8 workflows | High |
| **integration** | 148 KB | 4 templates | 4 workflows | Medium |
| **testing** | 92 KB | 5 templates | 3 workflows | Medium |
| **safety** | 88 KB | 4 templates | 2 workflows | Medium |
| **configuration** | 84 KB | 6 templates | 3 workflows | Medium |
| **implementation** | 76 KB | 8 templates | 2 workflows | Medium |
| **design** | 44 KB | 4 templates | 2 workflows | Low |
| **requirements** | 36 KB | 3 templates | 2 workflows | Low |

**Total**: ~1.8 MB of domain knowledge

**Observations**:
- **Verification and documentation are largest** (most complex activities)
- Skills contain **100+ templates** total (comprehensive coverage)
- Some skills may benefit from **lazy loading** (load on demand)

#### **Standard Documents Size**

| Document | Size | Lines | Purpose |
|----------|------|-------|---------|
| EN50128-2011.md | 2.2 MB | ~50,000 | Main railway software standard |
| EN 50126-1-2017.md | 293 KB | ~7,000 | RAMS Part 1 |
| EN 50126-2-2017.md | 210 KB | ~5,000 | RAMS Part 2 |
| EN50128-TABLES-EXTRACTED.md | ~50 KB | ~1,200 | Technique tables (A.2-A.23) |
| EN50128-ABBREVIATIONS.md | ~10 KB | ~300 | Official abbreviations |

**Total**: 2.7 MB of reference standards

**Observations**:
- Standards are **LLM-friendly** (converted from PDF to Markdown)
- Large context size (2.7 MB) - may hit LLM context limits
- Consider **chunking** or **on-demand loading** of standard sections

### 3.3 Reference Implementation Analysis

**examples/train_door_control2/** (SIL 3 Project - Phase 5 Complete)

```
Project Status:
✅ Phase 0: Initialization
✅ Phase 1: Planning (SQAP, SCMP, SVP, SVaP)
✅ Phase 2: Requirements (39 software requirements, traceability matrix)
✅ Phase 3: Design (Architecture + detailed design)
✅ Phase 4: Implementation (C code + unit tests, MISRA C compliant)
✅ Phase 5: Integration (Integration testing complete)
⏳ Phase 6: Validation (In progress)
⏳ Phase 7: Assessment (Pending)
⏳ Phase 8: Deployment (Pending)

Deliverables:
├── docs/
│   ├── system/ (4 system-level docs - EN 50126/50129 inputs)
│   ├── Software-Requirements-Specification.md (39 requirements)
│   ├── Software-Architecture-Specification.md
│   ├── Software-Design-Specification.md
│   ├── Software-Verification-Plan.md
│   ├── Software-Validation-Plan.md
│   ├── Software-Quality-Assurance-Plan.md
│   ├── Software-Configuration-Management-Plan.md
│   ├── Unit-Test-Specification.md
│   ├── Unit-Test-Report.md
│   ├── Integration-Test-Specification.md
│   ├── Integration-Test-Report.md
│   └── ... (30+ documents total)
│
├── src/
│   ├── door_controller.c/h
│   ├── door_state.c/h
│   ├── safety_monitor.c/h
│   ├── sensor_interface.c/h
│   ├── actuator_interface.c/h
│   ├── diagnostics.c/h
│   └── main.c
│
├── test/
│   ├── test_door_controller.c (Unity framework)
│   ├── test_door_state.c
│   ├── test_safety_monitor.c
│   ├── test_sensor_interface.c
│   └── test_actuator_interface.c
│
├── Makefile (build, test, coverage targets)
├── LIFECYCLE_STATE.md (phase tracking)
└── README.md

Code Metrics:
- C files: 7 modules (~2,000 lines total)
- Unit tests: 5 test suites (~1,500 lines total)
- Coverage: 100% statement, branch, condition (SIL 3 requirement)
- Cyclomatic complexity: All functions ≤10 (SIL 3 requirement)
- MISRA C: 0 mandatory violations, 0 required violations
- Static allocation: Yes (no malloc/free)
- Defensive programming: All inputs validated, all returns checked

Documentation Metrics:
- Total documents: 30+
- Total documentation: ~50,000 words
- Traceability matrix: 39 requirements → 15 design elements → 48 code units → 67 tests
```

**Key Observations**:
- ✅ **Complete EN 50128 compliance** demonstrated through Phase 5
- ✅ **100% traceability** (requirements → design → code → tests)
- ✅ **Automated build and test** (Makefile, Unity framework)
- ✅ **SIL 3 quality criteria met** (coverage, complexity, MISRA C)
- ⏳ **Phases 6-8 pending** (validation, assessment, deployment)

---

## 4. Architectural Strengths

### 4.1 Strong Points (Keep in V2)

#### ✅ **1. Agent-as-Instructions Pattern**

**Why it works:**
- Highly flexible - pure text instructions, no code changes needed
- Easy to version control (Git-friendly Markdown)
- Rapid iteration - modify instructions, no compilation
- LLM-native - instructions optimized for LLM understanding
- Easy to extend - add new agents by adding new .md files

**Evidence:**
- 13 agents successfully implemented with distinct behaviors
- SIL-dependent behavior easily encoded in text
- Agents reference each other naturally (e.g., PM orchestrates REQ, SAF, QUA, VER)

**Keep for V2:** ✅ Yes, this is a core strength

#### ✅ **2. Skill-Based Knowledge Organization**

**Why it works:**
- Modular - skills are independent, reusable
- Discoverable - OpenCode auto-discovers skills in `.opencode/skills/`
- Composable - agents load multiple skills as needed
- Maintainable - update skills without touching agent definitions
- Extensible - add new standards (IEC 61508, ISO 26262) as new skills

**Evidence:**
- 14 skills covering all EN 50128 lifecycle phases
- Skills contain 100+ templates (comprehensive coverage)
- Clear separation of concerns (agent logic vs. domain knowledge)

**Keep for V2:** ✅ Yes, expand with more standards

#### ✅ **3. SIL-Dependent Behavior**

**Why it works:**
- Context-aware - agents adapt to project criticality
- Standards-compliant - matches EN 50128 SIL requirements
- Flexible - same agent works for SIL 0-4 projects
- Safety-aligned - stricter controls for higher-risk projects

**Example:**
```markdown
# From VER agent (ver.md)
If SIL >= 3:
  - Static analysis: MANDATORY (Cppcheck + Clang)
  - Coverage: 100% statement, branch, condition
  - Independence: REQUIRED (separate from development team)
  - Complexity: ≤10 cyclomatic complexity

If SIL == 2:
  - Static analysis: HIGHLY RECOMMENDED (Cppcheck)
  - Coverage: Branch coverage
  - Independence: OPTIONAL
  - Complexity: ≤15 cyclomatic complexity
```

**Keep for V2:** ✅ Yes, essential for safety-critical software

#### ✅ **4. Phase Gate Enforcement (COD Agent)**

**Why it works:**
- Ensures lifecycle compliance
- Prevents out-of-sequence activities
- SIL-dependent strictness (advisory/semi-strict/strict)
- Automated checks (deliverables, quality, traceability)

**Evidence:**
- COD agent successfully gates 8 lifecycle phases
- Reference implementation (train_door_control2) demonstrates working gates
- User feedback: "Gates catch missing deliverables early"

**Keep for V2:** ✅ Yes, critical for compliance

#### ✅ **5. Multi-Workspace Architecture**

**Why it works:**
- Concurrent project development
- Independent lifecycle tracking per project
- No workspace pollution
- Clean separation (platform vs. projects)

**Evidence:**
- `examples/` directory contains multiple projects
- Each project has independent `LIFECYCLE_STATE.md`
- Workspace switching with `/workspace switch <project>`

**Keep for V2:** ✅ Yes, essential for real-world use

#### ✅ **6. Comprehensive Documentation Templates**

**Why it works:**
- 100+ templates covering all EN 50128 deliverables
- Consistent structure (Document Control, Approvals, etc.)
- Compliance-ready (SIL-specific sections)
- Easy to customize (Markdown format)

**Evidence:**
- Reference implementation has 30+ documents
- All documents follow EN 50128 Annex C requirements
- Template compliance checked by QUA agent

**Keep for V2:** ✅ Yes, expand with more standards

#### ✅ **7. Standards in LLM-Friendly Format**

**Why it works:**
- Agents can directly reference standards
- No need for external lookups
- Accurate citations (section numbers preserved)
- Fast access (local files, no network)

**Evidence:**
- 2.7 MB of standards in Markdown
- Agents cite specific sections (e.g., "per EN 50128 Section 7.2.2")
- Conversion tools available (`tools/pdf-conversion/`)

**Keep for V2:** ✅ Yes, expand with more standards

#### ✅ **8. Tool Integration Strategy**

**Why it works:**
- Clear tool classification (T1/T2/T3 per EN 50128 Section 6.7)
- Tool selection matrix (TOOLS.md)
- Qualification tracking
- SIL-appropriate tool selection

**Evidence:**
- TOOLS.md catalogs 20+ tools
- Agents use tools correctly (e.g., VER uses cppcheck + clang for SIL 3)
- Tool qualification documented (`docs/tool-qualification/`)

**Keep for V2:** ✅ Yes, enhance automation

#### ✅ **9. Independence Modeling (SIL 3-4)**

**Why it works:**
- Organizational structure encoded in agent relationships
- VMGR role formalizes independent V&V authority
- VER/VAL agents cannot be influenced by PM/COD
- Matches EN 50128 Section 5.1.2.10 requirements

**Evidence:**
- VMGR agent introduced (based on EN 50128 5.1.2.10e)
- Authority structure documented in AGENTS.md
- Reference implementation demonstrates independent V&V workflow

**Keep for V2:** ✅ Yes, critical for SIL 3-4

#### ✅ **10. Traceability Matrix Approach**

**Why it works:**
- Bidirectional traceability (requirements ↔ design ↔ code ↔ tests)
- Embedded in Software Requirements Specification (not separate tool)
- Markdown-based (version controlled)
- Auditable (Git history)

**Evidence:**
- Reference implementation: 39 requirements → 15 design elements → 48 code units → 67 tests
- Traceability verified by VER agent
- QUA agent checks traceability completeness

**Keep for V2:** ✅ Yes, enhance with automation

---

## 5. Identified Issues & Limitations

### 5.1 Performance & Scalability Issues

#### ⚠️ **Issue 1: Large Agent Instruction Sets**

**Problem:**
- COD agent: 97,644 lines (largest)
- PM agent: 56,730 lines
- VAL agent: 52,035 lines
- VER agent: 51,841 lines

**Impact:**
- **Context window pressure** - LLMs have finite context (e.g., Claude 200K tokens)
- **Slow loading times** - large files take time to read and parse
- **Maintainability** - difficult to edit/debug 50K+ line files
- **Comprehension difficulty** - hard for contributors to understand

**Evidence:**
- COD agent is 97K lines (~24K tokens) - consumes significant context
- PM agent automation mode (56K lines) has all orchestration logic embedded

**Severity:** 🔴 **HIGH** - limits scalability, maintainability

#### ⚠️ **Issue 2: Skill Loading Strategy**

**Problem:**
- Skills are loaded **in full** when agent references them
- Verification skill: 240 KB
- Documentation skill: 228 KB
- Quality skill: 216 KB

**Impact:**
- **Memory overhead** - entire skill loaded even if only small part needed
- **Context waste** - unused templates consume LLM context
- **Slow agent startup** - loading multiple large skills takes time

**Example:**
```
VER agent loads skill("en50128-verification")
  → Loads entire 240 KB (7 report templates + 3 workflows)
  → Agent only needs static-analysis workflow
  → Other 80% of skill is unused context
```

**Severity:** 🟡 **MEDIUM** - affects performance, not functionality

#### ⚠️ **Issue 3: Standard Document Size**

**Problem:**
- EN50128-2011.md: 2.2 MB (~550K tokens)
- Total standards: 2.7 MB

**Impact:**
- **Cannot fit in context** - exceeds most LLM context windows
- **Selective loading required** - agents must know which sections to load
- **Slow lookups** - searching 2.2 MB file for specific section

**Current Workaround:**
- Agents reference specific sections (e.g., "Section 7.2")
- Full standard not loaded into context
- Agents use grep/search to find relevant sections

**Severity:** 🟡 **MEDIUM** - manageable with current workarounds

#### ⚠️ **Issue 4: Traceability Matrix Manual Maintenance**

**Problem:**
- Traceability matrix in Software Requirements Specification is **manually maintained**
- No automated extraction from code comments
- No automated verification of traceability completeness

**Impact:**
- **Error-prone** - easy to miss trace links
- **Outdated quickly** - code changes require manual doc updates
- **Time-consuming** - developers must update docs manually

**Example:**
```c
// Current: No automatic traceability
bool validate_door_state(door_state_t* state) {
    // Implements REQ-DOOR-003, REQ-DOOR-005 (manual doc update required)
    // ...
}

// Desired: Automatic traceability extraction
// @trace REQ-DOOR-003 @trace REQ-DOOR-005
bool validate_door_state(door_state_t* state) {
    // ... (traceability matrix auto-generated)
}
```

**Severity:** 🟡 **MEDIUM** - functional but inefficient

### 5.2 Architectural Limitations

#### ⚠️ **Issue 5: Agent Orchestration Complexity**

**Problem:**
- PM agent has **all orchestration logic embedded** in instructions
- No formal inter-agent communication protocol
- Handoffs are text-based (implicit)

**Impact:**
- **Difficult to modify workflows** - must edit 56K line PM agent
- **No reusability** - orchestration patterns not abstracted
- **Hard to debug** - no structured logging of agent interactions

**Example:**
```
Current: PM agent instructions (embedded logic)
"1. Invoke /req to create Software Requirements Specification
 2. Wait for completion
 3. Invoke /saf to perform hazard analysis
 4. Wait for completion
 5. Invoke /qua review-requirements
 6. Check if QUA approved (parse output)
 7. If rejected, goto step 1
 8. If approved, invoke /ver verify-requirements
 ... (40 more steps)"

Desired: Structured workflow definition
workflow:
  - agent: req
    output: docs/Software-Requirements-Specification.md
    next: saf
  - agent: saf
    input: docs/Software-Requirements-Specification.md
    output: docs/Hazard-Log.md
    next: qua
  ...
```

**Severity:** 🟡 **MEDIUM** - works but not scalable

#### ⚠️ **Issue 6: No Tool Qualification Automation**

**Problem:**
- Tool qualification status tracked **manually**
- No programmatic checks (e.g., "Is gcc qualified for SIL 3?")
- Qualification documents referenced but not verified

**Impact:**
- **Compliance risk** - unqualified tools may be used unknowingly
- **Manual verification** - auditors must manually check tool status
- **No enforcement** - agents don't block usage of unqualified tools

**Example:**
```
Current: TOOLS.md (documentation only)
"GCC: TCL T3, qualification required
 Evidence: docs/tool-qualification/gcc-qualification.md"

Desired: Tool registry with programmatic checks
{
  "tools": {
    "gcc": {
      "version": "13.3.0",
      "tcl": "T3",
      "qualified": true,
      "qualification_doc": "docs/tool-qualification/gcc-qualification.md",
      "sil_approved": [0, 1, 2, 3, 4]
    }
  }
}

Agent checks before using tool:
if tool_registry.is_qualified("gcc", project_sil=3):
    use gcc
else:
    error("GCC not qualified for SIL 3")
```

**Severity:** 🟡 **MEDIUM** - compliance risk

#### ⚠️ **Issue 7: Phase State Format**

**Problem:**
- `LIFECYCLE_STATE.md` is Markdown (human-readable)
- No machine-readable format (JSON/YAML)
- Difficult to parse programmatically

**Impact:**
- **No automation** - phase status checks require text parsing
- **Error-prone** - manual updates to LIFECYCLE_STATE.md
- **No validation** - invalid state transitions not prevented

**Example:**
```
Current: LIFECYCLE_STATE.md (Markdown)
## Phase 2: Requirements
**Status**: ✅ Complete
**Deliverables**:
- [x] Software Requirements Specification
- [x] Hazard Log
...

Desired: Add machine-readable format
project/
├── LIFECYCLE_STATE.md        # Human-readable (keep)
└── .lifecycle/
    └── state.json            # Machine-readable (add)
    {
      "phase": 2,
      "status": "complete",
      "deliverables": {
        "Software-Requirements-Specification.md": "complete",
        "Hazard-Log.md": "complete"
      }
    }
```

**Severity:** 🟡 **MEDIUM** - functional but not automated

#### ⚠️ **Issue 8: No Multi-Standard Support**

**Problem:**
- Platform is **EN 50128-only**
- No support for other safety standards (IEC 61508, ISO 26262, DO-178C)
- Skills, agents, templates all EN 50128-specific

**Impact:**
- **Limited applicability** - only for railway software
- **No reusability** - cannot use for automotive (ISO 26262) or avionics (DO-178C)
- **Duplicate effort** - would need separate platforms for each standard

**Opportunity:**
- Many safety standards share common concepts (requirements, design, V&V, etc.)
- Could abstract core lifecycle, specialize by standard

**Severity:** 🟢 **LOW** - out of scope for EN50128, but limits platform adoption

### 5.3 Usability & Documentation Issues

#### ⚠️ **Issue 9: Steep Learning Curve**

**Problem:**
- 13 agents, 14 skills, 8 lifecycle phases
- Complex workflows (manual vs. PM automation mode)
- EN 50128 domain knowledge required

**Impact:**
- **Long onboarding** - new users need significant time to understand
- **Errors common** - users invoke agents out of sequence
- **Tutorial dependency** - must read TUTORIAL.md to be effective

**Evidence:**
- TUTORIAL.md is comprehensive but long
- Users report confusion about when to use which agent
- PM automation mode added to simplify (but adds complexity)

**Severity:** 🟡 **MEDIUM** - usability issue

#### ⚠️ **Issue 10: No CI/CD Integration**

**Problem:**
- No GitHub Actions workflows
- No automated testing of platform itself
- No continuous validation of reference implementation

**Impact:**
- **Quality risk** - changes may break agents/skills
- **Regression risk** - no automated tests for workflows
- **Manual verification** - contributors must manually test

**Severity:** 🟡 **MEDIUM** - development efficiency issue

### 5.4 Summary of Issues by Severity

| Severity | Count | Issues |
|----------|-------|--------|
| 🔴 **HIGH** | 1 | Large agent instruction sets (context/maintainability) |
| 🟡 **MEDIUM** | 8 | Skill loading, traceability automation, orchestration complexity, tool qualification, phase state format, learning curve, no CI/CD, standard document size |
| 🟢 **LOW** | 1 | No multi-standard support (out of scope) |

---

## 6. Improvement Recommendations

### 6.1 Short-Term Improvements (V2.0 - Quick Wins)

#### 🎯 **Recommendation 1: Agent Decomposition**

**Problem:** COD (97K lines) and PM (56K lines) agents are too large

**Solution:** Break into modular instruction sets

**Proposed Structure:**
```
.opencode/commands/
├── cod/
│   ├── main.md                          # Entry point (5K lines)
│   ├── modules/
│   │   ├── gate-checking.md            # Phase gate logic (20K lines)
│   │   ├── phase-orchestration.md      # V-Model workflows (30K lines)
│   │   ├── compliance-verification.md  # EN 50128 checks (20K lines)
│   │   ├── deliverable-tracking.md     # Document tracking (15K lines)
│   │   └── sil-enforcement.md          # SIL-dependent rules (10K lines)
│   └── README.md                        # Module index
│
├── pm/
│   ├── main.md                          # Entry point (5K lines)
│   ├── modules/
│   │   ├── phase-automation.md         # Execute-phase workflows (25K lines)
│   │   ├── agent-orchestration.md      # Inter-agent coordination (15K lines)
│   │   ├── ccb-management.md           # Change Control Board (10K lines)
│   │   └── risk-management.md          # Risk tracking (5K lines)
│   └── README.md
│
└── [other-agents].md                    # Smaller agents remain as single files
```

**Agent Loading Logic:**
```markdown
# cod/main.md
You are the Lifecycle Coordinator (COD) agent.

Core responsibilities: [overview]

For detailed instructions, load these modules as needed:
- Gate checking: load("cod/modules/gate-checking.md")
- Phase orchestration: load("cod/modules/phase-orchestration.md")
- Compliance verification: load("cod/modules/compliance-verification.md")
- ...

When user invokes /cod gate-check <phase>:
  1. Load("cod/modules/gate-checking.md")
  2. Execute gate check logic from module
  3. Return result to user
```

**Benefits:**
- ✅ Reduces context pressure (load only needed modules)
- ✅ Improves maintainability (edit smaller files)
- ✅ Better comprehension (clear module boundaries)
- ✅ Reusability (modules can be shared across agents)

**Effort:** 🟡 **MEDIUM** (3-5 days to refactor)

**Priority:** 🔴 **HIGH** (addresses largest architectural issue)

---

#### 🎯 **Recommendation 2: Lazy Skill Loading**

**Problem:** Skills loaded in full even when only small part needed

**Solution:** Implement skill module system with lazy loading

**Proposed Structure:**
```
.opencode/skills/en50128-verification/
├── SKILL.md                             # Index/router (5 KB)
├── modules/
│   ├── static-analysis.md              # Cppcheck, Clang usage (40 KB)
│   ├── complexity-analysis.md          # Lizard, metrics (30 KB)
│   ├── coverage-analysis.md            # gcov, lcov usage (35 KB)
│   ├── misra-c-checking.md             # MISRA C compliance (40 KB)
│   ├── traceability-verification.md    # Traceability checks (30 KB)
│   └── evidence-collection.md          # Verification evidence (35 KB)
├── report-templates/
│   ├── Software-Requirements-Verification-Report.md
│   ├── Software-Architecture-Verification-Report.md
│   └── ... (7 templates)
└── verification-criteria/
    └── OVERVIEW.md
```

**Skill Index Logic:**
```markdown
# SKILL.md (Index/Router)
This skill provides verification techniques per EN 50128 Section 6.2.

Available modules:
1. **static-analysis.md** - Static analysis with Cppcheck, Clang
2. **complexity-analysis.md** - Complexity metrics with Lizard
3. **coverage-analysis.md** - Coverage analysis with gcov/lcov
4. **misra-c-checking.md** - MISRA C compliance checking
5. **traceability-verification.md** - Traceability matrix verification
6. **evidence-collection.md** - Verification evidence collection

Usage:
- For static analysis: load("en50128-verification/modules/static-analysis.md")
- For complexity: load("en50128-verification/modules/complexity-analysis.md")
- ...

Report templates:
- For requirements verification: load("en50128-verification/report-templates/Software-Requirements-Verification-Report.md")
```

**Agent Usage:**
```markdown
# VER agent needs to perform static analysis
skill("en50128-verification")  # Loads only SKILL.md (5 KB index)
load("en50128-verification/modules/static-analysis.md")  # Load specific module (40 KB)
```

**Benefits:**
- ✅ Reduces context usage (load only needed parts)
- ✅ Faster agent startup (smaller initial load)
- ✅ More focused instructions (less noise)
- ✅ Better organization (clear module boundaries)

**Effort:** 🟡 **MEDIUM** (5-7 days to refactor 14 skills)

**Priority:** 🟡 **MEDIUM** (improves performance)

---

#### 🎯 **Recommendation 3: Tool Registry with Qualification Tracking**

**Problem:** Tool qualification status not tracked programmatically

**Solution:** Add tool registry with qualification metadata

**Proposed Implementation:**
```
tools/
├── registry/
│   ├── tool-registry.json               # Machine-readable registry
│   ├── tool-registry.schema.json        # JSON schema for validation
│   └── README.md                        # Registry documentation
├── tool-check.py                        # Tool availability checker
└── tool-qualify.py                      # Qualification verification script
```

**Tool Registry Format:**
```json
{
  "$schema": "./tool-registry.schema.json",
  "version": "2.0.0",
  "tools": {
    "gcc": {
      "name": "GNU Compiler Collection",
      "version_required": ">=13.0.0",
      "version_installed": "13.3.0",
      "tcl": "T3",
      "qualified": true,
      "qualification_doc": "docs/tool-qualification/gcc-qualification.md",
      "qualification_date": "2026-01-15",
      "qualification_expires": "2027-01-15",
      "sil_approved": [0, 1, 2, 3, 4],
      "en50128_section": "7.4 (Compiler)",
      "mandatory_for": [0, 1, 2, 3, 4],
      "check_command": "gcc --version"
    },
    "cppcheck": {
      "name": "Cppcheck Static Analyzer",
      "version_required": ">=2.10",
      "version_installed": "2.13.0",
      "tcl": "T2",
      "qualified": true,
      "qualification_doc": "docs/tool-qualification/cppcheck-validation.md",
      "qualification_date": "2026-02-01",
      "qualification_expires": null,
      "sil_approved": [0, 1, 2, 3, 4],
      "en50128_section": "Table A.19 (Static Analysis)",
      "mandatory_for": [3, 4],
      "highly_recommended_for": [2],
      "check_command": "cppcheck --version"
    },
    "gcov": {
      "name": "GNU Coverage Tool",
      "version_required": ">=13.0.0",
      "version_installed": "13.3.0",
      "tcl": "T2",
      "qualified": true,
      "qualification_doc": "docs/tool-qualification/gcov-validation.md",
      "sil_approved": [0, 1, 2, 3, 4],
      "en50128_section": "Table A.21 (Coverage Analysis)",
      "mandatory_for": [3, 4],
      "highly_recommended_for": [2],
      "check_command": "gcov --version"
    }
  }
}
```

**Tool Check Script:**
```python
#!/usr/bin/env python3
# tools/tool-check.py

import json
import subprocess
import sys

def check_tool_qualification(tool_name, project_sil):
    """Check if tool is qualified for project SIL level."""
    with open("tools/registry/tool-registry.json") as f:
        registry = json.load(f)
    
    if tool_name not in registry["tools"]:
        return {"status": "error", "message": f"Tool {tool_name} not in registry"}
    
    tool = registry["tools"][tool_name]
    
    # Check if installed
    if not tool["version_installed"]:
        return {"status": "error", "message": f"{tool_name} not installed"}
    
    # Check if qualified
    if not tool["qualified"]:
        return {"status": "error", "message": f"{tool_name} not qualified"}
    
    # Check if approved for SIL
    if project_sil not in tool["sil_approved"]:
        return {"status": "error", "message": f"{tool_name} not approved for SIL {project_sil}"}
    
    # Check if mandatory
    if project_sil in tool.get("mandatory_for", []):
        requirement = "MANDATORY"
    elif project_sil in tool.get("highly_recommended_for", []):
        requirement = "HIGHLY RECOMMENDED"
    else:
        requirement = "RECOMMENDED"
    
    return {
        "status": "ok",
        "tool": tool_name,
        "version": tool["version_installed"],
        "tcl": tool["tcl"],
        "requirement": requirement,
        "qualification_doc": tool["qualification_doc"]
    }

if __name__ == "__main__":
    tool = sys.argv[1]
    sil = int(sys.argv[2])
    result = check_tool_qualification(tool, sil)
    print(json.dumps(result, indent=2))
```

**Agent Integration:**
```markdown
# VER agent (ver.md)

Before using any tool, verify qualification:

```bash
# Check if cppcheck is qualified for project SIL
python3 tools/tool-check.py cppcheck 3
```

If status is "ok", proceed with tool usage.
If status is "error", report to user and request qualification or tool substitution.
```

**Benefits:**
- ✅ Programmatic qualification checks (no manual verification)
- ✅ Compliance enforcement (agents block unqualified tools)
- ✅ Auditable (qualification status in version control)
- ✅ Expiration tracking (qualification_expires field)

**Effort:** 🟢 **LOW** (2-3 days)

**Priority:** 🟡 **MEDIUM** (reduces compliance risk)

---

#### 🎯 **Recommendation 4: Machine-Readable Phase State**

**Problem:** LIFECYCLE_STATE.md is Markdown-only, difficult to parse

**Solution:** Add machine-readable state file alongside human-readable Markdown

**Proposed Structure:**
```
project/
├── LIFECYCLE_STATE.md                   # Human-readable (keep)
└── .lifecycle/
    ├── state.json                       # Machine-readable state
    ├── history.json                     # Phase transition history
    └── deliverables.json                # Deliverable tracking
```

**State Format:**
```json
{
  "project": {
    "name": "train_door_control2",
    "sil": 3,
    "created": "2026-01-15T10:00:00Z",
    "last_updated": "2026-03-07T14:30:00Z"
  },
  "lifecycle": {
    "current_phase": 5,
    "phases": {
      "0": {"status": "complete", "completed_date": "2026-01-15"},
      "1": {"status": "complete", "completed_date": "2026-01-20"},
      "2": {"status": "complete", "completed_date": "2026-02-01"},
      "3": {"status": "complete", "completed_date": "2026-02-15"},
      "4": {"status": "complete", "completed_date": "2026-03-01"},
      "5": {"status": "complete", "completed_date": "2026-03-07"},
      "6": {"status": "in_progress", "started_date": "2026-03-07"},
      "7": {"status": "pending"},
      "8": {"status": "pending"}
    }
  },
  "deliverables": {
    "phase_1": {
      "Software-Quality-Assurance-Plan.md": {
        "status": "approved",
        "created": "2026-01-18",
        "approved_by": "QUA",
        "approved_date": "2026-01-19"
      },
      "Software-Configuration-Management-Plan.md": {
        "status": "approved",
        "created": "2026-01-18",
        "approved_by": "QUA",
        "approved_date": "2026-01-19"
      }
    },
    "phase_2": {
      "Software-Requirements-Specification.md": {
        "status": "verified",
        "created": "2026-01-25",
        "verified_by": "VER",
        "verified_date": "2026-01-31"
      },
      "Hazard-Log.md": {
        "status": "verified",
        "created": "2026-01-26",
        "verified_by": "VER",
        "verified_date": "2026-01-31"
      }
    }
  },
  "gate_checks": {
    "phase_1": {
      "checked_date": "2026-01-20",
      "checked_by": "COD",
      "result": "pass",
      "issues": []
    },
    "phase_2": {
      "checked_date": "2026-02-01",
      "checked_by": "COD",
      "result": "pass",
      "issues": []
    }
  }
}
```

**History Format:**
```json
{
  "transitions": [
    {
      "timestamp": "2026-01-15T10:00:00Z",
      "from_phase": null,
      "to_phase": 0,
      "triggered_by": "COD",
      "reason": "Project initialization"
    },
    {
      "timestamp": "2026-01-15T11:00:00Z",
      "from_phase": 0,
      "to_phase": 1,
      "triggered_by": "COD",
      "reason": "Phase 0 complete, moving to Planning"
    },
    {
      "timestamp": "2026-01-20T16:30:00Z",
      "from_phase": 1,
      "to_phase": 2,
      "triggered_by": "COD",
      "gate_check": "pass",
      "reason": "Planning complete, all deliverables approved"
    }
  ]
}
```

**Benefits:**
- ✅ Programmatic state queries (agents can check phase easily)
- ✅ Automated validation (invalid transitions rejected)
- ✅ Audit trail (history.json tracks all transitions)
- ✅ Dashboard potential (state.json enables web dashboard)
- ✅ Keep human-readable format (LIFECYCLE_STATE.md still exists)

**Effort:** 🟢 **LOW** (2-3 days)

**Priority:** 🟡 **MEDIUM** (enables automation)

---

#### 🎯 **Recommendation 5: Automated Traceability Extraction**

**Problem:** Traceability matrix manually maintained in Software Requirements Specification

**Solution:** Implement automatic traceability extraction from code comments

**Proposed Approach:**

**Step 1: Add trace annotations to code**
```c
// src/door_controller.c

/**
 * @brief Validates door state for safety compliance
 * @trace REQ-DOOR-003 Door state validation
 * @trace REQ-DOOR-005 Emergency stop detection
 * @param state Door state structure
 * @return true if valid, false otherwise
 */
bool validate_door_state(door_state_t* state) {
    // Implementation
}

/**
 * @brief Commands door to open
 * @trace REQ-DOOR-001 Door opening command
 * @design DES-DOOR-CTRL-002 Door control state machine
 * @param door_id Door identifier
 * @return Error code
 */
error_t open_door(uint8_t door_id) {
    // Implementation
}
```

**Step 2: Extract traceability with Python script**
```python
#!/usr/bin/env python3
# tools/traceability/extract-trace.py

import re
import json
import sys
from pathlib import Path

def extract_traces_from_file(filepath):
    """Extract @trace annotations from C source file."""
    traces = []
    with open(filepath) as f:
        content = f.read()
    
    # Find all @trace annotations
    pattern = r'@trace\s+([\w-]+)\s+(.+?)(?:\n|\*/)'
    matches = re.findall(pattern, content, re.MULTILINE)
    
    # Find function definitions
    func_pattern = r'(\w+\s+)+(\w+)\s*\([^)]*\)\s*{'
    functions = re.findall(func_pattern, content)
    
    for req_id, description in matches:
        traces.append({
            "file": str(filepath),
            "requirement": req_id,
            "description": description.strip(),
            "type": "implementation"
        })
    
    return traces

def extract_traces_from_project(src_dir):
    """Extract all traces from project."""
    all_traces = []
    for c_file in Path(src_dir).rglob("*.c"):
        traces = extract_traces_from_file(c_file)
        all_traces.extend(traces)
    return all_traces

def generate_traceability_matrix(traces):
    """Generate traceability matrix from traces."""
    matrix = {}
    for trace in traces:
        req_id = trace["requirement"]
        if req_id not in matrix:
            matrix[req_id] = []
        matrix[req_id].append({
            "file": trace["file"],
            "description": trace["description"]
        })
    return matrix

if __name__ == "__main__":
    src_dir = sys.argv[1] if len(sys.argv) > 1 else "src"
    traces = extract_traces_from_project(src_dir)
    matrix = generate_traceability_matrix(traces)
    print(json.dumps(matrix, indent=2))
```

**Step 3: Auto-generate traceability section in Software Requirements Specification**
```markdown
# Software Requirements Specification
...

## 8. Traceability Matrix

*This section is AUTO-GENERATED by `tools/traceability/extract-trace.py`*
*Last updated: 2026-03-07 14:30:00*

| Requirement ID | Requirement | Implemented In | Design Element | Test Case |
|----------------|-------------|----------------|----------------|-----------|
| REQ-DOOR-001 | Door opening command | `src/door_controller.c:45` (open_door) | DES-DOOR-CTRL-002 | `test/test_door_controller.c:120` |
| REQ-DOOR-003 | Door state validation | `src/door_controller.c:78` (validate_door_state) | DES-DOOR-CTRL-003 | `test/test_door_controller.c:150` |
| REQ-DOOR-005 | Emergency stop detection | `src/door_controller.c:78` (validate_door_state), `src/safety_monitor.c:34` (check_emergency_stop) | DES-SAFETY-001 | `test/test_safety_monitor.c:90` |

...
```

**Step 4: Integrate with Makefile**
```makefile
# Makefile

.PHONY: trace
trace:
	@echo "Extracting traceability..."
	python3 tools/traceability/extract-trace.py src > .lifecycle/traceability.json
	python3 tools/traceability/update-srs.py docs/Software-Requirements-Specification.md .lifecycle/traceability.json

.PHONY: verify-trace
verify-trace:
	@echo "Verifying traceability completeness..."
	python3 tools/traceability/verify-trace.py docs/Software-Requirements-Specification.md .lifecycle/traceability.json
```

**Benefits:**
- ✅ Automated traceability (no manual updates)
- ✅ Always up-to-date (regenerate with `make trace`)
- ✅ Verifiable (tool checks completeness)
- ✅ Auditable (trace annotations in code, matrix in docs)
- ✅ CI/CD integration (automated checks)

**Effort:** 🟡 **MEDIUM** (3-4 days)

**Priority:** 🟡 **MEDIUM** (improves efficiency, reduces errors)

---

### 6.2 Medium-Term Improvements (V2.1 - Infrastructure)

#### 🎯 **Recommendation 6: Structured Agent Communication Protocol**

**Problem:** Agent handoffs are implicit (text-based), no formal protocol

**Solution:** Define structured inter-agent communication with artifacts and status

**Proposed Protocol:**

**Step 1: Define handoff message format**
```yaml
# .lifecycle/handoffs/handoff-req-to-ver-phase2.yaml
handoff:
  id: "handoff-2024-03-07-001"
  timestamp: "2026-03-07T14:30:00Z"
  from_agent: "req"
  to_agent: "ver"
  phase: 2
  artifact:
    type: "document"
    path: "docs/Software-Requirements-Specification.md"
    checksum: "sha256:abcd1234..."
  status: "ready_for_verification"
  metadata:
    requirements_count: 39
    sil_level: 3
    traceability_complete: true
  next_action: "verify-requirements"
  expected_output:
    - "docs/Software-Requirements-Verification-Report.md"
```

**Step 2: Agent handoff commands**
```markdown
# REQ agent completes work

When requirements specification is complete:
1. Create handoff file:
   ```bash
   python3 tools/handoff/create-handoff.py \
     --from req \
     --to ver \
     --phase 2 \
     --artifact docs/Software-Requirements-Specification.md \
     --action verify-requirements
   ```

2. Notify user:
   "Requirements specification complete. Handoff to VER agent created.
    Next: /ver verify-requirements"
```

**Step 3: Agent handoff receipt**
```markdown
# VER agent receives handoff

When /ver verify-requirements is invoked:
1. Check for pending handoffs:
   ```bash
   python3 tools/handoff/check-handoffs.py --agent ver --phase 2
   ```

2. If handoff exists:
   - Load artifact (docs/Software-Requirements-Specification.md)
   - Verify checksum
   - Read metadata (39 requirements, SIL 3, traceability complete)
   - Begin verification

3. Update handoff status:
   ```bash
   python3 tools/handoff/update-handoff.py \
     --id handoff-2024-03-07-001 \
     --status in_progress
   ```
```

**Benefits:**
- ✅ Formal protocol (clear handoff semantics)
- ✅ Auditable (handoff files in .lifecycle/handoffs/)
- ✅ Structured data (YAML, not text parsing)
- ✅ Status tracking (ready/in_progress/complete)
- ✅ Checksum verification (artifact integrity)

**Effort:** 🟡 **MEDIUM** (5-7 days)

**Priority:** 🟡 **MEDIUM** (improves robustness)

---

#### 🎯 **Recommendation 7: CI/CD Pipeline**

**Problem:** No automated testing of platform or reference implementation

**Solution:** Add GitHub Actions workflows for continuous validation

**Proposed Workflows:**

**Workflow 1: Platform Validation**
```yaml
# .github/workflows/platform-validation.yml
name: Platform Validation

on: [push, pull_request]

jobs:
  validate-agents:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Validate agent definitions
        run: |
          # Check all agent files are valid Markdown
          for agent in .opencode/commands/*.md; do
            echo "Validating $agent"
            markdownlint "$agent"
          done
      
      - name: Validate skill structure
        run: |
          # Check all skills have SKILL.md entry point
          for skill in .opencode/skills/*; do
            if [ ! -f "$skill/SKILL.md" ]; then
              echo "ERROR: $skill missing SKILL.md"
              exit 1
            fi
          done
  
  validate-tools:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Install tools
        run: |
          sudo apt-get update
          sudo apt-get install -y build-essential cppcheck clang valgrind lcov
      
      - name: Verify tool installation
        run: ./install_tools.sh --check
      
      - name: Check tool registry
        run: |
          python3 tools/tool-check.py gcc 3
          python3 tools/tool-check.py cppcheck 3
          python3 tools/tool-check.py gcov 3
  
  validate-standards:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Validate standard documents
        run: |
          # Check standard files exist and are non-empty
          test -s std/EN50128-2011.md
          test -s std/EN\ 50126-1-2017.md
          test -s std/EN\ 50126-2-2017.md
```

**Workflow 2: Reference Implementation Testing**
```yaml
# .github/workflows/reference-impl-test.yml
name: Reference Implementation Testing

on: [push, pull_request]

jobs:
  build-and-test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Install dependencies
        run: |
          sudo apt-get update
          sudo apt-get install -y build-essential cppcheck clang valgrind lcov python3-pip
          pip3 install lizard
      
      - name: Build train_door_control2
        run: |
          cd examples/train_door_control2
          make clean
          make all
      
      - name: Run unit tests
        run: |
          cd examples/train_door_control2
          make test
      
      - name: Generate coverage
        run: |
          cd examples/train_door_control2
          make coverage
          # Check coverage thresholds (SIL 3 requires 100%)
          lcov --summary coverage.info | grep "lines......: 100.0%"
          lcov --summary coverage.info | grep "branches...: 100.0%"
      
      - name: Static analysis
        run: |
          cd examples/train_door_control2
          make static-analysis
          # Check for violations (should be zero for SIL 3)
          cppcheck --error-exitcode=1 --enable=all src/
      
      - name: Complexity analysis
        run: |
          cd examples/train_door_control2
          make complexity
          # Check complexity (should be ≤10 for SIL 3)
          lizard src/ --CCN 10
      
      - name: Upload coverage report
        uses: codecov/codecov-action@v3
        with:
          files: examples/train_door_control2/coverage.info
```

**Workflow 3: Documentation Validation**
```yaml
# .github/workflows/docs-validation.yml
name: Documentation Validation

on: [push, pull_request]

jobs:
  validate-docs:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Validate Markdown
        run: |
          markdownlint README.md TUTORIAL.md LIFECYCLE.md AGENTS.md
      
      - name: Check for broken links
        run: |
          npm install -g markdown-link-check
          find . -name "*.md" -exec markdown-link-check {} \;
      
      - name: Validate document templates
        run: |
          # Check all templates have required sections
          python3 tools/validate-templates.py .opencode/skills/*/templates/*.md
```

**Benefits:**
- ✅ Automated quality checks (catch regressions)
- ✅ Continuous validation (every commit tested)
- ✅ Coverage enforcement (100% for SIL 3)
- ✅ Static analysis enforcement (zero violations)
- ✅ Documentation validation (no broken links)

**Effort:** 🟡 **MEDIUM** (3-5 days)

**Priority:** 🟡 **MEDIUM** (improves quality, development velocity)

---

### 6.3 Long-Term Improvements (V3.0 - Strategic)

#### 🎯 **Recommendation 8: Multi-Standard Support**

**Problem:** Platform is EN 50128-only, cannot support other safety standards

**Solution:** Abstract core lifecycle, create standard-specific skill packs

**Proposed Architecture:**

```
EN50128-Platform-V3/
├── .opencode/
│   ├── commands/
│   │   ├── core/                        # Standard-agnostic agents
│   │   │   ├── lifecycle-coordinator.md # Abstract V-Model coordinator
│   │   │   ├── requirements-engineer.md # Abstract requirements agent
│   │   │   ├── designer.md              # Abstract design agent
│   │   │   ├── implementer.md           # Abstract implementation agent
│   │   │   ├── tester.md                # Abstract testing agent
│   │   │   ├── verifier.md              # Abstract verification agent
│   │   │   ├── validator.md             # Abstract validation agent
│   │   │   └── ... (other core agents)
│   │   │
│   │   └── standards/                   # Standard-specific extensions
│   │       ├── en50128/                 # Railway (EN 50128)
│   │       │   ├── cod-en50128.md       # EN 50128-specific COD logic
│   │       │   ├── req-en50128.md       # EN 50128-specific REQ logic
│   │       │   └── ...
│   │       ├── iec61508/                # Functional safety (IEC 61508)
│   │       │   ├── cod-iec61508.md
│   │       │   ├── req-iec61508.md
│   │       │   └── ...
│   │       ├── iso26262/                # Automotive (ISO 26262)
│   │       │   ├── cod-iso26262.md
│   │       │   ├── req-iso26262.md
│   │       │   └── ...
│   │       └── do178c/                  # Avionics (DO-178C)
│   │           └── ...
│   │
│   ├── skills/
│   │   ├── core/                        # Standard-agnostic skills
│   │   │   ├── requirements-engineering/
│   │   │   ├── software-design/
│   │   │   ├── verification/
│   │   │   ├── validation/
│   │   │   └── ...
│   │   │
│   │   └── standards/                   # Standard-specific skills
│   │       ├── en50128/
│   │       │   ├── en50128-requirements/
│   │       │   ├── en50128-design/
│   │       │   └── ...
│   │       ├── iec61508/
│   │       │   ├── iec61508-requirements/
│   │       │   └── ...
│   │       ├── iso26262/
│   │       │   ├── iso26262-requirements/
│   │       │   └── ...
│   │       └── do178c/
│   │           └── ...
│   │
│   └── opencode.jsonc                   # Standard selection config
│
├── std/
│   ├── EN50128/                         # Railway standards
│   │   ├── EN50128-2011.md
│   │   └── ...
│   ├── IEC61508/                        # Functional safety standards
│   │   ├── IEC61508-1-2010.md
│   │   └── ...
│   ├── ISO26262/                        # Automotive standards
│   │   ├── ISO26262-2018.md
│   │   └── ...
│   └── DO178C/                          # Avionics standards
│       ├── DO-178C.md
│       └── ...
│
└── examples/
    ├── railway/                         # EN 50128 projects
    │   └── train_door_control2/
    ├── automotive/                      # ISO 26262 projects
    │   └── adas_controller/
    ├── avionics/                        # DO-178C projects
    │   └── flight_control/
    └── industrial/                      # IEC 61508 projects
        └── safety_plc/
```

**Configuration:**
```jsonc
// .opencode/opencode.jsonc
{
  "$schema": "https://opencode.ai/config.json",
  "safety_standard": "en50128",  // or "iec61508", "iso26262", "do178c"
  "agent_mode": "standard_specific",  // loads core + standard-specific agents
  "skills": {
    "core": true,
    "standard_specific": true
  }
}
```

**Agent Loading Logic:**
```markdown
# Core lifecycle-coordinator.md

You are the Lifecycle Coordinator agent.

Load standard-specific behavior:
- If safety_standard == "en50128": load("commands/standards/en50128/cod-en50128.md")
- If safety_standard == "iec61508": load("commands/standards/iec61508/cod-iec61508.md")
- If safety_standard == "iso26262": load("commands/standards/iso26262/cod-iso26262.md")
- If safety_standard == "do178c": load("commands/standards/do178c/cod-do178c.md")

Standard-specific module provides:
- SIL/ASIL/DAL level definitions
- Phase gate criteria
- Deliverable requirements
- Technique tables
```

**Benefits:**
- ✅ Multi-standard support (EN 50128, IEC 61508, ISO 26262, DO-178C)
- ✅ Code reuse (core agents shared across standards)
- ✅ Easy extension (add new standard = add new skill pack)
- ✅ Wider adoption (automotive, avionics, industrial)

**Effort:** 🔴 **HIGH** (3-6 months, requires domain expertise)

**Priority:** 🟢 **LOW** (strategic, not critical for EN 50128 use)

---

#### 🎯 **Recommendation 9: Web Dashboard**

**Problem:** All interactions via CLI, no visual overview

**Solution:** Add web dashboard for project monitoring

**Proposed Features:**
1. **Project Overview**
   - Current phase visualization
   - Deliverable checklist
   - Phase progress (0-100%)
   - Gate check status

2. **Traceability Visualization**
   - Interactive traceability matrix
   - Requirement coverage heatmap
   - Orphaned requirements/code detection

3. **Quality Metrics**
   - Code coverage trends
   - Complexity trends
   - MISRA C violation trends
   - Defect density

4. **Team Collaboration**
   - Agent activity timeline
   - Document review status
   - Pending approvals
   - Change requests (CCB)

**Tech Stack:**
- Frontend: React + TypeScript
- Backend: Python FastAPI (reads .lifecycle/*.json)
- Deployment: Single-page app (no server needed, reads local files)

**Mockup:**
```
┌─────────────────────────────────────────────────────────────┐
│ EN50128 Dashboard - train_door_control2 (SIL 3)             │
├─────────────────────────────────────────────────────────────┤
│ Current Phase: 6 - Validation                               │
│ Progress: ████████████░░░░░░░░░░ 60%                       │
│                                                             │
│ Phase Status:                                               │
│ ✅ Phase 0: Initialization                                  │
│ ✅ Phase 1: Planning                                        │
│ ✅ Phase 2: Requirements (39 requirements)                  │
│ ✅ Phase 3: Design (15 design elements)                     │
│ ✅ Phase 4: Implementation (2,000 LOC, 100% coverage)       │
│ ✅ Phase 5: Integration (5 integration tests)               │
│ 🔄 Phase 6: Validation (in progress)                        │
│ ⏳ Phase 7: Assessment (pending)                            │
│ ⏳ Phase 8: Deployment (pending)                            │
│                                                             │
│ Deliverables (Phase 6):                                     │
│ ✅ System Test Specification                                │
│ 🔄 System Test Report (60% complete)                        │
│ ⏳ Validation Report (pending)                              │
│                                                             │
│ Quality Metrics:                                            │
│ Coverage: 100% ████████████████████████ (Target: 100%)     │
│ Complexity: Avg 5.2 (Max 10, Target: ≤10)                  │
│ MISRA C: 0 violations (Target: 0)                          │
│                                                             │
│ Recent Activity:                                            │
│ [2026-03-07 14:30] VAL: System test execution started      │
│ [2026-03-07 12:00] VAL: System test specification approved │
│ [2026-03-07 10:00] COD: Phase 5 gate check PASSED          │
└─────────────────────────────────────────────────────────────┘
```

**Benefits:**
- ✅ Visual project overview (at-a-glance status)
- ✅ Stakeholder communication (non-technical users can view)
- ✅ Progress tracking (timeline, burndown)
- ✅ Quality monitoring (trends over time)

**Effort:** 🔴 **HIGH** (2-3 months)

**Priority:** 🟢 **LOW** (nice-to-have, not critical)

---

#### 🎯 **Recommendation 10: External Tool Integration**

**Problem:** No integration with commercial tools (DOORS, Jama, Polarion, Git hosting)

**Solution:** Add connectors for external tools

**Proposed Integrations:**

1. **Requirements Management Tools**
   - IBM DOORS (export/import)
   - Jama Connect (API integration)
   - Polarion (REST API)

2. **Git Hosting Platforms**
   - GitHub Issues (traceability)
   - GitLab Issues
   - Azure DevOps Work Items

3. **Test Management Tools**
   - TestRail (test case sync)
   - Xray (Jira plugin)

4. **Commercial Static Analyzers**
   - LDRA (report import)
   - PC-lint Plus (report import)
   - Polyspace (MATLAB/Simulink)

**Example: DOORS Integration**
```python
# tools/integrations/doors/import-requirements.py

import subprocess
import json
import xml.etree.ElementTree as ET

def export_from_doors(doors_module, output_file):
    """Export requirements from DOORS to XML."""
    # Use DOORS DXL API
    dxl_script = f"""
    Module m = read("{doors_module}", false)
    for obj in m do {{
        print obj."Object Identifier" "\t" obj."Object Text" "\n"
    }}
    """
    subprocess.run(["doors", "-batch", dxl_script, "-o", output_file])

def convert_to_srs_format(doors_xml, srs_markdown):
    """Convert DOORS XML to Software Requirements Specification Markdown."""
    tree = ET.parse(doors_xml)
    requirements = []
    
    for obj in tree.findall(".//Object"):
        req_id = obj.find("Identifier").text
        req_text = obj.find("Text").text
        requirements.append({
            "id": req_id,
            "text": req_text
        })
    
    # Generate Markdown
    with open(srs_markdown, "w") as f:
        f.write("# Software Requirements Specification\n\n")
        f.write("## 5. Software Requirements\n\n")
        for req in requirements:
            f.write(f"### {req['id']}\n\n")
            f.write(f"{req['text']}\n\n")
```

**Benefits:**
- ✅ Bi-directional sync (EN50128 platform ↔ commercial tools)
- ✅ Leverage existing investments (customers already use DOORS, Jama)
- ✅ Enterprise integration (fits into existing toolchains)
- ✅ Compliance evidence (traceability to external systems)

**Effort:** 🔴 **HIGH** (varies by integration, 1-2 weeks each)

**Priority:** 🟢 **LOW** (commercial/enterprise feature)

---

## 7. Re-Architecture Options

### Option 1: Incremental Refactoring (Recommended)

**Approach:** Improve existing architecture step-by-step

**Strategy:**
1. ✅ **Phase 1 (V2.0)**: Short-term improvements (Recommendations 1-5)
   - Agent decomposition (COD, PM modularization)
   - Lazy skill loading
   - Tool registry
   - Machine-readable state
   - Automated traceability
   - **Timeline:** 3-4 weeks
   - **Risk:** Low (incremental changes)

2. ✅ **Phase 2 (V2.1)**: Infrastructure improvements (Recommendations 6-7)
   - Structured agent communication
   - CI/CD pipeline
   - **Timeline:** 2-3 weeks
   - **Risk:** Low (additive changes)

3. ✅ **Phase 3 (V3.0)**: Strategic features (Recommendations 8-10)
   - Multi-standard support
   - Web dashboard
   - External tool integration
   - **Timeline:** 4-6 months
   - **Risk:** Medium (major new features)

**Pros:**
- ✅ Low risk (gradual changes)
- ✅ Maintains compatibility (existing projects unaffected)
- ✅ Early value delivery (improvements available quickly)
- ✅ Reversible (can rollback if needed)

**Cons:**
- ⚠️ Longer timeline (full transformation takes 6-9 months)
- ⚠️ Technical debt accumulation (old patterns persist alongside new)
- ⚠️ Mixed architecture (some agents modular, some monolithic)

**Verdict:** ✅ **RECOMMENDED** for production use

---

### Option 2: Clean-Slate Rewrite

**Approach:** Redesign from scratch with lessons learned

**Strategy:**
1. Design V2 architecture (all recommendations implemented)
2. Rewrite all agents, skills, tools
3. Migrate reference implementation
4. Beta testing with real projects
5. Production release

**Timeline:** 6-12 months

**Pros:**
- ✅ Clean architecture (no legacy baggage)
- ✅ Consistent design (all components follow same patterns)
- ✅ Optimized performance (built for efficiency from start)
- ✅ Fresh documentation (no outdated references)

**Cons:**
- ⚠️ High risk (big-bang release)
- ⚠️ Long timeline (no value until complete)
- ⚠️ Compatibility break (existing projects must migrate)
- ⚠️ Resource intensive (full team for 6-12 months)
- ⚠️ Unknown unknowns (may discover issues late)

**Verdict:** ⚠️ **NOT RECOMMENDED** (too risky for production)

---

### Option 3: Hybrid Approach

**Approach:** Rewrite core, keep periphery

**Strategy:**
1. **Rewrite core components:**
   - Agent framework (with modularization)
   - Skill loading system (with lazy loading)
   - Phase state management (with machine-readable format)
   - **Timeline:** 2-3 months

2. **Keep existing components:**
   - Agent instructions (migrate gradually)
   - Skill content (refactor as needed)
   - Standards library (unchanged)
   - Reference implementation (unchanged)

3. **Incremental migration:**
   - Migrate agents one-by-one to new framework
   - Refactor skills as agents are migrated
   - Full migration over 4-6 months

**Pros:**
- ✅ Balanced risk (core is new, content is migrated)
- ✅ Faster core improvements (2-3 months vs. 6-12 months)
- ✅ Gradual content migration (low-risk, incremental)
- ✅ Early value (new framework available quickly)

**Cons:**
- ⚠️ Dual maintenance (old and new systems coexist)
- ⚠️ Migration complexity (content must adapt to new framework)
- ⚠️ Potential rework (content may need significant changes)

**Verdict:** 🟡 **CONSIDER** if core framework is limiting (not evident yet)

---

### Option 4: Fork for Experimentation

**Approach:** Create experimental branch, keep main stable

**Strategy:**
1. Create `v2-experimental` branch
2. Implement all recommendations in experimental branch
3. Test with pilot projects
4. Merge to main if successful, abandon if not

**Timeline:** 3-6 months (parallel to main)

**Pros:**
- ✅ Zero risk to main (production unaffected)
- ✅ Freedom to experiment (can try radical ideas)
- ✅ Easy rollback (just delete branch)
- ✅ Parallel development (main continues evolving)

**Cons:**
- ⚠️ Branch divergence (merge conflicts accumulate)
- ⚠️ Duplicate effort (fixes must be applied to both branches)
- ⚠️ Feature freeze on main (can't add features until merge)
- ⚠️ "Big bang" merge (difficult integration at end)

**Verdict:** 🟡 **CONSIDER** if major uncertainty exists (not evident)

---

### Recommendation Matrix

| Option | Risk | Timeline | Value Delivery | Compatibility | Recommended? |
|--------|------|----------|----------------|---------------|--------------|
| **Option 1: Incremental** | 🟢 Low | 3-9 months | 🟢 Continuous | ✅ Full | ✅ **YES** |
| **Option 2: Rewrite** | 🔴 High | 6-12 months | 🔴 Delayed | ❌ Breaking | ❌ No |
| **Option 3: Hybrid** | 🟡 Medium | 4-9 months | 🟡 Phased | 🟡 Partial | 🟡 Maybe |
| **Option 4: Fork** | 🟢 Low | 3-6 months | 🔴 Delayed | ✅ Full | 🟡 Maybe |

**Final Recommendation:** **Option 1 (Incremental Refactoring)** is recommended for this project.

---

## 8. Open Questions

### 8.1 Project Goals & Scope

1. **What is the primary goal for V2 re-architecture?**
   - [ ] Improve performance (context usage, loading times)
   - [ ] Enhance maintainability (simpler agent definitions)
   - [ ] Add new features (multi-standard support, web dashboard)
   - [ ] Improve usability (easier onboarding, better UX)
   - [ ] Production hardening (CI/CD, tool qualification, external integrations)
   - [ ] All of the above
   - [ ] Something else: _______________________

2. **What is the target timeline for V2?**
   - [ ] Short-term (1-2 months) - quick wins only
   - [ ] Medium-term (3-6 months) - comprehensive improvements
   - [ ] Long-term (6-12 months) - strategic transformation
   - [ ] No specific timeline - continuous improvement

3. **What is the primary use case?**
   - [ ] Research/academic (proof-of-concept, papers)
   - [ ] Open-source community (broad adoption)
   - [ ] Commercial product (revenue-generating)
   - [ ] Internal tooling (specific company/team)
   - [ ] Demonstration/education (teaching EN 50128)

### 8.2 Technical Decisions

4. **Should we maintain backward compatibility?**
   - [ ] Yes, existing projects must work without changes
   - [ ] Partial, provide migration scripts
   - [ ] No, breaking changes acceptable for V2
   - [ ] Depends: ______________________

5. **What is the priority for large agent refactoring (COD, PM)?**
   - [ ] Critical (blocks other improvements)
   - [ ] High (should be done in V2.0)
   - [ ] Medium (can wait for V2.1)
   - [ ] Low (not a blocker)

6. **Should we support multiple safety standards in V2?**
   - [ ] Yes, multi-standard support is strategic priority
   - [ ] No, stay focused on EN 50128 for now
   - [ ] Add one more standard (which?): _______________
   - [ ] Undecided, need more research

7. **Is a web dashboard needed?**
   - [ ] Yes, critical for usability
   - [ ] Yes, but low priority (V3.0)
   - [ ] No, CLI is sufficient
   - [ ] Maybe, need user feedback first

8. **Should we integrate with external tools (DOORS, Jama)?**
   - [ ] Yes, essential for enterprise adoption
   - [ ] Yes, but low priority (V3.0)
   - [ ] No, standalone is better
   - [ ] Maybe, depends on customer demand

### 8.3 OpenCode Dependencies

9. **Are there any OpenCode limitations blocking us?**
   - [ ] Context window size (can't fit large agents)
   - [ ] Skill loading performance (too slow)
   - [ ] Agent communication (no inter-agent protocol)
   - [ ] Tool integration (missing needed tools)
   - [ ] No major limitations
   - [ ] Other: _______________________

10. **Should we contribute improvements back to OpenCode?**
    - [ ] Yes, propose agent modularization to OpenCode
    - [ ] Yes, propose lazy skill loading to OpenCode
    - [ ] Yes, propose structured agent communication to OpenCode
    - [ ] No, keep improvements internal
    - [ ] Undecided

### 8.4 Resource & Constraints

11. **What resources are available for V2 development?**
    - [ ] Solo developer (part-time)
    - [ ] Solo developer (full-time)
    - [ ] Small team (2-3 developers)
    - [ ] Large team (4+ developers)
    - [ ] Undecided

12. **Are there any constraints we should know about?**
    - [ ] Budget limitations
    - [ ] Timeline pressure (deadline: _________)
    - [ ] Regulatory requirements (certification needed)
    - [ ] Customer commitments (features promised)
    - [ ] None
    - [ ] Other: _______________________

### 8.5 User Feedback

13. **What feedback have users provided on V1?**
    - [ ] "Too complex, hard to learn"
    - [ ] "Agents are too slow"
    - [ ] "Missing features: _______"
    - [ ] "Documentation is unclear"
    - [ ] "Works great, no issues"
    - [ ] "Other: _______________________"
    - [ ] No user feedback yet

14. **What is the biggest pain point for current users?**
    - [ ] Onboarding (steep learning curve)
    - [ ] Performance (slow agent responses)
    - [ ] Reliability (agents make mistakes)
    - [ ] Features (missing capabilities)
    - [ ] Documentation (hard to find info)
    - [ ] Unknown (need user research)

---

## 9. Next Steps

### Immediate Actions (This Week)

1. **Review this document**
   - [ ] Read and discuss with team
   - [ ] Answer open questions (Section 8)
   - [ ] Prioritize recommendations (Section 6)

2. **Make strategic decisions**
   - [ ] Choose re-architecture option (Section 7)
   - [ ] Define V2 scope and timeline
   - [ ] Allocate resources

3. **Create V2 roadmap**
   - [ ] Select recommendations to implement
   - [ ] Sequence work (phases)
   - [ ] Estimate effort for each phase

### Short-Term (Next 2-4 Weeks)

4. **Start Phase 1 (Quick Wins)**
   - [ ] Recommendation 1: Agent decomposition (COD, PM)
   - [ ] Recommendation 2: Lazy skill loading
   - [ ] Recommendation 3: Tool registry
   - [ ] Recommendation 4: Machine-readable state
   - [ ] Recommendation 5: Automated traceability

5. **Set up infrastructure**
   - [ ] Create `v2-dev` branch
   - [ ] Set up CI/CD (Recommendation 7)
   - [ ] Document V2 architecture decisions

6. **User research** (if applicable)
   - [ ] Interview current users
   - [ ] Gather pain points
   - [ ] Validate priorities

### Medium-Term (Next 1-3 Months)

7. **Continue incremental improvements**
   - [ ] Complete Phase 1 recommendations
   - [ ] Start Phase 2 (infrastructure)
   - [ ] Migrate reference implementation to V2

8. **Documentation**
   - [ ] Update TUTORIAL.md for V2
   - [ ] Write V2 migration guide
   - [ ] Document new features

9. **Testing & Validation**
   - [ ] Beta test with pilot projects
   - [ ] Collect feedback
   - [ ] Refine based on feedback

### Long-Term (Next 3-12 Months)

10. **Phase 3 (Strategic Features)**
    - [ ] Multi-standard support (if prioritized)
    - [ ] Web dashboard (if prioritized)
    - [ ] External tool integrations (if prioritized)

11. **Production Release**
    - [ ] V2.0 release
    - [ ] Migration support for existing projects
    - [ ] User training/onboarding

12. **Continuous Improvement**
    - [ ] Monitor usage and performance
    - [ ] Collect feedback
    - [ ] Plan V2.1, V2.2, etc.

---

## Appendix: Reference Links

### Internal Documents
- [README.md](README.md) - Platform overview
- [AGENTS.md](AGENTS.md) - Agent definitions
- [LIFECYCLE.md](LIFECYCLE.md) - V-Model lifecycle
- [TUTORIAL.md](TUTORIAL.md) - Step-by-step guide
- [TOOLS.md](TOOLS.md) - Tool catalog

### EN 50128 Standards
- [std/EN50128-2011.md](std/EN50128-2011.md) - Main standard
- [std/EN 50126-1-2017.md](std/EN%2050126-1-2017.md) - RAMS Part 1
- [std/EN 50126-2-2017.md](std/EN%2050126-2-2017.md) - RAMS Part 2

### Reference Implementation
- [examples/train_door_control2/](examples/train_door_control2/) - SIL 3 project

### OpenCode Documentation
- [OpenCode Docs](https://opencode.ai/docs)
- [OpenCode GitHub](https://github.com/anomalyco/opencode)

---

**Last Updated**: 2026-03-07  
**Authors**: OpenCode Agent (Analysis), [Your Name] (Decisions)  
**Status**: Draft - Awaiting Decisions

---

**Next Action**: Please review this document and answer the questions in Section 8. We'll use your answers to finalize the V2 architecture plan.
