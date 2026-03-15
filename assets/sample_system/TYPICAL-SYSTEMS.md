# Typical Railway Systems Catalogue

This catalogue provides detailed outlines for typical railway safety systems. Each entry contains sufficient content to generate all four mandatory system-level input documents required by EN 50128 §7.2.2:

1. **System Requirements Specification** (SRS)
2. **System Architecture Description** (SAD)
3. **System Safety Plan** (SSP)
4. **System Safety Requirements Specification** (SSRS)

Use `@cod generate-system` to select a system and generate all four documents for the active project workspace.

---

## How to Use This Catalogue

1. Run `@cod plan --sil <level> --project <name>` to initialize a project
2. Run `@cod generate-system` to select a system from this catalogue
3. COD reads the selected system entry and generates the four documents in `docs/system/`
4. The generated documents become the authoritative system-level inputs for the project

Each catalogue entry is structured with the following sections:
- **System Overview** — name, SIL, domain, applicable standards
- **Operational Environment** — physical and operational context
- **System Boundary** — what is inside and outside the system
- **Hazard List** — identified hazards with risk classification and SIL rationale
- **Functional Requirements** — key system-level functional requirements
- **Safety Functions** — derived safety functions with SIL allocation
- **System Architecture** — hardware and software components, interfaces
- **Communication Interfaces** — protocols, data rates, timing
- **Non-Functional Requirements** — performance, reliability, maintainability
- **Design Constraints** — technology, standards, certification constraints
- **Glossary** — domain-specific terms

---

## System 1: Train Door Control System (SIL 3)

### System Overview

| Attribute | Value |
|-----------|-------|
| System Name | Train Door Control System (TDCS) |
| Abbreviation | TDCS |
| SIL Level | SIL 3 |
| Domain | Rolling Stock — Passenger Door Control |
| Applicable Standards | EN 50128:2011, EN 50129:2018, EN 50126:2017, EN 13272 |
| Typical Deployment | Electric multiple units (EMU), metro, suburban rail |
| Safety Authority Context | Vehicle safety case per EN 50129 |

### Operational Environment

- Operates on electrified mainline and metro railway networks
- Ambient temperature: -25°C to +55°C (operational), -40°C to +70°C (storage)
- Humidity: 5% to 95% (non-condensing)
- Vibration: EN 61373 Category 1 Class B
- EMC: EN 50121-3-2 (rolling stock emissions and immunity)
- Power supply: 24 VDC nominal (18–32 VDC range) from train battery
- Train speed range: 0–200 km/h (system active only at ≤ 5 km/h for door operations)

### System Boundary

**Inside the system boundary:**
- Door Control Unit (DCU) — central processing module
- Door Drive Units (DDU) per door leaf — electromechanical actuators with position sensors
- Obstacle detection sensors (infrared, 2 per door opening)
- Door open/close command inputs from Train Control and Management System (TCMS)
- Speed interlock input from TCMS (train speed signal)
- Door status outputs to TCMS (door locked, door open, door fault)
- Local door open buttons (platform side and cab side)
- Emergency door release mechanism (passive, manual)

**Outside the system boundary (interfaces only):**
- Train Control and Management System (TCMS) — provides speed, commands, receives status
- Driver Desk Display Unit — receives door status summary
- Platform Screen Doors (PSD) — receives door open/close commands (where fitted)
- Vehicle diagnostic system — receives fault logs via TCMS
- Wayside Automatic Train Protection (ATP) — no direct interface; speed interlock sourced from TCMS

### Hazard List

| ID | Hazard Description | Severity | Frequency | Risk Level | SIL |
|----|-------------------|----------|-----------|------------|-----|
| HAZ-001 | Train departs with door open or not fully locked | Catastrophic | Occasional | Intolerable | SIL 3 |
| HAZ-002 | Door closes on passenger causing entrapment injury | Critical | Frequent | Intolerable | SIL 3 |
| HAZ-003 | Door opens while train is moving above 5 km/h | Catastrophic | Remote | Intolerable | SIL 3 |
| HAZ-004 | Obstacle detected but door continues to close | Critical | Occasional | Intolerable | SIL 3 |
| HAZ-005 | False door-locked signal allows train departure with door ajar | Catastrophic | Occasional | Intolerable | SIL 3 |
| HAZ-006 | Door fails to open at station (passenger trapped) | Marginal | Frequent | Tolerable (ALARP) | SIL 2 |
| HAZ-007 | Door fails to close at end of dwell time (service disruption) | Marginal | Occasional | Tolerable (ALARP) | SIL 1 |
| HAZ-008 | Emergency door release triggers during normal operation | Critical | Remote | Tolerable (ALARP) | SIL 2 |
| HAZ-009 | DCU software fault leads to loss of all door control | Critical | Remote | Tolerable (ALARP) | SIL 2 |

**SIL Determination Basis (EN 50126 Risk Matrix):**
- Severity categories: Catastrophic (fatalities possible), Critical (serious injuries), Marginal (minor injuries/disruption)
- Frequency categories: Frequent (>10^-3/hr), Occasional (10^-3 to 10^-5/hr), Remote (10^-5 to 10^-7/hr), Incredible (<10^-7/hr)
- HAZ-001 through HAZ-005 drive the SIL 3 system classification

### Functional Requirements

| ID | Requirement | Category |
|----|-------------|----------|
| SYS-FR-001 | The system SHALL open all doors on the commanded side when commanded by TCMS and train speed ≤ 5 km/h | Door Operation |
| SYS-FR-002 | The system SHALL close and lock all doors when commanded by TCMS | Door Operation |
| SYS-FR-003 | The system SHALL prevent door opening when train speed > 5 km/h | Speed Interlock |
| SYS-FR-004 | The system SHALL prevent train departure authority if any door is not fully locked | Departure Interlock |
| SYS-FR-005 | The system SHALL detect obstacles in the door opening and reverse door motion within 150 ms | Obstacle Detection |
| SYS-FR-006 | The system SHALL transmit door-locked status to TCMS within 100 ms of lock confirmation | Status Reporting |
| SYS-FR-007 | The system SHALL transmit individual door fault status to TCMS for each defective door | Fault Reporting |
| SYS-FR-008 | The system SHALL allow manual emergency door release from inside the saloon | Emergency Operation |
| SYS-FR-009 | The system SHALL support selective door disablement (isolate one defective door) | Maintenance |
| SYS-FR-010 | The system SHALL log all door events with timestamps for diagnostic purposes | Diagnostics |
| SYS-FR-011 | The system SHALL command the safe state (doors locked, no active drive) on any internal fault | Fault Handling |
| SYS-FR-012 | The system SHALL complete door close-and-lock sequence within 8 seconds under nominal conditions | Performance |

