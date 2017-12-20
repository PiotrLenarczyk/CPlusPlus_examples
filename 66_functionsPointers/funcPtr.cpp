#include <iostream>
#include <string>
#include <map>
#include <string.h>
#include <typeinfo>

using namespace std;
typedef uint32_t uint;
size_t i = 0;

template < typename FuncPtr > inline void useFunc( FuncPtr funcName ){ funcName(); };
inline int printA( void ){ printf( "function A\n" ); return 0; };
inline int printB( void ){ printf( "function B\n" ); return 0; };
inline int printC( void ){ printf( "function C\n" ); return 0; };
inline int printArg( int* in, int in2 ){ printf( "function Arg1=%i; Arg2=%i\n", *in, in2 ); return 0; };

void printString( void ) {printf( "void func\n" );};
int printString2( char* ptr ) {printf( "void func str: %s\n", ptr ); return 0;};
int main( void )
{

	//auto fPtr = &printString2;
	int ( *funPtr )( char* )  = &printString2;
    cout << "funPtr: " << typeid( funPtr ).name() << endl;
	map < string, void ( * )() > mapStr
    {
        { "printString", &printString }
    };
	char tmp[] = "printString";
	mapStr[ tmp ]();
   
//1st method - template with function pointer typename
	useFunc( &printA );

//2nd method - typedef function pointer

	auto fPtr = &printString2;
	string funcPtrName =  typeid( fPtr ).name();
    cout << "fPtr: " << funcPtrName << endl;

	typedef int ( *FunIntCharPtr )( char* );
	FunIntCharPtr cPtr = &printString2;

    typedef int ( *Int_VoidTdf )();  
//    Int_VoidTdf ptr; ( ptr = &printB )();     //ptr = &printA; ptr();
	typedef int ( *Int_PtrIntTdf )( int* );
	typedef int ( *Int_PtrIntTdf )( int* );

//3rd method - map strings of functions name to functions pointers
    char str[] = "printC";
    map < string, int ( * )() > mapFuncsWithoutArgs
    {
        { "printA", &printA },
        { "printB", &printB },
        { "printC", &printC }
    };
	if ( mapFuncsWithoutArgs.find( str ) != mapFuncsWithoutArgs.end() )
	    mapFuncsWithoutArgs[ str ]();

//      the same of above + functions with arguments
        map < string, int ( * )( int*, int ) > mapFuncsTwoArgs
        {
            { "printArg", &printArg }
        };
        char str2[] = "printArg"; int arg = 8;
        mapFuncsTwoArgs[ str2 ]( &arg, 11U );

//4rd method preprocessor directives
	#define PTR *
	#define AMPERSAND &
    #define MKSTR( x ) # x  
	#define CONCAT( x, y ) x ## y
	cout << MKSTR( print ) << " " << MKSTR( Arg ) << endl;
	int tmpArg = -1;
	cout << "Function executed with output: "
		 <<	( CONCAT( print, Arg ) )( AMPERSAND tmpArg, 1 ) << endl;

	return 0;
}
