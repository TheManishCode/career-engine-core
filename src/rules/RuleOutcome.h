#ifndef CAREER_ENGINE_RULES_RULE_OUTCOME_H
#define CAREER_ENGINE_RULES_RULE_OUTCOME_H

#include <cstdint>
#include <optional>

#include "../types/ClassificationResult.h"

namespace career_engine {

// ============================================================================
// Match State
// ============================================================================

/// Ternary match state for rule evaluation.
/// Represents whether a rule matched, did not match, or abstained.
enum class MatchState : std::uint8_t {
    /// Rule evaluated and did not match.
    NoMatch,

    /// Rule evaluated and matched.
    Match,

    /// Rule chose not to evaluate (e.g., not applicable to input).
    Abstain
};

// ============================================================================
// Safety Assertion
// ============================================================================

/// Tri-state safety assertion from a rule.
/// Safety assertions are monotonic and non-overridable:
/// - Once AssertUnsafe is asserted, it cannot be overridden to AssertSafe.
/// - NoOpinion does not affect aggregation.
enum class SafetyAssertion : std::uint8_t {
    /// Rule has no opinion on this safety aspect.
    NoOpinion,

    /// Rule asserts this aspect is safe (e.g., safe to delete).
    AssertSafe,

    /// Rule asserts this aspect is unsafe (e.g., must not delete).
    /// This assertion is non-overridable by subsequent rules.
    AssertUnsafe
};

// ============================================================================
// Safety Contribution
// ============================================================================

/// Safety-related contributions from a rule evaluation.
/// Each field is an independent tri-state assertion.
/// Aggregation is monotonic: AssertUnsafe cannot be overridden.
struct SafetyContribution final {
    /// Assertion regarding safe_to_delete flag.
    /// AssertUnsafe means the email must NOT be auto-deleted.
    const SafetyAssertion safe_to_delete;

    /// Assertion regarding requires_review flag.
    /// AssertUnsafe means human review IS required.
    const SafetyAssertion requires_review;
};

// ============================================================================
// Classification Contribution
// ============================================================================

/// Classification-related contribution from a rule evaluation.
/// Rules may suggest a category or have no opinion.
struct ClassificationContribution final {
    /// Suggested signal category, if any.
    /// std::nullopt indicates the rule has no category opinion.
    const std::optional<SignalCategory> suggested_category;

    /// Confidence weight for this rule's contribution.
    /// Range: [0, 100]. Does not imply probability.
    /// Only meaningful if suggested_category has a value.
    const std::uint8_t confidence_weight;
};

// ============================================================================
// Advisory Contribution
// ============================================================================

/// Advisory-related contribution from a rule evaluation.
/// Advisory rules may adjust confidence or add explanation metadata.
struct AdvisoryContribution final {
    /// Confidence adjustment delta.
    /// Positive values increase confidence; negative values decrease.
    /// Range: [-50, +50]. std::nullopt means no adjustment.
    const std::optional<std::int8_t> confidence_delta;

    /// Additional rule that should be recorded in explanation metadata.
    /// std::nullopt if no additional explanation rule applies.
    const std::optional<RuleId> explanation_rule;
};

// ============================================================================
// Rule Outcome
// ============================================================================

/// Immutable outcome of evaluating a single rule against a RuleContext.
///
/// Design:
/// - Represents the rule's semantic contribution, not final decisions
/// - Phase-aware: contributions are interpreted by the RuleEngine per phase
/// - Suitable for deterministic aggregation
/// - No aggregation logic within this type
///
/// Ownership:
/// - Fully self-contained, no external references
/// - Immutable after construction
struct RuleOutcome final {
    /// The rule that produced this outcome.
    const RuleId rule_id;

    /// Whether the rule matched, did not match, or abstained.
    const MatchState match_state;

    /// Safety-related contributions.
    /// Meaningful in Safety phase; may be present in other phases.
    const SafetyContribution safety;

    /// Classification-related contributions.
    /// Meaningful in Classification and Noise phases.
    const ClassificationContribution classification;

    /// Advisory-related contributions.
    /// Meaningful in Advisory phase.
    const AdvisoryContribution advisory;
};

} // namespace career_engine

#endif // CAREER_ENGINE_RULES_RULE_OUTCOME_H
