/**
 * @file    test_fmg.c
 * @brief   Unit tests for FMG module (COMP-005) — 17 test cases.
 * @details Covers TC-FMG-001 through TC-FMG-017.
 *          Tests: FMG_AggregateFaults, FMG_ClassifyAndEscalate,
 *                 FMG_HandleSelectiveDisablement, FMG_Init, FMG_GetFaultState,
 *                 FMG_RunCycle, FMG_GetFault.
 *
 * @project TDC (Train Door Control System)
 * @phase   Phase 5 — Implementation & Testing
 * @sil     3
 * @date    2026-04-04
 *
 * @traceability
 *   Tests: REQ-SAFE-012/013/021, REQ-FUN-018
 *   Item 16: Software Component Test Specification §COMP-005
 *   Item 18: Source Code (fmg_aggregator.c, fmg_init.c)
 */

#include "../unity/src/unity.h"
#include "../../src/tdc_types.h"
#include "../../src/fmg.h"
#include "../../src/hal.h"

/* Stub setters from fmg_deps_stub.c */
extern void fmg_stub_set_spm_fault(uint8_t v);
extern void fmg_stub_set_obd_fault(uint8_t v);
extern void fmg_stub_set_dsm_fault(uint8_t v);
extern void fmg_stub_set_tci_fault(uint8_t v);
extern void fmg_stub_reset_all(void);

/* =========================================================================
 * setUp / tearDown
 * ========================================================================= */
void setUp(void)
{
    fmg_stub_reset_all();
    (void)HAL_Init();
    (void)FMG_Init();
}

void tearDown(void) {}

/* =========================================================================
 * TC-FMG-001: FMG_Init — returns SUCCESS, fault_state=0
 * Tests: REQ-SAFE-012
 * SIL: 3
 * ========================================================================= */
void test_FMG_Init_Success(void)
{
    /* TC-FMG-001 */
    error_t ret = FMG_Init();
    TEST_ASSERT_EQUAL_INT(SUCCESS, ret);
    TEST_ASSERT_EQUAL_UINT8(0U, FMG_GetFaultState());
}

/* =========================================================================
 * TC-FMG-002: FMG_AggregateFaults — no faults → fault_state=0
 * Tests: REQ-SAFE-012
 * SIL: 3
 * ========================================================================= */
void test_FMG_AggregateFaults_NoFaults(void)
{
    /* TC-FMG-002 */
    uint8_t state = 0xFFU;
    error_t ret = FMG_AggregateFaults(0U, 0U, 0U, 0U, 0U, &state);
    TEST_ASSERT_EQUAL_INT(SUCCESS, ret);
    TEST_ASSERT_EQUAL_UINT8(0U, state);
}

/* =========================================================================
 * TC-FMG-003: FMG_AggregateFaults — SPM fault → bit FMG_FAULT_BIT_SPM(0x01) set
 * Tests: REQ-SAFE-012
 * SIL: 3
 * ========================================================================= */
void test_FMG_AggregateFaults_SpmFault(void)
{
    /* TC-FMG-003 */
    uint8_t state = 0U;
    (void)FMG_AggregateFaults(1U, 0U, 0U, 0U, 0U, &state);
    TEST_ASSERT_TRUE((state & 0x01U) != 0U); /* FMG_FAULT_BIT_SPM = 0x01 */
}

/* =========================================================================
 * TC-FMG-004: FMG_AggregateFaults — HAL fault → bit FMG_FAULT_BIT_HAL(0x10) set
 * Tests: REQ-SAFE-012
 * SIL: 3
 * ========================================================================= */
void test_FMG_AggregateFaults_HalFault(void)
{
    /* TC-FMG-004 */
    uint8_t state = 0U;
    (void)FMG_AggregateFaults(0U, 0U, 0U, 0U, 1U, &state);
    TEST_ASSERT_TRUE((state & 0x10U) != 0U); /* FMG_FAULT_BIT_HAL = 0x10 */
}

/* =========================================================================
 * TC-FMG-005: FMG_AggregateFaults — NULL output → ERR_NULL_PTR
 * Tests: REQ-SAFE-012
 * SIL: 3
 * ========================================================================= */
void test_FMG_AggregateFaults_NullOut(void)
{
    /* TC-FMG-005 */
    error_t ret = FMG_AggregateFaults(0U, 0U, 0U, 0U, 0U, NULL);
    TEST_ASSERT_EQUAL_INT(ERR_NULL_PTR, ret);
}

