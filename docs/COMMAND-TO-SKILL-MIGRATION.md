# Command to Skill Migration Guide

**Version**: 1.0  
**Date**: 2026-03-15  
**Status**: ACTIVE - All commands deprecated

---

## Executive Summary

**All role-based commands have been deprecated** in favor of direct skill invocation. This transition completes the architecture transformation to a **document-centric workflow** as originally intended.

**Migration Path**: Commands (`.opencode/commands/*.md`) → Skills (`.opencode/skills/en50128-*/`)

---

## Why This Change?

### Original Goal (Architecture Transformation)

> "Role-centric implementation employ commands, e.g. /imp, /des, to perform roles actions. However, skills specified in commands will not be invoked properly. Thus, we should investigate roles definitions, behaviors and skills in commands and merge into agents and skills. **Commands for roles can be obsolated.**"

### Problems with Old Approach

1. **❌ Commands were role-centric** - Users invoked `/req`, `/des`, `/imp` commands
2. **❌ Skills were not auto-invoked** - Commands referenced skills but didn't load them
3. **❌ Duplication** - Behaviors defined in both commands and skills
4. **❌ Not document-centric** - Users still thought in terms of "roles" not "deliverables"

### Benefits of New Approach

1. **✅ Document-centric** - Focus on deliverables (SRS, SAS, SDS), not roles
2. **✅ Skills are primary** - All workflows, templates, tools in skills
3. **✅ No duplication** - Single source of truth (skills)
4. **✅ Clean architecture** - Aligns with EN 50128 deliverable-focused approach

---

## Migration Reference

### Command → Skill Mapping

| OLD (Deprecated Command) | NEW (Skill) | Description |
|--------------------------|-------------|-------------|
| `/req` | `en50128-requirements` | Requirements Engineering |
| `/des` | `en50128-design` | Architecture and Design |
| `/imp` | `en50128-implementation` | C Implementation |
| `/tst` | `en50128-testing` | Software Testing |
| `/ver` | `en50128-verification` | Software Verification |
| `/val` | `en50128-validation` | Software Validation |
| `/int` | `en50128-integration` | Software Integration |
| `/qua` | `en50128-quality` | Quality Assurance |
| `/saf` | `en50128-safety` | Safety Analysis |
| `/cm` | `en50128-configuration` | Configuration Management |
| `/pm` | `en50128-project-management` | Project Management |
| `/cod` | `en50128-lifecycle-coordination` | Lifecycle Coordination |
| `/vmgr` | `en50128-vv-management` (planned) | V&V Management |

### Utility Commands

| OLD Command | NEW Approach | Notes |
|-------------|--------------|-------|
| `/workspace` | Direct tool usage | Use `tools/workspace.py` or `python3 tools/workspace.py` |
| `/enhelp` | Direct tool usage | Use `tools/enhelp.py` or `python3 tools/enhelp.py` |
| `/pdf2md` | Direct tool usage | Use `tools/pdf-conversion/` scripts |

---

## How to Use Skills

### Method 1: Skill Tool (Recommended)

Load skills using the skill tool:

```
Load skill: en50128-requirements
```

This automatically loads:
- Complete workflows
- Document templates
- Tool integration examples
- EN 50128 standard references
- SIL-specific guidance

### Method 2: Direct File Access

If needed, reference skill files directly:
- **Skill Definition**: `.opencode/skills/en50128-requirements/SKILL.md`
- **Workflows**: `.opencode/skills/en50128-requirements/workflows/`
- **Templates**: `.opencode/skills/en50128-requirements/templates/`
- **Reports**: `.opencode/skills/en50128-requirements/reports/`

---

## Migration Examples

### Example 1: Requirements Engineering

**OLD Approach** (Deprecated):
```
User: "I need to create a Software Requirements Specification"
Agent: "I'll use the /req command"
Result: Command file loaded (21K), skill not auto-loaded
```

**NEW Approach** (Current):
```
User: "I need to create a Software Requirements Specification"
Agent: "I'll load the en50128-requirements skill"
Result: Skill loaded with complete workflows, templates, tools
```

