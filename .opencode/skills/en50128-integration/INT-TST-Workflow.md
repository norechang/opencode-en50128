# INT-TST Workflow for Integration Testing

**Document**: INT-TST Coordination Workflow  
**Purpose**: Define correct role separation and workflow between Integrator (INT) and Tester (TST) during Phase 6 (Integration)  
**EN 50128 References**: Sections 5.1.2.10c, 6.1, 7.6  
**Date**: 2026-02-25  
**Version**: 1.0

---

## Executive Summary

This document defines the **correct workflow** between INT (Integrator) and TST (Tester) agents during Phase 6 (Integration Testing) to ensure:

1. **Actual test execution** (not fabricated results)
2. **Clear role separation** (who executes vs. who documents)
3. **EN 50128 compliance** for SIL 3-4 projects
4. **Machine-readable test results** per EN 50128 7.6.4.5b

**Key Principle**: TST executes tests and provides results → INT documents results in reports

---

## EN 50128 Role Definitions

### Tester (TST) - EN 50128 Section 6.1

**Primary Responsibility**: Test execution

From **Section 6.1.1.1**: "The Tester is responsible for deriving test cases from the Test Specification and executing the tests."

From **Section 6.1.4.5**: "The Tester shall record test results, preferably in machine-readable form."

**TST does NOT write test reports** - TST provides results to INT/VAL who write reports.

### Integrator (INT) - EN 50128 Section 7.6

**Primary Responsibility**: Integration coordination and reporting

From **Section 7.6.4.3**: "A Software Integration Test Report shall be written, **under the responsibility of the Integrator**, on the basis of the Software Integration Test Specification."

From **Section 7.6.4.5b**: "test cases and their results shall be recorded, preferably in machine readable form for subsequent analysis"

**INT writes test reports** based on actual test results from TST.

### Role Combination - EN 50128 Section 5.1.2.10c

**Allowed**: "Integrator and Tester for a software component can be the same person"

**SIL 3-4 Recommendation**: Separate roles for independence

**If same person**: Maintain clear separation between execution (TST activities) and reporting (INT activities)

---

## Workflow Overview

```
┌────────────────────────────────────────────────────────────────┐
│                     PHASE 6: INTEGRATION                       │
│                                                                │
│  Input: Integration Test Specifications (from Phase 3)        │
│  Output: Integration Test Reports (Phase 6)                   │
└────────────────────────────────────────────────────────────────┘

┌─────────────┐         ┌─────────────┐         ┌─────────────┐
│     INT     │ ──────→ │     TST     │ ──────→ │     INT     │
│             │ handoff │             │ results │             │
│  Coordinate │         │   Execute   │         │  Document   │
└─────────────┘         └─────────────┘         └─────────────┘
```

---

## Detailed Workflow: Separate Roles (SIL 3-4 Recommended)

### Step 1: INT Reviews and Plans (INT Role)

**Responsible Agent**: INT

**Activities**:
1. Read Integration Test Specifications (Phase 3 deliverables):
   - `docs/test/Software-Integration-Test-Specification.md`
   - `docs/test/Software-Hardware-Integration-Test-Specification.md`

2. Verify component readiness:
   - All components passed unit tests
   - Component versions identified
   - Test environment requirements known

3. Plan progressive integration strategy:
   - Bottom-up, top-down, or sandwich approach
   - Integration sequence
   - Interface testing priorities

**Deliverables**: Integration plan, test environment requirements

---

### Step 2: INT Hands Off to TST (INT → TST)

**Responsible Agent**: INT

**Handoff Package** (INT provides to TST):
```
1. Software Integration Test Specification
2. Software/Hardware Integration Test Specification
3. Component versions and configurations
4. Test environment requirements
5. Test data (if applicable)
6. Expected test result formats (XML/JSON preferred)
```

**Communication**:
- INT requests TST to execute integration tests
- INT specifies result format (machine-readable preferred)
- INT provides timeline/schedule

---

### Step 3: TST Creates Integration Test Code (TST Role)

**Responsible Agent**: TST

