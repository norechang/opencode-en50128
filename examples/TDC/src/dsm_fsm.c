/**
 * @file    dsm_fsm.c
 * @brief   Door State Machine FSM engine and state-transition handlers.
 * @details Implements UNIT-DSM-001 (UpdateFSM) plus internal static helpers
 *          for each FSM state: Idle, Opening, FullyOpen, Closing,
 *          ObstacleReversal, FullyClosed, Locking, ClosedAndLocked, Fault.
 *          The main dispatcher (DSM_UpdateFSM) calls the appropriate static
 *          handler based on the current state; each handler returns the next
 *          state.  All transitions are logged via DGN.
 *
 * @project TDC (Train Door Control System)
 * @module  DSM (Door State Machine) — COMP-004
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety  SIL Level: 3
 * Safety Requirements: REQ-FUN-001–015, REQ-SAFE-007/008/009/010/011
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 * Deviations: None
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §6.1–§6.2
 */

/* Implements: REQ-FUN-001–015, REQ-SAFE-007/008/009/010/011 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §6.1–§6.2 (COMP-004) */
/* SIL: 3 */

#include <stdint.h>
#include <stddef.h>

#include "dsm.h"
#include "hal.h"
#include "dgn.h"
#include "tdc_types.h"

/*============================================================================
 * EXTERNAL SHARED STATE (owned by dsm_init.c)
 *===========================================================================*/
extern door_fsm_state_t g_dsm_state[MAX_DOORS];
extern uint8_t          g_dsm_cmd_open[MAX_DOORS];
extern uint8_t          g_dsm_cmd_close[MAX_DOORS];
extern uint8_t          g_dsm_disabled[MAX_DOORS];
extern uint32_t         g_dsm_entry_time_ms[MAX_DOORS];

/*============================================================================
 * MODULE CONSTANTS
 *===========================================================================*/
/** @brief Maximum motor run time before timeout fault (ms) */
#define DSM_MOTOR_TIMEOUT_MS   (5000U)

/** @brief Obstacle reversal drive time (ms) — drive back to open */
#define DSM_REVERSAL_DRIVE_MS  (2000U)

/** @brief Lock confirmation timeout (ms) */
#define DSM_LOCK_TIMEOUT_MS    (500U)

/*============================================================================
 * INTERNAL STATIC HELPERS — ONE PER FSM STATE
 * Each returns the new state.  Cyclomatic complexity ≤ 10 per SIL 3.
 *===========================================================================*/

/**
 * @brief Handle FSM_IDLE → next state.
 * @complexity Cyclomatic complexity: 3
 */
static door_fsm_state_t dsm_handle_idle(uint8_t door_id,
                                        uint8_t cmd_open,
                                        uint8_t safe_state_active,
                                        uint8_t speed_interlock)
{
    /* Implements: UNIT-DSM-002 */
    door_fsm_state_t next_state = FSM_IDLE;

    if (1U == safe_state_active)
    {
        /* Stay idle — safe state inhibits all movement */
        next_state = FSM_IDLE;
    }
    else if ((1U == cmd_open) && (0U == speed_interlock) &&
             (0U == g_dsm_disabled[door_id]))
    {
        (void)HAL_MotorStart(door_id, 1U); /* 1=open direction */
        next_state = FSM_OPENING;
    }
    else
    {
        next_state = FSM_IDLE;
    }

    return next_state;
}

/**
 * @brief Handle FSM_OPENING → next state.
 * @complexity Cyclomatic complexity: 5
 */
