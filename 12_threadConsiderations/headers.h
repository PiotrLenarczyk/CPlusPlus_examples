//biblioteki STL
#include <iostream>
#include <vector>
#include <thread> 
#include <math.h> //sqrt
#include <time.h> //clock()
#include <stdlib.h> //system
#include <sstream>
#include <QVector>

using namespace std;

class A 
{
public:
    void foo(int n) { cout << n << endl; }
};

class B
{
public:
    vector< double > n;
    void foo(  ) 
    {
        for ( int i = 0; i < ( int )n.size(); i++ )
            n[ i ] = pow( sqrt( n[ i ] ), 0.2381 );
    }
};

class Bsum
{
public:
    vector< float > a;
    vector< float > b;
    vector< float > c;
    void sum(  ) 
    {
        for ( int i = 0; i < ( int )a.size(); i++ )
            c[ i ] = a[ i ] + b[ i ];
    }
};
