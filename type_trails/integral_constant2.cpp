#include <iostream>
#include <type_traits>

template <unsigned n>
struct edad : std::integral_constant<int,n> {
};

int main() {

	constexpr int mi_edad { edad<54>::value };

    std::cout << std::boolalpha;
    std::cout << "from struct:" << edad<54>::value << std::endl;
    std::cout << "from INT:" << mi_edad << std::endl;

}

