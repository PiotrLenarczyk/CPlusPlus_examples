#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
typedef unsigned int uint;
uint nSteps = 0;
int i = 0; //for backward-computations there is no possibility to use slightly faster size_t datatype
const uint N = 1E9 / 2;
vector < float > vec( N, 1.0f );
float arr [ N ];

int main( void )
{
	cout << "Lets assume that operations are both-directional:" << endl;
	nSteps = 0;
	auto t1 = chrono::high_resolution_clock::now();
	for ( i = 0; i < N; i++ )
	{
		vec[ i ] = vec[ i ] * 0.8f;
		nSteps++;
	}
	auto t2 = chrono::high_resolution_clock::now();
	cout << "forward vec SAXPY: "
              << float( chrono::duration_cast<chrono::nanoseconds>(t2-t1).count() ) / 1000000
              << " [ms]	nSteps = " << uint( nSteps ) << endl;
   
     
   	nSteps = 0;
   	t1 = chrono::high_resolution_clock::now();
	for ( i = 0; i < N; i++ )
	{
		arr[ i ] = arr[ i ] * 0.8f;
		nSteps++;
	}
	t2 = chrono::high_resolution_clock::now();
	cout << "forward arr SAXPY: "
              << float( chrono::duration_cast<chrono::nanoseconds>(t2-t1).count() ) / 1000000
              << " [ms]	nSteps = " << uint( nSteps ) << endl;
    
    nSteps = 0;
    t1 = chrono::high_resolution_clock::now();       
	for ( i = N - 1; i > -1; i-- )			
	{
		vec[ i ] = vec[ i ] * 0.8f;
		nSteps++;
	}
	t2 = chrono::high_resolution_clock::now();
	cout << "backward vec SAXPY: "
              << float( chrono::duration_cast<chrono::nanoseconds>(t2-t1).count() ) / 1000000
              << " [ms]	nSteps = " << uint( nSteps ) << endl;            
              
    nSteps = 0;
    t1 = chrono::high_resolution_clock::now();       
	for ( i = N - 1; i > -1; i-- )
	{
		arr[ i ] = arr[ i ] * 0.8f;
		nSteps++;
	}
	t2 = chrono::high_resolution_clock::now();
	cout << "backward arr SAXPY: "
              << float( chrono::duration_cast<chrono::nanoseconds>(t2-t1).count() ) / 1000000
              << " [ms]	nSteps = " << uint( nSteps ) << endl;    
    
	return 0;
}
