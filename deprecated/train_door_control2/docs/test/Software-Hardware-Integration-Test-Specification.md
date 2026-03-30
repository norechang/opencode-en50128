# Software/Hardware Integration Test Specification
## Train Door Control System

---

### Document Control

| Field | Details |
|-------|---------|
| **Document ID** | DOC-HWINTTEST-2026-001 |
| **Version** | 1.0 |
| **Date** | 2026-02-21 |
| **Status** | Draft |
| **Classification** | Internal |
| **SIL Level** | SIL 3 |
| **Project** | Train Door Control System |
| **Organization** | Railway Safety Systems Inc. |

---

### Approval

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author (Integrator)** | [Integrator Name] | | |
| **Reviewer (Verifier)** | [Verifier Name] | | |
| **Approver (SW Manager)** | [SW Manager Name] | | |

---

### Document History

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2026-02-21 | Integrator | Initial version - SW/HW Integration test specification |

---

### Referenced Documents

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-SRS-2026-001 | Software Requirements Specification | 1.0 |
| DOC-SAS-2026-001 | Software Architecture Specification | 1.0 |
| DOC-SDS-2026-001 | Software Design Specification | 1.0 |
| DOC-INTERFACES-2026-001 | Software Interface Specifications | 1.0 |
| DOC-INTTEST-2026-001 | Software Integration Test Specification | 1.0 |
| DOC-HAZ-2026-001 | Hazard Log | 1.0 |
| EN 50128:2011 | Railway Applications - Software for Railway Control and Protection Systems | 2011 |

---

## Table of Contents

