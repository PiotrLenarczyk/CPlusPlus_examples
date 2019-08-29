//http://www.cplusplus.com/reference/cstring/memmove/
#include <cstdio> 
#define CAST( destPtr ) ( destPtr )( const void* )
using namespace std;
typedef __uint32_t uint;
typedef unsigned char byte;
uint i = 0x0;

#define MEMMOVE_BUFSIZE	0x10
unsigned int 	*memPtr_iSrc, *memPtr_iDst, 
				mem_noInts, mem_valueInt;
unsigned char 	*memPtr_cSrc, *memPtr_cDst, *memPtr_buf, 
				mem_buf[ MEMMOVE_BUFSIZE ];
#define memPtr_i1	memPtr_iDst
#define memPtr_i2	memPtr_iSrc
#define memPtr_c1	memPtr_cDst
#define memPtr_c2	memPtr_cSrc
#define mem_i		mem_valueInt
int memcmp( void *ptr1, void *ptr2, unsigned int num )
{	memPtr_i1 = (unsigned int*)ptr1;
	memPtr_i2 = (unsigned int*)ptr2;
	mem_noInts = num >> 2; //divide by 4
	while (mem_noInts > 0)
	{	if (*memPtr_i1 != *memPtr_i2)
		{	memPtr_c1 = (unsigned char *)memPtr_i1;
			memPtr_c2 = (unsigned char *)memPtr_i2;
			for ( mem_i = 0x0; mem_i < sizeof( int ); mem_i++ )
			{	if ( *(memPtr_c1 + mem_i) != *(memPtr_c2 + mem_i) )
					return ( (int)*(memPtr_c1 + mem_i) - (int)*(memPtr_c2 + mem_i) );
			};
		};
		mem_noInts--;
		memPtr_i1++;
		memPtr_i2++;
	};
	mem_noInts = num >> 2; //divide by 4
	num -= mem_noInts << 0x2; //reduce num of int number
	if ( mem_noInts > 0x1 ) //if (mem_noInts > 1)
	{	--memPtr_i1;
		--memPtr_i2;
	};
	//byte comparision of unaligned rest
	memPtr_c1 = (unsigned char *)memPtr_i1;
	memPtr_c2 = (unsigned char *)memPtr_i2;
	while (num > 0)
	{	if (*memPtr_c1 != *memPtr_c2)
			return (*memPtr_c1 - *memPtr_c2);
		num--;
		memPtr_c1++;
		memPtr_c2++;
	};
	return 0;
};

#define CHARACTER_MASK	0xFFFFFF00
void* memset( void *ptr, int value, unsigned int num )
{	memPtr_i1 = (unsigned int*)ptr;
	mem_noInts = num >> 0x2;
	//====(value &= 0xFF) || (value &= 0xFFFFFFFF)====
	if ( (value & CHARACTER_MASK) == 0x0 ) //set int size with character
	{	mem_valueInt  = (unsigned int)value << 0x00;
		mem_valueInt |= (unsigned int)value << 0x08;
		mem_valueInt |= (unsigned int)value << 0x10;
		mem_valueInt |= (unsigned int)value << 0x18;
	};
	while( mem_noInts-- )
		*memPtr_i1++ = mem_valueInt;
	mem_noInts = num >> 0x2;
	num -= mem_noInts << 0x2;	//reduce num of ints size number
	if ( mem_noInts > 0x1 ) 	//if (mem_noInts > 1)
		memPtr_i1--;
	//byte memory set with value of unaligned rest
	memPtr_c1 = (unsigned char *)memPtr_i1;
	while( num-- )
		*memPtr_c1++ = (unsigned char)value;
	return ptr;
};

