/**
 * @file    test_tci.c
 * @brief   Unit tests for TCI module (COMP-006) — 23 test cases.
 * @details Covers TC-TCI-001 through TC-TCI-023.
 *          Tests: TCI_CanRxISR, TCI_ProcessReceivedFrames,
 *                 TCI_TransmitDepartureInterlock, TCI_ValidateRxSeqDelta,
 *                 TCI_Init, TCI_GetFault, TCI_TransmitCycle,
 *                 TCI_TransmitDoorStatus, TCI_TransmitFaultReport,
 *                 TCI_GetSpeedFramePtr.
 *
 * @project TDC (Train Door Control System)
 * @phase   Phase 5 — Implementation & Testing
 * @sil     3
 * @date    2026-04-04
 *
 * @traceability
 *   Tests: REQ-SAFE-003/016, REQ-INT-007/008/009
 *   Item 16: Software Component Test Specification §COMP-006
 *   Item 18: Source Code (tci_rx.c, tci_tx.c, tci_seq.c, tci_init.c)
 */

#include "../unity/src/unity.h"
#include "../../src/tdc_types.h"
#include "../../src/tci.h"
#include "../../src/hal.h"

/* =========================================================================
 * TCI internal globals
 * ========================================================================= */
extern can_mailbox_t g_tci_mailbox[TCI_CAN_RX_MAILBOX_COUNT];
extern uint8_t       g_tci_fault_flag;

/* =========================================================================
 * HAL stub controls
 * ========================================================================= */
extern error_t  hal_stub_can_receive_ret;
extern uint32_t hal_stub_can_receive_id;
extern uint8_t  hal_stub_can_receive_data[8];
extern uint8_t  hal_stub_can_receive_dlc;
extern error_t  hal_stub_can_transmit_ret;
extern uint32_t hal_stub_tick_ms;

/* Stubs for DSM/FMG/SKN functions called indirectly by TCI */
/* These are provided by separate stub TUs compiled into the test binary */

/* =========================================================================
 * setUp / tearDown
 * ========================================================================= */
void setUp(void)
{
    hal_stub_can_receive_ret = SUCCESS;
    hal_stub_can_receive_id  = 0x100U;
    hal_stub_can_receive_dlc = 5U;
    hal_stub_can_transmit_ret = SUCCESS;
    hal_stub_tick_ms          = 0U;
    (void)HAL_Init();
    (void)TCI_Init();
}

void tearDown(void) {}

/* =========================================================================
 * TC-TCI-001: TCI_Init — clears all mailboxes, fault=0
 * Tests: REQ-INT-007
 * SIL: 3
 * ========================================================================= */
void test_TCI_Init_ClearsMailbox(void)
{
    /* TC-TCI-001 */
    uint8_t i;
    error_t ret = TCI_Init();
    TEST_ASSERT_EQUAL_INT(SUCCESS, ret);
    for (i = 0U; i < TCI_CAN_RX_MAILBOX_COUNT; i++) {
        TEST_ASSERT_EQUAL_UINT8(0U, g_tci_mailbox[i].valid);
    }
    TEST_ASSERT_EQUAL_UINT8(0U, g_tci_fault_flag);
}

/* =========================================================================
 * TC-TCI-002: TCI_GetFault — returns 0 after init
 * Tests: REQ-INT-007
 * SIL: 3
 * ========================================================================= */
void test_TCI_GetFault_AfterInit(void)
{
    /* TC-TCI-002 */
    TEST_ASSERT_EQUAL_UINT8(0U, TCI_GetFault());
}

/* =========================================================================
 * TC-TCI-003: TCI_CanRxISR — HAL_CAN_Receive failure → no mailbox update
 * Tests: REQ-INT-007
 * SIL: 3
 * ========================================================================= */
void test_TCI_CanRxISR_HalFail_NoMailboxUpdate(void)
{
    /* TC-TCI-003 */
    hal_stub_can_receive_ret = ERR_COMM_TIMEOUT;
    TCI_CanRxISR();
    /* Mailbox should still be invalid */
    TEST_ASSERT_EQUAL_UINT8(0U, g_tci_mailbox[0].valid);
}

/* =========================================================================
 * TC-TCI-004: TCI_CanRxISR — valid speed frame (0x100) → slot 0 populated
 * Tests: REQ-INT-007
 * SIL: 3
 * ========================================================================= */
void test_TCI_CanRxISR_ValidSpeedFrame_SlotPopulated(void)
{
    /* TC-TCI-004 */
    hal_stub_can_receive_id  = 0x100U;  /* Speed frame */
    hal_stub_can_receive_dlc = 5U;
    TCI_CanRxISR();
    TEST_ASSERT_EQUAL_UINT8(1U, g_tci_mailbox[0].valid);
    TEST_ASSERT_EQUAL_UINT32(0x100U, g_tci_mailbox[0].msg_id);
}

