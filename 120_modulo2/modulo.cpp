#include <cstdio> 
using namespace std;
#include "defaults.h"

//0bXXXXX1<----
int ctz( unsigned no ) //count trailing zeros ctz(S8 | S9) == 0x8;
{	switch( no )
	{	default : goto justCTZ;
		case 0x00:return 32;
		case S0 : return  0;
		case S1 : return  1;
		case S2 : return  2;
		case S3 : return  3;
		case S4 : return  4;
		case S5 : return  5;
		case S6 : return  6;
		case S7 : return  7;
		case S8 : return  8;
		case S9 : return  9;
		case S10: return 10;
		case S11: return 11;
		case S12: return 12;
		case S13: return 13;
		case S14: return 14;
		case S15: return 15;
		case S16: return 16;
		case S17: return 17;
		case S18: return 18;
		case S19: return 19;
		case S20: return 20;
		case S21: return 21;
		case S22: return 22;
		case S23: return 23;
		case S24: return 24;
		case S25: return 25;
		case S26: return 26;
		case S27: return 27;
		case S28: return 28;
		case S29: return 29;
		case S30: return 30;
		case S31: return 31;		
	};
justCTZ:
	for ( int i = 0x0; i < 0x20; i++ )
		if ( no & ( 0x1 << i ) )
			return i;
	return -1;
};//ctz

//0b---->1XXXXX
int clz( unsigned no ) //count leading zeros  clz(S31 | S30) == 0x1F;
{	switch( no )
	{	default : goto justCLZ;
		case 0x00:return 32;
		case S0 : return 31;
		case S1 : return 30;
		case S2 : return 29;
		case S3 : return 28; 
		case S4 : return 27;
		case S5 : return 26;
		case S6 : return 25;
		case S7 : return 24;
		case S8 : return 23;
		case S9 : return 22;
		case S10: return 21;
		case S11: return 20;
		case S12: return 19;
		case S13: return 18;
		case S14: return 17;
		case S15: return 16;
		case S16: return 15;
		case S17: return 14;
		case S18: return 13;
		case S19: return 12;
		case S20: return 11;
		case S21: return 10;
		case S22: return  9;
		case S23: return  8;
		case S24: return  7;
		case S25: return  6;
		case S26: return  5;
		case S27: return  4;
		case S28: return  3;
		case S29: return  2;
		case S30: return  1;
		case S31: return  0;
	};
justCLZ:
	for ( int i = 0x1F; i > -1; i-- )
	{	if ( no & ( 0x1 << i ) )
			return 31 - i;
	};
	return -1;
};//ctz

#define MODULO2( a, b ) ( a - ( b * (a >> ctz(b)) ) )
#define DIV2( a, b )	( a >> ctz(b) )

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	
	unsigned i = S8, mod = 0x4, div = 0x2;//only applicable to powers of two!
	printf( " ctz(0x%X) : %i\n", i, ctz( i ) );
	printf( " clz(0x%X) : %i\n", i, clz( i ) );
	
	printf( "0x%X %% %i = %i || %i\n", i, mod, i%mod, MODULO2( i, mod ) );
	printf( "%i / %i = %i || %i\n", i, div, i/div, DIV2( i, div ) );
	return  0x00;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
