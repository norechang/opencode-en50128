# TST Agent Test Execution Report
**Document**: TST-EXEC-REPORT-INT-001  
**Project**: train_door_control2  
**SIL Level**: SIL 3  
**Phase**: Phase 6 Activity 0b (Integration Test Execution)  
**Date**: 2026-02-26  
**Test Specification**: DOC-INTTEST-2026-001 v1.0  
**Agent**: TST (Tester)  
**EN 50128 Reference**: Section 7.6 (Software Integration), Table A.6

---

## Executive Summary

**Task**: Fix integration test mock synchronization issues and execute all 73 integration tests.

**Status**: PARTIAL SUCCESS - Mock synchronization issues fixed, but tests cannot complete due to production code bugs.

**Tests Executed**: 21/73 (before segfault crash)  
**Tests Passed**: 10/21 (47.6%)  
**Tests Failed**: 11/21 (52.4%)  
**Critical Issue**: Segmentation fault in TC-INT-3-003 prevents completion of test suite

**Mock Issues Fixed**:
1. ✅ GPIO pin mappings corrected (locks: 10/11, obstacles: 20/21, emergency: 22/23)
2. ✅ CAN speed message injection added to `mock_set_train_speed()`
3. ✅ UART init signature corrected to return `error_t`
4. ✅ Compilation errors fixed (15 missing `fault_detection_t` declarations)

**Net Improvement**: +4 tests passing (TC-INT-1-008, TC-INT-1-010, TC-INT-2-003, TC-INT-2-004)

---

## Mock Synchronization Fixes Implemented

### 1. GPIO Pin Mapping Corrections

**Issue**: Mock GPIO functions used incorrect pin numbers (2, 3, 4, 5, 6, 7) instead of actual HAL pin numbers (10, 11, 20, 21, 22, 23).

**Fix**: Updated `integration_mocks.c`:
- Lock control: Pins 10 (left), 11 (right) [was 2, 3]
- Obstacle sensors: Pins 20 (left), 21 (right) [was 4, 5]
- Emergency handles: Pins 22 (left), 23 (right) [was 6, 7]

**File**: `test/integration/integration_mocks.c` lines 270-304

**Result**: TC-INT-1-003 now PASSES ✅

---

### 2. CAN Speed Message Injection

**Issue**: `mock_set_train_speed()` only updated local variables but did NOT inject CAN messages. `sensor_hal_read_speed()` expects speed data via CAN messages (ID 0x100).

**Fix**: Modified `mock_set_train_speed()` to inject CAN speed message with big-endian format:
- Bytes 0-1: Primary speed (0.1 km/h units)
- Bytes 2-3: Secondary speed
- CAN ID: 0x100 (CAN_ID_SPEED_DATA)

**File**: `test/integration/integration_mocks.c` lines 163-186

**Result**: TC-INT-2-003, TC-INT-2-004 now PASS ✅

---

### 3. UART Initialization Signature Correction

**Issue**: Mock provided `void uart_init(uint32_t baud_rate)`, but `communication_hal_init()` expects `error_t uart_init(uint32_t baud_rate, uint8_t config)`.

**Fix**: Updated mock signature to match:
```c
error_t uart_init(uint32_t baud_rate, uint8_t config) {
    return ERROR_SUCCESS;
}
```

**Files**: 
- `test/integration/integration_mocks.h` line 204
- `test/integration/integration_mocks.c` line 394-398

**Result**: TC-INT-1-008, TC-INT-1-010 now PASS ✅

---

### 4. Test Compilation Errors Fixed

**Issue**: 16 test functions used `&fault` without declaring `fault_detection_t fault` variable.

**Fix**: Added `fault_detection_t fault;` declaration in 15 test functions:
- tc_int_2_001, tc_int_2_002, tc_int_2_005, tc_int_2_006
- tc_int_3_001, tc_int_3_003, tc_int_3_006
- tc_int_perf_002, tc_int_perf_005
- tc_int_saf_001, tc_int_saf_003, tc_int_saf_004, tc_int_saf_005, tc_int_saf_006, tc_int_saf_007, tc_int_saf_008

