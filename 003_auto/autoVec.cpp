//STL
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector < float > vec( 10 );
	size_t valVec( 0 );
	for ( auto& i : vec )
	{
		i = valVec;
		cout << "vec[" << valVec << "]: " << i << endl;
		valVec++;
	}
	valVec = 0;
	cout << "\n weryfikacja vec:" << endl;	
	for ( auto& i : vec )
                    cout << "vec[" << i << "]" << endl;
	return 0;
}

