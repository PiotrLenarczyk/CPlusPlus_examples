//STL
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int vecRows( 3 ), vecCols( 4 );
    vector < float > vec( vecCols, 0.01f );
    vector < vector < float > > vecVec( vecRows, vec );
    
    vector < float > vecTmp( vecCols, 0.0f ); //access row-major order vector instead of single value of vector1D1D
    for ( int y = 0; y < vecRows; y++ )
    {
        copy( vecVec[ y ].begin(), vecVec[ y ].end(), vecTmp.begin() ); //trivially paralelizable vecRows-times if vecCols.size() > 8000 ( at Intel i7 2660K; i7-5500U -> CUDA 3.5 )
        for ( int x = 0; x < vecCols; x++ )
            cout << "vecVec[" << y << "][" << x << "]: " << vecTmp[ x ] << endl;
    }
    
    return 0;
}
