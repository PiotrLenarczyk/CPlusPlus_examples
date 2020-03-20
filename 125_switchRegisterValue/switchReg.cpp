#include <cstdio> 
using namespace std;
typedef unsigned char u8;
#define S0			( 0x1 << 0x0 ) //optimization independed: (0x1)
#define S1			( 0x1 << 0x1 ) //optimization independed: (0x2)
#define S2			( 0x1 << 0x2 ) //...
#define S3			( 0x1 << 0x3 )
#define S4			( 0x1 << 0x4 )
#define S5			( 0x1 << 0x5 )
#define S6			( 0x1 << 0x6 )
#define S7			( 0x1 << 0x7 )
#define Z0			( 0x0 << 0x0 ) //reading - friendly zeros
#define Z1			( 0x0 << 0x1 )
#define Z2			( 0x0 << 0x2 )
#define Z3			( 0x0 << 0x3 )
#define Z4			( 0x0 << 0x4 )
#define Z5			( 0x0 << 0x5 )
#define Z6			( 0x0 << 0x6 )
#define Z7			( 0x0 << 0x7 )

void foo( void )
{	u8 reg;
	reg = ( 0x0 << 0x1 ) | ( 0x1 << 0x0 );
	puts( "mixed two (from 8) bits states - fastest interpretation ");
	reg &= S1 | S0; //4 states for 2 bits; 8 states for 3 bits; ...
	switch( reg )
	{	default:
			break;
		case Z1 | Z0: 		//0b00
			puts( "0b00" );
			break;
		case Z1 | S0:		//0b01
			puts( "0b01" );
			break;
		case S1 | Z0:		//0b10
			puts( "0b10" );
			break;
		case S1 | S0:		//0b11
			puts( "0b11" );
			break;
	};
	
	reg = ( 0x1 << 0x5 ) | ( 0x1 << 0x1 );
	puts( "individual bits - without use of clz(); ctz(); ");
	if ( reg & S7 )		puts( "bit 7 hit" );
	if ( reg & S6 )		puts( "bit 6 hit" );
	if ( reg & S5 )		puts( "bit 5 hit" );
	if ( reg & S4 )		puts( "bit 4 hit" );
	if ( reg & S3 )		puts( "bit 3 hit" );
	if ( reg & S2 )		puts( "bit 2 hit" );
	if ( reg & S1 )		puts( "bit 1 hit" );
	if ( reg & S0 )		puts( "bit 0 hit" );
};//foo()

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	foo();
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
