#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;
typedef uint32_t uint;
size_t i = 0;
int sysRet;
const uint N = 10;

int main( void )
{
	vector< float > vec( N, 0.10000001f );
	FILE *fileWritePtr; char fileName[] = "floatNorm.txt";
	fileWritePtr = fopen( fileName, "w" );
	for ( ; i < N; i++ )		//it is lossy stream ( float looses precision ) - use memcpy char stream instead
		fprintf( fileWritePtr, "data[%i]: %f\n", ( int )i, vec[ i ] );
	vec.resize( 0 );
	fclose( fileWritePtr );
	string COM = "cat ";
	sysRet = system( COM.append( fileName ).c_str() ); if ( sysRet !=0 ) { fprintf( stderr, "\tERROR: System Command!\n" ); return -1; };
	
	FILE *fileReadPtr = fopen( fileName, "r" );
	vector< float > vecRead( N ); int j = 0;
	//for ( i = 0; i < N; i++ )		//lossy float read
		fscanf( fileReadPtr, "data[%i]: %f\n", j, vecRead[ i ] );
	fclose( fileReadPtr );
	
	puts( "" );
	for ( i = 0; i < N; i++ )		//lossy float read
		printf( "read from file (%s) data[%i]: %f\n", fileName, j, vecRead[ j ] );
	
	return 0;
};
