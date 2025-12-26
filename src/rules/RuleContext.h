#ifndef CAREER_ENGINE_RULES_RULE_CONTEXT_H
#define CAREER_ENGINE_RULES_RULE_CONTEXT_H

#include <cstdint>

#include "../types/NormalizedEmail.h"

namespace career_engine {

// ============================================================================
// Rule Phase
// ============================================================================

/// Semantic phase of rule evaluation.
/// Rules execute within a specific phase; the RuleEngine controls ordering.
/// Phases are evaluated in the order defined here.
enum class RulePhase : std::uint8_t {
    /// Safety rules run first.
    /// Determine safe_to_delete and requires_review flags.
    /// These rules protect critical career signals from accidental loss.
    Safety,

    /// Classification rules assign the primary signal category.
    /// Determine Offer, Rejection, Interview, Assignment, RecruiterOutreach.
    Classification,

    /// Noise rules identify low-value or promotional content.
    /// Determine Advertisement classification and noise suppression.
    Noise,

    /// Advisory rules provide supplementary signals.
    /// May adjust confidence or add explanation metadata.
    /// Do not override Safety or Classification decisions.
    Advisory
};

// ============================================================================
// Rule Context
// ============================================================================

/// Immutable, read-only context passed to all rule evaluations.
///
/// Design:
/// - Contains only the input email and current evaluation phase
/// - Rules must not see or depend on partial classification state
/// - All accumulation occurs in the RuleEngine, not in rules
/// - No mutation, no logic, no helper methods
///
/// Ownership:
/// - Contains a const reference to externally-owned NormalizedEmail
/// - Lifetime of RuleContext must not exceed lifetime of referenced email
/// - No dynamic allocation
struct RuleContext final {
    /// The normalized email being classified.
    /// Owned externally; must remain valid for the lifetime of this context.
    const NormalizedEmail& input;

    /// The current evaluation phase.
    /// Determines which category of rules is being executed.
    const RulePhase phase;
};

} // namespace career_engine

#endif // CAREER_ENGINE_RULES_RULE_CONTEXT_H
