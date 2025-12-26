#pragma once

/*
===============================================================================
OutcomeAggregator.h — Deterministic Rule Outcome Aggregation Boundary
===============================================================================

PURPOSE
-------
This header defines the aggregation boundary responsible for combining
RuleOutcome objects into a final ClassificationResult.

Aggregation is a deterministic, ordered, rule-governed process that
resolves:
- Classification suggestions
- Confidence contributions
- Safety assertions
- Advisory adjustments

This header defines WHAT aggregation is responsible for,
but NOT HOW aggregation is implemented.

RESPONSIBILITIES
----------------
OutcomeAggregator is allowed to:
- Accept a sequence of RuleOutcome objects
- Apply deterministic aggregation rules
- Enforce safety monotonicity
- Resolve conflicting classification suggestions
- Compute a final ClassificationResult

OutcomeAggregator is NOT allowed to:
- Evaluate rules
- Access NormalizedEmail directly
- Perform rule ordering
- Invoke RuleEngine
- Access storage, UI, networking, or OS resources
- Perform non-deterministic behavior

BOUNDARY RULES
--------------
- Aggregation logic MUST be centralized here.
- No other module may combine RuleOutcome objects.
- Rules MUST NOT depend on this module.
- EngineInternal may delegate aggregation exclusively to this module.

DEPENDENCY DIRECTION
--------------------
OutcomeAggregator may depend on:
- rules/RuleOutcome.h
- types/ClassificationResult.h
- security/SafetyPolicy.h (consultative only)

OutcomeAggregator MUST NOT depend on:
- rules/RuleEngine.h
- core/Engine.h
- lifecycle/
- utils/

IMPLEMENTATION NOTE
-------------------
This file intentionally contains no implementation.

The corresponding .cpp file will contain the aggregation logic,
written to satisfy deterministic and safety constraints.

===============================================================================
*/
