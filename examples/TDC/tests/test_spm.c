/**
 * @file    test_spm.c
 * @brief   Unit tests for SPM module (COMP-002) — 14 test cases.
 * @details Covers TC-SPM-001 through TC-SPM-014.
 *          Tests: SPM_ProcessSpeedFrame, SPM_EvaluateInterlock, SPM_Init,
 *                 SPM_GetSpeed, SPM_GetFault.
 *
 * @project TDC (Train Door Control System)
 * @phase   Phase 5 — Implementation & Testing
 * @sil     3
 * @date    2026-04-04
 *
 * @traceability
 *   Tests: REQ-SAFE-003/004/016/018
 *   Item 16: Software Component Test Specification §COMP-002
 *   Item 18: Source Code (spm_can.c)
 */

#include "../unity/src/unity.h"
#include "../../src/tdc_types.h"
#include "../../src/spm.h"
#include "../../src/hal.h"

/* =========================================================================
 * TCI stub: spm_can.c calls TCI_GetSpeedFramePtr() which needs
 *           a stub to return controllable frames.
 * ========================================================================= */

/* Override provided via spm_tci_stub.c */
extern void spm_stub_set_speed_frame(const tcms_speed_msg_t *f, uint8_t valid);

extern uint32_t hal_stub_tick_ms;

/* SPM_CRC_DATA_LEN = sizeof(tcms_speed_msg_t) - sizeof(uint16_t).
 * tcms_speed_msg_t: uint16_t speed(2) + uint8_t seq(1) + pad(1) + uint16_t crc(2) = 6.
 * CRC_DATA_LEN = 6 - 2 = 4.
 * Build valid frames by populating struct fields then computing CRC over the
 * struct bytes (NOT a separate 3-byte array — struct padding must be included). */
#define SPM_CRC_DATA_LEN_TEST  \
    ((uint16_t)(sizeof(tcms_speed_msg_t) - sizeof(uint16_t)))

/**
 * @brief Build a valid speed frame with correct CRC.
 * @param[out] frame  Frame to populate.
 * @param[in]  speed  Speed value (km/h × 10).
 * @param[in]  seq    Sequence counter.
 */
static void build_speed_frame(tcms_speed_msg_t *frame,
                               uint16_t speed, uint8_t seq)
{
    frame->speed_kmh_x10 = speed;
    frame->seq_counter   = seq;
    frame->crc16         = 0U;  /* zero CRC field before computing */
    frame->crc16 = CRC16_CCITT_Compute((const uint8_t *)frame,
                                        SPM_CRC_DATA_LEN_TEST);
}

/* =========================================================================
 * setUp / tearDown
 * ========================================================================= */
void setUp(void)
{
    hal_stub_tick_ms = 0U;
    (void)HAL_Init();
    (void)SPM_Init();
    spm_stub_set_speed_frame(NULL, 0U);
}

void tearDown(void) {}

/* =========================================================================
 * TC-SPM-001: SPM_Init — returns SUCCESS
 * Tests: REQ-SAFE-004
 * SIL: 3
 * ========================================================================= */
void test_SPM_Init_Success(void)
{
    /* TC-SPM-001 */
    error_t ret = SPM_Init();
    TEST_ASSERT_EQUAL_INT(SUCCESS, ret);
}

/* =========================================================================
 * TC-SPM-002: SPM_GetSpeed — returns SPM_SPEED_UNKNOWN (0xFFFF) after init
 *             (fail-safe: no frame received yet)
 * Tests: REQ-SAFE-004
 * SIL: 3
 * ========================================================================= */
void test_SPM_GetSpeed_AfterInit(void)
{
    /* TC-SPM-002
     * SPM_Init() sets s_current_speed_kmh_x10 = SPM_SPEED_UNKNOWN = 0xFFFF
     * as a fail-safe sentinel.  SPM_GetSpeed() returns this value unchanged. */
    uint16_t speed = SPM_GetSpeed();
    TEST_ASSERT_EQUAL_UINT16(0xFFFFU, speed);
}

/* =========================================================================
 * TC-SPM-003: SPM_ProcessSpeedFrame — valid frame, CRC OK, stores speed
 * Tests: REQ-SAFE-004/016
 * SIL: 3
 * ========================================================================= */
void test_SPM_ProcessSpeedFrame_ValidFrame(void)
{
    /* TC-SPM-003
     * CRC is computed over sizeof(tcms_speed_msg_t)-sizeof(uint16_t) bytes,
     * which includes the padding byte between seq_counter and crc16.
     * Use build_speed_frame() to produce a correctly-CRC'd struct. */
    tcms_speed_msg_t frame;
    build_speed_frame(&frame, 300U, 0U);

    spm_stub_set_speed_frame(&frame, 1U);
    hal_stub_tick_ms = 100U;
    SPM_RunCycle();

    TEST_ASSERT_EQUAL_UINT16(300U, SPM_GetSpeed());
}

/* =========================================================================
 * TC-SPM-004: SPM_EvaluateInterlock — speed=0, no timeout → interlock=0
 * Tests: REQ-SAFE-003/018
 * SIL: 3
 * ========================================================================= */
