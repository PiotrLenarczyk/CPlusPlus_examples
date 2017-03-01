#include "headers.h"
//vector are mostly more usable than array!

int main()
{
    //C arrays:
    //1) no size info
    //2) no size controll and resizing
    int tab[ 5 ] = { 0, 1, 2, 3, 4 };
    for ( int &x : tab )
        x *= 2;
    cout << "tab[1]: " << tab[ 1 ] << endl;
    
    //STL vector container
    //1) static vector is ordered in memory ( values are sequential )
    //2) useful container functions
    //3) proportionate effectiveness
    vector <double> vec( 500000000 );
    for ( size_t i = 0; i < vec.size(); i++ ) vec[ i ] = i;
//     fastLambdaSqrttVec( vec );
//     fastLambdaMatFun2Vec( vec );
    LambdaVecSum( vec );
    cout << "vec[1]:" << ( double )vecSum / ( long int )vec.size() << endl;
    vecSum = 0;
    
    return 0;
}
