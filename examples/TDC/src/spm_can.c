/**
 * @file    spm_can.c
 * @brief   SPM CAN receive, validation, interlock evaluation, and cycle entry.
 * @details Implements UNIT-SPM-001 (ProcessSpeedFrame), UNIT-SPM-002
 *          (EvaluateInterlock), UNIT-SPM-003 (Init), UNIT-SPM-004 (RunCycle),
 *          UNIT-SPM-005 (GetSpeed), and SPM_GetFault accessor.
 *          Also provides TCI_GetSpeedFramePtr for TCI mailbox polling.
 *
 * @project TDC (Train Door Control System)
 * @module  SPM (Speed Monitor) — COMP-002
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety  SIL Level: 3
 * Safety Requirements: REQ-SAFE-001/002/003/016, REQ-PERF-002, SW-HAZ-001/007
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §4
 */

/* Implements: REQ-SAFE-001/002/003/016, SW-HAZ-001/007 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §4 (COMP-002) */

#include <stdint.h>
#include <stddef.h>

#include "spm.h"
#include "tci.h"
#include "skn.h"
#include "hal.h"
#include "dgn.h"
#include "tdc_types.h"

/*============================================================================
 * PREPROCESSOR DEFINITIONS
 *===========================================================================*/
/** @brief Maximum valid speed value (300.0 km/h × 10) */
#define SPM_MAX_SPEED_VALUE  (3000U)

/** @brief Unknown speed sentinel value */
#define SPM_SPEED_UNKNOWN    (0xFFFFU)

/** @brief CRC input length: all bytes of tcms_speed_msg_t except trailing crc16 */
#define SPM_CRC_DATA_LEN \
    ((uint16_t)(sizeof(tcms_speed_msg_t) - sizeof(uint16_t)))

/*============================================================================
 * STATIC VARIABLES
 *===========================================================================*/
/** @brief Latest validated speed message */
static tcms_speed_msg_t s_latest_speed_msg;

/** @brief Timestamp of last valid CAN Rx (ms) */
static uint32_t s_last_valid_rx_ms;

/** @brief Last received sequence counter value */
static uint8_t s_last_seq_counter;

/** @brief Current validated speed (km/h × 10); 0xFFFF if unknown */
static uint16_t s_current_speed_kmh_x10;

/** @brief Speed interlock active flag (1=door open inhibited) */
static uint8_t s_speed_interlock_active;

/** @brief SPM fault flag for FMG aggregation */
static uint8_t s_spm_fault_flag;

/*============================================================================
 * PUBLIC FUNCTION IMPLEMENTATIONS
 *===========================================================================*/

/**
 * @brief Initialise SPM to fail-safe defaults.
 * @complexity Cyclomatic complexity: 1 — within SIL 3 limit of 10
 */
error_t SPM_Init(void)
{
    /* Implements: UNIT-SPM-003 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §4.3.1 */

    /* Zero out speed message structure field-by-field */
    s_latest_speed_msg.speed_kmh_x10 = 0U;
    s_latest_speed_msg.seq_counter   = 0U;
    s_latest_speed_msg.crc16         = 0U;

    s_last_valid_rx_ms       = 0U;
    s_last_seq_counter       = 0U;
    s_current_speed_kmh_x10  = SPM_SPEED_UNKNOWN;  /* UNKNOWN — fail-safe */
    s_speed_interlock_active = 1U;                  /* Inhibit at startup */
    s_spm_fault_flag         = 0U;

    return SUCCESS;
}

/**
 * @brief Process a received CAN speed frame (CRC-16, sequence, range validation).
 * @complexity Cyclomatic complexity: 6 — within SIL 3 limit of 10
 */
