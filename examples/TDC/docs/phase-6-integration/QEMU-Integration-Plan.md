# QEMU Integration Plan

**REFERENCE**: EN 50128:2011 §7.6, §7.6.4.9, Table A.6; QEMU Tool Catalog `tools/catalog/qemu.yaml`

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-QEMUINTPLAN-2026-001 |
| **CI ID** | CI-QEMUINTPLAN-TDC-001 |
| **Version** | 1.0 |
| **Date** | 2026-04-04 |
| **Project** | TDC (Train Door Control System) |
| **SIL Level** | SIL 3 |
| **Author** | Software Integrator (INT) |
| **Reviewer** | Software Verifier (VER) |
| **Approver** | Software Validator (VAL) |
| **Status** | DRAFT — Submitted to PM for routing |
| **QEMU Version** | 8.2.2 (`/usr/bin/qemu-system-arm`) |
| **Tool Catalog Ref** | `tools/catalog/qemu.yaml` |

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 1.0 | 2026-04-04 | INT | Initial QEMU Integration Plan for HIL-pending test cases (Phase 6) and pre-validation support (Phase 7). | — |

## APPROVALS

**Signature Chain**

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Author (INT) | [INT Name] | _____________ | 2026-04-04 |
| Reviewer (QUA) | [QUA Name] | _____________ | [Date] |
| Approver (PM) | [PM Name] | _____________ | [Date] |

**Notes**:
- Author: INT — supplementary Phase 6 engineering document per EN 50128 §5.3.6.
- Reviewer (QUA): Format and process review per §6.5.
- Approver (PM): Project management approval and routing authority.
- INT MUST NOT contact QUA or VER directly — all submissions route through PM.

---

## 1. PURPOSE AND SCOPE

### 1.1 Purpose

This document defines the integration plan for using QEMU ARM System Emulator (v8.2.2)
to execute the four (4) HIL-pending test cases from the TDC Phase 6 HW/SW Integration
Test Report (DOC-HWINTTESTRPT-2026-001 v1.1) prior to availability of physical
STM32H743 hardware.

The plan also defines QEMU's role as a pre-validation environment to support Phase 7
(Overall Software Validation), enabling execution of additional functional scenarios
against a cross-compiled ARM binary before physical hardware is available.

### 1.2 Scope

**In scope**:
- Feasibility assessment of QEMU emulation for each of the 4 HIL-pending test cases
- QEMU board selection and configuration for TDC firmware emulation
- Cross-compilation procedure: TDC firmware for ARM Cortex-M4 QEMU target
- Test execution protocol for each HIL-pending test case under QEMU
- Limitation disclosure per EN 50128 §7.6.4.9 (simulation environment acknowledgement)
- Validation requirements: how QEMU results are cross-checked and error-bounded
- Tool qualification status and references (TCL assignment per `tools/catalog/qemu.yaml`)
- Pre-validation support protocol for Phase 7

**Out of scope**:
- Physical STM32H743 HIL test execution procedures (addressed in DOC-HWINTTESTSPEC-2026-001)
- QEMU Tool Validation Report (to be produced by TST per `deliverables/tools/QEMU-Tool-Validation-Report.md`)
- Phase 7 Overall Software Test Specification (VAL + TST responsibility)

### 1.3 Input Documents

| Document ID | Title | Version | Role |
|-------------|-------|---------|------|
| DOC-HWINTTESTRPT-2026-001 | HW/SW Integration Test Report (Item 22) | 1.1 | Source: 4 HIL-pending test cases |
| DOC-HWINTTESTSPEC-2026-001 | HW/SW Integration Test Specification (Item 13) | 0.1 DRAFT | Acceptance criteria for HIL-pending cases |
| DOC-SAS-2026-001 | Software Architecture Specification | 0.2 DRAFT | Component architecture; HAL layer |
| DOC-SDS-2026-001 | Software Design Specification | 0.1 DRAFT | Timing requirements; peripheral register detail |
| DOC-SRS-2026-001 | Software Requirements Specification | 0.1 DRAFT | REQ-PERF-001/003, REQ-INT-006, REQ-SAFE-018 |
| `tools/catalog/qemu.yaml` | QEMU Tool Catalog Entry | — | Tool qualification, TCL, known limitations |
| EN 50128:2011 | Railway Software Standard | 2011 | §7.6.4.9 simulation disclosure requirement |

---

## 2. QEMU TOOL QUALIFICATION SUMMARY

### 2.1 Tool Classification

Per `tools/catalog/qemu.yaml` and EN 50128 §6.7:

| Attribute | Value |
|-----------|-------|
| **Tool** | QEMU ARM System Emulator v8.2.2 |
| **Category** | Hardware Emulation |
| **Location** | `/usr/bin/qemu-system-arm` |
| **EN 50128 Ref** | Table A.6 (Integration Testing — HR SIL 3-4), §7.6 |
| **Mandatory by SIL** | HR (Highly Recommended) at SIL 3 |
| **TCL — Functional Testing** | **T1**: output verified by test assertions; no independent verification of tool output needed |
| **TCL — Performance/Timing** | **T2**: validation required to document known limitations, cross-check against static WCET analysis, and bound simulation error |

### 2.2 Tool Qualification Status

**Qualification status**: To be provided (see `deliverables/tools/QEMU-Tool-Validation-Report.md`).

**Action required**: TST SHALL produce the QEMU Tool Validation Report at path
`deliverables/tools/QEMU-Tool-Validation-Report.md` before QEMU-derived timing results
are submitted as Phase 6 evidence. This is a **mandatory pre-condition** for T2 usage.

