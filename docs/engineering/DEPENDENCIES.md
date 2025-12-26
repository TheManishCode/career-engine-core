# Dependencies Policy — Career Engine Core

## Purpose of This Document

This document defines **which dependencies are allowed**, **which are restricted**,
and **which are forbidden** in the Career Engine.

Dependencies shape:
- Security posture
- Build stability
- Portability
- Long-term maintenance cost

If a dependency violates this document, it must not be added.

---

## Dependency Philosophy

The Career Engine follows a **minimal-dependency philosophy**.

Principles:
- Prefer standard C++ over third-party code
- Add dependencies only when strictly necessary
- Isolate dependencies behind interfaces
- Avoid dependency sprawl

Every dependency increases attack surface and maintenance burden.

---

## Allowed Dependencies (DEFAULT)

### 1. C++ Standard Library

Allowed without approval:
- Containers (`<vector>`, `<array>`, `<map>`)
- Utilities (`<optional>`, `<variant>`, `<span>`)
- Algorithms (`<algorithm>`)
- Memory (`<memory>`)
- Time (`<chrono>`)

Rules:
- Prefer value semantics
- Avoid locale-sensitive behavior
- Avoid undefined behavior

---

### 2. Compiler & Toolchain

Allowed:
- MSVC / Clang / GCC (standard-conforming)
- CMake build system
- Standard sanitizers and analyzers

Tooling must not affect runtime behavior.

---

## Restricted Dependencies (REQUIRE EXPLICIT APPROVAL)

These dependencies may be used **only with justification** and documentation.

### 1. Cryptography Libraries

Allowed only if:
- OS primitives are insufficient
- Library is mature and audited
- Usage is minimal and isolated

Rules:
- Must live inside `security/`
- Must not leak into public APIs
- Must be documented in security docs

---

### 2. Storage Libraries

Examples:
- SQLite

Rules:
- Must be wrapped behind a storage interface
- Must not expose SQL or schemas to callers
- Must not embed business logic

---

### 3. Utility Libraries

Examples:
- Small header-only helpers

Rules:
- Must be strictly necessary
- Must not introduce macros or global state
- Must not duplicate standard library features

---

## Forbidden Dependencies (ABSOLUTE)

The following are **never allowed** in this repository.

### ❌ Networking & Communication
- HTTP clients
- Socket libraries
- IPC frameworks
- Messaging systems

---

### ❌ UI & Presentation
- Qt
- WinUI / WPF
- GTK
- Rendering engines

---

### ❌ Cloud & Services
- Cloud SDKs
- Telemetry libraries
- Analytics frameworks
- Remote configuration systems

---

### ❌ Frameworks & Heavy Abstractions
- ORMs
- Dependency injection frameworks
- Reflection frameworks
- Scripting runtimes

---

### ❌ Build-Time Network Dependencies
- Downloading code during build
- Fetching remote resources
- Auto-updating components

Builds must be fully offline and reproducible.

---

## Dependency Introduction Process

Before adding a dependency, answer:

1. What problem does this solve?
2. Why can’t the standard library solve it?
3. What security risk does it introduce?
4. How will it be isolated?
5. How will it be updated or removed?

If any answer is unclear, the dependency must not be added.

---

## Versioning Rules

- Pin dependency versions explicitly
- Avoid floating versions
- Document version upgrades
- Test upgrades thoroughly

Uncontrolled upgrades are forbidden.

---

## Dependency Auditing

Dependencies must:
- Be periodically reviewed
- Be checked for vulnerabilities
- Be removable without major refactor

If a dependency becomes unmaintained,
it must be removed or replaced.

---

## LLM-Specific Rules

AI coding assistants must:
- Prefer standard library solutions
- Avoid suggesting new dependencies
- Ask for approval before introducing libraries
- Never assume a dependency is acceptable

If unsure, generate code without adding dependencies.

---

## Final Dependency Rule

Dependencies are liabilities.

If a dependency does not clearly justify its cost,
it must not be added to the Career Engine.
