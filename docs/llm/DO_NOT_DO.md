# DO NOT DO — Absolute Prohibitions for LLMs and Contributors

## Purpose of This Document

This document defines **absolute, non-negotiable prohibitions** for
AI coding assistants and human contributors working on the Career Engine.

These are not guidelines.
These are **hard stops**.

If any code, suggestion, or design violates this document,
it must be rejected immediately.

---

## Authority Statement

This file has **higher authority than convenience, speed, or creativity**.

If any other document, prompt, or suggestion conflicts with this file,
**this file wins**.

---

## Core Principle

> If something is not explicitly allowed, assume it is forbidden.

This engine prioritizes:
- Determinism
- Security
- Explainability
- Trust

Anything that weakens these is prohibited.

---

## 🚫 ABSOLUTE PROHIBITIONS (NO EXCEPTIONS)

### 1. DO NOT Add Networking of Any Kind

The engine must NEVER:
- Make HTTP/HTTPS requests
- Open sockets
- Use REST, gRPC, WebSockets
- Communicate with cloud services
- Sync data externally
- Phone home

This is a **local-only engine**.

---

### 2. DO NOT Add UI or User Interaction

The engine must NEVER:
- Render UI
- Use UI frameworks (Qt, WinUI, WPF, GTK, etc.)
- Show dialogs, popups, notifications
- Handle user input directly

UI belongs outside this repository.

---

### 3. DO NOT Add Authentication Systems

The engine must NEVER:
- Implement login flows
- Store passwords
- Handle OAuth
- Manage sessions
- Integrate identity providers

Authentication is the caller’s responsibility.

---

### 4. DO NOT Add Telemetry or Analytics

The engine must NEVER:
- Collect usage data
- Emit telemetry
- Log user behavior
- Track engagement
- Send metrics externally

Privacy is non-negotiable.

---

### 5. DO NOT Use Black-Box ML for Core Decisions

The engine must NEVER:
- Replace rules with opaque ML models
- Use cloud-hosted models
- Download models at runtime
- Make decisions that cannot be explained

Rules are primary.  
ML (if ever allowed) is advisory only.

---

### 6. DO NOT Introduce Non-Determinism

The engine must NEVER:
- Use randomness
- Depend on system time for logic
- Depend on environment state
- Produce different outputs for same input

Same input must always produce same output.

---

### 7. DO NOT Modify Rules at Runtime

The engine must NEVER:
- Self-update rules
- Learn automatically
- Adapt behavior silently
- Persist behavioral changes

All behavior is fixed per release.

---

### 8. DO NOT Delete or Discard Data Silently

The engine must NEVER:
- Delete emails
- Discard classifications
- Suppress data irreversibly
- Auto-clean without explicit instruction

Suppression ≠ deletion.

---

### 9. DO NOT Store Secrets in Plaintext

The engine must NEVER:
- Hardcode secrets
- Store plaintext keys
- Log sensitive data
- Serialize decrypted secrets

Security violations are critical defects.

---

### 10. DO NOT Break Module Boundaries

The engine must NEVER:
- Bypass security layer
- Access storage directly from classifiers
- Introduce circular dependencies
- Collapse layers “for convenience”

Architecture violations are defects.

---

### 11. DO NOT Change Public Behavior Silently

The engine must NEVER:
- Change classification meaning silently
- Change priorities silently
- Change safety behavior silently
- Change outputs without versioning

Behavior is part of the API.

---

### 12. DO NOT Remove Tests to Make CI Pass

The engine must NEVER:
- Delete tests to fix failures
- Weaken assertions
- Mask non-determinism
- Disable CI checks

Tests define correctness.

---

### 13. DO NOT Assume User Intent

The engine must NEVER:
- Assume emails are safe to delete
- Assume consent
- Assume user goals
- Automate irreversible actions

The engine advises; users decide.

---

## 🚫 LLM-SPECIFIC HARD STOPS

AI coding assistants must NEVER:

- Invent new features
- Expand scope beyond PRD
- Add “helpful” automation
- Optimize by removing checks
- Simplify security for speed
- Ignore documentation
- Generate code outside requested file
- Cross module boundaries
- Add dependencies without approval

If unsure → **STOP AND ASK**.

---

## 🚫 FORBIDDEN JUSTIFICATIONS

The following are NEVER acceptable reasons:

- “This is faster”
- “This is simpler”
- “This is how others do it”
- “We can fix it later”
- “It probably won’t matter”
- “The LLM suggested it”

Correctness > convenience.

---

## Enforcement Rule

If any violation of this document is found:

1. The change must be reverted
2. The design must be reconsidered
3. Tests must be added to prevent recurrence

No exceptions.

---

## Final Rule

This engine may influence:
- Careers
- Opportunities
- Real human decisions

Therefore:

> **If a change feels powerful but unsafe, it is forbidden.**

When in doubt:
**Do less. Be explicit. Preserve trust.**
