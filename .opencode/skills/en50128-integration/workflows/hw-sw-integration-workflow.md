# Hardware/Software Integration Workflow

**EN 50128 Reference**: Section 7.6.1.1, 7.6.1.2, 7.6.4.7-7.6.4.10  
**Phase**: Phase 6 - Integration  
**Role**: Integrator (INT)  
**SIL Level**: All (0-4)

---

## Purpose

This workflow defines the complete process for integrating software components with target hardware, demonstrating that "the software and the hardware interact correctly to perform their intended functions" (EN 50128 Section 7.6.1.2).

**Key Objectives**:
- Software integration on target hardware platform
- Hardware abstraction layer validation
- Hardware-in-the-loop (HIL) testing
- Timing and performance verification on real hardware
- Safety mechanism validation (watchdogs, redundancy, voting)
- Evidence collection for Software/Hardware Integration Test Report

**Inputs**:
- Software Integration Test Report (from component integration)
- Software/Hardware Integration Test Specification
- Target hardware specification
- Hardware documentation (schematics, register maps, datasheets)
- Integrated software (from component integration phase)

**Outputs**:
- Software/Hardware Integration Test Report (Section 7.6.4.7-7.6.4.10)
- Hardware compatibility evidence
- Timing/performance validation results
- Safety mechanism test results
- Configuration documentation

---

## Table of Contents

