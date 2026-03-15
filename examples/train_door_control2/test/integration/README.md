# Integration Test Suite - Train Door Control System

**Document**: DOC-INTTEST-2026-001 v1.0  
**Project**: train_door_control2  
**SIL Level**: SIL 3  
**Test Execution**: Phase 6 Activity 0b (TST execution)

---

## Overview

This directory contains **73 integration test cases** for software integration testing per EN 50128:2011 Section 7.6.

**Test Organization**:
- Phase 1: HAL Layer Integration (11 tests) - `test_phase1_hal.c`
- Phase 2: Control Logic Integration (9 tests) - `test_phase2_control.c`
- Phase 3: Application Layer Integration (6 tests) - `test_phase3_app.c`
- Phase 4: System Integration (3 tests) - `test_phase4_system.c`
- Performance Testing (8 tests) - `test_performance.c`
- Safety-Critical Testing (36 tests) - `test_safety.c`

---

## Quick Start

```bash
# Build integration tests
make clean
make integration_tests

# Execute all 73 tests
./integration_test_runner

# Generate coverage report
make coverage

# View results
cat results/software_integration_results.xml
cat results/integration_execution.log
firefox results/coverage/index.html
```

---

## Test Environment

**Platform**: Linux x86_64 (host PC)  
**Compiler**: GCC 11.4.0 or later  
**Framework**: Custom test harness (Unity-compatible)  
**Coverage**: gcov/lcov  

**Hardware Status**: ⚠️ **Target hardware NOT available**  
- All tests execute on x86_64 host PC
- HAL functions use simulation/stubs
- Timing measurements are estimates only
- Hardware/software integration DEFERRED

---

## Test Results Location

**Machine-Readable Results**:
- `results/software_integration_results.xml` - JUnit XML format (73 test cases)

**Additional Outputs**:
- `results/integration_execution.log` - Console output
- `results/coverage/` - HTML coverage reports
- `results/performance_results.json` - Timing measurements
- `results/test_environment.yaml` - Test environment metadata
- `results/failures/` - Failure analysis (if any)

---

## Test Execution Time

**Estimated Duration**: ~2-3 hours (all 73 tests on host PC)

| Phase | Tests | Est. Time |
|-------|-------|-----------|
| Phase 1 (HAL) | 11 | ~20 min |
| Phase 2 (Control) | 9 | ~25 min |
| Phase 3 (Application) | 6 | ~15 min |
| Phase 4 (System) | 3 | ~30 min |
| Performance | 8 | ~40 min |
| Safety | 36 | ~70 min |
| **TOTAL** | **73** | **~200 min (3.3 hours)** |

---

## Success Criteria

**PASS Requirements**:
- ✅ All 73 test cases executed
- ✅ Pass rate ≥ 95% (≤ 3 failures allowed)
- ✅ No critical interface failures
- ✅ Coverage ≥ 95% statement, ≥ 95% branch
- ✅ All failures investigated and documented

**Preferred Target**: 73/73 PASS (100%)

---

## EN 50128 Compliance

**Standard**: EN 50128:2011 Section 7.6 (Software Integration)  
**Techniques Applied** (Table A.6, SIL 3):
- Functional/Black-Box Testing (HR)
- Performance Testing (HR)
- Interface Testing (HR)

**Traceability**: 100% requirements coverage (50 requirements, 73 test cases)

---

## Contact

**Tester (TST)**: Automated agent (OpenCode EN50128 TST)  
**Integrator (INT)**: Awaiting test results for Activity 0c (documentation)  
**Phase**: Phase 6 Activity 0b (Test Execution)  
**Date**: 2026-02-25
