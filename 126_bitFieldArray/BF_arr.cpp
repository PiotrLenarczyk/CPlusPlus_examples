#include <cstdio> 
using namespace std;
//##############################################################################
#ifndef STRINGIZE
	#define STRINGIZE( a, b ) a##b
#endif
//##############################################################################
//only compile-time Bit Fields!
#define BF_ARR( BFName, FieldName, no, val )								\
					BFName.STRINGIZE( FieldName, no ) = (val);
#define BFPTR_ARR( BFPTRName, FieldName, no, val )							\
					BFPTRName->STRINGIZE( FieldName, no ) = (val);
//##############################################################################
//only uniformly distibuted Bit Fields!
//instruction code size costly!
#define BF8_ARR( BFName, FieldName, no, val )								\
		switch( no )														\
		{	default:	break;												\
			case 0:		BFName.STRINGIZE( FieldName, 0 ) = (val);	break;	\
			case 1:		BFName.STRINGIZE( FieldName, 1 ) = (val);	break;	\
			case 2:		BFName.STRINGIZE( FieldName, 2 ) = (val);	break;	\
			case 3:		BFName.STRINGIZE( FieldName, 3 ) = (val);	break;	\
		};
#define BF8PTR_ARR( BFPtrName, FieldName, no, val )							\
		switch( no )														\
		{	default:	break;												\
			case 0:		BFPtrName->STRINGIZE( FieldName, 0 ) = (val);break;	\
			case 1:		BFPtrName->STRINGIZE( FieldName, 1 ) = (val);break;	\
			case 2:		BFPtrName->STRINGIZE( FieldName, 2 ) = (val);break;	\
			case 3:		BFPtrName->STRINGIZE( FieldName, 3 ) = (val);break;	\
		};

#define BF16_ARR( BFName, FieldName, no, val )								\
		switch( no )														\
		{	default:	break;												\
			case 0:		BFName.STRINGIZE( FieldName, 0 ) = (val);	break;	\
			case 1:		BFName.STRINGIZE( FieldName, 1 ) = (val);	break;	\
			case 2:		BFName.STRINGIZE( FieldName, 2 ) = (val);	break;	\
			case 3:		BFName.STRINGIZE( FieldName, 3 ) = (val);	break;	\
			case 4:		BFName.STRINGIZE( FieldName, 4 ) = (val);	break;	\
			case 5:		BFName.STRINGIZE( FieldName, 5 ) = (val);	break;	\
			case 6:		BFName.STRINGIZE( FieldName, 6 ) = (val);	break;	\
			case 7:		BFName.STRINGIZE( FieldName, 7 ) = (val);	break;	\
		};
#define BF16PTR_ARR( BFPtrName, FieldName, no, val )						\
		switch( no )														\
		{	default:	break;												\
			case 0:		BFPtrName->STRINGIZE( FieldName, 0 ) = (val);break;	\
			case 1:		BFPtrName->STRINGIZE( FieldName, 1 ) = (val);break;	\
			case 2:		BFPtrName->STRINGIZE( FieldName, 2 ) = (val);break;	\
			case 3:		BFPtrName->STRINGIZE( FieldName, 3 ) = (val);break;	\
			case 4:		BFPtrName->STRINGIZE( FieldName, 4 ) = (val);break;	\
			case 5:		BFPtrName->STRINGIZE( FieldName, 5 ) = (val);break;	\
			case 6:		BFPtrName->STRINGIZE( FieldName, 6 ) = (val);break;	\
			case 7:		BFPtrName->STRINGIZE( FieldName, 7 ) = (val);break;	\
		};

#define BF32_ARR( BFName, FieldName, no, val )								\
		switch( no )														\
		{	default:	break;												\
			case 0:		BFName.STRINGIZE( FieldName, 0 ) = (val);	break;	\
			case 1:		BFName.STRINGIZE( FieldName, 1 ) = (val);	break;	\
			case 2:		BFName.STRINGIZE( FieldName, 2 ) = (val);	break;	\
			case 3:		BFName.STRINGIZE( FieldName, 3 ) = (val);	break;	\
			case 4:		BFName.STRINGIZE( FieldName, 4 ) = (val);	break;	\
			case 5:		BFName.STRINGIZE( FieldName, 5 ) = (val);	break;	\
			case 6:		BFName.STRINGIZE( FieldName, 6 ) = (val);	break;	\
			case 7:		BFName.STRINGIZE( FieldName, 7 ) = (val);	break;	\
			case 8:		BFName.STRINGIZE( FieldName, 8 ) = (val);	break;	\
			case 9:		BFName.STRINGIZE( FieldName, 9 ) = (val);	break;	\
			case 10:	BFName.STRINGIZE( FieldName, 10 ) = (val);	break;	\
			case 11:	BFName.STRINGIZE( FieldName, 11 ) = (val);	break;	\
			case 12:	BFName.STRINGIZE( FieldName, 12 ) = (val);	break;	\
			case 13:	BFName.STRINGIZE( FieldName, 13 ) = (val);	break;	\
			case 14:	BFName.STRINGIZE( FieldName, 14 ) = (val);	break;	\
			case 15:	BFName.STRINGIZE( FieldName, 15 ) = (val);	break;	\
		};
