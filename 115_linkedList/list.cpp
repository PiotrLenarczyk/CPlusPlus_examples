#include <cstdio> 
#define CAST( destPtr ) ( destPtr )( const void* )
using namespace std;
typedef __uint32_t uint;
typedef unsigned char byte;
uint i = 0x0;

#define SO_MANY_VARIABLES 	0x400	
#define SIZE( ptr )			( int )(sizeof( ptr ) / \
							( sizeof( ptr[ 0 ] ) ))
#define SPACE_LEFT( ptr )	(int)( SO_MANY_VARIABLES - SIZE( ptr ) )
#define CHECK_SIZE( ptr )	if ( 	(int)SIZE( ptr ) > 					\
									(int)SO_MANY_VARIABLES )			\
							{ puts( "LIST SIZE HANDLER" ); while( 1 ); };
unsigned char myVariables[ SO_MANY_VARIABLES ];

//====
//typedef struct
//{	unsigned short intPart;		//2B assumed; constant precision error
	//__fp16 floatPart;	//2B assumed; 
						//constant precision error 2E-10 {-0.9(9); +0.9(9)};
						//overflow and underflow protection +-128
//} VariableHalf_TypeDef;
//...
//====

typedef struct
{	int intPart;		//4B assumed; constant precision error
	float floatPart;	//4B assumed; 
						//constant precision error 2E-23 {-0.9(9); +0.9(9)};
						//overflow and underflow protection +-32768
} Variable_TypeDef;

typedef struct
{	Variable_TypeDef *previousPtr;
	Variable_TypeDef *nextPtr;
} LinkedList_TypeDef;

typedef struct
{	long intPart;		//8B assumed
	double floatPart;	//8B assumed
						//constant precision error 2E-52 {-0.9(9); +0.9(9)};
						//overflow and underflow protection +-someBigNumber
} VariableLong_TypeDef;

typedef struct
{	VariableLong_TypeDef *previousPtr;
	VariableLong_TypeDef *nextPtr;
} LinkedListLong_TypeDef;


void foo( void )
{	Variable_TypeDef *vPtr;
	vPtr = (Variable_TypeDef*)myVariables;
	vPtr[ 0 ] = { 1, 0.1f };	//1.1f
	vPtr[ 1 ] = { 1, -0.7f }; 	//0.3f
	vPtr[ 2 ] = { 3, 0.14f };	//3.14f
	vPtr[ 3 ] = { 2, 0.72f };	//2.72f

	int lSize; 
	LinkedList_TypeDef l[ SO_MANY_VARIABLES / 
						  (sizeof( Variable_TypeDef )) ] = 
	{	{ &vPtr[ 0 ], &vPtr[ 1 ] },	//first list item
		{ &vPtr[ 1 ], &vPtr[ 3 ] },	//second list item
	};
	lSize = 0x2;
	for ( int i = 0x0; i < 0x4; i++ )	//presentation purposes only
		printf( "vPtr[%i] : %d+%f\n", i, vPtr[i].intPart, vPtr[i].floatPart );
	puts("");
	printf( "whole list size : %d\n", SIZE( l ) );
	for ( int i = 0x0; i < lSize; i++ )
	{	printf( "l[%i].previous : %d+%f\n", i, (l[i].previousPtr)->intPart, (l[i].previousPtr)->floatPart );
		printf( "l[%i].next : %d+%f\n\n", i, (l[i].nextPtr)->intPart,  (l[i].nextPtr)->floatPart );
	};
};//foo()

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	foo();

	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
