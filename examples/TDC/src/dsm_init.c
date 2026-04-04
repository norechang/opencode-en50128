/**
 * @file    dsm_init.c
 * @brief   DSM module initialisation, cycle entry, accessors, and global state.
 * @details Implements UNIT-DSM-015 (Init), UNIT-DSM-016 (RunCycle),
 *          UNIT-DSM-017 (GetDoorStates), UNIT-DSM-018 (GetLockStates),
 *          DSM_GetClosingFlags, DSM_GetFault, DSM_ProcessOpenCommand,
 *          DSM_ProcessCloseCommand.
 *          Also owns all DSM shared state variables (extern in dsm_fsm.c,
 *          dsm_mode.c, dsm_emergency.c).
 *
 * @project TDC (Train Door Control System)
 * @module  DSM (Door State Machine) — COMP-004
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety  SIL Level: 3
 * Safety Requirements: REQ-FUN-001–015, REQ-SAFE-007, REQ-SAFE-015
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §6
 */

/* Implements: REQ-FUN-001–015, REQ-SAFE-007, REQ-SAFE-015 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §6 (COMP-004) */
/* SIL: 3 */

#include <stdint.h>
#include <stddef.h>

#include "dsm.h"
#include "hal.h"
#include "skn.h"
#include "spm.h"
#include "dgn.h"
#include "tdc_types.h"

/*============================================================================
 * GLOBAL SHARED STATE — Owned here, externs in other DSM files
 *===========================================================================*/
door_fsm_state_t g_dsm_state[MAX_DOORS];
uint8_t          g_dsm_cmd_open[MAX_DOORS];
uint8_t          g_dsm_cmd_close[MAX_DOORS];
uint8_t          g_dsm_disabled[MAX_DOORS];
uint32_t         g_dsm_entry_time_ms[MAX_DOORS];
op_mode_t        g_dsm_mode;

/*============================================================================
 * MODULE-LEVEL STATIC STATE
 *===========================================================================*/
/** @brief Cached door state array (door_state_t cast to uint8_t) */
static uint8_t s_door_states[MAX_DOORS];

/** @brief Cached lock state array (1=locked) */
static uint8_t s_lock_states[MAX_DOORS];

/** @brief Closing-in-progress flags (1=door is closing) */
static uint8_t s_closing_flags[MAX_DOORS];

/** @brief DSM aggregated fault flag (0=OK, non-zero=fault) */
static uint8_t s_dsm_fault_flag;

/*============================================================================
 * PRIVATE HELPERS
 *===========================================================================*/

/**
 * @brief Map internal FSM state to external door_state_t value.
 * @complexity Cyclomatic complexity: 5
 */
static uint8_t dsm_map_state_to_external(door_fsm_state_t fsm_state)
{
    uint8_t ext_state;

    switch (fsm_state)
    {
        case FSM_FULLY_OPEN:
            ext_state = (uint8_t)DOOR_STATE_FULLY_OPEN;
            break;
        case FSM_IDLE:
        case FSM_OPENING:
        case FSM_CLOSING:
        case FSM_OBSTACLE_REVERSAL:
            ext_state = (uint8_t)DOOR_STATE_INTERMEDIATE;
            break;
        case FSM_FULLY_CLOSED:
        case FSM_LOCKING:
            ext_state = (uint8_t)DOOR_STATE_FULLY_CLOSED;
            break;
        case FSM_CLOSED_AND_LOCKED:
            ext_state = (uint8_t)DOOR_STATE_CLOSED_AND_LOCKED;
            break;
        case FSM_FAULT:
        default:
            ext_state = (uint8_t)DOOR_STATE_FAULT;
            break;
    }

    return ext_state;
}

/*============================================================================
 * PUBLIC FUNCTIONS
 *===========================================================================*/

/**
 * @brief Initialise DSM module.
 * @complexity Cyclomatic complexity: 2
 */
error_t DSM_Init(void)
{
    /* Implements: UNIT-DSM-015 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §6 */
    uint8_t i;

    for (i = 0U; i < MAX_DOORS; i++)
    {
        g_dsm_state[i]        = FSM_IDLE;
        g_dsm_cmd_open[i]     = 0U;
        g_dsm_cmd_close[i]    = 0U;
        g_dsm_disabled[i]     = 0U;
        g_dsm_entry_time_ms[i]= 0U;
        s_door_states[i]      = (uint8_t)DOOR_STATE_UNKNOWN;
        s_lock_states[i]      = 0U;
        s_closing_flags[i]    = 0U;
    }

    g_dsm_mode      = MODE_NORMAL;
    s_dsm_fault_flag = 0U;

    return SUCCESS;
}

