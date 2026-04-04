# TDC — Train Door Control System

**EN 50128:2011 SIL 3 Safety-Critical Railway Software**

| Attribute | Value |
|-----------|-------|
| **SIL Level** | 3 (High — single fatality risk category) |
| **COD Mode** | Strict Gatekeeper |
| **Standard** | EN 50128:2011 |
| **Language** | C (MISRA C:2012 compliant) |
| **Current Phase** | Phase 7 (Validation) — authorized 2026-04-04 |
| **Completion** | 95% (Phases 0–6 complete; Phase 7 authorized) |

---

## System Description

The Train Door Control System (TDCS) is a SIL 3 safety-critical software component responsible for
managing passenger door operations on railway vehicles. It enforces safety interlocks between
door state, train speed, and platform alignment.

**8 Software Components**:

| Component | Module | Description |
|-----------|--------|-------------|
| SKN | Safe State Kernel | Safety state machine; triggers safe state on any SIL 3 fault |
| SPM | Speed Monitor | Train speed monitoring and interlock enforcement |
| OBD | Obstacle Detection | Door obstacle sensing and door reversal logic |
| DSM | Door State Manager | Door open/close state machine |
| FMG | Fault Manager | Fault detection, classification, and logging |
| TCI | Train Control Interface | Interface to train control network (MVB/WTB) |
| DGN | Diagnostics | Built-in self-test (BIST) and health monitoring |
| HAL | Hardware Abstraction Layer | STM32H743 peripheral drivers (GPIO, SPI, IWDG, DWT) |

**Safety Architecture**: 2oo2 dual-channel design; CRC-16-CCITT (0x1021) unified across channels;
SPI transient filter (3-cycle); 5 SIL 3 safety functions addressed.

---

## Phase Status

| Phase | Name | Status | Gate | Notes |
|-------|------|--------|------|-------|
| 0 | Initialization | ✅ Complete | N/A | 4 system documents generated |
| 1 | Planning | ✅ PASSED | PASS | SQAP, SCMP, SVP v1.1, SVaP; CCR-SVP-001 applied |
| 2 | Requirements | ✅ PASSED | PASS | 53 SRS requirements (21 safety-critical); 133 OTSTSPEC test cases |
| 3 | Architecture & Design | ✅ PASSED | PASS | SAS/SDS/SIS; FMEA/FTA; 379 traceability links added |
| 4 | Component Design | ✅ PASSED | PASS | 30 modules; Component Test Spec; zero defects |
| 5 | Implementation & Testing | ✅ PASSED | PASS | 203 tests; 87.9% stmt / 83.9% branch; 3 NCRs closed |
| 6 | Integration | ✅ PASSED | PASS | 50/50 tests PASS; 90.3% stmt / 98.3% branch; QEMU integrated |
| 7 | Validation | 🔵 Authorized | — | VAL-C-001: 4 HIL tests required before final sign-off |
| 8 | Assessment | Not started | — | Independent assessor (mandatory SIL 3) |
| 9 | Deployment | Not started | — | — |

---

## Build and Test

### Prerequisites

```bash
# From repository root
./install_tools.sh
./install_python.sh
```

### Build and Run Tests

```bash
# From this directory
make              # Build source
make test         # Build and run 203 component tests + 50 integration tests
make coverage     # Generate coverage report (gcov/lcov)
make static       # Run static analysis (cppcheck)
make complexity   # Check cyclomatic complexity (lizard)
make clean        # Remove build artifacts
```

### Test Coverage (Phase 5 — Component Level)

| Metric | Result | EN 50128 SIL 3 Requirement |
|--------|--------|---------------------------|
| Statement | 87.9% | M (Mandatory) |
| Branch | 83.9% | M (Mandatory) |
| Compound Condition | Measured + documented | HR (Highly Recommended) |

Residual gaps (12.1% stmt / 16.1% branch) are justified with Table A.19 static analysis evidence
in `docs/phase-5-implementation-testing/Software-Component-Test-Report.md`.

### Integration Coverage (Phase 6)

| Metric | Result |
|--------|--------|
| Statement | 90.3% |
| Branch | 98.3% |
| Compound Condition | 100% |

---

## Key Documents

### System-Level Inputs (EN 50126/50129)
- `docs/system/System-Requirements-Specification.md`
- `docs/system/System-Architecture-Description.md`
- `docs/system/System-Safety-Plan.md`
- `docs/system/System-Safety-Requirements-Specification.md`

