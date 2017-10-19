#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;
typedef unsigned int uint;
uint nSteps = 0;
int i = 0; //for backward-computations there is no possibility to use slightly faster size_t datatype
const uint N = 1E9 / 2;
const uint half = N / 2;
vector < float > vec( N, 1.0f );
float arr [ N ];
void forwardArr( float *arrIn );
void backwardArr( float *arrIn );

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
	cout << "forward vec: "
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
	cout << "forward arr: "
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
	cout << "backward vec: "
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
	cout << "backward arr: "
              << float( chrono::duration_cast<chrono::nanoseconds>(t2-t1).count() ) / 1000000
              << " [ms]	nSteps = " << uint( nSteps ) << endl;    
              
    nSteps = 0;
    t1 = chrono::high_resolution_clock::now();       
	for ( i = 0; i < half; i++ )			
	{
		vec[ i ] = vec[ i ] * 0.8f;
        vec[ half - i ] = vec[ half - i ] * 0.8f;
		nSteps++;
	}
	t2 = chrono::high_resolution_clock::now();
	cout << "forward-backward vec: "
              << float( chrono::duration_cast<chrono::nanoseconds>(t2-t1).count() ) / 1000000
              << " [ms]	nSteps = " << uint( nSteps ) << endl;    
    
    nSteps = 0;
    t1 = chrono::high_resolution_clock::now();       
	for ( i = 0; i < half; i++ )			
	{
		arr[ i ] = arr[ i ] * 0.8f;
        arr[ half - i ] = arr[ half - i ] * 0.8f;
		nSteps++;
	}
	t2 = chrono::high_resolution_clock::now();
	cout << "forward-backward arr: "
              << float( chrono::duration_cast<chrono::nanoseconds>(t2-t1).count() ) / 1000000
              << " [ms]	nSteps = " << uint( nSteps ) << endl;  
            
    t1 = chrono::high_resolution_clock::now();   
    std::thread th1(  forwardArr, arr );
    std::thread th2(  backwardArr, arr );
    th1.join();
    th2.join();
    asm("nop");
	t2 = chrono::high_resolution_clock::now();
	cout << "forward-backward threads arr: "
              << float( chrono::duration_cast<chrono::nanoseconds>(t2-t1).count() ) / 1000000
              << endl;  
    
    vector < std::thread > vecThread;       
    t1 = chrono::high_resolution_clock::now();   
    vecThread.push_back( std::thread(  forwardArr, arr ) );
    vecThread.push_back( std::thread(  backwardArr, arr ) );
    for ( auto &th: vecThread)
        th.join();
    asm("nop");
	t2 = chrono::high_resolution_clock::now();
	cout << "forward-backward vector<thread> arr: "
              << float( chrono::duration_cast<chrono::nanoseconds>(t2-t1).count() ) / 1000000
              << endl;  
              
	return 0;
}

void forwardArr( float *arrIn )
{
    for ( i = 0; i < half; i++ )			
	{
		arrIn[ i ] = arrIn[ i ] * 0.8f;
	}
};

void backwardArr( float *arrIn )
{
    for ( i = 0; i < half; i++ )			
	{
        arrIn[ half - i ] = arrIn[ half - i ] * 0.8f;
    }
}

//Post Scriptum: it is trivial to find out that forward vector poses greatest abilities with almost-fastest timing with programming Time To Market coefficient.
