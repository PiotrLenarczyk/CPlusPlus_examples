/*
https://stackoverflow.com/questions/668653/how-could-i-implement-logical-implication-with-bitwise-or-other-efficient-code-i
https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
*/
//STL
#include <iostream>
#include <string>
#include <time.h>
#include <random>

using namespace std;

int implicate( int a, int b ) { return ~a | b; }

void rand_str( char *dest, size_t length )
{
    char charset[] = "0123456789"
                     "abcdefghijklmnopqrstuvwxyz"
                     "_";

    while ( length-- > 0 ) 
    {
        size_t index = ( double ) rand() / RAND_MAX * ( sizeof charset - 1 );
        *dest++ = charset[ index ];
    }
    *dest = '\0';
}

int main( void )
{
    uniform_int_distribution<> pseudoSeed { -2147483646, 2147483646 };
    default_random_engine e;
    e.seed( clock() + time( NULL ) );    
    srand( pseudoSeed( e ) );
    char buff [ 10 ];
    for ( int i = 0; i < 3; i++ )
    {
        e.seed( clock() );   
        srand( ( pseudoSeed( e ) + i ) * implicate( i, ( int )clock() ) );
        rand_str( buff, 10 );
        cout << "[" << buff << "]" << endl;
    }
    cout << endl;
    
    return 0;
}
