#include <stdio.h>
/*include <stdlib.h>*/

typedef unsigned int uint;

int main ( void )
{
	char a[] = { "Hello" };
	printf( "%s\n",a );
	printf( "a.length(): %u\n", ( uint )strlen( a ) );
	printf( "sizeof( a ): %u\n", sizeof( a ) );

	return 0;
}

