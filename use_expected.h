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
}// namespace use_expected
