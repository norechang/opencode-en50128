/**
 * @file    module_name.h
 * @brief   Brief description of module interface
 * @details Detailed description of module public interface, usage, and API
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
 * This module interface implements the following requirements:
 * - REQ-FUNC-XXX: [Requirement description]
 * - REQ-SAFE-XXX: [Requirement description]
 * 
 * @misra_compliance
 * MISRA C:2012 Compliance:
 * - All mandatory rules: Compliant
 * - All required rules: Compliant (or deviations documented)
 * 
 * @en50128_references
 * - EN 50128:2011 Section 7.4 (Software Design and Implementation)
 * - EN 50128:2011 Table A.4 (Implementation techniques)
 * 
 * @usage
 * Example usage:
 * @code
 * module_config_t config = {
 *     .value = 100U,
 *     .flags = 0U
 * };
 * 
 * error_t err = module_init(&config);
 * if (ERROR_SUCCESS == err) {
 *     uint8_t input[16] = {0};
 *     uint8_t output[16];
 *     uint16_t written;
 *     
 *     err = module_process(input, 16U, output, 16U, &written);
 *     if (ERROR_SUCCESS == err) {
 *         // Process output
 *     }
 *     
 *     module_deinit();
 * }
 * @endcode
 */

/* MISRA C:2012 Rule 21.1: Include guard pattern (recommended) */
#ifndef MODULE_NAME_H
#define MODULE_NAME_H

/*============================================================================
 * INCLUDES
 *===========================================================================*/

/* Standard library includes */
#include <stdint.h>     /* For fixed-width integer types (MANDATORY SIL 2+) */
#include <stdbool.h>    /* For bool type */
#include <stddef.h>     /* For NULL, size_t */

/* Project-specific includes */
#include "error_codes.h"    /* Common error codes */

/*============================================================================
 * PREPROCESSOR DEFINITIONS
 *===========================================================================*/

/**
 * @brief Module version major number
 */
#define MODULE_VERSION_MAJOR (1U)

/**
 * @brief Module version minor number
 */
#define MODULE_VERSION_MINOR (0U)

/**
 * @brief Module version patch number
 */
#define MODULE_VERSION_PATCH (0U)

/**
 * @brief Maximum input data size (example)
 */
#define MODULE_MAX_INPUT_SIZE (256U)

/**
 * @brief Maximum output data size (example)
 */
#define MODULE_MAX_OUTPUT_SIZE (256U)

/**
 * @brief Module-specific error codes
 * @note Error codes are in range MODULE_ERROR_BASE + [0..255]
 */
#define MODULE_ERROR_BASE           (0x1000U)
#define ERROR_ALREADY_INITIALIZED   (MODULE_ERROR_BASE + 1U)
#define ERROR_INVALID_CONFIG        (MODULE_ERROR_BASE + 2U)
#define ERROR_BUFFER_TOO_SMALL      (MODULE_ERROR_BASE + 3U)
#define ERROR_INVALID_PARAMETER     (MODULE_ERROR_BASE + 4U)

/*============================================================================
 * TYPE DEFINITIONS
 *===========================================================================*/

/**
 * @brief Module configuration structure
 * @note All fields use fixed-width types (MISRA C, SIL 2+ requirement)
 */
typedef struct {
    uint32_t value;     /**< Configuration value (range: 0..MAX_BUFFER_SIZE) */
    uint16_t flags;     /**< Configuration flags (bitfield) */
    uint8_t  mode;      /**< Operating mode (0=normal, 1=debug, 2=safe) */
    uint8_t  reserved;  /**< Reserved for future use / alignment */
} module_config_t;

/**
 * @brief Module status structure
 * @note All fields use fixed-width types (MISRA C, SIL 2+ requirement)
 */
typedef struct {
    uint32_t state;         /**< Current state value */
    uint16_t counter;       /**< Event counter */
    bool     initialized;   /**< Initialization status */
    uint8_t  reserved;      /**< Reserved for alignment */
} module_status_t;

/**
 * @brief Error type definition
 * @note Uses fixed-width type (MISRA C, SIL 2+ requirement)
 */
typedef uint32_t error_t;

/**
 * @brief Module state enumeration
 * @note Enum values explicitly specified (MISRA C recommendation)
 */
typedef enum {
    MODULE_STATE_UNINITIALIZED = 0U,    /**< Module not initialized */
    MODULE_STATE_IDLE = 1U,             /**< Module idle, ready for operation */
    MODULE_STATE_BUSY = 2U,             /**< Module processing data */
    MODULE_STATE_ERROR = 3U,            /**< Module in error state */
    MODULE_STATE_MAX = 4U               /**< Maximum state value (for validation) */
} module_state_enum_t;

/**
 * @brief Operating mode enumeration
 * @note Enum values explicitly specified (MISRA C recommendation)
 */
typedef enum {
    MODULE_MODE_NORMAL = 0U,    /**< Normal operating mode */
    MODULE_MODE_DEBUG = 1U,     /**< Debug mode (additional logging) */
    MODULE_MODE_SAFE = 2U,      /**< Safe mode (degraded functionality) */
    MODULE_MODE_MAX = 3U        /**< Maximum mode value (for validation) */
} module_mode_enum_t;

/*============================================================================
 * GLOBAL CONSTANTS (extern declarations)
 *===========================================================================*/

/**
 * @brief Module name string (defined in .c file)
 */
extern const char MODULE_NAME[];

/**
 * @brief Module version string (defined in .c file)
 */
extern const char MODULE_VERSION[];

/*============================================================================
 * PUBLIC FUNCTION PROTOTYPES
 *===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

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
 * @retval ERROR_ALREADY_INITIALIZED Module already initialized
 * 
 * @pre Module must not already be initialized
 * @post Module is initialized and ready for use
 * 
 * @safety This function is safety-critical (SIL [X])
 * 
 * @note This function must be called before any other module function
 * @warning Calling this function twice without deinit causes ERROR_ALREADY_INITIALIZED
 * 
 * @see module_deinit()
 */
