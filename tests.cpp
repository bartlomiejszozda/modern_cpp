#include <gtest/gtest.h>

#include "MyType.h"
#include "Rule5Class.h"
#include "Wrapper.h"
#include "use_concepts.h"
#include "use_expected.h"
#include "use_optional.h"
#include "use_ranges.h"
#include "use_ranges_v3.h"
#include "use_shared.h"
#include "use_span.h"
#include "use_string_view.h"

TEST(testExpected, testSquareRoot) {
    auto exp = use_expected::calcSquareRoot(-1);
    EXPECT_FALSE(exp.has_value());
    EXPECT_EQ("a is less than 0", exp.error());

    auto exp2 = use_expected::calcSquareRoot(5);
    EXPECT_TRUE(exp2.has_value());
    EXPECT_NEAR(2.23, exp2.value(), 0.01);
}

TEST(TestOptional, testOptional) {
    auto opt = use_optional::drawAndreturnOptionalIfOdd();

    if (opt.has_value()) {
        EXPECT_TRUE(opt.value() % 2 == 1);
    }
}

TEST(TestSharedPtrs, testDoubleFree) {
    // use_shared::doubleFree();
}

TEST(TestSharedPtrs, testMemoryLeak) {
    // use_shared::memoryLeak();
}

TEST(TestSpan, testSortFirst4InPlace) {
    std::vector<int> ints{1, 3, 6, 0, 8, 2, 3, 9};
    use_span::sortFirst4WithSpan(ints);
    auto expected = std::vector<int>{0, 1, 3, 6, 8, 2, 3, 9};
    EXPECT_EQ(expected, ints);
}

