#include <iostream>
#include <typeinfo>

using namespace std;
typedef uint32_t uint;
size_t i = 0;

struct returnStruct
{
    uint retVal;
    uint retStatus;
};

inline int printArg( int* in, int in2 ){ printf( "function Arg1=%i; Arg2=%i\n", *in, in2 ); return 0; };

returnStruct printFunc( void )
{ 
    printf( "some print out\n" );
    returnStruct retS { 1,10 };
    return retS;
};

int main( void )
{
	auto fPtr = &printArg;
    cout << "fPtr: " << typeid( fPtr ).name() << endl;
    int k = -1; int* iPtr = &k;
    cout << "i: " << typeid( k  ).name() << "\n" << "iPtr: " << typeid( iPtr ).name() << endl;
	returnStruct s = printFunc();
    cout << s.retVal << ", "<< s.retStatus << endl;
    
	return 0;
};
