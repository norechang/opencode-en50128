# Quality Assurance Workflow

**EN 50128 Reference**: Section 6.5 (Software Quality Assurance), Table A.9  
**Phase**: All phases (cross-cutting activity)  
**Role**: Quality Assurance (QUA)  
**SIL Level**: All (0-4)

---

## Purpose

This workflow defines the complete quality assurance process for EN 50128 railway software development. It implements EN 50128 Section 6.5 requirements for "identifying, monitoring and controlling all those activities, both technical and managerial, which are necessary to ensure that the software achieves the quality required."

**Key Objectives**:
- Develop and maintain Software Quality Assurance Plan (SQAP)
- Define and enforce quality gates at all lifecycle phases
- Collect and analyze quality metrics
- Manage non-conformances and corrective actions
- Ensure traceability throughout lifecycle (MANDATORY SIL 3-4)
- Provide audit trail for verification and validation

**Inputs**:
- Project charter and scope
- EN 50128:2011 requirements
- Software Requirements Specification (SRS)
- Software Configuration Management Plan (SCMP)
- All lifecycle deliverables

**Outputs**:
- Software Quality Assurance Plan (SQAP)
- Quality gate approval/rejection decisions
- Quality metrics reports
- Non-conformance reports (NCRs)
- Quality audit reports
- Software Quality Assurance Verification Report

---

## Table of Contents

