#ifndef CAREER_ENGINE_TYPES_NORMALIZED_EMAIL_H
#define CAREER_ENGINE_TYPES_NORMALIZED_EMAIL_H

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace career_engine {

// ============================================================================
// Source Platform
// ============================================================================

/// Known email source platforms for career-related signals.
/// This enum does NOT include an "Unknown" value; use std::optional to
/// represent absence or unknown platform.
enum class SourcePlatform : std::uint8_t {
    LinkedIn,
    Naukri,
    Indeed,
    Glassdoor,
    Gmail,
    Outlook,
    Yahoo
};

// ============================================================================
// Normalized Email
// ============================================================================

/// Immutable, normalized representation of a single email for classification.
///
/// This is a pure data contract:
/// - All fields are pre-extracted and sanitized by the caller
/// - The engine does not parse raw email formats
/// - No validation or normalization logic is performed by this type
/// - All textual data is owned by this struct
///
/// Ownership:
/// - This struct owns all its data (std::string members)
/// - Safe to store, pass across boundaries, or inspect after classification
/// - No lifetime coupling with external data
///
/// Immutability:
/// - All members are const after construction
/// - No mutators or setters
struct NormalizedEmail final {
    /// Stable, unique identifier for this email.
    /// Format is caller-defined (e.g., message-id, internal ID).
    /// Must be non-empty and consistent across invocations.
    const std::string id;

    /// Normalized sender email address.
    /// Expected format: lowercase, trimmed, domain-normalized.
    const std::string sender;

    /// Normalized email subject line.
    /// May be empty for subjectless emails.
    const std::string subject;

    /// Plain text body content, normalized and possibly truncated.
    /// HTML tags and formatting should be stripped by the caller.
    /// May be empty.
    const std::string body_plain;

    /// Normalized recipient email addresses.
    /// Includes To, CC, BCC if available.
    /// May be empty.
    const std::vector<std::string> recipients;

    /// UTC timestamp when the email was sent or received.
    /// Represented as seconds since Unix epoch (1970-01-01T00:00:00Z).
    /// Negative values are invalid and should not be passed.
    const std::int64_t timestamp_utc;

    /// Source platform from which this email originated, if known.
    /// std::nullopt indicates the platform is unknown or not provided.
    const std::optional<SourcePlatform> source_platform;
};

} // namespace career_engine

#endif // CAREER_ENGINE_TYPES_NORMALIZED_EMAIL_H
