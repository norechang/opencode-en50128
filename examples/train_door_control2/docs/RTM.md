# Requirements Traceability Matrix (RTM)

**Document ID**: DOC-RTM-2026-001  
**Version**: 1.0  
**Date**: 2026-02-19  
**Project**: train_door_control2  
**SIL Level**: 3  
**Author**: Requirements Engineer (REQ)  
**Status**: Draft

---

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-02-19 | REQ Engineer | Initial RTM based on SRS v1.0 | - |
| 1.0 | TBD | REQ Engineer | First approved version | TBD |

---

## 1. PURPOSE

This Requirements Traceability Matrix (RTM) provides bidirectional traceability between:
- **System Requirements** → **Software Requirements** → **Design** → **Code** → **Tests**

The RTM ensures:
1. **Forward Traceability**: Every requirement is implemented and tested
2. **Backward Traceability**: Every design, code module, and test traces to a requirement
3. **Completeness**: 100% coverage (mandatory for SIL 3 per EN 50128)
4. **Impact Analysis**: Changes to requirements can be tracked to affected design/code/tests

---

## 2. TRACEABILITY STATUS SUMMARY

| Category | Total | Traced to System | Traced to Design | Traced to Code | Traced to Tests | Complete |
|----------|-------|-----------------|------------------|----------------|-----------------|----------|
| **Functional** | 14 | 14 | 0 (Phase 3) | 0 (Phase 4) | 0 (Phase 4) | 28% |
| **Performance** | 6 | 6 | 0 (Phase 3) | 0 (Phase 4) | 0 (Phase 4) | 28% |
| **Interface - HW** | 12 | 12 | 0 (Phase 3) | 0 (Phase 4) | 0 (Phase 4) | 28% |
| **Interface - SW** | 1 | 1 | 0 (Phase 3) | 0 (Phase 4) | 0 (Phase 4) | 28% |
| **Interface - UI** | 1 | 1 | 0 (Phase 3) | 0 (Phase 4) | 0 (Phase 4) | 28% |
| **Safety** | 6 | 6 | 0 (Phase 3) | 0 (Phase 4) | 0 (Phase 4) | 28% |
| **Implementation** | 10 | 10 | 0 (Phase 3) | 0 (Phase 4) | 0 (Phase 4) | 28% |
| **TOTAL** | **50** | **50** | **0** | **0** | **0** | **28%** |

**Note**: As of 2026-02-19, we are in **Phase 2 (Requirements)**. Design, code, and tests will be added in subsequent phases.

**Traceability Target**: 100% complete by Phase 6 (Validation)

---

## 3. TRACEABILITY MATRIX

### 3.1 Functional Requirements Traceability

| SW Req ID | System Req | Hazard | Priority | SIL | Design Module | Code File | Test Cases | Status |
|-----------|-----------|--------|----------|-----|---------------|-----------|------------|--------|
| **REQ-FUNC-001** | SYS-REQ-001 | - | High | 3 | TBD (Phase 3) | TBD (Phase 4) | TBD (Phase 4) | ⚠️ Partial (System only) |
| **REQ-FUNC-002** | SYS-REQ-002 | - | High | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-FUNC-003** | SYS-REQ-003 | HAZ-001 | Critical | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-FUNC-004** | SYS-REQ-004 | HAZ-003 | Critical | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-FUNC-005** | SYS-REQ-005 | - | High | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-FUNC-006** | SYS-REQ-006 | - | High | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-FUNC-007** | SYS-REQ-007 | HAZ-002 | Critical | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-FUNC-008** | SYS-REQ-008 | HAZ-002 | Critical | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-FUNC-009** | SYS-REQ-009 | HAZ-002 | Critical | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-FUNC-010** | SYS-REQ-010 | - | High | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-FUNC-011** | SYS-REQ-011 | - | Medium | 0 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-FUNC-012** | SYS-REQ-012 | - | Critical | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-FUNC-013** | SYS-REQ-013 | - | Low | 0 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-FUNC-014** | SYS-REQ-014 | - | Critical | 3 | TBD | TBD | TBD | ⚠️ Partial |

---

### 3.2 Performance Requirements Traceability

| SW Req ID | System Req | Priority | SIL | Design Module | Code File | Test Cases | Status |
|-----------|-----------|----------|-----|---------------|-----------|------------|--------|
| **REQ-PERF-001** | SYS-PERF-001 | High | 3 | TBD (Phase 3) | TBD (Phase 4) | TBD (Phase 4) | ⚠️ Partial |
| **REQ-PERF-002** | SYS-PERF-002 | High | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-PERF-003** | SYS-PERF-003 | High | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-PERF-004** | SYS-PERF-004 | Critical | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-PERF-005** | SYS-PERF-005 | Medium | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-PERF-006** | SYS-PERF-006 | High | 3 | TBD | TBD | TBD | ⚠️ Partial |

