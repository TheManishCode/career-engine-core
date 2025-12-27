#include "JobPlatformNoiseRule.h"

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string_view>

#include "../../RuleContext.h"
#include "../../RuleOutcome.h"
#include "../../../types/ClassificationResult.h"
#include "../../../types/NormalizedEmail.h"

namespace career_engine {

namespace {

// ============================================================================
// Constants
// ============================================================================

constexpr std::uint8_t kAdvertisementWeight = 10;
constexpr std::int8_t kConfidenceDelta = -20;

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

// ============================================================================
// Platform Check
// ============================================================================

/// Returns true if source_platform is a known job board platform.
bool is_job_platform(const std::optional<SourcePlatform>& platform) noexcept {
    if (!platform.has_value()) {
        return false;
    }

    switch (platform.value()) {
        case SourcePlatform::LinkedIn:
        case SourcePlatform::Naukri:
        case SourcePlatform::Indeed:
        case SourcePlatform::Glassdoor:
            return true;
        default:
            return false;
    }
}

// ============================================================================
// Noise Phrase Detection
// ============================================================================

/// Returns true if text contains any noise phrase (case-insensitive).
bool contains_noise_phrase(std::string_view text) noexcept {
    if (contains_case_insensitive(text, "jobs for you")) {
        return true;
    }
    if (contains_case_insensitive(text, "recommended jobs")) {
        return true;
    }
    if (contains_case_insensitive(text, "top jobs")) {
        return true;
    }
    if (contains_case_insensitive(text, "new jobs")) {
        return true;
    }
    if (contains_case_insensitive(text, "hiring now")) {
        return true;
    }
    if (contains_case_insensitive(text, "don't miss")) {
        return true;
    }
    if (contains_case_insensitive(text, "apply now")) {
        return true;
    }
    return false;
}

// ============================================================================
// High-Value Keyword Detection (Exclusion Check)
// ============================================================================

/// Returns true if text contains any high-value keyword that should prevent
/// noise classification (case-insensitive).
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

// ============================================================================
// Outcome Construction
// ============================================================================

/// Creates a RuleOutcome for matched noise.
RuleOutcome make_match_outcome() noexcept {
    return RuleOutcome{
        .rule_id = RuleId::JobPlatformNoise,
        .match_state = MatchState::Match,
        .safety = SafetyContribution{
            .safe_to_delete = SafetyAssertion::NoOpinion,
            .requires_review = SafetyAssertion::NoOpinion
        },
        .classification = ClassificationContribution{
            .suggested_category = SignalCategory::Advertisement,
            .confidence_weight = kAdvertisementWeight
        },
        .advisory = AdvisoryContribution{
            .confidence_delta = kConfidenceDelta,
            .explanation_rule = std::nullopt
        }
    };
}

/// Creates a RuleOutcome for non-matched email.
RuleOutcome make_no_match_outcome() noexcept {
    return RuleOutcome{
        .rule_id = RuleId::JobPlatformNoise,
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
// JobPlatformNoiseRule Implementation
// ============================================================================

RuleId JobPlatformNoiseRule::id() const noexcept {
    return RuleId::JobPlatformNoise;
}

RuleOutcome JobPlatformNoiseRule::evaluate(const RuleContext& context) const noexcept {
    const NormalizedEmail& email = context.input;

    // Condition 1: Must be from a known job platform
    if (!is_job_platform(email.source_platform)) {
        return make_no_match_outcome();
    }

    const std::string_view subject = email.subject;
    const std::string_view body = email.body_plain;

    // Condition 3 (checked before 2 for early exit): Must NOT contain high-value keywords
    if (contains_high_value_keyword(subject) || contains_high_value_keyword(body)) {
        return make_no_match_outcome();
    }

    // Condition 2: Must contain at least one noise phrase
    if (!contains_noise_phrase(subject) && !contains_noise_phrase(body)) {
        return make_no_match_outcome();
    }

    // All conditions met: this is job platform noise
    return make_match_outcome();
}

} // namespace career_engine
