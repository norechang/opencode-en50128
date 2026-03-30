/**
 * @file communication_hal.c
 * @brief Hardware Abstraction Layer for Communication Implementation (MOD-008)
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.4, Table A.4
 * @compliance MISRA C:2012
 * @traceability DOC-COMPDES-2026-001 v1.0 Section 3.8 (MOD-008)
 * 
 * @description
 * Implements CAN bus and UART communication with full validation and error tracking.
 * All functions meet SIL 3 complexity requirement (≤10).
 * 
 * @defensive_programming
 * - All public functions validate parameters
 * - Initialization state checked before operation
 * - CAN message validation (ID, DLC ranges)
 * - Error counters for diagnostics
 * - NULL pointer checks on all parameters
 */

#include "communication_hal.h"

/*===========================================================================*/
/* Hardware Driver Stubs (to be replaced with actual driver in integration) */
/*===========================================================================*/

/* CAN Controller Modes */
#define CAN_MODE_NORMAL              (0U)

/* CAN Filter Configuration */
#define CAN_FILTER_ACCEPT_ALL        (0xFFFFFFFFU)

/* UART Configuration */
#define UART_8N1                     (0U)  /* 8 data bits, no parity, 1 stop bit */

/* Hardware function stubs (platform-specific, to be linked) */
extern error_t can_controller_init(uint32_t baud_rate, uint8_t mode);
extern error_t can_filter_config(uint32_t filter_mask);
extern error_t can_transmit(uint32_t id, const uint8_t* data, uint8_t dlc);
extern error_t can_receive(uint32_t* id, uint8_t* data, uint8_t* dlc);
extern bool can_is_rx_ready(void);
extern error_t uart_init(uint32_t baud_rate, uint8_t config);
extern error_t uart_transmit(const uint8_t* data, uint16_t length);
extern error_t uart_receive(uint8_t* data, uint16_t* length);
extern bool uart_is_rx_ready(void);

/*===========================================================================*/
/* Module State                                                              */
/*===========================================================================*/

/**
 * @brief Module state (static allocation)
 * @compliance EN 50128 SIL 3: Static memory allocation only
 */
static communication_hal_state_t g_communication_hal;

/*===========================================================================*/
/* Public Function Implementations                                           */
/*===========================================================================*/

/**
 * @brief Initialize CAN controller and UART
 * @complexity 4 (1 base + 3 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.8.2 (pseudocode lines 2844-2871)
 */
error_t communication_hal_init(void)
{
    error_t err;
    
    /* Step 1: Initialize CAN controller (500 kbps, standard 11-bit IDs) */
    err = can_controller_init(CAN_BAUD_RATE, CAN_MODE_NORMAL);
    if (err != ERROR_SUCCESS) {                                 /* +1 */
        return ERROR_HARDWARE_FAILURE;
    }
    
    /* Step 2: Configure CAN filters (accept all IDs for now) */
    err = can_filter_config(CAN_FILTER_ACCEPT_ALL);
    if (err != ERROR_SUCCESS) {                                 /* +1 */
        return ERROR_HARDWARE_FAILURE;
    }
    
    /* Step 3: Initialize UART for diagnostic console */
    err = uart_init(UART_BAUD_RATE, UART_8N1);
    if (err != ERROR_SUCCESS) {                                 /* +1 */
        return ERROR_HARDWARE_FAILURE;
    }
    
    /* Step 4: Initialize internal state */
    g_communication_hal.can_tx_count = 0U;
    g_communication_hal.can_rx_count = 0U;
    g_communication_hal.can_tx_error_count = 0U;
    g_communication_hal.can_rx_error_count = 0U;
    g_communication_hal.initialized = true;
    
    return ERROR_SUCCESS;
}

/**
 * @brief Send CAN message with validation
 * @complexity 6 (1 base + 5 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.8.3 (pseudocode lines 2890-2921)
 */
