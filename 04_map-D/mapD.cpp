//STL
#include <iostream>
#include <map>
#include <stdlib.h> //int rand

using namespace std;

int main() //D-mapToSort 2D discrete matrix of values
{
    map< float, float > map1D;
    map< float, float >::iterator map1Diter = map1D.begin();
    for ( size_t i = 0; i < 11; i++ )//                //rand X                    rand value
        map1D.insert( pair< float, float >( 1 + ( float )( rand() % 155 ) , 1 + ( float )( rand() % 10 ) ) );
    
    map< float, map< float, float >::iterator > map2D;
    map1Diter = map1D.begin();
    for ( size_t i = 10; i < 20; i++ )
    {//                                                                     //rand Y
        map2D.insert( pair< float, map< float, float >::iterator >( 1 + ( float )( rand() % 155 ) , map1Diter ) );
        cout << "map1D[" << map1Diter->first << "]: " << map1Diter->second << endl;
        map1Diter++;
    }
    
    cout << "===============================\n";
    for ( auto& x: map2D )
        cout << "map2D[" << x.first << "]: map1D[" << x.second->first << "]: " << x.second->second << endl;
    cout << "===============================\n"; 
    cout << "Sorted insertion of vectorD\n";
    return 0;
}
