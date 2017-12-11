#include <iostream>
#include <string>
#include <map>

using namespace std;
typedef uint32_t uint;
size_t i = 0;

template < typename FuncName > inline void useFunc( FuncName funcName ){ funcName(); };
inline int printA( void ){ printf( "function A\n" ); return 0; };
inline int printB( void ){ printf( "function B\n" ); return 0; };
inline int printC( void ){ printf( "function C\n" ); return 0; };
inline int printArg( int* in, int in2 ){ printf( "function Arg1=%i; Arg2=%i\n", *in, in2 ); return 0; };

int main( void )
{
   
//1st method - template with function pointer typename
	useFunc( &printA );
//2nd method - typedef function pointer
    typedef int ( *FunctionTdf )();  
    FunctionTdf ptr; ( ptr = &printB )();     //ptr = &printA; ptr();
//3rd method - map strings of functions name to functions pointers
    char str[] = "printC";
    map < string, int ( * )() > mapFuncsWithoutArgs
    {
        { "printA", &printA },
        { "printB", &printB },
        { "printC", &printC }
    };
    mapFuncsWithoutArgs[ str ]();
//      the same of above + functions with arguments
        map < string, int ( * )( int*, int ) > mapFuncsTwoArgs
        {
            { "printArg", &printArg }
        };
        char str2[] = "printArg"; int arg = 8;
        mapFuncsTwoArgs[ str2 ]( &arg, 11U );
    
	return 0;
}
