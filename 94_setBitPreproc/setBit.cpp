#include <iostream>
using namespace std;
typedef unsigned char byte;
typedef uint32_t uint;
uint i = 0, bitNumber;
#define SET_BIT( addr, bitNo )   { addr = ( ( ( addr >> bitNo ) & 0x1u ) != 0x1u ) 	\
												? addr |= 0x1u << bitNo 			\
												: addr 								\
								 }
#define RESET_BIT( addr, bitNo ) { addr = ( ( ( addr >> bitNo ) & 0x1u ) != 0x0u )	\
												? addr &= ~( 0x1u << bitNo )		\
												: addr 								\
								 }
#define BIT_VAL( addr, bitNo ) ( addr >> bitNo ) & 0x1u

void foo( void )
{	i = 0x0u; bitNumber = 31u;
	i = SET_BIT( i, bitNumber );
	printf( "0x%X\n", i );
	printf( "bit[%u] : %i\n", bitNumber, ( uint )BIT_VAL( i, bitNumber ) );
	
	i = RESET_BIT( i, bitNumber );
	printf( "0x%X\n", i );
	printf( "bit[%u] : %i\n", bitNumber, ( uint )BIT_VAL( i, bitNumber ) );
	
	puts( "====" );
	i = 0x0u; bitNumber = 31u;
	i <<= bitNumber;
	i = SET_BIT( i, bitNumber );
	printf( "0x%X\n", i );
	printf( "bit[%u] : %i\n", bitNumber, ( uint )BIT_VAL( i, bitNumber ) );
	
	i = RESET_BIT( i, bitNumber );
	printf( "0x%X\n", i );
	printf( "bit[%u] : %i\n", bitNumber, ( uint )BIT_VAL( i, bitNumber ) );
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	foo();
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
