#pragma once

/*
===============================================================================
SafetyPolicy.h — Safety Semantics and Invariants Boundary
===============================================================================

PURPOSE
-------
This header defines the safety semantics and invariants used during
classification outcome aggregation.

Safety in this engine is NOT a heuristic.
It is a strict, monotonic policy applied deterministically.

SafetyPolicy defines:
- What constitutes a safety assertion
- How conflicting safety assertions are interpreted
- Which safety states are terminal and non-overridable

This header defines WHAT safety rules exist,
but NOT HOW they are applied algorithmically.

RESPONSIBILITIES
----------------
SafetyPolicy is allowed to:
- Define safety invariants
- Define monotonicity rules for safety assertions
- Define precedence between safety states
- Be consulted by OutcomeAggregator during aggregation

SafetyPolicy is NOT allowed to:
- Evaluate rules
- Access RuleEngine
- Access NormalizedEmail
- Access storage, UI, networking, or OS resources
- Perform aggregation itself
- Perform non-deterministic behavior

SAFETY PRINCIPLES (NON-NEGOTIABLE)
---------------------------------
- Safety assertions are monotonic
- AssertUnsafe MUST always dominate AssertSafe
- Once unsafe, the classification is permanently unsafe
- No rule, advisory, or confidence adjustment may override safety

BOUNDARY RULES
--------------
- SafetyPolicy MUST be the single source of truth for safety semantics
- OutcomeAggregator MUST consult SafetyPolicy
- Rules MUST NOT embed safety resolution logic
- EngineInternal MUST NOT bypass SafetyPolicy

DEPENDENCY DIRECTION
--------------------
SafetyPolicy may depend on:
- rules/RuleOutcome.h (for SafetyAssertion types)

SafetyPolicy MUST NOT depend on:
- RuleEngine
- OutcomeAggregator
- core/
- lifecycle/
- utils/

IMPLEMENTATION NOTE
-------------------
This file intentionally contains no implementation.

All safety logic must be centralized and auditable,
implemented in the corresponding .cpp file (if required).

===============================================================================
*/
