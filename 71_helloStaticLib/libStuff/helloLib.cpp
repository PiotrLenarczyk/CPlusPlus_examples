#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;
#define uint uint32_t

int helloLib( void )
{	printf( "Hello Libs World!\n" );	
	return 0;
};

int helloPrint( char* arrIn, uint sizeArrIn )
{	for ( uint i = 0; i < sizeArrIn; i++ )
		printf( "%c", arrIn[ i ] );
	printf( "\n" );
	return 0;
};

int helloPrint( string arrIn )
{	printf( "%s\n", arrIn.c_str() );
	return 0;
};