#define BF32PTR_ARR( BFPtrName, FieldName, no, val )						\
		switch( no )														\
		{	default:	break;												\
			case 0:		BFPtrName->STRINGIZE( FieldName, 0 ) = (val);break;	\
			case 1:		BFPtrName->STRINGIZE( FieldName, 1 ) = (val);break;	\
			case 2:		BFPtrName->STRINGIZE( FieldName, 2 ) = (val);break;	\
			case 3:		BFPtrName->STRINGIZE( FieldName, 3 ) = (val);break;	\
			case 4:		BFPtrName->STRINGIZE( FieldName, 4 ) = (val);break;	\
			case 5:		BFPtrName->STRINGIZE( FieldName, 5 ) = (val);break;	\
			case 6:		BFPtrName->STRINGIZE( FieldName, 6 ) = (val);break;	\
			case 7:		BFPtrName->STRINGIZE( FieldName, 7 ) = (val);break;	\
			case 8:		BFPtrName->STRINGIZE( FieldName, 8 ) = (val);break;	\
			case 9:		BFPtrName->STRINGIZE( FieldName, 9 ) = (val);break;	\
			case 10:	BFPtrName->STRINGIZE( FieldName, 10 ) = (val);break;\
			case 11:	BFPtrName->STRINGIZE( FieldName, 11 ) = (val);break;\
			case 12:	BFPtrName->STRINGIZE( FieldName, 12 ) = (val);break;\
			case 13:	BFPtrName->STRINGIZE( FieldName, 13 ) = (val);break;\
			case 14:	BFPtrName->STRINGIZE( FieldName, 14 ) = (val);break;\
			case 15:	BFPtrName->STRINGIZE( FieldName, 15 ) = (val);break;\
		};

#define BF64_ARR( BFName, FieldName, no, val )								\
		switch( no )														\
		{	default:	break;												\
			case 0:		BFName.STRINGIZE( FieldName, 0 ) = (val);	break;	\
			case 1:		BFName.STRINGIZE( FieldName, 1 ) = (val);	break;	\
			case 2:		BFName.STRINGIZE( FieldName, 2 ) = (val);	break;	\
			case 3:		BFName.STRINGIZE( FieldName, 3 ) = (val);	break;	\
			case 4:		BFName.STRINGIZE( FieldName, 4 ) = (val);	break;	\
			case 5:		BFName.STRINGIZE( FieldName, 5 ) = (val);	break;	\
			case 6:		BFName.STRINGIZE( FieldName, 6 ) = (val);	break;	\
			case 7:		BFName.STRINGIZE( FieldName, 7 ) = (val);	break;	\
			case 8:		BFName.STRINGIZE( FieldName, 8 ) = (val);	break;	\
			case 9:		BFName.STRINGIZE( FieldName, 9 ) = (val);	break;	\
			case 10:	BFName.STRINGIZE( FieldName, 10 ) = (val);	break;	\
			case 11:	BFName.STRINGIZE( FieldName, 11 ) = (val);	break;	\
			case 12:	BFName.STRINGIZE( FieldName, 12 ) = (val);	break;	\
			case 13:	BFName.STRINGIZE( FieldName, 13 ) = (val);	break;	\
			case 14:	BFName.STRINGIZE( FieldName, 14 ) = (val);	break;	\
			case 15:	BFName.STRINGIZE( FieldName, 15 ) = (val);	break;	\
			case 16:	BFName.STRINGIZE( FieldName, 16 ) = (val);	break;	\
			case 17:	BFName.STRINGIZE( FieldName, 17 ) = (val);	break;	\
			case 18:	BFName.STRINGIZE( FieldName, 18 ) = (val);	break;	\
			case 19:	BFName.STRINGIZE( FieldName, 19 ) = (val);	break;	\
			case 20:	BFName.STRINGIZE( FieldName, 20 ) = (val);	break;	\
			case 21:	BFName.STRINGIZE( FieldName, 21 ) = (val);	break;	\
			case 22:	BFName.STRINGIZE( FieldName, 22 ) = (val);	break;	\
			case 23:	BFName.STRINGIZE( FieldName, 23 ) = (val);	break;	\
			case 24:	BFName.STRINGIZE( FieldName, 24 ) = (val);	break;	\
			case 25:	BFName.STRINGIZE( FieldName, 25 ) = (val);	break;	\
			case 26:	BFName.STRINGIZE( FieldName, 26 ) = (val);	break;	\
			case 27:	BFName.STRINGIZE( FieldName, 27 ) = (val);	break;	\
			case 28:	BFName.STRINGIZE( FieldName, 28 ) = (val);	break;	\
			case 29:	BFName.STRINGIZE( FieldName, 29 ) = (val);	break;	\
			case 30:	BFName.STRINGIZE( FieldName, 30 ) = (val);	break;	\
			case 31:	BFName.STRINGIZE( FieldName, 31 ) = (val);	break;	\
		};