1. [Hardware Abstraction Layer (HAL) Design](#hardware-abstraction-layer-hal-design)
2. [Target Hardware Configuration](#target-hardware-configuration)
3. [HAL Integration and Testing](#hal-integration-and-testing)
4. [Hardware-in-the-Loop (HIL) Testing](#hardware-in-the-loop-hil-testing)
5. [Timing and Performance Validation](#timing-and-performance-validation)
6. [Safety Mechanisms Validation](#safety-mechanisms-validation)
7. [Interrupt and Concurrency Testing](#interrupt-and-concurrency-testing)
8. [Hardware-Specific Defect Detection](#hardware-specific-defect-detection)
9. [Target Platform Validation](#target-platform-validation)
10. [Tool Integration for HW/SW Testing](#tool-integration-for-hwsw-testing)

---

## Hardware Abstraction Layer (HAL) Design

### HAL Purpose and Requirements

**EN 50128 Principle**: Hardware abstraction enables:
- **Portability**: Software can be tested on host before hardware available
- **Testability**: Software can be tested with hardware simulators
- **Maintainability**: Hardware changes isolated from application logic

**SIL Requirements**:
- **SIL 0-2**: HAL **recommended** for testability
- **SIL 3-4**: HAL **highly recommended** (enables thorough testing before hardware integration)

**C HAL Design Pattern**:

```c
// File: hal.h - Hardware Abstraction Layer Interface
// This interface is IDENTICAL on all platforms (real hardware, simulator, test stub)

#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include <stdbool.h>
#include "common_types.h"

/**
 * @brief Hardware Abstraction Layer (HAL)
 * @standard EN 50128 Section 7.6
 * @sil 3
 * 
 * DESIGN PRINCIPLE:
 * - Same interface on all platforms (hardware, simulator, test)
 * - No platform-specific code in upper layers
 * - All hardware access through HAL only
 */

// GPIO Operations
result_t hal_gpio_init(void);
result_t hal_gpio_set_pin(uint8_t pin, bool value);
result_t hal_gpio_read_pin(uint8_t pin, bool* value);

// Timer Operations
result_t hal_timer_init(uint32_t frequency_hz);
result_t hal_timer_start(void);
result_t hal_timer_stop(void);
uint32_t hal_timer_get_ticks(void);

// UART Operations
result_t hal_uart_init(uint32_t baud_rate);
result_t hal_uart_write(const uint8_t* data, size_t length);
result_t hal_uart_read(uint8_t* buffer, size_t max_length, size_t* bytes_read);

// ADC Operations (for sensors)
result_t hal_adc_init(uint8_t channel);
result_t hal_adc_read(uint8_t channel, uint16_t* value);

// PWM Operations (for actuators)
result_t hal_pwm_init(uint8_t channel, uint32_t frequency_hz);
result_t hal_pwm_set_duty_cycle(uint8_t channel, uint16_t duty_cycle_percent);

// Interrupt Operations
result_t hal_interrupt_enable(uint8_t irq_number);
result_t hal_interrupt_disable(uint8_t irq_number);
void hal_interrupt_register_handler(uint8_t irq_number, void (*handler)(void));

// System Operations
result_t hal_system_init(void);
void hal_system_reset(void);
uint32_t hal_system_get_timestamp_us(void);
void hal_delay_us(uint32_t microseconds);

#endif  // HAL_H
```

---

### Platform-Specific HAL Implementations

**Implementation 1: Real Target Hardware**

```c
// File: hal_target.c - HAL implementation for ARM Cortex-M4 target
// Used during hardware/software integration and deployment

#include "hal.h"
#include "stm32f4xx.h"  // Target-specific register definitions

// GPIO Implementation (Real Hardware)
result_t hal_gpio_init(void) {
    // Enable GPIO clocks on STM32F4
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  // Enable GPIOA clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;  // Enable GPIOB clock
    
    // Configure GPIO pins as outputs
    GPIOA->MODER |= GPIO_MODER_MODER5_0;  // PA5 as output
    
    return RESULT_SUCCESS;
}

result_t hal_gpio_set_pin(uint8_t pin, bool value) {
    if (pin > 15) {
        return RESULT_ERROR_INVALID_PARAM;
    }
    
    if (value) {
        GPIOA->BSRR = (1U << pin);  // Set pin (atomic)
    } else {
        GPIOA->BSRR = (1U << (pin + 16));  // Reset pin (atomic)
    }
    
    return RESULT_SUCCESS;
}

result_t hal_gpio_read_pin(uint8_t pin, bool* value) {
    if (pin > 15 || value == NULL) {
        return RESULT_ERROR_INVALID_PARAM;
    }
    
    *value = (GPIOA->IDR & (1U << pin)) ? true : false;
    return RESULT_SUCCESS;
}

// Timer Implementation (Real Hardware)
result_t hal_timer_init(uint32_t frequency_hz) {
    // Enable TIM2 clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    
    // Configure timer for desired frequency
    uint32_t system_clock = 168000000;  // 168 MHz (STM32F4)
    uint32_t prescaler = (system_clock / frequency_hz) - 1;
    
    TIM2->PSC = prescaler;
    TIM2->ARR = 0xFFFFFFFF;  // Max auto-reload (32-bit timer)
    TIM2->CR1 = TIM_CR1_CEN;  // Enable counter
    
    return RESULT_SUCCESS;
}

uint32_t hal_timer_get_ticks(void) {
    return TIM2->CNT;
}

// ADC Implementation (Real Hardware)
result_t hal_adc_init(uint8_t channel) {
    if (channel > 15) {
        return RESULT_ERROR_INVALID_PARAM;
    }
    
    // Enable ADC1 clock
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    
    // Configure ADC
    ADC1->CR2 = ADC_CR2_ADON;  // Power on ADC
    ADC1->SQR3 = channel;      // Select channel for conversion
    ADC1->SMPR2 = 0x7 << (channel * 3);  // Sample time
    
    return RESULT_SUCCESS;
}

result_t hal_adc_read(uint8_t channel, uint16_t* value) {
    if (channel > 15 || value == NULL) {
        return RESULT_ERROR_INVALID_PARAM;
    }
    
    // Start conversion
    ADC1->CR2 |= ADC_CR2_SWSTART;
    
    // Wait for conversion (with timeout)
    uint32_t timeout = 10000;
    while (!(ADC1->SR & ADC_SR_EOC) && timeout > 0) {
        timeout--;
    }
    
    if (timeout == 0) {
        return RESULT_ERROR_TIMEOUT;
    }
    
    *value = ADC1->DR;  // Read converted value (0-4095 for 12-bit ADC)
    return RESULT_SUCCESS;
}

// System timestamp (Real Hardware)
uint32_t hal_system_get_timestamp_us(void) {
    // Use SysTick or TIM2 for microsecond timestamp
    uint32_t ticks = TIM2->CNT;
    uint32_t frequency = 1000000;  // 1 MHz timer
    return ticks;  // Already in microseconds if 1 MHz timer
}
```

---

**Implementation 2: Host PC Simulator (for testing without hardware)**

```c
// File: hal_simulator.c - HAL implementation for host PC testing
// Used during development before hardware available

#include "hal.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>

// Simulated hardware state
static bool gpio_pins[16] = {false};
static uint32_t timer_ticks = 0;
static uint16_t adc_values[16] = {0};

// GPIO Implementation (Simulator)
result_t hal_gpio_init(void) {
    printf("[HAL_SIM] GPIO initialized\\n");
    return RESULT_SUCCESS;
}

result_t hal_gpio_set_pin(uint8_t pin, bool value) {
    if (pin > 15) {
        return RESULT_ERROR_INVALID_PARAM;
    }
    
    gpio_pins[pin] = value;
    printf("[HAL_SIM] GPIO pin %d set to %d\\n", pin, value);
    return RESULT_SUCCESS;
}

result_t hal_gpio_read_pin(uint8_t pin, bool* value) {
    if (pin > 15 || value == NULL) {
        return RESULT_ERROR_INVALID_PARAM;
    }
    
    *value = gpio_pins[pin];
    printf("[HAL_SIM] GPIO pin %d read: %d\\n", pin, *value);
    return RESULT_SUCCESS;
}

// Timer Implementation (Simulator)
result_t hal_timer_init(uint32_t frequency_hz) {
    printf("[HAL_SIM] Timer initialized at %u Hz\\n", frequency_hz);
    return RESULT_SUCCESS;
}

uint32_t hal_timer_get_ticks(void) {
    // Use host system clock for simulation
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;  // Return microseconds
}

// ADC Implementation (Simulator)
result_t hal_adc_init(uint8_t channel) {
    if (channel > 15) {
        return RESULT_ERROR_INVALID_PARAM;
    }
    
    printf("[HAL_SIM] ADC channel %d initialized\\n", channel);
    
    // Initialize with test value
    adc_values[channel] = 2048;  // Mid-scale (12-bit)
    return RESULT_SUCCESS;
}

result_t hal_adc_read(uint8_t channel, uint16_t* value) {
    if (channel > 15 || value == NULL) {
        return RESULT_ERROR_INVALID_PARAM;
    }
    
    // Return simulated value (can be controlled by test)
    *value = adc_values[channel];
    printf("[HAL_SIM] ADC channel %d read: %u\\n", channel, *value);
    return RESULT_SUCCESS;
}

// Test helper: Set simulated ADC value
void hal_adc_simulator_set_value(uint8_t channel, uint16_t value) {
    if (channel < 16) {
        adc_values[channel] = value;
    }
}

// System timestamp (Simulator)
uint32_t hal_system_get_timestamp_us(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
}
```

---

**Implementation 3: Test Stub (for unit testing)**

```c
// File: hal_stub.c - HAL stub for unit testing with full control
// Used during unit testing and integration testing

#include "hal.h"
#include <string.h>

// Stub state with full control for testing
typedef struct {
    bool gpio_initialized;
    bool gpio_pins[16];
    result_t gpio_error_injection;  // Error to inject
    
    bool adc_initialized[16];
    uint16_t adc_values[16];
    result_t adc_error_injection;
    
    uint32_t timer_ticks;
    uint32_t call_count_gpio_set;
    uint32_t call_count_adc_read;
} hal_stub_state_t;

static hal_stub_state_t stub_state;

// Stub initialization
void hal_stub_init(void) {
    memset(&stub_state, 0, sizeof(stub_state));
    stub_state.gpio_error_injection = RESULT_SUCCESS;
    stub_state.adc_error_injection = RESULT_SUCCESS;
}

// GPIO Implementation (Stub with error injection)
result_t hal_gpio_init(void) {
    if (stub_state.gpio_error_injection != RESULT_SUCCESS) {
        return stub_state.gpio_error_injection;
    }
    
    stub_state.gpio_initialized = true;
    return RESULT_SUCCESS;
}

result_t hal_gpio_set_pin(uint8_t pin, bool value) {
    stub_state.call_count_gpio_set++;
    
    if (!stub_state.gpio_initialized) {
        return RESULT_ERROR_NOT_INITIALIZED;
    }
    
    if (pin > 15) {
        return RESULT_ERROR_INVALID_PARAM;
    }
    
    if (stub_state.gpio_error_injection != RESULT_SUCCESS) {
        return stub_state.gpio_error_injection;
    }
    
    stub_state.gpio_pins[pin] = value;
    return RESULT_SUCCESS;
}

result_t hal_gpio_read_pin(uint8_t pin, bool* value) {
    if (!stub_state.gpio_initialized) {
        return RESULT_ERROR_NOT_INITIALIZED;
    }
    
    if (pin > 15 || value == NULL) {
        return RESULT_ERROR_INVALID_PARAM;
    }
    
    *value = stub_state.gpio_pins[pin];
    return RESULT_SUCCESS;
}

// ADC Implementation (Stub with error injection)
result_t hal_adc_init(uint8_t channel) {
    if (channel > 15) {
        return RESULT_ERROR_INVALID_PARAM;
    }
    
    if (stub_state.adc_error_injection != RESULT_SUCCESS) {
        return stub_state.adc_error_injection;
    }
    
    stub_state.adc_initialized[channel] = true;
    stub_state.adc_values[channel] = 2048;  // Default mid-scale
    return RESULT_SUCCESS;
}

result_t hal_adc_read(uint8_t channel, uint16_t* value) {
    stub_state.call_count_adc_read++;
    
    if (channel > 15) {
        return RESULT_ERROR_INVALID_PARAM;
    }
    
    if (!stub_state.adc_initialized[channel]) {
        return RESULT_ERROR_NOT_INITIALIZED;
    }
    
    if (value == NULL) {
        return RESULT_ERROR_NULL_PTR;
    }
    
    if (stub_state.adc_error_injection != RESULT_SUCCESS) {
        return stub_state.adc_error_injection;
    }
    
    *value = stub_state.adc_values[channel];
    return RESULT_SUCCESS;
}

// Test control functions
void hal_stub_inject_gpio_error(result_t error) {
    stub_state.gpio_error_injection = error;
}

void hal_stub_inject_adc_error(result_t error) {
    stub_state.adc_error_injection = error;
}

void hal_stub_set_adc_value(uint8_t channel, uint16_t value) {
    if (channel < 16) {
        stub_state.adc_values[channel] = value;
    }
}

uint32_t hal_stub_get_call_count_gpio_set(void) {
    return stub_state.call_count_gpio_set;
}

uint32_t hal_stub_get_call_count_adc_read(void) {
    return stub_state.call_count_adc_read;
}

// Timer stub
uint32_t hal_timer_get_ticks(void) {
    return stub_state.timer_ticks;
}

void hal_stub_set_timer_ticks(uint32_t ticks) {
    stub_state.timer_ticks = ticks;
}
```

---

### HAL Integration Test Example

```c
// File: test_hal_integration.c
// Tests application code with different HAL implementations

#include "sensor_driver.h"  // Uses HAL
#include "hal.h"
#include "unity.h"

void setUp(void) {
    #ifdef HAL_STUB
    hal_stub_init();
    #endif
    
    hal_system_init();
    hal_adc_init(0);
}

void test_sensor_driver_reads_through_hal(void) {
    // This test works with ANY HAL implementation (target, simulator, stub)
    
    #ifdef HAL_STUB
    // Stub: Set known value
    hal_stub_set_adc_value(0, 1234);
    #endif
    
    #ifdef HAL_SIMULATOR
    // Simulator: Set known value
    hal_adc_simulator_set_value(0, 1234);
    #endif
    
    // If using real hardware (HAL_TARGET), value comes from actual ADC
    
    // Test sensor driver (uses HAL internally)
    uint16_t value;
    result_t result = sensor_driver_read(&value);
    
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    #if defined(HAL_STUB) || defined(HAL_SIMULATOR)
    TEST_ASSERT_EQUAL(1234, value);  // Known value on stub/simulator
    #else
    TEST_ASSERT_TRUE(value >= 0 && value <= 4095);  // Valid range on real hardware
    #endif
}

void test_sensor_driver_handles_hal_error(void) {
    #ifdef HAL_STUB
    // Stub allows error injection
    hal_stub_inject_adc_error(RESULT_ERROR_HARDWARE);
    #endif
    
    uint16_t value;
    result_t result = sensor_driver_read(&value);
    
    #ifdef HAL_STUB
    TEST_ASSERT_EQUAL(RESULT_ERROR_HARDWARE, result);
    #else
    // On real hardware, cannot inject errors programmatically
    // (Would require physical fault injection)
    TEST_PASS_MESSAGE("Error injection test skipped on real hardware");
    #endif
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_sensor_driver_reads_through_hal);
    RUN_TEST(test_sensor_driver_handles_hal_error);
    return UNITY_END();
}
```

**Build for Different Platforms**:

```makefile
# Makefile with HAL platform selection

# Platform selection (default: stub for testing)
PLATFORM ?= stub

# HAL implementation selection
ifeq ($(PLATFORM),target)
    HAL_SRC = hal_target.c
    CFLAGS += -DHAL_TARGET
    CFLAGS += -mcpu=cortex-m4 -mthumb  # ARM target flags
    CC = arm-none-eabi-gcc
else ifeq ($(PLATFORM),simulator)
    HAL_SRC = hal_simulator.c
    CFLAGS += -DHAL_SIMULATOR
else
    HAL_SRC = hal_stub.c
    CFLAGS += -DHAL_STUB
endif

# Build test executable
test_hal: test_hal_integration.c sensor_driver.c $(HAL_SRC)
	$(CC) $(CFLAGS) $^ -o $@

# Run test on each platform
test_stub:
	$(MAKE) PLATFORM=stub test_hal
	./test_hal

test_simulator:
	$(MAKE) PLATFORM=simulator test_hal
	./test_hal

test_target:
	$(MAKE) PLATFORM=target test_hal
	# Flash to target hardware and run
	openocd -f flash_and_run.cfg
```

**Usage**:

```bash
# Test with stub (fast, controllable)
make test_stub

# Test with simulator (realistic, no hardware needed)
make test_simulator

# Test on target hardware (final validation)
make test_target
```

---

## Target Hardware Configuration

### Hardware Platform Documentation

**EN 50128 Section 7.6.4.9c**: "...document the identity and configuration of all items involved"

**Hardware Configuration Document Template**:

```markdown
# Hardware Configuration Document

**Project**: Railway Braking System  
**Hardware Platform**: STM32F407VGT6 (ARM Cortex-M4)  
**Document ID**: HCD-BRAKE-001  
**Version**: 1.0.0  
**Date**: 2026-03-14  
**SIL Level**: 3

## Hardware Specifications

### Microcontroller
- **Part Number**: STM32F407VGT6
- **Manufacturer**: STMicroelectronics
- **Core**: ARM Cortex-M4F, 32-bit RISC
- **Clock Speed**: 168 MHz (max)
- **Flash Memory**: 1 MB
- **SRAM**: 192 KB
- **Package**: LQFP-100

### Peripherals Used

| Peripheral | Purpose | Configuration |
|------------|---------|---------------|
| ADC1 Channel 0 | Speed Sensor | 12-bit, 1 MHz sampling |
| PWM TIM3 Channel 1 | Brake Actuator | 1 kHz, 0-100% duty cycle |
| UART2 | Diagnostics | 115200 baud, 8N1 |
| GPIO PA5 | Status LED | Output, push-pull |
| GPIO PA0 | Emergency Button | Input, pull-up |
| TIM2 | System Timer | 1 MHz (1 µs resolution) |

### Memory Map

| Region | Start Address | End Address | Size | Usage |
|--------|---------------|-------------|------|-------|
| Flash | 0x08000000 | 0x080FFFFF | 1 MB | Program code |
| SRAM1 | 0x20000000 | 0x2001BFFF | 112 KB | Application data |
| SRAM2 | 0x2001C000 | 0x2001FFFF | 16 KB | Safety critical data |
| CCM | 0x10000000 | 0x1000FFFF | 64 KB | Stack |

### Power Supply
- **Voltage**: 3.3V ± 0.3V
- **Current**: Max 200 mA
- **Source**: Regulated power supply with backup battery

### Interfaces

**Speed Sensor Interface**:
- Type: Analog voltage (0-3.3V)
- Resolution: 12-bit ADC (0-4095)
- Input impedance: 10 kΩ
- Sampling rate: 1 kHz
- Range: 0-250 km/h (0V = 0 km/h, 3.3V = 250 km/h)

**Brake Actuator Interface**:
- Type: PWM signal
- Frequency: 1 kHz
- Duty cycle: 0-100% (0% = no brake, 100% = full brake)
- Output voltage: 3.3V logic level
- Load: Brake driver circuit (not directly connected to actuator)

### Clock Configuration

```c
// System clock: 168 MHz from HSE (8 MHz) with PLL
RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
RCC_OscInitStruct.HSEState = RCC_HSE_ON;
RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
RCC_OscInitStruct.PLL.PLLM = 8;
RCC_OscInitStruct.PLL.PLLN = 336;
RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
RCC_OscInitStruct.PLL.PLLQ = 7;
```

### Compiler and Toolchain

**Compiler**: arm-none-eabi-gcc 10.3.1  
**Flags**: `-mcpu=cortex-m4 -mthumb -O2 -std=c99 -Wall -Wextra -Werror`

**Linker Script**: STM32F407VGTx_FLASH.ld  
**Startup Code**: startup_stm32f407xx.s

### Safety Mechanisms (SIL 3)

- **Watchdog**: Independent watchdog (IWDG), 1 second timeout
- **Memory Protection**: MPU enabled for stack overflow detection
- **Clock Security**: CSS (Clock Security System) enabled
- **Brown-out Reset**: BOR Level 3 (2.7V threshold)
```

---

### Hardware Setup Script

```bash
#!/bin/bash
# setup_target_hardware.sh
# Configures target hardware for software/hardware integration

set -e

HARDWARE_PLATFORM="STM32F407VGT6"
OPENOCD_CFG="stm32f4x.cfg"
GDB_PORT=3333

echo "======================================================================="
echo "Target Hardware Setup: $HARDWARE_PLATFORM"
echo "======================================================================="

# 1. Verify hardware connection
echo "1. Verifying hardware connection..."
openocd -f interface/stlink.cfg -f target/$OPENOCD_CFG \
    -c "init" -c "targets" -c "shutdown" > /dev/null 2>&1

if [ $? -eq 0 ]; then
    echo "   ✅ Hardware connected"
else
    echo "   ❌ Hardware NOT connected - check ST-Link connection"
    exit 1
fi

# 2. Read hardware information
echo "2. Reading hardware information..."
DEVICE_ID=$(openocd -f interface/stlink.cfg -f target/$OPENOCD_CFG \
    -c "init" -c "flash info 0" -c "shutdown" 2>&1 | grep "device id")
echo "   Device: $DEVICE_ID"

# 3. Erase flash
echo "3. Erasing flash memory..."
openocd -f interface/stlink.cfg -f target/$OPENOCD_CFG \
    -c "init" -c "reset halt" -c "flash erase_sector 0 0 last" -c "shutdown"
echo "   ✅ Flash erased"

# 4. Program software
echo "4. Programming integrated software..."
openocd -f interface/stlink.cfg -f target/$OPENOCD_CFG \
    -c "init" -c "reset halt" \
    -c "flash write_image erase build/railway_brake_system.elf" \
    -c "reset run" -c "shutdown"
echo "   ✅ Software programmed"

# 5. Verify programming
echo "5. Verifying software..."
openocd -f interface/stlink.cfg -f target/$OPENOCD_CFG \
    -c "init" -c "reset halt" \
    -c "verify_image build/railway_brake_system.elf" \
    -c "shutdown"
echo "   ✅ Software verified"

# 6. Configure debug interface
echo "6. Starting debug server (background)..."
openocd -f interface/stlink.cfg -f target/$OPENOCD_CFG \
    -c "gdb_port $GDB_PORT" > openocd.log 2>&1 &
OPENOCD_PID=$!
sleep 2
echo "   ✅ Debug server running (PID: $OPENOCD_PID, port: $GDB_PORT)"

# 7. Test communication
echo "7. Testing communication..."
echo "target extended-remote localhost:$GDB_PORT" > /tmp/gdb_test.cmd
echo "monitor reset halt" >> /tmp/gdb_test.cmd
echo "quit" >> /tmp/gdb_test.cmd

arm-none-eabi-gdb -batch -x /tmp/gdb_test.cmd build/railway_brake_system.elf
echo "   ✅ Communication OK"

echo ""
echo "======================================================================="
echo "Target Hardware Setup COMPLETE"
echo "======================================================================="
echo "Hardware Platform: $HARDWARE_PLATFORM"
echo "Software Image: build/railway_brake_system.elf"
echo "Debug Server: localhost:$GDB_PORT (PID: $OPENOCD_PID)"
echo ""
echo "Next Steps:"
echo "  - Connect to GDB: arm-none-eabi-gdb build/railway_brake_system.elf"
echo "  - Run HIL tests: make hil_test"
echo "  - Stop debug server: kill $OPENOCD_PID"
echo "======================================================================="
```

**Usage**:

```bash
# Setup target hardware and program software
./setup_target_hardware.sh

# Output:
# =======================================================================
# Target Hardware Setup: STM32F407VGT6
# =======================================================================
# 1. Verifying hardware connection...
#    ✅ Hardware connected
# 2. Reading hardware information...
#    Device: device id = 0x10036413
# 3. Erasing flash memory...
#    ✅ Flash erased
# 4. Programming integrated software...
#    ✅ Software programmed
# 5. Verifying software...
#    ✅ Software verified
# 6. Starting debug server (background)...
#    ✅ Debug server running (PID: 12345, port: 3333)
# 7. Testing communication...
#    ✅ Communication OK
```

---

## HAL Integration and Testing

### Progressive HAL Integration

**Step 1: Host PC Simulator (No Hardware Needed)**

```bash
# Build with simulator HAL
make PLATFORM=simulator test_sensor_driver

# Run tests on host PC
./test_sensor_driver

# Output:
# [HAL_SIM] ADC channel 0 initialized
# [HAL_SIM] ADC channel 0 read: 2048
# test_sensor_reads_adc: PASS
# test_sensor_converts_to_speed: PASS
# 2 Tests 0 Failures 0 Ignored
```

**Step 2: Target Hardware (Real Integration)**

```bash
# Build with target HAL
make PLATFORM=target test_sensor_driver

# Flash to target
./setup_target_hardware.sh

# Run tests on target (via GDB + semihosting)
arm-none-eabi-gdb build/test_sensor_driver.elf \
    -ex "target extended-remote localhost:3333" \
    -ex "load" \
    -ex "monitor reset halt" \
    -ex "continue"

# Output (via semihosting):
# test_sensor_reads_adc: PASS (ADC value: 2456)
# test_sensor_converts_to_speed: PASS (Speed: 120 km/h)
# 2 Tests 0 Failures 0 Ignored
```

---

### HAL Interface Violation Detection

```c
// Test: Detect when application violates HAL interface contract

void test_hal_detects_uninitialized_use(void) {
    // Do NOT call hal_adc_init() - intentional violation
    
    uint16_t value;
    result_t result = hal_adc_read(0, &value);
    
    // HAL should detect and reject (on stub/target, not all simulators)
    #if defined(HAL_STUB) || defined(HAL_TARGET)
    TEST_ASSERT_EQUAL(RESULT_ERROR_NOT_INITIALIZED, result);
    #endif
}

void test_hal_detects_invalid_parameters(void) {
    hal_adc_init(0);
    
    // Invalid channel
    uint16_t value;
    result_t result = hal_adc_read(99, &value);
    TEST_ASSERT_EQUAL(RESULT_ERROR_INVALID_PARAM, result);
    
    // NULL pointer
    result = hal_adc_read(0, NULL);
    TEST_ASSERT_EQUAL(RESULT_ERROR_NULL_PTR, result);
}

void test_hal_enforces_initialization_order(void) {
    // Try to read before system init
    hal_adc_init(0);  // May fail if system not initialized
    
    uint16_t value;
    result_t result = hal_adc_read(0, &value);
    
    // Some HALs require hal_system_init() first
    // Verify proper initialization sequence enforced
}
```

---

## Hardware-in-the-Loop (HIL) Testing

### HIL Test Setup

**Objective**: Test integrated software on real hardware with real sensors/actuators or physical simulators

**HIL Test Architecture**:

```
┌────────────────────────────────────────────────────────────┐
│ Test Host PC (Python)                                      │
│   - Test execution control                                 │
│   - Test case definition                                   │
│   - Result collection                                      │
│   - Stimulus generation                                    │
└────────┬───────────────────────────────────────────────────┘
         │ (USB/Ethernet)
         ↓
┌────────────────────────────────────────────────────────────┐
│ Target Hardware (STM32F4)                                  │
│   - Integrated software under test                         │
│   - Real-time execution                                    │
│   - Actual peripherals (ADC, PWM, GPIO, etc.)             │
└────┬──────────────────────────┬────────────────────────────┘
     │ (Analog/Digital I/O)     │
     ↓                          ↓
┌──────────────────┐    ┌──────────────────┐
│ Sensor Simulator │    │ Actuator Monitor │
│  - Speed signal  │    │  - Brake PWM     │
│  - Controlled by │    │  - Measured by   │
│  - Test PC       │    │  - Test PC       │
└──────────────────┘    └──────────────────┘
```

---

### HIL Test Script (Python)

```python
#!/usr/bin/env python3
"""
Hardware-in-the-Loop (HIL) Test Script
EN 50128 Section 7.6 - Software/Hardware Integration Testing
"""

import serial
import time
import struct
import sys

class HILTestHarness:
    def __init__(self, target_serial_port, sil_level):
        self.sil_level = sil_level
        self.serial = serial.Serial(target_serial_port, 115200, timeout=1)
        self.test_results = []
        
    def send_command(self, command, data=None):
        """Send command to target hardware"""
        packet = struct.pack('<B', command)
        if data:
            packet += data
        self.serial.write(packet)
        
    def read_response(self, timeout=1.0):
        """Read response from target hardware"""
        start = time.time()
        response = b''
        while (time.time() - start) < timeout:
            if self.serial.in_waiting:
                response += self.serial.read(self.serial.in_waiting)
                if b'\\n' in response:
                    break
            time.sleep(0.01)
        return response.decode('utf-8').strip()
    
    def set_sensor_value(self, sensor_id, value):
        """Set sensor value via DAC or external simulator"""
        # Command: 0x01 = Set Sensor
        data = struct.pack('<BH', sensor_id, value)
        self.send_command(0x01, data)
        time.sleep(0.05)  # Allow settling time
    
    def read_actuator_value(self, actuator_id):
        """Read actuator value (e.g., PWM duty cycle)"""
        # Command: 0x02 = Read Actuator
        data = struct.pack('<B', actuator_id)
        self.send_command(0x02, data)
        
        response = self.read_response()
        try:
            return int(response)
        except:
            return None
    
    def test_sensor_to_actuator_response(self):
        """
        HIL Test: Verify sensor input produces correct actuator output
        """
        print("\\nHIL Test: Sensor → Actuator Response")
        print("="*60)
        
        test_cases = [
            {'speed_kmh': 0,   'expected_brake': 0,   'tolerance': 5},
            {'speed_kmh': 50,  'expected_brake': 0,   'tolerance': 5},
            {'speed_kmh': 100, 'expected_brake': 30,  'tolerance': 5},
            {'speed_kmh': 150, 'expected_brake': 60,  'tolerance': 5},
            {'speed_kmh': 200, 'expected_brake': 100, 'tolerance': 5},
        ]
        
        passed = 0
        failed = 0
        
        for tc in test_cases:
            # Convert speed to ADC value (0-3.3V = 0-250 km/h, 12-bit ADC)
            adc_value = int((tc['speed_kmh'] / 250.0) * 4095)
            
            # Set sensor value
            self.set_sensor_value(sensor_id=0, value=adc_value)
            
            # Wait for processing
            time.sleep(0.1)
            
            # Read actuator value
            brake_level = self.read_actuator_value(actuator_id=0)
            
            # Verify
            if brake_level is None:
                print(f"  Speed {tc['speed_kmh']} km/h: FAIL (no response)")
                failed += 1
                continue
            
            expected = tc['expected_brake']
            tolerance = tc['tolerance']
            
            if abs(brake_level - expected) <= tolerance:
                print(f"  Speed {tc['speed_kmh']:3d} km/h → Brake {brake_level:3d}%: PASS")
                passed += 1
            else:
                print(f"  Speed {tc['speed_kmh']:3d} km/h → Brake {brake_level:3d}%: FAIL (expected {expected}±{tolerance})")
                failed += 1
        
        print(f"\\nResult: {passed}/{len(test_cases)} PASS")
        
        self.test_results.append({
            'test_name': 'sensor_to_actuator_response',
            'passed': passed,
            'failed': failed,
            'total': len(test_cases)
        })
        
        return failed == 0
    
    def test_timing_requirements(self):
        """
        HIL Test: Verify real-time timing requirements on target hardware
        """
        print("\\nHIL Test: Timing Requirements")
        print("="*60)
        
        # Timing requirement: Sensor → Actuator response < 10 ms (SIL 3)
        max_latency_ms = 10 if self.sil_level >= 3 else 50
        
        iterations = 100
        latencies = []
        
        for i in range(iterations):
            # Send sensor value with timestamp
            start_time = time.time()
            self.set_sensor_value(sensor_id=0, value=2048)
            
            # Wait for actuator response
            brake_level = self.read_actuator_value(actuator_id=0)
            end_time = time.time()
            
            latency_ms = (end_time - start_time) * 1000
            latencies.append(latency_ms)
            
            time.sleep(0.02)  # 50 Hz test rate
        
        # Statistics
        avg_latency = sum(latencies) / len(latencies)
        max_latency = max(latencies)
        min_latency = min(latencies)
        
        print(f"  Iterations: {iterations}")
        print(f"  Average Latency: {avg_latency:.2f} ms")
        print(f"  Min Latency: {min_latency:.2f} ms")
        print(f"  Max Latency: {max_latency:.2f} ms")
        print(f"  Requirement: < {max_latency_ms} ms")
        
        if max_latency < max_latency_ms:
            print(f"  Result: PASS ✅")
            passed = True
        else:
            print(f"  Result: FAIL ❌ (max latency {max_latency:.2f} ms exceeds {max_latency_ms} ms)")
            passed = False
        
        self.test_results.append({
            'test_name': 'timing_requirements',
            'avg_latency_ms': avg_latency,
            'max_latency_ms': max_latency,
            'requirement_ms': max_latency_ms,
            'passed': passed
        })
        
        return passed
    
    def test_fault_injection(self):
        """
        HIL Test: Inject hardware faults and verify safe state
        """
        print("\\nHIL Test: Fault Injection")
        print("="*60)
        
        # Test 1: Sensor disconnection (ADC reads 0 or 4095)
        print("  Test: Sensor disconnection...")
        self.set_sensor_value(sensor_id=0, value=0)  # Simulate disconnected sensor
        time.sleep(0.1)
        
        brake_level = self.read_actuator_value(actuator_id=0)
        if brake_level == 100:
            print(f"    Sensor disconnected → Brake {brake_level}%: PASS (safe state)")
            fault_test_pass = True
        else:
            print(f"    Sensor disconnected → Brake {brake_level}%: FAIL (expected 100% brake)")
            fault_test_pass = False
        
        # Test 2: Sensor out of range (value > max valid)
        print("  Test: Sensor out of range...")
        self.set_sensor_value(sensor_id=0, value=4095)  # Max ADC value (invalid for sensor)
        time.sleep(0.1)
        
        brake_level = self.read_actuator_value(actuator_id=0)
        if brake_level == 100:
            print(f"    Sensor out of range → Brake {brake_level}%: PASS (safe state)")
        else:
            print(f"    Sensor out of range → Brake {brake_level}%: FAIL (expected 100% brake)")
            fault_test_pass = False
        
        self.test_results.append({
            'test_name': 'fault_injection',
            'passed': fault_test_pass
        })
        
        return fault_test_pass
    
    def generate_report(self, output_path):
        """Generate HIL test report (machine-readable JSON)"""
        import json
        from datetime import datetime
        
        report = {
            'project': 'Railway Braking System',
            'test_type': 'Hardware-in-the-Loop (HIL)',
            'sil_level': self.sil_level,
            'timestamp': datetime.now().isoformat(),
            'target_platform': 'STM32F407VGT6',
            'test_results': self.test_results,
            'summary': {
                'total_tests': len(self.test_results),
                'passed_tests': sum(1 for r in self.test_results if r.get('passed', False)),
                'failed_tests': sum(1 for r in self.test_results if not r.get('passed', True))
            }
        }
        
        with open(output_path, 'w') as f:
            json.dump(report, f, indent=2)
        
        print(f"\\nHIL Test Report: {output_path}")
        print(f"Total Tests: {report['summary']['total_tests']}")
        print(f"Passed: {report['summary']['passed_tests']}")
        print(f"Failed: {report['summary']['failed_tests']}")
        
        return report['summary']['failed_tests'] == 0

def main():
    if len(sys.argv) < 3:
        print("Usage: hil_test.py <SERIAL_PORT> <SIL_LEVEL>")
        print("Example: hil_test.py /dev/ttyUSB0 3")
        sys.exit(1)
    
    serial_port = sys.argv[1]
    sil_level = int(sys.argv[2])
    
    print("="*60)
    print("Hardware-in-the-Loop (HIL) Testing")
    print(f"Target: {serial_port}")
    print(f"SIL Level: {sil_level}")
    print("="*60)
    
    harness = HILTestHarness(serial_port, sil_level)
    
    # Run tests
    all_passed = True
    all_passed &= harness.test_sensor_to_actuator_response()
    all_passed &= harness.test_timing_requirements()
    all_passed &= harness.test_fault_injection()
    
    # Generate report
    success = harness.generate_report('evidence/integration/hil_test_report.json')
    
    if success and all_passed:
        print("\\n✅ ALL HIL TESTS PASSED")
        sys.exit(0)
    else:
        print("\\n❌ HIL TESTS FAILED")
        sys.exit(1)

if __name__ == '__main__':
    main()
```

**Usage**:

```bash
# Run HIL tests on target hardware
python3 tools/hil_test.py /dev/ttyUSB0 3

# Output:
# ============================================================
# Hardware-in-the-Loop (HIL) Testing
# Target: /dev/ttyUSB0
# SIL Level: 3
# ============================================================
# 
# HIL Test: Sensor → Actuator Response
# ============================================================
#   Speed   0 km/h → Brake   0%: PASS
#   Speed  50 km/h → Brake   0%: PASS
#   Speed 100 km/h → Brake  30%: PASS
#   Speed 150 km/h → Brake  60%: PASS
#   Speed 200 km/h → Brake 100%: PASS
# 
# Result: 5/5 PASS
# 
# HIL Test: Timing Requirements
# ============================================================
#   Iterations: 100
#   Average Latency: 4.23 ms
#   Min Latency: 3.85 ms
#   Max Latency: 5.67 ms
#   Requirement: < 10 ms
#   Result: PASS ✅
# 
# HIL Test: Fault Injection
# ============================================================
#   Test: Sensor disconnection...
#     Sensor disconnected → Brake 100%: PASS (safe state)
#   Test: Sensor out of range...
#     Sensor out of range → Brake 100%: PASS (safe state)
# 
# HIL Test Report: evidence/integration/hil_test_report.json
# Total Tests: 3
# Passed: 3
# Failed: 0
# 
# ✅ ALL HIL TESTS PASSED
```

---

## Timing and Performance Validation

### Timing Analysis on Target Hardware

**SIL 3-4 Requirement**: Real-time performance must be validated on target hardware (not simulation)

```c
// File: timing_analysis.c
// Timing validation on target hardware

#include "hal.h"
#include "brake_controller.h"
#include "sensor_service.h"
#include <stdio.h>

#define NUM_SAMPLES 1000

typedef struct {
    uint32_t min_us;
    uint32_t max_us;
    uint32_t avg_us;
    uint32_t samples[NUM_SAMPLES];
} timing_stats_t;

void measure_execution_time(void (*function)(void), timing_stats_t* stats) {
    uint64_t total_us = 0;
    stats->min_us = UINT32_MAX;
    stats->max_us = 0;
    
    for (int i = 0; i < NUM_SAMPLES; i++) {
        uint32_t start = hal_system_get_timestamp_us();
        function();  // Execute function under test
        uint32_t end = hal_system_get_timestamp_us();
        
        uint32_t duration = end - start;
        stats->samples[i] = duration;
        
        if (duration < stats->min_us) stats->min_us = duration;
        if (duration > stats->max_us) stats->max_us = duration;
        total_us += duration;
    }
    
    stats->avg_us = (uint32_t)(total_us / NUM_SAMPLES);
}

void test_brake_controller_timing(void) {
    timing_stats_t stats;
    
    printf("Timing Analysis: brake_controller_compute()\\n");
    printf("==========================================================\\n");
    
    // Wrap function for measurement
    void brake_controller_wrapper(void) {
        brake_command_t command;
        brake_controller_compute(&command);
    }
    
    measure_execution_time(brake_controller_wrapper, &stats);
    
    printf("Samples: %d\\n", NUM_SAMPLES);
    printf("Min: %lu µs\\n", stats.min_us);
    printf("Max: %lu µs\\n", stats.max_us);
    printf("Avg: %lu µs\\n", stats.avg_us);
    
    // Requirement: < 1000 µs (1 ms) for SIL 3
    uint32_t requirement_us = 1000;
    
    if (stats.max_us < requirement_us) {
        printf("Result: PASS ✅ (max %lu µs < %lu µs)\\n", stats.max_us, requirement_us);
    } else {
        printf("Result: FAIL ❌ (max %lu µs >= %lu µs)\\n", stats.max_us, requirement_us);
    }
}

void test_end_to_end_latency(void) {
    printf("\\nTiming Analysis: End-to-End Latency\\n");
    printf("==========================================================\\n");
    
    // Measure: Sensor read → Brake compute → Actuator command
    void end_to_end_wrapper(void) {
        sensor_service_update();
        
        brake_command_t command;
        brake_controller_compute(&command);
        
        brake_service_apply(command.brake_level);
    }
    
    timing_stats_t stats;
    measure_execution_time(end_to_end_wrapper, &stats);
    
    printf("Samples: %d\\n", NUM_SAMPLES);
    printf("Min: %lu µs\\n", stats.min_us);
    printf("Max: %lu µs\\n", stats.max_us);
    printf("Avg: %lu µs\\n", stats.avg_us);
    
    // Requirement: < 10000 µs (10 ms) for SIL 3
    uint32_t requirement_us = 10000;
    
    if (stats.max_us < requirement_us) {
        printf("Result: PASS ✅\\n");
    } else {
        printf("Result: FAIL ❌\\n");
    }
}

int main(void) {
    hal_system_init();
    sensor_service_init();
    brake_controller_init();
    
    test_brake_controller_timing();
    test_end_to_end_latency();
    
    return 0;
}
```

**Build and Run on Target**:

```bash
# Build timing analysis for target
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O2 -g \
    -o build/timing_analysis.elf \
    timing_analysis.c brake_controller.c sensor_service.c hal_target.c

# Flash to target
./setup_target_hardware.sh

# Run and collect results (via semihosting or UART)
arm-none-eabi-gdb build/timing_analysis.elf \
    -ex "target extended-remote localhost:3333" \
    -ex "load" \
    -ex "monitor reset halt" \
    -ex "continue" | tee timing_analysis_results.txt

# Output:
# Timing Analysis: brake_controller_compute()
# ==========================================================
# Samples: 1000
# Min: 85 µs
# Max: 142 µs
# Avg: 95 µs
# Result: PASS ✅ (max 142 µs < 1000 µs)
# 
# Timing Analysis: End-to-End Latency
# ==========================================================
# Samples: 1000
# Min: 456 µs
# Max: 523 µs
# Avg: 478 µs
# Result: PASS ✅
```

---

## Safety Mechanisms Validation

### Watchdog Timer Testing

**SIL 3-4 Requirement**: Watchdog timer MUST be tested on target hardware

```c
// File: test_watchdog.c
// Validate watchdog timer operation on target hardware

#include "hal.h"
#include <stdio.h>

void test_watchdog_triggers_reset(void) {
    printf("\\nWatchdog Test: Trigger Reset\\n");
    printf("======================================\\n");
    
    // Enable watchdog (1 second timeout)
    hal_watchdog_init(1000);
    hal_watchdog_start();
    
    printf("Watchdog started (1 second timeout)\\n");
    printf("NOT refreshing watchdog...\\n");
    
    // Do NOT refresh watchdog → should reset after 1 second
    uint32_t start = hal_system_get_timestamp_us();
    while (1) {
        uint32_t elapsed_ms = (hal_system_get_timestamp_us() - start) / 1000;
        
        if (elapsed_ms % 100 == 0) {
            printf("Elapsed: %lu ms\\n", elapsed_ms);
        }
        
        // After 1 second, watchdog should reset the system
        // This code should NEVER print "2000 ms"
        if (elapsed_ms >= 2000) {
            printf("ERROR: Watchdog did NOT reset!\\n");
            break;
        }
    }
}

void test_watchdog_refresh_prevents_reset(void) {
    printf("\\nWatchdog Test: Refresh Prevents Reset\\n");
    printf("======================================\\n");
    
    // Enable watchdog (1 second timeout)
    hal_watchdog_init(1000);
    hal_watchdog_start();
    
    printf("Watchdog started (1 second timeout)\\n");
    printf("Refreshing watchdog every 500 ms...\\n");
    
    // Refresh watchdog periodically → should NOT reset
    for (int i = 0; i < 10; i++) {
        hal_delay_ms(500);
        hal_watchdog_refresh();
        printf("Refresh %d: OK\\n", i + 1);
    }
    
    printf("Result: PASS ✅ (no reset for 5 seconds)\\n");
    
    hal_watchdog_stop();
}

int main(void) {
    hal_system_init();
    
    // Check if reset was caused by watchdog
    uint32_t reset_reason = hal_system_get_reset_reason();
    
    if (reset_reason == RESET_REASON_WATCHDOG) {
        printf("\\n✅ Previous test: Watchdog reset detected (PASS)\\n");
        
        // Now test that refresh prevents reset
        test_watchdog_refresh_prevents_reset();
        
    } else {
        printf("\\nStarting watchdog tests...\\n");
        
        // Test 1: Watchdog triggers reset (this WILL reset the system)
        test_watchdog_triggers_reset();
    }
    
    return 0;
}
```

**Expected Behavior**:

```
# First run: Tests that watchdog triggers reset
Starting watchdog tests...

Watchdog Test: Trigger Reset
======================================
Watchdog started (1 second timeout)
NOT refreshing watchdog...
Elapsed: 100 ms
Elapsed: 200 ms
Elapsed: 300 ms
Elapsed: 400 ms
Elapsed: 500 ms
Elapsed: 600 ms
Elapsed: 700 ms
Elapsed: 800 ms
Elapsed: 900 ms
[SYSTEM RESET BY WATCHDOG]

# Second run (after watchdog reset): Tests that refresh prevents reset
✅ Previous test: Watchdog reset detected (PASS)

Watchdog Test: Refresh Prevents Reset
======================================
Watchdog started (1 second timeout)
Refreshing watchdog every 500 ms...
Refresh 1: OK
Refresh 2: OK
Refresh 3: OK
Refresh 4: OK
Refresh 5: OK
Refresh 6: OK
Refresh 7: OK
Refresh 8: OK
Refresh 9: OK
Refresh 10: OK
Result: PASS ✅ (no reset for 5 seconds)
```

---

## Interrupt and Concurrency Testing

### Interrupt Timing Validation

```c
// File: test_interrupts.c
// Validate interrupt handling on target hardware

#include "hal.h"
#include <stdio.h>

volatile uint32_t interrupt_count = 0;
volatile uint32_t max_interrupt_latency_us = 0;

// Timer interrupt handler (1 kHz = 1 ms period)
void timer_interrupt_handler(void) {
    static uint32_t last_interrupt_time = 0;
    
    uint32_t current_time = hal_system_get_timestamp_us();
    
    if (last_interrupt_time > 0) {
        // Measure interrupt latency (should be ~1000 µs)
        uint32_t latency = current_time - last_interrupt_time;
        
        if (latency > max_interrupt_latency_us) {
            max_interrupt_latency_us = latency;
        }
    }
    
    last_interrupt_time = current_time;
    interrupt_count++;
}

void test_interrupt_timing(void) {
    printf("\\nInterrupt Timing Test\\n");
    printf("======================================\\n");
    
    // Configure timer interrupt (1 kHz)
    hal_timer_init(1000);  // 1 kHz = 1 ms period
    hal_interrupt_register_handler(TIM2_IRQn, timer_interrupt_handler);
    hal_interrupt_enable(TIM2_IRQn);
    hal_timer_start();
    
    printf("Timer interrupt started (1 kHz)\\n");
    printf("Measuring interrupt timing...\\n");
    
    // Run for 5 seconds
    hal_delay_ms(5000);
    
    hal_timer_stop();
    hal_interrupt_disable(TIM2_IRQn);
    
    printf("\\nResults:\\n");
    printf("  Interrupts: %lu\\n", interrupt_count);
    printf("  Expected: ~5000 (1 kHz × 5 sec)\\n");
    printf("  Max Latency: %lu µs\\n", max_interrupt_latency_us);
    printf("  Expected: ~1000 µs (1 ms period)\\n");
    
    // Verify interrupt count (allow 1% tolerance)
    uint32_t expected_count = 5000;
    uint32_t tolerance = 50;  // 1%
    
    if (interrupt_count >= (expected_count - tolerance) &&
        interrupt_count <= (expected_count + tolerance)) {
        printf("  Interrupt Count: PASS ✅\\n");
    } else {
        printf("  Interrupt Count: FAIL ❌\\n");
    }
    
    // Verify interrupt latency (allow 10% tolerance for jitter)
    uint32_t expected_latency = 1000;
    uint32_t latency_tolerance = 100;  // 10%
    
    if (max_interrupt_latency_us >= (expected_latency - latency_tolerance) &&
        max_interrupt_latency_us <= (expected_latency + latency_tolerance)) {
        printf("  Interrupt Latency: PASS ✅\\n");
    } else {
        printf("  Interrupt Latency: FAIL ❌\\n");
    }
}

int main(void) {
    hal_system_init();
    test_interrupt_timing();
    return 0;
}
```

---

## Hardware-Specific Defect Detection

### Memory Corruption Detection (SIL 2+)

```c
// File: test_memory_corruption.c
// Detect memory corruption on target hardware (stack overflow, buffer overflow)

#include "hal.h"
#include <stdio.h>
#include <string.h>

#define STACK_CANARY 0xDEADBEEF

// Stack canary (guard value to detect stack overflow)
static uint32_t stack_canary = STACK_CANARY;

void test_stack_overflow_detection(void) {
    printf("\\nStack Overflow Detection Test\\n");
    printf("======================================\\n");
    
    // Verify canary intact before test
    if (stack_canary != STACK_CANARY) {
        printf("ERROR: Stack canary corrupted BEFORE test!\\n");
        return;
    }
    
    printf("Stack canary: 0x%08lX (intact)\\n", stack_canary);
    
    // Intentionally overflow stack (carefully controlled)
    // WARNING: This test WILL crash if MPU not configured
    
    #ifdef ENABLE_STACK_OVERFLOW_TEST
    uint8_t large_buffer[10000];  // Large stack allocation
    memset(large_buffer, 0xFF, sizeof(large_buffer));
    
    // Check if canary still intact
    if (stack_canary != STACK_CANARY) {
        printf("Stack overflow DETECTED (canary corrupted)\\n");
        printf("Result: PASS ✅ (overflow detected)\\n");
    } else {
        printf("Stack overflow NOT detected\\n");
        printf("Result: FAIL ❌ (overflow not detected)\\n");
    }
    #else
    printf("Stack overflow test SKIPPED (would crash system)\\n");
    printf("Manual test required with MPU enabled\\n");
    #endif
}

void test_buffer_overflow_detection(void) {
    printf("\\nBuffer Overflow Detection Test\\n");
    printf("======================================\\n");
    
    uint8_t buffer[10];
    uint32_t guard_value_before = 0xCAFEBABE;
    uint32_t guard_value_after = 0xCAFEBABE;
    
    // Guard values around buffer
    printf("Guard values: 0x%08lX, 0x%08lX\\n", guard_value_before, guard_value_after);
    
    // Safe write (within bounds)
    memset(buffer, 0xAA, sizeof(buffer));
    
    // Verify guard values intact
    if (guard_value_before == 0xCAFEBABE && guard_value_after == 0xCAFEBABE) {
        printf("Safe write: PASS ✅ (guard values intact)\\n");
    } else {
        printf("Safe write: FAIL ❌ (guard values corrupted)\\n");
    }
    
    // UNSAFE write (overflow) - ONLY if testing in controlled environment
    #ifdef ENABLE_OVERFLOW_TEST
    memset(buffer, 0xBB, sizeof(buffer) + 10);  // INTENTIONAL OVERFLOW
    
    if (guard_value_before != 0xCAFEBABE || guard_value_after != 0xCAFEBABE) {
        printf("Overflow detected: PASS ✅ (guard values corrupted as expected)\\n");
    } else {
        printf("Overflow NOT detected: FAIL ❌\\n");
    }
    #endif
}

int main(void) {
    hal_system_init();
    
    test_stack_overflow_detection();
    test_buffer_overflow_detection();
    
    return 0;
}
```

---

## Target Platform Validation

### Cross-Compiler Verification

**Objective**: Verify that cross-compiled code behaves identically on host and target

```bash
#!/bin/bash
# verify_cross_compilation.sh
# Compare behavior on host (simulator) vs target hardware

set -e

TEST_NAME="sensor_driver_test"

echo "Cross-Compilation Verification"
echo "======================================================================="

# 1. Build for host (x86_64)
echo "1. Building for host (x86_64)..."
gcc -DHAL_SIMULATOR -o build/host_$TEST_NAME \
    test_sensor_driver.c sensor_driver.c hal_simulator.c unity.c

# 2. Build for target (ARM Cortex-M4)
echo "2. Building for target (ARM Cortex-M4)..."
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -DHAL_TARGET \
    -o build/target_$TEST_NAME.elf \
    test_sensor_driver.c sensor_driver.c hal_target.c unity.c

# 3. Run on host
echo "3. Running on host..."
./build/host_$TEST_NAME > build/host_results.txt
HOST_RESULT=$?

# 4. Run on target
echo "4. Running on target..."
./setup_target_hardware.sh
arm-none-eabi-gdb build/target_$TEST_NAME.elf \
    -ex "target extended-remote localhost:3333" \
    -ex "load" \
    -ex "monitor reset halt" \
    -ex "continue" > build/target_results.txt
TARGET_RESULT=$?

# 5. Compare results
echo "5. Comparing results..."

if [ $HOST_RESULT -eq $TARGET_RESULT ]; then
    echo "   ✅ Exit codes match: $HOST_RESULT"
else
    echo "   ❌ Exit codes differ: host=$HOST_RESULT, target=$TARGET_RESULT"
    exit 1
fi

# Compare test output (ignore timing-related differences)
grep "Tests.*Failures" build/host_results.txt > build/host_summary.txt
grep "Tests.*Failures" build/target_results.txt > build/target_summary.txt

if diff -q build/host_summary.txt build/target_summary.txt; then
    echo "   ✅ Test results match"
else
    echo "   ❌ Test results differ"
    echo "   Host:   $(cat build/host_summary.txt)"
    echo "   Target: $(cat build/target_summary.txt)"
    exit 1
fi

echo ""
echo "======================================================================="
echo "Cross-Compilation Verification: PASS ✅"
echo "======================================================================="
```

---

## Tool Integration for HW/SW Testing

### Working Tools

**Cross-Compilation**:
- `arm-none-eabi-gcc` - ARM GCC cross-compiler
- `arm-none-eabi-gdb` - ARM GDB debugger
- `openocd` - On-chip debugger (ST-Link, J-Link support)

**Hardware Testing**:
- `Python + pyserial` - HIL test automation
- `GDB + semihosting` - On-target test execution with console output

**Timing Analysis**:
- HAL timestamp functions (`hal_system_get_timestamp_us()`)
- Target hardware timers (TIMx on STM32)

**Safety Testing**:
- Watchdog timer (IWDG on STM32)
- Memory Protection Unit (MPU) - stack overflow detection

**Example Workflow**:

```bash
# 1. Build for target
make PLATFORM=target all

# 2. Setup target hardware
./setup_target_hardware.sh

# 3. Run HIL tests
python3 tools/hil_test.py /dev/ttyUSB0 3

# 4. Collect evidence
./tools/collect_hwsw_integration_evidence.sh

# Output:
#   evidence/integration/hil_test_report.json
#   evidence/integration/timing_analysis_results.txt
#   evidence/integration/watchdog_test_results.txt
#   evidence/integration/Software_HW_Integration_Test_Report.md
```

---

## Summary

This hardware/software integration workflow provides:

1. **HAL Design**: Portable abstraction layer with stub/simulator/target implementations
2. **Progressive Integration**: Simulator → Target progression
3. **HIL Testing**: Automated test execution on real hardware
4. **Timing Validation**: Real-time performance measurement on target
5. **Safety Mechanisms**: Watchdog, MPU, memory protection validation
6. **Interrupt Testing**: Timing and concurrency validation
7. **Cross-Compilation Verification**: Host vs target behavior comparison
8. **Tool Integration**: openocd, arm-none-eabi-gcc, Python HIL automation

**EN 50128 Compliance**: Section 7.6.1.2, 7.6.4.7-7.6.4.10

**Next Steps**:
1. Review `workflows/interface-testing-workflow.md` for detailed interface test patterns
2. Review `workflows/performance-testing-workflow.md` for comprehensive performance validation

**Standard References**:
- EN 50128 Section 7.6.1.2: "...software and hardware interact correctly..."
- EN 50128 Section 7.6.4.7-7.6.4.10: Software/Hardware Integration Test Report
- EN 50128 Table A.6: Integration Techniques
