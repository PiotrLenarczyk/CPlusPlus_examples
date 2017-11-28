#include <iostream>

using namespace std;
typedef uint32_t uint; //median expected unsigned ( unsigned int ); It is not true for less than 32bit-word-wide archs
size_t i = 0;

template < typename T >
inline T func( T& inVal )
{
	return inVal++;
};

int main( void )
{
	float a = 0.0f; func( a );
	int32_t b = 0;  func( b );		//median expected int;
	cout << "inc f32: " << a << endl;
	cout << "inc int: " << b << endl;

	return 0;
}
