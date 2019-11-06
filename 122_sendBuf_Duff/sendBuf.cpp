//https://www.quora.com/What-are-some-examples-of-extremely-clever-problem-solving-in-the-software-development-world
//https://swtch.com/duffs-device/td-1983.txt
#include <cstdio> 
using namespace std;

void send4B_Duff(int *dstPtr, int *srcPtr, int wordCount)
{	static int n;
	n = (wordCount + 7) >> 0x3; //div by 8
	switch (wordCount % 8) 
	{	case 0: *dstPtr = *srcPtr++;
				printf( "rest: 0x%08X\n", *dstPtr );
		case 7: *dstPtr = *srcPtr++;
				printf( "rest: 0x%08X\n", *dstPtr );
		case 6: *dstPtr = *srcPtr++;
				printf( "rest: 0x%08X\n", *dstPtr );
		case 5: *dstPtr = *srcPtr++;
				printf( "rest: 0x%08X\n", *dstPtr );
		case 4: *dstPtr = *srcPtr++;
				printf( "rest: 0x%08X\n", *dstPtr );
		case 3: *dstPtr = *srcPtr++;
				printf( "rest: 0x%08X\n", *dstPtr );
		case 2: *dstPtr = *srcPtr++;
				printf( "rest: 0x%08X\n", *dstPtr );
		case 1: *dstPtr = *srcPtr++;
				printf( "rest: 0x%08X\n", *dstPtr );
	};
	puts( "unrolled:" );
	while (--n > 0) 
	{	*dstPtr = *srcPtr++;
			printf( "0x%08X\n", *dstPtr );
		*dstPtr = *srcPtr++;
			printf( "0x%08X\n", *dstPtr );
		*dstPtr = *srcPtr++;
			printf( "0x%08X\n", *dstPtr );
		*dstPtr = *srcPtr++;
			printf( "0x%08X\n", *dstPtr );
		*dstPtr = *srcPtr++;
			printf( "0x%08X\n", *dstPtr );
		*dstPtr = *srcPtr++;
			printf( "0x%08X\n", *dstPtr );
		*dstPtr = *srcPtr++;
			printf( "0x%08X\n", *dstPtr );
		*dstPtr = *srcPtr++;
			printf( "0x%08X\n", *dstPtr );
	};
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	
	#define ARR_SIZE	0x30
	unsigned char arr[ ARR_SIZE ]; for ( int i = 0x0; i < ARR_SIZE; i++ )	arr[ i ] = i;
	int buf;
	puts( "data send to device buffer:" );
	send4B_Duff( &buf, (int*)arr, 0x9 ); //send 36B with 4B wordsize to device "buf"
	
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
