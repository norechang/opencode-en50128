---
name: en50128-quality
description: EN 50128 software quality assurance processes for railway C applications
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  language: C
  section: "6.5"
  sil_applicability: "0-4"
---

## What I do

I provide quality assurance processes, code review techniques, and audit procedures required by EN 50128 Section 6.5:
- Software Quality Assurance Plan (SQAP) development
- Code reviews and Fagan inspections
- Process audits and compliance checks
- Metrics collection and analysis
- Configuration management oversight
- Quality gates enforcement

## When to use me

Use this skill when:
- Developing Software Quality Assurance Plan (SQAP)
- Performing code reviews and inspections
- Conducting process audits
- Collecting and analyzing quality metrics
- Enforcing quality gates
- Managing non-conformances
- Preparing for assessments

## Quality Assurance Techniques (EN 50128 Table A.9)

**EN 50128 Section 6.5, Table A.9** defines software quality assurance techniques:

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | Accredited to EN ISO 9001 | 7.1 | R | HR | HR |
| 2 | **Compliant with EN ISO 9001** | 7.1 | **M** | **M** | **M** |
| 3 | Compliant with ISO/IEC 90003 | 7.1 | R | R | R |
| 4 | **Company Quality System** | 7.1 | **M** | **M** | **M** |
| 5 | **Software Configuration Management** | D.48 | **M** | **M** | **M** |
| 6 | Checklists | D.7 | R | HR | HR |
| 7 | **Traceability** | D.58 | R | HR | **M** |
| 8 | **Data Recording and Analysis** | D.12 | HR | HR | **M** |

**MANDATORY for ALL SIL Levels (0, 1, 2, 3, 4):**
- **EN ISO 9001 Compliance (2)** - **MANDATORY**
- **Company Quality System (4)** - **MANDATORY**
- **Software Configuration Management (5)** - **MANDATORY**

**MANDATORY for SIL 3-4:**
- **Traceability (7)** - **MANDATORY**
- **Data Recording and Analysis (8)** - **MANDATORY**

**Key Points:**
- **Three techniques are MANDATORY for ALL SIL levels** (including SIL 0)
- Quality system SHALL comply with ISO 9001 (minimum)
- Configuration Management is MANDATORY for all projects
- Traceability and data analysis are MANDATORY for SIL 3-4

**Standard Reference:** `std/EN50128-2011.md` Section 6.5, Table A.9

## Quality Assurance Overview

**Purpose**: Ensure software development processes and products meet EN 50128 requirements

**Independence**: QA function must be independent from development team
- Reports to management, not development
- Authority to stop releases if quality issues found
- Mandatory for SIL 2+ (Highly Recommended for SIL 0-1)

**Key Responsibilities**:
- Software Quality Assurance Plan (SQAP) development
- Code reviews and inspections
- Process audits
- Metrics collection
- Non-conformance management
- Quality gates enforcement

## Software Quality Assurance Plan (SQAP)

### SQAP Template

