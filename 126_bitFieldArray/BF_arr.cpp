#include <cstdio> 
using namespace std;
//##############################################################################
#ifndef CONCATENATE
	#define CONCATENATE( a, b ) a##b
#endif
//##############################################################################
//only compile-time Bit Fields!
#define BF_ARR( BFName, FieldName, no, val )								\
					BFName.CONCATENATE( FieldName, no ) = (val);
#define BFPTR_ARR( BFPTRName, FieldName, no, val )							\
					BFPTRName->CONCATENATE( FieldName, no ) = (val);
//##############################################################################
//only uniformly distibuted Bit Fields!
//instruction code size costly!
#define BF4_ARR( BFName, FieldName, no, val )								\
		switch( no )														\
		{	default:	break;												\
			case 0:		BFName.CONCATENATE( FieldName, 0 ) = (val);	break;	\
			case 1:		BFName.CONCATENATE( FieldName, 1 ) = (val);	break;	\
			case 2:		BFName.CONCATENATE( FieldName, 2 ) = (val);	break;	\
			case 3:		BFName.CONCATENATE( FieldName, 3 ) = (val);	break;	\
		};
#define BF4PTR_ARR( BFPtrName, FieldName, no, val )							\
		switch( no )														\
		{	default:	break;												\
			case 0:		BFPtrName->CONCATENATE( FieldName, 0 ) = (val);break;	\
			case 1:		BFPtrName->CONCATENATE( FieldName, 1 ) = (val);break;	\
			case 2:		BFPtrName->CONCATENATE( FieldName, 2 ) = (val);break;	\
			case 3:		BFPtrName->CONCATENATE( FieldName, 3 ) = (val);break;	\
		};

#define BF8_ARR( BFName, FieldName, no, val )								\
		switch( no )														\
		{	default:	break;												\
			case 0:		BFName.CONCATENATE( FieldName, 0 ) = (val);	break;	\
			case 1:		BFName.CONCATENATE( FieldName, 1 ) = (val);	break;	\
			case 2:		BFName.CONCATENATE( FieldName, 2 ) = (val);	break;	\
			case 3:		BFName.CONCATENATE( FieldName, 3 ) = (val);	break;	\
			case 4:		BFName.CONCATENATE( FieldName, 4 ) = (val);	break;	\
			case 5:		BFName.CONCATENATE( FieldName, 5 ) = (val);	break;	\
			case 6:		BFName.CONCATENATE( FieldName, 6 ) = (val);	break;	\
			case 7:		BFName.CONCATENATE( FieldName, 7 ) = (val);	break;	\
		};
#define BF8PTR_ARR( BFPtrName, FieldName, no, val )						\
		switch( no )														\
		{	default:	break;												\
			case 0:		BFPtrName->CONCATENATE( FieldName, 0 ) = (val);break;	\
			case 1:		BFPtrName->CONCATENATE( FieldName, 1 ) = (val);break;	\
			case 2:		BFPtrName->CONCATENATE( FieldName, 2 ) = (val);break;	\
			case 3:		BFPtrName->CONCATENATE( FieldName, 3 ) = (val);break;	\
			case 4:		BFPtrName->CONCATENATE( FieldName, 4 ) = (val);break;	\
			case 5:		BFPtrName->CONCATENATE( FieldName, 5 ) = (val);break;	\
			case 6:		BFPtrName->CONCATENATE( FieldName, 6 ) = (val);break;	\
			case 7:		BFPtrName->CONCATENATE( FieldName, 7 ) = (val);break;	\
		};

#define BF16_ARR( BFName, FieldName, no, val )								\
		switch( no )														\
		{	default:	break;												\
			case 0:		BFName.CONCATENATE( FieldName, 0 ) = (val);	break;	\
			case 1:		BFName.CONCATENATE( FieldName, 1 ) = (val);	break;	\
			case 2:		BFName.CONCATENATE( FieldName, 2 ) = (val);	break;	\
			case 3:		BFName.CONCATENATE( FieldName, 3 ) = (val);	break;	\
			case 4:		BFName.CONCATENATE( FieldName, 4 ) = (val);	break;	\
			case 5:		BFName.CONCATENATE( FieldName, 5 ) = (val);	break;	\
			case 6:		BFName.CONCATENATE( FieldName, 6 ) = (val);	break;	\
			case 7:		BFName.CONCATENATE( FieldName, 7 ) = (val);	break;	\
			case 8:		BFName.CONCATENATE( FieldName, 8 ) = (val);	break;	\
			case 9:		BFName.CONCATENATE( FieldName, 9 ) = (val);	break;	\
			case 10:	BFName.CONCATENATE( FieldName, 10 ) = (val);	break;	\
			case 11:	BFName.CONCATENATE( FieldName, 11 ) = (val);	break;	\
			case 12:	BFName.CONCATENATE( FieldName, 12 ) = (val);	break;	\
			case 13:	BFName.CONCATENATE( FieldName, 13 ) = (val);	break;	\
			case 14:	BFName.CONCATENATE( FieldName, 14 ) = (val);	break;	\
			case 15:	BFName.CONCATENATE( FieldName, 15 ) = (val);	break;	\
		};
