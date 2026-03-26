# EN 50128 Tools Skill

**EN 50128 Reference**: Section 6.7 — Software Tools and Their Validation
**Target Roles**: All agents (REQ, DES, IMP, TST, VER, INT, VAL, SAF, QUA, CM, PM, COD)

---

## Authoritative Source

All tool policy — TCL classification, qualification obligations, tool category requirements,
SIL matrix, ISA obligations — is defined in:

| Document | Contents |
|----------|----------|
| `TOOLS.md` | TCL classification policy and decision tree, third-party vs. platform-developed policy, tool category framework (categories not instances), qualification process diagram, SIL requirements matrix, tool management obligations, ISA evaluation scope |

Specific tool instances, versions, invocation flags, qualification status, and evidence paths
are recorded in downstream operational documents derived from `TOOLS.md`.

---

## Key Policy Points

### TCL Classification (§6.7, Table 1)

- **T1**: Output verified by independent human review or independent process → no formal
  qualification document required. Record basis for T1 assignment.
- **T2**: Output used directly in the project; errors detected by an independent process
  → validation test suite + validation report required (§6.7.4.3, §6.7.4.10, §6.7.4.11).
- **T3**: Output cannot be independently verified by other means → full qualification
  evidence + report required (§6.7.4.4, §6.7.4.5).

When in doubt, assign the higher TCL. Downgrading requires documented justification (§6.7.4.2).

### Third-Party vs. Platform-Developed (critical for ISA)

- **Third-party tools**: project-specific validation supplements supplier evidence
  (certifications, history of use in safety-critical domains, test suite results).
- **Platform-developed tools**: project produces ALL evidence from scratch.
  T1 classification requires documented independent review of every tool output.
  T2 classification requires a project-authored validation test suite.
- **`to_be_provided`**: acceptable during development; MUST be resolved before ISA evaluation.

### Tool Category Obligations by SIL

Use the tool category framework in `TOOLS.md` Section 3 to determine the minimum TCL and
mandatory-from-SIL for each category:

- **Compiler / Linker / Assembler** → T3, mandatory SIL 1+
- **Static analysis** → T2, HR from SIL 2, M from SIL 3–4 (two independent tools mandatory at SIL 3–4)
- **Complexity analysis** → T2, M from SIL 3–4
- **Code coverage measurement** → T2, HR from SIL 2+
- **MC/DC coverage analysis** → T1 minimum, HR from SIL 3–4
- **Test execution framework** → T2, mandatory SIL 1+
- **MISRA C compliance checker** → T2, M from SIL 2+
- **Version control / CM** → T1, mandatory all SIL
- **Build automation** → T2, mandatory SIL 1+

### SIL Requirements Summary

| Obligation | SIL 1 | SIL 2 | SIL 3–4 |
|------------|-------|-------|---------|
| Assign TCL to every tool | **M** | **M** | **M** |
| T2 validation test suite | R | HR | **M** |
| T3 qualification report | HR | HR | **M** |
| Tool version lock (CM) | R | **M** | **M** |
| Tools Validation Report (Annex C item 26) | HR | HR | **M** |

### ISA Evaluation

The ISA will examine: TCL classification justification, T3 conformance evidence, platform-
developed tool validation test suites, version lock compliance, and resolution of all
`to_be_provided` gaps. See `TOOLS.md` Section 7 for the full ISA evaluation scope.
