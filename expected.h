#pragma once
#include <expected>

namespace expected {
    [[nodiscard]] std::expected<int, std::string> someCalculations(int a) {
        if (a > 0) {
            return 5;
        } else {
            return std::unexpected("a is less than 0");
        }
    }

    void useExpected(int a) {
        auto exp = someCalculations(a);
        if (exp.has_value()) {
            std::cout << "result is: " << exp.value() * 2 << std::endl;

        } else {
            std::cout << "error is: " << exp.error() << std::endl;
        }
    }
}// namespace expected
