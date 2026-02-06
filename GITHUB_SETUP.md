# GitHub Setup Instructions for opencode-en50128

## Overview

This document provides step-by-step instructions to push the EN 50128 Railway Software Development Framework to GitHub as a **private repository** named `opencode-en50128`.

## Prerequisites

- Git installed and configured
- GitHub account with access to create private repositories
- GitHub CLI (`gh`) installed (recommended but optional)
- SSH keys configured with GitHub (or use HTTPS with token)

## Current Status

✅ **Repository Initialized**: Local Git repository created  
✅ **Initial Commit Created**: All files committed  
✅ **Branch**: `main`  
✅ **Commit**: `219401d` - Initial EN 50128 framework

**Files committed**: 38 files, 13,116 lines  
**Repository location**: `/home/norechang/work/EN50128`

---

## Option 1: Using GitHub CLI (Recommended)

### Step 1: Install GitHub CLI (if not installed)

```bash
# On Ubuntu/Debian
sudo apt install gh

# On macOS
brew install gh

# On other systems, see: https://cli.github.com/
```

### Step 2: Authenticate with GitHub

```bash
gh auth login
```

Follow the prompts:
- Choose: **GitHub.com**
- Protocol: **HTTPS** or **SSH** (your preference)
- Authenticate: **Login with web browser** (or paste token)

### Step 3: Create Private Repository and Push

```bash
cd /home/norechang/work/EN50128

# Create private repository on GitHub and push
gh repo create opencode-en50128 \
  --private \
  --source=. \
  --remote=origin \
  --push \
  --description="EN 50128 Railway Software Development Framework - Role-based agents for OpenCode"

# Verify
gh repo view
```

**Done!** Repository is created and pushed to GitHub.

### Step 4: Set Default Branch (if needed)

```bash
# If GitHub created 'master' instead of 'main'
gh repo edit --default-branch main
```

---

## Option 2: Using GitHub Web Interface + Git Commands

### Step 1: Create Repository on GitHub

1. Go to https://github.com/new
2. Fill in repository details:
   - **Repository name**: `opencode-en50128`
   - **Description**: EN 50128 Railway Software Development Framework - Role-based agents for OpenCode
   - **Visibility**: ☑️ **Private**
   - **Initialize repository**: ⬜ **Do NOT check any boxes** (we already have local repo)

3. Click **"Create repository"**

### Step 2: Copy Repository URL

GitHub will show you the repository URL. Copy one of:
- **HTTPS**: `https://github.com/YOUR_USERNAME/opencode-en50128.git`
- **SSH**: `git@github.com:YOUR_USERNAME/opencode-en50128.git`

Replace `YOUR_USERNAME` with your actual GitHub username.

### Step 3: Add Remote and Push

```bash
cd /home/norechang/work/EN50128

# Add GitHub as remote (choose HTTPS or SSH)

# Option A: HTTPS
git remote add origin https://github.com/YOUR_USERNAME/opencode-en50128.git

# Option B: SSH (if you have SSH keys configured)
git remote add origin git@github.com:YOUR_USERNAME/opencode-en50128.git

# Verify remote
git remote -v

# Push to GitHub
git push -u origin main
```

**Done!** Your repository is now on GitHub.

---

## Option 3: Using Personal Access Token (PAT)

If you're using HTTPS and don't want to enter password every time:

### Step 1: Create Personal Access Token

1. Go to GitHub Settings: https://github.com/settings/tokens
2. Click **"Generate new token"** → **"Generate new token (classic)"**
3. Fill in:
   - **Note**: `opencode-en50128 access`
   - **Expiration**: Choose duration (90 days, 1 year, etc.)
   - **Scopes**: Select:
     - ☑️ `repo` (full control of private repositories)
