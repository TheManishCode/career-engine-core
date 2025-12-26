# Authentication & Access Control — Career Engine Core

## Purpose of This Document

This document defines **how authentication and access control are handled**
within the Career Engine.

It clarifies:
- What “authentication” means for a core engine
- How access to sensitive operations is gated
- What the engine is responsible for
- What the engine must explicitly NOT do

If implementation contradicts this document,
the implementation is incorrect.

---

## Authentication Philosophy

The Career Engine is **not an application** and **not a user-facing system**.

Therefore:
- The engine does NOT authenticate users in the traditional sense
- The engine relies on the **calling application** to establish identity
- The engine enforces **capability-based access**, not user login flows

Authentication in this engine is about **protecting sensitive operations**,
not managing identities.

---

## What Authentication Means in This Engine

Authentication in the Career Engine refers to:

- Gating access to sensitive engine capabilities
- Protecting encryption keys and secrets
- Preventing accidental or unsafe usage
- Ensuring explicit caller intent

It does NOT mean:
- Login screens
- Password prompts
- OAuth flows
- Session management
- Identity providers

---

## Responsibility Split (CRITICAL)

### Engine Responsibilities

The engine MUST:
- Enforce access control for sensitive operations
- Require explicit authorization context from the caller
- Protect secrets and keys internally
- Fail closed when authorization context is missing or invalid

---

### Caller Responsibilities

The calling application MUST:
- Authenticate the user (if needed)
- Decide when sensitive operations are allowed
- Provide explicit authorization context to the engine
- Handle user interaction and consent

The engine must never assume user intent.

---

## Authorization Context Model

Sensitive operations must require an explicit
**Authorization Context** object.

Examples of sensitive operations:
- Accessing decrypted sensitive data
- Persisting encrypted data
- Deleting or modifying critical career state
- Exporting or exposing engine outputs

Rules:
- Authorization context must be explicit
- No implicit or global authorization state
- No default “allow” behavior

---

## Access Control Rules

### 1. Explicit Consent Requirement

Operations that may cause irreversible effects must:
- Require explicit caller intent
- Require re-authorization context
- Be clearly documented

Silent authorization is forbidden.

---

### 2. Least Privilege Principle

Authorization context must:
- Grant only the minimum required capability
- Be scoped to a specific operation
- Be time-limited where applicable

Broad or unlimited access is forbidden.

---

### 3. No Global Authentication State

The engine must NOT:
- Maintain global authentication state
- Cache authorization across calls
- Assume previous authorization remains valid

Each sensitive operation must be independently authorized.

---

## Key Access Rules

- Encryption keys must never be accessible directly
- Key usage must be mediated by the security layer
- Callers must never receive raw key material
- Key access must be minimal and auditable

Keys are capabilities, not data.

---

## Failure Handling

If authentication or authorization fails:
- The engine must fail closed
- No partial operation may occur
- No sensitive data may be exposed
- Clear error information must be returned

Fallback behavior is forbidden.

---

## Auditability

The engine should support:
- Explicit signaling of authorization failures
- Clear distinction between auth errors and logic errors

However:
- The engine must NOT log sensitive authorization data
- The engine must NOT persist audit logs by default

Audit policy is owned by the caller.

---

## Forbidden Practices (ABSOLUTE)

The following are strictly forbidden:

- Storing passwords
- Prompting users for credentials
- Implementing OAuth or SSO
- Managing user sessions
- Persisting authorization state
- Granting implicit access
- Logging sensitive auth data

Violations indicate misuse of the engine.

---

## LLM-Specific Rules

AI coding assistants must:
- Treat authorization as explicit input
- Never invent authentication mechanisms
- Never assume a user is authenticated
- Ask for clarification if access rules are unclear

If unsure, deny access by default.

---

## Final Authentication Rule

The Career Engine enforces **capability-based safety**, not identity.

If a feature requires user login, identity management,
or session handling, it does **not belong in this repository**.
