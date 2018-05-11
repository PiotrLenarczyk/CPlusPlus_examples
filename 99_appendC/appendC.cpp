#include <stdio.h> 
#include <cstring>
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
	void prepend( const void* const strIn ) //costly (background hardcopy)!
	{	return;
	};
	
	
	
	
	
	void append( const void* const strIn )
	{	char* strInPtr = ( char* )strIn; uint sizeIn = strlen( strInPtr );
		if ( strlen( dataPtr ) + strlen( strInPtr ) < strSize - 1 )
		{	uint i=0;while( i < sizeIn )
			{	dataPtr[ size() + i ] = strInPtr[ i ];
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
	STRING str;str.mallocStr( 0x100 );
		str.append( "aa" ); 
		str.append( buf );
		printf( "[%s]\n", str.dataPtr );
		printf( "%u\n", str.size() );
	str.freeStr();

	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//Post Scriptum: no sizeof() usage!;
