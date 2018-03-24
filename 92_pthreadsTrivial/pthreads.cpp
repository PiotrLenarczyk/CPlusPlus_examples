#include <pthread.h>
#include <vector>
#include <time.h>
#include <iostream>
using namespace std;
typedef unsigned char byte;
typedef uint32_t uint;
#define nThreads 2
uint i = 0;
const uint fooNoArgs = 2;
void* foo( void* in )
{	uint arrIn[ fooNoArgs ];
	uint k=0;while( k < fooNoArgs )
	{	arrIn[ i ] = *( ( uint* )in + i );
		k++;
	};
	return nullptr;
};
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	vector< pthread_t > vecTh( nThreads );
//	create threads within main thread
	uint fooArgs[ fooNoArgs ];
	i=0;while( i < nThreads )
	{	fooArgs[ 0 ] = i;
		fooArgs[ 1 ] = i + 1;
		pthread_create( &vecTh[ i ], NULL, foo, ( void* )&fooArgs[ 0 ] );
		i++;
	};
//	sync threads execution
	i=0;while( i < nThreads )
	{	pthread_join( vecTh[ i ], NULL );
		i++;
	};

	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

