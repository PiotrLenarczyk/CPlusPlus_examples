#include <iostream>
#include <chrono>
#include <math.h>
#include <vector>
#define N  1E6

using namespace std;
typedef unsigned int uint;
vector < float >  vecf( N, 0.0f );
vector < uint > vecInt( N, 0 );

void trigonometricF( vector < float > &vecFIn );
void trigonometricUINT( vector < uint > &vecUintIn );

int main( void )
{
	auto t1 = std::chrono::high_resolution_clock::now();
	trigonometricF( vecf );
	auto t2 = std::chrono::high_resolution_clock::now();
	cout << "vector< float > unroll timing: " << float( std::chrono::duration_cast< std::chrono::nanoseconds >( t2 - t1 ).count() ) / 1E6 << "[ms]" << endl;
	t1 = std::chrono::high_resolution_clock::now();
	uint i = 0;
	for( ; i < N; i++ )
	{
		vecf[ i ] = i * i;
	}
	t2 = std::chrono::high_resolution_clock::now();
	cout << "vector< float > timing: " << float( std::chrono::duration_cast< std::chrono::nanoseconds >( t2 - t1 ).count() ) / 1E6 << "[ms]" << endl;
	
	t1 = std::chrono::high_resolution_clock::now();
	trigonometricUINT( vecInt );
	t2 = std::chrono::high_resolution_clock::now();
	cout << "vector< uint > unroll timing: " << float( std::chrono::duration_cast< std::chrono::nanoseconds >( t2 - t1 ).count() ) / 1E6 << "[ms]" << endl;
	
	t1 = std::chrono::high_resolution_clock::now();
	i = 0;
	for( ; i < N; i++ )
	{
		vecInt[ i ] = i * i;
	}
	t2 = std::chrono::high_resolution_clock::now();
	cout << "vector< uint > timing: " << float( std::chrono::duration_cast< std::chrono::nanoseconds >( t2 - t1 ).count() ) / 1E6 << "[ms]" << endl;

	return 0;
}

#pragma GCC push_options
#pragma GCC optimize( "unroll-loops" )
void trigonometricF( vector < float > &vecFIn )
{
	uint i = 0;
	for( ; i < N; i++ )
	{
		vecFIn[ i ] = i * i;
	}
}
#pragma GCC pop_options

#pragma GCC push_options
#pragma GCC optimize( "unroll-loops" )
void trigonometricUINT( vector < uint > &vecUintIn )
{
	uint i = 0;
	for( ; i < N; i++ )
	{
		vecUintIn[ i ] = i * i;
	}
}
#pragma GCC pop_options

