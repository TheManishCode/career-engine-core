#pragma once

/*
===============================================================================
LifecycleInference.h — Career Lifecycle Reasoning Boundary
===============================================================================

PURPOSE
-------
This header defines the boundary for inferring higher-level career lifecycle
signals from aggregated classification results.

Lifecycle inference answers questions such as:
- Is this email part of an active hiring process?
- Does this represent progression, stagnation, or closure?
- Should this signal influence long-term career state?

This header defines WHERE lifecycle reasoning belongs,
but NOT HOW lifecycle decisions are computed.

RESPONSIBILITIES
----------------
LifecycleInference is allowed to:
- Consume a fully aggregated ClassificationResult
- Infer lifecycle-level signals or annotations
- Remain deterministic and stateless
- Be invoked by EngineInternal after aggregation

LifecycleInference is NOT allowed to:
- Evaluate rules
- Aggregate RuleOutcome objects
- Influence safety decisions
- Modify ClassificationResult
- Access NormalizedEmail directly
- Access storage, UI, networking, or OS resources
- Perform non-deterministic behavior

BOUNDARY RULES
--------------
- Lifecycle inference MUST occur after aggregation
- Rules MUST NOT perform lifecycle reasoning
- OutcomeAggregator MUST NOT perform lifecycle reasoning
- EngineInternal may invoke lifecycle inference optionally

DEPENDENCY DIRECTION
--------------------
LifecycleInference may depend on:
- types/ClassificationResult.h

LifecycleInference MUST NOT depend on:
- rules/
- aggregation/
- security/
- core/Engine.h
- utils/

IMPLEMENTATION NOTE
-------------------
This file intentionally contains no implementation.

Lifecycle inference logic, if implemented, must be explicit,
auditable, and fully deterministic.

===============================================================================
*/
