# LLM Style Guide — Career Engine Core

## Purpose of This Document

This document defines **how LLM-generated output must look** when working
on the Career Engine.

This is not about aesthetics.
This is about:
- Readability
- Predictability
- Maintainability
- Auditability
- Safety

If generated output violates this guide, it must be rejected.

---

## Style Philosophy

> **Boring code is correct code.**

The preferred style is:
- Explicit over clever
- Verbose over implicit
- Predictable over optimized
- Readable over compact

The goal is to make code and docs easy to:
- Review
- Audit
- Test
- Maintain

---

## Tone & Language Rules

LLMs must use a tone that is:

- Professional
- Neutral
- Precise
- Unemotional
- Non-marketing

Avoid:
- Casual language
- Emojis
- Jokes
- Motivational phrasing
- Marketing-style claims

This is a production system, not a blog post.

---

## Structure Rules (MANDATORY)

### Code Output

LLM-generated code must:

- Be clearly structured
- Follow existing file layout
- Use consistent indentation
- Avoid unnecessary abstraction
- Avoid inline complexity

Prefer:
- Small functions
- Clear naming
- Explicit control flow

---

### Documentation Output

LLM-generated documentation must:

- Use clear headings
- Follow logical ordering
- Avoid redundancy
- Avoid vague statements
- Be authoritative, not suggestive

Docs must read as **rules**, not advice.

---

## Naming Discipline

LLMs must follow naming rules defined in:
- `CODING_STANDARDS.md`

Additional guidance:
- Names must be descriptive
- Avoid abbreviations
- Avoid single-letter variables (except indices)
- Avoid overloaded meanings

If a name needs explanation, it is wrong.

---

## Commenting Rules

Comments must:

- Explain *why*, not *what*
- Justify non-obvious decisions
- Call out safety or determinism concerns

Avoid:
- Redundant comments
- Commentary on obvious logic
- TODOs unless explicitly requested

---

## Explicitness Rules

LLMs must prefer:

- Explicit condition checks
- Explicit error handling
- Explicit return paths
- Explicit ordering

Avoid:
- Implicit conversions
- Clever one-liners
- Overloaded operators for logic
- Hidden side effects

Explicit code is safer code.

---

## Error Handling Style

LLMs must:

- Handle errors explicitly
- Avoid silent failures
- Avoid catch-all logic
- Avoid using exceptions unless required

Error paths must be as readable as success paths.

---

## Determinism Style Rules

Generated code must:

- Avoid randomness
- Avoid time-dependent behavior
- Avoid environment-dependent logic
- Avoid iteration over unordered structures unless order is fixed

If determinism is not obvious from reading the code,
the code is unacceptable.

---

## Safety-First Style

When writing logic that affects:

- Classification
- Rules
- Suppression
- Lifecycle
- Security

LLMs must:
- Prefer conservative behavior
- Preserve data
- Lower confidence rather than guessing
- Document safety rationale

---

## Forbidden Style Patterns (ABSOLUTE)

LLMs must NOT generate:

- Clever hacks
- Meta-programming
- Macros for logic
- Reflection-style patterns
- Dynamic behavior
- Implicit magic

If code looks “smart”, it is probably wrong.

---

## Diff Discipline

When modifying existing files, LLMs must:

- Minimize diff size
- Avoid unrelated changes
- Preserve formatting where possible
- Avoid re-ordering unless necessary

Large diffs are suspicious by default.

---

## Output Formatting Rules

LLMs must:

- Output only the requested file or code
- Avoid surrounding explanations unless asked
- Avoid inline reasoning in final output

Reasoning belongs in discussion, not in code.

---

## Consistency Rule

When in doubt:
- Follow existing patterns
- Match surrounding style
- Do not invent new conventions

Consistency beats novelty.

---

## LLM Self-Check (REQUIRED)

Before finalizing output, LLMs must internally verify:

- Style matches this document
- No forbidden patterns were used
- Code is readable without explanation
- Behavior is explicit and deterministic

If any check fails, regenerate.

---

## Final Style Rule

> **If future you would sigh while reading this, rewrite it.**

The best compliment this code can receive is:
> “Nothing surprising here.”
