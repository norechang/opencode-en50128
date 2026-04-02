# Software/Hardware Integration Test Specification

**REFERENCE**: EN 50128:2011 Section 7.6.4, Table A.6, Annex C Item 13

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-HWINTTESTSPEC-2026-001 |
| **CI ID** | CI-HWSITSPEC-TDC-001 |
| **Version** | 0.1 DRAFT |
| **Date** | 2026-04-02 |
| **Project** | TDC (Train Door Control System) |
| **SIL Level** | SIL 3 |
| **Author** | Software Integrator (INT) |
| **Reviewer** | Software Verifier (VER) |
| **Approver** | Project Manager (PM) |
| **Status** | Draft — submitted to QUA for review |

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-04-02 | INT | Initial draft — Phase 3 HW/SW Integration Test Specification from DOC-SAS-2026-001 v0.2, DOC-SDS-2026-001 v0.1, DOC-SIS-2026-001 v0.1. Covers all 13 external interfaces (EXT-001 through EXT-013 and EXT-ADC). | — |

## APPROVALS

**EN 50128 Annex C Table C.1 Signature Chain — Item 13 (HW/SW Integration Test Specification)**

| Written By | 1st Check | 2nd Check | Date |
|------------|-----------|-----------|------|
| Software Integrator<br>Name: [INT]<br>Signature: _____________ | Software Verifier<br>Name: [VER]<br>Signature: _____________ | Software Validator<br>Name: [VAL]<br>Signature: _____________ | 2026-04-02 |

**Notes:**
- **Written By**: INT owns Annex C Items 12 and 13 (EN 50128 §5.3.6, Table B.6).
- **1st Check**: VER independently reviews per §6.2. Mandatory independence at SIL 3.
- **2nd Check**: VAL reviews for validation readiness per §6.3.
- All submissions route through PM. INT does not contact QUA or VER directly.
- Test EXECUTION (Phase 6) and REPORTS (items 21/22) are separate deliverables.

---

## 1. INTRODUCTION

### 1.1 Purpose

This document constitutes the **Software/Hardware Integration Test Specification**
for the TDC (Train Door Control System) in accordance with EN 50128:2011 Section 7.6
and Annex C Item 13.

This specification defines:
- HW/SW integration strategy for TDC software on the STM32H743-based Door Control Unit
- Test cases for all 13 external interfaces (EXT-001 through EXT-013 + EXT-ADC) as
  defined in DOC-SIS-2026-001 §4
- Safety-critical HW/SW tests: speed sensor, position sensor, obstacle sensor, lock
  actuator, watchdog, CAN bus, RS-485, and cross-channel SPI hardware
- Performance and timing tests on target hardware
- Traceability to SRS REQ-INT-* requirements and SAS architecture

**Phase Note**: This specification is produced in **Phase 3** (Architecture & Design).
Test EXECUTION and HW/SW Integration Test Report (Item 22) are Phase 6 activities.

### 1.2 Scope

**In Scope**:
- Software integration with STM32H743 (MCU-A and MCU-B) target hardware
- Hardware Abstraction Layer (HAL, COMP-008) testing against real peripherals
- All 13 external interfaces (EXT-001 through EXT-013, EXT-ADC)
- GPIO inputs (sensors, DCP) and GPIO outputs (actuators, indicators)
- CAN bus interface (TCMS communication, EXT-007/EXT-008)
- RS-485 DDU interface (EXT-009)
- Cross-channel SPI hardware interface (EXT-010)
- Independent watchdog (IWDG) integration (EXT-006)
- ADC motor current sensing (EXT-ADC)
- Emergency release (EXT-011) and Driver Control Panel (EXT-012)
- Diagnostics port USB/RS-232 (EXT-013)
- Performance and timing on target hardware
- Resource usage (flash, RAM, stack)

**Out of Scope**:
- Pure software-to-software integration — see SW Integration Test Spec (Annex C Item 12)
- Hardware-only testing — hardware validation (system level)
- System-level validation — see Overall Software Test Specification (Annex C Item 16)

### 1.3 Definitions and Acronyms

| Term | Definition |
|------|------------|
| **ADC** | Analogue-to-Digital Converter (12-bit, motor current sensing) |
| **CAN** | Controller Area Network (2.0B, 250 kbit/s, TCMS interface) |
| **DCP** | Driver Control Panel (24 V discrete I/O) |
| **DDU** | Door Drive Unit (RS-485, per-door electromechanical actuator) |
| **DWT** | ARM Data Watchpoint and Trace — cycle counter for WCET measurement |
| **EXT-NNN** | External interface identifier from DOC-SIS-2026-001 §4 |
| **GPIO** | General Purpose Input/Output |
| **HAL** | Hardware Abstraction Layer (COMP-008) |
| **IWDG** | Independent Watchdog (STM32 hardware watchdog) |
| **JTAG/SWD** | Joint Test Action Group / Serial Wire Debug |
| **PWM** | Pulse Width Modulation (20 kHz, motor drive) |
| **SPI** | Serial Peripheral Interface (cross-channel redundancy link) |
| **WCET** | Worst-Case Execution Time |

### 1.4 Input Documents

| Document ID | Title | Version | Role |
|-------------|-------|---------|------|
| DOC-SAS-2026-001 | Software Architecture Specification | 0.2 DRAFT | Architecture, HAL API, HW interface context |
| DOC-SDS-2026-001 | Software Design Specification | 0.1 DRAFT | HAL module design, register-level detail |
| DOC-SIS-2026-001 | Software Interface Specifications | 0.1 DRAFT | Authoritative external interface definitions EXT-001–EXT-013, EXT-ADC |
| DOC-SRS-2026-001 | Software Requirements Specification | 0.1 DRAFT | REQ-INT-001–REQ-INT-013 traceability source |
| DOC-HW-DES-2026-001 | Hardware Design Specification | TBD | Pin assignments, peripheral configurations |

---

## 2. HARDWARE/SOFTWARE INTEGRATION STRATEGY

### 2.1 Integration Approach

**Integration Strategy**: **Bottom-Up from HAL, Safety-Critical First**

**Rationale**:
1. HAL (COMP-008) is the sole component that accesses hardware registers directly.
   All other SIL 3 components call HAL APIs. Therefore HAL must be integrated and
   validated on target hardware BEFORE any higher-level component integration.
2. Bottom-up minimises the need for hardware stubs — the actual STM32H743 peripherals
   are used from Phase 1, providing real timing characteristics.
3. Safety-critical peripherals (GPIO sensors, IWDG, CAN bus, SPI cross-channel) are
   tested before non-critical peripherals (diagnostics port, RS-485 DDU).
4. The 5-phase structure mirrors the SW Integration strategy (Item 12), ensuring
   HW/SW phases can be completed in parallel with SW integration phases.

**Target Platform**: STM32H743 (ARM Cortex-M7, 400 MHz)
- Flash: 2 MB (two banks of 1 MB)
- RAM: 1 MB (DTCM + AXI SRAM)
- Operating voltage: 3.3 V
- CAN: bxCAN controller
- SPI: SPI4 (cross-channel), SPI1 (Flash)
- USART: USART1 (RS-485), USART3 (diagnostics)
- ADC: ADC1 (motor current)
- Timer: TIM1 (PWM motor), TIM6 (20 ms scheduler tick)
- IWDG: Independent Watchdog (12 kHz LSI)

### 2.2 Integration Phases Overview

| Phase | Scope | Key External Interfaces | Safety Priority |
|-------|-------|------------------------|----------------|
| **HW Phase 1** | HAL GPIO + IWDG | EXT-002, EXT-003, EXT-004, EXT-005, EXT-006 (sensor GPIO + watchdog) | CRITICAL |
| **HW Phase 2** | HAL PWM + Motor control | EXT-001 (motor PWM/GPIO) | CRITICAL |
| **HW Phase 3** | HAL CAN bus | EXT-007, EXT-008 (TCMS CAN RX/TX) | CRITICAL |
| **HW Phase 4** | HAL SPI cross-channel + ADC | EXT-010 (SPI), EXT-ADC | CRITICAL |
| **HW Phase 5** | Remaining interfaces + full system | EXT-009, EXT-011, EXT-012, EXT-013 + regression | HIGH/MEDIUM |

### 2.3 Target Hardware Configuration

**Two DCU boards** required for full integration testing (Channel A and Channel B):

| Parameter | Value |
|-----------|-------|
| Board | STM32H743-based DCU (custom) |
| MCU | STM32H743VIT6, LQFP100 |
| Clock | 400 MHz (PLL from 8 MHz HSE crystal) |
| RAM | 1 MB SRAM (including 128 KB DTCM, 512 KB AXI, 256 KB SRAM1, 128 KB SRAM2) |
| Flash | 2 MB |
| Operating voltage | 3.3 V core; 24 V for door actuators (external) |
| Operating temperature | -25 °C to +70 °C (EN 50121-3-2 railway EMC) |

**Peripheral Connections for Testing**:

