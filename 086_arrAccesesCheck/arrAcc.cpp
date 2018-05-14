#include <time.h>
#include <iostream>
#include <array>
using namespace std;
typedef uint32_t uint;
uint i = 0, t = 0;
#define mltFact  0.05
const uint N = mltFact * 1024 * 1024 * 1024;	  
const uint X = 6;						//try other values
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
	printT( "static arr1D", clock() - t );
//======================================================================
	volatile float vTmp = 1.1f;
	t = clock();
	for ( i = 0; i < N; i++ )
		arr1D[ i ] = vTmp;
	t = clock() - t;
	printT( "static arr1D+=volatile", clock() - t );
//======================================================================
	const float cTmp = 1.1f;
	t = clock();
	for ( i = 0; i < N; i++ )
		arr1D[ i ] = cTmp;
	t = clock() - t;
	printT( "static arr1D+=const", clock() - t );
//======================================================================
	float arr2D[ Y ][ X ];
	t = clock();
	for ( uint y = 0; y < Y; y++ )
		for ( uint x = 0; x < X; x++ )
			arr2D[ y ][ x ] = tmp;
	printT( "static arr2D", clock() - t );
//======================================================================
	float* dynArr1D = ( float* )malloc( N * sizeof( float ) ); 
	if ( dynArr1D == nullptr ) return -1;
	t = clock();
	for ( i = 0; i < N; i++ )
		arr1D[ i ] = tmp;
	printT( "heap/dynamic arr1D", clock() - t );
//======================================================================
	t = clock();
	for ( i = 0; i < N; i++ )
		arr1D[ i ] = vTmp;
	t = clock() - t;
	printT( "heap/dynamic arr1D+=volatile", clock() - t );
//======================================================================
	t = clock();
	for ( i = 0; i < N; i++ )
		arr1D[ i ] = cTmp;
	t = clock() - t;
	printT( "heap/dynamic arr1D+=const", clock() - t );
	delete( dynArr1D );
//======================================================================
//"https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/"
//		2D arrays - pointer to pointer 			
	float** dynArr2D = ( float** )malloc( Y * sizeof( float* ) );
	if ( dynArr2D == nullptr ) return -1;
	for ( uint y = 0; y < Y; y++ )
		dynArr2D[ y ] = ( float* )malloc( X * sizeof( float ) );
	t = clock();
	for ( uint y = 0; y < Y; y++ )
		for ( uint x = 0; x < X; x++ )
			arr2D[ y ][ x ] = tmp;
	printT( "heap/dynamic arr2D", clock() - t );
	for ( uint y = 0; y < Y; y++ )	
		delete( dynArr2D[ y ] );
	delete( dynArr2D );
//======================================================================
	array< float, N > arrCont;
	t = clock();
	for ( i = 0; i < N; i++ )
		arrCont[ i ] = tmp;
	printT( "container arrCont", clock() - t );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void printT( const char *name, uint t )
{	if ( t < 1000 ){ printf( "\tERROR: [%s]\n", name ); return; };
	printf( "%s[%u] : %02f[GBps]; %02f[s]; %i periods\n", name, N, ( float( mltFact ) * 4.0f ) / ( float( t ) / float( CLOCKS_PER_SEC ) ), float( t ) / float( CLOCKS_PER_SEC ), t );
};
