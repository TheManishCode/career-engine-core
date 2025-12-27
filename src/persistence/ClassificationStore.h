#pragma once

#include <optional>
#include <string>

#include "../types/ClassificationResult.h"

namespace persistence {

    /**
     * Contract for persisting classification results produced by the engine.
     *
     * Implementations may store data in files, databases, memory, or elsewhere.
     * The core engine MUST NOT depend on any concrete storage mechanism.
     */
    struct ClassificationStore {
        virtual ~ClassificationStore() = default;

        // Save the classification result for a given email ID
        virtual void save(
            const std::string& email_id,
            const ClassificationResult& result
        ) = 0;

        // Load the classification result for a given email ID
        virtual std::optional<ClassificationResult>
            load(const std::string& email_id) const = 0;
    };

} // namespace persistence
