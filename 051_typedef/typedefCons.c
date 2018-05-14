#include <iostream>
using std::cout; using std::endl;
typedef unsigned int uint;

int main( void )
{
	uint a[ 1 ] = { 0 };
	float b = 1;
	a[ 0 ] = uint( b );
	cout << "a[ 0 ]: " << a[ 0 ] << endl;

	return 0;
}

