#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;
typedef uint32_t uint;
size_t i = 0;
vector < thread > vecTh( 0 );
const uint N = 4;
const uint l = 6;
vector < int > B;
void populateVec( vector< int > &in, const uint size );

mutex cout_mutex;							//stdout stream blocade
void coutmHcpy( uint localThNo, 			//arguments passed by hardcopy
				vector < int > in, 
				uint ind 
			  );	
void coutmPtr( uint localThNo, int *in );	//arguments passed by memory-coalesced-access pointers

mutex access_mutex;							//memory hazards blocade
void accMtx( uint localThNo, int *in );		//memory write queue

int main( void )
{
	populateVec( B, l ); 
	for ( i = 0; i < N; i++ )				//N-copies of B vector
		vecTh.push_back( thread( coutmHcpy, i, B, i ) ); 
	for ( i = 0; i < vecTh.size(); i++ )	
		vecTh[ i ].join();
	vecTh.clear();

	for ( i = 0; i < N; i++ )				//value passed by pointer
		vecTh.push_back( thread( coutmPtr, i, &B[ i ] ) ); 
	for ( i = 0; i < vecTh.size(); i++ )
		vecTh[ i ].join();
	vecTh.clear();

	for ( i = 0; i < N; i++ )				//each thread writes to the same memory address
		vecTh.push_back( thread( accMtx, i, &B[ 0 ] ) ); 
	for ( i = 0; i < vecTh.size(); i++ )
		vecTh[ i ].join();
	vecTh.clear();
    cout << "B[0]: " << B[ 0 ] << endl;

	return 0;
}; //end of main()

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Functions bodies
void populateVec( vector< int > &in, const uint size )
{
	in.resize( size );
	const int* ind0 = &in[ 0 ];
	uint ind = 0;
	for ( auto &x : in )
	{
		ind = &x - ind0;
		x = 10 * ind + ind;
	};
};

void coutmHcpy( uint localThNo, vector < int > in, uint ind )
{
	thread::id thName = this_thread::get_id();
	cout_mutex.lock();
		cout << "th[" << thName << "][" << localThNo << "] : ( " << in[ ind ] << " )\t\t;//freed[1]\n";
	cout_mutex.unlock();
};

void coutmPtr( uint localThNo, int *in )
{
	thread::id thName = this_thread::get_id();
	cout_mutex.lock();
		cout << "th[" << thName << "][" << localThNo << "] : ( " << *in << " )\t\t;//freed[1]\n";
	cout_mutex.unlock();
};

void accMtx( uint localThNo, int *in )
{
	thread::id thName = this_thread::get_id();
	access_mutex.lock();
	*in = localThNo;
	cout_mutex.lock();
		cout << "th[" << thName << "][" << localThNo << "] : " 
			 << "vec[0]: " << *in << "\t\t;//freed[2]\n";
	access_mutex.unlock();
	cout_mutex.unlock();
};

