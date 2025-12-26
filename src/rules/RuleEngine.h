#ifndef CAREER_ENGINE_RULES_RULE_ENGINE_H
#define CAREER_ENGINE_RULES_RULE_ENGINE_H

#include <span>
#include <vector>

#include "Rule.h"
#include "RuleContext.h"
#include "RuleOutcome.h"
#include "../types/NormalizedEmail.h"

namespace career_engine {

// ============================================================================
// Rule Engine
// ============================================================================

/// Orchestration interface for evaluating rules in a phased, deterministic manner.
///
/// Design:
/// - Stateless: no internal rule storage or configuration
/// - Deterministic: same input and rules produce same outcomes
/// - Non-owning: borrows rules via span, does not own them
/// - No interpretation: returns raw outcomes without aggregation or filtering
///
/// Evaluation order:
/// 1. Safety phase — all rules evaluated with RulePhase::Safety
/// 2. Classification phase — all rules evaluated with RulePhase::Classification
/// 3. Noise phase — all rules evaluated with RulePhase::Noise
/// 4. Advisory phase — all rules evaluated with RulePhase::Advisory
///
/// Contract:
/// - Rules are invoked in span order within each phase
/// - All outcomes are collected regardless of match state
/// - No conflict resolution or confidence calculation
/// - Caller is responsible for interpreting outcomes
class RuleEngine final {
public:
    RuleEngine() = default;
    ~RuleEngine() = default;

    // Non-copyable, non-movable (stateless orchestrator)
    RuleEngine(const RuleEngine&) = delete;
    RuleEngine& operator=(const RuleEngine&) = delete;
    RuleEngine(RuleEngine&&) = delete;
    RuleEngine& operator=(RuleEngine&&) = delete;

    /// Evaluates all provided rules against the input email in phased order.
    ///
    /// Phases are evaluated in order: Safety, Classification, Noise, Advisory.
    /// Within each phase, rules are evaluated in span order.
    /// All outcomes are returned without filtering or interpretation.
    ///
    /// Guarantees:
    /// - Deterministic: same input and rules produce same outcomes
    /// - No side effects beyond outcome collection
    /// - No exceptions thrown
    ///
    /// @param email The normalized email to classify
    /// @param rules Non-owning span of rule pointers to evaluate
    /// @return Vector of all RuleOutcome objects produced by evaluation
    [[nodiscard]] std::vector<RuleOutcome> evaluate(
        const NormalizedEmail& email,
        std::span<const Rule* const> rules) const noexcept;
};

} // namespace career_engine

#endif // CAREER_ENGINE_RULES_RULE_ENGINE_H