```markdown
# Software Quality Assurance Plan (SQAP)

## 1. Introduction
### 1.1 Purpose
Define quality assurance activities for [Project Name]

### 1.2 Scope
- Software Component: [Name]
- SIL Level: [0-4]
- Development Phase: [Requirements/Design/Implementation/Testing]
- QA Team: [Names and Roles]

### 1.3 References
- EN 50128:2011
- Software Requirements Specification
- Software Configuration Management Plan
- Project Quality Plan

## 2. Quality Organization
### 2.1 QA Team
- QA Manager: [Name]
- QA Engineers: [Names]
- Independence: YES (reports to [Manager])

### 2.2 Responsibilities
- QA Manager: Overall quality oversight, audit approval
- QA Engineers: Reviews, inspections, metrics collection
- Development Team: Quality compliance, defect resolution

## 3. Quality Standards
### 3.1 Coding Standards
- MISRA C:2012 (Mandatory for SIL 2+)
- Project-specific coding guidelines
- Cyclomatic complexity limits (10/15/20 by SIL)

### 3.2 Documentation Standards
- EN 50128 required documents
- Template compliance
- Traceability requirements

### 3.3 Process Standards
- EN 50128 Section 5 (Software Development Lifecycle)
- Change control procedures
- Configuration management

## 4. Quality Activities
### 4.1 Code Reviews
- **Frequency**: All code before integration
- **Participants**: Developer, Reviewer, QA
- **Checklist**: Code review checklist (Appendix A)
- **Exit Criteria**: Zero critical issues, all comments resolved

### 4.2 Design Reviews
- **Frequency**: Architecture design, detailed design
- **Participants**: Designer, Requirements Engineer, Safety Engineer, QA
- **Checklist**: Design review checklist (Appendix B)
- **Exit Criteria**: Design approved, traceability complete

### 4.3 Audits
- **Frequency**: Phase transitions, major milestones
- **Scope**: Process compliance, document review
- **Participants**: QA team, Project Manager
- **Deliverable**: Audit report with findings

### 4.4 Testing Oversight
- Review test plans and test cases
- Witness critical tests
- Verify coverage requirements met
- Approve test reports

## 5. Quality Metrics
### 5.1 Process Metrics
- Schedule adherence
- Defect detection rate
- Review effectiveness

### 5.2 Product Metrics
- Cyclomatic complexity
- MISRA C compliance rate
- Test coverage percentage
- Defect density

## 6. Non-Conformance Management
### 6.1 Detection
- Identified during reviews, audits, testing
- Logged in non-conformance tracking system

### 6.2 Resolution
- Analyze root cause
- Implement corrective action
- Verify effectiveness
- Update processes if needed

### 6.3 Tracking
- All non-conformances tracked to closure
- Monthly summary to management

## 7. Quality Gates
### 7.1 Phase Exit Criteria
Each phase must meet quality criteria before proceeding:

**Requirements Phase**:
- [ ] All requirements reviewed and approved
- [ ] Traceability matrix complete
- [ ] SIL levels assigned and justified

**Design Phase**:
- [ ] Architecture and detailed design reviewed
- [ ] Complexity within limits
- [ ] Traceability to requirements complete

**Implementation Phase**:
- [ ] All code reviewed and approved
- [ ] MISRA C compliance verified
- [ ] Unit tests pass with required coverage

**Testing Phase**:
- [ ] All tests executed and passed
- [ ] Coverage requirements met
- [ ] Defects resolved or accepted

**Deployment**:
- [ ] All quality activities complete
- [ ] Documentation complete
- [ ] Safety approval obtained

## 8. Tools
- Static analysis: PC-lint Plus, Cppcheck
- Complexity analysis: Lizard
- Coverage analysis: gcov/lcov
- Issue tracking: [Tool name]
- Configuration management: Git

## 9. Records
- Code review records
- Audit reports
- Non-conformance reports
- Quality metrics reports
- Meeting minutes

## 10. Approval
- QA Manager: _________________ Date: _______
- Project Manager: ____________ Date: _______
- Safety Manager: _____________ Date: _______
```

## Code Review Process

### Code Review Checklist for C Code

