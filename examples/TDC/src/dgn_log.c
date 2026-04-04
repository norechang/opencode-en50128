/**
 * @file    dgn_log.c
 * @brief   DGN circular event log — write, read, and count operations.
 * @details Implements DGN_Init, DGN_LogEvent, DGN_ReadEvent, DGN_GetLogCount.
 *          Uses a static circular buffer of MAX_LOG_ENTRIES event_log_entry_t
 *          elements.  All entries are protected by CRC-16-CCITT.
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
 * - SCDS DOC-COMPDES-2026-001 §9.1
 */

/* Implements: REQ-FUN-018 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §9.1 (COMP-007) */
/* SIL: 1 */

#include <stdint.h>
#include <stddef.h>

#include "dgn.h"
#include "hal.h"
#include "tdc_types.h"

/*============================================================================
 * GLOBAL SHARED STATE — Owned here, used by dgn_flash.c and dgn_port.c
 *===========================================================================*/

/** @brief Circular log buffer */
event_log_entry_t g_dgn_log[MAX_LOG_ENTRIES];

/** @brief Next write index into the circular buffer */
uint16_t g_dgn_write_idx;

/** @brief Total number of entries written (capped at MAX_LOG_ENTRIES when full) */
uint16_t g_dgn_entry_count;

/** @brief Flush-pending watermark: entries above this index need flushing */
uint16_t g_dgn_flush_pending_idx;

/*============================================================================
 * PRIVATE HELPERS
 *===========================================================================*/

/**
 * @brief Compute CRC-16 over an event log entry (excluding crc16 field).
 * @complexity Cyclomatic complexity: 1
 */
static uint16_t dgn_entry_crc(const event_log_entry_t *entry)
{
    /* Compute CRC over first 8 bytes: timestamp(4) + source(1) + code(1) + data(2) */
    uint8_t buf[8];

    buf[0U] = (uint8_t)(entry->timestamp_ms >> 24U);
    buf[1U] = (uint8_t)(entry->timestamp_ms >> 16U);
    buf[2U] = (uint8_t)(entry->timestamp_ms >>  8U);
    buf[3U] = (uint8_t)(entry->timestamp_ms        );
    buf[4U] = entry->source_comp;
    buf[5U] = entry->event_code;
    buf[6U] = (uint8_t)(entry->data >> 8U);
    buf[7U] = (uint8_t)(entry->data       );

    return CRC16_CCITT_Compute(buf, 8U);
}

/*============================================================================
 * PUBLIC FUNCTIONS
 *===========================================================================*/

/**
 * @brief Initialise DGN module.
 * @complexity Cyclomatic complexity: 2
 */
error_t DGN_Init(void)
{
    uint16_t i;

    for (i = 0U; i < MAX_LOG_ENTRIES; i++)
    {
        g_dgn_log[i].timestamp_ms = 0U;
        g_dgn_log[i].source_comp  = 0U;
        g_dgn_log[i].event_code   = 0U;
        g_dgn_log[i].data         = 0U;
        g_dgn_log[i].crc16        = 0U;
    }

    g_dgn_write_idx        = 0U;
    g_dgn_entry_count      = 0U;
    g_dgn_flush_pending_idx = 0U;

    return SUCCESS;
}

/**
 * @brief Write an event to the circular event log.
 * @complexity Cyclomatic complexity: 3
 */
error_t DGN_LogEvent(uint8_t source_comp, uint8_t event_code, uint16_t data)
{
    event_log_entry_t *slot;

    /* Write to current slot (circular wrap) */
    slot = &g_dgn_log[g_dgn_write_idx];

    slot->timestamp_ms = HAL_GetSystemTickMs();
    slot->source_comp  = source_comp;
    slot->event_code   = event_code;
    slot->data         = data;
    slot->crc16        = dgn_entry_crc(slot);

    /* Advance write index (wrap modulo MAX_LOG_ENTRIES) */
    g_dgn_write_idx = (uint16_t)((g_dgn_write_idx + 1U) % MAX_LOG_ENTRIES);

    if (g_dgn_entry_count < MAX_LOG_ENTRIES)
    {
        g_dgn_entry_count++;
    }

    return SUCCESS;
}

/**
 * @brief Read one event from the log by index.
 * @complexity Cyclomatic complexity: 3
 */
error_t DGN_ReadEvent(uint16_t index, event_log_entry_t *entry_out)
{
    if (NULL == entry_out)
    {
        return ERR_NULL_PTR;
    }

    if (index >= g_dgn_entry_count)
    {
        return ERR_RANGE;
    }

    *entry_out = g_dgn_log[index];
    return SUCCESS;
}

/**
 * @brief Get the current number of valid log entries.
 * @complexity Cyclomatic complexity: 1
 */
uint16_t DGN_GetLogCount(void)
{
    return g_dgn_entry_count;
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
