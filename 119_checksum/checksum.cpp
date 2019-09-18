#include <cstdio> 
using namespace std;


int seed;
#define RAND_A 1103515245		//glibc
#define	RAND_C 12345			//glibc
#define RAND_M 0x80000000		//glibc
void srand( int setSeed )
{	seed = setSeed;
};

int rand( void ) //linear congruential generator
{	return seed = ( (RAND_A * seed) + RAND_C ) % RAND_M;
};

int checksumAcc( void* xorIn ) //accumulated checksum; trivial LCG-based
{	seed ^= ( int )*( unsigned char* )xorIn;
	return seed = ( (RAND_A * seed) + RAND_C ) % RAND_M;
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	
	#define DATAS			0x4
	char arr[][DATAS] = 
	{	{ 0x11, 0x22, 0x33, 0x44 },
		{ 0x21, 0x22, 0x33, 0x44 },
	};
	puts( "====" );
	srand(0);
	for ( int i = 0x0; i < DATAS; i++ )
	{	printf( "rand()[%i]: 0x%08X\n", i, rand() );
	};
	
	puts( "====" );
	srand(0);
	for ( int i = 0x0; i < DATAS; i++ )
	{	printf( "arr[][0].cs[%i]: 0x%08X\n", i, checksumAcc( &arr[i][0] ) );
	};
	
	puts( "====" );
	srand(0);
	for ( int i = 0x0; i < DATAS; i++ )
	{	printf( "arr[][1].cs[%i]: 0x%08X\n", i, checksumAcc( &arr[i][1] ) );
	};

	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
