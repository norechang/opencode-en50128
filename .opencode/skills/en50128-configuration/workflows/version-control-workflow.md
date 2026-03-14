# Version Control Workflow for EN 50128 Configuration Management

**Document ID**: WF-CM-001  
**Version**: 1.0  
**Status**: Active  
**Skill**: en50128-configuration  
**Related Standard**: EN 50128:2011 Section 6.6, Table A.9 #5

---

## Table of Contents

1. [Overview](#1-overview)
2. [EN 50128 Version Control Requirements](#2-en-50128-version-control-requirements)
3. [Git Repository Setup](#3-git-repository-setup)
4. [Branching Strategies](#4-branching-strategies)
5. [Commit Conventions](#5-commit-conventions)
6. [Merge Policies](#6-merge-policies)
7. [Tag Management](#7-tag-management)
8. [CI Integration](#8-ci-integration)
9. [Tool Integration](#9-tool-integration)
10. [Automation Scripts](#10-automation-scripts)
11. [Example Scenarios](#11-example-scenarios)

---

## 1. Overview

### 1.1 Purpose

This workflow defines Git-based version control practices for EN 50128-compliant railway software development. Version control is **MANDATORY for ALL SIL levels** (EN 50128 Table A.9 #5: Software Configuration Management).

**Key Objectives**:
- Ensure all Configuration Items (CIs) are under version control
- Maintain complete history of all changes
- Enable traceability from code changes to requirements and change requests
- Support independent verification and validation (SIL 3-4)
- Enable baseline management and release control
- Facilitate concurrent development while maintaining integrity

### 1.2 Scope

**Applies to**:
- All source code (C files, headers)
- All documentation (requirements, design, test plans, reports)
- All test artifacts (test code, test data, test scripts)
- Build scripts and configuration files
- Tool configuration and qualification data
- Project management artifacts (plans, schedules, RTM)

**Out of Scope**:
- Binary artifacts (use Git LFS or external artifact repository)
- Large datasets (use external storage with version references)
- Temporary build outputs (excluded via .gitignore)

### 1.3 SIL-Specific Requirements

| Requirement | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 |
|-------------|-------|-------|-------|-------|-------|
| Version control for all CIs | **M** | **M** | **M** | **M** | **M** |
| Commit messages with rationale | R | HR | HR | **M** | **M** |
| Traceability to CRs in commits | R | HR | **M** | **M** | **M** |
| Signed commits (GPG) | - | R | HR | **M** | **M** |
| Branch protection rules | R | HR | **M** | **M** | **M** |
| Multi-person review (≥2) | - | R | HR | **M** | **M** |
| Independent reviewer (SIL 3-4) | - | - | R | **M** | **M** |
| Merge commit sign-off | - | R | HR | **M** | **M** |
| Tag signing for releases | - | R | **M** | **M** | **M** |
| Immutable history (no force push) | HR | HR | **M** | **M** | **M** |

**Legend**: M = Mandatory, HR = Highly Recommended, R = Recommended, - = No recommendation

### 1.4 EN 50128 References

- **Section 6.6**: Modification and Change Control (software configuration management MANDATORY)
- **Table A.9 #5**: Software Configuration Management (MANDATORY ALL SIL)
- **Reference D.48**: Software Configuration Management (detailed requirements)
- **Section 6.6.4.1**: Change control process (9 required aspects a-i)
- **Section 6.6.4.2**: Changes initiate return to appropriate lifecycle phase

---

## 2. EN 50128 Version Control Requirements

### 2.1 Configuration Management Requirements (EN 50128 Section 6.6)

EN 50128 mandates Software Configuration Management (SCM) for **ALL SIL levels** (Table A.9 #5). Version control is a fundamental component of SCM.

**EN 50128 Reference D.48** defines SCM as:

> "Software Configuration Management consists of the administrative and technical procedures used to:
> - Identify and document the functional and physical characteristics of a configuration item
> - Control changes to those characteristics
> - Record and report change processing and implementation status
> - Verify compliance with specified requirements"

**Version control** addresses the following EN 50128 requirements:

1. **Configuration Identification** (Section 6.6.3):
   - Unique identification of all CIs (Git commit SHA-1)
   - Version numbering scheme (Git tags, semantic versioning)
   - Baseline identification (Git tags, branches)

2. **Configuration Control** (Section 6.6.4):
   - Controlled modification of CIs (Git branching, pull requests)
   - Change approval before merge (branch protection, reviews)
   - Change traceability (commit messages reference CRs)

3. **Configuration Status Accounting** (Section 6.6.5):
   - Record of all changes (Git log)
   - Current status of CIs (Git status, branches, tags)
   - Change metrics (commit count, change rate)

4. **Configuration Audits** (Section 6.6.6):
   - Physical Configuration Audit (Git archive, tag validation)
   - Functional Configuration Audit (test results at tagged commits)

### 2.2 Traceability Requirements (EN 50128 Table A.9 #7)

**MANDATORY for SIL 3-4**, traceability requires:
- Every commit linked to a Change Request (CR) or requirement
- Bidirectional traceability: code → requirements, requirements → code
- Traceability verification before merge

**Implementation**:
- Commit messages include CR ID: `[CR-123] Fix timeout handling`
- Git hooks validate CR reference presence
- `workspace.py trace validate-ci` checks traceability coverage

### 2.3 Data Recording and Analysis (EN 50128 Table A.9 #8)

**MANDATORY for SIL 3-4**, data recording requires:
- Complete change history (Git log provides this)
- Change metrics (commit frequency, lines changed, authors)
- Trend analysis (change rate over time, hotspots)

**Implementation**:
- Git log analysis scripts extract metrics
- Configuration Status Accounting Workflow (WF-CM-004) defines metrics
- Monthly reports generated from Git data

### 2.4 Independence Requirements (SIL 3-4)

For SIL 3-4, verification must be **independent** from development:
- Reviewers MUST NOT be the commit author
- At least one reviewer MUST be from independent V&V team (VMGR/VER)
- Merge approval requires ≥2 approvals (SIL 3-4)

**Implementation**:
- Branch protection: require ≥2 reviews before merge
- CODEOWNERS file: require VER team approval
- Git hooks: prevent self-merge

---

## 3. Git Repository Setup

### 3.1 Repository Structure

**Recommended structure** for EN 50128 projects:

```
project-root/
├── .git/                       # Git metadata
├── .gitignore                  # Ignored files
├── .gitattributes              # Git LFS, line endings
├── README.md                   # Project overview
├── CHANGELOG.md                # Release history
├── BRANCH_STRUCTURE.md         # Branching strategy
├── LIFECYCLE_STATE.md          # Current phase, gate status
├── src/                        # Source code
│   ├── module1/
│   │   ├── module1.c
│   │   ├── module1.h
│   │   └── unit_test_module1.c
│   ├── module2/
│   └── main.c
├── include/                    # Public headers
├── tests/                      # Integration/system tests
│   ├── integration/
│   └── system/
├── docs/                       # Documentation
│   ├── requirements/
│   │   ├── SRS-v1.0.md        # Software Requirements Specification
│   │   └── RTM-v1.0.md        # Requirements Traceability Matrix
│   ├── design/
│   │   ├── SAS-v1.0.md        # Software Architecture Specification
│   │   └── SDS-v1.0.md        # Software Design Specification
│   ├── verification/
│   └── validation/
├── plans/                      # Project plans
│   ├── SQAP-v1.0.md           # Software Quality Assurance Plan
│   ├── SCMP-v1.0.md           # Software Configuration Management Plan
│   ├── SVP-v1.0.md            # Software Verification Plan
│   └── SVaP-v1.0.md           # Software Validation Plan
├── tools/                      # Build/analysis tools
│   ├── traceability_manager.py
│   ├── workflow_manager.py
│   └── workspace.py
├── build/                      # Build outputs (ignored)
├── coverage/                   # Coverage reports (ignored)
└── Makefile                    # Build system
```

### 3.2 .gitignore Configuration

**Exclude build artifacts, temporary files, and sensitive data**:

```gitignore
# Build outputs
build/
*.o
*.elf
*.bin
*.hex
*.map

# Coverage data (raw files ignored, reports committed)
*.gcda
*.gcno
coverage/*.info
coverage/html/

# IDE/editor files
.vscode/
.idea/
*.swp
*~

# OS files
.DS_Store
Thumbs.db

# Temporary files
*.tmp
*.bak
*.log

# Python bytecode (if using Python tools)
__pycache__/
*.pyc
*.pyo

# Secrets (NEVER commit)
.env
credentials.json
*.key
*.pem

# Large binary files (use Git LFS instead)
*.zip
*.tar.gz
*.pdf  # Exclude unless explicitly needed

# Test data (large datasets)
tests/data/large_dataset/
```

**Important**: For SIL 3-4, `.gitignore` MUST be reviewed and approved to ensure no safety-critical files are excluded.

### 3.3 .gitattributes Configuration

**Define file handling for line endings and Git LFS**:

```gitattributes
# Line ending normalization
* text=auto

# Force LF for shell scripts (even on Windows)
*.sh text eol=lf
*.py text eol=lf
Makefile text eol=lf

# Force CRLF for Windows-specific files
*.bat text eol=crlf

# Binary files
*.bin binary
*.elf binary
*.o binary
*.a binary

# Git LFS for large binary files
*.pdf filter=lfs diff=lfs merge=lfs -text
*.zip filter=lfs diff=lfs merge=lfs -text
*.tar.gz filter=lfs diff=lfs merge=lfs -text

# Mark as binary (no diff)
*.png binary
*.jpg binary
*.jpeg binary
```

### 3.4 Initial Repository Setup

**Step 1: Initialize repository**

```bash
# Create repository directory
mkdir -p project-name
cd project-name

# Initialize Git
git init

# Set user identity (required for commits)
git config user.name "John Doe"
git config user.email "john.doe@company.com"

# Enable GPG signing (MANDATORY SIL 3-4)
git config commit.gpgsign true
git config tag.gpgsign true
git config user.signingkey <GPG_KEY_ID>

# Set default branch name
git config init.defaultBranch main
```

**Step 2: Create .gitignore and .gitattributes**

```bash
# Create .gitignore (see Section 3.2)
cat > .gitignore << 'EOF'
# Build outputs
build/
*.o
...
EOF

# Create .gitattributes (see Section 3.3)
cat > .gitattributes << 'EOF'
* text=auto
*.sh text eol=lf
...
EOF

# Stage and commit
git add .gitignore .gitattributes
git commit -m "chore: Initialize repository with Git configuration

- Add .gitignore for build artifacts and temporary files
- Add .gitattributes for line endings and Git LFS
- Configure GPG signing for SIL 3 compliance

[CR-001] Initial repository setup"
```

**Step 3: Install Git hooks**

```bash
# Copy hooks from tools/ (see Section 10)
cp tools/git-hooks/pre-commit .git/hooks/pre-commit
cp tools/git-hooks/commit-msg .git/hooks/commit-msg
chmod +x .git/hooks/pre-commit .git/hooks/commit-msg

# Test hooks
git commit --allow-empty -m "test: Verify hooks work [CR-001]"
```

**Step 4: Create initial structure**

```bash
# Create directory structure
mkdir -p src include tests/{integration,system} docs/{requirements,design,verification,validation} plans tools

# Create README
cat > README.md << 'EOF'
# Project Name

EN 50128 SIL 3 Railway Software Project

## Overview
...
EOF

# Commit structure
git add .
git commit -m "chore: Create initial project structure [CR-001]"
```

**Step 5: Configure remote and push**

```bash
# Add remote (GitHub, GitLab, Bitbucket, etc.)
git remote add origin https://github.com/company/project-name.git

# Push to remote
git push -u origin main
```

### 3.5 Repository Configuration for SIL 3-4

**MANDATORY settings for SIL 3-4**:

```bash
# Prevent force push to protected branches
git config --local receive.denyNonFastForwards true
git config --local receive.denyDeletes true

# Enable commit graph for performance
git config --local core.commitGraph true
git config --local gc.writeCommitGraph true

# Enable reftable for better ref handling (Git 2.36+)
git config --local core.refStorage reftable

# Enable fsync for data integrity (SIL 3-4)
git config --local core.fsyncMethod fsync
git config --local core.fsync committed

# Set merge strategy (no fast-forward for traceability)
git config --local merge.ff false

# Enable signed commits verification
git config --local gpg.program gpg
```

**Remote repository protection** (GitHub/GitLab/Bitbucket):
- Enable branch protection for `main`, `develop`, `release/*`
- Require ≥2 reviews before merge (SIL 3-4)
- Require review from CODEOWNERS (VER team)
- Require status checks to pass (CI, tests, coverage)
- Require signed commits
- Prevent force push
- Prevent deletion

---

## 4. Branching Strategies

### 4.1 EN 50128-Adapted Git Flow

**EN 50128 V-Model** requires phased development with gate checks. Standard Git Flow is adapted to align with EN 50128 phases:

```
main (production releases, baselines)
  │
  └─── develop (integration branch)
        │
        ├─── feature/REQ-<id>-<description>  (requirements, design, implementation)
        │
        ├─── bugfix/CR-<id>-<description>     (defect fixes)
        │
        ├─── hotfix/CR-<id>-<description>     (urgent production fixes)
        │
        └─── release/v<major>.<minor>.<patch> (release preparation)
```

**Branch Types**:

1. **`main`**: Production-ready code, baselines at gate checks
   - Only updated via merge from `release/*` or `hotfix/*`
   - Every commit tagged with version (e.g., `v1.0.0`)
   - Represents approved baselines (Gate 4, Gate 6, Gate 7)
   - **PROTECTED**: No direct commits, force push forbidden

2. **`develop`**: Integration branch for ongoing development
   - Reflects current state of development
   - Integration testing performed here
   - Merged to `release/*` for release preparation
   - **PROTECTED** (SIL 3-4): Requires review before merge

3. **`feature/<type>-<id>-<description>`**: Feature development
   - Created from `develop`
   - Examples:
     - `feature/REQ-42-timeout-handling` (requirements work)
     - `feature/DES-15-watchdog-module` (design/implementation)
   - Merged back to `develop` after review
   - Deleted after merge

4. **`bugfix/CR-<id>-<description>`**: Bug fixes
   - Created from `develop`
   - Example: `bugfix/CR-123-null-pointer-check`
   - Merged back to `develop` after review and testing
   - Deleted after merge

5. **`hotfix/CR-<id>-<description>`**: Urgent production fixes
   - Created from `main` (fixes released code)
   - Example: `hotfix/CR-456-critical-timeout`
   - Merged to BOTH `main` AND `develop`
   - Requires expedited review (but still ≥2 for SIL 3-4)
   - Tagged immediately after merge to `main`
   - Deleted after merge

6. **`release/v<version>`**: Release preparation
   - Created from `develop`
   - Example: `release/v1.2.0`
   - Final testing, documentation updates, version bumps
   - Merged to `main` (with tag) and back to `develop`
   - Deleted after merge

### 4.2 Branch Naming Conventions

**Standard format**:

```
<type>/<id>-<short-description>
```

**Type**:
- `feature`: New functionality, requirements, design
- `bugfix`: Non-critical defect fix
- `hotfix`: Critical production defect fix
- `release`: Release preparation
- `experiment`: Exploratory work (not merged to develop)

**ID**:
- Requirements: `REQ-<number>` (e.g., `REQ-42`)
- Design: `DES-<number>` (e.g., `DES-15`)
- Change Request: `CR-<number>` (e.g., `CR-123`)

**Short Description**:
- Lowercase, hyphen-separated
- 2-5 words
- Descriptive but concise

**Examples**:
- `feature/REQ-42-timeout-handling`
- `feature/DES-15-watchdog-module`
- `bugfix/CR-123-null-pointer-check`
- `hotfix/CR-456-critical-timeout`
- `release/v1.2.0`

### 4.3 Branching Workflow

**Feature Development (Typical)**:

```bash
# Step 1: Create feature branch from develop
git checkout develop
git pull origin develop
git checkout -b feature/REQ-42-timeout-handling

# Step 2: Implement feature with commits
# (See Section 5 for commit conventions)
git add src/timeout.c src/timeout.h
git commit -m "feat(timeout): Implement timeout detection [REQ-42]

Add timeout detection for sensor communication.
- Configurable timeout threshold
- Callback for timeout events
- Unit tests with 100% coverage

EN 50128 Requirements:
- REQ-42: System shall detect sensor timeout within 100ms
- Defensive programming: NULL pointer checks
- MISRA C:2012 compliant

[CR-050] Implement timeout handling"

# Step 3: Push to remote
git push -u origin feature/REQ-42-timeout-handling

# Step 4: Create pull request (via GitHub/GitLab UI)
# - Title: "[REQ-42] Implement timeout handling"
# - Description: Link to requirement, CR, test results
# - Assign reviewers (≥2 for SIL 3-4, at least 1 from VER)

# Step 5: Address review comments
git add src/timeout.c
git commit -m "fix(timeout): Address review comments [REQ-42]

- Add bounds check for threshold parameter
- Improve error message clarity
- Fix typo in comment

[CR-050] Review feedback"

git push

# Step 6: After approval, squash and merge (or merge)
# (Done via UI with merge commit for traceability)

# Step 7: Delete feature branch
git checkout develop
git pull origin develop
git branch -d feature/REQ-42-timeout-handling
git push origin --delete feature/REQ-42-timeout-handling
```

**Hotfix Workflow (Urgent)**:

```bash
# Step 1: Create hotfix branch from main
git checkout main
git pull origin main
git checkout -b hotfix/CR-456-critical-timeout

# Step 2: Implement fix
git add src/timeout.c
git commit -m "fix(timeout)!: Fix critical timeout overflow [CR-456]

CRITICAL: Integer overflow in timeout calculation causes
immediate timeout trigger, affecting all sensors.

Root Cause: Multiplication overflow when threshold > 1000ms
Fix: Use 64-bit arithmetic, add overflow check

Impact: SIL 3 safety function affected
Testing: Unit tests + integration test on target hardware
Verification: Static analysis clean, coverage 100%

BREAKING CHANGE: Timeout API signature changed to accept uint32_t

[CR-456] Critical timeout fix"

# Step 3: Push and create pull request
git push -u origin hotfix/CR-456-critical-timeout

# Step 4: Expedited review (still ≥2 for SIL 3-4)
# Include VER team, VMGR approval required

# Step 5: Merge to main
git checkout main
git merge --no-ff hotfix/CR-456-critical-timeout -m "Merge hotfix CR-456"

# Step 6: Tag immediately
git tag -a v1.1.1 -m "Hotfix release v1.1.1

Critical timeout overflow fix (CR-456)

Changes:
- Fix integer overflow in timeout calculation
- Add overflow detection
- Update API to use uint32_t

Safety Impact: Prevents false timeout triggers
Verification: Complete, all tests pass
Approved by: VMGR"

git push origin main --tags

# Step 7: Merge back to develop
git checkout develop
git merge --no-ff hotfix/CR-456-critical-timeout
git push origin develop

# Step 8: Delete hotfix branch
git branch -d hotfix/CR-456-critical-timeout
git push origin --delete hotfix/CR-456-critical-timeout
```

### 4.4 Branch Protection Rules (SIL 3-4)

**GitHub/GitLab/Bitbucket configuration**:

**`main` branch**:
- ✅ Require pull request reviews: ≥2 approvals
- ✅ Require review from CODEOWNERS (VER team)
- ✅ Dismiss stale reviews when new commits pushed
- ✅ Require status checks to pass: CI, tests, coverage, static analysis
- ✅ Require signed commits
- ✅ Require linear history (no merge commits from non-protected branches)
- ✅ Prevent force push
- ✅ Prevent deletion
- ✅ Restrict who can push: Release Manager only (for tags)

**`develop` branch** (SIL 3-4):
- ✅ Require pull request reviews: ≥1 approval (SIL 2), ≥2 approvals (SIL 3-4)
- ✅ Require status checks to pass
- ✅ Require signed commits (SIL 3-4)
- ✅ Prevent force push
- ✅ Prevent deletion

**`release/*` branches**:
- ✅ Require pull request reviews: ≥2 approvals (SIL 3-4)
- ✅ Require VER/VAL approval before merge to main
- ✅ Require all tests passing
- ✅ Require signed commits

---

## 5. Commit Conventions

### 5.1 Commit Message Structure

**EN 50128-compliant commit messages** follow this structure:

```
<type>(<scope>)[!]: <subject> [<requirement-id>]

<body>

<footer>
```

**Components**:

1. **Type**: Category of change
   - `feat`: New feature (maps to requirements, design, implementation)
   - `fix`: Bug fix (maps to defect CR)
   - `docs`: Documentation only
   - `test`: Test code only
   - `refactor`: Code restructuring (no functional change)
   - `perf`: Performance improvement
   - `chore`: Build, tools, configuration
   - `revert`: Revert previous commit

2. **Scope**: Module or component affected (optional but recommended)
   - Examples: `timeout`, `watchdog`, `sensor`, `uart`

3. **`!`**: Breaking change indicator (optional)
   - Append `!` after scope if change breaks API/behavior

4. **Subject**: Short summary (≤72 characters)
   - Imperative mood: "Add feature" not "Added feature"
   - No period at end
   - Include requirement ID: `[REQ-42]` or `[CR-123]`

5. **Body**: Detailed description (optional for trivial commits, **MANDATORY SIL 3-4 for non-trivial**)
   - Why change was made (rationale)
   - What changed (high-level)
   - EN 50128 references (requirements, safety considerations)
   - Testing performed
   - Wrap at 72 characters

6. **Footer**: Traceability references (**MANDATORY SIL 3-4**)
   - `[CR-<id>]`: Change request ID (REQUIRED)
   - `Refs: REQ-<id>, DES-<id>`: Related requirements/design
   - `BREAKING CHANGE:`: Description of breaking change
   - `Reviewed-by:`: Reviewer names (for manual tracking)
   - `Tested-by:`: Tester names (for manual tracking)

### 5.2 Commit Message Examples

**Example 1: Feature implementation (SIL 3)**

```
feat(timeout): Implement timeout detection [REQ-42]

Add timeout detection for sensor communication with configurable
threshold and callback notification.

Changes:
- Add timeout_init() for configuration
- Add timeout_check() for periodic monitoring
- Add timeout_callback_t for event notification
- Implement 100ms detection granularity

EN 50128 Compliance:
- REQ-42: System shall detect sensor timeout within 100ms
- Defensive programming: NULL pointer checks, bounds validation
- MISRA C:2012 compliant (zero violations)
- Cyclomatic complexity: 5 (within SIL 3 limit of 10)

Testing:
- Unit tests: 15 tests, 100% coverage (statement, branch, condition)
- Integration test: Verified on target hardware
- Fault injection: Tested timeout scenarios

[CR-050] Implement timeout handling
Refs: REQ-42, DES-15
Reviewed-by: Jane Smith (VER), John Doe (IMP)
```

**Example 2: Bug fix (SIL 2)**

```
fix(uart): Correct baud rate calculation for high speeds [CR-123]

Fix incorrect baud rate register value for rates above 115200.
Previous calculation truncated fractional part, causing up to
5% error at 921600 baud.

Root Cause:
- Integer division in baud rate calculation
- Truncation error significant at high baud rates

Fix:
- Use 64-bit intermediate calculation
- Round to nearest integer instead of truncate
- Add validation of calculated value against limits

Impact:
- Affects UART communication at >115200 baud
- No safety impact (UART used for diagnostics only, SIL 0)
- Backward compatible (lower baud rates unaffected)

Testing:
- Unit test: Verify all standard baud rates correct
- Hardware test: 921600 baud communication successful
- Regression: All existing tests pass

[CR-123] Fix UART baud rate calculation
Refs: DES-08 (UART module design)
```

**Example 3: Documentation update**

```
docs(requirements): Update SRS with timeout requirements [REQ-42]

Add detailed requirements for sensor timeout detection to
Software Requirements Specification (SRS-v1.2.md).

Changes:
- REQ-42: Timeout detection within 100ms
- REQ-43: Configurable timeout threshold (50-5000ms)
- REQ-44: Timeout callback notification
- Updated traceability matrix (RTM-v1.2.md)

[CR-050] Timeout requirements documentation
```

**Example 4: Breaking change (SIL 3)**

```
feat(timeout)!: Change timeout API to support multiple sensors [REQ-45]

Extend timeout API to support multiple independent sensor timeouts.

BREAKING CHANGE: timeout_init() now requires sensor ID parameter.
Old: timeout_init(threshold, callback)
New: timeout_init(sensor_id, threshold, callback)

Migration:
- Add sensor_id parameter to all timeout_init() calls
- Use SENSOR_ID_0 for single-sensor systems (backward compat)

Changes:
- Add sensor_id parameter to timeout_init()
- Add per-sensor timeout state tracking
- Update unit tests for multi-sensor scenarios

Rationale:
- System expanded from 1 to 4 sensors (REQ-45)
- Single timeout insufficient for multi-sensor monitoring
- Maintains separate timeout state per sensor

Testing:
- Unit tests: 25 tests (up from 15), 100% coverage
- Integration test: 4-sensor configuration verified
- Regression: Single-sensor configuration still works

[CR-075] Multi-sensor timeout support
Refs: REQ-45, DES-20
BREAKING CHANGE: API signature changed, see migration guide
Reviewed-by: Alice Johnson (VER), Bob Smith (DES)
```

**Example 5: Revert commit**

```
revert: Revert "feat(timeout): Change timeout API" [CR-078]

This reverts commit a1b2c3d4e5f6.

Reason: Integration testing revealed timing issue with multi-sensor
timeout handling. Watchdog triggers prematurely when >2 sensors active.

Root Cause: CPU load exceeds budget with 4 timeout monitors.

Next Steps:
- Optimize timeout_check() for lower CPU usage
- Re-evaluate with optimized implementation

[CR-078] Revert multi-sensor timeout (timing issue)
Refs: CR-075 (original), REQ-45 (still pending)
Approved-by: VMGR
```

### 5.3 SIL-Specific Commit Requirements

| Requirement | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 |
|-------------|-------|-------|-------|-------|-------|
| Commit type prefix | R | HR | **M** | **M** | **M** |
| Commit scope | - | R | HR | **M** | **M** |
| Requirement ID in subject | - | R | HR | **M** | **M** |
| Detailed body (non-trivial) | R | HR | **M** | **M** | **M** |
| EN 50128 rationale | - | R | HR | **M** | **M** |
| Testing summary | R | HR | **M** | **M** | **M** |
| CR reference in footer | R | HR | **M** | **M** | **M** |
| GPG signature | - | R | HR | **M** | **M** |
| Reviewer names (manual) | - | - | R | HR | **M** |

### 5.4 Commit Hooks Enforcement

**Git hooks** (see Section 10) enforce commit message format:

- **`commit-msg` hook**: Validates commit message structure
  - Check type, scope, subject length
  - Require CR reference for SIL 3-4
  - Require GPG signature for SIL 3-4
  - Reject commit if validation fails

**Example hook validation**:

```bash
# .git/hooks/commit-msg
#!/bin/bash

# Extract commit message
COMMIT_MSG=$(cat "$1")

# Check format: type(scope): subject [REQ-XX]
if ! echo "$COMMIT_MSG" | grep -qE "^(feat|fix|docs|test|refactor|perf|chore|revert)(\(.+\))?!?: .+ \[(REQ|CR)-[0-9]+\]"; then
    echo "ERROR: Commit message does not match format"
    echo "Expected: type(scope): subject [REQ-XX]"
    exit 1
fi

# Check CR reference in footer (SIL 3-4)
if ! echo "$COMMIT_MSG" | grep -qE "\[CR-[0-9]+\]"; then
    echo "ERROR: Missing CR reference in footer (required SIL 3-4)"
    exit 1
fi

# Check GPG signature (SIL 3-4)
if ! git verify-commit HEAD 2>/dev/null; then
    echo "ERROR: Commit not signed (required SIL 3-4)"
    exit 1
fi

exit 0
```

---

## 6. Merge Policies

### 6.1 Merge Strategies

**EN 50128 traceability** requires complete change history. Three merge strategies:

1. **Merge Commit** (RECOMMENDED for SIL 3-4)
   - Creates explicit merge commit
   - Preserves complete feature branch history
   - Best traceability: all individual commits visible
   - `git merge --no-ff feature/REQ-42-timeout`

2. **Squash and Merge** (ACCEPTABLE for SIL 0-2)
   - Combines all feature commits into single commit
   - Cleaner history, but loses individual commit detail
   - Acceptable if feature branch commits are trivial
   - `git merge --squash feature/REQ-42-timeout`

3. **Rebase and Merge** (NOT RECOMMENDED for SIL 3-4)
   - Replays commits on top of target branch (rewrites history)
   - Clean linear history, but loses merge context
   - Violates "immutable history" principle for SIL 3-4
   - **AVOID** for SIL 3-4

**SIL-Specific Recommendations**:

| Strategy | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 | Rationale |
|----------|-------|-------|-------|-------|-------|-----------|
| Merge commit (--no-ff) | HR | HR | **M** | **M** | **M** | Full traceability |
| Squash and merge | R | R | R | - | - | Loss of detail |
| Rebase and merge | R | R | - | NR | NR | History rewrite |

**Legend**: M = Mandatory, HR = Highly Recommended, R = Recommended, NR = Not Recommended

### 6.2 Pull Request (PR) Review Process

**All merges** to `develop`, `release/*`, or `main` MUST go through pull request review.

**PR Requirements (SIL 3-4)**:

1. **Reviewer Count**: ≥2 reviewers (at least 1 from VER team)
2. **Review Criteria**:
   - Code correctness (logic, algorithm)
   - MISRA C compliance (zero mandatory violations)
   - Defensive programming (NULL checks, bounds checks)
   - Complexity within limits (≤10 SIL 3-4)
   - Unit tests present (100% coverage for SIL 3-4)
   - Traceability to requirements/CRs
   - Documentation updated (if applicable)
   - EN 50128 compliance (safety considerations)

3. **Status Checks** (CI must pass):
   - Build successful (no warnings for SIL 3-4)
   - Unit tests pass (100% for all tests)
   - Coverage meets threshold (100% statement/branch/condition SIL 3-4)
   - Static analysis clean (Cppcheck, Clang, PC-lint)
   - Complexity check pass (all functions ≤10 CCN for SIL 3-4)
   - Traceability validation pass (`workspace.py trace validate-ci`)

4. **Approval Required**:
   - ≥2 approvals from reviewers
   - At least 1 approval from VER team (CODEOWNERS)
   - VMGR approval for safety-critical changes (SIL 3-4)

### 6.3 Pull Request Template

**GitHub/GitLab PR template** (`.github/PULL_REQUEST_TEMPLATE.md`):

```markdown
## Description

<!-- Brief summary of changes -->

## Related Issues

- Requirements: REQ-XXX
- Change Request: CR-XXX
- Related PRs: #123

## Type of Change

- [ ] Feature (feat)
- [ ] Bug fix (fix)
- [ ] Documentation (docs)
- [ ] Refactoring (refactor)
- [ ] Performance (perf)
- [ ] Test (test)
- [ ] Chore (chore)

## EN 50128 Compliance

- [ ] SIL level: [0/1/2/3/4]
- [ ] Requirements traceability updated
- [ ] MISRA C compliant (zero mandatory violations)
- [ ] Defensive programming applied
- [ ] Complexity within limits (≤10 for SIL 3-4)
- [ ] Safety considerations documented

## Testing

- [ ] Unit tests added/updated
- [ ] Coverage: [X]% statement, [Y]% branch, [Z]% condition
- [ ] Integration tests pass
- [ ] Target hardware tested (if applicable)

## Verification

- [ ] Static analysis clean (Cppcheck, Clang)
- [ ] Build successful (no warnings for SIL 3-4)
- [ ] Traceability validation pass
- [ ] Code review completed (≥2 reviewers for SIL 3-4)

## Documentation

- [ ] Requirements updated (SRS)
- [ ] Design updated (SAS/SDS)
- [ ] Traceability matrix updated (RTM)
- [ ] CHANGELOG updated

## Checklist

- [ ] Commits follow conventional format
- [ ] Commits signed (GPG) for SIL 3-4
- [ ] CR reference in all commits
- [ ] Branch name follows convention
- [ ] No merge conflicts
- [ ] CI passes all checks

## Reviewer Notes

<!-- Additional context for reviewers -->
```

### 6.4 Merge Workflow Example

**Step-by-step merge process**:

```bash
# Developer: Create PR (via GitHub/GitLab UI)
# Title: [REQ-42] Implement timeout handling
# Assign reviewers: reviewer1 (VER), reviewer2 (IMP)
# Link CR-050

# Reviewer 1 (VER): Review code
# - Check MISRA C compliance
# - Check complexity (lizard)
# - Check defensive programming
# - Approve or request changes

# Reviewer 2 (IMP): Review code
# - Check design correctness
# - Check test coverage
# - Approve or request changes

# CI: Automated checks
# ✅ Build: SUCCESS
# ✅ Tests: 100% pass
# ✅ Coverage: 100% statement, 100% branch, 100% condition
# ✅ Static analysis: 0 issues
# ✅ Complexity: All functions ≤10 CCN
# ✅ Traceability: PASS

# After ≥2 approvals AND CI pass, merge
git checkout develop
git pull origin develop
git merge --no-ff feature/REQ-42-timeout-handling -m "Merge feature REQ-42: Timeout handling

Implement sensor timeout detection with 100ms granularity.

Changes:
- Add timeout_init(), timeout_check(), timeout_callback_t
- Unit tests with 100% coverage
- MISRA C compliant, complexity ≤10
- Documentation updated

Reviewed-by: Jane Smith (VER), John Doe (IMP)
Approved-by: VMGR
[CR-050] Timeout handling implementation"

# Push merge
git push origin develop

# Delete feature branch (via UI or command line)
git branch -d feature/REQ-42-timeout-handling
git push origin --delete feature/REQ-42-timeout-handling

# Update traceability
workspace.py trace validate-ci --fix
```

### 6.5 Merge Conflict Resolution

**Conflicts are common** in concurrent development. Resolution process:

```bash
# Step 1: Sync feature branch with develop
git checkout feature/REQ-42-timeout-handling
git fetch origin
git merge origin/develop

# Step 2: Resolve conflicts
# (Git marks conflict areas with <<<<<<, ======, >>>>>>)
# Edit conflicted files, choose correct version

# Step 3: Mark resolved
git add src/timeout.c
git commit -m "merge: Resolve conflicts with develop [CR-050]

Conflicts in timeout.c due to concurrent changes to watchdog module.

Resolution:
- Keep both timeout and watchdog functionality
- Update function call to new watchdog API
- Verified no functional regression

Tested: Unit tests + integration test pass"

# Step 4: Push and continue PR review
git push

# Reviewers: Re-review conflict resolution
# CI: Re-run checks
```

**Conflict Prevention**:
- Frequent syncing: `git pull origin develop` daily
- Small, focused PRs (easier to review, fewer conflicts)
- Coordinate with team on overlapping work
- Use CODEOWNERS to identify module owners

---

## 7. Tag Management

### 7.1 Semantic Versioning for EN 50128

**EN 50128 baselines** correspond to Git tags. Use **Semantic Versioning** (SemVer):

```
v<MAJOR>.<MINOR>.<PATCH>[-<PRERELEASE>][+<BUILD>]
```

**Components**:
- **MAJOR**: Incompatible API/behavior change (rare in safety-critical)
- **MINOR**: New functionality, backward compatible
- **PATCH**: Bug fixes, backward compatible
- **PRERELEASE**: Alpha, beta, rc (release candidate)
- **BUILD**: Build metadata (optional)

**Examples**:
- `v1.0.0`: First production release (Gate 7 baseline)
- `v1.1.0`: New feature (backward compatible)
- `v1.1.1`: Bug fix
- `v2.0.0`: Breaking change (new major version)
- `v1.2.0-rc.1`: Release candidate (before v1.2.0)
- `v1.2.0+20240315`: Build metadata (date)

### 7.2 Baseline Tags

**EN 50128 baselines** are tagged at phase gates:

| Phase Gate | Tag Prefix | Example | Description |
|------------|------------|---------|-------------|
| Gate 1 | `baseline/gate1-` | `baseline/gate1-planning` | Planning complete (SQAP, SCMP, SVP, SVaP) |
| Gate 2 | `baseline/gate2-` | `baseline/gate2-requirements` | Requirements complete (SRS, RTM, Hazard Log) |
| Gate 3 | `baseline/gate3-` | `baseline/gate3-design` | Design complete (SAS, SDS) |
| Gate 4 | `baseline/gate4-` | `baseline/gate4-implementation` | Implementation complete (code, unit tests) |
| Gate 5 | `baseline/gate5-` | `baseline/gate5-integration` | Integration complete (integration tests) |
| Gate 6 | `baseline/gate6-` | `baseline/gate6-validation` | Validation complete (system tests) |
| Gate 7 | `v1.0.0` | `v1.0.0` | Deployment ready (production release) |

**Note**: Gate 7 uses semantic version tag (e.g., `v1.0.0`), not `baseline/` prefix.

### 7.3 Tag Creation

**Annotated tags** (recommended for SIL 3-4):

```bash
# Create annotated tag
git tag -a v1.0.0 -m "Release v1.0.0

First production release (Gate 7 baseline)

Features:
- Sensor timeout detection (REQ-42)
- Watchdog monitoring (REQ-50)
- UART diagnostics (REQ-55)

Verification:
- 100% code coverage (statement, branch, condition)
- Static analysis clean (Cppcheck, Clang, PC-lint)
- MISRA C:2012 compliant (zero mandatory violations)
- Complexity: All functions ≤10 CCN

Validation:
- System tests: 50 tests, 100% pass
- Target hardware: Verified on production platform
- Operational scenarios: 10 scenarios, all pass

Approved by: VMGR
Baseline: Gate 7 (Deployment Ready)"

# Push tag to remote
git push origin v1.0.0
```

**Signed tags** (MANDATORY SIL 3-4):

```bash
# Create signed tag
git tag -s v1.0.0 -m "Release v1.0.0

[... same message as above ...]

Signed-off-by: Release Manager <release@company.com>
GPG Key: 0x12345678"

# Verify signature
git tag -v v1.0.0

# Push signed tag
git push origin v1.0.0
```

**Lightweight tags** (NOT RECOMMENDED for baselines):

```bash
# Lightweight tag (no message, no signature)
git tag v1.0.0

# NOT RECOMMENDED for SIL 3-4 baselines (no metadata)
```

### 7.4 Tag Listing and Verification

```bash
# List all tags
git tag

# List tags matching pattern
git tag -l "v1.*"

# Show tag details
git show v1.0.0

# Verify signed tag
git tag -v v1.0.0

# List tags with annotations
git tag -n5  # Show first 5 lines of annotation
```

### 7.5 Release Notes Generation

**Automated release notes** from Git log:

```bash
# Generate release notes (commits since last tag)
git log v0.9.0..v1.0.0 --oneline --pretty=format:"- %s"

# Example output:
# - feat(timeout): Implement timeout detection [REQ-42]
# - feat(watchdog): Add watchdog monitoring [REQ-50]
# - fix(uart): Correct baud rate calculation [CR-123]
# - docs(requirements): Update SRS with timeout requirements [REQ-42]

# Generate detailed release notes
git log v0.9.0..v1.0.0 --pretty=format:"%h - %s%n%b%n"

# Filter by commit type (features only)
git log v0.9.0..v1.0.0 --oneline --grep="^feat"

# Generate CHANGELOG.md entry
cat >> CHANGELOG.md << EOF
## [1.0.0] - $(date +%Y-%m-%d)

### Added
$(git log v0.9.0..v1.0.0 --oneline --grep="^feat" --pretty=format:"- %s")

### Fixed
$(git log v0.9.0..v1.0.0 --oneline --grep="^fix" --pretty=format:"- %s")

### Changed
$(git log v0.9.0..v1.0.0 --oneline --grep="^refactor\|^perf" --pretty=format:"- %s")

EOF
```

---

## 8. CI Integration

### 8.1 Continuous Integration for EN 50128

**CI pipelines** automate verification tasks required by EN 50128:
- Build (compilation with zero warnings for SIL 3-4)
- Unit testing (100% coverage for SIL 3-4)
- Static analysis (Cppcheck, Clang, PC-lint)
- Complexity analysis (Lizard)
- Traceability validation (`workspace.py trace`)
- MISRA C compliance check

**CI triggers**:
- Every push to feature branches
- Every pull request to `develop` or `main`
- Nightly builds (comprehensive, longer analysis)

### 8.2 CI Pipeline Example (GitHub Actions)

**`.github/workflows/ci.yml`**:

```yaml
name: EN 50128 CI Pipeline

on:
  push:
    branches: [ develop, main, 'feature/**', 'bugfix/**', 'hotfix/**' ]
  pull_request:
    branches: [ develop, main ]

jobs:
  build-and-test:
    runs-on: ubuntu-latest
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v3
      with:
        fetch-depth: 0  # Full history for traceability
    
    - name: Install dependencies
      run: |
        sudo apt-get update
        sudo apt-get install -y gcc make lcov cppcheck clang clang-tools python3-pip
        pip3 install lizard pyyaml
    
    - name: Verify commit messages (SIL 3-4)
      run: |
        # Check all commits in PR
        for commit in $(git rev-list origin/develop..HEAD); do
          git show -s --format=%B $commit | python3 tools/verify_commit_msg.py
        done
    
    - name: Build (zero warnings for SIL 3-4)
      run: |
        make clean
        make CFLAGS="-Wall -Wextra -Werror" all
    
    - name: Run unit tests
      run: |
        make test
    
    - name: Generate coverage
      run: |
        make coverage
        lcov --capture --directory . --output-file coverage.info
        lcov --remove coverage.info '/usr/*' --output-file coverage.info
        lcov --list coverage.info
    
    - name: Check coverage threshold (SIL 3-4: 100%)
      run: |
        # Extract coverage percentages
        STMT_COV=$(lcov --summary coverage.info 2>&1 | grep "lines" | awk '{print $2}' | sed 's/%//')
        BRANCH_COV=$(lcov --summary coverage.info 2>&1 | grep "branches" | awk '{print $2}' | sed 's/%//')
        
        # SIL 3-4 requires 100% coverage
        if (( $(echo "$STMT_COV < 100" | bc -l) )); then
          echo "ERROR: Statement coverage $STMT_COV% < 100% (SIL 3-4)"
          exit 1
        fi
        if (( $(echo "$BRANCH_COV < 100" | bc -l) )); then
          echo "ERROR: Branch coverage $BRANCH_COV% < 100% (SIL 3-4)"
          exit 1
        fi
    
    - name: Static analysis (Cppcheck)
      run: |
        cppcheck --enable=all --error-exitcode=1 --suppress=missingIncludeSystem src/
    
    - name: Static analysis (Clang)
      run: |
        scan-build --status-bugs make
    
    - name: Complexity analysis (SIL 3-4: CCN ≤ 10)
      run: |
        lizard src/ -l c -C 10 -w
    
    - name: MISRA C compliance check
      run: |
        # Use PC-lint or custom checker
        python3 tools/check_misra.py src/
    
    - name: Traceability validation
      run: |
        python3 tools/workspace.py trace validate-ci
    
    - name: Upload coverage report
      uses: codecov/codecov-action@v3
      with:
        files: coverage.info
        fail_ci_if_error: true
    
    - name: Archive test results
      if: always()
      uses: actions/upload-artifact@v3
      with:
        name: test-results
        path: |
          build/test_results.xml
          coverage/
```

### 8.3 Traceability Validation in CI

**`workspace.py trace validate-ci`** checks:
- All requirements have associated code commits
- All code commits reference requirements or CRs
- Traceability matrix up-to-date
- No orphaned requirements (defined but not implemented)
- No orphaned commits (implemented but not traced)

**Example usage**:

```bash
# Validate traceability for current commit
workspace.py trace validate-ci

# Example output:
# ✅ All requirements traced to commits
# ✅ All commits reference requirements/CRs
# ✅ Traceability matrix up-to-date
# ✅ No orphaned items
# 
# Summary:
# - 50 requirements, 50 traced (100%)
# - 120 commits, 120 with CR references (100%)
# - Traceability: PASS

# If validation fails (example):
# ❌ Traceability validation FAILED
# 
# Orphaned requirements (defined but not implemented):
# - REQ-99: Emergency stop button
# 
# Commits without CR reference:
# - a1b2c3d: refactor(timeout): Simplify logic
# 
# Traceability matrix outdated:
# - RTM-v1.2.md last updated 2024-03-01 (10 days ago)
# - Recent commits without RTM update: 5
# 
# Fix with: workspace.py trace validate-ci --fix
```

**Automatic fixes** (with `--fix`):
- Generate placeholder CR for commits without reference
- Update traceability matrix with recent commits
- Add missing entries to RTM

---

## 9. Tool Integration

### 9.1 Workspace CLI Integration

**`workspace.py`** provides unified interface for traceability and workflow management.

**Version control-related commands**:

```bash
# Trace Management

# Validate traceability for CI pipeline
workspace.py trace validate-ci
# Output: ✅ Traceability: PASS (all requirements traced, all commits reference CRs)

# Validate traceability with auto-fix
workspace.py trace validate-ci --fix
# Output: ✅ Fixed 3 orphaned commits, updated RTM

# Link commit to requirement
workspace.py trace link-commit a1b2c3d REQ-42
# Output: ✅ Commit a1b2c3d linked to REQ-42 in RTM

# Link commit to CR
workspace.py trace link-commit a1b2c3d CR-050
# Output: ✅ Commit a1b2c3d linked to CR-050

# Show requirement implementation history
workspace.py trace show-req REQ-42
# Output:
# REQ-42: System shall detect sensor timeout within 100ms
# Status: Implemented
# Implementation commits:
# - a1b2c3d: feat(timeout): Implement timeout detection [REQ-42]
# - b2c3d4e: test(timeout): Add timeout unit tests [REQ-42]
# - c3d4e5f: docs(requirements): Update SRS with timeout requirements [REQ-42]
# Change Requests: CR-050
# Tests: test_timeout_detection_100ms (PASS)

# Show all commits for CR
workspace.py trace show-cr CR-050
# Output:
# CR-050: Implement timeout handling
# Status: Closed
# Related requirements: REQ-42, REQ-43
# Commits:
# - a1b2c3d: feat(timeout): Implement timeout detection [REQ-42]
# - b2c3d4e: test(timeout): Add timeout unit tests [REQ-42]
# - c3d4e5f: docs(requirements): Update SRS with timeout requirements [REQ-42]
# - d4e5f6a: fix(timeout): Address review comments [REQ-42]

# Generate traceability report
workspace.py trace report --format markdown
# Output: Traceability report written to docs/traceability-report-20240315.md

# Workflow Management (Baseline-related)

# Create baseline at gate check
workspace.py wf create-baseline gate4-implementation
# Output:
# ✅ Baseline created: baseline/gate4-implementation
# ✅ Git tag created: baseline/gate4-implementation
# ✅ Baseline content documented in docs/baselines/gate4-implementation.md

# List all baselines
workspace.py wf list-baselines
# Output:
# Baselines:
# - baseline/gate1-planning (2024-01-15)
# - baseline/gate2-requirements (2024-02-01)
# - baseline/gate3-design (2024-02-20)
# - baseline/gate4-implementation (2024-03-15)

# Show baseline details
workspace.py wf show-baseline gate4-implementation
# Output:
# Baseline: gate4-implementation
# Date: 2024-03-15
# Git tag: baseline/gate4-implementation
# Git commit: a1b2c3d4e5f6
# Phase: Gate 4 (Implementation)
# Contents:
# - Source code: 50 files, 10,000 lines
# - Unit tests: 150 tests, 100% coverage
# - Documentation: SRS v1.2, SAS v1.1, SDS v1.1
# Status: Approved by VMGR

# Compare two baselines
workspace.py wf diff-baseline gate3-design gate4-implementation
# Output:
# Differences between gate3-design and gate4-implementation:
# - Source code: +5,000 lines (implementation complete)
# - Unit tests: +150 tests (all modules covered)
# - Documentation: SDS updated from v1.0 to v1.1
# - Change requests: CR-050, CR-051, CR-052 (3 CRs closed)

# Track CR status
workspace.py wf show-cr CR-050
# Output:
# CR-050: Implement timeout handling
# Status: Closed
# Submitted: 2024-02-15
# Approved: 2024-02-20 (CCB)
# Implemented: 2024-03-10
# Verified: 2024-03-12 (VER)
# Closed: 2024-03-15 (Gate 4)
# Related commits: a1b2c3d, b2c3d4e, c3d4e5f, d4e5f6a
```

### 9.2 Git Command Integration

**Essential Git commands** for EN 50128 workflows:

```bash
# Repository Setup
git init                                # Initialize repository
git clone <url>                         # Clone remote repository
git remote add origin <url>             # Add remote

# Branch Management
git branch                              # List branches
git branch feature/REQ-42-timeout       # Create branch
git checkout -b feature/REQ-42-timeout  # Create and checkout
git checkout develop                    # Switch branch
git branch -d feature/REQ-42-timeout    # Delete local branch
git push origin --delete feature/REQ-42 # Delete remote branch

# Commit Management
git add src/timeout.c                   # Stage file
git commit -m "feat: Add timeout [REQ-42]"  # Commit
git commit --amend                      # Amend last commit (local only!)
git revert a1b2c3d                      # Revert commit (safe)

# Synchronization
git fetch origin                        # Fetch remote changes
git pull origin develop                 # Fetch and merge
git push origin feature/REQ-42          # Push to remote

# Merge Management
git merge --no-ff feature/REQ-42        # Merge with merge commit
git merge --squash feature/REQ-42       # Squash merge
git merge --abort                       # Abort merge (if conflicts)

# Tag Management
git tag v1.0.0                          # Create lightweight tag
git tag -a v1.0.0 -m "Release v1.0.0"   # Create annotated tag
git tag -s v1.0.0 -m "Release v1.0.0"   # Create signed tag
git push origin v1.0.0                  # Push tag to remote
git push origin --tags                  # Push all tags

# History and Inspection
git log                                 # Show commit history
git log --oneline                       # Compact history
git log --graph --all                   # Graphical history
git log v0.9.0..v1.0.0                  # Commits between tags
git show a1b2c3d                        # Show commit details
git diff develop feature/REQ-42         # Diff between branches
git blame src/timeout.c                 # Show line-by-line authors

# Traceability Queries
git log --grep="REQ-42"                 # Find commits for REQ-42
git log --grep="CR-050"                 # Find commits for CR-050
git log --all --source --full-history -S "timeout_init"  # Find when function added

# Status and Inspection
git status                              # Working directory status
git diff                                # Unstaged changes
git diff --staged                       # Staged changes
git show HEAD                           # Show last commit
```

### 9.3 Pre-commit Hooks

**Pre-commit hooks** enforce code quality before commit:

```bash
# Install pre-commit framework (Python)
pip3 install pre-commit

# Create .pre-commit-config.yaml
cat > .pre-commit-config.yaml << 'EOF'
repos:
  - repo: https://github.com/pre-commit/pre-commit-hooks
    rev: v4.4.0
    hooks:
      - id: trailing-whitespace
      - id: end-of-file-fixer
      - id: check-yaml
      - id: check-added-large-files
        args: ['--maxkb=500']
  
  - repo: local
    hooks:
      - id: misra-check
        name: MISRA C Check
        entry: python3 tools/check_misra.py
        language: system
        files: \.(c|h)$
      
      - id: complexity-check
        name: Complexity Check (CCN ≤ 10)
        entry: bash -c 'lizard -l c -C 10 -w'
        language: system
        files: \.(c|h)$
      
      - id: commit-msg-format
        name: Commit Message Format
        entry: python3 tools/verify_commit_msg.py
        language: system
        stages: [commit-msg]
EOF

# Install hooks
pre-commit install
pre-commit install --hook-type commit-msg

# Run manually
pre-commit run --all-files
```

---

## 10. Automation Scripts

### 10.1 Git Hooks

**Commit Message Validation Hook** (`.git/hooks/commit-msg`):

```bash
#!/bin/bash
# .git/hooks/commit-msg
# Validates commit message format for EN 50128 compliance

COMMIT_MSG_FILE=$1
COMMIT_MSG=$(cat "$COMMIT_MSG_FILE")

# Configuration (adjust for SIL level)
SIL_LEVEL=3
REQUIRE_CR_REF=true  # MANDATORY SIL 3-4
REQUIRE_GPG_SIG=true # MANDATORY SIL 3-4

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Check commit message format: type(scope): subject [REQ/CR-XX]
if ! echo "$COMMIT_MSG" | head -1 | grep -qE "^(feat|fix|docs|test|refactor|perf|chore|revert)(\(.+\))?!?: .+ \[(REQ|CR)-[0-9]+\]"; then
    echo -e "${RED}ERROR: Commit message does not match format${NC}"
    echo ""
    echo "Expected format:"
    echo "  type(scope): subject [REQ-XX or CR-XX]"
    echo ""
    echo "  <detailed body>"
    echo ""
    echo "  [CR-XX] Change request reference"
    echo ""
    echo "Types: feat, fix, docs, test, refactor, perf, chore, revert"
    echo "Example: feat(timeout): Implement timeout detection [REQ-42]"
    echo ""
    exit 1
fi

# Check CR reference in footer (MANDATORY SIL 3-4)
if [ "$REQUIRE_CR_REF" = true ] && [ "$SIL_LEVEL" -ge 3 ]; then
    if ! echo "$COMMIT_MSG" | grep -qE "\[CR-[0-9]+\]"; then
        echo -e "${RED}ERROR: Missing CR reference in footer (MANDATORY SIL 3-4)${NC}"
        echo ""
        echo "Add CR reference at end of commit message:"
        echo "  [CR-XX] Change request description"
        echo ""
        exit 1
    fi
fi

# Check GPG signature (MANDATORY SIL 3-4)
if [ "$REQUIRE_GPG_SIG" = true ] && [ "$SIL_LEVEL" -ge 3 ]; then
    # Note: This check runs pre-commit, so signature not yet applied
    # Instead, check GPG configuration
    if ! git config --get commit.gpgsign | grep -q "true"; then
        echo -e "${YELLOW}WARNING: GPG signing not enabled (MANDATORY SIL 3-4)${NC}"
        echo "Enable with: git config commit.gpgsign true"
        echo ""
    fi
fi

# Check subject line length (≤72 characters)
SUBJECT_LINE=$(echo "$COMMIT_MSG" | head -1)
SUBJECT_LENGTH=${#SUBJECT_LINE}
if [ "$SUBJECT_LENGTH" -gt 72 ]; then
    echo -e "${YELLOW}WARNING: Subject line too long ($SUBJECT_LENGTH > 72 chars)${NC}"
    echo "Consider shortening to ≤72 characters"
    echo ""
fi

# Check body present for non-trivial commits (SIL 3-4)
if [ "$SIL_LEVEL" -ge 3 ]; then
    LINE_COUNT=$(echo "$COMMIT_MSG" | wc -l)
    if [ "$LINE_COUNT" -lt 5 ]; then
        echo -e "${YELLOW}WARNING: Commit message body recommended for SIL 3-4${NC}"
        echo "Include rationale, testing, EN 50128 references"
        echo ""
    fi
fi

echo -e "${GREEN}✅ Commit message format valid${NC}"
exit 0
```

**Pre-commit Hook** (`.git/hooks/pre-commit`):

```bash
#!/bin/bash
# .git/hooks/pre-commit
# Runs checks before allowing commit

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo "Running pre-commit checks..."

# Check 1: No debug code
if git diff --cached | grep -E "(printf|fprintf|TODO|FIXME|XXX)"; then
    echo -e "${YELLOW}WARNING: Debug code or TODOs found${NC}"
    echo "Remove or justify before committing"
    # Allow commit but warn (change to exit 1 to block)
fi

# Check 2: No trailing whitespace
if git diff --cached --check; then
    echo -e "${GREEN}✅ No trailing whitespace${NC}"
else
    echo -e "${RED}ERROR: Trailing whitespace found${NC}"
    echo "Fix with: git diff --cached --check"
    exit 1
fi

# Check 3: MISRA C compliance (C files only)
C_FILES=$(git diff --cached --name-only --diff-filter=ACM | grep -E '\.(c|h)$')
if [ -n "$C_FILES" ]; then
    echo "Checking MISRA C compliance..."
    if python3 tools/check_misra.py $C_FILES; then
        echo -e "${GREEN}✅ MISRA C compliant${NC}"
    else
        echo -e "${RED}ERROR: MISRA C violations found${NC}"
        echo "Fix violations before committing (MANDATORY SIL 3-4)"
        exit 1
    fi
fi

# Check 4: Complexity check (C files only)
if [ -n "$C_FILES" ]; then
    echo "Checking cyclomatic complexity..."
    if lizard -l c -C 10 -w $C_FILES; then
        echo -e "${GREEN}✅ Complexity within limits (≤10)${NC}"
    else
        echo -e "${RED}ERROR: Complexity exceeds limit (≤10 for SIL 3-4)${NC}"
        echo "Refactor functions to reduce complexity"
        exit 1
    fi
fi

# Check 5: No large files (>500 KB)
LARGE_FILES=$(git diff --cached --name-only --diff-filter=ACM | xargs -I {} du -k {} | awk '$1 > 500 {print $2}')
if [ -n "$LARGE_FILES" ]; then
    echo -e "${RED}ERROR: Large files found (>500 KB)${NC}"
    echo "$LARGE_FILES"
    echo "Use Git LFS for large binary files"
    exit 1
fi

echo -e "${GREEN}✅ All pre-commit checks passed${NC}"
exit 0
```

**Make hooks executable**:

```bash
chmod +x .git/hooks/commit-msg
chmod +x .git/hooks/pre-commit
```

### 10.2 Commit Message Validator Script

**`tools/verify_commit_msg.py`**:

```python
#!/usr/bin/env python3
"""
Verify commit message format for EN 50128 compliance.

Usage:
    python3 verify_commit_msg.py < commit_message.txt
    git log -1 --pretty=%B | python3 verify_commit_msg.py
"""

import sys
import re

# Configuration (adjust for SIL level)
SIL_LEVEL = 3
REQUIRE_CR_REF = SIL_LEVEL >= 3
REQUIRE_BODY = SIL_LEVEL >= 3

def main():
    # Read commit message from stdin
    commit_msg = sys.stdin.read()
    
    lines = commit_msg.strip().split('\n')
    if not lines:
        print("ERROR: Empty commit message")
        return 1
    
    subject = lines[0]
    body = '\n'.join(lines[2:]) if len(lines) > 2 else ""
    
    # Check subject line format: type(scope): subject [REQ/CR-XX]
    subject_pattern = r'^(feat|fix|docs|test|refactor|perf|chore|revert)(\(.+\))?!?: .+ \[(REQ|CR)-[0-9]+\]$'
    if not re.match(subject_pattern, subject):
        print("ERROR: Subject line does not match format")
        print("")
        print("Expected: type(scope): subject [REQ-XX or CR-XX]")
        print("Examples:")
        print("  feat(timeout): Implement timeout detection [REQ-42]")
        print("  fix(uart): Correct baud rate calculation [CR-123]")
        print("")
        return 1
    
    # Check subject length (≤72 characters)
    if len(subject) > 72:
        print(f"WARNING: Subject line too long ({len(subject)} > 72 chars)")
    
    # Check CR reference in footer (MANDATORY SIL 3-4)
    if REQUIRE_CR_REF:
        if not re.search(r'\[CR-[0-9]+\]', commit_msg):
            print("ERROR: Missing CR reference in footer (MANDATORY SIL 3-4)")
            print("Add: [CR-XX] Change request description")
            return 1
    
    # Check body present (SIL 3-4)
    if REQUIRE_BODY and len(lines) < 5:
        print("WARNING: Commit message body recommended for SIL 3-4")
        print("Include rationale, testing, EN 50128 references")
    
    print("✅ Commit message format valid")
    return 0

if __name__ == '__main__':
    sys.exit(main())
```

---

## 11. Example Scenarios

### 11.1 Scenario 1: SIL 3 Project - Initial Setup

**Context**: Starting a new SIL 3 railway software project. Need to set up Git repository with EN 50128-compliant version control.

**Steps**:

```bash
# Step 1: Create repository
mkdir railway-project-sil3
cd railway-project-sil3
git init
git config init.defaultBranch main

# Step 2: Configure user identity
git config user.name "John Doe"
git config user.email "john.doe@railway-company.com"

# Step 3: Enable GPG signing (MANDATORY SIL 3)
git config commit.gpgsign true
git config tag.gpgsign true
git config user.signingkey 0x12345678ABCDEF

# Step 4: Configure repository settings
git config core.fsyncMethod fsync
git config core.fsync committed
git config merge.ff false
git config receive.denyNonFastForwards true

# Step 5: Create .gitignore
cat > .gitignore << 'EOF'
# Build outputs
build/
*.o
*.elf
*.bin
*.map

# Coverage
*.gcda
*.gcno
coverage/*.info
coverage/html/

# IDE
.vscode/
*.swp

# Secrets
.env
*.key
EOF

# Step 6: Create .gitattributes
cat > .gitattributes << 'EOF'
* text=auto
*.sh text eol=lf
*.py text eol=lf
Makefile text eol=lf
*.bin binary
*.elf binary
*.o binary
*.pdf filter=lfs diff=lfs merge=lfs -text
EOF

# Step 7: Create initial structure
mkdir -p src include tests/{integration,system} docs/{requirements,design,verification,validation} plans tools
touch README.md CHANGELOG.md BRANCH_STRUCTURE.md LIFECYCLE_STATE.md

# Step 8: Create README.md
cat > README.md << 'EOF'
# Railway Safety System - SIL 3

EN 50128-compliant railway safety software.

## Overview
Safety-critical control system for railway signaling.

## SIL Level
SIL 3 (Safety Integrity Level 3)

## Development Language
C (MISRA C:2012 compliant)

## Version Control
Git-based configuration management following EN 50128 Section 6.6.

## Build
```
make all
make test
make coverage
```

## Documentation
- Requirements: `docs/requirements/SRS-v1.0.md`
- Architecture: `docs/design/SAS-v1.0.md`
- Design: `docs/design/SDS-v1.0.md`

## Contact
john.doe@railway-company.com
EOF

# Step 9: Initial commit
git add .
git commit -m "chore: Initialize SIL 3 railway safety project [CR-001]

Initial repository setup for EN 50128-compliant development.

Configuration:
- Git repository with GPG signing enabled
- MISRA C:2012 compliance enforced
- SIL 3 quality requirements
- Defensive programming mandatory
- Complexity limit: CCN ≤ 10

Directory structure:
- src/: Source code (C)
- include/: Public headers
- tests/: Unit, integration, system tests
- docs/: Requirements, design, verification, validation
- plans/: SQAP, SCMP, SVP, SVaP
- tools/: Build and analysis tools

EN 50128 References:
- Section 6.6: Software Configuration Management
- Table A.9 #5: Configuration Management (MANDATORY ALL SIL)

[CR-001] Initial repository setup
Approved-by: Project Manager
" --signoff

# Step 10: Install Git hooks
cp tools/git-hooks/pre-commit .git/hooks/pre-commit
cp tools/git-hooks/commit-msg .git/hooks/commit-msg
chmod +x .git/hooks/pre-commit .git/hooks/commit-msg

# Step 11: Create develop branch
git checkout -b develop
git push -u origin develop

# Step 12: Configure remote repository (GitHub)
# (Manually enable branch protection via GitHub UI)
# - main: Require 2 reviews, require VER approval, signed commits
# - develop: Require 1 review, signed commits

# Step 13: Create first feature branch
git checkout -b feature/REQ-01-system-init

# Ready for development!
```

### 11.2 Scenario 2: Feature Development with Full Workflow

**Context**: Implement a new feature (timeout handling) for SIL 3 project. Follow complete workflow from branch creation to merge.

**Steps**:

```bash
# Step 1: Create feature branch from develop
git checkout develop
git pull origin develop
git checkout -b feature/REQ-42-timeout-handling

# Step 2: Implement feature (multiple commits)

# Commit 1: Add timeout module header
cat > include/timeout.h << 'EOF'
#ifndef TIMEOUT_H
#define TIMEOUT_H

#include <stdint.h>
#include <stdbool.h>

typedef void (*timeout_callback_t)(uint8_t sensor_id);

void timeout_init(uint8_t sensor_id, uint32_t threshold_ms, timeout_callback_t callback);
bool timeout_check(uint8_t sensor_id, uint32_t elapsed_ms);
void timeout_reset(uint8_t sensor_id);

#endif /* TIMEOUT_H */
EOF

git add include/timeout.h
git commit -m "feat(timeout): Add timeout module interface [REQ-42]

Define timeout detection API for sensor monitoring.

Interface:
- timeout_init(): Initialize timeout for sensor
- timeout_check(): Check if timeout occurred
- timeout_reset(): Reset timeout counter

EN 50128 Compliance:
- REQ-42: Detect sensor timeout within 100ms
- Defensive programming: All pointers validated
- MISRA C:2012 compliant

[CR-050] Timeout module interface
" --signoff

# Commit 2: Implement timeout module
cat > src/timeout.c << 'EOF'
#include "timeout.h"
#include <stddef.h>

#define MAX_SENSORS 4

typedef struct {
    uint32_t threshold_ms;
    uint32_t elapsed_ms;
    timeout_callback_t callback;
    bool active;
} timeout_state_t;

static timeout_state_t timeouts[MAX_SENSORS];

void timeout_init(uint8_t sensor_id, uint32_t threshold_ms, timeout_callback_t callback) {
    if (sensor_id >= MAX_SENSORS) return;  /* Bounds check */
    if (callback == NULL) return;          /* NULL check */
    
    timeouts[sensor_id].threshold_ms = threshold_ms;
    timeouts[sensor_id].elapsed_ms = 0;
    timeouts[sensor_id].callback = callback;
    timeouts[sensor_id].active = true;
}

bool timeout_check(uint8_t sensor_id, uint32_t elapsed_ms) {
    if (sensor_id >= MAX_SENSORS) return false;
    if (!timeouts[sensor_id].active) return false;
    
    timeouts[sensor_id].elapsed_ms += elapsed_ms;
    
    if (timeouts[sensor_id].elapsed_ms >= timeouts[sensor_id].threshold_ms) {
        timeouts[sensor_id].callback(sensor_id);
        return true;
    }
    
    return false;
}

void timeout_reset(uint8_t sensor_id) {
    if (sensor_id >= MAX_SENSORS) return;
    timeouts[sensor_id].elapsed_ms = 0;
}
EOF

git add src/timeout.c
git commit -m "feat(timeout): Implement timeout detection logic [REQ-42]

Implement timeout monitoring with configurable threshold
and callback notification.

Implementation:
- Static array for up to 4 sensors
- Elapsed time accumulation
- Threshold comparison with callback trigger
- Reset functionality

EN 50128 Compliance:
- Defensive programming: Bounds checks, NULL checks
- Static allocation only (no malloc)
- MISRA C:2012 compliant
- Cyclomatic complexity: 3 (well within SIL 3 limit of 10)

Testing: Unit tests added separately

[CR-050] Timeout detection implementation
Refs: REQ-42
" --signoff

# Commit 3: Add unit tests
cat > tests/unit_test_timeout.c << 'EOF'
#include "unity.h"
#include "timeout.h"

static bool timeout_triggered;
static uint8_t timeout_sensor_id;

void timeout_callback(uint8_t sensor_id) {
    timeout_triggered = true;
    timeout_sensor_id = sensor_id;
}

void setUp(void) {
    timeout_triggered = false;
    timeout_sensor_id = 0xFF;
}

void tearDown(void) {}

void test_timeout_init(void) {
    timeout_init(0, 1000, timeout_callback);
    TEST_PASS();
}

void test_timeout_not_triggered(void) {
    timeout_init(0, 1000, timeout_callback);
    timeout_check(0, 500);
    TEST_ASSERT_FALSE(timeout_triggered);
}

void test_timeout_triggered(void) {
    timeout_init(0, 1000, timeout_callback);
    timeout_check(0, 1000);
    TEST_ASSERT_TRUE(timeout_triggered);
    TEST_ASSERT_EQUAL(0, timeout_sensor_id);
}

void test_timeout_reset(void) {
    timeout_init(0, 1000, timeout_callback);
    timeout_check(0, 500);
    timeout_reset(0);
    timeout_check(0, 500);
    TEST_ASSERT_FALSE(timeout_triggered);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_timeout_init);
    RUN_TEST(test_timeout_not_triggered);
    RUN_TEST(test_timeout_triggered);
    RUN_TEST(test_timeout_reset);
    return UNITY_END();
}
EOF

git add tests/unit_test_timeout.c
git commit -m "test(timeout): Add unit tests with 100% coverage [REQ-42]

Add comprehensive unit tests for timeout module.

Tests:
- test_timeout_init: Initialization
- test_timeout_not_triggered: Timeout not reached
- test_timeout_triggered: Timeout reached, callback invoked
- test_timeout_reset: Reset functionality

Coverage:
- Statement: 100% (all lines executed)
- Branch: 100% (all branches taken)
- Condition: 100% (all conditions tested)

EN 50128 Compliance:
- Table A.21: 100% coverage MANDATORY SIL 3-4
- Unit testing: MANDATORY SIL 3-4

[CR-050] Timeout unit tests
Refs: REQ-42
" --signoff

# Step 3: Build and test locally
make clean
make all
make test

# Check coverage
make coverage
lcov --capture --directory . --output-file coverage.info
lcov --list coverage.info
# Expected: 100% statement, branch, condition for timeout.c

# Step 4: Run static analysis
cppcheck --enable=all src/timeout.c
scan-build make

# Step 5: Check complexity
lizard -l c src/timeout.c
# Expected: All functions ≤10 CCN

# Step 6: Push feature branch
git push -u origin feature/REQ-42-timeout-handling

# Step 7: Create pull request (via GitHub UI)
# Title: [REQ-42] Implement timeout handling
# Description:
#   Implement sensor timeout detection per REQ-42.
#   
#   Requirements:
#   - REQ-42: System shall detect sensor timeout within 100ms
#   
#   Changes:
#   - Add timeout module (timeout.h, timeout.c)
#   - Add unit tests (100% coverage)
#   - MISRA C compliant, complexity ≤10
#   
#   Testing:
#   - 15 unit tests, 100% pass
#   - Coverage: 100% statement, branch, condition
#   - Static analysis: Clean (Cppcheck, Clang)
#   
#   Reviewers: @jane-ver (VER), @john-imp (IMP)
#   CR-050

# Step 8: Wait for review and CI
# CI pipeline runs automatically:
# - Build: ✅ SUCCESS
# - Tests: ✅ 15/15 PASS
# - Coverage: ✅ 100% statement, 100% branch, 100% condition
# - Static analysis: ✅ 0 issues
# - Complexity: ✅ All functions ≤10 CCN
# - Traceability: ✅ PASS

# Reviewers provide feedback:
# @jane-ver: "LGTM, complexity good, defensive programming applied. One comment: add overflow check for elapsed_ms accumulation."
# @john-imp: "Looks good. Tests are comprehensive."

# Step 9: Address review feedback
# Edit src/timeout.c: Add overflow check
git add src/timeout.c
git commit -m "fix(timeout): Add overflow check for elapsed time [REQ-42]

Address review feedback: Add overflow protection for elapsed_ms
accumulation to prevent integer overflow.

Changes:
- Check for overflow before adding elapsed_ms
- Return false if overflow would occur (conservative)

Testing:
- Added unit test: test_timeout_overflow
- All tests pass, coverage still 100%

[CR-050] Review feedback - overflow check
Reviewed-by: Jane Smith (VER)
" --signoff

git push

# Step 10: After ≥2 approvals and CI pass, merge via GitHub UI
# Merge method: "Create a merge commit" (recommended for SIL 3)

# Step 11: Sync local branches
git checkout develop
git pull origin develop

# Step 12: Delete feature branch
git branch -d feature/REQ-42-timeout-handling
git push origin --delete feature/REQ-42-timeout-handling

# Step 13: Update traceability
workspace.py trace validate-ci --fix
# Output: ✅ Traceability updated with 3 new commits for REQ-42

# Step 14: Update requirements document
# (Edit docs/requirements/SRS-v1.2.md: Mark REQ-42 as implemented)
git add docs/requirements/SRS-v1.2.md docs/requirements/RTM-v1.2.md
git commit -m "docs(requirements): Mark REQ-42 implemented [REQ-42]

Update SRS and RTM to reflect REQ-42 implementation.

Changes:
- SRS: Mark REQ-42 status = Implemented
- RTM: Add commits a1b2c3d, b2c3d4e, c3d4e5f

[CR-050] Requirements documentation update
" --signoff

git push origin develop

# Feature complete!
```

---

## Summary

This **Version Control Workflow** provides comprehensive guidance for Git-based configuration management in EN 50128-compliant railway software development.

**Key Takeaways**:
1. **Version control is MANDATORY for ALL SIL levels** (EN 50128 Table A.9 #5)
2. **Git branching strategy** adapted for EN 50128 V-Model (feature, bugfix, hotfix, release branches)
3. **Commit conventions** enforce traceability (CR references, GPG signatures for SIL 3-4)
4. **Merge policies** preserve complete history (merge commit recommended for SIL 3-4)
5. **Tag management** for baselines at phase gates (semantic versioning for releases)
6. **CI integration** automates verification (build, test, coverage, static analysis, traceability)
7. **Tool integration** with `workspace.py` for traceability and workflow management
8. **Automation scripts** (Git hooks) enforce quality and compliance before commit

**Related Workflows**:
- **WF-CM-002**: Change Control Workflow (CR process, CCB, impact analysis)
- **WF-CM-003**: Baseline Management Workflow (PCA/FCA audits, baseline control)
- **WF-CM-004**: Configuration Status Accounting (CI tracking, metrics)

**EN 50128 Compliance**:
- ✅ Section 6.6: Software Configuration Management
- ✅ Table A.9 #5: Software Configuration Management (MANDATORY ALL SIL)
- ✅ Table A.9 #7: Traceability (MANDATORY SIL 3-4)
- ✅ Table A.9 #8: Data Recording and Analysis (MANDATORY SIL 3-4)
- ✅ Reference D.48: Software Configuration Management detailed requirements

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

*End of Version Control Workflow (WF-CM-001)*
