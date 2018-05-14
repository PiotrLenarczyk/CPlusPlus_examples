/*
https://stackoverflow.com/questions/2741683/how-to-format-a-function-pointer
 */
#include <iostream>
using namespace std;
typedef uint32_t uint;
uint i = 0;

void foo( void )
{
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	unsigned char *p = ( unsigned char * )&foo;
	printf( "&foo = " );
	for ( i = 0; i < sizeof &foo; i++ )
        printf("%02x", p[i]);
        
    p = ( unsigned char * )&main;
	printf( "\n&main = " );
	for ( i = 0; i < sizeof &main; i++ )
        printf("%02x", p[i]);        
	
	return puts( "" );
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