/**
 * @brief 20 ms cycle entry — read sensors and advance each door FSM.
 * @complexity Cyclomatic complexity: 3
 */
void DSM_RunCycle(void)
{
    /* Implements: UNIT-DSM-016 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §6 */
    uint8_t  i;
    uint32_t tick_ms;
    error_t  err;

    /* Read sensor inputs for each door and advance FSM */
    uint8_t pos_a_open    = 0U;
    uint8_t pos_a_closed  = 0U;
    uint8_t pos_b_open    = 0U;
    uint8_t pos_b_closed  = 0U;
    uint8_t lock_a        = 0U;
    uint8_t lock_b        = 0U;

    tick_ms = HAL_GetSystemTickMs();

    for (i = 0U; i < MAX_DOORS; i++)
    {
        /* Read sensors — errors treated as sensor absent (fail-safe) */
        (void)HAL_GPIO_ReadPositionSensor(i, 0U, &pos_a_open);
        (void)HAL_GPIO_ReadPositionSensor(i, 1U, &pos_b_open);
        (void)HAL_GPIO_ReadPositionSensor(i, 0U, &pos_a_closed);
        (void)HAL_GPIO_ReadPositionSensor(i, 1U, &pos_b_closed);
        (void)HAL_GPIO_ReadLockSensor(i, 0U, &lock_a);
        (void)HAL_GPIO_ReadLockSensor(i, 1U, &lock_b);

        /* Advance FSM */
        err = DSM_UpdateFSM(i,
                            g_dsm_cmd_open[i],
                            g_dsm_cmd_close[i],
                            pos_a_open,
                            pos_a_closed,
                            pos_b_open,
                            pos_b_closed,
                            lock_a,
                            lock_b,
                            g_obstacle_flags[i],
                            g_speed_interlock_active,
                            g_safe_state_active,
                            tick_ms);
        if (SUCCESS != err)
        {
            s_dsm_fault_flag = 1U;
        }

        /* Handle emergency release */
        err = DSM_HandleEmergencyRelease(i, tick_ms);
        if (SUCCESS != err)
        {
            s_dsm_fault_flag = 1U;
        }

        /* Update exported state arrays */
        s_door_states[i]   = dsm_map_state_to_external(g_dsm_state[i]);
        s_lock_states[i]   = (g_dsm_state[i] == FSM_CLOSED_AND_LOCKED) ? 1U : 0U;
        s_closing_flags[i] = (g_dsm_state[i] == FSM_CLOSING) ? 1U : 0U;

        /* Set fault if any door in FAULT state */
        if (g_dsm_state[i] == FSM_FAULT)
        {
            s_dsm_fault_flag = 1U;
        }
    }
}

/**
 * @brief Process open command from TCMS.
 * @complexity Cyclomatic complexity: 2
 */
error_t DSM_ProcessOpenCommand(uint8_t door_mask)
{
    uint8_t i;

    for (i = 0U; i < MAX_DOORS; i++)
    {
        if ((door_mask & (1U << i)) != 0U)
        {
            g_dsm_cmd_open[i]  = 1U;
            g_dsm_cmd_close[i] = 0U;
        }
    }

    return SUCCESS;
}

/**
 * @brief Process close command from TCMS.
 * @complexity Cyclomatic complexity: 2
 */
error_t DSM_ProcessCloseCommand(uint8_t door_mask)
{
    uint8_t i;

    for (i = 0U; i < MAX_DOORS; i++)
    {
        if ((door_mask & (1U << i)) != 0U)
        {
            g_dsm_cmd_close[i] = 1U;
            g_dsm_cmd_open[i]  = 0U;
        }
    }

    return SUCCESS;
}

/**
 * @brief Get door state array.
 * @complexity Cyclomatic complexity: 1
 */
const uint8_t *DSM_GetDoorStates(void)
{
    /* Implements: UNIT-DSM-017 */
    return s_door_states;
}

/**
 * @brief Get lock state array.
 * @complexity Cyclomatic complexity: 1
 */
const uint8_t *DSM_GetLockStates(void)
{
    /* Implements: UNIT-DSM-018 */
    return s_lock_states;
}

/**
 * @brief Get closing flags array (for OBD obstacle detection).
 * @complexity Cyclomatic complexity: 1
 */
const uint8_t *DSM_GetClosingFlags(void)
{
    return s_closing_flags;
}

/**
 * @brief Get DSM fault status.
 * @complexity Cyclomatic complexity: 1
 */
uint8_t DSM_GetFault(void)
{
    return s_dsm_fault_flag;
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
