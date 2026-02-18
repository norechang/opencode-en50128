# Software Verification Plan (SVP)

## Project Information
- **Project Name**: Train Door Control System (Version 2)
- **Software Component**: Door Control Module
- **SIL Level**: 3
- **Document Version**: 1.0
- **Date**: 2026-02-18
- **Author**: Independent Verifier

## 1. Scope

This Software Verification Plan (SVP) defines the verification activities for the Train Door Control System, targeting SIL 3 compliance per EN 50128:2011.

The scope includes:
- All software requirements (SRS)
- Software architecture (SAS)
- Software design (SDS)
- Source code implementation
- Unit and integration tests
- Traceability verification

## 2. Verification Objectives

- Ensure software meets all functional and safety requirements
- Verify compliance with EN 50128:2011 SIL 3 requirements
- Confirm traceability from requirements to code and tests
- Validate static analysis, complexity, and coverage metrics
- Provide evidence for independent verification

## 3. Verification Techniques (EN 50128 Table A.5)

### Mandatory Techniques for SIL 3
- **Static Analysis** (Technique 3) - **MANDATORY**
- **Traceability** (Technique 7) - **MANDATORY**
- **Control Flow Analysis** (Table A.19, Technique 2) - **MANDATORY**
- **Data Flow Analysis** (Table A.19, Technique 3) - **MANDATORY**

### Highly Recommended Techniques for SIL 3
- Formal Proof (Technique 1) - Highly Recommended
- Metrics (Technique 5) - Highly Recommended
- Software Error Effect Analysis (Technique 9) - Highly Recommended
- Software Fault Tree Analysis (Technique 10) - Highly Recommended

### Approved Combination
- Static Analysis (3), Metrics (5), Traceability (7), Testing (8) + Formal Proof (1)

## 4. Verification Activities

### 4.1 Requirements Verification
- Review SRS for completeness and unambiguity
- Verify SIL assignment justification
- Check traceability to higher-level requirements

### 4.2 Design Verification
- Review SAS and SDS for modular design
- Verify interface definitions
- Check defensive programming patterns
- Validate complexity limits (CCN ≤ 10)

### 4.3 Code Verification
- Static analysis with qualified tools
- MISRA C:2012 compliance verification
- Complexity analysis
- Manual code review/walkthrough

### 4.4 Testing Verification
- Unit test verification
- Integration test verification
- Coverage analysis verification
- Fault injection testing

### 4.5 Traceability Verification
- Bidirectional traceability matrix validation
- Requirements-to-code traceability
- Code-to-test traceability

## 5. Tools and Environment

### Static Analysis Tools
- **PC-lint Plus 2.0**: MISRA C compliance, control/data flow analysis
- **Cppcheck 2.10**: General static analysis with MISRA addon
- **Clang Static Analyzer**: Deep semantic analysis

### Complexity Analysis Tools
- **Lizard 1.17**: Cyclomatic complexity measurement

### Coverage Analysis Tools
- **gcov/lcov**: Statement, branch, and condition coverage
- Custom Python scripts for threshold verification

### Other Tools
- **Unity Test Framework**: Unit testing
- **Python 3.x**: Automation scripts
- **Git**: Configuration management

## 6. Independence Requirements

Per EN 50128 Section 5.3.5 and Table A.5:
- **Independent Verification**: MANDATORY for SIL 3
- Verifier SHALL NOT be the same person as designer or implementer
- Verification activities performed by dedicated verification team
- Evidence collection and reporting independent of development team

## 7. Verification Criteria

### Pass/Fail Criteria
- **Static Analysis**: Zero critical issues, all warnings reviewed and justified
- **Complexity**: CCN ≤ 10 for all functions
- **Coverage**: 100% statement, 100% branch, 100% condition coverage
- **Traceability**: Complete bidirectional traceability
- **MISRA C**: Compliance with MISRA C:2012, deviations documented and approved

### Quality Gates
- Requirements verification: Before design phase
- Design verification: Before implementation phase
- Code verification: Continuous during implementation
- Testing verification: Before integration phase
- Final verification: Before validation phase

## 8. Verification Schedule

### Phase 1: Planning (Current)
- SVP development and approval

### Phase 2: Requirements Verification
- Timeline: 2 weeks after SRS approval
- Deliverable: Requirements Verification Report

### Phase 3: Design Verification
- Timeline: 3 weeks after SDS approval
- Deliverable: Design Verification Report

### Phase 4: Implementation Verification
- Timeline: Continuous during implementation (weekly checks)
- Deliverable: Code Verification Reports

### Phase 5: Testing Verification
- Timeline: 2 weeks after test completion
- Deliverable: Test Verification Report

### Phase 6: Final Verification
- Timeline: 1 week before validation
- Deliverable: Final Verification Report

## 9. Deliverables

### Verification Reports
- Requirements Verification Report
- Design Verification Report
- Code Verification Reports (per module)
- Test Verification Report
- Final Verification Report

### Evidence Collection
- Static analysis reports
- Complexity analysis results
- Coverage reports
- Traceability matrices
- Deviation records
- Review records

## 10. Roles and Responsibilities

### Independent Verifier
- Execute all verification activities
- Collect and document evidence
- Report findings to Project Manager and Safety Authority
- Approve verification completion

### Development Team
- Provide access to code, tests, and documentation
- Address verification findings
- Implement corrective actions

### Project Manager
- Ensure verification independence
- Review verification reports
- Approve verification milestones

## 11. Risk Management

### Verification Risks
- Tool qualification delays
- Incomplete traceability
- Complexity violations
- Coverage gaps

### Mitigation Strategies
- Early tool setup and qualification
- Continuous traceability maintenance
- Automated complexity checks in CI/CD
- Coverage targets in test planning

## 12. Configuration Management

All verification artifacts shall be under configuration management:
- Version control in Git
- Baselines at phase gates
- Change control for SVP modifications

## 13. References

- EN 50128:2011 Railway applications - Communication, signalling and processing systems - Software for railway control and protection systems
- EN 50126-1:2017 Railway Applications - The Specification and Demonstration of Reliability, Availability, Maintainability and Safety (RAMS)
- MISRA C:2012 Guidelines for the use of the C language in critical systems
- ISO/IEC 9899:2018 Programming languages - C

## 14. Approval

- **Verifier**: [Independent Verifier Name]
- **Date**: [Approval Date]
- **Project Manager**: [Name]
- **Safety Authority**: [Name]