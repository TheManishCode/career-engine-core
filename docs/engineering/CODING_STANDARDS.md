# Coding Standards — Career Engine Core

## Purpose of This Document

This document defines **mandatory coding standards** for the Career Engine.

It ensures:
- Consistent code style
- High readability
- Long-term maintainability
- Security and determinism
- Predictable LLM-generated code

If code violates these standards, it must be revised.

---

## Language Standard

- **C++20 is mandatory**
- Compiler extensions are forbidden unless explicitly approved
- Code must compile cleanly with warnings enabled

Portability and clarity take priority over novelty.

---

## File Organization Rules

### Directory Rules

- Each module lives in its own directory
- Headers and sources must be colocated per module
- No cross-module file placement

Example:

classifier/
classifier.h
classifier.cpp


---

### Header File Rules

- Headers must be self-contained
- Headers must include only what they need
- Prefer forward declarations where possible
- No using-directives (`using namespace`) in headers

Public headers must be stable and minimal.

---

## Naming Conventions

### Types
- `PascalCase`
- Examples: `ClassificationResult`, `LifecycleState`

### Functions
- `camelCase`
- Verbs preferred
- Examples: `classifyEmail()`, `evaluateRules()`

### Variables
- `camelCase`
- Descriptive, no abbreviations
- Examples: `confidenceScore`, `emailMetadata`

### Constants
- `UPPER_SNAKE_CASE`
- Examples: `MAX_CONFIDENCE`, `DEFAULT_TIMEOUT`

---

## Const-Correctness (MANDATORY)

- Use `const` wherever possible
- Prefer immutable data
- Mark member functions `const` when applicable

Lack of const-correctness is a design smell.

---

## Ownership & Lifetime Rules

- Ownership must be explicit
- Prefer value semantics
- Use move semantics intentionally
- Avoid shared ownership

If ownership is unclear, redesign the API.

---

## Function Design Rules

- Functions should do one thing
- Keep functions small and focused
- Avoid side effects
- Avoid hidden dependencies

If a function needs a comment to explain *what* it does,
it likely does too much.

---

## Error Handling Rules

- Errors must be explicit
- No silent failures
- Prefer return types that encode failure
- Avoid exceptions across module boundaries

Error handling must be predictable and testable.

---

## Control Flow Rules

- Avoid deeply nested logic
- Prefer early returns
- Avoid complex conditionals
- Avoid clever tricks

Readable code is safer code.

---

## Comments & Documentation

### When to Comment
- Non-obvious logic
- Security-sensitive decisions
- Boundary conditions

### When NOT to Comment
- Obvious code
- Redundant explanations

Comments must explain **why**, not **what**.

---

## Formatting Rules

- Consistent indentation
- One statement per line
- Braces on same line
- No trailing whitespace

Formatting should be boring and consistent.

---

## Header Hygiene

- No unnecessary includes
- Avoid transitive dependencies
- Minimize compile times

Header bloat is a maintenance risk.

---

## Forbidden Coding Practices (ABSOLUTE)

- `using namespace std;`
- Macros for logic
- Hidden global state
- Magic numbers
- C-style casts
- Compiler-specific hacks

Violations must be removed.

---

## LLM-Specific Rules

AI coding assistants must:
- Follow these standards strictly
- Prefer clarity over brevity
- Avoid “clever” optimizations
- Ask for clarification if intent is unclear

Generated code is subject to the same review standards.

---

## Review Checklist

Before merging code, verify:
- Code follows naming conventions
- Ownership is explicit
- Error handling is clear
- No forbidden practices
- Code is readable without explanation

If any item fails, the code must be revised.

---

## Final Coding Rule

Code will be read more often than it is written.

Write code for:
- Future maintainers
- Security reviewers
- Static analysis tools
- AI assistants

Clarity is the highest form of correctness.
