/**
 * @file communication_hal.h
 * @brief Hardware Abstraction Layer for Communication (MOD-008)
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.4, Table A.4
 * @compliance MISRA C:2012
 * @traceability DOC-COMPDES-2026-001 v1.0 Section 3.8 (MOD-008)
 * 
 * @description
 * Provides hardware abstraction for CAN bus (primary) and UART (diagnostic).
 * Maximum cyclomatic complexity: 7 (SIL 3 target: ≤10).
 * 
 * @memory_footprint
 * - communication_hal_state_t: 17 bytes
 * - can_message_t: 13 bytes (defined in sensor_hal.h, used here)
 * - Total: 30 bytes
 */

#ifndef COMMUNICATION_HAL_H
#define COMMUNICATION_HAL_H

#include "../common/types.h"
#include "../common/error_codes.h"
#include "../sensor_hal/sensor_hal.h"  /* For can_message_t */

/*===========================================================================*/
/* Constants                                                                 */
/*===========================================================================*/

/** CAN bus configuration */
#define CAN_BAUD_RATE        (500000U)      /**< 500 kbps */
#define CAN_MAX_DLC          (8U)           /**< Max CAN data bytes */
#define CAN_ID_MAX           (0x7FFU)       /**< 11-bit CAN ID maximum */

/** UART configuration */
#define UART_BAUD_RATE       (115200U)      /**< 115200 baud */

/*===========================================================================*/
/* Data Structures                                                           */
/*===========================================================================*/

/**
 * @brief Communication HAL internal state structure
 * @compliance MISRA C:2012 Rule 8.2 (complete type definitions)
 */
typedef struct {
    uint32_t can_tx_count;              /**< CAN messages transmitted */
    uint32_t can_rx_count;              /**< CAN messages received */
    uint32_t can_tx_error_count;        /**< CAN TX errors */
    uint32_t can_rx_error_count;        /**< CAN RX errors */
    bool initialized;                   /**< Initialization flag */
} communication_hal_state_t;

/*===========================================================================*/
/* Public Function Prototypes                                                */
/*===========================================================================*/

/**
 * @brief Initialize CAN controller and UART
 * @return ERROR_SUCCESS on success, ERROR_HARDWARE_FAILURE on init failure
 * @complexity 4 (1 base + 3 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.8.2
 */
error_t communication_hal_init(void);

/**
 * @brief Send CAN message with validation
 * @param[in] msg Pointer to CAN message structure
 * @return ERROR_SUCCESS on success
 *         ERROR_NOT_INITIALIZED if not initialized
 *         ERROR_NULL_POINTER if msg is NULL
 *         ERROR_INVALID_PARAMETER if CAN ID or DLC invalid
 *         (other errors from CAN driver)
 * @complexity 6 (1 base + 5 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.8.3
 */
error_t communication_hal_can_send(const can_message_t* msg);

/**
 * @brief Receive CAN message (non-blocking) with validation
 * @param[out] msg Pointer to store received CAN message
 * @return ERROR_SUCCESS on success
 *         ERROR_NOT_INITIALIZED if not initialized
 *         ERROR_NULL_POINTER if msg is NULL
 *         ERROR_NO_DATA if no message available
 *         ERROR_INVALID_DATA if received message invalid
 *         (other errors from CAN driver)
 * @complexity 7 (1 base + 6 IF/OR)
 * @traceability DOC-COMPDES-2026-001 Section 3.8.4
 */
error_t communication_hal_can_receive(can_message_t* msg);

/**
 * @brief Check if CAN message available in RX buffer
 * @return true if message available, false otherwise
 * @complexity 2 (1 base + 1 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.8.5
 * @note Simple wrapper around hardware function
 */
bool communication_hal_can_is_rx_ready(void);

/**
 * @brief Send UART data (diagnostic console - non-safety-critical)
 * @param[in] data Pointer to data buffer to transmit
 * @param[in] length Number of bytes to transmit
 * @return ERROR_SUCCESS on success
 *         ERROR_NOT_INITIALIZED if not initialized
 *         ERROR_INVALID_PARAMETER if data is NULL or length is 0
 *         (other errors from UART driver)
 * @complexity 4 (1 base + 3 IF/OR)
 * @traceability DOC-COMPDES-2026-001 Section 3.8.6
 */
error_t communication_hal_uart_send(const uint8_t* data, uint16_t length);

/**
 * @brief Receive UART data (diagnostic console - non-safety-critical)
 * @param[out] data Pointer to buffer to store received data
 * @param[out] length Pointer to store number of bytes received
 * @return ERROR_SUCCESS on success
 *         ERROR_NOT_INITIALIZED if not initialized
 *         ERROR_NULL_POINTER if any pointer is NULL
 *         ERROR_NO_DATA if no data available
 *         (other errors from UART driver)
 * @complexity 5 (1 base + 4 IF/OR)
 * @traceability DOC-COMPDES-2026-001 Section 3.8.7
 */
error_t communication_hal_uart_receive(uint8_t* data, uint16_t* length);

#endif /* COMMUNICATION_HAL_H */
