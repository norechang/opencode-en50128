/**
 * @file    tci.h
 * @brief   TCMS Interface (TCI) public interface for TDC
 * @details CAN receive mailbox, frame processing with CRC-16 validation,
 *          departure interlock and door status transmit, sequence counter
 *          management, and cycle entry.
 *
 * @project TDC (Train Door Control System)
 * @module  TCI (TCMS Interface) — COMP-006
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety
 * SIL Level: 3
 * Safety Requirements: REQ-SAFE-003/016, REQ-FUN-016, REQ-INT-007/008/009
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §8
 */

#ifndef TCI_H
#define TCI_H

#include <stdint.h>
#include "tdc_types.h"

/** @brief Maximum number of CAN Rx mailbox slots (IDs 0x100–0x104) */
#define TCI_CAN_RX_MAILBOX_COUNT (5U)

/**
 * @brief CAN receive mailbox entry (one per expected CAN ID).
 */
typedef struct {
    uint32_t msg_id;              /**< CAN message identifier */
    uint8_t  data[8];             /**< CAN data bytes */
    uint8_t  dlc;                 /**< Data Length Code (0–8) */
    uint32_t rx_timestamp_ms;     /**< System tick at time of reception */
    uint8_t  valid;               /**< 1=entry contains unprocessed frame */
} can_mailbox_t;

/**
 * @brief Initialise TCI module — clear mailboxes, reset sequence counters.
 * @return error_t SUCCESS
 * @note   UNIT-TCI-007; Complexity: 1
 */
error_t TCI_Init(void);

/**
 * @brief CAN receive ISR — copy frame from HAL FIFO to static mailbox.
 * @details Minimal ISR: one HAL read, one bounds check, copy. No processing.
 * @note   UNIT-TCI-001; Complexity: 3
 */
void TCI_CanRxISR(void);

/**
 * @brief Process all pending CAN receive mailbox frames (called from cycle).
 * @details Validates CRC-16-CCITT, routes each validated frame to the
 *          appropriate handler by CAN message ID.
 * @return error_t SUCCESS (individual frame CRC errors are logged, not returned)
 * @note   UNIT-TCI-002; Complexity: 8
 */
error_t TCI_ProcessReceivedFrames(void);

/**
 * @brief Transmit departure interlock status (CAN ID 0x200) every 100 ms.
 * @param[in] interlock_ok 1=all doors locked (departure allowed), 0=not ready
 * @return error_t SUCCESS, ERR_TIMEOUT
 * @note   UNIT-TCI-003; Complexity: 1
 */
error_t TCI_TransmitDepartureInterlock(uint8_t interlock_ok);

/**
 * @brief Transmit door and lock status summary (CAN ID 0x201) every 100 ms.
 * @param[in] door_states Array of door states [MAX_DOORS]
 * @param[in] lock_states Array of lock states [MAX_DOORS]
 * @return error_t SUCCESS, ERR_NULL_PTR, ERR_TIMEOUT
 * @note   UNIT-TCI-004; Complexity: 1
 */
error_t TCI_TransmitDoorStatus(const uint8_t door_states[MAX_DOORS],
                               const uint8_t lock_states[MAX_DOORS]);

/**
 * @brief Transmit fault report to TCMS (CAN ID 0x202).
 * @param[in] fault_code  Fault code byte
 * @param[in] severity    Fault severity
 * @return error_t SUCCESS, ERR_TIMEOUT
 * @note   UNIT-TCI-005; Complexity: 1
 */
error_t TCI_TransmitFaultReport(uint8_t fault_code, fault_severity_t severity);

/**
 * @brief Validate Rx sequence counter delta for a given CAN message ID.
 * @param[in] msg_id CAN message ID (0x100–0x104)
 * @param[in] rx_seq Received sequence counter value
 * @return error_t SUCCESS, ERR_RANGE (sequence discontinuity is logged, not fatal)
 * @note   UNIT-TCI-006; Complexity: 3
 */
error_t TCI_ValidateRxSeqDelta(uint8_t msg_id, uint8_t rx_seq);

/**
 * @brief 20 ms cycle entry — transmit periodic status frames every 100 ms.
 * @note   UNIT-TCI-008; Complexity: 2
 */
void TCI_TransmitCycle(void);

/**
 * @brief Get pointer to latest validated speed frame (for SPM polling).
 * @return const tcms_speed_msg_t* Latest speed frame, or NULL if no valid frame
 */
const tcms_speed_msg_t *TCI_GetSpeedFramePtr(void);

/**
 * @brief Get TCI fault status for FMG aggregation.
 * @return uint8_t 0 = no fault, non-zero = CAN fault
 */
uint8_t TCI_GetFault(void);

#endif /* TCI_H */

/*============================================================================
 * END OF FILE
 *===========================================================================*/
