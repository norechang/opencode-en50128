/**
 * @file    skn_safe_state.c
 * @brief   SKN Safe State Manager — safe-state evaluation and departure interlock.
 * @details Implements UNIT-SKN-004 (EvaluateSafeState), UNIT-SKN-005
 *          (EvaluateDepartureInterlock), UNIT-SKN-006 (CheckMemoryIntegrity),
 *          UNIT-SKN-007 (CheckStackCanary), and SKN_GetDepartureInterlock accessor.
 *
 * @project TDC (Train Door Control System)
 * @module  SKN (Safety Kernel) — MOD-SKN-002
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety  SIL Level: 3
 * Safety Requirements: REQ-SAFE-007/008/009/012/015, SW-HAZ-003/006/008
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §3.2
 */

/* Implements: REQ-SAFE-007/008/009/012/015, SW-HAZ-003/006/008 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §3.2 (MOD-SKN-002) */

#include <stdint.h>
#include <stddef.h>

#include "skn.h"
#include "hal.h"
#include "tdc_types.h"

/*============================================================================
 * PREPROCESSOR DEFINITIONS
 *===========================================================================*/
/** @brief Bitmask for critical faults in FMG fault state (bits 0, 1, 2) */
#define SKN_FAULT_CRITICAL_MASK  (0x07U)

/** @brief Size of CRC input: all bytes of cross_channel_state_t except crc16 */
#define SKN_CRC_DATA_LEN \
    ((uint16_t)(sizeof(cross_channel_state_t) - sizeof(uint16_t)))

/*============================================================================
 * EXTERNAL SYMBOLS (linker-provided memory region markers)
 * On target: these are placed by the linker script.
 * Stub: static arrays used for unit testing.
 *===========================================================================*/
/** @brief Start of ROM region for CRC check (linker symbol) */
extern uint8_t  __rom_start__;
/** @brief End of ROM region for CRC check (linker symbol) */
extern uint8_t  __rom_end__;
/** @brief Expected ROM CRC (initialised by SKN_Init) */
extern uint16_t __rom_expected_crc__;
/** @brief Top-of-stack canary location (linker symbol) */
extern uint32_t __stack_top_canary__;
/** @brief Bottom-of-stack canary location (linker symbol) */
extern uint32_t __stack_bottom_canary__;

/*============================================================================
 * STATIC VARIABLES
 *===========================================================================*/
/** @brief Safe-state flag — sticky: once set, never cleared in normal ops */
static uint8_t s_safe_state_active;

/** @brief Departure interlock flag — 1 if all doors CLOSED_AND_LOCKED */
static uint8_t s_departure_interlock_ok;

/** @brief CRC-16 snapshot of safety-critical global variables (taken at init) */
static uint16_t s_safety_globals_crc_snapshot;

/** @brief Safety globals region for CRC snapshot (stub for unit testing) */
static uint8_t s_safety_globals_region[SAFETY_GLOBALS_LEN];

/*============================================================================
 * PUBLIC FUNCTION IMPLEMENTATIONS
 *===========================================================================*/

/**
 * @brief Evaluate safe-state triggers — sticky flag, never cleared.
 * @complexity Cyclomatic complexity: 5 — within SIL 3 limit of 10
 */
error_t SKN_EvaluateSafeState(uint8_t channel_disagree,
                              uint8_t fault_state,
                              uint8_t memory_crc_ok,
                              uint8_t stack_canary_ok,
                              uint8_t *safe_state_active_out)
{
    /* Implements: REQ-SAFE-008/012, UNIT-SKN-004 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §3.2.1 */
    error_t result;
    uint8_t critical_fault;
    uint8_t trigger;

    if (NULL == safe_state_active_out)
    {
        result = ERR_NULL_PTR;
    }
    else
    {
        critical_fault = (fault_state & SKN_FAULT_CRITICAL_MASK);
        trigger = (uint8_t)(channel_disagree | critical_fault);

        if (0U == memory_crc_ok)
        {
            trigger = 1U;
        }
        else if (0U == stack_canary_ok)
        {
            trigger = 1U;
        }
        else
        {
            /* No action — both checks passed */
        }

        if (0U != trigger)
        {
            /* Safe state is STICKY — never cleared in normal operation */
            s_safe_state_active = 1U;
        }

        *safe_state_active_out = s_safe_state_active;
        result = SUCCESS;
    }

    return result;
}

/**
 * @brief Evaluate departure interlock (all doors CLOSED_AND_LOCKED).
 * @complexity Cyclomatic complexity: 7 — within SIL 3 limit of 10
 */
