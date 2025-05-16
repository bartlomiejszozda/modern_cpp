#pragma once

#include "format_specializations.h"
#include <iostream>
#include <memory>

class MyBaseType {
public:
    virtual void overriden(int a) = 0;
};

class MyType : public MyBaseType {
public:
    MyType(std::shared_ptr<int> val) {
        value = val;
    }

    void overriden(int a) override {
        if (*value == a) {
            std::cout << "equal" << std::endl;
        } else {
            std::cout << "not equal" << std::endl;
        }
    };

private:
    std::shared_ptr<int> value;
};

template<>
struct std::formatter<MyType> {
    constexpr auto parse(std::format_parse_context &ctx) {
        return ctx.begin();// No additional parsing needed
    }

    auto format(const MyType &my, std::format_context &ctx) const {
        return std::format_to(ctx.out(), "my type from formatter");
    }
};