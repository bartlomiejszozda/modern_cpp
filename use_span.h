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

    void sortFirst4InPlace() {
        std::vector<int> ints{1, 3, 6, 0, 8, 2, 3, 9};
        print("ints before: {}", ints);// print using std::format specialization
        sortFirst4WithSpan(ints);
        print("ints after: {}", ints);// print using std::format specialization
    }

    void spanMisuse() {
        auto retVec = []() { return std::vector<int>{1, 2, 3}; };
        std::span<const int> s = retVec();
        // lifetime of lambda returned value ends after this line so it's a dangling reference https://quuxplusone.github.io/blog/2021/10/03/p2447-span-from-initializer-list/#but-dangling
        // std::span is a non-owning reference (like pointer, reference, string_view, weak_ptr), so you need to ensure about object lifetime
        // however everything is fine when you do `fun(retVec());`, because lambda returned value lives till the next code line
        // std::span accepts rvalue, and you should know that it's a "parameter-only" type and non-owning reference
        // another interesting article about lifetimes: https://quuxplusone.github.io/blog/2019/03/11/value-category-is-not-lifetime/
        // the problem comes from string_view https://quuxplusone.github.io/blog/2018/03/27/string-view-is-a-borrow-type/
        // VERY SHORTLY: use std::string_view and std::span only as parameter types. https://quuxplusone.github.io/blog/2018/03/27/string-view-is-a-borrow-type/
    }
}// namespace use_span