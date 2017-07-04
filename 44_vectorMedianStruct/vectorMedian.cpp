//STL
#include <vector>
#include <algorithm>

using std::vector;

struct vecMedian
{
    vector < float > vec;
    long long int vecMedian = 0;
    int isVecInRange() //normalize vec; please note that it is trivially paralizable
    {
        for ( size_t i = 0; i < vec.size(); i++ )
            if ( vec[ i ] < -1.0f || vec[ i ] > 1.0f )  //[ -1.0f; +1.0f ] gives best float accuracy and it is slightly faster float range
            {
                vector < float > vecCopy = vec;
                long long int vecMedianTmp = 0;
                sort( vecCopy.begin(), vecCopy.end() );
                vecMedianTmp = ( long long int )vecCopy[ vecCopy.size() / 2 ];
                for ( size_t ii = 0; ii < vec.size(); ii++ )
                    vec[ ii ] -= float( vecMedianTmp );
                vecMedian += vecMedianTmp;  //variable vecMedian holds median value with constant error
                break;
            }
        return 0;
    }
};

int main( void ) //In my electronic opinion it is usable mainly on GPU.
{
    vecMedian vec1;
    vec1.vec.resize( 100 );
    //do pro computational stuff
    //...
    //for example at the end of big loop
    vec1.isVecInRange();
    
    return 0;    
}

//P.S. quite accurate.