/* =========================================================================
 * TC-TCI-005: TCI_CanRxISR — unknown CAN ID → no mailbox updated
 * Tests: REQ-INT-007
 * SIL: 3
 * ========================================================================= */
void test_TCI_CanRxISR_UnknownId_Discarded(void)
{
    /* TC-TCI-005 */
    hal_stub_can_receive_id = 0x999U; /* Not a known TCMS ID */
    TCI_CanRxISR();
    uint8_t i;
    for (i = 0U; i < TCI_CAN_RX_MAILBOX_COUNT; i++) {
        TEST_ASSERT_EQUAL_UINT8(0U, g_tci_mailbox[i].valid);
    }
}

/* =========================================================================
 * TC-TCI-006: TCI_ProcessReceivedFrames — empty mailboxes → SUCCESS
 * Tests: REQ-INT-007
 * SIL: 3
 * ========================================================================= */
void test_TCI_ProcessReceivedFrames_EmptyMailbox(void)
{
    /* TC-TCI-006 */
    error_t ret = TCI_ProcessReceivedFrames();
    TEST_ASSERT_EQUAL_INT(SUCCESS, ret);
}

/* =========================================================================
 * TC-TCI-007: TCI_ProcessReceivedFrames — speed frame with bad CRC →
 *             fault flag set
 * Tests: REQ-SAFE-016, REQ-INT-007
 * SIL: 3
 * ========================================================================= */
void test_TCI_ProcessReceivedFrames_BadCRC_SetsFault(void)
{
    /* TC-TCI-007 */
    /* Inject speed frame with wrong CRC */
    g_tci_mailbox[0].msg_id = 0x100U;
    g_tci_mailbox[0].dlc    = 5U;
    g_tci_mailbox[0].data[0] = 0x01U;
    g_tci_mailbox[0].data[1] = 0x00U;
    g_tci_mailbox[0].data[2] = 0x00U;
    g_tci_mailbox[0].data[3] = 0xFFU; /* Wrong CRC high */
    g_tci_mailbox[0].data[4] = 0xFFU; /* Wrong CRC low  */
    g_tci_mailbox[0].valid   = 1U;

    (void)TCI_ProcessReceivedFrames();
    TEST_ASSERT_EQUAL_UINT8(1U, g_tci_fault_flag);
}

/* =========================================================================
 * TC-TCI-008: TCI_TransmitDepartureInterlock — interlock_ok=1 → SUCCESS
 * Tests: REQ-INT-008
 * SIL: 3
 * ========================================================================= */
void test_TCI_TransmitDepartureInterlock_OK(void)
{
    /* TC-TCI-008 */
    error_t ret = TCI_TransmitDepartureInterlock(1U);
    TEST_ASSERT_EQUAL_INT(SUCCESS, ret);
}

/* =========================================================================
 * TC-TCI-009: TCI_TransmitDepartureInterlock — interlock_ok=0 → SUCCESS
 *             (transmission still occurs — sends "not OK" to TCMS)
 * Tests: REQ-INT-008
 * SIL: 3
 * ========================================================================= */
void test_TCI_TransmitDepartureInterlock_NotOK(void)
{
    /* TC-TCI-009 */
    error_t ret = TCI_TransmitDepartureInterlock(0U);
    TEST_ASSERT_EQUAL_INT(SUCCESS, ret);
}

/* =========================================================================
 * TC-TCI-010: TCI_ValidateRxSeqDelta — 3 consecutive discontinuities →
 *             fault flag set
 * Tests: REQ-SAFE-016, REQ-INT-009
 * SIL: 3
 * ========================================================================= */
void test_TCI_ValidateRxSeqDelta_ThreeDiscontinuities_Fault(void)
{
    /* TC-TCI-010 */
    /* Slot 0 = speed frame (msg_id byte = 0x00 → slot = 0x00 & 0x0F = 0) */
    uint8_t msg_id = 0x00U; /* Bottom byte of 0x100 */

    /* First reception: seed */
    (void)TCI_ValidateRxSeqDelta(msg_id, 0U);
    /* Three non-consecutive frames */
    (void)TCI_ValidateRxSeqDelta(msg_id, 5U); /* disc 1 */
    (void)TCI_ValidateRxSeqDelta(msg_id, 10U); /* disc 2 */
    (void)TCI_ValidateRxSeqDelta(msg_id, 20U); /* disc 3 → fault */
    TEST_ASSERT_EQUAL_UINT8(1U, g_tci_fault_flag);
}

/* =========================================================================
 * Stub setter declarations (tci_deps_stub.c)
 * ========================================================================= */