---

### 3.3 Interface Requirements Traceability (Hardware)

| SW Req ID | System Req | Priority | SIL | Design Module | Code File | Test Cases | Status |
|-----------|-----------|----------|-----|---------------|-----------|------------|--------|
| **REQ-IF-HW-001** | SYS-IF-001 | High | 3 | TBD (Phase 3) | TBD (Phase 4) | TBD (Phase 4) | ⚠️ Partial |
| **REQ-IF-HW-002** | SYS-IF-002 | High | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-IF-HW-003** | SYS-IF-003 | High | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-IF-HW-004** | SYS-IF-004 | High | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-IF-HW-005** | SYS-IF-005 | Critical | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-IF-HW-006** | SYS-IF-006 | Critical | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-IF-HW-007** | SYS-IF-007 | Critical | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-IF-HW-008** | SYS-IF-008 | Critical | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-IF-HW-009** | SYS-IF-009 | High | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-IF-HW-010** | SYS-IF-010 | Low | 0 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-IF-HW-011** | SYS-IF-011 | Critical | 3 | TBD | TBD | TBD | ⚠️ Partial |
| **REQ-IF-HW-012** | SYS-IF-012 | Critical | 3 | TBD | TBD | TBD | ⚠️ Partial |

---

### 3.4 Interface Requirements Traceability (Software & UI)

| SW Req ID | System Req | Priority | SIL | Design Module | Code File | Test Cases | Status |
|-----------|-----------|----------|-----|---------------|-----------|------------|--------|
| **REQ-IF-SW-001** | SYS-IF-020 | High | 3 | TBD (Phase 3) | TBD (Phase 4) | TBD (Phase 4) | ⚠️ Partial |
| **REQ-IF-UI-001** | SYS-IF-030 | Low | 0 | TBD | TBD | TBD | ⚠️ Partial |

---

### 3.5 Safety Requirements Traceability

| SW Req ID | System Req | Hazard | Priority | SIL | Design Module | Code File | Test Cases | Safety Analysis | Status |
|-----------|-----------|--------|----------|-----|---------------|-----------|------------|----------------|--------|
| **REQ-SAFE-001** | SYS-REQ-003 | HAZ-001 | Critical | 3 | TBD (Phase 3) | TBD (Phase 4) | TBD (Phase 4) | TBD (FMEA, FTA) | ⚠️ Partial |
| **REQ-SAFE-002** | SYS-REQ-008 | HAZ-002 | Critical | 3 | TBD | TBD | TBD | TBD (FMEA) | ⚠️ Partial |
| **REQ-SAFE-003** | SYS-REQ-003 | HAZ-001 | Critical | 3 | TBD | TBD | TBD | TBD (FMEA) | ⚠️ Partial |
| **REQ-SAFE-004** | SYS-REQ-004 | HAZ-003 | Critical | 3 | TBD | TBD | TBD | TBD (FMEA) | ⚠️ Partial |
| **REQ-SAFE-005** | SYS-REQ-009 | HAZ-002 | Critical | 3 | TBD | TBD | TBD | TBD (FMEA) | ⚠️ Partial |
| **REQ-SAFE-006** | Multiple | HAZ-001, HAZ-002 | Critical | 3 | TBD | TBD | TBD | TBD (FMEA) | ⚠️ Partial |

---

### 3.6 Implementation Constraints Traceability

| SW Req ID | EN 50128 Ref | Priority | SIL | Verification Method | Tools | Status |
|-----------|-------------|----------|-----|---------------------|-------|--------|
| **REQ-IMPL-001** | Table A.4 | High | 3 | Static Analysis | PC-lint Plus, Cppcheck | ⚠️ Partial (Phase 4) |
| **REQ-IMPL-002** | MISRA C 4.6 | High | 3 | Static Analysis, Review | PC-lint, grep | ⚠️ Partial |
| **REQ-IMPL-003** | Table A.4 | Critical | 3 | Static Analysis, Review | grep, linker config | ⚠️ Partial |
| **REQ-IMPL-004** | Table A.4 | High | 3 | Static Analysis | Call graph analysis | ⚠️ Partial |
| **REQ-IMPL-005** | Table A.4 | High | 3 | Static Analysis | Lizard, PC-lint | ⚠️ Partial |
| **REQ-IMPL-006** | Table A.3 | High | 3 | Code Review, Analysis | Manual review, Cppcheck | ⚠️ Partial |
| **REQ-IMPL-007** | Best Practices | High | 3 | Code Review | Manual review | ⚠️ Partial |
| **REQ-IMPL-008** | MISRA C | Medium | 3 | Code Review, Analysis | PC-lint | ⚠️ Partial |
| **REQ-IMPL-009** | MISRA C | Medium | 3 | Code Review | Manual review | ⚠️ Partial |
| **REQ-IMPL-010** | MISRA C | Medium | 3 | Code Review, Analysis | PC-lint | ⚠️ Partial |

