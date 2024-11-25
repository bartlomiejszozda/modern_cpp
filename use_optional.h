#pragma once

#include <format>
#include <optional>
#include <random>

namespace use_optional {
    auto drawAndreturnOptionalIfOdd() -> std::optional<int> {
        std::default_random_engine eng(std::random_device{}());
        std::uniform_int_distribution<int> int_distribution(0, 100);
        auto drawn = int_distribution(eng);
        if (drawn % 2) {
            return drawn;
        }
        return std::nullopt;
    }
}// namespace use_optional