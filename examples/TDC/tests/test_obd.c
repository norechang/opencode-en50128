/**
 * @file    test_obd.c
 * @brief   Unit tests for OBD module (COMP-008) — 9 test cases.
 * @details Covers TC-OBD-001 through TC-OBD-009.
 *          Tests: OBD_PollSensorsAndEvaluate, OBD_Init, OBD_GetFault,
 *                 OBD_GetObstacleFlags.
 *
 * @project TDC (Train Door Control System)
 * @phase   Phase 5 — Implementation & Testing
 * @sil     3
 * @date    2026-04-04
 *
 * @traceability
 *   Tests: REQ-SAFE-009/017
 *   Item 16: Software Component Test Specification §COMP-008
 *   Item 18: Source Code (obd_detect.c)
 */

#include "../unity/src/unity.h"
#include "../../src/tdc_types.h"
#include "../../src/obd.h"
#include "../../src/hal.h"

/* =========================================================================
 * OBD DSM stub control (obd_dsm_stub.c)
 * ========================================================================= */
extern void obd_stub_set_closing_flags(const uint8_t flags[MAX_DOORS]);

extern uint8_t hal_stub_gpio_value;

/* =========================================================================
 * setUp / tearDown
 * ========================================================================= */
void setUp(void)
{
    uint8_t no_close[MAX_DOORS] = {0U, 0U, 0U, 0U};
    hal_stub_gpio_value = 0U;
    obd_stub_set_closing_flags(no_close);
    (void)HAL_Init();
    (void)OBD_Init();
}

void tearDown(void) {}

/* =========================================================================
 * TC-OBD-001: OBD_Init — returns SUCCESS
 * Tests: REQ-SAFE-009
 * SIL: 3
 * ========================================================================= */
void test_OBD_Init_Success(void)
{
    /* TC-OBD-001 */
    error_t ret = OBD_Init();
    TEST_ASSERT_EQUAL_INT(SUCCESS, ret);
}

/* =========================================================================
 * TC-OBD-002: OBD_PollSensorsAndEvaluate — NULL door_closing_flags →
 *             fail-safe: all obstacle flags set, returns ERR_NULL_PTR
 * Tests: REQ-SAFE-009
 * SIL: 3
 * ========================================================================= */
void test_OBD_PollSensorsAndEvaluate_NullClosingFlags(void)
{
    /* TC-OBD-002 */
    uint8_t obs[MAX_DOORS] = {0U, 0U, 0U, 0U};
    error_t ret = OBD_PollSensorsAndEvaluate(NULL, obs);
    TEST_ASSERT_EQUAL_INT(ERR_NULL_PTR, ret);
    /* Fail-safe: all obstacle flags set */
    TEST_ASSERT_EQUAL_UINT8(1U, obs[0]);
    TEST_ASSERT_EQUAL_UINT8(1U, obs[1]);
    TEST_ASSERT_EQUAL_UINT8(1U, obs[2]);
    TEST_ASSERT_EQUAL_UINT8(1U, obs[3]);
}

/* =========================================================================
 * TC-OBD-003: OBD_PollSensorsAndEvaluate — NULL obstacle_flags_out →
 *             ERR_NULL_PTR
 * Tests: REQ-SAFE-009
 * SIL: 3
 * ========================================================================= */
void test_OBD_PollSensorsAndEvaluate_NullObstacleOut(void)
{
    /* TC-OBD-003 */
    uint8_t closing[MAX_DOORS] = {0U, 0U, 0U, 0U};
    error_t ret = OBD_PollSensorsAndEvaluate(closing, NULL);
    TEST_ASSERT_EQUAL_INT(ERR_NULL_PTR, ret);
}

/* =========================================================================
 * TC-OBD-004: OBD_PollSensorsAndEvaluate — door not closing, no sensor →
 *             obstacle_flag=0
 * Tests: REQ-SAFE-009/017
 * SIL: 3
 * ========================================================================= */
void test_OBD_PollSensorsAndEvaluate_NotClosing_NoObstacle(void)
{
    /* TC-OBD-004 */
    uint8_t closing[MAX_DOORS] = {0U, 0U, 0U, 0U};
    uint8_t obs[MAX_DOORS]     = {1U, 1U, 1U, 1U};
    hal_stub_gpio_value = 0U; /* No force detected */
    error_t ret = OBD_PollSensorsAndEvaluate(closing, obs);
    TEST_ASSERT_EQUAL_INT(SUCCESS, ret);
    TEST_ASSERT_EQUAL_UINT8(0U, obs[0]);
}

