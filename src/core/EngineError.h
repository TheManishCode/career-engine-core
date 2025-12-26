#ifndef CAREER_ENGINE_CORE_ENGINE_ERROR_H
#define CAREER_ENGINE_CORE_ENGINE_ERROR_H

#include <cstdint>

namespace career_engine {

// ============================================================================
// Error Codes
// ============================================================================

/// Canonical error codes for the Career Engine public interface.
///
/// Design principles:
/// - Machine-readable and stable across versions
/// - No error strings required for correctness
/// - Explicit categorization of failure modes
/// - Suitable for use in Result<T, EngineError>
///
/// Error categories:
/// - None: Success (no error)
/// - Invalid input: Caller provided malformed or incomplete data
/// - Unsupported input: Input is well-formed but not processable
/// - Internal invariant violation: Engine internal consistency failure
/// - Engine misuse: Caller violated API contract
enum class EngineErrorCode : std::uint8_t {
    // -------------------------------------------------------------------------
    // Success
    // -------------------------------------------------------------------------

    /// No error occurred.
    None = 0,

    // -------------------------------------------------------------------------
    // Invalid Input (1-49)
    // Caller provided malformed or incomplete data.
    // -------------------------------------------------------------------------

    /// Input data failed basic validation.
    InvalidInput = 1,

    /// Sender field is empty or missing.
    EmptySender = 2,

    /// Email identifier is empty or missing.
    EmptyId = 3,

    /// Timestamp is malformed or out of valid range.
    MalformedTimestamp = 4,

    // -------------------------------------------------------------------------
    // Unsupported Input (50-99)
    // Input is well-formed but cannot be processed.
    // -------------------------------------------------------------------------

    /// Input contains data the engine cannot interpret.
    UnsupportedInput = 50,

    /// Source platform is not recognized.
    UnsupportedPlatform = 51,

    /// Input encoding is not supported.
    UnsupportedEncoding = 52,

    // -------------------------------------------------------------------------
    // Internal Invariant Violation (100-149)
    // Engine internal consistency failure. Should never occur.
    // -------------------------------------------------------------------------

    /// An internal invariant was violated.
    /// This indicates a bug in the engine, not caller error.
    InternalInvariantViolation = 100,

    /// Internal rule evaluation failed unexpectedly.
    RuleEvaluationFailure = 101,

    // -------------------------------------------------------------------------
    // Engine Misuse (150-199)
    // Caller violated API contract.
    // -------------------------------------------------------------------------

    /// Caller violated a documented precondition.
    PreconditionViolation = 150,

    /// Engine was used in an invalid state.
    InvalidState = 151
};

// ============================================================================
// Error Struct
// ============================================================================

/// Lightweight, immutable error representation for the engine interface.
///
/// Design:
/// - Contains only an error code (no strings, no diagnostics)
/// - Machine-readable and deterministic
/// - Suitable for Result<T, EngineError> pattern
/// - No recovery logic or exception semantics
///
/// Usage:
/// - Check code against EngineErrorCode::None to determine success
/// - Error codes are stable and safe to serialize or compare
struct EngineError final {
    const EngineErrorCode code;
};

// ============================================================================
// Error Category Queries
// ============================================================================

/// Returns true if the error code represents an invalid input error.
[[nodiscard]] constexpr bool is_invalid_input(EngineErrorCode code) noexcept {
    const auto v = static_cast<std::uint8_t>(code);
    return v >= 1 && v <= 49;
}

/// Returns true if the error code represents an unsupported input error.
[[nodiscard]] constexpr bool is_unsupported_input(EngineErrorCode code) noexcept {
    const auto v = static_cast<std::uint8_t>(code);
    return v >= 50 && v <= 99;
}

/// Returns true if the error code represents an internal invariant violation.
[[nodiscard]] constexpr bool is_internal_error(EngineErrorCode code) noexcept {
    const auto v = static_cast<std::uint8_t>(code);
    return v >= 100 && v <= 149;
}

/// Returns true if the error code represents engine misuse by the caller.
[[nodiscard]] constexpr bool is_misuse_error(EngineErrorCode code) noexcept {
    const auto v = static_cast<std::uint8_t>(code);
    return v >= 150 && v <= 199;
}

} // namespace career_engine

#endif // CAREER_ENGINE_CORE_ENGINE_ERROR_H
