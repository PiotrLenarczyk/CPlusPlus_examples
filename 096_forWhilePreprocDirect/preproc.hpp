#pragma once
//==============================================================================================
#define STRINGIZE(arg)					#arg
#define CONCATENATE(arg1, arg2) 		arg1##arg2
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
#define RMW_( VARIABLE, ind )   		{ VARIABLE[ ind ] += VARIABLE[ ind ]; }
//--------------------------------------------------------------------------------------------
//============================================================================================
