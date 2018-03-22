/*
https://stackoverflow.com/questions/19895038/how-can-i-read-value-from-register-using-c
*/ 
#include <time.h>
#include <iostream>
using namespace std;
typedef uint32_t uint;
typedef unsigned char byte;
uint t = 0, t1, t2;
#define MB 1024lu*1024lu
#define GB 1024lu*MB
uint64_t N = 1 * GB;
uint64_t i = 0;
uint64_t j = 0;
void accessRMW( void );
void accessWrite( void );
void accessRead( void );
void benchLoop( uint64_t inN );

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{//	SINGLE CORE ACCESSES - MOST OF TRADITIONAL uARCH'S HAS MEMORY BOTTLENECKS:
//	register unsigned char AL_REG asm("%al");		
	//accessRMW();
	//accessWrite();
	//accessRead();
	benchLoop( 1 * GB );

	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void accessWrite( void )
{	//char* arr[ N ] = { 0 };	//ERROR: too big array ( depends on motherboard memory hardware driver )
	char *arr = ( char* )calloc( N, sizeof( char ) );

	t = clock();
	for ( i = 0; i < N; i++ )
		arr[ i ] = 14;
	t = clock() - t;
	printf( "[char] for loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( float( N ) * float( t ) / float( CLOCKS_PER_SEC ) ), t );
//	======
	t = clock();
	i = 0;
	while ( i <= N )
	{	arr[ i ] = 14;
		i ++;
	}
	t = clock() - t;
	printf( "[char] while forward loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( float( N ) * float( t ) / float( CLOCKS_PER_SEC ) ), t );
//	======
	t = clock();
	i = N - 1;
	while ( i > 0 )
	{	arr[ i ] = 14;
		i --;
	}
	t = clock() - t;
	printf( "[char] while backward loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( float( N ) * float( t ) / float( CLOCKS_PER_SEC ) ), t );
//	======
	delete( arr );
//	======
	int *arrInt = ( int* )calloc( N, sizeof( int ) );
//	======	
	t = clock();
	for ( i = 0; i < N; i++ )
		arrInt[ i ] = 14;
	t = clock() - t;
	printf( "[int] for loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( float( N ) * 4.0f * float( t ) / float( CLOCKS_PER_SEC ) ), t );
//	======
	t = clock();
	i = 0;
	while ( i <= N )
	{	arrInt[ i ] = 14;
		i ++;
	}
	t = clock() - t;
	printf( "[int] while forward loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( float( N ) * 4.0f * float( t ) / float( CLOCKS_PER_SEC ) ), t );
//	======
	t = clock();
	i = N - 1;
	while ( i > 0 )
	{	arrInt[ i ] = 14;
		i --;
	}
	t = clock() - t;
	printf( "[int] while backward loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( float( N ) * 4.0f * float( t ) / float( CLOCKS_PER_SEC ) ), t );
	
	delete( arrInt );
};

void accessRead( void )
{	char *arr = ( char* )calloc( N, sizeof( char ) );
	typedef char CharRegister; //long long datatype declaration
	volatile CharRegister alReg;
	CharRegister register al asm( "al" ); //declaration of using 64bit register (CPU: x64, x86 )
	alReg = 0; 
	cout << "alReg: " << alReg << endl;
	cout << "&alReg: " << &alReg << endl; //register-type address

	t = clock();
	for ( i = 0; i < N; i++ )
		alReg = arr[ i ];
	t = clock() - t;
	printf( "[char] for loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( float( N ) * float( t ) / float( CLOCKS_PER_SEC ) ), t );
//	======
	t = clock();
	i = 0;
	while ( i <= N )
	{	alReg = arr[ i ];
		i ++;
	}
	t = clock() - t;
	printf( "[char] while forward loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( float( N ) * float( t ) / float( CLOCKS_PER_SEC ) ), t );
//	======
	t = clock();
	i = N - 1;
	while ( i > 0 )
	{	alReg = arr[ i ];
		i --;
	}
	t = clock() - t;
	printf( "[char] while backward loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( float( N ) * float( t ) / float( CLOCKS_PER_SEC ) ), t );
//	======
	delete( arr );
//	======
	int *arrInt = ( int* )calloc( N, sizeof( int ) );
	typedef int IntRegister; //long long datatype declaration
	volatile IntRegister eaxReg;
	IntRegister register eax asm( "eax" ); //declaration of using 64bit register (CPU: x64, x86 )
	eaxReg = 0; 
	cout << "eaxReg: " << eaxReg << endl;
	cout << "&eaxReg: " << &eaxReg << endl; //register-type address
//	======	
	t = clock();
	for ( i = 0; i < N; i++ )
		eaxReg = arrInt[ i ];
	t = clock() - t;
	printf( "[int] for loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( float( N ) * 4.0f * float( t ) / float( CLOCKS_PER_SEC ) ), t );
//	======
	t = clock();
	i = 0;
	while ( i <= N )
	{	eaxReg = arrInt[ i ];
		i ++;
	}
	t = clock() - t;
	printf( "[int] while forward loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( float( N ) * 4.0f * float( t ) / float( CLOCKS_PER_SEC ) ), t );
//	======
	t = clock();
	i = N - 1;
	while ( i > 0 )
	{	eaxReg = arrInt[ i ];
		i --;
	}
	t = clock() - t;
	printf( "[int] while backward loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( float( N ) * 4.0f * float( t ) / float( CLOCKS_PER_SEC ) ), t );
	
	delete( arrInt );
};

void accessRMW( void )
{	char *arr = ( char* )calloc( N, sizeof( char ) );

	t = clock();
	for ( i = 0; i < N; i++ )
		arr[ i ] += 14;
	t = clock() - t;
	printf( "[char] for loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( float( N ) * float( t ) / float( CLOCKS_PER_SEC ) ), t );
//	======
	t = clock();
	i = 0;
	while ( i <= N )
	{	arr[ i ] += 14;
		i ++;
	}
	t = clock() - t;
	printf( "[char] while forward loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( float( N ) * float( t ) / float( CLOCKS_PER_SEC ) ), t );
//	======
	t = clock();
	i = N - 1;
	while ( i > 0 )
	{	arr[ i ] += 14;
		i --;
	}
	t = clock() - t;
	printf( "[char] while backward loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( float( N ) * float( t ) / float( CLOCKS_PER_SEC ) ), t );
//	======
	delete( arr );
//	======
	int *arrInt = ( int* )calloc( N, sizeof( int ) );
//	======	
	t = clock();
	for ( i = 0; i < N; i++ )
		arrInt[ i ] += 14;
	t = clock() - t;
	printf( "[int] for loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( float( N ) * 4.0f * float( t ) / float( CLOCKS_PER_SEC ) ), t );
//	======
	t = clock();
	i = 0;
	while ( i <= N )
	{	arrInt[ i ] += 14;
		i ++;
	}
	t = clock() - t;
	printf( "[int] while forward loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( float( N ) * 4.0f * float( t ) / float( CLOCKS_PER_SEC ) ), t );
//	======
	t = clock();
	i = N - 1;
	while ( i > 0 )
	{	arrInt[ i ] += 14;
		i --;
	}
	t = clock() - t;
	printf( "[int] while backward loop elapsed : %02f[GBps]; %i[periods]\n", float( N ) / ( float( N ) * 4.0f * float( t ) / float( CLOCKS_PER_SEC ) ), t );
	
	delete( arrInt );
};

void benchLoop( uint64_t inN )
{	byte* arr = ( byte* )malloc( inN );
		printf( "====\n%02f[GB] RMW array comparision:\n====\n", float( inN ) / float( GB ) );
//		while loop
		t1 = clock();
		for ( i = 0; i < inN; i++ )
			arr[ i ] += arr[ i ];
		t1 = clock() - t1;
//		for loop
		t2 = clock();
		i = 0; while( i < inN )
		{	arr[ i ] += arr[ i ];
			i++;
		};
		t2 = clock() - t2;
//		printout
		if ( ( t1 < 500 ) || ( t2 < 500 ) )
		{	printf( "ERROR!\n" );
			return;
		};
		printf( "for loop: %02f[GBps]; %i[periods]\n", ( float( inN ) / float( GB ) ) / ( float( t1 ) / float( CLOCKS_PER_SEC ) ), t1 );
		printf( "while loop: %02f[GBps]; %i[periods]\n", ( float( inN ) / float( GB ) ) / ( float( t1 ) / float( CLOCKS_PER_SEC ) ), t2 );
	delete( arr );
};
