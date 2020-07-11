#include <iostream>
#include <type_traits>

struct A { 

    A (int,int) 
    {
    }; 
    
};

int main() {

  std::cout << std::boolalpha;

  std::cout << "is_constructible:" << std::endl;

  // Un 'int' se puede contruir sin ningun parametro
  std::cout << "int: " << std::is_constructible<int>::value << std::endl;

  // Un 'int' se puede contruir con un parametro de tipo 'float' (hace un casting)
  std::cout << "int(float): " << std::is_constructible<int,float>::value << std::endl;

  // Un 'int' no se puede constuir con dos parametros 'float' (no hay un constructor con dos parametros)
  std::cout << "int(float,float): " << std::is_constructible<int,float,float>::value << std::endl;

  // Un 'A' no se puede construir sin parametros.
  std::cout << "A: " << std::is_constructible<A>::value << std::endl;

  // Un 'A' no se puede constuir con solo un parametro
  std::cout << "A(int): " << std::is_constructible<A,int>::value << std::endl;

  // Un 'A' si se puede construis con dos parametros 'int'
  std::cout << "A(int,int): " << std::is_constructible<A,int,int>::value << std::endl;

  // Un 'A' no se puede constuir con tres parametros
  std::cout << "A(int,int,int): " << std::is_constructible<A,int,int,int>::value << std::endl;

  // Un 'A' Se puede constuir con un parametro int o otro float
  std::cout << "A(int,float): " << std::is_constructible<A,int,float>::value << std::endl;

  // Un 'A' Se puede constuir con dos parametros float
  std::cout << "A(float,float): " << std::is_constructible<A,float,float>::value << std::endl;

  return 0;
}