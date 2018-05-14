#include <stdio.h>
#include <stdlib.h>
#define unsigned uint
uint i = 0;

void foo( void )
{	char tmp = 'a';
	char* tmpPtr = &tmp;
	printf( "sizeof(tmp) : %lu\n", sizeof( tmp ) );
	printf( "sizeof(tmpPtr) : %lu\n", sizeof( tmpPtr ) );
//======================================================================
	char* arrPtr = "someTestSampleText";
	printf( "arrPtr : %s\n", arrPtr );
	printf( "&arrPtr : %p\n", &arrPtr );
	printf( "sizeof(arrPtr) : %lu\n", sizeof( arrPtr ) );
	char arr[] = "someTestSampleText";
	printf( "arr : %s\n", arr );
	printf( "&arr : %p\n", &arr );
	printf( "sizeof(arr) : %lu\n", sizeof( arr ) );
//======================================================================
	uint X = 0x400;
	uint Y = 0x2;
	char** arr2DYX = ( char** )malloc( Y * sizeof( char* ) );
		i = 0; while ( i < Y )
		{	arr2DYX[ i ] = ( char* )malloc( X * sizeof( char ) );
			i++;
		};
			printf( "trivial sizeof( arr2DYX ) : %lu\n", sizeof( arr2DYX ) );
			printf( "proper sizeof( arr2DYX ) : %lu\n", 
						( Y * sizeof( char* ) ) * ( X * sizeof( char ) ) );
		i = 0; while ( i < Y )
		{	delete( arr2DYX[ i ] );
			i++;
		};
	delete( arr2DYX );
//======================================================================	
	X = 0x2;
	Y = 0x400;
	char** arr2DXY = ( char** )malloc( X * sizeof( char* ) );
		i = 0; while ( i < X )
		{	arr2DXY[ i ] = ( char* )malloc( Y * sizeof( char ) );
			i++;
		};
			printf( "trivial sizeof( arr2DXY ) : %lu\n", sizeof( arr2DXY ) );
			printf( "proper sizeof( arr2DXY ) : %lu\n", 
						( Y * sizeof( char ) ) * ( X * sizeof( char* ) ) );
		i = 0; while ( i < X )
		{	delete( arr2DXY[ i ] );
			i++;
		};
	delete( arr2DXY );
//======================================================================	
	X = 0x400;
	Y = 0x2;
	uint x, y;
	char* arr1DYX = ( char* )calloc( Y * X, sizeof( char ) );
		printf( "trivial sizeof( arr1DYX ) : %lu\n", sizeof( arr1DYX ) );
		printf( "proper sizeof( arr1DYX ) : %lu\n", 
					( Y *  X * sizeof( char ) ) );
		printf( "arr1DYX[ 0x402 ] : %i\n", arr1DYX[ 0x402 ] );
//		set arr1DYX[ 1 ][ 2 ] via MACRO to 0x1
#define CHAR_ARRYX( arr, y, x, X ) arr[ ( y * X ) + x ]
		y = 1, x = 2;
		CHAR_ARRYX( arr1DYX, y, x, X ) = 0x1;
		printf( "MACRO arr1DYX[ 1 ][ 2 ]/arr1DYX[ 0x402 ] : %i\n", arr1DYX[ 0x402 ] );
//		set arr1DYX[ 1 ][ 2 ] via address arithmetic to 0x2
		y = 1; x= 2;
		arr1DYX[ ( y * X ) + x ] = 0x2;
		printf( "address arithmetic arr1DYX[ 1 ][ 2 ]/arr1DYX[ 0x402 ] : %i\n", 
					arr1DYX[ 0x402 ] );
	delete( arr1DYX );
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	foo();
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Post Scriptum: please do make your programs optimized for information density. It could be achieved via:
//	-cut all data to indispensible part,
//	-preprocessing of redundant calculations, and saving results into Look Up Tables ( LUT ),
//	-lossy( stronger & non-reversible ) compression / lossless compression,
//	-data normalization,
//	-only processing of most influential frequency coefficients in frequency domain ( wavelets/DWT, real spectrum/DCT, etc. ),
//	-statistic analysis ( Principial Component Analysis ).
//Another optimization of data locality, which could be achieved via:
//	-avoiding costly input-output ( read/write operaiotn ) to: HDD's, network stuff, cout/cin, monitors, 
//								( including PCIe transfers to GPU for too small problems ),
//	-proper usage of datatypes ( fastest implementations tends to arrays ),
//	-in many-core parallelism scheme provide coalesced access for cache utilization,
//	-proper usage of hardware ( motherboard hardware driver buses ),
//	-avoiding volatile and const qualifiers.
//Post Post Scriptum: please note that, efficient-optimal program could not be safe.
