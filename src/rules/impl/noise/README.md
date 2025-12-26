# Noise Rules — Intent and Boundaries

## Purpose
This directory contains rules responsible for identifying **noise and
non-actionable content**, such as advertisements or low-signal messages.

## Allowed Responsibilities
Noise rules may:
- Identify promotional or irrelevant emails
- Suggest Advertisement or Unknown categories
- Suppress confidence contributions from noisy signals
- Return noise-related classification contributions via RuleOutcome

## Forbidden Responsibilities
Noise rules MUST NOT:
- Override explicit career signals
- Perform safety assertions
- Perform lifecycle reasoning
- Decide final classification outcomes
- Depend on aggregation or safety policy logic

## Design Principles
- Noise suppression is advisory, not destructive
- Strong career signals must dominate noise
- Rules must remain conservative and deterministic

Noise rules reduce clutter — they do not erase meaning.
