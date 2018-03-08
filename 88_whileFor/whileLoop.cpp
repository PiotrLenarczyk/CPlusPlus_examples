#include <time.h>
#include <iostream>
using namespace std;
typedef uint32_t uint;
uint i = 0, t = 0;
const uint64_t N = 2147483648;	// 2GiB memory array ( 2*1024*1024*1024 )

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	//char* arr[ N ] = { 0 };	//ERROR: too big array ( dpends on motherboard memory driver )
	char *arr = ( char* )calloc( N, 1 );
	t = clock();
	for ( i = 0; i < N; i++ )
		arr[ i ] += 14;
	t = clock() - t;
	printf( "for loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( 1024.0f * 1024.0f * 1024.0f * float( t ) / float( CLOCKS_PER_SEC ) ), t );
	
	t = clock();
	i = 0;
	while ( i <= N )
	{	arr[ i ] += 14;
		i ++;
	}
	t = clock() - t;
	printf( "while forward loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( 1024.0f * 1024.0f * 1024.0f * float( t ) / float( CLOCKS_PER_SEC ) ), t );
	
	t = clock();
	i = N - 1;
	while ( i > 0 )
	{	arr[ i ] += 14;
		i --;
	}
	t = clock() - t;
	printf( "while backward loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( 1024.0f * 1024.0f * 1024.0f * float( t ) / float( CLOCKS_PER_SEC ) ), t );
	
	delete( arr );
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