```markdown
# Code Review Checklist - EN 50128 C Code

## Review Information
- File: [filename.c]
- Author: [Name]
- Reviewer: [Name]
- Date: [Date]
- SIL Level: [0-4]

## 1. MISRA C Compliance
- [ ] Fixed-width types used (uint8_t, uint16_t, etc.)
- [ ] No dynamic memory allocation (malloc/free)
- [ ] No recursion
- [ ] All function return values checked
- [ ] All pointers validated before use
- [ ] No implicit type conversions
- [ ] Explicit casting where needed
- [ ] Boolean conditions explicit (==, !=, not implicit)
- [ ] All switches have default case
- [ ] No unreachable code

## 2. Defensive Programming
- [ ] All function parameters validated
- [ ] NULL pointer checks present
- [ ] Range checks on all inputs
- [ ] Buffer overflow prevention
- [ ] Integer overflow checks
- [ ] Division by zero checks
- [ ] All outputs validated before return
- [ ] Error handling comprehensive

## 3. Complexity
- [ ] Cyclomatic complexity within limit (10/15/20 by SIL)
- [ ] Function length reasonable (< 100 lines recommended)
- [ ] Nesting depth acceptable (< 4 levels)
- [ ] Single responsibility per function
- [ ] Clear, understandable logic

## 4. Error Handling
- [ ] All functions return error status
- [ ] Error codes defined in enum
- [ ] Errors propagated correctly
- [ ] Safety-critical errors handled immediately
- [ ] Error logging present
- [ ] Recovery mechanisms implemented

## 5. Documentation
- [ ] File header with purpose and author
- [ ] Function comments (purpose, params, returns)
- [ ] Complex algorithms explained
- [ ] Safety-critical sections marked
- [ ] MISRA deviations documented
- [ ] Traceability comments (REQ-xxx, DES-yyy)

## 6. Naming Conventions
- [ ] Clear, descriptive names
- [ ] Consistent naming style
- [ ] Type suffixes for clarity (_t for types)
- [ ] No single-letter variables (except i, j in loops)
- [ ] Constants in UPPER_CASE

## 7. Memory Safety
- [ ] All arrays have bounds checking
- [ ] Static allocation only (SIL 2+)
- [ ] No variable-length arrays
- [ ] Stack usage within limits
- [ ] No memory leaks possible

## 8. Concurrency (if applicable)
- [ ] Shared data protected (interrupts disabled/mutexes)
- [ ] Volatile keyword for shared variables
- [ ] No race conditions
- [ ] Atomic operations where needed
- [ ] Critical sections minimized

## 9. Testing
- [ ] Unit tests exist
- [ ] Tests cover normal cases
- [ ] Tests cover boundary cases
- [ ] Tests cover error cases
- [ ] Test coverage meets SIL requirements

## 10. Traceability
- [ ] Requirements traced (REQ-xxx in comments)
- [ ] Design elements traced (DES-yyy in comments)
- [ ] Test cases referenced

## Issues Found
| Severity | Line | Issue | Resolution |
|----------|------|-------|------------|
| Critical |      |       |            |
| Major    |      |       |            |
| Minor    |      |       |            |

**Severity Definitions**:
- **Critical**: Safety impact, must fix before merge
- **Major**: Violates EN 50128/MISRA, must fix before merge
- **Minor**: Code quality issue, should fix

## Review Decision
[ ] APPROVED - No issues or all issues resolved
[ ] APPROVED WITH CONDITIONS - Minor issues, fix before next review
[ ] REJECTED - Critical/major issues, re-review required

## Reviewer Signature
Reviewer: _________________ Date: _______
```

### Code Review Example: C Function

```c
// BEFORE CODE REVIEW - Issues present

#include <stdlib.h>  // Issue: Uses malloc

int process_data(int* data, int size) {  // Issue: int instead of fixed-width
    int* result = malloc(size * sizeof(int));  // Issue: Dynamic allocation
    
    for (int i = 0; i < size; i++) {  // Issue: No bounds check
        result[i] = data[i] * 2;  // Issue: No overflow check
    }
    
    return result;  // Issue: Returns pointer, memory leak risk
}

// AFTER CODE REVIEW - Issues fixed

#include <stdint.h>
#include <stdbool.h>
#include "error_codes.h"

/**
 * Process data by doubling each value
 * 
 * @param[in]  input   Input data array
 * @param[in]  size    Number of elements
 * @param[out] output  Output data array (must be pre-allocated)
 * @return Error code (SUCCESS or error)
 * 
 * Traceability: REQ-PROC-001, DES-PROC-005
 */
error_t process_data(
    const uint32_t* input,
    uint32_t size,
    uint32_t* output
) {
    // Pre-condition: Validate pointers
    if ((input == NULL) || (output == NULL)) {
        return ERROR_NULL_POINTER;
    }
    
    // Pre-condition: Validate size
    if ((size == 0U) || (size > MAX_ARRAY_SIZE)) {
        return ERROR_INVALID_SIZE;
    }
    
    // Process each element with overflow check
    for (uint32_t i = 0U; i < size; i++) {
        // Check for overflow before multiplication
        if (input[i] > (UINT32_MAX / 2U)) {
            return ERROR_OVERFLOW;
        }
        
        output[i] = input[i] * 2U;
    }
    
    return SUCCESS;
}
```

### Review Comments Example

