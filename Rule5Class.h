#pragma once
#include <iostream>

class Rule5Class {
public:
    Rule5Class() : val(new int{0}) {
        std::cout << "Object created" << "\n";
    }
    Rule5Class(const Rule5Class &o) : val(new int{*o.val}) {
        std::cout << "Object copied" << "\n";
    }
    Rule5Class(Rule5Class &&o) noexcept : val(o.val) {
        o.val = nullptr;
        std::cout << "Object moved" << "\n";
    }
    Rule5Class &operator=(const Rule5Class &o) {
        if (this == &o) {
            return *this;
        }
        delete this->val;

        this->val = new int{*o.val};
        std::cout << "Object assignment copied" << "\n";
        return *this;
    }
    Rule5Class &operator=(Rule5Class &&o) noexcept {
        if (this == &o) {
            return *this;
        }
        delete this->val;
        this->val = o.val;
        o.val = nullptr;
        std::cout << "Object assignment moved" << "\n";
        return *this;
    }
    /*
    Rule5Class(Rule5Class &) {
        // just for testing, not a bright idea to create such copy constructor
        val = new int{0};
        std::cout << "Object non-const copied" << "\n";
    }
     */

    /*
    // copy swap idiom
    Rule5Class &operator=(Rule5Class o) {
        std::swap(this->val, o.val);
        // better to use swap instead of this->val = o.val; because o destructor will delete o.val (swapped from this->val) automatically.
        return *this;
    }
    */

    ~Rule5Class() {
        delete val;
        std::cout << "~Object destructed" << std::endl;
    }
    bool operator==(const Rule5Class &o) const {
        return *this->val == *o.val;
    }

private:
    int *val;
};