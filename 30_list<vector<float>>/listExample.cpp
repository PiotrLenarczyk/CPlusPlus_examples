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

const unsigned no = 8000;
const vector< float > vecInit( no, 0.0f );
list < vector < float > > listVec( 15, vecInit );
typedef list < vector < float > >::iterator listVecPtr;

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
    
    listVecPtr  lVecPtr = listVec.begin();
    cout << "list vec max size: " << listVec.max_size() << endl;
    cout << "first list vecor element: " << ((vector< float >)(*lVecPtr)).at( 0 ) << endl;
    
    return 0;
}
