# Memory Safety — Career Engine Core

## Purpose of This Document

This document defines **mandatory memory safety rules** for the Career Engine.

Because this engine is written in **C++** and handles **security-sensitive data**,
memory safety is a **first-order security requirement**, not an implementation detail.

If code violates this document, it is considered **unsafe and incorrect**.

---

## Memory Safety Philosophy

Memory errors are security bugs.

The engine must assume:
- Memory can be inspected (debuggers, crash dumps, malware)
- Undefined behavior is exploitable
- Convenience leads to unsafe patterns

Therefore:
- Safety > performance
- Explicit ownership > implicit sharing
- RAII > manual management

---

## Core Principles

### 1. RAII Is Mandatory

All resources must be managed via **RAII**:
- Memory
- File handles
- Locks
- Cryptographic material

Rules:
- No raw `new` / `delete`
- No manual `malloc` / `free`
- Prefer `std::unique_ptr`, `std::vector`, `std::array`

If RAII cannot be used, the design is wrong.

---

### 2. No Undefined Behavior (ABSOLUTE)

The engine must not rely on:
- Uninitialized memory
- Dangling references
- Out-of-bounds access
- Type punning
- Strict-aliasing violations

Code that *“usually works”* is unacceptable.

---

### 3. Ownership Must Be Explicit

Every piece of memory must have:
- A single clear owner
- A well-defined lifetime
- A documented transfer of ownership (if any)

Rules:
- Prefer move semantics
- Avoid shared ownership
- Use `std::shared_ptr` only with strong justification

---

## Sensitive Data Handling (CRITICAL)

### What Is Sensitive

Sensitive data includes:
- Encryption keys
- Derived secrets
- Decrypted email content
- Career classifications (when critical)
- Authorization context

---

### Zeroization Rules

Sensitive memory must:
- Be wiped immediately after use
- Be wiped before destruction
- Use secure zeroization (not `memset` optimized away)

Zeroization must:
- Be explicit
- Be deterministic
- Be tested

Relying on destructor timing alone is insufficient.

---

### Lifetime Minimization

Rules:
- Keep sensitive data in memory for the shortest time possible
- Avoid long-lived buffers
- Avoid caching decrypted data

If sensitive data must persist longer,
it must be encrypted or otherwise protected.

---

## Stack vs Heap Usage

### Stack Allocation (Preferred)
- Short-lived data
- Small buffers
- Deterministic lifetimes

### Heap Allocation (Controlled)
- Large data
- Variable-size collections
- Must still use RAII

Rules:
- Avoid heap allocation in hot paths
- Avoid fragmentation-prone patterns
- Never allocate sensitive data unnecessarily

---

## References & Views

Rules:
- Prefer value types where practical
- Prefer `std::span<const T>` for read-only views
- Avoid non-owning raw pointers
- Never return references to internal buffers

Dangling views are security bugs.

---

## Concurrency & Thread Safety

If concurrency is used:
- Ownership rules must still apply
- Shared state must be explicit
- Data races are forbidden

Rules:
- Prefer immutability
- Avoid global mutable state
- Avoid implicit thread-local storage

If thread safety is unclear, single-threaded is safer.

---

## Error Handling & Memory Safety

- No throwing exceptions from destructors
- No memory leaks on error paths
- Cleanup must be guaranteed even on failure

Error handling must not introduce leaks or corruption.

---

## Forbidden Practices (ABSOLUTE)

The following are strictly forbidden:

- Raw owning pointers
- Manual memory management
- `reinterpret_cast` for logic
- `const_cast` to mutate state
- C-style arrays for dynamic data
- Buffer size assumptions
- Reliance on compiler-specific behavior

Any occurrence is a defect.

---

## Tooling Expectations

Code should be written assuming:
- Static analysis will be used
- Sanitizers may be enabled
- Warnings are treated as errors

Unsafe code will not be “fixed later”.

---

## LLM-Specific Rules

AI coding assistants must:
- Prefer RAII containers
- Avoid unsafe pointer arithmetic
- Avoid raw memory manipulation
- Avoid micro-optimizations that reduce safety

If unsure, generate **simpler, safer code**.

---

## Final Memory Safety Rule

Memory safety protects:
- Security
- Correctness
- User trust

If a feature requires violating memory safety,
the feature must not be implemented.

There are no exceptions.
