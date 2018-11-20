#include <stdio.h>

typedef unsigned char 			u8;
typedef unsigned short 			u16;
typedef unsigned int			u32;
typedef unsigned long			u64;
#define COUNT( ... ) 			COUNT_( __VA_ARGS__, COUNT_RSEQ_N() )
#define COUNT_( ... )			COUNT_ARG_N( __VA_ARGS__ )
#define COUNT_ARG_N( 										\
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, 			\
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, 			\
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, 			\
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, 			\
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, 			\
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, 			\
         _61,_62,_63,_64,_65,_66,_67,_68,_69,_70, 			\
         _71,_72,_73,_74,_75,_76,_77,_78,_79,_80, 			\
         _81,_82,_83,_84,_85,_86,_87,_88,_89,_90, 			\
         _91,_92,_93,_94,_95,_96,_97,_98,_99,_100, 			\
         _101,_102,_103,_104,_105,_106,_107,_108,_109,_110, \
         _111,_112,_113,_114,_115,_116,_117,_118,_119,_120, \
         _121,_122,_123,_124,_125,_126,_127,N,...) 	N
#define COUNT_RSEQ_N() 										\
                   127, 126, 125, 124, 123, 122, 121, 120, 	\
         119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 	\
         109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 	\
          99,  98,  97,  96,  95,  94,  93,  92,  91,  90, 	\
          89,  88,  87,  86,  85,  84,  83,  82,  81,  80, 	\
          79,  78,  77,  76,  75,  74,  73,  72,  71,  70, 	\
          69,  68,  67,  66,  65,  64,  63,  62,  61,  60, 	\
          59,  58,  57,  56,  55,  54,  53,  52,  51,  50, 	\
          49,  48,  47,  46,  45,  44,  43,  42,  41,  40, 	\
		  39,  38,  37,  36,  35,  34,  33,  32,  31,  30, 	\
          29,  28,  27,  26,  25,  24,  23,  22,  21,  20, 	\
          19,  18,  17,  16,  15,  14,  13,  12,  11,  10, 	\
           9,   8,   7,   6,   5,   4,   3,   2,   1,   0
//==============================================================================================
#define STRINGIZE( arg )							#arg
#define CONCATENATE( arg1, arg2 ) 					arg1##arg2
#define FE_CUMMULATIVE_1( macroName, x, ... ) 		macroName( x )
#define FE_CUMMULATIVE_2( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_1( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_3( macroName, x, ... )  		macroName( x ) FE_CUMMULATIVE_2( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_4( macroName, x, ... ) 		macroName( x ) FE_CUMMULATIVE_3( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_5( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_4( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_6( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_5( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_7( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_6( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_8( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_7( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_9( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_8( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_10( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_9( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_11( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_10( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_12( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_11( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_13( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_12( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_14( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_13( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_15( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_14( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_16( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_15( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_17( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_16( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_18( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_17( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_19( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_18( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_20( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_19( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_21( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_20( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_22( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_21( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_23( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_22( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_24( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_23( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_25( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_24( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_26( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_25( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_27( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_26( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_28( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_27( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_29( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_28( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_30( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_29( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_31( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_30( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_32( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_31( macroName,  __VA_ARGS__ )

#define FE_CUMMULATIVE_( N, macroName, ... )		CONCATENATE( FE_CUMMULATIVE_, N )( macroName, __VA_ARGS__ )
#define FOR_EACH_CUMMUlATIVE( macroName, ... ) 		FE_CUMMULATIVE_( COUNT( __VA_ARGS__ ), macroName, __VA_ARGS__ )
//============================================================================================
//--------------------------------------------------------------------------------------------
//------------------------	MACRO KERNELS ----------------------------------------------------
//--------------------------------------------------------------------------------------------
#define	_BOR( val )		| ( 0x1 << val ) 		//bit number or
#define	_BAND( val )	& ( 0x1 << val )		//bit number and
#define	_BANDNOT( val )	& ( ~( 0x1 << val ) )	//bit number and not
//--------------------------------------------------------------------------------------------
#define	bsetN32( addr, ... )	*( ( u32* )( addr ) ) |= ( 0x0 FOR_EACH_CUMMUlATIVE( _BOR, __VA_ARGS__ ) );
#define	bresN32( addr, ... )	*( ( u32* )( addr ) ) &= ( 0xFFFFFFFF FOR_EACH_CUMMUlATIVE( _BANDNOT, __VA_ARGS__ ) );
#define	borN32( ... )			( u32 )( 0x0 FOR_EACH_CUMMUlATIVE( _BOR, __VA_ARGS__ ) )
#define	bandNotN32( ... )		( u32 )( 0xFFFFFFFF FOR_EACH_CUMMUlATIVE( _BANDNOT, __VA_ARGS__ ) )
//==============================================================================================

