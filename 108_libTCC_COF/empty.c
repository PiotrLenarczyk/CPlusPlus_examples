//https://blog.mister-muffin.de/2011/10/22/discovering-tcc/
//#include "tcclib.h"
#include <stdlib.h>
#include <stdio.h>
#include "libtcc.h"
#include <unistd.h>	//sleep
#include <time.h> //program timeout
#include <signal.h>	//break program signal handle
int ret; //system commands return value
void exitHandler( int signalIn )
{	printf( "\nProgram terminated.\n" );
	exit( EXIT_SUCCESS );
};

//char* my_prog =
	//#include "externProg.c"	//externProg.c : /y7/R"( /*program body here*/ )"
//;
void foo( void )
{	printf( "foo call\n" );
};

#define PROG_SIZE 0x20000 //128kiB source code limit
char cstArr[ PROG_SIZE ];
void switchPtrs( char* progArr )
{	char* in = progArr, *cstPtr = cstArr;
	while( *in != 0 )
		*cstPtr++ = *in++;
	*cstPtr = 0x0;
};

int previousFileChecksum;
int readFile( char *fileName ) 
{   char *code;
	int c = 0x0, n = 0x0, currentChecksum = 0x0;
	long f_size = 0x0;
	FILE *file = fopen( fileName, "r" );
		if ( file == NULL ) { printf( "====\n\tCould not open file!\n====\n" ); return 0x0; }
		fseek( file, 0, SEEK_END );
		f_size = ftell( file );
		if ( f_size > ( long )PROG_SIZE ){ printf( "====\n\tFile too big!\n====\n" ); return 0x0; }
		fseek( file, 0, SEEK_SET );
		code = malloc( f_size );
			while (( c = fgetc( file )) != EOF )
			{	code[ n++ ] = ( char )c;
				currentChecksum += c;
			};
			code[ n ] = '\0';
			switchPtrs( code );
		free( code );
    fclose( file );
	return currentChecksum;
};

clock_t t; //timeout marker
void cof( void ); //compilation-on-the-fly
//======================================================================
//======================================================================
int main(int argc, char **argv)
{	if ( argc == 1 ){ printf( "No source file provided!\n" ); return 0; }
	t = clock(); signal( SIGINT, exitHandler );
	while( 1 )
	{	if ( previousFileChecksum != readFile( argv[ argc - 1 ] ) )
		{	ret = system( "clear" );
			cof();
			previousFileChecksum = readFile( argv[ argc - 1 ] );
		};
		if ( ((float)( clock() - t ) / CLOCKS_PER_SEC ) > ( 30.0f * 60.0f ) ) //30 minutes timeout
		{	ret = system( "clear" );
			printf( "====\nProgram timeouted!\n====\n" );
			break;
		};
	};
	return 0;
};
//======================================================================
//======================================================================
void cof( void )
{	int ( *foobar_func )( int );
	void *mem;
	TCCState *s;
	s = tcc_new();
	tcc_set_output_type( s, TCC_OUTPUT_MEMORY );
	if ( tcc_compile_string( s, cstArr ) == -1 )	//try compilation of provided source code
	{	tcc_delete( s );	//source is not correct
		sleep( 1 );
		return;
	};
	tcc_add_symbol( s, "foo", foo );
	mem = malloc( tcc_relocate( s, NULL ) );
	tcc_relocate(s, mem);
	foobar_func = tcc_get_symbol( s, "main" );
	tcc_delete( s );
	printf( "External prog returned: %d\n", foobar_func( 32 ) );
	free( mem );
};
