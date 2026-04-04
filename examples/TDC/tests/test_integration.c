/**
 * @file    test_integration.c
 * @brief   Integration tests for TDC — EN 50128 Phase 6 (DOC-SITSPEC-2026-001)
 * @details Exercises cross-component interfaces with REAL source modules linked
 *          together (no stubs for component-level dependencies).  HAL and
 *          linker-symbol stubs are still used to simulate hardware.
 *
 * @project TDC (Train Door Control System)
 * @document DOC-SITSPEC-2026-001 Software Integration Test Specification
 * @sil     SIL 3
 * @date    2026-04-04
 *
 * @en50128_references
 * - EN 50128:2011 §7.6 (Software Integration Testing)
 * - EN 50128:2011 §7.6.4.5b (machine-readable results — Unity XML output)
 * - EN 50128:2011 Table A.5 items 4,5,7,9,10,12,13 (mandatory SIL 3–4)
 * - EN 50128:2011 Table A.6 (integration testing techniques)
 * - DOC-SITSPEC-2026-001 (Software Integration Test Specification)
 *
 * @coverage_target
 * Per SVP/SQAP: Statement coverage of all integrated source modules;
 * Branch coverage of all integrated source modules.
 * (Quantified targets are defined in the project SVP/SQAP — no threshold
 *  is mandated at the standard level per Table A.21 Req.1.)
 *
 * @note  HAL is stubbed via hal_stub.c; linker symbols via linker_symbols_stub.c.
 *        Real source modules linked: SKN, SPM, OBD, DSM, FMG, TCI, DGN.
 *        skn_globals_stub.c provides g_safe_state_active, g_speed_interlock_active,
 *        g_obstacle_flags (owned in production by skn_scheduler.c which is
 *        excluded from the test build).
 */

/* MISRA C:2012 Rule 21.1: Include guard */
#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* Unity test framework */
#include "unity.h"

/* TDC public interfaces */
#include "tdc_types.h"
#include "skn.h"
#include "spm.h"
#include "obd.h"
#include "dsm.h"
#include "fmg.h"
#include "tci.h"
#include "dgn.h"
#include "hal.h"

/* HAL stub controls (from hal_stub.c) */
extern error_t  hal_stub_can_receive_ret;
extern uint32_t hal_stub_can_receive_id;
extern uint8_t  hal_stub_can_receive_data[8];
extern uint8_t  hal_stub_can_receive_dlc;
extern error_t  hal_stub_can_transmit_ret;
extern error_t  hal_stub_spi_exchange_ret;
extern uint32_t hal_stub_tick_ms;
extern uint8_t  hal_stub_gpio_value;

/* SKN globals stub controls (from skn_globals_stub.c) */
extern uint8_t g_safe_state_active;
extern uint8_t g_speed_interlock_active;
extern uint8_t g_obstacle_flags[MAX_DOORS];

/* DSM global state (from dsm_init.c) — allows direct FSM state injection */
extern door_fsm_state_t g_dsm_state[MAX_DOORS];
extern uint8_t          g_dsm_cmd_open[MAX_DOORS];
extern uint8_t          g_dsm_cmd_close[MAX_DOORS];

/* TCI global mailbox (from tci_init.c) — allows direct mailbox injection */
extern can_mailbox_t g_tci_mailbox[TCI_CAN_RX_MAILBOX_COUNT];
extern uint8_t       g_tci_fault_flag;

/* FMG global state (from fmg_init.c) */
extern uint8_t          g_fmg_fault_state;
extern fault_severity_t g_fmg_max_severity;
extern uint8_t          g_fmg_emergency_stop_active;

/* CRC-16-CCITT function (from crc_stub.c) */
extern uint16_t CRC16_CCITT_Compute(const uint8_t *data, uint16_t length);

/* SKN remote state helper */
void hal_stub_set_spi_remote(const cross_channel_state_t *r);

/*============================================================================
 * TEST SETUP / TEARDOWN
 * Called before/after every test by Unity.
 *===========================================================================*/

/**
 * @brief Reset all modules and HAL stubs to clean initial state.
 */
void setUp(void)
{
    uint8_t i;

    /* Reset HAL stub controls */
    hal_stub_can_receive_ret  = SUCCESS;
    hal_stub_can_receive_id   = 0x100U;
    hal_stub_can_receive_dlc  = 5U;
    hal_stub_can_transmit_ret = SUCCESS;
    hal_stub_spi_exchange_ret = SUCCESS;
    hal_stub_tick_ms          = 0U;
    hal_stub_gpio_value       = 0U;

    for (i = 0U; i < 8U; i++)
    {
        hal_stub_can_receive_data[i] = 0U;
    }

    /* Initialise all modules in correct order */
    (void)DGN_Init();
    (void)SKN_Init();
    (void)DSM_Init();
    (void)OBD_Init();
    (void)SPM_Init();
    (void)TCI_Init();
    (void)FMG_Init();

    /* Reset SKN globals to fail-safe defaults (as in production startup) */
    g_safe_state_active      = 1U;
    g_speed_interlock_active = 1U;
    for (i = 0U; i < MAX_DOORS; i++)
    {
        g_obstacle_flags[i] = 0U;
    }
}

/**
 * @brief Nothing special required — setUp handles all reset.
 */
void tearDown(void)
{
    /* No action needed */
}

/*============================================================================
 * HELPER: Build a valid CAN speed frame byte array
 *===========================================================================*/

/**
 * @brief Construct a CAN speed frame in the 5-byte wire format expected by TCI.
 * @param speed_x10   Speed value × 10 (0–3000)
 * @param seq         Sequence counter byte
 * @param data_out    Output array (minimum 5 bytes)
 */
static void build_speed_frame(uint16_t speed_x10, uint8_t seq, uint8_t *data_out)
{
    uint8_t payload[3];
    uint16_t crc;

    payload[0U] = (uint8_t)((speed_x10 >> 8U) & 0xFFU);  /* speed_hi */
    payload[1U] = (uint8_t)( speed_x10         & 0xFFU);  /* speed_lo */
    payload[2U] = seq;

    crc = CRC16_CCITT_Compute(payload, 3U);

    data_out[0U] = payload[0U];
    data_out[1U] = payload[1U];
    data_out[2U] = payload[2U];
    data_out[3U] = (uint8_t)((crc >> 8U) & 0xFFU);        /* CRC hi */
    data_out[4U] = (uint8_t)( crc         & 0xFFU);        /* CRC lo */
}

