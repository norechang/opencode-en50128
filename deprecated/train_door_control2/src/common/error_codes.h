/**
 * @file error_codes.h
 * @brief Error code definitions for train door control system
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.4
 * @compliance MISRA C:2012
 * @traceability DOC-COMPDES-2026-001 v1.0 Section 3 (Common)
 * 
 * @description
 * Provides error code enumeration used by all modules.
 * All functions return error_t for consistent error handling.
 */

#ifndef ERROR_CODES_H
#define ERROR_CODES_H

#include <stdint.h>

/*===========================================================================*/
/* Error Code Enumeration                                                    */
/*===========================================================================*/

/**
 * @brief Error code type
 * @compliance MISRA C:2012 Rule 8.2 (complete function types)
 */
typedef enum {
    ERROR_SUCCESS = 0U,                  /**< Operation successful */
    ERROR_NULL_POINTER = 1U,             /**< NULL pointer parameter */
    ERROR_INVALID_PARAMETER = 2U,        /**< Invalid parameter value */
    ERROR_OUT_OF_RANGE = 3U,             /**< Parameter out of valid range */
    ERROR_TIMEOUT = 4U,                  /**< Operation timeout */
    ERROR_HARDWARE_FAILURE = 5U,         /**< Hardware fault detected */
    ERROR_NOT_INITIALIZED = 6U,          /**< Module not initialized */
    ERROR_BUFFER_FULL = 7U,              /**< Buffer overflow */
    ERROR_NO_DATA = 8U,                  /**< No data available */
    ERROR_COMMUNICATION_FAILURE = 9U,    /**< Communication error */
    ERROR_INVALID_STATE = 10U,           /**< Invalid state for operation */
    ERROR_INVALID_DATA = 11U             /**< Invalid data received */
} error_t;

#endif /* ERROR_CODES_H */