For T1 (functional/logic) usage: QEMU test assertions provide independent verification
of output. No additional tool validation is required for functional tests where
pass/fail is determined by the firmware's own output (serial/semihosting) compared to
specification.

### 2.3 EN 50128 §7.6.4.9 Disclosure Requirement

EN 50128:2011 §7.6.4.9 states:
> *"Where simulation is used, it shall be clearly stated in the test report which items
> have been simulated and what the limitations of the simulation are."*

This document constitutes the §7.6.4.9 disclosure. All QEMU results produced under
this plan SHALL reference this document in the updated HW/SW Integration Test Report
(DOC-HWINTTESTRPT-2026-001) and/or supplementary test evidence.

---

## 3. QEMU HARDWARE CONFIGURATION

### 3.1 Board Selection Rationale

**Selected board**: `netduinoplus2` (Cortex-M4 @ emulated 168 MHz)

**Rationale**:

| Criterion | Assessment |
|-----------|------------|
| TDC target | STM32H743 (Cortex-M7 @ 400 MHz) |
| Best available QEMU board | `netduinoplus2` (Cortex-M4) — closest STM32-based Cortex-M board supported |
| ISA compatibility | ARMv7E-M (Cortex-M4) is a subset of ARMv7E-M+ (Cortex-M7); Thumb-2 instruction encoding is compatible for functional testing |
| Performance delta | Cortex-M4 @ emulated clock ≠ Cortex-M7 @ 400 MHz. **All timing values from QEMU are estimates only** (TCL T2); not valid as hardware measurements |
| Alternative board | `olimex-stm32-h405` (also Cortex-M4) — usable as secondary cross-check |
| Peripheral support | GPIO, USART, SPI approximated by QEMU machine model. CAN and IWDG peripheral fidelity is limited (see Section 4 limitations) |

**Explicit acknowledgement**: QEMU does NOT emulate the STM32H743. The `netduinoplus2`
machine model uses STM32F405-equivalent peripheral register layout. Any test relying
on specific peripheral register behaviour or silicon-level timing SHALL be classified
as "QEMU cannot substitute for physical hardware" in this plan.

### 3.2 Cross-Compilation Build Procedure

The TDC firmware must be cross-compiled for ARM Cortex-M4 (the QEMU target).

#### 3.2.1 Prerequisites

```bash
# Install ARM cross-compiler
sudo apt-get install gcc-arm-none-eabi binutils-arm-none-eabi

# Verify QEMU installation
qemu-system-arm --version   # Should report QEMU 8.2.2

# Verify cross-compiler
arm-none-eabi-gcc --version
```

#### 3.2.2 QEMU Target Build Configuration

Create `Makefile.qemu` (or pass flags to existing build system):

```makefile
# QEMU ARM Cortex-M4 cross-compilation flags
CC      = arm-none-eabi-gcc
CFLAGS  = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS += -std=c99 -Wall -Wextra -Wpedantic
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -DQEMU_TARGET -DCONFIG_CORTEX_M4
CFLAGS += -g3 -O1
LDFLAGS = -T linker/stm32f405_qemu.ld
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -specs=nano.specs -specs=nosys.specs
LDFLAGS += -lc -lgcc

# Output
TARGET  = build/tdc_qemu.elf
```

**Critical notes**:
- A QEMU-compatible linker script (`linker/stm32f405_qemu.ld`) defining the
  `netduinoplus2` flash/RAM map MUST be created. This is NOT the production
  STM32H743 linker script.
- The `QEMU_TARGET` preprocessor define MUST be used to conditionally exclude
  STM32H743-specific register addresses (IWDG_BASE, DWT, etc.) and redirect
  output to USART1 (semihosting or ITM).
- The production linker script and build flags SHALL NOT be modified.
  Cross-compilation for QEMU uses a parallel build path.

#### 3.2.3 Serial Output Redirect

For QEMU execution, firmware output is redirected to USART1 → stdio:

```c
/* In tdc_qemu_bsp.c (QEMU-specific BSP layer, NOT part of safety software) */
#ifdef QEMU_TARGET
  /* Redirect printf to USART1 serial → QEMU stdio */
  void _write(int fd, char *buf, int count) {
      for (int i = 0; i < count; i++) {
          USART1->DR = buf[i];
          while (!(USART1->SR & USART_SR_TXE));
      }
  }
#endif
```

#### 3.2.4 QEMU Launch Command

```bash
# Functional testing (T1) — netduinoplus2 with serial output to terminal
qemu-system-arm \
    -M netduinoplus2 \
    -cpu cortex-m4 \
    -kernel build/tdc_qemu.elf \
    -nographic \
    -serial stdio \
    -no-reboot

# With timeout guard (for automated CI)
timeout 60 qemu-system-arm \
    -M netduinoplus2 \
    -cpu cortex-m4 \
    -kernel build/tdc_qemu.elf \
    -nographic \
    -serial stdio \
    -no-reboot \
    2>&1 | tee qemu_output.log
```

---

## 4. FEASIBILITY ASSESSMENT — 4 HIL-PENDING TEST CASES

### 4.1 Assessment Summary Table

