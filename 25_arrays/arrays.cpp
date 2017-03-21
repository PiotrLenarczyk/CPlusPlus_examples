//STL
#include <iostream>

using std::cout;
using std::endl;

unsigned int x( 0 ), n( 6 );

int main()
{
    int rgbColours[ n ][ 3 ] = { 
        {   0,  155,    0 }, /*rgbColours[ 0 ]*/
        { 155,    0,    0 }, /*rgbColours[ 1 ]*/
        {   0,    0,  155 }, /*rgbColours[ 2 ]*/
        { 255,  255,    0 }, /*rgbColours[ 3 ]*/
        { 255,    0,  255 }, /*rgbColours[ 4 ]*/
        {   0,    0,    0 }  /*rgbColours[ 5 ]*/
    };
    for ( x = 0; x < n; x++ )
        cout << "rgbColours[" << x << "]: [ " 
             << rgbColours[ x ][ 0 ] << ", " 
             << rgbColours[ x ][ 1 ] << ", " 
             << rgbColours[ x ][ 2 ] << " ]" << endl;    
 
    int ROW = 2;
    int COL = 3;
    float **ptrVal = new float* [ ROW ]; //matrix rowsY
    for ( int i = 0; i < COL; i++ )
            ptrVal[ i ] = new float[ COL ];
    ptrVal[ 0 ][ 1 ] = 11.1f;
    cout << ptrVal[0][1] << endl;
    for ( int i = 0; i < COL; i++ )
            delete[] ptrVal[ i ];
    delete[] ptrVal;
             
    return 0;
}
