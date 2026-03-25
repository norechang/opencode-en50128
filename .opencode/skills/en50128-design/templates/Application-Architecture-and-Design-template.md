# Application Architecture and Design

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 §8.4.3  
**ANNEX C ITEM**: #31

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-APP-ARCH-DESIGN-[YYYY]-[NNN] |
| **Version** | [X.Y] |
| **Date** | [YYYY-MM-DD] |
| **Project / Application** | [Application Name] |
| **SIL Level** | [0 \| 1 \| 2 \| 3 \| 4] |
| **Author** | [Name], DES |
| **Reviewer** | [Name], VER |
| **Approver (Second Check)** | [Name], VAL |
| **Status** | [Draft \| Approved \| Baseline] |

## DOCUMENT CONTROL

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft |

---

## 1. Introduction

### 1.1 Purpose

This document defines the architecture and design of [Application Name], describing how the generic software [Generic Software Name / Version] is configured and applied to meet the Application Requirements Specification (DOC-APP-REQ-YYYY-NNN), in accordance with EN 50128:2011 Section 8.4.3.

### 1.2 Application Context

| Field | Value |
|-------|-------|
| **Generic Software** | [Name / Version] |
| **Application Name** | [Name] |
| **Operational Context** | [Description] |
| **Target Hardware** | [Hardware platform] |
| **SIL Level** | SIL [X] per EN 50128:2011 |

### 1.3 Reference Documents

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-APP-REQ-YYYY-NNN | Application Requirements Specification | X.Y |
| DOC-009-SAS | Software Architecture Specification (Generic) | X.Y |
| DOC-010-SDS | Software Design Specification (Generic) | X.Y |
| DOC-011-SIS | Software Interface Specifications (Generic) | X.Y |
| STD-EN50128 | EN 50128:2011 Railway Applications | - |

---

## 2. Application Architecture Overview (§8.4.3.1)

### 2.1 Architecture Description

[High-level description of how the application is structured. Describe the relationship between the generic software and the application-specific data/algorithms.]

### 2.2 Architecture Diagram

```
┌─────────────────────────────────────────────┐
│              Generic Software               │
│  ┌─────────────┐   ┌─────────────────────┐  │
│  │   Fixed SW  │   │  Configurable Parts │  │
│  │  (kernel,   │   │  (data tables,      │  │
│  │   drivers)  │   │   parameters,       │  │
│  └─────────────┘   │   algorithms)       │  │
│                    └─────────────────────┘  │
└──────────────────────────┬──────────────────┘
                           │ Application Data
                           ▼
                  ┌─────────────────┐
                  │  Application    │
                  │  Data/Algorithms│
                  │  [This document]│
                  └─────────────────┘
```

### 2.3 Application Modules / Data Domains

| Module / Domain | Description | SIL | Status |
|-----------------|-------------|-----|--------|
| [APP-MOD-001] | [Description] | SIL [X] | [Defined/TBD] |

---

## 3. Application Data Design (§8.4.3.2)

### 3.1 Data Tables

| Table ID | Name | Description | Source | SIL |
|----------|------|-------------|--------|-----|
| APP-TABLE-001 | [Name] | [Description] | [Site survey/specification] | [SIL] |

### 3.2 Configuration Parameters

| Parameter ID | Name | Data Type | Range | Units | Default | SIL |
|-------------|------|-----------|-------|-------|---------|-----|
| APP-PARAM-001 | [Name] | [Type] | [Min–Max] | [Unit] | [Default] | [SIL] |

### 3.3 Application Algorithms

| Algorithm ID | Name | Description | Input Parameters | Output | SIL |
|-------------|------|-------------|-----------------|--------|-----|
| APP-ALG-001 | [Name] | [Description] | [Inputs] | [Output] | [SIL] |

---

## 4. Interface Design (§8.4.3.3)

### 4.1 Application Data Interfaces with Generic Software

| Interface ID | Description | Data Direction | Format | Protocol |
|-------------|-------------|---------------|--------|----------|
| APP-IF-001 | [Description] | [Input/Output] | [Format] | [Protocol] |

### 4.2 Hardware Interfaces

| Interface ID | Hardware Component | Description | Signal Type |
|-------------|-------------------|-------------|-------------|
| APP-HW-IF-001 | [Hardware] | [Description] | [Type] |

---

## 5. Safety Design (§8.4.3.4)

### 5.1 Safety-Relevant Application Data

| Safety Requirement | Application Data / Algorithm | Fail-Safe Behaviour |
|-------------------|------------------------------|---------------------|
| APP-REQ-S001 | [Data / Algorithm ID] | [Fail-safe description] |

### 5.2 Protective Measures

| Measure | Description | Applicable SIL |
|---------|-------------|----------------|
| Range checking on input data | [Description] | SIL [X]+ |
| Default safe-state values | [Description] | SIL [X]+ |
| [Other protective measures] | [Description] | [SIL] |

---

## 6. Compatibility with Generic Software

| Compatibility Aspect | Generic SW Requirement | Application Design Compliance |
|---------------------|----------------------|------------------------------|
| Data format | [Requirement] | [How application data complies] |
| Parameter ranges | [Requirement] | [How application data complies] |
| Interface contracts | [Requirement] | [How application data complies] |

---

## 7. Design Traceability

### 7.1 Application Requirements → Design Elements

| Application Requirement | Design Element(s) | Coverage |
|------------------------|------------------|---------|
| APP-REQ-001 | APP-TABLE-001, APP-PARAM-001 | Full |
| APP-REQ-S001 | APP-ALG-001, Safety Measure X | Full |

---

**End of Application Architecture and Design**
