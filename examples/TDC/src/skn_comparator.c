/**
 * @file    skn_comparator.c
 * @brief   SKN Cross-Channel Comparator — SPI exchange and field comparison.
 * @details Implements UNIT-SKN-001 (BuildLocalState), UNIT-SKN-002
 *          (ExchangeAndCompare), and UNIT-SKN-003 (FieldsDisagree).
 *          OI-FMEA-001 SPI transient filter: 3 consecutive infrastructure
 *          faults required before asserting safe state. CRC failure or
 *          field disagreement → immediate safe state.
 *
 * @project TDC (Train Door Control System)
 * @module  SKN (Safety Kernel) — MOD-SKN-001
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety  SIL Level: 3
 * Safety Requirements: REQ-SAFE-002/008/010, SW-HAZ-001/003/011
 *
 * @misra_compliance
 * MISRA C:2012 Compliance:
 * - All mandatory rules: Compliant
 * - No dynamic allocation, no recursion, no function pointers
 * - Fixed-width types throughout
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §3.1
 */

/* Implements: REQ-SAFE-002/008/010/018, SW-HAZ-001/003/011 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §3.1 (MOD-SKN-001) */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "skn.h"
#include "hal.h"
#include "dgn.h"
#include "tdc_types.h"

/*============================================================================
 * PREPROCESSOR DEFINITIONS
 *===========================================================================*/
/** @brief Number of consecutive SPI infrastructure faults before safe-state */
#define SKN_SPI_FAULT_THRESHOLD (3U)

/** @brief Size of CRC input region: all bytes except trailing crc16 field */
#define SKN_CRC_DATA_LEN \
    ((uint16_t)(sizeof(cross_channel_state_t) - sizeof(uint16_t)))

/*============================================================================
 * STATIC VARIABLES
 *===========================================================================*/
/** @brief Buffer for the remote channel state received over SPI */
static cross_channel_state_t s_remote_state;

/** @brief SPI infrastructure fault consecutive counter (OI-FMEA-001) */
static uint8_t s_spi_infra_fault_count;

/** @brief Last known-good remote state (used during transient filter) */
static cross_channel_state_t s_last_good_remote;

/*============================================================================
 * STATIC FUNCTION PROTOTYPES
 *===========================================================================*/
/**
 * @brief Compare all safety-critical fields between two cross-channel states.
 * @param[in] a Pointer to first state
 * @param[in] b Pointer to second state
 * @return uint8_t 1 if any field disagrees, 0 if all agree
 * @note UNIT-SKN-003; Complexity: 8
 */
static uint8_t SKN_FieldsDisagree(const cross_channel_state_t *a,
                                   const cross_channel_state_t *b);

/*============================================================================
 * PUBLIC FUNCTION IMPLEMENTATIONS
 *===========================================================================*/

/**
 * @brief Build local safety state structure with CRC-16-CCITT.
 * @complexity Cyclomatic complexity: 2 — within SIL 3 limit of 10
 */
error_t SKN_BuildLocalState(cross_channel_state_t *state,
                            uint16_t speed_kmh_x10,
                            const uint8_t door_states[MAX_DOORS],
                            const uint8_t lock_states[MAX_DOORS],
                            const uint8_t obstacle_flags[MAX_DOORS],
                            uint8_t fault_flags,
                            uint8_t safety_decisions)
{
    /* Implements: REQ-SAFE-010/018, UNIT-SKN-001 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §3.1.1 */
    error_t result;
    uint8_t door_idx;

    if (NULL == state)
    {
        result = ERR_NULL_PTR;
    }
    else
    {
        state->speed_kmh_x10  = speed_kmh_x10;
        state->fault_flags    = fault_flags;
        state->safety_decisions = safety_decisions;

        for (door_idx = 0U; door_idx < MAX_DOORS; door_idx++)
        {
            state->door_states[door_idx]    = door_states[door_idx];
            state->lock_states[door_idx]    = lock_states[door_idx];
            state->obstacle_flags[door_idx] = obstacle_flags[door_idx];
        }

        /* Compute CRC-16-CCITT over all fields except trailing crc16 */
        state->crc16 = CRC16_CCITT_Compute((const uint8_t *)state,
                                            SKN_CRC_DATA_LEN);
        result = SUCCESS;
    }

    return result;
}

/**
 * @brief Exchange cross-channel state via SPI and compare safety fields.
 * @details Implements OI-FMEA-001 transient filter (3-consecutive rule).
 * @complexity Cyclomatic complexity: 7 — within SIL 3 limit of 10
 */
