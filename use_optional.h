#pragma once
#include <format>
#include <optional>
#include <random>

namespace use_optional {
    auto returnOptional() -> std::optional<int> {
        std::default_random_engine eng(std::random_device{}());
        std::uniform_int_distribution<int> int_distribution(0, 100);
        auto drawn = int_distribution(eng);
        if (drawn % 2) {
            return drawn;
        }
        return std::nullopt;
    }

    void drawEvenNumber() {
        auto opt = use_optional::returnOptional();
        if (opt.has_value()) {
            std::cout << std::format("{0} is optional", opt.value()) << std::endl;
        } else {
            std::cout << std::format("is not optional") << std::endl;
        }
    }

}// namespace use_optional