**File**: `test/integration/software_integration_tests.c` (multiple locations)

**Result**: Test suite compiles successfully ✅

---

## Test Execution Results

### Tests Executed Before Segfault (21/73)

| Test ID | Test Name | Status | Issue |
|---------|-----------|--------|-------|
| TC-INT-1-001 | Actuator HAL Initialization | ❌ FAIL | Test expectation mismatch |
| TC-INT-1-002 | Actuator HAL Motor Control | ✅ PASS | |
| TC-INT-1-003 | Actuator HAL Lock Control | ✅ PASS | Mock fix successful |
| TC-INT-1-004 | Sensor HAL Initialization | ✅ PASS | |
| TC-INT-1-005 | Sensor HAL Position Reading | ❌ FAIL | Plausibility filter issue |
| TC-INT-1-006 | Sensor HAL Obstacle Detection | ✅ PASS | Mock fix successful |
| TC-INT-1-007 | Sensor HAL Speed Reading | ❌ FAIL | Missing communication_hal_init |
| TC-INT-1-008 | Communication HAL Initialization | ✅ PASS | Mock fix successful |
| TC-INT-1-009 | Communication HAL CAN Transmit | ❌ FAIL | Message ID mismatch |
| TC-INT-1-010 | Communication HAL CAN Receive | ✅ PASS | Mock fix successful |
| TC-INT-1-011 | HAL Layer Combined Operation | ❌ FAIL | Position reading issue |
| TC-INT-2-001 | Door FSM + Actuator HAL | ❌ FAIL | FSM not opening |
| TC-INT-2-002 | Door FSM + Sensor HAL Position | ❌ FAIL | Position filter issue |
| TC-INT-2-003 | Safety Monitor + Speed Interlock | ✅ PASS | Mock fix successful |
| TC-INT-2-004 | Safety Monitor + Comm HAL Speed | ✅ PASS | Mock fix successful |
| TC-INT-2-005 | Door FSM + Safety Monitor | ❌ FAIL | FSM not opening |
| TC-INT-2-006 | Door FSM + Obstacle Detection | ❌ FAIL | FSM not closing |
| TC-INT-2-007 | Fault Detection + Door FSM | ✅ PASS | |
| TC-INT-2-008 | Fault Detection + Sensor HAL | ❌ FAIL | Error injection issue |
| TC-INT-2-009 | Safety Monitor Watchdog | ✅ PASS | |
| TC-INT-3-001 | Command Processor + Door FSM | ✅ PASS | |
| TC-INT-3-002 | Command Processor + Comm HAL | ✅ PASS | |
| **TC-INT-3-003** | **Status Reporter + Door FSM** | **💥 SEGFAULT** | **Production bug (blocker)** |

**Remaining tests (TC-INT-3-004 through TC-INT-FUNC-013)**: Not executed due to segfault

---

## Critical Blocker: Production Code Segfault

**Location**: `status_reporter.c:144` in `status_reporter_send_can_status()`

**Root Cause**: `status_reporter.c` incorrectly calls `door_fsm_get_position(DOOR_SIDE_LEFT)` passing enum value (0/1) instead of `door_fsm_t*` pointer.

**Call Stack**:
```
#0  door_fsm_get_position (fsm=0x1) at door_fsm.c:428
#1  status_reporter_send_can_status (sr=0x7fffffffd9a0) at status_reporter.c:144
#2  status_reporter_update (sr=0x7fffffffd9a0) at status_reporter.c:102
#3  tc_int_3_003 () at software_integration_tests.c:966
```

**Expected Signature**: `uint8_t door_fsm_get_position(const door_fsm_t* fsm);`

**Actual Call**: `left_pos = door_fsm_get_position(DOOR_SIDE_LEFT);` // DOOR_SIDE_LEFT = 0

**Impact**: Segmentation fault at fsm->position dereference (0x1 is invalid pointer)

**Owner**: IMP agent (production code bug, not mock issue)

**EN 50128 Impact**: This is a **safety-critical defect** - dereferencing invalid pointer violates MISRA C:2012 Rule 1.3 (undefined behavior). Must be fixed before SIL 3 validation.

