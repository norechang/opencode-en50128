# Coverage Analysis Report - After Defect Fixes

**Document ID**: DOC-COVERAGE-2026-001  
**Version**: 1.0  
**Date**: 2026-02-22  
**Project**: train_door_control2  
**SIL Level**: 3  
**Component**: MOD-001 (Door Control FSM)

---

## Executive Summary

After fixing DEFECT #1 (event queue processing) and DEFECT #2 (queue buffer size), test suite execution shows:

| Metric | Current | Target (SIL 3) | Status |
|--------|---------|----------------|--------|
| **Test Pass Rate** | 43/43 (100%) | 100% | ✅ **PASS** |
| **Statement Coverage** | 90.50% (200/221 lines) | 100% | ⚠️ **FAIL** (21 lines uncovered) |
| **Branch Coverage** | 95.74% executed, 86.17% taken (94 branches) | 100% | ⚠️ **FAIL** |
| **MC/DC Coverage** | Not measured | 100% | ⚠️ **FAIL** |

**Conclusion**: Component testing is **NOT SIL 3 COMPLIANT** due to coverage gaps. Additional test cases required.

---

## Coverage Improvement

| Metric | Before Fixes | After Fixes | Improvement |
|--------|--------------|-------------|-------------|
| Statement Coverage | 83.71% | 90.50% | +6.79% |
| Lines Covered | 185/221 | 200/221 | +15 lines |
| Test Pass Rate | 40/43 (93.0%) | 43/43 (100%) | +3 tests |

**Analysis**: Defect fixes successfully unblocked 15 lines that were previously unreachable. However, 21 lines remain uncovered due to **missing test cases**, NOT code defects.

---

## Uncovered Code Analysis

### Category 1: Missing Critical Safety Function - `transition_to_locked()` (13 lines)

**Function**: `door_fsm_transition_to_locked()` (lines 576-611)  
**Purpose**: Transition to LOCKED state when train speed > 5 km/h  
**SIL Level**: 3 (REQ-FUNC-003 - Critical safety requirement)  
**Status**: ⚠️ **ENTIRE FUNCTION UNCOVERED (0% coverage)**

**Uncovered Lines**:
```
589:    fsm->previous_state = fsm->current_state;
592:    fsm->current_state = DOOR_STATE_LOCKED;
593:    fsm->state_entry_time_ms = get_system_time_ms();
594:    fsm->locked = true;
597:    error = actuator_hal_set_door_lock(fsm->side, true);
598:    if (error != ERROR_SUCCESS) {
599:        fault_detection_report_fault(FAULT_LOCK_ACTUATOR_FAILURE, FAULT_SEVERITY_CRITICAL);
600:        return error;
604:    error = actuator_hal_set_door_pwm(fsm->side, DOOR_FSM_PWM_STOP_DUTY);
605:    if (error != ERROR_SUCCESS) {
606:        fault_detection_report_fault(FAULT_ACTUATOR_FAILURE, FAULT_SEVERITY_MAJOR);
607:        return error;
610:    return ERROR_SUCCESS;
```

**Root Cause**: Missing test cases TC-MOD001-019, TC-MOD001-021, TC-MOD001-022 (specified but not implemented)

**Safety Impact**: **CRITICAL**  
- Lock function prevents doors from opening while train is moving (HAZ-001: "Doors open while train is moving" - Catastrophic severity)
- Untested lock actuator failure path (line 599) could result in doors remaining unlocked at speed
- Untested lock success path (lines 589-594) means normal locking operation never verified

**Required Test Cases**:
1. **TC-MOD001-021**: Transition to Locked Success
   - Precondition: Door CLOSED, speed > 5 km/h, LOCK_CMD event
   - Expected: State = LOCKED, locked = true, lock actuator engaged
   - **Covers**: Lines 589-594, 597-610 (nominal path)

2. **TC-MOD001-022**: Transition to Locked CRITICAL FAULT (Door Not Closed)
   - Precondition: Door OPEN (position > 5%), LOCK_CMD event
   - Expected: ERROR_INVALID_STATE, enter EMERGENCY state, fault FAULT_DOOR_NOT_CLOSED_MOVING
   - **Covers**: Lines 581-585 (already covered by TC-MOD001-046)

3. **TC-MOD001-021b**: Transition to Locked Lock Actuator Failure
   - Precondition: Door CLOSED, LOCK_CMD event, mock lock actuator failure
   - Expected: ERROR returned, fault FAULT_LOCK_ACTUATOR_FAILURE
   - **Covers**: Lines 598-600 (error path)

