#include <iostream>

using namespace std;
typedef uint32_t uint;
size_t i = 0;

//named int-types array / int-types strings array
enum:uint32_t		//intXX; uintXX; size_t
{	flag1 = 1,
	flag2, 
	flag3, 
	flag4 = 15, 
	flag5,
	flag6,
} A;

int main( void )
{
	cout << "sizeof(A) : " << sizeof( A ) << endl;
	cout << "flag1 : " << flag1 << endl;
	cout << "flag2 : " << flag2 << endl;
	cout << "flag3 : " << flag3 << endl;
	cout << "flag4 : " << flag4 << endl;
	cout << "flag5 : " << flag5 << endl;
	cout << "flag6 : " << flag6 << endl;

	return 0;
};