1. [Introduction](#1-introduction)
2. [SW/HW Integration Strategy](#2-swhw-integration-strategy)
3. [Hardware Test Environment](#3-hardware-test-environment)
4. [Hardware Interface Test Cases](#4-hardware-interface-test-cases)
5. [Sensor Integration Test Cases](#5-sensor-integration-test-cases)
6. [Actuator Integration Test Cases](#6-actuator-integration-test-cases)
7. [Communication Interface Test Cases](#7-communication-interface-test-cases)
8. [Real-Time Performance Tests](#8-real-time-performance-tests)
9. [Hardware Safety Tests](#9-hardware-safety-tests)
10. [Test Traceability Matrix](#10-test-traceability-matrix)
11. [Test Execution Schedule](#11-test-execution-schedule)
12. [EN 50128 Compliance](#12-en-50128-compliance)

---

## 1. Introduction

### 1.1 Purpose

This document specifies the software/hardware integration testing for the Train Door Control System. It defines test cases, procedures, and acceptance criteria to verify correct interaction between software modules and physical hardware interfaces in accordance with EN 50128:2011 Section 7.6.

### 1.2 Scope

This specification covers:
- Hardware interface testing (GPIO, ADC, PWM, CAN, UART)
- Integration with real sensors (position, obstacle, speed, emergency)
- Integration with real actuators (door motors, lock solenoids)
- Real-time performance on target hardware (ARM Cortex-M4)
- Hardware fault injection and recovery
- Safety-critical hardware interlocks
- EMI/EMC considerations (reference only)

**Out of Scope**:
- Software-only integration tests (covered by DOC-INTTEST-2026-001)
- Hardware design verification (covered by hardware test specification)
- System validation tests (covered by Software Validation Test Specification)

### 1.3 Target Hardware Platform

**Microcontroller**: ARM Cortex-M4 (STM32F407 or equivalent)
- **CPU**: 168 MHz, 32-bit RISC
- **RAM**: 192 KB SRAM
- **Flash**: 1 MB
- **Peripherals**: 12-bit ADC, timers with PWM, CAN 2.0B, UART, GPIO

**Sensors**:
- Door position sensors (analog, 0-3.3V, 12-bit ADC)
- Obstacle detection sensors (digital GPIO, infrared + pressure)
- Speed sensors (CAN bus, 20 Hz update)
- Emergency release handle (digital GPIO, hardware interrupt)

**Actuators**:
- Door motors (PWM-controlled, 24V DC, H-bridge driver)
- Door lock solenoids (digital GPIO, 12V DC)

**Communication**:
- CAN 2.0B transceiver (500 kbps)
- UART (115200 baud, diagnostic port)

### 1.4 EN 50128 Requirements

**SIL 3 Hardware Integration Testing Requirements:**
- **Functional and Black-box Testing**: Highly Recommended (Table A.6)
- **Performance Testing on Target**: Mandatory (Table A.18)
- **Interface Testing**: Highly Recommended (Table A.6)
- **Hardware Fault Injection**: Highly Recommended (SIL 3)
- **Real-Time Timing Verification**: Mandatory (SIL 3)

---

## 2. SW/HW Integration Strategy

### 2.1 Integration Approach

**Strategy**: **Incremental Bottom-Up Integration with Real Hardware**

**Phase 1: Hardware Interface Layer**
- GPIO initialization and control
- ADC reading with real analog sensors
- PWM generation with oscilloscope verification
- CAN transceiver with bus analyzer
- UART communication with terminal

**Phase 2: Sensor Integration**
- Position sensors with mechanical fixture
- Obstacle sensors with physical test objects
- Speed sensor emulation via CAN
- Emergency handle with button fixture

**Phase 3: Actuator Integration**
- Motor control with load testing
- Lock solenoid with mechanical verification
- Combined sensor + actuator closed-loop

**Phase 4: Communication Integration**
- CAN bus with external CAN nodes
- UART diagnostic interface
- Real-time message timing

**Phase 5: Full System on Target Hardware**
- Complete system with all hardware interfaces
- Real-time performance measurement
- Hardware fault injection
- Safety interlock verification

### 2.2 Test Equipment Required

**Measurement Equipment**:
- Oscilloscope (4-channel, 100 MHz bandwidth)
- Logic analyzer (16-channel, 100 MS/s)
- CAN bus analyzer (Vector CANalyzer or equivalent)
- Multimeter (DMM)
- Power supply (0-30V, 5A)
- Function generator (for sensor simulation)

**Test Fixtures**:
- Door motor test fixture (mechanical load, position measurement)
- Sensor interface board (analog voltage generation, digital I/O)
- CAN bus test node (command generator, message logger)
- Fault injection board (sensor disconnect, power glitch, EMI)

**Software Tools**:
- Debugger (J-Link, ST-Link)
- GDB + OpenOCD (on-chip debugging)
- Serial terminal (PuTTY, TeraTerm)
- CAN trace analysis tools

### 2.3 Test Environment Setup

**Hardware Configuration**:
```
┌────────────────────────────────────────────────────┐
│  STM32F407 Development Board                      │
│  (ARM Cortex-M4, 168 MHz)                         │
│                                                    │
│  [ADC] ◄──── Position Sensors (analog 0-3.3V)    │
│  [GPIO] ◄─── Obstacle Sensors (digital, IR)      │
│  [GPIO] ◄─── Emergency Handle (interrupt)         │
│  [PWM] ─────► Motor Driver (H-bridge, 10 kHz)    │
│  [GPIO] ────► Lock Solenoid Driver (12V relay)   │
│  [CAN] ◄───► CAN Transceiver (500 kbps)          │
│  [UART] ────► Serial Console (115200 baud)        │
│  [SWD] ◄───► Debugger (J-Link/ST-Link)           │
└────────────────────────────────────────────────────┘
         │              │               │
         ▼              ▼               ▼
   Oscilloscope   CAN Analyzer   Logic Analyzer
```

---

## 3. Hardware Test Environment

### 3.1 GPIO Interface Test Setup

**Configuration**:
- **Digital Outputs**: 6 GPIO pins (motor direction, lock control, status LEDs)
- **Digital Inputs**: 8 GPIO pins (obstacle sensors, emergency handle, buttons)
- **Pull-up/Pull-down**: Configured per signal type
- **Interrupt Capability**: Emergency handle (rising edge)

**Measurement**:
- Logic analyzer on all GPIO pins
- Oscilloscope for timing verification
- Multimeter for voltage levels

### 3.2 ADC Interface Test Setup

**Configuration**:
- **ADC Channels**: 2 channels (left/right position sensors)
- **Resolution**: 12-bit (0-4095 counts)
- **Sampling Rate**: 100 Hz (10ms period)
- **Reference Voltage**: 3.3V (internal VREF+)
- **Input Range**: 0-3.3V

**Sensor Simulation**:
- Precision voltage source (0-3.3V, ±1% accuracy)
- Function generator for dynamic testing
- Potentiometer for manual position control

### 3.3 PWM Interface Test Setup

**Configuration**:
- **PWM Channels**: 2 channels (left/right door motors)
- **Frequency**: 10 kHz (motor driver requirement)
- **Duty Cycle**: 0-100%
- **Timer**: TIM1 (advanced timer, 168 MHz clock)

**Measurement**:
- Oscilloscope (duty cycle, frequency, rise/fall time)
- Motor load test fixture (torque, current draw)

### 3.4 CAN Bus Test Setup

**Configuration**:
- **CAN Controller**: CAN1 peripheral
- **Bit Rate**: 500 kbps
- **Filters**: Accept IDs 0x100-0x1FF
- **TX/RX Interrupts**: Enabled
- **Transceiver**: MCP2551 or TJA1050

**Test Equipment**:
- CAN bus analyzer (Vector CANalyzer)
- CAN message generator (CANoe or custom node)
- 120Ω termination resistors

### 3.5 UART Test Setup

**Configuration**:
- **UART**: USART1
- **Baud Rate**: 115200 baud
- **Format**: 8N1 (8 data, no parity, 1 stop)
- **Flow Control**: None

**Test Equipment**:
- Serial terminal (PuTTY)
- USB-to-UART adapter (FTDI, CP2102)

---

## 4. Hardware Interface Test Cases

### 4.1 GPIO Interface Tests

---

#### TC-HWINT-GPIO-001: GPIO Output Initialization

**Objective**: Verify GPIO outputs initialize to safe states.

**Hardware Under Test**: STM32F407 GPIO ports

**Requirements Traced**: REQ-IMPL-001, REQ-SAFE-001

**Preconditions**:
- Target hardware powered off
- Logic analyzer connected to all GPIO outputs

**Test Steps**:
1. Power on target hardware
2. Monitor GPIO states during boot
3. Verify motor direction outputs = LOW (stopped)
4. Verify lock solenoid output = HIGH (engaged)
5. Verify status LEDs = OFF
6. Measure GPIO voltage levels
7. Verify no glitches during initialization

**Expected Results**:
- Motor direction GPIOs: 0V ± 0.2V (LOW)
- Lock solenoid GPIO: 3.3V ± 0.2V (HIGH, engaged)
- Status LED GPIOs: 0V (OFF)
- Initialization time < 100ms
- No glitches > 1µs detected

**Pass/Fail Criteria**: All GPIO outputs in safe states, voltage levels correct, no glitches.

---

#### TC-HWINT-GPIO-002: GPIO Output Control

**Objective**: Verify software can control GPIO outputs correctly.

**Hardware Under Test**: GPIO outputs, MOD-006 (Actuator HAL)

**Requirements Traced**: REQ-IF-HW-003, REQ-IF-HW-004

**Preconditions**:
- System initialized
- Oscilloscope connected to motor direction GPIO

**Test Steps**:
1. Call `actuator_hal_set_door_pwm(DOOR_SIDE_LEFT, 50)` (50% duty, forward)
2. Verify motor direction GPIO = HIGH
3. Measure GPIO switching time
4. Call `actuator_hal_set_door_pwm(DOOR_SIDE_LEFT, -50)` (50% duty, reverse)
5. Verify motor direction GPIO = LOW
6. Measure GPIO switching time
7. Call `actuator_hal_set_door_lock(DOOR_SIDE_LEFT, true)` (engage lock)
8. Verify lock GPIO = HIGH
9. Measure GPIO switching time

**Expected Results**:
- Motor direction GPIO switches correctly (HIGH/LOW)
- Lock GPIO switches correctly (HIGH = engaged)
- GPIO switching time < 1µs
- Output voltage levels: HIGH = 3.3V ± 0.2V, LOW = 0V ± 0.2V

**Pass/Fail Criteria**: Correct GPIO control, switching time < 1µs, voltage levels correct.

---

#### TC-HWINT-GPIO-003: GPIO Input Reading

**Objective**: Verify software reads GPIO inputs correctly.

**Hardware Under Test**: GPIO inputs, MOD-007 (Sensor HAL)

**Requirements Traced**: REQ-IF-HW-005, REQ-IF-HW-006

**Preconditions**:
- System initialized
- GPIO inputs connected to test fixture

**Test Steps**:
1. Set obstacle sensor GPIO to HIGH (3.3V)
2. Call `sensor_hal_read_obstacle(DOOR_SIDE_LEFT)`
3. Verify return value = `OBSTACLE_CLEAR`
4. Set obstacle sensor GPIO to LOW (0V)
5. Call `sensor_hal_read_obstacle(DOOR_SIDE_LEFT)`
6. Verify return value = `OBSTACLE_DETECTED`
7. Measure input reading latency
8. Test with intermediate voltages (1.0V, 2.0V, 2.5V)
9. Verify logic threshold = 1.65V ± 0.2V

**Expected Results**:
- HIGH (> 2.0V) read as logic 1
- LOW (< 0.8V) read as logic 0
- Intermediate voltages handled per threshold
- Reading latency < 10µs
- No false detections due to noise

**Pass/Fail Criteria**: Correct GPIO input reading, latency < 10µs, proper thresholds.

---

#### TC-HWINT-GPIO-004: GPIO Interrupt Handling

**Objective**: Verify GPIO interrupt (emergency handle) triggers correctly.

**Hardware Under Test**: GPIO with EXTI interrupt, emergency handle input

**Requirements Traced**: REQ-IF-HW-012, REQ-FUNC-004

**Preconditions**:
- System initialized
- Emergency handle GPIO configured for rising edge interrupt
- Oscilloscope connected to GPIO and ISR flag

**Test Steps**:
1. Set emergency handle GPIO to LOW (0V)
2. Verify no interrupt triggered
3. Apply rising edge (LOW → HIGH transition, <10ns rise time)
4. Start timer
5. Verify interrupt service routine (ISR) executes
6. Stop timer when ISR completes
7. Measure interrupt latency (edge to ISR entry)
8. Verify emergency event logged
9. Repeat test 100 times for consistency

**Expected Results**:
- Interrupt triggered on rising edge
- Interrupt latency: mean = 5-10µs, max ≤ 20µs
- ISR execution time < 50µs
- 100% interrupt detection rate (100/100 tests)
- Emergency event logged every time

**Pass/Fail Criteria**: Interrupt latency ≤ 20µs, 100% detection rate.

---

### 4.2 ADC Interface Tests

---

#### TC-HWINT-ADC-001: ADC Initialization and Configuration

**Objective**: Verify ADC hardware configured correctly.

**Hardware Under Test**: STM32 ADC1, ADC2

**Requirements Traced**: REQ-IF-HW-001, REQ-IF-HW-002

**Preconditions**:
- Target hardware powered on
- ADC inputs disconnected (floating)

**Test Steps**:
1. Call `sensor_hal_init()`
2. Read ADC configuration registers
3. Verify ADC resolution = 12-bit (0-4095)
4. Verify ADC reference voltage = 3.3V (VREF+)
5. Verify sampling time = 15 cycles (1.8µs at 84 MHz)
6. Verify conversion mode = continuous
7. Measure ADC clock frequency

**Expected Results**:
- ADC resolution: 12-bit
- ADC clock: 10.5 MHz (84 MHz / 8 prescaler)
- Sampling time: 1.8µs
- Total conversion time: 2.0µs (15 + 12 cycles)
- Reference voltage: 3.3V ± 0.05V

**Pass/Fail Criteria**: ADC configuration correct, timing parameters met.

---

#### TC-HWINT-ADC-002: ADC Position Sensor Reading (Static)

**Objective**: Verify ADC reads position sensor voltage accurately.

**Hardware Under Test**: ADC channel, position sensor input

**Requirements Traced**: REQ-IF-HW-001, REQ-FUNC-005

**Preconditions**:
- System initialized
- Precision voltage source connected to ADC input

**Test Steps**:
1. Set voltage source to 0.0V (fully closed)
2. Call `sensor_hal_read_position(DOOR_SIDE_LEFT, &position_raw)`
3. Verify ADC value = 0 ± 10 counts (0.8% error)
4. Calculate position percentage = (ADC / 4095) * 100
5. Verify position = 0 ± 2%
6. Set voltage to 1.65V (50% open)
7. Read ADC, verify = 2048 ± 20 counts
8. Verify position = 50 ± 2%
9. Set voltage to 3.3V (100% open)
10. Read ADC, verify = 4095 ± 10 counts
11. Verify position = 100 ± 2%
12. Repeat at 0.33V, 0.66V, 1.0V, 2.0V, 2.64V, 2.97V
13. Calculate linearity error

**Expected Results**:
- ADC values within ± 20 counts (0.5%) of expected
- Position percentages within ± 2%
- Linearity error < 1% (INL < 10 LSB)
- No stuck bits or missing codes

**Pass/Fail Criteria**: ADC readings within ± 2%, linearity < 1%.

---

#### TC-HWINT-ADC-003: ADC Position Sensor Reading (Dynamic)

**Objective**: Verify ADC tracks changing sensor voltage.

**Hardware Under Test**: ADC with real position sensor or function generator

**Requirements Traced**: REQ-IF-HW-001, REQ-PERF-001

**Preconditions**:
- System initialized
- Function generator connected (0-3.3V, 0.5 Hz sine wave)

**Test Steps**:
1. Configure function generator: 0-3.3V, 0.5 Hz sine wave
2. Start continuous ADC sampling at 100 Hz (10ms period)
3. Record 500 samples (5 seconds, 5 complete cycles)
4. Calculate position values from ADC readings
5. Verify position follows sine wave (0% → 100% → 0%)
6. Measure sampling jitter (time between samples)
7. Analyze signal-to-noise ratio (SNR)
8. Check for aliasing or missed samples

**Expected Results**:
- Smooth position curve matching sine wave
- Sampling rate: 100 Hz ± 1 Hz
- Sampling jitter: < 1ms
- SNR > 60 dB (10 bits ENOB effective)
- No missed samples (500/500 captured)

**Pass/Fail Criteria**: Sampling rate accurate, jitter < 1ms, no missed samples.

---

#### TC-HWINT-ADC-004: ADC Noise and Filtering

**Objective**: Verify ADC readings stable despite electrical noise.

**Hardware Under Test**: ADC with analog filter

**Requirements Traced**: REQ-IF-HW-001, REQ-IMPL-003

**Preconditions**:
- System initialized
- Voltage source set to 1.65V (50% position)
- PWM motor control running (10 kHz, noise source)

**Test Steps**:
1. Set position sensor voltage to 1.65V
2. Enable motor PWM (10 kHz, 80% duty cycle, noise injection)
3. Sample ADC continuously for 10 seconds (1000 samples)
4. Calculate mean, standard deviation, peak-to-peak noise
5. Apply digital filter (moving average, N=8)
6. Recalculate statistics after filtering
7. Measure effect of PWM on ADC readings

**Expected Results**:
- Unfiltered ADC: mean = 2048 ± 20, std dev < 10 counts, pk-pk < 30 counts
- Filtered ADC: mean = 2048 ± 10, std dev < 5 counts, pk-pk < 20 counts
- PWM noise coupling < 0.5% of full scale (< 20 counts)
- Analog filter cutoff frequency: 100 Hz (RC filter)

**Pass/Fail Criteria**: Noise < 20 counts pk-pk (filtered), PWM coupling < 0.5%.

---

### 4.3 PWM Interface Tests

---

#### TC-HWINT-PWM-001: PWM Frequency and Resolution

**Objective**: Verify PWM frequency and duty cycle resolution.

**Hardware Under Test**: Timer PWM peripheral

**Requirements Traced**: REQ-IF-HW-003, REQ-IF-HW-004

**Preconditions**:
- System initialized
- Oscilloscope connected to PWM output

**Test Steps**:
1. Call `actuator_hal_set_door_pwm(DOOR_SIDE_LEFT, 50)` (50% duty)
2. Measure PWM frequency with oscilloscope
3. Verify frequency = 10 kHz ± 100 Hz
4. Measure duty cycle
5. Verify duty cycle = 50% ± 1%
6. Set duty cycle to 0%, 25%, 50%, 75%, 100%
7. Measure each duty cycle
8. Calculate resolution (smallest duty cycle step)
9. Verify resolution ≤ 0.5% (200 steps minimum)

**Expected Results**:
- PWM frequency: 10.0 kHz ± 0.1 kHz
- Duty cycle accuracy: ± 1% of setpoint
- Resolution: 0.4% (168 MHz / 840 prescaler = 200 kHz timer, 200 kHz / 10 kHz = 20 steps per percent = 0.05% resolution, but 1% typical)
- Rise time < 50ns, fall time < 50ns

**Pass/Fail Criteria**: Frequency = 10 kHz ± 100 Hz, duty cycle accuracy ± 1%.

---

#### TC-HWINT-PWM-002: PWM Duty Cycle Sweep

**Objective**: Verify PWM duty cycle linear across full range.

**Hardware Under Test**: PWM output, motor driver

**Requirements Traced**: REQ-IF-HW-003

**Preconditions**:
- System initialized
- Oscilloscope connected to PWM

**Test Steps**:
1. Sweep duty cycle from 0% to 100% in 10% steps
2. Measure actual duty cycle at each step
3. Record measured vs. commanded duty cycle
4. Calculate linearity error
5. Verify no stuck values or jumps
6. Test negative duty cycle (reverse direction flag)

**Expected Results**:
- Measured duty cycle within ± 2% of commanded
- Linearity error < 1% across full range
- No discontinuities or stuck values
- Reverse direction flag inverts motor direction (H-bridge control)

**Pass/Fail Criteria**: Duty cycle linear across range, error < 2%.

---

#### TC-HWINT-PWM-003: PWM Update Rate and Latency

**Objective**: Verify PWM duty cycle updates quickly.

**Hardware Under Test**: PWM peripheral, motor control

**Requirements Traced**: REQ-PERF-001, REQ-IF-HW-003

**Preconditions**:
- System initialized
- Oscilloscope in trigger mode

**Test Steps**:
1. Set PWM duty cycle to 20%
2. Wait for stable output (10ms)
3. Trigger oscilloscope
4. Call `actuator_hal_set_door_pwm(DOOR_SIDE_LEFT, 80)` (step change 20% → 80%)
5. Measure time from function call to PWM output change
6. Verify update latency
7. Repeat test with various step changes
8. Measure update jitter

**Expected Results**:
- PWM update latency: < 100µs (< 1 PWM period at 10 kHz)
- Update occurs at next PWM period boundary
- Update jitter < 10µs
- No partial pulses or glitches during update

**Pass/Fail Criteria**: Update latency < 100µs, no glitches.

---

#### TC-HWINT-PWM-004: PWM Under Motor Load

**Objective**: Verify PWM drives real motor correctly under load.

**Hardware Under Test**: PWM output, H-bridge motor driver, DC motor

**Requirements Traced**: REQ-IF-HW-003, REQ-FUNC-001

**Preconditions**:
- System initialized
- Motor connected via H-bridge driver
- Current sensor in series with motor

**Test Steps**:
1. Set PWM duty cycle to 50%, forward direction
2. Measure motor current draw
3. Verify motor rotates forward
4. Increase duty cycle to 80%
5. Verify motor speed increases (measure RPM if possible)
6. Verify current draw increases
7. Set duty cycle to 0%, verify motor stops
8. Set duty cycle to 50%, reverse direction
9. Verify motor rotates reverse
10. Measure motor current in reverse
11. Apply mechanical load to motor
12. Verify PWM maintains stable despite load

**Expected Results**:
- Motor current: 0.5-2.0A at 50% duty (depends on motor)
- Motor rotates in correct direction (forward/reverse)
- Motor speed proportional to duty cycle
- PWM frequency stable under load (10 kHz ± 100 Hz)
- No current spikes > 5A (overcurrent protection)

**Pass/Fail Criteria**: Motor operates correctly, current within limits, no overcurrent.

---

## 5. Sensor Integration Test Cases

### 5.1 Position Sensor Tests

---

#### TC-HWINT-SENSOR-001: Position Sensor Mechanical Calibration

**Objective**: Calibrate position sensor with real door mechanism.

**Hardware Under Test**: Position sensor (potentiometer or Hall sensor), ADC

**Requirements Traced**: REQ-IF-HW-001, REQ-FUNC-005

**Preconditions**:
- Door mechanism installed on test fixture
- Position sensor mechanically coupled to door

**Test Steps**:
1. Manually move door to fully closed position (0%)
2. Read ADC value, record as `ADC_CLOSED`
3. Verify ADC_CLOSED = 0 ± 50 counts
4. Manually move door to fully open position (100%)
5. Read ADC value, record as `ADC_OPEN`
6. Verify ADC_OPEN = 4095 ± 50 counts
7. Move door to 25%, 50%, 75% positions (measured mechanically)
8. Read ADC at each position
9. Verify linearity: ADC vs. mechanical position
10. Calculate calibration constants (slope, offset)

**Expected Results**:
- ADC_CLOSED = 0-100 counts (< 2.5%)
- ADC_OPEN = 3995-4095 counts (> 97.5%)
- Linearity error < 2% across full travel
- Calibration constants: slope ≈ 40.95 counts/%, offset ≈ 0

**Pass/Fail Criteria**: ADC range covers 0-100%, linearity < 2%.

---

#### TC-HWINT-SENSOR-002: Position Sensor During Door Motion

**Objective**: Verify position sensor tracks door motion accurately.

**Hardware Under Test**: Position sensor, ADC, motor control

**Requirements Traced**: REQ-FUNC-001, REQ-FUNC-002, REQ-FUNC-005

**Preconditions**:
- System initialized
- Door mechanism on test fixture

**Test Steps**:
1. Command door to open (0% → 100%)
2. Sample position sensor at 100 Hz during motion
3. Record position vs. time data (500+ samples)
4. Verify position increases monotonically (no reversals except at endpoints)
5. Measure door opening time
6. Verify position reaches 100% ± 2% at end
7. Command door to close (100% → 0%)
8. Sample position sensor during closing
9. Verify position decreases monotonically
10. Measure door closing time

**Expected Results**:
- Position increases smoothly during opening (no jumps > 5%)
- Opening time: 3-5 seconds
- Final position: 98-100% (door fully open)
- Position decreases smoothly during closing
- Closing time: 5-7 seconds
- Final position: 0-2% (door fully closed)

**Pass/Fail Criteria**: Smooth motion, times within limits, endpoints accurate.

---

#### TC-HWINT-SENSOR-003: Position Sensor Fault Detection

**Objective**: Verify system detects position sensor faults.

**Hardware Under Test**: Position sensor, ADC, fault detection module

**Requirements Traced**: REQ-FUNC-007, REQ-SAFE-004

**Preconditions**:
- System operational
- Fault injection capability available

**Test Steps**:
1. Normal operation: verify position sensor readings valid
2. Disconnect position sensor (open circuit)
3. Verify ADC reads out-of-range value (0 or 4095)
4. Call `door_fsm_update()`
5. Verify fault detected: `FAULT_POSITION_SENSOR`
6. Verify system enters safe state (motor stopped, door locked)
7. Measure fault detection time
8. Reconnect sensor, verify system recovers after reset

**Expected Results**:
- Sensor disconnect detected within 100ms (2 sampling periods)
- Fault code: `FAULT_POSITION_SENSOR_LEFT` or `RIGHT`
- Safe state entered immediately (motor stop < 50ms)
- Fault logged in non-volatile memory
- System recovers after sensor reconnect + reset

**Pass/Fail Criteria**: Fault detection time ≤ 100ms, safe state entered.

---

### 5.2 Obstacle Sensor Tests

---

#### TC-HWINT-SENSOR-004: Obstacle Sensor Detection (Infrared)

**Objective**: Verify infrared obstacle sensor detects physical objects.

**Hardware Under Test**: Infrared obstacle sensor, GPIO input

**Requirements Traced**: REQ-IF-HW-005, REQ-FUNC-009

**Preconditions**:
- System initialized
- Obstacle sensor mounted on door frame
- Test objects available (hand simulator, cardboard, reflective surface)

**Test Steps**:
1. Clear door area (no obstacles)
2. Call `sensor_hal_read_obstacle(DOOR_SIDE_LEFT)`
3. Verify return value = `OBSTACLE_CLEAR`
4. Place test object in sensor beam (10cm from sensor)
5. Call `sensor_hal_read_obstacle(DOOR_SIDE_LEFT)`
6. Verify return value = `OBSTACLE_DETECTED`
7. Measure detection distance (move object, find max range)
8. Test with various materials (flesh-tone rubber, cardboard, metal, black fabric)
9. Verify detection for all materials

**Expected Results**:
- Clear area: `OBSTACLE_CLEAR`
- Object present: `OBSTACLE_DETECTED`
- Detection range: 5-30cm (depends on sensor type)
- Detection latency < 10ms
- All test materials detected (reflectivity > 10%)

**Pass/Fail Criteria**: 100% detection rate for all materials, range > 5cm.

---

#### TC-HWINT-SENSOR-005: Obstacle Detection Reaction Time

**Objective**: Verify obstacle detection reaction time meets 100ms requirement.

**Hardware Under Test**: Obstacle sensor, door FSM, motor control

**Requirements Traced**: REQ-FUNC-009, REQ-PERF-004, HAZ-002 mitigation

**Preconditions**:
- Door in CLOSING state (motor running)
- Obstacle sensor clear
- High-speed camera or oscilloscope for timing

**Test Steps**:
1. Command door to close (starting at 80% open)
2. Verify motor running, closing direction
3. Insert test object into sensor beam (trigger obstacle)
4. Start timer at object insertion
5. Monitor motor PWM output for direction change
6. Stop timer when motor reverses
7. Measure total reaction time
8. Repeat test 50 times for statistical analysis
9. Calculate mean, max, std dev of reaction time

**Expected Results**:
- Mean reaction time: 50-80ms
- Maximum reaction time: ≤ 100ms (50/50 tests)
- Standard deviation: < 20ms
- Door reverses direction immediately upon detection
- 100% obstacle detection rate (50/50 tests)

**Pass/Fail Criteria**: Max reaction time ≤ 100ms, 100% detection rate.

---

#### TC-HWINT-SENSOR-006: Obstacle Sensor Redundancy

**Objective**: Verify redundant obstacle sensors (IR + pressure) work together.

**Hardware Under Test**: Infrared sensor, pressure sensor, fault detection

**Requirements Traced**: REQ-IF-HW-005, REQ-IF-HW-006, REQ-SAFE-002

**Preconditions**:
- Both IR and pressure sensors operational
- Door in CLOSING state

**Test Steps**:
1. Close door without obstacles (both sensors clear)
2. Verify no false detections
3. Insert soft object (detects on IR only)
4. Verify obstacle detected by IR sensor
5. Verify door reverses (OR logic: ANY sensor triggers)
6. Insert rigid object with pressure (detects on both IR and pressure)
7. Verify obstacle detected by both sensors
8. Verify door reverses
9. Disconnect IR sensor (simulate fault)
10. Insert object (pressure sensor only)
11. Verify obstacle still detected (degraded mode)
12. Disconnect both sensors
13. Verify fault reported, safe state entered

**Expected Results**:
- OR logic: ANY sensor triggers obstacle detection
- Single sensor fault: degraded mode continues (reduced speed)
- Both sensors fault: safe state entered (motor stopped)
- Fault detection time < 200ms
- Redundancy improves detection reliability (99.9% vs. 99%)

**Pass/Fail Criteria**: OR logic correct, degraded mode operational, fault handled.

---

### 5.3 Speed Sensor Tests

---

#### TC-HWINT-SENSOR-007: Speed Sensor CAN Message Reception

**Objective**: Verify speed sensor data received via CAN bus.

**Hardware Under Test**: CAN transceiver, CAN controller, speed sensor interface

**Requirements Traced**: REQ-IF-HW-007, REQ-IF-HW-008, REQ-FUNC-003

**Preconditions**:
- CAN bus operational (500 kbps)
- CAN message generator connected (simulates speed sensor)

**Test Steps**:
1. Send CAN message: ID=0x100, data[0-1] = 0x0000 (0.0 km/h)
2. Call `safety_monitor_update()`
3. Verify speed value = 0.0 km/h
4. Send CAN message: ID=0x100, data[0-1] = 0x0032 (5.0 km/h)
5. Verify speed value = 5.0 km/h
6. Send CAN message: ID=0x100, data[0-1] = 0x0064 (10.0 km/h)
7. Verify speed value = 10.0 km/h
8. Verify speed interlock activates when speed > 5 km/h
9. Measure CAN message reception latency

**Expected Results**:
- Speed values decoded correctly from CAN data
- Speed update rate: 20 Hz (50ms period)
- Reception latency: < 10ms
- Speed interlock activates at 5.0 km/h threshold
- No message loss (100% reception rate)

**Pass/Fail Criteria**: Speed values correct, latency < 10ms, 0% message loss.

---

#### TC-HWINT-SENSOR-008: Redundant Speed Sensor Cross-Check

**Objective**: Verify primary and secondary speed sensors cross-checked.

**Hardware Under Test**: CAN bus, safety monitor, fault detection

**Requirements Traced**: REQ-IF-HW-007, REQ-IF-HW-008, REQ-SAFE-001

**Preconditions**:
- CAN bus operational
- Both speed sensors (ID=0x100, ID=0x101) transmitting

**Test Steps**:
1. Send speed messages: primary = 10 km/h, secondary = 10 km/h
2. Verify safety monitor accepts both (agree within 10%)
3. Verify validated speed = 10 km/h (average)
4. Send speed messages: primary = 10 km/h, secondary = 15 km/h
5. Verify disagreement detected (> 10% difference)
6. Verify safety monitor uses MAX (15 km/h) fail-safe
7. Verify warning fault logged: `FAULT_SPEED_SENSOR_DISAGREE`
8. Stop secondary speed messages (simulate sensor failure)
9. Verify primary speed used (degraded mode)
10. Verify fault logged: `FAULT_SPEED_SENSOR_SECONDARY`
11. Stop both speed messages (both sensors failed)
12. Verify fail-safe: assume speed > 5 km/h, lock doors
13. Verify critical fault: `FAULT_SPEED_SENSOR_BOTH`

**Expected Results**:
- Sensors agree: average used, no faults
- Sensors disagree: MAX used (fail-safe), warning fault
- One sensor fails: remaining sensor used, major fault
- Both sensors fail: assume high speed, lock doors, critical fault
- Fault detection time < 200ms

**Pass/Fail Criteria**: Fail-safe logic correct, all fault modes detected.

---

### 5.4 Emergency Handle Tests

---

#### TC-HWINT-SENSOR-009: Emergency Handle Activation

**Objective**: Verify emergency handle activates door release immediately.

**Hardware Under Test**: Emergency handle GPIO, interrupt, lock solenoid

**Requirements Traced**: REQ-IF-HW-012, REQ-FUNC-004, HAZ-003 mitigation

**Preconditions**:
- Door closed and locked
- Train speed = 10 km/h (speed interlock active)

**Test Steps**:
1. Verify door locked (speed > 5 km/h)
2. Activate emergency handle (GPIO LOW → HIGH transition)
3. Start timer
4. Monitor lock solenoid output (expect release)
5. Stop timer when lock releases
6. Measure emergency release time
7. Verify emergency event logged
8. Verify emergency release overrides speed interlock
9. Verify emergency release works in all door states (CLOSED, OPENING, OPEN, CLOSING, LOCKED, FAULT)
10. Repeat test 50 times for reliability

**Expected Results**:
- Lock releases immediately (< 100ms)
- Emergency release overrides all safety interlocks
- Emergency event logged with timestamp
- 100% activation rate (50/50 tests)
- Works in all door states
- Hardware-level direct path (software monitors but does not control)

**Pass/Fail Criteria**: Release time ≤ 100ms, 100% activation rate, overrides all interlocks.

---

## 6. Actuator Integration Test Cases

### 6.1 Door Motor Tests

---

#### TC-HWINT-ACTUATOR-001: Motor Forward/Reverse Operation

**Objective**: Verify motor operates in forward and reverse directions.

**Hardware Under Test**: PWM output, H-bridge motor driver, DC motor

**Requirements Traced**: REQ-IF-HW-003, REQ-FUNC-001, REQ-FUNC-002

**Preconditions**:
- System initialized
- Motor connected, no load

**Test Steps**:
1. Set PWM: 50% duty, forward direction
2. Measure motor current and voltage
3. Verify motor rotates forward (clockwise, door opening)
4. Measure motor RPM (if tachometer available)
5. Set PWM: 0% duty (stop)
6. Verify motor stops within 500ms
7. Set PWM: 50% duty, reverse direction
8. Verify motor rotates reverse (counterclockwise, door closing)
9. Measure motor current and voltage (reverse)
10. Measure motor RPM (reverse)
11. Verify current draw similar in both directions

**Expected Results**:
- Motor rotates correctly in both directions
- Current draw: 0.5-2.0A at 50% duty (no load)
- Motor stops within 500ms of 0% duty command
- RPM proportional to duty cycle (≈500-1000 RPM at 50%)
- Voltage across motor: 12V at 50% duty (24V supply)

**Pass/Fail Criteria**: Correct rotation both directions, current within limits, stops promptly.

---

#### TC-HWINT-ACTUATOR-002: Motor Under Mechanical Load

**Objective**: Verify motor operates correctly under door load.

**Hardware Under Test**: Motor, H-bridge driver, door mechanism

**Requirements Traced**: REQ-FUNC-001, REQ-FUNC-002, REQ-PERF-002, REQ-PERF-003

**Preconditions**:
- Motor connected to real door mechanism
- Door free to move (no obstructions)

**Test Steps**:
1. Command door to open (0% → 100%)
2. Measure motor current during opening
3. Measure door opening time
4. Verify door reaches 100% open
5. Command door to close (100% → 0%)
6. Measure motor current during closing
7. Measure door closing time
8. Verify door reaches 0% closed
9. Apply external load to door (add weight, increase friction)
10. Repeat open/close commands
11. Verify motor stall current does not exceed limit

**Expected Results**:
- Opening time: 3-5 seconds (normal load)
- Closing time: 5-7 seconds (normal load)
- Motor current: 1-3A during motion (loaded)
- Motor stall current: < 5A (overcurrent protection)
- Door completes full travel under load
- No thermal shutdown (motor temperature < 80°C)

**Pass/Fail Criteria**: Times within limits, current < 5A, no thermal issues.

---

#### TC-HWINT-ACTUATOR-003: Motor Stall Detection

**Objective**: Verify system detects motor stall (door jammed).

**Hardware Under Test**: Motor, current sensor, fault detection

**Requirements Traced**: REQ-FUNC-007, REQ-SAFE-004

**Preconditions**:
- Door in OPENING state
- Door position = 30%

**Test Steps**:
1. Command door to open
2. Mechanically block door at 30% (jam simulation)
3. Verify motor current increases (stall current)
4. Verify position does not change for 5 seconds
5. Verify fault detected: `FAULT_DOOR_TIMEOUT`
6. Verify motor stopped (PWM = 0%)
7. Verify system enters FAULT state
8. Measure fault detection time
9. Remove obstruction
10. Reset system, verify recovery

**Expected Results**:
- Motor stall current: 4-5A (depends on motor)
- Position unchanged for 5 seconds
- Fault detected at 5.0 ± 0.1 seconds
- Motor stopped immediately after fault detection
- System enters FAULT state
- Recovery possible after obstruction removed

**Pass/Fail Criteria**: Fault detection time = 5.0 ± 0.1s, motor stopped, safe state entered.

---

### 6.2 Lock Solenoid Tests

---

#### TC-HWINT-ACTUATOR-004: Lock Solenoid Engage/Release

**Objective**: Verify lock solenoid engages and releases correctly.

**Hardware Under Test**: Lock solenoid, GPIO driver, mechanical lock

**Requirements Traced**: REQ-IF-HW-005, REQ-FUNC-003

**Preconditions**:
- System initialized
- Lock mechanism installed
- Lock position sensor (if available)

**Test Steps**:
1. Call `actuator_hal_set_door_lock(DOOR_SIDE_LEFT, true)` (engage)
2. Measure GPIO output voltage (expect HIGH)
3. Verify lock solenoid energized (12V applied)
4. Measure solenoid current draw
5. Verify mechanical lock engages (tactile/visual confirmation)
6. Measure engagement time
7. Call `actuator_hal_set_door_lock(DOOR_SIDE_LEFT, false)` (release)
8. Measure GPIO output voltage (expect LOW)
9. Verify solenoid de-energized (0V)
10. Verify mechanical lock releases
11. Measure release time

**Expected Results**:
- Engage: GPIO HIGH (3.3V), solenoid energized (12V, 0.5-1.0A)
- Lock engagement time < 100ms
- Release: GPIO LOW (0V), solenoid de-energized (0V, 0A)
- Lock release time < 100ms
- Mechanical lock holds door securely when engaged
- Lock releases smoothly when de-energized

**Pass/Fail Criteria**: Engagement/release time < 100ms, correct operation, current within limits.

---

#### TC-HWINT-ACTUATOR-005: Lock Under Speed Interlock

**Objective**: Verify lock engages automatically when speed exceeds threshold.

**Hardware Under Test**: Lock solenoid, safety monitor, speed sensor

**Requirements Traced**: REQ-FUNC-003, REQ-SAFE-001, HAZ-001 mitigation

**Preconditions**:
- Door closed (position ≤ 5%)
- Train speed = 3 km/h (below threshold)
- Lock released

**Test Steps**:
1. Verify lock status = RELEASED (speed < 5 km/h)
2. Increase train speed to 6 km/h (CAN message)
3. Start timer
4. Call `door_fsm_update()` and `safety_monitor_update()`
5. Monitor lock GPIO output
6. Stop timer when lock engages (GPIO HIGH)
7. Measure lock engagement time
8. Verify door remains closed
9. Attempt to open door (command should be rejected)
10. Verify door does not open (safety interlock active)

**Expected Results**:
- Lock engagement time: < 200ms (from speed change to lock engaged)
- Lock remains engaged while speed > 5 km/h
- Door open command rejected (safety interlock)
- Lock status reported to CAN status message
- No glitches or intermittent lock states

**Pass/Fail Criteria**: Lock engagement time < 200ms, door open prevented.

---

## 7. Communication Interface Test Cases

### 7.1 CAN Bus Tests

---

#### TC-HWINT-CAN-001: CAN Bus Initialization and Configuration

**Objective**: Verify CAN controller initialized correctly at 500 kbps.

**Hardware Under Test**: CAN controller, CAN transceiver

**Requirements Traced**: REQ-IF-SW-001

**Preconditions**:
- Target hardware powered on
- CAN bus analyzer connected

**Test Steps**:
1. Call `communication_hal_init()`
2. Read CAN controller registers
3. Verify bit rate = 500 kbps
4. Verify sample point = 87.5% (per CAN specification)
5. Verify filters configured: accept IDs 0x100-0x1FF
6. Verify TX/RX interrupts enabled
7. Send test message (ID=0x7FF, broadcast)
8. Verify message transmitted on bus analyzer
9. Measure bit time (expect 2.0 µs at 500 kbps)

**Expected Results**:
- CAN bit rate: 500 kbps ± 0.5%
- Sample point: 87.5% ± 5%
- Filters: accept IDs 0x100-0x1FF, reject others
- Test message transmitted successfully
- Bit time: 2.0 µs ± 0.05 µs
- No bus errors (error counter = 0)

**Pass/Fail Criteria**: Bit rate accurate, configuration correct, test message transmitted.

---

#### TC-HWINT-CAN-002: CAN Command Message Reception

**Objective**: Verify system receives and processes CAN command messages.

**Hardware Under Test**: CAN transceiver, command processor

**Requirements Traced**: REQ-IF-SW-001, REQ-FUNC-003

**Preconditions**:
- CAN bus operational
- CAN message generator connected

**Test Steps**:
1. Send CAN message: ID=0x200, DLC=2, data[0]=0x01 (OPEN_LEFT command)
2. Call `command_processor_update()`
3. Verify command decoded correctly
4. Verify door FSM receives OPEN command
5. Measure reception latency (CAN RX to command processed)
6. Send CAN message: ID=0x200, data[0]=0x02 (CLOSE_LEFT command)
7. Verify command decoded correctly
8. Send invalid CAN message: ID=0x999 (unknown ID)
9. Verify message rejected (not processed)
10. Send CAN message with wrong DLC (ID=0x200, DLC=1)
11. Verify message rejected

**Expected Results**:
- Valid commands (ID=0x200, DLC=2) processed correctly
- Invalid messages rejected (unknown ID or wrong DLC)
- Reception latency: < 20ms
- Command decode accuracy: 100%
- No command queue overflow

**Pass/Fail Criteria**: Valid commands processed, invalid rejected, latency < 20ms.

---

#### TC-HWINT-CAN-003: CAN Status Message Transmission

**Objective**: Verify system transmits CAN status messages at 20 Hz.

**Hardware Under Test**: CAN transceiver, status reporter

**Requirements Traced**: REQ-IF-SW-001, REQ-FUNC-006

**Preconditions**:
- CAN bus operational
- CAN bus analyzer connected

**Test Steps**:
1. Run system for 10 seconds
2. Record all CAN messages ID=0x201 (status message)
3. Count status messages received
4. Calculate transmission rate (messages per second)
5. Measure transmission period (time between consecutive messages)
6. Decode status message data bytes
7. Verify data[0] = door position (0-100%)
8. Verify data[1] = door state (CLOSED=0, OPEN=1, etc.)
9. Verify data[2] = lock status (0=released, 1=engaged)
10. Verify data[3-4] = fault code
11. Calculate transmission jitter (std dev of period)

**Expected Results**:
- Status messages: 200 messages in 10 seconds (20 Hz)
- Transmission period: 50ms ± 5ms
- Transmission jitter: < 5ms
- Data bytes correctly encoded per protocol
- 0% message loss
- No bus errors

**Pass/Fail Criteria**: Transmission rate = 20 Hz ± 1 Hz, jitter < 5ms, data correct.

---

#### TC-HWINT-CAN-004: CAN Bus Error Handling

**Objective**: Verify system handles CAN bus errors gracefully.

**Hardware Under Test**: CAN controller, fault detection

**Requirements Traced**: REQ-FUNC-007, REQ-SAFE-004

**Preconditions**:
- CAN bus operational

**Test Steps**:
1. Disconnect CAN transceiver (bus offline)
2. Attempt to send status message
3. Verify TX error counter increases
4. Verify fault detected: `FAULT_CAN_TX_FAIL`
5. Measure fault detection time
6. Reconnect CAN transceiver
7. Verify communication resumes
8. Inject CAN bus short (CAN_H shorted to CAN_L)
9. Verify bus error detected
10. Verify system enters safe state (if critical)
11. Remove short, verify recovery

**Expected Results**:
- TX error detected within 200ms (4 transmission attempts)
- Fault logged: `FAULT_CAN_TX_FAIL` or `FAULT_CAN_BUS_OFF`
- Communication resumes automatically after reconnect
- Bus short detected: error counter > 127, bus-off state
- System recovers after error cleared

**Pass/Fail Criteria**: Error detection time < 200ms, automatic recovery after error cleared.

---

### 7.2 UART Tests

---

#### TC-HWINT-UART-001: UART Diagnostic Console

**Objective**: Verify UART diagnostic console operates correctly.

**Hardware Under Test**: UART peripheral, diagnostic interface

**Requirements Traced**: REQ-IF-UI-001

**Preconditions**:
- System initialized
- Serial terminal connected (115200 baud, 8N1)

**Test Steps**:
1. Power on system
2. Verify boot message transmitted via UART
3. Verify message format: ASCII text, newline-terminated
4. Send command via terminal: "status"
5. Verify system responds with status information
6. Verify status includes: door position, state, faults
7. Send command: "open left"
8. Verify door opens (if safe to do so)
9. Verify acknowledgment message transmitted
10. Test special characters (CR, LF, backspace)

**Expected Results**:
- Boot message transmitted within 1 second of power-on
- Command echoed back to terminal
- Status information accurate (matches internal state)
- Commands executed if valid
- Invalid commands rejected with error message
- Baud rate: 115200 ± 1%
- No character loss or corruption

**Pass/Fail Criteria**: Console functional, baud rate accurate, commands processed.

---

## 8. Real-Time Performance Tests

### 8.1 Timing Tests on Target Hardware

---

#### TC-HWINT-PERF-001: Main Control Loop Timing on Target

**Objective**: Measure worst-case execution time (WCET) on real hardware.

**Hardware Under Test**: Complete system on target hardware

**Requirements Traced**: REQ-PERF-001

**Preconditions**:
- System operational on target hardware
- DWT cycle counter enabled
- All peripherals active (CAN, ADC, PWM, GPIO)

**Test Steps**:
1. Instrument main control loop with DWT cycle counter
2. Measure execution time for 1000 consecutive iterations
3. Record start/end cycle counts
4. Calculate execution time (cycles / 168 MHz = time)
5. Identify worst-case iteration (maximum time)
6. Analyze which function consumed most time
7. Verify no iteration exceeds 50ms deadline
8. Calculate CPU utilization (execution time / period)

**Expected Results**:
- Mean execution time: 30-40ms
- Worst-case execution time (WCET): ≤ 45ms
- Maximum execution time: < 50ms (deadline)
- Timing jitter: < 5ms
- CPU utilization: 60-80%
- 0% deadline misses (0/1000 iterations exceed 50ms)

**Pass/Fail Criteria**: WCET ≤ 45ms, 0% deadline misses, CPU utilization < 80%.

---

#### TC-HWINT-PERF-002: Interrupt Latency Measurement

**Objective**: Measure interrupt service routine (ISR) latency on target hardware.

**Hardware Under Test**: Interrupt controller, GPIO interrupt (emergency handle)

**Requirements Traced**: REQ-PERF-001, REQ-IF-HW-012

**Preconditions**:
- System operational
- Oscilloscope connected to GPIO input and ISR flag output

**Test Steps**:
1. Configure emergency handle GPIO interrupt (rising edge)
2. Configure debug GPIO to toggle in ISR (mark ISR entry)
3. Apply rising edge to emergency handle GPIO
4. Measure time from GPIO edge to ISR flag toggle
5. Measure interrupt latency (edge to ISR entry)
6. Measure ISR execution time (ISR entry to exit)
7. Repeat test 100 times
8. Calculate mean, max, std dev of latency
9. Test with various interrupt priorities

**Expected Results**:
- Interrupt latency: mean = 5-10µs, max ≤ 20µs
- ISR execution time: < 50µs
- Latency jitter: < 5µs
- 100% interrupt detection rate (100/100 tests)
- Interrupt priority affects latency (higher priority = lower latency)

**Pass/Fail Criteria**: Max interrupt latency ≤ 20µs, ISR execution < 50µs.

---

#### TC-HWINT-PERF-003: Real-Time Obstacle Reaction Time

**Objective**: Measure obstacle detection reaction time on real hardware.

**Hardware Under Test**: Complete system with real obstacle sensor and motor

**Requirements Traced**: REQ-PERF-004, REQ-FUNC-009, HAZ-002 mitigation

**Preconditions**:
- Door in CLOSING state (motor running)
- High-speed camera or oscilloscope for timing
- Physical test object

**Test Steps**:
1. Command door to close
2. Door at 70% position, motor running
3. Insert physical object into obstacle sensor beam
4. Start timer (hardware trigger from sensor)
5. Monitor motor PWM output for direction change
6. Stop timer when motor direction reverses
7. Measure total reaction time (sensor trigger to motor reverse)
8. Repeat test 100 times at various positions (90%, 70%, 50%, 30%, 10%)
9. Calculate mean, max, std dev for each position

**Expected Results**:
- Mean reaction time: 50-80ms (all positions)
- Maximum reaction time: ≤ 100ms (all positions, all 100 tests)
- Reaction time breakdown:
  - Sensor detection: < 10ms
  - Sensor reading (GPIO): < 10ms
  - FSM processing: < 30ms
  - Motor command update: < 10ms
  - Motor physical response: < 40ms
- 100% detection rate (no missed obstacles)

**Pass/Fail Criteria**: Max reaction time ≤ 100ms (all positions), 100% detection rate.

---

#### TC-HWINT-PERF-004: CAN Message Latency on Target

**Objective**: Measure CAN message transmission and reception latency on real hardware.

**Hardware Under Test**: CAN transceiver, CAN controller, CAN bus

**Requirements Traced**: REQ-PERF-001, REQ-IF-SW-001

**Preconditions**:
- CAN bus operational
- CAN bus analyzer with timestamp capability

**Test Steps**:
1. Prepare status message in software
2. Call `communication_hal_can_send()` with timestamp
3. Measure time from function call to CAN message on bus (analyzer timestamp)
4. Calculate TX latency
5. Repeat 100 times
6. Generate CAN command message externally
7. Timestamp message transmission on bus
8. Measure time from bus transmission to `command_processor_update()` processing
9. Calculate RX latency
10. Repeat 100 times

**Expected Results**:
- TX latency: mean = 2-5ms, max ≤ 10ms
- RX latency: mean = 2-5ms, max ≤ 10ms
- Total latency (TX + RX): ≤ 20ms
- Latency jitter: < 5ms
- 0% message loss

**Pass/Fail Criteria**: Max TX latency ≤ 10ms, max RX latency ≤ 10ms, 0% loss.

---

### 8.2 Stress Tests on Target Hardware

---

#### TC-HWINT-PERF-005: Maximum CPU Load Test

**Objective**: Verify system operates correctly under maximum CPU load.

**Hardware Under Test**: Complete system on target hardware

**Requirements Traced**: REQ-PERF-005

**Preconditions**:
- System operational
- All peripherals active

**Test Steps**:
1. Enable all diagnostic logging (maximum overhead)
2. Rapid door commands (OPEN, CLOSE every 100ms)
3. Inject CAN traffic (100 messages/second)
4. Enable fault injection (generate transient faults)
5. Run for 10 minutes continuous operation
6. Monitor CPU idle time
7. Monitor control loop timing (deadline misses)
8. Monitor fault detection (no false faults due to timing)
9. Verify no watchdog timeouts
10. Verify no buffer overflows

**Expected Results**:
- CPU utilization: ≤ 90% (peak)
- CPU idle time: ≥ 10%
- 0% control loop deadline misses
- 0% watchdog timeouts
- 0% buffer overflows (CAN, UART, event queues)
- All commands processed correctly
- No system crashes or resets

**Pass/Fail Criteria**: CPU utilization ≤ 90%, 0% deadline misses, system stable.

---

#### TC-HWINT-PERF-006: Long-Duration Stress Test

**Objective**: Verify system stability over extended operation (24 hours).

**Hardware Under Test**: Complete system on target hardware

**Requirements Traced**: REQ-PERF-005, REQ-IMPL-009

**Preconditions**:
- System operational
- Automated test harness (door command generator)

**Test Steps**:
1. Configure automated test: open/close door every 60 seconds
2. Run for 24 hours (1440 cycles)
3. Log all operations, faults, timing measurements
4. Monitor memory usage (check for leaks)
5. Monitor CPU temperature (thermal stability)
6. Monitor power consumption
7. Verify watchdog never triggers
8. Count successful vs. failed operations
9. Analyze fault log (transient vs. persistent faults)

**Expected Results**:
- 1440 successful open/close cycles (100% success rate)
- Memory usage stable (no leaks, constant RAM usage)
- CPU temperature < 80°C (thermal management)
- Power consumption stable (±10%)
- 0 watchdog timeouts
- 0 system crashes or resets
- Transient faults < 0.1% (< 2 faults in 24 hours)

**Pass/Fail Criteria**: 100% operation success, memory stable, no watchdog timeouts.

---

## 9. Hardware Safety Tests

### 9.1 Hardware Fault Injection Tests

---

#### TC-HWINT-SAFETY-001: Power Supply Glitch Test

**Objective**: Verify system handles power supply glitches gracefully.

**Hardware Under Test**: Power supply, reset circuit, watchdog

**Requirements Traced**: REQ-SAFE-002, REQ-FUNC-008

**Preconditions**:
- System operational
- Power supply with programmable glitch generator

**Test Steps**:
1. Normal operation: door at 50% position, motor running
2. Inject power glitch: 50ms dropout (simulate brownout)
3. Verify system detects glitch (voltage monitor)
4. Verify system enters safe state:
   - Motor stops (PWM = 0%)
   - Lock engages (if door closed)
   - Fault logged: `FAULT_POWER_GLITCH`
5. Verify watchdog triggers reset if glitch > 100ms
6. Verify system recovers after reset
7. Verify door position preserved (non-volatile memory)
8. Repeat test with glitches of 10ms, 30ms, 50ms, 100ms, 200ms

**Expected Results**:
- Glitches < 100ms: system recovers without reset
- Glitches > 100ms: watchdog triggers reset
- Safe state entered within 50ms of glitch detection
- Motor stopped immediately (no uncontrolled motion)
- System recovers after reset (all modules re-initialize)
- No data corruption (non-volatile memory intact)

**Pass/Fail Criteria**: Safe state entered ≤ 50ms, watchdog triggers on long glitch, recovery successful.

---

#### TC-HWINT-SAFETY-002: Sensor Disconnect Fault Injection

**Objective**: Verify system detects and handles sensor disconnects.

**Hardware Under Test**: Position sensor, obstacle sensor, ADC, GPIO, fault detection

**Requirements Traced**: REQ-FUNC-007, REQ-SAFE-004

**Preconditions**:
- System operational
- Sensors connected via removable connectors

**Test Steps**:
1. Normal operation: sensors reading valid values
2. Disconnect position sensor (open circuit)
3. Verify ADC reads out-of-range (0 or 4095)
4. Verify fault detected: `FAULT_POSITION_SENSOR`
5. Verify system enters safe state (motor stopped)
6. Measure fault detection time
7. Reconnect sensor, verify recovery after reset
8. Repeat for obstacle sensor (GPIO stuck HIGH or LOW)
9. Verify fault: `FAULT_OBSTACLE_SENSOR`
10. Repeat for speed sensor (CAN timeout)
11. Verify fault: `FAULT_SPEED_SENSOR_TIMEOUT`

**Expected Results**:
- Position sensor disconnect: detected within 100ms (2 ADC samples)
- Obstacle sensor disconnect: detected within 200ms (debounce + detection)
- Speed sensor timeout: detected within 100ms (CAN timeout)
- Safe state entered immediately (motor stop < 50ms)
- All faults logged with timestamp
- Recovery possible after sensor reconnect + reset

**Pass/Fail Criteria**: All sensor faults detected ≤ 200ms, safe state entered.

---

#### TC-HWINT-SAFETY-003: Actuator Fault Injection

**Objective**: Verify system detects and handles actuator faults.

**Hardware Under Test**: Motor driver, lock solenoid, fault detection

**Requirements Traced**: REQ-FUNC-007, REQ-SAFE-004

**Preconditions**:
- System operational
- Actuators connected

**Test Steps**:
1. Command door to open
2. Disconnect motor power (simulate motor failure)
3. Verify position does not change (motor not moving)
4. Wait 5 seconds (timeout threshold)
5. Verify fault detected: `FAULT_DOOR_TIMEOUT`
6. Verify system enters FAULT state
7. Measure fault detection time
8. Reconnect motor, verify recovery
9. Command lock to engage
10. Disconnect lock solenoid (simulate lock failure)
11. Verify lock status mismatch (commanded vs. actual)
12. Verify fault detected: `FAULT_LOCK_SOLENOID`

**Expected Results**:
- Motor timeout: detected at 5.0 ± 0.1 seconds
- Lock solenoid fault: detected within 200ms (if feedback available)
- System enters FAULT state
- Motor stopped, safe state maintained
- Faults logged
- Recovery after actuator repair + reset

**Pass/Fail Criteria**: Actuator faults detected, timeout accurate, safe state entered.

---

#### TC-HWINT-SAFETY-004: CAN Bus Fault Injection

**Objective**: Verify system handles CAN bus faults gracefully.

**Hardware Under Test**: CAN transceiver, CAN controller, fault detection

**Requirements Traced**: REQ-FUNC-007, REQ-IF-SW-001

**Preconditions**:
- CAN bus operational
- CAN bus with fault injection capability

**Test Steps**:
1. Normal operation: CAN messages flowing
2. Disconnect CAN bus (bus offline)
3. Verify TX error counter increases
4. Verify fault detected: `FAULT_CAN_BUS_OFF`
5. Measure fault detection time
6. Verify system enters safe state (if speed sensor unavailable)
7. Reconnect CAN bus, verify recovery
8. Inject CAN bus short (CAN_H to CAN_L)
9. Verify bus error detected
10. Inject dominant bit storm (bus permanently dominant)
11. Verify CAN controller enters bus-off state
12. Verify fault detected

**Expected Results**:
- CAN bus offline: detected within 200ms (4 TX attempts or RX timeout)
- CAN bus short: detected within 100ms (error counter > 127)
- System enters safe state (assume speed > 5 km/h, lock doors)
- Faults logged: `FAULT_CAN_TIMEOUT`, `FAULT_CAN_BUS_OFF`
- Recovery after bus repair (automatic bus-off recovery)

**Pass/Fail Criteria**: CAN faults detected ≤ 200ms, safe state entered.

---

### 9.2 Hardware Safety Interlock Tests

---

#### TC-HWINT-SAFETY-005: Speed Interlock Hardware Verification

**Objective**: Verify speed interlock prevents door opening at hardware level.

**Hardware Under Test**: Safety monitor, speed sensor, lock solenoid, door motor

**Requirements Traced**: REQ-FUNC-003, REQ-SAFE-001, HAZ-001 mitigation

**Preconditions**:
- System operational
- Real speed sensor (or CAN simulation)

**Test Steps**:
1. Set train speed to 0 km/h
2. Command door to open
3. Verify door opens (safety OK)
4. Increase speed to 6 km/h during opening (door at 50%)
5. Verify safety monitor detects speed violation
6. Verify motor immediately reverses (emergency close)
7. Verify lock engages when door reaches closed position
8. Measure reaction time (speed violation to motor reverse)
9. Attempt to open door while speed > 5 km/h
10. Verify command rejected (safety interlock active)
11. Verify lock remains engaged

**Expected Results**:
- Door opens when speed < 1 km/h
- Speed violation detected immediately (< 100ms)
- Motor reverses within 100ms of violation
- Lock engages when door closed
- Door open command rejected when speed > 5 km/h
- Lock remains engaged while speed > 5 km/h

**Pass/Fail Criteria**: Reaction time ≤ 100ms, door open prevented at speed, HAZ-001 mitigated.

---

#### TC-HWINT-SAFETY-006: Obstacle Detection Hardware Verification

**Objective**: Verify obstacle detection prevents door closure on real obstacle.

**Hardware Under Test**: Obstacle sensors, door motor, door FSM

**Requirements Traced**: REQ-FUNC-009, REQ-SAFE-002, HAZ-002 mitigation

**Preconditions**:
- System operational
- Real obstacle sensors (IR + pressure)
- Physical test object (human arm simulator)

**Test Steps**:
1. Command door to close
2. Door at 70% position, motor running
3. Insert physical test object (human arm simulator) into door path
4. Trigger obstacle sensor
5. Measure time from sensor trigger to motor reverse
6. Verify door reverses immediately
7. Verify door reopens to safe position (fully open)
8. Measure force applied to test object (if force sensor available)
9. Repeat test at various positions (90%, 70%, 50%, 30%, 10%)
10. Verify 100% detection rate

**Expected Results**:
- Obstacle detected within 10ms (sensor response)
- Motor reverses within 100ms of detection (all positions)
- Door reopens to fully open position
- Force on test object: < 150 N (safety limit per EN standard)
- 100% detection rate (100/100 tests, all positions)
- No injuries or damage to test object

**Pass/Fail Criteria**: Reaction time ≤ 100ms, force < 150 N, 100% detection, HAZ-002 mitigated.

---

#### TC-HWINT-SAFETY-007: Emergency Release Hardware Override

**Objective**: Verify emergency release operates at hardware level (independent of software).

**Hardware Under Test**: Emergency handle, lock solenoid, hardware relay

**Requirements Traced**: REQ-FUNC-004, REQ-IF-HW-012, HAZ-003 mitigation

**Preconditions**:
- Door closed and locked
- Train speed = 10 km/h (speed interlock active)
- Software disabled (simulate software failure)

**Test Steps**:
1. Verify door locked (speed > 5 km/h)
2. Disable software (halt CPU with debugger)
3. Activate emergency release handle
4. Verify lock releases immediately (hardware direct path)
5. Measure release time
6. Verify door can be manually opened
7. Verify hardware override bypasses all software controls
8. Re-enable software
9. Verify software detects emergency release event (after the fact)
10. Verify event logged

**Expected Results**:
- Lock releases immediately (< 100ms) even with software disabled
- Hardware direct path functional (relay/solenoid circuit)
- Door can be manually opened
- Software monitoring (if running) logs event but does NOT control release
- Emergency release overrides ALL software interlocks
- 100% reliability (fail-safe hardware design)

**Pass/Fail Criteria**: Release time ≤ 100ms, works with software disabled, HAZ-003 mitigated.

---

#### TC-HWINT-SAFETY-008: Watchdog Reset Hardware Verification

**Objective**: Verify external hardware watchdog resets system on software hang.

**Hardware Under Test**: External watchdog timer, reset circuit

**Requirements Traced**: REQ-FUNC-008, REQ-SAFE-002, HAZ-004 mitigation

**Preconditions**:
- System operational
- External watchdog enabled (100ms timeout)

**Test Steps**:
1. Normal operation: verify watchdog refreshed every 50ms
2. Inject infinite loop in software (simulate hang)
3. Stop refreshing watchdog
4. Wait 100ms (watchdog timeout)
5. Verify watchdog triggers hardware reset
6. Measure reset time (from timeout to reset assertion)
7. Verify system resets (CPU restarts)
8. Verify safe state entered during reset:
   - Motor stopped (hardware-level disable)
   - Lock engaged (fail-safe)
9. Verify system recovers after reset
10. Verify reset cause logged: `RESET_WATCHDOG`

**Expected Results**:
- Watchdog timeout at 100 ± 10ms (after last refresh)
- Hardware reset asserted immediately (< 10µs)
- Motor stopped during reset (hardware cutoff)
- Lock engaged during reset (fail-safe relay)
- System reboots and re-initializes
- Reset cause logged in non-volatile memory

**Pass/Fail Criteria**: Watchdog timeout accurate, hardware reset works, safe state entered, HAZ-004 mitigated.

---

## 10. Test Traceability Matrix

### 10.1 Requirements to Test Cases Mapping

| Requirement | Description | Test Case(s) | Status |
|-------------|-------------|--------------|--------|
| REQ-FUNC-001 | Door opening control | TC-HWINT-GPIO-002, TC-HWINT-ACTUATOR-001, TC-HWINT-SENSOR-002, TC-HWINT-PERF-005 | Planned |
| REQ-FUNC-002 | Door closing control | TC-HWINT-ACTUATOR-001, TC-HWINT-SENSOR-002, TC-HWINT-PERF-005 | Planned |
| REQ-FUNC-003 | Door lock control | TC-HWINT-ACTUATOR-004, TC-HWINT-ACTUATOR-005, TC-HWINT-SAFETY-005 | Planned |
| REQ-FUNC-004 | Emergency door release | TC-HWINT-SENSOR-009, TC-HWINT-SAFETY-007 | Planned |
| REQ-FUNC-005 | Door position monitoring | TC-HWINT-ADC-002, TC-HWINT-ADC-003, TC-HWINT-SENSOR-001, TC-HWINT-SENSOR-002 | Planned |
| REQ-FUNC-006 | Status reporting (CAN) | TC-HWINT-CAN-003 | Planned |
| REQ-FUNC-007 | Fault detection | TC-HWINT-SENSOR-003, TC-HWINT-ACTUATOR-003, TC-HWINT-SAFETY-002, TC-HWINT-SAFETY-003 | Planned |
| REQ-FUNC-008 | Watchdog monitoring | TC-HWINT-GPIO-004, TC-HWINT-SAFETY-008 | Planned |
| REQ-FUNC-009 | Obstacle detection | TC-HWINT-SENSOR-004, TC-HWINT-SENSOR-005, TC-HWINT-SENSOR-006, TC-HWINT-SAFETY-006 | Planned |
| REQ-PERF-001 | Control loop timing | TC-HWINT-PERF-001, TC-HWINT-PERF-005 | Planned |
| REQ-PERF-004 | Obstacle reaction time | TC-HWINT-SENSOR-005, TC-HWINT-PERF-003, TC-HWINT-SAFETY-006 | Planned |
| REQ-IF-HW-001 | Position sensor interface | TC-HWINT-ADC-001, TC-HWINT-ADC-002, TC-HWINT-ADC-003, TC-HWINT-ADC-004 | Planned |
| REQ-IF-HW-003 | Motor control interface | TC-HWINT-PWM-001, TC-HWINT-PWM-002, TC-HWINT-PWM-003, TC-HWINT-PWM-004 | Planned |
| REQ-IF-HW-005 | Obstacle sensor interface | TC-HWINT-SENSOR-004, TC-HWINT-SENSOR-005, TC-HWINT-SENSOR-006 | Planned |
| REQ-IF-HW-007 | Speed sensor interface | TC-HWINT-SENSOR-007, TC-HWINT-SENSOR-008 | Planned |
| REQ-IF-HW-012 | Emergency handle interface | TC-HWINT-GPIO-004, TC-HWINT-SENSOR-009, TC-HWINT-SAFETY-007 | Planned |
| REQ-IF-SW-001 | CAN bus interface | TC-HWINT-CAN-001, TC-HWINT-CAN-002, TC-HWINT-CAN-003, TC-HWINT-CAN-004 | Planned |
| REQ-SAFE-001 | Fail-safe door locking | TC-HWINT-SENSOR-008, TC-HWINT-SAFETY-005 | Planned |
| REQ-SAFE-002 | Watchdog safe state | TC-HWINT-SAFETY-001, TC-HWINT-SAFETY-008 | Planned |
| REQ-SAFE-004 | Fault detection safe state | TC-HWINT-SAFETY-002, TC-HWINT-SAFETY-003 | Planned |

### 10.2 Hazards to Test Cases Mapping

| Hazard | Description | Mitigation Test Case(s) | Status |
|--------|-------------|-------------------------|--------|
| HAZ-001 | Doors opening while train moving | TC-HWINT-SENSOR-007, TC-HWINT-SENSOR-008, TC-HWINT-SAFETY-005 | Planned |
| HAZ-002 | Door closing on passenger | TC-HWINT-SENSOR-004, TC-HWINT-SENSOR-005, TC-HWINT-PERF-003, TC-HWINT-SAFETY-006 | Planned |
| HAZ-003 | Emergency door release failure | TC-HWINT-SENSOR-009, TC-HWINT-SAFETY-007 | Planned |
| HAZ-004 | Software lockup | TC-HWINT-SAFETY-008 | Planned |

### 10.3 EN 50128 Table A.6 Compliance

| Technique | SIL 3-4 | Test Case(s) | Compliance |
|-----------|---------|--------------|------------|
| **Functional and Black-box Testing** | HR | All TC-HWINT test cases | ✓ Implemented |
| **Performance Testing** | HR | TC-HWINT-PERF-001 to TC-HWINT-PERF-006 | ✓ Implemented |
| **Interface Testing** | HR | TC-HWINT-GPIO, ADC, PWM, CAN, UART series | ✓ Implemented |
| **Boundary Value Analysis** | M | TC-HWINT-ADC-002 (0%, 50%, 100%), TC-HWINT-PWM-002 (0-100% sweep) | ✓ Implemented |

**Total Test Cases**: 48 hardware integration test cases

---

## 11. Test Execution Schedule

### 11.1 Test Phase Timeline

**Phase 1: Hardware Interface Tests** (Week 1)
- GPIO tests: 4 test cases (TC-HWINT-GPIO-001 to 004)
- ADC tests: 4 test cases (TC-HWINT-ADC-001 to 004)
- PWM tests: 4 test cases (TC-HWINT-PWM-001 to 004)
- CAN tests: 4 test cases (TC-HWINT-CAN-001 to 004)
- UART tests: 1 test case (TC-HWINT-UART-001)
- **Duration**: 5 days (1 week)

**Phase 2: Sensor Integration Tests** (Week 2)
- Position sensor tests: 3 test cases (TC-HWINT-SENSOR-001 to 003)
- Obstacle sensor tests: 3 test cases (TC-HWINT-SENSOR-004 to 006)
- Speed sensor tests: 2 test cases (TC-HWINT-SENSOR-007 to 008)
- Emergency handle tests: 1 test case (TC-HWINT-SENSOR-009)
- **Duration**: 5 days (1 week)

**Phase 3: Actuator Integration Tests** (Week 3)
- Motor tests: 3 test cases (TC-HWINT-ACTUATOR-001 to 003)
- Lock solenoid tests: 2 test cases (TC-HWINT-ACTUATOR-004 to 005)
- **Duration**: 3 days

**Phase 4: Real-Time Performance Tests** (Week 3-4)
- Timing tests: 4 test cases (TC-HWINT-PERF-001 to 004)
- Stress tests: 2 test cases (TC-HWINT-PERF-005 to 006)
- **Duration**: 4 days

**Phase 5: Hardware Safety Tests** (Week 4-5)
- Fault injection tests: 4 test cases (TC-HWINT-SAFETY-001 to 004)
- Hardware interlock tests: 4 test cases (TC-HWINT-SAFETY-005 to 008)
- **Duration**: 5 days (1 week)

**Total Duration**: **5 weeks** (25 working days)

### 11.2 Test Prerequisites

**Before Starting Phase 1**:
- Target hardware assembled and powered
- All measurement equipment calibrated (oscilloscope, logic analyzer, CAN analyzer)
- Test fixtures fabricated and verified
- Software built and flashed to target hardware
- Test environment setup document completed

**Before Starting Phase 2**:
- Phase 1 tests passed (GPIO, ADC, PWM, CAN, UART functional)
- Real sensors installed (position, obstacle, speed, emergency)
- Sensor calibration completed

**Before Starting Phase 3**:
- Phase 2 tests passed (sensors functional)
- Real actuators installed (motor, lock solenoid)
- Actuator safety limits configured

**Before Starting Phase 4**:
- Phases 1-3 tests passed
- DWT cycle counter enabled in software
- Performance monitoring instrumentation added

**Before Starting Phase 5**:
- All previous phases passed
- Fault injection equipment available
- Safety test procedures reviewed and approved

---

## 12. EN 50128 Compliance

### 12.1 EN 50128 Section 7.6 Requirements

**Software/Hardware Integration** (EN 50128:2011 Section 7.6):
- ✓ Hardware interface testing on target platform
- ✓ Real-time performance verification on target hardware
- ✓ Hardware fault injection and recovery testing
- ✓ Safety-critical hardware interlock verification
- ✓ Timing and performance measurement on target
- ✓ Communication interface testing (CAN, UART)

### 12.2 EN 50128 Table A.6 Compliance

**Integration Techniques for SIL 3** (Table A.6 - Software Integration):

| Technique | SIL 3-4 Rec. | Applied | Evidence |
|-----------|--------------|---------|----------|
| **Functional and Black-box Testing** | HR | ✓ Yes | All 48 test cases |
| **Performance Testing** | HR | ✓ Yes | TC-HWINT-PERF series (6 tests) |
| **Interface Testing** | HR | ✓ Yes | TC-HWINT-GPIO, ADC, PWM, CAN, UART (17 tests) |

### 12.3 Test Coverage Summary

**Hardware Interfaces Tested**:
- GPIO: 4 test cases (input, output, interrupt)
- ADC: 4 test cases (static, dynamic, noise, calibration)
- PWM: 4 test cases (frequency, duty cycle, latency, load)
- CAN: 4 test cases (init, TX, RX, errors)
- UART: 1 test case (console)
- **Total**: 17 interface tests

**Sensor Integration Tested**:
- Position sensors: 3 test cases
- Obstacle sensors: 3 test cases
- Speed sensors: 2 test cases
- Emergency handle: 1 test case
- **Total**: 9 sensor tests

**Actuator Integration Tested**:
- Door motors: 3 test cases
- Lock solenoids: 2 test cases
- **Total**: 5 actuator tests

**Performance Tested**:
- Timing tests: 4 test cases
- Stress tests: 2 test cases
- **Total**: 6 performance tests

**Safety Tested**:
- Fault injection: 4 test cases
- Hardware interlocks: 4 test cases
- **Total**: 8 safety tests

**Grand Total**: **48 SW/HW integration test cases**

### 12.4 Test Completion Criteria

**Phase 1 Complete When**:
- All 17 hardware interface tests passed
- No critical defects open
- Test report published

**Phase 2 Complete When**:
- All 9 sensor integration tests passed
- Sensor calibration data recorded
- No critical defects open

**Phase 3 Complete When**:
- All 5 actuator integration tests passed
- Actuator safety limits verified
- No critical defects open

**Phase 4 Complete When**:
- All 6 performance tests passed
- WCET < 45ms verified
- Timing margins documented

**Phase 5 Complete When**:
- All 8 safety tests passed
- All hazards mitigated (HAZ-001, HAZ-002, HAZ-003, HAZ-004)
- Safety test report published

**Overall Test Phase Complete When**:
- All 48 test cases executed
- Pass rate ≥ 95% (≤ 2 minor defects acceptable, 0 critical defects)
- All test reports approved by Verifier
- Traceability matrix complete (requirements → tests → results)
- Ready for Software Validation (Phase 6)

---

## DELIVERABLE STATUS

**DELIVERABLE_COMPLETE: docs/test/Software-Hardware-Integration-Test-Specification.md (PHASE 3 COMPLETE)**

This completes Activity 6 (FINAL activity) of Phase 3 (Architecture & Design)!

**Summary**:
- **Document ID**: DOC-HWINTTEST-2026-001
- **Total Test Cases**: 48 SW/HW integration test cases
- **Coverage**: All hardware interfaces (GPIO, ADC, PWM, CAN, UART), all sensors, all actuators, real-time performance, hardware safety tests
- **EN 50128 Compliance**: Section 7.6, Table A.6 (Functional Testing, Performance Testing, Interface Testing)
- **SIL 3 Requirements**: Hardware fault injection, real-time timing verification, safety interlock verification
- **Test Duration**: 5 weeks (25 working days)
- **Traceability**: Complete traceability to requirements, hazards, EN 50128 techniques

**Phase 3 Deliverables Complete**:
1. ✓ Software Architecture Specification (DOC-SAS-2026-001)
2. ✓ Software Design Specification (DOC-SDS-2026-001)
3. ✓ Software Interface Specifications (DOC-INTERFACES-2026-001)
4. ✓ Software Integration Test Specification (DOC-INTTEST-2026-001)
5. ✓ Hazard Log (DOC-HAZLOG-2026-001)
6. ✓ **Software/Hardware Integration Test Specification (DOC-HWINTTEST-2026-001)** ← THIS DOCUMENT

**Next Phase**: Phase 4 - Implementation & Testing (Unit Testing)
