# Project Organization Chart - Train Door Control System

**Project:** train_door_control2  
**SIL Level:** 3  
**Date:** 2026-02-18  

---

## Organizational Structure

```
                Safety Authority / Customer
                            |
                ┌───────────┴───────────┐
                |                       |
            Assessor          Lifecycle Coordinator (COD)
         (independent)                  |
                        ┌───────────────┼────────────┐
                        |               |            |
                Project Manager   Validator    Software Manager
                (PM)            (VAL)        (SM - combined with PM)
                - Team mgmt       (independent)
                - Resources
                - Stakeholders
                        |
                        ├─── Requirements Engineer (REQ)
                        ├─── Designer (DES)  
                        ├─── Implementer (IMP)
                        ├─── Tester (TST)
                        ├─── Integrator (INT)
                        ├─── Verifier (VER)
                        ├─── Safety Engineer (SAF)
                        ├─── Quality Assurance (QUA)
                        └─── Configuration Manager (CM)
```

---

## Role Definitions and Responsibilities

### Management Roles

| Role | EN 50128 Section | Primary Responsibility | Reporting To |
|------|------------------|-------------------------|--------------|
| **Lifecycle Coordinator (COD)** | Platform Extension (Section 5.3) | End-to-end lifecycle orchestration, phase gates, compliance enforcement | Safety Authority |
| **Project Manager (PM)** | Table B.9 | Team coordination, resource management, stakeholder communication | COD (for lifecycle decisions) |
| **Software Manager (SM)** | Section 5.3.1, Table B.1 | Software development activities | PM |
| **Validator (VAL)** | Table B.7 | Independent validation | Safety Authority (independent) |
| **Assessor** | Table B.8 | Independent safety assessment | Safety Authority (independent) |

### Development Roles

| Role | EN 50128 Section | Primary Responsibility | Reporting To |
|------|------------------|-------------------------|--------------|
| **Requirements Engineer (REQ)** | Section 7.2 | Requirements specification and traceability | PM |
| **Designer (DES)** | Section 7.3 | Software architecture and design | PM |
| **Implementer (IMP)** | Section 7.4 | Code implementation with MISRA C compliance | PM |
| **Tester (TST)** | Section 7.5 | Unit and integration testing | PM |
| **Integrator (INT)** | Section 7.6 | Software integration | PM |
| **Verifier (VER)** | Section 6.2 | Static analysis and verification | PM |
| **Safety Engineer (SAF)** | Section 7.1, EN 50126 | Hazard analysis, FMEA, safety case | PM |
| **Quality Assurance (QUA)** | Section 6.5 | QA plan, code reviews, quality metrics | PM |
| **Configuration Manager (CM)** | Section 6.6 | Configuration management, change control | PM |

---

## Independence Requirements (SIL 3)

### Critical Independence Rules

| Requirement | Status | Justification |
|-------------|--------|---------------|
| **Validator SHALL NOT report to PM** | COMPLIANT | VAL reports directly to Safety Authority |
| **Assessor SHALL be independent** | COMPLIANT | ASR reports directly to Safety Authority |
| **Verifier independence from Implementer** | COMPLIANT | VER reports to PM, separate from IMP |
| **Role combinations allowed** | COMPLIANT | No prohibited combinations (PM cannot be VAL or ASR) |

### Personnel Assignments

| Role | Assigned Person | Organization | Contact |
|------|-----------------|--------------|---------|
| **Lifecycle Coordinator (COD)** | Lifecycle Coordinator | Platform | cod@platform.com |
| **Project Manager (PM)** | Sarah Johnson | Acme Railway Systems | sarah.johnson@acme-rail.com |
| **Software Manager (SM)** | Combined with PM | - | - |
| **Requirements Engineer (REQ)** | Michael Chen | Acme Railway Systems | michael.chen@acme-rail.com |
| **Designer (DES)** | Elena Rodriguez | Acme Railway Systems | elena.rodriguez@acme-rail.com |
| **Implementer (IMP)** | David Kim | Acme Railway Systems | david.kim@acme-rail.com |
| **Tester (TST)** | Lisa Thompson | Acme Railway Systems | lisa.thompson@acme-rail.com |
| **Integrator (INT)** | Robert Garcia | Acme Railway Systems | robert.garcia@acme-rail.com |
| **Verifier (VER)** | Anna Petrov | Acme Railway Systems | anna.petrov@acme-rail.com |
| **Validator (VAL)** | James Wilson | Independent Validation Ltd | james.wilson@validation.com |
| **Assessor** | Dr. Maria Santos | Safety Assessment Authority | maria.santos@safety-auth.org |
| **Safety Engineer (SAF)** | Thomas Brown | Acme Railway Systems | thomas.brown@acme-rail.com |
| **Quality Assurance (QUA)** | Jennifer Lee | Acme Railway Systems | jennifer.lee@acme-rail.com |
| **Configuration Manager (CM)** | Mark Davis | Acme Railway Systems | mark.davis@acme-rail.com |

**Note:** All personnel assignments comply with Section 5.1.2.3 requirements for named assignments.

---

## Communication Protocols

### Internal Communications
- **Weekly team meetings** chaired by PM
- **Daily stand-ups** for active development phases
- **Email distribution** for all team members
- **Document sharing** via version control system

### External Communications
- **Validator (VAL)**: Information exchange only, no directive authority
  - Weekly status updates
  - Document reviews upon request
  - Independent decision making
- **Assessor**: Independent assessment coordination
  - Provide requested documentation
  - Respond to assessment findings
  - No influence on assessment decisions
- **Safety Authority**: Regular reporting through COD
- **Customer**: Stakeholder updates through PM

---

## Role Combination Rationale (SIL 3)

For SIL 3 projects, role combinations are allowed provided independence requirements are satisfied:

- **PM combined with SM**: Allowed (PM has software development authority)
- **No other combinations**: Maintains separation required for SIL 3
- **Validator separate**: Mandatory independence
- **Assessor separate**: Mandatory independence

**Justification**: Organizational structure provides adequate separation while maintaining efficiency for SIL 3 requirements.

---

## Approval and Review

**Approved By:** Sarah Johnson (Project Manager)  
**Date:** 2026-02-18  
**Reviewed By:** Lifecycle Coordinator (COD)  
**Compliance Verified:** Independence requirements satisfied per Section 5.1.2.9-14

---

**Document ID:** ORG-001  
**Version:** 1.0  
**Effective Date:** 2026-02-18