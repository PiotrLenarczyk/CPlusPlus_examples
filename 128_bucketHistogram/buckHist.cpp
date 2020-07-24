// http://www.concentric.net/~Ttwang/tech/inthash.htm
#include <cstdio> 
#include <time.h>	//clock()
using namespace std;

typedef unsigned char 	u8;
typedef unsigned short 	u16;
typedef unsigned int	u32;
typedef unsigned long long u64;
#define U8_SIZE			sizeof( u8 )
#define U16_SIZE		sizeof( u16 )
#define U32_SIZE		sizeof( u32 )
#define MAX_U8			(u16)(0x100)
#define MAX_U16			(u32)(0x10000)
#define	MAX_U32			(u64)(0x100000000)

#define MAX_BUCKETS 	0x20
#define BUCKETNO_2		0x2
#define BUCKETNO_4		0x4
#define BUCKETNO_8		0x8
#define BUCKETNO_16		0x10
#define BUCKETNO_32		0x20
u64 varMax;
u32 bucketWidth, bucketNo, hist[ MAX_BUCKETS ], mask32[ MAX_BUCKETS ];
u16 mask16[ MAX_BUCKETS ];
u8 mask8[ MAX_BUCKETS ];

//deterministic bucket hist with set no of buckets and analysis size(varSize)
#define hist(data, size, histBucketsSize) 					\
		__hist( sizeof(*data), (u8*)(void*)data, size, histBucketsSize )
