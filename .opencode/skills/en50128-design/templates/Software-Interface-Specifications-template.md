# Software Interface Specifications (SIS)

**Document ID**: DOC-DES-YYYY-NNN  
**Project**: [Project Name]  
**Software Component**: [Component Name]  
**SIL Level**: [0/1/2/3/4]  
**Version**: [X.Y]  
**Date**: [YYYY-MM-DD]

---

## Document Control

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | YYYY-MM-DD | [Author] | Initial draft | - |
| 1.0 | YYYY-MM-DD | [Author] | First release | [Approver] |

---

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Designer** (Author) | [Name] | | YYYY-MM-DD |
| **Verifier** (Reviewer) | [Name] | | YYYY-MM-DD |
| **Quality Assurance** (Template Check) | [Name] | | YYYY-MM-DD |
| **Project Manager** (Approval) | [Name] | | YYYY-MM-DD |

---

## EN 50128 References

| Section | Title | Relevance |
|---------|-------|-----------|
| **7.3** | Software Architecture and Design | PRIMARY - Design phase |
| **Table A.3** | Software Architecture techniques | Design techniques by SIL |
| **Table A.4** | Software Design and Implementation | Implementation guidance |
| **Annex C** | Documentation Requirements | Deliverable requirements |

---

## 1. Introduction

### 1.1 Purpose

This document specifies all interfaces for [Software Component] in accordance with EN 50128:2011 Section 7.3.

**Objectives**:
- Define all internal software interfaces (module-to-module)
- Define external software interfaces (system boundaries)
- Define hardware-software interfaces
- Specify data structures, protocols, and timing for all interfaces
- Ensure traceability from requirements to interfaces

**EN 50128 Table A.3**: Fully Defined Interface is **HIGHLY RECOMMENDED** for all SIL levels

### 1.2 Scope

**In Scope**:
- Internal interfaces between software modules
- External interfaces to other systems
- Hardware abstraction layer (HAL) interfaces
- Data structures and type definitions
- Function prototypes and APIs
- Communication protocols
- Error codes and error handling

**Out of Scope**:
- Implementation details (see Software Design Specification)
- Hardware specifications (see Hardware Specification)

### 1.3 Definitions

| Term | Definition |
|------|------------|
| **Interface** | Boundary between two modules where data/control is exchanged |
| **API** | Application Programming Interface |
| **HAL** | Hardware Abstraction Layer |
| **Protocol** | Rules governing data exchange |

---

## 2. Interface Overview

### 2.1 Interface Architecture

```
┌─────────────────────────────────────────────┐
│         External System Interfaces          │
├─────────────────────────────────────────────┤
│                                             │
│  ┌───────────┐    ┌───────────┐           │
│  │ Module A  │◄──►│ Module B  │           │
│  └───────────┘    └───────────┘           │
│        ▲               ▲                    │
│        │               │                    │
│  ┌─────┴───────────────┴─────┐            │
│  │   Hardware Abstraction     │            │
│  │         Layer (HAL)         │            │
│  └────────────────────────────┘            │
│                 ▲                           │
└─────────────────┼───────────────────────────┘
                  │
          ┌───────┴────────┐
          │    Hardware    │
          └────────────────┘
```

### 2.2 Interface Categories

| Interface Type | Count | Description |
|----------------|-------|-------------|
| Internal Software Interfaces | [N] | Module-to-module interfaces |
| External Software Interfaces | [M] | System-to-system interfaces |
| Hardware-Software Interfaces | [P] | HAL interfaces to hardware |
| User Interfaces | [Q] | User interaction (if applicable) |

---

## 3. Internal Software Interfaces

### 3.1 Module Interface: [Module A ↔ Module B]

**Interface ID**: INT-SW-001

**Description**: [Brief description of interface purpose]

**Direction**: [Module A → Module B] or [Bidirectional]

**Type**: [Function call / Shared memory / Message passing / Event]

**Requirements Traced**: REQ-ARCH-XXX, REQ-DES-XXX

#### 3.1.1 Data Structures

```c
/**
 * @brief Interface data structure
 */
typedef struct {
    uint32_t field1;    /**< Description of field1 */
    uint16_t field2;    /**< Description of field2 */
    uint8_t  field3;    /**< Description of field3 */
    uint8_t  reserved;  /**< Reserved for alignment */
} interface_data_t;
```

#### 3.1.2 Function Prototypes

```c
/**
 * @brief Function name
 * @param[in] param1 Description
 * @param[out] param2 Description
 * @return error_t Error code
 */
error_t function_name(const interface_data_t *param1, uint32_t *param2);
```

