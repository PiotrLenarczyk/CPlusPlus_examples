#include <iostream>

using namespace std;
typedef uint32_t uint;
size_t i = 0;

void printBits( const void * const ptr, size_t const size );
int compareValsBits( const void * ptrA, size_t sizeA, const void * ptrB, size_t sizeB );


int main( void )
{
	uint a = 15;
	uint b = 16;

	printBits( &a, sizeof( a ) );

	printBits( &b, sizeof( b ) );
	
	compareValsBits( &a, sizeof( a ), &b, sizeof( b ) );
	return 0;
}


void printBits( void const * const ptr, size_t const size )
{
	printf( "hexVal = %#08x; decVal = %i \n", * ( uint* )ptr, * ( uint* )ptr );
	
    unsigned char *b = ( unsigned char* ) ptr;
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
};

int compareValsBits( const void * ptrA, size_t sizeA, const void * ptrB, size_t sizeB )
{
	if ( sizeA != sizeB )
		return -1;
	printf( "comparing: \n[%#08x](%i)\n[%#08x](%i)\n====\n", * ( uint* )ptrA, * ( uint* )ptrA, * ( uint* )ptrB, * ( uint* )ptrB );
	
	
    unsigned char *a = ( unsigned char* ) ptrA;
    unsigned char *b = ( unsigned char* ) ptrB;
    unsigned char byteA, byteB;
    int i, j;

    for (i=sizeA-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byteA = (a[i] >> j) & 1;
            printf( " %u ", byteA );
        }
    }
    puts("");
    for (i=sizeA-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byteB = (b[i] >> j) & 1;
            printf( " %u ", byteB );
        }
    }
    puts("");
    for( int ind  = 31; ind > 9; ind-- )
		printf( "%d ", ind );
    for( int ind  = 9; ind > -1; ind-- )
		printf( " %d ", ind );		
    puts(""); 
    
    for (i=sizeA-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
	        byteA = (a[i] >> j) & 1;
            byteB = (b[i] >> j) & 1;
            if ( byteA == byteB )
            	printf( "   " );
            else
            	printf( " x " );
        }
    }
    
    printf( "\n====\n" );
};
