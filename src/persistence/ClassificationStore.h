#pragma once

#include <optional>
#include <string>

#include "../types/ClassificationResult.h"

namespace persistence {

    /**
     * Contract for persisting classification results produced by the engine.
     */
    struct ClassificationStore {
        virtual ~ClassificationStore() = default;

        // Save classification result for an email
        virtual void save(
            const std::string& email_id,
            const career_engine::ClassificationResult& result
        ) = 0;

        // Load classification result for an email
        virtual std::optional<career_engine::ClassificationResult>
            load(const std::string& email_id) const = 0;
    };

} // namespace persistence
