#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int NUMBER_OF_ITEMS = 10;

int main()
{
    int X = 4, Y = 51;
    vector < float > vec ( NUMBER_OF_ITEMS, 0.1f );
    vec[ 3 ] = 5;
    ofstream data_file;      // pay attention here! ofstream
    data_file.open( "imFile.bin", ios::out | ios::binary );
    data_file.write( reinterpret_cast< char* >( &X ), 1 * sizeof( int ) ); 
    data_file.write( reinterpret_cast< char* >( &vec[ 0 ] ), vec.size() * sizeof( float ) ); 
    data_file.write( reinterpret_cast< char* >( &Y ), 1 * sizeof( int ) ); 
    data_file.close();
    
    vector < float > vecIn; int XIn, YIn;
    ifstream data_fileIn;      // NOW it's ifstream
    data_fileIn.open( "imFile.bin", ios::in | ios::binary );
    vecIn.resize( NUMBER_OF_ITEMS );
    data_fileIn.read( reinterpret_cast< char* >( &XIn ), 1 * sizeof( int ) );
    data_fileIn.read( reinterpret_cast< char* >( &vecIn[ 0 ] ), NUMBER_OF_ITEMS * sizeof( float ) );
    data_fileIn.read( reinterpret_cast< char* >( &YIn ), 1 * sizeof( int ) );
    data_fileIn.close();
    
    for ( int i = 0; i < NUMBER_OF_ITEMS; i++ )
        cout << "vecIn[ " << i << " ]: " << vecIn[ i ] << endl;
    cout << "XIn: " << XIn << endl;
    cout << "YIn: " << YIn << endl;
    
    return 0;
}
