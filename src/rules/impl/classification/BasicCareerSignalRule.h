#ifndef CAREER_ENGINE_RULES_IMPL_CLASSIFICATION_BASIC_CAREER_SIGNAL_RULE_H
#define CAREER_ENGINE_RULES_IMPL_CLASSIFICATION_BASIC_CAREER_SIGNAL_RULE_H

#include "../../../Rule.h"

namespace career_engine {

/// Classification rule that detects basic career signals from email content.
///
/// Behavior:
/// - Matches if email subject OR body contains (case-insensitive ASCII):
///   * "offer" ? SignalCategory::Offer (weight 60)
///   * "interview" ? SignalCategory::Interview (weight 50)
///   * "assignment" ? SignalCategory::Assignment (weight 40)
/// - If multiple keywords match, selects ONLY the strongest one
/// - When not matched: returns NoMatch with no contribution
///
/// Design:
/// - Deterministic: same input always produces same output
/// - Stateless: no internal state
/// - Pure: no side effects, no I/O, no logging
/// - Simple ASCII case-insensitive matching (no regex)
/// - One category per outcome, never multiple
class BasicCareerSignalRule final : public Rule {
public:
    BasicCareerSignalRule() = default;
    ~BasicCareerSignalRule() override = default;

    /// Returns RuleId::BasicCareerSignal.
    [[nodiscard]] RuleId id() const noexcept override;

    /// Evaluates the email for basic career signals.
    /// Returns Match with classification contribution if keywords found, NoMatch otherwise.
    [[nodiscard]] RuleOutcome evaluate(const RuleContext& context) const noexcept override;
};

} // namespace career_engine

#endif // CAREER_ENGINE_RULES_IMPL_CLASSIFICATION_BASIC_CAREER_SIGNAL_RULE_H
