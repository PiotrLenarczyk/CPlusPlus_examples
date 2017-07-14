/* https://stackoverflow.com/questions/5840148/how-can-i-get-a-files-size-in-c */
//STL
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring> //memcpy

using namespace std;

const unsigned N = 5;
const unsigned D = 3;
vector < float > vecTmp( N, 1.131004f );
vector < vector < float > > vecD( D, vecTmp );
unsigned char chFloat[ D ][ N ][ sizeof( float ) ]; //data uchar 3D memory
void loadFloatsToCharArray( void )
{  
    size_t x, y;
    for ( y = 0; y < D; y++ )
        for ( x = 0; x < N; x++ )
            memcpy( chFloat[ y ][ x ], ( unsigned char* )( &vecD[ y ][ x ] ), sizeof( float ) );
}
void loadCharArrayToFloats( void )
{
    size_t x, y;
    for ( y = 0; y < D; y++ )
        for ( x = 0; x < N; x++ )
            memcpy( ( unsigned char* )( &vecD[ y ][ x ] ), chFloat[ y ][ x ], sizeof( float ) );
}
unsigned get_file_size( std::string filename ) // path to file
{
    FILE *p_file = NULL;
    p_file = fopen( filename.c_str(), "rb" );
    fseek( p_file, 0, SEEK_END );
    int size = ftell( p_file );
    fclose( p_file );
    return size;
}

int main( void )
{
    unsigned char chFloat1D[ sizeof( float ) * D * N ];
    
    loadFloatsToCharArray();
    cout << "chArr.size: " << sizeof( chFloat ) << endl;
    unsigned x, y, u;
    for ( y = 0; y < D; y++ )
        for ( x = 0; x < N; x++ )
            vecD[ y ][ x ] = 0.0f;
    unsigned ind1D;
    for ( y = 0; y < D; y++ )
        for ( x = 0; x < N; x++ )
            for ( u = 0; u < sizeof( float ); u++ )
            {
                ind1D = ( y * N ) + ( x * sizeof( float ) ) + u;
                chFloat1D[ ind1D ] = chFloat[ y ][ x ][ u ];
            }

    ofstream outFile;
    outFile.open( "tmp.txt", ofstream::out | ofstream::binary );
    for ( x = 0; x < sizeof( chFloat1D ); x++ )
    {
        outFile << chFloat1D[ x ];
        chFloat1D[ x ] = 0; 
    }
    outFile.close();
    
    ifstream inFile;
    inFile.open( "tmp.txt", ofstream::in | ofstream::binary );
    for ( x = 0; x < get_file_size( "tmp.txt" ); x++ )
    {
        inFile >> chFloat1D[ x ];
    }
    inFile.close();
    
    loadCharArrayToFloats();
    for ( y = 0; y < D; y++ )
    {
        printf( "vecD[y=%i]: ", ( int )y );
        for ( x = 0; x < N; x++ )
            printf( "%f, ", vecD[ y ][ x ] );
        cout << endl;
    }

    return 0;
}
