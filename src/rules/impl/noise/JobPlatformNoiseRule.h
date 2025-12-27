#ifndef CAREER_ENGINE_RULES_IMPL_NOISE_JOB_PLATFORM_NOISE_RULE_H
#define CAREER_ENGINE_RULES_IMPL_NOISE_JOB_PLATFORM_NOISE_RULE_H

#include "../../Rule.h"

namespace career_engine {

/// Noise suppression rule for job platform promotional emails.
///
/// Behavior:
/// - Matches ONLY IF all conditions are met:
///   1) source_platform is LinkedIn, Naukri, Indeed, or Glassdoor
///   2) subject OR body contains noise phrases (case-insensitive):
///      "jobs for you", "recommended jobs", "top jobs", "new jobs",
///      "hiring now", "don't miss", "apply now"
///   3) subject/body does NOT contain high-value keywords:
///      "offer", "interview", "assignment"
///
/// - When matched:
///   * SignalCategory::Advertisement with weight 10
///   * confidence_delta = -20
///   * No safety assertions
///
/// - When not matched: NoMatch with no contribution
///
/// Design:
/// - Deterministic: same input always produces same output
/// - Stateless: no internal state
/// - Pure: no side effects, no I/O, no logging
/// - Simple ASCII case-insensitive matching (no regex)
class JobPlatformNoiseRule final : public Rule {
public:
    JobPlatformNoiseRule() = default;
    ~JobPlatformNoiseRule() override = default;

    /// Returns RuleId::JobPlatformNoise.
    [[nodiscard]] RuleId id() const noexcept override;

    /// Evaluates the email for job platform noise patterns.
    /// Returns Match with classification/advisory if noise detected, NoMatch otherwise.
    [[nodiscard]] RuleOutcome evaluate(const RuleContext& context) const noexcept override;
};

} // namespace career_engine

#endif // CAREER_ENGINE_RULES_IMPL_NOISE_JOB_PLATFORM_NOISE_RULE_H
