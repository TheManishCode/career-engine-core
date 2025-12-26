# Threat Model — Career Engine Core

## Purpose of This Document

This document defines the **threat model** for the Career Engine.

It describes:
- What assets must be protected
- Who the potential attackers are
- What attack surfaces exist
- What threats are in scope
- What threats are explicitly out of scope
- How the engine must behave under attack

Security decisions **must be based on this model**.
If code contradicts this document, the code is wrong.

---

## Security Philosophy

The Career Engine is a **local-first, security-sensitive library**
that processes highly valuable personal data related to a user’s
career and identity.

The engine must assume:
- The user environment is not fully trusted
- Attackers may gain partial access to the system
- Mistakes are more costly than inconvenience

Security is treated as a **design constraint**, not a feature.

---

## Assets to Protect (WHAT MATTERS)

The engine must protect the following assets:

### 1. Career-Critical Data
- Job offer emails
- Interview communications
- Assignment and assessment details
- Recruiter communications
- Job lifecycle state

Loss or corruption of this data may cause real-world harm.

---

### 2. Sensitive Derived Intelligence
- Career classifications
- Confidence scores
- Lifecycle inferences
- Safety flags (e.g., safe-to-delete)

These outputs influence user decisions and must not be corrupted.

---

### 3. Secrets & Credentials (If Present)
- Encrypted tokens
- Encryption keys
- Derived secrets

No plaintext secrets must ever be exposed.

---

### 4. Engine Integrity
- Deterministic behavior
- Correct rule execution
- Unmodified logic

The engine must not be tricked into unsafe behavior.

---

## Threat Actors (WHO WE DEFEND AGAINST)

### 1. Malicious Local Software
- Malware on the user’s machine
- Other processes attempting to read memory or files

---

### 2. Curious or Careless Users
- Accidental deletion
- Misuse of APIs
- Unsafe configuration

The engine must protect users from themselves where possible.

---

### 3. Supply Chain Risks
- Compromised dependencies
- Malicious updates
- Tampered builds

---

### 4. Partial System Compromise
- Attacker gains read access to disk
- Attacker gains access to logs
- Attacker inspects crash dumps

The engine must minimize damage under partial compromise.

---

## Attack Surfaces (WHERE ATTACKS CAN HAPPEN)

### 1. Input Data
- Email content
- Metadata
- Timestamps
- Identifiers

All input is **untrusted**.

---

### 2. Memory
- In-memory secrets
- Intermediate data
- Buffers

Memory must be treated as observable by attackers.

---

### 3. Storage
- Local persistence
- Cached results
- Encrypted data stores

Disk access must be assumed readable.

---

### 4. Build Artifacts
- Static libraries
- Object files
- Symbols

Build outputs may be reverse engineered.

---

## In-Scope Threats (MUST DEFEND AGAINST)

The engine must actively defend against:

### 1. Data Leakage
- Plaintext secrets on disk
- Sensitive data in logs
- Leaked memory contents

---

### 2. Unsafe Deletion
- Accidental removal of critical career data
- Silent loss of job-related state

---

### 3. Input Manipulation
- Crafted emails causing misclassification
- Malicious inputs attempting rule bypass
- Edge cases causing undefined behavior

---

### 4. Memory Safety Violations
- Buffer overflows
- Use-after-free
- Dangling pointers
- Uninitialized reads

---

### 5. Logic Corruption
- Bypassing safety checks
- Skipping stages in data flow
- Violating determinism

---

## Out-of-Scope Threats (EXPLICITLY NOT HANDLED)

The engine does NOT defend against:

- Full OS compromise
- Kernel-level attackers
- Hardware attacks
- Physical access attacks
- Active network attackers (engine has no network layer)

These threats must be handled by the operating system
or the integrating application.

---

## Security Assumptions

The engine assumes:
- The compiler and standard library are trustworthy
- OS cryptographic primitives are correct
- The caller follows documented API usage
- The engine is not run with elevated privileges unnecessarily

Violating these assumptions weakens security guarantees.

---

## Security Controls (MANDATORY)

Based on this threat model, the engine must enforce:

### 1. Fail-Closed Behavior
- When in doubt, deny or protect
- Never silently allow risky behavior

---

### 2. Explicit Validation
- Validate all inputs
- Sanitize before processing
- Reject malformed data early

---

### 3. Secure Memory Handling
- Zero sensitive buffers after use
- Avoid long-lived secrets in memory
- Prefer stack allocation when safe

---

### 4. Encryption at Rest
- Encrypt sensitive stored data
- Never store plaintext secrets
- Protect key material rigorously

---

### 5. Deterministic Execution
- No randomness
- No hidden state
- No time-based behavior

Determinism reduces exploitability.

---

## Failure Handling Under Attack

When an attack or anomaly is detected:
- Surface explicit errors
- Preserve data integrity
- Avoid partial or corrupt output
- Maintain safe defaults

The engine must remain predictable under stress.

---

## LLM-Specific Security Rules

AI coding assistants must:
- Treat all input as hostile
- Avoid unsafe APIs
- Avoid undefined behavior
- Avoid convenience shortcuts
- Prefer conservative designs

If a generated solution weakens security,
it must be rejected.

---

## Final Security Rule

This engine may handle data that affects
a user’s career, opportunities, and future.

Security failures are **not acceptable trade-offs**.

If a feature cannot be implemented securely,
the feature must not be implemented at all.
