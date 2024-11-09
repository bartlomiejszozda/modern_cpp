#include <iostream>

#include "MyType.h"
#include "use_expected.h"
#include "use_optional.h"
#include "use_shared.h"
#include "use_span.h"
#include "use_string_view.h"

int main() {
    //    use_shared::doubleFree();
    //    use_shared::memoryLeak();
    //    use_expected::squareRoot(-1);
    //    use_expected::squareRoot(5);
    //    use_optional::drawEvenNumber();
    //    use_span::sortFirst4InPlace();
    //    use_formatter::printOwnTypeUsingFormatter();
    use_string_view::printChar();
    use_string_view::printString();


    return 0;
}