| Peripheral | STM32 Instance | Pin/Port | Connection for Test |
|------------|---------------|----------|---------------------|
| Motor PWM | TIM1 CH1–CH4 | PA8, PA9, PA10, PE11 | Oscilloscope CH1–CH4 |
| Motor Direction | GPIO | PE8–PE11 | Oscilloscope + logic analyser |
| Position Sensor A/B | GPIO input | Per schematic | Signal generator (24V logic) |
| Lock Sensor A/B | GPIO input | Per schematic | Signal generator (24V logic) |
| Obstacle Sensor A/B | GPIO interrupt | Per schematic | Signal generator + pulse injection |
| Lock Actuator | GPIO output + driver | Per schematic | Relay load or oscilloscope |
| CAN bus | bxCAN | PA11 (RX), PA12 (TX) | Vector CANalyzer or Peak PCAN |
| RS-485 | USART1 | PB6 (TX), PB7 (RX), PB8 (DE) | RS-485 analyser or scope |
| SPI cross-channel | SPI4 | PE2 (SCK), PE5 (MISO), PE6 (MOSI), PE4 (CS) | Wire to Channel B SPI4 |
| ADC motor current | ADC1 IN2–IN5 | PC2–PC5 | Signal generator (0–3.3V ramp) |
| IWDG | IWDG | — | Software timing test |
| Emergency release | GPIO | Per schematic | Manual switch or signal generator |
| DCP discrete I/O | GPIO | Per schematic | Signal generator + LED load |
| Diagnostics port | USART3 | PD8 (TX), PD9 (RX) | USB-UART adapter + terminal |

**Test Equipment Required**:

| Equipment | Purpose |
|-----------|---------|
| Oscilloscope (4-channel, ≥ 100 MHz) | PWM waveform, timing measurement |
| Logic analyser (≥ 8-channel) | SPI frame capture, CAN frame analysis |
| CAN analyser (Vector CANalyzer or Peak PCAN-USB) | CAN frame injection and capture |
| RS-485 breakout + analyser | DDU protocol validation |
| Signal generator (0–24V, adjustable) | Sensor signal injection |
| JTAG/SWD debugger (ST-Link v3 or Segger J-Link) | Flash programming and debug |
| PC with development environment | Build, flash, and test automation |

### 2.4 Hardware Abstraction Layer Architecture

```
┌───────────────────────────────────────────────────────┐
│               TDC Application Layer (SIL 3)            │
│  SKN · SPM · OBD · DSM · FMG · TCI · DGN              │
├───────────────────────────────────────────────────────┤
│               HAL API (COMP-008, SIL 3)               │
│  HAL_GPIO_*  HAL_PWM_*  HAL_CAN_*  HAL_SPI_*          │
│  HAL_RS485_* HAL_ADC_*  HAL_Watchdog_*                │
├───────────────────────────────────────────────────────┤
│               STM32 Peripheral Registers               │
│  GPIO · TIM1 · bxCAN · SPI4 · USART1 · ADC1 · IWDG   │
│  SPI1 (Flash) · USART3 (Diag)                         │
├───────────────────────────────────────────────────────┤
│               Physical Hardware                        │
│  Motors · Sensors · Actuators · CAN Bus · RS-485      │
│  SPI Cross-Link · Diagnostics Port                     │
└───────────────────────────────────────────────────────┘
       ↑ HW/SW Integration Boundary — this document
```

---

## 3. HW/SW INTEGRATION TEST ENVIRONMENT

### 3.1 Test Hardware Setup

**Development Board Configuration**:
- Development boards: Two TDC DCU prototype boards (DCU-A, DCU-B)
- Debugger/Programmer: ST-Link v3 (SWD interface) on both boards
- Power supply: 3.3V regulated; separate 24V supply for actuators
- Serial console: USART3 → USB-UART adapter for test logging
- Logic analyser: Saleae Logic 16 on SPI4 and USART1

**Build and Test Toolchain**:

| Tool | Version | Purpose |
|------|---------|---------|
| arm-none-eabi-gcc | 12.x | Cross-compiler |
| arm-none-eabi-gdb | 12.x | On-target debugging |
| OpenOCD | 0.12 | SWD debug interface |
| CMake | 3.x | Build system |
| Unity | 2.5 | C test framework for HAL unit harness |
| Python | 3.x | Test automation scripts |
| Segger SystemView | 3.x | RTOS/bare-metal timing profiler |

**Test Build Configuration**:
- Compiler flags: `-mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -O0 -g -DDEBUG`
- Coverage: not applicable on target (executed via gcov on host for SW integration; timing via DWT on target)
- MISRA C: `-Wall -Wextra` + PC-lint annotations verified by VER

### 3.2 Test Data and Test Vectors

- GPIO test vectors: sensor activation sequences per SIS §4 (EXT-002 to EXT-005)
- CAN test frames: pre-computed with CRC-16-CCITT 0x1021 for all 5 RX and 4 TX message IDs
- SPI test frames: `cross_channel_state_t` instances with known CRC values
- ADC test vectors: voltage levels mapping to 0A, 10A, 15A (overcurrent), 20A (max) via signal generator
- Watchdog timing: DWT cycle counter test; verified by oscilloscope on watchdog kick GPIO
- Fault injection: controlled GPIO level changes; CAN frame bit corruption via CAN analyser

---

## 4. HW/SW INTEGRATION TEST CASES

### 4.1 Test Case Convention

Each test case uses the following format:

```
TC-HWSW-NNN: <test name>
External Interface: EXT-NNN / REQ-INT-NNN
SAS reference: COMP-NNN §<section>
SIS reference: DOC-SIS-2026-001 §4.<N>
SIL: <level>
Type: Interface (M) | Functional (HR) | Performance (HR) | Resource | Fault Injection
HW Phase: <1–5>
Priority: Critical | High | Medium
Test Equipment: <instruments required>
```

### 4.2 HW Phase 1 — GPIO Sensors and IWDG

**Objective**: Verify HAL correctly reads GPIO sensor inputs (position, lock, obstacle)
and the hardware watchdog initialises and operates correctly on the STM32H743.

---

**TC-HWSW-001: HAL GPIO position sensor initialisation and read (EXT-002)**
```
External Interface: EXT-002 / REQ-INT-002
SAS reference: COMP-008 §4.9
SIS reference: DOC-SIS-2026-001 §4.2
SIL: 3
Type: Interface (M), Functional (HR)
HW Phase: 1
Priority: Critical
Test Equipment: Signal generator (24V logic level), oscilloscope
```
**Objective**: Verify `HAL_GPIO_ReadPositionSensor` correctly reads the 24V GPIO input
for position sensors A and B on each door; correct pull-down; debounce (2 readings, 40 ms).

**Preconditions**: GPIO pins configured as inputs with pull-down (10 kΩ); STM32 powered; SWD connected.

**Test Steps**:
1. Apply 0V (not activated) to position sensor A GPIO for door 0; call `HAL_GPIO_ReadPositionSensor(0, 0, &val)` twice (40 ms apart)
2. Verify `*val = 0` (not activated); return = `ERROR_SUCCESS`
3. Apply 24V (logic HIGH via level shifter) to sensor A; call twice (40 ms apart)
4. Verify `*val = 1` (activated)
5. Repeat for sensor B (sensor_idx=1) and all 4 doors
6. Apply voltage simultaneously to both sensors A and B for door 2 (2oo2 = locked)
7. Verify DSM stub correctly identifies DOOR_CLOSED_AND_LOCKED via 2oo2 logic

**Expected Results**:
- GPIO reads match applied voltage with 2-reading debounce (40 ms)
- `ERROR_SUCCESS` returned for all valid reads

**Pass/Fail Criteria**:
- PASS: All GPIO reads match applied logic levels; debounce implemented; no ERR_HW_FAULT
- FAIL: Level mismatch, no debounce, or HAL function crash

---

**TC-HWSW-002: HAL GPIO lock sensor read and 2oo2 integration (EXT-005)**
```
External Interface: EXT-005 / REQ-INT-005
SAS reference: COMP-008 §4.9, COMP-004 §4.5
SIS reference: DOC-SIS-2026-001 §4.5
SIL: 3
Type: Interface (M), Functional (HR)
HW Phase: 1
Priority: Critical
Test Equipment: Signal generator
```
**Objective**: Verify HAL reads lock sensor GPIO inputs; DSM applies 2oo2 voting rule
(both sensors must agree for LOCKED state); sensor disagreement → departure interlock held.

**Test Steps**:
1. Apply 24V to both lock sensors A and B for door 0; call `HAL_GPIO_ReadLockSensor(0, 0, &val_a)` and `HAL_GPIO_ReadLockSensor(0, 1, &val_b)`
2. Verify `val_a = 1, val_b = 1`; DSM 2oo2 evaluates → `lock_states[0] = 1` (locked)
3. Apply 0V to sensor B only (disagreement); execute DSM 2oo2 vote
4. Verify DSM detects disagreement; `lock_states[0] = 0` (conservative → unlocked); `ERR_SENSOR_DISAGREE` raised
5. Verify FMG receives `FAULT_SENSOR_DISAGREE` fault code
6. Verify departure interlock remains HELD (`departure_interlock_ok = 0`) on sensor disagreement

