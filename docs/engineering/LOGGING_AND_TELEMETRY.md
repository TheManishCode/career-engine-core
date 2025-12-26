# Logging & Telemetry — Career Engine Core

## Purpose of This Document

This document defines **what may and may not be logged** by the Career Engine
and establishes strict boundaries around telemetry.

Logging mistakes are **security incidents**, not minor bugs.

If code violates this document, it must be corrected immediately.

---

## Logging Philosophy

The Career Engine is:
- A local-first library
- Security-sensitive
- Privacy-preserving by default

Therefore:
- Logging is optional
- Telemetry is disabled by default
- Silence is safer than verbosity

Logs exist to aid debugging, not to observe users.

---

## What Logging Is For

Logging may be used to:
- Signal internal failures
- Surface invariant violations
- Aid development and testing
- Provide high-level diagnostic information

Logging must NEVER be required for correct behavior.

---

## What MUST NOT Be Logged (ABSOLUTE)

The engine must NEVER log:

- Email content (full or partial)
- Email metadata (sender, subject, recipients)
- Career classifications
- Job lifecycle state
- Confidence scores
- Encryption keys or secrets
- Tokens or credentials
- Authorization context
- User identifiers
- Derived intelligence of any kind

Logging any of the above is a critical defect.

---

## What MAY Be Logged (WITH CARE)

Allowed log content includes:

- High-level error codes
- Module-level failure indicators
- Sanitized, non-identifying messages
- Internal state transitions without data values

Examples:
- "Storage initialization failed"
- "Rule evaluation error in classifier module"

All messages must be generic.

---

## Log Levels

If log levels are supported, they must be limited to:

- ERROR — unrecoverable failures
- WARN — recoverable anomalies
- INFO — high-level engine status (optional)
- DEBUG — development-only diagnostics

Rules:
- DEBUG logs must be disabled in production builds
- ERROR/WARN logs must not expose sensitive data

---

## Telemetry Rules (STRICT)

The engine must NOT:
- Emit telemetry
- Collect analytics
- Phone home
- Send metrics externally
- Persist usage data

Telemetry is **out of scope** for this repository.

Any telemetry must be implemented by the calling application,
outside the engine.

---

## Configuration Rules

- Logging must be explicitly enabled by the caller
- Logging must be configurable at compile or runtime
- Default configuration must be minimal or silent

Implicit logging is forbidden.

---

## Log Storage Rules

If logs are stored:
- Storage is managed by the caller
- The engine must not manage log files
- Logs must not persist sensitive data

The engine must treat logging as best-effort only.

---

## Error Handling vs Logging

- Errors must be returned explicitly
- Logging must not replace error handling
- Logging must not affect control flow

If behavior depends on logging, the design is wrong.

---

## LLM-Specific Rules

AI coding assistants must:
- Avoid adding logs by default
- Never log data values
- Prefer returning errors over logging
- Treat logging as optional and minimal

If unsure, do not log.

---

## Audit & Review Checklist

Before merging logging-related code, verify:
- No sensitive data is logged
- Logs are generic and sanitized
- Logging is optional and configurable
- Telemetry is not introduced

Any uncertainty requires removal of logging.

---

## Final Logging Rule

Logs must never expose user data,
engine intelligence, or security-sensitive information.

If logging feels helpful but risky,
**do not log**.
