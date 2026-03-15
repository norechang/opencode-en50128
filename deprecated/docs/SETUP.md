# EN 50128 Development Environment Setup Guide

**Purpose**: Install and configure tools for EN 50128-compliant railway software development  
**Target Platform**: Linux (Ubuntu 20.04+), macOS, Windows (WSL2)  
**Estimated Time**: 30-60 minutes

---

## Overview

This guide will help you set up a complete development environment for EN 50128:2011 compliant railway software development in C.

### Tools Covered

1. **GCC** - GNU Compiler Collection (C11 standard)
2. **Unity** - Unit testing framework for C
3. **gcov/lcov** - Code coverage analysis
4. **Cppcheck** - Static analysis tool
5. **Lizard** - Cyclomatic complexity analyzer
6. **Git** - Version control
7. **Make** - Build automation
8. **PC-lint Plus** (Optional) - Commercial MISRA C checker

---

## Prerequisites

### Minimum System Requirements

- **OS**: Linux (Ubuntu 20.04+), macOS 11+, or Windows 10/11 with WSL2
- **RAM**: 4 GB minimum, 8 GB recommended
- **Disk**: 2 GB free space
- **Network**: Internet connection for package downloads

### Required Knowledge

- Basic command-line usage
- Basic C programming
- Basic Git operations

---

## Installation Steps

### 1. Install Base Development Tools

#### Ubuntu/Debian Linux

```bash
# Update package list
sudo apt update

# Install essential build tools
sudo apt install -y \
    build-essential \
    gcc \
    g++ \
    make \
    git \
    cmake \
    python3 \
    python3-pip

# Verify installation
gcc --version      # Should show GCC 9.0+
make --version     # Should show GNU Make 4.0+
git --version      # Should show Git 2.0+
python3 --version  # Should show Python 3.8+
```

#### macOS

```bash
# Install Xcode Command Line Tools
xcode-select --install

# Install Homebrew (if not already installed)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install development tools
brew install gcc make git cmake python3

# Verify installation
gcc --version
make --version
git --version
python3 --version
```

#### Windows (WSL2)

```powershell
# Enable WSL2 (PowerShell as Administrator)
wsl --install -d Ubuntu-22.04

# Launch Ubuntu and follow Linux instructions above
```

---

### 2. Install Unity Test Framework

Unity is a lightweight unit testing framework for C.

#### Method 1: Clone from GitHub (Recommended)

```bash
# Clone Unity repository
cd ~/
git clone https://github.com/ThrowTheSwitch/Unity.git

# Set environment variable (add to ~/.bashrc or ~/.zshrc)
export UNITY_ROOT=~/Unity
echo 'export UNITY_ROOT=~/Unity' >> ~/.bashrc
source ~/.bashrc

# Verify installation
ls $UNITY_ROOT/src/unity.c
# Should show: /home/username/Unity/src/unity.c
```

#### Method 2: Install in Project (Alternative)

```bash
# Navigate to your project
cd /path/to/your/project

# Create test directory structure
mkdir -p test/unity

# Download Unity files
cd test/unity
wget https://raw.githubusercontent.com/ThrowTheSwitch/Unity/master/src/unity.c
wget https://raw.githubusercontent.com/ThrowTheSwitch/Unity/master/src/unity.h
wget https://raw.githubusercontent.com/ThrowTheSwitch/Unity/master/src/unity_internals.h

cd ../..
```

#### Verify Unity Installation

Create a simple test:

```bash
# Create test file
cat > test_example.c << 'EOF'
#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_example(void) {
    TEST_ASSERT_EQUAL(1, 1);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_example);
    return UNITY_END();
}
EOF

# Compile and run
gcc -I$UNITY_ROOT/src test_example.c $UNITY_ROOT/src/unity.c -o test_example
./test_example

# Expected output:
# test_example.c:8:test_example:PASS
# 1 Tests 0 Failures 0 Ignored
# OK

# Clean up
rm test_example.c test_example
```

---

### 3. Install gcov and lcov (Coverage Tools)

gcov is included with GCC. Install lcov for HTML reports.

#### Ubuntu/Debian

