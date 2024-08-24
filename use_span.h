#pragma once
#include <algorithm>
#include <iostream>
#include <span>
#include <vector>

#include "format_specializations.h"

namespace use_span {
    void sortWithSpan(std::span<int> int_collection) {
        std::sort(int_collection.begin(), int_collection.end());
    }

    void useSpan() {
        std::vector<int> ints{1, 3, 6, 0, 8, 2, 3, 9};
        MyType my;
        print("my type format: {}", my);
        print("ints before: {}", ints);
        sortWithSpan(ints);
        print("ints after: {}", ints);
    }
}// namespace use_span