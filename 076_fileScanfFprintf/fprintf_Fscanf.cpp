#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;
typedef uint32_t uint;
int i = 0;
int sysRet;
const uint N = 10;
const int cpSize = sizeof( float );
char cpBuf[ cpSize ];

void trivialStream( void );
void binaryStream( void );


int main( void )
{
	//trivialStream();
	//binaryStream();
	
	return 0;
};

void binaryStream( void )
{
	vector< float > vec( N );
	FILE *fileWritePtr; char fileName[] = "floatNorm.txt";
	fileWritePtr = fopen( fileName, "w" );
	for ( i = 0; i < N; i++ )
	{
		vec[ i ] = 0.1f + float( i );
		memcpy( &cpBuf[ 0 ], &vec[ i ], cpSize );
		fprintf( fileWritePtr, "data[%i]: %s\n", ( int )i, cpBuf );
	};
	vec.resize( 0 );
	fclose( fileWritePtr );
	string COM = "cat ";
	sysRet = system( COM.append( fileName ).c_str() ); if ( sysRet !=0 ) { fprintf( stderr, "\tERROR: System Command!\n" ); return; };
	
	FILE *fileReadPtr = fopen( fileName, "r" );
	vector< float > vecRead( N ); int j; int readRet = 0;
	for ( i = 0; i < N; i++ )	//lossy stream read
	{
		readRet = fscanf( fileReadPtr, "data[%i]: %s\n", &j, &cpBuf[ 0 ] );
		memcpy( &vecRead[ i ], &cpBuf, cpSize );
	};
	fclose( fileReadPtr );
	
	puts( "" );
	for ( i = 0; i < N; i++ )
		printf( "read from file (%s) data[%i]: %f\n", fileName, i, vecRead[ i ] );
};

void trivialStream( void )
{
	vector< float > vec( N );
	FILE *fileWritePtr; char fileName[] = "floatNorm.txt";
	fileWritePtr = fopen( fileName, "w" );
	for ( i = 0; i < N; i++ )		//it is lossy stream ( float looses precision ) - use memcpy char stream instead
	{
		vec[ i ] = 0.1f + float( i );
		fprintf( fileWritePtr, "data[%i]: %f\n", ( int )i, vec[ i ] );
	};
	vec.resize( 0 );
	fclose( fileWritePtr );
	string COM = "cat ";
	sysRet = system( COM.append( fileName ).c_str() ); if ( sysRet !=0 ) { fprintf( stderr, "\tERROR: System Command!\n" ); return; };
	
	FILE *fileReadPtr = fopen( fileName, "r" );
	vector< float > vecRead( N ); int j; int readRet = 0;
	for ( i = 0; i < N; i++ )	//lossy stream read
		readRet = fscanf( fileReadPtr, "data[%i]: %f\n", &j, &vecRead[ i ] );
	fclose( fileReadPtr );
	
	puts( "" );
	for ( i = 0; i < N; i++ )
		printf( "read from file (%s) data[%i]: %f\n", fileName, i, vecRead[ i ] );
};
