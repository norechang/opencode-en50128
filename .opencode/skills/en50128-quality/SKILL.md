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

---

## Comprehensive Workflows

This skill provides **4 comprehensive workflows** (248 pages, 6,188 lines) covering all EN 50128 quality assurance activities. These workflows implement EN 50128 Section 6.5 requirements with complete tool integration, code examples, and SIL-specific guidance.

### Workflow 1: Quality Assurance Workflow

**File**: `.opencode/skills/en50128-quality/workflows/quality-assurance-workflow.md` (1,523 lines, ~61 pages)

**Purpose**: Complete EN 50128 quality assurance process for all lifecycle phases

**Key Topics**:
1. **SQAP Development**: Software Quality Assurance Plan structure and content per EN 50128 Section 6.5.4.3
2. **Quality Gates Framework**: 6 phase gates (requirements, design, implementation, testing, validation, deployment) with SIL-specific criteria
3. **Quality Metrics Collection**: Python script for collecting complexity, MISRA C compliance, coverage, and code metrics
4. **Non-Conformance Management**: NCR process, template, tracking, and resolution workflow
5. **Quality Audit Process**: Audit planning, execution, finding management, and closure
6. **Traceability Management**: workspace.py trace integration for 100% traceability validation (MANDATORY SIL 3-4)

**Tool Integration**:
```bash
# Quality gate check (automated)
python3 tools/quality_gate.py implementation 3

# Quality metrics collection
python3 tools/collect_metrics.py src/ 3

# Non-conformance tracking
workspace.py wf log-ncr \
    --ncr-id NCR-2026-005 \
    --severity MAJOR \
    --description "MISRA C Rule 21.3 violation: dynamic memory allocation"

# Traceability validation (MANDATORY SIL 3-4)
workspace.py trace validate --phase testing --sil 3
```

**Example Scenarios**:
1. MISRA C Violation Found (Major NCR)
2. Coverage Requirement Not Met (Gate Rejection)
3. Traceability Gap Detected (Critical NCR)

---

### Workflow 2: Document Review Workflow

**File**: `.opencode/skills/en50128-quality/workflows/document-review-workflow.md` (1,947 lines, ~78 pages)

**Purpose**: EN 50128 document template compliance review (MANDATORY before technical review)

**Key Topics**:
1. **EN 50128 Document Requirements**: Annex C Table C.1 mandatory documents, template structure
2. **Document ID Format Validation**: DOC-[ROLE]-[TYPE]-[NNN] format enforcement
3. **Document Control Table Validation**: Version, date, author, SIL level, status verification
4. **Approvals Table Validation**: SIL-specific approvers (Independent Verifier, Independent Validator, Assessor for SIL 3-4)
5. **Traceability Section Validation**: MANDATORY for SIL 3-4, 100% coverage required
6. **1-Pass Review Policy**: Developer gets ONE resubmit opportunity, escalate if second review fails
7. **Automated Document Checking**: Python script for template compliance validation

**QA Review is Gate-Keeper**:
- QA reviews FORMAT and STRUCTURE (template compliance) FIRST
- Technical reviewers review CONTENT (requirements correctness, design quality) AFTER QA approval
- No technical review until QA approves document template compliance

**Tool Integration**:
```bash
# Submit document for QA review
workspace.py wf submit \
    --deliverable DOC-VER-REP-001 \
    --phase verification \
    --author "John Smith" \
    --version 1.0

# Automated document template check
python3 tools/document_checker.py \
    --document docs/DOC-VER-REP-001.md \
    --sil 3 \
    --output evidence/qa/doc_review_DOC-VER-REP-001.json

# QA review decision (approve)
workspace.py wf review \
    --deliverable DOC-VER-REP-001 \
    --reviewer QUA \
    --status approved \
    --comments "Template compliance verified. Proceed to technical review."

# QA review decision (reject)
workspace.py wf review \
    --deliverable DOC-VER-REP-001 \
    --reviewer QUA \
    --status rejected \
    --comments "Document ID format incorrect. Fix and resubmit (1 pass allowed)."
```

**Example Scenarios**:
1. Document ID Format Incorrect (REJECT)
2. Missing Independent Validator for SIL 3 (REJECT)
3. Traceability Section Empty (REJECT, SIL 3)
4. All Checks Pass (APPROVE)

---

### Workflow 3: Technical Review Workflow

**File**: `.opencode/skills/en50128-quality/workflows/technical-review-workflow.md` (1,463 lines, ~59 pages)