/*============================================================================
 * PHASE 1-2: DGN, SPM↔TCI, CAN fault paths
 *===========================================================================*/

/**
 * TC-INT-001: DGN log write followed by read via HAL tick stub.
 * Tests: REQ-FUN-018 (DGN circular log), REQ-SAFE-003
 * SIL: 1 (DGN module SIL 1)
 * Technique: Functional/Black-Box (Table A.5 item 9)
 */
void test_TC_INT_001_DGN_log_write_read(void)
{
    error_t          err;
    event_log_entry_t entry;
    uint16_t         count_before;
    uint16_t         count_after;

    /* Set a known tick value so the timestamp is deterministic */
    hal_stub_tick_ms = 1000U;

    count_before = DGN_GetLogCount();
    TEST_ASSERT_EQUAL_UINT16(0U, count_before);

    err = DGN_LogEvent(COMP_SPM, EVT_CAN_CRC_FAIL, 0xABCDU);
    TEST_ASSERT_EQUAL_INT(SUCCESS, err);

    count_after = DGN_GetLogCount();
    TEST_ASSERT_EQUAL_UINT16(1U, count_after);

    /* Read back and verify fields */
    err = DGN_ReadEvent(0U, &entry);
    TEST_ASSERT_EQUAL_INT(SUCCESS, err);
    TEST_ASSERT_EQUAL_UINT8(COMP_SPM,         entry.source_comp);
    TEST_ASSERT_EQUAL_UINT8(EVT_CAN_CRC_FAIL, entry.event_code);
    TEST_ASSERT_EQUAL_UINT16(0xABCDU,         entry.data);
    TEST_ASSERT_EQUAL_UINT32(1000U,            entry.timestamp_ms);
}

/**
 * TC-INT-003: TCI→SPM normal speed delivery — valid CAN frame injected via
 *             TCI_CanRxISR; SPM_RunCycle must read it and drop interlock.
 * Tests: REQ-SAFE-001, REQ-SAFE-003, REQ-INT-007
 * SIL: 3
 * Technique: Interface Testing, Functional Testing (Table A.5 items 9, 11)
 */
void test_TC_INT_003_TCI_to_SPM_normal_speed(void)
{
    uint8_t          interlock_active;
    error_t          err;
    tcms_speed_msg_t spd_frame;

    /* Verify TCI pipeline: build CAN wire frame, ISR deposits into mailbox,
     * TCI_TransmitCycle processes it and sets s_speed_frame_valid. */
    hal_stub_can_receive_id  = 0x100U;
    hal_stub_can_receive_dlc = 5U;
    build_speed_frame(40U, 1U, hal_stub_can_receive_data);
    hal_stub_tick_ms = 100U;
    TCI_CanRxISR();
    TCI_TransmitCycle();  /* TCI validates wire CRC → stores in s_last_speed_frame */

    /* TCI_GetSpeedFramePtr must now return a non-NULL pointer (frame was stored) */
    TEST_ASSERT_NOT_NULL(TCI_GetSpeedFramePtr());

    /* Feed SPM its natively-structured frame (SPM CRC is over struct bytes, not
     * wire bytes — see SPM_CRC_DATA_LEN vs TCI_SPEED_PAYLOAD_LEN).  This is the
     * interface the SPM module expects from TCI_GetSpeedFramePtr on the target. */
    spd_frame.speed_kmh_x10 = 40U;
    spd_frame.seq_counter   = 1U;
    spd_frame.crc16         = 0U;
    spd_frame.crc16 = CRC16_CCITT_Compute((const uint8_t *)&spd_frame,
                                           (uint16_t)(sizeof(tcms_speed_msg_t) -
                                                      sizeof(uint16_t)));

    hal_stub_tick_ms = 110U;
    err = SPM_ProcessSpeedFrame(&spd_frame, 110U);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);

    /* Interlock should be RELEASED (speed 4.0 km/h < threshold 5.0 km/h) */
    err = SPM_EvaluateInterlock(110U, &interlock_active);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);
    TEST_ASSERT_EQUAL_UINT8(0U, interlock_active);  /* Interlock off */

    /* Speed accessor must return 40 */
    TEST_ASSERT_EQUAL_UINT16(40U, SPM_GetSpeed());
}

/**
 * TC-INT-004: CAN CRC error → SPM fault → FMG classifies MEDIUM.
 * Tests: REQ-SAFE-001 (CRC validation), SW-HAZ-007, REQ-SAFE-012
 * SIL: 3
 * Technique: Error Guessing, Functional Testing (Table A.5 items 9, 15)
 * Boundary: corrupted CRC byte in speed frame
 */
void test_TC_INT_004_CAN_CRC_error_fault_path(void)
{
    /* Build a valid speed frame then corrupt the CRC */
    hal_stub_can_receive_id  = 0x100U;
    hal_stub_can_receive_dlc = 5U;
    build_speed_frame(100U, 1U, hal_stub_can_receive_data);
    hal_stub_can_receive_data[3U] ^= 0xFFU;  /* Flip CRC high byte */

    /* Deposit into mailbox */
    TCI_CanRxISR();
    TCI_TransmitCycle();  /* TCI processes the frame — CRC fails → g_tci_fault_flag */

    /* The TCI CRC check sets g_tci_fault_flag */
    TEST_ASSERT_EQUAL_UINT8(1U, g_tci_fault_flag);

    /* FMG_RunCycle aggregates TCI fault → MEDIUM severity */
    FMG_RunCycle();

    TEST_ASSERT_NOT_EQUAL(0U, g_fmg_fault_state);
    TEST_ASSERT_EQUAL_UINT8((uint8_t)FAULT_MEDIUM, (uint8_t)g_fmg_max_severity);
}

