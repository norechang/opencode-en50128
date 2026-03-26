# Software Change Request

**EN 50128:2011 Reference**: §6.6, §6.6.4.1(a–i), §6.6.4.2  
**Template Version**: 3.0  
**Stored at**: `changes/CR-<YYYYMMDD>-<NNN>.md`

---

## Document Header

| Field | Value |
|-------|-------|
| **CR Number** | CR-YYYYMMDD-NNN |
| **Document ID** | DOC-CHANGEREC-YYYY-NNN |
| **Version** | 0.1 |
| **Date Submitted** | YYYY-MM-DD |
| **Project** | [Project Name] |
| **SIL Level** | [0 \| 1 \| 2 \| 3 \| 4] |
| **Originator** | [Name, Role] |
| **Status** | [Submitted \| Under CCB Review \| Approved \| Rejected \| Implemented \| Closed] |

## Document History

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 0.1 | YYYY-MM-DD | [Name] | Initial submission |

---

## §6.6.4.1(a) — Change Identification

| Field | Value |
|-------|-------|
| **CR Title** | [Short descriptive title] |
| **CR Number** | CR-YYYYMMDD-NNN |
| **Priority** | [Critical \| High \| Medium \| Low] |
| **Category** | [Defect \| Safety Issue \| Enhancement \| Documentation] |

---

## §6.6.4.1(b) — Reason for Change

**Problem / Change Need Statement:**

[Describe the defect, non-conformance, or change need precisely. Reference the phase,
document, or code location where the issue was found.]

**Current Situation:**

[Describe the current erroneous or inadequate state.]

**Desired Outcome:**

[Describe what the correct or improved state should be.]

---

## §6.6.4.1(c) — Consequence Analysis

### Technical Impact

**Earliest affected lifecycle phase:**

| Phase | Affected | Re-entry required |
|-------|----------|-------------------|
| Phase 2 — Requirements | [Yes / No] | [Yes / No] |
| Phase 3 — Architecture & Design | [Yes / No] | [Yes / No] |
| Phase 4 — Component Design | [Yes / No] | [Yes / No] |
| Phase 5 — Implementation & Testing | [Yes / No] | [Yes / No] |
| Phase 6 — Integration | [Yes / No] | [Yes / No] |
| Phase 7 — Validation | [Yes / No] | [Yes / No] |
| Phase 9 — Deployment | [Yes / No] | [Yes / No] |

**Earliest re-entry phase**: Phase [N]  
**Normative basis**: §6.6.4.2 — all changes shall initiate a return to an appropriate lifecycle phase.

### Safety Impact

- [ ] No safety impact — justification: [text]
- [ ] Potential safety impact — SAF analysis required before CCB vote
- [ ] Confirmed safety impact — SIL re-assessment required

**Hazard Log update required**: [Yes / No]

### Affected Configuration Items (§6.6.4.1(f))

| CI Key | Document / Artifact | Current Version | Impact Level |
|--------|---------------------|----------------|--------------|
| [e.g. SRS] | Software Requirements Specification | [v1.2] | [High / Medium / Low] |
| [e.g. COMPDESIGN] | Software Component Design Specification | [v1.0] | |

---

## §6.6.4.1(d) — Approval (CCB Decision)

**CCB Meeting Date**: YYYY-MM-DD  
**CCB Chair**: [PM Name] (PM is CCB Chair per WORKFLOW.md)  
**CM Secretary**: [CM Name] (CM records decisions; does not vote)

**CCB Participants** (per WORKFLOW.md Diagram 4):

| Role | Name | Present |
|------|------|---------|
| PM (Chair) | [Name] | [Yes / No] |
| REQ | [Name] | [Yes / No] |
| SAF | [Name] | [Yes / No] |
| DES | [Name] | [Yes / No] |
| IMP | [Name] | [Yes / No] |
| TST | [Name] | [Yes / No] |
| VER | [Name] | [Yes / No] |
| CM (Secretary) | [Name] | Yes |

**CCB Decision**: [Approved / Rejected / Deferred]

**Conditions (if Approved with conditions)**:
1. [Condition 1]

**Rejection / Deferral Rationale (if applicable)**:
[Reason]

