#ifndef __x86_64__
ERROR
#endif
//https://stackoverflow.com/questions/9887839/how-to-count-clock-cycles-with-rdtsc-in-gcc-x86
//http://www.mcs.anl.gov/~kazutomo/rdtsc.html
#include <stdio.h> 
using namespace std;
typedef unsigned char byte;
typedef __uint32_t uint;
uint i = 0x0;

#define CLOCKS_PER_SEC  ( __uint64_t )1000000
extern __inline__ __uint64_t time( void )
{   uint hi, lo;
    __asm__ __volatile__ ( "rdtsc" : "=a"( lo ), "=d"( hi ) );
    return ( ( __uint64_t )lo ) | ( ( ( __uint64_t )hi ) << 32 );
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	__uint64_t t = time();
	printf( "%lu\n", t );

	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
