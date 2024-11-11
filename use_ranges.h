#pragma once

#include <span>
#include <string>
#include <ranges>
#include <iostream>
#include "format_specializations.h"

/*
Task 3.5: Learn how to create own ranges pipe object and create filterEven and square functions in such way that they can be used in ranges pipe

Need to use ranges-v3:
        Task 8: Chaining Views with views::cycle
        Goal: Repeat a short range cyclically to create a range of repeating values.
        Details: Use views::cycle to repeat a range (e.g., {1, 2, 3}) multiple times. Limit the length with views::take.
        Example: Input {1, 2, 3} with views::take(10) should output {1, 2, 3, 1, 2, 3, 1, 2, 3, 1}.

        Task 9: Applying views::unique
        Goal: Remove consecutive duplicate numbers in a sorted list.
        Details: Use std::views::unique to remove consecutive duplicates.
        Example: Input {1, 1, 2, 2, 2, 3, 3, 4} should output {1, 2, 3, 4}.

        Task 10: Applying views::generate
        Goal: Generate an infinite range of numbers based on a formula (e.g., 3 * n + 1).
        Details: Use std::views::generate with a lambda that returns a formula-based sequence. Limit the length with views::take.
        Example: Starting with 1, formula 3 * n + 1, take 5 numbers: {1, 4, 13, 40, 121}.

        Task 11: Working with views::zip
        Goal: Create a range of pairs by zipping two ranges together.
        Details: Use views::zip to combine two ranges (e.g., {1, 2, 3} and {'a', 'b', 'c'}) into pairs.
        Example: {1, 2, 3} and {'a', 'b', 'c'} should output {(1, 'a'), (2, 'b'), (3, 'c')}.

        Task 12: Sliding Window with Custom View
        Goal: Implement a sliding window view that groups elements into small, overlapping subranges.
        Details: Write a custom view or use std::views::sliding (if available) to create sliding subranges over the data.
        Example: For {1, 2, 3, 4, 5} with a window size of 3, the output should be { {1, 2, 3}, {2, 3, 4}, {3, 4, 5} }.
*/

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
        return "dupa";
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