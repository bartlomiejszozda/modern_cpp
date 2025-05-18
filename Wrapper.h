#pragma once
#include <utility>
#include <vector>

template<typename T>
class Wrapper {
public:
    Wrapper(const Wrapper &) = default;
    Wrapper(Wrapper &&) = default;

    template<typename U>
        requires std::convertible_to<U &&, T>
    explicit Wrapper(U &&param) : wrapped(std::forward<U>(param)) {
    }

private:
    T wrapped;
};