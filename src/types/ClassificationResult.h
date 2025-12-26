#ifndef CAREER_ENGINE_TYPES_CLASSIFICATION_RESULT_H
#define CAREER_ENGINE_TYPES_CLASSIFICATION_RESULT_H

#include <cstdint>
#include <vector>

namespace career_engine {

// ============================================================================
// Signal Category
// ============================================================================

/// Primary classification of a career-related email signal.
/// Categories are mutually exclusive; exactly one applies per evaluation.
/// This is a deterministic output — no probabilistic interpretation.
enum class SignalCategory : std::uint8_t {
    Unknown,            // Unable to classify with sufficient confidence
    Offer,              // Job offer or offer-related communication
    Rejection,          // Application rejection or decline
    Interview,          // Interview scheduling, confirmation, or follow-up
    Assignment,         // Task assignment or project-related communication
    RecruiterOutreach,  // Recruiter-initiated contact
    Advertisement       // Job board promotion or marketing noise
};

// ============================================================================
// Confidence Score
// ============================================================================

/// Classification confidence as an explicit numeric value.
///
/// Range: [0, 100]
/// - 0: No confidence (effectively random)
/// - 50: Threshold for uncertainty
/// - 70: Minimum threshold for actionable decisions
/// - 100: Maximum confidence
///
/// This is NOT a probability. It represents rule-based certainty.
/// Values outside [0, 100] are invalid and must not be produced.
struct Confidence final {
    const std::uint8_t value;
};

// ============================================================================
// Safety Flags
// ============================================================================

/// Safety indicators that protect critical career signals from accidental loss.
/// These flags are conservative by default — false negatives are preferred
/// over false positives when protecting important emails.
struct SafetyFlags final {
    /// If false, the email should NOT be auto-deleted or archived without review.
    /// Critical signals (Offer, Interview) default to false.
    const bool safe_to_delete;

    /// If true, human review is recommended before any destructive action.
    /// Set when classification is uncertain or signal is high-value.
    const bool requires_review;
};

// ============================================================================
// Explanation Metadata
// ============================================================================

/// Identifies which rule contributed to a classification decision.
/// Machine-readable, suitable for debugging, auditing, and tests.
enum class RuleId : std::uint16_t {
    None,                       // No specific rule matched
    SubjectKeywordOffer,        // Subject contains offer-related keywords
    SubjectKeywordRejection,    // Subject contains rejection-related keywords
    SubjectKeywordInterview,    // Subject contains interview-related keywords
    SenderDomainJobBoard,       // Sender domain is a known job board
    SenderDomainRecruiter,      // Sender domain is a known recruiting firm
    BodyPatternOffer,           // Body matches offer letter patterns
    BodyPatternRejection,       // Body matches rejection letter patterns
    BodyPatternInterview,       // Body matches interview scheduling patterns
    PlatformLinkedIn,           // Source platform is LinkedIn
    PlatformNaukri,             // Source platform is Naukri
    PlatformIndeed,             // Source platform is Indeed
    NoisePatternAdvertisement,  // Matches job advertisement noise patterns
    NoisePatternMassEmail,      // Detected as mass/bulk email
    FallbackUnknown             // No rules matched; defaulted to Unknown
};

/// A single rule match that contributed to the classification.
/// Multiple rules may fire; this captures each contributing factor.
struct RuleMatch final {
    /// The rule that matched.
    const RuleId rule_id;

    /// Contribution weight of this rule to the final confidence.
    /// Range: [0, 100]. Does not imply probability.
    const std::uint8_t weight;
};

/// Structured explanation of how a classification was determined.
/// Machine-readable, deterministic, and suitable for auditing.
/// No free-form human text — all fields are typed and enumerated.
struct ExplanationMetadata final {
    /// Ordered list of rules that matched, from highest to lowest weight.
    /// Empty if no rules matched (category will be Unknown).
    const std::vector<RuleMatch> matched_rules;

    /// The primary rule that determined the classification.
    /// This is the rule with the highest weight, or None if no rules matched.
    const RuleId primary_rule;

    /// Total number of rules evaluated (for diagnostics).
    const std::uint16_t rules_evaluated;
};

// ============================================================================
// Classification Result
// ============================================================================

/// The complete, immutable result of classifying a single email signal.
///
/// This is a pure data contract:
/// - Immutable after construction
/// - Deterministic output for deterministic input
/// - No lifecycle state
/// - No user intent inference
/// - No business logic
///
/// All fields are const to enforce immutability.
struct ClassificationResult final {
    /// The determined signal category.
    const SignalCategory category;

    /// Confidence in the classification. Range: [0, 100].
    const Confidence confidence;

    /// Safety indicators for downstream decisions.
    const SafetyFlags safety;

    /// Machine-readable explanation of the classification.
    const ExplanationMetadata explanation;
};

} // namespace career_engine

#endif // CAREER_ENGINE_TYPES_CLASSIFICATION_RESULT_H