```bash
sudo apt install -y lcov

# Verify installation
lcov --version
# Should show: lcov: LCOV version 1.14+
```

#### macOS

```bash
brew install lcov

# Verify installation
lcov --version
```

#### Test Coverage Tools

```bash
# Create a simple C program
cat > example.c << 'EOF'
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main(void) {
    printf("2 + 3 = %d\n", add(2, 3));
    return 0;
}
EOF

# Compile with coverage flags
gcc -fprofile-arcs -ftest-coverage example.c -o example

# Run program (generates .gcda files)
./example

# Generate coverage report
gcov example.c

# Check coverage
cat example.c.gcov
# Should show execution counts for each line

# Generate HTML report with lcov
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_html

# View HTML report
xdg-open coverage_html/index.html  # Linux
open coverage_html/index.html      # macOS

# Clean up
rm example example.c *.gcov *.gcda *.gcno coverage.info
rm -rf coverage_html
```

---

### 4. Install Cppcheck (Static Analysis)

Cppcheck is a static analysis tool for C/C++.

#### Ubuntu/Debian

```bash
sudo apt install -y cppcheck

# Verify installation
cppcheck --version
# Should show: Cppcheck 2.0+
```

#### macOS

```bash
brew install cppcheck

# Verify installation
cppcheck --version
```

#### Test Cppcheck

```bash
# Create a simple C file with intentional issues
cat > example_bad.c << 'EOF'
#include <stdio.h>

int main(void) {
    int x;  // Uninitialized variable
    printf("%d\n", x);
    return 0;
}
EOF

# Run Cppcheck
cppcheck --enable=all --error-exitcode=1 example_bad.c

# Expected output:
# [example_bad.c:5]: (error) Uninitialized variable: x

# Clean up
rm example_bad.c
```

---

### 5. Install Lizard (Complexity Analyzer)

Lizard analyzes code complexity (cyclomatic complexity).

#### All Platforms (via pip)

```bash
# Install using pip
pip3 install lizard

# Verify installation
lizard --version
# Should show: lizard 1.17+

# Alternative: Install locally in user directory
pip3 install --user lizard
export PATH=$PATH:~/.local/bin
```

#### Test Lizard

```bash
# Create a C file
cat > example_complex.c << 'EOF'
#include <stdio.h>

int calculate(int x) {
    if (x < 0) {
        return -1;
    } else if (x == 0) {
        return 0;
    } else if (x < 10) {
        return x * 2;
    } else {
        return x * 3;
    }
}

int main(void) {
    printf("%d\n", calculate(5));
    return 0;
}
EOF

# Run Lizard
lizard example_complex.c

# Expected output:
# NLOC    CCN   Function
#   12      5   calculate
#    3      1   main

# Clean up
rm example_complex.c
```

---

### 6. Install PC-lint Plus (Optional, Commercial)

PC-lint Plus is a commercial MISRA C checker from Gimpel Software.

**Note**: PC-lint Plus requires a commercial license. This step is optional but highly recommended for SIL 2+ projects.

#### Installation

1. Purchase license from https://pclintplus.com/
2. Download installer for your platform
3. Follow vendor installation instructions
4. Configure for MISRA C:2012

#### Configuration Example

```bash
# Create PC-lint configuration file
cat > pclint_config.lnt << 'EOF'
// MISRA C:2012 configuration
au-misra3.lnt

// Compiler options
-w3               // Warning level 3
-e900             // Enable all messages
+fll              // Enable long long
-fcu              // Plain char is unsigned

// Include paths
-i/usr/include
-i./src

// File to check
src/door_control.c
EOF

# Run PC-lint
pclint pclint_config.lnt

# Clean up
rm pclint_config.lnt
```

**Alternative**: Use Cppcheck with `--addon=misra` for basic MISRA checking (free).

---

### 7. Configure Git

```bash
# Set your identity
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"

# Set default editor (choose one)
git config --global core.editor vim
git config --global core.editor nano
git config --global core.editor "code --wait"  # VS Code

# Set line endings (Unix style)
git config --global core.autocrlf input

# Enable colors
git config --global color.ui auto

# Verify configuration
git config --list
```