**Pass/Fail Criteria**:
- PASS: 2oo2 logic correct; disagreement detected; interlock held
- FAIL: LOCKED state set with disagreeing sensors (safety violation)

---

**TC-HWSW-003: HAL GPIO obstacle sensor ISR on real hardware (EXT-003)**
```
External Interface: EXT-003 / REQ-INT-003
SAS reference: COMP-008 §4.9, COMP-003 §4.4
SIS reference: DOC-SIS-2026-001 §4.3
SIL: 3
Type: Interface (M), Functional (HR)
HW Phase: 1
Priority: Critical
Test Equipment: Signal generator (pulse generator, rising-edge 24V pulse), oscilloscope, logic analyser
```
**Objective**: Verify GPIO interrupt (`OBD_ObstacleISR`) fires within ≤ 1 ms of rising
edge; `hal_obs_isr_flag[door]` set correctly; polled read confirms obstacle.

**Test Steps**:
1. Configure obstacle sensor GPIO as interrupt-capable (rising-edge, pull-down)
2. Connect oscilloscope to GPIO pin and to DWT output toggle pin (ISR entry marker)
3. Apply 24V rising-edge pulse to obstacle sensor A, door 0; measure ISR latency on oscilloscope
4. Verify `hal_obs_isr_flag[0] = 1` immediately after ISR
5. Call `HAL_GPIO_ReadObstacleSensor(0, 0, &val)` in polling cycle; verify `*val = 1`
6. Remove pulse (return to 0V); execute 3 polling cycles (60 ms)
7. Verify `hal_obs_isr_flag[0]` cleared after 3 consecutive clear readings per OBD debounce

**Expected Results**:
- ISR latency ≤ 1 ms (measured on oscilloscope)
- ISR flag set atomically; no race condition

**Pass/Fail Criteria**:
- PASS: ISR latency ≤ 1 ms; flag set correctly; cleared after 3 clear cycles
- FAIL: ISR latency > 1 ms, flag not set, or premature clear

---

**TC-HWSW-004: Hardware watchdog (IWDG) initialisation and normal operation (EXT-006)**
```
External Interface: EXT-006 / REQ-INT-006
SAS reference: COMP-008 §4.9
SIS reference: DOC-SIS-2026-001 §4.6
SIL: 3
Type: Interface (M), Functional (HR)
HW Phase: 1
Priority: Critical
Test Equipment: Oscilloscope, power supply monitor
```
**Objective**: Verify IWDG configured with 50 ms timeout; `HAL_Watchdog_Refresh` called
every 40 ms (within scheduler cycle); IWDG does NOT fire during normal operation.

**Test Steps**:
1. Initialise IWDG with 50 ms timeout via HAL; start 20 ms scheduler
2. Verify `HAL_Watchdog_Refresh` called at each cycle start (step 1 of schedule, every 20 ms)
3. Run 1000 cycles (20 seconds); verify no hardware reset (IWDG RCC reset flag clear)
4. Verify `watchdog_status` = 0 throughout
5. Log IWDG prescaler and reload register values; verify 50 ms timeout mathematically
   (12 kHz LSI: reload = (0.05 s × 12000 Hz / prescaler))

**Pass/Fail Criteria**:
- PASS: No IWDG reset in 1000 cycles; prescaler/reload values correct for 50 ms
- FAIL: IWDG fires during normal operation (false reset)

---

**TC-HWSW-005: Hardware watchdog timeout test (EXT-006)**
```
External Interface: EXT-006 / REQ-INT-006
SAS reference: COMP-008 §4.9, SAS §7.4 (defence-in-depth layer 7)
SIS reference: DOC-SIS-2026-001 §4.6
SIL: 3
Type: Interface (M), Functional (HR)
HW Phase: 1
Priority: Critical
Test Equipment: Logic analyser on reset line, oscilloscope
```
**Objective**: Verify system RESETS when watchdog refresh is withheld for > 50 ms;
system restarts with `safe_state_active = 1` (cold-start fail-safe default).

**Test Steps**:
1. Start system in normal operation; disable watchdog refresh (comment out `HAL_Watchdog_Refresh` in test build)
2. Measure time to hardware reset on oscilloscope (NRST pin pulse)
3. Verify reset occurs within 50 ms ± 5 ms (IWDG LSI tolerance)
4. Verify RCC reset status register (`RCC_RSR`) shows IWDG reset flag set
5. After reset, read `safe_state_active`; verify = 1 (cold-start default)

**Pass/Fail Criteria**:
- PASS: Reset within 50 ms ± 5 ms; IWDG flag set; cold-start safe state = 1
- FAIL: No reset, reset too late (> 55 ms), or cold start with safe_state_active = 0

---

**TC-HWSW-006: HAL GPIO lock actuator output (EXT-004)**
```
External Interface: EXT-004 / REQ-INT-004
SAS reference: COMP-008 §4.9
SIS reference: DOC-SIS-2026-001 §4.4
SIL: 3
Type: Interface (M), Functional (HR)
HW Phase: 1
Priority: Critical
Test Equipment: Oscilloscope or multimeter on GPIO output
```
**Objective**: Verify `HAL_GPIO_SetLockActuator` drives GPIO correctly; active-LOW
encoding: unlock=1 → GPIO LOW (energise solenoid); unlock=0 → GPIO HIGH (spring locked).

**Test Steps**:
1. Call `HAL_GPIO_SetLockActuator(0, 1)` (unlock); measure GPIO pin 0 voltage
2. Verify GPIO = LOW (active-LOW encoding: unlock command drives pin LOW)
3. Call `HAL_GPIO_SetLockActuator(0, 0)` (lock); measure GPIO pin 0
4. Verify GPIO = HIGH (de-energised; spring return to locked)
5. Repeat for all 4 doors (door_id 0–3)
6. Call with invalid door_id = 4; verify `ERR_RANGE` returned; no GPIO change

**Pass/Fail Criteria**:
- PASS: Active-LOW encoding verified on all 4 channels; ERR_RANGE for invalid door_id
- FAIL: Wrong encoding (lock command drives LOW — safety violation), or invalid door_id accepted

---

### 4.3 HW Phase 2 — Motor PWM and Direction Control

**Objective**: Verify HAL motor control functions generate correct PWM waveforms
and direction signals on target hardware (REQ-INT-001).

---

**TC-HWSW-007: HAL PWM duty cycle output on target hardware (EXT-001)**
```
External Interface: EXT-001 / REQ-INT-001
SAS reference: COMP-008 §4.9
SIS reference: DOC-SIS-2026-001 §4.1
SIL: 3
Type: Interface (M), Functional (HR)
HW Phase: 2
Priority: Critical
Test Equipment: Oscilloscope (4-channel, ≥ 100 MHz bandwidth)
```
**Objective**: Verify `HAL_PWM_SetDutyCycle` generates correct 20 kHz PWM waveforms
with accurate duty cycle on all 4 TIM1 channels.

**Test Steps**:
1. Call `HAL_PWM_SetDutyCycle(0, 50)` (door 0, 50% duty); measure TIM1_CH1 on oscilloscope
2. Verify: frequency = 20 kHz ± 1%; duty = 50% ± 2%
3. Call `HAL_PWM_SetDutyCycle(0, 0)` (stop); verify GPIO output = LOW (no PWM)
4. Call `HAL_PWM_SetDutyCycle(0, 100)` (full); verify duty = 100% ± 1%
5. Repeat for all 4 doors (door_id 0–3)
6. Call with duty = 101 (out of range); verify `ERR_RANGE` returned; no PWM change

**Pass/Fail Criteria**:
- PASS: 20 kHz ± 1%; duty matches ± 2%; duty=0 stops motor; ERR_RANGE for duty>100
- FAIL: Frequency wrong, duty inaccurate, motor not stopping on duty=0

---

**TC-HWSW-008: HAL motor direction GPIO (EXT-001)**
```
External Interface: EXT-001 / REQ-INT-001
SAS reference: COMP-008 §4.9
SIS reference: DOC-SIS-2026-001 §4.1
SIL: 3
Type: Interface (M), Functional (HR)
HW Phase: 2
Priority: Critical
Test Equipment: Oscilloscope or logic analyser
```
**Objective**: Verify `HAL_GPIO_SetMotorDirection` drives direction GPIO correctly;
direction=0 = open, direction=1 = close; no race condition between direction change and PWM.

**Test Steps**:
1. Call `HAL_GPIO_SetMotorDirection(0, 0)` (open); measure direction GPIO for door 0
2. Verify GPIO = LOW (open direction encoding)
3. Call `HAL_GPIO_SetMotorDirection(0, 1)` (close); measure GPIO
4. Verify GPIO = HIGH (close direction encoding)
5. Verify direction change occurs BEFORE PWM applies (no race condition: direction set → 1 µs → PWM start)
6. Repeat for doors 1–3