TEST(TestSpan, testSpanMisuse) {
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

TEST(TestFormatter, testPrintOwnTypeUsingFormatter) {
    EXPECT_NO_THROW({
        MyType mytype{std::make_shared<Rule5Class>()};
        print("mytype printed with the formatter: {}", mytype);
    });
}

TEST(TestStringView, testStringViewAcceptsStringAndCharPtr) {
    const char *char_str = "const char ptr bla";
    std::string str{"string bla"};

    use_string_view::acceptStringView(str);                              // ok lval string
    use_string_view::acceptStringView(char_str);                         // ok lval char*
    use_string_view::acceptStringView("const char rval");                // ok, static array
    use_string_view::acceptStringView(std::string("const char ptr bla"));// also ok, temporary string will outlive printStringView
}

TEST(TestConstructDestruct, testConstructDestruct) {
    std::cout << "-----Test constructors, destructors, operators, const lifetime extension \n";
    {
        Rule5Class a = Rule5Class{};
        const Rule5Class a2 = a;
        Rule5Class a3, a4, a5{a2};
        a3 = a;
        a4 = std::move(a);

        auto a_lambda = []() { return Rule5Class{}; };

        // auto& cannot_bind_to_temporary = Rule5Class{}; cannot bind to temporary A
        const Rule5Class &const_lifetime_extension = a_lambda();// const lifetime extension
        auto &&not_extended_lifetime = Rule5Class{};
        // using not_extended_lifetime is UB because && doesn't extend lifetime of temporary
    }
    std::cout << "-----" << std::endl;
}

TEST(TestPerfectForwardingConstructDestruct, testPerfectForwardingConstructDestruct) {
    std::cout << "-----Perfect forwarding construct/destruct" << std::endl;

    {
        std::cout << "perfect forwarding by &&" << std::endl;
        Rule5Class obj;
        Wrapper<Rule5Class> wrapper(std::move(obj));
    }
    {
        std::cout << "perfect forwarding by value" << std::endl;
        Rule5Class obj;
        Wrapper<Rule5Class> wrapper(obj);
    }
    {
        std::cout << "perfect forwarding by const value" << std::endl;
        const Rule5Class obj;
        Wrapper<const Rule5Class> wrapper(obj);
    }
    {
        std::cout << "perfect forwarding by const value to const ref" << std::endl;
        const Rule5Class obj;
        Wrapper<const Rule5Class &> wrapper(obj);
    }
    std::cout << "-----" << std::endl;
}

TEST(TestStdRanges, testFilterEven) {
    std::vector<int> example{-6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
    std::vector<int> expected{-6, -4, -2, 0, 2, 4, 6};
    EXPECT_EQ(expected, use_ranges::filterEven(example));
}

TEST(TestStdRanges, testSquare) {
    std::vector<int> example{-6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
    std::vector<int> expected{36, 25, 16, 9, 4, 1, 0, 1, 4, 9, 16, 25, 36};
    EXPECT_EQ(expected, use_ranges::square(example));
}

TEST(TestStdRanges, testReverse) {
    std::vector<int> example{-6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
    std::vector<int> expected{6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6};
    EXPECT_EQ(expected, use_ranges::reverse(example));
}

TEST(TestStdRanges, testSquareOddTake2) {
    std::vector<int> example{-6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
    std::vector<int> expected{1, 9};
    EXPECT_EQ(expected, use_ranges::squareOddTake2(example));
}

TEST(TestStdRanges, testDrop2) {
    std::vector<int> example{-6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
    std::vector<int> expected{-4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
    EXPECT_EQ(expected, use_ranges::drop2(example));
}

TEST(TestStdRanges, testFlatNested) {
    std::vector<int> expected{1, 2, 3, 4, 5, 6};
    EXPECT_EQ(expected, use_ranges::flatNested({{1, 2},
                                                {3, 4},
                                                {5, 6}}));
}

TEST(TestStdRanges, testGenerateFromIota) {
    std::vector<int> expected{100, 101, 102, 103, 104, 105, 106, 107, 108, 109};
    EXPECT_EQ(expected, use_ranges::generateFromIota());
}

TEST(TestRangesV3, testSortReverseDrop5) {
    std::vector<int> input{2, 1, 4, 3, 5, 6, 7, 8, 9};
    std::vector<int> expected{9, 8, 7, 6, 5};
    auto result = use_ranges_v3::sortReverseDrop5(input);
    EXPECT_EQ(expected, result | ranges::to<std::vector<int>>);
    // Or compare one by one thanks to zip
    for (auto &&[exp, res]: ranges::views::zip(expected, result)) {
        EXPECT_EQ(exp, res);
    }
}

TEST(TestRangesV3, oddSquared) {
    using namespace ranges;
    std::vector vec{1, 2, 3, 4, 5, 6};
    auto result = vec | views::filter([](int el) { return el % 2; }) | views::transform([](auto el) { return el * el; });
    std::vector expected{1, 9, 25};
    EXPECT_EQ(expected, result | to<std::vector<int>>);
}
TEST(TestRangesV3, sumOfReciprocals) {
    std::vector<double> data = {2.0, 4.0, 8.0};
    EXPECT_EQ(0.875, use_ranges_v3::sumOfReciprocals1(data));
    EXPECT_EQ(0.875, use_ranges_v3::sumOfReciprocals2(data));
    data = {2.0, 4.0, 8.0};
    EXPECT_EQ(0.875, use_ranges_v3::sumOfReciprocals3(data));
    EXPECT_EQ(0.875, use_ranges_v3::sumOfReciprocals4(data));
}

TEST(TestRangesV3, binaryToDecimal) {
    std::vector<int> binary{1, 0, 1, 1, 0};
    auto expected = 22;
    EXPECT_EQ(expected, use_ranges_v3::binaryToDecimal(binary));
}

TEST(TestRangesV3, everyIntegerOnce) {
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 8, 9, 23, 53, 123};
    std::vector<int> input{1, 2, 3, 4, 5, 1, 2, 3, 6, 8, 9, 123, 53, 23};
    EXPECT_EQ(expected, use_ranges_v3::everyIntegerOnce(input));
}

TEST(TestRangesV3, splitByOne) {
    std::vector<int> input{1, 2, 3, 1, 4, 5, 1, 6, 7, 1, 8, 9};
    std::vector<std::vector<int>> expected{{}, {2, 3}, {4, 5}, {6, 7}, {8, 9}};
    EXPECT_EQ(expected, use_ranges_v3::toSplitByOne(input));
}

TEST(Concepts, add_integers) {
    using namespace use_concepts;
    add_integers(1, 2);
    add_integers2(1, 2);
    add_integers_shorter(1, 2);
    add_integers_auto(1, 2);
    // wont compile add_integers(1, 2.0);
}

TEST(Concepts, average) {
    using namespace use_concepts;
    std::vector<int> ints{1, 2, 3, 4, 5, 6, 7};
    EXPECT_EQ(4.0, average(ints));
    std::vector<float> floats{0.5, 1.5};
    EXPECT_EQ(1.0, average(floats));
    std::vector<double> doubles{0.5, 1.5};
    EXPECT_EQ(1.0, average(doubles));
    std::vector<char> chars{'a', 'b', 'c'};
    EXPECT_EQ('b', average(chars));
    // average(std::vector<MyType>{MyType{}, MyType{}}); // doesnt satisfy concept
}

TEST(Concepts, own_requires) {
    using namespace use_concepts;
    print_type(MyType{std::make_shared<Rule5Class>()});
    //    print_type(MyType2{});
    static_assert(has_a_member_of_type_int<MyType2>);
    static_assert(!has_a_member_of_type_int<MyType>);
    move_and_make_sound(Animal{});
    //    move_and_make_sound(NonAnimal{});
}
