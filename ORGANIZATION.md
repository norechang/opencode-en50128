# EN 50128 Organizational Role Structure

This document defines the organizational hierarchy and independence architecture for EN 50128:2011 railway software development, in SIL-based variants.

> **Normative Basis:** The SIL-tiered role assignment architecture in this document is grounded in EN 50128:2011 §5.1.2.9, which states: *"Throughout the Software Lifecycle, the assignment of roles to persons shall be in accordance with 5.1.2.10 to 5.1.2.14, to the extent required by software SIL."* The three SIL-tier sections below implement the preferred organisational structures defined in §5.1.2.10 (SIL 3–4), §5.1.2.11 (SIL 1–2), and §5.1.2.12 (SIL 0).

> **Platform Role Notice:** The "VMGR (V&V Manager)" role used in this platform is a **platform-defined extension** not enumerated in EN 50128:2011 Annex B. The closest normative analogue is §5.1.2.10(e), which states the Verifier may report to the Project Manager **or** to the Validator, and §5.1.2.10(f), which prohibits the Validator from reporting to the Project Manager. The platform's VMGR construct implements the "Verifier reports to Validator" option of §5.1.2.10(e) via a named independent V&V authority that sits on the independent side of the §5.1.2.10(g–j) wall. This is a platform architectural choice, not a direct normative mandate. **This platform architecture must be approved by the Safety Authority and documented in the SQAP before use on any SIL 1–4 project.** All other roles correspond directly to Annex B definitions.

> **Role Label Mapping:** Platform abbreviations map to normative EN 50128:2011 Annex B roles as follows:

| Platform Label | EN 50128:2011 Annex B Role | Section |
|----------------|---------------------------|---------|
| REQ | Requirements Manager | Table B.1 |
| DES | Designer | Table B.2 |
| IMP | Implementer | Table B.3 |
| TST | Tester | Table B.4 |
| VER | Verifier | Table B.5 |
| INT | Integrator | Table B.6 |
| VAL | Validator | Table B.7 |
| ASR | Assessor | Table B.8 |
| PM  | Project Manager | Table B.9 |
| CM  | Configuration Manager | Table B.10 |
| SAF | Safety Engineer | §7.1 (platform extension) |
| QUA | Quality Assurance | §6.5 (platform extension) |
| COD | Lifecycle Coordinator | §5.3 (platform extension) |
| VMGR | V&V Manager | Platform extension — basis: §5.1.2.10(e–f) |

---

## Index

