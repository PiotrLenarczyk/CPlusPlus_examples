#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;
typedef uint32_t uint;
size_t i = 0;
int b[ 6 ] = { 11, 22, 33, 44, 55, 66 };

mutex cout_mutex;
void coutmHcpy( uint localThNo, int in );	//arguments passed only by hardcopy
void coutmPtr( uint localThNo, int *in );	//arguments passed by memory-coalesced-access pointers

int main( void )
{
	const uint N = 4;
	vector < thread > vecTh( 0 );
	for ( i = 0; i < N; i++ )
		vecTh.push_back( thread( coutmHcpy, i, i ) ); 
	for ( i = 0; i < vecTh.size(); i++ )	
		vecTh[ i ].join();
	vecTh.clear();

	for ( i = 0; i < N; i++ )
		vecTh.push_back( thread( coutmPtr, i, &b[ i ] ) ); 
	for ( i = 0; i < vecTh.size(); i++ )
		vecTh[ i ].join();
	vecTh.clear();

	return 0;
}; //end of main()

void coutmHcpy( uint localThNo, int in )
{
	thread::id thName = this_thread::get_id();
	cout_mutex.lock();
		cout << "th[" << thName << "][" << localThNo << "] : ( " << in << " )\t\t;//freed\n";
	cout_mutex.unlock();
};

void coutmPtr( uint localThNo, int *in )
{
	thread::id thName = this_thread::get_id();
	cout_mutex.lock();
		cout << "th[" << thName << "][" << localThNo << "] : ( " << *in << " )\t\t;//freed\n";
	cout_mutex.unlock();
};