### Planning (Phase 1)
- `docs/phase-1-planning/Software-Quality-Assurance-Plan.md` (SQAP)
- `docs/phase-1-planning/Software-Configuration-Management-Plan.md` (SCMP)
- `docs/phase-1-planning/Software-Verification-Plan.md` (SVP v1.1 — CCR-SVP-001 applied)
- `docs/phase-1-planning/Software-Validation-Plan.md` (SVaP)

### Requirements (Phase 2)
- `docs/phase-2-requirements/Software-Requirements-Specification.md` (SRS — 53 requirements)
- `docs/phase-2-requirements/Overall-Software-Test-Specification.md` (133 test cases)

### Architecture & Design (Phase 3)
- `docs/phase-3-architecture-design/Software-Architecture-Specification.md` (SAS)
- `docs/phase-3-architecture-design/Software-Design-Specification.md` (SDS)
- `docs/phase-3-architecture-design/Software-Interface-Specifications.md` (SIS)
- `docs/phase-3-architecture-design/Software-Integration-Test-Specification.md`
- `docs/phase-3-architecture-design/Software-Hardware-Integration-Test-Specification.md`

### Component Design (Phase 4)
- `docs/phase-4-component-design/Software-Component-Design-Specification.md`
- `docs/phase-4-component-design/Software-Component-Test-Specification.md`

### Implementation & Testing (Phase 5)
- `docs/phase-5-implementation-testing/Software-Component-Test-Report.md` (Item 20 v1.1 — 203 tests)
- `docs/phase-5-implementation-testing/reports/Software-Source-Code-Verification-Report.md` (Item 19 v1.1)
- `docs/phase-5-implementation-testing/reports/VMGR-VV-Outcome-Report-Phase-5.md` (VMGR APPROVED)

### Integration (Phase 6)
- `docs/phase-6-integration/Software-Integration-Test-Report.md` (Item 21 — 28/28 PASS)
- `docs/phase-6-integration/Hardware-Software-Integration-Test-Report.md` (Item 22 — 22/26 executed + QEMU)
- `docs/phase-6-integration/QEMU-Integration-Plan.md` (DOC-QEMUINTPLAN-2026-001)
- `docs/phase-6-integration/QEMU-Tool-Validation-Report.md` (DOC-TVR-QEMU-2026-001)
- `docs/phase-6-integration/reports/VMGR-VV-Outcome-Phase-6.md` (VMGR APPROVED WITH CONDITIONS)

### Safety
- `docs/safety/Hazard-Log.md`
- `docs/safety/FMEA-Report.md`
- `docs/safety/FTA-Report.md`

### Traceability
- `docs/traceability/Requirements-Traceability-Matrix.md` (100% SRS→SAS→SDS→tests)

### Change Control
- `docs/change-control/CCR-SVP-001.md` (SVP Table A.21 correction — APPROVED)

### Non-Conformance
- `docs/non-conformance/NCR-P5-001.md` — Coverage waiver invalid — CLOSED
- `docs/non-conformance/NCR-P5-002.md` — VER independent verification — CLOSED
- `docs/non-conformance/NCR-P5-003.md` — Compound condition coverage — CLOSED

---

## Open Tracked Conditions (Phase 7 Entry)

| ID | Severity | Description | Owner | Blocking |
|----|----------|-------------|-------|---------|
| VAL-C-001 | MANDATORY | Complete 4 HIL tests on physical STM32H743 before Phase 7 final sign-off | PM/INT/TST | Yes (Phase 7 gate) |
| VER-C-001 | MINOR | Generate CSV traceability matrices for T6/T7/T11/T12 | CM | No |
| VAL-C-002 | MINOR | Close VER-C-001 before Phase 7 | CM | No |

**HIL-pending tests** (VAL-C-001):
1. TC-HWSW-005 — IWDG hardware timeout measurement (oscilloscope, 50 ms ±5 ms)
2. TC-HWSW-PERF-001 — WCET ≤ 16 ms (DWT cycle counter on Cortex-M7 @ 400 MHz)
3. TC-HWSW-PERF-004 — ISR latency ≤ 1 ms (oscilloscope on GPIO interrupt)
4. TC-HWSW-FAULT-002 — Memory CRC corruption via JTAG (OpenOCD/GDB on STM32H743 SRAM)

---

## Lifecycle State

Full lifecycle state, deliverable status, and tracked conditions:
- `LIFECYCLE_STATE.md` — authoritative lifecycle tracking document

---

## Platform Resources

- **Main README**: `../../README.md` — Platform overview
- **User Guide**: `../../docs/USER-GUIDE.md`
- **Lifecycle**: `../../LIFECYCLE.md`
- **Agents**: `../../AGENTS.md`
- **Standard**: `../../std/EN50128-2011.md`
