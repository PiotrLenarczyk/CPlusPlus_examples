//https://stackoverflow.com/questions/1623111/programmatic-way-to-get-variable-name-in-c
#include <cstdio> 	//printf
#include <cstdlib>	//system

using namespace std;

//======================================================================
//======================================================================
//					IMPORT EXPORT BINARY FILE STRUCTURE
//======================================================================
//======================================================================
//-#MAX_LONG_UNSIGNED limit for file size
//-no size limits for each variable=object=structure=instructions
//-1024 variables allowed in single file
//-variable stringName limited to 1kiB characters
//-file accessed by 16kiB temporary buffer
//-HEADER: 1024x: checksum variableName | type | flags | fileOffset
//-VARIABLES contains: nameSize2B | stringNameXB | size8B | binaryDataXB
//======================================================================
//======================================================================
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%% HEADER OFFSET 0x0 %%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//	cheksum2B_of_variable0Name,
//	type1B_variable0,
//	flags1B_variable0,
//	fileAddres8B_variable0,	
//	...
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^ VARIABLES OFFSET 0x4000 ^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//	nameSize2B_variable0,			//file offset 0x4000
//	stringName_variable0\0,			//file offset 0x4002
//	size8B_variable0,				//file offset 0x4XXX
//	variable0,						//file offset 0xXXXXXXXX
//	...
//	EOF
//======================================================================
//======================================================================
#define VARNAME( var )					#var
#define DUMP( var ) 					printf( "%s : 0x%X\n", VARNAME( var ), var );
#define SIZE_1B							0x1
#define EOV 							"EOV"
#define EOV_PATTERN						*(unsigned*)&EOV
#define	FILEACCESS_SIZE					0x1
#define	FILEREAD_BUFSIZE				0x4000	//16kiB file read - header size
#define MAX_VARNAME						0x400
#define MAX_VARIABLES					0x400
#define	HEADER_OFFSET					0x0
#define	VARIABLES_OFFSET				0x4000
#define	FSEEK_VARIABLES( filePtr )		fseek( filePtr, VARIABLES_OFFSET, SEEK_SET );
#define	CLEAR( in ) for( int i = 0x0; i < sizeof( in ); i++ ) \
						*(unsigned char*)(void*)(&in) = 0x0;
unsigned char fileReadBuf[ FILEREAD_BUFSIZE ];
unsigned char varName[ MAX_VARNAME ];
int varCount;




long unsigned foundVarsFilePtrs[ MAX_VARIABLES ];


unsigned char typeName[ 0x20 ];
unsigned char* TYPE( unsigned char type )
{	CLEAR( typeName );
	switch( type )
	{	default:
#define TYPE_UNDEFINED				0x00
		case TYPE_UNDEFINED:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_UNDEFINED ) );i++ )
				typeName[ i ] = VARNAME( TYPE_UNDEFINED )[ i ];
			break;
#define TYPE_FUNCTION_PTR			0x01
		case TYPE_FUNCTION_PTR:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_FUNCTION_PTR ) );i++ )
				typeName[ i ] = VARNAME( TYPE_FUNCTION_PTR )[ i ];
			break;
#define TYPE_MACHINE_CODE			0x02
		case TYPE_MACHINE_CODE:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_MACHINE_CODE ) );i++ )
				typeName[ i ] = VARNAME( TYPE_MACHINE_CODE )[ i ];
			break;
#define TYPE_DATA					0x03
		case TYPE_DATA:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_DATA ) );i++ )
				typeName[ i ] = VARNAME( TYPE_DATA )[ i ];
			break;
#define TYPE_FLAG					0x04
		case TYPE_FLAG:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_FLAG ) );i++ )
				typeName[ i ] = VARNAME( TYPE_FLAG )[ i ];
			break;
#define TYPE_ORDER					0x05
		case TYPE_ORDER:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_ORDER ) );i++ )
				typeName[ i ] = VARNAME( TYPE_ORDER )[ i ];
			break;
#define TYPE_PTR					0x06
		case TYPE_PTR:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_PTR ) );i++ )
				typeName[ i ] = VARNAME( TYPE_PTR )[ i ];
			break;
//====
//... reserved
//====
#define TYPE_STRUCT					0x86
		case TYPE_STRUCT:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_STRUCT ) );i++ )
				typeName[ i ] = VARNAME( TYPE_STRUCT )[ i ];
			break;
