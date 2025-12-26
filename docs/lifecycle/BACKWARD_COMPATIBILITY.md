# Backward Compatibility — Career Engine Core

## Purpose of This Document

This document defines **what backward compatibility means** for the Career Engine
and **what guarantees are provided to callers across versions**.

Backward compatibility is a **trust contract**.
If this contract is broken without following the rules here,
the release is invalid.

---

## Compatibility Philosophy

Backward compatibility exists to:
- Protect downstream applications
- Prevent silent behavior changes
- Enable safe upgrades
- Preserve determinism and trust

Breaking compatibility is sometimes necessary,
but it must **never be accidental or silent**.

---

## Types of Compatibility (AUTHORITATIVE)

The Career Engine recognizes **three distinct compatibility domains**:

1. **API Compatibility**
2. **ABI Compatibility**
3. **Behavioral Compatibility**

Each has different guarantees and rules.

---

## 1. API Compatibility

### Definition

API compatibility means:
- Existing source code continues to compile
- Public headers remain usable
- Public function signatures remain valid

Public API includes:
- Public headers
- Public classes and structs
- Public functions
- Public enums and constants
- Documented behavior

---

### API Compatibility Guarantees

Within the same **MAJOR version**:

- APIs must not be removed
- Function signatures must not change
- Public types must not change meaning
- Required parameters must not be added

Breaking API compatibility requires a **MAJOR version bump**.

---

### Allowed API Changes (Non-Breaking)

Allowed within MINOR/PATCH versions:
- Adding new APIs
- Adding optional parameters with defaults
- Adding new enum values (with care)
- Improving documentation

These changes must not affect existing code.

---

## 2. ABI Compatibility (IMPORTANT)

### Definition

ABI compatibility means:
- Binary consumers continue to work
- Object layout remains compatible
- Linking does not break

ABI applies if the engine is:
- Distributed as a static or shared library
- Used by precompiled binaries

---

### ABI Compatibility Guarantees

Within the same **MINOR version**:

- Layout of public structs/classes must not change
- Virtual table layout must not change
- Inline behavior must not change semantics

If ABI compatibility cannot be guaranteed,
this must be documented clearly.

---

### ABI Breaking Changes

The following break ABI compatibility:
- Reordering struct members
- Adding/removing virtual functions
- Changing inheritance
- Changing inline function behavior
- Changing alignment or padding

ABI-breaking changes require a **MAJOR version bump**.

---

## 3. Behavioral Compatibility (CRITICAL)

### Definition

Behavioral compatibility means:
- Same input produces the same output
- Same rules lead to same classifications
- Same safety behavior is preserved

Behavior is part of the public contract.

---

### Behavioral Guarantees

Within the same **MINOR version**:

- Classification meaning must not change
- Lifecycle inference must not regress
- Safety rules must not weaken
- Determinism must be preserved

Silent behavioral drift is forbidden.

---

### Allowed Behavioral Changes

Allowed only when:
- Change is documented
- Change is intentional
- Change aligns with PRD and GOALS

Behavioral changes require at least a **MINOR version bump**.

---

## Compatibility vs Bug Fixes

Bug fixes are allowed if:
- They correct objectively incorrect behavior
- They reduce false positives or errors
- They improve safety

Bug fixes must not:
- Change meaning of outputs silently
- Break determinism
- Remove safeguards

If a bug fix changes observable behavior,
it must be documented clearly.

---

## Data Compatibility

### Persisted Data

Rules:
- Persisted data formats must remain readable
- Schema evolution must be backward-compatible
- Migration must be explicit if required

Data loss during upgrade is unacceptable.

---

### Historical Interpretability

Past outputs must remain interpretable:
- Old classifications must retain meaning
- Deprecated rules must remain explainable
- Historical lifecycle states must not become invalid

History must not be rewritten.

---

## Compatibility & Deprecation

Compatibility works together with `DEPRECATION_POLICY.md`.

Rules:
- Deprecated features remain compatible during grace period
- Removal only occurs in MAJOR versions
- Compatibility guarantees end only after documented removal

Deprecation without compatibility guarantees is invalid.

---

## Security & Compatibility

Security fixes may:
- Override compatibility in extreme cases
- Accelerate removal of unsafe behavior

However:
- Impact must be documented
- Changes must be explicit
- Versioning rules still apply

Security overrides convenience, not transparency.

---

## LLM-Specific Rules

AI coding assistants must:
- Assume backward compatibility is required
- Avoid modifying public APIs silently
- Flag potential compatibility breaks
- Treat behavior as part of the API

If unsure whether a change is breaking, assume it is.

---

## Compatibility Review Checklist

Before merging changes, verify:
- API compatibility preserved (or version bumped)
- ABI compatibility preserved (or version bumped)
- Behavior compatibility preserved (or documented)
- Determinism preserved
- Security guarantees preserved

If any item is unclear, the change must not be merged.

---

## Final Compatibility Rule

Backward compatibility is not about convenience —
it is about **respecting users and integrations**.

If compatibility must be broken,
do it explicitly, deliberately, and transparently.
