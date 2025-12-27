#include "OutcomeAggregator.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <span>
#include <vector>

#include "../rules/RuleOutcome.h"
#include "../types/ClassificationResult.h"

namespace career_engine {

// ============================================================================
// Deterministic Tie-Break Order
// ============================================================================

// Category priority for deterministic tie-breaking (lower index = higher priority)
// Order: Offer > Interview > Assignment > RecruiterOutreach > Rejection > Advertisement > Unknown
constexpr std::array<SignalCategory, 7> kCategoryPriority = {
    SignalCategory::Offer,
    SignalCategory::Interview,
    SignalCategory::Assignment,
    SignalCategory::RecruiterOutreach,
    SignalCategory::Rejection,
    SignalCategory::Advertisement,
    SignalCategory::Unknown
};

// ============================================================================
// Aggregation Implementation
// ============================================================================

ClassificationResult aggregate_outcomes(std::span<const RuleOutcome> outcomes) noexcept {
    // -------------------------------------------------------------------------
    // Phase 1: Count total rules evaluated
    // -------------------------------------------------------------------------
    const std::uint16_t rules_evaluated = static_cast<std::uint16_t>(outcomes.size());

    // -------------------------------------------------------------------------
    // Phase 2: Aggregate safety assertions (monotonic)
    // -------------------------------------------------------------------------
    bool any_unsafe_delete = false;
    bool any_unsafe_review = false;
    bool any_safe_delete = false;
    bool any_safe_review = false;

    for (const auto& outcome : outcomes) {
        // safe_to_delete assertions
        if (outcome.safety.safe_to_delete == SafetyAssertion::AssertUnsafe) {
            any_unsafe_delete = true;
        } else if (outcome.safety.safe_to_delete == SafetyAssertion::AssertSafe) {
            any_safe_delete = true;
        }

        // requires_review assertions
        if (outcome.safety.requires_review == SafetyAssertion::AssertUnsafe) {
            any_unsafe_review = true;
        } else if (outcome.safety.requires_review == SafetyAssertion::AssertSafe) {
            any_safe_review = true;
        }
    }

    // Apply monotonicity: AssertUnsafe always wins
    // safe_to_delete: false if any unsafe, true only if safe and no unsafe, else false (default safe)
    // requires_review: true if any unsafe, false only if safe and no unsafe, else false (default)
    const bool final_safe_to_delete = any_unsafe_delete ? false : (any_safe_delete ? true : true);
    const bool final_requires_review = any_unsafe_delete || any_unsafe_review ? true : false;

    // -------------------------------------------------------------------------
    // Phase 3: Aggregate classification weights per category
    // -------------------------------------------------------------------------
    std::array<std::uint32_t, 7> category_weights = {0, 0, 0, 0, 0, 0, 0};

    // Map SignalCategory enum to array index
    // SignalCategory values: Unknown=0, Offer=1, Rejection=2, Interview=3,
    //                        Assignment=4, RecruiterOutreach=5, Advertisement=6
    auto category_to_index = [](SignalCategory cat) -> std::size_t {
        return static_cast<std::size_t>(cat);
    };

    // Collect weights from matched rules only
    for (const auto& outcome : outcomes) {
        if (outcome.match_state != MatchState::Match) {
            continue;
        }

        if (outcome.classification.suggested_category.has_value()) {
            const SignalCategory cat = outcome.classification.suggested_category.value();
            const std::size_t idx = category_to_index(cat);
            category_weights[idx] += outcome.classification.confidence_weight;
        }
    }

    // -------------------------------------------------------------------------
    // Phase 4: Determine winning category with deterministic tie-breaking
    // -------------------------------------------------------------------------
    SignalCategory winning_category = SignalCategory::Unknown;
    std::uint32_t winning_weight = 0;

    // Iterate in priority order for deterministic tie-breaking
    for (const SignalCategory cat : kCategoryPriority) {
        const std::size_t idx = category_to_index(cat);
        const std::uint32_t weight = category_weights[idx];

        if (weight > winning_weight) {
            winning_weight = weight;
            winning_category = cat;
        }
        // If weight == winning_weight, earlier category in priority order wins (already set)
    }

    // -------------------------------------------------------------------------
    // Phase 5: Collect matched rules contributing to winning category
    // -------------------------------------------------------------------------
    struct RuleContribution {
        RuleId rule_id;
        std::uint8_t weight;
    };

    std::vector<RuleContribution> contributing_rules;

    for (const auto& outcome : outcomes) {
        if (outcome.match_state != MatchState::Match) {
            continue;
        }

        if (outcome.classification.suggested_category.has_value()) {
            if (outcome.classification.suggested_category.value() == winning_category) {
                contributing_rules.push_back({
                    outcome.rule_id,
                    outcome.classification.confidence_weight
                });
            }
        }
    }

    // Sort by descending weight, then by RuleId ordinal for deterministic tie-breaking
    std::sort(contributing_rules.begin(), contributing_rules.end(),
        [](const RuleContribution& a, const RuleContribution& b) {
            if (a.weight != b.weight) {
                return a.weight > b.weight; // Descending weight
            }
            // Tie-break by RuleId ordinal (lower ordinal = higher priority)
            return static_cast<std::uint16_t>(a.rule_id) < static_cast<std::uint16_t>(b.rule_id);
        });

    // -------------------------------------------------------------------------
    // Phase 6: Build matched_rules vector and determine primary_rule
    // -------------------------------------------------------------------------
    std::vector<RuleMatch> matched_rules;
    matched_rules.reserve(contributing_rules.size());

    for (const auto& contrib : contributing_rules) {
        matched_rules.push_back(RuleMatch{
            .rule_id = contrib.rule_id,
            .weight = contrib.weight
        });
    }

    // Primary rule is the first in sorted order (highest weight, lowest ordinal on tie)
    const RuleId primary_rule = contributing_rules.empty()
        ? RuleId::None
        : contributing_rules[0].rule_id;

    // -------------------------------------------------------------------------
    // Phase 7: Aggregate confidence
    // -------------------------------------------------------------------------
    std::int32_t confidence_accumulator = 0;

    // Add classification confidence weights from matched rules
    for (const auto& outcome : outcomes) {
        if (outcome.match_state != MatchState::Match) {
            continue;
        }

        if (outcome.classification.suggested_category.has_value()) {
            if (outcome.classification.suggested_category.value() == winning_category) {
                confidence_accumulator += outcome.classification.confidence_weight;
            }
        }
    }

    // Apply advisory confidence deltas
    for (const auto& outcome : outcomes) {
        if (outcome.advisory.confidence_delta.has_value()) {
            confidence_accumulator += outcome.advisory.confidence_delta.value();
        }
    }

    // Clamp to [0, 100]
    if (confidence_accumulator < 0) {
        confidence_accumulator = 0;
    } else if (confidence_accumulator > 100) {
        confidence_accumulator = 100;
    }

    const std::uint8_t final_confidence = static_cast<std::uint8_t>(confidence_accumulator);

    // -------------------------------------------------------------------------
    // Phase 8: Construct final ClassificationResult
    // -------------------------------------------------------------------------
    return ClassificationResult{
        .category = winning_category,
        .confidence = Confidence{.value = final_confidence},
        .safety = SafetyFlags{
            .safe_to_delete = final_safe_to_delete,
            .requires_review = final_requires_review
        },
        .explanation = ExplanationMetadata{
            .matched_rules = std::move(matched_rules),
            .primary_rule = primary_rule,
            .rules_evaluated = rules_evaluated
        }
    };
}

} // namespace career_engine
