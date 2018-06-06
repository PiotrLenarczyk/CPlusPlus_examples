//https://www.cs.colorado.edu/~srirams/courses/csci2824-spr14/gmpTutorial.html
#include <gmp.h>
#include <cstdio> 
#define STRINGIZE( x ) #x
#define CAST( destPtr ) ( destPtr )( const void* )
using namespace std;
typedef __uint32_t uint;
typedef mpz_t uMem;
typedef unsigned char byte;

//----------------------------------------------------------------------
mpz_t bigInt;
#define FREE {  mpz_clear( bigInt ); \
			 }
//----------------------------------------------------------------------
#define HEX 16
#define DEC 10
#define INIT { 	mpz_init( bigInt ); \
				mpz_set_ui( bigInt, 0 ); }
#define ERR( input ) { 	printf( "==== ERROR!\n\tl[%i]: [%s]->[%s]\n====\n", __LINE__, __FUNCTION__, input ); \
						FREE }
#define TRY( input, inResult ) { if ( input != inResult ) ERR( STRINGIZE( input ) ) }
#define printHEX( var ) { printf ( STRINGIZE( var )" = 0x"); mpz_out_str( stdout, HEX, var ); puts(""); }
#define printDEC( var ) { printf ( STRINGIZE( var )" = "); mpz_out_str( stdout, DEC, var ); puts(""); }
#define PLUS( IN, num ) mpz_add_ui( IN, IN, num );
#define ADD( OUT, IN_1, IN_2 ) mpz_add( OUT, IN_1, IN_2 );


void foo( const char* in )
{	INIT;
		TRY ( mpz_set_str( bigInt, in, HEX ), 0 );
		printHEX( bigInt );
		PLUS( bigInt, 1 );
		printHEX( bigInt );
	FREE;
};//foo()

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	foo( "100" );
//----------------------------------------------------------------------
#	define N 2
#	define FOR( noElems ) for ( uint i = 0; i < noElems; i++ ) 
#	define FOR_printDEC( var, noElems ) { for ( uint i = 0; i < noElems; i++ ) { printf ( STRINGIZE( var )"[%u] = ", i ); mpz_out_str( stdout, DEC, var[ i ] ); puts(""); }; }
//----------------------------------------------------------------------
	mpz_t bigArr[ N ];
	FOR( N ) {	mpz_init( bigArr[ i ] ); mpz_set_ui( bigArr[ i ], 1 );	};
		PLUS( bigArr[ 1 ], 14 );
		ADD( bigArr[ 0 ], bigArr[ 0 ], bigArr[ 1 ] ); 
		FOR_printDEC( bigArr, N );
	FOR( N ) mpz_clear( bigArr[ i ] );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