**Pass/Fail Criteria**:
- PASS: Direction encoding matches SIS specification; direction precedes PWM
- FAIL: Wrong direction encoding or race condition (direction changes while PWM active)

---

**TC-HWSW-009: Motor fail-safe on safe state (EXT-001, IF-015)**
```
External Interface: EXT-001 / REQ-INT-001
SAS reference: COMP-004 §4.5, COMP-008 §4.9
SIS reference: DOC-SIS-2026-001 §4.1, §3.16
SIL: 3
Type: Interface (M), Functional (HR)
HW Phase: 2
Priority: Critical
Test Equipment: Oscilloscope
```
**Objective**: Verify all motor PWM outputs go to duty=0 (stopped) within one
scheduler cycle (20 ms) of `safe_state_active = 1` assertion.

**Test Steps**:
1. Start all 4 motors at 50% duty (all doors in FSM_CLOSING)
2. Assert `safe_state_active = 1`; timestamp T0 (microsecond precision via DWT)
3. Measure time T1 when all PWM outputs = 0% on oscilloscope
4. T1 - T0 ≤ 20 ms (one scheduler cycle); verify on oscilloscope

**Pass/Fail Criteria**:
- PASS: All PWM outputs stop within 20 ms of safe state assertion
- FAIL: Any motor continues after 20 ms safe state assertion

---

### 4.4 HW Phase 3 — CAN Bus Interface

**Objective**: Verify HAL CAN functions (`HAL_CAN_Receive`, `HAL_CAN_Transmit`) on
real CAN bus hardware; CRC-16-CCITT validated at receive; correct frame transmission.

---

**TC-HWSW-010: CAN bus RX — TCMS speed frame (EXT-007)**
```
External Interface: EXT-007 / REQ-INT-007
SAS reference: COMP-008 §4.9, COMP-006 §4.7
SIS reference: DOC-SIS-2026-001 §4.7
SIL: 3
Type: Interface (M), Functional (HR)
HW Phase: 3
Priority: Critical
Test Equipment: CAN analyser (Vector CANalyzer or Peak PCAN-USB)
```
**Objective**: Verify HAL CAN RX interrupt correctly captures CAN 0x100 (TCMS speed
frame); `HAL_CAN_Receive` returns correct msg_id, data, and dlc; CRC validated by TCI.

**Test Steps**:
1. Connect CAN analyser to CAN bus (same bus as DCU-A)
2. Inject CAN frame: ID=0x100, DLC=5, data={0x01, 0xF4, 0x01, CRC_HI, CRC_LO} (speed=500, seq=1, CRC-16-CCITT 0x1021)
3. Execute HAL CAN RX ISR path; call `HAL_CAN_Receive(&msg_id, data, &dlc)`
4. Verify msg_id=0x100, dlc=5, data matches injected frame
5. Inject frame with corrupted CRC; verify TCI returns `ERR_CRC`; previous value retained
6. Do not inject any frame for 201 ms; verify `ERR_COMM_TIMEOUT` from SPM

**Pass/Fail Criteria**:
- PASS: Frame received correctly; CRC error detected; timeout detected at 200 ms
- FAIL: Wrong msg_id/dlc/data; CRC error missed; timeout not detected

---

**TC-HWSW-011: CAN bus TX — departure interlock frame (EXT-008)**
```
External Interface: EXT-008 / REQ-INT-008
SAS reference: COMP-008 §4.9, COMP-006 §4.7
SIS reference: DOC-SIS-2026-001 §4.8
SIL: 3
Type: Interface (M), Functional (HR)
HW Phase: 3
Priority: Critical
Test Equipment: CAN analyser
```
**Objective**: Verify HAL CAN TX sends CAN 0x200 (departure interlock) at 100 ms
intervals with correct content and CRC-16-CCITT (0x1021).

**Test Steps**:
1. Set `departure_interlock_ok = 1` via SKN; execute TCI cycle
2. Call `HAL_CAN_Transmit(0x200, data, 4)` with computed CRC
3. Capture frame on CAN analyser; verify ID=0x200, DLC=4, byte0=1 (interlock OK)
4. Compute CRC-16-CCITT (0x1021) over bytes 0–1; verify CRC matches bytes 2–3
5. Verify frame retransmitted every 100 ms (10 captures; measure inter-frame gap)
6. Set `departure_interlock_ok = 0`; verify next frame byte0=0

**Pass/Fail Criteria**:
- PASS: Correct ID/DLC/data; CRC correct; 100 ms periodic transmission
- FAIL: Wrong CRC, wrong timing, or interlock state not reflected in frame

---

**TC-HWSW-012: CAN bus TX — fault report frame (EXT-008)**
```
External Interface: EXT-008 / REQ-INT-008
SAS reference: COMP-006 §4.7, COMP-005 §4.6
SIS reference: DOC-SIS-2026-001 §4.8
SIL: 3
Type: Interface (M), Functional (HR)
HW Phase: 3
Priority: High
Test Equipment: CAN analyser
```
**Objective**: Verify FMG → TCI fault reporting chain: fault code transmitted on
CAN 0x202 on-event and repeated at 500 ms while fault active.

**Test Steps**:
1. Inject fault code 0x02 (FAULT_SPI_DISAGREE, CRITICAL) via FMG; timestamp T0
2. Execute TCI cycle; verify CAN 0x202 transmitted at T1 ≤ T0 + 20 ms
3. Advance time by 501 ms; verify CAN 0x202 retransmitted
4. Clear fault via FMG; verify CAN 0x202 stops after one more transmission

**Pass/Fail Criteria**:
- PASS: Fault on CAN within 20 ms; retransmitted at 500 ms; stops on fault clear
- FAIL: Fault not transmitted, wrong timing, or continued after fault clear

---

### 4.5 HW Phase 4 — SPI Cross-Channel and ADC

**Objective**: Verify cross-channel SPI hardware link between DCU-A and DCU-B;
ADC motor current sensing for obstacle-by-force detection.

---

**TC-HWSW-013: SPI cross-channel hardware exchange — normal operation (EXT-010)**
```
External Interface: EXT-010 / REQ-INT-010
SAS reference: COMP-001 §4.2, COMP-008 §4.9
SIS reference: DOC-SIS-2026-001 §4.10
SIL: 3
Type: Interface (M), Functional (HR)
HW Phase: 4
Priority: Critical
Test Equipment: Logic analyser on SPI4 (SCK, MOSI, MISO, CS)
```
**Objective**: Verify `HAL_SPI_CrossChannel_Exchange` correctly transmits and receives
`cross_channel_state_t` at 10 Mbit/s with correct CRC-16-CCITT framing; logic analyser
captures frame structure.

**Preconditions**: Both DCU-A and DCU-B powered; SPI4 wire connected; same software binary.

**Test Steps**:
1. Populate `cross_channel_state_t` on DCU-A with known values; compute CRC-16-CCITT (0x1021)
2. Execute `HAL_SPI_CrossChannel_Exchange(&tx, &rx)` on both boards simultaneously (step 6 of schedule)
3. Capture SPI frames on logic analyser; verify: 10 Mbit/s clock, CPOL=0/CPHA=0, CS active-LOW
4. Verify `rx` on DCU-A contains DCU-B's transmitted `cross_channel_state_t` with correct CRC
5. Verify frame size = `sizeof(cross_channel_state_t)` bytes (no dynamic sizing)
6. Execute 100 consecutive exchanges; verify no timeout or hardware error

**Pass/Fail Criteria**:
- PASS: 10 Mbit/s; correct frame structure; CRC validates on both sides; 100/100 successful
- FAIL: SPI speed wrong, CRC failures, frame size mismatch, or timeouts

---

**TC-HWSW-014: SPI cross-channel timeout test (EXT-010)**
```
External Interface: EXT-010 / REQ-INT-010
SAS reference: COMP-001 §4.2 (OI-FMEA-001)
SIS reference: DOC-SIS-2026-001 §4.10, §3.18
SIL: 3
Type: Interface (M), Error
HW Phase: 4
Priority: Critical
Test Equipment: Logic analyser
```
**Objective**: Verify SPI timeout (> 5 ms) is detected by HAL and reported to SKN
as `ERR_TIMEOUT`; SPI transient filter (OI-FMEA-001) operates correctly on hardware.

**Test Steps**:
1. Disable DCU-B SPI transmission (hold CS HIGH); start SPI exchange on DCU-A
2. Measure timeout duration on logic analyser; verify `HAL_SPI_CrossChannel_Exchange` returns `ERR_TIMEOUT` after 5 ms ± 1 ms
3. Execute 3 consecutive timeout cycles on DCU-A; verify `safe_state_active = 1` after 3rd
4. Restore DCU-B SPI; verify system requires maintenance reset (safe state irreversible)

**Pass/Fail Criteria**:
- PASS: Timeout at 5 ms ± 1 ms; safe state after 3 consecutive timeouts
- FAIL: No timeout detection, immediate safe state (filter not applied), or recovery without reset

---

