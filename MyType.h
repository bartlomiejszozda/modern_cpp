#pragma once

#include "Rule5Class.h"
#include "format_specializations.h"
#include "use_shared.h"
#include <iostream>
#include <memory>

class MyBaseType {
public:
    virtual void compare_polymorphicaly(Rule5Class a) = 0;
    virtual ~MyBaseType() = default;
};

class MyType : public MyBaseType {
public:
    explicit MyType(const std::shared_ptr<Rule5Class> &val) {
        value = val;
    }

    void compare_polymorphicaly(Rule5Class a) override {
        if (*value == a) {
            std::cout << "equal" << std::endl;
        } else {
            std::cout << "not equal" << std::endl;
        }
    };

private:
    std::shared_ptr<Rule5Class> value;
};

class MyTypeWithMutable {
public:
    void const_method() const {
        this->mutable_member = "changed by const method";
    }

    mutable std::string mutable_member = "original";
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