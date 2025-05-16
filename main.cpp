#include "MyType.h"
#include <iostream>
#include <memory>

int main() {

    std::unique_ptr<MyBaseType> my_type = std::make_unique<MyType>(std::make_shared<int>(5));
    my_type->overriden(5);
    return 0;
}