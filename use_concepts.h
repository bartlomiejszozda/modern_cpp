#include <concepts>
#include <range/v3/numeric.hpp>

namespace use_concepts {
    template<typename T>
    concept is_integer = std::is_same<T, int>::value;

    template<typename T>
        requires is_integer<T>
    void add_integers(T one, T two) {
    }

    template<typename T>
    void add_integers2(T one, T two)
        requires is_integer<T>
    {
    }

    template<is_integer T>
    void add_integers_shorter(T one, T two) {
    }

    void add_integers_auto(is_integer auto one, is_integer auto two) {
    }

    template<typename T>
        requires std::integral<T> || std::floating_point<T>
    constexpr double average(const std::vector<T> &input) {
        return ranges::accumulate(input, 0.0) / static_cast<double>(input.size());
    }

    template<typename T>
    concept is_calable_with_std_format = requires(T v) {
        print("{}", v);
    };

    void print_type(is_calable_with_std_format auto to_print) {
        print("{}", to_print);
    }

    class MyType2 {
    public:
        int a;
    };

    template<typename T>
    concept has_a_member_of_type_int = requires(T v) {
        { v.a } -> std::convertible_to<int>;
    };

    template<typename T>
    concept animal_interface = requires(T v) {
        v.move();
        v.make_sound();
    };

    class Animal {
    public:
        void move() {};
        void make_sound() {};
    };

    class NonAnimal {
        void doesnt_move() {};
        void doesnt_make_sound() {};
    };

    void move_and_make_sound(animal_interface auto animal) {
        animal.move();
        animal.make_sound();
    }
}// namespace use_concepts