| TC ID | HIL-PENDING ID | Test Objective | QEMU Feasibility | Rationale | Notes |
|-------|---------------|----------------|-----------------|-----------|-------|
| TC-HWSW-005 | HIL-PENDING-001 | IWDG hardware timeout 50 ms ± 5 ms (NRST pulse) | **Physical hardware required** | IWDG is silicon-level peripheral. QEMU cannot model LSI oscillator (±10% tolerance) or generate real NRST reset events. The `HAL_Watchdog_Refresh` stub always succeeds; QEMU machine has no IWDG peripheral model for netduinoplus2 that can produce a real silicon watchdog reset. | Partial QEMU coverage only: watchdog API call sequence and software path can be exercised via QEMU functional test. Timeout measurement requires real hardware. |
| TC-HWSW-PERF-001 | HIL-PENDING-002 | WCET ≤ 16 ms via DWT cycle counter at 400 MHz | **QEMU-feasible with limitations** | QEMU can execute the worst-case scenario (4 doors closing, all obstacle flags set, CAN+SPI stubs active). Cycle counts on Cortex-M4 at emulated clock are NOT valid hardware measurements (TCL T2). Result must be cross-checked against static WCET analysis. Can provide upper-bound execution path validation. | QEMU can confirm no infinite loops, identify unexpected branches. Cannot replace DWT measurement on real 400 MHz silicon. Must document simulation error bound. |
| TC-HWSW-PERF-004 | HIL-PENDING-003 | ISR latency ≤ 1 ms (obstacle GPIO interrupt to ISR entry) | **Physical hardware required** | NVIC interrupt latency is hardware-specific. QEMU Cortex-M4 interrupt simulation does not model precise NVIC pipeline timing. Oscilloscope measurement (GPIO pulse vs ISR-entry GPIO toggle) is hardware-only. QEMU cannot substitute for two-channel oscilloscope measurement. | QEMU functional coverage only: can verify that the ISR handler is invoked and completes correctly (T1). Cannot measure latency (T2 not applicable — latency is physical, not estimable via QEMU). |
| TC-HWSW-FAULT-002 | HIL-PENDING-004 | Memory CRC corruption via JTAG (OpenOCD/GDB memory write during execution) | **QEMU-feasible with limitations** | QEMU supports GDB remote stub (`-s -S` flags). A GDB script can write to emulated SRAM during firmware execution — analogous to JTAG memory write on real hardware. This can trigger the SKN CRC check and validate the `safe_state_active=1` response chain. Limitation: QEMU SRAM is host memory; the corruption semantics differ from real silicon SRAM corruption (no ECC, no hardware memory protection). | Functionally valid for verifying the software CRC check logic and safe state response. Cannot verify hardware ECC response or physical memory fault injection. |

### 4.2 Detailed Feasibility Analysis

---

#### 4.2.1 TC-HWSW-005: IWDG Hardware Timeout — **Physical Hardware Required**

**Test objective** (from HIL-PENDING-001, DOC-HWINTTESTRPT-2026-001 §8):
Verify that the IWDG peripheral resets the MCU at 50 ms ± 5 ms when watchdog
refresh is withheld; verify RCC_RSR IWDG flag is set; verify cold-start safe state.

**QEMU analysis**:

| Aspect | QEMU Capability | Assessment |
|--------|-----------------|-----------|
| IWDG peripheral model | `netduinoplus2` machine does not model IWDG register set (IWDG_KR, IWDG_PR, IWDG_RLR) with clock-accurate countdown | **Cannot simulate** |
| LSI oscillator accuracy (±10%) | QEMU has no LSI clock model; internal timer does not emulate LSI tolerance | **Cannot simulate** |
| Hardware reset event (NRST pulse) | QEMU can model software reset (`NVIC_SystemReset`) but not IWDG-triggered silicon reset with NRST pin | **Cannot simulate** |
| RCC reset cause flag (RCC_RSR) | STM32F405 register layout differs from STM32H743; QEMU machine model does not support RCC_RSR IWDG bit | **Cannot simulate** |
| Software path (watchdog refresh logic) | QEMU CAN execute `HAL_Watchdog_Refresh()` call sequence; verify correct invocation in scheduler cycle | **Partial T1 coverage** |

**QEMU what CAN be tested**:
- That `HAL_Watchdog_Refresh()` is called once per scheduler cycle (functional path, T1)
- That withholding refresh does not cause a software crash (code path coverage)
- That the watchdog refresh integration sequence in `skn_safe_state.c` is exercised

**Verdict**: **Physical hardware required** for TC-HWSW-005. QEMU cannot replace the
50 ms ± 5 ms silicon timeout measurement. A partial QEMU test (`TC-QEMU-IWDG-CALL`)
can supplement, but does NOT discharge HIL-PENDING-001.

---

#### 4.2.2 TC-HWSW-PERF-001: WCET Measurement — **QEMU-Feasible with Limitations**

**Test objective** (from HIL-PENDING-002, DOC-HWINTTESTRPT-2026-001 §8):
Verify WCET ≤ 16 ms on STM32H743 @ 400 MHz via DWT cycle counter; worst-case
scenario: 4 doors closing + all obstacle flags + CAN + SPI active.

**QEMU analysis**:

| Aspect | QEMU Capability | Assessment |
|--------|-----------------|-----------|
| Worst-case code path execution | QEMU can run firmware with worst-case inputs via HAL stub injection | **Can simulate (T1 — path coverage)** |
| DWT cycle counter | QEMU Cortex-M4 does NOT implement DWT (Data Watchpoint and Trace) peripheral | **Cannot use DWT** |
| Timing accuracy (16 ms threshold) | QEMU cycle counts are NOT representative of Cortex-M7 @ 400 MHz (different pipeline, FPU, cache, peripheral stall cycles) | **T2 — estimate only; large error bound** |
| Execution path completeness | QEMU verifies all code branches are executed; confirms no path leads to infinite loop | **High value (T1)** |
| Static WCET cross-check | QEMU timing can be compared against static analysis (STACK tool or similar) to bound error | **Cross-check applicable** |

