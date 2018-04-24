#include <stdio.h> 
#include <stdlib.h>
using namespace std;
typedef unsigned char byte;
typedef __uint32_t uint;
uint i = 0x0;
#define N 10
float arr[ N ];

int cmpf( const void* a, const void* b )
{	if ( *( float* )a == *( float* )b )
		return 0;
	if ( *( float* )a < *( float* )b )
		return -1;
	else
		return 1;
};//cmpf

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	i=0;while( i < N )
	{	arr[ i ] = ( rand() * rand() ) % 10;
		i+=1;
	};
	qsort( arr, N, sizeof( float ), cmpf );
	i=0;while( i < N )
	{	printf( "arr[%i] : %f\n", i, arr[ i ] );
		i+=1;
	};
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
