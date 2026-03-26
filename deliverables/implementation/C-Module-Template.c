/**
 * @file    module_name.c
 * @brief   Brief description of module functionality
 * @details Detailed description of module purpose, algorithms, and usage
 * 
 * @project [Project Name]
 * @module  [Module Name]
 * @author  [Author Name]
 * @date    [YYYY-MM-DD]
 * @version [X.Y]
 * 
 * @copyright Copyright (c) [YYYY] [Company Name]. All rights reserved.
 * 
 * @safety
 * SIL Level: [0/1/2/3/4]
 * Safety Requirements: [List safety-related requirements this module implements]
 * 
 * @requirements
 * This module implements the following requirements:
 * - REQ-FUNC-XXX: [Requirement description]
 * - REQ-SAFE-XXX: [Requirement description]
 * 
 * @misra_compliance
 * MISRA C:2012 Compliance:
 * - All mandatory rules: Compliant
 * - All required rules: Compliant (or deviations documented below)
 * - Deviations: [List any MISRA deviations with justification]
 * 
 * @en50128_references
 * - EN 50128:2011 Section 7.4 (Software Design and Implementation)
 * - EN 50128:2011 Table A.4 (Implementation techniques)
 */

/*============================================================================
 * INCLUDES
 *===========================================================================*/

/* Standard library includes (MISRA C:2012 permits standard library) */
#include <stdint.h>     /* For fixed-width integer types (MANDATORY SIL 2+) */
#include <stdbool.h>    /* For bool type */
#include <stddef.h>     /* For NULL, size_t */

/* Project-specific includes */
#include "module_name.h"        /* Module header (always first) */
#include "other_module.h"       /* Other module interfaces */

/*============================================================================
 * PREPROCESSOR DEFINITIONS
 *===========================================================================*/

/**
 * @brief Module version string
 */
#define MODULE_VERSION "1.0"

/**
 * @brief Maximum buffer size (example)
 * @note Must be power of 2 for efficient masking
 */
#define MAX_BUFFER_SIZE (256U)

/**
 * @brief Error code base for this module
 */
#define MODULE_ERROR_BASE (0x1000U)

/*============================================================================
 * TYPE DEFINITIONS
 *===========================================================================*/

/**
 * @brief Internal state structure for module
 * @note All fields use fixed-width types (MISRA C, SIL 2+ requirement)
 */
typedef struct {
    uint32_t state;             /**< Current state */
    uint16_t counter;           /**< Event counter */
    bool     initialized;       /**< Initialization flag */
    uint8_t  reserved;          /**< Reserved for alignment */
} module_state_t;

/*============================================================================
 * STATIC (PRIVATE) VARIABLES
 *===========================================================================*/

/**
 * @brief Module state (static allocation, MANDATORY for SIL 2+)
 * @note No dynamic allocation permitted (EN 50128 SIL 2+)
 */
static module_state_t g_module_state = {
    .state = 0U,
    .counter = 0U,
    .initialized = false,
    .reserved = 0U
};

/**
 * @brief Internal buffer (static allocation)
 */
static uint8_t g_buffer[MAX_BUFFER_SIZE];

/*============================================================================
 * STATIC (PRIVATE) FUNCTION PROTOTYPES
 *===========================================================================*/

/**
 * @brief Internal helper function
 * @param[in] param1 Description of parameter
 * @return Error code (0 = success)
 * @note Static function, not exposed in header
 */
static error_t internal_helper(uint32_t param1);

/**
 * @brief Validate input parameters
 * @param[in] ptr Pointer to validate (NULL check)
 * @param[in] value Value to validate (range check)
 * @return true if valid, false otherwise
 * @note Defensive programming (EN 50128 Table A.4, HR for SIL 3-4)
 */
static bool validate_params(const void *ptr, uint32_t value);

/*============================================================================
 * PUBLIC FUNCTION IMPLEMENTATIONS
 *===========================================================================*/

/**
 * @brief Initialize the module
 * @details This function initializes the module state and prepares it for use.
 *          Must be called before any other module functions.
 * 
 * @param[in] config Pointer to configuration structure (must not be NULL)
 * 
 * @return error_t Error code
 * @retval ERROR_SUCCESS Initialization successful
 * @retval ERROR_NULL_POINTER config is NULL
 * @retval ERROR_INVALID_CONFIG Configuration invalid
 * 
 * @pre Module must not already be initialized
 * @post Module is initialized and ready for use
 * 
 * @safety This function is safety-critical (SIL [X])
 * 
 * @complexity Cyclomatic complexity: [X] (Target: ≤10 for SIL 3-4, ≤15 for SIL 2)
 * 
 * @misra_compliance Compliant with MISRA C:2012
 */