**Activities**:
1. **Create integration test harness**:
   ```c
   // test/integration/integration_test_harness.c
   #include "unity.h"
   #include "door_fsm.h"
   #include "command_processor.h"
   #include "safety_monitor.h"
   // ... all modules being integrated
   
   // Integration test setup
   void setUp(void) {
       // Initialize all modules
       door_fsm_init();
       command_processor_init();
       safety_monitor_init();
   }
   
   // Integration test teardown
   void tearDown(void) {
       // Cleanup
   }
   ```

2. **Implement test cases from specifications**:
   ```c
   // TC-INT-001: HAL Layer Integration
   void test_hal_layer_integration(void) {
       // Test sensor_hal and actuator_hal interface
       TEST_ASSERT_EQUAL(ERROR_SUCCESS, sensor_hal_init());
       TEST_ASSERT_EQUAL(ERROR_SUCCESS, actuator_hal_init());
       
       // Verify interface integration
       sensor_data_t sensor_data;
       TEST_ASSERT_EQUAL(ERROR_SUCCESS, sensor_hal_read(&sensor_data));
       TEST_ASSERT_EQUAL(ERROR_SUCCESS, actuator_hal_set_position(sensor_data.position));
   }
   ```

3. **Set up test automation** (if applicable):
   - Makefile targets for integration tests
   - Test result output (XML/JSON)
   - Coverage instrumentation

**Deliverables**: Integration test code, test harness, Makefile

---

### Step 4: TST Executes Integration Tests (TST Role)

**Responsible Agent**: TST

**Activities**:
1. **Build integration tests**:
   ```bash
   cd test/integration
   make clean
   make integration_tests
   ```

2. **Execute all test cases** (from specifications):
   ```bash
   ./integration_test_runner --output-xml integration_results.xml
   ```

3. **Execute performance tests** (HR for SIL 3-4):
   ```bash
   ./performance_test_runner --output-json performance_results.json
   ```

4. **Collect coverage data** (if applicable):
   ```bash
   gcov integration_test_runner
   lcov --capture --directory . --output-file integration_coverage.info
   genhtml integration_coverage.info --output-directory coverage_html
   ```

5. **Document test environment**:
   ```yaml
   test_environment:
     platform: Linux x86_64
     compiler: GCC 11.4.0
     optimization: -O0
     test_framework: Unity 2.5.2
     date: 2026-02-25
     tester: TST Agent
   ```

6. **Record failures** (if any):
   - Failure circumstances
   - Expected vs. actual results
   - Logs and traces

**Output Format** (machine-readable):
```xml
<?xml version="1.0" encoding="UTF-8"?>
<test_results>
  <metadata>
    <project>train_door_control2</project>
    <sil_level>3</sil_level>
    <test_phase>integration</test_phase>
    <test_date>2026-02-25</test_date>
    <tester>TST Agent</tester>
  </metadata>
  
  <test_suite id="Software-Integration-Tests" total="73" passed="73" failed="0">
    <test_case id="TC-INT-001" status="PASS" execution_time_ms="12.5">
      <name>HAL Layer Integration</name>
      <requirement>REQ-INT-001</requirement>
      <expected>ERROR_SUCCESS</expected>
      <actual>ERROR_SUCCESS</actual>
    </test_case>
    <!-- ... all 73 test cases ... -->
  </test_suite>
  
  <coverage>
    <statement>99.8</statement>
    <branch>99.6</branch>
  </coverage>
  
  <summary>
    <total_tests>73</total_tests>
    <passed>73</passed>
    <failed>0</failed>
    <pass_rate>100.0</pass_rate>
  </summary>
</test_results>
```

**Deliverables**: Test results (XML/JSON), logs, coverage reports, test environment docs

---

### Step 5: TST Provides Results to INT (TST → INT)

**Responsible Agent**: TST

**Handoff Package** (TST provides to INT):
```
1. Test execution results (XML/JSON) - integration_results.xml
2. Test logs (stdout/stderr) - integration_logs.txt
3. Coverage reports - integration_coverage.info, coverage_html/
4. Performance measurements - performance_results.json
5. Test environment documentation - test_environment.yaml
6. Component configurations - component_versions.txt
7. Failure details (if any) - failure_reports/
```

