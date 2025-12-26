# Testing Strategy — Career Engine Core

## Purpose of This Document

This document defines **how testing is designed, structured, and enforced**
for the Career Engine.

Testing is not optional.
Testing is the primary mechanism that protects:
- Determinism
- Security guarantees
- Architectural boundaries
- Long-term maintainability

Code without tests is considered **incomplete**.

---

## Testing Philosophy

The Career Engine follows a **defensive testing philosophy**.

Principles:
- Tests validate intent, not implementation quirks
- Deterministic behavior must be provable
- Failure paths must be tested as rigorously as success paths
- Security assumptions must be testable

If behavior cannot be tested, it cannot be trusted.

---

## Testing Scope

Testing applies to:
- Core logic
- Security primitives
- Error handling
- Boundary conditions
- Regression prevention

Testing does NOT apply to:
- UI (out of scope)
- Network behavior (out of scope)
- External services (out of scope)

---

## Test Types (AUTHORITATIVE)

### 1. Unit Tests (MANDATORY)

#### Purpose
Validate individual components in isolation.

#### Requirements
- One module per test suite
- No shared global state
- No external dependencies
- Deterministic input/output

#### Coverage
- Classifier rules
- Noise filter rules
- Lifecycle transitions
- Utility functions
- Error conditions

Unit tests are the foundation of trust.

---

### 2. Integration Tests (RESTRICTED)

#### Purpose
Validate interactions between modules.

#### Requirements
- Limited scope
- Explicit setup and teardown
- No I/O unless explicitly mocked
- Deterministic behavior only

#### Coverage
- Engine pipeline execution
- Module orchestration
- Security + storage interaction

Integration tests must not replace unit tests.

---

### 3. Security Tests (MANDATORY)

#### Purpose
Validate security guarantees.

#### Coverage
- Encryption/decryption correctness
- Authentication gate enforcement
- Key lifecycle behavior
- Memory zeroization
- Fail-closed behavior

Security code without tests is a vulnerability.

---

### 4. Negative & Failure Tests (MANDATORY)

#### Purpose
Ensure correct behavior under failure.

#### Coverage
- Invalid input
- Malformed data
- Missing authorization context
- Storage failure
- Encryption failure

Failure tests are first-class tests.

---

### 5. Regression Tests (MANDATORY)

#### Purpose
Prevent reintroduction of fixed bugs.

Rules:
- Every bug fix must include a regression test
- Regression tests must fail before the fix
- Regression tests must pass after the fix

No regression test → no bug fix acceptance.

---

## Determinism Testing

The engine must be provably deterministic.

Rules:
- Same input → same output
- Tests must assert exact output equality
- No tolerance-based comparisons for logic

Non-deterministic tests indicate design flaws.

---

## Test Data Rules

- Use synthetic test data
- Do not use real emails
- Do not use personal data
- Do not embed sensitive content

Test data must be safe, minimal, and reproducible.

---

## Mocking & Stubbing Rules

Allowed:
- Mock storage interfaces
- Stub encryption boundaries (carefully)
- Fake authorization contexts

Forbidden:
- Mocking core business logic
- Mocking rule evaluation
- Mocking determinism

Mocks must not hide logic errors.

---

## Test Structure Guidelines

Recommended structure:

tests/
├── unit/
│ ├── classifier/
│ ├── noise_filter/
│ ├── lifecycle/
│ └── utils/
├── integration/
│ └── engine_pipeline/
├── security/
│ ├── encryption/
│ ├── auth/
│ └── key_management/
└── regression/


Structure clarity improves test reliability.

---

## Performance Testing (LIMITED)

Performance tests may exist to:
- Detect regressions
- Validate complexity assumptions

Rules:
- Performance tests must not be flaky
- Performance tests must not assert exact timings
- Performance tests must not weaken safety checks

Performance testing complements correctness testing.

---

## Tooling Expectations

Tests should assume:
- Warnings treated as errors
- Sanitizers may be enabled
- Debug and release builds tested

Tests must pass under strict tooling.

---

## CI Expectations

CI must:
- Run all tests on every change
- Block merges on test failure
- Provide deterministic results

CI is a gatekeeper, not a suggestion.

---

## LLM-Specific Rules

AI coding assistants must:
- Generate tests for new logic
- Update tests when behavior changes
- Never remove tests to “fix” failures
- Treat tests as part of the feature

If unsure how to test, ask before coding.

---

## Test Review Checklist

Before merging code, verify:
- New logic has tests
- Failure paths are covered
- Determinism is asserted
- Security behavior is tested
- No test relies on undefined behavior

If any check fails, the change is incomplete.

---

## Final Testing Rule

Tests are executable documentation.

If the behavior of the engine cannot be demonstrated
through tests, the behavior is not real.