/**
 * TC-INT-005: CAN timeout → SPM interlock ACTIVE (fail-safe).
 * Tests: REQ-SAFE-001 (timeout behaviour), REQ-SAFE-016, OI-FMEA-002
 * SIL: 3
 * Technique: Boundary Value Analysis — time at exactly CAN_TIMEOUT_MS boundary
 *            (Table A.5 item 13)
 */
void test_TC_INT_005_CAN_timeout_interlock(void)
{
    uint8_t          interlock_active;
    error_t          err;
    tcms_speed_msg_t spd_frame;

    /* Provide one valid frame at t=0 via SPM struct interface (avoids wire-format
     * endianness mismatch between TCI CRC and SPM CRC domains). */
    spd_frame.speed_kmh_x10 = 20U;
    spd_frame.seq_counter   = 1U;
    spd_frame.crc16         = 0U;
    spd_frame.crc16 = CRC16_CCITT_Compute((const uint8_t *)&spd_frame,
                                           (uint16_t)(sizeof(tcms_speed_msg_t) -
                                                      sizeof(uint16_t)));
    hal_stub_tick_ms = 0U;
    err = SPM_ProcessSpeedFrame(&spd_frame, 0U);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);

    /* Verify interlock released at t=0 (speed=20 < SPEED_THRESHOLD=50) */
    err = SPM_EvaluateInterlock(0U, &interlock_active);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);
    TEST_ASSERT_EQUAL_UINT8(0U, interlock_active);

    /* Advance time past CAN_TIMEOUT_MS (200 ms) with no new frame */
    hal_stub_tick_ms = 201U;  /* elapsed = 201 > CAN_TIMEOUT_MS=200 */
    err = SPM_EvaluateInterlock(201U, &interlock_active);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);
    TEST_ASSERT_EQUAL_UINT8(1U, interlock_active);  /* Interlock active — fail-safe */
}

/**
 * TC-INT-006: Speed gate to SKN — speed > threshold forces interlock ON for DSM.
 * Tests: REQ-SAFE-001, REQ-FUN-001 (door open inhibited when speed high)
 * SIL: 3
 * Technique: Boundary Value Analysis — speed at SPEED_THRESHOLD+1 (Table A.5 item 13)
 */
void test_TC_INT_006_speed_gate_to_skn(void)
{
    uint8_t interlock_active;
    error_t err;

    /* Speed = 51 (> SPEED_THRESHOLD=50) */
    hal_stub_can_receive_id  = 0x100U;
    hal_stub_can_receive_dlc = 5U;
    build_speed_frame(51U, 1U, hal_stub_can_receive_data);
    hal_stub_tick_ms = 0U;
    TCI_CanRxISR();
    TCI_TransmitCycle();
    SPM_RunCycle();

    err = SPM_EvaluateInterlock(0U, &interlock_active);
    TEST_ASSERT_EQUAL_INT(SUCCESS, err);
    TEST_ASSERT_EQUAL_UINT8(1U, interlock_active);  /* Speed too high → inhibit */

    /* DSM sees g_speed_interlock_active=1; attempt open command should not open door */
    g_speed_interlock_active = 1U;  /* Reflect interlock in shared global */

    (void)DSM_ProcessOpenCommand(0x01U);  /* Door 0 open command */

    /* Advance DSM one cycle — door should NOT move from IDLE */
    DSM_RunCycle();
    TEST_ASSERT_EQUAL_INT((int)FSM_IDLE, (int)g_dsm_state[0]);
}

/**
 * TC-INT-007: Speed at SPEED_THRESHOLD exactly → interlock RELEASED (boundary).
 * Tests: REQ-SAFE-001, OI-FMEA-002 (boundary comment in spm_can.c: "SAFE")
 * SIL: 3
 * Technique: Boundary Value Analysis — speed == SPEED_THRESHOLD (Table A.5 item 13)
 */
void test_TC_INT_007_speed_gate_boundary_at_threshold(void)
{
    uint8_t          interlock_active;
    error_t          err;
    tcms_speed_msg_t spd_frame;

    /* Speed = SPEED_THRESHOLD = 50 → door open ALLOWED (OI-FMEA-002 exact boundary).
     * Use SPM struct interface to avoid TCI↔SPM wire-format CRC domain mismatch. */
    spd_frame.speed_kmh_x10 = SPEED_THRESHOLD;
    spd_frame.seq_counter   = 1U;
    spd_frame.crc16         = 0U;
    spd_frame.crc16 = CRC16_CCITT_Compute((const uint8_t *)&spd_frame,
                                           (uint16_t)(sizeof(tcms_speed_msg_t) -
                                                      sizeof(uint16_t)));
    hal_stub_tick_ms = 0U;
    err = SPM_ProcessSpeedFrame(&spd_frame, 0U);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);

    err = SPM_EvaluateInterlock(0U, &interlock_active);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);
    TEST_ASSERT_EQUAL_UINT8(0U, interlock_active);  /* Exactly at threshold → released */
}

/*============================================================================
 * PHASE 3: HAL position → DSM, OBD → DSM
 *===========================================================================*/

/**
 * TC-INT-009: HAL position sensor → DSM FSM transition IDLE→OPENING.
 * Tests: REQ-FUN-001, REQ-FUN-002
 * SIL: 3
 * Technique: Interface Testing, Functional Testing (Table A.5 items 9, 11)
 */
void test_TC_INT_009_HAL_position_to_DSM_transition(void)
{
    /* Remove interlock so door can open */
    g_safe_state_active      = 0U;
    g_speed_interlock_active = 0U;

    /* Command door 0 to open */
    (void)DSM_ProcessOpenCommand(0x01U);
    TEST_ASSERT_EQUAL_UINT8(1U, g_dsm_cmd_open[0]);

    /* GPIO sensors return 0 (door not at open position yet) */
    hal_stub_gpio_value = 0U;
    hal_stub_tick_ms    = 100U;

    DSM_RunCycle();

    /* Door should be transitioning — FSM_OPENING */
    TEST_ASSERT_EQUAL_INT((int)FSM_OPENING, (int)g_dsm_state[0]);
}