#define	TYPE_UNSIGNED_CHAR			0x87
		case TYPE_UNSIGNED_CHAR:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_UNSIGNED_CHAR ) );i++ )
				typeName[ i ] = VARNAME( TYPE_UNSIGNED_CHAR )[ i ];
			break;
#define TYPE_CHAR					0x88
		case TYPE_CHAR:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_CHAR ) );i++ )
				typeName[ i ] = VARNAME( TYPE_CHAR )[ i ];
			break;
#define	TYPE_UNSIGNED_SHORT			0x89
		case TYPE_UNSIGNED_SHORT:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_UNSIGNED_SHORT ) );i++ )
				typeName[ i ] = VARNAME( TYPE_UNSIGNED_SHORT )[ i ];
			break;
#define	TYPE_SHORT					0x8A
		case TYPE_SHORT:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_SHORT ) );i++ )
				typeName[ i ] = VARNAME( TYPE_SHORT )[ i ];
			break;
#define TYPE_UNSIGNED_INT			0x8B
		case TYPE_UNSIGNED_INT:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_UNSIGNED_INT ) );i++ )
				typeName[ i ] = VARNAME( TYPE_UNSIGNED_INT )[ i ];
			break;
#define TYPE_INT					0x8C
		case TYPE_INT:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_INT ) );i++ )
				typeName[ i ] = VARNAME( TYPE_INT )[ i ];
			break;
#define TYPE_UNSIGNED_LONG			0x8D
		case TYPE_UNSIGNED_LONG:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_UNSIGNED_LONG ) );i++ )
				typeName[ i ] = VARNAME( TYPE_UNSIGNED_LONG )[ i ];
			break;
#define TYPE_LONG					0x8E
		case TYPE_LONG:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_LONG ) );i++ )
				typeName[ i ] = VARNAME( TYPE_LONG )[ i ];
			break;
#define TYPE_UNIGNED_LONG_LONG		0x8F
		case TYPE_UNIGNED_LONG_LONG:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_UNIGNED_LONG_LONG ) );i++ )
				typeName[ i ] = VARNAME( TYPE_UNIGNED_LONG_LONG )[ i ];
			break;
#define TYPE_LONG_LONG				0x90
		case TYPE_LONG_LONG:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_LONG_LONG ) );i++ )
				typeName[ i ] = VARNAME( TYPE_LONG_LONG )[ i ];
			break;
#define	TYPE_FLOAT16				0x91
		case TYPE_FLOAT16:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_FLOAT16 ) );i++ )
				typeName[ i ] = VARNAME( TYPE_FLOAT16 )[ i ];
			break;
#define TYPE_FLOAT					0x92
		case TYPE_FLOAT:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_FLOAT ) );i++ )
				typeName[ i ] = VARNAME( TYPE_FLOAT )[ i ];
			break;
#define TYPE_DOUBLE					0x93
		case TYPE_DOUBLE:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_DOUBLE ) );i++ )
				typeName[ i ] = VARNAME( TYPE_DOUBLE )[ i ];
			break;
#define TYPE_LONG_DOUBLE			0x94
		case TYPE_LONG_DOUBLE:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_LONG_DOUBLE ) );i++ )
				typeName[ i ] = VARNAME( TYPE_LONG_DOUBLE )[ i ];
			break;
#define	TYPE_STRING					0x95
		case TYPE_STRING:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_STRING ) );i++ )
				typeName[ i ] = VARNAME( TYPE_STRING )[ i ];
			break;
#define	TYPE_CONSTANT				0x96
		case TYPE_CONSTANT:
			for ( int i = 0x0; i < sizeof( VARNAME( TYPE_CONSTANT ) );i++ )
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
			for ( int i = 0x0; i < sizeof( VARNAME( FLAG_UNDEFINED ) );i++ )
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
#define	FILEREAD_FLAGS_SIZE		0x10
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

#define PRINT_COMMAND "hexdump -Cv "
void PRINT( void* fileName, long unsigned offset )
{	int i;
	unsigned char command[ 0x400 ], *namePtr;
		for ( i = 0x0; i < sizeof(PRINT_COMMAND);i++ )
			command[ i ] = PRINT_COMMAND[i];
	i--;
	namePtr = (unsigned char*)fileName;
	while( *namePtr )
		command[ i++ ] = *namePtr++;
	command[ i ] = 0x0;
	i = system( (char*)command );
};

