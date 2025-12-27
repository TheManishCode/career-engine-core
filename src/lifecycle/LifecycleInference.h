#pragma once

/*
===============================================================================
LifecycleInference.h — Career Lifecycle Reasoning Boundary
===============================================================================

PURPOSE
-------
This header defines the boundary for inferring higher-level career lifecycle
signals from aggregated classification results.

Lifecycle inference answers questions such as:
- Is this email part of an active hiring process?
- Does this represent progression, stagnation, or closure?
- Should this signal influence long-term career state?

This header defines WHERE lifecycle reasoning belongs,
but NOT HOW lifecycle decisions are computed.

RESPONSIBILITIES
----------------
LifecycleInference is allowed to:
- Consume a fully aggregated ClassificationResult
- Infer lifecycle-level signals or annotations
- Remain deterministic and stateless
- Be invoked by EngineInternal after aggregation

LifecycleInference is NOT allowed to:
- Evaluate rules
- Aggregate RuleOutcome objects
- Influence safety decisions
- Modify ClassificationResult
- Access NormalizedEmail directly
- Access storage, UI, networking, or OS resources
- Perform non-deterministic behavior

BOUNDARY RULES
--------------
- Lifecycle inference MUST occur after aggregation
- Rules MUST NOT perform lifecycle reasoning
- OutcomeAggregator MUST NOT perform lifecycle reasoning
- EngineInternal may invoke lifecycle inference optionally

DEPENDENCY DIRECTION
--------------------
LifecycleInference may depend on:
- types/ClassificationResult.h

LifecycleInference MUST NOT depend on:
- rules/
- aggregation/
- security/
- core/Engine.h
- utils/

IMPLEMENTATION NOTE
-------------------
This file intentionally contains no implementation.

Lifecycle inference logic, if implemented, must be explicit,
auditable, and fully deterministic.

===============================================================================
*/

#ifndef CAREER_ENGINE_LIFECYCLE_LIFECYCLE_INFERENCE_H
#define CAREER_ENGINE_LIFECYCLE_LIFECYCLE_INFERENCE_H

#include <cstdint>
#include <span>

#include "../types/ClassificationResult.h"

namespace career_engine {

// ============================================================================
// Lifecycle State (Level-1 Core Engine)
// ============================================================================

/// Represents the inferred state of a career event lifecycle.
/// Constrained to Level-1 semantics: derived directly from SignalCategory.
enum class LifecycleState : std::uint8_t {
    /// No lifecycle information available or not applicable.
    Unknown,

    /// Application or assignment-related signal received.
    Applied,

    /// Interview signal received, actively engaged in process.
    Interviewing,

    /// Offer signal received.
    Offer,

    /// Process concluded (rejection or no further signals expected).
    Closed
};

// ============================================================================
// Lifecycle Policy
// ============================================================================

/// Controls how lifecycle inference handles the Closed state.
enum class LifecyclePolicy : std::uint8_t {
    /// Once Closed is reached, ignore remaining events.
    /// Use when events are strictly sequential and closure is final.
    ClosedIsTerminal,

    /// Allow transitions from Closed back to other states.
    /// Use when processes can reopen (e.g., new role at same company).
    ClosedCanReopen
};

// ============================================================================
// Lifecycle Event
// ============================================================================

/// A single lifecycle event derived from a classified email signal.
/// Contains only SignalCategory and timestamp — no separate event type.
struct LifecycleEvent final {
    /// The classified signal category from the email.
    const SignalCategory signal;

