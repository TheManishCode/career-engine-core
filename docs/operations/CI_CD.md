# CI/CD — Career Engine Core

## Purpose of This Document

This document defines the **Continuous Integration and Continuous Delivery (CI/CD)**
rules for the Career Engine repository.

CI/CD exists to:
- Enforce engineering discipline
- Prevent insecure or unstable code from merging
- Guarantee determinism and reproducibility
- Protect long-term maintainability

If a change bypasses CI/CD rules, it must not be merged.

---

## CI/CD Philosophy

CI/CD is a **gatekeeper**, not a convenience tool.

Principles:
- Every change is validated automatically
- Failures block progress
- Automation enforces standards, humans define intent
- No “temporary” bypasses

Green CI is a requirement, not a suggestion.

---

## Scope of CI/CD

CI/CD applies to:
- All production code
- All test code
- All documentation changes (where applicable)
- All AI-generated code

No exceptions.

---

## Continuous Integration (CI)

### Trigger Conditions

CI must run on:
- Every pull request
- Every push to protected branches
- Every merge into main branches

CI must not be optional.

---

### CI Pipeline Stages (MANDATORY)

CI must include the following stages **in order**:

---

### 1. Source Validation

- Ensure repository structure is intact
- Ensure required files exist
- Validate formatting rules (if applicable)

Structural violations fail CI immediately.

---

### 2. Build (Clean)

- Build from a clean state
- No cached artifacts
- No network access during build
- Deterministic build configuration

If build is not reproducible, CI must fail.

---

### 3. Static Analysis

- Enable compiler warnings as errors
- Run static analysis tools
- Detect undefined behavior risks
- Detect security-relevant issues

Warnings are treated as failures.

---

### 4. Unit Tests

- Run all unit tests
- Enforce deterministic results
- No flaky tests allowed

Test failures block merges.

---

### 5. Integration Tests (If Present)

- Validate module interactions
- Validate pipeline execution
- Validate security boundaries

Integration test failures block merges.

---

### 6. Security Tests

- Encryption tests
- Authentication gate tests
- Key lifecycle tests
- Memory safety checks (sanitizers if enabled)

Security test failures are critical blockers.

---

### 7. Determinism Verification

- Same inputs produce same outputs
- No hidden state or randomness detected
- No time-dependent logic

Non-determinism is a hard failure.

---

## CI Failure Policy

When CI fails:
- The failure must be fixed before merge
- CI must not be bypassed
- “Fix later” is not acceptable

Temporary disabling of CI is forbidden.

---

## Continuous Delivery (CD)

### Definition

CD refers to **release preparation**, not auto-deployment.

The Career Engine does NOT:
- Auto-deploy
- Auto-publish binaries
- Auto-tag releases

Human intent is required for releases.

---

### CD Responsibilities

CD may:
- Validate release readiness
- Generate artifacts
- Verify versioning
- Prepare release metadata

CD must never:
- Publish without approval
- Change source code
- Modify version numbers automatically

---

## Branching & Protection Rules

### Protected Branches

Protected branches must:
- Require passing CI
- Require code review
- Disallow force-push
- Disallow direct commits

Main branches are sacred.

---

### Pull Request Requirements

Each PR must:
- Pass full CI
- Include tests for new logic
- Respect documentation rules
- Avoid scope creep

PRs without CI success must not be merged.

---

## Versioning & CI/CD

CI/CD must:
- Validate version changes against `VERSIONING.md`
- Flag potential breaking changes
- Prevent accidental version drift

CI must not auto-bump versions.

---

## Artifact Handling

If artifacts are generated:
- Artifacts must be reproducible
- Artifacts must match source exactly
- Checksums should be generated

Artifacts without traceability are invalid.

---

## Secrets & CI/CD

CI/CD must:
- Never expose secrets in logs
- Never store secrets in plaintext
- Use secure secret injection mechanisms
- Avoid unnecessary secret access

Secrets leakage is a critical incident.

---

## CI/CD Configuration Rules

- CI configuration must be version-controlled
- CI scripts must be deterministic
- CI must not rely on external mutable state

CI behavior must be inspectable and auditable.

---

## LLM-Specific Rules

AI coding assistants must:
- Assume CI will enforce all rules
- Avoid suggesting CI bypasses
- Generate code that passes CI by design
- Respect test and security requirements

If a suggestion would fail CI, it is invalid.

---

## CI/CD Review Checklist

Before merging changes to CI/CD:
- Does it strengthen enforcement?
- Does it reduce risk?
- Does it preserve determinism?
- Does it avoid bypass mechanisms?

Weakening CI/CD is forbidden.

---

## Final CI/CD Rule

CI/CD protects the integrity of the project.

If CI/CD is bypassed,
every guarantee in this repository becomes meaningless.