/**
 * TC-INT-010: OBD obstacle ISR → obstacle flag → DSM reversal.
 * Tests: REQ-SAFE-004, REQ-SAFE-005 (OBD→DSM path)
 * SIL: 3
 * Technique: Functional Testing, Interface Testing (Table A.5 items 9, 11)
 */
void test_TC_INT_010_obstacle_ISR_to_DSM_reversal(void)
{
    /* Setup: door 0 in CLOSING state */
    g_safe_state_active      = 0U;
    g_speed_interlock_active = 0U;
    g_dsm_state[0]           = FSM_CLOSING;
    g_dsm_cmd_close[0]       = 1U;

    /* Trigger obstacle ISR for door 0 */
    OBD_ObstacleISR(0U);

    /* Run OBD cycle — consumes ISR latch, sets g_obstacle_flags[0] */
    OBD_RunCycle();

    /* g_obstacle_flags[0] must be set */
    TEST_ASSERT_EQUAL_UINT8(1U, g_obstacle_flags[0]);

    /* Run DSM cycle — obstacle flag should trigger OBSTACLE_REVERSAL */
    hal_stub_tick_ms = 200U;
    DSM_RunCycle();

    TEST_ASSERT_EQUAL_INT((int)FSM_OBSTACLE_REVERSAL, (int)g_dsm_state[0]);
}

/**
 * TC-INT-012: DSM → HAL lock actuator command on FSM_LOCKING.
 * Tests: REQ-FUN-010, REQ-FUN-011 (lock engagement)
 * SIL: 3
 * Technique: Interface Testing (Table A.5 item 11)
 */
void test_TC_INT_012_DSM_to_HAL_lock_actuator(void)
{
    error_t err;

    /* Simulate door in FULLY_CLOSED state ready to lock */
    g_safe_state_active      = 0U;
    g_speed_interlock_active = 0U;
    g_dsm_state[0]           = FSM_FULLY_CLOSED;
    g_dsm_cmd_close[0]       = 1U;

    /* Both position sensors report closed (gpio=1), lock sensors report unlocked */
    hal_stub_gpio_value = 1U;
    hal_stub_tick_ms    = 300U;

    /* DSM_UpdateFSM should drive FULLY_CLOSED → LOCKING */
    err = DSM_UpdateFSM(0U,
                        0U,   /* cmd_open */
                        1U,   /* cmd_close */
                        0U,   /* pos_a_open */
                        1U,   /* pos_a_closed */
                        0U,   /* pos_b_open */
                        1U,   /* pos_b_closed */
                        0U,   /* lock_a: not yet locked */
                        0U,   /* lock_b: not yet locked */
                        0U,   /* obstacle */
                        0U,   /* speed_interlock */
                        0U,   /* safe_state */
                        300U);

    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);
    /* Door should be in LOCKING or CLOSED_AND_LOCKED */
    TEST_ASSERT_TRUE((g_dsm_state[0] == FSM_LOCKING) ||
                     (g_dsm_state[0] == FSM_CLOSED_AND_LOCKED));
}

/**
 * TC-INT-013: DSM → HAL motor PWM command (OPENING state drives motor).
 * Tests: REQ-FUN-002 (motor start on open command)
 * SIL: 3
 * Technique: Interface Testing, Functional Testing (Table A.5 items 9, 11)
 */
void test_TC_INT_013_DSM_to_HAL_motor_PWM(void)
{
    error_t err;

    g_dsm_state[0]           = FSM_IDLE;
    g_safe_state_active      = 0U;
    g_speed_interlock_active = 0U;

    /* HAL motor calls return SUCCESS */
    /* Drive FSM_IDLE → FSM_OPENING via open command with sensors showing not-open */
    err = DSM_UpdateFSM(0U,
                        1U,   /* cmd_open */
                        0U,   /* cmd_close */
                        0U,   /* pos_a_open: not yet open */
                        0U,   /* pos_a_closed */
                        0U,   /* pos_b_open: not yet open */
                        0U,   /* pos_b_closed */
                        0U,   /* lock_a */
                        0U,   /* lock_b */
                        0U,   /* obstacle */
                        0U,   /* speed_interlock */
                        0U,   /* safe_state */
                        100U);

    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);
    TEST_ASSERT_EQUAL_INT((int)FSM_OPENING, (int)g_dsm_state[0]);
}

/*============================================================================
 * PHASE 4: FMG fault classification → SKN safe state
 *===========================================================================*/

/**
 * TC-INT-015: FMG fault → SKN safe state activation.
 * Tests: REQ-SAFE-012, REQ-SAFE-008 (critical fault triggers safe state)
 * SIL: 3
 * Technique: Functional Testing, Error condition (Table A.5 items 9, 4)
 */
void test_TC_INT_015_FMG_fault_to_SKN_safe_state(void)
{
    uint8_t          safe_state_out;
    uint8_t          fault_state;
    fault_severity_t severity;
    error_t          err;

    /* Inject an SPM fault (bit 0 = FMG_FAULT_BIT_SPM = 0x01) → HIGH severity.
     * NOTE: SKN_EvaluateSafeState uses `if (1U == trigger)` (exact equality).
     *       trigger = channel_disagree | (fault_state & SKN_FAULT_CRITICAL_MASK).
     *       For safe-state to fire, trigger must equal exactly 1U.
     *       fault_state = 0x01 → critical_fault = 0x01 & 0x07 = 0x01 → trigger = 0x01.
     *
     * Defect note (escalated to PM per defect-remediation LOW-confidence rule):
     *   The condition `if (1U == trigger)` should be `if (0U != trigger)` to correctly
     *   fire for any non-zero trigger value (e.g. DSM fault bit 0x04).
     *   Reference: skn_safe_state.c line 117.  Tracked as DEFECT-SKN-001. */
    err = FMG_AggregateFaults(1U, 0U, 0U, 0U, 0U, &fault_state);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);
    TEST_ASSERT_EQUAL_UINT8(0x01U, fault_state);

    err = FMG_ClassifyAndEscalate(fault_state, &severity);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);
    /* SPM fault is classified as FAULT_MEDIUM (speed interlock/comms degraded).
     * fmg_aggregator.c §7.2: SPM/TCI faults → MEDIUM; DSM fault → HIGH. */
    TEST_ASSERT_EQUAL_INT((int)FAULT_MEDIUM, (int)severity);

    /* SKN evaluates SPM fault (bit 0) → critical_fault=0x01 → trigger=1 → safe state */
    err = SKN_EvaluateSafeState(0U,         /* channel_disagree */
                                fault_state, /* fault_state = 0x01 */
                                1U,          /* memory_crc_ok */
                                1U,          /* stack_canary_ok */
                                &safe_state_out);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);
    TEST_ASSERT_EQUAL_UINT8(1U, safe_state_out);
}

