#include <iostream>
#include <chrono>

using namespace std;

int main()
{
    auto t1 = std::chrono::high_resolution_clock::now();
    int i;//trivialy its faster operation than chrono measurements
    auto t2 = std::chrono::high_resolution_clock::now(); //highest possible standard chronometrics
    std::cout << "int took "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count()
              << " [ns]\n";
}
