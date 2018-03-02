#include <iostream>
using namespace std;
typedef uint32_t uint;
uint i = 0;



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	
	const uint X = 32, Y = 3;
	float arr1D[ X * Y ];
	printf( "sizeof( arr1D ): %li\n", sizeof( arr1D ) );
	float arr2D[ Y ][ X ];
	printf( "sizeof( arr2D ): %li\n", sizeof( arr2D ) );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