**QEMU test procedure** (`TC-QEMU-WCET-001`):
1. Cross-compile firmware with `QEMU_TARGET` and performance logging stubs
2. Configure worst-case stub state (4 doors: DSM_CLOSING, `g_obstacle_flags=0xF`, CAN+SPI busy)
3. Launch QEMU; firmware instruments start/end of `SKN_RunCycle()` via USART1 timestamp
4. Capture 1,000 cycle measurements via QEMU serial output
5. Report: max QEMU elapsed time, execution path coverage (confirms all worst-case branches hit)
6. Cross-check: compare QEMU max elapsed with static WCET analysis result

**Simulation error bound requirement** (TCL T2):
```
Bound = f(cycle_count_QEMU) × (400 MHz / emulated_clock) × pipeline_factor
```
A conservative factor ≥ 2.0× shall be applied to all QEMU timing estimates until
validated against physical hardware. If static WCET analysis gives T_wcet_static,
and QEMU gives T_qemu, then:
- If `T_qemu × 2.0 < 16 ms`: moderate confidence (still requires HIL confirmation)
- If `T_qemu × 2.0 ≥ 16 ms`: escalate immediately — possible WCET violation risk

**Verdict**: **QEMU-feasible with limitations.** QEMU execution of TC-HWSW-PERF-001
provides:
1. Confirmation of worst-case execution path coverage (no infinite loops, correct branches)
2. Rough timing estimate with documented 2× simulation error factor
3. Does NOT discharge HIL-PENDING-002. Physical STM32H743 DWT measurement is still
   required before Phase 7 final sign-off.

---

#### 4.2.3 TC-HWSW-PERF-004: ISR Latency — **Physical Hardware Required**

**Test objective** (from HIL-PENDING-003, DOC-HWINTTESTRPT-2026-001 §8):
Verify obstacle ISR latency ≤ 1 ms via two-channel oscilloscope (GPIO pulse → ISR-entry
GPIO toggle) on real STM32H743 silicon.

**QEMU analysis**:

| Aspect | QEMU Capability | Assessment |
|--------|-----------------|-----------|
| GPIO interrupt simulation | QEMU Cortex-M4 models NVIC; external interrupt can be triggered via GDB `monitor` or semihosting | **Partial — functional only** |
| NVIC interrupt latency accuracy | QEMU does not model exact Cortex-M7 interrupt latency pipeline (typically 12 cycles at 400 MHz + context save). QEMU timing includes host OS scheduling jitter | **Cannot measure accurately** |
| Oscilloscope-equivalent measurement | No oscilloscope or GPIO timing measurement capability in QEMU | **Cannot simulate** |
| ISR handler execution (functional) | QEMU CAN verify that `OBD_ObstacleISR` is invoked when EXTI interrupt fires, flag is set, and DSM reversal is triggered | **T1 functional coverage** |

**QEMU what CAN be tested**:
- That `OBD_ObstacleISR` is correctly registered and invoked by the NVIC on EXTI line assertion
- That the ISR sets `g_obstacle_flags` correctly
- That the scheduler detects the flag and initiates door reversal (functional chain)

**Verdict**: **Physical hardware required** for TC-HWSW-PERF-004. QEMU cannot provide
a valid ISR latency measurement. A partial QEMU test (`TC-QEMU-ISR-FUNC`) can verify
ISR invocation (T1), but does NOT discharge HIL-PENDING-003.

---

#### 4.2.4 TC-HWSW-FAULT-002: Memory CRC via JTAG — **QEMU-Feasible with Limitations**

**Test objective** (from HIL-PENDING-004, DOC-HWINTTESTRPT-2026-001 §8):
Via OpenOCD/GDB on real silicon: corrupt `door_states[0]` in SRAM during execution;
verify CRC mismatch detected ≤ 120 ms; `safe_state_active=1`; `FAULT_CRC_ERROR` logged.

**QEMU analysis**:

| Aspect | QEMU Capability | Assessment |
|--------|-----------------|-----------|
| GDB remote stub | QEMU supports `-s` (GDB server on TCP:1234) + `-S` (halt at startup) | **Supported** |
| SRAM memory write during execution | GDB `set {uint32_t}0x<address> = <value>` can corrupt specific SRAM location while firmware runs | **Functional equivalent** |
| CRC detection response | After corruption, SKN cycle runs; CRC mismatch triggers `safe_state_active=1` | **Testable in QEMU (T1)** |
| DGN log verification | Fault log entry `FAULT_CRC_ERROR` readable via USART1 output or GDB memory read | **Testable in QEMU (T1)** |
| Timing: ≤ 120 ms detection | QEMU timing is approximate (TCL T2); 120 ms is a coarse bound — QEMU can validate order-of-magnitude correctness (≤ N scheduler cycles) | **T2 estimate only** |
| Hardware ECC / memory protection | QEMU does not model STM32H743 SRAM ECC; physical memory fault injection via hardware bus errors cannot be simulated | **Cannot simulate** |

**QEMU test procedure** (`TC-QEMU-MEMCRC-001`):
1. Cross-compile firmware with `QEMU_TARGET`; flash address of `door_states[0]` known from map file
2. Launch QEMU with GDB server: `qemu-system-arm -M netduinoplus2 ... -s -S`
3. Attach GDB: `arm-none-eabi-gdb build/tdc_qemu.elf`
4. Set breakpoint at SKN CRC check entry; run firmware to steady state (all doors IDLE)
5. While running: `(gdb) set {uint32_t}door_states[0].state = 0xFF` (corrupt known field)
6. Continue execution; capture USART1 output for `FAULT_CRC_ERROR` log entry
7. Read `safe_state_active` via GDB after up to 150 ms emulated time
8. Pass criterion: CRC fault logged; `safe_state_active=1`; no crash

