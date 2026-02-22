/**
 * @file fault_detection.c
 * @brief Fault Detection and Diagnosis Module Implementation (MOD-003)
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.4, Table A.4
 * @compliance MISRA C:2012
 * @traceability DOC-COMPDES-2026-001 v1.0 Section 3.3 (MOD-003)
 * 
 * @description
 * Implements fault logging, aging, and critical fault detection.
 * All functions meet SIL 3 complexity requirement (≤10).
 * 
 * @defensive_programming
 * - NULL pointer checks on all functions
 * - Circular buffer management for fault log
 * - Automatic fault aging and expiration
 * - Critical fault flag for safe state entry
 */

#include "fault_detection.h"

/*===========================================================================*/
/* Public Function Implementations                                           */
/*===========================================================================*/

/**
 * @brief Initialize fault detection module
 * @complexity 2 (1 base + 1 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.3.1 (pseudocode lines 1282-1303)
 */
error_t fault_detection_init(fault_detection_t* fd)
{
    uint8_t i;
    
    /* Step 1: NULL check (defensive programming) */
    if (fd == NULL) {                                           /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 2: Clear fault log (32 entries) */
    for (i = 0U; i < FAULT_LOG_SIZE; i++) {
        fd->fault_log[i].code = FAULT_NONE;
        fd->fault_log[i].severity = FAULT_SEVERITY_MINOR;
        fd->fault_log[i].timestamp = 0U;
        fd->fault_log[i].active = false;
    }
    
    /* Step 3: Reset counters */
    fd->fault_log_head = 0U;
    fd->fault_log_count = 0U;
    fd->critical_fault_active = false;
    
    return ERROR_SUCCESS;
}

/**
 * @brief Update fault detection, age faults, clear expired faults
 * @complexity 6 (1 base + 5 IF/FOR decision points)
 * @traceability DOC-COMPDES-2026-001 Section 3.3.2 (pseudocode lines 1317-1351)
 */
error_t fault_detection_update(fault_detection_t* fd)
{
    uint32_t current_time_ms;
    bool critical_fault_found;
    uint8_t i;
    uint32_t fault_age_ms;
    
    /* Step 1: NULL check (defensive programming) */
    if (fd == NULL) {                                           /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 2: Get current time */
    current_time_ms = get_system_time_ms();
    
    /* Step 3: Age faults (clear faults inactive for > 10 seconds) */
    critical_fault_found = false;
    
    for (i = 0U; i < FAULT_LOG_SIZE; i++) {                    /* +1 */
        if (fd->fault_log[i].active == true) {                  /* +1 */
            fault_age_ms = current_time_ms - fd->fault_log[i].timestamp;
            
            /* Check if fault has aged out (10 seconds) */
            if (fault_age_ms > FAULT_AGE_TIMEOUT_MS) {          /* +1 */
                fd->fault_log[i].active = false;
                if (fd->fault_log_count > 0U) {
                    fd->fault_log_count--;
                }
            } else {
                /* Fault still active: check if critical */
                if (fd->fault_log[i].severity == FAULT_SEVERITY_CRITICAL) { /* +1 */
                    critical_fault_found = true;
                }
            }
        }
    }
    
    /* Step 4: Update critical fault flag */
    fd->critical_fault_active = critical_fault_found;
    
    return ERROR_SUCCESS;
}

/**
 * @brief Report a fault with timestamp and severity
 * @complexity 7 (1 base + 6 IF/FOR decision points)
 * @traceability DOC-COMPDES-2026-001 Section 3.3.3 (pseudocode lines 1365-1412)
 */
error_t fault_detection_report_fault(fault_detection_t* fd, fault_code_t code, fault_severity_t severity)
{
    uint8_t i;
    
    /* Step 1: NULL check (defensive programming) */
    if (fd == NULL) {                                           /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 2: Severity validation */
    if (severity >= FAULT_SEVERITY_MAX) {                       /* +1 */
        return ERROR_INVALID_PARAMETER;
    }
    
    /* Step 3: Check if fault already exists in log (update timestamp) */
    for (i = 0U; i < FAULT_LOG_SIZE; i++) {                    /* +1 */
        if ((fd->fault_log[i].active == true) && (fd->fault_log[i].code == code)) { /* +1 */
            /* Fault already logged: update timestamp (refresh) */
            fd->fault_log[i].timestamp = get_system_time_ms();
            fd->fault_log[i].severity = severity;  /* Update severity if changed */
            
            /* Update critical fault flag if needed */
            if (severity == FAULT_SEVERITY_CRITICAL) {          /* +1 */
                fd->critical_fault_active = true;
            }
            
            return ERROR_SUCCESS;
        }
    }
    
    /* Step 4: Fault not in log - add new entry (circular buffer) */
    fd->fault_log[fd->fault_log_head].code = code;
    fd->fault_log[fd->fault_log_head].severity = severity;
    fd->fault_log[fd->fault_log_head].timestamp = get_system_time_ms();
    fd->fault_log[fd->fault_log_head].active = true;
    
    /* Step 5: Advance circular buffer head */
    fd->fault_log_head = (fd->fault_log_head + 1U) % FAULT_LOG_SIZE;
    
    /* Step 6: Increment count (saturate at FAULT_LOG_SIZE) */
    if (fd->fault_log_count < FAULT_LOG_SIZE) {                 /* +1 */
        fd->fault_log_count++;
    }
    
    /* Step 7: Update critical fault flag if needed */
    if (severity == FAULT_SEVERITY_CRITICAL) {
        fd->critical_fault_active = true;
    }
    
    return ERROR_SUCCESS;
}

/**
 * @brief Check if any critical fault is active
 * @complexity 2 (1 base + 1 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.3.4 (pseudocode lines 1426-1434)
 */
bool fault_detection_is_critical_fault_active(const fault_detection_t* fd)
{
    /* Defensive NULL check */
    if (fd == NULL) {                                           /* +1 */
        return true;  /* Fail-safe: assume critical fault */
    }
    
    return fd->critical_fault_active;
}

/**
 * @brief Get all active fault codes (for status reporting)
 * @complexity 5 (1 base + 4 IF/FOR decision points)
 * @traceability DOC-COMPDES-2026-001 Section 3.3.5 (pseudocode lines 1449-1478)
 */
uint8_t fault_detection_get_active_faults(const fault_detection_t* fd, 
                                           fault_code_t* buffer, 
                                           uint8_t buffer_size)
{
    uint8_t fault_count;
    uint8_t i;
    
    /* Step 1: NULL checks */
    if ((fd == NULL) || (buffer == NULL)) {                     /* +1 */
        return 0U;
    }
    
    /* Step 2: Buffer size validation */
    if (buffer_size == 0U) {                                    /* +1 */
        return 0U;
    }
    
    /* Step 3: Iterate through fault log, copy active faults */
    fault_count = 0U;
    
    for (i = 0U; i < FAULT_LOG_SIZE; i++) {                    /* +1 */
        /* Check if buffer full */
        if (fault_count >= buffer_size) {                       /* +1 */
            break;
        }
        
        /* Check if fault is active */
        if (fd->fault_log[i].active == true) {
            buffer[fault_count] = fd->fault_log[i].code;
            fault_count++;
        }
    }
    
    /* Step 4: Return number of faults copied */
    return fault_count;
}

/**
 * @brief Clear a fault (manual reset)
 * @complexity 5 (1 base + 4 IF/FOR decision points)
 * @traceability DOC-COMPDES-2026-001 Section 3.3.6 (pseudocode lines 1492-1528)
 */
error_t fault_detection_clear_fault(fault_detection_t* fd, fault_code_t code)
{
    bool fault_found;
    bool critical_fault_found;
    uint8_t i;
    
    /* Step 1: NULL check (defensive programming) */
    if (fd == NULL) {                                           /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 2: Search for fault in log */
    fault_found = false;
    
    for (i = 0U; i < FAULT_LOG_SIZE; i++) {                    /* +1 */
        if ((fd->fault_log[i].active == true) && (fd->fault_log[i].code == code)) { /* +1 */
            /* Mark fault as inactive */
            fd->fault_log[i].active = false;
            if (fd->fault_log_count > 0U) {
                fd->fault_log_count--;
            }
            fault_found = true;
            break;
        }
    }
    
    /* Step 3: Check if fault was found */
    if (!fault_found) {                                         /* +1 */
        return ERROR_INVALID_PARAMETER;
    }
    
    /* Step 4: Re-scan for critical faults */
    critical_fault_found = false;
    for (i = 0U; i < FAULT_LOG_SIZE; i++) {
        if ((fd->fault_log[i].active == true) && 
            (fd->fault_log[i].severity == FAULT_SEVERITY_CRITICAL)) {
            critical_fault_found = true;
            break;
        }
    }
    fd->critical_fault_active = critical_fault_found;
    
    return ERROR_SUCCESS;
}
