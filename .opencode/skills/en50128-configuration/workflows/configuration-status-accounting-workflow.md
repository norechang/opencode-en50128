# Configuration Status Accounting Workflow

**Skill**: en50128-configuration  
**Workflow**: Configuration Status Accounting  
**Version**: 1.0.0  
**Last Updated**: 2026-03-14

---

## Table of Contents

1. [Overview](#overview)
2. [EN 50128 Requirements](#en-50128-requirements)
3. [Configuration Item (CI) Tracking](#configuration-item-ci-tracking)
4. [Change Metrics](#change-metrics)
5. [Baseline Metrics](#baseline-metrics)
6. [Traceability Metrics](#traceability-metrics)
7. [Status Reporting](#status-reporting)
8. [Tool Integration](#tool-integration)
9. [Automation Scripts](#automation-scripts)
10. [Complete Example Scenarios](#complete-example-scenarios)

---

## Overview

### Purpose

Configuration Status Accounting (CSA) provides visibility into the state of all configuration items (CIs) throughout the software lifecycle. CSA tracks:

- **Configuration Item Status**: Which CIs exist, their versions, and current state
- **Change Status**: Change requests and their progress through the workflow
- **Baseline Status**: Which baselines have been established and their composition
- **Traceability Status**: Coverage of requirements-to-implementation traceability
- **Quality Metrics**: Trends in changes, defects, and compliance

### EN 50128 Context

Configuration Status Accounting supports:

- **Table A.9 #8**: Data Recording and Analysis (MANDATORY SIL 3-4, HR SIL 1-2)
- **Section 6.6.5**: Configuration status accounting throughout lifecycle
- **Section 6.6.3**: Configuration identification (CSA tracks all identified CIs)
- **Section 6.6.4**: Change control (CSA reports change metrics)
- **Section 6.6.6**: Configuration audits (CSA provides data for PCA/FCA)

### Key Activities

1. **CI Registry Management**: Maintain comprehensive inventory of all CIs
2. **Status Tracking**: Track CI state transitions (draft → baseline → released → obsolete)
3. **Change Metrics Collection**: Measure CR count, resolution time, categories
4. **Baseline Metrics Collection**: Measure baseline count, size, artifact composition
5. **Traceability Metrics**: Calculate requirements coverage, identify gaps
6. **Report Generation**: Produce weekly, monthly, and gate reports
7. **Trend Analysis**: Identify patterns in changes, defects, quality

### Relationship to Other Workflows

- **Version Control Workflow**: CSA tracks versions from Git repository
- **Change Control Workflow**: CSA reports CR status and metrics
- **Baseline Management Workflow**: CSA tracks baselines and composition

---

## EN 50128 Requirements

### Table A.9 #8: Data Recording and Analysis

| SIL Level | Classification | Requirements |
|-----------|----------------|--------------|
| **SIL 0** | --- | No specific requirement |
| **SIL 1-2** | **HR** (Highly Recommended) | Data recording and analysis highly recommended |
| **SIL 3-4** | **M** (MANDATORY) | Data recording and analysis MANDATORY |

**EN 50128 Section 6.6.5** states:

> "Configuration status accounting shall be maintained throughout the software lifecycle. This shall provide information on the state of baselines, the status of changes to baselines, and the implementation status of approved changes."

### Required Data for SIL 3-4

**Configuration Item Data** (MANDATORY):
- Unique CI identifier
- CI type (source, document, test, tool)
- CI version/revision
- CI status (draft, baseline, released, obsolete)
- CI owner/responsible person
- CI creation date
- CI last modified date
- CI baseline membership

**Change Data** (MANDATORY):
- CR identifier
- CR status (SUBMITTED, APPROVED, IMPLEMENTATION, VERIFICATION, CLOSED, REJECTED)
- CR type (defect, enhancement, safety)
- CR affected CIs
- CR effort (estimated vs. actual)
- CR resolution time
- CR approver/implementer

**Baseline Data** (MANDATORY):
- Baseline identifier
- Baseline date
- Baseline composition (all CIs with versions and checksums)
- Baseline phase gate
- Baseline approval status

**Traceability Data** (MANDATORY SIL 3-4):
- Requirement-to-CI mappings
- CI-to-test mappings
- Coverage percentage
- Traceability gaps

**Quality Metrics** (MANDATORY SIL 3-4):
- Defect density (defects per KLOC)
- Change rate (CRs per month)
- Requirements volatility (requirement changes per phase)
- Test coverage (statement, branch, MC/DC)
- MISRA C compliance (violations per KLOC)

### CSA Report Frequency by SIL

| Report Type | SIL 0-1 | SIL 2 | SIL 3-4 |
|-------------|---------|-------|---------|
| **Weekly Status** | Optional | Recommended | MANDATORY |
| **Monthly Summary** | Recommended | MANDATORY | MANDATORY |
| **Phase Gate Report** | MANDATORY | MANDATORY | MANDATORY |
| **Trend Analysis** | Optional | Recommended | MANDATORY |
| **Configuration Audit** | --- | Recommended | MANDATORY (PCA/FCA) |

---

## Configuration Item (CI) Tracking

### CI Registry Structure

Every project SHALL maintain a CI Registry that identifies all configuration items.

**CI Registry Format** (`config/ci-registry.json`):

```json
{
  "project": "Railway Signaling Controller",
  "sil": 3,
  "registry_version": "1.2.0",
  "last_updated": "2026-03-14T10:30:00Z",
  "configuration_items": [
    {
      "ci_id": "CI-SRC-001",
      "ci_type": "source",
      "name": "atp_controller.c",
      "path": "src/atp/atp_controller.c",
      "version": "1.3.2",
      "git_commit": "a1b2c3d4e5f6g7h8i9j0",
      "status": "baseline",
      "baseline_id": "BL-GATE4-001",
      "owner": "John Smith (IMP)",
      "created_date": "2025-11-01",
      "last_modified": "2026-02-15",
      "checksum_sha256": "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
      "size_bytes": 8192,
      "loc": 312,
      "related_requirements": ["REQ-ATP-001", "REQ-ATP-002", "REQ-ATP-005"],
      "related_tests": ["TEST-ATP-001", "TEST-ATP-002"],
      "safety_critical": true,
      "sil_level": 3
    },
    {
      "ci_id": "CI-DOC-001",
      "ci_type": "document",
      "name": "Software Requirements Specification",
      "path": "docs/software-requirements-specification.md",
      "version": "2.1.0",
      "git_commit": "b2c3d4e5f6g7h8i9j0k1",
      "status": "baseline",
      "baseline_id": "BL-GATE2-001",
      "owner": "Alice Johnson (REQ)",
      "created_date": "2025-10-01",
      "last_modified": "2026-01-20",
      "checksum_sha256": "d3e0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b866",
      "size_bytes": 245760,
      "word_count": 12500,
      "requirement_count": 87,
      "approval_status": "APPROVED",
      "approvers": ["Bob Wilson (DES)", "Carol Martinez (VER)"]
    },
    {
      "ci_id": "CI-TST-001",
      "ci_type": "test",
      "name": "test_atp_controller.c",
      "path": "tests/unit/test_atp_controller.c",
      "version": "1.2.0",
      "git_commit": "c3d4e5f6g7h8i9j0k1l2",
      "status": "baseline",
      "baseline_id": "BL-GATE4-001",
      "owner": "David Lee (TST)",
      "created_date": "2025-11-15",
      "last_modified": "2026-02-20",
      "checksum_sha256": "f4b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b877",
      "size_bytes": 6144,
      "test_cases": 24,
      "tested_requirements": ["REQ-ATP-001", "REQ-ATP-002", "REQ-ATP-005"],
      "tested_source": ["CI-SRC-001"]
    },
    {
      "ci_id": "CI-TOOL-001",
      "ci_type": "tool",
      "name": "Cppcheck",
      "version": "2.13.0",
      "qualification_status": "T2_VALIDATED",
      "qualification_evidence": "docs/tool-qualification/cppcheck-qualification.md",
      "usage": "Static analysis for MISRA C compliance",
      "owner": "VER team",
      "confidence_level": "T2"
    }
  ],
  "ci_statistics": {
    "total_cis": 234,
    "source_files": 87,
    "documents": 45,
    "test_files": 98,
    "tools": 4,
    "baseline_cis": 198,
    "draft_cis": 36,
    "obsolete_cis": 0
  }
}
```

### CI Status Definitions

| Status | Description | Allowed Transitions |
|--------|-------------|---------------------|
| **DRAFT** | CI under development, not yet reviewed | → BASELINE (via baseline establishment) |
| **BASELINE** | CI approved and included in baseline | → RELEASED (via deployment), → OBSOLETE (via change) |
| **RELEASED** | CI deployed to production | → OBSOLETE (via new version) |
| **OBSOLETE** | CI superseded by newer version | (Terminal state) |

### CI Type Classification

| CI Type | Examples | Tracking Requirements |
|---------|----------|----------------------|
| **source** | `.c`, `.h` files | Version, checksum, LOC, complexity, MISRA compliance |
| **document** | SRS, SAS, SDS, plans, reports | Version, checksum, word count, approval status |
| **test** | Unit tests, integration tests, test scripts | Version, checksum, test case count, coverage |
| **tool** | gcc, cppcheck, lcov | Version, qualification status, confidence level |
| **configuration** | Makefiles, CI/CD configs, Git hooks | Version, checksum |
| **data** | Test data, lookup tables, configuration data | Version, checksum, validation status |

### CI Tracking with workspace.py

**List All CIs**:

```bash
# List all CIs in registry
python3 tools/workspace.py trace list-cis

# Filter by type
python3 tools/workspace.py trace list-cis --type source
python3 tools/workspace.py trace list-cis --type document

# Filter by status
python3 tools/workspace.py trace list-cis --status baseline
python3 tools/workspace.py trace list-cis --status draft

# Filter by baseline
python3 tools/workspace.py trace list-cis --baseline BL-GATE4-001
```

**Add CI to Registry**:

```bash
# Add source file
python3 tools/workspace.py trace add-ci \
  --ci-id CI-SRC-042 \
  --type source \
  --path src/braking/emergency_brake.c \
  --owner "Jane Doe (IMP)" \
  --sil 3

# Add document
python3 tools/workspace.py trace add-ci \
  --ci-id CI-DOC-015 \
  --type document \
  --path docs/verification-report.md \
  --owner "Bob Wilson (VER)" \
  --sil 3
```

**Update CI Status**:

```bash
# Update status to baseline
python3 tools/workspace.py trace update-ci-status \
  --ci-id CI-SRC-042 \
  --status baseline \
  --baseline-id BL-GATE4-002

# Update status to obsolete (new version created)
python3 tools/workspace.py trace update-ci-status \
  --ci-id CI-SRC-042 \
  --status obsolete \
  --reason "Superseded by CI-SRC-043"
```

**Validate CI Registry**:

```bash
# Check for missing CIs (files in Git not in registry)
python3 tools/workspace.py trace validate-ci-registry --check-missing

# Check for orphaned CIs (CIs in registry not in Git)
python3 tools/workspace.py trace validate-ci-registry --check-orphans

# Check for checksum mismatches
python3 tools/workspace.py trace validate-ci-registry --check-checksums
```

---

## Change Metrics

### Change Request Metrics

Configuration Status Accounting tracks change request (CR) metrics to provide visibility into change activity.

**Key CR Metrics**:

1. **CR Count**: Total number of CRs by status, type, severity
2. **CR Resolution Time**: Time from SUBMITTED to CLOSED
3. **CR Backlog**: Number of open CRs (SUBMITTED, APPROVED, IMPLEMENTATION, VERIFICATION)
4. **CR Approval Rate**: Percentage of CRs approved vs. rejected
5. **CR Effort Accuracy**: Estimated effort vs. actual effort
6. **CR Category Distribution**: Breakdown by type (defect, enhancement, safety)

### Change Metrics Data Structure

**Change Metrics Format** (`reports/change-metrics.json`):

```json
{
  "report_date": "2026-03-14",
  "report_period": {
    "start_date": "2026-02-14",
    "end_date": "2026-03-14"
  },
  "project": "Railway Signaling Controller",
  "sil": 3,
  "cr_count": {
    "total": 45,
    "by_status": {
      "SUBMITTED": 8,
      "APPROVED": 5,
      "IMPLEMENTATION": 7,
      "VERIFICATION": 3,
      "CLOSED": 20,
      "REJECTED": 2
    },
    "by_type": {
      "defect": 18,
      "enhancement": 15,
      "safety": 8,
      "documentation": 4
    },
    "by_severity": {
      "critical": 3,
      "major": 12,
      "minor": 20,
      "trivial": 10
    },
    "by_phase": {
      "requirements": 5,
      "design": 8,
      "implementation": 15,
      "integration": 10,
      "validation": 7
    }
  },
  "cr_resolution_time": {
    "average_days": 12.5,
    "median_days": 10.0,
    "min_days": 2,
    "max_days": 45,
    "by_severity": {
      "critical": 3.2,
      "major": 8.5,
      "minor": 15.3,
      "trivial": 22.7
    }
  },
  "cr_backlog": {
    "total_open": 23,
    "open_by_status": {
      "SUBMITTED": 8,
      "APPROVED": 5,
      "IMPLEMENTATION": 7,
      "VERIFICATION": 3
    },
    "aging": {
      "0_7_days": 12,
      "8_14_days": 6,
      "15_30_days": 3,
      "over_30_days": 2
    }
  },
  "cr_approval_rate": {
    "total_evaluated": 43,
    "approved": 41,
    "rejected": 2,
    "approval_percentage": 95.3
  },
  "cr_effort_accuracy": {
    "total_closed_with_effort": 18,
    "average_estimated_hours": 24.5,
    "average_actual_hours": 28.3,
    "variance_percentage": 15.5,
    "underestimated": 12,
    "overestimated": 4,
    "accurate": 2
  },
  "cr_trends": {
    "monthly_cr_count": [
      {"month": "2025-12", "count": 38},
      {"month": "2026-01", "count": 42},
      {"month": "2026-02", "count": 45},
      {"month": "2026-03", "count": 45}
    ],
    "monthly_closure_rate": [
      {"month": "2025-12", "rate": 0.75},
      {"month": "2026-01", "rate": 0.68},
      {"month": "2026-02", "rate": 0.72},
      {"month": "2026-03", "rate": 0.78}
    ]
  },
  "quality_indicators": {
    "defect_density_per_kloc": 2.1,
    "change_rate_per_month": 15.0,
    "critical_defects_outstanding": 1,
    "safety_crs_outstanding": 2
  }
}
```

### CR Metrics Collection with workspace.py

**Generate Change Metrics Report**:

```bash
# Generate metrics for last 30 days
python3 tools/workspace.py wf metrics-cr --period 30

# Generate metrics for specific date range
python3 tools/workspace.py wf metrics-cr \
  --start-date 2026-02-01 \
  --end-date 2026-03-01

# Generate metrics by phase
python3 tools/workspace.py wf metrics-cr --group-by phase

# Generate metrics by severity
python3 tools/workspace.py wf metrics-cr --group-by severity
```

**Query CR Status**:

```bash
# List all open CRs
python3 tools/workspace.py wf list-cr --status open

# List CRs by age (aging backlog)
python3 tools/workspace.py wf list-cr --older-than 30

# List critical defects
python3 tools/workspace.py wf list-cr --severity critical --type defect
```

**CR Trend Analysis**:

```bash
# Generate trend report (monthly CR count, closure rate)
python3 tools/workspace.py wf trend-cr --months 6

# Export trend data to CSV
python3 tools/workspace.py wf trend-cr --months 12 --format csv --output reports/cr-trends.csv
```

### SIL-Specific CR Metrics Requirements

| Metric | SIL 0-1 | SIL 2 | SIL 3-4 |
|--------|---------|-------|---------|
| **CR Count by Status** | Recommended | MANDATORY | MANDATORY |
| **CR Resolution Time** | Recommended | MANDATORY | MANDATORY |
| **CR Backlog Aging** | Optional | Recommended | MANDATORY |
| **CR Effort Accuracy** | Optional | Recommended | MANDATORY |
| **Defect Density** | Optional | Recommended | MANDATORY |
| **Critical Defects Outstanding** | --- | MANDATORY | MANDATORY |
| **Safety CR Outstanding** | --- | MANDATORY | MANDATORY |
| **Trend Analysis** | Optional | Recommended | MANDATORY |

---

## Baseline Metrics

### Baseline Tracking Metrics

Configuration Status Accounting tracks baseline metrics to monitor project progress and configuration stability.

**Key Baseline Metrics**:

1. **Baseline Count**: Total number of baselines established
2. **Baseline Size**: Number of CIs per baseline, total size (bytes, LOC)
3. **Baseline Growth**: Change in baseline size over time
4. **Baseline Composition**: Breakdown by CI type (source, document, test, tool)
5. **Baseline Stability**: Number of changes to baseline CIs after baseline establishment
6. **Baseline Compliance**: PCA/FCA audit results (SIL 3-4)

### Baseline Metrics Data Structure

**Baseline Metrics Format** (`reports/baseline-metrics.json`):

```json
{
  "report_date": "2026-03-14",
  "project": "Railway Signaling Controller",
  "sil": 3,
  "baseline_count": {
    "total": 7,
    "by_phase": {
      "gate1_planning": 1,
      "gate2_requirements": 1,
      "gate3_design": 1,
      "gate4_implementation": 1,
      "gate5_integration": 1,
      "gate6_validation": 1,
      "gate7_assessment": 1
    }
  },
  "latest_baseline": {
    "baseline_id": "BL-GATE6-001",
    "baseline_date": "2026-03-10",
    "phase_gate": "gate6_validation",
    "total_cis": 234,
    "total_size_bytes": 15728640,
    "total_loc": 18500,
    "ci_composition": {
      "source_files": 87,
      "header_files": 87,
      "documents": 45,
      "test_files": 98,
      "tools": 4,
      "configuration_files": 13
    },
    "ci_by_lifecycle_phase": {
      "requirements": 46,
      "architecture": 35,
      "design": 58,
      "implementation": 87,
      "testing": 98,
      "validation": 10
    },
    "approval_status": "APPROVED",
    "pca_status": "PASSED",
    "fca_status": "PASSED"
  },
  "baseline_growth": {
    "baselines": [
      {
        "baseline_id": "BL-GATE1-001",
        "date": "2025-10-15",
        "ci_count": 20,
        "size_bytes": 512000,
        "loc": 0
      },
      {
        "baseline_id": "BL-GATE2-001",
        "date": "2025-11-30",
        "ci_count": 65,
        "size_bytes": 2048000,
        "loc": 0
      },
      {
        "baseline_id": "BL-GATE3-001",
        "date": "2025-12-20",
        "ci_count": 105,
        "size_bytes": 4096000,
        "loc": 2500
      },
      {
        "baseline_id": "BL-GATE4-001",
        "date": "2026-01-31",
        "ci_count": 198,
        "size_bytes": 12582912,
        "loc": 15000
      },
      {
        "baseline_id": "BL-GATE5-001",
        "date": "2026-02-28",
        "ci_count": 228,
        "size_bytes": 14680064,
        "loc": 17200
      },
      {
        "baseline_id": "BL-GATE6-001",
        "date": "2026-03-10",
        "ci_count": 234,
        "size_bytes": 15728640,
        "loc": 18500
      }
    ],
    "growth_rate": {
      "ci_count_monthly_average": 35.7,
      "size_bytes_monthly_average": 3052544,
      "loc_monthly_average": 3700
    }
  },
  "baseline_stability": {
    "bl_gate4_changes_after_baseline": 12,
    "bl_gate5_changes_after_baseline": 6,
    "bl_gate6_changes_after_baseline": 0,
    "total_post_baseline_changes": 18,
    "stability_percentage": 92.3
  },
  "baseline_compliance": {
    "pca_audits_completed": 7,
    "pca_audits_passed": 7,
    "pca_pass_rate": 100.0,
    "fca_audits_completed": 7,
    "fca_audits_passed": 7,
    "fca_pass_rate": 100.0,
    "audit_findings_total": 15,
    "audit_findings_closed": 15,
    "audit_findings_open": 0
  }
}
```

### Baseline Metrics Collection with workspace.py

**Generate Baseline Metrics Report**:

```bash
# Generate baseline metrics for all baselines
python3 tools/workspace.py wf metrics-baseline

# Generate metrics for specific baseline
python3 tools/workspace.py wf metrics-baseline --baseline BL-GATE6-001

# Generate baseline growth trend
python3 tools/workspace.py wf trend-baseline --output reports/baseline-growth.csv
```

**Query Baseline Composition**:

```bash
# List all CIs in baseline
python3 tools/workspace.py wf list-baseline-cis --baseline BL-GATE6-001

# List CIs by type in baseline
python3 tools/workspace.py wf list-baseline-cis --baseline BL-GATE6-001 --type source

# Compare two baselines (show differences)
python3 tools/workspace.py wf compare-baselines \
  --baseline1 BL-GATE5-001 \
  --baseline2 BL-GATE6-001
```

**Baseline Stability Analysis**:

```bash
# Count changes to baseline CIs after baseline establishment
python3 tools/workspace.py wf analyze-baseline-stability \
  --baseline BL-GATE4-001

# Report CIs changed after baseline
python3 tools/workspace.py wf list-post-baseline-changes \
  --baseline BL-GATE4-001
```

### SIL-Specific Baseline Metrics Requirements

| Metric | SIL 0-1 | SIL 2 | SIL 3-4 |
|--------|---------|-------|---------|
| **Baseline Count** | Recommended | MANDATORY | MANDATORY |
| **Baseline Size (CI count)** | Recommended | MANDATORY | MANDATORY |
| **Baseline Composition** | Recommended | MANDATORY | MANDATORY |
| **Baseline Growth Trend** | Optional | Recommended | MANDATORY |
| **Baseline Stability** | Optional | Recommended | MANDATORY |
| **PCA/FCA Audit Results** | --- | Recommended | MANDATORY |

---

## Traceability Metrics

### Traceability Coverage Metrics

Configuration Status Accounting tracks traceability metrics to ensure requirements coverage (MANDATORY SIL 3-4 per Table A.9 #7).

**Key Traceability Metrics**:

1. **Requirements Coverage**: Percentage of requirements traced to design, implementation, tests
2. **Backward Traceability**: Percentage of CIs (source, tests) traced back to requirements
3. **Traceability Gaps**: Requirements without implementation, tests without requirements, etc.
4. **Traceability Matrix Completeness**: Percentage of traceability matrix filled
5. **Orphaned Items**: CIs not traced to any requirement (potential over-implementation)

### Traceability Metrics Data Structure

**Traceability Metrics Format** (`reports/traceability-metrics.json`):

```json
{
  "report_date": "2026-03-14",
  "project": "Railway Signaling Controller",
  "sil": 3,
  "requirements_traceability": {
    "total_requirements": 87,
    "requirements_traced_to_design": 87,
    "requirements_traced_to_implementation": 85,
    "requirements_traced_to_tests": 87,
    "requirements_fully_traced": 85,
    "requirements_not_implemented": 2,
    "requirements_not_tested": 0,
    "forward_traceability_percentage": 97.7,
    "gaps": [
      {
        "requirement_id": "REQ-ATP-042",
        "missing_trace_to": "implementation",
        "reason": "Implementation deferred to Phase 2 per CR-2026-035"
      },
      {
        "requirement_id": "REQ-DIAG-015",
        "missing_trace_to": "implementation",
        "reason": "Under development, target: 2026-03-20"
      }
    ]
  },
  "backward_traceability": {
    "total_source_files": 87,
    "source_files_traced_to_requirements": 85,
    "source_files_orphaned": 2,
    "total_test_files": 98,
    "test_files_traced_to_requirements": 98,
    "test_files_orphaned": 0,
    "backward_traceability_percentage": 98.9,
    "orphaned_items": [
      {
        "ci_id": "CI-SRC-078",
        "name": "util_helper.c",
        "reason": "Utility function, not requirement-specific"
      },
      {
        "ci_id": "CI-SRC-079",
        "name": "debug_logger.c",
        "reason": "Development support, not in final release"
      }
    ]
  },
  "traceability_matrix_completeness": {
    "total_matrix_cells": 7830,
    "filled_cells": 7650,
    "empty_cells": 180,
    "completeness_percentage": 97.7
  },
  "traceability_by_sil": {
    "sil_4_requirements": 15,
    "sil_4_traced_to_implementation": 15,
    "sil_4_traced_to_tests": 15,
    "sil_4_traceability_percentage": 100.0,
    "sil_3_requirements": 42,
    "sil_3_traced_to_implementation": 40,
    "sil_3_traced_to_tests": 42,
    "sil_3_traceability_percentage": 95.2,
    "sil_2_requirements": 20,
    "sil_2_traced_to_implementation": 20,
    "sil_2_traced_to_tests": 20,
    "sil_2_traceability_percentage": 100.0,
    "sil_1_requirements": 10,
    "sil_1_traced_to_implementation": 10,
    "sil_1_traced_to_tests": 10,
    "sil_1_traceability_percentage": 100.0
  },
  "test_coverage_traceability": {
    "total_requirements": 87,
    "requirements_with_unit_tests": 87,
    "requirements_with_integration_tests": 85,
    "requirements_with_system_tests": 87,
    "test_coverage_percentage": 100.0
  }
}
```

### Traceability Metrics Collection with workspace.py

**Generate Traceability Metrics Report**:

```bash
# Generate complete traceability metrics
python3 tools/workspace.py trace metrics

# Generate forward traceability report (requirements → implementation/tests)
python3 tools/workspace.py trace metrics --direction forward

# Generate backward traceability report (implementation/tests → requirements)
python3 tools/workspace.py trace metrics --direction backward

# Generate traceability gaps report
python3 tools/workspace.py trace gaps
```

**Query Traceability Data**:

```bash
# List requirements not traced to implementation
python3 tools/workspace.py trace list-gaps --type not-implemented

# List requirements not traced to tests
python3 tools/workspace.py trace list-gaps --type not-tested

# List orphaned source files (no requirement trace)
python3 tools/workspace.py trace list-orphans --type source

# List orphaned test files
python3 tools/workspace.py trace list-orphans --type test
```

**Validate Traceability Matrix**:

```bash
# Validate complete traceability matrix
python3 tools/workspace.py trace validate

# Validate traceability for specific SIL level
python3 tools/workspace.py trace validate --sil 3

# Validate traceability for specific requirement
python3 tools/workspace.py trace validate --requirement REQ-ATP-042
```

**Export Traceability Matrix**:

```bash
# Export traceability matrix to CSV
python3 tools/workspace.py trace export-matrix \
  --format csv \
  --output reports/traceability-matrix.csv

# Export traceability matrix to Excel
python3 tools/workspace.py trace export-matrix \
  --format xlsx \
  --output reports/traceability-matrix.xlsx
```

### SIL-Specific Traceability Requirements

| Metric | SIL 0-1 | SIL 2 | SIL 3-4 |
|--------|---------|-------|---------|
| **Forward Traceability (Req → Impl)** | Recommended | Highly Recommended | **MANDATORY (100%)** |
| **Forward Traceability (Req → Test)** | Recommended | Highly Recommended | **MANDATORY (100%)** |
| **Backward Traceability (Impl → Req)** | Optional | Recommended | **MANDATORY** |
| **Traceability Matrix** | Optional | Recommended | **MANDATORY** |
| **Traceability Gaps Report** | Optional | Recommended | **MANDATORY** |
| **Orphaned Items Report** | Optional | Recommended | **MANDATORY** |

**EN 50128 Table A.9 #7**: Traceability is **MANDATORY for SIL 3-4**, Highly Recommended for SIL 1-2.

---

## Status Reporting

### Report Types

Configuration Status Accounting generates multiple report types for different audiences and purposes.

| Report Type | Frequency | Audience | Purpose |
|-------------|-----------|----------|---------|
| **Weekly Status Report** | Weekly | PM, CM, Team Leads | Track weekly progress, changes, issues |
| **Monthly Summary Report** | Monthly | PM, CM, Senior Management | Track monthly trends, metrics, compliance |
| **Phase Gate Report** | At each gate | COD, PM, VER, VAL, VMGR | Gate decision (GO/NO-GO) |
| **Configuration Audit Report** | Gate 2-7 | CM, QUA, VER, VAL | PCA/FCA audit results (SIL 3-4) |
| **Traceability Report** | Monthly | CM, VER | Requirements coverage, gaps |
| **Change Metrics Report** | Monthly | PM, CM | CR trends, backlog, resolution time |
| **Quality Dashboard** | Real-time | All roles | Live metrics, KPIs, trends |

### Weekly Status Report

**Purpose**: Provide concise summary of weekly CM activities, changes, and status.

**Weekly Status Report Template** (`reports/weekly-status-YYYY-WNN.md`):

```markdown
# Weekly Configuration Status Report

**Project**: Railway Signaling Controller  
**SIL Level**: 3  
**Report Week**: 2026-W11 (2026-03-10 to 2026-03-14)  
**Report Date**: 2026-03-14  
**Prepared By**: Configuration Manager

---

## Executive Summary

- **Baseline Status**: BL-GATE6-001 established on 2026-03-10 (Gate 6 Validation)
- **Change Activity**: 8 CRs submitted, 5 CRs closed, 23 CRs open
- **Traceability Status**: 97.7% complete (2 gaps identified)
- **Issues**: None

---

## Configuration Item Status

| Status | Count | Change from Last Week |
|--------|-------|-----------------------|
| Draft | 36 | +12 |
| Baseline | 198 | +6 |
| Released | 0 | 0 |
| Obsolete | 0 | 0 |
| **Total CIs** | **234** | **+18** |

**New CIs This Week**:
- CI-SRC-085 to CI-SRC-090: Emergency brake module enhancements (6 files)
- CI-DOC-046: Validation Report (1 document)
- CI-TST-099 to CI-TST-104: New integration tests (6 tests)
- CI-DOC-047 to CI-DOC-051: Test specifications (5 documents)

---

## Change Request Status

| Status | Count | Change from Last Week |
|--------|-------|-----------------------|
| SUBMITTED | 8 | +5 |
| APPROVED | 5 | +2 |
| IMPLEMENTATION | 7 | -1 |
| VERIFICATION | 3 | +1 |
| CLOSED | 20 | +5 |
| REJECTED | 2 | 0 |
| **Total CRs** | **45** | **+8** |

**CRs Closed This Week**:
- CR-2026-040: Fix ATP speed calculation overflow (Critical defect)
- CR-2026-038: Update braking algorithm documentation
- CR-2026-037: Add diagnostic logging to ATP controller
- CR-2026-036: Enhance test coverage for emergency brake
- CR-2026-034: Update SRS with new safety requirements

**Critical CRs Open**: 1 (CR-2026-045: Emergency brake timing issue)

---

## Baseline Status

**Current Baseline**: BL-GATE6-001 (Validation Baseline)  
**Baseline Date**: 2026-03-10  
**Baseline CIs**: 234 (198 baseline, 36 draft)  
**PCA Status**: PASSED  
**FCA Status**: PASSED

**Next Baseline**: BL-GATE7-001 (Assessment/Deployment Baseline)  
**Target Date**: 2026-03-25

---

## Traceability Status

| Metric | Status | Target | Compliance |
|--------|--------|--------|------------|
| Forward Traceability (Req → Impl) | 97.7% | 100% | ⚠️ 2 gaps |
| Forward Traceability (Req → Test) | 100% | 100% | ✅ Pass |
| Backward Traceability | 98.9% | ≥95% | ✅ Pass |

**Traceability Gaps** (2):
- REQ-ATP-042: Implementation deferred per CR-2026-035
- REQ-DIAG-015: Under development, target 2026-03-20

---

## Issues and Risks

**Issues**: None

**Risks**:
1. **Risk**: REQ-ATP-042 implementation deferral may delay Gate 7
   - **Mitigation**: Fast-track CR-2026-035 implementation, target completion 2026-03-18
   - **Status**: IN PROGRESS

---

## Action Items

| Action | Owner | Due Date | Status |
|--------|-------|----------|--------|
| Complete REQ-DIAG-015 implementation | John Smith (IMP) | 2026-03-20 | IN PROGRESS |
| Resolve CR-2026-045 (critical) | Alice Johnson (IMP) | 2026-03-17 | IN PROGRESS |
| Update traceability matrix for REQ-ATP-042 | Bob Wilson (CM) | 2026-03-18 | NOT STARTED |

---

## Next Week Priorities

1. Close critical CR-2026-045 (emergency brake timing)
2. Complete REQ-DIAG-015 implementation and testing
3. Resolve 2 traceability gaps
4. Prepare for Gate 7 baseline (BL-GATE7-001)

---

**Report Generated**: 2026-03-14 10:30:00 UTC  
**Next Report**: 2026-03-21 (Week 2026-W12)
```

**Generate Weekly Report with Automation Script**:

```bash
# Generate weekly status report for current week
python3 tools/scripts/generate_weekly_status_report.py

# Generate weekly status report for specific week
python3 tools/scripts/generate_weekly_status_report.py --week 2026-W11
```

### Monthly Summary Report

**Purpose**: Provide comprehensive monthly summary of CM activities, trends, and quality metrics.

**Monthly Summary Report Template** (`reports/monthly-summary-YYYY-MM.md`):

```markdown
# Monthly Configuration Status Report

**Project**: Railway Signaling Controller  
**SIL Level**: 3  
**Report Month**: March 2026  
**Report Date**: 2026-03-31  
**Prepared By**: Configuration Manager

---

## Executive Summary

March 2026 was a critical month with Gate 6 (Validation) and Gate 7 (Assessment) completed. Key achievements:

- ✅ Gate 6 baseline established (BL-GATE6-001) with PCA/FCA passed
- ✅ Gate 7 baseline established (BL-GATE7-001) - Deployment ready
- ✅ 45 CRs processed (20 closed, 2 rejected, 23 open)
- ✅ Traceability improved from 95.2% to 100% (all gaps resolved)
- ⚠️ Change rate increased 12% (45 CRs vs. 40 in February)

---

## Configuration Item Statistics

| Metric | March 2026 | February 2026 | Change |
|--------|------------|---------------|--------|
| Total CIs | 234 | 228 | +6 (+2.6%) |
| Baseline CIs | 234 | 198 | +36 (+18.2%) |
| Draft CIs | 0 | 30 | -30 (-100%) |
| Source Files | 87 | 85 | +2 (+2.4%) |
| Documents | 45 | 42 | +3 (+7.1%) |
| Test Files | 98 | 96 | +2 (+2.1%) |
| Total LOC | 18,500 | 17,200 | +1,300 (+7.6%) |

---

## Change Request Statistics

| Metric | March 2026 | February 2026 | Change |
|--------|------------|---------------|--------|
| CRs Submitted | 45 | 40 | +5 (+12.5%) |
| CRs Closed | 20 | 18 | +2 (+11.1%) |
| CRs Rejected | 2 | 1 | +1 (+100%) |
| CRs Open (End of Month) | 23 | 21 | +2 (+9.5%) |
| Average Resolution Time | 12.5 days | 14.2 days | -1.7 days (-12.0%) |
| Critical Defects Closed | 3 | 2 | +1 (+50%) |
| Safety CRs Closed | 5 | 4 | +1 (+25%) |

**CR Type Distribution**:
- Defects: 18 (40%)
- Enhancements: 15 (33%)
- Safety: 8 (18%)
- Documentation: 4 (9%)

**CR Severity Distribution**:
- Critical: 3 (7%)
- Major: 12 (27%)
- Minor: 20 (44%)
- Trivial: 10 (22%)

---

## Baseline Activity

**Baselines Established**:
1. **BL-GATE6-001** (2026-03-10): Validation Baseline
   - CIs: 234
   - PCA: PASSED
   - FCA: PASSED
2. **BL-GATE7-001** (2026-03-28): Assessment/Deployment Baseline
   - CIs: 234
   - PCA: PASSED
   - FCA: PASSED
   - Deployment Ready: YES

**Baseline Stability**:
- BL-GATE5-001: 6 CIs changed after baseline (97.4% stability)
- BL-GATE6-001: 0 CIs changed after baseline (100% stability)

---

## Traceability Metrics

| Metric | March 2026 | February 2026 | Target | Status |
|--------|------------|---------------|--------|--------|
| Requirements Total | 87 | 85 | --- | +2 |
| Forward Trace (Req → Impl) | 100% | 97.7% | 100% | ✅ |
| Forward Trace (Req → Test) | 100% | 100% | 100% | ✅ |
| Backward Trace | 100% | 98.9% | ≥95% | ✅ |
| Traceability Gaps | 0 | 2 | 0 | ✅ |

**Gaps Resolved**:
- REQ-ATP-042: Implementation completed (CR-2026-035 closed)
- REQ-DIAG-015: Implementation completed and tested

---

## Quality Metrics

| Metric | March 2026 | February 2026 | Target | Status |
|--------|------------|---------------|--------|--------|
| Defect Density (per KLOC) | 2.1 | 2.3 | ≤3.0 | ✅ |
| Statement Coverage | 100% | 99.8% | 100% | ✅ |
| Branch Coverage | 100% | 99.5% | 100% | ✅ |
| MC/DC Coverage | 100% | 99.2% | 100% | ✅ |
| MISRA C Compliance | 100% | 99.8% | 100% | ✅ |
| Cyclomatic Complexity (avg) | 6.2 | 6.5 | ≤10 | ✅ |

---

## Trends and Analysis

### CR Trend (6 months)

| Month | CRs Submitted | CRs Closed | Open CRs (EOM) | Closure Rate |
|-------|---------------|------------|----------------|--------------|
| Oct 2025 | 32 | 25 | 18 | 78% |
| Nov 2025 | 35 | 28 | 25 | 80% |
| Dec 2025 | 38 | 30 | 33 | 79% |
| Jan 2026 | 42 | 35 | 40 | 83% |
| Feb 2026 | 40 | 32 | 21 | 80% |
| Mar 2026 | 45 | 20 | 23 | 44% |

**Analysis**: March closure rate decreased to 44% due to focus on Gate 6/7 activities (validation, assessment). Open CRs increased slightly but remain manageable. April focus will be on closing open CRs.

### Baseline Growth (6 months)

| Baseline | Date | CI Count | LOC | Size (MB) |
|----------|------|----------|-----|-----------|
| BL-GATE1-001 | Oct 2025 | 20 | 0 | 0.5 |
| BL-GATE2-001 | Nov 2025 | 65 | 0 | 2.0 |
| BL-GATE3-001 | Dec 2025 | 105 | 2,500 | 4.0 |
| BL-GATE4-001 | Jan 2026 | 198 | 15,000 | 12.0 |
| BL-GATE5-001 | Feb 2026 | 228 | 17,200 | 14.0 |
| BL-GATE6-001 | Mar 2026 | 234 | 18,500 | 15.0 |
| BL-GATE7-001 | Mar 2026 | 234 | 18,500 | 15.0 |

**Analysis**: Baseline growth stabilized in March (BL-GATE6 and BL-GATE7 identical). All planned features implemented. Project ready for deployment.

---

## Issues and Risks

**Issues**: None

**Risks**: None (All risks from previous month resolved)

---

## Compliance Status

| Requirement | Status | Evidence |
|-------------|--------|----------|
| EN 50128 Section 6.6 (CM) | ✅ COMPLIANT | SCMP followed, all baselines established |
| Table A.9 #5 (CM MANDATORY) | ✅ COMPLIANT | Git version control, change control, baselines |
| Table A.9 #7 (Traceability M SIL3-4) | ✅ COMPLIANT | 100% traceability, matrix complete |
| Table A.9 #8 (Data Recording M SIL3-4) | ✅ COMPLIANT | CSA reports weekly/monthly, metrics tracked |
| PCA/FCA (MANDATORY SIL 3-4) | ✅ COMPLIANT | PCA/FCA passed for BL-GATE6, BL-GATE7 |

---

## Next Month Priorities (April 2026)

1. Close remaining 23 open CRs
2. Maintain 100% traceability
3. Prepare deployment package (BL-GATE7-001)
4. Conduct post-deployment review
5. Archive project artifacts

---

**Report Generated**: 2026-03-31 17:00:00 UTC  
**Next Report**: 2026-04-30 (April 2026 Monthly Summary)
```

**Generate Monthly Report with Automation Script**:

```bash
# Generate monthly summary report for current month
python3 tools/scripts/generate_monthly_summary_report.py

# Generate monthly summary report for specific month
python3 tools/scripts/generate_monthly_summary_report.py --month 2026-03
```

### Phase Gate Report

**Purpose**: Provide comprehensive CM status for gate decision (GO/NO-GO).

**Phase Gate Report Template** (`reports/gate-report-GATEN.md`):

See **Baseline Management Workflow** Section 3 for complete gate report template.

**Generate Gate Report with Automation Script**:

```bash
# Generate gate report for specific gate
python3 tools/scripts/generate_gate_report.py --gate gate6_validation

# Include all metrics (CI, CR, traceability, quality)
python3 tools/scripts/generate_gate_report.py --gate gate6_validation --full
```

---

## Tool Integration

### workspace.py Integration

Configuration Status Accounting relies heavily on `workspace.py` for data collection and reporting.

**workspace.py Subcommands for CSA**:

```bash
# CI Tracking
python3 tools/workspace.py trace list-cis                    # List all CIs
python3 tools/workspace.py trace add-ci <options>            # Add CI to registry
python3 tools/workspace.py trace update-ci-status <options>  # Update CI status
python3 tools/workspace.py trace validate-ci-registry        # Validate registry

# Change Metrics
python3 tools/workspace.py wf metrics-cr <options>           # Generate CR metrics
python3 tools/workspace.py wf list-cr <options>              # List CRs
python3 tools/workspace.py wf trend-cr <options>             # CR trend analysis

# Baseline Metrics
python3 tools/workspace.py wf metrics-baseline <options>     # Generate baseline metrics
python3 tools/workspace.py wf list-baseline-cis <options>    # List CIs in baseline
python3 tools/workspace.py wf compare-baselines <options>    # Compare baselines
python3 tools/workspace.py wf analyze-baseline-stability <options>  # Stability analysis

# Traceability Metrics
python3 tools/workspace.py trace metrics                     # Traceability metrics
python3 tools/workspace.py trace gaps                        # Traceability gaps
python3 tools/workspace.py trace list-orphans <options>      # Orphaned items
python3 tools/workspace.py trace validate                    # Validate traceability
python3 tools/workspace.py trace export-matrix <options>     # Export matrix
```

### Git Integration

CSA integrates with Git to automatically collect version and commit data.

**Automatic CI Discovery from Git**:

```bash
# Scan Git repository and populate CI registry
python3 tools/scripts/populate_ci_registry_from_git.py

# Update CI versions from Git
python3 tools/scripts/sync_ci_versions_from_git.py

# Compare CI registry with Git (find missing/orphaned CIs)
python3 tools/scripts/validate_ci_registry_vs_git.py
```

**Extract Change Metrics from Git**:

```bash
# Count commits per week/month
git log --since="2026-03-01" --until="2026-03-31" --oneline | wc -l

# Count commits by author
git shortlog -s -n --since="2026-03-01" --until="2026-03-31"

# Count changed files
git diff --stat BL-GATE5-001..BL-GATE6-001
```

### CI/CD Integration

CSA can be integrated into CI/CD pipelines for automated reporting.

**CI/CD Pipeline Integration** (`.github/workflows/csa-report.yml`):

```yaml
name: Configuration Status Accounting Report

on:
  schedule:
    - cron: '0 9 * * 1'  # Every Monday at 9 AM UTC
  workflow_dispatch:

jobs:
  generate-csa-report:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout repository
        uses: actions/checkout@v4
        with:
          fetch-depth: 0  # Full history for metrics
      
      - name: Setup Python
        uses: actions/setup-python@v5
        with:
          python-version: '3.11'
      
      - name: Install dependencies
        run: |
          python -m pip install --upgrade pip
          pip install -r tools/requirements.txt
      
      - name: Generate weekly status report
        run: |
          python3 tools/scripts/generate_weekly_status_report.py
      
      - name: Generate CI metrics
        run: |
          python3 tools/workspace.py trace metrics > reports/ci-metrics.txt
      
      - name: Generate CR metrics
        run: |
          python3 tools/workspace.py wf metrics-cr --period 30 > reports/cr-metrics.txt
      
      - name: Generate baseline metrics
        run: |
          python3 tools/workspace.py wf metrics-baseline > reports/baseline-metrics.txt
      
      - name: Generate traceability metrics
        run: |
          python3 tools/workspace.py trace gaps > reports/traceability-gaps.txt
      
      - name: Upload reports as artifacts
        uses: actions/upload-artifact@v4
        with:
          name: csa-reports
          path: reports/
      
      - name: Commit reports to repository
        run: |
          git config user.name "CSA Bot"
          git config user.email "csa@project.local"
          git add reports/
          git commit -m "chore(csa): Weekly status report $(date +%Y-W%V)"
          git push
```

---

## Automation Scripts

### Script 1: CI Registry Manager

**Purpose**: Maintain CI registry, sync with Git, validate consistency.

**Script**: `tools/scripts/ci_registry_manager.py`

```python
#!/usr/bin/env python3
"""
CI Registry Manager

Manages the configuration item (CI) registry for EN 50128 projects.
Provides commands to add, update, list, and validate CIs.

Usage:
    python3 ci_registry_manager.py populate     # Populate from Git
    python3 ci_registry_manager.py sync         # Sync versions with Git
    python3 ci_registry_manager.py validate     # Validate registry
    python3 ci_registry_manager.py list         # List all CIs
    python3 ci_registry_manager.py add <options>  # Add CI manually
"""

import argparse
import hashlib
import json
import os
import subprocess
import sys
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Optional

# Configuration
CI_REGISTRY_PATH = "config/ci-registry.json"
PROJECT_ROOT = Path(__file__).parent.parent.parent

def run_command(cmd: List[str], cwd: Optional[Path] = None) -> str:
    """Run shell command and return output."""
    result = subprocess.run(
        cmd,
        cwd=cwd or PROJECT_ROOT,
        capture_output=True,
        text=True,
        check=True
    )
    return result.stdout.strip()

def calculate_checksum(file_path: Path) -> str:
    """Calculate SHA256 checksum of file."""
    sha256 = hashlib.sha256()
    with open(file_path, 'rb') as f:
        for block in iter(lambda: f.read(4096), b''):
            sha256.update(block)
    return sha256.hexdigest()

def count_loc(file_path: Path) -> int:
    """Count lines of code (non-empty, non-comment)."""
    if not file_path.suffix in ['.c', '.h', '.py']:
        return 0
    
    loc = 0
    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
        in_block_comment = False
        for line in f:
            line = line.strip()
            # Skip empty lines
            if not line:
                continue
            # Skip block comments
            if line.startswith('/*'):
                in_block_comment = True
            if '*/' in line:
                in_block_comment = False
                continue
            if in_block_comment:
                continue
            # Skip line comments
            if line.startswith('//') or line.startswith('#'):
                continue
            loc += 1
    return loc

def get_git_info(file_path: Path) -> Dict[str, str]:
    """Get Git commit and version for file."""
    try:
        commit = run_command(['git', 'log', '-1', '--format=%H', str(file_path)])
        date = run_command(['git', 'log', '-1', '--format=%ci', str(file_path)])
        return {
            'commit': commit[:12] if commit else 'unknown',
            'date': date.split()[0] if date else 'unknown'
        }
    except subprocess.CalledProcessError:
        return {'commit': 'unknown', 'date': 'unknown'}

def classify_ci_type(file_path: Path) -> str:
    """Classify CI type based on file path and extension."""
    path_str = str(file_path).lower()
    
    if 'test' in path_str:
        return 'test'
    elif file_path.suffix in ['.c', '.h', '.cpp', '.hpp']:
        return 'source'
    elif file_path.suffix in ['.md', '.pdf', '.docx', '.txt']:
        return 'document'
    elif 'makefile' in path_str or file_path.name in ['Makefile', 'CMakeLists.txt']:
        return 'configuration'
    elif file_path.suffix in ['.json', '.yaml', '.yml', '.xml']:
        return 'configuration'
    else:
        return 'other'

def populate_ci_registry():
    """Populate CI registry from Git repository."""
    print("Populating CI registry from Git repository...")
    
    # Get all tracked files
    tracked_files = run_command(['git', 'ls-files']).split('\n')
    
    # Exclude certain directories
    exclude_dirs = ['.git', 'venv', '__pycache__', 'node_modules', '.opencode']
    filtered_files = [
        f for f in tracked_files
        if not any(excl in f for excl in exclude_dirs)
    ]
    
    cis = []
    for i, file_path_str in enumerate(filtered_files, 1):
        file_path = PROJECT_ROOT / file_path_str
        if not file_path.exists():
            continue
        
        ci_type = classify_ci_type(file_path)
        git_info = get_git_info(file_path)
        
        ci = {
            'ci_id': f"CI-{ci_type.upper()[:3]}-{i:03d}",
            'ci_type': ci_type,
            'name': file_path.name,
            'path': file_path_str,
            'version': '1.0.0',
            'git_commit': git_info['commit'],
            'status': 'draft',
            'owner': 'Unknown',
            'created_date': git_info['date'],
            'last_modified': git_info['date'],
            'checksum_sha256': calculate_checksum(file_path),
            'size_bytes': file_path.stat().st_size
        }
        
        if ci_type == 'source':
            ci['loc'] = count_loc(file_path)
        
        cis.append(ci)
        print(f"  [{i}/{len(filtered_files)}] Added {ci['ci_id']}: {file_path_str}")
    
    # Create registry structure
    registry = {
        'project': 'Railway Signaling Controller',
        'sil': 3,
        'registry_version': '1.0.0',
        'last_updated': datetime.now().isoformat(),
        'configuration_items': cis,
        'ci_statistics': {
            'total_cis': len(cis),
            'source_files': sum(1 for ci in cis if ci['ci_type'] == 'source'),
            'documents': sum(1 for ci in cis if ci['ci_type'] == 'document'),
            'test_files': sum(1 for ci in cis if ci['ci_type'] == 'test'),
            'configuration_files': sum(1 for ci in cis if ci['ci_type'] == 'configuration'),
            'draft_cis': len(cis),
            'baseline_cis': 0,
            'obsolete_cis': 0
        }
    }
    
    # Write registry
    registry_path = PROJECT_ROOT / CI_REGISTRY_PATH
    registry_path.parent.mkdir(parents=True, exist_ok=True)
    with open(registry_path, 'w') as f:
        json.dump(registry, f, indent=2)
    
    print(f"\n✅ CI registry populated: {len(cis)} CIs")
    print(f"   Registry saved to: {CI_REGISTRY_PATH}")

def sync_ci_versions():
    """Sync CI versions with Git commits."""
    print("Syncing CI versions with Git...")
    
    registry_path = PROJECT_ROOT / CI_REGISTRY_PATH
    if not registry_path.exists():
        print("❌ CI registry not found. Run 'populate' first.")
        sys.exit(1)
    
    with open(registry_path, 'r') as f:
        registry = json.load(f)
    
    updated_count = 0
    for ci in registry['configuration_items']:
        file_path = PROJECT_ROOT / ci['path']
        if not file_path.exists():
            print(f"  ⚠️  {ci['ci_id']}: File not found: {ci['path']}")
            continue
        
        git_info = get_git_info(file_path)
        if git_info['commit'] != ci['git_commit']:
            ci['git_commit'] = git_info['commit']
            ci['last_modified'] = git_info['date']
            ci['checksum_sha256'] = calculate_checksum(file_path)
            updated_count += 1
            print(f"  ✓ {ci['ci_id']}: Updated to commit {git_info['commit']}")
    
    registry['last_updated'] = datetime.now().isoformat()
    
    with open(registry_path, 'w') as f:
        json.dump(registry, f, indent=2)
    
    print(f"\n✅ Sync complete: {updated_count} CIs updated")

def validate_ci_registry():
    """Validate CI registry consistency."""
    print("Validating CI registry...")
    
    registry_path = PROJECT_ROOT / CI_REGISTRY_PATH
    if not registry_path.exists():
        print("❌ CI registry not found.")
        sys.exit(1)
    
    with open(registry_path, 'r') as f:
        registry = json.load(f)
    
    errors = []
    warnings = []
    
    # Check for missing files
    for ci in registry['configuration_items']:
        file_path = PROJECT_ROOT / ci['path']
        if not file_path.exists():
            errors.append(f"CI {ci['ci_id']}: File not found: {ci['path']}")
        else:
            # Check checksum
            actual_checksum = calculate_checksum(file_path)
            if actual_checksum != ci['checksum_sha256']:
                warnings.append(f"CI {ci['ci_id']}: Checksum mismatch (file modified since last sync)")
    
    # Check for orphaned files (Git files not in registry)
    tracked_files = set(run_command(['git', 'ls-files']).split('\n'))
    registry_files = set(ci['path'] for ci in registry['configuration_items'])
    orphaned = tracked_files - registry_files
    exclude_dirs = ['.git', 'venv', '__pycache__', 'node_modules', '.opencode']
    orphaned = [f for f in orphaned if not any(excl in f for excl in exclude_dirs)]
    
    if orphaned:
        warnings.append(f"{len(orphaned)} files in Git not in registry (run 'populate' or 'sync')")
        for file in list(orphaned)[:5]:
            warnings.append(f"  - {file}")
        if len(orphaned) > 5:
            warnings.append(f"  ... and {len(orphaned) - 5} more")
    
    # Print results
    print(f"\n📊 Validation Results:")
    print(f"   Total CIs: {len(registry['configuration_items'])}")
    print(f"   Errors: {len(errors)}")
    print(f"   Warnings: {len(warnings)}")
    
    if errors:
        print("\n❌ Errors:")
        for error in errors:
            print(f"   {error}")
    
    if warnings:
        print("\n⚠️  Warnings:")
        for warning in warnings:
            print(f"   {warning}")
    
    if not errors and not warnings:
        print("\n✅ CI registry is valid")
    
    sys.exit(1 if errors else 0)

def list_cis(ci_type: Optional[str] = None, status: Optional[str] = None):
    """List CIs with optional filters."""
    registry_path = PROJECT_ROOT / CI_REGISTRY_PATH
    if not registry_path.exists():
        print("❌ CI registry not found.")
        sys.exit(1)
    
    with open(registry_path, 'r') as f:
        registry = json.load(f)
    
    cis = registry['configuration_items']
    
    # Apply filters
    if ci_type:
        cis = [ci for ci in cis if ci['ci_type'] == ci_type]
    if status:
        cis = [ci for ci in cis if ci['status'] == status]
    
    print(f"\n📋 Configuration Items ({len(cis)}):")
    print(f"{'CI ID':<20} {'Type':<12} {'Status':<10} {'Path'}")
    print("-" * 80)
    
    for ci in cis:
        print(f"{ci['ci_id']:<20} {ci['ci_type']:<12} {ci['status']:<10} {ci['path']}")

def main():
    parser = argparse.ArgumentParser(description='CI Registry Manager')
    subparsers = parser.add_subparsers(dest='command', help='Command to execute')
    
    subparsers.add_parser('populate', help='Populate CI registry from Git')
    subparsers.add_parser('sync', help='Sync CI versions with Git')
    subparsers.add_parser('validate', help='Validate CI registry')
    
    list_parser = subparsers.add_parser('list', help='List CIs')
    list_parser.add_argument('--type', choices=['source', 'document', 'test', 'configuration', 'other'], help='Filter by CI type')
    list_parser.add_argument('--status', choices=['draft', 'baseline', 'released', 'obsolete'], help='Filter by status')
    
    args = parser.parse_args()
    
    if args.command == 'populate':
        populate_ci_registry()
    elif args.command == 'sync':
        sync_ci_versions()
    elif args.command == 'validate':
        validate_ci_registry()
    elif args.command == 'list':
        list_cis(ci_type=args.type, status=args.status)
    else:
        parser.print_help()

if __name__ == '__main__':
    main()
```

**Usage Examples**:

```bash
# Populate CI registry from Git (initial setup)
python3 tools/scripts/ci_registry_manager.py populate

# Sync CI versions with Git (after commits)
python3 tools/scripts/ci_registry_manager.py sync

# Validate CI registry
python3 tools/scripts/ci_registry_manager.py validate

# List all CIs
python3 tools/scripts/ci_registry_manager.py list

# List source files only
python3 tools/scripts/ci_registry_manager.py list --type source

# List baseline CIs
python3 tools/scripts/ci_registry_manager.py list --status baseline
```

---

### Script 2: Metrics Dashboard Generator

**Purpose**: Generate HTML dashboard with real-time CM metrics.

**Script**: `tools/scripts/generate_metrics_dashboard.py`

```python
#!/usr/bin/env python3
"""
Metrics Dashboard Generator

Generates an HTML dashboard with Configuration Status Accounting metrics.

Usage:
    python3 generate_metrics_dashboard.py
    python3 generate_metrics_dashboard.py --output reports/dashboard.html
"""

import argparse
import json
import subprocess
from datetime import datetime
from pathlib import Path
from typing import Dict

PROJECT_ROOT = Path(__file__).parent.parent.parent

def load_ci_registry() -> Dict:
    """Load CI registry."""
    registry_path = PROJECT_ROOT / "config/ci-registry.json"
    if not registry_path.exists():
        return {}
    with open(registry_path, 'r') as f:
        return json.load(f)

def load_change_metrics() -> Dict:
    """Load change metrics."""
    metrics_path = PROJECT_ROOT / "reports/change-metrics.json"
    if not metrics_path.exists():
        return {}
    with open(metrics_path, 'r') as f:
        return json.load(f)

def load_traceability_metrics() -> Dict:
    """Load traceability metrics."""
    metrics_path = PROJECT_ROOT / "reports/traceability-metrics.json"
    if not metrics_path.exists():
        return {}
    with open(metrics_path, 'r') as f:
        return json.load(f)

def generate_dashboard_html(ci_data: Dict, cr_data: Dict, trace_data: Dict) -> str:
    """Generate HTML dashboard."""
    
    # Extract key metrics
    total_cis = ci_data.get('ci_statistics', {}).get('total_cis', 0)
    baseline_cis = ci_data.get('ci_statistics', {}).get('baseline_cis', 0)
    draft_cis = ci_data.get('ci_statistics', {}).get('draft_cis', 0)
    
    total_crs = cr_data.get('cr_count', {}).get('total', 0)
    open_crs = cr_data.get('cr_backlog', {}).get('total_open', 0)
    closed_crs = cr_data.get('cr_count', {}).get('by_status', {}).get('CLOSED', 0)
    
    req_trace_pct = trace_data.get('requirements_traceability', {}).get('forward_traceability_percentage', 0)
    trace_gaps = len(trace_data.get('requirements_traceability', {}).get('gaps', []))
    
    html = f"""
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Configuration Status Accounting Dashboard</title>
    <style>
        * {{
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }}
        body {{
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: #f5f5f5;
            padding: 20px;
        }}
        .container {{
            max-width: 1400px;
            margin: 0 auto;
        }}
        .header {{
            background: #2c3e50;
            color: white;
            padding: 30px;
            border-radius: 8px;
            margin-bottom: 20px;
        }}
        .header h1 {{
            font-size: 32px;
            margin-bottom: 10px;
        }}
        .header p {{
            font-size: 16px;
            opacity: 0.9;
        }}
        .metrics-grid {{
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
            gap: 20px;
            margin-bottom: 20px;
        }}
        .metric-card {{
            background: white;
            padding: 25px;
            border-radius: 8px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
        }}
        .metric-card h2 {{
            font-size: 18px;
            color: #34495e;
            margin-bottom: 15px;
        }}
        .metric-value {{
            font-size: 48px;
            font-weight: bold;
            color: #3498db;
            margin-bottom: 10px;
        }}
        .metric-label {{
            font-size: 14px;
            color: #7f8c8d;
        }}
        .metric-success {{
            color: #27ae60;
        }}
        .metric-warning {{
            color: #f39c12;
        }}
        .metric-danger {{
            color: #e74c3c;
        }}
        .progress-bar {{
            width: 100%;
            height: 30px;
            background: #ecf0f1;
            border-radius: 15px;
            overflow: hidden;
            margin-top: 10px;
        }}
        .progress-fill {{
            height: 100%;
            background: #3498db;
            display: flex;
            align-items: center;
            justify-content: center;
            color: white;
            font-weight: bold;
            transition: width 0.3s ease;
        }}
        .chart-container {{
            background: white;
            padding: 25px;
            border-radius: 8px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
            margin-bottom: 20px;
        }}
        .status-indicator {{
            display: inline-block;
            width: 12px;
            height: 12px;
            border-radius: 50%;
            margin-right: 8px;
        }}
        .status-green {{
            background: #27ae60;
        }}
        .status-yellow {{
            background: #f39c12;
        }}
        .status-red {{
            background: #e74c3c;
        }}
        table {{
            width: 100%;
            border-collapse: collapse;
            margin-top: 15px;
        }}
        th, td {{
            text-align: left;
            padding: 12px;
            border-bottom: 1px solid #ecf0f1;
        }}
        th {{
            background: #f8f9fa;
            font-weight: 600;
            color: #2c3e50;
        }}
        .footer {{
            text-align: center;
            padding: 20px;
            color: #7f8c8d;
            font-size: 14px;
        }}
    </style>
</head>
<body>
    <div class="container">
        <div class="header">
            <h1>Configuration Status Accounting Dashboard</h1>
            <p>Railway Signaling Controller - SIL 3 | Generated: {datetime.now().strftime('%Y-%m-%d %H:%M:%S UTC')}</p>
        </div>
        
        <div class="metrics-grid">
            <div class="metric-card">
                <h2>Configuration Items</h2>
                <div class="metric-value">{total_cis}</div>
                <div class="metric-label">Total CIs</div>
                <table>
                    <tr>
                        <td><span class="status-indicator status-green"></span> Baseline</td>
                        <td style="text-align: right; font-weight: bold;">{baseline_cis}</td>
                    </tr>
                    <tr>
                        <td><span class="status-indicator status-yellow"></span> Draft</td>
                        <td style="text-align: right; font-weight: bold;">{draft_cis}</td>
                    </tr>
                </table>
            </div>
            
            <div class="metric-card">
                <h2>Change Requests</h2>
                <div class="metric-value">{total_crs}</div>
                <div class="metric-label">Total CRs</div>
                <table>
                    <tr>
                        <td><span class="status-indicator status-yellow"></span> Open</td>
                        <td style="text-align: right; font-weight: bold;">{open_crs}</td>
                    </tr>
                    <tr>
                        <td><span class="status-indicator status-green"></span> Closed</td>
                        <td style="text-align: right; font-weight: bold;">{closed_crs}</td>
                    </tr>
                </table>
            </div>
            
            <div class="metric-card">
                <h2>Traceability</h2>
                <div class="metric-value {'metric-success' if req_trace_pct == 100 else 'metric-warning'}">{req_trace_pct:.1f}%</div>
                <div class="metric-label">Requirements Traced</div>
                <div class="progress-bar">
                    <div class="progress-fill" style="width: {req_trace_pct}%;">
                        {req_trace_pct:.1f}%
                    </div>
                </div>
                <p style="margin-top: 10px; color: {'#27ae60' if trace_gaps == 0 else '#e74c3c'};">
                    <strong>{trace_gaps}</strong> gaps identified
                </p>
            </div>
        </div>
        
        <div class="chart-container">
            <h2>CI Composition</h2>
            <table>
                <thead>
                    <tr>
                        <th>CI Type</th>
                        <th style="text-align: right;">Count</th>
                        <th style="text-align: right;">Percentage</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td>Source Files</td>
                        <td style="text-align: right;">{ci_data.get('ci_statistics', {}).get('source_files', 0)}</td>
                        <td style="text-align: right;">{ci_data.get('ci_statistics', {}).get('source_files', 0) / max(total_cis, 1) * 100:.1f}%</td>
                    </tr>
                    <tr>
                        <td>Documents</td>
                        <td style="text-align: right;">{ci_data.get('ci_statistics', {}).get('documents', 0)}</td>
                        <td style="text-align: right;">{ci_data.get('ci_statistics', {}).get('documents', 0) / max(total_cis, 1) * 100:.1f}%</td>
                    </tr>
                    <tr>
                        <td>Test Files</td>
                        <td style="text-align: right;">{ci_data.get('ci_statistics', {}).get('test_files', 0)}</td>
                        <td style="text-align: right;">{ci_data.get('ci_statistics', {}).get('test_files', 0) / max(total_cis, 1) * 100:.1f}%</td>
                    </tr>
                </tbody>
            </table>
        </div>
        
        <div class="footer">
            <p>EN 50128 Configuration Management | Data Recording and Analysis (Table A.9 #8 - MANDATORY SIL 3-4)</p>
        </div>
    </div>
</body>
</html>
"""
    return html

def main():
    parser = argparse.ArgumentParser(description='Generate Metrics Dashboard')
    parser.add_argument('--output', default='reports/dashboard.html', help='Output HTML file')
    args = parser.parse_args()
    
    print("Generating metrics dashboard...")
    
    # Load data
    ci_data = load_ci_registry()
    cr_data = load_change_metrics()
    trace_data = load_traceability_metrics()
    
    # Generate HTML
    html = generate_dashboard_html(ci_data, cr_data, trace_data)
    
    # Write output
    output_path = PROJECT_ROOT / args.output
    output_path.parent.mkdir(parents=True, exist_ok=True)
    with open(output_path, 'w') as f:
        f.write(html)
    
    print(f"✅ Dashboard generated: {args.output}")
    print(f"   Open in browser: file://{output_path.absolute()}")

if __name__ == '__main__':
    main()
```

**Usage**:

```bash
# Generate dashboard with default output
python3 tools/scripts/generate_metrics_dashboard.py

# Generate dashboard with custom output
python3 tools/scripts/generate_metrics_dashboard.py --output reports/csa-dashboard.html

# Open dashboard in browser
xdg-open reports/dashboard.html  # Linux
open reports/dashboard.html      # macOS
start reports/dashboard.html     # Windows
```

---

## Complete Example Scenarios

### Scenario 1: SIL 3 Project - Initial CSA Setup

**Context**: New SIL 3 project starting Phase 1 (Planning). CM needs to establish CI registry and CSA infrastructure.

**Steps**:

1. **Populate CI Registry from Git**

```bash
cd /path/to/railway-signaling-controller

# Populate CI registry
python3 tools/scripts/ci_registry_manager.py populate

# Output:
# Populating CI registry from Git repository...
#   [1/234] Added CI-DOC-001: docs/software-quality-assurance-plan.md
#   [2/234] Added CI-DOC-002: docs/software-configuration-management-plan.md
#   ...
#   [234/234] Added CI-CFG-013: .github/workflows/ci.yml
# 
# ✅ CI registry populated: 234 CIs
#    Registry saved to: config/ci-registry.json
```

2. **Validate CI Registry**

```bash
python3 tools/scripts/ci_registry_manager.py validate

# Output:
# Validating CI registry...
# 
# 📊 Validation Results:
#    Total CIs: 234
#    Errors: 0
#    Warnings: 0
# 
# ✅ CI registry is valid
```

3. **Generate Initial Traceability Metrics**

```bash
python3 tools/workspace.py trace metrics > reports/traceability-metrics-initial.txt

# Output:
# Requirements Traceability Metrics
# ==================================
# Total Requirements: 87
# Requirements Traced to Implementation: 0 (0.0%)
# Requirements Traced to Tests: 0 (0.0%)
# 
# ⚠️  WARNING: Traceability not yet established (expected in Phase 2)
```

4. **Generate Initial Metrics Dashboard**

```bash
python3 tools/scripts/generate_metrics_dashboard.py

# Output:
# Generating metrics dashboard...
# ✅ Dashboard generated: reports/dashboard.html
#    Open in browser: file:///path/to/project/reports/dashboard.html
```

5. **Commit CI Registry to Git**

```bash
git add config/ci-registry.json
git add reports/dashboard.html
git commit -m "chore(cm): Initialize CI registry and CSA infrastructure

- Populated CI registry with 234 CIs from Git
- Generated initial metrics dashboard
- Validated CI registry (0 errors, 0 warnings)
- Traceability tracking infrastructure ready for Phase 2

Related: PHASE-1-PLANNING"

git push origin main
```

**Result**: CI registry established, CSA infrastructure ready, initial metrics generated.

---

### Scenario 2: SIL 3 Project - Monthly Status Report Generation

**Context**: End of March 2026, Gate 6 (Validation) complete. CM generates monthly summary report.

**Steps**:

1. **Sync CI Versions with Git** (ensure latest data)

```bash
python3 tools/scripts/ci_registry_manager.py sync

# Output:
# Syncing CI versions with Git...
#   ✓ CI-SRC-042: Updated to commit a1b2c3d4e5f6
#   ✓ CI-DOC-046: Updated to commit b2c3d4e5f6g7
#   ...
# 
# ✅ Sync complete: 18 CIs updated
```

2. **Generate Change Metrics**

```bash
python3 tools/workspace.py wf metrics-cr --period 30 > reports/cr-metrics-march.json

# Check summary
cat reports/cr-metrics-march.json | jq '.cr_count'

# Output:
# {
#   "total": 45,
#   "by_status": {
#     "SUBMITTED": 8,
#     "CLOSED": 20,
#     ...
#   }
# }
```

3. **Generate Traceability Metrics**

```bash
python3 tools/workspace.py trace metrics > reports/traceability-metrics-march.json

# Check forward traceability
cat reports/traceability-metrics-march.json | jq '.requirements_traceability.forward_traceability_percentage'

# Output:
# 100.0
```

4. **Generate Baseline Metrics**

```bash
python3 tools/workspace.py wf metrics-baseline > reports/baseline-metrics-march.json

# Check latest baseline
cat reports/baseline-metrics-march.json | jq '.latest_baseline'

# Output:
# {
#   "baseline_id": "BL-GATE6-001",
#   "baseline_date": "2026-03-10",
#   "total_cis": 234,
#   ...
# }
```

5. **Generate Monthly Summary Report**

```bash
python3 tools/scripts/generate_monthly_summary_report.py --month 2026-03

# Output:
# Generating monthly summary report for March 2026...
# ✅ Report generated: reports/monthly-summary-2026-03.md
```

6. **Generate Updated Dashboard**

```bash
python3 tools/scripts/generate_metrics_dashboard.py

# Output:
# Generating metrics dashboard...
# ✅ Dashboard generated: reports/dashboard.html
```

7. **Commit Reports**

```bash
git add reports/
git commit -m "chore(csa): March 2026 monthly status report

- 45 CRs processed (20 closed, 23 open)
- Gate 6 baseline (BL-GATE6-001) established
- 100% traceability achieved (2 gaps resolved)
- 234 CIs tracked (all baseline, 0 draft)

Monthly Summary: reports/monthly-summary-2026-03.md"

git push origin main
```

**Result**: Comprehensive monthly report generated, all metrics tracked, EN 50128 Table A.9 #8 (Data Recording) compliance demonstrated.

---

### Scenario 3: SIL 3 Project - Phase Gate Report (Gate 6 Validation)

**Context**: Gate 6 (Validation) approaching. COD requests gate report from CM.

**Steps**:

1. **Generate Gate Report with Full Metrics**

```bash
python3 tools/scripts/generate_gate_report.py --gate gate6_validation --full

# Output:
# Generating gate report for Gate 6 (Validation)...
# Collecting CI metrics...
# Collecting CR metrics...
# Collecting traceability metrics...
# Collecting quality metrics...
# Generating PCA/FCA checklist...
# ✅ Gate report generated: reports/gate-report-gate6-validation.md
```

2. **Review Gate Report** (example excerpt)

```bash
cat reports/gate-report-gate6-validation.md

# Output (excerpt):
# # Phase Gate Report: Gate 6 (Validation)
# 
# ## Gate Decision Criteria
# 
# | Criterion | Status | Evidence |
# |-----------|--------|----------|
# | All validation tests passed | ✅ PASS | Validation Report DOC-VAL-001 |
# | Traceability 100% | ✅ PASS | 87/87 requirements traced |
# | PCA/FCA passed | ✅ PASS | Audit reports DOC-CM-045, DOC-CM-046 |
# | All critical CRs closed | ✅ PASS | 0 critical CRs open |
# | Baseline established | ✅ PASS | BL-GATE6-001 |
# 
# **RECOMMENDATION**: ✅ GO (Proceed to Gate 7 - Assessment)
```

3. **Submit Gate Report to COD**

```bash
# Submit via workspace.py workflow
python3 tools/workspace.py wf submit-document \
  --doc-id reports/gate-report-gate6-validation.md \
  --phase gate6_validation \
  --submitter "Bob Wilson (CM)" \
  --approver "COD"

# Output:
# ✅ Document submitted for approval
#    Document: reports/gate-report-gate6-validation.md
#    Workflow ID: WF-GATE6-CM-001
#    Status: SUBMITTED
#    Awaiting approval from: COD
```

4. **COD Reviews and Approves Gate**

```bash
# COD performs gate check (separate workflow)
python3 tools/workspace.py wf gate-check gate6_validation

# Output:
# Phase Gate Check: gate6_validation
# ===================================
# ✅ All gate criteria met
# ✅ Baseline BL-GATE6-001 established
# ✅ PCA/FCA passed
# ✅ Traceability 100%
# 
# DECISION: GO (Proceed to gate7_assessment)
```

5. **Update LIFECYCLE_STATE.md**

```bash
# COD updates lifecycle state (automatic via /cod gate-check)
cat docs/LIFECYCLE_STATE.md | grep current_phase

# Output:
# current_phase: "gate7_assessment"
```

**Result**: Gate 6 passed, comprehensive CM metrics provided, EN 50128 compliance demonstrated, project proceeds to Gate 7.

---

## Summary

Configuration Status Accounting (CSA) is **MANDATORY for SIL 3-4** per EN 50128 Table A.9 #8 (Data Recording and Analysis). This workflow provides:

1. **CI Tracking**: Comprehensive CI registry with version control, checksums, traceability
2. **Change Metrics**: CR count, resolution time, backlog, trends
3. **Baseline Metrics**: Baseline count, size, composition, stability, PCA/FCA audit results
4. **Traceability Metrics**: Requirements coverage, gaps, orphaned items
5. **Status Reporting**: Weekly, monthly, gate reports with trends and compliance status
6. **Tool Integration**: workspace.py trace/wf commands, Git integration, CI/CD automation
7. **Automation Scripts**: CI registry manager, metrics dashboard generator

**EN 50128 Compliance**:
- ✅ Section 6.6.5: Configuration status accounting throughout lifecycle
- ✅ Table A.9 #8: Data Recording and Analysis (MANDATORY SIL 3-4)
- ✅ Section 6.6.6: PCA/FCA audit data collection
- ✅ Table A.9 #7: Traceability metrics (MANDATORY SIL 3-4)

**Key Tools**:
- `workspace.py trace` - CI tracking, traceability metrics
- `workspace.py wf` - CR metrics, baseline metrics, workflow tracking
- `ci_registry_manager.py` - CI registry automation
- `generate_metrics_dashboard.py` - Real-time HTML dashboard
- `generate_weekly_status_report.py` - Automated weekly reports
- `generate_monthly_summary_report.py` - Automated monthly reports
- `generate_gate_report.py` - Automated gate reports

CSA provides **visibility, transparency, and accountability** for all configuration management activities, enabling data-driven decisions and EN 50128 compliance verification.