error_t module_init(const module_config_t *config)
{
    error_t result = ERROR_SUCCESS;
    
    /* DEFENSIVE PROGRAMMING: NULL pointer check (MANDATORY SIL 2+) */
    if (NULL == config) {
        result = ERROR_NULL_POINTER;
    }
    /* Check if already initialized */
    else if (true == g_module_state.initialized) {
        result = ERROR_ALREADY_INITIALIZED;
    }
    /* Validate configuration parameters */
    else if (false == validate_params(config, config->value)) {
        result = ERROR_INVALID_CONFIG;
    }
    else {
        /* Initialize module state */
        g_module_state.state = 0U;
        g_module_state.counter = 0U;
        g_module_state.initialized = true;
        
        /* Initialize buffer to zero */
        for (uint16_t i = 0U; i < MAX_BUFFER_SIZE; i++) {
            g_buffer[i] = 0U;
        }
        
        result = ERROR_SUCCESS;
    }
    
    return result;
}

/**
 * @brief Process data through the module
 * @details This function processes input data and produces output data.
 * 
 * @param[in]  input_data  Pointer to input data (must not be NULL)
 * @param[in]  input_size  Size of input data in bytes (must be > 0)
 * @param[out] output_data Pointer to output buffer (must not be NULL)
 * @param[in]  output_size Size of output buffer in bytes
 * @param[out] bytes_written Pointer to variable receiving bytes written (may be NULL)
 * 
 * @return error_t Error code
 * @retval ERROR_SUCCESS Processing successful
 * @retval ERROR_NULL_POINTER input_data or output_data is NULL
 * @retval ERROR_INVALID_SIZE input_size is 0 or output_size too small
 * @retval ERROR_NOT_INITIALIZED Module not initialized
 * 
 * @pre Module must be initialized (module_init() called)
 * @pre input_data must point to valid memory
 * @pre output_data must point to valid memory
 * @post output_data contains processed data
 * @post *bytes_written contains number of bytes written (if not NULL)
 * 
 * @safety This function is safety-critical (SIL [X])
 * 
 * @complexity Cyclomatic complexity: [X] (Target: ≤10 for SIL 3-4)
 */
error_t module_process(const uint8_t *input_data, 
                        uint16_t input_size,
                        uint8_t *output_data,
                        uint16_t output_size,
                        uint16_t *bytes_written)
{
    error_t result = ERROR_SUCCESS;
    uint16_t processed = 0U;
    
    /* DEFENSIVE PROGRAMMING: Parameter validation (MANDATORY SIL 2+) */
    if (NULL == input_data) {
        result = ERROR_NULL_POINTER;
    }
    else if (NULL == output_data) {
        result = ERROR_NULL_POINTER;
    }
    else if (0U == input_size) {
        result = ERROR_INVALID_SIZE;
    }
    else if (output_size < input_size) {
        result = ERROR_BUFFER_TOO_SMALL;
    }
    /* Check module initialized */
    else if (false == g_module_state.initialized) {
        result = ERROR_NOT_INITIALIZED;
    }
    else {
        /* Process data (example: copy with transformation) */
        for (uint16_t i = 0U; i < input_size; i++) {
            /* Example processing: invert bits */
            output_data[i] = (uint8_t)(~input_data[i]);
            processed++;
        }
        
        /* Update module state */
        g_module_state.counter++;
        
        /* Return bytes written (if requested) */
        if (NULL != bytes_written) {
            *bytes_written = processed;
        }
        
        result = ERROR_SUCCESS;
    }
    
    return result;
}

/**
 * @brief Get module status
 * @details This function retrieves the current module status.
 * 
 * @param[out] status Pointer to status structure (must not be NULL)
 * 
 * @return error_t Error code
 * @retval ERROR_SUCCESS Status retrieved successfully
 * @retval ERROR_NULL_POINTER status is NULL
 * @retval ERROR_NOT_INITIALIZED Module not initialized
 * 
 * @pre Module must be initialized
 * @post *status contains current module status
 * 
 * @safety This function is non-critical
 * 
 * @complexity Cyclomatic complexity: 3
 */
