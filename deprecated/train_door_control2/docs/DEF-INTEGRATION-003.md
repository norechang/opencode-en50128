# Defect Report: DEF-INTEGRATION-003

**Document ID**: DEF-INTEGRATION-003  
**Project**: train_door_control2  
**SIL Level**: SIL 3  
**Date**: 2026-02-26  
**Severity**: **CRITICAL (Safety-Critical)**  
**Priority**: P1 (Highest)  
**Status**: FIXED

---

## 1. Defect Summary

**Title**: Speed Interlock Logic Error - Incorrect Function Signature Causing Undefined Behavior

**Test ID**: TC-INT-SAF-001 (Speed Interlock During Door Opening)  
**Module**: MOD-001 (Door FSM), MOD-002 (Safety Monitor)  
**Root Cause**: Function signature mismatch and missing module initialization

---

## 2. Problem Description

### 2.1 Test Failure
- **Test**: TC-INT-SAF-001 "Speed Interlock During Door Opening"
- **Expected**: Door SHOULD open when train speed = 0 km/h (safe condition)
- **Actual**: Door BLOCKED from opening when train speed = 0 km/h
- **Impact**: **SAFETY-CRITICAL** - Incorrect speed interlock logic could:
  - Allow doors to open at high speed (catastrophic)
  - Prevent doors from opening at standstill (operational failure)

### 2.2 Failure Evidence
```
TC-INT-SAF-001: Speed Interlock During Door Opening ... FAIL
ASSERTION FAILED: Door should open at 0 km/h (line 1439)
Expected: DOOR_STATE_OPENING (1)
Actual: DOOR_STATE_FAULT (6)
```

---

## 3. Root Cause Analysis

### 3.1 Primary Issue: Function Signature Mismatch

**File**: `src/door_control/door_fsm.c`

**Line 24 (BEFORE FIX)**:
```c
extern bool safety_monitor_is_safe_to_open(void);  // ← NO PARAMETERS (WRONG)
```

**Correct Signature** (from `safety_monitor.h`):
```c
bool safety_monitor_is_safe_to_open(const safety_monitor_t* monitor);  // ← REQUIRES PARAMETER
```

**Line 161 (BEFORE FIX)**:
```c
if (safety_monitor_is_safe_to_open()) {  // ← Called with NO arguments (UNDEFINED BEHAVIOR)
```

**Impact**: Calling `safety_monitor_is_safe_to_open()` with NO arguments when the function expects a pointer caused:
- Garbage pointer passed to function
- NULL check likely failed or invalid memory access
- Fail-safe logic returned `false` (unsafe to open)
- Door blocked even at 0 km/h

### 3.2 Secondary Issue: Missing Module Integration

**Problem**: `door_fsm_t` structure had NO reference to `safety_monitor_t`

**Before**:
```c
typedef struct {
    ...
    fault_detection_t* fault_detection;  // ← Only fault detection pointer
} door_fsm_t;
```

**After**:
```c
typedef struct {
    ...
    fault_detection_t* fault_detection;
    safety_monitor_t* safety_monitor;     // ← Added safety monitor pointer
} door_fsm_t;
```

### 3.3 Tertiary Issue: Missing `fault_detection_init()` in Tests

**Problem**: Integration tests declared `fault_detection_t fault` but never initialized it, causing door FSM to enter FAULT state immediately.

---

## 4. Fix Implementation

### 4.1 Changes to `door_fsm.h`

1. **Added forward declaration**:
```c
typedef struct safety_monitor_s safety_monitor_t;
```

2. **Added safety_monitor pointer to door_fsm_t**:
```c
typedef struct {
    ...
    safety_monitor_t* safety_monitor;  // ← NEW (4 or 8 bytes)
} door_fsm_t;
```

3. **Updated `door_fsm_init()` signature**:
```c
error_t door_fsm_init(door_fsm_t* fsm, door_side_t side, 
                      fault_detection_t* fd, safety_monitor_t* sm);  // ← Added sm parameter
```

### 4.2 Changes to `door_fsm.c`

1. **Added header include**:
```c
#include "../safety_monitor/safety_monitor.h"
```

2. **Removed incorrect extern declaration**:
```c
// DELETED: extern bool safety_monitor_is_safe_to_open(void);
```

3. **Updated `door_fsm_init()` implementation**:
```c
error_t door_fsm_init(door_fsm_t* fsm, door_side_t side, 
                      fault_detection_t* fd, safety_monitor_t* sm) {
    ...
    if (sm == NULL) {  // ← NEW: Defensive NULL check
        return ERROR_NULL_POINTER;
    }
    ...
    fsm->safety_monitor = sm;  // ← NEW: Store safety monitor reference
    return ERROR_SUCCESS;
}
```