```
Review: process_data() function
Reviewer: Jane Smith
Date: 2024-01-15

CRITICAL ISSUES:
1. Line 5: Dynamic memory allocation (malloc) - FORBIDDEN for SIL 2+
   Resolution: Use static allocation or caller-provided buffer
   
2. Line 11: Memory leak - allocated memory never freed
   Resolution: See resolution for issue 1

MAJOR ISSUES:
3. Line 3: Non-fixed-width type 'int' used
   Resolution: Change to uint32_t or appropriate fixed-width type
   
4. Line 8: No integer overflow check before multiplication
   Resolution: Add overflow check: if (data[i] > INT_MAX/2)
   
5. Line 5: No NULL pointer check for 'data' parameter
   Resolution: Add validation at function entry

MINOR ISSUES:
6. Missing function documentation comment
   Resolution: Add Doxygen-style comment with params and return

7. Line 7: No bounds checking on array access
   Resolution: Add size validation (size > 0 && size <= MAX_SIZE)

RECOMMENDATION: REJECT - Must fix critical and major issues, then re-review
```

## Design Review Process

### Design Review Checklist

```markdown
# Design Review Checklist - EN 50128

## Design Information
- Component: [Name]
- Designer: [Name]
- Reviewers: [Names]
- Date: [Date]
- SIL Level: [0-4]

## 1. Requirements Traceability
- [ ] All requirements allocated to design elements
- [ ] Each design element traces to requirement(s)
- [ ] Traceability matrix complete and accurate
- [ ] No orphan design elements

## 2. Architecture
- [ ] Modular design with clear separation
- [ ] Interfaces clearly specified
- [ ] Dependencies minimized
- [ ] Safety functions isolated
- [ ] Hardware abstraction appropriate

## 3. Complexity Management
- [ ] Estimated cyclomatic complexity within limits
- [ ] Functions have single responsibility
- [ ] Control flow clear and simple
- [ ] No deep nesting anticipated

## 4. Memory Management (Critical for C)
- [ ] Static allocation strategy defined
- [ ] Memory budgets specified
- [ ] Stack usage estimated and acceptable
- [ ] No dynamic allocation planned (SIL 2+)

## 5. Error Handling Design
- [ ] Error types defined (error_t enum)
- [ ] Error propagation strategy clear
- [ ] Recovery mechanisms specified
- [ ] Safe states defined

## 6. Safety Design
- [ ] Hazards identified and addressed
- [ ] Fault detection mechanisms specified
- [ ] Redundancy where required
- [ ] Fail-safe behavior defined
- [ ] Watchdog implementation planned

## 7. Interface Design
- [ ] Input validation specified
- [ ] Output ranges defined
- [ ] Hardware interfaces specified
- [ ] Communication protocols defined
- [ ] Error conditions handled

## 8. Performance Design
- [ ] Worst-case execution time estimated
- [ ] Real-time constraints identified
- [ ] Resource usage estimated
- [ ] Optimization approach defined

## 9. Testability
- [ ] Design supports unit testing
- [ ] Test points identified
- [ ] Coverage achievable
- [ ] Debugging support included

## 10. Documentation
- [ ] Software Architecture Specification (SAS) complete
- [ ] Software Design Specification (SDS) complete
- [ ] Interface Control Documents (ICD) complete
- [ ] Design rationale documented

## Review Decision
[ ] APPROVED
[ ] APPROVED WITH CONDITIONS
[ ] REJECTED

## Reviewers
- Requirements Engineer: __________ Date: ____
- Safety Engineer: _______________ Date: ____
- QA Engineer: ___________________ Date: ____
```

## Process Audit Checklist

