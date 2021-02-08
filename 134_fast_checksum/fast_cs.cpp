#include <cstdio> 
using namespace std;

/* Function randomizes array checksum due to size, and input values.
 * Fast implementation is based on register depth, could be trivially
 * parallelized to similar design. Basically it is LCG-VMPC derivate.
 */
#define CS_RAND_A (unsigned long long)(0x8d316e46ee0680b8)	//rand()
#define	CS_RAND_C (unsigned long long)(0xc505b0796c4532bd)	//rand()
unsigned long long cs( 	register unsigned char *in,
						unsigned long long size ) 
{	unsigned long long cs_acc;
	long long cs_count8B, cs_count1B;
	cs_count8B = (long long)size >> 0x3;
	cs_count1B = (long long)size - (cs_count8B << 0x3);
	cs_acc = 0x58bd0e27df67ac8c * size;	//rand()'ed size init

	//8B checksum
	while( cs_count8B-- )
	{	cs_acc ^= (CS_RAND_A * 
				*(unsigned long long*)in) + CS_RAND_C;
		cs_acc += (unsigned long long)*(unsigned char*)in + 1;
		in += sizeof(unsigned long long);
	};
	
	//few bytes checksum
	while( cs_count1B-- )
	{	cs_acc ^= (CS_RAND_A * 
				(unsigned long long)*(unsigned char*)in) + CS_RAND_C;
		cs_acc += (unsigned long long)*(unsigned char*)in + 1;
		in++;
	};
	
	return cs_acc;
};//cs()

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	
	unsigned char arr1[] = {0};	
	printf( "arr1.cs : 0x%016llX\n", 
		cs((unsigned char*)arr1, sizeof(arr1)) );
	
	unsigned char arr2[] = {0, 0};	
	printf( "arr2.cs : 0x%016llX\n", 
		cs((unsigned char*)arr2, sizeof(arr2)) );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