void test_SPM_EvaluateInterlock_SpeedZero(void)
{
    /* TC-SPM-004
     * Inject a valid frame with speed=0 so the speed is known.
     * Then evaluate within the 200 ms timeout window. */
    tcms_speed_msg_t frame;
    build_speed_frame(&frame, 0U, 0U);
    spm_stub_set_speed_frame(&frame, 1U);
    hal_stub_tick_ms = 50U;
    SPM_RunCycle();

    uint8_t interlock = 1U;
    error_t ret = SPM_EvaluateInterlock(50U, &interlock);
    TEST_ASSERT_EQUAL_INT(SUCCESS, ret);
    /* speed=0 <= SPEED_THRESHOLD(50) → interlock=0 */
    TEST_ASSERT_EQUAL_UINT8(0U, interlock);
}

/* =========================================================================
 * TC-SPM-005: SPM_EvaluateInterlock — speed above threshold → interlock=1
 * Tests: REQ-SAFE-003/018
 * SIL: 3
 * ========================================================================= */
void test_SPM_EvaluateInterlock_SpeedAboveThreshold(void)
{
    /* TC-SPM-005
     * SPEED_THRESHOLD = 50 (5.0 km/h × 10).
     * Inject speed = 510 (51 km/h × 10) > 50 → interlock active. */
    tcms_speed_msg_t frame;
    build_speed_frame(&frame, 510U, 0U);

    spm_stub_set_speed_frame(&frame, 1U);
    hal_stub_tick_ms = 100U;
    SPM_RunCycle();

    uint8_t interlock = 0U;
    (void)SPM_EvaluateInterlock(100U, &interlock);
    TEST_ASSERT_EQUAL_UINT8(1U, interlock);
}

/* =========================================================================
 * TC-SPM-006: SPM_EvaluateInterlock — speed = SPEED_THRESHOLD (exact = 50)
 *             → interlock=0 (threshold is STRICTLY >; 50 == 50 is safe)
 * Tests: REQ-SAFE-003, OI-FMEA-002
 * SIL: 3
 * ========================================================================= */
void test_SPM_EvaluateInterlock_SpeedExactThreshold(void)
{
    /* TC-SPM-006
     * SPEED_THRESHOLD = 50 (5.0 km/h × 10).
     * Inject speed = 50 (exactly at threshold).
     * Condition is (speed > SPEED_THRESHOLD) = (50 > 50) = false → interlock=0. */
    tcms_speed_msg_t frame;
    build_speed_frame(&frame, 50U, 0U);

    spm_stub_set_speed_frame(&frame, 1U);
    hal_stub_tick_ms = 100U;
    SPM_RunCycle();

    uint8_t interlock = 1U;
    (void)SPM_EvaluateInterlock(100U, &interlock);
    /* speed=50 == SPEED_THRESHOLD=50; condition is > 50 → false → interlock=0 */
    TEST_ASSERT_EQUAL_UINT8(0U, interlock);
}

/* =========================================================================
 * TC-SPM-007: SPM_EvaluateInterlock — CAN timeout (>200ms) → interlock=1
 * Tests: REQ-SAFE-003
 * SIL: 3
 * ========================================================================= */
void test_SPM_EvaluateInterlock_CanTimeout(void)
{
    /* TC-SPM-007 */
    /* No frame received — last_valid_rx_ms stays 0 */
    /* Advance tick past timeout */
    uint8_t interlock = 0U;
    hal_stub_tick_ms = 250U; /* > CAN_TIMEOUT_MS=200 */
    (void)SPM_EvaluateInterlock(250U, &interlock);
    TEST_ASSERT_EQUAL_UINT8(1U, interlock);
}

/* =========================================================================
 * TC-SPM-008: SPM_EvaluateInterlock — NULL out → ERR_NULL_PTR
 * Tests: REQ-SAFE-003
 * SIL: 3
 * ========================================================================= */
void test_SPM_EvaluateInterlock_NullOut(void)
{
    /* TC-SPM-008 */
    error_t ret = SPM_EvaluateInterlock(0U, NULL);
    TEST_ASSERT_EQUAL_INT(ERR_NULL_PTR, ret);
}

/* =========================================================================
 * TC-SPM-009: SPM_ProcessSpeedFrame — seq counter normal increment (0→1)
 * Tests: REQ-SAFE-016
 * SIL: 3
 * ========================================================================= */
void test_SPM_ProcessSpeedFrame_SeqIncrement(void)
{
    /* TC-SPM-009 — seq 0 → 1, valid */
    tcms_speed_msg_t frame;

    /* First frame: seq=0 */
    build_speed_frame(&frame, 100U, 0U);
    spm_stub_set_speed_frame(&frame, 1U);
    hal_stub_tick_ms = 50U;
    SPM_RunCycle();

    /* Second frame: seq=1 */
    build_speed_frame(&frame, 100U, 1U);
    spm_stub_set_speed_frame(&frame, 1U);
    hal_stub_tick_ms = 70U;
    SPM_RunCycle();

    /* SPM_GetFault should be 0 (no CRC or seq fault) */
    TEST_ASSERT_EQUAL_UINT8(0U, SPM_GetFault());
}

