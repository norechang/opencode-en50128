/**
 * @file    dsm_voter.c
 * @brief   DSM 2oo2 position sensor voter.
 * @details Implements UNIT-DSM-012: applies 2-out-of-2 voting to a pair of
 *          binary sensor readings.  If both sensors agree the agreed value is
 *          returned; if they disagree the output is set to 0 (fail-safe) and
 *          the disagree flag is set.
 *
 * @project TDC (Train Door Control System)
 * @module  DSM (Door State Machine) — COMP-004
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety  SIL Level: 3
 * Safety Requirements: REQ-SAFE-008/010, SW-HAZ-003
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §6.2
 */

/* Implements: REQ-SAFE-008/010, SW-HAZ-003 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §6.2 (COMP-004) */
/* SIL: 3 */

#include <stdint.h>
#include <stddef.h>

#include "dsm.h"
#include "tdc_types.h"

/**
 * @brief 2oo2 position sensor voter.
 * @complexity Cyclomatic complexity: 3 — within SIL 3 limit of 10
 */
error_t DSM_VotePosition(uint8_t  door_id,
                         uint8_t  pos_a,
                         uint8_t  pos_b,
                         uint8_t *voted_position,
                         uint8_t *disagree_out)
{
    /* Implements: UNIT-DSM-012 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §6.2 */

    if ((NULL == voted_position) || (NULL == disagree_out))
    {
        return ERR_NULL_PTR;
    }

    if (door_id >= MAX_DOORS)
    {
        *voted_position = 0U; /* Fail-safe: no position */
        *disagree_out   = 1U;
        return ERR_RANGE;
    }

    /* Normalise to 0 or 1 */
    if (((pos_a != 0U) ? 1U : 0U) == ((pos_b != 0U) ? 1U : 0U))
    {
        *voted_position = (pos_a != 0U) ? 1U : 0U;
        *disagree_out   = 0U;
    }
    else
    {
        /* Sensors disagree — fail-safe: report no-position */
        *voted_position = 0U;
        *disagree_out   = 1U;
    }

    return SUCCESS;
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
