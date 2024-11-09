#pragma once
#include <iostream>
#include <string>

namespace use_string_view {
    void printStringView(std::string_view str) {
        std::cout << str << "\n";
    }

    void printChar() {
        const char *str = "const char ptr bla";
        printStringView(str);
    }

    void printString() {
        std::string str{"string bla"};
        printStringView(str);
    }
}// namespace use_string_view