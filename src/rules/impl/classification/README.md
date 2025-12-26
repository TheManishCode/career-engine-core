# Classification Rules — Intent and Boundaries

## Purpose
This directory contains rules that suggest **career-related signal categories**
such as offers, rejections, interviews, or assignments.

## Allowed Responsibilities
Classification rules may:
- Inspect the input email
- Suggest a SignalCategory
- Provide a confidence contribution
- Return structured classification contributions via RuleOutcome

## Forbidden Responsibilities
Classification rules MUST NOT:
- Resolve conflicts between categories
- Aggregate confidence scores
- Make final classification decisions
- Perform safety resolution
- Perform lifecycle reasoning
- Depend on aggregation logic

## Design Principles
- Rules suggest meaning; the engine decides meaning
- Multiple rules may suggest competing categories
- Determinism and explainability are mandatory

Classification rules provide signals, not conclusions.
