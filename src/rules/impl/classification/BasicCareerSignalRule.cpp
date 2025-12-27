#include "BasicCareerSignalRule.h"

#include <cstddef>
#include <cstdint>
#include <string_view>

#include "../../RuleContext.h"
#include "../../RuleOutcome.h"
#include "../../../types/ClassificationResult.h"
#include "../../../types/NormalizedEmail.h"

namespace career_engine {

namespace {

// ============================================================================
// Keyword Weights (deterministic priority order)
// ============================================================================

constexpr std::uint8_t kOfferWeight = 60;
constexpr std::uint8_t kInterviewWeight = 50;
constexpr std::uint8_t kAssignmentWeight = 40;

// ============================================================================
// Case-Insensitive ASCII Substring Search
// ============================================================================

/// Converts ASCII character to lowercase.
/// Non-ASCII characters are returned unchanged.
constexpr char to_lower_ascii(char c) noexcept {
    if (c >= 'A' && c <= 'Z') {
        return static_cast<char>(c + ('a' - 'A'));
    }
    return c;
}

/// Performs case-insensitive ASCII substring search.
/// Returns true if needle is found within haystack.
bool contains_case_insensitive(std::string_view haystack, std::string_view needle) noexcept {
    if (needle.empty()) {
        return true;
    }
    if (haystack.size() < needle.size()) {
        return false;
    }

    const std::size_t limit = haystack.size() - needle.size() + 1;

    for (std::size_t i = 0; i < limit; ++i) {
        bool match = true;
        for (std::size_t j = 0; j < needle.size(); ++j) {
            if (to_lower_ascii(haystack[i + j]) != to_lower_ascii(needle[j])) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }

    return false;
}

/// Checks if text contains the specified keyword (case-insensitive).
bool text_contains_keyword(std::string_view subject, std::string_view body, std::string_view keyword) noexcept {
    return contains_case_insensitive(subject, keyword) || contains_case_insensitive(body, keyword);
}

// ============================================================================
// Outcome Construction
// ============================================================================

/// Creates a RuleOutcome for a matched classification.
RuleOutcome make_match_outcome(SignalCategory category, std::uint8_t weight) noexcept {
    return RuleOutcome{
        .rule_id = RuleId::BasicCareerSignal,
        .match_state = MatchState::Match,
        .safety = SafetyContribution{
            .safe_to_delete = SafetyAssertion::NoOpinion,
            .requires_review = SafetyAssertion::NoOpinion
        },
        .classification = ClassificationContribution{
            .suggested_category = category,
            .confidence_weight = weight
        },
        .advisory = AdvisoryContribution{
            .confidence_delta = std::nullopt,
            .explanation_rule = std::nullopt
        }
    };
}

/// Creates a RuleOutcome for a non-matched email.
RuleOutcome make_no_match_outcome() noexcept {
    return RuleOutcome{
        .rule_id = RuleId::BasicCareerSignal,
        .match_state = MatchState::NoMatch,
        .safety = SafetyContribution{
            .safe_to_delete = SafetyAssertion::NoOpinion,
            .requires_review = SafetyAssertion::NoOpinion
        },
        .classification = ClassificationContribution{
            .suggested_category = std::nullopt,
            .confidence_weight = 0
        },
        .advisory = AdvisoryContribution{
            .confidence_delta = std::nullopt,
            .explanation_rule = std::nullopt
        }
    };
}

} // anonymous namespace

// ============================================================================
// BasicCareerSignalRule Implementation
// ============================================================================

RuleId BasicCareerSignalRule::id() const noexcept {
    return RuleId::BasicCareerSignal;
}

RuleOutcome BasicCareerSignalRule::evaluate(const RuleContext& context) const noexcept {
    const NormalizedEmail& email = context.input;
    const std::string_view subject = email.subject;
    const std::string_view body = email.body_plain;

    // Check keywords in priority order (strongest first)
    // Return immediately on first match to ensure only one category per outcome

    // Priority 1: "offer" (weight 60)
    if (text_contains_keyword(subject, body, "offer")) {
        return make_match_outcome(SignalCategory::Offer, kOfferWeight);
    }

    // Priority 2: "interview" (weight 50)
    if (text_contains_keyword(subject, body, "interview")) {
        return make_match_outcome(SignalCategory::Interview, kInterviewWeight);
    }

    // Priority 3: "assignment" (weight 40)
    if (text_contains_keyword(subject, body, "assignment")) {
        return make_match_outcome(SignalCategory::Assignment, kAssignmentWeight);
    }

    // No keywords matched
    return make_no_match_outcome();
}

} // namespace career_engine