**TC-HWSW-015: ADC motor current sensing — overcurrent detection (EXT-ADC)**
```
External Interface: EXT-ADC / REQ-SAFE-006 (OBD force-based obstacle)
SAS reference: COMP-008 §4.9, COMP-003 §4.4
SIS reference: DOC-SIS-2026-001 §4.14
SIL: 3
Type: Interface (M), Functional (HR)
HW Phase: 4
Priority: Critical
Test Equipment: Signal generator (0–3.3V), oscilloscope
```
**Objective**: Verify `HAL_ADC_ReadMotorCurrent` returns correct 12-bit ADC values
mapping to 0–20 A; overcurrent threshold (default 15 A = ADC value 3071) triggers
obstacle flag via OBD.

**Test Steps**:
1. Apply 0V to ADC1_IN2 (door 0 motor current); call `HAL_ADC_ReadMotorCurrent(0, &adc_raw)`
2. Verify `adc_raw` ≈ 0 (± 10 LSB noise)
3. Apply 1.65V (50% = ~10A); verify `adc_raw` ≈ 2048 ± 50
4. Apply 2.48V (76% = ~15A overcurrent threshold); execute OBD cycle
5. Verify `obstacle_flags[0] = 1` (force-based obstacle detection triggered)
6. Simulate ADC fault (HAL returns `ERR_HW_FAULT`); verify OBD assumes overcurrent (fail-safe)

**Pass/Fail Criteria**:
- PASS: ADC values linear to applied voltage; overcurrent triggers obstacle flag; ADC fault → fail-safe
- FAIL: ADC values incorrect, overcurrent not detected, or HAL fault ignored

---

### 4.6 HW Phase 5 — Remaining Interfaces and Full System

---

**TC-HWSW-016: RS-485 DDU interface — frame exchange (EXT-009)**
```
External Interface: EXT-009 / REQ-INT-009
SAS reference: COMP-008 §4.9, COMP-006 §4.7
SIS reference: DOC-SIS-2026-001 §4.9
SIL: SIL 2 (DDU non-safety-critical communication)
Type: Interface (M), Functional (HR)
HW Phase: 5
Priority: High
Test Equipment: RS-485 analyser or USART sniffer
```
**Objective**: Verify `HAL_RS485_DDU_Exchange` sends correct RS-485 frames (115.2 kbit/s,
8N1) and receives DDU acknowledgement; timeout 40 ms.

**Test Steps**:
1. Send door status command (0x01) to DDU address 0x01 via HAL; capture frame on RS-485 analyser
2. Verify frame: SOF=0xAA, Addr=0x01, Len=8, Payload=door_states[4]+lock_states[4], Seq=counter, CRC-16-CCITT, EOF=0x55
3. Simulate DDU ACK (0x81 status alive); verify HAL accepts response
4. Simulate DDU timeout (no response in 40 ms); verify `ERR_COMM_TIMEOUT` logged; one retry
5. After retry timeout: verify `ERR_COMM_TIMEOUT` to FMG (non-safe-state-triggering)

**Pass/Fail Criteria**:
- PASS: Frame format correct; timeout at 40 ms; retry once; non-critical fault on DDU loss
- FAIL: Wrong frame format, no timeout detection, or DDU loss causes safe state (incorrect escalation)

---

**TC-HWSW-017: Emergency release GPIO detection (EXT-011)**
```
External Interface: EXT-011 / REQ-INT-011
SAS reference: COMP-004 §4.5
SIS reference: DOC-SIS-2026-001 §4.11
SIL: SIL 2
Type: Interface (M), Functional (HR)
HW Phase: 5
Priority: High
Test Equipment: Manual switch or signal generator (active-LOW)
```
**Objective**: Verify emergency release GPIO (active-LOW) is correctly read; door unlocked
regardless of operational mode; TCMS notified within 200 ms; speed guard active at > 5 km/h.

**Test Steps**:
1. Assert emergency release GPIO LOW (activated) for door 1; speed = 0 (train stopped)
2. Execute HAL read + DSM cycle; verify door 1 lock actuator commanded to unlock
3. Verify CAN 0x202 fault code `EMERGENCY_RELEASE_ACTIVATED` sent within 200 ms
4. Verify event log entry written via FMG → DGN
5. Now simulate speed = 600 (> 5 km/h); assert emergency release
6. Verify `ERR_NOT_PERMITTED` returned; door NOT unlocked; alert still sent

**Pass/Fail Criteria**:
- PASS: Emergency release unlocks at speed=0; blocked at speed>5 km/h; TCMS alerted ≤ 200 ms
- FAIL: Release blocked at speed=0, or release permitted at speed>5 km/h (safety violation)

---

**TC-HWSW-018: Driver Control Panel GPIO I/O (EXT-012)**
```
External Interface: EXT-012 / REQ-INT-012
SAS reference: COMP-008 §4.9
SIS reference: DOC-SIS-2026-001 §4.12
SIL: SIL 2 (DCP)
Type: Interface (M), Functional (HR)
HW Phase: 5
Priority: High
Test Equipment: Signal generator (inputs), LED/oscilloscope (outputs)
```
**Objective**: Verify HAL reads DCP input signals (OPEN, CLOSE, MODE_SEL, EMRG_STOP)
and writes DCP output indicators (LED_CLOSED, LED_LOCKED, LED_FAULT, LED_SAFE) correctly.

**Test Steps**:
1. Apply 24V to DCP_DOOR_OPEN (active-HIGH); call `HAL_GPIO_ReadDCP(DCP_DOOR_OPEN, &val)`; verify val=1
2. Apply 0V; verify val=0
3. Apply active-LOW DCP_EMRG_STOP (0V = activated); verify val=1 (inverted logic handled by HAL)
4. Call `HAL_GPIO_WriteDCP(DCP_LED_FAULT, 1)` (fault LED on); measure output GPIO = HIGH
5. Call `HAL_GPIO_WriteDCP(DCP_LED_SAFE, 1)` (safe state LED on); measure GPIO = HIGH
6. Simulate safe state: verify DCP_LED_SAFE = HIGH and DCP_LED_FAULT blinking

**Pass/Fail Criteria**:
- PASS: All inputs read correctly; all outputs drive correctly; LED logic matches system state
- FAIL: Wrong logic level, inverted signal, or LED not driven

---

**TC-HWSW-019: Diagnostics port — mode-based access control (EXT-013)**
```
External Interface: EXT-013 / REQ-INT-013
SAS reference: COMP-007 §4.8
SIS reference: DOC-SIS-2026-001 §4.13
SIL: SIL 1 (diagnostics)
Type: Interface (M), Functional (HR)
HW Phase: 5
Priority: Medium
Test Equipment: USB-UART adapter + terminal emulator
```
**Objective**: Verify diagnostics port access control: read-only in MODE_NORMAL; full
access in MODE_DIAGNOSTIC; MUST NOT affect any safety-critical variable.

**Test Steps**:
1. Connect terminal emulator to USART3 at 115.2 kbit/s, 8N1
2. Set `current_mode = MODE_NORMAL`; send write command via diagnostics port
3. Verify command rejected (`ERR_NOT_PERMITTED`); no safety variable changed
4. Set `current_mode = MODE_DIAGNOSTIC`; send valid log read command
5. Verify event log data returned correctly
6. From MODE_DIAGNOSTIC, attempt to write `safe_state_active = 0`
7. Verify rejected; `safe_state_active` unchanged (write-ownership protection)

**Pass/Fail Criteria**:
- PASS: Write blocked in NORMAL mode; access granted in DIAGNOSTIC mode; safe variables protected
- FAIL: Write permitted in NORMAL mode, or safety variable modified via diagnostics port

---

### 4.7 Performance and Timing Tests on Target Hardware

**EN 50128 Table A.6 Item 4: Performance Testing — Highly Recommended at SIL 3**

---

**TC-HWSW-PERF-001: WCET on target STM32H743 (REQ-PERF-001)**
```
External Interface: ALL
SAS reference: SAS §3.1, §9.3 REQ-PERF-001
SIL: 3
Type: Performance (HR)
HW Phase: 5
Priority: Critical
Test Equipment: Segger SystemView or DWT cycle counter + logic analyser
```
**Objective**: Verify complete 20 ms scheduler cycle WCET ≤ 16 ms on actual STM32H743
hardware at 400 MHz (worst-case: all 4 doors in FSM_CLOSING + active obstacle + CAN/SPI).

**Test Steps**:
1. Configure DWT cycle counter; toggle GPIO at cycle start and cycle end
2. Set worst-case: 4 doors in FSM_CLOSING, obstacle_flags=0xF, CAN active, SPI exchange
3. Execute 10,000 cycles; measure GPIO toggle period via oscilloscope
4. Compute WCET = max(cycle_end - cycle_start) × (1/400e6) seconds
5. Verify WCET ≤ 16 ms; compute CPU utilisation = WCET / 20 ms ≤ 80% (REQ-PERF-008)

**Pass/Fail Criteria**:
- PASS: WCET ≤ 16 ms; CPU utilisation ≤ 80%
- FAIL: Any cycle ≥ 16 ms or CPU > 80%

---