error_t communication_hal_can_send(const can_message_t* msg)
{
    error_t err;
    
    /* Step 1: Defensive programming - Check initialization */
    if (g_communication_hal.initialized == false) {             /* +1 */
        return ERROR_NOT_INITIALIZED;
    }
    
    /* Step 2: Defensive programming - NULL check */
    if (msg == NULL) {                                          /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 3: Defensive programming - Validate CAN message ID */
    if (msg->id > CAN_ID_MAX) {                                 /* +1 */
        return ERROR_INVALID_PARAMETER;
    }
    
    /* Step 4: Defensive programming - Validate CAN message DLC */
    if (msg->dlc > CAN_MAX_DLC) {                               /* +1 */
        return ERROR_INVALID_PARAMETER;
    }
    
    /* Step 5: Transmit CAN message */
    err = can_transmit(msg->id, msg->data, msg->dlc);
    if (err != ERROR_SUCCESS) {                                 /* +1 */
        g_communication_hal.can_tx_error_count++;
        return err;
    }
    
    /* Step 6: Update statistics */
    g_communication_hal.can_tx_count++;
    
    return ERROR_SUCCESS;
}

/**
 * @brief Receive CAN message (non-blocking) with validation
 * @complexity 7 (1 base + 6 IF/OR decision points)
 * @traceability DOC-COMPDES-2026-001 Section 3.8.4 (pseudocode lines 2940-2973)
 */
error_t communication_hal_can_receive(can_message_t* msg)
{
    error_t err;
    
    /* Step 1: Defensive programming - Check initialization */
    if (g_communication_hal.initialized == false) {             /* +1 */
        return ERROR_NOT_INITIALIZED;
    }
    
    /* Step 2: Defensive programming - NULL check */
    if (msg == NULL) {                                          /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 3: Check if CAN message available */
    if (can_is_rx_ready() == false) {                           /* +1 */
        return ERROR_NO_DATA;
    }
    
    /* Step 4: Receive CAN message */
    err = can_receive(&msg->id, msg->data, &msg->dlc);
    if (err != ERROR_SUCCESS) {                                 /* +1 */
        g_communication_hal.can_rx_error_count++;
        return err;
    }
    
    /* Step 5: Validate received message parameters */
    if ((msg->id > CAN_ID_MAX) || (msg->dlc > CAN_MAX_DLC)) {  /* +1 +1 */
        g_communication_hal.can_rx_error_count++;
        return ERROR_INVALID_DATA;
    }
    
    /* Step 6: Update statistics */
    g_communication_hal.can_rx_count++;
    
    return ERROR_SUCCESS;
}

/**
 * @brief Check if CAN message available in RX buffer
 * @complexity 2 (1 base + 1 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.8.5 (pseudocode lines 2992-2999)
 */
bool communication_hal_can_is_rx_ready(void)
{
    /* Check CAN RX buffer status */
    if (can_is_rx_ready() == true) {                            /* +1 */
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Send UART data (diagnostic console - non-safety-critical)
 * @complexity 4 (1 base + 3 IF/OR decision points)
 * @traceability DOC-COMPDES-2026-001 Section 3.8.6 (pseudocode lines 3018-3036)
 */
error_t communication_hal_uart_send(const uint8_t* data, uint16_t length)
{
    error_t err;
    
    /* Step 1: Defensive programming - Check initialization */
    if (g_communication_hal.initialized == false) {             /* +1 */
        return ERROR_NOT_INITIALIZED;
    }
    
    /* Step 2: Defensive programming - NULL check and length check */
    if ((data == NULL) || (length == 0U)) {                     /* +1 +1 */
        return ERROR_INVALID_PARAMETER;
    }
    
    /* Step 3: Transmit UART data */
    err = uart_transmit(data, length);
    if (err != ERROR_SUCCESS) {
        return err;
    }
    
    return ERROR_SUCCESS;
}

/**
 * @brief Receive UART data (diagnostic console - non-safety-critical)
 * @complexity 5 (1 base + 4 IF/OR decision points)
 * @traceability DOC-COMPDES-2026-001 Section 3.8.7 (pseudocode lines 3055-3078)
 */
error_t communication_hal_uart_receive(uint8_t* data, uint16_t* length)
{
    error_t err;
    
    /* Step 1: Defensive programming - Check initialization */
    if (g_communication_hal.initialized == false) {             /* +1 */
        return ERROR_NOT_INITIALIZED;
    }
    
    /* Step 2: Defensive programming - NULL checks */
    if ((data == NULL) || (length == NULL)) {                   /* +1 +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 3: Check if UART data available */
    if (uart_is_rx_ready() == false) {                          /* +1 */
        return ERROR_NO_DATA;
    }
    
    /* Step 4: Receive UART data */
    err = uart_receive(data, length);
    if (err != ERROR_SUCCESS) {
        return err;
    }
    
    return ERROR_SUCCESS;
}
