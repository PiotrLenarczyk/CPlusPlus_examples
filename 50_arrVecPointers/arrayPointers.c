#include <iostream>

using namespace std;

void printArr( float *arrIn );
size_t i = 0;
typedef unsigned int uint;

int main( void )
{
	float a[ 3 ] = { 0.0f, 1.0f, 2.0f };
	uint arrLength = sizeof( a ) / sizeof( float );
	cout << "arrLength: " << arrLength << endl;
	for ( i = 0; i < arrLength; i++ )
		printArr( &a[ i ] );
	cout << "Array value called by name (zero index): " << endl;
	printArr( a );

	return 0;
}

void printArr( float *arrIn )
{
	cout << *arrIn << endl;
}

