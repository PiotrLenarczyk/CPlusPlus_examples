//STL
#include <iostream>
/*
    https://www.youtube.com/watch?v=S12qx1DwjVk
    https://www.youtube.com/watch?v=npQF28g6s_k#t=38.422222
 */
using namespace std;

typedef int fxp;
//some number:      0010 0010 0010 0010.0000 0001 0000 1000
const int scale = 16; //range [-10,10]; 1/2^27
//fraction mask:    0000 0000 0000 0000.1111 1111 1111 1111
const int fractionMask = 0xffffffff >> (32 - scale);
const int intMask = ~fractionMask;

#define doubleToFixed(x) ((x) * (double)(1<<scale))
#define fixedToDouble(x) ((double)(x) / (double)(1<<scale))
#define intToFixed(x) ((x) << scale)
#define fixedToInt(x) ((x) >> scale)
#define fractionPart(x) ((x) & fractionMask)
#define intPart(x) ((x) & intMask)
#define MUL_LONG(x, y) ((long)(x) * (long)(y)) >> scale
#define MUL_FXP8(x, y) (((x) >> 8) * ((y) >> 8))
#define DIV_LONG(x, y) ((long)(x) << 16) / (y)
#define DIV_FXP8(x, y) (((x) << 8) / (y) << 8)

int main( void )
{    
    cout.precision(20);
    fxp f = doubleToFixed( 5.7 );
    cout << "fxp(double): " << fixedToDouble( f ) << endl;
    cout << "float: " << 5.7f << endl;
    cout << "double: " << 5.7 << endl;

    int i ( 6 );
    cout << "fxp(int): " << fixedToInt(intToFixed(i)) << endl;
    cout << "int: " << i << endl;

    fxp f1 = doubleToFixed(5.1);
    fxp f2 = doubleToFixed(10.2);
    fxp res;
    cout << fixedToDouble(f1) << " + " << fixedToDouble(f2) << " = ";
    res = f1 + f2;
    cout << fixedToDouble(res) << endl;
    cout << fixedToDouble(f1) << " - " << fixedToDouble(f2) << " = ";
    res = f1 - f2;
    cout << fixedToDouble(res) << endl;

    cout << "fxp.epsilon: " << fixedToDouble( 1 ) << endl;
    cout << "fxp.incEpsilon: " << fixedToDouble( f1++ ) << endl;
    fxp inc = doubleToFixed( 1.0 );
    cout << "proper incerementation: " << fixedToDouble( f1 ) << " + 1 = " << fixedToDouble( f1 + inc ) << endl;

    cout << "fxp.fractional( " << fixedToDouble( f1 ) << " ): " << fixedToDouble( fractionPart( f1 ) ) << endl;
    cout << "fxp.intPart( " << fixedToDouble( f1 ) << " ): " << fixedToDouble( intPart( f1 ) ) << endl;

    cout << "sizeof(int): " << sizeof( int ) << endl;
    cout << "sizeof(long): " << sizeof( long ) << endl;
    cout << "sizeof(long long): " << sizeof( long long ) << endl;
    cout << fixedToDouble(f1) << " * " << fixedToDouble(f2) << " = " << fixedToDouble( MUL_LONG(f1, f2) ) << endl;
    cout << fixedToDouble(f1) << " * " << fixedToDouble(f2) << " = " << fixedToDouble( MUL_FXP8(f1, f2) ) << endl;
    cout << fixedToDouble(f1) << " / " << fixedToDouble(f2) << " = " << fixedToDouble( DIV_LONG(f1, f2) ) << endl;
    cout << fixedToDouble(f1) << " / " << fixedToDouble(f2) << " = " << fixedToDouble( DIV_FXP8(f1, f2) ) << endl;

    return 0;
}