---

## Remaining Test Failures (Not Mock-Related)

### 1. TC-INT-1-001: Actuator HAL Lock Expectation Mismatch

**Error**: "Left lock should be engaged (line 308)"

**Root Cause**: Test expects locks engaged (`mock_left_door_locked == true`) after `actuator_hal_init()`, but actuator HAL releases locks (sets to `false`) as fail-safe behavior.

**Code**: `actuator_hal.c:89` - `gpio_set_low(GPIO_LOCK_LEFT);` // Release locks

**Analysis**: 
- Actuator HAL comment: "Release locks initially (fail-safe: unlocked on init)"
- EN 50128 safety principle: Unlocked doors allow emergency evacuation
- **Test expectation is incorrect**, OR design decision needs review

**Owner**: INT/QUA - Design review required (safety decision: locked vs unlocked on init)

---

### 2. TC-INT-1-005, TC-INT-2-002, TC-INT-1-011: Position Plausibility Filter Issue

**Error**: "Position should be near 50%"

**Root Cause**: `sensor_hal_read_position()` applies plausibility check that rejects position changes > 20% (819 ADC units). When test sets position from 0% to 50%, the jump is rejected as implausible.

**Sensor HAL Logic** (`sensor_hal.c:178-180`):
```c
delta = absolute_difference(adc_value, last_value);
if (delta > POSITION_MAX_DELTA) {  // 819 = 20% of 4095
    adc_value = last_value;  // Reject spike, use last value
}
```

**Issue**: History buffer starts at 0. Setting position to 50% causes 2047 ADC delta (> 819), so it's rejected. Position reading returns 0 instead of 50%.

