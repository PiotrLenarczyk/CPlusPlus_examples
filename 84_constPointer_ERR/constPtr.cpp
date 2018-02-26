#include <iostream>

using namespace std;
typedef uint32_t uint;
uint i = 0;

__attribute__((always_inline)) inline void 
foo( register int const * const inPtr, register const uint size,  int * const outPtr )
{
	for ( i = 0; i < size; i++ )
	{
		outPtr[ i ] = inPtr[ i ] % 2;
	};
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{
	const uint N = 2;
	int a[ N ] = { 5, 7 };
	int b[ N ] = { 0, 0 };
	for ( i = 0; i < N; i++ )
		printf( "b[%u] : %i\n", i,  b[ i ] );
	foo( &a[ 0 ], N, &b[ 0 ] );
	for ( i = 0; i < N; i++ )
		printf( "b[%u] : %i\n", i,  b[ i ] );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