/* =========================================================================
 * TC-SPM-010: SPM_ProcessSpeedFrame — seq counter rollover (255→0) is valid
 * Tests: REQ-SAFE-016
 * SIL: 3
 * ========================================================================= */
void test_SPM_ProcessSpeedFrame_SeqRollover(void)
{
    /* TC-SPM-010 */
    tcms_speed_msg_t frame;

    /* Frame at seq=255 */
    build_speed_frame(&frame, 50U, 255U);
    spm_stub_set_speed_frame(&frame, 1U);
    hal_stub_tick_ms = 50U;
    SPM_RunCycle();

    /* Rollover: seq=0 */
    build_speed_frame(&frame, 50U, 0U);
    spm_stub_set_speed_frame(&frame, 1U);
    hal_stub_tick_ms = 70U;
    SPM_RunCycle();

    TEST_ASSERT_EQUAL_UINT16(50U, SPM_GetSpeed());
}

/* =========================================================================
 * TC-SPM-011: SPM_RunCycle — no frame available (NULL ptr from TCI) → no fault
 * Tests: REQ-SAFE-004
 * SIL: 3
 * ========================================================================= */
void test_SPM_RunCycle_NoFrame(void)
{
    /* TC-SPM-011 */
    spm_stub_set_speed_frame(NULL, 0U);
    hal_stub_tick_ms = 10U;
    SPM_RunCycle();
    /* Within timeout — no fault */
    TEST_ASSERT_EQUAL_UINT8(0U, SPM_GetFault());
}

/* =========================================================================
 * TC-SPM-012: SPM_GetFault — returns 0 after clean init
 * Tests: REQ-SAFE-004
 * SIL: 3
 * ========================================================================= */
void test_SPM_GetFault_AfterInit(void)
{
    /* TC-SPM-012 */
    TEST_ASSERT_EQUAL_UINT8(0U, SPM_GetFault());
}

/* =========================================================================
 * TC-SPM-013: SPM_EvaluateInterlock — boundary: tick=200 (exactly CAN_TIMEOUT_MS)
 *             → interlock stays 0 (timeout is STRICTLY >)
 * Tests: REQ-SAFE-003
 * SIL: 3
 * ========================================================================= */
void test_SPM_EvaluateInterlock_ExactTimeout(void)
{
    /* TC-SPM-013
     * Receive a frame with speed=0 at tick=0 so speed is known.
     * Evaluate at exactly 200 ms: elapsed = 200 - 0 = 200.
     * Condition: elapsed_ms > CAN_TIMEOUT_MS = 200 > 200 = false.
     * Speed = 0 <= 50 → interlock = 0. */
    tcms_speed_msg_t frame;
    build_speed_frame(&frame, 0U, 0U);
    spm_stub_set_speed_frame(&frame, 1U);
    hal_stub_tick_ms = 0U;
    SPM_RunCycle();

    uint8_t interlock = 1U;
    (void)SPM_EvaluateInterlock(200U, &interlock);
    TEST_ASSERT_EQUAL_UINT8(0U, interlock);
}

/* =========================================================================
 * TC-SPM-014: SPM_EvaluateInterlock — boundary: tick=201 → interlock=1
 * Tests: REQ-SAFE-003
 * SIL: 3
 * ========================================================================= */
void test_SPM_EvaluateInterlock_JustPastTimeout(void)
{
    /* TC-SPM-014 */
    tcms_speed_msg_t frame;
    build_speed_frame(&frame, 0U, 0U);
    spm_stub_set_speed_frame(&frame, 1U);
    hal_stub_tick_ms = 0U;
    SPM_RunCycle();

    uint8_t interlock = 0U;
    (void)SPM_EvaluateInterlock(201U, &interlock);
    /* elapsed = 201 > 200 → timeout → interlock=1 */
    TEST_ASSERT_EQUAL_UINT8(1U, interlock);
}

/* =========================================================================
 * Main
 * ========================================================================= */
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_SPM_Init_Success);
    RUN_TEST(test_SPM_GetSpeed_AfterInit);
    RUN_TEST(test_SPM_ProcessSpeedFrame_ValidFrame);
    RUN_TEST(test_SPM_EvaluateInterlock_SpeedZero);
    RUN_TEST(test_SPM_EvaluateInterlock_SpeedAboveThreshold);
    RUN_TEST(test_SPM_EvaluateInterlock_SpeedExactThreshold);
    RUN_TEST(test_SPM_EvaluateInterlock_CanTimeout);
    RUN_TEST(test_SPM_EvaluateInterlock_NullOut);
    RUN_TEST(test_SPM_ProcessSpeedFrame_SeqIncrement);
    RUN_TEST(test_SPM_ProcessSpeedFrame_SeqRollover);
    RUN_TEST(test_SPM_RunCycle_NoFrame);
    RUN_TEST(test_SPM_GetFault_AfterInit);
    RUN_TEST(test_SPM_EvaluateInterlock_ExactTimeout);
    RUN_TEST(test_SPM_EvaluateInterlock_JustPastTimeout);

    return UNITY_END();
}
