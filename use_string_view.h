#pragma once

#include <iostream>
#include <string>

namespace use_string_view {
    void printStringView(std::string_view str) {
        std::cout << str << "\n";
    }

}// namespace use_string_view