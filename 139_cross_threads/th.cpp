//https://docs.microsoft.com/en-us/windows/win32/sync/using-mutex-objects
//https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
#include <cstdio> 
#include <cstring>
#include <cstdarg>
#include "threads.h"

enum: int{ POOLSIZE = 0x10, DATASIZE = 0x40 };

typedef struct
{	unsigned char 		i_th;
	unsigned 			datasize;
	unsigned char 		*data;
}Th_printf_DataType;
 
CROSS_MUTEX_CREATE( m_i ); 
int global_i;

char thout[ (1 + POOLSIZE) * DATASIZE ];
void* th_printf( void* in ) 
{	Th_printf_DataType *th_data;
	th_data = (Th_printf_DataType*)in;
	
	//obvious implementation:
	//	-threads executes randomly
	//	-writes to stdout and global_i is ordered with global mutex
	//	-printf might be a non-blocking function (terminal-depended) 
	cross_lock( m_i ); 
		printf( "[%i] : (size = %i)\"%s\"", 
			th_data->i_th,  
			th_data->datasize,
			(char*)th_data->data );
		printf( "global_i : %i\n", global_i ); 
	cross_unlock( m_i );
	
	//non-blocking, fully async, no race conditions, memory costly
	sprintf( &thout[ th_data->i_th * DATASIZE ], 
		"[%i] : (size = %i)\"%s\"", 
		th_data->i_th,  
		th_data->datasize,
		(char*)th_data->data );
	sprintf( 	&thout[ (th_data->i_th * DATASIZE) + 
				strlen(&thout[ th_data->i_th * DATASIZE ]) ], 
					"global_i : %i\n", global_i );
	
	//inc global i
	global_i++;

	//terminate this thread
	cross_exit_this_thread();
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	Cross_Thread th_main, th_pool[ POOLSIZE ];
	int th_res_main, th_res_pool[ POOLSIZE ];

	//set function data
	char main_arr[] = "Main thread input!";
	Th_printf_DataType main_data = 
	{	0,
		(unsigned)strlen( main_arr ),
		(unsigned char*)main_arr
	}; 
	char pool_arr[] = "...input...";
	Th_printf_DataType th_data[ POOLSIZE ];
	for( int t = 0x0; t < POOLSIZE; t++ )
	{	th_data[ t ].i_th = t + 1;
		th_data[ t ].datasize = (unsigned)strlen( pool_arr );
		th_data[ t ].data = (unsigned char*)pool_arr;
	};
	 
	//run main thread 
	global_i = 0;
	th_res_main = cross_create_thread( th_main, th_printf, 
		(void*)&main_data);
	
	//run thread pool on function data
	for( int t = 0x0; t < POOLSIZE; t++ )
		th_res_pool[ t ] = cross_create_thread( th_pool[ t ],
								th_printf, (void*)&th_data[ t ]);
	
	//join main thread
	cross_synchronize( th_main );
	printf( "[0].main returned : %i\n", th_res_main );
	
	//join thread pool
	for( int t = 0x0; t < POOLSIZE; t++ )
	{	cross_synchronize( th_pool[ t ] );
		printf( "[%i].pool returned : %i\n", t+1, th_res_pool[ t ] );
	};
	
	//free created mutex'es
	CROSS_MUTEX_FREE( m_i );
	
	printf( "\nglobal_i: %i = %i\n", POOLSIZE+1, global_i ); 
	
	printf( "\n====\nthout:\n");
	for ( int t = 0x0; t < (1 + POOLSIZE); t++ )
		printf( "th%s", &thout[ t * DATASIZE ] );
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


