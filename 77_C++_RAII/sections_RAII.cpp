#include <iostream>

using namespace std;
typedef uint32_t uint;
size_t i = 0;

int main( void )
{
	namedSection1:
	{
		int tmp = 11;
		cout << "tmp: " << tmp << endl;
	};
	//cout << "tmp: " << tmp << endl;	//error: tmp was not declared

	return 0;
};
