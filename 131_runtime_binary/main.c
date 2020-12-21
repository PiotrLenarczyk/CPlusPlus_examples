//input source file

#include <stdio.h>
#include <string.h>

void foo( int* );

int global_var[3];
int main( int argc, char* argv[] )
{	memset( global_var, 0x0, sizeof(global_var) );
	global_var[1] = 0x44332211;
	foo( &global_var[1] );
	
	return 0;
};

void foo( int *in )
{	printf( "%s() input : 0x%08X\n", __FUNCTION__, *in );
};
