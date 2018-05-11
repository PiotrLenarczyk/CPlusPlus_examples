#include <stdio.h> 
#include <cstring>
#include <string>
#include <stdlib.h>
using namespace std;
typedef unsigned char byte;
typedef __uint32_t uint;
uint i = 0x0;
	
typedef struct 
{	char* dataPtr;
	char* endPtr;
	uint strSize;
	void mallocStr( uint size )
	{	dataPtr = ( char* )malloc( size );
		endPtr = dataPtr;
		strSize = size;
	};
	uint size( void )
	{	return endPtr - dataPtr;
	};
	void rellocStr( uint size )	//background hardcopy!
	{	//malloc
		//copy + update(dataPtr, endPtr, strSize)
		//freeOld
		return;
	};
	void prepend( const void* const strIn ) //background hardcopy!
	{	//malloc
		//prependCopy + update(dataPtr, endPtr, strSize)
		//freeOld
		return;
	};
	
	
	
	void append( const void* const strIn )
	{	char* strInPtr = ( char* )strIn; 
		uint sizeIn = strlen( strInPtr ), currSize = size(), i=0x0;
		if ( currSize + sizeIn < strSize - 1 )
		{	while( i < sizeIn )
			{	dataPtr[ currSize + i ] = strInPtr[ i ];
				i+=1;
			}; endPtr += sizeIn;
		}else
		{	printf( "\tERROR : STRING full!\n" );
		};
	};
	void freeStr( void )
	{	free( dataPtr );
		strSize = 0x0;
		dataPtr = NULL;
		endPtr = NULL;
	};
} STRING;


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	char buf[] = "SomeText";
	const char* buff2 = " other!";
	string theString = "C++11";
	STRING str;str.mallocStr( 0x100 );
		str.append( "aa" ); 
		str.append( buf );
		str.append( buff2 );
		str.append( theString.c_str() );
		printf( "[%s]\n", str.dataPtr );
		printf( "%u\n", str.size() );
	str.freeStr();

	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//Post Scriptum: no sizeof() feature - str.size()!;