### Example 2: Design

**OLD Approach** (Deprecated):
```
User: "Help me design the software architecture"
Agent: "I'll use the /des command"
Result: Command file loaded (23K), skill referenced but not loaded
```

**NEW Approach** (Current):
```
User: "Help me design the software architecture"
Agent: "I'll load the en50128-design skill"
Result: Skill loaded with architecture patterns, MISRA C design guidance, defensive programming
```

### Example 3: Implementation

**OLD Approach** (Deprecated):
```
User: "I need to implement this module in C"
Agent: "I'll use the /imp command"
Result: Command file loaded (19K), skill not loaded
```

**NEW Approach** (Current):
```
User: "I need to implement this module in C"
Agent: "I'll load the en50128-implementation skill"
Result: Skill loaded with C coding patterns, MISRA C compliance checks, unit testing workflows
```

---

## What Changed in Each Skill

All 13 skills have been enhanced with comprehensive workflows, templates, and tool integration:

### 1. en50128-requirements (160 pages, 7 files)
- **Workflows**: Requirements elicitation, SIL assignment, traceability management
- **Tools**: workspace.py trace (60+ examples)
- **Templates**: Software Requirements Specification, RTM, Hazard Log
- **EN 50128**: Section 7.2, Table A.2

### 2. en50128-design (310 pages, 10 files)
- **Workflows**: Architecture design, detailed design, defensive programming
- **Tools**: workspace.py trace (40+ examples)
- **Templates**: Software Architecture Specification, Software Design Specification
- **EN 50128**: Section 7.3, Table A.3, Table A.4

### 3. en50128-implementation (340 pages, 9 files)
- **Workflows**: C implementation, MISRA C compliance, unit testing
- **Tools**: workspace.py wf, check_misra.py (30+ examples)
- **Templates**: Source code templates, unit test templates
- **EN 50128**: Section 7.4, Table A.4, Table A.12

### 4. en50128-verification (400 pages, 11 files)
- **Workflows**: Static analysis, verification reporting, evidence collection
- **Tools**: cppcheck, clang, lizard, workspace.py (50+ examples)
- **Templates**: 11 verification report templates
- **EN 50128**: Section 6.2, Table A.5, Table A.19

### 5. en50128-testing (260 pages, 4 files)
- **Workflows**: Unit testing, integration testing, coverage analysis
- **Tools**: gcov, lcov, mcdc_analyzer.py, workspace.py (40+ examples)
- **Templates**: Test specifications, test reports
- **EN 50128**: Sections 7.4, 7.5, Table A.5, Table A.21

### 6. en50128-integration (335 pages, 5 files)
- **Workflows**: Progressive integration, HW/SW integration, HIL testing
- **Tools**: workspace.py trace/wf (35+ examples)
- **Templates**: Integration test specifications, integration reports
- **EN 50128**: Section 7.6, Table A.6

### 7. en50128-validation (335 pages, 4 files)
- **Workflows**: System validation, acceptance testing, operational validation
- **Tools**: workspace.py trace/wf (30+ examples)
- **Templates**: Validation specifications, validation reports
- **EN 50128**: Section 7.7, Table A.7

### 8. en50128-quality (248 pages, 5 files)
- **Workflows**: SQAP, quality gates, document review, technical review, audits
- **Tools**: workspace.py wf (50+ examples)
- **Templates**: SQAP, review checklists, quality reports
- **EN 50128**: Section 6.5, Table A.9

### 9. en50128-safety (350 pages, 5 files)
- **Workflows**: Hazard analysis, FMEA, FTA, CCF, safety case
- **Tools**: workspace.py trace (40+ examples)
- **Templates**: Hazard Log, FMEA templates, FTA templates
- **EN 50128**: Section 7.1, Section 6.3, Table A.8

### 10. en50128-lifecycle-coordination (300 pages, 5 files)
- **Workflows**: V-Model orchestration, phase gates, traceability, iterations
- **Tools**: workspace.py trace/wf (75+ examples)
- **Templates**: LIFECYCLE_STATE.md, phase transition checklists
- **EN 50128**: Section 5.3, Annex C

