# Software Source Code and Supporting Documentation — Item 18
## TDC Train Door Control System

---

## Document Control

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SOURCECODE-2026-001 |
| **Version** | 1.0 |
| **Date** | 2026-04-04 |
| **Author** | IMP |
| **Status** | Draft |

---

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Author | IMP | IMP | 2026-04-04 |
| Reviewer (QUA) | QUA | ___ | ___ |
| Approver (PM) | PM | ___ | ___ |

---

## 1. Scope

This document is the formal package wrapper for **Annex C Item 18 — Software Source Code
and Supporting Documentation** for the TDC (Train Door Control System) project.

| Property | Value |
|----------|-------|
| **Project** | TDC (Train Door Control System) |
| **SIL Level** | 3 |
| **Phase** | 5 (Implementation and Testing) |
| **Annex C Item** | 18 |
| **Design Input** | SCDS DOC-COMPDES-2026-001 (Item 15) |
| **Source Path** | `examples/TDC/src/` |
| **Language** | C (MISRA C:2012) |
| **Total Files** | 31 (9 headers + 21 implementation + 1 traceability matrix) |

Supporting documentation included in this package:

- `TRACEABILITY.md` — Design-to-code traceability matrix (unit IDs → functions → SRS requirements)

---

## 2. Source Code Package Manifest

All files are at version 1.0 (initial release). SHA-256 hashes computed at time of package
assembly (2026-04-04). Any modification invalidates the hash and requires a new baseline.

### 2.1 Header Files (9 files)

| File | Component | COMP-ID | SCDS Ref | Version | SHA-256 Hash |
|------|-----------|---------|----------|---------|--------------|
| `tdc_types.h` | Shared Types & Constants | — | SCDS §2 | 1.0 | `927b7fad0248cc5a8582dc57909dc316f8520c23fdac32f5d561cf2ad5918a6d` |
| `hal.h` | Hardware Abstraction Layer | COMP-008 | SCDS §10 | 1.0 | `e38a28f32b7768450c07543aef0eae762f9061beaf0c318d0184845e1c26ac9b` |
| `skn.h` | Safety Kernel | COMP-001 | SCDS §3 | 1.0 | `07c5b84d3322cf4f6d72575f5918963e1dd27bd4459538cedbbe3fd989527344` |
| `spm.h` | Speed Monitor | COMP-002 | SCDS §4 | 1.0 | `51249bbdc56795f1494d983980e1ebc3f092697c13d2c542da5123ff64aa4f45` |
| `obd.h` | Obstacle Detector | COMP-003 | SCDS §5 | 1.0 | `e7559c68dc644518adcd591b1bccd3fb028e8b02a6a2f007dda3e827c67297ee` |
| `dsm.h` | Door State Machine | COMP-004 | SCDS §6 | 1.0 | `1375de6f9bbb9913ede8b1c398d9b61b476175cc86184386d7cc0d055eb31140` |
| `fmg.h` | Fault Manager | COMP-005 | SCDS §7 | 1.0 | `1ac74d151920ca437e17ac3636da89562764c9c29e6da8435091bbcd9f5f06b2` |
| `tci.h` | Train Control Interface | COMP-006 | SCDS §8 | 1.0 | `11ef2e0713e13a0d60e529fbc23016fd8b41c1b924f173457d16b59f07f942ce` |
| `dgn.h` | Diagnostics | COMP-007 | SCDS §9 | 1.0 | `7c17b9d7dbf3e493d60f9d3f4565a65888b7082b3b364ca0789cf7d3fd7d99ce` |

### 2.2 Implementation Files (21 files)

