/*
	https://www.tutorialspoint.com/cplusplus/cpp_preprocessor.htm
*/
#include <iostream>
#include <vector>
#define CONCATENATE(a,b) a##b

using namespace std;
typedef uint32_t uint;
size_t i = 0;
uint N = 1E3;

template < typename T >
inline void funInc( vector< T > &vecIn )
{
	for ( auto &x:vecIn )
		x++;
};

int main( int argc, char* argv[] )
{	
	vector < float > vecf32_0( N, 0.0f );
	vector < float > vecf32_1( N, 0.0f );
	funInc( vecf32_0 );
	funInc( vecf32_1 );
	cout << "vecf32_0[ 1 ]: " << vecf32_0[ 1 ] << endl;
	cout << "vecf32_1[ 1 ]: " << vecf32_1[ 1 ] << endl;
	
	uint vecsNo = atoi( argv[ argc - 1 ] );
	for ( i = 0; i < vecsNo; i++ )
	{
		vector < float > CONCATENATE( vecf32__, i ) ( N, 0.0f );
		funInc( CONCATENATE( vecf32__, i ) );
		cout << "vecf32__" << i << "[ 1 ]: " << CONCATENATE( vecf32__, i )[ 1 ] << endl;
	}
	
	return 0;
}
