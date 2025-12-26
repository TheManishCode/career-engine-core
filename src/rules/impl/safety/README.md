# Safety Rules — Intent and Boundaries

## Purpose
This directory contains rules that emit **safety-related assertions** only.

Safety rules exist to protect the user from accidental data loss,
misclassification, or unsafe automated actions.

## Allowed Responsibilities
Safety rules may:
- Inspect the input email
- Assert safety signals such as:
  - safe_to_delete
  - requires_review
- Return SafetyAssertion values via RuleOutcome

## Forbidden Responsibilities
Safety rules MUST NOT:
- Assign classification categories
- Adjust confidence scores
- Perform lifecycle reasoning
- Override or resolve safety conflicts
- Access aggregation logic
- Depend on other rules

## Design Principles
- Safety assertions are monotonic
- AssertUnsafe is terminal and non-overridable
- Rules must remain stateless and deterministic

Safety rules contribute protection — not decisions.
