/**
 * @file    fmg_aggregator.c
 * @brief   FMG fault aggregation and classification.
 * @details Implements UNIT-FMG-001 (AggregateFaults), UNIT-FMG-002
 *          (ClassifyAndEscalate), UNIT-FMG-003 (HandleSelectiveDisablement),
 *          and FMG_ProcessEmergencyStop.
 *
 * @project TDC (Train Door Control System)
 * @module  FMG (Fault Manager) — COMP-005
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety  SIL Level: 3
 * Safety Requirements: REQ-SAFE-012/013/021, REQ-FUN-013/017/018
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §7.1–§7.3
 */

/* Implements: REQ-SAFE-012/013/021, REQ-FUN-013/017/018 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §7.1–§7.3 (COMP-005) */
/* SIL: 3 */

#include <stdint.h>
#include <stddef.h>

#include "fmg.h"
#include "dgn.h"
#include "tdc_types.h"

/*============================================================================
 * FAULT BITMASK CONSTANTS
 * Each bit corresponds to one component's fault flag.
 *===========================================================================*/
#define FMG_FAULT_BIT_SPM  (0x01U)  /**< SPM fault bit */
#define FMG_FAULT_BIT_OBD  (0x02U)  /**< OBD fault bit */
#define FMG_FAULT_BIT_DSM  (0x04U)  /**< DSM fault bit */
#define FMG_FAULT_BIT_TCI  (0x08U)  /**< TCI fault bit */
#define FMG_FAULT_BIT_HAL  (0x10U)  /**< HAL fault bit */

/*============================================================================
 * EXTERNAL SHARED STATE (owned by fmg_init.c)
 *===========================================================================*/
extern uint8_t          g_fmg_fault_state;
extern fault_severity_t g_fmg_max_severity;
extern uint8_t          g_fmg_disabled_doors;
extern uint8_t          g_fmg_emergency_stop_active;

/**
 * @brief Aggregate fault flags from all components.
 * @complexity Cyclomatic complexity: 2
 */
error_t FMG_AggregateFaults(uint8_t  spm_fault,
                             uint8_t  obd_fault,
                             uint8_t  dsm_fault,
                             uint8_t  tci_fault,
                             uint8_t  hal_fault,
                             uint8_t *fault_state_out)
{
    /* Implements: UNIT-FMG-001 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §7.1 */
    if (NULL == fault_state_out)
    {
        return ERR_NULL_PTR;
    }

    *fault_state_out = 0U;

    if (spm_fault != 0U) { *fault_state_out |= FMG_FAULT_BIT_SPM; }
    if (obd_fault != 0U) { *fault_state_out |= FMG_FAULT_BIT_OBD; }
    if (dsm_fault != 0U) { *fault_state_out |= FMG_FAULT_BIT_DSM; }
    if (tci_fault != 0U) { *fault_state_out |= FMG_FAULT_BIT_TCI; }
    if (hal_fault != 0U) { *fault_state_out |= FMG_FAULT_BIT_HAL; }

    return SUCCESS;
}

/**
 * @brief Classify fault bitmask and escalate to maximum severity.
 * @complexity Cyclomatic complexity: 4
 */
error_t FMG_ClassifyAndEscalate(uint8_t           fault_state,
                                 fault_severity_t *max_severity_out)
{
    /* Implements: UNIT-FMG-002 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §7.2 */
    if (NULL == max_severity_out)
    {
        return ERR_NULL_PTR;
    }

    /* CRITICAL: HAL fault or combined DSM+SPM = total loss of safe operation */
    if ((fault_state & FMG_FAULT_BIT_HAL) != 0U)
    {
        *max_severity_out = FAULT_CRITICAL;
        LOG_EVENT(COMP_FMG, COMP_FMG, EVT_FAULT_ACTIVE, (uint16_t)FAULT_CRITICAL);
        return SUCCESS;
    }

    /* HIGH: DSM fault = direct safety function loss */
    if ((fault_state & FMG_FAULT_BIT_DSM) != 0U)
    {
        *max_severity_out = FAULT_HIGH;
        LOG_EVENT(COMP_FMG, COMP_FMG, EVT_FAULT_ACTIVE, (uint16_t)FAULT_HIGH);
        return SUCCESS;
    }

    /* MEDIUM: SPM or TCI fault = speed interlock or comms degraded */
    if (((fault_state & FMG_FAULT_BIT_SPM) != 0U) ||
        ((fault_state & FMG_FAULT_BIT_TCI) != 0U))
    {
        *max_severity_out = FAULT_MEDIUM;
        LOG_EVENT(COMP_FMG, COMP_FMG, EVT_FAULT_ACTIVE, (uint16_t)FAULT_MEDIUM);
        return SUCCESS;
    }

    /* LOW: OBD fault only */
    if ((fault_state & FMG_FAULT_BIT_OBD) != 0U)
    {
        *max_severity_out = FAULT_LOW;
        LOG_EVENT(COMP_FMG, COMP_FMG, EVT_FAULT_ACTIVE, (uint16_t)FAULT_LOW);
        return SUCCESS;
    }

    *max_severity_out = FAULT_NONE;
    return SUCCESS;
}

/**
 * @brief Apply selective door disablement when authorised by TCMS.
 * @complexity Cyclomatic complexity: 2
 */
error_t FMG_HandleSelectiveDisablement(uint8_t door_mask,
                                        uint8_t tcms_authorized)
{
    /* Implements: UNIT-FMG-003 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §7.3 */
    if (0U == tcms_authorized)
    {
        LOG_EVENT(COMP_FMG, COMP_FMG, EVT_SELECTIVE_DISABLE_UNAUTHORIZED,
                  (uint16_t)door_mask);
        return ERR_NOT_PERMITTED;
    }

    g_fmg_disabled_doors = door_mask;
    LOG_EVENT(COMP_FMG, COMP_FMG, EVT_SELECTIVE_DISABLE, (uint16_t)door_mask);
    return SUCCESS;
}

/**
 * @brief Process emergency stop command.
 * @complexity Cyclomatic complexity: 1
 */
error_t FMG_ProcessEmergencyStop(uint8_t stop_code)
{
    g_fmg_emergency_stop_active = 1U;
    LOG_EVENT(COMP_FMG, COMP_FMG, EVT_FAULT_ACTIVE, (uint16_t)stop_code);
    return SUCCESS;
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
