# Application Requirements Specification

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 §8.4.4.2  
**ANNEX C ITEM**: #30

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-APP-REQ-[YYYY]-[NNN] |
| **Version** | [X.Y] |
| **Date** | [YYYY-MM-DD] |
| **Project / Application** | [Application Name] |
| **SIL Level** | [0 \| 1 \| 2 \| 3 \| 4] |
| **Author** | [Name], Application Developer |
| **Reviewer** | [Name], VER |
| **Approver** | [Name], PM |
| **Status** | [Draft \| Approved \| Baseline] |

## DOCUMENT CONTROL

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft |

---

## 1. Introduction

### 1.1 Purpose

This Application Requirements Specification (AppRS) defines the specific requirements for configuring and applying the generic software [Generic Software Name / Version] to the [Application Name] operational context, in accordance with EN 50128:2011 Section 8.4.4.2.

### 1.2 Application Context

| Field | Value |
|-------|-------|
| **Generic Software** | [Name / Version] |
| **Application Name** | [Name] |
| **Operational Context** | [Description of the specific railway application and environment] |
| **Target Hardware** | [Hardware platform] |
| **SIL Level** | SIL [X] per EN 50128:2011 |

### 1.3 Relationship to System Requirements

| System Requirement ID | Application Requirement(s) |
|----------------------|---------------------------|
| [SYS-REQ-001] | [APP-REQ-001, APP-REQ-002] |

### 1.4 Reference Documents

| Document ID | Title | Version |
|-------------|-------|---------|
| [SRS of generic SW] | Software Requirements Specification | X.Y |
| [SAS of generic SW] | Software Architecture Specification | X.Y |
| [SIS of generic SW] | Software Interface Specifications | X.Y |
| STD-EN50128 | EN 50128:2011 Railway Applications | - |

---

## 2. Application Requirements

### 2.1 Requirement Format

Each requirement uses the format:

| Field | Description |
|-------|-------------|
| **ID** | Unique requirement identifier (APP-REQ-NNN) |
| **Type** | Functional / Safety / Performance / Interface / Constraint |
| **SIL** | SIL level of this requirement |
| **Priority** | Mandatory / Highly Recommended / Recommended |
| **Rationale** | Why this requirement exists |
| **Acceptance Criteria** | How compliance is verified |

### 2.2 Functional Requirements

#### APP-REQ-001: [Requirement Name]

| Field | Value |
|-------|-------|
| **ID** | APP-REQ-001 |
| **Statement** | The application SHALL [requirement statement] |
| **Type** | Functional |
| **SIL** | [SIL X] |
| **Priority** | Mandatory |
| **Rationale** | [Why this is required] |
| **Acceptance Criteria** | [How to verify compliance] |
| **Traceability** | [System requirement or hazard ID] |

#### APP-REQ-002: [Requirement Name]

[Repeat format for each requirement]

### 2.3 Safety Requirements

#### APP-REQ-S001: [Safety Requirement Name]

| Field | Value |
|-------|-------|
| **ID** | APP-REQ-S001 |
| **Statement** | The application SHALL [safety requirement] |
| **Type** | Safety |
| **SIL** | [SIL X] |
| **Priority** | Mandatory |
| **Hazard Reference** | [Hazard Log ID] |
| **Acceptance Criteria** | [How to verify compliance] |
| **Traceability** | [Hazard ID / System requirement] |

### 2.4 Performance Requirements

| ID | Requirement | Parameter | Limit | Measurement Method |
|----|-------------|-----------|-------|-------------------|
| APP-REQ-P001 | [Description] | [Parameter] | [Limit] | [Method] |

### 2.5 Interface Requirements

| ID | Interface | Requirement | Compatibility Constraint |
|----|-----------|-------------|------------------------|
| APP-REQ-I001 | [Interface name] | [Requirement] | [Constraint] |

### 2.6 Constraints

| ID | Constraint | Reason | Reference |
|----|-----------|--------|-----------|
| APP-REQ-C001 | [Constraint statement] | [Reason] | [Reference] |

---

## 3. Application Data Specification

### 3.1 Data Parameters

| Parameter ID | Name | Data Type | Range / Format | Default | SIL |
|-------------|------|-----------|---------------|---------|-----|
| APP-PARAM-001 | [Name] | [Type] | [Range] | [Default] | [SIL] |

### 3.2 Configuration Tables

| Table ID | Name | Description | Source |
|----------|------|-------------|--------|
| APP-TABLE-001 | [Name] | [Description] | [Source — site survey, etc.] |

---

## 4. Traceability Matrix

### 4.1 System Requirements → Application Requirements

| System Requirement | Application Requirement(s) | Coverage |
|-------------------|---------------------------|---------|
| [SRS-REQ-001] | APP-REQ-001 | [Full/Partial] |

### 4.2 Application Requirements → Acceptance Tests

| Application Requirement | Test ID(s) | Coverage |
|------------------------|-----------|---------|
| APP-REQ-001 | [APP-TEST-001] | [Full/Partial] |

---

**End of Application Requirements Specification**
