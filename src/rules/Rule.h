#ifndef CAREER_ENGINE_RULES_RULE_H
#define CAREER_ENGINE_RULES_RULE_H

#include "RuleContext.h"
#include "RuleOutcome.h"
#include "../types/ClassificationResult.h"

namespace career_engine {

// ============================================================================
// Rule Interface
// ============================================================================

/// Abstract interface representing a single rule in the rule engine.
///
/// Design:
/// - Stateless and pure: same input always produces same output
/// - Deterministic: no randomness, no hidden state
/// - No ownership of data: rules do not store context or results
/// - Safe to store and invoke via base pointer/reference
///
/// Contract:
/// - Each rule has a stable, unique RuleId
/// - Rules evaluate a RuleContext and produce a RuleOutcome
/// - Rules must not access RuleEngine, ClassificationResult, or mutable state
/// - Rules must not perform logging or diagnostics
///
/// Lifetime:
/// - Rules are owned by the RuleEngine or rule registry
/// - Virtual destructor ensures safe polymorphic deletion
class Rule {
public:
    /// Virtual destructor for safe polymorphic deletion.
    virtual ~Rule() = default;

    // Non-copyable, non-movable (polymorphic type)
    Rule(const Rule&) = delete;
    Rule& operator=(const Rule&) = delete;
    Rule(Rule&&) = delete;
    Rule& operator=(Rule&&) = delete;

    /// Returns the stable identifier for this rule.
    /// Must be constant for the lifetime of the rule instance.
    /// Used for explanation metadata and debugging.
    [[nodiscard]] virtual RuleId id() const noexcept = 0;

    /// Evaluates this rule against the given context.
    ///
    /// Guarantees:
    /// - Deterministic: same context produces same outcome
    /// - Pure: no side effects, no state mutation
    /// - No exceptions thrown
    ///
    /// @param context The read-only evaluation context
    /// @return The outcome of evaluating this rule
    [[nodiscard]] virtual RuleOutcome evaluate(
        const RuleContext& context) const noexcept = 0;

protected:
    /// Protected default constructor for derived classes only.
    Rule() = default;
};

} // namespace career_engine

#endif // CAREER_ENGINE_RULES_RULE_H
