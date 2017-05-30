/* https://www.youtube.com/watch?v=nDj35pMLBQE */
//STL
#include <iostream>
#include <time.h>

using namespace std;

extern "C" int SomeFunction( int i );

int main( void )
{
	int in = 5;
	int out;
	clock_t t = clock();
	out = SomeFunction( in );
	cout << "CPU clocks: " << float( clock() - t ) << endl;

	cout << "result: " << out << endl;
	
	return 0;
}