#define BF16PTR_ARR( BFPtrName, FieldName, no, val )						\
		switch( no )														\
		{	default:	break;												\
			case 0:		BFPtrName->CONCATENATE( FieldName, 0 ) = (val);break;	\
			case 1:		BFPtrName->CONCATENATE( FieldName, 1 ) = (val);break;	\
			case 2:		BFPtrName->CONCATENATE( FieldName, 2 ) = (val);break;	\
			case 3:		BFPtrName->CONCATENATE( FieldName, 3 ) = (val);break;	\
			case 4:		BFPtrName->CONCATENATE( FieldName, 4 ) = (val);break;	\
			case 5:		BFPtrName->CONCATENATE( FieldName, 5 ) = (val);break;	\
			case 6:		BFPtrName->CONCATENATE( FieldName, 6 ) = (val);break;	\
			case 7:		BFPtrName->CONCATENATE( FieldName, 7 ) = (val);break;	\
			case 8:		BFPtrName->CONCATENATE( FieldName, 8 ) = (val);break;	\
			case 9:		BFPtrName->CONCATENATE( FieldName, 9 ) = (val);break;	\
			case 10:	BFPtrName->CONCATENATE( FieldName, 10 ) = (val);break;\
			case 11:	BFPtrName->CONCATENATE( FieldName, 11 ) = (val);break;\
			case 12:	BFPtrName->CONCATENATE( FieldName, 12 ) = (val);break;\
			case 13:	BFPtrName->CONCATENATE( FieldName, 13 ) = (val);break;\
			case 14:	BFPtrName->CONCATENATE( FieldName, 14 ) = (val);break;\
			case 15:	BFPtrName->CONCATENATE( FieldName, 15 ) = (val);break;\
		};

#define BF32_ARR( BFName, FieldName, no, val )								\
		switch( no )														\
		{	default:	break;												\
			case 0:		BFName.CONCATENATE( FieldName, 0 ) = (val);	break;	\
			case 1:		BFName.CONCATENATE( FieldName, 1 ) = (val);	break;	\
			case 2:		BFName.CONCATENATE( FieldName, 2 ) = (val);	break;	\
			case 3:		BFName.CONCATENATE( FieldName, 3 ) = (val);	break;	\
			case 4:		BFName.CONCATENATE( FieldName, 4 ) = (val);	break;	\
			case 5:		BFName.CONCATENATE( FieldName, 5 ) = (val);	break;	\
			case 6:		BFName.CONCATENATE( FieldName, 6 ) = (val);	break;	\
			case 7:		BFName.CONCATENATE( FieldName, 7 ) = (val);	break;	\
			case 8:		BFName.CONCATENATE( FieldName, 8 ) = (val);	break;	\
			case 9:		BFName.CONCATENATE( FieldName, 9 ) = (val);	break;	\
			case 10:	BFName.CONCATENATE( FieldName, 10 ) = (val);	break;	\
			case 11:	BFName.CONCATENATE( FieldName, 11 ) = (val);	break;	\
			case 12:	BFName.CONCATENATE( FieldName, 12 ) = (val);	break;	\
			case 13:	BFName.CONCATENATE( FieldName, 13 ) = (val);	break;	\
			case 14:	BFName.CONCATENATE( FieldName, 14 ) = (val);	break;	\
			case 15:	BFName.CONCATENATE( FieldName, 15 ) = (val);	break;	\
			case 16:	BFName.CONCATENATE( FieldName, 16 ) = (val);	break;	\
			case 17:	BFName.CONCATENATE( FieldName, 17 ) = (val);	break;	\
			case 18:	BFName.CONCATENATE( FieldName, 18 ) = (val);	break;	\
			case 19:	BFName.CONCATENATE( FieldName, 19 ) = (val);	break;	\
			case 20:	BFName.CONCATENATE( FieldName, 20 ) = (val);	break;	\
			case 21:	BFName.CONCATENATE( FieldName, 21 ) = (val);	break;	\
			case 22:	BFName.CONCATENATE( FieldName, 22 ) = (val);	break;	\
			case 23:	BFName.CONCATENATE( FieldName, 23 ) = (val);	break;	\
			case 24:	BFName.CONCATENATE( FieldName, 24 ) = (val);	break;	\
			case 25:	BFName.CONCATENATE( FieldName, 25 ) = (val);	break;	\
			case 26:	BFName.CONCATENATE( FieldName, 26 ) = (val);	break;	\
			case 27:	BFName.CONCATENATE( FieldName, 27 ) = (val);	break;	\
			case 28:	BFName.CONCATENATE( FieldName, 28 ) = (val);	break;	\
			case 29:	BFName.CONCATENATE( FieldName, 29 ) = (val);	break;	\
			case 30:	BFName.CONCATENATE( FieldName, 30 ) = (val);	break;	\
			case 31:	BFName.CONCATENATE( FieldName, 31 ) = (val);	break;	\
		};