**Simulation limitations for this test**:
- QEMU SRAM write is a host memory write; it does not model hardware memory bus fault injection
- If the firmware uses hardware ECC detection (STM32H743 SRAM ECC hardware), this path
  cannot be exercised by QEMU
- The 120 ms timing acceptance criterion cannot be rigorously verified; count scheduler
  cycles instead (should trigger within 2 scheduler cycles = ≤ 32 ms worst case)

**Verdict**: **QEMU-feasible with limitations.** The software CRC detection and safe
state response chain can be functionally verified via QEMU+GDB. This provides significant
confidence in the software logic. However:
- Does NOT replace JTAG-based physical test (hardware ECC path not covered)
- Timing bound must be expressed in scheduler cycles, not milliseconds, under QEMU
- HIL-PENDING-004 is partially discharged by QEMU; physical hardware confirms ECC path

---

## 5. QEMU FEASIBILITY SUMMARY

### 5.1 HIL-Pending Reduction Assessment

| TC ID | QEMU Verdict | HIL Still Required? | QEMU Contribution |
|-------|-------------|--------------------|--------------------|
| TC-HWSW-005 (IWDG timeout) | Physical hardware required | **YES — HIL-PENDING-001 not discharged** | Partial: watchdog API call-path coverage only |
| TC-HWSW-PERF-001 (WCET) | QEMU-feasible with limitations | **YES — HIL-PENDING-002 not fully discharged** | Partial: worst-case path coverage + timing estimate with 2× error bound |
| TC-HWSW-PERF-004 (ISR latency) | Physical hardware required | **YES — HIL-PENDING-003 not discharged** | Partial: ISR functional invocation verification only |
| TC-HWSW-FAULT-002 (JTAG CRC) | QEMU-feasible with limitations | **YES — HIL-PENDING-004 partially discharged** | Significant: GDB memory write + CRC detection chain fully verifiable |

**Recommendation**: QEMU execution CANNOT fully replace any of the 4 HIL-pending
test cases for SIL 3 compliance purposes. The 4 HIL-pending items remain HIL-required
for Phase 7 final sign-off. However, QEMU adds measurable value:

1. **TC-HWSW-FAULT-002 (JTAG CRC)**: The software logic is substantially verifiable
   via QEMU+GDB. The GDB memory write approach is functionally equivalent to JTAG
   injection for the software CRC path. **This is the strongest QEMU use case.**

2. **TC-HWSW-PERF-001 (WCET)**: QEMU confirms worst-case code path execution and
   provides a gross timing estimate. If the estimate is well below the 16 ms threshold
   (e.g., ≤ 4 ms in QEMU), it provides advance confidence. Formal verification still
   requires DWT on real silicon.

3. **TC-HWSW-005 (IWDG)** and **TC-HWSW-PERF-004 (ISR latency)**: QEMU provides only
   functional supplementary coverage, not measurement capability. Physical hardware
   remains mandatory for these.

### 5.2 New QEMU Test Cases Defined

The following supplementary QEMU test cases are defined under this plan:

| TC ID | Test Case | Linked HIL-PENDING | TCL | Discharges HIL? |
|-------|----------|-------------------|-----|----------------|
| TC-QEMU-WCET-001 | Worst-case execution path + timing estimate | HIL-PENDING-002 | T2 | No (partial) |
| TC-QEMU-MEMCRC-001 | Memory CRC corruption via GDB write | HIL-PENDING-004 | T1 | No (partial) |
| TC-QEMU-ISR-FUNC-001 | ISR invocation functional verification | HIL-PENDING-003 | T1 | No (supplementary) |
| TC-QEMU-IWDG-CALL-001 | Watchdog API call-path coverage | HIL-PENDING-001 | T1 | No (supplementary) |

---

## 6. QEMU TEST EXECUTION PROTOCOLS

### 6.1 TC-QEMU-WCET-001: Worst-Case Execution Path + Timing Estimate

**Linked HIL-PENDING**: HIL-PENDING-002 (TC-HWSW-PERF-001)
**TCL**: T2 (timing estimate — T2 validation applies; see Section 2.2)
**Precondition**: QEMU Tool Validation Report approved by TST/PM

**Setup**:
```bash
# 1. Cross-compile with QEMU target
make -f Makefile.qemu EXTRA_CFLAGS="-DWCET_QEMU_TRACE" TARGET=tdc_qemu_wcet.elf

# 2. Launch QEMU with serial output capture
timeout 120 qemu-system-arm \
    -M netduinoplus2 \
    -cpu cortex-m4 \
    -kernel build/tdc_qemu_wcet.elf \
    -nographic -serial stdio -no-reboot \
    2>&1 | tee qemu_wcet_output.log
```

**Worst-case stimulus** (encoded in firmware via `QEMU_TARGET` block):
```c
#ifdef WCET_QEMU_TRACE
/* Inject worst-case state at startup */
for (uint8_t i = 0; i < MAX_DOORS; i++) {
    hal_stub_gpio_value[i] = 1;          /* sensors asserted */
    g_obstacle_flags[i] = 1;            /* obstacle on every door */
}
/* Force all doors into FSM_CLOSING state */
/* CAN stub returns ERR_TIMEOUT to maximize branch path */
hal_stub_can_receive_ret = ERR_TIMEOUT;
/* SPI stub: force max data processing path */
hal_stub_spi_exchange_ret = SUCCESS;
#endif
```