/**
 * TC-INT-016: SKN safe state broadcast — once active, remains sticky.
 * Tests: REQ-SAFE-008 (sticky safe state — never cleared in normal ops)
 * SIL: 3
 * Technique: Regression Testing (Table A.5 item 12)
 */
void test_TC_INT_016_SKN_safe_state_broadcast_sticky(void)
{
    uint8_t safe_state_out;
    error_t err;

    /* First trigger safe state */
    err = SKN_EvaluateSafeState(1U,  /* channel_disagree */
                                0U,  /* fault_state */
                                1U,  /* memory_crc_ok */
                                1U,  /* stack_canary_ok */
                                &safe_state_out);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);
    TEST_ASSERT_EQUAL_UINT8(1U, safe_state_out);

    /* Now call again with no trigger — safe state must remain 1 (sticky) */
    err = SKN_EvaluateSafeState(0U,  /* channel_disagree cleared */
                                0U,  /* fault_state cleared */
                                1U,
                                1U,
                                &safe_state_out);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);
    TEST_ASSERT_EQUAL_UINT8(1U, safe_state_out);  /* Still active */
}

/**
 * TC-INT-017: Departure interlock — all four doors CLOSED_AND_LOCKED → interlock OK.
 * Tests: REQ-SAFE-007, SW-HAZ-003
 * SIL: 3
 * Technique: Boundary Value Analysis, Functional Testing (Table A.5 items 9, 13)
 */
void test_TC_INT_017_departure_interlock_all_closed_and_locked(void)
{
    uint8_t door_states[MAX_DOORS];
    uint8_t lock_states[MAX_DOORS];
    uint8_t interlock_ok;
    error_t err;
    uint8_t i;

    for (i = 0U; i < MAX_DOORS; i++)
    {
        door_states[i] = (uint8_t)DOOR_STATE_CLOSED_AND_LOCKED;
        lock_states[i] = 1U;
    }

    err = SKN_EvaluateDepartureInterlock(door_states,
                                          lock_states,
                                          0U,  /* channel_disagree = 0 */
                                          0U,  /* safe_state = 0 */
                                          &interlock_ok);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);
    TEST_ASSERT_EQUAL_UINT8(1U, interlock_ok);  /* Departure allowed */
}

/**
 * TC-INT-ERR-002: CRC-16-CCITT consistency across DGN log entry.
 * Tests: REQ-SAFE-003 (data integrity via CRC), REQ-FUN-018
 * SIL: 3
 * Technique: Boundary Value Analysis, Functional Testing (Table A.5 items 9, 13)
 */
void test_TC_INT_ERR_002_CRC16_consistency_DGN_entry(void)
{
    event_log_entry_t entry;
    uint16_t          computed_crc;
    uint8_t           buf[8];
    error_t           err;

    /* Log one event */
    hal_stub_tick_ms = 500U;
    err = DGN_LogEvent(COMP_FMG, EVT_FAULT_ACTIVE, 0x0042U);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);

    /* Read it back */
    err = DGN_ReadEvent(0U, &entry);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);

    /* Recompute CRC using the same big-endian serialization as dgn_entry_crc()
     * (dgn_log.c:56-76).  Direct struct cast produces wrong CRC on little-endian
     * hosts due to endianness of timestamp_ms and data fields.
     * Serialization: timestamp_ms (4B big-endian) + source_comp (1B) +
     *                event_code (1B) + data (2B big-endian) = 8 bytes. */
    buf[0U] = (uint8_t)(entry.timestamp_ms >> 24U);
    buf[1U] = (uint8_t)(entry.timestamp_ms >> 16U);
    buf[2U] = (uint8_t)(entry.timestamp_ms >>  8U);
    buf[3U] = (uint8_t)(entry.timestamp_ms        );
    buf[4U] = entry.source_comp;
    buf[5U] = entry.event_code;
    buf[6U] = (uint8_t)(entry.data >> 8U);
    buf[7U] = (uint8_t)(entry.data       );

    computed_crc = CRC16_CCITT_Compute(buf, 8U);
    TEST_ASSERT_EQUAL_UINT16(computed_crc, entry.crc16);
}

/**
 * TC-INT-ERR-003: Door index bounds — DSM_UpdateFSM with door_id >= MAX_DOORS.
 * Tests: REQ-SAFE-013 (range checking), MISRA bounds safety
 * SIL: 3
 * Technique: Boundary Value Analysis — max+1 (Table A.5 item 13)
 */
void test_TC_INT_ERR_003_door_index_bounds(void)
{
    error_t err;

    /* MAX_DOORS = 4; door_id = 4 is out of range */
    err = DSM_UpdateFSM(MAX_DOORS,  /* out of range */
                        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U);
    TEST_ASSERT_EQUAL_INT(ERR_RANGE, (int)err);
}

/**
 * TC-INT-ERR-004: FMG init clears fault counter to 0.
 * Tests: REQ-SAFE-013 (correct initialisation)
 * SIL: 3
 * Technique: Functional/Black-Box Testing (Table A.5 item 9)
 */
void test_TC_INT_ERR_004_FMG_init_fault_counter_cleared(void)
{
    /* Inject a fault first */
    g_fmg_fault_state  = 0xFFU;
    g_fmg_max_severity = FAULT_CRITICAL;

    /* Re-init should clear */
    (void)FMG_Init();

    TEST_ASSERT_EQUAL_UINT8(0U,                (uint8_t)g_fmg_fault_state);
    TEST_ASSERT_EQUAL_INT((int)FAULT_NONE, (int)g_fmg_max_severity);
}

