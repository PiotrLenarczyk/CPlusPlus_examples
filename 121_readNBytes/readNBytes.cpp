#include <cstdio> 
using namespace std;

typedef struct{	unsigned char t[ 4 ]; }BYTES_4_TypeDef;
typedef struct{	unsigned char t[ 5 ]; }BYTES_5_TypeDef;

#define readNB( dstPtr, srcPtr, size )											\
		{	static int i32, i8; 												\
			i32 = size >> 0x2; i8 = size;										\
			while( i32-- ) 	( (unsigned*)(void*)dstPtr )[ i32 ] = 				\
								( (unsigned*)(void*)srcPtr )[ i32 ];			\
			while( i8-- ) 	( (unsigned char*)(void*)dstPtr )[ i8 ] = 			\
								( (unsigned char*)(void*)srcPtr )[ i8 ];		\
		};
																
#define printNB( srcPtr, N ) { 	static int i; i = N; 							\
								static unsigned char* u8Ptr; 					\
								u8Ptr = (unsigned char*)(void*)srcPtr;			\
								printf( "\"%s\" @0x%p:\n\t", #srcPtr, srcPtr ); \
								while( i-- ) {printf( "%02X ", *u8Ptr++ );};	\
								puts("");										\
								};
#define	printObj( obj )	printNB( &obj, sizeof( obj ) );
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	unsigned char arr[] = { 1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7 };
	
	BYTES_5_TypeDef dst;
	printObj( dst );
	readNB( &dst, &arr[0], 0x4 );
	printNB( &dst, sizeof( dst ) );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
