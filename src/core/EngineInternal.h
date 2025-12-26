#pragma once

/*
===============================================================================
EngineInternal.h — Internal Engine Orchestration Boundary
===============================================================================

PURPOSE
-------
This header defines internal-only orchestration constructs used by the
Engine implementation (Engine.cpp).

This file is NOT part of the public API.

It exists to:
- Coordinate rule evaluation
- Coordinate outcome aggregation
- Enforce internal sequencing and boundaries
- Prevent leakage of implementation details into Engine.h

RESPONSIBILITIES
----------------
EngineInternal is allowed to:
- Invoke RuleEngine
- Pass NormalizedEmail into rule evaluation
- Collect RuleOutcome objects
- Delegate aggregation to OutcomeAggregator
- Construct the final ClassificationResult

EngineInternal is NOT allowed to:
- Implement rule logic
- Implement aggregation logic
- Implement safety policy logic
- Access storage, UI, networking, or OS resources
- Mutate input data
- Perform non-deterministic behavior

BOUNDARY RULES
--------------
- Public code MUST NOT include this header.
- This header may only be included by:
    - src/core/Engine.cpp

DEPENDENCY DIRECTION
--------------------
EngineInternal may depend on:
- rules/
- aggregation/
- security/
- types/

EngineInternal MUST NOT be depended on by:
- rules/
- aggregation/
- utils/
- tests/

IMPLEMENTATION NOTE
-------------------
This file intentionally contains no implementation.
All logic must live in Engine.cpp or deeper internal modules.

===============================================================================
*/
