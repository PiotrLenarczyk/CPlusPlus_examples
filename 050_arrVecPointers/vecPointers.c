#include <iostream>
#include <vector>

using namespace std;
typedef unsigned int uint;

size_t i = 0;
uint N = 1E6;

void printVec( vector < float > &vecIn );
void pointVec( float *vecIn );

int main( void )
{
	vector < float > vec( N, 0.0f );
	cout << "vec zero index: " << endl;
	printVec( vec );

	vec[ 1 ] = 1.0f;
	cout << "Passed vector value: " << endl;
	pointVec( &vec[ 0 ] );

	return 0;
}

void printVec(  vector< float > &vecIn )
{
	cout << vecIn[ 0] << endl;
}

void pointVec( float *vecIn )
{
	cout << vecIn[ 1 ] << endl;
}

