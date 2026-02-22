# QUA Integration: Visual Workflow Comparison

## BEFORE: QUA Integration Unclear

```
Phase 2: Requirements
┌──────────────────────────────────────────────────────────┐
│ REQ: Create SRS, RTM                                     │
│   ↓                                                      │
│ SAF: Hazard analysis                                     │
│   ↓                                                      │
│ VER: Independent verification ❌ (checks template here) │
│   ↓                                                      │
│ CM: Baseline                                             │
│   ↓                                                      │
│ COD: Gate check                                          │
└──────────────────────────────────────────────────────────┘

Problem: VER checks both technical AND template compliance
Risk: Template issues found late in verification process
```

---

## AFTER: QUA Quality Gate Before VER

```
Phase 2: Requirements
┌──────────────────────────────────────────────────────────┐
│ REQ: Create SRS, RTM                                     │
│   ↓                                                      │
│ SAF: Hazard analysis                                     │
│   ↓                                                      │
│ QUA: Template compliance check ✅ QUALITY GATE           │
│      - Document ID format                                │
│      - Document Control table                            │
│      - Approvals table                                   │
│      → Generate QA Template Compliance Report            │
│   ↓                                                      │
│ VER: Independent technical verification                  │
│      (assumes template compliance verified by QUA)       │
│   ↓                                                      │
│ CM: Baseline                                             │
│   ↓                                                      │
│ COD: Gate check (verifies QUA report exists)            │
└──────────────────────────────────────────────────────────┘

Benefit: QUA catches template issues early (quality gate)
Efficiency: VER focuses on technical verification only
```

---

## Complete Updated Workflow (All Phases)

```
┌─────────────────────────────────────────────────────────────────────┐
│                    PHASE 1: PLANNING                                │
├─────────────────────────────────────────────────────────────────────┤
│ PM/CM: Create SQAP, SCMP, SVP, SVaP                                │
│   ↓                                                                 │
│ QUA: Template compliance check ✅                                   │
│   ↓                                                                 │
│ VER: Technical verification                                         │
│   ↓                                                                 │
│ COD: Gate check → Phase 2                                          │
└─────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────┐
│                    PHASE 2: REQUIREMENTS                            │
├─────────────────────────────────────────────────────────────────────┤
│ REQ: Create SRS, RTM                                                │
│   ↓                                                                 │
│ SAF: Hazard analysis, safety requirements                           │
│   ↓                                                                 │
│ QUA: Template compliance check ✅ (MANDATORY SIL 3-4)               │
│      - SRS template compliance                                      │
│      - RTM template compliance                                      │
│      - Hazard Log template compliance                               │
│      - Test Spec template compliance                                │
│   ↓                                                                 │
│ VER: Independent technical verification                             │
│   ↓                                                                 │
│ CM: Requirements baseline                                           │
│   ↓                                                                 │
│ COD: Gate check → Phase 3                                          │
└─────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────┐
│                    PHASE 3: DESIGN                                  │
├─────────────────────────────────────────────────────────────────────┤
│ DES: Create SAS, SDS, ICD                                           │
│   ↓                                                                 │
│ SAF: FMEA/FTA, safety mechanisms                                    │
│   ↓                                                                 │
│ QUA: Template compliance + Design review ✅ (MANDATORY SIL 3-4)     │
│      - SAS/SDS/ICD template compliance                              │
│      - Complexity limits verification                               │
│      - Defensive programming patterns check                         │
│   ↓                                                                 │
│ VER: Independent technical verification                             │
│   ↓                                                                 │
│ CM: Design baseline                                                 │
│   ↓                                                                 │
│ COD: Gate check → Phase 4                                          │
└─────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────┐
│                    PHASE 4: IMPLEMENTATION                          │
├─────────────────────────────────────────────────────────────────────┤
│ IMP: Implement C code, unit tests                                  │
│   ↓                                                                 │
│ TST: Execute unit tests, measure coverage                           │
│   ↓                                                                 │
│ QUA: Code review ✅ (MANDATORY ALL SILS)                            │
│      - MISRA C:2012 compliance (zero mandatory violations SIL 2+)   │
│      - Complexity verification (≤10 SIL 3-4)                        │
│      - Defensive programming check                                  │
│      - Code documentation compliance                                │
│   ↓                                                                 │
│ VER: Static analysis, technical verification                        │
│   ↓                                                                 │
│ CM: Code baseline                                                   │
│   ↓                                                                 │
│ COD: Gate check → Phase 5                                          │
└─────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────┐
│                    PHASE 5: INTEGRATION                             │
├─────────────────────────────────────────────────────────────────────┤
│ INT: Integration testing, interface testing, performance testing   │
│   ↓                                                                 │
│ QUA: Integration test review ✅ (MANDATORY SIL 3-4)                 │
│      - Integration test spec template compliance                    │
│      - Integration test results documentation                       │
│   ↓                                                                 │
│ VER: Integration verification                                       │
│   ↓                                                                 │
│ CM: Integration baseline                                            │
│   ↓                                                                 │
│ COD: Gate check → Phase 6                                          │
└─────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────┐
│                    PHASE 6: VALIDATION                              │
├─────────────────────────────────────────────────────────────────────┤
│ VAL: System testing, UAT, safety validation                        │
│   ↓                                                                 │
│ QUA: Validation review ✅ (MANDATORY SIL 3-4)                       │
│      - Validation plan/report template compliance                   │
│      - UAT results documentation                                    │
│   ↓                                                                 │
│ VER: Validation verification                                        │
│   ↓                                                                 │
│ CM: Validation baseline                                             │
│   ↓                                                                 │
│ COD: Gate check → Phase 7                                          │
└─────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────┐
│                    PHASE 7: ASSESSMENT (SIL 3-4)                    │
├─────────────────────────────────────────────────────────────────────┤
│ Assessor: Independent assessment (mandatory SIL 3-4)                │
│   ↓                                                                 │
│ COD: Gate check → Phase 8 (Deployment)                             │
└─────────────────────────────────────────────────────────────────────┘

Legend:
  ✅ = QUA quality gate checkpoint (BEFORE VER)
  SIL 3-4 = MANDATORY for SIL 3-4 projects (strict enforcement)
  ALL SILS = MANDATORY for ALL SIL levels (0, 1, 2, 3, 4)
```

