#include <iostream>
#include <type_traits>

int main() {

    constexpr std::true_type verdadero;
    constexpr bool b_from_cast {verdadero};
    constexpr bool b_from_functor {verdadero()};
    constexpr bool b_from_value {std::true_type::value};

    std::cout << std::boolalpha;
    std::cout << "verdadero:" << verdadero() << std::endl;
    std::cout << "b_from_cast:" << b_from_cast << std::endl;
    std::cout << "b_from_functor:" << b_from_functor << std::endl;
    std::cout << "b_from_value:" << b_from_value << std::endl;

    return 0;

}