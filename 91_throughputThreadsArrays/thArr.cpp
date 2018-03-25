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
		iFoo=0u;while( iFoo < N )
		{	arr[ iFoo ] += arr[ iFoo ];
			iFoo++;
		};
	t[ no ] = clock() - t[ no ];
	printf( "thread[%i] has ended\n", no );
	delete( arr );
};

