#include "headers.h"

vector< vector< float > > vector1D1D( int &vecSizeRows, int &vecSizeCols, float &vecVal )
{
    //square matrix
    vector< float > vec1DTmp( vecSizeCols, vecVal );
    vector < vector< float > > vec1D1D( vecSizeRows, vec1DTmp );
    return vec1D1D;
}
