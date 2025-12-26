# Versioning & Compatibility — Career Engine Core

## Purpose of This Document

This document defines **how versions are assigned, incremented, and interpreted**
for the Career Engine.

It establishes:
- Semantic meaning of version numbers
- API and ABI compatibility rules
- What constitutes a breaking change
- How releases must be managed

If implementation or release practices violate this document,
the release is invalid.

---

## Versioning Philosophy

Version numbers are a **contract**.

They communicate:
- Stability guarantees
- Upgrade risk
- Compatibility expectations

Incorrect versioning breaks trust and downstream integrations.

---

## Versioning Scheme

The Career Engine uses **Semantic Versioning**:

MAJOR.MINOR.PATCH


Example: 1.4.2


Each component has strict meaning.

---

## MAJOR Version

Increment **MAJOR** when:

- Public API is broken
- Behavior changes in incompatible ways
- Data formats change incompatibly
- Security model changes
- Determinism guarantees change

Rules:
- MAJOR increments require explicit migration notes
- MAJOR changes must be rare and deliberate
- Backward compatibility is NOT guaranteed across MAJOR versions

---

## MINOR Version

Increment **MINOR** when:

- New functionality is added
- Existing APIs are extended (additive only)
- New classifications or rules are introduced
- Performance improvements are made without behavior change

Rules:
- MINOR updates must be backward compatible
- Existing APIs must continue to work
- Behavior must remain deterministic

---

## PATCH Version

Increment **PATCH** when:

- Bug fixes are applied
- Security vulnerabilities are fixed
- Internal refactors occur without behavior change
- Documentation-only changes are released

Rules:
- PATCH updates must not change public behavior
- PATCH updates must be safe to apply automatically

---

## API Stability Rules

### Public API Definition

Public API includes:
- Public headers
- Public types
- Public function signatures
- Documented behavior

Anything exposed to the caller is part of the API.

---

### API Compatibility Guarantees

- No API removal without MAJOR bump
- No signature change without MAJOR bump
- No behavior change without at least MINOR bump
- Deprecations must be explicit and documented

---

## ABI Compatibility Rules (IMPORTANT)

If the engine is distributed as a binary:

- ABI stability must be preserved within MINOR versions
- Layout changes to public types require MAJOR bump
- Inline function changes must be carefully reviewed

If ABI stability cannot be guaranteed,
this must be documented clearly.

---

## Deprecation Policy

- Deprecations must be announced in a MINOR release
- Deprecated APIs must remain available for at least one MAJOR cycle
- Deprecations must include clear alternatives

Silent deprecations are forbidden.

---

## Release Discipline

Each release must include:
- Version number
- Changelog
- Summary of changes
- Compatibility notes (if applicable)
- Security notes (if applicable)

Releases without documentation are invalid.

---

## Security & Versioning

Security fixes:
- May require PATCH or MINOR bump
- Must be clearly documented
- Must not silently change behavior

Emergency fixes must still follow versioning rules.

---

## Tagging & Source Control

- Each release must be tagged in version control
- Tags must be immutable
- Release tags must correspond exactly to source state

Rewriting release history is forbidden.

---

## LLM-Specific Rules

AI coding assistants must:
- Respect existing versioning constraints
- Never introduce breaking changes silently
- Flag changes that may require version bumps
- Avoid modifying public APIs without instruction

If unsure whether a change is breaking, assume it is.

---

## Review Checklist

Before releasing a new version:
- Is the version number correct?
- Are changes backward compatible?
- Is the changelog accurate?
- Are security implications documented?

If any answer is unclear, delay the release.

---

## Final Versioning Rule

Version numbers communicate trust.

If users cannot rely on version semantics,
the project has failed its responsibility.