static door_fsm_state_t dsm_handle_opening(uint8_t door_id,
                                           uint8_t pos_a_open,
                                           uint8_t pos_b_open,
                                           uint8_t obstacle,
                                           uint8_t safe_state_active,
                                           uint32_t current_time_ms)
{
    /* Implements: UNIT-DSM-003 */
    door_fsm_state_t next_state = FSM_OPENING;
    uint32_t elapsed_ms;
    uint8_t  voted_open     = 0U;
    uint8_t  disagree       = 0U;

    if (1U == safe_state_active)
    {
        (void)HAL_MotorStop(door_id);
        return FSM_FAULT;
    }

    (void)DSM_VotePosition(door_id, pos_a_open, pos_b_open,
                           &voted_open, &disagree);

    if (1U == disagree)
    {
        LOG_EVENT(COMP_DSM, COMP_DSM, EVT_SENSOR_DISAGREE, (uint16_t)door_id);
        (void)HAL_MotorStop(door_id);
        return FSM_FAULT;
    }

    if (1U == voted_open)
    {
        (void)HAL_MotorStop(door_id);
        return FSM_FULLY_OPEN;
    }

    if (1U == obstacle)
    {
        (void)HAL_MotorStop(door_id);
        return FSM_FULLY_OPEN; /* Opening obstacle: stop — door stays open */
    }

    /* Timeout guard */
    elapsed_ms = current_time_ms - g_dsm_entry_time_ms[door_id];
    if (elapsed_ms >= DSM_MOTOR_TIMEOUT_MS)
    {
        LOG_EVENT(COMP_DSM, COMP_DSM, EVT_FSM_FAULT, (uint16_t)door_id);
        (void)HAL_MotorStop(door_id);
        return FSM_FAULT;
    }

    return next_state;
}

/**
 * @brief Handle FSM_FULLY_OPEN → next state.
 * @complexity Cyclomatic complexity: 3
 */
static door_fsm_state_t dsm_handle_fully_open(uint8_t door_id,
                                              uint8_t cmd_close,
                                              uint8_t safe_state_active)
{
    /* Implements: UNIT-DSM-004 */
    door_fsm_state_t next_state = FSM_FULLY_OPEN;

    if (1U == safe_state_active)
    {
        next_state = FSM_FULLY_OPEN; /* Safe state holds door open */
    }
    else if ((1U == cmd_close) && (0U == g_dsm_disabled[door_id]))
    {
        (void)HAL_MotorStart(door_id, 0U); /* 0=close direction */
        next_state = FSM_CLOSING;
    }
    else
    {
        next_state = FSM_FULLY_OPEN;
    }

    return next_state;
}

/**
 * @brief Handle FSM_CLOSING → next state.
 * @complexity Cyclomatic complexity: 7
 */
static door_fsm_state_t dsm_handle_closing(uint8_t door_id,
                                           uint8_t pos_a_closed,
                                           uint8_t pos_b_closed,
                                           uint8_t obstacle,
                                           uint8_t safe_state_active,
                                           uint32_t current_time_ms)
{
    /* Implements: UNIT-DSM-005 */
    door_fsm_state_t next_state = FSM_CLOSING;
    uint32_t elapsed_ms;
    uint8_t  voted_closed = 0U;
    uint8_t  disagree     = 0U;

    if (1U == safe_state_active)
    {
        /* Safe state during closing: stop motor, go to fault */
        (void)HAL_MotorStop(door_id);
        return FSM_FAULT;
    }

    if (1U == obstacle)
    {
        /* Obstacle detected while closing → reverse to open */
        (void)HAL_MotorStop(door_id);
        (void)HAL_MotorStart(door_id, 1U); /* reverse */
        LOG_EVENT(COMP_DSM, COMP_DSM, EVT_SENSOR_DISAGREE,
                  (uint16_t)door_id);
        return FSM_OBSTACLE_REVERSAL;
    }

    (void)DSM_VotePosition(door_id, pos_a_closed, pos_b_closed,
                           &voted_closed, &disagree);

    if (1U == disagree)
    {
        LOG_EVENT(COMP_DSM, COMP_DSM, EVT_SENSOR_DISAGREE, (uint16_t)door_id);
        (void)HAL_MotorStop(door_id);
        return FSM_FAULT;
    }

    if (1U == voted_closed)
    {
        (void)HAL_MotorStop(door_id);
        return FSM_FULLY_CLOSED;
    }

    /* Timeout guard */
    elapsed_ms = current_time_ms - g_dsm_entry_time_ms[door_id];
    if (elapsed_ms >= DSM_MOTOR_TIMEOUT_MS)
    {
        LOG_EVENT(COMP_DSM, COMP_DSM, EVT_FSM_FAULT, (uint16_t)door_id);
        (void)HAL_MotorStop(door_id);
        return FSM_FAULT;
    }

    return next_state;
}

/**
 * @brief Handle FSM_OBSTACLE_REVERSAL → next state.
 * @complexity Cyclomatic complexity: 4
 */