### 11. en50128-configuration (213 pages, 5 files)
- **Workflows**: Version control, change control, baselines, PCA/FCA audits
- **Tools**: Git, workspace.py (60+ examples)
- **Templates**: SCMP, change request forms, baseline checklists
- **EN 50128**: Section 6.6, Table A.9

### 12. en50128-documentation (177 pages, 5 files)
- **Workflows**: Document creation, document review, document automation
- **Tools**: workspace.py wf (30+ examples)
- **Templates**: All EN 50128 Annex C documents
- **EN 50128**: Section 6.1, Annex C

### 13. en50128-tools (183 pages, 5 files)
- **Workflows**: Tool qualification, tool selection, tool validation
- **Tools**: Tool validation scripts (40+ examples)
- **Templates**: Tool Qualification Report, Tool Validation Report
- **EN 50128**: Section 6.7

---

## Archived Command Files

All deprecated command files have been moved to `.opencode/commands-deprecated/` for historical reference:

```
.opencode/commands-deprecated/
├── README.md (explains deprecation)
├── req.md (21K)
├── des.md (23K)
├── imp.md (19K)
├── tst.md (34K)
├── ver.md (51K)
├── val.md (51K)
├── int.md (25K)
├── qua.md (34K)
├── saf.md (24K)
├── cm.md (18K)
├── pm.md (56K)
├── cod.md (96K)
├── vmgr.md (21K)
├── workspace.md (23K)
├── enhelp.md (7.5K)
├── pdf2md.md (6K)
└── _workspace-awareness.md (6.5K)

Total: 17 command files (historical reference only)
```

**DO NOT USE** these files. They are archived for historical reference only.

---

## Document-Centric Workflow

### Old Mindset (Role-Centric)

```
User thinks: "I need a Requirements Engineer"
User invokes: /req
Result: Role-based command loaded
```

### New Mindset (Document-Centric)

```
User thinks: "I need to create a Software Requirements Specification"
User invokes: en50128-requirements skill
Result: Complete SRS workflow loaded with templates, tools, EN 50128 guidance
```

### Focus on Deliverables, Not Roles

EN 50128 is **deliverable-focused** (see Annex C Table C.1). The new architecture aligns with this:

| Lifecycle Phase | EN 50128 Deliverable | Skill to Use |
|-----------------|----------------------|--------------|
| Phase 1: Planning | SQAP, SCMP, SVP, SVaP | `en50128-quality`, `en50128-configuration` |
| Phase 2: Requirements | Software Requirements Specification, Hazard Log, RTM | `en50128-requirements`, `en50128-safety` |
| Phase 3: Design | Software Architecture Specification, Software Design Specification | `en50128-design` |
| Phase 4: Implementation | Source Code, Unit Tests | `en50128-implementation`, `en50128-testing` |
| Phase 5: Integration | Integration Tests | `en50128-integration`, `en50128-testing` |
| Phase 6: Validation | Validation Report | `en50128-validation` |
| Phase 7: Assessment | Assessment Report | `en50128-validation` (independent assessor) |
| Phase 8: Deployment | Release Package | `en50128-configuration` |

---

## Tool Integration

All skills include comprehensive tool integration examples:

### Traceability Management (workspace.py trace)

```bash
# Create traceability database
python3 tools/workspace.py trace create --sil 3

# Add requirement
python3 tools/workspace.py trace add \
  --id REQ-SYS-001 \
  --type system_requirement \
  --description "System shall detect door obstacles" \
  --sil 3

# Validate traceability (100% required for SIL 3+)
python3 tools/workspace.py trace validate
```

### Workflow Management (workspace.py wf)

```bash
# Submit document for review
python3 tools/workspace.py wf submit \
  --doc-id DOC-SRS-2026-001 \
  --doc-path docs/Software-Requirements-Specification.md \
  --phase requirements \
  --submitter "Requirements Engineer" \
  --sil 3

# Review document
python3 tools/workspace.py wf review \
  --doc-id DOC-SRS-2026-001 \
  --reviewer "Quality Assurance" \
  --decision approve \
  --comments "SRS meets all EN 50128 Section 7.2 requirements"
```

