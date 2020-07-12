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
 
void waits(int idx)
{

    // Se utiliza el mutex para obtener un acceso exclusivo
    std::unique_lock<std::mutex> lk(cv_m);

    // Se toma una referencia de tiempo
    auto now = std::chrono::system_clock::now();

    // Se espera que se cunpla la condicion hasta 100 milliseconds mas tarde de la referencia
    if (cv.wait_until(lk, now + idx*100ms, [](){return i == 1;}))
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
    std::this_thread::sleep_for(120ms);
    std::cerr << "Notifying...\n";
    cv.notify_all();
    std::this_thread::sleep_for(100ms);
    i = 1;
    std::cerr << "Notifying again...\n";
    cv.notify_all();
}
 
int main()
{
    std::thread t1(waits, 1);
    std::thread t2(waits, 2);
    std::thread t3(waits, 3);
    std::thread t4(signals);
    t1.join(); 
    t2.join();
    t3.join();
    t4.join();
}

