#include <stdlib.h>		//malloc()
#include <stdio.h> 		//printf()
#include <string.h>		//strlen()
#include <string>		//not needed - just for example
using namespace std;
typedef unsigned char byte;
typedef __uint32_t uint;
uint i = 0x0;
	
typedef struct 
{	char* dataPtr = NULL;
	char* endPtr = NULL;
	uint strSize = 0x0;
//======================================================================
	void mallocStr( uint size )
	{	dataPtr = ( char* )malloc( size );
		dataPtr[ size - 1 ] = '\0';
		endPtr = dataPtr; 
		strSize = size;
	};
//======================================================================
	uint size( void )
	{	return uint( endPtr - dataPtr );
	};
//======================================================================
	void resizeStr( uint newSize )	//costly background hardcopy! only enlarging
	{	uint i = 0x0, currSize = size();
		if ( newSize < currSize )
		{	printf( "====\n\tERROR : lossy resize!\n====\n" );
			fatalStr();
			return;
		};
		char* newDataPtr = ( char* )malloc( newSize );
		while ( i < currSize )
		{	newDataPtr[ i ] = dataPtr[ i ];
			i+=1;
		}; 
		free( dataPtr );
		dataPtr = newDataPtr; newDataPtr = NULL;
		dataPtr[ newSize - 1 ] = '\0';
		endPtr = dataPtr + currSize;
		strSize = newSize;
	};
//======================================================================
	void prepend( const void* const strIn ) //costly background hardcopy!
	{	char* strInPtr = ( char* )strIn; 
		uint sizeIn = strlen( strInPtr ), currSize = size(), 
			 newSize = currSize + sizeIn, i=0x0;
		char* newDataPtr = ( char* )malloc( newSize + 1 ); //'\0'
		i=0x0;while ( i < sizeIn )	//prepend part
		{	newDataPtr[ i ] = strInPtr[ i ];
			i+=1;
		}; strInPtr = NULL;
		i=sizeIn;while ( i < newSize )	//hardcopy
		{	newDataPtr[ i ] = dataPtr[ i - sizeIn ];
			i+=1;
		}; 
		free( dataPtr );
		dataPtr = newDataPtr; newDataPtr = NULL;
		dataPtr[ newSize + 0 ] = '\0'; //malloc newDataPtr
		endPtr = dataPtr + newSize;
		strSize = newSize;
	};
//======================================================================
	void append( const void* const strIn )
	{	char* strInPtr = ( char* )strIn; 
		uint sizeIn = strlen( strInPtr ), currSize = size(), i=0x0;
		if ( currSize + sizeIn < strSize - 1 )
		{	i=0x0;while( i < sizeIn )
			{	dataPtr[ currSize + i ] = strInPtr[ i ];
				i+=1;
			}; endPtr += sizeIn;
		}else
		{	uint newSize = currSize + sizeIn;
			resizeStr( newSize );
			i=0x0;while( i < sizeIn )
			{	dataPtr[ currSize + i ] = strInPtr[ i ];
				i+=1;
			}; endPtr += sizeIn;
			printf( "====\n\tERROR : STRING full - provided costly hardcopy!\n====\n" );		
		};
		strInPtr = NULL;
	};
//======================================================================
	void freeStr( void )
	{	free( dataPtr ); dataPtr = NULL;
		strSize = 0x0;
		endPtr = NULL;
	};
//======================================================================
	void fatalStr( void )
	{	printf( "====\n\tERROR : Program corruption! STRING_OBJECT.free();\n====\n" );
		freeStr();
	};
} STRING;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	char buf[] = "SomeText";
	const char* buff2 = " other!";
	string theString = " C++11";
	STRING str;str.mallocStr( 0x20 );
		str.append( "aa" ); 
		str.append( buf );
		str.append( buff2 );
		str.append( theString.c_str() );
		str.append( " array." );
		printf( "[%s].size() : %u\n", str.dataPtr, str.size() );
		printf( "&str : %p\n", str.dataPtr );
		str.resizeStr( 0x30 );
		printf( "[%s].size() : %u\n", str.dataPtr, str.size() );
		printf( "&str : %p\n", str.dataPtr );
		str.prepend( "prependPattern_" );
		printf( "[%s].size() : %u\n", str.dataPtr, str.size() );
		str.append( "_StringOverflow" );
		printf( "[%s].size() : %u\n", str.dataPtr, str.size() );
		//str.resizeStr( 0x10 ); //lossy resize
	str.freeStr();
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//Post Scriptum: no sizeof() feature - str.size()!;
