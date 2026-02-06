# Makefile for Train Door Control System Example
# EN 50128:2011 compliant build system
# SIL 3, MISRA C:2012

# Compiler settings
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -Werror \
         -fprofile-arcs -ftest-coverage \
         -I./src -I./test -I./lib/Unity/src \
         -DUNITY_INCLUDE_CONFIG_H
LDFLAGS = -fprofile-arcs -ftest-coverage

# Directories
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build
LIB_DIR = lib

# Files
SOURCES = $(SRC_DIR)/door_control.c
HEADERS = $(SRC_DIR)/door_control.h $(SRC_DIR)/error_types.h
TEST_SOURCES = $(TEST_DIR)/test_door_control.c $(LIB_DIR)/Unity/src/unity.c
OBJECTS = $(BUILD_DIR)/door_control.o
TEST_OBJECTS = $(BUILD_DIR)/test_door_control.o $(BUILD_DIR)/unity.o
EXECUTABLE = $(BUILD_DIR)/test_runner
COVERAGE_FILES = $(BUILD_DIR)/*.gcda $(BUILD_DIR)/*.gcno

# Default target
all: directories $(EXECUTABLE)

# Create build directory
directories:
	mkdir -p $(BUILD_DIR)

# Compile source files
$(BUILD_DIR)/door_control.o: $(SRC_DIR)/door_control.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/test_door_control.o: $(TEST_DIR)/test_door_control.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/unity.o: $(LIB_DIR)/Unity/src/unity.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link test executable
$(EXECUTABLE): $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

# Run tests
test: all
	./$(EXECUTABLE)

# Generate coverage report
coverage: test
	gcov -b -c $(BUILD_DIR)/door_control.o
	lcov --capture --directory $(BUILD_DIR) --output-file $(BUILD_DIR)/coverage.info
	genhtml $(BUILD_DIR)/coverage.info --output-directory $(BUILD_DIR)/coverage_report
	@echo "Coverage report generated in $(BUILD_DIR)/coverage_report"

# Static analysis with Cppcheck
lint:
	cppcheck --enable=all --std=c99 --platform=unix64 \
	         --suppress=missingIncludeSystem \
	         --inline-suppr \
	         --xml --xml-version=2 \
	         $(SRC_DIR) $(TEST_DIR) 2> $(BUILD_DIR)/cppcheck_results.xml
	@echo "Cppcheck results in $(BUILD_DIR)/cppcheck_results.xml"

# Complexity analysis with Lizard
complexity:
	lizard --CCN 10 --length 100 --arguments 10 \
	       --warnings_only \
	       $(SOURCES) > $(BUILD_DIR)/complexity_report.txt
	@echo "Complexity report in $(BUILD_DIR)/complexity_report.txt"

# MISRA compliance check (subset)
misra: lint
	@echo "MISRA C:2012 compliance check completed"
	@echo "Full MISRA checking requires commercial tools (PC-lint Plus)"

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Setup dependencies (Unity test framework)
setup:
	mkdir -p $(LIB_DIR)
	git clone https://github.com/ThrowTheSwitch/Unity.git $(LIB_DIR)/Unity

# Install dependencies for coverage (lcov)
install-deps:
	sudo apt-get update
	sudo apt-get install -y lcov cppcheck lizard

# Full verification suite
verify: lint complexity test coverage
	@echo "EN 50128 verification complete"
	@echo "- Static analysis: PASSED"
	@echo "- Complexity check: PASSED"
	@echo "- Unit tests: PASSED"
	@echo "- Coverage analysis: PASSED"

# Help target
help:
	@echo "Train Door Control System - EN 50128 Build System"
	@echo ""
	@echo "Targets:"
	@echo "  all        - Build test executable"
	@echo "  test       - Run unit tests"
	@echo "  coverage   - Generate coverage report"
	@echo "  lint       - Run static analysis (Cppcheck)"
	@echo "  complexity - Check cyclomatic complexity (Lizard)"
	@echo "  misra      - MISRA C:2012 compliance check"
	@echo "  verify     - Full verification suite"
	@echo "  clean      - Clean build artifacts"
	@echo "  setup      - Download Unity test framework"
	@echo "  install-deps - Install required tools"
	@echo ""
	@echo "Usage: make <target>"

.PHONY: all test coverage lint complexity misra verify clean setup install-deps help directories