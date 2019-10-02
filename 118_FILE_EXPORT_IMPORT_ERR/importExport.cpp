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
//	stringNameNB_variable0\0,		//file offset 0x4002
//	size8B_variable0,				//file offset 0x4XXX
//	bytesNB_variable0,				//file offset 0xXXXXXXXX
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


#include "inc.c"

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
