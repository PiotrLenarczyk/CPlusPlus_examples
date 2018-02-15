#include <iostream>
using namespace std;
typedef uint32_t uint;
size_t i = 0;

void foo( const int &in, int* out );

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{//	first usage	
	int a = 5, b;
	foo( a, &b );
//	second usage
	foo( 5, &b );
	foo( 14, &b );
#define B 5
	foo( B, &b );
#define ADD( x, y ) ( x + y )
	foo( ADD( B, 1 ), &b );

	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void foo( const int &in, int* out )
{	cout << "in: " << in << endl;	//read-only!
	const int* inPtr = &in;
	cout << "*in: " << inPtr << endl;
	*out = in + 1;
};
