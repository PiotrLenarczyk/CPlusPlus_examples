#include <iostream>
#include <time.h>
#include <array>
#include <vector>

using namespace std;
typedef uint32_t uint;
uint i = 0;

#define N 20000
#define N_loops 400
int t1, t2, t3, t4, t5, t6, t7;
int a[ N ] = { 4, 7, };
int b[ N ] = { 0, 0, };
vector < int > vecA( N ); 
vector < int > vecB( N ); 
array < int, N > arrA; 
array < int, N > arrB; 

__attribute__((always_inline)) inline  
void foo( register int const *const inPtr, const uint size, register int *const outPtr )
{	register int actVal = 0;
	for ( i = 0; i < size; i++ )
	{	actVal = inPtr[ i ];
		outPtr[ i ] = ( actVal * actVal ) + ( actVal % 2 );
	};
};

void bar( int const *const inPtr, const uint size, int *const outPtr )
{	int actVal = 0;
	for ( i = 0; i < size; i++ )
	{	actVal = inPtr[ i ];
		outPtr[ i ] = ( actVal * actVal ) + ( actVal % 2 );
	};
};

void car( int * inPtr, uint size, int * outPtr )
{	int actVal = 0;
	for ( i = 0; i < size; i++ )
	{	actVal = inPtr[ i ];
		outPtr[ i ] = ( actVal * actVal ) + ( actVal % 2 );
	};
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{//first run of short programs is always slower due to Operating System background CPU overclocking:
	for ( i = 0; i < N; i++ )
	{	int tmp = rand();
		a[ i ] = tmp;
		vecA[ i ] = tmp;
		arrA[ i ] = tmp;
	}
//	function with compiler directives
	t1 = clock();
	for ( int j = 0; j < N_loops; j++ )
		foo( &a[ 0 ], N, &b[ 0 ] );
	t1 = clock() - t1;
	
//	function without compiler directives
	t2 = clock();
	for ( int j = 0; j < N_loops; j++ )
		bar( &a[ 0 ], N, &b[ 0 ] );
	t2 = clock() - t2;

//	function without compiler directives and consts
	t3 = clock();
	for ( int j = 0; j < N_loops; j++ )
		car( &a[ 0 ], N, &b[ 0 ] );
	t3 = clock() - t3;

//	direct computations 1
	t4 = clock();
	for ( int j = 0; j < N_loops; j++ )
	{	int actVal = 0;
		for ( i = 0; i < N; i++ )
		{	actVal = a[ i ];
			b[ i ] = ( actVal * actVal ) + ( actVal % 2 );
		};  
	};
	t4 = clock() - t4;
	
//	direct computations 2
	t5 = clock();
	for ( int j = 0; j < N_loops; j++ )
	{	for ( i = 0; i < N; i++ )
		{	b[ i ] = ( a[ i ] * a[ i ] ) + ( a[ i ] % 2 );
		};  
	};
	t5 = clock() - t5;
	
//	direct std::array
	t6 = clock();
	for ( int j = 0; j < N_loops; j++ )
	{	for ( i = 0; i < N; i++ )
		{	arrA[ i ] = ( arrB[ i ] * arrB[ i ] ) + ( arrB[ i ] % 2 );
		};  
	};
	t6 = clock() - t6;
	
//	direct std::vector
	t7 = clock();
	for ( int j = 0; j < N_loops; j++ )
	{	for ( i = 0; i < N; i++ )
		{	vecB[ i ] = ( vecA[ i ] * vecA[ i ] ) + ( vecA[ i ] % 2 );
		};  
	};
	t7 = clock() - t7;
	
	cout << "function foo() with compiler directives : " << float( t1 ) / CLOCKS_PER_SEC << "[s]\n"
		 << "function bar() without compiler directives : " << float( t2 ) / CLOCKS_PER_SEC << "[s]\n"
		 << "function car() without compiler directives and consts : " << float( t3 ) / CLOCKS_PER_SEC << "[s]\n"
		 << "direct computations 1 : " << float( t4 ) / CLOCKS_PER_SEC << "[s]\n"
		 << "direct computations 2 : " << float( t5 ) / CLOCKS_PER_SEC << "[s]\n"
		 << "direct computations std::array : " << float( t6 ) / CLOCKS_PER_SEC << "[s]\n"
		 << "direct computations std::vector : " << float( t7 ) / CLOCKS_PER_SEC << "[s]\n"
		 << "without compiler directives slow down : " << 100.0f * ( 1.0f - ( float( t1 ) / float( t2 ) ) ) << "[%]\n"
		 << "without compiler directives and consts slow down : " << 100.0f * ( 1.0f - ( float( t1 ) / float( t3 ) ) ) << "[%]\n"
		 << "direct computations 1 slow down : " << 100.0f * ( 1.0f - ( float( t1 ) / float( t4 ) ) ) << "[%]\n"
		 << "direct computations 2 slow down : " << 100.0f * ( 1.0f - ( float( t1 ) / float( t5 ) ) ) << "[%]\n"
		 << "direct computations std::array slow down : " << 100.0f * ( 1.0f - ( float( t1 ) / float( t6 ) ) ) << "[%]\n"
		 << "direct computations std::vector slow down : " << 100.0f * ( 1.0f - ( float( t1 ) / float( t7 ) ) ) << "[%]\n";

	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


//Post Scriptum: results for C arrays are almost the same on modern uArchs. 

