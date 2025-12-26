# Advisory Rules — Intent and Boundaries

## Purpose
This directory contains rules that provide **supplementary signals**
after primary classification and safety evaluation.

Advisory rules refine, not decide.

## Allowed Responsibilities
Advisory rules may:
- Adjust confidence scores (bounded deltas only)
- Contribute explanation metadata
- Add secondary contextual signals

## Forbidden Responsibilities
Advisory rules MUST NOT:
- Assign or override classification categories
- Assert or resolve safety conditions
- Perform lifecycle reasoning
- Make final decisions of any kind
- Depend on aggregation or engine internals

## Design Principles
- Advisory rules are non-authoritative
- Contributions must be explainable and bounded
- Determinism is mandatory

Advisory rules enhance understanding — they never control outcomes.