#define BF32PTR_ARR( BFPtrName, FieldName, no, val )						\
		switch( no )														\
		{	default:	break;												\
			case 0:		BFPtrName->CONCATENATE( FieldName, 0 ) = (val);break;	\
			case 1:		BFPtrName->CONCATENATE( FieldName, 1 ) = (val);break;	\
			case 2:		BFPtrName->CONCATENATE( FieldName, 2 ) = (val);break;	\
			case 3:		BFPtrName->CONCATENATE( FieldName, 3 ) = (val);break;	\
			case 4:		BFPtrName->CONCATENATE( FieldName, 4 ) = (val);break;	\
			case 5:		BFPtrName->CONCATENATE( FieldName, 5 ) = (val);break;	\
			case 6:		BFPtrName->CONCATENATE( FieldName, 6 ) = (val);break;	\
			case 7:		BFPtrName->CONCATENATE( FieldName, 7 ) = (val);break;	\
			case 8:		BFPtrName->CONCATENATE( FieldName, 8 ) = (val);break;	\
			case 9:		BFPtrName->CONCATENATE( FieldName, 9 ) = (val);break;	\
			case 10:	BFPtrName->CONCATENATE( FieldName, 10 ) = (val);break;\
			case 11:	BFPtrName->CONCATENATE( FieldName, 11 ) = (val);break;\
			case 12:	BFPtrName->CONCATENATE( FieldName, 12 ) = (val);break;\
			case 13:	BFPtrName->CONCATENATE( FieldName, 13 ) = (val);break;\
			case 14:	BFPtrName->CONCATENATE( FieldName, 14 ) = (val);break;\
			case 15:	BFPtrName->CONCATENATE( FieldName, 15 ) = (val);break;\
			case 16:	BFPtrName->CONCATENATE( FieldName, 16 ) = (val);break;\
			case 17:	BFPtrName->CONCATENATE( FieldName, 17 ) = (val);break;\
			case 18:	BFPtrName->CONCATENATE( FieldName, 18 ) = (val);break;\
			case 19:	BFPtrName->CONCATENATE( FieldName, 19 ) = (val);break;\
			case 20:	BFPtrName->CONCATENATE( FieldName, 20 ) = (val);break;\
			case 21:	BFPtrName->CONCATENATE( FieldName, 21 ) = (val);break;\
			case 22:	BFPtrName->CONCATENATE( FieldName, 22 ) = (val);break;\
			case 23:	BFPtrName->CONCATENATE( FieldName, 23 ) = (val);break;\
			case 24:	BFPtrName->CONCATENATE( FieldName, 24 ) = (val);break;\
			case 25:	BFPtrName->CONCATENATE( FieldName, 25 ) = (val);break;\
			case 26:	BFPtrName->CONCATENATE( FieldName, 26 ) = (val);break;\
			case 27:	BFPtrName->CONCATENATE( FieldName, 27 ) = (val);break;\
			case 28:	BFPtrName->CONCATENATE( FieldName, 28 ) = (val);break;\
			case 29:	BFPtrName->CONCATENATE( FieldName, 29 ) = (val);break;\
			case 30:	BFPtrName->CONCATENATE( FieldName, 30 ) = (val);break;\
			case 31:	BFPtrName->CONCATENATE( FieldName, 31 ) = (val);break;\
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
		  	BF16PTR_ARR( BFPtr, Field, i, 0x3 );
	printf( "BFPtr->Field[%d] : %d\n",i,
				((( fieldMask << (i * fieldSize) ) & 
					*(unsigned int*)&BF) >> (i * fieldSize)) & fieldMask 
		  );
	printf( "*(unsigned int*)&BF : 0x%08X\n", *( unsigned int* )&BF );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