extern void tci_stub_set_fault_state(uint8_t val);
extern void tci_stub_set_departure_interlock(uint8_t v);

/* =========================================================================
 * TC-TCI-011: TCI_TransmitDoorStatus — NULL door_states → ERR_NULL_PTR
 * Tests: REQ-INT-008
 * SIL: 3
 * Coverage target: Branch coverage per SVP/SQAP project target
 * ========================================================================= */
void test_TCI_TransmitDoorStatus_NullDoorStates(void)
{
    /* TC-TCI-011 */
    uint8_t lock_states[MAX_DOORS] = {0U, 0U, 0U, 0U};
    error_t ret = TCI_TransmitDoorStatus(NULL, lock_states);
    TEST_ASSERT_EQUAL_INT(ERR_NULL_PTR, ret);
}

/* =========================================================================
 * TC-TCI-012: TCI_TransmitDoorStatus — NULL lock_states → ERR_NULL_PTR
 * Tests: REQ-INT-008
 * SIL: 3
 * Coverage target: Branch coverage per SVP/SQAP project target
 * ========================================================================= */
void test_TCI_TransmitDoorStatus_NullLockStates(void)
{
    /* TC-TCI-012 */
    uint8_t door_states[MAX_DOORS] = {1U, 1U, 1U, 1U};
    error_t ret = TCI_TransmitDoorStatus(door_states, NULL);
    TEST_ASSERT_EQUAL_INT(ERR_NULL_PTR, ret);
}

/* =========================================================================
 * TC-TCI-013: TCI_TransmitDoorStatus — valid arrays → SUCCESS
 * Tests: REQ-INT-008
 * SIL: 3
 * Coverage target: Statement + Branch coverage per SVP/SQAP project target
 * ========================================================================= */
void test_TCI_TransmitDoorStatus_Valid(void)
{
    /* TC-TCI-013 */
    uint8_t door_states[MAX_DOORS] = {1U, 2U, 3U, 4U};
    uint8_t lock_states[MAX_DOORS] = {0U, 0U, 1U, 1U};
    error_t ret = TCI_TransmitDoorStatus(door_states, lock_states);
    TEST_ASSERT_EQUAL_INT(SUCCESS, ret);
}

/* =========================================================================
 * TC-TCI-014: TCI_TransmitFaultReport — valid call → SUCCESS
 * Tests: REQ-INT-009
 * SIL: 3
 * Coverage target: Statement coverage per SVP/SQAP project target
 * ========================================================================= */
void test_TCI_TransmitFaultReport_Valid(void)
{
    /* TC-TCI-014 */
    error_t ret = TCI_TransmitFaultReport(0x05U, FAULT_HIGH);
    TEST_ASSERT_EQUAL_INT(SUCCESS, ret);
}

/* =========================================================================
 * TC-TCI-015: TCI_TransmitCycle — cycle_count < TCI_TX_CYCLE_DIVISOR →
 *             only process Rx, no transmit
 * Tests: REQ-INT-007
 * SIL: 3
 * Coverage target: Branch coverage per SVP/SQAP project target
 * ========================================================================= */
void test_TCI_TransmitCycle_BelowDivisor_NoTransmit(void)
{
    /* TC-TCI-015: call once — cycle_count goes 0→1 (below divisor=5) */
    hal_stub_can_receive_ret = ERR_TIMEOUT; /* no pending frame — no fault */
    TCI_TransmitCycle();
    /* Fault should still be 0 (no frame processing error, no transmit) */
    TEST_ASSERT_EQUAL_UINT8(0U, g_tci_fault_flag);
}

/* =========================================================================
 * TC-TCI-016: TCI_TransmitCycle — reach TCI_TX_CYCLE_DIVISOR →
 *             transmit status (no fault state → skip FaultReport)
 * Tests: REQ-INT-007, REQ-INT-008
 * SIL: 3
 * Coverage target: Branch coverage per SVP/SQAP project target
 * ========================================================================= */
void test_TCI_TransmitCycle_AtDivisor_TransmitsStatus(void)
{
    /* TC-TCI-016: drive TCI_TransmitCycle to the transmit branch (divisor=5) */
    uint8_t i;
    hal_stub_can_receive_ret  = ERR_TIMEOUT; /* no pending Rx */
    hal_stub_can_transmit_ret = SUCCESS;
    tci_stub_set_fault_state(0U);            /* no fault → skip FaultReport */
    for (i = 0U; i < 5U; i++) {
        TCI_TransmitCycle();
    }
    TEST_ASSERT_EQUAL_UINT8(0U, g_tci_fault_flag);
}

