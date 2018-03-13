#include <iostream>
using namespace std;
typedef uint32_t uint;
uint i = 0;

void foo( void )
{	char* arrPtr = "someTestText";
	printf( "arrPtr : %s\n", arrPtr );
	printf( "&arrPtr : %p\n", &arrPtr );
	printf( "sizeof(arrPtr) : %lu\n", sizeof( arrPtr ) );
	char arr[] = "someTestText";
	printf( "arr : %s\n", arr );
	printf( "&arr : %p\n", &arr );
	printf( "sizeof(arr) : %lu\n", sizeof( arr ) );
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	foo();
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
