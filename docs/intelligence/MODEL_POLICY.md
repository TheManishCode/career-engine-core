# Model Policy — Career Engine Core

## Purpose of This Document

This document defines **if, when, and how machine learning models may be used**
inside the Career Engine.

This policy exists to:
- Prevent accidental black-box behavior
- Preserve determinism and explainability
- Protect security and privacy guarantees
- Clearly separate rules from models

If any implementation violates this policy, it must be rejected.

---

## Core Policy Statement (AUTHORITATIVE)

> **Rules are primary.  
> Models are secondary.  
> Models must never replace rules.**

The Career Engine is a **rule-driven system**.
Machine learning, if used at all, is **advisory-only**.

---

## What “Model” Means in This Context

A “model” refers to any statistical or ML-based component, including:

- Classical ML (e.g., logistic regression, SVM)
- Neural networks
- Embedding models
- Scoring or ranking models
- Heuristic models trained on data

This applies regardless of size or complexity.

---

## Default Position: NO MODELS

By default:
- **No ML models are used**
- The engine functions fully using deterministic rules
- All intelligence is explainable through rule traces

This is the **baseline and preferred state**.

---

## When Models MAY Be Introduced (RESTRICTED)

Models may be considered only if **all** conditions are met:

1. Rules alone cannot achieve acceptable accuracy
2. The model’s output can be fully constrained by rules
3. The model is explainable and auditable
4. The model runs fully locally
5. Determinism can be guaranteed
6. Governance and rollback are defined

Failure to meet any condition forbids model usage.

---

## Allowed Roles for Models (VERY LIMITED)

If approved, models may ONLY:

- Assist in **signal scoring**
- Assist in **confidence estimation**
- Assist in **ranking already-classified results**
- Suggest candidate classifications (never final)

Models must NEVER make final decisions.

---

## Forbidden Roles for Models (ABSOLUTE)

Models must NEVER:

- Replace rule-based classification
- Override safety rules
- Control lifecycle transitions
- Decide deletion or suppression
- Modify engine behavior dynamically
- Learn at runtime
- Fetch external data
- Depend on cloud inference

Any of the above is a critical violation.

---

## Determinism Requirements for Models

If a model is used, it must guarantee:

- Same input → same output
- No stochastic behavior
- Fixed weights per release
- No adaptive behavior
- No runtime retraining

Random seeds alone are NOT sufficient.
True determinism is required.

---

## Explainability Requirements

Every model-assisted decision must be explainable:

- What input features were used
- What the model contributed
- How the rule engine constrained the output

If a model’s contribution cannot be explained,
it must not be used.

---

## Model Isolation Rules

Models must be:

- Isolated in the `intelligence/` layer
- Wrapped behind explicit interfaces
- Invisible to public APIs
- Invisible to storage layer
- Invisible to security layer

No model logic may leak into rule code.

---

## Model Versioning Rules

- Models are versioned with the engine
- Models change only between releases
- Model updates require documented justification
- Model updates follow VERSIONING.md

Silent model updates are forbidden.

---

## Model Testing Requirements (MANDATORY)

Any approved model must have:

- Deterministic unit tests
- Boundary condition tests
- Adversarial input tests
- Regression tests

Model behavior must be testable like any rule.

---

## Model Security Rules

Models must NOT:

- Contain embedded secrets
- Leak training data
- Log sensitive inputs
- Expose internal weights externally

Models are treated as untrusted code until proven safe.

---

## Training Data Rules (If Ever Applicable)

If models are trained:

- Training happens outside this repository
- Training data is never bundled
- Personal user data is never used
- Training pipelines are documented

This repository contains **inference only**, if anything.

---

## Interaction with MLOps

Any model usage must comply with:
- `MLOPS_BOUNDARIES.md`
- `RULES_GOVERNANCE.md`
- `SECURITY/*` documents

Model usage without MLOps governance is forbidden.

---

## LLM-Specific Rules

AI coding assistants must:

- Assume models are disallowed by default
- Never introduce models silently
- Never replace rules with models
- Always flag model usage explicitly

If unsure, do not suggest models.

---

## Review Checklist for Model Introduction

Before approving any model usage:

- [ ] Rules-only solution was insufficient
- [ ] Model role is advisory only
- [ ] Determinism is guaranteed
- [ ] Explainability is documented
- [ ] Tests exist
- [ ] Versioning impact is assessed
- [ ] Security implications reviewed

If any box is unchecked, reject the model.

---

## Final Model Policy Rule

Models are powerful — and dangerous.

In a system that influences careers:

> **Any intelligence that cannot be explained, controlled, and rolled back  
> does not belong here.**