#define BF64PTR_ARR( BFPtrName, FieldName, no, val )						\
		switch( no )														\
		{	default:	break;												\
			case 0:		BFPtrName->STRINGIZE( FieldName, 0 ) = (val);break;	\
			case 1:		BFPtrName->STRINGIZE( FieldName, 1 ) = (val);break;	\
			case 2:		BFPtrName->STRINGIZE( FieldName, 2 ) = (val);break;	\
			case 3:		BFPtrName->STRINGIZE( FieldName, 3 ) = (val);break;	\
			case 4:		BFPtrName->STRINGIZE( FieldName, 4 ) = (val);break;	\
			case 5:		BFPtrName->STRINGIZE( FieldName, 5 ) = (val);break;	\
			case 6:		BFPtrName->STRINGIZE( FieldName, 6 ) = (val);break;	\
			case 7:		BFPtrName->STRINGIZE( FieldName, 7 ) = (val);break;	\
			case 8:		BFPtrName->STRINGIZE( FieldName, 8 ) = (val);break;	\
			case 9:		BFPtrName->STRINGIZE( FieldName, 9 ) = (val);break;	\
			case 10:	BFPtrName->STRINGIZE( FieldName, 10 ) = (val);break;\
			case 11:	BFPtrName->STRINGIZE( FieldName, 11 ) = (val);break;\
			case 12:	BFPtrName->STRINGIZE( FieldName, 12 ) = (val);break;\
			case 13:	BFPtrName->STRINGIZE( FieldName, 13 ) = (val);break;\
			case 14:	BFPtrName->STRINGIZE( FieldName, 14 ) = (val);break;\
			case 15:	BFPtrName->STRINGIZE( FieldName, 15 ) = (val);break;\
			case 16:	BFPtrName->STRINGIZE( FieldName, 16 ) = (val);break;\
			case 17:	BFPtrName->STRINGIZE( FieldName, 17 ) = (val);break;\
			case 18:	BFPtrName->STRINGIZE( FieldName, 18 ) = (val);break;\
			case 19:	BFPtrName->STRINGIZE( FieldName, 19 ) = (val);break;\
			case 20:	BFPtrName->STRINGIZE( FieldName, 20 ) = (val);break;\
			case 21:	BFPtrName->STRINGIZE( FieldName, 21 ) = (val);break;\
			case 22:	BFPtrName->STRINGIZE( FieldName, 22 ) = (val);break;\
			case 23:	BFPtrName->STRINGIZE( FieldName, 23 ) = (val);break;\
			case 24:	BFPtrName->STRINGIZE( FieldName, 24 ) = (val);break;\
			case 25:	BFPtrName->STRINGIZE( FieldName, 25 ) = (val);break;\
			case 26:	BFPtrName->STRINGIZE( FieldName, 26 ) = (val);break;\
			case 27:	BFPtrName->STRINGIZE( FieldName, 27 ) = (val);break;\
			case 28:	BFPtrName->STRINGIZE( FieldName, 28 ) = (val);break;\
			case 29:	BFPtrName->STRINGIZE( FieldName, 29 ) = (val);break;\
			case 30:	BFPtrName->STRINGIZE( FieldName, 30 ) = (val);break;\
			case 31:	BFPtrName->STRINGIZE( FieldName, 31 ) = (val);break;\
		};
//##############################################################################
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
	printf( "*(unsigned int*)&BF : 0x%08X\n", *( unsigned int* )&BF );
	printf( "BF.Field4 : %d\n", BF.Field4 );
		BF_ARR( BF, Field, 4, 0x3 );
	printf( "BF.Field4 : %d\n", BF.Field4 );
	printf( "*(unsigned int*)&BF : 0x%08X\n", *( unsigned int* )&BF );
	int i, fieldSize, fieldMask; 
	i = 0x5; fieldSize = 0x2; fieldMask = 0b11; //printf applicable
	//no direct access to BF.Field[i]:
	printf( "BFPtr->Field[%d] : %d\n",i,
				((( fieldMask << (i * fieldSize) ) & 
					*(unsigned int*)&BF) >> (i * fieldSize)) & fieldMask 
		  );
		  	BF32PTR_ARR( BFPtr, Field, i, 0x3 );
	printf( "BFPtr->Field[%d] : %d\n",i,
				((( fieldMask << (i * fieldSize) ) & 
					*(unsigned int*)&BF) >> (i * fieldSize)) & fieldMask 
		  );
	printf( "*(unsigned int*)&BF : 0x%08X\n", *( unsigned int* )&BF );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
