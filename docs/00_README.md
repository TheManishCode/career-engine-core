# Career Engine — Documentation Index

## Purpose of This Repository

This repository contains the **C++ Core Engine** for a larger product.
It is **NOT** the full application.

This engine is responsible for:
- Deterministic email classification
- Career/job intelligence extraction
- Noise suppression (LinkedIn, Naukri, etc.)
- Rule-based decision logic
- Security-sensitive processing
- Local-first, privacy-preserving computation

There is:
- ❌ No UI
- ❌ No networking stack
- ❌ No OAuth flows
- ❌ No cloud infrastructure
- ❌ No web services

Those belong in other repositories.

---

## How to Read This Documentation (IMPORTANT)

All documentation is organized by **intent**:

1. **WHY** — What problem this engine solves  
2. **HOW** — How the engine is designed  
3. **RULES** — What must never be violated  

LLMs and humans **must read in this order**.

---

## Documentation Structure

### 1️⃣ Intent (WHY)

Location: docs/intent/

Contains:
- Product requirements for the engine
- Explicit goals and non-goals
- Design philosophy

Start here to understand **what this engine exists to do**.

---

### 2️⃣ Architecture (HOW)

Location: docs/architecture/


Contains:
- Module boundaries
- Data flow
- Dependency rules

Read this before adding or modifying any code.

---

### 3️⃣ Security (NON-NEGOTIABLE)

Location: docs/security/


Contains:
- Threat model
- Encryption rules
- Memory safety rules
- Secure coding constraints

**Security rules override all other concerns**, including performance
and convenience.

---

### 4️⃣ Engineering Standards (HOW TO CODE)

Location: docs/engineering/

Contains:
- C++ coding standards
- Error-handling rules
- Performance expectations
- Dependency restrictions

All code must comply with these documents.

---

### 5️⃣ Lifecycle & Versioning

Location: docs/lifecycle/


Contains:
- Versioning rules
- Backward compatibility policy
- Deprecation strategy

This engine is expected to be reused long-term.

---

### 6️⃣ Automation (CI / Testing)

Location: docs/automation/


Contains:
- CI/CD expectations
- Testing strategy
- Release process

Automation must preserve determinism and security.

---

### 7️⃣ Intelligence & ML Boundaries

Location: docs/intelligence/

Contains:
- Classification strategy
- Rule engine model
- ML usage boundaries
- Explicit MLOps exclusions

This engine is **rule-first, ML-optional**, and local-only.

---

### 8️⃣ LLM Instructions (CRITICAL)

Location: docs/llm_instructions/

These files exist **specifically for AI coding assistants**.

They define:
- What LLMs are allowed to generate
- What LLMs must never suggest
- Coding style for generated code
- Prompting rules

If LLM output conflicts with these files, the files win.

---

## Absolute Rules (Do Not Break)

- This repository must remain a **C++ static library**
- No UI code may be added
- No network servers or HTTP clients
- No cloud dependencies
- No plaintext secrets
- No dynamic code execution
- No hidden side effects

Violations indicate incorrect usage of this repository.

---

## Contribution Order (MANDATORY)

Before writing or modifying code, contributors must read:

1. `docs/intent/ENGINE_PHILOSOPHY.md`
2. `docs/security/THREAT_MODEL.md`
3. `docs/architecture/OVERVIEW.md`
4. `docs/engineering/CODING_STANDARDS.md`
5. `docs/llm/CONTEXT.md` (for AI-assisted coding)

Skipping these leads to incorrect design decisions.

---

## Final Note

This engine is designed to be:
- Predictable
- Secure
- Deterministic
- Reusable
- Boring at the edges
- Powerful at the core

If something feels convenient but violates these principles,
it should not be implemented.
