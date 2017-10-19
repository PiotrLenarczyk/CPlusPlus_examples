//STL
#include <vector>
#include <iostream>

using namespace std;

double diffErr( float a, double b )
{
    return b - double( a );
}
int returnFun( float a );

int main( void )
{
    float a = 1.1f;
    double b = 1.1;
    cout << "diff err: " << diffErr( a, b ) * 1E9 << "[1E9]" << endl;
    if ( a == b )
        cout << "comparision: 1"<< endl;
    else
        cout << "comparision: 0" << endl;
    
    
    return returnFun( a );
}

int returnFun( float a )
{
    printf( "Program executed normally.\n" );
    return 0;
}
