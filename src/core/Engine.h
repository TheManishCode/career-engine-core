#ifndef CAREER_ENGINE_CORE_ENGINE_H
#define CAREER_ENGINE_CORE_ENGINE_H

#include <cstdint>

#include "EngineError.h"
#include "../types/ClassificationResult.h"
#include "../types/NormalizedEmail.h"

namespace career_engine {

// ============================================================================
// Result Type
// ============================================================================

/// Result type for engine operations.
/// Holds either a successful value or an error, never both.
/// Caller must check has_value() before accessing value().
template <typename T>
class Result final {
public:
    /// Constructs a successful result.
    explicit Result(T value) noexcept(std::is_nothrow_move_constructible_v<T>);

    /// Constructs an error result.
    explicit Result(EngineError error) noexcept;

    // Non-copyable, movable
    Result(const Result&) = delete;
    Result& operator=(const Result&) = delete;
    Result(Result&&) noexcept(std::is_nothrow_move_constructible_v<T>) = default;
    Result& operator=(Result&&) noexcept(std::is_nothrow_move_assignable_v<T>) = default;

    ~Result() = default;

    /// Returns true if the result contains a value.
    [[nodiscard]] bool has_value() const noexcept;

    /// Returns true if the result contains an error.
    [[nodiscard]] bool has_error() const noexcept;

    /// Returns the contained value. Precondition: has_value() == true.
    [[nodiscard]] const T& value() const noexcept;

    /// Returns the contained error. Precondition: has_error() == true.
    [[nodiscard]] const EngineError& error() const noexcept;

private:
    T value_;
    EngineError error_;
    bool has_value_;
};

// ============================================================================
// Engine Interface
// ============================================================================

/// The Career Engine core classifier.
/// Stateless, deterministic, and safe to use from any context.
/// Same input always produces same output.
class Engine final {
public:
    Engine() = default;
    ~Engine() = default;

    // Non-copyable, non-movable (stateless singleton-style usage)
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

    /// Classifies a single normalized email and returns a structured result.
    /// This is the primary entry point for the engine.
    ///
    /// Guarantees:
    /// - Deterministic: same input produces same output
    /// - No side effects
    /// - No exceptions thrown
    /// - No heap allocations beyond result construction
    ///
    /// @param email The normalized email to classify
    /// @return Result containing ClassificationResult or EngineError
    [[nodiscard]] Result<ClassificationResult> classify(
        const NormalizedEmail& email) const noexcept;
};

} // namespace career_engine

#endif // CAREER_ENGINE_CORE_ENGINE_H