/* =========================================================================
 * TC-OBD-005: OBD_PollSensorsAndEvaluate — door IS closing, sensor reads
 *             below threshold → obstacle_flag=0
 * Tests: REQ-SAFE-009/017
 * SIL: 3
 * ========================================================================= */
void test_OBD_PollSensorsAndEvaluate_Closing_BelowThreshold(void)
{
    /* TC-OBD-005 */
    uint8_t closing[MAX_DOORS] = {1U, 0U, 0U, 0U};
    uint8_t obs[MAX_DOORS]     = {0U, 0U, 0U, 0U};
    /* The OBD HAL returns ADC value; stub returns 0 → below OBD_MAX_FORCE_ADC */
    error_t ret = OBD_PollSensorsAndEvaluate(closing, obs);
    TEST_ASSERT_EQUAL_INT(SUCCESS, ret);
    TEST_ASSERT_EQUAL_UINT8(0U, obs[0]);
}

/* =========================================================================
 * TC-OBD-006: OBD_GetFault — returns 0 after clean init
 * Tests: REQ-SAFE-009
 * SIL: 3
 * ========================================================================= */
void test_OBD_GetFault_AfterInit(void)
{
    /* TC-OBD-006 */
    uint8_t fault = OBD_GetFault();
    TEST_ASSERT_EQUAL_UINT8(0U, fault);
}

/* =========================================================================
 * TC-OBD-007: OBD_GetObstacleFlags — returns non-NULL pointer
 * Tests: REQ-SAFE-009
 * SIL: 3
 * ========================================================================= */
void test_OBD_GetObstacleFlags_NotNull(void)
{
    /* TC-OBD-007 */
    const uint8_t *flags = OBD_GetObstacleFlags();
    TEST_ASSERT_NOT_NULL(flags);
}

/* =========================================================================
 * TC-OBD-008: OBD_RunCycle — returns without crash after init
 * Tests: REQ-SAFE-009
 * SIL: 3
 * ========================================================================= */
void test_OBD_RunCycle_Runs(void)
{
    /* TC-OBD-008 */
    OBD_RunCycle(); /* Must not crash or assert */
    TEST_ASSERT_TRUE(1); /* Reaching here = PASS */
}

/* =========================================================================
 * TC-OBD-009: OBD_PollSensorsAndEvaluate — all doors closing, GPIO=0 →
 *             all obstacle flags 0 (below threshold)
 * Tests: REQ-SAFE-017
 * SIL: 3
 * ========================================================================= */
void test_OBD_PollSensorsAndEvaluate_AllClosing_NoForce(void)
{
    /* TC-OBD-009 */
    uint8_t closing[MAX_DOORS] = {1U, 1U, 1U, 1U};
    uint8_t obs[MAX_DOORS]     = {1U, 1U, 1U, 1U};
    hal_stub_gpio_value = 0U;
    error_t ret = OBD_PollSensorsAndEvaluate(closing, obs);
    TEST_ASSERT_EQUAL_INT(SUCCESS, ret);
    uint8_t i;
    for (i = 0U; i < MAX_DOORS; i++) {
        TEST_ASSERT_EQUAL_UINT8(0U, obs[i]);
    }
}

/* =========================================================================
 * Main
 * ========================================================================= */
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_OBD_Init_Success);
    RUN_TEST(test_OBD_PollSensorsAndEvaluate_NullClosingFlags);
    RUN_TEST(test_OBD_PollSensorsAndEvaluate_NullObstacleOut);
    RUN_TEST(test_OBD_PollSensorsAndEvaluate_NotClosing_NoObstacle);
    RUN_TEST(test_OBD_PollSensorsAndEvaluate_Closing_BelowThreshold);
    RUN_TEST(test_OBD_GetFault_AfterInit);
    RUN_TEST(test_OBD_GetObstacleFlags_NotNull);
    RUN_TEST(test_OBD_RunCycle_Runs);
    RUN_TEST(test_OBD_PollSensorsAndEvaluate_AllClosing_NoForce);

    return UNITY_END();
}
