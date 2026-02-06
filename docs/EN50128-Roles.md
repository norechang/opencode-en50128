# EN 50128 Organizational Roles Reference

This document provides a quick reference for EN 50128:2011 Section 5 and Annex B organizational role definitions.

## Standard Role Definitions

### Management Roles

#### Project Manager (Section 5, Table B.9)

**Responsibility**: Overall project responsibility and coordination

**Key Activities**:
- Overall project planning and management
- Coordinate between all roles
- Resource allocation and management
- Schedule management
- Risk management
- Stakeholder communication
- Ensure compliance with standards
- Project-level decision making

**Independence**: Not required

**EN 50128 Reference**: Section 5 (organization requirements), Table B.9 (detailed specification)

**Notes**: 
- Oversees the entire project including hardware, system, and software aspects
- Coordinates with Software Manager for software-specific activities
- Ultimate responsibility for project delivery

---

#### Software Manager (Section 5.3.1, Table B.1)

**Responsibility**: Overall responsibility for software development activities

**Responsibility**: Overall responsibility for software development

**Key Activities**:
- Establish software development plans
- Allocate resources
- Monitor progress
- Ensure quality assurance activities
- Coordinate with other roles
- Report to management

**Independence**: Not required

**Notes**: 
- Focuses specifically on software development activities
- Works under Project Manager in larger projects
- In software-only projects, may be the same person as Project Manager

---

### 2. Designer (Section 5.3.2)

**Responsibility**: Software architecture and design

**Key Activities**:
- Create Software Architecture Specification (SAS)
- Create Software Design Specification (SDS)
- Define interfaces
- Apply design techniques per Table A.4
- Participate in design reviews

**Independence**: Not required (but designer should not assess their own design)

**Agent**: `/des`

---

### 3. Implementer (Section 5.3.3)

**Responsibility**: Software implementation (coding)

**Key Activities**:
- Implement software in C (MISRA C:2012 for SIL 2+)
- Follow coding standards
- Implement defensive programming
- Participate in code reviews
- Create unit tests

**Independence**: Not required (but implementer should not test their own code alone)

**Agent**: `/imp`

---

### 4. Tester (Section 5.3.4)

**Responsibility**: Software testing

**Key Activities**:
- Develop test specifications
- Execute tests
- Record test results
- Perform coverage analysis
- Report defects

**Independence**: 
- Not required for SIL 0-2
- Highly recommended for SIL 3-4

**Agent**: `/tst`

---

### 5. Verifier (Section 5.3.5)

**Responsibility**: Software verification

**Key Activities**:
- Plan verification activities
- Perform static analysis
- Conduct reviews
- Verify traceability
- Check compliance with standards
- Collect evidence

**Independence**: 
- Not required for SIL 0-1
- Highly recommended for SIL 2
- **MANDATORY for SIL 3-4**

**Agent**: `/ver`

**Notes**: 
- For SIL 3-4, verifier MUST NOT be designer or implementer
- Verifier reports independently of development team

---

### 6. Integrator (Section 5.3.6)

**Responsibility**: Software integration

**Key Activities**:
- Plan integration strategy
- Integrate software modules
- Resolve integration issues
- Perform integration testing
- Document integration results

**Independence**: Not required

**Agent**: Part of `/tst` responsibilities in this workspace

---

### 7. Validator (Section 5.3.7)

**Responsibility**: Software validation

**Key Activities**:
- Plan validation activities
- Perform system testing
- Conduct acceptance testing
- Validate operational scenarios
- Obtain customer acceptance

**Independence**: 
- Not required for SIL 0-1
- Highly recommended for SIL 2
- **MANDATORY for SIL 3-4**

**Agent**: `/val`

**Notes**: 
- For SIL 3-4, validator MUST NOT be involved in development
- Validator should represent end-user perspective

---

### 8. Assessor (Section 5.3.8, Table B.8)

**Responsibility**: Independent safety assessment

**Key Activities**:
- Review all lifecycle artifacts
- Assess compliance with EN 50128
- Review safety case
- Verify independence of verification/validation
- Issue assessment report
- Approve for deployment

**Independence**: **MANDATORY for SIL 3-4**

**Agent**: Part of `/qua` responsibilities, but MUST be independent person

**Notes**: 
- Assessor MUST be completely independent of development
- Often external to the organization
- Required for final approval before deployment

---

#### Configuration Manager (Section 5, Table B.10)

**Responsibility**: Configuration and change management

**Key Activities**:
- Establish and maintain configuration management system
- Control configuration items
- Manage baselines
- Control changes
- Maintain version control
- Manage release process
- Track configuration status
- Configuration audits

**Independence**: Not required

**Agent**: Part of `/qua` responsibilities in this workspace

**Notes**: 
- Essential for maintaining integrity of software artifacts
- Particularly important for SIL 3-4 projects
- Often combined with QA role in smaller projects

---

## Role Independence Matrix

| Role | SIL 0-1 | SIL 2 | SIL 3-4 |
|------|---------|-------|---------|
| Project Manager | No | No | No |
| Software Manager | No | No | No |
| Configuration Manager | No | No | No |
| Designer | No | No | No |
| Implementer | No | No | No |
| Tester | No | HR | HR |
| Verifier | No | HR | **M** |
| Integrator | No | No | No |
| Validator | No | HR | **M** |
| Assessor | N/A | N/A | **M** |

**Legend**:
- **M** = Mandatory
- **HR** = Highly Recommended
- **No** = Not required

---

## Role Combination Rules

### Allowed Combinations (if independence not required)

✅ Software Manager + Designer  
✅ Designer + Implementer  
✅ Implementer + Tester (SIL 0-2 only)  
✅ Integrator + Tester  

### Prohibited Combinations (for SIL 3-4)

❌ Designer/Implementer + Verifier  
❌ Any development role + Validator  
❌ Any role + Assessor  
❌ Implementer + Tester (own code)  

### Best Practice

For SIL 3-4 projects:
- Separate teams for Development and Verification/Validation
- Independent Assessor (often external)
- Clear organizational separation
- Independent reporting lines

---

## Agent Mapping to EN 50128 Roles

| EN 50128 Role | Agent | Command | Independence Notes |
|---------------|-------|---------|-------------------|
| Project Manager | N/A | N/A | Overall project responsibility |
| Software Manager | N/A | N/A | Software development responsibility |
| Configuration Manager | QA | `/qua` | Configuration management |
| Designer | Designer | `/des` | Not required |
| Implementer | Implementer | `/imp` | Not required |
| Tester | Tester | `/tst` | Highly recommended for SIL 3-4 |
| Verifier | Verifier | `/ver` | **Mandatory for SIL 3-4** |
| Integrator | Tester | `/tst` | Not required |
| Validator | Validator | `/val` | **Mandatory for SIL 3-4** |
| Assessor | QA | `/qua` | **Mandatory for SIL 3-4** |

**Additional Agents** (not explicitly in EN 50128):
- Safety Engineer (`/saf`) - Supports safety analysis per Section 7.1
- Requirements Engineer (`/req`) - Supports requirements phase per Section 7.2
- Quality Assurance (`/qua`) - Supports QA per Section 6.3

---

## References

- EN 50128:2011 Section 5.3: Roles and Responsibilities
- EN 50128:2011 Table A.1: Software lifecycle phases
- EN 50128:2011 Annex B: Guidance on independence

---

**Related Documents**:
- `LIFECYCLE.md` - Complete development lifecycle
- `AGENTS.md` - Agent definitions and workflows