**Pass criteria** (QEMU WCET test):
1. Firmware executes ≥ 10,000 scheduler cycles without hang or crash
2. USART1 reports cycle timestamp delta for 10,000 worst-case cycles
3. Maximum reported cycle time: record in QEMU WCET evidence
4. Cross-check: `T_qemu_max × 2.0 < 16,000 µs` (if met: advance confidence)
5. No infinite loop, unexpected exception, or hard fault reported

**Evidence file**: `docs/phase-6-integration/qemu-evidence/qemu-wcet-output.log`

---

### 6.2 TC-QEMU-MEMCRC-001: Memory CRC Corruption via GDB

**Linked HIL-PENDING**: HIL-PENDING-004 (TC-HWSW-FAULT-002)
**TCL**: T1 (functional verification — pass/fail determined by firmware output)
**Precondition**: QEMU functional capability confirmed; no T2 qualification needed for T1 usage

**Setup**:
```bash
# Terminal 1: Launch QEMU with GDB server (halted at startup)
qemu-system-arm \
    -M netduinoplus2 \
    -cpu cortex-m4 \
    -kernel build/tdc_qemu.elf \
    -nographic -serial stdio \
    -s -S &
QEMU_PID=$!

# Terminal 2: Attach GDB
arm-none-eabi-gdb build/tdc_qemu.elf \
    -ex "target remote :1234" \
    -ex "load" \
    -ex "break main" \
    -ex "continue"
```

**GDB corruption script** (`tools/qemu/corrupt_mem_crc_test.gdb`):
```gdb
# Wait for firmware to reach steady-state (all doors IDLE, CRC valid)
# Step 1: Run to steady state
continue &
sleep 2

# Step 2: Locate door_states[0] in memory map (from tdc_qemu.map)
# Example address — update from actual map file
set $door_states_base = (uint32_t *)0x20000100

# Step 3: Corrupt door_states[0].state field
set {uint32_t}$door_states_base = 0xDEADBEEF

# Step 4: Continue execution; SKN_RunCycle will detect CRC mismatch
continue

# Step 5: After next scheduler cycle, check safe_state_active
# (from skn_globals address in map file)
print g_safe_state_active

# Expected: g_safe_state_active == 1
# Expected: USART1 output contains "FAULT_CRC_ERROR"
```

**Pass criteria** (QEMU CRC test):
1. `g_safe_state_active == 1` after corruption (read via GDB or USART output)
2. `FAULT_CRC_ERROR` appears in USART1 capture log
3. Safe state is sticky (subsequent GDB reads confirm value remains 1)
4. No firmware crash or unexpected exception before CRC detection

**Evidence file**: `docs/phase-6-integration/qemu-evidence/qemu-memcrc-output.log`

---

### 6.3 TC-QEMU-ISR-FUNC-001: ISR Functional Invocation

**Linked HIL-PENDING**: HIL-PENDING-003 (TC-HWSW-PERF-004)
**TCL**: T1 (functional — verifies ISR is invoked, not latency)

**Procedure**:
1. Cross-compile firmware; obstacle EXTI line mapped to QEMU-supported GPIO
2. Use QEMU GDB interface to assert EXTI interrupt line: `monitor system_reset` +
   set EXTI pending bit via memory write
3. Confirm `OBD_ObstacleISR` is entered (GDB breakpoint at ISR entry)
4. Confirm `g_obstacle_flags` set after ISR returns
5. Run one scheduler cycle; confirm DSM door reversal triggered

**Pass criteria**: ISR invoked; `g_obstacle_flags` set; DSM reversal initiated; no crash.

**Evidence file**: `docs/phase-6-integration/qemu-evidence/qemu-isr-func-output.log`

---

### 6.4 TC-QEMU-IWDG-CALL-001: Watchdog API Call-Path Coverage

**Linked HIL-PENDING**: HIL-PENDING-001 (TC-HWSW-005)
**TCL**: T1 (functional — verifies API call path; NOT silicon timeout)

**Procedure**:
1. Launch QEMU with normal firmware
2. Confirm USART1 log shows `HAL_Watchdog_Refresh()` invoked each scheduler cycle
3. Confirm no unexpected watchdog-related errors in normal operation (1,000 cycles)
4. Withhold refresh (patch firmware to skip refresh call via conditional compile);
   confirm code path exits normally (for HAL API, not for silicon timeout)

**Pass criteria**: Watchdog API called correctly in scheduler cycle; no false errors.
**Limitation noted**: Silicon watchdog timeout (50 ms ± 5 ms) is NOT verified by this test.

**Evidence file**: `docs/phase-6-integration/qemu-evidence/qemu-iwdg-call-output.log`

---

## 7. EN 50128 §7.6.4.9 SIMULATION LIMITATION DISCLOSURE

Per EN 50128:2011 §7.6.4.9, the following simulation limitations are formally disclosed
for all QEMU-derived test evidence:

### 7.1 Hardware Platform Mismatch

**Simulated**: ARM Cortex-M4 @ approximately 168 MHz (QEMU `netduinoplus2` machine model)
**Target**: ARM Cortex-M7 @ 400 MHz (STM32H743VIT6)

The following differences exist and SHALL NOT be ignored in interpretation of results:

