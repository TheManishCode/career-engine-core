# Data Flow — Career Engine Core

## Purpose of This Document

This document defines **how data flows through the Career Engine** from
input to output.

It establishes:
- The exact processing stages
- The direction of data movement
- What each stage is allowed to read or modify
- Where data must be validated and protected

If code violates this data flow, it is architecturally incorrect,
even if functionality appears correct.

---

## Core Data Flow Principle

The Career Engine processes data using a **strict, linear, staged pipeline**.

Data must:
- Flow forward only
- Never skip stages
- Never loop backward
- Never mutate upstream state

Each stage:
- Has a single responsibility
- Produces explicit output
- Is independently testable

---

## High-Level Pipeline

Raw Input
↓
Normalization
↓
Signal Extraction
↓
Rule Evaluation
↓
Classification
↓
Confidence Assignment
↓
Safety & Guard Checks
↓
Structured Output


This order is **mandatory**.

---

## Stage 1: Raw Input

### Description
The engine receives **normalized input structures** from the caller.

Examples:
- Parsed email metadata
- Parsed email content
- Timestamps
- Sender identifiers

### Rules
- Inputs are treated as **untrusted**
- No assumptions about correctness
- No side effects allowed

### Output
- Raw input passed to normalization

---

## Stage 2: Normalization

### Description
Convert raw input into **canonical internal representations**.

Examples:
- Normalize text casing
- Normalize timestamps
- Canonicalize sender domains
- Strip irrelevant formatting

### Rules
- Deterministic transformations only
- No inference or classification
- No persistence
- No security decisions

### Output
- Normalized, sanitized data structures

---

## Stage 3: Signal Extraction

### Description
Extract **signals** from normalized data.

Examples:
- Keyword matches
- Structural patterns
- Sender reputation indicators
- Attachment presence
- Platform identifiers

Signals are **facts**, not decisions.

### Rules
- Signals must be explicit and inspectable
- No weighting or scoring here
- No rule application
- No state mutation

### Output
- Structured signal set

---

## Stage 4: Rule Evaluation

### Description
Apply **deterministic rules** to extracted signals.

Examples:
- Career vs non-career detection
- Job category inference
- Platform noise identification

### Rules
- Rules must be explicit and version-controlled
- No probabilistic logic
- No learning or adaptation
- No persistence

### Output
- Rule outcomes
- Decision rationale (rule traces)

---

## Stage 5: Classification

### Description
Produce **semantic classifications** based on rule outcomes.

Examples:
- Offer
- Rejection
- Assignment
- Interview
- Advertisement

### Rules
- Classifications must map directly to rules
- No speculative inference
- No lifecycle assumptions

### Output
- Classification results
- Associated rule traces

---

## Stage 6: Confidence Assignment

### Description
Assign **confidence scores** to classifications.

Confidence reflects:
- Strength of rule matches
- Consistency of signals
- Absence of conflicting indicators

### Rules
- Deterministic scoring only
- Scores must be explainable
- No hidden heuristics

### Output
- Classification + confidence pairs

---

## Stage 7: Safety & Guard Checks

### Description
Apply **safety rules** before results are exposed.

Examples:
- Critical email detection
- Safe-to-delete protection
- Uncertainty surfacing

### Rules
- Fail closed on uncertainty
- Safety overrides classification
- No output suppression without explanation

### Output
- Guarded, validated results

---

## Stage 8: Structured Output

### Description
Produce final engine output structures.

Examples:
- Career classification result
- Lifecycle hints
- Safety flags
- Explanations

### Rules
- Outputs must be immutable
- Outputs must be self-describing
- Outputs must contain no sensitive raw data unless required

---

## Lifecycle-Specific Data Flow

Lifecycle inference uses **historical outputs**, not raw inputs.

Past Outputs
↓
Lifecycle Inference
↓
Updated Lifecycle State


Rules:
- Lifecycle logic must not reclassify emails
- Lifecycle must consume outputs, not inputs
- State transitions must be explicit

---

## Data Mutability Rules

- Raw input: immutable
- Normalized data: immutable
- Signals: immutable
- Rule outcomes: immutable
- Final output: immutable

Any mutation must:
- Occur in a new data structure
- Be explicit
- Be documented

---

## Error Propagation

- Errors propagate upward immediately
- No silent recovery
- No partial output on failure
- Errors must include stage context

If a stage fails, downstream stages must not execute.

---

## Observability & Explainability

Each stage must support:
- Traceability
- Explanation generation
- Deterministic replay

If a decision cannot be traced to a specific stage,
the design is invalid.

---

## Forbidden Data Flow Patterns

The following are explicitly forbidden:

- Skipping normalization
- Rules modifying signals
- Classification modifying rules
- Lifecycle logic reclassifying emails
- Storage logic influencing classification
- Security logic being bypassed

Any such pattern is a critical defect.

---

## Final Data Flow Rule

The pipeline exists to:
- Protect correctness
- Preserve security
- Enable explainability

If a shortcut simplifies implementation but violates
the data flow, the shortcut must not be taken.
