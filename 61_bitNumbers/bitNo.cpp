#include <iostream>

using namespace std;
typedef uint32_t uint;
size_t i = 0;

void printBits(size_t const size, void const * const ptr)
{
	printf( "tmpVal = %#08x \n", * ( uint* )ptr );
	
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf( " %u ", byte );
        }
    }
    puts("");
    for( int ind  = 31; ind > 9; ind-- )
		printf( "%d ", ind );
    for( int ind  = 9; ind > -1; ind-- )
		printf( " %d ", ind );		
    puts(""); puts("");
}

int main( void )
{
	uint a = 15;
	printBits( sizeof( a ), &a );

	return 0;
}
