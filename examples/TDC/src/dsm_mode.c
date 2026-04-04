/**
 * @file    dsm_mode.c
 * @brief   DSM operational mode transition handler.
 * @details Implements UNIT-DSM-013: validates mode transition guard conditions
 *          and applies the mode change if authorised.
 *
 * @project TDC (Train Door Control System)
 * @module  DSM (Door State Machine) — COMP-004
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety  SIL Level: 3
 * Safety Requirements: REQ-SAFE-019/020, REQ-FUN-016/017
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §6.3
 */

/* Implements: REQ-SAFE-019/020, REQ-FUN-016/017 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §6.3 (COMP-004) */
/* SIL: 3 */

#include <stdint.h>

#include "dsm.h"
#include "dgn.h"
#include "tdc_types.h"

/*============================================================================
 * EXTERNAL SHARED STATE (owned by dsm_init.c)
 *===========================================================================*/
extern op_mode_t g_dsm_mode;

/**
 * @brief Transition operational mode with guard conditions.
 * @complexity Cyclomatic complexity: 8 — within SIL 3 limit of 10
 */
error_t DSM_TransitionMode(op_mode_t requested_mode,
                           uint8_t   tcms_authorized,
                           uint8_t   speed_zero)
{
    /* Implements: UNIT-DSM-013 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §6.3 */
    error_t result = SUCCESS;

    /* Guard: TCMS authorisation is mandatory for all mode changes */
    if (0U == tcms_authorized)
    {
        return ERR_NOT_PERMITTED;
    }

    switch (requested_mode)
    {
        case MODE_NORMAL:
            /* Always permitted if TCMS authorises */
            g_dsm_mode = MODE_NORMAL;
            break;

        case MODE_DIAGNOSTIC:
            /* Diagnostic requires speed = 0 */
            if (0U == speed_zero)
            {
                result = ERR_NOT_PERMITTED;
            }
            else
            {
                g_dsm_mode = MODE_DIAGNOSTIC;
                LOG_EVENT(COMP_DSM, COMP_DSM, EVT_LOG_INIT, (uint16_t)MODE_DIAGNOSTIC);
            }
            break;

        case MODE_MAINTENANCE:
            /* Maintenance requires speed = 0 */
            if (0U == speed_zero)
            {
                result = ERR_NOT_PERMITTED;
            }
            else
            {
                g_dsm_mode = MODE_MAINTENANCE;
                LOG_EVENT(COMP_DSM, COMP_DSM, EVT_LOG_INIT, (uint16_t)MODE_MAINTENANCE);
            }
            break;

        case MODE_DOOR_DISABLED:
            /* Door disabled allowed in any speed — requires authorisation (already checked) */
            g_dsm_mode = MODE_DOOR_DISABLED;
            LOG_EVENT(COMP_DSM, COMP_DSM, EVT_SELECTIVE_DISABLE, 0U);
            break;

        default:
            result = ERR_INVALID_STATE;
            break;
    }

    return result;
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
