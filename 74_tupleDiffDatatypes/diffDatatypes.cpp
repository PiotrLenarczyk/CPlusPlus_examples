#include <iostream>
#include <tuple>
#include <typeinfo>

using namespace std;
typedef uint32_t uint;
uint i = 0;

//	FUNCTIONS POINTERS TYPE DEFINITIONS
typedef int( *F_PTR1 )( int&, int& );
typedef int( *F_PTR2 )( float&, float& );
typedef int( *F_PTR3 )( int&, float& );
//	FUNCTION POINTERS STRUCT
typedef struct 
{	F_PTR1 f1;
	F_PTR2 f2;
	F_PTR3 f3;
} FuncPtrs;

//some functions
int foo( int &a, int &b ) { return printf( "Hi!\n" ); };
int bar( float &a, float &b );
int bar2( int &a, float &b );

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{//	FIRST ATTEMPT
	auto tupleDifferentDatatypes = make_tuple( &foo, &bar, &bar2 );
	cout << "tuple datatype with index [1]:" << typeid( get< 0 > ( tupleDifferentDatatypes ) ).name() << endl;

//	SECOND ATTEMPT
	FuncPtrs funcPtrs = { &foo, &bar, &bar2 };
	cout << "struct datatype with index[1] : " << typeid( funcPtrs.f1 ).name() << endl;
	int a = 0; int b = 0; funcPtrs.f1( a, b ); //function call syntax

	return 0;
}; //end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