    /// UTC timestamp of the email (seconds since epoch).
    const std::int64_t timestamp_utc;
};

// ============================================================================
// State Transition Logic
// ============================================================================

namespace detail {

/// Determines if Closed state should stop processing.
[[nodiscard]] constexpr bool is_closed(LifecycleState state) noexcept {
    return state == LifecycleState::Closed;
}

/// Applies a single signal to the current state.
/// Transitions are derived directly from SignalCategory.
/// Returns the new state after the transition.
[[nodiscard]] constexpr LifecycleState apply_transition(
    LifecycleState current,
    SignalCategory signal) noexcept
{
    switch (current) {
        case LifecycleState::Unknown:
            switch (signal) {
                case SignalCategory::Unknown:
                    return LifecycleState::Unknown;
                case SignalCategory::Offer:
                    return LifecycleState::Offer;
                case SignalCategory::Rejection:
                    return LifecycleState::Closed;
                case SignalCategory::Interview:
                    return LifecycleState::Interviewing;
                case SignalCategory::Assignment:
                    return LifecycleState::Applied;
                case SignalCategory::RecruiterOutreach:
                    return LifecycleState::Applied;
                case SignalCategory::Advertisement:
                    return LifecycleState::Unknown;
            }
            break;

        case LifecycleState::Applied:
            switch (signal) {
                case SignalCategory::Unknown:
                    return LifecycleState::Applied;
                case SignalCategory::Offer:
                    return LifecycleState::Offer;
                case SignalCategory::Rejection:
                    return LifecycleState::Closed;
                case SignalCategory::Interview:
                    return LifecycleState::Interviewing;
                case SignalCategory::Assignment:
                    return LifecycleState::Applied;
                case SignalCategory::RecruiterOutreach:
                    return LifecycleState::Applied;
                case SignalCategory::Advertisement:
                    return LifecycleState::Applied;
            }
            break;

        case LifecycleState::Interviewing:
            switch (signal) {
                case SignalCategory::Unknown:
                    return LifecycleState::Interviewing;
                case SignalCategory::Offer:
                    return LifecycleState::Offer;
                case SignalCategory::Rejection:
                    return LifecycleState::Closed;
                case SignalCategory::Interview:
                    return LifecycleState::Interviewing;
                case SignalCategory::Assignment:
                    return LifecycleState::Interviewing;
                case SignalCategory::RecruiterOutreach:
                    return LifecycleState::Interviewing;
                case SignalCategory::Advertisement:
                    return LifecycleState::Interviewing;
            }
            break;

        case LifecycleState::Offer:
            switch (signal) {
                case SignalCategory::Unknown:
                    return LifecycleState::Offer;
                case SignalCategory::Offer:
                    return LifecycleState::Offer;
                case SignalCategory::Rejection:
                    return LifecycleState::Closed;
                case SignalCategory::Interview:
                    return LifecycleState::Offer;
                case SignalCategory::Assignment:
                    return LifecycleState::Offer;
                case SignalCategory::RecruiterOutreach:
                    return LifecycleState::Offer;
                case SignalCategory::Advertisement:
                    return LifecycleState::Offer;
            }
            break;

        case LifecycleState::Closed:
            switch (signal) {
                case SignalCategory::Unknown:
                    return LifecycleState::Closed;
                case SignalCategory::Offer:
                    return LifecycleState::Offer;
                case SignalCategory::Rejection:
                    return LifecycleState::Closed;
                case SignalCategory::Interview:
                    return LifecycleState::Interviewing;
                case SignalCategory::Assignment:
                    return LifecycleState::Applied;
                case SignalCategory::RecruiterOutreach:
                    return LifecycleState::Applied;
                case SignalCategory::Advertisement:
                    return LifecycleState::Closed;
            }
            break;
    }

    return current; // Unreachable, but satisfies compiler
}

} // namespace detail

// ============================================================================
// Lifecycle Inference Function
// ============================================================================

/// Infers the final lifecycle state from a sequence of classified events.
///
/// Behavior:
/// - Starts from LifecycleState::Unknown
/// - Events are processed in provided order (no sorting performed)
/// - Transitions are derived directly from SignalCategory
/// - Policy controls handling of Closed state
///
/// Guarantees:
/// - Deterministic: same events and policy produce same result
/// - No side effects
/// - No dynamic allocation
/// - No exceptions
///
/// @param events Span of lifecycle events (processed in order)
/// @param policy Controls whether Closed state stops processing
/// @return The final inferred lifecycle state
[[nodiscard]] constexpr LifecycleState infer(
    std::span<const LifecycleEvent> events,
    LifecyclePolicy policy) noexcept
{
    LifecycleState state = LifecycleState::Unknown;

    for (const LifecycleEvent& event : events) {
        // Check if we should stop processing
        if (policy == LifecyclePolicy::ClosedIsTerminal) {
            if (detail::is_closed(state)) {
                break;
            }
        }

        // Apply transition based on signal category
        state = detail::apply_transition(state, event.signal);
    }

    return state;
}

} // namespace career_engine

#endif // CAREER_ENGINE_LIFECYCLE_LIFECYCLE_INFERENCE_H
