#include <cstdio> 
using namespace std;

typedef unsigned char 		u8;
typedef unsigned int		u32;

//======================================================================
#define RANGES1_NO( arr )	(sizeof(arr) / sizeof(arr[0])) 
#define get_range1No(val, arrPtr)	_get_range1No(val, arrPtr, RANGES1_NO(arrPtr))
u32 _get_range1No( u32 val, u32* arrPtr, u32 rangesNo )
{	u32 no, i; no = i = 0x0;
	for ( ; i < (rangesNo - 1); i++ )
		no |= 	((val >= arrPtr[i]) && 
				 (val < (arrPtr[i + 1]))) * i;
	no |= (val >= arrPtr[i]) * i; //last open range
	return no;
};
//======================================================================
#define RANGES2_NO( arr )		((sizeof(arr) / sizeof(arr[0])) >> 0x1)
#define get_range2No(val, arrPtr)	_get_range2No(val, arrPtr, RANGES2_NO(arrPtr))
u32 _get_range2No( u32 val, u32* arrPtr, u32 rangesNo )
{	u32 no, i; no = i = 0x0;
	for ( ; i < (rangesNo << 0x1); i += 0x2 )
		no |= 	((val >= arrPtr[ i ]) && 
				 (val <= arrPtr[ i + 1 ])) * i;
	no >>= 0x1;
	return no;
};
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
u32 ranges1[] = 	//range start values only - continuous area
{	0x00000000,// up to 0x00000FFF
	0x00001000,// up to 0x00004FFF
	0x00005000,// up to 0x0000FFFF
	0x00010000,// up to 0xFFFFFFFF
};

u32 ranges2[] = 	//allowed values within split area
{	0x00000000, 0x00000FFF,
	0x00001000, 0x00002FFF, //gap 0x00003000 - 0x00004FFF
	0x00005000, 0x0000FFFF,
	0x00010000, 0x0002FFFF,
};

int main( void )
{	
	u32 val; val = 0x2000;
	printf( "%d\n", get_range1No( val, ranges1 ) );
	printf( "%d\n", get_range2No( val, ranges2 ) );
				
	switch( get_range2No( val, ranges2) )
	{	default:
			puts( "all other cases" );
			break;
		case 0x0:
			puts( "range 0x0 procedure" );
			break;
		case 0x1:
			puts( "range 0x1 procedure" );
			break;
	};
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
