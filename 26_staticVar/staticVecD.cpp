//STL
#include <iostream>
#include <vector>
#include <time.h>

//namespace flags
using std::vector;
using std::cout;
using std::endl;

//tmp variable
uint16_t i = 0;

//global variables
uint16_t vecRows = 10;
uint16_t vecCols = 9000;
vector < float > vec1D( vecRows, 0.1f ); //1st global variable declaration 
vector < vector < float > > vec2D( vecCols, vec1D ); //speedup varyies depending on hardware should be not less than a ~10

int main( void )
{
	clock_t t( clock() );
// 	vector < float > vec1D( vecRows, 0.1f ); //2nd local variable declaration
// 	vector < vector < float > > vec2D( vecCols, vec1D ); //comment and try 1st
	for ( i = 0; i < 4; i++ )
		printf( "vec[ %i ][ 1 ]: %f\n", i, vec2D[ i ][ 1 ] );
	cout << "elapsed time: " << float( clock() - t ) / 1000 << "[ms]" << endl;

	return 0;
}
