#include <stdlib.h>		//malloc()
#include <stdio.h> 		//printf()
#include <string.h>		//strlen()
#include <string>		//not needed - just for example
#include <stdarg.h>		//append( printf-style )
using namespace std;
typedef unsigned char byte;
typedef uint32_t uint;

typedef struct //last character of ALLOCATED SPACE is always '\0'!
{	char* dataPtr = NULL;	//data pointer
	char* endPtr = NULL;	//current number of 'active' char's
	char tmpBuf[ 0x15 ];	//temporary internal buffer for custom I/O
	uint64_t strSize = 0x0;	//allocated space size
//======================================================================
	void mallocSTRING( uint64_t size )
	{	dataPtr = ( char* )malloc( size );
		dataPtr[ size - 1 ] = '\0';
		endPtr = dataPtr; 
		strSize = size;
	};
//====
	char* operator & ( void ) { return dataPtr; };
//====
	void set( char val )
	{	uint64_t i=0x0;while( i < strSize - 1 )
		{	dataPtr[ i ] = val;
			i+=1;
		}; dataPtr[ strSize - 1 ] = '\0';
		endPtr = dataPtr + strSize - 1;
	};
	void set( const char* val ) { set( *val ); };
//====
	void reset( void )
	{	uint64_t i=0x0;while( i < strSize - 1 )
		{	dataPtr[ i ] = 0x0;
			i+=1;
		}; dataPtr[ strSize - 1 ] = '\0';
		endPtr = dataPtr;
	};
	void clear( void )
	{	reset();
	};
//====
	uint64_t strlenSTRING( void )
	{	return size();
	};
//====
	uint64_t sizeofSTRING( void )
	{	if ( dataPtr == NULL ) return sizeof( dataPtr ) + sizeof( endPtr ) 
									+ sizeof( tmpBuf ) + sizeof( strSize ) + 3; //3B for C struct functions ptr's
		else return ( strSize * sizeof( char ) ) + sizeof( dataPtr ) 
					+ sizeof( endPtr ) + sizeof( tmpBuf ) + sizeof( strSize );			
	}; 
//======================================================================
	uint64_t size( void ) //size of 'active' characters
	{	return uint64_t( endPtr - dataPtr );
	};
//====
//				SIZE MUST HAVE +1 FOR '\0'
	void resizeStr( uint newSize )	//costly background hardcopy!
	{	uint64_t i = 0x0, currSize = size();
		if ( newSize > currSize  )
		{	char* newDataPtr = ( char* )malloc( newSize );
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
		if ( newSize <= currSize  )	//lossy resize
		{	char* newDataPtr = ( char* )malloc( newSize );
			while ( i < newSize - 1 )
			{	newDataPtr[ i ] = dataPtr[ i ];
				i+=1;
			}; 
			free( dataPtr );
			dataPtr = newDataPtr; newDataPtr = NULL;
			dataPtr[ newSize - 1 ] = '\0';
			endPtr = dataPtr + newSize - 1;
			strSize = newSize;
		};
	};
//======================================================================
	void prepend( const void* strIn ) //costly background hardcopy!
	{	char* strInPtr = ( char* )strIn; 
		uint64_t sizeIn = strlen( strInPtr ), currSize = size(), 
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
		strSize = newSize + 1;
	};
//====
	void append( const void* strIn )
	{	char* strInPtr = ( char* )strIn; 
		uint64_t sizeIn = strlen( strInPtr ), currSize = size(), i=0x0;
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
			printf( "====\n\tERROR : STRING full - provided costly hardcopy!!! \n\t\t\"%s\"\n====\n", strInPtr );		
		}; strInPtr = NULL;
	};
	
////====	APPEND ALIASES:
	void append( unsigned char in ) { sprintf( tmpBuf, "%c", in ); 	append( tmpBuf ); };
	void append( char in ) 			{ sprintf( tmpBuf, "%c", in ); 	append( tmpBuf ); };
	void append( uint64_t in )		{ sprintf( tmpBuf, "%lu", in ); append( tmpBuf ); };
	void append( uint32_t in ) 		{ sprintf( tmpBuf, "%u", in ); 	append( tmpBuf ); };
	void append( uint16_t in ) 		{ sprintf( tmpBuf, "%u", in ); 	append( tmpBuf ); };
	void append( int64_t in ) 		{ sprintf( tmpBuf, "%li", in ); append( tmpBuf ); };
	void append( int32_t in ) 		{ sprintf( tmpBuf, "%i", in ); 	append( tmpBuf ); };
	void append( int16_t in ) 		{ sprintf( tmpBuf, "%i", in );	append( tmpBuf ); };
	void append( int8_t in ) 		{ sprintf( tmpBuf, "%i", in ); 	append( tmpBuf ); };
	void append( float in ) 		{ sprintf( tmpBuf, "%f", in ); 	append( tmpBuf ); };	
	void append( double in ) 		{ sprintf( tmpBuf, "%f", in ); 	append( tmpBuf ); };
	void operator += ( const void* strIn )	{ append( strIn ); };
	void operator += ( unsigned char in )	{ sprintf( tmpBuf, "%c", in ); 	append( tmpBuf ); };
	void operator += ( char in )			{ sprintf( tmpBuf, "%c", in ); 	append( tmpBuf ); };
	void operator += ( uint64_t in )		{ sprintf( tmpBuf, "%lu", in ); 	append( tmpBuf ); };
	void operator += ( uint32_t in )		{ sprintf( tmpBuf, "%u", in ); 	append( tmpBuf ); };
	void operator += ( uint16_t in )		{ sprintf( tmpBuf, "%u", in ); 	append( tmpBuf ); };
	void operator += ( int64_t in )			{ sprintf( tmpBuf, "%li", in ); 	append( tmpBuf ); };
	void operator += ( int32_t in )			{ sprintf( tmpBuf, "%i", in ); 	append( tmpBuf ); };
	void operator += ( int16_t in )			{ sprintf( tmpBuf, "%i", in ); 	append( tmpBuf ); };
	void operator += ( int8_t in )			{ sprintf( tmpBuf, "%i", in ); 	append( tmpBuf ); };
	void operator += ( float in )			{ sprintf( tmpBuf, "%f", in ); 	append( tmpBuf ); };
	void operator += ( double in )			{ sprintf( tmpBuf, "%f", in ); 	append( tmpBuf ); };
	void operator << ( const void* strIn )	{ append( strIn ); };
	void operator << ( unsigned char in )	{ sprintf( tmpBuf, "%c", in ); 	append( tmpBuf ); };
	void operator << ( char in )			{ sprintf( tmpBuf, "%c", in ); 	append( tmpBuf ); };
	void operator << ( uint64_t in )		{ sprintf( tmpBuf, "%lu", in ); 	append( tmpBuf ); };
	void operator << ( uint32_t in )		{ sprintf( tmpBuf, "%u", in ); 	append( tmpBuf ); };
	void operator << ( uint16_t in )		{ sprintf( tmpBuf, "%u", in ); 	append( tmpBuf ); };
	void operator << ( int64_t in )			{ sprintf( tmpBuf, "%li", in ); 	append( tmpBuf ); };
	void operator << ( int32_t in )			{ sprintf( tmpBuf, "%i", in ); 	append( tmpBuf ); };
	void operator << ( int16_t in )			{ sprintf( tmpBuf, "%i", in ); 	append( tmpBuf ); };
	void operator << ( int8_t in )			{ sprintf( tmpBuf, "%i", in ); 	append( tmpBuf ); };
	void operator << ( float in )			{ sprintf( tmpBuf, "%f", in ); 	append( tmpBuf ); };
	void operator << ( double in )			{ sprintf( tmpBuf, "%f", in ); 	append( tmpBuf ); };
////====	APPEND PRINTF
	void appendf( const char* fmt, ... )
	{	va_list ap;
		char *p = 0x0, *strPtr = 0x0;
		uint32_t ival = 0x0;
		double dval = 0.0;
		va_start( ap, fmt );
		if ( *fmt == 0x0 ) //empty string
		{	va_end( ap );
			return;
		};
		for ( p = ( char* )( const void* )fmt; *p; p++ )
		{	if ( *p != '%' )
			{	append( *p );
				continue;
			};
			switch ( *++p )
			{	case 'f':
					dval = va_arg( ap, double );
					append( dval );
					break;
				case 'i':
				case 'd':
					ival = va_arg( ap, int );
					append( ival );
					break;
				case 's':
					strPtr = va_arg( ap, char* );
					append( strPtr );
					break;
				default:
					append( *p );
					break;
			};
		};			
		va_end( ap );
	};
//======================================================================
	char  operator () ( uint64_t i )		{ return dataPtr[ i ]; };
	char  operator [] ( uint64_t i )		{ return dataPtr[ i ]; };
	char* operator () ( uint64_t iBeg, uint64_t iEnd )		
	{ 	uint64_t i=0x0;
		if ( ( iEnd - iBeg ) > 0x14 ) //tmpBuf size
		{	puts( "====\n\tERROR : address range must be <= 20!!! \n\t\t\n====\n" );
			return NULL;
		};
		while( i <= iEnd - iBeg )
		{	tmpBuf[ i ] = dataPtr[ iBeg + i ];
			i+=1;
		}; tmpBuf[ iEnd - iBeg + 1 ] = '\0';
		return tmpBuf; 
	};
//======================================================================
	void freeStr( void )
	{	free( dataPtr ); dataPtr = NULL;
		endPtr = NULL;
		strSize = 0x0;
	};
} STRING;
//======================================================================

