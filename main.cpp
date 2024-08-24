#include <iostream>

#include "expected.h"
#include "optional.h"
#include "shared_ptr.h"
#include "span.h"

int main() {
    //    shared::doubleFree();
    //    shared::memoryLeak();
    //    expected::useExpected(-1);
    //    expected::useExpected(5);
    //    optional::useOptional();
    span::useSpan();


    return 0;
}
