# Deprecation Policy — Career Engine Core

## Purpose of This Document

This document defines **how features, APIs, rules, behaviors, and capabilities
are deprecated** within the Career Engine.

Deprecation is a **contractual process**, not an implementation detail.

This policy exists to:
- Prevent silent breakage
- Protect downstream integrations
- Preserve user trust
- Maintain long-term stability
- Enforce disciplined evolution

If a change violates this policy, it must not be merged or released.

---

## Deprecation Philosophy

Deprecation is **communication before removal**.

Principles:
- No surprises
- No silent behavior changes
- No sudden removals
- No ambiguity about timelines

Breaking users is worse than delaying features.

---

## What Can Be Deprecated

The following may be deprecated:

- Public APIs (functions, classes, headers)
- Classification rules
- Noise suppression rules
- Lifecycle inference behavior
- Configuration options
- Output fields
- Internal extension points (if documented)

Anything exposed to callers or influencing behavior
is subject to this policy.

---

## What MUST NOT Be Deprecated Silently (ABSOLUTE)

The following must NEVER be silently deprecated:

- Security guarantees
- Determinism guarantees
- Safety behavior (e.g., safe-to-delete logic)
- Encryption behavior
- Authentication or authorization requirements

Any change here requires **explicit versioning and documentation**.

---

## Deprecation Lifecycle (AUTHORITATIVE)

All deprecations must follow this lifecycle:

Active
↓
Deprecated (Documented)
↓
Grace Period
↓
Removal (Major Version Only)


Skipping steps is forbidden.

---

## Step 1: Deprecation Announcement

A feature is considered deprecated only when:

- It is explicitly marked as deprecated
- Deprecation is documented
- Alternatives are provided
- Timeline is communicated

Required artifacts:
- Documentation update
- Release notes entry
- Clear migration guidance

Implicit deprecation does not exist.

---

## Step 2: Deprecation Marking

Deprecated elements must be clearly marked:

- In documentation
- In code comments (if applicable)
- In public headers or interfaces (if applicable)

Marking must include:
- Deprecation reason
- Recommended replacement
- Expected removal version

Example (conceptual):
> Deprecated since v1.4 — will be removed in v2.0

---

## Step 3: Grace Period (MANDATORY)

All deprecated features must have a **grace period**.

Rules:
- Grace period lasts at least **one MINOR release**
- Deprecated functionality must continue to work
- Behavior must not change during grace period
- Security fixes may still be applied

Breaking deprecated features during grace period is forbidden.

---

## Step 4: Removal Rules

Removal is allowed only when:

- Grace period has completed
- Removal occurs in a **MAJOR version**
- Removal is documented clearly
- Migration path has been available

Silent removal is forbidden.

---

## Versioning Interaction

Deprecation interacts with versioning as follows:

| Action | Allowed Version |
|------|----------------|
| Mark deprecated | MINOR |
| Maintain deprecated | PATCH / MINOR |
| Remove deprecated | MAJOR |

Any deviation requires explicit justification.

---

## Behavioral Deprecation (SPECIAL CASE)

If behavior (not API) is deprecated:

- Old behavior must remain default during grace period
- New behavior must be opt-in (if applicable)
- Behavior switch must be explicit and documented

Silent behavior drift is forbidden.

---

## Rule Deprecation (Intelligence Layer)

Rules may be deprecated if:
- They are incorrect
- They are too aggressive
- They are superseded by safer logic

Rule deprecation must:
- Be documented in RULES_GOVERNANCE.md
- Include test coverage
- Preserve determinism
- Avoid retroactive behavior changes

Historical outputs must remain interpretable.

---

## Security-Related Deprecation

If a deprecated feature is security-sensitive:

- Security fixes may override grace period
- Removal may be accelerated
- Impact must be clearly documented

Security always overrides convenience.

---

## Tooling & Warnings

If supported:
- Deprecation warnings may be surfaced
- Warnings must not expose sensitive data
- Warnings must not alter behavior

Warnings must inform, not punish.

---

## LLM-Specific Rules

AI coding assistants must:
- Respect deprecated markers
- Avoid using deprecated APIs in new code
- Prefer recommended replacements
- Never remove deprecated code without instruction

If unsure, treat deprecated features as still active.

---

## Review Checklist for Deprecation

Before approving a deprecation, verify:
- Reason is documented
- Replacement exists
- Timeline is clear
- Grace period is defined
- Versioning rules are followed

If any item is missing, the deprecation is invalid.

---

## Final Deprecation Rule

Deprecation is a promise to users.

Breaking that promise damages trust far more
than delaying change.

Deprecate carefully. Remove deliberately.
