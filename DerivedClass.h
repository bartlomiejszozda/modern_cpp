#pragma once
#include <iostream>

namespace call_virtual_from_constructor {
    using namespace std;

    class BaseClass {
    public:
        BaseClass() {
            foo();
        }
        virtual void foo() {
            cout << "foo from base" << endl;
        }
    };

    class DerivedClass : BaseClass {
    public:
        DerivedClass() {
        }
        void foo() {
            cout << "foo from derived" << endl;
        }
    };
}// namespace call_virtual_from_constructor