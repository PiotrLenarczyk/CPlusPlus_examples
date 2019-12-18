unsigned char typeName[ 0x20 ];
unsigned char* TYPE( unsigned char type )
{	CLEAR( typeName );
	switch( type )
	{	default:
#define TYPE_UNDEFINED				0x00
		case TYPE_UNDEFINED:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_UNDEFINED ) );i++ )
				typeName[ i ] = VARNAME( TYPE_UNDEFINED )[ i ];
			break;
#define TYPE_FUNCTION_PTR			0x01
		case TYPE_FUNCTION_PTR:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_FUNCTION_PTR ) );i++ )
				typeName[ i ] = VARNAME( TYPE_FUNCTION_PTR )[ i ];
			break;
#define TYPE_MACHINE_CODE			0x02
		case TYPE_MACHINE_CODE:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_MACHINE_CODE ) );i++ )
				typeName[ i ] = VARNAME( TYPE_MACHINE_CODE )[ i ];
			break;
#define TYPE_DATA					0x03
		case TYPE_DATA:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_DATA ) );i++ )
				typeName[ i ] = VARNAME( TYPE_DATA )[ i ];
			break;
#define TYPE_FLAG					0x04
		case TYPE_FLAG:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_FLAG ) );i++ )
				typeName[ i ] = VARNAME( TYPE_FLAG )[ i ];
			break;
#define TYPE_ORDER					0x05
		case TYPE_ORDER:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_ORDER ) );i++ )
				typeName[ i ] = VARNAME( TYPE_ORDER )[ i ];
			break;
#define TYPE_PTR					0x06
		case TYPE_PTR:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_PTR ) );i++ )
				typeName[ i ] = VARNAME( TYPE_PTR )[ i ];
			break;
//====
//... reserved
//====
#define TYPE_STRUCT					0x86
		case TYPE_STRUCT:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_STRUCT ) );i++ )
				typeName[ i ] = VARNAME( TYPE_STRUCT )[ i ];
			break;
#define	TYPE_UNSIGNED_CHAR			0x87
		case TYPE_UNSIGNED_CHAR:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_UNSIGNED_CHAR ) );i++ )
				typeName[ i ] = VARNAME( TYPE_UNSIGNED_CHAR )[ i ];
			break;
#define TYPE_CHAR					0x88
		case TYPE_CHAR:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_CHAR ) );i++ )
				typeName[ i ] = VARNAME( TYPE_CHAR )[ i ];
			break;
#define	TYPE_UNSIGNED_SHORT			0x89
		case TYPE_UNSIGNED_SHORT:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_UNSIGNED_SHORT ) );i++ )
				typeName[ i ] = VARNAME( TYPE_UNSIGNED_SHORT )[ i ];
			break;
#define	TYPE_SHORT					0x8A
		case TYPE_SHORT:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_SHORT ) );i++ )
				typeName[ i ] = VARNAME( TYPE_SHORT )[ i ];
			break;
#define TYPE_UNSIGNED_INT			0x8B
		case TYPE_UNSIGNED_INT:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_UNSIGNED_INT ) );i++ )
				typeName[ i ] = VARNAME( TYPE_UNSIGNED_INT )[ i ];
			break;
#define TYPE_INT					0x8C
		case TYPE_INT:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_INT ) );i++ )
				typeName[ i ] = VARNAME( TYPE_INT )[ i ];
			break;
#define TYPE_UNSIGNED_LONG			0x8D
		case TYPE_UNSIGNED_LONG:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_UNSIGNED_LONG ) );i++ )
				typeName[ i ] = VARNAME( TYPE_UNSIGNED_LONG )[ i ];
			break;
#define TYPE_LONG					0x8E
		case TYPE_LONG:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_LONG ) );i++ )
				typeName[ i ] = VARNAME( TYPE_LONG )[ i ];
			break;