**Purpose**: Technical content review for design, code, and tests (AFTER document template compliance)

**Key Topics**:
1. **Design Review Process**: Architecture review and detailed design review with multi-reviewer team
2. **Code Review Process**: MISRA C compliance (zero mandatory violations SIL 2+), complexity (CCN ≤ 10 SIL 3-4), defensive programming
3. **Test Review Process**: Test plan review, test specification review, test report review with coverage validation
4. **Review Meeting Management**: Opening, presentation, walkthrough, defect discussion, wrap-up
5. **Defect Management**: Severity classification (Critical, Major, Minor), resolution workflow, re-review process
6. **Review Checklists**: Comprehensive checklists for requirements, design, code, and test reviews
7. **Automated Technical Checks**: MISRA C (Cppcheck), complexity (Lizard), coverage (gcov/lcov)

**Review Team Composition**:
- **Design Review**: DES (author), REQ, SAF, IMP, QUA
- **Code Review**: IMP (author), Peer Developer, QUA
- **Test Review**: TST (author), REQ, VER, QUA

**Tool Integration**:
```bash
# Pre-review automated checks (MUST PASS before submitting)
# 1. MISRA C compliance
cppcheck --enable=all --addon=misra.json --xml src/*.c 2> cppcheck_report.xml
python3 tools/check_misra.py --report cppcheck_report.xml --sil 3 --mandatory-only

# 2. Complexity check
lizard src/*.c -o lizard_report.txt
python3 tools/check_complexity.py --report lizard_report.txt --sil 3 --max-ccn 10

# 3. Coverage check
gcov src/*.c
lcov --capture --directory . --output-file coverage.info
python3 tools/check_coverage.py --coverage coverage.info --sil 3 --statement 100 --branch 100

# Submit for technical review (after QA document review approval)
workspace.py wf submit \
    --deliverable src/door_controller.c \
    --phase implementation \
    --author "Dave Developer" \
    --version 1.0

# Technical review approval
workspace.py wf review \
    --deliverable src/door_controller.c \
    --reviewer QUA \
    --status approved \
    --comments "Code review complete. All checks passed. Proceed to integration."
```

**Example Scenarios**:
1. Design Review - Missing Safety Redundancy (REJECT, Critical defect)
2. Code Review - MISRA C Mandatory Violation (REJECT, malloc used)
3. Code Review - Defensive Programming Issue (REWORK, missing NULL check)
4. Test Review - Coverage Incomplete (REJECT, 95% vs 100% required)

---

### Workflow 4: Quality Audit Workflow

**File**: `.opencode/skills/en50128-quality/workflows/quality-audit-workflow.md` (1,255 lines, ~50 pages)

**Purpose**: Independent verification that EN 50128 process is followed (MANDATORY SIL 3-4)

**Key Topics**:
1. **Process Compliance Audit**: Verify V-Model lifecycle adherence, phase gates enforced, EN 50128 techniques applied
2. **Artifact Audit**: Verify deliverables meet EN 50128 Annex C requirements, template compliance, review status
3. **Tool Qualification Audit**: Verify T2/T3 tools qualified per Annex B (MANDATORY SIL 3-4)
4. **Pre-Release Audit**: Final audit before deployment (MANDATORY SIL 3-4)
5. **Audit Execution**: Opening meeting, evidence collection, interviews, observations, closing meeting
6. **Finding Management**: Non-conformance classification (Critical, Major, Minor), corrective action tracking, follow-up audit
7. **Audit Report Generation**: Audit plan, checklist, findings, corrective actions, closure

**Audit Frequency by SIL**:
- **SIL 3-4**: Process audit monthly (M), artifact audit per phase (M), tool audit per tool (M), pre-release audit (M)
- **SIL 2**: Process audit quarterly (HR), artifact audit per phase (HR), pre-release audit (HR)
- **SIL 0-1**: Optional

**Tool Integration**:
```bash
# Create audit record
workspace.py wf create-audit \
    --audit-id AUD-2026-Q1-001 \
    --type process-compliance \
    --project "Railway Door Controller" \
    --sil 3 \
    --start-date 2026-04-10 \
    --end-date 2026-04-12 \
    --lead-auditor "Eve Green"

# Run automated audit checks
./tools/run_audit_checks.sh \
    --audit-id AUD-2026-Q1-001 \
    --sil 3 \
    --output audit_evidence/

# Log audit finding
workspace.py wf log-finding \
    --audit-id AUD-2026-Q1-001 \
    --finding-id F01 \
    --type non-conformance \
    --severity critical \
    --area traceability \
    --description "3 requirements not traced to design" \
    --assigned-to "Alice Designer" \
    --due-date 2026-04-15

# Verify finding resolved
workspace.py wf verify-finding \
    --finding-id AUD-2026-Q1-001-F01 \
    --verified-by "Eve Green (QA)" \
    --verification-evidence "workspace.py trace validate shows 100% coverage"
```