| Parameter | QEMU / netduinoplus2 | TDC Target / STM32H743 | Impact |
|-----------|---------------------|------------------------|--------|
| CPU Core | Cortex-M4 (ARMv7E-M) | Cortex-M7 (ARMv7E-M+) | Pipeline depth, FPU performance differ |
| Clock frequency | Emulated (not real-time) | 400 MHz (PLL from HSE) | All timing results are estimates |
| DWT cycle counter | Not modelled | Present (required for WCET) | DWT-based WCET not possible in QEMU |
| IWDG peripheral | Not modelled (or differs from STM32H743 IWDG_PR/RLR) | Silicon-accurate | Watchdog timeout cannot be measured |
| CAN peripheral | Not modelled (netduinoplus2 has no CAN) | FDCAN on STM32H743 | CAN bus-level tests not executable in QEMU |
| GPIO interrupt timing | Approximated | NVIC 12-cycle latency at 400 MHz | ISR latency not measurable |
| SRAM ECC | Not modelled | STM32H743 has hardware ECC on SRAM | ECC fault path not testable |
| ADC peripheral | Not modelled | ADC1 on STM32H743 with DMA | ADC ramp test not executable |

### 7.2 TCL-Specific Limitations

**T1 (functional) results** (TC-QEMU-MEMCRC-001, TC-QEMU-ISR-FUNC-001,
TC-QEMU-IWDG-CALL-001): These are valid functional test results. Pass/fail is
determined by firmware output (assertions, USART log), which is independent of
platform-specific timing. The verification is valid for software logic correctness.

**T2 (timing estimate) results** (TC-QEMU-WCET-001): These are estimates ONLY.
The simulation error bound (≥ 2×) SHALL be applied to all QEMU timing figures.
T2 results MUST be cross-checked against static WCET analysis before any timing
claim is made. T2 results SHALL NOT appear as measured WCET values in any EN 50128
deliverable without the 2× error bound and cross-check explicitly stated.

### 7.3 Results Validity Statement

> **QEMU-derived test results (PASS verdicts) are valid for software logic
> correctness (T1 usage). They are NOT valid as substitutes for physical hardware
> measurements of timing, peripheral electrical behaviour, or silicon-level fault
> injection. All four HIL-pending items remain HIL-required for Phase 7 final
> sign-off per DOC-HWINTTESTRPT-2026-001 §13.2.**

---

## 8. VALIDATION REQUIREMENTS AND CROSS-CHECKS

### 8.1 QEMU Result Cross-Check Protocol

Before QEMU results are presented as evidence in updated Phase 6 deliverables:

| Step | Action | Responsible | Required Before |
|------|--------|-------------|----------------|
| V1 | Confirm QEMU Tool Validation Report produced | TST (via PM) | Any T2 result use |
| V2 | Cross-compile TDC firmware; verify build succeeds with zero errors | INT/TST | All QEMU tests |
| V3 | Run TC-QEMU-MEMCRC-001; compare output against stub-based TC-HWSW-FAULT-002 specification | TST | QEMU evidence for FAULT-002 |
| V4 | Run TC-QEMU-WCET-001; compare QEMU max cycle time against static WCET from VER/TST | INT/TST | QEMU timing evidence |
| V5 | Apply 2× simulation error factor to all T2 timing figures | INT | Any timing claim |
| V6 | Document QEMU vs. physical hardware result delta in updated DOC-HWINTTESTRPT-2026-001 | INT | Phase 7 entry |
| V7 | VER reviews QEMU evidence and updates verification matrix | VER (via PM) | Phase 7 gate |

### 8.2 WCET Simulation Error Bound

The simulation error bound for QEMU Cortex-M4 → STM32H743 Cortex-M7 timing:

```
T_real_estimate = T_qemu × K_arch × K_clock × K_peripheral

Where:
  K_arch = 1.3  (Cortex-M7 pipeline vs Cortex-M4 — M7 is typically faster)
  K_clock = 400/168 ≈ 2.4  (clock ratio; QEMU emulated vs real silicon)
  K_peripheral = 1.5  (peripheral stall cycles on real hardware)

Conservative composite factor = 2.0 × (applied uniformly)
```

If QEMU reports T_qemu_max:
- Estimated real WCET ≤ T_qemu_max × 2.0 (conservative upper bound)
- If T_qemu_max × 2.0 < 8 ms: Low risk (well within 16 ms budget)
- If 8 ms ≤ T_qemu_max × 2.0 < 16 ms: Moderate risk — escalate to PM; prioritise HIL
- If T_qemu_max × 2.0 ≥ 16 ms: HIGH RISK — immediate PM notification; possible REQ violation

---

## 9. PHASE 7 PRE-VALIDATION SUPPORT

### 9.1 Pre-Validation Environment

QEMU provides a pre-validation environment for Phase 7 (Overall Software Validation)
for functional scenario testing before physical hardware is available.

**Phase 7 pre-validation scope** (QEMU, T1 only):
- Full system scenario: train approaching station → doors open → obstacle → reversal → close
- Emergency release scenario: speed=0, emergency GPIO assertion → unlock
- Safe state propagation: multi-fault injection via GDB → all motors stop
- CAN protocol scenarios: departure interlock, speed timeout, fault reporting

**Phase 7 pre-validation scope** (NOT QEMU — requires hardware):
- Any timing-dependent acceptance test
- CAN bus electrical layer verification
- Physical actuator response measurement
- IWDG watchdog validation

### 9.2 Phase 7 QEMU Evidence Status

All QEMU-derived Phase 7 evidence SHALL be labelled:
```
[QEMU-PRE-VAL] — Functional scenario confirmed in QEMU simulation.
Physical hardware validation required before final acceptance.
```

This label SHALL appear in Phase 7 test records wherever QEMU pre-validation
results are used to support Phase 7 test case execution.

---

## 10. RISK REGISTER

