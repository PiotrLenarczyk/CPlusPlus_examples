//STL
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm> //vector.fill

using namespace std;

int main( void )
{
    map< float, float > mapInd; //key-ordered map; keys iterator is sorted!; key1 = sparse image row index; value1/key2 = rowVectorBeggining; value2 = dataVector;
    unordered_map< float, vector < float > > mapRowBeg; //key-unordered map ( unordered maps are more effective for intact key-major accesses )
    vector < float > tmpData;
    float someRowBeg( 0 );
    for ( float i = 0; i < 10; i++ )
    {
        someRowBeg = ( int( i*i*i*i ) % 70 );        
//                                           ind  someRowBeginnings
        mapInd.insert( pair< float, float >(  i, someRowBeg ) );        
        tmpData.resize( int( i + 3 ) ); fill( tmpData.begin(), tmpData.end(), 1.17f * i );
//                                                  someRowBeginnings  exampleData
        mapRowBeg.insert( pair< float, vector< float > >( someRowBeg, tmpData ) );
    }
    
    cout << "mapInd contains:\n";
    for ( auto& x1: mapInd )
        cout << "[" << x1.first << "] : [" << x1.second << "]" << endl;
    cout << "u-mapRowBeg contains:\n";
    for ( auto& x2: mapRowBeg )
        cout << "[" << x2.first << "]: vector.size()=" << x2.second.size() << " dataVector.at(0)=" << x2.second[ 0 ] << endl;
    
    return 0;
}
