# EN 50128 Project - Next Steps

**Date:** 2026-02-06  
**Status:** Phase 1 Complete - Continue with Phase 2

---

## ✅ What We Accomplished Today

### 1. Standards Extraction and Documentation (COMPLETE)
- ✅ Extracted **Section 3.2 Abbreviations** → `std/EN50128-ABBREVIATIONS.md`
- ✅ Extracted **Tables A.6-A.11 and A.21** → `std/EN50128-TABLES-EXTRACTED.md`
- ✅ Extracted **Role Specifications** (Tables B.6, B.9, B.10) from Annex B
- ✅ Documented all official EN 50128 abbreviations (ASR, DES, IMP, INT, PM, etc.)

### 2. New Agent Commands Created (3/3 COMPLETE)
- ✅ **`.opencode/commands/int.md`** - Integrator Agent
  - Added Table A.6 (Integration techniques)
  - Added independence requirements for SIL 3-4
  - Added C language integration patterns
  - Added integration workflow and checklists
  
- ✅ **`.opencode/commands/pm.md`** - Project Manager Agent
  - Added independence requirements (critical: Validator independence)
  - Added role combination rules by SIL level
  - Added coordination workflows
  - Distinguished from Software Manager role
  
- ✅ **`.opencode/commands/cm.md`** - Configuration Manager Agent
  - Added Table A.9 (Quality Assurance - CM is mandatory for ALL SILs)
  - Added traceability requirements (mandatory SIL 3-4)
  - Added C language configuration management patterns
  - Added SCMP requirements and baselines

### 3. Existing Agent Commands Updated (2/7 COMPLETE)
- ✅ **`.opencode/commands/req.md`** - Requirements Engineer
  - Added complete Table A.2 with all 4 techniques
  - Updated standard references to `std/*.md`
  
- ✅ **`.opencode/commands/des.md`** - Designer  
  - Added complete Table A.3 with all 23 techniques
  - Added approved combinations for SIL 3-4 and SIL 1-2
  - Updated standard references to `std/*.md`
  - Fixed table reference (was A.4, now correct A.3)

### 4. Master Documentation Updates (COMPLETE)
- ✅ **`PROJECT_REVISION_STATUS.md`** - Updated with latest progress
- ✅ **`std/EN50128-ABBREVIATIONS.md`** - Created official abbreviations reference
- ✅ **`std/EN50128-TABLES-EXTRACTED.md`** - Created tables A.6-A.11, A.21 reference

---

## 📋 Remaining Work - Clear Action Items

### PHASE 2A: Complete Remaining Agent Commands (5 files)

#### Task 1: Update imp.md (Implementer)
**File:** `.opencode/commands/imp.md`  
**Current Issue:** References Table A.18 (incorrect)  
**Required Changes:**
1. Add complete **Table A.4** (Software Design and Implementation) with all 14 techniques
2. Add approved combination for SIL 3-4: `4, 5, 6, 8 + one from {1 or 2}`
3. Update standard references:
   - Change `Table A.18` to `Table A.4`
   - Add `std/EN50128-2011.md` line references
   - Add `std/EN50128-TABLES-EXTRACTED.md` reference
4. Add reference to `std/EN50128-ABBREVIATIONS.md`

**Table A.4 Content (from PROJECT_REVISION_STATUS.md):**
```
Key techniques:
- Structured Methodology (M for SIL 3-4)
- Modular Approach (M for SIL 2+)
- Design and Coding Standards (M for SIL 3-4)
- Analysable Programs (M for SIL 3-4)
- Structured Programming (M for SIL 3-4)

Approved combination (SIL 3-4): 4,5,6,8 + one from 1 or 2
```

#### Task 2: Update tst.md (Tester)
**File:** `.opencode/commands/tst.md`  
**Required Changes:**
1. Add **Table A.5** testing subset (extract from existing Table A.5):
   - Dynamic Analysis and Testing (M for SIL 3-4)
   - Test Coverage for Code (M for SIL 3-4)
   - Functional/Black-Box Testing (M for SIL 3-4)
   - Performance Testing (M for SIL 3-4)
   - Interface Testing (HR for all)
   
2. Add complete **Table A.21** (Test Coverage):
   ```
   | Coverage Type      | SIL 0 | SIL 1-2 | SIL 3-4 |
   |--------------------|-------|---------|---------|
   | Statement Coverage | HR    | HR      | M       |
   | Branch Coverage    | HR    | M       | M       |
   | Condition Coverage | -     | R       | M       |
   ```

3. Update standard references to `std/*.md`

#### Task 3: Update ver.md (Verifier)
**File:** `.opencode/commands/ver.md`  
**Required Changes:**
1. Add **Table A.5** verification subset:
   - Formal Proof (HR for SIL 3-4)
   - Static Analysis (M for SIL 3-4)
   - Metrics (HR for SIL 3-4)
   - Traceability (M for SIL 3-4)
   - Software Error Effect Analysis (HR for SIL 3-4)
   
