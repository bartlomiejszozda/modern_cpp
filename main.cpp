#include <iostream>

#include "MyType.h"
#include "use_expected.h"
#include "use_optional.h"
#include "use_ranges.h"
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
    //    use_span::spanMisuse();
    //    use_formatter::printOwnTypeUsingFormatter();
    //    use_string_view::printChar();
    //    use_string_view::printString();
    std::vector<int> example{-6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
    use_ranges::filterEven(example);
    use_ranges::square(example);
    use_ranges::reverse(example);
    use_ranges::squareOddTake2(example);
    use_ranges::drop2(example);
    use_ranges::flatNested({{1, 2},
                            {3, 4},
                            {5, 6}});
    use_ranges::generateFromIota();

    return 0;
}