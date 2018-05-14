#include <stdint.h>
#include <stdio.h> //printf
uint16_t x, y; //note that for int16_t there are the same size

int main( void )
{
    x = 0;
    y = 2;
    return printf( "%i\n", x + y );
}