2. Add **Table A.19** (Static Analysis techniques)

3. Add approved combination for SIL 3-4: `3, 5, 7, 8 + one from {1, 2, 6}`

4. Update standard references to `std/*.md`

#### Task 4: Update val.md (Validator)
**File:** `.opencode/commands/val.md`  
**Required Changes:**
1. Add **Table A.7** (Overall Software Testing):
   - Performance Testing (M for SIL 3-4)
   - Functional and Black-box Testing (M for SIL 3-4)
   - Modelling (R for SIL 3-4)

2. Add independence requirements from Section 5.1.2:
   - SHALL NOT report to Project Manager (SIL 3-4)
   - Makes independent release decision (Section 5.1.2.8)
   
3. Update standard references to `std/*.md`

#### Task 5: Update saf.md (Safety Engineer) and qua.md (Quality Assurance)
**File:** `.opencode/commands/saf.md`  
**Required Changes:**
1. Add **Table A.8** (Software Analysis Techniques):
   - Static Software Analysis (HR for SIL 3-4)
   - Dynamic Software Analysis (HR for SIL 3-4)
   - Software Error Effect Analysis (HR for SIL 3-4)
   
2. Update standard references to `std/*.md`

**File:** `.opencode/commands/qua.md`  
**Required Changes:**
1. Add complete **Table A.9** (Software Quality Assurance) - all 8 techniques
2. Emphasize mandatory techniques:
   - EN ISO 9001 Compliance (M for ALL SILs)
   - Company Quality System (M for ALL SILs)
   - Software Configuration Management (M for ALL SILs)
   - Traceability (M for SIL 3-4)
   - Data Recording and Analysis (M for SIL 3-4)
   
3. Update standard references to `std/*.md`

---

### PHASE 2B: Create New Skills (3 directories)

Create skill directories for the new agent commands:

#### Skill 1: Integration
**Directory:** `.opencode/skills/en50128-integration/`  
**Files to Create:**
```
en50128-integration/
├── SKILL.md - Overview and Table A.6
├── techniques.md - Integration techniques (functional testing, performance)
├── patterns.md - Progressive integration, bottom-up, top-down, sandwich
├── checklists.md - Integration quality checklist
└── examples.md - C language integration examples (if not examples/ directory)
```

#### Skill 2: Project Management
**Directory:** `.opencode/skills/en50128-project-management/`  
**Files to Create:**
```
en50128-project-management/
├── SKILL.md - Overview and independence requirements
├── organization.md - Organizational structures by SIL
├── planning.md - Lifecycle planning, phase planning
├── coordination.md - Role coordination, stakeholder management
└── checklists.md - Project management checklist
```

#### Skill 3: Configuration Management
**Directory:** `.opencode/skills/en50128-configuration/`  
**Files to Create:**
```
en50128-configuration/
├── SKILL.md - Overview and Table A.9 (CM mandatory for all SILs)
├── scmp.md - Software Configuration Management Plan
├── baselines.md - Baseline management, versioning
├── traceability.md - Traceability matrix (mandatory SIL 3-4)
├── change-control.md - Change request process
└── examples.md - C language version control examples
```

---

### PHASE 2C: Update Existing Skills (9 directories)

Each existing skill needs:
1. Add appropriate Table A.X reference in SKILL.md
2. Add technique implementations from extracted tables
3. Update standard references to `std/*.md`
4. Add C language specific examples

**Directories:**
1. `.opencode/skills/en50128-requirements/` - Add Table A.2
2. `.opencode/skills/en50128-design/` - Add Table A.3
3. `.opencode/skills/en50128-implementation/` - Add Table A.4
4. `.opencode/skills/en50128-testing/` - Add Table A.5 (testing) + Table A.21
5. `.opencode/skills/en50128-verification/` - Add Table A.5 (verification) + Table A.19
6. `.opencode/skills/en50128-validation/` - Add Table A.7
7. `.opencode/skills/en50128-safety/` - Add Table A.8
8. `.opencode/skills/en50128-quality/` - Add Table A.9
9. `.opencode/skills/en50128-documentation/` - Add all table references

---

### PHASE 2D: Update Master Documentation

#### Task 1: Update AGENTS.md
**File:** `AGENTS.md`  
**Required Changes:**
1. Add Integrator (INT) section after Tester
2. Add Project Manager (PM) section after Assessor
3. Add Configuration Manager (CM) section after Project Manager
4. Update agent workflow diagram to include new roles
5. Update agent interaction table

#### Task 2: Update README.md
**File:** `README.md`  
**Required Changes:**
1. Add 3 new commands to command list:
   - `/int` - Integrator
   - `/pm` - Project Manager
   - `/cm` - Configuration Manager