error_t SKN_ExchangeAndCompare(const cross_channel_state_t *local,
                               uint8_t *safe_state_active_out)
{
    /* Implements: REQ-SAFE-002/008, OI-FMEA-001, SW-HAZ-011, UNIT-SKN-002 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §3.1.2 */
    error_t result;
    error_t spi_result;
    uint16_t computed_crc;

    if ((NULL == local) || (NULL == safe_state_active_out))
    {
        result = ERR_NULL_PTR;
    }
    else
    {
        /* Step 1: SPI exchange */
        spi_result = HAL_SPI_CrossChannel_Exchange(local, &s_remote_state);

        if (spi_result != SUCCESS)
        {
            /* SPI infrastructure fault: CRC error, timeout, or HW error */
            if (s_spi_infra_fault_count < SKN_SPI_FAULT_THRESHOLD)
            {
                s_spi_infra_fault_count++;
            }

            if (s_spi_infra_fault_count >= SKN_SPI_FAULT_THRESHOLD)
            {
                /* 3 consecutive faults → assert safe state */
                *safe_state_active_out = 1U;
                LOG_EVENT(DGN, COMP_SKN, EVT_SPI_INFRA_PERSISTENT,
                          (uint16_t)s_spi_infra_fault_count);
                result = ERR_COMM_TIMEOUT;
            }
            else
            {
                /* Transient: use last known-good, do NOT assert safe state */
                s_remote_state = s_last_good_remote;
                *safe_state_active_out = 0U;
                LOG_EVENT(DGN, COMP_SKN, EVT_SPI_INFRA_TRANSIENT,
                          (uint16_t)s_spi_infra_fault_count);
                result = ERR_CRC;
            }
        }
        else
        {
            /* Step 2: Validate remote CRC-16 over safety-data payload */
            computed_crc = CRC16_CCITT_Compute((const uint8_t *)&s_remote_state,
                                               SKN_CRC_DATA_LEN);

            if (computed_crc != s_remote_state.crc16)
            {
                /* CRC failure on safety data → immediate safe state */
                s_spi_infra_fault_count = 0U;
                *safe_state_active_out  = 1U;
                LOG_EVENT(DGN, COMP_SKN, EVT_SPI_CRC_FAIL, 0U);
                result = ERR_CRC;
            }
            else
            {
                /* Step 3: CRC OK — reset counter and compare fields */
                s_spi_infra_fault_count = 0U;
                s_last_good_remote      = s_remote_state;

                if (1U == SKN_FieldsDisagree(local, &s_remote_state))
                {
                    /* Safety-data disagreement → immediate safe state */
                    *safe_state_active_out = 1U;
                    LOG_EVENT(DGN, COMP_SKN, EVT_CHANNEL_DISAGREE, 0U);
                    result = ERR_SENSOR_DISAGREE;
                }
                else
                {
                    *safe_state_active_out = 0U;
                    result = SUCCESS;
                }
            }
        }
    }

    return result;
}

/*============================================================================
 * STATIC FUNCTION IMPLEMENTATIONS
 *===========================================================================*/

/**
 * @brief Compare all safety-critical fields between two cross-channel states.
 * @complexity Cyclomatic complexity: 8 — within SIL 3 limit of 10
 */
static uint8_t SKN_FieldsDisagree(const cross_channel_state_t *a,
                                   const cross_channel_state_t *b)
{
    /* Implements: UNIT-SKN-003 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §3.1.3 */
    uint8_t disagree;
    uint8_t door_idx;

    disagree = 0U;

    if (a->speed_kmh_x10 != b->speed_kmh_x10)
    {
        disagree = 1U;
    }
    else
    {
        for (door_idx = 0U; door_idx < MAX_DOORS; door_idx++)
        {
            if (a->door_states[door_idx] != b->door_states[door_idx])
            {
                disagree = 1U;
            }
            else if (a->lock_states[door_idx] != b->lock_states[door_idx])
            {
                disagree = 1U;
            }
            else if (a->obstacle_flags[door_idx] != b->obstacle_flags[door_idx])
            {
                disagree = 1U;
            }
            else
            {
                /* No action — MISRA Rule 15.7: else clause required */
            }
        }

        if (a->fault_flags != b->fault_flags)
        {
            disagree = 1U;
        }
        else if (a->safety_decisions != b->safety_decisions)
        {
            disagree = 1U;
        }
        else
        {
            /* No action */
        }
    }

    return disagree;
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
