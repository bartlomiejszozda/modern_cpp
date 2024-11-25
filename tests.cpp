#include <gtest/gtest.h>

#include "MyType.h"
#include "use_expected.h"
#include "use_optional.h"
#include "use_ranges.h"
#include "use_shared.h"
#include "use_span.h"
#include "use_string_view.h"

TEST(Test, testSquareRoot) {
    auto exp = use_expected::calcSquareRoot(-1);
    EXPECT_FALSE(exp.has_value());
    EXPECT_EQ("a is less than 0", exp.error());

    auto exp2 = use_expected::calcSquareRoot(5);
    EXPECT_TRUE(exp2.has_value());
    EXPECT_NEAR(2.23, exp2.value(), 0.01);
}

TEST(Test, testOptional) {
    auto opt = use_optional::drawAndreturnOptionalIfOdd();

    if (opt.has_value()) {
        EXPECT_TRUE(opt.value() % 2 == 1);
    }
}

TEST(Test, testDoubleFree) {
    // use_shared::doubleFree();
}

TEST(Test, testMemoryLeak) {
    // use_shared::memoryLeak();
}

TEST(Test, testSortFirst4InPlace) {
    std::vector<int> ints{1, 3, 6, 0, 8, 2, 3, 9};
    use_span::sortFirst4WithSpan(ints);
    auto expected = std::vector<int>{0, 1, 3, 6, 8, 2, 3, 9};
    EXPECT_EQ(expected, ints);
}

TEST(Test, testSpanMisuse) {
    //auto retVec = []() { return std::vector<int>{1, 2, 3}; };
    //std::span<const int> s = retVec();

    // DESCRIPTION:
    // lifetime of lambda returned value ends after this line so it's a dangling reference https://quuxplusone.github.io/blog/2021/10/03/p2447-span-from-initializer-list/#but-dangling
    // std::span is a non-owning reference (like pointer, reference, string_view, weak_ptr), so you need to ensure about object lifetime
    // however everything is fine when you do `fun(retVec());`, because lambda returned value lives till the next code line
    // std::span accepts rvalue, and you should know that it's a "parameter-only" type and non-owning reference
    // another interesting article about lifetimes: https://quuxplusone.github.io/blog/2019/03/11/value-category-is-not-lifetime/
    // the problem comes from string_view https://quuxplusone.github.io/blog/2018/03/27/string-view-is-a-borrow-type/
    // VERY SHORTLY: use std::string_view and std::span only as parameter types. https://quuxplusone.github.io/blog/2018/03/27/string-view-is-a-borrow-type/
}

TEST(Test, testPrintOwnTypeUsingFormatter) {
    EXPECT_NO_THROW({
        MyType mytype;
        print("mytype printed with the formatter: {}", mytype);
    });
}

TEST(Test, testStringViewAcceptsStringAndCharPtr) {
    const char *char_str = "const char ptr bla";
    std::string str{"string bla"};

    use_string_view::printStringView(str);                              //ok lval string
    use_string_view::printStringView(char_str);                         //ok lval char*
    use_string_view::printStringView("const char rval");                // ok, static array
    use_string_view::printStringView(std::string("const char ptr bla"));//also ok, temporary string will outlive printStringView
}

TEST(Test, testFilterEven) {
    std::vector<int> example{-6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
    std::vector<int> expected{-6, -4, -2, 0, 2, 4, 6};
    EXPECT_EQ(expected, use_ranges::filterEven(example));
}

TEST(Test, testSquare) {
    std::vector<int> example{-6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
    std::vector<int> expected{36, 25, 16, 9, 4, 1, 0, 1, 4, 9, 16, 25, 36};
    EXPECT_EQ(expected, use_ranges::square(example));
}

TEST(Test, testReverse) {
    std::vector<int> example{-6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
    std::vector<int> expected{6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6};
    EXPECT_EQ(expected, use_ranges::reverse(example));
}

TEST(Test, testSquareOddTake2) {
    std::vector<int> example{-6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
    std::vector<int> expected{1, 9};
    EXPECT_EQ(expected, use_ranges::squareOddTake2(example));
}

TEST(Test, testDrop2) {
    std::vector<int> example{-6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
    std::vector<int> expected{-4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
    EXPECT_EQ(expected, use_ranges::drop2(example));
}

TEST(Test, testFlatNested) {
    std::vector<int> expected{1, 2, 3, 4, 5, 6};
    EXPECT_EQ(expected, use_ranges::flatNested({{1, 2},
                                                {3, 4},
                                                {5, 6}}));
}

TEST(Test, testGenerateFromIota) {
    std::vector<int> expected{100, 101, 102, 103, 104, 105, 106, 107, 108, 109};
    EXPECT_EQ(expected, use_ranges::generateFromIota());
}