#define TYPE_UNIGNED_LONG_LONG		0x8F
		case TYPE_UNIGNED_LONG_LONG:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_UNIGNED_LONG_LONG ) );i++ )
				typeName[ i ] = VARNAME( TYPE_UNIGNED_LONG_LONG )[ i ];
			break;
#define TYPE_LONG_LONG				0x90
		case TYPE_LONG_LONG:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_LONG_LONG ) );i++ )
				typeName[ i ] = VARNAME( TYPE_LONG_LONG )[ i ];
			break;
#define	TYPE_FLOAT16				0x91
		case TYPE_FLOAT16:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_FLOAT16 ) );i++ )
				typeName[ i ] = VARNAME( TYPE_FLOAT16 )[ i ];
			break;
#define TYPE_FLOAT					0x92
		case TYPE_FLOAT:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_FLOAT ) );i++ )
				typeName[ i ] = VARNAME( TYPE_FLOAT )[ i ];
			break;
#define TYPE_DOUBLE					0x93
		case TYPE_DOUBLE:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_DOUBLE ) );i++ )
				typeName[ i ] = VARNAME( TYPE_DOUBLE )[ i ];
			break;
#define TYPE_LONG_DOUBLE			0x94
		case TYPE_LONG_DOUBLE:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_LONG_DOUBLE ) );i++ )
				typeName[ i ] = VARNAME( TYPE_LONG_DOUBLE )[ i ];
			break;
#define	TYPE_STRING					0x95
		case TYPE_STRING:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_STRING ) );i++ )
				typeName[ i ] = VARNAME( TYPE_STRING )[ i ];
			break;
#define	TYPE_CONSTANT				0x96
		case TYPE_CONSTANT:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( TYPE_CONSTANT ) );i++ )
				typeName[ i ] = VARNAME( TYPE_CONSTANT )[ i ];
			break;
//====
//... reserved
//====
	};
	return typeName;
};

unsigned char flagName[ 0x20 ];
unsigned char* FLAG( unsigned char flag )
{	CLEAR( flagName );
	switch( flag )
	{	default:
#define FLAG_UNDEFINED				0x00
		case FLAG_UNDEFINED:
			for ( int i = 0x0; i < (int)sizeof( VARNAME( FLAG_UNDEFINED ) );i++ )
				flagName[ i ] = VARNAME( FLAG_UNDEFINED )[ i ];
			break;
//====
//... reserved
//====
	};
	return flagName;
};

typedef struct
{	
#define	FILEREAD_CS_SIZE		0x2
	short cs;
#define	FILEREAD_VARTYPE_SIZE	0x1
	unsigned char varType;
#define	FILEREAD_FLAGS_SIZE		0x1
	unsigned char flags;
#define FILEREAD_VAROFFSET_SIZE	0x8
	long unsigned fileVarOffset;
}HEADER_LUT_TypeDef;
HEADER_LUT_TypeDef varLUT;
typedef struct
{	
#define	FILEREAD_HEADER_SIZE	sizeof( HEADER_LUT_TypeDef )
	HEADER_LUT_TypeDef LUT[ MAX_VARIABLES ];
}HEADER_TypeDef;
HEADER_TypeDef HEADER;
typedef struct
{	
#define	FILEREAD_VARNAMESIZE_SIZE	0x2
	short nameSize;
	unsigned char *namePtr;
#define	FILEREAD_VARSIZE_SIZE		0x8
	long unsigned size;
	unsigned char *dataPtr;
}VARIABLE_TypeDef;
VARIABLE_TypeDef VARIABLE;

int checksumSeed;
#define RAND_A 1103515245		//glibc
#define	RAND_C 12345			//glibc
#define RAND_M 0x80000000		//glibc
static inline
short checksumArr( register unsigned char *arrPtr )
{	checksumSeed = *arrPtr++;
	while( *arrPtr )
	{	checksumSeed ^= *arrPtr++;
		checksumSeed = ( (RAND_A * checksumSeed) + RAND_C ) % RAND_M;
	};
	return (checksumSeed >> 0x10) ^ checksumSeed;//2B checksum
};
