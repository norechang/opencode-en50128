/**
 * @file    dgn.h
 * @brief   Diagnostics (DGN) public interface for TDC
 * @details Circular-buffer event log, SPI Flash deferred write, and
 *          diagnostic serial port (read-only in Normal mode).
 *
 * @project TDC (Train Door Control System)
 * @module  DGN (Diagnostics) — COMP-007
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety
 * SIL Level: 1 (non-safety — diagnostic only)
 * Safety Requirements: REQ-FUN-018
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §9
 */

#ifndef DGN_H
#define DGN_H

#include <stdint.h>
#include "tdc_types.h"

/**
 * @brief Initialise DGN module — clear circular buffer, reset write pointer.
 * @return error_t SUCCESS
 * @note   Complexity: 1
 */
error_t DGN_Init(void);

/**
 * @brief 20 ms cycle entry — flush pending log entries to SPI Flash.
 * @note   Complexity: 2
 */
void DGN_RunCycle(void);

/**
 * @brief Write an event to the circular event log.
 * @details Thread-safe for single-writer contexts (atomic index increment).
 *          Overwrites oldest entry when log is full (circular).
 *          CRC-16-CCITT is computed over the entry (excluding crc16 field).
 * @param[in] source_comp Source component ID (COMP_xxx constant)
 * @param[in] event_code  Event code (EVT_xxx constant)
 * @param[in] data        Event-specific data payload
 * @return error_t SUCCESS
 * @note   Complexity: 3
 */
error_t DGN_LogEvent(uint8_t source_comp, uint8_t event_code, uint16_t data);

/**
 * @brief Read one event from the log by index.
 * @param[in]  index     Log index (0–MAX_LOG_ENTRIES-1)
 * @param[out] entry_out Pointer to output entry structure (must not be NULL)
 * @return error_t SUCCESS, ERR_NULL_PTR, ERR_RANGE
 * @note   Complexity: 3
 */
error_t DGN_ReadEvent(uint16_t index, event_log_entry_t *entry_out);

/**
 * @brief Get the current number of valid log entries.
 * @return uint16_t Entry count (0–MAX_LOG_ENTRIES)
 * @note   Complexity: 1
 */
uint16_t DGN_GetLogCount(void);

/**
 * @brief Flush pending log entries to SPI Flash storage (deferred write).
 * @return error_t SUCCESS, ERR_TIMEOUT, ERR_HW_FAULT
 * @note   Complexity: 5
 */
error_t DGN_FlushToFlash(void);

/**
 * @brief Service the diagnostic serial port (read-only in Normal mode).
 * @param[in] op_mode Current operational mode (used for access control)
 * @return error_t SUCCESS
 * @note   Complexity: 4
 */
error_t DGN_ServiceDiagPort(op_mode_t op_mode);

/**
 * @brief Convenience macro — log an event from any component.
 * @note  Expands to DGN_LogEvent(...); return value intentionally discarded
 *        for non-safety DGN (SIL 1 — logging must not block safety execution).
 */
#define LOG_EVENT(module_unused, src, code, dat) \
    (void)DGN_LogEvent((uint8_t)(src), (uint8_t)(code), (uint16_t)(dat))

#endif /* DGN_H */

/*============================================================================
 * END OF FILE
 *===========================================================================*/
