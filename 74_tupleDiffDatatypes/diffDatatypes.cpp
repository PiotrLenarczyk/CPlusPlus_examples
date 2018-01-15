#include <iostream>
#include <tuple>
#include <typeinfo>

using namespace std;
typedef uint32_t uint;
size_t i = 0;

int foo( int &a, int &b );
int bar( float &a, float &b );
int bar2( int &a, float &b );

int main( void )
{
	auto tupleDifferentDatatypes = make_tuple( &foo, &bar, &bar2 );
	cout << "tuple datatype with index [1]:" << typeid( get< 1 > ( tupleDifferentDatatypes ) ).name() << endl;
	
	return 0;
}