---

## Verification Checklist

Run this complete verification script:

```bash
#!/bin/bash
# EN 50128 Development Environment Verification Script

echo "=== EN 50128 Development Environment Verification ==="
echo ""

# Check GCC
echo "1. GCC Compiler:"
gcc --version | head -n 1
if [ $? -eq 0 ]; then echo "   ✅ PASS"; else echo "   ❌ FAIL"; fi
echo ""

# Check Make
echo "2. Make Build Tool:"
make --version | head -n 1
if [ $? -eq 0 ]; then echo "   ✅ PASS"; else echo "   ❌ FAIL"; fi
echo ""

# Check Git
echo "3. Git Version Control:"
git --version
if [ $? -eq 0 ]; then echo "   ✅ PASS"; else echo "   ❌ FAIL"; fi
echo ""

# Check Python
echo "4. Python:"
python3 --version
if [ $? -eq 0 ]; then echo "   ✅ PASS"; else echo "   ❌ FAIL"; fi
echo ""

# Check Unity
echo "5. Unity Test Framework:"
if [ -n "$UNITY_ROOT" ] && [ -f "$UNITY_ROOT/src/unity.c" ]; then
    echo "   UNITY_ROOT=$UNITY_ROOT"
    echo "   ✅ PASS"
else
    echo "   ❌ FAIL - UNITY_ROOT not set or Unity not found"
fi
echo ""

# Check lcov
echo "6. lcov Coverage Tool:"
lcov --version | head -n 1
if [ $? -eq 0 ]; then echo "   ✅ PASS"; else echo "   ❌ FAIL"; fi
echo ""

# Check Cppcheck
echo "7. Cppcheck Static Analyzer:"
cppcheck --version
if [ $? -eq 0 ]; then echo "   ✅ PASS"; else echo "   ❌ FAIL"; fi
echo ""

# Check Lizard
echo "8. Lizard Complexity Analyzer:"
lizard --version 2>/dev/null
if [ $? -eq 0 ]; then echo "   ✅ PASS"; else echo "   ❌ FAIL"; fi
echo ""

echo "=== Verification Complete ==="
```

Save this as `verify_setup.sh`, make it executable, and run:

```bash
chmod +x verify_setup.sh
./verify_setup.sh
```

**Expected Output**: All items should show ✅ PASS.

---

## Test the Complete Toolchain

### Clone the EN 50128 Repository

```bash
# Clone repository
git clone https://github.com/norechang/opencode-en50128.git
cd opencode-en50128

# Checkout sample branch (if available)
git checkout sample1

# Navigate to example
cd examples/train_door_control
```

### Build and Test

```bash
# Clean build
make clean

# Compile
make all

# Run tests
make test

# Generate coverage
make coverage

# Run verification
make verify
```

**Expected Results**:
- ✅ All 15 tests PASS
- ✅ 100% coverage (statement and branch)
- ✅ No Cppcheck violations
- ✅ All functions complexity ≤ 10

---

## IDE Setup (Optional)

### Visual Studio Code

**Install Extensions**:

1. **C/C++** (Microsoft) - IntelliSense, debugging
2. **C/C++ Extension Pack** - Complete C/C++ development
3. **Makefile Tools** - Makefile support
4. **Test Explorer UI** - Test visualization
5. **Coverage Gutters** - Inline coverage display

**Install VS Code**:

```bash
# Ubuntu/Debian
sudo snap install --classic code

# macOS
brew install --cask visual-studio-code
```

**Configure VS Code**:

Create `.vscode/settings.json`:

```json
{
    "C_Cpp.default.cStandard": "c11",
    "C_Cpp.default.compilerPath": "/usr/bin/gcc",
    "C_Cpp.default.intelliSenseMode": "gcc-x64",
    "files.associations": {
        "*.h": "c",
        "*.c": "c"
    },
    "editor.rulers": [80, 100],
    "editor.tabSize": 4,
    "editor.insertSpaces": true,
    "files.trimTrailingWhitespace": true,
    "C_Cpp.errorSquiggles": "Enabled",
    "C_Cpp.codeAnalysis.clangTidy.enabled": true
}
```

