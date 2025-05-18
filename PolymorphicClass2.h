#pragma once

#include <iostream>
using namespace std;

class BaseClass2 {
    BaseClass2() {
        foo();
    }
    virtual void foo() {
        cout << "foo from base" << endl;
    }
};

class PolymorphicClass2 {
    void foo() {
        cout << "foo from derived" << endl;
    }
};