**TC-HWSW-PERF-002: Flash code size (REQ-PERF-010)**
```
External Interface: N/A (static analysis)
SAS reference: §9.3 REQ-PERF-010
SIL: 3
Type: Resource
HW Phase: 5
Priority: High
Test Equipment: arm-none-eabi-size utility
```
**Objective**: Verify complete TDC firmware image ≤ 1600 KB flash (REQ-PERF-010).

**Test Steps**:
1. Build release firmware (`-O2 -DNDEBUG`)
2. Run `arm-none-eabi-size firmware.elf`; record `.text + .rodata` sections (code + constants)
3. Verify total ≤ 1,638,400 bytes (1600 KB)

**Pass/Fail Criteria**:
- PASS: Flash usage ≤ 1600 KB
- FAIL: Flash usage > 1600 KB

---

**TC-HWSW-PERF-003: RAM static allocation (REQ-PERF-009)**
```
External Interface: N/A (static analysis)
SAS reference: §9.3 REQ-PERF-009
SIL: 3
Type: Resource
HW Phase: 5
Priority: High
Test Equipment: arm-none-eabi-size + linker map file
```
**Objective**: Verify total static RAM usage ≤ 800 KB (REQ-PERF-009); NO dynamic
allocation (heap = 0 bytes for SIL 2+, MISRA C:2012 Rule 21.3).

**Test Steps**:
1. Build release firmware; analyse linker map file
2. Sum `.data + .bss + .stack` sections; verify ≤ 819,200 bytes (800 KB)
3. Verify heap size = 0 bytes in linker script (`__heap_size = 0`)
4. Verify `malloc`, `calloc`, `realloc`, `free` are absent in firmware image (symbol check)

**Pass/Fail Criteria**:
- PASS: RAM ≤ 800 KB; heap = 0; no dynamic allocation symbols
- FAIL: RAM > 800 KB, heap > 0, or any dynamic allocation function present

---

**TC-HWSW-PERF-004: Obstacle ISR latency on hardware (REQ-PERF-003)**
```
External Interface: EXT-003 / REQ-INT-003
SAS reference: COMP-003 §4.4, §9.3 REQ-PERF-003
SIS reference: DOC-SIS-2026-001 §4.3
SIL: 3
Type: Performance (HR)
HW Phase: 5
Priority: Critical
Test Equipment: Oscilloscope (2-channel), signal generator
```
**Objective**: Verify obstacle ISR latency ≤ 1 ms on real hardware; measure from
rising-edge GPIO pulse to `OBD_ObstacleISR` entry (via GPIO toggle at ISR entry).

**Test Steps**:
1. Configure GPIO toggle at ISR entry (port pin toggled in `OBD_ObstacleISR`)
2. Apply rising-edge pulse to obstacle sensor A, door 0 via signal generator
3. Measure channel 1 (sensor pulse) vs channel 2 (ISR GPIO toggle) on oscilloscope
4. Compute ISR latency = rising edge → ISR toggle
5. Repeat 100 times; record max ISR latency

**Pass/Fail Criteria**:
- PASS: Max ISR latency ≤ 1 ms (REQ-INT-003)
- FAIL: Any ISR latency > 1 ms

---

### 4.8 Fault Injection Tests

---

**TC-HWSW-FAULT-001: HAL peripheral failure — CAN controller fault (EXT-007)**
```
External Interface: EXT-007 / REQ-INT-007
SAS reference: COMP-006 §4.7, COMP-005 §4.6
SIS reference: DOC-SIS-2026-001 §4.7
SIL: 3
Type: Fault Injection
HW Phase: 5
Priority: High
Test Equipment: CAN analyser
```
**Objective**: Verify HAL returns `ERR_HW_FAULT` on CAN controller internal error; TCI
escalates to FMG; FMG triggers safe state.

**Test Steps**:
1. Simulate CAN bus-off condition by disconnecting CAN bus termination
2. Inject excessive CAN frames to force bus error counter overflow
3. Verify CAN controller enters bus-off state; `HAL_CAN_Receive` returns `ERR_HW_FAULT`
4. Verify TCI calls FMG with `FAULT_CAN_TIMEOUT`; FMG asserts critical fault
5. Verify `safe_state_active = 1` triggered (per §4.6 FMG fault classification: CRITICAL)

**Pass/Fail Criteria**:
- PASS: CAN bus-off detected; safe state asserted via FMG → SKN chain
- FAIL: CAN error silently ignored; no safe state on bus-off

---

**TC-HWSW-FAULT-002: Memory integrity check — CRC failure on safety globals (REQ-SAFE-018)**
```
External Interface: N/A (internal memory)
SAS reference: COMP-001 §4.2, §7.4 (layer 5: memory integrity)
SIS reference: DOC-SIS-2026-001 §1.4
SIL: 3
Type: Fault Injection
HW Phase: 5
Priority: Critical
Test Equipment: JTAG debugger (memory write via GDB)
```
**Objective**: Verify SKN memory integrity check (every 100 ms, REQ-SAFE-018) detects
CRC mismatch on safety-critical global variables and triggers safe state.

**Test Steps**:
1. Run system in normal operation; confirm memory CRC check passes every 100 ms
2. Via JTAG debugger (test instrumentation only), corrupt one byte of `door_states[0]` directly in RAM
3. Within ≤ 120 ms (one + one 100 ms check interval), verify CRC mismatch detected by SKN
4. Verify `safe_state_active = 1` asserted by SKN on memory CRC failure
5. Verify FMG logs `FAULT_CRC_ERROR` event

**Pass/Fail Criteria**:
- PASS: Memory corruption detected within 120 ms; safe state asserted; fault logged
- FAIL: Corruption not detected or safe state not asserted

---

**TC-HWSW-FAULT-003: Stack canary corruption detection (REQ-SAFE-018)**
```
External Interface: N/A (internal memory)
SAS reference: SAS §7.4 (layer 4: stack canary), COMP-001 §4.2
SIS reference: N/A
SIL: 3
Type: Fault Injection
HW Phase: 5
Priority: Critical
Test Equipment: JTAG debugger
```
**Objective**: Verify stack canary corruption is detected by SKN within one cycle;
safe state asserted immediately.

**Test Steps**:
1. Identify stack canary location (end of stack) in MAP file
2. Via JTAG, overwrite canary value
3. Execute one SKN cycle; verify canary mismatch detected
4. Verify `safe_state_active = 1` asserted immediately (same cycle)
5. Verify FMG logs event

**Pass/Fail Criteria**:
- PASS: Stack canary checked each cycle; corruption detected within 20 ms; safe state asserted
- FAIL: Canary not checked or corruption not detected

---

## 5. TRACEABILITY MATRIX

### 5.1 External Interface Coverage (Mandatory SIL 3 — Table A.6 Item 3)

Every external interface EXT-001 through EXT-013 (and EXT-ADC) SHALL be covered by
at least one HW/SW integration test case.

| Interface ID | SRS Ref | Description | Test Case(s) | Coverage |
|---|---|---|---|---|
| EXT-001 | REQ-INT-001 | PWM motor actuator | TC-HWSW-007, TC-HWSW-008, TC-HWSW-009 | ✓ |
| EXT-002 | REQ-INT-002 | Door position sensors (GPIO) | TC-HWSW-001 | ✓ |
| EXT-003 | REQ-INT-003 | Obstacle sensors (GPIO + ISR) | TC-HWSW-003, TC-HWSW-PERF-004 | ✓ |
| EXT-004 | REQ-INT-004 | Lock actuators (GPIO) | TC-HWSW-006, TC-HWSW-009 | ✓ |
| EXT-005 | REQ-INT-005 | Lock position sensors (GPIO) | TC-HWSW-002 | ✓ |
| EXT-006 | REQ-INT-006 | Independent watchdog (IWDG) | TC-HWSW-004, TC-HWSW-005 | ✓ |
| EXT-007 | REQ-INT-007 | CAN bus RX from TCMS | TC-HWSW-010, TC-HWSW-FAULT-001 | ✓ |
| EXT-008 | REQ-INT-008 | CAN bus TX to TCMS | TC-HWSW-011, TC-HWSW-012 | ✓ |
| EXT-009 | REQ-INT-009 | RS-485 DDU interface | TC-HWSW-016 | ✓ |
| EXT-010 | REQ-INT-010 | Cross-channel SPI | TC-HWSW-013, TC-HWSW-014 | ✓ |
| EXT-011 | REQ-INT-011 | Emergency release (GPIO) | TC-HWSW-017 | ✓ |
| EXT-012 | REQ-INT-012 | Driver Control Panel (GPIO) | TC-HWSW-018 | ✓ |
| EXT-013 | REQ-INT-013 | Diagnostics port (USB/RS-232) | TC-HWSW-019 | ✓ |
| EXT-ADC | REQ-SAFE-006 | ADC motor current sensing | TC-HWSW-015 | ✓ |

**Coverage Statistics**:
- Total external interfaces: **14** (EXT-001 through EXT-013 + EXT-ADC)
- Interfaces with test cases: **14 / 14**
- Coverage: **100%** ✓

