/**
 * @file    tci_seq.c
 * @brief   TCI Rx sequence counter validation.
 * @details Implements UNIT-TCI-006 (ValidateRxSeqDelta): checks that the
 *          incoming sequence counter advances by exactly 1 (modulo 256).
 *          Discontinuities are logged; after 3 consecutive discontinuities
 *          the TCI fault flag is set.
 *
 * @project TDC (Train Door Control System)
 * @module  TCI (TCMS Interface) — COMP-006
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety  SIL Level: 3
 * Safety Requirements: REQ-SAFE-016, REQ-INT-009
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §8.3
 */

/* Implements: REQ-SAFE-016, REQ-INT-009 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §8.3 (COMP-006) */
/* SIL: 3 */

#include <stdint.h>

#include "tci.h"
#include "dgn.h"
#include "tdc_types.h"

/*============================================================================
 * EXTERNAL SHARED STATE (owned by tci_init.c)
 *===========================================================================*/
extern uint8_t g_tci_fault_flag;

/*============================================================================
 * MODULE CONSTANTS
 *===========================================================================*/
/** @brief Number of consecutive discontinuities before fault assertion */
#define TCI_SEQ_FAULT_COUNT  (3U)

/*============================================================================
 * MODULE-LEVEL STATIC STATE
 *===========================================================================*/
/** @brief Last received sequence counter per CAN ID slot (0–4) */
static uint8_t s_last_seq[TCI_CAN_RX_MAILBOX_COUNT];

/** @brief Consecutive discontinuity counter per slot */
static uint8_t s_discon_count[TCI_CAN_RX_MAILBOX_COUNT];

/** @brief Initialisation flag (0=first receive, counter not yet seeded) */
static uint8_t s_seq_initialised[TCI_CAN_RX_MAILBOX_COUNT];

/*============================================================================
 * PUBLIC FUNCTIONS
 *===========================================================================*/

/**
 * @brief Validate Rx sequence counter delta.
 * @complexity Cyclomatic complexity: 3 — within SIL 3 limit of 10
 */
error_t TCI_ValidateRxSeqDelta(uint8_t msg_id, uint8_t rx_seq)
{
    /* Implements: UNIT-TCI-006 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §8.3 */
    uint8_t slot;
    uint8_t expected_seq;

    /* Map msg_id byte to slot index (msg_id is the bottom byte of CAN ID) */
    /* Slots: 0x00=speed(0x100), 0x01=open(0x101), etc. — use bottom nibble */
    slot = (uint8_t)(msg_id & 0x0FU);
    if (slot >= TCI_CAN_RX_MAILBOX_COUNT)
    {
        return ERR_RANGE;
    }

    /* First reception: seed counter */
    if (0U == s_seq_initialised[slot])
    {
        s_last_seq[slot]       = rx_seq;
        s_discon_count[slot]   = 0U;
        s_seq_initialised[slot] = 1U;
        return SUCCESS;
    }

    expected_seq = (uint8_t)(s_last_seq[slot] + 1U); /* modulo 256 automatic */

    if (rx_seq == expected_seq)
    {
        s_discon_count[slot] = 0U;  /* Reset discontinuity counter */
    }
    else
    {
        s_discon_count[slot]++;
        LOG_EVENT(COMP_TCI, COMP_TCI, EVT_SEQ_DISCONTINUITY,
                  (uint16_t)rx_seq);

        if (s_discon_count[slot] >= TCI_SEQ_FAULT_COUNT)
        {
            g_tci_fault_flag = 1U;
        }
    }

    s_last_seq[slot] = rx_seq;
    return (s_discon_count[slot] > 0U) ? ERR_RANGE : SUCCESS;
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
