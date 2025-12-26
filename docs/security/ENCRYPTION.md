# Encryption Standards — Career Engine Core

## Purpose of This Document

This document defines **exact encryption rules** for the Career Engine.

It answers:
- What must be encrypted
- Which algorithms are allowed
- How keys are derived and stored
- What is explicitly forbidden
- How encryption failures must be handled

These rules are **mandatory**.
If code violates this document, it is insecure and must be rejected.

---

## Encryption Philosophy

Encryption in the Career Engine exists to:
- Protect user career data under partial compromise
- Prevent plaintext data leakage
- Limit damage if storage or memory is accessed

Encryption is **defensive by default**, not optional.

---

## What Must Be Encrypted (MANDATORY)

The following data **must always be encrypted at rest**:

### 1. Sensitive Persisted Data
- Job offer indicators
- Interview communications
- Assignment metadata
- Lifecycle state
- Safety flags

---

### 2. Secrets & Credentials (If Present)
- OAuth tokens (if ever passed through)
- API tokens
- Encryption keys
- Derived secrets

---

### 3. Derived Intelligence (When Persisted)
- Career classifications
- Confidence scores
- Lifecycle inference results

---

## What Must NOT Be Encrypted

The following may remain unencrypted:
- Non-sensitive configuration constants
- Static rule definitions (non-user data)
- Public engine metadata

Encryption should not be applied blindly.

---

## Approved Cryptographic Algorithms

Only the following algorithms are allowed.

### Symmetric Encryption (At Rest)

**Algorithm:** AES-256-GCM  
**Mode:** Authenticated encryption (AEAD)

Properties:
- Confidentiality
- Integrity
- Authentication

Using AES without authentication is forbidden.

---

### Key Derivation

**Algorithm:** Argon2id (preferred)

Requirements:
- Memory-hard
- Resistant to GPU attacks
- Deterministic parameters

If Argon2id is unavailable, fallback must be explicitly documented
and approved.

---

### Randomness

- Use OS-provided CSPRNG only
- Never use `rand()`
- Never roll custom randomness

---

## Key Hierarchy (MANDATORY)

Keys must be layered to reduce blast radius.

Root Secret (User / OS Protected)
↓
Key Derivation (Argon2id)
↓
Master Key
↓

↓ ↓ ↓
Storage Key Token Key Metadata Key


Rules:
- Keys must never be reused across purposes
- Keys must never be stored plaintext
- Derived keys must be isolated

---

## Key Storage Rules

- Root secrets must be protected by OS mechanisms when possible
- Derived keys must live in memory only
- Persisted keys must be encrypted
- Keys must be wiped from memory after use

No key material may be logged or serialized.

---

## Initialization Vector (IV) Rules

- IVs must be unique per encryption operation
- IVs must be generated via CSPRNG
- IV reuse is forbidden

IVs may be stored alongside ciphertext.

---

## Encryption Boundaries

Encryption logic must:
- Live in `security/` module only
- Be abstracted behind clean interfaces
- Never leak crypto primitives to callers

Callers must not know encryption details.

---

## Failure Handling

Encryption failures must:
- Fail closed
- Prevent data persistence
- Surface explicit errors
- Never silently fall back to plaintext

Silent encryption failure is a critical defect.

---

## Forbidden Practices (ABSOLUTE)

The following are strictly forbidden:

- Rolling custom crypto
- Using deprecated algorithms (MD5, SHA1, DES, RC4)
- Using AES without authentication
- Reusing IVs
- Hardcoding keys
- Storing keys in source code
- Logging secrets
- Encrypting data without integrity protection

Violations are security-critical.

---

## Testing Requirements

Encryption code must be tested for:
- Correct encryption/decryption
- Authentication failure on tampering
- Deterministic behavior
- Proper memory zeroization

Tests must not log secrets.

---

## LLM-Specific Rules

AI coding assistants must:
- Use only approved algorithms
- Avoid crypto shortcuts
- Avoid suggesting libraries without approval
- Prefer OS primitives where available

If uncertain, generate **interfaces only**, not implementations.

---

## Final Encryption Rule

Encryption protects users against catastrophic loss.

If a feature requires weakening encryption,
the feature must not be implemented.

Security is not negotiable.
