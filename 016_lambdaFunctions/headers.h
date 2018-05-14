//STL
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

    //part of calculations compiler can make f.e. Look Up Tables
    constexpr long int someGlobal = 0 + 0;
    long int vecSum = 0;
    
    //partial functions
    double matFun( double &d ) { return pow( sqrt( d ), 0.542 ); }
    
    //lambda functions
    void LambdaSqrttVec( vector <double> &v ) { for_each( v.begin(), v.end(), []( double &x ) { sqrt( x ); } ); }
    void LambdaMatFunVec( vector <double> &v ) { for_each( v.begin(), v.end(), []( double &x ) { matFun( x ); } ); }
    void LambdaMatFun2Vec( vector <double> &v ) { for_each( v.begin(), v.end(), []( double &x ) { pow( sqrt( x ), 0.542 ); } ); }
    void LambdaVecSum( vector <double> &v ) { for_each( v.begin(), v.end(), []( double &x ) { vecSum += x; } ); }