2. Update agent workflow examples
3. Update quick start guide

#### Task 3: Update LIFECYCLE.md (if needed)
**File:** `LIFECYCLE.md`  
**Required Changes:**
1. Verify Integration phase (Section 7.6) references Integrator role
2. Verify Configuration Management activities throughout lifecycle
3. Verify Project Manager coordination activities

---

### PHASE 2E: Verification and Quality

#### Task 1: Cross-Reference Verification
- [ ] Verify all EN 50128 section numbers are correct
- [ ] Verify all table references (A.1-A.23, B.1-B.10) are accurate
- [ ] Verify all file paths to `std/*.md` are correct
- [ ] Verify no broken links or missing references

#### Task 2: Terminology Alignment
- [ ] Check all abbreviations match `std/EN50128-ABBREVIATIONS.md`
- [ ] Verify consistent use of role names (DES, IMP, INT, PM, CM, etc.)
- [ ] Verify consistent use of document abbreviations (SRS, SAS, SDS, etc.)

#### Task 3: Completeness Check
- [ ] All 10 agent commands have technique tables
- [ ] All 12 skills exist and have content
- [ ] All standard references point to correct locations
- [ ] All approved combinations documented where applicable

---

## 🚀 Quick Start for Next Session

To continue this work efficiently, use this prompt:

```
Continue the EN 50128 project revision from NEXT_STEPS.md.

PHASE 2A: Complete remaining 5 agent command files:
1. Update imp.md - Add Table A.4, fix table reference (currently wrong)
2. Update tst.md - Add Table A.5 (testing subset) + Table A.21
3. Update ver.md - Add Table A.5 (verification subset) + Table A.19
4. Update val.md - Add Table A.7, independence requirements
5. Update saf.md and qua.md - Add Tables A.8 and A.9

Reference data location:
- Full Table A.2-A.5 in: PROJECT_REVISION_STATUS.md
- Tables A.6-A.11, A.21 in: std/EN50128-TABLES-EXTRACTED.md
- Official abbreviations in: std/EN50128-ABBREVIATIONS.md
- Standard location: std/EN50128-2011.md

After PHASE 2A, continue with PHASE 2B (create 3 new skills), then PHASE 2C (update 9 existing skills).
```

---

## 📊 Progress Tracking

### Overall Progress
- ✅ Phase 1: Standards Extraction - **100% COMPLETE**
- 🔄 Phase 2A: Agent Commands - **40% COMPLETE** (4/10 done)
- ⏳ Phase 2B: New Skills - **0% COMPLETE** (0/3 done)
- ⏳ Phase 2C: Update Existing Skills - **0% COMPLETE** (0/9 done)
- ⏳ Phase 2D: Master Documentation - **0% COMPLETE** (0/3 docs)
- ⏳ Phase 2E: Verification - **0% COMPLETE**

### Estimated Time Remaining
- Phase 2A: 1-2 hours (5 files)
- Phase 2B: 2 hours (3 skill sets)
- Phase 2C: 3-4 hours (9 skill updates)
- Phase 2D: 1 hour (3 documentation files)
- Phase 2E: 1 hour (verification)
- **Total: 8-10 hours**

---

## 📁 Key Files Created Today

1. `std/EN50128-ABBREVIATIONS.md` - Official EN 50128 abbreviations
2. `std/EN50128-TABLES-EXTRACTED.md` - Tables A.6-A.11, A.21
3. `.opencode/commands/int.md` - Integrator Agent
4. `.opencode/commands/pm.md` - Project Manager Agent
5. `.opencode/commands/cm.md` - Configuration Manager Agent
6. `NEXT_STEPS.md` - This file
7. Updated: `.opencode/commands/des.md` - Added Table A.3
8. Updated: `PROJECT_REVISION_STATUS.md` - Progress tracking

---

## 🔗 Quick Reference Links

### Tables Location
- **Tables A.2-A.5:** `PROJECT_REVISION_STATUS.md` (lines 133-241)
- **Tables A.6-A.11, A.21:** `std/EN50128-TABLES-EXTRACTED.md`
- **All Tables:** EN 50128:2011 Annex A - `std/EN50128-2011.md` (lines 4246+)

### Role Definitions
- **Annex B Tables B.1-B.10:** `std/EN50128-2011.md` Annex B
- **Section 5.1.2:** Independence Requirements - lines 1125-1248
- **Agent Roles:** `AGENTS.md`

### Standard References
- **Full Standard:** `std/EN50128-2011.md` (2.2 MB)
- **RAMS Part 1:** `std/EN 50126-1-2017.md` (293 KB)
- **RAMS Part 2:** `std/EN 50126-2-2017.md` (210 KB)

---

**Document Status:** Active Roadmap  
**Last Updated:** 2026-02-06  
**Next Session:** Continue with PHASE 2A (update remaining 5 agent commands)