---

## 4. HAZARD TO REQUIREMENT MAPPING

This section provides reverse traceability from identified hazards to mitigating requirements.

| Hazard ID | Hazard Description | Risk Level | Mitigating SW Requirements | Status |
|-----------|-------------------|------------|---------------------------|--------|
| **HAZ-001** | Doors open while train is moving | Catastrophic | REQ-FUNC-003, REQ-SAFE-001, REQ-SAFE-003, REQ-SAFE-006, REQ-IF-HW-007, REQ-IF-HW-008 | ⚠️ Requirements Defined (Safety Analysis Pending) |
| **HAZ-002** | Doors close on passenger causing injury | Critical | REQ-FUNC-002, REQ-FUNC-007, REQ-FUNC-009, REQ-SAFE-002, REQ-SAFE-005, REQ-SAFE-006, REQ-IF-HW-005, REQ-IF-HW-006, REQ-PERF-004 | ⚠️ Requirements Defined (Safety Analysis Pending) |
| **HAZ-003** | Passengers trapped during emergency | Critical | REQ-FUNC-004, REQ-SAFE-004, REQ-IF-HW-012 | ⚠️ Requirements Defined (Safety Analysis Pending) |

**Note**: Detailed hazard analysis (FMEA, FTA) will be performed by Safety Engineer (/saf) in Phase 2.

---

## 5. REQUIREMENTS COVERAGE ANALYSIS

### 5.1 Forward Traceability (Requirements → Implementation)

| Traceability Link | Target | Current | Percentage | Status |
|-------------------|--------|---------|------------|--------|
| SW Req → Design | 50 | 0 | 0% | ⚠️ Phase 3 (Architecture & Design) |
| SW Req → Code | 50 | 0 | 0% | ⚠️ Phase 4 (Implementation) |
| SW Req → Tests | 50 | 0 | 0% | ⚠️ Phase 4 (Testing) |

### 5.2 Backward Traceability (Implementation → Requirements)

| Traceability Link | Status |
|-------------------|--------|
| Design → SW Req | ⚠️ Phase 3 (Architecture & Design) |
| Code → SW Req | ⚠️ Phase 4 (Implementation) |
| Tests → SW Req | ⚠️ Phase 4 (Testing) |

### 5.3 SIL 3 Requirements Coverage

| SIL Level | Count | Traced to System | Traced to Design | Traced to Code | Traced to Tests | Complete |
|-----------|-------|-----------------|------------------|----------------|-----------------|----------|
| **SIL 3** | 46 | 46 (100%) | 0 (0%) | 0 (0%) | 0 (0%) | 28% |
| **SIL 0** | 4 | 4 (100%) | 0 (0%) | 0 (0%) | 0 (0%) | 28% |

**SIL 3 Compliance Target**: 100% traceability from requirements → design → code → tests (mandatory per EN 50128)

---

## 6. DERIVED REQUIREMENTS

Derived requirements are software requirements that are NOT directly traceable to a system requirement but are necessary for implementation or compliance with EN 50128.

| SW Req ID | Category | Rationale | Status |
|-----------|----------|-----------|--------|
| **REQ-IMPL-001** | Implementation | MISRA C:2012 compliance (EN 50128 mandatory for SIL 3) | ✓ Justified |
| **REQ-IMPL-002** | Implementation | Fixed-width types (MISRA C best practice, EN 50128) | ✓ Justified |
| **REQ-IMPL-003** | Implementation | Static allocation (EN 50128 mandatory for SIL 2+) | ✓ Justified |
| **REQ-IMPL-004** | Implementation | No recursion (EN 50128 highly recommended SIL 3-4) | ✓ Justified |
| **REQ-IMPL-005** | Implementation | Cyclomatic complexity (EN 50128 mandatory for SIL 3) | ✓ Justified |
| **REQ-IMPL-006** | Implementation | Defensive programming (EN 50128 highly recommended SIL 3-4) | ✓ Justified |
| **REQ-IMPL-007** | Implementation | Error handling strategy (EN 50128 design best practice) | ✓ Justified |
| **REQ-IMPL-008** | Implementation | Function parameter limits (MISRA C, maintainability) | ✓ Justified |
| **REQ-IMPL-009** | Implementation | Minimize globals (MISRA C, EN 50128 best practice) | ✓ Justified |
| **REQ-IMPL-010** | Implementation | Const correctness (MISRA C, safety) | ✓ Justified |

