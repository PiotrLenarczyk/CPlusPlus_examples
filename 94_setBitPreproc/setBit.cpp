//https://stackoverflow.com/questions/1872220/is-it-possible-to-iterate-over-arguments-in-variadic-macros
#include <stdio.h>
using namespace std;
typedef unsigned char byte;
typedef __uint32_t uint;
uint i = 0x0u, a = 0x0u, bitNumber;
//==============================================================================================
#define STRINGIZE(arg)				#arg
#define CONCATENATE(arg1, arg2) 	arg1##arg2
#define __FE0_1(what, x, ...) 	what(x)
#define __FE0_2(what, x, ...)	what(x);	__FE0_1(what,  __VA_ARGS__);
#define __FE0_3(what, x, ...)  	what(x);	__FE0_2(what,  __VA_ARGS__);
#define __FE0_4(what, x, ...) 	what(x);	__FE0_3(what,  __VA_ARGS__);
#define __FE0_5(what, x, ...)	what(x);	__FE0_4(what,  __VA_ARGS__);
#define __FE0_6(what, x, ...)	what(x);	__FE0_5(what,  __VA_ARGS__);
#define __FE0_7(what, x, ...)	what(x);	__FE0_6(what,  __VA_ARGS__);
#define __FE0_8(what, x, ...)	what(x);	__FE0_7(what,  __VA_ARGS__);
#define __FE0_NARG(...) 			__FE0_NARG_(__VA_ARGS__, __FE0_RSEQ_N())
#define __FE0_NARG_(...) 		__FE0_ARG_N(__VA_ARGS__) 
#define __FE0_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N 
#define __FE0_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0
#define __FE0_(N, what, x, ...)	CONCATENATE(__FE0_, N)(what, x, __VA_ARGS__)
#define __FE0(what, x, ...) 		__FE0_(__FE0_NARG(x, __VA_ARGS__), what, x, __VA_ARGS__)

#define __FE1_1(what, some, x, ...) 	what(some, x)
#define __FE1_2(what, some, x, ...)		what(some, x);	__FE1_1(what, some,  __VA_ARGS__);
#define __FE1_3(what, some, x, ...)  	what(some, x);	__FE1_2(what, some,  __VA_ARGS__);
#define __FE1_4(what, some, x, ...) 	what(some, x);	__FE1_3(what, some,  __VA_ARGS__);
#define __FE1_5(what, some, x, ...)		what(some, x);	__FE1_4(what, some,  __VA_ARGS__);
#define __FE1_6(what, some, x, ...)		what(some, x);	__FE1_5(what, some,  __VA_ARGS__);
#define __FE1_7(what, some, x, ...)		what(some, x);	__FE1_6(what, some,  __VA_ARGS__);
#define __FE1_8(what, some, x, ...)		what(some, x);	__FE1_7(what, some,  __VA_ARGS__);
#define __FE1_NARG(...) 				__FE1_NARG_(__VA_ARGS__, __FE1_RSEQ_N())
#define __FE1_NARG_(...) 				__FE1_ARG_N(__VA_ARGS__) 
#define __FE1_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N 
#define __FE1_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0
#define __FE1_(N, what, some, x, ...)	CONCATENATE(__FE1_, N)(what, some, x, __VA_ARGS__)
#define __FE1(what, some, x, ...) 		__FE1_(__FE1_NARG(x, __VA_ARGS__), what, some, x, __VA_ARGS__)
//============================================================================================
//--------------------------------------------------------------------------------------------
//------------------------	MACRO KERNELS ----------------------------------------------------
//--------------------------------------------------------------------------------------------
#define PRINT_(text, arg)				{ printf( STRINGIZE(text)" : %i\n", arg ); }
#define SET_BIT_( VARIABLE, bitNo )   	{ VARIABLE = ( ( ( VARIABLE >> bitNo ) & 0x1u ) != 0x1u ) 	\
												? VARIABLE |= 0x1u << bitNo 						\
												: VARIABLE = VARIABLE;								\
										}
#define RESET_BIT_( VARIABLE, bitNo ) 	{ VARIABLE = ( ( ( VARIABLE >> bitNo ) & 0x1u ) != 0x0u )	\
												? VARIABLE &= ~( 0x1u << bitNo )					\
												: VARIABLE = VARIABLE;								\
										}
#define BIT_VAL_( VARIABLE, bitNo ) ( VARIABLE >> bitNo ) & 0x1u
//--------------------------------------------------------------------------------------------
//============================================================================================
#define PRINT(arg)PRINT_(int, arg)
#define SET_BIT(bitNo)SET_BIT_(VARIABLE, bitNo)
#define RESET_BIT(bitNo)RESET_BIT_(VARIABLE, bitNo)
#define SET_2BITS( VARIABLE, arg1, arg2 )	{	SET_BIT_( VARIABLE, arg1 ); 						\
												SET_BIT_( VARIABLE, arg2 ); 						\
											}
//============================================================================================
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void foo( void );
int main( void )
{//////		FIRST ATTEMPT
	__FE1( SET_BIT_, a, 0, 1 );
	printf( "0x%X\n", a );
	
//////	SECOND ATTEMPT
	//foo();
	
//////	THIRD ATTEMPT
	//__FE0(PRINT, 0xDu, 0xCu);
	
//////	FOURTH ATTEMPT
//#define VARIABLE a
	//__FE0(SET_BIT, 0x0u, 0x1u, 0x7u);
//#undef VARIABLE
	//printf( "0x%X\n", a );
	//RESET_BIT_( a, 0x7u )
	//printf( "0x%X\n", a );
	
//////	FIFTH ATTEMPT - trivial
	//a = 0x0u;
	//SET_2BITS( a, 0, 1 );
	//printf( "0x%X\n", a );
	
//////	SIXTH ATTEMPT
	//a = 0x0u;
	//SET_BIT_( a, 0x0u );SET_BIT_( a, 0x1u )
	//printf( "0x%X\n", a );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void foo( void )
{	i = 0x0u; bitNumber = 31u;
	puts( "====" );
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
