#include "headers.h"

int main()
{

    cout << "intiger datatypes: " << endl;
    cout << "bool: " << sizeof( true ) << endl;
    cout << "char: " << sizeof( char ) << endl;
    cout << "uint8_t: " << sizeof( uint8_t ) << endl;    
    cout << "short int: [" << sizeof( short int ) << "]B   max: " << __SHRT_MAX__ << endl;
    cout << "int: [" << sizeof( int ) << "]B   max: " << __INT32_MAX__ << endl;
    cout << "long int: [" << sizeof( long int ) << "]B     max: " << __LONG_LONG_MAX__ << endl;
    cout << "__int128: " << sizeof( __int128 ) << endl;
    cout << "floating points datatypes: " << endl;
//     // GPU Half to float: ( only GP108 Pascal architekture!!! values [ -10, +10] )
//     float f = ((h&0x8000)<<16) | (((h&0x7c00)+0x1C000)<<13) | ((h&0x03FF)<<13); 
//     float f=0.22;
//     // GPU Float to half:
//     uint32_t x = *((uint32_t*)&f);
//     uint16_t h = ((x>>16)&0x8000)|((((x&0x7f800000)-0x38000000)>>13)&0x7c00)|((x>>13)&0x03ff);
//     cout << "half precision: " << sizeof(h) << endl;
    cout << "float: " << sizeof( float ) << endl;
    cout << "double: " << sizeof( double ) << endl;
    cout << "long double: " << sizeof( long double ) << endl;
    cout << "__float128: " << sizeof( __float128 ) << endl;
    
    return 0;
}