*Note: SIS §4 enumerates 13 named external interfaces (EXT-001–EXT-013) plus EXT-ADC
(motor current ADC, referenced in §4.14). This specification covers all 14.*

### 5.2 Safety Function → HW/SW Test Case Traceability

| Safety Function | SF-ID | SRS Requirement | Primary HW/SW Test Cases |
|---|---|---|---|
| Speed Interlock | SF-001 | REQ-SAFE-001, REQ-INT-007 | TC-HWSW-010 (CAN RX), TC-HWSW-011 |
| Departure Interlock | SF-002 | REQ-SAFE-002, REQ-INT-001 | TC-HWSW-002 (lock sensor 2oo2), TC-HWSW-006, TC-HWSW-011 |
| Obstacle Detection | SF-003 | REQ-SAFE-004, REQ-INT-003 | TC-HWSW-003, TC-HWSW-015 (ADC), TC-HWSW-PERF-004 |
| Safe State on Fault | SF-004 | REQ-SAFE-012, REQ-INT-006 | TC-HWSW-004, TC-HWSW-005, TC-HWSW-009, TC-HWSW-FAULT-001–003 |
| Door Position Verification | SF-005 | REQ-SAFE-007, REQ-INT-002 | TC-HWSW-001, TC-HWSW-002 |

### 5.3 SRS REQ-INT-* Requirements → HW/SW Test Case Traceability

| Requirement | Description | Test Case(s) |
|---|---|---|
| REQ-INT-001 | Door motor PWM interface | TC-HWSW-007, TC-HWSW-008, TC-HWSW-009 |
| REQ-INT-002 | Door position sensor interface | TC-HWSW-001 |
| REQ-INT-003 | Obstacle sensor (interrupt) | TC-HWSW-003, TC-HWSW-PERF-004 |
| REQ-INT-004 | Door lock actuator interface | TC-HWSW-006 |
| REQ-INT-005 | Lock sensor interface | TC-HWSW-002 |
| REQ-INT-006 | Hardware watchdog (IWDG) | TC-HWSW-004, TC-HWSW-005 |
| REQ-INT-007 | CAN RX from TCMS | TC-HWSW-010 |
| REQ-INT-008 | CAN TX to TCMS | TC-HWSW-011, TC-HWSW-012 |
| REQ-INT-009 | RS-485 DDU | TC-HWSW-016 |
| REQ-INT-010 | Cross-channel SPI | TC-HWSW-013, TC-HWSW-014 |
| REQ-INT-011 | Emergency release | TC-HWSW-017 |
| REQ-INT-012 | Driver Control Panel | TC-HWSW-018 |
| REQ-INT-013 | Diagnostics port | TC-HWSW-019 |
| REQ-SAFE-001 | Speed interlock | TC-HWSW-010 |
| REQ-SAFE-006 | ADC/motor current obstacle | TC-HWSW-015 |
| REQ-SAFE-018 | Memory integrity / stack canary | TC-HWSW-FAULT-002, TC-HWSW-FAULT-003 |
| REQ-PERF-001 | WCET ≤ 16 ms | TC-HWSW-PERF-001 |
| REQ-PERF-008 | CPU utilisation ≤ 80% | TC-HWSW-PERF-001 |
| REQ-PERF-009 | SRAM ≤ 800 KB | TC-HWSW-PERF-003 |
| REQ-PERF-010 | Flash ≤ 1600 KB | TC-HWSW-PERF-002 |

---

## 6. HW/SW INTEGRATION TEST PROCEDURE

### 6.1 HW Phase 1: GPIO Sensors and IWDG

**Entry Criteria**:
- [ ] HAL component compiled and linked for STM32H743 target
- [ ] Target hardware (DCU board) available and powered
- [ ] ST-Link connected; firmware flashable
- [ ] Signal generator and oscilloscope calibrated and connected

**Test Cases**: TC-HWSW-001, TC-HWSW-002, TC-HWSW-003, TC-HWSW-004, TC-HWSW-005, TC-HWSW-006

**Exit Criteria**:
- [ ] TC-HWSW-001 through TC-HWSW-006 PASSED
- [ ] 2oo2 sensor voting verified on hardware
- [ ] IWDG 50 ms timeout verified by measurement
- [ ] No critical defects open

### 6.2 HW Phase 2: Motor PWM and Direction

**Entry Criteria**:
- [ ] HW Phase 1 exit criteria met
- [ ] Oscilloscope connected to PWM channels (TIM1 CH1–CH4)

**Test Cases**: TC-HWSW-007, TC-HWSW-008, TC-HWSW-009

**Exit Criteria**:
- [ ] TC-HWSW-007 through TC-HWSW-009 PASSED
- [ ] PWM frequency verified at 20 kHz ± 1% by oscilloscope
- [ ] Fail-safe (duty=0 on safe state) verified by measurement

### 6.3 HW Phase 3: CAN Bus Interface

**Entry Criteria**:
- [ ] HW Phase 2 exit criteria met
- [ ] CAN analyser connected to CAN bus
- [ ] CAN termination resistors in place (120 Ω at each end)

**Test Cases**: TC-HWSW-010, TC-HWSW-011, TC-HWSW-012

**Exit Criteria**:
- [ ] TC-HWSW-010 through TC-HWSW-012 PASSED
- [ ] CRC-16-CCITT (0x1021) verified on CAN frames by analyser capture
- [ ] 100 ms TX timing verified

### 6.4 HW Phase 4: SPI Cross-Channel and ADC

**Entry Criteria**:
- [ ] HW Phase 3 exit criteria met
- [ ] Two DCU boards available; SPI4 cross-link wired
- [ ] Logic analyser on SPI4 bus
- [ ] Signal generator connected to ADC inputs

**Test Cases**: TC-HWSW-013, TC-HWSW-014, TC-HWSW-015

**Exit Criteria**:
- [ ] TC-HWSW-013 through TC-HWSW-015 PASSED
- [ ] SPI 10 Mbit/s frame capture validated by logic analyser
- [ ] ADC linearity verified; overcurrent threshold functional

### 6.5 HW Phase 5: Remaining Interfaces + Full System

**Entry Criteria**:
- [ ] HW Phase 4 exit criteria met
- [ ] RS-485 test equipment ready
- [ ] Emergency release switch or signal available
- [ ] Diagnostics terminal emulator configured

**Test Cases**: TC-HWSW-016 through TC-HWSW-019, TC-HWSW-PERF-001 through TC-HWSW-PERF-004, TC-HWSW-FAULT-001 through TC-HWSW-FAULT-003

**Regression Test**: Execute all HW Phase 1–4 test cases as regression

**Exit Criteria**:
- [ ] TC-HWSW-016 through TC-HWSW-019 PASSED
- [ ] TC-HWSW-PERF-001 through TC-HWSW-PERF-004 PASSED (WCET, Flash, RAM, ISR latency)
- [ ] TC-HWSW-FAULT-001 through TC-HWSW-FAULT-003 PASSED
- [ ] All Phase 1–4 regression tests PASSED
- [ ] 100% external interface coverage (14/14 interfaces)
- [ ] No critical or high-severity defects open

---

## 7. TEST ENTRY AND EXIT CRITERIA (OVERALL)

### 7.1 Overall Entry Criteria

**Entry Criteria for HW/SW Integration Testing (Phase 6)**:
- [ ] SW Integration Testing (Item 12) Phase 1–4 complete (SW components integrated)
- [ ] SW Integration Test Report (Item 21) available or SW integration Phase 5 in progress
- [ ] Target hardware (two DCU boards) available, validated, and under CM control
- [ ] HAL unit tests passed on host (pre-target)
- [ ] This specification (Item 13) reviewed by VER and QUA
- [ ] All test equipment calibrated and available
- [ ] HW/SW test environment configured and validated
- [ ] Traceability matrix (§5.1) verified — 14/14 external interfaces covered

### 7.2 Overall Exit Criteria

**Exit Criteria for HW/SW Integration Testing**:
- [ ] All 27 HW/SW test cases executed (TC-HWSW-001 through TC-HWSW-FAULT-003)
- [ ] All safety-critical tests PASSED (TC-HWSW-001–015, FAULT-001–003)
- [ ] All performance tests PASSED (WCET ≤ 16 ms, Flash ≤ 1600 KB, RAM ≤ 800 KB, ISR ≤ 1 ms)
- [ ] 100% external interface coverage (14/14): verified in §5.1
- [ ] No critical or high-severity defects open
- [ ] HW/SW Integration Test Report (Item 22) completed by INT with TST-provided results
- [ ] VER approval of HW/SW Integration Test Report (independent, SIL 3 mandatory)
- [ ] Hardware configuration (board revision, firmware version, git SHA) recorded in Item 22

---

## 8. DEFECT MANAGEMENT

### 8.1 Defect Classification

