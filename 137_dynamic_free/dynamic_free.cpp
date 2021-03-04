#include <cstdio> 
#include <cstdlib>
#include <cstring>

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#define HEAP_OBJS_INC					0x8 //no of get heap objects

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
typedef struct
{	int inc = HEAP_OBJS_INC;//dynamic utilization of heap
	int used = 0;			//no of free obj pointers
	int left = 0;			//no of free obj slots
	unsigned long long	size = 0; //heap utilization (resources only)
	void** obj;				//object pointers; single obj size: <4GiB
}Heap_Resources_TypeDef;
Heap_Resources_TypeDef HEAP;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//dynamic allocation - no need for each item heap free'ing
void* alloc( size_t req_size ) //malloc() overlay
{	//mallocate objects pointers array: initialize, or extend on demand
	if (HEAP.left == 0)
	{	//use ptr as temporary pointer for extending objs array
		void **ptr = (void**)malloc((HEAP.used + HEAP.inc) 
									* sizeof( void* ));
		if ( ptr == NULL )	return NULL; 	//check avaiable memory
		//copy objs to new, extended location
		memmove( ptr, HEAP.obj, HEAP.used * sizeof( void* ) );
		free( HEAP.obj );			//free previous objs location
		HEAP.obj = ptr;				//update objs pointer
		ptr = NULL;					//free temporary pointer
		HEAP.left = HEAP.inc;		//update avaiable no of objs
	};
	
	//mallocate requested resource
	HEAP.obj[ HEAP.used ] = ( void* )malloc( req_size );
	if ( HEAP.obj[ HEAP.used ] == NULL )	return NULL;//check memory
	
	//update heap struct data
	HEAP.size += req_size;
	HEAP.used++;
	HEAP.left--;
	
	//return requested resource (before used objects increment)
	return HEAP.obj[ HEAP.used - 1 ];
};

//single free of all HEAP resources just before exit()
int free( void )	//free() overlay
{	//free each resource
	for( int i = 0x0; i < HEAP.used; i++ )
		free( HEAP.obj[ i ] );
	
	//free objects pointers
	if (HEAP.obj)
		free( HEAP.obj );
	
	//zero index'es
	HEAP.size = 0x0;
	HEAP.used = 0x0;
	HEAP.left = 0x0;
	
	return (int)NULL;
};

void heap_print( void )
{	printf( "HEAP.used : %i\n", HEAP.used );
	printf( "HEAP.left : %i\n", HEAP.left );
	printf( "HEAP.size : %llu\n", HEAP.size );
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	//first allocation - background HEAP.objs initialized
	char* arr = (char*)alloc( 20 );
	puts("arr[]:");heap_print();puts("");
		
	//second allocation
	int *iptr = (int*)alloc( 20 * sizeof(int*) );
	puts("arr[] + iptr[]:");heap_print();puts("");
	
	//multiple allocations with background HEAP.objs extending
	float **fptr; 
	fptr = (float**)alloc( 12 * sizeof(float*) );
	for( int i = 0x0; i < 12; i++ )
		fptr[ i ] = (float*)alloc( 5 * sizeof(float) );
	puts("arr[] + iptr[] + fptr[][]:");heap_print();puts("");
		
	//single heap free of: {"arr[]", "iptr[]", "fptr[][]"};
	return free();
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