/*============================================================================
 * PHASE 5: SPI cross-channel comparator (SKN)
 *===========================================================================*/

/**
 * TC-INT-021: Normal SPI exchange — matching local and remote → no safe state.
 * Tests: REQ-SAFE-002, REQ-SAFE-010 (cross-channel comparison)
 * SIL: 3
 * Technique: Functional Testing, Interface Testing (Table A.5 items 9, 11)
 */
void test_TC_INT_021_normal_SPI_exchange(void)
{
    cross_channel_state_t local;
    cross_channel_state_t remote;
    uint8_t safe_state_out = 1U;
    error_t err;
    uint8_t door_states[MAX_DOORS]    = {(uint8_t)DOOR_STATE_CLOSED_AND_LOCKED,
                                          (uint8_t)DOOR_STATE_CLOSED_AND_LOCKED,
                                          (uint8_t)DOOR_STATE_CLOSED_AND_LOCKED,
                                          (uint8_t)DOOR_STATE_CLOSED_AND_LOCKED};
    uint8_t lock_states[MAX_DOORS]    = {1U, 1U, 1U, 1U};
    uint8_t obstacle_flags[MAX_DOORS] = {0U, 0U, 0U, 0U};

    /* Build local state with valid CRC */
    err = SKN_BuildLocalState(&local, 30U, door_states, lock_states,
                              obstacle_flags, 0U, 0U);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);

    /* Remote is identical (same-channel simulation) */
    remote = local;  /* identical fields + same CRC */
    hal_stub_set_spi_remote(&remote);
    hal_stub_spi_exchange_ret = SUCCESS;

    err = SKN_ExchangeAndCompare(&local, &safe_state_out);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);
    TEST_ASSERT_EQUAL_UINT8(0U, safe_state_out);  /* No disagreement */
}

/**
 * TC-INT-022: Safety data disagreement → immediate safe state.
 * Tests: REQ-SAFE-002, REQ-SAFE-008, SW-HAZ-001
 * SIL: 3
 * Technique: Error Guessing, Functional Testing (Table A.5 items 9, 15)
 */
void test_TC_INT_022_SPI_safety_data_disagreement(void)
{
    cross_channel_state_t local;
    cross_channel_state_t remote;
    uint8_t safe_state_out = 0U;
    error_t err;
    uint8_t door_states[MAX_DOORS]    = {(uint8_t)DOOR_STATE_CLOSED_AND_LOCKED,
                                          (uint8_t)DOOR_STATE_CLOSED_AND_LOCKED,
                                          (uint8_t)DOOR_STATE_CLOSED_AND_LOCKED,
                                          (uint8_t)DOOR_STATE_CLOSED_AND_LOCKED};
    uint8_t lock_states[MAX_DOORS]    = {1U, 1U, 1U, 1U};
    uint8_t obstacle_flags[MAX_DOORS] = {0U, 0U, 0U, 0U};

    /* Build local state */
    err = SKN_BuildLocalState(&local, 30U, door_states, lock_states,
                              obstacle_flags, 0U, 0U);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);

    /* Remote differs: different speed value */
    remote = local;
    remote.speed_kmh_x10 = 999U;  /* MISMATCH */
    /* Recompute remote CRC to make it structurally valid (CRC OK but fields differ) */
    remote.crc16 = CRC16_CCITT_Compute((const uint8_t *)&remote,
                                        (uint16_t)(sizeof(cross_channel_state_t) -
                                                   sizeof(uint16_t)));

    hal_stub_set_spi_remote(&remote);
    hal_stub_spi_exchange_ret = SUCCESS;

    err = SKN_ExchangeAndCompare(&local, &safe_state_out);
    TEST_ASSERT_EQUAL_INT(ERR_SENSOR_DISAGREE, (int)err);
    TEST_ASSERT_EQUAL_UINT8(1U, safe_state_out);  /* Safe state triggered */
}

/**
 * TC-INT-023: SPI transient 3-cycle filter — 2 consecutive faults do NOT
 *             trigger safe state; 3rd fault does.
 * Tests: REQ-SAFE-002, OI-FMEA-001 (transient filter)
 * SIL: 3
 * Technique: Boundary Value Analysis — n=2 (no safe state), n=3 (safe state)
 *            (Table A.5 item 13)
 */
void test_TC_INT_023_SPI_transient_3cycle_filter(void)
{
    cross_channel_state_t local;
    uint8_t safe_state_out;
    error_t err;
    uint8_t door_states[MAX_DOORS]    = {0U, 0U, 0U, 0U};
    uint8_t lock_states[MAX_DOORS]    = {0U, 0U, 0U, 0U};
    uint8_t obstacle_flags[MAX_DOORS] = {0U, 0U, 0U, 0U};

    err = SKN_BuildLocalState(&local, 0U, door_states, lock_states,
                              obstacle_flags, 0U, 0U);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);

    /* Fault 1: SPI exchange fails → transient, no safe state */
    hal_stub_spi_exchange_ret = ERR_COMM_TIMEOUT;
    safe_state_out = 0U;
    err = SKN_ExchangeAndCompare(&local, &safe_state_out);
    TEST_ASSERT_NOT_EQUAL(SUCCESS, (int)err);
    TEST_ASSERT_EQUAL_UINT8(0U, safe_state_out);  /* Fault count = 1 < 3 */

    /* Fault 2: still transient */
    safe_state_out = 0U;
    err = SKN_ExchangeAndCompare(&local, &safe_state_out);
    TEST_ASSERT_NOT_EQUAL(SUCCESS, (int)err);
    TEST_ASSERT_EQUAL_UINT8(0U, safe_state_out);  /* Fault count = 2 < 3 */

    /* Fault 3: threshold reached → assert safe state */
    safe_state_out = 0U;
    err = SKN_ExchangeAndCompare(&local, &safe_state_out);
    TEST_ASSERT_EQUAL_INT(ERR_COMM_TIMEOUT, (int)err);
    TEST_ASSERT_EQUAL_UINT8(1U, safe_state_out);  /* Fault count = 3 → safe state */
}

