/**
 * @file error_types.h
 * @brief Error code definitions for Train Door Control System
 * @standard EN 50128:2011
 * @sil 3
 * @misra MISRA C:2012 compliant
 */

#ifndef ERROR_TYPES_H
#define ERROR_TYPES_H

/**
 * @brief Error codes for system-wide error handling
 * 
 * All functions return error_t to enable comprehensive error checking.
 * SUCCESS (0) indicates normal operation.
 * All other values indicate specific error conditions.
 */
typedef enum {
    SUCCESS = 0,                    /**< Operation completed successfully */
    ERROR_NULL_POINTER = 1,         /**< NULL pointer passed as argument */
    ERROR_INVALID_PARAMETER = 2,    /**< Parameter out of valid range */
    ERROR_OUT_OF_RANGE = 3,         /**< Value exceeds defined limits */
    ERROR_TIMEOUT = 4,              /**< Operation timed out */
    ERROR_HARDWARE_FAULT = 5,       /**< Hardware failure detected */
    ERROR_SENSOR_FAULT = 6,         /**< Sensor reading invalid or missing */
    ERROR_INVALID_STATE = 7,        /**< Operation not permitted in current state */
    ERROR_SPEED_NOT_ZERO = 8,       /**< Speed must be zero for this operation */
    ERROR_DOOR_NOT_CLOSED = 9,      /**< Door is not fully closed */
    ERROR_DOOR_NOT_LOCKED = 10,     /**< Door lock not engaged */
    ERROR_SAFETY_INTERLOCK = 11,    /**< Safety interlock prevents operation */
    ERROR_REDUNDANCY_FAULT = 12     /**< Redundant check failed */
} error_t;

#endif /* ERROR_TYPES_H */
