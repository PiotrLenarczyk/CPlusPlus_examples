//STL
#include <iostream>
#include <list>
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
    
    return 0;
}