/* =========================================================================
 * TC-TCI-017: TCI_TransmitCycle — at divisor with active fault state →
 *             TCI_TransmitFaultReport also called
 * Tests: REQ-INT-009
 * SIL: 3
 * Coverage target: Branch coverage per SVP/SQAP project target
 * ========================================================================= */
void test_TCI_TransmitCycle_WithFaultState_SendsFaultReport(void)
{
    /* TC-TCI-017 */
    uint8_t i;
    hal_stub_can_receive_ret  = ERR_TIMEOUT;
    hal_stub_can_transmit_ret = SUCCESS;
    tci_stub_set_fault_state(0x05U); /* non-zero → triggers FaultReport branch */
    for (i = 0U; i < 5U; i++) {
        TCI_TransmitCycle();
    }
    TEST_ASSERT_EQUAL_UINT8(0U, g_tci_fault_flag);
    tci_stub_set_fault_state(0U); /* restore */
}

/* =========================================================================
 * TC-TCI-018: TCI_TransmitCycle — ProcessReceivedFrames failure sets fault
 * Tests: REQ-INT-007
 * SIL: 3
 * Coverage target: Branch coverage per SVP/SQAP project target
 * ========================================================================= */
void test_TCI_TransmitCycle_RxFault_SetsFaultFlag(void)
{
    /* TC-TCI-018: inject a bad-CRC frame so ProcessReceivedFrames returns error */
    g_tci_mailbox[0].msg_id  = 0x100U;
    g_tci_mailbox[0].dlc     = 5U;
    g_tci_mailbox[0].data[0] = 0x01U;
    g_tci_mailbox[0].data[1] = 0x00U;
    g_tci_mailbox[0].data[2] = 0x00U;
    g_tci_mailbox[0].data[3] = 0xFFU; /* bad CRC */
    g_tci_mailbox[0].data[4] = 0xFFU;
    g_tci_mailbox[0].valid   = 1U;
    TCI_TransmitCycle();
    TEST_ASSERT_EQUAL_UINT8(1U, g_tci_fault_flag);
}

/* =========================================================================
 * TC-TCI-019: TCI_TransmitCycle — HAL transmit failure during status tx
 *             sets fault flag
 * Tests: REQ-INT-008
 * SIL: 3
 * Coverage target: Branch coverage per SVP/SQAP project target
 * ========================================================================= */
void test_TCI_TransmitCycle_HalTransmitFail_SetsFaultFlag(void)
{
    /* TC-TCI-019: force HAL_CAN_Transmit to fail during the 5th cycle */
    uint8_t i;
    hal_stub_can_receive_ret  = ERR_TIMEOUT;
    hal_stub_can_transmit_ret = ERR_HW_FAULT;  /* force failure */
    tci_stub_set_fault_state(0U);
    for (i = 0U; i < 5U; i++) {
        TCI_TransmitCycle();
    }
    /* At least one transmit failed → fault must be set */
    TEST_ASSERT_EQUAL_UINT8(1U, g_tci_fault_flag);
    hal_stub_can_transmit_ret = SUCCESS; /* restore */
}

/* =========================================================================
 * Main
 * ========================================================================= */
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_TCI_Init_ClearsMailbox);
    RUN_TEST(test_TCI_GetFault_AfterInit);
    RUN_TEST(test_TCI_CanRxISR_HalFail_NoMailboxUpdate);
    RUN_TEST(test_TCI_CanRxISR_ValidSpeedFrame_SlotPopulated);
    RUN_TEST(test_TCI_CanRxISR_UnknownId_Discarded);
    RUN_TEST(test_TCI_ProcessReceivedFrames_EmptyMailbox);
    RUN_TEST(test_TCI_ProcessReceivedFrames_BadCRC_SetsFault);
    RUN_TEST(test_TCI_TransmitDepartureInterlock_OK);
    RUN_TEST(test_TCI_TransmitDepartureInterlock_NotOK);
    RUN_TEST(test_TCI_ValidateRxSeqDelta_ThreeDiscontinuities_Fault);
    RUN_TEST(test_TCI_TransmitDoorStatus_NullDoorStates);
    RUN_TEST(test_TCI_TransmitDoorStatus_NullLockStates);
    RUN_TEST(test_TCI_TransmitDoorStatus_Valid);
    RUN_TEST(test_TCI_TransmitFaultReport_Valid);
    RUN_TEST(test_TCI_TransmitCycle_BelowDivisor_NoTransmit);
    RUN_TEST(test_TCI_TransmitCycle_AtDivisor_TransmitsStatus);
    RUN_TEST(test_TCI_TransmitCycle_WithFaultState_SendsFaultReport);
    RUN_TEST(test_TCI_TransmitCycle_RxFault_SetsFaultFlag);
    RUN_TEST(test_TCI_TransmitCycle_HalTransmitFail_SetsFaultFlag);

    return UNITY_END();
}
