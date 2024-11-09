#pragma once
#include <cmath>
#include <expected>

namespace use_expected {
    [[nodiscard]] std::expected<double, std::string> calcSquareRoot(double a) {
        if (a > 0) {
            return sqrt(a);
        } else {
            return std::unexpected("a is less than 0");
        }
    }

    void squareRoot(double a) {
        auto exp = calcSquareRoot(a);
        if (exp.has_value()) {
            std::cout << "result is: " << exp.value() << std::endl;
        } else {
            std::cout << "error is: " << exp.error() << std::endl;
        }
    }
}// namespace use_expected