| File | Component | Module-ID | SCDS Ref | Version | SHA-256 Hash |
|------|-----------|-----------|----------|---------|--------------|
| `hal_services.c` | Hardware Abstraction Layer | COMP-008 | SCDS §10 | 1.0 | `138f7e7f5dba86ed5f37f8951456f8f226b99135870560ced950c7860adeecb7` |
| `skn_comparator.c` | Safety Kernel | MOD-SKN-001 | SCDS §3.1 | 1.0 | `ce69973206503ae6c87e472a178ccd2d36b3f41c82c237e5d48f86a2e96302ea` |
| `skn_safe_state.c` | Safety Kernel | MOD-SKN-002 | SCDS §3.2 | 1.0 | `08f19632441e5da81f34ac645435276a588df1e3f3e2a7aaabd463163f699959` |
| `skn_scheduler.c` | Safety Kernel | MOD-SKN-003 | SCDS §3.3 | 1.0 | `c946565729337e463b83bcaf2cbce8e8f61b7b0c8eeab73d7a5e7f8a3b2bb0f4` |
| `skn_init.c` | Safety Kernel | MOD-SKN-004 | SCDS §3.4 | 1.0 | `ac9a65de29002c98285a52f472559ec87efb2fc758d84497c36b78f61ff768f4` |
| `spm_can.c` | Speed Monitor | COMP-002 | SCDS §4 | 1.0 | `726099e633757ca5ea9d3767ab86196de61653d74b0b68a035c4530f6d603c0d` |
| `obd_detect.c` | Obstacle Detector | COMP-003 | SCDS §5 | 1.0 | `7a659bb81021e822d105d8b59e2cf0278aa6963e3acf999b72b3968def819807` |
| `dsm_fsm.c` | Door State Machine | MOD-DSM-001 | SCDS §6.1–§6.2 | 1.0 | `f54e548d1afbecaa9a54a6d177807c8b63088b7d4d4e60847ffd716729134598` |
| `dsm_voter.c` | Door State Machine | MOD-DSM-002 | SCDS §6.3 | 1.0 | `9d3991d1bc2c0fde234f386de34286723d5c06f9f1873b4c8a94518ce44e9532` |
| `dsm_mode.c` | Door State Machine | MOD-DSM-003 | SCDS §6.4 | 1.0 | `ebf3ad97c230a132bb22267d55aa59886ac49bdc246f7aacc4e1e616be1d23d5` |
| `dsm_emergency.c` | Door State Machine | MOD-DSM-004 | SCDS §6.5 | 1.0 | `4d7ba31eeeaddf8fef05227c89f59ffa0757f26cb3b7d4f71e467160a0fb1d9b` |
| `dsm_init.c` | Door State Machine | MOD-DSM-005 | SCDS §6.6 | 1.0 | `a083d03860a6ee9c818938fe139658b77efe75576da2ce3175ea27afc9e3d5ca` |
| `fmg_aggregator.c` | Fault Manager | MOD-FMG-001 | SCDS §7.1 | 1.0 | `1700062b5ffb0a592804a97847341ab88f0c1fda4f13fe53d87dc88437b34965` |
| `fmg_init.c` | Fault Manager | MOD-FMG-002 | SCDS §7.2 | 1.0 | `b625be5fcd165d2d78a96ecbf3a7ebfeaf98ad54d75546c47623f3790b359fec` |
| `tci_rx.c` | Train Control Interface | MOD-TCI-001 | SCDS §8.1 | 1.0 | `88b7c597ecf223d5b97783d55139913b797700321c8e84691e1b7527dd035373` |
| `tci_tx.c` | Train Control Interface | MOD-TCI-002 | SCDS §8.2 | 1.0 | `197020dce4267cebd15730e6e1fdff99cbdb968c9e26ac9c0628353c6b40884f` |
| `tci_seq.c` | Train Control Interface | MOD-TCI-003 | SCDS §8.3 | 1.0 | `64473574fdd1bd14d15d4d4d92e8f58eda090216070da64491565f8736df9d8c` |
| `tci_init.c` | Train Control Interface | MOD-TCI-004 | SCDS §8.4 | 1.0 | `5e3536b0c203f06301a6c3656f97bc7df526c8ed8dee182ce1055ae10433fd76` |
| `dgn_log.c` | Diagnostics | MOD-DGN-001 | SCDS §9.1 | 1.0 | `2d71f858b8acaa266e323dc08ebb78f2076d55926281aa5e8d347a76c0a31586` |
| `dgn_flash.c` | Diagnostics | MOD-DGN-002 | SCDS §9.2 | 1.0 | `03c567a19067c76132576e5ecb9b8611138cb4cc93140adf190fdadf0ef5f300` |
| `dgn_port.c` | Diagnostics | MOD-DGN-003 | SCDS §9.3 | 1.0 | `062547e6b35dbfb6fc2d2d46158daa30fe3eece8bab76ae55bae1a361b360769` |

### 2.3 Supporting Documentation (1 file)

| File | Purpose | Version | SHA-256 Hash |
|------|---------|---------|--------------|
| `TRACEABILITY.md` | Design-to-code traceability matrix | 1.0 | `9137dace6b7901243e62d38faef549f88dd4a17ff64ed68936f863678f29b835` |

### 2.4 Package Manifest Summary

| Category | Count |
|----------|-------|
| Header files (`.h`) | 9 |
| Implementation files (`.c`) | 21 |
| Supporting documentation | 1 |
| **Total files** | **31** |

---

## 3. Build Instructions

### 3.1 Compiler Requirements

| Property | Value |
|----------|-------|
| **Compiler** | GCC 11.2.0 or later (arm-none-eabi-gcc for target) |
| **C Standard** | C99 (`-std=c99`) |
| **Target Architecture** | ARM Cortex-M4 (`-mcpu=cortex-m4 -mthumb`) |
| **FPU** | Hard float (`-mfpu=fpv4-sp-d16 -mfloat-abi=hard`) |
| **Optimisation** | `-O2` (release) / `-O0 -g3` (debug/test) |

