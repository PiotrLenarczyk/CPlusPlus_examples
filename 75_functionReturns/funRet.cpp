#include <iostream>
#include <vector>

using namespace std;
typedef uint32_t uint;
size_t i = 0;

vector < float > *foo( float &a, float &b );
#ifdef __cplusplus
extern "C"
{
#endif
	void *bar( float &a, float &b )
	{
		static vector < float > vecCInputs;
		vecCInputs.resize( 2 );
		vecCInputs[ 0 ] = a;
		vecCInputs[ 1 ] = b;
		return &vecCInputs;
	};
#ifdef __cplusplus
};
#endif

int main( void )
{
	float x = 0.0f, y = 0.1f;
	vector< float > fooRet = *foo( x, y );		//hardcopy
	for ( ;i < fooRet.size(); i++ )
		cout << "fooRet["  << i << "]: " << fooRet[ i ] << endl;
		
	vector< float >* fooRet2 = foo( x, y );		//pointer to function static container pointer
	for ( i = 0; i < fooRet2->size(); i++ )
		cout << "*fooRet2["  << i << "]: " << fooRet2->at( i ) << endl;
	
//		C void* hardcopy
	vector< float > barRet = *static_cast< vector< float >* >( bar( x, y ) );
	for ( i = 0;i < barRet.size(); i++ )
		cout << "barRet["  << i << "]: " << barRet[ i ] << endl;
	
//		C void* pointer to function static container pointer
	vector< float >* barRet2 = ( vector< float >* )bar( x, y );
	for ( i = 0;i < barRet2->size(); i++ )
		cout << "*barRet2["  << i << "]: " << barRet2->at( i ) << endl;
		
//		C void* pointer to function static container with -fpermissive flag warning ( no casting )
	vector< float >* barRet3 = bar( x, y );
	for ( i = 0;i < barRet3->size(); i++ )
		cout << "*barRet3["  << i << "]: " << barRet3->at( i ) << endl;
	
	return 0;
};

vector < float > *foo( float &a, float &b )
{
	static vector < float > vecInputs;
	vecInputs.resize( 2 );
	vecInputs[ 0 ] = a;
	vecInputs[ 1 ] = b;
	return &vecInputs;
};
