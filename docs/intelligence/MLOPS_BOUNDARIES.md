# MLOps Boundaries — Career Engine Core

## Purpose of This Document

This document defines **strict operational boundaries for any machine learning
or statistical models** associated with the Career Engine.

This is **not** a typical MLOps document.

Its purpose is to:
- Prevent scope creep
- Prevent cloud dependency
- Prevent silent model drift
- Preserve determinism and explainability
- Keep the engine rule-first, not model-driven

If any MLOps practice violates this document, it is forbidden.

---

## Core Boundary Statement (AUTHORITATIVE)

> **This repository is NOT an ML platform.  
> MLOps is constrained, optional, and subordinate to rules.**

The Career Engine:
- Does not require ML
- Does not assume ML
- Must function correctly with zero models

---

## What “MLOps” Means Here (VERY NARROW)

In this project, MLOps refers ONLY to:

- Versioning of optional, approved models
- Validation of deterministic inference
- Safe packaging of model artifacts
- Controlled rollout via releases

It does NOT include:
- Training pipelines
- Experiment tracking
- Online inference
- Monitoring dashboards
- Continuous learning systems

---

## Explicitly Out of Scope (ABSOLUTE)

The following are **never allowed**:

- Cloud-based training
- Cloud-based inference
- Remote model fetching
- Runtime model updates
- Online learning
- Auto-retraining
- A/B testing
- Telemetry-driven optimization
- Feature stores
- Model registries (cloud or remote)

Violations are critical defects.

---

## Training Boundaries

If models are ever trained:

- Training occurs **outside** this repository
- Training code is **not included**
- Training data is **not included**
- Personal user data is **never used**
- Training is a one-time, offline process

This repository is **inference-only**, if models exist at all.

---

## Model Artifact Rules

Approved model artifacts must:

- Be immutable
- Be versioned with the engine
- Be bundled explicitly at build/release time
- Have checksums
- Have documented provenance

Model artifacts must never:
- Be downloaded dynamically
- Be swapped at runtime
- Be modified after release

---

## Deterministic Inference Requirements

All model inference must guarantee:

- Same input → same output
- No randomness
- No nondeterministic math paths
- No hardware-dependent variation

If determinism cannot be proven,
the model must not be used.

---

## Model Deployment Rules

Model deployment is governed by:

- `VERSIONING.md`
- `DEPRECATION_POLICY.md`
- `BACKWARD_COMPATIBILITY.md`
- `MODEL_POLICY.md`

Rules:
- Model changes are release events
- Model changes require documentation
- Model changes require tests
- Silent model updates are forbidden

---

## Validation & Testing (MANDATORY)

Any model included must have:

- Deterministic unit tests
- Boundary and adversarial tests
- Regression tests
- Rule-interaction tests

Models without tests are invalid.

---

## Rollback & Recovery

Model-related issues must be recoverable by:

- Reverting the release
- Issuing a patch release
- Disabling model usage explicitly (if supported)

Rollback must not require retraining.

---

## Security Boundaries

Models must NOT:

- Contain secrets
- Embed credentials
- Leak training data
- Log sensitive inputs
- Expose internal weights

Model files are treated as **potentially sensitive artifacts**.

---

## Observability Boundaries

The engine must NOT:

- Monitor model performance in production
- Collect inference metrics
- Track user outcomes
- Send model-related telemetry

Observability belongs to the caller, not the engine.

---

## Human-in-the-Loop Requirement

Any decision to:
- Add a model
- Update a model
- Remove a model

Requires:
- Explicit human approval
- Documentation
- Review against governance documents

Automation must not decide intelligence changes.

---

## LLM-Specific Rules

AI coding assistants must:

- Assume MLOps is disallowed by default
- Never suggest cloud MLOps tools
- Never introduce pipelines or registries
- Never automate model updates
- Always defer to rules first

If unsure, do not mention ML at all.

---

## Enforcement Checklist

Before approving any ML-related change:

- [ ] Rules-only solution evaluated
- [ ] Model role is advisory only
- [ ] Determinism proven
- [ ] Artifacts immutable
- [ ] Tests exist
- [ ] Rollback defined
- [ ] Security reviewed
- [ ] Versioning impact assessed

If any box is unchecked, reject the change.

---

## Final Boundary Rule

This engine exists to **reduce risk**, not increase it.

Any MLOps practice that introduces:
- Drift
- Opacity
- Automation without control

is incompatible with this project.

> **When in doubt, do not add ML.**
