# Secure Coding Rules — Career Engine Core

## Purpose of This Document

This document defines **non-negotiable secure coding rules** for the
Career Engine.

These rules apply to:
- All production code
- All test code
- All generated code (including AI-assisted code)

If any rule is violated, the code must be fixed or rejected.

---

## Secure Coding Philosophy

Security failures in this engine can cause:
- Loss of critical career data
- Incorrect career decisions
- Loss of user trust

Therefore:
- Security is mandatory
- Defensive coding is expected
- Convenience is never an excuse

---

## 1. Input Handling Rules

### All Inputs Are Untrusted

- All external input must be validated
- All input must be sanitized before use
- Never assume correctness of input structure or content

Examples of untrusted input:
- Email text
- Metadata fields
- Identifiers
- Timestamps

---

### Validation Rules

- Validate length, format, and type
- Reject malformed input early
- Avoid partial validation

If validation fails, **fail closed**.

---

## 2. Error Handling Rules

### Explicit Error Propagation

- Errors must be returned explicitly
- Errors must include context
- Silent failure is forbidden

---

### No Catch-and-Ignore

- Never catch exceptions and continue silently
- Never suppress errors to “keep going”

If recovery is not safe, abort the operation.

---

## 3. Logging Rules (CRITICAL)

### What Must NOT Be Logged

The engine must NEVER log:
- Email content
- Decrypted data
- Encryption keys
- Tokens or credentials
- Authorization context
- User-identifiable data

---

### What May Be Logged

Allowed (with care):
- High-level error codes
- Non-sensitive status indicators
- Sanitized diagnostics

Logs must be:
- Minimal
- Non-identifying
- Optional

---

## 4. Resource Management Rules

- All resources must use RAII
- All cleanup must be deterministic
- No resource leaks on failure paths

If cleanup logic is complex, redesign the code.

---

## 5. Control Flow Rules

- Avoid deeply nested logic
- Avoid complex condition chains
- Prefer early returns on error
- Avoid undefined behavior paths

Clear control flow improves security.

---

## 6. API Design Rules

- Public APIs must validate inputs
- Public APIs must document failure modes
- Public APIs must avoid exposing internals

Breaking API invariants is a security risk.

---

## 7. Configuration Rules

- No magic numbers
- No hidden configuration flags
- No undocumented behavior switches

Configuration must be explicit and documented.

---

## 8. Testing & Security

Security-relevant code must:
- Have unit tests
- Test failure paths
- Test boundary conditions
- Avoid relying on undefined behavior

Tests must not weaken security assumptions.

---

## 9. Forbidden Coding Practices (ABSOLUTE)

The following are strictly forbidden:

- Hardcoded secrets
- Debug backdoors
- Hidden feature flags
- Unsafe C APIs
- Dynamic code execution
- Reflection-based behavior
- Undefined behavior reliance

Any occurrence is a critical defect.

---

## 10. LLM-Specific Rules

AI coding assistants must:
- Follow all security documents
- Avoid “clever” shortcuts
- Prefer explicit, boring code
- Ask for clarification if unsure

Generated code must be reviewed as untrusted input.

---

## Secure Review Checklist

Before merging code, verify:
- Inputs validated
- Errors explicit
- No sensitive logging
- Memory safety preserved
- Security rules respected

If any item fails, the code must not be merged.

---

## Final Secure Coding Rule

Security is not optional.

If a piece of code:
- Is hard to reason about
- Is hard to test
- Relies on undefined behavior

Then it is insecure by definition and must be rewritten.
