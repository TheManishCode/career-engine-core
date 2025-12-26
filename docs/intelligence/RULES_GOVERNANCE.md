# Rules & Intelligence Governance — Career Engine Core

## Purpose of This Document

This document defines **how classification rules, noise filters, lifecycle
heuristics, and any intelligence logic evolve** within the Career Engine.

It ensures:
- Determinism is preserved
- Behavior remains explainable
- Changes are auditable
- Scope creep is prevented
- LLM-assisted changes are controlled

If a rule change violates this document, it must not be merged.

---

## Governance Philosophy

Rules ARE the product.

Therefore:
- Rules must be explicit
- Rules must be version-controlled
- Rules must be reviewable
- Rules must be testable
- Rules must be reversible

Hidden or implicit intelligence is forbidden.

---

## What Is Governed by This Document

This governance applies to:
- Career detection rules
- Job classification rules
- Platform noise suppression rules
- Lifecycle inference heuristics
- Confidence scoring logic

It applies regardless of whether logic is:
- Hard-coded
- Table-driven
- Config-driven
- AI-assisted (if ever added)

---

## Determinism Guarantee (NON-NEGOTIABLE)

All rules must satisfy:

- Same input → same output
- No randomness
- No time-based behavior
- No environment-dependent logic

If a rule cannot guarantee determinism,
it is not allowed.

---

## Rule Design Principles

### 1. Explicit Over Implicit

Rules must:
- Be written explicitly
- Avoid hidden thresholds
- Avoid magic constants
- Avoid undocumented precedence

If a rule cannot be explained in plain language,
it must be rewritten.

---

### 2. Conservative by Default

Rules must:
- Prefer false negatives over false positives
- Protect critical career events
- Avoid aggressive suppression

Safety overrides convenience.

---

### 3. Explainability Required

Every rule must:
- Have a human-readable description
- Be traceable in outputs
- Be linked to test cases

Unexplainable rules are forbidden.

---

## Rule Lifecycle (AUTHORITATIVE)

All rules must follow this lifecycle:

Proposal
↓
Design Review
↓
Implementation
↓
Testing
↓
Documentation
↓
Release


Skipping steps is forbidden.

---

## Rule Proposal Requirements

Every rule proposal must include:

- Problem statement
- Motivation
- Examples of input/output
- Expected impact
- Risk analysis

“Seems useful” is not a valid justification.

---

## Rule Review Requirements

Rule reviews must verify:

- Determinism
- Explainability
- Security impact
- Test coverage
- Compatibility with PRD & GOALS

Rules that fail review must be rejected.

---

## Testing Requirements for Rules

Every rule must have:
- Positive test cases
- Negative test cases
- Boundary condition tests
- Regression tests (if modifying existing behavior)

Rules without tests do not exist.

---

## Rule Versioning

Rules are versioned implicitly via:
- Source control
- Release versions

Rules must NOT:
- Self-update
- Be modified at runtime
- Be fetched remotely

Behavior must be fixed per release.

---

## Breaking Rule Changes

A rule change is considered **breaking** if it:
- Changes classification meaning
- Alters lifecycle transitions
- Changes safety behavior
- Changes confidence interpretation

Breaking rule changes require:
- MAJOR or MINOR version bump (per VERSIONING.md)
- Explicit documentation
- Migration notes if applicable

Silent behavior change is forbidden.

---

## Noise Filter Governance (SPECIAL CASE)

Noise suppression rules must be:
- Extra conservative
- Fully reversible
- Transparent in output

Rules must never permanently discard data.
Suppression ≠ deletion.

---

## Lifecycle Heuristics Governance

Lifecycle inference must:
- Be monotonic or explicitly reversible
- Avoid speculative jumps
- Require strong evidence for advancement

Lifecycle regressions must be documented and tested.

---

## Confidence Scoring Governance

Confidence scores must:
- Be deterministic
- Be explainable
- Be bounded and documented

Confidence must never imply certainty.

---

## ML & Statistical Methods (FUTURE-CONSTRAINED)

If ML or statistical assistance is ever introduced:

- ML must not replace rules
- ML must not be a black box
- ML must be local-only
- ML must be optional
- ML output must be explainable
- ML must be governed by this document

Until explicitly approved, ML is considered **out of scope**.

---

## Rollback & Recovery

Rule changes must be reversible by:
- Reverting commits
- Releasing patch versions
- Maintaining backward compatibility where possible

Hotfixes must still follow governance.

---

## LLM-Specific Rules

AI coding assistants must:
- Treat rules as policy, not suggestions
- Never invent new rules silently
- Always generate tests with rule changes
- Flag behavior changes explicitly

If unsure, do not modify rules.

---

## Auditability

For every rule change, the repository must contain:
- Commit history
- Tests proving behavior
- Documentation describing intent

If a rule cannot be audited, it is invalid.

---

## Governance Review Checklist

Before merging rule changes, verify:
- Rule is documented
- Rule is deterministic
- Rule is tested
- Rule is reviewed
- Rule aligns with PRD and GOALS

If any check fails, the change must not be merged.

---

## Final Governance Rule

Rules define user trust.

Any shortcut in rule governance
will eventually surface as a user-facing failure.

Govern rules as if careers depend on them —
because they do.
