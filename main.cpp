#include <iostream>

#include "expected.h"
#include "optional.h"
#include "shared_ptr.h"

int main() {
    //    shared::doubleFree();
    //    shared::memoryLeak();
    //    expected::useExpected(-1);
    //    expected::useExpected(5);
    optional::useOptional();

    return 0;
}
