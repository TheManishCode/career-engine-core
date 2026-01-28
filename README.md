# Career Engine — Core Intelligence
 
## Overview

The Career Engine is a **local-first, deterministic intelligence core**
designed to help users **understand, organize, and reason about career-related
emails and signals**.

This repository contains **only the core engine**.

It does NOT:
- Provide a UI
- Connect to the internet
- Send or receive emails
- Authenticate users
- Perform automation actions

It produces **structured, explainable intelligence** that other applications
may consume.

---

## What This Project Is

The Career Engine is:

- A **rule-first intelligence engine**
- Fully **deterministic**
- **Explainable by design**
- **Privacy-preserving**
- Safe to run locally
- Designed for long-term correctness

Primary responsibilities:
- Classify career-related emails
- Distinguish signal vs noise
- Protect critical career events
- Provide confidence and explanations
- Preserve user trust

---

## What This Project Is NOT

This project is **explicitly not**:

- A web application
- An email client
- A background service
- A cloud service
- An ML platform
- An automation system
- A decision-maker

The engine **advises**.  
The user (or calling application) decides.

---

## Design Principles (NON-NEGOTIABLE)

1. **Determinism**
   - Same input → same output
   - No randomness
   - No hidden state

2. **Explainability**
   - Every decision is traceable
   - Rules are explicit
   - No black-box logic

3. **Safety First**
   - Critical signals are protected
   - Ambiguity is preserved, not guessed
   - False positives are worse than false negatives

4. **Privacy by Default**
   - No telemetry
   - No networking
   - No data exfiltration

5. **Rule-First Intelligence**
   - Rules define truth
   - Models (if ever used) are advisory only

---

## Repository Structure

```
core_engine/
├── docs/
│   ├── intent/
│   ├── architecture/
│   ├── security/
│   ├── engineering/
│   ├── lifecycle/
│   ├── operations/
│   ├── intelligence/
│   └── llm/
├── src/
├── tests/
├── core_engine.vcxproj
└── README.md
```

📌 **The `docs/` folder is the authority.**

---

## How to Get Started

1. Read `docs/intent/PRD.md`
2. Read `docs/intelligence/CLASSIFICATION_STRATEGY.md`
3. Read `docs/intelligence/RULE_ENGINE.md`
4. Read `docs/security/THREAT_MODEL.md`
5. Read `docs/llm/DO_NOT_DO.md`

---

## Contribution Rules

- Follow all documents in `docs/`
- Preserve determinism
- Add tests for new logic
- No networking, telemetry, or UI
- No silent behavior changes

---

## Final Statement

This engine may influence real careers.

> **When in doubt, do less — but do it correctly.**