### Safety Functions

| ID | Safety Function | SIL | Derived From |
|----|----------------|-----|--------------|
| SF-001 | Speed Interlock: Inhibit door open command when train speed > 5 km/h | SIL 3 | HAZ-003 |
| SF-002 | Departure Interlock: Withhold door-locked signal until all doors confirmed locked | SIL 3 | HAZ-001, HAZ-005 |
| SF-003 | Obstacle Detection and Reversal: Detect and respond to obstacle within 150 ms | SIL 3 | HAZ-002, HAZ-004 |
| SF-004 | Safe State: Command all doors to locked state on system fault | SIL 3 | HAZ-005, HAZ-009 |
| SF-005 | Door Position Verification: Confirm door lock status via independent sensor channel | SIL 3 | HAZ-001, HAZ-005 |
| SF-006 | Emergency Release Monitoring: Detect and report emergency release activation | SIL 2 | HAZ-008 |
| SF-007 | Fault Isolation: Isolate defective door and maintain operation of remaining doors | SIL 2 | HAZ-009 |

### System Architecture

**Processing Architecture:**
- Dual-channel (2oo2) DCU with independent CPUs running identical software
- Each channel independently monitors all sensor inputs and computes outputs
- Outputs compared by cross-channel monitor before actuation
- Disagreement between channels → safe state transition

**Hardware Components:**
- DCU: STM32H743 (or equivalent) dual microcontroller module, 400 MHz, 1 MB SRAM
- DDU: Per-door electromechanical drive with DC motor, encoder, end-stop switches
- Obstacle sensors: Infrared beam pairs, 2 per door opening (redundant)
- Power: 24 VDC primary with 5 V/3.3 V DC-DC converters; watchdog circuit
- Non-volatile storage: SPI flash 16 MB for event log

**Software Components:**
- Door State Machine (DSM): main control logic, state-based door sequencing
- Speed Monitor (SPM): reads speed from TCMS, enforces interlock
- Obstacle Detector (OBD): processes obstacle sensor inputs, triggers reversal
- TCMS Interface (TCI): CAN bus driver, message encoding/decoding
- Fault Manager (FMG): fault detection, safe state management, fault log
- Diagnostics (DGN): event logging, diagnostic data reporting
- Hardware Abstraction Layer (HAL): GPIO, ADC, CAN, SPI drivers

### Communication Interfaces

| Interface | Protocol | Data Rate | Purpose |
|-----------|----------|-----------|---------|
| TCMS ↔ DCU | CAN 2.0B (ISO 11898) | 250 kbit/s | Speed signal, door commands, door status |
| DCU ↔ DDU | Proprietary RS-485 | 115.2 kbit/s | Drive commands, position feedback per door |
| DCU ↔ Obstacle Sensors | Digital GPIO (24 V) | N/A (interrupt-driven) | Obstacle detect/clear |
| DCU channel A ↔ channel B | SPI cross-link | 10 Mbit/s | Cross-channel comparison data |
| DCU ↔ Diagnostics port | USB/RS-232 | 115.2 kbit/s | Maintenance laptop access |

**Key Timing Requirements:**
- Speed signal update rate from TCMS: 100 ms period (10 Hz)
- Door command → first motor movement: ≤ 200 ms
- Obstacle detected → motor reversal: ≤ 150 ms
- Door position confirmed → TCMS status update: ≤ 100 ms
- Watchdog timeout (no software heartbeat): 50 ms → safe state

### Non-Functional Requirements

| Category | Requirement |
|----------|-------------|
| Reliability | MTBF ≥ 200,000 hours for the DCU |
| Availability | System availability ≥ 99.9% per 24-hour period |
| Maintainability | Mean Time To Repair (MTTR) ≤ 4 hours with standard railway maintenance tools |
| Safety Integrity | PFH ≤ 10^-7 per hour (SIL 3 per IEC 61508 Table 2) |
| Response Time | End-to-end command-to-locked response ≤ 8 seconds |
| Service Life | ≥ 30 years with scheduled maintenance |
| Certifiability | EN 50129 Safety Case required; EN 50128 SIL 3 for software |

### Design Constraints

- Software implemented in C, MISRA C:2012 mandatory
- No dynamic memory allocation (static allocation only)
- Cyclomatic complexity ≤ 10 per function
- 100% statement, branch, and condition (MC/DC) coverage required
- Software independence: Verifier and Validator must be independent from development team
- Hardware qualification: EN 50155 for railway electronic equipment
- No recursion permitted in safety-critical code paths
- All external inputs validated before use

### Glossary

| Term | Definition |
|------|-----------|
| DCU | Door Control Unit — central processing module for door control |
| DDU | Door Drive Unit — per-door electromechanical actuator module |
| TCMS | Train Control and Management System — train-level supervisory system |
| 2oo2 | Two-out-of-two voting — both channels must agree for output to actuate |
| PFH | Probability of Failure per Hour — SIL integrity measure |
| HAZ | Hazard — identified potential source of harm |
| SF | Safety Function — function that maintains or achieves a safe state |
| MTBF | Mean Time Between Failures |
| MTTR | Mean Time To Repair |
| SIL | Safety Integrity Level (EN 61508 / EN 50128) |

---

## System 2: Railway Level Crossing Protection System (SIL 4)

### System Overview