void copy( const void* dest, const void* src )
{	char* out = ( char* )dest;
	char* in  = ( char* )src;
	while( *out++ = *in++ );
};

void copy_n( void const* dest,  void const* src, uint n )
{	char* out = ( char* )dest;
	char* in  = ( char* )src;
	while( n-- )
	{	*out++ = *in++;
	};
};

void copy_4B( void const* dest,  void const* src, uint n )
{	if( n % 4 != 0 ) return;
	n /= 4;
	uint* out = ( uint* )dest;
	uint* in  = ( uint* )src;
	while( n-- )
	{	*out++ = *in++;
	};
};

void copy_4096B( void const* dest,  void const* src, uint n ) //ideal for MACRO kernel
{	if( n % 4096 != 0 ) return; //not necessary
	struct TMP { byte tmp[ 4096 ]; };
	n /= 4096;
	TMP* out = ( TMP* )dest;
	TMP* in  = ( TMP* )src;
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
	float theFloat = 1.13f;
	STRING str;str.mallocSTRING( 0x20 );
		str.append( "aa" ); 
		str.append( buf );
		printf( "[%s].size() : %lu\n", str.dataPtr, str.size() );
		str.append( buff2 );
		str.append( theString.c_str() );
		str.append( " array." );
		printf( "[%s].size() : %lu\n", str.dataPtr, str.size() );
		printf( "&str : %p\n", str.dataPtr );
		str.resizeStr( 0x30 );
		printf( "[%s].size() : %lu\n", str.dataPtr, str.size() );
		printf( "&str : %p\n", str.dataPtr );
		str.prepend( "prependPattern_" );
		printf( "[%s].size() : %lu\n", str.dataPtr, str.size() );
		str.append( "_StringOverflow" );
		printf( "[%s].size() : %lu\n", str.dataPtr, str.size() );
		str.resizeStr( 0x9 ); //lossy resize
		str.resizeStr( 0x80 );
		printf( "[%s].size() : %lu\n", str.dataPtr, str.size() );
		str.append( "_float( " ); str.append( theFloat ); str.append( "f )" );
		printf( "[%s].size() : %lu\n", str.dataPtr, str.size() );
		STRING tmpStr; tmpStr.mallocSTRING( 0xF );
			tmpStr.append( "STRING_OBJECT" );
		str.append( tmpStr.dataPtr );
		tmpStr.freeStr();
		printf( "[%s].size() : %lu\n", str.dataPtr, str.size() );
		byte space = ' ';
		str += space;
		str << 1.0;
		str << 'f';
		printf( "[%s].size() : %lu\n", str.dataPtr, str.size() );
		printf( "%c\n", str( 1 ) );
		printf( "%c\n", str[ 1 ] );
		printf( "[%s].size() : %lu\n", str( 0, 19 ), strlen( str( 0, 19 ) ) ); //get 20 char's 
		str.resizeStr( 0x9 ); str.set( 0x31 );
		printf( "[%s].size() : %lu\n", str.dataPtr, str.size() );
		str.set( 0x42 );
		printf( "[%s].size() : %lu\n", str.dataPtr, str.size() );
		str.set( '\"' );
		printf( "[%s].size() : %lu\n", str.dataPtr, str.size() );
		printf( "\n====\tstr.resizeStr( 0x100 );\n" ); str.resizeStr( 0x100 );
		printf( "STRING_OBJECT* relocations str.dataPtr=%p : &str=%p\n", str.dataPtr, &str ); //comment & operator overload function
		printf( "STRING_OBJECT* true value : %p\n", &str.dataPtr );	
		printf( "\'active\' chars size- str.size() : %lu\n", str.size() );
		printf( "allocated chars space - str.strSize : %lu\n", str.strSize );
		printf( "STRING_OBJECT \'used memory\' - str.sizeofSTRING() : %lu\n", str.sizeofSTRING() );
		printf( "sizeof(STRING_OBJECT) : %lu \t(not recommended - lack of allocated chars space)\n", sizeof( str ) );
		printf( "====\n" );
		printf( "\n====\tstr.freeStr();\n" ); str.freeStr();
		printf( "STRING_OBJECT* relocations str.dataPtr=%p : &str=%p\n", str.dataPtr, &str ); //comment & operator overload function
		printf( "STRING_OBJECT* true value : %p\n", &str.dataPtr );	
		printf( "\'active\' chars size- str.size() : %lu\n", str.size() );
		printf( "allocated chars space - str.strSize : %lu\n", str.strSize );
		printf( "STRING_OBJECT \'used memory\' - str.sizeofSTRING() : %lu\n", str.sizeofSTRING() );
		printf( "sizeof(STRING_OBJECT) : %lu\n", sizeof( str ) );
		printf( "====\n" );		
	str.freeStr();
	
	str.mallocSTRING( 0x20 );
		str.clear(); 
		str.appendf( "printf style : %s", theString.c_str() );
		printf( "[%s].size() : %lu\n", str.dataPtr, str.size() );
	str.freeStr();

	puts( "====" );
	uint a = 15;
	char b[ 5 ]; b[ 4 ] = '\0';
	copy_n( &b[ 0 ], &a, sizeof( a ) );
		printf( "0x%X :", a ); byte i=0;while( i < 4 ) { printf( "0x%X ", b[ i ] & 0xFF ); i+=1; }; puts( "" );
	copy_n( &b[ 0 ], "aa23", 4 );
		printf( "0x%X : %s\n", a, b );
	copy_4B( &b[ 0 ], "aa23", 4 );
		printf( "0x%X : %s\n", a, b );
	puts( "====" );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//Post Scriptum: no sizeof() feature : STRING_OBJECT.strSize, instead!; 