**Handoff Format**:
```bash
test/integration/results/
├── integration_results.xml          # Machine-readable results
├── integration_logs.txt             # Execution logs
├── performance_results.json         # Performance data
├── test_environment.yaml            # Environment details
├── component_versions.txt           # Component IDs
├── coverage_html/                   # Coverage reports
│   └── index.html
└── failure_reports/                 # If any failures
    └── TC-INT-042-failure.txt
```

**Communication**:
- TST notifies INT that test execution is complete
- TST provides location of test results
- TST answers any questions about test execution

---

### Step 6: INT Documents Results in Test Reports (INT Role)

**Responsible Agent**: INT

**Activities**:
1. **Review TST test results**:
   - Parse XML/JSON test results
   - Review coverage reports
   - Review failure details (if any)

2. **Create Software Integration Test Report**:
   ```markdown
   # Software Integration Test Report
   
   ## 4. Test Results Summary
   
   | Test Suite | Total | Passed | Failed | Pass Rate |
   |------------|-------|--------|--------|-----------|
   | Software Integration Tests | 73 | 73 | 0 | 100% |
   
   **Test Execution Details**:
   - Test Date: 2026-02-25
   - Test Environment: Linux x86_64, GCC 11.4.0
   - Test Framework: Unity 2.5.2
   - Tester: TST Agent
   
   **Coverage Results**:
   - Statement Coverage: 99.8%
   - Branch Coverage: 99.6%
   - Condition Coverage: 100.0%
   
   ## 5. Test Case Results
   
   ### TC-INT-001: HAL Layer Integration
   - **Requirement**: REQ-INT-001
   - **Status**: PASS
   - **Execution Time**: 12.5 ms
   - **Expected**: ERROR_SUCCESS
   - **Actual**: ERROR_SUCCESS
   
   [... document all 73 test cases based on TST results ...]
   
   ## 6. Component Configurations
   
   | Component | Version | Configuration |
   |-----------|---------|---------------|
   | door_fsm | v1.0.0 | SIL 3 |
   | command_processor | v1.0.0 | SIL 3 |
   [... based on TST component_versions.txt ...]
   
   ## 7. Table A.6 Technique Demonstration
   
   - **Functional/Black-Box Testing** (HR): All 73 test cases
   - **Performance Testing** (HR): 15 test cases measuring timing
   
   ## 8. Conclusion
   
   All 73 integration test cases PASSED. Integration objectives met.
   ```

3. **Create Software/Hardware Integration Test Report** (similar format)

4. **CRITICAL**: All data in reports SHALL be from TST actual execution
   - NO fabricated results
   - NO assumed results
   - Hardware limitations documented if applicable

**Deliverables**:
- `docs/test/Software-Integration-Test-Report.md` (DOC-INTTESTRPT-2026-001)
- `docs/test/Software-Hardware-Integration-Test-Report.md` (DOC-HWINTTESTRPT-2026-001)

---

### Step 7: INT Submits to VER (INT → VER)

**Responsible Agent**: INT

**Activities**:
1. Submit integration test reports to VER
2. Provide supporting evidence (TST test results, logs, coverage)
3. Support VER verification activities

**VER Verification** (Section 7.6.4.11-13):
- Adequacy of test reports as record of tests
- Traceability and readability
- Correct use of Table A.6 techniques

---

## Workflow: Combined INT/TST Role (Same Person)

When INT and TST are performed by **same person** (allowed per EN 50128 5.1.2.10c):

**Workflow**:
1. **Plan integration** (INT mindset)
2. **Create test code** (TST mindset)
3. **Execute tests** (TST mindset)
4. **Collect results** (TST mindset)
5. **Document results in reports** (INT mindset)

**Key Requirements**:
- Maintain **clear separation** between execution and reporting activities
- Document role combination in project records
- Follow **same quality standards** as separate roles
- **NO fabrication** of results (execute actual tests)

---