| Attribute | Value |
|-----------|-------|
| System Name | Railway Level Crossing Protection System (LCPS) |
| Abbreviation | LCPS |
| SIL Level | SIL 4 |
| Domain | Infrastructure — Level Crossing Safety |
| Applicable Standards | EN 50128:2011, EN 50129:2018, EN 50126:2017, EN 50159 (communication), prEN 50675 (level crossings) |
| Typical Deployment | Rural and suburban road/rail level crossings (half-barrier, full-barrier, or light-only types) |
| Safety Authority Context | Infrastructure safety case; approval from national railway safety authority required |

### Operational Environment

- Installed at road/rail grade crossings on mainline, branch, and heritage railways
- Ambient temperature: -40°C to +70°C (rail trackside environment)
- Humidity: 0% to 100% (including condensation and ice formation)
- Ingress protection: IP67 for all outdoor equipment
- Power supply: 230 VAC mains primary, 48 VDC battery backup (≥ 8 hours)
- EMC: EN 50121-4 (infrastructure trackside installations)
- Railway line speeds: up to 200 km/h
- Road traffic: mixed vehicles including HGVs and agricultural vehicles

### System Boundary

**Inside the system boundary:**
- Level Crossing Controller (LCC) — central safety logic processor
- Train detection subsystem (track circuits or axle counters, 2 per approach direction)
- Boom barrier actuators (1 or 2 barriers per road lane; half-barrier or full-barrier)
- Warning lights (flashing red LEDs, road-side facing, ≥ 2 per approach lane)
- Acoustic warning bells/horns
- Obstacle detection radar or inductive loops (road vehicle presence in crossing zone)
- Stagger switches (mechanical confirmation of boom barrier down position)
- Crossing clear monitor output to train signalling system (or train detection)
- Communication link to interlocking or centralized traffic control (CTC)
- Local operator panel (for maintenance use only, key-switched)

**Outside the system boundary:**
- Train signalling system (interlocking) — provides signal aspects; receives crossing status
- Road Traffic Controller — no direct interface (crossing uses pre-emptive activation)
- Emergency services — receive alarm via external monitoring system (interface only)
- National Rail Operations Centre — receives status via SCADA interface (output only)

### Hazard List

| ID | Hazard Description | Severity | Frequency | Risk Level | SIL |
|----|-------------------|----------|-----------|------------|-----|
| HAZ-001 | Road vehicle on crossing when train arrives — barrier fails to lower | Catastrophic | Occasional | Intolerable | SIL 4 |
| HAZ-002 | Crossing protection activates but train detection fails (premature clearance) | Catastrophic | Remote | Intolerable | SIL 4 |
| HAZ-003 | Obstacle in crossing zone not detected; train signal cleared | Catastrophic | Occasional | Intolerable | SIL 4 |
| HAZ-004 | Barriers lower on road vehicle (entrapment), closing lane to emergency exit | Critical | Occasional | Intolerable | SIL 4 |
| HAZ-005 | Warning lights fail to activate (no visual warning to road users) | Catastrophic | Remote | Intolerable | SIL 4 |
| HAZ-006 | Spurious activation (false alarm) causes unnecessary traffic disruption | Marginal | Frequent | Tolerable (ALARP) | SIL 1 |
| HAZ-007 | Barrier raises before train has fully cleared crossing | Catastrophic | Remote | Intolerable | SIL 4 |
| HAZ-008 | Communication failure to interlocking causes missed train approach | Catastrophic | Remote | Intolerable | SIL 4 |
| HAZ-009 | Power failure causes barriers to fail in raised (open) position | Catastrophic | Occasional | Intolerable | SIL 4 |
| HAZ-010 | Maintenance override inadvertently left active during normal operation | Catastrophic | Remote | Intolerable | SIL 3 |

**SIL Determination Basis:**
- HAZ-001, HAZ-002, HAZ-003, HAZ-005, HAZ-007, HAZ-008, HAZ-009 all lead to potential train/vehicle collisions
- Train/vehicle collision at mainline speed is catastrophic and irreversible
- Frequency of train approach combined with road vehicle presence justifies SIL 4
- HAZ-009 specifically addressed by fail-safe barrier design (barriers fall under gravity on power loss)

### Functional Requirements

| ID | Requirement | Category |
|----|-------------|----------|
| SYS-FR-001 | The system SHALL detect a train approaching the crossing at least 30 seconds before train arrival at design line speed | Train Detection |
| SYS-FR-002 | The system SHALL activate acoustic and visual warnings for road users at least 10 seconds before barrier descent begins | Warning Activation |
| SYS-FR-003 | The system SHALL lower all road-side barriers within 8 seconds of warning activation command | Barrier Control |
| SYS-FR-004 | The system SHALL confirm barriers are in the fully-lowered position before clearing the crossing to train signalling | Barrier Confirmation |
| SYS-FR-005 | The system SHALL detect the presence of road vehicles in the crossing zone and withhold clearance to train signalling | Obstacle Detection |
| SYS-FR-006 | The system SHALL detect train departure from the crossing approach and withdrawal from the crossing zone before raising barriers | Train Clearance |
| SYS-FR-007 | The system SHALL raise barriers only after both train departure is confirmed AND crossing zone is clear | Barrier Release |
| SYS-FR-008 | The system SHALL transmit crossing status (protected, clear, fault) to interlocking system within 500 ms of state change | Interlocking Interface |
| SYS-FR-009 | The system SHALL enter and maintain safe state on detection of any internal fault condition | Fault Handling |
| SYS-FR-010 | The system SHALL maintain warning lights and barriers in safe state (barriers down, lights active) on power failure | Fail-Safe |
| SYS-FR-011 | The system SHALL log all operational events, alarms, and faults with timestamps | Diagnostics |
| SYS-FR-012 | The system SHALL provide secure maintenance access via key-switched local panel only | Maintenance |

### Safety Functions

