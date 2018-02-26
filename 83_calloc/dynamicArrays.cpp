#include <iostream>
using namespace std;
typedef uint32_t uint;
uint i = 0;

__attribute__((always_inline)) static inline 
const void foo( void )
{
	const uint N = 100;
	float* arr = ( float* )calloc( N, sizeof( float ) ); //0 initialization
		puts( "\nDynamic array via calloc function:" );
		for ( i = 0; i < 3; i++ )
			printf( "arr[%i] : %f\n", i, arr[ i ] );
//	.... some dynamic array of zeros usage
	free( arr );	//must be freed!
};

__attribute__((always_inline)) static inline 
const void bar( void )
{
	const uint N = 100;
	float* arr = ( float* )malloc( N * sizeof( float ) ); //only memory allocation
		puts( "\nDynamic trash array via malloc function:" );
		for ( i = 0; i < 3; i++ )
			printf( "arr[%i] : %f\n", i, arr[ i ] );
//	.... some dynamic array of trash values usage
	free( arr );	//must be freed!
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	foo();
	bar();
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
