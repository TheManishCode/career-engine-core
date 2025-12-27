#pragma once

#include <cstdint>

namespace career_engine {

    /**
     * Career Engine Core — Semantic API Versioning
     *
     * Versioning scheme:
     *   MAJOR: Breaking API changes
     *   MINOR: Backward-compatible feature additions
     *   PATCH: Bug fixes and internal improvements
     *
     * NOTE:
     * - Only MAJOR is considered for hard compatibility checks.
     * - MINOR and PATCH are informational and advisory.
     */

     // -----------------------------------------------------------------------------
     // Semantic Version Components
     // -----------------------------------------------------------------------------

    inline constexpr std::uint32_t CAREER_ENGINE_API_MAJOR = 1;
    inline constexpr std::uint32_t CAREER_ENGINE_API_MINOR = 0;
    inline constexpr std::uint32_t CAREER_ENGINE_API_PATCH = 0;

    // -----------------------------------------------------------------------------
    // Combined API Version (Monotonic, Comparable)
    // -----------------------------------------------------------------------------
    //
    // Format: (MAJOR << 16) | (MINOR << 8) | PATCH
    //
    // This allows simple integer comparison while preserving ordering.
    //
    inline constexpr std::uint32_t CAREER_ENGINE_API_VERSION =
        (CAREER_ENGINE_API_MAJOR << 16) |
        (CAREER_ENGINE_API_MINOR << 8) |
        CAREER_ENGINE_API_PATCH;

} // namespace career_engine
