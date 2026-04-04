/**
 * @file    dsm_emergency.c
 * @brief   DSM emergency door release handler.
 * @details Implements UNIT-DSM-014: handles emergency release button with
 *          60 ms debounce per SW-HAZ-009.  On confirmed release, forces door
 *          to FULLY_OPEN regardless of current speed or mode.
 *
 * @project TDC (Train Door Control System)
 * @module  DSM (Door State Machine) — COMP-004
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety  SIL Level: 3
 * Safety Requirements: REQ-SAFE-011, SW-HAZ-009
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §6.4
 */

/* Implements: REQ-SAFE-011, SW-HAZ-009 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §6.4 (COMP-004) */
/* SIL: 3 */

#include <stdint.h>

#include "dsm.h"
#include "hal.h"
#include "dgn.h"
#include "tdc_types.h"

/*============================================================================
 * EXTERNAL SHARED STATE (owned by dsm_init.c)
 *===========================================================================*/
extern door_fsm_state_t g_dsm_state[MAX_DOORS];
extern uint32_t         g_dsm_entry_time_ms[MAX_DOORS];

/*============================================================================
 * MODULE CONSTANTS
 *===========================================================================*/
/** @brief Emergency release debounce period per SW-HAZ-009 (ms) */
#define DSM_EMERG_DEBOUNCE_MS  (60U)

/*============================================================================
 * MODULE-LEVEL STATIC STATE
 *===========================================================================*/
/** @brief First-seen timestamp for emergency release debounce (per door) */
static uint32_t s_emerg_first_seen_ms[MAX_DOORS];

/** @brief Pending debounce flag (1=debounce in progress) */
static uint8_t  s_emerg_debouncing[MAX_DOORS];

/**
 * @brief Handle emergency door release with 60 ms debounce.
 * @complexity Cyclomatic complexity: 4 — within SIL 3 limit of 10
 */
error_t DSM_HandleEmergencyRelease(uint8_t door_id, uint32_t current_time_ms)
{
    /* Implements: UNIT-DSM-014 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §6.4 */
    uint32_t elapsed_ms;
    uint8_t  gpio_state;

    if (door_id >= MAX_DOORS)
    {
        return ERR_RANGE;
    }

    gpio_state = HAL_GPIO_ReadEmergencyRelease(door_id);

    if (0U == gpio_state)
    {
        /* Button released — reset debounce state */
        s_emerg_debouncing[door_id]    = 0U;
        s_emerg_first_seen_ms[door_id] = 0U;
        return SUCCESS;
    }

    /* Button pressed — start or continue debounce */
    if (0U == s_emerg_debouncing[door_id])
    {
        s_emerg_first_seen_ms[door_id] = current_time_ms;
        s_emerg_debouncing[door_id]    = 1U;
        return SUCCESS;
    }

    elapsed_ms = current_time_ms - s_emerg_first_seen_ms[door_id];
    if (elapsed_ms >= DSM_EMERG_DEBOUNCE_MS)
    {
        /* Debounce confirmed — force door open regardless of state */
        (void)HAL_LockDisengage(door_id);
        (void)HAL_MotorStart(door_id, 1U); /* open direction */
        g_dsm_state[door_id]         = FSM_OPENING;
        g_dsm_entry_time_ms[door_id] = current_time_ms;
        s_emerg_debouncing[door_id]  = 0U;
        LOG_EVENT(COMP_DSM, COMP_DSM, EVT_EMERGENCY_RELEASE, (uint16_t)door_id);
    }

    return SUCCESS;
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
