#include <stdio.h>
using namespace std;
typedef unsigned char byte;
typedef __uint32_t uint;
uint i = 0x0u, a = 0x0u, bitNumber;
//==============================================================================================
#define STRINGIZE(arg)				#arg
#define CONCATENATE(arg1, arg2) 	arg1##arg2
#define FOR_EACH_1(what, x, ...) 	what(x)
#define FOR_EACH_2(what, x, ...)	what(x);	FOR_EACH_1(what,  __VA_ARGS__);
#define FOR_EACH_3(what, x, ...)  	what(x);	FOR_EACH_2(what,  __VA_ARGS__);
#define FOR_EACH_4(what, x, ...) 	what(x);	FOR_EACH_3(what,  __VA_ARGS__);
#define FOR_EACH_5(what, x, ...)	what(x);	FOR_EACH_4(what,  __VA_ARGS__);
#define FOR_EACH_6(what, x, ...)	what(x);	FOR_EACH_5(what,  __VA_ARGS__);
#define FOR_EACH_7(what, x, ...)	what(x);	FOR_EACH_6(what,  __VA_ARGS__);
#define FOR_EACH_8(what, x, ...)	what(x);	FOR_EACH_7(what,  __VA_ARGS__);
#define FOR_EACH_NARG(...) 			FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) 		FOR_EACH_ARG_N(__VA_ARGS__) 
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N 
#define FOR_EACH_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0
#define FOR_EACH_(N, what, x, ...)	CONCATENATE(FOR_EACH_, N)(what, x, __VA_ARGS__)
#define FOR_EACH(what, x, ...) 		FOR_EACH_(FOR_EACH_NARG(x, __VA_ARGS__), what, x, __VA_ARGS__)
//============================================================================================
#define PRINT_(text, arg)			{ printf( STRINGIZE(text)" : %i\n", arg ); }
#define PRINT(arg)PRINT_(int, arg)
//--------------------------------------------------------------------------------------------
//------------------------	MACRO KERNELS ----------------------------------------------------
//--------------------------------------------------------------------------------------------
#define SET_BIT_( VARIABLE, bitNo )   { VARIABLE = ( ( ( VARIABLE >> bitNo ) & 0x1u ) != 0x1u ) 	\
												? VARIABLE |= 0x1u << bitNo 						\
												: VARIABLE = VARIABLE;								\
								 }
#define RESET_BIT_( VARIABLE, bitNo ) { VARIABLE = ( ( ( VARIABLE >> bitNo ) & 0x1u ) != 0x0u )		\
												? VARIABLE &= ~( 0x1u << bitNo )					\
												: VARIABLE = VARIABLE;								\
								 }
#define BIT_VAL_( VARIABLE, bitNo ) ( VARIABLE >> bitNo ) & 0x1u
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
#define SET_BIT(bitNo)SET_BIT_(VARIABLE, bitNo)
#define RESET_BIT(bitNo)RESET_BIT_(VARIABLE, bitNo)
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void foo( void );
int main( void )
{////		FIRST ATTEMPT
	foo();
	
////	SECOND ATTEMPT
	FOR_EACH(PRINT, 0xDu, 0xCu);
	
////	THIRD ATTEMPT
#define VARIABLE a
	FOR_EACH(SET_BIT, 0x0u, 0x1u, 0x7u);
#undef VARIABLE
	printf( "0x%X\n", a );
	RESET_BIT_( a, 0x7u )
	printf( "0x%X\n", a );
////	FOURTH ATTEMPT
	a = 0x0u;
	SET_BIT_( a, 0x0u );SET_BIT_( a, 0x1u )
	printf( "0x%X\n", a );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void foo( void )
{	i = 0x0u; bitNumber = 31u;
	SET_BIT_( i, bitNumber );
	printf( "0x%.8X\n", i );
	printf( "bit[%u] : %i\n", bitNumber, ( uint )BIT_VAL_( i, bitNumber ) );
	
	RESET_BIT_( i, bitNumber );
	printf( "0x%.8X\n", i );
	printf( "bit[%u] : %i\n", bitNumber, ( uint )BIT_VAL_( i, bitNumber ) );
	
	puts( "====" );
	i = 0x0u; bitNumber = 31u;
	i <<= bitNumber;
	SET_BIT_( i, bitNumber );
	printf( "0x%.8X\n", i );
	printf( "bit[%u] : %i\n", bitNumber, ( uint )BIT_VAL_( i, bitNumber ) );
	
	RESET_BIT_( i, bitNumber );
	printf( "0x%.8X\n", i );
	printf( "bit[%u] : %i\n", bitNumber, ( uint )BIT_VAL_( i, bitNumber ) );
	
	puts( "====" );
};//foo()
