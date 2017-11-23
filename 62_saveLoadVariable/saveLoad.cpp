/* https://stackoverflow.com/questions/5840148/how-can-i-get-a-files-size-in-c */
//STL
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring> //memcpy

using namespace std;
typedef uint32_t uint;
typedef unsigned char uchar;
const uint N = 5;

//heap function pointers:
template < typename T >
inline void saveVectorToFile( string name, vector< T > &inVal );
template < typename T >
inline vector< T > loadVectorFromFile( string name );

struct float4
{
	float x;
	float y;
	float z;
	float w;
};

int main( void )
{
	string name = "fileName1D.txt";
	vector < float >  vec1D( N, 0.1741f );
	cout << "sizeof( vec1D ): " << sizeof( vec1D ) << endl;
	saveVectorToFile( name, vec1D );
	vector < float > vecRead = loadVectorFromFile< float >( name );
	for ( auto &x : vecRead )cout << "vec[ " << uint( &x - &vecRead[ 0 ] ) << " ]: " << x << endl;
		
	string name2 = "fileName4D.txt";
	float4 f4;
	f4.x = 0.1f; f4.y = 0.2f; f4.z = 0.3f; f4.w = 1.0f;
	vector < float4 > vec4D( N, f4 );
	saveVectorToFile( name2, vec4D );
	vector < float4 > vec4DRead = loadVectorFromFile< float4 >( name2 );
	cout << "vec4DRead[ 4 ].y :" << vec4DRead[ 4 ].y << endl;
	
	
	
//	NESTED VECTORS DATA SAVE&LOAD
	cout << "================" << endl << "== Nested vectors example ==" << endl << "================" << endl;
	string name3 = "fileNameNestedVec.txt";
	uint l = 2;
	vector < float > tmp( l, 0.1f );
	vector < vector < float > > vec2D( N, tmp );
    ofstream dataOut;
    dataOut.open( name3.c_str(), ios::out | ios::binary );
    dataOut.write( ( char* )( &N ), sizeof( uint ) ); 
    dataOut.write( reinterpret_cast< char* >( &l ), sizeof( uint ) ); 
    for ( auto &x : vec2D )
	    dataOut.write( reinterpret_cast< char* >( &x ), x.size() * sizeof( float ) ); 
	dataOut.close();
	cout << "vec2D[ 4 ][ 1 ] : " << vec2D[ 4 ][ 1 ] << endl;
	vector < vector < float > > vec2DRead;
	uint vecsNo, vec1DSize;
	ifstream dataIn;
    dataIn.open( name3.c_str(), ios::in | ios::binary );
    dataIn.read( reinterpret_cast< char* >( &vecsNo ), sizeof( uint ) );
	dataIn.read( reinterpret_cast< char* >( &vec1DSize ), sizeof( uint ) );
	vector < float > tmp2( vec1DSize );
	for ( uint x = 0; x < vecsNo; x++ )
	{
		dataIn.read( reinterpret_cast< char* >( &tmp2 ), sizeof( float ) * vec1DSize );
		vec2DRead.push_back( tmp2 );
	}
	dataIn.close();
	cout << "vec2DRead[ 4 ][ 1 ] : " << vec2DRead[ 4 ][ 1 ] << endl;
	
    return 0;
}

//===============================================================================================
//============================ FUNCTIONS BODIES =================================================
//===============================================================================================
template < typename T >
inline void saveVectorToFile( string name, vector< T > &inVal )
{  

	ofstream outFile; outFile.open( name.c_str(), ofstream::out | ofstream::binary );
	const uint varSize = sizeof( T );
	uchar buff[ varSize ];
	uint b = 0;
	for ( auto &x : inVal )
	{
		memcpy( &buff, ( uchar* )( &x ), varSize );
		for ( b = 0; b < varSize; b++ )
			outFile << buff[ b ];
	}
	outFile.close();
		
};

inline unsigned getFileSize( std::string filename ) // path to file
{
    FILE *p_file = NULL;
    p_file = fopen( filename.c_str(), "rb" );
    fseek( p_file, 0, SEEK_END );
    int size = ftell( p_file );
    fclose( p_file );
    return size;
};

template < typename T >
inline vector< T > loadVectorFromFile( string name )
{
	ifstream inFile; inFile.open( name.c_str(), ofstream::in | ofstream::binary );
	const uint fileSize = getFileSize( name );
	const uint varSize = sizeof( T );
	const uint varNo = fileSize / varSize;
	uchar fileBuffor[ fileSize ];
	vector < T > vecOut( varNo );
	uint x = 0;
	for ( x = 0; x < fileSize; x++ )
		inFile >> fileBuffor[ x ];
	inFile.close();
	for ( x = 0; x < fileSize; x += varSize )
	{
		memcpy( ( uchar* )( &vecOut[ x / varSize ] ), &fileBuffor[ x ], varSize );
	}	
	return vecOut;
};

//P.S. please note mapped file alternative