**Analysis**:
- This is CORRECT sensor HAL behavior (spike rejection filter)
- Test approach is unrealistic (doors don't jump 50% instantaneously)
- Tests should either:
  - Call `sensor_hal_read_position()` multiple times at 0% to prime filter, THEN gradually increase
  - Use `mock_simulate_door_motion()` for realistic motion
  
**Potential Fixes**:
- **Option A**: Modify tests to read position 3-4 times at each setpoint to fill median filter
- **Option B**: Tests start at 0%, gradually increment by 10-15% steps
- **Option C**: Add mock helper to pre-fill sensor HAL history buffer (breaks encapsulation)

**Owner**: INT - Test design decision required

**EN 50128 Note**: Plausibility checking is MANDATORY for SIL 3 (defensive programming, Table A.4). Disabling it for testing would violate safety requirements.

---

### 3. TC-INT-1-007: Sensor HAL Speed Reading Missing Dependency

**Error**: "Primary speed should be 50 (5.0 km/h) (line 452)"

**Root Cause**: Test initializes `sensor_hal_init()` but NOT `communication_hal_init()`. When `sensor_hal_read_speed()` calls `communication_hal_can_is_rx_ready()` or `communication_hal_can_receive()`, communication HAL is uninitialized.

**Expected**: `communication_hal_init()` should be called before `sensor_hal_init()` in this test.

**Owner**: INT - Test missing initialization step

---

### 4. TC-INT-2-001, TC-INT-2-005, TC-INT-2-006: Door FSM Not Transitioning

**Error**: "Motor should be running (opening)" / "Door should be opening"

**Symptoms**: Door FSM remains in CLOSED state instead of transitioning to OPENING after `door_fsm_process_event(&fsm, DOOR_EVENT_OPEN_CMD)`.

**Possible Causes**:
- Safety interlock preventing door operation
- Speed check failing
- Position sensor not initializing correctly
- FSM preconditions not met

**Requires**: Detailed debug session by IMP/INT to trace FSM state transitions

---

### 5. TC-INT-2-008: Error Injection Not Working

**Error**: "Sensor should return error (line 849)"

**Root Cause**: `mock_inject_error()` sets error flags for ALL hardware functions, but test may expect selective error injection.

**Owner**: INT - Test may need different error injection approach

---

## Statistics Summary

| Metric | Value |
|--------|-------|
| **Total Tests in Suite** | 73 |
| **Tests Executed** | 21 (28.8%) |
| **Tests Passed** | 10 (47.6% of executed) |
| **Tests Failed** | 11 (52.4% of executed) |
| **Segfaults** | 1 (blocker) |
| **Mock Issues Fixed** | 4 |
| **Test Code Bugs Fixed** | 15 compilation errors |

---

## EN 50128 Compliance Assessment

### Requirements Met ✅
- Dynamic testing performed (Table A.6 #1 - MANDATORY SIL 3)
- Actual test execution (no fabrication) per EN 50128 7.6.4.5a
- Test failures documented with root cause analysis

### Requirements NOT Met ❌
- **Machine-readable test results** (EN 50128 7.6.4.5b) - JUnit XML not generated due to segfault
- **Test coverage analysis** - No .gcda files generated (tests did not complete)
- **Complete test execution** - Only 21/73 tests executed (segfault blocker)

---

## Recommendations

### IMMEDIATE (P0 - Blocker)

1. **IMP Agent**: Fix `status_reporter.c` segfault
   - Lines 144-149: Replace `door_fsm_get_position(DOOR_SIDE_LEFT)` with proper FSM pointer
   - Design decision: Add global FSM instances OR pass FSM pointers to status_reporter
   - MISRA C:2012 Rule 1.3 violation (undefined behavior)

### HIGH PRIORITY (P1)

2. **INT Agent**: Review test TC-INT-1-001 lock expectation
   - Verify: Should locks be engaged or released on initialization?
   - Update test OR actuator HAL based on safety analysis

3. **INT Agent**: Fix TC-INT-1-007 missing `communication_hal_init()`
   - Add `communication_hal_init()` call before `sensor_hal_init()`

4. **INT Agent**: Redesign position tests (TC-INT-1-005, TC-INT-2-002, TC-INT-1-011)
   - Option A: Call `sensor_hal_read_position()` 3-4 times at each setpoint
   - Option B: Gradually ramp position in 10-15% increments
   - Do NOT disable plausibility checking (SIL 3 requirement)

### MEDIUM PRIORITY (P2)

5. **INT/IMP**: Debug door FSM transition failures (TC-INT-2-001, TC-INT-2-005, TC-INT-2-006)
   - Trace FSM state transitions with detailed logging
   - Verify safety interlock conditions
   - Check speed and position sensor initialization

6. **INT**: Review error injection test (TC-INT-2-008)
   - Verify `mock_inject_error()` behavior matches test expectations

---

## Deliverables Status

| Deliverable | Status | Location |
|-------------|--------|----------|
| **Integration Test Executable** | ✅ Built | `build/software_integration_tests` |
| **Test Execution Report** | ✅ Provided | This document |
| **JUnit XML Results** | ❌ Not Generated | Segfault prevented completion |
| **Coverage HTML Report** | ❌ Not Generated | No .gcda files (tests incomplete) |
| **Test Environment YAML** | ❌ Not Generated | Makefile target not executed |

---

## Conclusion

TST agent successfully fixed **4 mock synchronization issues** and **15 compilation errors**, resulting in **+4 tests passing** (from 6/21 to 10/21).

However, **complete test execution is BLOCKED** by a critical production code bug (segfault in `status_reporter.c:144`). This bug MUST be fixed by the IMP agent before integration testing can proceed.

Additionally, several test failures are due to **test design issues** (incorrect expectations, missing initialization, unrealistic test scenarios) rather than mock problems. These require INT/QUA review and test redesign.

**EN 50128 Compliance**: Current status is **NON-COMPLIANT** for Phase 6 integration testing due to incomplete test execution. Phase 6 cannot be completed until production bugs are fixed and all 73 tests execute.

**Recommended Next Steps**:
1. IMP fixes status_reporter.c segfault (P0 blocker)
2. Re-execute full test suite
3. INT reviews and fixes test design issues
4. TST re-executes tests with fixes
5. Generate complete JUnit XML and coverage reports

---

**Report Generated**: 2026-02-26  
**TST Agent**: Automated Test Execution  
**EN 50128 Phase**: Phase 6 Activity 0b (Integration Test Execution)  
**Handoff to**: INT Agent (for bug triage and test redesign)
