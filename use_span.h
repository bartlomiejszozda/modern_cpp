#pragma once

#include <algorithm>
#include <iostream>
#include <span>
#include <vector>

#include "format_specializations.h"

namespace use_span {
    void sortFirst4WithSpan(std::span<int> int_collection) {
        auto num_el = 4;
        if (int_collection.size() >= num_el) {
            auto first4 = int_collection.subspan(0, num_el);
            std::sort(first4.begin(), first4.end());
        }
    }
}// namespace use_span