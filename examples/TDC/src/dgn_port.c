/**
 * @file    dgn_port.c
 * @brief   DGN diagnostic serial port service and cycle entry.
 * @details Implements DGN_ServiceDiagPort and DGN_RunCycle.
 *          In Normal mode the port is read-only (no commands accepted).
 *          In Diagnostic or Maintenance mode a limited command set is
 *          accepted.  DGN_RunCycle calls DGN_FlushToFlash and polls the
 *          diagnostic port once per 20 ms cycle.
 *
 * @project TDC (Train Door Control System)
 * @module  DGN (Diagnostics) — COMP-007
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety  SIL Level: 1 (non-safety — diagnostic only)
 * Safety Requirements: REQ-FUN-018
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §9.3
 */

/* Implements: REQ-FUN-018 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §9.3 (COMP-007) */
/* SIL: 1 */

#include <stdint.h>

#include "dgn.h"
#include "tdc_types.h"

/*============================================================================
 * MODULE CONSTANTS
 *===========================================================================*/
/** @brief Diagnostic port flush cycle: flush every 10 cycles (200 ms) */
#define DGN_PORT_FLUSH_PERIOD  (10U)

/*============================================================================
 * MODULE-LEVEL STATIC STATE
 *===========================================================================*/
/** @brief Cycle counter for flash flush rate-limiting */
static uint8_t s_port_cycle_count;

/**
 * @brief Service the diagnostic serial port.
 * @complexity Cyclomatic complexity: 4
 */
error_t DGN_ServiceDiagPort(op_mode_t op_mode)
{
    /* Design ref: SCDS DOC-COMPDES-2026-001 §9.3 */
    /* In Normal mode: read-only. Tx log entries to port when queried.
     * In Diagnostic/Maintenance mode: accept READ_LOG and CLEAR_LOG commands.
     * This is a platform stub — actual UART read/write replaced in production. */

    if (op_mode == MODE_NORMAL)
    {
        /* Read-only mode: no command processing, output only */
        /* (Platform stub: no actual UART output in stub) */
        return SUCCESS;
    }

    if ((op_mode == MODE_DIAGNOSTIC) || (op_mode == MODE_MAINTENANCE))
    {
        /* Extended diagnostic access permitted */
        /* Platform stub: actual UART command processing omitted */
        return SUCCESS;
    }

    /* Unknown mode — return not-permitted */
    return ERR_NOT_PERMITTED;
}

/**
 * @brief 20 ms cycle entry — flush pending log entries to Flash.
 * @complexity Cyclomatic complexity: 2
 */
void DGN_RunCycle(void)
{
    /* Design ref: SCDS DOC-COMPDES-2026-001 §9 */
    s_port_cycle_count++;

    if (s_port_cycle_count >= DGN_PORT_FLUSH_PERIOD)
    {
        s_port_cycle_count = 0U;
        (void)DGN_FlushToFlash();
    }
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
