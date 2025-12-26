# Classification Strategy — Career Engine Core

## Purpose of This Document

This document defines **how the Career Engine thinks about classification**.

It does NOT describe implementation details.
It defines:
- Classification philosophy
- Priority rules
- Safety-first decision ordering
- How ambiguity is handled
- What correctness means

If code behavior contradicts this strategy,
the code is wrong.

---

## Classification Philosophy

Classification exists to **reduce cognitive load without losing critical signal**.

The engine must:
- Prefer safety over aggressiveness
- Prefer precision over recall for critical events
- Avoid speculative interpretation
- Surface uncertainty explicitly

Classification is **decision support**, not automation.

---

## What Classification Means (AUTHORITATIVE)

Classification answers:

> “What kind of career-relevant signal does this email represent?”

It does NOT:
- Decide user actions
- Delete data
- Respond to emails
- Apply for jobs
- Enforce lifecycle state unilaterally

Classification produces **structured meaning**, nothing more.

---

## Core Classification Dimensions

Every career-related email is evaluated along these axes:

1. **Career relevance**
2. **Signal type**
3. **Criticality**
4. **Confidence**

These dimensions are independent but correlated.

---

## 1. Career Relevance Detection (FIRST GATE)

### Rule

An email must first be classified as:
- Career-related
- Non-career
- Ambiguous

Rules:
- Non-career emails must never enter job classification
- Ambiguous emails must be preserved, not discarded
- False positives are worse than false negatives

Career relevance is a **hard gate**.

---

## 2. Signal Type Classification (PRIMARY)

If career-related, classify into one or more of:

### High-Signal Categories (CRITICAL)

- Job Offer / Selection
- Interview / Scheduling
- Assignment / Assessment
- Recruiter Direct Outreach

These categories have **highest protection priority**.

---

### Medium-Signal Categories

- Application Confirmation
- Application Status Update
- Follow-up Requests

Important, but not immediately critical.

---

### Low-Signal Categories (NOISE-PRONE)

- Job Advertisements
- Platform Promotions
- Digest Emails
- Recommendation Blasts

Low-signal does NOT mean useless —
it means lower urgency.

---

## 3. Criticality Determination (SAFETY LAYER)

Criticality answers:

> “Could mishandling this cause real-world harm?”

Rules:
- Offers are always critical
- Interviews are always critical
- Assignments are always critical
- Rejections are non-critical but emotionally relevant
- Advertisements are non-critical

Criticality is **orthogonal to confidence**.

---

## 4. Confidence Scoring (LAST)

Confidence reflects:
- Strength of matching signals
- Absence of contradictions
- Rule agreement consistency

Rules:
- Confidence must be deterministic
- Confidence must be explainable
- Low confidence must not suppress results
- Confidence must never imply certainty

Low confidence ≠ low importance.

---

## Priority Resolution Rules (NON-NEGOTIABLE)

If multiple signals are detected:

Offer / Selection

Interview
> Assignment
> Recruiter Outreach
> Application Status
> Advertisement


Rules:
- Higher-priority signals dominate classification
- Lower-priority signals may still be recorded
- No critical signal may be overridden by noise

Priority resolution must be explicit and documented.

---

## Noise Suppression Interaction

Classification must cooperate with noise suppression:

- Classification identifies meaning
- Noise filter evaluates visibility

Rules:
- Classification must NEVER discard data
- Noise suppression must NEVER alter classification meaning
- Suppression must be reversible

Classification is truth; noise filtering is presentation guidance.

---

## Ambiguity Handling (MANDATORY)

When signals conflict or are weak:

- Mark classification as ambiguous
- Reduce confidence
- Preserve data
- Surface explanation

Rules:
- Never guess to improve confidence
- Never hide ambiguity
- Never force-fit categories

Ambiguity is safer than misclassification.

---

## Lifecycle Interaction Rules

Classification feeds lifecycle inference but does NOT control it.

Rules:
- Classification does not advance lifecycle state directly
- Lifecycle logic consumes classification output
- Reclassification must not rewrite history

Classification describes events; lifecycle interprets sequences.

---

## Determinism Guarantees

Classification must guarantee:

- Same input → same classification
- Same rules → same result
- No randomness
- No environment dependence

If classification is not deterministic,
it is invalid.

---

## Safety Overrides

Safety rules may override classification usage but not meaning.

Examples:
- A low-confidence offer is still protected
- An ambiguous interview is still critical
- A misclassified ad must not delete data

Safety > confidence > convenience.

---

## What Classification MUST NOT Do (ABSOLUTE)

Classification must NOT:
- Learn automatically
- Modify rules at runtime
- Use black-box models
- Depend on external services
- Depend on user history silently
- Perform deletion or suppression

Violations are critical defects.

---

## LLM-Specific Rules

AI coding assistants must:
- Follow this strategy exactly
- Never invent new categories silently
- Never reorder priorities
- Always preserve ambiguity
- Generate tests for classification behavior

If unsure, classify conservatively.

---

## Review Checklist for Classification Changes

Before approving classification changes:
- Does it preserve determinism?
- Does it improve safety?
- Does it reduce false positives?
- Is ambiguity handled explicitly?
- Are tests updated?

If any answer is unclear, reject the change.

---

## Final Classification Rule

Classification shapes user trust.

A single incorrect classification can:
- Cause missed opportunities
- Create false hope
- Increase anxiety
- Lose trust permanently

When in doubt:
**preserve data, lower confidence, explain clearly.**
