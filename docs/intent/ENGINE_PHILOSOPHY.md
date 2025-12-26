# Engine Philosophy

## Purpose of This Document

This document defines the **core philosophy** of the Career Engine.
It explains **how the engine thinks**, **how decisions are made**, and
**which trade-offs are acceptable or forbidden**.

This file is more important than individual implementations.
If code and philosophy conflict, **the philosophy wins**.

This document is written for:
- Core contributors
- Reviewers
- AI coding assistants (Copilot, ChatGPT, etc.)

---

## Core Principle

The Career Engine is a **deterministic, security-first, local-only
intelligence engine**.

It exists to transform **raw email data** into **structured,
career-relevant signals** while minimizing:
- Noise
- Risk
- Cognitive load
- Hidden behavior

The engine must behave predictably and explainably at all times.

---

## Design Pillars

### 1. Determinism Over Cleverness

Given the same input, the engine must always produce the same output.

- No randomness
- No hidden state
- No time-dependent logic (unless explicitly modeled)
- No non-deterministic data structures in critical paths

This is required for:
- Trust
- Debugging
- Security audits
- Long-term maintenance

---

### 2. Rule-First, Intelligence-Second

The engine is **rule-driven by default**.

Rules are:
- Explicit
- Inspectable
- Deterministic
- Version-controlled

Machine learning or statistical methods:
- Are optional
- Must never replace rules
- Must never obscure decisions
- Must be local-only if used

If a decision cannot be explained in plain language,
it does not belong in the engine.

---

### 3. Security Is Not a Feature — It Is a Constraint

Security is not implemented *after* functionality.
It is a **hard constraint** applied **before** design decisions.

This means:
- No plaintext secrets
- No unsafe memory handling
- No implicit trust of inputs
- No silent failures
- No convenience shortcuts that weaken safety

If a feature cannot be implemented securely,
the feature must be redesigned or rejected.

---

### 4. Local-First, Privacy-Preserving by Default

All computation must assume:
- User data stays on the user’s machine
- No external services are trusted
- No telemetry is required to function

The engine must work:
- Offline
- Without cloud dependencies
- Without sending user data externally

Privacy is a **default**, not a configuration option.

---

### 5. Narrow Responsibility, Strong Boundaries

The engine has **one responsibility**:
> Convert email-derived signals into structured career intelligence.

It must NOT:
- Render UI
- Manage authentication UI flows
- Perform network orchestration
- Act as a service or daemon
- Enforce product-level policies

Clear boundaries prevent architectural decay.

---

### 6. Boring Interfaces, Powerful Internals

Public interfaces must be:
- Simple
- Stable
- Minimal

Internal implementations may be complex,
but complexity must never leak outside the engine.

A boring interface is a sign of good design.

---

## Decision-Making Model

The engine evaluates data using a staged pipeline:

1. Input normalization
2. Signal extraction
3. Rule evaluation
4. Classification
5. Confidence assignment
6. Safety checks

Each stage:
- Has clear inputs and outputs
- Has no side effects
- Can be tested independently

No stage may bypass another.

---

## Failure Philosophy

Failures must be:
- Explicit
- Observable
- Contained

The engine must:
- Fail closed, not open
- Prefer conservative classification over risky assumptions
- Never silently ignore errors

If uncertainty is high, the engine must say so.

---

## Performance Philosophy

Performance matters, but **correctness and safety matter more**.

Performance optimizations must:
- Be justified
- Be measurable
- Not weaken security
- Not reduce clarity

Premature optimization is discouraged.
Predictability is preferred over raw speed.

---

## Change Philosophy

Every change must answer:
1. What problem does this solve?
2. Does it violate any core principle?
3. Can it be explained clearly?
4. Is the behavior deterministic?
5. Is security preserved?

If these cannot be answered clearly,
the change should not be merged.

---

## AI Coding Assistant Rules

When AI tools are used:
- They must follow this philosophy
- They must not invent features
- They must not cross repository boundaries
- They must not introduce hidden behavior

Generated code must be reviewed with the assumption
that AI may optimize incorrectly.

---

## Final Statement

This engine values:
- Clarity over cleverness
- Safety over convenience
- Explicit rules over hidden logic
- Long-term maintainability over short-term speed

If a design choice violates these values,
it is the wrong choice for this engine.
