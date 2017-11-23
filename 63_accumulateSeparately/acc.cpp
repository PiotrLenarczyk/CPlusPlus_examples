#include <iostream>
#include <vector>
#include <chrono>

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
	long long int llTmp = 0, llint = 0;
	float f32fract = 0.0f;
	for ( auto &x : inVal )
	{
		llTmp = ( long long int )x;
		f32fract += float( x ) - float( llTmp ); 
		llint += llTmp;
		if ( ( f32fract > 9.9f ) || ( f32fract < -9.9f ) )//minimizing accumulative error
		{
			llTmp = ( long long int )llint;
			llint += llTmp;
			f32fract -= llTmp;
		}
	}

	return f32fract + llint;
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
		if ( ( fS.fraction > 9.9f ) || ( fS.fraction < -9.9f ) )//minimizing accumulative error
		{
			llTmp = ( long long int )fS.intPart;
			fS.intPart += llTmp;
			fS.fraction -= llTmp;
		}
	}

	return fS.fraction + fS.intPart;
};

template < typename T >
inline T registersAccumulate( vector< T >& inVal ) //results are wrong - there are hazards.
{	
	volatile long long int llTmp; 
	long long int register r15 asm("r14");	//64b integer register declaration
// 	cout << "&llTmp: " << &llTmp << endl;
	
	volatile long long int intPart; 
	long long int register r14 asm("r15");	//64b integer register declaration
// 	cout << "&intPart: " << &intPart << endl;
	
	volatile float fraction;
	float register floatXmm asm( "xmm7" ); //register declaration SMM ( SIMD ) 128bit
// 	cout << "&fraction: " << &fraction << endl;
	
	for ( auto &x : inVal )
	{
		llTmp = ( long long int )x;
		fraction += float( x ) - float( llTmp ); 
		intPart += llTmp;
		if ( fraction > 99.9f )
		{
			llTmp = ( long long int )intPart;
			intPart += llTmp;
			fraction -= llTmp;
		}
	}
	
	return fraction + intPart;
};

void printVals( float &result0, float &result1, float result2 )
{
    cout << "trivial acc = " << result0 << endl;
    cout << "separate acc = " << result1 << endl;
	cout << "registers acc = " << result2 << endl;
};

int main( void )
{
	const uint N = 1E7;
	vector < float > vec1D( N, 0.17f );
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
              
//    printVals( result0, result1, result2 );  //result2 for registers processing is wrong!

	return 0;
}

//P.S. please note usage only for very long arrays holding large floating points numbers!