error_t module_init(const module_config_t *config);

/**
 * @brief Process data through the module
 * @details This function processes input data and produces output data.
 * 
 * @param[in]  input_data  Pointer to input data (must not be NULL)
 * @param[in]  input_size  Size of input data in bytes (must be > 0 and ≤ MODULE_MAX_INPUT_SIZE)
 * @param[out] output_data Pointer to output buffer (must not be NULL)
 * @param[in]  output_size Size of output buffer in bytes (must be ≥ input_size)
 * @param[out] bytes_written Pointer to variable receiving bytes written (may be NULL)
 * 
 * @return error_t Error code
 * @retval ERROR_SUCCESS Processing successful
 * @retval ERROR_NULL_POINTER input_data or output_data is NULL
 * @retval ERROR_INVALID_SIZE input_size is 0 or output_size too small
 * @retval ERROR_NOT_INITIALIZED Module not initialized
 * @retval ERROR_BUFFER_TOO_SMALL Output buffer too small for processed data
 * 
 * @pre Module must be initialized (module_init() called)
 * @pre input_data must point to valid memory of at least input_size bytes
 * @pre output_data must point to valid memory of at least output_size bytes
 * @post output_data contains processed data (if successful)
 * @post *bytes_written contains number of bytes written to output_data (if not NULL)
 * 
 * @safety This function is safety-critical (SIL [X])
 * 
 * @note If bytes_written is NULL, the actual bytes written will not be returned
 * @warning Input and output buffers must not overlap
 * 
 * @see module_init()
 */
error_t module_process(const uint8_t *input_data, 
                        uint16_t input_size,
                        uint8_t *output_data,
                        uint16_t output_size,
                        uint16_t *bytes_written);

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
 * @post *status contains current module status (if successful)
 * 
 * @safety This function is non-critical
 * 
 * @note This function does not modify module state
 * 
 * @see module_status_t
 */
error_t module_get_status(module_status_t *status);

/**
 * @brief Deinitialize the module
 * @details This function deinitializes the module and releases resources.
 *          After calling this function, module_init() must be called again
 *          before using any other module functions.
 * 
 * @return error_t Error code
 * @retval ERROR_SUCCESS Deinitialization successful
 * @retval ERROR_NOT_INITIALIZED Module not initialized
 * 
 * @pre Module must be initialized
 * @post Module is deinitialized and cannot be used until reinitialized
 * @post All internal state is cleared
 * 
 * @safety This function is safety-critical (SIL [X])
 * 
 * @note After calling this function, the module is in uninitialized state
 * 
 * @see module_init()
 */
error_t module_deinit(void);

/*============================================================================
 * INLINE FUNCTIONS (for performance-critical operations)
 *===========================================================================*/

/**
 * @brief Check if module is initialized (inline for performance)
 * @details This is a lightweight check for module initialization status.
 * 
 * @return bool Initialization status
 * @retval true Module is initialized
 * @retval false Module is not initialized
 * 
 * @note This function is inline for performance in critical paths
 * @note This function does not perform comprehensive error checking
 * 
 * @warning For safety-critical code, prefer module_get_status() which performs full validation
 */
static inline bool module_is_initialized(void)
{
    /* Note: This would need access to internal state in actual implementation
     * In practice, this might be implemented differently or removed
     * This is an example of inline function declaration
     */
    return false; /* Placeholder implementation */
}

#ifdef __cplusplus
}
#endif

/*============================================================================
 * UNIT TEST INTERFACE (Conditional Compilation)
 *===========================================================================*/

#ifdef UNIT_TEST

/**
 * @brief Unit test hook to access internal state
 * @note Only available when compiled with UNIT_TEST defined
 * @return Pointer to module state (for testing only)
 * @warning Do not use in production code
 */
extern module_state_t* test_get_module_state(void);

/**
 * @brief Unit test hook to reset module state
 * @note Only available when compiled with UNIT_TEST defined
 * @warning Do not use in production code
 */
extern void test_reset_module_state(void);

#endif /* UNIT_TEST */

/*============================================================================
 * MISRA C:2012 COMPLIANCE NOTES
 *===========================================================================*/

/**
 * @misra_compliance
 * 
 * This header file is compliant with MISRA C:2012 with the following notes:
 * 
 * - Rule 8.5: All external declarations have one definition (in .c file)
 * - Rule 8.7: Functions/variables with external linkage properly declared
 * - Rule 8.11: Static storage arrays sized (not applicable in header)
 * - Rule 20.7: Fixed-width types used (stdint.h)
 * - Rule 21.1: Include guards used (#ifndef/#define/#endif pattern)
 * 
 * No MISRA deviations required for this header file.
 */

/*============================================================================
 * EN 50128 COMPLIANCE NOTES
 *===========================================================================*/

/**
 * @en50128_compliance
 * 
 * This header file follows EN 50128:2011 guidelines:
 * 
 * - Section 7.4: Structured methodology applied
 * - Table A.4: Modular approach (M for SIL 2+)
 * - Table A.4: Design and coding standards (M for SIL 3-4)
 * - Table A.4: Fully defined interface (HR for SIL 2+)
 * - Defensive programming: All pointers checked for NULL
 * - Fixed-width types: All integer types are fixed-width (SIL 2+ requirement)
 * - No dynamic allocation: All data structures are statically sized
 * 
 * SIL Level: [X]
 * Safety Functions: [List safety-critical functions]
 */

#endif /* MODULE_NAME_H */

/*============================================================================
 * END OF FILE
 *===========================================================================*/