error_t module_get_status(module_status_t *status)
{
    error_t result = ERROR_SUCCESS;
    
    /* DEFENSIVE PROGRAMMING: NULL pointer check */
    if (NULL == status) {
        result = ERROR_NULL_POINTER;
    }
    else if (false == g_module_state.initialized) {
        result = ERROR_NOT_INITIALIZED;
    }
    else {
        /* Populate status structure */
        status->state = g_module_state.state;
        status->counter = g_module_state.counter;
        status->initialized = g_module_state.initialized;
        
        result = ERROR_SUCCESS;
    }
    
    return result;
}

/**
 * @brief Deinitialize the module
 * @details This function deinitializes the module and releases resources.
 * 
 * @return error_t Error code
 * @retval ERROR_SUCCESS Deinitialization successful
 * @retval ERROR_NOT_INITIALIZED Module not initialized
 * 
 * @pre Module must be initialized
 * @post Module is deinitialized and cannot be used until reinitialized
 * 
 * @safety This function is safety-critical (SIL [X])
 * 
 * @complexity Cyclomatic complexity: 2
 */
error_t module_deinit(void)
{
    error_t result = ERROR_SUCCESS;
    
    /* Check module initialized */
    if (false == g_module_state.initialized) {
        result = ERROR_NOT_INITIALIZED;
    }
    else {
        /* Reset module state */
        g_module_state.state = 0U;
        g_module_state.counter = 0U;
        g_module_state.initialized = false;
        
        /* Clear sensitive data from buffer (security consideration) */
        for (uint16_t i = 0U; i < MAX_BUFFER_SIZE; i++) {
            g_buffer[i] = 0U;
        }
        
        result = ERROR_SUCCESS;
    }
    
    return result;
}

/*============================================================================
 * STATIC (PRIVATE) FUNCTION IMPLEMENTATIONS
 *===========================================================================*/

/**
 * @brief Internal helper function implementation
 * @details This is an internal helper function not exposed in the header.
 * 
 * @param[in] param1 Input parameter
 * 
 * @return error_t Error code
 * 
 * @complexity Cyclomatic complexity: 2
 */
static error_t internal_helper(uint32_t param1)
{
    error_t result = ERROR_SUCCESS;
    
    /* Validate parameter range */
    if (param1 > MAX_BUFFER_SIZE) {
        result = ERROR_INVALID_PARAMETER;
    }
    else {
        /* Perform helper operation */
        g_module_state.state = param1;
        result = ERROR_SUCCESS;
    }
    
    return result;
}

/**
 * @brief Validate input parameters (defensive programming)
 * @details This function validates input parameters for safety-critical operations.
 * 
 * @param[in] ptr Pointer to validate (NULL check)
 * @param[in] value Value to validate (range check)
 * 
 * @return bool Validation result
 * @retval true Parameters are valid
 * @retval false Parameters are invalid
 * 
 * @note This is a defensive programming measure (EN 50128 Table A.4, HR SIL 3-4)
 * 
 * @complexity Cyclomatic complexity: 3
 */
static bool validate_params(const void *ptr, uint32_t value)
{
    bool is_valid = false;
    
    /* NULL pointer check */
    if (NULL == ptr) {
        is_valid = false;
    }
    /* Range check (example: value must be in valid range) */
    else if (value > MAX_BUFFER_SIZE) {
        is_valid = false;
    }
    else {
        is_valid = true;
    }
    
    return is_valid;
}

/*============================================================================
 * UNIT TEST HOOKS (Conditional Compilation)
 *===========================================================================*/

#ifdef UNIT_TEST

/**
 * @brief Unit test hook to access internal state
 * @note Only available when compiled with UNIT_TEST defined
 * @return Pointer to module state (for testing only)
 */
module_state_t* test_get_module_state(void)
{
    return &g_module_state;
}

/**
 * @brief Unit test hook to reset module state
 * @note Only available when compiled with UNIT_TEST defined
 */
void test_reset_module_state(void)
{
    g_module_state.state = 0U;
    g_module_state.counter = 0U;
    g_module_state.initialized = false;
}

#endif /* UNIT_TEST */

/*============================================================================
 * END OF FILE
 *===========================================================================*/