### 3.2 Mandatory Compiler Flags

```
-std=c99
-Wall
-Wextra
-Werror
-Wpedantic
-Wconversion
-Wshadow
-Wundef
-Wmissing-prototypes
-DSIL_LEVEL=3
-DMAX_DOORS=8
-mcpu=cortex-m4
-mthumb
-mfpu=fpv4-sp-d16
-mfloat-abi=hard
-O2
-ffunction-sections
-fdata-sections
```

### 3.3 Include Paths

```
-I examples/TDC/src/
-I vendor/cmsis/Include/
```

### 3.4 Build Commands

```bash
# Clean previous build artefacts
make clean

# Build all modules (release, ARM Cortex-M4)
make all TARGET=arm-cortex-m4

# Build for host (unit test execution with Unity)
make test TARGET=host

# Static analysis (run before submission to VER)
make analyse
```

### 3.5 Example Makefile Fragment

```makefile
CC      = arm-none-eabi-gcc
CFLAGS  = -std=c99 -Wall -Wextra -Werror -Wpedantic -Wconversion \
          -Wshadow -Wundef -Wmissing-prototypes \
          -DSIL_LEVEL=3 -DMAX_DOORS=8 \
          -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard \
          -O2 -ffunction-sections -fdata-sections
INCLUDE = -I examples/TDC/src/ -I vendor/cmsis/Include/
SRCS    = $(wildcard examples/TDC/src/*.c)
OBJS    = $(SRCS:.c=.o)

all: $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS)

analyse:
	cppcheck --enable=warning --error-exitcode=1 --std=c99 \
	         --suppress=missingIncludeSystem --suppress=missingInclude \
	         examples/TDC/src/*.c
```

### 3.6 Dependencies

| Dependency | Version | Purpose |
|------------|---------|---------|
| GCC (arm-none-eabi) | 11.2.0+ | Cross-compiler for ARM Cortex-M4 target |
| CMSIS | 5.8.0 | ARM Cortex-M4 core support headers |
| Unity | 2.5.2 | Unit test framework (test builds only) |
| cppcheck | 2.x | Static analysis (run by IMP/VER) |
| lizard | 1.21.3 | Cyclomatic complexity measurement |

### 3.7 Static Analysis Results (Informational — Verified by VER in Item 19)

| Tool | Result | Details |
|------|--------|---------|
| cppcheck | PASS (0 errors, 0 warnings) | Run on all 21 `.c` files |
| lizard | PASS (0 CCN violations) | Max CCN observed: 10 (SIL-3 limit: 10) |

---

## 4. Change Summary

| Version | Date | Author | Description |
|---------|------|--------|-------------|
| 1.0 | 2026-04-04 | IMP | Initial release — first delivery of TDC source code package (Phase 5). Implements all 97 software units across 8 components (SKN=9, SPM=5, OBD=5, DSM=18, FMG=6, TCI=8, DGN=8, HAL=20) per SCDS DOC-COMPDES-2026-001. |

**Change Detail**: Initial release. No prior version exists.  
No deviations from SCDS DOC-COMPDES-2026-001 recorded at this revision.  
All MISRA C:2012 mandatory rules compliant. Zero dynamic memory allocation.  
Static analysis clean (cppcheck, lizard). Full Design→Code traceability established in `TRACEABILITY.md`.

---

## 5. Known Limitations and Deviations

| ID | Location | Description | Disposition |
|----|----------|-------------|-------------|
| DEV-001 | `skn_init.c`, `skn_safe_state.c` | Pointer arithmetic on linker-defined symbols (`__rom_start__`, `__rom_end__`) uses `uintptr_t` cast arithmetic instead of direct pointer subtraction to maintain static-analysis cleanliness; semantically equivalent on ARM Cortex-M4 target. | Accepted — MISRA-compliant workaround documented in source |
| DEV-002 | `dsm_fsm.c`, `obd_detect.c` | Two private helper functions (`dsm_dispatch_state`, `obd_evaluate_single_door`) added beyond SCDS unit list to satisfy SIL-3 CCN ≤ 10 limit; documented in `TRACEABILITY.md` §5. | Accepted — required by EN 50128 Table A.4 complexity constraint |

---

## 6. References

| Document | ID | Description |
|----------|----|-------------|
| EN 50128:2011 | — | Railway software standard — §7.5 Component Implementation |
| SCDS | DOC-COMPDES-2026-001 | Software Component Design Specification (Item 15) |
| SRS | DOC-SRS-2026-001 | Software Requirements Specification (Item 6) |
| TRACEABILITY | (this package) | Design-to-code traceability matrix — `TRACEABILITY.md` |
| QUA Review Iteration 1 | QUA-REVIEW-ITEM18-2026-001 | QUA format review finding report |

---

*End of Software Source Code Package — Item 18 — DOC-SOURCECODE-2026-001 v1.0*
