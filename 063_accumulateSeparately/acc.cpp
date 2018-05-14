#include <iostream>
#include <vector>
#include <chrono>
#include <climits> 
#include <cfloat>

using namespace std;
typedef uint32_t uint;
size_t i = 0;

struct floatSeparate
{
	float fraction;
	long long int intPart;
};

template < typename T >
inline T trivialAccumulate( vector< T > &inVal )
{
	T result = 0;
	for ( auto &x : inVal )
		result += x;
    
	return result;
};

template < typename T >
inline T localAccumulate( vector< T >& inVal )
{
    uint lloverflow = 0;                                       //positive overflow counter
	long long int llArr[ 3 ] = { 0, 0 };                       //[0] - tmp LL; [1] - accumulator; 
	float f32fract = 0.0f;
	for ( auto &x : inVal )
	{
		llArr[ 0 ] = ( long long int )x;
		f32fract += float( x ) - float( llArr[ 0 ] ); 
        if ( llArr[ 0 ] + llArr[ 1 ] > LLONG_MAX )            //long long int positive overflow only
            lloverflow++;
		llArr[ 1 ] += llArr[ 0 ];
		if ( ( f32fract > 9.9f ) || ( f32fract < -9.9f ) )    //minimizing cumulative error - both positive and negative
		{
			llArr[ 0 ] = ( long long int )f32fract;
			llArr[ 1 ] += llArr[ 0 ];
			f32fract -= llArr[ 0 ];
		}
	}

	return f32fract + ( float )( llArr[ 1 ] ) + ( float )( ( LLONG_MAX * lloverflow ) );
};

template < typename T >
inline T accumulate( vector< T >& inVal )
{
	long long int llTmp;
	floatSeparate fS = { 0.0f, 0 };	
	for ( auto &x : inVal )
	{
		llTmp = ( long long int )x;
		fS.fraction += float( x ) - float( llTmp ); 
		fS.intPart += llTmp;
		if ( ( fS.fraction > 9.9f ) || ( fS.fraction < -9.9f ) )
		{
			llTmp = ( long long int )fS.fraction;
			fS.intPart += llTmp;
			fS.fraction -= llTmp;
		}
	}

	return fS.fraction + ( float )fS.intPart;
};

template < typename T >
inline T registersAccumulate( vector< T >& inVal )  //results are wrong - there are hazards.
{	
	volatile long long int llTmp; 
	long long int register r15 asm("r14");	        //64b integer register declaration
// 	cout << "&llTmp: " << &llTmp << endl;
	
	volatile long long int intPart; 
	long long int register r14 asm("r15");	        //64b integer register declaration
// 	cout << "&intPart: " << &intPart << endl;
	
	volatile float fraction;
	float register floatXmm asm( "xmm7" );          //register declaration SMM 128bit
// 	cout << "&fraction: " << &fraction << endl;
	
	for ( auto &x : inVal )
	{
		llTmp = ( long long int )x;
		fraction += float( x ) - float( llTmp ); 
		intPart += llTmp;
		if ( fraction > 99.9f )
		{
			llTmp = ( long long int )fraction;
			intPart += llTmp;
			fraction -= llTmp;
		}
	}
	
	return fraction + ( float )intPart;
};

uint printVals( float &result0, float &result1, float &result2, float &result3 )
{
    cout << "trivial acc = " << result0 << endl;
    cout << "separate acc = " << result1 << endl;
    cout << "local separate acc = " << result2 << endl;
	cout << "registers acc = " << result3 << endl;
    cout << "trivial and local separate error: " << result2 - result0 << endl;
    return 0;
};

int main( void )
{  
	const uint N = 1E7;
	vector < float > vec1D( N, 0.17f ); //size of vector vec1D for 1E9 size is ~4GB
	float result0, result1, result2, result3;
	auto t1 = chrono::high_resolution_clock::now();
    result0 = trivialAccumulate( vec1D );
    auto t2 = chrono::high_resolution_clock::now();
    cout << "trivial accumulation took :"
              << chrono::duration_cast< chrono::nanoseconds >( t2 - t1 ).count()
              << " [ns]\n";
              
    auto t3 = chrono::high_resolution_clock::now();
    result1 = accumulate( vec1D );
	auto t4 = chrono::high_resolution_clock::now();
    cout << "separate accumulation took :"
              << chrono::duration_cast< chrono::nanoseconds >( t4 - t3 ).count()
              << " [ns]\n";
              
    auto t5 = chrono::high_resolution_clock::now();
    result2 = localAccumulate( vec1D );
	auto t6 = chrono::high_resolution_clock::now();
    cout << "separate local accumulation took :"
              << chrono::duration_cast< chrono::nanoseconds >( t6 - t5 ).count()
              << " [ns]\n";              
              
    auto t7 = chrono::high_resolution_clock::now();
    result3 = registersAccumulate( vec1D );
    auto t8 = chrono::high_resolution_clock::now();
    cout << "registers accumulation took :"
              << chrono::duration_cast< chrono::nanoseconds >( t8 - t7 ).count()
              << " [ns]\n";
              
//     printVals( result0, result1, result2, result3 );  //registers processing provides wrong results!
    return 0; 
}

//P.S. please note usage only for very long arrays holding large floating points numbers!
