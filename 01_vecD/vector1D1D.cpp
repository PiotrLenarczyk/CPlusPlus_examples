#include "headers.h"

int main()
{
//  2D matrix as 1D vector of 1D vectors ( vector1D1D vel vector2D vel matrix )
    int vecSizeRows = 10;/*Y*/ int vecSizeCols = 4;/*X*/ float vec1D1DVal = 0.2f;
    vector < vector< float > > vec1D1D = vector1D1D( vecSizeRows, vecSizeCols, vec1D1DVal ); 
    //vector [ 10rows x 4cols ]
    for ( int y = 0; y < vecSizeRows; y++ )
        for ( int x = 0; x < vecSizeCols; x++ )
            cout << "vec1D1D[y=" << y << "][x=" << x << "]: " << vec1D1D[ y ][ x ] << endl;
        
    return 0;
}
