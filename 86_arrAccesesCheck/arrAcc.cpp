#include <time.h>
#include <iostream>
#include <array>
using namespace std;
typedef uint32_t uint;
uint i = 0, t = 0;
const uint mltFact = 16;
const uint N = mltFact * 1024 * 1024;	  
const uint X = 12;						//try other values
const uint Y = N / X;

void printT( const char *name, uint t );

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	float tmp = 14.1f;
	float arr1D[ N ];
	t = clock();
	for ( i = 0; i < N; i++ )
		arr1D[ i ] = tmp;
	printT( "arr1D", clock() - t );
	
	const float cTmp = 1.1f;
	t = clock();
	for ( i = 0; i < N; i++ )
		arr1D[ i ] = cTmp;
	t = clock() - t;
	printT( "arr1D+=const", clock() - t );
													 
	float arr2D[ Y ][ X ];
	t = clock();
	for ( uint y = 0; y < Y; y++ )
		for ( uint x = 0; x < X; x++ )
			arr2D[ y ][ x ] = tmp;
	printT( "arr2D", clock() - t );

	array< float, N > arrCont;
	t = clock();
	for ( i = 0; i < N; i++ )
		arrCont[ i ] = tmp;
	printT( "arrCont", clock() - t );

	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void printT( const char *name, uint t )
{	if ( t < 50 ){ printf( "\tERROR: [%s]\n", name ); return; };
	printf( "%s[%u] : %02f[GBps]; %02f[s]; %i clks\n", name, N, ( float( mltFact ) * 4.0f ) / ( 1024.0f * float( t ) / float( CLOCKS_PER_SEC ) ), float( t ) / float( CLOCKS_PER_SEC ), t );
};