void* memcpy( void *destinationPtr, void *sourcePtr, unsigned int num )
{	memPtr_iDst = (unsigned int *)destinationPtr;
	memPtr_iSrc = (unsigned int *)sourcePtr;
	mem_noInts = num >> 0x2; //divide by 4
	while( mem_noInts-- )
		*memPtr_iDst++ = *memPtr_iSrc++;
	mem_noInts = num >> 0x2;
	num -= mem_noInts << 0x2;	//reduce num of ints size number
	if ( mem_noInts > 0x1 ) 	//if (mem_noInts > 1)
	{	memPtr_iDst--;
		memPtr_iSrc--;
	};
	//byte memory move
	memPtr_cSrc = (unsigned char *)memPtr_iSrc;
	memPtr_cDst = (unsigned char *)memPtr_iDst;
	while( num-- )
		*memPtr_cDst++ = *memPtr_cSrc++;
	return destinationPtr;
};

//=======================================================================================
void* memmove( void *destinationPtr, void *sourcePtr, unsigned int num )
{	if ( num > MEMMOVE_BUFSIZE )	//num<MEMMOVE_BUFSIZE
		return (void*)-1;
	memPtr_buf = mem_buf;
	memPtr_cSrc = (unsigned char *)sourcePtr;
	memPtr_iDst = (unsigned int *)destinationPtr;
	memPtr_iSrc = (unsigned int *)sourcePtr;
	mem_noInts = num;
	//get data into memmove buffer
	while( mem_noInts-- )
		*memPtr_buf++ = *memPtr_cSrc++;
	//copuy into dst from buffer via intPtr
	memPtr_iSrc = (unsigned int *)mem_buf;
	mem_noInts = num >> 0x2; //divide by 4
	while( mem_noInts-- )
		*memPtr_iDst++ = *memPtr_iSrc++;
	mem_noInts = num >> 0x2;
	num -= mem_noInts << 0x2;	//reduce num of ints size number
	if ( (num >> 0x2) > 0x1 ) 	//if (mem_noInts > 1)
	{	memPtr_iDst--;
		memPtr_iSrc--;
	};
	//byte memory move
	memPtr_cSrc = (unsigned char *)memPtr_iSrc;
	memPtr_cDst = (unsigned char *)memPtr_iDst;
	while( num-- )
		*memPtr_cDst++ = *memPtr_cSrc++;
	return destinationPtr;
};

//=======================================================================================
void* memchr( void *ptr, int value, unsigned int num )
{	memPtr_cSrc = (unsigned char *)ptr;
	mem_noInts = num;
	mem_i = 0x0;
	while( (mem_noInts--) && (*memPtr_cSrc++ != (unsigned char)value) )
		mem_i++;
	if ( mem_i == num )
		return 0x0;
	return (void*)--memPtr_cSrc;
};

#define ALIGN_ADDR( addr, alignment )				\
			addr += alignment - (addr % alignment);	\
				
void foo( void )
{	
	char * pch;
	char str4[] = "Example string";
	pch = (char*) memchr (str4, 'p', sizeof(str4));
	if (pch!=NULL)
		printf ("'p' found at position %d.\n", (int)(pch-str4+1));
	else
		printf ("'p' not found.\n");
	
	char str3[] = "memmove can be very useful......";
	memmove (str3+20,str3+15,11);
	puts (str3);

	char str2[ 0x40 ]; memset( str2, 0x0, 0x40 );
	char str1[] = "memcpy 0x1234567";
	memcpy(str2,str1,11);
	puts (str2);

	char str[] = "almost every programmer should know memset!";
	memset (str,'-',6);
	puts (str);

	char buffer1[] = "DWgaOtP12df0";
	char buffer2[] = "DWGAOTP12DF0";
	int n;
	n=memcmp ( buffer1, buffer2, sizeof(buffer1) );
	if (n>0) printf ("'%s' is greater than '%s'.\n",buffer1,buffer2);
	else if (n<0) printf ("'%s' is less than '%s'.\n",buffer1,buffer2);
	else printf ("'%s' is the same as '%s'.\n",buffer1,buffer2);
	
	int addr = 0x7;
	ALIGN_ADDR( addr, 0x4 );
	printf( "addr : %d\n", addr );
	
	addr = 0x3;
	ALIGN_ADDR( addr, 0x4 );
	printf( "addr : %d\n", addr );
};//foo()

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	
	foo();
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