| ID | Safety Function | SIL | Derived From |
|----|----------------|-----|--------------|
| SF-001 | Train Approach Detection: Detect train approach on both tracks with 2-out-of-2 confirmation | SIL 4 | HAZ-001, HAZ-002 |
| SF-002 | Protection Activation: Activate warnings and lower barriers before train arrival | SIL 4 | HAZ-001, HAZ-005 |
| SF-003 | Crossing Clear Confirmation: Confirm all barriers down and crossing zone clear before signalling clearance | SIL 4 | HAZ-003, HAZ-004, HAZ-007 |
| SF-004 | Train Departure Detection: Confirm complete train passage before barrier raise authorization | SIL 4 | HAZ-007 |
| SF-005 | Fail-Safe Default: All outputs default to safe state (barriers down, no clearance) on fault or power loss | SIL 4 | HAZ-009 |
| SF-006 | Obstacle Detection: Detect and report road vehicles in crossing zone to prevent premature clearance | SIL 4 | HAZ-003 |
| SF-007 | Maintenance Override Protection: Detect, log, and limit duration of maintenance override; auto-cancel after timeout | SIL 3 | HAZ-010 |

### System Architecture

**Processing Architecture:**
- Triple Modular Redundant (TMR) controller: three independent processing channels (A, B, C)
- 2oo3 voting on all safety outputs (barrier commands, interlocking clearance signal)
- Each channel independently evaluates all inputs; outputs driven only when 2 of 3 agree
- Watchdog timer on each channel: 100 ms timeout

**Hardware Components:**
- LCC: TMR safety controller with separate CPU boards per channel (e.g., TÜV-qualified SIL 4 PLC platform or bespoke STM32H7-based design)
- Track circuits: DC or AC coded track circuits per approach; OR axle counters (manufacturer-supplied, SIL 4 qualified separately)
- Barriers: Electromechanical actuators with gravity-fall failsafe; down position confirmed by stagger switches (redundant 2 per barrier)
- Warning lights: LED arrays with current monitoring for lamp health detection
- Obstacle detection: Radar or inductive loops with independent processing
- Power system: UPS with 8-hour battery, mains monitoring, battery health monitoring
- Communication: Ethernet (IEC 62280 / EN 50159) for interlocking link; modem for SCADA

**Software Components:**
- Train Detection Manager (TDM): processes track circuit / axle counter inputs, determines approach/departure state
- Protection Sequence Controller (PSC): state machine controlling warning-to-barrier-lowered-to-clearance sequence
- Obstacle Monitor (OBM): continuous evaluation of crossing zone clear status
- Barrier Control Driver (BCD): barrier actuator commands and position feedback processing
- Interlocking Interface Manager (IIM): SIL-compliant communication with interlocking, status encoding/decoding
- Fault Monitor (FMM): internal diagnostics, channel comparison, safe state management
- Event Logger (EVL): timestamped event recording to non-volatile storage
- HAL: hardware abstraction for all physical I/O

### Communication Interfaces

| Interface | Protocol | Data Rate | Purpose |
|-----------|----------|-----------|---------|
| LCC ↔ Interlocking | EN 50159 Category 2 (Ethernet + safety layer) | 100 Mbit/s | Crossing status, train detection confirmation |
| LCC ↔ Track Circuits | Relay/digital inputs (hardwired) | N/A | Train detection (occupancy) |
| LCC ↔ Barrier Actuators | 24 VDC relay outputs + feedback inputs | N/A | Barrier lower/raise commands, position feedback |
| LCC ↔ Warning Lights | 230 VAC relay outputs + current feedback | N/A | Light activation and health monitoring |
| LCC ↔ SCADA | Ethernet Modbus TCP | 10 Mbit/s | Operational status monitoring (non-safety) |
| Channel A ↔ B ↔ C (inter-channel) | SPI/parallel synchronous bus | 50 Mbit/s | Cross-channel voting data |
| LCC ↔ Maintenance Panel | RS-232 (key-switched, physically locked) | 9600 baud | Maintenance access only |

### Non-Functional Requirements

| Category | Requirement |
|----------|-------------|
| Safety Integrity | PFH ≤ 10^-8 per hour (SIL 4 per IEC 61508 Table 2) |
| Availability | System availability ≥ 99.95% per year |
| Reliability | MTBF ≥ 500,000 hours for the LCC module |
| Response Time | Train approach detection to first warning output ≤ 1 second |
| Fail-Safe Behaviour | Any single component failure drives system to barriers-down safe state |
| Service Life | ≥ 40 years with scheduled maintenance |
| Certifiability | EN 50129 Safety Case plus national Railway Safety Authority approval |
| Maintainability | MTTR ≤ 4 hours; spare parts available for 25 years |

### Design Constraints

- Software in C (MISRA C:2012 mandatory, SIL 4 configuration)
- TMR architecture requires independent software development for each channel or formal equivalence proof
- No dynamic memory allocation in safety-critical code
- Cyclomatic complexity ≤ 10
- 100% statement, branch, and condition coverage
- Fail-safe hardware design: outputs must default to safe state without software intervention
- Physical security: enclosure to be tamper-evident, rated IP67
- EN 50159 Category 2 safety communication for all interlocking messages

### Glossary

| Term | Definition |
|------|-----------|
| LCC | Level Crossing Controller — central safety processor |
| TMR | Triple Modular Redundant — three independent channels with 2oo3 voting |
| 2oo3 | Two-out-of-three voting — majority decision on safety outputs |
| PFH | Probability of Failure per Hour |
| SCADA | Supervisory Control and Data Acquisition — remote monitoring system |
| HAZ | Hazard |
| SF | Safety Function |
| CTC | Centralized Traffic Control |
| UPS | Uninterruptible Power Supply |
| HGV | Heavy Goods Vehicle |
| LCPS | Level Crossing Protection System |

---

## System 3: Automatic Train Protection On-Board Unit (SIL 4)

### System Overview

| Attribute | Value |
|-----------|-------|
| System Name | Automatic Train Protection On-Board Unit (ATP-OBU) |
| Abbreviation | ATP-OBU |
| SIL Level | SIL 4 |
| Domain | Rolling Stock — Train Protection and Supervision |
| Applicable Standards | EN 50128:2011, EN 50129:2018, EN 50126:2017, EN 50159 (communication), subset of ETCS SRS (if applicable) |
| Typical Deployment | Mainline passenger trains, high-speed rail; national ATP or ETCS Level 1/2 |
| Safety Authority Context | Vehicle safety case per EN 50129; national type approval required |

