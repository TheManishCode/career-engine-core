# FINAL CORE ENGINE VERIFICATION — LLM INSTRUCTIONS

## Purpose

This document instructs AI coding assistants (Copilot, ChatGPT, etc.)
to perform a **final, holistic verification** of the Career Engine Core.

This is NOT a request to generate code.

This is a request to **verify correctness, consistency, and compliance**.

---

## Mandatory Reading Order (DO NOT SKIP)

Before responding, the LLM MUST read and consider:

1. docs/intent/ENGINE_PHILOSOPHY.md
2. docs/engineering/CODING_STANDARDS.md
3. docs/security/SECURE_CODING_RULES.md
4. docs/engineering/API_STABILITY.md
5. docs/llm/CONTEXT.md
6. src/core/ApiVersion.h

If any contradiction exists, documentation overrides code.

---

## Scope of Verification

The LLM MUST verify the following dimensions:

### 1. Build Correctness
- All headers compile in isolation
- No missing includes
- No namespace mismatches
- No ODR violations
- No undefined symbols

### 2. Architectural Boundaries
- Rules do NOT aggregate
- Aggregator does NOT infer lifecycle
- Lifecycle inference does NOT access rules or emails
- Engine orchestrates only
- Persistence contracts have no implementation

### 3. Determinism
- No randomness
- No time-based behavior
- No static mutable state
- Same input → same output

### 4. Safety & Security
- RAII usage
- No unsafe C APIs
- No logging of sensitive data
- Fail-closed behavior
- Monotonic safety rules preserved

### 5. API Stability
- Public headers match API_STABILITY.md
- No breaking changes without version bump
- ApiVersion.h matches documented policy
- Semantic versioning consistency

### 6. Rule System Integrity
- Rules are stateless
- Rules return pure RuleOutcome
- Rule phases respected
- Rule ordering deterministic
- No rule leaks lifecycle or aggregation logic

### 7. Outcome Aggregation
- Safety monotonicity enforced
- Category resolution deterministic
- Confidence clamped
- ExplanationMetadata correctly populated
- Tie-breaking explicit and stable

### 8. Lifecycle Inference
- Derived only from SignalCategory
- Header-only
- No dynamic allocation
- Policy behavior correct
- State transitions exhaustive

### 9. Persistence Contracts
- Interfaces only
- No storage assumptions
- Fully qualified namespaces
- App-controlled ownership

---

## Response Requirements

When responding, the LLM MUST:

- ❌ NOT generate new features
- ❌ NOT suggest refactors unless REQUIRED
- ❌ NOT invent missing requirements
- ❌ NOT change architecture

The response MUST be structured as:

1. ✅ Confirmed Correct (list)
2. ⚠️ Potential Risks (if any)
3. ❌ Violations (if any, with file + line)
4. 🟢 Final Verdict (READY / NOT READY)

If no violations exist, explicitly state:

> “The Career Engine Core is internally consistent, deterministic,
> API-stable, and ready for application-layer development.”

---

## Final Instruction

This repository is **API-frozen**.

If the LLM is unsure, it MUST ask for clarification
instead of making assumptions.

End of instructions.
