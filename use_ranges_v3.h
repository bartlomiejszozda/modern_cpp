#include <format>
#include <range/v3/action.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/core.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>


namespace use_ranges_v3 {
    auto sortReverseDrop5(std::span<int> input) {
        return input | ranges::views::all | ranges::views::drop(4) | ranges::actions::sort | ranges::views::reverse;
    }

    double sumOfReciprocals1(const std::span<double> data) {
        // typical transform
        {
            auto vec = data | ranges::views::transform([](const auto &el) { return 1.0 / el; });
            return ranges::accumulate(vec, 0.0);
        }
    }

    double sumOfReciprocals2(std::span<double> data) {
        // transform without copy - hack for testing purposes
        {
            auto view = data | ranges::views::transform([](auto &el) -> auto & { el = 1.0 / el; return el; });
            for (const auto &x: view) {
                // Forces evaluation
            }
            return ranges::accumulate(data, 0.0);
        }
    }

    auto sumOfReciprocals3(const std::span<double> data) {
        // another hack for testing purposes
        {
            double result;
            auto view = data | ranges::views::transform([&result](const auto &el) { result += 1.0 / el; return el; });
            for (const auto &x: view) {
                // Forces evaluation
            }
            return result;
        }
    }

    auto sumOfReciprocals4(const std::span<double> data) {
        // use fold left
        {
            auto view = data | ranges::views::transform([](const auto &el) { return 1.0 / el; });
            return ranges::fold_left(view, 0.0, std::plus{});
        }
    }

    int binaryToDecimal(const std::span<int> binary) {
        auto reversed = binary | ranges::views::reverse;
        auto values = ranges::views::iota(static_cast<size_t>(0), binary.size()) | ranges::views::transform([](const auto &el) { return 1 << el; });
        return ranges::inner_product(reversed, values, 0);
    }

    std::vector<int> everyIntegerOnce(std::vector<int> vec) {
        vec |= ranges::actions::sort | ranges::actions::unique;
        return vec;
    }

    std::vector<std::vector<int>> toSplitByOne(std::span<int> input) {
        return input | ranges::views::split(1) | ranges::to<std::vector<std::vector<int>>>;
    }

}// namespace use_ranges_v3
