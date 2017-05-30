/* https://www.youtube.com/watch?v=nDj35pMLBQE */
//STL
#include <iostream>

using namespace std;

extern "C" int SomeFunction( int i );

int main( void )
{
	cout << "result: " << SomeFunction( 100 ) << endl;

	return 0;
}

