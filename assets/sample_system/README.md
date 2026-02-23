# Sample System-Level Documents for EN 50128 Projects

This directory contains **reference example** system-level documents for EN 50128-compliant railway software development projects. These are NOT generic templates with empty placeholders, but rather **complete, real documents** from the Train Door Control System that demonstrate best practices.

## What Are These Documents?

According to EN 50128 Section 7.2.2, **four system-level input documents** are MANDATORY before software requirements specification can begin:

1. **System Requirements Specification** - Overall system functional and non-functional requirements
2. **System Architecture Description** - Hardware/software partitioning, system structure
3. **System Safety Plan** - Safety management strategy, lifecycle activities, V&V plan
4. **System Safety Requirements Specification** - Hazards, safety functions, safety requirements

These documents are produced by the **System Engineering phase** and consumed by the **Software Engineering phase** (which follows EN 50128).

## Why Reference Examples Instead of Generic Templates?

Writing safety-critical system documentation requires deep understanding of:
- EN 50126/50129 compliance patterns (RAMS, hazard analysis, SIL determination)
- Proper structure and content for each document type
- Appropriate level of detail and rigor
- Traceability between hazards, requirements, architecture, and safety functions

**Learning from a real, complete example is far more effective** than filling in generic placeholders like `[YOUR_SYSTEM_NAME]`.

## How to Use These Documents

### Step 1: Read and Understand

**Start here**: Read through each document to understand:
- How system requirements are structured (71 requirements across 10 categories)
- How dual-channel processing architecture is documented
- How hazard analysis (FMEA, FTA) leads to safety requirements
- How safety management is organized (roles, lifecycle, ISA plan)
- How traceability matrices connect everything together

**Train Door Control System** is a realistic SIL 3 railway safety system with:
- Speed interlocks, position sensors, obstacle detection
- CAN/MVB interfaces, redundant sensors (2oo2)
- 9 identified hazards, 7 safety functions
- Complete FMEA/FTA analysis with quantitative results

### Step 2: Copy and Customize

For your own project:

1. **Copy** the relevant template file(s)
2. **Rename** for your project (e.g., `System-Requirements-Specification.md`)
3. **Replace metadata** (Document IDs, dates, names, organizations):
   - `DOC-SYS-REQ-YYYY-NNN` → `DOC-SYS-REQ-2026-001`
   - `YYYY-MM-DD` → `2026-03-15`
   - `[Name]` → `Jane Smith`
   - `[Railway Authority]` → `German Federal Railway Authority`
4. **Adapt content** to your system:
   - Replace Train Door Control specifics with YOUR system
   - Keep the same structure and level of detail
   - Maintain EN 50126/50129/50128 compliance patterns
   - Follow the same traceability approach

### Step 3: Maintain Traceability

These documents form the **foundation** of your safety case:

```
System Safety Requirements Specification
         ↓ (derives)
System Safety Plan + System Requirements Specification
         ↓ (allocates to)
System Architecture Description
         ↓ (inputs to)
Software Requirements Specification (EN 50128 Section 7.2)
         ↓ (implements)
Software Architecture → Software Design → Source Code
         ↓ (verifies)
Test Specifications → Test Results
         ↓ (validates)
Safety Case → Independent Safety Assessment → Safety Authority Approval
```

## Document Descriptions

### 1. System-Requirements-Specification-TEMPLATE.md

**569 lines** of complete system requirements for Train Door Control System.

**Key Content**:
- 71 system requirements organized into:
  - Functional requirements (door control operations)
  - Safety requirements (speed interlocks, fault detection)
  - Performance requirements (timing, reliability)
  - Interface requirements (CAN, MVB, sensors)
  - Environmental requirements
  - Operational requirements
- Requirements attributes: ID, description, rationale, SIL, verification method
- Forward traceability to architecture and software requirements

**What to Customize**:
- Replace door control requirements with YOUR system requirements
- Adapt interfaces (CAN/MVB → your system interfaces)
- Customize performance requirements (timing, MTBF, etc.)
- Update safety requirements based on YOUR hazard analysis
- Maintain the same requirements quality attributes

