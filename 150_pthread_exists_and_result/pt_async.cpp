#include <cstdio> 
#include <pthread.h>
#include <unistd.h>

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#define FUNC_CAST(s)	(void*(*)(void*))&s
int async_func_completed = false;
typedef struct
{
	void*(*func_ptr)(void*);
	void* args;
	void* ret;
}TypeDef_Async_Caller;

void async_caller( TypeDef_Async_Caller* in )
{
	async_func_completed = false;
		in->ret = (*in->func_ptr)(in->args);
	async_func_completed = true;
};

void* async ( void*(*func)(void*), void* func_args, void*(*wdg_func)(void*), void* wdg_args, int wdg_period_ms )
{
	int st;
	pthread_t t_async;
	TypeDef_Async_Caller caller_data;
	caller_data.func_ptr = func;
	caller_data.args = func_args;

	st = pthread_create( &t_async, NULL, FUNC_CAST(async_caller), &caller_data );
	while( async_func_completed != true )
	{
		(*wdg_func)(wdg_args);
		usleep( wdg_period_ms * 1000 );
	};
	pthread_join( t_async, NULL );

	return caller_data.ret;
};
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




void foo( void )
{
	puts( "...msg from foo()..." );
	sleep( 1 );
};//foo()

void wdg( int key )
{
	printf( "\t...WDG func(%i)...\n", key );
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	
	(int*)async( FUNC_CAST(foo), NULL, FUNC_CAST(wdg), (void*)11, 200 );
	printf( "Thread executed asynchronously\n" );
	
	puts( "...program terminated..." );
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
