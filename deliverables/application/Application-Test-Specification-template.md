# Application Test Specification

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 §8.4.5.3  
**ANNEX C ITEM**: #33

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-APP-TEST-SPEC-[YYYY]-[NNN] |
| **Version** | [MAJOR.MINOR] |
| **Date** | [YYYY-MM-DD] |
| **Project / Application** | [Application Name] |
| **SIL Level** | [0 \| 1 \| 2 \| 3 \| 4] |
| **Author** | [AuthorName], TST |
| **Reviewer** | [ReviewerName], VER |
| **Approver** | [ApproverName], PM |
| **Status** | [Draft \| Approved \| Baseline] |

## DOCUMENT CONTROL

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft |

---

## 1. Introduction

### 1.1 Purpose

This Application Test Specification defines the tests to be performed on the complete installation of [Application Name] to verify that the application data and algorithms meet the Application Requirements Specification (DOC-APP-REQ-YYYY-NNN), per EN 50128:2011 §8.4.5.3.

### 1.2 Test Scope

**Application:** [Application Name]  
**Generic Software Version:** [Version]  
**Application Data Version:** [Version]  
**Test Environment:** [Complete installation description]

### 1.3 Reference Documents

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-APP-REQ-YYYY-NNN | Application Requirements Specification | X.Y |
| DOC-APP-PREP-PLAN-YYYY-NNN | Application Preparation Plan | X.Y |
| DOC-SVP-YYYY-NNN | Software Verification Plan | X.Y |

---

## 2. Test Strategy (§8.4.5.3)

### 2.1 Test Levels

Tests are performed on the **complete installation** (hardware + software + application data) to verify:
1. Application data/algorithms meet functional requirements
2. Application behaviour meets safety requirements
3. Application is compatible with the generic software
4. Application behaves correctly at boundary conditions

### 2.2 Entry Criteria

- [ ] Application data and algorithms installed on target hardware
- [ ] Application Requirements Specification baselined
- [ ] Test environment verified (hardware, connections, tools)
- [ ] Test personnel qualified

### 2.3 Exit Criteria

- [ ] All mandatory test cases executed
- [ ] All safety-critical tests passed
- [ ] No open critical or high-severity defects
- [ ] Test report signed

---

## 3. Test Cases

### 3.1 Test Case Format

| Field | Description |
|-------|-------------|
| **Test ID** | Unique identifier (APP-TC-NNN) |
| **Requirements** | Application requirement IDs covered |
| **Preconditions** | System state before test |
| **Input** | Test inputs/stimuli |
| **Procedure** | Step-by-step test procedure |
| **Expected Result** | What should happen |
| **Pass Criteria** | Objective pass/fail criterion |
| **SIL** | SIL level of tested requirement |

---

### 3.2 Functional Tests

#### APP-TC-001: [Test Name]

| Field | Value |
|-------|-------|
| **Test ID** | APP-TC-001 |
| **Requirements** | APP-REQ-001 |
| **Preconditions** | [System state] |
| **Input** | [Input data / command] |
| **Procedure** | 1. [Step] 2. [Step] 3. [Step] |
| **Expected Result** | [Expected system behaviour] |
| **Pass Criteria** | [Objective criterion] |
| **SIL** | SIL [X] |

#### APP-TC-002: [Test Name]

[Repeat for each test case]

---

### 3.3 Safety Tests

#### APP-TC-S001: [Safety Test Name]

| Field | Value |
|-------|-------|
| **Test ID** | APP-TC-S001 |
| **Requirements** | APP-REQ-S001 |
| **Preconditions** | [System state] |
| **Input** | [Fault injection / hazardous condition] |
| **Procedure** | 1. [Step] 2. [Step] |
| **Expected Result** | [Safe state achieved] |
| **Pass Criteria** | [Objective criterion — fail-safe behaviour] |
| **SIL** | SIL [X] |

---

### 3.4 Boundary Condition Tests

| Test ID | Parameter | Lower Bound Test | Upper Bound Test | Pass Criteria |
|---------|-----------|-----------------|-----------------|---------------|
| APP-TC-B001 | [Parameter] | [Min value test] | [Max value test] | [Criteria] |

---

### 3.5 Compatibility Tests

| Test ID | Description | Generic SW Version | Expected Result |
|---------|-------------|-------------------|----------------|
| APP-TC-C001 | Interface compatibility | [Version] | [Expected] |

---

## 4. Traceability Matrix

| Application Requirement | Test Case(s) | Coverage |
|------------------------|-------------|---------|
| APP-REQ-001 | APP-TC-001 | Full |
| APP-REQ-S001 | APP-TC-S001 | Full |

---

## 5. Test Environment

| Component | Specification | Configuration |
|-----------|--------------|---------------|
| Target hardware | [Specification] | [Configuration] |
| Generic software | [Version] | [Configuration] |
| Application data | [Version] | [Source] |
| Test tools | [Tools] | [Versions] |

---

**End of Application Test Specification**
