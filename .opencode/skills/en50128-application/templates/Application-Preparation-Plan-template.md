# Application Preparation Plan

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 §8.4.3.3  
**ANNEX C ITEM**: #29

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-APP-PREP-PLAN-[YYYY]-[NNN] |
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

This Application Preparation Plan defines the activities, methods, and schedule for preparing application data and algorithms for [Application Name], in accordance with EN 50128:2011 Section 8.4.

Application preparation covers the configuration and specialisation of the generic software for the specific operational context.

### 1.2 Application Context

| Field | Value |
|-------|-------|
| **Generic Software** | [Name / Version] |
| **Application Name** | [Name] |
| **Operational Context** | [Description of the specific railway application] |
| **Target Hardware** | [Hardware platform] |
| **SIL Level** | [SIL X] |

### 1.3 Reference Documents

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-APP-REQ-YYYY-NNN | Application Requirements Specification | X.Y |
| DOC-009-SAS | Software Architecture Specification (Generic) | X.Y |
| DOC-SVP-YYYY-NNN | Software Verification Plan | X.Y |
| STD-EN50128 | EN 50128:2011 Railway Applications | - |

---

## 2. Application Data and Algorithms Scope

### 2.1 Application Data Items

| Data ID | Description | Source | SIL |
|---------|-------------|--------|-----|
| APP-DATA-001 | [Data description] | [Source] | [SIL] |
| APP-DATA-002 | [Data description] | [Source] | [SIL] |

### 2.2 Application Algorithms

| Algorithm ID | Description | Purpose | SIL |
|-------------|-------------|---------|-----|
| APP-ALG-001 | [Algorithm description] | [Purpose] | [SIL] |

---

## 3. Preparation Activities

### 3.1 Correctness Activities (§8.4.4.4(a))

| Activity ID | Activity Description | Method | Responsible | Completion Criteria |
|-------------|---------------------|--------|-------------|---------------------|
| PREP-001 | [Correctness verification activity] | [Method] | [Role] | [Criteria] |

### 3.2 Completeness Activities (§8.4.4.4(b))

| Activity ID | Activity Description | Method | Responsible | Completion Criteria |
|-------------|---------------------|--------|-------------|---------------------|
| PREP-010 | [Completeness check activity] | [Method] | [Role] | [Criteria] |

### 3.3 Coherency with Application Principles (§8.4.4.4(c))

| Principle | Check Activity | Method |
|-----------|---------------|--------|
| [Safety principle 1] | [Check description] | [Review / test] |

### 3.4 Coherency with Application Architecture (§8.4.4.4(d))

| Architecture Element | Check Activity | Method |
|----------------------|---------------|--------|
| [Component 1] | [Check description] | [Review / test] |

### 3.5 Compatibility with Generic Application (§8.4.4.4(e))

| Compatibility Aspect | Check Activity | Method |
|----------------------|---------------|--------|
| Data formats | [Check description] | [Review / test] |
| Parameter ranges | [Check description] | [Review / test] |
| Interface contracts | [Check description] | [Review / test] |

### 3.6 Installation Test Planning (§8.4.4.4(f))

| Test ID | Description | Pass Criteria |
|---------|-------------|---------------|
| INST-001 | [Installation test description] | [Criteria] |

---

## 4. Application Preparation Schedule

| Milestone | Target Date | Responsible |
|-----------|-------------|-------------|
| Application data defined | [Date] | [Role] |
| Correctness checks complete | [Date] | [Role] |
| Completeness checks complete | [Date] | [Role] |
| Coherency checks complete | [Date] | [Role] |
| Compatibility confirmed | [Date] | [Role] |
| Installation tests specified | [Date] | [Role] |
| Application Preparation Plan reviewed by VER | [Date] | VER |

---

## 5. Tools Used for Application Preparation

| Tool | Version | Class (T1/T2/T3) | Purpose |
|------|---------|------------------|---------|
| [Tool name] | [Version] | T[1/2/3] | [Purpose] |

---

**End of Application Preparation Plan**
