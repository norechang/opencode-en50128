/**
 * @file    test_dgn.c
 * @brief   Unit tests for DGN module (COMP-007, SIL 1) — 3 test cases.
 * @details Covers TC-DGN-001 through TC-DGN-003.
 *          Tests: DGN_LogEvent, DGN_ReadEvent, DGN_GetLogCount.
 *          DGN is SIL 1 — branch coverage HR, statement coverage HR.
 *
 * @project TDC (Train Door Control System)
 * @phase   Phase 5 — Implementation & Testing
 * @sil     1
 * @date    2026-04-04
 *
 * @traceability
 *   Tests: REQ-FUN-018
 *   Item 16: Software Component Test Specification §COMP-007
 *   Item 18: Source Code (dgn_log.c)
 */

#include "../unity/src/unity.h"
#include "../../src/tdc_types.h"
#include "../../src/dgn.h"
#include "../../src/hal.h"

extern uint32_t hal_stub_tick_ms;

/* =========================================================================
 * setUp / tearDown
 * ========================================================================= */
void setUp(void)
{
    hal_stub_tick_ms = 1000U;
    (void)HAL_Init();
    (void)DGN_Init();
}

void tearDown(void) {}

/* =========================================================================
 * TC-DGN-001: DGN_LogEvent — write and read back single entry
 * Tests: REQ-FUN-018
 * SIL: 1
 * Coverage target: Statement + Branch per SVP/SQAP §5.3
 * ========================================================================= */
void test_DGN_LogEvent_WriteAndRead(void)
{
    /* TC-DGN-001 */
    event_log_entry_t entry;
    error_t ret;

    /* Write one event */
    ret = DGN_LogEvent(COMP_SKN, EVT_FSM_FAULT, 0x1234U);
    TEST_ASSERT_EQUAL_INT(SUCCESS, ret);
    TEST_ASSERT_EQUAL_UINT16(1U, DGN_GetLogCount());

    /* Read it back */
    ret = DGN_ReadEvent(0U, &entry);
    TEST_ASSERT_EQUAL_INT(SUCCESS, ret);
    TEST_ASSERT_EQUAL_UINT8(COMP_SKN, entry.source_comp);
    TEST_ASSERT_EQUAL_UINT8(EVT_FSM_FAULT, entry.event_code);
    TEST_ASSERT_EQUAL_UINT16(0x1234U, entry.data);
}

/* =========================================================================
 * TC-DGN-002: DGN_LogEvent — circular buffer wrap (write MAX_LOG_ENTRIES+1)
 * Tests: REQ-FUN-018
 * SIL: 1
 * ========================================================================= */
void test_DGN_LogEvent_CircularWrap(void)
{
    /* TC-DGN-002 */
    uint16_t i;
    /* Fill entire buffer */
    for (i = 0U; i < MAX_LOG_ENTRIES; i++) {
        (void)DGN_LogEvent(COMP_SKN, EVT_LOG_INIT, i);
    }
    /* Count capped at MAX_LOG_ENTRIES */
    TEST_ASSERT_EQUAL_UINT16(MAX_LOG_ENTRIES, DGN_GetLogCount());

    /* Write one more — should wrap, count stays at MAX_LOG_ENTRIES */
    (void)DGN_LogEvent(COMP_SKN, EVT_LOG_INIT, 0xFFFFU);
    TEST_ASSERT_EQUAL_UINT16(MAX_LOG_ENTRIES, DGN_GetLogCount());
}

/* =========================================================================
 * TC-DGN-003: DGN_ReadEvent — NULL out → ERR_NULL_PTR;
 *             index >= count → ERR_RANGE
 * Tests: REQ-FUN-018
 * SIL: 1
 * ========================================================================= */
void test_DGN_ReadEvent_ErrorCases(void)
{
    /* TC-DGN-003 */
    event_log_entry_t entry;

    /* NULL pointer */
    error_t ret = DGN_ReadEvent(0U, NULL);
    TEST_ASSERT_EQUAL_INT(ERR_NULL_PTR, ret);

    /* Out of range (no entries written) */
    ret = DGN_ReadEvent(0U, &entry);
    TEST_ASSERT_EQUAL_INT(ERR_RANGE, ret);
}

/* =========================================================================
 * Main
 * ========================================================================= */
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_DGN_LogEvent_WriteAndRead);
    RUN_TEST(test_DGN_LogEvent_CircularWrap);
    RUN_TEST(test_DGN_ReadEvent_ErrorCases);

    return UNITY_END();
}