1. [SIL 0: Minimal Organization](#sil-0-minimal-organization)
2. [SIL 1–2: Permissive Organization](#sil-12-permissive-organization)
3. [SIL 3–4: Strict Independence Organization](#sil-34-strict-independence-organization)
4. [Key Differences Summary](#key-differences-summary)
5. [Role Combination Rules](#role-combination-rules)
6. [Independence Reference Matrix](#independence-reference-matrix)

---

## SIL 0: Minimal Organization

Assessment may be waived when an ISO 9001 certificate is available (§6.4.1.2). Maximum role consolidation is permitted for the V&V stream. INT, TST, VER, and VAL for the same component may all be the same person (§5.1.2.12(b)). However, §5.1.2.12(d) and §5.1.2.12(e) impose residual prohibitions even at SIL 0: Requirements Manager, Designer, and Implementer shall not also be Tester or Integrator for the **same component** (§5.1.2.12(d)); Verifier and Validator shall not also be Requirements Manager, Designer, or Implementer (§5.1.2.12(e)).

```
┌─────────────────────────────────────────────────────────────────────┐
│                    SAFETY AUTHORITY / CUSTOMER                      │
└────────────────────────────┬────────────────────────────────────────┘
                             │ governs
                             ▼
┌────────────────────────────────────────────────────────────────────┐
│                  COD  (Lifecycle Coordinator)                       │
│          Phase gate enforcement · Lifecycle state · Compliance      │
└──────────────────────────────┬─────────────────────────────────────┘
                               │ authorizes phases
                               ▼
┌────────────────────────────────────────────────────────────────────┐
│                     PM  (Project Manager)                           │
│              Team coordination · CCB · Resource management          │
└────────┬───────────────────────────────────────────────────────────┘
         │ orchestrates
         ▼
┌────────────────────────────────────────────────────────────────────┐
│                   DEVELOPMENT & V&V TEAM                            │
│                                                                     │
│  ┌──────────────┐  ┌──────┐  ┌──────┐  ┌──────┐  ┌──────┐        │
│  │Requirements  │  │ DES  │  │ IMP  │  │ INT  │  │ SAF  │        │
│  │   Manager    │  │Design│  │ Code │  │Integ.│  │Safety│        │
│  └──────────────┘  └──────┘  └──────┘  └──────┘  └──────┘        │
│                                                                     │
│  ┌──────┐  ┌──────┐  ┌──────┐  ┌──────┐                           │
│  │ TST  │  │ VER  │  │  CM  │  │ QUA  │                           │
│  │Tests │  │Verif.│  │ CfgMg│  │Audits│                           │
│  └──────┘  └──────┘  └──────┘  └──────┘                           │
│                                                                     │
│  Per §5.1.2.12(b): INT, TST, VER, VAL for same component          │
│  may all be the same person.                                        │
└────────────────────────────────────────────────────────────────────┘
         │
         ▼
┌────────────────────────────────────────────────────────────────────┐
│              VAL  (Validator)               ★ RELEASE AUTHORITY    │
│   System testing · Acceptance · Reports to PM (§5.1.2.12(a))      │
│   Software SHALL NOT be released without Validator sign-off        │
│   (§5.1.2.8, §6.3.4.16)                                           │
└────────────────────────────────────────────────────────────────────┘
         │ (if ISO 9001 cert available, ASR may be waived — §6.4.1.2)
         ▼
┌────────────────────────────────────────────────────────────────────┐
│         ASR  (Assessor)  [waivable at SIL 0 per §6.4.1.2          │
│          if ISO 9001 certificate is in place]                      │
│   Independent · Reviews all artifacts · Reports to Safety Authority│
└────────────────────────────────────────────────────────────────────┘
```

**Key characteristics at SIL 0:**
- V&V stream consolidation permitted — INT, TST, VER, VAL for same component may be one person (§5.1.2.12(b))
- **Residual prohibitions still apply:** REQ/DES/IMP shall not be TST/INT for the same component (§5.1.2.12(d)); VER/VAL shall not be REQ/DES/IMP (§5.1.2.12(e))
- Assessor may be waived **only** if an ISO 9001 certificate is available (§6.4.1.2)
- VAL holds release authority: no software release without Validator sign-off (§5.1.2.8, §6.3.4.16)
- VER and VAL may report to PM (§5.1.2.12(a))

---

## SIL 1–2: Permissive Organization

Assessment is **mandatory** (§5.1.2.4). VER and VAL must not also hold development roles — this is a **mandatory "shall" clause** (§5.1.2.11(h)), not an advisory. Organisational reporting independence for VER/VAL is HR at SIL 1–2. No VMGR required.

```
┌─────────────────────────────────────────────────────────────────────┐
│                    SAFETY AUTHORITY / CUSTOMER                      │
└──────────┬─────────────────────────────────────────┬────────────────┘
           │ governs                                 │ independently
           ▼                                         │ reports to
┌────────────────────────────────────────────────────│───────────────┐
│                  COD  (Lifecycle Coordinator)       │               │
│          Phase gate enforcement · Lifecycle state   │               │
└──────────────────────────────┬─────────────────────│───────────────┘
                               │ authorizes phases   │
                               ▼                     │
┌────────────────────────────────────────────────────│───────────────┐
│                     PM  (Project Manager)           │               │
│              Team coordination · CCB · Resources    │               │
└────────┬───────────────────────────────────────────│───────────────┘
         │ orchestrates                              │
         ▼                                          ▼
┌──────────────────────────────┐    ┌───────────────────────────────┐
│      DEVELOPMENT TEAM        │    │  ASR  (Assessor)  ★MANDATORY  │
│                              │    │  Independent from project      │
│  ┌──────────────┐  ┌──────┐  │    │  (§5.1.2.4–5.1.2.6)           │
│  │Requirements  │  │ DES  │  │    │  May be external OR internal   │
│  │   Manager    │  │Design│  │    │  at SA discretion (§5.1.2.5)  │
│  └──────────────┘  └──────┘  │    │  §5.1.2.11(k), §6.4.4.1       │
│  ┌──────┐  ┌──────┐          │    │  Reviews ALL artifacts         │
│  │ IMP  │  │ INT  │          │    │  Organisationally independent  │
│  │ Code │  │Integ.│          │    │  from REQ, DES, IMP, INT,     │
│  └──────┘  └──────┘          │    │  TST, VER, VAL (§5.1.2.11(k)) │
│  ┌──────┐  ┌──────┐          │    └───────────────────────────────┘
│  ┌──────┐  ┌──────┐          │
│  │ TST  │  │ SAF  │          │
│  └──────┘  └──────┘          │
│                              │
│  ┌──────┐  ┌──────┐          │
│  │ QUA  │  │  CM  │          │
│  └──────┘  └──────┘          │
└──────────────────────────────┘
         │ reviewed by (independence HR — reporting to PM permitted)
         ▼
┌────────────────────────────────────────────────────────────────────┐
│   VER  (Verifier)                                                  │
│   [independence: organisational separation HR — §5.1.2.11(b–e)]   │
│   MANDATORY: VER shall not also be REQ/DES/IMP/INT/TST (§5.1.2.11(h)) │
│   May report to PM (§5.1.2.11(e))                                 │
│   VER and VAL may be the same person at SIL 1–2 (§5.1.2.11(d))   │
└────────────────────────────────────────────────────────────────────┘
         │
         ▼
┌────────────────────────────────────────────────────────────────────┐
│   VAL  (Validator)                      ★ RELEASE AUTHORITY        │
│   [independence: organisational separation HR — §5.1.2.11(b–c)]   │
│   MANDATORY: VAL shall not also be REQ/DES/IMP/INT/TST (§5.1.2.11(h)) │
│   May report to PM at SIL 1–2 (§5.1.2.11(e))                     │
│   Software SHALL NOT be released without Validator sign-off        │
│   (§5.1.2.8, §6.3.4.16)                                           │
└────────────────────────────────────────────────────────────────────┘
```

**Key characteristics at SIL 1–2:**
- ASR (Assessor) is **mandatory** per §5.1.2.4; no ISO 9001 waiver applies at SIL 1–2
- **VER and VAL must not hold any development role** (REQ/DES/IMP/INT/TST) — this is a mandatory **"shall"** prohibition (§5.1.2.11(h)), independent of organisational structure
- Organisational reporting independence for VER/VAL is **HR** — they may report to PM (§5.1.2.11(e))
- VER and VAL may be the same person (§5.1.2.11(d))
- No VMGR required — VER/VAL operate under COD/PM oversight
- VAL holds release authority: no software release without Validator sign-off (§5.1.2.8, §6.3.4.16)

---

## SIL 3–4: Strict Independence Organization

Mandatory independence wall separates development from verification/validation. VMGR is a required platform-defined independent V&V authority (normative basis: §5.1.2.10(e–f)). External Assessor is mandatory per §5.1.2.4, §5.1.2.10(m), §6.4.4.1.

> **§5.1.2.10 Structure Note:** §5.1.2.10 contains both **permissive "can" clauses** (sub-clauses a–f, k–o, which describe what is structurally allowed) and **prohibitory "shall neither" clauses** (sub-clauses g–j, which establish mandatory forbidden combinations). The independence wall below is grounded specifically in the prohibitory sub-clauses (g–j). The "preferred organisational structure" preamble of §5.1.2.10 refers to the overall structural preference — it does not dilute the mandatory "shall neither" force of sub-clauses (g–j).

```
┌──────────────────────────────────────────────────────────────────────┐
│                   SAFETY AUTHORITY / CUSTOMER                        │
└───────────────┬──────────────────────────────┬───────────────────────┘
                │ governs                      │ independently reports to
                ▼                              ▼
┌───────────────────────────┐    ┌─────────────────────────────────────┐
│  COD (Lifecycle Coord.)   │◄──►│   ASR  (Assessor)  ★MANDATORY INDEP │
│  Phase gate authority     │ no │   Independent from project (§5.1.2.6)│
│  Overall lifecycle state  │rep.│   Appointed by supplier, customer,   │
│                           │    │   or Safety Authority (§5.1.2.4)     │
│                           │    │   May be external OR internal at SA  │
│                           │    │   discretion (§5.1.2.5)              │
│                           │    │   Reviews ALL artifacts              │
│                           │    │   Organisationally independent from  │
│                           │    │   PM, REQ, DES, IMP, INT, TST,      │
│                           │    │   VER, VAL (§5.1.2.10(m), §6.4.4.1) │
└──────────────┬────────────┘    └─────────────────────────────────────┘
               │ authorizes                  ▲
               │ phases                      │ receives reports
               ▼                             │
┌──────────────────────────────────────────────────────────────────────┐
│                ╔══════════════════════════════════╗                  │
│                ║   MANDATORY INDEPENDENCE WALL     ║                 │
│                ║   (§5.1.2.10(g–j))               ║                 │
│                ╚══════════════════════════════════╝                  │
│                                                                      │
│  ┌───────────────────────────┐   ║  ┌──────────────────────────────┐ │
│  │   PM  (Project Manager)   │   ║  │  VMGR  ★INDEP [platform ext] │ │
│  │  CCB · Team coord         │   ║  │  Basis: §5.1.2.10(e–f)       │ │
│  │  Reports to COD for       │   ║  │  (VAL shall not report to PM)│ │
│  │  lifecycle decisions      │   ║  │  Manages VER team            │ │
│  └───────────┬───────────────┘   ║  │  Reviews VER+VAL reports     │ │
│              │ orchestrates      ║  │  Final V&V approval          │ │
│              ▼                   ║  │  Cannot be overridden by COD │ │
│  ┌───────────────────────────┐   ║  │  or PM                       │ │
│  │    DEVELOPMENT STREAM     │   ║  └──────────┬───────────────────┘ │
│  │                           │   ║             │ manages             │
│  │  ┌──────────────┐         │   ║             ▼                     │
│  │  │Requirements  │  ┌────┐ │   ║  ┌──────────────────────────────┐ │
│  │  │   Manager    │  │DES │ │   ║  │  VER (Verifier)   ★INDEP     │ │
│  │  └──────────────┘  └────┘ │   ║  │  Static analysis             │ │
│  │  ┌──────┐  ┌──────┐       │   ║  │  Coverage checks             │ │
│  │  │ IMP  │  │ INT  │       │   ║  │  Verification reports        │ │
│  │  └──────┘  └──────┘       │   ║  │  Reports to VMGR             │ │
│  │  ┌──────┐  ┌──────┐       │   ║  └──────────────────────────────┘ │
│  │  │ TST  │  │ SAF  │       │   ║                                   │
│  │  │★indep│  └──────┘       │   ║  ┌──────────────────────────────┐ │
│  │  └──────┘                 │   ║  │  VAL (Validator) ★INDEP      │ │
│  └───────────────────────────┘   ║  │  System & acceptance tests   │ │
│                                  ║  │  SHALL NOT report to PM      │ │
│  ┌───────────────────────────┐   ║  │  (§5.1.2.10(f))              │ │
│  │  SUPPORT ROLES (no indep) │   ║  │  ★ RELEASE AUTHORITY         │ │
│  │  ┌──────┐  ┌──────┐       │   ║  │  (§5.1.2.8, §6.3.4.16)      │ │
│  │  │ QUA  │  │  CM  │       │   ║  └──────────────────────────────┘ │
│  │  └──────┘  └──────┘       │   ║                                   │
│  └───────────────────────────┘   ║                                   │
└──────────────────────────────────╚═══════════════════════════════════┘

  ★INDEP  = Organizationally and functionally INDEPENDENT (Mandatory)
  ★indep  = Independence highly recommended (HR)
  ║       = Independence boundary — role combination across this wall FORBIDDEN
  ◄──►    = Peer coordination (no reporting relationship)
  ★ RELEASE AUTHORITY = Software SHALL NOT be released without VAL sign-off
```

**Key characteristics at SIL 3–4:**
- VMGR is a **platform-defined independent authority** (not in Annex B); implements §5.1.2.10(e) "Verifier reports to Validator" option via a named V&V authority; §5.1.2.10(f) prohibits VAL from reporting to PM — Safety Authority approval required, documented in SQAP
- Hard independence wall (§5.1.2.10(g–j)): sub-clauses g–j use "shall neither" — these are mandatory prohibitions; sub-clauses a–f and k–o use "can" — these are permissive structural options
- Development roles on the left **cannot** hold VER/VAL roles on the right (§5.1.2.10(g–j))
- VER and VAL are **mandatorily organisationally independent** from all development roles
- VAL **shall not report to PM** (§5.1.2.10(f))
- ASR is **mandatory** and independent from the project per §5.1.2.6; appointed by supplier, customer, or Safety Authority (§5.1.2.4); may be external or — at Safety Authority discretion — internal to the supplier/customer organisation (§5.1.2.5); organisational independence per §5.1.2.10(m), §6.4.4.1
- COD and ASR coordinate at peer level — ASR does not report to COD
- TST independence is **HR** (Highly Recommended)
- VAL holds release authority: software **shall not** be released without Validator authorisation (§5.1.2.8, §6.3.4.16)

---

## Key Differences Summary

| Aspect | SIL 0 | SIL 1–2 | SIL 3–4 |
|---|---|---|---|
| VER role-combination prohibition | Permitted (§5.1.2.12(b)) | **Mandatory "shall"** — VER not REQ/DES/IMP/INT/TST (§5.1.2.11(h)) | **Mandatory** (§5.1.2.10(g–j)) |
| VAL role-combination prohibition | Permitted (§5.1.2.12(b)) | **Mandatory "shall"** — VAL not REQ/DES/IMP/INT/TST (§5.1.2.11(h)) | **Mandatory** (§5.1.2.10(g–j)) |
| VER/VAL organisational independence | Not required | HR — may report to PM | **Mandatory** — VAL shall not report to PM (§5.1.2.10(f)) |
| VMGR role | Not required | Not required | Platform-defined authority (basis §5.1.2.10(e–f)) |
| TST independence | Not required | HR | HR |
| ASR (Assessor) | Waivable (ISO 9001 cert) §6.4.1.2 | **Mandatory** §5.1.2.4, §5.1.2.11(k) | **Mandatory** §5.1.2.4, §5.1.2.10(m), §6.4.4.1 |
| REQ/DES/IMP+TST same component | Permitted | **Forbidden** (§5.1.2.11(f–g)) — allowed for different component (§5.1.2.13) | **Forbidden** (§5.1.2.10(g–h)) — allowed for different component (§5.1.2.13) |
| INT+TST same person (same component) | Permitted | Allowed | Allowed (§5.1.2.10(o)) |
| Organisational boundary | Informal | Informal | **Hard wall — enforced** |
| VAL release authority | **Mandatory** §6.3.4.16 | **Mandatory** §6.3.4.16 | **Mandatory** §6.3.4.16 |

---

## Role Combination Rules

### Allowed at All SIL Levels

| Combination | Notes | Reference |
|---|---|---|
| DES + IMP (same component) | Designer may also implement | §5.1.2.10(a), §5.1.2.11(a) |
| REQ + DES + IMP (same component) | Requirements Manager, Designer, Implementer may be one person | §5.1.2.10(a) |
| PM + Software Manager | Combined management role | §5.1.2.10(k), §5.1.2.11(i), §5.1.2.12(f) |
| PM + REQ/DES/IMP/INT/TST/VER (conditional) | PM may also perform these roles provided independence requirements for those roles are respected | §5.1.2.10(k), §5.1.2.11(i), §5.1.2.12(f) |
| REQ/DES/IMP (component A) + TST/INT (component B) | Cross-component: developer of one component may test/integrate a different component | §5.1.2.13 |

### Allowed at SIL 0 Only (§5.1.2.12)

| Combination | Notes | Reference |
|---|---|---|
| INT + TST + VER + VAL (same component) | All four roles may be the same person | §5.1.2.12(b) |

### Allowed at SIL 1–2 (§5.1.2.11)

| Combination | Notes | Reference |
|---|---|---|
| VER + VAL (same person) | Verifier and Validator may be the same person | §5.1.2.11(d) |
| VER or VAL reporting to PM | Both may report to Project Manager | §5.1.2.11(e) |
| INT + TST | Same person may integrate and test | §5.1.2.11(f) |

### Conditional Exceptions at SIL 1–2 (§5.1.2.11)

| Combination | Conditions | Reference |
|---|---|---|
| VER + INT + TST (same person) | Verifier may also integrate and test; VAL must then include reviewing the Verifier's output documents | §5.1.2.11(l) |
| VAL + VER + INT + TST (same person) | Validator may also be Verifier, Integrator, and Tester; VER output must be reviewed by another competent person; subject to Assessor approval | §5.1.2.11(m) |

### Conditional Exceptions at SIL 3–4 (subject to Assessor approval)

| Combination | Conditions | Reference |
|---|---|---|
| VAL + VER (same person) | Permitted if: VER output is reviewed by another competent independent person; subject to Assessor approval | §5.1.2.10(n) |
| VER + INT + TST | Verifier may also integrate and test; VAL must then check adequacy of the documented evidence | §5.1.2.10(o) |

### Forbidden — Mandatory Prohibition at All SIL Levels (SIL 0–4)

| Combination | Reason | Reference |
|---|---|---|
| REQ/DES/IMP + TST/INT (same component) | Developer shall not test or integrate the same component — applies at **all SIL levels including SIL 0** | §5.1.2.12(d), §5.1.2.10(g–h), §5.1.2.11(f–g) |
| VER/VAL + REQ/DES/IMP (any component) | Verifier/Validator shall not hold requirements, design, or implementation roles — applies at **all SIL levels including SIL 0**. **SIL 0 scope note:** At SIL 0, §5.1.2.12(e) restricts this prohibition to REQ/DES/IMP only — INT and TST are **not** included (VER/VAL+INT+TST is permitted at SIL 0 per §5.1.2.12(b)). At SIL 1–4, the prohibition extends to include INT and TST per §5.1.2.11(h) and §5.1.2.10(i–j). | §5.1.2.12(e), §5.1.2.10(i–j), §5.1.2.11(h) |

### Forbidden — Mandatory Prohibition at SIL 1–4

| Combination | Reason | Reference |
|---|---|---|
| REQ/DES/IMP/INT/TST + VER (same project) | VER shall not hold any development or test role | §5.1.2.11(h), §5.1.2.10(g–i) |
| REQ/DES/IMP/INT/TST + VAL (same project) | VAL shall not hold any development or test role | §5.1.2.11(h), §5.1.2.10(g–i) |
| Any role + ASR | Assessor must be fully independent from all project roles | §5.1.2.5–5.1.2.6, §5.1.2.10(m) |
| VAL reporting to PM (SIL 3–4) | Validator shall not report to Project Manager | §5.1.2.10(f) |

---

## Independence Reference Matrix

| Role | SIL 0 | SIL 1–2 | SIL 3–4 |
|---|---|---|---|
| Requirements Manager (REQ) | No | No | No |
| Designer (DES) | No | No | No |
| Implementer (IMP) | No | No | No |
| Integrator (INT) | No | No | No |
| Tester (TST) | No | HR | HR |
| Verifier (VER) | No (§5.1.2.12) | Role-combination prohibition: **M** / Org. separation: HR (§5.1.2.11(b–e,h)) | **Mandatory** (§5.1.2.10(g–j)) |
| Validator (VAL) | No (§5.1.2.12) | Role-combination prohibition: **M** / Org. separation: HR (§5.1.2.11(b–c,h)) | **Mandatory** (§5.1.2.10(f–j)) |
| V&V Manager (VMGR) | No | No | Platform policy (basis §5.1.2.10(e–f)) |
| Assessor (ASR) | Waivable (ISO 9001 cert) §6.4.1.2 | **Mandatory** §5.1.2.4, §5.1.2.11(k) | **Mandatory** §5.1.2.4, §5.1.2.10(m), §6.4.4.1 |
| Project Manager (PM) | No | No | No |
| Configuration Manager (CM) | No | No | No |
| Safety Engineer (SAF) | No | No | No |
| Quality Assurance (QUA) | No | No | No |

**Legend:**
- **Mandatory** = normative "shall" requirement
- **HR** = Highly Recommended — rationale required if not applied
- **No** = not required by standard
- Role-combination prohibition = person holding this role **shall not** also hold REQ/DES/IMP/INT/TST roles (applies regardless of organisational structure)
- Org. separation = organisational/reporting line independence from development

> **Role Stability (§5.1.2.14):** The roles of Verifier and Validator **shall** be defined at the project level and **shall remain unchanged** throughout the development project. This applies at all SIL levels. Any personnel change within the VER or VAL roles (including within a VMGR-managed VER team at SIL 3–4) must be formally documented and assessed.

---

*References: EN 50128:2011 §5.1.2.4–5.1.2.14, §5.1.2.9, §5.1.2.10(a–o), §5.1.2.11(a–m), §5.1.2.12(a–e), §5.1.2.13, §5.1.2.14, §6.3.4.16, §6.4.1.2, §6.4.4.1, Annex B Tables B.1–B.10*