void LIST( void* fileName )
{	//read file via 4kiB temporary buffer 
	//find EOV patterns and print varnames
	//EOV can come out at file buffer edge - separate variable name read
	//buffer file reads and rest read byte by byte	
	size_t st, i, filePosition; 
	long unsigned foundSize; unsigned char *cPtr;
	FILE *pFile;
	pFile = fopen( (const char*)fileName, "rb" );
	//file read with FILEREAD_BUFSIZE
	printf( "\"%s\" variables:\n", (char*)fileName );
	//HEADER file offset: 0x0
		st = fread( (void*)&HEADER, FILEACCESS_SIZE, FILEREAD_HEADER_SIZE, pFile );
		i = 0x0;while( HEADER.LUT[ i ].cs )
		{	//header info:
			printf( "\t(%s).0x%X \t\t@0x%016lX\n",
				TYPE( HEADER.LUT[ i ].varType ),
				HEADER.LUT[ i ].cs,
				HEADER.LUT[ i ].fileVarOffset );
			
//full info:
			filePosition = ftell( pFile );
			fseek( pFile, HEADER.LUT[ i ].fileVarOffset, SEEK_SET );
//access must be checked with fileSize
st = fread( fileReadBuf, FILEACCESS_SIZE, FILEREAD_BUFSIZE, pFile );
			fseek( pFile, filePosition, SEEK_SET );

			
			printf( "\t(%s)\"%s\" [%lu]B \t@0x%016lX\n",
				TYPE( HEADER.LUT[ i ].varType ),
				&fileReadBuf[ 2 ],
				*(long unsigned*)&fileReadBuf[
					FILEREAD_VARNAMESIZE_SIZE + 
					*(short*)fileReadBuf  ],
				HEADER.LUT[ i ].fileVarOffset );
			i++;
		};
	fclose( pFile );
};

int SAVE( void* fileName, unsigned char type, void* variableOut, long unsigned size )
{	//only append to binary file via fwrite
	//existing types will be deleted, and written last after file shrinking (variables shift - addresses must be recalculated)
	//single object at a time
	//jump within file with fseek
	FILE *pFile;
	pFile = fopen( (const char*)fileName, "wb" );
//HEADER file offset: 0x0

//rewrite this section
		CLEAR( varLUT );
		CLEAR( HEADER );
		varLUT.cs = checksumArr( (unsigned char*)variableOut );
		varLUT.fileVarOffset = VARIABLES_OFFSET;
		HEADER.LUT[ 0 ] = 
		{	checksumArr( (unsigned char*)variableOut ),
			TYPE_INT,
			FLAG_UNDEFINED,
			VARIABLES_OFFSET
		};
		fwrite( &HEADER, SIZE_1B, sizeof(HEADER_TypeDef), pFile );
//VARIABLES file offset: 0x4000
		FSEEK_VARIABLES( pFile );
		short varNameSize; 
		varNameSize =sizeof( VARNAME(variableOut) );
		fwrite( &varNameSize, SIZE_1B, FILEREAD_VARNAMESIZE_SIZE, pFile );
		fwrite( VARNAME(variableOut), SIZE_1B, sizeof( VARNAME(variableOut) ), pFile  );
		fwrite( &size, SIZE_1B, sizeof( long unsigned ), pFile  );
		fwrite( variableOut, SIZE_1B, *(size_t*)&size, pFile );
for ( int i = 0x0; i < FILEREAD_BUFSIZE; i++ ) fileReadBuf[i] = 0x0;
fwrite( fileReadBuf, SIZE_1B, FILEREAD_BUFSIZE, pFile );
	fclose( pFile );
	return 0x1;
};

int LOAD( void* fileName, void* variableIn, void* size )
{	
};


char currentlyOpened[ 0x200 ];
int OPEN( void* fileName )
{	for ( int i = 0x0; i < sizeof( HEADER ); i+=0x4 )
		*( unsigned* )( &HEADER ) = ( unsigned )0x0;
};
#if (0)

int DELETE( void* fileName )
{
};

void listVariables( void )
{
};

int SAVE( void* variableOut, long unsigned size )
{	SAVE( currentlyOpened, variableOut, size );
};

int LOAD( void* variableIn, long unsigned size )
{	
};

#endif
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#ifdef SELF_CONTAINED
int main( void )
{	
	char filename[] = "data.bin";
	int i = 0x44332211, st, size;
	size = 4;
	OPEN( filename );
	st = SAVE( filename, TYPE_INT, &i, size );
	LIST( filename );
	return 0;
};//end of main()
#endif //SELF_CONTAINED
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