error_t SKN_EvaluateDepartureInterlock(const uint8_t door_states[MAX_DOORS],
                                       const uint8_t lock_states[MAX_DOORS],
                                       uint8_t channel_disagree,
                                       uint8_t safe_state_active,
                                       uint8_t *interlock_ok_out)
{
    /* Implements: REQ-SAFE-007, SW-HAZ-003, UNIT-SKN-005 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §3.2.2 */
    error_t result;
    uint8_t all_locked;
    uint8_t door_idx;

    if ((NULL == door_states) || (NULL == lock_states) || (NULL == interlock_ok_out))
    {
        if (NULL != interlock_ok_out)
        {
            *interlock_ok_out = 0U;  /* Fail-closed */
        }
        result = ERR_NULL_PTR;
    }
    else if ((1U == safe_state_active) || (1U == channel_disagree))
    {
        *interlock_ok_out = 0U;
        s_departure_interlock_ok = 0U;
        result = SUCCESS;
    }
    else
    {
        all_locked = 1U;

        for (door_idx = 0U; door_idx < MAX_DOORS; door_idx++)
        {
            if ((uint8_t)DOOR_STATE_CLOSED_AND_LOCKED != door_states[door_idx])
            {
                all_locked = 0U;
            }
            else if (0U == lock_states[door_idx])
            {
                all_locked = 0U;
            }
            else
            {
                /* Door locked — continue checking remaining doors */
            }
        }

        *interlock_ok_out        = all_locked;
        s_departure_interlock_ok = all_locked;
        result = SUCCESS;
    }

    return result;
}

/**
 * @brief Check ROM and safety-critical RAM CRC-16 integrity.
 * @complexity Cyclomatic complexity: 4 — within SIL 3 limit of 10
 */
error_t SKN_CheckMemoryIntegrity(uint8_t *crc_ok_out)
{
    /* Implements: REQ-SAFE-009, SW-HAZ-008, UNIT-SKN-006 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §3.2.3 */
    error_t  result;
    uint16_t rom_crc;
    uint16_t ram_crc;
    uint16_t rom_len;

    if (NULL == crc_ok_out)
    {
        result = ERR_NULL_PTR;
    }
    else
    {
        /* ROM CRC check — use uintptr_t arithmetic (not pointer subtraction)
         * to avoid MISRA Rule 18.2 / cppcheck comparePointers on extern
         * linker symbols __rom_start__ / __rom_end__. */
        rom_len = (uint16_t)((uintptr_t)&__rom_end__ - (uintptr_t)&__rom_start__);
        rom_crc = CRC16_CCITT_Compute(&__rom_start__, rom_len);

        if (rom_crc != __rom_expected_crc__)
        {
            *crc_ok_out = 0U;
            result = ERR_CRC;
        }
        else
        {
            /* Safety-critical RAM CRC check */
            ram_crc = CRC16_CCITT_Compute(s_safety_globals_region,
                                          SAFETY_GLOBALS_LEN);

            if (ram_crc != s_safety_globals_crc_snapshot)
            {
                *crc_ok_out = 0U;
                result = ERR_CRC;
            }
            else
            {
                *crc_ok_out = 1U;
                result = SUCCESS;
            }
        }
    }

    return result;
}

/**
 * @brief Check stack canary values at top and bottom of stack.
 * @complexity Cyclomatic complexity: 3 — within SIL 3 limit of 10
 */
error_t SKN_CheckStackCanary(uint8_t *canary_ok_out)
{
    /* Implements: REQ-SAFE-009, SW-HAZ-008, UNIT-SKN-007 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §3.2.4 */
    error_t result;

    if (NULL == canary_ok_out)
    {
        result = ERR_NULL_PTR;
    }
    else if ((__stack_top_canary__    != (uint32_t)CANARY_VALUE) ||
             (__stack_bottom_canary__ != (uint32_t)CANARY_VALUE))
    {
        *canary_ok_out = 0U;
        result = ERR_HW_FAULT;
    }
    else
    {
        *canary_ok_out = 1U;
        result = SUCCESS;
    }

    return result;
}

/**
 * @brief Get current departure interlock status.
 * @complexity Cyclomatic complexity: 1
 */
uint8_t SKN_GetDepartureInterlock(void)
{
    /* Implements: accessor for s_departure_interlock_ok */
    return s_departure_interlock_ok;
}

/**
 * @brief Initialise safe-state module — clear all flags, take CRC snapshots.
 * @complexity Cyclomatic complexity: 1
 */
void SKN_SafeState_Init(void)
{
    /* Implements: part of UNIT-SKN-009, called from skn_init.c */
    uint8_t byte_idx;

    s_safe_state_active      = 0U;
    s_departure_interlock_ok = 0U;

    /* Initialise safety globals region and take CRC snapshot */
    for (byte_idx = 0U; byte_idx < SAFETY_GLOBALS_LEN; byte_idx++)
    {
        s_safety_globals_region[byte_idx] = 0U;
    }
    s_safety_globals_crc_snapshot = CRC16_CCITT_Compute(s_safety_globals_region,
                                                         SAFETY_GLOBALS_LEN);

    /* Place stack canary values */
    __stack_top_canary__    = (uint32_t)CANARY_VALUE;
    __stack_bottom_canary__ = (uint32_t)CANARY_VALUE;
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
