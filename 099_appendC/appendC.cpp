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
	void resizeStr( uint newSize )	//costly background hardcopy!
	{	uint i = 0x0, currSize = size();
		char* newDataPtr = ( char* )malloc( newSize );
		if ( newSize > currSize  )
		{	while ( i < currSize )
			{	newDataPtr[ i ] = dataPtr[ i ];
				i+=1;
			}; 
			free( dataPtr );
			dataPtr = newDataPtr; newDataPtr = NULL;
			dataPtr[ newSize - 1 ] = '\0';
			endPtr = dataPtr + currSize;
			strSize = newSize;
		};
		if ( newSize <= currSize  )	//lossy resize
		{	while ( i < newSize )
			{	newDataPtr[ i ] = dataPtr[ i ];
				i+=1;
			}; 
			free( dataPtr );
			dataPtr = newDataPtr; newDataPtr = NULL;
			dataPtr[ newSize - 1 ] = '\0';
			endPtr = dataPtr + newSize;
			strSize = newSize;
		};
	};
//======================================================================
	void prepend( const void* strIn ) //costly background hardcopy!
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
	void append( const void* strIn )
	{	char* strInPtr = ( char* )strIn; 
		uint sizeIn = strlen( strInPtr ), currSize = size(), i=0x0;
		if ( currSize + sizeIn < strSize - 1 )
		{	i=0x0;while( i < sizeIn )
			{	dataPtr[ currSize + i ] = strInPtr[ i ];
				i+=1;
			}; endPtr += sizeIn;
		}else
		{	uint newSize = currSize + sizeIn;
			resizeStr( newSize );		 //costly background hardcopy!
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
} STRING;

void copy( const void* dest, const void* src )
{	char* out = ( char* )dest;
	char* in = ( char* )src;
	while( *out++ = *in++ );
};

void copy_n( void const* dest,  void const* src, uint n )
{	char* out = ( char* )dest;
	char* in = ( char* )src;
	while( n-- )
	{	*out++ = *in++;
	};
};

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
		str.resizeStr( 0x10 ); //lossy resize
		printf( "[%s].size() : %u\n", str.dataPtr, str.size() );
	str.freeStr();
	
	puts( "====" );
	uint a = 15;
	char b[ 5 ]; b[ 4 ] = '\0';
	copy_n( &b[ 0 ], &a, sizeof( a ) );
		printf( "0x%X :", a ); i=0;while( i < 4 ) { printf( "0x%X ", b[ i ] & 0xFF ); i+=1; }; puts( "" );
	copy_n( &b[ 0 ], "aa23", 4 );
		printf( "0x%X : %s\n", a, b );
	puts( "====" );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//Post Scriptum: no sizeof() feature - str.size()!;