### Operational Environment

- Installed on locomotives, EMUs, and passenger coaches on electrified mainline networks
- Ambient temperature: -25°C to +55°C (operational in cab/underframe locations)
- Vibration: EN 61373 Category 1 Class B (underframe mounting)
- Power supply: 72–110 VDC nominal train battery (voltage range: 60–130 VDC)
- EMC: EN 50121-3-2 (rolling stock)
- Operating speeds: 0–350 km/h (design speed dependent on deployment)
- Traction: Electric (25 kV AC, 15 kV AC, or 750 V DC); no specific constraints on ATP
- Braking: Service brakes and emergency brakes (pneumatic and/or electrodynamic); ATP controls emergency brake application

### System Boundary

**Inside the system boundary:**
- ATP Central Unit (ATP-CU) — primary safety processor
- Balise Transmission Module (BTM) — Eurobalise transponder reader (receive-only)
- Tachometer Interface Unit (TIU) — dual-channel speed and distance measurement
- Brake Interface Unit (BIU) — emergency brake relay driver and monitoring
- Driver-Machine Interface (DMI) — speed display, mode indicator, acknowledgement button
- Odometry processing (speed and distance calculation from tachometer inputs)
- ATP-OBU internal event recorder (non-volatile, tamper-evident)

**Outside the system boundary:**
- Traction Control System — speed data forwarded; no direct ATP control of traction
- Train Management System (TMS) — receives ATP mode and status for display
- Trackside balises — passive transponders, no active interface
- Radio Block Centre (RBC) — only if ETCS Level 2/3 (then in scope of extension)
- Emergency brake system — ATP drives the brake relay; brakes themselves are out of scope
- Signalling infrastructure — ATP reads balise data; wayside system is out of scope

### Hazard List

| ID | Hazard Description | Severity | Frequency | Risk Level | SIL |
|----|-------------------|----------|-----------|------------|-----|
| HAZ-001 | Train exceeds speed limit without emergency brake application | Catastrophic | Occasional | Intolerable | SIL 4 |
| HAZ-002 | Train passes signal at danger (SPAD) without brake intervention | Catastrophic | Occasional | Intolerable | SIL 4 |
| HAZ-003 | Emergency brake applies spuriously at high speed (passenger injury risk) | Critical | Frequent | Intolerable | SIL 3 |
| HAZ-004 | ATP fails to detect balise data; incorrect movement authority applied | Catastrophic | Remote | Intolerable | SIL 4 |
| HAZ-005 | Speed measurement error causes incorrect brake curve calculation | Catastrophic | Remote | Intolerable | SIL 4 |
| HAZ-006 | ATP failure allows train to depart without valid movement authority | Catastrophic | Remote | Intolerable | SIL 4 |
| HAZ-007 | Driver bypasses ATP via maintenance override without authorisation | Catastrophic | Remote | Intolerable | SIL 4 |
| HAZ-008 | Odometry drift causes incorrect train position estimate (beyond tolerance) | Catastrophic | Occasional | Intolerable | SIL 4 |
| HAZ-009 | DMI failure masks speed supervision warning to driver | Critical | Remote | Tolerable (ALARP) | SIL 2 |
| HAZ-010 | ATP software fault causes silent failure (no brake, no warning) | Catastrophic | Incredible | Intolerable | SIL 4 |

**SIL Determination Basis:**
- Train-to-train collision or derailment from excessive speed are catastrophic irreversible events
- HAZ-001 through HAZ-002, HAZ-004 through HAZ-008, HAZ-010 all drive SIL 4
- HAZ-003 classified SIL 3 (critical but reversible with injury potential; spurious braking managed by design)
- HAZ-009 classified SIL 2 (redundant driver monitoring through cab signal backup)

### Functional Requirements

| ID | Requirement | Category |
|----|-------------|----------|
| SYS-FR-001 | The system SHALL continuously monitor train speed and compare against the applicable speed limit profile | Speed Supervision |
| SYS-FR-002 | The system SHALL apply the emergency brake when train speed exceeds the warning speed curve for more than 4 seconds without driver acknowledgement | Overspeed Response |
| SYS-FR-003 | The system SHALL apply the emergency brake immediately when train speed exceeds the emergency brake application curve | Emergency Braking |
| SYS-FR-004 | The system SHALL read and decode balise telegrams from Eurobalises to obtain movement authority and speed profile data | Balise Reading |
| SYS-FR-005 | The system SHALL calculate and maintain the train position within ±5 metres at speeds up to 160 km/h and ±10 metres at speeds above 160 km/h | Odometry |
| SYS-FR-006 | The system SHALL display current speed, permitted speed, target speed, and ATP mode to the driver at all times | DMI Display |
| SYS-FR-007 | The system SHALL warn the driver by audible and visual alert at least 6 seconds before emergency brake application | Driver Warning |
| SYS-FR-008 | The system SHALL apply emergency braking if the driver does not acknowledge an overspeed warning within 4 seconds | Unacknowledged Warning |
| SYS-FR-009 | The system SHALL log all safety-relevant events (balise reads, speed violations, brake applications, mode changes) in a tamper-evident recorder | Event Recording |
| SYS-FR-010 | The system SHALL perform a power-on self-test and refuse to release brakes if any critical fault is detected | Self-Test |
| SYS-FR-011 | The system SHALL enter and hold the safe state (emergency brake applied, movement authority void) on detection of any unhandled internal fault | Fault Handling |
| SYS-FR-012 | The system SHALL require authorised key activation for any maintenance mode; maintenance mode SHALL be time-limited to 30 minutes | Maintenance Mode |

### Safety Functions

