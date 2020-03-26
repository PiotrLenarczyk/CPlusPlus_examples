#include <cstdio> 
using namespace std;
#ifndef STRINGIZE
	#define STRINGIZE( a, b ) a##b
#endif
//only uniformly distibuted Bit Fields!
#define BF_ARR( BFName, FieldName, no, val )								\
					BFName.STRINGIZE( FieldName, no ) = (val);
#define BFPTR_ARR( BFPTRName, FieldName, no, val )							\
					BFPTRName->STRINGIZE( FieldName, no ) = (val);
		
typedef struct
{	unsigned char Field0		:2;
	unsigned char Field1		:2;
	unsigned char Field2		:2;
	unsigned char Field3		:2;
	unsigned char Field4		:2;
	unsigned char Field5		:2;
	unsigned char Field6		:2;
	unsigned char Field7		:2;
	unsigned char Field8		:2;
	unsigned char Field9		:2;
	unsigned char Field10		:2;
	unsigned char Field11		:2;
	unsigned char Field12		:2;
	unsigned char Field13		:2;
	unsigned char Field14		:2;
	unsigned char Field15		:2;
	unsigned char Field16		:2;
	unsigned char Field17		:2;
	unsigned char Field18		:2;
	unsigned char Field19		:2;
	unsigned char Field20		:2;
	unsigned char Field21		:2;
	unsigned char Field22		:2;
	unsigned char Field23		:2;
	unsigned char Field24		:2;
	unsigned char Field25		:2;
	unsigned char Field26		:2;
	unsigned char Field27		:2;
	unsigned char Field28		:2;
	unsigned char Field29		:2;
	unsigned char Field30		:2;
	unsigned char Field31		:2;
}BF_TypeDef;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	BF_TypeDef BF, *BFPtr; 
	BFPtr  = &BF;
	//zeroing Bit Field "BF"
	{	unsigned char *cPtr;	cPtr = ( unsigned char* )( void* )&BF;
		for ( int i = 0x0; i < sizeof( BF ); i++ ) *cPtr++ = 0x0;
	};
	printf( "Bit Field \"BF\" size: %d\n", sizeof( BF_TypeDef ) );
	printf( "*(unsigned int*)&BF : 0x%16X\n", *( unsigned int* )&BF );
	printf( "BF.Field3 : %d\n", BF.Field3 );
		BF_ARR( BF, Field, 3, 0b11 );
	printf( "BF.Field3 : %d\n", BF.Field3 );
	printf( "*(unsigned int*)&BF : 0x%016X\n", *( unsigned int* )&BF );
	printf( "BFPtr->Field5 : %d\n", BF.Field5 );
		BFPTR_ARR( BFPtr, Field, 5, 0b11 );
	printf( "BFPtr->Field5 : %d\n", BF.Field5 );
	printf( "*(unsigned int*)&BF : 0x%016X\n", *( unsigned int* )&BF );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
