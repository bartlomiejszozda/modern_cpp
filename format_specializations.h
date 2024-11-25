#pragma once
#include <cstdio>
#include <format>
#include <string_view>
#include <vector>

template<typename... Args>
void print(const std::string_view fmt_str, Args &&...args) {
    auto fmt_args{std::make_format_args(args...)};
    std::string outstr{std::vformat(fmt_str, fmt_args) + "\n"};
    fputs(outstr.c_str(), stdout);
}

template<>
struct std::formatter<std::vector<int>> {
    template<typename ParseContext>
    constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();// No additional parsing needed
    }

    // Format the vector
    template<typename FormatContext>
    auto format(const std::vector<int> &vec, FormatContext &ctx) const {
        auto out = ctx.out();
        *out++ = '[';
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            if (it != vec.begin()) {
                *out++ = ',';
                *out++ = ' ';
            }
            out = std::format_to(out, "{}", *it);// Format each element
        }
        *out++ = ']';
        return out;
    }
};
