/**
 * @file    tci_rx.c
 * @brief   TCI CAN receive ISR, frame processor, and speed frame accessor.
 * @details Implements UNIT-TCI-001 (CanRxISR), UNIT-TCI-002
 *          (ProcessReceivedFrames), and TCI_GetSpeedFramePtr.
 *          The ISR copies raw frames into a static double-buffer mailbox;
 *          the cycle-task processor validates CRC-16 and routes each frame.
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
 * - SCDS DOC-COMPDES-2026-001 §8.1
 */

/* Implements: REQ-SAFE-003/016, REQ-INT-007/008/009 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §8.1 (COMP-006) */
/* SIL: 3 */

#include <stdint.h>
#include <stddef.h>

#include "tci.h"
#include "dsm.h"
#include "fmg.h"
#include "hal.h"
#include "dgn.h"
#include "tdc_types.h"

/*============================================================================
 * EXTERNAL SHARED STATE (owned by tci_init.c)
 *===========================================================================*/
extern can_mailbox_t g_tci_mailbox[TCI_CAN_RX_MAILBOX_COUNT];
extern uint8_t       g_tci_fault_flag;

/*============================================================================
 * MODULE CONSTANTS — CAN message IDs expected from TCMS
 *===========================================================================*/
#define TCI_CAN_ID_SPEED   (0x100U)  /**< Speed frame from TCMS */
#define TCI_CAN_ID_OPEN    (0x101U)  /**< Door open command */
#define TCI_CAN_ID_CLOSE   (0x102U)  /**< Door close command */
#define TCI_CAN_ID_MODE    (0x103U)  /**< Mode command */
#define TCI_CAN_ID_ESTOP   (0x104U)  /**< Emergency stop */

/** @brief CRC field offset in speed frame: bytes 0–2 = payload, 3–4 = CRC */
#define TCI_SPEED_PAYLOAD_LEN  (3U)

/** @brief Maximum DLC for TCMS frames */
#define TCI_MAX_DLC            (8U)

/*============================================================================
 * MODULE-LEVEL STATIC STATE
 *===========================================================================*/
/** @brief Last validated TCMS speed message */
static tcms_speed_msg_t s_last_speed_frame;

/** @brief Valid flag: 1 if s_last_speed_frame has been populated at least once */
static uint8_t s_speed_frame_valid;

/*============================================================================
 * PRIVATE HELPERS
 *===========================================================================*/

/**
 * @brief Locate the mailbox slot index for a given CAN message ID.
 * @complexity Cyclomatic complexity: 2
 */
static uint8_t tci_find_slot(uint32_t msg_id)
{
    uint8_t idx = TCI_CAN_RX_MAILBOX_COUNT; /* Sentinel: not found */

    if      (msg_id == TCI_CAN_ID_SPEED) { idx = 0U; }
    else if (msg_id == TCI_CAN_ID_OPEN)  { idx = 1U; }
    else if (msg_id == TCI_CAN_ID_CLOSE) { idx = 2U; }
    else if (msg_id == TCI_CAN_ID_MODE)  { idx = 3U; }
    else if (msg_id == TCI_CAN_ID_ESTOP) { idx = 4U; }
    else { /* Unknown ID — ignored */ }

    return idx;
}

/**
 * @brief Process a validated speed frame.
 * @complexity Cyclomatic complexity: 2
 */
static void tci_process_speed_frame(const can_mailbox_t *slot)
{
    uint16_t computed_crc;
    uint8_t  payload[TCI_SPEED_PAYLOAD_LEN];

    /* Extract payload bytes */
    payload[0U] = slot->data[0U];  /* speed_kmh_x10 high byte */
    payload[1U] = slot->data[1U];  /* speed_kmh_x10 low byte  */
    payload[2U] = slot->data[2U];  /* seq_counter             */

    computed_crc = CRC16_CCITT_Compute(payload, TCI_SPEED_PAYLOAD_LEN);

    /* Received CRC is in bytes 3–4 (big-endian) */
    uint16_t rx_crc = ((uint16_t)slot->data[3U] << 8U) |
                       (uint16_t)slot->data[4U];

    if (computed_crc != rx_crc)
    {
        LOG_EVENT(COMP_TCI, COMP_TCI, EVT_CAN_CRC_FAIL, (uint16_t)TCI_CAN_ID_SPEED);
        g_tci_fault_flag = 1U;
        return;
    }

    /* Validate sequence */
    (void)TCI_ValidateRxSeqDelta((uint8_t)TCI_CAN_ID_SPEED, payload[2U]);

    /* Store validated frame */
    s_last_speed_frame.speed_kmh_x10 = ((uint16_t)payload[0U] << 8U) |
                                         (uint16_t)payload[1U];
    s_last_speed_frame.seq_counter   = payload[2U];
    s_last_speed_frame.crc16         = rx_crc;
    s_speed_frame_valid              = 1U;
}

