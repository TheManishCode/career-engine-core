# Product Requirements Document (PRD)
## Career Engine — Core Intelligence Library

---

## 1. Purpose

This document defines **what the Career Engine MUST do** and
**what it MUST NOT do**.

This PRD applies **only** to the C++ core engine contained in this
repository. It does **not** describe UI, applications, services,
or deployment environments.

If implementation deviates from this PRD, the implementation is wrong.

---

## 2. Problem Statement

Students and job-seekers receive a high volume of emails related to:
- Job applications
- Recruiter communications
- Assignments and assessments
- Interviews
- Rejections and offers
- Job platform notifications (LinkedIn, Naukri, etc.)

Existing email systems:
- Treat all emails equally
- Provide no lifecycle awareness
- Mix high-signal and low-signal content
- Create cognitive overload
- Offer no safety guarantees

The Career Engine exists to **extract structured career intelligence**
from raw email signals in a **safe, deterministic, and explainable**
manner.

---

## 3. Target Consumers of This Engine

This engine is intended to be used by:
- Desktop applications
- Local services
- Secure client-side products

This engine is **not** intended to be:
- A standalone application
- A network service
- A cloud API
- A background daemon

---

## 4. Core Responsibilities (MUST HAVE)

The engine MUST provide the following capabilities.

---

### 4.1 Career Email Detection

- Identify whether an email is career-related
- Distinguish career emails from personal or irrelevant emails
- Operate using deterministic logic

---

### 4.2 Job Classification

For career-related emails, classify into one or more categories:

- Application Confirmation
- Assignment / Assessment
- Interview / Scheduling
- Selection / Offer
- Rejection
- Recruiter Outreach
- Job Advertisement / Promotion

Classification must include:
- Confidence score
- Reasoning trace (rule-level explanation)

---

### 4.3 Platform Noise Suppression

- Identify low-signal emails from job platforms
- Suppress repetitive, promotional, or irrelevant notifications
- Preserve high-signal recruiter or application-status emails

Noise suppression must be conservative and reversible.

---

### 4.4 Job Lifecycle Inference

- Infer job entities from emails
- Track lifecycle stages over time:
  - Applied
  - Assignment
  - Interview
  - Selected / Rejected
- Update lifecycle deterministically as new emails arrive

Lifecycle inference must not rely on external state.

---

### 4.5 Safety & Protection Logic

- Identify critical emails (offers, assignments, interviews)
- Prevent unsafe deletion decisions
- Support safe-to-delete recommendations
- Surface uncertainty explicitly

Safety must always override convenience.

---

## 5. Non-Goals (MUST NEVER DO)

The engine MUST NOT:

- Render any UI
- Manage user interaction flows
- Perform network I/O
- Authenticate users
- Handle OAuth flows
- Call external APIs
- Store plaintext credentials
- Execute arbitrary code
- Learn from external data sources
- Self-modify behavior at runtime

Any request for these features must be rejected.

---

## 6. Functional Requirements

### 6.1 Determinism

- Same input → same output
- No randomness
- No hidden mutable global state

---

### 6.2 Explainability

- Every classification must be explainable
- Rules must be inspectable
- Decisions must be traceable

---

### 6.3 Local-Only Operation

- All logic must function offline
- No cloud dependency
- No telemetry requirement

---

### 6.4 Extensibility (Controlled)

- Rules may be extended via data/config
- Core logic must remain stable
- Extensibility must not weaken security

---

## 7. Non-Functional Requirements

### Performance
- Must handle large email datasets efficiently
- Must avoid unnecessary allocations
- Must not block calling applications

### Security
- Encrypted storage where applicable
- Secure memory handling
- Fail-closed behavior

### Reliability
- Explicit error reporting
- No silent failures
- Predictable behavior under stress

---

## 8. Interfaces & Integration

- Engine must expose a **clean, minimal C++ API**
- No assumptions about UI or platform
- No static initialization side effects

Integration responsibility lies with the caller.

---

## 9. Success Criteria

The engine is considered successful if it:
- Reduces visible job-related noise significantly
- Correctly identifies high-signal career events
- Never causes loss of critical career data
- Maintains user trust through predictability

---

## 10. Future Considerations (NOT COMMITMENTS)

Possible future extensions:
- More refined classification rules
- Better lifecycle heuristics
- Optional local ML assistance

These are **not guaranteed** and must respect all existing constraints.

---

## 11. Final Authority

This PRD is authoritative.

If any code, test, or design decision conflicts with this document,
the document must be followed and the code corrected.