### Static Analysis (check_misra.py, cppcheck)

```bash
# MISRA C compliance check (SIL 2+)
python3 tools/static-analysis/check_misra.py \
  --src src/ \
  --sil 3 \
  --report docs/reports/MISRA-C-Report.md

# Cppcheck static analysis (MANDATORY SIL 3+)
cppcheck --enable=all --xml --xml-version=2 \
  src/ 2> docs/reports/cppcheck-report.xml
```

### Coverage Analysis (gcov, lcov)

```bash
# Compile with coverage instrumentation
gcc -fprofile-arcs -ftest-coverage -o test test.c module.c

# Run tests
./test

# Generate coverage report
gcov module.c
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory docs/reports/coverage/

# Verify 100% coverage (MANDATORY SIL 3+)
# Statement: 100%, Branch: 100%, Condition: 100%
```

---

## Frequently Asked Questions

### Q1: Can I still use `/req`, `/des`, etc.?

**A**: No, these commands have been deprecated. Use skills directly.

### Q2: Where did the command files go?

**A**: They are archived in `.opencode/commands-deprecated/` for historical reference only.

### Q3: What if I need the old command behavior?

**A**: All command behaviors have been **merged into skills**. Skills provide the same (and enhanced) functionality.

### Q4: How do I know which skill to use?

**A**: See the "Command → Skill Mapping" table above, or consult `AGENTS.md` "Agent-to-Skill Mapping" section.

### Q5: Will there be new commands in the future?

**A**: No. The platform is now **skill-based** and **document-centric**. Any new capabilities will be added to skills, not commands.

### Q6: What about workspace.py and enhelp.py?

**A**: These are **tools**, not role commands. Continue to use them directly:
- `python3 tools/workspace.py <subcommand>`
- `python3 tools/enhelp.py <topic>`

### Q7: How do I transition my existing projects?

**A**: No changes needed for existing projects. Only the **invocation method** changed (commands → skills). All deliverables, traceability, and workflows remain the same.

### Q8: What if I find a bug in a skill?

**A**: Report issues to the platform maintainer. Skills are the **single source of truth** and are actively maintained.

---

## Summary of Changes

| Aspect | OLD (Deprecated) | NEW (Current) |
|--------|------------------|---------------|
| **Invocation** | `/req`, `/des`, `/imp` commands | Load skills: `en50128-requirements`, `en50128-design`, `en50128-implementation` |
| **Location** | `.opencode/commands/*.md` | `.opencode/skills/en50128-*/` |
| **Focus** | Role-centric (who does it) | Document-centric (what is delivered) |
| **Behaviors** | Duplicated in commands and skills | Single source: skills only |
| **Skill Loading** | Manual reference, not auto-loaded | Skills are primary, load directly |
| **Content Size** | Commands: ~500K (17 files) | Skills: ~144K lines (80 files, 13 skills) |
| **Tool Integration** | Limited examples | 800+ tool command examples |
| **EN 50128 Coverage** | Basic references | Complete coverage: Sections 5-7, Annexes A-C, all technique tables |

---

## Next Steps

1. **Familiarize yourself with skills** - Browse `.opencode/skills/` directory
2. **Use the skill tool** - Load skills using skill tool invocation
3. **Focus on deliverables** - Think "what document do I need?" not "what role do I need?"
4. **Leverage tool integration** - Use workspace.py trace/wf commands extensively
5. **Follow EN 50128** - Skills enforce all EN 50128 Section 5-7 requirements

---

## Related Documents

- **`AGENTS.md`** - Updated with skill-based invocation (command references removed)
- **`docs/ARCHITECTURE-TRANSFORMATION-GAP-ANALYSIS.md`** - Analysis that led to this decision
- **`docs/phase3-plan.md`** - Phase 3 plan (tool implementation + sample project)
- **`.opencode/commands-deprecated/README.md`** - Explanation of command deprecation
- **`.opencode/skills/*/SKILL.md`** - Skill definitions for all 13 skills

---

**END OF MIGRATION GUIDE**