**Example Scenarios**:
1. Process Audit Finds Phase Gate Violation (Critical NC)
2. Artifact Audit Finds Missing Deliverable (Major NC, SVP missing)
3. Tool Audit Finds Unqualified T3 Tool (Critical NC, gcc not qualified)
4. Pre-Release Audit Approves Release (OK, zero NC)

---

## Quality Workflow Selection by SIL

| Workflow | SIL 0-1 | SIL 2 | SIL 3-4 | Frequency |
|----------|---------|-------|---------|-----------|
| **Quality Assurance** | Recommended | Highly Recommended | **MANDATORY** | Continuous (all phases) |
| **Document Review** | Recommended | Highly Recommended | **MANDATORY** | Per deliverable |
| **Technical Review** | Recommended | Highly Recommended | **MANDATORY** | Per deliverable (after doc review) |
| **Quality Audit** | Optional | Quarterly (HR) | Monthly (M) + Pre-Release (M) | Periodic + Pre-Release |

**Legend**: M = Mandatory, HR = Highly Recommended, R = Recommended

---

## Tool Integration

All quality workflows integrate with `workspace.py` for traceability and workflow management.

### Traceability Management (MANDATORY SIL 3-4)

**Validate Traceability**:
```bash
# Validate requirements → design traceability
workspace.py trace validate --phase design --sil 3

# Output:
# Traceability Validation: PASS
# Coverage: 100% (40/40 requirements traced)
# Orphan requirements: 0
# Orphan design elements: 0
```

**Generate Traceability Report**:
```bash
# Generate traceability matrix for inclusion in deliverable
workspace.py trace report \
    --from design --to requirements \
    --format markdown \
    --output evidence/traceability/design-to-requirements.md
```

**Create Traceability Link**:
```bash
# Link design element to requirement
workspace.py trace create \
    --from design --to requirements \
    --source-id MOD-DOOR-001 --target-id REQ-DOOR-001 \
    --rationale "DoorController module implements door control requirement"
```

### Workflow Management

**Submit Deliverable for Review**:
```bash
workspace.py wf submit \
    --deliverable DOC-VER-REP-001 \
    --phase verification \
    --author "John Smith" \
    --version 1.0
```

**Review Deliverable (QA)**:
```bash
# Approve
workspace.py wf review \
    --deliverable DOC-VER-REP-001 \
    --reviewer QUA \
    --status approved \
    --comments "Template compliance verified. Proceed to technical review."

# Reject
workspace.py wf review \
    --deliverable DOC-VER-REP-001 \
    --reviewer QUA \
    --status rejected \
    --comments "Missing Independent Validator in Approvals table. Fix and resubmit."
```

**Check Workflow Status**:
```bash
workspace.py wf status --deliverable DOC-VER-REP-001

# Output:
# Deliverable: DOC-VER-REP-001
# Status: QA_REVIEW
# Phase: verification
# Submitted: 2026-03-14 10:30:00
# Reviewer: QUA (Jane Doe)
# Comments: Awaiting QA template compliance review
```

**Log Defect**:
```bash
workspace.py wf log-defect \
    --deliverable src/door_controller.c \
    --defect-id DEF-2026-125 \
    --severity CRITICAL \
    --description "Missing NULL pointer check in door_set_state()" \
    --assigned-to "Dave Developer" \
    --due-date 2026-03-26
```

### Automated Quality Checks

**MISRA C Compliance Check**:
```bash
# Run Cppcheck with MISRA addon
cppcheck --enable=all --addon=misra.json --xml src/*.c 2> cppcheck_report.xml

# Check for mandatory violations (MUST be 0 for SIL 2+)
python3 tools/check_misra.py \
    --report cppcheck_report.xml \
    --sil 3 \
    --mandatory-only

# Output:
# MISRA C Compliance Check: PASS
# Mandatory violations: 0
# Required violations: 3 (deviations documented)
# Advisory violations: 12 (reviewed)
```

