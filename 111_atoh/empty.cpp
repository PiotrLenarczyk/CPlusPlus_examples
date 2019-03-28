//https://www.microchip.com/forums/m183323.aspx
#include <cstdio> 
#define CAST( destPtr ) ( destPtr )( const void* )
using namespace std;
typedef __uint32_t uint;
typedef unsigned char byte;
uint i = 0x0;

unsigned char atoh( unsigned char c )
{	if ( c > '9' )
		return ((c + 9) & 0x0F);
	return 0x0;
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	printf( "atoh(%c): 0x%1X\n", 'A', atoh( 'A' ) );
	printf( "atoh(%c): 0x%1X\n", 'a', atoh( 'a' ) );
	printf( "atoh(%c): 0x%1X\n", 'G', atoh( 'G' ) );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
