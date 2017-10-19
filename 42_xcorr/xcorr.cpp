//STL
#include <iostream>
#include <random>

using std::vector;using std::cout;using std::endl;using std::default_random_engine;using std::uniform_real_distribution;

//GLOBALS
unsigned i = 0, N;
unsigned sizeA ( 100 ), sizeB ( 104 ); //if: sizeA >> sizeB perform spatial subsampling on A ( take one per some samples )
double accdA( 0.0 ), accdB( 0.0 );
double r_xy( 0.0 ), num( 0.0 ), xixSq( 0.0 ), yiySq( 0.0 );
float accA( accdA ), accB( accdB );
vector < float > a( sizeA );
vector < float > aia( sizeA );
vector < float > b( sizeB );
vector < float > bib( sizeB );

//FUNCTIONS
void populateAB();

int main( void )
{   populateAB();
    
    if ( sizeA >= sizeB )
        N = sizeB;
    else
        N = sizeA;
//  mean
    for ( i = 0; i < sizeA; i++ )
        accdA += a[ i ];
    for ( i = 0; i < sizeB; i++ )
        accdB += b[ i ];
    accdA /= sizeA; accdB /= sizeB;
    
//  aia; bib
    for ( i = 0; i < sizeA; i++ )
        aia[ i ] = a[ i ] - accA;
    for ( i = 0; i < sizeB; i++ )
        bib[ i ] = b[ i ] - accB;

//  numerator
    for ( i = 0; i < N; i++ )
        num += aia[ i ] * bib[ i ];
        
//  denominator
    for ( i = 0; i < N; i++ )
    {
        xixSq += aia[ i ] * aia[ i ];
        yiySq += bib[ i ] * bib[ i ];
    }
    xixSq = sqrt( xixSq ); yiySq = sqrt( yiySq ); 
    r_xy = xixSq * yiySq;
    r_xy = num / r_xy;
    cout << "r_xy: " << r_xy << endl;
    
    return 0;
}

void populateAB()
{
    default_random_engine genRand;
    uniform_real_distribution< float > randf( 0.0f, 1.0f ); 
    for ( i = 0; i < sizeA; i++ )
        a[ i ] = randf( genRand );
    for ( i = 0; i < sizeB; i++ )
        b[ i ] = a[ i ] * randf( genRand ) * 0.1f;
}
