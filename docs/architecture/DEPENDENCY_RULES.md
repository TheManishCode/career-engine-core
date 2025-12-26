# Dependency Rules — Career Engine Core

## Purpose of This Document

This document defines **which dependencies are allowed, restricted, or forbidden**
within the Career Engine.

Its goals are to:
- Prevent hidden coupling
- Preserve deterministic behavior
- Protect security guarantees
- Keep build times and complexity low
- Stop accidental architectural erosion (especially via LLMs)

If code violates these rules, it must be refactored or rejected.

---

## Core Dependency Principle

Dependencies must be:
- **Minimal**
- **Explicit**
- **One-directional**
- **Justified**

Convenience is never a valid reason to add a dependency.

---

## Allowed Dependency Categories

### 1. Standard C++ Library

Allowed:
- `<string>`, `<string_view>`
- `<vector>`, `<array>`
- `<map>`, `<unordered_map>` (with care)
- `<optional>`, `<variant>`
- `<chrono>`
- `<algorithm>`, `<utility>`
- `<memory>` (RAII only)
- `<span>` (read-only preferred)

Rules:
- Prefer value types
- Avoid unnecessary dynamic allocation
- Avoid locale-dependent behavior

---

### 2. Internal Engine Modules (Controlled)

Allowed only as defined in `MODULE_BOUNDARIES.md`.

**Permitted Direction (Summary):**

engine
↓
[classifier | noise_filter | lifecycle]
↓
security
↓
storage


Rules:
- No reverse dependencies
- No sideways dependencies unless explicitly allowed
- All dependencies must be declared in headers clearly

---

### 3. Cryptographic & OS Primitives (Abstracted)

Allowed:
- OS-provided cryptographic primitives
- Secure random number generators
- Memory zeroization utilities

Rules:
- Must be wrapped behind engine abstractions
- Must not leak platform-specific APIs into public headers
- Must not introduce runtime configuration complexity

---

## Restricted Dependencies (Require Justification)

These dependencies may be used **only with strong justification** and documentation.

### 1. Third-Party Libraries

Allowed only if:
- License is permissive and compatible
- Library is mature and actively maintained
- Library is strictly necessary
- No simpler alternative exists

Examples (case-by-case):
- SQLite (via abstraction)
- Minimal crypto helpers (if OS primitives insufficient)

Rules:
- Must be isolated in a single module
- Must not be exposed through public API
- Must be documented in `engineering/DEPENDENCIES.md`

---

### 2. Platform-Specific APIs

Allowed only if:
- Encapsulated behind interfaces
- Absolutely required
- Non-portable code is isolated

Rules:
- No platform assumptions in core logic
- No platform headers in public engine headers

---

## Forbidden Dependencies (ABSOLUTE)

The following are **never allowed** in this repository.

### ❌ Networking & I/O
- HTTP clients
- Socket APIs
- IPC frameworks
- Web libraries

### ❌ UI & Presentation
- Qt, WinUI, WPF, GTK
- Rendering libraries
- Notification systems

### ❌ Cloud & Services
- Cloud SDKs
- Telemetry libraries
- Analytics frameworks

### ❌ Dynamic Code & Scripting
- Embedded scripting engines
- Reflection-based execution
- Runtime code generation

### ❌ Heavy Frameworks
- Full ORMs
- Dependency injection frameworks
- Large utility frameworks

### ❌ Unsafe or Deprecated APIs
- C-style string manipulation
- Deprecated C++ APIs
- Undefined-behavior-prone libraries

If a dependency falls into these categories,
it must not be added under any circumstance.

---

## Header Dependency Rules

- Headers must include **only what they use**
- Avoid transitive includes
- Prefer forward declarations
- Public headers must be minimal and stable

Public headers must:
- Compile independently
- Avoid including heavy headers
- Avoid exposing implementation details

---

## Build-Time Dependency Rules

- Dependencies must not depend on build order side effects
- No code generation steps that alter behavior
- No network access during build
- Deterministic builds only

---

## Dependency Review Checklist

Before adding or modifying a dependency, answer:

1. Is this dependency absolutely necessary?
2. Does it violate any module boundary?
3. Can it be replaced with simpler logic?
4. Is its behavior deterministic?
5. Does it introduce security risk?
6. Does it complicate testing?

If any answer is unclear, the dependency should not be added.

---

## LLM-Specific Instruction

AI coding assistants must:
- Prefer standard library solutions
- Avoid introducing new libraries
- Ask for approval before suggesting third-party dependencies
- Never assume a dependency is acceptable

If uncertain, generate code **without adding dependencies**.

---

## Final Dependency Rule

Dependencies define the **shape of the system**.

Every unnecessary dependency:
- Reduces clarity
- Increases attack surface
- Increases maintenance cost

When in doubt, **do not add the dependency**.
