#include <cstdio> 
#define CAST( destPtr ) ( destPtr )( const void* )
using namespace std;
typedef unsigned uint;
typedef unsigned char byte;
unsigned i = 0x0;

void printChars( int maxSize, char* cPtr, char* ptrName )
{	char *charPtr; charPtr = cPtr;
	maxSize--; //last byte will be 0x0 = '\0'
	printf( "char *cPtr;\ncPtr = %s;\n", ptrName );
	while( ( *charPtr++ ) && ( maxSize-- )  )
		printf( "*cPtr++ = \'%c\';\n", *( charPtr - 0x1 ) );
	printf( "*cPtr = 0x0;\n\n" );
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	
	#define CHECK_SIZE 0x40
	#define STRING( a )	#a
	char arr[ CHECK_SIZE ]; for( int i = 0x0; i < CHECK_SIZE; i++ )arr[i] = 0x0;
	printChars	( 	sizeof("HelloWorld!"), 
					"HelloWorld!==here will not be continued==", 
					STRING( arr ) 
				);
	printf( "instructions check:" );
	//paste printed instructions:
	
	
	
				char *cPtr;
				cPtr = arr;
				*cPtr++ = 'H';
				*cPtr++ = 'e';
				*cPtr++ = 'l';
				*cPtr++ = 'l';
				*cPtr++ = 'o';
				*cPtr++ = 'W';
				*cPtr++ = 'o';
				*cPtr++ = 'r';
				*cPtr++ = 'l';
				*cPtr++ = 'd';
				*cPtr++ = '!';
				*cPtr = 0x0;
				
				
				
				
	//end of paste area
	printf( "\n%s\n", arr );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