---

### Category 2: Actuator PWM Failure Paths (8 lines)

**Function**: `actuator_hal_set_door_pwm()` error handling in 4 transition functions  
**SIL Level**: 3 (fault detection requirement)  
**Status**: ⚠️ **ERROR PATHS UNCOVERED**

**Uncovered Lines**:

#### `transition_to_opening()` (lines 483-484):
```
483:        fault_detection_report_fault(FAULT_ACTUATOR_FAILURE, FAULT_SEVERITY_MAJOR);
484:        return error;
```

#### `transition_to_open()` (lines 508-509):
```
508:        fault_detection_report_fault(FAULT_ACTUATOR_FAILURE, FAULT_SEVERITY_MAJOR);
509:        return error;
```

#### `transition_to_closing()` (lines 534-535):
```
534:        fault_detection_report_fault(FAULT_ACTUATOR_FAILURE, FAULT_SEVERITY_MAJOR);
535:        return error;
```

#### `transition_to_closed()` (lines 559-560):
```
559:        fault_detection_report_fault(FAULT_ACTUATOR_FAILURE, FAULT_SEVERITY_MAJOR);
560:        return error;
```

**Root Cause**: Fault injection tests not implemented for PWM actuator failures

**Safety Impact**: **MAJOR**  
- Actuator failures could result in door stuck in intermediate position
- Untested error paths mean fault detection system not verified for actuator failures

**Required Test Cases**:
1. **TC-MOD001-049**: Transition to Opening PWM Failure
   - Mock `actuator_hal_set_door_pwm()` to return ERROR_HARDWARE_FAILURE in OPENING transition
   - **Covers**: Lines 483-484

2. **TC-MOD001-050**: Transition to Open PWM Failure  
   - Mock `actuator_hal_set_door_pwm()` to return ERROR_HARDWARE_FAILURE in OPEN transition
   - **Covers**: Lines 508-509

3. **TC-MOD001-051**: Transition to Closing PWM Failure
   - Mock `actuator_hal_set_door_pwm()` to return ERROR_HARDWARE_FAILURE in CLOSING transition
   - **Covers**: Lines 534-535

4. **TC-MOD001-052**: Transition to Closed PWM Failure
   - Mock `actuator_hal_set_door_pwm()` to return ERROR_HARDWARE_FAILURE in CLOSED transition
   - **Covers**: Lines 559-560

---

## Branch Coverage Analysis

**Current**: 95.74% branches executed, 86.17% taken  
**Target**: 100%  
**Gap**: 4 branches not executed, 13 branches not taken

**Analysis**: Branch coverage gaps are caused by the same 21 uncovered lines (each `if (error != ERROR_SUCCESS)` creates 2 branches: taken/not-taken).

**Expected after new tests**: 100% branch coverage

---

## MC/DC Coverage Analysis

**Current**: Not measured (gcov does not support MC/DC directly)  
**Target**: 100% (MANDATORY for SIL 3-4)  
**Status**: ⚠️ **NOT MEASURED**

**EN 50128 Requirement**: Table A.21, SIL 3-4: MC/DC coverage is MANDATORY

**Complex Conditions Requiring MC/DC**:
1. Line 166: `event_queue_contains(fsm, DOOR_EVENT_LOCK_CMD)` (in CLOSED state)
2. Line 248: `event_queue_contains(fsm, DOOR_EVENT_UNLOCK_CMD)` (in LOCKED state)
3. Line 581: `fsm->position > DOOR_FSM_POSITION_CLOSED_PCT` (lock validation)
4. Speed interlock conditions (in MOD-002, not yet tested)

**Recommendation**: Use commercial MC/DC coverage tool (e.g., VectorCAST, LDRA, Cantata) or manually verify MC/DC using boolean truth tables for all multi-condition expressions.

---

## Test Case Gap Summary

### Missing Test Cases (Specified but Not Implemented)

| Test Case ID | Priority | Covers | Status |
|--------------|----------|--------|--------|
| **TC-MOD001-019** | CRITICAL | Transition to Opening from Locked | ❌ NOT IMPLEMENTED |
| **TC-MOD001-020** | HIGH | (Unknown - check spec) | ❌ NOT IMPLEMENTED |
| **TC-MOD001-021** | CRITICAL | Transition to Locked Success | ❌ NOT IMPLEMENTED |
| **TC-MOD001-022** | CRITICAL | Transition to Locked FAULT | ❌ NOT IMPLEMENTED |

