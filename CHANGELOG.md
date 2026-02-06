# Changelog

All notable changes to the EN 50128 Railway Software Development Framework will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Planned
- Tool integration examples (CMake, Jenkins CI/CD)
- Example C project with complete workflow
- Hardware-in-the-loop (HIL) test framework
- Automated traceability matrix generation
- Safety case template generator

## [1.0.0] - 2026-02-06

### Added - Initial Release

#### Core Framework
- EN 50128 compliant role-based agent architecture
- 8 specialized agents for complete SDLC coverage
- 9 domain-specific skills with EN 50128 patterns
- Complete agent-skill linking mechanism
- C language as primary development language (MISRA C:2012)
- Python for tooling support only

#### Agents (.opencode/commands/)
- **REQ** - Requirements Engineer (EN 50128 Section 7.2)
- **DES** - Designer (EN 50128 Section 7.3)
- **IMP** - Implementer (EN 50128 Section 7.4)
- **TST** - Tester (EN 50128 Sections 7.4, 7.5)
- **SAF** - Safety Engineer (EN 50128 Section 7.1)
- **VER** - Verifier (EN 50128 Section 6.4)
- **VAL** - Validator (EN 50128 Section 7.6)
- **QUA** - Quality Assurance (EN 50128 Section 6.3)

#### Skills (.opencode/skills/)
- **en50128-requirements** - Requirements engineering patterns
- **en50128-design** - C architecture and design patterns
- **en50128-implementation** - MISRA C:2012 programming patterns
- **en50128-testing** - Unity test framework with coverage analysis
- **en50128-safety** - FMEA, FTA, and safety patterns
- **en50128-verification** - Static analysis (PC-lint, Cppcheck, Lizard)
- **en50128-validation** - System testing and UAT
- **en50128-quality** - Code reviews, SQAP, audits
- **en50128-documentation** - EN 50128 document templates (shared)

#### Static Analysis Tools
- PC-lint Plus configuration (pclint.lnt)
- Cppcheck project configuration with MISRA addon
- Python-based MISRA compliance checker
- Cyclomatic complexity verification script

#### Documentation
- Comprehensive README with quick start
- EN 50128 Compliance Guide
- Project Structure documentation
- Quick Reference guide
- Complete Agent-Skill Mapping documentation
- Agent-Skill Linking Summary
- Visual diagrams of architecture
- AGENTS.md with role definitions

#### Standards Support
- EN 50128:2011 Railway Software Standard
- EN 50126:2017 RAMS (Part 1 and Part 2)
- MISRA C:2012 Coding Standard
- IEC 61508 references

#### Development Constraints by SIL
- **SIL 0-1**: Cyclomatic complexity ≤ 20
- **SIL 2**: Cyclomatic complexity ≤ 15, MISRA C mandatory, 100% statement+branch coverage
- **SIL 3-4**: Cyclomatic complexity ≤ 10, independent V&V, 100% MC/DC coverage, no dynamic memory

#### Key Features
- Fixed-width type enforcement (uint8_t, uint16_t, not int/long)
- Static memory allocation only (SIL 2+)
- Comprehensive error handling patterns (error_t return types)
- Defensive programming patterns (NULL checks, range validation)
- No recursion (highly recommended SIL 3-4)
- No dynamic allocation (malloc/free forbidden for SIL 2+)

#### Template Structure
- Source code organization (src/)
- Test framework structure (src/test/)
- Hardware abstraction layer (src/hal/)
- Safety functions (src/safety/)
- Configuration management structure

#### Build System Support
- Makefile templates
- CMake configuration examples
- Tool integration scripts

#### Quality Assurance
- Code review checklists (MISRA C, defensive programming)
- Design review checklists
- Process audit checklists
- Quality gate definitions
- Metrics collection scripts

### Repository Structure
```
EN50128/
├── .opencode/          # OpenCode configuration
│   ├── commands/       # 8 agent command files
│   └── skills/         # 9 skill modules
├── docs/               # Comprehensive documentation
├── src/                # Source code structure
├── tools/              # Static analysis tools
├── templates/          # Document templates
├── std/                # Reference standards (PDFs - excluded from git)
├── AGENTS.md           # Agent definitions
├── README.md           # Project overview
├── CONTRIBUTING.md     # Contribution guidelines
├── LICENSE             # Proprietary license
├── CHANGELOG.md        # This file
└── .gitignore          # Git ignore rules
```

### Notes
- This is a private repository with restricted access
- All standard PDFs (EN 50128, EN 50126) excluded from version control due to copyright
- Framework designed specifically for OpenCode integration
- Focus on C language for safety-critical railway software
- Python relegated to non-safety-critical tooling only

### Dependencies
- OpenCode (for agent framework)
- Git (for version control)
- GCC/Clang (for C compilation)
- PC-lint Plus (optional, commercial - MISRA C checking)
- Cppcheck (optional, open-source - static analysis)
- Lizard (optional - complexity analysis)
- gcov/lcov (optional - coverage analysis)
- Unity (optional - unit testing framework for C)

### Compatibility
- EN 50128:2011 compliant
- MISRA C:2012 compliant
- OpenCode compatible
- SIL 0-4 support

### Known Limitations
- Condition/decision coverage (MC/DC) requires commercial tools (VectorCAST, Bullseye)
- PC-lint Plus is commercial software (license required)
- Some advanced FTA analysis may require specialized tools
- Hardware-in-the-loop testing requires target hardware

## Version History

### Version Numbering
- **Major** (X.0.0): Significant framework changes, new agents, breaking changes
- **Minor** (0.X.0): New skills, enhanced features, backward compatible
- **Patch** (0.0.X): Bug fixes, documentation updates, minor improvements

### Upcoming Versions (Planned)

#### [1.1.0] - TBD
- Example C project: Train door control system
- Complete workflow demonstration
- CMake build system integration
- Jenkins CI/CD pipeline example

#### [1.2.0] - TBD
- Additional skills for tool qualification
- Extended FMEA/FTA templates
- Automated report generation
- Traceability tool integration

#### [2.0.0] - TBD
- Multi-language support (add C++)
- Extended SIL 4 guidance
- Formal methods integration (Frama-C, CBMC)
- Safety case automation

---

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines on how to contribute to this project.

## Questions or Issues?

For questions about:
- **EN 50128 Compliance**: Contact Safety Manager
- **Technical Issues**: Create GitHub issue
- **Access/Licensing**: Contact Repository Owner

## References

- EN 50128:2011 - Railway Applications - Software for Railway Control and Protection Systems
- EN 50126-1:2017 - Railway Applications - The Specification and Demonstration of RAMS - Part 1: Generic RAMS Process
- EN 50126-2:2017 - Railway Applications - The Specification and Demonstration of RAMS - Part 2: Systems Approach to Safety
- MISRA C:2012 - Guidelines for the Use of the C Language in Critical Systems (Third Edition)
- IEC 61508 - Functional Safety of Electrical/Electronic/Programmable Electronic Safety-related Systems

---

**Repository**: opencode-en50128 (Private)  
**Maintained by**: [Your Organization Name]  
**Last Updated**: 2026-02-06