```markdown
# EN 50128 Process Audit Checklist

## Audit Information
- Project: [Name]
- Audit Date: [Date]
- Auditor: [Name]
- Phase: [Requirements/Design/Implementation/Testing]
- SIL Level: [0-4]

## 1. Software Development Lifecycle Compliance
- [ ] Lifecycle model documented and followed
- [ ] Phase entry/exit criteria defined
- [ ] Phase reviews conducted
- [ ] Documentation per EN 50128 Table A.1

## 2. Requirements Management
- [ ] SRS exists and approved
- [ ] Requirements have unique IDs
- [ ] SIL levels assigned
- [ ] Traceability matrix maintained
- [ ] Change control process followed

## 3. Design Management
- [ ] SAS and SDS exist and approved
- [ ] Design reviews conducted
- [ ] Traceability to requirements
- [ ] Complexity limits adhered to

## 4. Implementation
- [ ] Coding standards defined (MISRA C)
- [ ] Code reviews conducted for all code
- [ ] Static analysis performed
- [ ] Unit tests developed
- [ ] Coverage requirements met

## 5. Testing
- [ ] Test plans approved
- [ ] Test cases traceable to requirements
- [ ] All tests executed
- [ ] Coverage measured and acceptable
- [ ] Defects tracked to closure

## 6. Verification
- [ ] Verification plan exists
- [ ] Independent verification (SIL 3-4)
- [ ] Static analysis performed
- [ ] Results documented

## 7. Validation
- [ ] Validation plan exists
- [ ] Independent validation (SIL 3-4)
- [ ] Customer involvement
- [ ] Results documented

## 8. Configuration Management
- [ ] SCMP exists and followed
- [ ] Version control used
- [ ] Baselines defined
- [ ] Change control active

## 9. Quality Assurance
- [ ] SQAP exists and followed
- [ ] Reviews conducted
- [ ] Metrics collected
- [ ] Non-conformances tracked

## 10. Safety
- [ ] Safety plan exists
- [ ] Hazard analysis performed
- [ ] Safety requirements defined
- [ ] Safety case developed

## 11. Documentation
- [ ] All mandatory documents exist
- [ ] Documents approved
- [ ] Documents under version control
- [ ] Traceability complete

## 12. Tool Qualification (if applicable)
- [ ] Tools identified and assessed
- [ ] Tool qualification performed if required
- [ ] Tool usage documented

## Findings
| ID | Type | Description | Severity | Action Required |
|----|------|-------------|----------|-----------------|
|    |      |             |          |                 |

**Severity**:
- **Critical**: Major non-compliance, stop development
- **Major**: Significant issue, must fix before next phase
- **Minor**: Process improvement opportunity

## Audit Conclusion
- Compliant: YES / NO
- Findings: [Count by severity]
- Follow-up Required: YES / NO

## Auditor Signature
Auditor: _________________ Date: _______
```

## Quality Metrics

### Metrics Collection Script

