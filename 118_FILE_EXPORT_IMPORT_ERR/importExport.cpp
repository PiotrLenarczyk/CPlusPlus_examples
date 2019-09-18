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
//-no size limits for each variable/object/structure/instructions
//-1024 variables allowed in single file
//-variable stringName limited to 1kiB characters
//-file accessed by 4kiB temporary buffer
//-HEADER contains 1024x: checksum variableName | fileOffset
//-VARIABLES contains: stringName4B | size8B | binaryData
//======================================================================
//======================================================================
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%% HEADER OFFSET 0x0 %%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//	cheksum4B_variable0Name,		//file offset 0x00
//	fileAddres8B_variable0,			//file offset 0x04
//	cheksum4B_variable1Name,		//file offset 0x08
//	fileAddres8B_variable1,			//file offset 0x0C
//	...
//	cheksum4B_variable1023Name,		//file offset 0x2FF4
//	fileAddres8B_variable1023,		//file offset 0x2FF8
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^ VARIABLES OFFSET 0x3000 ^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//	EOV\0,							//file offset 0x3000
//	string_variable0Name\0,			//file offset 0x3004
//	longUnsigned8B_variable0Size,	//file offset 0x3XXX
//	variable0_binaryData,			//file offset 0xXXXXXXXX
//	EOV\0,							//file offset 0xXXXXXXXX
//	string_variable1Name\0,			//file offset 0xXXXXXXXX
//	longUnsigned8B_variable1Size,	//file offset 0xXXXXXXXX
//	variable1_binaryData,			//file offset 0xXXXXXXXX
//	...
//	EOF
//======================================================================
//======================================================================
#define VARNAME( var )		#var
#define DUMP( var ) 		printf( "%s : 0x%X\n", VARNAME( var ), var );
#define SIZE_1B				0x1
#define EOV 				"EOV"
#define EOV_PATTERN			*(unsigned*)&EOV
#define	FILEACCESS_SIZE		0x1
#define	FILEREAD_BUFSIZE	0x1000	//4kiB file read - optimized for SSD's
#define MAX_VARNAME			0x400
#define MAX_VARIABLES		0x400

unsigned char fileReadBuf[ FILEREAD_BUFSIZE ];
unsigned char varName[ MAX_VARNAME ];
int varCount;




long unsigned foundVarsFilePtrs[ MAX_VARIABLES ];






typedef struct
{	unsigned cs;
	long unsigned fileOffset;
}HEADER_LUT_TypeDef;
typedef struct
{	HEADER_LUT_TypeDef LUT[ MAX_VARIABLES ];
}HEADER_TypeDef;
typedef struct
{	int eov;
	unsigned char *namePtr;
	long unsigned size;
	unsigned char dataPtr;
}VARIABLE_TypeDef;

int checksumSeed;
#define RAND_A 1103515245		//glibc
#define	RAND_C 12345			//glibc
#define RAND_M 0x80000000		//glibc
static inline
int checksumArr( register unsigned char *arrPtr )
{	checksumSeed = *arrPtr++;
	while( *arrPtr )
	{	checksumSeed ^= *arrPtr++;
		checksumSeed = ( (RAND_A * checksumSeed) + RAND_C ) % RAND_M;
	};
	return checksumSeed;
};

#define PRINT_COMMAND "hexdump -Cv -n 32 "
void PRINT( void* fileName )
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
	size_t st; int i, *bufPtr, fileBufNo = 0x0, fileBufCount = 0x0;
	long unsigned foundSize; unsigned char *cPtr;
	FILE *pFile;
	pFile = fopen( (const char*)fileName, "rb" );
//HEADER file offset: 0x0
//...
//VARIABLES file offset: 0x3000
	//file read with FILEREAD_BUFSIZE
		st = fread( fileReadBuf, FILEACCESS_SIZE, FILEREAD_BUFSIZE, pFile );
		bufPtr = (int*)fileReadBuf; varCount = 0x0;
		printf( "\"%s\" variables[%i]:\n", (char*)fileName, MAX_VARIABLES );
		for ( i = 0x0; i < FILEREAD_BUFSIZE; i += 0x4 )
		{	if ( *bufPtr == EOV_PATTERN )
			{	foundVarsFilePtrs[ varCount ] = 
					( long unsigned )(bufPtr - (int*)fileReadBuf) +
					(fileBufNo * FILEREAD_BUFSIZE);
				cPtr = ((unsigned char*)( bufPtr )) + sizeof( EOV_PATTERN );
				while(*cPtr++);
				foundSize = *(long unsigned*)cPtr;
				printf( "\t\"%s\"\t\t[%li]B\t\t@0x%016lX\n", 
						(char*)bufPtr + 0x4,
						foundSize,
						foundVarsFilePtrs[ varCount ]);
				varCount++;
			};
			bufPtr++;
		};
	//byte file read
	//...
	printf( "\"%s\" found variables : [%i]\n", (char*)fileName, varCount );
	fclose( pFile );
};

int SAVE( void* fileName, void* variableOut, long unsigned size )
{	//only append to binary file via fwrite
	//existing types will be deleted, and written last after file shrinking (variables shift - addresses must be recalculated)
	//single object at a time
	//jump within file with fseek
	FILE *pFile;
	pFile = fopen( (const char*)fileName, "wb" );
//HEADER file offset: 0x0
//...
//VARIABLES file offset: 0x3000
		fwrite( EOV, SIZE_1B, sizeof( EOV ), pFile );
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

#if (0)
char currentlyOpened[ 0x200 ];
int OPEN( void* fileName )
{
};

int DELETE( void* fileName )
{
};

void listVariables( void )
{
};

int SAVE( void* variableOut, void* size )
{	SAVE( currentlyOpened, variableOut, size );
};

int LOAD( void* variableIn, void* size )
{	LOAD( currentlyOpened, variableIn, size );
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
	st = SAVE( filename, &i, size );
	LIST( filename );
	PRINT( filename );
	return 0;
};//end of main()
#endif //SELF_CONTAINED
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