#### 3.1.3 Error Codes

| Error Code | Value | Description |
|------------|-------|-------------|
| ERROR_SUCCESS | 0x0000 | Operation successful |
| ERROR_INVALID_PARAM | 0x0001 | Invalid parameter |
| ERROR_TIMEOUT | 0x0002 | Operation timeout |

#### 3.1.4 Timing Constraints

| Parameter | Value | Unit |
|-----------|-------|------|
| Maximum response time | [X] | ms |
| Minimum call interval | [Y] | ms |
| Timeout | [Z] | ms |

#### 3.1.5 Usage Example

```c
interface_data_t data = {
    .field1 = 100U,
    .field2 = 50U,
    .field3 = 1U,
    .reserved = 0U
};

uint32_t result;
error_t err = function_name(&data, &result);
if (ERROR_SUCCESS == err) {
    // Process result
}
```

---

## 4. External Software Interfaces

### 4.1 External Interface: [System X]

**Interface ID**: INT-EXT-001

**Description**: [Interface to external system X]

**Protocol**: [UART / SPI / I2C / CAN / Ethernet / etc.]

**Direction**: [Input / Output / Bidirectional]

**Requirements Traced**: REQ-FUNC-XXX, REQ-IF-XXX

#### 4.1.1 Communication Protocol

**Protocol Type**: [Serial / Network / etc.]

**Physical Layer**:
- Connector: [Type]
- Voltage levels: [Voltage]
- Baud rate: [Rate] (if serial)
- Clock: [Frequency] (if applicable)

**Data Link Layer**:
- Frame format: [Format]
- Error detection: [CRC/Checksum/Parity]
- Flow control: [Hardware/Software/None]

#### 4.1.2 Message Format

```
┌────────┬────────┬────────┬────────┬────────┐
│ Header │ Length │  Data  │  CRC   │  End   │
├────────┼────────┼────────┼────────┼────────┤
│ 1 byte │ 2 bytes│ N bytes│ 2 bytes│ 1 byte │
└────────┴────────┴────────┴────────┴────────┘
```

**Header**: [Description]  
**Length**: [Description]  
**Data**: [Description]  
**CRC**: [CRC-16/CRC-32 algorithm]  
**End**: [Description]

#### 4.1.3 Command Set

| Command ID | Name | Direction | Parameters | Response |
|------------|------|-----------|------------|----------|
| 0x01 | CMD_INIT | Output | None | ACK/NACK |
| 0x02 | CMD_READ | Output | Address, Length | Data + ACK |
| 0x03 | CMD_WRITE | Output | Address, Data | ACK/NACK |

#### 4.1.4 Timing

| Parameter | Value | Unit |
|-----------|-------|------|
| Command timeout | [X] | ms |
| Response timeout | [Y] | ms |
| Retry interval | [Z] | ms |
| Maximum retries | [N] | - |

---

## 5. Hardware-Software Interfaces (HAL)

### 5.1 HAL Interface: [Peripheral Name]

**Interface ID**: INT-HAL-001

**Hardware**: [UART1 / SPI1 / Timer1 / GPIO / etc.]

**Purpose**: [Interface purpose]

**Requirements Traced**: REQ-HWSW-XXX

#### 5.1.1 HAL Function Prototypes

```c
/**
 * @brief Initialize hardware peripheral
 * @param[in] config Configuration structure
 * @return error_t Error code
 */
error_t hal_peripheral_init(const hal_config_t *config);

/**
 * @brief Read from hardware peripheral
 * @param[out] data Output buffer
 * @param[in] size Buffer size
 * @return error_t Error code
 */
error_t hal_peripheral_read(uint8_t *data, uint16_t size);

/**
 * @brief Write to hardware peripheral
 * @param[in] data Input buffer
 * @param[in] size Data size
 * @return error_t Error code
 */
error_t hal_peripheral_write(const uint8_t *data, uint16_t size);
```

#### 5.1.2 Configuration Structure

```c
typedef struct {
    uint32_t baudrate;      /**< Baud rate (for UART) */
    uint8_t  data_bits;     /**< Data bits (5/6/7/8) */
    uint8_t  stop_bits;     /**< Stop bits (1/2) */
    uint8_t  parity;        /**< Parity (none/odd/even) */
} hal_config_t;
```

#### 5.1.3 Register Mapping

| Register | Address | Access | Description |
|----------|---------|--------|-------------|
| CTRL | 0x4000_0000 | RW | Control register |
| STATUS | 0x4000_0004 | RO | Status register |
| DATA | 0x4000_0008 | RW | Data register |

---