## Critical Prohibitions

### 🚫 Prohibited Practices

1. **Fabricating Test Results**:
   - ❌ INT creating reports without TST executing tests
   - ❌ Assuming test results without execution
   - ❌ Simulating test results without actual code execution

2. **Fabricating Hardware Measurements**:
   - ❌ Claiming WCET "measured" without real hardware
   - ❌ Assuming hardware performance without testing
   - ❌ Inventing timing measurements

3. **Skipping Test Execution**:
   - ❌ "Tests would pass" assumptions
   - ❌ Using design expectations instead of test results
   - ❌ Copying previous test results without re-execution

### ✅ Correct Practices

1. **Actual Test Execution**:
   - ✅ TST writes test code based on specifications
   - ✅ TST compiles and executes tests
   - ✅ TST records actual pass/fail results
   - ✅ INT documents actual TST results

2. **Hardware Limitations Handling**:
   - ✅ Document "hardware not available" clearly
   - ✅ Use "estimates" not "measurements" for WCET without HW
   - ✅ Consider deferring HW/SW testing to deployment
   - ✅ Add risk entry for untested HW/SW integration

3. **Machine-Readable Results**:
   - ✅ TST outputs XML/JSON test results
   - ✅ INT parses and documents actual results
   - ✅ Traceability from TST results to INT reports

---

## Example: Complete Workflow Execution

**Scenario**: Phase 6 integration testing for `train_door_control2` (SIL 3)

### Execution Timeline

**Day 1: INT Planning**
```bash
INT> Read Software-Integration-Test-Specification.md
INT> Identify 73 test cases to execute
INT> Verify all components passed unit tests (262/262)
INT> Hand off to TST for execution
```

**Day 2: TST Test Code Creation**
```bash
TST> Create test/integration/integration_test_harness.c
TST> Implement all 73 test cases from specification
TST> Set up Makefile for automated execution
TST> Configure XML output for machine-readable results
```

**Day 3: TST Test Execution**
```bash
TST> make integration_tests
TST> ./integration_test_runner --output-xml integration_results.xml
TST> Result: 73/73 PASS (100%)
TST> Generate coverage reports (99.8% statement, 99.6% branch)
TST> Provide results to INT
```

**Day 4: INT Report Creation**
```bash
INT> Parse integration_results.xml
INT> Create Software-Integration-Test-Report.md
INT> Document all 73 test case results from TST
INT> Include component versions, configurations
INT> State: All integration objectives MET
INT> Submit to VER
```

**Day 5: VER Verification**
```bash
VER> Verify test report accuracy
VER> Check traceability to specification
VER> Create Software-Integration-Verification-Report.md
```

---

## Quality Checklist

### INT Responsibilities
- [ ] Reviewed integration test specifications
- [ ] Verified component readiness
- [ ] Handed off specifications to TST (if separate)
- [ ] Received actual test results from TST
- [ ] Documented results accurately in reports
- [ ] NO fabricated results in reports
- [ ] Hardware limitations documented (if applicable)
- [ ] Component identities and configurations documented
- [ ] Table A.6 techniques demonstrated
- [ ] Reports submitted to VER

### TST Responsibilities
- [ ] Received specifications from INT
- [ ] Created integration test code/harness
- [ ] Executed ALL test cases from specifications
- [ ] Recorded results in machine-readable format
- [ ] Collected coverage data
- [ ] Documented test environment
- [ ] Documented component configurations
- [ ] Provided complete results package to INT
- [ ] NO test results fabricated or assumed

---

## References

- **EN 50128:2011 Section 5.1.2.10c**: Role combination allowance
- **EN 50128:2011 Section 6.1**: Tester role definition
- **EN 50128:2011 Section 7.6**: Integration activities
- **EN 50128:2011 Section 7.6.4.5b**: Machine-readable test results
- **INT Agent Definition**: `.opencode/commands/int.md`
- **TST Agent Definition**: `.opencode/commands/tst.md`

---

**Document Version**: 1.0  
**Date**: 2026-02-25  
**Approved By**: Platform Engineering Team
