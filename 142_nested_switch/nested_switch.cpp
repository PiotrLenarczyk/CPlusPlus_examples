#include <cstdio>

#define SELECTOR_1					0x100
	#define SUBSELECTOR_1				0x1
	#define SUBSELECTOR_2				0x2
	#define SUBSELECTOR_3_DEPENDED_1	0x11
	#define SUBSELECTOR_4_DEPENDED_2	0x12
#define SELECTOR_2					0x200
	#define SUBSELECTOR_1				0x1
#define PRINT( s )	printf( #s" : 0x%08X\n", s );
#define CONCATENATE( a, b ) a##b
#define CASE_GOTOLABEL_SUBSELECTOR_3_DEPENDED_1( i )				\
			CONCATENATE(chooser_3_, i)
#define CASE_GOTOLABEL_SUBSELECTOR_4_DEPENDED_2( i )				\
			CONCATENATE(chooser_4_, i)
#define CHOOSER_SUBSELECTORS_ALL( i )								\
			switch( global_subselector )							\
			{	case SUBSELECTOR_3_DEPENDED_1: 						\
					goto CASE_GOTOLABEL_SUBSELECTOR_3_DEPENDED_1(i);\
					break;											\
				case SUBSELECTOR_4_DEPENDED_2:						\
					goto CASE_GOTOLABEL_SUBSELECTOR_4_DEPENDED_2(i);\
					break;											\
			};

int global_selector, global_subselector;

void switch_chooser( void )
{	global_selector = SELECTOR_1;
	global_subselector = SUBSELECTOR_4_DEPENDED_2;
	printf( "\n====\nFirst subselection within func\n====\n" );
	switch( global_selector )
	{	case SELECTOR_1:
			PRINT( SELECTOR_1 );
			printf( "\t" );
			switch( global_subselector )
			{	default:
					break;
				CASE_GOTOLABEL_SUBSELECTOR_3_DEPENDED_1(1):
				case SUBSELECTOR_1:
					PRINT( SUBSELECTOR_1 );
					break;
				CASE_GOTOLABEL_SUBSELECTOR_4_DEPENDED_2(1):
				case SUBSELECTOR_2:
					PRINT( SUBSELECTOR_2 );
					break;
				case SUBSELECTOR_3_DEPENDED_1:
				case SUBSELECTOR_4_DEPENDED_2:
					CHOOSER_SUBSELECTORS_ALL(1);
					break;
			};
			break;
		default:
		case SELECTOR_2:
			PRINT( SELECTOR_2 );
			break;
	};
	
	//multiple subselections
	printf( "\n====\nSecond subselection within func\n====\n" );
	global_subselector = SUBSELECTOR_3_DEPENDED_1;
	switch( global_subselector )
	{	default:
			break;
		CASE_GOTOLABEL_SUBSELECTOR_3_DEPENDED_1(2):
		case SUBSELECTOR_1:
			PRINT( SUBSELECTOR_1 );
			break;
		CASE_GOTOLABEL_SUBSELECTOR_4_DEPENDED_2(2):
		case SUBSELECTOR_2:
			PRINT( SUBSELECTOR_2 );
			break;
		case SUBSELECTOR_3_DEPENDED_1:
		case SUBSELECTOR_4_DEPENDED_2:
			CHOOSER_SUBSELECTORS_ALL(2);
			break;
	};
};

void switch_second_func( void )
{	printf( "\n====\nThird subselection other func\n====\n" );
	global_subselector = SUBSELECTOR_3_DEPENDED_1;
	switch( global_subselector )
	{	default:
			break;
		CASE_GOTOLABEL_SUBSELECTOR_3_DEPENDED_1(1):
		case SUBSELECTOR_1:
			PRINT( SUBSELECTOR_1 );
			break;
		CASE_GOTOLABEL_SUBSELECTOR_4_DEPENDED_2(1):
		case SUBSELECTOR_2:
			PRINT( SUBSELECTOR_2 );
			break;
		case SUBSELECTOR_3_DEPENDED_1:
		case SUBSELECTOR_4_DEPENDED_2:
			CHOOSER_SUBSELECTORS_ALL(1);
			break;
	};
};

int main( void )
{
	switch_chooser();
	
	switch_second_func();
	return 0;
};