| ID | Safety Function | SIL | Derived From |
|----|----------------|-----|--------------|
| SF-001 | Speed Supervision: Continuous enforcement of permitted speed profile with automatic emergency brake | SIL 4 | HAZ-001 |
| SF-002 | Signal Passed At Danger (SPAD) Prevention: Emergency brake on end-of-movement-authority overshoot | SIL 4 | HAZ-002 |
| SF-003 | Balise Integrity Check: Validate and reject corrupt or replayed balise telegrams | SIL 4 | HAZ-004 |
| SF-004 | Odometry Integrity: Dual-channel speed measurement with cross-comparison; halt on disagreement | SIL 4 | HAZ-005, HAZ-008 |
| SF-005 | Safe State on Fault: Emergency brake application on any safety function failure | SIL 4 | HAZ-010 |
| SF-006 | Movement Authority Enforcement: Inhibit train movement without valid movement authority | SIL 4 | HAZ-006 |
| SF-007 | Override Audit: Log and time-limit maintenance override; alert driver and TMS | SIL 4 | HAZ-007 |
| SF-008 | Driver Warning: Audible and visual overspeed warning before automatic brake intervention | SIL 3 | HAZ-003 (false brake mitigation) |

### System Architecture

**Processing Architecture:**
- Dual-channel (2oo2) ATP Central Unit with diverse hardware per channel (one FPGA-based, one microcontroller-based, or two independent MCU designs)
- Both channels compute independently; outputs driven via AND-gate relay logic
- Emergency brake relay de-energised (brake applied) unless both channels assert "safe to run"
- Channel comparison performed every 50 ms; disagreement → brake application

**Hardware Components:**
- ATP-CU: Dual-channel safety processor (e.g., TÜV-certified SIL 4 compute module or bespoke STM32H7 + FPGA design)
- BTM: Eurobalise reader with SIL 4 qualification (typically manufacturer-supplied separate module)
- TIU: Dual-channel tachometer conditioner — two independent pulse-count channels for speed/distance
- BIU: Vital relay output module with health monitoring; fail-open design (brake applied on loss of power or relay fault)
- DMI: TFT display + keypad with watchdog; not safety-critical (display failure triggers audio alert backup)
- Power: 72–110 VDC input, isolated DC-DC converters per channel; brownout detection
- Data recorder: 8 GB eMMC with cryptographic integrity checking

**Software Components:**
- Speed Supervisor (SSV): brake curve calculation, speed limit profile management, overspeed detection
- Balise Decoder (BLD): Eurobalise telegram parsing, CRC validation, movement authority extraction
- Odometry Engine (ODE): dual-channel speed integration, position accumulation, error bound tracking
- Brake Control Manager (BCM): emergency brake relay command logic, BIU monitoring
- DMI Manager (DMM): display rendering, driver acknowledgement handling, mode annunciation
- Mode Manager (MMG): ATP operating mode state machine (Standby, Full Supervision, Staff Responsible, Shunting, Maintenance)
- Fault Handler (FHD): cross-channel comparison, internal diagnostics, safe state management
- Event Recorder Interface (ERI): secure event logging with timestamp and integrity seal
- HAL: hardware abstraction for BTM, TIU, BIU, DMI, power monitor

### Communication Interfaces

| Interface | Protocol | Data Rate | Purpose |
|-----------|----------|-----------|---------|
| Balises ↔ BTM | Eurobalise 27.095 MHz inductive link (passive, IEC 62313) | 564 kbit/s (uplink) | Balise telegram reception |
| BTM ↔ ATP-CU | Proprietary serial (HDLC-like) or SIL-qualified bus | 1 Mbit/s | Decoded balise data transfer |
| TIU ↔ ATP-CU | Pulse train (two independent channels) | Up to 100 kHz | Speed/distance pulses |
| BIU ↔ ATP-CU | Dry relay output + supervised feedback | N/A | Emergency brake relay control/status |
| ATP-CU ↔ DMI | CAN 2.0B | 250 kbit/s | Speed, mode, alerts, acknowledgements |
| ATP-CU ↔ TMS | MVB (Multifunction Vehicle Bus, EN 50170) | 1.5 Mbit/s | ATP mode and status (non-safety read-only) |
| ATP-CU ↔ Data Recorder | SATA or SPI | 600 Mbit/s | Event log writes |
| Channel A ↔ Channel B | Synchronous dual-port RAM or SPI cross-link | 10 Mbit/s | Cross-channel comparison |

### Non-Functional Requirements

| Category | Requirement |
|----------|-------------|
| Safety Integrity | PFH ≤ 10^-8 per hour (SIL 4) |
| Spurious Brake Rate | Mean rate of spurious emergency brakes ≤ 1 per 100,000 train-hours |
| Availability | ATP system availability ≥ 99.9% |
| Response Time | Speed violation detected to brake relay de-energised ≤ 200 ms |
| Odometry Accuracy | Position error ≤ ±5 m at v ≤ 160 km/h; ±10 m at v > 160 km/h |
| Service Life | ≥ 30 years with scheduled component replacement |
| Certifiability | EN 50129 safety case; national type approval; ETCS compatibility test if applicable |
| Data Retention | Event recorder retains last 48 hours of data in crash-survivable storage |

### Design Constraints

- Software in C (MISRA C:2012), SIL 4: formal proof or exhaustive testing required in addition to 100% MC/DC coverage
- Dual-channel diverse design requires independent software development teams or formal equivalence proof
- Balise decoder must handle all Eurobalise telegram types per UNISIG SRS
- No dynamic memory allocation; fixed-size buffers for all balise and speed data
- Cyclomatic complexity ≤ 10
- Brake relay BIU must be fail-open (de-energised = brake applied) — hardware constraint drives software design
- Clock synchronisation required between channels: ±1 ms tolerance

### Glossary

| Term | Definition |
|------|-----------|
| ATP | Automatic Train Protection |
| OBU | On-Board Unit |
| CU | Central Unit |
| BTM | Balise Transmission Module |
| TIU | Tachometer Interface Unit |
| BIU | Brake Interface Unit |
| DMI | Driver-Machine Interface |
| SPAD | Signal Passed At Danger |
| ETCS | European Train Control System |
| RBC | Radio Block Centre |
| SRS | System Requirements Specification |
| EMA | End of Movement Authority |
| TMS | Train Management System |
| MVB | Multifunction Vehicle Bus |
| PFH | Probability of Failure per Hour |

