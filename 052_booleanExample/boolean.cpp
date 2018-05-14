/*
https://en.wikipedia.org/wiki/Bitwise_operations_in_C
*/
#include <stdio.h>
#include <cstdint>
    
void showbits( uint8_t x )
{
    int i; 
    for( i = ( sizeof( uint8_t ) * 8 ) - 1; i >= 0; i-- )
    	( x&( 1u << i ) ) ? 
    		putchar( '1' ) 
    		: 
    		putchar( '0' );
}

int main( void )
{
    uint8_t j = 15, m, n;
    printf( "[ %d ]  in binary               ", j );
    showbits( j ); printf( "\n" );

	uint8_t jj = j; j = ~j;
    printf( "[ %d ]  negated                 ", jj );
    showbits( j ); printf( ".dec=[ %d ]\n", j ); j = jj;

	m = 40;
    printf( "[ %d ]  in binary               ", m );
    showbits( m ); printf( "\n" );
    n = j & m;
    printf( "[ %d ]      and    [ %d ] gives ", j, m );
    showbits( n ); printf( "\n" );

    n = j | m;
    printf( "[ %d ]      or     [ %d ] gives ", j, m );
    showbits( n );    printf( "\n" );

    n = j ^ m;
    printf( "[ %d ]     xor     [ %d ] gives ", j, m );
    showbits( n );    printf( "\n" );

    /* the loop for right shift operation */
    for ( m = 0; m <= 1; m++ ) 
	{
        n = j >> m;
        printf( "[ %d ] right shift [ %d ] gives  ", j, m );
        showbits( n );    printf( "\n" );
    }

    return 0;
}
