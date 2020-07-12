#include <iostream>
#include <memory>
 
struct Foo : public std::enable_shared_from_this<Foo> {

    Foo() 
    { 
        std::cout << "Foo::Foo\n"; 
    }

    ~Foo() 
    { 
        std::cout << "Foo::~Foo\n"; 
    } 

    std::shared_ptr<Foo> getFoo() 
    { 
        return shared_from_this(); 
    }

};
 
int main() {

    // Se crea un nuevo Foo con y su direccion se almacena en f
    Foo *f = new Foo;

    // Se crea un pf1 que es un shared_ptr a Foo pero sin inicializar
    std::shared_ptr<Foo> pf1;
 
    {
        // Se crea un pf2 que es un shared_ptr a Foo y se inicializa con el puntero f
        // f ahora ya no es un problema porque pf2 se encarga del ciclo de vida del objeto Foo
        std::shared_ptr<Foo> pf2(f);

        // pf2 que no gestionaba ningun objeto ahora se le asigna otro std::shared_ptr<Foo>
        // que es creado internalmente por Foo gracias a heredar std::enable_shared_from_this<Foo>
        pf1 = pf2->getFoo();

        // Termina el ambito de pf2 pero el objeto que gestion no se destruye porque su gestion esta 
        // comnpartida con pf1 que es del ambito superior.
    }
 
    std::cout << "pf2 is gone\n";
    // Ahora termina el ambido de pf1 y si se destruira el objeto Foo

}