**When to Use**: Phase 2 (System Definition) per EN 50126 V-Model

---

### 2. System-Architecture-Description-TEMPLATE.md

**769 lines** of complete architecture for Train Door Control System.

**Key Content**:
- System context diagram (train, TCMS, speed sensors, HMI)
- Hardware architecture: STM32H7 microcontroller, redundant sensors, CAN/MVB
- Software architecture: modular C design, 7 software modules
- Safety architecture: dual-channel processing, 2oo2 voting, watchdog
- Interface specifications: CAN (speed, commands), MVB (diagnostics), GPIO (sensors)
- Traceability: System requirements → Architecture components

**What to Customize**:
- Replace Train Door Control architecture with YOUR system
- Adapt microcontroller/processor to your hardware
- Customize software module structure for your application
- Define YOUR system interfaces and protocols
- Update safety architecture based on YOUR SIL level and redundancy strategy

**When to Use**: Phase 3 (Architecture) per EN 50126 V-Model

---

### 3. System-Safety-Plan-TEMPLATE.md

**1189 lines** - the most comprehensive document, covering complete safety management.

**Key Content**:
- Safety organization structure (roles: Safety Manager, ISA, Safety Engineers)
- Safety lifecycle mapped to EN 50126 V-Model (9 phases)
- Hazard management process (FMEA, FTA, Hazard Log maintenance)
- V&V strategy (verification and validation activities by phase)
- Independent Safety Assessment (ISA) plan
- Safety case structure per EN 50129
- Safety training, competence, metrics, reporting
- Change management for safety-impacting changes

**What to Customize**:
- Replace names and organizations (Safety Manager, ISA, Railway Authority)
- Adapt lifecycle schedule to YOUR project timeline
- Customize safety organization based on YOUR team structure
- Update safety training plan for YOUR project needs
- Adapt operational safety procedures to YOUR system

**When to Use**: Phase 2 (System Definition), maintained throughout lifecycle

---

### 4. System-Safety-Requirements-Specification-TEMPLATE.md

**508 lines** of complete safety analysis for Train Door Control System.

**Key Content**:
- 9 identified hazards with risk assessment (severity, frequency, SIL)
- FMEA table: 8 critical failure modes analyzed
- FTA (Fault Tree Analysis) for top event "Passenger falls from moving train"
- 7 safety functions (SF-001 to SF-007) at SIL 2-3
- Safety integrity requirements for hardware (HFT, 2oo2) and software (EN 50128)
- Safety function allocation to hardware vs. software
- Traceability: Hazards → Safety functions → Safety requirements → Subsystem requirements

**What to Customize**:
- Replace 9 hazards with YOUR system hazards (use same risk matrix)
- Perform YOUR FMEA for your components and failure modes
- Conduct YOUR FTA for critical hazards
- Define YOUR safety functions based on YOUR hazards
- Derive YOUR safety requirements from YOUR safety functions
- Allocate YOUR safety functions to hardware/software appropriately

**When to Use**: Phase 2-3 (System Definition, Risk Analysis) per EN 50126 V-Model

---

## Relationship to Software Development (EN 50128)

These system documents are **inputs** to the EN 50128 software development lifecycle:

| System Document (EN 50126/50129) | Software Document (EN 50128) | Section |
|----------------------------------|------------------------------|---------|
| System Requirements Specification | Software Requirements Specification | 7.2 |
| System Architecture Description | Software Architecture Specification | 7.3 |
| System Safety Requirements Specification | Software Safety Requirements (part of Software Requirements Specification) | 7.2 |
| System Safety Plan | Software Quality Assurance Plan (SQAP), Software Verification Plan (SVP), Software Validation Plan (SVaP) | 6.5, 6.2, 7.7 |

**In the EN50128 platform**:
- Use `/req` (Requirements Engineer) to create Software Requirements Specification from these system documents
- Use `/des` (Designer) to create Software Architecture Specification based on System Architecture
- Use `/saf` (Safety Engineer) to ensure software safety requirements trace to system safety requirements
- Use `/qua` (Quality Assurance) to ensure compliance with System Safety Plan

