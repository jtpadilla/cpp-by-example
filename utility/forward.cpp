#include <utility>      // std::forward
#include <iostream>     // std::cout
#include <iomanip>

// acepta una referencia lvalue como parametro
template<class T>
void func2(T &)
{ 
    std::cout << "func2(T &)\n"; 
}

// Acepta una referencia lvalue a una constante como parametro
template<class T>
void func2(T const&)
{ 
    std::cout << "func2(T const&)\n"; 
}

// Acepta un referencia rvalue como parametro
template<class T>
void func2(T &&)
{ 
    std::cout << "func2(T &&)\n"; 
}

// Esta funcion recibe una referencioa rvalue como parametro y utiliza
// std::forward<T>() para seleccionar la version de func2() que corresponde.
template<class T>
void func(T&& a)
{
    func2(std::forward<T>(a));
}

// Esta funcion es utilizada para generar....
int f()
{ 
    return 7; 
}

// Esta funcion recibe un String que indica lo esperado y un functor que realiza
// la llamada a func() la cual mediante el std::forward() renvia a quien corresponda.
template<class Func>
void Test(const std::string& label, Func f)
{
    std::cout << std::setfill(' ') << std::setw(14) << std::left << label << " --> ";
    f();
}

int main()
{

    Test("func(T)",        []()
    {
        int a; 
        func(a); 
    });

    Test("func(T &)",      []()
    {
        int a; 
        int& b = a; 
        func(b); 
    });

    Test("func(T const&)", []()
    {
        int a; 
        const int& b = a; 
        func(b); 
    });

    Test("func(T &&)",     []()
    { 
        func(1); 
    });

    Test("func(T &&)",     []()
    { 
        func(f()); 
    });

    return 0;

}