/* =========================================================================
 * TC-FMG-006: FMG_ClassifyAndEscalate — fault_state=0 → FAULT_NONE
 * Tests: REQ-SAFE-013
 * SIL: 3
 * ========================================================================= */
void test_FMG_ClassifyAndEscalate_NoFault(void)
{
    /* TC-FMG-006 */
    fault_severity_t sev = FAULT_CRITICAL;
    error_t ret = FMG_ClassifyAndEscalate(0U, &sev);
    TEST_ASSERT_EQUAL_INT(SUCCESS, ret);
    TEST_ASSERT_EQUAL_INT(FAULT_NONE, sev);
}

/* =========================================================================
 * TC-FMG-007: FMG_ClassifyAndEscalate — HAL fault bit (0x10) → FAULT_CRITICAL
 * Tests: REQ-SAFE-013
 * SIL: 3
 * ========================================================================= */
void test_FMG_ClassifyAndEscalate_HalFault_Critical(void)
{
    /* TC-FMG-007 */
    fault_severity_t sev = FAULT_NONE;
    (void)FMG_ClassifyAndEscalate(0x10U, &sev); /* FMG_FAULT_BIT_HAL */
    TEST_ASSERT_EQUAL_INT(FAULT_CRITICAL, sev);
}

/* =========================================================================
 * TC-FMG-008: FMG_ClassifyAndEscalate — NULL out → ERR_NULL_PTR
 * Tests: REQ-SAFE-013
 * SIL: 3
 * ========================================================================= */
void test_FMG_ClassifyAndEscalate_NullOut(void)
{
    /* TC-FMG-008 */
    error_t ret = FMG_ClassifyAndEscalate(0x01U, NULL);
    TEST_ASSERT_EQUAL_INT(ERR_NULL_PTR, ret);
}

/* =========================================================================
 * TC-FMG-009: FMG_ProcessEmergencyStop — sets g_fmg_emergency_stop_active flag
 * Tests: REQ-SAFE-021
 * SIL: 3
 * ========================================================================= */
extern uint8_t g_fmg_emergency_stop_active;

void test_FMG_ProcessEmergencyStop_SetsFlag(void)
{
    /* TC-FMG-009 */
    g_fmg_emergency_stop_active = 0U; /* ensure clean state */
    error_t ret = FMG_ProcessEmergencyStop(1U);
    TEST_ASSERT_EQUAL_INT(SUCCESS, ret);
    TEST_ASSERT_EQUAL_UINT8(1U, g_fmg_emergency_stop_active);
}

/* =========================================================================
 * TC-FMG-010: FMG_RunCycle — no faults from stubs → fault_state=0
 * Tests: REQ-SAFE-012
 * SIL: 3
 * Coverage target: Statement + Branch coverage per SVP/SQAP project target
 * ========================================================================= */
void test_FMG_RunCycle_NoFaults(void)
{
    /* TC-FMG-010 */
    fmg_stub_reset_all(); /* all fault stubs return 0 */
    FMG_RunCycle();
    TEST_ASSERT_EQUAL_UINT8(0U, FMG_GetFaultState());
    TEST_ASSERT_EQUAL_UINT8(0U, FMG_GetFault());
}

/* =========================================================================
 * TC-FMG-011: FMG_RunCycle — SPM fault injected → fault_state non-zero
 * Tests: REQ-SAFE-012/013
 * SIL: 3
 * Coverage target: Branch coverage per SVP/SQAP project target
 * ========================================================================= */
void test_FMG_RunCycle_SpmFault_SetsFaultState(void)
{
    /* TC-FMG-011 */
    fmg_stub_set_spm_fault(1U);
    FMG_RunCycle();
    TEST_ASSERT_NOT_EQUAL(0U, FMG_GetFaultState());
    TEST_ASSERT_EQUAL_UINT8(1U, FMG_GetFault());
}

/* =========================================================================
 * TC-FMG-012: FMG_RunCycle — DSM fault injected → fault_state non-zero
 * Tests: REQ-SAFE-012/013
 * SIL: 3
 * Coverage target: Branch coverage per SVP/SQAP project target
 * ========================================================================= */
void test_FMG_RunCycle_DsmFault_SetsFaultState(void)
{
    /* TC-FMG-012 */
    fmg_stub_set_dsm_fault(1U);
    FMG_RunCycle();
    TEST_ASSERT_NOT_EQUAL(0U, FMG_GetFaultState());
}

