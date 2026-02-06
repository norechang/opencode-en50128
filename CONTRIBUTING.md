# Contributing to opencode-en50128

Thank you for your interest in contributing to the EN 50128 Railway Software Development Framework!

## Repository Status

This is a **PRIVATE** repository containing proprietary EN 50128 railway software development tools and processes.

## Access Control

- Access is restricted to authorized personnel only
- All contributors must have appropriate EN 50128 training and clearance
- Do not share repository contents outside authorized team

## Contributing Guidelines

### 1. Branch Strategy

- `main` - Stable, production-ready framework
- `develop` - Integration branch for features
- `feature/*` - Feature development branches
- `hotfix/*` - Urgent fixes to main branch

### 2. Commit Message Format

Follow conventional commits format:

```
<type>(<scope>): <subject>

<body>

<footer>
```

**Types:**
- `feat`: New feature or agent/skill
- `fix`: Bug fix
- `docs`: Documentation changes
- `style`: Code style changes (formatting, no logic change)
- `refactor`: Code refactoring
- `test`: Adding or updating tests
- `chore`: Maintenance tasks

**Examples:**
```
feat(agent): add validator agent with en50128-validation skill

Add new validator agent for EN 50128 Section 7.6 compliance.
Includes system testing, UAT, and operational scenario validation.

Resolves: #123

---

fix(skill): correct MISRA C rule reference in implementation skill

Fixed incorrect reference to MISRA C:2012 Rule 10.1

---

docs(readme): update installation instructions

Add detailed setup steps for PC-lint Plus integration
```

### 3. Code Review Process

All changes require code review:

1. Create feature branch from `develop`
2. Make changes following EN 50128 standards
3. Run verification checks (see below)
4. Create pull request to `develop`
5. Address review comments
6. Obtain approval from:
   - For agent/skill changes: QA + Safety reviewer
   - For documentation: Technical writer
   - For tools: Verification engineer
7. Merge after approval

### 4. Pre-Commit Checks

Before committing, ensure:

**For Skills:**
- [ ] YAML frontmatter is valid
- [ ] Skill name matches directory name
- [ ] Examples are MISRA C compliant
- [ ] Documentation is complete

**For Agents:**
- [ ] Command file references correct skill
- [ ] Role definition is clear
- [ ] EN 50128 section referenced
- [ ] Output artifacts listed

**For Code Examples:**
- [ ] MISRA C:2012 compliant
- [ ] Defensive programming applied
- [ ] Fixed-width types used
- [ ] Error handling present

**For Documentation:**
- [ ] Markdown formatting correct
- [ ] No broken links
- [ ] Standard references accurate
- [ ] Examples tested

### 5. Verification Script

Run before committing:

```bash
# Verify agent-skill links
bash tools/verify_links.sh

# Check MISRA compliance of examples
python3 tools/static-analysis/check_misra.py src/ 3

# Validate YAML frontmatter
python3 tools/validate_skills.py
```

### 6. Pull Request Template

When creating a PR, include:

```markdown
## Description
[What does this PR do?]

## Type of Change
- [ ] New feature (agent/skill)
- [ ] Bug fix
- [ ] Documentation update
- [ ] Refactoring
- [ ] Tool improvement

## EN 50128 Compliance
- [ ] Follows EN 50128 requirements
- [ ] Appropriate for SIL level: [0/1/2/3/4]
- [ ] Safety reviewed (if applicable)

## Testing
- [ ] Examples tested
- [ ] Verification scripts pass
- [ ] Documentation reviewed

## Checklist
- [ ] YAML frontmatter valid
- [ ] MISRA C compliant (where applicable)
- [ ] Documentation updated
- [ ] CHANGELOG.md updated
- [ ] No sensitive information exposed

## Related Issues
Closes #[issue number]
```

### 7. File Organization

When adding new content:

**Agents:**
```
.opencode/commands/[agent-name].md
```

**Skills:**
```
.opencode/skills/en50128-[name]/
└── SKILL.md
```

**Documentation:**
```
docs/[topic-name].md
```

**Tools:**
```
tools/[category]/[tool-name]
```

### 8. Standards Compliance

All contributions must comply with:

- EN 50128:2011 Railway Software Standard
- MISRA C:2012 (for code examples)
- EN 50126 RAMS requirements
- IEC 61508 (referenced sections)

### 9. Safety-Critical Considerations

When contributing to safety-critical components:

1. **Requirements Traceability**: Link to requirements
2. **Hazard Analysis**: Consider safety implications
3. **Independent Review**: Require independent verification for SIL 3-4
4. **Documentation**: Maintain comprehensive documentation
5. **Testing**: Ensure adequate test coverage

### 10. Prohibited Content

**Never commit:**
- Personal credentials or API keys
- Proprietary customer data
- Unreviewed safety-critical code
- Copyrighted material without permission
- Large binary files (>10MB)

### 11. Issue Reporting

When reporting issues:

1. Check existing issues first
2. Use issue template
3. Provide minimal reproducible example
4. Include environment details
5. Tag with appropriate labels

### 12. Communication

- Technical discussions: GitHub Issues
- Security issues: Direct to repository owner (private)
- General questions: Team chat or email

## Questions?

Contact the repository maintainer or safety manager for questions about:
- EN 50128 compliance
- Safety requirements
- Process questions
- Tool usage

## License

This repository is proprietary. See LICENSE file for details.

---

**Remember:** Safety comes first. When in doubt about EN 50128 compliance, always consult with the safety team before committing changes.