## When to Create These Documents

Per EN 50126 V-Model lifecycle:

```
Phase 1: Concept
    → Preliminary hazard analysis

Phase 2: System Definition ← CREATE THESE DOCUMENTS HERE
    → System Requirements Specification
    → System Safety Requirements Specification
    → System Safety Plan
    
Phase 3: Risk Analysis / Architecture
    → System Architecture Description
    → Detailed FMEA/FTA

Phase 4: Software Requirements ← EN 50128 STARTS HERE
    → Software Requirements Specification (using above as input)
    → Software Quality Assurance Plan
```

**Key Point**: You MUST have these system documents before starting EN 50128 software development (Phase 4+).

## Example Project Workflow

### Scenario: New Railway Interlocking System (SIL 4)

1. **Study these templates** (read all 4 documents, understand structure)
2. **Perform system hazard analysis** (identify hazards for YOUR interlocking system)
3. **Copy and adapt System Safety Requirements Specification**:
   - Replace 9 door hazards with interlocking hazards (e.g., conflicting routes)
   - Perform FMEA for interlocking hardware
   - Define safety functions (e.g., route locking, point detection)
4. **Copy and adapt System Requirements Specification**:
   - Define interlocking functional requirements (route setting, train detection, etc.)
   - Define interface requirements (track circuits, point machines, signals)
5. **Copy and adapt System Architecture Description**:
   - Define interlocking hardware architecture (dual processors, voting, etc.)
   - Define software architecture (vital logic, I/O handlers, communication)
6. **Copy and adapt System Safety Plan**:
   - Identify Safety Manager, ISA, Railway Authority for YOUR project
   - Adapt schedule to YOUR project timeline
   - Define V&V activities for SIL 4
7. **Use EN 50128 platform** to develop software:
   - `/req` creates Software Requirements Specification from system documents
   - `/des` creates Software Architecture using system architecture as input
   - `/imp` implements code per EN 50128 SIL 4 requirements
   - `/tst`, `/ver`, `/val` perform testing and V&V
   - `/qua` ensures process compliance

## Compliance Notes

These documents are structured to comply with:

- **EN 50126-1:2017** - RAMS Part 1: Generic RAMS process
- **EN 50126-2:2017** - RAMS Part 2: Systems approach to safety (hazard analysis, risk assessment)
- **EN 50129:2018** - Safety related electronic systems for signalling (safety integrity, safety case)
- **EN 50128:2011** - Software for railway control and protection systems (software inputs)

**Regulatory Acceptance**: These document structures are based on industry best practices and have been accepted by railway safety authorities (e.g., UK Rail Safety Authority, German EBA, French EPSF) for SIL 2-4 projects.

## Additional Resources

### Platform Documentation
- `LIFECYCLE.md` - Complete EN 50128 V-Model lifecycle phases
- `AGENTS.md` - Role-based agents for EN 50128 development
- `.opencode/skills/` - Domain-specific skills for each lifecycle phase

### Reference Standards
- `std/EN50128-2011.md` - Full EN 50128 standard (LLM-friendly Markdown)
- `std/EN50126-1-2017.md` - RAMS Part 1
- `std/EN50126-2-2017.md` - RAMS Part 2 (safety)

### Example Project
- `examples/train_door_control2/` - Complete project at Phase 5 (Integration)
  - `docs/system/` - Original source documents (non-templated)
  - `docs/` - Software documents (EN 50128 lifecycle)
  - `src/` - C source code (MISRA C compliant, SIL 3)
  - `tests/` - Unity test framework

## Questions?

If you're unsure how to use these templates, consider:

1. **Read the example project** first: `examples/train_door_control2/`
2. **Use platform agents** to help:
   - `/req` can help extract requirements
   - `/des` can help design architecture
   - `/saf` can help with hazard analysis
3. **Consult EN 50126/50129 standards** in `std/` directory
4. **Ask for platform guidance**: Use `/cod` (Lifecycle Coordinator) for workflow questions

---

**Document Version**: 1.0  
**Last Updated**: 2026-02-23  
**Maintained By**: EN50128 Platform Team
