/**
 * @file    tci_tx.c
 * @brief   TCI CAN transmit functions.
 * @details Implements UNIT-TCI-003 (TransmitDepartureInterlock),
 *          UNIT-TCI-004 (TransmitDoorStatus), UNIT-TCI-005
 *          (TransmitFaultReport).  Each frame carries a CRC-16-CCITT over
 *          the payload bytes before the CRC field.
 *
 * @project TDC (Train Door Control System)
 * @module  TCI (TCMS Interface) — COMP-006
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety  SIL Level: 3
 * Safety Requirements: REQ-SAFE-003, REQ-FUN-016, REQ-INT-008/009
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §8.2
 */

/* Implements: REQ-SAFE-003, REQ-FUN-016, REQ-INT-008/009 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §8.2 (COMP-006) */
/* SIL: 3 */

#include <stdint.h>
#include <stddef.h>

#include "tci.h"
#include "hal.h"
#include "dgn.h"
#include "tdc_types.h"

/*============================================================================
 * MODULE CONSTANTS — CAN transmit IDs
 *===========================================================================*/
#define TCI_TX_ID_INTERLOCK   (0x200U)  /**< Departure interlock status */
#define TCI_TX_ID_DOOR_STATUS (0x201U)  /**< Door and lock status */
#define TCI_TX_ID_FAULT       (0x202U)  /**< Fault report */

/*============================================================================
 * PRIVATE HELPERS
 *===========================================================================*/

/**
 * @brief Pack a uint16_t CRC into two bytes (big-endian).
 * @complexity Cyclomatic complexity: 1
 */
static void tci_pack_crc(uint16_t crc, uint8_t *buf, uint8_t offset)
{
    buf[offset]      = (uint8_t)(crc >> 8U);
    buf[offset + 1U] = (uint8_t)(crc & 0xFFU);
}

/*============================================================================
 * PUBLIC FUNCTIONS
 *===========================================================================*/

/**
 * @brief Transmit departure interlock status (CAN ID 0x200) every 100 ms.
 * @complexity Cyclomatic complexity: 1
 */
error_t TCI_TransmitDepartureInterlock(uint8_t interlock_ok)
{
    /* Implements: UNIT-TCI-003 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §8.2 */
    uint8_t  data[3];  /* [0]=interlock_ok, [1-2]=CRC */
    uint16_t crc;

    data[0U] = (interlock_ok != 0U) ? 1U : 0U;
    crc = CRC16_CCITT_Compute(data, 1U);
    tci_pack_crc(crc, data, 1U);

    return HAL_CAN_Transmit(TCI_TX_ID_INTERLOCK, data, 3U);
}

/**
 * @brief Transmit door and lock status (CAN ID 0x201) every 100 ms.
 * @complexity Cyclomatic complexity: 2
 */
error_t TCI_TransmitDoorStatus(const uint8_t door_states[MAX_DOORS],
                                const uint8_t lock_states[MAX_DOORS])
{
    /* Implements: UNIT-TCI-004 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §8.2 */
    uint8_t  data[MAX_DOORS + MAX_DOORS + 2U]; /* 4 door + 4 lock + 2 CRC */
    uint16_t crc;
    uint8_t  i;

    if ((NULL == door_states) || (NULL == lock_states))
    {
        return ERR_NULL_PTR;
    }

    for (i = 0U; i < MAX_DOORS; i++)
    {
        data[i]             = door_states[i];
        data[i + MAX_DOORS] = lock_states[i];
    }

    crc = CRC16_CCITT_Compute(data, (uint16_t)(MAX_DOORS + MAX_DOORS));
    tci_pack_crc(crc, data, (uint8_t)(MAX_DOORS + MAX_DOORS));

    return HAL_CAN_Transmit(TCI_TX_ID_DOOR_STATUS, data,
                            (uint8_t)(MAX_DOORS + MAX_DOORS + 2U));
}

/**
 * @brief Transmit fault report to TCMS (CAN ID 0x202).
 * @complexity Cyclomatic complexity: 1
 */
error_t TCI_TransmitFaultReport(uint8_t fault_code, fault_severity_t severity)
{
    /* Implements: UNIT-TCI-005 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §8.2 */
    uint8_t  data[4];  /* [0]=fault_code, [1]=severity, [2-3]=CRC */
    uint16_t crc;

    data[0U] = fault_code;
    data[1U] = (uint8_t)severity;
    crc = CRC16_CCITT_Compute(data, 2U);
    tci_pack_crc(crc, data, 2U);

    return HAL_CAN_Transmit(TCI_TX_ID_FAULT, data, 4U);
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
