#include <iostream>
#include <type_traits>

int main() {

    constexpr std::false_type falso;
    constexpr bool b_from_cast {falso};
    constexpr bool b_from_functor {falso()};
    constexpr bool b_from_value {std::false_type::value};

    std::cout << std::boolalpha;
    std::cout << "falso:" << falso() << std::endl;
    std::cout << "b_from_cast:" << b_from_cast << std::endl;
    std::cout << "b_from_functor:" << b_from_functor << std::endl;
    std::cout << "b_from_value:" << b_from_value << std::endl;

    return 0;

}