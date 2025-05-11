#pragma once

#include "format_specializations.h"
#include <iostream>
#include <ranges>
#include <span>
#include <string>

namespace use_ranges {
    std::string most_frequent_word() {
        std::vector<std::string> sentences{" Lorem ipsum dolor sit amet,",
                                           " consectetur adipiscing elit,",
                                           " sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.",
                                           " Ut enim ad minim veniam,",
                                           " quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.",
                                           " Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.",
                                           " Excepteur sint occaecat cupidatat non proident,",
                                           " sunt in culpa qui officia deserunt mollit anim id est laborum.",
                                           " Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium,",
                                           " totam rem aperiam,",
                                           " eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo.",
                                           " Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit,",
                                           " sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt.",
                                           " Neque porro quisquam est,",
                                           " qui dolorem ipsum quia dolor sit amet, consectetur,",
                                           " adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem.",
                                           " Ut enim ad minima veniam,",
                                           " quis nostrum exercitationem ullam corporis suscipit laboriosam,",
                                           " nisi ut aliquid ex ea commodi consequatur?",
                                           " Quis autem vel eum iure reprehenderit qui in ea voluptate velit esse quam nihil molestiae consequatur,",
                                           " vel illum qui dolorem eum fugiat quo voluptas nulla pariatur?"};
        // remove punctuation marks
        // convert to lovercase
        // split by spaces
        // prepare a list (or better a map) with word count
        // return N most frequent words
        return "";
    }

    std::vector<int> toVector(auto range) {
        std::vector<int> result;
        std::ranges::copy(range, std::back_inserter(result));
        return result;
    }

    std::vector<int> filterEven(std::span<int> numbers) {
        auto even_numbers = numbers | std::views::filter([](const int num) { return num % 2 == 0; });
        return toVector(even_numbers);
    }

    std::vector<int> square(std::span<int> numbers) {
        auto squared = numbers | std::views::transform([](const int num) { return num * num; });
        return toVector(squared);
    }

    std::vector<int> reverse(std::span<int> numbers) {
        auto squaredOddFirst2 =
                numbers | std::views::reverse;
        return toVector(squaredOddFirst2);
    }

    std::vector<int> drop2(std::span<int> numbers) {
        auto squaredOddFirst2 = numbers | std::views::drop(2);
        return toVector(squaredOddFirst2);
    }

    std::vector<int> squareOddTake2(std::span<int> numbers) {
        auto squaredOddFirst2 = numbers | std::views::filter([](const int num) { return num % 2 == 1; }) |
                                std::views::transform([](const int num) { return num * num; }) | std::views::take(2);
        return toVector(squaredOddFirst2);
    }

    std::vector<int> flatNested(std::vector<std::vector<int>> numbers) {
        auto flated = numbers | std::views::join;
        return toVector(flated);
    }

    std::vector<int> generateFromIota() {
        auto generated = std::views::iota(100) | std::views::take(10);
        return toVector(generated);
    }
}// namespace use_ranges