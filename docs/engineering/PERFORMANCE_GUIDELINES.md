# Performance Guidelines — Career Engine Core

## Purpose of This Document

This document defines **how performance must be approached** in the
Career Engine.

Performance is important, but it is **never allowed to override**:
- Security
- Determinism
- Correctness
- Clarity

If a performance optimization violates any of these,
the optimization must be rejected.

---

## Performance Philosophy

The engine prioritizes:
1. Correctness
2. Security
3. Determinism
4. Maintainability
5. Performance

Performance work must be:
- Intentional
- Measurable
- Justified

Premature optimization is explicitly discouraged.

---

## Deterministic Performance

Performance characteristics must be:
- Predictable
- Repeatable
- Independent of hidden state

Rules:
- No randomness
- No time-based behavior affecting logic
- No environment-dependent shortcuts

Performance must not change results.

---

## Hot Path Identification

Only optimize **proven hot paths**.

Rules:
- Measure before optimizing
- Document why a path is hot
- Avoid speculative optimizations

If performance impact is unmeasured,
the change must be considered unnecessary.

---

## Allocation Guidelines

### Allocation Minimization

- Avoid unnecessary heap allocations
- Prefer stack allocation for small, short-lived data
- Reuse buffers only when safe and explicit

---

### Containers & Memory

- Prefer `std::vector` over linked structures
- Reserve capacity when size is known
- Avoid frequent reallocations in loops

Memory efficiency improves predictability.

---

## Copy & Move Semantics

- Prefer move semantics where ownership transfers
- Avoid unnecessary copies
- Prefer passing by reference-to-const for large objects

Do not sacrifice clarity for micro-optimizations.

---

## Algorithmic Complexity

- Prefer simpler algorithms with predictable complexity
- Avoid worst-case exponential behavior
- Avoid pathological cases in untrusted input handling

Big-O analysis matters more than constant factors.

---

## Caching Rules

Caching is **restricted**.

Allowed only if:
- Cache keys are explicit
- Cache invalidation is deterministic
- Cache size is bounded
- Cache does not contain sensitive plaintext data

Hidden or implicit caching is forbidden.

---

## Concurrency & Performance

Concurrency is optional and restricted.

Rules:
- Prefer single-threaded determinism
- Avoid shared mutable state
- Avoid lock-heavy designs

Concurrency must not introduce:
- Data races
- Non-determinism
- Complex synchronization logic

If concurrency complicates correctness,
do not use it.

---

## I/O & Blocking Behavior

- Engine must not block indefinitely
- Avoid synchronous I/O in hot paths
- Storage access must be explicit and controlled

The engine must remain responsive to callers.

---

## Profiling & Measurement

Performance changes must be validated using:
- Benchmarks
- Profilers
- Reproducible test cases

Anecdotal performance claims are invalid.

---

## Performance & Security Interaction

Security-sensitive code must NOT be optimized
in ways that:
- Reduce validation
- Skip checks
- Remove safeguards
- Expose timing side channels

Security always overrides performance.

---

## Forbidden Performance Practices (ABSOLUTE)

The following are strictly forbidden:

- Removing validation for speed
- Skipping safety checks
- Using undefined behavior for optimization
- Compiler-specific hacks
- “Trusting” input for performance

Violations are security defects.

---

## LLM-Specific Rules

AI coding assistants must:
- Avoid speculative optimization
- Prefer clear, correct code
- Suggest optimization only with justification
- Never remove safety checks for speed

If unsure, do not optimize.

---

## Performance Review Checklist

Before merging performance-related changes:
- Is performance impact measured?
- Is correctness preserved?
- Is determinism preserved?
- Is security preserved?
- Is the change documented?

If any answer is unclear, reject the change.

---

## Final Performance Rule

Performance is valuable only when:
- It is measured
- It is safe
- It is predictable

Fast incorrect code is worse than slow correct code.
