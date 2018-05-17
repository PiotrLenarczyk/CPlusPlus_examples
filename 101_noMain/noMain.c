


void _start()
{	exit( foo() );
};


//http://dbp-consulting.com/tutorials/debugging/linuxProgramStartup.html
//https://www.quora.com/Can-a-program-be-compiled-without-a-main
#include <stdlib.h>
#include <stdio.h> 
typedef unsigned char byte;
typedef __uint32_t uint;
uint i = 0x0;

void foo( void )
{	printf( "foo()\n" );
};//foo()

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	printf( "main()\n" );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
