#include <iostream>

#include "use_expected.h"
#include "use_optional.h"
#include "use_shared.h"
#include "use_span.h"

int main() {
    //    shared::doubleFree();
    //    shared::memoryLeak();
    //    expected::useExpected(-1);
    //    expected::useExpected(5);
    //    optional::useOptional();
    use_span::useSpan();


    return 0;
}
