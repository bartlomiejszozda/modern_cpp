#include <format>
#include <iostream>
#include <memory>

namespace shared {
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

        delete a;// Manual deletion
        delete b;// Manual deletion
    }

    void memoryLeak() {
        auto a = std::make_shared<A>();
        auto b = std::make_shared<B>();

        a->ptrB = std::shared_ptr<B>(b);// A's shared_ptr to B
        b->ptrA = std::shared_ptr<A>(a);// B's shared_ptr to A
    }

}// namespace shared
