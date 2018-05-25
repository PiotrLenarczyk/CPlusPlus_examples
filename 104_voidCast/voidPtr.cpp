#include <stdio.h> 
using namespace std;
typedef unsigned char byte;
typedef __uint32_t uint;
uint i = 0x0;

#define CAST2( destPtr )		( destPtr )( const void* )
#define CAST( destPtr, expr )	( destPtr )( const void* )( expr )

void foo( float* in )
{	printf( "%f\n", *in );
};//foo()

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	byte a[ 4 ] = {	0, 0, 0x80, 0x3F, }; 	//1.0f
	foo( ( float* )( const void* )&a[ 0 ] );
	foo( CAST( float*, a ) );
	foo( CAST2( float* )"0000" );			//0.0f
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
