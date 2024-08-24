#include <format>
#include <optional>
#include <random>

namespace optional {
    auto returnOptional() -> std::optional<int> {
        std::default_random_engine eng(std::random_device{}());
        std::uniform_int_distribution<int> int_distribution(0, 10);
        auto drawn = int_distribution(eng);
        if (drawn % 2) {
            return drawn;
        }
        return std::nullopt;
    }

    void useOptional() {
        auto opt = optional::returnOptional();
        if (opt.has_value()) {
            std::cout << std::format("{0} is optional", opt.value());
        } else {
            std::cout << std::format("is not optional");
        }
    }

}// namespace optional