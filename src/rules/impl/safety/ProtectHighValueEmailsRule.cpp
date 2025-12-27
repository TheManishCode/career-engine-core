#include "ProtectHighValueEmailsRule.h"

#include <cctype>
#include <cstddef>
#include <string_view>

#include "../../../RuleContext.h"
#include "../../../RuleOutcome.h"
#include "../../../../types/ClassificationResult.h"
#include "../../../../types/NormalizedEmail.h"

namespace career_engine {

namespace {

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
/// Both strings are compared as lowercase ASCII.
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

/// Checks if text contains any high-value career keyword.
/// Keywords: "offer", "interview", "assignment"
bool contains_high_value_keyword(std::string_view text) noexcept {
    if (contains_case_insensitive(text, "offer")) {
        return true;
    }
    if (contains_case_insensitive(text, "interview")) {
        return true;
    }
    if (contains_case_insensitive(text, "assignment")) {
        return true;
    }
    return false;
}

/// Creates a RuleOutcome for a matched high-value email.
RuleOutcome make_match_outcome() noexcept {
    return RuleOutcome{
        .rule_id = RuleId::SafetyHighValueEmail,
        .match_state = MatchState::Match,
        .safety = SafetyContribution{
            .safe_to_delete = SafetyAssertion::AssertUnsafe,
            .requires_review = SafetyAssertion::AssertUnsafe
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

/// Creates a RuleOutcome for a non-matched email.
RuleOutcome make_no_match_outcome() noexcept {
    return RuleOutcome{
        .rule_id = RuleId::SafetyHighValueEmail,
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
// ProtectHighValueEmailsRule Implementation
// ============================================================================

RuleId ProtectHighValueEmailsRule::id() const noexcept {
    return RuleId::SafetyHighValueEmail;
}

RuleOutcome ProtectHighValueEmailsRule::evaluate(const RuleContext& context) const noexcept {
    const NormalizedEmail& email = context.input;

    // Check subject for high-value keywords
    if (contains_high_value_keyword(email.subject)) {
        return make_match_outcome();
    }

    // Check body for high-value keywords
    if (contains_high_value_keyword(email.body_plain)) {
        return make_match_outcome();
    }

    // No high-value keywords found
    return make_no_match_outcome();
}

} // namespace career_engine
