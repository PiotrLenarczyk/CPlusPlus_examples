#include <cstdio>
#include <unistd.h>

int main( void )
{
	while(1)
	{
		printf( "\t...software execution...\n" );
		usleep( 1000 * 1000 ); //every 1000[ms] 
	};
	
	return 0;
};