void __hist( u8 varSize, u8* data, u32 size, u8 histBucketsSize )
{	//count masks
	switch( varSize )
	{	case U8_SIZE:		varMax = (u64)MAX_U8;		break;
		case U16_SIZE:		varMax = (u64)MAX_U16;		break;
		case U32_SIZE:		varMax = (u64)MAX_U32;		break;
	};
	switch( histBucketsSize )
	{	case BUCKETNO_2:	bucketWidth = (u32)(varMax >> (u64)(0x1));	break;
		case BUCKETNO_4:	bucketWidth = (u32)(varMax >> (u64)(0x2));	break;
		case BUCKETNO_8:	bucketWidth = (u32)(varMax >> (u64)(0x3));	break;
		case BUCKETNO_16:	bucketWidth = (u32)(varMax >> (u64)(0x4));	break;
		case BUCKETNO_32:	bucketWidth = (u32)(varMax >> (u64)(0x5));	break;
	};
	switch( varSize )
	{	case U8_SIZE:
			for ( u32 i = 0x0; i < histBucketsSize; i++ )
				mask8[ i ] = bucketWidth * i;
			break;
		case U16_SIZE:
			for ( u32 i = 0x0; i < histBucketsSize; i++ )
				mask16[ i ] = bucketWidth * i;
			break;
		case U32_SIZE:
			for ( u32 i = 0x0; i < histBucketsSize; i++ )
				mask32[ i ] = bucketWidth * i;
			break;
	};
	
	//count histogram
	switch( varSize )
	{	case U8_SIZE:
			for ( int i = 0x0; i < MAX_BUCKETS; i++ )
				hist[ i ] = 0x0;
			for( u32 i = 0x0;i < size; i += U8_SIZE)//analyze data
			{	//highest bucket
				bucketNo = (( (*(u8*)(data + i) >= mask8[ histBucketsSize - 1 ]) && ((u16)*(u8*)(data + i) < MAX_U8)) * (histBucketsSize - 1) );
				//aggregate bucket number
				switch( histBucketsSize )
				{	case BUCKETNO_2:	
						bucketNo |= 
							(( (*(u8*)(data + i) >= mask8[0]) && (*(u8*)(data + i) < mask8[1])) * 0 );
						break;
					case BUCKETNO_4:	
						bucketNo |= 
							(( (*(u8*)(data + i) >= mask8[0]) && (*(u8*)(data + i) < mask8[1])) * 0 ) |
							(( (*(u8*)(data + i) >= mask8[1]) && (*(u8*)(data + i) < mask8[2])) * 1 ) |
							(( (*(u8*)(data + i) >= mask8[2]) && (*(u8*)(data + i) < mask8[3])) * 2 );
						break;
					case BUCKETNO_8:
						bucketNo |= 
							(( (*(u8*)(data + i) >= mask8[0]) && (*(u8*)(data + i) < mask8[1])) * 0 ) |
							(( (*(u8*)(data + i) >= mask8[1]) && (*(u8*)(data + i) < mask8[2])) * 1 ) |
							(( (*(u8*)(data + i) >= mask8[2]) && (*(u8*)(data + i) < mask8[3])) * 2 ) |
							(( (*(u8*)(data + i) >= mask8[3]) && (*(u8*)(data + i) < mask8[4])) * 3 ) |
							(( (*(u8*)(data + i) >= mask8[4]) && (*(u8*)(data + i) < mask8[5])) * 4 ) |
							(( (*(u8*)(data + i) >= mask8[5]) && (*(u8*)(data + i) < mask8[6])) * 5 ) |
							(( (*(u8*)(data + i) >= mask8[6]) && (*(u8*)(data + i) < mask8[7])) * 6 );
						break;
					case BUCKETNO_16:	
						bucketNo |= 
							(( (*(u8*)(data + i) >= mask8[0]) && (*(u8*)(data + i) < mask8[1])) * 0 ) |
							(( (*(u8*)(data + i) >= mask8[1]) && (*(u8*)(data + i) < mask8[2])) * 1 ) |
							(( (*(u8*)(data + i) >= mask8[2]) && (*(u8*)(data + i) < mask8[3])) * 2 ) |
							(( (*(u8*)(data + i) >= mask8[3]) && (*(u8*)(data + i) < mask8[4])) * 3 ) |
							(( (*(u8*)(data + i) >= mask8[4]) && (*(u8*)(data + i) < mask8[5])) * 4 ) |
							(( (*(u8*)(data + i) >= mask8[5]) && (*(u8*)(data + i) < mask8[6])) * 5 ) |
							(( (*(u8*)(data + i) >= mask8[6]) && (*(u8*)(data + i) < mask8[7])) * 6 ) |
							(( (*(u8*)(data + i) >= mask8[7]) && (*(u8*)(data + i) < mask8[8])) * 7 ) |
							(( (*(u8*)(data + i) >= mask8[8]) && (*(u8*)(data + i) < mask8[9])) * 8 ) |
							(( (*(u8*)(data + i) >= mask8[9]) && (*(u8*)(data + i) < mask8[10])) * 9 ) |
							(( (*(u8*)(data + i) >= mask8[10]) && (*(u8*)(data + i) < mask8[11])) * 10 ) |
							(( (*(u8*)(data + i) >= mask8[11]) && (*(u8*)(data + i) < mask8[12])) * 11 ) |
							(( (*(u8*)(data + i) >= mask8[12]) && (*(u8*)(data + i) < mask8[13])) * 12 ) |
							(( (*(u8*)(data + i) >= mask8[13]) && (*(u8*)(data + i) < mask8[14])) * 13 ) |
							(( (*(u8*)(data + i) >= mask8[14]) && (*(u8*)(data + i) < mask8[15])) * 14 );
						break;
					case BUCKETNO_32:	
						bucketNo |= 
							(( (*(u8*)(data + i) >= mask8[0]) && (*(u8*)(data + i) < mask8[1])) * 0 ) |
							(( (*(u8*)(data + i) >= mask8[1]) && (*(u8*)(data + i) < mask8[2])) * 1 ) |
							(( (*(u8*)(data + i) >= mask8[2]) && (*(u8*)(data + i) < mask8[3])) * 2 ) |
							(( (*(u8*)(data + i) >= mask8[3]) && (*(u8*)(data + i) < mask8[4])) * 3 ) |
							(( (*(u8*)(data + i) >= mask8[4]) && (*(u8*)(data + i) < mask8[5])) * 4 ) |
							(( (*(u8*)(data + i) >= mask8[5]) && (*(u8*)(data + i) < mask8[6])) * 5 ) |
							(( (*(u8*)(data + i) >= mask8[6]) && (*(u8*)(data + i) < mask8[7])) * 6 ) |
							(( (*(u8*)(data + i) >= mask8[7]) && (*(u8*)(data + i) < mask8[8])) * 7 ) |
							(( (*(u8*)(data + i) >= mask8[8]) && (*(u8*)(data + i) < mask8[9])) * 8 ) |
							(( (*(u8*)(data + i) >= mask8[9]) && (*(u8*)(data + i) < mask8[10])) * 9 ) |
							(( (*(u8*)(data + i) >= mask8[10]) && (*(u8*)(data + i) < mask8[11])) * 10 ) |
							(( (*(u8*)(data + i) >= mask8[11]) && (*(u8*)(data + i) < mask8[12])) * 11 ) |
							(( (*(u8*)(data + i) >= mask8[12]) && (*(u8*)(data + i) < mask8[13])) * 12 ) |
							(( (*(u8*)(data + i) >= mask8[13]) && (*(u8*)(data + i) < mask8[14])) * 13 ) |
							(( (*(u8*)(data + i) >= mask8[14]) && (*(u8*)(data + i) < mask8[15])) * 14 ) |
							(( (*(u8*)(data + i) >= mask8[15]) && (*(u8*)(data + i) < mask8[16])) * 15 ) |
							(( (*(u8*)(data + i) >= mask8[16]) && (*(u8*)(data + i) < mask8[17])) * 16 ) |
							(( (*(u8*)(data + i) >= mask8[17]) && (*(u8*)(data + i) < mask8[18])) * 17 ) |
							(( (*(u8*)(data + i) >= mask8[18]) && (*(u8*)(data + i) < mask8[19])) * 18 ) |
							(( (*(u8*)(data + i) >= mask8[19]) && (*(u8*)(data + i) < mask8[20])) * 19 ) |
							(( (*(u8*)(data + i) >= mask8[20]) && (*(u8*)(data + i) < mask8[21])) * 20 ) |
							(( (*(u8*)(data + i) >= mask8[21]) && (*(u8*)(data + i) < mask8[22])) * 21 ) |
							(( (*(u8*)(data + i) >= mask8[22]) && (*(u8*)(data + i) < mask8[23])) * 22 ) |
							(( (*(u8*)(data + i) >= mask8[23]) && (*(u8*)(data + i) < mask8[24])) * 23 ) |
							(( (*(u8*)(data + i) >= mask8[24]) && (*(u8*)(data + i) < mask8[25])) * 24 ) |
							(( (*(u8*)(data + i) >= mask8[25]) && (*(u8*)(data + i) < mask8[26])) * 25 ) |
							(( (*(u8*)(data + i) >= mask8[26]) && (*(u8*)(data + i) < mask8[27])) * 26 ) |
							(( (*(u8*)(data + i) >= mask8[27]) && (*(u8*)(data + i) < mask8[28])) * 27 ) |
							(( (*(u8*)(data + i) >= mask8[28]) && (*(u8*)(data + i) < mask8[29])) * 28 ) |
							(( (*(u8*)(data + i) >= mask8[29]) && (*(u8*)(data + i) < mask8[30])) * 29 ) |
							(( (*(u8*)(data + i) >= mask8[30]) && (*(u8*)(data + i) < mask8[31])) * 30 );
						break;
				};//switch( histBucketsSize )
				switch( bucketNo )
				{	case 0:		hist[0]++;	break;
					case 1:		hist[1]++;	break;
					case 2:		hist[2]++;	break;
					case 3:		hist[3]++;	break;
					case 4:		hist[4]++;	break;
					case 5:		hist[5]++;	break;
					case 6:		hist[6]++;	break;
					case 7:		hist[7]++;	break;
					case 8:		hist[8]++;	break;
					case 9:		hist[9]++;	break;
					case 10:	hist[10]++;	break;
					case 11:	hist[11]++;	break;
					case 12:	hist[12]++;	break;
					case 13:	hist[13]++;	break;
					case 14:	hist[14]++;	break;
					case 15:	hist[15]++;	break;
					case 16:	hist[16]++;	break;
					case 17:	hist[17]++;	break;
					case 18:	hist[18]++;	break;
					case 19:	hist[19]++;	break;
					case 20:	hist[20]++;	break;
					case 21:	hist[21]++;	break;
					case 22:	hist[22]++;	break;
					case 23:	hist[23]++;	break;
					case 24:	hist[24]++;	break;
					case 25:	hist[25]++;	break;
					case 26:	hist[26]++;	break;
					case 27:	hist[27]++;	break;
					case 28:	hist[28]++;	break;
					case 29:	hist[29]++;	break;
					case 30:	hist[30]++;	break;
					case 31:	hist[31]++;	break;
				};//switch( bucketNo )
			};//for () data
			break; //U8_SIZE
		case U16_SIZE:
			for ( int i = 0x0; i < MAX_BUCKETS; i++ )
				hist[ i ] = 0x0;
			for( u32 i = 0x0;i < size; i += U16_SIZE)//analyze data
			{	//highest bucket compared to datatype MAX value
				bucketNo = (( (*(u16*)(data + i) >= mask16[ histBucketsSize - 1 ]) && ((u32)*(u16*)(data + i) < MAX_U16)) * (histBucketsSize - 1) );
				//aggregate bucket number
				switch( histBucketsSize )
				{	case BUCKETNO_2:	
						bucketNo |= 
							(( (*(u16*)(data + i) >= mask16[0]) && (*(u16*)(data + i) < mask16[1])) * 0 );
						break;
					case BUCKETNO_4:	
						bucketNo |= 
							(( (*(u16*)(data + i) >= mask16[0]) && (*(u16*)(data + i) < mask16[1])) * 0 ) |
							(( (*(u16*)(data + i) >= mask16[1]) && (*(u16*)(data + i) < mask16[2])) * 1 ) |
							(( (*(u16*)(data + i) >= mask16[2]) && (*(u16*)(data + i) < mask16[3])) * 2 );
						break;
					case BUCKETNO_8:
						bucketNo |= 
							(( (*(u16*)(data + i) >= mask16[0]) && (*(u16*)(data + i) < mask16[1])) * 0 ) |
							(( (*(u16*)(data + i) >= mask16[1]) && (*(u16*)(data + i) < mask16[2])) * 1 ) |
							(( (*(u16*)(data + i) >= mask16[2]) && (*(u16*)(data + i) < mask16[3])) * 2 ) |
							(( (*(u16*)(data + i) >= mask16[3]) && (*(u16*)(data + i) < mask16[4])) * 3 ) |
							(( (*(u16*)(data + i) >= mask16[4]) && (*(u16*)(data + i) < mask16[5])) * 4 ) |
							(( (*(u16*)(data + i) >= mask16[5]) && (*(u16*)(data + i) < mask16[6])) * 5 ) |
							(( (*(u16*)(data + i) >= mask16[6]) && (*(u16*)(data + i) < mask16[7])) * 6 );
						break;
					case BUCKETNO_16:	
						bucketNo |= 
							(( (*(u16*)(data + i) >= mask16[0]) && (*(u16*)(data + i) < mask16[1])) * 0 ) |
							(( (*(u16*)(data + i) >= mask16[1]) && (*(u16*)(data + i) < mask16[2])) * 1 ) |
							(( (*(u16*)(data + i) >= mask16[2]) && (*(u16*)(data + i) < mask16[3])) * 2 ) |
							(( (*(u16*)(data + i) >= mask16[3]) && (*(u16*)(data + i) < mask16[4])) * 3 ) |
							(( (*(u16*)(data + i) >= mask16[4]) && (*(u16*)(data + i) < mask16[5])) * 4 ) |
							(( (*(u16*)(data + i) >= mask16[5]) && (*(u16*)(data + i) < mask16[6])) * 5 ) |
							(( (*(u16*)(data + i) >= mask16[6]) && (*(u16*)(data + i) < mask16[7])) * 6 ) |
							(( (*(u16*)(data + i) >= mask16[7]) && (*(u16*)(data + i) < mask16[8])) * 7 ) |
							(( (*(u16*)(data + i) >= mask16[8]) && (*(u16*)(data + i) < mask16[9])) * 8 ) |
							(( (*(u16*)(data + i) >= mask16[9]) && (*(u16*)(data + i) < mask16[10])) * 9 ) |
							(( (*(u16*)(data + i) >= mask16[10]) && (*(u16*)(data + i) < mask16[11])) * 10 ) |
							(( (*(u16*)(data + i) >= mask16[11]) && (*(u16*)(data + i) < mask16[12])) * 11 ) |
							(( (*(u16*)(data + i) >= mask16[12]) && (*(u16*)(data + i) < mask16[13])) * 12 ) |
							(( (*(u16*)(data + i) >= mask16[13]) && (*(u16*)(data + i) < mask16[14])) * 13 ) |
							(( (*(u16*)(data + i) >= mask16[14]) && (*(u16*)(data + i) < mask16[15])) * 14 );
						break;
					case BUCKETNO_32:	
						bucketNo |= 
							(( (*(u16*)(data + i) >= mask16[0]) && (*(u16*)(data + i) < mask16[1])) * 0 ) |
							(( (*(u16*)(data + i) >= mask16[1]) && (*(u16*)(data + i) < mask16[2])) * 1 ) |
							(( (*(u16*)(data + i) >= mask16[2]) && (*(u16*)(data + i) < mask16[3])) * 2 ) |
							(( (*(u16*)(data + i) >= mask16[3]) && (*(u16*)(data + i) < mask16[4])) * 3 ) |
							(( (*(u16*)(data + i) >= mask16[4]) && (*(u16*)(data + i) < mask16[5])) * 4 ) |
							(( (*(u16*)(data + i) >= mask16[5]) && (*(u16*)(data + i) < mask16[6])) * 5 ) |
							(( (*(u16*)(data + i) >= mask16[6]) && (*(u16*)(data + i) < mask16[7])) * 6 ) |
							(( (*(u16*)(data + i) >= mask16[7]) && (*(u16*)(data + i) < mask16[8])) * 7 ) |
							(( (*(u16*)(data + i) >= mask16[8]) && (*(u16*)(data + i) < mask16[9])) * 8 ) |
							(( (*(u16*)(data + i) >= mask16[9]) && (*(u16*)(data + i) < mask16[10])) * 9 ) |
							(( (*(u16*)(data + i) >= mask16[10]) && (*(u16*)(data + i) < mask16[11])) * 10 ) |
							(( (*(u16*)(data + i) >= mask16[11]) && (*(u16*)(data + i) < mask16[12])) * 11 ) |
							(( (*(u16*)(data + i) >= mask16[12]) && (*(u16*)(data + i) < mask16[13])) * 12 ) |
							(( (*(u16*)(data + i) >= mask16[13]) && (*(u16*)(data + i) < mask16[14])) * 13 ) |
							(( (*(u16*)(data + i) >= mask16[14]) && (*(u16*)(data + i) < mask16[15])) * 14 ) |
							(( (*(u16*)(data + i) >= mask16[15]) && (*(u16*)(data + i) < mask16[16])) * 15 ) |
							(( (*(u16*)(data + i) >= mask16[16]) && (*(u16*)(data + i) < mask16[17])) * 16 ) |
							(( (*(u16*)(data + i) >= mask16[17]) && (*(u16*)(data + i) < mask16[18])) * 17 ) |
							(( (*(u16*)(data + i) >= mask16[18]) && (*(u16*)(data + i) < mask16[19])) * 18 ) |
							(( (*(u16*)(data + i) >= mask16[19]) && (*(u16*)(data + i) < mask16[20])) * 19 ) |
							(( (*(u16*)(data + i) >= mask16[20]) && (*(u16*)(data + i) < mask16[21])) * 20 ) |
							(( (*(u16*)(data + i) >= mask16[21]) && (*(u16*)(data + i) < mask16[22])) * 21 ) |
							(( (*(u16*)(data + i) >= mask16[22]) && (*(u16*)(data + i) < mask16[23])) * 22 ) |
							(( (*(u16*)(data + i) >= mask16[23]) && (*(u16*)(data + i) < mask16[24])) * 23 ) |
							(( (*(u16*)(data + i) >= mask16[24]) && (*(u16*)(data + i) < mask16[25])) * 24 ) |
							(( (*(u16*)(data + i) >= mask16[25]) && (*(u16*)(data + i) < mask16[26])) * 25 ) |
							(( (*(u16*)(data + i) >= mask16[26]) && (*(u16*)(data + i) < mask16[27])) * 26 ) |
							(( (*(u16*)(data + i) >= mask16[27]) && (*(u16*)(data + i) < mask16[28])) * 27 ) |
							(( (*(u16*)(data + i) >= mask16[28]) && (*(u16*)(data + i) < mask16[29])) * 28 ) |
							(( (*(u16*)(data + i) >= mask16[29]) && (*(u16*)(data + i) < mask16[30])) * 29 ) |
							(( (*(u16*)(data + i) >= mask16[30]) && (*(u16*)(data + i) < mask16[31])) * 30 );
						break;
				};//switch( histBucketsSize )
				switch( bucketNo )
				{	case 0:		hist[0]++;	break;
					case 1:		hist[1]++;	break;
					case 2:		hist[2]++;	break;
					case 3:		hist[3]++;	break;
					case 4:		hist[4]++;	break;
					case 5:		hist[5]++;	break;
					case 6:		hist[6]++;	break;
					case 7:		hist[7]++;	break;
					case 8:		hist[8]++;	break;
					case 9:		hist[9]++;	break;
					case 10:	hist[10]++;	break;
					case 11:	hist[11]++;	break;
					case 12:	hist[12]++;	break;
					case 13:	hist[13]++;	break;
					case 14:	hist[14]++;	break;
					case 15:	hist[15]++;	break;
					case 16:	hist[16]++;	break;
					case 17:	hist[17]++;	break;
					case 18:	hist[18]++;	break;
					case 19:	hist[19]++;	break;
					case 20:	hist[20]++;	break;
					case 21:	hist[21]++;	break;
					case 22:	hist[22]++;	break;
					case 23:	hist[23]++;	break;
					case 24:	hist[24]++;	break;
					case 25:	hist[25]++;	break;
					case 26:	hist[26]++;	break;
					case 27:	hist[27]++;	break;
					case 28:	hist[28]++;	break;
					case 29:	hist[29]++;	break;
					case 30:	hist[30]++;	break;
					case 31:	hist[31]++;	break;
				};//switch( bucketNo )
			};//for () data
			break; //U16_SIZE
		case U32_SIZE:
			for ( int i = 0x0; i < MAX_BUCKETS; i++ )
				hist[ i ] = 0x0;
			for( u32 i = 0x0;i < size; i += U32_SIZE)//analyze data
			{	//highest bucket compared to datatype MAX value
				bucketNo = (( (*(u32*)(data + i) >= mask32[ histBucketsSize - 1 ]) && ((u64)*(u32*)(data + i) < MAX_U32)) * (histBucketsSize - 1) );
				//aggregate bucket number
				switch( histBucketsSize )
				{	case BUCKETNO_2:	
						bucketNo |= 
							(( (*(u32*)(data + i) >= mask32[0]) && (*(u32*)(data + i) < mask32[1])) * 0 );
						break;
					case BUCKETNO_4:	
						bucketNo |= 
							(( (*(u32*)(data + i) >= mask32[0]) && (*(u32*)(data + i) < mask32[1])) * 0 ) |
							(( (*(u32*)(data + i) >= mask32[1]) && (*(u32*)(data + i) < mask32[2])) * 1 ) |
							(( (*(u32*)(data + i) >= mask32[2]) && (*(u32*)(data + i) < mask32[3])) * 2 );
						break;
					case BUCKETNO_8:
						bucketNo |= 
							(( (*(u32*)(data + i) >= mask32[0]) && (*(u32*)(data + i) < mask32[1])) * 0 ) |
							(( (*(u32*)(data + i) >= mask32[1]) && (*(u32*)(data + i) < mask32[2])) * 1 ) |
							(( (*(u32*)(data + i) >= mask32[2]) && (*(u32*)(data + i) < mask32[3])) * 2 ) |
							(( (*(u32*)(data + i) >= mask32[3]) && (*(u32*)(data + i) < mask32[4])) * 3 ) |
							(( (*(u32*)(data + i) >= mask32[4]) && (*(u32*)(data + i) < mask32[5])) * 4 ) |
							(( (*(u32*)(data + i) >= mask32[5]) && (*(u32*)(data + i) < mask32[6])) * 5 ) |
							(( (*(u32*)(data + i) >= mask32[6]) && (*(u32*)(data + i) < mask32[7])) * 6 );
						break;
					case BUCKETNO_16:	
						bucketNo |= 
							(( (*(u32*)(data + i) >= mask32[0]) && (*(u32*)(data + i) < mask32[1])) * 0 ) |
							(( (*(u32*)(data + i) >= mask32[1]) && (*(u32*)(data + i) < mask32[2])) * 1 ) |
							(( (*(u32*)(data + i) >= mask32[2]) && (*(u32*)(data + i) < mask32[3])) * 2 ) |
							(( (*(u32*)(data + i) >= mask32[3]) && (*(u32*)(data + i) < mask32[4])) * 3 ) |
							(( (*(u32*)(data + i) >= mask32[4]) && (*(u32*)(data + i) < mask32[5])) * 4 ) |
							(( (*(u32*)(data + i) >= mask32[5]) && (*(u32*)(data + i) < mask32[6])) * 5 ) |
							(( (*(u32*)(data + i) >= mask32[6]) && (*(u32*)(data + i) < mask32[7])) * 6 ) |
							(( (*(u32*)(data + i) >= mask32[7]) && (*(u32*)(data + i) < mask32[8])) * 7 ) |
							(( (*(u32*)(data + i) >= mask32[8]) && (*(u32*)(data + i) < mask32[9])) * 8 ) |
							(( (*(u32*)(data + i) >= mask32[9]) && (*(u32*)(data + i) < mask32[10])) * 9 ) |
							(( (*(u32*)(data + i) >= mask32[10]) && (*(u32*)(data + i) < mask32[11])) * 10 ) |
							(( (*(u32*)(data + i) >= mask32[11]) && (*(u32*)(data + i) < mask32[12])) * 11 ) |
							(( (*(u32*)(data + i) >= mask32[12]) && (*(u32*)(data + i) < mask32[13])) * 12 ) |
							(( (*(u32*)(data + i) >= mask32[13]) && (*(u32*)(data + i) < mask32[14])) * 13 ) |
							(( (*(u32*)(data + i) >= mask32[14]) && (*(u32*)(data + i) < mask32[15])) * 14 );
						break;
					case BUCKETNO_32:	
						bucketNo |= 
							(( (*(u32*)(data + i) >= mask32[0]) && (*(u32*)(data + i) < mask32[1])) * 0 ) |
							(( (*(u32*)(data + i) >= mask32[1]) && (*(u32*)(data + i) < mask32[2])) * 1 ) |
							(( (*(u32*)(data + i) >= mask32[2]) && (*(u32*)(data + i) < mask32[3])) * 2 ) |
							(( (*(u32*)(data + i) >= mask32[3]) && (*(u32*)(data + i) < mask32[4])) * 3 ) |
							(( (*(u32*)(data + i) >= mask32[4]) && (*(u32*)(data + i) < mask32[5])) * 4 ) |
							(( (*(u32*)(data + i) >= mask32[5]) && (*(u32*)(data + i) < mask32[6])) * 5 ) |
							(( (*(u32*)(data + i) >= mask32[6]) && (*(u32*)(data + i) < mask32[7])) * 6 ) |
							(( (*(u32*)(data + i) >= mask32[7]) && (*(u32*)(data + i) < mask32[8])) * 7 ) |
							(( (*(u32*)(data + i) >= mask32[8]) && (*(u32*)(data + i) < mask32[9])) * 8 ) |
							(( (*(u32*)(data + i) >= mask32[9]) && (*(u32*)(data + i) < mask32[10])) * 9 ) |
							(( (*(u32*)(data + i) >= mask32[10]) && (*(u32*)(data + i) < mask32[11])) * 10 ) |
							(( (*(u32*)(data + i) >= mask32[11]) && (*(u32*)(data + i) < mask32[12])) * 11 ) |
							(( (*(u32*)(data + i) >= mask32[12]) && (*(u32*)(data + i) < mask32[13])) * 12 ) |
							(( (*(u32*)(data + i) >= mask32[13]) && (*(u32*)(data + i) < mask32[14])) * 13 ) |
							(( (*(u32*)(data + i) >= mask32[14]) && (*(u32*)(data + i) < mask32[15])) * 14 ) |
							(( (*(u32*)(data + i) >= mask32[15]) && (*(u32*)(data + i) < mask32[16])) * 15 ) |
							(( (*(u32*)(data + i) >= mask32[16]) && (*(u32*)(data + i) < mask32[17])) * 16 ) |
							(( (*(u32*)(data + i) >= mask32[17]) && (*(u32*)(data + i) < mask32[18])) * 17 ) |
							(( (*(u32*)(data + i) >= mask32[18]) && (*(u32*)(data + i) < mask32[19])) * 18 ) |
							(( (*(u32*)(data + i) >= mask32[19]) && (*(u32*)(data + i) < mask32[20])) * 19 ) |
							(( (*(u32*)(data + i) >= mask32[20]) && (*(u32*)(data + i) < mask32[21])) * 20 ) |
							(( (*(u32*)(data + i) >= mask32[21]) && (*(u32*)(data + i) < mask32[22])) * 21 ) |
							(( (*(u32*)(data + i) >= mask32[22]) && (*(u32*)(data + i) < mask32[23])) * 22 ) |
							(( (*(u32*)(data + i) >= mask32[23]) && (*(u32*)(data + i) < mask32[24])) * 23 ) |
							(( (*(u32*)(data + i) >= mask32[24]) && (*(u32*)(data + i) < mask32[25])) * 24 ) |
							(( (*(u32*)(data + i) >= mask32[25]) && (*(u32*)(data + i) < mask32[26])) * 25 ) |
							(( (*(u32*)(data + i) >= mask32[26]) && (*(u32*)(data + i) < mask32[27])) * 26 ) |
							(( (*(u32*)(data + i) >= mask32[27]) && (*(u32*)(data + i) < mask32[28])) * 27 ) |
							(( (*(u32*)(data + i) >= mask32[28]) && (*(u32*)(data + i) < mask32[29])) * 28 ) |
							(( (*(u32*)(data + i) >= mask32[29]) && (*(u32*)(data + i) < mask32[30])) * 29 ) |
							(( (*(u32*)(data + i) >= mask32[30]) && (*(u32*)(data + i) < mask32[31])) * 30 );
						break;
				};//switch( histBucketsSize )
				switch( bucketNo )
				{	case 0:		hist[0]++;	break;
					case 1:		hist[1]++;	break;
					case 2:		hist[2]++;	break;
					case 3:		hist[3]++;	break;
					case 4:		hist[4]++;	break;
					case 5:		hist[5]++;	break;
					case 6:		hist[6]++;	break;
					case 7:		hist[7]++;	break;
					case 8:		hist[8]++;	break;
					case 9:		hist[9]++;	break;
					case 10:	hist[10]++;	break;
					case 11:	hist[11]++;	break;
					case 12:	hist[12]++;	break;
					case 13:	hist[13]++;	break;
					case 14:	hist[14]++;	break;
					case 15:	hist[15]++;	break;
					case 16:	hist[16]++;	break;
					case 17:	hist[17]++;	break;
					case 18:	hist[18]++;	break;
					case 19:	hist[19]++;	break;
					case 20:	hist[20]++;	break;
					case 21:	hist[21]++;	break;
					case 22:	hist[22]++;	break;
					case 23:	hist[23]++;	break;
					case 24:	hist[24]++;	break;
					case 25:	hist[25]++;	break;
					case 26:	hist[26]++;	break;
					case 27:	hist[27]++;	break;
					case 28:	hist[28]++;	break;
					case 29:	hist[29]++;	break;
					case 30:	hist[30]++;	break;
					case 31:	hist[31]++;	break;
				};//switch( bucketNo )
			};//for () data
			break; //U32_SIZE
	};
};