---

## System 4: Platform Screen Door System (SIL 2)

### System Overview

| Attribute | Value |
|-----------|-------|
| System Name | Platform Screen Door System (PSDS) |
| Abbreviation | PSDS |
| SIL Level | SIL 2 |
| Domain | Infrastructure — Station Platform Safety |
| Applicable Standards | EN 50128:2011, EN 50129:2018, EN 50126:2017, EN 50159 (communication) |
| Typical Deployment | Metro, light rail, and automated people movers with fixed stopping positions |
| Safety Authority Context | Infrastructure safety case; compatibility with rolling stock type approval required |

### Operational Environment

- Installed at metro or light rail station platforms in underground, at-grade, or elevated configurations
- Ambient temperature: -10°C to +40°C (station platform environment, climate controlled underground)
- Humidity: 10% to 95% (non-condensing in climate-controlled underground stations)
- Power supply: 400 VAC 3-phase mains primary, 48 VDC battery backup (≥ 2 hours)
- EMC: EN 50121-2 (railway infrastructure and apparatus)
- Train stopping accuracy: ±300 mm (required for door alignment with train doors)
- Train types: Fixed-formation trains with defined door positions; compatible with CBTC or conventional signalling

### System Boundary

**Inside the system boundary:**
- Platform Screen Door Controller (PSDC) — central safety processor per platform (one per platform face)
- Individual Door Control Modules (DCM) — one per PSD leaf pair, distributed along the platform
- Position sensors per door leaf (obstruction/open/closed confirmation)
- Obstacle detection (infrared or light curtain between door leaves when closing)
- Door drive motors and locking mechanisms per door unit
- PSDC-to-DCM field bus (safety communication)
- Interface to train door control or CBTC Automatic Train Operation (ATO) system (door open/close commands)
- Platform edge emergency stop buttons (manual override)
- Local operator panel (station staff key-switch)
- Status indication lights (open/closed, fault) per door unit (passenger-facing)

**Outside the system boundary:**
- CBTC ATO system or train door control — provides door open/close commands; receives PSD status
- Station control room display — receives summary status via non-safety SCADA interface
- Train detection system — used by ATO/train control; PSDS does not directly interface
- Station emergency ventilation — no direct interface
- Fire alarm system — emergency commands received as hardwired inputs (in scope as input interface)

### Hazard List

| ID | Hazard Description | Severity | Frequency | Risk Level | SIL |
|----|-------------------|----------|-----------|------------|-----|
| HAZ-001 | PSD closes on passenger (entrapment/injury) | Critical | Frequent | Intolerable | SIL 2 |
| HAZ-002 | PSD opens while train not present (fall onto track) | Catastrophic | Occasional | Intolerable | SIL 2 |
| HAZ-003 | PSD and train door misaligned — passenger steps into gap | Critical | Occasional | Intolerable | SIL 2 |
| HAZ-004 | Train departs with PSD open (passenger caught between PSD and train) | Catastrophic | Remote | Intolerable | SIL 2 |
| HAZ-005 | PSD fails to open at station (passenger trapped on train) | Marginal | Frequent | Tolerable (ALARP) | SIL 1 |
| HAZ-006 | PSD fails to close; train held at station (service disruption) | Negligible | Frequent | Broadly Acceptable | SIL 0 |
| HAZ-007 | Fire condition — PSD fails to open for emergency evacuation | Critical | Incredible | Tolerable (ALARP) | SIL 2 |
| HAZ-008 | Spurious open command from ATO fault causes unexpected door opening | Catastrophic | Remote | Intolerable | SIL 2 |

**SIL Determination Basis:**
- HAZ-002, HAZ-004 could be catastrophic (fall onto electrified track or train dragging) but platform metro speeds and frequencies place them at SIL 2 rather than SIL 3-4
- SIL 2 justified by controlled environment, dwell time management, and redundant train-side interlocks
- HAZ-001 is the highest-frequency safety-relevant event driving the SIL 2 classification

### Functional Requirements

| ID | Requirement | Category |
|----|-------------|----------|
| SYS-FR-001 | The system SHALL open all PSDs aligned with the stopped train's door positions when commanded by ATO/train control | Door Operation |
| SYS-FR-002 | The system SHALL close all PSDs when commanded by ATO/train control | Door Operation |
| SYS-FR-003 | The system SHALL confirm train presence and alignment before executing any open command | Train Alignment |
| SYS-FR-004 | The system SHALL detect obstacles in the closing path and reverse PSD motion within 200 ms | Obstacle Detection |
| SYS-FR-005 | The system SHALL withhold PSD-closed-and-locked confirmation from ATO until all PSDs are confirmed locked | Departure Interlock |
| SYS-FR-006 | The system SHALL open all PSDs for emergency evacuation on fire alarm input within 3 seconds | Emergency Evacuation |
| SYS-FR-007 | The system SHALL provide door-open and door-closed indication lights visible to passengers on each door unit | Passenger Indication |
| SYS-FR-008 | The system SHALL detect and report individual door faults; defective doors SHALL be individually isolatable | Fault Management |
| SYS-FR-009 | The system SHALL enter safe state (all doors locked closed or all doors free/open in emergency) on unhandled internal fault | Fault Handling |
| SYS-FR-010 | The system SHALL log all door operations, faults, and commands with timestamps | Diagnostics |
| SYS-FR-011 | The system SHALL allow station staff to manually control individual doors via key-switch panel (with logged authority) | Manual Operation |
| SYS-FR-012 | The system SHALL reject any open command if train presence is not confirmed | Safety Interlock |

### Safety Functions