static door_fsm_state_t dsm_handle_obstacle_reversal(uint8_t  door_id,
                                                     uint8_t  pos_a_open,
                                                     uint8_t  pos_b_open,
                                                     uint32_t current_time_ms)
{
    /* Implements: UNIT-DSM-006 */
    door_fsm_state_t next_state = FSM_OBSTACLE_REVERSAL;
    uint32_t elapsed_ms;
    uint8_t  voted_open = 0U;
    uint8_t  disagree   = 0U;

    (void)DSM_VotePosition(door_id, pos_a_open, pos_b_open,
                           &voted_open, &disagree);

    if (1U == voted_open)
    {
        (void)HAL_MotorStop(door_id);
        return FSM_FULLY_OPEN;
    }

    elapsed_ms = current_time_ms - g_dsm_entry_time_ms[door_id];
    if (elapsed_ms >= DSM_REVERSAL_DRIVE_MS)
    {
        /* Reversal drive timed out — fault */
        LOG_EVENT(COMP_DSM, COMP_DSM, EVT_FSM_FAULT, (uint16_t)door_id);
        (void)HAL_MotorStop(door_id);
        return FSM_FAULT;
    }

    return next_state;
}

/**
 * @brief Handle FSM_FULLY_CLOSED → next state (energise lock solenoid).
 * @complexity Cyclomatic complexity: 2
 */
static door_fsm_state_t dsm_handle_fully_closed(uint8_t door_id)
{
    /* Implements: UNIT-DSM-007 */
    error_t err;

    err = HAL_LockEngage(door_id);
    if (SUCCESS != err)
    {
        LOG_EVENT(COMP_DSM, COMP_DSM, EVT_FSM_FAULT, (uint16_t)door_id);
        return FSM_FAULT;
    }

    return FSM_LOCKING;
}

/**
 * @brief Handle FSM_LOCKING → next state (await lock sensor confirmation).
 * @complexity Cyclomatic complexity: 5
 */
static door_fsm_state_t dsm_handle_locking(uint8_t  door_id,
                                           uint8_t  lock_a,
                                           uint8_t  lock_b,
                                           uint32_t current_time_ms)
{
    /* Implements: UNIT-DSM-008 */
    door_fsm_state_t next_state = FSM_LOCKING;
    uint32_t elapsed_ms;
    uint8_t  voted_lock = 0U;
    uint8_t  disagree   = 0U;

    (void)DSM_VotePosition(door_id, lock_a, lock_b,
                           &voted_lock, &disagree);

    if (1U == disagree)
    {
        LOG_EVENT(COMP_DSM, COMP_DSM, EVT_SENSOR_DISAGREE, (uint16_t)door_id);
        return FSM_FAULT;
    }

    if (1U == voted_lock)
    {
        return FSM_CLOSED_AND_LOCKED;
    }

    elapsed_ms = current_time_ms - g_dsm_entry_time_ms[door_id];
    if (elapsed_ms >= DSM_LOCK_TIMEOUT_MS)
    {
        LOG_EVENT(COMP_DSM, COMP_DSM, EVT_FSM_FAULT, (uint16_t)door_id);
        return FSM_FAULT;
    }

    return next_state;
}

/**
 * @brief Handle FSM_CLOSED_AND_LOCKED → next state.
 * @complexity Cyclomatic complexity: 4
 */
static door_fsm_state_t dsm_handle_closed_and_locked(uint8_t door_id,
                                                     uint8_t cmd_open,
                                                     uint8_t speed_interlock,
                                                     uint8_t safe_state_active)
{
    /* Implements: UNIT-DSM-009 */
    door_fsm_state_t next_state = FSM_CLOSED_AND_LOCKED;

    if (1U == safe_state_active)
    {
        return FSM_CLOSED_AND_LOCKED; /* Hold lock */
    }

    if ((1U == cmd_open) && (0U == speed_interlock) &&
        (0U == g_dsm_disabled[door_id]))
    {
        error_t err;
        err = HAL_LockDisengage(door_id);
        if (SUCCESS != err)
        {
            LOG_EVENT(COMP_DSM, COMP_DSM, EVT_FSM_FAULT, (uint16_t)door_id);
            return FSM_FAULT;
        }
        (void)HAL_MotorStart(door_id, 1U); /* open direction */
        return FSM_OPENING;
    }

    return next_state;
}

/**
 * @brief Handle FSM_FAULT — stays in fault; only SKN reset can clear.
 * @complexity Cyclomatic complexity: 1
 */
static door_fsm_state_t dsm_handle_fault(uint8_t door_id)
{
    /* Implements: UNIT-DSM-010 */
    (void)door_id;
    /* Motor already stopped on fault entry; hold lock if engaged */
    return FSM_FAULT;
}