| Risk ID | Risk | Likelihood | Severity | Mitigation |
|---------|------|-----------|---------|-----------|
| QEMU-RISK-001 | Cross-compilation fails due to STM32H743-specific intrinsics in TDC source | Medium | High | Audit `src/*.c` for H7-specific register defines; create `#ifdef QEMU_TARGET` exclusions |
| QEMU-RISK-002 | QEMU netduinoplus2 peripheral model incompatible with TDC HAL assumptions | Medium | Medium | Run with `-nographic -serial stdio` only; use software-only HAL paths; stub remaining peripherals |
| QEMU-RISK-003 | QEMU timing results used without 2× error factor — WCET false confidence | Low | Critical | **Mandatory**: all T2 results SHALL carry documented 2× bound (enforced by INT) |
| QEMU-RISK-004 | QEMU Tool Validation Report not produced before T2 evidence presented | Low | High | INT to confirm with PM that TST has produced validation report before Phase 6 evidence update |
| QEMU-RISK-005 | GDB memory write address incorrect (SRAM layout differs QEMU vs hardware) | Medium | Medium | Use actual `tdc_qemu.map` to extract `door_states` address; verify via GDB symbol lookup before corruption |
| QEMU-RISK-006 | Phase 7 team uses QEMU pre-validation PASS as final acceptance | Low | Critical | Phase 7 test plan SHALL explicitly state which tests require physical hardware; COD gate-check enforces |

---

## 11. OPEN ACTIONS

| Action ID | Description | Responsible | Precondition | Status |
|-----------|-------------|-------------|-------------|--------|
| ACT-QEMU-001 | Produce QEMU Tool Validation Report | TST (via PM) | QEMU available | OPEN |
| ACT-QEMU-002 | Create QEMU linker script (`linker/stm32f405_qemu.ld`) | IMP (via PM) | — | OPEN |
| ACT-QEMU-003 | Audit `src/*.c` for STM32H743-specific register addresses; add `#ifdef QEMU_TARGET` guards | IMP (via PM) | — | OPEN |
| ACT-QEMU-004 | Execute TC-QEMU-MEMCRC-001; capture GDB output log | TST (via PM) | ACT-QEMU-002 complete | OPEN |
| ACT-QEMU-005 | Execute TC-QEMU-WCET-001; produce WCET estimate log | TST (via PM) | ACT-QEMU-002, ACT-QEMU-001 complete | OPEN |
| ACT-QEMU-006 | Update DOC-HWINTTESTRPT-2026-001 with QEMU evidence references | INT (via PM) | ACT-QEMU-004, ACT-QEMU-005 complete | OPEN |
| ACT-QEMU-007 | Confirm VER reviews updated QEMU evidence | VER (via PM) | ACT-QEMU-006 complete | OPEN |

---

## 12. TRACEABILITY

### 12.1 Test Cases → HIL-Pending Items

| QEMU Test Case | Linked HIL-PENDING | Specification Ref | Discharges? |
|----------------|-------------------|-------------------|-------------|
| TC-QEMU-WCET-001 | HIL-PENDING-002 | DOC-HWINTTESTSPEC-2026-001 §4.7 | No (partial path coverage) |
| TC-QEMU-MEMCRC-001 | HIL-PENDING-004 | DOC-HWINTTESTSPEC-2026-001 §4.8 | Partial (software logic verified; not hardware ECC) |
| TC-QEMU-ISR-FUNC-001 | HIL-PENDING-003 | DOC-HWINTTESTSPEC-2026-001 §4.7 | No (functional only) |
| TC-QEMU-IWDG-CALL-001 | HIL-PENDING-001 | DOC-HWINTTESTSPEC-2026-001 §4.2 | No (API path only) |

### 12.2 Requirements → Test Coverage

| Requirement | Description | HIL-Pending TC | QEMU Supplement |
|-------------|-------------|---------------|----------------|
| REQ-INT-006 | IWDG watchdog refresh | TC-HWSW-005 | TC-QEMU-IWDG-CALL-001 |
| REQ-PERF-001 | WCET ≤ 16 ms | TC-HWSW-PERF-001 | TC-QEMU-WCET-001 |
| REQ-PERF-003 | ISR latency ≤ 1 ms | TC-HWSW-PERF-004 | TC-QEMU-ISR-FUNC-001 |
| REQ-SAFE-018 | Memory CRC detection ≤ 120 ms | TC-HWSW-FAULT-002 | TC-QEMU-MEMCRC-001 |

---

## 13. REFERENCES

### 13.1 Normative References

- **EN 50128:2011** — §7.6 (Integration Testing), §7.6.4.9 (Simulation Disclosure),
  Table A.6 (Integration Techniques), §6.7 (Tool Qualification)

### 13.2 Project Documents

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-HWINTTESTRPT-2026-001 | HW/SW Integration Test Report (Item 22) | 1.1 |
| DOC-HWINTTESTSPEC-2026-001 | HW/SW Integration Test Specification (Item 13) | 0.1 DRAFT |
| DOC-SAS-2026-001 | Software Architecture Specification | 0.2 DRAFT |
| DOC-SDS-2026-001 | Software Design Specification | 0.1 DRAFT |
| DOC-SRS-2026-001 | Software Requirements Specification | 0.1 DRAFT |

### 13.3 Tool References

| Reference | Description |
|-----------|-------------|
| `tools/catalog/qemu.yaml` | QEMU Tool Catalog Entry (TCL, limitations, flags) |
| `deliverables/tools/QEMU-Tool-Validation-Report.md` | QEMU Tool Validation Report (to be produced by TST) |
| `deliverables/tools/Tool-Validation-Report-template.md` | Tool Validation Report template |

---

**END OF DOCUMENT**

*Submitted to PM for routing to QUA and VER per EN 50128 §5.3.6 and WORKFLOW.md.*