```python
#!/usr/bin/env python3
"""Collect EN 50128 quality metrics."""

import subprocess
import re
import json
from datetime import datetime

class QualityMetrics:
    def __init__(self, source_dir, sil_level):
        self.source_dir = source_dir
        self.sil_level = sil_level
        self.metrics = {}
    
    def collect_all_metrics(self):
        """Collect all quality metrics."""
        print("=== Collecting Quality Metrics ===\n")
        
        self.collect_complexity_metrics()
        self.collect_misra_compliance()
        self.collect_coverage_metrics()
        self.collect_code_metrics()
        
        self.save_metrics()
        self.print_summary()
    
    def collect_complexity_metrics(self):
        """Collect cyclomatic complexity."""
        print("Collecting complexity metrics...")
        result = subprocess.run(
            ['lizard', self.source_dir],
            capture_output=True,
            text=True
        )
        
        # Parse lizard output
        avg_ccn_match = re.search(r'Average CCN: ([\d.]+)', result.stdout)
        max_ccn_match = re.search(r'Max CCN: (\d+)', result.stdout)
        
        limits = {0: 20, 1: 20, 2: 15, 3: 10, 4: 10}
        limit = limits.get(self.sil_level, 10)
        
        self.metrics['complexity'] = {
            'average_ccn': float(avg_ccn_match.group(1)) if avg_ccn_match else 0,
            'max_ccn': int(max_ccn_match.group(1)) if max_ccn_match else 0,
            'limit': limit,
            'compliant': (int(max_ccn_match.group(1)) <= limit) if max_ccn_match else False
        }
    
    def collect_misra_compliance(self):
        """Collect MISRA C compliance rate."""
        print("Collecting MISRA compliance...")
        result = subprocess.run(
            ['cppcheck', '--addon=misra', '--quiet', self.source_dir],
            capture_output=True,
            text=True
        )
        
        violations = len(result.stderr.split('\n')) - 1
        
        self.metrics['misra'] = {
            'violations': violations,
            'compliant': (violations == 0)
        }
    
    def collect_coverage_metrics(self):
        """Collect test coverage."""
        print("Collecting coverage metrics...")
        if not subprocess.run(['which', 'lcov'], capture_output=True).returncode == 0:
            self.metrics['coverage'] = {'available': False}
            return
        
        result = subprocess.run(
            ['lcov', '--summary', 'coverage.info'],
            capture_output=True,
            text=True
        )
        
        lines_match = re.search(r'lines\.*:\s+([\d.]+)%', result.stdout)
        branches_match = re.search(r'branches\.*:\s+([\d.]+)%', result.stdout)
        
        requirements = {
            0: {'statement': 80, 'branch': 70},
            1: {'statement': 90, 'branch': 80},
            2: {'statement': 100, 'branch': 100},
            3: {'statement': 100, 'branch': 100},
            4: {'statement': 100, 'branch': 100}
        }
        
        req = requirements.get(self.sil_level, {'statement': 100, 'branch': 100})
        
        line_cov = float(lines_match.group(1)) if lines_match else 0
        branch_cov = float(branches_match.group(1)) if branches_match else 0
        
        self.metrics['coverage'] = {
            'statement': line_cov,
            'branch': branch_cov,
            'required_statement': req['statement'],
            'required_branch': req['branch'],
            'compliant': (line_cov >= req['statement'] and branch_cov >= req['branch'])
        }
    
    def collect_code_metrics(self):
        """Collect basic code metrics."""
        print("Collecting code metrics...")
        result = subprocess.run(
            ['cloc', '--json', self.source_dir],
            capture_output=True,
            text=True
        )
        
        try:
            cloc_data = json.loads(result.stdout)
            c_data = cloc_data.get('C', {})
            
            self.metrics['code'] = {
                'files': c_data.get('nFiles', 0),
                'lines': c_data.get('code', 0),
                'comments': c_data.get('comment', 0),
                'comment_ratio': c_data.get('comment', 0) / c_data.get('code', 1) * 100
            }
        except:
            self.metrics['code'] = {'available': False}
    
    def save_metrics(self):
        """Save metrics to file."""
        self.metrics['timestamp'] = datetime.now().isoformat()
        self.metrics['sil_level'] = self.sil_level
        
        with open('quality_metrics.json', 'w') as f:
            json.dump(self.metrics, f, indent=2)
    
    def print_summary(self):
        """Print metrics summary."""
        print("\n=== Quality Metrics Summary ===")
        
        if 'complexity' in self.metrics:
            m = self.metrics['complexity']
            print(f"\nComplexity:")
            print(f"  Average CCN: {m['average_ccn']:.1f}")
            print(f"  Max CCN: {m['max_ccn']} (limit: {m['limit']})")
            print(f"  Status: {'PASS' if m['compliant'] else 'FAIL'}")
        
        if 'misra' in self.metrics:
            m = self.metrics['misra']
            print(f"\nMISRA C Compliance:")
            print(f"  Violations: {m['violations']}")
            print(f"  Status: {'PASS' if m['compliant'] else 'FAIL'}")
        
        if 'coverage' in self.metrics and self.metrics['coverage'].get('available', True):
            m = self.metrics['coverage']
            print(f"\nTest Coverage:")
            print(f"  Statement: {m['statement']:.1f}% (required: {m['required_statement']}%)")
            print(f"  Branch: {m['branch']:.1f}% (required: {m['required_branch']}%)")
            print(f"  Status: {'PASS' if m['compliant'] else 'FAIL'}")
        
        if 'code' in self.metrics and self.metrics['code'].get('available', True):
            m = self.metrics['code']
            print(f"\nCode Metrics:")
            print(f"  Files: {m['files']}")
            print(f"  Lines of Code: {m['lines']}")
            print(f"  Comment Ratio: {m['comment_ratio']:.1f}%")

if __name__ == '__main__':
    import sys
    if len(sys.argv) != 3:
        print("Usage: collect_metrics.py <source_dir> <sil_level>")
        sys.exit(1)
    
    metrics = QualityMetrics(sys.argv[1], int(sys.argv[2]))
    metrics.collect_all_metrics()
```

## Non-Conformance Management

### Non-Conformance Report Template

