#include <stdio.h> 
#include <stdlib.h>
#include <chrono>
#include "preproc.hpp"
using namespace std;
using namespace std::chrono;
typedef unsigned char byte;
typedef __uint32_t uint;

uint i = 0x0;
high_resolution_clock::time_point t;
float dur[ 5 ] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
#define N 8
float arr[ N ];
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{//CPU warm up
	t = chrono::high_resolution_clock::now(); 
		i=0;while( i < ( 0x1u << 18 ) ) { arr[ 0 ] = arr[ 0 ]; i+=1; };
	dur[ 0 ] =  duration_cast< duration< float > >( high_resolution_clock::now() - t ).count()* 1E9;
	
//	//goto
	t = chrono::high_resolution_clock::now();
	i=0;
jump:{	arr[ i ] += arr[ i ];
		if ( i < N ) 
		{	i+=1;
			goto jump;
		};
	};
    dur[ 0 ] =  duration_cast< duration< float > >( high_resolution_clock::now() - t ).count()* 1E9;
	
//	//for loop
	t = chrono::high_resolution_clock::now();
	for ( i = 0; i < N; i++)
		arr[ i ] += arr[ i ];
    dur[ 1 ] =  duration_cast< duration< float > >( high_resolution_clock::now() - t ).count()* 1E9;
    
//  //while loop
    t = chrono::high_resolution_clock::now();
	i=0;while( i < N )
	{	arr[ i ] += arr[ i ];
		i+=1;
	};
    dur[ 2 ] =  duration_cast< duration< float > >( high_resolution_clock::now() - t ).count()* 1E9;
//	//preprocessor FOR_EACH macro
	t = chrono::high_resolution_clock::now();
	__FE1( RMW_, arr, 0, 1, 2, 4, 5, 6, 7 );
    dur[ 3 ] =  duration_cast< duration< float > >( high_resolution_clock::now() - t ).count()* 1E9;
    
//	//direct instructions via string generator
	t = chrono::high_resolution_clock::now();
	arr[ 0 ] += arr[ 0 ];
	arr[ 1 ] += arr[ 1 ];
	arr[ 2 ] += arr[ 2 ];
	arr[ 3 ] += arr[ 3 ];
	arr[ 4 ] += arr[ 4 ];
	arr[ 5 ] += arr[ 5 ];
	arr[ 6 ] += arr[ 6 ];
	arr[ 7 ] += arr[ 7 ];
    dur[ 4 ] =  duration_cast< duration< float > >( high_resolution_clock::now() - t ).count()* 1E9;
    
//	summation
    printf( "goto loop : %19.2f[Bps]\n", float( N ) / dur[ 0 ] );
    printf( "for loop : %20.2f[Bps]\n", float( N ) / dur[ 1 ] );
	printf( "while loop : %18.2f[Bps]\n", float( N ) / dur[ 2 ] );
	printf( "macro loop : %18.2f[Bps]\n", float( N ) / dur[ 3 ] );
	printf( "direct instructions : %9.2f[Bps]\n", float( N ) / dur[ 4 ] );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
