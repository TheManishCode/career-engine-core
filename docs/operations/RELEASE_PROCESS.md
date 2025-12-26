# Release Process — Career Engine Core

## Purpose of This Document

This document defines the **authoritative release process** for the
Career Engine.

It specifies:
- How releases are prepared
- What validation gates must pass
- How versions are finalized
- What artifacts are produced
- What must never be skipped

A release that does not follow this process is **invalid**.

---

## Release Philosophy

Releases are **deliberate events**, not side effects of development.

The release process exists to:
- Preserve user trust
- Protect security guarantees
- Ensure determinism and reproducibility
- Prevent accidental breaking changes

Speed is never prioritized over correctness.

---

## Release Types

The engine supports three release types:

- **PATCH Release** — Bug fixes, security fixes, documentation
- **MINOR Release** — Backward-compatible features and improvements
- **MAJOR Release** — Breaking changes or compatibility resets

Release type must align with `VERSIONING.md`.

---

## Preconditions for Any Release

Before initiating a release:

- All tests must pass
- No known security issues remain
- Documentation must be up to date
- Version number must be agreed upon
- Release scope must be frozen

Unstable or incomplete work must not be released.

---

## Release Preparation Steps

### 1. Version Finalization

- Update version number according to `VERSIONING.md`
- Ensure version change is intentional and justified
- No further feature changes after version bump

Version bumps must occur in a dedicated commit.

---

### 2. Documentation Verification

Verify that:
- Changelog is complete
- Breaking changes (if any) are documented
- Security notes are included
- Migration notes exist (for MAJOR releases)

Incomplete documentation blocks release.

---

### 3. Test Validation (MANDATORY)

The following must pass:

- Unit tests
- Integration tests (if applicable)
- Security-related tests
- Determinism checks

Test failures are release blockers.

---

### 4. Static Analysis & Tooling

Before release:
- Enable compiler warnings as errors
- Run static analysis tools
- Ensure no new warnings are introduced

Warnings in release builds are unacceptable.

---

### 5. Build Verification

- Clean build from scratch
- Deterministic build verification
- No network access during build
- No environment-specific behavior

Builds must be reproducible.

---

## Release Execution Steps

### 6. Release Commit

- Create a dedicated release commit
- No unrelated changes in this commit
- Commit message must reference version

Release commits must be clean and auditable.

---

### 7. Tagging

- Create an immutable version tag
- Tag must match version exactly
- Tags must point to release commit

Retagging or tag mutation is forbidden.

---

### 8. Artifact Generation

If applicable, generate:
- Static libraries
- Headers
- Checksums

Artifacts must correspond exactly to the tagged source.

---

## Post-Release Steps

### 9. Verification

After release:
- Verify tagged build matches released artifacts
- Verify documentation is published
- Verify no accidental changes slipped in

Discrepancies must be investigated immediately.

---

### 10. Communication

For each release:
- Publish release notes
- Highlight breaking changes clearly
- Highlight security fixes clearly

Silence is unacceptable for breaking changes.

---

## Rollback Policy

If a release is found to be faulty:

- Do not delete or rewrite release history
- Issue a follow-up PATCH release
- Document the issue transparently

Rewriting history breaks trust.

---

## Emergency Security Releases

For critical vulnerabilities:

- Follow PATCH release flow
- Minimize scope to fix only
- Document the vulnerability
- Encourage immediate upgrade

Security fixes must still follow discipline.

---

## Automation Expectations

CI/CD may automate:
- Testing
- Building
- Tag verification

Automation must never:
- Skip validation steps
- Modify source behavior
- Hide failures

Automation enforces discipline, it does not replace it.

---

## LLM-Specific Rules

AI coding assistants must:
- Never auto-bump versions
- Never auto-tag releases
- Never bypass release gates
- Flag changes that may affect release type

Release decisions require human intent.

---

## Release Checklist (FINAL)

Before publishing a release, confirm:

- [ ] Version number is correct
- [ ] All tests pass
- [ ] Security rules are upheld
- [ ] Documentation is complete
- [ ] Tag is correct and immutable

If any box is unchecked, do not release.

---

## Final Release Rule

Releases define reputation.

A careful release process is not bureaucracy —
it is respect for users, contributors, and future maintainers.
