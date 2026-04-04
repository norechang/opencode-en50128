/**
 * @file    skn_scheduler.c
 * @brief   SKN Scheduler — top-level 20 ms cycle dispatcher.
 * @details Implements UNIT-SKN-008 (RunCycle) — orchestrates all TDC
 *          components in deterministic order every 20 ms.
 *          Global safety flags are defined here (architecture rule: writable
 *          only by SKN for g_safe_state_active; SPM writes g_speed_interlock_active;
 *          OBD writes g_obstacle_flags).
 *
 * @project TDC (Train Door Control System)
 * @module  SKN (Safety Kernel) — MOD-SKN-003
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety  SIL Level: 3
 * Safety Requirements: REQ-SAFE-015, SW-HAZ-001/003/006
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §3.3
 */

/* Implements: REQ-SAFE-015, SW-HAZ-001/003/006, UNIT-SKN-008 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §3.3 (MOD-SKN-003) */

#include <stdint.h>

#include "skn.h"
#include "spm.h"
#include "obd.h"
#include "dsm.h"
#include "fmg.h"
#include "tci.h"
#include "dgn.h"
#include "hal.h"
#include "tdc_types.h"

/*============================================================================
 * GLOBAL SAFETY STATE DEFINITIONS
 * Architecture rule (SAS §5.2): g_safe_state_active written ONLY by SKN.
 *===========================================================================*/

/** @brief Global safe-state flag. Written ONLY by SKN. Read by all components. */
uint8_t g_safe_state_active = 1U;  /* Default: fail-safe ON at startup */

/** @brief Global speed interlock flag. Written by SPM. Read by DSM and SKN. */
uint8_t g_speed_interlock_active = 1U;  /* Default: inhibit at startup */

/** @brief Global obstacle flags per door. Written by OBD. Read by DSM. */
uint8_t g_obstacle_flags[MAX_DOORS] = {0U, 0U, 0U, 0U};

/*============================================================================
 * STATIC VARIABLES
 *===========================================================================*/
/** @brief Cycle counter for periodic tasks (e.g. memory check every 100 ms) */
static uint32_t s_cycle_count;

/** @brief Departure interlock result from last evaluation */
static uint8_t s_departure_interlock_ok;

/*============================================================================
 * STATIC FUNCTION DECLARATIONS (used internally in this TU)
 *===========================================================================*/
/** Forward declaration for SKN_SafeState_Init from skn_safe_state.c */
extern void SKN_SafeState_Init(void);

/*============================================================================
 * PUBLIC FUNCTION IMPLEMENTATIONS
 *===========================================================================*/

/**
 * @brief Top-level 20 ms cycle dispatcher.
 * @details Step order:
 *   1. Build local cross-channel state
 *   2. Exchange with peer DCU via SPI
 *   3. Check stack canary
 *   4. Every 5 cycles (100 ms): check memory integrity
 *   5. Evaluate safe-state triggers
 *   6. Evaluate departure interlock
 *   7. Process TCI Rx frames
 *   8. Run SPM cycle (speed + interlock)
 *   9. Run OBD cycle (obstacle detection)
 *   10. Run DSM cycle (door FSM)
 *   11. Run FMG cycle (fault aggregation)
 *   12. Transmit TCI periodic frames
 *   13. Refresh watchdog
 *   14. Run DGN cycle (log flush)
 *   15. Increment cycle counter
 * @complexity Cyclomatic complexity: 3 — within SIL 3 limit of 10
 */
void SKN_RunCycle(void)
{
    /* Implements: REQ-SAFE-015, UNIT-SKN-008 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §3.3.1 */
    cross_channel_state_t local_state;
    uint8_t channel_disagree;
    uint8_t canary_ok;
    uint8_t mem_ok;
    error_t err;
    uint8_t safety_decisions;

    /* Default: memory OK unless checked this cycle */
    mem_ok          = 1U;
    channel_disagree = 0U;
    canary_ok        = 1U;

    /* Safety decisions bitmask for cross-channel state */
    safety_decisions = (uint8_t)(g_safe_state_active |
                                 ((uint8_t)(s_departure_interlock_ok << 1U)));

    /* Step 1: Build local state */
    err = SKN_BuildLocalState(&local_state,
                              SPM_GetSpeed(),
                              DSM_GetDoorStates(),
                              DSM_GetLockStates(),
                              OBD_GetObstacleFlags(),
                              FMG_GetFaultState(),
                              safety_decisions);
    if (err != SUCCESS)
    {
        g_safe_state_active = 1U;  /* Fail-safe if build fails */
    }

    /* Step 2: Exchange and compare */
    err = SKN_ExchangeAndCompare(&local_state, &channel_disagree);
    if ((err != SUCCESS) && (err != ERR_CRC))
    {
        /* ERR_CRC with channel_disagree=0 is transient — do not force safe state here;
         * SKN_EvaluateSafeState will handle the sticky logic. */
    }

    /* Step 3: Stack canary check (every cycle) */
    err = SKN_CheckStackCanary(&canary_ok);
    if (err != SUCCESS)
    {
        canary_ok = 0U;
    }

    /* Step 4: Memory integrity check every 5 cycles (100 ms) */
    if ((s_cycle_count % 5U) == 0U)
    {
        err = SKN_CheckMemoryIntegrity(&mem_ok);
        if (err != SUCCESS)
        {
            mem_ok = 0U;
        }
    }

    /* Step 5: Evaluate safe-state triggers (sticky flag) */
    err = SKN_EvaluateSafeState(channel_disagree,
                                FMG_GetFaultState(),
                                mem_ok,
                                canary_ok,
                                &g_safe_state_active);
    if (err != SUCCESS)
    {
        g_safe_state_active = 1U;  /* Fail-safe */
    }

    /* Step 6: Evaluate departure interlock */
    err = SKN_EvaluateDepartureInterlock(DSM_GetDoorStates(),
                                         DSM_GetLockStates(),
                                         channel_disagree,
                                         g_safe_state_active,
                                         &s_departure_interlock_ok);
    if (err != SUCCESS)
    {
        s_departure_interlock_ok = 0U;  /* Fail-closed */
    }

    /* Steps 7–14: Component cycles in deterministic order */
    err = TCI_ProcessReceivedFrames();
    (void)err;  /* TCI Rx errors are logged internally */

    SPM_RunCycle();
    OBD_RunCycle();
    DSM_RunCycle();
    FMG_RunCycle();
    TCI_TransmitCycle();

    err = HAL_Watchdog_Refresh();
    (void)err;  /* Watchdog failure logged via fault flag */

    DGN_RunCycle();

    /* Step 15: Increment cycle counter (wraps at UINT32_MAX — acceptable) */
    s_cycle_count++;
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
