#include <iostream>
#include <chrono>

using namespace std;

int main()
{
    auto t1 = chrono::high_resolution_clock::now();
    int i;//trivialy its faster operation than chrono measurements
    auto t2 = chrono::high_resolution_clock::now(); //highest possible standard chronometrics
    cout << "int took "
              << chrono::duration_cast< chrono::nanoseconds >( t2 - t1 ).count()
              << " [ns]\n";
}
