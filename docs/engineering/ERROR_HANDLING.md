# Error Handling — Career Engine Core

## Purpose of This Document

This document defines **how errors must be represented, propagated,
and handled** throughout the Career Engine.

Error handling in this engine is a **design concern**, not an afterthought.
If code violates these rules, it must be rewritten.

---

## Error Handling Philosophy

Errors are part of normal operation.

The engine must:
- Detect errors early
- Surface errors explicitly
- Avoid hidden recovery
- Preserve determinism under failure

Silent failure is worse than loud failure.

---

## What Constitutes an Error

Errors include:
- Invalid or malformed input
- Rule evaluation failures
- Security violations
- Encryption or key failures
- Storage failures
- Invariant violations

Unexpected states are errors, not edge cases.

---

## Error Representation

### Explicit Error Types (Preferred)

Errors should be represented using:
- Structured error types
- Enumerated error codes
- Descriptive error messages

Errors must be machine-readable and human-understandable.

---

### Return-Based Error Propagation

Preferred patterns:
- `std::expected<T, Error>`
- Explicit error-return objects
- Result types with status

Exceptions must not be used for normal control flow.

---

## Exception Usage (RESTRICTED)

Exceptions may be used only for:
- Truly exceptional conditions
- Programming errors that indicate bugs

Rules:
- Exceptions must not cross module boundaries
- Destructors must never throw
- Exceptions must not carry sensitive data

If exception usage is unclear, do not use exceptions.

---

## Error Propagation Rules

- Errors propagate upward immediately
- No swallowing or masking errors
- No retry loops without explicit justification
- No fallback to unsafe behavior

Fail fast, fail clearly.

---

## Error Context Requirements

Every error must include:
- Error code or type
- Originating module
- Operation being performed

Error messages must NOT include:
- Sensitive data
- User data
- Internal secrets

---

## Fail-Closed Principle

On error:
- Abort the current operation
- Prevent partial output
- Preserve data integrity
- Maintain safe defaults

Never continue execution in an uncertain state.

---

## Boundary Error Handling

At module boundaries:
- Validate inputs
- Translate internal errors to public error types
- Avoid leaking implementation details

Public APIs must document all possible error conditions.

---

## Logging & Errors

- Logging errors is optional
- Logged errors must be sanitized
- Logs must not be relied upon for correctness

Error handling must not depend on logging.

---

## Error Handling in Tests

Tests must:
- Explicitly check error conditions
- Validate error codes and messages
- Cover failure paths

Untested error paths are bugs.

---

## Forbidden Error Practices (ABSOLUTE)

The following are strictly forbidden:

- Ignoring return values
- Catch-and-ignore blocks
- Implicit error conversion
- Logging instead of returning errors
- Using assertions for recoverable errors

Violations are defects.

---

## LLM-Specific Rules

AI coding assistants must:
- Prefer explicit error types
- Avoid exceptions by default
- Never assume operations succeed
- Surface errors explicitly

If uncertain, return an error.

---

## Final Error Handling Rule

Errors define system behavior under stress.

If error handling is unclear, inconsistent,
or hidden, the design is wrong and must be fixed.
