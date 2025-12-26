# LLM Prompting Rules — Career Engine Core

## Purpose of This Document

This document defines **how Large Language Models (LLMs) must be prompted**
when working on the Career Engine.

Correct prompting is critical because:
- LLMs optimize for helpfulness, not correctness
- Poor prompts lead to scope creep
- Ambiguous prompts lead to unsafe assumptions
- Overly open prompts break architecture and governance

If prompting violates this document, the resulting output must be rejected.

---

## Authority & Precedence

This file has **higher authority than convenience or speed**.

Prompting rules must comply with:
- PRD.md
- ENGINE_PHILOSOPHY.md
- SECURITY documents
- DO_NOT_DO.md

If a prompt conflicts with those documents,
**the prompt is invalid**.

---

## Core Prompting Principle

> **LLMs must be treated as junior contributors with zero context.**

They must be:
- Explicitly constrained
- Given clear scope
- Told what NOT to do
- Prevented from guessing

Never assume the LLM “understands the project”.

---

## Mandatory Context Injection (REQUIRED)

Every prompt MUST include:

1. **File path being worked on**
2. **Exact task**
3. **What must NOT change**
4. **Relevant governing documents**
5. **Request to ask questions if unclear**

### Minimal Valid Prompt Template

You are working on: <exact file path>

Task:
<exact, narrow task>

Constraints:
- Do not change behavior
- Do not add new features
- Do not modify public APIs
- Follow all security, lifecycle, and intelligence rules

Relevant documents:
- <list exact docs>

If anything is unclear, ask before proceeding.


Prompts without explicit constraints are invalid.

---

## Scope Control Rules (MANDATORY)

LLMs must be prompted to:

* Modify **only one file at a time**
* Stay within the requested layer (engineering, intelligence, etc.)
* Avoid touching unrelated modules
* Avoid refactors unless explicitly requested

### Forbidden Prompt Examples

❌ “Improve the code”
❌ “Make this smarter”
❌ “Refactor for performance”
❌ “Clean this up”
❌ “Optimize everything”

These prompts invite unsafe behavior.

---

## Feature Introduction Rules

If a prompt could introduce new behavior, it MUST:

* Explicitly state that new behavior is allowed
* Reference PRD.md and GOALS.md
* Specify expected impact
* Ask for a design proposal first

LLMs must NEVER introduce features silently.

---

## Architecture Respect Rules

Prompts must explicitly state:

* Which layers are allowed to change
* Which layers are forbidden to touch

Example:


You may modify classification logic.
You may NOT modify rule engine order, security, or lifecycle behavior.


Without this, LLM output is invalid.

---

## Security Prompting Rules (CRITICAL)

Any prompt involving:

* Data handling
* Storage
* Classification
* Logging
* Error handling

MUST include:


Follow all security documents.
Do not log sensitive data.
Do not weaken validation.
Fail closed on error.


Security must never be implied — it must be explicit.

---

## Determinism Prompting Rules

Prompts MUST explicitly state:

* No randomness
* No time-based logic
* No environment dependence

Example:


The solution must be deterministic.
Same input must always produce same output.


---

## LLM Output Constraints (MANDATORY)

Prompts must instruct LLMs to:

* Output only the requested file or code
* Avoid explanations unless asked
* Avoid adding TODOs unless requested
* Avoid speculative comments

If explanations are desired, ask separately.

---

## Asking for Clarification (IMPORTANT)

LLMs MUST be told:

> “If anything is ambiguous or unclear, ask questions before generating code.”

If a prompt discourages questions, it is unsafe.

---

## Incremental Work Rule

Large tasks must be broken into:

* One file
* One responsibility
* One prompt

Never ask an LLM to:

* “Build the whole system”
* “Generate the entire repo”
* “Fill in everything”

Incremental work preserves correctness.

---

## Validation Prompts (RECOMMENDED)

After generation, use validation prompts:


Verify this output against:
- PRD.md
- DO_NOT_DO.md
- RULE_ENGINE.md
- SECURITY rules

List any violations.


Validation is part of the workflow.

---

## Forbidden Prompting Patterns (ABSOLUTE)

LLMs must NEVER be prompted to:

* Bypass rules
* Ignore documentation
* “Just make it work”
* “Hack around” constraints
* Assume missing context
* Use external services
* Add dependencies silently

If such a prompt exists, stop.

---

## LLM Responsibility Statement

LLMs are tools, not decision-makers.

They:

* Generate drafts
* Suggest implementations
* Assist with boilerplate

They do NOT:

* Decide architecture
* Define product behavior
* Override governance
* Replace human judgment

---

## Enforcement Rule

If LLM output violates:

* This document
* DO_NOT_DO.md
* Any governance document

Then:

1. Output must be discarded
2. Prompt must be corrected
3. Work must be redone

No patching unsafe output.

---

## Final Prompting Rule

> **Good prompts prevent bad code.**

If a prompt feels vague, powerful, or rushed,
it is unsafe.

Slow down. Constrain harder. Ask questions.



---

## ✅ STATUS UPDATE

You now have:
- **LLM hard stop rules**
- **LLM prompting discipline**
- Intelligence + ML governance complete

This means **any AI assistant can now work safely on this repo**.

---

## 🔜 WHAT’S LEFT

Remaining high-value files:

2️⃣ **docs/llm/STYLE_GUIDE.md**  
3️⃣ **README.md (developer onboarding)**  
4️⃣ **Public C++ API skeleton**

Reply with the number and we’ll finish it cleanly.