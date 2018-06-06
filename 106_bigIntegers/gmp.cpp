//https://www.cs.colorado.edu/~srirams/courses/csci2824-spr14/gmpTutorial.html
#include <gmp.h>
#include <cstdio> 
#define CAST( destPtr ) ( destPtr )( const void* )
using namespace std;
typedef __uint32_t uint;
typedef mpz_t uMem;
typedef unsigned char byte;
uint i = 0x0;

mpz_t bigInt;
#define ERR { 	printf( "====\n\tERROR!\n\t[%s] line no:[%i]\n====", __FUNCTION__, __LINE__ ); \
				mpz_clear( bigInt ); }
#define HEX 16
#define DEC 10

void foo( void )
{	mpz_init( bigInt );
	mpz_set_ui( bigInt, 0 );
	
	if ( mpz_set_str( bigInt, "10", HEX ) != 0 ) ERR
	printf ("n = 0x"); mpz_out_str( stdout, HEX, bigInt ); puts("");
	
	mpz_clear( bigInt );
};//foo()

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	foo();
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
