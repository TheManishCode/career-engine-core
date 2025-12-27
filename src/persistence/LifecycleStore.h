#pragma once

#include <optional>
#include <string>

#include "../lifecycle/LifecycleInference.h"

namespace persistence {

    /**
     * Contract for persisting inferred lifecycle state for a career opportunity.
     *
     * The meaning of thread_id is defined by the application layer.
     * The core engine does not interpret or generate thread identifiers.
     */
    struct LifecycleStore {
        virtual ~LifecycleStore() = default;

        // Save lifecycle state for a career thread / opportunity
        virtual void save(
            const std::string& thread_id,
            LifecycleState state
        ) = 0;

        // Load lifecycle state for a career thread / opportunity
        virtual std::optional<LifecycleState>
            load(const std::string& thread_id) const = 0;
    };

} // namespace persistence