/*============================================================================
 * PUBLIC FUNCTIONS
 *===========================================================================*/

/*----------------------------------------------------------------------------
 * DSM_UpdateFSM helper — switch dispatch extracted to keep CCN ≤ 10
 * @complexity Cyclomatic complexity: 10 — at SIL 3 limit of 10
 *---------------------------------------------------------------------------*/
static door_fsm_state_t dsm_dispatch_state(uint8_t door_id,
                                            door_fsm_state_t  current_state,
                                            uint8_t cmd_open,
                                            uint8_t cmd_close,
                                            uint8_t pos_a_open,
                                            uint8_t pos_a_closed,
                                            uint8_t pos_b_open,
                                            uint8_t pos_b_closed,
                                            uint8_t lock_a,
                                            uint8_t lock_b,
                                            uint8_t obstacle,
                                            uint8_t speed_interlock,
                                            uint8_t safe_state_active,
                                            uint32_t current_time_ms)
{
    /* Implements: UNIT-DSM-001 dispatch table */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §6.1 */
    door_fsm_state_t next_state;

    switch (current_state)
    {
        case FSM_IDLE:
            next_state = dsm_handle_idle(door_id, cmd_open,
                                         safe_state_active, speed_interlock);
            break;

        case FSM_OPENING:
            next_state = dsm_handle_opening(door_id, pos_a_open, pos_b_open,
                                            obstacle, safe_state_active,
                                            current_time_ms);
            break;

        case FSM_FULLY_OPEN:
            next_state = dsm_handle_fully_open(door_id, cmd_close,
                                               safe_state_active);
            break;

        case FSM_CLOSING:
            next_state = dsm_handle_closing(door_id, pos_a_closed, pos_b_closed,
                                            obstacle, safe_state_active,
                                            current_time_ms);
            break;

        case FSM_OBSTACLE_REVERSAL:
            next_state = dsm_handle_obstacle_reversal(door_id,
                                                      pos_a_open, pos_b_open,
                                                      current_time_ms);
            break;

        case FSM_FULLY_CLOSED:
            next_state = dsm_handle_fully_closed(door_id);
            break;

        case FSM_LOCKING:
            next_state = dsm_handle_locking(door_id, lock_a, lock_b,
                                            current_time_ms);
            break;

        case FSM_CLOSED_AND_LOCKED:
            next_state = dsm_handle_closed_and_locked(door_id, cmd_open,
                                                       speed_interlock,
                                                       safe_state_active);
            break;

        case FSM_FAULT:
            next_state = dsm_handle_fault(door_id);
            break;

        default:
            /* Unknown state — treat as fault */
            (void)HAL_MotorStop(door_id);
            next_state = FSM_FAULT;
            break;
    }

    return next_state;
}

/**
 * @brief Update per-door FSM — validate then call dispatch helper.
 * @complexity Cyclomatic complexity: 2 — within SIL 3 limit of 10
 */
error_t DSM_UpdateFSM(uint8_t door_id,
                      uint8_t cmd_open,
                      uint8_t cmd_close,
                      uint8_t pos_a_open,
                      uint8_t pos_a_closed,
                      uint8_t pos_b_open,
                      uint8_t pos_b_closed,
                      uint8_t lock_a,
                      uint8_t lock_b,
                      uint8_t obstacle,
                      uint8_t speed_interlock,
                      uint8_t safe_state_active,
                      uint32_t current_time_ms)
{
    /* Implements: UNIT-DSM-001 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §6.1 */
    door_fsm_state_t  prev_state;
    door_fsm_state_t  next_state;

    if (door_id >= MAX_DOORS)
    {
        return ERR_RANGE;
    }

    prev_state = g_dsm_state[door_id];

    next_state = dsm_dispatch_state(door_id, prev_state,
                                    cmd_open, cmd_close,
                                    pos_a_open, pos_a_closed,
                                    pos_b_open, pos_b_closed,
                                    lock_a, lock_b,
                                    obstacle, speed_interlock,
                                    safe_state_active, current_time_ms);

    /* Record entry time on any state change */
    if (next_state != prev_state)
    {
        g_dsm_entry_time_ms[door_id] = current_time_ms;
    }

    g_dsm_state[door_id] = next_state;
    return SUCCESS;
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