1. [Quality Assurance Overview](#quality-assurance-overview)
2. [SQAP Development](#sqap-development)
3. [Quality Gates Framework](#quality-gates-framework)
4. [Quality Metrics Collection](#quality-metrics-collection)
5. [Non-Conformance Management](#non-conformance-management)
6. [Quality Audit Process](#quality-audit-process)
7. [Traceability Management](#traceability-management)
8. [Tool Integration](#tool-integration)
9. [SIL-Specific Requirements](#sil-specific-requirements)
10. [Example QA Scenarios](#example-qa-scenarios)

---

## Quality Assurance Overview

### EN 50128 Requirements for QA

**Section 6.5.1.1**: "To identify, monitor and control all those activities, both technical and managerial, which are necessary to ensure that the software achieves the quality required."

**Section 6.5.4.2**: "The organisations taking part in the software development shall implement and use a Quality Assurance System compliant with EN ISO 9000."

**Section 6.5.4.3**: "A Software Quality Assurance Plan shall be written, under the responsibility of the Verifier."

**Key Requirements**:
- EN ISO 9001 compliance MANDATORY (all SIL levels)
- Company Quality System MANDATORY (all SIL levels)
- Software Configuration Management MANDATORY (all SIL levels)
- Traceability MANDATORY (SIL 3-4)
- Data recording and analysis MANDATORY (SIL 3-4)

---

### QA Independence Requirements

| SIL Level | Independence Requirement | Reporting Line |
|-----------|-------------------------|----------------|
| **SIL 0-1** | Recommended | May report to PM |
| **SIL 2** | Highly Recommended | Should report independently |
| **SIL 3-4** | **MANDATORY** | **Must NOT report to PM or development** |

**SIL 3-4 Independence**:
- QA team separate from development organization
- QA Manager reports to senior management or Safety Manager
- QA has authority to stop releases if quality issues found
- No development responsibilities for QA personnel

---

### QA Responsibilities by Lifecycle Phase

| Phase | QA Activities | Deliverables |
|-------|--------------|--------------|
| **Planning** | SQAP development, SCMP review | SQAP approved |
| **Requirements** | Requirements review, traceability check | Requirements approval |
| **Design** | Design review, complexity check | Design approval |
| **Implementation** | Code review, MISRA C check, complexity validation | Code approval |
| **Testing** | Test plan review, coverage validation | Test approval |
| **Integration** | Integration test review, interface validation | Integration approval |
| **Verification** | Verification report review (template compliance) | VER report approval |
| **Validation** | Validation report review (template compliance) | VAL report approval |
| **Deployment** | Final audit, release approval | Release certificate |

---

## SQAP Development

### Software Quality Assurance Plan Template

**EN 50128 Section 6.5.4.5** defines MANDATORY content for SQAP:

```markdown
# Software Quality Assurance Plan (SQAP)

## Document Control
- **Document ID**: DOC-QUA-SQAP-001
- **Version**: 1.0
- **Date**: 2026-03-14
- **Author**: [QA Manager Name]
- **Approvers**: QA Manager, Project Manager, Safety Manager
- **SIL Level**: [0-4]
- **Project**: [Railway Safety System Name]

---

## 1. Introduction

### 1.1 Purpose
This Software Quality Assurance Plan (SQAP) defines the quality assurance strategy, activities, and responsibilities for the [Project Name] railway software development project, compliant with EN 50128:2011 Section 6.5 at SIL [level].

**Objectives**:
- Ensure software achieves required quality level
- Provide qualitative defense against systematic faults
- Establish audit trail for verification and validation
- Ensure EN 50128 compliance at SIL [level]

### 1.2 Scope
- **Software Component**: [Name and description]
- **SIL Level**: [0-4]
- **Development Lifecycle**: V-Model per EN 50128 Section 5.3
- **Quality Standards**: EN 50128:2011, EN ISO 9001, MISRA C:2012
- **QA Team**: [Names, roles, independence status]

### 1.3 References
- EN 50128:2011 (Railway Applications - Software for Railway Control Systems)
- EN ISO 9001:2015 (Quality Management Systems)
- MISRA C:2012 (Coding Standard for C)
- Software Requirements Specification - DOC-REQ-SRS-001
- Software Configuration Management Plan - DOC-CM-SCMP-001
- Software Verification Plan - DOC-VER-SVP-001
- Software Validation Plan - DOC-VAL-SVP-001

### 1.4 Definitions and Abbreviations
- **SQAP**: Software Quality Assurance Plan
- **QA**: Quality Assurance
- **NCR**: Non-Conformance Report
- **SIL**: Safety Integrity Level
- **MISRA**: Motor Industry Software Reliability Association
- **CCN**: Cyclomatic Complexity Number

---

## 2. Quality Organization

### 2.1 QA Team Structure

**QA Manager**: [Name]
- Overall quality oversight and planning
- SQAP development and maintenance
- Quality gate approvals
- Management reporting
- **Independence**: Reports to [Senior Management/Safety Manager] (NOT Project Manager for SIL 3-4)

**QA Engineers**: [Names]
- Document reviews (template compliance)
- Code reviews (MISRA C, complexity, defensive programming)
- Design reviews (architecture, complexity, traceability)
- Quality metrics collection and reporting
- Audit execution
- Non-conformance tracking

**Project Manager**: [Name]
- Development team coordination
- Resource allocation
- Schedule management
- **NOTE**: PM does NOT have authority over QA decisions (SIL 3-4)

**Development Team**:
- Quality compliance in all deliverables
- Defect resolution per QA feedback
- Process adherence

### 2.2 QA Independence (SIL 3-4 MANDATORY)

**EN 50128 Section 5.1.2.10**: QA function must be independent from development.

**Independence Measures**:
- QA team separate from development organization
- QA Manager reports to [Safety Manager/Senior Management], NOT Project Manager
- QA personnel have NO development responsibilities
- QA has authority to STOP releases if quality issues found
- QA decisions CANNOT be overridden by Project Manager

**Conflict Resolution**:
- QA-PM disagreements escalated to [Safety Manager/Senior Management]
- Final authority on quality issues: QA Manager (SIL 3-4)
- Release approval requires QA sign-off (no release without QA approval)

---

## 3. Quality Standards

### 3.1 Coding Standards (MANDATORY SIL 2+)

**MISRA C:2012 Compliance**:
- All C code SHALL comply with MISRA C:2012 mandatory rules
- Zero mandatory violations allowed for SIL 2+ (verified by PC-lint Plus, Cppcheck)
- Advisory violations require documented justification
- Deviation process per SQAP Section 7

**Cyclomatic Complexity Limits** (per EN 50128 Table D.53):
| SIL Level | Maximum CCN | Verification Method |
|-----------|-------------|---------------------|
| SIL 0-1 | 20 | Lizard |
| SIL 2 | 15 | Lizard |
| SIL 3-4 | 10 | Lizard |

**Defensive Programming** (HR for SIL 3-4):
- All function parameters validated (NULL checks, range checks)
- All pointers validated before use
- All function return values checked
- Integer overflow/underflow detection
- Buffer overflow prevention
- Division by zero checks

### 3.2 Documentation Standards

**EN 50128 Document Requirements**:
- All documents SHALL follow EN 50128 templates (Annex C, Table C.1)
- Document ID format: DOC-[ROLE]-[TYPE]-[NNN]
- Document Control table mandatory (ID, version, date, author, approvers)
- Approvals table mandatory with SIL-specific approvers
- Version history table mandatory
- Traceability sections mandatory (SIL 3-4)

**Document Template Compliance**:
- QA reviews ALL documents for template compliance BEFORE technical review
- Template violations result in rejection (1 resubmission allowed)
- Template compliance verification using `enhelp.py check-doc`

### 3.3 Process Standards

**EN 50128 Lifecycle** (Section 5.3):
- V-Model lifecycle per EN 50128
- Phase entry/exit criteria defined in SQAP Section 5
- Quality gates at all phase transitions
- Independent verification and validation (SIL 3-4)

**Change Control**:
- All changes managed via Configuration Management (SCMP)
- Change impact analysis mandatory
- Regression testing for all changes
- Traceability updated for all changes

---

## 4. Quality Activities

### 4.1 Document Reviews (MANDATORY - 1 Pass Allowed)

**Frequency**: All documents before submission to technical reviewers

**Process**:
1. Developer creates deliverable
2. **QA reviews for template compliance (1 pass)**
3. If QA rejects: Developer fixes and resubmits ONCE
4. If QA approves: Proceeds to technical review (VER/VAL/VMGR/DES/etc.)

**QA Review Checklist**:
- [ ] Document ID format correct (DOC-XXX-YYY-NNN)
- [ ] Document Control table complete
- [ ] Approvals table with SIL-specific approvers
- [ ] Version history table present
- [ ] All sections from template present
- [ ] Traceability sections complete (SIL 3-4)
- [ ] References to other documents correct

**Exit Criteria**:
- Zero template compliance violations
- All sections complete
- Document ready for technical review

**Deliverable**: QA Document Review Report

### 4.2 Code Reviews (MANDATORY - All Code)

**Frequency**: All code before integration

**Participants**: Developer (author), Peer Reviewer, QA Engineer

**Process**:
1. Developer submits code + unit tests
2. Automated checks: MISRA C (Cppcheck), complexity (Lizard)
3. Peer review: Logic, defensive programming, error handling
4. QA review: MISRA C compliance, complexity, defensive programming
5. Developer fixes all critical/major issues
6. Re-review if critical issues found
7. QA approval required for integration

**Code Review Checklist**: See Section 10.1

**Exit Criteria**:
- Zero critical issues
- Zero mandatory MISRA C violations (SIL 2+)
- Cyclomatic complexity within limits
- All comments resolved
- Unit tests pass with required coverage

**Deliverable**: Code Review Report

### 4.3 Design Reviews (MANDATORY)

**Frequency**: Architecture design, detailed design

**Participants**: Designer, Requirements Engineer, Safety Engineer, QA Engineer

**Process**:
1. Designer submits Software Architecture Specification (SAS) or Software Design Specification (SDS)
2. QA reviews for template compliance (1 pass)
3. Technical review: Requirements traceability, complexity, safety design
4. QA review: Traceability completeness, complexity estimates, defensive programming design
5. Designer addresses all comments
6. QA approval required for implementation

**Design Review Checklist**: See Section 10.2

**Exit Criteria**:
- Design approved by all reviewers
- Traceability complete (100% requirements allocated)
- Estimated complexity within limits
- Safety design adequate

**Deliverable**: Design Review Report

### 4.4 Testing Oversight (MANDATORY SIL 2+)

**Activities**:
- Review test plans (unit, integration, validation)
- Review test specifications (test cases, procedures)
- Witness critical tests (safety-critical functions, SIL 3-4)
- Verify coverage requirements met (100% for SIL 3-4)
- Approve test reports

**Coverage Requirements** (EN 50128 Table A.21):
| SIL Level | Statement | Branch | Condition | MC/DC |
|-----------|-----------|--------|-----------|-------|
| SIL 0 | 80% (R) | 70% (R) | - | - |
| SIL 1 | 90% (HR) | 80% (HR) | - | - |
| SIL 2 | 100% (**M**) | 100% (**M**) | - | - |
| SIL 3-4 | 100% (**M**) | 100% (**M**) | 100% (**M**) | HR |

**Exit Criteria**:
- All test plans approved
- Coverage requirements met
- All tests pass
- Defects resolved or accepted with justification

**Deliverable**: Test Oversight Report

---

## 5. Quality Gates

### 5.1 Quality Gate Framework

**Purpose**: Ensure phase completion meets quality criteria before proceeding

**Gate Authority**:
- **SIL 0-2**: QA Manager approves, PM can override with justification
- **SIL 3-4**: QA Manager approves, PM CANNOT override

**Gate Process**:
1. Phase lead requests gate approval
2. QA evaluates exit criteria (checklist)
3. QA Manager approves or rejects
4. If rejected: Issues must be resolved before proceeding
5. If approved: Phase transition authorized

### 5.2 Requirements Phase Gate

**Exit Criteria**:
- [ ] Software Requirements Specification (SRS) approved
- [ ] All requirements reviewed and approved
- [ ] Traceability matrix complete (system req → software req)
- [ ] SIL levels assigned and justified
- [ ] Requirements verification report approved
- [ ] Requirements meet EN 50128 Section 7.2 requirements
- [ ] No open critical defects

**Verification Method**:
```bash
# Check traceability completeness
workspace.py trace validate --phase requirements --sil <sil-level>

# Verify SIL assignments
python3 tools/sil_checker.py --srs docs/DOC-REQ-SRS-001.md

# Check requirements quality
python3 tools/requirements_checker.py \
    --srs docs/DOC-REQ-SRS-001.md \
    --sil <sil-level> \
    --output evidence/qa/requirements_gate_check.json
```

**Deliverable**: Requirements Gate Approval

---

### 5.3 Design Phase Gate

**Exit Criteria**:
- [ ] Software Architecture Specification (SAS) approved
- [ ] Software Design Specification (SDS) approved
- [ ] Design reviews complete
- [ ] Estimated complexity within limits
- [ ] Traceability complete (requirements → design)
- [ ] Design verification report approved
- [ ] Interface specifications complete
- [ ] No open critical defects

**Verification Method**:
```bash
# Check design traceability
workspace.py trace validate --phase design --sil <sil-level>

# Estimate complexity (before implementation)
lizard --CCN <limit> design/pseudocode/ || echo "Design complexity exceeds limit"

# Check design quality
python3 tools/design_checker.py \
    --sas docs/DOC-DES-SAS-001.md \
    --sds docs/DOC-DES-SDS-001.md \
    --sil <sil-level> \
    --output evidence/qa/design_gate_check.json
```

**Deliverable**: Design Gate Approval

---

### 5.4 Implementation Phase Gate

**Exit Criteria**:
- [ ] All code reviewed and approved (100% code review coverage)
- [ ] MISRA C compliance verified (zero mandatory violations for SIL 2+)
- [ ] Cyclomatic complexity within limits (all functions)
- [ ] Unit tests pass with required coverage
- [ ] Static analysis clean (Cppcheck, Clang)
- [ ] Traceability complete (design → code → unit tests)
- [ ] Implementation verification report approved
- [ ] No open critical defects

**Verification Method**:
```bash
# Check code review coverage (100% required)
python3 tools/code_review_coverage.py \
    --source src/ \
    --reviews evidence/qa/code_reviews/ \
    --output evidence/qa/code_review_coverage.json

# Verify MISRA C compliance
cppcheck --addon=misra --quiet src/ 2>&1 | tee evidence/qa/misra_violations.txt
# SIL 2+: Must be zero violations

# Check complexity
lizard --CCN <limit> src/

# Verify unit test coverage
python3 tools/check_coverage.py \
    --sil <sil-level> \
    --coverage coverage.json \
    --output evidence/qa/coverage_validation.json

# Check traceability
workspace.py trace validate --phase implementation --sil <sil-level>
```

**Deliverable**: Implementation Gate Approval

---

### 5.5 Testing Phase Gate

**Exit Criteria**:
- [ ] All test plans approved (unit, integration, validation)
- [ ] All tests executed and passed
- [ ] Coverage requirements met (statement, branch, condition per SIL)
- [ ] Traceability complete (requirements → tests)
- [ ] Test reports approved
- [ ] Defects resolved or accepted with justification
- [ ] No open critical defects

**Verification Method**:
```bash
# Verify test coverage
python3 tools/check_coverage.py \
    --sil <sil-level> \
    --coverage combined_coverage.json \
    --output evidence/qa/test_gate_coverage.json

# Check test traceability
workspace.py trace validate --phase testing --sil <sil-level>
workspace.py trace report \
    --from requirements \
    --to tests \
    --output evidence/qa/test_traceability.md

# Verify all tests passed
python3 tools/test_results_checker.py \
    --results tests/results/*.json \
    --output evidence/qa/test_results_summary.json
```

**Deliverable**: Testing Gate Approval

---

### 5.6 Deployment Gate (Final Release)

**Exit Criteria**:
- [ ] All quality activities complete
- [ ] All documentation complete and approved
- [ ] Verification report approved (VER)
- [ ] Validation report approved (VAL)
- [ ] Safety approval obtained (SAF)
- [ ] Customer acceptance obtained (UAT certificate)
- [ ] Configuration baseline established
- [ ] No open critical or major defects
- [ ] All traceability complete (end-to-end)
- [ ] Final audit complete (QA)

**Verification Method**:
```bash
# Final audit check
python3 tools/final_audit.py \
    --sil <sil-level> \
    --evidence evidence/ \
    --output evidence/qa/final_audit_report.json

# Verify end-to-end traceability
workspace.py trace validate --phase all --sil <sil-level>

# Check open defects
python3 tools/defect_checker.py \
    --defects defects.json \
    --allow-minor-only \
    --output evidence/qa/defect_status.json
```

**Deliverable**: Release Certificate

---

## 6. Quality Metrics Collection

### 6.1 Metrics Framework

**EN 50128 Section 6.5.4.5**: "Data recording and analysis" (MANDATORY SIL 3-4)

**Metrics Categories**:
1. **Process Metrics**: Schedule adherence, defect detection rate, review effectiveness
2. **Product Metrics**: Cyclomatic complexity, MISRA C compliance rate, test coverage, defect density
3. **Project Metrics**: Team productivity, rework rate, quality costs

### 6.2 Key Quality Metrics

| Metric | Target (SIL 3-4) | Collection Method |
|--------|------------------|-------------------|
| **MISRA C Compliance Rate** | 100% (mandatory rules) | Cppcheck, PC-lint Plus |
| **Cyclomatic Complexity** | Max CCN ≤ 10 | Lizard |
| **Test Coverage** | Statement 100%, Branch 100%, Condition 100% | gcov, lcov |
| **Code Review Coverage** | 100% (all code reviewed) | Manual tracking |
| **Defect Density** | < 1 per KLOC | Defect tracking system |
| **Traceability Completeness** | 100% (all requirements traced) | workspace.py trace validate |
| **Requirements Stability** | Change rate < 10% after baseline | Requirements tracking |
| **Test Pass Rate** | 100% (all tests pass) | Test results |

### 6.3 Metrics Collection Script

```python
#!/usr/bin/env python3
"""EN 50128 Quality Metrics Collector - Production Version"""

import subprocess
import re
import json
import os
from datetime import datetime
from pathlib import Path

class EN50128QualityMetrics:
    """Collect comprehensive quality metrics for EN 50128 compliance."""
    
    def __init__(self, project_root, sil_level):
        self.project_root = Path(project_root)
        self.sil_level = int(sil_level)
        self.metrics = {
            'project': str(self.project_root),
            'sil_level': self.sil_level,
            'timestamp': datetime.now().isoformat(),
            'metrics': {}
        }
    
    def collect_all(self):
        """Collect all quality metrics."""
        print(f"=== EN 50128 Quality Metrics (SIL {self.sil_level}) ===\n")
        
        self.collect_misra_compliance()
        self.collect_complexity_metrics()
        self.collect_coverage_metrics()
        self.collect_code_review_coverage()
        self.collect_traceability_metrics()
        self.collect_defect_metrics()
        
        self.evaluate_compliance()
        self.save_metrics()
        self.print_summary()
    
    def collect_misra_compliance(self):
        """Collect MISRA C:2012 compliance metrics."""
        print("Collecting MISRA C compliance...")
        
        result = subprocess.run(
            ['cppcheck', '--addon=misra', '--quiet', 
             str(self.project_root / 'src')],
            capture_output=True,
            text=True,
            cwd=self.project_root
        )
        
        violations = result.stderr.strip().split('\n') if result.stderr else []
        violation_count = len([v for v in violations if v])
        
        # SIL-specific requirement
        sil_requirement = {
            0: {'mandatory_violations': 10, 'advisory_violations': 50},
            1: {'mandatory_violations': 5, 'advisory_violations': 30},
            2: {'mandatory_violations': 0, 'advisory_violations': 20},
            3: {'mandatory_violations': 0, 'advisory_violations': 10},
            4: {'mandatory_violations': 0, 'advisory_violations': 0}
        }
        
        req = sil_requirement.get(self.sil_level, 
                                   {'mandatory_violations': 0, 'advisory_violations': 0})
        
        self.metrics['metrics']['misra_compliance'] = {
            'total_violations': violation_count,
            'allowed_mandatory_violations': req['mandatory_violations'],
            'allowed_advisory_violations': req['advisory_violations'],
            'compliant': (violation_count <= req['mandatory_violations']),
            'violations': violations[:10]  # First 10 for reference
        }
    
    def collect_complexity_metrics(self):
        """Collect cyclomatic complexity metrics."""
        print("Collecting complexity metrics...")
        
        complexity_limits = {0: 20, 1: 20, 2: 15, 3: 10, 4: 10}
        limit = complexity_limits.get(self.sil_level, 10)
        
        result = subprocess.run(
            ['lizard', str(self.project_root / 'src')],
            capture_output=True,
            text=True,
            cwd=self.project_root
        )
        
        avg_ccn_match = re.search(r'Average CCN:\s+([\d.]+)', result.stdout)
        max_ccn_match = re.search(r'Max CCN:\s+(\d+)', result.stdout)
        
        avg_ccn = float(avg_ccn_match.group(1)) if avg_ccn_match else 0.0
        max_ccn = int(max_ccn_match.group(1)) if max_ccn_match else 0
        
        self.metrics['metrics']['complexity'] = {
            'average_ccn': avg_ccn,
            'max_ccn': max_ccn,
            'limit_ccn': limit,
            'compliant': (max_ccn <= limit)
        }
    
    def collect_coverage_metrics(self):
        """Collect test coverage metrics."""
        print("Collecting coverage metrics...")
        
        coverage_file = self.project_root / 'coverage.json'
        if not coverage_file.exists():
            self.metrics['metrics']['coverage'] = {
                'available': False,
                'message': 'Coverage data not found'
            }
            return
        
        with open(coverage_file) as f:
            coverage_data = json.load(f)
        
        # SIL-specific requirements
        requirements = {
            0: {'statement': 80, 'branch': 70, 'condition': 0},
            1: {'statement': 90, 'branch': 80, 'condition': 0},
            2: {'statement': 100, 'branch': 100, 'condition': 0},
            3: {'statement': 100, 'branch': 100, 'condition': 100},
            4: {'statement': 100, 'branch': 100, 'condition': 100}
        }
        
        req = requirements.get(self.sil_level, 
                               {'statement': 100, 'branch': 100, 'condition': 100})
        
        stmt_cov = coverage_data.get('line_percent', 0)
        branch_cov = coverage_data.get('branch_percent', 0)
        cond_cov = coverage_data.get('condition_percent', 0)
        
        compliant = (stmt_cov >= req['statement'] and 
                     branch_cov >= req['branch'] and
                     cond_cov >= req['condition'])
        
        self.metrics['metrics']['coverage'] = {
            'statement_coverage': stmt_cov,
            'branch_coverage': branch_cov,
            'condition_coverage': cond_cov,
            'required_statement': req['statement'],
            'required_branch': req['branch'],
            'required_condition': req['condition'],
            'compliant': compliant
        }
    
    def collect_code_review_coverage(self):
        """Collect code review coverage metrics."""
        print("Collecting code review coverage...")
        
        # Find all source files
        src_files = list((self.project_root / 'src').rglob('*.c'))
        total_files = len(src_files)
        
        # Find code review reports
        review_dir = self.project_root / 'evidence' / 'qa' / 'code_reviews'
        if not review_dir.exists():
            reviewed_files = 0
        else:
            review_files = list(review_dir.glob('*.md'))
            reviewed_files = len(review_files)
        
        coverage_percent = (reviewed_files / total_files * 100) if total_files > 0 else 0
        
        # SIL 2+: 100% code review coverage required
        required = 100 if self.sil_level >= 2 else 90
        
        self.metrics['metrics']['code_review'] = {
            'total_source_files': total_files,
            'reviewed_files': reviewed_files,
            'coverage_percent': coverage_percent,
            'required_percent': required,
            'compliant': (coverage_percent >= required)
        }
    
    def collect_traceability_metrics(self):
        """Collect traceability completeness metrics."""
        print("Collecting traceability metrics...")
        
        # Run traceability validation
        result = subprocess.run(
            ['python3', 'tools/workspace.py', 'trace', 'validate',
             '--phase', 'all', '--sil', str(self.sil_level)],
            capture_output=True,
            text=True,
            cwd=self.project_root
        )
        
        # Parse validation result
        compliant = (result.returncode == 0)
        
        # SIL 3-4: 100% traceability required
        required = 100 if self.sil_level >= 3 else 90
        
        self.metrics['metrics']['traceability'] = {
            'compliant': compliant,
            'required_completeness': required,
            'validation_output': result.stdout[:500]  # First 500 chars
        }
    
    def collect_defect_metrics(self):
        """Collect defect metrics."""
        print("Collecting defect metrics...")
        
        defect_file = self.project_root / 'defects.json'
        if not defect_file.exists():
            self.metrics['metrics']['defects'] = {
                'available': False,
                'message': 'Defect tracking data not found'
            }
            return
        
        with open(defect_file) as f:
            defects = json.load(f)
        
        open_critical = len([d for d in defects if d.get('severity') == 'critical' 
                             and d.get('status') == 'open'])
        open_major = len([d for d in defects if d.get('severity') == 'major' 
                          and d.get('status') == 'open'])
        open_minor = len([d for d in defects if d.get('severity') == 'minor' 
                          and d.get('status') == 'open'])
        
        # SIL 3-4: Zero open critical/major defects for release
        compliant = (open_critical == 0 and 
                     (open_major == 0 if self.sil_level >= 3 else True))
        
        self.metrics['metrics']['defects'] = {
            'open_critical': open_critical,
            'open_major': open_major,
            'open_minor': open_minor,
            'total_open': open_critical + open_major + open_minor,
            'compliant': compliant
        }
    
    def evaluate_compliance(self):
        """Evaluate overall EN 50128 compliance."""
        print("\nEvaluating EN 50128 compliance...")
        
        # Check each metric for compliance
        compliant_metrics = []
        non_compliant_metrics = []
        
        for metric_name, metric_data in self.metrics['metrics'].items():
            if isinstance(metric_data, dict) and 'compliant' in metric_data:
                if metric_data['compliant']:
                    compliant_metrics.append(metric_name)
                else:
                    non_compliant_metrics.append(metric_name)
        
        overall_compliant = (len(non_compliant_metrics) == 0)
        
        self.metrics['compliance'] = {
            'overall_compliant': overall_compliant,
            'compliant_metrics': compliant_metrics,
            'non_compliant_metrics': non_compliant_metrics
        }
    
    def save_metrics(self):
        """Save metrics to JSON file."""
        output_file = self.project_root / 'evidence' / 'qa' / 'quality_metrics.json'
        output_file.parent.mkdir(parents=True, exist_ok=True)
        
        with open(output_file, 'w') as f:
            json.dump(self.metrics, f, indent=2)
        
        print(f"\nMetrics saved to: {output_file}")
    
    def print_summary(self):
        """Print metrics summary."""
        print("\n" + "=" * 60)
        print(f"QUALITY METRICS SUMMARY (SIL {self.sil_level})")
        print("=" * 60)
        
        # MISRA C Compliance
        if 'misra_compliance' in self.metrics['metrics']:
            m = self.metrics['metrics']['misra_compliance']
            status = "✓ PASS" if m['compliant'] else "✗ FAIL"
            print(f"\nMISRA C Compliance: {status}")
            print(f"  Total violations: {m['total_violations']}")
            print(f"  Allowed (mandatory): {m['allowed_mandatory_violations']}")
        
        # Complexity
        if 'complexity' in self.metrics['metrics']:
            m = self.metrics['metrics']['complexity']
            status = "✓ PASS" if m['compliant'] else "✗ FAIL"
            print(f"\nCyclomatic Complexity: {status}")
            print(f"  Average CCN: {m['average_ccn']:.1f}")
            print(f"  Max CCN: {m['max_ccn']} (limit: {m['limit_ccn']})")
        
        # Coverage
        if 'coverage' in self.metrics['metrics']:
            m = self.metrics['metrics']['coverage']
            if m.get('available', True):
                status = "✓ PASS" if m['compliant'] else "✗ FAIL"
                print(f"\nTest Coverage: {status}")
                print(f"  Statement: {m['statement_coverage']:.1f}% "
                      f"(required: {m['required_statement']}%)")
                print(f"  Branch: {m['branch_coverage']:.1f}% "
                      f"(required: {m['required_branch']}%)")
                if m['required_condition'] > 0:
                    print(f"  Condition: {m['condition_coverage']:.1f}% "
                          f"(required: {m['required_condition']}%)")
        
        # Code Review
        if 'code_review' in self.metrics['metrics']:
            m = self.metrics['metrics']['code_review']
            status = "✓ PASS" if m['compliant'] else "✗ FAIL"
            print(f"\nCode Review Coverage: {status}")
            print(f"  Reviewed: {m['reviewed_files']}/{m['total_source_files']} files "
                  f"({m['coverage_percent']:.1f}%)")
            print(f"  Required: {m['required_percent']}%")
        
        # Traceability
        if 'traceability' in self.metrics['metrics']:
            m = self.metrics['metrics']['traceability']
            status = "✓ PASS" if m['compliant'] else "✗ FAIL"
            print(f"\nTraceability: {status}")
            print(f"  Required completeness: {m['required_completeness']}%")
        
        # Defects
        if 'defects' in self.metrics['metrics']:
            m = self.metrics['metrics']['defects']
            if m.get('available', True):
                status = "✓ PASS" if m['compliant'] else "✗ FAIL"
                print(f"\nDefect Status: {status}")
                print(f"  Open Critical: {m['open_critical']}")
                print(f"  Open Major: {m['open_major']}")
                print(f"  Open Minor: {m['open_minor']}")
        
        # Overall Compliance
        print("\n" + "=" * 60)
        if self.metrics['compliance']['overall_compliant']:
            print("✓ OVERALL COMPLIANCE: PASS")
            print("All quality metrics meet EN 50128 requirements")
        else:
            print("✗ OVERALL COMPLIANCE: FAIL")
            print("Non-compliant metrics:")
            for metric in self.metrics['compliance']['non_compliant_metrics']:
                print(f"  - {metric}")
        print("=" * 60)

if __name__ == '__main__':
    import sys
    if len(sys.argv) != 3:
        print("Usage: quality_metrics.py <project_root> <sil_level>")
        print("Example: quality_metrics.py . 3")
        sys.exit(1)
    
    collector = EN50128QualityMetrics(sys.argv[1], sys.argv[2])
    collector.collect_all()
    
    # Exit with failure if not compliant
    sys.exit(0 if collector.metrics['compliance']['overall_compliant'] else 1)
```

**Usage**:
```bash
# Collect all quality metrics for SIL 3 project
python3 tools/quality_metrics.py . 3

# Output: evidence/qa/quality_metrics.json
# Exit code: 0 (pass) or 1 (fail)
```

---

## 7. Non-Conformance Management

### 7.1 NCR Process

**EN 50128 Section 6.5.4.5(d)**: "Tracking and tracing of deviations"

**Non-Conformance Types**:
- **Critical**: Safety impact or major standard violation (STOP WORK)
- **Major**: Significant quality/compliance issue (must fix before phase gate)
- **Minor**: Process deviation, quality improvement opportunity

**NCR Workflow**:
```
Detection → Logging → Impact Assessment → Root Cause Analysis → 
Corrective Action → Verification → Closure
```

### 7.2 Non-Conformance Report Template

```markdown
# Non-Conformance Report (NCR)

## NCR Information
- **NCR ID**: NCR-2026-001
- **Date Raised**: 2026-03-14
- **Raised By**: [QA Engineer Name]
- **Project**: [Railway Safety System Name]
- **Phase**: [Requirements/Design/Implementation/Testing/etc.]
- **SIL Level**: [0-4]

---

## Non-Conformance Details

### Description
[Clear, objective description of the non-conformance]

**Example**: "File `brake_controller.c` contains dynamic memory allocation (malloc) on line 142, violating MISRA C:2012 Rule 21.3 and EN 50128 requirement for static allocation at SIL 3."

### Standard/Requirement Violated
- EN 50128 Section/Table: [e.g., Section 7.4, Table A.4]
- MISRA C Rule: [e.g., Rule 21.3 (Mandatory)]
- Project Requirement: [e.g., SQAP Section 3.1]

### Location
- **Document/File**: `src/brake_controller.c`
- **Section/Line**: Line 142
- **Module**: Brake Control System

### Severity
[X] Critical - Safety impact or major standard violation  
[ ] Major - Significant issue, affects quality/compliance  
[ ] Minor - Process deviation, quality improvement

**Justification for Severity**: Dynamic memory allocation in safety-critical code poses uncontrolled memory exhaustion risk, directly impacting safety at SIL 3.

---

## Impact Assessment

### Safety Impact
**HIGH**: Dynamic memory allocation can lead to memory exhaustion or fragmentation, causing safety-critical brake function failure. This violates SIL 3 deterministic behavior requirement.

### Quality Impact
**HIGH**: MISRA C:2012 Rule 21.3 violation (Mandatory). Static analysis tools will flag as critical violation. Zero mandatory violations required for SIL 3.

### Schedule Impact
**MEDIUM**: Estimated 2 days to refactor to static allocation, retest, and reverify.

---

## Root Cause Analysis

### Immediate Cause
Developer used malloc() to allocate buffer dynamically based on runtime parameter.

### Root Cause
1. Insufficient training on EN 50128 static allocation requirements
2. No automated check for malloc/free in CI pipeline
3. Code review missed the violation

### Contributing Factors
- Developer new to EN 50128 projects
- Code review checklist not followed completely
- Static analysis not run before code review

---

## Corrective Action

### Immediate Action (This Instance)
1. Refactor `brake_controller.c` to use static allocation
2. Define maximum buffer size based on worst-case analysis
3. Add buffer size validation at runtime
4. Re-run unit tests and static analysis
5. Re-review code

**Assigned To**: [Developer Name]  
**Due Date**: 2026-03-16

### Preventive Action (Prevent Recurrence)
1. Add malloc/free detection to CI pipeline (Cppcheck rule)
2. Conduct EN 50128 training for all developers (memory management focus)
3. Update code review checklist with explicit malloc/free check
4. Add pre-commit hook to reject malloc/free in src/

**Assigned To**: [QA Manager]  
**Due Date**: 2026-03-20

### Process Improvement
- Update SQAP Section 3.1 to include CI pipeline requirements
- Add static allocation patterns to coding guidelines
- Schedule monthly refresher training on MISRA C and EN 50128

---

## Verification

### Verification Method
1. Code inspection: Verify no malloc/calloc/realloc/free in refactored code
2. Static analysis: Run Cppcheck, verify zero Rule 21.3 violations
3. Unit tests: Execute all brake controller unit tests, verify 100% pass
4. Code review: Re-review refactored code with updated checklist

### Verification Result
[To be filled after corrective action implementation]

- [ ] Code refactored (verified by: _________)
- [ ] Static analysis clean (verified by: _________)
- [ ] Unit tests pass (verified by: _________)
- [ ] Code review approved (verified by: _________)

---

## Closure

- **Corrective Action Completed**: [Date]
- **Verified By**: [QA Engineer Name]
- **Approved for Closure**: [QA Manager Name]
- **Closure Date**: [Date]

---

## Approvals

- **QA Manager**: _________________ Date: _______
- **Project Manager**: ____________ Date: _______
```

### 7.3 NCR Tracking

**Tracking System**: JSON-based tracking with Python scripts

```python
#!/usr/bin/env python3
"""NCR Tracking System for EN 50128 Projects"""

import json
from datetime import datetime
from pathlib import Path

class NCRTracker:
    """Track and manage Non-Conformance Reports."""
    
    def __init__(self, ncr_file='ncr_tracking.json'):
        self.ncr_file = Path(ncr_file)
        self.ncrs = self.load_ncrs()
    
    def load_ncrs(self):
        """Load existing NCRs from file."""
        if self.ncr_file.exists():
            with open(self.ncr_file) as f:
                return json.load(f)
        return {'ncrs': []}
    
    def create_ncr(self, description, severity, location, violated_standard):
        """Create a new NCR."""
        ncr_id = f"NCR-{datetime.now().year}-{len(self.ncrs['ncrs']) + 1:03d}"
        
        ncr = {
            'id': ncr_id,
            'date_raised': datetime.now().isoformat(),
            'description': description,
            'severity': severity,  # critical, major, minor
            'location': location,
            'violated_standard': violated_standard,
            'status': 'open',
            'corrective_action': None,
            'verification': None,
            'closure_date': None
        }
        
        self.ncrs['ncrs'].append(ncr)
        self.save_ncrs()
        
        print(f"NCR created: {ncr_id}")
        return ncr_id
    
    def update_ncr(self, ncr_id, **kwargs):
        """Update an existing NCR."""
        for ncr in self.ncrs['ncrs']:
            if ncr['id'] == ncr_id:
                ncr.update(kwargs)
                self.save_ncrs()
                print(f"NCR updated: {ncr_id}")
                return True
        return False
    
    def close_ncr(self, ncr_id):
        """Close an NCR after verification."""
        for ncr in self.ncrs['ncrs']:
            if ncr['id'] == ncr_id:
                ncr['status'] = 'closed'
                ncr['closure_date'] = datetime.now().isoformat()
                self.save_ncrs()
                print(f"NCR closed: {ncr_id}")
                return True
        return False
    
    def get_open_ncrs(self, severity=None):
        """Get all open NCRs, optionally filtered by severity."""
        open_ncrs = [ncr for ncr in self.ncrs['ncrs'] if ncr['status'] == 'open']
        if severity:
            open_ncrs = [ncr for ncr in open_ncrs if ncr['severity'] == severity]
        return open_ncrs
    
    def report(self):
        """Generate NCR summary report."""
        total = len(self.ncrs['ncrs'])
        open_critical = len(self.get_open_ncrs('critical'))
        open_major = len(self.get_open_ncrs('major'))
        open_minor = len(self.get_open_ncrs('minor'))
        closed = len([ncr for ncr in self.ncrs['ncrs'] if ncr['status'] == 'closed'])
        
        print("\n=== NCR Summary Report ===")
        print(f"Total NCRs: {total}")
        print(f"Open Critical: {open_critical}")
        print(f"Open Major: {open_major}")
        print(f"Open Minor: {open_minor}")
        print(f"Closed: {closed}")
        
        if open_critical > 0:
            print("\n⚠️  CRITICAL NCRs OPEN - STOP WORK")
            for ncr in self.get_open_ncrs('critical'):
                print(f"  {ncr['id']}: {ncr['description'][:60]}...")
    
    def save_ncrs(self):
        """Save NCRs to file."""
        with open(self.ncr_file, 'w') as f:
            json.dump(self.ncrs, f, indent=2)

if __name__ == '__main__':
    tracker = NCRTracker()
    
    # Example usage
    tracker.create_ncr(
        description="Dynamic memory allocation in brake_controller.c line 142",
        severity="critical",
        location="src/brake_controller.c:142",
        violated_standard="MISRA C:2012 Rule 21.3, EN 50128 SIL 3 static allocation"
    )
    
    tracker.report()
```

---

## 8. Quality Audit Process

### 8.1 Audit Types

**Process Audits**: Verify EN 50128 process compliance
**Product Audits**: Verify deliverable quality and completeness
**Tool Audits**: Verify tool qualification and usage (T2/T3 tools)

**Frequency**:
- Phase transitions (mandatory)
- Major milestones
- After significant changes
- Pre-release (mandatory)

### 8.2 Audit Checklist

See current SKILL.md for complete audit checklist (lines 533-635).

**Key Audit Areas**:
1. Lifecycle compliance (V-Model, phase gates)
2. Requirements management (SRS, traceability, SIL assignments)
3. Design management (SAS, SDS, complexity, traceability)
4. Implementation (coding standards, code reviews, static analysis, unit tests)
5. Testing (test plans, coverage, traceability)
6. Verification (static analysis, verification reports, independence)
7. Validation (customer involvement, operational testing, validation reports, independence)
8. Configuration management (SCMP, version control, baselines, change control)
9. Quality assurance (SQAP, reviews, metrics, NCRs)
10. Safety (safety plan, hazard analysis, safety requirements, safety case)
11. Documentation (all mandatory documents, approvals, traceability)
12. Tool qualification (tool assessment, qualification evidence, tool usage)

---

## 9. Traceability Management

### 9.1 EN 50128 Traceability Requirements

**Section 6.5.4.14**: "Traceability to requirements shall be an important consideration in the validation of a safety-related system."

**Section 6.5.4.15**: Traceability shall address:
a) Requirements → Design
b) Design → Implementation
c) Requirements/Design → Tests (component, integration, overall)

**SIL 3-4**: Traceability is **MANDATORY** (EN 50128 Table A.9)

### 9.2 Traceability Workflow

```bash
# 1. Create traceability links during development
workspace.py trace create \
    --from requirements \
    --to design \
    --source-id REQ-SAF-015 \
    --target-id DES-MOD-010 \
    --rationale "Design module implements emergency brake requirement"

# 2. Validate traceability completeness (per phase)
workspace.py trace validate --phase requirements --sil 3
workspace.py trace validate --phase design --sil 3
workspace.py trace validate --phase implementation --sil 3
workspace.py trace validate --phase testing --sil 3

# 3. Generate traceability reports
workspace.py trace report \
    --from requirements \
    --to design \
    --format markdown \
    --output evidence/traceability/req_to_design.md

workspace.py trace report \
    --from requirements \
    --to tests \
    --format markdown \
    --output evidence/traceability/req_to_tests.md

# 4. Identify gaps
workspace.py trace check-gaps --from requirements --to tests

# 5. Final traceability audit (all phases)
workspace.py trace validate --phase all --sil 3
```

**Quality Gate Requirement**: 100% traceability completeness for SIL 3-4 before release

---

## 10. Tool Integration

### 10.1 QA Tools (Working Implementations)

**Static Analysis Tools**:
- **Cppcheck**: MISRA C compliance checking
- **PC-lint Plus**: Advanced MISRA C checking (if available)
- **Clang Static Analyzer**: Additional static analysis

**Complexity Analysis**:
- **Lizard**: Cyclomatic complexity measurement

**Coverage Analysis**:
- **gcov**: Statement and branch coverage
- **lcov**: Coverage report generation

**Traceability Management**:
- **workspace.py trace**: Complete traceability management

**Workflow Management**:
- **workspace.py wf**: Workflow state management (submit, review, approve)

**Custom QA Tools**:
- **quality_metrics.py**: Comprehensive metrics collection
- **ncr_tracker.py**: Non-conformance tracking
- **quality_gate.py**: Automated gate checks

### 10.2 Workflow Integration

**QA Review Workflow**:
```bash
# Developer submits deliverable
workspace.py wf submit --deliverable DOC-VER-REP-001 --phase verification

# QA reviews (template compliance check)
workspace.py wf review \
    --deliverable DOC-VER-REP-001 \
    --reviewer QUA \
    --status approved \
    --comments "Template compliance verified. All sections complete."

# If rejected:
workspace.py wf review \
    --deliverable DOC-VER-REP-001 \
    --reviewer QUA \
    --status rejected \
    --comments "Document ID format incorrect. Approvals table missing SIL 3 approvers."

# Developer fixes and resubmits ONCE
workspace.py wf submit --deliverable DOC-VER-REP-001 --phase verification --resubmit

# Check workflow status
workspace.py wf status --deliverable DOC-VER-REP-001
```

---

## 11. SIL-Specific Requirements

### SIL 0-1

| Requirement | Implementation |
|-------------|----------------|
| EN ISO 9001 compliance (M) | Company Quality System active |
| Configuration Management (M) | SCMP in place, Git version control |
| Code reviews (R) | Peer review recommended |
| MISRA C compliance (R) | Advisory rules recommended |
| Traceability (R) | 80% completeness |

### SIL 2

| Requirement | Implementation |
|-------------|----------------|
| EN ISO 9001 compliance (M) | Company Quality System active |
| Configuration Management (M) | SCMP in place, Git with baselines |
| Code reviews (HR) | 100% code reviewed |
| MISRA C compliance (M) | Zero mandatory violations |
| Complexity limit | CCN ≤ 15 |
| Coverage (M) | Statement 100%, Branch 100% |
| Traceability (HR) | 95% completeness |
| Independent QA (HR) | QA team separate from development |

### SIL 3-4

| Requirement | Implementation |
|-------------|----------------|
| EN ISO 9001 compliance (M) | Company Quality System active |
| Configuration Management (M) | SCMP in place, Git with strict baselines |
| Code reviews (M) | 100% code reviewed, QA approval mandatory |
| MISRA C compliance (M) | Zero mandatory violations, minimal advisory |
| Complexity limit | CCN ≤ 10 |
| Coverage (M) | Statement 100%, Branch 100%, Condition 100% |
| Traceability (M) | 100% completeness |
| Independent QA (M) | QA team independent, reports to Safety Manager |
| Data recording and analysis (M) | Quality metrics collected and analyzed |
| Quality gates (M) | All phase gates enforced, QA approval cannot be overridden |

---

## 12. Example QA Scenarios

### Scenario 1: Code Review Detects MISRA C Violation

**Context**: SIL 3 brake controller project, implementation phase

**Issue Detected**:
```c
// File: src/brake_controller.c, Line 142
int* allocate_buffer(int size) {
    return malloc(size * sizeof(int));  // ← MISRA C Rule 21.3 violation
}
```

**QA Action**:
1. **Detect**: Static analysis (Cppcheck) flags Rule 21.3 violation
2. **Log NCR**: NCR-2026-001 created (severity: CRITICAL)
3. **Reject Code**: Code review result: REJECTED
4. **Inform Developer**: "Fix MISRA C Rule 21.3 violation (malloc forbidden), use static allocation"
5. **Developer Fixes**:
```c
// Fixed version
#define MAX_BUFFER_SIZE 256
static int buffer[MAX_BUFFER_SIZE];

error_t get_buffer(int size, int** output) {
    if (size > MAX_BUFFER_SIZE) return ERROR_BUFFER_TOO_LARGE;
    *output = buffer;
    return SUCCESS;
}
```
6. **Re-Review**: QA reviews fixed code, verifies static analysis clean
7. **Approve**: Code review result: APPROVED
8. **Close NCR**: NCR-2026-001 closed after verification

**Preventive Action**: Add malloc detection to CI pipeline

---

### Scenario 2: Quality Gate Rejects Phase Transition

**Context**: SIL 3 door control project, implementation phase complete, requesting gate approval

**Gate Check**:
```bash
python3 tools/quality_gate.py implementation 3
```

**Result**: FAIL
- MISRA C compliance: PASS ✓
- Complexity: PASS ✓
- Unit tests: PASS ✓
- **Coverage: FAIL ✗** (Branch coverage 95%, required 100%)
- Traceability: PASS ✓

**QA Action**:
1. **Reject Gate**: Implementation phase gate REJECTED
2. **Inform PM**: "Cannot proceed to integration phase. Coverage requirement not met."
3. **Create Action Item**: "Add tests to achieve 100% branch coverage"
4. **Developer Action**: Write additional tests for uncovered branches
5. **Re-Check**:
```bash
python3 tools/quality_gate.py implementation 3
```
6. **Result**: PASS (Coverage 100%)
7. **Approve Gate**: Implementation phase gate APPROVED, proceed to integration

---

### Scenario 3: Traceability Gap Detected

**Context**: SIL 3 speed controller project, testing phase

**Traceability Check**:
```bash
workspace.py trace validate --phase testing --sil 3
```

**Result**: FAIL
- Requirements with no tests: REQ-SPEED-012, REQ-SPEED-015
- **Gap**: 2 safety-critical requirements not covered by tests (98% coverage, 100% required)

**QA Action**:
1. **Log NCR**: NCR-2026-005 created (severity: MAJOR)
2. **Inform TST**: "Add tests for REQ-SPEED-012 and REQ-SPEED-015"
3. **TST Action**: Create VT-SPEED-025 and VT-SPEED-026 validation tests
4. **Update Traceability**:
```bash
workspace.py trace create \
    --from tests --to requirements \
    --source-id VT-SPEED-025 --target-id REQ-SPEED-012 \
    --rationale "Validation test verifies speed limit enforcement"

workspace.py trace create \
    --from tests --to requirements \
    --source-id VT-SPEED-026 --target-id REQ-SPEED-015 \
    --rationale "Validation test verifies overspeed alarm"
```
5. **Re-Validate**:
```bash
workspace.py trace validate --phase testing --sil 3
```
6. **Result**: PASS (100% traceability)
7. **Close NCR**: NCR-2026-005 closed

---

## 13. References

- EN 50128:2011 Section 6.5 (Software Quality Assurance)
- EN 50128:2011 Table A.9 (Software Quality Assurance Techniques)
- EN ISO 9001:2015 (Quality Management Systems)
- EN ISO 9000:2015 (Quality Management - Fundamentals and Vocabulary)
- ISO/IEC 90003:2014 (Software Engineering - Guidelines for ISO 9001)
- MISRA C:2012 (Coding Standard for C)
