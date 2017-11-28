#include <iostream>
#include <climits>
#include <iomanip>

using namespace std;
typedef uint32_t uint;
typedef uint64_t u64;

int main( void )
{
	float f32;
	u64 i;
	for ( i = 0; i < ULLONG_MAX; i++ )
	{
		f32 = i;
		if ( ( u64 )f32 != i )
		{
			cout << setprecision( 20 ) <<  "Comparision error: f32(" << float( i ) << ")(" << ( u64 )f32 <<  ") != (" << i << ")\n";
			break;
		}
	};
	cout << "uint16_t.max()=USHRT_MAX: " << USHRT_MAX << endl;
	cout << "uint32_t.max()=UINT_MAX: " << UINT_MAX << endl;
	cout << "uint64_t.max()=ULONG_MAX: " << ULONG_MAX << endl;
	cout << "index < USHRT_MAX: " << bool ( i < USHRT_MAX ) << endl;
	cout << "index < UINT_MAX: " << bool ( i < UINT_MAX ) << endl;
	cout << "index < ULONG_MAX: " << bool ( i < ULONG_MAX ) << endl;
	
	float fArray[ 2 ] = { 1.1f, 1.2f };
	float f32Index = 0;
	cout << "fArray[ uint(float) ]: " << fArray[ uint( f32Index ) ] << endl;
	
	return 0;
};

