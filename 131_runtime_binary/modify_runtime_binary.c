#include <stdio.h>
#include <string.h>
#define READ_MODE
#define FIND_MODE MODE_VERBOSE
#include "variables.h"
#define SYS( s )		system( s );
#define COMM_SIZE		256

//======================================================================
char comm[ COMM_SIZE ];
void vars_open( char* filename )
{	read_variables( DEFAULT_VAR_FILENAME, FIND_MODE );
	file_size = open_file( filename );
	if ( file_size == FILESIZE_UNINITIALIZED )
	{	exit(-1);
	};
}; 

void vars_free( void )
{	close_file();
};
//======================================================================
//	MODIFIED FILE OPERATIONS
//======================================================================
FILE *modifiedFile;
char* modifiedBufPtr;
long modified_copy_file( char* srcFilename, char* dstFilename )
{	int lSize;
	modifiedFile = fopen ( srcFilename , "rb" );
	if (modifiedFile==NULL) 
	{	printf("File \"%s\" do not exist!\n", srcFilename); 
		exit(1);
	};
	fseek (modifiedFile , 0 , SEEK_END);
	lSize = ftell (modifiedFile);
	rewind (modifiedFile);
	
	modifiedBufPtr = (char*)malloc( lSize );
	// copy the input file into the buffer:
	fread (modifiedBufPtr,1,lSize,modifiedFile);
	rewind (modifiedFile);
	
//=====================================================================
	//actual binary file modification based on variables.bin
	FILE *outFile;
	outFile = fopen ( dstFilename , "wb" );
	if (outFile==NULL) 
	{	printf("Modified file error!\n"); 
		exit(1);
	}; 
	fseek (modifiedFile , 0 , SEEK_END);
	
	
	int newInt = 0x88776655;
	char newFuncName[] = "bar";
	*(int*)(modifiedBufPtr + varArr.var[0].offset) = newInt;
	for ( int i = 0; i < strlen(newFuncName); i++ )
		*(char*)(modifiedBufPtr + varArr.var[1].offset + i) = 
			newFuncName[i];
	
	fwrite( modifiedBufPtr, 1, lSize, outFile );
//=====================================================================
		
	fclose( outFile );
	return lSize;
};

void modified_close_file( void )
{	free( modifiedBufPtr );
	fclose( modifiedFile );
	pFile = NULL;
};

//======================================================================
int main( int argc, char* argv[] )
{	char *binaryIn = argv[1], *binaryOut = argv[2];	
	vars_open( binaryIn );
		find_variables( FIND_MODE );
		
		CP_NULL(comm, "echo ====\n");
		APPEND(comm, "echo Original binary:\n");
		APPEND(comm, "echo ");APPEND(comm, binaryIn);APPEND(comm,"\n");
		APPEND(comm, "echo ====\n");
		APPEND(comm, "./");APPEND(comm, binaryIn); APPEND(comm, "\n");
		APPEND(comm, "echo ====\n");
		SYS( comm );
	vars_free(); 
	//====
	//	MODIFICATION OF BINARY
	//====
	modified_copy_file( binaryIn, binaryOut );
	
	
		CP_NULL(comm, "echo ----\n");
		APPEND(comm, "echo Modified binary:\n");
		APPEND(comm, "echo ");APPEND(comm, binaryOut);APPEND(comm,"\n");
		APPEND(comm, "echo ----\n");
		APPEND(comm, "./");APPEND(comm, binaryOut);APPEND(comm,"\n");
		SYS(comm);
	modified_close_file();

	return 0;
};