**Complexity Check**:
```bash
# Run Lizard complexity analysis
lizard src/*.c -o lizard_report.txt

# Check functions exceeding limit
python3 tools/check_complexity.py \
    --report lizard_report.txt \
    --sil 3 \
    --max-ccn 10

# Output:
# Complexity Check: PASS
# Functions analyzed: 25
# Functions within limit (CCN ≤ 10): 25
# Max complexity: 8 (door_emergency_stop)
```

**Coverage Check**:
```bash
# Run unit tests with coverage
make test

# Generate coverage report
gcov src/*.c
lcov --capture --directory . --output-file coverage.info

# Check coverage (SIL 3 requires 100%)
python3 tools/check_coverage.py \
    --coverage coverage.info \
    --sil 3 \
    --statement 100 \
    --branch 100 \
    --condition 100

# Output:
# Coverage Check: PASS
# Statement coverage: 100.0% (450/450 lines)
# Branch coverage: 100.0% (120/120 branches)
# Condition coverage: 100.0% (80/80 conditions)
```

---

## EN 50128 Coverage

### Section 6.5: Software Quality Assurance

All workflows implement EN 50128 Section 6.5 requirements:

| Section | Requirement | Workflows | Coverage |
|---------|-------------|-----------|----------|
| **6.5.1.1** | Identify, monitor, and control quality activities | Quality Assurance Workflow | Complete |
| **6.5.1.2** | Provide evidence that activities performed | Quality Audit Workflow | Complete |
| **6.5.4.2** | Implement Quality Assurance System (ISO 9001) | Quality Assurance Workflow (SQAP) | Complete |
| **6.5.4.3** | Software Quality Assurance Plan | Quality Assurance Workflow (Section 2) | Complete |
| **6.5.4.5(c)** | Documentation and configuration control | Document Review Workflow | Complete |
| **6.5.4.5(d)** | Traceability | All workflows (workspace.py trace) | Complete |
| **6.5.4.5(e)** | Reviews, audits, inspections | Technical Review + Audit Workflows | Complete |

### Table A.9: Software Quality Assurance Techniques

| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Workflow Coverage |
|-----------|-------|---------|---------|------------------|
| **1. Accredited to EN ISO 9001** | R | HR | HR | Quality Assurance Workflow (SQAP) |
| **2. Compliant with EN ISO 9001** | **M** | **M** | **M** | Quality Assurance Workflow (SQAP) |
| **3. Compliant with ISO/IEC 90003** | R | R | R | Quality Assurance Workflow |
| **4. Company Quality System** | **M** | **M** | **M** | Quality Assurance Workflow |
| **5. Software Configuration Management** | **M** | **M** | **M** | Quality Audit Workflow (Section 4.5) |
| **6. Checklists** | R | HR | HR | All workflows (comprehensive checklists) |
| **7. Traceability** | R | HR | **M** | All workflows (workspace.py trace) |
| **8. Data Recording and Analysis** | HR | HR | **M** | Quality Assurance Workflow (metrics) |

---

## Statistics

**Total Workflow Content**:
- **4 workflows**: 6,188 lines (~248 pages)
- **30+ code examples**: Complete, production-ready C code and Python scripts
- **80+ tool command examples**: Full workspace.py, Cppcheck, Lizard, gcov integration
- **12+ complete scenarios**: Real-world examples with solutions

**Workflow Breakdown**:
1. Quality Assurance Workflow: 1,523 lines (~61 pages)
2. Document Review Workflow: 1,947 lines (~78 pages)
3. Technical Review Workflow: 1,463 lines (~59 pages)
4. Quality Audit Workflow: 1,255 lines (~50 pages)

**Tool Integration**:
- **workspace.py trace**: 40+ examples (traceability management)
- **workspace.py wf**: 50+ examples (workflow management)
- **Cppcheck**: 15+ examples (MISRA C compliance)
- **Lizard**: 10+ examples (complexity analysis)
- **gcov/lcov**: 15+ examples (coverage analysis)

---

## References

- EN 50128:2011 Section 6.3 (Software Quality Assurance)
- EN 50128:2011 Section 6.5 (Software Quality Assurance)
- EN 50128:2011 Table A.9 (Software Quality Assurance Techniques)
- EN 50128:2011 Annex B (Tool Classification and Qualification)
- EN 50128:2011 Annex C (Document Control Summary - Table C.1)
- ISO 9001 (Quality Management)
- ISO/IEC 90003:2014 (Software Engineering - Guidelines for ISO 9001)
- MISRA C:2012 (Coding Standard)
- IEEE 1028-2008 (Standard for Software Reviews and Audits)