```markdown
# Non-Conformance Report

## NCR Information
- NCR ID: NCR-[Year]-[Number]
- Date Raised: [Date]
- Raised By: [Name]
- Project: [Name]
- Phase: [Requirements/Design/Implementation/Testing]
- SIL Level: [0-4]

## Non-Conformance Details
### Description
[Clear description of the non-conformance]

### Standard/Requirement Violated
[EN 50128 section / MISRA rule / Project requirement]

### Location
- Document/File: [Name]
- Section/Line: [Location]

### Severity
[ ] Critical - Safety impact or major standard violation
[ ] Major - Significant issue, affects quality/compliance
[ ] Minor - Process deviation, quality improvement

## Impact Assessment
### Safety Impact
[Assessment of safety implications]

### Quality Impact
[Assessment of quality implications]

### Schedule Impact
[Assessment of schedule implications]

## Root Cause Analysis
### Immediate Cause
[What directly caused the issue]

### Root Cause
[Underlying cause - process, training, tools, etc.]

### Contributing Factors
[Other factors that contributed]

## Corrective Action
### Immediate Action
[Action taken to address this instance]

### Preventive Action
[Action to prevent recurrence]

### Process Improvement
[Changes to processes/procedures]

## Verification
### Verification Method
[How effectiveness will be verified]

### Verification Result
[Result of verification - filled after implementation]

## Closure
- Corrective Action Completed: [Date]
- Verified By: [Name]
- Approved for Closure: [Name]
- Closure Date: [Date]

## Approvals
- QA Manager: _________________ Date: _______
- Project Manager: ____________ Date: _______
```

## Quality Gates

### Phase Exit Quality Gate

```python
#!/usr/bin/env python3
"""EN 50128 Quality Gate Check."""

import sys

class QualityGate:
    def __init__(self, phase, sil_level):
        self.phase = phase
        self.sil_level = sil_level
        self.checks = []
        self.passed = True
    
    def check_requirements_phase(self):
        """Quality gate for requirements phase."""
        self.checks = [
            ("All requirements reviewed and approved", self.check_file_exists("srs_approval.txt")),
            ("Traceability matrix complete", self.check_file_exists("traceability.csv")),
            ("SIL levels assigned", self.check_sil_assigned()),
        ]
    
    def check_implementation_phase(self):
        """Quality gate for implementation phase."""
        self.checks = [
            ("All code reviewed", self.check_code_reviews()),
            ("MISRA C compliance", self.check_misra_compliance()),
            ("Complexity within limits", self.check_complexity()),
            ("Unit tests pass", self.check_unit_tests()),
            ("Coverage requirements met", self.check_coverage()),
        ]
    
    def check_code_reviews(self):
        """Check that all code has been reviewed."""
        # Implementation: Check that review records exist for all source files
        return True  # Placeholder
    
    def check_misra_compliance(self):
        """Check MISRA C compliance."""
        import subprocess
        result = subprocess.run(
            ['cppcheck', '--addon=misra', '--quiet', 'src/'],
            capture_output=True
        )
        return len(result.stderr) == 0
    
    def check_complexity(self):
        """Check cyclomatic complexity."""
        limits = {0: 20, 1: 20, 2: 15, 3: 10, 4: 10}
        limit = limits.get(self.sil_level, 10)
        
        import subprocess
        result = subprocess.run(
            ['lizard', '--CCN', str(limit), '--warnings_only', 'src/'],
            capture_output=True
        )
        return result.returncode == 0
    
    def evaluate(self):
        """Evaluate quality gate."""
        print(f"=== Quality Gate: {self.phase} (SIL {self.sil_level}) ===\n")
        
        # Run appropriate checks
        if self.phase == "requirements":
            self.check_requirements_phase()
        elif self.phase == "implementation":
            self.check_implementation_phase()
        
        # Print results
        for check_name, result in self.checks:
            status = "PASS" if result else "FAIL"
            print(f"{check_name}: {status}")
            if not result:
                self.passed = False
        
        print(f"\nQuality Gate: {'PASSED' if self.passed else 'FAILED'}")
        
        return 0 if self.passed else 1

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: quality_gate.py <phase> <sil_level>")
        sys.exit(1)
    
    gate = QualityGate(sys.argv[1], int(sys.argv[2]))
    sys.exit(gate.evaluate())
```

## References

- EN 50128:2011 Section 6.3 (Software Quality Assurance)
- EN 50128:2011 Table A.20 (Software Quality Assurance Techniques)
- ISO 9001 (Quality Management)
- MISRA C:2012 (Coding Standard)