**CCB Signatures** (SIL-dependent):

| Role | Name | Signature | Date |
|------|------|-----------|------|
| PM (Chair) | [Name] | | YYYY-MM-DD |
| SAF (if safety impact) | [Name] | | YYYY-MM-DD |
| VER (SIL 3–4) | [Name] | | YYYY-MM-DD |

> **Note**: VAL signs the Software Validation Report (Phase 7). ASR signs the Software Assessment
> Report (Phase 8). Neither VAL nor ASR signs individual Change Requests. See WORKFLOW.md §independence.

---

## §6.6.4.1(e) — Documents to be Updated

| CI Key | Document Name | Current Version | Action |
|--------|--------------|----------------|--------|
| [SRS] | Software Requirements Specification | [v1.2] | [Update §X.Y] |
| [SDS] | Software Design Specification | [v1.0] | [Update §X.Y] |
| [SOURCECODE] | Source Code | [commit abc123] | [Modify module.c] |

---

## §6.6.4.1(g) — Implementation, Verification and Test

**Implementation approach**:

[Describe the proposed solution.]

**Verification activities required**:
- [ ] VER re-verification of Phase [N] deliverables
- [ ] Static analysis re-run (SIL 2–4)
- [ ] Coverage re-measurement (SIL 2–4)
- [ ] VER Verification Report update required

**Test activities required**:
- [ ] Unit tests: [describe scope]
- [ ] Integration tests: [describe scope]
- [ ] Overall software tests (if Phase 7 affected): [describe scope]

**Revalidation required** (if Phase 7 affected):
- [ ] VAL Validation Report to be re-issued (§6.3.4.10 — must state new baseline)

---

## §6.6.4.1(h) — Parties to be Notified

| Party | Name | Notification method | Date notified |
|-------|------|---------------------|---------------|
| COD | [Name] | [Task tool / meeting] | YYYY-MM-DD |
| PM | [Name] | | YYYY-MM-DD |
| Safety Authority (if safety impact) | [Name] | | YYYY-MM-DD |

---

## §6.6.4.1(i) — Traceability

**Traceability update required**: [Yes / No]

| Traceability link | Action |
|-------------------|--------|
| Requirement → Design | [Update if requirements changed] |
| Design → Code | [Update if design changed] |
| Code → Test | [Update if code changed] |
| Test → Requirement | [Update if tests changed] |

**Traceability rule reference**: `TRACEABILITY.md`

---

## CM Baseline Actions (CM completes this section)

**Baseline branch created from**: [e.g. `planning-baseline` gate 5 tag]  
**Branch name**: [e.g. `cr-YYYYMMDD-NNN-branch`]

After all affected gates re-pass:

**Post-CR baseline name**: [e.g. `implementation-baseline-post-cr-YYYYMMDD-NNN`]  
**VCS tag**: [e.g. `myproject-gate5-implementation-baseline-YYYYMMDD`]  
**Manifest path**: `baselines/<baseline-name>/manifest.yaml`  
**Superseded baseline archived**: [Yes / No]  
**Normative basis**: §9.1.4.2, D.48 — superseded baselines are archived, never deleted.

---

## Closure

**All §6.6.4.1(a–i) aspects addressed**: [Yes / No]

| Aspect | Status |
|--------|--------|
| (a) Unique identification | [Complete] |
| (b) Reason recorded | [Complete] |
| (c) Consequences analysed | [Complete] |
| (d) CCB approval obtained | [Complete / Pending] |
| (e) Affected documents updated | [Complete / Pending] |
| (f) Affected CIs recorded | [Complete] |
| (g) Implementation, verification, test complete | [Complete / Pending] |
| (h) Relevant parties notified | [Complete] |
| (i) Traceability maintained | [Complete / Pending] |

**CR Status**: [Closed]  
**Closure Date**: YYYY-MM-DD  
**CM sign-off**: [Name], YYYY-MM-DD

---

**EN 50128:2011 References**: §6.6, §6.6.4.1(a–i), §6.6.4.2, §9.2.4  
**Related documents**: `WORKFLOW.md` Diagram 4, `activities/baseline-management.yaml` `change_request_baseline_path`  
**Skill Owner**: Configuration Manager (`cm`)
