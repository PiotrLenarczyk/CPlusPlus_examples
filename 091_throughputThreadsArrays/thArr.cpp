#include <pthread.h>
#include <vector>
#include <time.h>
#include <iostream>
using namespace std;
typedef unsigned char byte;
typedef uint32_t uint;
#define GB 1024lu*1024lu*1024lu
#define nThreads 3
long unsigned int i = 0;
uint noN = 1, N = noN * GB;
uint t[ nThreads ]; float tSum = 0; 
void* foo( void* in );
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	vector< pthread_t > vecTh( nThreads );
//	create threads within main thread
	i=0;while( i < nThreads )
	{	pthread_create( &vecTh[ i ], NULL, foo, ( void* )i );
		i += 1;
	};
//	sync threads execution
	i=0;while( i < nThreads )
	{	pthread_join( vecTh[ i ], NULL );
		i++;
	};
	i=0;while( i < nThreads )
	{	tSum = t[ i ];
		i++;
	};
	if ( tSum < 500 )
		printf( "\tERROR!\n" );
	else
		printf( "For %i[threads] of %u[GB] arrays throughput is: %02f[GBps]; %02f[periods];\n", 
				nThreads,
				noN,
				( noN * nThreads ) / ( tSum / float( CLOCKS_PER_SEC ) ), 
				tSum );
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void* foo( void* in )
{	uint no = ( uint )in;
	uint iFoo;
	byte* arr = ( byte* )malloc( N );
	t[ no ] = clock();
//	LINEAR
/*		iFoo=0u;while( iFoo < N )
		{	arr[ iFoo ] += arr[ iFoo ];
			iFoo++;
		};//*/
//	4B
/*		iFoo=0u;while( iFoo < N )
		{	arr[ iFoo + 0 ] += arr[ iFoo + 0 ];
			arr[ iFoo + 1 ] += arr[ iFoo + 1 ];
			arr[ iFoo + 2 ] += arr[ iFoo + 2 ];
			arr[ iFoo + 3 ] += arr[ iFoo + 3 ];
			iFoo += 4;
		};//*/
//	6B
		iFoo=0u;while( iFoo < N )
		{	arr[ iFoo + 0 ] += arr[ iFoo + 0 ];
			arr[ iFoo + 1 ] += arr[ iFoo + 1 ];
			arr[ iFoo + 2 ] += arr[ iFoo + 2 ];
			arr[ iFoo + 3 ] += arr[ iFoo + 3 ];
			arr[ iFoo + 4 ] += arr[ iFoo + 4 ];
			arr[ iFoo + 5 ] += arr[ iFoo + 5 ];
			iFoo += 6;
		};//*/
//	8B
/*		iFoo=0u;while( iFoo < N )
		{	arr[ iFoo + 0 ] += arr[ iFoo + 0 ];
			arr[ iFoo + 1 ] += arr[ iFoo + 1 ];
			arr[ iFoo + 2 ] += arr[ iFoo + 2 ];
			arr[ iFoo + 3 ] += arr[ iFoo + 3 ];
			arr[ iFoo + 4 ] += arr[ iFoo + 4 ];
			arr[ iFoo + 5 ] += arr[ iFoo + 5 ];
			arr[ iFoo + 6 ] += arr[ iFoo + 6 ];
			arr[ iFoo + 7 ] += arr[ iFoo + 7 ];
			iFoo += 8;
		};//*/
//	16B
/*		iFoo=0u;while( iFoo < N )
		{	arr[ iFoo + 0 ] += arr[ iFoo + 0 ];
			arr[ iFoo + 1 ] += arr[ iFoo + 1 ];
			arr[ iFoo + 2 ] += arr[ iFoo + 2 ];
			arr[ iFoo + 3 ] += arr[ iFoo + 3 ];
			arr[ iFoo + 4 ] += arr[ iFoo + 4 ];
			arr[ iFoo + 5 ] += arr[ iFoo + 5 ];
			arr[ iFoo + 6 ] += arr[ iFoo + 6 ];
			arr[ iFoo + 7 ] += arr[ iFoo + 7 ];
			arr[ iFoo + 8 ] += arr[ iFoo + 8 ];
			arr[ iFoo + 9 ] += arr[ iFoo + 9 ];
			arr[ iFoo + 10 ] += arr[ iFoo + 10 ];
			arr[ iFoo + 11 ] += arr[ iFoo + 11 ];
			arr[ iFoo + 12 ] += arr[ iFoo + 12 ];
			arr[ iFoo + 13 ] += arr[ iFoo + 13 ];
			arr[ iFoo + 14 ] += arr[ iFoo + 14 ];
			arr[ iFoo + 15 ] += arr[ iFoo + 15 ];
			iFoo += 16;
		};//*/
//	32B
/*		iFoo=0u;while( iFoo < N )
		{	arr[ iFoo + 0 ] += arr[ iFoo + 0 ];
			arr[ iFoo + 1 ] += arr[ iFoo + 1 ];
			arr[ iFoo + 2 ] += arr[ iFoo + 2 ];
			arr[ iFoo + 3 ] += arr[ iFoo + 3 ];
			arr[ iFoo + 4 ] += arr[ iFoo + 4 ];
			arr[ iFoo + 5 ] += arr[ iFoo + 5 ];
			arr[ iFoo + 6 ] += arr[ iFoo + 6 ];
			arr[ iFoo + 7 ] += arr[ iFoo + 7 ];
			arr[ iFoo + 8 ] += arr[ iFoo + 8 ];
			arr[ iFoo + 9 ] += arr[ iFoo + 9 ];
			arr[ iFoo + 10 ] += arr[ iFoo + 10 ];
			arr[ iFoo + 11 ] += arr[ iFoo + 11 ];
			arr[ iFoo + 12 ] += arr[ iFoo + 12 ];
			arr[ iFoo + 13 ] += arr[ iFoo + 13 ];
			arr[ iFoo + 14 ] += arr[ iFoo + 14 ];
			arr[ iFoo + 15 ] += arr[ iFoo + 15 ];
			arr[ iFoo + 16 ] += arr[ iFoo + 16 ];
			arr[ iFoo + 17 ] += arr[ iFoo + 17 ];
			arr[ iFoo + 18 ] += arr[ iFoo + 18 ];
			arr[ iFoo + 19 ] += arr[ iFoo + 19 ];
			arr[ iFoo + 20 ] += arr[ iFoo + 20 ];
			arr[ iFoo + 21 ] += arr[ iFoo + 21 ];
			arr[ iFoo + 22 ] += arr[ iFoo + 22 ];
			arr[ iFoo + 23 ] += arr[ iFoo + 23 ];
			arr[ iFoo + 24 ] += arr[ iFoo + 24 ];
			arr[ iFoo + 25 ] += arr[ iFoo + 25 ];
			arr[ iFoo + 26 ] += arr[ iFoo + 26 ];
			arr[ iFoo + 27 ] += arr[ iFoo + 27 ];
			arr[ iFoo + 28 ] += arr[ iFoo + 28 ];
			arr[ iFoo + 29 ] += arr[ iFoo + 29 ];
			arr[ iFoo + 30 ] += arr[ iFoo + 30 ];
			arr[ iFoo + 31 ] += arr[ iFoo + 31 ];
			iFoo += 32;
		};//*/
	t[ no ] = clock() - t[ no ];
	printf( "thread[%i] has ended\n", no );
	delete( arr );
};
