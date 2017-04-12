//STL
#include <iostream>
#include <vector>
#include <cmath> //sin()
#include <math.h> //PI
#include <stdlib.h> //abs

using std::vector;
using std::cout; using std::endl;

int N = 1001;
vector < float > sine_table( N );
float xCos = 0;

void init_sine()
{
    for ( int i = 0; i < N; i++ )
        sine_table[ i ] = sin( 2 * M_PI * i / 360 );
}

float lookup_sine( float &x )
{
    float y = float( int( x ) % 90 );
    if ( x < 90 )
        return sine_table[ y ];
    if ( x < 180 )
        return sine_table[ 90 - y ];
    if ( x < 270 )
        return -sine_table[ y ];
    return -sine_table[ 90 - y ];
}

 float lookup_cosine( float &x )
 {
     xCos = x + 90;
     return lookup_sine( xCos );
 }
 
 float lookup_tan( float &x )
 {
     return lookup_sine( x ) / lookup_cosine( x );
 }
 
int main()
{
    init_sine();
    float sinTmp( 0 );
    vector < float > sin_ref;
    vector < float > sin_resLUT;
    for ( float fi = 0; fi < M_PI * 2; fi += M_PI / 360 )
    {
        sinTmp = sin( fi );
        cout << " sin( " << fi << "): " << sinTmp << endl;
        sin_ref.push_back( sinTmp );
    }
    for ( float fi = 0; fi < 360; fi++ )
    {
        sinTmp = lookup_sine( fi );
        cout << " sinLUT( " << fi << "): " << sinTmp << endl;
        sin_resLUT.push_back( sinTmp );        
    }
    long double accDiff( 0 );
    for ( int i = 0; i < sin_ref.size(); i++ )
        accDiff += sin_ref[ i ] - sin_resLUT[ i ];
    cout << "accumulated difference for [" << N << "] length sin lookup table: " << accDiff << endl;
    cout << "mean accuracy for [" << N << "] length sin lookup table: " << accDiff / 360 << "[angle]" << endl;
    cout << "=======================\n" << "lookup_sine tune up\n" <<  "=======================\n";
    float tuningConst = accDiff / 360;
    for ( float fi = 0; fi < 360; fi++ )
    {
        sinTmp = lookup_sine( fi ) + tuningConst;
        sin_resLUT[ fi ] = sinTmp;
    }
    accDiff = 0;
    for ( int i = 0; i < sin_ref.size(); i++ )
        accDiff += sin_ref[ i ] - sin_resLUT[ i ];
    cout << "accumulated difference for [" << N << "] length sin lookup table: " << accDiff << endl;
    cout << "mean accuracy for [" << N << "] length sin lookup table: " << accDiff / 360 << "[angle]" << endl;
    cout << "\nAlso trivial precomputation to global array LUT gives quite good results!\n" << endl;
    
    return 0;
}
