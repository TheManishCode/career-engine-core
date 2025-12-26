# LLM Context — Career Engine Core

## Purpose of This File

This file defines **how AI coding assistants must understand and behave**
when working in this repository.

This repository is intentionally designed to be **LLM-assisted**, but
only within **strict boundaries**.

If an LLM suggestion conflicts with any document in `docs/`,
**the documentation always wins**.

---

## Repository Identity

This repository contains a **C++ static library** that implements the
**core intelligence engine** for career-related email processing.

This engine:
- Has no UI
- Has no networking layer
- Has no OAuth or authentication UI
- Has no cloud or server components
- Has no runtime telemetry

It is **not** an application.
It is a **reusable, embedded engine**.

---

## What This Engine Does

The engine converts **email-derived signals** into **structured,
career-relevant intelligence**.

Examples of responsibilities:
- Classifying job-related emails
- Identifying offers, rejections, assignments, interviews
- Suppressing noise from job platforms (LinkedIn, Naukri, etc.)
- Assigning confidence scores
- Enforcing safety rules (e.g., safe-to-delete protection)

All behavior must be:
- Deterministic
- Explainable
- Testable
- Local-only

---

## What This Engine Does NOT Do

LLMs must NEVER generate code that:
- Renders UI
- Starts servers or listeners
- Makes HTTP requests
- Uses OAuth flows
- Talks to cloud APIs
- Downloads models or data
- Executes arbitrary scripts
- Stores plaintext secrets
- Uses dynamic code execution
- Introduces global mutable state

If such functionality is requested, it belongs in another repository.

---

## Architectural Boundaries

The engine is divided into **strict modules**:
- Classification
- Noise filtering
- Lifecycle inference
- Security utilities
- Storage abstraction
- Public engine interface

Modules must communicate via:
- Explicit interfaces
- Clearly defined data structures
- One-way dependencies

Circular dependencies are forbidden.

---

## Determinism Requirements

LLMs must assume:
- Same input → same output
- No randomness
- No hidden time-based behavior
- No environment-dependent logic

If determinism cannot be guaranteed,
the implementation is invalid.

---

## Security Constraints (NON-NEGOTIABLE)

Generated code must:
- Use RAII for all resources
- Zero sensitive memory after use
- Avoid unsafe C/C++ functions
- Avoid undefined behavior
- Fail closed, not open
- Never log sensitive data

Convenience must never override security.

---

## Performance Expectations

Performance-sensitive code must:
- Minimize allocations
- Avoid unnecessary copies
- Prefer value semantics where safe
- Be explicit about ownership

However:
- Correctness > performance
- Safety > speed

---

## Error Handling Rules

LLMs must:
- Prefer explicit error propagation
- Avoid silent failures
- Avoid throwing exceptions across module boundaries
- Clearly document failure modes

Uncertainty must be surfaced, not hidden.

---

## Code Style Expectations

Generated code must:
- Follow C++20
- Use clear, descriptive names
- Prefer small, composable functions
- Avoid macros unless strictly necessary
- Avoid magic numbers
- Include comments for non-obvious logic

---

## Testing Expectations

Any non-trivial logic should be:
- Unit-testable
- Deterministic
- Isolated from external state

LLMs should prefer designs that simplify testing.

---

## AI-Specific Instructions

When generating code:
1. Read `docs/intent/ENGINE_PHILOSOPHY.md`
2. Respect all security documents
3. Do not invent features
4. Do not cross repository boundaries
5. Ask for clarification if intent is ambiguous

If unsure, generate **minimal scaffolding**, not full implementations.

---

## Final Instruction to LLMs

This repository values:
- Explicitness over cleverness
- Boundaries over convenience
- Safety over speed
- Long-term maintainability over rapid output

Any suggestion that violates these principles
is incorrect for this repository.