u32 mix(u32 a, u32 b, u32 c)
{   a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}

#define RAND_A 						1103515245		//glibc
#define	RAND_C 						12345			//glibc
#define RAND_M 						( 0x1 << 0x1F )	//glibc
int seed;
void srand( int setSeed )
{	seed = setSeed;
};

int rand( void )
{	return seed = ( (RAND_A * seed) + RAND_C ) % RAND_M;
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#define BUFSIZE	0x100
u32 arr[ BUFSIZE ]; //u8 u16 u32
int main( void )
{	u32 size, noElems, histBucketsSize;
	size = sizeof(arr);
	noElems = size / sizeof(arr[0]); 
	histBucketsSize = BUCKETNO_8;
	
	//randomize seed
	srand( mix(clock(), time(NULL), clock() + 1) );
	for (int i = 0x0; i < (0x1 | (rand() % 0x100)); i++, rand())
	{	srand( mix(rand(), rand(), rand() + 0x1) );
	};
	
	//init arr[]
	switch (sizeof(arr[0]))
	{	case U8_SIZE: 	printf( "u8 " ); break;
		case U16_SIZE: 	printf( "u16 " ); break;
		case U32_SIZE: 	printf( "u32 " ); break;
	};
	printf( "arr[] = \n{\n" );
	for ( u32 i = 0x0; i < noElems; i++ )
	{	arr[ i ] = rand();
		printf( "0x%08X, ", arr[ i ] );
	};
	printf( "};\n" );

	//count bucket histogram
	hist(arr, size, histBucketsSize );
	
	//print hist results
	u32 histSum = 0x0;
	printf( "\n====\n%d x %dB data histogram of %d buckets with width : 0x%08X(%d)\n", noElems, sizeof(arr[0]), histBucketsSize, bucketWidth, bucketWidth );
	for ( u32 i = 0x0; i < histBucketsSize; i++ )
	{	histSum += hist[ i ];
		printf( "hist[%02d] : ", i);
		for( u32 h = 0x0; h < hist[ i ]; h++ )
			printf( "*" );
		printf("\n");
	};
	if ( (size / sizeof(arr[0])) == histSum )
		printf( "histSum(size = %d) : %d\n====\n", (size / sizeof(arr[0])), histSum );
	else
	{	printf( "histSum(size = %d) : %d\n====\n", (size / sizeof(arr[0])), histSum );
		puts( "====\n!!!!\n\tFATAL ERROR\n!!!!\n====" );
	};
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