error_t SPM_ProcessSpeedFrame(const tcms_speed_msg_t *msg,
                              uint32_t timestamp_ms)
{
    /* Implements: REQ-SAFE-001/003, UNIT-SPM-001 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §4.1.1 */
    error_t  result;
    uint16_t computed_crc;
    uint8_t  expected_seq;

    if (NULL == msg)
    {
        result = ERR_NULL_PTR;
    }
    else
    {
        /* CRC-16-CCITT validation (OI-FTA-003) */
        computed_crc = CRC16_CCITT_Compute((const uint8_t *)msg, SPM_CRC_DATA_LEN);

        if (computed_crc != msg->crc16)
        {
            LOG_EVENT(DGN, COMP_SPM, EVT_CAN_CRC_FAIL, 0U);
            s_spm_fault_flag = 1U;
            result = ERR_CRC;
        }
        else
        {
            /* Sequence counter check (modulo-256) — non-fatal, log only */
            expected_seq = (uint8_t)((s_last_seq_counter + 1U) & 0xFFU);

            if (msg->seq_counter != expected_seq)
            {
                LOG_EVENT(DGN, COMP_SPM, EVT_CAN_SEQ_SKIP,
                          (uint16_t)msg->seq_counter);
            }

            /* Range check: 0–3000 (0–300.0 km/h × 10) */
            if (msg->speed_kmh_x10 > SPM_MAX_SPEED_VALUE)
            {
                LOG_EVENT(DGN, COMP_SPM, EVT_SPEED_RANGE_ERR,
                          msg->speed_kmh_x10);
                s_spm_fault_flag = 1U;
                result = ERR_RANGE;
            }
            else
            {
                /* Valid frame — update state */
                s_latest_speed_msg       = *msg;
                s_last_valid_rx_ms       = timestamp_ms;
                s_last_seq_counter       = msg->seq_counter;
                s_current_speed_kmh_x10  = msg->speed_kmh_x10;
                s_spm_fault_flag         = 0U;
                result = SUCCESS;
            }
        }
    }

    return result;
}

/**
 * @brief Evaluate speed interlock based on speed value and data freshness.
 * @complexity Cyclomatic complexity: 5 — within SIL 3 limit of 10
 */
error_t SPM_EvaluateInterlock(uint32_t current_time_ms,
                              uint8_t *interlock_active_out)
{
    /* Implements: REQ-SAFE-001/016, OI-FMEA-002, UNIT-SPM-002 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §4.2.1 */
    error_t  result;
    uint32_t elapsed_ms;

    if (NULL == interlock_active_out)
    {
        result = ERR_NULL_PTR;
    }
    else
    {
        /* Timeout check — if data stale, assume moving */
        elapsed_ms = current_time_ms - s_last_valid_rx_ms;

        if (elapsed_ms > CAN_TIMEOUT_MS)
        {
            s_speed_interlock_active = 1U;
            *interlock_active_out = 1U;
            result = SUCCESS;
        }
        else if (SPM_SPEED_UNKNOWN == s_current_speed_kmh_x10)
        {
            /* Speed unknown → fail-safe: inhibit door open */
            s_speed_interlock_active = 1U;
            *interlock_active_out = 1U;
            result = SUCCESS;
        }
        else
        {
            /* OI-FMEA-002: exact boundary (speed == SPEED_THRESHOLD) is SAFE
             * (door open allowed at exactly 5.0 km/h) */
            if (s_current_speed_kmh_x10 > SPEED_THRESHOLD)
            {
                s_speed_interlock_active = 1U;
            }
            else
            {
                s_speed_interlock_active = 0U;
            }

            *interlock_active_out = s_speed_interlock_active;
            result = SUCCESS;
        }
    }

    return result;
}

/**
 * @brief 20 ms cycle entry — poll TCI mailbox and evaluate interlock.
 * @complexity Cyclomatic complexity: 2 — within SIL 3 limit of 10
 */
void SPM_RunCycle(void)
{
    /* Implements: UNIT-SPM-004 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §4.3.2 */
    const tcms_speed_msg_t *frame_ptr;
    uint32_t tick_ms;
    error_t  err;

    tick_ms   = HAL_GetSystemTickMs();
    frame_ptr = TCI_GetSpeedFramePtr();

    if (NULL != frame_ptr)
    {
        err = SPM_ProcessSpeedFrame(frame_ptr, tick_ms);
        (void)err;  /* Error logged internally */
    }

    err = SPM_EvaluateInterlock(tick_ms, &g_speed_interlock_active);
    (void)err;  /* Error logged internally */
}

/**
 * @brief Get current speed value (accessor).
 * @complexity Cyclomatic complexity: 1
 */
uint16_t SPM_GetSpeed(void)
{
    /* Implements: UNIT-SPM-005 */
    return s_current_speed_kmh_x10;
}

/**
 * @brief Get SPM fault status for FMG aggregation.
 * @complexity Cyclomatic complexity: 1
 */
uint8_t SPM_GetFault(void)
{
    return s_spm_fault_flag;
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