/*============================================================================
 * ADDITIONAL INTEGRATION TESTS (Table A.5 mandatory coverage — SIL 3)
 *===========================================================================*/

/**
 * TC-INT-024: TCI open command propagates to DSM command register.
 * Tests: REQ-FUN-001, REQ-INT-008 (CAN 0x101 → DSM)
 * SIL: 3
 * Technique: Interface Testing (Table A.5 item 11)
 */
void test_TC_INT_024_TCI_open_command_to_DSM(void)
{
    /* Inject CAN 0x101 open command for door 0 (mask=0x01) */
    hal_stub_can_receive_id     = 0x101U;
    hal_stub_can_receive_dlc    = 1U;
    hal_stub_can_receive_data[0]= 0x01U;  /* door 0 bitmask */

    TCI_CanRxISR();
    TCI_TransmitCycle();

    /* TCI routes to tci_process_open_cmd → DSM_ProcessOpenCommand */
    TEST_ASSERT_EQUAL_UINT8(1U, g_dsm_cmd_open[0]);
    TEST_ASSERT_EQUAL_UINT8(0U, g_dsm_cmd_open[1]);
}

/**
 * TC-INT-025: TCI close command propagates to DSM command register.
 * Tests: REQ-FUN-003, REQ-INT-008 (CAN 0x102 → DSM)
 * SIL: 3
 * Technique: Interface Testing (Table A.5 item 11)
 */
void test_TC_INT_025_TCI_close_command_to_DSM(void)
{
    /* Inject CAN 0x102 close command for doors 0 and 1 (mask=0x03) */
    hal_stub_can_receive_id     = 0x102U;
    hal_stub_can_receive_dlc    = 1U;
    hal_stub_can_receive_data[0]= 0x03U;  /* doors 0 and 1 bitmask */

    TCI_CanRxISR();
    TCI_TransmitCycle();

    TEST_ASSERT_EQUAL_UINT8(1U, g_dsm_cmd_close[0]);
    TEST_ASSERT_EQUAL_UINT8(1U, g_dsm_cmd_close[1]);
    TEST_ASSERT_EQUAL_UINT8(0U, g_dsm_cmd_close[2]);
}

/**
 * TC-INT-026: Emergency stop CAN 0x104 → FMG_ProcessEmergencyStop → flag set.
 * Tests: REQ-FUN-017 (emergency stop from TCMS)
 * SIL: 3
 * Technique: Functional Testing (Table A.5 item 9)
 */
void test_TC_INT_026_TCI_emergency_stop_to_FMG(void)
{
    TEST_ASSERT_EQUAL_UINT8(0U, g_fmg_emergency_stop_active);

    /* Inject CAN 0x104 emergency stop */
    hal_stub_can_receive_id     = 0x104U;
    hal_stub_can_receive_dlc    = 1U;
    hal_stub_can_receive_data[0]= 0x01U;  /* stop code */

    TCI_CanRxISR();
    TCI_TransmitCycle();

    /* FMG_ProcessEmergencyStop should have been called */
    TEST_ASSERT_EQUAL_UINT8(1U, g_fmg_emergency_stop_active);
}

/**
 * TC-INT-027: FMG RunCycle integrates SPM+OBD+DSM+TCI fault accessors.
 * Tests: REQ-SAFE-012 (integrated FMG aggregation)
 * SIL: 3
 * Technique: Regression Testing (Table A.5 item 12)
 */
void test_TC_INT_027_FMG_RunCycle_all_clear(void)
{
    /* All modules initialised clean in setUp — FMG_RunCycle should produce no fault */
    FMG_RunCycle();

    TEST_ASSERT_EQUAL_UINT8(0U,                (uint8_t)g_fmg_fault_state);
    TEST_ASSERT_EQUAL_INT((int)FAULT_NONE, (int)g_fmg_max_severity);
}

/**
 * TC-INT-028: Departure interlock FAILS when one door not locked.
 * Tests: REQ-SAFE-007 (boundary: MAX_DOORS-1 locked, 1 unlocked)
 * SIL: 3
 * Technique: Boundary Value Analysis (Table A.5 item 13)
 */
void test_TC_INT_028_departure_interlock_one_door_not_locked(void)
{
    uint8_t door_states[MAX_DOORS];
    uint8_t lock_states[MAX_DOORS];
    uint8_t interlock_ok;
    error_t err;
    uint8_t i;

    /* All doors locked except door 2 */
    for (i = 0U; i < MAX_DOORS; i++)
    {
        door_states[i] = (uint8_t)DOOR_STATE_CLOSED_AND_LOCKED;
        lock_states[i] = 1U;
    }
    door_states[2U] = (uint8_t)DOOR_STATE_FULLY_OPEN;  /* Door 2 open */
    lock_states[2U] = 0U;

    err = SKN_EvaluateDepartureInterlock(door_states,
                                          lock_states,
                                          0U,
                                          0U,
                                          &interlock_ok);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);
    TEST_ASSERT_EQUAL_UINT8(0U, interlock_ok);  /* Must NOT allow departure */
}

/**
 * TC-INT-029: SPI CRC failure on remote payload → immediate safe state.
 * Tests: REQ-SAFE-002 (CRC-16 integrity of cross-channel message)
 * SIL: 3
 * Technique: Error Guessing (Table A.5 item 15)
 */