**Total Derived Requirements**: 10 (all implementation constraints)

---

## 7. ORPHAN ANALYSIS

### 7.1 Orphan Requirements

Orphan requirements are software requirements that are NOT traced to any system requirement.

**Status**: None identified (all 50 requirements trace to system requirements or are justified as derived)

### 7.2 Orphan Design Elements

Orphan design elements are design modules, code files, or tests that do NOT trace to any requirement.

**Status**: TBD (Phase 3 and later)

---

## 8. CHANGE IMPACT ANALYSIS

This section will be used to track the impact of requirement changes on downstream artifacts (design, code, tests).

| Change Request | Requirements Changed | Design Impacted | Code Impacted | Tests Impacted | Status |
|----------------|---------------------|-----------------|---------------|----------------|--------|
| *No changes yet* | - | - | - | - | - |

**Change Control**: All requirement changes SHALL be reviewed by CCB and impact analysis SHALL be performed using this RTM.

---

## 9. RTM MAINTENANCE PLAN

### 9.1 Update Frequency

The RTM SHALL be updated:
- **Phase 2 (Requirements)**: After SRS approval (initial baseline)
- **Phase 3 (Design)**: After SAS/SDS approval (add design modules)
- **Phase 4 (Implementation)**: After code implementation (add code files)
- **Phase 4 (Testing)**: After test execution (add test cases)
- **After CCB approval**: For any requirement change

### 9.2 Responsibilities

| Role | Responsibility |
|------|---------------|
| **Configuration Manager (CM)** | Maintain RTM, update after each phase gate, track completeness |
| **Requirements Engineer (REQ)** | Provide initial RTM based on SRS |
| **Designer (DES)** | Update RTM with design module mappings (Phase 3) |
| **Implementer (IMP)** | Update RTM with code file mappings (Phase 4) |
| **Tester (TST)** | Update RTM with test case mappings (Phase 4) |
| **Verifier (VER)** | Verify RTM completeness at each phase gate |

### 9.3 Tools

- **Current**: Markdown table (manual maintenance)
- **Future** (if project scales): Dedicated traceability tool (e.g., DOORS, Polarion, Jama)

---

## 10. COMPLIANCE CHECKLIST

### 10.1 EN 50128 Section 7.2 Traceability Requirements

| Requirement | Evidence | Status |
|-------------|----------|--------|
| **Bidirectional traceability established** | This RTM provides forward (Req → Design → Code → Tests) and backward traces | ✓ Complete (structure) |
| **100% requirements traced** | All 50 requirements traced to system requirements or justified as derived | ✓ Complete |
| **Safety requirements traced to hazards** | Section 4 (Hazard to Requirement Mapping) | ✓ Complete |
| **Traceability maintained through lifecycle** | RTM maintenance plan (Section 9) | ✓ Complete |
| **Change impact analysis supported** | Section 8 (Change Impact Analysis table) | ✓ Complete |

### 10.2 RTM Completeness (Current Phase)

| Phase | Traceability Target | Current Status |
|-------|---------------------|----------------|
| **Phase 2 (Requirements)** | SW Req ↔ System Req | ✓ 100% Complete (50/50) |
| **Phase 3 (Design)** | SW Req → Design Modules | ⚠️ Pending (0/50) |
| **Phase 4 (Implementation)** | Design → Code Files | ⚠️ Pending (0/TBD) |
| **Phase 4 (Testing)** | SW Req → Test Cases | ⚠️ Pending (0/TBD) |
| **Phase 6 (Validation)** | 100% end-to-end traceability | ⚠️ Target for Phase 6 |

---

## REFERENCES

| Reference | Document |
|-----------|----------|
| **[SRS]** | Software Requirements Specification, DOC-SRS-2026-001 v1.0 |
| **[SCMP]** | Software Configuration Management Plan, DOC-SCMP-2026-001 v2.0 |
| **[EN50128]** | EN 50128:2011 Section 7.2 (Requirements Specification) |
| **[HAZLOG]** | Hazard Log, TBD (to be created by Safety Engineer) |

---

## DOCUMENT HISTORY

This document is maintained under configuration control per SCMP. All changes SHALL be approved by the Configuration Manager (CM).

**Current Version**: 1.0 (Draft)  
**Last Updated**: 2026-02-19  
**Next Review**: Phase 3 (Design) - update with design module mappings  
**Baseline**: Not yet baselined (awaiting SRS approval)

---

**END OF DOCUMENT**
