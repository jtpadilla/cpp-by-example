#include <iostream>
#include <atomic>
#include <condition_variable>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

// Mutex 
std::mutex cv_m;

// Condicion de variable
std::condition_variable cv;

// Un int con acceso atomico
std::atomic<int> i{0};
 
 // Este metodo esperara hasta que:
 //   1) Haya conseguido que se cunpla la condicion deseada
 //   2) Haya transcurrido el tiempo maximo que se quiere esperar (aunque no se haya cumplido la condicion deseada)
void waits(int idx)
{

    // Se utiliza el mutex para obtener un acceso exclusivo
    std::unique_lock<std::mutex> lk(cv_m);

    // Se toma una referencia de tiempo
    auto now = std::chrono::system_clock::now();

    // Se espera que se cunpla la condicion durante 100 milliseconds mas tarde de la referencia
    if (cv.wait_until(lk, now + idx * 1000ms, [](){return i == 1;}))
    {
        // Este thread ha consegudo el acceso exclusivo
        std::cerr << "Thread " << idx << " finished waiting. i == " << i << '\n';
    }
    else
    {
        // Este thread no ha consegudo el acceso exclusivo
        std::cerr << "Thread " << idx << " timed out. i == " << i << '\n';
    }
}
 

void signals()
{

    // El thread de control esperara 120ms..
    std::this_thread::sleep_for(2200ms);

    // Ahora envia una notidicacion a todos los 'waits' para que verifiquen la condicion
    std::cerr << "Notifying...\n";
    cv.notify_all();

    // El threda de control espera 100ms mas..
    std::this_thread::sleep_for(100ms);

    // Se realiza el cambio de la condicion
    i = 1;

    // Se envia otra vez la notificacion para que los threads que quedan vivos verifiquen de nuevo.
    std::cerr << "Notifying again...\n";
    cv.notify_all();

}
 
int main()
{

    // Se lanzan los threads controlados por la condicion
    std::thread t1(waits, 1);
    std::thread t2(waits, 2);
    std::thread t3(waits, 3);
    std::thread t4(waits, 4);
    std::thread t5(waits, 5);

    // Se lanza el thread de control que gestiona la condicion
    std::thread s(signals);

    // Esperamos a que termine todos los threads
    t1.join(); 
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    s.join();

}