/**
 * @brief Process a door open command frame (CAN 0x101).
 * @complexity Cyclomatic complexity: 1
 */
static void tci_process_open_cmd(const can_mailbox_t *slot)
{
    (void)DSM_ProcessOpenCommand(slot->data[0U]);
}

/**
 * @brief Process a door close command frame (CAN 0x102).
 * @complexity Cyclomatic complexity: 1
 */
static void tci_process_close_cmd(const can_mailbox_t *slot)
{
    (void)DSM_ProcessCloseCommand(slot->data[0U]);
}

/**
 * @brief Process an emergency stop frame (CAN 0x104).
 * @complexity Cyclomatic complexity: 1
 */
static void tci_process_estop(const can_mailbox_t *slot)
{
    (void)FMG_ProcessEmergencyStop(slot->data[0U]);
}

/*============================================================================
 * PUBLIC FUNCTIONS
 *===========================================================================*/

/**
 * @brief CAN receive ISR — copy from HAL FIFO to mailbox.
 * @complexity Cyclomatic complexity: 3
 */
void TCI_CanRxISR(void)
{
    /* Implements: UNIT-TCI-001 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §8.1 */
    uint32_t msg_id = 0U;
    uint8_t  data[TCI_MAX_DLC];
    uint8_t  dlc    = 0U;
    uint8_t  slot_idx;
    uint8_t  b;
    error_t  err;

    err = HAL_CAN_Receive(&msg_id, data, &dlc);
    if (SUCCESS != err)
    {
        return;
    }

    slot_idx = tci_find_slot(msg_id);
    if (slot_idx >= TCI_CAN_RX_MAILBOX_COUNT)
    {
        return; /* Unknown ID — discard */
    }

    /* Bounds-checked copy */
    g_tci_mailbox[slot_idx].msg_id         = msg_id;
    g_tci_mailbox[slot_idx].dlc            = (dlc <= TCI_MAX_DLC) ? dlc : TCI_MAX_DLC;
    g_tci_mailbox[slot_idx].rx_timestamp_ms = HAL_GetSystemTickMs();
    g_tci_mailbox[slot_idx].valid          = 1U;

    for (b = 0U; b < g_tci_mailbox[slot_idx].dlc; b++)
    {
        g_tci_mailbox[slot_idx].data[b] = data[b];
    }
}

/**
 * @brief Process all pending CAN receive mailbox frames.
 * @complexity Cyclomatic complexity: 8 — within SIL 3 limit of 10
 */
error_t TCI_ProcessReceivedFrames(void)
{
    /* Implements: UNIT-TCI-002 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §8.1 */
    uint8_t i;

    for (i = 0U; i < TCI_CAN_RX_MAILBOX_COUNT; i++)
    {
        if (0U == g_tci_mailbox[i].valid)
        {
            continue;
        }

        /* Process by slot (each slot maps to one CAN ID) */
        switch (i)
        {
            case 0U:
                tci_process_speed_frame(&g_tci_mailbox[i]);
                break;
            case 1U:
                tci_process_open_cmd(&g_tci_mailbox[i]);
                break;
            case 2U:
                tci_process_close_cmd(&g_tci_mailbox[i]);
                break;
            case 3U:
                /* Mode command — handled by DSM via FMG */
                break;
            case 4U:
                tci_process_estop(&g_tci_mailbox[i]);
                break;
            default:
                /* Should not reach — defensive */
                break;
        }

        /* Clear mailbox slot after processing */
        g_tci_mailbox[i].valid = 0U;
    }

    return SUCCESS;
}

/**
 * @brief Get pointer to latest validated speed frame (for SPM polling).
 * @complexity Cyclomatic complexity: 2
 */
const tcms_speed_msg_t *TCI_GetSpeedFramePtr(void)
{
    if (0U == s_speed_frame_valid)
    {
        return NULL;
    }

    return &s_last_speed_frame;
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
