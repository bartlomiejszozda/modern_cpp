#include <iostream>

class A {
public:
    A() {
        std::cout << "A created" << "\n";
    }
    A(const A &a) {
        std::cout << "A copied" << "\n";
    }
    A(const A &&a) noexcept {
        std::cout << "A moved" << "\n";
    }
    A &operator=(const A &a) {
        std::cout << "A assignment copied" << "\n";
        return *this;
    }
    A &operator=(A &&a) noexcept {
        std::cout << "A assignment moved" << "\n";
        return *this;
    }
    A(A &) {
        std::cout << "A non-const copied" << "\n";
    }
    ~A() {
        std::cout << "~A destructed" << std::endl;
    }
};