//STL
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring> //memcpy

using namespace std;

unsigned i = 0;
const unsigned no = 4;

struct Floats
{
    float f[ no ];                                          //original float data
    unsigned char chFloat[ no ][ sizeof( float ) ];         //original data uchar 2D memory sector
    void loadFloatsToCharArrays( void )
    {  
        for ( unsigned i = 0; i < no; i++ )
            memcpy( chFloat[ i ], ( unsigned char* )( &f[ i ] ), no );
    }
    void loadCharArraysToFloats()
    {
        for ( unsigned i = 0; i < no; i++ )
            memcpy( ( unsigned char* )( &f[ i ] ), chFloat[ i ], no );
    }
};

int main( void )
{
    Floats f;
    for ( i = 0; i < no; i++ )
        f.f[ i ] =  1.41f + i * 0.8161f;
    f.loadFloatsToCharArrays();
    for ( i = 0; i < no; i++ )
        f.f[ i ] = -0.0f;
    for ( i = 0; i < no; i++ )
    {
        cout << "float[" << i << "]: " << f.f[ i ] << endl;
        cout << "charArrayOfFloats[" << i << "]: [";
        for ( unsigned j = 0; j < sizeof( float ); j++ )
             cout << f.chFloat[ i ][ j ];
        cout << "]" << endl;
    }
    f.loadCharArraysToFloats();
    for ( i = 0; i < no; i++ )
        cout << "float[" << i << "]" << f.f[ i ] << endl;
    cout << "========================= struct sending:\n";
    cout << "struct size(): " << unsigned( sizeof( f ) ) << endl;
    unsigned char charFloatsExport[ unsigned( sizeof( f ) ) ];
    memcpy( charFloatsExport, ( unsigned char* )( &f ), sizeof( f ) );
    Floats fReconstructed;
    memcpy( &fReconstructed, charFloatsExport, sizeof( f ) );
    for ( i = 0; i < no; i++ )
        cout << "fReconstructed[" << i << "]" << fReconstructed.f[ i ] << endl;

    return 0;
}
