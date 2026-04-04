/**
 * @file    tci_init.c
 * @brief   TCI module initialisation, cycle entry, fault accessor, and
 *          global mailbox state.
 * @details Implements UNIT-TCI-007 (Init), UNIT-TCI-008 (TransmitCycle),
 *          TCI_GetFault.
 *          Also owns g_tci_mailbox and g_tci_fault_flag (extern in other TCI
 *          files).
 *
 * @project TDC (Train Door Control System)
 * @module  TCI (TCMS Interface) — COMP-006
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety  SIL Level: 3
 * Safety Requirements: REQ-SAFE-003/016, REQ-INT-007/008/009
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §8
 */

/* Implements: REQ-SAFE-003/016, REQ-INT-007/008/009 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §8 (COMP-006) */
/* SIL: 3 */

#include <stdint.h>
#include <stddef.h>

#include "tci.h"
#include "skn.h"
#include "dsm.h"
#include "fmg.h"
#include "hal.h"
#include "dgn.h"
#include "tdc_types.h"

/*============================================================================
 * GLOBAL SHARED STATE — Owned here, externs in tci_rx.c / tci_seq.c
 *===========================================================================*/
can_mailbox_t g_tci_mailbox[TCI_CAN_RX_MAILBOX_COUNT];
uint8_t       g_tci_fault_flag = 0U;

/*============================================================================
 * MODULE CONSTANTS
 *===========================================================================*/
/** @brief Transmit cycle divisor: transmit every 100 ms = 5 × 20 ms cycles */
#define TCI_TX_CYCLE_DIVISOR  (5U)

/*============================================================================
 * MODULE-LEVEL STATIC STATE
 *===========================================================================*/
/** @brief 20 ms cycle counter (0–4) to time 100 ms transmit period */
static uint8_t s_tx_cycle_count;

/**
 * @brief Initialise TCI module.
 * @complexity Cyclomatic complexity: 2
 */
error_t TCI_Init(void)
{
    /* Implements: UNIT-TCI-007 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §8 */
    uint8_t i;
    uint8_t b;

    for (i = 0U; i < TCI_CAN_RX_MAILBOX_COUNT; i++)
    {
        g_tci_mailbox[i].msg_id          = 0U;
        g_tci_mailbox[i].dlc             = 0U;
        g_tci_mailbox[i].rx_timestamp_ms = 0U;
        g_tci_mailbox[i].valid           = 0U;

        for (b = 0U; b < 8U; b++)
        {
            g_tci_mailbox[i].data[b] = 0U;
        }
    }

    g_tci_fault_flag  = 0U;
    s_tx_cycle_count  = 0U;

    return SUCCESS;
}

/**
 * @brief 20 ms cycle entry — process Rx frames and transmit periodic status.
 * @complexity Cyclomatic complexity: 2
 */
void TCI_TransmitCycle(void)
{
    /* Implements: UNIT-TCI-008 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §8 */
    error_t err;

    /* Process any newly received CAN frames every cycle */
    err = TCI_ProcessReceivedFrames();
    if (SUCCESS != err)
    {
        g_tci_fault_flag = 1U;
    }

    /* Transmit status every 100 ms */
    s_tx_cycle_count++;
    if (s_tx_cycle_count >= TCI_TX_CYCLE_DIVISOR)
    {
        s_tx_cycle_count = 0U;

        err = TCI_TransmitDepartureInterlock(SKN_GetDepartureInterlock());
        if (SUCCESS != err)
        {
            g_tci_fault_flag = 1U;
        }

        err = TCI_TransmitDoorStatus(DSM_GetDoorStates(), DSM_GetLockStates());
        if (SUCCESS != err)
        {
            g_tci_fault_flag = 1U;
        }

        if (FMG_GetFaultState() != 0U)
        {
            err = TCI_TransmitFaultReport(FMG_GetFaultState(),
                                          (fault_severity_t)FAULT_HIGH);
            if (SUCCESS != err)
            {
                g_tci_fault_flag = 1U;
            }
        }
    }
}

/**
 * @brief Get TCI fault status.
 * @complexity Cyclomatic complexity: 1
 */
uint8_t TCI_GetFault(void)
{
    return g_tci_fault_flag;
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