void printBits( size_t const size, void const * const ptr )
{	if 		( size == 1 )
		printf( "hexVal = %#08x; decimalVal = %i \n", * ( u8* )ptr, * ( u8* )ptr );
	else if ( size == 2 )
		printf( "hexVal = %#08x; decimalVal = %i \n", * ( u16* )ptr, * ( u16* )ptr );
	else if ( size == 4 )
		printf( "hexVal = %#08x; decimalVal = %i \n", * ( u32* )ptr, * ( u32* )ptr );
	else if ( size == 8 )
		printf( "hexVal = %#08lx; decimalVal = %lu \n", * ( u64* )ptr, * ( u64* )ptr );
		
    unsigned char *b = ( unsigned char* ) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf( " %u ", byte );
        }
    }
    puts("");
    if ( ( size > 1 ) && ( size <= 12 ) )
    {	for( int ind  = 8*size - 1; ind > 9; ind-- )
			printf( "%d ", ind );
		for( int ind  = 9; ind > -1; ind-- )
			printf( " %d ", ind );		
	}
	else
	{	for( int ind  = 7; ind > -1; ind-- )
			printf( " %d ", ind );	
	}
    puts(""); puts("");
};


int compareValsBits( size_t sizeA, void * ptrA, size_t sizeB, void * ptrB )
{	if ( sizeA != sizeB )
		return -1;
	if ( sizeA == 8 )
		return 1;
		
	if 	( sizeA == 1 )
		printf( "comparing: \n[%#04x](%u)\n[%#04x](%u)\n====\n", * ( u8* )ptrA, * ( u8* )ptrA, * ( u8* )ptrB, * ( u8* )ptrB );
	else if ( sizeA == 2 )
		printf( "comparing: \n[%#06x](%u)\n[%#06x](%u)\n====\n", * ( u16* )ptrA, * ( u16* )ptrA, * ( u16* )ptrB, * ( u16* )ptrB );
	else if ( sizeA == 4 )
		printf( "comparing: \n[%#010x](%u)\n[%#010x](%u)\n====\n", * ( u32* )ptrA, * ( u32* )ptrA, * ( u32* )ptrB, * ( u32* )ptrB );
			
	unsigned char *a = ( unsigned char* ) ptrA;
    unsigned char *b = ( unsigned char* ) ptrB;
    unsigned char byteA, byteB;
    int i, j;

    for (i=sizeA-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byteA = (a[i] >> j) & 1;
            printf( " %u ", byteA );
        }
    }
    puts("");
    for (i=sizeA-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byteB = (b[i] >> j) & 1;
            printf( " %u ", byteB );
        }
    }
    puts("");
    if ( sizeA == 1 )
    {	for( int ind  = 7; ind > -1; ind-- )
			printf( " %d ", ind );	
	};
	if ( sizeA == 2 )
	{	for( int ind  = 15; ind > 9; ind-- )
			printf( "%d ", ind );
		for( int ind  = 9; ind > -1; ind-- )
			printf( " %d ", ind );		
	};
	if ( sizeA == 4 )
	{	for( int ind  = 31; ind > 9; ind-- )
			printf( "%d ", ind );
		for( int ind  = 9; ind > -1; ind-- )
			printf( " %d ", ind );		
	};
    puts(""); 
    
    for (i=sizeA-1;i>=0;i--)
    {   for (j=7;j>=0;j--)
        {   byteA = (a[i] >> j) & 1;
            byteB = (b[i] >> j) & 1;
            if ( byteA == byteB )
            	printf( "   " );
            else
            	printf( " x " );
        }
    };
    
    printf( "\n====\n" );
};


//==============================================================================================
//==============================================================================================
//==============================================================================================
u32	n, m;
int main( void )
{	n = m = 0x0;
	n = bsetN32( &n, 1, 2, 24, 25, 26, 28 );
	compareValsBits( sizeof( n ), &n, sizeof( m ), &m );
	
	m = borN32( 2, 25 );
	compareValsBits( sizeof( n ), &n, sizeof( m ), &m );
	
	return 0x0;
};
//==============================================================================================
//==============================================================================================
//==============================================================================================
