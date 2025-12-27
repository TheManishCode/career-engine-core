#ifndef CAREER_ENGINE_RULES_IMPL_SAFETY_PROTECT_HIGH_VALUE_EMAILS_RULE_H
#define CAREER_ENGINE_RULES_IMPL_SAFETY_PROTECT_HIGH_VALUE_EMAILS_RULE_H

#include "../../../Rule.h"

namespace career_engine {

/// Safety rule that protects high-value career emails from accidental deletion.
///
/// Behavior:
/// - Matches if email subject OR body contains (case-insensitive ASCII):
///   "offer", "interview", or "assignment"
/// - When matched: asserts AssertUnsafe for both safe_to_delete and requires_review
/// - When not matched: returns NoMatch with NoOpinion
///
/// Design:
/// - Deterministic: same input always produces same output
/// - Stateless: no internal state
/// - Pure: no side effects, no I/O, no logging
/// - Simple ASCII case-insensitive matching (no regex)
class ProtectHighValueEmailsRule final : public Rule {
public:
    ProtectHighValueEmailsRule() = default;
    ~ProtectHighValueEmailsRule() override = default;

    /// Returns RuleId::SafetyHighValueEmail.
    [[nodiscard]] RuleId id() const noexcept override;

    /// Evaluates the email for high-value career signals.
    /// Returns Match with safety assertions if keywords found, NoMatch otherwise.
    [[nodiscard]] RuleOutcome evaluate(const RuleContext& context) const noexcept override;
};

} // namespace career_engine

#endif // CAREER_ENGINE_RULES_IMPL_SAFETY_PROTECT_HIGH_VALUE_EMAILS_RULE_H
