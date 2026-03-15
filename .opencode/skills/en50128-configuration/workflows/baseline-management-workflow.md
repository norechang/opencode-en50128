# Baseline Management Workflow for EN 50128 Configuration Management

**Document ID**: WF-CM-003  
**Version**: 1.0  
**Status**: Active  
**Skill**: en50128-configuration  
**Related Standard**: EN 50128:2011 Section 6.6, Annex C Table C.1

---

## Table of Contents

1. [Overview](#1-overview)
2. [EN 50128 Baseline Requirements](#2-en-50128-baseline-requirements)
3. [Baseline Establishment](#3-baseline-establishment)
4. [Baseline Control](#4-baseline-control)
5. [Baseline Composition](#5-baseline-composition)
6. [Physical Configuration Audit (PCA)](#6-physical-configuration-audit-pca)
7. [Functional Configuration Audit (FCA)](#7-functional-configuration-audit-fca)
8. [Baseline Release Process](#8-baseline-release-process)
9. [Tool Integration](#9-tool-integration)
10. [Automation Scripts](#10-automation-scripts)
11. [Example Scenarios](#11-example-scenarios)

---

## 1. Overview

### 1.1 Purpose

This workflow defines **baseline management** for EN 50128-compliant railway software development. Baselines represent controlled snapshots of configuration items (CIs) at specific lifecycle milestones, providing a stable foundation for further development and a reference for audits.

**Key Objectives**:
- Establish baselines at phase gates (Gate 1-7)
- Control access to baselined CIs (prevent unauthorized changes)
- Document baseline composition (complete inventory)
- Perform Physical Configuration Audits (PCA) to verify completeness
- Perform Functional Configuration Audits (FCA) to verify correctness
- Enable traceability from baselines to requirements
- Support release management and deployment

### 1.2 Scope

**Baseline types**:
1. **Planning Baseline** (Gate 1): SQAP, SCMP, SVP, SVaP approved
2. **Requirements Baseline** (Gate 2): SRS, RTM, Hazard Log approved
3. **Design Baseline** (Gate 3): SAS, SDS approved
4. **Implementation Baseline** (Gate 4): Source code, unit tests complete
5. **Integration Baseline** (Gate 5): Integration tests complete
6. **Validation Baseline** (Gate 6): System tests, validation complete
7. **Release Baseline** (Gate 7): Deployment-ready package

**Out of Scope**:
- Work-in-progress (before baseline establishment)
- Temporary build artifacts (not CIs)
- External dependencies (tracked via manifest, not included in baseline)

### 1.3 SIL-Specific Requirements

| Requirement | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 |
|-------------|-------|-------|-------|-------|-------|
| Baseline at phase gates | **M** | **M** | **M** | **M** | **M** |
| Baseline documentation | R | HR | **M** | **M** | **M** |
| Baseline freeze (immutability) | R | HR | **M** | **M** | **M** |
| Change control for baselines | **M** | **M** | **M** | **M** | **M** |
| Physical Configuration Audit (PCA) | R | HR | **M** | **M** | **M** |
| Functional Configuration Audit (FCA) | - | R | HR | **M** | **M** |
| Independent audit (PCA/FCA) | - | - | R | **M** | **M** |
| Baseline traceability to requirements | R | HR | **M** | **M** | **M** |
| Signed baseline tags (GPG) | - | R | HR | **M** | **M** |
| Baseline archival (long-term) | R | HR | **M** | **M** | **M** |

**Legend**: M = Mandatory, HR = Highly Recommended, R = Recommended, - = No recommendation

### 1.4 EN 50128 References

- **Section 6.6**: Software Configuration Management (baseline control)
- **Section 6.6.4.1(f)**: Baseline update after change
- **Section 6.6.6**: Configuration Audits (PCA, FCA)
- **Annex C Table C.1**: Document control summary (baseline triggers)
- **Section 5.3.2**: Lifecycle phases (baseline at phase completion)
- **Table A.9 #5**: Software Configuration Management (MANDATORY ALL SIL)

---

## 2. EN 50128 Baseline Requirements

### 2.1 Configuration Management Plan (Section 6.6)

EN 50128 Section 6.6 requires:

> "Software Configuration Management shall provide the administrative and technical procedures for:
> - Identifying and documenting the functional and physical characteristics of a configuration item
> - **Controlling changes to those characteristics**
> - Recording and reporting change processing and implementation status
> - Verifying compliance with specified requirements"

**Baselines** are the mechanism for "controlling changes" - once a baseline is established, changes require formal change control (CR process).

### 2.2 Configuration Audits (Section 6.6.6)

EN 50128 Section 6.6.6 defines two types of audits:

**Physical Configuration Audit (PCA)**:
- Verifies that all CIs in the baseline exist and are correctly identified
- Checks that baseline documentation matches actual CI contents
- Confirms version numbers, file names, checksums are correct
- **MANDATORY for SIL 3-4** (highly recommended SIL 2)

**Functional Configuration Audit (FCA)**:
- Verifies that baselined CIs meet their specified requirements
- Checks that test results demonstrate requirement satisfaction
- Confirms traceability from CIs to requirements
- **MANDATORY for SIL 3-4** (highly recommended SIL 2)

### 2.3 Baseline Triggers (Annex C Table C.1)

EN 50128 Annex C Table C.1 defines **document control** per lifecycle phase. Baselines are established when documents for a phase are approved:

| Phase | Baseline | Trigger Documents | Gate Check |
|-------|----------|-------------------|------------|
| Phase 1: Planning | Planning Baseline | SQAP, SCMP, SVP, SVaP approved | Gate 1 |
| Phase 2: Requirements | Requirements Baseline | SRS, RTM, Hazard Log approved | Gate 2 |
| Phase 3: Architecture & Design | Design Baseline | SAS, SDS approved | Gate 3 |
| Phase 4: Implementation | Implementation Baseline | Source code, unit tests complete | Gate 4 |
| Phase 5: Integration | Integration Baseline | Integration tests complete | Gate 5 |
| Phase 6: Validation | Validation Baseline | System tests, validation report approved | Gate 6 |
| Phase 7: Assessment (SIL 3-4) | - | Assessment report approved | Gate 7a |
| Phase 8: Deployment | Release Baseline | Release package approved | Gate 7 (or 7b) |

**Note**: COD (Lifecycle Coordinator) enforces gate checks; CM (Configuration Manager) establishes baselines after gate approval.

### 2.4 Baseline Immutability

**Critical principle**: Once a baseline is established, it is **IMMUTABLE**.

- CIs in a baseline CANNOT be modified directly
- Any change requires formal CR process (see Change Control Workflow WF-CM-002)
- Change results in NEW baseline (e.g., v1.0 → v1.1 after CR implementation)

**Enforcement**:
- Git tags are immutable (cannot be changed once pushed)
- Branch protection prevents force push to baseline tags
- Archive baselines to read-only storage (SIL 3-4)

---

## 3. Baseline Establishment

### 3.1 Baseline Establishment Process

**Prerequisites**:
1. All deliverables for the phase are complete
2. Quality checks passed (QUA reviews completed)
3. Verification completed (VER approval obtained)
4. Gate check passed (COD approval obtained)
5. Traceability complete (RTM up-to-date)

**Steps**:

**Step 1: Verify Phase Completion**
```bash
# CM checks LIFECYCLE_STATE.md for gate approval
cat LIFECYCLE_STATE.md | grep "gate2-requirements"
# Output: gate2-requirements: APPROVED (2024-03-15 by COD)

# Verify all required documents exist
ls docs/requirements/
# Expected: SRS-v1.0.md, RTM-v1.0.md

# Verify QUA and VER approval
grep "Approved-by" docs/requirements/SRS-v1.0.md
# Expected: QUA: Alice Johnson (2024-03-10)
#           VER: Bob Smith (2024-03-12)
```

**Step 2: Create Baseline Tag**
```bash
# Create annotated, signed tag (MANDATORY SIL 3-4)
git tag -s baseline/gate2-requirements -m "Requirements Baseline (Gate 2)

Phase: Gate 2 (Requirements)
Date: 2024-03-15
Approved by: COD (Lifecycle Coordinator)

Contents:
- Software Requirements Specification (SRS-v1.0.md)
- Requirements Traceability Matrix (RTM-v1.0.md)
- Hazard Log (Hazard-Log-v1.0.md)
- Software Quality Assurance Plan (SQAP-v1.0.md)
- Software Configuration Management Plan (SCMP-v1.0.md)

Verification:
- QUA approval: Alice Johnson (2024-03-10)
- VER approval: Bob Smith (2024-03-12)
- COD gate check: PASS (2024-03-15)

Traceability:
- 50 requirements defined
- 100% traced to stakeholder needs
- RTM complete and verified

Quality Metrics:
- SRS review: 0 major issues, 5 minor issues (resolved)
- Requirements clarity: 100% unambiguous
- Testability: 100% verifiable

Signed-off-by: John Doe (CM) <john.doe@company.com>
GPG Key: 0x12345678ABCDEF
"

# Verify tag signature
git tag -v baseline/gate2-requirements
# Expected: gpg: Good signature from "John Doe (CM) <john.doe@company.com>"

# Push tag to remote
git push origin baseline/gate2-requirements
```

**Step 3: Document Baseline Composition**
```bash
# Create baseline documentation
workspace.py wf create-baseline gate2-requirements

# Output: ✅ Baseline documentation created: docs/baselines/gate2-requirements.md

# Baseline manifest generated automatically:
cat docs/baselines/gate2-requirements.md
```

**Baseline documentation template**:

```markdown
# Baseline: gate2-requirements

**Baseline ID**: baseline/gate2-requirements  
**Phase**: Gate 2 (Requirements)  
**Date**: 2024-03-15  
**Git Tag**: baseline/gate2-requirements  
**Git Commit**: a1b2c3d4e5f6789012345678901234567890abcd  
**Approved by**: COD (Lifecycle Coordinator)  

## Baseline Composition

### Documents

| Document | Version | File Path | Checksum (SHA-256) |
|----------|---------|-----------|-------------------|
| Software Requirements Specification | v1.0 | docs/requirements/SRS-v1.0.md | 3a5f7c9d... |
| Requirements Traceability Matrix | v1.0 | docs/requirements/RTM-v1.0.md | 8b4e6a2c... |
| Hazard Log | v1.0 | docs/safety/Hazard-Log-v1.0.md | 1d7f9e3b... |
| Software Quality Assurance Plan | v1.0 | plans/SQAP-v1.0.md | 6c2a8d4f... |
| Software Configuration Management Plan | v1.0 | plans/SCMP-v1.0.md | 9f5b3e7a... |

### Source Code

| Component | Files | Lines of Code | Checksum |
|-----------|-------|---------------|----------|
| (None - requirements phase) | - | - | - |

### Tests

| Test Suite | Files | Test Count | Checksum |
|------------|-------|------------|----------|
| (None - requirements phase) | - | - | - |

### Total Baseline Size

- Documents: 5 files, ~15,000 words
- Source code: 0 files, 0 lines
- Tests: 0 files, 0 tests

## Requirements Summary

- Total requirements: 50
- Functional requirements: 35
- Non-functional requirements: 10
- Safety requirements: 5
- Traceability: 100% (50/50 traced to stakeholder needs)

## Verification Status

- QUA approval: Alice Johnson (2024-03-10)
- VER approval: Bob Smith (2024-03-12)
- COD gate check: PASS (2024-03-15)

## Physical Configuration Audit (PCA)

- Status: SCHEDULED (2024-03-20)
- Auditor: Bob Smith (VER, independent)

## Functional Configuration Audit (FCA)

- Status: SCHEDULED (2024-03-22)
- Auditor: Carol White (VMGR, independent)

## Change Control

- Baseline frozen: YES
- Changes require: CR approval via CCB
- Next baseline: gate3-design (after Gate 3 completion)

---

**Baseline established by**: John Doe (CM)  
**Date**: 2024-03-15  
**Signature**: (GPG signature embedded in Git tag)
```

**Step 4: Update Baseline Registry**
```bash
# Append to baseline registry
cat >> docs/baselines/BASELINE_REGISTRY.md << EOF

## baseline/gate2-requirements

- **Date**: 2024-03-15
- **Phase**: Gate 2 (Requirements)
- **Git Tag**: baseline/gate2-requirements
- **Git Commit**: a1b2c3d4e5f6
- **Approved by**: COD
- **PCA Status**: Scheduled (2024-03-20)
- **FCA Status**: Scheduled (2024-03-22)
- **Documentation**: [docs/baselines/gate2-requirements.md](./gate2-requirements.md)

EOF

# Commit baseline documentation
git add docs/baselines/
git commit -m "chore(cm): Establish baseline gate2-requirements

Baseline for Gate 2 (Requirements) established.

Contents:
- SRS-v1.0.md (50 requirements)
- RTM-v1.0.md (100% traceability)
- Hazard-Log-v1.0.md (5 hazards identified)

Approvals:
- QUA: Alice Johnson
- VER: Bob Smith
- COD: Gate 2 PASS

Next steps:
- PCA scheduled 2024-03-20
- FCA scheduled 2024-03-22

[Baseline-Gate2] Requirements baseline establishment
" --signoff

git push origin develop
```

**Step 5: Notify Stakeholders**
```bash
# Automated notification (via CI webhook or email)
# Notify: PM, COD, QUA, VER, VMGR, team

echo "Baseline gate2-requirements established. PCA/FCA scheduled."
```

### 3.2 Baseline Naming Conventions

**Baseline tag format**:

```
baseline/gate<N>-<phase-name>[-v<version>]
```

**Examples**:

- `baseline/gate1-planning` - Initial planning baseline
- `baseline/gate2-requirements` - Initial requirements baseline
- `baseline/gate2-requirements-v1.1` - Updated requirements baseline (after CR)
- `baseline/gate3-design` - Initial design baseline
- `baseline/gate4-implementation` - Initial implementation baseline
- `baseline/gate5-integration` - Initial integration baseline
- `baseline/gate6-validation` - Initial validation baseline
- `baseline/gate7-release` - Release baseline (deployment-ready)

**Release baselines** (Gate 7) use semantic versioning:

- `v1.0.0` - First production release
- `v1.0.1` - Patch release (bug fixes)
- `v1.1.0` - Minor release (new features, backward compatible)
- `v2.0.0` - Major release (breaking changes)

### 3.3 Baseline Update (After Change)

**After CR implementation**, a new baseline may be created:

**Minor change** (bug fix, documentation update):
- Update existing baseline: `baseline/gate4-implementation` → `baseline/gate4-implementation-v1.1`
- Or create patch release: `v1.0.0` → `v1.0.1`

**Major change** (new feature, requirement change):
- Create new gate baseline: `baseline/gate3-design` → `baseline/gate3-design-v2.0`
- Or create minor release: `v1.0.0` → `v1.1.0`

**Breaking change** (API change, architecture change):
- Create new major release: `v1.0.0` → `v2.0.0`

**Example**:

```bash
# After CR-123 (null pointer fix) implemented and verified
# Determine baseline impact: Patch (bug fix, < 1% code change)

# Create updated baseline
git tag -s baseline/gate4-implementation-v1.1 -m "Implementation Baseline v1.1

Updated baseline after CR-123 (null pointer fix).

Changes:
- CR-123: Fix null pointer dereference in timeout module

Verification:
- All tests pass (16/16)
- Coverage: 100%
- Static analysis: Clean
- VER approval: Bob Smith (2024-03-13)
- VMGR approval: Carol White (2024-03-13)

Previous baseline: baseline/gate4-implementation (2024-03-01)
"

git push origin baseline/gate4-implementation-v1.1

# Update baseline documentation
workspace.py wf update-baseline gate4-implementation-v1.1 --previous gate4-implementation
```

---

## 4. Baseline Control

### 4.1 Baseline Freeze

**Once baseline established**, all CIs in the baseline are **FROZEN**:

- No direct modifications allowed
- Any change requires CR approval (see Change Control Workflow WF-CM-002)
- Git tag is immutable (cannot be modified or deleted)
- Branch protection enforces freeze

**Enforcement mechanisms**:

**1. Git Tag Immutability**
```bash
# Tags cannot be changed once pushed
git tag -f baseline/gate2-requirements  # FORBIDDEN (force retag)
# Remote will reject: error: cannot force update immutable ref
```

**2. Branch Protection** (GitHub/GitLab/Bitbucket)
```yaml
# Baseline tags protected
tag_protection:
  - pattern: "baseline/*"
    allowed_to_create: [maintainer]
    allowed_to_delete: [nobody]
  - pattern: "v*"
    allowed_to_create: [maintainer]
    allowed_to_delete: [nobody]
```

**3. Repository Configuration**
```bash
# Prevent tag deletion locally
git config --local receive.denyDeletes true

# Prevent non-fast-forward updates
git config --local receive.denyNonFastForwards true
```

### 4.2 Change Control for Baselined CIs

**To modify a baselined CI**:

1. **Submit CR** (see Change Control Workflow WF-CM-002)
   - Describe change
   - Identify affected CIs (in baseline)
   - Perform impact analysis

2. **CCB Approval**
   - CCB reviews CR
   - Assesses impact on baseline
   - Approves/rejects

3. **Implementation**
   - Create branch from baseline: `git checkout -b bugfix/CR-123 baseline/gate4-implementation`
   - Implement change
   - Test thoroughly (re-verification)

4. **Merge and New Baseline**
   - Merge to main branch
   - Create NEW baseline: `baseline/gate4-implementation-v1.1`
   - Old baseline remains frozen (historical reference)

**Example**:

```bash
# Scenario: Fix bug in baselined code

# Step 1: Create branch from baseline
git checkout -b bugfix/CR-123-null-pointer baseline/gate4-implementation

# Step 2: Implement fix
# [Modify code, tests]
git commit -m "fix(timeout): Add bounds check [CR-123]" --signoff

# Step 3: Create PR, review, verify
# [PR review, CI passes, VER approval]

# Step 4: Merge to main
git checkout main
git merge --no-ff bugfix/CR-123-null-pointer

# Step 5: Create new baseline
git tag -s baseline/gate4-implementation-v1.1 -m "Implementation Baseline v1.1 (CR-123)"
git push origin main baseline/gate4-implementation-v1.1

# Step 6: Update baseline documentation
workspace.py wf update-baseline gate4-implementation-v1.1 --cr CR-123

# Old baseline (gate4-implementation) remains frozen, unchanged
```

### 4.3 Baseline Deviation Tracking

**Deviations** from baseline (temporary exceptions) are tracked:

**Use case**: Critical production issue requires emergency patch before formal CR process completes.

**Process**:

1. **Document deviation**
   ```yaml
   # docs/baselines/deviations/DEV-001.yaml
   deviation_id: DEV-001
   baseline: baseline/gate4-implementation
   reason: "Critical production bug requires immediate fix (CR-456)"
   affected_cis:
     - src/timeout.c
   temporary_fix: "Hotfix branch deployed to production"
   permanent_solution: "CR-456 in progress, will update baseline"
   approved_by: "VMGR (emergency authority)"
   date: 2024-03-20
   expiration: 2024-03-27  # Must resolve within 1 week
   ```

2. **Track deviation status**
   ```bash
   workspace.py wf create-deviation DEV-001 --baseline gate4-implementation --reason "Critical bug" --expiration "2024-03-27"
   ```

3. **Resolve deviation**
   - Complete CR-456 process
   - Create new baseline incorporating fix
   - Close deviation: `workspace.py wf close-deviation DEV-001 --baseline gate4-implementation-v1.2`

**SIL 3-4 constraint**: Deviations require VMGR approval and MUST be resolved within defined timeframe (typically 1 week).

---

## 5. Baseline Composition

### 5.1 Configuration Items (CIs) in Baseline

**Complete inventory** of CIs included in each baseline:

**Gate 1: Planning Baseline**
- Software Quality Assurance Plan (SQAP)
- Software Configuration Management Plan (SCMP)
- Software Verification Plan (SVP)
- Software Validation Plan (SVaP)
- Project schedule
- Risk register

**Gate 2: Requirements Baseline**
- Software Requirements Specification (SRS)
- Requirements Traceability Matrix (RTM)
- Hazard Log
- SQAP, SCMP, SVP, SVaP (from Gate 1)

**Gate 3: Design Baseline**
- Software Architecture Specification (SAS)
- Software Design Specification (SDS)
- Interface specifications (if separate)
- SRS, RTM, Hazard Log (from Gate 2)

**Gate 4: Implementation Baseline**
- Source code (all `.c`, `.h` files)
- Unit tests (all unit test files)
- Build scripts (Makefile, CMakeLists.txt)
- SAS, SDS (from Gate 3)
- SRS, RTM (from Gate 2)

**Gate 5: Integration Baseline**
- Source code (from Gate 4)
- Integration tests (all integration test files)
- Integration test reports
- SDS (from Gate 3)

**Gate 6: Validation Baseline**
- Source code (from Gate 4/5)
- System tests (all system test files)
- Validation test reports
- Validation Report (VaR)
- SRS, RTM (final versions)

**Gate 7: Release Baseline**
- Complete source code
- Complete test suite (unit, integration, system)
- All documentation (SRS, SAS, SDS, RTM, plans, reports)
- Release notes
- Deployment package (binary, configuration files)
- User documentation (if applicable)

### 5.2 Baseline Manifest

**Manifest file** lists all CIs in baseline with checksums:

```yaml
# docs/baselines/manifests/gate4-implementation.yaml

baseline_id: baseline/gate4-implementation
git_tag: baseline/gate4-implementation
git_commit: a1b2c3d4e5f6789012345678901234567890abcd
date: 2024-03-15
phase: gate4-implementation
approved_by: COD

configuration_items:
  source_code:
    - path: src/main.c
      checksum: sha256:3a5f7c9d1b8e6a2c4f0d9e7b5a3c1f8d6e4b2a0c9f7e5d3b1a8f6e4c2a0d9e7b
      lines: 250
      complexity: 25
    
    - path: src/timeout.c
      checksum: sha256:8b4e6a2c1f9d7e5b3a0c8f6e4d2b0a9f7e5c3d1b8f6a4e2c0d9f7e5b3a1c8f6
      lines: 150
      complexity: 10
    
    - path: include/timeout.h
      checksum: sha256:1d7f9e3b5a2c0f8e6d4b2a0c9f7e5d3b1a8f6e4c2a0d9e7b5a3c1f8d6e4b2a0
      lines: 30
      complexity: 0
  
  tests:
    - path: tests/unit_test_main.c
      checksum: sha256:6c2a8d4f0b9e7c5a3d1f8e6c4b2a0d9f7e5c3b1a8f6d4e2c0a9f7e5d3b1c8f6
      test_count: 10
    
    - path: tests/unit_test_timeout.c
      checksum: sha256:9f5b3e7a1c8d6f4b2e0a9d7f5c3e1b8f6d4a2c0e9f7d5b3a1c8f6e4d2b0a9f7
      test_count: 16
  
  documentation:
    - path: docs/requirements/SRS-v1.0.md
      checksum: sha256:2e0a8f6d4c2b0a9f7e5d3c1b8f6e4d2a0c9f7e5b3a1d8f6c4e2b0a9d7f5c3e1
      word_count: 5000
    
    - path: docs/design/SAS-v1.0.md
      checksum: sha256:5c3a1f8e6d4b2a0c9f7e5d3b1a8f6e4c2a0d9f7e5b3a1c8f6d4e2b0a9f7e5c3
      word_count: 3000
    
    - path: docs/design/SDS-v1.0.md
      checksum: sha256:8a1c6f4e2d0b9f7e5c3a1d8f6e4b2a0c9f7d5e3b1a8f6c4e2d0b9a7f5e3c1a8
      word_count: 4000
  
  build_scripts:
    - path: Makefile
      checksum: sha256:0b9d7f5e3c1a8f6d4e2b0a9c7f5e3d1b8a6f4e2c0d9a7f5c3e1b8f6d4c2a0b9
      lines: 100

summary:
  total_source_files: 3
  total_source_lines: 430
  total_tests: 2
  total_test_count: 26
  total_docs: 3
  total_build_files: 1

metrics:
  code_coverage: 100%
  cyclomatic_complexity: 35 (max 10 per function)
  misra_violations: 0 (mandatory)
  static_analysis_issues: 0

verification:
  unit_tests: 26/26 PASS
  integration_tests: 3/3 PASS
  static_analysis: CLEAN
  code_review: APPROVED (QUA, VER)

approvals:
  qua: Alice Johnson (2024-03-10)
  ver: Bob Smith (2024-03-12)
  cod: Gate 4 PASS (2024-03-15)
```

**Generate manifest automatically**:

```bash
# Generate baseline manifest
python3 tools/baseline_manager.py --baseline gate4-implementation --generate-manifest

# Output: docs/baselines/manifests/gate4-implementation.yaml
```

### 5.3 External Dependencies

**External dependencies** (libraries, tools) are tracked separately:

```yaml
# docs/baselines/dependencies/gate4-implementation.yaml

baseline_id: baseline/gate4-implementation

external_dependencies:
  compilers:
    - name: gcc
      version: 11.2.0
      checksum: sha256:abc123...
      qualification: T2 (qualified for SIL 3)
  
  libraries:
    - name: Unity (test framework)
      version: 2.5.2
      source: https://github.com/ThrowTheSwitch/Unity
      checksum: sha256:def456...
      license: MIT
  
  tools:
    - name: cppcheck
      version: 2.10
      purpose: Static analysis
      checksum: sha256:ghi789...
      qualification: T1 (no qualification)
  
  operating_system:
    - name: Linux
      version: Ubuntu 22.04 LTS
      kernel: 5.15.0
      purpose: Development environment
```

**Why separate?**
- External dependencies not stored in Git (large, not owned by project)
- Version and checksum recorded for reproducibility
- License information tracked for compliance
- Qualification status documented (EN 50128 Section 6.7 Tool Qualification)

---

## 6. Physical Configuration Audit (PCA)

### 6.1 PCA Purpose and Scope

**EN 50128 Section 6.6.6** defines PCA:

> "The Physical Configuration Audit verifies that the actual configuration items correspond to the documented configuration."

**Purpose**:
- Verify all CIs in baseline documentation actually exist
- Verify checksums match (no corruption, no unauthorized changes)
- Verify version numbers are correct
- Verify baseline is complete (no missing CIs)

**Scope**:
- All CIs listed in baseline manifest
- All documentation references
- All traceability links

**MANDATORY for SIL 3-4** (highly recommended SIL 2)

### 6.2 PCA Process

**Prerequisites**:
- Baseline established
- Baseline documentation complete (manifest, composition document)
- Independent auditor assigned (VER team, not involved in development)

**Steps**:

**Step 1: PCA Planning**
```bash
# CM schedules PCA
workspace.py wf schedule-pca gate4-implementation --auditor "Bob Smith (VER)" --date "2024-03-20"

# Output: PCA scheduled for baseline gate4-implementation
# Auditor: Bob Smith (VER)
# Date: 2024-03-20
```

**Step 2: PCA Checklist Preparation**

```markdown
# Physical Configuration Audit Checklist: gate4-implementation

**Baseline**: baseline/gate4-implementation  
**Auditor**: Bob Smith (VER)  
**Date**: 2024-03-20  

## Checklist Items

### 1. Baseline Tag Verification

- [ ] Git tag exists: `git tag -l baseline/gate4-implementation`
- [ ] Tag is annotated: `git show baseline/gate4-implementation`
- [ ] Tag is signed (SIL 3-4): `git tag -v baseline/gate4-implementation`
- [ ] Tag signature valid (SIL 3-4): Check GPG key
- [ ] Tag message complete: Includes phase, date, approvals

### 2. Baseline Documentation Verification

- [ ] Baseline composition document exists: `docs/baselines/gate4-implementation.md`
- [ ] Baseline manifest exists: `docs/baselines/manifests/gate4-implementation.yaml`
- [ ] Baseline registry updated: `docs/baselines/BASELINE_REGISTRY.md` includes entry
- [ ] Dependencies documented: `docs/baselines/dependencies/gate4-implementation.yaml`

### 3. Source Code Verification

For each source file in manifest:
- [ ] File exists at specified path
- [ ] Checksum matches: `sha256sum <file>` == manifest checksum
- [ ] File not modified since baseline: `git diff baseline/gate4-implementation -- <file>` (should be empty)

Example:
```bash
# Check src/timeout.c
sha256sum src/timeout.c
# Compare to manifest checksum: 8b4e6a2c1f9d7e5b3a0c8f6e4d2b0a9f7e5c3d1b8f6a4e2c0d9f7e5b3a1c8f6

git diff baseline/gate4-implementation -- src/timeout.c
# Expected: (empty output, no diff)
```

- [ ] src/main.c: Exists ✓, Checksum matches ✓, Unmodified ✓
- [ ] src/timeout.c: Exists ✓, Checksum matches ✓, Unmodified ✓
- [ ] include/timeout.h: Exists ✓, Checksum matches ✓, Unmodified ✓

### 4. Test Verification

For each test file in manifest:
- [ ] Test file exists
- [ ] Checksum matches
- [ ] Test count matches manifest

- [ ] tests/unit_test_main.c: Exists ✓, Checksum matches ✓, 10 tests ✓
- [ ] tests/unit_test_timeout.c: Exists ✓, Checksum matches ✓, 16 tests ✓

### 5. Documentation Verification

For each document in manifest:
- [ ] Document exists
- [ ] Checksum matches
- [ ] Version number correct

- [ ] docs/requirements/SRS-v1.0.md: Exists ✓, Checksum matches ✓, Version v1.0 ✓
- [ ] docs/design/SAS-v1.0.md: Exists ✓, Checksum matches ✓, Version v1.0 ✓
- [ ] docs/design/SDS-v1.0.md: Exists ✓, Checksum matches ✓, Version v1.0 ✓

### 6. Build Scripts Verification

- [ ] Makefile: Exists ✓, Checksum matches ✓

### 7. Completeness Check

- [ ] All CIs in manifest accounted for
- [ ] No extra CIs in baseline (not in manifest)
- [ ] No missing CIs (in manifest but not in baseline)

### 8. Traceability Verification

- [ ] RTM references correct baseline: `grep "baseline/gate4-implementation" docs/requirements/RTM-v1.0.md`
- [ ] All requirements traced: `workspace.py trace validate-ci --baseline gate4-implementation`

### 9. Approval Verification

- [ ] QUA approval documented: Check SDS footer
- [ ] VER approval documented: Check SDS footer
- [ ] COD gate approval: Check LIFECYCLE_STATE.md

## PCA Result

- **Status**: [PASS / FAIL / CONDITIONAL PASS]
- **Issues Found**: [Count]
- **Major Issues**: [Count]
- **Minor Issues**: [Count]

## Issues Log

| ID | Severity | Description | Resolution |
|----|----------|-------------|------------|
| (None) | - | - | - |

## Conclusion

[PASS / FAIL summary]

---

**Auditor**: Bob Smith (VER)  
**Signature**: _________________  
**Date**: 2024-03-20
```

**Step 3: Execute PCA**

Auditor performs checks:

```bash
# 1. Verify tag exists and is signed
git tag -l baseline/gate4-implementation
git tag -v baseline/gate4-implementation

# 2. Verify baseline documentation
ls docs/baselines/gate4-implementation.md
ls docs/baselines/manifests/gate4-implementation.yaml

# 3. Automated checksum verification
python3 tools/baseline_manager.py --baseline gate4-implementation --verify-checksums

# Output:
# Verifying checksums for baseline gate4-implementation...
# ✓ src/main.c: Checksum matches
# ✓ src/timeout.c: Checksum matches
# ✓ include/timeout.h: Checksum matches
# ✓ tests/unit_test_main.c: Checksum matches
# ✓ tests/unit_test_timeout.c: Checksum matches
# ✓ docs/requirements/SRS-v1.0.md: Checksum matches
# ✓ docs/design/SAS-v1.0.md: Checksum matches
# ✓ docs/design/SDS-v1.0.md: Checksum matches
# ✓ Makefile: Checksum matches
# 
# Result: All checksums verified (9/9)

# 4. Verify no modifications since baseline
git diff baseline/gate4-implementation

# Expected: (empty, no output)

# 5. Verify traceability
workspace.py trace validate-ci --baseline gate4-implementation

# Output: ✅ Traceability: PASS
```

**Step 4: Document PCA Results**

```markdown
# Physical Configuration Audit Report: gate4-implementation

**Baseline**: baseline/gate4-implementation  
**Auditor**: Bob Smith (VER, independent)  
**Date**: 2024-03-20  
**Result**: **PASS**  

## Summary

Physical Configuration Audit completed for baseline gate4-implementation.
All configuration items verified against baseline manifest.

- **Total CIs**: 9 (3 source, 2 tests, 3 docs, 1 build)
- **Verified**: 9/9 (100%)
- **Checksum matches**: 9/9 (100%)
- **Issues found**: 0

## Verification Results

### Source Code
- ✓ src/main.c: Exists, checksum matches, unmodified
- ✓ src/timeout.c: Exists, checksum matches, unmodified
- ✓ include/timeout.h: Exists, checksum matches, unmodified

### Tests
- ✓ tests/unit_test_main.c: Exists, checksum matches, 10 tests
- ✓ tests/unit_test_timeout.c: Exists, checksum matches, 16 tests

### Documentation
- ✓ docs/requirements/SRS-v1.0.md: Exists, checksum matches, version correct
- ✓ docs/design/SAS-v1.0.md: Exists, checksum matches, version correct
- ✓ docs/design/SDS-v1.0.md: Exists, checksum matches, version correct

### Build Scripts
- ✓ Makefile: Exists, checksum matches

### Baseline Documentation
- ✓ Baseline composition document: Complete
- ✓ Baseline manifest: Complete and accurate
- ✓ Baseline registry: Updated
- ✓ Dependencies documented

### Traceability
- ✓ RTM references correct baseline
- ✓ All requirements traced (50/50)
- ✓ Traceability validation: PASS

### Approvals
- ✓ QUA approval: Alice Johnson (2024-03-10)
- ✓ VER approval: Bob Smith (2024-03-12)
- ✓ COD gate approval: PASS (2024-03-15)

## Issues

**Major Issues**: 0  
**Minor Issues**: 0  

## Conclusion

Physical Configuration Audit **PASSED** for baseline gate4-implementation.

- All CIs exist and match manifest
- All checksums verified
- No unauthorized modifications detected
- Baseline documentation complete
- Traceability verified
- Approvals documented

Baseline gate4-implementation is physically correct and complete.

---

**Auditor**: Bob Smith (VER)  
**Signature**: [GPG signature]  
**Date**: 2024-03-20  

**Approved by**: Carol White (VMGR)  
**Date**: 2024-03-21
```

**Step 5: Archive PCA Report**

```bash
# Store PCA report
git add docs/audits/PCA-gate4-implementation-2024-03-20.md
git commit -m "docs(audit): PCA report for gate4-implementation

Physical Configuration Audit completed for baseline gate4-implementation.

Result: PASS
Auditor: Bob Smith (VER)
Date: 2024-03-20

All CIs verified (9/9), all checksums match, no issues found.

[PCA-Gate4] Physical Configuration Audit report
" --signoff

git push origin develop
```

### 6.3 PCA Failure Handling

**If PCA fails** (issues found):

**Example issues**:
- Checksum mismatch (file modified after baseline)
- Missing CI (file in manifest but not in repository)
- Extra CI (file in repository but not in manifest)
- Documentation incomplete

**Resolution**:

1. **Document issue** in PCA report
2. **Investigate root cause**
   - Unauthorized change?
   - Manifest error?
   - Git corruption?
3. **Determine corrective action**
   - If unauthorized change: Revert to baseline, discipline responsible party
   - If manifest error: Update manifest, re-establish baseline
   - If Git corruption: Restore from backup
4. **Implement corrective action**
5. **Re-run PCA** to verify resolution
6. **Update PCA report** with final status

**Example**:

```markdown
## Issues

### Issue PCA-001: Checksum Mismatch

- **Severity**: MAJOR
- **CI**: src/timeout.c
- **Description**: Checksum does not match manifest
  - Expected: 8b4e6a2c1f9d7e5b3a0c8f6e4d2b0a9f7e5c3d1b8f6a4e2c0d9f7e5b3a1c8f6
  - Actual: 1a2b3c4d5e6f7a8b9c0d1e2f3a4b5c6d7e8f9a0b1c2d3e4f5a6b7c8d9e0f1a2
- **Root Cause**: Unauthorized modification after baseline establishment (commit f9e8d7c6)
- **Corrective Action**: 
  - Revert unauthorized change: `git revert f9e8d7c6`
  - Re-verify checksum
  - Discipline: Warning issued to developer
- **Resolution Date**: 2024-03-21
- **Status**: RESOLVED

## PCA Re-run Result

**Date**: 2024-03-21  
**Result**: **PASS**  

All issues resolved. Baseline gate4-implementation physically correct.
```

---

## 7. Functional Configuration Audit (FCA)

### 7.1 FCA Purpose and Scope

**EN 50128 Section 6.6.6** defines FCA:

> "The Functional Configuration Audit verifies that the configuration items meet their specified requirements."

**Purpose**:
- Verify all requirements implemented in baseline
- Verify all tests executed and passed
- Verify traceability from requirements to tests to code
- Verify baseline meets functional and safety requirements

**Scope**:
- All requirements in SRS
- All test results (unit, integration, system)
- All verification evidence (static analysis, code review, coverage)
- Traceability completeness

**MANDATORY for SIL 3-4** (highly recommended SIL 2)

### 7.2 FCA Process

**Prerequisites**:
- PCA completed and passed
- All verification activities complete
- All test results available

**Steps**:

**Step 1: FCA Planning**
```bash
# CM schedules FCA (after PCA)
workspace.py wf schedule-fca gate4-implementation --auditor "Carol White (VMGR)" --date "2024-03-22"

# Output: FCA scheduled for baseline gate4-implementation
# Auditor: Carol White (VMGR, independent)
# Date: 2024-03-22
```

**Step 2: FCA Checklist Preparation**

```markdown
# Functional Configuration Audit Checklist: gate4-implementation

**Baseline**: baseline/gate4-implementation  
**Auditor**: Carol White (VMGR)  
**Date**: 2024-03-22  

## Checklist Items

### 1. Requirements Implementation

For each requirement in SRS:
- [ ] Requirement implemented (code exists)
- [ ] Requirement traced to code (RTM entry)
- [ ] Implementation verified (test exists)
- [ ] Test passed

Example:
- [ ] REQ-42: Timeout detection implemented (src/timeout.c)
- [ ] REQ-42: Traced in RTM (commit a1b2c3d)
- [ ] REQ-42: Test exists (test_timeout_detection_100ms)
- [ ] REQ-42: Test passed (PASS)

**Automated check**:
```bash
workspace.py trace validate-req REQ-42
# Output: ✅ REQ-42: Implemented, traced, tested, PASS
```

- [ ] REQ-01: ✓ Implemented, ✓ Traced, ✓ Tested, ✓ PASS
- [ ] REQ-02: ✓ Implemented, ✓ Traced, ✓ Tested, ✓ PASS
- [ ] ... (all 50 requirements)
- [ ] REQ-50: ✓ Implemented, ✓ Traced, ✓ Tested, ✓ PASS

**Summary**: 50/50 requirements (100%)

### 2. Test Results Verification

- [ ] Unit tests executed: `make test`
- [ ] Unit tests passed: 26/26 (100%)
- [ ] Integration tests executed: `make integration-test`
- [ ] Integration tests passed: 3/3 (100%)
- [ ] Test results archived: `docs/verification/test-results-gate4.xml`

### 3. Coverage Verification (SIL 3-4)

- [ ] Statement coverage measured: `make coverage`
- [ ] Statement coverage ≥ 100%: 100% (PASS)
- [ ] Branch coverage ≥ 100%: 100% (PASS)
- [ ] Condition coverage ≥ 100%: 100% (PASS) (SIL 3-4)
- [ ] Coverage report archived: `docs/verification/coverage-report-gate4.html`

### 4. Static Analysis Verification

- [ ] Cppcheck executed: `cppcheck --enable=all src/`
- [ ] Cppcheck issues: 0 critical (PASS)
- [ ] Clang Static Analyzer executed: `scan-build make`
- [ ] Clang issues: 0 (PASS)
- [ ] MISRA C check executed (SIL 3-4): `python3 tools/check_misra.py src/`
- [ ] MISRA C violations: 0 mandatory (PASS)
- [ ] Static analysis report archived: `docs/verification/static-analysis-gate4.md`

### 5. Code Review Verification

- [ ] Code review completed: All code reviewed (QUA, VER)
- [ ] Code review issues resolved: 0 open issues
- [ ] Code review report archived: `docs/verification/code-review-gate4.md`

### 6. Complexity Verification (SIL 3-4)

- [ ] Complexity measured: `lizard src/`
- [ ] All functions ≤ 10 CCN: PASS (max 7 CCN)
- [ ] Module complexity acceptable: 35 CCN total (PASS)
- [ ] Complexity report archived: `docs/verification/complexity-gate4.txt`

### 7. Traceability Completeness

- [ ] All requirements traced forward (req → code): 50/50 (100%)
- [ ] All code traced backward (code → req): 100% functions
- [ ] RTM complete: All entries verified
- [ ] Traceability validation: `workspace.py trace validate-ci --baseline gate4-implementation`
  - Output: ✅ PASS

### 8. Safety Requirements Verification (SIL 3-4)

For each safety requirement:
- [ ] Safety requirement implemented
- [ ] Safety requirement tested
- [ ] Hazard mitigation effective (FMEA/FTA updated)

- [ ] REQ-10: Defensive programming (verified in code review)
- [ ] REQ-42: Timeout detection (tested, PASS)
- [ ] ... (all 5 safety requirements)

**Hazard Log Review**:
- [ ] All hazards addressed: 5/5
- [ ] All mitigations implemented: 5/5
- [ ] Residual risk acceptable: PASS

### 9. Documentation Completeness

- [ ] SRS complete: 50 requirements, all unambiguous
- [ ] SAS complete: Architecture documented
- [ ] SDS complete: Detailed design documented
- [ ] RTM complete: 100% traceability
- [ ] Verification reports complete: Unit test, integration test, static analysis, code review

### 10. Approval Verification

- [ ] QUA approval: Alice Johnson (2024-03-10)
- [ ] VER approval: Bob Smith (2024-03-12)
- [ ] COD gate approval: PASS (2024-03-15)
- [ ] PCA passed: Bob Smith (VER, 2024-03-20)

## FCA Result

- **Status**: [PASS / FAIL / CONDITIONAL PASS]
- **Requirements Met**: [Count / Total]
- **Tests Passed**: [Count / Total]
- **Coverage**: [Statement%, Branch%, Condition%]
- **Issues Found**: [Count]

## Issues Log

| ID | Severity | Description | Resolution |
|----|----------|-------------|------------|
| (None) | - | - | - |

## Conclusion

[PASS / FAIL summary]

---

**Auditor**: Carol White (VMGR)  
**Signature**: _________________  
**Date**: 2024-03-22
```

**Step 3: Execute FCA**

Auditor performs checks:

```bash
# 1. Verify all requirements implemented
workspace.py trace validate-all-req --baseline gate4-implementation

# Output:
# Validating all requirements for baseline gate4-implementation...
# ✓ REQ-01: Implemented, traced, tested, PASS
# ✓ REQ-02: Implemented, traced, tested, PASS
# ...
# ✓ REQ-50: Implemented, traced, tested, PASS
# 
# Result: 50/50 requirements met (100%)

# 2. Verify all tests passed
make test
# Output: 26/26 tests PASS

make integration-test
# Output: 3/3 tests PASS

# 3. Verify coverage
make coverage
lcov --summary coverage.info
# Output: Statement: 100%, Branch: 100%, Condition: 100%

# 4. Verify static analysis
cppcheck --enable=all src/
# Output: 0 errors

scan-build make
# Output: scan-build: 0 bugs found

python3 tools/check_misra.py src/
# Output: 0 mandatory violations

# 5. Verify complexity
lizard src/
# Output: All functions ≤10 CCN, max 7 CCN

# 6. Verify traceability
workspace.py trace validate-ci --baseline gate4-implementation
# Output: ✅ Traceability: PASS (100% forward, 100% backward)
```

**Step 4: Document FCA Results**

```markdown
# Functional Configuration Audit Report: gate4-implementation

**Baseline**: baseline/gate4-implementation  
**Auditor**: Carol White (VMGR, independent)  
**Date**: 2024-03-22  
**Result**: **PASS**  

## Summary

Functional Configuration Audit completed for baseline gate4-implementation.
All requirements verified as implemented and tested.

- **Total Requirements**: 50 (35 functional, 10 non-functional, 5 safety)
- **Requirements Met**: 50/50 (100%)
- **Tests Executed**: 29 (26 unit, 3 integration)
- **Tests Passed**: 29/29 (100%)
- **Coverage**: Statement 100%, Branch 100%, Condition 100%
- **Issues Found**: 0

## Requirements Verification

### Functional Requirements (35)
- ✓ All 35 functional requirements implemented
- ✓ All 35 traced to code (RTM complete)
- ✓ All 35 tested (tests passed)

### Non-Functional Requirements (10)
- ✓ All 10 non-functional requirements implemented
- ✓ Performance requirements met (timing tests passed)
- ✓ Reliability requirements met (fault injection tests passed)

### Safety Requirements (5)
- ✓ All 5 safety requirements implemented
- ✓ REQ-10: Defensive programming verified (code review)
- ✓ REQ-42: Timeout detection verified (unit tests, integration tests)
- ✓ Hazard mitigations effective (FMEA/FTA updated)

## Test Results

### Unit Tests
- **Executed**: 26
- **Passed**: 26 (100%)
- **Failed**: 0
- **Skipped**: 0

### Integration Tests
- **Executed**: 3
- **Passed**: 3 (100%)
- **Failed**: 0
- **Skipped**: 0

### Test Coverage (SIL 3 requirement: 100%)
- **Statement Coverage**: 100% ✓
- **Branch Coverage**: 100% ✓
- **Condition Coverage**: 100% ✓ (SIL 3-4)

## Static Analysis

### Cppcheck
- **Issues Found**: 0
- **Critical Issues**: 0
- **Status**: PASS

### Clang Static Analyzer
- **Bugs Found**: 0
- **Status**: PASS

### MISRA C:2012 Compliance (SIL 3-4)
- **Mandatory Violations**: 0 ✓
- **Required Violations**: 2 (justified in deviation report)
- **Advisory Violations**: 10 (acceptable)
- **Status**: PASS

## Code Review

- **Code Review Completed**: Yes (QUA, VER)
- **Issues Raised**: 8 (all resolved)
- **Major Issues**: 0
- **Minor Issues**: 8 (resolved before baseline)
- **Status**: PASS

## Complexity Analysis (SIL 3-4 requirement: ≤10 CCN)

- **Max Function Complexity**: 7 CCN (timeout_check)
- **Average Function Complexity**: 4 CCN
- **Module Complexity**: 35 CCN total
- **Status**: PASS (all functions ≤10 CCN)

## Traceability

- **Forward Traceability** (req → code): 50/50 (100%)
- **Backward Traceability** (code → req): 100% functions
- **RTM Complete**: Yes
- **Traceability Validation**: PASS

## Safety Verification (SIL 3)

### Hazard Analysis
- **Total Hazards**: 5
- **Hazards Mitigated**: 5 (100%)
- **Residual Risk**: ACCEPTABLE

### FMEA
- **Failure Modes Analyzed**: 10
- **RPN Reduced**: All to acceptable levels
- **Status**: PASS

### Safety Requirements
- **Safety Requirements**: 5
- **Safety Requirements Met**: 5 (100%)
- **Safety Tests Passed**: 100%

## Documentation

- ✓ SRS complete and approved
- ✓ SAS complete and approved
- ✓ SDS complete and approved
- ✓ RTM complete and verified
- ✓ Verification reports complete
- ✓ PCA passed (2024-03-20)

## Approvals

- ✓ QUA: Alice Johnson (2024-03-10)
- ✓ VER: Bob Smith (2024-03-12)
- ✓ COD: Gate 4 PASS (2024-03-15)
- ✓ PCA: Bob Smith (VER, 2024-03-20)

## Issues

**Major Issues**: 0  
**Minor Issues**: 0  

## Conclusion

Functional Configuration Audit **PASSED** for baseline gate4-implementation.

- All requirements implemented and tested
- All tests passed (100%)
- Coverage meets SIL 3 requirements (100%)
- Static analysis clean
- Complexity within limits
- Traceability complete
- Safety requirements verified
- Documentation complete

Baseline gate4-implementation is functionally correct and meets all specified requirements.

**Recommendation**: Baseline gate4-implementation approved for progression to Gate 5 (Integration).

---

**Auditor**: Carol White (VMGR)  
**Signature**: [GPG signature]  
**Date**: 2024-03-22  

**Approved for Release**: Yes  
**Next Phase**: Gate 5 (Integration)
```

**Step 5: Archive FCA Report**

```bash
# Store FCA report
git add docs/audits/FCA-gate4-implementation-2024-03-22.md
git commit -m "docs(audit): FCA report for gate4-implementation

Functional Configuration Audit completed for baseline gate4-implementation.

Result: PASS
Auditor: Carol White (VMGR)
Date: 2024-03-22

All requirements met (50/50), all tests passed (29/29), coverage 100%.

[FCA-Gate4] Functional Configuration Audit report
" --signoff

git push origin develop
```

### 7.3 FCA Failure Handling

**If FCA fails** (requirements not met):

**Example issues**:
- Requirement not implemented (no code)
- Requirement not tested (no test)
- Test failed
- Coverage insufficient
- Traceability incomplete

**Resolution**:

1. **Document issue** in FCA report (FAIL or CONDITIONAL PASS)
2. **Create CRs** for each issue
3. **Implement fixes** (follow Change Control Workflow)
4. **Re-verify** after fixes
5. **Re-run FCA** to verify resolution
6. **Update FCA report** with final status

**Example**:

```markdown
## Issues

### Issue FCA-001: Requirement Not Tested

- **Severity**: MAJOR
- **Requirement**: REQ-48 (Watchdog timeout < 500ms)
- **Description**: No test exists to verify watchdog timeout performance
- **Impact**: Cannot verify requirement met
- **Corrective Action**: 
  - CR-130: Add watchdog timeout performance test
  - Implement test
  - Execute test, verify PASS
- **Target Resolution**: 2024-03-25
- **Status**: IN PROGRESS

## FCA Result

**Status**: **CONDITIONAL PASS**

Baseline gate4-implementation is functionally correct EXCEPT for issue FCA-001.

**Conditions for final PASS**:
- CR-130 must be completed (watchdog timeout test added)
- Test must pass
- FCA re-run required

**Re-run Date**: 2024-03-26 (after CR-130 completion)
```

---

## 8. Baseline Release Process

### 8.1 Release Baseline (Gate 7)

**Release baseline** is the final, deployment-ready baseline:

**Prerequisites**:
- All development phases complete (Gates 1-6)
- All verification complete (VER approval)
- All validation complete (VAL approval, VMGR approval)
- Assessment complete (ISA approval, SIL 3-4 only)
- PCA and FCA passed for all prior baselines

**Release Baseline Contents**:
- Complete source code (all modules)
- Complete test suite (unit, integration, system)
- Complete documentation (SRS, SAS, SDS, RTM, all reports)
- Release notes (changes, known issues, limitations)
- Deployment package (binary, configuration, scripts)
- User documentation (if applicable)
- Tool qualification data (EN 50128 Section 6.7)

**Release Process**:

```bash
# Step 1: Verify all gates passed
workspace.py wf status
# Output: All gates (1-7) PASS

# Step 2: Create release tag (semantic version)
git tag -s v1.0.0 -m "Release v1.0.0 - First Production Release

EN 50128 SIL 3 Railway Safety Software
Release Date: 2024-06-15

Features:
- Sensor timeout detection (REQ-42)
- Watchdog monitoring (REQ-50)
- UART diagnostics (REQ-55)
- Emergency stop handling (REQ-10)

Verification:
- 100 unit tests, 100% PASS
- 20 integration tests, 100% PASS
- 50 system tests, 100% PASS
- Coverage: 100% statement, branch, condition
- Static analysis: Clean (Cppcheck, Clang, PC-lint)
- MISRA C:2012: 0 mandatory violations
- Complexity: All functions ≤10 CCN

Validation:
- 10 operational scenarios, 100% PASS
- Target hardware: Verified
- Customer acceptance: APPROVED

Assessment (SIL 3):
- Independent Safety Assessor: APPROVED
- Assessment Report: AR-v1.0-2024-06-10.pdf

Approvals:
- VER: Bob Smith (2024-06-01)
- VAL: Carol White (VMGR, 2024-06-05)
- ISA: David Brown (2024-06-10)
- Customer: Jane Doe (2024-06-12)

Baselines:
- baseline/gate1-planning
- baseline/gate2-requirements
- baseline/gate3-design
- baseline/gate4-implementation
- baseline/gate5-integration
- baseline/gate6-validation

Quality Metrics:
- Total CRs: 50 (all closed)
- Defect density: 0.5 defects/KLOC
- Test pass rate: 100%
- Customer satisfaction: 9/10

Signed-off-by: John Doe (CM) <john.doe@company.com>
GPG Key: 0x12345678ABCDEF
"

git push origin v1.0.0

# Step 3: Create release package
python3 tools/baseline_manager.py --create-release v1.0.0

# Output:
# Creating release package for v1.0.0...
# ✓ Source code archived: releases/v1.0.0/source.tar.gz
# ✓ Binary built: releases/v1.0.0/firmware.bin
# ✓ Documentation packaged: releases/v1.0.0/docs.zip
# ✓ Test results archived: releases/v1.0.0/test-results.zip
# ✓ Release notes generated: releases/v1.0.0/RELEASE_NOTES.md
# ✓ Checksums generated: releases/v1.0.0/checksums.sha256
# 
# Release package created: releases/v1.0.0/

# Step 4: Sign release package
gpg --armor --detach-sign releases/v1.0.0/firmware.bin
# Output: releases/v1.0.0/firmware.bin.asc

# Step 5: Archive release (long-term storage)
workspace.py wf archive-release v1.0.0 --storage /archive/releases/

# Output: ✅ Release v1.0.0 archived to /archive/releases/v1.0.0/

# Step 6: Update CHANGELOG
cat >> CHANGELOG.md << EOF

## [1.0.0] - 2024-06-15

First production release. EN 50128 SIL 3 compliant.

### Added
- Sensor timeout detection (REQ-42)
- Watchdog monitoring (REQ-50)
- UART diagnostics (REQ-55)
- Emergency stop handling (REQ-10)

### Verified
- 100% test coverage
- MISRA C:2012 compliant
- Independent assessment APPROVED

### Validated
- Customer acceptance APPROVED
- 10 operational scenarios PASS

EOF

git add CHANGELOG.md
git commit -m "docs: Update CHANGELOG for v1.0.0 release" --signoff
git push origin main
```

### 8.2 Release Notes Template

**`releases/v1.0.0/RELEASE_NOTES.md`**:

```markdown
# Release Notes: v1.0.0

**Release Date**: 2024-06-15  
**Product**: Railway Safety Software  
**SIL Level**: SIL 3  
**EN 50128**: 2011  

## Overview

First production release of EN 50128 SIL 3 compliant railway safety software.

## Features

### New Features

- **Sensor Timeout Detection** (REQ-42)
  - Detects sensor communication timeout within 100ms
  - Configurable timeout threshold (50-5000ms)
  - Callback notification on timeout event

- **Watchdog Monitoring** (REQ-50)
  - Hardware watchdog timer integration
  - 500ms timeout
  - Automatic reset on timeout

- **UART Diagnostics** (REQ-55)
  - Diagnostic output via UART
  - 115200 baud, 8N1
  - Status messages, error logs

- **Emergency Stop** (REQ-10)
  - Immediate stop on emergency button press
  - < 50ms response time
  - Safe state entered

## System Requirements

- **Target Platform**: ARM Cortex-M4, 168 MHz
- **Memory**: 128 KB Flash, 32 KB RAM
- **Peripherals**: UART, GPIO, Timer, Watchdog

## Installation

1. Flash firmware.bin to target: `flash-tool --write firmware.bin`
2. Verify checksum: `sha256sum firmware.bin` == checksums.sha256
3. Reset target
4. Verify boot: Check UART output for "System Ready"

## Known Issues

**None** - All known issues resolved before release.

## Limitations

- Maximum 4 sensors supported
- UART diagnostics SIL 0 (not safety-critical)

## Testing

- **Unit Tests**: 100/100 PASS (100%)
- **Integration Tests**: 20/20 PASS (100%)
- **System Tests**: 50/50 PASS (100%)
- **Coverage**: 100% statement, branch, condition
- **Static Analysis**: 0 critical issues
- **MISRA C**: 0 mandatory violations

## Verification

- **Verifier**: Bob Smith (VER, independent)
- **Verification Report**: VR-v1.0-2024-06-01.md
- **Result**: APPROVED

## Validation

- **Validator**: Carol White (VMGR, independent)
- **Validation Report**: VaR-v1.0-2024-06-05.md
- **Result**: APPROVED

## Assessment (SIL 3)

- **Assessor**: David Brown (ISA, independent)
- **Assessment Report**: AR-v1.0-2024-06-10.pdf
- **Result**: APPROVED

## Customer Acceptance

- **Customer**: Jane Doe (Railway Company)
- **Acceptance Date**: 2024-06-12
- **Result**: APPROVED

## Documentation

- Software Requirements Specification (SRS-v1.0.md)
- Software Architecture Specification (SAS-v1.0.md)
- Software Design Specification (SDS-v1.0.md)
- Requirements Traceability Matrix (RTM-v1.0.md)
- Hazard Log (Hazard-Log-v1.0.md)
- Software Quality Assurance Plan (SQAP-v1.0.md)
- Software Configuration Management Plan (SCMP-v1.0.md)
- Software Verification Plan (SVP-v1.0.md)
- Software Validation Plan (SVaP-v1.0.md)
- Verification Report (VR-v1.0-2024-06-01.md)
- Validation Report (VaR-v1.0-2024-06-05.md)
- Assessment Report (AR-v1.0-2024-06-10.pdf)

## Support

- **Email**: support@company.com
- **Issue Tracker**: https://github.com/company/project/issues

---

**Release Manager**: John Doe (CM)  
**Signature**: [GPG signature]  
**Date**: 2024-06-15
```

---

## 9. Tool Integration

### 9.1 Workspace CLI Integration

**`workspace.py wf` commands** for baseline management:

```bash
# Baseline Creation
workspace.py wf create-baseline gate4-implementation
# Output: ✅ Baseline gate4-implementation created

# Baseline Documentation
workspace.py wf show-baseline gate4-implementation
# Output: (displays baseline details, CIs, approvals)

# Baseline Listing
workspace.py wf list-baselines
# Output: List of all baselines

# Baseline Comparison
workspace.py wf diff-baseline gate3-design gate4-implementation
# Output: Differences between baselines

# Baseline Update
workspace.py wf update-baseline gate4-implementation-v1.1 --previous gate4-implementation --cr CR-123
# Output: ✅ Baseline gate4-implementation-v1.1 created

# PCA Scheduling
workspace.py wf schedule-pca gate4-implementation --auditor "Bob Smith (VER)" --date "2024-03-20"
# Output: ✅ PCA scheduled

# FCA Scheduling
workspace.py wf schedule-fca gate4-implementation --auditor "Carol White (VMGR)" --date "2024-03-22"
# Output: ✅ FCA scheduled

# Release Creation
workspace.py wf create-release v1.0.0
# Output: ✅ Release package created: releases/v1.0.0/

# Release Archival
workspace.py wf archive-release v1.0.0 --storage /archive/releases/
# Output: ✅ Release v1.0.0 archived
```

### 9.2 Git Integration

**Git commands** for baseline management:

```bash
# Create baseline tag
git tag -s baseline/gate4-implementation -m "Implementation Baseline"

# List baseline tags
git tag -l "baseline/*"

# Show baseline details
git show baseline/gate4-implementation

# Verify baseline signature
git tag -v baseline/gate4-implementation

# Checkout baseline
git checkout baseline/gate4-implementation

# Compare baselines
git diff baseline/gate3-design baseline/gate4-implementation

# Archive baseline
git archive --format=tar.gz --prefix=gate4-implementation/ baseline/gate4-implementation > gate4-implementation.tar.gz
```

---

## 10. Automation Scripts

### 10.1 Baseline Manager Script

**`tools/baseline_manager.py`** (200 lines) - comprehensive baseline management:

```python
#!/usr/bin/env python3
"""
Baseline Manager for EN 50128 Configuration Management.

Manages baseline creation, documentation, verification, and archival.

Usage:
    python3 baseline_manager.py --baseline gate4-implementation --generate-manifest
    python3 baseline_manager.py --baseline gate4-implementation --verify-checksums
    python3 baseline_manager.py --create-release v1.0.0
"""

import argparse
import yaml
import subprocess
import os
import hashlib
from typing import List, Dict

class BaselineManager:
    def __init__(self, baseline_id: str):
        self.baseline_id = baseline_id
        self.git_tag = f"baseline/{baseline_id}"
        self.manifest = {}
    
    def generate_manifest(self):
        """Generate baseline manifest with checksums."""
        print(f"Generating manifest for baseline {self.baseline_id}...")
        
        # Checkout baseline
        subprocess.run(f"git checkout {self.git_tag}", shell=True, check=True)
        
        # Get baseline commit
        git_commit = subprocess.check_output(f"git rev-parse {self.git_tag}", shell=True).decode().strip()
        
        # Initialize manifest
        self.manifest = {
            'baseline_id': self.baseline_id,
            'git_tag': self.git_tag,
            'git_commit': git_commit,
            'date': subprocess.check_output(['date', '+%Y-%m-%d']).decode().strip(),
            'configuration_items': {
                'source_code': [],
                'tests': [],
                'documentation': [],
                'build_scripts': []
            }
        }
        
        # Source code
        for root, dirs, files in os.walk('src'):
            for file in files:
                if file.endswith(('.c', '.h')):
                    path = os.path.join(root, file)
                    self.manifest['configuration_items']['source_code'].append({
                        'path': path,
                        'checksum': self._calculate_checksum(path),
                        'lines': self._count_lines(path),
                        'complexity': self._calculate_complexity(path)
                    })
        
        # Tests
        for root, dirs, files in os.walk('tests'):
            for file in files:
                if file.endswith('.c'):
                    path = os.path.join(root, file)
                    self.manifest['configuration_items']['tests'].append({
                        'path': path,
                        'checksum': self._calculate_checksum(path),
                        'test_count': self._count_tests(path)
                    })
        
        # Documentation
        for root, dirs, files in os.walk('docs'):
            for file in files:
                if file.endswith('.md'):
                    path = os.path.join(root, file)
                    self.manifest['configuration_items']['documentation'].append({
                        'path': path,
                        'checksum': self._calculate_checksum(path),
                        'word_count': self._count_words(path)
                    })
        
        # Build scripts
        if os.path.exists('Makefile'):
            self.manifest['configuration_items']['build_scripts'].append({
                'path': 'Makefile',
                'checksum': self._calculate_checksum('Makefile'),
                'lines': self._count_lines('Makefile')
            })
        
        # Write manifest
        manifest_file = f"docs/baselines/manifests/{self.baseline_id}.yaml"
        os.makedirs(os.path.dirname(manifest_file), exist_ok=True)
        with open(manifest_file, 'w') as f:
            yaml.dump(self.manifest, f, default_flow_style=False)
        
        print(f"✅ Manifest generated: {manifest_file}")
    
    def verify_checksums(self):
        """Verify checksums against manifest."""
        print(f"Verifying checksums for baseline {self.baseline_id}...")
        
        # Load manifest
        manifest_file = f"docs/baselines/manifests/{self.baseline_id}.yaml"
        with open(manifest_file, 'r') as f:
            self.manifest = yaml.safe_load(f)
        
        # Checkout baseline
        subprocess.run(f"git checkout {self.git_tag}", shell=True, check=True)
        
        # Verify all CIs
        errors = 0
        total = 0
        
        for ci_type, cis in self.manifest['configuration_items'].items():
            for ci in cis:
                path = ci['path']
                expected_checksum = ci['checksum']
                actual_checksum = self._calculate_checksum(path)
                
                total += 1
                
                if expected_checksum == actual_checksum:
                    print(f"✓ {path}: Checksum matches")
                else:
                    print(f"✗ {path}: Checksum MISMATCH")
                    print(f"  Expected: {expected_checksum}")
                    print(f"  Actual: {actual_checksum}")
                    errors += 1
        
        print(f"\nResult: {total - errors}/{total} checksums verified")
        
        if errors > 0:
            print(f"❌ {errors} checksum mismatches found")
            return False
        else:
            print("✅ All checksums verified")
            return True
    
    def create_release(self, version: str):
        """Create release package."""
        print(f"Creating release package for {version}...")
        
        release_dir = f"releases/{version}"
        os.makedirs(release_dir, exist_ok=True)
        
        # Checkout release tag
        subprocess.run(f"git checkout {version}", shell=True, check=True)
        
        # Archive source code
        subprocess.run(f"git archive --format=tar.gz --prefix={version}/ {version} > {release_dir}/source.tar.gz", shell=True, check=True)
        print(f"✓ Source code archived: {release_dir}/source.tar.gz")
        
        # Build binary (if applicable)
        if os.path.exists('Makefile'):
            subprocess.run("make clean all", shell=True, check=True)
            if os.path.exists('build/firmware.bin'):
                subprocess.run(f"cp build/firmware.bin {release_dir}/firmware.bin", shell=True, check=True)
                print(f"✓ Binary built: {release_dir}/firmware.bin")
        
        # Package documentation
        subprocess.run(f"tar -czf {release_dir}/docs.tar.gz docs/", shell=True, check=True)
        print(f"✓ Documentation packaged: {release_dir}/docs.tar.gz")
        
        # Archive test results
        if os.path.exists('test-results/'):
            subprocess.run(f"tar -czf {release_dir}/test-results.tar.gz test-results/", shell=True, check=True)
            print(f"✓ Test results archived: {release_dir}/test-results.tar.gz")
        
        # Generate checksums
        checksums_file = f"{release_dir}/checksums.sha256"
        subprocess.run(f"cd {release_dir} && sha256sum * > checksums.sha256", shell=True, check=True)
        print(f"✓ Checksums generated: {checksums_file}")
        
        print(f"\n✅ Release package created: {release_dir}/")
    
    def _calculate_checksum(self, file_path: str) -> str:
        """Calculate SHA-256 checksum of file."""
        sha256 = hashlib.sha256()
        with open(file_path, 'rb') as f:
            for chunk in iter(lambda: f.read(4096), b""):
                sha256.update(chunk)
        return f"sha256:{sha256.hexdigest()}"
    
    def _count_lines(self, file_path: str) -> int:
        """Count lines in file."""
        with open(file_path, 'r') as f:
            return len(f.readlines())
    
    def _count_words(self, file_path: str) -> int:
        """Count words in file."""
        with open(file_path, 'r') as f:
            return len(f.read().split())
    
    def _count_tests(self, file_path: str) -> int:
        """Count test functions in file."""
        with open(file_path, 'r') as f:
            content = f.read()
            return content.count('void test_')
    
    def _calculate_complexity(self, file_path: str) -> int:
        """Calculate cyclomatic complexity using lizard."""
        try:
            output = subprocess.check_output(f"lizard {file_path} -l c", shell=True).decode()
            # Parse total complexity (simplified)
            for line in output.split('\n'):
                if file_path in line:
                    parts = line.split()
                    if len(parts) >= 3:
                        return int(parts[1])  # Complexity column
            return 0
        except:
            return 0


def main():
    parser = argparse.ArgumentParser(description='Baseline Manager')
    parser.add_argument('--baseline', help='Baseline ID (e.g., gate4-implementation)')
    parser.add_argument('--generate-manifest', action='store_true', help='Generate baseline manifest')
    parser.add_argument('--verify-checksums', action='store_true', help='Verify checksums against manifest')
    parser.add_argument('--create-release', help='Create release package (version tag, e.g., v1.0.0)')
    
    args = parser.parse_args()
    
    if args.create_release:
        manager = BaselineManager('')
        manager.create_release(args.create_release)
    elif args.baseline:
        manager = BaselineManager(args.baseline)
        
        if args.generate_manifest:
            manager.generate_manifest()
        elif args.verify_checksums:
            success = manager.verify_checksums()
            if not success:
                return 1
    else:
        print("ERROR: Specify --baseline or --create-release")
        return 1
    
    return 0


if __name__ == '__main__':
    exit(main())
```

### 10.2 PCA/FCA Checklist Generator

**`tools/audit_checklist_generator.py`** (150 lines) - generates PCA/FCA checklists:

```python
#!/usr/bin/env python3
"""
PCA/FCA Checklist Generator for EN 50128.

Generates Physical Configuration Audit (PCA) and Functional Configuration
Audit (FCA) checklists from baseline manifest.

Usage:
    python3 audit_checklist_generator.py --baseline gate4-implementation --audit PCA
    python3 audit_checklist_generator.py --baseline gate4-implementation --audit FCA
"""

import argparse
import yaml
import os

class AuditChecklistGenerator:
    def __init__(self, baseline_id: str, audit_type: str):
        self.baseline_id = baseline_id
        self.audit_type = audit_type
        self.manifest = None
    
    def load_manifest(self):
        """Load baseline manifest."""
        manifest_file = f"docs/baselines/manifests/{self.baseline_id}.yaml"
        with open(manifest_file, 'r') as f:
            self.manifest = yaml.safe_load(f)
    
    def generate_pca_checklist(self) -> str:
        """Generate PCA checklist."""
        checklist = f"""# Physical Configuration Audit Checklist: {self.baseline_id}

**Baseline**: baseline/{self.baseline_id}  
**Auditor**: _______________  
**Date**: _______________  

## Checklist Items

### 1. Baseline Tag Verification

- [ ] Git tag exists: `git tag -l baseline/{self.baseline_id}`
- [ ] Tag is annotated: `git show baseline/{self.baseline_id}`
- [ ] Tag is signed (SIL 3-4): `git tag -v baseline/{self.baseline_id}`
- [ ] Tag message complete

### 2. Baseline Documentation Verification

- [ ] Baseline composition document exists
- [ ] Baseline manifest exists
- [ ] Baseline registry updated
- [ ] Dependencies documented

### 3. Source Code Verification

"""
        for ci in self.manifest['configuration_items']['source_code']:
            checklist += f"- [ ] {ci['path']}: Exists, checksum matches\n"
        
        checklist += "\n### 4. Test Verification\n\n"
        for ci in self.manifest['configuration_items']['tests']:
            checklist += f"- [ ] {ci['path']}: Exists, checksum matches\n"
        
        checklist += "\n### 5. Documentation Verification\n\n"
        for ci in self.manifest['configuration_items']['documentation']:
            checklist += f"- [ ] {ci['path']}: Exists, checksum matches\n"
        
        checklist += """
### 6. Completeness Check

- [ ] All CIs in manifest accounted for
- [ ] No extra CIs not in manifest

### 7. Traceability Verification

- [ ] RTM references correct baseline
- [ ] All requirements traced

## PCA Result

- **Status**: [PASS / FAIL]
- **Issues Found**: ___

---

**Auditor**: _______________  
**Date**: _______________
"""
        return checklist
    
    def generate_fca_checklist(self) -> str:
        """Generate FCA checklist."""
        checklist = f"""# Functional Configuration Audit Checklist: {self.baseline_id}

**Baseline**: baseline/{self.baseline_id}  
**Auditor**: _______________  
**Date**: _______________  

## Checklist Items

### 1. Requirements Implementation

- [ ] All requirements implemented
- [ ] All requirements tested
- [ ] All tests passed

### 2. Test Results Verification

- [ ] Unit tests executed
- [ ] Unit tests passed: ___/___ (100%)
- [ ] Integration tests passed: ___/___ (100%)

### 3. Coverage Verification (SIL 3-4)

- [ ] Statement coverage ≥ 100%
- [ ] Branch coverage ≥ 100%
- [ ] Condition coverage ≥ 100%

### 4. Static Analysis Verification

- [ ] Cppcheck clean
- [ ] Clang clean
- [ ] MISRA C: 0 mandatory violations

### 5. Complexity Verification (SIL 3-4)

- [ ] All functions ≤ 10 CCN

### 6. Traceability Completeness

- [ ] Forward traceability: 100%
- [ ] Backward traceability: 100%

### 7. Safety Requirements (SIL 3-4)

- [ ] All safety requirements met
- [ ] All hazards mitigated

## FCA Result

- **Status**: [PASS / FAIL]
- **Requirements Met**: ___/___
- **Tests Passed**: ___/___

---

**Auditor**: _______________  
**Date**: _______________
"""
        return checklist
    
    def generate(self):
        """Generate checklist."""
        self.load_manifest()
        
        if self.audit_type == 'PCA':
            checklist = self.generate_pca_checklist()
        elif self.audit_type == 'FCA':
            checklist = self.generate_fca_checklist()
        else:
            raise ValueError(f"Unknown audit type: {self.audit_type}")
        
        # Write checklist
        output_file = f"docs/audits/{self.audit_type}-checklist-{self.baseline_id}.md"
        os.makedirs(os.path.dirname(output_file), exist_ok=True)
        with open(output_file, 'w') as f:
            f.write(checklist)
        
        print(f"✅ {self.audit_type} checklist generated: {output_file}")


def main():
    parser = argparse.ArgumentParser(description='Audit Checklist Generator')
    parser.add_argument('--baseline', required=True, help='Baseline ID')
    parser.add_argument('--audit', required=True, choices=['PCA', 'FCA'], help='Audit type')
    
    args = parser.parse_args()
    
    generator = AuditChecklistGenerator(args.baseline, args.audit)
    generator.generate()
    
    return 0


if __name__ == '__main__':
    exit(main())
```

---

## 11. Example Scenarios

### 11.1 Scenario 1: Complete Baseline Lifecycle (SIL 3)

**Context**: Complete baseline management from establishment through PCA/FCA to next phase.

**Timeline**: Gate 4 (Implementation) baseline

```bash
# Day 1: Baseline Establishment (after Gate 4 approval)

# Step 1: Verify gate approval
cat LIFECYCLE_STATE.md | grep gate4
# Output: gate4-implementation: APPROVED (2024-03-15 by COD)

# Step 2: Create baseline tag
git tag -s baseline/gate4-implementation -m "Implementation Baseline (Gate 4)
[... complete tag message ...]
"
git push origin baseline/gate4-implementation

# Step 3: Generate manifest
python3 tools/baseline_manager.py --baseline gate4-implementation --generate-manifest
# Output: ✅ Manifest generated: docs/baselines/manifests/gate4-implementation.yaml

# Step 4: Create baseline documentation
workspace.py wf create-baseline gate4-implementation
# Output: ✅ Baseline documentation: docs/baselines/gate4-implementation.md

# Step 5: Update registry
# (Automated by workspace.py)

# Step 6: Commit baseline docs
git add docs/baselines/
git commit -m "chore(cm): Establish baseline gate4-implementation" --signoff
git push origin develop

# Step 7: Schedule audits
workspace.py wf schedule-pca gate4-implementation --auditor "Bob Smith (VER)" --date "2024-03-20"
workspace.py wf schedule-fca gate4-implementation --auditor "Carol White (VMGR)" --date "2024-03-22"

# Day 2-5: PCA Preparation

# Generate PCA checklist
python3 tools/audit_checklist_generator.py --baseline gate4-implementation --audit PCA
# Output: ✅ PCA checklist: docs/audits/PCA-checklist-gate4-implementation.md

# Day 6: PCA Execution (2024-03-20)

# Auditor (Bob Smith, VER) executes PCA
python3 tools/baseline_manager.py --baseline gate4-implementation --verify-checksums
# Output: ✅ All checksums verified (9/9)

# Complete PCA checklist
# [Manual: Review each item, check boxes]

# Create PCA report
# [Manual: Write PCA report, see Section 6.2]

# Archive PCA report
git add docs/audits/PCA-gate4-implementation-2024-03-20.md
git commit -m "docs(audit): PCA report for gate4-implementation (PASS)" --signoff
git push origin develop

# Day 7-8: FCA Preparation

# Generate FCA checklist
python3 tools/audit_checklist_generator.py --baseline gate4-implementation --audit FCA
# Output: ✅ FCA checklist: docs/audits/FCA-checklist-gate4-implementation.md

# Day 9: FCA Execution (2024-03-22)

# Auditor (Carol White, VMGR) executes FCA
workspace.py trace validate-all-req --baseline gate4-implementation
# Output: ✅ 50/50 requirements met (100%)

make test
# Output: 26/26 tests PASS

make coverage
# Output: Statement 100%, Branch 100%, Condition 100%

cppcheck --enable=all src/
# Output: 0 issues

# Complete FCA checklist
# [Manual: Review each item, check boxes]

# Create FCA report
# [Manual: Write FCA report, see Section 7.2]

# Archive FCA report
git add docs/audits/FCA-gate4-implementation-2024-03-22.md
git commit -m "docs(audit): FCA report for gate4-implementation (PASS)" --signoff
git push origin develop

# Day 10: Baseline Approved, Proceed to Gate 5

# Update LIFECYCLE_STATE.md
# (Automated by COD after PCA/FCA approval)

# Notify team: Gate 5 (Integration) ready to begin
echo "Baseline gate4-implementation approved (PCA PASS, FCA PASS). Proceeding to Gate 5."
```

---

## Summary

This **Baseline Management Workflow** provides comprehensive guidance for establishing, controlling, and auditing baselines in EN 50128-compliant railway software development.

**Key Takeaways**:
1. **Baselines MANDATORY at all phase gates** (Gate 1-7) for all SIL levels
2. **Baseline immutability**: Once established, baselines are frozen (changes via CR only)
3. **Physical Configuration Audit (PCA)** verifies baseline completeness (MANDATORY SIL 3-4)
4. **Functional Configuration Audit (FCA)** verifies requirements met (MANDATORY SIL 3-4)
5. **Independent auditors** required for PCA/FCA (SIL 3-4)
6. **Git tags** enforce baseline immutability (annotated, signed for SIL 3-4)
7. **Baseline manifest** documents complete CI inventory with checksums
8. **Release baseline** (Gate 7) is deployment-ready package
9. **Traceability** verified in PCA/FCA (100% required for SIL 3-4)
10. **Tool integration** (`workspace.py wf`, Git) automates baseline management

**Related Workflows**:
- **WF-CM-001**: Version Control Workflow (Git tags, branching)
- **WF-CM-002**: Change Control Workflow (CR process for baseline changes)
- **WF-CM-004**: Configuration Status Accounting (baseline metrics, tracking)

**EN 50128 Compliance**:
- ✅ Section 6.6: Software Configuration Management (baseline control)
- ✅ Section 6.6.4.1(f): Baseline update after change
- ✅ Section 6.6.6: Configuration Audits (PCA, FCA)
- ✅ Annex C Table C.1: Document control (baseline triggers)
- ✅ Table A.9 #5: Software Configuration Management (MANDATORY ALL SIL)

---

**Document Control**

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2024-03-15 | Configuration Team | Initial version |

**Approvals**

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Configuration Manager | | | |
| Quality Assurance | | | |
| VMGR (SIL 3-4) | | | |

---

*End of Baseline Management Workflow (WF-CM-003)*
