#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point t3, t4, t5;

int main( void )
{   auto t1 = chrono::high_resolution_clock::now();
    int i;//trivialy its faster operation than chrono measurements
    auto t2 = chrono::high_resolution_clock::now(); //highest possible standard chronometrics
    cout << "int took "
              << chrono::duration_cast< chrono::nanoseconds >( t2 - t1 ).count()
              << " [ns]\n";
              
    t3 = high_resolution_clock::now();
	int j;
    t4 = high_resolution_clock::now();
	float sec =  duration_cast< duration< float > >( t4 - t3 ).count();
	printf( "sec : %f[ns]\n", sec * 1E9 );
	
	t5 = high_resolution_clock::now();
	int k;
	float ns =  duration_cast< duration< float > >( high_resolution_clock::now() - t5 ).count()* 1E9;
	printf( "ns : %f[ns]\n", ns );
              
    return 0;
}