/* =========================================================================
 * TC-FMG-013: FMG_RunCycle — OBD fault injected → fault_state non-zero
 * Tests: REQ-SAFE-012
 * SIL: 3
 * Coverage target: Branch coverage per SVP/SQAP project target
 * ========================================================================= */
void test_FMG_RunCycle_ObdFault_SetsFaultState(void)
{
    /* TC-FMG-013 */
    fmg_stub_set_obd_fault(1U);
    FMG_RunCycle();
    TEST_ASSERT_NOT_EQUAL(0U, FMG_GetFaultState());
}

/* =========================================================================
 * TC-FMG-014: FMG_RunCycle — TCI fault injected → fault_state non-zero
 * Tests: REQ-SAFE-012
 * SIL: 3
 * Coverage target: Branch coverage per SVP/SQAP project target
 * ========================================================================= */
void test_FMG_RunCycle_TciFault_SetsFaultState(void)
{
    /* TC-FMG-014 */
    fmg_stub_set_tci_fault(1U);
    FMG_RunCycle();
    TEST_ASSERT_NOT_EQUAL(0U, FMG_GetFaultState());
}

/* =========================================================================
 * TC-FMG-015: FMG_GetFault — fault_state=0 after Init → returns 0
 * Tests: REQ-SAFE-012
 * SIL: 3
 * Coverage target: Branch coverage per SVP/SQAP project target
 * ========================================================================= */
void test_FMG_GetFault_AfterInit_ReturnsZero(void)
{
    /* TC-FMG-015 */
    (void)FMG_Init();
    TEST_ASSERT_EQUAL_UINT8(0U, FMG_GetFault());
}

/* =========================================================================
 * TC-FMG-016: FMG_GetFault — after RunCycle with fault → returns 1
 * Tests: REQ-SAFE-012
 * SIL: 3
 * Coverage target: Branch coverage per SVP/SQAP project target
 * ========================================================================= */
void test_FMG_GetFault_AfterRunCycle_WithFault_ReturnsOne(void)
{
    /* TC-FMG-016 */
    fmg_stub_set_spm_fault(1U);
    FMG_RunCycle();
    TEST_ASSERT_EQUAL_UINT8(1U, FMG_GetFault());
}

/* =========================================================================
 * TC-FMG-017: FMG_RunCycle — all faults injected → fault_state has all bits
 * Tests: REQ-SAFE-012/013
 * SIL: 3
 * Coverage target: Statement + Branch + Compound Condition coverage
 * ========================================================================= */
void test_FMG_RunCycle_AllFaults(void)
{
    /* TC-FMG-017 */
    fmg_stub_set_spm_fault(1U);
    fmg_stub_set_obd_fault(1U);
    fmg_stub_set_dsm_fault(1U);
    fmg_stub_set_tci_fault(1U);
    FMG_RunCycle();
    /* With all component faults set, fault_state must be non-zero */
    TEST_ASSERT_NOT_EQUAL(0U, FMG_GetFaultState());
    TEST_ASSERT_EQUAL_UINT8(1U, FMG_GetFault());
}

/* =========================================================================
 * Main
 * ========================================================================= */
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_FMG_Init_Success);
    RUN_TEST(test_FMG_AggregateFaults_NoFaults);
    RUN_TEST(test_FMG_AggregateFaults_SpmFault);
    RUN_TEST(test_FMG_AggregateFaults_HalFault);
    RUN_TEST(test_FMG_AggregateFaults_NullOut);
    RUN_TEST(test_FMG_ClassifyAndEscalate_NoFault);
    RUN_TEST(test_FMG_ClassifyAndEscalate_HalFault_Critical);
    RUN_TEST(test_FMG_ClassifyAndEscalate_NullOut);
    RUN_TEST(test_FMG_ProcessEmergencyStop_SetsFlag);
    RUN_TEST(test_FMG_RunCycle_NoFaults);
    RUN_TEST(test_FMG_RunCycle_SpmFault_SetsFaultState);
    RUN_TEST(test_FMG_RunCycle_DsmFault_SetsFaultState);
    RUN_TEST(test_FMG_RunCycle_ObdFault_SetsFaultState);
    RUN_TEST(test_FMG_RunCycle_TciFault_SetsFaultState);
    RUN_TEST(test_FMG_GetFault_AfterInit_ReturnsZero);
    RUN_TEST(test_FMG_GetFault_AfterRunCycle_WithFault_ReturnsOne);
    RUN_TEST(test_FMG_RunCycle_AllFaults);

    return UNITY_END();
}
