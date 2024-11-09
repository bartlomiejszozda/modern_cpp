#pragma once
#include <format>
#include <iostream>
#include <memory>

namespace use_shared {
    class B;// Forward declaration

    class A {
    public:
        std::shared_ptr<B> ptrB;
        ~A() { std::cout << "A destroyed\n"; }
    };

    class B {
    public:
        std::shared_ptr<A> ptrA;
        ~B() { std::cout << "B destroyed\n"; }
    };

    void doubleFree() {
        A *a = new A();
        B *b = new B();

        a->ptrB = std::shared_ptr<B>(b);// A's shared_ptr to B
        b->ptrA = std::shared_ptr<A>(a);// B's shared_ptr to A

        delete a;// delete b also, because shared_ptr(b) counter = 1
        delete b;// second b deletion
    }

    void memoryLeak() {
        auto a = std::make_shared<A>();
        auto b = std::make_shared<B>();

        a->ptrB = std::shared_ptr<B>(b);
        b->ptrA = std::shared_ptr<A>(a);

        // call shared_ptr(a) destructor (not A destructor) and only shared_ptr(a) counter is decreased
        // call shared_ptr(b) destructor (not B destructor) and only shared_ptr(b) counter is decreased
        // finally shared_ptr(a) and shared_ptr(b) counters are 1. a and b aren't deleted
    }

}// namespace use_shared
