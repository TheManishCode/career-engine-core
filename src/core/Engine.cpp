#include "Engine.h"

#include <array>
#include <span>
#include <vector>

#include "EngineError.h"
#include "../aggregation/OutcomeAggregator.h"
#include "../rules/Rule.h"
#include "../rules/RuleEngine.h"
#include "../rules/RuleOutcome.h"
#include "../rules/impl/classification/BasicCareerSignalRule.h"
#include "../rules/impl/safety/ProtectHighValueEmailsRule.h"
#include "../types/ClassificationResult.h"
#include "../types/NormalizedEmail.h"

namespace career_engine {

// ============================================================================
// Forward declaration of aggregation function
// ============================================================================

// Defined in OutcomeAggregator.cpp
ClassificationResult aggregate_outcomes(std::span<const RuleOutcome> outcomes) noexcept;

// ============================================================================
// Built-in Rules (static lifetime)
// ============================================================================

namespace {

// Static rule instances with stable lifetime
const ProtectHighValueEmailsRule kSafetyRule;
const BasicCareerSignalRule kClassificationRule;

// Static rule pointer array for RuleEngine
constexpr std::array<const Rule*, 2> kBuiltInRules = {
    &kSafetyRule,
    &kClassificationRule
};

} // anonymous namespace

// ============================================================================
// Result<T> Implementation
// ============================================================================

template <typename T>
Result<T>::Result(T value) noexcept(std::is_nothrow_move_constructible_v<T>)
    : value_{std::move(value)}
    , error_{EngineErrorCode::None}
    , has_value_{true}
{}

template <typename T>
Result<T>::Result(EngineError error) noexcept
    : value_{}
    , error_{error}
    , has_value_{false}
{}

template <typename T>
bool Result<T>::has_value() const noexcept {
    return has_value_;
}

template <typename T>
bool Result<T>::has_error() const noexcept {
    return !has_value_;
}

template <typename T>
const T& Result<T>::value() const noexcept {
    return value_;
}

template <typename T>
const EngineError& Result<T>::error() const noexcept {
    return error_;
}

// Explicit instantiation for ClassificationResult
template class Result<ClassificationResult>;

// ============================================================================
// Engine Implementation
// ============================================================================

Result<ClassificationResult> Engine::classify(
    const NormalizedEmail& email) const noexcept
{
    // -------------------------------------------------------------------------
    // Step 1: Validate input preconditions
    // -------------------------------------------------------------------------

    // Check for empty sender (required field)
    if (email.sender.empty()) {
        return Result<ClassificationResult>{EngineError{EngineErrorCode::EmptySender}};
    }

    // Check for empty id (required field)
    if (email.id.empty()) {
        return Result<ClassificationResult>{EngineError{EngineErrorCode::EmptyId}};
    }

    // Check for invalid timestamp (negative is invalid per NormalizedEmail contract)
    if (email.timestamp_utc < 0) {
        return Result<ClassificationResult>{EngineError{EngineErrorCode::MalformedTimestamp}};
    }

    // -------------------------------------------------------------------------
    // Step 2: Invoke RuleEngine with built-in rules
    // -------------------------------------------------------------------------

    RuleEngine rule_engine;

    std::vector<RuleOutcome> outcomes = rule_engine.evaluate(
        email,
        std::span<const Rule* const>{kBuiltInRules}
    );

    // -------------------------------------------------------------------------
    // Step 3: Handle empty outcomes (conservative Unknown result)
    // -------------------------------------------------------------------------

    if (outcomes.empty()) {
        // Return conservative result: Unknown, no confidence, not safe to delete, requires review
        return Result<ClassificationResult>{ClassificationResult{
            .category = SignalCategory::Unknown,
            .confidence = Confidence{.value = 0},
            .safety = SafetyFlags{
                .safe_to_delete = false,
                .requires_review = true
            },
            .explanation = ExplanationMetadata{
                .matched_rules = {},
                .primary_rule = RuleId::None,
                .rules_evaluated = 0
            }
        }};
    }

    // -------------------------------------------------------------------------
    // Step 4: Delegate aggregation to OutcomeAggregator
    // -------------------------------------------------------------------------

    ClassificationResult result = aggregate_outcomes(
        std::span<const RuleOutcome>{outcomes}
    );

    return Result<ClassificationResult>{std::move(result)};
}

} // namespace career_engine
