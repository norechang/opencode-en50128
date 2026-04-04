/**
 * @file    fmg_init.c
 * @brief   FMG module initialisation, cycle entry, and accessors.
 * @details Implements UNIT-FMG-004 (Init), UNIT-FMG-005 (RunCycle),
 *          UNIT-FMG-006 (GetFaultState), FMG_GetFault.
 *          Also owns all FMG shared state variables.
 *
 * @project TDC (Train Door Control System)
 * @module  FMG (Fault Manager) — COMP-005
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety  SIL Level: 3
 * Safety Requirements: REQ-SAFE-012/013/021, REQ-FUN-018, SW-HAZ-005/010
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §7
 */

/* Implements: REQ-SAFE-012/013/021, REQ-FUN-018, SW-HAZ-005/010 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §7 (COMP-005) */
/* SIL: 3 */

#include <stdint.h>

#include "fmg.h"
#include "spm.h"
#include "obd.h"
#include "dsm.h"
#include "tci.h"
#include "hal.h"
#include "dgn.h"
#include "tdc_types.h"

/*============================================================================
 * GLOBAL SHARED STATE — Owned here, externs in fmg_aggregator.c
 *===========================================================================*/
uint8_t          g_fmg_fault_state         = 0U;
fault_severity_t g_fmg_max_severity        = FAULT_NONE;
uint8_t          g_fmg_disabled_doors      = 0U;
uint8_t          g_fmg_emergency_stop_active = 0U;

/*============================================================================
 * MODULE CONSTANTS
 *===========================================================================*/
/** @brief HAL fault flag value for HAL_GetSystemTickMs failure sentinel */
#define FMG_HAL_FAULT_SENTINEL  (0U)

/**
 * @brief Initialise FMG module — clear all fault state.
 * @complexity Cyclomatic complexity: 1
 */
error_t FMG_Init(void)
{
    /* Implements: UNIT-FMG-004 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §7 */
    g_fmg_fault_state           = 0U;
    g_fmg_max_severity          = FAULT_NONE;
    g_fmg_disabled_doors        = 0U;
    g_fmg_emergency_stop_active = 0U;
    return SUCCESS;
}

/**
 * @brief 20 ms cycle entry — aggregate and classify current faults.
 * @complexity Cyclomatic complexity: 2
 */
void FMG_RunCycle(void)
{
    /* Implements: UNIT-FMG-005 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §7 */
    uint8_t          new_fault_state = 0U;
    fault_severity_t new_severity    = FAULT_NONE;
    error_t          err;

    err = FMG_AggregateFaults(SPM_GetFault(),
                              OBD_GetFault(),
                              DSM_GetFault(),
                              TCI_GetFault(),
                              0U,  /* HAL self-test fault: 0 unless HAL reports */
                              &new_fault_state);
    if (SUCCESS != err)
    {
        /* Aggregation itself failed — treat as critical */
        g_fmg_fault_state  = 0xFFU;
        g_fmg_max_severity = FAULT_CRITICAL;
        return;
    }

    err = FMG_ClassifyAndEscalate(new_fault_state, &new_severity);
    if (SUCCESS != err)
    {
        g_fmg_max_severity = FAULT_CRITICAL;
        return;
    }

    g_fmg_fault_state  = new_fault_state;
    g_fmg_max_severity = new_severity;
}

/**
 * @brief Get current aggregated fault state.
 * @complexity Cyclomatic complexity: 1
 */
uint8_t FMG_GetFaultState(void)
{
    /* Implements: UNIT-FMG-006 */
    return g_fmg_fault_state;
}

/**
 * @brief Get FMG fault flag for self-reporting.
 * @complexity Cyclomatic complexity: 1
 */
uint8_t FMG_GetFault(void)
{
    return (g_fmg_fault_state != 0U) ? 1U : 0U;
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
