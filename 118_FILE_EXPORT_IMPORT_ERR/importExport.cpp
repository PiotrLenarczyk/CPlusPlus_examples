//https://stackoverflow.com/questions/1623111/programmatic-way-to-get-variable-name-in-c
#include <cstdio> 
using namespace std;

#define VARNAME( var )	#var
#define DUMP( var ) printf( "%s : 0x%X\n", VARNAME( var ), var );
void listVariables( void* fileName )
{
};

int SAVE( void* fileName, void* variableOut, void* size )
{	//only append to binary file via fwrite
	//existing types will be deleted, and written last after file shrinking
	//single object at a time
	//jump within file with fseek
	FILE *pFile;
	pFile = fopen( (const char*)fileName, "wb" );
		fwrite( variableOut, 0x1, (size_t)size, pFile );
	fclose( pFile );
};

int LOAD( void* fileName, void* variableIn, void* size )
{	size_t readCount;
	FILE *pFile;
	pFile = fopen( (const char*)fileName, "wb" );
		readCount = fread( variableIn, 0x1, (size_t)size, pFile );
	fclose( pFile );
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
int main( void )
{	
	int i = 0x11223344;
	DUMP(i);
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
