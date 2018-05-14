#include <iostream>
using namespace std;
typedef uint32_t uint;
uint i = 0;

__attribute__((always_inline)) static inline 
void foo( const int in = 1, int* out = nullptr )
{	printf( "in = %i\n", in );
	if ( out != nullptr )
		printf( "*out : %i\n", *out );
};

__attribute__((always_inline)) static inline 
void bar( const uint *in = nullptr, const uint inSize = 0 )
{	for ( i = 0; i < inSize; i++ )
		printf( "in[%i] : %u\n", i, in[ i ] );
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	int a = 5;
	foo( -1 );
	foo( a );
	foo( a, &a );
	
#define N 3
	uint arr[ N ] = { 5, 6, 11 };
	bar( &arr[ 0 ], N );
	bar();	//it is not an error!
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
