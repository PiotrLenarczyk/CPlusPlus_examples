//https://stackoverflow.com/questions/1623111/programmatic-way-to-get-variable-name-in-c
#include <cstdio> 
using namespace std;

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
unsigned long foundVarsFilePtrs[ MAX_VARIABLES ];
void LIST( void* fileName )
{	//read file via 4kiB temporary buffer 
	//find EOV patterns and print varnames
	//EOV can come out at file buffer edge - separate variable name read
	
	size_t st; int i, *bufPtr, fileBufNo = 0x0;
	FILE *pFile;
	pFile = fopen( (const char*)fileName, "rb" );
	//file read with FILEREAD_BUFSIZE
		st = fread( fileReadBuf, FILEACCESS_SIZE, FILEREAD_BUFSIZE, pFile );
		bufPtr = (int*)fileReadBuf; varCount = 0x0;
		printf( "\"%s\" variables[%i]:\n", (char*)fileName, MAX_VARIABLES );
		for ( i = 0x0; i < FILEREAD_BUFSIZE; i += 0x4 )
		{	if ( *bufPtr == EOV_PATTERN )
			{	foundVarsFilePtrs[ varCount ] = 
					( unsigned long )(bufPtr - (int*)fileReadBuf) +
					(fileBufNo * FILEREAD_BUFSIZE);
				printf( "\t\"%s\" @0x%016lX\n", 
						(char*)bufPtr + 0x4,
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
	//existing types will be deleted, and written last after file shrinking
	//single object at a time
	//jump within file with fseek
	FILE *pFile;
	pFile = fopen( (const char*)fileName, "wb" );
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
	return 0;
};//end of main()
#endif //SELF_CONTAINED
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
