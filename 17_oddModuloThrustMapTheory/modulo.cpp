#include <iostream>
#include <vector>

using namespace std;

bool is_odd( int n ) {
    return n % 2 == 1;
}

int main()
{
    //as Map it is a pseudoMap for taking advantage of vector< vector > twoVariablesPairs
    //and temporary odd-even pseudoMap pairs, P.S. cost of reading rows != cost of reading cols!!!
    int dimSize = 4;
    int mapSize = 10;
    vector < float > vecMap( mapSize , 0.0f ); //cols-major order - data vector dims/value/attributes
    vector < vector < float > > vecMapPairs( 3, vecMap ); //row-major order key, value, ind + perFunctioVector reorderingTmpInd
    vector < vector < vector < float > > > vecMaps( dimSize, vecMapPairs );
    
    //even-odd scatter sets; needs gather postprocessing
    for ( int i = 0; i < 10; i++ )
        cout << "odd " << i << ": " << is_odd( i ) << endl;
    //P.S. less intuitive == more erroneus; less size && more information( PCA analysis )
    
    return 0;
}
