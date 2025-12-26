# Module Boundaries — Career Engine Core

## Purpose of This Document

This document defines **strict ownership and responsibility boundaries**
for every major module in the Career Engine.

It answers:
- What each module owns
- What each module is allowed to do
- What each module must NEVER do
- How modules may interact

If code crosses these boundaries, it is incorrect
even if it “works”.

---

## Boundary Enforcement Principle

Each module must:
- Have a single, clear responsibility
- Expose a minimal public surface
- Avoid knowledge of unrelated modules
- Communicate only through defined interfaces

Boundary violations lead to:
- Security risks
- Hidden coupling
- Testing difficulty
- Long-term maintenance failure

---

## Module Map (Authoritative)

src/
├── engine/ # Public API and orchestration
├── classifier/ # Career and job classification logic
├── noise_filter/ # Platform noise suppression
├── lifecycle/ # Job lifecycle inference
├── security/ # Security primitives and guards
├── storage/ # Persistence abstractions
└── utils/ # Shared utilities (pure, stateless)


Each folder corresponds to **one logical module**.

---

## 1. `engine/` — Public Interface & Orchestration

### Owns
- Public C++ API
- Input/output data structures
- Pipeline orchestration
- Coordination between modules

### Must Do
- Call modules in correct order
- Enforce architectural flow
- Surface errors clearly

### Must NOT Do
- Implement classification logic
- Perform rule evaluation
- Access storage directly
- Perform encryption directly
- Contain business logic

### Allowed Dependencies
- classifier/
- noise_filter/
- lifecycle/
- security/
- storage/ (via interface)

---

## 2. `classifier/` — Career & Job Classification

### Owns
- Career email detection
- Job category classification
- Confidence scoring logic
- Rule-based decision logic

### Must Do
- Produce deterministic classifications
- Provide reasoning traces
- Operate purely on inputs

### Must NOT Do
- Perform I/O
- Access storage
- Encrypt data
- Track lifecycle state
- Suppress noise

### Allowed Dependencies
- utils/
- security/ (validation only)

---

## 3. `noise_filter/` — Platform Noise Suppression

### Owns
- Detection of low-signal emails
- Platform-specific noise rules
- Suppression recommendations

### Must Do
- Be conservative and reversible
- Operate deterministically
- Preserve high-signal content

### Must NOT Do
- Perform classification
- Infer lifecycle state
- Modify stored data
- Delete or discard data

### Allowed Dependencies
- utils/
- classifier/ (read-only signals)

---

## 4. `lifecycle/` — Job Lifecycle Inference

### Owns
- Job entity creation
- Lifecycle state transitions
- Timeline inference logic

### Must Do
- Infer state conservatively
- Maintain explicit state transitions
- Avoid speculative jumps

### Must NOT Do
- Classify individual emails
- Suppress noise
- Perform encryption
- Persist data directly

### Allowed Dependencies
- classifier/
- utils/

---

## 5. `security/` — Security & Safety Primitives

### Owns
- Encryption utilities
- Secure memory handling
- Validation and sanitization
- Safe-to-delete guards

### Must Do
- Fail closed on error
- Enforce security invariants
- Zero sensitive memory

### Must NOT Do
- Implement business logic
- Perform classification
- Manage lifecycle state
- Access UI or network APIs

### Allowed Dependencies
- utils/
- OS cryptographic primitives (abstracted)

---

## 6. `storage/` — Persistence Abstraction

### Owns
- Data persistence interfaces
- Encrypted storage implementation
- Schema evolution support

### Must Do
- Abstract underlying storage
- Preserve data integrity
- Support safe recovery

### Must NOT Do
- Perform classification
- Enforce business rules
- Apply security policy decisions
- Infer lifecycle state

### Allowed Dependencies
- security/
- utils/

---

## 7. `utils/` — Shared Pure Utilities

### Owns
- Pure helper functions
- Value-type utilities
- Common data structures

### Must Do
- Remain stateless
- Remain deterministic
- Avoid side effects

### Must NOT Do
- Access storage
- Perform encryption
- Maintain state
- Encode business logic

### Allowed Dependencies
- Standard C++ library only

---

## Forbidden Cross-Module Dependencies

The following are **explicitly forbidden**:

- classifier → storage
- classifier → lifecycle
- noise_filter → storage
- lifecycle → storage
- utils → any other module
- any module → UI or network code

If a dependency feels necessary but is forbidden,
the design is wrong and must be revisited.

---

## Dependency Direction Rule

All dependencies must follow this direction:

engine
↓
[classifier | noise_filter | lifecycle]
↓
security
↓
storage


No upward or sideways dependencies.

---

## Boundary Violation Checklist

Before merging code, ask:
- Does this module own this responsibility?
- Does this introduce hidden coupling?
- Does this bypass another module?
- Can this logic be tested in isolation?

If any answer is unclear, the code violates boundaries.

---

## Final Boundary Rule

Modules are contracts.

Breaking a module boundary may speed up development temporarily,
but it guarantees future failure.

**Respect boundaries, or redesign the feature.**