| ID | Safety Function | SIL | Derived From |
|----|----------------|-----|--------------|
| SF-001 | Train Presence Interlock: Inhibit PSD opening unless train presence and alignment confirmed | SIL 2 | HAZ-002, HAZ-008 |
| SF-002 | Obstacle Detection and Reversal: Detect and respond to obstacle within 200 ms during closing | SIL 2 | HAZ-001 |
| SF-003 | Departure Interlock: Withhold PSD-locked confirmation until all PSDs confirmed closed and locked | SIL 2 | HAZ-004 |
| SF-004 | Safe State on Fault: Lock all PSDs closed and inhibit movement on internal fault | SIL 2 | HAZ-004, HAZ-008 |
| SF-005 | Emergency Evacuation Mode: Open all PSDs on confirmed fire alarm within 3 seconds | SIL 2 | HAZ-007 |
| SF-006 | Alignment Verification: Confirm door alignment within ±300 mm tolerance before opening | SIL 2 | HAZ-003 |

### System Architecture

**Processing Architecture:**
- Single PSDC safety processor (SIL 2 qualified hardware) per platform face
- DCMs distributed along the platform, connected via deterministic field bus
- PSDC performs centralised safety logic; DCMs handle local motor control and sensor I/O
- Watchdog on PSDC: 200 ms timeout → safe state

**Hardware Components:**
- PSDC: SIL 2 qualified safety PLC or bespoke safety processor (e.g., Cortex-M7 with hardware watchdog)
- DCM: Per-door-unit embedded controller (STM32F4 class) with local motor driver and sensor conditioning
- Door drives: DC brushless motors with encoder feedback and mechanical end-stops
- Obstacle sensors: Light curtains (IEC 61496 Type 4 ESPE for SIL 2) per door opening
- Position sensors: Reed switches + magnetic targets for open/closed/locked positions (2 per door leaf)
- Field bus: ProfiSafe or CANopen Safety on RS-485 physical layer
- Power: 400 VAC → 48 VDC for door drives; 24 VDC for controls; battery backup
- Indication lights: LED strip per door unit, driven by DCM, supervised by current monitoring

**Software Components:**
- Platform Sequence Controller (PSC): centralised door operation state machine
- Train Alignment Monitor (TAM): processes train presence and alignment inputs
- Obstacle Detection Manager (ODM): processes light curtain inputs from all DCMs
- DCM Communication Manager (DCM-CM): field bus master, DCM health monitoring
- ATO Interface Manager (AIM): receives/validates commands from ATO; sends PSD status
- Emergency Manager (EMG): fire alarm input processing, emergency mode control
- Fault Manager (FMG): fault detection, isolation, safe state management
- Event Logger (EVL): timestamped event recording to flash storage
- HAL: abstraction for field bus, ATO interface, power monitoring

### Communication Interfaces

| Interface | Protocol | Data Rate | Purpose |
|-----------|----------|-----------|---------|
| ATO/Train Control ↔ PSDC | CAN 2.0B or Ethernet (EN 50159 Cat. 1 for safety commands) | 250 kbit/s – 100 Mbit/s | Door commands, PSD status |
| PSDC ↔ DCMs | ProfiSafe (PROFIBUS DP) or CANopen Safety | 1.5 Mbit/s | Door commands, position/obstacle feedback |
| PSDC ↔ Emergency Panel | Hardwired 24 VDC inputs | N/A | Platform emergency stop buttons, fire alarm relay |
| PSDC ↔ SCADA | Ethernet Modbus TCP | 10 Mbit/s | Non-safety status reporting to station control |
| PSDC ↔ Operator Panel | RS-232 (key-switched) | 115.2 kbit/s | Staff control and maintenance access |

### Non-Functional Requirements

| Category | Requirement |
|----------|-------------|
| Safety Integrity | PFH ≤ 10^-6 per hour (SIL 2 per IEC 61508 Table 2) |
| Availability | System availability ≥ 99.8% per platform per day |
| Reliability | MTBF ≥ 100,000 hours for PSDC |
| Response Time | Command to first door movement ≤ 300 ms; obstacle detected to reversal ≤ 200 ms |
| Service Life | ≥ 25 years with scheduled maintenance |
| Certifiability | EN 50129 Safety Case; compatibility test report with train type |
| Maintainability | MTTR ≤ 2 hours; individual DCM replaceable in < 30 minutes |
| Emergency Response | All PSDs open for evacuation within 3 seconds of confirmed fire alarm |

### Design Constraints

- Software in C (MISRA C:2012, SIL 2 configuration)
- No dynamic memory allocation
- Cyclomatic complexity ≤ 15 (SIL 2 limit)
- 100% branch coverage and MC/DC coverage mandatory
- EN 50159 Category 1 safety communication required for ATO interface
- DCM firmware upgradeable in field (with cryptographic signature verification)
- Physical installation: PSDC enclosure rated IP54; DCMs rated IP44 (platform environment)

### Glossary

| Term | Definition |
|------|-----------|
| PSDS | Platform Screen Door System |
| PSDC | Platform Screen Door Controller |
| DCM | Door Control Module — per-door-unit embedded controller |
| ATO | Automatic Train Operation — automated driving system |
| CBTC | Communications-Based Train Control |
| PFH | Probability of Failure per Hour |
| ESPE | Electro-Sensitive Protective Equipment (light curtains) |
| PSD | Platform Screen Door |
| SIL | Safety Integrity Level |
| HAZ | Hazard |
| SF | Safety Function |

---

## Catalogue Metadata

| System | SIL | Domain | Complexity | Recommended For |
|--------|-----|--------|-----------|----------------|
| Train Door Control System | SIL 3 | Rolling Stock | Medium | Learning EN 50128 platform; first project |
| Level Crossing Protection System | SIL 4 | Infrastructure | High | Infrastructure projects; full V-Model |
| ATP On-Board Unit | SIL 4 | Rolling Stock | Very High | Advanced users; ETCS/ATP projects |
| Platform Screen Door System | SIL 2 | Infrastructure | Medium | Metro/LRT projects; SIL 2 certification |

**Document Version**: 1.0  
**Last Updated**: 2026-03-15  
**Maintained By**: EN50128 Platform Team
