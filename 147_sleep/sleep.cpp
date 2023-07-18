#include <cstdio> 
#include <cstdlib>
#include <ctime>

//#define VERBOSE

#define RAND_A 1103515245		//glibc
#define	RAND_C 12345			//glibc
#define RAND_M 0x80000000		//glibc
int checksumSeed;
static inline
int checksumArr( unsigned char *arrPtr, int size )
{
    checksumSeed = *arrPtr++;
    while( size-- )
    {
        checksumSeed ^= *arrPtr++;
        checksumSeed = ( (RAND_A * checksumSeed) + RAND_C ) % RAND_M;
    };
    return checksumSeed;
};

void sleep( int wait_ms )
{
	float wait_s, t, ticps;
	clock_t t1;
	ticps = float(CLOCKS_PER_SEC);
	wait_s = (float)wait_ms / 1000.0f;
	t1 = clock();
	t = (float)(clock() - t1) / ticps;
	while ( wait_s > t )
	{
		t = (float)(clock() - t1) / ticps;
	};
	printf( "sleep() : %f[s]\n", (double)t );

};


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( int argc, char *argv[] )
{	sleep( (int)strtoul(argv[1], NULL, 0) );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