| Severity | Definition | Action |
|----------|------------|--------|
| **Critical** | Safety-critical HW/SW interface failure; safe state not triggered; IWDG not functional; CRC not checked | Immediate fix; hardware review if HW defect |
| **High** | Interface timing non-compliant; ADC linearity error; wrong GPIO encoding | Fix before next HW phase |
| **Medium** | Non-safety interface error; DDU timeout incorrect; DCP indicator wrong | Fix before full system integration |
| **Low** | Diagnostics port cosmetic; non-critical data format issue | Fix before Item 22 |

### 8.2 HW/SW Defect Routing

All HW/SW integration defects are reported to PM:
- SW defects: PM routes to IMP (fix) + DES (review if architectural change)
- HW defects: PM routes to Hardware Engineer + DES
- INT does not contact QUA or VER directly

---

## 9. RISKS AND MITIGATION

| Risk | Probability | Impact | Mitigation |
|------|-------------|--------|------------|
| Target hardware not available | Low | High | Procure two DCU boards early; use Nucleo-H743 for HAL prototype testing |
| IWDG timing inaccurate (LSI tolerance ±10%) | Medium | Critical | Measure actual LSI frequency with DWT; adjust reload register; verify by oscilloscope |
| SPI cross-channel wiring issue | Low | High | Validate SPI loopback on single board first; verify with logic analyser before cross-channel |
| ADC non-linearity on motor current | Medium | High | Calibrate ADC with known resistive loads; verify linearity at 0A, 5A, 10A, 15A, 20A |
| CAN termination impedance mismatch | Low | Medium | Use 120 Ω terminators; verify signal quality with oscilloscope |
| Performance failure (WCET > 16 ms) | Low | Critical | Profile on actual target early; identify bottlenecks in HAL drivers; co-design with IMP |

---

## 10. CONFIGURATION MANAGEMENT

**Document Version Control**:
- Document: DOC-HWINTTESTSPEC-2026-001 v0.1
- Repository: git (project repository)
- Baseline: Phase 3 architecture baseline

**Target Hardware Configuration** (to be verified at Phase 6):
- Hardware board: [Board model, revision TBD]
- Firmware version: [Version to be recorded at test start]
- Git commit SHA: [To be recorded at Phase 6 test start]

---

## 11. ROLES AND RESPONSIBILITIES

| Role | Responsibilities |
|------|-----------------|
| **Integrator (INT)** | Owns this specification (Item 13); authors HW/SW Integration Test Report (Item 22) from TST results |
| **Tester (TST)** | Executes HW/SW integration tests in Phase 6 on target hardware; returns machine-readable results to PM |
| **Hardware Engineer** | Provides target hardware; assists with test equipment setup; investigates HW defects |
| **Verifier (VER)** | Reviews this specification; reviews Test Report (Item 22); owns Item 23 |
| **Quality Assurance (QUA)** | Verifies process and template compliance |
| **Project Manager (PM)** | Routes all deliverables; INT submits to PM only |
| **Implementer (IMP)** | Fixes SW defects found in HW/SW integration |

---

## 12. REFERENCES

### 12.1 Normative References

- **EN 50128:2011** — Railway applications — Software for railway control and protection systems (§5.3.6, §7.6, Table A.6)
- **EN 50126:2017** — Railway applications — RAMS
- **MISRA C:2012** — Guidelines for the use of the C language in critical systems
- **IEC 61508:2010** — Functional safety of E/E/PE safety-related systems

### 12.2 Project References

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-SAS-2026-001 | Software Architecture Specification | 0.2 DRAFT |
| DOC-SDS-2026-001 | Software Design Specification | 0.1 DRAFT |
| DOC-SIS-2026-001 | Software Interface Specifications | 0.1 DRAFT |
| DOC-SRS-2026-001 | Software Requirements Specification | 0.1 DRAFT |
| DOC-HW-DES-2026-001 | Hardware Design Specification | TBD |
| DOC-SQAP-2026-001 | Software Quality Assurance Plan | — |
| DOC-SCMP-2026-001 | Software Configuration Management Plan | — |
| DOC-SVP-2026-001 | Software Verification Plan | — |
| DOC-SITSPEC-2026-001 | Software Integration Test Specification (Item 12) | 0.1 DRAFT |

---

## APPENDIX A: HW/SW TEST CASE SUMMARY TABLE

| TC ID | HW Phase | External Interface | Type | Priority | Safety Function |
|-------|----------|-------------------|------|----------|----------------|
| TC-HWSW-001 | 1 | EXT-002 | Interface, Functional | Critical | SF-005 |
| TC-HWSW-002 | 1 | EXT-005 | Interface, Functional | Critical | SF-002, SF-005 |
| TC-HWSW-003 | 1 | EXT-003 | Interface, Functional | Critical | SF-003 |
| TC-HWSW-004 | 1 | EXT-006 | Interface, Functional | Critical | SF-004 |
| TC-HWSW-005 | 1 | EXT-006 | Interface, Functional | Critical | SF-004 |
| TC-HWSW-006 | 1 | EXT-004 | Interface, Functional | Critical | SF-002 |
| TC-HWSW-007 | 2 | EXT-001 | Interface, Functional | Critical | SF-003 |
| TC-HWSW-008 | 2 | EXT-001 | Interface, Functional | Critical | SF-003 |
| TC-HWSW-009 | 2 | EXT-001 | Interface, Functional | Critical | SF-004 |
| TC-HWSW-010 | 3 | EXT-007 | Interface, Functional | Critical | SF-001 |
| TC-HWSW-011 | 3 | EXT-008 | Interface, Functional | Critical | SF-002 |
| TC-HWSW-012 | 3 | EXT-008 | Interface, Functional | High | SF-004 |
| TC-HWSW-013 | 4 | EXT-010 | Interface, Functional | Critical | SF-004, SF-005 |
| TC-HWSW-014 | 4 | EXT-010 | Interface, Error | Critical | SF-004 |
| TC-HWSW-015 | 4 | EXT-ADC | Interface, Functional | Critical | SF-003 |
| TC-HWSW-016 | 5 | EXT-009 | Interface, Functional | High | — |
| TC-HWSW-017 | 5 | EXT-011 | Interface, Functional | High | SF-002 |
| TC-HWSW-018 | 5 | EXT-012 | Interface, Functional | High | — |
| TC-HWSW-019 | 5 | EXT-013 | Interface, Functional | Medium | — |
| TC-HWSW-PERF-001 | 5 | ALL | Performance | Critical | All |
| TC-HWSW-PERF-002 | 5 | N/A | Resource | High | All |
| TC-HWSW-PERF-003 | 5 | N/A | Resource | High | All |
| TC-HWSW-PERF-004 | 5 | EXT-003 | Performance | Critical | SF-003 |
| TC-HWSW-FAULT-001 | 5 | EXT-007 | Fault Injection | High | SF-004 |
| TC-HWSW-FAULT-002 | 5 | N/A | Fault Injection | Critical | SF-004 |
| TC-HWSW-FAULT-003 | 5 | N/A | Fault Injection | Critical | SF-004 |

**Total test cases defined: 26**
**Total external interfaces covered: 14 / 14 (100%)**
**Total traceability links: ≥ 55** (interface → test case; test case → SF; test case → REQ-INT)

---

## APPENDIX B: PERIPHERAL REGISTER CONFIGURATION SUMMARY

The following STM32H743 peripheral configurations shall be verified during HW Phase 1–4
integration testing:

| Peripheral | Instance | Key Configuration | Test Case |
|------------|----------|------------------|-----------|
| IWDG | IWDG | Prescaler: /4 (3 kHz); Reload: 150 (50 ms @ 12 kHz LSI / 4) | TC-HWSW-004, TC-HWSW-005 |
| TIM1 | TIM1 | ARR for 20 kHz PWM; 4 channels CH1–CH4 active | TC-HWSW-007 |
| GPIO motor direction | GPIOE | PE8–PE11: push-pull output; open=LOW, close=HIGH | TC-HWSW-008 |
| GPIO lock actuator | GPIOB | Per schematic: open-drain, active-LOW | TC-HWSW-006 |
| GPIO position sensor | GPIOC/D | Pull-down; digital input; 2-reading debounce | TC-HWSW-001 |
| GPIO obstacle sensor | GPIOA | Interrupt: rising-edge; NVIC priority 0 (highest) | TC-HWSW-003 |
| bxCAN | CAN1 | 250 kbit/s; filter for IDs 0x100–0x104; FIFO0 | TC-HWSW-010 |
| SPI4 | SPI4 | Master (Ch A) / Slave (Ch B); 10 Mbit/s; CPOL=0, CPHA=0 | TC-HWSW-013 |
| USART1 | USART1 | RS-485; 115.2 kbit/s; 8N1; DE control on PB8 | TC-HWSW-016 |
| ADC1 | ADC1 | 12-bit; IN2–IN5; sampling time 8.5 cycles; 20 µs conversion | TC-HWSW-015 |
| USART3 | USART3 | Diagnostics; 115.2 kbit/s; 8N1 | TC-HWSW-019 |

---

**END OF DOCUMENT**

*Submitted to PM for routing to QUA and VER per EN 50128 §5.3.6 and WORKFLOW.md.*