### New Test Cases (Fault Injection)

| Test Case ID | Priority | Covers | Status |
|--------------|----------|--------|--------|
| **TC-MOD001-021b** | CRITICAL | Lock actuator failure | ❌ NOT IMPLEMENTED |
| **TC-MOD001-049** | MAJOR | Opening PWM failure | ❌ NOT IMPLEMENTED |
| **TC-MOD001-050** | MAJOR | Open PWM failure | ❌ NOT IMPLEMENTED |
| **TC-MOD001-051** | MAJOR | Closing PWM failure | ❌ NOT IMPLEMENTED |
| **TC-MOD001-052** | MAJOR | Closed PWM failure | ❌ NOT IMPLEMENTED |

**Total Additional Tests Required**: 8 (4 missing + 4 fault injection)

**Estimated Coverage After Implementation**:
- Statement: 100% (221/221 lines)
- Branch: 100% (94/94 branches taken)
- Test pass rate: 51/51 (100%)

---

## Recommendations

### Immediate Actions (MANDATORY for SIL 3 compliance)

1. **Implement Missing LOCK Test Cases** (TC-MOD001-019, 021, 022)
   - Priority: **CRITICAL** (safety function untested)
   - Estimated effort: 2 hours
   - Blocks: SIL 3 compliance

2. **Implement Fault Injection Tests** (TC-MOD001-021b, 049-052)
   - Priority: **MAJOR** (error paths untested)
   - Estimated effort: 2-3 hours
   - Blocks: 100% branch coverage

3. **Measure MC/DC Coverage**
   - Priority: **MANDATORY** (EN 50128 Table A.21)
   - Options:
     - Commercial tool (VectorCAST, LDRA, Cantata)
     - Manual truth table analysis
   - Estimated effort: 4-8 hours (tool setup + analysis)

### Before Moving to Verification Phase

- [ ] All 51 test cases implemented and passing (43 current + 8 new)
- [ ] Statement coverage ≥ 100%
- [ ] Branch coverage ≥ 100%
- [ ] MC/DC coverage ≥ 100%
- [ ] All safety-critical functions tested (REQ-FUNC-003 LOCK function)
- [ ] All fault injection tests passing
- [ ] Software Component Test Report generated
- [ ] Test traceability matrix complete (req → test spec → test code → results)

---

## Test Infrastructure Status

**Status**: ✅ **READY FOR NEW TESTS**

- Custom test framework: ✅ Working
- Mock system: ✅ Working (supports fault injection via mock return values)
- Coverage measurement: ✅ Working (gcov/lcov)
- Build system: ✅ Working (Makefile with coverage support)

**To Add Fault Injection Tests**: Modify `test_mocks.c` to add failure modes:
```c
// Example: Mock lock actuator failure
void mock_lock_actuator_set_failure(bool enable) {
    g_mock_lock_actuator_failure = enable;
}

// In actuator_hal_set_door_lock():
if (g_mock_lock_actuator_failure) {
    return ERROR_HARDWARE_FAILURE;
}
```

---

## Traceability Matrix Update Required

Current traceability shows **MOD-001 → TC-MOD001-001 through TC-MOD001-048** (43 tests).

After implementing missing tests, update traceability to:
- **REQ-FUNC-003** (Lock Control) → TC-MOD001-019, 021, 021b, 022
- **Fault Detection** → TC-MOD001-049, 050, 051, 052

---

## Conclusion

Current testing effort has achieved:
- ✅ 100% test pass rate (all 43 tests passing)
- ✅ Defect fixes validated (event processing and queue size)
- ✅ 90.50% statement coverage (+6.79% improvement)
- ⚠️ 21 lines uncovered due to **missing test cases** (NOT code defects)
- ⚠️ **CRITICAL safety function (`transition_to_locked()`) completely untested**

**Component MOD-001 is NOT SIL 3 COMPLIANT** until:
1. All 8 missing test cases implemented
2. 100% statement, branch, and MC/DC coverage achieved
3. Lock function (REQ-FUNC-003) fully tested

**Next Steps**: Implement missing test cases TC-MOD001-019, 020, 021, 021b, 022, 049-052.

---

**Prepared by**: TST Agent (Testing)  
**Reviewed by**: (Pending)  
**Approved by**: (Pending)

**Document Control**:
- Version 1.0: 2026-02-22 - Initial coverage analysis after defect fixes (TST Agent)
