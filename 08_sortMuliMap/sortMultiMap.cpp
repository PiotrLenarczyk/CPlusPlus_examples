//STL
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    multimap< float, string > mymm;
    multimap< float, string >::iterator it;

    mymm.insert( pair< float, string >(  10.0, "x1" )); //faster
    mymm.insert( make_pair( 10.0, "y1" ) ); //slower
    mymm.insert( make_pair( 10.1, "x2" ) );
    mymm.insert( make_pair( 10.1, "y2" ) );
    mymm.insert( make_pair( 8.1, "x3" ) );
    mymm.insert( make_pair( 8.1, "y3" ) );
    mymm.insert( make_pair( 21.8, "x4" ) );
    mymm.insert( make_pair( 21.8, "y4" ) );
    mymm.insert( make_pair( 1.31, "x5" ) );
    mymm.insert( make_pair( 1.31, "y5" ) );

    for ( float c = 8.2; c <= 11; c++ )
    {
        cout << "There are mymm: " << mymm.count( c ) << " elements with key " << c << ":";
        multimap< float, string >::iterator it;
        for ( it = mymm.equal_range( c ).first; it != mymm.equal_range( c ).second; ++it )
            cout << ' ' << ( *it ).second;
        cout << '\n';
    }
  
    cout << "mymm contains:\n";
    for ( it = mymm.begin();  it != mymm.end(); it++ )
        cout << ( *it ).first << " => " << ( *it ).second << '\n';
    
    multimap< float, float > mymm2;
    multimap< float, float >::iterator it2;

    mymm2.insert( pair< float, float >(  10.0, 1.0 ));
    mymm2.insert( make_pair( 10.0, 11.0 ) );
    mymm2.insert( make_pair( 10.1, 2.0 ) );
    mymm2.insert( make_pair( 10.1, 22.0 ) );
  
    cout << "mymm2 contains:\n";
    for ( it2 = mymm2.begin();  it2 != mymm2.end(); it2++ )
        cout << ( *it2 ).first << " => " << ( *it2 ).second << '\n';
    
    cout << "mymm2 XYZ contains:\n";
    float x = 0; float y = 0; float z = 0; bool flagy = false;
    for ( it2 = mymm2.begin();  it2 != mymm2.end(); it2++ )
    {
        x = ( *it2 ).first;
        if ( flagy )
        {
            z = ( *it2 ).second;
            flagy = false;
            cout << "x: " << x << " y: " << y << " z : " << z << endl;
        }
        else 
        {
            y = ( *it2 ).second;
            flagy = true;
        }
    }
    return 0;
}