## 6. Data Type Definitions

### 6.1 Common Data Types

```c
/* Fixed-width integer types (MANDATORY SIL 2+) */
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;

/* Boolean type */
typedef bool boolean_t;

/* Error code type */
typedef uint32_t error_t;
```

### 6.2 Interface-Specific Types

```c
/**
 * @brief State enumeration
 */
typedef enum {
    STATE_IDLE = 0U,
    STATE_BUSY = 1U,
    STATE_ERROR = 2U,
    STATE_MAX = 3U
} state_t;

/**
 * @brief Configuration structure
 */
typedef struct {
    uint32_t parameter1;
    uint16_t parameter2;
    uint8_t  parameter3;
    uint8_t  reserved;
} config_t;
```

---

## 7. Error Handling

### 7.1 Error Code Ranges

| Module | Range | Description |
|--------|-------|-------------|
| Common | 0x0000-0x00FF | Common error codes |
| Module A | 0x1000-0x10FF | Module A errors |
| Module B | 0x2000-0x20FF | Module B errors |
| HAL | 0x9000-0x9FFF | HAL errors |

### 7.2 Common Error Codes

| Error Code | Value | Description |
|------------|-------|-------------|
| ERROR_SUCCESS | 0x0000 | Operation successful |
| ERROR_NULL_POINTER | 0x0001 | NULL pointer passed |
| ERROR_INVALID_PARAMETER | 0x0002 | Invalid parameter |
| ERROR_TIMEOUT | 0x0003 | Operation timeout |
| ERROR_NOT_INITIALIZED | 0x0004 | Module not initialized |
| ERROR_BUSY | 0x0005 | Resource busy |
| ERROR_OVERFLOW | 0x0006 | Buffer overflow |

---

## 8. Memory Map

### 8.1 Software Memory Map

| Section | Start Address | End Address | Size | Access |
|---------|---------------|-------------|------|--------|
| Code (Flash) | 0x0800_0000 | 0x0801_FFFF | 128KB | RO |
| Data (RAM) | 0x2000_0000 | 0x2000_3FFF | 16KB | RW |
| Stack | 0x2000_3000 | 0x2000_3FFF | 4KB | RW |
| Heap | N/A | N/A | 0KB | N/A (SIL 2+) |

### 8.2 Peripheral Memory Map

| Peripheral | Base Address | Size | Description |
|------------|--------------|------|-------------|
| UART1 | 0x4000_0000 | 1KB | UART peripheral |
| SPI1 | 0x4000_1000 | 1KB | SPI peripheral |
| GPIO | 0x4000_2000 | 1KB | GPIO ports |
| Timer1 | 0x4000_3000 | 1KB | Timer peripheral |

---

## 9. Interface Constraints

### 9.1 Timing Constraints

| Interface | Parameter | Constraint |
|-----------|-----------|------------|
| INT-SW-001 | Max response time | ≤ 10 ms |
| INT-EXT-001 | Timeout | ≤ 100 ms |
| INT-HAL-001 | Interrupt latency | ≤ 50 µs |

### 9.2 Resource Constraints

| Resource | Limit | Usage |
|----------|-------|-------|
| Stack size | 4KB | [Actual usage] |
| RAM usage | 16KB | [Actual usage] |
| Flash usage | 128KB | [Actual usage] |

---

## 10. Interface Traceability

### 10.1 Requirements to Interfaces

| Requirement ID | Interface ID(s) | Description |
|----------------|-----------------|-------------|
| REQ-FUNC-001 | INT-SW-001 | [Description] |
| REQ-FUNC-002 | INT-EXT-001 | [Description] |
| REQ-HWSW-001 | INT-HAL-001 | [Description] |

---

## 11. References

### 11.1 Normative References

- **EN 50128:2011** - Railway applications - Software for railway control and protection systems
- **MISRA C:2012** - Guidelines for the Use of the C Language in Critical Systems

### 11.2 Project References

- **Software Requirements Specification (SRS)** - DOC-REQ-YYYY-NNN
- **Software Architecture Specification (SAS)** - DOC-DES-YYYY-NNN
- **Software Design Specification (SDS)** - DOC-DES-YYYY-NNN
- **Hardware Specification** - [Hardware document]

---

## Appendix A: Interface Usage Examples

[Detailed usage examples for each interface]

---

## Appendix B: Interface Diagrams

[Sequence diagrams, timing diagrams for interfaces]

---

## Document History

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 0.1 | YYYY-MM-DD | [Author] | Initial draft |
| 1.0 | YYYY-MM-DD | [Author] | First release |

---

**END OF DOCUMENT**