4. **Fixed safety interlock check** (line 173):
```c
// BEFORE: if (safety_monitor_is_safe_to_open()) {  // ← NO ARGUMENT
// AFTER:
if (safety_monitor_is_safe_to_open(fsm->safety_monitor)) {  // ← PASS MONITOR POINTER
```

### 4.3 Changes to `safety_monitor.h`

**Added struct tag for forward declaration**:
```c
// BEFORE: typedef struct { ... } safety_monitor_t;
// AFTER:
typedef struct safety_monitor_s { ... } safety_monitor_t;  // ← Added tag
```

### 4.4 Changes to Integration Tests

**Updated ALL `door_fsm_init()` calls** (32 instances):
```c
// BEFORE: door_fsm_init(&fsm, DOOR_SIDE_LEFT, &fault);
// AFTER:
safety_monitor_init(&monitor);         // ← Ensure monitor initialized
fault_detection_init(&fault);          // ← Ensure fault detection initialized
door_fsm_init(&fsm, DOOR_SIDE_LEFT, &fault, &monitor);  // ← Pass both pointers
```

---

## 5. Verification Results

### 5.1 Standalone Test (Isolated TC-INT-SAF-001)

```
Running TC-INT-SAF-001 with debug...
Safety monitor speed: 0 (0.1 km/h units)
Is safe to open: 1 ✓
Should lock: 0 ✓
Critical fault active: 0 ✓
Door state: 1 (DOOR_STATE_OPENING) ✓
✓ PASS: Door opened successfully at 0 km/h
```

**Result**: **PASS** ✓

### 5.2 Speed Interlock Verification

| Speed (km/h) | `is_safe_to_open()` | `should_lock()` | Door Behavior | Result |
|--------------|---------------------|-----------------|---------------|--------|
| 0            | TRUE                | FALSE           | Opens         | ✓ CORRECT |
| 1            | FALSE               | FALSE           | Blocked       | ✓ CORRECT |
| 6            | FALSE               | TRUE            | Locked        | ✓ CORRECT |

---

## 6. Traceability

### 6.1 Safety Requirements
- **SR-003**: Speed interlock (doors must NOT open if train speed > 5 km/h)
- **SR-004**: Fail-safe logic (doors must default to LOCKED state)

### 6.2 Design Documents
- **DOC-COMPDES-2026-001**: Component Design Specification
  - Section 3.1 (MOD-001 Door FSM)
  - Section 3.2 (MOD-002 Safety Monitor)

### 6.3 Standards Compliance
- **EN 50128:2011 Section 7.4** (Implementation)
- **EN 50128:2011 Table A.4** (Design and Coding Standards - MANDATORY SIL 3)
- **MISRA C:2012** (Defensive programming, pointer validation)

---

## 7. Lessons Learned

### 7.1 Design Issues
1. **Loose coupling violated**: `door_fsm.c` used `extern` declaration instead of proper header include
2. **Integration not validated**: Module interactions not tested before integration phase
3. **Type safety bypassed**: Incorrect function signature not caught by compiler (C allows this)

### 7.2 Preventive Measures
1. **ALWAYS include proper headers** - Never use `extern` for functions from other modules
2. **Use `-Werror -Wstrict-prototypes`** - Enable strict compiler warnings
3. **Static analysis BEFORE integration** - Would have caught signature mismatch
4. **Module initialization checklist** - Ensure ALL modules initialized in correct order

---

## 8. Files Modified

| File | Lines Changed | Type |
|------|---------------|------|
| `src/door_control/door_fsm.h` | +3, ~8 | Interface |
| `src/door_control/door_fsm.c` | +7, ~5 | Implementation |
| `src/safety_monitor/safety_monitor.h` | ~1 | Interface |
| `test/integration/software_integration_tests.c` | ~64 | Test |

**Total**: 4 files, ~88 lines changed

---

## 9. Review and Approval

| Role | Name | Date | Signature |
|------|------|------|-----------|
| **Implementer (IMP)** | OpenCode IMP Agent | 2026-02-26 | ✓ Fixed |
| **Verifier (VER)** | _Pending_ | _Pending_ | _Pending_ |
| **Quality Assurance (QUA)** | _Pending_ | _Pending_ | _Pending_ |

---

## 10. Closure Criteria

- [x] Root cause identified and documented
- [x] Fix implemented with defensive programming
- [x] Standalone test passes
- [ ] Full integration test suite passes (TC-INT-SAF-001 through TC-INT-SAF-010)
- [ ] Unit tests updated and passing
- [ ] Static analysis clean (zero violations)
- [ ] Code review completed (QUA)
- [ ] Verification report updated (VER)

**Status**: Fix verified in isolation, awaiting full test suite validation.

---

**END OF DEFECT REPORT**
