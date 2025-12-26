# Non-Goals — Explicit Exclusions for the Career Engine

## Purpose of This Document

This document defines **what the Career Engine will NOT do**.

These are **hard exclusions**, not missing features.
They exist to:
- Prevent scope creep
- Preserve security and determinism
- Maintain architectural clarity
- Stop incorrect LLM-generated code
- Avoid future refactors caused by wrong assumptions

If a proposed feature violates this document,
**the feature must be rejected**.

---

## Core Non-Goal Statement

The Career Engine is a **core intelligence library**, not a product.

Anything related to **presentation, interaction, orchestration, or cloud**
is **out of scope** for this repository.

---

## 1. User Interface (UI) — NOT A GOAL

The engine must NOT:
- Render any UI
- Use UI frameworks (Qt, WinUI, WPF, etc.)
- Handle user input directly
- Manage dialogs, notifications, or views
- Contain layout, styling, or UX logic

UI belongs in a separate application layer.

---

## 2. Networking & Communication — NOT A GOAL

The engine must NOT:
- Start servers or listeners
- Perform HTTP/HTTPS requests
- Use sockets or IPC mechanisms
- Communicate with remote services
- Sync data over the network

The engine must function **fully offline**.

---

## 3. Authentication & OAuth — NOT A GOAL

The engine must NOT:
- Authenticate users
- Implement OAuth flows
- Manage access tokens
- Store refresh tokens
- Interact with identity providers

Authentication is the responsibility of the calling application.

---

## 4. Cloud Infrastructure — NOT A GOAL

The engine must NOT:
- Depend on cloud services
- Upload or download user data
- Use cloud storage
- Perform telemetry or analytics
- Require internet connectivity

Cloud integration belongs outside this repository.

---

## 5. Autonomous Decision-Making — NOT A GOAL

The engine must NOT:
- Apply to jobs on behalf of users
- Send emails automatically
- Respond to recruiters
- Make irreversible decisions
- Act without explicit caller control

The engine provides **recommendations**, not actions.

---

## 6. Black-Box Machine Learning — NOT A GOAL

The engine must NOT:
- Use opaque ML models for core decisions
- Download models at runtime
- Train models automatically
- Perform online learning
- Replace rules with probabilistic guesses

Explainability is mandatory.

---

## 7. Self-Modifying Behavior — NOT A GOAL

The engine must NOT:
- Modify its own rules at runtime
- Generate executable code dynamically
- Change behavior based on hidden state
- Persist undocumented internal state

All behavior must be:
- Explicit
- Version-controlled
- Reviewable

---

## 8. Platform Lock-In — NOT A GOAL

The engine must NOT:
- Depend on OS-specific APIs without abstraction
- Assume a specific UI framework
- Assume a specific database engine
- Assume a specific email provider

Portability and reuse are core values.

---

## 9. Silent Failure or Implicit Behavior — NOT A GOAL

The engine must NOT:
- Silently ignore errors
- Guess intent without sufficient evidence
- Hide uncertainty
- Perform destructive actions without signaling

When unsure, the engine must be conservative.

---

## 10. Developer Convenience Over Safety — NOT A GOAL

The engine must NOT:
- Sacrifice safety for speed
- Use unsafe shortcuts
- Log sensitive data
- Skip validation for convenience

Security and correctness are always higher priority.

---

## 11. Repository Scope Expansion — NOT A GOAL

This repository must NOT evolve into:
- A monorepo
- A product repository
- A UI project
- A service repository
- A deployment repository

If functionality does not belong to the core engine,
it belongs elsewhere.

---

## Final Rule

If a proposed change requires the sentence:

> “We’ll just add this here for now…”

Then it **does not belong in this repository**.

Non-goals are not limitations.
They are what make this engine strong, safe, and maintainable.
