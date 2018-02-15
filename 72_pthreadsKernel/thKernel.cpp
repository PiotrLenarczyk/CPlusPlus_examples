#include <stdlib.h>		//fprintf
#include <iostream>
#include <vector>		//pthreads container; threads data container
#include <pthread.h>	//pthreads
#include <unistd.h>		//getpid

using namespace std;
typedef uint32_t uint;
size_t i = 0;
#define nThreads 3

//single thread data struct
struct thData
{
//	thread header
	int thNo;	//program logic thread number
//	data header
	vector < float > data;				//data population should be coalesced
	uint64_t normData = 0;
	uint8_t   normDataOverflowCount = 0;
};
struct thData thDataArr[ nThreads ];	//each thread data struct must be populated separately
pthread_mutex_t printMutex;				//each thread printf

//single thread processing function
void *thKernel( void *thArg);

//======================================================================
//======================================================================
//======================================================================
int main( int argc, char * argv[] )
{
	vector< pthread_t > vecTh( nThreads );
//	create threads within main thread
	for ( i = 0; i < nThreads; i++ )
	{
		thDataArr[ i ].thNo = ( int )i;
		pthread_create( &vecTh[ i ], NULL, thKernel, ( void * )&thDataArr[ i ] );
	}
//	sync threads execution
	for ( i = 0; i < nThreads; i++ )
		pthread_join( vecTh[ i ], NULL );
		
	return 0;
};
//======================================================================
//======================================================================
//======================================================================

void *thKernel( void *thArg )
{
//	local thread stuff
	thData *localThData = ( thData* )( thArg );
	long int sysThId = pthread_self();
//	local thread data stuff
	const uint N = 1024;
	localThData->data.resize( N );
//	first attempt - th single printf
	//printf( "thread PID: %li\nsystem thread ID: %li\nprogram logic thread number: %i\nLocal thread data size: %i\n\n", 
				//( long int )getpid(), 
				//sysThId, 
				//localThData->thNo,
				//( uint )localThData->data.size());
				
//	second attempt - th print mutex
	pthread_mutex_lock( &printMutex );
		printf( "thread PID: %li\n", ( long int )getpid() );
		printf( "system thread ID: %li\n", sysThId );
		printf( "program logic thread number: %i\n", localThData->thNo );
		printf( "Local thread data size: %i\n\n", ( uint )localThData->data.size());
	pthread_mutex_unlock( &printMutex );

	return NULL;
};
