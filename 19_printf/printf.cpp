//STL
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int vecRows( 3 ), vecCols( 4 ); vector < float > vec( vecCols, 0.01f );
    vector < vector < float > > vecVec( vecRows, vec );
    for ( int y = 0; y < vecRows; y++ )
    {
        printf( "vecVec[Y=%d][X=:]: [", y );
        for ( int x = 0; x < vecCols; x++ )
        {
            printf( " %f ", vecVec[ y ][ x ]  );
        }
        printf( "]\n" );
    }
    
    return 0;
}
