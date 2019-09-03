//https://barrgroup.com/Embedded-Systems/How-To/C-Function-Pointers 
#include <cstdio> 
using namespace std;

//=============== FUNCTIONS	============================================
#define DUMMY_NO	0x0
void* dummy( void* in )
{	return 0;
};

#define FOO_NO	0x1
void* foo( void* in )
{	puts( "from foo();" );
};

#define BAR_NO	0x2
void* bar( void* in )
{	puts( "from bar();" );
};

//====
//... milions of functions
//====

#define BAZ_NO	0x4
void* baz( void* in )
{	puts( "from baz();" );
};

//=============== FUNCNAMES	============================================
#define MAX_FUNCNAME_SIZE	0x20
unsigned char funcNames[][ MAX_FUNCNAME_SIZE ] = 
{	"void* dummy( void* in )",	//DUMMY_NO
	"void* foo( void* in )",	//FOO_NO
	"void* bar( void* in )",	//BAR_NO
	"void* dummy( void* in )",	//0x3
	"void* baz( void* in )",	//BAZ_NO
};

//=============== FUNCCALLS	============================================
#define FUNCNAME( funcNo )	printf( "%s;\n", funcNames[ funcNo ] );
#define CALL( funcNo, arg ) caller[ funcNo ]( arg );

void* ( *caller[] )( void* ) = 
{ 	dummy,						//DUMMY_NO
	foo, 						//FOO_NO
	bar,						//BAR_NO
	dummy,						//0x3
	baz,						//BAZ_NO
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	int arg; arg = 0x0;
	
	FUNCNAME( FOO_NO );
	puts( "" );
	//independly from size of functions set, each call cost is constant:
	
	CALL( FOO_NO, &arg );
	CALL( BAZ_NO, &arg );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