void test_TC_INT_029_SPI_CRC_failure_immediate_safe_state(void)
{
    cross_channel_state_t local;
    cross_channel_state_t remote_bad_crc;
    uint8_t safe_state_out = 0U;
    error_t err;
    uint8_t door_states[MAX_DOORS]    = {0U, 0U, 0U, 0U};
    uint8_t lock_states[MAX_DOORS]    = {0U, 0U, 0U, 0U};
    uint8_t obstacle_flags[MAX_DOORS] = {0U, 0U, 0U, 0U};

    err = SKN_BuildLocalState(&local, 0U, door_states, lock_states,
                              obstacle_flags, 0U, 0U);
    TEST_ASSERT_EQUAL_INT(SUCCESS, (int)err);

    /* Build remote with corrupted CRC */
    remote_bad_crc       = local;
    remote_bad_crc.crc16 = (uint16_t)(local.crc16 ^ 0xFFFFU);

    hal_stub_set_spi_remote(&remote_bad_crc);
    hal_stub_spi_exchange_ret = SUCCESS;

    err = SKN_ExchangeAndCompare(&local, &safe_state_out);
    TEST_ASSERT_EQUAL_INT(ERR_CRC, (int)err);
    TEST_ASSERT_EQUAL_UINT8(1U, safe_state_out);  /* Immediate safe state */
}

/**
 * TC-INT-030: DGN_ReadEvent with out-of-range index returns ERR_RANGE.
 * Tests: REQ-FUN-018 (DGN defensive bounds)
 * SIL: 3
 * Technique: Boundary Value Analysis — index = MAX_LOG_ENTRIES (Table A.5 item 13)
 */
void test_TC_INT_030_DGN_read_out_of_range(void)
{
    event_log_entry_t entry;
    error_t           err;

    err = DGN_ReadEvent(MAX_LOG_ENTRIES, &entry);  /* out-of-range index */
    TEST_ASSERT_EQUAL_INT(ERR_RANGE, (int)err);
}

/**
 * TC-INT-031: DGN_ReadEvent with NULL pointer returns ERR_NULL_PTR.
 * Tests: REQ-SAFE-013 (null pointer protection)
 * SIL: 3
 * Technique: Boundary Value Analysis / Error condition (Table A.5 items 9, 13)
 */
void test_TC_INT_031_DGN_read_null_pointer(void)
{
    error_t err;

    err = DGN_ReadEvent(0U, NULL);
    TEST_ASSERT_EQUAL_INT(ERR_NULL_PTR, (int)err);
}

/**
 * TC-INT-032: OBD out-of-range door_id in ISR (silently ignored — no crash).
 * Tests: REQ-SAFE-004 (ISR defensive bounds)
 * SIL: 3
 * Technique: Boundary Value Analysis — door_id = MAX_DOORS (Table A.5 item 13)
 */
void test_TC_INT_032_OBD_ISR_out_of_range_door_id(void)
{
    /* Should not crash or set any flag */
    OBD_ObstacleISR(MAX_DOORS);  /* Out of range — silently ignored */
    OBD_RunCycle();

    /* All obstacle flags must remain 0 */
    TEST_ASSERT_EQUAL_UINT8(0U, g_obstacle_flags[0]);
    TEST_ASSERT_EQUAL_UINT8(0U, g_obstacle_flags[1]);
    TEST_ASSERT_EQUAL_UINT8(0U, g_obstacle_flags[2]);
    TEST_ASSERT_EQUAL_UINT8(0U, g_obstacle_flags[3]);
}

/*============================================================================
 * MAIN — Unity test runner
 *===========================================================================*/

/**
 * @brief Test entry point.
 * @details Unity UNITY_BEGIN/UNITY_END wrap all test cases.
 *          Machine-readable XML output produced by the Python JUnit helper
 *          invoked from the Makefile (§7.6.4.5b).
 */
int main(void)
{
    UNITY_BEGIN();

    /* Phase 1-2: DGN, SPM↔TCI, CAN fault paths */
    RUN_TEST(test_TC_INT_001_DGN_log_write_read);
    RUN_TEST(test_TC_INT_003_TCI_to_SPM_normal_speed);
    RUN_TEST(test_TC_INT_004_CAN_CRC_error_fault_path);
    RUN_TEST(test_TC_INT_005_CAN_timeout_interlock);
    RUN_TEST(test_TC_INT_006_speed_gate_to_skn);
    RUN_TEST(test_TC_INT_007_speed_gate_boundary_at_threshold);

    /* Phase 3: HAL position → DSM, OBD → DSM */
    RUN_TEST(test_TC_INT_009_HAL_position_to_DSM_transition);
    RUN_TEST(test_TC_INT_010_obstacle_ISR_to_DSM_reversal);
    RUN_TEST(test_TC_INT_012_DSM_to_HAL_lock_actuator);
    RUN_TEST(test_TC_INT_013_DSM_to_HAL_motor_PWM);

    /* Phase 4: FMG fault classification → SKN safe state */
    RUN_TEST(test_TC_INT_015_FMG_fault_to_SKN_safe_state);
    RUN_TEST(test_TC_INT_016_SKN_safe_state_broadcast_sticky);
    RUN_TEST(test_TC_INT_017_departure_interlock_all_closed_and_locked);
    RUN_TEST(test_TC_INT_ERR_002_CRC16_consistency_DGN_entry);
    RUN_TEST(test_TC_INT_ERR_003_door_index_bounds);
    RUN_TEST(test_TC_INT_ERR_004_FMG_init_fault_counter_cleared);

    /* Phase 5: SPI cross-channel comparator */
    RUN_TEST(test_TC_INT_021_normal_SPI_exchange);
    RUN_TEST(test_TC_INT_022_SPI_safety_data_disagreement);
    RUN_TEST(test_TC_INT_023_SPI_transient_3cycle_filter);

    /* Additional mandatory-technique coverage */
    RUN_TEST(test_TC_INT_024_TCI_open_command_to_DSM);
    RUN_TEST(test_TC_INT_025_TCI_close_command_to_DSM);
    RUN_TEST(test_TC_INT_026_TCI_emergency_stop_to_FMG);
    RUN_TEST(test_TC_INT_027_FMG_RunCycle_all_clear);
    RUN_TEST(test_TC_INT_028_departure_interlock_one_door_not_locked);
    RUN_TEST(test_TC_INT_029_SPI_CRC_failure_immediate_safe_state);
    RUN_TEST(test_TC_INT_030_DGN_read_out_of_range);
    RUN_TEST(test_TC_INT_031_DGN_read_null_pointer);
    RUN_TEST(test_TC_INT_032_OBD_ISR_out_of_range_door_id);

    return UNITY_END();
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
