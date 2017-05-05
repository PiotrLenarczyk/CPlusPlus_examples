//STL
#include <iostream>
#include <list>
#include <vector>
/*
        https://www.youtube.com/watch?v=4-u9R40G1j8
*/ 

using namespace std;

typedef list < float > dList;
typedef list < float >::iterator dListPtr;

int main( void )
{
    dList l = { .31f, .914f, .1f };
    dListPtr lPtr = l.begin();
    for ( unsigned i = 0; i < ( unsigned )l.size(); i++ )
    {
        cout << "l[ " << i << "]: " << *lPtr << endl;
        lPtr++;
    }
    cout << "===== sorted: =====" << endl;
    l.sort();
    for ( dListPtr i = l.begin(); i != l.end(); i++ )
        cout << "l: " << *i << endl;
    
    vector < float > tmpVec( 10, 1.11f );
    list< vector< float > > lVec( 10, tmpVec );
    list< vector< float > >::iterator lVecPtr = lVec.begin();
    cout << "l[0][1]: " << (*lVecPtr)[ 1 ] << endl;
    cout << "l[0][1]: " << (*lVecPtr).at( 1 ) << endl;

    return 0;
}
//P.S. theretically list< vector< float > > should be more efficient than vector < vector < float > > vecD, in my personal opinion, but I am not sure.
