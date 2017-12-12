#include <iostream>
#include <string>
#include <map>
#include <string.h>

using namespace std;
typedef uint32_t uint;
size_t i = 0;

template < typename FuncPtr > inline void useFunc( FuncPtr funcName ){ funcName(); };
inline int printA( void ){ printf( "function A\n" ); return 0; };
inline int printB( void ){ printf( "function B\n" ); return 0; };
inline int printC( void ){ printf( "function C\n" ); return 0; };
inline int printArg( int* in, int in2 ){ printf( "function Arg1=%i; Arg2=%i\n", *in, in2 ); return 0; };

void printString( void ) {printf( "void func\n" );};

int main( void )
{
	string s = "start 1 2";
	char c[100]; strcpy( c, s.c_str());
	char t1[100]; strcpy( t1, s.c_str());
	char t2[100]; strcpy( t2, s.c_str());
	char* cPtr = 0; char separators[] = "  \n";
	cPtr = strtok( c, separators );
	i = 0;
	while ( cPtr != NULL )
	{
		if ( i == 0 ) strcpy( c, cPtr );
		if ( i == 1 ) strcpy( t1, cPtr );
		if ( i == 2 ) strcpy( t2, cPtr );
		cPtr = strtok( NULL, separators );
		i++;
	};
	printf( "c[%s], t1[%s], t2[%s]\n", c, t1, t2 );
return 0;
	map < string, void ( * )() > mapStr
    {
        { "printString", &printString }
    };
	char tmp[] = "printString";
	mapStr[ tmp ]();
   
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
	if ( mapFuncsWithoutArgs.find( str ) != mapFuncsWithoutArgs.end() )
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
