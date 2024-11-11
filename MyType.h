#pragma once

#include "format_specializations.h"

class MyType {
};

template<>
struct std::formatter<MyType> {
    constexpr auto parse(std::format_parse_context &ctx) {
        return ctx.begin();// No additional parsing needed
    }

    // Format the vector
    auto format(const MyType &my, std::format_context &ctx) const {
        return std::format_to(ctx.out(), "my type from formatter");
    }
};