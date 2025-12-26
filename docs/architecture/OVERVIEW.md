
All data flows **top-down**.
Lower layers must never depend on higher layers.

---

## Core Layers

### 1. Public Engine Interface

**Responsibility**
- Expose a minimal, stable C++ API
- Accept normalized input data
- Return structured, deterministic results

**Characteristics**
- Thin layer
- No business logic
- No stateful behavior beyond coordination
- No platform assumptions

**Rules**
- Must not perform classification itself
- Must not bypass security or safety checks
- Must not expose internal data structures directly

---

### 2. Core Intelligence Pipeline

**Responsibility**
- Extract signals from inputs
- Apply rule-based classification
- Perform noise suppression
- Infer job lifecycle state
- Produce explainable outputs

**Subcomponents**
- Career detection
- Job classification
- Platform noise filtering
- Confidence scoring
- Lifecycle inference

**Rules**
- No I/O
- No encryption logic
- No storage access
- Deterministic execution only

This layer contains the **primary business logic**.

---

### 3. Security & Safety Layer

**Responsibility**
- Enforce security guarantees
- Protect sensitive data
- Prevent unsafe operations
- Guard critical decisions

**Subcomponents**
- Encryption utilities
- Secure memory handling
- Safe-to-delete guards
- Validation and sanitization

**Rules**
- Must be applied before persistence
- Must not be bypassed by callers
- Must fail closed on error

Security is **orthogonal** to intelligence logic.

---

### 4. Storage & Persistence Layer

**Responsibility**
- Abstract local persistence
- Store structured engine outputs
- Handle encrypted storage where applicable

**Characteristics**
- Interface-driven
- Replaceable implementation
- No business logic

**Rules**
- No classification logic
- No rule evaluation
- No direct access from UI layers

Persistence is optional but supported.

---

## Data Flow Model

The engine processes data using a **strict, staged pipeline**:

Input Data
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
Safety Checks
↓
Structured Output


### Key Properties
- Each stage has a single responsibility
- Each stage is independently testable
- No stage may be skipped
- No backward data flow

---

## Dependency Rules (Summary)

- Public API → Core Pipeline
- Core Pipeline → Security Layer
- Security Layer → Storage Layer (optional)
- Reverse dependencies are forbidden

No module may depend on:
- UI code
- Network code
- Platform-specific APIs (unless abstracted)

---

## State Management

- Prefer immutable data structures
- Avoid global mutable state
- Explicitly model all state transitions
- Persist state only through defined interfaces

Hidden or implicit state is forbidden.

---

## Error Propagation

- Errors propagate upward explicitly
- No silent failure
- No exception leakage across module boundaries
- Errors must include context for diagnosis

The engine must remain predictable under failure.

---

## Testing Implications

This architecture enables:
- Unit testing at every layer
- Deterministic test outcomes
- Mockable storage interfaces
- Isolated security validation

If code is hard to test, it likely violates architecture.

---

## Extension Model

Extensions must:
- Respect existing boundaries
- Be additive, not invasive
- Avoid modifying core assumptions
- Maintain determinism and security

If an extension requires breaking boundaries,
it belongs in another repository.

---

## Final Architectural Rule

The Career Engine architecture exists to:
- Protect correctness
- Preserve security
- Enable long-term maintenance

If a design choice simplifies one layer but complicates another,
the choice must be rejected.

Architecture is a **constraint**, not a suggestion.