4. Click **"Generate token"**
5. **Copy the token** (you won't see it again!)

### Step 2: Create Repository and Push

```bash
cd /home/norechang/work/EN50128

# Add remote with token embedded (NOT recommended for shared systems)
# git remote add origin https://YOUR_TOKEN@github.com/YOUR_USERNAME/opencode-en50128.git

# Better: Use credential helper
git config credential.helper store

# Add remote
git remote add origin https://github.com/YOUR_USERNAME/opencode-en50128.git

# Push (will prompt for username and password - use token as password)
git push -u origin main

# Enter:
# Username: YOUR_USERNAME
# Password: YOUR_PERSONAL_ACCESS_TOKEN (paste the token)
```

---

## Verification Steps

After pushing, verify everything is correct:

### 1. Check GitHub Repository

```bash
# Open in browser (if using gh CLI)
gh repo view --web

# Or manually visit:
# https://github.com/YOUR_USERNAME/opencode-en50128
```

Verify:
- ✅ Repository is **private** (lock icon visible)
- ✅ All 38 files are present
- ✅ README.md is displayed
- ✅ Folder structure is intact:
  - `.opencode/commands/` (8 agent files)
  - `.opencode/skills/` (9 skill files)
  - `docs/` (documentation)
  - `tools/` (static analysis tools)

### 2. Check Repository Settings

```bash
# Using gh CLI
gh repo edit --enable-issues --enable-wiki=false

# Or manually:
# Go to Settings → General
# - Issues: Enabled
# - Wiki: Disabled
# - Projects: Disabled (optional)
```

### 3. Add Repository Topics (Optional)

```bash
gh repo edit --add-topic en50128,railway,safety-critical,misra-c,opencode,agents
```

Or manually add topics on GitHub:
- `en50128`
- `railway`
- `safety-critical`
- `misra-c`
- `opencode`
- `agents`
- `embedded-systems`
- `c-programming`

### 4. Protect Main Branch (Recommended)

```bash
# Require pull request reviews before merging
gh api repos/YOUR_USERNAME/opencode-en50128/branches/main/protection \
  --method PUT \
  --field required_status_checks=null \
  --field enforce_admins=true \
  --field required_pull_request_reviews='{"dismissal_restrictions":{},"dismiss_stale_reviews":false,"require_code_owner_reviews":false,"required_approving_review_count":1}'
```

Or manually:
1. Go to **Settings → Branches**
2. Click **"Add branch protection rule"**
3. Branch name pattern: `main`
4. Enable:
   - ☑️ Require pull request reviews before merging
   - ☑️ Require approvals: **1**
   - ☑️ Dismiss stale reviews
5. Click **"Create"**

---

## Adding Collaborators (For Team Access)

### Using GitHub CLI

```bash
gh repo set-permissions --add-user USERNAME --permission write
```

### Using Web Interface

1. Go to **Settings → Collaborators**
2. Click **"Add people"**
3. Enter username or email
4. Choose permission level:
   - **Read**: View only
   - **Write**: Push access
   - **Admin**: Full access

---

## Repository Badges (Optional)

Add badges to README.md for better visibility:

```markdown
# EN 50128 Railway Software Development Framework

[![License: Proprietary](https://img.shields.io/badge/License-Proprietary-red.svg)](LICENSE)
[![EN 50128:2011](https://img.shields.io/badge/EN%2050128-2011-blue.svg)](https://www.cenelec.eu/)
[![MISRA C:2012](https://img.shields.io/badge/MISRA%20C-2012-green.svg)](https://www.misra.org.uk/)
[![Private](https://img.shields.io/badge/Repository-Private-orange.svg)](https://github.com/YOUR_USERNAME/opencode-en50128)
```

---

## Post-Push Tasks

### 1. Update LICENSE File

Edit `LICENSE` file to include your organization name:

```bash
# Edit LICENSE file
nano LICENSE

# Replace placeholders:
# [Your Organization Name] → Your actual organization
# [legal@yourorganization.com] → Your contact email
# [Your Organization Address] → Your address

# Commit changes
git add LICENSE
git commit -m "docs: update license with organization details"
git push
```

### 2. Configure GitHub Actions (Optional)

Create CI/CD workflow for automated checks:

```bash
mkdir -p .github/workflows

cat > .github/workflows/verify.yml << 'EOF'
name: EN 50128 Verification

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main, develop ]

jobs:
  verify:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Set up Python
      uses: actions/setup-python@v4
      with:
        python-version: '3.10'
    
    - name: Install tools
      run: |
        sudo apt-get update
        sudo apt-get install -y cppcheck
        pip install lizard
    
    - name: Verify agent-skill links
      run: |
        bash tools/verify_links.sh
    
    - name: Check YAML frontmatter
      run: |
        python3 tools/validate_skills.py
    
    - name: Static analysis (if C code present)
      run: |
        if [ -d "src" ] && [ "$(find src -name '*.c')" ]; then
          cppcheck --addon=misra --enable=all src/
        fi
EOF

git add .github/workflows/verify.yml
git commit -m "ci: add GitHub Actions workflow for verification"
git push
```

### 3. Add Issue Templates (Optional)

```bash
mkdir -p .github/ISSUE_TEMPLATE

# Create bug report template
cat > .github/ISSUE_TEMPLATE/bug_report.md << 'EOF'
---
name: Bug report
about: Create a report to help us improve
title: '[BUG] '
labels: bug
assignees: ''
---

## Description
[Clear description of the bug]

## EN 50128 Context
- Agent: [REQ/DES/IMP/TST/SAF/VER/VAL/QUA]
- SIL Level: [0/1/2/3/4]
- Standard Section: [EN 50128 section reference]

## Steps to Reproduce
1. 
2. 
3. 

## Expected Behavior
[What should happen]

## Actual Behavior
[What actually happens]

## Environment
- OpenCode version:
- OS:
- Compiler (if relevant):

## Safety Impact
[Any safety implications]
EOF

# Create feature request template
cat > .github/ISSUE_TEMPLATE/feature_request.md << 'EOF'
---
name: Feature request
about: Suggest an enhancement
title: '[FEATURE] '
labels: enhancement
assignees: ''
---

## Description
[Clear description of the feature]

## Motivation
[Why this feature is needed]

## EN 50128 Compliance
- Affects SIL: [0/1/2/3/4]
- Standard section: [EN 50128 reference]
- Safety impact: [None/Low/Medium/High]

## Proposed Solution
[How this could be implemented]

## Alternatives Considered
[Other approaches considered]
EOF

git add .github/ISSUE_TEMPLATE/
git commit -m "docs: add issue templates"
git push
```

---

## Troubleshooting

### Issue: "Permission denied (publickey)"

**Solution**: SSH keys not configured. Either:

**Option A**: Use HTTPS instead
```bash
git remote set-url origin https://github.com/YOUR_USERNAME/opencode-en50128.git
```

**Option B**: Add SSH key to GitHub
```bash
ssh-keygen -t ed25519 -C "your_email@example.com"
cat ~/.ssh/id_ed25519.pub
# Copy the output and add to GitHub: Settings → SSH and GPG keys
```

### Issue: "Repository not found"

**Causes**:
- Repository doesn't exist yet
- Wrong repository name
- No access permissions

**Solution**:
1. Verify repository exists: `gh repo view YOUR_USERNAME/opencode-en50128`
2. Check spelling of repository name
3. Verify you have access (if organization repo)

### Issue: "Updates were rejected"

**Cause**: Remote has changes you don't have locally

**Solution**:
```bash
git pull --rebase origin main
git push origin main
```

### Issue: "Large files detected"

**Cause**: Standard PDFs might be too large

**Solution**: Already handled by `.gitignore` - PDF files in `std/` are excluded.

---

## Next Steps

After pushing to GitHub:

1. **✅ Share repository URL** with team members
2. **✅ Set up branch protection rules** (if working in team)
3. **✅ Add collaborators** with appropriate permissions
4. **✅ Configure integrations** (Slack, Discord notifications)
5. **✅ Set up project board** (optional, for task tracking)
6. **✅ Enable security alerts** (Settings → Security)

---

## Repository Information

**Repository Name**: `opencode-en50128`  
**Visibility**: Private  
**Default Branch**: `main`  
**Initial Commit**: `219401d`  
**Files**: 38 files, 13,116 lines  
**License**: Proprietary  

**Contents**:
- 8 EN 50128 agent commands
- 9 domain-specific skills
- Complete documentation
- Static analysis tools
- Project structure

**Standards**:
- EN 50128:2011
- EN 50126:2017
- MISRA C:2012
- IEC 61508

---

## Quick Reference Commands

```bash
# View repository info
gh repo view
gh repo view --web

# Check status
git status
git log --oneline -5

# Push changes
git add -A
git commit -m "feat: description"
git push

# Pull updates
git pull

# Create new branch
git checkout -b feature/new-feature
git push -u origin feature/new-feature

# View remotes
git remote -v
```

---

## Support

For questions or issues:
- **GitHub Issues**: Create issue in repository
- **Email**: [Your contact email]
- **Documentation**: See `/docs` directory

---

**Repository URL** (after creation):  
`https://github.com/YOUR_USERNAME/opencode-en50128`

**SSH URL**:  
`git@github.com:YOUR_USERNAME/opencode-en50128.git`

---

*Last updated: 2026-02-06*  
*Version: 1.0.0*