---

## QUA Checkpoint Summary by Phase

| Phase | QUA Activity | When | Output | SIL Requirement |
|-------|--------------|------|--------|-----------------|
| **1** | Template compliance | After PM/CM, BEFORE VER | QA Template Compliance Report | SIL 3-4: M |
| **2** | Template compliance | After REQ/SAF, BEFORE VER | QA Template Compliance Report | SIL 3-4: M |
| **3** | Template + Design review | After DES/SAF, BEFORE VER | QA Template + Design Review Report | SIL 3-4: M |
| **4** | Code review | After IMP/TST, BEFORE VER | QA Code Review Report | ALL: M |
| **5** | Integration test review | After INT, BEFORE VER | QA Integration Test Review Report | SIL 3-4: M |
| **6** | Validation review | After VAL, BEFORE VER | QA Validation Review Report | SIL 3-4: M |

**M** = Mandatory

---

## Key Principles

### 1. QUA as Quality Gate
```
Document → QUA (template check) → VER (technical check) → Baseline
              ↑
         Quality Gate
     (catches admin issues)
```

### 2. Separation of Concerns
- **QUA**: Administrative compliance (template, format, structure)
- **VER**: Technical compliance (requirements, design, code quality)

### 3. Fail-Fast Principle
- Catch template issues EARLY (at QUA gate)
- Don't waste VER effort on non-compliant documents
- Reduce rework cycles

### 4. Independence Preserved
- QUA is independent quality function
- VER is independent verification function (SIL 3-4)
- Both report independently (QUA → PM, VER → COD/Safety Authority)

---

## Efficiency Comparison

### BEFORE (VER checks everything)
```
Document created → Wait for VER → VER finds template issue → Rework → Re-verify
                   ↑─────────── WASTE ──────────↑
Time: Document (1 day) + VER wait (2 days) + VER review (1 day) + Rework (0.5 day) + Re-verify (0.5 day) = 5 days
```

### AFTER (QUA quality gate)
```
Document created → QUA template check (0.5 day) → Fix template issue (0.2 day) → 
VER technical check (1 day) → Done
                   ↑─ FAST FEEDBACK ─↑
Time: Document (1 day) + QUA check (0.5 day) + Fix (0.2 day) + VER (1 day) = 2.7 days
```

**Savings**: 2.3 days per document (46% faster)

---

## Workflow Invocation Summary

### Phase 2 Example (Requirements)
```bash
# Create requirements
/req
# Outputs: SRS.md, RTM.md

# Safety analysis
/saf
# Outputs: Hazard-Log.md

# Test specification
/tst
# Outputs: Overall-Test-Spec.md

# QUA template compliance check (BEFORE VER) ← NEW
/qua
# Checks: SRS, RTM, Hazard-Log, Test-Spec templates
# Output: QA-Template-Compliance-Report.md

# Independent verification (assumes templates OK)
/ver
# Checks: Technical correctness, traceability, safety
# Output: Requirements-Verification.md

# Baseline
/cm
# Creates: Baseline 1 (Requirements)

# Gate check
/cod gate-check requirements
# Verifies: All deliverables including QA report
```

---

## COD Gate Check Changes

### BEFORE
```
/cod gate-check requirements
→ Checks: SRS exists, RTM exists, Hazard Log exists
→ Passes if documents present and approved
```

### AFTER
```
/cod gate-check requirements
→ Checks: 
  - SRS exists ✓
  - RTM exists ✓
  - Hazard Log exists ✓
  - QA Template Compliance Report exists ✓ (NEW - SIL 3-4: MANDATORY)
  - All documents approved ✓
→ BLOCKS if QA report missing (SIL 3-4 strict mode)
```

---

## Conclusion

**Problem Solved**: ✅ QUA template compliance checks now explicitly integrated BEFORE VER verification

**Benefits**:
1. ✅ Earlier defect detection (quality gate)
2. ✅ Clearer workflow (explicit checkpoints)
3. ✅ Reduced rework (fail-fast principle)
4. ✅ Better compliance (EN 50128 Section 6.5)
5. ✅ Improved efficiency (46% faster - see comparison)

**Implementation Status**: ✅ COMPLETE
- LIFECYCLE.md updated (all phases)
- AGENTS.md workflow updated
- qua.md agent specification updated

**Next Action**: Apply updated workflow starting Phase 3 for train_door_control2 project