Create `.vscode/tasks.json`:

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build",
            "type": "shell",
            "command": "make all",
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
        {
            "label": "Test",
            "type": "shell",
            "command": "make test",
            "group": "test"
        },
        {
            "label": "Coverage",
            "type": "shell",
            "command": "make coverage"
        },
        {
            "label": "Verify",
            "type": "shell",
            "command": "make verify"
        }
    ]
}
```

---

## Troubleshooting

### Unity Not Found

**Problem**: `fatal error: unity.h: No such file or directory`

**Solution**:
```bash
# Check UNITY_ROOT
echo $UNITY_ROOT

# If empty, set it
export UNITY_ROOT=~/Unity
echo 'export UNITY_ROOT=~/Unity' >> ~/.bashrc
source ~/.bashrc

# Verify
ls $UNITY_ROOT/src/unity.c
```

### Coverage Files Not Generated

**Problem**: No `.gcda` files after running tests

**Solution**:
```bash
# Ensure compilation with coverage flags
gcc -fprofile-arcs -ftest-coverage -O0 -g ...

# Ensure executable runs successfully
./your_test_executable

# Check for .gcda files
ls *.gcda
```

### Cppcheck False Positives

**Problem**: Cppcheck reports false positives

**Solution**:
```bash
# Suppress specific warnings
cppcheck --suppress=unmatchedSuppression --suppress=missingInclude ...

# Create suppression file
cat > cppcheck_suppress.txt << 'EOF'
unmatchedSuppression
missingInclude
EOF

cppcheck --suppressions-list=cppcheck_suppress.txt ...
```

### Lizard Not Found

**Problem**: `command not found: lizard`

**Solution**:
```bash
# Check installation
pip3 list | grep lizard

# If not found, reinstall
pip3 install --user lizard

# Add to PATH
export PATH=$PATH:~/.local/bin
echo 'export PATH=$PATH:~/.local/bin' >> ~/.bashrc
source ~/.bashrc
```

### Permission Denied

**Problem**: `Permission denied` when running scripts

**Solution**:
```bash
# Make script executable
chmod +x script_name.sh

# Or run with bash
bash script_name.sh
```

---

## Next Steps

1. ✅ Verify all tools are installed (run `verify_setup.sh`)
2. ✅ Test the toolchain with the train door control example
3. ✅ Read the [Quick Start Guide](QUICKSTART.md)
4. ✅ Review [LIFECYCLE.md](../LIFECYCLE.md) for development process
5. ✅ Start your first EN 50128 project!

---

## Additional Resources

### Official Tool Documentation
- **GCC**: https://gcc.gnu.org/onlinedocs/
- **Unity**: https://github.com/ThrowTheSwitch/Unity
- **lcov**: http://ltp.sourceforge.net/coverage/lcov.php
- **Cppcheck**: http://cppcheck.sourceforge.net/
- **Lizard**: https://github.com/terryyin/lizard
- **PC-lint Plus**: https://pclintplus.com/

### MISRA C Resources
- **MISRA C:2012**: https://misra.org.uk/
- **MISRA Compliance:2020**: https://misra.org.uk/
- **Cppcheck MISRA addon**: https://github.com/danmar/cppcheck/blob/main/addons/misra.py

### Training and Tutorials
- **Unity Tutorial**: https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityGettingStartedGuide.md
- **gcov Tutorial**: https://gcc.gnu.org/onlinedocs/gcc/Gcov.html
- **MISRA C Examples**: https://www.misra.org.uk/forum/

---

## Support

If you encounter issues:

1. Check the [Troubleshooting](#troubleshooting) section
2. Review tool documentation
3. Search for error messages online
4. Ask on relevant forums (Stack Overflow, tool-specific forums)
5. Contact tool vendors for commercial products

---

**Document Version**: 1.0  
**Last Updated**: 2026-02-06  
**Platform**: Linux, macOS, Windows (WSL2)  
**Tools Version**: GCC 9+, Unity latest, lcov 1.14+, Cppcheck 2.0+, Lizard 1.17+
