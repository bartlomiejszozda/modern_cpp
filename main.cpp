#include "MyType.h"
#include "Rule5Class.h"
#include <iostream>
#include <memory>

int main() {

    {
        std::unique_ptr<MyBaseType> my_type = std::make_unique<MyType>(std::make_shared<Rule5Class>());
        my_type->compare_polymorphicaly(Rule5Class());
    }
    {
        const MyTypeWithMutable my_type_with_mutable;
        std::cout << my_type_with_mutable.mutable_member << std::endl;
        my_type_with_mutable.mutable_member = "changed by access";
        std::cout << my_type_with_mutable.mutable_member << std::endl;//changed by access
        my_type_with_mutable.const_method();
        std::cout << my_type_with_mutable.mutable_member << std::endl;//changed by const method
    }


    return 0;
}