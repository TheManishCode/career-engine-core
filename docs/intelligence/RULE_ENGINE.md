# Rule Engine — Career Engine Core

## Purpose of This Document

This document defines **what the Rule Engine is**, **how rules are evaluated**,
and **how conflicts are resolved** inside the Career Engine.

This file is the **final authority** on:
- Rule execution order
- Determinism guarantees
- Conflict resolution
- Safety precedence
- What rules may and may not do

If implementation behavior contradicts this document,
the implementation is incorrect.

---

## Rule Engine Philosophy

Rules are **explicit logic**, not heuristics.

The Rule Engine must be:
- Deterministic
- Explainable
- Auditable
- Immutable at runtime

The engine does not “infer” or “guess”.
It **evaluates rules** and reports outcomes.

---

## What the Rule Engine Is (AUTHORITATIVE)

The Rule Engine is a **deterministic decision evaluator** that:

- Consumes normalized inputs and extracted signals
- Applies a fixed, ordered set of rules
- Produces structured decisions with explanations
- Never mutates inputs
- Never mutates rules

It is **not**:
- A learning system
- A probabilistic model
- A policy engine
- A workflow engine
- A rules authoring UI

---

## Rule Characteristics (MANDATORY)

Every rule must be:

- **Explicit** — written, readable, and version-controlled
- **Deterministic** — same input → same output
- **Pure** — no side effects
- **Stateless** — no memory of past evaluations
- **Explainable** — reason must be traceable

Rules that violate any of these properties are forbidden.

---

## Rule Evaluation Pipeline (AUTHORITATIVE)

Rules are evaluated in a **strict, ordered pipeline**:

Input (Normalized Data)
↓
Signal Set
↓
Rule Set Evaluation
↓
Intermediate Outcomes
↓
Conflict Resolution
↓
Final Rule Outcome


No stage may be skipped or reordered.

---

## Rule Ordering (CRITICAL)

Rules are evaluated in **explicit priority order**.

### Priority Classes

Rules are grouped into priority classes:

1. **Safety Rules** (highest priority)
2. **Critical Classification Rules**
3. **Standard Classification Rules**
4. **Noise Identification Rules**
5. **Advisory Rules** (lowest priority)

Higher-priority rules **always dominate** lower-priority rules.

---

## Safety Rules (ABSOLUTE PRECEDENCE)

Safety rules:
- Execute first
- Cannot be overridden
- Cannot be suppressed
- Cannot be bypassed

Examples:
- Offer protection
- Interview protection
- Assignment protection
- Safe-to-delete guards

If a safety rule triggers, all lower-priority rules must respect it.

---

## Classification Rules

Classification rules:
- Assign semantic meaning
- Identify signal categories
- Produce confidence contributions

Rules:
- Must not delete or suppress data
- Must not override safety rules
- Must not assume lifecycle state

Classification describes **what**, not **what to do**.

---

## Noise Rules

Noise rules:
- Identify low-signal patterns
- Recommend suppression (not deletion)
- Must remain reversible

Rules:
- Must never suppress safety-classified signals
- Must not alter classification meaning
- Must be conservative

Noise rules influence visibility, not truth.

---

## Advisory Rules

Advisory rules:
- Add metadata
- Add hints
- Add secondary annotations

Rules:
- Must never affect safety
- Must never affect classification outcome
- Must never influence lifecycle directly

Advisory rules are optional.

---

## Conflict Resolution (MANDATORY)

When multiple rules produce conflicting outcomes:

Resolution order is:

Safety > Classification > Noise > Advisory


Rules:
- Lower-priority outcomes are overridden
- Conflicts must be recorded in explanation traces
- Resolution must be deterministic

No conflict may be resolved implicitly.

---

## Rule Output Structure

Every rule evaluation must produce:

- Rule identifier
- Rule priority
- Match result (true/false)
- Reason/explanation
- Confidence contribution (if applicable)

Outputs must be **structured and inspectable**.

---

## Confidence Contribution Rules

Rules may contribute to confidence only if:

- Contribution is deterministic
- Contribution is bounded
- Contribution is documented
- Contribution is explainable

Confidence must be **aggregated**, never guessed.

---

## Rule Immutability (ABSOLUTE)

Rules must be:

- Fixed at compile or release time
- Immutable during runtime
- Versioned with source control

The engine must NEVER:
- Modify rules dynamically
- Enable/disable rules silently
- Persist rule state

Behavior must be frozen per release.

---

## Determinism Guarantees

The Rule Engine must guarantee:

- No randomness
- No time-based logic
- No environment-based behavior
- No order-dependent iteration
- No undefined behavior

Same input must always produce the same rule trace.

---

## Error Handling in Rule Evaluation

If rule evaluation fails:

- Fail closed
- Surface explicit error
- Do not emit partial results
- Do not guess or fallback

Errors must not be masked.

---

## Rule Testing Requirements

Every rule must have:

- Positive match tests
- Negative match tests
- Boundary tests
- Regression tests (if modified)

Rule tests must assert:
- Match outcome
- Explanation correctness
- Deterministic ordering

Untested rules are invalid.

---

## Rule Evolution Rules

Changes to rules must follow:

- RULES_GOVERNANCE.md
- VERSIONING.md
- DEPRECATION_POLICY.md

Silent rule changes are forbidden.

---

## LLM-Specific Rules

AI coding assistants must:

- Never invent rules
- Never reorder priorities
- Never collapse rule stages
- Never remove explanation traces
- Always generate tests for rule changes

If unsure, do not modify rules.

---

## Forbidden Rule Engine Behaviors (ABSOLUTE)

The Rule Engine must NEVER:

- Learn from data
- Cache decisions
- Persist intermediate state
- Depend on external services
- Infer intent beyond rules
- Bypass safety rules
- Produce side effects

Violations are critical defects.

---

## Final Rule Engine Law

The Rule Engine defines **truth** for the Career Engine.

If the Rule Engine:
- Becomes opaque
- Becomes adaptive
- Becomes non-deterministic

Then the engine has failed its core responsibility.

> **Rules must be boring, explicit, and correct — always.**
