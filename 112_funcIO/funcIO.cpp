#include <cstdio> 
#define CAST( destPtr ) ( destPtr )( const void* )
using namespace std;
typedef __uint32_t uint;
typedef unsigned char byte;
uint i = 0x0;
//======================================================================
//function types
enum: int 	
{	CONTROL = 0x1, 
	PROCESS, 
	SEND, 
	RECEIVE,
}FUNC_TYPE;

char* FUNC_TYPENAME[0x20] 
{	( char* )"NULL",
	( char* )"CONTROL", 
	( char* )"PROCESS",
	( char* )"SEND",
	( char* )"RECEIVE",
};
//======================================================================
//function input - output handler
typedef struct
{	//data
	uint 	size;
	void* 	data;	//any object
}IO;
IO IN 		= { 0x10, ( char* )"in data" };
IO OUT 		= { 0x10, ( char* )"out data" };
IO EMPTY 	= { 0x0, NULL };

//function struct
typedef struct
{	char	name[ 0x20 ];
	int 	type;
	int 	command;	//optional
	IO*		funcOut;
	IO*		funcIn;
	void 	( *funcPtr )( IO* funcOut, IO* funcIn );
	void 	run( void ) 
			{  	printf( "====\n[%s]%s();\n====\n", FUNC_TYPENAME[ type ], name );
				funcPtr( funcOut, funcIn ); 
			};
}FUNCTION;
//======================================================================
//generic functions made in one fashion: void (*)(IO*,IO*)
void FOO( IO* out, IO* in )
{	if ( in->size )
		printf( "input: \n\tsize : 0x%X \n\tdata: [%s]\n", in->size, (char*)in->data );
	//optional return stuff:
	if ( out->size )
		printf( "output: \n\tsize : 0x%X \n\tdata: [%s]\n", out->size, (char*)out->data );
};//FOO()

FUNCTION allFuncs[] = 
{	{ "first", SEND, 0x0, &EMPTY, &EMPTY, &FOO },
	{ "second", SEND, 0x0, &EMPTY, &EMPTY, &FOO },
	{ 0x0 }
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	//local data exchange
	IO someInput = { 0x10, ( void* )"Hello World!" };
	IO someOutput = { 0x0, NULL };
	FUNCTION foo = { "foo", SEND, 0x0, &EMPTY, &someInput, &FOO };
	foo.run();
	
	//global data exchange
	OUT = { 0x20, ( void* )"sample output from func!" };
	FUNCTION bar = { "bar", RECEIVE, 0, &OUT, &EMPTY, &FOO };
	bar.run();
	
	i = 0x0; while( allFuncs[ i ].type )
	{	allFuncs[ i ].run();
		i++;
	};
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
