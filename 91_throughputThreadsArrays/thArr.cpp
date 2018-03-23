#include <pthread.h>
#include <vector>
#include <time.h>
#include <iostream>
using namespace std;
typedef unsigned char byte;
typedef uint32_t uint;
#define GB 1024lu*1024lu*1024lu
uint i = 0, N = 1 * GB, nThreads = 4;
uint t[ nThreads ];
void foo( uint no )
{	uint iFoo;
	byte* arr = ( byte* )malloc( N );
	t[ no ] = clock();
		iFoo=0u;while( iFoo < N )
		{	arr[ iFoo ] += arr[ iFoo ];
			iFoo++;
		};
	t[ no ] = clock() - t[ no ];
	delete( arr );
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	vector< pthread_t > vecTh( nThreads );
//	create threads within main thread
	for ( i = 0; i < nThreads; i++ )
		pthread_create( &vecTh[ i ], NULL, thKernel, ( void * )&thDataArr[ i ] );
//	sync threads execution
	for ( i = 0; i < nThreads; i++ )
		pthread_join( vecTh[ i ], NULL );
		
	foo();
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
