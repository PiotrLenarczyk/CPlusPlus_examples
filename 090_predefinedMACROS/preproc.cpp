#include <iostream>
using namespace std;
typedef uint32_t uint;
uint i = 0;

void foo( void )
{	printf( "function name: [%s]\n", __FUNCTION__ );
	printf( "function type and name: [%s]\n", __PRETTY_FUNCTION__ );
	printf( "file name: [%s]\n", __FILE__ );
	printf( "line number: [%i]\n", __LINE__ );
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	foo();
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
