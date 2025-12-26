#pragma once

/*
===============================================================================
DeterministicHelpers.h — Deterministic Utility Boundary
===============================================================================

PURPOSE
-------
This header defines a collection point for small, deterministic helper
functions used across the engine implementation.

These helpers exist to:
- Reduce duplication
- Improve clarity
- Centralize low-level, reusable logic

All helpers defined here MUST be fully deterministic and side-effect free.

RESPONSIBILITIES
----------------
DeterministicHelpers is allowed to:
- Provide pure helper functions
- Operate only on provided inputs
- Return results without modifying external state
- Be reused across core, aggregation, and lifecycle modules

DeterministicHelpers is NOT allowed to:
- Access time, clocks, randomness, or environment state
- Perform I/O of any kind
- Access global or static mutable state
- Perform allocation-heavy or caching behavior
- Encode business logic or policy decisions

BOUNDARY RULES
--------------
- All functions MUST be referentially transparent
- Same input MUST always produce same output
- No hidden state or implicit dependencies
- Helpers MUST be easy to unit test in isolation

DEPENDENCY DIRECTION
--------------------
DeterministicHelpers may depend on:
- Standard library headers only
- types/ (for simple value types)

DeterministicHelpers MUST NOT depend on:
- core/
- rules/
- aggregation/
- security/
- lifecycle/

IMPLEMENTATION NOTE
-------------------
This file intentionally contains no implementation.

All helpers added here must justify their existence and
document why they cannot live closer to their call site.

===============================================================================
*/
